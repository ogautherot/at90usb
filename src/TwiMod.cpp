/* 
 * File:   TwiMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:39 PM
 */

#include "TwiMod.h"

TwiMod::TwiMod() {
    TWBR = 0;
    TWCR = 0;
    TWAMR = 0;
    
    TWAR = 0;  // Optional
}

//TwiMod::TwiMod(const TwiMod& orig) {
//}

//TwiMod::~TwiMod() {
//}

ISR(TWI_vect)
{
    
}
