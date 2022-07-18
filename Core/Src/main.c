#include "main.h"
#include "../LIB/littlefs/lfs.h"
#include "stdio.h"


struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
struct cpu_timer_basic_10bit tb_g2[def_num_tb_g2];
struct cpu_timer_8bit_reset_contorol_Seconds tbrc_s1[def_num_tbrc_s1];

struct counter c;
struct st_W25Q W25Q;
struct st_programer programer;

char str[100]={"kave1380,rafiee"};
uint32_t i=0;
int adc[10];

//-----------------------------------------
void hard_ini();
void soft_ini();

long int test[5];

long int spi_out[5];

unsigned char ram_read[256];
unsigned char ram_write[256];


//------------------------------------------------------------------------------------------------------------
uint16_t DviceID = 0;
int error_code = 0;

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


int main(void)
{
	
	hard_ini();
	soft_ini();
	
	tbr_g1[def_tbr_g1_led_blank].EN=1;
	tbr_g1[def_tbr_g1_led_blank].C_set_time=800;
	
	c.j=1;
	
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
	
  while (1)
  {

		
		if( tbr_g1[def_tbr_g1_led_blank].F_end ){ tbr_g1[def_tbr_g1_led_blank].F_end=0;
			
				
				/*W25Q_Read_Manufact_Device_ID();
				W25Q_Read_StatusReg();
			  
				W25Q_EraseSector4KB(0); 
			
				for(c.i=0;c.i<50;c.i++) ram_write[c.i]=c.i; 
			
				W25Q_WritePage(ram_write,0,50);
				//-----------------------------------				 
				W25Q_ReadPage(ram_read,0,50); */
				
							
				if( c.j==128 )c.j=1;
				else c.j *= 2;
			
				soft_spi_send(c.j);
			
				//LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_15);
		
				adc[9] = read_adc(9);
				adc[8] = read_adc(8);
			
		}
		
		debuge_uart();
		
		program_manager();
		
	}
}






//----------------------------------------------------------------------
//----------------------------------------------------------------------

void soft_ini(){
	
	ini_cpu_timer();
	soft_spi_ini();	
	
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
	
	dac_ini();
	
}


















































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
