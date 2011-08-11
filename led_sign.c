#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "usb_serial.h"

int main(void) {
    CPU_PRESCALE(0);

    usb_init( );

    for (;;) {
        usb_serial_putchar(usb_serial_getchar( ));
    }
}
