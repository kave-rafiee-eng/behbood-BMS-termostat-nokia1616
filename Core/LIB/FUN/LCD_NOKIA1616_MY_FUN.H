
#ifndef __LCD_NOKIA1616_MY_FUN_H
#define __LCD_NOKIA1616_MY_FUN_H

void put_picture_from_spi_flash(char num_pic);
void Square(int x,int y,int h,int w , unsigned int color );
void put_char(int x, int y, unsigned char in , char size , unsigned int color);
void lcd_put_number(char x,char y, int number, char size , unsigned int back_color ,  unsigned int num_color);
void startup_lcd_picture();
#endif 
