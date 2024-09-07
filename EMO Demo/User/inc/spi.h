/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

void SPI_Config(void);
void SPI_SendByte(SPI_TypeDef* SPIx, uint8_t data);

#endif /* __SPI_H */
/******************************** END OF FILE *********************************/
