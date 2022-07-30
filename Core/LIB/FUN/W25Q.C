#include  "main.h"

extern unsigned char ram[256];
extern struct st_W25Q W25Q;

	 
void W25Q_WritePage_start(unsigned long int  NumPage) 
{
   W25Q_Enable_Write();  
	
   clear_CS_W25Q;  
   SPI_w25q(W25Q_PageProgram);         
   SPI_w25q((uint8_t)((NumPage) >> 16));  	
   SPI_w25q((uint8_t)((NumPage) >> 8));
   SPI_w25q((uint8_t)NumPage);	
} 

void W25Q_ReadPage_start(unsigned long int  NumPage) 
{
    clear_CS_W25Q;  
    SPI_w25q(W25Q_ReadData);         
    SPI_w25q((uint8_t)((NumPage) >> 16));  	
    SPI_w25q((uint8_t)((NumPage) >> 8));
    SPI_w25q((uint8_t)NumPage);

}

void W25Q_ini(){
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};	
	/////////////
  GPIO_InitStruct.Pin = pin_CS_W25Q;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT ;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_CS_W25Q, &GPIO_InitStruct);
	/////////////
  GPIO_InitStruct.Pin = pin_HOLD_W25Q;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT ;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_HOLD_W25Q, &GPIO_InitStruct);
	/////////////
  GPIO_InitStruct.Pin = pin_WP_W25Q;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT ;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(port_WP_W25Q, &GPIO_InitStruct);	
	
	set_CS_W25Q;
	set_HOLD_W25Q;
	set_WP_W25Q;
	
}

//-----------------------------------------------------------------------------**********************************
//-----------------------------------------------------------------------------**********************************

void W25Q_Read_Manufact_Device_ID()
{    
	spi_ini(4);
	
	clear_CS_W25Q; 

		SPI_w25q(W25Q_ManufactDeviceID);
		SPI_w25q(0x00);	
		SPI_w25q(0x00);
		SPI_w25q(0x00);
			
		W25Q.ID_Manufacturer = SPI_w25q(0x00);
		W25Q.ID_device = SPI_w25q(0x00);
		
	set_CS_W25Q;
	
}

void W25Q_Read_StatusReg()
{

	clear_CS_W25Q; 
	
		SPI_w25q(W25Q_ReadStatusReg1);
		W25Q.StatusReg1 = SPI_w25q(0);
	
	set_CS_W25Q;
	
	clear_CS_W25Q; 
	
		SPI_w25q(W25Q_ReadStatusReg2);
		W25Q.StatusReg2 = SPI_w25q(0);
	
	set_CS_W25Q;
}  

void W25Q_WaitBusy(void)
{
	 W25Q_Read_StatusReg();
	 while ((W25Q.StatusReg1&0x01))W25Q_Read_StatusReg();
}

void W25Q_EraseSector4KB(unsigned long int address)  
{
   static unsigned char Data1=0,Data2=0,Data3=0;

   address=address*4096;

   Data1= (address>>16);
   Data2= (address>>8);
   Data3= (address);

   W25Q_Enable_Write();  
	 W25Q_WaitBusy(); 
	
   clear_CS_W25Q;  

	 SPI_w25q(W25Q_SectorErase);
	 SPI_w25q(Data1);
	 SPI_w25q(Data2);
	 SPI_w25q(Data3);
	
   set_CS_W25Q;  
	
   W25Q_WaitBusy();         
	
}

void W25Q_ReadPage(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint16_t i;
	
    clear_CS_W25Q;  
	
    SPI_w25q(W25Q_ReadData);         
    SPI_w25q((uint8_t)((ReadAddr) >> 16));  	
    SPI_w25q((uint8_t)((ReadAddr) >> 8));
    SPI_w25q((uint8_t)ReadAddr);
    for (i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = SPI_w25q(0);	
    }
		
   set_CS_W25Q;
}


void W25Q_WritePage(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
   uint16_t i;
	
   W25Q_Enable_Write(); 
	
   clear_CS_W25Q; 
	
   SPI_w25q(W25Q_PageProgram);      
   SPI_w25q((uint8_t)((WriteAddr) >> 16)); 	
   SPI_w25q((uint8_t)((WriteAddr) >> 8));
   SPI_w25q((uint8_t)WriteAddr);
	
   for (i = 0; i < NumByteToWrite; i++)SPI_w25q(pBuffer[i]);
	
   set_CS_W25Q;
	
   W25Q_WaitBusy();

}






void W25Q_EraseChip(void)     
{
	
	W25Q_Enable_Write();
	
	clear_CS_W25Q; 
		SPI_w25q(W25Q_ChipErase);
		SPI_w25q(0x00);	
	set_CS_W25Q;

  W25Q_WaitBusy();                 
}
	
	
void W25Q_EraseBlock64KB(unsigned long int address)       
{
   static unsigned char Data1=0,Data2=0,Data3=0;

   address=address*65536;
   Data1= (address>>16);
   Data2= (address>>8);
   Data3= (address);

   W25Q_Enable_Write();  
   clear_CS_W25Q; 

   SPI_Send_8b(W25Q_BlockErase64,Data1);  
   SPI_Send_8b(Data2,Data3); 	

   set_CS_W25Q; 
   W25Q_WaitBusy();                   
}	
	

void W25Q_EraseBlock32KB(unsigned long int address)     
{
   static unsigned char Data1=0,Data2=0,Data3=0;

   address=address*32768;
   Data1= (address>>16);
   Data2= (address>>8);
   Data3= (address);

   W25Q_Enable_Write(); 
   clear_CS_W25Q;  

	 SPI_Send_8b(W25Q_BlockErase32,Data1);   
	 SPI_Send_8b(Data2,Data3);   
    
   set_CS_W25Q; 
   W25Q_WaitBusy();                  
}




void W25Q_Disable_Write(void)
{
   clear_CS_W25Q;
	
   SPI_w25q(W25Q_WriteDisable); 
	
   set_CS_W25Q;
} 
                           
void W25Q_Enable_Write(void)
{

   clear_CS_W25Q;
	
   SPI_w25q(W25Q_WriteEnable); 
	
   set_CS_W25Q;
	
} 



























