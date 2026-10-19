#include "dht_io.h"
#include "dht_decode.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "lesson09";
static const gpio_num_t DHT_GPIO = GPIO_NUM_15;

void app_main(void)
{
    while (1) {
        uint8_t frame[5] = {0};
        dht_reading_t reading;
        if (dht_read_frame(DHT_GPIO, frame) == 0 && dht_decode(frame, &reading) == 0) {
            ESP_LOGI(TAG, "temp_c_x10=%d humidity_x10=%d", reading.temp_c_x10, reading.humidity_x10);
        } else {
            ESP_LOGW(TAG, "dht read failed");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
