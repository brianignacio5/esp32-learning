#pragma once

#include <stddef.h>

typedef struct {
    int temp_c_x10;
    int humidity_pct;
    int boot;
} reading_t;

/* Write sensors/<device_id>/reading.
   device_id is 1 to 32 characters of letters, digits, or underscore.
   Returns 0, or -1 without writing buf when the id or the buffer is unusable. */
int sensor_topic(char *buf, size_t len, const char *device_id);

/* Same JSON object as lesson 12. Returns 0, or -1 without writing buf. */
int sensor_payload(const reading_t *in, char *buf, size_t len);
