/* 
 * File:   EventQueue.cpp
 * Author: olivier
 * 
 * Created on May 3, 2024, 11:27 PM
 */

#include "EventQueue.h"

EventQueue  queue;


EventQueue::EventQueue() {
    Flags.Empty = 1;
}

bool EventQueue::IsEmpty(void)
{
    return Flags.Empty;
}

int8_t EventQueue::Push(EventStruct *ev)
{
    if (Flags.Full) {
        Flags.Overflow = 1;
        return -1;
    }
    
    *((uint32_t *) &Events[IdxIn]) = *((uint32_t *) ev);
    
    IdxIn = (IdxIn + 1) & (QUEUE_SIZE - 1);
    Flags.Empty = 0;
    if (IdxIn == IdxOut)  {
        Flags.Full = 1;
    }
    return 0;
}

int8_t EventQueue::Pop(EventStruct *ev)
{
    if (Flags.Empty)    {
        return -1;
    }

    *((uint32_t *) ev) = *((uint32_t *) &Events[IdxOut]);
    Flags.Full = 0;
    if (IdxIn == IdxOut)    {
        Flags.Empty = 1;
    }
    
    return 0;
}


