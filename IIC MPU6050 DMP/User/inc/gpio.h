/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

#include "main.h"


/* Private macro -------------------------------------------------------------*/
#define GPIO_NUMBER 16u

/* λ����������ÿһλ����Ϊһ��32λ���֣��������Դﵽ����λ��Ŀ�� */
#define BITBAND(addr, pin)      ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF)<<5) + (pin<<2))
#define MEM_ADDR(addr)          *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, pin)     MEM_ADDR(BITBAND(addr, pin))

/* ��һIO�ڲ���(n<16) */
#define PAout(n)        BIT_ADDR(GPIOA_BASE + 12, n)
#define PBout(n)        BIT_ADDR(GPIOB_BASE + 12, n)
#define PCout(n)        BIT_ADDR(GPIOC_BASE + 12, n)
#define PDout(n)        BIT_ADDR(GPIOD_BASE + 12, n)
#define PEout(n)        BIT_ADDR(GPIOE_BASE + 12, n)
#define PFout(n)        BIT_ADDR(GPIOF_BASE + 12, n)
#define PGout(n)        BIT_ADDR(GPIOG_BASE + 12, n)

#define PAin(n)         BIT_ADDR(GPIOA_BASE + 8, n)
#define PBin(n)         BIT_ADDR(GPIOB_BASE + 8, n)
#define PCin(n)         BIT_ADDR(GPIOC_BASE + 8, n)
#define PDin(n)         BIT_ADDR(GPIOD_BASE + 8, n)
#define PEin(n)         BIT_ADDR(GPIOE_BASE + 8, n)
#define PFin(n)         BIT_ADDR(GPIOF_BASE + 8, n)
#define PGin(n)         BIT_ADDR(GPIOG_BASE + 8, n)

/* Private function prototypes -----------------------------------------------*/
void GPIO_Config(void);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* __GPIO_H */
/******************************** END OF FILE *********************************/
