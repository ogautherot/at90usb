/* 
 * File:   EepromMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:19 PM
 */

#ifndef EEPROMMOD_H
#define	EEPROMMOD_H

#include <cstdint>

#include <avr/io.h>


class EepromMod {
public:
    EepromMod() { }
    //EepromMod(const EepromMod& orig);
    //virtual ~EepromMod();
    static uint8_t GetByte(uint16_t addr);
    
private:

};

#endif	/* EEPROMMOD_H */

