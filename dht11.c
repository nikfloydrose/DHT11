/*
 * Driver for DHT11 sensor.
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

#define START_DELAYMS 20
#define SAFE_DELAYMS 1500
#define THRESHOLD_US 100
#define TOTAL_BITS 41
#define NUM_BYTES 5
#define FALLING_EDGES (TOTAL_BITS + 1)  /* count also falling edge of start bit */

static volatile UINT32 timeVector[FALLING_EDGES];
static volatile UINT8 cntEdge;
static volatile UINT8 readyToMeasure;
static UINT16 timeVectorDelta[TOTAL_BITS];
static UINT32 startSampleT;
static UINT8 outBits[TOTAL_BITS - 1];
static UINT8 dataBytes[NUM_BYTES];
static UINT8 parityCheck;
static UINT8 cntBits;
static UINT8 i, j;

static void getSystemTimeUs(void)
{
  if(readyToMeasure)
    timeVector[cntEdge++] = GET_MICROSECONDS();
}

DHT11_RESULT dht11GetData(UINT8 dht11Gpio, DHT11_DATA *ptrData)
{ 
  /* wait for sensor adjustment before each measure */
  DELAY_MS(SAFE_DELAYMS);
  
  /* send start signal */
  GPIO_MODE(dht11Gpio, GPIO_OUT);
  GPIO_WRITE(dht11Gpio, GPIO_LOW);
  DELAY_MS(START_DELAYMS);
  GPIO_WRITE(dht11Gpio, GPIO_HIGH);
  GPIO_MODE(dht11Gpio, GPIO_IN_PULLUP);

  ATTACH_INTERRUPT(dht11Gpio, getSystemTimeUs, FALLING_EDGE);
  startSampleT = GET_MILLISECONDS();
  readyToMeasure = 1;
  cntEdge = 0;
    
  /* sample time on the falling edges of rx data */
  while((cntEdge < FALLING_EDGES) && ((GET_MILLISECONDS() - startSampleT) < SAFE_DELAYMS));
  
  readyToMeasure = 0;
  DETACH_INTERRUPT(dht11Gpio);

  /* check if all bits have been acquired */
  if(cntEdge != FALLING_EDGES)
  {
    return DHT11_RESULT_BAD_MEASURE;
  }
  
  /* compute delta times between falling edges */
  for(cntEdge = 0; cntEdge < FALLING_EDGES; cntEdge++)
  {
    timeVectorDelta[cntEdge] = timeVector[cntEdge + 1] - timeVector[cntEdge];
  }
 
  /* discriminate bit values */
  for(i = 0; i < TOTAL_BITS; i++)
  {
    outBits[i] = (timeVectorDelta[i + 1] < THRESHOLD_US) ? 0 : 1;
  }

  /* compute bytes values */
  cntBits = 0;

  for(i = 0; i < NUM_BYTES; i++)
  {
    dataBytes[i] = 0;
    
    for(j = 0; j < 8; j++)
    {
      dataBytes[i] += ((1 << (7 - j)) * outBits[cntBits++]);
    }
  }

  /* compute parity check */
  parityCheck = 0;
  
  for(i = 0; i < (NUM_BYTES - 1); i++)
  {
     parityCheck += dataBytes[i];
  }

  /* return results */
  if(parityCheck == dataBytes[NUM_BYTES - 1])
  {
    ptrData->RH = dataBytes[0] + ((FLOAT)dataBytes[1]) / 100;
    ptrData->T  = dataBytes[2] + ((FLOAT)dataBytes[3]) / 100;
    return DHT11_RESULT_SUCCESS;
  }
  else
  {
    return DHT11_RESULT_BAD_PARITY;
  }
}
