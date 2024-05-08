/* 
 * File:   WatchdogMod.cpp
 * Author: olivier
 * 
 * Created on May 7, 2024, 10:55 PM
 */

#include "WatchdogMod.h"

WatchdogMod::WatchdogMod() {
    WDTCSR =
            (1 << 5) | (0 << 0)     // 4s timeout (bits 5, 2, 1, 0)
            //| (1 << 4)              // Watchdog System Reset Enable
            | (1 << 6)              // Watchdog Interrupt Enable
            | (1 << 7)              // Watchdog Interrupt Flag
            ;
}

//WatchdogMod::WatchdogMod(const WatchdogMod& orig) {
//}

//WatchdogMod::~WatchdogMod() {
//}

ISR(WDT_vect)
{
    
}
