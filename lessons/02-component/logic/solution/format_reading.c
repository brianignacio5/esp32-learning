#include "format_reading.h"

#include <stdio.h>

int format_reading(char *buf, size_t len, int temp_c_x10, int humidity_pct)
{
    int negative;
    int magnitude;
    int whole;
    int frac;

    if (buf == NULL || len == 0) {
        return -1;
    }

    negative = temp_c_x10 < 0;
    magnitude = negative ? -temp_c_x10 : temp_c_x10;
    whole = magnitude / 10;
    frac = magnitude % 10;

    if (negative) {
        return snprintf(buf, len, "-%d.%dC %d%%", whole, frac, humidity_pct);
    }
    return snprintf(buf, len, "%d.%dC %d%%", whole, frac, humidity_pct);
}
