/*
 * Test code for DHT11 driver on Arduino Uno board.
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

#include "dht11.h"

#define DHT_GPIO 2  /* DHT11 sensor attached to GPIO 2 of Arduino Uno */
String outMessage;
DHT11_DATA dht11Data;
DHT11_RESULT ret;

void setup()
{
  Serial.begin(9600);
  outMessage.reserve(30);
}
 
void loop()
{
  /* get data from DHT11 sensor */
  ret = dht11GetData(DHT_GPIO, &dht11Data);

  /* print result */
  switch(ret)
  {   
    case DHT11_RESULT_SUCCESS:
      outMessage = "RH = " + String(dht11Data.RH) + " %\n" + "T = " + String(dht11Data.T) + " °C\n";
      break;

    case DHT11_RESULT_BAD_MEASURE:
      outMessage = "Bad measure!";
      break;

    case DHT11_RESULT_BAD_PARITY:
      outMessage = "Bad parity check!"; 
      break;

    default:
      outMessage = "Generic error."; 
  }
  Serial.println(outMessage);
}
