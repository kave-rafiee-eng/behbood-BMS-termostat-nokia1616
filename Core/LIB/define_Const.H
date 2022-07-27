#ifndef _DEFINE_CONST_H
#define _DEFINE_CONST_H

#define code_version 11

//-------------------------------------------CPU_TIMER

#define def_num_tbrc_s1 10
#define def_num_tbr_g1 10
#define def_num_tb_g2 10

#define def_tbrc_s1_dark_mode 1

#define def_tbr_g1_DEGUG 1 
#define def_tbr_g1_led_blank 2
#define def_tbr_g1_read_touch 3
#define def_tbr_g1_seting_temp_hum 4

#define def_tb_g2_rx_CLR 1

//-------------------------------------------LAYER
#define def_num_led_layer 1

//-------------------------------------------UART
#define def_time_uart_rx_CLR 100
#define def_num_rx_get 20
#define def_num_tx_send 20

#define SOFT_UART_MAX_BYTE_GET 50


//-------------------------------------------lfs
#define def_num_lfs_ram 1000

//-------------------------------------------w25q
#define addr_start_block_swap 15
#define size_swap_sector4k 25

#define addr_start_block_pic 1
#define size_pic_sector4k 16

#endif

