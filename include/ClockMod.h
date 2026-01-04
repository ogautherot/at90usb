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

#include "arch.h"

#include "PowerMeter.h"

class ClockMod {
public:
    ClockMod();

    /** Check the state of the PLL lock.
     */
    uint8_t checkPllLock(void)
    {
        return (PLLCSR & (1 << PLOCK));
    }

private:
};

/// @brief
extern ClockMod clockMod;

#endif /* CLOCKMOD_H */
