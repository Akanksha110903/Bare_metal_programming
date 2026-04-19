#include "uart.h"

#define GPIODEN               (1u<<3)
#define UART2EN               (1U<<17)
#define DMA1EN                (1U<<21)
#define DMA_S_EN              (1U<<0)
#define DMA_MEM_INC           (1U<<10)
#define DMA_DIR_MEM_TO_PERIPH (1U<<6)
#define DMA_CR_TCIE           (1U<<4)
#define UART_CR3_DMAT         (1U<<7)

//16000000

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200
#define CR1_TE       (1U<<3)
#define CR1_RE       (1U<<2)
#define CR1_UE       (1U<<13)
#define SR_TXE       (1U<<7)
#define CR1_RXNEIE   (1U<<5)

static void uart_set_baudrate(uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate);


void dma1_stream6_init(uint32_t src, uint32_t dst,uint32_t len)
{
	//enable clk access to dma
	RCC->AHB1ENR |= DMA1EN;

	//disable DMA1 stream6
	DMA1_Stream6->CR &=~(DMA_S_EN);

	//Wait until DMA1 Stream 6 is disabled
	while(DMA1_Stream6->CR & DMA_S_EN);

	//clear all interrupt flags of stream6
	DMA1->HIFCR |=(1U<<16);
	DMA1->HIFCR |=(1U<<18);
	DMA1->HIFCR |=(1U<<19);
	DMA1->HIFCR |=(1U<<20);
	DMA1->HIFCR |=(1U<<21);

	//set the destination buffer
	DMA1_Stream6->PAR = dst;

	//set source buffer
	DMA1_Stream6->M0AR = src;


	//set length
	DMA1_Stream6->NDTR = len;

	//select stream6 CH4
	DMA1_Stream6->CR &= ~(1U<<25);
	DMA1_Stream6->CR &= ~(1U<<26);
	DMA1_Stream6->CR |= (1U<<27);

	//enable memory increament
	DMA1_Stream6->CR |= DMA_MEM_INC;

	//configure transfer direction  (memory to peripheral)
	DMA1_Stream6->CR |= DMA_DIR_MEM_TO_PERIPH;

	//enable DMA transfer complete interrupt
	DMA1_Stream6->CR |= DMA_CR_TCIE;

	//enable direct mode and disable FIFO
	DMA1_Stream6->FCR = 0;


	//enable DMA1 stream6
	DMA1_Stream6->CR |=(DMA_S_EN);

	//enable UART2 transmitter DMA
	USART2->CR3 |= UART_CR3_DMAT;

	//DMA interrupt enable NVIC
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}


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

void uart2_rx_interrupt_init(void)
{
	/*****configure uart gpio pin*******/
	//enable clock access to gpio d
	RCC->AHB1ENR |= GPIODEN;

	//set PD6 mode to alternate function mode: 10 (pin for rx)
	GPIOD->MODER &= ~(1U<<12);
	GPIOD->MODER |= (1U<<13);

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

	//Enable RXNE interrupt
	USART2->CR1 |= CR1_RXNEIE ;

	//Enable UART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);

	//enable uart module
	USART2->CR1 |= CR1_UE;

}

