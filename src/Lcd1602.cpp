/**
 */

#include "lib.h"
#include "Lcd1602.h"

#define CMD_8_BITS  1
#define CMD_4_BITS  0
#define CMD_DELAY   500

#define LCD_TRX_DATA(p,w)   SendTrx(1, p, w)
#define LCD_TRX_CMD(p,w)    SendTrx(1, p, w)

static void SetE(uint8_t on) {
    if (on) {
        LCD1602_CTRL_PORT |= LCD1602_E_MASK;
    } else {
        LCD1602_CTRL_PORT &= ~LCD1602_E_MASK;
    }
}

static void SetDataDir(uint8_t _dir_in) {
    if (_dir_in) {
        LCD1602_DATA_DIR &= ~LCD1602_DATA_MASK;
    } else {
        LCD1602_DATA_DIR |= LCD1602_DATA_MASK;
    }
}

static void SetLcdControlBus(uint8_t rs, uint8_t rw) {
    if (rs) {
        LCD1602_CTRL_PORT |= LCD1602_RS_MASK;
    } else {
        LCD1602_CTRL_PORT &= ~LCD1602_RS_MASK;
    }

    if (rw) {
        LCD1602_CTRL_PORT |= LCD1602_RW_MASK;
    } else {
        LCD1602_CTRL_PORT &= ~LCD1602_RW_MASK;
    }
}

/* ************************************************************************ */
#pragma GCC push_options
#pragma GCC optimize ("Os")

static uint8_t SampleBus(void) {
    uint8_t ret;

    SetDataDir(1);
    SetE(1);
    _NOP();
    ret = LCD1602_DATA_IN;
    SetE(0);
    SetDataDir(0);

    return ret;
}

uint8_t GetData(uint8_t isData) {
    uint8_t ret;

    if (isData) {
        // Read data RAM
        SetLcdControlBus(1, 1);
    } else {
        // Read control bus
        SetLcdControlBus(0, 1);
    }

    ret = SampleBus() << 4;
    sleep_us(10);
    ret |= SampleBus() & 0x0f;
    SetLcdControlBus(0, 0);
    return ret;
}

static void PokeBus(uint8_t d) {
    LCD1602_DATA_PORT = (LCD1602_DATA_PORT & 0xf0) | (d & 0x0f);
    SetE(1);
    _NOP();
    //sleep_us(1);
    SetE(0);
}

#pragma GCC pop_options

/* ************************************************************************ */

uint16_t WaitForBusy(void) {
    uint8_t count = 0;

    while (GetData(0) & 0x80) {
        count++;
    }
    return count;
}

void SendTrx(uint8_t pattern, uint8_t doubletrx, uint8_t isData) {
    WaitForBusy();
    if (isData) {
        SetLcdControlBus(1, 0);
    } else {
        SetLcdControlBus(0, 0);
    }
    PokeBus(pattern >> 4);

    if (doubletrx) {
        PokeBus(pattern & 0x0f);
    }
}

void Lcd1602Driver::SendChar(uint8_t c) {
    SendTrx(c, 1, 1);
}

void Lcd1602Driver::SendSingleCmd(uint8_t pattern) {
    SendTrx(pattern, 0, 0);
}

void Lcd1602Driver::SendCmd(uint8_t pattern) {
    SendTrx(pattern, 1, 0);
}

void Lcd1602Driver::SetBusWidth(uint8_t width) {
    uint8_t cmd = (width > 4) ? 0x30 : 0x20;
    SendSingleCmd(cmd);
}

void Lcd1602Driver::SendStr(const char *s, uint8_t len) {
    while (len)   {
        SendChar(*s);
        --len;
        ++s;
    }
}

void Lcd1602Driver::SendStr(const char *s) {
    while (1)   {
        char c = *s;
        
        if (0 == c) {
            break;
        }
        SendChar(c);
        ++s;
    }
}

void Lcd1602Driver::SendConstStr(const PROGMEM char *s, uint8_t len) {
    while (len)   {
        SendChar(pgm_read_byte(s));
        --len;
        ++s;
    }
}

void Lcd1602Driver::SendConstStr(const PROGMEM char *s) {
    while (1) {
        char c = pgm_read_byte(s);
        if (0 == c) {
            break;
        }
        SendChar(c);
        ++s;
    }
}

void Lcd1602Driver::Init(void) {
    uint8_t i;

    // Set up the physical bus
    LCD1602_CTRL_PORT = 0;
    LCD1602_CTRL_DIR = 0x7f;

    for (i = 0; i < 10; i++)
        sleep_us(10000);
    SetDataDir(0);

    // Configure the bus interface of the LCD module
    SetBusWidth(8);
    SetBusWidth(8);
    SetBusWidth(8);
    SetBusWidth(4);
    FunctionSet(0, 1, 1);
    sleep_us(100);

    DisplayOn(1, 1, 1);
    ClearDisplay();
    ReturnHome();
    EntryMode(1, 0);
}
