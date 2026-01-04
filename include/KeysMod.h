/*
 * File:   KeysMod.h
 * Author: olivier
 *
 * Created on July 28, 2024, 11:39 PM
 */

#ifndef KEYSMOD_H
#define KEYSMOD_H

#include <stdint.h>

#include "arch.h"

#include "PowerMeter.h"

class KeysMod {
public:
    KeysMod();
    // KeysMod(const KeysMod& orig);
    // virtual ~KeysMod();

    uint8_t probe();

    uint8_t getLastState(void)
    {
        return LastState;
    }

private:
    uint8_t LastState;
};

extern KeysMod Keys;

#endif /* KEYSMOD_H */
