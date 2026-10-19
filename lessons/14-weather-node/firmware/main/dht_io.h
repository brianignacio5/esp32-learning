#pragma once

#include <stdint.h>

#include "driver/gpio.h"

int dht_read_frame(gpio_num_t gpio, uint8_t frame[5]);
