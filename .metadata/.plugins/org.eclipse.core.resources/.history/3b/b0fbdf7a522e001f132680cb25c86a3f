#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"
#include "uart.h"

#define GPIOC_EN           (1U<<4)
#define PIN13              (1U<<13)
#define LED_PIN             PIN13

char key;

int main(void)
{
	//enable clock to led gpio
	RCC -> APB2ENR |= GPIOC_EN;

	//set pc13 as output push pull
	GPIOC->CRH |= (1U << 20);
	GPIOC->CRH |= (1U << 21);
	GPIOC->CRH &= ~(1U << 22);
	GPIOC->CRH &= ~(0U << 23);

	uart1_rxtx_init();

	while(1)
	{
		key = uart1_read();
		if(key=='1')
		{
			GPIOC->ODR |= LED_PIN;
		}
		else
		{
			GPIOC->ODR &= ~LED_PIN;
		}
	}
}




