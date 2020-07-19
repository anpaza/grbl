/*
  arch_timer.h - AVR timers
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

#ifndef _arch_timer_h
#define _arch_timer_h

/*
 * Timer cross-platform wrappers.
 *
 * For stepping Grbl uses two timers: Stepper Pulse Timer (SPT) to pulse stepping
 * motors and Stepper Reset Timer (SRT) to reset stepper pulse pins after certain
 * amount of microseconds (controlled by the $0 parameter).
 *
 * When variable-speed spindle is used (VARIABLE_SPINDLE), another timer is used
 * to generate the PWM signal for spindle controller: Variable Spindle Timer (VST).
 *
 * Also, if software debouncing for LIMIT pins is enabled (ENABLE_SOFTWARE_DEBOUNCE),
 * one more Debounce Timer (DT) is used.
 *
 * On AVR we use:
 * - the 8-bit timer 0 for SRT.
 * - the 16-bit timer 1 for SPT.
 * - 8-bit timer 2 for VST.
 * - Watchdog timer for DT.
 */

/**
 * Configure Timer 1: Stepper Driver Interrupt
 */
#define SPT_INIT \
  do { \
    TCCR1B &= ~(1<<WGM13); /* waveform generation = 0100 = CTC */ \
    TCCR1B |=  (1<<WGM12); \
    TCCR1A &= ~((1<<WGM11) | (1<<WGM10)); \
    TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0)); /* Disconnect OC1 output*/ \
    /* TCCR1B = (TCCR1B & ~((1<<CS12) | (1<<CS11))) | (1<<CS10); // Set in st_go_idle(). */ \
    /* TIMSK1 &= ~(1<<OCIE1A);  // Set in st_go_idle(). */ \
  } while (0)

/**
 * Start SPT interrupt generation.
 */
#define SPT_START \
  do { \
    TIMSK1 |= (1<<OCIE1A); \
  } while (0)

/**
 * Set SPT interrupt period.
 * @param period Stepper Pulse Timer period in timer clocks.
 */
#define SPT_SET(period) \
  do { \
    OCR1A = period; \
  } while (0)

/**
 * Stop SPT interrupts.
 */
#define SPT_STOP \
  do { \
    /* Disable Timer1 interrupt */ \
    TIMSK1 &= ~(1<<OCIE1A); \
    /* Reset clock to no prescaling. */ \
    TCCR1B = (TCCR1B & ~((1<<CS12) | (1<<CS11))) | (1<<CS10); \
  } while (0)

// -------------------------------------------------------------------------- //

#ifdef STEP_PULSE_DELAY
// Enable Timer0 overflow interrupt and Compare Match A interrupt
# define TIMSK0_INIT ((1<<TOIE0) | (1<<OCIE0A))
#else
// Enable Timer0 overflow interrupt
# define TIMSK0_INIT (1<<TOIE0)
#endif

/**
 * Configure Timer 0: Stepper Port Reset Interrupt
 */
#define SRT_INIT \
  do { \
    /* Disconnect OC0 outputs and OVF interrupt. */ \
    TIMSK0 &= ~((1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0)); \
    TCCR0A = 0; /* Normal operation */ \
    TCCR0B = 0; /* Disable Timer0 until needed */ \
    TIMSK0 |= TIMSK0_INIT; \
  } while (0)

/**
 * Convert microseconds to SRT period in timer ticks.
 */
#define SRT_PERIOD(us)

/**
 * Set SRT interrupt period.
 * @param period Stepper Reset Timer period in timer clocks.
 *  This value is computed with the SRT_PERIOD(us) macro.
 */
#define SRT_SET(period) \
  do { \
    /* Reload Timer0 counter */ \
    TCNT0 = period; \
  } while (0)

/**
 * Start SRT interrupt generation.
 */
#define SRT_START \
  do { \
    /* Begin Timer0. Full speed, 1/8 prescaler */ \
    TCCR0B = (1<<CS01); \
  } while (0)

/**
 * Stop SRT interrupts.
 */
#define SRT_STOP \
  do { \
    TCCR0B = 0; \
  } while (0)

// -------------------------------------------------------------------------- //

/*
 * Another timer is used for spindle PWM (if VARIABLE_SPINDLE is defined).
 * We'll name it Variable Spindle Timer (VST).
 */

/**
 * Configure Variable Spindle Timer (VST)
 */
#define VST_INIT \
  do { \
    /* Configure PWM output compare timer */ \
    SPINDLE_TCCRA_REGISTER = SPINDLE_TCCRA_INIT_MASK; \
    SPINDLE_TCCRB_REGISTER = SPINDLE_TCCRB_INIT_MASK; \
  } while (0)

/**
 * Set spindle PWM duty factor.
 * @param duty A value between SPINDLE_PWM_OFF_VALUE and SPINDLE_PWM_MAX_VALUE.
 */
#define VST_PWM(duty) \
  do { \
    /* Set PWM output level. */ \
    SPINDLE_OCR_REGISTER = duty; \
  } while (0)

/**
 * Check if VST PWM output is running
 */
#define VST_ENABLED \
  (SPINDLE_TCCRA_REGISTER & (1<<SPINDLE_COMB_BIT))

#define VST_ENABLE(state) \
  do { \
    if (state) \
      SPINDLE_TCCRA_REGISTER |= (1<<SPINDLE_COMB_BIT); \
    else \
      SPINDLE_TCCRA_REGISTER &= ~(1<<SPINDLE_COMB_BIT); \
  } while (0)

// -------------------------------------------------------------------------- //

#define DT_INT_vect WDT_vect

/**
 * Configure debouncing timer
 */
#define DT_INIT \
  do { \
    MCUSR &= ~(1<<WDRF); \
    WDTCSR |= (1<<WDCE) | (1<<WDE); \
    /* Set time-out at ~32msec */ \
    WDTCSR = (1<<WDP0); \
  } while (0)

/**
 * Start DT interrupt generation.
 */
#define DT_START \
  do { \
    if (!(WDTCSR & (1<<WDIE))) { WDTCSR |= (1<<WDIE); } \
  } while (0)

/**
 * Stop DT interrupt generation.
 */
#define DT_STOP \
  do { \
    /* Disable watchdog timer */ \
    WDTCSR &= ~(1<<WDIE); \
  } while (0)

#endif
