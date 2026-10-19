#include "click_count.h"

int click_count_hit(int *total, int every)
{
    if (total == NULL || every < 1) {
        return -1;
    }
    *total += 1;
    if ((*total % every) == 0) {
        return 1;
    }
    return 0;
}
