/* 
 * File:   EventQueue.cpp
 * Author: olivier
 * 
 * Created on May 3, 2024, 11:27 PM
 */

#include "EventQueue.h"

#define QUEUE_FLAGS_EMPTY       1
#define QUEUE_FLAGS_FULL        2
#define QUEUE_FLAGS_OVF         4


EventQueue Queue;

EventQueue::EventQueue() {
    Flags = QUEUE_FLAGS_EMPTY; // .Empty = 1;
}

bool EventQueue::IsEmpty(void) {
    return Flags & QUEUE_FLAGS_EMPTY;
}

int8_t EventQueue::Push(uint8_t t, uint8_t arg0, uint16_t arg1) {
    uint8_t id = IdxIn;
    uint8_t flags = Flags;
    EventStruct *Event = &Events[id];
    EventStruct myEvent = {.s =
        { .EvType = t, .Arg0 = arg0, .Arg1 = arg1}};
    uint8_t ret = 0;

    if (flags & QUEUE_FLAGS_FULL) {
        flags |= QUEUE_FLAGS_OVF; // .Overflow = 1;
        ret = -1;
    } else {
        flags &= ~QUEUE_FLAGS_EMPTY; // .Empty = 0;

        Event->v = myEvent.v;

        id = (id + 1) & (QUEUE_SIZE - 1);
        if (id == IdxOut) {
            flags |= QUEUE_FLAGS_FULL; // .Full = 1;
        }
        IdxIn = id;
    }
    Flags = flags;
    return ret;
}

int8_t EventQueue::Pop(EventStruct *ev) {
    uint8_t flags = Flags;
    int8_t ret = 0;

    if (flags & QUEUE_FLAGS_EMPTY) {
        ret = -1;
    } else {
        uint8_t id = IdxOut;
        ev->v = Events[id].v;
        flags &= ~QUEUE_FLAGS_FULL; // .Full = 0;
        if (IdxIn == id) {
            flags |= QUEUE_FLAGS_EMPTY; // .Empty = 1;
        }
        id = (id + 1) & (QUEUE_SIZE - 1);
        IdxOut = id;
    }
    Flags = flags;

    return ret;
}

