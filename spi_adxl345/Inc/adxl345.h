/*
 * adxl345.h
 *
 *  Created on: Apr 5, 2026
 *      Author: a00591431
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "spi.h"

#define DEVICE_ADDR      (0x53)
#define DEV_ID_R          (0x00)
#define POWER_CTL        (0x2D)
#define DATA_FORMAT      (0x31)
#define DATA_START_ADDR  (0X32)

#define FOUR_G         (0X01)
#define RESET_V        (0X00)
#define SET_MEASURE_B  (0X08)

void adxl_init(void);
void adxl_write(uint8_t address, char value);
void adxl_read(uint8_t address,uint8_t *rxdata);




#endif /* ADXL345_H_ */
