/**
  ******************************************************************************
  * @file    /User/src/gpio.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    29-May-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312/GBK as encoding.
  *
  ******************************************************************************
  */

#include "gpio.h"

/**
  * @brief  Init the specified GPIO pin
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                          |RCC_APB2Periph_GPIOB
                          |RCC_APB2Periph_GPIOE
                          |RCC_APB2Periph_GPIOF, ENABLE);
    /* USART1_TX PA9 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART1_RX PA10 */
    #ifdef EN_USART1_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    #endif /* EN_USART1_RX */

    /* Buzzer PB8 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
    
    /* Button PE3, PE4 EXTI3, EXTI4 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    /* Button PA0 EXTI0 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* LCD1602A PF0-2 PF4-7 */
    GPIO_InitStructure.GPIO_Pin = LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin|LCD_DATA_Pins;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_Port, &GPIO_InitStructure);
}


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
