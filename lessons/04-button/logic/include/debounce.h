#pragma once

#include <stddef.h>

typedef struct {
    int stable;
    int candidate;
    int count;
} debounce_t;

/* stable and candidate start at level (treated as 0 or 1). count starts at 0. */
void debounce_init(debounce_t *db, int level);

/* Feed one sample.
   Returns 1 only on the sample that changes db->stable.
   A new level is accepted after `need` consecutive samples of that level.
   need < 1 is treated as 1.
   A NULL db, or a level other than 0 or 1, returns 0 and changes nothing.
   Samples that match the current stable level cancel a candidate in progress. */
int debounce_update(debounce_t *db, int level, int need);
