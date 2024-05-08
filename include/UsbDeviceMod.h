/* 
 * File:   UsbDeviceMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:40 PM
 */

#ifndef USBDEVICEMOD_H
#define	USBDEVICEMOD_H

#include <avr/io.h>
#include <avr/interrupt.h>


class UsbDeviceMod {
public:
    UsbDeviceMod();
    //UsbDeviceMod(const UsbDeviceMod& orig);
    //virtual ~UsbDeviceMod();
    
    void ClearInterrupt(uint8_t mask)   {
        UHINT = mask;
    }
    
    uint8_t GetHostAddress()
    {
        return UHADDR;
    }
    
    uint8_t GetHostFrameNumber()
    {
        return UHFNUM;
    }
    
    uint8_t GetHostFrameLength()
    {
        return UHFLEN;
    }
    
    uint8_t GetReqNumber()
    {
        return UPINRQX;
    }
    
    void ResetPipe(uint8_t mask)
    {
        UPRST = mask;
    }
    
    uint8_t GetStatus()
    {
        return UPSTAX;
    }
    
    uint8_t GetPipeData()
    {
        return UPDATX;
    }
    
    uint16_t GetDeviceFrameNumber()
    {
        return UDFNUML;
    }
    
    uint8_t GetDeviceFrameNumberError()
    {
        return UDMFN;
    }
    
    uint8_t GetEndpointStatus()
    {
        return UESTA0X;
    }
    
    uint8_t GetControlStatus()
    {
        return UESTA1X;
    }
    
    uint16_t GetByteCount()
    {
        return UEBCX;
    }
    
    uint8_t GetEndpointIntMask()
    {
        return UEINT;
    }
    
    uint8_t GetEndpointErrorFlags()
    {
        return UPERRX;
    }
    
    uint16_t GetEndpointBytesCount()
    {
        return UPBCX;
    }
    
    uint8_t GetPipeIntFlags()
    {
        return UPINT;
    }
    
private:

};

#endif	/* USBDEVICEMOD_H */

