#pragma once

#include <stddef.h>

typedef struct {
    int temp_c_x10;
    int humidity_pct;
    int boot;
} reading_t;

/* Write {"temp_c":25.5,"humidity":40,"boot":3} for 255 tenths, 40 percent, boot 3.
   temp_c always has one decimal place. No spaces.
   Returns 0, or -1 when in or buf is NULL, len is 0, or the text does not fit.
   On failure buf is left unchanged. */
int reading_to_json(const reading_t *in, char *buf, size_t len);
