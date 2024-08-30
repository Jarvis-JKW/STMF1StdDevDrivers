/**
  ******************************************************************************
  * @file    /User/src/usart.c
  * @author  Jarvis-JKW
  * @version v0.0.2
  * @date    2022��2��6��
  * @brief   ���ڳ�ʼ����ͨ�ų���
  ******************************************************************************
  */
#include "usart.h"

#ifdef EN_USART1_RX
/*  USART_RX_Data:          ͨ�����ڽ��յ���˫�ֽ�
 *  USART_RX_Data&0x8000:   ������ɱ�־λ
 *  USART_RX_Data&0x4000:   �Ƿ���յ�0x0d
 *  USART_RX_Data&0x3fff:   ��13λΪ���յ�����Ч�ֽ�
 *  USART_RX_Buffer:        ���ݻ����������USART_REC_LEN���ֽ�
*/
uint16_t USART_RX_Data=0;
uint8_t USART_RX_Buffer[USART_RX_MAX];
#endif /* EN_USART1_RX */

/**
  * @brief  ����1ͨ���ض���printf�����봮������ͨ��
  * @param  �����ʣ�����ֵ115200
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

        //USART1_RX	  GPIOA.10��ʼ��
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
        USART_InitStructure.USART_BaudRate = baudRate;              //���ڲ�����
        USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
        USART_InitStructure.USART_StopBits = USART_StopBits_1;      //һ��ֹͣλ
        USART_InitStructure.USART_Parity = USART_Parity_No;         //����żУ��λ
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
        USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; //�շ�ģʽ
        USART_Init(USART1, &USART_InitStructure);

        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);              //ʹ�ܴ���1�жϽ���
    }
    #else
    {
        USART_DeInit(USART1);
        USART_InitStructure.USART_BaudRate = baudRate;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Tx;             //������
        
        USART_Init(USART1, &USART_InitStructure);
    }
    #endif /* EN_USART1_RX */

    USART_Cmd(USART1, ENABLE);

    printf("Hello, world!\r\n");
}

/**
  * @brief  ���ڵ������ִ�ӡ���͵��ַ���
  *	@param	�˳����մ������ݵ�ʱ��
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
                PBout(5) = ~PBout(5);//DS0��˸��ʾ������������
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

                    if(USART_RX_Data>(USART_RX_MAX-1))  //���մ���,���¿�ʼ
                        USART_RX_Data = 0;
                }
            }
        }
    }
}

#endif	/* EN_USART1_RX */
/******************************** END OF FILE *********************************/
