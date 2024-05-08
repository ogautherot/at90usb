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
#include <avr/interrupt.h>


class AdcMod {
public:
    AdcMod();
    //AdcMod(const AdcMod& orig);
    //virtual ~AdcMod();
    
    void StartConversion() {
        ADCSRA |= (1 << 6);
    }
    
    void SelectChannel(uint8_t c)
    {
        ADMUX = (ADMUX & 0xe0) | (c & 0x1f);
    }
    
    uint8_t GetChannel()
    {
        return ADMUX & 0x1f;
    }

    
private:

};

extern AdcMod Adc;

#endif	/* ADCMOD_H */

