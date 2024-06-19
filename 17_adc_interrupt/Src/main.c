#include "stm32f1xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"


uint32_t sensor_value;

int main(void)
{
	//uart1_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1)
	{

	}
}

static void adc1_callback(void)
{
	sensor_value = ADC1->DR;
	//printf("Sensor value : %d \n \r", sensor_value);
}

void ADC1_2_IRQHandler(void)
{
	/*Check for EOC in SR*/
	if((ADC1->SR & SR_EOC)!=0)
	{
		/*Clear EOC flag*/
		ADC1->SR |= SR_EOC;

		//Do something
		adc1_callback();
	}
}
