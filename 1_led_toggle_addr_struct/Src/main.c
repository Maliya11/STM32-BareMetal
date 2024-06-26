
#include <stdint.h>
#define PERIPH_BASE        (0x40000000UL)

#define APB2PERIPH_OFFSET  (0x10000UL)
#define APB2PERIPH_BASE    (PERIPH_BASE + APB2PERIPH_OFFSET)

#define GPIOC_OFFSET       (0x1000UL)
#define GPIOC_BASE         (APB2PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET         (0x11000UL)
#define RCC_BASE           (APB2PERIPH_BASE + RCC_OFFSET)

#define PIN13              (1U<<13)
#define LED_PIN             PIN13

#define GPIOC_EN           (1U<<4)
#define __IO               volatile


typedef struct
{
	__IO uint32_t DUMMY[6];
	__IO uint32_t RCC_APB2ENR;
}RCC_TypeDef;


typedef struct
{
	__IO uint32_t GPIOx_CRL;
	__IO uint32_t GPIOx_CRH;
	__IO uint32_t GPIOx_IDR;
	__IO uint32_t GPIOx_ODR;
	__IO uint32_t GPIOx_BSRR;
	__IO uint32_t GPIOx_BRR;
	__IO uint32_t GPIOx_LCKR;
}GPIO_TypeDef;


#define RCC               ((RCC_TypeDef*) RCC_BASE)
#define GPIOC             ((GPIO_TypeDef*)GPIOC_BASE)


int main(void)
{
	/*Enable clock access to GPIOC*/
	RCC->RCC_APB2ENR |= GPIOC_EN;


	/*set PC13 as output pin*/
	GPIOC->GPIOx_CRH |= (1U << 20);
	GPIOC->GPIOx_CRH |= (1U << 21);
	GPIOC->GPIOx_CRH &= ~(1U << 22);
	GPIOC->GPIOx_CRH &= ~(0U << 23);


	while(1)
	{
		/*toggle LED*/
		GPIOC->GPIOx_ODR ^= LED_PIN;

		for(int i=0; i<1000000;i++){}
	}
}

