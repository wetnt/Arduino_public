/*
  seeed_unified_library_interface.cpp
  Seeed Unified Library Interface for Arduino Only
  
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2012-3-7 - Create File
  2013-3-11 - I2C test ok
  2013-3-14 - UART test ok

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

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Suli.h"



/*
 * UART Init
 * - uart_device: uart device pointer
 * - uart_num: for some MCU, there's more than one uart, this is the number of uart
 *   for Arduino-UNO(or others use 328, 32u4, 168), these is a hardware uart and software uart.
 *   uart_num = -1 - Software Serial
 *   uart_num = 0, uart0
 *   uart_num = 1, uart1, Arduino Mega Only
 *   uart_num = 2, uart2, Arduino Mega Only
 *   uart_num = 3, uart3, Arduino Mega Only
 * - baud： baudrate
 */
void suli_uart_init(void * uart_device, int16 uart_num, uint32 baud){
    ((SoftwareSerial *)uart_device) -> begin(baud);
}


void uart_send(void * uart_device, const __FlashStringHelper  *data)
{
	((SoftwareSerial *)uart_device) -> print(data);
}
void uart_send(void * uart_device, uint8 *data)
{
	((SoftwareSerial *)uart_device) -> print((const char*)data);
}


/*
 * read a byte from uart
 */
uint8 suli_uart_read_byte(void * uart_device, int16 uart_num) {
    return ((SoftwareSerial *)uart_device) -> read();
}


/*
 * if uart get data, return 1-readable, 0-unreadable
 */
uint16 suli_uart_readable(void * uart_device, int16 uart_num){
    return ((SoftwareSerial *)uart_device) -> available();
}

