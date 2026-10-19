#include <string.h>

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"

static const char *TAG = "lesson10";
static EventGroupHandle_t s_wifi;
static int s_retries;

#define CONNECTED_BIT BIT0
#define FAIL_BIT BIT1

static void on_wifi(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    (void)arg;
    (void)data;
    /* TODO: on WIFI_EVENT_STA_START, call esp_wifi_connect().
       On WIFI_EVENT_STA_DISCONNECTED, retry up to 10 times, then set FAIL_BIT.
       On IP_EVENT_STA_GOT_IP, log "got ip: " with IPSTR / IP2STR and set CONNECTED_BIT. */
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        s_retries++;
    }
}

void app_main(void)
{
    wifi_config_t wifi_config = {0};
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    EventBits_t bits;
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    s_wifi = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, on_wifi, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, on_wifi, NULL, NULL));

    /* TODO: SSID "Wokwi-GUEST", empty password, WIFI_AUTH_OPEN, channel 6. */
    (void)wifi_config;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    bits = xEventGroupWaitBits(s_wifi, CONNECTED_BIT | FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(20000));
    if (bits & CONNECTED_BIT) {
        ESP_LOGI(TAG, "station up");
    } else {
        ESP_LOGW(TAG, "station failed");
    }
}
