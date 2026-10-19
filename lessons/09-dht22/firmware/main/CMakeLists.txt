idf_component_register(SRCS "app_main.c" "dht_io.c"
                       INCLUDE_DIRS "."
                       REQUIRES log esp_driver_gpio esp_timer freertos logic)
