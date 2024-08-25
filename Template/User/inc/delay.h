/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#ifdef DELAY_WITH_SYSTICK
void Delay_Init(void);
#endif /* DELAY_WITH_SYSTICK */

void delay_ms(uint16_t ms);
void delay_us(uint32_t us);
void delay_s(uint8_t s);


//included by "usart.c", "led.c", "buzzer.c", "button.c", "rtc.c", "hcsr04.c",
//"init.c"
#endif /* __DELAY_H */
/******************************** END OF FILE *********************************/
