#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f1xx.h"

void pa15_exti_init(void);

#define   LINE15     (1U<<15)

#endif /* EXTI_H_ */
