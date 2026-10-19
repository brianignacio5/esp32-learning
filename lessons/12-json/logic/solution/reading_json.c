#include "reading_json.h"

#include <stdio.h>
#include <string.h>

#include "cJSON.h"

int reading_to_json(const reading_t *in, char *buf, size_t len)
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
