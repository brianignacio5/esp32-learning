# Lesson 03 — Blink a GPIO

About one hour. One pin, one LED, a delay.

## What you will learn

- How to configure a GPIO as an output
- How `gpio_set_level` drives the pin the LED is wired to
- How `vTaskDelay` waits without spinning in a tight loop

## The task

The red LED in `firmware/diagram.json` is on GPIO2, through a 220 ohm resistor to ground. In `app_main`:

1. Configure GPIO2 as an output
2. Forever: drive it high, log `led on`, wait 500 ms, drive it low, log `led off`, wait 500 ms

## Acceptance

- The Wokwi LED blinks about once a second (500 ms on, 500 ms off)
- The log alternates `led on` and `led off`
- `firmware/scenario.yaml` sees `led on` with GPIO2 high, then `led off` with GPIO2 low

## Read

- [GPIO API](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/peripherals/gpio.html)
- Example to read after you finish: [get-started/blink](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/get-started/blink)

## Build and simulate

Open `lessons/03-blink/firmware`.

```bash
idf.py set-target esp32
idf.py build
```

**Wokwi: Start Simulator**. On hardware, GPIO2 is the usual DevKitC LED pin. **ESP-IDF: Build, Flash and Monitor**.

## Check

```bash
./scripts/check-lesson.sh 03 --wokwi
```

There is no host test. The scenario is the check, and it needs `WOKWI_CLI_TOKEN` plus a built firmware. Without a token, watch the LED yourself.

## Solution

`firmware/main/solution/app_main.c`.

## Hints

- `gpio_config()` takes a `gpio_config_t`. The pin mask is `1ULL << GPIO_NUM_2`.
- `pdMS_TO_TICKS(500)` converts milliseconds into FreeRTOS ticks. Pass that to `vTaskDelay`.
- Log the new state after you set the pin, so a test can wait for the text and then read the pin.
