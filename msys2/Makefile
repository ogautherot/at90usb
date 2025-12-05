

CXX=avr-g++


#OBJS=obj/AdcMod.o obj/AnalogCompMod.o obj/ClockMod.o obj/EepromMod.o obj/FlashMod.o obj/GpioMod.o obj/GpregMod.o obj/OcmMod.o obj/PowerMgmtMod.o obj/SpiMod.o obj/SystemControlMod.o obj/TimerMod.o obj/TwiMod.o obj/UsartMod.o obj/UsbDeviceMod.o obj/Sleep.o
OBJS=obj/newavr-main.o obj/dummyIrq.o \
	obj/AdcMod.o obj/AnalogCompMod.o obj/ClockMod.o obj/EepromMod.o \
	obj/FlashMod.o obj/GpioMod.o obj/GpregMod.o obj/OcmMod.o obj/PowerMgmtMod.o \
	obj/SpiMod.o obj/SystemControlMod.o obj/TimerMod.o obj/TwiMod.o \
	obj/UsartMod.o obj/WatchdogMod.o \
	obj/EventQueue.o obj/Lcd1602.o obj/Sleep.o obj/Rtc.o obj/KeysMod.o \
	obj/Flash24aa512.o
	# obj/UsbDeviceMod.o 
TARGET=at90usb.elf
CFLAGSCOMMON=-mmcu=at90usb647 -c -g -Og -Iinclude -fpack-struct -Wall -Wextra \
	-Iinclude \
	#-ffunction-sections -fdata-sections 
CFLAGS=${CFLAGSCOMMON} -std=c11
CXXFLAGS=${CFLAGSCOMMON} -std=c++11
LDFLAGS=-mmcu=at90usb647 -g 
LDLIBS=-lm -lc -Wl,--gc-sections -Wl,-Map,build/${TARGET}.map


.PHONY: doc clean avarice debug

all: build/${TARGET}

doc:
	doxygen

build/${TARGET}: ${OBJS}
	mkdir -p build
	${CXX} ${LDFLAGS} -o $@ ${OBJS} ${LDLIBS}
	avr-size build/${TARGET}

obj/%.o: src/%.c
	mkdir -p obj
	${CXX} ${CFLAGS} $< -o $@

obj/%.o: src/%.cpp
	mkdir -p obj
	${CXX} ${CXXFLAGS} $< -o $@

clean:
	rm -rf build/* obj/* doc/*

avarice:
	avrdude -c atmelice -p usb646 -B 250kHz -U flash:w:build/${TARGET}:e
	avarice -4 --file build/${TARGET} localhost:3333

debug:
	avr-gdb -x gdbinit -w build/${TARGET}
