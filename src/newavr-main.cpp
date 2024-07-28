/*
 * File:   newavr-main.c
 * Author: olivier
 *
 * Created on May 1, 2024, 8:15 PM
 */

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include "lib.h"
#include "EventQueue.h"
#include "Lcd1602.h"


/* ************************ END OF DEFINITIONS ************************* */

/* Fuse defaults:
 *  - Low: 0x5e
 *  - High: 0x9b
 *  - Extended: 0xf3 (BODLEVEL 2V6, HWBE)
 */


FUSES = {
    .low =
    // FUSE_CKSEL2 & FUSE_CKSEL3 & // CKSEL[3:1] = 110 for 8MHz crystal (FUSE_CKSELn)
    FUSE_CKSEL1 & // FUSE_CKSEL0 &
    FUSE_SUT1 & FUSE_SUT0 & // SUT = 10 for 14 cycles after reset (fastest)
    FUSE_CKOUT & // Allow CKOUT (FUSE_CKOUT)
    0xff,   // FUSE_CKDIV8, // FUSE_CKDIV8 unprogrammed
    .high =
    // FUSE_BOOTRST &              // FUSE_BOOTRST: Move boot to upper flash
    FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & // 11: 512 words, 10: 1K, 01: 2K, 00: 4K
    //                            // FUSE_BOOTSZn: boot loader section size (128 words/page), 11 =
    // FUSE_EESAVE &             // Preserve EEPROM upon flash erase
    //FUSE_WDTON &              // enable interrupts
    FUSE_SPIEN & FUSE_JTAGEN, // & FUSE_OCDEN, // Enable JTAG and SPI
    .extended =
    FUSE_BODLEVEL2 & // FUSE_BODLEVELn: 011 for 2.6V
    FUSE_HWBE // FUSE_HWBE: Hardware Boot Enable
};
// ==========================================================================


uint16_t Time(void);
uint16_t Time(void)
{
    uint16_t before, after;
    
    before = TCNT1;
    sleep_us(10);
    after = TCNT1;
    after -= before;
    return after;
}

uint8_t GetResetSource(void) {
    return MCUSR;
}

/** Clocks initialization. The external crystal is assumed to be 8MHz.
 */
void ClockInit(void) {
    // Set CPU clock to the frequency of the crystal
    CLKPR = CLKPCE; // 0x80, to enable the reset of the CLKPS bits
    CLKPR = 0;

    // USB PLL
    PLLCSR = PLLP1 | PLLP0 | PLLE;
    while (0 == (PLLCSR & PLOCK)) {
        // Do nothing
    }
}

void SetTimer0(void)
{
    // System tick
    TCNT0 = 0;
    TCCR0A = 0x02;
    TCCR0B = 0x03;  // Prescaler x64
    OCR0A = 124;    // 1ms interrupt
    OCR0B = 0;
    TIMSK0 = 0x02;
}

void SetTimer1(void)
{
    // Fast timer for performance measurement
    TCCR1A = 0;
    TCCR1B = 1;
    TCCR1C = 0;
    TIMSK1 = 0;
}

/** Board Support package - Ports directions
 *
 */
void PortsInit(void) {
    PORTA = 0;
    DDRA = 0x03;
}

/** SysInit: Hardware initialization
 */
const char LcdTitle[] PROGMEM = ">Battery Tester<";
const char LcdNoLoad[] PROGMEM = "  Load missing  ";

void SysInit(void) {
    Lcd1602Driver lcd;
    volatile uint16_t duration;
 
    SetTimer1();
    duration = Time();
    
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    PRR0 = 0; // Set bits matching unused peripherals
    PRR1 = (1 << PRUSART1);

    PortsInit();
    // ClockInit();
    lcd.Init();
    lcd.SendConstStr(LcdTitle);
    lcd.SetAddress(0, 0x40);
    lcd.SendConstStr(LcdNoLoad);
    SetTimer0();
    sei();
}

void SystemError(void) {
    // Set ports to inputs, except LEDs
    DDRA |= 0x03;
    while (1) {
        PORTA = (1 == (PORTA & 0x03)) ? 2 : 1;
        sleep_us(0xffff);
    }
}

/** main
 * @return Returns 0, if at all...
 */
int main(void) {
    MCUSR = 0;
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    /* Turn off WDT */
    WDTCSR = 0x00;
    SysInit();
    //SystemError();
    PORTA = 2;
    DDRA = 3;
    /* Replace with your application code */
    while (1) {
        EventStruct ev;

        wdt_reset();
        while (!Queue.IsEmpty())
        {
            Queue.Pop(&ev);
        }
        sleep_cpu();
    }
    return 0;
}
