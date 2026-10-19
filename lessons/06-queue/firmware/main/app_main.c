#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "click_count.h"

static const char *TAG = "lesson06";
static const gpio_num_t BUTTON_GPIO = GPIO_NUM_4;

static QueueHandle_t clicks;

static void debounce_init_level(int *stable, int level)
{
    *stable = level ? 1 : 0;
}

static int debounce_press(int *stable, int *count, int level)
{
    const int need = 3;
    if (level == *stable) {
        *count = 0;
        return 0;
    }
    *count += 1;
    if (*count >= need) {
        *stable = level;
        *count = 0;
        return *stable == 0;
    }
    return 0;
}

static void consumer_task(void *arg)
{
    int total = 0;
    uint8_t event = 0;
    (void)arg;
    while (1) {
        /* TODO: wait on `clicks`, then call click_count_hit(&total, 5).
           Log "fifth click" when it returns 1. */
        (void)total;
        (void)event;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

static void button_task(void *arg)
{
    int stable = 1;
    int count = 0;
    (void)arg;
    debounce_init_level(&stable, 1);
    while (1) {
        int level = gpio_get_level(BUTTON_GPIO);
        if (debounce_press(&stable, &count, level)) {
            uint8_t event = 1;
            /* TODO: xQueueSend the event. */
            (void)event;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    gpio_config_t button = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&button));

    /* TODO: clicks = xQueueCreate(8, sizeof(uint8_t)); */
    clicks = NULL;
    ESP_LOGI(TAG, "lesson 06 ready");
    xTaskCreate(consumer_task, "consumer", 2048, NULL, 5, NULL);
    xTaskCreate(button_task, "button", 2048, NULL, 5, NULL);
}
