#include "sensor_publish.h"

int sensor_topic(char *buf, size_t len, const char *device_id)
{
    /* TODO: sensors/<device_id>/reading, with the id rules in the header. */
    (void)buf;
    (void)len;
    (void)device_id;
    return -1;
}

int sensor_payload(const reading_t *in, char *buf, size_t len)
{
    /* TODO: the lesson 12 JSON object. */
    (void)in;
    (void)buf;
    (void)len;
    return -1;
}
