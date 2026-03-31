#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"



int time_stamp =0;
//setup : connect a jumper wire from PA5 to PC6
int main(void)
{

	tim2_pa5_output_compare();
	tim3_pc6_input_capture();




	 while(1)
	 {

        //wait until edge is captured
		 while(!(TIM3->SR & SR_CC1IF)){}

		//read capture value
		 time_stamp = TIM3->CCR1;

	 }

}



