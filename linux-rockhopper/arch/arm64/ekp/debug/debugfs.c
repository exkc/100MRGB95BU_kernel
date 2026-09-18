// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/debugfs.h>
#include <linux/ekp.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/types.h>

#include "debugfs.h"

static struct dentry *ekp_debugfs_dir;

static int __init ekp_debugfs_init(void)
{
	if (!debugfs_initialized())
		return -ENODEV;

	ekp_debugfs_dir = debugfs_create_dir("ekp", NULL);
	if (IS_ERR_OR_NULL(ekp_debugfs_dir)) {
		pr_err("%s: cannot create debugfs root entry\n", __func__);
		return -ENOMEM;
	}

	if (ekp_enabled()) {
		ekp_debugfs_state_init(ekp_debugfs_dir);
		ekp_debugfs_test_helpers_init(ekp_debugfs_dir);
	}

	ekp_debugfs_sysinfo_init(ekp_debugfs_dir);

	return 0;
}
late_initcall(ekp_debugfs_init)

static void __exit ekp_debugfs_exit(void)
{
	debugfs_remove_recursive(ekp_debugfs_dir);
}
__exitcall(ekp_debugfs_exit);

static int ekp_debugfs_show(struct seq_file *m, void *data)
{
	struct ekp_debugfs_ops *ops = m->private;

	if (!ops->show)
		return -EPERM;

	return ops->show(m);
}

static int ekp_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, ekp_debugfs_show, inode->i_private);
}

static ssize_t ekp_debugfs_write(struct file *file, const char __user *buf,
				 size_t len, loff_t *ppos)
{
	struct seq_file *m = file->private_data;
	struct ekp_debugfs_ops *ops = m->private;
	ssize_t ret;

	if (!ops->store)
		return -EACCES;

	mutex_lock(&m->lock);
	ret = ops->store(buf, len);
	if (ret < 0) {
		mutex_unlock(&m->lock);
		return ret;
	}
	mutex_unlock(&m->lock);

	return len;
}

static const struct file_operations ekp_debugfs_fops = {
	.owner		= THIS_MODULE,
	.open		= ekp_debugfs_open,
	.write		= ekp_debugfs_write,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

void __init ekp_debugfs_create_files(struct ekp_debugfs_attr *attrs,
				     int count, struct dentry *parent)
{
	int i;

	if (IS_ERR_OR_NULL(parent))
		return;

	for (i = 0; i < count; ++i) {
		umode_t mode = 0;

		if (attrs[i].ops->show != NULL)
			mode |= S_IRUSR;

		if (attrs[i].ops->store != NULL)
			mode |= S_IWUSR;

		debugfs_create_file(attrs[i].name, mode, parent,
				    (void *)attrs[i].ops, &ekp_debugfs_fops);
	}
}
