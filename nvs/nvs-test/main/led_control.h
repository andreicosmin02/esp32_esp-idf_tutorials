// main/led_control.h

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdint.h>

void init_led(void);
void set_led_state(uint8_t state);
uint8_t get_led_state(void);

#endif // LED_CONTROL_H
