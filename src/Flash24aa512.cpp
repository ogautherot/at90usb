/*
 * File:   Flash24AA512.cpp
 * Author: olivier
 *
 * Created on July 28, 2024, 10:36 PM
 */

#include "Flash24aa512.h"

Flash24aa512Mod::Flash24aa512Mod()
{
    DeviceAddr = 0xa0;
    MemPos = 0;
}

// Flash24aa512Mod::Flash24aa512Mod(const Flash24aa512Mod& orig) {
// }

// Flash24aa512Mod::~Flash24aa512Mod() {
// }

int8_t Flash24aa512Mod::WriteByte(uint16_t addr, uint8_t v)
{
    (void)addr;
    (void)v;
    return 0;
}

int8_t Flash24aa512Mod::WritePage(uint16_t addr, uint8_t *buf, uint8_t len)
{
    (void)addr;
    (void)buf;
    (void)len;
    return 0;
}

int8_t Flash24aa512Mod::LoadBuf(uint8_t *buf, uint8_t offset, uint8_t length)
{
    (void)buf;
    (void)offset;
    (void)length;
    return 0;
}

uint8_t Flash24aa512Mod::ReadByte(uint16_t addr)
{
    (void)addr;
    return 0;
}

int8_t Flash24aa512Mod::ReadPage(uint16_t addr, uint8_t len)
{
    (void)addr;
    (void)len;
    return 0;
}
