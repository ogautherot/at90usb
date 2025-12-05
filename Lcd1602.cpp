/**
 */

#include "lib.h"
#include "Lcd1602.h"

#define CMD_8_BITS 1
#define CMD_4_BITS 0
#define CMD_DELAY 500

#define LCD_SET_E LCD1602_CTRL_PORT |= LCD1602_E_MASK
#define LCD_CLR_E LCD1602_CTRL_PORT &= ~LCD1602_E_MASK
#define LCD_SET_RS LCD1602_CTRL_PORT |= LCD1602_RS_MASK
#define LCD_CLR_RS LCD1602_CTRL_PORT &= ~LCD1602_RS_MASK
#define LCD_SET_RW LCD1602_CTRL_PORT |= LCD1602_RW_MASK
#define LCD_CLR_RW LCD1602_CTRL_PORT &= ~LCD1602_RW_MASK
#define LCD_DATA_IN LCD1602_DATA_DIR &= ~LCD1602_DATA_MASK
#define LCD_DATA_OUT LCD1602_DATA_DIR |= LCD1602_DATA_MASK

Lcd1602Driver lcd;

/* ************************************************************************ */
#pragma GCC push_options
#pragma GCC optimize("Os")

static uint8_t SampleBus(void)
{
    uint8_t ret;

    // SetDataDir(1);
    LCD1602_DATA_IN;
    LCD_SET_E; // SetE(1);
    _NOP();
    ret = LCD1602_DATA_IN;
    LCD_CLR_E; // SetE(0);
    // SetDataDir(0);
    LCD_DATA_OUT;

    return ret;
}

uint8_t GetData(void) // (uint8_t isData)
{
    uint8_t ret;

    // Read data RAM
    // SetLcdControlBus(1, 1);
    LCD_SET_RS;
    LCD_SET_RW;

    ret = SampleBus() << 4;
    // sleep_us(10);
    ret |= SampleBus() & 0x0f;
    // SetLcdControlBus(0, 0);
    LCD_CLR_RS;
    LCD_CLR_RW;

    return ret;
}

uint8_t GetCtrl(void)
{
    uint8_t ret;

    // Read control bus
    // SetLcdControlBus(0, 1);
    LCD_CLR_RS;
    LCD_SET_RW;

    ret = SampleBus() << 4;
    // sleep_us(10);
    ret |= SampleBus() & 0x0f;
    // SetLcdControlBus(0, 0);
    LCD_CLR_RS;
    LCD_CLR_RW;

    return ret;
}

static void PokeBus(uint8_t d)
{
    LCD1602_DATA_PORT = (LCD1602_DATA_PORT & 0xf0) | (d & 0x0f);
    LCD_SET_E; // SetE(1);
    _NOP();
    // sleep_us(1);
    LCD_CLR_E; // SetE(0);
}

#pragma GCC pop_options

/* ************************************************************************ */

uint16_t WaitForBusy(void)
{
    uint8_t count = 0;

    while (GetCtrl() & 0x80)
    {
        count++;
    }
    // sleep_us(10);
    return count;
}

#if 0
void SendTrx(uint8_t pattern, uint8_t doubletrx)
{
    PokeBus(pattern >> 4);

    if (doubletrx)
    {
        PokeBus(pattern & 0x0f);
    }
}
#endif

void Lcd1602Driver::SendChar(uint8_t c)
{
    WaitForBusy();
    LCD_SET_RS;
    LCD_CLR_RW;
    // SendTrx(c, 1);
    PokeBus(c >> 4);
    PokeBus(c & 0xf);
}

void Lcd1602Driver::SendSingleCmd(uint8_t pattern)
{
    WaitForBusy();
    LCD_CLR_RS;
    LCD_CLR_RW;
    // SendTrx(pattern, 0);
    PokeBus(pattern >> 4);
    PokeBus(pattern & 0xf);
}

void Lcd1602Driver::SendCmd(uint8_t pattern)
{
    WaitForBusy();
    LCD_CLR_RS;
    LCD_CLR_RW;
    // SendTrx(pattern, 1);
    PokeBus(pattern >> 4);
}

void Lcd1602Driver::SetBusWidth(uint8_t width)
{
    uint8_t cmd = (width > 4) ? 0x30 : 0x20;
    SendSingleCmd(cmd);
}

void Lcd1602Driver::SendStr(const char *s, uint8_t len)
{
    while (len)
    {
        SendChar(*s);
        --len;
        ++s;
    }
}

void Lcd1602Driver::SendStr(const char *s)
{
    while (1)
    {
        char c = *s;

        if (0 == c)
        {
            break;
        }
        SendChar(c);
        ++s;
    }
}

void Lcd1602Driver::SendConstStr(const char *s, uint8_t len)
{
    while (len)
    {
        SendChar(pgm_read_byte(s));
        --len;
        ++s;
    }
}

void Lcd1602Driver::SendConstStr(const char *s)
{
    while (1)
    {
        char c = pgm_read_byte(s);
        if (0 == c)
        {
            break;
        }
        SendChar(c);
        ++s;
    }
}

void Lcd1602Driver::Init(void)
{
    uint8_t i;

    // Set up the physical bus
    LCD1602_CTRL_PORT = 0;
    LCD1602_CTRL_DIR = 0x7f;

    for (i = 0; i < 10; i++)
        sleep_us(10000);
    // SetDataDir(0);
    LCD_DATA_OUT;

    // Configure the bus interface of the LCD module
    SetBusWidth(8);
    SetBusWidth(8);
    SetBusWidth(8);
    SetBusWidth(4);
    FunctionSet(0, 1, 1);
    // sleep_us(100);

    DisplayOn(0, 1, 1);
    // sleep_us(1000);
    DisplayOn(1, 1, 1);
    ClearDisplay();
    ReturnHome();
    EntryMode(1, 0);
}
