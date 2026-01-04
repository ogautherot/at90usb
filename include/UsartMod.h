/*
 * File:   UsartMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:38 PM
 */

#ifndef USARTMOD_H
#define USARTMOD_H

#include "arch.h"

#include "PowerMeter.h"

class UsartMod {
public:
    UsartMod();
    // UsartMod(const UsartMod& orig);
    // virtual ~UsartMod();

    uint8_t getStatusA()
    {
        return UCSR1A;
    }

    uint8_t getStatusB()
    {
        return UCSR1B;
    }

    uint8_t getData()
    {
        return UDR1;
    }

    void setData(uint8_t d)
    {
        UDR1 = d;
    }

private:
};

#endif /* USARTMOD_H */
