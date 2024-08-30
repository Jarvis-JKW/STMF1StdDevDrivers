/**
  ******************************************************************************
  * @file       /User/src/debug.c
  * @author     Jarvis_jkw
  * @version    V0.0.1
  * @date       2022��7��7��
  ******************************************************************************
  * @attention  Ĭ��ʹ��UART�����������Ĵ���ͨ�ţ�����ʹ��MicroLib��
  */
/* Includes ------------------------------------------------------------------*/
#include "debug.h"

/* Retargets the C libaray printf function to the USART ----------------------*/
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(FILE *f)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

#ifndef __MICROLIB
#pragma import(__use_no_semihosting)
/* ����ʹ�ð�����ģʽ */
void _sys_exit(int x)
{ 
    x = x;
}


/* ��׼����Ҫ��֧�ֺ��� */
struct __FILE
{
    int handle; 
};
FILE __stdout;
//FILE __stdin;

#endif /* __MICROLIB */


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  ch: the char to be send.
  * @param  *f:
  * @retval the char that send out.
  */
PUTCHAR_PROTOTYPE
{
    USART_ClearFlag(USART1, USART_FLAG_TC);

    /* Write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);
    
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    return ch;
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  *f
  * @retval the char that received.
  */
/*
GETCHAR_PROTOTYPE
{
}
*/



/******************************** END OF FILE *********************************/
