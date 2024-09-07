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
//#include "emo_blink.h"      /* blink_max = 16 */
//#include "emo_speechless.h" /* speech_less_max = 13 */
//#include "emo_sad.h" /* sad_max = 27 */
//#include "emo_angry.h" /* sad_max = 26 */
#include "emo_happy.h" /* happy_max = 31 */

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
    uint8_t i;
    Init_all();
    
    LCD_Putzh(36, 16, "ÄãºÃ", 16, 0);
    LCD_Puts(68, 16, ", ", 16, 0);
    LCD_Putzh(84, 16, "ÊÀ½ç", 16, 0);
    LCD_Puts(116, 16, "! ", 16, 0);
    LCD_Puts(28, 48, "Hello, world!", 16, 0);
    delay_s(2);
    LCD_Fill(0, 0, LCD_Configuration.width, LCD_Configuration.height, LCD_Configuration.bgColor);

    while(1)
    {
        for(i = 0; i < 31; i++)
            LCD_ShowPic(40, 20, 80, 40, EMO_HAPPY[i]);
        delay_ms(1500);
        for(i = 31; i > 0; i--)
            LCD_ShowPic(40, 20, 80, 40, EMO_HAPPY[i-1]);
        delay_s(5);
        GPIO_TogglePin(LED0_Port, LED0_Pin);
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
    LCD_Fill(0, 0, LCD_Configuration.width, LCD_Configuration.height, LCD_Configuration.bgColor);
    
}
/******************************** END OF FILE *********************************/
