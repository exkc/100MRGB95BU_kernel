/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * LG DTV SoC USB 1.1/2.0 PHY driver
 *
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
 */
#ifndef _PHY_LG1K_USB_NSI_H
#define _PHY_LG1K_USB_NSI_H

#include <linux/device.h>
#include <linux/phy/phy.h>
#include "phy-lg1k-usb.h"

struct lg1k_usb3_phy_nsi {
	struct lg1k_usb_phy lgphy;
	struct device *dev;
};

struct lg1k_usb2_phy_nsi {
	struct lg1k_usb_phy lgphy;
	struct device *dev;
};

#define lgphy_to_nsiphy3(x)	container_of((x), struct lg1k_usb3_phy_nsi, lgphy)
#define lgphy_to_nsiphy2(x)	container_of((x), struct lg1k_usb2_phy_nsi, lgphy)
#endif // _PHY_LG1K_USB_NSI_H
