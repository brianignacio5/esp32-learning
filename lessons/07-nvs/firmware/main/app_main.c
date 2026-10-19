#include <stdint.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char *TAG = "lesson07";
static const gpio_num_t LED_GPIO = GPIO_NUM_2;

static void configure_led(void)
{
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&cfg));
}

void app_main(void)
{
    configure_led();

    /* TODO: init NVS, open namespace "lesson", bump boot_count, toggle led,
       commit, and log "boot_count=<n>" and "led_state=<0 or 1>".
       Drive LED_GPIO from the stored led value. */
    ESP_LOGI(TAG, "lesson 07 start");
    (void)LED_GPIO;
}
