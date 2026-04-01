#ifndef __STM32F1XX_HAL_CONF_H
#define __STM32F1XX_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED

#define HSE_VALUE    8000000U
#define HSI_VALUE    8000000U
#define LSI_VALUE    40000U
#define LSE_VALUE    32768U
#define HSE_STARTUP_TIMEOUT    100U
#define LSE_STARTUP_TIMEOUT    5000U
#define VDD_VALUE    3300U
#define TICK_INT_PRIORITY    0x0FU
#define USE_RTOS    0U
#define PREFETCH_ENABLE    1U
#define FLASH_LATENCY_0    0U
#define FLASH_LATENCY_1    FLASH_ACR_LATENCY_0
#define FLASH_LATENCY_2    FLASH_ACR_LATENCY_1

#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_cortex.h"
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_pwr.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_spi.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef USE_FULL_ASSERT
#include "stm32_assert.h"
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif

#ifdef __cplusplus
}
#endif

#endif
