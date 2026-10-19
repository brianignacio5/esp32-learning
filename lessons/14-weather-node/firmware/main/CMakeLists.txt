idf_component_register(SRCS "app_main.c" "wifi_connect.c" "mqtt_pub.c" "dht_io.c" "dht_provided.c" "nvs_store.c" "sensor.c"
                       INCLUDE_DIRS "."
                       REQUIRES log logic esp_driver_gpio esp_timer freertos nvs_flash esp_wifi esp_event esp_netif mqtt)
