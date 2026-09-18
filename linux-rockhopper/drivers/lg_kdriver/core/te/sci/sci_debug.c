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
 *  sci debug driver
 *
 *  author		yeonju.lee(yeonju.lee@lge.com)
 *  version		1.0
 *  date		2019.05.07
 *  note		Additional information.
 *
 */

#include "sci_impl.h"
#include "sci_reg.h"

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	DEBUG_ID_VERSION = 0,
	DEBUG_ID_LOGMASK,
	DEBUG_ID_REG_DUMP,
	DEBUG_ID_REG_WRITE,
	DEBUG_ID_PRINT_DATA,
};

enum sci_log_mask_bit {
	LOG_MASK_ISR = (0x1 << 0),
	LOG_MASK_REG = (0x1 << 1),
};

struct reg_log_level {
	char c;
	const char *str;
	int bit;
	void (*setlogmask)(int);
	u32 (*getlogmask)(void);
};

static const struct reg_log_level log_level_table[] = {
	{'i', "ISR", LOG_MASK_ISR, sci_isr_set_log_mask, sci_isr_get_log_mask},
	{'r', "REG", LOG_MASK_REG, sci_reg_set_log_mask, sci_reg_get_log_mask},
};

static void set_log_mask(const char *cmd)
{
	const char *p = cmd;
	int val, i;
	void (*op)(int en);
	const struct reg_log_level *l = log_level_table;
	int size = ARRAY_SIZE(log_level_table);

	val = -1;
	op = NULL;

	while (*p != 0) {
		if (*p == '+') {
			val = true;
		} else if (*p == '-') {
			val = false;
		} else if (val != -1) {
			for (i = 0; i < size; i++) {
				if (*p == l[i].c) {
					op = l[i].setlogmask;
				}
			}

			if (val != -1 && op != NULL) {
				op(val);
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

static void show_reg_logmask(struct seq_file *m)
{
	const struct reg_log_level *l = log_level_table;
	int size = ARRAY_SIZE(log_level_table);
	u32 value;
	int i;

	for (i = 0; i < size; i++) {
		dprintf("(%c)%5s :", l[i].c, l[i].str);

		value = l[i].getlogmask();
		dprintf("%c\n", value == 0 ? 'X' : 'O');
	}
}

static void show_reg_dump(struct seq_file *m)
{
	sci_reg_dump_seq_file(m);
}

static void show_print_data(struct te_debug_item *item, struct seq_file *m)
{
	bool enable;

	enable = sci_get_debug_print(item->private);
	dprintf("print %s\n", enable ? "enable" : "disable");
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		seq_printf(m, "20221206.0\n");
		break;
	case DEBUG_ID_LOGMASK:
		show_reg_logmask(m);
		break;
	case DEBUG_ID_REG_DUMP:
		show_reg_dump(m);
		break;
	case DEBUG_ID_PRINT_DATA:
		show_print_data(item, m);
		break;
	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int write_reg_value(const char *cmd)
{
	int rc;
	u32 offset, value;

	rc = sscanf(cmd, "%i %i", &offset, &value);
	if (rc != 2) {
		return -EINVAL;
	}

	sci_reg_write(offset, value);

	return 0;
}

static void set_print_data(struct te_debug_item *item, const char *cmd)
{
	struct sci_dev *dev = item->private;
	u32 val;

	val = simple_strtoul(cmd, NULL, 0);

	sci_set_debug_print(dev, (val) ? true : false);
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;

	switch (item->flags) {
	case DEBUG_ID_LOGMASK:
		set_log_mask(str);
		break;
	case DEBUG_ID_REG_WRITE:
		ret = write_reg_value(str);
		break;
	case DEBUG_ID_PRINT_DATA:
		set_print_data(item, str);
		break;
	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("version", &debug_ops, DEBUG_ID_VERSION),
	DBGITM_SIM_W("logmask", &debug_ops, DEBUG_ID_LOGMASK),
	DBGITM_SIM("regdump", &debug_ops, DEBUG_ID_REG_DUMP),
	DBGITM_SIM("regvalue", &debug_ops, DEBUG_ID_REG_WRITE),
	DBGITM_SIM("print_data", &debug_ops, DEBUG_ID_PRINT_DATA),
};

int sci_debug_init(struct sci_dev *dev)
{
	struct sci_debug *d = &dev->debug;
	int ret;

	log_noti("%s", __func__);

	d->dir = te_debug_create_dir(SCI_MODULE, NULL);
	CHECK_ERROR(!d->dir, return -EIO, "err in te_debug_create_dir");

	ret = debug_create_item_files(debug_list, dev, d->dir);
	CHECK_ERROR(ret, goto remove_dir, "err in debug_create_item_files");

	return 0;

remove_dir:
	te_debug_remove_dir(d->dir);

	return ret;
}

void sci_debug_release(struct sci_dev *dev)
{
	te_debug_remove_dir(dev->debug.dir);
}

/** @} */
