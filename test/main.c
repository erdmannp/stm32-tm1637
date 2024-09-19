#include "stm32_tm1637.h"

int main() {
  tm1637Init();
  tm1637DisplayDecimal(4, 1);
  tm1637SetBrightness(5);
  tm1637DisplayTwoNumbers(-4, 6);
  tm1637DisplayTwoNumbers(4, -6);
  tm1637DisplayTwoNumbers(24, -6);

  return 0;
}

 void HAL_GPIO_Init(char* c, GPIO_InitTypeDef *g) {}
 void HAL_GPIO_WritePin(char *c1, char *c2, char *c3) {}
 void __HAL_RCC_GPIOC_CLK_ENABLE() {}

