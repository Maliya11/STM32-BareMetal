#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"
#include "uart.h"




int main(void)
{

	uart1_tx_init();

	while(1)
	{
		//uart1_write('Y');
		printf("Hello World...\n\r");
	}
}




