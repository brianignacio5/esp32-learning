# ESP-IDF IoT course

Fourteen one-hour lessons in C for the ESP32. You write the code, run a check, and compare it with the solution in the same lesson.

The board in every simulator diagram is the ESP32-DevKitC V4 (`idf.py set-target esp32`). Tool setup is in [docs/setup.md](docs/setup.md). The toolchain is ESP-IDF **v6.0.3**. Lesson links go to that version of the [ESP-IDF programming guide](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/index.html).

## How a lesson is laid out

```text
lessons/04-button/
  README.md                 what this hour teaches, the task, how to check
  logic/                    the C you write when the lesson has a pure function
    include/
    debounce.c              starter
    solution/debounce.c     reference
  firmware/                 the ESP-IDF project you build and simulate
    main/app_main.c
    main/solution/          present when the task edits the firmware
    diagram.json            Wokwi circuit
    wokwi.toml
    scenario.yaml           simulator check
  host_test/                Unity test, present when the lesson has pure C
```

Open `firmware` (not the repository root) as the ESP-IDF project. Build, then start Wokwi. The starter compiles. The interesting lines are marked `TODO`.

From the repository root, with ESP-IDF sourced:

```bash
./scripts/check-lesson.sh 04          # test your code
./scripts/check-lesson.sh 04 --solution   # test the reference
```

Host tests build with `idf.py --preview set-target linux` and need no board and no Wokwi token. Add `--wokwi` to build the firmware and run `scenario.yaml`. That needs `WOKWI_CLI_TOKEN` and `wokwi-cli`. Without the token the script says so and skips the simulator. Lessons 11 and 13 also have `scenario.optional.yaml` for a public HTTP or MQTT smoke test. Those are not the pass/fail gate.

## Curriculum

Each lesson is about an hour. Do them in order. The later firmware includes working copies of the earlier helpers so you are not rewriting Wi-Fi every time.

**The chip**

1. [Hello ESP-IDF](lessons/01-hello/README.md) — `app_main`, logging, chip info
2. [A component and a host test](lessons/02-component/README.md) — format a sensor reading, Unity on the host
3. [Blink a GPIO](lessons/03-blink/README.md) — GPIO2, 500 ms
4. [Button and debounce](lessons/04-button/README.md) — a testable state machine, then the pin

**Tasks and storage**

5. [Two FreeRTOS tasks](lessons/05-tasks/README.md) — logger and blinker
6. [A queue](lessons/06-queue/README.md) — button task, consumer, every fifth click
7. [NVS](lessons/07-nvs/README.md) — boot count and LED state across a restart

**Sensors**

8. [ADC scale](lessons/08-adc/README.md) — potentiometer counts to a percent
9. [DHT22 frame](lessons/09-dht22/README.md) — checksum and sign bit; the pulse reader is provided

**Onto the network**

10. [Wi-Fi station](lessons/10-wifi/README.md) — join `Wokwi-GUEST` and print the IP
11. [HTTP status line](lessons/11-http/README.md) — build a GET, parse the code
12. [JSON](lessons/12-json/README.md) — one cJSON object
13. [MQTT publish](lessons/13-mqtt/README.md) — topic and payload; the public broker is optional
14. [Weather node](lessons/14-weather-node/README.md) — sample, decide, encode, publish, remember

## Checks

| Lessons | What proves it |
| --- | --- |
| 02, 04, 06, 08, 09, 11, 12, 13, 14 | Unity host test of the reference solution in CI |
| 01, 03, 05, 07, 10, and the hardware lessons above | Wokwi scenario, run locally or in CI when `WOKWI_CLI_TOKEN` is set |
| 11, 13 | Public HTTP and MQTT are `scenario.optional.yaml` only |

GitHub Actions uses the `espressif/idf:v6.0.3` image. The Wokwi job exits cleanly when the token secret is unset.

## Not in this course

These are worth doing later, on your own, from the ESP-IDF examples: LEDC servo, an SSD1306 over I2C, deep sleep, SoftAP, and BLE on real hardware. Wokwi does not simulate Bluetooth.

## Editors

Use the ESP-IDF extension for build, flash, monitor, and menuconfig. Use Wokwi to run the diagram. Use clangd against `build/compile_commands.json` for completion. Details and the command names are in [docs/setup.md](docs/setup.md).
