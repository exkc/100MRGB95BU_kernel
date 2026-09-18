/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2024 by LG Electronics Inc.
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

/** @file
 *
 *  helpers to import dma-buf
 *
 *  author
 *  version		1.0
 *  date		2024.06
 *  note		Additional information.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/rmap.h>
#include <linux/completion.h>
#include <linux/io.h>
#include <linux/types.h>

#include <linux/dma-buf.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/mm.h>
#include <linux/of_device.h>

#include "dmabuf_importer.h"

#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif



#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,16,0)

MODULE_IMPORT_NS(DMA_BUF);
#endif


struct buffer_priv_info {
	dma_addr_t addr;
	ulong size;
	struct dma_buf *dmabuf;
};


#ifdef CONFIG_COMPAT
static inline void __user *ulong_to_uptr(ulong value)
{
	if (is_compat_task())
		return compat_ptr(value);
	else
		return (void __user *)value;
}

#else

static inline void __user *ulong_to_uptr(ulong value)
{
	return (void __user *)value;
}

#endif


static inline bool check_contiguous(struct sg_table * sgt, int * nr_pages)
{
	struct scatterlist *sg;
	/* NOTE: Assume that the 'dma_address' space is the cpu physical address. */
	dma_addr_t cont_phys;
	dma_addr_t this_phys;
	int i;
	bool ret_val = true;

	cont_phys = sg_phys(sgt->sgl);

	*nr_pages = 0;

	for_each_sg(sgt->sgl, sg, sgt->nents, i) {
		this_phys = sg_phys(sg);
		if (this_phys != cont_phys) {
			/* not contigous */
			ret_val = false;
			break;
		}

		cont_phys = sg_dma_address(sg) + sg_dma_len(sg);
		*nr_pages += PAGE_ALIGN(sg_dma_len(sg)) >> PAGE_SHIFT;
	}

	//printk("%s: contig(%d), nr_pages=%d\n", __func__, (int)ret_val, *nr_pages);

	return ret_val;
}


static struct sg_table *test_export_dmabuf_map(
                                        struct dma_buf_attachment *attachment,
                                        enum dma_data_direction direction)
{
	struct sg_table *sgt;

	int ret;

	struct buffer_priv_info *buf_priv;

	buf_priv = (struct buffer_priv_info *)attachment->dmabuf->priv;

	if (NULL == buf_priv) {
		return ERR_PTR(-ENOMEM);
	}

	sgt = kmalloc(sizeof(struct sg_table), GFP_KERNEL);

	if (!sgt) {
		return ERR_PTR(-ENOMEM);
	}

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,2,0)

	mutex_lock(&attachment->dmabuf->lock);
#endif

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);

	if (ret) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,2,0)

		mutex_unlock(&attachment->dmabuf->lock);
#endif
		kfree(sgt);
		return ERR_PTR(ret);
	}

	sg_dma_len(sgt->sgl) = buf_priv->size;
	sg_set_page(sgt->sgl,
				pfn_to_page(PFN_DOWN(buf_priv->addr)),
				buf_priv->size,
				0);
	sg_dma_address(sgt->sgl) = buf_priv->addr;

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,2,0)

	mutex_unlock(&attachment->dmabuf->lock);
#endif

	return sgt;
}

static void test_export_dmabuf_unmap(struct dma_buf_attachment *attachment,
							 struct sg_table *sg,
							 enum dma_data_direction direction)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,2,0)

	mutex_lock(&attachment->dmabuf->lock);
#endif

	sg_free_table(sg);

	kfree(sg);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,2,0)

	mutex_unlock(&attachment->dmabuf->lock);
#endif
}

static void test_export_dmabuf_release(struct dma_buf *buf)
{
	struct buffer_priv_info *buf_priv = (struct buffer_priv_info *)buf->priv;

	if (buf_priv != NULL)
		kfree(buf_priv);

	pr_info("dma_buf release : 0x%lx\n", (ulong)(unsigned long long)buf);

	return;
}

static struct dma_buf_ops test_export_dmabuf_ops = {
	.map_dma_buf =           test_export_dmabuf_map,
	.unmap_dma_buf =         test_export_dmabuf_unmap,
	.release =               test_export_dmabuf_release,
};


int dmabuf_helper_test_export_to_fd(struct device *dev,
						dma_addr_t addr, ulong size)
{
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	struct dma_buf * dmabuf = NULL;

	struct buffer_priv_info *priv = NULL;

	int fd;

	(void)dev;

	if (addr == 0 || size == 0) {
		pr_err("%s: bad param (0x%llx:0x%lx)", __func__, addr, size);
		return -EINVAL;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL) {
		return -ENOMEM;
	}

	priv->addr = addr;
	priv->size = size;

	/* export dma-buf */
	exp_info.ops = &test_export_dmabuf_ops;
	exp_info.size = size;
	exp_info.flags = O_CLOEXEC|O_RDWR;
	exp_info.priv = (void *)priv;

	dmabuf = dma_buf_export(&exp_info);

	if (IS_ERR(dmabuf)) {
		pr_err("%s: couldn't export dma_buf", __func__);

		kfree(priv);
		return IS_ERR(dmabuf);
	}

	pr_info("dma_buf create : 0x%lx\n", (ulong)(unsigned long long)dmabuf);


	priv->dmabuf = dmabuf;

	fd = dma_buf_fd(dmabuf, O_CLOEXEC);

	if (fd < 0)
		dma_buf_put(dmabuf);

	return fd;
}


int dmabuf_helper_get_info_from_fd(struct device *dev,
						int fd,
                        dma_addr_t *addr,
                        ulong *size)
{
	struct sg_table * sgt;
	struct dma_buf_attachment * attachment;
	struct dma_buf *dma_buf;

	int res = -1;

	int nr_pages;

	(void)dev;

	dma_buf = dma_buf_get(fd);
	if (IS_ERR(dma_buf)) {
		pr_warn("warn, fd(%d) is not dma-buf\n", fd);
		return -EBADF;
	}

	attachment = dma_buf_attach(dma_buf, dev);
	if (IS_ERR(attachment)) {
		pr_err("fail to attach (fd:%d)\n", fd);

		res = PTR_ERR(attachment);
		goto fail_attach;
	}

	sgt = dma_buf_map_attachment(attachment, DMA_BIDIRECTIONAL);

	if (IS_ERR(sgt)) {
		pr_err("fail to map (fd:%d)\n", fd);

		res = PTR_ERR(sgt);
		goto fail_sgmap;
	}

	/* Where is this from? If it is not contiguous, not supported.*/
	if (check_contiguous(sgt, &nr_pages) != true) {
		pr_err("The buffer exported by '%s' is not contiguous (fd:%d)\n",
				dma_buf->exp_name, fd);

		res = -EINVAL;
		goto not_supported;
	}

	pr_info("NOTI:'%s' is importing the buffer exported by '%s'\n",
	        dev_name(dev), dma_buf->exp_name);

	*addr = (dma_addr_t)sg_dma_address(sgt->sgl);
	*size = dma_buf->size;

	res = 0;

not_supported:
	dma_buf_unmap_attachment(attachment, sgt, DMA_BIDIRECTIONAL);

fail_sgmap:
	dma_buf_detach(dma_buf, attachment);

fail_attach:
	dma_buf_put(dma_buf);

	return res;
}


int dmabuf_ioctl_test_export(struct device *dev, unsigned long arg)
{
	int fd = -1;

	struct dmabuf_buffer_io_info io_info = { };

	void __user *uptr = NULL;

	uptr = ulong_to_uptr(arg);

	//printk("uptr : 0x%lx\n", (ulong)uptr);

	if (copy_from_user((void *)&io_info, uptr, sizeof(io_info)) != 0) {

		return -EFAULT;
	}

	//printk("%x vs %x\n", io_info.magic, DMABUF_IO_MAGIC);

	if (io_info.magic != DMABUF_IO_MAGIC) {

		return -EINVAL;
	}

	fd = dmabuf_helper_test_export_to_fd(dev,
								(dma_addr_t)io_info.addr, (ulong)io_info.size);

	if (fd < 0) {

		return -EBADF;
	}

	io_info.fd = fd;

	if (copy_to_user(uptr, (void *)&io_info, sizeof(io_info)) != 0) {

		return -EFAULT;
	}

	return 0;
}

int dmabuf_ioctl_get_info(struct device *dev, unsigned long arg)
{
	int res = 0;

	struct dmabuf_buffer_io_info io_info = { };

	dma_addr_t addr = 0;
	ulong size = 0;

	void __user *uptr = NULL;

	uptr = ulong_to_uptr(arg);

	if (copy_from_user((void *)&io_info, uptr, sizeof(io_info)) != 0) {

		return -EFAULT;
	}

	if (io_info.magic != DMABUF_IO_MAGIC) {

		return -EINVAL;
	}

	res = dmabuf_helper_get_info_from_fd(dev, io_info.fd, &addr, &size);
	if (res != 0) {
		pr_err("fail (%s) : getting from fd (res:%d)\n", __func__,  res);
		return res;
	}

	io_info.addr = (unsigned long long)addr;
	io_info.size = (unsigned long long)size;

	if (copy_to_user(uptr, (void *)&io_info, sizeof(io_info)) != 0) {

		return -EFAULT;
	}

	return 0;
}

