/*
 * Header file for DHT11 driver.
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

#ifndef DHT11_H
#define DHT11_H

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DHT11 result of conversion */
typedef enum {
  DHT11_RESULT_SUCCESS = 0, /* correct conversion */
  DHT11_RESULT_BAD_MEASURE, /* not all bits have been acquired */
  DHT11_RESULT_BAD_PARITY   /* parity check over all bits is wrong */
} DHT11_RESULT;

/* struct that holds DHT11 conversion values */
typedef struct {
  FLOAT RH; /* relative humidity */
  FLOAT T;  /* temperature */
} DHT11_DATA;

/* Description:
 *  the function dht11GetData reads humidity and temperature data from DHT11 sensor
 *  
 * Parameters:
 *  dht11Gpio: GPIO where DHT11 sensor is connected
 *  ptrData: pointer to struct DHT11_DATA where conversion result is written
 *  
 * Return value:
 *  refer to DHT11_RESULT enum
 */
DHT11_RESULT dht11GetData(UINT8 dht11Gpio, DHT11_DATA *ptrData);

#ifdef __cplusplus
}
#endif
#endif /* DHT11_H */
