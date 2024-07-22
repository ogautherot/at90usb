/** LCD driver
 *
 */

#ifndef __LCD_1602_H__
#define __LCD_1602_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/cpufunc.h>

// Board-level definitions
#define LCD1602_CTRL_PORT PORTA
#define LCD1602_CTRL_DIR DDRA
#define LCD1602_RS_MASK 0x04
#define LCD1602_RW_MASK 0x08
#define LCD1602_E_MASK 0x10

#define LCD1602_DATA_PORT PORTA
#define LCD1602_DATA_MASK 0xf0

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

#define LCD1602_CTRL_DIR_SET(m) \
    do                          \
    {                           \
        LCD1602_CTRL |= (m);    \
    } while (0)

#define LCD1602_DATA_DIR_SET(_dir_in)   \
    do                                  \
    {                                   \
        if (_dir_in)                    \
        {                               \
            DDRA &= ~LCD1602_DATA_MASK; \
        }                               \
        else                            \
        {                               \
            DDRA |= LCD1602_DATA_MASK;  \
        }                               \
    } while (0)

#define LCD1602_DATA_SET(x)                         \
    do                                              \
    {                                               \
        PORTA = (PORTA & ~LCD1602_DATA_MASK) | (x); \
    } while (0)

#define LCD1602_DATA_GET_D7 (PORTA & 0x80)

/** LCD driver class, for the typical 16x02 displays
 */
class Lcd1602Driver
{
public:
    Lcd1602Driver() {}
    virtual ~Lcd1602Driver() {}

    void SetLcdControlBus(uint8_t rs, uint8_t rw)
    {
        uint8_t mask = LCD1602_CTRL_PORT & ~(LCD1602_RS_MASK | LCD1602_RW_MASK) &
                       LCD1602_CTRL_DIR;

        mask |= ((rs) ? LCD1602_RS_MASK : 0) |
                ((rw) ? LCD1602_RW_MASK : 0);
        mask &= ~(((rs) ? 0 : LCD1602_RS_MASK) &
                  ((rw) ? 0 : LCD1602_RW_MASK));
        LCD1602_CTRL_PORT = mask;
    }

    uint8_t GetBusy(void)
    {
        uint8_t ret;
        uint8_t dummy;

        SetLcdControlBus(0, 1);
        LCD1602_E_SET;
        _NOP();
        _NOP();
        ret = LCD1602_DATA_GET_D7;
        LCD1602_E_CLR;

        // Second cycle to close the transaction
        LCD1602_E_SET;
        dummy = LCD1602_DATA_GET_D7;
        LCD1602_E_CLR;

        (void)dummy;
        return ret;
    }

    void WaitForBusy(void)
    {
        while (GetBusy())
        {
            // Do nothing
        }
    }

    /** This method sends a pattern to the LCD module using the command
     * interface. If widetrx is set, the lower 4 bits will be sent as
     * a second bus cycle.
     */
    void SendCmd(uint8_t pattern, uint8_t widetrx)
    {
        SetLcdControlBus(0, 0);
        LCD1602_E_SET;
        LCD1602_DATA_SET(pattern & 0xf0);
        LCD1602_E_CLR;

        if (widetrx)
        {
            LCD1602_E_SET;
            LCD1602_DATA_SET(pattern << 4);
            LCD1602_E_CLR;
        }
    }

    void ClearDisplay()
    {
        SendCmd(0x01, 1);
    }

    void Init(void)
    {
        // Set up the physical bus
        SetLcdControlBus(0, 0);
        LCD1602_E_CLR;
        LCD1602_CTRL_DIR_SET(LCD1602_RS_MASK | LCD1602_RW_MASK | LCD1602_E_MASK);
        LCD1602_DATA_DIR_SET(0);

        // Configure the bus interface of the LCD module
        SetBusWidth(8);
        SetBusWidth(8);
        SetBusWidth(4);
    }
};

#endif // __LCD_1602_H__
