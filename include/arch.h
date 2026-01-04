/**
 * @file arch.h
 * @brief Architecture-specific definitions.
 * @details This file contains definitions and configurations specific to the
 * target architecture, such as microcontroller registers, clock settings, and
 * other hardware-related parameters.
 */

#ifndef __ARCH_H__
#define __ARCH_H__

#include <stdint.h>

#ifdef __INTELLISENSE__
#define __AVR_AT90USB647__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/builtins.h>
#include <avr/cpufunc.h>
#include <avr/signature.h>

#include "bsp.h"

#endif /* __ARCH_H__ */
