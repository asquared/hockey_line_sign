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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile uint8_t counts;

void main_timer_init(void) {
    TCCR1A = 0x00; /* count to OCR1A, disable compare outputs */
    TCCR1B = 0x0b; /* count to OCR1A and enable 1/64 prescale */
    OCR1A = 2499; /* 2500 counts at 250kHz = 1/100 sec */
    TIMSK1 |= (1<<OCIE1A); /* interrupt on overflow */
}

ISR(TIMER1_COMPA_vect) {
    counts++;
}

uint8_t main_timer_counts(void) {
    uint8_t old_counts;

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        old_counts = counts;
        counts = 0;
    }

    return old_counts;
}
