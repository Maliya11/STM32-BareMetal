#include "stm32f1xx.h"

#define GPIOC_EN           (1U<<4)
#define PIN13              (1U<<13)
#define LED_PIN             PIN13



int main(void)
{
	RCC -> APB2ENR |= GPIOC_EN;

	GPIOC->CRH |= (1U << 20);
	GPIOC->CRH |= (1U << 21);
	GPIOC->CRH &= ~(1U << 22);
	GPIOC->CRH &= ~(0U << 23);

	while(1)
	{
		GPIOC->ODR ^= LED_PIN;

		for(int i=0; i<100000; i++){}
	}
}
