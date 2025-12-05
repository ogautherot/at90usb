/*
 * File:   Rtc.h
 * Author: olivier
 *
 * Created on July 29, 2024, 12:35 PM
 */

#ifndef RTC_H
#define RTC_H

#include <stdint.h>

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

    void Increment(void);

    void StartRtc(void)
    {
        timers.StartTimer3();
    }

    void StopRtc(void)
    {
        timers.StopTimer3();
    }

    void ResetRtc(void)
    {
        timers.ResetTimer3();
    }

    void GetTime(RtcBuf* ts);

    uint8_t GetSecond()
    {
        return LocalTs.second;
    }

    uint8_t GetMinute()
    {
        return LocalTs.minute;
    }

    uint8_t GetHour()
    {
        return LocalTs.hour;
    }

    char* StrTime(void);

private:
    volatile RtcBuf LocalTs;
};

extern Rtc rtc;

#endif /* RTC_H */
