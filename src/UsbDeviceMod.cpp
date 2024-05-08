/* 
 * File:   UsbDeviceMod.cpp
 * Author: olivier
 * 
 * Created on May 1, 2024, 10:40 PM
 */

#include "UsbDeviceMod.h"

UsbDeviceMod::UsbDeviceMod() {
    UHWCON = 0;
    USBCON = 0;
    USBSTA = 0;
    USBINT = 0;
    OTGCON = 0;
    OTGIEN = 0;
    // OTGINT
    UDCON = 0;
    // UDINT
    // UDIEN
    UDADDR = 0;
    UEINTX = 0;
    UENUM = 0;
    UERST = 0;
    UECONX = 0;
    UECFG0X = 0;
    UECFG1X = 0;
    UEIENX = 0;
    OTGTCON = 0;    // OTG Timer Config
    
    UHIEN = 0;  // If needed
    UHCON = 1;
    UPNUM = 0;
    UPCONX = 0;
    UPIENX = 0;
    
    UPCFG0X = 0;
    UPCFG1X = 0;
    UPCFG2X = 0;
}

//UsbDeviceMod::UsbDeviceMod(const UsbDeviceMod& orig) {
//}

//UsbDeviceMod::~UsbDeviceMod() {
//}

ISR(USB_GEN_vect)
{
    uint8_t UPINTX;
}

ISR(USB_COM_vect)
{
    
}
