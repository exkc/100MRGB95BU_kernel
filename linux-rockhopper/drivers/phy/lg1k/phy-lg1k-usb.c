// SPDX-License-Identifier: GPL-2.0-only
/*
 * LG DTV SoC USB PHY driver
 *
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
 */

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/gpio.h>

#include <linux/delay.h>
#include <linux/io.h>
#include <linux/phy/phy.h>
#include <linux/regmap.h>
#include "phy-lg1k-usb.h"

__maybe_unused
static int set_pinmux_select(void __iomem *addr,
				unsigned int mask, unsigned int value)
{
	unsigned int set_val;

	if (!addr)
		return -EFAULT;

	set_val = readl(addr);
	set_val = (set_val & (~mask)) | value;

	writel(set_val, addr);

	return 0;
}

__maybe_unused
static int set_reset_ctl(void __iomem *addr,
			unsigned int mask, int inverse, int enable)
{
	unsigned int set_val;

	if (!addr)
		return -EFAULT;

	enable ^= inverse;

	set_val = readl(addr);
	set_val = enable ? (set_val & (~mask)) : (set_val | mask);

	writel(set_val, addr);

	return 0;
}

int lg1k_usb_phy_parse_dt(struct lg1k_usb_phy *lgphy)
{
	//unsigned int regs[2];
	int ret;
	int i;
	struct device_node *np = lgphy->dev->of_node;
	struct resource res;

	if (!np) {
		dev_err(lgphy->dev, "device node is null\n");
		return -ENODEV;
	}

	i = of_property_match_string(np, "reg-names", "base");
	lgphy->hc_base = of_iomap(np, i);
	if (!lgphy->hc_base) {
		dev_err(lgphy->dev, "host controller base is null\n");
		ret = -EFAULT;
		goto cleanup;
	}
	if (of_address_to_resource(np, i, &res)) {
		dev_err(lgphy->dev, "host controller phys addr is null\n");
		ret = -EFAULT;
		goto cleanup;
	}
	lgphy->hc_phys = res.start;

	i = of_property_match_string(np, "reg-names", "host");
	lgphy->host_reg = of_iomap(np, i);
	if (!lgphy->host_reg) {
		dev_err(lgphy->dev, "host ctrl reg is null\n");
		ret = -EFAULT;
		goto cleanup;
	}

	i = of_property_match_string(np, "reg-names", "phy");
	lgphy->phy_reg = of_iomap(np, i);
	if (!lgphy->phy_reg) {
		dev_err(lgphy->dev, "phy ctrl reg is null\n");
		ret = -EFAULT;
		goto cleanup;
	}

	i = of_property_match_string(np, "reg-names", "pinmux");
	lgphy->pin_mux[0] = of_iomap(np, i);

	i = of_property_match_string(np, "reg-names", "pinmux1");
	lgphy->pin_mux[1] = of_iomap(np, i);

	lgphy->ctl_gpio = lgphy->ocd_gpio = -1;
	lgphy->ctl_gpio = of_get_named_gpio(np, "ctl-gpios", 0);
	lgphy->ocd_gpio = of_get_named_gpio(np, "ocd-gpios", 0);
	lgphy->hw_initialized = 0;

	return 0;

cleanup:
	if (lgphy->hc_base)
		iounmap(lgphy->hc_base);
	if (lgphy->host_reg)
		iounmap(lgphy->host_reg);
	if (lgphy->phy_reg)
		iounmap(lgphy->phy_reg);
#if 0
	if (lgphy->gbl_reg)
		iounmap(lgphy->gbl_reg);
#endif
	if (lgphy->pin_mux[0])
		iounmap(lgphy->pin_mux[0]);
	if (lgphy->pin_mux[1])
		iounmap(lgphy->pin_mux[1]);
	return ret;
}
EXPORT_SYMBOL_GPL(lg1k_usb_phy_parse_dt);

void lg1k_usb_phy_remove(struct lg1k_usb_phy *lgphy)
{
	//usb_remove_phy(&lgphy->phy);
	iounmap(lgphy->hc_base);
	iounmap(lgphy->host_reg);
	iounmap(lgphy->phy_reg);

	if (lgphy->pin_mux[0])
		iounmap(lgphy->pin_mux[0]);
	if (lgphy->pin_mux[1])
		iounmap(lgphy->pin_mux[1]);
}
EXPORT_SYMBOL_GPL(lg1k_usb_phy_remove);

int lg1k_usb_phy_set_gpio_pinmux(struct lg1k_usb_phy *lgphy, int idx)
{
	int ret;
	unsigned int regs[2];
	static const char *str[] = {"gpio-pinmux", "gpio-pinmux1"};

	if (IS_ENABLED(CONFIG_PINCTRL_LG1K))
		return 0;

	if (!lgphy->pin_mux[idx])
		return -1;

	if (of_property_read_u32_array(lgphy->dev->of_node,
						str[idx], regs, 2)) {
		dev_warn(lgphy->dev, "pinmux[%i] won't be set\n", idx);
		return -1;
	}

	ret = set_pinmux_select(lgphy->pin_mux[idx], regs[0], regs[1]);
	if (ret)
		dev_err(lgphy->dev, "error in pinmux[%d] set\n", idx);

	return ret;
}

int lg1k_usb_phy_set_vbus(struct lg1k_usb_phy *lgphy, int on)
{
	lg1k_usb_phy_set_gpio_pinmux(lgphy, 0);
	lg1k_usb_phy_set_gpio_pinmux(lgphy, 1);

	/*
	 * gpio_request() and gpio_free() should not be called in order to avoid
	 * interference with user space agents.
	 */
	if (lgphy->ctl_gpio >= 0) {
		if (!IS_ENABLED(CONFIG_PINCTRL_LG1K))
			gpio_direction_output(lgphy->ctl_gpio, on);
		gpio_set_value(lgphy->ctl_gpio, on);

		dev_info(lgphy->dev, "vbus turn %s\n", on ? "on" : "off");
	}

	if (on && (lgphy->ocd_gpio >= 0)) {
		if (!IS_ENABLED(CONFIG_PINCTRL_LG1K))
			gpio_direction_input(lgphy->ocd_gpio);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(lg1k_usb_phy_set_vbus);

int lg1k_usb_phy_power_on(struct phy *phy)
{
	struct lg1k_usb_phy *lgphy = phy_get_drvdata(phy);

        dev_dbg(&phy->dev, "request to power_on\n");

	return lg1k_usb_phy_set_vbus(lgphy, true);
}

int lg1k_usb_phy_power_off(struct phy *phy)
{
	struct lg1k_usb_phy *lgphy = phy_get_drvdata(phy);

        dev_dbg(&phy->dev, "request to power_off\n");

	return lg1k_usb_phy_set_vbus(lgphy, false);
}

struct phy *lg1k_usb_phy_xlate(struct device *dev, struct of_phandle_args *args)
{
	struct lg1k_usb_phy *lgphy = dev_get_drvdata(dev);

	if (!lgphy)
		return ERR_PTR(-EINVAL);

	return lgphy->phy;
}

MODULE_DESCRIPTION("LG DTV USB phy controller");
MODULE_AUTHOR("Daewoong Kim <daewoong00.kim@lge.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lg1k-usbphy");
