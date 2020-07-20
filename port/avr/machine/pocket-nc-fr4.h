/*
  pocket_nc_fr4.h - Pocket NC FR4 CNC default settings configuration file
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

#ifndef pocket_nc_fr4_h
#define pocket_nc_fr4_h

#include "arduino-atmega328p.h"

// Description: Pocket NC FR4 CNC mill.
#define DEFAULT_X_STEPS_PER_MM 800.0
#define DEFAULT_Y_STEPS_PER_MM 800.0
#define DEFAULT_Z_STEPS_PER_MM 800.0
#define DEFAULT_X_MAX_RATE 300.0 // mm/min
#define DEFAULT_Y_MAX_RATE 300.0 // mm/min
#define DEFAULT_Z_MAX_RATE 300.0 // mm/min
#define DEFAULT_X_ACCELERATION (30.0*60*60) // 15*60*60 mm/min^2 = 15 mm/sec^2
#define DEFAULT_Y_ACCELERATION (30.0*60*60) // 15*60*60 mm/min^2 = 15 mm/sec^2
#define DEFAULT_Z_ACCELERATION (30.0*60*60) // 15*60*60 mm/min^2 = 15 mm/sec^2
#define DEFAULT_X_MAX_TRAVEL 225.0 // mm NOTE: Must be a positive value.
#define DEFAULT_Y_MAX_TRAVEL 125.0 // mm NOTE: Must be a positive value.
#define DEFAULT_Z_MAX_TRAVEL 170.0 // mm NOTE: Must be a positive value.
#define DEFAULT_SPINDLE_RPM_MAX 7000.0 // rpm
#define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
#define DEFAULT_STEP_PULSE_MICROSECONDS 10
#define DEFAULT_STEPPING_INVERT_MASK 0
#define DEFAULT_DIRECTION_INVERT_MASK ((1<<Y_AXIS)|(1<<Z_AXIS))
#define DEFAULT_STEPPER_IDLE_LOCK_TIME 250 // msec (0-254, 255 keeps steppers enabled)
#define DEFAULT_STATUS_REPORT_MASK 3 // WPos enabled
#define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
#define DEFAULT_ARC_TOLERANCE 0.002 // mm
#define DEFAULT_REPORT_INCHES 0 // false
#define DEFAULT_INVERT_ST_ENABLE 1 // false
#define DEFAULT_INVERT_LIMIT_PINS 0 // false
#define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
#define DEFAULT_HARD_LIMIT_ENABLE 0  // false
#define DEFAULT_INVERT_PROBE_PIN 0 // false
#define DEFAULT_LASER_MODE 0 // false
#define DEFAULT_HOMING_ENABLE 1  // false
#define DEFAULT_HOMING_DIR_MASK 1 // move positive dir
#define DEFAULT_HOMING_FEED_RATE 100.0 // mm/min
#define DEFAULT_HOMING_SEEK_RATE 300.0 // mm/min
#define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
#define DEFAULT_HOMING_PULLOFF 3.0 // mm

#endif
