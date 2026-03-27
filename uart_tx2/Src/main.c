#include <stdint.h>
#include "stm32f4xx.h"

#define GPIODEN  (1u<<3)
#define UART2EN  (1U<<17)

//16000000

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200
#define CR1_TE (1U<<3)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)

static void uart_set_baudrate(uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate);
static void uart_send(char *buff);

void uart2_tx_init(void);
void uart2_write(int ch);

#define BUFF_SIZE 20
char tx_buffer[BUFF_SIZE]="Hi Akanksha\n";

int main(void)
{
     uart2_tx_init();

	while(1)
	{
		//uart2_write('A');
		uart_send(tx_buffer);



	}
}


void uart2_tx_init(void)
{
	/*****configure uart gpio pin*******/
	//enable clock access to gpio d
	RCC->AHB1ENR |= GPIODEN;

	//set PD5 mode to alternate function mode: 10
	GPIOD->MODER &= ~(1U<<10);
	GPIOD->MODER |= (1U<<11);
    // PD5 -> AF mode
//    GPIOD->MODER &= ~(3U << 10);
//    GPIOD->MODER |=  (2U << 10);

	//set PD5 alternate function type to uart_tx   AF7: 0111
	GPIOD->AFR[0] |= (1U<<20);
	GPIOD->AFR[0] |= (1U<<21);
	GPIOD->AFR[0] |= (1U<<22);
	GPIOD->AFR[0] &= ~(1U<<23);
//	GPIOD->AFR[0] &= ~(0xF << 20);  // Clear AFR for PD5
//	GPIOD->AFR[0] |=  (7 << 20);    // AF7 for USART2


	/*************confugure usard module********/
	//enable clock access to usart 2
	RCC->APB1ENR |= UART2EN;

	//configure baude rate
	uart_set_baudrate(SYS_FREQ,UART_BAUDRATE);


	//configure transfer direction
	USART2->CR1 |= CR1_TE;

	//enable uart module
	USART2->CR1 |= CR1_UE;

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

static void uart_send(char *buff){
	while(*buff){
		uart2_write(*buff++);
	}
}
