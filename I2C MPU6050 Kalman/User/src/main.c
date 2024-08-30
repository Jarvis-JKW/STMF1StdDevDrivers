/**
  ******************************************************************************
  * @file    /User/src/main.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    12-Aug-2022
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
#include "timer.h"
#include "iic.h"
#include "led.h"
#include "oled.h"
#include "mpu6050.h"

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
        printf("Pitch:%-9.1f Roll:%-9.1f\r\n", MPU_DataStruct.pitch, MPU_DataStruct.roll);
        GPIO_TogglePin(LED0_Port, LED0_Pin);
        delay_ms(1000);
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
    GPIO_Config();
    USART1_Config(115200);
    I2C_Config();
    OLED_Init();
    MPU6050_Init();
    OLED_Putzh( 8,16, 0, 16, 1);
    OLED_Putzh(24,16, 1, 16, 1);
    OLED_Putzh(40,16, 4, 16, 1);
    OLED_Putzh( 8,32, 2, 16, 1);
    OLED_Putzh(24,32, 3, 16, 1);
    OLED_Putzh(40,32, 4, 16, 1);
    OLED_Putzh( 8,48, 5, 16, 1);
    OLED_Putzh(40,48, 6, 16, 1);
    OLED_Refresh();
    TIM4_Config(199, 7199);
}
/******************************** END OF FILE *********************************/
