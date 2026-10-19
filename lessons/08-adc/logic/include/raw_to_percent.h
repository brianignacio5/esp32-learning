#pragma once

/* Map a 12-bit ADC reading to a percent in the range 0..100.
   raw <= 0 returns 0. raw >= 4095 returns 100.
   Otherwise return (raw * 100 + 2047) / 4095, which rounds to nearest. */
int raw_to_percent(int raw);
