/* 
 * File:   ClockMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:25 PM
 */

#ifndef CLOCKMOD_H
#define	CLOCKMOD_H

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

class ClockMod {
public:
    ClockMod();
    //ClockMod(const ClockMod& orig);
    //virtual ~ClockMod();
    
    void Init(void);
    void StartPll(void);
    
    
private:

};

#endif	/* CLOCKMOD_H */

