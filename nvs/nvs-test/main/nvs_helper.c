// main/nvs_helper.c

#include "nvs_helper.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

static const char *TAG = "NVS_HELPER";
#define NVS_NAMESPACE "storage"

void init_nvs(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "NVS initialized successfully");
}

esp_err_t save_led_state(uint8_t state)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    // Open NVS handle
    err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error opening NVS handle: %s", esp_err_to_name(err));
        return err;
    }

    // Write value to NVS
    err = nvs_set_u8(nvs_handle, "led_state", state);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set LED state in NVS: %s", esp_err_to_name(err));
        nvs_close(nvs_handle);
        return err;
    }

    // Commit written value
    err = nvs_commit(nvs_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to commit LED state to NVS: %s", esp_err_to_name(err));
    }
    else
    {
        ESP_LOGI(TAG, "LED state saved to NVS: %d", state);
    }

    // Close NVS handle
    nvs_close(nvs_handle);
    return err;
}

esp_err_t read_led_state(uint8_t *state)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    // Open NVS handle
    err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error opening NVS handle: %s", esp_err_to_name(err));
        return err;
    }

    // Read the value from NVS
    err = nvs_get_u8(nvs_handle, "led_state", state);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "LED state read from NVS: %d", *state);
    }
    else if (err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGI(TAG, "LED state not found in NVS, defaulting to OFF");
        *state = 0;   // Default state is OFF
        err = ESP_OK; // Treat as success with default value
    }
    else
    {
        ESP_LOGE(TAG, "Error reading LED state from NVS: %s", esp_err_to_name(err));
    }

    // Close NVS handle
    nvs_close(nvs_handle);
    return err;
}
