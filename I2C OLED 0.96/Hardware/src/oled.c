/**
  ******************************************************************************
  * @file    /User/src/oled.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    11-Aug-2022
  * @brief   OLED driver via I2C bus.
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "oled.h"
#include "oledfont.h"
#include "iic.h"

uint8_t OLED_GRAM[8][144] = {0};

/**
  * @brief  OLED Init program.
  * @param  None
  * @retval None
  */
void OLED_Init(void)
{
    OLED_WriteCmd(0xAE);//--turn off oled panel
    OLED_WriteCmd(0x00);//---set low column address
    OLED_WriteCmd(0x10);//---set high column address
    OLED_WriteCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WriteCmd(0x81);//--set contrast control register
    OLED_WriteCmd(0xCF);// Set SEG Output Current Brightness
    OLED_WriteCmd(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WriteCmd(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WriteCmd(0xA6);//--set normal display
    OLED_WriteCmd(0xA8);//--set multiplex ratio(1 to 64)
    OLED_WriteCmd(0x3f);//--1/64 duty
    OLED_WriteCmd(0xD3);//-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WriteCmd(0x00);//-not offset
    OLED_WriteCmd(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WriteCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WriteCmd(0xD9);//--set pre-charge period
    OLED_WriteCmd(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WriteCmd(0xDA);//--set com pins hardware configuration
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0xDB);//--set vcomh
    OLED_WriteCmd(0x40);//Set VCOM Deselect Level
    OLED_WriteCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WriteCmd(0x02);//
    OLED_WriteCmd(0x8D);//--set Charge Pump enable/disable
    OLED_WriteCmd(0x14);//--set(0x10) disable
    OLED_WriteCmd(0xA4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WriteCmd(0xA6);// Disable Inverse Display On (0xa6/a7) 
    OLED_Clear();
    OLED_WriteCmd(0xAF);
    
    OLED_ColorTurn(DISABLE);
    OLED_DirectionTurn(DISABLE);
}

void OLED_Display(FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        OLED_WriteCmd(0x8D);
        OLED_WriteCmd(0x14);
        OLED_WriteCmd(0xAF);
    }
    else
    {
        OLED_WriteCmd(0x8D);
        OLED_WriteCmd(0x10);
        OLED_WriteCmd(0xAE);
    }
}

//屏幕旋转180度
void OLED_DirectionTurn(FunctionalState NewState)
{
    /* inverse 180 */
    if (NewState != DISABLE)
    {
        OLED_WriteCmd(0xC0);
        OLED_WriteCmd(0xA0);
    }
    else /* normal */
    {
        OLED_WriteCmd(0xC8);
        OLED_WriteCmd(0xA1);
    }
}


/**
  * @brief  Refresh GRAM to OLED.
  * @param  None
  * @retval None
  */    
void OLED_Refresh(void)
{
    uint8_t p;

    for(p = 0; p < 8; p++)
    {
        OLED_WriteCmd(0xB0+p); //设置页地址
        OLED_WriteCmd(0x10);   //设置低列起始地址
        OLED_WriteCmd(0x00);   //设置高列起始地址
        OLED_WritePage(OLED_GRAM[p]);
    }
}

/**
  * @brief  Partial Refresh GRAM to OLED.
  * @param  None
  * @retval None
  */ 
void OLED_PartialRefresh(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
    uint8_t p;
    
    startY /= 8;
    endY = endY%8 ? endY/8+1:endY/8;
    for(p = startY; p < endY; p++)
    {
        OLED_WriteCmd(0xB0+p); //设置页地址
        OLED_WriteCmd(0x00+startX%16);   //设置低列起始地址
        OLED_WriteCmd(0x10+startX/16);   //设置高列起始地址
        I2C_WriteBytes(I2C1, OLED_ADDR, 0x40, OLED_GRAM[p]+startX, endX-startX);
    }
}

/**
 * @brief   Clear screen
 * @param   None
 * @retval  None
 */
void OLED_Clear(void)
{
    uint8_t p, c;
    
    for(p = 0; p < 8; p++)
    {
        for(c = 0; c < 128; c++)
        {
            OLED_GRAM[p][c] = 0;
        }
    }
    OLED_Refresh();
}


/**
  * @brief  Graphic functions
  * @param  x: 0 ~ 127
  *         y: 0 ~ 63
  *         inv_flag: 0 inverse | 1 normal
  * @retval None
  */
void OLED_DrawPoint(uint8_t x, uint8_t y,  uint8_t inv_flag)
{
    uint8_t i, tmp;
    
    i = y / 8;
    tmp = 1 << (y % 8);
    
    if(inv_flag)
        OLED_GRAM[i][x] |= tmp;
    else
    {
        OLED_GRAM[i][x] = ~OLED_GRAM[i][x];
        OLED_GRAM[i][x] |= tmp;
        OLED_GRAM[i][x] = ~OLED_GRAM[i][x];
    }
}

void OLED_DrawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t inv_flag)
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
        OLED_DrawPoint(uRow, uCol, inv_flag);
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

void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r)
{
    int a = 0, b = r;

    while(2 * b * b >= r * r)      
    {
        OLED_DrawPoint(x + a, y - b,1);
        OLED_DrawPoint(x - a, y - b,1);
        OLED_DrawPoint(x - a, y + b,1);
        OLED_DrawPoint(x + a, y + b,1);

        OLED_DrawPoint(x + b, y + a,1);
        OLED_DrawPoint(x + b, y - a,1);
        OLED_DrawPoint(x - b, y - a,1);
        OLED_DrawPoint(x - b, y + a,1);
        a++;
        if((a*a + b*b) > (r*r)) //判断要画的点是否过远
        {
            a--;
            b--;
        }
    }
}


/**
  * @brief  print the ASCII character to OLED.
  * @param  Coordinates of starting point
  *         ASCII code of character
  *         size of character: 08|12|16|24
  *         inv_flag: 0 inverse | 1 normal
  * @retval None
  */
void OLED_Putchar(uint8_t x, uint8_t y, uint8_t ch, uint8_t sizeY, uint8_t inv_flag)
{
    uint8_t r, c, temp, sizeX, startX = x, startY = y;

    sizeX = sizeY==8 ? 6:(sizeY/8+((sizeY%8)?1:0))*(sizeY/2);
    ch -= ' ';
    for(c = 0; c < sizeX; c++)
    {
        switch(sizeY)
        {
            case 8: temp = ascii_0806[ch][c]; break;
            case 12:temp = ascii_1206[ch][c]; break;
            case 16:temp = ascii_1608[ch][c]; break;
            case 24:temp = ascii_2412[ch][c]; break;
            default: return;
        }
        for(r = 0; r < 8; r++)
        {
            OLED_DrawPoint(x, y, temp&0x01 ? inv_flag:(!inv_flag));
            temp>>=1;
            y++;
        }

        x++;
        if((sizeY != 8)&&((x-startX) == sizeY/2))
        {
            x = startX;
            startY += 8;
        }
        y = startY;
    }
}


/**
  * @brief  print the ASCII string to OLED.
  * @param  Coordinates of starting point
  *         Address of the first character of the string
  *         size of character: 8|12|16|24
  *         inv_flag: 0 inverse | 1 normal
  * @retval None
  */
void OLED_Puts(uint8_t x, uint8_t y, char *p, uint8_t sizeY, uint8_t inv_flag)
{
    while((*p >= ' ')&&(*p <= '~'))
    {
        OLED_Putchar(x, y, *p++, sizeY, inv_flag);
        x += (sizeY == 8 ? 6:(sizeY/2));
    }
}


/**
  * @brief  print the Chinese characters to OLED.
  * @param  Coordinates of starting point
  *         Index of the character
  *         size of character: 16|24|32|64
  *         inv_flag: 0 inverse | 1 normal
  * @retval None
  */
void OLED_Putzh(uint8_t x, uint8_t y, uint8_t idx, uint8_t sizeY, uint8_t inv_flag)
{
    uint8_t r, temp, startX = x, startY = y;
    uint16_t i, TypefaceNum = (sizeY/8+((sizeY%8)?1:0))*sizeY;  //得到字体一个字符对应点阵集所占的字节数
    for(i = 0; i < TypefaceNum; i++)
    {
        switch(sizeY)
        {
            case 16: temp = tfont16[idx][i]; break;
            case 24: temp = tfont24[idx][i]; break;
            case 32: temp = tfont32[idx][i]; break;
            case 64: temp = tfont64[idx][i]; break;
            default: return;
        }
        
        for(r = 0; r < 8; r++)  //  each page controls 8 rows
        {
            OLED_DrawPoint(x, y, temp&0x01 ? inv_flag:(!inv_flag));
            temp>>=1;
            y++;
        }
        x++;
        if((x-startX) == sizeY)
        {
            x = startX;
            startY += 8;        //  goto next page
        }
        y = startY;
    }
}


/**
  * @brief  print the binary picture to OLED.
  * @param  Coordinates of starting point
  *         scale of the picture (pixels)
  *         address of the picture array
  *         inv_flag: 0 inverse | 1 normal
  * @retval None
  */
void OLED_ShowPic(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t *pic, uint8_t inv_flag)
{
    uint8_t r, c, temp, p, startX = x, startY = y;
    uint16_t i = 0;
    
    height = height/8 + ((height%8) ? 1:0); // convert number of pixels to number of pages
    for(p = 0; p < height; p++)
    {
        for(c = 0; c < width; c++)
        {
            temp = pic[i++];
            for(r = 0; r < 8; r++)          // each page controls 8 rows
            {
                OLED_DrawPoint(x, y, temp&0x01 ? inv_flag:(!inv_flag));
                temp >>= 1;
                y++;
            }

            x++;
            if((x-startX) == width)
            {
                x = startX;
                startY += 8;    //  goto next page
            }
            y = startY;
        }
    }
}

/**
  * @brief  print the binary picture to OLED.
  * @param  number of chinese characters
  *         number of full-width blank between cycles
  *         inv_flag: 0 inverse | 1 normal
  * @note   Chinese characters are required size 16.
  * @retval None
  */
void OLED_Scrollzh(uint8_t n, uint8_t gap, uint8_t inv_flag)
{
    uint8_t p, c, idx = 0, i = 0, j;
    
    while(1)
    {
        if(i==0)
        {
            OLED_Putzh(128, 24, idx, 16, inv_flag);
            idx++;
        }
        
        if(idx==n)
        {
            for(j = 0; j < 16 * gap; j++)
            {
                for(c = 1; c < 144; c++)
                {
                    for(p = 0; p < 8; p++)
                    {
                        OLED_GRAM[p][c-1] = OLED_GRAM[p][c];
                    }
                }
                OLED_Refresh();
            }
            idx = 0;
        }
        
        i++; //hiden GRAM cols
        if(i==16)
            i = 0;
        for(c = 1; c < 144; c++)
        {
            for(p = 0; p < 8; p++)
            {
                OLED_GRAM[p][c-1] = OLED_GRAM[p][c];
            }
        }
        OLED_Refresh();
    }
}

