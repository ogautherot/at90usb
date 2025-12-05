/*
 * File:   GpioMod.cpp
 * Author: olivier
 *
 * Created on May 1, 2024, 10:29 PM
 */

#include "GpioMod.h"

GpioMod::GpioMod()
{
    /* Clear bit JTD to enable JTAG. By default, set IVSEL to 0 (change only
     * to reprogram the flash base within the boot loader in upper flash) */
    MCUCR = (1 << PUD); // JTD, IVSEL, IVCE

    // (1 << PCIF0) to enable Pin Change Interrupts
    PCIFR = 0;
    PCMSK0 = 0;
    PCIFR = 1; // Optional, Clear flag

    // (1 << INTn) to enable external interrupt
    EIMSK = 0;
    EICRA = 0;
    EICRB = 0;

    /* By default, set all I/O pins to input and set the PORTx registers
     * to 0xff to activate the pull-ups (for noise reduction)           */
    // PORTA[1:0]: LEDs
    // PORTA[4:2]: Control signals for current sink
    PORTA = 0xe0;
    DDRA = 0x1f;

    // PORTB[7:4]: IN keys
    PORTB = 0xff;
    DDRB = 0;

    // LCD interface
    PORTC = 0xff;
    DDRC = 0x7f;

    // Ports D[1:0]: assigned to TWI if TWEN is set to 1
    // Port D2: IN (CHOK)
    // Port D3: OUT (EN)
    PORTD = 0xff;
    DDRD = 0;

    // Not used on board
    PORTE = 0xff;
    DDRE = 0;

    // Analog inputs and JTAG. The JTAG interface disables automatically the GPIOs.
    PORTF = 0xff;
    DDRF = 0;
}

// GpioMod::GpioMod(const GpioMod& orig) {
// }

// GpioMod::~GpioMod() {
// }

ISR(INT0_vect)
{
    while (1)
        ;
    EIFR = INTF0;
}

ISR(INT1_vect)
{
    while (1)
        ;
    EIFR = INTF1;
}

ISR(INT2_vect)
{
    while (1)
        ;
    EIFR = INTF2;
}

ISR(INT3_vect)
{
    while (1)
        ;
    EIFR = INTF3;
}

ISR(INT4_vect)
{
    while (1)
        ;
    EIFR = INTF4;
}

ISR(INT5_vect)
{
    while (1)
        ;
    EIFR = INTF5;
}

ISR(INT6_vect)
{
    while (1)
        ;
    EIFR = INTF6;
}

ISR(INT7_vect)
{
    while (1)
        ;
    EIFR = INTF7;
}

ISR(PCINT0_vect)
{
    while (1)
        ;
    PCIFR = 1;
}
