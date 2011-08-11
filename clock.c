#include "clock.h"

int update_clock(struct clock *clock, uint8_t n_ticks) {
    while (n_ticks >= 128) {
        update_clock(clock, 127);
        n_ticks -= 127;
    }

    clock->hundredths -= n_ticks;

    /* borrowing */
    while (clock->hundredths < 0) {
        clock->tenths--;
        clock->hundredths += 10;
    }

    while (clock->tenths < 0) {
        clock->seconds--;
        clock->tenths += 10;
    }

    while (clock->seconds < 0) {
        clock->ten_seconds--;
        clock->seconds += 10;
    }

    while (clock->ten_seconds < 0) {
        clock->minutes--;
        clock->ten_seconds += 6;
    }

    while (clock->minutes < 0) {
        clock->ten_minutes--;
        clock->minutes += 10;
    }

    while (clock->ten_minutes < 0) {
        clock->hours--;
        clock->ten_minutes += 6;
    }

    while (clock->hours < 0) {
        clock->ten_hours--;
        clock->hours += 10;
    }

    while (clock->ten_hours < 0) {
        clock->days--;
        /* this could do stupid things?? */
        clock->ten_hours += 2;
        clock->hours += 4;
    }

    while (clock->days < 0) {
        clock->ten_days--;
        clock->days += 10;
    }

    if (clock->ten_days < 0) {
        clock->ten_days = 0;
        return 0; /* time's up! */
    } else {
        return 1; /* time still left on the clock */
    }
}
