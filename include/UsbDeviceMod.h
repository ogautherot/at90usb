/*
 * File:   UsbDeviceMod.h
 * Author: olivier
 *
 * Created on May 1, 2024, 10:40 PM
 */

#ifndef USBDEVICEMOD_H
#define USBDEVICEMOD_H

#include "PowerMeter.h"
#include "usb.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define WCHAR_TO_STRING_DESCRIPTOR(Array)                                                                                            \
    {                                                                                                                                \
        .bLength = sizeof(USB_StringDescriptor_t) + (sizeof(Array) - 2), .bDescriptorType = DESCRIPTOR_TYPE_STRING, .bString = Array \
    }

/* USB Descriptor Types. See USB 1.1 spec, page 187, table 9-5 */
#define DESCRIPTOR_TYPE_DEVICE 0x01
#define DESCRIPTOR_TYPE_CONFIGURATION 0x02
#define DESCRIPTOR_TYPE_STRING 0x03
#define DESCRIPTOR_TYPE_INTERFACE 0x04
#define DESCRIPTOR_TYPE_ENDPOINT 0x05

#define USB_VERSION(a, b, c) ((((a) & 0xf) << 8) | (((b) & 0xf) << 4) | ((c) & 0xf))

/* Class Definition */
#define USB_CLASS_VENDOR 0xFF

#define USB_SUBCLASS_NONE 0x00

#define USB_PROTOCOL_NONE 0x00

#define STRING_ID_MANUFACTURER 0
#define STRING_ID_PRODUCT 1
#define STRING_ID_SERIAL 2
#define STRING_ID_CONFIG 3
#define STRING_ID_INTERFACE 4

#define USB_CONFIG_POWERED_MASK 0x40
#define USB_CONFIG_BUS_POWERED 0x80
#define USB_CONFIG_SELF_POWERED 0xC0
#define USB_CONFIG_REMOTE_WAKEUP 0x20

#define USB_CURRENT_CONSUMPTION(a) ((a) / 2)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK 0x03
#define USB_ENDPOINT_TYPE_CONTROL 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS 0x01
#define USB_ENDPOINT_TYPE_BULK 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT 0x03
#define USB_ENDPOINT_SYNC_MASK 0x0C
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION 0x00
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS 0x04
#define USB_ENDPOINT_SYNC_ADAPTIVE 0x08
#define USB_ENDPOINT_SYNC_SYNCHRONOUS 0x0C
#define USB_ENDPOINT_USAGE_MASK 0x30
#define USB_ENDPOINT_USAGE_DATA 0x00
#define USB_ENDPOINT_USAGE_FEEDBACK 0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK 0x20
#define USB_ENDPOINT_USAGE_RESERVED 0x30

typedef struct
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} __attribute__((packed)) USB_DeviceDescriptor_t;

typedef struct
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} __attribute__((packed)) USB_ConfigurationDescriptor_t;

typedef struct
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __attribute__((packed)) USB_InterfaceDescriptor_t;

typedef struct
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} __attribute__((packed)) USB_EndpointDescriptor_t;

typedef struct
{
    USB_ConfigurationDescriptor_t Configuration;
    USB_InterfaceDescriptor_t Interface;
    USB_EndpointDescriptor_t DataINEndpoint;
    USB_EndpointDescriptor_t DataOUTEndpoint;
} USB_Configuration_t;

typedef struct
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    wchar_t bString[];
} __attribute__((packed)) USB_StringDescriptor_t;

typedef struct
{
    void (*ConfigurationChanged)(const uint8_t Configuration);
    void (*ControlRequest)(const uint8_t bRequest, const uint8_t bmRequestType, const uint16_t wValue);
    void (*Error)();
} USB_DeviceCallbacks_t;

enum Endpoint_Type_t {
    endpoint_type_none, // a connection-less endpoint
    endpoint_type_bind, // a connection-oriented bind endpoint
    endpoint_type_connect // a connection-oriented connect endpoint
};

typedef enum {
    ATTACHED,
    POWERED,
    DEFAULT,
    ADDRESSED,
    CONFIGURED,
    SUSPENDED
} USB_State_t;

class UsbDeviceMod {
public:
    UsbDeviceMod();
    // UsbDeviceMod(const UsbDeviceMod& orig);
    // virtual ~UsbDeviceMod();

    void Init(void);

    void Poll(void);

    void ClearInterrupt(uint8_t mask)
    {
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

    uint8_t Endpoint_Configure(
        const uint8_t Address, const Endpoint_Type_t Type,
        const uint8_t Size, const uint8_t DoubleBank);

private:
    volatile USB_State_t _USBDeviceState;
};

#endif /* USBDEVICEMOD_H */
