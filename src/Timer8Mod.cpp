/* 
 * File:   TimerMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:32 PM
 */

#include "Timer8Mod.h"
#include "EventQueue.h"


typedef struct Timer8_t {
    uint8_t     tccra;
    uint8_t     tccrb;
    uint8_t     tcnt;
    uint8_t     ocra;
    uint8_t     ocrb;
} Timer8_t;

Timer8Mod Timer0;

Timer8Mod::Timer8Mod() {
    GTCCR = 0;

    // Mode CTC (WGM = 010)
    TCCR0A = 0x02;      // WGM0 and WGM1
    TCCR0B = 0;         // Set to 0x02 to start counting
    TCNT0 = 0;
    OCR0A = 0;          // Steps of 0.5us
    OCR0B = 0;          // Unused
    TIMSK0 = 0x02;      // OCIE0A
}

//Timer8Mod::Timer8Mod(const Timer8Mod& orig) {
//}

//Timer8Mod::~Timer8Mod() {
//}


int8_t  Timer8Mod::SetTimer(uint8_t t, uint8_t arg0)
{
    int8_t ret = -1;

    if (t < 128)        {
        OCR0A = t << 1;
        TCCR0B = 0x02;
        EventArg0 = arg0;
        ret = 0;
    }
    return ret;
}

ISR(TIMER0_COMPA_vect)
{
    TCCR0B = 0;         // Stop counting
    TIFR0 = 0x02;       // Optional - OCF0A
    Queue.Push(TIMER0_ELAPSED, 0, 0);
}


