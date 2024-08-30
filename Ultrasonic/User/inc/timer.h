/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H
/* Includes ------------------------------------------------------------------*/
#include "sys.h"


/** @defgroup Timer_Init_Functions
  * @{
  */
void TIM7_Time_Init(uint16_t Autoreload, uint16_t Prescaler);
/**
  * @}
  */


#endif	/* __TIMER_H */
/******************************** END OF FILE *********************************/
