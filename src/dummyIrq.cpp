/*
 */

// #include <stdlib.h>

// #include <avr/iousb646.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TRAP(x)   \
    ISR(x)        \
    {             \
        while (1) \
            ;     \
    }

// TRAP(INT0_vect)
// TRAP(INT1_vect)
// TRAP(INT2_vect)
// TRAP(INT3_vect)
// TRAP(INT4_vect)
// TRAP(INT5_vect)
// TRAP(INT6_vect)
// TRAP(INT7_vect)
// TRAP(PCINT0_vect)
// TRAP(USB_GEN_vect)
// TRAP(USB_COM_vect)
// TRAP(WDT_vect)
// TRAP(TIMER2_COMPA_vect)
// TRAP(TIMER2_COMPB_vect)
// TRAP(TIMER2_OVF_vect)
// TRAP(TIMER1_CAPT_vect)
// TRAP(TIMER1_COMPA_vect)
// TRAP(TIMER1_COMPB_vect)
// TRAP(TIMER1_COMPC_vect)
// TRAP(TIMER1_OVF_vect)
// TRAP(TIMER0_COMPA_vect)
// TRAP(TIMER0_COMPB_vect)
// TRAP(TIMER0_OVF_vect)
// TRAP(SPI_STC_vect)
// TRAP(USART1_RX_vect)
// TRAP(USART1_UDRE_vect)
// TRAP(USART1_TX_vect)
// TRAP(ANALOG_COMP_vect)
// TRAP(ADC_vect)
// TRAP(EE_READY_vect)
// TRAP(TIMER3_CAPT_vect)
// TRAP(TIMER3_COMPA_vect)
// TRAP(TIMER3_COMPB_vect)
// TRAP(TIMER3_COMPC_vect)
// TRAP(TIMER3_OVF_vect)
// TRAP(TWI_vect)
// TRAP(SPM_READY_vect)
