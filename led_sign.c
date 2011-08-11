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

int main(void) {
    uint8_t i;
    uint8_t flag = 0;
    int16_t horn_timeout = 0;

    struct clock clock;

    CLKPR = 0x80;
    CLKPR = 0x00;

    display_io_init( );
    lamp_test( );
    usb_init( );
    main_timer_init( );
    sei( );

    memset(&clock, 0, sizeof(struct clock));
    clock.ten_seconds = 1;

    for (;;) {
        if (usb_serial_available( ) > 0) {
            /* process input */
            usb_serial_flush_input( ); /* whoops */
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
