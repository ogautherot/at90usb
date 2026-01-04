/*
 * File:   KeysMod.cpp
 * Author: olivier
 *
 * Created on July 28, 2024, 11:39 PM
 */

#include "KeysMod.h"

KeysMod::KeysMod()
{
}

// KeysMod::KeysMod(const KeysMod& orig) {
// }

// KeysMod::~KeysMod() {
// }

uint8_t KeysMod::probe()
{
    uint8_t ret = (~PORTD & ~LastState) & 0xf0;

    LastState = ret;
    return ret;
}
