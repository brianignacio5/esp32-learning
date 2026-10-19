#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "lesson05";
static const gpio_num_t LED_GPIO = GPIO_NUM_2;

void app_main(void)
{
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&cfg));

    /* TODO: log "tasks started", then create a logger task and a blink task.
       logger: every 1000 ms, log "tick".
       blink: every 500 ms, toggle LED_GPIO and log "led on" or "led off".
       Stack 2048, priority 5. */
    ESP_LOGI(TAG, "lesson 05 start");
}
