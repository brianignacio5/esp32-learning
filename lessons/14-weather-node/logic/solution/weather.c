#include "weather.h"

#include <stdio.h>
#include <string.h>

#include "cJSON.h"

static int iabs(int value)
{
    return value < 0 ? -value : value;
}

int should_publish(const sample_t *last, const sample_t *now, int button_pressed,
                   int temp_threshold_x10, int humidity_threshold)
{
    if (now == NULL || temp_threshold_x10 < 0 || humidity_threshold < 0) {
        return 0;
    }
    if (last == NULL || button_pressed) {
        return 1;
    }
    if (iabs(now->temp_c_x10 - last->temp_c_x10) >= temp_threshold_x10) {
        return 1;
    }
    if (iabs(now->humidity_pct - last->humidity_pct) >= humidity_threshold) {
        return 1;
    }
    return 0;
}

int reading_to_json(int temp_c_x10, int humidity_pct, int boot, char *buf, size_t len)
{

    cJSON *root;
    char temp[16];
    char *printed;
    int negative;
    int magnitude;
    size_t need;

    if (buf == NULL || len == 0) {
        return -1;
    }

    negative = temp_c_x10 < 0;
    magnitude = negative ? -temp_c_x10 : temp_c_x10;
    snprintf(temp, sizeof temp, "%s%d.%d", negative ? "-" : "", magnitude / 10, magnitude % 10);

    root = cJSON_CreateObject();
    if (root == NULL) {
        return -1;
    }
    cJSON_AddRawToObject(root, "temp_c", temp);
    cJSON_AddNumberToObject(root, "humidity", humidity_pct);
    cJSON_AddNumberToObject(root, "boot", boot);
    printed = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (printed == NULL) {
        return -1;
    }
    need = strlen(printed);
    if (need + 1 > len) {
        cJSON_free(printed);
        return -1;
    }
    memcpy(buf, printed, need + 1);
    cJSON_free(printed);
    return 0;
}
