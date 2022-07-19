#include "main.h"
#include "W25Q.h"
#include "PC_COM.h"
#include "../define_Const.h"
#include "../my_struct.h"
#include "cpu_timer.h"
#include "string.h"
#include  "../LIB/CODE/DAC.h"
#include "../LIB/littlefs/lfs.h"
#include "stdio.h"

char lfs_write=0;
uint32_t WriteBuf_i=0;


struct st_usart_RX usart_RX; 
struct st_usart_TX usart_TX;

extern char WriteBuf[def_num_lfs_ram];
extern char ReadBuf[def_num_lfs_ram];
extern lfs_t lfs;
extern lfs_file_t file;

extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
extern struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
extern struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];

extern struct counter c;
struct st_debuge_out_EN debuge_out_EN;

struct st_debuge_var	debuge_var;

extern struct st_programer programer;
extern struct st_W25Q W25Q;

char usart_comp_str( char str_comp[10] );
void usart_send_str_int( char str_send[20] , int var );
void uart_manager_interupt();
void debuge_uart();


char put_help(){

	if( debuge_var.i_next == 1 ) 	    { clr_str_tx(); printf("-----------------------------------------------\n");}
	else if( debuge_var.i_next == 2 ) usart_send_str_int("  *help*",0);
	else if( debuge_var.i_next == 3 ) usart_send_str_int("  *system*",1);
	else if( debuge_var.i_next == 4 ) usart_send_str_int("  *w25q*",1);	
	else if( debuge_var.i_next == 5 ) usart_send_str_int("  *program_on*",1);		
	else if( debuge_var.i_next == 6 ) usart_send_str_int("  *myfile.read*",1);	
	else if( debuge_var.i_next == 7 ) usart_send_str_int("  *myfile.write",1);	
	
	else if( debuge_var.i_next == 10 ) { clr_str_tx(); printf("-----------------------------------------------\n");}
	else{ 
		return 0;
	}
	return 1;	
}



int ram_i=0;
char put_w25q(){

	char temp;
	
	if( debuge_var.i_next == 1 ) { usart_send_str_int("   ------",0);
				W25Q_Read_Manufact_Device_ID();
				W25Q_Read_StatusReg();	
	}
	else if( debuge_var.i_next == 2 ) usart_send_str_int("  ID_Manu",W25Q.ID_Manufacturer);
	else if( debuge_var.i_next == 3 ) usart_send_str_int("  ID_device",W25Q.ID_device);
	else if( debuge_var.i_next == 4 ) usart_send_str_int("  Reg1",W25Q.StatusReg1);
	else if( debuge_var.i_next == 5 ) usart_send_str_int("  Reg2",W25Q.StatusReg2);	
	else if( debuge_var.i_next == 6 ) { programer.I=0; programer.P=0;
	W25Q_ReadPage_start(programer.P*256);	} 
	else if( debuge_var.i_next == 7 ) { debuge_var.i_next=6;  	
		
	 	if( programer.I > 255 ){ usart_send_str_int("   ------",0);	
			
			set_CS_W25Q; 
			
				programer.I=0; 	
				programer.P++;
				W25Q_ReadPage_start(programer.P*256);
				if( programer.P >= 250 ){
					debuge_var.i_next=7;	
				}	
				
	 	}
	 	else{
			
			clr_str_tx();
			
			temp = SPI_w25q(0);
			
			printf ("/%x/",temp);
			
			//USART1->TDR = SPI_w25q(0);
			
			
	 		programer.I++;	
			
	 	}
	}		
	else if( debuge_var.i_next == 21 ) usart_send_str_int("   ------",0);
	else{ 
		ram_i=0;
		return 0;
	}
	return 1;	
}



void debuge_uart(){
	
	if( tb_g2[def_tb_g2_rx_CLR].F_end == 1 ){ tb_g2[def_tb_g2_rx_CLR].F_end=0;

		if( lfs_write ){ lfs_write=0; clr_str_tx();
			
					lfs_file_open(&lfs, &file, "my_file", LFS_O_RDWR | LFS_O_CREAT);
					lfs_file_rewind(&lfs, &file);
					lfs_file_write(&lfs, &file, &WriteBuf, sizeof(WriteBuf));
					lfs_file_close(&lfs, &file);
					lfs_unmount(&lfs);	
			
		}
		else if( debuge_out_EN.programer == 1 ){ 
			
			//usart_send_str_int("--*END*--;",code_version);
				
			debuge_out_EN.programer=0; 				
			set_CS_W25Q;

			debuge_var.i_next=0;			
			clr_str_rx();
			clr_str_tx();
			
			printf("--*END*--I=%d,P=%d,",programer.I,programer.P);	
			
		}
		else if( usart_comp_str("help;") ){ 
				debuge_out_EN.help=1;	
				usart_send_str_int("PUT_HELP;",code_version);
		}	
		else if( usart_comp_str("myfile.read") ){ clr_str_tx();
			
			lfs_file_open(&lfs, &file, "my_file", LFS_O_RDWR | LFS_O_CREAT);
			lfs_file_read(&lfs, &file, &ReadBuf, sizeof(ReadBuf));
			lfs_file_close(&lfs, &file);
			lfs_unmount(&lfs);
			printf("****************your DATA///////////////////-\n");
			printf("*\n");printf("*\n");printf("*\n");printf("*\n");printf("*\n");
			ReadBuf[0]='*';
			printf("%s",ReadBuf);
	    printf("*\n");printf("*\n");printf("*\n");printf("*\n");printf("*\n");
		}				
		else if( usart_comp_str("myfile.write") ){ clr_str_tx();
			
				printf("*\n");printf("*\n");printf("*\n");printf("*\n");printf("*\n");
				printf("----------littleFS START After send data----------\n");
			  printf("*\n");printf("*\n");printf("*\n");printf("*\n");printf("*\n");
				lfs_write=1;
				for(c.i=0; c.i<200; c.i++ )WriteBuf[c.i] = NULL;
			  //strcmp(WriteBuf,usart_TX.str);
				WriteBuf_i=0;

		}		
		else if( usart_comp_str("dac;") ){ 
			dac_start();
			debuge_out_EN.dac=1-debuge_out_EN.dac;
			usart_send_str_int("DAC_EN;",debuge_out_EN.dac);
		}
		else if( usart_comp_str("w25q;") ){ set_CS_W25Q;	
			debuge_out_EN.w25q=1 - debuge_out_EN.w25q;
			if( debuge_out_EN.w25q ){
				usart_send_str_int("W25Q;",code_version);	
			}	 					
		}		
		else if( usart_comp_str("program_on;") ){ 
			
			int l_c=0;
			for( l_c=0; l_c<20; l_c++ ){
				W25Q_EraseSector4KB(l_c);
			}											
			
			programer.I=0;
			programer.P=0;
			
			W25Q_WritePage_start(programer.P*256);
			
			debuge_out_EN.programer=1;
			
			debuge_out_EN.w25q=0;
			usart_send_str_int("program_on;",code_version);
			
		}		
		else {
			usart_send_str_int("--Error404--",code_version);
			//strcpy( usart_TX.str , "--Error404--" );
			//uart_tx_dma( 10 , (uint32_t)&USART1->TDR , (uint32_t)&usart_TX.str );
		}
		debuge_var.i_next=0;			
		clr_str_rx();					
	}
	
	
	/*if( debuge_out_EN.sec_ct == 1 ){
		
		tbrc_s1[def_tbrc_s1_log_root].EN=1;
		tbrc_s1[def_tbrc_s1_log_root].C_set_time=2;
		tbrc_s1[def_tbrc_s1_log_root].AUTO=1;	
	}
	else{	
		tbrc_s1[def_tbrc_s1_log_root].EN=0;			
	}*/
	
	
	/*if( tbrc_s1[def_tbrc_s1_log_root].F_end == 1 ){ 
		
		tbrc_s1[def_tbrc_s1_log_root].F_end=0;
		
		if( debuge_out_EN.sec_ct == 1 ){
			debuge_out_EN.ct = 1;
		}
		
	}*/	
		
	if(  debuge_out_EN.help || debuge_out_EN.system ||
	debuge_out_EN.w25q 
	 )
	{	
		tbr_g1[def_tbr_g1_DEGUG].C_set_time=5;
		tbr_g1[def_tbr_g1_DEGUG].EN=1;	
	}
	else { 
		tbr_g1[def_tbr_g1_DEGUG].EN=0;
		debuge_var.i_next=0;
	}
	
	if( tbr_g1[def_tbr_g1_DEGUG].F_end == 1 ){ tbr_g1[def_tbr_g1_DEGUG].F_end=0;
		
		debuge_var.i_next++;
	
		if( debuge_out_EN.help ) debuge_out_EN.help=put_help();			
		else if( debuge_out_EN.w25q  ) debuge_out_EN.w25q = put_w25q();
		else { 
							
		}		
	
	}
	

		
}


char usart_comp_str( char str_comp[def_num_rx_get] ){
	
	for(c.i=0; c.i<def_num_rx_get; c.i++ ){
		
		if( usart_RX.str[c.i] != '\0' ){
			if( usart_RX.str[c.i] !=  str_comp[c.i] ){ return 0; }	
		}
		else{
			return 1;	
		}
			
	}			
}

void usart_send_str_int( char str_send[def_num_tx_send-5] , int var ){
	
	int b[5]={' ',' ',' ',' '};
	
	if( var >= 0 ){ b[3] = (var % 10)+48; }
	if( var >= 10 ){ b[2] = ((var/10) % 10)+48; }	
	if( var >= 100 ){ b[1] = ((var/100) % 10)+48 ;}
	if( var >= 1000 ){ b[0] = ((var/1000) % 10)+48; }
	
	clr_str_tx();
		
	strcpy( usart_TX.str , str_send );
	
	c.i=0;
	while( usart_TX.str[c.i] != '\0' ){ c.i++; }
		
	usart_TX.str[c.i] = b[0]; 
	usart_TX.str[c.i+1] = b[1];
	usart_TX.str[c.i+2] = b[2];
	usart_TX.str[c.i+3] = b[3];
	usart_TX.str[c.i+4] = 0x0A;
	usart_TX.str[c.i+5] = '\0';
	
	USART1->TDR = usart_TX.str[0];
	
}


void program_manager(){
	
		if(  lfs_write ){
			if(usart_RX.I > 0 ){ usart_RX.I=0;	
					WriteBuf[WriteBuf_i]=usart_RX.str[0];
					WriteBuf_i++;
			}
		}
		else if( debuge_out_EN.programer ){
				if(usart_RX.I > 0 ){ usart_RX.I=0;																				
							
						if(  programer.I > 255 )  { 
							
								set_CS_W25Q;
							  W25Q_WaitBusy();

   							programer.I = 0;
								programer.P++;		
								W25Q_WritePage_start(programer.P*256);			
						}	
						
					  SPI_w25q(usart_RX.str[0]);  						
						programer.I++;
						
				}
		}
}

void uart_manager_interupt_rx(){
	
		tb_g2[def_tb_g2_rx_CLR].EN=1; 
		tb_g2[def_tb_g2_rx_CLR].I_time=def_time_uart_rx_CLR; 
		
		usart_RX.str[usart_RX.I] = USART1->RDR ;	
		usart_RX.I++;
		if( usart_RX.I > def_num_rx_get )usart_RX.I=0; 	
	
}

void uart_manager_interupt_tx(){
	
		usart_TX.I++;
		if( usart_TX.I > def_num_tx_send )usart_TX.I=0;
		
		if( usart_TX.str[usart_TX.I] != '\0' ){
			USART1->TDR = usart_TX.str[usart_TX.I];
		}
		else{ usart_TX.I=0; }	
	
}



void clr_str_tx(){
	for( c.i=0; c.i<def_num_tx_send; c.i++ ) usart_TX.str[c.i]='\0';	
	usart_TX.I=0;
}

void clr_str_rx(){
	for( c.i=0; c.i<def_num_rx_get; c.i++ ) usart_RX.str[c.i]='\0';
	usart_RX.I=0;
}

void ini_debuge(){
	
	clr_str_tx();
	clr_str_rx();
	
	debuge_var.i_next=0;
				
	debuge_out_EN.help=0;

	
}
