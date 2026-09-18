/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
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
 *  TE(Transport Engine) Driver
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2021-06-17
 *  @note		Additional information.
 */

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "te_impl.h"

static DEFINE_MUTEX(clockgate_lock);

static int do_clockgate(struct te_device *dev, bool disable)
{
	int i, ret;

	pmlog_info(dev, 0, disable ? "suspend" : "resume",
		   "try to clock_gating");

	if (disable) {
		te_halt_timer(dev, true);

		for (i = 0; i < dev->num_mcu; i++) {
			ret = te_mcu_stall(dev, i, true);
			pmlog_info(dev, ret, "suspend", "mcu stall");
			if (ret)
				return ret;
		}

		ret = TE_REG_ClockGate(true);
		pmlog_info(dev, ret, "suspend", "clock gating");
		if (ret)
			return ret;
	} else {
		ret = TE_REG_ClockGate(false);
		pmlog_info(dev, ret, "resume", "clock gating");

		for (i = 0; i < dev->num_mcu; i++) {
			ret = te_mcu_stall(dev, i, false);
			pmlog_info(dev, ret, "resume", "mcu stall");
		}

		te_halt_timer(dev, false);
	}

	return 0;
}

/* Debug Function */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
enum {
	DEBUG_ID_CLOCKGATE = 0,
	DEBUG_ID_REFCNT,
};

static const struct te_val_str gating_dev_str[] = {
	{TE_DEVICE_TYPE_TE, "TE"},
	{TE_DEVICE_TYPE_ARIB2, "ARIB2"},
	{TE_DEVICE_TYPE_ATSC3, "ATSC3"},
	{TE_DEVICE_TYPE_CI14, "CI14"},
	{TE_DEVICE_TYPE_CRYPTO, "CRYPTO"},
	{TE_DEVICE_TYPE_DVB_CI14, "DVB_CI14"},
	{TE_DEVICE_TYPE_DVB_DELIVERY, "DELIVERY"},
	{TE_DEVICE_TYPE_DVB_DEMUX, "DEMUX"},
	{TE_DEVICE_TYPE_DVB_DVR, "DVR"},
	{TE_DEVICE_TYPE_PVR, "PVR"},
	{TE_DEVICE_TYPE_SDEC, "SDEC"},
	{TE_DEVICE_TYPE_MCU, "MCU"},
	{TE_DEVICE_TYPE_CI, "CI"},
	{TE_DEVICE_TYPE_CI20, "CI20"},
	{TE_DEVICE_TYPE_DEMOD, "DEMOD"},
};

static const struct te_val_str rpm_status_str[] = {
	{RPM_ACTIVE, "ACTIVE"},
	{RPM_RESUMING, "RESUMING"},
	{RPM_SUSPENDED, "SUSPENDED"},
	{RPM_SUSPENDING, "SUSPENDING"},
};

static const char *get_gating_dev_to_str(enum te_device_type type)
{
	return find_match_string(gating_dev_str, type, "Invalid");
}

static const char *get_rpm_status_to_str(enum rpm_status status)
{
	return find_match_string(rpm_status_str, status, "unknown");
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct te_device *dev = item->private;
	struct dev_pm_info *power = &dev->pdev->dev.power;
	int i, cnt, ret = 0;

	switch (item->flags) {
	case DEBUG_ID_CLOCKGATE:
		dprintf("%s\n", get_rpm_status_to_str(power->runtime_status));
		break;

	case DEBUG_ID_REFCNT:
		dprintf("total:%d (pm actual:%d)\n\n", dev->clockgate.ref_cnt,
			 atomic_read(&power->usage_count));
		for (i = 0; i < TE_DEVICE_TYPE_MAX; i++) {
			cnt = dev->clockgate.dev_cnt[i];
			if (!cnt)
				continue;

			dprintf("%s: %d\n", get_gating_dev_to_str(i), cnt);
		}
		break;
	default:
		ret = -EPERM;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	struct te_device *dev = item->private;
	u32 val;
	int i, cnt, ret = 0;

	switch (item->flags) {
	case DEBUG_ID_CLOCKGATE: //TODO: how to protect from user's node usage
		val = simple_strtoul(str, NULL, 0);

		cnt = dev->clockgate.ref_cnt;

		if (val) {
			if (pm_runtime_status_suspended(&dev->pdev->dev)) {
				return -EPERM;
			}

			for (i = 0; i < cnt; i++)
				pm_runtime_put_sync(&dev->pdev->dev);
		} else {
			if (!pm_runtime_status_suspended(&dev->pdev->dev)) {
				return -EPERM;
			}

			for (i = 0; i < cnt; i++)
				pm_runtime_get_sync(&dev->pdev->dev);
		}

		break;

	default:
		ret = -EPERM;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("clock_gate", &debug_ops, DEBUG_ID_CLOCKGATE),
	DBGITM_SIM_R("refcnt", &debug_ops, DEBUG_ID_REFCNT),
};

static void init_debug(struct te_device *dev)
{
	debug_create_item_files(debug_list, dev, dev->debug.dir);
}

static void init_clockgate(struct te_device *dev)
{
	do_clockgate(dev, true);
	pm_runtime_enable(&dev->pdev->dev);
	pm_runtime_forbid(&dev->pdev->dev);
}

int te_clockgate_do_clockgate(struct te_device *dev, bool disable)
{
	int ret;

	mutex_lock(&clockgate_lock);
	ret = do_clockgate(dev, disable);
	mutex_unlock(&clockgate_lock);

	return ret;
}

int te_clockgate_init(struct te_device *dev)
{
	init_clockgate(dev);
	init_debug(dev);

	return 0;
}

int te_clockgate_suspend(struct te_device *dev)
{
	//nothing to do
	return 0;
}

int te_clockgate_resume(struct te_device *dev)
{
	//nothing to do
	return 0;
}

int te_clockgate_acquire_clock(struct te_device *dev, enum te_device_type type)
{
	struct te_dev_clockgate *cg = &dev->clockgate;

	if (type >= TE_DEVICE_TYPE_MAX)
		return -EINVAL;

	pm_runtime_get_sync(&dev->pdev->dev);

	mutex_lock(&clockgate_lock);

	cg->ref_cnt++;
	cg->dev_cnt[type]++;

	if (type == TE_DEVICE_TYPE_DEMOD)
		pmlog_info(dev, 0, "resume", "enable demod");

	log_device("ref_cnt:%d(%s)", cg->ref_cnt, get_gating_dev_to_str(type));

	mutex_unlock(&clockgate_lock);

	return 0;
}

static void print_ref_cnt(struct te_device *dev)
{
	int i, cnt;

	for (i = 0; i < TE_DEVICE_TYPE_MAX; i++) {
		cnt = dev->clockgate.dev_cnt[i];
		if (!cnt)
			continue;

		log_error("%s: %d", get_gating_dev_to_str(i), cnt);
	}
}

int te_clockgate_release_clock(struct te_device *dev, enum te_device_type type)
{
	struct te_dev_clockgate *cg = &dev->clockgate;

	if (type >= TE_DEVICE_TYPE_MAX)
		return -EINVAL;

	mutex_lock(&clockgate_lock);

	if (unlikely(cg->ref_cnt == 0)) {
		log_error("Fatal error: ref_cnt is already zero; last (%s)",
			  get_gating_dev_to_str(type));
		print_ref_cnt(dev);
		mutex_unlock(&clockgate_lock);
		return -EFAULT;
	}

	cg->dev_cnt[type]--;
	cg->ref_cnt--;

	log_device("ref_cnt:%d(%s)", cg->ref_cnt, get_gating_dev_to_str(type));
	if (type == TE_DEVICE_TYPE_DEMOD)
		pmlog_info(dev, 0, "suspend", "disable demod");

	mutex_unlock(&clockgate_lock);

	pm_runtime_put_sync(&dev->pdev->dev);

	return 0;
}
