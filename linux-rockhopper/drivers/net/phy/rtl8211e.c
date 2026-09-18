#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/netdevice.h>
#include <linux/of.h>
#include <linux/phy.h>
#include <linux/syscore_ops.h>

#define RTL8211E_GBCR		0x09
#define RTL8211E_GBSR		0x0a
#define RTL8211E_MACR		0x0d
#define RTL8211E_MADR		0x0e
#define RTL8211E_INER		0x12
#define RTL8211E_INSR		0x13
#define RTL8211E_EPSR		0x1e
#define RTL8211E_PGSR		0x1f

#define WAKE_MAGIC_SUSPEND	(1 << 15)

struct rtl8211e_priv {
	struct list_head list;
	struct phy_device *phydev;
};

static int rtl8211e_config_intr(struct phy_device *phydev);
static int rtl8211e_isolate(struct phy_device *phydev, int enable);

static LIST_HEAD(rtl8211e_list);

int __weak rtl8211_arch_init(struct phy_device *phydev)
{
	return 0;
}

static void rtl8211e_syscore_resume(void)
{
	struct rtl8211e_priv *priv;
	list_for_each_entry(priv, &rtl8211e_list, list) {
		rtl8211_arch_init(priv->phydev);
		rtl8211e_isolate(priv->phydev, 0);
	}
}

static struct syscore_ops rtl8211e_syscore_ops = {
	.resume		= rtl8211e_syscore_resume,
};

static int rtl8211e_isolate(struct phy_device *phydev, int enable)
{
	int v;

	if (enable) {
		/* isolate RGMII/GMII interface */
		v = phy_read(phydev, MII_BMCR) | 0x0400;
		phy_write(phydev, MII_BMCR, v);
	} else {
		/* de-isolate RGMII/GMII interface */
		v = phy_read(phydev, MII_BMCR) & 0xfbff;
		phy_write(phydev, MII_BMCR, v);

		/* de-isolate again -- possible HW bug */
		v = phy_read(phydev, MII_BMCR) & 0xfbff;
		phy_write(phydev, MII_BMCR, v);
	}

	return 0;
}

static int rtl8211e_soft_reset(struct phy_device *phydev)
{
	struct gpio_desc *gpio = gpiod_get(&phydev->mdio.dev, "reset", GPIOD_ASIS);

	if (!IS_ERR(gpio)) {
		dev_info(&phydev->mdio.dev, "hard-reset by GPIO\n");

		gpiod_direction_output(gpio, 0);
		gpiod_set_value(gpio, 1);
		mdelay(10);
		gpiod_set_value(gpio, 0);
		mdelay(30);

		gpiod_put(gpio);
	} else {
		struct device_node *dn = phydev->mdio.dev.of_node;
		void __iomem *gpio_va;
		phys_addr_t gpio_pa;
		u32 prop;

		if (of_property_read_u32(dn, "reset-addr", &prop) < 0)
			goto soft_reset;

		gpio_pa = (phys_addr_t)prop;
		gpio_va = ioremap(gpio_pa, 4);
		if (!gpio_va)
			goto soft_reset;

		dev_info(&phydev->mdio.dev, "hard-reset by GPIO addr\n");

		writeb_relaxed(0x00, gpio_va);
		mdelay(10);
		writeb_relaxed(0xff, gpio_va);
		mdelay(30);

		iounmap(gpio_va);
	}

soft_reset:

	dev_info(&phydev->mdio.dev, "soft-reset by MDIO\n");
	return genphy_soft_reset(phydev);
}

static int rtl8211e_config_init(struct phy_device *phydev)
{
	struct ethtool_keee eee;
	int v;

	/* disable EEE */
	phy_ethtool_get_eee(phydev, &eee);
	linkmode_zero(eee.advertised);
	phy_ethtool_set_eee(phydev, &eee);

	/* enable spread-spectrum clocking */
	phy_write(phydev, RTL8211E_PGSR, 0x0007);
	phy_write(phydev, RTL8211E_EPSR, 0x00a0);
	v = phy_read(phydev, 0x1a) & 0xfffb;
	phy_write(phydev, 0x1a, v);

	/* back to page 0 */
	phy_write(phydev, RTL8211E_PGSR, 0x0000);

	if (phy_interrupt_is_valid(phydev))
		rtl8211e_config_intr(phydev);

	return 0;
}

static int rtl8211e_probe(struct phy_device *phydev)
{
	struct rtl8211e_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&priv->list);
	priv->phydev = phydev;
	phydev->priv = priv;

	rtl8211_arch_init(phydev);

	list_add(&priv->list, &rtl8211e_list);

	return 0;
}

static int rtl8211e_sanity(struct phy_device *phydev)
{
	u16 phyidr[2];
	int v;

	/* check if we can read PHY registers */
	phyidr[0] = phy_read(phydev, MII_PHYSID1);
	phyidr[1] = phy_read(phydev, MII_PHYSID2);
	if (((phyidr[0] << 16) | phyidr[1]) != phydev->phy_id)
		return 0;

	/* check if accumulated idle error count */
	v = phy_read(phydev, RTL8211E_GBSR);
	if (v & 0x00ff) {
		dev_warn(&phydev->mdio.dev, "idle error count: %d\n", v & 0x00ff);
		return 0;
	}

	return 1;
}

static int rtl8211e_resume(struct phy_device *phydev)
{
	if (!phydev->adjust_link || !phydev->attached_dev) {
		dev_info(&phydev->mdio.dev, "skip resume\n");
		return 0;
	}

	/* disable WOL */
	phy_write(phydev, RTL8211E_PGSR, 0x0007);
	phy_write(phydev, RTL8211E_EPSR, 0x006d);
	phy_write(phydev, 0x15, 0x0000);
	phy_write(phydev, 0x16, 0x9fff);

	/* back to page 0 */
	phy_write(phydev, RTL8211E_PGSR, 0x0000);

	if (rtl8211e_sanity(phydev)) {
		genphy_read_status(phydev);
		if (phydev->link) {
			dev_info(&phydev->mdio.dev, "fast-path resume\n");
			phydev->state = PHY_RUNNING;
			phydev->adjust_link(phydev->attached_dev);

			return 0;
		}
	}

	dev_info(&phydev->mdio.dev, "slow-path resume\n");
	phy_init_hw(phydev);

	return 0;
}

static int rtl8211e_ack_interrupt(struct phy_device *phydev)
{
	phy_read(phydev, RTL8211E_INSR);
	return 0;
}

static int rtl8211e_config_intr(struct phy_device *phydev)
{
	phy_write(phydev, RTL8211E_INER, phydev->interrupts ? 0x0400 : 0x0000);
	/* read INSR once for interrupt logic to work properly */
	rtl8211e_ack_interrupt(phydev);
	return 0;
}

static void
rtl8211e_get_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *netdev = phydev->attached_dev;
	u16 mac_addr[3];
	int wol_event;

	/* get current WOL event set */
	phy_write(phydev, RTL8211E_PGSR, 0x0007);
	phy_write(phydev, RTL8211E_EPSR, 0x006d);
	wol_event = phy_read(phydev, 0x15);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	if (wol_event & 0x1000) {
		wol->wolopts |= WAKE_MAGIC;

		/* get current MAC address set */
		phy_write(phydev, RTL8211E_PGSR, 0x0007);
		phy_write(phydev, RTL8211E_EPSR, 0x006e);
		mac_addr[0] = phy_read(phydev, 0x15);
		mac_addr[1] = phy_read(phydev, 0x16);
		mac_addr[2] = phy_read(phydev, 0x17);

		if (netdev && memcmp(mac_addr, netdev->dev_addr, ETH_ALEN)) {
			dev_warn(&phydev->mdio.dev, "invalid MAC address: %pM\n",
			         mac_addr);
		}
	}

	/* back to page 0 */
	phy_write(phydev, RTL8211E_PGSR, 0x0000);
}

static int
rtl8211e_set_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *netdev = phydev->attached_dev;
	u16 const *mac_addr = (u16 *)netdev->dev_addr;
	int wol_event = 0;

	wol->wolopts &= ~WAKE_MAGIC_SUSPEND;

	if ((wol->wolopts & wol->supported) != wol->wolopts)
		return -ENOTSUPP;

	if (wol->wolopts & WAKE_MAGIC) {
		wol_event |= 0x1000;

		/* set MAC address */
		phy_write(phydev, RTL8211E_PGSR, 0x0007);
		phy_write(phydev, RTL8211E_EPSR, 0x006e);
		phy_write(phydev, 0x15, mac_addr[0]);
		phy_write(phydev, 0x16, mac_addr[1]);
		phy_write(phydev, 0x17, mac_addr[2]);
	}

	/* set WOL event */
	phy_write(phydev, RTL8211E_PGSR, 0x0007);
	phy_write(phydev, RTL8211E_EPSR, 0x006d);
	phy_write(phydev, 0x16, 0x1fff);
	phy_write(phydev, 0x15, wol_event);

	/* back to page 0 */
	phy_write(phydev, RTL8211E_PGSR, 0x0000);

	return rtl8211e_isolate(phydev, 1);
}

static struct phy_driver rtl8211e_drvs[] = {
	{
		.phy_id		= 0x001cc915,
		.name		= "RTL8211E(G) Gigabit Ethernet",
		.phy_id_mask	= 0xffffffff,
		.features	= PHY_GBIT_FEATURES,
		.soft_reset	= rtl8211e_soft_reset,
		.config_init	= rtl8211e_config_init,
		.probe		= rtl8211e_probe,
		.resume		= rtl8211e_resume,
		.config_aneg	= genphy_config_aneg,
		.read_status	= genphy_read_status,
		.config_intr	= rtl8211e_config_intr,
		.get_wol	= rtl8211e_get_wol,
		.set_wol	= rtl8211e_set_wol,
		.mdiodrv.driver.owner	= THIS_MODULE,
	},
};

static int __init rtl8211e_init(void)
{
	int v;

	v = phy_drivers_register(rtl8211e_drvs, ARRAY_SIZE(rtl8211e_drvs), THIS_MODULE);
	if (v < 0)
		return v;

	register_syscore_ops(&rtl8211e_syscore_ops);

	return 0;
}
module_init(rtl8211e_init);

static void __exit rtl8211e_exit(void)
{
	unregister_syscore_ops(&rtl8211e_syscore_ops);
	phy_drivers_unregister(rtl8211e_drvs, ARRAY_SIZE(rtl8211e_drvs));
}
module_exit(rtl8211e_exit);

static struct mdio_device_id rtl8211e_ids[] __maybe_unused = {
	{ 0x001cc915, 0xffffffff },
	{ /* sentinel */ },
};

MODULE_DEVICE_TABLE(mdio, rtl8211e_ids);

MODULE_AUTHOR("Jongsung Kim <neidhard.kim@lge.com>");
MODULE_DESCRIPTION("Realtek RTL8211E(G) Gigabit Ethernet PHY driver");
MODULE_LICENSE("GPL");
