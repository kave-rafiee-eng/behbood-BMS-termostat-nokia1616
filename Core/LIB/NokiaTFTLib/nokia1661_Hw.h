#ifndef NOKIA1661_HW_H_
#define NOKIA1661_HW_H_

#include  "main.h"

#define LCD_STM32F030_HW		1


#if LCD_STM32F030_HW

#include <string.h>

#define LCD_PORT		GPIOA
#define LCD_GPIO_Enable()	SET_BIT(RCC->AHBENR,RCC_AHBENR_GPIOAEN );

#define LCD_RST				11
#define LCD_CS				10
#define LCD_SDA				9
#define LCD_CLK				8

#define LCD_RSDA()			(LCD_PORT->IDR&(1<<LCD_SDA))
#define SBI(port,bit) 		port->BSRR = (1<<bit)
#define CBI(port,bit) 		port->BRR  = (1<<bit)

#define memcpy_P			memcpy
#define PROGMEM
#define PSTR(x)				(x)
#define pgm_read_byte(x)	*(x)
#define _delay_ms(x)		delay_ms(x) /*Define this Function in External Source*/

#define _rst_set()	SBI(LCD_PORT,LCD_RST)
#define _rst_clr()	CBI(LCD_PORT,LCD_RST)
#define _cs_set()	SBI(LCD_PORT,LCD_CS)
#define _cs_clr()	CBI(LCD_PORT,LCD_CS)
#define _sda_set()	SBI(LCD_PORT,LCD_SDA)
#define _sda_clr()	CBI(LCD_PORT,LCD_SDA)
#define _clk_set()	SBI(LCD_PORT,LCD_CLK)
#define _clk_clr()	CBI(LCD_PORT,LCD_CLK)



#define _rst_HS()	LCD_PORT->OSPEEDR &=~(0x3<<(2*LCD_RST));\
					LCD_PORT->OSPEEDR |= (0x3<<(2*LCD_RST));

#define _cs_HS()	LCD_PORT->OSPEEDR &=~(0x3<<(2*LCD_RST));\
					LCD_PORT->OSPEEDR |= (0x3<<(2*LCD_RST));

#define _sda_HS()	LCD_PORT->OSPEEDR &=~(0x3<<(2*LCD_RST));\
					LCD_PORT->OSPEEDR |= (0x3<<(2*LCD_RST));

#define _clk_HS()	LCD_PORT->OSPEEDR &=~(0x3<<(2*LCD_CLK));\
					LCD_PORT->OSPEEDR |= (0x3<<(2*LCD_CLK));					
					
					

					
					
#define _rst_Out()	LCD_PORT->MODER &=~(0x3<<(2*LCD_RST));\
					LCD_PORT->MODER |= (0x1<<(2*LCD_RST));
					

#define _cs_Out()	LCD_PORT->MODER &=~(0x3<<(2*LCD_CS));\
					LCD_PORT->MODER |= (0x1<<(2*LCD_CS));



#define _sda_Out()	LCD_PORT->MODER &=~(0x3<<(2*LCD_SDA));\
					LCD_PORT->MODER |= (0x1<<(2*LCD_SDA));
					
#define _sda_In()	LCD_PORT->MODER &=~(0x3<<(2*LCD_SDA));\
					LCD_PORT->MODER |= (0x0<<(2*LCD_SDA));


#define _clk_Out()	LCD_PORT->MODER &=~(0x3<<(2*LCD_CLK));\
					LCD_PORT->MODER |= (0x1<<(2*LCD_CLK));


#define _Init_GPIO() { _rst_Out(); _cs_Out(); _sda_Out(); _clk_Out(); _rst_HS(); _cs_HS(); _sda_HS(); _clk_HS();   }

#endif



#endif /* NOKIA1661_HW_H_ */
