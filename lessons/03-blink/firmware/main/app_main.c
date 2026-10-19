#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "lesson03";
static const gpio_num_t LED_GPIO = GPIO_NUM_2;

void app_main(void)
{
    /* TODO: configure LED_GPIO as an output and toggle it every 500 ms.
       Log "led on" when you drive it high and "led off" when you drive it low. */
    ESP_LOGI(TAG, "lesson 03 start");
    (void)LED_GPIO;
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
