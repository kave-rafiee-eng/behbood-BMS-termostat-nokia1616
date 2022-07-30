#include "main.h"

		
#define lcd_temp_x 60
#define lcd_temp_y 45

#define lcd_Humidity_x 60
#define lcd_Humidity_y 96
	
extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
extern struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
extern struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];

extern struct st_bms bms;
extern struct st_touch touch; 


char temp[10];
char temp_dark_mode=0;

void refresh_data(){

		if( bms.dark_mode )put_picture_from_spi_flash(5);
	
		lcd_put_number(lcd_temp_x,lcd_temp_y, bms.TEMP_now, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );
		lcd_put_number(lcd_Humidity_x,lcd_Humidity_y, bms.Humidity_now, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );
	
		lcd_put_number(10,10, bms.config, 1 , LCD_VGA_BLACK , LCD_VGA_WHITE );
		lcd_put_number(30,10, bms.Actuator, 1 , LCD_VGA_BLACK , LCD_VGA_WHITE );
		lcd_put_number(50,10, bms.Sensor, 1 , LCD_VGA_BLACK , LCD_VGA_WHITE );
	
		bms.dark_mode = 0;	
	
}

void refresh_home(){
	
		put_picture_from_spi_flash(7);
		lcd_put_number(lcd_temp_x,lcd_temp_y, bms.TEMP_now, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );
		lcd_put_number(lcd_Humidity_x,lcd_Humidity_y, bms.Humidity_now, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );
	
		lcd_put_number(10,10, bms.config, 1 , LCD_VGA_BLACK , LCD_VGA_WHITE );
		lcd_put_number(30,10, bms.Actuator, 1 , LCD_VGA_BLACK , LCD_VGA_WHITE );
		lcd_put_number(50,10, bms.Sensor, 1 , LCD_VGA_BLACK , LCD_VGA_WHITE );
	
		bms.dark_mode = 0;
		
}
	
void seting_set_point(){
	
	
		if( bms.dark_mode == 0 ){
				if( tbr_g1[def_tbr_g1_read_touch].F_end ){ tbr_g1[def_tbr_g1_read_touch].F_end=0;
							
						read_touch();
					
						if( touch.seting > 0 ){
							
							tbr_g1[def_tbr_g1_seting_temp_hum].EN=1;

							
							if(touch.less_fast || touch.pluse_fast)tbr_g1[def_tbr_g1_seting_temp_hum].C_set_time=100;
							else if(touch.pluse || touch.less )tbr_g1[def_tbr_g1_seting_temp_hum].C_set_time=400; 
							else tbr_g1[def_tbr_g1_seting_temp_hum].EN=0;
							
							if(touch.less_timer==1 || touch.pluse_timer == 1 )tbr_g1[def_tbr_g1_seting_temp_hum].F_end=1;
							
						}
						else{
							
								if( bms.Humidity_now != temp[2] ){ temp[2] = bms.Humidity_now;
									lcd_put_number(lcd_Humidity_x,lcd_Humidity_y, bms.Humidity_now, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );
								}						
								if( bms.TEMP_now != temp[3] ){ temp[3] = bms.TEMP_now;
									lcd_put_number(lcd_temp_x,lcd_temp_y, bms.TEMP_now, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );
								}					
							
						}
						
						if( touch.edge )tbr_g1[def_tbr_g1_seting_temp_hum].F_end=1;
						

				}			
				
				
				if( tbr_g1[def_tbr_g1_seting_temp_hum].F_end ){ tbr_g1[def_tbr_g1_seting_temp_hum].F_end=0;
					
				if( temp[0] != touch.seting){ temp[0] = touch.seting;
					
						if( touch.seting == 1 ){
								lcd_put_number(lcd_temp_x,lcd_temp_y, bms.TEMP_set, 3 , LCD_VGA_RED , LCD_VGA_WHITE );
								lcd_put_number(lcd_Humidity_x,lcd_Humidity_y, bms.Humidity_set, 3 , LCD_VGA_WHITE , LCD_VGA_BLACK );	
						}
						if( touch.seting == 2 ){
								lcd_put_number(lcd_temp_x,lcd_temp_y, bms.TEMP_set, 3 , LCD_VGA_GREEN , LCD_VGA_WHITE );
								lcd_put_number(lcd_Humidity_x,lcd_Humidity_y, bms.Humidity_set, 3 , LCD_VGA_RED , LCD_VGA_WHITE );								
						}						
						else if( touch.seting == 0 ){
							
							temp[0]=0;
							tbr_g1[def_tbr_g1_seting_temp_hum].EN=0;
							refresh_home();
							bms.seting_RUN=1;
							
						}						
				}
				
				if( touch.seting == 1 ){
						if( touch.pluse && bms.TEMP_set < 99)bms.TEMP_set++;
						if( touch.less && bms.TEMP_set > 0 )bms.TEMP_set--;
						lcd_put_number(lcd_temp_x,lcd_temp_y, bms.TEMP_set, 3 , LCD_VGA_RED , LCD_VGA_WHITE );
				}
				else if( touch.seting == 2 ){
						if( touch.pluse && bms.Humidity_set < 99)bms.Humidity_set++;
						if( touch.less && bms.Humidity_set > 0 )bms.Humidity_set--;
						lcd_put_number(lcd_Humidity_x,lcd_Humidity_y, bms.Humidity_set, 3 , LCD_VGA_RED , LCD_VGA_WHITE );
				}	
			
			}		
		}	
	
}

void dark_mode_manage(){
	
		if( tbrc_s1[def_tbrc_s1_dark_mode].F_end ){ tbrc_s1[def_tbrc_s1_dark_mode].F_end=0;
			bms.dark_mode=1;
		}
		
	
		if( bms.dark_mode == 1 ){ tbrc_s1[def_tbrc_s1_dark_mode].I_time=0;
			
				if(temp_dark_mode == 0 )put_picture_from_spi_flash(6);
				temp_dark_mode=1;
			
				if( port_T3->IDR & (0x1<<(pin_T3)) ){ 
						
				}
				else {
						bms.dark_mode = 0; 
						refresh_home();
				}
				
		}
		else temp_dark_mode=0;
	
}

void startup_lcd_picture(){
	
	put_picture_from_spi_flash(6);
	LL_mDelay(2000);
	
	char i;
	for(i=0; i<4; i++){
		put_picture_from_spi_flash(i);
		LL_mDelay(2000);
	}

	
}

void BMS_TERMOSTAT_INI(){
	
	tbr_g1[def_tbr_g1_read_touch].EN=1;
	tbr_g1[def_tbr_g1_read_touch].C_set_time=50;	

	tbrc_s1[def_tbrc_s1_dark_mode].AUTO=1;
	tbrc_s1[def_tbrc_s1_dark_mode].C_set_time=30;
	tbrc_s1[def_tbrc_s1_dark_mode].EN=1;
	
}