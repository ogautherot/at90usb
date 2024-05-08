/* 
 * File:   TwiMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:39 PM
 */

#ifndef TWIMOD_H
#define	TWIMOD_H

#include <avr/io.h>
#include <avr/interrupt.h>


class TwiMod {
public:
    TwiMod();
    //TwiMod(const TwiMod& orig);
    //virtual ~TwiMod();
    
    uint8_t GetStatus()
    {
        return TWSR;
    }
    
    uint8_t GetData()
    {
        return TWDR;
    }
    
    
private:

};

#endif	/* TWIMOD_H */

