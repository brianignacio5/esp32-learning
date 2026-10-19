#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "debounce.h"

static const char *TAG = "lesson04";
static const gpio_num_t LED_GPIO = GPIO_NUM_2;
static const gpio_num_t BUTTON_GPIO = GPIO_NUM_4;

void app_main(void)
{
    /* TODO: configure the LED as an output and the button as an input with a pull-up.
       Poll BUTTON_GPIO every 10 ms. Pass the level to debounce_update with need 3.
       When the stable level becomes 0, toggle the LED and log "led on" or "led off". */
    ESP_LOGI(TAG, "lesson 04 ready");
    (void)LED_GPIO;
    (void)BUTTON_GPIO;
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
