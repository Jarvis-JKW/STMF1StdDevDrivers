/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUZZER_H
#define __BUZZER_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @defgroup C_Tone_Frequency
  * @{
  */
#define DO_L  262
#define RE_L  294
#define MI_L  330
#define FA_L  349
#define SO_L  392
#define LA_L  440
#define SI_L  494

#define DO    523
#define RE    587
#define MI    659
#define FA    698
#define SO    784
#define LA    880
#define SI    988

#define DO_H 1047
#define RE_H 1175
#define MI_H 1319
#define FA_H 1397
#define SO_H 1568
#define LA_H 1760
#define SI_H 1967
/**
  * @}
  */

void beep(uint8_t i);
void tone(uint16_t freq, uint16_t time);

//included by "stm32f10x_it.c", "init.c"
#endif /* __BUZZER_H */
/******************************** END OF FILE *********************************/
