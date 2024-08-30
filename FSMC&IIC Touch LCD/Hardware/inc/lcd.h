/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "iic.h"
/* Display define ------------------------------------------------------------*/
#define LCD_CMD_ADDR        0x6C0007FE
#define LCD_DATA_ADDR       0x6C000800

#define LCD_WIDTH           480
#define LCD_HEIGHT          800

#define LCD_WRGRAM_CMD      0x2C00
#define LCD_SETX_CMD        0x2A00
#define LCD_SETY_CMD        0x2B00

/* RGB565 Code */
#define LCD_COLOR_WHITE     0xFFFF
#define LCD_COLOR_BLACK     0x0000
#define LCD_COLOR_RED       0xF800
#define LCD_COLOR_GREEN     0x07E0
#define LCD_COLOR_BLUE      0x001F
#define LCD_COLOR_YELLOW    0xFFC0
#define LCD_COLOR_PINK      0xF81F
#define LCD_COLOR_CYAN      0x07FF

/* Touch define --------------------------------------------------------------*/
#define LCD_PRESS_DOWN      0x80
#define LCD_CATCH_PRESS     0x40

#define GT9147_CTRL         0x8040      //GT9147控制寄存器
#define GT9147_CONFIG       0x8047      //GT9147配置起始地址寄存器
#define GT9147_CHECK        0x80FF      //GT9147校验和寄存器
#define GT9147_PRODUCT_ID   0x8140      //GT9147产品ID寄存器

#define GT9147_GSTID        0x814E      //GT9147当前检测到的触摸情况
#define GT9147_TOUCH1       0x8150
#define GT9147_TOUCH2       0x8158
#define GT9147_TOUCH3       0x8160
#define GT9147_TOUCH4       0x8168
#define GT9147_TOUCH5       0x8170

#define LCD_WriteCmd(cmd)       *(uint16_t *)(LCD_CMD_ADDR) = cmd
#define LCD_WriteData(data)     *(uint16_t *)(LCD_DATA_ADDR)= data
#define LCD_Write(addr, data)   {LCD_WriteCmd(addr); LCD_WriteData(data);}
#define LCD_ReadData()          *(uint16_t *)(LCD_DATA_ADDR)
#define LCD_Backlight(NewState) GPIO_WriteBit(GPIOB, GPIO_Pin_0, NewState ? Bit_SET:Bit_RESET)

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    uint16_t width, height;
    uint16_t id;
    uint8_t direction;
    uint16_t bgColor, penColor;
    uint16_t x[5], y[5];
    uint8_t touchState;
} LCD_ConfigTypedef;

typedef enum
{
    _LR_UD, //from Left to Right, then from Up to Down //竖向正向显示
    _LR_DU, //from Left to Right, then from Down to Up
    _RL_UD, //from Right to left, then from Up to Down
    _RL_DU, //from Right to left, then from Down to Up //竖向倒置显示
    _UD_LR, //from Up to Down, then from Left to Right
    _DU_LR, //from Down to Up, then from Left to Right //横向靠右显示
    _UD_RL, //from Up to Down, then from Right to left //横向靠左显示
    _DU_RL  //from Down to Up, then from Right to left
} LCD_Scan_Mode;
/* Public variables ----------------------------------------------------------*/
extern LCD_ConfigTypedef LCD_Configuration;
extern IIC_TypeDef IIC_Touch;

/* Display functions ---------------------------------------------------------*/
void LCD_Init(void);
//void LCD_Write(uint16_t addr, uint16_t data);

uint8_t LCD_ReadID(void);

void LCD_SetWindow(u16 sx, u16 sy, u16 width, u16 height);
void LCD_SetScanMode(LCD_Scan_Mode mode);
void LCD_SetDirection(uint8_t NewDirection);

void LCD_SetCursor(uint16_t x, uint16_t y);
void LCD_Clear(uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_Fill(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);

void LCD_Putchar(uint16_t x, uint16_t y, char ch, uint8_t size);
void LCD_Puts(uint16_t startX, uint16_t startY, uint16_t linechars, uint16_t line, uint8_t size, char *p);

void LCD_Display_Test(void);

/* Touch functions based on IIC3 ---------------------------------------------*/
uint8_t LCD_Touch_Init(void);
void GT9147_SendConfig(uint8_t mode);
uint8_t LCD_TouchScan(void);

void LCD_PaintClear(void);
void LCD_PaintPoint(uint16_t centerX, uint16_t centerY, uint16_t radius, uint16_t color);
void LCD_PaintLine(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t size, uint16_t color);
void LCD_Paint(void);

#endif /* __LCD_H */
/******************************** END OF FILE *********************************/
