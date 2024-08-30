/**
  ******************************************************************************
  * @file       /User/src/timer.c 
  * @author     Jarvis-JKW
  * @version    V0.0.3
  * @date       12-Aug-2022
  ******************************************************************************
  * @attention  T_OV(us) = (Autoreload+1) * (Prescaler_Value+1) / f_CLK(MHz)
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "timer.h"


/**
  * @brief  定时器4中断初始化函数
  */
void TIM4_Config(uint16_t Autoreload, uint16_t Prescaler)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
    TIM_TimeBaseInitStructure.TIM_Period = Autoreload;
    TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}


/* TIMx Interruption(s) ------------------------------------------------------*/
#include "mpu6050.h"
#include "oled.h"

void TIM4_IRQHandler(void)   //TIM4中断
{
    char temp[15] = {0};

    if(TIM_GetITStatus(TIM4, TIM_IT_Update)!= RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        Kalman_UpdateData();
        sprintf(temp, "%5.1f", MPU_DataStruct.pitch);
        OLED_Puts(64,16, temp, 16, 1);
        sprintf(temp, "%5.1f", MPU_DataStruct.roll);
        OLED_Puts(64,32, temp, 16, 1);
        sprintf(temp, "%5.1f", MPU_DataStruct.temperature);
        OLED_Puts(64,48, temp, 16, 1);
        OLED_Putzh(112,48, 7, 16, 1);
        OLED_PartialRefresh(64, 0, 128, 64);
    }
}
/******************************** END OF FILE *********************************/
