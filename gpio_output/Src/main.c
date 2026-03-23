#include "stm32f4xx.h"

#define GPIODEN (1U<<3) //enable clock for PORTD (0b 0000 0000 0000 0000 0000 0000 0000 1000)

#define PIN12                (1U<<12)
#define PIN13                (1U<<13)
#define PIN14                (1U<<14)
#define PIN15                (1U<<15)

#define LED_RED              PIN14
#define LED_GREEN            PIN12
#define LED_BLUE             PIN15
#define LED_ORANGE           PIN13





int main(void)
{
	RCC->AHB1ENR |=GPIODEN;


	//clean all the bit
	GPIOD->MODER &= ~((3U<<(2*12)) | (3U<<(2*13)) | (3U<<(2*14)) | (3U<<(2*15)));

	//set pins as output
	GPIOD->MODER |= ((1U<<(2*12)) | (1U<<(2*13)) | (1U<<(2*14)) |(1U<<(2*15)));

	while(1)
	{
		//TOGGLE LEDS
		GPIOD->ODR ^= (LED_RED | LED_GREEN | LED_BLUE | LED_ORANGE);
		for(int i=0;i<100000;i++){}

	}
}
