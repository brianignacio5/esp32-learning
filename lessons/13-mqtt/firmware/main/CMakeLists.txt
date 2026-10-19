idf_component_register(SRCS "app_main.c" "wifi_connect.c"
                       INCLUDE_DIRS "."
                       REQUIRES log logic nvs_flash esp_wifi esp_event esp_netif freertos mqtt)
