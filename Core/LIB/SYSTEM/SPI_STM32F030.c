#include "main.h"
#include "../LIB/SYSTEM/SPI_STM32F030.h"


uint32_t SPI_w25q( uint8_t d ){
	
		uint8_t a,b;
	
		b = d & 0x0f;
		a = d >> 4;
	
		uint32_t d_f;
	
		d_f = b;
		d_f <<= 8;
		d_f |= a;
	
		SPI1->DR = d_f;
	
	while( READ_BIT(SPI1->SR,SPI_SR_BSY) ){}
/*SPIx_SR	
	 BSY: Busy flag
0: SPI not busy
1: SPI is busy in communication or Tx buffer is not empty
This flag is set and cleared by hardware*/
	
	if( READ_BIT(SPI1->SR,SPI_SR_RXNE) )
/*RXNE: Receive buffer not empty
0: Rx buffer empty
1: Rx buffer not empty*/		
		
	d_f = SPI1->DR;
	
	a = d_f & 0x0f;
	b = d_f >> 8;
	
	d_f=0;
	
	d_f = a << 4;
	d_f |= b;
	return d_f;
	
		
}

uint32_t SPI_Send_4b(uint8_t d1 ,  uint8_t d2 ){
	
		uint32_t d_f;
	
		d_f = d2;
		d_f <<= 8;
		d_f |= d1;
	
		SPI1->DR = d_f;
	
	while( READ_BIT(SPI1->SR,SPI_SR_BSY) ){}
/*SPIx_SR	
	 BSY: Busy flag
0: SPI not busy
1: SPI is busy in communication or Tx buffer is not empty
This flag is set and cleared by hardware*/
	
	if( READ_BIT(SPI1->SR,SPI_SR_RXNE) )return SPI1->DR;
/*RXNE: Receive buffer not empty
0: Rx buffer empty
1: Rx buffer not empty*/		
		
}

uint32_t SPI_Send_8b(uint8_t d1 ,  uint8_t d2 ){
	
		uint32_t d_f;
	
		d_f = d2;
		d_f <<= 8;
		d_f |= d1;
	
		SPI1->DR = d_f;
	
	while( READ_BIT(SPI1->SR,SPI_SR_BSY) ){}
/*SPIx_SR	
	 BSY: Busy flag
0: SPI not busy
1: SPI is busy in communication or Tx buffer is not empty
This flag is set and cleared by hardware*/
	
	if( READ_BIT(SPI1->SR,SPI_SR_RXNE) )return SPI1->DR;
/*RXNE: Receive buffer not empty
0: Rx buffer empty
1: Rx buffer not empty*/		
		
}

uint32_t SPI_Send( uint32_t d ){

	SPI1->DR = d;
	
	while( READ_BIT(SPI1->SR,SPI_SR_BSY) ){}
		
/*SPIx_SR	
	 BSY: Busy flag
0: SPI not busy
1: SPI is busy in communication or Tx buffer is not empty
This flag is set and cleared by hardware*/
	
	if( READ_BIT(SPI1->SR,SPI_SR_RXNE) ){
		
			return SPI1->DR;
	}
/*RXNE: Receive buffer not empty
0: Rx buffer empty
1: Rx buffer not empty*/
	
}
//------------------------------------------------------------------------
void soft_spi_send( uint8_t d){

		uint8_t l_i;
	
		clear_sh_mr;
		clear_sh_put;
		set_sh_put;
		clear_sh_put;
		set_sh_mr;
	
		for(l_i=128; l_i>1; l_i/=2 ){
			clear_sh_clk;
				if( d & l_i  )set_sh_do;
				else clear_sh_do;
			set_sh_clk;	
		}		
		
		clear_sh_put;
		set_sh_put;
		clear_sh_put;		
		
}
//------------------------------------------------------------------------
void spi_ini(char bit){
	
	uint32_t sh;

	
	CLEAR_BIT(SPI1->CR1,SPI_CR1_SPE);
	
	sh=1;
	sh <<= 3;	
	SPI1->CR1=sh;
	/* BR[2:0]: Baud rate control
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256*/	

	if( bit == 8 )sh = 7;
		else if( bit == 4 )sh = 3;
	
	sh <<= 8;
	SPI1->CR2=sh;
/*8 DS [3:0]: Data size
These bits configure the data length for SPI transfers:
0000: Not used
0001: Not used
0010: Not used
0011: 4-bit
0100: 5-bit
0101: 6-bit
0110: 7-bit
0111: 8-bit
1000: 9-bit*/
	
	
	//SET_BIT(SPI1->CR1,SPI_CR1_BIDIMODE);
	//CLEAR_BIT(SPI1->CR1,SPI_CR1_BIDIOE);
	
	SET_BIT(SPI1->CR2,SPI_CR2_SSOE);

	//SET_BIT(SPI1->CR1,SPI_CR1_LSBFIRST);
	
/* NSSP: NSS pulse management
This bit is used in master mode only. it allow the SPI to generate an NSS pulse between two 
consecutive data when doing continuous transfers. In the case of a single data transfer, it 
forces the NSS pin high level after the transfer. 
It has no meaning if CPHA = ’1’, or FRF = ’1’.
0: No NSS pulse
1: NSS pulse generated*/	

	//SET_BIT(SPI1->CR1,SPI_CR1_RXONLY);
	
	SET_BIT(SPI1->CR1,SPI_CR1_MSTR);
	/* MSTR: Master selection
0: Slave configuration
1: Master configuration*/

	SET_BIT(SPI1->CR1,SPI_CR1_SPE);
	/* SPE: SPI enable
0: Peripheral disabled
1: Peripheral enabled*/
	

}
//------------------------------------------------------------------------
void soft_spi_ini(){
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};	
	
	GPIO_InitStruct.Pin = pin_sh_do;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_sh_do, &GPIO_InitStruct);
		
	GPIO_InitStruct.Pin = pin_sh_put;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_sh_put, &GPIO_InitStruct);
		
	GPIO_InitStruct.Pin = pin_sh_clk;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_sh_clk, &GPIO_InitStruct);
		
	GPIO_InitStruct.Pin = pin_sh_mr;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_sh_mr, &GPIO_InitStruct);	
}