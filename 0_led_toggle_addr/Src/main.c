
#define PERIPH_BASE        (0x40000000UL)

#define APB2PERIPH_OFFSET  (0x10000UL)
#define APB2PERIPH_BASE    (PERIPH_BASE + APB2PERIPH_OFFSET)

#define GPIOC_OFFSET       (0x1000UL)
#define GPIOC_BASE         (APB2PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET         (0x11000UL)
#define RCC_BASE           (APB2PERIPH_BASE + RCC_OFFSET)

#define APB2EN_R_OFFSET    (0x18UL)
#define RCC_APB2EN_R       (*(volatile unsigned int *)(RCC_BASE + APB2EN_R_OFFSET))

#define CRH_R_OFFSET       (0x04UL)
#define GPIOC_CRH_R        (*(volatile unsigned int *)(GPIOC_BASE + CRH_R_OFFSET))

#define OD_R_OFFSET        (0x0CUL)
#define GPIOC_OD_R         (*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET))

#define PIN13              (1U<<13)
#define LED_PIN             PIN13

#define GPIOC_EN           (1U<<4)


int main(void)
{
	/*Enable clock access to GPIOC*/
	RCC_APB2EN_R |= GPIOC_EN;  //FRIENDLY PROGRAMMING

	/*set PC13 as output pin*/
	GPIOC_CRH_R |= (1U << 20);
	GPIOC_CRH_R |= (1U << 21);
	GPIOC_CRH_R &= ~(1U << 22);
	GPIOC_CRH_R &= ~(0U << 23);

	while(1)
	{
		/*set PC13 high*/
		//GPIOC_OD_R |= LED_PIN;

		/*toggle LED*/
		GPIOC_OD_R ^= LED_PIN;
		for(int i=0; i<100000;i++){}
	}
}

