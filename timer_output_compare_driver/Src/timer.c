#include "stm32f4xx.h"

#define TIM2EN  (1U<<0)
#define CR1_CEN (1U<<0)


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
