#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "debounce.h"

static const char *TAG = "lesson04";
static const gpio_num_t LED_GPIO = GPIO_NUM_2;
static const gpio_num_t BUTTON_GPIO = GPIO_NUM_4;

static void configure_pins(void)
{
    gpio_config_t led = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config_t button = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&led));
    ESP_ERROR_CHECK(gpio_config(&button));
    gpio_set_level(LED_GPIO, 0);
}

void app_main(void)
{
    configure_pins();

    debounce_t db;
    debounce_init(&db, 1);
    int led_on = 0;

    ESP_LOGI(TAG, "lesson 04 ready");
    ESP_LOGI(TAG, "led off");

    while (1) {
        int level = gpio_get_level(BUTTON_GPIO);
        if (debounce_update(&db, level, 3) && db.stable == 0) {
            led_on = !led_on;
            gpio_set_level(LED_GPIO, led_on);
            ESP_LOGI(TAG, "%s", led_on ? "led on" : "led off");
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
