/*
 * vb2_gen_memop.c - memory allocator for videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 * Modifier: Harish Chandra Singh <harish.singh@lge.com>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#include <linux/io.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>
#include <linux/refcount.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6 ,10, 0))
#include <linux/iosys-map.h>
#endif
#include <media/videobuf2-v4l2.h>
#include <media/v4l2-device.h>
#include "os_util.h"
#include "v4l2_lg_dev_configs.h"
#include "vb2_gen_memop.h"
#include "de_def.h"

extern char *capture_mem_str[5];
extern int instance_svp_info;

static void vb2_gen_put(void *buf_priv);
static unsigned int __allocFrmBuffer(int plane, unsigned int size,char **o_mem_pool);
static int vb2_gen_map_dmabuf(void *mem_priv);
void *vb2_gen_dmabuf_ops_kmap(struct dma_buf *dbuf, unsigned long pgnum);

/*
 * Note: Assuming RGB is always single plane
 * plane = 0 and allocation fails, move on to allocate using the othe buffer
 *
 * currently use plane no to determine the RGB or YUV format
 */
static unsigned int __allocFrmBuffer(int plane, unsigned int size,char **o_mem_pool)
{
	unsigned int paddr = 0;
    unsigned int pool_offset = 0;

	/* Invalid plane no */
	if ((plane != 0) && (plane != 1)) {
		return 0;
	}

    pool_offset = (instance_svp_info) ? 3 : 0;

    paddr = (UINT32)hma_alloc(capture_mem_str[plane + pool_offset], (int)size, PAGE_SIZE);
    *o_mem_pool = capture_mem_str[plane + pool_offset];

	if (paddr == 0) {
		if (plane == 0) {
			paddr = (UINT32)hma_alloc(capture_mem_str[2], (int)size, PAGE_SIZE);
			*o_mem_pool = capture_mem_str[2];
			DE_NOTI("Mem allocation on C-Plane for RGB\n");
		}
	}

	if (!paddr)
		DE_ERROR("%s: buffer allocation failed (0x%08X)\n", __func__, (UINT32)paddr);

	return paddr;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
static void *vb2_gps_alloc(struct vb2_buffer *vb, struct device *dev, unsigned long size)
#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void *vb2_gps_alloc(struct device *dev, unsigned long attr, unsigned long size,
                   enum dma_data_direction dma_dir, gfp_t gfp_flags)
#else
static void *vb2_gps_alloc(struct device *dev, unsigned long size,
			       enum dma_data_direction dma_dir, gfp_t gfp_flags)
#endif
#endif
{
	struct vb2_gen_buf *buf;
	unsigned long aligned_size = 0;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
	buf = kzalloc(sizeof(struct vb2_gen_buf), GFP_KERNEL | vb->vb2_queue->gfp_flags);
#else
	buf = kzalloc(sizeof(struct vb2_gen_buf), GFP_KERNEL | gfp_flags);
#endif
	if (!buf)
		return NULL;

	aligned_size = PAGE_ALIGN(size);

	/*Harish: NTBD --> Memory bus load sharing [as of now same bank is used always */
	buf->phyAddr = __allocFrmBuffer(0, aligned_size, &buf->mem_pool);
	if (buf->phyAddr == 0){
		kfree(buf);
		return NULL;
	}
	else {
		buf->vaddr = vmap_phys(buf->phyAddr,size);
		if(buf->vaddr == NULL){
			hma_free(buf->mem_pool,buf->phyAddr);
			kfree(buf);
			return NULL;
		}
	}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
	buf->dma_dir = vb->vb2_queue->dma_dir;
#else
	buf->dma_dir = dma_dir;
#endif
	buf->handler.refcount = &buf->refcount;
	buf->handler.put = vb2_gen_put;
	buf->handler.arg = buf;
	buf->size = size;
	refcount_set(&buf->refcount, 1);

	//DE_NOTI("%s :: [virtual Addr] %p [Phy Addr] 0x%08lx",__func__,(unsigned long)buf->vaddr,buf->phyAddr);
	
	return buf;
}


static void vb2_gen_put(void *buf_priv)
{
	struct vb2_gen_buf *buf = buf_priv;

	if (refcount_dec_and_test(&buf->refcount)) {
		if((buf->vaddr != NULL) && (buf->vaddr != (void *)FAKE_ADDRESS)){
//			DE_NOTI("%s :: [virtual Addr]%p",__func__,(unsigned long)buf->vaddr);
			if(buf->phyAddr)
				hma_free(buf->mem_pool,buf->phyAddr);
			vunmap(buf->vaddr);
		}
		kfree(buf);
	}
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
static void *vb2_vt_alloc(struct vb2_buffer *vb, struct device *dev, unsigned long size)
#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void *vb2_vt_alloc(struct device *dev, unsigned long attr, unsigned long size,
                   enum dma_data_direction dma_dir, gfp_t gfp_flags)
#else
static void *vb2_vt_alloc(struct device *dev, unsigned long size,
			       enum dma_data_direction dma_dir, gfp_t gfp_flags)
#endif
#endif
{
	struct vb2_gen_buf *buf;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
	buf = kzalloc(sizeof(struct vb2_gen_buf), GFP_KERNEL | vb->vb2_queue->gfp_flags);
#else
	buf = kzalloc(sizeof(struct vb2_gen_buf), GFP_KERNEL | gfp_flags);
#endif
	if (!buf)
		return NULL;

	buf->vaddr = (void *)FAKE_ADDRESS;
	buf->phyAddr = 0;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
	buf->dma_dir = vb->vb2_queue->dma_dir;
#else
	buf->dma_dir = dma_dir;
#endif
	buf->handler.refcount = &buf->refcount;
	buf->handler.put = vb2_gen_put;
	buf->handler.arg = buf;
	buf->size = size;
	refcount_set(&buf->refcount, 1);
	//DE_NOTI("%s :: [virtual Addr] %p [Phy Addr] %ld",__func__,(unsigned long)buf->vaddr,buf->phyAddr);
	return buf;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
static void *vb2_gen_get_userptr(struct vb2_buffer *vb, struct device *dev, unsigned long vaddr,
				     unsigned long size)
#else
static void *vb2_gen_get_userptr(struct device *dev, unsigned long vaddr,
				     unsigned long size,
				     enum dma_data_direction dma_dir)
#endif
{
	struct vb2_gen_buf *buf;
	struct frame_vector *vec;
	int n_pages, offset, i;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return NULL;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
	buf->dma_dir = vb->vb2_queue->dma_dir;
#else
	buf->dma_dir = dma_dir;
#endif
	offset = vaddr & ~PAGE_MASK;
	buf->size = size;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
	vec = vb2_create_framevec(vaddr, size, buf->dma_dir == DMA_FROM_DEVICE);
#else
	vec = vb2_create_framevec(vaddr, size);
#endif

#else
	vec = vb2_create_framevec(vaddr, size, dma_dir == DMA_FROM_DEVICE);
#endif
	if (IS_ERR(vec))
		goto fail_pfnvec_create;
	buf->vec = vec;
	n_pages = frame_vector_count(vec);
	if (frame_vector_to_pages(vec) < 0) {
		unsigned long *nums = frame_vector_pfns(vec);

		/*
		 * We cannot get page pointers for these pfns. Check memory is
		 * physically contiguous and use direct mapping.
		 */
		for (i = 1; i < n_pages; i++)
			if (nums[i-1] + 1 != nums[i])
				goto fail_map;
		buf->vaddr = (__force void *)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
				ioremap(nums[0] << PAGE_SHIFT, size);
#else
				ioremap_nocache(nums[0] << PAGE_SHIFT, size);
#endif
	} else {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
		buf->vaddr = vm_map_ram(frame_vector_pages(vec), n_pages, -1);
#else
		buf->vaddr = vm_map_ram(frame_vector_pages(vec), n_pages, -1,
					PAGE_KERNEL);
#endif
	}

	if (!buf->vaddr)
		goto fail_map;
	buf->vaddr += offset;
	return buf;

fail_map:
	vb2_destroy_framevec(vec);
fail_pfnvec_create:
	kfree(buf);

	return NULL;
}

static void vb2_gen_put_userptr(void *buf_priv)
{
	struct vb2_gen_buf *buf = buf_priv;
	unsigned long vaddr = (unsigned long)buf->vaddr & PAGE_MASK;
	unsigned int i;
	struct page **pages;
	unsigned int n_pages;

	if (!buf->vec->is_pfns) {
		n_pages = frame_vector_count(buf->vec);
		pages = frame_vector_pages(buf->vec);
		if (vaddr)
			vm_unmap_ram((void *)vaddr, n_pages);
		if (buf->dma_dir == DMA_FROM_DEVICE)
			for (i = 0; i < n_pages; i++)
				set_page_dirty_lock(pages[i]);
	} else {
		iounmap((__force void __iomem *)buf->vaddr);
	}
	vb2_destroy_framevec(buf->vec);
	kfree(buf);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
static void *vb2_gen_vaddr(struct vb2_buffer *vb, void *buf_priv)
#else
static void *vb2_gen_vaddr(void *buf_priv)
#endif
{
	struct vb2_gen_buf *buf = buf_priv;

	if (buf->vaddr == (void *)FAKE_ADDRESS) {
		pr_err("Address of an unallocated plane requested "
		       "or cannot map user pointer\n");
		return NULL;
	}

	return buf->vaddr;
}

static unsigned int vb2_gen_num_users(void *buf_priv)
{
	struct vb2_gen_buf *buf = buf_priv;
	return refcount_read(&buf->refcount);
}

static int vb2_gen_mmap(void *buf_priv, struct vm_area_struct *vma)
{
	struct vb2_gen_buf *buf = buf_priv;
	int ret = 0;

	if (!buf) {
		DE_NOTI("No memory to map\n");
		return -EINVAL;
	}
#if 0
	DE_NOTI("%s: Mapping address 0x%x Size:: %d StartAddress: 0x%x ENDAddr:: 0x%x Physical Address:: 0x%x\n", __func__,buf->vaddr,buf->size,vma->vm_start,\
		vma->vm_end,vmalloc_to_pfn((void *)buf->vaddr));
	#endif

	if((vma->vm_end - vma->vm_start) > buf->size){
		DE_NOTI("Memory size not supported");
		return -ENXIO;
	}
	if (remap_pfn_range(vma,vma->vm_start,vmalloc_to_pfn((void *)buf->vaddr),(vma->vm_end - vma->vm_start),vma->vm_page_prot)){
		DE_NOTI("remap page range failed\n");
		return -ENXIO;
	}

	/*
	 * Make sure that vm_areas for 2 buffers won't be merged together
	 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
	vm_flags_set(vma,  VM_DONTEXPAND);
#else
	vma->vm_flags		|= VM_DONTEXPAND;
#endif
	/*
	 * Use common vm_area operations to track buffer refcount.
	 */
	vma->vm_private_data	= &buf->handler;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->open(vma);

	return ret;
}

#ifdef CONFIG_HAS_DMA
/*********************************************/
/*         DMABUF ops for exporters          */
/*********************************************/

struct vb2_gen_attachment {
	struct sg_table sgt;
	enum dma_data_direction dma_dir;
};

static int vb2_gen_dmabuf_ops_attach(struct dma_buf *dbuf,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	struct device *dev,
#endif
	struct dma_buf_attachment *dbuf_attach)
{
	struct vb2_gen_attachment *attach;
	struct vb2_gen_buf *buf = dbuf->priv;
	int num_pages = PAGE_ALIGN(buf->size) / PAGE_SIZE;
	struct sg_table *sgt;
	//struct scatterlist *sg;
	//void *vaddr = buf->vaddr;
	//int i;
	int ret;

	attach = kzalloc(sizeof(*attach), GFP_KERNEL);
	if (!attach)
		return -ENOMEM;

	sgt = &attach->sgt;
	ret = sg_alloc_table(sgt, 1 /* num_pages */, GFP_KERNEL);
	if (ret) {
		kfree(attach);
		return ret;
	}
#if 1
	sg_dma_len(sgt->sgl) = num_pages * PAGE_SIZE;
	sg_dma_address(sgt->sgl) = buf->phyAddr;
#else
	for_each_sg(sgt->sgl, sg, sgt->nents, i) {
		struct page *page = vmalloc_to_page(vaddr);

		if (!page) {
			sg_free_table(sgt);
			kfree(attach);
			return -ENOMEM;
		}
		sg_set_page(sg, page, PAGE_SIZE, 0);
		vaddr += PAGE_SIZE;
	}
#endif

	attach->dma_dir = DMA_NONE;
	dbuf_attach->priv = attach;
	return 0;
}

static void vb2_gen_dmabuf_ops_detach(struct dma_buf *dbuf,
	struct dma_buf_attachment *db_attach)
{
	struct vb2_gen_attachment *attach = db_attach->priv;
	struct sg_table *sgt;

	sgt = &attach->sgt;
#if 0

	/* release the scatterlist cache */
	if (attach->dma_dir != DMA_NONE)
		dma_unmap_sg(db_attach->dev, sgt->sgl, sgt->orig_nents,
			attach->dma_dir);
#endif
	sg_free_table(sgt);
	kfree(attach);
	db_attach->priv = NULL;
}

static struct sg_table *vb2_gen_dmabuf_ops_map(
	struct dma_buf_attachment *db_attach, enum dma_data_direction dma_dir)
{
	struct vb2_gen_attachment *attach = db_attach->priv;
	/* stealing dmabuf mutex to serialize map/unmap operations */
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,1,0)
	struct mutex *lock = &db_attach->dmabuf->lock;
#endif
	struct sg_table *sgt;

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,1,0)
	mutex_lock(lock);
#endif
	sgt = &attach->sgt;
	/* return previously mapped sg table */
	if (attach->dma_dir == dma_dir) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,1,0)
		mutex_unlock(lock);
#endif
		return sgt;
	}

	/* release any previous cache */
	if (attach->dma_dir != DMA_NONE) {
#if 0
		dma_unmap_sg(db_attach->dev, sgt->sgl, sgt->orig_nents,
			attach->dma_dir);
#endif
		attach->dma_dir = DMA_NONE;
	}

#if 0
	/* mapping to the client with new direction */
	sgt->nents = dma_map_sg(db_attach->dev, sgt->sgl, sgt->orig_nents,
				dma_dir);
	if (!sgt->nents) {
		pr_err("failed to map scatterlist\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,1,0)
		mutex_unlock(lock);
#endif
		return ERR_PTR(-EIO);
	}
#endif

	attach->dma_dir = dma_dir;

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,1,0)
	mutex_unlock(lock);
#endif
	return sgt;
}

static void vb2_gen_dmabuf_ops_unmap(struct dma_buf_attachment *db_attach,
	struct sg_table *sgt, enum dma_data_direction dma_dir)
{
	/* nothing to be done here */
}

static void vb2_gen_dmabuf_ops_release(struct dma_buf *dbuf)
{
	/* drop reference obtained in vb2_gen_get_dmabuf */
	vb2_gen_put(dbuf->priv);
}

void *vb2_gen_dmabuf_ops_kmap(struct dma_buf *dbuf, unsigned long pgnum)
{
	struct vb2_gen_buf *buf = dbuf->priv;

	return buf->vaddr + pgnum * PAGE_SIZE;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6 ,10, 0))
static int vb2_gen_dmabuf_ops_vmap(struct dma_buf *dbuf, struct iosys_map *map)
#else
static void *vb2_gen_dmabuf_ops_vmap(struct dma_buf *dbuf)
#endif
{
	struct vb2_gen_buf *buf = dbuf->priv;

	return buf->vaddr ? 1 : 0;
}

static int vb2_gen_dmabuf_ops_mmap(struct dma_buf *dbuf,
	struct vm_area_struct *vma)
{
	return vb2_gen_mmap(dbuf->priv, vma);
}

static struct dma_buf_ops vb2_gen_dmabuf_ops = {
	.attach = vb2_gen_dmabuf_ops_attach,
	.detach = vb2_gen_dmabuf_ops_detach,
	.map_dma_buf = vb2_gen_dmabuf_ops_map,
	.unmap_dma_buf = vb2_gen_dmabuf_ops_unmap,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5 ,9, 0))
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.map = vb2_gen_dmabuf_ops_kmap,
#else
	.kmap = vb2_gen_dmabuf_ops_kmap,
	.kmap_atomic = vb2_gen_dmabuf_ops_kmap,
#endif
#endif
	.vmap = vb2_gen_dmabuf_ops_vmap,
	.mmap = vb2_gen_dmabuf_ops_mmap,
	.release = vb2_gen_dmabuf_ops_release,
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
static struct dma_buf *vb2_gen_get_dmabuf(struct vb2_buffer *vb, void *buf_priv, unsigned long flags)
#else
static struct dma_buf *vb2_gen_get_dmabuf(void *buf_priv, unsigned long flags)
#endif
{
	struct vb2_gen_buf *buf = buf_priv;
	struct dma_buf *dbuf;
	char *svp_str = "secured";
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_gen_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	if (WARN_ON(!buf->vaddr))
		return NULL;

	dbuf = dma_buf_export(&exp_info);
	if (IS_ERR(dbuf))
		return NULL;

	/* dmabuf keeps reference to vb2 buffer */
	refcount_inc(&buf->refcount);

	if(instance_svp_info) {
		exp_info.exp_name = svp_str;
		dbuf->exp_name = svp_str;
	}
	DE_NOTI("gps exp_info.exp_name[%s] svp[%d]", exp_info.exp_name, instance_svp_info);
	DE_NOTI("gps dbuf->exp_name[%s]", dbuf->exp_name);

	return dbuf;
}
#endif /* CONFIG_HAS_DMA */


/*********************************************/
/*       callbacks for DMABUF buffers        */
/*********************************************/

static int vb2_gen_map_dmabuf(void *mem_priv)
{
	struct vb2_gen_buf *buf = mem_priv;

#if 1
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6 ,10, 0))
	return dma_buf_vmap(buf->dbuf, NULL);
#else
	return dma_buf_vmap(buf->dbuf);
#endif

	return buf->vaddr ? 0 : -EFAULT;
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6 ,10, 0))
	buf->vaddr = dma_buf_vmap(buf->dbuf, NULL);
#else
	buf->vaddr = dma_buf_vmap(buf->dbuf);
#endif

	return buf->vaddr ? 0 : -EFAULT;
#endif
}


static void vb2_gen_unmap_dmabuf(void *mem_priv)
{
	struct vb2_gen_buf *buf = mem_priv;

	dma_buf_vunmap(buf->dbuf, buf->vaddr);
	buf->vaddr = NULL;
}

static void vb2_gen_detach_dmabuf(void *mem_priv)
{
	struct vb2_gen_buf *buf = mem_priv;

	if (buf->vaddr)
		dma_buf_vunmap(buf->dbuf, buf->vaddr);

	kfree(buf);
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
static void *vb2_gen_attach_dmabuf(struct vb2_buffer *vb, struct device *dev, struct dma_buf *dbuf,
	unsigned long size)
#else
static void *vb2_gen_attach_dmabuf(struct device *dev, struct dma_buf *dbuf,
	unsigned long size, enum dma_data_direction dma_dir)
#endif
{
	struct vb2_gen_buf *buf;

	if (dbuf->size < size)
		return ERR_PTR(-EFAULT);

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	buf->dbuf = dbuf;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,15, 0))
	buf->dma_dir = vb->vb2_queue->dma_dir;
#else
	buf->dma_dir = dma_dir;
#endif
	buf->size = size;

	return buf;
}


const struct vb2_mem_ops vb2_gps_memops = {
	.alloc		= vb2_gps_alloc,
	.put		= vb2_gen_put,
	.get_userptr	= vb2_gen_get_userptr,
	.put_userptr	= vb2_gen_put_userptr,
#ifdef CONFIG_HAS_DMA
	.get_dmabuf	= vb2_gen_get_dmabuf,
#endif
	.map_dmabuf	= vb2_gen_map_dmabuf,
	.unmap_dmabuf	= vb2_gen_unmap_dmabuf,
	.attach_dmabuf	= vb2_gen_attach_dmabuf,
	.detach_dmabuf	= vb2_gen_detach_dmabuf,
	.vaddr		= vb2_gen_vaddr,
	.mmap		= vb2_gen_mmap,
	.num_users	= vb2_gen_num_users,
};

const struct vb2_mem_ops vb2_vt_memops = {
	.alloc		= vb2_vt_alloc,
	.put		= vb2_gen_put,
	.get_userptr	= vb2_gen_get_userptr,
	.put_userptr	= vb2_gen_put_userptr,
#ifdef CONFIG_HAS_DMA
	.get_dmabuf	= vb2_gen_get_dmabuf,
#endif
	.map_dmabuf	= vb2_gen_map_dmabuf,
	.unmap_dmabuf	= vb2_gen_unmap_dmabuf,
	.attach_dmabuf	= vb2_gen_attach_dmabuf,
	.detach_dmabuf	= vb2_gen_detach_dmabuf,
	.vaddr		= vb2_gen_vaddr,
	.mmap		= vb2_gen_mmap,
	.num_users	= vb2_gen_num_users,
};


EXPORT_SYMBOL_GPL(vb2_gps_memops);
EXPORT_SYMBOL_GPL(vb2_vt_memops);

MODULE_DESCRIPTION("capture driver memory handling routines for videobuf2");
MODULE_AUTHOR("Harish Chandra Singh <harish.singh@lge.com>");
MODULE_LICENSE("GPL");

