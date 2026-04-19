#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

static void dma_callback(void);

#define GPIODEN     (1U<<3)
#define PIN12       (1U<<12)
#define LED_GREEN    PIN12




int main(void)
{
	char message[20]="hello there";
	RCC->AHB1ENR |= GPIODEN;
	//set pin 12 as output mode
	GPIOD->MODER &= ~(3U<<(2*12));
	GPIOD->MODER |= (1U<<(2*12));
	uart2_rx_tx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 20);

	while(1)
	{

	}
}




void delay(void)
{
    for(int i=0;i<50000;i++);
}


static void dma_callback(void)
{
	GPIOD->ODR ^= LED_GREEN;


}

void DMA1_Stream6_IRQHandler(void)
{
	//Check for transfer complete interrupt
	if(DMA1->HISR & HISR_TCIF6)
	{
		//Clear flag
		DMA1->HIFCR |= HIFCR_CTCIF6;

		//do something
		dma_callback();
	}
}


