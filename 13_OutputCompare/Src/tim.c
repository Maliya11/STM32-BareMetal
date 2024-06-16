#include "tim.h"

#define TIM2EN      	(1U<<0)
#define CR1_CEN     	(1U<<0)
#define OC_TOGGLE   	(1U<<4) | (1U<<5)
#define CCER_CC1E   	(1U<<0)
#define GPIOA_EN		(1U<<2)
#define MAPR_TIM2_REMAP (1U<<8) | (1U<<9)

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

void tim2_PA0_output_compare(void)
{
	/*Configure GPIOA*/
	RCC->APB2ENR |= GPIOA_EN;
	/*Set PA0 to alternate function mode*/
	GPIOA->CRL |= (1U<<0);
	GPIOA->CRL |= (1U<<1);
	GPIOA->CRL |= ~(1U<<2);
	GPIOA->CRL |= (1U<<3);
	/*Set PA0 alternate function type*/
	AFIO->MAPR &= ~ MAPR_TIM2_REMAP;


	/*Enable clock access to TIM2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set pre-scalar value*/
	TIM2->PSC = 1600-1;  /* 16MHz/1600 = 10kHz */
	/*Set auto reload value*/
	TIM2->ARR = 10000 - 1; /* 10kHz/10000 = 1Hz */

	/*Set output compare toggle mode*/
	TIM2->CCMR1 = OC_TOGGLE;
	/*Enable TIM2 channel 1 in compare mode*/
	TIM2->CCER |= CCER_CC1E;

	/*clean counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}




