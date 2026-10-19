#include "sensor_publish.h"

#include <stdio.h>
#include <string.h>

#include "cJSON.h"

static int valid_id(const char *device_id)
{
    size_t n = 0;
    const char *p;

    if (device_id == NULL) {
        return 0;
    }
    for (p = device_id; *p != '\0'; p++) {
        char c = *p;
        int ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
        if (!ok) {
            return 0;
        }
        n++;
        if (n > 32) {
            return 0;
        }
    }
    return n > 0;
}

int sensor_topic(char *buf, size_t len, const char *device_id)
{
    int need;

    if (buf == NULL || !valid_id(device_id)) {
        return -1;
    }
    need = snprintf(NULL, 0, "sensors/%s/reading", device_id);
    if (need < 0 || (size_t)need + 1 > len) {
        return -1;
    }
    snprintf(buf, len, "sensors/%s/reading", device_id);
    return 0;
}

int sensor_payload(const reading_t *in, char *buf, size_t len)
{
    int temp_c_x10;
    int humidity_pct;
    int boot;

    if (in == NULL) {
        return -1;
    }
    temp_c_x10 = in->temp_c_x10;
    humidity_pct = in->humidity_pct;
    boot = in->boot;

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
