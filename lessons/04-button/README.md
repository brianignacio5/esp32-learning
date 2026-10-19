# Lesson 04 — A button and a debounce state machine

About one hour. The click detector is plain C, so a host test can poke it. The GPIO code only feeds it samples.

## What you will learn

- Why a raw GPIO read chatters, and how a counter of matching samples rejects that
- How an internal pull-up makes an open button read as 1, and a button to ground read as 0
- How to keep that policy out of the driver so it can be tested without a pin

## The task

1. Implement `debounce_init` and `debounce_update` in `logic/debounce.c`. The header describes when a sample changes the stable level.
2. In `firmware/main/app_main.c`, poll GPIO4 every 10 ms and pass the level to `debounce_update` with `need` set to 3. GPIO4 is the push button, wired to ground. Enable the pull-up.
3. When the stable level becomes 0 (a press), toggle GPIO2, the LED from lesson 03. Log `led on` or `led off`. A release must not toggle the LED.

## Acceptance

- Three matching new samples accept a level. A different sample in the middle starts the count over.
- `need` less than 1 behaves as 1. Levels other than 0 or 1 are ignored.
- `./scripts/check-lesson.sh 04` passes
- In Wokwi, pressing the button turns the LED on, and the next press turns it off

## Read

- [GPIO API](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/peripherals/gpio.html)
- Example to read after you finish: [peripherals/gpio/generic_gpio](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/peripherals/gpio/generic_gpio)

## Build and simulate

```bash
./scripts/check-lesson.sh 04
```

Firmware project: `lessons/04-button/firmware`. Build it for `esp32` and start Wokwi. The button part has bounce turned off so the scenario is about your state machine, not about contact noise. On a real button, `need` of 3 at 10 ms is 30 ms, which is a bit short; raise it once the test is green.

## Check

Host test for the state machine. Wokwi scenario for the LED.

## Solution

- `logic/solution/debounce.c`
- `firmware/main/solution/app_main.c`

## Hints

- Keep three fields: the stable level, the candidate level, and how many times the candidate has been seen in a row.
- If the new sample equals the stable level, the candidate was noise. Reset the count.
- Toggle only when `debounce_update` returns 1 and the new stable level is 0.
