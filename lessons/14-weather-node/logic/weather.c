#include "weather.h"

int should_publish(const sample_t *last, const sample_t *now, int button_pressed,
                   int temp_threshold_x10, int humidity_threshold)
{
    /* TODO: implement the contract in weather.h. */
    (void)last;
    (void)now;
    (void)button_pressed;
    (void)temp_threshold_x10;
    (void)humidity_threshold;
    return 0;
}

int reading_to_json(int temp_c_x10, int humidity_pct, int boot, char *buf, size_t len)
{
    /* TODO: the lesson 12 JSON object. */
    (void)temp_c_x10;
    (void)humidity_pct;
    (void)boot;
    (void)buf;
    (void)len;
    return -1;
}
