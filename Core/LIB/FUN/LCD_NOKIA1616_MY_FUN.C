
#include "main.h"
#include "../LIB/NokiaTFTLib/lcd_font5x7.h"


extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
extern struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
extern struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];

extern struct counter c;

extern struct st_programer programer;
extern struct st_W25Q W25Q;

extern unsigned char ram_read[];
extern unsigned char ram_write[512];


void lcd_put_number(char x,char y, int number, char size , unsigned int back_color ,  unsigned int num_color ){
	
		Square(x,y-3,((size*5)+(size*2))*2,(size*8)+3,back_color);
	
		if( number > 9 )put_char(x,y,((number/10)%10)+48,size,num_color);
		if( number >= 0 )put_char(x+(size*5)+(size*2),y,((number/1)%10)+48,size,num_color);
	
}

void put_picture_from_spi_flash(char num_pic ){
	
			nlcdSetOrientation(LCD_ORIENTATION_270);
		
			_nlcdSetWindow(0, 0, nlcdGetWidth(), nlcdGetHeight());
			int all_pixel = nlcdGetWidth()*nlcdGetHeight();
		
			printf("\n nlcdGetWidth=%d, nlcdGetHeight=%d, all_pixel=%d",nlcdGetWidth(),nlcdGetHeight(),all_pixel);	

			programer.P = (addr_start_block_pic *256 )+ ( num_pic * size_pic_sector4k * 16 ) ;
		
			int cont;
			for(cont=0; cont<=all_pixel/128 ; cont++ ){
								
				//W25Q_ReadPage((uint8_t *)&ram_read[0],programer.P*256, 256);
				//printf("\n PAGE_READ = %d", programer.P );	
				
				W25Q_ReadPage_start(programer.P*256);	
				
				for(c.v25=0; c.v25<256; c.v25+=2){
					
					_nlcdSend( SPI_w25q(0) | SPFD54124B_SEND_DATA  );
					_nlcdSend( SPI_w25q(0) | SPFD54124B_SEND_DATA  );					
				}
				set_CS_W25Q;
				programer.P++;
				
			}				
			
			_nlcdSendCmd(SPFD54124B_CMD_NOP);
	
}


void Square(int x,int y,int h,int w ,  unsigned int color){
	
		unsigned char i,j,k,l;

		for(j=0; j<h; j++){
			
				for(i=0; i<w; i++){
					
					 nlcdPixel(x+j,y+i,color);

				}
		}	
	
}

void put_char(int x, int y, unsigned char in , char size ,  unsigned int color){
	
		unsigned char ch;		
		unsigned char tavan;
	
		in -= 32;
		in *= 5;
		in +=7;
	
		unsigned char i,j,k,l;
		
		for(j=0; j<5*size; j+=size){
		
				ch = font5x7latcyr[in+(j/size)];

				tavan=1;
				for(i=0; i<8*size; i+=size){
					
						if( ch & tavan ){ 
							for(k=0;k<size;k++){
								for(l=0;l<size;l++)nlcdPixel(x+j+k,y+i+l,color);
							}
							
						}
						tavan*=2;

				}
		}	
}