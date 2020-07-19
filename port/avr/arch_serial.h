/*
  arch_serial.h - Serial port architecture-specific definitions
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

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

#ifndef arch_serial_h
#define arch_serial_h

// Enable Data Register Empty Interrupt to make sure tx-streaming is running
#define SERIAL_START_WRITE \
  UCSR0B |=  (1 << UDRIE0)

// Turn off Data Register Empty Interrupt to stop tx-streaming if this concludes the transfer
#define SERIAL_STOP_WRITE \
  UCSR0B &= ~(1 << UDRIE0)

// Send a byte from the buffer
#define SERIAL_OUT(c) \
  UDR0 = c;

// Read a byte from serial port
#define SERIAL_IN \
  UDR0

#endif
