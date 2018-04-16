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
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;
typedef float FLOAT;

/* time functions */
#define GET_MICROSECONDS() micros() /* get time from the system in microseconds */
#define GET_MILLISECONDS() millis() /* get time from the system in milliseconds */
#define DELAY_MS(ms) delay(ms)  /* delay milliseconds */

/* interrupt configuration */
#define ATTACH_INTERRUPT(pin, ISR, mode) attachInterrupt(digitalPinToInterrupt(pin), ISR, mode) /* attach interrupt on GPIO pin, with ISR function and mode trigger method */
#define DETACH_INTERRUPT(pin) detachInterrupt(digitalPinToInterrupt(pin)) /* detach interrupt from GPIO pin */
#define FALLING_EDGE FALLING /* mode parameter of ATTACH_INTERRUPT: trigger the interrupt on the falling edge of the input signal */

/* GPIO configuration */
#define GPIO_MODE(pin, mode) pinMode(pin, mode) /* set GPIO pin mode (output or input pullup) */
#define GPIO_WRITE(pin, value) digitalWrite(pin, value) /* set GPIO pin state (low or high) */
#define GPIO_OUT OUTPUT /* mode parameter of GPIO_MODE */
#define GPIO_IN_PULLUP INPUT_PULLUP /* mode parameter of GPIO_MODE */
#define GPIO_LOW LOW /* value parameter of GPIO_MODE */
#define GPIO_HIGH HIGH /* value parameter of GPIO_MODE */

#endif /* PLATFORM_H */
