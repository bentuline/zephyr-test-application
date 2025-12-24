#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led =
	GPIO_DT_SPEC_GET_OR(LED0_NODE, gpios, {0});

int main(void)
{
	LOG_INF("zephyr-test-application start");

	if (led.port == NULL || !device_is_ready(led.port)) {
		LOG_WRN("LED0 alias not found; running heartbeat only");
		while (1) {
			k_sleep(K_SECONDS(1));
			LOG_INF("heartbeat");
		}
	}

	int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret != 0) {
		LOG_ERR("Failed to configure LED (err %d)", ret);
		return ret;
	}

	bool on = true;
	while (1) {
		on = !on;
		gpio_pin_set_dt(&led, on);
		LOG_INF("LED %s", on ? "on" : "off");
		k_sleep(K_SECONDS(1));
	}
}

