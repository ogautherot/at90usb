/* 
 * File:   ClockMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:25 PM
 */

#include <avr/cpufunc.h>

#include "ClockMod.h"


extern volatile uint32_t ClockModCnt;
volatile uint32_t ClockModCnt = 1;

/** Disable the CPU prescaler and start the PLL.
 */
ClockMod::ClockMod() {
    // Disable prescaler - CLKPS[3:0]]
    CLKPR = CLKPCE;
    CLKPR = 0;

    // Enable PLL
    PLLCSR = (1 << PLLP1) | (1 << PLLP0) | (1 << PLLE);
    while (PLLCSR & (1 << PLOCK))
        ClockModCnt++;
}

