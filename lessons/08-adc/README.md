# Lesson 08 — Scale an ADC reading

About one hour. The chip gives you a raw count. You turn it into a percent a person can read.

## What you will learn

- What a 12-bit ADC reading means (0 to 4095)
- How to round to the nearest percent without floating point
- How the oneshot ADC driver is configured, so you can read the boilerplate and trust it

## The task

Implement `raw_to_percent()` in `logic/raw_to_percent.c`.

- `raw <= 0` returns 0
- `raw >= 4095` returns 100
- Otherwise return `(raw * 100 + 2047) / 4095`, which rounds to the nearest percent

The firmware already configures ADC1 channel 6, which is GPIO34, and prints `adc percent=<n>` twice a second. The potentiometer in the diagram is the voltage on that pin.

## Acceptance

- `0` and negative raw values return 0. `4095` and anything above it return 100
- `2048` returns 50. `20` returns 0. `21` returns 1
- `./scripts/check-lesson.sh 08` passes
- Dragging the Wokwi potentiometer changes the logged percent

## Read

- [ADC oneshot mode](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/peripherals/adc_oneshot.html)
- Example to read after you finish: [peripherals/adc/oneshot_read](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/peripherals/adc/oneshot_read)

## Build and simulate

```bash
./scripts/check-lesson.sh 08
```

Build `lessons/08-adc/firmware` and start Wokwi. Move the potentiometer while the log scrolls.

## Check

The host test checks the arithmetic. The scenario checks that a percent line is printed. The slider is a visual check: the simulated millivolts are not a strict unit test.

## Solution

`logic/solution/raw_to_percent.c`.

## Hints

- Clamp before the multiply so a negative raw cannot underflow the formula.
- `2047` is half of 4095, the usual "add half a step before dividing" rounding trick.
- GPIO34 is input-only on the ESP32. That is why the pot is not on GPIO2.
