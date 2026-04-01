#include "exti.h"

#define GPIOAEN (1U<<0)
#define SYSCONFIGEN (1U<<14)


void pa0_exti_init(void)
{
	//disable global interrupt
	__disable_irq();

	//enable clock access for GPIOC
	RCC->AHB1ENR |= GPIOAEN;

	//set PA0 as input pin
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);

	//enable clock access to SYSCFG
	RCC->APB2ENR |= SYSCONFIGEN;

	//select PORTC FOR EXTI0
	SYSCFG->EXTICR[0] &= ~(1U<<0);
	SYSCFG->EXTICR[0] &= ~(1U<<0);
	SYSCFG->EXTICR[0] &= ~(1U<<0);
	SYSCFG->EXTICR[0] &= ~(1U<<0);


	//unmask EXTI0
	EXTI->IMR |= (1U<<0);

	//select falling edge trigger
	EXTI->FTSR |= (1U<<0);

	//enable EXTI0 line in NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);

	//enable global interrupt
	__enable_irq();
}
