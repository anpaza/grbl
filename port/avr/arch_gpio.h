/*
  arch_gpio.h - GPIO access functions for AVR architecture
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

#ifndef _arch_gpio_h
#define _arch_gpio_h

/**
 * Grbl uses GPIO pins either separately, or as an atomic 'pin set'.
 * We'll call the later a 'virtual port', which contains only the
 * pins related to certain task, e.g. the STEP virtual port contains
 * the pins related to axis steppers, LIMIT contains the pins reflecting
 * limit switch states and so on.
 *
 * Thus, there are two groups of macros that work with GPIO pins.
 *
 * The macros having "PIN" in their name will work with single pins.
 * You may initialize, set, query the pin identified by a name.
 * The following pins are currently used by Grbl:
 *
 * - STEPPERS_DISABLE will disable (hold) all steppers at once
 * - PROBE inputs the probe state
 * - COOLANT_FLOOD controls flooding coolant
 * - COOLANT_MIST controls mist coolant
 * - SPINDLE_ENABLE turns on the spindle
 * - SPINDLE_DIRECTION controls spindle rotation direction
 * - SPINDLE_PWM is the pin that outputs the PWM signal used
 *     to control spindle rotation speed.
 *
 * The macros having "PINS" in their name work with a virtual port,
 * e.g. with multiple pins at once. You may query all the pins in a
 * virtual port, set all the pins at once. Currently the following
 * virtual ports are used in Grbl:
 *
 * - STEP contains the pins that pulse a step signal to axis steppers
 * - DIRECTION contains the pins controlling steppers rotation direction
 * - LIMIT contains the pins reflecting limit switch states for all axes
 * - CONTROL contains the user-control signals, e.g. RESET, FEED_HOLD etc.
 */

// This type can hold the pin mask for any pin of any port
typedef uint8_t gpio_pin_mask_t;

/**
 * Get the bitmask of a virtual port.
 *
 * @param vport Virtual port name.
 */
#define GPIO_PINS_MASK(vport) \
  JOIN2(vport, _MASK)

/**
 * Get the port id for certain pin. Function returns port id letter,
 * e.g. A, B, C, ...
 *
 * @param pin Pin or virtual port name
 */
#define GPIO_PORT(pin) \
  JOIN2(pin, _PORT)

/**
 * Initialize all pins in a virtual port
 */
#define GPIO_INIT_PINS(vport) \
  do { \
    if (JOIN2(vport, _DIR)) \
      JOIN2(DDR, GPIO_PORT(vport)) |= JOIN2(vport, _MASK); \
    else \
      JOIN2(DDR, GPIO_PORT(vport)) &= ~JOIN2(vport, _MASK); \
  } while (0)

/**
 * Set all the pins in a virtual port at once.
 * This is equivalent to: port = (port & ~mask) | (pins & mask)
 *
 * @param vport Virtual port identifier, one of STEP, DIRECTION, LIMIT, CONTROL.
 * @param pins Virtual port pin state, a bitwise OR of (1<<XXX_BIT) flags.
 */
#define GPIO_SET_PINS(vport,pins) \
  do { \
    JOIN2(PORT, GPIO_PORT(vport)) = (JOIN2(PORT, GPIO_PORT(vport)) & ~JOIN2(vport, _MASK)) | \
      ((pins) & JOIN2(vport, _MASK)); \
  } while (0)

/**
 * Get the states of all pins in a virtual port at once.
 * This is equivalent to: port & mask
 *
 * @param vport Virtual port identifier, one of STEP, DIRECTION, LIMIT, CONTROL.
 */
#define GPIO_GET_PINS(vport) \
  (JOIN2(PIN, GPIO_PORT(vport)) & JOIN2(vport, _MASK))

/**
 * Enable or disable internal pull-up resitors for pins.
 * Works only for virtual ports configured in input mode (XXX_DIR is 0).
 *
 * @param vport Virtual port identifier, one of STEP, DIRECTION, LIMIT, CONTROL.
 * @param state zero to disable pullups, non-zero to enable
 */
#define GPIO_PULLUP_PINS(vport, state) \
  GPIO_SET_PINS(vport, state)

// -------------------------------------------------------------------------- //

/**
 * Get the bitmask of a GPIO pin. The returned value is guaranteed to fit
 * into the gpio_pin_mask_t type.
 *
 * @param pin Pin name, one of STEPPERS_DISABLE, PROBE, COOLANT_FLOOD, COOLANT_MIST,
 *  SPINDLE_ENABLE, SPINDLE_DIRECTION, SPINDLE_PWM
 */
#define GPIO_PIN_MASK(pin) \
  (1 << JOIN2(pin, _BIT))

/**
 * Init a singleton GPIO pin
 * @param pin Pin name, one of STEPPERS_DISABLE, PROBE, COOLANT_FLOOD, COOLANT_MIST,
 *  SPINDLE_ENABLE, SPINDLE_DIRECTION, SPINDLE_PWM
 */
#define GPIO_INIT_PIN(pin) \
  do { \
    if (JOIN2(pin, _DIR)) \
      JOIN2(DDR, GPIO_PORT(pin)) |= GPIO_PIN_MASK(pin); \
    else \
      JOIN2(DDR, GPIO_PORT(pin)) &= ~GPIO_PIN_MASK(pin); \
  } while (0)

/**
 * Set a singleton GPIO pin
 * @param pin Pin name, one of STEPPERS_DISABLE, PROBE, COOLANT_FLOOD, COOLANT_MIST,
 *  SPINDLE_ENABLE, SPINDLE_DIRECTION, SPINDLE_PWM
 * @param state Pin state, zero or non-zero
 */
#define GPIO_SET_PIN(pin, state) \
  do { \
    if (state) \
      JOIN2(PORT, GPIO_PORT(pin)) |= GPIO_PIN_MASK(pin); \
    else \
      JOIN2(PORT, GPIO_PORT(pin)) &= ~GPIO_PIN_MASK(pin); \
  } while (0)

/**
 * Get the state of a singleton GPIO pin.
 * If GPIO is configured for output (pin_DIR is non-zero),
 * pin state is read from PORT register, otherwise from PIN.
 *
 * @param pin Pin name, one of STEPPERS_DISABLE, PROBE, COOLANT_FLOOD, COOLANT_MIST,
 *  SPINDLE_ENABLE, SPINDLE_DIRECTION, SPINDLE_PWM
 */
#define GPIO_GET_PIN(pin) \
  (JOIN2(pin, _DIR) ? \
   JOIN2(PORT, GPIO_PORT(pin)) & GPIO_PIN_MASK(pin) : \
   JOIN2(PIN, GPIO_PORT(pin)) & GPIO_PIN_MASK(pin))

/**
 * Enable or disable internal pull-up resitor for pin.
 * Works only for pins configured in input mode (XXX_DIR is 0).
 *
 * @param pin Pin name, one of STEPPERS_DISABLE, PROBE, COOLANT_FLOOD, COOLANT_MIST,
 *  SPINDLE_ENABLE, SPINDLE_DIRECTION, SPINDLE_PWM
 * @param state zero to disable pullups, non-zero to enable
 */
#define GPIO_PULLUP_PIN(pin, state) \
  GPIO_SET_PIN(pin, state)

// -------------------------------------------------------------------------- //

/**
 * Enable pin change interrupt for a virtual port.
 */
#define GPIO_IRQ_PINS(vport, state) \
  do { \
    if (state) {\
      /* Enable specific pins of the Pin Change Interrupt */ \
      JOIN2(vport, _PCMSK) |= JOIN2(vport, _MASK); \
      /* Enable Pin Change Interrupt */ \
      PCICR |= (1 << JOIN2(vport, _INT)); \
    } else { \
      /* Disable specific pins of the Pin Change Interrupt */ \
      JOIN2(vport, _PCMSK) &= ~JOIN2(vport, _MASK); \
      /* Disable Pin Change Interrupt */ \
      PCICR &= ~(1 << JOIN2(vport, _INT)); \
    } \
  } while (0)

#endif
