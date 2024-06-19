#include "tim.h"

#define TIM2EN      (1U<<0)
#define CR1_CEN     (1U<<0)
#define DIER_UIE    (1U<<0)


void tim2_1Hz_init(void)
{
	/*Enable clock access to TIM2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set pre-scalar value*/
	TIM2->PSC = 1600-1;  /* 16MHz/1600 = 10kHz */

	/*Set auto reload value*/
	TIM2->ARR = 10000 - 1; /* 10kHz/10000 = 1Hz */

	/*clean counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}

void tim2_1Hz_interrupt_init(void)
{
	/*Enable clock access to TIM2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set pre-scalar value*/
	TIM2->PSC = 1600-1;  /* 16MHz/1600 = 10kHz */

	/*Set auto reload value*/
	TIM2->ARR = 10000 - 1; /* 10kHz/10000 = 1Hz */

	/*clean counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

	/*Enable TIM2 interrupt*/
	TIM2->DIER |= DIER_UIE;

	/*Enable TIM2 NVIC interrupt*/
	NVIC_EnableIRQ(TIM2_IRQn);
}




