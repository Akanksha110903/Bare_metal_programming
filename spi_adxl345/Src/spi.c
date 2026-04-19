#include "spi.h"

#define SPI1_EN   (1U<<12)
#define GPIOAEN   (1U<<0)
#define CR1_CPHA  (1U<<0)
#define CR1_CPOL  (1U<<1)
#define SR_TXE    (1U<<1)
#define SR_RXNE    (1U<<0)
#define SR_BUSY   (1U<<7)

/*Pinout
 * PA9  - NSS
 * PA5  - SCK
 * PA6  - MISO
 * PA7  - MOSI
 * AF5*/
void spi_gpio_init(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//Set PA5, PA6, PA7 to alternate function mode
	//PA5
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	//PA6
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	//PA7
	GPIOA->MODER &= ~(1U<<14);
	GPIOA->MODER |= (1U<<15);

	//Set PA9 as output pin mode
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &= ~(1U<<19);

	//Set the PA5,PA6 , PA7 to AF5
	//PA5 to  AF5
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	//PA6 to AF5
	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &= ~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &= ~(1U<<27);

	//PA7 to AF5
	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &= ~(1U<<31);
}

void spi1_config(void)
{
	//enable clock acces to SPI1
	RCC->APB1ENR |= SPI1_EN;

	//Set the baud rate : fPLK/4
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 &=~(1U<<5);

	//Set CPOL to 1 and CPHA to 1
	SPI1->CR1 |= CR1_CPHA;
	SPI1->CR1 |= CR1_CPOL;

	//Enable full duplex
	SPI1->CR1 &= ~(1U<<10);

	//set MSB to be first
	SPI1->CR1 &= ~(1U<<7);

	//Set SPI in master mode
	SPI1->CR1 |= (1U<<2);

	//Set 8-bit data frame format
	SPI1->CR1 &= ~(1U<<11);

	//Select software slave management by setting SSM=1 and SSI=1
	SPI1->CR1 |= (1U<<8);
	SPI1->CR1 |= (1U<<9);

	//Enable SPI mode
	SPI1->CR1 |= (1U<<6);
}

void spi1_transmit(uint8_t *data, uint32_t size)
{
	uint32_t i=0;
	uint8_t temp;

	while(i<size)
	{
		//Wait until TXE is set
		while(!(SPI1->SR & SR_TXE)){}

		//Write the data
		SPI1->DR = data[i];
		i++;
	}
	//wait for TXE is set
	while(!(SPI1->SR & SR_TXE)){}

	//wait for BUSY flag to reset
	while(SPI1->SR & (SR_BUSY)){}

	//Clear OVR flag
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void spi1_receive(uint8_t *data, uint32_t size)
{
	while(size)
	{
		//send dummy data
		SPI1->DR = 0;

		//Wait for RXNE flag to set
		while(!(SPI1->SR & SR_RXNE));

		//Read the data from data register
		*data++ = SPI1->DR;
		size--;
	}
}

void cs_enable(void)
{
	GPIOA->ODR &= ~(1U<<9);
}

void cs_disable(void)
{
	GPIOA->ODR |= (1U<<9);
}
