
/*
 * File:   EventQueue.h
 * Author: olivier
 *
 * Created on May 3, 2024, 11:27 PM
 */

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

/** @brief Event queue manager.
 *
 * This module is the core of the application. The events are treated on a
 * FIFO basis.
 */

#include <stdint.h>

#define QUEUE_SIZE 16

typedef union EventStruct {
    uint32_t v;

    struct EventFields {
        uint8_t EvType;
        uint8_t Arg0;
        uint16_t Arg1;
    } s;
} EventStruct;

class EventQueue {
public:
    EventQueue();
    bool IsEmpty(void);

    int8_t Push(uint8_t t, uint8_t arg0, uint16_t arg1);
    int8_t Pop(EventStruct* ev);

private:
    uint8_t IdxIn;
    uint8_t IdxOut;
    uint8_t Flags;
    EventStruct Events[QUEUE_SIZE];
};

typedef enum EventId {
    SYSTICK_ELAPSED = 1,
    RTC_ELAPSED = 2,
    ADC_ELAPSED = 3
} EventId;

extern EventQueue Queue;

#endif /* EVENTQUEUE_H */
