// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/ekp.h>

#include "private.h"
#include "version.h"

unsigned int fw_ver __ro_after_init;
unsigned int launcher_ver __ro_after_init;

static int enabled_proc_show(struct seq_file *m, void *v)
{
	unsigned int enabled = 0;

	if (!ekp_enabled())
		goto out;

	if (IS_ENABLED(CONFIG_EKP_FORCE_ENABLE))
		enabled = 1;
	else
		enabled = 2;

out:
	seq_printf(m, "%u\n", enabled);
	return 0;
}

static int enabled_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, enabled_proc_show, NULL);
}

static const struct proc_ops enabled_proc_ops = {
	.proc_open	= enabled_proc_open,
	.proc_read	= seq_read,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
};

static int version_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "EKP Firmware : v%u.%u.%u",
		   ekp_ver_major(fw_ver),
		   ekp_ver_minor(fw_ver),
		   ekp_ver_revision(fw_ver));

	if ((fw_ver & (~0xFF)) != EKP_VERSION) {
		seq_printf(m, " (must be v%u.%u.x)",
			   EKP_VER_MAJOR, EKP_VER_MINOR);
	}

	seq_printf(m, "\n");

	return 0;
}

static int version_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, version_proc_show, NULL);
}

static const struct proc_ops version_proc_ops = {
	.proc_open	= version_proc_open,
	.proc_read	= seq_read,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
};

static int __init ekp_proc_init(void)
{
	struct proc_dir_entry *procfs;

	procfs = proc_mkdir("ekp", NULL);
	if (!procfs)
		return -ENOMEM;

	if (!proc_create("enabled", S_IRUSR, procfs, &enabled_proc_ops))
		return -ENOMEM;

	if (!proc_create("version", S_IRUSR, procfs, &version_proc_ops))
		return -ENOMEM;

	return 0;
}
device_initcall(ekp_proc_init);
