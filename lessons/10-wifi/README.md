# Lesson 10 — Join a Wi-Fi network

About one hour. The chip becomes a station, associates, and prints the address it was given.

## What you will learn

- The station startup sequence: netif, event loop, Wi-Fi init, config, start
- Which events matter: `WIFI_EVENT_STA_START`, `WIFI_EVENT_STA_DISCONNECTED`, `IP_EVENT_STA_GOT_IP`
- Why this simulator wants the open SSID `Wokwi-GUEST` on channel 6

## The task

Finish `firmware/main/app_main.c`. The init order is already there. You fill in two pieces:

1. The event handler. On start, call `esp_wifi_connect()`. On disconnect, call it again. On got-IP, log `got ip: <address>` with the `IPSTR` / `IP2STR` macros and set `CONNECTED_BIT` on the event group.
2. The `wifi_config_t`. SSID `Wokwi-GUEST`, empty password, `threshold.authmode` of `WIFI_AUTH_OPEN`, channel `6`.

Channel 6 is the Wokwi guest AP. Setting it skips a scan.

## Acceptance

- The log contains `got ip`
- The address is an IPv4 address (in Wokwi it is in `10.10.0.0/16` on the public gateway)
- No real Wi-Fi password is written anywhere. This course only uses `Wokwi-GUEST`

## Read

- [Wi-Fi driver](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-guides/wifi.html)
- [Wokwi ESP32 Wi-Fi](https://docs.wokwi.com/guides/esp32-wifi)
- Example to read after you finish: [wifi/getting_started/station](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/wifi/getting_started/station)

## Build and simulate

Open `lessons/10-wifi/firmware`.

```bash
idf.py set-target esp32
idf.py build
```

Start Wokwi. The serial log is the whole user interface for this hour.

## Check

`firmware/scenario.yaml` waits for `got ip`. There is no host test. Run it with `./scripts/check-lesson.sh 10 --wokwi` when `WOKWI_CLI_TOKEN` is set.

## Solution

`firmware/main/solution/app_main.c`.

## Hints

- `ip_event_got_ip_t *event = data;` then `event->ip_info.ip` is the address.
- An open network still needs `threshold.authmode = WIFI_AUTH_OPEN`. The default threshold rejects an open AP.
- Give up after a handful of disconnects, or the log will scroll forever when the SSID is wrong.
