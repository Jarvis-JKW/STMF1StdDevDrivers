/**
  ******************************************************************************
  * @file    /Hardware/src/digitaltube.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    29-May-2022
  * @brief   LED program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * To display numbers with CA digital tube(s).
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "digitaltube.h"

static const uint8_t NumTable[] = {0x77, 0x14, 0xb3, 0xb6, //0 ~ 3
                                   0xd4, 0xe6, 0xe7, 0x34, //4 ~ 7
                                   0xf7, 0xf6, 0xf5, 0xc7, //8 ~ b
                                   0x63, 0x97, 0xe3, 0xe1};//c ~ f

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  7 seg Common Anode digital display program.
  * @param  0-15
  * @ret    None
  */
void DT_Show(uint8_t num)
{
    uint16_t temp = GPIO_ReadOutputData(DT_Port);

    temp &= 0xff00;
    temp |= (~NumTable[num])&0xff;
    GPIO_Write(GPIOF, temp);
}


void DT_ShowNums(uint8_t *data)
{
    uint8_t i;
    
    for(i = 0; i < 8; i++)
    {
        GPIO_SetBits(CS_Port, CS_Pin_1<<i);
        DT_Show(data[i]);
        delay_us(500);
        GPIO_ResetBits(CS_Port, CS_Pin_1<<i);
    }
}


/******************************** END OF FILE *********************************/
