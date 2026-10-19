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
    int msg_id;
    if (sensor_topic(topic, sizeof topic, "esp32") != 0) {
        return;
    }
    if (sensor_payload(&reading, payload, sizeof payload) != 0) {
        return;
    }
    msg_id = esp_mqtt_client_publish(client, topic, payload, 0, 0, 0);
    if (msg_id >= 0) {
        ESP_LOGI(TAG, "mqtt published");
    }
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
