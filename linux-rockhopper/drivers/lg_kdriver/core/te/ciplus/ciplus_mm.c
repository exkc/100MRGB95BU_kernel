/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  ciplus memory driver
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2015-11-03
 *  @note		Additional information.
 */

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "ciplus_impl.h"

static int init(struct ciplus_device *dev)
{
	int ret;
	struct te_mem_region_info *info;

	info = te_get_mem_region_info(TE_MEM_SHARED);

	ret = te_mem_register(CIPLUS_MEM_NAME, info->addr, info->size,
			      TE_MEM_TYPE_CMA);
	CHECK_ERROR(ret, return ret, "can't register memory");

	dev->mem = te_mem_open(CIPLUS_MEM_NAME);
	CHECK_ERROR(!dev->mem, goto err_cip_mem, "Error in te_mem_open");

	return 0;

err_cip_mem:
	te_mem_unregister(CIPLUS_MEM_NAME);
	return -EIO;
}

static void release(struct ciplus_device *dev)
{
	te_mem_close(dev->mem);
	te_mem_unregister(CIPLUS_MEM_NAME);
}

static int get_mem_info(struct te_mem_ctx *h, LX_CIPLUS_MEM_INFO_T *info)
{
	struct te_mem_info i;

	te_mem_get_info(h, &i);

	info->addr = i.addr;
	info->size = i.size;
	info->free = i.free;
	info->avail = i.avail;

	return 0;
}

static int alloc_mem(struct te_mem_ctx *ctx, LX_CIPLUS_MEM_T *mem)
{
	u32 ptr;

	ptr = te_mem_alloc(ctx, mem->size, "ci+");
	CHECK_ERROR(!ptr, return -ENOMEM, "Alloc Failed");

	mem->addr = ptr;
	return 0;
}

static int do_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct ciplus_fh *fh = priv;
	u32 *ptr;

	//MUTEX LOCK HERE

	switch (cmd) {
	case CIPLUS_MM_OPEN:
		if (fh->mem) {
			log_error("MM is already opend\n");
			return -EBUSY;
		}
		fh->mem = te_mem_open(CIPLUS_MEM_NAME);
		CHECK_ERROR(!fh->mem, return -ENOMEM, "MM allocation failed");
		ret = 0;
		break;
	case CIPLUS_MM_CLOSE:
		if (fh->mem) {
			te_mem_close(fh->mem);
			fh->mem = NULL;
		}
		ret = 0;
		break;
	case CIPLUS_MM_ALLOC:
		CHECK_ERROR(!fh->mem, return -EINVAL, "MM is not opened");

		ret = alloc_mem(fh->mem, arg);
		break;
	case CIPLUS_MM_FREE:
		CHECK_ERROR(!fh->mem, return -EINVAL, "MM is not opened");

		ptr = arg;
		ret = te_mem_free(fh->mem, *ptr);
		break;
	case CIPLUS_MM_GETINFO:
		CHECK_ERROR(!fh->mem, return -EINVAL, "MM is not opened");
		ret = get_mem_info(fh->mem, arg);
		break;
	case CIPLUS_MM_CACHE_CTRL: {
		LX_TE_CACHE_CTRL_T *param = arg;

		CHECK_ERROR(!fh->mem, return -EINVAL, "MM is not opened");
		ret = te_mem_check_paddr_range(fh->mem, param->paddr,
					       param->size);
		if (ret)
			return ret;

		/* vaddr check needed? */

		ret = te_ioctl_cache_ctrl(param);
		break;
	}
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	//MUTEX UNLOCK HERE

	return ret;
}

static void close(struct ciplus_fh *fh)
{
	if (fh->mem) {
		te_mem_close(fh->mem);
	}
}

static const struct ciplus_ioctl ioctl_mem = {
	.magic = CIPLUS_IOC_MM_MAGIC,
	.func = do_ioctl,
};

const struct ciplus_sub_driver ciplus_mem_driver = {
	.name = "ciplus_mem",
	.init = init,
	.release = release,

//      .open = mem_open,
	.close = close,
	.ioctl = &ioctl_mem,
};
