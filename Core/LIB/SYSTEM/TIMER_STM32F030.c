#include "main.h"
#include "TIMER_STM32F030.H"

void tim14_ini(){
	
	SET_BIT(RCC->APB1ENR,RCC_APB1ENR_TIM14EN );
	// TIM14EN: TIM14 timer clock enable
	
  NVIC_SetPriority(TIM14_IRQn, 2);
  NVIC_EnableIRQ(TIM14_IRQn);
		
 	SET_BIT(TIM14->CR1, TIM_CR1_ARPE);
/* ARPE: Auto-reload preload enable
0: TIMx_ARR register is not buffered
1: TIMx_ARR register is buffered*/
	
	TIM14->PSC = 32000;
	//TIM14 prescale
 
	TIM14->ARR= 1500;
	
 	SET_BIT(TIM14->CR1, TIM_CR1_CEN);
/*CEN: Counter enable
0: Counter disabled
1: Counter enabled*/

	SET_BIT(TIM14->DIER, TIM_DIER_UIE);
 /*Bit 0 UIE: Update interrupt enable
0: Update interrupt disabled
1: Update interrupt enabled*/
	
}
