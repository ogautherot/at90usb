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

#define EEP_MODE_ERASE          (1 << EEPM0)
#define EEP_MODE_WRITE          (2 << EEPM0)
#define EEP_MODE_ERASE_WRITE    (0 << EEPM0)

using namespace std;


class FlashMod {
public:
    FlashMod()  { }
    // FlashMod(const FlashMod& orig);
    // virtual ~FlashMod();    
    

private:
    
    
};

#endif	/* FLASHMOD_H */

