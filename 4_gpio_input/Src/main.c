#include "stm32f1xx.h"

#define GPIOB_EN           (1U<<3)
#define GPIOC_EN           (1U<<4)

#define PIN11              (1U<<11)
#define PIN13			   (1U<<13)

#define LED_PIN             PIN13
#define BTN_PIN             PIN11



int main(void)
{
	/*enable clock for GPIOB and GPIOC*/
	RCC -> APB2ENR |= GPIOC_EN;
	RCC -> APB2ENR |= GPIOB_EN;

	/*set GPIOC pin 13 as output*/
	GPIOC->CRH |= (1U << 20);
	GPIOC->CRH |= (1U << 21);
	GPIOC->CRH &= ~(1U << 22);
	GPIOC->CRH &= ~(0U << 23);

	/*set GPIOB pin 11 as input*/
	GPIOB->CRH &= ~(1U << 16);
	GPIOB->CRH &= ~(1U << 17);
	GPIOB->CRH |= (1U << 18);
	GPIOB->CRH &= ~(1U << 19);

	while(1)
	{
		if(!(GPIOB->IDR & BTN_PIN)){
			/*Turn on led*/
			GPIOC->BSRR = LED_PIN;
		}
		else{
			/*Turn of LED*/
			GPIOC->BSRR = (1U<<29);
		}
	}
}
