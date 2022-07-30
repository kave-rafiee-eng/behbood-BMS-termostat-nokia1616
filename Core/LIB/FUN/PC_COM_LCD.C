#include "main.h"
#include "W25Q.h"

#include "PC_COM_LCD.h"
#include "../define_Const.h"
#include "../my_struct.h"
#include "cpu_timer.h"
#include "string.h"




#define COMMAND_help "help"
#define COMMAND_w25q_read_bit "w25q_read_bit"
#define COMMAND_swap_read "swap_read"
#define COMMAND_w25q_read_pic "w25q_read_pic"
#define COMMAND_w25q_write_pic "w25q_write_pic"
#define COMMAND_lcd_put_picture "lcd_put_picture"




struct st_usart_RX usart_RX; 

extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
extern struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
extern struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];

extern struct counter c;
struct st_debuge_out_EN debuge_out_EN;

struct st_debuge_var	debuge_var;

extern struct st_programer programer;
extern struct st_W25Q W25Q;

extern unsigned char ram_read[];
extern unsigned char ram_write[512];

extern struct st_bms bms;

void uart_manager_interupt();
void debuge_uart();

void clear_temp_ram(){
	
		for(c.v32=0; c.v32<255; c.v32++){
				ram_read[c.v32]=0xff;
				ram_write[c.v32]=0xff;
		}	
}

long int scan_uart_get_int(){

		clr_str_rx();	
		while( !tb_g2[def_tb_g2_rx_CLR].F_end ){printf("."); LL_mDelay(500);}
			tb_g2[def_tb_g2_rx_CLR].F_end=0;
		return atoi(usart_RX.str);		
}


void w25q_put_page(){
	
		clr_str_rx();
		while( !tb_g2[def_tb_g2_rx_CLR].F_end ) { 
			
			W25Q_ReadPage((uint8_t *)&ram_read,programer.P*256,256);
			printf("\n PAGE = %d \n", programer.P );			
			for(c.v32=0; c.v32<256; c.v32++){
					if(c.v32%16 == 0 )printf("\n");	
					printf("%2x,",ram_read[c.v32]);
			}
			
			programer.P++;			
		}tb_g2[def_tb_g2_rx_CLR].F_end=0;
		clr_str_rx();
		
}

void put_w25q_register(){
	
			printf("---------------\n");
		
				W25Q_Read_Manufact_Device_ID();
				W25Q_Read_StatusReg();	
				printf("Manufact_Device_ID = %x \n",	W25Q.ID_Manufacturer);
				printf("ID_device = %x \n",	W25Q.ID_device);
				printf("StatusReg1 = %x \n",	W25Q.StatusReg1);
				printf("StatusReg2 = %x \n",	W25Q.StatusReg2);		
		
		printf("---------------\n");		
	
	
}


char lcd_put_picture(){
	
	programer.P=0; programer.I=0;
	
	if( !strcmp(COMMAND_lcd_put_picture,usart_RX.str) ){ 
		
			char num_pic=0;
			printf("NUM_PICTURE = \n");
			num_pic = scan_uart_get_int();
			printf("\n NUM_PICTURE = %d \n", num_pic );	
		
			_nlcdSetWindow(0, 0, nlcdGetWidth(), nlcdGetHeight());
			int all_pixel = nlcdGetWidth()*nlcdGetHeight();
		
			printf("\n nlcdGetWidth=%d, nlcdGetHeight=%d, all_pixel=%d",nlcdGetWidth(),nlcdGetHeight(),all_pixel);	

			programer.P = (addr_start_block_pic *256 )+ ( num_pic * size_pic_sector4k * 16 ) ;
		
			int cont;
			for(cont=0; cont<all_pixel/128 ; cont++ ){
								
				//W25Q_ReadPage((uint8_t *)&ram_read[0],programer.P*256, 256);
				//printf("\n PAGE_READ = %d", programer.P );	
				
				W25Q_ReadPage_start(programer.P*256);	
				
				for(c.v25=0; c.v25<255; c.v25+=2){
					
					_nlcdSend( SPI_w25q(0) | SPFD54124B_SEND_DATA  );
					_nlcdSend( SPI_w25q(0) | SPFD54124B_SEND_DATA  );					
				}
				set_CS_W25Q;
				programer.P++;
				
			}				
			
			_nlcdSendCmd(SPFD54124B_CMD_NOP);
	 
	}
	return 0;
	
}
char w25q(){
	
	programer.P=0; programer.I=0;
	
	if( !strcmp(COMMAND_w25q_read_bit,usart_RX.str) ){ 
	
		put_w25q_register();
		
		printf("NUM_START_PAGE = \n");
		programer.P = scan_uart_get_int();
		printf("\n PAGE_START = %d \n", programer.P );
		
		w25q_put_page();

	}
	else if( !strcmp(COMMAND_swap_read,usart_RX.str) ){

		put_w25q_register();
		
		programer.P = addr_start_block_swap * 256;
	
		printf("SWAP_READ_BIT = \n");
		printf("\n PAGE_START = %d \n", programer.P );
		
		w25q_put_page();	
	}
	if( !strcmp(COMMAND_w25q_read_pic,usart_RX.str) ){ 
	
		put_w25q_register();
		
		char num_pic;
		
		printf("NUM_PICTURE = \n");
		num_pic = scan_uart_get_int();
		programer.P = (addr_start_block_pic *256 )+ ( num_pic * size_pic_sector4k * 16 );
		printf("\n NUM_PICTURE = %d & PAGE_START = %d\n", num_pic , programer.P );
		
		w25q_put_page();

	}
	//-------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------
	if( !strcmp(COMMAND_w25q_write_pic,usart_RX.str) ){ 
		
		//--swap ereasing 
		put_w25q_register();
	
		programer.P = addr_start_block_swap * 256;
		printf("\n SWAP_ADDRES(RGB16 FOR LCD (192 per page ,SAVE) ) = %d \n", programer.P );

		printf("\n EARSING_SWAP\n");
		c.v32 = addr_start_block_swap * 16;
		for(c.j=0; c.j<size_swap_sector4k; c.j++){
			 W25Q_EraseSector4KB(c.v32);
			 printf("EraseSector4KB = %d\n",c.v32);
			 c.v32++;
		}
		printf("\n-XXX-successful_ERAS_SWAP-XXX-programer.I= %d, programer.P = %d \n",programer.I,programer.P);
		
		//--get data from uart and save it to swap
		
			clr_str_rx();
			W25Q_WritePage_start(programer.P*256);
			while( tb_g2[def_tb_g2_rx_CLR].F_end == 0  ){
				
				if(usart_RX.I > 0 ){ usart_RX.I=0;																				
							
						if(  programer.I == 191 )  { 
							
							  SPI_w25q(usart_RX.str[0]);  	
								//SPI_w25q(50);  
								set_CS_W25Q;
							  W25Q_WaitBusy();

   							programer.I = 0;
								programer.P++;		
								W25Q_WritePage_start(programer.P*256);			
						}
						else{
							SPI_w25q(usart_RX.str[0]);  
							//SPI_w25q(50);
							programer.I++;
						}
				 }	
					
			}tb_g2[def_tb_g2_rx_CLR].F_end = 0;	

			clr_str_rx();
			
			int size_save_swap = (programer.P *256 ) - (addr_start_block_swap * 65536);
			printf("\n!successful_SAVE_SWAP----programer.I= %d, programer.P = %d , %d KB SAVE\n",programer.I,programer.P,size_save_swap);				
			
			//-------------------------------convert format

			int num_pic;	
			printf("NUM_PICTURE_TO_CONVERT&SAVE = \n");
			num_pic = scan_uart_get_int();
			programer.P = (addr_start_block_pic *256 )+ ( num_pic * size_pic_sector4k * 16 );
			printf("\n NUM_PICTURE = %d & PAGE_START = %d\n", num_pic , programer.P );

			//--ERASING SPASE OF PICTURE

			printf("\n ERASING_SPASE_OF_PICTURE\n");
			c.v32 = (addr_start_block_pic *16 )+ ( num_pic * size_pic_sector4k);
			c.v32 -=1;
			for(c.j=0; c.j<size_swap_sector4k; c.j++){
				 W25Q_EraseSector4KB(c.v32);
				 printf("EraseSector4KB = %d\n",c.v32);
				 c.v32++;
			}
			
			//--CONVERTING
		
			printf("\n**************START CONVERTING**************\n");
			
			unsigned long int swap_p;
			
			unsigned char r,g,b;			
			
			swap_p = addr_start_block_swap * 256;
			
			clear_temp_ram();
			
			int cont,c_swap;
			c_swap=0;
			for(cont=0; cont<size_pic_sector4k * 16 ; cont++ ){
				
					W25Q_ReadPage((uint8_t *)&ram_read,	(swap_p+c_swap)*256,	256);
					W25Q_ReadPage((uint8_t *)&ram_read[256],(swap_p+c_swap+1)*256,	256);
					
					c.i=0;
					for(c.j=0; c.j<192; c.j+=3){
						
								r = ram_read[c.j];
								g = ram_read[c.j+1];
								b = ram_read[c.j+2];
								
								r = r /8;
								g = g /4;
								b = b /8;	
						
								c.v32 =  rgb_color_pack(r, g, b);
								ram_write[c.i] =  ( c.v32 >> 8 ) | SPFD54124B_SEND_DATA;
								ram_write[c.i+1] = c.v32 | SPFD54124B_SEND_DATA;
								c.i+=2;
						}
				
					c.i=0;
					for(c.j=0; c.j<192; c.j+=3){
						
								r = ram_read[256+c.j];
								g = ram_read[256+c.j+1];
								b = ram_read[256+c.j+2];
								
								r = r /8;
								g = g /4;
								b = b /8;	
						
								c.v32 =  rgb_color_pack(r, g, b);
						
								ram_write[128+c.i+1] =  c.v32 ;
								ram_write[128+c.i] = ( c.v32 >> 8 )  ;
						
								c.i+=2;
						}
			
				programer.P = (addr_start_block_pic *256 )+ ( num_pic * size_pic_sector4k * 16 ) + cont;
				W25Q_WritePage(ram_write, programer.P*256, 256);
						
				printf("swap_page %d & %d convert&save to %d page of picture\n",swap_p*256+c_swap,swap_p*256+c_swap+1,programer.P);
						
				c_swap +=2;
						
			}
		
			
		
	}
	
	return 0;
		
}


char help(){

	if( !strcmp(COMMAND_help,usart_RX.str) ){
		
		printf("---------------\n");	
		printf(COMMAND_help);printf("\n");	
		printf(COMMAND_w25q_read_bit);printf("\n");	
		printf(COMMAND_swap_read);printf("\n");
		printf(COMMAND_w25q_read_pic);printf("\n");
		printf(COMMAND_w25q_write_pic);printf("\n");		
		printf(COMMAND_lcd_put_picture);printf("\n");	
		
		printf("---------------\n");		
		
	}
	else return 0;
	
}




void debuge_uart(){
	
	if( tb_g2[def_tb_g2_rx_CLR].F_end == 1 ){ tb_g2[def_tb_g2_rx_CLR].F_end=0;

		if( help() ){}
		else if( w25q() ){}	
		else if( lcd_put_picture() ){}		
		else printf("---command not found---\n");
			
		debuge_var.i_next=0;			
		clr_str_rx();	
		
	}
	
		
}



void uart_manager_interupt_rx(){
	
		tb_g2[def_tb_g2_rx_CLR].EN=1; 
		tb_g2[def_tb_g2_rx_CLR].I_time=def_time_uart_rx_CLR; 
		
		usart_RX.str[usart_RX.I] = USART1->RDR ;	
		usart_RX.I++;
		if( usart_RX.I > def_num_rx_get )usart_RX.I=0; 	
	
}


void clr_str_rx(){
	for( c.i=0; c.i<def_num_rx_get; c.i++ ) usart_RX.str[c.i]='\0';
	usart_RX.I=0;
}

void ini_debuge(){
	
	clr_str_rx();

}
