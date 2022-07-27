#ifndef __USART_STM32F030_H
#define __USART_STM32F030_H


#include "main.h"

void USART_ini();
void uart_tx_dma(char n_s , uint32_t ad_p , uint32_t ad_m );

void soft_uart_ini();
void soft_uart_send_byte(unsigned char data);
unsigned char  soft_uart_rx_check();
unsigned char  soft_uart_get_byte();
void soft_uart_rx_str_clear();
unsigned char  maneager_get_soft_uart_STR();

#endif