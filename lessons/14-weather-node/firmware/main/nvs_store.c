#include "nvs_store.h"

#include "nvs.h"
#include "nvs_flash.h"

int nvs_next_boot(void)
{
    nvs_handle_t handle;
    int32_t boot = 0;
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(nvs_open("weather", NVS_READWRITE, &handle));
    err = nvs_get_i32(handle, "boot", &boot);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
        ESP_ERROR_CHECK(err);
    }
    boot++;
    ESP_ERROR_CHECK(nvs_set_i32(handle, "boot", boot));
    ESP_ERROR_CHECK(nvs_commit(handle));
    nvs_close(handle);
    return (int)boot;
}
