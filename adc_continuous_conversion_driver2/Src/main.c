#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

//PA1 for adc
//PD5 FOR TX
//PD6 FOR RX
uint32_t sensor_value;

int main(void)
{
	uart2_rx_tx_init();
	PA1_adc_init();
	start_conversion();


	 while(1)
	 {

		 sensor_value = adc_read();
		 uart2_write(sensor_value);

	 }

}



