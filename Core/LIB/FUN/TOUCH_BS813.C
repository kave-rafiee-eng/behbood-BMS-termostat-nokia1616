#include "TOUCH_BS813.H"
#include "main.h"



extern struct st_soft_usart_TX	soft_usart_TX;
extern struct st_bms bms;

extern struct st_touch touch; 
extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
extern struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
extern struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];


void init_touch_led(void){
	
	SET_BIT(RCC->AHBENR,RCC_AHBENR_GPIOAEN );
	SET_BIT(RCC->AHBENR,RCC_AHBENR_GPIOBEN );
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};	
	
	GPIO_InitStruct.Pin = pin_LED1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_LED1, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = pin_LED2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_LED2, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = pin_LED3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_LED3, &GPIO_InitStruct);
	
	//------------input
	
	
	port_T1->MODER &=~(0x3<<(2*pin_T1));
	port_T1->MODER |= (0x0<<(2*pin_T1));
	
	port_T1->PUPDR &=~(0x3<<(2*pin_T1));
	port_T1->PUPDR |= (0x1<<(2*pin_T1));
	
		
	port_T2->MODER &=~(0x3<<(2*pin_T2));
	port_T2->MODER |= (0x0<<(2*pin_T2));
	
	port_T2->PUPDR &=~(0x3<<(2*pin_T2));
	port_T2->PUPDR |= (0x1<<(2*pin_T2));
	
		
	port_T3->MODER &=~(0x3<<(2*pin_T3));
	port_T3->MODER |= (0x0<<(2*pin_T3));
	
	port_T3->PUPDR &=~(0x3<<(2*pin_T3));
	port_T3->PUPDR |= (0x1<<(2*pin_T3));
	
}

void read_touch(){
		
		touch.REST_TIMER=0;
		while( !(port_T1->IDR & (0x1<<pin_T1)) && !( port_T2->IDR & (0x1<<pin_T2)) ){clear_LED1;clear_LED2;
			touch.REST_TIMER++;
			if( touch.REST_TIMER > 1000 ){	
				
				touch.REST_TIMER=0;
				soft_usart_TX.EN_STDOUT_OUT=1;
				printf("3#");
				soft_usart_TX.EN_STDOUT_OUT=0;	
				bms.config=0;
				refresh_home();
			}
			LL_mDelay(1);
		}
			
		
		if( port_T1->IDR & (0x1<<(pin_T1)) ){ set_LED1;
				touch.pluse=0;	
				touch.pluse_fast=0;
				touch.pluse_timer=0;
		}
		else {clear_LED1;
				touch.pluse_timer++;
				touch.pluse=1;
				if( touch.pluse_timer > 40 ){touch.pluse_timer=40;
					touch.pluse_fast=1;
				}
				tbrc_s1[def_tbrc_s1_dark_mode].I_time=0;
					
		}
	
		if( port_T2->IDR & (0x1<<(pin_T2)) ){ set_LED2;
				touch.less=0;	
				touch.less_fast=0;
				touch.less_timer=0;
		}
		else {clear_LED2;
				touch.less_timer++;
				touch.less=1;
				if( touch.less_timer > 40 ){touch.less_timer=40;
					touch.less_fast=1;
				}
				tbrc_s1[def_tbrc_s1_dark_mode].I_time=0;
		}

		
		if( port_T3->IDR & (0x1<<(pin_T3)) ){ 
				touch.edge=0;			
		}
		else {
			
				if( touch.edge==0 ){  
					touch.edge=1;
					touch.seting++;
					if( touch.seting > 2 ) touch.seting=0;
				}
				tbrc_s1[def_tbrc_s1_dark_mode].I_time=0;
			
		}
		
		if( touch.seting == 0 )set_LED3;
		else clear_LED3;
				

	
}
