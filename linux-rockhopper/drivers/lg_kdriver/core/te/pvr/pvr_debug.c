/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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

/** @file
 *
 *  pvr device driver
 *
 *  author		ks.hyun(ks.hyunlge.com)
 *  version		1.0
 *  date		2018.10.29
 *  note		Additional information.
 *
 */

#include <lg1k/te/mem.h>

#include "pvr_impl.h"

enum {
	DEBUG_ID_VERSION = 0,
	DEBUG_ID_MEM_INFO,
};

enum {
	STATUS_UP_DEV = (0x1 << PVR_DEBUG_STATUS_UP_DEV),
	STATUS_DN_DEV = (0x1 << PVR_DEBUG_STATUS_DN_DEV),
	STATUS_ALL = 0xFFFFFF,
};

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct te_mem_region_info *info;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		seq_printf(m, "20181029.0\n");
		break;

	case DEBUG_ID_MEM_INFO:
		info = te_get_mem_region_info(TE_MEM_PVR);
		seq_printf(m, "0x%08x ++ 0x%08x\n", info->addr, info->size);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;

	switch (item->flags) {
	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

/** STATUS **/
static int debug_status_show(struct te_debug_item *item, struct seq_file *m)
{
	int i;
	struct pvr_device *dev = item->private;

	for (i = 0; i < PVR_DEBUG_STATUS_MAX; i++) {
		if (item->flags & (0x1 << i)) {
			pvr_debug_show_t func = dev->debug.show_status[i];
			if (func)
				func(dev, m);
		}
	}

	return 0;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_simple_ops debug_status_ops = {
	.show = debug_status_show,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("version", &debug_ops, DEBUG_ID_VERSION),
	DBGITM_SIM_R("mem_info", &debug_ops, DEBUG_ID_MEM_INFO),

	DBGITM_SIM_R("up_status", &debug_status_ops, STATUS_UP_DEV),
	DBGITM_SIM_R("dn_status", &debug_status_ops, STATUS_DN_DEV),
	DBGITM_SIM_R("status", &debug_status_ops, STATUS_ALL),
};

static int init_device(struct pvr_device *dev)
{
	int ret;
	struct pvr_debug *d = &dev->debug;

	d->dir = te_debug_create_dir(PVR_MODULE, NULL);
	CHECK_ERROR(!d->dir, return -EIO, "Err in te_debug_create_dir");

	ret = debug_create_item_files(debug_list, dev, d->dir);

	return ret;
}

static void release_device(struct pvr_device *dev)
{
	te_debug_remove_dir(dev->debug.dir);
}

int pvr_debug_register_status_show(struct pvr_device *dev,
				   enum pvr_debug_status status,
				   pvr_debug_show_t show)
{
	struct pvr_debug *d = &dev->debug;

	if (status >= PVR_DEBUG_STATUS_MAX)
		return -EINVAL;

	d->show_status[status] = show;

	return 0;
}

const struct pvr_sub_driver pvr_debug_driver = {
	.name = "pvr_debug",

	.init = init_device,
	.release = release_device,
};

/** @} */
