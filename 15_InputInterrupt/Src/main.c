#include "stm32f1xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOC_EN           (1U<<4)
#define PIN13              (1U<<13)
#define LED_PIN             PIN13

static void exti_callback(void);

int main(void)
{
	RCC -> APB2ENR |= GPIOC_EN;

	GPIOC->CRH |= (1U << 20);
	GPIOC->CRH |= (1U << 21);
	GPIOC->CRH &= ~(1U << 22);
	GPIOC->CRH &= ~(1U << 23);

	pa15_exti_init();
	uart1_tx_init();


	while(1)
	{

	}
}

static void exti_callback(void)
{
	printf("BTN pressed...\n\r");
	GPIOC->ODR ^= LED_PIN;
}

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & LINE15) != 0)
	{
		/*Clear the PR flag*/
		EXTI->PR |= LINE15;

		//do something
		exti_callback();
	}
}
