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

