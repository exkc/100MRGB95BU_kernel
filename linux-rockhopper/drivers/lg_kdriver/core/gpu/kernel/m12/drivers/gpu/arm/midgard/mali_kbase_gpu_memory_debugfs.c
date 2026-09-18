/*
 *
 * (C) COPYRIGHT 2012-2015 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */



#include <mali_kbase_gpu_memory_debugfs.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
#include <asm/gpuinfo.h>
#endif

#ifdef CONFIG_DEBUG_FS

/** Show callback for the @c gpu_memory debugfs file.
 *
 * This function is called to get the contents of the @c gpu_memory debugfs
 * file. This is a report of current gpu memory usage.
 *
 * @param sfile The debugfs entry
 * @param data Data associated with the entry
 *
 * @return 0 if successfully prints data in debugfs entry file
 *         -1 if it encountered an error
 */
static int kbasep_gpu_memory_seq_show(struct seq_file *sfile, void *data)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;

	kbdev_list = kbase_dev_list_get();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbasep_kctx_list_element *element;

		kbdev = list_entry(entry, struct kbase_device, entry);
		/* output the total memory usage and cap for this device */
		seq_printf(sfile, "%-16s  %10u\n",
				kbdev->devname,
				atomic_read(&(kbdev->memdev.used_pages)));
#if defined(LGE_GLOBAL_POOL_CONTROL)
{
		extern int get_freelist_for_global_pool(void);
		seq_printf(sfile, "%-16s  %10d\n", \
				"global-pool", get_freelist_for_global_pool());
}
#endif

#if defined(LGE_PAGE_POOL_MAX) && (LGE_PAGE_POOL_MAX != 0)
{
		extern int get_freelist_for_xreclaimable(void);
		seq_printf(sfile, "%-16s  %10d\n", \
				"xreclaimable", get_freelist_for_xreclaimable());
}
#endif
		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(element, &kbdev->kctx_list, link) {
			struct pid *pid;
			struct task_struct *task;

			pid = find_get_pid(element->kctx->pid);
			task = get_pid_task(pid, PIDTYPE_PID);
			if(!task)
			{
				seq_printf(sfile," Can't find process ID on system");
			}
			else
			{
				/* output the memory usage and cap for each kctx
				* opened on this device */
				seq_printf(sfile, "  %s-0x%p (pid:%6d[%30s]) %10u\n", \
					"kctx",
					element->kctx,
					element->kctx->pid,
					task->comm,
					atomic_read(&(element->kctx->used_pages)));
			}
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_dev_list_put(kbdev_list);
	return 0;
}

static int kbasep_webos_mem_seq_show(struct seq_file *sfile, void *data)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;

	kbdev_list = kbase_dev_list_get();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbasep_kctx_list_element *element;

		kbdev = list_entry(entry, struct kbase_device, entry);
		/* output the total memory usage and cap for this device */
		seq_printf(sfile, "%6s %-28s %-10s\n", \
				   "PID", "ProcessName", "Size(MB)");

		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(element, &kbdev->kctx_list, link) {
			struct pid *pid;
			struct task_struct *task;

			pid = find_get_pid(element->kctx->pid);
			task = get_pid_task(pid, PIDTYPE_PID);
			if(!task)
			{
				seq_printf(sfile," Can't find process ID on system");
			}
			else
			{
				/* output the memory usage and cap for each kctx
				* opened on this device */
				int gpu_memory=0, ump_memory=0;

#ifdef CONFIG_UMP
				ump_memory = ump_debug_mem_for_webos_mem(element->kctx->pid);
#endif /* CONFIG_UMP */
				gpu_memory = (ump_memory + (atomic_read(&(element->kctx->used_pages))*PAGE_SIZE)) / 1024 / 1024;
				if (gpu_memory <= 0)
					gpu_memory = 1; // adjust values(1MB).

				seq_printf(sfile, "%6d %-30s %-10u\n", \
					element->kctx->pid,
					task->comm,
					gpu_memory);
			}
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_dev_list_put(kbdev_list);

	return 0;
}

/*
 *  File operations related to debugfs entry for gpu_memory
 */
static int kbasep_gpu_memory_debugfs_open(struct inode *in, struct file *file)
{
	return single_open(file, kbasep_gpu_memory_seq_show , NULL);
}

static const struct file_operations kbasep_gpu_memory_debugfs_fops = {
	.open = kbasep_gpu_memory_debugfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};


static int kbasep_webos_mem_debugfs_open(struct inode *in, struct file *file)
{
	return single_open(file, kbasep_webos_mem_seq_show , NULL);
}

static const struct file_operations kbasep_webos_mem_debugfs_fops = {
	.open = kbasep_webos_mem_debugfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
static struct gpu_info_driver gpuinfo_driver;

int get_gpu_memory (int client_tgid)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;
	int gpu_memory = 0 ;

	kbdev_list = kbase_dev_list_get();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbasep_kctx_list_element *element;

		kbdev = list_entry(entry, struct kbase_device, entry);

		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(element, &kbdev->kctx_list, link) {
			struct pid *pid;
			struct task_struct *task;

			pid = find_get_pid(element->kctx->pid);
			task = get_pid_task(pid, PIDTYPE_PID);
			/* output the memory usage and cap for each kctx
			* opened on this device */
			if(element->kctx->tgid == client_tgid)
			    gpu_memory += atomic_read(&(element->kctx->used_pages));
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_dev_list_put(kbdev_list);

	return gpu_memory;
}

static int getTotal_for_meminfo (void)
{
	int gpu_mem_total_page = 0;
	unsigned int ump_mem_total_page = 0;
	struct list_head *entry;
	const struct list_head *kbdev_list;

	kbdev_list = kbase_dev_list_get();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;

		kbdev = list_entry(entry, struct kbase_device, entry);
		/* output the total memory usage and cap for this device */
		gpu_mem_total_page = atomic_read(&(kbdev->memdev.used_pages));
	}
	kbase_dev_list_put(kbdev_list);
#ifdef CONFIG_UMP
	if (ump_debug_mem_for_meminfo(&ump_mem_total_page) < 0)
		printk(KERN_ERR "fail to call ump_debug_mem_for_meminfo\n");
#endif /* CONFIG_UMP */
	return gpu_mem_total_page+ump_mem_total_page;
}
static int getCached_for_meminfo (void)
{
	return 0;
}

static int getReclaimable_for_meminfo (void)
{
	return 0;
}

#endif

/*
 *  Initialize debugfs entry for gpu_memory
 */
void kbasep_gpu_memory_debugfs_init(struct kbase_device *kbdev)
{

	kbdev->gpu_memory_dentry = debugfs_create_file("gpu_memory", \
					S_IRUGO, \
					kbdev->mali_debugfs_directory, \
					NULL, \
					&kbasep_gpu_memory_debugfs_fops);
	if (IS_ERR(kbdev->gpu_memory_dentry))
		return;

#ifdef CONFIG_MALI_LGE_KMALLOC_DEBUG
	kbdev->kmalloc_debug_dentry = debugfs_create_file("kmalloc_debug",
							  S_IRUGO,
							  kbdev->mali_debugfs_directory,
							  NULL,
							  &kmalloc_debug_debugfs_fops);
	if (IS_ERR(kbdev->kmalloc_debug_dentry))
		printk(KERN_ERR "fail to create kmalloc_debug debugfs entry\n");
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
	gpuinfo_driver.getTotal = getTotal_for_meminfo;
	gpuinfo_driver.getCached = getCached_for_meminfo;
	gpuinfo_driver.getReclaimable = getReclaimable_for_meminfo;
	if (gpu_info_register(&gpuinfo_driver) < 0)
		printk(KERN_ERR "fail to register gpu_info for meminfo\n");
#endif

	kbdev->webos_mem_dentry = debugfs_create_file("gpu", \
					S_IRUGO, \
					kbdev->webos_mem_directory, \
					NULL, \
					&kbasep_webos_mem_debugfs_fops);
	if (IS_ERR(kbdev->webos_mem_dentry))
		return;

	return;
}

/*
 *  Terminate debugfs entry for gpu_memory
 */
void kbasep_gpu_memory_debugfs_term(struct kbase_device *kbdev)
{
	debugfs_remove(kbdev->gpu_memory_dentry);
	debugfs_remove(kbdev->webos_mem_dentry);
#ifdef CONFIG_MALI_LGE_KMALLOC_DEBUG
	debugfs_remove(kbdev->kmalloc_debug_dentry);
#endif
	debugfs_create_file("gpu_memory", S_IRUGO,
			kbdev->mali_debugfs_directory, NULL,
			&kbasep_gpu_memory_debugfs_fops);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
	if (gpu_info_unregister(&gpuinfo_driver) < 0)
		printk(KERN_ERR "fail to unregister gpu_info for meminfo\n");

#endif
	return;
}

#else
/*
 * Stub functions for when debugfs is disabled
 */
void kbasep_gpu_memory_debugfs_init(struct kbase_device *kbdev)
{
	return;
}

void kbasep_gpu_memory_debugfs_term(struct kbase_device *kbdev)
{
	return;
}
#endif
