
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

typedef struct FlagsStruct {
    uint8_t Empty : 1;
    uint8_t Full : 1;
    uint8_t Overflow : 1;
    uint8_t : 5;
} FlagsStruct;

class EventQueue {
public:
    EventQueue();
    bool isEmpty(void);

    int8_t push(uint8_t t, uint8_t arg0, uint16_t arg1);
    int8_t pop(EventStruct* ev);

private:
    uint8_t _IdxIn;
    uint8_t _IdxOut;
    uint16_t _PushTime;
    uint16_t _PopTime;
    FlagsStruct _Flags;
    EventStruct _Events[QUEUE_SIZE];
};

typedef enum EventId {
    SYSTICK_ELAPSED = 1,
    RTC_ELAPSED = 2,
    ADC_ELAPSED = 3
} EventId;

extern EventQueue Queue;

#endif /* EVENTQUEUE_H */
