#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

int BTN_PIN_R = 28;
int BTN_PIN_G = 26;

int LED_PIN_R = 4;
int LED_PIN_G = 6;

volatile int FALL_R = 0;
volatile int RISE_G = 0;

void btn_callback(uint gpio, uint32_t events)
{
  if (gpio == BTN_PIN_R)
  {
    if (events == 0x4)
    {
      FALL_R = 1;
    } 
  }
  else if (gpio == BTN_PIN_G)
  {
    if (events == 0x8)
    {
      RISE_G = 1;
    }
  }
}



int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_G, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  

  while (true) {
    if (FALL_R)
    {
      FALL_R = 0;
      if (!gpio_get(LED_PIN_R)) 
      {
        gpio_put(LED_PIN_R, 1);
      }
      else
      {
        gpio_put(LED_PIN_R, 0);
      }
    }
    else if (RISE_G)
    {
      RISE_G = 0;
      if (!gpio_get(LED_PIN_G)) 
      {
        gpio_put(LED_PIN_G, 1);
      }
      else
      {
        gpio_put(LED_PIN_G, 0);
      }
    }
    
  }
}
