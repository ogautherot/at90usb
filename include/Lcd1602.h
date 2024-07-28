
/** LCD driver
 *
 */

#ifndef __LCD_1602_H__
#define __LCD_1602_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/pgmspace.h> 

// Board-level definitions
#define LCD1602_CTRL_PORT PORTC
#define LCD1602_CTRL_DIR DDRC
#define LCD1602_RS_MASK 0x40
#define LCD1602_RW_MASK 0x20
#define LCD1602_E_MASK 0x10

#define LCD1602_DATA_PORT PORTC
#define LCD1602_DATA_IN   PINC
#define LCD1602_DATA_DIR  DDRC
#define LCD1602_DATA_MASK 0x0f
#define LCD1602_DATA_GET_D7 (PORTA & 0x80)

/** LCD driver class, for the typical 16x02 displays
 */
class Lcd1602Driver
{
public:

    Lcd1602Driver()
    {
    }

    /** This method sends a pattern to the LCD module using the command
     * interface. If widetrx is set, the lower 4 bits will be sent as
     * a second bus cycle.
     */

    void ClearDisplay(void)
    {
        SendCmd(0x01);
    }

    void ReturnHome(void)
    {
        SendCmd(0x02);
    }

    void EntryMode(uint8_t increment, uint8_t shift)
    {
        uint8_t cmd = 0x04 | (increment ? 0x2 : 0) | (shift ? 0x01 : 0);
        SendCmd(cmd);
    }

    void DisplayOn(uint8_t show, uint8_t cursor, uint8_t blink)
    {
        uint8_t cmd = 0x08 | (show ? 0x04 : 0) | (cursor ? 0x02 : 0) | (blink ? 0x01 : 0);
        SendCmd(cmd);
    }

    void DisplayShift(uint8_t display, uint8_t right)
    {
        uint8_t cmd = 0x10 | (display ? 0x08 : 0) | (right ? 0x04 : 0);
        SendCmd(cmd);
    }

    void FunctionSet(uint8_t width, uint8_t dual, uint8_t high)
    {
        uint8_t cmd = 0x20 | (width ? 0x10 : 0) | (dual ? 0x08 : 0) | (high ? 0x04 : 0);
        SendCmd(cmd);
    }

    void SetAddress(uint8_t cgram, uint8_t addr)
    {
        uint8_t cmd = (cgram ? 0x40 : 0x80) | addr;
        SendCmd(cmd);
    }

    static void SendChar(uint8_t c);

    static void SendSingleCmd(uint8_t pattern);

    static void SendCmd(uint8_t pattern);

    void Init(void);
    
    static void SendStr(const char *s, uint8_t len);

    static void SendStr(const char *s);

    static void SendConstStr(const char *s, uint8_t len);

    static void SendConstStr(const char *s);

private:
    static void SetBusWidth(uint8_t width);
};

#endif // __LCD_1602_H__
