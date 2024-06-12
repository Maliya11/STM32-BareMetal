/*
 * uart.c
 *
 *  Created on: Jun 12, 2024
 *      Author: ACER
 */
#include "uart.h"

#define GPIOA_EN           (1U<<2)
#define UART1_EN           (1U<<14)
#define AFIO_EN            (1U<<0)

#define CR1_TE             (1U<<3)
#define CR1_RE             (1U<<2)

#define CR1_UE             (1U<<13)
#define SR_TXE             (1U<<7)
#define SR_RXNE            (1U<<5)

#define SYS_FREQ           16000000
#define APB2_CLK		   SYS_FREQ

#define UART_BAUDRATE      115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart1_write(int ch);

int __io_putchar(int ch)
{
	uart1_write(ch);
	return ch;
}

void uart1_rxtx_init(void)
{
	/*******Configure usart gpio pins*********/
	/*Enable clock access to gpioa*/
	RCC->APB2ENR |= GPIOA_EN;

	/*Set PA9 to alternate function mode*/
	GPIOA->CRH |= (1U<<4);
	GPIOA->CRH |= (1U<<5);
	GPIOA->CRH &= ~(1U<<6);
	GPIOA->CRH |= (1U<<7);

	/*Set PA10 to alternate function mode*/
	GPIOA->CRH |= (1U<<8);
	GPIOA->CRH |= (1U<<9);
	GPIOA->CRH &= ~(1U<<10);
	GPIOA->CRH |= (1U<<11);

	/*Set PA9 to UART_TX and PA10 to RX*/
	AFIO->MAPR &= ~(1U<<2);

	/**********Configure uart module**************/
	/*Enable clock access to uart1*/
	RCC->APB2ENR |= UART1_EN;
	RCC->APB2ENR |= AFIO_EN;

	/*configure baudrate*/
	uart_set_baudrate(USART1,APB2_CLK,UART_BAUDRATE);

	/*Configure transfer direction*/
	USART1->CR1 = (CR1_TE | CR1_RE);  //SETTING THE VALUE
	//TO ERASE THE UART REGISTER

	/*Enable uart module*/
	USART1->CR1 |= CR1_UE;
}

void uart1_tx_init(void)
{
	/*******Configure usart gpio pins*********/
	/*Enable clock access to gpioa*/
	RCC->APB2ENR |= GPIOA_EN;

	/*Set PA9 to alternate function mode*/
	GPIOA->CRH |= (1U<<4);
	GPIOA->CRH |= (1U<<5);
	GPIOA->CRH &= ~(1U<<6);
	GPIOA->CRH |= (1U<<7);

	/*Set PA2 type to UART_TX*/
	AFIO->MAPR &= ~(1U<<2);

	/**********Configure uart module**************/
	/*Enable clock access to uart1*/
	RCC->APB2ENR |= UART1_EN;

	/*configure baudrate*/
	uart_set_baudrate(USART1,APB2_CLK,UART_BAUDRATE);

	/*Configure transfer direction*/
	USART1->CR1 = CR1_TE;  //SETTING THE VALUE
	//TO ERASE THE UART REGISTER

	/*Enable uart module*/
	USART1->CR1 |= CR1_UE;
}

char uart1_read(void)
{
	/*Make sure receive data register is not empty*/
	while(!(USART1->SR & SR_RXNE)){}

	/*Read data*/
	return USART1->DR;
}

void uart1_write(int ch)
{
	/*Make sure transmit data register is empty*/
	while(!(USART1->SR & SR_TXE)){}

	/*Write to transmit data register*/
	USART1->DR = (ch & 0xFF); //to transmit 8 bit

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
