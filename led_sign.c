#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>

#include "usb_serial.h"
#include "main_timer.h"
#include "display_io.h"
#include "clock.h"
#include "main_timer.h"

static void draw_clock(struct clock *clock) {
    set_digit(0, clock->hundredths);
    set_digit(1, clock->tenths);
    set_digit(2, clock->seconds);
    set_digit(3, clock->ten_seconds);
    set_digit(4, clock->minutes);
    set_digit(5, clock->ten_minutes);
    set_digit(6, clock->hours);
    set_digit(7, clock->ten_hours);
    set_digit(8, clock->days);
    set_digit(9, clock->ten_days);
}

static void execute_cmd(struct clock *clock, int where, int ch) {
    if (ch < '0' || ch > '9') {
        return;
    }

    int8_t new_hours;
    int8_t digit = ch - '0';

    switch (where) {
        case 'D': clock->ten_days = digit; break;
        case 'd': clock->days = digit; break;
        case 'H':
            new_hours = digit * 10 + clock->hours;
            if (new_hours < 24) {
                clock->ten_hours = digit;
            }
            break;
        case 'h':
            new_hours = 10 * clock->ten_hours + digit;
            if (new_hours < 24) {
                clock->hours = digit;
            }
            break;
        case 'M': if (digit < 6) clock->ten_minutes = digit; break;
        case 'm': clock->minutes = digit; break;
        case 'S': if (digit < 6) clock->ten_seconds = digit; break;
        case 's': clock->seconds = digit; break;
        case 'T': clock->tenths = digit; break;
        case 't': clock->hundredths = digit; break;
    }
}

int main(void) {
    uint8_t flag = 1;
    int16_t horn_timeout = 0;
    int ch;
    int where = 0;

    struct clock clock;

    CLKPR = 0x80;
    CLKPR = 0x00;

    display_io_init( );
    lamp_test( );
    usb_init( );
    main_timer_init( );
    sei( );

    memset(&clock, 0, sizeof(struct clock));

    for (;;) {
        if (usb_serial_available( ) > 0) {
            /* process input */
            ch = usb_serial_getchar( );
            switch (ch) {
                case 'p': /* pause */
                    flag = 1;
                    horn_timeout = 0;
                    break;

                case 'g': /* go */
                    flag = 0;
                    break;
    
                case 'D': /* 10-days */
                case 'd': /* days */
                case 'H': /* 10-hours */
                case 'h': /* hours */
                case 'M': /* 10-minutes */
                case 'm': /* minutes */
                case 'S': /* 10-seconds */
                case 's': /* seconds */
                case 'T': /* tenths */
                case 't': /* hundredths (tenths of tenths) */
                    where = ch;
                    break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    /* only execute commands when paused */
                    if (!flag) {
                        execute_cmd(&clock, where, ch);
                    }
                    break;
            }
        } else {
            if (!flag) {
                if (update_clock(&clock, main_timer_counts( )) == 0) {
                    flag = 1;
                    horn_timeout = 1000; /* 10 sec = 1000/100 sec */
                }
            } else {
                if (horn_timeout > 0) {
                    horn_on( );
                    horn_timeout -= main_timer_counts( );
                } else {
                    horn_off( );
                }
            }

            draw_clock(&clock);
        }
    }
}
