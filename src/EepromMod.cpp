/*
 * File:   EepromMod.cpp
 * Author: olivier
 *
 * Created on May 1, 2024, 10:19 PM
 */

#include "EepromMod.h"

#define EEPROM_CMD(mode)            \
    {                               \
        EECR = mode | (1 << EEMPE); \
        EECR = mode | (1 << EEPE);  \
    }

static uint16_t EepromStepCount = 0;
static uint8_t EepromStepCmd = 0;
static uint8_t* EepromSrcBuf = NULL;

EepromMod::EepromMod()
{
    waitEepromReady();
    EECR = 0;
    // Ignore EEDR, EEARL and EEARH
}

uint8_t EepromMod::getByte(uint16_t addr)
{
    EEAR = addr;
    EECR = 1 << EERE;
    return EEDR;
}

int8_t EepromMod::get(uint8_t* dest, uint16_t addr, uint16_t size)
{
    waitEepromReady();
    while (size > 0) {
        EEAR = addr;
        EECR = 1 << EERE;
        *dest = EEDR;
        size--;
        dest++;
        addr++;
    }
    return 0;
}

void EepromMod::putByte(uint16_t addr, uint8_t val)
{
    waitEepromReady();
    EEAR = addr;
    EEDR = val;
    EEPROM_CMD(EEP_MODE_WRITE);
}

void EepromMod::put(uint8_t* src, uint16_t addr, uint16_t size)
{
    while (size > 0) {
        waitEepromReady();
        EEAR = addr;
        EEDR = *src;
        src++;
        EEPROM_CMD(EEP_MODE_WRITE);
        addr++; // EepromIncrementAddress();
        size--;
    }
}

int8_t EepromMod::processBlock(uint16_t addr, uint8_t mode, int16_t size)
{
    int8_t ret = -1;

    if (!EEPROM_IS_BUSY) {
        if (size > 0) {
            cli();
            EEAR = addr;
            EEPROM_CMD(mode);
            sei();
        }
        ret = 0;
    }
    return ret;
}

int8_t EepromMod::step(void)
{
    if (EepromStepCmd == 0) {
        return 0;
    }

    if (EepromStepCount == 0) {
        EepromStepCmd = 0;
        return 0;
    }
    EepromStepCount--;
    EEAR++; // EepromIncrementAddress();

    if ((EepromStepCmd == EEP_MODE_WRITE) || (EepromStepCmd == EEP_MODE_ERASE_WRITE)) {
        EEDR = *EepromSrcBuf;
        EepromSrcBuf++;
    }

    EEPROM_CMD(EepromStepCmd);
    return 0;
}

ISR(EE_READY_vect)
{
    while (1)
        ;

    // EEPROM interrupt flag cleared automatically
}
