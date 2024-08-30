/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IIC_H
#define __IIC_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    GPIO_TypeDef *SCL_Port, *SDA_Port;
    uint16_t SCL_Pin, SDA_Pin;
} IIC_TypeDef;
extern IIC_TypeDef IIC2;
/* Private define ------------------------------------------------------------*/
#define ACK     Bit_RESET
#define NACK    Bit_SET

#define IIC_SDA_Mode        GPIOMode_TypeDef
#define IIC_SDA_Mode_Out    GPIO_Mode_Out_PP
#define IIC_SDA_Mode_IN     GPIO_Mode_IPU

/* Private function prototypes -----------------------------------------------*/
void IIC_GenerateSTART(IIC_TypeDef* IICx);
void IIC_GenerateSTOP(IIC_TypeDef* IICx);
void IIC_SendData(IIC_TypeDef* IICx, uint8_t data);
uint8_t IIC_ReceiveData(IIC_TypeDef* IICx, BitAction ACK_State);

uint8_t IIC_Read(IIC_TypeDef* IICx ,uint8_t slaveAddr, uint8_t regAddr);
uint8_t IIC_Write(IIC_TypeDef* IICx ,uint8_t slaveAddr, uint8_t regAddr, uint8_t data);
uint8_t IIC_ReadBytes(IIC_TypeDef* IICx, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint8_t len);
uint8_t IIC_WriteBytes(IIC_TypeDef* IICx, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint8_t len);

#endif /* __IIC_H */
/******************************** END OF FILE *********************************/
