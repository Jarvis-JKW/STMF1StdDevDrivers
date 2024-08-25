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
#include "exti.h"
#include "rtc.h"
#include "lcd1602a.h"

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
    LCD1602A_Clock();
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
    RTC_Config();
    EXTI_Config();

    LCD1602A_Write(LCD1602_CMD, 0x33); //显示模式
    LCD1602A_Write(LCD1602_CMD, 0x32); //4位数据线，0x38表示8位数据线
    LCD1602A_Write(LCD1602_CMD, 0x28); //4位数据初始化，5*7点阵，双行
    LCD1602A_Write(LCD1602_CMD, 0x06); //显示模式为地址加以字符不移动
    LCD1602A_Write(LCD1602_CMD, 0x0c); //开启总显示并不显示光标
    LCD1602A_Write(LCD1602_CMD, 0x01); //清屏
}
/******************************** END OF FILE *********************************/
