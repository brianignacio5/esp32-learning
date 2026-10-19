#include "mqtt_pub.h"

#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "mqtt_client.h"

static const char *TAG = "mqtt";
static EventGroupHandle_t s_events;
static esp_mqtt_client_handle_t s_client;

#define READY_BIT BIT0

static void on_mqtt(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    (void)arg;
    (void)base;
    (void)data;
    if (id == MQTT_EVENT_CONNECTED) {
        xEventGroupSetBits(s_events, READY_BIT);
    }
}

void mqtt_start(void)
{
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = "mqtt://broker.hivemq.com",
    };
    EventBits_t bits;

    s_events = xEventGroupCreate();
    s_client = esp_mqtt_client_init(&cfg);
    ESP_ERROR_CHECK(esp_mqtt_client_register_event(s_client, ESP_EVENT_ANY_ID, on_mqtt, NULL));
    ESP_ERROR_CHECK(esp_mqtt_client_start(s_client));
    bits = xEventGroupWaitBits(s_events, READY_BIT, pdFALSE, pdTRUE, pdMS_TO_TICKS(15000));
    if (bits & READY_BIT) {
        ESP_LOGI(TAG, "mqtt ready");
    } else {
        ESP_LOGW(TAG, "mqtt not connected");
    }
}

int mqtt_publish_json(const char *json)
{
    int msg_id;
    if (s_client == NULL || json == NULL) {
        return -1;
    }
    msg_id = esp_mqtt_client_publish(s_client, "sensors/weather/reading", json, 0, 0, 0);
    if (msg_id < 0) {
        ESP_LOGW(TAG, "mqtt publish failed");
        return -1;
    }
    return 0;
}
