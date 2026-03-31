#include "stm32f4xx.h"

#define TIM2EN    (1U<<0)
#define CR1_CEN   (1U<<0)
#define OC_TOGGLE ((1U<<4) | (1U<<5))
#define CCER_CC1E (1U<<0)
#define GPIOAEN   (1U<<0)
#define AFR5_TIM  (1U<<20)


void tim2_1hz_init(void)
{
	//enable clock acces to timer 2
	RCC->APB1ENR |= TIM2EN;

	//set prescalar
	TIM2->PSC = 1600 -1;   //16 000 000/1600 = 10 000 Hz

	//set autoreload
	TIM2->ARR = 1000;  //10 000/1000 = 1 Hz

	//clear timer counter
	TIM2->CNT = 0;

	//enable timer
	TIM2->CR1 |= CR1_CEN;
}


void tim2_pa5_output_compare(void)
{
	//enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	///SET PA5 to alternate fun mode
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	//ste PA5 to alternate function type to TIM2 CH1
	GPIOA->AFR[0] |= AFR5_TIM;


	//enable clock acces to timer 2
	RCC->APB1ENR |= TIM2EN;

	//set prescalar
	TIM2->PSC = 1600 -1;   //16 000 000/1600 = 10 000 Hz

	//set autoreload
	TIM2->ARR = 10000-1;  //10 000/10 000= 1 Hz

	//set output compare toggle mode
	TIM2->CCMR1 |= OC_TOGGLE;

	//enable tim2 ch1 in compare mode
	TIM2->CCER |= CCER_CC1E;


	//clear timer counter
	TIM2->CNT = 0;

	//enable timer
	TIM2->CR1 |= CR1_CEN;
}
