/* 
 * File:   Timer16Mod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:34 PM
 */

#include "Timer16Mod.h"

Timer16Mod::Timer16Mod()
{
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;
    TCNT1 = 0;
    TIMSK1 = 0;
    
    TCCR3A = 0;
    TCCR3B = 0;
    TCCR3C = 0;
    TCNT3 = 0;
    TIMSK3 = 0;
    
    TIFR1 = 0;  // (1 << TOV1) || (1 << OCF1A) 
    TIFR3 = 0;
}

//Timer16Mod::Timer16Mod(const Timer16Mod& orig) {
//}

//Timer16Mod::~Timer16Mod() {
//}


#if 0

ISR(TIMER1_CAPT_vect)
{
    
}
#endif

#if 0
ISR(TIMER1_COMPA_vect)
{
    
}
#endif

#if 0
ISR(TIMER1_COMPB_vect)
{
    
}
#endif

#if 0
ISR(TIMER1_COMPC_vect)
{
    
}
#endif

#if 0
ISR(TIMER1_OVF_vect)
{
    
}
#endif

#if 0
ISR(TIMER3_CAPT_vect)
{
    
}
#endif

#if 0
ISR(TIMER3_COMPA_vect)
{
    
}
#endif

#if 0
ISR(TIMER3_COMPB_vect)
{
    
}
#endif

#if 0
ISR(TIMER3_COMPC_vect)
{
    
}
#endif

#if 0
ISR(TIMER3_OVF_vect)
{
    
}
#endif

