#pragma once

/* Increment the persisted boot counter in the "weather" namespace and return it. */
int nvs_next_boot(void);
