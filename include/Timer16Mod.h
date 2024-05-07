/* 
 * File:   Timer16Mod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:34 PM
 */

/** Timers implementation
 *
 * Timer 1: free-running for execution time
 *      - x1 prescaler, 16MHz clock, free-running
 *      - no interrupts
 *
 * Timer 3: RTC
 *      - x64 prescaler, 250kHz clock
 *      - interrupts @10ms
 * 
 * */
#ifndef TIMER16MOD_H
#define	TIMER16MOD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include <string.h>


class Timer16Mod {
public:
    Timer16Mod();
    //Timer16Mod(const Timer16Mod& orig);
    //virtual ~Timer16Mod();

    void Init(uint8_t prescaler, uint16_t period);
    
private:

};

#endif	/* TIMER16MOD_H */

