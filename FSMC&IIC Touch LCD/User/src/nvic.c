/**
  ******************************************************************************
  * @file    /User/src/nvic.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    29-May-2022
  * @brief   Nested vectored interrupt controller config program
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312/GBK as encoding.
  * 
  ******************************************************************************
  */ 
  
#include "nvic.h"


void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    #ifdef EN_USART1_RX /* UART异步通信, 串口中断接收数据 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    #endif /* EN_USART1_RX */
}

/******************************** END OF FILE *********************************/
