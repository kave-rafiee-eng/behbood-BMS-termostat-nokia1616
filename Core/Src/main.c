#include "main.h"
#include "../LIB/ESP/main_ESP.H"

char read_gpio(GPIO_TypeDef *GPIOx , unsigned int pin){
	
	if( GPIOx ->IDR & (0x1<<(pin)) )return 1;
	else return 0;
	
}

struct st_soft_usart_RX	soft_usart_RX;
struct st_soft_usart_TX	soft_usart_TX;

int gpio[3];
struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];

struct counter c;
struct st_W25Q W25Q;
struct st_programer programer;

struct st_bms bms;
struct st_touch touch; 

int adc[10];

//-----------------------------------------
void hard_ini();
void soft_ini();

unsigned char ram_read[512];
unsigned char ram_write[512];


//------------------------------------------------------------------------------------------------------------

lfs_t lfs;
lfs_file_t file;

static int user_provided_block_device_read(
    const struct lfs_config *lfsc, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
	
	  W25Q_ReadPage((uint8_t *)buffer,(block * lfsc->block_size + off),size);
    return LFS_ERR_OK;
}

static int user_provided_block_device_prog(
    const struct lfs_config *lfsc, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
	
	W25Q_WritePage((uint8_t*)buffer,(block * lfsc->block_size + off),size);
    return LFS_ERR_OK;
}

static int user_provided_block_device_erase(const struct lfs_config *lfsc, lfs_block_t block)
{
	  W25Q_EraseSector4KB(block);
    return LFS_ERR_OK;
}
static int user_provided_block_device_sync(const struct lfs_config *lfsc)
{
    return LFS_ERR_OK;
}

static uint8_t lfs_read_cache_buf[256];
static uint8_t lfs_prog_cache_buf[256];
static uint8_t lfs_lookahead_buf[16];	// 128/8=16

char WriteBuf[def_num_lfs_ram] = {"Hi,Budy! if you get this Message......Congratulations!You have succeeded!!"};
char ReadBuf[def_num_lfs_ram];

const struct lfs_config cfg = {

   	.context = NULL,

    .read  = user_provided_block_device_read, 
    .prog  = user_provided_block_device_prog, 
    .erase = user_provided_block_device_erase,
    .sync  = user_provided_block_device_sync,

    .read_size = 256,
    .prog_size = 256,
    .block_size = 4096,
    .block_count = 512,
	
	.cache_size = 256,
	.block_cycles = 200,
	
	.lookahead_size = 64,
	
	.read_buffer = lfs_read_cache_buf,
	.prog_buffer = lfs_prog_cache_buf,
	.lookahead_buffer = lfs_lookahead_buf,
	
};

//------------------------------------------------------------------------------------------------------------
					

char rx_pin;

int main(void)
{


	hard_ini();
	soft_ini();
	
	startup_lcd_picture();
	BMS_TERMOSTAT_INI();
	
	tbr_g1[def_tbr_g1_led_blank].EN=1;
	tbr_g1[def_tbr_g1_led_blank].C_set_time=1000;

	

  while (1)
  {


		if( tbr_g1[def_tbr_g1_led_blank].F_end ){ tbr_g1[def_tbr_g1_led_blank].F_end=0;

		}
	
		soft_usart_RX.F_data_get = soft_uart_rx_check();

		seting_set_point();
		dark_mode_manage();
		
		debuge_uart();
		
		interupt_soft_uart();
		ESP_main();
		ESP_timer();
		ESP_ini();
		
	}
}






//----------------------------------------------------------------------
//----------------------------------------------------------------------

void soft_ini(){
	
	ini_cpu_timer();
	//soft_spi_ini();	
	nlcdInit();
	
}

void hard_ini(){
	
	clock_ini();
	dma_ini();
	nvic_ini();
	
  HAL_Init();

	gpio_ini();
	
	USART_ini();
	adc_calibre();
	adc_ini();
	tim14_ini();
	
	spi_ini(4);
	
	W25Q_ini();
	
	init_touch_led();
	
	soft_uart_ini();
}



	/*nlcdSetBackgroundColor(LCD_VGA_RED);
	nlcdClear();

	nlcdSetBackgroundColor(LCD_VGA_BLUE);
	nlcdClear();
	
	nlcdSetBackgroundColor(LCD_VGA_WHITE);
	nlcdSetFont(font5x7lat);
	nlcdClear();
	
	nlcdSetOrientation(LCD_ORIENTATION_180);
	//nlcdGotoCharXY(50,50);
	//nlcdStringP(LCD_VGA_BLUE, PSTR("Sisoog.Com"));


	nlcdSetOrientation(LCD_ORIENTATION_90);
	
	
	for(int i=0;i<32;i++)nlcdPixel(64+i,64,LCD_VGA_RED);
		
	put_char(10,10,'2',1);
	put_char(30,30,'2',2);
	put_char(80,80,48,3);
	
	Square(80,80,50,50);*/

	/*
	int err = lfs_mount(&lfs, &cfg);
	if (err)
	{
		lfs_format(&lfs, &cfg);
		lfs_mount(&lfs, &cfg);
	}


	lfs_file_open(&lfs, &file, "my_file", LFS_O_RDWR | LFS_O_CREAT);
	lfs_file_read(&lfs, &file, &ReadBuf, sizeof(ReadBuf));
	lfs_file_close(&lfs, &file);
	lfs_unmount(&lfs);
		
	ReadBuf[0]='*';
	printf("%s",ReadBuf);
	*/
















































void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
