/*
 * File:   AdcMod.cpp
 * Author: olivier
 *
 * Created on May 1, 2024, 10:41 PM
 */

#include <stdlib.h>

#include "AdcMod.h"
#include "EventQueue.h"

#include "GpioMod.h"

// Clear potential pending interrupt
#define ADC_DEFAULT_STATUS ((1 << ADEN) | (1 << ADIF) | (1 << ADPS2) | (1 << ADPS1))

/** Set reference to 2.56V (REFS[1:0] = 11), enable the ADC, clear potential
 * pending interrupt, prescaler set to 64 (ADPS[2:0] = 110), digital inputs are
 * disabled.
 *
 * A first conversion is started to initialize the converter.
 */
AdcMod::AdcMod()
{
    // REFS[1:0]=11 (2.56V ref), channel 0. Readings are in units of 10mV
    // ADLAR=0 (right adjust)
    ADMUX = (1 << REFS1) | (1 << REFS0);

    // Enable converter and start first conversion (the first one
    // initializes the converter).
    // Prescaler x64 (125kHz / 8us)
    // Conversion time: 13 * 8us = 104us / 9.6ks/s
    ADCSRA = ADC_DEFAULT_STATUS;
    ADCSRA = ADC_DEFAULT_STATUS | (1 << ADSC); // 0xde;

    ADCSRB = ADHSM; // No trigger, high speed
    DIDR0 = 0x07;   // AN0, AN1 and AN2
    DIDR1 = 0x00;

    // Measurement state machine
    ConvIndex = 0;

    //    while (0 == (ADCSRA & (1 << ADIF)));

    // Enable interrupts
    ADCSRA = ADC_DEFAULT_STATUS | (1 << ADIE);
}

/** ADC interrupt service routine. Check for 2 consecutive stable readings.
 */
ISR(ADC_vect)
{
    // Interrupt flag disabled automatically
    uint16_t val = ADCW;
    static uint16_t LastVal = 0;
    uint8_t index = Adc.GetIndex();

    if (2 > abs(val - LastVal))
    {
        if (ADC_CONV_INDEX_CURRENT == index)
        {
            index = ADC_CONV_INDEX_LOAD;
            Adc.CurrentSample = val;
            Adc.SelectLoadSensor();
        }
        else if (ADC_CONV_INDEX_LOAD == index)
        {
            index = ADC_CONV_INDEX_BATTERY;
            Adc.LoadVoltageSample = val;
            Adc.SelectBatterySensor();
        }
        else if (ADC_CONV_INDEX_BATTERY == index)
        {
            Adc.BatteryVoltageSample = val;
            index = 0;
            Adc.BatteryVoltageSample = val;
            Adc.SelectCurrentSensor();
            Queue.Push(ADC_ELAPSED, 0, 0);
        }
        Adc.SetIndex(index);
        LastVal = 0;
    }
}
