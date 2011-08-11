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
