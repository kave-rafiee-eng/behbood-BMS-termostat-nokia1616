#ifndef __USART_STM32F030_H
#define __USART_STM32F030_H

#include "main.h"

void USART_ini();
void uart_tx_dma(char n_s , uint32_t ad_p , uint32_t ad_m );

#endif