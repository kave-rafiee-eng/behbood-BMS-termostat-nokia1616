#include "main.h"
#include "stm32f0xx_it.h"


void NMI_Handler(void)
{

  while (1)
  {
  }

}


void HardFault_Handler(void)
{

 /* while (1)
  {
		
		

  }*/
	
	printf("HardFault_Handler\n");
	
}


void SVC_Handler(void)
{

}


void PendSV_Handler(void)
{

}


void SysTick_Handler(void)
{

  HAL_IncTick();
	timer_basic_manager();
	
}




volatile int tim14;
void TIM14_IRQHandler(void){
	
	//tim14++;	
	CLEAR_BIT(TIM14->SR,TIM_SR_UIF );
	timer_second_manager();

}


void DMA1_Channel2_3_IRQHandler(void)
{

  //HAL_DMA_IRQHandler(&hdma_usart1_tx);

}

volatile char data_rx;

void USART1_IRQHandler(void)
{

 // HAL_UART_IRQHandler(&huart1);
	
	if( READ_BIT(USART1->ISR,USART_ISR_TC ) ){
	
			//uart_manager_interupt_tx();
			SET_BIT(USART1->ICR,USART_ICR_TCCF );
			/*TCCF: Transmission complete clear flag
			Writing 1 to this bit clears the TC flag in the USARTx_ISR register		*/
						
	}
/*TC: Transmission complete
This bit is set by hardware if the transmission of a frame containing data is complete and if 
TXE is set. An interrupt is generated if TCIE=1 in the USARTx_CR1 register. It is cleared by 
software, writing 1 to the TCCF in the USARTx_ICR register or by a write to the 
USARTx_TDR register.
An interrupt is generated if TCIE=1 in the USARTx_CR1 register. 
0: Transmission is not complete
1: Transmission is complete*/

	
	if( READ_BIT(USART1->ISR,USART_ISR_RXNE ) ){

	  uart_manager_interupt_rx();		
		data_rx = USART1->RDR;	
		//USART1->TDR = data_rx;
		
	}
/* RXNE: Read data register not empty
This bit is set by hardware when the content of the RDR shift register has been transferred 
to the USARTx_RDR register. It is cleared by a read to the USARTx_RDR register. The 
RXNE flag can also be cleared by writing 1 to the RXFRQ in the USARTx_RQR register. 
An interrupt is generated if RXNEIE=1 in the USARTx_CR1 register.
0: data is not received
1: Received data is ready to be read*/

}
