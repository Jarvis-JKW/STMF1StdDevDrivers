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

    /* Digital Tube PF0-PF7 */
    GPIO_InitStructure.GPIO_Pin = DT_Pin_A|DT_Pin_B|DT_Pin_C|DT_Pin_D|
                                  DT_Pin_E|DT_Pin_F|DT_Pin_G|DT_Pin_DP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(DT_Port, &GPIO_InitStructure);
    
    /* 74HC573 PF8-PF15 */
    GPIO_InitStructure.GPIO_Pin = CS_Pin_1|CS_Pin_2|CS_Pin_3|CS_Pin_4|
                                  CS_Pin_5|CS_Pin_6|CS_Pin_7|CS_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(CS_Port, &GPIO_InitStructure);
    GPIO_ResetBits(CS_Port, CS_Pin_1|CS_Pin_2|CS_Pin_3|CS_Pin_4|
                            CS_Pin_5|CS_Pin_6|CS_Pin_7|CS_Pin_8);
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
