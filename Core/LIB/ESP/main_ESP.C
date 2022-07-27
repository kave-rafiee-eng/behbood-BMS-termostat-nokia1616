#include "main.h"
#include "../LIB/ESP/main_ESP.H"

#define def_tbr_g1_ESP_T1 5
#define def_tbr_g1_ESP_T2 6

extern struct st_soft_usart_RX	soft_usart_RX;
extern struct st_soft_usart_TX	soft_usart_TX;

extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];

extern struct st_bms bms;

void interupt_soft_uart(){

		if( soft_usart_RX.F_data_get ){soft_usart_RX.F_data_get=0;
			
					// soft_usart_RX.DATA *last data
					//soft_usart_RX.STR  *STRING DATA
					//soft_usart_RX.STR_count *NUMBER OF DATA SAVE ON STRING
					//soft_uart_send_byte();
			
					soft_usart_TX.EN_STDOUT_OUT=1;
					printf(soft_usart_RX.STR);
					soft_usart_TX.EN_STDOUT_OUT=0;
			
					soft_uart_rx_str_clear();
					
		}
	
}


void ESP_main(){
	
		//bms.Humidity_now
		//bms.Humidity_set
		//bms.TEMP_now
		//bms.TEMP_set
		//bms.seting_RUN * seting_end_from_touch
	
	if( bms.seting_RUN ){ bms.seting_RUN=0;

					soft_usart_TX.EN_STDOUT_OUT=1;
					printf("\nseting_end\n");
					soft_usart_TX.EN_STDOUT_OUT=0;
		
	}
		
}


void ESP_timer(){
	
		if( tbr_g1[def_tbr_g1_ESP_T1].F_end ){ tbr_g1[def_tbr_g1_ESP_T1].F_end=0;

				soft_usart_TX.EN_STDOUT_OUT=1;
				printf("test_printf_on_SOFT_UART \n");
				soft_usart_TX.EN_STDOUT_OUT=0;
		}
		
		if( tbr_g1[def_tbr_g1_ESP_T2].F_end ){ tbr_g1[def_tbr_g1_ESP_T2].F_end=0;

		}		
		
	
}

void ESP_ini(){
			
	tbr_g1[def_tbr_g1_ESP_T1].EN=1;
	tbr_g1[def_tbr_g1_ESP_T1].C_set_time=900;	
		
	tbr_g1[def_tbr_g1_ESP_T2].EN=1;
	tbr_g1[def_tbr_g1_ESP_T2].C_set_time=50;	
	
}

