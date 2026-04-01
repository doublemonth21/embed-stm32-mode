#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "main.h"

#define USART1_RECEIVE_LENGTH 1024

extern UART_HandleTypeDef huart1;
extern uint8_t u1_recv_buff[USART1_RECEIVE_LENGTH];
extern uint16_t u1_recv_length;
extern uint8_t u1_recv_flag;

void uart1_init(uint32_t baud);
void USART1_IRQHandler(void);
void uart1_receive_clear(void);
uint8_t *uart1_get_data(void);

#endif
