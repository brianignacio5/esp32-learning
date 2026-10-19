#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "lesson05";
static const gpio_num_t LED_GPIO = GPIO_NUM_2;

static void logger_task(void *arg)
{
    (void)arg;
    while (1) {
        ESP_LOGI(TAG, "tick");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void blink_task(void *arg)
{
    (void)arg;
    int on = 0;
    while (1) {
        on = !on;
        gpio_set_level(LED_GPIO, on);
        ESP_LOGI(TAG, "%s", on ? "led on" : "led off");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

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

    ESP_LOGI(TAG, "tasks started");
    xTaskCreate(logger_task, "logger", 2048, NULL, 5, NULL);
    xTaskCreate(blink_task, "blink", 2048, NULL, 5, NULL);
}
