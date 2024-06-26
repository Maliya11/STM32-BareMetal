/*
 * adc.c
 *
 *  Created on: Jun 11, 2024
 *      Author: ACER
 */

#include "stm32f1xx.h"
#include "adc.h"

#define ADC1EN            (1U<<9)
#define GPIOAEN           (1U<<2)
#define ADC_CH1           (1U<<0)
#define ADC_SEQ_LEN_1      0x00
#define CR2_ADON          (1U<<0)
#define CR2_SWSTART       (1U<<30)
#define CR2_CONT          (1U<<1)
#define CR1_EOCIE         (1U<<5)

void pa1_adc_interrupt_init(void)
{
	/*Configure the ADC GPIO pin*/

	/*Enable clock access to GPIOA*/
	RCC->APB2ENR |= GPIOAEN;

	/*Set the mode for PA1 to analog*/
	GPIOA->CRL &= ~(1U<<4);
	GPIOA->CRL &= ~(1U<<5);
	GPIOA->CRL &= ~(1U<<6);
	GPIOA->CRL &= ~(1U<<7);

	/*Configure the ADC module*/
	/*Clock access to ADC module*/
	RCC->APB2ENR |= ADC1EN;

	/*Enable ADC end-of-conversion interrupt*/
	ADC1->CR1 |= CR1_EOCIE;

	/*Enable ADC IRQ in NVIC*/
	NVIC_EnableIRQ(ADC1_2_IRQn);

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;


	/*Enable ADC module*/
	ADC1->CR2 |= CR2_ADON;

}


void pa1_adc_init(void)
{
	/*Configure the ADC GPIO pin*/

	/*Enable clock access to GPIOA*/
	RCC->APB2ENR |= GPIOAEN;

	/*Set the mode for PA1 to analog*/
	GPIOA->CRL &= ~(1U<<4);
	GPIOA->CRL &= ~(1U<<5);
	GPIOA->CRL &= ~(1U<<6);
	GPIOA->CRL &= ~(1U<<7);

	/*Configure the ADC module*/
	/*Clock access to ADC module*/
	RCC->APB2ENR |= ADC1EN;

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/*Enable ADC module*/
	ADC1->CR2 |= CR2_ADON;

}

void start_conversion(void)
{
	/*Enable cts conversion*/
	ADC1->CR2 |= CR2_CONT;

	/*start ADC conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read()
{
	/*wait for conversion to be complete*/
	while(!(ADC1->SR & SR_EOC)){}

	/*Read converted result*/
	return (ADC1->DR);
}
