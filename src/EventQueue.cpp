/*
 * File:   EventQueue.cpp
 * Author: olivier
 *
 * Created on May 3, 2024, 11:27 PM
 */

#include <string.h>

#include "PowerMeter.h"
#include "GpioMod.h"
#include "EventQueue.h"

#define QUEUE_FLAGS_EMPTY 1
#define QUEUE_FLAGS_FULL 2
#define QUEUE_FLAGS_OVF 4

EventQueue::EventQueue()
{
    memset(&Queue, 0, sizeof(Queue));
    _Flags = { .Empty = 1, .Full = 0, .Overflow = 0 };
}

bool EventQueue::isEmpty(void)
{
    return _Flags.Empty;
}

#pragma GCC optimize("Os")

int8_t EventQueue::push(uint8_t t, uint8_t arg0, uint16_t arg1)
{
    uint16_t ts = TCNT1;
    uint8_t id = _IdxIn;
    EventStruct* Event = &_Events[id];
    EventStruct myEvent = { .s = { .EvType = t, .Arg0 = arg0, .Arg1 = arg1 } };
    uint8_t ret = 0;

#ifdef __AVR__
    uint8_t sreg = SREG & 0x80;

    cli();
#endif

    if (_Flags.Full) {
        _Flags.Overflow = 1;
        ret = -1;
    } else {
        _Flags.Empty = 0;

        Event->v = myEvent.v;

        id = (id + 1) & (QUEUE_SIZE - 1);
        if (id == _IdxOut) {
            _Flags.Full = 1;
        }

        _IdxIn = id;
    }

    ts = TCNT1 - ts;
    if (ts > _PushTime) {
        _PushTime = ts;
    }

#ifdef __AVR__
    SREG = sreg;
#endif

    return ret;
}

int8_t EventQueue::pop(EventStruct* ev)
{
    uint16_t ts = TCNT1;
    int8_t ret = 0;

#ifdef __AVR__
    uint8_t sreg = SREG;

    cli();
#else
#endif

    if (_Flags.Empty) {
        ret = -1;
    } else {
        uint8_t id = _IdxOut;

        ev->v = _Events[id].v;
        _Events[id].v = 0;
        _Flags.Full = 0;

        id = (id + 1) & (QUEUE_SIZE - 1);
        if (_IdxIn == id) {
            _Flags.Empty = 1;
        }

        _IdxOut = id;
    }

    ts = TCNT1 - ts;
    if (ts > _PopTime) {
        _PopTime = ts;
    }

#ifdef __AVR__
    SREG = sreg;
#else
#endif

    return ret;
}
