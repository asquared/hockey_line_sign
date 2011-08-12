/*
 * Copyright (C) 2011 Exavideo LLC <exavideo@asquaredlabs.com>
 * 
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 */

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
