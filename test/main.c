#include "stm32_tm1637.h"

int main() {
  tm1637Init();
  tm1637DisplayDecimal(4, 1);
  tm1637SetBrightness(5);
  return 0;
}

 void HAL_GPIO_Init(char* c, GPIO_InitTypeDef *g) {}
 void HAL_GPIO_WritePin(char *c1, char *c2, char *c3) {}
 void __HAL_RCC_GPIOC_CLK_ENABLE() {}

