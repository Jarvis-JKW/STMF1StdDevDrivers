/**
  ******************************************************************************
  * @file    /Hardware/src/led.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    23-May-2022
  * @brief   LED program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * To light the LEDs(DS0: PB5 , DS1: PE5) on board
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  LED Blink program.
  * @param  None
  * @retval None
  */
void LED_Blink(uint8_t times)
{
    for(times*=2; times>0; times--)
    {
        GPIO_TogglePin(LED0_Port, LED0_Pin);
        delay_ms(100);
    }
    GPIO_SetBits(LED0_Port, LED0_Pin);
}

/******************************** END OF FILE *********************************/
