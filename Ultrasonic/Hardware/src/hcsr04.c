/**
  ******************************************************************************
  * @file    /Hardware/src/hcsr04.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    22-Jan-2022
  * @brief   HC-SR04超声测距模块
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 使用了TIM7计时，使用前需先初始化并禁用
  ******************************************************************************
  */  

#include "hcsr04.h"

#define SOUNDSPEED      347     //sqrt(k * Rg * T) = sqrt(1.4 * 287 * 300)
#define	HC_SR04_PORT    GPIOE
#define	HC_SR04_CLK     RCC_APB2Periph_GPIOE
#define	TRIG_Pin        GPIO_Pin_1
#define	ECHO_Pin        GPIO_Pin_2

/**
  * @brief  HC-SR04 Init program.
  * @param  None
  * @retval None
  */
void HC_SR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(HC_SR04_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = TRIG_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(HC_SR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HC_SR04_PORT, TRIG_Pin);
    
    GPIO_InitStructure.GPIO_Pin = ECHO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(HC_SR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HC_SR04_PORT, ECHO_Pin);
}

/**
  * @brief  Ultrasonic ranging program.
  * @param  None
  * @retval Distance in centimeters.
  */
float HC_SR04_Range(void)
{
    float temp = 0;
    uint8_t i = 5;

    while(i--)
    {
        while(GPIO_ReadInputDataBit(HC_SR04_PORT, ECHO_Pin) == 1);
        
        GPIO_SetBits(HC_SR04_PORT, TRIG_Pin);
        delay_us(15);
        GPIO_ResetBits(HC_SR04_PORT, TRIG_Pin);
            
        while(GPIO_ReadInputDataBit(HC_SR04_PORT, ECHO_Pin) == 0);
        TIM_SetCounter(TIM7,0);
        TIM_Cmd(TIM7, ENABLE);
        while(GPIO_ReadInputDataBit(HC_SR04_PORT, ECHO_Pin) == 1);
        TIM_Cmd(TIM7, DISABLE);

        delay_ms(60);
        temp += TIM_GetCounter(TIM7) * SOUNDSPEED / 1000000.0 / 2 * 100;
        //                   t[us]   *   v[m/s]   / 1e6[s/us] / 2 * 100[cm/m]
    }
    return temp / (float)i;
}

/******************************** END OF FILE *********************************/
