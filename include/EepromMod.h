/*
 * File:   EepromMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:19 PM
 */

#ifndef EEPROMMOD_H
#define EEPROMMOD_H

/** @brief EEPROM driver.
 */

#include <stdint.h>
#include <string.h>

#include "arch.h"

#include "PowerMeter.h"

#define EEP_MODE_ERASE (1 << EEPM0)
#define EEP_MODE_WRITE (2 << EEPM0)
#define EEP_MODE_ERASE_WRITE (0 << EEPM0)

#define EEPROM_IS_BUSY ((EECR & (1 << EEPE)) | (SPMCSR & SPMEN))

class EepromMod {
public:
    EepromMod();

    // EepromMod(const EepromMod& orig);
    // virtual ~EepromMod();

    uint8_t getByte(uint16_t addr);
    int8_t get(uint8_t* dest, uint16_t addr, uint16_t len);
    void putByte(uint16_t addr, uint8_t val);
    void put(uint8_t* src, uint16_t addr, uint16_t size);

    static int8_t processBlock(uint16_t addr, uint8_t mode, int16_t size);
    static int8_t step(void);

    int8_t eraseByte(uint16_t addr)
    {
        return processBlock(addr, EEP_MODE_ERASE, 1);
    }

    int8_t eraseBlock(uint16_t addr, uint16_t size)
    {
        return processBlock(addr, EEP_MODE_ERASE, size);
    }

private:
    /**
     * @brief Wait for the EEPROM to be ready for the next operation.
     */
    void waitEepromReady(void)
    {
        while (EECR & (1 << EEPE)) {
        }
    }
};

extern EepromMod eeprom;

#endif /* EEPROMMOD_H */
