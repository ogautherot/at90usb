/*
 * File:   KeysMod.h
 * Author: olivier
 *
 * Created on July 28, 2024, 11:39 PM
 */

#ifndef KEYSMOD_H
#define KEYSMOD_H

#include "PowerMeter.h"

#include <avr/io.h>
#include <stdint.h>

class KeysMod {
public:
    KeysMod();
    // KeysMod(const KeysMod& orig);
    // virtual ~KeysMod();

    uint8_t ProbeKeys();

private:
    uint8_t LastState;
};

extern KeysMod Keys;

#endif /* KEYSMOD_H */
