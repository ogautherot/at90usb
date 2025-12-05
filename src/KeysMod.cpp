/* 
 * File:   KeysMod.cpp
 * Author: olivier
 * 
 * Created on July 28, 2024, 11:39 PM
 */

#include "KeysMod.h"


KeysMod::KeysMod() {
}

//KeysMod::KeysMod(const KeysMod& orig) {
//}

//KeysMod::~KeysMod() {
//}

uint8_t KeysMod::ProbeKeys()
{
    uint8_t ret = ~PORTB & ~LastState;
    
    LastState = ret;
    return ret;
}


