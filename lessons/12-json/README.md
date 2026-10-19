# Lesson 12 — A JSON reading

About one hour. No pins and no network. You build one JSON object and a host test parses it back.

## What you will learn

- How to build an object with cJSON and print it without extra whitespace
- Why a temperature in tenths should become a one-decimal JSON number
- How a unit test can parse your output instead of trusting a hand-written string only

## The task

Implement `reading_to_json()` in `logic/reading_json.c`.

For temperature 255 tenths, humidity 40, and boot 3, the text is:

```text
{"temp_c":25.5,"humidity":40,"boot":3}
```

Use cJSON for the object. `cJSON_AddNumberToObject` will not promise one decimal place, so format the temperature yourself (the same tenths split as lesson 02) and add it with `cJSON_AddRawToObject`. Humidity and boot are integers.

Return 0 on success. Return -1 for a NULL argument or a buffer that cannot hold the text. There is no partial JSON left behind on failure: either you write the whole string, or you return before writing.

## Acceptance

- The sample above matches that string exactly
- `-55` tenths becomes `"temp_c":-5.5`
- `./scripts/check-lesson.sh 12` passes
- The firmware log line contains `json {"temp_c":25.5,"humidity":40,"boot":3}`

## Read

- [cJSON in ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/system/misc_system_api.html) (the `json` component; the header is `cJSON.h`)
- cJSON's own comments in the header your build picks up from the ESP-IDF tree

## Build and simulate

```bash
./scripts/check-lesson.sh 12
```

`lessons/12-json/firmware` prints the sample reading. No Wi-Fi.

## Check

The host test checks the exact text and parses it with cJSON again. The scenario checks the same text on the serial log.

## Solution

`logic/solution/reading_json.c`.

## Hints

- `cJSON_PrintUnformatted` allocates a string. Free it with `cJSON_free`, and `cJSON_Delete` the object.
- A raw value of `25.5` is a JSON number, not a string. Do not add quotes around it.
