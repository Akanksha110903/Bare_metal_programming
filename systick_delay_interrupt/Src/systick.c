#include "stm32f4xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VAL 16000
#define CTRL_ENABLE      (1U<<0)
#define CTRL_CLKSRC      (1U<<2)
#define CTRL_COUNTFLAG   (1U<<16)
#define CTRL_TICKINT     (1U<<1)
#define ONE_SEC_LOAD     16000000


void systickDelay(int delay)
{
	/*****configure systick*****/
	//reload the number of clock per milisecond
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	//clear systick current value register
	SysTick->VAL = 0;

	//enable systick and select internal clk src
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0;i<delay;i++)
	{
		//wait until the count flag is set
		while((SysTick->CTRL & CTRL_COUNTFLAG)==0){};
	}
	SysTick->CTRL =0;//disable systick
}

void systick_1hz_interrupt(void)
{
	/*****configure systick*****/
		//reload with number of clock per second
		SysTick->LOAD = ONE_SEC_LOAD -1;

		//clear systick current value register
		SysTick->VAL = 0;

		//enable systick and select internal clk src and
		SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC ;

		//Eable interrupt
		SysTick->CTRL |=CTRL_TICKINT;
}
