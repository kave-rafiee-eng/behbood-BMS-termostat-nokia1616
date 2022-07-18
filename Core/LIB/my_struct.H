#include "define_const.h"
#ifndef _MY_STRUCT_H_
#define _MY_STRUCT_H_
	
	struct st_programer 
	{
		unsigned int I : 9;
		unsigned long int P : 32;
				
	};
	
	struct st_W25Q 
	{
		unsigned long int ID_Manufacturer : 32;
		unsigned long int ID_device : 32;
		unsigned long int BUF : 32;
		unsigned long int StatusReg1 : 32;
		unsigned long int StatusReg2 : 32;			
						
	};
	
	struct st_debuge_out_EN	 
	{
		unsigned char help : 1;
		unsigned char system : 1;
		unsigned char w25q : 1;	
		unsigned char programer :1;
		unsigned char dac :1;
						
	};
	struct st_debuge_var	 
	{
		unsigned char i_next : 8;
	};


	
	struct st_usart_RX	 
	{
		unsigned char I : 7;
		unsigned char str[def_num_rx_get] ;	
	};

	struct st_usart_TX	 
	{
		unsigned char I : 7;
		unsigned char str[def_num_tx_send] ;	
	};	
	
	struct counter
	{
		unsigned int i : 8;	
		unsigned int j : 8;
		unsigned long int v32 : 32;
		unsigned long int v25 : 25;
		unsigned int da : 8;	
		unsigned int db : 8;
		unsigned int dc : 8;	
		unsigned int dd : 8;		
						
	};
	
	struct cpu_timer_basic_10bit_auto_reset	 
	{
		unsigned char F_end : 1;
		unsigned char EN : 1;
		unsigned int I_time : 10;
		unsigned int C_set_time : 10;		
	};
	
	struct  cpu_timer_basic_10bit
	{
		unsigned char F_end :1;
		unsigned char EN :1;
		unsigned int I_time :10;		
	};
	
	struct  cpu_timer_8bit_reset_contorol_Seconds
	{
		unsigned char AUTO : 1;
		unsigned char F_end : 1;
		unsigned char EN : 1;
		unsigned int I_time : 10;
		unsigned int C_set_time : 10;		
	};


#endif