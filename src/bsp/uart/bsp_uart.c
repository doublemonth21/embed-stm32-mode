#include "bsp_uart.h"

#include <stdio.h>

UART_HandleTypeDef huart1;
uint8_t u1_recv_buff[USART1_RECEIVE_LENGTH];
uint16_t u1_recv_length;
uint8_t u1_recv_flag;

void uart1_init(uint32_t baud)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = baud;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }

    __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

#if !defined(__MICROLIB)
#if (__ARMCLIB_VERSION <= 6000000)
struct __FILE {
    int handle;
};
#endif
FILE __stdout;
void _sys_exit(int x)
{
    (void)x;
}
#endif

int fputc(int ch, FILE *f)
{
    uint8_t data = (uint8_t)ch;
    (void)f;
    HAL_UART_Transmit(&huart1, &data, 1U, HAL_MAX_DELAY);
    return ch;
}

void uart1_receive_clear(void)
{
    u1_recv_length = 0U;
    u1_recv_flag = 0U;
}

uint8_t *uart1_get_data(void)
{
    if (u1_recv_flag == 1U) {
        uart1_receive_clear();
        return u1_recv_buff;
    }

    return NULL;
}

void USART1_IRQHandler(void)
{
    if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET) &&
        (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_RXNE) != RESET)) {
        uint8_t data = (uint8_t)(huart1.Instance->DR & 0x00FFU);
        if (u1_recv_length < (USART1_RECEIVE_LENGTH - 1U)) {
            u1_recv_buff[u1_recv_length++] = data;
        }
    }

    if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET) &&
        (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_IDLE) != RESET)) {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        u1_recv_buff[u1_recv_length] = '\0';
        u1_recv_flag = 1U;
    }
}
