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

/** @file
 *
 *  CI SPI Interface for ION hardware
 *
 *  @author	Ilkyu Kim
 *  @version	1.1
 *  @date	2025-03-06
 *  @note	Additional information.
 */

#include <lg1k/te/util.h>
#include <lg1k/te/ion.h>
#include <lg1k/te/debug.h>
#include "te_impl.h"
#include "ion_debug.h"
#include "ion_ci_reg.h"
#include "ion_io_reg.h"
#include "ion_reg_db.h"
#include "ion_debug.h"

#ifndef CONFIG_ION_MASTER_SLAVE
#define ION_DEBUG_CH_NUM 1
#else
#define ION_DEBUG_CH_NUM 2
#endif

enum ion_reg_mode {
	ION_REG_MODE_IO = 0,
	ION_REG_MODE_CI,
	ION_REG_MODE_MAX
};

/* Debug Feature */
struct debug_reg_ctrl {
	enum ion_reg_mode mode;
	u8 ch;
	u16 offset;
};

static struct debug_reg_ctrl reg_ctrl;

enum {
	DEBUG_ID_CHANNEL = 0,
	DEBUG_ID_OFFSET,
	DEBUG_ID_REG,
	DEBUG_ID_CLOCK,
	DEBUG_ID_MODE,
	DEBUG_ID_IO_TYPE,
	DEBUG_ID_MAX,
};

static const struct te_val_str ion_mode_str[] = {
	{ION_REG_MODE_IO, "IO"},
	{ION_REG_MODE_CI, "CI"},
};

static const char *get_reg_mode_str(enum ion_reg_mode mode)
{
	return find_match_string(ion_mode_str, mode, "Invalid");
}

static enum ion_reg_mode str_to_reg_mode(const char *str)
{
	return find_match_value(ion_mode_str, str, ION_REG_MODE_MAX);
}

static const struct te_val_str ion_io_type_str[] = {
	{ION_TPI_TS, "TS"},
	{ION_TPI_LGC, "LGC"},
	{ION_TPI_TLV, "TLV"},
};

static const char *get_io_type_str(enum te_ion_tpi_type type)
{
	return find_match_string(ion_io_type_str, type, "Invalid");
}

static enum te_ion_tpi_type str_to_io_tpi_type(const char *str)
{
	return find_match_value(ion_io_type_str, str, ION_TPI_MAX);
}

enum te_ion_block {
	ION_BLOCK_CTOP,
	ION_BLOCK_SARADC0,
	ION_BLOCK_SARADC1,
	ION_BLOCK_MCRG,
	ION_BLOCK_BND,
	ION_BLOCK_SCRG,
	ION_BLOCK_SRDS12TO3,
	ION_BLOCK_SRDS32TO1_0,
	ION_BLOCK_IOMUX_CTRL,
	ION_BLOCK_SPI_TO_AHB,
	ION_BLOCK_SRDS32TO1_1
};

enum {
	REGDUMP_MASK_TOP = (0x1 << ION_BLOCK_CTOP),
	REGDUMP_MASK_SARADC0 = (0x1 << ION_BLOCK_SARADC0),
	REGDUMP_MASK_SARADC1 = (0x1 << ION_BLOCK_SARADC1),
	REGDUMP_MASK_MCRG = (0x1 << ION_BLOCK_MCRG),
	REGDUMP_MASK_BND = (0x1 << ION_BLOCK_BND),
	REGDUMP_MASK_SCRG = (0x1 << ION_BLOCK_SCRG),
	REGDUMP_MASK_SRDS12TO3 = (0x1 << ION_BLOCK_SRDS12TO3),
	REGDUMP_MASK_SRDS32TO1_0 = (0x1 << ION_BLOCK_SRDS32TO1_0),
	REGDUMP_MASK_IOMUX_CTRL = (0x1 << ION_BLOCK_IOMUX_CTRL),
	REGDUMP_MASK_SPI_TO_AHB = (0x1 << ION_BLOCK_SPI_TO_AHB),
	REGDUMP_MASK_SRDS32TO1_1 = (0x1 << ION_BLOCK_SRDS32TO1_1),
	REGDUMP_MASK_ALL = 0x7FF,

};

static const struct te_val_str reg_block_str[] = {
	{ION_BLOCK_CTOP, "CTOP"},
	{ION_BLOCK_SARADC0, "SARADC0"},
	{ION_BLOCK_SARADC1, "SARADC1"},
	{ION_BLOCK_MCRG, "MCRG"},
	{ION_BLOCK_BND, "BND"},
	{ION_BLOCK_SCRG, "SCRG"},
	{ION_BLOCK_SRDS12TO3, "SRDS12TO3"},
	{ION_BLOCK_SRDS32TO1_0, "SRDS32TO1_0"},
	{ION_BLOCK_IOMUX_CTRL, "IOMUX_CTRL"},
	{ION_BLOCK_SPI_TO_AHB, "SPI_TO_AHB"},
	{ION_BLOCK_SRDS32TO1_1, "SRDS32TO1_1"}
};

static int get_reg_block_info(enum te_ion_block block, u32 *addr, u32 *size)
{
	switch (block) {
	case ION_BLOCK_CTOP:
		*addr = CTOP_BASE_ADDRESS;
		*size = CTOP_REG_SIZE;
		break;
	case ION_BLOCK_SARADC0:
		*addr = SARADC0_BASE_ADDRESS;
		*size = SARADC0_REG_SIZE;
		break;
	case ION_BLOCK_SARADC1:
		*addr = SARADC1_BASE_ADDRESS;
		*size = SARADC1_REG_SIZE;
		break;
	case ION_BLOCK_MCRG:
		*addr = ION_MCRG_BASE_ADDRESS;
		*size = ION_MCRG_REG_SIZE;
		break;
	case ION_BLOCK_BND:
		*addr = ION_BND_BASE_ADDRESS;
		*size = ION_BND_REG_SIZE;
		break;
	case ION_BLOCK_SCRG:
		*addr = ION_SCRG_BASE_ADDRESS;
		*size = ION_SCRG_REG_SIZE;
		break;
	case ION_BLOCK_SRDS12TO3:
		*addr = SRDS12TO3_BASE_ADDRESS;
		*size = SRDS12TO3_REG_SIZE;
		break;
	case ION_BLOCK_SRDS32TO1_0:
		*addr = SRDS32TO1_0_BASE_ADDRESS;
		*size = SRDS32TO1_0_REG_SIZE;
		break;
	case ION_BLOCK_IOMUX_CTRL:
		*addr = IOMUX_CTRL_BASE_ADDRESS;
		*size = IOMUX_CTRL_REG_SIZE;
		break;
	case ION_BLOCK_SPI_TO_AHB:
		*addr = SPI_TO_AHB_BASE_ADDRESS;
		*size = SPI_TO_AHB_REG_SIZE;
		break;
	case ION_BLOCK_SRDS32TO1_1:
		*addr = SRDS32TO1_1_BASE_ADDRESS;
		*size = SRDS32TO1_1_REG_SIZE;
	break;
	default:
		return -EINVAL;
	}

	return 0;
}

static void ion_reg_dump(struct seq_file *m, struct te_dev_ion *dev,
			 enum ion_reg_mode mode, u8 ch, enum te_ion_block block)
{
	u32 addr, size;
	u32 offset, val;
	int rc;

#ifndef CONFIG_ION_MASTER_SLAVE
	if (ch == 1) {
		seq_printf(m, "internal rx dump not supported\n");
		return;
	}
#endif

	rc = get_reg_block_info(block, &addr, &size);
	if (rc) {
		seq_printf(m, "invalid block %u\n", block);
		return;
	}

	for (offset = 0; offset < size; offset += 4) {
		if (mode == ION_REG_MODE_IO) {
			ion_io_reg_read(dev, ch, &val, addr + offset);
		} else {
			ion_ci_reg_read(dev, ch, &val, addr + offset);
		}

		if ((offset & 0xF) == 0) {
			if (offset == 0)
				seq_printf(m, "%04x : ", offset);
			else
				seq_printf(m, "\n%04x : ", offset);
		}

		seq_printf(m, "%08x ", val);
	}
	seq_printf(m, "\n");
}

// ion0_rx not working properly yet
static int reg_show(struct te_debug_item *item, struct seq_file *m)
{
	struct te_dev_ion_debug_reg *r = item->private;
	const struct te_val_str *l = reg_block_str;
	int size = ARRAY_SIZE(reg_block_str);
	enum ion_reg_mode mode;
	u8 ch;
	int i;

	mode = (r->dev) ? ION_REG_MODE_CI : ION_REG_MODE_IO;
	ch = r->ch;

	for (i = 0; i < size; i++) {
		if (item->flags & (0x1 << l[i].val)) {
			seq_printf(m, "%s\n", l[i].str);
			ion_reg_dump(m, r->ion, mode, ch, l[i].val);
			seq_printf(m, "\n");
		}
	}

	return 0;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct te_dev_ion *dev = item->private;
	u32 val, ofs;
	u8 ch;
	int i;

	switch (item->flags) {
	case DEBUG_ID_CHANNEL:
		seq_printf(m, "channel: %u\n", reg_ctrl.ch);
		break;

	case DEBUG_ID_OFFSET:
		seq_printf(m, "offset: 0x%04x\n", reg_ctrl.offset);
		break;

	case DEBUG_ID_REG:
		if (reg_ctrl.ch >= ION_DEBUG_CH_NUM) {
			seq_printf(m, "invalid ch:%u\n", reg_ctrl.ch);
			return -EPERM;
		}
		ch = reg_ctrl.ch;
		ofs = reg_ctrl.offset;

		if (reg_ctrl.mode == ION_REG_MODE_CI) {
			ion_ci_reg_read(dev, ch, &val, ofs);
		} else if (reg_ctrl.mode == ION_REG_MODE_IO) {
			ofs += 0x10000;
			ion_io_reg_read(dev, ch, &val, ofs);
		} else {
			seq_printf(m, "invalid Mode %u\n", reg_ctrl.mode);
			break;
		}
		seq_printf(m, "[%u] [0x%04x]: %08x\n", ch, ofs, val);
		break;

	case DEBUG_ID_CLOCK:
		seq_printf(m, "[%u] %u (%u Mhz)\n", dev->ci_spi_ch,
			   dev->spi_clk, (dev->spi_clk / 1000 / 1000));
		break;

	case DEBUG_ID_MODE:
		seq_printf(m, "mode: %s\n", get_reg_mode_str(reg_ctrl.mode));
		break;

	case DEBUG_ID_IO_TYPE:
		for (i = 0; i < TE_ION_TPI_NUM; i++) {
			seq_printf(m, "[%d] io_type: %s (%s)\n", i,
				   get_io_type_str(dev->tpi[i].type),
				   dev->tpi[i].en ? "enable" : "disable");
		}
		break;

	default:
		return -EPERM;
	}

	return 0;
}

static int reg_write_command(struct te_dev_ion *dev, char *str)
{
	u8 ch;
	u32 addr;
	u32 val[4], v;
	int rc;

	rc = sscanf(str, "%8x %8x %8x %8x", val, val + 1, val + 2, val + 3);
	switch (rc) {
	case 1: //only value
		v = val[0];
		break;

	case 2: //addr, value
		reg_ctrl.offset = val[0];
		v = val[1];
		break;

	case 3: //ch, addr, value
		if (val[0] >= ION_DEBUG_CH_NUM) {
			log_error("invalid channel %u", val[0]);
			return -EFAULT;
		}

		reg_ctrl.ch = val[0];
		reg_ctrl.offset = val[1];
		v = val[2];
		break;

	case 4:
		if (val[0] > 1) {
			log_error("invalid ion %u", val[0]);
			return -EFAULT;
		} else if (val[1] >= ION_DEBUG_CH_NUM) {
			log_error("invalid channel %u", val[0]);
			return -EFAULT;
		}

		reg_ctrl.mode = (val[0] == 0) ?
			ION_REG_MODE_IO : ION_REG_MODE_CI;
		reg_ctrl.ch = val[1];
		reg_ctrl.offset = val[2];
		v = val[3];
		break;

	default:
		return -EPERM;
	}

	ch = reg_ctrl.ch;
	addr = reg_ctrl.offset;

	if (reg_ctrl.mode == ION_REG_MODE_CI) {
		return ion_ci_reg_write(dev, ch, v, addr);
	} else if (reg_ctrl.mode == ION_REG_MODE_IO) {
		return ion_io_reg_write(dev, ch, v, addr);
	} else {
		log_error("invalid mode %u", reg_ctrl.mode);
		return -EINVAL;
	}
}

static int set_io_type(struct te_dev_ion *dev, char *str)
{
	struct te_dev_ion_tpi *tpi;
	struct te_device *tdev;
	u32 idx;
	enum te_ion_tpi_type type;
	bool parallel;
	char ps_str[2], type_str[4];
	int rc;

	rc = sscanf(str, "%2x %1s %3s", &idx, ps_str, type_str);
	if (rc < 3)
		goto error;

	if (idx >= TE_ION_TPI_NUM)
		goto error;
	tpi = &dev->tpi[idx];
	if (!tpi)
		goto error;

	if (ps_str[0] == 'P') {
		parallel = true;
	} else if (ps_str[0] == 'S') {
		parallel = false;
	} else {
		goto error;
	}

	type = str_to_io_tpi_type(type_str);
	if (type == ION_TPI_MAX)
		goto error;

	tdev = container_of(dev, struct te_device, ion);

	switch (type) {
	case ION_TPI_TS:
	default:
		rc = ion_io_set_tp(tdev, tpi->idx, parallel);
		break;

	case ION_TPI_TLV:
		rc = ion_io_set_tlv(tdev, tpi->idx, parallel);
		break;

	case ION_TPI_LGC:
		rc = ion_io_set_lgc(tdev, tpi->idx, parallel);
		break;
	}

	return rc;

error:
	log_noti("set io\n    usage [tpi] [parallel/serial] [type]");
	log_noti("    tpi: 0, 1");
	log_noti("    parallel/serial: P, S");
	log_noti("    type: TS, TLV, LGC");
	return -EINVAL;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	struct te_dev_ion *dev = item->private;
	int rc;
	u32 val;
	enum ion_reg_mode mode;
	int ret = 0;
#define ION_REG_OFFSET_LIMIT 0xFFFF

	switch(item->flags) {
	case DEBUG_ID_CHANNEL:
		rc = sscanf(str, "%2x", &val);
		if (rc != 1)
			return -EINVAL;
		if (val >= ION_DEBUG_CH_NUM)
			return -EFAULT;

		reg_ctrl.ch = val;
		break;

	case DEBUG_ID_OFFSET:
		rc = sscanf(str, "%4x", &val);
		if (rc != 1)
			return -EINVAL;
		if (val > ION_REG_OFFSET_LIMIT)
			return -EFAULT;

		reg_ctrl.offset = val;
		break;

	case DEBUG_ID_REG:
		ret = reg_write_command(dev, str);
		break;

	case DEBUG_ID_MODE:
		mode = str_to_reg_mode(str);
		if (mode != ION_REG_MODE_MAX) {
			reg_ctrl.mode = mode;
		} else {
			ret = -EINVAL;
		}
		break;

	case DEBUG_ID_IO_TYPE:
		ret = set_io_type(dev, str);
		break;

	default:
		return -EPERM;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("channel", &debug_ops, DEBUG_ID_CHANNEL),
	DBGITM_SIM("offset", &debug_ops, DEBUG_ID_OFFSET),
	DBGITM_SIM("reg", &debug_ops, DEBUG_ID_REG),
	DBGITM_SIM_R("clock", &debug_ops, DEBUG_ID_CLOCK),
	DBGITM_SIM("mode", &debug_ops, DEBUG_ID_MODE),
	DBGITM_SIM("io_type", &debug_ops, DEBUG_ID_IO_TYPE),
};

static const struct te_debug_item_info regdump_list[] = {
	DBGITM_SHOW("regdump", reg_show, REGDUMP_MASK_ALL),
	DBGITM_SHOW("regdump_top", reg_show, REGDUMP_MASK_TOP),
	DBGITM_SHOW("regdump_saradc0", reg_show, REGDUMP_MASK_SARADC0),
	DBGITM_SHOW("regdump_saradc1", reg_show, REGDUMP_MASK_SARADC1),
	DBGITM_SHOW("regdump_mcrg", reg_show, REGDUMP_MASK_MCRG),
	DBGITM_SHOW("regdump_bnd", reg_show, REGDUMP_MASK_BND),
	DBGITM_SHOW("regdump_scrg", reg_show, REGDUMP_MASK_SCRG),
	DBGITM_SHOW("regdump_srds12to3", reg_show, REGDUMP_MASK_SRDS12TO3),
	DBGITM_SHOW("regdump_srds32to1_0", reg_show, REGDUMP_MASK_SRDS32TO1_0),
	DBGITM_SHOW("regdump_iomux_ctrl", reg_show, REGDUMP_MASK_IOMUX_CTRL),
	DBGITM_SHOW("regdump_spi_to_ahb", reg_show, REGDUMP_MASK_SPI_TO_AHB),
	DBGITM_SHOW("regdump_srds32to1_1", reg_show, REGDUMP_MASK_SRDS32TO1_1),
};

#define DEBUG_REG_NUM 4
int ion_debug_init(struct te_device *dev)
{
	int i, ret;
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_debug_reg *r;
	char str[8];

	reg_ctrl.mode = ION_REG_MODE_CI;
	reg_ctrl.ch = 0;
	reg_ctrl.offset = 0x44; // Safe area to write (TEST REGISTER)

	ion->debug_dir = te_debug_create_dir("ion", dev->debug.dir);
	if (!ion->debug_dir) {
		log_error("Err in te_debug_create_dir");
		return -EIO;
	}

	ret = debug_create_item_files(debug_list, ion, ion->debug_dir);
	if (ret) {
		log_error("error in create item files %d", ret);
		goto exit;
	}

	for (i = 0; i < DEBUG_REG_NUM; i++) {
		r = &ion->reg[i];
		r->dev = (i / 2);
		r->ch = (i & 1);
		r->ion = ion;

		snprintf(str, sizeof(str), "%d_%s", r->dev, (r->ch) ? "rx" :
			 "tx");
		r->debug_dir = te_debug_create_dir(str, ion->debug_dir);

		ret = debug_create_item_files(regdump_list, r, r->debug_dir);
		if (ret)
			log_error("error in create item files[%d] %d", i, ret);
	}

	log_noti("init done");

exit:
	return ret;
}

void ion_debug_release(struct te_device *dev)
{
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_debug_reg *r;
	int i;

	for (i = 0; i < DEBUG_REG_NUM; i++) {
		r = &ion->reg[i];
		te_debug_remove_dir(r->debug_dir);
	}

	te_debug_remove_dir(ion->debug_dir);
}
