/**
  ******************************************************************************
  * @file    /User/src/fsmc.c 
  * @author  Jarvis-JKW
  * @version V0.0.1
  * @date    09-Aug-2022
  * @brief   FSMC config program
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312/GBK as encoding.
  * 
  ******************************************************************************
  */ 

#include "fsmc.h"

void FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef         FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef   FSMC_ReadWriteTimingStructure; 
    FSMC_NORSRAMTimingInitTypeDef   FSMC_WriteTimingStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

    FSMC_ReadWriteTimingStructure.FSMC_AddressSetupTime = 0x01; //2��HCLK 1/36M=27ns
    FSMC_ReadWriteTimingStructure.FSMC_AddressHoldTime = 0x00;  //ģʽAδ�õ�
    FSMC_ReadWriteTimingStructure.FSMC_DataSetupTime = 0x0f;    //16��HCLK��Һ������IC�Ķ����ݵ�ʱ���ٶȲ���̫��
    FSMC_ReadWriteTimingStructure.FSMC_BusTurnAroundDuration = 0x00;
    FSMC_ReadWriteTimingStructure.FSMC_CLKDivision = 0x00;
    FSMC_ReadWriteTimingStructure.FSMC_DataLatency = 0x00;
    FSMC_ReadWriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A;
    
    FSMC_WriteTimingStructure.FSMC_AddressSetupTime = 0x00; //1��HCLK
    FSMC_WriteTimingStructure.FSMC_AddressHoldTime = 0x00;  //ģʽAδ�õ�
    FSMC_WriteTimingStructure.FSMC_DataSetupTime = 0x03;    //4��HCLK
    FSMC_WriteTimingStructure.FSMC_BusTurnAroundDuration = 0x00;
    FSMC_WriteTimingStructure.FSMC_CLKDivision = 0x00;
    FSMC_WriteTimingStructure.FSMC_DataLatency = 0x00;
    FSMC_WriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A;
    
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;                      //ʹ��NE4����ӦBTCR[6],[7]��
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;      //�洢�����ݿ��Ϊ16bit
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;     //�洢��дʹ��
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;         //��дʹ�ò�ͬ��ʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStructure;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingStructure;
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}
/******************************** END OF FILE *********************************/
