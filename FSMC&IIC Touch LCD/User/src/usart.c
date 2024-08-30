/**
  ******************************************************************************
  * @file    /User/src/usart.c
  * @author  Jarvis-JKW
  * @version v0.0.3
  * @date    2022��5��29��
  * @brief   ���ڳ�ʼ����ͨ�ų���
  ******************************************************************************
  */
#include "usart.h"


#ifdef EN_USART1_RX
/*  USART_RX_Data:          ͨ�����ڽ��յ���˫�ֽ�
 *  USART_RX_Data&0x8000:   ������ɱ�־λ
 *  USART_RX_Data&0x4000:   �Ƿ���յ�0x0d
 *  USART_RX_Data&0x3fff:   ��13λΪ���յ�����Ч�ֽ�
 *  USART_RX_Buffer:        ���ݻ����������USART_RX_MAX���ֽ�
*/
uint16_t USART_RX_Data=0;
uint8_t USART_RX_Buffer[USART_RX_MAX];
#endif /* EN_USART1_RX */


/**
  * @brief  ����1��ʼ������
  * @param  �����ʣ�����ֵ115200
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
        temp = USART_ReceiveData(USART1);               //��ȡ���յ�������
        if((USART_RX_Data&0x8000)!=SET)                 //����δ���
        {
            if((USART_RX_Data&0x4000)!=RESET)           //���յ���0x0d
            {
                if(temp!=0x0a)                          //���մ���,���¿�ʼ
                    USART_RX_Data = 0;
                else                                    //���������
                    USART_RX_Data |= 0x8000;
            }
            else                                        //��û�յ�0x0d
            {
                if(temp==0x0d)
                    USART_RX_Data |= 0x4000;
                else
                {
                    USART_RX_Buffer[USART_RX_Data&0x3fff] = temp;
                    USART_RX_Data++;

                    if(USART_RX_Data>(USART_RX_MAX-1))  //���մ���, ���¿�ʼ
                        USART_RX_Data = 0;
                }
            }
        }
    }
}

#endif	/* EN_USART1_RX */
/******************************** END OF FILE *********************************/
