/*
 * File:   TimerMod.cpp
 * Author: olivier
 *
 * Created on August 2, 2024, 4:27 PM
 */

#include "TimerMod.h"
#include "EventQueue.h"
#include "Rtc.h"
#include "KeysMod.h"
#include "PowerMeter.h"

/** Configure timers.
 */
TimerMod::TimerMod()
{
    // Disable prescaler sync
    GTCCR = 0;

    // -----------------------------------------------
    // ADC. Prescaler 1us, counter: 125us
    // Delay, one shot
    TCNT0 = 0;
    // COM0A: 00 (OC0A disconnected), COM0B: 00 (OC0B disconnected)
    // WGM[2:0] = 010 (Mode 2 - Clear Timer on Compare Match, count up to OCRA)
    TCCR0A = (1 << WGM01); // WGM[1:0] = 10
    TCCR0B = 0x00; // CS[2:0] = 000, enable with 010
    OCR0A = 124;
    OCR0B = 0; // Unused
    TIMSK0 = (1 << OCIE0A);
    TIFR0 = (1 << TOV0) | (1 << OCF0A) | (1 << OCF0B);

    // -----------------------------------------------
    // Free running - start at boot
    TCCR1A = 0;
    TCCR1B = (1 << CS10);
    TCCR1C = 0;
    TCNT1 = 0;
    TIMSK1 = 0;

    // -----------------------------------------------
    // SystemTick
    TCNT2 = 0;
    // COM2A: 00 (OC2A disconnected), COM2B: 00 (OC2B disconnected)
    // WGM[2:0] = 010 (Mode 2 - CTC: Clear Timer on Compare Match, count up to OCRA)
    TCCR2A = (1 << WGM21);
    // Force Output Compare for OCRA enabled and OCRB disabled
    TCCR2B = (1 << FOC2A); // Set CS2 to 0x4 to start counting
    OCR2A = 124; // Steps of 0.5us
    OCR2B = 0; // Unused
    TIMSK2 = (1 << OCIE2A); // None
    TIFR2 = (1 << TOV2) | (1 << OCF2A) | (1 << OCF2B);

    // Set CS2 to 0x4 to start counting
    // TCCR2B = (1 << FOC2A) | (1 << CS22);

    // -----------------------------------------------
    // RTC
    TCNT3 = 0;
    // COM3A: 00 (OC3A disconnected), COM3B: 00 (OC3B disconnected)
    // WGM[3:0] = 0100 (Mode 4 - CTC: Clear Timer on Compare Match, count up to OCRA)
    TCCR3A = 0; // WGM[1:0] = 00]
    // ICNC3: 0 (Input Capture Noise Canceler disabled), ICES3: 0 (rising edge)
    // ICES3: 0 (falling edge), WGM32: 1, CS[2:0] = 100 (prescaler x256)
    // WGM3[3:2] = 10
    // CS[2:0] = 000 - set to 100 to start counting with /256 prescaler
    TCCR3B = (1 << WGM32);
    // FOC3A, FOC3B and FOC3C disabled
    TCCR3C = 0;
    // Set OCR3A for 1 second at 8MHz with /256 prescaler
    OCR3A = 31249;
    // Enable interrupt on OCR3A match
    TIMSK3 = (1 << OCIE3A);
    // Clear pending interrupt flags
    TIFR3 = (1 << ICF3) | (1 << OCF3C) | (1 << OCF3B) | (1 << OCF3A) | (1 << TOV3);
}

void TimerMod::startAdcTimer(uint8_t delay)
{
    TCNT0 = 0;
    OCR0A = delay;
    TCCR0B |= (1 << CS01); // Prescaler x8, 1us steps
}

// ===========================================================================

// ADC channel change
ISR(TIMER0_COMPA_vect)
{
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
    Queue.push(ADC_ELAPSED, 0, 0);
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
    uint8_t keyState;

    Queue.push(SYSTICK_ELAPSED, 0, 0);
    keyState = Keys.probe();
    if (Keys.getLastState() != 0) {
        powerMeter.setLedSink(1);
    } else {
        powerMeter.setLedSink(0);
    }
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
    rtc.increment();
    Queue.push(RTC_ELAPSED, 0, 0);
}

// N.A.
ISR(TIMER3_COMPB_vect)
{
    // rtc_increment();
    // Queue.Push(RTC_ELAPSED, 0, 0);
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
