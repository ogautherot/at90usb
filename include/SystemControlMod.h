/* 
 * File:   SystemControlMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:27 PM
 */

#ifndef SYSTEMCONTROLMOD_H
#define	SYSTEMCONTROLMOD_H

#include <avr/io.h>
#include <avr/interrupt.h>


class SystemControlMod {
public:
    SystemControlMod();
    //SystemControlMod(const SystemControlMod& orig);
    //virtual ~SystemControlMod();
    
    void SetDebugRegister(uint8_t d)
    {
        while (OCDR & 0x80);
        OCDR = d;
    }
    
    uint8_t GetResetSource()
    {
        return MCUSR;
    }
    
private:

};

#endif	/* SYSTEMCONTROLMOD_H */

