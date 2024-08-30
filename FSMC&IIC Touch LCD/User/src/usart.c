/**
  ******************************************************************************
  * @file    /User/src/usart.c
  * @author  Jarvis-JKW
  * @version v0.0.3
  * @date    2022年5月29日
  * @brief   串口初始化及通信程序
  ******************************************************************************
  */
#include "usart.h"


#ifdef EN_USART1_RX
/*  USART_RX_Data:          通过串口接收到的双字节
 *  USART_RX_Data&0x8000:   接收完成标志位
 *  USART_RX_Data&0x4000:   是否接收到0x0d
 *  USART_RX_Data&0x3fff:   低13位为接收到的有效字节
 *  USART_RX_Buffer:        数据缓存区，最大USART_RX_MAX个字节
*/
uint16_t USART_RX_Data=0;
uint8_t USART_RX_Buffer[USART_RX_MAX];
#endif /* EN_USART1_RX */


/**
  * @brief  串口1初始化函数
  * @param  波特率，典型值115200
  * @retval None
  */
void USART1_Config(uint32_t baudRate)
{
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    USART_DeInit(USART1);
    USART_InitStructure.USART_BaudRate = baudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    #ifdef EN_USART1_RX
    {
        USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStructure);

        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    }
    #else
    {
        USART_InitStructure.USART_Mode = USART_Mode_Tx;
        
        USART_Init(USART1, &USART_InitStructure);
    }
    #endif /* EN_USART1_RX */

    USART_Cmd(USART1, ENABLE);
//    printf("Hello, world!\r\n");
}


/* U(S)ARTx Interruption(s) --------------------------------------------------*/
#ifdef EN_USART1_RX
/**
  * @brief  This function handles USART1 Interruption, which communicate with the upper computer.
  * @note   The data received are required to end with CR('\r', 0x0d) & LF('\n', 0x0a)
  */
void USART1_IRQHandler(void)
{
    uint8_t temp;

    if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET)
    {
        temp = USART_ReceiveData(USART1);               //读取接收到的数据
        if((USART_RX_Data&0x8000)!=SET)                 //接收未完成
        {
            if((USART_RX_Data&0x4000)!=RESET)           //接收到了0x0d
            {
                if(temp!=0x0a)                          //接收错误,重新开始
                    USART_RX_Data = 0;
                else                                    //接收完成了
                    USART_RX_Data |= 0x8000;
            }
            else                                        //还没收到0x0d
            {
                if(temp==0x0d)
                    USART_RX_Data |= 0x4000;
                else
                {
                    USART_RX_Buffer[USART_RX_Data&0x3fff] = temp;
                    USART_RX_Data++;

                    if(USART_RX_Data>(USART_RX_MAX-1))  //接收错误, 重新开始
                        USART_RX_Data = 0;
                }
            }
        }
    }
}

#endif	/* EN_USART1_RX */
/******************************** END OF FILE *********************************/
