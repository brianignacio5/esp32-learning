#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "sensor_publish.h"
#include "wifi_connect.h"

static const char *TAG = "lesson13";

static void on_connected(esp_mqtt_client_handle_t client)
{
    char topic[64];
    char payload[128];
    reading_t reading = {.temp_c_x10 = 255, .humidity_pct = 40, .boot = 3};
    /* TODO: build the topic for "esp32" and the payload, then publish at QoS 0.
       Log "mqtt published" when esp_mqtt_client_publish returns >= 0. */
    (void)client;
    (void)topic;
    (void)payload;
    (void)reading;
}

static void on_mqtt(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    esp_mqtt_event_handle_t event = data;
    (void)arg;
    (void)base;
    if (id == MQTT_EVENT_CONNECTED) {
        on_connected(event->client);
    } else if (id == MQTT_EVENT_ERROR) {
        ESP_LOGW(TAG, "mqtt error");
    }
}

void app_main(void)
{
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = "mqtt://broker.hivemq.com",
    };
    esp_mqtt_client_handle_t client;

    ESP_LOGI(TAG, "lesson 13 ready");
    if (wifi_connect() != 0) {
        return;
    }
    client = esp_mqtt_client_init(&cfg);
    ESP_ERROR_CHECK(esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, on_mqtt, NULL));
    ESP_ERROR_CHECK(esp_mqtt_client_start(client));
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
