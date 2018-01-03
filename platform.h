/*
 * Platform dependent data types and functions for DHT11 driver.
 * The driver code is easily portable to any platform which supports the functions below.
 * Here is given an example for Arduino Uno board: if you wish to reuse the code on another
 * system you only need to reassign the definitions of this file.
 * 
 * Copyright (C) 2018  Nicola Simoni <nikfloydrose@hotmail.it>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include "Arduino.h"

/* data types */
#define UINT8 unsigned char
#define UINT16 unsigned int
#define UINT32 unsigned long
#define FLOAT float

/* time functions */
#define GET_MICROSECONDS() micros() /* get time from the system in microseconds */
#define GET_MILLISECONDS() millis() /* get time from the system in milliseconds */
#define DELAY_MS(ms) delay(ms)  /* delay milliseconds */

/* interrupt configuration */
#define ATTACH_INTERRUPT(pin, ISR, mode) attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
#define DETACH_INTERRUPT(pin) detachInterrupt(digitalPinToInterrupt(pin))
#define FALLING_EDGE FALLING /* trigger the interrupt on the falling edge of the input signal */

/* GPIO configuration */
#define GPIO_MODE(pin, mode) pinMode(pin, mode)
#define GPIO_WRITE(pin, value) digitalWrite(pin, value)
#define GPIO_OUT OUTPUT
#define GPIO_IN_PULLUP INPUT_PULLUP
#define GPIO_LOW LOW
#define GPIO_HIGH HIGH

#endif /* PLATFORM_H */
