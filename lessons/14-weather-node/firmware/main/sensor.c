#include "sensor.h"

#include <stddef.h>

#include "dht_io.h"
#include "dht_provided.h"
#include "driver/gpio.h"

static const gpio_num_t DHT_GPIO = GPIO_NUM_15;

void sensor_init(void)
{
    gpio_reset_pin(DHT_GPIO);
    gpio_set_pull_mode(DHT_GPIO, GPIO_PULLUP_ONLY);
}

int sensor_read(sample_t *out)
{
    uint8_t frame[5];
    dht_sample_t reading;

    if (out == NULL) {
        return -1;
    }
    if (dht_read_frame(DHT_GPIO, frame) != 0) {
        return -1;
    }
    if (dht_decode(frame, &reading) != 0) {
        return -1;
    }
    out->temp_c_x10 = reading.temp_c_x10;
    out->humidity_pct = reading.humidity_x10 / 10;
    return 0;
}
