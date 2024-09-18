// main/led_control.c

#include "led_control.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "LED_CONTROL";
#define LED_GPIO GPIO_NUM_2 // LED connected to GPIO2

static uint8_t current_led_state = 0; // Default state is OFF

void init_led(void)
{
    // Initialize the GPIO pin
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_GPIO, current_led_state);
    ESP_LOGI(TAG, "LED initialized");
}

void set_led_state(uint8_t state)
{
    current_led_state = state;
    gpio_set_level(LED_GPIO, current_led_state);
    ESP_LOGI(TAG, "LED set to %s", current_led_state ? "ON" : "OFF");
}

uint8_t get_led_state(void)
{
    return current_led_state;
}
