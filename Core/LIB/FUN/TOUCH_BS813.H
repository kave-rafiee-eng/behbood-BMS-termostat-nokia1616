#ifndef _TOUCH_BS813_H
#define _TOUCH_BS813_H

#define pin_T3 3
#define port_T3 GPIOB

#define pin_T2 15
#define port_T2 GPIOA

#define pin_T1 4
#define port_T1 GPIOB

//--------

#define pin_LED1 GPIO_BSRR_BS_5
#define port_LED1 GPIOB

#define pin_LED2 GPIO_BSRR_BS_7
#define port_LED2 GPIOB

#define pin_LED3 GPIO_BSRR_BS_6
#define port_LED3 GPIOB

//--------

#define set_LED1  port_LED1->BSRR = pin_LED1
#define clear_LED1  port_LED1->BRR = pin_LED1

#define set_LED2  port_LED2->BSRR = pin_LED2
#define clear_LED2  port_LED2->BRR = pin_LED2

#define set_LED3  port_LED3->BSRR = pin_LED3
#define clear_LED3  port_LED3->BRR = pin_LED3

	void init_touch_led();
	void read_touch();

#endif