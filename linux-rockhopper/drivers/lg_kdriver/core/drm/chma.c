/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <linux/version.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
#else
#include <linux/dma-direct.h>
#endif

#include <asm/cacheflush.h>

#include "hma_alloc.h"

static int debug_level = 0;
module_param(debug_level, int, 0640);

#define debug(fmt,args...)	do{ if (debug_level > 0) printk(KERN_DEBUG"%s.%d: "fmt,__func__,__LINE__,##args); }while(0)

struct hdma_priv {
	struct dma_map_ops ops;

	char poolname[0];
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static struct dma_map_ops *get_dma_ops(struct device *dev)
{
	return dev->archdata.dma_ops;
}

typedef struct dma_attrs *_dma_attrs_t;
#else

typedef unsigned long _dma_attrs_t;
#endif

static void *hdma_alloc(struct device *dev, size_t size,
			dma_addr_t * dma_handle, gfp_t gfp, _dma_attrs_t attrs)
{
	struct hdma_priv *priv =
	    container_of(get_dma_ops(dev), struct hdma_priv, ops);
	phys_addr_t addr;
	void *cpu_addr;

	debug("alloc %zd at %s..\n", size, priv->poolname);
	addr = hma_alloc(priv->poolname, size, PAGE_SIZE);
	if (!addr) {
		dev_err(dev, "no mem size %zd at %s,\n", size, priv->poolname);
		return NULL;
	}

	cpu_addr = hma_map(addr, size);
	if (cpu_addr)
		*dma_handle = (dma_addr_t) addr;
	else
		hma_free(priv->poolname, addr);

	debug("alloc %pad(0x%zx)\n", dma_handle, size);

	return cpu_addr;
}

static void hdma_free(struct device *dev, size_t size,
		      void *vaddr, dma_addr_t dma_handle, _dma_attrs_t attrs)
{
	struct hdma_priv *priv =
	    container_of(get_dma_ops(dev), struct hdma_priv, ops);

	debug("free %pad\n", &dma_handle);
	hma_unmap(vaddr);
	hma_free(priv->poolname, (phys_addr_t) dma_handle);
}

static int hdma_mmap(struct device *dev, struct vm_area_struct *vma,
		     void *vaddr, dma_addr_t dma_handle, size_t size,
		     _dma_attrs_t attrs)
{
	int ret;

	/* 메모리가 두개의 page 사이에 걸쳐있을 수 있다 */
	debug("map %pad(0x%zx) at 0x%lx - 0x%lx(0x%lx)\n", &dma_handle, size,
	      vma->vm_start, vma->vm_end, vma->vm_end - vma->vm_start);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
	vm_flags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
#else
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;	//to prevent swapout
#endif
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	ret = remap_pfn_range(vma, vma->vm_start,
			      dma_handle >> PAGE_SHIFT,
			      size, vma->vm_page_prot);
	return ret;
}

static int hdma_get_sgtable(struct device *dev, struct sg_table *sgt,
			    void *cpu_addr, dma_addr_t handle, size_t size,
			    _dma_attrs_t attrs)
{
	int ret = sg_alloc_table(sgt, 1, GFP_KERNEL);

	if (!ret)
		sg_set_page(sgt->sgl, phys_to_page(dma_to_phys(dev, handle)),
			    PAGE_ALIGN(size), 0);

	return ret;
}

static int hdma_map_sg(struct device *dev, struct scatterlist *sgl,
		       int nents, enum dma_data_direction dir,
		       _dma_attrs_t attrs)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 19, 0)
	struct scatterlist *sg;
	int i;

	for_each_sg(sgl, sg, nents, i)
	    __dma_map_area(phys_to_virt(dma_to_phys(dev, sg->dma_address)),
			   sg->length, dir);
#else
	// Calls ops->sync_sg_for_cpu(). But its null.
	dma_sync_sg_for_cpu(dev, sgl, nents, dir);
#endif

	return nents;
}

static void hdma_unmap_sg(struct device *dev,
			  struct scatterlist *sgl, int nents,
			  enum dma_data_direction dir, _dma_attrs_t attrs)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 19, 0)
	struct scatterlist *sg;
	int i;

	for_each_sg(sgl, sg, nents, i)
	    __dma_unmap_area(phys_to_virt(dma_to_phys(dev, sg->dma_address)),
			     sg->length, dir);
#else
	// Calls ops->sync_sg_for_cpu(). But its null.
	dma_sync_sg_for_cpu(dev, sgl, nents, dir);
#endif
}

int chma_set_dma_ops(struct device *dev, const char *poolname)
{
	struct hdma_priv *priv;

	priv = kzalloc(sizeof(*priv) + strlen(poolname) + 1, GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	strcpy(priv->poolname, poolname);
	priv->ops.alloc = hdma_alloc;
	priv->ops.free = hdma_free;
	priv->ops.mmap = hdma_mmap;
	priv->ops.get_sgtable = hdma_get_sgtable;
	priv->ops.map_sg = hdma_map_sg;
	priv->ops.unmap_sg = hdma_unmap_sg;
	// TODO: hma dma_buf cache sync
	priv->ops.sync_sg_for_cpu = NULL;
	priv->ops.sync_sg_for_device = NULL;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	dev->archdata.dma_ops = &priv->ops;
#else
	set_dma_ops(dev, &priv->ops);
#endif
	dev->coherent_dma_mask = DMA_BIT_MASK(32);
	dev->dma_mask = &dev->coherent_dma_mask;

	return 0;
}
