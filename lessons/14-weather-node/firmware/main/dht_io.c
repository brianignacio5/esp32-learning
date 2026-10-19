#include "dht_io.h"

#include <stddef.h>
#include <string.h>

#include "esp_timer.h"

static void busy_wait_us(int64_t us)
{
    int64_t start = esp_timer_get_time();
    while ((esp_timer_get_time() - start) < us) {
    }
}

static int wait_level(gpio_num_t gpio, int level, int timeout_us)
{
    int64_t start = esp_timer_get_time();
    while (gpio_get_level(gpio) != level) {
        if ((esp_timer_get_time() - start) > timeout_us) {
            return -1;
        }
    }
    return (int)(esp_timer_get_time() - start);
}

int dht_read_frame(gpio_num_t gpio, uint8_t frame[5])
{
    int bit;

    if (frame == NULL) {
        return -1;
    }
    memset(frame, 0, 5);

    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
    gpio_set_level(gpio, 0);
    busy_wait_us(3000);
    gpio_set_level(gpio, 1);
    busy_wait_us(30);
    gpio_set_direction(gpio, GPIO_MODE_INPUT);
    gpio_set_pull_mode(gpio, GPIO_PULLUP_ONLY);

    if (wait_level(gpio, 0, 300) < 0 || wait_level(gpio, 1, 200) < 0 || wait_level(gpio, 0, 200) < 0) {
        return -1;
    }

    for (bit = 0; bit < 40; bit++) {
        int high_us;
        if (wait_level(gpio, 1, 120) < 0) {
            return -1;
        }
        high_us = wait_level(gpio, 0, 200);
        if (high_us < 0) {
            return -1;
        }
        frame[bit / 8] = (uint8_t)((frame[bit / 8] << 1) | (high_us > 50 ? 1 : 0));
    }
    return 0;
}
