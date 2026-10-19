#include "esp_log.h"
#include "format_reading.h"

static const char *TAG = "lesson02";

void app_main(void)
{
    char buf[32];
    int n = format_reading(buf, sizeof buf, 235, 40);
    if (n < 0) {
        ESP_LOGE(TAG, "format failed");
        return;
    }
    ESP_LOGI(TAG, "reading %s", buf);
}
