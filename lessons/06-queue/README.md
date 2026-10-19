# Lesson 06 — A queue between two tasks

About one hour. One task notices the button. Another task counts. A queue is the only way they share the click.

## What you will learn

- How `xQueueCreate`, `xQueueSend`, and `xQueueReceive` move a small message between tasks
- Why the consumer blocks on the queue instead of polling a global
- How a tiny counter function stays easy to test on the host

## The task

1. Implement `click_count_hit()` in `logic/click_count.c`. It increments a total and returns 1 when that total is a positive multiple of `every`.
2. In `app_main.c`, create a queue of 8 `uint8_t` events.
3. Finish `button_task` so a debounced press sends one event. The debounce helper is already in the file.
4. Finish `consumer_task` so it waits for an event, calls `click_count_hit` with `every` 5, and logs `fifth click` when the function returns 1.

## Acceptance

- Starting from 0, calls with `every` 5 return 0, 0, 0, 0, 1, and the fifth call leaves the total at 5. The tenth call returns 1 again
- A NULL total or `every` less than 1 returns -1
- `./scripts/check-lesson.sh 06` passes
- Five presses in Wokwi produce the log line `fifth click`

## Read

- [FreeRTOS queues](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/system/freertos_idf.html)
- Example to read after you finish: [basic_freertos_smp_usage](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/system/freertos/basic_freertos_smp_usage)

## Build and simulate

```bash
./scripts/check-lesson.sh 06
```

Then build `lessons/06-queue/firmware` and start Wokwi. Press the button five times.

## Check

The host test checks the counter. The scenario presses the button five times and waits for `fifth click`.

## Solution

- `logic/solution/click_count.c`
- `firmware/main/solution/app_main.c`

## Hints

- `xQueueReceive(clicks, &event, portMAX_DELAY)` sleeps until a press arrives.
- Send `sizeof event` is wrong for this queue. You created it with `sizeof(uint8_t)`, so send the address of a `uint8_t` and a timeout of 0.
- Do not reset the total after a hit. The next report is the next multiple.
