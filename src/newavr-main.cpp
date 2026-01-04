/*
 * File:   newavr-main.c
 * Author: olivier
 *
 * Created on May 1, 2024, 8:15 PM
 */

#include <string.h>
#include <stdlib.h>

#include "PowerMeter.h"

#include "lib.h"
#include "EventQueue.h"
#include "Lcd1602.h"
#include "Rtc.h"
#include "ClockMod.h"
#include "AdcMod.h"
#include "GpioMod.h"
#include "EepromMod.h"
#include "FlashMod.h"
#include "PowerMgmtMod.h"
#include "SystemControlMod.h"
#include "TwiMod.h"
#include "SpiMod.h"
#include "UsartMod.h"
// #include "UsbDeviceMod.h"
#include "KeysMod.h"
#include "Flash24aa512.h"

/* ************************ END OF DEFINITIONS ************************* */

/* Fuse defaults:
 *  - Low: 0x5e
 *  - High: 0x9b
 *  - Extended: 0xf3 (BODLEVEL 2V6, HWBE)
 */

/* ******** Global Variables - constructors ordering ******** */

/*
PowerMgmtMod PwrMgmt;
SystemControlMod SystemControl;
TwiMod Twi;
SpiMod Spi;
UsartMod Usart;
UsbDeviceMod UsbDevice;

ClockMod Clock;
EepromMod Eeprom;
FlashMod Flash;
// OcmMod Ocm;

Flash24aa512Mod Flash24aa512;
*/

AdcMod adc0;
Rtc rtc;
TimerMod timers;
GpioMod gpio;
KeysMod Keys;
EepromMod eeprom;

EventQueue Queue;

uint16_t errno = 0;

/* ******** End of Global Variables - end of constructors ordering ******** */

FUSES = {
    .low =
        // FUSE_CKSEL2 & FUSE_CKSEL3 & // CKSEL[3:1] = 110 for 8MHz crystal (FUSE_CKSELn)
    FUSE_CKSEL1 & // FUSE_CKSEL0 &
        FUSE_SUT1 & FUSE_SUT0 & // SUT = 10 for 14 cycles after reset (fastest)
        FUSE_CKOUT & // Allow CKOUT (FUSE_CKOUT)
        0xff, // FUSE_CKDIV8, // FUSE_CKDIV8 unprogrammed
    .high =
        // FUSE_BOOTRST &              // FUSE_BOOTRST: Move boot to upper flash
    FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & // 11: 512 words, 10: 1K, 01: 2K, 00: 4K
                                  // // FUSE_BOOTSZn: boot loader section size (128 words/page)
        FUSE_EESAVE & // Preserve EEPROM upon flash erase
        FUSE_WDTON & // enable interrupts
        FUSE_SPIEN & FUSE_JTAGEN, // & FUSE_OCDEN, // Enable JTAG and SPI
    .extended = FUSE_BODLEVEL2 & // FUSE_BODLEVELn: 011 for 2.6V
        FUSE_HWBE // FUSE_HWBE: Hardware Boot Enable
};
// ==========================================================================

/** SysInit: Hardware initialization
 */
const char LcdTitle[] PROGMEM = ">Battery Tester<";
const char LcdNoLoad[] PROGMEM = "  Load missing  ";
// const char LcdTitle[]  PROGMEM =  "V=12.3V I=0.85A ";
// const char LcdNoLoad[] PROGMEM =  "P=10.4W C=12.3Ah";
//                                 "V=12.3V  I=0.85A";
//                                 "P=10.4W C=12.3Ah";
// const char LcdTitle[] PROGMEM = "Discharge 90h30m";
const char TextRunning[] PROGMEM = "Running ";

void SysInit(void)
{
    // while (!clock.CheckPllLock());

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    PRR0 = 0; // Set bits matching unused peripherals
    PRR1 = (1 << PRUSART1);

    lcd.init();
    lcd.sendConstStr(LcdTitle);
    lcd.lcdSetAddress(0, LCD_LINE2);
    lcd.sendConstStr(LcdNoLoad);

    sei();
}

void SystemError(void)
{
    // Set ports to inputs, except LEDs
    while (1) {
        uint8_t i;

        PORTA = (1 == (PORTA & 0x03)) ? 2 : 1;
        for (i = 0; i < 4; i++) {
            sleep_us(0xffff);
        }
    }
}

void DisplayTime()
{
    lcd.lcdSetAddress(0, LCD_LINE2);
    if (errno != 0) {
        // If errno != 0, display error code with RTC time
        char buf[10] = "Err 00  ";
        buf[4] = xdigit((errno >> 4) & 0x0f);
        buf[5] = xdigit(errno & 0x0f);
        lcd.sendStr(buf);
    } else {
        // If no error, display running time
        lcd.sendConstStr(TextRunning, sizeof(TextRunning) - 1);
    }
    lcd.lcdSetAddress(0, LCD_LINE2 + 8);
    lcd.sendStr(rtc.strTime(), 8);
}

/** main
 * @return Returns 0, if at all...
 */
int main(void)
{
    MCUSR = 0;

    // WDTCSR |= (1 << WDCE) | (1 << WDE) | (1 << WDP2) | (1 << WDP1);
    /* Turn off WDT */
    // WDTCSR &= ~(1 << WDE);
    SysInit();

    // gpio.SetLedCharging();
    // gpio.SetLedSink();

    //    adc0.StartConversion();
    //    rtc.StartRtc();
    //    timers.StartSystickTimer();

    rtc.startRtc();

    while (1) {
        EventStruct ev;

        // wdt_reset();
        while (!Queue.isEmpty()) {
            Queue.pop(&ev);
            switch (ev.s.EvType) {
            case 0:
                powerMeter.setLedSink(1);
                powerMeter.setLedCharging(1);
                break;

            case SYSTICK_ELAPSED:
                // 2ms systick
                break;

            case RTC_ELAPSED:
                // 1s event
                // errno = (errno + 1) & 0x1f;
                DisplayTime();
                break;

            case ADC_ELAPSED:
                break;
            }
        }
        sleep_cpu();
    }
    return 0;
}
