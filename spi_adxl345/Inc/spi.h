/*
 * spi.h
 *
 *  Created on: Apr 6, 2026
 *      Author: a00591431
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"

void spi_gpio_init(void);
void spi1_config(void);
void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif /* SPI_H_ */
