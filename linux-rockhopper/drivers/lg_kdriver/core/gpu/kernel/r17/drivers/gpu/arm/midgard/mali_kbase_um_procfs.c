/**
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2019 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

#include <mali_kbase_um_procfs.h>
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/dma-buf-unified.h>
#ifdef CONFIG_DEBUG_FS


/** Show callback for the @c um procfs file.
 *
 * This function is called to get the contents of the @c um procfs
 * file. This is a report of current memory usage and distribution in userspace.
 *
 * @param sfile The procfs entry
 * @param data Data associated with the entry
 *
 * @return 0 if it successfully prints data in procfs entry file, non-zero otherwise
 */
static int kbasep_um_seq_show(struct seq_file *sfile, void *data)
{
	struct kbase_context *kctx = (struct kbase_context *)sfile->private;
	seq_printf(sfile, "%d\n", dma_buf_unified_info(kctx->tgid));

	return 0;
}

/*
 *  File operations related to procfs entry for um
 */
static int kbasep_um_procfs_open(struct inode *in, struct file *file)
{
	return single_open(file, kbasep_um_seq_show, PDE_DATA(in));
}

static const struct file_operations kbasep_um_procfs_fops = {
	.open = kbasep_um_procfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int kbasep_um_procfs_insert(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	int err = 0;
	char kctx_name[64];

	snprintf(kctx_name, 64, "%d", kctx->tgid);

	proc_create_data(kctx_name, 0644,
                            kbdev->webos_um_directory,
                            &kbasep_um_procfs_fops,
                            (void *)kctx);

        if(kbdev->webos_um_directory == NULL)
        {
            err = -ENOMEM;
        }

	return err;
}

void kbasep_um_procfs_remove(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	char kctx_name[64];

        snprintf(kctx_name, 64, "%d", kctx->tgid);
	remove_proc_entry(kctx_name, kbdev->webos_um_directory);
}

#else /* CONFIG_DEBUG_FS */

int kbasep_um_procfs_insert(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	return 0;
}

void kbasep_um_procfs_remove(struct kbase_context *kctx, struct kbase_device *kbdev)
{

}

#endif /* CONFIG_DEBUG_FS */
