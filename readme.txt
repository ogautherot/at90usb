
ADC:    Chained readings
        - Requires 125us slots between channel changes
        - Case for Timer0
        - Send event upon reading the last sample

TIMER0:
        - ADC channel sync

TIMER1: Free running

TMER2:

TIMER3: RTC
        - prescaler x64 (250kHz)
        - interrupts @10ms

DIV10(v)        (v + v/2 + v/16 + v/32) >> 4


