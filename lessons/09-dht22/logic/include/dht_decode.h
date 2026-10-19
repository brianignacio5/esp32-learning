#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int ok;
    int temp_c_x10;
    int humidity_x10;
} dht_reading_t;

/* frame is hum_hi, hum_lo, temp_hi, temp_lo, checksum.
   Humidity and temperature are in tenths.
   Bit 15 of the 16-bit temperature is the sign; the lower 15 bits are the magnitude.
   Returns 0 and writes *out when the checksum matches.
   Returns -1, without writing *out, when frame or out is NULL or the checksum fails. */
int dht_decode(const uint8_t frame[5], dht_reading_t *out);
