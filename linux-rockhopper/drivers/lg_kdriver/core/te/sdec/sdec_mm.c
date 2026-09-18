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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sdec_impl.h"
#include "hma_alloc.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

static int get_mem_info(struct te_mem_ctx *h, LX_SDEC_MEM_INFO_T *info)
{
	struct te_mem_info i;

	te_mem_get_info(h, &i);

	info->addr = i.addr;
	info->size = i.size;
	info->free = i.free;
	info->avail = i.avail;

	return 0;
}

static int mem_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int rc;
	struct sdec_fh *fh = priv;
	struct te_mem_ctx *mem = fh->mem;
	LX_SDEC_MEM_INFO_T *info;
	u32 *addr;
	LX_SDEC_MEM_T *sdec_mem;
	u32 ptr;

	if (!mem) {
		mem = te_mem_open(TE_MEM_SDEC_NAME);
		if (!mem)
			return -EIO;

		fh->mem = mem;
	}

	switch (cmd) {
	case SDEC_IOC_MM_GETINFO:
		info = arg;
		rc = get_mem_info(mem, info);
		break;

	case SDEC_IOC_MM_FREE:
		addr = arg;
		rc = te_mem_free(mem, *addr);
		break;

	case SDEC_IOC_MM_ALLOC:
		sdec_mem = arg;

		ptr = te_mem_alloc(mem, sdec_mem->size, "user");
		if (!ptr) {
			rc = -ENOMEM;
		} else {
			rc = 0;
			sdec_mem->addr = ptr;
		}
		break;

	case SDEC_IOC_MM_CACHE_CTRL: {
		LX_TE_CACHE_CTRL_T *ctrl = arg;

		rc = te_mem_check_paddr_range(mem, ctrl->paddr, ctrl->size);
		if (rc)
			return rc;

		/* vaddr check needed? */

		rc = te_ioctl_cache_ctrl(ctrl);
		break;
	}
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		rc = -ENOTTY;
		break;
	}

	return rc;
}

static int mem_dev_open(struct sdec_fh *fh)
{
	return 0;
}

static void mem_dev_close(struct sdec_fh *fh)
{
	if (fh->mem) {
		te_mem_close(fh->mem);
	}
}

static int mem_dev_init(struct sdec_device *dev)
{
	int ret;
	struct te_mem_region_info *info;

	info = te_get_mem_region_info(TE_MEM_SDEC);
	ret = te_mem_register(TE_MEM_SDEC_NAME, info->addr, info->size,
			      TE_MEM_TYPE_NORMAL);
	CHECK_ERROR(ret, return ret, "can't register memory");

	return 0;
}

static void mem_dev_release(struct sdec_device *dev)
{
	te_mem_unregister(TE_MEM_SDEC_NAME);
}

static const struct sdec_ioctl ioctl_mem = {
	.magic = SDEC_IOC_MM_MAGIC,
	.func = mem_dev_ioctl,
};

const struct sdec_sub_driver sdec_mem_driver = {
	.name = "sdec_mem",
	.init = mem_dev_init,
	.release = mem_dev_release,

	.open = mem_dev_open,
	.close = mem_dev_close,
	.ioctl = &ioctl_mem,
};
