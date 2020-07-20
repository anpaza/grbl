/*
  machine.h - Platform-specific Grbl configuration
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

#ifndef machine_h
#define machine_h

/*
 * This file is included from grbl.h to declare all port mappings,
 * features and default settings for machine type selected by user.
 * Machine type selection is made by assigning a value to the
 * MACHINE variable in root makefile or on the 'make' command line.
 * Then, the file port/avr/machine/$(MACHINE).h will be included
 * below. It is expected to:
 *
 * - Define peripherial devices (GPIOs, timers and so on) used by
 *   Grbl on this type of machine.
 * - Define or re-define compile-time configurations for Grbl
 *   (see grbl/config.h).
 * - Define factory defaults for many Grbl '$' system parameters.
 *
 * On AVR the first goal is usually achieved by including the file
 * arduino-atmega328p.h. It can be influenced by some #define's
 * (e.g. ENABLE_DUAL_AXIS) which you should define in your machine
 * header file before including arduino-atmega328p.h.
 */

// Include the header file describing target board
#include MACHINE_H

#endif
