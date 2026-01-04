/*
 * File:   TimerMod.h
 * Author: olivier
 *
 * Created on August 2, 2024, 4:27 PM
 */

#ifndef TIMERMOD_H
#define TIMERMOD_H

/** Timers implementation.
 *
 * The assignment is as follows:
 * - Timer0:    Delay for ADC channel selection (125us)
 *  + CTC mode (WGM[2:0] = 011
 *  + Single shot (the counter is disabled within the interrupt handler)
 *  + Prescaler: x8 (1us steps)
 *  + OCR0A: Definition of the delay
 *  + Interrupt vector OCIE0A in TIMSK0
 *
 * - Timer1:    Free-running counter
 *  + Waveform Generation Mode: normal (WGM[2:0] = 000)
 *  + Clock Select: no prescaling (CLKio / 1)
 *  + No interrupt
 *
 * - Timer2:    System tick (interrupt @1kHz)
 *  + Waveform Generation Mode: CTC / OCRA (WGM[2:0] = 010)
 *  + Prescaler: 000 at boot, CLK/64 (CS2[2:0] = 100) to enable
 *  + OCRA = 124
 *  + Interrupt OCIE2A
 *
 * - Timer3:    RTC
 *  + Waveform Generation Mode: CTC / OCRA (WGM[2:0] = 100)
 *  + Prescaler: CLK/256 (CS[2:0] = 100), OCRA = 31249
 *  + Interrupt OCIE3A
 *
 */

#include <string.h>

#include "arch.h"

#include "PowerMeter.h"

class TimerMod {
public:
    /// Constructor.
    TimerMod();
    // TimerMod(const TimerMod& orig);
    // virtual ~TimerMod();

    void startAdcTimer(uint8_t delay);

    void stopAdcTimer(void)
    {
        TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
        TCNT0 = 0;
    }

    /** Start the counter, prescaler x128
     *  Counter (divider) x125, 2ms tick
     */
    void startSystickTimer(void)
    {
        TCCR2B |= (1 << CS22) | (1 << CS20);
    }

    void stopSystickTimer(void)
    {
        TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
        TCNT2 = 0;
    }

    void startTimer3(void)
    {
        TCCR3B |= (1 << CS32);
    }

    void stopTimer3(void)
    {
        TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30));
    }

    void resetTimer3(void)
    {
        TCNT3 = 0;
    }

    uint16_t getClockTime() { return TCNT1; }

private:
};

extern TimerMod timers;

#endif /* TIMERMOD_H */
