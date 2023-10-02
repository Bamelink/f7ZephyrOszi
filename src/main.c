#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "adc.h"

#define SLEEP_TIME_MS  1000


int main(void)
{
	int ret;

	ret = adc_init();
	if (ret != 0) {
		return -1;
	}
	printk("ADC init success\n");

	while (1) {
		HAL_ADC_Start_IT(&hadc1);
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
