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

#include "te_impl.h"
#include "te_kapi.h"

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	DEBUG_ID_VERSION = 0,
	DEBUG_ID_DELAY,
	DEBUG_ID_REG,
	DEBUG_ID_REG_BLOCK,
	DEBUG_ID_REG_OFFSET,
	DEBUG_ID_REG_VALUE,
	DEBUG_ID_REG_LOGMASK,
};

enum {
	REGDUMP_MASK_TOP = (0x1 << LX_TE_BLOCK_TOP),
	REGDUMP_MASK_TPI = (0x1 << LX_TE_BLOCK_TPI),
	REGDUMP_MASK_FE_PIDF = (0x1 << LX_TE_BLOCK_FE_PIDF),
	REGDUMP_MASK_FE_TSBUF = (0x1 << LX_TE_BLOCK_FE_TSBUF),
	REGDUMP_MASK_FE_STCC = (0x1 << LX_TE_BLOCK_FE_STCC),
	REGDUMP_MASK_BE = (0x1 << LX_TE_BLOCK_BE_TOP),
	REGDUMP_MASK_UPLOAD0 = (0x1 << LX_TE_BLOCK_UPLOAD0),
	REGDUMP_MASK_UPLOAD1 = (0x1 << LX_TE_BLOCK_UPLOAD1),
	REGDUMP_MASK_CIPLUS = (0x1 << LX_TE_BLOCK_CIPLUS),
	REGDUMP_MASK_A3 = (0x1 << LX_TE_BLOCK_A3),
	REGDUMP_MASK_ARIB2 = (0x1 << LX_TE_BLOCK_ARIB2),
	REGDUMP_MASK_DUMPER = (0x1 << LX_TE_BLOCK_DUMPER),
	REGDUMP_MASK_DSC0 = (0x1 << LX_TE_BLOCK_DSC0),
	REGDUMP_MASK_DSC1 = (0x1 << LX_TE_BLOCK_DSC1),
	REGDUMP_MASK_MCU0 = (0x1 << LX_TE_BLOCK_MCU0),
	REGDUMP_MASK_MCU1 = (0x1 << LX_TE_BLOCK_MCU1),
	REGDUMP_MASK_MCU_ALL = (REGDUMP_MASK_MCU0 | REGDUMP_MASK_MCU1),
	REGDUMP_MASK_ALL = 0xFFFFFF & ~(REGDUMP_MASK_DSC0 | REGDUMP_MASK_DSC1),
};

struct debug_reg_ctrl {
	LX_TE_BLOCK_T block;
	u32 offset;
};

static const struct te_val_str reg_block_str[] = {
	{LX_TE_BLOCK_TOP, "TOP"},
	{LX_TE_BLOCK_TPI, "TPI"},
	{LX_TE_BLOCK_FE_PIDF, "FE_PIDF"},
	{LX_TE_BLOCK_FE_TSBUF, "FE_TSBUF"},
	{LX_TE_BLOCK_FE_STCC, "FE_STCC"},
	{LX_TE_BLOCK_BE_TOP, "BE"},
	{LX_TE_BLOCK_UPLOAD0, "UPLOAD0"},
	{LX_TE_BLOCK_UPLOAD1, "UPLOAD1"},
	{LX_TE_BLOCK_MCU0, "MCU0"},
	{LX_TE_BLOCK_MCU1, "MCU1"},
	{LX_TE_BLOCK_CIPLUS, "CIPLUS"},
	{LX_TE_BLOCK_A3, "A3"},
	{LX_TE_BLOCK_ARIB2, "ARIB2"},
	{LX_TE_BLOCK_DUMPER, "DUMPER"},
	{LX_TE_BLOCK_DSC0, "DSC0"},
	{LX_TE_BLOCK_DSC1, "DSC1"},
};

static struct debug_reg_ctrl reg_ctrl;

static int reg_write(LX_TE_BLOCK_T block, u32 offset, u32 value)
{
	unsigned long base_addr;
	u32 max_size;

	base_addr = (unsigned long)TE_REG_GetBaseAddr(block);
	max_size = TE_REG_GetSize(block);

	if (base_addr == 0 || offset >= max_size || (offset % 4) != 0)
		return -EINVAL;

	TE_WRITE32(base_addr + offset, value);

	return 0;
}

static int reg_read(LX_TE_BLOCK_T block, u32 offset, u32 *value)
{
	unsigned long base_addr;
	u32 max_size;

	base_addr = (unsigned long)TE_REG_GetBaseAddr(block);
	max_size = TE_REG_GetSize(block);

	if (base_addr == 0 || offset >= max_size || (offset % 4) != 0)
		return -EINVAL;

	*value = TE_READ32(base_addr + offset);

	return 0;
}

struct reg_log_level {
	char c;
	const char *str;
	int bit;
};

static const struct reg_log_level reg_log_level_table[] = {
	{'t', "TOP", REG_LOG_TOP_BIT},
	{'i', "TPI", REG_LOG_TPI_BIT},
	{'f', "FE", REG_LOG_FE_BIT},
	{'b', "BE", REG_LOG_BE_BIT},
	{'u', "UPLOAD", REG_LOG_UPLOAD_BIT},
	{'s', "DESC", REG_LOG_DSC_BIT},
	{'c', "CI+", REG_LOG_CIPLUS_BIT},
	{'p', "CTOP", REG_LOG_CTOP_BIT},
	{'a', "ATSC3.0", REG_LOG_ATSC3_BIT},
	{'d', "DUMPER", REG_LOG_DUMPER_BIT},
	{'z', "DSC", REG_LOG_DSC_BIT},
	{'v', "VERBOSE", REG_LOG_VERBOSE_BIT},
};

static void show_reg_logmask(struct seq_file *m)
{
	int i;
	u32 value = TE_REG_GetLogMask();
	const struct reg_log_level *l = reg_log_level_table;
	int size = ARRAY_SIZE(reg_log_level_table);

	for (i = 0; i < size; i++) {
		dprintf("(%c)%8s : %c\n", l[i].c, l[i].str,
			((0x1 << l[i].bit) & value) ? 'O' : 'X');
	}
}

static void set_reg_logmask(const char *cmd)
{
	const char *p = cmd;
	int i, bit;
	int (*op)(enum te_reg_log_bit bit);
	const struct reg_log_level *l = reg_log_level_table;
	int size = ARRAY_SIZE(reg_log_level_table);

	bit = -1;
	op = NULL;
	while (*p != 0) {
		if (*p == '+') {
			op = TE_REG_EnableLogMask;
		} else if (*p == '-') {
			op = TE_REG_DisableLogMask;
		} else if (op != NULL) {
			for (i = 0; i < size; i++) {
				if (*p == l[i].c) {
					bit = l[i].bit;
					break;
				}
			}

			if (bit != -1) {
				op(bit);
				break;
			} else {
				op = NULL;
			}
		} else {
			op = NULL;
		}
		p++;
	}
}

static int reg_write_command(const char *command)
{
	int rc;
	char name[32];
	u32 offset, value;
	LX_TE_BLOCK_T block;

	rc = sscanf(command, "%31s %i %i", name, &offset, &value);
	if (rc != 3)
		return -EINVAL;

	block = find_match_value(reg_block_str, name, LX_TE_BLOCK_NONE);
	if (block == LX_TE_BLOCK_NONE)
		return -EINVAL;

	return reg_write(block, offset, value);
}

static int reg_show(struct te_debug_item *item, struct seq_file *m)
{
	int i;
	const struct te_val_str *l = reg_block_str;
	int size = ARRAY_SIZE(reg_block_str);

	for (i = 0; i < size; i++) {
		if (item->flags & (0x1 << l[i].val)) {
			seq_printf(m, "%s\n", l[i].str);
			te_reg_dump_seq_file(l[i].val, m);
			seq_printf(m, "\n");
		}
	}

	return 0;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	int i;
	u32 value;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		dprintf("20180713.0\n");
		break;

	case DEBUG_ID_REG:
		for (i = 0; i < ARRAY_SIZE(reg_block_str); i++)
			dprintf("%s\n", reg_block_str[i].str);
		break;

	case DEBUG_ID_REG_BLOCK:
		dprintf("%s\n", find_match_string(reg_block_str, reg_ctrl.block,
						  "none"));
		break;

	case DEBUG_ID_REG_OFFSET:
		dprintf("0x%x\n", reg_ctrl.offset);
		break;

	case DEBUG_ID_REG_VALUE:
		ret = reg_read(reg_ctrl.block, reg_ctrl.offset, &value);
		if (!ret)
			dprintf("0x%x\n", value);
		break;

	case DEBUG_ID_REG_LOGMASK:
		show_reg_logmask(m);
		break;

	default:
		ret = -EPERM;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	u32 val;
	int ret = 0;

	switch (item->flags) {
	case DEBUG_ID_DELAY:
		val = simple_strtoul(str, NULL, 0);
		msleep(val);
		break;

	case DEBUG_ID_REG:
		ret = reg_write_command(str);
		break;

	case DEBUG_ID_REG_BLOCK:
		val = find_match_value(reg_block_str, str, LX_TE_BLOCK_NONE);

		if (val == LX_TE_BLOCK_NONE)
			ret = -EINVAL;
		else
			reg_ctrl.block = val;
		break;

	case DEBUG_ID_REG_OFFSET:
		val = simple_strtoul(str, NULL, 0);
		reg_ctrl.offset = val;
		break;

	case DEBUG_ID_REG_VALUE:
		val = simple_strtoul(str, NULL, 16);	/* base 16 */
		ret = reg_write(reg_ctrl.block, reg_ctrl.offset, val);
		break;

	case DEBUG_ID_REG_LOGMASK:
		set_reg_logmask(str);
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

int te_get_authority(enum ipc_authority_module module)
{
	if (module >= IPC_AUTH_MAX)
		return -EINVAL;

	return te_ipc_get_authority(module);
}

struct te_debug_dir *te_get_debug_dir(struct te_device *dev)
{
	return dev->debug.dir;
}

static ssize_t data_write(struct file *file, const char __user *buf,
			size_t len, loff_t *ppos)
{
	char *data;

	data = vmalloc(len+1);
	if (!data)
		return -ENOMEM;

	if (copy_from_user(data+1, buf, len)) {
		vfree(data);
		return -EFAULT;
	}
	data[0] = IPC_WRITE_DEBUG;

	te_ipc_write_data(data, len+1);

	vfree(data);

	return len;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
static const struct proc_ops data_fops = {
	.proc_write = data_write,
};
#else
static const struct file_operations data_fops = {
	.write = data_write,
};
#endif

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("version", &debug_ops, DEBUG_ID_VERSION),
	DBGITM_SIM("delay", &debug_ops, DEBUG_ID_DELAY),
	DBGITM_SIM("reg", &debug_ops, DEBUG_ID_REG),
	DBGITM_SIM("reg_block", &debug_ops, DEBUG_ID_REG_BLOCK),
	DBGITM_SIM("reg_offset", &debug_ops, DEBUG_ID_REG_OFFSET),
	DBGITM_SIM("reg_value", &debug_ops, DEBUG_ID_REG_VALUE),
	DBGITM_SIM("reg_logmask", &debug_ops, DEBUG_ID_REG_LOGMASK),

	DBGITM_SHOW("regdump", reg_show, REGDUMP_MASK_ALL),
	DBGITM_SHOW("regdump_top", reg_show, REGDUMP_MASK_TOP),
	DBGITM_SHOW("regdump_tpi", reg_show, REGDUMP_MASK_TPI),
	DBGITM_SHOW("regdump_fe_pidf", reg_show, REGDUMP_MASK_FE_PIDF),
	DBGITM_SHOW("regdump_fe_tsbuf", reg_show, REGDUMP_MASK_FE_TSBUF),
	DBGITM_SHOW("regdump_fe_stcc", reg_show, REGDUMP_MASK_FE_STCC),
	DBGITM_SHOW("regdump_be", reg_show, REGDUMP_MASK_BE),
	DBGITM_SHOW("regdump_up0", reg_show, REGDUMP_MASK_UPLOAD0),
	DBGITM_SHOW("regdump_up1", reg_show, REGDUMP_MASK_UPLOAD1),
	DBGITM_SHOW("regdump_ciplus", reg_show, REGDUMP_MASK_CIPLUS),
	DBGITM_SHOW("regdump_a3", reg_show, REGDUMP_MASK_A3),
	DBGITM_SHOW("regdump_arib2", reg_show, REGDUMP_MASK_ARIB2),
	DBGITM_SHOW("regdump_dumper", reg_show, REGDUMP_MASK_DUMPER),
	DBGITM_SHOW("regdump_dsc0", reg_show, REGDUMP_MASK_DSC0),
	DBGITM_SHOW("regdump_dsc1", reg_show, REGDUMP_MASK_DSC1),
	DBGITM_SHOW("regdump_mcu0", reg_show, REGDUMP_MASK_MCU0),
	DBGITM_SHOW("regdump_mcu1", reg_show, REGDUMP_MASK_MCU1),

	DBGITM_FOPS("data_write", &data_fops, 0),
};

static int debug_init(struct te_device *dev)
{
	struct te_dev_debug *d = &dev->debug;

	d->dir = te_debug_create_dir(TE_MODULE, NULL);
	CHECK_ERROR(!d->dir, return -EIO, "Err in te_debug_create_dir");

	debug_create_item_files(debug_list, dev, d->dir);

	return 0;
}

static void debug_release(struct te_device *dev)
{
	te_debug_remove_dir(dev->debug.dir);
}

const struct te_sub_driver te_debug_driver = {
	.name = "te_debug",
	.early_init = debug_init,
	.release = debug_release,
};

/** @} */
