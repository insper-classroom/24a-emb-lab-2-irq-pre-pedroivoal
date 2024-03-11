#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int PRESSED = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    PRESSED = 1;
  } else if (events == 0x8) { // rise edge
    PRESSED = 2;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (PRESSED == 1) { // fall edge
      printf("fall \n");
      PRESSED = 0;
    } else if (PRESSED == 2) { // rise edge
      printf("rise \n");
      PRESSED = 0;
    }
  }
}
