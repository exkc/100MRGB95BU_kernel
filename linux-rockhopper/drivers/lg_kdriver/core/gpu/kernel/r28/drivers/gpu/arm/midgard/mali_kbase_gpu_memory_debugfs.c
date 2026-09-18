/*
 *
 * (C) COPYRIGHT 2012-2017, 2019 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 */

#include <mali_kbase.h>
#include <device/mali_kbase_device.h>

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
int get_gpu_total_memory (void)
{
       struct list_head *entry;
       const struct list_head *kbdev_list;
       int gpu_memory = 0;

       kbdev_list = kbase_device_get_list();
       list_for_each(entry, kbdev_list) {
               struct kbase_device *kbdev = NULL;
	       struct kbase_context *kctx_element;

               kbdev = list_entry(entry, struct kbase_device, entry);

               mutex_lock(&kbdev->kctx_list_lock);
               list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
			/* output the memory usage and cap for each kctx
			* opened on this device */
			gpu_memory += atomic_read(&(kctx_element->used_pages));
               }
               mutex_unlock(&kbdev->kctx_list_lock);
       }
       kbase_device_put_list(kbdev_list);

       return gpu_memory;
}

int get_gpu_cached_memory (void)
{
	return 0;
}

int get_gpu_pool_memory (void)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;
	int pool_memory = 0;

	kbdev_list = kbase_device_get_list();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbase_context *kctx_element;
		int gid=0;

		kbdev = list_entry(entry, struct kbase_device, entry);
		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
			for (gid = 0; gid < MEMORY_GROUP_MANAGER_NR_GROUPS; ++gid) {
		                pool_memory += kbase_mem_pool_size(&(kctx_element->mem_pools.small[gid]));
		                pool_memory += kbase_mem_pool_size(&(kctx_element->mem_pools.large[gid]));
		        }
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_device_put_list(kbdev_list);

	return (pool_memory);
}

int get_gpu_memory (int client_tgid)
{
       struct list_head *entry;
       const struct list_head *kbdev_list;
       int gpu_memory = 0 ;

       kbdev_list = kbase_device_get_list();
       list_for_each(entry, kbdev_list) {
               struct kbase_device *kbdev = NULL;
	       struct kbase_context *kctx_element;

               kbdev = list_entry(entry, struct kbase_device, entry);

               mutex_lock(&kbdev->kctx_list_lock);
               list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
                       struct pid *pid;
                       struct task_struct *task;

                       pid = find_get_pid(kctx_element->pid);
                       task = get_pid_task(pid, PIDTYPE_PID);
                       /* output the memory usage and cap for each kctx
                       * opened on this device */
                       if(kctx_element->tgid == client_tgid)
                           gpu_memory += atomic_read(&(kctx_element->used_pages));
               }
               mutex_unlock(&kbdev->kctx_list_lock);
       }
       kbase_device_put_list(kbdev_list);

       return gpu_memory;
}

static int kbasep_gpu_memory_seq_show(struct seq_file *sfile, void *data)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;

	kbdev_list = kbase_device_get_list();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbase_context *kctx;

		kbdev = list_entry(entry, struct kbase_device, entry);
		/* output the total memory usage and cap for this device */
		seq_printf(sfile, "%-16s  %10u\n",
				kbdev->devname,
				atomic_read(&(kbdev->memdev.used_pages)));
		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(kctx, &kbdev->kctx_list, kctx_list_link) {
			/* output the memory usage and cap for each kctx
			* opened on this device */
			seq_printf(sfile, "  %s-0x%p %10u\n",
				"kctx",
				kctx,
				atomic_read(&(kctx->used_pages)));
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_device_put_list(kbdev_list);
	return 0;
}

/*
 *  File operations related to debugfs entry for gpu_memory
 */
static int kbasep_gpu_memory_debugfs_open(struct inode *in, struct file *file)
{
	return single_open(file, kbasep_gpu_memory_seq_show, NULL);
}

static const struct file_operations kbasep_gpu_memory_debugfs_fops = {
	.owner = THIS_MODULE,
	.open = kbasep_gpu_memory_debugfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

/*
 *  Initialize debugfs entry for gpu_memory
 */
void kbasep_gpu_memory_debugfs_init(struct kbase_device *kbdev)
{
	debugfs_create_file("gpu_memory", S_IRUGO,
			kbdev->mali_debugfs_directory, NULL,
			&kbasep_gpu_memory_debugfs_fops);
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
#endif
