
#define USE_FULL_LL_DRIVER 1

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------

#include "stm32f0xx_ll_i2c.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_gpio.h"


#include "../LIB/define_Const.h"
#include "../LIB/my_struct.h"
#include "../LIB/SYSTEM/USART_STM32F030.h"
#include "../LIB/SYSTEM/ADC_STM32F030.h"
#include "../LIB/SYSTEM/CORTEX_STM32F030.h"
#include "../LIB/SYSTEM/TIMER_STM32F030.h"
#include "../LIB/SYSTEM/GPIO_STM32F030.h"
#include "../LIB/SYSTEM/SPI_STM32F030.h"
#include "../LIB/FUN/CPU_TIMER.h"
#include "../LIB/FUN/PC_COM.h"
#include "../LIB/FUN/W25Q.h"
#include "../LIB/FUN/TOUCH_BS813.H"
#include "../LIB/FUN/LCD_NOKIA1616_MY_FUN.H"

#include "../LIB/FUN/BMS_TERMOSTAT.H"



#include "stdio.h"
#include "stdlib.h"


#include "../LIB/littlefs/lfs.h"


#include "../LIB/NokiaTFTLib/nokia1661_lcd_driver.h"
#include "../LIB/NokiaTFTLib/spfd54124b.h"

#define SBI(port,bit) 		port->BSRR = (1<<bit)
#define CBI(port,bit) 		port->BRR  = (1<<bit)

char read_gpio(GPIO_TypeDef *GPIOx , unsigned int pin);

void Error_Handler(void);

//void printf(char ad_str[]);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

