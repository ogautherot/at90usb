/* 
 * File:   AdcMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:41 PM
 */

#include "AdcMod.h"

AdcMod Adc;

AdcMod::AdcMod() {
    ADMUX = 0xc0;
    ADCSRA = 0xcf;
    ADCSRB = 0;
    DIDR0 = 0x07;
    DIDR1 = 0x00;
}

#if 0
ISR(ADC_vect)
{
    uint16_t val = ADC;
}
#endif
