/**
  ******************************************************************************
  * @file    /User/src/usart.c
  * @author  Jarvis-JKW
  * @version v0.0.2
  * @date    2022年2月6日
  * @brief   串口初始化及通信程序
  ******************************************************************************
  */
#include "usart.h"

#ifdef EN_USART1_RX
/*  USART_RX_Data:          通过串口接收到的双字节
 *  USART_RX_Data&0x8000:   接收完成标志位
 *  USART_RX_Data&0x4000:   是否接收到0x0d
 *  USART_RX_Data&0x3fff:   低13位为接收到的有效字节
 *  USART_RX_Buffer:        数据缓存区，最大USART_REC_LEN个字节
*/
uint16_t USART_RX_Data=0;
uint8_t USART_RX_Buffer[USART_RX_MAX];
#endif /* EN_USART1_RX */

/**
  * @brief  串口1通过重定向printf用于与串口助手通信
  * @param  波特率，典型值115200
  * @retval None
  */
void USART1_Init(uint32_t baudRate)
{
    GPIO_InitTypeDef 	GPIO_InitStructure;
    USART_InitTypeDef	USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1
                          |RCC_APB2Periph_GPIOA, ENABLE);
  
    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    #ifdef EN_USART1_RX
    {
        NVIC_InitTypeDef NVIC_InitStructure;

        //USART1_RX	  GPIOA.10初始化
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        USART_DeInit(USART1);
        USART_InitStructure.USART_BaudRate = baudRate;              //串口波特率
        USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位数据格式
        USART_InitStructure.USART_StopBits = USART_StopBits_1;      //一个停止位
        USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验位
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
        USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; //收发模式
        USART_Init(USART1, &USART_InitStructure);

        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);              //使能串口1中断接收
    }
    #else
    {
        USART_DeInit(USART1);
        USART_InitStructure.USART_BaudRate = baudRate;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Tx;             //仅发送
        
        USART_Init(USART1, &USART_InitStructure);
    }
    #endif /* EN_USART1_RX */

    USART_Cmd(USART1, ENABLE);

    printf("Hello, world!\r\n");
}

/**
  * @brief  串口调试助手打印发送的字符串
  *	@param	退出接收串口数据的时间
  */
void COM_SendString(uint8_t sec)
{
    uint8_t i, len;
    uint16_t time = 0;

    printf("STM32F10x USART Communication Test\r\n");
    printf("The program will end in %d seconds.\r\n", sec);

    while(time<(sec*100))
    {
        if(USART_RX_Data&0x8000)
        {
            len = USART_RX_Data&0x3f;
            printf("\rCopy: ");

            for(i = 0; i < len; i++)
            {
                USART_SendData(USART1, USART_RX_Buffer[i]);
                while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!= SET);
            }
            
            printf("\r\n");
            USART_RX_Data = 0;
        }
        else
        {
            time++;
            if(time%50==0)
                PBout(5) = ~PBout(5);//DS0闪烁表示程序正在运行
            delay_ms(10);
        }
    }
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

                    if(USART_RX_Data>(USART_RX_MAX-1))  //接收错误,重新开始
                        USART_RX_Data = 0;
                }
            }
        }
    }
}

#endif	/* EN_USART1_RX */
/******************************** END OF FILE *********************************/
