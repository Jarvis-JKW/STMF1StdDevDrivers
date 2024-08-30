/**
  ******************************************************************************
  * @file    /User/src/main.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    23-May-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312/GBK as encoding.
  * 
  * Add standard peripherals library drivers to "StdPeriph_Driver" group
  * and Uncomment corresponding line in 'stm32f10x_conf.h' if necessary.
  * 
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include "hcsr04.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Init program.
  */
void Init_all(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    #ifdef DELAY_WITH_SYSTICK
        Delay_Init();
    #endif /* DELAY_WITH_SYSTICK */
    USART1_Init(115200);

    TIM7_Time_Init(0xffff, 71);
    HC_SR04_Init();
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

    Init_all();

    while(1)
    {
        printf("%.2f", HC_SR04_Range());
        delay_ms(500);
    }
}




/******************************** END OF FILE *********************************/
