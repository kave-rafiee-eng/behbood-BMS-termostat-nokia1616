#include "main.h"
#include "ADC_STM32F030.H"

void adc_calibre(){
	
	CLEAR_BIT(ADC1->CR,ADC_CR_ADCAL );	
	/*ADCAL: ADC calibration
	This bit is set by software to start the calibration of the ADC.
	It is cleared by hardware after calibration is complete.
	0: Calibration complete
	1: Write 1 to calibrate the ADC. Read at 1 means that a calibration is in progress.
	Note: Software is allowed to set ADCAL only*/
	
	while( READ_BIT(ADC1->CR,ADC_CR_ADCAL)){}
	
}

void adc_ini(){
	
	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);
	
  CLEAR_BIT(ADC1->CFGR1,ADC_CFGR1_CONT );
	/*ADC_CFGR1
	CONT: Single / continuous conversion mode
	This bit is set and cleared by software. If it is set, conversion takes place continuously until it is 
	cleared.
	0: Single conversion mode
	1: Continuous conversion mode*/
	
	
	/*ADC_CFGR1
	 RES[1:0]: Data resolution
	These bits are written by software to select the resolution of the conversion.
	00: 12 bits
	01: 10 bits
	10: 8 bits
	11: 6 bits*/

	SET_BIT(ADC->CCR,ADC_CCR_VREFEN );
  /*VREFEN: VREFINT enable
	This bit is set and cleared by software to enable/disable the VREFINT.
	0: VREFINT disabled
	1: VREFINT enabled
	Note: Software is allowed to write this bit only when ADSTART=0 (which ensures that no conversion 
	is ongoing).*/

	SET_BIT(ADC1->CR,ADC_CR_ADEN );
	/*ADEN: ADC enable command
	This bit is set by software to enable the ADC. The ADC will be effectively ready to operate once the 
	ADRDY flag has been set.
	It is cleared by hardware when the ADC is disabled, after the execution of the ADDIS command.
	0: ADC is disabled (OFF state)
	1: Write 1 to enable the ADC*/
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};	
	
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


int read_adc(char ch){
	
	int b=1;
	
	while( ch > 0 ){ ch--;
				b *= 2;
	}
	
	ADC1->CHSELR = b;
	//ADC channel selection register

	SET_BIT(ADC1->CR,ADC_CR_ADSTART );	
	//ADC start conversion command
	
	while( READ_BIT(ADC1->ISR,ADC_ISR_EOC) == 0 ){}
	
	return ADC1->DR;
}