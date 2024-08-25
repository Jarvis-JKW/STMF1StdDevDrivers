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
#define DT_Port   GPIOF
#define CS_Port   GPIOF

#define DT_Pin_A  GPIO_Pin_5
#define DT_Pin_B  GPIO_Pin_4
#define DT_Pin_C  GPIO_Pin_2
#define DT_Pin_D  GPIO_Pin_1
#define DT_Pin_E  GPIO_Pin_0
#define DT_Pin_F  GPIO_Pin_6
#define DT_Pin_G  GPIO_Pin_7
#define DT_Pin_DP GPIO_Pin_3

#define CS_Pin_1  GPIO_Pin_8
#define CS_Pin_2  GPIO_Pin_9
#define CS_Pin_3  GPIO_Pin_10
#define CS_Pin_4  GPIO_Pin_11
#define CS_Pin_5  GPIO_Pin_12
#define CS_Pin_6  GPIO_Pin_13
#define CS_Pin_7  GPIO_Pin_14
#define CS_Pin_8  GPIO_Pin_15
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/


#endif /* __MAIN_H */
/******************************** END OF FILE *********************************/
