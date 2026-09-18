#include <linux/kernel.h>

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/phy.h>

#define PHYID_RTL8211E	0x001cc915
#define PHYID_RTL8211F	0x001cc916

#define ZQ_CAL_TIMEOUT	8

/* imported from drivers/net/phy/omniphy.c */
struct omniphy_priv {
	struct list_head list;
	struct phy_device *phydev;
	int off_gpio;	/* gpios-index to disable omniphy (-1 for none) */
	int wol_gpio;	/* gpios-index to isolate omniphy (-1 for none) */
	int release_gpio;
	struct gpio_desc *gpios[0];
};

int lge_lg1k_arch_reset(struct phy_device *phydev, int enable);

static int lge_lg1k_rev1_fixup_run(struct phy_device *phydev)
{
	int max_trial = 4;
	int v;

	while (max_trial--) {
		genphy_soft_reset(phydev);

		/* page 3 */
		phy_write(phydev, 0x1f, 0x0003);
		/* RX_REG power OFF */
		phy_write(phydev, 0x10, 0x0008);
		/* RXADC digital logic OFF */
		phy_write(phydev, 0x14, 0x0500);
		/* RX_REG power ON */
		phy_write(phydev, 0x10, 0x0000);
		/* wait stabilized */
		mdelay(10);
		/* RXADC digital logic ON and
		 * RX_V1 ADC input clock inversion ON */
		phy_write(phydev, 0x14, 0x5500);

		genphy_soft_reset(phydev);

		/* page 3 */
		phy_write(phydev, 0x1f, 0x0003);
		phy_write(phydev, 0x14, 0x57b3);
		phy_write(phydev, 0x13, 0x0c55);

		/* page 2 */
		phy_write(phydev, 0x1f, 0x0002);
		phy_write(phydev, 0x1b, 0xfc02);
		phy_write(phydev, 0x1a, 0x0008);
		v = phy_read(phydev, 0x1e);
		if (v & 0x0001) {
			dev_info(&phydev->mdio.dev, "PLL okay\n");
		} else {
			dev_info(&phydev->mdio.dev, "PLL failed\n");
			phy_write(phydev, 0x1b, 0x4451);
			phy_write(phydev, 0x1d, 0x2281);
			continue;
		}

		/* page 9 */
		phy_write(phydev, 0x1f, 0x0009);
		/* check if RXCLK generation is okay */
		v = phy_read(phydev, 0x10);
		if (v) {
			dev_info(&phydev->mdio.dev, "RXCLK okay\n");
			break;
		} else {
			dev_info(&phydev->mdio.dev, "RXCLK failed\n");
		}
	}

	/* page 1 */
	phy_write(phydev, 0x1f, 0x0001);
	phy_write(phydev, 0x11, 0xf777);
	phy_write(phydev, 0x12, 0xbbb3);
	phy_write(phydev, 0x13, 0x3d59);
	phy_write(phydev, 0x14, 0x1000);
	phy_write(phydev, 0x15, 0x0053);
	/* page 0 */
	phy_write(phydev, 0x1f, 0x0000);

	return genphy_config_aneg(phydev);
}

static int lge_lg1k_rev2_fixup_run(struct phy_device *phydev)
{
	int max_trial = 4;
	int v;
	static void __iomem *base;

	while (max_trial--) {
		genphy_soft_reset(phydev);

		/* page 10 */
		phy_write(phydev, 0x1f, 0x000a);
		phy_write(phydev, 0x10, 0x0604);
		phy_write(phydev, 0x15, 0x02c4);
		phy_write(phydev, 0x16, 0x0260);
		phy_write(phydev, 0x17, 0x0222);
		phy_write(phydev, 0x1d, 0x1e24);
		phy_write(phydev, 0x1e, 0x292d);

		/* page 1 */
		phy_write(phydev, 0x1f, 0x0001);
		phy_write(phydev, 0x15, 0x0052);

		/* page 3 */
		phy_write(phydev, 0x1f, 0x0003);
		phy_write(phydev, 0x14, 0x57b3);
		phy_write(phydev, 0x13, 0x0c55);
		phy_write(phydev, 0x15, 0xa431);
		phy_write(phydev, 0x16, 0xddcb);

		/* page 9 */
		phy_write(phydev, 0x1f, 0x0009);
		phy_write(phydev, 0x12, 0x010c);
		phy_write(phydev, 0x12, 0x0108);

		/* page 2 */
		phy_write(phydev, 0x1f, 0x0002);
		phy_write(phydev, 0x1b, 0xfc02);
		phy_write(phydev, 0x1a, 0x0008);
		v = phy_read(phydev, 0x1e);
		if (v & 0x0001) {
			dev_info(&phydev->mdio.dev, "PLL okay\n");
		} else {
			dev_info(&phydev->mdio.dev, "PLL failed\n");

			/* LG1315-specific workaround */

			if (!base)
				base = ioremap(0xf3514000, 0x1000);

			v = readl_relaxed(base + 0x0030);
			if ((v & 0x00f0) < 0x0080)
				writel_relaxed(v + 0x0080, base + 0x0030);
			else
				writel_relaxed(v | 0x00f0, base + 0x0030);
			mdelay(1);
			phy_modify(phydev, MII_BMCR, 0, BMCR_PDOWN);
			mdelay(15);
			phy_modify(phydev, MII_BMCR, BMCR_PDOWN, 0);
			udelay(300);
			writel_relaxed(v, base + 0x0030);
			mdelay(1);
			continue;
		}

		/* page 9 */
		phy_write(phydev, 0x1f, 0x0009);
		/* check if RXCLK generation is okay */
		v = phy_read(phydev, 0x10);
		if (v) {
			dev_info(&phydev->mdio.dev, "RXCLK okay\n");
			break;
		} else {
			dev_info(&phydev->mdio.dev, "RXCLK failed\n");
		}
	}

	/* page 1 */
	phy_write(phydev, 0x1f, 0x0001);
	phy_write(phydev, 0x11, 0xf777);
	phy_write(phydev, 0x12, 0xbbb3);
	phy_write(phydev, 0x13, 0x3d59);
	phy_write(phydev, 0x14, 0x1000);
	phy_write(phydev, 0x15, 0x0052);
	/* page 0 */
	phy_write(phydev, 0x1f, 0x0000);

	return genphy_config_aneg(phydev);
}

static int lge_lg1k_rev3_fixup_run(struct phy_device *phydev)
{
	int max_trial = 4;
	int v;

	while (max_trial--) {
		genphy_soft_reset(phydev);

		phy_write(phydev, 0x13, 0x0005);	/* 10T_CTRL */

		phy_write(phydev, 0x1f, 0x000a);	/* page 10 */
		phy_write(phydev, 0x10, 0x0604);	/* energy on level */
		phy_write(phydev, 0x15, 0x02c4);	/* amp thr3 */
		phy_write(phydev, 0x16, 0x0260);	/* amp thr4 */
		phy_write(phydev, 0x17, 0x0222);	/* amp thr5 */
		phy_write(phydev, 0x1d, 0x1e24);	/* DACG0 */
		phy_write(phydev, 0x1e, 0x2d31);	/* DACG1 */

		phy_write(phydev, 0x1f, 0x0001);	/* page 1 */
		phy_write(phydev, 0x15, 0x0052);	/* ZQcal TX5 */

		phy_write(phydev, 0x1f, 0x0003);	/* page 3 */
		phy_write(phydev, 0x11, 0x00e8);	/* squelch level */
		phy_write(phydev, 0x14, 0x57b3);
		phy_write(phydev, 0x15, 0xa431);	/* RXGAIN set */
		phy_write(phydev, 0x16, 0xddcb);

		phy_write(phydev, 0x1f, 0x0009);	/* page 9 */
		phy_write(phydev, 0x12, 0x010c);	/* AGC reset */
		phy_write(phydev, 0x12, 0x0108);

		phy_write(phydev, 0x1f, 0x0002);	/* page 2 */
		phy_write(phydev, 0x1b, 0xfc02);	/* RX Bias increase */
		phy_write(phydev, 0x1a, 0x0008);

		v = phy_read(phydev, 0x1e);
		if (v & 0x0001) {
			dev_info(&phydev->mdio.dev, "PLL okay\n");
		} else {
			dev_info(&phydev->mdio.dev, "PLL failed\n");

			phy_write(phydev, 0x1b, 0xfd42); /* PPLPD enable */
			udelay(100);
			phy_write(phydev, 0x1b, 0xfc02); /* PPLPD disable */
			udelay(100);
			/* EPHY CRG reset */
			lge_lg1k_arch_reset(phydev, 1);
			mdelay(2);
			lge_lg1k_arch_reset(phydev, 0);
			mdelay(2);
			continue;
		}

		phy_write(phydev, 0x1f, 0x0009);	/* page 9 */
		/* check if RXCLK generation is okay */
		v = phy_read(phydev, 0x10);
		if (v) {
			dev_info(&phydev->mdio.dev, "RXCLK okay\n");
			break;
		} else {
			dev_info(&phydev->mdio.dev, "RXCLK failed\n");
		}
	}

	phy_write(phydev, 0x1f, 0x0000);		/* page 0 */

	return genphy_config_aneg(phydev);
}

static int lge_lg1k_rev4_fixup_run(struct phy_device *phydev)
{
	int max_trial = 4;
	int v;

	while (max_trial--) {
		genphy_soft_reset(phydev);

		phy_write(phydev, 0x13, 0x0005);	/* 10T_CTRL */

		phy_write(phydev, 0x1f, 0x000a);	/* page 10 */
		phy_write(phydev, 0x17, 0x0222);	/* amp thr5 */
		phy_write(phydev, 0x1d, 0x1e24);	/* DACG0 */
		phy_write(phydev, 0x1e, 0x292d);	/* DACG1 */

		phy_write(phydev, 0x1f, 0x0001);	/* page 1 */
		phy_write(phydev, 0x15, 0x003e);	/* ZQcal TX5 */
		phy_write(phydev, 0x11, 0x3333);	/* RXterm */
		phy_write(phydev, 0x12, 0x3333);
		phy_write(phydev, 0x13, 0x3333);
		phy_write(phydev, 0x14, 0x3333);

		phy_write(phydev, 0x1f, 0x0003);	/* page 3 */
		phy_write(phydev, 0x11, 0x00e8);	/* squelch level */
		phy_write(phydev, 0x13, 0x0b13);	/* ADC bias */
		phy_write(phydev, 0x14, 0x14c3);
		phy_write(phydev, 0x15, 0xa431);	/* RXGAIN set */
		phy_write(phydev, 0x16, 0xddcb);

		phy_write(phydev, 0x1f, 0x0009);	/* page 9 */
		phy_write(phydev, 0x12, 0x010c);	/* AGC reset */
		phy_write(phydev, 0x12, 0x0108);

		phy_write(phydev, 0x1f, 0x0002);	/* page 2 */
		phy_write(phydev, 0x11, 0x0161);	/* TX */
		phy_write(phydev, 0x12, 0x8240);
		phy_write(phydev, 0x13, 0x04c0);
		phy_write(phydev, 0x1b, 0xfc02);	/* RX Bias increase */
		phy_write(phydev, 0x1a, 0x0008);

		v = phy_read(phydev, 0x1e);
		if (v & 0x0001) {
			dev_info(&phydev->mdio.dev, "PLL okay\n");
		} else {
			dev_info(&phydev->mdio.dev, "PLL failed\n");

			phy_write(phydev, 0x1b, 0xfd42); /* PPLPD enable */
			udelay(100);
			phy_write(phydev, 0x1b, 0xfc02); /* PPLPD disable */
			udelay(100);
			/* EPHY CRG reset */
			lge_lg1k_arch_reset(phydev, 1);
			mdelay(2);
			lge_lg1k_arch_reset(phydev, 0);
			mdelay(2);
			continue;
		}

		phy_write(phydev, 0x1f, 0x0009);	/* page 9 */
		/* check if RXCLK generation is okay */
		v = phy_read(phydev, 0x10);
		if (v) {
			dev_info(&phydev->mdio.dev, "RXCLK okay\n");
			break;
		} else {
			dev_info(&phydev->mdio.dev, "RXCLK failed\n");
		}
	}

	phy_write(phydev, 0x1f, 0x0000);		/* page 0 */

	return genphy_config_aneg(phydev);
}

static int omniphy_fixup_run(struct phy_device *phydev)
{
	int i = 0;
	int v;

	/* enable access to Analog and DSP register bank */
	phy_write(phydev, 0x14, 0x0400);
	phy_write(phydev, 0x14, 0x0000);
	phy_write(phydev, 0x14, 0x0400);

	/* apply some Tx-tuning values */
	if (of_machine_is_compatible("lge,lg1211") ||
	    of_machine_is_compatible("lge,lg1313c0") ||
	    of_machine_is_compatible("lge,lg1314")) {
		/* start ZQ calibration */
		phy_write(phydev, 0x17, 0x0001);
		phy_write(phydev, 0x14, 0x7800);
		/* wait for zq_cal_done */
		for (i = 0; i < ZQ_CAL_TIMEOUT; i++) {
			phy_write(phydev, 0x14, 0xb820);
			v = phy_read(phydev, 0x15);
			if (v & 0x0001)
				break;
		}
		/* adjust 100BT amplitude */
		phy_write(phydev, 0x17, 0xe000);
		phy_write(phydev, 0x14, 0x441c);
		/* adjust 10BT amplitude */
		phy_write(phydev, 0x17, 0x002f);
		phy_write(phydev, 0x14, 0x4418);
	} else if (of_machine_is_compatible("lge,lg1313")) {
		phy_write(phydev, 0x17, 0x804e);
		phy_write(phydev, 0x14, 0x4416);
		phy_write(phydev, 0x17, 0x3c00);
		phy_write(phydev, 0x14, 0x4417);
		phy_write(phydev, 0x17, 0x0036);
		phy_write(phydev, 0x14, 0x4418);
		phy_write(phydev, 0x17, 0x1000);
		phy_write(phydev, 0x14, 0x441c);
	}

	dev_info(&phydev->mdio.dev, "Tx-tuning applied\n");

	return 0;
}

static int sunplus_fixup_run(struct phy_device *phydev)
{
	/* page 8 */
	phy_write(phydev, 0x1f, 0x0800);
	/* fine-tune for Tx impedence */
	phy_write(phydev, 0x18, 0x00bc);
	/* bypass Tx level */
	phy_write(phydev, 0x1d, 0x0844);
	/* page 6 */
	phy_write(phydev, 0x1f, 0x0600);
	/* inverse internal sample clock & Rx tune */
	phy_write(phydev, 0x19, 0x000c);
	/* clock selection & Tx amp. adjust */
	if (of_machine_is_compatible("lge,lg1811"))
		phy_write(phydev, 0x15, 0x3410);
	else
		phy_write(phydev, 0x15, 0x3232);
	/* PLL parameter for 50MHz XTAL input */
	phy_write(phydev, 0x17, 0x0545);
	/* tune for MDI Tx driver */
	phy_write(phydev, 0x13, 0xa000);
	/* tune for MDI-X Tx driver */
	phy_write(phydev, 0x14, 0x708a);
	/* page 1 */
	phy_write(phydev, 0x1f, 0x0100);
	/* disable auto power-save */
	phy_write(phydev, 0x12, 0x4824);
	/* page 0 */
	phy_write(phydev, 0x1f, 0x0000);

	return 0;
}

static int rtl8201_fixup_run(struct phy_device *phydev)
{
	/* adjust RMII mode setting */
	phy_write(phydev, 0x1f, 0x0007);
	phy_write(phydev, 0x10, 0x077a);

	/* return to page 0 */
	phy_write(phydev, 0x1f, 0x0000);

	return 0;
}

static int rtl8211_fixup_run(struct phy_device *phydev)
{
	switch (phydev->phy_id) {
	case PHYID_RTL8211E:
		/* set to extention page */
		phy_write(phydev, 0x1f, 0x0007);
		/* set to extention page 164 */
		phy_write(phydev, 0x1e, 0x00a4);
		/* adjust RGMII drive strength */
		phy_write(phydev, 0x1c, 0x85ff);
		break;

	case PHYID_RTL8211F:
		/* set to page 0x0d41 */
		phy_write(phydev, 0x1f, 0x0d41);
		/* adjust RGMII drive strength */
		phy_write(phydev, 0x11, 0x5524);
		break;

	default:
		dev_warn(&phydev->mdio.dev, "unknown PHY ID: %08x\n",
			 phydev->phy_id);
		break;
	}

	/* back to page 0 */
	phy_write(phydev, 0x1f, 0x0000);

	return 0;
}

static int omniphy_lg1211_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* soft-reset */
		base = ioremap(0xc7501000, 0x1000);

	v = readl_relaxed(base + 0x0004);
	if (enable)
		v |= 0x00000101;
	else
		v &= 0xfffffefe;
	writel_relaxed(v, base + 0x0004);

	return 0;
}

static int omniphy_lg1313_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* soft-reset */
		base = ioremap(0xc3501000, 0x1000);

	v = readl_relaxed(base + 0x0004);
	if (enable)
		v |= 0x00000404;
	else
		v &= 0xfffffbfb;
	writel_relaxed(v, base + 0x0004);

	return 0;
}

static int omniphy_lg1313c0_reset(struct phy_device *phydev, int enable)
{
	struct omniphy_priv *priv = phydev->priv;
	static void __iomem *base[2];
	u32 v;

	if (!base[0])	/* pinmux */
		base[0] = ioremap(0xc9305000, 0x1000);
	if (!base[1])	/* GPIO39 */
		base[1] = ioremap(0xfd440000, 0x1000);

	if (!enable) {
		/* ensure not isolated before releasing reset */
		if (priv->wol_gpio >= 0 && priv->gpios[priv->wol_gpio]) {
			/* pinmux to use GPIO39 */
			v = readl_relaxed(base[0] + 0x0410) | 0x80000000;
			writel_relaxed(v, base[0] + 0x0410);
			v = readl_relaxed(base[0] + 0x0424) | 0x08000000;
			writel_relaxed(v, base[0] + 0x0424);

			/* GPIO39 to high-output */
			v = readb_relaxed(base[1] + 0x0400) | 0x80;
			writeb_relaxed(v, base[1] + 0x0400);
			writeb_relaxed(0x80, base[1] + 0x0200);
		}
	}

	return omniphy_lg1313_reset(phydev, enable);
}

static int omniphy_lg1314_reset(struct phy_device *phydev, int enable)
{
	struct omniphy_priv *priv = phydev->priv;
	static void __iomem *base[3];
	u32 v;

	if (!base[0])	/* soft-reset */
		base[0] = ioremap(0xc3501000, 0x1000);
	if (!base[1])	/* direct IRQ */
		base[1] = ioremap(0xc37c0000, 0x1000);
	if (!base[2])	/* GPIO[141..142] */
		base[2] = ioremap(0xfd510000, 0x1000);

	if (!enable) {
		/* ensure not isolated before releasing reset */
		if (priv->off_gpio < 0 || !priv->gpios[priv->off_gpio] ||
		    priv->wol_gpio < 0 || !priv->gpios[priv->wol_gpio]) {
			/* GPIO141 and GPIO142 to high-output */
			v = readb_relaxed(base[2] + 0x0400) | 0x60;
			writeb_relaxed(v, base[2] + 0x0400);
			writeb_relaxed(0x60, base[2] + 0x0180);
		}

		/* direct omniphy interrupt to CPU */
		v = readl_relaxed(base[1] + 0x0060) & 0xfffffffe;
		writel_relaxed(v, base[1] + 0x0060);
	}

	/* assert or deassert reset */
	v = readl_relaxed(base[0] + 0x000c);
	if (enable)
		v |= 0x00001002;
	else
		v &= 0xffffeffd;
	writel_relaxed(v, base[0] + 0x000c);

	return 0;
}

int omniphy_arch_reset(struct phy_device *phydev, int enable)
{
	static int (*arch_reset_func)(struct phy_device *, int);

	if (enable)
		dev_info(&phydev->mdio.dev, "hard-reset by CTOP\n");

	if (!arch_reset_func) {
		if (of_machine_is_compatible("lge,lg1211"))
			arch_reset_func = omniphy_lg1211_reset;
		if (of_machine_is_compatible("lge,lg1313"))
			arch_reset_func = omniphy_lg1313_reset;
		if (of_machine_is_compatible("lge,lg1313c0"))
			arch_reset_func = omniphy_lg1313c0_reset;
		if (of_machine_is_compatible("lge,lg1314"))
			arch_reset_func = omniphy_lg1314_reset;
	}

	return arch_reset_func ? arch_reset_func(phydev, enable) : 0;
}
EXPORT_SYMBOL(omniphy_arch_reset);

static int sunplus_lg1212_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* soft-reset */
		base = ioremap(0xc3301000, 0x1000);

	v = readl_relaxed(base + 0x0004);
	if (enable)
		v |= 0x00000020;
	else
		v &= 0xffffffdf;
	writel_relaxed(v, base + 0x0004);

	return 0;
}

static int sunplus_lg1811_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* soft-reset */
		base = ioremap(0xf3018000, 0x1000);

	v = readl_relaxed(base + 0x0004);
	if (enable)
		v |= 0x00000010;
	else
		v &= 0xffffffef;
	writel_relaxed(v, base + 0x0004);

	return 0;
}

int sunplus_arch_reset(struct phy_device *phydev, int enable)
{
	static int (*arch_reset_func)(struct phy_device *, int);

	if (enable)
		dev_info(&phydev->mdio.dev, "hard-reset by CTOP\n");

	if (!arch_reset_func) {
		if (of_machine_is_compatible("lge,lg1212"))
			arch_reset_func = sunplus_lg1212_reset;
		if (of_machine_is_compatible("lge,lg1811"))
			arch_reset_func = sunplus_lg1811_reset;
	}

	return arch_reset_func ? arch_reset_func(phydev, enable) : 0;
}
EXPORT_SYMBOL(sunplus_arch_reset);

static int sunplus_lg1212_isolate(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* isolate */
		base = ioremap(0xc3300000, 0x1000);

	v = readl_relaxed(base + 0x0820);
	if (enable)
		v &= 0xffffffef;
	else
		v |= 0x00000010;
	writel_relaxed(v, base + 0x0820);

	return 0;
}

static int sunplus_lg1811_isolate(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* isolate */
		base = ioremap(0xf3011000, 0x1000);

	v = readl_relaxed(base + 0x04f4);
	if (enable)
		v &= 0xfffffffe;
	else
		v |= 0x00000001;
	writel_relaxed(v, base + 0x04f4);

	return 0;
}

int sunplus_arch_isolate(struct phy_device *phydev, int enable)
{
	static int (*arch_isolate_func)(struct phy_device *, int);

	if (!arch_isolate_func) {
		if (of_machine_is_compatible("lge,lg1212"))
			arch_isolate_func = sunplus_lg1212_isolate;
		if (of_machine_is_compatible("lge,lg1811"))
			arch_isolate_func = sunplus_lg1811_isolate;
	}

	return arch_isolate_func ? arch_isolate_func(phydev, enable) : 0;
}

static int sunplus_lg1212_shutdown(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* shutdown */
		base = ioremap(0xf0004000, 0x1000);

	v = readl_relaxed(base + 0x0058);
	if (enable)
		v |= 0x00000001;
	else
		v &= 0xfffffffe;
	writel_relaxed(v, base + 0x0058);

	return 0;
}

static int sunplus_lg1811_shutdown(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* shutdown */
		base = ioremap(0xf0004000, 0x1000);

	v = readl_relaxed(base + 0x0058);
	if (enable)
		v |= 0x00000001;
	else
		v &= 0xfffffffe;
	writel_relaxed(v, base + 0x0058);

	return 0;
}

int sunplus_arch_shutdown(struct phy_device *phydev, int enable)
{
	static int (*arch_shutdown_func)(struct phy_device *, int);

	if (!arch_shutdown_func) {
		if (of_machine_is_compatible("lge,lg1212"))
			arch_shutdown_func = sunplus_lg1212_shutdown;
		if (of_machine_is_compatible("lge,lg1811"))
			arch_shutdown_func = sunplus_lg1811_shutdown;
	}

	return arch_shutdown_func ? arch_shutdown_func(phydev, enable) : 0;
}

static int lge_lg1k_lg1213_isolate(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xf30d5000, 0x1000);

	v = readl_relaxed(base + 0x0200);
	if (enable)
		dev_warn(&phydev->mdio.dev, "differed isolation\n");
	else
		v |= 0x00000004;
	writel_relaxed(v, base + 0x0200);

	return 0;
}

int lge_lg1k_arch_isolate(struct phy_device *phydev, int enable)
{
	static int (*arch_isolate_func)(struct phy_device *, int);

	if (!arch_isolate_func) {
		if (of_machine_is_compatible("lge,lg1213"))
			arch_isolate_func = lge_lg1k_lg1213_isolate;
	}

	return arch_isolate_func ? arch_isolate_func(phydev, enable) : 0;
}

static int lge_lg1k_lg1213_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xc4110000, 0x1000);

	v = readl_relaxed(base + 0x000c);
	if (enable)
		v |= 0x00000004;
	else
		v &= 0xfffffffb;
	writel_relaxed(v, base + 0x000c);

	return 0;
}

static int lge_lg1k_lg1214_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xc8850000, 0x1000);

	v = readl_relaxed(base + 0x000c);
	if (enable)
		v |= 0x00000004;
	else
		v &= 0xfffffffb;
	writel_relaxed(v, base + 0x000c);

	return 0;
}

static int lge_lg1k_lg1215_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xf3380000, 0x1000);

	v = readl_relaxed(base + 0x000c);
	if (enable)
		v |= 0x00000004;
	else
		v &= 0xfffffffb;
	writel_relaxed(v, base + 0x000c);

	return 0;
}

static int lge_lg1k_lg1315_reset(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xf3150000, 0x1000);

	v = readl_relaxed(base + 0x000c);
	if (enable)
		v |= 0x00000004;
	else
		v &= 0xfffffffb;
	writel_relaxed(v, base + 0x000c);

	return 0;
}

int lge_lg1k_arch_reset(struct phy_device *phydev, int enable)
{
	static int (*arch_reset_func)(struct phy_device *, int);

	if (enable)
		dev_info(&phydev->mdio.dev, "hard-reset by CTOP\n");

	if (!arch_reset_func) {
		if (of_machine_is_compatible("lge,lg1213"))
			arch_reset_func = lge_lg1k_lg1213_reset;
		if (of_machine_is_compatible("lge,lg1214"))
			arch_reset_func = lge_lg1k_lg1214_reset;
		if (of_machine_is_compatible("lge,lg1215"))
			arch_reset_func = lge_lg1k_lg1215_reset;
		if (of_machine_is_compatible("lge,lg1315"))
			arch_reset_func = lge_lg1k_lg1315_reset;
	}

	return arch_reset_func ? arch_reset_func(phydev, enable) : 0;
}

static int lge_lg1k_lg1213_shutdown(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xf0004000, 0x1000);

	v = readl_relaxed(base + 0x0058);
	if (enable) {
		/* page 3 */
		phy_write(phydev, 0x1f, 0x0003);
		phy_write(phydev, 0x10, 0x000e);
		phy_write(phydev, 0x11, 0x00af);
		phy_write(phydev, 0x12, 0x6043);
		phy_write(phydev, 0x14, 0x0500);
		phy_write(phydev, 0x1c, 0x0007);
		/* page 2 */
		phy_write(phydev, 0x1f, 0x0002);
		phy_write(phydev, 0x10, 0x01a5);
		phy_write(phydev, 0x1b, 0x4451);
		phy_write(phydev, 0x1d, 0x2281);
		phy_write(phydev, 0x1a, 0x8015);

		v |= 0x00000001;
	} else {
		v &= 0xfffffffe;
	}
	writel_relaxed(v, base + 0x0058);

	return 0;
}

static int lge_lg1k_lg1214_shutdown(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xc8862000, 0x1000);

	v = readl_relaxed(base + 0x0010);
	if (enable)
		v |= 0x00000001;
	else
		v &= 0xfffffffe;
	writel_relaxed(v, base + 0x0010);

	return 0;
}

static int lge_lg1k_lg1215_shutdown(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xf0004000, 0x1000);

	v = readl_relaxed(base + 0x0058);
	if (enable)
		v |= 0x00000001;
	else
		v &= 0xfffffffe;
	writel_relaxed(v, base + 0x0058);

	return 0;
}

static int lge_lg1k_lg1315_shutdown(struct phy_device *phydev, int enable)
{
	static void __iomem *base;
	u32 v;

	if (!base)
		base = ioremap(0xf0004000, 0x1000);

	v = readl_relaxed(base + 0x0058);
	if (enable)
		v |= 0x00000001;
	else
		v &= 0xfffffffe;
	writel_relaxed(v, base + 0x0058);

	return 0;
}

int lge_lg1k_arch_shutdown(struct phy_device *phydev, int enable)
{
	static int (*arch_shutdown_func)(struct phy_device *, int);

	if (!arch_shutdown_func) {
		if (of_machine_is_compatible("lge,lg1213"))
			arch_shutdown_func = lge_lg1k_lg1213_shutdown;
		if (of_machine_is_compatible("lge,lg1214"))
			arch_shutdown_func = lge_lg1k_lg1214_shutdown;
		if (of_machine_is_compatible("lge,lg1215"))
			arch_shutdown_func = lge_lg1k_lg1215_shutdown;
		if (of_machine_is_compatible("lge,lg1315"))
			arch_shutdown_func = lge_lg1k_lg1315_shutdown;
	}

	return arch_shutdown_func ? arch_shutdown_func(phydev, enable) : 0;
}

static int omniphy_lg1314_config_intr(struct phy_device *phydev)
{
	static void __iomem *base;
	u32 v;

	if (!base)	/* IRQ route */
		base = ioremap(0xc37c0000, 0x1000);

	v = readl_relaxed(base + 0x0060);
	if (phydev->interrupts == PHY_INTERRUPT_DISABLED)
		v |= 0x00000001;	/* Micom */
	else
		v &= 0xfffffffe;	/* CPU */
	writel_relaxed(v, base + 0x0060);

	return 0;
}

int omniphy_arch_config_intr(struct phy_device *phydev)
{
	static int (*arch_config_intr_func)(struct phy_device *);

	if (!arch_config_intr_func) {
		if (of_machine_is_compatible("lge,lg1314"))
			arch_config_intr_func = omniphy_lg1314_config_intr;
	}

	return arch_config_intr_func ? arch_config_intr_func(phydev) : 0;
}
EXPORT_SYMBOL(omniphy_arch_config_intr);

int omniphy_arch_init(struct phy_device *phydev)
{
	struct omniphy_priv *priv = phydev->priv;

	if (of_machine_is_compatible("lge,lg1313c0")) {
		priv->off_gpio = -1;
		if (priv->gpios[2]) {
			if (gpiod_get_value(priv->gpios[2])) {
				priv->wol_gpio = 1;
				priv->release_gpio = 0;
				gpiod_put(priv->gpios[0]);
				priv->gpios[0] = NULL;
			} else {
				/*
				 * Early version of LG1313 rev.C0 board has
				 * a unified GPIO to control multiple devices.
				 * This is faulty and give up WOL to support
				 * another (major) device. Release PHY-
				 * isolation GPIO just after initial
				 * de-isolation in omniphy_soft_reset().
				 */
				priv->wol_gpio = 0;
				priv->release_gpio = 1;
				gpiod_put(priv->gpios[1]);
				priv->gpios[1] = NULL;
			}
			gpiod_put(priv->gpios[2]);
			priv->gpios[2] = NULL;
		} else {
			priv->wol_gpio = 0;
			priv->release_gpio = 0;
		}
	} else if (of_machine_is_compatible("lge,lg1314")) {
		priv->off_gpio = 1;
		priv->wol_gpio = 0;
		priv->release_gpio = 0;
	} else {
		priv->off_gpio = -1;
		priv->wol_gpio = 0;
		priv->release_gpio = 0;
	}

	return 0;
}
EXPORT_SYMBOL(omniphy_arch_init);

static int rtl8211_lg1212_init(struct phy_device *phydev)
{
	static void __iomem *base[2];

	if (!base[0])
		base[0] = ioremap(0xc930e000, 0x1000);

	/* adjust RGMII Tx drive strength */
	writel_relaxed(0x00101000, base[0] + 0x04d4);
	writel_relaxed(0x00101000, base[0] + 0x04d8);
	writel_relaxed(0x00101000, base[0] + 0x04dc);
	writel_relaxed(0x00101000, base[0] + 0x04e0);
	writel_relaxed(0x00101000, base[0] + 0x04e4);
	writel_relaxed(0x00101000, base[0] + 0x04e8);

	if (!base[1])
		base[1] = ioremap(0xc3780000, 0x1000);

	/* switch to RGMII interface */
	writel_relaxed(0x00000001, base[1] + 0x0008);

	return 0;
}

static int rtl8211_lg1213_init(struct phy_device *phydev)
{
	static void __iomem *base;

	if (!base)
		base = ioremap(0xcc332000, 0x1000);

	/*
	 * Tx pad drive strength adjustment (max)
	 * Rx pad schmitt trigger control
	 */
	writel_relaxed(0x414f4f4f, base + 0x0008);
	writel_relaxed(0x004f4f4f, base + 0x000c);

	return 0;
}

static int rtl8211_lg1811_init(struct phy_device *phydev)
{
	static void __iomem *base;

	if (!base)
		base = ioremap(0xc9394000, 0x1000);

	/*
	 * Tx pad drive strength adjustment (max)
	 * Rx pad schmitt trigger control
	 */
	writel_relaxed(0xa1606060, base + 0x041c);
	writel_relaxed(0xa0606969, base + 0x0420);
	writel_relaxed(0x69696969, base + 0x0424);

	return 0;
}

int rtl8211_arch_init(struct phy_device *phydev)
{
	static int (*arch_init_func)(struct phy_device *);

	if (of_machine_is_compatible("lge,lg1212"))
		arch_init_func = rtl8211_lg1212_init;
	if (of_machine_is_compatible("lge,lg1213"))
		arch_init_func = rtl8211_lg1213_init;
	if (of_machine_is_compatible("lge,lg1811"))
		arch_init_func = rtl8211_lg1811_init;

	return arch_init_func ? arch_init_func(phydev) : 0;
}
EXPORT_SYMBOL(rtl8211_arch_init);

static int lg1k_init_eth(void)
{
	phy_register_fixup_for_uid(0xf3364c11, 0xffffffff, lge_lg1k_rev1_fixup_run);
	phy_register_fixup_for_uid(0xf3364c12, 0xffffffff, lge_lg1k_rev2_fixup_run);
	phy_register_fixup_for_uid(0xf3364c13, 0xffffffff, lge_lg1k_rev3_fixup_run);
	phy_register_fixup_for_uid(0xf3364c14, 0xffffffff, lge_lg1k_rev4_fixup_run);
	phy_register_fixup_for_uid(0x01814570, 0xfffffff0, omniphy_fixup_run);
	phy_register_fixup_for_uid(0x00441400, 0xfffffff0, sunplus_fixup_run);
	phy_register_fixup_for_uid(0x001cc816, 0xfffffff0, rtl8201_fixup_run);
	phy_register_fixup_for_uid(0x001cc915, 0xfffffff0, rtl8211_fixup_run);
	return 0;
}
#ifndef	CONFIG_USER_INITCALL_NET
device_initcall(lg1k_init_eth);
#else	/* CONFIG_USER_INITCALL_NET */
user_initcall_grp("NET", lg1k_init_eth);
#endif	/* CONFIG_USER_INITCALL_NET */
