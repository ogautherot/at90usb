AT90USBxxx BSP
==============

ADC:    Chained readings
        - Requires 125us slots between channel changes
        - Case for Timer0
        - Send event upon reading the last sample

TIMER0:	ADC channel sync
	- Delays of 125us
	- Prescaler x8 (1MHz), OCA 125
	- One shot, stop upon overflow

TIMER1: Free running (function timing)

TMER2:	Systick @10ms
	- 

TIMER3: RTC
	- CTC mode (OCR3A)
        - prescaler x256 (250kHz)
	- OCA 31249 (122, 17)
        - interrupts @1s
	- Increment RTC within

DIV10(v)        (v + v/2 + v/16 + v/32) >> 4


