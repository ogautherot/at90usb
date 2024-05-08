/* 
 * File:   EepromMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:19 PM
 */

#ifndef EEPROMMOD_H
#define	EEPROMMOD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <string.h>

#define EEP_MODE_ERASE          (1 << EEPM0)
#define EEP_MODE_WRITE          (2 << EEPM0)
#define EEP_MODE_ERASE_WRITE    (0 << EEPM0)

#define EEPROM_IS_BUSY  ((EECR & (1 << EEPE)) | (SPMCSR & SPMEN))

class EepromMod {
public:

    EepromMod();
    
    //EepromMod(const EepromMod& orig);
    //virtual ~EepromMod();

    static uint8_t GetByte(uint16_t addr);
    static int8_t Get(uint8_t *dest, uint16_t addr, uint16_t len);

    static int8_t ProcessBlock(uint16_t addr, uint8_t mode, int16_t size);
    static int8_t Step(void);

    int8_t EraseByte(uint16_t addr) {
        return ProcessBlock(addr, EEP_MODE_ERASE, 1);
    }

    int8_t EraseBlock(uint16_t addr, uint16_t size) {
        return ProcessBlock(addr, EEP_MODE_ERASE, size);
    }


private:

};

#endif	/* EEPROMMOD_H */

