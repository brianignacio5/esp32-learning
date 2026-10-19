#include "esp_chip_info.h"
#include "esp_idf_version.h"
#include "esp_log.h"

static const char *TAG = "lesson01";

static const char *chip_model_name(esp_chip_model_t model)
{
    switch (model) {
    case CHIP_ESP32:
        return "ESP32";
    case CHIP_ESP32S2:
        return "ESP32-S2";
    case CHIP_ESP32S3:
        return "ESP32-S3";
    case CHIP_ESP32C3:
        return "ESP32-C3";
    default:
        return "unknown";
    }
}

void app_main(void)
{
    esp_chip_info_t chip;
    esp_chip_info(&chip);

    ESP_LOGI(TAG, "lesson 01 ready");
    ESP_LOGI(TAG, "chip %s, idf %s", chip_model_name(chip.model), esp_get_idf_version());
}
