/*
 * tim.h
 *
 *  Created on: Jun 15, 2024
 *      Author: ACER
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f1xx.h"
void tim2_1Hz_init(void);
void tim2_1Hz_interrupt_init(void);


#define SR_UIF     (1U<<0)

#endif /* TIM_H_ */
