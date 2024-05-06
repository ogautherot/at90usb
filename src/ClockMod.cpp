/* 
 * File:   ClockMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:25 PM
 */

#include "ClockMod.h"

ClockMod::ClockMod() {
    // Disable prescaler
    CLKPR = 0;
    
    // Enable PLL
    PLLCSR = (6 << PLLP0) | (1 << PLLE);
}

//ClockMod::ClockMod(const ClockMod& orig) {
//}
//
//ClockMod::~ClockMod() {
//}



