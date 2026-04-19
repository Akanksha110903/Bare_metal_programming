#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adxl345.h"

int16_t x,y,z;
float xg,yg,zg;
uint8_t rxdata[6];

int main(void)
{
	 adxl_init();

	while(1)
	{
		adxl_read(DATA_START_ADDR,rxdata);

		x = ((rxdata[1]<<8) | rxdata[0]);
		y = ((rxdata[3]<<8) | rxdata[2]);
		z = ((rxdata[5]<<8) | rxdata[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);

	}
}





