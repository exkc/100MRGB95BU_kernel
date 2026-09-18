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
 *  atsc3 memory driver
 *
 *  @author		Yeonju Lee ( yeonju.lee@lge.com)
 *  @version	0.1
 *  @date		2016-02-29
 *  @note		Additional information.
 */

#include "atsc3_impl.h"

static int mem_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct atsc3_fh *fh = priv;

	if (!fh->mem) {
		fh->mem = te_mem_open(ATSC3_MEM_NAME);
		if (!fh->mem)
			return -EIO;
	}

	if (cmd == ATSC3_IOC_MM_GETINFO) {
		LX_ATSC3_MEM_INFO_T *info = arg;
		struct te_mem_info i;

		te_mem_get_info(fh->mem, &i);

		info->addr = i.addr;
		info->size = i.size;
		info->free = i.free;
		info->avail = i.avail;
		ret = 0;
	} else if (cmd == ATSC3_IOC_MM_FREE) {
		u32 *params = arg;
		ret = te_mem_free(fh->mem, *params);
	} else if (cmd == ATSC3_IOC_MM_ALLOC) {
		LX_ATSC3_MEM_T *params = arg;
		u32 ptr;

		ptr = te_mem_alloc(fh->mem, params->size, "atsc3_user");
		if (!ptr) {
			ret = -ENOMEM;
		} else {
			ret = 0;
			params->addr = ptr;
		}
	} else if (cmd == ATSC3_IOC_MM_CACHE_CTRL) {
		LX_TE_CACHE_CTRL_T *param = arg;

		ret = te_mem_check_paddr_range(fh->mem, param->paddr,
					       param->size);
		if (ret)
			return ret;

		/* vaddr check needed? */

		ret = te_ioctl_cache_ctrl(param);
	} else {
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
	}

	return ret;
}

static void mem_dev_close(struct atsc3_fh *fh)
{
	if (fh->mem) {
		te_mem_close(fh->mem);
	}
}

static int mem_dev_init(struct atsc3_device *dev)
{
	int ret;
	struct te_mem_region_info *info;

	info = te_get_mem_region_info(TE_MEM_SHARED);
	ret = te_mem_register(ATSC3_MEM_NAME, info->addr, info->size,
			      TE_MEM_TYPE_CMA);

	CHECK_ERROR(ret, return ret, "can't register memory");

	return 0;
}

static void mem_dev_release(struct atsc3_device *dev)
{
	te_mem_unregister(ATSC3_MEM_NAME);
}

static const struct atsc3_ioctl ioctl_mem = {
	.magic = ATSC3_IOC_MM_MAGIC,
	.func = mem_dev_ioctl,
};

const struct atsc3_sub_driver atsc3_mem_driver = {
	.name = "atsc3_mem",
	.init = mem_dev_init,
	.release = mem_dev_release,

//      .open = mem_open,
	.close = mem_dev_close,
	.ioctl = &ioctl_mem,
};
