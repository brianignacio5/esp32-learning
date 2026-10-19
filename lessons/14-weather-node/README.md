# Lesson 14 — Weather node

About one hour. This is the capstone. The sensor reader, Wi-Fi join, MQTT client, and NVS boot counter are provided. You decide when a reading is worth sending, and you build the payload.

## What you will learn

- How the earlier hours sit in one loop: sample, decide, encode, publish, remember
- A threshold so a quiet sensor does not publish on every poll
- A button path that publishes immediately

## The task

1. Implement `should_publish()` and `reading_to_json()` in `logic/weather.c`.
   - No previous sample (`last` is NULL) publishes
   - A pressed button publishes
   - Otherwise publish when the temperature moved by at least `temp_threshold_x10` tenths, or the humidity moved by at least `humidity_threshold` percent
   - A NULL `now`, or a negative threshold, does not publish
   - The JSON text is the lesson 12 object. `reading_to_json(255, 40, 1, ...)` writes `{"temp_c":25.5,"humidity":40,"boot":1}`
2. Finish the loop in `firmware/main/app_main.c`. The helpers are declared in the headers next to it.
   - Thresholds: 5 tenths of a degree (0.5 C) and 2 percent humidity
   - On publish: build JSON with the boot count, call `mqtt_publish_json`, log `published <json>`, and remember the sample
   - MQTT may fail when the public broker is unreachable. Still log the JSON. The serial line is the check

The DHT22 is on GPIO15. The button is on GPIO4, active low, with a pull-up. Polls are two seconds apart because that is as fast as a DHT22 should be read.

## Acceptance

- `./scripts/check-lesson.sh 14` passes
- The first good sample logs a `published` line whose JSON contains `"temp_c":25.5` when the simulated sensor is at 25.5 C and 40% humidity
- A second identical sample does not require another publish. A button press or a large enough change does

## Read

Skim the helper sources, then the pages you already used:

- [NVS](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/storage/nvs_flash.html)
- [MQTT](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/protocols/mqtt.html)
- [Wi-Fi](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-guides/wifi.html)

## Build and simulate

```bash
./scripts/check-lesson.sh 14
```

Build `lessons/14-weather-node/firmware` and start Wokwi. The scenario sets the DHT22 and waits for the published JSON. The first sample publishes because there is no previous sample.

## Check

Host test for the decision and the payload. Wokwi for the serial JSON. The public MQTT broker is not the gate.

## Solution

- `logic/solution/weather.c`
- `firmware/main/solution/app_main.c`

## Hints

- Use the absolute difference. A drop of 0.5 C is as interesting as a rise.
- Pass `have_last ? &last : NULL` so the first sample takes the "no history" path.
- Log the JSON after you build it, whether or not `mqtt_publish_json` returns 0.
