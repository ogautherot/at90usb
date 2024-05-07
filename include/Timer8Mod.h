/* 
 * File:   TimerMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:32 PM
 */

/** Timers implementation
 *
 *  Timer 0: ADC timing (125us slots)
 *      - x8 prescaler, 0.5us resolution (2MHz)
 *      - single shot (stop upon counter match)
 *      - No OC signals
 *
 *  Timer 2: Unused
 *
 * */
#ifndef TIMER8MOD_H
#define	TIMER8MOD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include <string.h>
#include <stdint.h>


class Timer8Mod {
public:
    Timer8Mod();
    //Timer8Mod(const Timer8Mod& orig);
    //virtual ~Timer8Mod();

    int8_t      SetTimer(uint8_t t, uint8_t arg0);

private:
    uint8_t     tccra;
    uint8_t     tccrb;
    uint8_t     tcnt;
    uint8_t     ocra;
    uint8_t     ocrb;

    uint8_t     EventArg0;
};

#endif	/* TIMER8MOD_H */

