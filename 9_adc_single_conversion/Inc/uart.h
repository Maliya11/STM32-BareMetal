/*
 * uart.h
 *
 *  Created on: Jun 12, 2024
 *      Author: ACER
 */

#ifndef UART_H_
#define UART_H

#include <stdint.h>
#include "stm32f1xx.h"

void uart1_tx_init(void);
void uart1_rxtx_init(void);
char uart1_read(void);



#endif /* UART_H_ */
