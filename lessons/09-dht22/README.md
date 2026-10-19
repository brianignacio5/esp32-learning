# Lesson 09 — Decode a DHT22 frame

About one hour. The sensor's timing is fiddly, so the pulse reader is provided. You check the frame and turn it into numbers.

## What you will learn

- The DHT22's 40-bit frame: 16 bits of humidity, 16 bits of temperature, 8 bits of checksum
- How the checksum is the low 8 bits of the sum of the first four bytes
- How the top bit of the temperature word means "negative"

## The task

Implement `dht_decode()` in `logic/dht_decode.c`.

A frame is five bytes: humidity high, humidity low, temperature high, temperature low, checksum. Humidity and temperature are both in tenths (`400` means 40.0%, `255` means 25.5 C). If bit 15 of the temperature word is set, the lower 15 bits are a negative magnitude.

Return 0 and fill `out` when the checksum matches. Return -1, and leave `out` alone, when the pointer is NULL or the checksum does not match.

The firmware reader on GPIO15 calls your function and logs `temp_c_x10=<n> humidity_x10=<n>`.

## Acceptance

- Bytes `01 90 00 FF 90` decode to humidity 400 and temperature 255
- Bytes `01 90 80 37 48` decode to humidity 400 and temperature -55
- A flipped checksum byte returns -1
- `./scripts/check-lesson.sh 09` passes
- With the Wokwi DHT22 set to 25.5 C and 40% humidity, the log shows `temp_c_x10=255 humidity_x10=400`

## Read

- The frame layout above is the whole protocol you need. The reader in `firmware/main/dht_io.c` shows the start pulse and the bit timing if you want the rest.
- [GPIO API](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/peripherals/gpio.html) for the pull-up the data pin uses

## Build and simulate

```bash
./scripts/check-lesson.sh 09
```

Build `lessons/09-dht22/firmware` and start Wokwi. The scenario sets the sensor before the chip finishes booting. You can also drag the temperature and humidity sliders and watch the next line, about two seconds later. The DHT22 will not sample faster than that.

## Check

The host test feeds recorded frames. The scenario checks one live reading. If the live read misses a pulse, the firmware tries again. The host test does not depend on that.

## Solution

`logic/solution/dht_decode.c`.

## Hints

- Checksum: `(uint8_t)(frame[0] + frame[1] + frame[2] + frame[3])` compared with `frame[4]`.
- Temperature magnitude is `temp & 0x7FFF`. Apply the sign after that mask, not before.
