/* 
 * File:   FlashMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:18 PM
 */

#ifndef FLASHMOD_H
#define	FLASHMOD_H

#include <avr/io.h>

#include <stdint.h>
#include <string.h>

using namespace std;

#include <avr/io.h>
#include <avr/interrupt.h>


class FlashMod {
public:
    FlashMod();
    // FlashMod(const FlashMod& orig);
    // virtual ~FlashMod();    
    
    uint32_t GetSignature()
    {
        return 0;  // See SPMCSR
    }
    
    // @TODO Implement page write and page erase

private:
    
    
};

#endif	/* FLASHMOD_H */

