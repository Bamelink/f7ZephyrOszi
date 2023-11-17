#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include "adc.h"

#define SLEEP_TIME_MS  1000


BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
	     "Console device is not ACM CDC UART device");

int main(void)
{
	/* ENABLE USB FS AS CONSOLE FOR PRINTK */
	const struct device *const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
	uint32_t dtr = 0;

	if (usb_enable(NULL)) {
		return 0;
	}

	/* Poll if the DTR flag was set */
	while (!dtr) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
		/* Give CPU resources to low priority threads. */
		k_sleep(K_MSEC(100));
	}
	printk("USB Initialized\n");

	int ret;

	ret = adc_init();
	if (ret != 0) {
		return -1;
	}
	printk("ADC init success\n");

	while (1) {
		HAL_ADC_Start_IT(&hadc1);
		k_msleep(SLEEP_TIME_MS);
		printk("Hi\n");
	}
	return 0;
}
