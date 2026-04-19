#include <stdint.h>
#include "adxl345.h"

char data;

uint8_t data_reg[6];
void adxl_read_address(uint8_t reg)
{
	I2C1_byteRead (DEVICE_ADDR, reg, &data);
}

void adxl_write(uint8_t reg, char value)
{
	char data[1];
	data[0] = value;

	I2C1_burstWrite(DEVICE_ADDR, reg,1, data);
}

void adxl_read_values(uint8_t reg)
{
	I2C1_burstRead(DEVICE_ADDR,reg, 6, (char*) data_reg);

}

void adxl_init(void)
{
	//enable I2C module
	I2C1_init();

	//read the DVID, this should return 0xE5
	adxl_read_address(DEV_ID_R);

	//set the data format range +-4g
	adxl_write(DATA_FORMAT , FOUR_G);

	//reset all bits
	adxl_write(POWER_CTL , RESET_V);

	//set the power control measure bit
	adxl_write(POWER_CTL ,SET_MEASURE_B);



}
