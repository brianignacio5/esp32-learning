#pragma once

#include <stdint.h>

#include "driver/gpio.h"

/* Read one 5-byte DHT22 frame on gpio. Returns 0 on a complete frame.
   The checksum is not checked here. */
int dht_read_frame(gpio_num_t gpio, uint8_t frame[5]);
