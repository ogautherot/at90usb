/** LCD driver
 *
 */

#ifndef __LCD_1602_H__
#define __LCD_1602_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/cpufunc.h>

// Board-level definitions
#define LCD1602_CTRL_PORT PORTC
#define LCD1602_CTRL_DIR DDRC
#define LCD1602_RS_MASK 0x40
#define LCD1602_RW_MASK 0x20
#define LCD1602_E_MASK 0x10

#define LCD1602_DATA_PORT PORTC
#define LCD1602_DATA_MASK 0x0f

// Bus handling
/*
#define LCD1602_RS_SET                      \
    do                                      \
    {                                       \
        LCD1602_RS_PORT |= LCD1602_RS_MASK; \
    } while (0)

#define LCD1602_RS_CLR                       \
    do                                       \
    {                                        \
        LCD1602_RS_PORT &= ~LCD1602_RS_MASK; \
    } while (0)

#define LCD1602_RW_SET                      \
    do                                      \
    {                                       \
        LCD1602_RW_PORT |= LCD1602_RW_MASK; \
    } while (0)

#define LCD1602_RW_CLR                       \
    do                                       \
    {                                        \
        LCD1602_RW_PORT &= ~LCD1602_RW_MASK; \
    } while (0)
*/

/*
#define LCD1602_E_SET                        \
    do                                       \
    {                                        \
        LCD1602_CTRL_PORT |= LCD1602_E_MASK; \
    } while (0)

#define LCD1602_E_CLR                         \
    do                                        \
    {                                         \
        LCD1602_CTRL_PORT &= ~LCD1602_E_MASK; \
    } while (0)
*/


/*
#define LCD1602_DATA_SET(x)                         \
    do                                              \
    {                                               \
        PORTA = (PORTA & ~LCD1602_DATA_MASK) | (x); \
    } while (0)
*/

#define LCD1602_DATA_GET_D7 (PORTA & 0x80)

/** LCD driver class, for the typical 16x02 displays
 */
class Lcd1602Driver
{
public:
    Lcd1602Driver() {}
    //virtual ~Lcd1602Driver() {}

    void SetLcdControlBus(uint8_t rs, uint8_t rw, uint8_t e);

    uint8_t GetBusy(void);

    void WaitForBusy(void);

    /** This method sends a pattern to the LCD module using the command
     * interface. If widetrx is set, the lower 4 bits will be sent as
     * a second bus cycle.
     */
    void SendCmd(uint8_t pattern, uint8_t widetrx);

    void SetBusWidth(uint8_t width);
    
    void ClearDisplay(void);

    void ReturnHome(void);

    void EntryMode(uint8_t increment, uint8_t shift);

    void DisplayOn(uint8_t show, uint8_t cursor, uint8_t blink);

    void DisplayShift(uint8_t display, uint8_t right);

    void FunctionSet(uint8_t width, uint8_t dual, uint8_t high);

    void SetAddress(uint8_t cgram, uint8_t addr);

    void SendChar(uint8_t c);
    
    void Init(void)
    {
        // Set up the physical bus
        LCD1602_CTRL_PORT = 0;
        LCD1602_CTRL_DIR = 0x7f;
        
        // Configure the bus interface of the LCD module
        SetBusWidth(8);
        SetBusWidth(8);
        WaitForBusy();
        SetBusWidth(4);
        
        FunctionSet(0, 1, 0);
        DisplayShift(0, 1);
        DisplayOn(1, 1, 1);
        
        SetAddress(0, 0);
        SendChar('H');
        SendChar('e');
        SendChar('l');
        SendChar('l');
        SendChar('o');
    }

private:
    void SetE(void);
    void ClearE(void);
    void SetDataDir(uint8_t _dir_in);
    void SetData(uint8_t v);

};

#endif // __LCD_1602_H__
