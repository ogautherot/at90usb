

#include "Lcd1602.h"

void Lcd1602Driver::SetData(uint8_t v)
{
    uint8_t mask = LCD1602_DATA_PORT & ~LCD1602_DATA_MASK;
    mask |= v & 0x0f;
        
    LCD1602_DATA_PORT = mask;
}

void Lcd1602Driver::SetDataDir(uint8_t _dir_in)
{
    if (_dir_in)
    {
        DDRA &= ~LCD1602_DATA_MASK;
    }
    else
    {
        DDRA |= LCD1602_DATA_MASK;
    }
}

void Lcd1602Driver::ClearE(void)
{
    LCD1602_CTRL_PORT &= ~LCD1602_E_MASK;
}

void Lcd1602Driver::SetE(void)
{
    LCD1602_CTRL_PORT |= LCD1602_E_MASK;
}

void Lcd1602Driver::SendChar(uint8_t c)
{
    WaitForBusy();

    SetLcdControlBus(1, 1, 0);
    SetE();
    SetData(c >> 4);
    ClearE();
    SetLcdControlBus(1, 1, 0);
    SetE();
    SetData(c & 0x0f);
    ClearE();
}

void Lcd1602Driver::SetAddress(uint8_t cgram, uint8_t addr)
{
    uint8_t cmd = (cgram ? 0x40 : 0x80) | addr;
    WaitForBusy();
    SendCmd(cmd, 1);
}

void Lcd1602Driver::FunctionSet(uint8_t width, uint8_t dual, uint8_t high)
{
    uint8_t cmd = 0x20 | (width ? 0x10 : 0) | (dual ? 0x08 : 0) | (high ? 0x04 : 0);
    WaitForBusy();
    SendCmd(cmd, 1);
}

void Lcd1602Driver::DisplayShift(uint8_t display, uint8_t right)
{
    uint8_t cmd = 0x10 | (display ? 0x08 : 0) | (right ? 0x04 : 0);
    WaitForBusy();
    SendCmd(cmd, 1);
}

void Lcd1602Driver::DisplayOn(uint8_t show, uint8_t cursor, uint8_t blink)
{
    uint8_t cmd = 0x08 | (show ? 0x04 : 0) | (cursor ? 0x02 : 0) | (blink ? 0x01 : 0);
    WaitForBusy();
    SendCmd(cmd, 1);
}

void Lcd1602Driver::EntryMode(uint8_t increment, uint8_t shift)
{
    uint8_t cmd = 0x04 | (increment ? 0x2 : 0) | (shift ? 0x01 : 0);
    WaitForBusy();
    SendCmd(cmd, 1);
}

void Lcd1602Driver::ReturnHome(void)
    {
        WaitForBusy();
        SendCmd(0x02, 1);
    }

void Lcd1602Driver::ClearDisplay(void)
    {
        WaitForBusy();
        SendCmd(0x01, 1);
    }

void Lcd1602Driver::SetBusWidth(uint8_t width)
{
    uint8_t cmd = (width > 4) ? 0x03 : 0x02;
    SendCmd(cmd, 0);
}

void Lcd1602Driver::SendCmd(uint8_t pattern, uint8_t widetrx)
{
    SetLcdControlBus(0, 0, 0);
    SetE();
    SetData(pattern >> 4);
    ClearE();
    
    if (widetrx)
    {
        SetLcdControlBus(0, 0, 0);
        SetE();
        SetData(pattern & 0x0f);
        ClearE();
    }
}

void Lcd1602Driver::WaitForBusy(void)
{
    while (GetBusy())
    {
        // Do nothing
    }
}

uint8_t Lcd1602Driver::GetBusy(void)
{
    uint8_t ret;
    uint8_t dummy;
    
    SetDataDir(1);
    SetLcdControlBus(0, 1, 0);
    SetE();
    _NOP();
    _NOP();
    ret = LCD1602_DATA_GET_D7;
    ClearE();
    
    // Second cycle to close the transaction
    SetE();
    dummy = LCD1602_DATA_GET_D7;
    ClearE();
    SetDataDir(0);
    
    (void)dummy;
    return ret;
}

void Lcd1602Driver::SetLcdControlBus(uint8_t rs, uint8_t rw, uint8_t e)
{
    uint8_t mask = LCD1602_CTRL_PORT &
                    ~(LCD1602_RS_MASK | LCD1602_RW_MASK | LCD1602_E_MASK) &
                    LCD1602_CTRL_DIR;
    
    mask |= ((rs) ? LCD1602_RS_MASK : 0) |
                    ((rw) ? LCD1602_RW_MASK : 0) |
                    ((e) ? LCD1602_E_MASK : 0);
    mask &= (((rs) ? ~LCD1602_RS_MASK : 0xff) &
                    ((rw) ? ~LCD1602_RW_MASK : 0xff) &
                    ((e) ? ~LCD1602_E_MASK : 0xff));
    LCD1602_CTRL_PORT = mask;
}

