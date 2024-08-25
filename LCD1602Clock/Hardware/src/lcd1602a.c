/**
  ******************************************************************************
  * @file    /Hardware/src/lcd1602a.c 
  * @author  Jarvis-JKW
  * @version V0.0.1
  * @date    23-Jan-2022
  * @brief   LCD1602A program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "lcd1602a.h"
#include "rtc.h" 

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  LCD1602A Write program.
  * @note   分两次传送数据，低四位强制置为0100或0101
  * @retval None
  */
void LCD1602A_Write(LCD_Write_Mode mode, uint8_t data)
{
    GPIO_Write(LCD_Port, (data|0x0f)&0xf4+mode);   //写入高四位
    delay_ms(1);

    GPIO_Write(LCD_Port, 0x00);                    //锁定数据
    delay_ms(1);

    GPIO_Write(LCD_Port, (data<<4|0x0f)&0xf4+mode);//写入低四位
    delay_ms(1);

    GPIO_Write(LCD_Port, 0x00);                    //锁定数据
    delay_ms(1);
}

/**
  * @brief  LCD1602A send string.
  * @param  addr: 0x80 + offset | 0xa0 + offset
  * @retval None
  */
void LCD1602A_Sendstr(uint8_t addr, uint8_t len, uint8_t *data)
{
    uint8_t i;

    LCD1602A_Write(LCD1602_CMD, addr);

    for(i=1; i<len; i++)
        LCD1602A_Write(LCD1602_DATA, *data++);
}


/**
  * @brief  LCD1602A send number.
  * @param  addr: 0x80 + offset | 0xa0 + offset
  * @param  num: the number no longer than 10000
  * @retval None
  */
void LCD1602A_Sendnum(uint8_t addr, uint16_t num)
{
    uint8_t i=0, str[5];

    LCD1602A_Write(LCD1602_CMD, addr);

    if(num==0)
        LCD1602A_Write(LCD1602_DATA, '0');

    /* convert number to character */
    while(num)
    {
        str[i++] = num % 10 + '0';
        num /= 10;
    }
    while(i--)
        LCD1602A_Write(LCD1602_DATA, str[i]);
}

/**
  * @brief  LCD1602A Clock.
  * @param  None
  * @retval None
  */
void LCD1602A_Clock(void)
{
    uint8_t t;

    LCD1602A_Sendstr(0x82, sizeof("Hello, world!"), (uint8_t *)"Hello, World!");
    delay_s(2);
    LCD1602A_Write(LCD1602_CMD, 0x01);
    
    
    LCD1602A_Sendstr(0x80+7, sizeof("-"), (uint8_t *)"-");
    LCD1602A_Sendstr(0x80+10, sizeof("-"), (uint8_t *)"-");

    

    while(1)
    {
        if(t!=CAL_Structure.ss)
        {
            t = CAL_Structure.ss;
            
            LCD1602A_Sendnum(0x80+3, CAL_Structure.yyyy);
            if(CAL_Structure.MM<10)
            {
                LCD1602A_Sendnum(0x80+8, 0);
                LCD1602A_Sendnum(0x80+9, CAL_Structure.MM);
            }
            else
                LCD1602A_Sendnum(0x80+8, CAL_Structure.MM);

            if(CAL_Structure.dd<10)
            {
                LCD1602A_Sendnum(0x80+11, 0);
                LCD1602A_Sendnum(0x80+12, CAL_Structure.dd);
            }
            else
                LCD1602A_Sendnum(0x80+11, CAL_Structure.dd);
            
            if(CAL_Structure.HH<10)
            {
                LCD1602A_Sendstr(0xc0+4, sizeof(" "), (uint8_t *)" ");
                LCD1602A_Sendnum(0xc0+5, CAL_Structure.HH);
            }
            else
                LCD1602A_Sendnum(0xc0+4, CAL_Structure.HH);

            if(CAL_Structure.mm<10)
            {
                LCD1602A_Sendnum(0xc0+7, 0);
                LCD1602A_Sendnum(0xc0+8, CAL_Structure.mm);
            }
            else
                LCD1602A_Sendnum(0xc0+7, CAL_Structure.mm);

            if(CAL_Structure.ss<10)
            {
                LCD1602A_Sendnum(0xc0+10, 0);
                LCD1602A_Sendnum(0xc0+11, CAL_Structure.ss);
            }
            else
                LCD1602A_Sendnum(0xc0+10, CAL_Structure.ss);

        }
        if(t%2)
        {
            LCD1602A_Sendstr(0xc0+6, sizeof(":"), (uint8_t *)":");
            LCD1602A_Sendstr(0xc0+9, sizeof(":"), (uint8_t *)":");
        }
        else
        {
            LCD1602A_Sendstr(0xc0+6, sizeof(" "), (uint8_t *)" ");
            LCD1602A_Sendstr(0xc0+9, sizeof(" "), (uint8_t *)" ");
        }
        delay_ms(200);
    }
}

/******************************** END OF FILE *********************************/
