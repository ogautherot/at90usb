/*
 * File:   WatchdogMod.h
 * Author: olivier
 *
 * Created on May 7, 2024, 10:55 PM
 */

#ifndef WATCHDOGMOD_H
#define WATCHDOGMOD_H

#include "arch.h"

#include "PowerMeter.h"

class WatchdogMod {
public:
    WatchdogMod()
    {
        WDTCSR = 0x47;
    }

    // WatchdogMod(const WatchdogMod &orig);
    virtual ~WatchdogMod();

    void watchdogEnable(void)
    {
        wdt_enable(WDP3); // Timeout: 4s
    }

    void watchdogReset(void)
    {
        wdt_reset();
    }

private:
};

#endif /* WATCHDOGMOD_H */
