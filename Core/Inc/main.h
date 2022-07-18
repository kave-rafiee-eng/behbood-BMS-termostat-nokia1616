
#define USE_FULL_LL_DRIVER 1

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

//#define LED GPIO_BSRR_BS_15

#define def_num_lfs_ram 1000

#define pin_dac_put GPIO_BSRR_BS_0
#define port_dac_put GPIOF

#define pin_dac_mr GPIO_BSRR_BS_1
#define port_dac_mr GPIOF

#define pin_pam_en GPIO_BSRR_BS_6
#define port_pam_en GPIOB


#define set_dac_put  port_dac_put->BSRR = pin_dac_put
#define clear_dac_put  port_dac_put->BRR = pin_dac_put

#define set_dac_mr  port_dac_mr->BSRR = pin_dac_mr
#define clear_dac_mr  port_dac_mr->BRR = pin_dac_mr

#define set_pam_en  port_pam_en->BSRR = pin_pam_en
#define clear_pam_en  port_pam_en->BRR = pin_pam_en


//---------------------------------------
#define pin_sh_do GPIO_BSRR_BS_15
#define port_sh_do GPIOA

#define pin_sh_put GPIO_BSRR_BS_3
#define port_sh_put GPIOB

#define pin_sh_clk GPIO_BSRR_BS_4
#define port_sh_clk GPIOB

#define pin_sh_mr GPIO_BSRR_BS_5
#define port_sh_mr GPIOB


#define set_sh_do  port_sh_do->BSRR = pin_sh_do
#define clear_sh_do  port_sh_do->BRR = pin_sh_do

#define set_sh_put  port_sh_put->BSRR = pin_sh_put
#define clear_sh_put  port_sh_put->BRR = pin_sh_put

#define set_sh_clk  port_sh_clk->BSRR = pin_sh_clk
#define clear_sh_clk  port_sh_clk->BRR = pin_sh_clk

#define set_sh_mr  port_sh_mr->BSRR = pin_sh_mr
#define clear_sh_mr  port_sh_mr->BRR = pin_sh_mr

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

#include "../LIB/CODE/DAC.H"


void Error_Handler(void);

//void printf(char ad_str[]);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

