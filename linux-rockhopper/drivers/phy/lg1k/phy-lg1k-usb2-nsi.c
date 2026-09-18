// SPDX-License-Identifier: GPL-2.0-only
/*
 * LG DTV SoC USB 1.1/2.0 PHY driver
 *
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
 */
#include <linux/clk.h>
#include <linux/mfd/syscon.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/phy/phy.h>
#include <linux/platform_device.h>
#include <linux/spinlock.h>
#include "phy-lg1k-usb-nsi.h"

static int lg1k_usb2_reset(struct lg1k_usb_phy *lgphy)
{
	union usb2_phy_reset_union phy_reset;
	union usb2_host_reset_union host_reset;

	if (!lgphy->phy_reg || !lgphy->host_reg) {
		dev_err(lgphy->dev, "phy reg or host reg is null\n");
		return -EFAULT;
	}
	phy_reset.val = readl(lgphy->phy_reg + phy_offset(2, reset));
	phy_reset.reg.usb2_phy_reset = 0; /* CAUTION: inverse */
	writel(phy_reset.val, lgphy->phy_reg + phy_offset(2, reset));

	/* delay is required between phy_reset and host_reset for some chips */
	usleep_range(1000, 1100);

	host_reset.val = readl(lgphy->host_reg + host_offset(2, reset));
	host_reset.reg.usb2_host_utmi_reset = 1;
	writel(host_reset.val, lgphy->host_reg + host_offset(2, reset));
	host_reset.reg.usb2_host_bus_reset = 1;
	host_reset.reg.usb2_host_core_reset = 1;
	writel(host_reset.val, lgphy->host_reg + host_offset(2, reset));

	return 0;
}

static int lg1k_usb2_init(struct lg1k_usb_phy *lgphy)
{
	if (lgphy->hw_initialized) {
		dev_info(lgphy->dev, "phy is already initialized\n");
		return 0;
	}
	lg1k_usb2_reset(lgphy);
	lgphy->hw_initialized = 1;

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int lg1k_usb2_phy_ctrl_backup(struct lg1k_usb_phy *lgphy)
{
	struct usb2_phy_ctrl_backup *pp;

	if (!lgphy->phy_reg) {
		dev_err(lgphy->dev, "phy reg is null\n");
		return -1;
	}
	dev_dbg(lgphy->dev, "phy ctrl backup\n");

	/* backup phy parameters */
	pp = &lgphy->priv.usb2.phy_ctrl_backup;
	pp->param0 = readl(lgphy->phy_reg + phy_offset(2, param0));
	pp->param1 = readl(lgphy->phy_reg + phy_offset(2, param1));

	return 0;
}

static int lg1k_usb2_phy_ctrl_restore(struct lg1k_usb_phy *lgphy)
{
	struct usb2_phy_ctrl_backup *pp;

	if (!lgphy->phy_reg) {
		dev_err(lgphy->dev, "phy reg is null\n");
		return -1;
	}
	dev_dbg(lgphy->dev, "phy ctrl restore\n");

	/* restore phy parameters */
	pp = &lgphy->priv.usb2.phy_ctrl_backup;
	writel(pp->param0, lgphy->phy_reg + phy_offset(2, param0));
	writel(pp->param1, lgphy->phy_reg + phy_offset(2, param1));

	return 0;
}

static int lg1k_usb2_host_ctrl_backup(struct lg1k_usb_phy *lgphy)
{
	struct usb2_host_ctrl_backup *ph;

	if (!lgphy->host_reg) {
		dev_err(lgphy->dev, "host reg is null\n");
		return -1;
	}
	dev_dbg(lgphy->dev, "host ctrl backup\n");

	/* backup host parameters */
	ph = &lgphy->priv.usb2.host_ctrl_backup;
	ph->param0 = readl(lgphy->host_reg + host_offset(2, param0));

	return 0;
}

static int lg1k_usb2_host_ctrl_restore(struct lg1k_usb_phy *lgphy)
{
	struct usb2_host_ctrl_backup *ph;

	if (!lgphy->host_reg) {
		dev_err(lgphy->dev, "host reg is null\n");
		return -1;
	}
	dev_dbg(lgphy->dev, "host ctrl restore\n");

	/* restore host parameters */
	ph = &lgphy->priv.usb2.host_ctrl_backup;
	writel(ph->param0, lgphy->host_reg + host_offset(2, param0));

	return 0;
}

static int lg1k_usb2_ehci_insnreg_backup(struct lg1k_usb_phy *lgphy)
{
	struct usb2_ehci_insnreg_backup *ei;
	struct device_node *np = lgphy->dev->of_node;

	if (!of_device_is_compatible(np->parent, "lge,lg115x-ehci"))
		return 0;
	if (!lgphy->hc_base) {
		dev_err(lgphy->dev, "error hc base iomem\n");
		return -1;
	}
	dev_dbg(lgphy->dev, "ehci insnregs backup\n");

	/* backup ehci insnregs */
	ei = &lgphy->priv.usb2.ehci_insnreg_backup;
	ei->insnreg01 = readl(lgphy->hc_base + EHCI_INSNREG01);
	ei->insnreg02 = readl(lgphy->hc_base + EHCI_INSNREG02);
	ei->insnreg03 = readl(lgphy->hc_base + EHCI_INSNREG03);

	return 0;
}

static int lg1k_usb2_ehci_insnreg_restore(struct lg1k_usb_phy *lgphy)
{
	struct usb2_ehci_insnreg_backup *ei;
	struct device_node *np = lgphy->dev->of_node;

	if (!of_device_is_compatible(np->parent, "lge,lg115x-ehci"))
		return 0;
	if (!lgphy->hc_base) {
		dev_err(lgphy->dev, "error hc base iomem\n");
		return -1;
	}
	dev_dbg(lgphy->dev, "ehci insnregs restore\n");

	/* restore ehci insnregs */
	ei = &lgphy->priv.usb2.ehci_insnreg_backup;
	writel(ei->insnreg01, lgphy->hc_base + EHCI_INSNREG01);
	writel(ei->insnreg02, lgphy->hc_base + EHCI_INSNREG02);
	writel(ei->insnreg03, lgphy->hc_base + EHCI_INSNREG03);

	return 0;
}


static int lg1k_usb2_suspend_late(struct device *dev)
{
	struct lg1k_usb_phy *lgphy = dev_get_drvdata(dev);

	dev_info(dev, "suspend_late phy\n");
	if (!lgphy) {
		dev_err(dev, "error phy reg iomem\n");
		return -1;
	}

	lg1k_usb2_ehci_insnreg_backup(lgphy);
	lg1k_usb2_phy_ctrl_backup(lgphy);
	lg1k_usb2_host_ctrl_backup(lgphy);
	//lg1k_usb_phy_set_vbus(lgphy, false);

	lgphy->hw_initialized = 0;

	return 0;
}

static int lg1k_usb2_resume(struct device *dev)
{
	struct lg1k_usb_phy *lgphy = dev_get_drvdata(dev);

	dev_info(dev, "resume phy\n");
	if (!lgphy) {
		dev_err(dev, "lgphy is null\n");
		return -1;
	}
	if (lgphy->hw_initialized) {
		dev_info(lgphy->dev, "phy is already initialized\n");
		return 0;
	}
	lg1k_usb2_host_ctrl_restore(lgphy);
	lg1k_usb2_phy_ctrl_restore(lgphy);

	lg1k_usb2_reset(lgphy);
	lg1k_usb2_ehci_insnreg_restore(lgphy);

	//usleep_range(10000, 10100);
	//lg1k_usb_phy_set_vbus(lgphy, true);

	lgphy->hw_initialized = 1;

	return 0;
}

static int lg1k_usb2_resume_early(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops lg1k_usb2_pm_ops = {
	.resume = lg1k_usb2_resume,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(lg1k_usb2_suspend_late,
			lg1k_usb2_resume_early)
};
#define DEV_PM_OPS	(&lg1k_usb2_pm_ops)
#else
#define DEV_PM_OPS	NULL
#endif /* CONFIG_PM_SLEEP */

__maybe_unused
static int lg1k_usb2_phy_init(struct phy *phy)
{
	struct lg1k_usb_phy *lgphy = phy_get_drvdata(phy);

	return lg1k_usb2_init(lgphy);
}

static const struct lg1k_usb_phy_data lg1k_usb2_phy_nsi_data = {
	.label		= "usb2-nanosilicon"
};

static const struct phy_ops lg1k_usb2_phy_nsi_ops = {
	.power_on	= lg1k_usb_phy_power_on,
	.power_off	= lg1k_usb_phy_power_off,
	.owner		= THIS_MODULE,
};

static const struct of_device_id lg1k_usb2_phy_of_match[] = {
	{
		.compatible = "lge,lg1k-usb2-phy-nsi",
		.data = &lg1k_usb2_phy_nsi_data,
	},
	{ },
};
MODULE_DEVICE_TABLE(of, lg1k_usb2_phy_of_match);

static int lg1k_usb2_phy_nsi_probe(struct platform_device *pdev)
{
	const struct lg1k_usb_phy_data *data;
	struct lg1k_usb2_phy_nsi *priv;
	struct lg1k_usb_phy *lgphy;
	struct phy *phy;
	struct device *dev = &pdev->dev;
	struct phy_provider *phy_provider;

	if (!dev->of_node) {
		dev_err(dev, "device tree is required\n");
		return -EINVAL;
	}

	data = of_device_get_match_data(dev);
	if (!data)
		return -EINVAL;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;
	lgphy = &priv->lgphy;
	lgphy->dev = dev;
	lgphy->id = pdev->id;

	dev_set_drvdata(dev, lgphy);
	spin_lock_init(&lgphy->lock);
	lg1k_usb_phy_parse_dt(lgphy);

	dev_dbg(dev, "creating phy\n");
	phy = lgphy->phy = devm_phy_create(dev, NULL, &lg1k_usb2_phy_nsi_ops);
	if (IS_ERR(phy)) {
		dev_err(dev, "failed to create phy\n");
		return PTR_ERR(phy);
	}
	phy_set_drvdata(phy, lgphy);

	phy_provider = devm_of_phy_provider_register(dev, lg1k_usb_phy_xlate);
	if (IS_ERR(phy_provider)) {
		dev_err(dev, "failed to register phy provider\n");
		return PTR_ERR(phy_provider);
	}

	return 0;
}

static struct platform_driver lg1k_usb2_phy_nsi_driver = {
	.probe	= lg1k_usb2_phy_nsi_probe,
	.driver = {
		.of_match_table	= lg1k_usb2_phy_of_match,
		.name		= "lg1k-usb2-phy-nsi",
		.pm		= DEV_PM_OPS,
		.suppress_bind_attrs = true,
	}
};

module_platform_driver(lg1k_usb2_phy_nsi_driver);
MODULE_DESCRIPTION("LG DTV SoC USB 2.0 PHY Nanosilicon driver");
MODULE_AUTHOR("Daewoong Kim <daewoong00.kim@lge.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lg1k-usb2-phy-nsi");
