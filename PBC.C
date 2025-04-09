#include "main.h"
#include <stdio.h>

UART_HandleTypeDef huart2;
int counter = 0;
uint8_t last_button_state = 1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  char msg[30];

  while (1)
  {
    uint8_t current_button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    if (last_button_state == 1 && current_button_state == 0) // Falling edge detection
    {
      counter++;
      sprintf(msg, "Count: %d\r\n", counter);
      HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

      HAL_Delay(200); // Simple debounce
    }

    last_button_state = current_button_state;
  }
}
