#pragma once

#include <stddef.h>

/* Write a reading into buf.
   temp_c_x10 is tenths of a degree Celsius (235 means 23.5, -5 means -0.5).
   humidity_pct is printed as an integer percent.
   The text is "23.5C 40%" with no extra spaces.
   Returns the number of characters that would have been written, excluding
   the terminating NUL (the same contract as snprintf).
   Returns -1 when buf is NULL or len is 0. */
int format_reading(char *buf, size_t len, int temp_c_x10, int humidity_pct);
