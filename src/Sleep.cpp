/**
 */

#include <avr/io.h>
#include <avr/cpufunc.h>

#include "lib.h"

#pragma GCC push_options
#pragma GCC optimize ("O2")

void sleep_us(uint16_t t)
{
    while (t > 0)   {
        asm volatile("nop;");
        asm volatile("nop;");
        asm volatile("nop;");
        asm volatile("nop;");
        --t;
    }
}

#pragma GCC pop_options
