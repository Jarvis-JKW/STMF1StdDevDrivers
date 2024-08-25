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
#define LCD_Port        GPIOF
#define LCD_RS_Pin      GPIO_Pin_0
#define LCD_RW_Pin      GPIO_Pin_1
#define LCD_EN_Pin      GPIO_Pin_2
#define LCD_DATA_Pins   GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
/* Public macro --------------------------------------------------------------*/
#define	KEY0    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define KEY1    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define KEY_UP  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/


#endif /* __MAIN_H */
/******************************** END OF FILE *********************************/
