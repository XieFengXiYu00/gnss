/*
 * Copyright (c) 2014 Zubax, zubax.com
 * Distributed under the MIT License, available in the file LICENSE.
 * Author: Pavel Kirienko <pavel.kirienko@zubax.com>
 */

#pragma once

/*#if !DEBUG_BUILD && !RELEASE_BUILD
#  error Either DEBUG_BUILD or RELEASE_BUILD must be defined
#endif*/

#include <zubax_chibios/sys/assert_always.h>
#include <ch.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * NuttX-like console print; should be used instead of printf()/chprintf()
 * TODO: use type safe version for C++.
 */
__attribute__ ((format (printf, 1, 2)))
void lowsyslog(const char* format, ...);

/**
 * Changes current stdout stream.
 */
void sysSetStdOutStream(BaseSequentialStream* stream);

/**
 * Emergency termination hook that can be overriden by the application.
 */
extern void sysApplicationHaltHook(void);

/**
 * Replacement for chThdSleepUntil() that accepts timestamps from the past.
 * http://sourceforge.net/p/chibios/bugs/292/#ec7c
 */
void sysSleepUntilChTime(systime_t sleep_until);

__attribute__((noreturn))
void sysPanic(const char* msg);

#ifdef __cplusplus
}
#endif
