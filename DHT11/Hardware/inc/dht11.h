/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"

void DHT11_Start(void);
uint8_t DHT11_Check(void);
uint8_t DHT11_ReadByte(void);
uint8_t DHT11_Update(uint8_t *temp, uint8_t *humi);


#endif	/* __DHT11_H */
/******************************** END OF FILE *********************************/
