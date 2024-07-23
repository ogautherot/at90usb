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

#include "EventQueue.h"
#include "Lcd1602.h"

extern "C"
{
    int main(void);
}

/* ************************ END OF DEFINITIONS ************************* */

FUSES = {
    .low =
        FUSE_CKSEL2 & FUSE_CKSEL3 & // CKSEL = 1111 for 16MHz crystal (FUSE_CKSELn)
        FUSE_SUT1 & FUSE_CKSEL2 &   // SUT = 10 for 14 cycles after reset (fastest)
        FUSE_CKOUT &                // Allow CKOUT (FUSE_CKOUT)
        FUSE_CKDIV8,                // FUSE_CKDIV8 unprogrammed

    .high =
        0xff &                        // FUSE_BOOTRST: Move boot to upper flash
        FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & // 11: 512 words, 10: 1K, 01: 2K, 00: 4K
        // 0xff &                   // FUSE_BOOTSZn: boot loader section size (128 words/page), 11 =
        FUSE_EESAVE &             // Preserve EEPROM upon flash erase
        0xff &                    // FUSE_WDTON: enable interrupts
        FUSE_SPIEN & FUSE_JTAGEN, // Enable JTAG and SPI
    .extended =
        FUSE_BODLEVEL2 & // FUSE_BODLEVELn: 111 to disable
        FUSE_HWBE        // FUSE_HWBE: Hardware Boot Enable
};

uint8_t GetResetSource(void)
{
    return MCUSR;
}

/** Clocks initialization. The external crystal is assumed to be 8MHz.
 */
void ClockInit(void)
{
    // Set CPU clock to the frequency of the crystal
    CLKPR = CLKPCE; // 0x80, to enable the reset of the CLKPS bits
    CLKPR = 0;

    // USB PLL
    PLLCSR = PLLP1 | PLLP0 | PLLE;
    while (0 == (PLLCSR & PLOCK))
    {
        // Do nothing
    }
}

/** Board Support package - Ports directions
 *
 */
void PortsInit(void)
{
    PORTA = 0;
    DDRA = 0x03;
}

/** SysInit: Hardware initialization
 */
void SysInit(void)
{
    Lcd1602Driver lcd;

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    PRR0 = 0; // Set bits matching unused peripherals
    PRR1 = (1 << PRUSART1);

    PortsInit();

    ClockInit();
    lcd.Init();
    sei();
}

void SystemError(void)
{
    // Set ports to inputs, except LEDs
    while (1)
    {
        PORTA = 1;
        PORTA = 2;
    }
}

/** main
 * @return Returns 0, if at all...
 */
int main(void)
{
    /* Replace with your application code */
    while (1)
    {
        EventStruct ev;

        while (!Queue.IsEmpty())
        {
            Queue.Pop(&ev);
        }
        sleep_cpu();
    }
    return 0;
}
