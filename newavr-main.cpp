/*
 * File:   newavr-main.c
 * Author: olivier
 *
 * Created on May 1, 2024, 8:15 PM
 */


#include <avr/io.h>

#include "EventQueue.h"

extern "C"  {
    int main(void);
}


EventQueue  queue;


int main(void) {
    /* Replace with your application code */
    while (1) {
        EventQueue ev;
        
        if (!queue.IsEmpty())   {
            queue.Pop(&ev);
        }
        sleep_mode();
    }
}
