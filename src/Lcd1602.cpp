/**
 */

#include "lib.h"
#include "Lcd1602.h"
#include "GpioMod.h"
#include "TimerMod.h"

#define CMD_8_BITS 1
#define CMD_4_BITS 0
#define CMD_DELAY 500

Lcd1602Driver lcd;

/* ************************************************************************ */

uint8_t Lcd1602Driver::sampleBus(void)
{
    uint8_t ret;

    LCD_DATA_IN;

    LCD_SET_E;
    _NOP();
    ret = LCD1602_DATA_IN;
    LCD_CLR_E;

    LCD_DATA_OUT;

    return ret & LCD1602_DATA_MASK;
}

uint8_t Lcd1602Driver::read(uint8_t mask)
{
    uint8_t ret;

#ifdef __AVR__
    uint8_t sreg = SREG;
    cli();
#endif

    LCD1602_CTRL_PORT = (LCD1602_CTRL_PORT & ~LCD1602_CTRL_MASK) | mask;
    ret = sampleBus() << 4;
    ret |= sampleBus();
    LCD1602_CTRL_PORT = (LCD1602_CTRL_PORT & ~LCD1602_CTRL_MASK);

#ifdef __AVR__
    SREG = sreg;
#endif

    return ret;
}

void Lcd1602Driver::setBus(uint8_t d)
{
    LCD1602_DATA_PORT = (LCD1602_DATA_PORT & 0xf0) | (d & 0x0f);
    LCD_SET_E; // SetE(1);
    _NOP();
    LCD_CLR_E; // SetE(0);
}

void Lcd1602Driver::write(uint8_t d, uint8_t mask)
{
#ifdef __AVR__
    uint8_t sreg = SREG;
    cli();
#endif

    waitForBusy();

    LCD1602_CTRL_PORT = (LCD1602_CTRL_PORT & ~LCD1602_CTRL_MASK) | mask;
    setBus(d >> 4);
    setBus(d);
    LCD1602_CTRL_PORT = (LCD1602_CTRL_PORT & ~LCD1602_CTRL_MASK);

#ifdef __AVR__
    SREG = sreg;
#endif
}

uint16_t Lcd1602Driver::waitForBusy(void)
{
    uint8_t count = 0;

    while (getCtrl() & 0x80) {
        count++;
    }

    return count;
}

/* ************************************************************************ */

uint32_t bad_char = 0;

void Lcd1602Driver::syncBusWidth(uint8_t pattern)
{
    LCD_CLR_RS;
    setBus(pattern);
}

void Lcd1602Driver::sendStr(const char* s, uint8_t len)
{
    while (len) {
        const uint8_t c = *s;
        sendChar(c);
        --len;
        ++s;
    }
}

void Lcd1602Driver::sendStr(const char* s)
{
    while (1) {
        char c = *s;

        if (0 == c) {
            break;
        }
        sendChar(c);
        ++s;
    }
}

void Lcd1602Driver::sendConstStr(const char* s, uint8_t len)
{
    while (len) {
        uint8_t c = pgm_read_byte(s);
        sendChar(c);
        --len;
        ++s;
    }
}

void Lcd1602Driver::sendConstStr(const char* s)
{
    while (1) {
        char c = pgm_read_byte(s);
        if (0 == c) {
            break;
        }
        sendChar(c);
        ++s;
    }
}

void Lcd1602Driver::init(void)
{
    uint8_t i;

    // Set up the physical bus
    LCD1602_CTRL_PORT = 0;
    LCD1602_CTRL_DIR = 0xff;
    // LCD_DATA_OUT;

    for (i = 0; i < 10; i++)
        sleep_us(50000);

    // Configure the bus interface of the LCD module
    for (int i = 0; i < 3; i++) {
        syncBusWidth(LCD1602_8BIT_PATTERN);
        sleep_us(5000);
    }
    syncBusWidth(LCD1602_4BIT_PATTERN);
    sleep_us(100);
    lcdFunctionSet(0, 1, 1);
    lcdClearDisplay();
    lcdDisplayShift(0, 1);
    lcdDisplayOn(1, 1, 1);
    lcdReturnHome();
    // lcdEntryMode(1, 0);
}
