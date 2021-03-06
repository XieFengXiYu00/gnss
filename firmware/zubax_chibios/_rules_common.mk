#
# Copyright (c) 2014 Zubax, zubax.com
# Distributed under the MIT License, available in the file LICENSE.
# Author: Pavel Kirienko <pavel.kirienko@zubax.com>
#

ZUBAX_CHIBIOS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

CSRC += $(ZUBAX_CHIBIOS_DIR)/zubax_chibios/sys/sys_console.c                    \
        $(ZUBAX_CHIBIOS_DIR)/zubax_chibios/sys/sys.c

CPPSRC += $(ZUBAX_CHIBIOS_DIR)/zubax_chibios/sys/libstdcpp.cpp

UINCDIR += $(ZUBAX_CHIBIOS_DIR)

UDEFS +=

#
# OS configuration
#

ifndef SERIAL_CLI_PORT_NUMBER
    $(error SERIAL_CLI_PORT_NUMBER must be assigned an integer value greater than zero)
endif

UDEFS += -DSTDOUT_SD=SD$(SERIAL_CLI_PORT_NUMBER) -DSTDIN_SD=STDOUT_SD -DSERIAL_CLI_PORT_NUMBER=$(SERIAL_CLI_PORT_NUMBER)

UDEFS += -DCORTEX_ENABLE_WFI_IDLE=1 -DCHPRINTF_USE_FLOAT=1

USE_LINK_GC = yes
USE_THUMB ?= yes
USE_VERBOSE_COMPILE ?= no
USE_FWLIB ?= no

CHIBIOS := $(ZUBAX_CHIBIOS_DIR)/chibios
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/kernel/kernel.mk
include $(CHIBIOS)/os/various/cpp_wrappers/kernel.mk


VARIOUSSRC = $(CHIBIOS)/os/various/syscalls.c    \
             $(CHIBIOS)/os/various/chprintf.c    \
             $(CHIBIOS)/os/various/shell.c       \
             $(CHIBIOS)/os/various/memstreams.c

CSRC += $(PORTSRC) $(KERNSRC) $(HALSRC) $(PLATFORMSRC) $(VARIOUSSRC)

CPPSRC += $(CHCPPSRC)

ASMSRC += $(PORTASM)

INCDIR += $(PORTINC) $(KERNINC) $(HALINC) $(PLATFORMINC) $(CHCPPINC) $(CHIBIOS)/os/various

#
# Build configuration
#

NO_BUILTIN += -fno-builtin-printf -fno-builtin-fprintf  -fno-builtin-vprintf -fno-builtin-vfprintf -fno-builtin-puts

USE_OPT += -falign-functions=16 -U__STRICT_ANSI__ -fno-exceptions -fno-unwind-tables -fno-stack-protector \
           $(NO_BUILTIN) -fconserve-stack

# Explicit usage flags are needed for LTO:
USE_OPT += -u_port_lock -u_port_unlock -u_exit -u_kill -u_getpid -uchThdExit

USE_COPT += -std=c99
USE_CPPOPT += -std=c++11 -fno-rtti -fno-exceptions -fno-threadsafe-statics

USE_OPT += -nodefaultlibs -lc -lgcc -lm

RELEASE ?= 0
RELEASE_OPT ?= -O1 -fomit-frame-pointer
DEBUG_OPT ?= -O1 -g3
ifneq ($(RELEASE),0)
    DDEFS += -DRELEASE_BUILD=1 -DNDEBUG=1
    USE_OPT += $(RELEASE_OPT)
else
    DDEFS += -DDEBUG_BUILD=1
    USE_OPT += $(DEBUG_OPT)
endif

#
# Compiler options
#

MCU  = cortex-m3

TOOLCHAIN_PREFIX ?= arm-none-eabi
CC   = $(TOOLCHAIN_PREFIX)-gcc
CPPC = $(TOOLCHAIN_PREFIX)-g++
LD   = $(TOOLCHAIN_PREFIX)-g++
CP   = $(TOOLCHAIN_PREFIX)-objcopy
AS   = $(TOOLCHAIN_PREFIX)-gcc -x assembler-with-cpp
OD   = $(TOOLCHAIN_PREFIX)-objdump
SZ   = $(TOOLCHAIN_PREFIX)-size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT +=

# THUMB-specific options here
TOPT ?= -mthumb -DTHUMB=1

CWARN += -Wall -Wextra -Wstrict-prototypes
CPPWARN += -Wall -Wextra -Werror

# asm statement fix
DDEFS += -Dasm=__asm

include $(CHIBIOS)/os/ports/GCC/ARMCMx/rules.mk
