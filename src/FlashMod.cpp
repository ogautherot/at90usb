/* 
 * File:   FlashMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:18 PM
 */

#include "FlashMod.h"


FlashMod::FlashMod()
{
    SPMCSR = 0;
}

ISR(SPM_READY_vect)
{
    
}

