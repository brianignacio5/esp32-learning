#include "raw_to_percent.h"

int raw_to_percent(int raw)
{
    if (raw <= 0) {
        return 0;
    }
    if (raw >= 4095) {
        return 100;
    }
    return (raw * 100 + 2047) / 4095;
}
