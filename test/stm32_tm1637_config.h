#pragma once

#include "stdio.h"
#include "stdint.h"

#define CLK_PORT "GPIOC"
#define DIO_PORT "GPIOC"
#define CLK_PIN "GPIO_PIN_0"
#define DIO_PIN "GPIO_PIN_1"
#define CLK_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define DIO_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define GPIO_PIN_RESET "GPIO_PIN_RESET"
#define GPIO_PIN_SET "GPIO_PIN_SET"

#define  GPIO_PULLUP "PULLUP"
#define GPIO_MODE_OUTPUT_OD "ODE_OUTPUT_OD"
#define GPIO_SPEED_FREQ_VERY_HIGH "SPEED_FREQ_VERY_HIGH"

#define POORTEST 1

 typedef struct
 {
   char* Pin;
   char* Mode;
   char* Speed;
   char* OutputType;
   char* Pull;
   char* Alternate;
 } GPIO_InitTypeDef;


void HAL_GPIO_Init(char* c, GPIO_InitTypeDef *g);
void HAL_GPIO_WritePin(char *c1, char *c2, char *c3);
void __HAL_RCC_GPIOC_CLK_ENABLE();
