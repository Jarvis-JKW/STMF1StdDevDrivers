/**
  ******************************************************************************
  * @file       /User/src/timer.c 
  * @author     Jarvis-JKW
  * @version    V0.0.3
  * @date       2022年5月23日
  ******************************************************************************
  * @attention  T_OV(us) = (Autoreload+1) * (Prescaler_Value+1) / f_CLK(MHz)
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "timer.h"


/**
  * @brief  定时器7初始化函数
  * @note	HC-SR04超声波测距
  */
void TIM7_Time_Init(uint16_t Autoreload, uint16_t Prescaler)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    
    //定时器初始化
    TIM_TimeBaseInitStructure.TIM_Period = Autoreload;
    TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
    
    TIM_Cmd(TIM7, DISABLE);
}


/* TIMx Interruption(s) ------------------------------------------------------*/
/******************************** END OF FILE *********************************/
