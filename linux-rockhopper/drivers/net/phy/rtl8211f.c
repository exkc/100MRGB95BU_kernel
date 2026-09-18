#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/netdevice.h>
#include <linux/of.h>
#include <linux/phy.h>
#include <linux/syscore_ops.h>

#define RTL8211F_GBCR		0x09
#define RTL8211F_GBSR		0x0a
#define RTL8211F_INER		0x12	/* page 0x0a42 */
#define RTL8211F_INSR		0x1d	/* page 0x0a43 */
#define RTL8211F_PGSR		0x1f

#define WAKE_MAGIC_SUSPEND	(1 << 15)

struct rtl8211f_priv {
	struct list_head list;
	struct phy_device *phydev;
};

static LIST_HEAD(rtl8211f_list);

static void rtl8211f_syscore_resume(void)
{
	struct rtl8211f_priv *priv;
	list_for_each_entry(priv, &rtl8211f_list, list) {
		if (phy_interrupt_is_valid(priv->phydev))
			disable_irq_nosync(priv->phydev->irq);
	}
}

static struct syscore_ops rtl8211f_syscore_ops = {
	.resume		= rtl8211f_syscore_resume,
};

int __weak rtl8211_arch_init(struct phy_device *phydev)
{
	return 0;
}

static int rtl8211f_config_intr(struct phy_device *phydev);

static int rtl8211f_soft_reset(struct phy_device *phydev)
{
	struct gpio_desc *gpio = gpiod_get(&phydev->mdio.dev, "reset", GPIOD_ASIS);
	int v;

	if (!IS_ERR(gpio)) {
		dev_info(&phydev->mdio.dev, "hard-reset by GPIO\n");

		gpiod_direction_output(gpio, 0);
		gpiod_set_value(gpio, 1);
		mdelay(60);
		gpiod_set_value(gpio, 0);
		mdelay(75);

		gpiod_put(gpio);

		/* wait for PHY Register Accessible interrupt */
		phy_write(phydev, RTL8211F_PGSR, 0x0a43);
		do {
			mdelay(1);
			v = phy_read(phydev, 0x1d);
		} while (!(v & 0x0020));
	}

	/* enable spread-spectrum clocking */
	phy_write(phydev, RTL8211F_PGSR, 0x0c44);
	phy_write(phydev, 0x13, 0x5f00);
	phy_write(phydev, RTL8211F_PGSR, 0x0d09);
	phy_write(phydev, 0x10, 0xcf00);
	phy_write(phydev, RTL8211F_PGSR, 0x0a43);
	phy_write(phydev, 0x19, 0x38c3);

	/* back to page 0 */
	phy_write(phydev, RTL8211F_PGSR, 0x0000);

	dev_info(&phydev->mdio.dev, "soft-reset by MDIO\n");

	return genphy_soft_reset(phydev);
}

static int rtl8211f_config_init(struct phy_device *phydev)
{
	struct ethtool_keee eee;

	rtl8211_arch_init(phydev);

	/* disable EEE */
	phy_ethtool_get_eee(phydev, &eee);
	linkmode_zero(eee.advertised);
	phy_ethtool_set_eee(phydev, &eee);

	if (phy_interrupt_is_valid(phydev))
		rtl8211f_config_intr(phydev);

	return 0;
}

static int rtl8211f_probe(struct phy_device *phydev)
{
	struct rtl8211f_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&priv->list);
	priv->phydev = phydev;
	phydev->priv = priv;

	list_add(&priv->list, &rtl8211f_list);

	return 0;
}

static int rtl8211f_sanity(struct phy_device *phydev)
{
	u16 phyidr[2];
	int v;

	/* check if we can read PHY registers */
	phyidr[0] = phy_read(phydev, MII_PHYSID1);
	phyidr[1] = phy_read(phydev, MII_PHYSID2);
	if (((phyidr[0] << 16) | phyidr[1]) != phydev->phy_id)
		return 0;

	/* check if accumulated idle error count */
	v = phy_read(phydev, RTL8211F_GBSR);
	if (v & 0x00ff) {
		dev_warn(&phydev->mdio.dev, "idle error count: %d\n", v & 0x00ff);
		return 0;
	}

	return 1;
}

static int rtl8211f_resume(struct phy_device *phydev)
{
	if (!phydev->adjust_link || !phydev->attached_dev) {
		dev_info(&phydev->mdio.dev, "skip resume\n");
		return 0;
	}

	/* disable and reset WOL */
	phy_write(phydev, RTL8211F_PGSR, 0x0d8a);
	phy_write(phydev, 0x10, 0x0000);
	phy_write(phydev, 0x11, 0x1fff);

	/* enable RGMII pad */
	phy_write(phydev, RTL8211F_PGSR, 0x0d8a);
	phy_write(phydev, 0x13, phy_read(phydev, 0x13) & 0x7fff);

	/* switch pin31 back to INTB function */
	phy_write(phydev, RTL8211F_PGSR, 0x0d40);
	phy_write(phydev, 0x16, phy_read(phydev, 0x16) & 0xffdf);

	/* back to page 0 */
	phy_write(phydev, RTL8211F_PGSR, 0x0000);

	if (rtl8211f_sanity(phydev)) {
		genphy_read_status(phydev);
		if (phydev->link) {
			dev_info(&phydev->mdio.dev, "fast-path resume\n");
			rtl8211_arch_init(phydev);
			phydev->state = PHY_RUNNING;
			phydev->adjust_link(phydev->attached_dev);

			goto done;
		}
	}

	dev_info(&phydev->mdio.dev, "slow-path resume\n");
	phy_init_hw(phydev);
done:
	if (phy_interrupt_is_valid(phydev))
		enable_irq(phydev->irq);

	return 0;
}

static int rtl8211f_ack_interrupt(struct phy_device *phydev)
{
	phy_write(phydev, RTL8211F_PGSR, 0x0a43);
	phy_read(phydev, RTL8211F_INSR);
	phy_write(phydev, RTL8211F_PGSR, 0x0000);
	return 0;
}

static int rtl8211f_config_intr(struct phy_device *phydev)
{
	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		rtl8211f_ack_interrupt(phydev);
		phy_write(phydev, RTL8211F_PGSR, 0x0a42);
		phy_write(phydev, RTL8211F_INER, 0x0010);
		phy_write(phydev, RTL8211F_PGSR, 0x0000);
	} else {
		phy_write(phydev, RTL8211F_PGSR, 0x0a42);
		phy_write(phydev, RTL8211F_INER, 0x0000);
		phy_write(phydev, RTL8211F_PGSR, 0x0000);
		rtl8211f_ack_interrupt(phydev);
	}
	return 0;
}

static void
rtl8211f_get_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *netdev = phydev->attached_dev;
	u16 mac_addr[3];
	int wol_event;

	/* get current WOL event set */
	phy_write(phydev, RTL8211F_PGSR, 0x0d8a);
	wol_event = phy_read(phydev, 0x10);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	if ((wol_event & 0x1000) == 0x1000) {
		wol->wolopts |= WAKE_MAGIC;

		/* get current MAC address set */
		phy_write(phydev, RTL8211F_PGSR, 0x0d8c);
		mac_addr[0] = phy_read(phydev, 0x10);
		mac_addr[1] = phy_read(phydev, 0x11);
		mac_addr[2] = phy_read(phydev, 0x12);

		if (netdev && memcmp(mac_addr, netdev->dev_addr, ETH_ALEN)) {
			dev_warn(&phydev->mdio.dev, "invalid MAC address: %pM\n",
			         mac_addr);
		}
	}

	/* back to page 0 */
	phy_write(phydev, RTL8211F_PGSR, 0x0000);
}

static int
rtl8211f_set_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
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
		phy_write(phydev, RTL8211F_PGSR, 0x0d8c);
		phy_write(phydev, 0x10, mac_addr[0]);
		phy_write(phydev, 0x11, mac_addr[1]);
		phy_write(phydev, 0x12, mac_addr[2]);
	}

	/* set WOL event */
	phy_write(phydev, RTL8211F_PGSR, 0x0d8a);
	phy_write(phydev, 0x11, 0x9fff);
	phy_write(phydev, 0x10, wol_event);

	if (wol_event) {
		/* optional RGMII pad isolation */
		phy_write(phydev, RTL8211F_PGSR, 0x0d8a);
		phy_write(phydev, 0x13, phy_read(phydev, 0x13) | 0x8000);

		/* switch pin31 to PMEB function */
		phy_write(phydev, RTL8211F_PGSR, 0x0d40);
		phy_write(phydev, 0x16, phy_read(phydev, 0x16) | 0x0020);
	}

	/* back to page 0 */
	phy_write(phydev, RTL8211F_PGSR, 0x0000);

	return 0;
}

static struct phy_driver rtl8211f_drvs[] = {
	{
		.phy_id		= 0x001cc916,
		.name		= "RTL8211F Gigabit Ethernet",
		.phy_id_mask	= 0xffffffff,
		.features	= PHY_GBIT_FEATURES,
		.soft_reset	= rtl8211f_soft_reset,
		.config_init	= rtl8211f_config_init,
		.probe		= rtl8211f_probe,
		.resume		= rtl8211f_resume,
		.config_aneg	= genphy_config_aneg,
		.read_status	= genphy_read_status,
		.config_intr	= rtl8211f_config_intr,
		.get_wol	= rtl8211f_get_wol,
		.set_wol	= rtl8211f_set_wol,
		.mdiodrv.driver.owner	= THIS_MODULE,
	},
};

static int __init rtl8211f_init(void)
{
	int v;

	v = phy_drivers_register(rtl8211f_drvs, ARRAY_SIZE(rtl8211f_drvs), THIS_MODULE);
	if (v < 0)
		return v;

	register_syscore_ops(&rtl8211f_syscore_ops);

	return 0;
}
module_init(rtl8211f_init);

static void __exit rtl8211f_exit(void)
{
	unregister_syscore_ops(&rtl8211f_syscore_ops);
	phy_drivers_unregister(rtl8211f_drvs, ARRAY_SIZE(rtl8211f_drvs));
}
module_exit(rtl8211f_exit);

static struct mdio_device_id rtl8211f_ids[] __maybe_unused = {
	{ 0x001cc916, 0xffffffff },
	{ /* sentinel */ },
};
MODULE_DEVICE_TABLE(mdio, rtl8211f_ids);

MODULE_AUTHOR("Jongsung Kim <neidhard.kim@lge.com>");
MODULE_DESCRIPTION("Realtek RTL8211F Gigabit Ethernet PHY driver");
MODULE_LICENSE("GPL");
