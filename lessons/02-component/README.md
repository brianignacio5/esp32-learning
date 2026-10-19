# Lesson 02 — A component and a host test

About one hour. The code you write does not touch a pin. A unit test on your computer tells you if it is right, and the firmware prints it.

## What you will learn

- How a project component is laid out (`CMakeLists.txt`, a header, a source file)
- How `snprintf` reports the length it wanted to write
- How to run a Unity test with the ESP-IDF linux target, with no board attached

## The task

Implement `format_reading()` in `logic/format_reading.c`. The contract is in `logic/include/format_reading.h`.

`temp_c_x10` is temperature in tenths of a degree: `235` means `23.5`, and `-55` means `-5.5`. Humidity is an integer percent. The text looks like `23.5C 40%`.

## Acceptance

- `format_reading(buf, sizeof buf, 235, 40)` writes `23.5C 40%`
- `-55` becomes `-5.5C`, and `-5` becomes `-0.5C` (do not print `-0` as `0`)
- A NULL buffer or a zero length returns `-1`
- A short buffer stays NUL-terminated and the return value is the full length, the same way `snprintf` works
- `./scripts/check-lesson.sh 02` passes
- The firmware log contains `reading 23.5C 40%`

## Read

- [Build system and components](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-guides/build-system.html)
- [Unit testing](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-guides/unit-tests.html)
- [Running applications on the host](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-guides/host-apps.html)
- Example to read after you finish: [system/unit_test](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/system/unit_test)

## Build and simulate

Firmware project: `lessons/02-component/firmware`.

```bash
idf.py set-target esp32
idf.py build
```

Host test, from `lessons/02-component/host_test` (or from the repo root):

```bash
./scripts/check-lesson.sh 02
```

That command copies the lesson to a temp directory, builds the linux target, and runs the Unity binary. It does not modify your files. Your stub returns `-1`, so the test fails until `format_reading` matches the header.

## Check

The host test is the pass/fail gate. Wokwi should then show `reading 23.5C 40%`.

## Solution

`logic/solution/format_reading.c`.

## Hints

- Split the tenths into a whole part and one decimal digit. For a negative value, format the minus sign yourself so `-5` stays `-0.5` and not `0.5`.
- Call `snprintf` and return what it returns. That gives you the truncation behavior for free.
