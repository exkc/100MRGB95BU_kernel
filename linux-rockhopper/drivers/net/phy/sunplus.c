#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/ethtool.h>
#include <linux/list.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/syscore_ops.h>

#define SUNPLUS_ISR	0x10	/* Interrupt Status Register */
#define SUNPLUS_IMR	0x11	/* Interrupt Mask Register */
#define SUNPLUS_GCR	0x13	/* Global Configuration Register */
#define SUNPLUS_MAR0	0x16	/* MAC Address Register 0 */
#define SUNPLUS_MAR1	0x17	/* MAC Address Register 1 */
#define SUNPLUS_MAR2	0x18	/* MAC Address Register 2 */
#define SUNPLUS_PSR	0x1f	/* Page Selection Register */

#define WAKE_MAGIC_SUSPEND	(1 << 15)

struct sunplus_priv {
	struct list_head list;
	struct phy_device *phydev;
};

static int sunplus_ack_interrupt(struct phy_device *);
static int sunplus_config_intr(struct phy_device *);
static void sunplus_get_wol(struct phy_device *, struct ethtool_wolinfo *);

static LIST_HEAD(sunplus_list);

int __weak sunplus_arch_isolate(struct phy_device *phydev, int enable)
{
	return 0;
}

int __weak sunplus_arch_reset(struct phy_device *phydev, int enable)
{
	return 0;
}

int __weak sunplus_arch_shutdown(struct phy_device *phydev, int enable)
{
	return 0;
}

static int sunplus_isolate(struct phy_device *phydev, int enable)
{
	return sunplus_arch_isolate(phydev, enable);
}

static int sunplus_shutdown(struct phy_device *phydev, int enable)
{
	int v;

	if (enable) {
		phy_write(phydev, SUNPLUS_PSR, 0x0100);
		phy_write(phydev, 0x12, 0x4824);
		phy_write(phydev, SUNPLUS_PSR, 0x0600);
		phy_write(phydev, 0x1c, 0x8880);
		phy_write(phydev, SUNPLUS_PSR, 0x0000);
		v = phy_read(phydev, MII_BMCR) | BMCR_PDOWN;
		phy_write(phydev, MII_BMCR, v);
	}

	return sunplus_arch_shutdown(phydev, enable);
}

static int sunplus_syscore_suspend(void)
{
	struct sunplus_priv *priv;
	struct ethtool_wolinfo wol;

	list_for_each_entry(priv, &sunplus_list, list) {
		sunplus_get_wol(priv->phydev, &wol);
		if (!wol.wolopts)
			sunplus_shutdown(priv->phydev, 1);
		sunplus_isolate(priv->phydev, 1);
	}

	return 0;
}

static void sunplus_syscore_resume(void)
{
	struct sunplus_priv *priv;

	list_for_each_entry(priv, &sunplus_list, list) {
		sunplus_shutdown(priv->phydev, 0);
		sunplus_isolate(priv->phydev, 0);
	}
}

static struct syscore_ops sunplus_syscore_ops = {
	.suspend	= sunplus_syscore_suspend,
	.resume		= sunplus_syscore_resume,
};

static int sunplus_soft_reset(struct phy_device *phydev)
{
	int rv;

	rv = sunplus_arch_reset(phydev, 1);
	if (rv < 0)
		return rv;
	rv = sunplus_isolate(phydev, 0);
	if (rv < 0)
		return rv;
	rv = sunplus_shutdown(phydev, 1);
	if (rv < 0)
		return rv;

	mdelay(10);

	rv = sunplus_shutdown(phydev, 0);
	if (rv < 0)
		return rv;

	mdelay(10);

	rv = sunplus_arch_reset(phydev, 0);
	if (rv < 0)
		return rv;

	udelay(12);

	return 0;
}

static int sunplus_config_init(struct phy_device *phydev)
{
	struct ethtool_keee eee;

	phy_ethtool_get_eee(phydev, &eee);
	linkmode_zero(eee.advertised);
	phy_ethtool_set_eee(phydev, &eee);

	if (phy_interrupt_is_valid(phydev))
		sunplus_config_intr(phydev);

	return 0;
}

static int sunplus_probe(struct phy_device *phydev)
{
	struct sunplus_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&priv->list);
	priv->phydev = phydev;
	phydev->priv = priv;

	list_add(&priv->list, &sunplus_list);

	return 0;
}

static void sunplus_remove(struct phy_device *phydev)
{
	struct sunplus_priv *priv = phydev->priv;
	list_del(&priv->list);
}

static int sunplus_resume(struct phy_device *phydev)
{
	dev_info(&phydev->mdio.dev, "slow-path resume\n");
	phy_init_hw(phydev);
	return 0;
}

static int sunplus_read_status(struct phy_device *phydev)
{
	int rv;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		rv = genphy_aneg_done(phydev);
		if (rv < 0)
			return rv;
		if (!rv)
			goto continue_read_status;

		rv = phy_read(phydev, MII_LPA);
		if (rv < 0)
			return rv;
		if (!(rv & LPA_LPACK)) {
			dev_warn(&phydev->mdio.dev, "invalid LPA -- reset\n");
			return phy_init_hw(phydev);
		}
	}

continue_read_status:
	return genphy_read_status(phydev);
}

static int sunplus_ack_interrupt(struct phy_device *phydev)
{
	phy_write(phydev, SUNPLUS_ISR, phy_read(phydev, SUNPLUS_ISR));
	return 0;
}

static int sunplus_config_intr(struct phy_device *phydev)
{
	int imr = phy_read(phydev, SUNPLUS_IMR);

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		sunplus_ack_interrupt(phydev);
		phy_write(phydev, SUNPLUS_IMR, imr | 0x8000);
	}	
	else {
		phy_write(phydev, SUNPLUS_IMR, imr & 0x7000);
		sunplus_ack_interrupt(phydev);
	}
	return 0;
}

static void
sunplus_get_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *netdev = phydev->attached_dev;
	u16 mac_addr[3];
	int evt = phy_read(phydev, SUNPLUS_GCR);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	if (evt & 0x0400) {
		wol->wolopts |= WAKE_MAGIC;

		mac_addr[0] = be16_to_cpu(phy_read(phydev, SUNPLUS_MAR0));
		mac_addr[1] = be16_to_cpu(phy_read(phydev, SUNPLUS_MAR1));
		mac_addr[2] = be16_to_cpu(phy_read(phydev, SUNPLUS_MAR2));

		if (netdev && memcmp(mac_addr, netdev->dev_addr, ETH_ALEN)) {
			dev_warn(&phydev->mdio.dev, "invalid MAC address: %pM\n",
				 mac_addr);
		}
	}
}

static int
sunplus_set_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *netdev = phydev->attached_dev;
	u16 const *mac_addr = (u16 *)netdev->dev_addr;
	int evt = phy_read(phydev, SUNPLUS_GCR) & 0xfbff;
	int imr = phy_read(phydev, SUNPLUS_IMR);
	bool differ_isol = false;

	/* handle and clear possible private flag first */
	if (wol->wolopts & WAKE_MAGIC_SUSPEND) {
		differ_isol = true;
		wol->wolopts ^= WAKE_MAGIC_SUSPEND;
	}

	if ((wol->wolopts & wol->supported) != wol->wolopts)
		return -ENOTSUPP;

	if (wol->wolopts & WAKE_MAGIC) {
		evt |= 0x0400;

		phy_write(phydev, SUNPLUS_MAR0, cpu_to_be16(mac_addr[0]));
		phy_write(phydev, SUNPLUS_MAR1, cpu_to_be16(mac_addr[1]));
		phy_write(phydev, SUNPLUS_MAR2, cpu_to_be16(mac_addr[2]));
	}

	phy_write(phydev, SUNPLUS_GCR, evt);

	if (evt)
		phy_write(phydev, SUNPLUS_IMR, imr | 0x4000);
	else
		phy_write(phydev, SUNPLUS_IMR, imr & 0xb000);

	if (!differ_isol) {
		if (!wol->wolopts)
			sunplus_shutdown(phydev, 1);
		sunplus_isolate(phydev, 1);
	}

	return 0;
}

static struct phy_driver sunplus_drvs[] = {
	{
		.phy_id		= 0x00441400,
		.name		= "Sunplus Fast Ethernet Transceiver",
		.phy_id_mask	= 0xfffffff0,
		.features	= PHY_BASIC_FEATURES,
		.soft_reset	= sunplus_soft_reset,
		.config_init	= sunplus_config_init,
		.probe		= sunplus_probe,
		.remove		= sunplus_remove,
		.resume		= sunplus_resume,
		.config_aneg	= genphy_config_aneg,
		.read_status	= sunplus_read_status,
		.config_intr	= sunplus_config_intr,
		.get_wol	= sunplus_get_wol,
		.set_wol	= sunplus_set_wol,
		.mdiodrv.driver.owner	= THIS_MODULE,
	},
};

static int __init sunplus_init(void)
{
	int rv;

	rv = phy_drivers_register(sunplus_drvs, ARRAY_SIZE(sunplus_drvs), THIS_MODULE);
	if (rv < 0)
		return rv;

	register_syscore_ops(&sunplus_syscore_ops);

	return 0;
}
module_init(sunplus_init);

static void __exit sunplus_exit(void)
{
	unregister_syscore_ops(&sunplus_syscore_ops);
	phy_drivers_unregister(sunplus_drvs, ARRAY_SIZE(sunplus_drvs));
}
module_exit(sunplus_exit);

static struct mdio_device_id sunplus_ids[] __maybe_unused = {
	{ 0x00441400, 0xfffffff0 },
	{ /* sentinel */ },
};
MODULE_DEVICE_TABLE(mdio, sunplus_ids);

MODULE_AUTHOR("Jongsung Kim <neidhard.kim@lge.com>");
MODULE_DESCRIPTION("Sunplus Fast Ethernet Transceiver driver");
MODULE_LICENSE("GPL");
