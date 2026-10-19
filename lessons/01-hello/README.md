# Lesson 01 — Hello ESP-IDF

About one hour. You will build a project, read the serial log, and see the same firmware in Wokwi.

## What you will learn

- Where an ESP-IDF program starts: `app_main`
- How `ESP_LOGI` writes a line you can see in the monitor
- How to ask the chip which model it is, and which ESP-IDF version it was built with

## The task

Edit `firmware/main/app_main.c`. On boot, log these three facts:

1. The exact text `lesson 01 ready`
2. The chip model name (`ESP32` on the board this course uses)
3. The ESP-IDF version string from `esp_get_idf_version()`

Use the tag `lesson01` so the log lines are easy to spot.

## Acceptance

- The serial monitor shows `lesson 01 ready`
- The same boot also shows `ESP32` and a version string such as `v6.0.3`
- Wokwi scenario `firmware/scenario.yaml` reaches `lesson 01 ready`

## Read

- [Application startup](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-guides/startup.html)
- [Logging](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/system/log.html)
- [Miscellaneous system APIs](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/system/misc_system_api.html) (`esp_chip_info`)
- Example to read after you finish: [hello_world](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/get-started/hello_world)

## Build and simulate

Open `lessons/01-hello/firmware` as the ESP-IDF project. The repository root is not a project.

```bash
idf.py set-target esp32
idf.py build
```

In VS Code: **ESP-IDF: Build your Project**, then **Wokwi: Start Simulator**. On a real board: **ESP-IDF: Build, Flash and Monitor**. Quit the monitor with Ctrl-].

## Check

This lesson has no host test. The check is the serial line.

```bash
# with WOKWI_CLI_TOKEN set, after sourcing ESP-IDF
./scripts/check-lesson.sh 01 --solution --wokwi
```

## Solution

`firmware/main/solution/app_main.c`. Look at it after your log line shows up.

## Hints

- `esp_chip_info_t` is filled by `esp_chip_info()`. The `model` field is an enum; `CHIP_ESP32` is the one you want a string for.
- `ESP_LOGI(TAG, "...")` is the usual info line. The monitor text contains your message, plus a timestamp and the tag.
