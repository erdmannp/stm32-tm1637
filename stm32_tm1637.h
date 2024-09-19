#pragma once

#include "stm32_tm1637_config.h"

void tm1637Init(void);
void tm1637DisplayDecimal(int v, int displaySeparator);
void tm1637SetBrightness(char brightness);
void tm1637DisplayTwoNumbers(int left, int right);
