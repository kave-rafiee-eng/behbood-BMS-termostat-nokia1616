#include "main.h"
#include "USART_STM32F030.H"

void USART_ini(){

	CLEAR_BIT(USART1->CR1,USART_CR1_UE );	
	
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_USART1EN );	
	
	SET_BIT(USART1->CR3,USART_CR3_DMAT );		
 /*DMAT: DMA enable transmitter
This bit is set/reset by software
1: DMA mode is enabled for transmission
0: DMA mode is disabled for transmission*/

	CLEAR_BIT(USART1->CR1,USART_CR1_OVER8 );
	/*OVER8: Oversampling mode
0: Oversampling by 16
1: Oversampling by 8
This bit can only be written when the USART is disabled (UE=0).
*/

	SET_BIT(USART1->CR1,USART_CR1_TE );	
/*TE: Transmitter enable
This bit enables the transmitter. It is set and cleared by software.
0: Transmitter is disabled
1: Transmitter is enabled
During transmission, a �0� pulse on the TE bit (�0� followed by �1�) sends a preamble
(idle line) after the current word. In order to generate an idle character, the TE must not
be immediately written to 1.
*/

	SET_BIT(USART1->CR1,USART_CR1_RE );	
/*RE: Receiver enable
This bit enables the receiver. It is set and cleared by software. 
0: Receiver is disabled
1: Receiver is enabled and begins searching for a start bit*/
	
	USART1->BRR = 1250;
/*SET_BIT(USART1->CR1,USART_CR3_BRR0 );	
Bits 15:4 BRR[15:4]
BRR[15:4] = USARTDIV[15:4]
Bits 3:0 BRR[3:0]
When OVER8 = 0, BRR[3:0] = USARTDIV[3:0].
When OVER8 = 1:
BRR[2:0] = USARTDIV[3:0] shifted 1 bit to the right.
BRR[3] must be kept cleared.*/
//D0 - 38400


	SET_BIT(USART1->CR1,USART_CR1_UE );	
/*UE: USART enable
When this bit is cleared, the USART prescalers and outputs are stopped immediately, and
current operations are discarded. The configuration of the USART is kept, but all the status flags, in the USARTx_ISR are set to their default values. This bit is set and cleared by
software.
0: USART prescaler and outputs disabled, low-power mode
1: USART enabled*/


	SET_BIT(USART1->CR1,USART_CR1_TCIE );	
/*TCIE: Transmission complete interrupt enable
This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever TC=1 in the USARTx_ISR register
Bit 5 RXNEIE: RXNE interrupt enable
This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USARTx_ISR 
register*/

	SET_BIT(USART1->CR1,USART_CR1_RXNEIE );	
/*RXNEIE: RXNE interrupt enable
This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USARTx_ISR 
register*/

	
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};	
	/////////////
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
	/////////////	
	
}



void uart_tx_dma(char n_s , uint32_t ad_p , uint32_t ad_m ){

	CLEAR_BIT(DMA1_Channel2->CCR,DMA_CCR_EN );

	SET_BIT(DMA1_Channel2->CCR,DMA_CCR_MINC );
	/*MINC: Memory increment mode
	This bit is set and cleared by software.
	0: Memory increment mode disabled
	1: Memory increment mode enabled */

	CLEAR_BIT(DMA1_Channel2->CCR,DMA_CCR_CIRC );
	/*CIRC: Circular mode
	This bit is set and cleared by software.
	0: Circular mode disabled
	1: Circular mode enabled*/

	SET_BIT(DMA1_Channel2->CCR,DMA_CCR_DIR );	
	/*DIR: Data transfer direction
	This bit is set and cleared by software.
	0: Read from peripheral
	1: Read from memory*/
	
	/*DMA1_Channel2->CNDTR = 5;
	DMA1_Channel2->CPAR = (uint32_t) &USART1->TDR;
	DMA1_Channel2->CMAR = (uint32_t) &str;*/
		
	DMA1_Channel2->CNDTR = n_s;
	DMA1_Channel2->CPAR =  ad_p;
	DMA1_Channel2->CMAR =  ad_m;
	
	SET_BIT(DMA1_Channel2->CCR,DMA_CCR_EN );	
	/*EN: Channel enable
	This bit is set and cleared by software.
	0: Channel disabled
	1: Channel enabled*/
		
}

