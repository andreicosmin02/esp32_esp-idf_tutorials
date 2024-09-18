// main/nvs_helper.h

#ifndef NVS_HELPER_H
#define NVS_HELPER_H

#include <stdint.h>
#include "esp_err.h"

void init_nvs(void);
esp_err_t save_led_state(uint8_t state);
esp_err_t read_led_state(uint8_t *state);

#endif // NVS_HELPER_H
