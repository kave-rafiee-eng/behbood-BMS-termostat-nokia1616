#include  "main.h"
#include  "DAC.H"
#include  "../LIB/SYSTEM/SPI_STM32F030.h"

extern struct st_programer programer;
extern struct st_W25Q W25Q;
extern struct st_debuge_out_EN debuge_out_EN;


void dac_ini(){
		
	SET_BIT(RCC->AHBENR,RCC_AHBENR_GPIOFEN );
	
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};	
	
	GPIO_InitStruct.Pin = pin_dac_mr;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_dac_mr, &GPIO_InitStruct);	
	
	GPIO_InitStruct.Pin = pin_dac_put;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_dac_put, &GPIO_InitStruct);	
	
	GPIO_InitStruct.Pin = pin_pam_en ;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_pam_en , &GPIO_InitStruct);

	set_dac_mr;
	set_dac_put;
	set_pam_en;
		
}
	
void dac(){
		
	if( debuge_out_EN.dac ){
		
		programer.I++;
		if(  programer.I > 250 )  { programer.I = 0;
						
				set_CS_W25Q;  
				spi_ini(8);
				programer.P++;		
				W25Q_ReadPage_start(programer.P);
				spi_ini(4);
			
				clear_dac_mr;
				clear_dac_put;
				set_dac_put;
				clear_dac_put;
				set_dac_mr;	
		}
		
		SPI1->DR=0;
		while( READ_BIT(SPI1->SR,SPI_SR_BSY) ){}
			
		set_dac_put;
		clear_dac_put;
			
	}
}

void dac_start(){
	
	programer.I=0;
	programer.P=0;

	W25Q_ReadPage_start(programer.P);

	spi_ini(4);

	clear_dac_mr;
	clear_dac_put;
	set_dac_put;
	clear_dac_put;
	set_dac_mr;	
}
	
	
	
	