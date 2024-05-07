/*
 * File:   newavr-main.c
 * Author: olivier
 *
 * Created on May 1, 2024, 8:15 PM
 */


#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "EventQueue.h"

extern "C"  {
    int main(void);
}

/* ************************ END OF DEFINITIONS ************************* */

FUSES = {
    .low = 
            // CKSEL = 1111 for 16MHz crystal (FUSE_CKSELn)
            0xff &
            // SUT = 10 for 14 cycles after reset (fastest)
            FUSE_SUT1 &
            // Allow CKOUT (FUSE_CKOUT)
            FUSE_CKOUT &
            // FUSE_CKDIV8 unprogrammed
            FUSE_CKDIV8,
    .high =
            // FUSE_BOOTRST: Move boot to upper flash
            0xff &
            // FUSE_BOOTSZn: boot loader section size (128 words/page)
            // 11: 512 words, 10: 1K, 01: 2K, 00: 4K 
            0xff &
            // FUSE_EESAVE: rease EEPROM upon flash erase
            0xff &
            // FUSE_WDTON: enable interrupts
            0xff &
            // FUSE_SPIEN
            FUSE_SPIEN & FUSE_JTAGEN,
    .extended =
            // FUSE_BODLEVELn: 111 to disable
            FUSE_BODLEVEL2 &
            // FUSE_HWBE: Hardware Boot Enable
            FUSE_HWBE
            
};
int main(void) {
    /* Replace with your application code */
    while (1) {
        EventStruct ev;
        
        if (!Queue.IsEmpty())   {
            Queue.Pop(&ev);
        }
        //sleep_mode();
    }
}
