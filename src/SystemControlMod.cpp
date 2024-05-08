/* 
 * File:   SystemControlMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:27 PM
 */

#include "SystemControlMod.h"

SystemControlMod::SystemControlMod() {
    // Force prescaler to 0
    CLKPR = 0x80;
    CLKPR = 0;
    
    // Power Reduction Register 0
    PRR0 = 0
            | (1 << PRTWI)
            | (1 << PRTIM2)
            | (1 << PRTIM0)
            | (1 << PRTIM1)
            | (1 << PRSPI)
            | (1 << PRADC)
            ;
    
    PRR1 = 0
            | (1 << PRUSB)
            | (1 << PRTIM3)
            | (1 << PRUSART1)
            ;
    
    // External memory control
    XMCRA = 0;
    XMCRB = 0;
    
    SMCR = (0 << 1) | SE;
}

//SystemControlMod::SystemControlMod(const SystemControlMod& orig) {
//}

//SystemControlMod::~SystemControlMod() {
//}

