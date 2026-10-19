#include "esp_log.h"
#include "http_exchange.h"
#include "http_line.h"
#include "wifi_connect.h"

static const char *TAG = "lesson11";

void app_main(void)
{
    char request[160];
    char line[128];
    int code = 0;

    ESP_LOGI(TAG, "lesson 11 ready");
    if (wifi_connect() != 0) {
        return;
    }
    if (build_http_get(request, sizeof request, "example.com", "/") != 0) {
        ESP_LOGE(TAG, "request build failed");
        return;
    }
    if (http_exchange("example.com", request, line, sizeof line) != 0) {
        ESP_LOGE(TAG, "http exchange failed");
        return;
    }
    ESP_LOGI(TAG, "status line: %s", line);
    if (parse_status_code(line, &code) != 0) {
        ESP_LOGE(TAG, "status parse failed");
        return;
    }
    ESP_LOGI(TAG, "status=%d", code);
}
