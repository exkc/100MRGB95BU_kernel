/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * LG DTV SoC USB 1.1/2.0 PHY driver
 *
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
 */
#ifndef _LG1K_USB_PHY_H_
#define _LG1K_USB_PHY_H_

#include <linux/types.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/usb/phy.h>
#include <linux/of.h>

/* usb2 params */
struct usb2_host_reset_type {
	unsigned int
	usb2_host_utmi_reset		:1,
	usb2_host_core_reset		:1,
	usb2_host_bus_reset		:1,
	reserved_0			:29;
};

union usb2_host_reset_union {
	unsigned int val;
	struct usb2_host_reset_type reg;
};

struct usb2_phy_reset_type {
	unsigned int
	usb2_phy_reset			:1,
	reserved_0			:31;
};

union usb2_phy_reset_union {
	unsigned int val;
	struct usb2_phy_reset_type reg;
};

/* usb3 params */
struct usb3_host_reset_type {
	unsigned int
	usb3_host_core_reset		:1,
	usb3_host_bus_reset		:1,
	reserved_0			:30;
};

union usb3_host_reset_union {
	unsigned int val;
	struct usb3_host_reset_type reg;
};

struct usb3_phy_reset_type {
	unsigned int
	usb3_phy_reset			:1,
	reserved_0			:31;
};

union usb3_phy_reset_union {
	unsigned int val;
	struct usb3_phy_reset_type reg;
};

/* groups of params */
struct usb2_host_ctrl {
	union usb2_host_reset_union	usb2_host_reset;
	unsigned int			usb2_host_param0;
	unsigned int			usb2_host_param1;
	unsigned int			usb2_host_param2;
	unsigned int			usb2_host_param3;
};

struct usb2_phy_ctrl {
	union usb2_phy_reset_union	usb2_phy_reset;
	unsigned int			usb2_phy_param0;
	unsigned int			usb2_phy_param1;
	unsigned int			usb2_phy_param2;
};

struct usb2_phy_param_ctrl {
	unsigned int			usb2_phy_param0;
	unsigned int			usb2_phy_param1;
	unsigned int			usb2_phy_param2;
};

struct usb2_phy_ctrl_backup {
	u32	param0;
	u32	param1;
	u32	param2;
};

struct usb2_host_ctrl_backup {
	u32     param0;
	u32	param1;
	u32	param2;
};

#define EHCI_INSNREG01	0x094
#define EHCI_INSNREG02	0x098
#define EHCI_INSNREG03	0x09c
struct usb2_ehci_insnreg_backup {
	u32     insnreg01;	// packet buffer out/in thresholds
	u32     insnreg02;	// packet buffer depth
	u32     insnreg03;	// tx_tra_delay and so on
};

struct usb3_host_ctrl {
	union usb3_host_reset_union	usb3_host_reset;
	unsigned int			usb3_host_param0;
	unsigned int			usb3_host_param1;
	unsigned int			usb3_host_param2;
	unsigned int			usb3_host_param3;
	unsigned int			usb3_host_param4;
	unsigned int			usb3_host_param5;
	unsigned int			usb3_host_param6;
};

struct usb3_phy_ctrl {
	union usb3_phy_reset_union	usb3_phy_reset;
	unsigned int			usb3_phy_param0;
	unsigned int			usb3_phy_param1;
	unsigned int			usb3_phy_param2;
	unsigned int			usb3_phy_param3;
	unsigned int			usb3_phy_param4;
	unsigned int			usb3_phy_param5;
	unsigned int			usb3_phy_param6;
};

struct usb3_phy_ctrl_backup {
	u32	param0;
	u32	param1;
	u32	param2;
	u32	param3;
	u32	param4;
	u32	param5;
	u32	param6;
};

struct usb3_host_ctrl_backup {
	u32	param0;
	u32	param1;
	u32	param2;
	u32	param3;
	u32	param4;
	u32	param5;
	u32	param6;
};

#define GBL_REG_OFFSET		0xc000
#define GBL_REG_SIZE		0x1000
#define GBL_GSBUSCFG0		0x100
#define GBL_GRXTHRCFG		0x10c
#define GBL_GUCTL1		0x11c
#define GBL_GUCTL		0x12c
#define GBL_GUSB2PHYCFG		0x200
#define GBL_GUCTL2		0x19c
struct usb3_gbl_regs_backup {
	u32	gsbuscfg0;
	u32	grxthrcfg;
	u32	guctl1;
	u32	guctl;
	u32	gusb2phycfg;
	u32	guctl2;
};

struct usb2_ctrl_reg {
	struct usb2_host_ctrl		*host;
	struct usb2_phy_ctrl		*phy;
};

struct usb3_ctrl_reg {
	struct usb3_host_ctrl		*host;
	struct usb3_phy_ctrl		*phy;
};

struct usb2_priv {
	struct usb2_phy_ctrl_backup	phy_ctrl_backup;
	struct usb2_host_ctrl_backup	host_ctrl_backup;
	struct usb2_ehci_insnreg_backup	ehci_insnreg_backup;
};

struct usb3_priv {
	struct usb3_phy_ctrl_backup	phy_ctrl_backup;
	struct usb3_host_ctrl_backup	host_ctrl_backup;
	struct usb3_gbl_regs_backup	gbl_regs_backup;
};

union usb_phy_priv {
	struct usb2_priv usb2;
	struct usb3_priv usb3;
};

struct lg1k_usb_phy_data {
	char *label;
	unsigned int	dummy;
};

struct lg1k_usb_phy {
	struct phy *phy;
	struct device *dev;
	unsigned int id;
	spinlock_t lock;

	/* of data */
	void __iomem *hc_base;
	void __iomem *host_reg;
	void __iomem *phy_reg;
	void __iomem *gbl_reg;
	void __iomem *pin_mux[2];
	int ctl_gpio;
	int ocd_gpio;
	phys_addr_t hc_phys;

	union usb_phy_priv priv;
	struct lg1k_usb_phy_data *data;

	int hw_initialized;
};

#define phy_offset(n, m) offsetof(struct usb##n##_phy_ctrl, usb##n##_phy_##m)
#define host_offset(n, m) offsetof(struct usb##n##_host_ctrl, usb##n##_host_##m)

int lg1k_usb_phy_parse_dt(struct lg1k_usb_phy *lgphy);
void lg1k_usb_phy_remove(struct lg1k_usb_phy *lgphy);
int lg1k_usb_phy_set_gpio_pinmux(struct lg1k_usb_phy *lgphy, int idx);
int lg1k_usb_phy_set_vbus(struct lg1k_usb_phy *lgphy, int on);

int lg1k_usb_phy_power_on(struct phy *phy);
int lg1k_usb_phy_power_off(struct phy *phy);

struct phy *lg1k_usb_phy_xlate(struct device *dev, struct of_phandle_args *args);
#endif // _LG1K_USB_PHY_H_
