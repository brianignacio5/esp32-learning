# Lesson 13 — Publish a reading

About one hour. The broker is the unreliable part, so the test checks the topic and the payload. The firmware shows the publish call.

## What you will learn

- A topic layout `sensors/<device_id>/reading`
- How the lesson 12 JSON object becomes an MQTT payload
- Where `esp_mqtt_client_publish` sits, after `MQTT_EVENT_CONNECTED`

## The task

1. Implement `sensor_topic()` and `sensor_payload()` in `logic/sensor_publish.c`.
   - A device id is 1 to 32 characters of letters, digits, or `_`
   - `esp32` becomes `sensors/esp32/reading`
   - The payload is the same JSON object as lesson 12
2. In `on_connected` inside `firmware/main/app_main.c`, build the topic for device id `esp32`, build the payload for 25.5 C, 40% humidity, boot 3, and publish it at QoS 0. When `esp_mqtt_client_publish` returns a value greater than or equal to 0, log `mqtt published`.

Wi-Fi and the MQTT client setup are provided. The broker URI is the public `mqtt://broker.hivemq.com`. That host is a smoke test, not a guarantee.

## Acceptance

- `./scripts/check-lesson.sh 13` passes, including the exact topic and payload strings
- A device id with a space, a slash, or more than 32 characters is rejected, and a too-small buffer is rejected without a partial topic
- On a good network the log also shows `mqtt published`

## Read

- [MQTT](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/protocols/mqtt.html)
- Example to read after you finish: [protocols/mqtt](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/protocols/mqtt). That example uses TLS. This lesson stays on plain `mqtt://` so Wokwi's public gateway can reach the broker.

## Build and simulate

```bash
./scripts/check-lesson.sh 13
```

Build `lessons/13-mqtt/firmware` and start Wokwi if you want the smoke test. The optional scenario waits for `mqtt published`:

```bash
wokwi-cli . --scenario scenario.optional.yaml --timeout 120000
```

A reliable broker is one you run on your computer and reach through the Wokwi private gateway (`host.wokwi.internal`). The VS Code extension includes that gateway. The public broker is only for a first look.

## Check

The host test is the pass/fail gate.

## Solution

- `logic/solution/sensor_publish.c`
- `firmware/main/solution/app_main.c`

## Hints

- QoS 0 publish returns message id 0 on success and -1 on failure. Treat any id greater than or equal to 0 as published.
- Publish from the connected event. Publishing before that returns -1.
- Reuse the temperature formatting from lesson 12 inside `sensor_payload`.
