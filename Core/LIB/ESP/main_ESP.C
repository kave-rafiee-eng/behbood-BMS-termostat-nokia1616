#include "main.h"
#include "../LIB/ESP/main_ESP.H"

#define def_tbr_g1_ESP_T1 5
#define def_tbr_g1_ESP_T2 6

extern struct st_soft_usart_RX	soft_usart_RX;
extern struct st_soft_usart_TX	soft_usart_TX;

extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];

extern struct st_bms bms;
extern struct st_touch touch; 

#define esp_recive_target_temp "tt:"
#define esp_recive_target_humidity "th:"
#define esp_recive_sensor_tempreture "ct:"
#define esp_recive_sensor_humidity "ch:"

#define esp_recive_config "Config"
#define esp_recive_not_config "!Config"

#define esp_recive_Sensor_connected "Sensor"
#define esp_recive_Sensor_not_connected "!Sensor"

#define esp_recive_Actuator_connected "Actuator"
#define esp_recive_Actuator_not_connected "!Actuator"



int strfind(char str[],char substr[]){
		int ad = strstr(str,substr)  - (char *)&str[0];
		if( ad >= 0 )return ad;
		return -1;
}

int esp_recive_number(char buffer_uart[],char command[]){
	
		if( strfind(buffer_uart,command) >= 0 ){
			
				int ad = strfind(buffer_uart,(char *)command);
				char num[2];
				num[0] = buffer_uart[ad+strlen(command)];
				num[1] = buffer_uart[ad+strlen(command)+1];
				return atoi(num);		
		}
		return -1;
	
}

void interupt_soft_uart(){

		if( soft_usart_RX.F_data_get ){soft_usart_RX.F_data_get=0;
			
					soft_usart_TX.EN_STDOUT_OUT=1;
			
					int target_temp,target_humidity,
					sensor_tempreture,sensor_humidity,
					config,Sensor_connected,Actuator_connected,
					not_config,Sensor_not_connected,Actuator_not_connected
					;
					
					target_temp = esp_recive_number((char *)soft_usart_RX.STR,(char *)esp_recive_target_temp);
					target_humidity = esp_recive_number((char *)soft_usart_RX.STR,(char *)esp_recive_target_humidity);
					sensor_tempreture = esp_recive_number((char *)soft_usart_RX.STR,(char *)esp_recive_sensor_tempreture);
					sensor_humidity = esp_recive_number((char *)soft_usart_RX.STR,(char *)esp_recive_sensor_humidity);
					
					config = strfind((char *)soft_usart_RX.STR,(char *)esp_recive_config);
					not_config = strfind((char *)soft_usart_RX.STR,(char *)esp_recive_not_config);
						
					Sensor_connected = strfind((char *)soft_usart_RX.STR,(char *)esp_recive_Sensor_connected);
					Sensor_not_connected = strfind((char *)soft_usart_RX.STR,(char *)esp_recive_Sensor_not_connected);
					
					Actuator_connected = strfind((char *)soft_usart_RX.STR,(char *)esp_recive_Actuator_connected);
					Actuator_not_connected = strfind((char *)soft_usart_RX.STR,(char *)esp_recive_Actuator_not_connected);		
					
					if(touch.seting == 0 ){
						if( target_temp >=0  ){ bms.TEMP_set = target_temp; printf("target_temp=%d\n",target_temp); }
						if( target_humidity >=0 ){ bms.Humidity_set = target_humidity; printf("target_humidity=%d\n",target_humidity); }
					}
					if( sensor_tempreture >=0 ){  bms.TEMP_now = sensor_tempreture; printf("sensor_tempreture=%d\n",sensor_tempreture); }
					if( sensor_humidity >=0 ){  bms.Humidity_now = sensor_humidity;	printf("sensor_humidity=%d\n",sensor_humidity); }
					
					
					if( not_config >=0 ){ bms.config=0; printf("not_config\n");} 
					else if( config >=0 ){  bms.config=1; printf("config\n");}
					
					if( Sensor_not_connected >=0 ){ bms.Sensor=0; printf("Sensor_not_connected\n");}	
					else if( Sensor_connected >=0 ){ bms.Sensor=1; printf("Sensor_connected\n");}
					
					if( Actuator_not_connected >=0 ){ bms.Actuator=0; printf("Actuator_not_connected\n");}	
					else if( Actuator_connected >=0 ){ bms.Actuator=1; printf("Actuator_connected\n");}
					
					soft_uart_rx_str_clear();
					soft_usart_TX.EN_STDOUT_OUT=0;
					
					if(touch.seting == 0 ) refresh_data();
					
		}
	
}


void ESP_main(){
	
	
	if( bms.seting_RUN ){ bms.seting_RUN=0;

					soft_usart_TX.EN_STDOUT_OUT=1;
					printf("1:%2d#",bms.TEMP_set );
					printf("2:%2d#",bms.Humidity_set );
					soft_usart_TX.EN_STDOUT_OUT=0;
		
	}
		
}


void ESP_timer(){
	
		if( tbr_g1[def_tbr_g1_ESP_T1].F_end ){ tbr_g1[def_tbr_g1_ESP_T1].F_end=0;

				soft_usart_TX.EN_STDOUT_OUT=1;
				//printf("test_printf_on_SOFT_UART \n");
				soft_usart_TX.EN_STDOUT_OUT=0;
		}
		
		if( tbr_g1[def_tbr_g1_ESP_T2].F_end ){ tbr_g1[def_tbr_g1_ESP_T2].F_end=0;

		}		

}


void ESP_ini(){
			
	tbr_g1[def_tbr_g1_ESP_T1].EN=1;
	tbr_g1[def_tbr_g1_ESP_T1].C_set_time=1000;	
		
	tbr_g1[def_tbr_g1_ESP_T2].EN=1;
	tbr_g1[def_tbr_g1_ESP_T2].C_set_time=50;	
	
}

