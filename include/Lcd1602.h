
/** LCD driver
 *
 */

#ifndef __LCD_1602_H__
#define __LCD_1602_H__

#include <stdint.h>

#include "arch.h"

#include "PowerMeter.h"

// Board-level definitions
#define LCD1602_CTRL_PORT PORTC
#define LCD1602_DATA_PORT PORTC
#define LCD1602_DATA_IN PINC
#define LCD1602_CTRL_DIR DDRC
#define LCD1602_DATA_DIR DDRC

#define LCD1602_RS_MASK 0x40
#define LCD1602_RW_MASK 0x20
#define LCD1602_E_MASK 0x10
#define LCD1602_CTRL_MASK (LCD1602_RS_MASK | LCD1602_RW_MASK | LCD1602_E_MASK)
#define LCD1602_DATA_MASK 0x0f

#define LCD_LINE1 0x00
#define LCD_LINE2 0x40

#define LCD_SET_E LCD1602_CTRL_PORT |= LCD1602_E_MASK
#define LCD_CLR_E LCD1602_CTRL_PORT &= ~LCD1602_E_MASK
#define LCD_SET_RS LCD1602_CTRL_PORT |= LCD1602_RS_MASK
#define LCD_CLR_RS LCD1602_CTRL_PORT &= ~LCD1602_RS_MASK
#define LCD_SET_RW LCD1602_CTRL_PORT |= LCD1602_RW_MASK
#define LCD_CLR_RW LCD1602_CTRL_PORT &= ~LCD1602_RW_MASK
#define LCD_DATA_IN LCD1602_DATA_DIR &= ~LCD1602_DATA_MASK
#define LCD_DATA_OUT LCD1602_DATA_DIR |= LCD1602_DATA_MASK

#define LCD1602_8BIT_PATTERN 0x3
#define LCD1602_4BIT_PATTERN 0x2

/** LCD driver class, for the typical 16x02 displays
 */
class Lcd1602Driver {
public:
    Lcd1602Driver()
    {
        LCD1602_CTRL_DIR = 0;
    }

    static uint8_t getData(void)
    {
        waitForBusy();
        return read(LCD1602_RS_MASK | LCD1602_RW_MASK);
    }

    static uint8_t getCtrl(void)
    {
        return read(LCD1602_RW_MASK);
    }

    static void sendCmd(uint8_t d)
    {
        write(d, 0);
    }

    static void sendChar(uint8_t d)
    {
        write(d, LCD1602_RS_MASK);
    }

    /* ************************************************************* */

    static void syncBusWidth(uint8_t width);

    /** This method sends a pattern to the LCD module using the command
     * interface. If widetrx is set, the lower 4 bits will be sent as
     * a second bus cycle.
     */

    static void lcdClearDisplay(void)
    {
        sendCmd(0x01);
    }

    static void lcdReturnHome(void)
    {
        sendCmd(0x02);
    }

    static void lcdEntryMode(uint8_t increment, uint8_t shift)
    {
        uint8_t cmd = 0x04 | (increment ? 0x2 : 0) | (shift ? 0x01 : 0);
        sendCmd(cmd);
    }

    static void lcdDisplayOn(uint8_t show, uint8_t cursor, uint8_t blink)
    {
        uint8_t cmd = 0x08 | (show ? 0x04 : 0) | (cursor ? 0x02 : 0) | (blink ? 0x01 : 0);
        sendCmd(cmd);
    }

    static void lcdDisplayShift(uint8_t display, uint8_t right)
    {
        uint8_t cmd = 0x10 | (display ? 0x08 : 0) | (right ? 0x04 : 0);
        sendCmd(cmd);
    }

    static void lcdFunctionSet(uint8_t width, uint8_t dual, uint8_t high)
    {
        uint8_t cmd = 0x20 | (width ? 0x10 : 0) | (dual ? 0x08 : 0) | (high ? 0x04 : 0);
        sendCmd(cmd);
    }

    static void lcdSetAddress(uint8_t cgram, uint8_t addr)
    {
        uint8_t cmd = (cgram ? 0x40 : 0x80) | addr;
        sendCmd(cmd);
    }

    static void init(void);

    static void sendStr(const char* s, uint8_t len);

    static void sendStr(const char* s);

    static void sendConstStr(const char* s, uint8_t len);

    static void sendConstStr(const char* s);

private:
    static uint8_t sampleBus(void);

    static uint8_t read(uint8_t mask);

    static void setBus(uint8_t d);

    static void write(uint8_t d, uint8_t mask);

    static uint16_t waitForBusy(void);
};

extern Lcd1602Driver lcd;

#endif // __LCD_1602_H__
