#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIODEN     (1U<<3)
#define PIN12       (1U<<12)
#define LED_GREEN    PIN12

void delay(void);
char key;


int main(void)
{
	RCC->AHB1ENR |= GPIODEN;
	//set pin 12 as output mode
	GPIOD->MODER &= ~(3U<<(2*12));
	GPIOD->MODER |= (1U<<(2*12));

	 uart2_rx_interrupt_init();

	while(1)
	{

	}
}




void delay(void)
{
    for(int i=0;i<50000;i++);
}


static void uart_callback(void)
{
	key = USART2->DR;//RED THE DATA
			if(key =='l')
			{
				GPIOD->ODR |=  LED_GREEN;
			}else
			{
				GPIOD->ODR &= ~(LED_GREEN);
			}

}



void USART2_IRQHandler(void)
{
	//check if RXNE is set
	if(USART2->SR & SR_RXNE)
	{
		//do something
		uart_callback();

	}
}
