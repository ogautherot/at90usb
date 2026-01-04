/*
 * File:   Flash24AA512.h
 * Author: olivier
 *
 * Created on July 28, 2024, 9:05 PM
 */

#ifndef __FLASH24AA512_H__
#define __FLASH24AA512_H__

/** @brief 24AA512 Flash driver
 */

#include <stdint.h>
#include <string.h>

#include "arch.h"

#include "TwiMod.h"

// I2C address: addr[7:1] = 0x50

class Flash24aa512Mod {
public:
    Flash24aa512Mod();
    // virtual ~Flash24aa512Mod();

    int8_t writeByte(uint16_t addr, uint8_t v);
    int8_t writePage(uint16_t addr, uint8_t* buf, uint8_t len);
    int8_t loadBuf(uint8_t* buf, uint8_t offset, uint8_t length);
    uint8_t readByte(uint16_t addr);
    int8_t readPage(uint16_t addr, uint8_t len);

    int clearBuf();

private:
    uint8_t DeviceAddr;
    uint16_t MemPos;
};

extern Flash24aa512Mod Flash24aa512;

#endif /* __FLASH24AA512_H__ */
