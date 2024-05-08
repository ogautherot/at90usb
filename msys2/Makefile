

CXX=avr-g++


#OBJS=obj/AdcMod.o obj/AnalogCompMod.o obj/ClockMod.o obj/EepromMod.o obj/FlashMod.o obj/GpioMod.o obj/GpregMod.o obj/OcmMod.o obj/PowerMgmtMod.o obj/SpiMod.o obj/SystemControlMod.o obj/Timer16Mod.o obj/Timer8Mod.o obj/TwiMod.o obj/UsartMod.o obj/UsbDeviceMod.o
OBJS=obj/newavr-main.o obj/AdcMod.o obj/AnalogCompMod.o obj/ClockMod.o obj/EepromMod.o obj/FlashMod.o obj/GpioMod.o obj/GpregMod.o obj/OcmMod.o obj/PowerMgmtMod.o obj/SpiMod.o obj/SystemControlMod.o obj/Timer16Mod.o obj/Timer8Mod.o obj/TwiMod.o obj/UsartMod.o obj/UsbDeviceMod.o obj/EventQueue.o
TARGET=at90usb.elf
CFLAGS=-mmcu=at90usb647 -c -g -O1 -Iinclude -ffunction-sections -fdata-sections -fpack-struct -Wall -Wextra -Wpedantic 
LDFLAGS=-mmcu=at90usb647 -g
LDLIBS=-lm -lc -Wl,--gc-sections -Wl,-Map,build/${TARGET}.map


build/${TARGET}: ${OBJS}
	mkdir -p build
	${CXX} ${LDFLAGS} -o $@ ${OBJS} ${LDLIBS}
	avr-size build/${TARGET}

obj/%.o: src/%.c
	mkdir -p obj
	${CXX} ${CFLAGS} $< -o $@

obj/%.o: src/%.cpp
	mkdir -p obj
	${CXX} ${CFLAGS} $< -o $@

.PHONY: clean

clean:
	rm -rf build/* obj/*

