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

#include "lxdvb_impl.h"
#include "lxdvb_proc.h"

#include "proc_util.h"


struct lxdvb_proc_dir {
	struct proc_dir_entry *entry;
	struct lxdvb_proc_dir *parent;

	/* List entry in struct lxdvb_proc_dir::child */
	struct list_head child_entry;

	struct list_head child;
	struct list_head files;
	char name[0];
};

struct lxdvb_proc_node {
	struct lxdvb_proc_item item;
	struct lxdvb_proc_ops ops;
	struct proc_dir_entry *entry;
};

struct lxdvb_proc_files {
	/* List entry in struct lxdvb_proc_dir::files */
	struct list_head list;
	int count;
	struct lxdvb_proc_node node[0];
};


static int proc_show(struct seq_file *m, void *data)
{
	struct lxdvb_proc_node *node = m->private;

	if (!node->ops.show)
		return -EPERM;

	return node->ops.show(&node->item, m);
}

static int proc_open(struct inode *inode, struct file *file)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	struct lxdvb_proc_node *node = pde_data(inode);
#else
	struct lxdvb_proc_node *node = PDE_DATA(inode);
#endif
	return single_open(file, proc_show, node);
}

static ssize_t proc_write(struct file *file, const char __user *buf,
			  size_t len, loff_t *ppos)
{
	struct seq_file *m = file->private_data;
	struct lxdvb_proc_node *node = m->private;
	int ret;
	char *data;

	if (!node->ops.write)
		return -EPERM;

	// TODO: consider len & ppos

	data = vmalloc(len + 1);
	if (!data)
		return -ENOMEM;

	if (copy_from_user(data, buf, len))
		ret = -EFAULT;
	else {
		data[len] = 0;	/* NULL termination */
		ret = node->ops.write(&node->item, data, len);
	}
	vfree(data);

	return ret < 0 ? ret : len;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops fops = {
	.proc_open = proc_open,
	.proc_read = seq_read,
	.proc_write = proc_write,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static const struct file_operations fops = {
	.open = proc_open,
	.read = seq_read,
	.write = proc_write,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

int __lxdvb_proc_create_files(const struct lxdvb_proc_item_info *infos,
			      int count, void *private,
			      struct lxdvb_proc_dir *dir,
			      struct lxdvb_proc_files **files)
{
	int i, j;
	struct lxdvb_proc_item *item;
	struct lxdvb_proc_node *node;
	struct lxdvb_proc_files *f;
	const struct lxdvb_proc_item_info *info;

	if (!dir)
		return -EINVAL;

	f = vmalloc(sizeof(*f) + sizeof(struct lxdvb_proc_node) * count);
	if (!f)
		return -ENOMEM;

	f->count = count;

	for (i = 0; i < count; i++) {
		info = &infos[i];
		node = &f->node[i];
		item = &node->item;

		item->name = info->name;
		item->flags = info->flags;
		item->private = private;
		if (info->type == LXDVB_PROC_TYPE_SHOW) {
			node->ops.show = info->show;
		} else {
			node->ops = *info->ops;
		}

		node->entry = proc_create_data(item->name, info->mode,
					       dir->entry, &fops, node);
		if (!node->entry) {
			for (j = 0; j < i; j++) {
				node = &f->node[j];
				proc_remove(node->entry);
			}
			vfree(f);
			return -EIO;
		}
	}

	list_add_tail(&f->list, &dir->files);

	if (files)
		*files = f;

	return 0;
}

void lxdvb_proc_remove_files(struct lxdvb_proc_files *files)
{
	int i;
	struct lxdvb_proc_node *node;

	list_del(&files->list);

	for (i = 0; i < files->count; i++) {
		node = &files->node[i];
		proc_remove(node->entry);
	}
	vfree(files);
}

struct lxdvb_proc_dir *lxdvb_proc_create_dir(const char *name,
					     struct lxdvb_proc_dir *parent)
{
	struct lxdvb_proc_dir *dir;
	struct proc_dir_entry *dentry;

	dir = kmalloc(sizeof(*dir) + strlen(name) + 1, GFP_KERNEL);
	if (!dir)
		return NULL;

	strncpy(dir->name, name, strlen(name) + 1);
	dir->parent = parent;
	INIT_LIST_HEAD(&dir->child);
	INIT_LIST_HEAD(&dir->files);

	if (parent)
		dentry = parent->entry;
	else
		dentry = OS_PROC_GetLinuxTvEntry();

	dir->entry = proc_mkdir(name, dentry);
	if (!dir->entry) {
		kfree(dir);
		return NULL;
	}

	if (parent)
		list_add_tail(&dir->child_entry, &parent->child);

	return dir;
}

void lxdvb_proc_remove_dir(struct lxdvb_proc_dir *dir)
{
	struct lxdvb_proc_dir *child, *child2;
	struct lxdvb_proc_files *files, *files2;

	list_for_each_entry_safe(child, child2, &dir->child, child_entry) {
		lxdvb_proc_remove_dir(child);
	}

	list_for_each_entry_safe(files, files2, &dir->files, list) {
		lxdvb_proc_remove_files(files);
	}

	if (dir->parent)
		list_del(&dir->child_entry);

	proc_remove(dir->entry);

	kfree(dir);
}

int lxdvb_proc_init(struct lxdvb_device *dev)
{

	return 0;
}

/** @} */
