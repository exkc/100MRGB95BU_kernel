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
 *  arib2 device driver
 *
 *  @author	Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date	2016-03-09
 *  @note	Additional information.
 */

#include "arib2_impl.h"

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	DEBUG_ID_VERSION = 0,
	DEBUG_ID_INSTANTBOOT,
	DEBUG_ID_MAX,
};

enum {
	STATUS_INPUT = (0x01 << ARIB2_DEBUG_STATUS_INPUT),
	STATUS_CLOCK = (0x01 << ARIB2_DEBUG_STATUS_CLOCK),
	STATUS_DUMP = (0x01 << ARIB2_DEBUG_STATUS_DUMP),
	STATUS_ALL = 0xFFFFFF,
};

static int suspend_resume_ctrl(struct arib2_device *dev, u8 status)
{
	int ret;

	if (status == 0)
		ret = arib2_dev_suspend(dev);
	else if (status == 1)
		ret = arib2_dev_resume(dev);
	else
		ret = -EPERM;

	return ret;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		dprintf("20190326.0\n");
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
	u32 val;
	struct arib2_device *dev = item->private;

	switch (item->flags) {
	case DEBUG_ID_INSTANTBOOT:
		val = simple_strtoul(str, (char **)NULL, 0);
		suspend_resume_ctrl(dev, val);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_status_show(struct te_debug_item *item, struct seq_file *m)
{
	int i;
	int cnt = 0;
	struct arib2_device *dev = item->private;

	for (i = 0; i < ARIB2_DEBUG_STATUS_MAX; i++) {
		if (item->flags & (0x1 << i)) {
			arib2_debug_show_t func = dev->debug.show_status[i];
			if (func) {
				if (cnt)
					dprintf("\n");
				func(dev, m);
				cnt++;
			}
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
	DBGITM_SIM_W("instantboot", &debug_ops, DEBUG_ID_INSTANTBOOT),

	DBGITM_SIM_R("input", &debug_status_ops, STATUS_INPUT),
	DBGITM_SIM_R("clock", &debug_status_ops, STATUS_CLOCK),
	DBGITM_SIM_R("dump", &debug_status_ops, STATUS_DUMP),
	DBGITM_SIM_R("status", &debug_status_ops, STATUS_ALL),
};

static int debug_dev_init(struct arib2_device *dev)
{
	int ret, i;
	struct arib2_dev_debug *d = &dev->debug;

	d->dir = te_debug_create_dir(ARIB2_MODULE, NULL);
	CHECK_ERROR(!d->dir, return -EIO, "Err in te_debug_create_dir");

	for (i = 0; i < dev->num_channel; i++) {
		struct arib2_channel *c = &dev->channels[i];
		snprintf(c->debug_name, sizeof(c->debug_name), "%d", i);
		c->debug_dir = te_debug_create_dir(c->debug_name, d->dir);
	}
	ret = debug_create_item_files(debug_list, dev, d->dir);

	return ret;
}

static void debug_dev_release(struct arib2_device *dev)
{
	te_debug_remove_dir(dev->debug.dir);
}

int arib2_debug_register_status_show(struct arib2_device *dev,
				     enum arib2_debug_status status,
				     arib2_debug_show_t show)
{
	struct arib2_dev_debug *d = &dev->debug;

	if (status >= ARIB2_DEBUG_STATUS_MAX)
		return -EINVAL;

	d->show_status[status] = show;

	return 0;
}

const struct arib2_sub_driver arib2_debug_driver = {
	.name = "arib2_debug",
	.early_init = debug_dev_init,
	.release = debug_dev_release,
};
