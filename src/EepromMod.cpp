/* 
 * File:   EepromMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:19 PM
 */

#include "EepromMod.h"


// EepromMod::EepromMod(const EepromMod& orig) { }

// EepromMod::~EepromMod() { }

uint8_t EepromMod::GetByte(uint16_t addr)
{
    EEAR = addr;
    EECR = 1 << EERE;
    return EEDR;
}

int8_t EepromMod::Get(uint8_t *dest, uint16_t addr, uint16_t len)
{
    if (len == 0)   {
        return 0;
    }
    
    EEAR = addr;
    do {
        uint8_t tmp;

        EECR = 1 << EERE;
        *dest = EEDR;
        dest++;
        tmp = EEARL + 1;
        EEARL = tmp;
        EEARH = EEARH + 1;
    } while (len > 0);
}

