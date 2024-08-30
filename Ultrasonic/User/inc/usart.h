/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"

void USART1_Init(uint32_t baudRate);

#ifdef EN_USART1_RX
    #define USART_RX_MAX    200     //最大接收字节数
    extern uint8_t USART_RX_Buffer[];
    extern uint16_t USART_RX_Data;
    void COM_SendString(uint8_t sec);
#endif /* EN_USART1_RX */

#endif  /* __USART_H */
/******************************** END OF FILE *********************************/
