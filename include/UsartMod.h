/* 
 * File:   UsartMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:38 PM
 */

#ifndef USARTMOD_H
#define	USARTMOD_H

#include <avr/io.h>
#include <avr/interrupt.h>


class UsartMod {
public:
    UsartMod();
    //UsartMod(const UsartMod& orig);
    //virtual ~UsartMod();
    
    uint8_t GetStatusA()
    {
        return UCSR1A;
    }
    
    uint8_t GetStatusB()
    {
        return UCSR1B;
    }
    
    uint8_t GetData()   {
        return UDR1;
    }
    
    void SetData(uint8_t d)
    {
        UDR1 = d;
    }
    
private:

};

#endif	/* USARTMOD_H */

