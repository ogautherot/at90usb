/*
 * File:   ClockMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:25 PM
 */

#ifndef CLOCKMOD_H
#define CLOCKMOD_H

/** @brief Clock control module.
 *
 * The main role of this module is the USB PLL.
 */
#include <stdint.h>

#include "PowerMeter.h"

#include <avr/interrupt.h>
#include <avr/io.h>

class ClockMod {
public:
    ClockMod();

    /** Check the state of the PLL lock.
     */
    uint8_t CheckPllLock(void)
    {
        return (PLLCSR & (1 << PLOCK));
    }

private:
};

extern ClockMod clock;

#endif /* CLOCKMOD_H */
