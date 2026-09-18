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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "sdec_impl.h"

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	STATUS_PID_FILTER = (0x1 << SDEC_DEBUG_STATUS_PID_FILTER),
	STATUS_STREAM_FILTER = (0x1 << SDEC_DEBUG_STATUS_STREAM_FILTER),
	STATUS_MCU_FILTER = (0x1 << SDEC_DEBUG_STATUS_MCU_FILTER),
	STATUS_TEMI = (0x1 << SDEC_DEBUG_STATUS_TEMI),
	STATUS_INPUT = (0x1 << SDEC_DEBUG_STATUS_INPUT),
	STATUS_PCR_RECOVERY = (0x1 << SDEC_DEBUG_STATUS_PCR_RECOVERY),
	STATUS_NOTI = (0x1 << SDEC_DEBUG_STATUS_NOTI),
	STATUS_ALL = 0xFFFFFF,
};

enum {
	DEBUG_ID_VERSION = 0,
	DEBUG_ID_INSTANTBOOT,
};

static int suspend_resume_ctrl(struct sdec_device *dev, bool status)
{
	int ret;

	if (status == 0) {
		ret = sdec_device_suspend(dev);
	} else {
		ret = sdec_device_resume(dev);
	}

	return ret;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		dprintf("20190325.0\n");
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
	struct sdec_device *dev = item->private;

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

/** STATUS **/

static int debug_status_show(struct te_debug_item *item, struct seq_file *m)
{
	int i;
	int cnt = 0;
	struct sdec_device *dev = item->private;

	for (i = 0; i < SDEC_DEBUG_STATUS_MAX; i++) {
		if (item->flags & (0x1 << i)) {
			sdec_debug_show_t func = dev->debug.show_status[i];
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
	DBGITM_SIM_R("pid_filter", &debug_status_ops, STATUS_PID_FILTER),
	DBGITM_SIM_R("stream_filter", &debug_status_ops, STATUS_STREAM_FILTER),
	DBGITM_SIM_R("mcu_filter", &debug_status_ops, STATUS_MCU_FILTER),
	DBGITM_SIM_R("temi", &debug_status_ops, STATUS_TEMI),
	DBGITM_SIM_R("input", &debug_status_ops, STATUS_INPUT),
	DBGITM_SIM_R("pcr_recovery", &debug_status_ops, STATUS_PCR_RECOVERY),
	DBGITM_SIM_R("noti", &debug_status_ops, STATUS_NOTI),
	DBGITM_SIM_R("status", &debug_status_ops, STATUS_ALL),
};

/* sdec sub device functions */

static int debug_dev_init(struct sdec_device *dev)
{
	int ret, i;
	struct sdec_dev_debug *d = &dev->debug;

	d->dir = te_debug_create_dir(SDEC_MODULE, NULL);
	CHECK_ERROR(!d->dir, return -EIO, "Err in te_debug_create_dir");

	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_channel *c = &dev->channels[i];

		snprintf(c->debug_name, sizeof(c->debug_name), "%d", i);
		c->debug_dir = te_debug_create_dir(c->debug_name, d->dir);
	}
	ret = debug_create_item_files(debug_list, dev, d->dir);

	return ret;
}

static void debug_dev_release(struct sdec_device *dev)
{
	te_debug_remove_dir(dev->debug.dir);
}

int sdec_debug_register_status_show(struct sdec_device *dev,
				    enum sdec_debug_status status,
				    sdec_debug_show_t show)
{
	struct sdec_dev_debug *d = &dev->debug;

	if (status >= SDEC_DEBUG_STATUS_MAX)
		return -EINVAL;

	d->show_status[status] = show;

	return 0;
}

const struct sdec_sub_driver sdec_debug_driver = {
	.name = "sdec_debug",
	.early_init = debug_dev_init,
	.release = debug_dev_release,
};

/** @} */
