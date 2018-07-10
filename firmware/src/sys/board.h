/*
 * Copyright (c) 2014 Zubax, zubax.com
 * Distributed under the MIT License, available in the file LICENSE.
 * Author: Pavel Kirienko <pavel.kirienko@zubax.com>
 */

#pragma once

#define STM32_HSECLK            25000000

#define STM32F10X_CL


#define DEBUG_BUILD 1



/*
 * GPIO
 */
// Misc
#define GPIO_PORT_SERIAL_RX     GPIOD
#define GPIO_PIN_SERIAL_RX      6

// LED
#define GPIO_PORT_LED_STATUS    GPIOE
#define GPIO_PIN_LED_STATUS     13

#define GPIO_PORT_LED_CAN1      GPIOE
#define GPIO_PIN_LED_CAN1       15

#define GPIO_PORT_LED_CAN2      GPIOE
#define GPIO_PIN_LED_CAN2       14


/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*#define VAL_GPIOACRL            0x88888B88      // 7..0
#define VAL_GPIOACRH            0x888488b3      // 15..8
#define VAL_GPIOAODR            0x00000000

#define VAL_GPIOBCRL            0x88888882
#define VAL_GPIOBCRH            0x8848FF88
#define VAL_GPIOBODR            0x00000000

#define VAL_GPIOCCRL            0x88228888
#define VAL_GPIOCCRH            0x88888888
#define VAL_GPIOCODR            0x00000000

#define VAL_GPIODCRL            0x88888888
#define VAL_GPIODCRH            0x88888888
#define VAL_GPIODODR            0x00000000

#define VAL_GPIOECRL            0x88888888
#define VAL_GPIOECRH            0x88888888
#define VAL_GPIOEODR            0x00000000 */

#define VAL_GPIOACRL            0x88888888                      // 7..0
#define VAL_GPIOACRH            0x88800888                      // 15..8
#define VAL_GPIOAODR            0xFFFFFFFF                      // SWDIO and chip select pull up

#define VAL_GPIOBCRL            0x88222888
#define VAL_GPIOBCRH            0x88488A48
#define VAL_GPIOBODR            0xFFFFFFFF

#define VAL_GPIOCCRL            0x88888888
#define VAL_GPIOCCRH            0x88888888
#define VAL_GPIOCODR            0xFFFFFFFF

#define VAL_GPIODCRL            0x88888888                      //串口2 的PD5、PD6 
#define VAL_GPIODCRH            0x88888888
#define VAL_GPIODODR            0xFFFFFFFF

#define VAL_GPIOECRL            0x88888888
#define VAL_GPIOECRH            0x88888888
#define VAL_GPIOEODR            0x00000000



#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */
