#include "stm32f1xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"



int main(void)
{

	tim2_PA0_output_compare();

	while(1)
	{

	}
}
