/*
 * Copyright (c) 2015, Zolertia - http://www.zolertia.com
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
/*---------------------------------------------------------------------------*/
/**
 * \addtogroup zoul-examples
 * @{
 *
 * \defgroup zoul-bmpx8x-test BMP085/BMP180 pressure and temperature sensor test
 *
 * Demonstrates the use of the BMP085/BMP180 pressure and temperature sensor
 * @{
 *
 * \file
 *         Test file for the BMP085/BMP180 digital pressure and temp sensor
 *
 * \author
 *         Antonio Lignan <alinan@zolertia.com>
 */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include "contiki.h"
#include "dev/i2c.h"
#include "dev/leds.h"
#include "dev/gpio.h"
#include "si7021.h"
#include "math.h"
/*---------------------------------------------------------------------------*/
#define SENSOR_READ_INTERVAL (3 * CLOCK_SECOND)
/*---------------------------------------------------------------------------*/
PROCESS(remote_bmpx8x_process, "BMP085/BMP180 test process");
AUTOSTART_PROCESSES(&remote_bmpx8x_process);
/*---------------------------------------------------------------------------*/
static struct etimer et;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_bmpx8x_process, ev, data)
{

  PROCESS_BEGIN();
  si7021_config();
  /* And periodically poll the sensor */
  uint16_t temp, rh;

  while(1) {
    etimer_set(&et, SENSOR_READ_INTERVAL);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		temp = si7021_readTemp(TEMP_NOHOLD);
    rh = si7021_readHumd(RH_NOHOLD);
    float temp1 = (float) temp * 1.00;
    float hum = (float) rh * 1.00;
    float t = (float) (temp1 * 175.75) / 65536.0 - 46.85;
    float h = (float) (hum * 125) / 65536.0 - 6.0;
    printf("temp: %ld.%2u, rh: %ld.%2u\n", (long)t,
    (unsigned)((t-floor(t))*100), (long)h,
    (unsigned)((h-floor(h))*100));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 */

