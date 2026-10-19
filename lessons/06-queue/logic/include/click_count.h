#pragma once

#include <stddef.h>

/* Increment *total by one.
   Return 1 when the new total is a positive multiple of every, otherwise 0.
   Return -1 when total is NULL or every is less than 1.
   The total is not cleared when a multiple is reached. */
int click_count_hit(int *total, int every);
