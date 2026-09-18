#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/list.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/syscore_ops.h>

#define WAKE_MAGIC_SUSPEND	(1 << 15)

void __weak exthub_read_status(struct phy_device *phydev) { }

static int lge_lg1k_config_intr(struct phy_device *);

int __weak lge_lg1k_arch_isolate(struct phy_device *phydev, int enable)
{
	return 0;
}

int __weak lge_lg1k_arch_reset(struct phy_device *phydev, int enable)
{
	return 0;
}

int __weak lge_lg1k_arch_shutdown(struct phy_device *phydev, int enable)
{
	return 0;
}

static int lge_lg1k_soft_reset(struct phy_device *phydev)
{
	lge_lg1k_arch_shutdown(phydev, 1);

	mdelay(10);

	lge_lg1k_arch_reset(phydev, 1);
	lge_lg1k_arch_isolate(phydev, 0);
	lge_lg1k_arch_shutdown(phydev, 0);

	mdelay(10);

	lge_lg1k_arch_reset(phydev, 0);

	mdelay(10);

	return 0;
}

static int lge_lg1k_config_init(struct phy_device *phydev)
{
	lge_lg1k_config_intr(phydev);
	return 0;
}

static int lge_lg1k_resume(struct phy_device *phydev)
{
	u16 mac_addr[3];

	lge_lg1k_arch_isolate(phydev, 0);
	lge_lg1k_arch_shutdown(phydev, 0);

	/* clear possible WOL interrupt(s) */
	phy_read(phydev, 0x1b);
	/* disable WOL interrupts */
	phy_write(phydev, 0x1c, 0x0000);

	phy_write(phydev, 0x1f, 0x0004);
	mac_addr[2] = ntohs(phy_read(phydev, 0x10));
	mac_addr[1] = ntohs(phy_read(phydev, 0x11));
	mac_addr[0] = ntohs(phy_read(phydev, 0x12));
	phy_write(phydev, 0x1f, 0x0000);

	dev_info(&phydev->mdio.dev, "MAC address for WOL: %pM\n", mac_addr);
	if (is_valid_ether_addr((u8 *)mac_addr)) {
		genphy_read_status(phydev);
		if (phydev->link) {
			dev_info(&phydev->mdio.dev, "fast-path resume\n");
			phydev->state = PHY_RUNNING;
			netif_carrier_on(phydev->attached_dev);

			return 0;
		}
	}

	dev_info(&phydev->mdio.dev, "slow-path resume\n");
	phy_init_hw(phydev);
	phydev->link = 0;
	phydev->state = PHY_READY;
	netif_carrier_off(phydev->attached_dev);

	return 0;
}

static int lge_lg1k_config_aneg(struct phy_device *phydev)
{
	switch (phydev->mdix_ctrl) {
	case ETH_TP_MDI:
		phy_modify(phydev, 0x11, 0x0003, 0x0000);
		break;
	case ETH_TP_MDI_X:
		phy_modify(phydev, 0x11, 0x0003, 0x0002);
		break;
	default:
		/* defaults to auto-negotiation */
		phydev->mdix_ctrl = ETH_TP_MDI_AUTO;
		fallthrough;
	case ETH_TP_MDI_AUTO:
		phy_modify(phydev, 0x11, 0x0003, 0x0001);
		break;
	}

	if (phydev->mdix_ctrl != ETH_TP_MDI_AUTO)
		phydev->mdix = phydev->mdix_ctrl;
	else
		phydev->mdix = ETH_TP_MDI_INVALID;

	return genphy_config_aneg(phydev);
}

static int lge_lg1k_read_status(struct phy_device *phydev)
{
	int rv = genphy_read_status(phydev);
	int cnt;

	exthub_read_status(phydev);

	if (rv < 0 || !phydev->link)
		return rv;

	if (phydev->speed == SPEED_UNKNOWN || phydev->duplex == DUPLEX_UNKNOWN) {
		dev_info(&phydev->mdio.dev, "invalid link mode\n");
		rv = phy_read(phydev, 0x12);
		switch (rv & 0x0003) {
		case 0x0001:
			phydev->speed = SPEED_10;
			break;
		case 0x0002:
			phydev->speed = SPEED_100;
			break;
		default:
			dev_warn(&phydev->mdio.dev, "invalid link speed -- reset\n");
			return phy_init_hw(phydev);
		}
		phydev->duplex = (rv & 0x0004) ? DUPLEX_FULL : DUPLEX_HALF;
	}

	if (phydev->mdix == ETH_TP_MDI_INVALID) {
		rv = phy_read(phydev, 0x11);
		if (rv & 0x0004)
			phydev->mdix = ETH_TP_MDI_X;
		else
			phydev->mdix = ETH_TP_MDI;
	}

	if (phydev->speed == SPEED_100) {
		phy_write(phydev, 0x1f, 0x0009);
		for (cnt = 3; cnt; cnt--) {
			if (phy_read(phydev, 0x14) != 0x4100 ||
			    phy_read(phydev, 0x18) != 0x0100)
				break;
			mdelay(10);
		}
		phy_write(phydev, 0x1f, 0x0004);
		rv = phy_read(phydev, 0x1a);
		phy_write(phydev, 0x1f, 0x0000);
		if (!cnt || !rv) {
			dev_warn(&phydev->mdio.dev, "%s%s%s -- reset DSP\n",
				 !cnt ? "EQ stuck" : "",
				 !cnt && !rv ? " and " : "",
				 !rv ? "descrambler lock failed" : "");
			phy_write(phydev, 0x1c, 0x0000);
			phy_write(phydev, 0x1f, 0x0009);
			phy_write(phydev, 0x12, 0x0109);
			phy_write(phydev, 0x1f, 0x0000);
			phy_write(phydev, 0x1c, 0x0050);
		}
	}

	return 0;
}

static int lge_lg1k_ack_interrupt(struct phy_device *phydev)
{
	int rv = phy_read(phydev, 0x1d);

	dev_info(&phydev->mdio.dev, "Link ISR: %04x\n", rv);
	if ((rv & 0x0050) == 0x0040) {
		dev_warn(&phydev->mdio.dev, "invalid ISR -- reset\n");
		return phy_init_hw(phydev);
	}

	return rv < 0 ? rv : 0;
}

static int lge_lg1k_config_intr(struct phy_device *phydev)
{
	int ret;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		ret = lge_lg1k_ack_interrupt(phydev);
		if (ret)
			return ret;
		ret = phy_write(phydev, 0x1e, 0x0050);
	} else {
		ret = phy_write(phydev, 0x1e, 0x0000);
		if (ret)
			return ret;
		ret = lge_lg1k_ack_interrupt(phydev);
	}

	return ret;
}

static void
lge_lg1k_get_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	int evt;

	wol->supported = WAKE_MAGIC | WAKE_MAGIC_SUSPEND;
	wol->wolopts = 0;

	phy_write(phydev, 0x1f, 0x0004);
	evt = phy_read(phydev, 0x13);
	phy_write(phydev, 0x1f, 0x0000);

	if (evt & 0x0007)
		wol->wolopts |= WAKE_MAGIC;
}

static int
lge_lg1k_set_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *netdev = phydev->attached_dev;
	u16 const *mac_addr = (u16 *)netdev->dev_addr;

	/* clear possible WOL interrupt(s) */
	phy_read(phydev, 0x1b);

	if (wol->wolopts & WAKE_MAGIC) {
		phy_write(phydev, 0x1f, 0x0004);
		phy_write(phydev, 0x10, htons(mac_addr[2]));
		phy_write(phydev, 0x11, htons(mac_addr[1]));
		phy_write(phydev, 0x12, htons(mac_addr[0]));
		phy_write(phydev, 0x13, 0x000f);
		phy_write(phydev, 0x1f, 0x0000);
		phy_write(phydev, 0x1c, 0x0007);
	} else {
		phy_write(phydev, 0x1f, 0x0004);
		phy_write(phydev, 0x10, 0x0000);
		phy_write(phydev, 0x11, 0x0000);
		phy_write(phydev, 0x12, 0x0000);
		phy_write(phydev, 0x13, 0x0000);
		phy_write(phydev, 0x1f, 0x0000);
		phy_write(phydev, 0x1c, 0x0000);
	}

	if (!(wol->wolopts & WAKE_MAGIC_SUSPEND)) {
		if (!wol->wolopts)
			lge_lg1k_arch_shutdown(phydev, 1);
		lge_lg1k_arch_isolate(phydev, 1);
	}

	return 0;
}

static struct phy_driver lge_lg1k_drvs[] = {
	{
		PHY_ID_MATCH_MODEL(0xf3364c11),
		.name		= "LG1K Fast Ethernet Transceiver",
		.features	= PHY_BASIC_FEATURES,
		.soft_reset	= lge_lg1k_soft_reset,
		.config_init	= lge_lg1k_config_init,
		.resume		= lge_lg1k_resume,
		.config_aneg	= lge_lg1k_config_aneg,
		.read_status	= lge_lg1k_read_status,
		.config_intr	= lge_lg1k_config_intr,
		.get_wol	= lge_lg1k_get_wol,
		.set_wol	= lge_lg1k_set_wol,
	},
};
module_phy_driver(lge_lg1k_drvs);

static struct mdio_device_id lge_lg1k_ids[] __maybe_unused = {
	{ PHY_ID_MATCH_MODEL(0xf3364c11), },
	{ /* sentinel */ },
};
MODULE_DEVICE_TABLE(mdio, lge_lg1k_ids);

MODULE_AUTHOR("Jongsung Kim <neidhard.kim@lge.com>");
MODULE_DESCRIPTION("LG Electronics Fast Ethernet Transceiver driver");
MODULE_LICENSE("GPL");
