/* 
 * File:   GpregMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:24 PM
 */

#ifndef GPREGMOD_H
#define	GPREGMOD_H

#include <stdint.h>
#include <string.h>

#include <avr/io.h>


class GpregMod {
public:
    static void SetReg(uint8_t idx, uint8_t val)       {
        switch (idx)    {
            case 0:     GPIOR0 = val;   break;
            case 1:     GPIOR1 = val;   break;
            case 2:     GPIOR2 = val;   break;
        }
    }

    static uint8_t GetReg(uint8_t idx) {
        return (idx == 0) ? GPIOR0 :
                (idx == 1) ? GPIOR1 :
                (idx == 2) ? GPIOR2 :
                0;
    }

private:

};

#define Gpreg   ((GpregMod *) NULL)

#endif	/* GPREGMOD_H */

