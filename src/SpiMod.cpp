/* 
 * File:   SpiMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:37 PM
 */

#include "SpiMod.h"

SpiMod::SpiMod() {
    // Disable SPI by default
    SPCR = 0;
    SPSR = 0;
    // SPDR
}

//SpiMod::SpiMod(const SpiMod& orig) {
//}

//SpiMod::~SpiMod() {
//}

ISR(SPI_STC_vect)
{
    
}
