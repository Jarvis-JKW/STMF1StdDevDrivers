/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    volatile uint8_t HH, mm, ss;
    volatile uint16_t yyyy;
    volatile uint8_t MM, dd, week;
}CAL_TypeDef;//日历结构体

extern CAL_TypeDef CAL_Structure;
extern const uint8_t mon_table[12];

uint8_t RTC_Config(void);
uint8_t isLeapYear(uint16_t year);

uint8_t RTC_UpdateTime(void);
uint8_t CalcWeek(uint16_t year, uint8_t month, uint8_t day);
uint8_t RTC_Set(uint16_t yyyy, uint8_t MM, uint8_t dd, uint8_t HH, uint8_t mm, uint8_t ss);
uint8_t RTC_Alarm_Set(uint16_t yyyy, uint8_t MM, uint8_t dd, uint8_t HH, uint8_t mm, uint8_t ss);
void COM_RTC_Clock(uint8_t sec);

//included by "stm32f10x_it.c", "usart.c", "init.c"
#endif	/* __RTC_H */
/******************************** END OF FILE *********************************/
