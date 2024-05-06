/* 
 * File:   AdcMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:41 PM
 */

#ifndef ADCMOD_H
#define	ADCMOD_H

#include <stdint.h>
#include <string.h>

#include <avr/io.h>


class AdcMod {
public:
    AdcMod();
    //AdcMod(const AdcMod& orig);
    //virtual ~AdcMod();

    uint16_t GetCurrentMa()     {
        return CurrentSample + CurrentSample + (CurrentSample / 2);
    }

    uint16_t GetBatteryVoltage10mV()    {
        return BatterySample + BatterySample + (BatterySample / 2);
    }

    uint16_t GetCollectorVoltage10mV() {
        return CollectorSample + CollectorSample + (CollectorSample / 2);
    }
    
private:
    // With a 1 ohm resistor, current resolution is 2.5mA
    uint16_t CurrentSample;
    uint16_t BatterySample;
    uint16_t CollectorSample;

};

extern AdcMod Adc;

#endif	/* ADCMOD_H */

