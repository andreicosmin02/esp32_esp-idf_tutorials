// main/main.c

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_helper.h"
#include "led_control.h"

static const char *TAG = "MAIN_APP";

void app_main(void)
{
    uint8_t led_state;
    esp_err_t err;

    // Initialize NVS
    init_nvs();

    // Initialize LED GPIO
    init_led();

    // Read the last LED state from NVS
    err = read_led_state(&led_state);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to read LED state from NVS");
        led_state = 0; // Default to OFF if read failed
    }

    set_led_state(led_state);

    while (1)
    {
        // Wait for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Toggle LED state
        led_state = !led_state;
        set_led_state(led_state);

        // Save the new state to NVS
        err = save_led_state(led_state);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to save LED state to NVS");
        }

        ESP_LOGI(TAG, "LED toggled to %s", led_state ? "ON" : "OFF");
    }
}
