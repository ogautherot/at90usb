
#include <avr/io.h>
#include <avr/interrupt.h>


void ClkInit()
{
    CLKPR = 1 << CLKPCE;
    do ; while (CLKPR & (1 << CLKPCE));

    PLLCSR = (6 << PLLP0) | (1 << PLLE);

}


