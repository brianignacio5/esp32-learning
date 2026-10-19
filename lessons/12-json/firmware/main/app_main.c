#include "esp_log.h"
#include "reading_json.h"

static const char *TAG = "lesson12";

void app_main(void)
{
    reading_t in = {.temp_c_x10 = 255, .humidity_pct = 40, .boot = 3};
    char buf[80];
    if (reading_to_json(&in, buf, sizeof buf) != 0) {
        ESP_LOGE(TAG, "json failed");
        return;
    }
    ESP_LOGI(TAG, "json %s", buf);
}
