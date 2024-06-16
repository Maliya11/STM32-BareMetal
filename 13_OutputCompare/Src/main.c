#include "stm32f1xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"

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

	uart1_tx_init();
	tim2_1Hz_init();

	while(1)
	{
		/*Wait for UIF*/
		while(!(TIM2->SR & SR_UIF)){}

		/*Clear UIF*/
		TIM2->SR &= ~SR_UIF;

		printf("A second passed \n\r");
		GPIOC->ODR ^= LED_PIN;
	}
}
