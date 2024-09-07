/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef	__LCD_H
#define	__LCD_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define LCD_PORTRAIT        0
#define LCD_PORTRAIT_INV    1
#define LCD_LANDSCAPE       2
#define LCD_LANDSCAPE_INV   3


/* RGB565 Code */
#define LCD_COLOR_WHITE     0xFFFF
#define LCD_COLOR_BLACK     0x0000
#define LCD_COLOR_RED       0xF800
#define LCD_COLOR_GREEN     0x07E0
#define LCD_COLOR_BLUE      0x001F
#define LCD_COLOR_YELLOW    0xFFC0
#define LCD_COLOR_PINK      0xF81F
#define LCD_COLOR_CYAN      0x07FF

typedef struct
{
    uint16_t width, height;
    uint16_t bgColor, penColor;
} _LCD_ConfigTypedef;
extern _LCD_ConfigTypedef LCD_Configuration;

void LCD_Init(void);
void LCD_Write8bitData(uint8_t data);
void LCD_WriteData(uint16_t data);
void LCD_WriteCmd(uint8_t cmd);

void LCD_SetRefreshArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY);
void LCD_Fill(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);
void LCD_DrawRect(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);
void LCD_DrawCircle(uint16_t x, uint16_t y, uint8_t r, uint16_t color);
void LCD_Putchar(uint16_t x, uint16_t y, uint8_t ch, uint8_t sizeY, uint8_t mode);
void LCD_Puts(uint16_t startX, uint16_t startY, char *p, uint8_t sizeY, uint8_t mode);
void LCD_Putzh(uint16_t startX, uint16_t startY, char *p, uint8_t sizeY, uint8_t mode);
void LCD_ShowPic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pic);
#endif	/* __LCD_H */
/******************************** END OF FILE *********************************/
