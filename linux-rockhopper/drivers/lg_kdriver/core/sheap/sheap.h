/*
 * SoC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2024 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _SHEAP_DRV_H_
#define _SHEAP_DRV_H_

#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/list.h>

/**
 * struct sheap - represents a sheap
 * @name:		used for debugging/device-node name
 * @devt:		sheap device node
 * @list:		list head connecting to list of sheaps
 * @cdev:		sheap char device
 * @class:		sheap class
 * @dev:		sheap device
 * @poolname:	hma pool name for secure mem allocation
*/
struct sheap {
	const char *name;
	void *priv;
	dev_t devt;
	struct list_head list;
	struct cdev cdev;
	struct class *class;
	struct device *dev;
	const char *poolname;
};

/**
 * struct sheap_buf
 * @size:			allocated sheap buffer size
 * @paddr:			allocated sheap pyhsical address
*/
struct sheap_buf {
	unsigned int size;
	phys_addr_t paddr;
};

/**
 * struct sheap_attachment
 * @dev:			device ptr of attachment
 * @table:			sg_table for allocated sheap buffer
*/
struct sheap_attachment {
	struct device *dev;
	struct sg_table table;
};

#endif /* _SHEAP_DRV_H_ */
