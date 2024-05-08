/* 
 * File:   GpioMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:29 PM
 */

#include "GpioMod.h"

GpioMod::GpioMod() {
    /* Clear bit JTD to enable JTAG. By default, set IVSEL to 0 (change only
     * to reprogram the flash base within the boot loader in upper flash) */
    MCUCR = (1 << PUD);     // JTD, IVSEL, IVCE
    
    // (1 << PCIF0) to enable Pin Change Interrupts
    PCIFR = 0;
    PCMSK0 = 0;
    PCIFR = 1;      // Optional, Clear flag
    
    // (1 << INTn) to enable external interrupt
    EIMSK = 0;
    EICRA = 0;
    EICRB = 0;
    
    /* By default, set all I/O pins to input and set the PORTx registers
     * to 0xff to activate the pull-ups (for noise reduction)           */
    DDRA = 0;
    PORTA = 0xff;
    DDRB = 0;
    PORTB = 0xff;
    DDRC = 0;
    PORTC = 0xff;
    DDRD = 0;
    PORTD = 0xff;
    DDRE = 0;
    PORTE = 0xff;
    DDRF = 0;
    PORTF = 0xff;
}

//GpioMod::GpioMod(const GpioMod& orig) {
//}

//GpioMod::~GpioMod() {
//}


#if 0
ISR(INT0_vect)
{
    EIFR = INTF0;
}
#endif

#if 0
ISR(INT1_vect)
{
    EIFR = INTF1;
}
#endif

#if 0
ISR(INT2_vect)
{
    EIFR = INTF2;
}
#endif

#if 0
ISR(INT3_vect)
{
    EIFR = INTF3;
}
#endif

#if 0
ISR(INT4_vect)
{
    EIFR = INTF4;
}
#endif

#if 0
ISR(INT5_vect)
{
    EIFR = INTF5;
}
#endif

#if 0
ISR(INT6_vect)
{
    EIFR = INTF6;
}
#endif

#if 0
ISR(INT7_vect)
{
    EIFR = INTF7;
}
#endif
