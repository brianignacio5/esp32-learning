#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "raw_to_percent.h"

static const char *TAG = "lesson08";

void app_main(void)
{
    adc_oneshot_unit_handle_t adc;
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_chan_cfg_t chan_cfg = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    int raw = 0;

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&unit_cfg, &adc));
    /* GPIO34 is ADC1 channel 6 on the ESP32. */
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc, ADC_CHANNEL_6, &chan_cfg));

    while (1) {
        ESP_ERROR_CHECK(adc_oneshot_read(adc, ADC_CHANNEL_6, &raw));
        ESP_LOGI(TAG, "adc percent=%d", raw_to_percent(raw));
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
