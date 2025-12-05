/*
 * File:   TimerMod.cpp
 * Author: olivier
 *
 * Created on August 2, 2024, 4:27 PM
 */

#include "TimerMod.h"
#include "EventQueue.h"
#include "Rtc.h"

/** Configure timers.
 */
TimerMod::TimerMod()
{
    // Disable prescaler sync
    GTCCR = 0;

    // -----------------------------------------------
    // ADC. Prescaler 1us, couter: 125us
    // Delay, one shot
    TCCR0A = 0x02; // WGM[1:0] = 10
    TCCR0B = 0x00; // CS[2:0] = 000, enable with 010
    TCNT0 = 0;
    OCR0A = 124;
    TIMSK0 = (1 << OCIE0A);
    TIFR0 = (1 << TOV0) | (1 << OCF0A) | (1 << OCF0B);

    // -----------------------------------------------
    // Free running
    TCCR1A = 0;
    TCCR1B = (1 << CS10);
    TCCR1C = 0;
    TCNT1 = 0;
    TIMSK1 = 0;

    // -----------------------------------------------
    // SystemTick
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << FOC2A); // Set to 0x84 to start counting
    TCNT2 = 0;
    OCR2A = 124;            // Steps of 0.5us
    OCR2B = 0;              // Unused
    TIMSK2 = (1 << OCIE2A); // None
    TIFR2 = (1 << TOV2) | (1 << OCF2A) | (1 << OCF2B);

    // -----------------------------------------------
    // RTC
    TCCR3A = 0; // WGM[1:0] = 00]
    TCCR3B = (1 << WGM32);
    TCCR3C = 0;
    OCR3A = 31249;
    TCNT3 = 0;
    TIMSK3 = (1 << OCIE3A);
    TIFR3 = (1 << ICF3) | (1 << OCF3C) | (1 << OCF3B) | (1 << OCF3A) | (1 << TOV3);
}

// ===========================================================================

// ADC channel change
ISR(TIMER0_COMPA_vect)
{
    timers.StopAdcTimer();
    Queue.Push(ADC_ELAPSED, 0, 0);
}

// N.A.
ISR(TIMER0_COMPB_vect)
{
    while (1)
        ;
}

// N.A.
ISR(TIMER0_OVF_vect)
{
    while (1)
        ;
}

// ==========================================================================

// Not used
ISR(TIMER1_CAPT_vect)
{
    while (1)
        ;
}

// Not used
ISR(TIMER1_COMPA_vect)
{
    while (1)
        ;
}

// Not used
ISR(TIMER1_COMPB_vect)
{
    while (1)
        ;
}

// Not used
ISR(TIMER1_COMPC_vect)
{
    while (1)
        ;
}

// Not used
ISR(TIMER1_OVF_vect)
{
    while (1)
        ;
}

// ===========================================================================

// SysTick
ISR(TIMER2_COMPA_vect)
{
    Queue.Push(SYSTICK_ELAPSED, 0, 0);
}

// N.A.
ISR(TIMER2_COMPB_vect)
{
    while (1)
        ;
}

// N.A.
ISR(TIMER2_OVF_vect)
{
    while (1)
        ;
}

// ===========================================================================

// N.A.
ISR(TIMER3_CAPT_vect)
{
    while (1)
        ;
}

// RTC
ISR(TIMER3_COMPA_vect)
{
    rtc.Increment();
    Queue.Push(RTC_ELAPSED, 0, 0);
}

// N.A.
ISR(TIMER3_COMPB_vect)
{
    // rtc_increment();
    Queue.Push(RTC_ELAPSED, 0, 0);
}

// N.A.
ISR(TIMER3_COMPC_vect)
{
    while (1)
        ;
}

// N.A.
ISR(TIMER3_OVF_vect)
{
    while (1)
        ;
}
