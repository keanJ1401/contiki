#include "contiki.h"
#include "cpu.h"
#include "sys/etimer.h"
#include "dev/leds.h"
#include "dev/i2c.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define MAX4409_ADDRESS 0x4A
static struct etimer et;
/*---------------------------------------------------------------------------*/
void max44009_init() {
  i2c_init(I2C_SDA_PORT, I2C_SDA_PIN, I2C_SCL_PORT, I2C_SCL_PIN,
           I2C_SCL_NORMAL_BUS_SPEED);
  uint8_t max_data[2] = {0x02, 0x40};
  i2c_burst_send(MAX4409_ADDRESS, max_data, 2);
}
uint32_t read_light() {
	uint8_t exponent, mantissa;
	uint8_t max44009_data[2];
	uint32_t result;	

	i2c_single_send(MAX4409_ADDRESS, 0x03);
	i2c_single_receive(ADDRESS, &max44009_data[0]);
	i2c_single_send(MAX4409_ADDRESS, 0x04);
	i2c_single_receive(MAX4409_ADDRESS, &max44009_data[1]);

	exponent = (max44009_data[0] >> 4);
	mantissa = ((max44009_data[0] & 0x0F) << 4) | (max44009_data[1] & 0x0F);
	result = pow(2, exponent) * mantissa * 45;
	return result;	
}
PROCESS(max44009_demo_prcess, "MAX44009 Demo - Light Sensor");
AUTOSTART_PROCESSES(&max44009_demo_prcess);


PROCESS_THREAD(max44009_demo_prcess, ev, data)
{

  uint32_t light;
  PROCESS_BEGIN();
max44009_init();
  while(1) {
    etimer_set(&et, 2*CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(ev==PROCESS_EVENT_TIMER);

	//printf("Light: %lu.%2ld lux", luminiance/1000, luminiance%1000);
        light = read_light();
        printf("Light: %lu.%lulux\n", light / 1000, light % 1000);
	etimer_reset(&et);

  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 * @}
 */
