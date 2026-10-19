#pragma once

/* Join the Wokwi guest network. Returns 0 when the station has an IP.
   Returns -1 if it still has no IP after a short retry budget. */
int wifi_connect(void);
