#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"


#define GPIODEN  (1U<<3)
#define GPIOD_12 (1U<<12)
#define LED_PIN  GPIOD_12


int main(void)
{
	//enable clock for GPIOA
	RCC->AHB1ENR |= GPIODEN;

	//set PD12 AS output pin
	GPIOD->MODER &=~(3U<<(2*12));//first clear all bits
	GPIOD->MODER |= (1U<<(2*12));//set for output mode




	 while(1)
	 {

		 GPIOD->ODR ^= LED_PIN;
		 systickDelay(1000);

	 }

}



