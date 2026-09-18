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
 *  TE(Transport Engine) Driver for linux dvb
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2019-06-05
 *  @note	Additional information.
 */

#ifndef _LXDVB_PROC_H_
#define _LXDVB_PROC_H_

#include <linux/device.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>

struct lxdvb_proc_dir;
struct lxdvb_proc_files;
struct lxdvb_proc_item;

enum lxdvb_proc_type {
	LXDVB_PROC_TYPE_OPS = 0,
	LXDVB_PROC_TYPE_SHOW,
};

struct lxdvb_proc_ops {
	int (*show)(struct lxdvb_proc_item *item, struct seq_file *m);
	int (*write)(struct lxdvb_proc_item *item, char *buf, size_t len);
};

struct lxdvb_proc_item {
	const char *name;
	unsigned long flags;
	void *private;
};

struct lxdvb_proc_item_info {
	const char *name;
	enum lxdvb_proc_type type;
	umode_t mode;
	union {
		const struct lxdvb_proc_ops *ops;
		int (*show)(struct lxdvb_proc_item *item, struct seq_file *m);
	};
	unsigned long flags;
};

#define __LXDVB_PROC_ITEM(_name, _mode, _ops, _flags) \
  {.name = _name, .type = LXDVB_PROC_TYPE_OPS, \
   .mode = _mode, .ops = _ops, .flags = _flags }

#define LXDVB_PROC_ITEM(_name, _ops, _flags) \
  __LXDVB_PROC_ITEM(_name, S_IRUSR | S_IWUSR, _ops, _flags)

#define LXDVB_PROC_ITEM_R(_name, _ops, _flags) \
  __LXDVB_PROC_ITEM(_name, S_IRUSR, _ops, _flags)

#define LXDVB_PROC_ITEM_W(_name, _ops, _flags) \
  __LXDVB_PROC_ITEM(_name, S_IWUSR, _ops, _flags)

#define LXDVB_PROC_ITEM_SHOW(_name, _show, _flags) \
  {.name = _name, .type = LXDVB_PROC_TYPE_SHOW, \
   .mode = S_IWUSR, .show = _show, .flags = _flags }


struct lxdvb_proc_dir *lxdvb_proc_create_dir(const char *name,
					     struct lxdvb_proc_dir *parent);
void lxdvb_proc_remove_dir(struct lxdvb_proc_dir *dir);

int __lxdvb_proc_create_files(const struct lxdvb_proc_item_info *infos,
			      int count, void *private,
			      struct lxdvb_proc_dir *dir,
			      struct lxdvb_proc_files **files);

#define lxdvb_proc_create_files(_infos, _priv, _dir) \
  __lxdvb_proc_create_files(_infos, ARRAY_SIZE(_infos), _priv, _dir, NULL)

void lxdvb_proc_remove_files(struct lxdvb_proc_files *files);


#endif
