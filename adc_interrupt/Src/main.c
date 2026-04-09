#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

static void adc_callback(void);
//PA1 for adc
//PD5 FOR TX
//PD6 FOR RX
uint32_t sensor_value;

int main(void)
{
	uart2_rx_tx_init();
	PA1_adc_interrupt_init();
	start_conversion();


	 while(1)
	 {



	 }

}
static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	uart2_write(sensor_value);

}

void ADC_IRQHandler(void)
{
	//check for eoc in SR
	if((ADC1->SR & SR_EOC)!=0);

	//clear eoc flag
	ADC1->SR &=~SR_EOC;

	//Do something
	adc_callback();
}



