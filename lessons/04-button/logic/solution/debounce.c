#include "debounce.h"

void debounce_init(debounce_t *db, int level)
{
    if (db == NULL) {
        return;
    }
    db->stable = level ? 1 : 0;
    db->candidate = db->stable;
    db->count = 0;
}

int debounce_update(debounce_t *db, int level, int need)
{
    if (db == NULL || (level != 0 && level != 1)) {
        return 0;
    }
    if (need < 1) {
        need = 1;
    }
    if (level == db->stable) {
        db->candidate = level;
        db->count = 0;
        return 0;
    }
    if (level != db->candidate) {
        db->candidate = level;
        db->count = 1;
    } else {
        db->count++;
    }
    if (db->count >= need) {
        db->stable = level;
        db->count = 0;
        return 1;
    }
    return 0;
}
