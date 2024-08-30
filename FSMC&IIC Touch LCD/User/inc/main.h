/**
  ******************************************************************************
  * @file    /User/inc/main.h
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
  *
  ******************************************************************************
  */  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "binary.h"
#include "debug.h"

/* Public typedef ------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define LED0_Port       GPIOB
#define LED0_Pin        GPIO_Pin_5
#define GT9147_ADDR     0x28
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/


#endif /* __MAIN_H */
/******************************** END OF FILE *********************************/
