#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/ethtool.h>
#include <linux/phy.h>

static int ext_unplugged;
module_param(ext_unplugged, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ext_unplugged, "Link status from external switch");

static int use_forced_mode;
module_param(use_forced_mode, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(use_forced_mode, "Force 100Mbps/Full-duplex mode");

void exthub_read_status(struct phy_device *phydev)
{
	if (!use_forced_mode)
		return;

	if (ext_unplugged) {
		dev_info(&phydev->mdio.dev, "[COMMERCIAL] exthub link down\n");
		phydev->link = 0;
		phydev->state = PHY_NOLINK;
		phydev->speed = SPEED_UNKNOWN;
		phydev->duplex = DUPLEX_UNKNOWN;
		phydev->mdix = ETH_TP_MDI_INVALID;
		phydev->phy_link_change(phydev, false);
	} else {
		dev_info(&phydev->mdio.dev, "[COMMERCIAL] exthub link up\n");
		phydev->link = 1;
		phydev->state = PHY_RUNNING;
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_FULL;
		phydev->mdix = ETH_TP_MDI;
		phydev->phy_link_change(phydev, true);
	}

	dev_info(&phydev->mdio.dev, "phydev->link: %d\n", phydev->link);
}
EXPORT_SYMBOL_GPL(exthub_read_status);

MODULE_AUTHOR("Sangjin Han <sangjin7.han@lge.com>");
MODULE_DESCRIPTION("Logical link-status considering on-board switching hub");
MODULE_LICENSE("GPL");
