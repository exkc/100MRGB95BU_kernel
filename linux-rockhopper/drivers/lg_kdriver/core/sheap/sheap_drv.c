/*
 * SoC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
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

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/dma-buf.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>

#include "sheap.h"
#include "sheap_kapi.h"
#include "logm.h"
#include "hma_alloc.h"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
MODULE_IMPORT_NS(DMA_BUF);
#endif

#define DEV_NAME "sheap"

#define debug(fmt, args...) logm_debug(sheap, fmt, ##args)
#define info(fmt, args...) logm_info(sheap, fmt, ##args)
#define noti(fmt, args...) logm_noti(sheap, fmt, ##args)
#define warn(fmt, args...) logm_warning(sheap, fmt, ##args)
#define error(fmt, args...) logm_error(sheap, fmt, ##args)

logm_define(sheap, log_level_noti);

static struct sheap sheap;

static int sheap_open(struct inode *inode, struct file *fp)
{
	debug("open.. minor:%d\n", iminor(inode));

	return 0;
}

static int sheap_release(struct inode *inode, struct file *fp)
{
	debug("close.. minor:%d\n", iminor(inode));

	return 0;
}

static int sheap_buf_attach(struct dma_buf *dmabuf,
							struct dma_buf_attachment *attachment)
{
	struct sheap_buf *buf = dmabuf->priv;
	struct sheap_attachment *sa;
	struct sg_table *table;

	sa = kzalloc(sizeof(*sa), GFP_KERNEL);
	if (!sa) {
		error("kzalloc %zd failed\n", sizeof(*sa));
		return -ENOMEM;
	}

	table = &sa->table;
	if (sg_alloc_table(table, 1, GFP_KERNEL)) {
		kfree(sa);
		return -ENOMEM;
	}

	sg_set_page(table->sgl, phys_to_page(buf->paddr), buf->size, 0);
	sg_dma_address(table->sgl) = buf->paddr;
	sg_dma_len(table->sgl) = buf->size;

	sa->dev = attachment->dev;
	attachment->priv = sa;

	debug("attachment%p dev:%s table:%p\n", sa, dev_name(sa->dev), table);

	return 0;
}

static void sheap_buf_detach(struct dma_buf *dmabuf,
							 struct dma_buf_attachment *attachment)
{
	struct sheap_attachment *sa = attachment->priv;

	debug("detachment%p table:%p\n", sa, &sa->table);

	sg_free_table(&sa->table);
	kfree(sa);
}

static struct sg_table *
sheap_buf_map_dma_buf(struct dma_buf_attachment *attachment,
					  enum dma_data_direction direction)
{
	struct sheap_attachment *a = attachment->priv;

	return &a->table;
}

static void sheap_buf_unmap_dma_buf(struct dma_buf_attachment *attachment,
									struct sg_table *table,
									enum dma_data_direction direction)
{
}

static void sheap_buf_release(struct dma_buf *dmabuf)
{
	struct sheap_buf *buf = dmabuf->priv;

	debug("free %d, dmabuf:%p\n", buf->size, dmabuf);

	hma_free(sheap.poolname, buf->paddr);
	kfree(buf);
}

static const struct dma_buf_ops sheap_buf_ops = {
	.attach = sheap_buf_attach,
	.detach = sheap_buf_detach,
	.map_dma_buf = sheap_buf_map_dma_buf,
	.unmap_dma_buf = sheap_buf_unmap_dma_buf,
	.release = sheap_buf_release,
};

static struct dma_buf *alloc_dma_buf(int len, int fd_flags, int heap_flags)
{
	struct dma_buf *dmabuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	struct sheap_buf *buf;
	int ret = -ENOMEM;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf) {
		error("kzalloc %zd failed\n", sizeof(*buf));
		return ERR_PTR(-ENOMEM);
	}

	buf->size = len;
	buf->paddr = hma_alloc_user(sheap.poolname, len, PAGE_SIZE, "sheap");
	if (!buf->paddr) {
		error("hma alloc failed size:%d\n", len);
		goto free_buf;
	}

	exp_info.ops = &sheap_buf_ops;
	exp_info.size = buf->size;
	exp_info.flags = fd_flags;
	exp_info.priv = buf;
	dmabuf = dma_buf_export(&exp_info);
	if (IS_ERR(dmabuf)) {
		error("dma buf export failed\n");
		ret = PTR_ERR(dmabuf);
		goto free_hma;
	}

	return dmabuf;

free_hma:
	hma_free(sheap.poolname, buf->paddr);

free_buf:
	kfree(buf);

	return ERR_PTR(ret);
}

static int sheap_alloc(int len, int fd_flags, int heap_flags)
{
	struct dma_buf *dmabuf;
	int fd;

	len = PAGE_ALIGN(len);
	if (!len) {
		error("len is null\n");
		return -EINVAL;
	}

	dmabuf = alloc_dma_buf(len, fd_flags, heap_flags);
	if (IS_ERR(dmabuf)) {
		error("dmabuf alloc error\n");
		return -EINVAL;
	}

	fd = dma_buf_fd(dmabuf, fd_flags);
	if (fd < 0) {
		error("dma buf fd error %d\n", fd);
		dma_buf_put(dmabuf);
	}

	debug("alloc %d, dmabuf:%p, fd:%d\n", len, dmabuf, fd);

	return fd;
}

static long sheap_ioctl_alloc(struct sheap_alloc_data *adata)
{
	int fd;

	if (adata->fd) {
		error("fd:%d already exists\n", adata->fd);
		return -EINVAL;
	}

	if (adata->fd_flags & ~SHEAP_VALID_FD_FLAGS) {
		error("fd_flags %x now allowed\n", adata->fd_flags);
		return -EINVAL;
	}

	if (adata->heap_flags & ~SHEAP_VALID_HEAP_FLAGS) {
		error("heap_flags %llx now allowed\n", adata->heap_flags);
		return -EINVAL;
	}

	fd = sheap_alloc(adata->len, adata->fd_flags, adata->heap_flags);
	if (fd < 0)
		return fd;

	adata->fd = fd;

	return 0;
}

static long sheap_ioctl_attach(struct sheap_attach_data *adata)
{
	long ret = 0;
	struct dma_buf *dmabuf;
	struct dma_buf_attachment *attachment;
	struct sg_table *table;

	if (!adata->fd) {
		error("invalid fd\n");
		return -EINVAL;
	}

	dmabuf = dma_buf_get(adata->fd);
	if (IS_ERR(dmabuf)) {
		error("dma_buf_get failed\n");
		return PTR_ERR(dmabuf);
	}

	attachment = dma_buf_attach(dmabuf, sheap.dev);
	if (IS_ERR(dmabuf)) {
		error("dma_buf_attach failed\n");
		return PTR_ERR(attachment);
	}

	table = dma_buf_map_attachment(attachment, DMA_BIDIRECTIONAL);
	if (IS_ERR(table)) {
		ret = PTR_ERR(table);
		goto fail_detach;
	}

	adata->paddr = sg_dma_address(table->sgl);

	debug("dmabuf%p(fd:%d) attach:%p table:%p paddr:%llx \n", dmabuf, adata->fd,
		  attachment, table, adata->paddr);

	dma_buf_unmap_attachment(attachment, table, DMA_BIDIRECTIONAL);

fail_detach:
	dma_buf_detach(dmabuf, attachment);
	dma_buf_put(dmabuf);

	return ret;
}

static long sheap_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	long ret = 0;
	union args {
		struct sheap_alloc_data alloc_data;
		struct sheap_attach_data attach_data;
	} kdata;

	debug("cmd %08x\n", cmd);
	if (_IOC_TYPE(cmd) != SHEAP_IOC_MAGIC) {
		error("wrong ioctl cmd%d\n", cmd);
		return -EINVAL;
	}

	/* copy arg data from user space */
	if (_IOC_DIR(cmd) & _IOC_WRITE) {
		int r;
		r = copy_from_user(&kdata, (void *)arg, _IOC_SIZE(cmd));
		if (r) {
			error("copy_from_user failed. cmd:%d arg:%08lx\n", cmd, arg);
			return -EFAULT;
		}
	} else {
		memset(&kdata, 0, sizeof(kdata));
	}

	switch (cmd) {
	case SHEAP_IOCTL_ALLOC:
		ret = sheap_ioctl_alloc(&kdata.alloc_data);
		break;
	case SHEAP_IOCTL_ATTACH:
		ret = sheap_ioctl_attach(&kdata.attach_data);
		break;
	default:
		ret = -ENOTTY; /* Inappropriate ioctl for device */
		break;
	}

	if (ret >= 0 && _IOC_DIR(cmd) & _IOC_READ) {
		int r;

		r = copy_to_user((void *)arg, &kdata, _IOC_SIZE(cmd));
		if (r) {
			error("copy_to_user failed. cmd:%d arg:%08lx\n", cmd, arg);
			return -EFAULT;
		}
	}

	return ret;
}

static struct file_operations fops = {
	.open = sheap_open,
	.release = sheap_release,
	.unlocked_ioctl = sheap_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = sheap_ioctl,
#endif
};

static int __init sheap_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&sheap.devt, 0, 1, DEV_NAME);
	if (ret) {
		error("chrdev alloc failed %d\n", ret);
		return ret;
	}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
	sheap.class = class_create(DEV_NAME);
#else
	sheap.class = class_create(THIS_MODULE, DEV_NAME);
#endif
	if (IS_ERR(sheap.class)) {
		error("class create failed\n");
		ret = PTR_ERR(sheap.class);
		goto err_class;
	}

	cdev_init(&sheap.cdev, &fops);
	ret = cdev_add(&sheap.cdev, sheap.devt, 1);
	if (ret < 0) {
		error("cdev add failed %d\n", ret);
		goto err_cdev;
	}

	sheap.dev = device_create(sheap.class, NULL, sheap.devt, NULL, DEV_NAME);
	if (IS_ERR(sheap.dev)) {
		error("device create failed\n");
		ret = PTR_ERR(sheap.dev);
		goto err;
	}

	sheap.poolname = "vpb";

	noti("%s(major:%d) has been loaded\n", DEV_NAME, MAJOR(sheap.devt));

	return 0;

err:
	cdev_del(&sheap.cdev);
err_cdev:
	class_destroy(sheap.class);
err_class:
	unregister_chrdev_region(sheap.devt, 1);
	return ret;
}

static void __exit sheap_exit(void)
{
	cdev_del(&sheap.cdev);
	device_destroy(sheap.class, sheap.devt);
	class_destroy(sheap.class);
	unregister_chrdev_region(sheap.devt, 1);

	noti("%s has been unloaded\n", DEV_NAME);
}

module_init(sheap_init);
module_exit(sheap_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("lg1k secure heap driver");
MODULE_VERSION("0.5");
