#include "uart.h"

#define GPIODEN  (1u<<3)
#define UART2EN  (1U<<17)

//16000000

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200
#define CR1_TE (1U<<3)
#define CR1_RE (1U<<2)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)
#define SR_RXNE (1U<<5)

static void uart_set_baudrate(uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate);





void uart2_rx_tx_init(void)
{
	/*****configure uart gpio pin*******/
	//enable clock access to gpio d
	RCC->AHB1ENR |= GPIODEN;

	//set PD5 mode to alternate function mode: 10 (pin for tx)
	GPIOD->MODER &= ~(1U<<10);
	GPIOD->MODER |= (1U<<11);

	//set PD6 mode to alternate function mode: 10 (pin for rx)
	GPIOD->MODER &= ~(1U<<12);
	GPIOD->MODER |= (1U<<13);


	//set PD5 alternate function type to uart_tx   AF7: 0111
	GPIOD->AFR[0] |= (1U<<20);
	GPIOD->AFR[0] |= (1U<<21);
	GPIOD->AFR[0] |= (1U<<22);
	GPIOD->AFR[0] &= ~(1U<<23);


	//set PD6 alternate function type to uart_Rx   AF7: 0111
		GPIOD->AFR[0] |= (1U<<24);
		GPIOD->AFR[0] |= (1U<<25);
		GPIOD->AFR[0] |= (1U<<26);
		GPIOD->AFR[0] &= ~(1U<<27);



	/*************confugure usart module********/
	//enable clock access to usart 2
	RCC->APB1ENR |= UART2EN;

	//configure baude rate
	uart_set_baudrate(SYS_FREQ,UART_BAUDRATE);


	//configure transfer direction trasmission and receiver enable
	USART2->CR1 |= (CR1_TE | CR1_RE);



	//enable uart module
	USART2->CR1 |= CR1_UE;

}

char uart2_read(void){
	//make sure receive data register is not empty
	while(!(USART2->SR & SR_RXNE))
	{

	}
	//return the contenct of the data register
	return USART2->DR;
}

void uart2_write(int ch)
{
	//make sure transmit data register is empty
	while(!(USART2->SR & SR_TXE))
	{

	}

	//write to transmit data register

	USART2->DR = (ch & 0xFF);
}
static void uart_set_baudrate(uint32_t PeriphClk,uint32_t BaudRate)
{
	USART2->BRR =compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);

}

void uart_send(char *buff){
	while(*buff){
		uart2_write(*buff++);
	}
}
