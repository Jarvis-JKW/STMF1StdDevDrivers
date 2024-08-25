/**
  ******************************************************************************
  * @file    /Hardware/src/buzzer.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    29-Jan-2022
  * @brief   Buzzer program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * To Beep with the buzzer
  * ��Դ������ԭ��ͼ��������ԭ��Elite_STM32F1_V1.4
  * ��Դ������ʹ��PNP��8550������: E-VCC, B-GPIOB.9, C-Buzzer
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "buzzer.h"

/* Private functions ---------------------------------------------------------*/
/* Nokia Tone
tone(SO,150); tone(FA,150); tone(LA_L,300); tone(SI_L,300);
tone(MI,150); tone(RE,150); tone(FA_L,300); tone(SO_L,300);
tone(RE,150); tone(DO,150); tone(MI_L,300); tone(SO_L,300);
tone(DO, 900);
*/

/**
  * @brief  ��Դ��������������
  * @param  �����Ĵ���
  * @retval None
  */
void beep(uint8_t i)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);

    while(i--)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_8);
        delay_ms(60);

        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
        delay_ms(60);
    }
}


/**
  * @brief  ��Դ��������������
  * @param  ������Ƶ��(Hz)��ʱ��(ms)
  * @retval None
  */
void tone(uint16_t freq, uint16_t time)
{
    u32 temp;

    for(temp=time*1e3;temp>0;temp-=1e6/freq)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_9);
        delay_us(5e5/freq);

        GPIO_ResetBits(GPIOB, GPIO_Pin_9);
        delay_us(5e5/freq);
    }
}

/******************************** END OF FILE *********************************/
