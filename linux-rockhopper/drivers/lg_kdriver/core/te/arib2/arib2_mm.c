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
 *  arib2 memory driver
 *
 *  @author		Yeonju Lee ( yeonju.lee@lge.com)
 *  @version		0.1
 *  @date		2017-11-21
 *  @note		Additional information.
 */

#include <lg1k/te/mem.h>

#include "arib2_impl.h"

static int mem_dev_init(struct arib2_device *dev)
{
	int ret;
	struct te_mem_region_info *info;

	info = te_get_mem_region_info(TE_MEM_SHARED);
	ret = te_mem_register(ARIB2_MEM_NAME, info->addr, info->size,
			      TE_MEM_TYPE_CMA);

	CHECK_ERROR(ret, return ret, "can't register memory");

	return 0;
}

static void mem_dev_release(struct arib2_device *dev)
{
	te_mem_unregister(ARIB2_MEM_NAME);
}

static void mem_dev_close(struct arib2_fh *fh)
{
	if (fh->mem) {
		te_mem_close(fh->mem);
	}
}

static int mem_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct arib2_fh *fh = priv;
	struct te_mem_ctx *ctx;
	LX_ARIB2_MEM_INFO_T *info;
	struct te_mem_info mem_info;
	LX_ARIB2_MEM_T *mem;
	LX_TE_CACHE_CTRL_T *cache;
	u32 *addr;
	u32 ptr;

	ctx = fh->mem;
	if (!ctx) {
		ctx = te_mem_open(ARIB2_MEM_NAME);
		if (!ctx)
			return -EIO;
		fh->mem = ctx;
	}

	switch (cmd) {
	case ARIB2_IOC_MM_GETINFO:
		info = arg;

		te_mem_get_info(ctx, &mem_info);

		info->addr = mem_info.addr;
		info->size = mem_info.size;
		info->free = mem_info.free;
		info->avail = mem_info.avail;
		ret = 0;
		break;

	case ARIB2_IOC_MM_FREE:
		addr = arg;
		ret = te_mem_free(ctx, *addr);
		break;
	case ARIB2_IOC_MM_ALLOC:
		mem = arg;
		ptr = te_mem_alloc(ctx, mem->size, "arib2_user");
		if (!ptr) {
			ret = -ENOMEM;
		} else {
			ret = 0;
			mem->addr = ptr;
		}
		break;
	case ARIB2_IOC_MM_CACHE_CTRL:
		cache = arg;

		/* check paddr range for input validation */
		ret = te_mem_check_paddr_range(ctx, cache->paddr, cache->size);
		if (ret)
			return ret;

		/* vaddr check needed? */

		ret = te_ioctl_cache_ctrl(cache);
		break;
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static const struct arib2_ioctl ioctl_mem = {
	.magic = ARIB2_IOC_MM_MAGIC,
	.func = mem_dev_ioctl,
};

const struct arib2_sub_driver arib2_mem_driver = {
	.name = "arib2_mem",
	.init = mem_dev_init,
	.release = mem_dev_release,

	.close = mem_dev_close,
	.ioctl = &ioctl_mem,
};
