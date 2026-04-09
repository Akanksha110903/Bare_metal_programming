#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

static void tim2_callback(void);

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

	tim2_1hz_interrupt_init();




	 while(1)
	 {


	 }

}
static void tim2_callback(void)
{
	GPIOD->ODR ^= LED_PIN;
}

void TIM2_IRQHandler(void)
{
	//clear update interrupt flag (UIF)
	TIM2->SR &=~SR_UIF;

	//do something
	tim2_callback();
}



