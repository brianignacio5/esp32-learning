#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int temp_c_x10;
    int humidity_x10;
} dht_sample_t;

/* Provided from lesson 09. Returns 0 on a valid frame. */
int dht_decode(const uint8_t frame[5], dht_sample_t *out);
