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

#include <linux/debugfs.h>
#include <linux/proc_fs.h>

#include "te_impl.h"

#if 0
#define debug(fmt, args...)	log_noti(fmt, ##args)
#else
#define debug(fmt, args...)	do{}while(0)
#endif

#ifdef CONFIG_TE_DEBUGFS
typedef struct dentry dentry_t;
#else
typedef struct proc_dir_entry dentry_t;
#endif

struct te_debug_dir {
	dentry_t *dent;
	struct te_debug_dir *parent;
	struct te_debug_dir *link;	/* not null if it is symbolic link */
	struct list_head list;	/* list of child if it has parent */
	struct list_head child;
	struct list_head files;
	char name[0];
};

struct te_debug_node {
	struct te_debug_item item;
	dentry_t *dent;
};

struct te_debug_item_files {
	struct list_head list;	// node of struct te_debug_dir.files
	int count;
	struct te_debug_node node[0];
};

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

static int debug_open(struct inode *inode, struct file *file)
{
	file->private_data = te_debug_get_inode_private(inode);

	return 0;
}

static int debug_show(struct seq_file *m, void *data)
{
	struct te_debug_item *item = m->private;

	return item->data.show(item, m);
}

static int debug_seq_open(struct inode *inode, struct file *file)
{
	struct te_debug_item *item = te_debug_get_inode_private(inode);

	return single_open(file, debug_show, item);
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops seq_fops = {
	.proc_open = debug_seq_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static const struct file_operations seq_fops = {
	.open = debug_seq_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
static ssize_t debug_str_read(struct file *file, char __user *buf,
			      size_t len, loff_t *ppos)
{
	struct te_debug_item *item = file->private_data;
	ssize_t ret;
	char *str;
	size_t avail = strlen(item->data.value) + 2;	/* '\n' + '\0' */

	if (*ppos != 0)
		return 0;

	str = vmalloc(avail);
	if (!str)
		return -ENOMEM;

	snprintf(str, avail, "%s\n", (char *)item->data.value);

	ret = simple_read_from_buffer(buf, len, ppos, str, avail);
	vfree(str);

	return ret;
}

static ssize_t debug_str_write(struct file *file, const char __user *buf,
			       size_t len, loff_t *ppos)
{
	struct te_debug_item *item = file->private_data;
	char *data, *str;

	data = vmalloc(len + 1);
	if (!data)
		return -ENOMEM;

	if (copy_from_user(data, buf, len)) {
		vfree(data);
		return -EFAULT;
	}

	data[len] = '\0';

	str = strim(data);
	snprintf(item->data.value, item->data.size, "%s", str);

	vfree(data);

	return len;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops str_fops = {
	.proc_open = debug_open,
	.proc_read = debug_str_read,
	.proc_write = debug_str_write,
};
#else
static const struct file_operations str_fops = {
	.open = debug_open,
	.read = debug_str_read,
	.write = debug_str_write,
};
#endif
static int debug_simple_show(struct seq_file *m, void *data)
{
	struct te_debug_item *item = m->private;

	return item->data.sops->show(item, m);
}

static int debug_simple_open(struct inode *inode, struct file *file)
{
	struct te_debug_item *item = te_debug_get_inode_private(inode);

	return single_open(file, debug_simple_show, item);
}

static ssize_t debug_simple_write(struct file *file, const char __user *buf,
				  size_t len, loff_t *ppos)
{
	struct seq_file *m = file->private_data;
	struct te_debug_item *item = m->private;
	int ret;
	char *data;

	if (!item->data.sops->write)
		return -EPERM;

// TODO: consider len & ppos

	data = vmalloc(len + 1);
	if (!data)
		return -ENOMEM;

	if (copy_from_user(data, buf, len))
		ret = -EFAULT;
	else {
		char *str;
		data[len] = 0;	/* NULL termination */
		str = strim(data);
		ret = item->data.sops->write(item, str);
	}
	vfree(data);

	return ret < 0 ? ret : len;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops simple_fops = {
	.proc_open = debug_simple_open,
	.proc_read = seq_read,
	.proc_write = debug_simple_write,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static const struct file_operations simple_fops = {
	.open = debug_simple_open,
	.read = seq_read,
	.write = debug_simple_write,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
static ssize_t debug_value_read(struct file *file, char __user *buf,
				size_t len, loff_t *ppos)
{
	struct te_debug_item *item = file->private_data;
	u64 val;
	char str[32];
	size_t avail;

	if (*ppos != 0)
		return 0;

	switch (item->data.size) {
	case 1:
		val = *(u8 *)(item->data.value);
		break;
	case 2:
		val = *(u16 *)(item->data.value);
		break;
	case 4:
		val = *(u32 *)(item->data.value);
		break;
	case 8:
		val = *(u64 *)(item->data.value);
		break;
	default:
		val = 0;
		break;
	}

	if (item->flags & TE_DEBUG_FLAG_HEX) {
		avail = snprintf(str, sizeof(str), "0x%llx\n", val);
	} else {
		avail = snprintf(str, sizeof(str), "%llu\n", val);
	}

	return simple_read_from_buffer(buf, len, ppos, str, avail);
}

static ssize_t debug_value_write(struct file *file, const char __user *buf,
				 size_t len, loff_t *ppos)
{
	struct te_debug_item *item = file->private_data;
	char *data;
	u64 val;

	data = vmalloc(len + 1);
	if (!data)
		return -ENOMEM;

	if (copy_from_user(data, buf, len)) {
		vfree(data);
		return -EFAULT;
	}
	data[len] = '\0';

	val = simple_strtoll(data, NULL, 0);
	switch (item->data.size) {
	case 1:
		*(u8 *)(item->data.value) = val;
		break;
	case 2:
		*(u16 *)(item->data.value) = val;
		break;
	case 4:
		*(u32 *)(item->data.value) = val;
		break;
	case 8:
		*(u64 *)(item->data.value) = val;
		break;
	default:
		break;
	}

	vfree(data);

	return len;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
static const struct proc_ops value_fops = {
	.proc_open = debug_open,
	.proc_read = debug_value_read,
	.proc_write = debug_value_write,
};
#else
static const struct file_operations value_fops = {
	.open = debug_open,
	.read = debug_value_read,
	.write = debug_value_write,
};
#endif

#ifdef CONFIG_TE_DEBUGFS
static dentry_t *create_debug_dir(const char *name, struct dentry *parent)
{
	dentry_t *dent;

	dent = debugfs_create_dir(name, parent);

	return IS_ERR_OR_NULL(dent) ? NULL : dent;
}

static dentry_t *create_debug_file(const struct te_debug_item *item,
				   umode_t mode, dentry_t *parent,
				   const struct file_operations *fops)
{
	dentry_t *dent;

	dent = debugfs_create_file(item->name, mode, parent, (void *)item,
				   fops);

	return IS_ERR_OR_NULL(dent) ? NULL : dent;
}

static dentry_t *create_symlink(const char *name, dentry_t *parent,
				const char *dest)
{
	struct dentry *dent;

	dent = debugfs_create_symlink(name, parent, dest);

	return IS_ERR_OR_NULL(dent) ? NULL : dent;
}

static void remove_debug_entry(dentry_t *dent)
{
	debugfs_remove(dent);
}
#else		/* PROC FS */
static dentry_t *create_debug_dir(const char *name, dentry_t *parent)
{
	dentry_t *dent;

	dent = proc_mkdir(name, parent);

	return dent;
}

static dentry_t *create_debug_file(const struct te_debug_item *item,
				   umode_t mode, dentry_t *parent,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
				   const struct proc_ops *fops)
#else
				   const struct file_operations *fops)
#endif
{
	dentry_t *dent;

	dent = proc_create_data(item->name, mode, parent, fops, (void *)item);

	return dent;
}

static dentry_t *create_symlink(const char *name, dentry_t *parent,
				const char *dest)
{
	dentry_t *dent;

	dent = proc_symlink(name, parent, dest);

	return dent;
}

static void remove_debug_entry(dentry_t *dent)
{
	proc_remove(dent);
}
#endif

int te_debug_create_item_files(const struct te_debug_item_info *infos,
			       int count,
			       void *private,
			       struct te_debug_dir *dir,
			       struct te_debug_item_files **files)
{
	int i;
	struct te_debug_item *item;
	struct te_debug_node *node;
	struct te_debug_item_files *ifs;
	const struct te_debug_item_info *info;
	dentry_t *dent;

	if (!dir)
		return -EINVAL;

	ifs = vmalloc(sizeof(*ifs) + sizeof(struct te_debug_node) * count);
	if (!ifs)
		return -ENOMEM;

	if (dir->link)
		dir = dir->link;

	ifs->count = count;

	for (i = 0; i < count; i++) {
		info = &infos[i];
		node = &ifs->node[i];

		node->item.name = info->name;
		node->item.data = info->data;
		node->item.flags = info->flags;
		node->item.private = private;

		item = &node->item;

		switch (info->type) {
		case TE_DEBUG_TYPE_NUM:
			dent = create_debug_file(item, info->mode,
						 dir->dent, &value_fops);
			break;

		case TE_DEBUG_TYPE_STR:
			dent = create_debug_file(item, info->mode,
						 dir->dent, &str_fops);
			break;

		case TE_DEBUG_TYPE_SHOW:
			dent = create_debug_file(item, info->mode,
						 dir->dent, &seq_fops);
			break;

		case TE_DEBUG_TYPE_FOPS:
			dent = create_debug_file(item, info->mode,
						 dir->dent, info->data.fops);
			break;

		case TE_DEBUG_TYPE_SIMPLE:
			dent = create_debug_file(item, info->mode,
						 dir->dent, &simple_fops);
			break;

		default:
			dent = NULL;
			break;
		}

		if (!dent) {
			count = i;
			for (i = 0; i < count; i++) {
				node = &ifs->node[i];
				remove_debug_entry(node->dent);
			}
			vfree(ifs);

			return -EINVAL;
		}

		node->dent = dent;
	}

	list_add_tail(&ifs->list, &dir->files);

	if (files)
		*files = ifs;

	return 0;
}

void te_debug_remove_item_files(struct te_debug_item_files *files)
{
	int i;
	struct te_debug_node *node;

	list_del(&files->list);

	for (i = 0; i < files->count; i++) {
		node = &files->node[i];
		remove_debug_entry(node->dent);
	}
	vfree(files);
}

struct te_debug_dir *te_debug_create_dir(const char *name,
					 struct te_debug_dir *parent)
{
	struct te_debug_dir *dir;

	dir = kmalloc(sizeof(*dir) + strlen(name) + 1, GFP_KERNEL);
	if (!dir)
		return NULL;

	if (parent && parent->link)
		parent = parent->link;

	strncpy(dir->name, name, strlen(name) + 1);
	dir->parent = parent;
	dir->link = NULL;
	INIT_LIST_HEAD(&dir->child);
	INIT_LIST_HEAD(&dir->files);

	dir->dent = create_debug_dir(name, parent ? parent->dent : NULL);
	if (!dir->dent) {
		kfree(dir);
		return NULL;
	}

	if (parent)
		list_add_tail(&dir->list, &parent->child);

	return dir;
}

struct te_debug_dir *te_debug_create_symlink(struct te_debug_dir *src,
					     const char *dest)
{
	struct te_debug_dir *dir;
	dentry_t *parent;

	if (!src || src->link)
		return NULL;

	dir = kmalloc(sizeof(*dir) + strlen(dest) + 1, GFP_KERNEL);
	if (!dir)
		return NULL;

	strncpy(dir->name, dest, strlen(dest) + 1);
	dir->parent = src->parent;
	dir->link = src;
	INIT_LIST_HEAD(&dir->child);
	INIT_LIST_HEAD(&dir->files);

	parent = (src->parent) ? src->parent->dent : NULL;

	dir->dent = create_symlink(src->name, parent, dest);
	if (!dir->dent) {
		kfree(dir);
		return NULL;
	}
	list_add_tail(&dir->list, &src->child);

	return dir;
}

void te_debug_remove_dir(struct te_debug_dir *dir)
{
	if (!dir->link) {
		struct te_debug_dir *child, *child2;
		struct te_debug_item_files *files, *files2;

		list_for_each_entry_safe(child, child2, &dir->child, list) {
			te_debug_remove_dir(child);
		}

		list_for_each_entry_safe(files, files2, &dir->files, list) {
			te_debug_remove_item_files(files);
		}
	}

	if (dir->parent)
		list_del(&dir->list);

	remove_debug_entry(dir->dent);

	kfree(dir);
}

/* user parameters */
struct te_debug_param {
	struct list_head items;
	void *buf;
};

struct param_item {
	char *name;
	char *value;
	struct list_head list;
};

static char *param_trim_line(char *s)
{
	char *s1 = s;

	/* Remove comments start with '#' or ';' */
	while (*s1 && *s1 != '#' && *s1 != ';') {
		s1++;
	}
	*s1 = 0;

	return strim(s);
}

static int parse_one_line_param(struct te_debug_param *p, char *line)
{
	const char *delim = ":";
	struct param_item *item;
	char *name, *value;

	name = strsep(&line, delim);
	if (!line)
		return -EINVAL;

	name = strim(name);
	value = strim(line);

	if (!*name)
		return -EINVAL;

	item = kmalloc(sizeof(struct param_item), GFP_KERNEL);
	if (!item)
		return -ENOMEM;

	item->name = name;
	item->value = value;

	list_add_tail(&item->list, &p->items);

	return 0;
}

static void destory_param_items(struct te_debug_param *p)
{
	struct param_item *item, *temp;

	list_for_each_entry_safe(item, temp, &p->items, list) {
		kfree(item);
	}
}

/**
 * te_debug_param_create - create debug params from the path
 *
 * It makes @struct te_debug_param after parsing input file.
 * The input file format as follows:
 * [name] : [value]
 * comment is starting with '#' or ';'
 * ---------------------------
 * # key configuration example
 * key size: 16
 * cas type: 16
 * oddkey: 0x00, 0x12, 0x34 # array list
 * ----------------------------
 *
 * Return: pointer of @struct te_debug_param if succeed or ERR_PTR(...)
 */
struct te_debug_param *te_debug_param_create(const char *path)
{
	int ret, n;
	char *s = NULL;
	struct te_debug_param *p;
	const char *delim = "\r\n";
	char *line, *tok;

	ret = te_read_file_from_path(path, (void**)&s, 16 * 1024);
	if (ret < 0)
		return ERR_PTR(ret);

	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p) {
		ret = -ENOMEM;
		goto err_malloc;
	}

	INIT_LIST_HEAD(&p->items);
	p->buf = s;

	n = 0;
	tok = s;
	while ((line = strsep(&tok, delim))) {
		if (!*line)
			continue;
		n++;
		line = param_trim_line(line);
		if (*line == '\0')
			continue;

		debug("line='%s'", line);

		ret = parse_one_line_param(p, line);
		if (ret) {
			log_warning("parse error - %d:'%s'", n, line);
			goto err_parse;
		}
	}

	return p;

err_parse:
	destory_param_items(p);
	kfree(p);
err_malloc:
	vfree(s);

	return ERR_PTR(ret);
}

void te_debug_param_destory(struct te_debug_param *param)
{
	destory_param_items(param);
	vfree(param->buf);
	kfree(param);
}

void te_debug_param_display(struct te_debug_param *param)
{
	struct param_item *item;

	list_for_each_entry(item, &param->items, list) {
		log_noti("%s='%s'\n", item->name, item->value);
	}
}

static struct param_item *get_param_item(struct te_debug_param *p,
					 const char *name)
{
	struct param_item *item;

	list_for_each_entry(item, &p->items, list) {
		if (!strcasecmp(name, item->name))
			return item;
	}

	return NULL;
}

const char *te_debug_param_get_str(struct te_debug_param *param,
				   const char *name)
{
	struct param_item *item = get_param_item(param, name);

	if (!item)
		return NULL;

	return item->value;
}

/**
 * te_debug_param_get_num - get number value
 *
 * Return: 0 on success, -EINVAL if @name is not exist in the item list
 */
int te_debug_param_get_num(struct te_debug_param *param,
			   const char *name, int *num, unsigned int base)
{
	struct param_item *item = get_param_item(param, name);

	if (!item)
		return -EINVAL;

	*num = (int)simple_strtol(item->value, NULL, base);

	return 0;
}

int te_debug_param_get_hex(struct te_debug_param *param,
			   const char *name, unsigned long *value)
{
	struct param_item *item = get_param_item(param, name);

	if (!item)
		return -EINVAL;

	*value = simple_strtoul(item->value, NULL, 16);

	return 0;
}

/*
 * te_debug_param_get_num_array - get number array values
 *  array value are separated by delimeters " \t[],"
 *
 * @arr: allocated array
 *
 * Return: number of array count if succeed,
 * -EINVAL if @name item is not eixt
 * -ENOMEM if no memory to parse the items
 */
int te_debug_param_get_num_array(struct te_debug_param *param,
				 const char *name, int *arr, int max_count,
				 unsigned int base)
{
	char *s, *v, *tok;
	int count;
	const char *delim = " \t[],";
	struct param_item *item = get_param_item(param, name);

	if (!item)
		return -EINVAL;

	s = kmalloc(strlen(item->value) + 1, GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	strcpy(s, item->value);

	count = 0;
	tok = s;
	while ((v = strsep(&tok, delim))) {
		if (!*v)
			continue;

		if (count >= max_count) {
			log_warning("more items but over max(%d)\n", max_count);
			break;
		}
		arr[count] = (int)simple_strtol(v, NULL, base);
		debug("arr[%d]=%d('%s')\n", count, arr[count], v);
		count++;
	}
	kfree(s);

	return count;
}
