/**
  ******************************************************************************
  * @file    /User/src/exti.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    2022年1月29日
  * @brief   外部中断初始化，调用前需在外设中先使能对应GPIO时钟
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "exti.h"
#include "rtc.h"
#include "buzzer.h"

/**
  * @brief  EXTI init programs.
  * @note   KEY_UP: 改变所调整时间的单位
  *         KEY0:   时间单位 -
  *         KEY1:   时间单位 +
  */
void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* PA0 KEY UP: 上升沿触发 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;           //中断模式
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStructure);
    
    /* PE3 KEY0: 下降沿触发 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line=EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    /* PE4 KEY1: 下降沿触发 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    EXTI_InitStructure.EXTI_Line=EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
}


/* EXTIx Interruption(s) -----------------------------------------------------*/
/**
  * @brief  The functions handles EXTI0 Interruption, which change RTC clock setting scale.
  */
uint8_t timeScale=1;
void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
    {
        delay_ms(10);   //去抖动
        if(KEY_UP==1)
        {
            if(++timeScale>6)
                timeScale=1;

            beep(timeScale);
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

/**
  * @brief  The functions handles EXTI3 Interruption, which set the RTC clock faster.
  */
void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
    {
        delay_ms(10);
        if(KEY1==0)
        {
            beep(1);
            switch(timeScale)
            {
                case 6:	CAL_Structure.yyyy++;	break;
                case 5: CAL_Structure.MM++;		break;
                case 4: CAL_Structure.dd++;		break;
                case 3: CAL_Structure.HH++;		break;
                case 2: CAL_Structure.mm++;		break;
                case 1: CAL_Structure.ss++;		break;
            }
            RTC_Set(CAL_Structure.yyyy,
                    CAL_Structure.MM,
                    CAL_Structure.dd,
                    CAL_Structure.HH,
                    CAL_Structure.mm,
                    CAL_Structure.ss);
        }
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

/**
  * @brief  The functions handles EXT4 Interruption, which set the RTC clock lower.
  */
void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
    {
        delay_ms(10);
        if(KEY0==0)
        {
            beep(1);
            switch(timeScale)
            {
                case 6:	CAL_Structure.yyyy--;	break;
                case 5: CAL_Structure.MM--;		break;
                case 4: CAL_Structure.dd--;		break;
                case 3: CAL_Structure.HH--;		break;
                case 2: CAL_Structure.mm--;		break;
                case 1: CAL_Structure.ss--;		break;
            }
            RTC_Set(CAL_Structure.yyyy,
                    CAL_Structure.MM,
                    CAL_Structure.dd,
                    CAL_Structure.HH,
                    CAL_Structure.mm,
                    CAL_Structure.ss);
        }
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

/******************************** END OF FILE *********************************/
