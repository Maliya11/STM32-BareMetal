#include "exti.h"

#define GPIOAEN     (1U<<2)

void pa15_exti_init(void)
{
	/*Disable global interrupts*/
	__disable_irq();

	/*Enable clock access for GPIOA*/
	RCC->APB2ENR |= GPIOAEN;

	/*Set PA15 as input*/
	GPIOA->CRH &= ~(1U<<28);
	GPIOA->CRH &= ~(1U<<29);
	GPIOA->CRH |=  (1U<<30);
	GPIOA->CRH &= ~(1U<<31);

	/*Select PORTA for EXTI15*/
	AFIO->EXTICR[3] = 0;

	/*Un-mask EXTI15*/
	EXTI->IMR |= (1U<<15);

	/*Select falling edge trigger*/
	EXTI->FTSR |= (1U<<15);

	/*Enable EXTI15 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*Enable global interrupts*/
	__enable_irq();
}
