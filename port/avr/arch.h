/*
  arch.h - AVR architecture definitions
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _arch_h
#define _arch_h

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <math.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Useful macros

/// Join two tokens together and interpret the result as a new token
#define JOIN2(a,b)              _JOIN2(a, b)
#define _JOIN2(a,b)             a##b

/* Execute instructions atomically, with interrupts disabled */
#define ATOMIC(instr) \
  do { \
    uint8_t sreg = SREG; \
    cli(); \
    instr; \
    SREG = sreg; \
  } while (0)

// AVR architecture support for Grbl

#include "arch_gpio.h"
#include "arch_timer.h"
#include "arch_serial.h"

#endif
