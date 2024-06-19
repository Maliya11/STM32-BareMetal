/*
 * adc.h
 *
 *  Created on: Jun 11, 2024
 *      Author: ACER
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read();
void pa1_adc_interrupt_init(void);

#define SR_EOC            (1U<<1)

#endif /* ADC_H_ */
