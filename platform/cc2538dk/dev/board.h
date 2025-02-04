/*
 * Copyright (c) 2012, Texas Instruments Incorporated - http://www.ti.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \addtogroup cc2538dk
 * @{
 *
 * \defgroup cc2538-smartrf SmartRF06EB Peripherals
 *
 * Defines related to the SmartRF06EB
 *
 * This file provides connectivity information on LEDs, Buttons, UART and
 * other SmartRF peripherals
 *
 * Notably, PC0 is used to drive LED1 as well as the USB D+ pullup. Therefore
 * when USB is enabled, LED1 can not be driven by firmware.
 *
 * This file can be used as the basis to configure other platforms using the
 * cc2538 SoC.
 * @{
 *
 * \file
 * Header file with definitions related to the I/O connections on the TI
 * SmartRF06EB
 *
 * \note   Do not include this file directly. It gets included by contiki-conf
 *         after all relevant directives have been set.
 */
#ifndef BOARD_H_
#define BOARD_H_

#include "dev/gpio.h"
#include "dev/nvic.h"
/*---------------------------------------------------------------------------*/
/** \name SmartRF LED configuration
 *
 * LEDs on the SmartRF06 (EB and BB) are connected as follows:
 * - LED1 (Red)    -> PC0
 * - LED2 (Yellow) -> PC1
 * - LED3 (Green)  -> PC2
 * - LED4 (Orange) -> PC3
 *
 * LED1 shares the same pin with the USB pullup
 * @{
 */
/*---------------------------------------------------------------------------*/
/* Some files include leds.h before us, so we need to get rid of defaults in
 * leds.h before we provide correct definitions */
#undef LEDS_GREEN
#undef LEDS_YELLOW
#undef LEDS_RED
#undef LEDS_CONF_ALL

#define LEDS_YELLOW             2 /**< LED2 (Yellow) -> PC1 */
#define LEDS_GREEN              4 /**< LED3 (Green)  -> PC2 */
#define LEDS_ORANGE             8 /**< LED4 (Orange) -> PC3 */

#if USB_SERIAL_CONF_ENABLE
#define LEDS_CONF_ALL           14
#define LEDS_RED                LEDS_ORANGE
#else
#define LEDS_CONF_ALL           15
#define LEDS_RED                1 /**< LED1 (Red)    -> PC0 */
#endif

/* Notify various examples that we have LEDs */
#define PLATFORM_HAS_LEDS       1
/** @} */
/*---------------------------------------------------------------------------*/
/** \name USB configuration
 *
 * The USB pullup is driven by PC0 and is shared with LED1
 */
#define USB_PULLUP_PORT         GPIO_C_NUM
#define USB_PULLUP_PIN          0
/** @} */
/*---------------------------------------------------------------------------*/
/** \name UART configuration
 *
 * On the SmartRF06EB, the UART (XDS back channel) is connected to the
 * following ports/pins
 * - RX:  PA0
 * - TX:  PA1
 * - CTS: PB0 (Can only be used with UART1)
 * - RTS: PD3 (Can only be used with UART1)
 *
 * We configure the port to use UART0. To use UART1, replace UART0_* with
 * UART1_* below.
 * @{
 */
#define UART0_RX_PORT           GPIO_A_NUM
#define UART0_RX_PIN            0

#define UART0_TX_PORT           GPIO_A_NUM
#define UART0_TX_PIN            1

#define UART1_CTS_PORT          GPIO_B_NUM
#define UART1_CTS_PIN           0

#define UART1_RTS_PORT          GPIO_D_NUM
#define UART1_RTS_PIN           3
/** @} */
/*---------------------------------------------------------------------------*/
/** \name SmartRF Button configuration
 *
 * Buttons on the SmartRF06 are connected as follows:
 * - BUTTON_SELECT -> PA3
 * - BUTTON_LEFT -> PC4
 * - BUTTON_RIGHT -> PC5
 * - BUTTON_UP -> PC6
 * - BUTTON_DOWN -> PC7
 * @{
 */
/** BUTTON_SELECT -> PA3 */
#define BUTTON_SELECT_PORT      GPIO_A_NUM
#define BUTTON_SELECT_PIN       3
#define BUTTON_SELECT_VECTOR    GPIO_A_IRQn

/** BUTTON_LEFT -> PC4 */
#define BUTTON_LEFT_PORT        GPIO_C_NUM
#define BUTTON_LEFT_PIN         4
#define BUTTON_LEFT_VECTOR      GPIO_C_IRQn

/** BUTTON_RIGHT -> PC5 */
#define BUTTON_RIGHT_PORT       GPIO_C_NUM
#define BUTTON_RIGHT_PIN        5
#define BUTTON_RIGHT_VECTOR     GPIO_C_IRQn

/** BUTTON_UP -> PC6 */
#define BUTTON_UP_PORT          GPIO_C_NUM
#define BUTTON_UP_PIN           6
#define BUTTON_UP_VECTOR        GPIO_C_IRQn

/** BUTTON_DOWN -> PC7 */
#define BUTTON_DOWN_PORT        GPIO_C_NUM
#define BUTTON_DOWN_PIN         7
#define BUTTON_DOWN_VECTOR      GPIO_C_IRQn

/* Notify various examples that we have Buttons */
#define PLATFORM_HAS_BUTTON     1
/** @} */
/*------I2C--------*/

#define I2C_SDA_PORT GPIO_A_NUM
#define I2C_SDA_PIN  6

#define I2C_SCL_PORT GPIO_A_NUM
#define I2C_SCL_PIN 5

#define I2C_INT_PORT             GPIO_C_NUM
#define I2C_INT_PIN              7
#define I2C_INT_VECTOR GPIO_C_IRQn

#define HW_INT_OVER_THRS                              0x01
#define HW_INT_BELOW_THRS                             0x02
#define HW_INT_DISABLE                                0x03
/*---------------------------------------------------------------------------*/
/**
 * \name ADC configuration
 *
 * These values configure which CC2538 pins and ADC channels to use for the ADC
 * inputs.
 *
 * ADC inputs can only be on port A.
 * @{
 */
#define ADC_ALS_PWR_PORT        GPIO_A_NUM /**< ALS power GPIO control port */
#define ADC_ALS_PWR_PIN         7 /**< ALS power GPIO control pin */
#define ADC_ALS_OUT_PIN         6 /**< ALS output ADC input pin on port A */
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name SPI configuration
 *
 * These values configure which CC2538 pins to use for the SPI lines. Both
 * SPI instances can be used independently by providing the corresponding
 * port / pin macros.
 * @{
 */
#define SPI0_IN_USE             0
#define SPI1_IN_USE             0
#if SPI0_IN_USE
/** Clock port SPI0 */
#define SPI0_CLK_PORT           GPIO_A_NUM
/** Clock pin SPI0 */
#define SPI0_CLK_PIN            2
/** TX port SPI0 (master mode: MOSI) */
#define SPI0_TX_PORT            GPIO_A_NUM
/** TX pin SPI0 */
#define SPI0_TX_PIN             4
/** RX port SPI0 (master mode: MISO */
#define SPI0_RX_PORT            GPIO_A_NUM
/** RX pin SPI0 */
#define SPI0_RX_PIN             5
#endif  /* #if SPI0_IN_USE */
#if SPI1_IN_USE
/** Clock port SPI1 */
#define SPI1_CLK_PORT           GPIO_A_NUM
/** Clock pin SPI1 */
#define SPI1_CLK_PIN            2
/** TX port SPI1 (master mode: MOSI) */
#define SPI1_TX_PORT            GPIO_A_NUM
/** TX pin SPI1 */
#define SPI1_TX_PIN             4
/** RX port SPI1 (master mode: MISO) */
#define SPI1_RX_PORT            GPIO_A_NUM
/** RX pin SPI1 */
#define SPI1_RX_PIN             5
#endif  /* #if SPI1_IN_USE */
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Device string used on startup
 * @{
 */
#define BOARD_STRING "TI SmartRF06 + cc2538EM"
/** @} */

#endif /* BOARD_H_ */

/**
 * @}
 * @}
 */
