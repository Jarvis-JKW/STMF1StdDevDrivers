/**
  ******************************************************************************
  * @file    /Hardware/src/dht11.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    2022年7月26日
  * @brief   温湿度传感器
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "dht11.h"

static uint8_t time = 0;
/**
  * @brief  DHT11 I/O set program.
  * @param  mode: GPIO_Mode_Out_PP | GPIO_Mode_IPU
  * @retval None
  */
static void DHT11_Mode(GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if(mode==GPIO_Mode_Out_PP)
    {
        GPIO_InitStructure.GPIO_Pin = DHT11_Pin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else
    {
        GPIO_InitStructure.GPIO_Pin = DHT11_Pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    }

    GPIO_Init(DHT11_Port, &GPIO_InitStructure);
}


/**
  * @brief  DHT11 Start Signal.
  * @param  None
  * @retval None
  */
void DHT11_Start(void)
{
    DHT11_Mode(GPIO_Mode_Out_PP);

    GPIO_ResetBits(DHT11_Port, DHT11_Pin);
    delay_ms(20);

    GPIO_SetBits(DHT11_Port, DHT11_Pin);
    delay_us(30);
}


/**
  * @brief  DHT11 Check.
  * @param  None
  * @retval SUCCESS | ERROR
  */
uint8_t DHT11_Check(void)
{
    DHT11_Mode(GPIO_Mode_IPU);
    
    while((GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin)==RESET) && (time<100))
    {
        time++;
        delay_us(1);
    }
    
    if(time < 100)
        time = 0;
    else
    {
        time = 0;
        return ERROR; //Time out
    }
    
    while((GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin)==SET) && (time<100))
    {
        time++;
        delay_us(1);
    }
    if(time < 100)
        time = 0;
    else
    {
        time = 0;
        return ERROR; //Time out
    }
    return SUCCESS;
}


/**
  * @brief  DHT11 read a byte.
  * @param  None
  * @retval data | ERROR
  */
uint8_t DHT11_ReadByte(void)
{
    uint8_t data = 0, i = 8;
    
    while(i-->0)
    {
        data <<= 1;
        while((GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin)!=RESET) && (time<100))
        {
            time++;
            delay_us(1);
        }
        time = 0;
        
        /* start to transmit 1-bit data(50us) */
        while((GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin)==RESET) && (time<55))
        {
            time++;
            delay_us(1);
        }
        if(time < 55)
            time = 0;
        else
        {
            time = 0;
            return ERROR;
        }
        delay_us(40);
        data |= GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin);
    }
    return data;
}


/**
  * @brief  DHT11 Update data.
  * @param  data pointer
  * @retval SUCCESS | ERROR
  */
uint8_t DHT11_Update(uint8_t *temp, uint8_t *humi)
{
    uint8_t i, data[5];
    
    DHT11_Start();
    if(DHT11_Check()!=ERROR)
    {
        for(i = 0; i < 5; i++)
        {
            data[i] = DHT11_ReadByte();
        }
        delay_us(55);
        /* humi(int) humi(dec) temp(int) temp(dec) val */
        if((data[0]+data[1]+data[2]+data[3])==data[4])
        {
            *humi = data[0];
            *temp = data[2];
        }
        else
        {
            for(i = 0; i < 5; i++)
            {
                data[i] = 0;
            }
            return ERROR;
        }
    }
    else
        return ERROR;
    return SUCCESS;
}
/******************************** END OF FILE *********************************/
