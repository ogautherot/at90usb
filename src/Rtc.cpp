/* 
 * File:   Rtc.cpp
 * Author: olivier
 * 
 * Created on July 29, 2024, 12:35 PM
 */

#include "Rtc.h"


Rtc::Rtc() {
    LocalTs.second = 0;
    LocalTs.minute = 0;
    LocalTs.hour = 0;
}

void Rtc::Increment(void)
{
    uint8_t second = LocalTs.second;
    
    ++second;
    if (60 <= second)   {
        uint8_t minute = LocalTs.minute;
        
        second -= 60;
        ++minute;
        if (60 <= minute)   {
            minute -= 60;
            ++LocalTs.hour;
        }
        LocalTs.minute = minute;
    }
    LocalTs.second = second;
}

void Rtc::GetTime(RtcBuf *ts)
{
    // Repeat reading while seconds field moves
    do {
        ts->second = LocalTs.second;
        ts->minute = LocalTs.minute;
        ts->hour = LocalTs.hour;
    } while (ts->second != LocalTs.second);
}

char *Rtc::StrTime(void) {
    static char buf[9] = "00:00:00";
    RtcBuf ts;

    rtc.GetTime(&ts);
    buf[0] = '0' + ts.hour / 10;
    buf[1] = '0' + ts.hour % 10;
    buf[3] = '0' + ts.minute / 10;
    buf[4] = '0' + ts.minute % 10;
    buf[6] = '0' + ts.second / 10;
    buf[7] = '0' + ts.second % 10;
    buf[8] = 0;
    return buf;
}

