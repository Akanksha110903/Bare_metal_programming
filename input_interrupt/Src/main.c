#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"
#include "exti.h"

#define GPIODEN (1U<<3) //enable clock for PORTD (0b 0000 0000 0000 0000 0000 0000 0000 1000)

#define PIN12                (1U<<12)
#define LED_GREEN            PIN12

static void exti_callback(void);


//press the user button to see the led toggle
int main(void)
{
	RCC->AHB1ENR |=GPIODEN;


	//clean all the bit
	GPIOD->MODER &= ~((3U<<(2*12)));

	//set pins as output
	GPIOD->MODER |= ((1U<<(2*12)));
	 pa0_exti_init();




	 while(1)
	 {


	 }

}

static void exti_callback(void)
{
	GPIOD->ODR ^=  LED_GREEN;
}
void EXTI0_IRQHandler(void)
{
	if((EXTI->PR & LINE_0)!=0)
	{
		//Clear PR flag
		EXTI->PR |= LINE_0;

		//do something....
		exti_callback();
	}
}



