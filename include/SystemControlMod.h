/*
 * File:   SystemControlMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:27 PM
 */

#ifndef SYSTEMCONTROLMOD_H
#define SYSTEMCONTROLMOD_H

#include "arch.h"

#include "PowerMeter.h"

class SystemControlMod {
public:
    SystemControlMod();
    // SystemControlMod(const SystemControlMod& orig);
    // virtual ~SystemControlMod();

    void setDebugRegister(uint8_t d)
    {
        while (OCDR & 0x80)
            ;
        OCDR = d;
    }

    uint8_t getResetSource()
    {
        return MCUSR;
    }

private:
};

#endif /* SYSTEMCONTROLMOD_H */
