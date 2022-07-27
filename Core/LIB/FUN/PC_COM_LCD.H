#ifndef _DEBUGE_UART_H_
#define _DEBUGE_UART_H_

#include "../define_Const.h"

char usart_comp_str( char str_comp[def_num_rx_get] );
void usart_send_str_int( char str_send[def_num_tx_send-5] , int var );
void uart_manager_interupt_rx();
void uart_manager_interupt_tx();
void debuge_uart();
void clr_str_tx();
void clr_str_rx();
void ini_debuge();
void program_manager();
char help();

#endif
