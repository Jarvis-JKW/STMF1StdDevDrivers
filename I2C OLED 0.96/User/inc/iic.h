/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IIC_H
#define __IIC_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

void I2C_Config(void);

uint8_t I2C_Write(I2C_TypeDef* I2Cx ,uint8_t slaveAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C_WriteBytes(I2C_TypeDef* I2Cx, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint8_t len);

#endif /* __IIC_H */
/******************************** END OF FILE *********************************/
