#pragma once

// Copy this in the project part, not here.

#include "stm32f0xx_hal.h"
// Change this to your project include. e.g. stm33l1xx_hal.h

#define CLK_PORT GPIOC
#define DIO_PORT GPIOC
#define CLK_PIN GPIO_PIN_0
#define DIO_PIN GPIO_PIN_1
#define CLK_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define DIO_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE


