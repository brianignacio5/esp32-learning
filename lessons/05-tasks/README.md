# Lesson 05 — Two FreeRTOS tasks

About one hour. `app_main` starts the work and then returns. Two tasks keep running.

## What you will learn

- How to create a task with `xTaskCreate`
- How each task has its own stack and a priority
- How `vTaskDelay` lets the other task run

## The task

In `firmware/main/app_main.c`:

1. Configure GPIO2 as an output (the LED from lesson 03)
2. Log `tasks started`
3. Create a logger task that logs `tick` every 1000 ms
4. Create a blink task that toggles GPIO2 every 500 ms and logs `led on` or `led off`

Use a stack of 2048 words and priority 5 for both. The names `logger` and `blink` are enough.

## Acceptance

- After `tasks started`, the log shows both `tick` and `led on`
- The LED blinks twice as fast as the tick line
- `app_main` does not contain the infinite loops. Those live in the tasks

## Read

- [FreeRTOS task API](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/system/freertos_idf.html)
- Example to read after you finish: [basic_freertos_smp_usage](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/system/freertos/basic_freertos_smp_usage)

## Build and simulate

Open `lessons/05-tasks/firmware`, set the target to `esp32`, build, and start Wokwi.

## Check

There is no host test. The scenario waits for `tasks started`, then `tick`, then `led on`.

## Solution

`firmware/main/solution/app_main.c`.

## Hints

- A task function is `void task(void *arg)` and usually loops forever.
- `xTaskCreate(fn, "name", 2048, NULL, 5, NULL)` is the call. Check that it returns `pdPASS` if you want to be strict.
- Log `tasks started` before creating the tasks so a test can tell setup from the later lines.
