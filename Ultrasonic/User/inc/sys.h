/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_H
#define __SYS_H

/* Public includes -----------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "binary.h"


/* Pubic macro ---------------------------------------------------------------*/
#define GPIO_NUMBER     16u
/* 位带操作：把每一位膨胀为一个32位的字，访问字以达到访问位的目的 */
#define BITBAND(addr, pin)      ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF)<<5) + (pin<<2)) 
#define MEM_ADDR(addr)          *((volatile unsigned long *)(addr)) 
#define BIT_ADDR(addr, pin)     MEM_ADDR(BITBAND(addr, pin))

/* IO口地址映射 */
#define GPIOA_ODR_Addr  (GPIOA_BASE + 12)
#define GPIOB_ODR_Addr  (GPIOB_BASE + 12)
#define GPIOC_ODR_Addr  (GPIOC_BASE + 12)
#define GPIOD_ODR_Addr  (GPIOD_BASE + 12)
#define GPIOE_ODR_Addr  (GPIOE_BASE + 12)
#define GPIOF_ODR_Addr  (GPIOF_BASE + 12)
#define GPIOG_ODR_Addr  (GPIOG_BASE + 12)

#define GPIOA_IDR_Addr  (GPIOA_BASE + 8)
#define GPIOB_IDR_Addr  (GPIOB_BASE + 8)
#define GPIOC_IDR_Addr  (GPIOC_BASE + 8)
#define GPIOD_IDR_Addr  (GPIOD_BASE + 8)
#define GPIOE_IDR_Addr  (GPIOE_BASE + 8)
#define GPIOF_IDR_Addr  (GPIOF_BASE + 8)
#define GPIOG_IDR_Addr  (GPIOG_BASE + 8)


/* 单一IO口操作(n<16) */
#define PAout(n)        BIT_ADDR(GPIOA_ODR_Addr, n)
#define PBout(n)        BIT_ADDR(GPIOB_ODR_Addr, n)
#define PCout(n)        BIT_ADDR(GPIOC_ODR_Addr, n)
#define PDout(n)        BIT_ADDR(GPIOD_ODR_Addr, n)
#define PEout(n)        BIT_ADDR(GPIOE_ODR_Addr, n)
#define PFout(n)        BIT_ADDR(GPIOF_ODR_Addr, n)
#define PGout(n)        BIT_ADDR(GPIOG_ODR_Addr, n)

#define PAin(n)         BIT_ADDR(GPIOA_IDR_Addr, n)
#define PBin(n)         BIT_ADDR(GPIOB_IDR_Addr, n)
#define PCin(n)         BIT_ADDR(GPIOC_IDR_Addr, n)
#define PDin(n)         BIT_ADDR(GPIOD_IDR_Addr, n)
#define PEin(n)         BIT_ADDR(GPIOE_IDR_Addr, n)
#define PFin(n)         BIT_ADDR(GPIOF_IDR_Addr, n)
#define PGin(n)         BIT_ADDR(GPIOG_IDR_Addr, n)


void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif  /* __SYS_H */
/******************************** END OF FILE *********************************/
