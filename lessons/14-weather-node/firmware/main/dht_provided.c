#include "dht_provided.h"

int dht_decode(const uint8_t frame[5], dht_sample_t *out)
{
    uint8_t sum;
    int humidity;
    int temperature;
    int negative;

    if (frame == NULL || out == NULL) {
        return -1;
    }
    sum = (uint8_t)(frame[0] + frame[1] + frame[2] + frame[3]);
    if (sum != frame[4]) {
        return -1;
    }
    humidity = ((int)frame[0] << 8) | frame[1];
    temperature = ((int)frame[2] << 8) | frame[3];
    negative = (temperature & 0x8000) != 0;
    temperature &= 0x7FFF;
    if (negative) {
        temperature = -temperature;
    }
    out->humidity_x10 = humidity;
    out->temp_c_x10 = temperature;
    return 0;
}
