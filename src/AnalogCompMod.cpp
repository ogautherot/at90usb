/* 
 * File:   AnalogCompMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:40 PM
 */

// Not in use


#include "AnalogCompMod.h"

AnalogCompMod::AnalogCompMod()
{
    ACSR =
              (1 << ACD)        // Disable analog comparator
            //| (1 << ACBG)       // Bandgap reference
            //| (1 << ACO)        // Analog Comparator Output
            //| (1 << ACI)        // Analog Comparator Interrupt Flag
            //| (1 << ACIE)       // Analog Comparator Interrupt Enable
            //| (1 << ACIC)       // Analog Comparator Input Capture Enable
            //| (0 << ACIS)       // Analog Comparator Interrupt Mode Select
            ;
    
    

}

//AnalogCompMod::AnalogCompMod(const AnalogCompMod& orig) { }

//AnalogCompMod::~AnalogCompMod() { }

#if 0
ISR(ANALOG_COMP_vect)
{
    
}
#endif
