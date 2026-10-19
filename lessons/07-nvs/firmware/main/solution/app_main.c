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

static void init_nvs(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

void app_main(void)
{
    nvs_handle_t handle;
    int32_t boot_count = 0;
    uint8_t led = 0;
    esp_err_t err;

    configure_led();
    init_nvs();

    ESP_ERROR_CHECK(nvs_open("lesson", NVS_READWRITE, &handle));

    err = nvs_get_i32(handle, "boot_count", &boot_count);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
        ESP_ERROR_CHECK(err);
    }
    boot_count++;
    ESP_ERROR_CHECK(nvs_set_i32(handle, "boot_count", boot_count));

    err = nvs_get_u8(handle, "led", &led);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
        ESP_ERROR_CHECK(err);
    }
    led = !led;
    ESP_ERROR_CHECK(nvs_set_u8(handle, "led", led));
    ESP_ERROR_CHECK(nvs_commit(handle));
    nvs_close(handle);

    gpio_set_level(LED_GPIO, led);
    ESP_LOGI(TAG, "boot_count=%ld", (long)boot_count);
    ESP_LOGI(TAG, "led_state=%u", (unsigned)led);
}
