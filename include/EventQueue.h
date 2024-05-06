/* 
 * File:   EventQueue.h
 * Author: olivier
 *
 * Created on May 3, 2024, 11:27 PM
 */

#ifndef EVENTQUEUE_H
#define	EVENTQUEUE_H

#include <stdint.h>

#define QUEUE_SIZE  8


typedef struct EventStruct    {
    uint8_t     EvType;
    uint8_t     Arg1;
    uint16_t    Arg2;
} EventStruct;


class EventQueue {
public:
    EventQueue();
    bool IsEmpty(void);
    
    int8_t Push(EventStruct *ev);
    int8_t Pop(EventStruct *ev);
    
private:
    uint8_t IdxIn;
    uint8_t IdxOut;
    struct  {
        uint8_t Empty:1;
        uint8_t Full:1;
        uint8_t Overflow:1;
    } Flags;
    EventStruct Events[QUEUE_SIZE];
};

#endif	/* EVENTQUEUE_H */

