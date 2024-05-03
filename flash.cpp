
#include <avr/io.h>

#include <stdint.h>
#include <string.h>

#define EEP_MODE_ERASE          (1 << EEPM0)
#define EEP_MODE_WRITE          (2 << EEPM0)
#define EEP_MODE_ERASE_WRITE    (0 << EEPM0)

using namespace std;

static uint16_t EepromStepCount = 0;
static uint8_t  EepromStepCmd = 0;
static uint8_t  *EepromSrcBuf = NULL;


static inline void EepromCmd(uint8_t mode)
{
    EECR = mode | (1 << EEMPE);
    EECR = mode | (1 << EEPE);
}

uint8_t EepromGetByte(uint16_t addr)
{
    EEAR = addr;
    EECR = 1;
    return EEDR;
}

int8_t EepromGetBlock(uint8_t *dest, uint16_t addr, uint16_t size)
{
    EEAR = addr;

    while (size > 0)    {
        EECR = 1 << EERE;
        *dest = EEDR;
        size--;
        dest++;
    }
    return 0;
}


static inline int8_t  EepromIsBusy(void)
{
    return (EECR & (1 << EEPE)) | (SPMCSR & SPMEN);
}


int8_t  EepromProcessBlock(uint16_t addr, uint8_t mode, int16_t size)
{
    int8_t ret = -1;

    if (!EepromIsBusy())    {
        if (size > 0) {
            EEAR = addr;
            EepromCmd(mode);
        }
        ret = 0;
    }
    return ret;
}

int8_t  EepromEraseByte(uint16_t addr)
{
    return EepromProcessBlock(addr, EEP_MODE_ERASE, 1);
}

int8_t  EepromEraseBlock(uint16_t addr, uint16_t size)
{
    return EepromProcessBlock(addr, EEP_MODE_ERASE, size);
}

int8_t EepromStep(void)
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

    EepromCmd(EepromStepCmd);
    return 0;
}




