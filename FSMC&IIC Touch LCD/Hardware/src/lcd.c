/**
  ******************************************************************************
  * @file    /Hardware/src/lcd.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    13-Feb-2022
  * @brief   Private BSP Display & Touch driver for AlienTek TFT-LCD 4.3 
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312/GBK as encoding.
  * Display IC: NT35510
  * Touch   IC: GT9147/GT917S
  ******************************************************************************
  */

#include "lcd.h"
#include "font.h"

const uint16_t GT9147_TouchxAddress[] = {GT9147_TOUCH1, GT9147_TOUCH2, GT9147_TOUCH3, GT9147_TOUCH4, GT9147_TOUCH5};
const uint16_t PaintBrushColor[] = {LCD_COLOR_BLACK, LCD_COLOR_RED, LCD_COLOR_BLUE, LCD_COLOR_CYAN, LCD_COLOR_GREEN};

LCD_ConfigTypedef LCD_Configuration;
IIC_TypeDef IIC_Touch;

/* Display functions ---------------------------------------------------------*/
void LCD_Init(void)
{
    if(LCD_ReadID()!=ERROR)
    {
        LCD_Write(0xF000, 0x55); LCD_Write(0xF001, 0xAA); LCD_Write(0xF002, 0x52);
        LCD_Write(0xF003, 0x08); LCD_Write(0xF004, 0x01);
        /* AVDD Set AVDD 5.2V */
        LCD_Write(0xB000, 0x0D); LCD_Write(0xB001, 0x0D); LCD_Write(0xB002, 0x0D);
        /* AVDD ratio */
        LCD_Write(0xB600, 0x34); LCD_Write(0xB601, 0x34); LCD_Write(0xB602, 0x34);
        /* AVEE -5.2V */
        LCD_Write(0xB100, 0x0D); LCD_Write(0xB101, 0x0D); LCD_Write(0xB102, 0x0D);
        /* AVEE ratio */
        LCD_Write(0xB700, 0x34); LCD_Write(0xB701, 0x34); LCD_Write(0xB702, 0x34);
        /* VCL -2.5V */
        LCD_Write(0xB200, 0x00); LCD_Write(0xB201, 0x00); LCD_Write(0xB202, 0x00);
        /* VCL ratio */
        LCD_Write(0xB800, 0x24); LCD_Write(0xB801, 0x24); LCD_Write(0xB802, 0x24);
        /* VGH 15V (Free pump) */
        LCD_Write(0xBF00, 0x01); LCD_Write(0xB300, 0x0F);
        LCD_Write(0xB301, 0x0F); LCD_Write(0xB302, 0x0F);
        /* VGH ratio */
        LCD_Write(0xB900, 0x34); LCD_Write(0xB901, 0x34); LCD_Write(0xB902, 0x34);
        /* VGL_REG -10V */
        LCD_Write(0xB500, 0x08); LCD_Write(0xB501, 0x08);
        LCD_Write(0xB502, 0x08); LCD_Write(0xC200, 0x03);
        /* VGLX ratio */
        LCD_Write(0xBA00, 0x24); LCD_Write(0xBA01, 0x24); LCD_Write(0xBA02, 0x24);
        /* VGMP/VGSP 4.5V/0V */
        LCD_Write(0xBC00, 0x00); LCD_Write(0xBC01, 0x78); LCD_Write(0xBC02, 0x00);
        /* VGMN/VGSN -4.5V/0V */
        LCD_Write(0xBD00, 0x00); LCD_Write(0xBD01, 0x78); LCD_Write(0xBD02, 0x00);
        /* VCOM */
        LCD_Write(0xBE00, 0x00); LCD_Write(0xBE01, 0x64);
        /* Gamma Setting */
        LCD_Write(0xD100, 0x00); LCD_Write(0xD101, 0x33); LCD_Write(0xD102, 0x00);
        LCD_Write(0xD103, 0x34); LCD_Write(0xD104, 0x00); LCD_Write(0xD105, 0x3A);
        LCD_Write(0xD106, 0x00); LCD_Write(0xD107, 0x4A); LCD_Write(0xD108, 0x00);
        LCD_Write(0xD109, 0x5C); LCD_Write(0xD10A, 0x00); LCD_Write(0xD10B, 0x81);
        LCD_Write(0xD10C, 0x00); LCD_Write(0xD10D, 0xA6); LCD_Write(0xD10E, 0x00);
        LCD_Write(0xD10F, 0xE5); LCD_Write(0xD110, 0x01); LCD_Write(0xD111, 0x13);
        LCD_Write(0xD112, 0x01); LCD_Write(0xD113, 0x54); LCD_Write(0xD114, 0x01);
        LCD_Write(0xD115, 0x82); LCD_Write(0xD116, 0x01); LCD_Write(0xD117, 0xCA);
        LCD_Write(0xD118, 0x02); LCD_Write(0xD119, 0x00); LCD_Write(0xD11A, 0x02);
        LCD_Write(0xD11B, 0x01); LCD_Write(0xD11C, 0x02); LCD_Write(0xD11D, 0x34);
        LCD_Write(0xD11E, 0x02); LCD_Write(0xD11F, 0x67); LCD_Write(0xD120, 0x02);
        LCD_Write(0xD121, 0x84); LCD_Write(0xD122, 0x02); LCD_Write(0xD123, 0xA4);
        LCD_Write(0xD124, 0x02); LCD_Write(0xD125, 0xB7); LCD_Write(0xD126, 0x02);
        LCD_Write(0xD127, 0xCF); LCD_Write(0xD128, 0x02); LCD_Write(0xD129, 0xDE);
        LCD_Write(0xD12A, 0x02); LCD_Write(0xD12B, 0xF2); LCD_Write(0xD12C, 0x02);
        LCD_Write(0xD12D, 0xFE); LCD_Write(0xD12E, 0x03); LCD_Write(0xD12F, 0x10);
        LCD_Write(0xD130, 0x03); LCD_Write(0xD131, 0x33); LCD_Write(0xD132, 0x03);
        LCD_Write(0xD133, 0x6D); LCD_Write(0xD200, 0x00); LCD_Write(0xD201, 0x33);
        LCD_Write(0xD202, 0x00); LCD_Write(0xD203, 0x34); LCD_Write(0xD204, 0x00);
        LCD_Write(0xD205, 0x3A); LCD_Write(0xD206, 0x00); LCD_Write(0xD207, 0x4A);
        LCD_Write(0xD208, 0x00); LCD_Write(0xD209, 0x5C); LCD_Write(0xD20A, 0x00);
        LCD_Write(0xD20B, 0x81); LCD_Write(0xD20C, 0x00); LCD_Write(0xD20D, 0xA6);
        LCD_Write(0xD20E, 0x00); LCD_Write(0xD20F, 0xE5); LCD_Write(0xD210, 0x01);
        LCD_Write(0xD211, 0x13); LCD_Write(0xD212, 0x01); LCD_Write(0xD213, 0x54);
        LCD_Write(0xD214, 0x01); LCD_Write(0xD215, 0x82); LCD_Write(0xD216, 0x01);
        LCD_Write(0xD217, 0xCA); LCD_Write(0xD218, 0x02); LCD_Write(0xD219, 0x00);
        LCD_Write(0xD21A, 0x02); LCD_Write(0xD21B, 0x01); LCD_Write(0xD21C, 0x02);
        LCD_Write(0xD21D, 0x34); LCD_Write(0xD21E, 0x02); LCD_Write(0xD21F, 0x67);
        LCD_Write(0xD220, 0x02); LCD_Write(0xD221, 0x84); LCD_Write(0xD222, 0x02);
        LCD_Write(0xD223, 0xA4); LCD_Write(0xD224, 0x02); LCD_Write(0xD225, 0xB7);
        LCD_Write(0xD226, 0x02); LCD_Write(0xD227, 0xCF); LCD_Write(0xD228, 0x02);
        LCD_Write(0xD229, 0xDE); LCD_Write(0xD22A, 0x02); LCD_Write(0xD22B, 0xF2);
        LCD_Write(0xD22C, 0x02); LCD_Write(0xD22D, 0xFE); LCD_Write(0xD22E, 0x03);
        LCD_Write(0xD22F, 0x10); LCD_Write(0xD230, 0x03); LCD_Write(0xD231, 0x33);
        LCD_Write(0xD232, 0x03); LCD_Write(0xD233, 0x6D); LCD_Write(0xD300, 0x00);
        LCD_Write(0xD301, 0x33); LCD_Write(0xD302, 0x00); LCD_Write(0xD303, 0x34);
        LCD_Write(0xD304, 0x00); LCD_Write(0xD305, 0x3A); LCD_Write(0xD306, 0x00);
        LCD_Write(0xD307, 0x4A); LCD_Write(0xD308, 0x00); LCD_Write(0xD309, 0x5C);
        LCD_Write(0xD30A, 0x00); LCD_Write(0xD30B, 0x81); LCD_Write(0xD30C, 0x00);
        LCD_Write(0xD30D, 0xA6); LCD_Write(0xD30E, 0x00); LCD_Write(0xD30F, 0xE5);
        LCD_Write(0xD310, 0x01); LCD_Write(0xD311, 0x13); LCD_Write(0xD312, 0x01);
        LCD_Write(0xD313, 0x54); LCD_Write(0xD314, 0x01); LCD_Write(0xD315, 0x82);
        LCD_Write(0xD316, 0x01); LCD_Write(0xD317, 0xCA); LCD_Write(0xD318, 0x02);
        LCD_Write(0xD319, 0x00); LCD_Write(0xD31A, 0x02); LCD_Write(0xD31B, 0x01);
        LCD_Write(0xD31C, 0x02); LCD_Write(0xD31D, 0x34); LCD_Write(0xD31E, 0x02);
        LCD_Write(0xD31F, 0x67); LCD_Write(0xD320, 0x02); LCD_Write(0xD321, 0x84);
        LCD_Write(0xD322, 0x02); LCD_Write(0xD323, 0xA4); LCD_Write(0xD324, 0x02);
        LCD_Write(0xD325, 0xB7); LCD_Write(0xD326, 0x02); LCD_Write(0xD327, 0xCF);
        LCD_Write(0xD328, 0x02); LCD_Write(0xD329, 0xDE); LCD_Write(0xD32A, 0x02);
        LCD_Write(0xD32B, 0xF2); LCD_Write(0xD32C, 0x02); LCD_Write(0xD32D, 0xFE);
        LCD_Write(0xD32E, 0x03); LCD_Write(0xD32F, 0x10); LCD_Write(0xD330, 0x03);
        LCD_Write(0xD331, 0x33); LCD_Write(0xD332, 0x03); LCD_Write(0xD333, 0x6D);
        LCD_Write(0xD400, 0x00); LCD_Write(0xD401, 0x33); LCD_Write(0xD402, 0x00);
        LCD_Write(0xD403, 0x34); LCD_Write(0xD404, 0x00); LCD_Write(0xD405, 0x3A);
        LCD_Write(0xD406, 0x00); LCD_Write(0xD407, 0x4A); LCD_Write(0xD408, 0x00);
        LCD_Write(0xD409, 0x5C); LCD_Write(0xD40A, 0x00); LCD_Write(0xD40B, 0x81);
        LCD_Write(0xD40C, 0x00); LCD_Write(0xD40D, 0xA6); LCD_Write(0xD40E, 0x00);
        LCD_Write(0xD40F, 0xE5); LCD_Write(0xD410, 0x01); LCD_Write(0xD411, 0x13);
        LCD_Write(0xD412, 0x01); LCD_Write(0xD413, 0x54); LCD_Write(0xD414, 0x01);
        LCD_Write(0xD415, 0x82); LCD_Write(0xD416, 0x01); LCD_Write(0xD417, 0xCA);
        LCD_Write(0xD418, 0x02); LCD_Write(0xD419, 0x00); LCD_Write(0xD41A, 0x02);
        LCD_Write(0xD41B, 0x01); LCD_Write(0xD41C, 0x02); LCD_Write(0xD41D, 0x34);
        LCD_Write(0xD41E, 0x02); LCD_Write(0xD41F, 0x67); LCD_Write(0xD420, 0x02);
        LCD_Write(0xD421, 0x84); LCD_Write(0xD422, 0x02); LCD_Write(0xD423, 0xA4);
        LCD_Write(0xD424, 0x02); LCD_Write(0xD425, 0xB7); LCD_Write(0xD426, 0x02);
        LCD_Write(0xD427, 0xCF); LCD_Write(0xD428, 0x02); LCD_Write(0xD429, 0xDE);
        LCD_Write(0xD42A, 0x02); LCD_Write(0xD42B, 0xF2); LCD_Write(0xD42C, 0x02);
        LCD_Write(0xD42D, 0xFE); LCD_Write(0xD42E, 0x03); LCD_Write(0xD42F, 0x10);
        LCD_Write(0xD430, 0x03); LCD_Write(0xD431, 0x33); LCD_Write(0xD432, 0x03);
        LCD_Write(0xD433, 0x6D); LCD_Write(0xD500, 0x00); LCD_Write(0xD501, 0x33);
        LCD_Write(0xD502, 0x00); LCD_Write(0xD503, 0x34); LCD_Write(0xD504, 0x00);
        LCD_Write(0xD505, 0x3A); LCD_Write(0xD506, 0x00); LCD_Write(0xD507, 0x4A);
        LCD_Write(0xD508, 0x00); LCD_Write(0xD509, 0x5C); LCD_Write(0xD50A, 0x00);
        LCD_Write(0xD50B, 0x81); LCD_Write(0xD50C, 0x00); LCD_Write(0xD50D, 0xA6);
        LCD_Write(0xD50E, 0x00); LCD_Write(0xD50F, 0xE5); LCD_Write(0xD510, 0x01);
        LCD_Write(0xD511, 0x13); LCD_Write(0xD512, 0x01); LCD_Write(0xD513, 0x54);
        LCD_Write(0xD514, 0x01); LCD_Write(0xD515, 0x82); LCD_Write(0xD516, 0x01);
        LCD_Write(0xD517, 0xCA); LCD_Write(0xD518, 0x02); LCD_Write(0xD519, 0x00);
        LCD_Write(0xD51A, 0x02); LCD_Write(0xD51B, 0x01); LCD_Write(0xD51C, 0x02);
        LCD_Write(0xD51D, 0x34); LCD_Write(0xD51E, 0x02); LCD_Write(0xD51F, 0x67);
        LCD_Write(0xD520, 0x02); LCD_Write(0xD521, 0x84); LCD_Write(0xD522, 0x02);
        LCD_Write(0xD523, 0xA4); LCD_Write(0xD524, 0x02); LCD_Write(0xD525, 0xB7);
        LCD_Write(0xD526, 0x02); LCD_Write(0xD527, 0xCF); LCD_Write(0xD528, 0x02);
        LCD_Write(0xD529, 0xDE); LCD_Write(0xD52A, 0x02); LCD_Write(0xD52B, 0xF2);
        LCD_Write(0xD52C, 0x02); LCD_Write(0xD52D, 0xFE); LCD_Write(0xD52E, 0x03);
        LCD_Write(0xD52F, 0x10); LCD_Write(0xD530, 0x03); LCD_Write(0xD531, 0x33);
        LCD_Write(0xD532, 0x03); LCD_Write(0xD533, 0x6D); LCD_Write(0xD600, 0x00);
        LCD_Write(0xD601, 0x33); LCD_Write(0xD602, 0x00); LCD_Write(0xD603, 0x34);
        LCD_Write(0xD604, 0x00); LCD_Write(0xD605, 0x3A); LCD_Write(0xD606, 0x00);
        LCD_Write(0xD607, 0x4A); LCD_Write(0xD608, 0x00); LCD_Write(0xD609, 0x5C);
        LCD_Write(0xD60A, 0x00); LCD_Write(0xD60B, 0x81); LCD_Write(0xD60C, 0x00);
        LCD_Write(0xD60D, 0xA6); LCD_Write(0xD60E, 0x00); LCD_Write(0xD60F, 0xE5);
        LCD_Write(0xD610, 0x01); LCD_Write(0xD611, 0x13); LCD_Write(0xD612, 0x01);
        LCD_Write(0xD613, 0x54); LCD_Write(0xD614, 0x01); LCD_Write(0xD615, 0x82);
        LCD_Write(0xD616, 0x01); LCD_Write(0xD617, 0xCA); LCD_Write(0xD618, 0x02);
        LCD_Write(0xD619, 0x00); LCD_Write(0xD61A, 0x02); LCD_Write(0xD61B, 0x01);
        LCD_Write(0xD61C, 0x02); LCD_Write(0xD61D, 0x34); LCD_Write(0xD61E, 0x02);
        LCD_Write(0xD61F, 0x67); LCD_Write(0xD620, 0x02); LCD_Write(0xD621, 0x84);
        LCD_Write(0xD622, 0x02); LCD_Write(0xD623, 0xA4); LCD_Write(0xD624, 0x02);
        LCD_Write(0xD625, 0xB7); LCD_Write(0xD626, 0x02); LCD_Write(0xD627, 0xCF);
        LCD_Write(0xD628, 0x02); LCD_Write(0xD629, 0xDE); LCD_Write(0xD62A, 0x02);
        LCD_Write(0xD62B, 0xF2); LCD_Write(0xD62C, 0x02); LCD_Write(0xD62D, 0xFE);
        LCD_Write(0xD62E, 0x03); LCD_Write(0xD62F, 0x10); LCD_Write(0xD630, 0x03);
        LCD_Write(0xD631, 0x33); LCD_Write(0xD632, 0x03); LCD_Write(0xD633, 0x6D);
        /* LV2 Page 0 enable */
        LCD_Write(0xF000, 0x55); LCD_Write(0xF001, 0xAA); LCD_Write(0xF002, 0x52);
        LCD_Write(0xF003, 0x08); LCD_Write(0xF004, 0x00);
        /* Display control */
        LCD_Write(0xB100, 0xCC); LCD_Write(0xB101, 0x00);
        /* Source hold time */
        LCD_Write(0xB600, 0x05);
        /* Gate EQ control */
        LCD_Write(0xB700, 0x70); LCD_Write(0xB701, 0x70);
        /* Source EQ control (Mode 2) */
        LCD_Write(0xB800, 0x01); LCD_Write(0xB801, 0x03);
        LCD_Write(0xB802, 0x03); LCD_Write(0xB803, 0x03);
        /* Inversion mode (2-dot) */
        LCD_Write(0xBC00, 0x02); LCD_Write(0xBC01, 0x00); LCD_Write(0xBC02, 0x00);
        /* Timing control 4H w/ 4-delay */
        LCD_Write(0xC900, 0xD0); LCD_Write(0xC901, 0x02); LCD_Write(0xC902, 0x50);
        LCD_Write(0xC903, 0x50); LCD_Write(0xC904, 0x50); LCD_Write(0x3500, 0x00);
        LCD_Write(0x3A00, 0x55); //16-bit/pixel
        LCD_WriteCmd(0x1100);
        delay_us(120);
        LCD_WriteCmd(0x2900);
    }
    else
    {
        printf("Not support LCD IC: ");
        if(LCD_Configuration.id)
            printf("%x\r\n", LCD_Configuration.id);
        else
            printf("Unkown\r\n");
        return;
    }
    LCD_SetDirection(0);
    LCD_Configuration.bgColor = LCD_COLOR_WHITE;
    LCD_Backlight(ENABLE);
    LCD_Clear(LCD_Configuration.bgColor);
}


/**
 * @brief   Write data to the register
 * @param   reg: addr | cmd
 * @param   data
 * @retval  None
 */
//void LCD_Write(uint16_t addr, uint16_t data)
//{
//    *(uint16_t *)(LCD_CMD_ADDR) = addr;
//    *(uint16_t *)(LCD_DATA_ADDR) = data;
//}

/**
 * @brief    Read ID
 * @param    None
 * @retval   4 bit BCD code of IC ID
 */
uint8_t LCD_ReadID(void)
{
    /* NT35510 */
    LCD_Write(0xF000, 0x0055);
    LCD_Write(0xF001, 0x00AA);
    LCD_Write(0xF002, 0x0052);
    LCD_Write(0xF003, 0x0008);
    LCD_Write(0xF004, 0x0001);

    LCD_WriteCmd(0xC500);
    LCD_Configuration.id = LCD_ReadData()<<8;   //expect: 0x55
    LCD_WriteCmd(0xC501);
    LCD_Configuration.id |= LCD_ReadData();     //expect: 0x10
    if(LCD_Configuration.id==0x5510)
        return SUCCESS;

    /* NT35310 */
    LCD_WriteCmd(0xD4);
    LCD_Configuration.id = LCD_ReadData();
    LCD_Configuration.id = LCD_ReadData();

    LCD_Configuration.id = LCD_ReadData()<<8;   //expect: 0x53
    LCD_Configuration.id |= LCD_ReadData();     //expect: 0x10
    if(LCD_Configuration.id==0x5310)
        return ERROR;

    /* ILI9341 */
    LCD_WriteCmd(0XD3);				   
	LCD_Configuration.id = LCD_ReadData();
	LCD_Configuration.id = LCD_ReadData();

	LCD_Configuration.id = LCD_ReadData()<<8;   //expect: 0x93
	LCD_Configuration.id |= LCD_ReadData();     //expect: 0x41
    if(LCD_Configuration.id == 0x9341)
        return ERROR;

    /* ST7789 */
    LCD_WriteCmd(0X04);
    LCD_Configuration.id = LCD_ReadData();      //dummy read
    LCD_Configuration.id = LCD_ReadData();

    LCD_Configuration.id = LCD_ReadData()<<8;   //expect: 0x85
    LCD_Configuration.id |= LCD_ReadData();     //expect: 0x52
    if(LCD_Configuration.id == 0X8552)
    {
        LCD_Configuration.id = 0x7789;
        return ERROR;
    }
    
    /* SSD1963 */
    LCD_WriteCmd(0XA1);
    LCD_Configuration.id = LCD_ReadData();
    LCD_Configuration.id = LCD_ReadData()<<8;   //expect: 0x57
    LCD_Configuration.id |= LCD_ReadData();     //expect: 0x61
    if(LCD_Configuration.id == 0X5761)
    {
        LCD_Configuration.id = 0X1963;
        return ERROR;
    }
    LCD_Configuration.id = 0;
    return ERROR;
}

/**
 * @brief   Set window/display area
 * @param   startX, startY / left-top
 * @param   endX, endY / right-bottom
 * @retval  None
 */
void LCD_SetWindow(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY)
{
    LCD_Write(LCD_SETX_CMD,     startX >> 8);
    LCD_Write(LCD_SETX_CMD + 1, startX & 0xff);
    LCD_Write(LCD_SETX_CMD + 2,  endX  >> 8);
    LCD_Write(LCD_SETX_CMD + 3,  endX  & 0xff);

    LCD_Write(LCD_SETY_CMD,     startY >> 8);
    LCD_Write(LCD_SETY_CMD + 1, startY & 0xff);
    LCD_Write(LCD_SETY_CMD + 2,  endY  >> 8);
    LCD_Write(LCD_SETY_CMD + 3,  endY  & 0xff);
}

/**
 * @brief   Set the screen scan mode
 * @param   mode: LCD_Scan_Mode macro
 * @retval  None
 */
void LCD_SetScanMode(LCD_Scan_Mode mode)
{
    uint16_t temp = 0;

    switch(mode)
    {
        case _LR_UD: temp |= 0<<5 | 0<<6 | 0<<7; break;
        case _LR_DU: temp |= 0<<5 | 0<<6 | 1<<7; break;
        case _RL_UD: temp |= 0<<5 | 1<<6 | 0<<7; break;
        case _RL_DU: temp |= 0<<5 | 1<<6 | 1<<7; break;
        case _UD_LR: temp |= 1<<5 | 0<<6 | 0<<7; break;
        case _DU_LR: temp |= 1<<5 | 0<<6 | 1<<7; break;
        case _UD_RL: temp |= 1<<5 | 1<<6 | 0<<7; break;
        case _DU_RL: temp |= 1<<5 | 1<<6 | 1<<7; break;
    }
    LCD_Write(0x3600, temp);

    /* ½»»»x, y×ø±ê */
    if(temp&0x20)
    {
        if(LCD_Configuration.width < LCD_Configuration.height)
        {
            temp = LCD_Configuration.width;
            LCD_Configuration.width = LCD_Configuration.height;
            LCD_Configuration.height = temp;
        }
    }
    else
    {
        if(LCD_Configuration.width > LCD_Configuration.height)
        {
            temp = LCD_Configuration.width;
            LCD_Configuration.width = LCD_Configuration.height;
            LCD_Configuration.height = temp;
        }
    }
    LCD_SetWindow(0, 0, LCD_Configuration.width-1, LCD_Configuration.height-1);
}

/**
 * @brief   Set display direction
 * @param   0: portrait | 1: inverse portrait
 * @param   2: landscape toward left | 3: landscape toward right
 * @retval  None
 */
void LCD_SetDirection(uint8_t NewDirection)
{
    if(NewDirection>>1) /* ºáÆÁ */
    {
        LCD_Configuration.width = LCD_HEIGHT;
        LCD_Configuration.height = LCD_WIDTH;
    }
    else /* ÊúÆÁ */
    {
        LCD_Configuration.width = LCD_WIDTH;
        LCD_Configuration.height = LCD_HEIGHT;
    }
    LCD_Configuration.direction = NewDirection;
    
    switch(NewDirection)
    {
        case 0: LCD_SetScanMode(_LR_UD); break;
        case 1: LCD_SetScanMode(_RL_DU); break;
        case 2: LCD_SetScanMode(_DU_LR); break;
        case 3: LCD_SetScanMode(_UD_RL); break;
    }
}

/**
 * @brief   Set display cursor
 * @param   corordinate of cursor
 * @retval  None
 */
void LCD_SetCursor(uint16_t x, uint16_t y)
{
    LCD_Write(LCD_SETX_CMD,     x >> 8);
    LCD_Write(LCD_SETX_CMD + 1, x & 0xff);
    LCD_Write(LCD_SETY_CMD,     y >> 8);
    LCD_Write(LCD_SETY_CMD + 1, y & 0xff);
}

/**
 * @brief   Fill the FULLSCREEN with color / Clear screen
 * @param   color: RGB 565 code
 * @retval  None
 */
void LCD_Clear(uint16_t color)
{
    uint32_t points = LCD_Configuration.width * LCD_Configuration.height;

    LCD_SetCursor(0, 0);
    LCD_WriteCmd(LCD_WRGRAM_CMD);

    while(points --> 0)
        LCD_WriteData(color);

    LCD_Configuration.bgColor = color;
    /* ×Ô¶¯ÉèÖÃ»­±ÊÑÕÉ« */
    LCD_Configuration.penColor = ~color;
    if((LCD_Configuration.penColor>>11 > 0xf && (LCD_Configuration.penColor>>5&0x3f) > 0x1f) ||
       (LCD_Configuration.penColor>>11 > 0xf && (LCD_Configuration.penColor   &0x1f) > 0xf ) ||
      ((LCD_Configuration.penColor>>5&0x3f) > 0x1f && (LCD_Configuration.penColor&0x1f) > 0xf))
        LCD_Configuration.penColor = LCD_COLOR_WHITE;
    else
        LCD_Configuration.penColor = LCD_COLOR_BLACK;
}

/**
 * @brief   local draw point
 * @param   x|y: corordinate of point
 * @param   color: RGB 565 code
 * @retval  None
 */
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetCursor(x, y);
    LCD_Write(LCD_WRGRAM_CMD, color);
}

/**
 * @brief   Fill the specified area with color
 * @param   startX, startY: The coordinates of the top left corner
 * @param   endX, endY: The coordinates of the bottom right corner
 * @param   color: RGB 565 code
 * @retval  None
 */
void LCD_Fill(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color)
{
    uint16_t hlineLength;

    while(startY <= endY)
    {
        hlineLength = endX - startX;
        LCD_SetCursor(startX, startY++);
        LCD_WriteCmd(LCD_WRGRAM_CMD);

        while(hlineLength --> 0)
            LCD_WriteData(color);
    }
}


/**
 * @brief   print a character on screen
 * @param   x|y: corordinate of cursor
 * @param   ch: valid ASCII character
 * @param   size 12|16|24
 * @retval  None
 */
void LCD_Putchar(uint16_t x, uint16_t y, char ch, uint8_t size)
{
    uint8_t temp, i, j;
    uint16_t y0 = y;
    uint8_t charSetsize = (size/8 + (size%8 != 0)) * (size/2);

    assert_param(x<LCD_Configuration.width-size && y<LCD_Configuration.height-size);
    assert_param(size==12 || size==16 || size==24);
    assert_param(ch>=' ' && ch<='~');
    ch -= ' ';

    for(i = 0; i < charSetsize; i++)
    {
        switch(size)
        {
            case 12: temp = asc2_1206[ch][i]; break;
            case 16: temp = asc2_1608[ch][i]; break;
            case 24: temp = asc2_2412[ch][i]; break;
        }
        for(j = 0; j < 8; j++)
        {
            if(temp&0x80)
                LCD_DrawPoint(x, y, LCD_Configuration.penColor);
            else
                LCD_DrawPoint(x, y, LCD_Configuration.bgColor);
            temp <<= 1;
            
            if(y++ >= LCD_Configuration.height)
                return;
            if(y-y0 == size)
            {
                y = y0;
                if(x++ >= LCD_Configuration.width)
                    return;
                break;
            }
        }
    }
}

/**
 * @brief   print a string on screen
 * @param   startX/startY: corordinate of start point
 * @param   linechars: The number of characters in a line
 * @param   line: maximum number of lines alowed
 * @retval  None
 */
void LCD_Puts(uint16_t startX, uint16_t startY, uint16_t linechars, uint16_t line, uint8_t size, char *p)
{
    uint16_t x = startX, y = startY;

    while ((*p <= '~') && (*p >= ' '))
    {
        if (x >= startX + size*linechars)
        {
            x = startX;
            y += size;
        }

        if (y >= startY + size*line)
            break;

        LCD_Putchar(x, y, *p++, size);
        x += size / 2;
    }
}

/* Touch functions based on IIC3 ---------------------------------------------*/
uint8_t LCD_Touch_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    IIC_Touch.SCL_Port = GPIOB;
    IIC_Touch.SDA_Port = GPIOF;
    IIC_Touch.SCL_Pin = GPIO_Pin_1;
    IIC_Touch.SDA_Pin = GPIO_Pin_9;

    GPIO_ResetBits(GPIOF, GPIO_Pin_11);
    delay_ms(10);
    GPIO_SetBits(GPIOF, GPIO_Pin_11);
    delay_ms(10);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_SetBits(GPIOF, GPIO_Pin_10);

    return 0;
}


uint8_t LCD_TouchScan(void)
{
    uint8_t buffer[4], temp[3] = {0};
    uint8_t i, flag = 0;
    static uint8_t t = 0;
    
    t++;
    if(t%10==0 || t<10)
    {
        temp[0] = IIC_Read(&IIC_Touch, GT9147_ADDR, GT9147_GSTID);

        if(temp[0]&0x80 && (temp[0]&0xF)<6)
            IIC_Write(&IIC_Touch, GT9147_ADDR, GT9147_GSTID, 0);
        
        if(temp[0]&0xf && (temp[0]&0xF)<6)
        {
            temp[1] = 0xff<<(temp[0]&0xf);
            temp[2] = LCD_Configuration.touchState;

            LCD_Configuration.touchState = (~temp[1])|LCD_PRESS_DOWN|LCD_CATCH_PRESS;
            LCD_Configuration.x[4] = LCD_Configuration.x[0];
            LCD_Configuration.y[4] = LCD_Configuration.y[0];

            for(i=0; i<5; i++)
            {
                if(LCD_Configuration.touchState&(1<<i))
                {
                    IIC_ReadBytes(&IIC_Touch, GT9147_ADDR, GT9147_TouchxAddress[i], buffer, 4);
                    switch(LCD_Configuration.direction)
                    {
                        case 0:
                            LCD_Configuration.x[i] = ((uint16_t)buffer[1]<<8) + buffer[0];
                            LCD_Configuration.y[i] = ((uint16_t)buffer[3]<<8) + buffer[2];
                            break;
                        case 1:
                            LCD_Configuration.x[i] = LCD_Configuration.width - ((uint16_t)buffer[1]<<8) - buffer[0];
                            LCD_Configuration.y[i] = LCD_Configuration.height - ((uint16_t)buffer[3]<<8) - buffer[2];
                            break;
                        case 2:
                            LCD_Configuration.y[i] = ((uint16_t)buffer[1]<<8) + buffer[0];
                            LCD_Configuration.x[i] = LCD_Configuration.width - ((uint16_t)buffer[3]<<8) - buffer[2];
                            break;
                        case 3:
                            LCD_Configuration.y[i] = LCD_Configuration.height - ((uint16_t)buffer[1]<<8) - buffer[0];
                            LCD_Configuration.x[i] = ((uint16_t)buffer[3]<<8) + buffer[2];
                    }
                }
            }
            flag++;
            /* invalid data */
            if(LCD_Configuration.x[0]>LCD_Configuration.width || LCD_Configuration.y[0]>LCD_Configuration.height)
            {
                if((temp[0]&0xf)>1)
                {
                    LCD_Configuration.x[0] = LCD_Configuration.x[1];
                    LCD_Configuration.y[0] = LCD_Configuration.y[1];
                    t = 0;
                }
                else
                {
                    LCD_Configuration.x[0] = LCD_Configuration.x[4];
                    LCD_Configuration.y[0] = LCD_Configuration.y[4];
                    temp[0] = 0x80;
                    LCD_Configuration.touchState = temp[2];
                }
            }
            else
                t = 0;
        }
    }
    if((temp[0]&0x8f)==0x80)
    {
        if(LCD_Configuration.touchState&LCD_PRESS_DOWN)
            LCD_Configuration.touchState &= ~(1<<7);
        else
        {
            LCD_Configuration.x[0] = 0xffff;
            LCD_Configuration.y[0] = 0xffff;
            LCD_Configuration.touchState &= 0xe0;
        }
    }
    if(t>240)
        t = 10;
    return flag;
}

void LCD_PaintClear(void)
{
    LCD_Clear(LCD_COLOR_WHITE);
    LCD_Puts(LCD_Configuration.width-54, 10, sizeof("Clear"), 1, 16, "Clear");
}


void LCD_PaintPoint(uint16_t centerX, uint16_t centerY, uint16_t radius, uint16_t color)
{
    uint32_t i, x = radius;
    uint32_t i_max = (uint32_t)radius * 707 / 1000 + 1;
    uint32_t sq_max = (uint32_t)radius * (uint32_t)radius + (uint32_t)(radius>>1);
    /* Paint horizen lines: endX = startX + len - 1 */
    LCD_Fill(centerX-radius, centerY, centerX+radius-1, centerY, color); //len = radius * 2

    for(i=1; i<=i_max; i++)
    {
        if(i*i+x*x>sq_max)
        {
            if(x>i_max)
            {
                /* len = i-1 <<1, x*2==x<<1 */
                LCD_Fill(centerX-i+1, centerY+x, centerX+i-2, centerY+x, color);
                LCD_Fill(centerX-i+1, centerY-x, centerX+i-2, centerY-x, color);
            }
            x--;
        }
        /* len = x * 2 , draw lines from inside */
        LCD_Fill(centerX-x, centerY+i, centerX+x-1, centerY+i, color);
        LCD_Fill(centerX-x, centerY-i, centerX+x-1, centerY-i, color);
    }
}

void LCD_PaintLine(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t size, uint16_t color)
{
    uint16_t i;
    int xErr = 0, yErr = 0, deltaX = endX-startX, deltaY = endY-startY, distance;
    int incX, incY, uRow = startX, uCol = startY;

    if(startX<size || startY<size || endX<size || endY<size)
        return;

    if(deltaX>0)
        incX = 1;
    else if(deltaX==0)
        incX = 0;
    else
    {
        incX = -1;
        deltaX *= -1;
    }

    if(deltaY>0)
        incY = 1;
    else if(deltaY==0)
        incY = 0;
    else
    {
        incY = -1;
        deltaY *= -1;
    }

    distance = deltaX>deltaY ? deltaX:deltaY;
    for(i=0; i<=distance+1; i++)
    {
        LCD_PaintPoint(uRow, uCol, size, color);
        xErr += deltaX;
        yErr += deltaY;
        if(xErr>distance)
        {
            xErr -= distance;
            uRow += incX;
        }
        if(yErr>distance)
        {
            yErr -= distance;
            uCol += incY;
        }
    }
}

/* Test functions ------------------------------------------------------------*/
/**
  * @brief  LCD display test function.
  * @param  None
  * @retval None
  */
void LCD_Display_Test(void)
{
    uint8_t i = 0;
    char lcd_id[12];
    sprintf(lcd_id, "LCD id: %x", LCD_Configuration.id);
    while(1)
    {
        switch(i)
		{
			case 0: LCD_Clear(LCD_COLOR_WHITE);  break;
			case 1: LCD_Clear(LCD_COLOR_RED);    break;
			case 2: LCD_Clear(LCD_COLOR_GREEN);  break;
			case 3: LCD_Clear(LCD_COLOR_BLUE);   break;
            case 4: LCD_Clear(LCD_COLOR_YELLOW); break;
            case 5: LCD_Clear(LCD_COLOR_PINK);   break;
            case 6: LCD_Clear(LCD_COLOR_CYAN);   break;
			case 7: LCD_Clear(LCD_COLOR_BLACK);  break;
		}

        if(LCD_Configuration.direction/2==0)
        {
            LCD_Puts(90, 10, sizeof("STM32F103ZET6 TFT-LCD Test"), 1, 24, "STM32F103ZET6 TFT-LCD Test"); 
            LCD_Puts(160, 50, sizeof("Hello, world!"), 1, 24, "Hello, world!");
            LCD_Puts(10, 775, sizeof(lcd_id), 1, 16, lcd_id);      					 
            LCD_Puts(410, 780, sizeof("2022/2/11"), 1, 12, "2022/2/11");
        }
        else
        {
            LCD_Puts(250, 10, sizeof("STM32F103ZET6 TFT-LCD Test"), 1, 24, "STM32F103ZET6 TFT-LCD Test"); 
            LCD_Puts(320, 50, sizeof("Hello, world!"), 1, 24, "Hello, world!");
            LCD_Puts(10, 455, sizeof(lcd_id), 1, 16, lcd_id);      					 
            LCD_Puts(730, 460, sizeof("2022/2/11"), 1, 12, "2022/2/11");
        }
		   		 
		delay_ms(1000);
        if(++i==8)
            break;
    }
}

/**
  * @brief  LCD touch test function.
  * @param  None
  * @retval None
  */
void LCD_Paint(void)
{
    uint8_t i;
    uint16_t lastData[5][2];
    
    LCD_PaintClear();
    while(1)
    {
        LCD_TouchScan();
        for(i=0; i<5; i++)
        {
            if(LCD_Configuration.touchState & (1<<i))
            {
                if(LCD_Configuration.x[i]<LCD_Configuration.width && LCD_Configuration.y[i]<LCD_Configuration.height)
                {
                    if(lastData[i][0]==0xffff)
                    {
                        lastData[i][0] = LCD_Configuration.x[i];
                        lastData[i][1] = LCD_Configuration.y[i];
                    }

                    LCD_PaintLine(lastData[i][0], lastData[i][1],
                                  LCD_Configuration.x[i], LCD_Configuration.y[i], 2, PaintBrushColor[i]);
                    lastData[i][0] = LCD_Configuration.x[i];
                    lastData[i][1] = LCD_Configuration.y[i];

                    if(LCD_Configuration.x[i]>(LCD_Configuration.width-54) && LCD_Configuration.y[i]<26)
                        LCD_PaintClear();
                }
            }
            else
                lastData[i][0] = 0xffff;
        }
        delay_ms(5);
    }
}
/******************************** END OF FILE *********************************/
