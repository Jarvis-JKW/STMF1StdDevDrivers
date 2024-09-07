/**
  ******************************************************************************
  * @file    /User/src/spi.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    1-Feb-2022
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 测试芯片为W25Q128，使用SPI协议进行读写或擦除操作
  ******************************************************************************
  */

#include "spi.h"
/**
  * @brief  SPI init program.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
    SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

/**
  * @brief  SPI1 send byte program.
  * @param  0~255
  * @retval None
  */
void SPI_SendByte(SPI_TypeDef* SPIx, uint8_t data)
{
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPIx, data);
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
}


/******************************** END OF FILE *********************************/
