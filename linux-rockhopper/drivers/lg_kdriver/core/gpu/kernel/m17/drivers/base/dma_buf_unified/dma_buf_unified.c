/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.
 
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

#include <linux/dma-buf-unified.h>
#include <linux/dma-buf.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
#include <linux/dma-attrs.h>
#include <linux/dma-mapping.h>
#endif

//#define	WORKAROUND_NON_PAGES	1

struct dma_buf_unified_alloc {
	/* the real alloc */
	int nr_pages;
	struct page **pages;

	int type;

	/* the debug usage tracking */
	int nr_attached_devices;
	int nr_device_mappings;
	int nr_cpu_mappings;

	/* failure simulation */
	int fail_attach;
	int fail_map;
	int fail_mmap;

	bool contiguous;
	dma_addr_t contig_dma_addr;
	void *contig_cpu_addr;

#ifdef	WORKAROUND_NON_PAGES
	unsigned long phys_addr;
#endif
	/* to get information about dma_buf memory size of each process */
	int tgid;
	struct list_head list_node;

	unsigned int map_cached;
	struct sg_table *sg;
};

enum dma_buf_type {
	DMA_BUF_ALLOC	= 0,
	DMA_BUF_LMA	= 1,
	DMA_BUF_ION	= 2,
};

struct dma_buf_list {
        struct list_head head;
        struct mutex lock;
};

static struct dma_buf_list db_list;

static struct miscdevice te_device;

int dma_buf_unified_info(int tgid)
{

	struct dma_buf_unified_alloc *alloc;
	int count, ret, total_size=0;

	ret = mutex_lock_interruptible(&db_list.lock);

	if (ret)
	    return ret;

	list_for_each_entry(alloc, &db_list.head, list_node) {

	    if(tgid == alloc->tgid)
		total_size += alloc->nr_pages;
	}

	mutex_unlock(&db_list.lock);

        return total_size;
}

EXPORT_SYMBOL(dma_buf_unified_info);

static int dma_buf_unified_attach(struct dma_buf *buf, struct device *dev, struct dma_buf_attachment *attachment)
{
	struct dma_buf_unified_alloc	*alloc;
	alloc = buf->priv;

	if (alloc->fail_attach)
		return -EFAULT;

	/* dma_buf is externally locked during call */
	alloc->nr_attached_devices++;
	return 0;
}

static void dma_buf_unified_detach(struct dma_buf *buf, struct dma_buf_attachment *attachment)
{
	struct dma_buf_unified_alloc *alloc;
	alloc = buf->priv;
	/* dma_buf is externally locked during call */

	alloc->nr_attached_devices--;
}

static struct sg_table *dma_buf_unified_map(struct dma_buf_attachment *attachment, enum dma_data_direction direction)
{
	struct sg_table *sg;
	struct scatterlist *iter;
	struct dma_buf_unified_alloc	*alloc;
	int i;
	int ret;

	alloc = attachment->dmabuf->priv;

	if (alloc->fail_map)
		return ERR_PTR(-ENOMEM);

#if !(defined(ARCH_HAS_SG_CHAIN) || defined(CONFIG_ARCH_HAS_SG_CHAIN))
	/* if the ARCH can't chain we can't have allocs larger than a single sg can hold */
	if (alloc->nr_pages > SG_MAX_SINGLE_ALLOC)
		return ERR_PTR(-EINVAL);
#endif

	sg = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!sg)
		return ERR_PTR(-ENOMEM);

	/* from here we access the allocation object, so lock the dmabuf pointing to it */
	mutex_lock(&attachment->dmabuf->lock);

	if (alloc->contiguous)
		ret = sg_alloc_table(sg, 1, GFP_KERNEL);
	else
		ret = sg_alloc_table(sg, alloc->nr_pages, GFP_KERNEL);
	if (ret) {
		mutex_unlock(&attachment->dmabuf->lock);
		kfree(sg);
		return ERR_PTR(ret);
	}

	if (alloc->contiguous) {
		sg_dma_len(sg->sgl) = alloc->nr_pages * PAGE_SIZE;
		sg_set_page(sg->sgl, pfn_to_page(PFN_DOWN(alloc->contig_dma_addr)), alloc->nr_pages * PAGE_SIZE, 0);
		sg_dma_address(sg->sgl) = alloc->contig_dma_addr;
	} else {
		for_each_sg(sg->sgl, iter, alloc->nr_pages, i)
			sg_set_page(iter, alloc->pages[i], PAGE_SIZE, 0);
	}

#ifdef	WORKAROUND_NON_PAGES
	if (alloc->type != DMA_BUF_LMA)
	{
		if (!dma_map_sg(attachment->dev, sg->sgl, sg->nents, direction)) {
			mutex_unlock(&attachment->dmabuf->lock);
			sg_free_table(sg);
			kfree(sg);
			return ERR_PTR(-ENOMEM);
		}
	}
	else
	{
		struct scatterlist *s;

		for_each_sg(sg->sgl, s, sg->nents, i)
			s->dma_address = (dma_addr_t)(alloc->phys_addr + PAGE_SIZE*i);
	}
#else
	if (!dma_map_sg(attachment->dev, sg->sgl, sg->nents, direction)) {
		mutex_unlock(&attachment->dmabuf->lock);
		sg_free_table(sg);
		kfree(sg);
		return ERR_PTR(-ENOMEM);
	}
#endif


	alloc->nr_device_mappings++;
	alloc->sg = sg;
	mutex_unlock(&attachment->dmabuf->lock);
	return sg;
}

static void dma_buf_unified_unmap(struct dma_buf_attachment *attachment,
							 struct sg_table *sg, enum dma_data_direction direction)
{
	struct dma_buf_unified_alloc *alloc;

	alloc = attachment->dmabuf->priv;

#ifdef	WORKAROUND_NON_PAGES
	if (alloc->type != DMA_BUF_LMA)
#endif
	dma_unmap_sg(attachment->dev, sg->sgl, sg->nents, direction);
	sg_free_table(sg);
	kfree(sg);

	mutex_lock(&attachment->dmabuf->lock);
	alloc->nr_device_mappings--;
	alloc->sg = NULL;
	mutex_unlock(&attachment->dmabuf->lock);
}

static void dma_buf_unified_release(struct dma_buf *buf)
{
	int i;
	struct dma_buf_unified_alloc *alloc;
	alloc = buf->priv;
	/* no need for locking */

	if (alloc->type == DMA_BUF_ALLOC)
	{
		if (alloc->contiguous) {
			DEFINE_DMA_ATTRS(attrs);

			dma_set_attr(DMA_ATTR_WRITE_COMBINE, &attrs);
			dma_free_attrs(te_device.this_device,
							alloc->nr_pages * PAGE_SIZE,
							alloc->contig_cpu_addr, alloc->contig_dma_addr, &attrs);
		} else {
			for (i = 0; i < alloc->nr_pages; i++)
				__free_page(alloc->pages[i]);
		}
		mutex_lock(&db_list.lock);
		list_del(&alloc->list_node);
		mutex_unlock(&db_list.lock);
	}

	kfree(alloc->pages);
	kfree(alloc);
}

static void dma_buf_unified_mmap_open(struct vm_area_struct *vma)
{
	struct dma_buf *dma_buf;
	struct dma_buf_unified_alloc *alloc;

	dma_buf = vma->vm_private_data;
	alloc = dma_buf->priv;

	mutex_lock(&dma_buf->lock);
	alloc->nr_cpu_mappings++;
	mutex_unlock(&dma_buf->lock);
}

static void dma_buf_unified_mmap_close(struct vm_area_struct *vma)
{
	struct dma_buf *dma_buf;
	struct dma_buf_unified_alloc *alloc;
	dma_buf = vma->vm_private_data;
	alloc = dma_buf->priv;

	BUG_ON(alloc->nr_cpu_mappings <= 0);
	mutex_lock(&dma_buf->lock);
	alloc->nr_cpu_mappings--;
	mutex_unlock(&dma_buf->lock);
}

static int dma_buf_unified_mmap_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct dma_buf_unified_alloc *alloc;
	struct dma_buf *dmabuf;
	struct page *pageptr;

	dmabuf = vma->vm_private_data;
	alloc = dmabuf->priv;

	if (vmf->pgoff > alloc->nr_pages)
		return VM_FAULT_SIGBUS;

	pageptr = alloc->pages[vmf->pgoff];

	BUG_ON(!pageptr);

	get_page(pageptr);
	vmf->page = pageptr;

	return 0;
}

struct vm_operations_struct dma_buf_unified_vm_ops = {
	.open = dma_buf_unified_mmap_open,
	.close = dma_buf_unified_mmap_close,
	.fault = dma_buf_unified_mmap_fault
};

static int dma_buf_unified_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
{
	struct dma_buf_unified_alloc *alloc;
	alloc = dmabuf->priv;

	if (alloc->fail_mmap)
		return -ENOMEM;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 7, 0))
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
#else
	vma->vm_flags |= VM_RESERVED | VM_IO | VM_DONTEXPAND;
#endif
	vma->vm_ops = &dma_buf_unified_vm_ops;
	vma->vm_private_data = dmabuf;
	if(alloc->map_cached == DMA_UNIFIED_UNCACHED)
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

#ifdef	WORKAROUND_NON_PAGES
	if(alloc->type == DMA_BUF_LMA)
	{
		int i, err;
		uint64_t paddr;

		vma->vm_flags |= VM_MIXEDMAP;
		for (i=0; i<alloc->nr_pages; i++)
		{
			paddr = alloc->phys_addr + PAGE_SIZE*i;
			err = vm_insert_mixed(vma, vma->vm_start + (i << PAGE_SHIFT), paddr >> PAGE_SHIFT);
			if (err != 0)
				printk("vm_insert_mixed error %d\n", err);
		}
	}
#endif
	/*  we fault in the pages on access */

	/* call open to do the ref-counting */
	dma_buf_unified_vm_ops.open(vma);

	return 0;
}

static void *dma_buf_unified_kmap_atomic(struct dma_buf *buf, unsigned long page_num)
{
	/* IGNORE */
	return NULL;
}

static void *dma_buf_unified_kmap(struct dma_buf *buf, unsigned long page_num)
{
	struct dma_buf_unified_alloc *alloc;

#ifdef	WORKAROUND_NON_PAGES
	return NULL;
#endif
	alloc = buf->priv;
	if (page_num >= alloc->nr_pages)
		return NULL;

	return kmap(alloc->pages[page_num]);
}
static void dma_buf_unified_kunmap(struct dma_buf *buf,
		unsigned long page_num, void *addr)
{
	struct dma_buf_unified_alloc *alloc;

#ifdef	WORKAROUND_NON_PAGES
	return;
#endif
	alloc = buf->priv;
	if (page_num >= alloc->nr_pages)
		return;

	kunmap(alloc->pages[page_num]);
	return;
}

static struct dma_buf_ops dma_buf_unified_ops = {
	/* real handlers */
	.attach		= dma_buf_unified_attach,
	.detach		= dma_buf_unified_detach,
	.map_dma_buf	= dma_buf_unified_map,
	.unmap_dma_buf	= dma_buf_unified_unmap,
	.release	= dma_buf_unified_release,
	.mmap		= dma_buf_unified_mmap,
	.kmap		= dma_buf_unified_kmap,
	.kunmap		= dma_buf_unified_kunmap,

	/* nop handlers for mandatory functions we ignore */
	.kmap_atomic = dma_buf_unified_kmap_atomic
};

static int do_dma_buf_unified_ioctl_version(struct dma_buf_unified_ioctl_version __user *buf)
{
	struct dma_buf_unified_ioctl_version v;

	if (copy_from_user(&v, buf, sizeof(v)))
		return -EFAULT;

	v.major = DMA_BUF_UNIFIED_VER_MAJOR;
	v.minor = DMA_BUF_UNIFIED_VER_MINOR;

	if (copy_to_user(buf, &v, sizeof(v)))
		return -EFAULT;
	else
		return 0;
}

static int do_dma_buf_unified_ioctl_alloc(struct dma_buf_unified_ioctl_alloc __user *buf, bool contiguous)
{
	struct dma_buf_unified_ioctl_alloc alloc_req;
	struct dma_buf_unified_alloc *alloc;
	struct dma_buf *dma_buf;
	int i = 0;
	int fd;

	if (copy_from_user(&alloc_req, buf, sizeof(alloc_req))) {
		dev_err(te_device.this_device, "%s: couldn't get user data", __func__);
		goto no_input;
	}

	if (!alloc_req.size) {
		dev_err(te_device.this_device, "%s: no size specified", __func__);
		goto invalid_size;
	}

#if !(defined(ARCH_HAS_SG_CHAIN) || defined(CONFIG_ARCH_HAS_SG_CHAIN))
	/* Whilst it is possible to allocate larger buffer, we won't be able to
	 * map it during actual usage (mmap() still succeeds). We fail here so
	 * userspace code can deal with it early than having driver failure
	 * later on. */
	if (alloc_req.size > SG_MAX_SINGLE_ALLOC) {
		dev_err(te_device.this_device, "%s: buffer size of %llu pages exceeded the mapping limit of %lu pages",
				__func__, alloc_req.size, SG_MAX_SINGLE_ALLOC);
		goto invalid_size;
	}
#endif

	alloc = kzalloc(sizeof(struct dma_buf_unified_alloc), GFP_KERNEL);
	if (NULL == alloc) {
		dev_err(te_device.this_device, "%s: couldn't alloc object", __func__);
		goto no_alloc_object;
	}

	alloc->nr_pages = alloc_req.size;
	alloc->contiguous = contiguous;
	alloc->type = DMA_BUF_ALLOC;
	alloc->tgid = current->tgid;
	alloc->map_cached = alloc_req.map_cached;

	alloc->pages = kzalloc(sizeof(struct page *) * alloc->nr_pages, GFP_KERNEL);
	if (!alloc->pages) {
		dev_err(te_device.this_device,
				"%s: couldn't alloc %d page structures", __func__,
				alloc->nr_pages);
		goto free_alloc_object;
	}

	if (contiguous) {
		dma_addr_t dma_aux;

		DEFINE_DMA_ATTRS(attrs);

		dma_set_attr(DMA_ATTR_WRITE_COMBINE, &attrs);
		alloc->contig_cpu_addr = dma_alloc_attrs(te_device.this_device,
				alloc->nr_pages * PAGE_SIZE,
				&alloc->contig_dma_addr,
				GFP_KERNEL | __GFP_ZERO, &attrs);
		if (!alloc->contig_cpu_addr) {
			dev_err(te_device.this_device, "%s: couldn't alloc contiguous buffer %d pages", __func__, alloc->nr_pages);
			goto free_page_struct;
		}
		dma_aux = alloc->contig_dma_addr;
		for (i = 0; i < alloc->nr_pages; i++) {
			alloc->pages[i] = pfn_to_page(PFN_DOWN(dma_aux));
			dma_aux += PAGE_SIZE;
		}
	} else {
		for (i = 0; i < alloc->nr_pages; i++) {
			alloc->pages[i] = alloc_page(GFP_KERNEL | __GFP_ZERO);
			if (NULL == alloc->pages[i]) {
				dev_err(te_device.this_device, "%s: couldn't alloc page", __func__);
				goto no_page;
			}

			{
				void *kaddr;
				kaddr = kmap(alloc->pages[i]);
#ifdef CONFIG_ARM
				__cpuc_flush_dcache_area(kaddr, PAGE_SIZE);
				outer_flush_range( PFN_PHYS(page_to_pfn(alloc->pages[i])), PFN_PHYS(page_to_pfn(alloc->pages[i])) + PAGE_SIZE );
#elif defined(CONFIG_ARM64)
				__dma_map_area(kaddr, PAGE_SIZE, DMA_FROM_DEVICE);
#endif
				kunmap(alloc->pages[i]);

			}
		}
	}

	/* alloc ready, let's export it */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
	{
		struct dma_buf_export_info export_info = {
			.exp_name = "dma_buf_unified",
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 2, 0))
			.owner = THIS_MODULE,
#endif
			.ops = &dma_buf_unified_ops,
			.size = alloc->nr_pages << PAGE_SHIFT,
			.flags = O_CLOEXEC | O_RDWR,
			.priv = alloc,
		};

		dma_buf = dma_buf_export(&export_info);
	}
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0))
	dma_buf = dma_buf_export(alloc, &dma_buf_unified_ops,
			alloc->nr_pages << PAGE_SHIFT, O_CLOEXEC|O_RDWR, NULL);
#else
	dma_buf = dma_buf_export(alloc, &dma_buf_unified_ops,
			alloc->nr_pages << PAGE_SHIFT, O_CLOEXEC|O_RDWR);
#endif
	if (IS_ERR_OR_NULL(dma_buf)) {
		dev_err(te_device.this_device, "%s: couldn't export dma_buf", __func__);
		goto no_export;
	}

	/* get fd for buf */
	fd = dma_buf_fd(dma_buf, O_CLOEXEC);

	if (fd < 0) {
		dev_err(te_device.this_device, "%s: couldn't get fd from dma_buf", __func__);
		dma_buf_put(dma_buf);
		return fd;
	}

	mutex_lock(&db_list.lock);
	list_add(&alloc->list_node, &db_list.head);
	mutex_unlock(&db_list.lock);

	return fd;

no_export:
	/* i still valid */
no_page:
	if (contiguous) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
		DEFINE_DMA_ATTRS(attrs);

		dma_set_attr(DMA_ATTR_WRITE_COMBINE, &attrs);
		dma_free_attrs(te_device.this_device,
						alloc->nr_pages * PAGE_SIZE,
						alloc->contig_cpu_addr, alloc->contig_dma_addr, &attrs);
#else
		dma_free_writecombine(te_device.this_device,
								alloc->nr_pages * PAGE_SIZE,
								alloc->contig_cpu_addr, alloc->contig_dma_addr);
#endif
	} else {
		while (i-- > 0)
			__free_page(alloc->pages[i]);
	}
free_page_struct:
	kfree(alloc->pages);
free_alloc_object:
	kfree(alloc);
no_alloc_object:
invalid_size:
no_input:
	return -EFAULT;
}

/**
* convert external physical memory to dma_buf
*/
static int do_dma_buf_unified_ioctl_import(struct dma_buf_unified_ioctl_import __user *arg)
{
	struct dma_buf_unified_ioctl_import trans;
	struct dma_buf_unified_alloc *import;
	struct dma_buf *dma_buf;
	unsigned int phys_address;
	int fd = -1;
	int i;

	if (copy_from_user(&trans, arg, sizeof(trans)))
	{
		dev_err(te_device.this_device, "%s: couldn't get user data", __func__);
		return -EFAULT;
	}

	import = kzalloc(sizeof(struct dma_buf_unified_alloc), GFP_KERNEL);
	if (NULL == import) {
		dev_err(te_device.this_device, "%s: couldn't alloc object", __func__);
		return -EFAULT;
	}

	import->nr_pages = trans.size;
	import->contiguous = 0;
	import->type = DMA_BUF_LMA;
	import->map_cached = trans.map_cached;

	// TODO : replace to vmalloc
	import->pages = kzalloc(sizeof(struct page *) * import->nr_pages, GFP_KERNEL);
	if (!import->pages) {
		dev_err(te_device.this_device,
				"%s: couldn't alloc %d page structures", __func__,
				import->nr_pages);
		goto free_import_object;
	}

#ifdef	WORKAROUND_NON_PAGES
	import->phys_addr = trans.phys_addr;
#endif
	phys_address = trans.phys_addr;
	for( i=0; i<import->nr_pages; i++)
	{
		struct page *page;
		page = pfn_to_page(PFN_DOWN(phys_address));
		import->pages[i] = page;

		phys_address += (1<<PAGE_SHIFT);
	}

	/* export fd */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
	{
		struct dma_buf_export_info export_info = {
			.exp_name = "dma_buf_unified",
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 2, 0))
			.owner = THIS_MODULE,
#endif
			.ops = &dma_buf_unified_ops,
			.size = import->nr_pages << PAGE_SHIFT,
			.flags = O_CLOEXEC | O_RDWR,
			.priv = import,
		};

		dma_buf = dma_buf_export(&export_info);
	}
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0))
	dma_buf = dma_buf_export(import, &dma_buf_unified_ops,
			import->nr_pages << PAGE_SHIFT, O_CLOEXEC|O_RDWR, NULL);
#else
	dma_buf = dma_buf_export(import, &dma_buf_unified_ops,
			import->nr_pages << PAGE_SHIFT, O_CLOEXEC|O_RDWR);
#endif

	if (IS_ERR_OR_NULL(dma_buf)) {
		dev_err(te_device.this_device, "%s: couldn't export dma_buf", __func__);
		goto no_export_import;
	}

	/* get fd for buf */
	fd = dma_buf_fd(dma_buf, O_CLOEXEC);

	if (fd < 0) {
		dev_err(te_device.this_device, "%s: couldn't get fd from dma_buf", __func__);
		dma_buf_put(dma_buf);
		return fd;
	}

	return fd;

no_export_import:
	kfree(import->pages);
free_import_object:
	kfree(import);

	return -EFAULT;
}

static int do_dma_buf_unified_ioctl_status(struct dma_buf_unified_ioctl_status __user *arg)
{
	struct dma_buf_unified_ioctl_status status;
	struct dma_buf *dmabuf;
	struct dma_buf_unified_alloc *alloc;
	int res = -EINVAL;

	if (copy_from_user(&status, arg, sizeof(status)))
		return -EFAULT;

	dmabuf = dma_buf_get(status.fd);

	if (IS_ERR_OR_NULL(dmabuf))
		return -EINVAL;

	/* verify it's one of ours */
	if (dmabuf->ops != &dma_buf_unified_ops)
		goto err_have_dmabuf;

	/* ours, get the current status */
	alloc = dmabuf->priv;

	/* lock while reading status to take a snapshot */
	mutex_lock(&dmabuf->lock);
	status.attached_devices = alloc->nr_attached_devices;
	status.device_mappings = alloc->nr_device_mappings;
	status.cpu_mappings = alloc->nr_cpu_mappings;
	mutex_unlock(&dmabuf->lock);

	if (copy_to_user(arg, &status, sizeof(status)))
		goto err_have_dmabuf;

	/* All OK */
	res = 0;

err_have_dmabuf:
	dma_buf_put(dmabuf);
	return res;
}

static int do_dma_buf_unified_ioctl_set_failing(struct dma_buf_unified_ioctl_set_failing __user *arg)
{
	struct dma_buf *dmabuf;
	struct dma_buf_unified_ioctl_set_failing f;
	struct dma_buf_unified_alloc *alloc;
	int res = -EINVAL;

	if (copy_from_user(&f, arg, sizeof(f)))
		return -EFAULT;

	dmabuf = dma_buf_get(f.fd);
	if (IS_ERR_OR_NULL(dmabuf))
		return -EINVAL;

	/* verify it's one of ours */
	if (dmabuf->ops != &dma_buf_unified_ops)
		goto err_have_dmabuf;

	/* ours, set the fail modes */
	alloc = dmabuf->priv;
	/* lock to set the fail modes atomically */
	mutex_lock(&dmabuf->lock);
	alloc->fail_attach = f.fail_attach;
	alloc->fail_map    = f.fail_map;
	alloc->fail_mmap   = f.fail_mmap;
	mutex_unlock(&dmabuf->lock);

	/* success */
	res = 0;

err_have_dmabuf:
	dma_buf_put(dmabuf);
	return res;
}

static int do_dma_buf_unified_ioctl_buffer_sync(struct dma_buf_unified_ioctl_buffer_sync __user *arg)
{
	struct dma_buf *dmabuf;
	struct dma_buf_unified_ioctl_buffer_sync sync;
	struct dma_buf_unified_alloc *alloc;
	int res = 0;

	if (copy_from_user(&sync, arg, sizeof(sync)))
		return -EFAULT;

	dmabuf = dma_buf_get(sync.fd);
	if (IS_ERR_OR_NULL(dmabuf))
		return -EINVAL;

	alloc = dmabuf->priv;

	if(alloc->map_cached == DMA_UNIFIED_UNCACHED)
		goto dma_sync_no_req;
	if(alloc->sg == NULL)
		goto dma_sync_no_req;

	if(sync.direction == 0)
		dma_sync_sg_for_device(te_device.this_device, alloc->sg, alloc->nr_pages, DMA_TO_DEVICE);
	else
		dma_sync_sg_for_cpu(te_device.this_device, alloc->sg, alloc->nr_pages, DMA_FROM_DEVICE);

dma_sync_no_req:
	dma_buf_put(dmabuf);
	return res;
}

static int do_dma_buf_unified_ioctl_valid(void __user  * arg)
{
	struct dma_buf_uninfied_ioctl_valid valid;
	struct dma_buf * dmabuf;
	int res;

	if (copy_from_user(&valid, arg, sizeof(valid))) {
		return -EFAULT;
	}

	dmabuf = dma_buf_get(valid.fd);

	if (IS_ERR_OR_NULL(dmabuf)) {
		return -EINVAL;
	}

	valid.size = (unsigned int)dmabuf->size;

	if (dmabuf->ops != &dma_buf_unified_ops) {
		valid.owned = 0;
	} else {
		valid.owned = 1;
	}

	if (copy_to_user(arg, &valid, sizeof(valid))) {
		res =  -EFAULT;
	} else {
		res = 0;
	}

	dma_buf_put(dmabuf);

	return res;
}

static long dma_buf_unified_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case DMA_BUF_UNIFIED_VERSION:
		return do_dma_buf_unified_ioctl_version((struct dma_buf_unified_ioctl_version __user *)arg);
	case DMA_BUF_UNIFIED_ALLOC:
		return do_dma_buf_unified_ioctl_alloc((struct dma_buf_unified_ioctl_alloc __user *)arg, false);
	case DMA_BUF_UNIFIED_ALLOC_CONT:
		return do_dma_buf_unified_ioctl_alloc((struct dma_buf_unified_ioctl_alloc __user *)arg, true);
	case DMA_BUF_UNIFIED_QUERY:
		return do_dma_buf_unified_ioctl_status((struct dma_buf_unified_ioctl_status __user *)arg);
	case DMA_BUF_UNIFIED_SET_FAILING:
		return do_dma_buf_unified_ioctl_set_failing((struct dma_buf_unified_ioctl_set_failing __user *)arg);
	case DMA_BUF_UNIFIED_IMPORT:
		return do_dma_buf_unified_ioctl_import((struct dma_buf_unified_ioctl_import __user *)arg);
	case DMA_BUF_UNIFIED_SYNC:
		return do_dma_buf_unified_ioctl_buffer_sync((struct dma_buf_unified_ioctl_buffer_sync __user *)arg);
	case DMA_BUF_UNIFIED_VALID:
		return do_dma_buf_unified_ioctl_valid((void __user *) arg);
	default:
		return -ENOTTY;
	}
}

static const struct file_operations dma_buf_unified_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = dma_buf_unified_ioctl,
	.compat_ioctl = dma_buf_unified_ioctl,
};

static int __init dma_buf_unified_init(void)
{
	int res;
	te_device.minor = MISC_DYNAMIC_MINOR;
	te_device.name = "dma_buf_unified";
	te_device.fops = &dma_buf_unified_fops;

	res = misc_register(&te_device);
	if (res) {
		printk(KERN_WARNING"Misc device registration failed of 'dma_buf_unified'\n");
		return res;
	}
	te_device.this_device->coherent_dma_mask = DMA_BIT_MASK(32);

	mutex_init(&db_list.lock);
	INIT_LIST_HEAD(&db_list.head);
	LIST_HEAD(db_list);

	dev_info(te_device.this_device, "dma_buf_unified ready\n");
	return 0;

}

static void __exit dma_buf_unified_exit(void)
{
	misc_deregister(&te_device);
}

module_init(dma_buf_unified_init);
module_exit(dma_buf_unified_exit);
MODULE_LICENSE("GPL");

