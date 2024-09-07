/**
  ******************************************************************************
  * @file    /User/inc/main.h
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
  *
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "binary.h"
#include "debug.h"

/* Public typedef ------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define LED0_Port   GPIOB
#define LCD_Port    GPIOA
#define LED0_Pin    GPIO_Pin_5
#define LCD_BLK_Pin GPIO_Pin_1
#define LCD_DC_Pin  GPIO_Pin_2
#define LCD_RES_Pin GPIO_Pin_3
#define LCD_CS_Pin  GPIO_Pin_4
#define LCD_DIR     LCD_LANDSCAPE
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/



/******************************** END OF FILE *********************************/
