/*
 *
 * (C) COPYRIGHT 2011-2014 ARM Limited. All rights reserved.
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





#include <linux/ump.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0)
#include <drivers/staging/android/ion/ion.h>
#else
#include <linux/ion.h>
#endif
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/kallsyms.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0)
#define LGSIC_ION_CLIENT_NAME "lg1k_ion_client_create"
#else
#define LGSIC_ION_CLIENT_NAME "lg115x_ion_client_create"
#endif

typedef void * (*lgsic_ion_client_create)(unsigned int, const char *);

static int s_ump_ion_registered = 0;

struct ion_wrapping_info
{
	struct ion_client *   ion_client;
	struct ion_handle *   ion_handle;
	int                   num_phys_blocks;
	struct scatterlist *  sglist;
};


static int import_ion_client_create(void** const custom_session_data)
{
	struct ion_client ** ion_client;
	lgsic_ion_client_create func;

	ion_client = (struct ion_client**)custom_session_data;

	func = (lgsic_ion_client_create)kallsyms_lookup_name(LGSIC_ION_CLIENT_NAME);

	if (func != NULL)
		*ion_client = (struct ion_client *)func(0, "ump");
	else
		return PTR_RET(NULL);

	return PTR_RET(*ion_client);
}


static void import_ion_client_destroy(void* custom_session_data)
{
	struct ion_client * ion_client;

	ion_client = (struct ion_client*)custom_session_data;
	BUG_ON(!ion_client);

	ion_client_destroy(ion_client);
}


static void import_ion_release_callback(const ump_dd_handle handle, void * info)
{
	struct ion_wrapping_info * ion_info;

	BUG_ON(!info);

	(void)handle;
	ion_info = (struct ion_wrapping_info*)info;

	ion_free(ion_info->ion_client, ion_info->ion_handle);
	kfree(ion_info);
	module_put(THIS_MODULE);
}

static ump_dd_handle import_ion_import(void * custom_session_data, void * pfd, ump_alloc_flags flags)
{
	int fd;
	ump_dd_handle ump_handle;
	struct scatterlist * iter;
	struct sg_table * sg_table;
	int num_dma_blocks;
	ump_dd_physical_block_64 * phys_blocks;
	unsigned int i;
	struct ion_wrapping_info * ion_info;

	BUG_ON(!custom_session_data);
	BUG_ON(!pfd);

	ion_info = kzalloc(sizeof(*ion_info), GFP_KERNEL);
	if (NULL == ion_info)
	{
		return UMP_DD_INVALID_MEMORY_HANDLE;
	}

	ion_info->ion_client = (struct ion_client*)custom_session_data;

	if (get_user(fd, (int*)pfd))
	{
		goto out;
	}

	ion_info->ion_handle = ion_import_dma_buf(ion_info->ion_client, fd);

	if (IS_ERR_OR_NULL(ion_info->ion_handle))
	{
		goto out;
	}

	sg_table = ion_sg_table(ion_info->ion_client, ion_info->ion_handle);
	ion_info->sglist = sg_table->sgl;

	if (IS_ERR_OR_NULL(ion_info->sglist))
	{
		goto ion_dma_map_failed;
	}

	num_dma_blocks = sg_table->nents;

	phys_blocks = vmalloc(num_dma_blocks * sizeof(*phys_blocks));
	if (NULL == phys_blocks)
	{
		goto vmalloc_failed;
	}

	for_each_sg(sg_table->sgl, iter, num_dma_blocks, i)	{
		phys_blocks[i].addr = sg_phys(iter);
		phys_blocks[i].size = sg_dma_len(iter);
		pr_debug("%s %d (sg:%d):sg_dma_len(%d) / sg_phys(0x%llx) \n", __func__, __LINE__, i, sg_dma_len(iter), (unsigned long long)sg_phys(iter));
	}

	ump_handle = ump_dd_create_from_phys_blocks_64(phys_blocks,
						num_dma_blocks,
						flags,
						NULL,
						import_ion_release_callback,
						ion_info
						);

	vfree(phys_blocks);

	if (ump_handle != UMP_DD_INVALID_MEMORY_HANDLE)
	{
		/*
		 * As we have a final release callback installed
		 * we must keep the module locked until
		 * the callback has been triggered
		 * */
		__module_get(THIS_MODULE);
		return ump_handle;
	}

	/* failed*/
vmalloc_failed:
ion_dma_map_failed:
	ion_free(ion_info->ion_client, ion_info->ion_handle);
out:
	kfree(ion_info);
	return UMP_DD_INVALID_MEMORY_HANDLE;
}

struct ump_import_handler import_handler_ion =
{
	.linux_module =  THIS_MODULE,
	.session_begin = import_ion_client_create,
	.session_end =   import_ion_client_destroy,
	.import =        import_ion_import
};

static int __init import_ion_initialize_module(void)
{
	/* register with UMP */
	if ( 0 == kallsyms_lookup_name(LGSIC_ION_CLIENT_NAME)) {
		printk("fail: %s(), not found %s\n", __func__, LGSIC_ION_CLIENT_NAME);
		return -EEXIST;
	}

	s_ump_ion_registered = 1;

	return ump_import_module_register(UMP_EXTERNAL_MEM_TYPE_ION,
					&import_handler_ion
					);
}

static void __exit import_ion_cleanup_module(void)
{
	/* unregister import handler */
	if (s_ump_ion_registered)
		ump_import_module_unregister(UMP_EXTERNAL_MEM_TYPE_ION);
}

/* Setup init and exit functions for this module */
module_init(import_ion_initialize_module);
module_exit(import_ion_cleanup_module);

/* And some module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ARM Ltd.");
MODULE_VERSION("1.0");
