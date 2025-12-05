/*
 * File:   AdcMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:41 PM
 */

#ifndef ADCMOD_H
#define ADCMOD_H

#include <stdint.h>
#include <string.h>

/** @file AdcMod.h
 */

#include "PowerMeter.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/// ADC channel. Current sensor.
#define ADC_CONV_INDEX_CURRENT 0
/// ADC channel. Collector voltage to measure the power dissipated in the transistor.
#define ADC_CONV_INDEX_LOAD 1
/// ADC channel. Battery voltage.
#define ADC_CONV_INDEX_BATTERY 2

/** @class AdcMod
 * @brief ADC driver.
 *
 * @details The ADC clock rate is set to 125kHz (must be below 200kHz).
 * The high-speed mode can be considered but is not qualified for now.
 * The prescaler is set to 64 (8MHz / 125kHz).
 *
 * The reference voltage is set to the internal bandgap, 2.56V. With a 10-bit
 * resolution, the resolution is of 2.5mV.
 *
 * Auto-trigger is disabled. ADC Interrupt Enable (ADIE) is off during boot and
 * activated once the master loop is started.
 *
 * The inputs are assigned to:
 * - 0: Current sensor (resolution of 2.5mA)
 * - 1: Collector voltage (resolution of 25mV)
 * - 2: Battery voltage (resolution of 25mV)
 */
class AdcMod {
    /**
     */
public:
    /** Constructor.
     */
    AdcMod();

    /** Start a conversion. The interrupt-driven state machine will scan the
     * different test points.
     */
    void StartConversion()
    {
        ADCSRA |= (1 << ADSC);
    }

    /** Select current sensor input.
     */
    void SelectCurrentSensor()
    {
        ADMUX = (ADMUX & 0xe0); // Channel 0
    }

    /** Select collector voltage input (dissipated power in the transistor).
     */
    void SelectLoadSensor()
    {
        ADMUX = (ADMUX & 0xe0) | 0x01; // Channel 1
    }

    /** Select battery voltage input.
     */
    void SelectBatterySensor()
    {
        ADMUX = (ADMUX & 0xe0) | 0x02; // Channel 2
    }

    /** Generic analog input selector.
     */
    void SelectChannel(uint8_t c)
    {
        ADMUX = (ADMUX & 0xe0) | (c & 0x1f);
    }

    /** Read the active analog input channel.
     */
    uint8_t GetChannel()
    {
        return ADMUX & 0x1f;
    }

    /** Read the ADC (16-bit register).
     */
    uint16_t ReadConversion(void)
    {
        return ADCW;
    }

    /** Get state-machine index.
     */
    uint8_t GetIndex(void)
    {
        return ConvIndex;
    }

    /** Convert ADC reading to mA (ADC resolution of 2.5mA).
     */
    uint16_t GetCurrent_mA(void)
    {
        return (CurrentSample << 1) | (CurrentSample >> 1);
    }

    /** Convert ADC reading to units of 100mV.
     */
    uint16_t GetBatteryVoltage_100mV(void)
    {
        return BatteryVoltageSample >> 2;
    }

    /** Set the index of the interrupt-driven state-machine.
     */
    void SetIndex(uint8_t idx)
    {
        ConvIndex = idx;
    }

    /// ADC reading of the current sensor.
    uint16_t CurrentSample;
    /// ADC reading of the battery voltage sensor.
    uint16_t BatteryVoltageSample;
    /// ADC reading for the load voltage sensor.
    uint16_t LoadVoltageSample;

private:
    /// Index of the convsertor state-machine
    uint8_t ConvIndex;
    /// Number of samples considered for the average per second.
    uint16_t NumSamples;
    /// Consolidated sum of the current samples.
    uint32_t CurrentSum;
    /// Consolidated sum of the load voltage samples.
    uint32_t LoadVoltageSum;
    /// Consolidated sum of the battery voltage samples.
    uint32_t BatteryVoltageSum;
};

extern AdcMod Adc;

#endif /* ADCMOD_H */
