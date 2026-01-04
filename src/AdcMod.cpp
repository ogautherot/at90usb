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

/** ADC default configuration.
 * ADEN: ADC Enable
 * ADATE: Disable ADC Auto Trigger (0)
 * ADIF: ADC interrupt flag - clear pending interrupts
 * ADIE: ADC Interrupt Enable - disabled at boot
 * ADPS[2:0]: Prescaler x64 (125kHz @ 8MHz)
 */
/* ************************************************************* */
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
    // ADLAR=0 (right adjust). MUX = 00000 (channel 0)
    ADMUX = (1 << REFS1) | (1 << REFS0);

    // Enable converter
    // Prescaler x64 (125kHz / 8us)
    // Conversion time: 13 * 8us = 104us / 9.6ks/s
    ADCSRA = ADC_DEFAULT_STATUS;

    ADCSRB = 0; // No trigger, normal speed
    DIDR0 = 0x07; // AN0, AN1 and AN2
    DIDR1 = 0x00;
    ACSR = 0; // Disable comparator

    // Start first conversion (the first one initializes the converter).
    ADCSRA = ADC_DEFAULT_STATUS | (1 << ADSC); // 0xde;

    // Measurement state machine
    _ConvIndex = 0;
    _NumSamples = 0;
    _CurrentSample = 0;
    _CurrentSum = 0;
    _LoadVoltageSample = 0;
    _LoadVoltageSum = 0;
    _BatteryVoltageSample = 0;
    _BatteryVoltageSum = 0;
    _SampleCount = 0;

    // Wait for conversion to complete
    while (0 == (ADCSRA & (1 << ADIF))) {
        // Do nothing
    }

    // Enable interrupts
    // ADCSRA = ADC_DEFAULT_STATUS | (1 << ADIE);
}

/** ADC interrupt service routine. Check for 2 consecutive stable readings.
 */
ISR(ADC_vect)
{
    // Interrupt flag disabled automatically
    uint16_t val = ADCW;
    static uint16_t LastVal = 0;
    uint8_t index = adc0.getIndex();
    adc0._SampleCount++;

    if (2 > abs(val - LastVal)) {
        if (ADC_CONV_INDEX_CURRENT == index) {
            index = ADC_CONV_INDEX_LOAD;
            adc0._CurrentSample = val;
            adc0.selectLoadSensor();
        } else if (ADC_CONV_INDEX_LOAD == index) {
            index = ADC_CONV_INDEX_BATTERY;
            adc0._LoadVoltageSample = val;
            adc0.selectBatterySensor();
        } else if (ADC_CONV_INDEX_BATTERY == index) {
            adc0._BatteryVoltageSample = val;
            index = 0;
            adc0._BatteryVoltageSample = val;
            adc0.selectCurrentSensor();
            Queue.push(ADC_ELAPSED, 0, 0);
        }
        adc0.setIndex(index);
        LastVal = 0;
    }
}
