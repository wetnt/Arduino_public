/*
  seeed_unified_library_interface.h
  Seeed Unified Library Interface for Arduino
  
  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2014-3-7 - Create File
  2014-3-11 - I2C test ok
  2014-3-14 - UART test ok
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __SEEED_UNIFIED_LIBRARY_INTERFACE_H__
#define __SEEED_UNIFIED_LIBRARY_INTERFACE_H__

#include <Arduino.h>

/**
 * GPIO TYPE, it means the data type you gpio name, 
 * such as, for Arduino, we use pinMode(pin, INPUT), and pin is int. 
 * but for mbed, it's gpio_t
 * For porting, you should modify here
 */
typedef     int     IO_T;                           // IO type
typedef     int     PIN_T;                          // pin name
typedef     int     DIR_T;                          // pin direction

typedef int ANALOG_T;                               // pin analog


/** 
 * PIN MODE
 * INPUT or OUTPUT
 */
#define HAL_PIN_INPUT   INPUT                       // INPUT and OUTPUT was declared in Arduino IDE
#define HAL_PIN_OUTPUT  OUTPUT


/**
 * PIN STATE
 * HIGH or LOW
 */
#define HAL_PIN_HIGH    HIGH                        // HIGH and LOW was declered in Arduino IDE
#define HAL_PIN_LOW     LOW


/**
 * DATA TYPE
 * ALL our suly-compatible library will will those data type
 */
typedef signed char     int8;
typedef unsigned char   uint8;
typedef signed short    int16;
typedef unsigned short  uint16;
typedef signed long     int32;
typedef unsigned long   uint32;



// UART

/*
 * uart init
 */
void suli_uart_init(void * uart_device, int16 uart_num, uint32 baud);


/*
 * send a buff to uart
 */
void uart_send(void * uart_device, uint8 *data);
void uart_send(void * uart_device, const __FlashStringHelper *data);


/*
 * read a byte from uart
 */
uint8 suli_uart_read_byte(void * uart_device, int16 uart_num);


/*
 * if uart get data, return 1-readable, 0-unreadable
 */
uint16 suli_uart_readable(void * uart_device, int16 uart_num);



#endif
