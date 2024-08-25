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
#include "spi.h"
#include "led.h"
#include "lcd.h"


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
    uint8_t i = 0;
    uint16_t colors[] = {LCD_COLOR_BLACK,
                         LCD_COLOR_BLUE,
                         LCD_COLOR_CYAN,
                         LCD_COLOR_GREEN,
                         LCD_COLOR_PINK,
                         LCD_COLOR_RED,
                         LCD_COLOR_WHITE,
                         LCD_COLOR_YELLOW};
    Init_all();
    
    LCD_Putzh(36, 16, "ÄãºÃ", 16, 0);
    LCD_Puts(68, 16, ", ", 16, 0);
    LCD_Putzh(84, 16, "ÊÀ½ç", 16, 0);
    LCD_Puts(116, 16, "! ", 16, 0);
    LCD_Puts(28, 48, "Hello, world!", 16, 0);
    delay_s(2);

    while(1)
    {
        if(i == sizeof(colors)/sizeof(colors[0]))
        {
            i = 0;
        }
        LCD_Clear(colors[i++]);
        GPIO_TogglePin(LED0_Port, LED0_Pin);

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
    GPIO_Config();
    USART1_Config(115200);
    SPI_Config();

    LCD_Init();
    LCD_Clear(LCD_Configuration.bgColor);
    
}
/******************************** END OF FILE *********************************/
