#ifndef _DISPLAY_IO_H
#define _DISPLAY_IO_H

#include <stdint.h>

/* Initialize I/O lines */
void display_io_init(void);

/* Turn horn ON */
void horn_on(void);

/* Turn horn OFF */
void horn_off(void);

/* set a given digit to display the given value */
void set_digit(uint8_t digit, uint8_t value);

/* test all digits on display */
void lamp_test(void);

#endif

