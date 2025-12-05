/**
 *
 */

#ifndef __POWER_METER_H_INCLUDED__
#define __POWER_METER_H_INCLUDED__

#include <avr/interrupt.h>
#include <avr/io.h>

#define __AVR_AT90USB647__ 1

#define LED_SET_CHARGING (PORTA |= 1)
#define LED_CLR_CHARGING (PORTA &= ~1)
#define LED_SET_SINKING (PORTA |= 2)
#define LED_CLR_SINKING (PORTA &= ~2)

#endif // __POWER_METER_H_INCLUDED__
