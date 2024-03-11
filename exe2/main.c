#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_PIN_R = 4;
volatile int PRESSED = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    PRESSED = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  while (true) {
    if (PRESSED) {
      PRESSED = 0;
      if (!gpio_get(LED_PIN_R)) {
        gpio_put(LED_PIN_R, 1);
      } else {
        gpio_put(LED_PIN_R, 0);
      }
    }
  }
}


/*
OU


const int BTN_PIN_R = 28;
const int LED_PIN_R = 4;
volatile int PRESSED = 0;

void btn_callback(uint gpio, uint32_t events) {
  PRESSED = 1;
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE , true, &btn_callback);
  
  while (true) {
    if (PRESSED) {
      PRESSED = 0;
      if (!gpio_get(LED_PIN_R)) {
        gpio_put(LED_PIN_R, 1);
      } else {
        gpio_put(LED_PIN_R, 0);
      }
    }
  }
}
*/