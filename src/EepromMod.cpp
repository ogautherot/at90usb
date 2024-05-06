/* 
 * File:   EepromMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:19 PM
 */

#include "EepromMod.h"


#define EEPROM_CMD(mode)    \
    { EECR = mode | (1 << EEMPE);   \
    EECR = mode | (1 << EEPE);  }


static uint16_t EepromStepCount = 0;
static uint8_t  EepromStepCmd = 0;
static uint8_t  *EepromSrcBuf = NULL;


uint8_t EepromMod::GetByte(uint16_t addr)
{
    EEAR = addr;
    EECR = 1 << EERE;
    return EEDR;
}


int8_t EepromMod::Get(uint8_t *dest, uint16_t addr, uint16_t size)
{
    if (size == 0)   {
        return 0;
    }

    EEAR = addr;

    while (size > 0)    {
        EECR = 1 << EERE;
        *dest = EEDR;
        size--;
        dest++;
        EEAR++;
    }
    return 0;
}


int8_t  EepromMod::ProcessBlock(uint16_t addr, uint8_t mode, int16_t size)
{
    int8_t ret = -1;

    if (!IsBusy())    {
        if (size > 0) {
            EEAR = addr;
            EEPROM_CMD(mode);
        }
        ret = 0;
    }
    return ret;
}


int8_t EepromMod::Step(void)
{
    if (EepromStepCmd == 0)     {
        return 0;
    }

    if (EepromStepCount == 0)   {
        EepromStepCmd = 0;
        return 0;
    }
    EepromStepCount--;
    EEAR++;     // EepromIncrementAddress();

    if ((EepromStepCmd == EEP_MODE_WRITE) || (EepromStepCmd == EEP_MODE_ERASE_WRITE)) {
        EEDR = *EepromSrcBuf;
        EepromSrcBuf++;
    }

    EEPROM_CMD(EepromStepCmd);
    return 0;
}


