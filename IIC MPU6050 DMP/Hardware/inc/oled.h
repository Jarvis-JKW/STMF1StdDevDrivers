#ifndef __OLED_H
#define __OLED_H 

#include "main.h"

//-----------------OLED端口定义---------------- 
#define OLED_WriteCmd(cmd)      IIC_Write(&IIC2, OLED_ADDR, 0x00, cmd)
#define OLED_WriteData(data)    IIC_Write(&IIC2, OLED_ADDR, 0x40, data)
#define OLED_WritePage(arr)     IIC_WriteBytes(&IIC2, OLED_ADDR, 0x40, arr, 128)
#define OLED_ColorTurn(flag)    OLED_WriteCmd(0xA6+(flag?1:0)) // 0:正常显示 1:反色显示

void OLED_Init(void);
void OLED_DirectionTurn(FunctionalState NewState);

void OLED_Refresh(void);
void OLED_PartialRefresh(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
void OLED_Clear(void);
void OLED_Display(FunctionalState NewState);

void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_Putchar(uint8_t x, uint8_t y, uint8_t ch, uint8_t sizeY, uint8_t inv_flag);
void OLED_Puts(uint8_t x, uint8_t y, char *p, uint8_t sizeY, uint8_t inv_flag);
void OLED_Putzh(uint8_t x, uint8_t y, uint8_t idx, uint8_t sizeY, uint8_t inv_flag);
void OLED_ShowPic(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t *pic, uint8_t inv_flag);
void OLED_Scrollzh(uint8_t n, uint8_t gap, uint8_t inv_flag);



#endif

