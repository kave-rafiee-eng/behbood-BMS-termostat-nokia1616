#ifndef __SPI_STM32F030_H
#define __SPI_STM32F030_H

#include "main.h"

uint32_t SPI_w25q(uint8_t d );

void soft_spi_send(uint8_t);
void soft_spi_ini();

void spi_ini(char bit);
uint32_t SPI_Send(uint32_t);	

uint32_t SPI_Send_8b(uint8_t d1 ,  uint8_t d2 );	
uint32_t SPI_Send_4b(uint8_t d1 ,  uint8_t d2 );

#endif