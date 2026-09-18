/*
 *
 * (C) COPYRIGHT LGE. All rights reserved.
 *
 TODO: Head comment ...
 *
 */

#include <linux/ump.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/list.h>
#include <linux/sched.h>


typedef struct lgfb_import_data_s {
	struct list_head list;
	unsigned int pid;
	ump_dd_handle handle;
	ump_lgfb_memory_handle data;
} lgfb_import_data_t;

static struct dentry *lgfb_debugfs_dir;
static struct dentry *lgfb_info_dentry;

static DEFINE_MUTEX(lgfb_list_mutex);

static LIST_HEAD(s_import_info_list);

static void add_info_list(ump_dd_handle handle, ump_lgfb_memory_handle data)
{
	lgfb_import_data_t * list_data;

	mutex_lock(&lgfb_list_mutex);

	list_data = kmalloc(sizeof(lgfb_import_data_t), GFP_KERNEL);

	list_data->handle = handle;
	list_data->data = data;
	list_data->pid = task_pid_nr(current);

	list_add_tail(&list_data->list, &s_import_info_list);

	mutex_unlock(&lgfb_list_mutex);
}

static void remove_info_list(ump_dd_handle handle)
{
	lgfb_import_data_t * list_data;
	struct list_head * list;

	if (list_empty(&s_import_info_list))
		return;

	mutex_lock(&lgfb_list_mutex);

	list_for_each(list, &s_import_info_list)
	{
		list_data = list_entry(list, lgfb_import_data_t, list);

		if (list_data->handle == handle)
		{
			list_del(&list_data->list);
			kfree(list_data);
			break;
		}
	}

	mutex_unlock(&lgfb_list_mutex);
}

static int prinout_info_list(struct seq_file *sfile)
{
	int i;
	lgfb_import_data_t * list_data;
	struct list_head * list;
	uint64_t total = 0;

	if (list_empty(&s_import_info_list))
		return 0;

	mutex_lock(&lgfb_list_mutex);

	list_for_each(list, &s_import_info_list)
	{
		list_data = list_entry(list, lgfb_import_data_t, list);
		seq_printf(sfile, "ump_handle-0x%p (pid:%d) \n",
				list_data->handle,
				list_data->pid);

		for (i = 0; i < list_data->data.number ; i++) {
			seq_printf(sfile, "\taddress:0x%llx  size:%lld\n",
					list_data->data.infos[i].addr,
					list_data->data.infos[i].size);
			total += list_data->data.infos[i].size;
		}
	}

	seq_printf(sfile, "\n@lgfb_import: %10llu\n", total);

	mutex_unlock(&lgfb_list_mutex);

	return 0;
}

static int lgfb_debug_seq_show(struct seq_file *sfile, void *data)
{
	ssize_t ret = 0;

	ret = prinout_info_list(sfile);

	return ret;
}


static int lgfb_debugfs_open(struct inode *in, struct file *file)
{
	return single_open(file, lgfb_debug_seq_show , NULL);
}

static const struct file_operations lgfb_memory_debugfs_fops = {
	.open = lgfb_debugfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static void lgfb_debugfs_init(void)
{
	lgfb_debugfs_dir = debugfs_create_dir("lgfb_import", NULL);
	lgfb_info_dentry = debugfs_create_file("status",
					S_IRUGO,
					lgfb_debugfs_dir,
					NULL,
					&lgfb_memory_debugfs_fops);
}

static void lgfb_debugfs_term(void)
{
	debugfs_remove(lgfb_info_dentry);
	debugfs_remove(lgfb_debugfs_dir);
}

static void import_lgfb_release_callback(const ump_dd_handle handle, void * info)
{
	remove_info_list(handle);
}

static int s_ump_lgfb_registered = 0;

static int import_lgfb_client_create(void** const custom_session_data)
{
	int ** dummy = (int **)custom_session_data;

	*dummy = &s_ump_lgfb_registered;

	return *dummy;
}

static void import_lgfb_client_destroy(void* custom_session_data)
{
	return;
}

static ump_dd_handle import_lgfb_import(void * custom_session_data, void * pinfo, ump_alloc_flags flags)
{
	ump_dd_handle ump_handle;
	ump_dd_physical_block_64 phys_block[UMP_LGFB_MAX_BUFFER_NUM];
	ump_lgfb_memory_handle lgfb_info;
	int i;

	if (copy_from_user(&lgfb_info, pinfo, sizeof(lgfb_info)))
		goto error;

	if (lgfb_info.number > UMP_LGFB_MAX_BUFFER_NUM)
		goto error;

	for(i = 0 ;i < lgfb_info.number; i++)
	{
		phys_block[i].addr = lgfb_info.infos[i].addr;
		phys_block[i].size = lgfb_info.infos[i].size;
		/*printk("%s: a:0x%x s:0x%x\n", __func__, (unsigned long)lgfb_info.infos[i].addr, (unsigned long)lgfb_info.infos[i].size);*/
	}

	ump_handle = ump_dd_create_from_phys_blocks_64(&phys_block,
						lgfb_info.number,
						flags,
						NULL,
						import_lgfb_release_callback,
						NULL
						);

	if (ump_handle != UMP_DD_INVALID_MEMORY_HANDLE)
	{
		add_info_list(ump_handle, lgfb_info);
	}

	return ump_handle;

error:
	return UMP_DD_INVALID_MEMORY_HANDLE;
}

struct ump_import_handler import_handler_lgfb =
{
	.linux_module =  THIS_MODULE,
	.session_begin = import_lgfb_client_create,
	.session_end =   import_lgfb_client_destroy,
	.import =        import_lgfb_import
};

static int __init import_lgfb_initialize_module(void)
{
	lgfb_debugfs_init();

	return ump_import_module_register(UMP_EXTERNAL_MEM_TYPE_LGFB,
					&import_handler_lgfb
					);
}

static void __exit import_lgfb_cleanup_module(void)
{
	lgfb_debugfs_term();

	ump_import_module_unregister(UMP_EXTERNAL_MEM_TYPE_LGFB);
}

module_init(import_lgfb_initialize_module);
module_exit(import_lgfb_cleanup_module);

MODULE_LICENSE("GPL");
