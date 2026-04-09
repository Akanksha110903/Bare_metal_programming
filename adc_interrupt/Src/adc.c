#include "stm32f4xx.h"
#include "adc.h"
//apb2
//rcc-apb2 en  1<<8  for adc1
#define GPIOAEN        (1U<<0)
#define ADC1EN         (1U<<8)
#define ADC_CH1        (1U<<0)
#define ADC_SEQ_LEN_1  (0x00)
#define CR2_ADC_ON     (1U<<0)
#define CR2_SWSTART    (1U<<30)
#define CR2_CONT       (1U<<1)
#define CR1_EOCIE      (1U<<5)

//adc1_in1 - PA1

void PA1_adc_init(void)
{
	//********configure ADC GPIO PIN*******
	//enable clock access to adc pin port PA1
	RCC->AHB1ENR |= GPIOAEN;

	//set mode of PA1 to analog mode
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	//*********configure the ADC parameter********
	//configure ACD clock enable
	RCC->APB2ENR |= ADC1EN;

	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	//conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;



	//enable ADC module
	ADC1->CR2 = CR2_ADC_ON;

}

void start_conversion(void)
{
	/*enable continuous conversion*/
	ADC1->CR2 |= CR2_CONT;
	//start adc conversion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	//wait for conversion to be read
	while(!(ADC1->SR & SR_EOC))
	{

	}

	//read converted result
	return ADC1->DR;
}


void PA1_adc_interrupt_init(void)
{
	//********configure ADC GPIO PIN*******
	//enable clock access to adc pin port PA1
	RCC->AHB1ENR |= GPIOAEN;

	//set mode of PA1 to analog mode
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	//*********configure the ADC parameter********
	//configure ACD clock enable
	RCC->APB2ENR |= ADC1EN;

	//Enable ADC end-of-coversion-interrupt
	ADC1->CR1 |= CR1_EOCIE;

	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	//enable ADC interrupt in NVIC
	NVIC_EnableIRQ(ADC_IRQn);

	//conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;


	//enable ADC module
	ADC1->CR2 = CR2_ADC_ON;

}
