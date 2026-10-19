#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_pub.h"
#include "nvs_store.h"
#include "sensor.h"
#include "weather.h"
#include "wifi_connect.h"

static const char *TAG = "weather";
static const gpio_num_t BUTTON_GPIO = GPIO_NUM_4;

static void configure_button(void)
{
    gpio_config_t button = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&button));
}

void app_main(void)
{
    sample_t last = {0};
    int have_last = 0;
    int boot;

    configure_button();
    wifi_connect();
    mqtt_start();
    sensor_init();
    boot = nvs_next_boot();

    while (1) {
        sample_t now;
        int pressed;
        if (sensor_read(&now) != 0) {
            ESP_LOGW(TAG, "sensor read failed");
            vTaskDelay(pdMS_TO_TICKS(2000));
            continue;
        }
        pressed = gpio_get_level(BUTTON_GPIO) == 0;
        if (should_publish(have_last ? &last : NULL, &now, pressed, 5, 2)) {
            char json[160];
            if (reading_to_json(now.temp_c_x10, now.humidity_pct, boot, json, sizeof json) == 0) {
                mqtt_publish_json(json);
                ESP_LOGI(TAG, "published %s", json);
                last = now;
                have_last = 1;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
