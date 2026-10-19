# Lesson 07 — Remember something in NVS

About one hour. RAM forgets a reboot. NVS is a small key-value store in flash that does not.

## What you will learn

- How to initialize NVS, and when an erase-and-retry is the right recovery
- How to open a namespace and get, set, and commit an integer
- How a missing key (`ESP_ERR_NVS_NOT_FOUND`) differs from a real failure

## The task

In `app_main`, using the namespace `lesson`:

1. Initialize NVS. If init reports `ESP_ERR_NVS_NO_FREE_PAGES` or `ESP_ERR_NVS_NEW_VERSION_FOUND`, erase and init again.
2. Read the `int32` key `boot_count`. Treat a missing key as 0. Add one, store it, and log `boot_count=<number>`.
3. Read the `uint8` key `led`. Treat a missing key as 0. Invert it, store it, drive GPIO2 with that level, and log `led_state=<0 or 1>`.
4. Commit, then close the handle.

## Acceptance

- A fresh simulator logs `boot_count=1` and `led_state=1`, and the LED is on
- Restart the simulator without wiping flash. The next boot logs `boot_count=2` and `led_state=0`, and the LED is off
- Both keys are written before `nvs_commit`

## Read

- [Non-volatile storage](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/storage/nvs_flash.html)
- Example to read after you finish: [storage/nvs/nvs_rw_value](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/storage/nvs/nvs_rw_value)

## Build and simulate

Open `lessons/07-nvs/firmware`, build for `esp32`, and start Wokwi. Use the simulator's restart action for the second boot. Do not start a brand new simulation if you want the count to grow: a new simulation starts from empty flash again.

## Check

The scenario covers the first boot (`boot_count=1` and `led_state=1`). The second boot is the manual check in the steps above. There is no host test; the useful part of this hour is the flash itself.

## Solution

`firmware/main/solution/app_main.c`.

## Hints

- `nvs_get_i32` returning `ESP_ERR_NVS_NOT_FOUND` is normal on the first boot. Leave your local variable at 0 and continue.
- `nvs_set_*` does not hit flash until `nvs_commit`.
- GPIO2 is already configured for you. You only set the level.
