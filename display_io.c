#include <avr/io.h>
#include <util/delay.h>

#include "display_io.h"


void display_io_init(void) {
    /* BCD output */
    DDRD |= 0x0f;
    PORTD &= ~0x0f;

    /* digit latch outputs */
    DDRB = 0xff;
    PORTB = 0xff;
    DDRC |= 0xc0;
    PORTC |= 0xc0;

    /* horn */
    DDRD |= 0x40;
    PORTD &= ~0x40;
}

void horn_on(void) {
    PORTD |= 0x40;
}

void horn_off(void) {
    PORTD &= ~0x40;
}

static void digit_latch_enable(uint8_t digit) {
    switch (digit) {
        case 0: PORTB &= ~0x01; break;
        case 1: PORTB &= ~0x02; break;
        case 2: PORTB &= ~0x04; break;
        case 3: PORTB &= ~0x08; break;
        case 4: PORTB &= ~0x10; break;
        case 5: PORTB &= ~0x20; break;
        case 6: PORTB &= ~0x40; break;
        case 7: PORTB &= ~0x80; break;
        case 8: PORTC &= ~0x40; break;
        case 9: PORTC &= ~0x80; break;
    }
}

static void digit_latch_disable(void) {
    PORTB = 0xff;
    PORTC |= 0xc0;
}

static inline void nop(void) {
    __asm__ __volatile__("nop");
}

void set_digit(uint8_t digit, uint8_t value) {
    /* drive digit out on port B */
    value &= 0x0f;
    PORTB &= ~0x0f;
    PORTB |= value;

    /* make sure we meet the setup time */
    nop( );
    nop( );
    nop( );
    nop( );

    /* enable the digit latch */
    digit_latch_enable(digit);
    
    /* delay for minimum latch pulsewidth */
    nop( );
    nop( );
    nop( );
    nop( );

    /* done! (hold time is actually negative) */
    digit_latch_disable( );
}

void lamp_test(void) {
    uint8_t i, j;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            set_digit(j, i);
        }
        _delay_ms(250);
    }

    horn_on( );
    _delay_ms(250);
    horn_off( );
}
