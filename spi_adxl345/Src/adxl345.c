#include <stdint.h>
#include "adxl345.h"

#define MULTI_BYTE_EN  0x40
#define READ_OPERATION 0x80
char data;

//uint8_t rxdata[6];
void adxl_read(uint8_t address,uint8_t *rxdata)
{


	//set read operation
	address |= READ_OPERATION;

	//enable multibyte, place address into buffer
	address |= MULTI_BYTE_EN;

	//pull cs line low to enable slave
	cs_enable();

	//set address
	spi1_transmit(&address, 1);

	//read 6 bytes
	spi1_receive(rxdata,6);

	//pull cs line high to disable slave
	cs_disable();




}

void adxl_write(uint8_t address, char value)
{
	uint8_t data[2];

	//enable multibyte, place address into buffer
	data[0] = address | MULTI_BYTE_EN;

	//place the data into buffer
	data[1] = value;

	//pull cs line low to enable slave
	cs_enable();

	//transmit data and address
	spi1_transmit(data, 2);

	//pull cs line high to disable slave
	cs_disable();



}



void adxl_init(void)
{
	//enable SPI gpio
	spi_gpio_init();

	//enable SPI config
	spi1_config();

	//set the data format range +-4g
	adxl_write(DATA_FORMAT , FOUR_G);

	//reset all bits
	adxl_write(POWER_CTL , RESET_V);

	//set the power control measure bit
	adxl_write(POWER_CTL ,SET_MEASURE_B);



}
