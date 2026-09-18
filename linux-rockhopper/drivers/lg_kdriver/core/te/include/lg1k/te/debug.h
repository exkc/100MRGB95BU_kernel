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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-07-09
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_DEBUG_H_
#define	_LG1K_TE_DEBUG_H_

#include <linux/device.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/version.h>

//#define CONFIG_TE_DEBUGFS

enum te_debug_type {
	TE_DEBUG_TYPE_NUM = 0,
	TE_DEBUG_TYPE_STR,
	TE_DEBUG_TYPE_SHOW,
	TE_DEBUG_TYPE_FOPS,
	TE_DEBUG_TYPE_SIMPLE,
};

enum te_debug_flag {
	TE_DEBUG_FLAG_HEX = (0x1 << 0),
};

struct te_debug_dir;
struct te_debug_item;
struct te_debug_item_files;


struct te_debug_simple_ops {
	int (*show)(struct te_debug_item *item, struct seq_file *m);
	int (*write)(struct te_debug_item *item, char *str);
};

struct te_debug_data {
	union {
		const struct te_debug_simple_ops *sops;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
		const struct proc_ops *fops;
#else
		const struct file_operations *fops;
#endif
		int (*show)(struct te_debug_item *item, struct seq_file *m);
		void *value;
	};
	u32 size;
};

struct te_debug_item_info {
	const char *name;
	enum te_debug_type type;
	umode_t mode;
	struct te_debug_data data;
	unsigned long flags;
};

struct te_debug_item {
	const char *name;
	struct te_debug_data data;
	unsigned long flags;
	void *private;
};

#define TE_DEBUG_ITEM(_name, _type, _mode, _value, _size, _flags) \
  {.name = _name, .type = _type, .mode = _mode, \
   .data = {.value = (void*)_value, .size = _size}, \
   .flags = (u32)_flags}

#define DBGITM_NUM(_name, _value) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_NUM, S_IRUSR | S_IWUSR, _value, \
		sizeof(*(_value)), 0)

#define DBGITM_HEX(_name, _value) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_NUM, S_IRUSR | S_IWUSR, _value, \
		sizeof(*(_value)), TE_DEBUG_FLAG_HEX)

#define DBGITM_STR(_name, _value) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_STR, S_IRUSR | S_IWUSR, _value, \
		sizeof(_value) + __must_be_array(_value), 0)

#define DBGITM_SHOW(_name, _show, _flags) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_SHOW, S_IRUSR, _show, 0, _flags)

#define DBGITM_FOPS(_name, _fops, _flags) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_FOPS, S_IRUSR | S_IWUSR, _fops, 0, _flags)

#define DBGITM_SIM(_name, _sops, _flags) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_SIMPLE, S_IRUSR | S_IWUSR, _sops, \
		0, _flags)

#define DBGITM_SIM_R(_name, _sops, _flags) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_SIMPLE, S_IRUSR, _sops, 0, _flags)

#define DBGITM_SIM_W(_name, _sops, _flags) \
  TE_DEBUG_ITEM(_name, TE_DEBUG_TYPE_SIMPLE, S_IWUSR, _sops, 0, _flags)


struct te_debug_dir *te_debug_create_dir(const char *name,
					 struct te_debug_dir *parent);

void te_debug_remove_dir(struct te_debug_dir *dir);

struct te_debug_dir *te_debug_create_symlink(struct te_debug_dir *src,
					     const char *dest);


int te_debug_create_item_files(const struct te_debug_item_info *infos,
			       int count,
			       void *private,
			       struct te_debug_dir *dir,
			       struct te_debug_item_files **files);

#define debug_create_item_files(infos, priv, dir) \
  te_debug_create_item_files(infos, ARRAY_SIZE(infos), priv, dir, NULL)

void te_debug_remove_item_files(struct te_debug_item_files *files);


static inline void *te_debug_get_inode_private(struct inode *inode)
{
#ifdef CONFIG_TE_DEBUGFS
	return inode->i_private;
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	return pde_data(inode);
#else
	return PDE_DATA(inode);
#endif
#endif
}


/* debug user parameters */
struct te_debug_param;

struct te_debug_param *te_debug_param_create(const char *path);
void te_debug_param_destory(struct te_debug_param *param);

const char *te_debug_param_get_str(struct te_debug_param *param,
				   const char *name);
int te_debug_param_get_num(struct te_debug_param *param,
			   const char *name, int *num, unsigned int base);
int te_debug_param_get_hex(struct te_debug_param *param,
			   const char *name, unsigned long *value);
int te_debug_param_get_num_array(struct te_debug_param *param,
				 const char *name, int *arr, int max_count,
				 unsigned int base);
void te_debug_param_display(struct te_debug_param *param);

#endif				/* _LG1K_TE_DEBUG_H_ */

/** @} */
