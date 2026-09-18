/**
 * @Title      proc file system for  memory profiling
 * @Copyright  Copyright (c) LG Electronics All Rights Reserved
 * @License    Strictly Confidential.
*/

#include <linux/module.h>
#include <linux/tty.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <mali_kbase_mem_profile_procfs.h>

#ifdef CONFIG_DEBUG_FS

/** Show callback for the @c mem_profile procfs file.
 *
 * This function is called to get the contents of the @c mem_profile procfs
 * file. This is a report of current memory usage and distribution in userspace.
 *
 * @param sfile The procfs entry
 * @param data Data associated with the entry
 *
 * @return 0 if it successfully prints data in procfs entry file, non-zero otherwise
 */
static int kbasep_mem_profile_seq_show(struct seq_file *sfile, void *data)
{
	struct kbase_context *kctx = (struct kbase_context *)sfile->private;
	seq_printf(sfile, "%d\n", get_gpu_memory(kctx->tgid));
	return 0;
}

/*
 *  File operations related to procfs entry for mem_profile
 */
static int kbasep_mem_profile_procfs_open(struct inode *in, struct file *file)
{
	return single_open(file, kbasep_mem_profile_seq_show, PDE_DATA(in));
}

static const struct file_operations kbasep_mem_profile_procfs_fops = {
	.open = kbasep_mem_profile_procfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int kbasep_mem_profile_procfs_insert(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	int err = 0;
	char kctx_name[64];

	snprintf(kctx_name, 64, "%d", kctx->tgid);
	proc_create_data(kctx_name, 0644,
			    kbdev->webos_gpu_directory,
			    &kbasep_mem_profile_procfs_fops,
			    (void *)kctx);

	if(kbdev->webos_gpu_directory == NULL)
	{
	    err = -ENOMEM;
	}

	return err;
}

void kbasep_mem_profile_procfs_remove(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	char kctx_name[64];

        snprintf(kctx_name, 64, "%d", kctx->tgid);
	remove_proc_entry(kctx_name, kbdev->webos_gpu_directory);
}

#else /* CONFIG_DEBUG_FS */

int kbasep_mem_profile_procfs_insert(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	return 0;
}

void kbasep_mem_profile_procfs_remove(struct kbase_context *kctx, struct kbase_device *kbdev)
{

}

#endif /* CONFIG_DEBUG_FS */
