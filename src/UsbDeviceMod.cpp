/*
 * File:   UsbDeviceMod.cpp
 * Author: olivier
 *
 * Created on May 1, 2024, 10:40 PM
 */

#include "UsbDeviceMod.h"

const USB_DeviceDescriptor_t PROGMEM DeviceDescriptor = {
    .bLength = sizeof(USB_DeviceDescriptor_t),
    .bDescriptorType = DESCRIPTOR_TYPE_DEVICE,
    .bcdUSB = USB_VERSION(1, 1, 0),
    .bDeviceClass = USB_CLASS_VENDOR,
    .bDeviceSubClass = USB_SUBCLASS_NONE,
    .bDeviceProtocol = USB_PROTOCOL_NONE,
    .bMaxPacketSize0 = 8,
    .idVendor = 0x0123,
    .idProduct = 0x4567,
    .bcdDevice = USB_VERSION(1, 0, 0),
    .iManufacturer = STRING_ID_MANUFACTURER,
    .iProduct = STRING_ID_PRODUCT,
    .iSerialNumber = STRING_ID_SERIAL,
    .bNumConfigurations = 1
};

const USB_Configuration_t PROGMEM ConfigurationDescriptor = {
    .Configuration = {
        .bLength = sizeof(USB_ConfigurationDescriptor_t),
        .bDescriptorType = DESCRIPTOR_TYPE_CONFIGURATION,
        .wTotalLength = sizeof(USB_Configuration_t),
        .bNumInterfaces = 0x01,
        .bConfigurationValue = 0x01,
        .iConfiguration = 0x00,
        .bmAttributes = 0xc0, // USB_MASK2CONFIG(USB_CONFIG_SELF_POWERED),
        .bMaxPower = USB_CURRENT_CONSUMPTION(100),
    },
    .Interface = {
        .bLength = sizeof(USB_InterfaceDescriptor_t),
        .bDescriptorType = DESCRIPTOR_TYPE_INTERFACE,
        .bInterfaceNumber = 0x00,
        .bAlternateSetting = 0x00,
        .bNumEndpoints = 0x02,
        .bInterfaceClass = USB_CLASS_VENDOR,
        .bInterfaceSubClass = USB_SUBCLASS_NONE,
        .bInterfaceProtocol = USB_PROTOCOL_NONE,
        .iInterface = 0x00,
    },
    .DataINEndpoint = {
        .bLength = sizeof(USB_EndpointDescriptor_t),
        .bDescriptorType = DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = 0x80, // IN_EP,
        .bmAttributes = USB_ENDPOINT_USAGE_DATA | USB_ENDPOINT_SYNC_NO | USB_ENDPOINT_TRANSFER_INTERRUPT,
        .wMaxPacketSize = EP_SIZE,
        .bInterval = 0x0A,
    },
    .DataOUTEndpoint = {
        .bLength = sizeof(USB_EndpointDescriptor_t),
        .bDescriptorType = DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = 0, // OUT_EP,
        .bmAttributes = USB_ENDPOINT_USAGE_DATA | USB_ENDPOINT_SYNC_NO | USB_ENDPOINT_TRANSFER_INTERRUPT,
        .wMaxPacketSize = EP_SIZE,
        .bInterval = 0x0A,
    }
};

void USB_Event_OnError(void);
void USB_Event_ConfigurationChanged(const uint8_t Configuration);
const USB_DeviceCallbacks_t Events_USB = {
    .Error = USB_Event_OnError,
    .ConfigurationChanged = USB_Event_ConfigurationChanged,
};

const USB_StringDescriptor_t PROGMEM ManufacturerString = WCHAR_TO_STRING_DESCRIPTOR(L"Daniel Kampert");
const USB_StringDescriptor_t PROGMEM ProductString = WCHAR_TO_STRING_DESCRIPTOR(L"AT90USB1287 USB-Example");
const USB_StringDescriptor_t PROGMEM SerialString = WCHAR_TO_STRING_DESCRIPTOR(L"0815");
const USB_StringDescriptor_t PROGMEM LANGID = LANG_TO_STRING_DESCRIPTOR(CONV_LANG(LANG_ENGLISH, SUBLANG_FRENCH));

uint8_t UsbDeviceMod::endpointConfigure(
    const uint8_t Address, const Endpoint_Type_t Type,
    const uint8_t Size, const uint8_t DoubleBank)
{
    uint8_t Address_Temp = Address & 0x0F;
    for (uint8_t i = Address_Temp; i < 0x07; i++) {
        uint8_t UECFG0X_Temp;
        uint8_t UECFG1X_Temp;
        uint8_t UEIENX_Temp;
        UENUM = Address_Temp;
        if (i == Address_Temp) {
            UECFG0X_Temp = (Type << EPTYPE0);

            if (Address & ENDPOINT_DIR_MASK_IN) {
                UECFG0X_Temp |= (0x01 << EPDIR);
            }
            if (DoubleBank) {
                UECFG1X_Temp |= (0x01 << EPBK0);
            }

            uint8_t Temp = 0x08;
            uint8_t EPSIZE = 0x00;
            while (Temp < Size) {
                EPSIZE++;
                Temp <<= 0x01;
            }
            UECFG1X_Temp |= (EPSIZE << EPSIZE0);
            UECFG1X_Temp |= (0x01 << ALLOC);
            UEIENX_Temp = 0x00;
        } else {
            UECFG0X_Temp = UECFG0X;
            UECFG1X_Temp = UECFG1X;
            UEIENX_Temp = UEIENX;
        }
        if (!(UECFG1X_Temp & (0x01 << ALLOC))) {
            continue;
        }
        UECONX &= ~(0x01 << EPEN);
        UECFG1X &= ~(0x01 << ALLOC);
        UECONX |= (0x01 << EPEN);
        UECFG0X = UECFG0X_Temp;
        UECFG1X = UECFG1X_Temp;
        UEIENX = UEIENX_Temp;
        if (!(UESTA0X & (0x01 << CFGOK))) {
            return 0x0;
        }
    }

    return 0x01;
}

UsbDeviceMod::UsbDeviceMod()
{
    _USBDeviceState = USB_STATE_UNATTACHED;

    UHWCON = (0x01 << UVREGE);
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
    OTGTCON = 0; // OTG Timer Config

    UHIEN = 0; // If needed
    UHCON = 1;
    UPNUM = 0;
    UPCONX = 0;
    UPIENX = 0;

    UPCFG0X = 0;
    UPCFG1X = 0;
    UPCFG2X = 0;

    // USBCON &= ~(0x01 << USBE);
    USBCON = (0x01 << USBE) | (0x01 << VBUSTE);
    UDIEN |= (0x01 << EORSTE);
}

void UsbDeviceMod::init(void)
{
    USBController_Init(USB_MODE_DEVICE, USB_SPEED_LOW);
    _USBEvents = *Events;
    _DeviceState = USB_STATE_RESET;
}

void UsbDeviceMod::poll(void)
{
    if (_DeviceState == USB_STATE_UNATTACHED) {
        return;
    }
    uint8_t CurrEndpoint = UENUM;
    UENUM = ENDPOINT_CONTROL_ADDRESS;
    if (UEINTX & (0x01 << RXSTPI)) {
        USBDevice_ControlRequest();
    }
    UENUM = CurrEndpoint;
}

void USBDevice_ControlRequest(void)
{
    uint8_t* RequestHeader = (uint8_t*)&_ControlRequest;
    for (uint8_t i = 0x00; i < sizeof(USB_SetupPacket_t); i++) {
        *(RequestHeader++) = UEDATX;
    }
    UEINTX &= ~(0x01 << RXSTPI);
    switch (_ControlRequest.bRequest) {
    case REQUEST_SET_ADDRESS: {
        break;
    }
    case REQUEST_GET_DESCRIPTOR: {
        break;
    }
    case REQUEST_SET_CONFIGURATION: {
        break;
    }
    }
}

const void* USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, uint16_t* Size)
{
    uint8_t DescriptorType = (wValue >> 0x08);
    uint8_t DescriptorNumber = (wValue & 0xFF);
    switch (DescriptorType) {
    case DESCRIPTOR_TYPE_DEVICE: {
        *Size = sizeof(USB_DeviceDescriptor_t);
        return &DeviceDescriptor;
    }
    case DESCRIPTOR_TYPE_CONFIGURATION: {
        *Size = sizeof(USB_Configuration_t);
        return &ConfigurationDescriptor;
    }
    case DESCRIPTOR_TYPE_STRING: {
        switch (DescriptorNumber) {
        case STRING_ID_LANGUAGE: {
            *Size = pgm_read_byte(&LANGID.bLength);
            return &LANGID;
        }
        case STRING_ID_MANUFACTURER: {
            *Size = pgm_read_byte(&ManufacturerString.bLength);
            return &ManufacturerString;
        }
        case STRING_ID_PRODUCT: {
            *Size = pgm_read_byte(&ProductString.bLength);
            return &ProductString;
        }
        case STRING_ID_SERIAL: {
            *Size = pgm_read_byte(&SerialString.bLength);
            return &SerialString;
        }
        }
    }
    }
    *Size = 0x00;
    return NULL;
}

Endpoint_CS_State_t USB_DeviceStream_ControlIN(const void* Buffer, const uint16_t Length, const uint16_t RequestedLength)
{
    uint8_t* Buffer_Temp = (uint8_t*)Buffer;
    uint16_t Length_Temp = Length;
    uint8_t LastPacketFull = 0x00;
    if (Length > RequestedLength) {
        Length_Temp = RequestedLength;
    }
    while (Length_Temp) {
        Endpoint_CS_State_t State = USB_DeviceStream_GetControlEndpointState();
        if (State != ENDPOINT_CS_NO_ERROR) {
            return State;
        } else if (UEINTX & (0x01 << RXOUTI)) {
            break;
        }
        if (UEINTX & (0x01 << TXINI)) {
            while (Length_Temp && (UEBCX < Endpoint_ControlSize)) {
                UEDATX = pgm_read_byte(Buffer_Temp++);
                Length_Temp--;
            }
            UEINTX &= ~((0x01 << TXINI) | (0x01 << FIFOCON));
        }
    }
    while (!(UEINTX & (0x01 << TXINI)))
        ;
    UEINTX &= ~((0x01 << TXINI) | (0x01 << FIFOCON));
    while (!(UEINTX & (0x01 << RXOUTI))) {
        Endpoint_CS_State_t State = USBStream_GetControlEndpointState();
        if (State != ENDPOINT_CS_NO_ERROR) {
            return State;
        }
    }
    UEINTX &= ~((0x01 << RXOUTI) | (0x01 << FIFOCON));
    return ENDPOINT_CS_NO_ERROR;
}

static Endpoint_CS_State_t USB_DeviceStream_GetControlEndpointState(void)
{
    if (_DeviceState == USB_STATE_UNATTACHED) {
        return ENDPOINT_CS_DISCONNECT;
    } else if (__DeviceState == USB_STATE_SUSPEND) {
        return ENDPOINT_CS_SUSPEND;
    } else if (UEINTX & (0x01 << RXSTPI)) {
        return ENDPOINT_CS_ABORT_FROM_HOST;
    }

    return ENDPOINT_CS_NO_ERROR;
}
... Endpoint_CS_State_t State = USB_DeviceStream_GetControlEndpointState();
if (State != ENDPOINT_CS_NO_ERROR) {
    return State;
} else if (UEINTX & (0x01 << RXOUTI)) {
    break;
}

// UsbDeviceMod::UsbDeviceMod(const UsbDeviceMod& orig) {
// }

// UsbDeviceMod::~UsbDeviceMod() {
// }

ISR(USB_GEN_vect)
{
    if (USBINT & (0x01 << VBUSTI)) {
        USBINT &= ~(0x01 << VBUSTI);
        if (USBSTA & (0x01 << VBUS)) {
            PLLCSR = (((0x01 << PLLP1) | (0x01 << PLLP0)) | (0x01 << PLLE));
            while (!(PLLCSR & (0x01 << PLOCK)))
                ;
            _USBDeviceState = USB_STATE_POWERED;
        } else {
            PLLCSR = 0x00;
            _USBDeviceState = USB_STATE_UNATTACHED;
        }
    } else {
        // USB general
        OTGINT = 0x3f;
        USBINT = 0x03;

        // USB device
        UDINT = 0x7d;
        // ??? UEINT = 0xff;

        // Host register
        UHINT = 0x7f;
    }

    if (UDINT & (0x01 << EORSTI)) {
        UDINT &= ~(0x01 << EORSTI);
        _USBDeviceState = USB_STATE_RESET;
        Endpoint_Configure(0, ENDPOINT_TYPE_CONTROL, ENDPOINT_CONTROL_SIZE, 0);
    }

    if (USBController_CheckForInterrupt(USB_EOR_INTERRUPT)) {
        USBController_ClearInterruptFlag(USB_EOR_INTERRUPT);
        _DeviceState = USB_STATE_RESET;
        if (Endpoint_Configure(0, ENDPOINT_TYPE_CONTROL, Endpoint_ControlSize, 0)) {
            PORTD &= ~(0x01 << 0x04);
            PORTD |= (0x01 << 0x05);
        } else {
            if (_USBEvents.Error != NULL) {
                _USBEvents.Error();
            }
        }
    }
}

ISR(USB_COM_vect)
{
    while (1)
        ;

    UPIENX = 0xdf;
    UEINTX = 0xff;
}
