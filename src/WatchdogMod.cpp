/*
 * File:   WatchdogMod.cpp
 * Author: olivier
 *
 * Created on May 7, 2024, 10:55 PM
 */

#include "WatchdogMod.h"

// WatchdogMod::WatchdogMod(const WatchdogMod& orig) {
// }

// WatchdogMod::~WatchdogMod() {
// }

ISR(WDT_vect) {
    while (1) {
    }
}
