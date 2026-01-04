/**
 *
 */

#ifndef __POWER_METER_H_INCLUDED__
#define __POWER_METER_H_INCLUDED__

#include "arch.h"

// #define __AVR_AT90USB647__ 1

// Port A
#define LED_SINK_MASK (1 << 0)
#define LED_CHARGING_MASK (1 << 1)
#define CTRL_SINK_MASK (1 << 2)
#define CTRL_SHUNT_LOAD_MASK (1 << 3)
#define CTRL_EXT_LOAD_MASK (1 << 4)

// Port B
#define PROBE_SINK_MASK (1 << 4)

/** @brief Power meter BSP.
 * The methods are mainly implemented in the class declarations to allow for
 * inlining.
 */
class PowerMeter {
public:
    PowerMeter(void) { }

    // PowerMeter(const PowerMeter& orig);
    // virtual ~PowerMeter();

    /** Discharge LED control methods (red LED)
     *
     * @param on true to turn on, false to turn off
     */
    void setLedSink(bool on)
    {
        if (on) {
            PORTA |= LED_SINK_MASK;
        } else {
            PORTA &= ~LED_SINK_MASK;
        }
    }

    /** Charging LED control methods (green LED)
     *
     * @param on true to turn on, false to turn off
     */
    void setLedCharging(bool on)
    {
        if (on) {
            PORTA |= LED_CHARGING_MASK;
        } else {
            PORTA &= ~LED_CHARGING_MASK;
        }
    }

    /** Turn on/off the discharge circuit, i.e. the Darlington transistor.
     * Do not turn on before checking that the battery voltage is safe in the
     * given operating conditions.
     * Turn off at boot.
     *
     * @param on true to turn on, false to turn off
     */
    void setControlSink(bool on)
    {
        if (on) {
            PORTA |= CTRL_SINK_MASK;
        } else {
            PORTA &= ~CTRL_SINK_MASK;
        }
    }

    /** Bypass the 2.7 ohm resistor on the collector if the battery voltage is
     * low (typically below 3.6V). Turn off at boot.
     *
     * @param on true to turn on, false to turn off
     */
    void setControlShuntLoad(bool on)
    {
        if (on) {
            PORTA |= CTRL_SHUNT_LOAD_MASK;
        } else {
            PORTA &= ~CTRL_SHUNT_LOAD_MASK;
        }
    }

    /** Connect or disconnect the external load (power resistor bank) for
     * high-voltage batteries (over 12V).
     * Turn off at boot.
     *
     * @param on true to turn on, false to turn off
     */
    void setControlExtLoad(bool on)
    {
        if (on) {
            PORTA |= CTRL_EXT_LOAD_MASK;
        } else {
            PORTA &= ~CTRL_EXT_LOAD_MASK;
        }
    }

    /** Low current sink to check battery voltage. Should be the first step of
     * the battery test procedure.
     *
     * @param on true to turn on, false to turn off
     */
    void setProbeSink(bool on)
    {
        if (on) {
            PORTA |= (1 << 5);
        } else {
            PORTA &= ~(1 << 5);
        }
    }
};

// BSP API
extern PowerMeter powerMeter;

// Error number variable
extern uint16_t errno;

#endif // __POWER_METER_H_INCLUDED__
