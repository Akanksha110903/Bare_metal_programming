#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

static void systick_callback(void);

#define GPIODEN  (1U<<3)
#define GPIOD_13 (1U<<13)
#define LED_PIN  GPIOD_13


int main(void)
{
	//enable clock for GPIOA
	RCC->AHB1ENR |= GPIODEN;

	//set PD12 AS output pin
	GPIOD->MODER &=~(3U<<(2*13));//first clear all bits
	GPIOD->MODER |= (1U<<(2*13));//set for output mode

	systick_1hz_interrupt();


	 while(1)
	 {



	 }

}

static void systick_callback(void)
{

	GPIOD->ODR ^= LED_PIN;

}

void SysTick_Handler(void)
{
	//do something
	systick_callback();
}



