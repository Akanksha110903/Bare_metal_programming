#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOBEN     (1U<<1)
#define I2C1EN      (1U<<21)
#define SWRST       (1U<<15)
#define I2C_100KHz             80
#define SD_MODE_MAX_RISE_TIME  17
#define CR1_PE      (1U<<0)
#define SR2_BUSY    (1U<<1)
#define CR1_START   (1U<<8)
#define SR1_SB      (1U<<0)
#define SR1_ADDR    (1U<<1)
#define SR1_TXE     (1U<<7)
#define SR1_RXNE    (1U<<6)
#define CR1_ACK     (1U<<10)
#define CR1_STOP    (1U<<9)
#define SR1_BTF     (1U<<1)

//Pinout
/*PB 8 ----- SCL*/
/*PB 9 ----- SDA*/

void I2C1_init(void)
{
	//enable clock access to I2C1

	//enable clock  access to GPIOB
	RCC->AHB1ENR |= GPIOBEN;

	//Set PB8 mode to alternate function AF4
	GPIOB->MODER &= ~(1U<<16);
	GPIOB->MODER |= (1U<<17);

	//Set PB9 mode to alternate function
	GPIOB->MODER &= ~(1U<<18);
	GPIOB->MODER |= (1U<<19);

	//SET AF4 for PB8
	GPIOB->AFR[1] &= ~(1U<<0);
	GPIOB->AFR[1] &= ~(1U<<1);
	GPIOB->AFR[1] |=  (1U<<2);
	GPIOB->AFR[1] &= ~(1U<<3);

	//SET AF4 for PB9
	GPIOB->AFR[1] &= ~(1U<<4);
	GPIOB->AFR[1] &= ~(1U<<5);
	GPIOB->AFR[1] |=  (1U<<6);
	GPIOB->AFR[1] &= ~(1U<<7);

	//Set PB8 output type to open drain
	GPIOB->OTYPER |= (1U<<8);

	//Set PB9 output type to open drain
	GPIOB->OTYPER |= (1U<<9);

	//enable Pullup for PB8
	GPIOB->OSPEEDR |= (1U<<16);
	GPIOB->OSPEEDR &= ~(1U<<17);

	//enable Pullup for PB9
	GPIOB->OSPEEDR |= (1U<<18);
	GPIOB->OSPEEDR &= ~(1U<<19);

	//Enable clock access to I2C1
	RCC->APB1ENR |= I2C1EN;

	//Enter reset mode
	I2C1->CR1 |= SWRST;

	//Come out of reset mode
	I2C1->CR1 &= ~(SWRST);

	//Set peripheral clock frequency
	I2C1->CR2 &= ~(1U<<0);
	I2C1->CR2 &= ~(1U<<1);
	I2C1->CR2 &= ~(1U<<2);
	I2C1->CR2 &= ~(1U<<3);
	I2C1->CR2 |=  (1U<<4);
	I2C1->CR2 &= ~(1U<<5);

	//set I2C to statndard mode
	I2C1->CCR = I2C_100KHz;

	//Set rise time
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

	//Enable I2C
	I2C1->CR1 |= CR1_PE;


}

void I2C1_byteRead (char saddr, char maddr, char* data)
{
	volatile int tmp;

	//wait until bus not busy
	while(I2C1->SR2 & (SR2_BUSY)){}

	//Generate start
	I2C1->CR1 |= CR1_START;

	//Wait for start flag to set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait for address flag to be set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Clear the ADDR flag
	tmp = I2C1->SR2;

	//wait until transmitter empty
	while(!(I2C1->SR1 & (SR1_TXE))){}

	//Send memory address
	I2C1->DR = maddr;

	//wait until transmitter empty
	while(!(I2C1->SR1 & (SR1_TXE))){}

	//Generate restart
	I2C1->CR1 |= CR1_START;

	//Wait for start flag to set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + read
	I2C1->DR = saddr << 1 | 1;

	//wait for address flag to be set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Disable acknowledge
	I2C1->CR1 &= ~CR1_ACK;

	//Clear the ADDR flag
	tmp = I2C1->SR2;

	//Generate stop after data received
	I2C1->CR1 |= CR1_STOP;

	//wait for RXNE flag to set
	while(!(I2C1->SR1 & (SR1_RXNE))){}

	//store in data
	*data++ = I2C1->DR;

}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	//wait until bus not busy
	while(I2C1->SR2 & (SR2_BUSY)){}

	//Generate start
	I2C1->CR1 |= CR1_START;

	//Wait for start flag to set
	while(!(I2C1->SR1 & (SR1_SB))){}


	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait for address flag to be set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Clear the ADDR flag
	tmp = I2C1->SR2;

	//wait until transmitter empty
	while(!(I2C1->SR1 & (SR1_TXE))){}

	//Send memory address
	I2C1->DR = maddr;

	//wait until transmitter empty
	while(!(I2C1->SR1 & (SR1_TXE))){}

	//Generate restart
	I2C1->CR1 |= CR1_START;

	//Wait for start flag to set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + read
	I2C1->DR = saddr << 1 | 1;

	//wait for address flag to be set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Clear the ADDR flag
	tmp = I2C1->SR2;

	//Enable acknowledge
	I2C1->CR1 |= CR1_ACK;

	while(n>0U)
	{
		//if one byte
		if(n==1U)
		{
			//Disable acknowledge
			I2C1->CR1 &= ~CR1_ACK;

			//generate stop condtion
			I2C1->CR1 |= CR1_STOP;

			//wait for RXNE flag to set
			while(!(I2C1->SR1 & (SR1_RXNE))){}

			//store in data
			*data++ = I2C1->DR;

			break;

		}else
		{

			//wait for RXNE flag to set
			while(!(I2C1->SR1 & (SR1_RXNE))){}

			//store in data
			*data++ = I2C1->DR;

			//decreament n
			n--;

		}
	}
}


void I2C1_burstWrite(char saddr, char maddr,int n, char* data)
{
	volatile int tmp;
	//wait until bus not busy
	while(I2C1->SR2 & (SR2_BUSY)){}

	//Generate start
	I2C1->CR1 |= CR1_START;

	//Wait for start flag to set
	while(!(I2C1->SR1 & (SR1_SB))){}


	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait for address flag to be set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Clear the ADDR flag
	tmp = I2C1->SR2;

	//wait until transmitter empty
	while(!(I2C1->SR1 & (SR1_TXE))){}

	//Send memory address
	I2C1->DR = maddr;


	for(int i=0;i<n;i++)
	{
		//wait until transmitter empty
		while(!(I2C1->SR1 & (SR1_TXE))){}

		//transmit the data
		I2C1->DR = *data++;
	}

	//wait until the transfer finished
	while(!(I2C1->SR1 & (SR1_BTF))){}
}
