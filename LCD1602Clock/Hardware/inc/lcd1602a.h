/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef	__LCD1602_H
#define	__LCD1602_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef enum {LCD1602_CMD = 0, LCD1602_DATA = !LCD1602_CMD} LCD_Write_Mode;

void LCD1602A_Write(LCD_Write_Mode mode, uint8_t data);
void LCD1602A_Sendstr(uint8_t addr, uint8_t len, uint8_t *data);
void LCD1602A_Sendnum(uint8_t addr, uint16_t num);
void LCD1602A_Clock(void);


#endif	/* __LCD1602_H */
/******************************** END OF FILE *********************************/
