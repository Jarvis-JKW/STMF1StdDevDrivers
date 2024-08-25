/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

#include "main.h"


void USART1_Init(uint32_t baudRate);

#ifdef EN_USART1_RX
#define USART_RX_MAX 200
#endif /* EN_USART1_RX */


#endif  /* __USART_H */
/******************************** END OF FILE *********************************/
