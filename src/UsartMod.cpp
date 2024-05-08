/* 
 * File:   UsartMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:38 PM
 */

#include "UsartMod.h"

UsartMod::UsartMod() {
    UBRR1 = 0;
    UCSR1C = 0;
}

//UsartMod::UsartMod(const UsartMod& orig) {
//}

//UsartMod::~UsartMod() {
//}

ISR(USART1_RX_vect)
{
    
}

ISR(USART1_UDRE_vect)
{
    
}

ISR(USART1_TX_vect)
{
    
}

