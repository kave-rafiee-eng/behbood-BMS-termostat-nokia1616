#include "stdint.h"

#ifndef _DEBUGE_W25Q_H_
#define _DEBUGE_W25Q_H_

#define SIZE  256   // Page Size
#define W25Q_WriteEnable       0x06     
#define W25Q_WriteDisable      0x04    
#define W25Q_ReadStatusReg1    0x05     
#define W25Q_ReadStatusReg2    0x35  
#define W25Q_ReadStatusReg3    0x15    
#define W25Q_WriteStatusReg1   0x01  
#define W25Q_WriteStatusReg2   0x31
#define W25Q_WriteStatusReg3   0x11   
#define W25Q_ReadData          0x03    
#define W25Q_FastReadData      0x0B     
#define W25Q_FastReadDual      0x3B     
#define W25Q_PageProgram       0x02     
#define W25Q_BlockErase32      0x52    
#define W25Q_BlockErase64      0xD8     
#define W25Q_SectorErase       0x20     
#define W25Q_ChipErase		  	 0xC7  // 0xC7 || 0x60     
#define W25Q_PowerDown			 0xB9     
#define W25Q_ReleasePowerDown  0xAB     
#define W25Q_ManufactDeviceID	 0x90     
   
		 
#define pin_WP_W25Q GPIO_BSRR_BS_1
#define port_WP_W25Q GPIOA	  
	 
#define pin_HOLD_W25Q GPIO_BSRR_BS_4
#define port_HOLD_W25Q GPIOA	 
	 
#define pin_CS_W25Q GPIO_BSRR_BS_0
#define port_CS_W25Q GPIOA

//--------

#define set_CS_W25Q  port_CS_W25Q->BSRR = pin_CS_W25Q
#define clear_CS_W25Q  port_CS_W25Q->BRR = pin_CS_W25Q

#define set_HOLD_W25Q port_HOLD_W25Q->BSRR = pin_HOLD_W25Q
#define clear_HOLD_W25Q port_HOLD_W25Q->BRR = pin_HOLD_W25Q

#define set_WP_W25Q port_WP_W25Q->BSRR = pin_WP_W25Q
#define clear_WP_W25Q port_WP_W25Q->BRR = pin_WP_W25Q


void W25Q_EraseBlock32KB(unsigned long int address); /* (0.5)Block:128 Page 256B */    
void W25Q_EraseBlock64KB(unsigned long int address); /* Block:256 Page 256B */     
void W25Q_EraseChip(void);
void W25Q_WritePage_start(unsigned long int  NumPage) ;
void W25Q_ReadPage_start(unsigned long int  NumPage) ;


void W25Q_ini();

void W25Q_Disable_Write(void);                         
void W25Q_Enable_Write(void);

void W25Q_WaitBusy(void);
void W25Q_EraseSector4KB(unsigned long int address); /* 16 Page 256B = 4096 */
void W25Q_Read_Manufact_Device_ID();
void W25Q_Read_StatusReg();

void W25Q_ReadPage(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void W25Q_WritePage(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);


#endif