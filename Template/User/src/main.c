/**
  ******************************************************************************
  * @file    /User/src/main.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    29-May-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312/GBK as encoding.
  * 
  * Add standard peripherals library drivers to "StdPeriph_Driver" group
  * and Uncomment corresponding line in 'stm32f10x_conf.h'.
  *
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nvic.h"
#include "usart.h"
#include "led.h"
#include "dht11.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Init_all(void);

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
        LED_Blink(1);
        delay_s(1);
    }
}


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Init program.
  * @retval None
  */
void Init_all(void)
{
	NVIC_Config();

    #ifdef DELAY_WITH_SYSTICK
    Delay_Init();
    #endif /* DELAY_WITH_SYSTICK */

    GPIOx_Init();
    USART1_Init(115200);

}
/******************************** END OF FILE *********************************/
