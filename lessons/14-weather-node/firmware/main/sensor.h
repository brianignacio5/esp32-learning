#pragma once

#include "weather.h"

void sensor_init(void);

/* Read the DHT22 on GPIO15 into out. humidity_pct is humidity_x10 / 10.
   Returns 0 on a decoded frame. */
int sensor_read(sample_t *out);
