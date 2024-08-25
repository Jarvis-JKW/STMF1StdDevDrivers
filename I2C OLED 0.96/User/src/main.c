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
#include "bmp.h"

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
    char ch = '&', tmp[10] = {0};

    Init_all();
    
    while(1)
    {
        OLED_ShowPic(0,0,128,64,BMP1,1);
		OLED_Refresh();
		delay_ms(1000);
		OLED_Clear();

		OLED_Putzh(18,0,0,16,1);//你
		OLED_Putzh(36,0,1,16,1);//好
		OLED_Putzh(72,0,2,16,1);//世
		OLED_Putzh(90,0,3,16,1);//界

		OLED_Puts(8,16,"Hello, world!",16,1);
		OLED_Puts(20,32,"2022/08/08",16,1);
        sprintf(tmp, "ASCII:%c", ch);
		OLED_Puts(0,48,tmp,16,1);  
        sprintf(tmp, "CODE: %d", ch);
		OLED_Puts(63,48,tmp,16,1);
		OLED_Refresh();
		delay_s(1);
		OLED_Clear();

		OLED_Putzh( 0, 0, 0, 16, 1);//16*16 你
        OLED_Putzh( 0,16, 1, 24, 1);//24*24 好
		OLED_Putzh(24, 0, 2, 32, 1);//32*32 世
        OLED_Putzh(64, 0, 3, 64, 1);//64*64 界
        OLED_Refresh();
        delay_s(1);
        OLED_Clear();

		OLED_Puts( 0, 0, "Hello", 8, 1);//6*8
		OLED_Puts(36, 8, "World",12, 1);//6*12
        OLED_Puts( 0,20, "Hello",16, 1);//8*16
		OLED_Puts(48,36, "World",24, 1);//12*24
        OLED_Refresh();
		delay_ms(1000);
		OLED_Scrollzh(4, 4, 1);
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
    
}
/******************************** END OF FILE *********************************/
