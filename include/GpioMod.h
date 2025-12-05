/*
 * File:   GpioMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:29 PM
 */

#ifndef GPIOMOD_H
#define GPIOMOD_H

/** @brief GPIO driver module.
 *
 *
 */

#include "PowerMeter.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#define LED_SINK_MASK (1 << 0)
#define LED_CHARGING_MASK (1 << 1)
#define CTRL_SINK_MASK (1 << 2)
#define CTRL_SHUNT_LOAD_MASK (1 << 3)
#define CTRL_EXT_LOAD_MASK (1 << 4)

class GpioMod {
public:
    GpioMod();
    // GpioMod(const GpioMod& orig);
    // virtual ~GpioMod();

    void TogglePin(uint8_t port, uint8_t pin)
    {
        switch (port) {
        case 0:
            PINA = (1 << pin);
            break;
        case 1:
            PINB = (1 << pin);
            break;
        case 2:
            PINC = (1 << pin);
            break;
        case 3:
            PIND = (1 << pin);
            break;
        case 4:
            PINE = (1 << pin);
            break;
        case 5:
            PINF = (1 << pin);
            break;
        }
    }

    void SetPin(uint8_t port, uint8_t pin)
    {
        switch (port) {
        case 0:
            PORTA |= (1 << pin);
            break;
        case 1:
            PORTB |= (1 << pin);
            break;
        case 2:
            PORTC |= (1 << pin);
            break;
        case 3:
            PORTD |= (1 << pin);
            break;
        case 4:
            PORTE |= (1 << pin);
            break;
        case 5:
            PORTF |= (1 << pin);
            break;
        }
    }

    void SetHiZ(uint8_t port, uint8_t pin)
    {
        // Set first to input and then disable the pull-up
        switch (port) {
        case 0:
            DDRA &= ~(1 << pin);
            PORTA &= ~(1 << pin);
            break;
        case 1:
            DDRB &= ~(1 << pin);
            PORTB &= ~(1 << pin);
            break;
        case 2:
            DDRC &= ~(1 << pin);
            PORTC &= ~(1 << pin);
            break;
        case 3:
            DDRD &= ~(1 << pin);
            PORTD &= ~(1 << pin);
            break;
        case 4:
            DDRE &= ~(1 << pin);
            PORTE &= ~(1 << pin);
            break;
        case 5:
            DDRF &= ~(1 << pin);
            PORTF &= ~(1 << pin);
            break;
        }
    }

    void ClearHiZ(uint8_t port, uint8_t pin, uint8_t val)
    {
        // Set the port value and switch to low impedance
        switch (port) {
        case 0:
            if (val) {
                PORTA |= (1 << pin);
            } else {
                PORTA &= ~(1 << pin);
            }
            DDRA |= (1 << pin);
            break;
        case 1:
            if (val) {
                PORTB &= ~(1 << pin);
            } else {
                PORTB &= ~(1 << pin);
            }
            DDRB &= ~(1 << pin);
            break;
        case 2:
            if (val) {
                PORTC &= ~(1 << pin);
            } else {
                PORTC &= ~(1 << pin);
            }
            DDRC &= ~(1 << pin);
            break;
        case 3:
            if (val) {
                PORTD &= ~(1 << pin);
            } else {
                PORTD &= ~(1 << pin);
            }
            DDRD &= ~(1 << pin);
            break;
        case 4:
            if (val) {
                PORTE &= ~(1 << pin);
            } else {
                PORTE &= ~(1 << pin);
            }
            DDRE &= ~(1 << pin);
            break;
        case 5:
            if (val) {
                PORTF &= ~(1 << pin);
            } else {
                PORTF &= ~(1 << pin);
            }
            DDRF &= ~(1 << pin);
            break;
        }
    }

    void SetLedSink(void)
    {
        PORTA |= LED_SINK_MASK;
    }

    void ClearLedSink(void)
    {
        PORTA &= ~LED_SINK_MASK;
    }

    void SetLedCharging(void)
    {
        PORTA |= LED_CHARGING_MASK;
    }

    void ClearLedCharging(void)
    {
        PORTA &= ~LED_CHARGING_MASK;
    }

    void SetControlSink(void)
    {
        PORTA |= CTRL_SINK_MASK;
    }

    void ClearControlSink(void)
    {
        PORTA &= ~CTRL_SINK_MASK;
    }

    void SetControlShuntLoad(void)
    {
        PORTA |= CTRL_SHUNT_LOAD_MASK;
    }

    void ClearControlShuntLoad(void)
    {
        PORTA &= ~CTRL_SHUNT_LOAD_MASK;
    }

    void SetControlExtLoad(void)
    {
        PORTA |= CTRL_EXT_LOAD_MASK;
    }

    void ClearControlExtLoad(void)
    {
        PORTA &= ~CTRL_EXT_LOAD_MASK;
    }

    uint8_t
    GetKeyMask(void)
    {
        return (PORTB >> 4);
    }

private:
};

extern GpioMod gpio;

#endif /* GPIOMOD_H */
