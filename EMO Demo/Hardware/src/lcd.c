/**
  ******************************************************************************
  * @file    /Hardware/src/lcd.c 
  * @author  Jarvis-JKW
  * @version V0.0.1
  * @date    29-July-2022
  * @brief   LCD program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * IC: ST7735S SPI1
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "led.h"
#include "spi.h"
#include "font.h"

_LCD_ConfigTypedef LCD_Configuration;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  LCD Init program.
  * @param  None
  * @retval None
  */
void LCD_Init(void)
{
    GPIO_ResetBits(LCD_Port, LCD_RES_Pin);
    delay_ms(100);
    GPIO_SetBits(LCD_Port, LCD_RES_Pin);
    delay_ms(100);
    
    GPIO_SetBits(LCD_Port, LCD_BLK_Pin);
    delay_ms(100);

    LCD_WriteCmd(0x11);
    delay_ms(120);

    LCD_WriteCmd(0xB1); LCD_Write8bitData(0x05); LCD_Write8bitData(0x3C); LCD_Write8bitData(0x3C);   
    LCD_WriteCmd(0xB2); LCD_Write8bitData(0x05); LCD_Write8bitData(0x3C); LCD_Write8bitData(0x3C);   
    LCD_WriteCmd(0xB3); LCD_Write8bitData(0x05); LCD_Write8bitData(0x3C); LCD_Write8bitData(0x3C);
                        LCD_Write8bitData(0x05); LCD_Write8bitData(0x3C); LCD_Write8bitData(0x3C);
    LCD_WriteCmd(0xB4); LCD_Write8bitData(0x03);
    LCD_WriteCmd(0xC0); LCD_Write8bitData(0xAB); LCD_Write8bitData(0x0B); LCD_Write8bitData(0x04);
    LCD_WriteCmd(0xC1); LCD_Write8bitData(0xC5);
    LCD_WriteCmd(0xC2); LCD_Write8bitData(0x0D); LCD_Write8bitData(0x00);
    LCD_WriteCmd(0xC3); LCD_Write8bitData(0x8D); LCD_Write8bitData(0x6A);
    LCD_WriteCmd(0xC4); LCD_Write8bitData(0x8D); LCD_Write8bitData(0xEE);   
    LCD_WriteCmd(0xC5); LCD_Write8bitData(0x0F);
    LCD_WriteCmd(0xE0); LCD_Write8bitData(0x07); LCD_Write8bitData(0x0E); LCD_Write8bitData(0x08);
                        LCD_Write8bitData(0x07); LCD_Write8bitData(0x10); LCD_Write8bitData(0x07);
                        LCD_Write8bitData(0x02); LCD_Write8bitData(0x07); LCD_Write8bitData(0x09);
                        LCD_Write8bitData(0x0F); LCD_Write8bitData(0x25); LCD_Write8bitData(0x36);
                        LCD_Write8bitData(0x00); LCD_Write8bitData(0x08); LCD_Write8bitData(0x04);
                        LCD_Write8bitData(0x10);
    LCD_WriteCmd(0xE1); LCD_Write8bitData(0x0A); LCD_Write8bitData(0x0D); LCD_Write8bitData(0x08);
                        LCD_Write8bitData(0x07); LCD_Write8bitData(0x0F); LCD_Write8bitData(0x07);
                        LCD_Write8bitData(0x02); LCD_Write8bitData(0x07); LCD_Write8bitData(0x09);
                        LCD_Write8bitData(0x0F); LCD_Write8bitData(0x25); LCD_Write8bitData(0x35);   
                        LCD_Write8bitData(0x00); LCD_Write8bitData(0x09); LCD_Write8bitData(0x04);
                        LCD_Write8bitData(0x10);
    LCD_WriteCmd(0xFC); LCD_Write8bitData(0x80);
    LCD_WriteCmd(0x3A); LCD_Write8bitData(0x05);   
    LCD_WriteCmd(0x36);

    switch(LCD_DIR)
    {
        case LCD_PORTRAIT:
            LCD_Write8bitData(0x08);
            LCD_Configuration.width = 80;
            LCD_Configuration.height = 160;
            break;
        case LCD_PORTRAIT_INV:
            LCD_Write8bitData(0xC8);
            LCD_Configuration.width = 80;
            LCD_Configuration.height = 160;
            break;
        case LCD_LANDSCAPE:
            LCD_Write8bitData(0x78);
            LCD_Configuration.width = 160;
            LCD_Configuration.height = 80;
            break;
        case LCD_LANDSCAPE_INV:
            LCD_Write8bitData(0xA8);
            LCD_Configuration.width = 160;
            LCD_Configuration.height = 80;
            break;
    }

    LCD_WriteCmd(0x21);
    LCD_WriteCmd(0x29);
    LCD_WriteCmd(0x2A); LCD_Write8bitData(0x00); LCD_Write8bitData(0x1A); LCD_Write8bitData(0x00);
                        LCD_Write8bitData(0x69);
    LCD_WriteCmd(0x2B); LCD_Write8bitData(0x00); LCD_Write8bitData(0x01); LCD_Write8bitData(0x00);
                        LCD_Write8bitData(0xA0);
    LCD_WriteCmd(0x2C);

    LCD_Configuration.bgColor = LCD_COLOR_BLACK;
    LCD_Configuration.penColor = LCD_COLOR_WHITE;
}

/**
  * @brief  LCD write Data program.
  * @param  data will be transmit to display IC 
  * @retval None
  */
void LCD_Write8bitData(uint8_t data)
{
    GPIO_ResetBits(LCD_Port, LCD_CS_Pin);
    SPI_SendByte(SPI1, data);
    GPIO_SetBits(LCD_Port, LCD_CS_Pin);
}

void LCD_WriteData(uint16_t data)
{
    GPIO_ResetBits(LCD_Port, LCD_CS_Pin);
    SPI_SendByte(SPI1, data>>8);
    SPI_SendByte(SPI1, data&0xFF);
    GPIO_SetBits(LCD_Port, LCD_CS_Pin);
}

/**
  * @brief  LCD write command program.
  * @param  command will be transmit to display IC 
  * @retval None
  */
void LCD_WriteCmd(uint8_t cmd)
{
    GPIO_ResetBits(LCD_Port, LCD_DC_Pin|LCD_CS_Pin);
    SPI_SendByte(SPI1, cmd);
    GPIO_SetBits(LCD_Port, LCD_DC_Pin|LCD_CS_Pin);
}


/**
  * @brief  LCD set refresh area.
  * @param  Coordinates of edge points
  * @retval None
  */
void LCD_SetRefreshArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY)
{
    if(LCD_DIR>>1) /* Landscape */
    {
        LCD_WriteCmd(0x2a); LCD_WriteData(startX+ 1); LCD_WriteData(endX+ 1);
        LCD_WriteCmd(0x2b); LCD_WriteData(startY+26); LCD_WriteData(endY+26);
        LCD_WriteCmd(0x2c);
    }
    else /* Portrait */
    {
        LCD_WriteCmd(0x2a); LCD_WriteData(startX+26); LCD_WriteData(endX+26);
        LCD_WriteCmd(0x2b); LCD_WriteData(startY+ 1); LCD_WriteData(endY+ 1);
        LCD_WriteCmd(0x2c);
    }
}


/**
  * @brief  Fill the area with the color.
  * @param  Coordinates of area & color
  * @retval None
  */
void LCD_Fill(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color)
{
    uint16_t i, j;
    
    LCD_SetRefreshArea(startX, startY, endX-1, endY-1);
    for(i = startY; i < endY; i++)
    for(j = startX; j < endX; j++)
        LCD_WriteData(color);
}

/**
  * @brief  Graphic functions
  * @param  Coordinates of key points & color
  * @retval None
  */
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetRefreshArea(x, y, x, y);
    LCD_WriteData(color);
}

void LCD_DrawLine(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color)
{
    uint16_t t;
    int distance, deltaX = endX - startX, deltaY = endY - startY, xErr = 0, yErr = 0;
    int incX, incY, uRow = startX, uCol = startY;
    
    if(deltaX > 0)
        incX = 1;
    else if(deltaX == 0)
        incX = 0;
    else
    {
        incX = -1;
        deltaX = -deltaX;
    }
    
    if(deltaY > 0)
        incY = 1;
    else if(deltaY == 0)
        incY = 0;
    else
    {
        incY = -1;
        deltaY = -deltaY;
    }
    
    distance = deltaX > deltaY ? deltaX:deltaY;
    
    for(t = 0; t < distance+1; t++)
    {
        LCD_DrawPoint(uRow, uCol, color);
        xErr += deltaX;
        yErr += deltaY;
        if(xErr > distance)
        {
            xErr -= distance;
            uRow += incX;
        }
        if(yErr > distance)
        {
            yErr -= distance;
            uCol += incY;
        }
    }
}

void LCD_DrawRect(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color)
{
    LCD_DrawLine(startX, startY, endX, startY, color);
    LCD_DrawLine(startX, startY, startX, endY, color);
    LCD_DrawLine(startX, endY, endX, endY, color);
    LCD_DrawLine(endX, startY, endX, endY, color);
}

void LCD_DrawCircle(uint16_t x, uint16_t y, uint8_t r, uint16_t color)
{
    int a = 0, b = r;

    while(a <= b)
    {
        LCD_DrawPoint(x - b, y - a, color);
        LCD_DrawPoint(x + b, y - a, color);
        LCD_DrawPoint(x - a, y + b, color);
        LCD_DrawPoint(x - a, y - b, color);
        LCD_DrawPoint(x + b, y + a, color);
        LCD_DrawPoint(x + a, y - b, color);
        LCD_DrawPoint(x + a, y + b, color);
        LCD_DrawPoint(x - b, y + a, color);
        a++;
        if((a * a + b * b)>(r * r))//判断要画的点是否过远
        {
            b--;
        }
    }
}


/**
  * @brief  print the ASCII character to LCD.
  * @param  Coordinates of starting point
  *         ASCII code of character
  *         size of character: 12|16|24|32
  *         mode: superposition
  * @retval None
  */
void LCD_Putchar(uint16_t x, uint16_t y, uint8_t ch, uint8_t sizeY, uint8_t mode)
{
    uint8_t temp, t, m = 0, sizeX = sizeY/2;
    uint16_t i, TypefaceNum = (sizeX/8+((sizeX%8)!=0))*sizeY;//一个字符所占字节大小
    uint16_t x0=x;

    ch -= ' ';    //得到偏移后的值
    LCD_SetRefreshArea(x,y,x+sizeX-1,y+sizeY-1);
    for(i=0;i<TypefaceNum;i++)
    {
        switch(sizeY)
        {
            case 12: temp = ascii_1206[ch][i]; break;
            case 16: temp = ascii_1608[ch][i]; break;
            case 24: temp = ascii_2412[ch][i]; break;
            case 32: temp = ascii_3216[ch][i]; break;
            default: return;
        }

        for(t=0;t<8;t++)
        {
            if(!mode) /* 非叠加模式 */
            {
                if(temp&(0x01<<t))
                    LCD_WriteData(LCD_Configuration.penColor);
                else
                    LCD_WriteData(LCD_Configuration.bgColor);
                m++;
                if(m%sizeX==0)
                {
                    m=0;
                    break;
                }
            }
            else /* 叠加模式 */
            {
                if(temp&(0x01<<t))
                    LCD_DrawPoint(x, y, LCD_Configuration.penColor);
                x++;
                if((x-x0)==sizeX)
                {
                    x=x0;
                    y++;
                    break;
                }
            }
        }
    }
}

/**
  * @brief  print the ASCII string to LCD.
  * @param  Coordinates of starting point
  *         Address of the first character of the string
  *         size of character: 12|16|24|32
  *         mode: superposition
  * @retval None
  */
void LCD_Puts(uint16_t startX, uint16_t startY, char *p, uint8_t sizeY, uint8_t mode)
{
    while(*p != '\0')
    {
        LCD_Putchar(startX, startY, *p++, sizeY, mode);
        startX += sizeY / 2; 
    }
}

/**
  * @brief  print the Chinese characters to LCD.
  * @param  Coordinates of starting point
  *         Address of the first character of the characters
  *         size of character: 12|16|24|32
  *         mode: superposition
  * @retval None
  */
void LCD_Putzh(uint16_t startX, uint16_t startY, char *p, uint8_t sizeY, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k, num;
    uint16_t x0 = startX, TypefaceNum = (sizeY/8+((sizeY%8)?1:0))*sizeY;

    switch(sizeY)
    {
        case 12: num = sizeof(tfont12)/sizeof(typFNT_GB12); break;
        case 16: num = sizeof(tfont16)/sizeof(typFNT_GB16); break;
        case 24: num = sizeof(tfont24)/sizeof(typFNT_GB24); break;
        case 32: num = sizeof(tfont32)/sizeof(typFNT_GB32); break;
    }

    while(*p != '\0')
    {
        for(k = 0; k<num; k++)
        {
            if (((tfont12[k].Index[0]==*(p))&&(tfont12[k].Index[1]==*(p+1))&&(sizeY==12))||
                ((tfont16[k].Index[0]==*(p))&&(tfont16[k].Index[1]==*(p+1))&&(sizeY==16))||
                ((tfont24[k].Index[0]==*(p))&&(tfont24[k].Index[1]==*(p+1))&&(sizeY==24))||
                ((tfont32[k].Index[0]==*(p))&&(tfont32[k].Index[1]==*(p+1))&&(sizeY==32)))
            {     
                LCD_SetRefreshArea(startX, startY, startX+sizeY-1, startY+sizeY-1);
                for(i = 0; i < TypefaceNum; i++)
                {
                    for(j = 0; j < 8; j++)
                    {    
                        if(!mode)/* 非叠加方式 */
                        {
                            if(((tfont12[k].Msk[i]&(0x01<<j))&&(sizeY==12))||((tfont16[k].Msk[i]&(0x01<<j))&&(sizeY==16))||
                               ((tfont24[k].Msk[i]&(0x01<<j))&&(sizeY==24))||((tfont32[k].Msk[i]&(0x01<<j))&&(sizeY==32)))
                                LCD_WriteData(LCD_Configuration.penColor);
                            else
                                LCD_WriteData(LCD_Configuration.bgColor);
                            m++;
                            if(m%sizeY==0)
                            {
                                m=0;
                                break;
                            }
                        }
                        else /* 叠加方式 */
                        {
                            if(((tfont12[k].Msk[i]&(0x01<<j))&&(sizeY==12))||((tfont16[k].Msk[i]&(0x01<<j))&&(sizeY==16))||
                               ((tfont24[k].Msk[i]&(0x01<<j))&&(sizeY==24))||((tfont32[k].Msk[i]&(0x01<<j))&&(sizeY==32)))
                                LCD_DrawPoint(startX, startY, LCD_Configuration.penColor);//画一个点
                            startX++;
                            if((startX-x0)==sizeY)
                            {
                                startX = x0;
                                startY++;
                                break;
                            }
                        }
                    }
                }
            }                      
            continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
        }
        p += 2;
        startX += sizeY;
    }
}


void LCD_ShowPic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pic)
{
    uint16_t r, c;
    uint32_t k = 0;
    
    LCD_SetRefreshArea(x, y, x + width - 1, y + height - 1);
    for(r = 0; r < width; r++)
    {
        for(c = 0; c < height; c++)
        {
            LCD_Write8bitData(pic[k<<1]);
            LCD_Write8bitData(pic[k<<1|1]);
            k++;
        }
    }
}

/******************************** END OF FILE *********************************/
