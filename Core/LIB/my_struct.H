#include "define_const.h"
#ifndef _MY_STRUCT_H_
#define _MY_STRUCT_H_
	
	
		
	struct st_touch
	{
		unsigned char pluse : 1;
		unsigned char less : 1;
		unsigned char seting : 3;	
		unsigned char edge : 1;

		unsigned int less_timer ;	
		unsigned int pluse_timer ;
		
		unsigned char less_fast : 1;
		unsigned char pluse_fast : 1;	
		
		int REST_TIMER : 14;
		
	};
	
	struct st_bms 
	{
		
		int TEMP_set : 10;
		int Humidity_set : 10;
		
		int TEMP_now : 10;
		int Humidity_now : 10;	
		
		unsigned char dark_mode : 1;	
		
		unsigned char config : 1;
		unsigned char Sensor : 1;
		unsigned char Actuator : 1;
		
		unsigned char seting_RUN : 1;
				
	};
	
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

	

	struct st_soft_usart_RX	 
	{
		unsigned char F_data_get :1;
		volatile unsigned char STR_count : 7;
		unsigned char STR[def_num_rx_get] ;
		unsigned char DATA ;
	};
	
	struct st_soft_usart_TX	 
	{
		unsigned char EN_STDOUT_OUT :1;
	};	
	
	
	struct st_usart_RX	 
	{
		volatile unsigned char I : 7;
		unsigned char str[def_num_rx_get] ;	
	};

	struct st_usart_TX	 
	{
		unsigned char I : 7;
		unsigned char str[def_num_tx_send] ;	
	};	
	
	struct counter
	{
		volatile unsigned int i : 8;	
		volatile unsigned int j : 8;
		unsigned long int v32 : 32;
		unsigned long int v25 : 25;
		unsigned int da : 8;	
		unsigned int db : 8;
		unsigned int dc : 8;	
		unsigned int dd : 8;		
						
	};
	
	struct cpu_timer_basic_10bit_auto_reset	 
	{
		volatile unsigned char F_end : 1;
		volatile unsigned char EN : 1;
		volatile unsigned int I_time : 10;
		volatile unsigned int C_set_time : 10;		
	};
	
	struct  cpu_timer_basic_10bit
	{
		volatile unsigned char F_end :1;
		volatile unsigned char EN :1;
		volatile unsigned int I_time :10;		
	};
	
	struct  cpu_timer_8bit_reset_contorol_Seconds
	{
		volatile unsigned char AUTO : 1;
		volatile unsigned char F_end : 1;
		volatile unsigned char EN : 1;
		volatile unsigned int I_time : 10;
		volatile unsigned int C_set_time : 10;		
	};


#endif