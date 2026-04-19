#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"


void uart2_rx_tx_init(void);
void uart2_write(int ch);
void uart_send(char *buff);
char uart2_read(void);
void uart2_rx_interrupt_init(void);

#define SR_RXNE      (1U<<5)


#endif //UART_H_
