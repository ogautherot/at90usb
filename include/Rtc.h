/*
 * File:   Rtc.h
 * Author: olivier
 *
 * Created on July 29, 2024, 12:35 PM
 */

#ifndef RTC_H
#define RTC_H

#include <stdint.h>

#include "arch.h"

#include "TimerMod.h"

typedef struct RtcBuf {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} RtcBuf;

class Rtc {
public:
    Rtc();
    // Rtc(const Rtc& orig);
    // virtual ~Rtc();

    void increment(void);

    void startRtc(void)
    {
        timers.startTimer3();
    }

    void stopRtc(void)
    {
        timers.stopTimer3();
    }

    void resetRtc(void)
    {
        timers.resetTimer3();
    }

    void getTime(RtcBuf* ts);

    uint8_t getSecond()
    {
        return LocalTs.second;
    }

    uint8_t getMinute()
    {
        return LocalTs.minute;
    }

    uint8_t getHour()
    {
        return LocalTs.hour;
    }

    char* strTime(void);

private:
    volatile RtcBuf LocalTs;
};

extern Rtc rtc;

#endif /* RTC_H */
