/*
 * File:   WatchdogMod.h
 * Author: olivier
 *
 * Created on May 7, 2024, 10:55 PM
 */

#ifndef WATCHDOGMOD_H
#define WATCHDOGMOD_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

class WatchdogMod
{
public:
    WatchdogMod() {}
    // WatchdogMod(const WatchdogMod &orig);
    virtual ~WatchdogMod();

    void WatchdogEnable(void)
    {
        wdt_enable(WDP3); // Timeout: 4s
    }

    void WatchdogReset(void)
    {
        wdt_reset();
    }

private:
};

#endif /* WATCHDOGMOD_H */
