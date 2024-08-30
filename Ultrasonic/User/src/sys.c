/**
  ******************************************************************************
  * @file       /User/src/sys.c
  * @author     Jarvis_jkw
  * @version    V0.0.2
  * @date       2022年2月7日
  ******************************************************************************
  * @attention  默认使用USART1进行与计算机的串口通信，无需使用MicroLib库
  */
/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "usart.h"


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
/* 避免使用半主机模式 */
void _sys_exit(int x)
{ 
    x = x;
}


/* 标准库需要的支持函数 */
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
//GETCHAR_PROTOTYPE
//{
//}


/**
  * @brief  Toggles the specified GPIO pin
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  */
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint32_t odr;

    /* Check the parameters */
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    /* get current Ouput Data Register value */
    odr = GPIOx->ODR;

    /* Set selected pins that were at low level, and reset ones that were high */
    GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
}

/******************************** END OF FILE *********************************/
