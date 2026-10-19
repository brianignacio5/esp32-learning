#pragma once

#include <stddef.h>


typedef struct {
    int temp_c_x10;
    int humidity_pct;
} sample_t;

/* Return 1 when this sample should be published.
   last NULL means there is no history, which publishes.
   button_pressed publishes even when the sample did not change.
   Otherwise compare absolute deltas with the thresholds.
   Return 0 when now is NULL or either threshold is negative. */
int should_publish(const sample_t *last, const sample_t *now, int button_pressed,
                   int temp_threshold_x10, int humidity_threshold);

/* {"temp_c":25.5,"humidity":40,"boot":1} for (255, 40, 1).
   Returns 0, or -1 without writing buf. */
int reading_to_json(int temp_c_x10, int humidity_pct, int boot, char *buf, size_t len);
