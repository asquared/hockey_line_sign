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

#ifndef _CLOCK_H
#define _CLOCK_H

#include <stdint.h>

struct clock {
    int8_t ten_days, days;
    int8_t ten_hours, hours;
    int8_t ten_minutes, minutes;
    int8_t ten_seconds, seconds;
    int8_t tenths, hundredths;
};

int update_clock(struct clock *clock, uint8_t n_ticks);

#endif
