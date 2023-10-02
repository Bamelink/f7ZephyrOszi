#ifndef ADC_H
#define ADC_H

#include <stm32f7xx_hal.h>

extern ADC_HandleTypeDef hadc1;

uint8_t adc_init();

#endif