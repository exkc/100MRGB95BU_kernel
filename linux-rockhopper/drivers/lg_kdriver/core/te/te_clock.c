/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2018-07-09
 *  @note	Additional information.
 */

#include "te_impl.h"


static int debug_stc_show(struct te_debug_item *item, struct seq_file *m)
{
	struct te_config *cfg = te_get_config();
	int ret;
	u32 base_32, base_31_0, ext;

	if (!cfg->no_stcc_bug) {
		ret = TE_REG_GetLiveStcc(item->flags, &base_32, &base_31_0, &ext);
		if (ret)
			return ret;
	} else {
		ret = te_ipc_get_stcc(item->flags, &base_32, &base_31_0);
		if (ret)
			return ret;
		ext = 0;
	}

	seq_printf(m, "0x%x%08x\n", (base_32 & 0x1), base_31_0);

	return 0;
}

static int debug_stc_write(struct te_debug_item *item, char *str)
{
	int ret;
	u32 base_32, base_31_0;
	unsigned long long v;
	u8 idx = item->flags;
	struct te_config *cfg = te_get_config();

	if (!strcasecmp("reset", str)) {
		if (!cfg->no_stcc_bug) {
			return TE_REG_ResetStcc(idx);
		} else {
			return te_ipc_reset_stcc(idx);
		}
	}

	v = simple_strtoull(str, NULL, 0);

	base_32 = (v & 0x100000000ULL) ? 1 : 0;
	base_31_0 = v & 0xFFFFFFFFULL;

	if (!cfg->no_stcc_bug) {
		ret = TE_REG_SetStcc(idx, base_32, base_31_0);
	} else {
		ret = te_ipc_set_stcc(idx, base_32, base_31_0);
	}

	return ret;
}

static int debug_gstc_show(struct te_debug_item *item, struct seq_file *m)
{
	struct te_config *cfg = te_get_config();
	int ret;
	u32 base_32, base_31_0, ext;

	if (!cfg->no_stcc_bug) {
		ret = TE_REG_GetGstcc(item->flags, &base_32, &base_31_0, &ext);
		if (ret)
			return ret;
	} else {
		ret = te_ipc_get_gstcc(item->flags, &base_32, &base_31_0);
		if (ret)
			return ret;
		ext = 0;
	}

	seq_printf(m, "0x%x%08x\n", (base_32 & 0x1), base_31_0);

	return 0;
}

static int debug_gstc_write(struct te_debug_item *item, char *str)
{
	struct te_config *cfg = te_get_config();
	int ret;
	u32 base_32, base_31_0;
	unsigned long long v;
	u8 idx = item->flags;

	if (!strcasecmp("reset", str)) {
		if (!cfg->no_stcc_bug) {
			return TE_REG_ResetGstcc(idx);
		} else {
			return te_ipc_reset_gstcc(idx);
		}
	}

	v = simple_strtoull(str, NULL, 0);

	base_32 = (v & 0x100000000ULL) ? 1 : 0;
	base_31_0 = v & 0xFFFFFFFFULL;

	if (!cfg->no_stcc_bug) {
		ret = TE_REG_SetGstcc(idx, base_32, base_31_0, 0);
	} else {
		ret = te_ipc_set_gstcc(idx, base_32, base_31_0);
	}

	return ret;
}

static const struct te_debug_simple_ops debug_stc_ops = {
	.show = debug_stc_show,
	.write = debug_stc_write,
};

static const struct te_debug_simple_ops debug_gstc_ops = {
	.show = debug_gstc_show,
	.write = debug_gstc_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("stc0", &debug_stc_ops, 0),
	DBGITM_SIM("stc1", &debug_stc_ops, 1),
	DBGITM_SIM("stc2", &debug_stc_ops, 2),
	DBGITM_SIM("stc3", &debug_stc_ops, 3),
	DBGITM_SIM("gstc0", &debug_gstc_ops, 0),
	DBGITM_SIM("gstc1", &debug_gstc_ops, 1),
	DBGITM_SIM("gstc2", &debug_gstc_ops, 2),
	DBGITM_SIM("gstc3", &debug_gstc_ops, 3),
};

static void init_debug(struct te_device *dev)
{
	struct te_dev_clk *clk = &dev->clk;

	clk->debug_dir = te_debug_create_dir("clock", dev->debug.dir);
	if (!clk->debug_dir) {
		log_error("can't create 'clock' debug dir\n");
		return;
	}

	debug_create_item_files(debug_list, dev, clk->debug_dir);
}


static int dev_init(struct te_device *dev)
{
	init_debug(dev);
	return 0;
}

static void dev_release(struct te_device *dev)
{

}

const struct te_sub_driver te_clk_driver = {
	.name = "te_clock",
	.init = dev_init,
	.release = dev_release,
};
