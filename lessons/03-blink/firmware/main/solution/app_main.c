#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "lesson03";
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

    int on = 0;
    while (1) {
        on = !on;
        gpio_set_level(LED_GPIO, on);
        ESP_LOGI(TAG, "%s", on ? "led on" : "led off");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
