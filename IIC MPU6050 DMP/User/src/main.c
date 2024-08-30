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
    char temp[15] = {0};

    Init_all();
    OLED_Puts(8, 0, "Pitch :", 16, 1);
    OLED_Puts(16,16, "Roll :", 16, 1);
    OLED_Puts(16,32, " Yaw :", 16, 1);
    OLED_Puts(16,48, "Temp :      C", 16, 1);
    OLED_PartialRefresh(0, 0, 64, 64);
    while(1)
    {
        MPU_GyroUpdate();
        MPU_AccelUpdate();
        MPU_TempUpdate();
        DMP_Update();
        printf("Pitch:%-9.1f Roll:%-9.1f Yaw:%-9.1f\r\n", MPU_DataStruct.pitch, MPU_DataStruct.roll, MPU_DataStruct.yaw);
        sprintf(temp, "%6.1f", MPU_DataStruct.pitch);
        OLED_Puts(64, 0, temp, 16, 1);
        sprintf(temp, "%6.1f", MPU_DataStruct.roll);
        OLED_Puts(64,16, temp, 16, 1);
        sprintf(temp, "%6.1f", MPU_DataStruct.yaw);
        OLED_Puts(64,32, temp, 16, 1);
        sprintf(temp, "%5.1f", MPU_DataStruct.temperature);
        OLED_Puts(64,48, temp, 16, 1);
        OLED_PartialRefresh(64, 0, 128, 64);
    }

}


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Init program.
  * @retval None
  */
void Init_all(void)
{
    uint8_t errCode = 0;
	NVIC_Config();
    #ifdef DELAY_WITH_SYSTICK
    Delay_Init();
    #endif /* DELAY_WITH_SYSTICK */
    GPIO_Config();
    USART1_Config(115200);

    OLED_Init();
    OLED_Puts( 4,16, "Initializing...", 16, 1);
    OLED_Puts(16,32, "Please wait.", 16, 1);
    OLED_PartialRefresh(4, 0, 124, 32);
    MPU6050_Init();
    while((errCode = DMP_Init())!=0)
    {
        printf("DMP Init Error, error code: %d.\r\n", errCode);
        delay_ms(500);
        GPIO_TogglePin(GPIOB, GPIO_Pin_5);
    }
    OLED_Clear();
}
/******************************** END OF FILE *********************************/
