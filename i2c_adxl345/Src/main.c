#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adxl345.h"

int16_t x,y,z;
float xg,yg,zg;


extern uint8_t data_reg[6];

int main(void)
{
	 adxl_init();

	while(1)
	{
		adxl_read_values(DATA_START_ADDR);

		x = ((data_reg[1]<<8) | data_reg[0]);
		y = ((data_reg[3]<<8) | data_reg[2]);
		z = ((data_reg[5]<<8) | data_reg[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);

	}
}





