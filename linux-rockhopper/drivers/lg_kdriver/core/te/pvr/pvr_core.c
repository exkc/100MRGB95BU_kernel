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
 *  pvr device driver
 *
 *  author		ks.hyun(ks.hyunlge.com)
 *  version		1.0
 *  date		2018.10.29
 *  note		Additional information.
 *
 */

#include <lg1k/te/mem.h>

#include "pvr_impl.h"

static const struct pvr_sub_driver *sub_drivers[] = {
	&pvr_debug_driver,
	&pvr_dn_driver,
	&pvr_up_driver,
	&pvr_isr_driver,
};

struct pvr_device *pvr_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, PVR_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_pvr_device(sd);
}

bool pvr_is_shared_mem(struct pvr_device *dev)
{
	return dev->cfg->use_shared_mem;
}

static int init_hw(struct pvr_device *dev)
{
	TE_REG_SetHwDownloadEnable(true);
	TE_REG_SetDownloadTimeStampMode(TIMESTAMP_MODE_32BITS);

	if (dev->cfg->no_pie) {
		/* Disable Hardware PIE */
		TE_REG_SetHwPieEnable(false);
	} else {
		TE_REG_SetHwPieEnable(true);
	}

	return 0;
}

static void enable_interrupt(void)
{
	/* enable BE & UPLOAD interrupt */
	TE_REG_SetIntrEnable(TOP_INTR_BE | TOP_INTR_UPLOAD0 | TOP_INTR_UPLOAD1,
			     true);

	TE_REG_SetBeIntrEnable(BE_INTR_SEGMENT_DN0 | BE_INTR_SEGMENT_DN1, true);
}

static void disable_interrupt(void)
{
	u32 mask;		// Disable all available BE mask

	mask = BE_INTR_SEGMENT_DN0 | BE_INTR_SEGMENT_DN1 | BE_INTR_BE_DONE |
	    BE_INTR_CLEAR_TSBUFFER | BE_INTR_PIE_DETECT |
	    BE_INTR_CLEAR_TSBUFFER_FULL;

	TE_REG_SetBeIntrEnable(mask, false);

	TE_REG_SetIntrEnable(TOP_INTR_BE | TOP_INTR_UPLOAD0 | TOP_INTR_UPLOAD1,
			     false);
}

static int init_memory(struct pvr_device *dev)
{
	int ret;
	struct te_mem_region_info *info;

	if (!dev->cfg->use_shared_mem) {
		info = te_get_mem_region_info(TE_MEM_PVR);
		ret = te_mem_register(PVR_MEM_NAME, info->addr, info->size,
				      TE_MEM_TYPE_CMA);
		CHECK_ERROR(ret, return ret, "can't register memory(%s)",
			    PVR_MEM_NAME);
	}


	info = te_get_mem_region_info(TE_MEM_SHARED);
	ret = te_mem_register(TE_MEM_SHARED_NAME, info->addr, info->size,
			      TE_MEM_TYPE_CMA);
	CHECK_ERROR(ret, goto err_mem_register, "can't register memory(%s)",
		    TE_MEM_SHARED_NAME);


	return 0;

err_mem_register:
	if (!dev->cfg->use_shared_mem)
		te_mem_unregister(PVR_MEM_NAME);

	return ret;
}

static void release_memory(struct pvr_device *dev)
{
	if (!dev->cfg->use_shared_mem)
		te_mem_unregister(PVR_MEM_NAME);
}

/* deprecated. will be removed */
static int get_hw_info(LX_PVR_HW_INFO_T *info)
{
	struct pvr_config *cfg = pvr_get_config();
	struct te_mem_region_info *mem_info =
	    te_get_mem_region_info(TE_MEM_PVR);

	info->num_dndev = cfg->num_dn;
	info->num_updev = cfg->num_up;
	info->mem_size = mem_info->size;

	info->no_pie = cfg->no_pie;
	info->swap_dn_timestamp = cfg->swap_dn_timestamp;
	info->fixup_index_error = cfg->fixup_index_error;
	info->fix_up_timestamp = cfg->fix_up_timestamp;

	return 0;
}

static int sub_device_init(struct pvr_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct pvr_sub_driver *s = sub_drivers[i];

		if (s->init) {
			log_device("'%s' - init start\n", s->name);
			ret = s->init(dev);
			if (ret) {
				log_error("'%s' init failed\n", s->name);
				return ret;
			}
			log_device("'%s' - init done\n", s->name);
		}
	}

	return 0;
}

static void sub_device_release(struct pvr_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct pvr_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

static int sub_device_suspend(struct pvr_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct pvr_sub_driver *s = sub_drivers[i - 1];

		if (s->suspend) {
			log_device("'%s' - suspend start\n", s->name);
			ret = s->suspend(dev);
			if (ret) {
				log_error("'%s' suspend failed\n", s->name);
				return ret;
			}
			log_device("'%s' - suspend done\n", s->name);
		}
	}

	return 0;
}

static int sub_device_resume(struct pvr_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct pvr_sub_driver *s = sub_drivers[i];

		if (s->resume) {
			log_device("'%s' - resume start\n", s->name);
			ret = s->resume(dev);
			if (ret) {
				log_error("'%s' resume failed\n", s->name);
				return ret;
			}
			log_device("'%s' - resume done\n", s->name);
		}
	}

	return 0;
}

static struct te_mem_ctx *mem_open(struct pvr_device *dev, int id)
{
	struct te_mem_ctx *mem;
	const char *name;

	name = (id == LX_PVR_MM_ID_0) ? PVR_MODULE : TE_MEM_SHARED_NAME;
	if (id == LX_PVR_MM_ID_0 && pvr_is_shared_mem(dev)) {
		log_warning("ID:0 is considered as shared memory");
		name = TE_MEM_SHARED_NAME;
	}

	mem = te_mem_open(name);
	CHECK_ERROR(!mem, return NULL, "Err in te_mem_open('%s')\n", name);

	return mem;
}

/* deprecated. will be removed */
static int ioc_mem_alloc(struct pvr_fh *fh, LX_PVR_MM_ALLOC_T *param)
{
	int ret;
	u32 ptr;
	struct te_mem_ctx *mem;

	CHECK_ERROR(param->id >= LX_PVR_MM_ID_MAX,
		    return -EINVAL, "invalid id(%d)", param->id);

	mem = fh->mem[param->id];
	if (!mem) {
		mem = mem_open(fh->dev, param->id);
		if (!mem)
			return -EIO;

		fh->mem[param->id] = mem;
	}

	ptr = te_mem_alloc(mem, param->size, "USER");
	if (ptr == 0) {
		ret = -ENOMEM;
	} else {
		ret = 0;
		param->addr = ptr;
	}

	return ret;
}

/* deprecated. will be removed */
static int ioc_mem_free(struct pvr_fh *fh, LX_PVR_MM_FREE_T *param)
{
	struct te_mem_ctx *mem;

	CHECK_PARAM(param->id >= LX_PVR_MM_ID_MAX,
		    "invalid id(%d)", param->id);

	mem = fh->mem[param->id];
	CHECK_PARAM(!mem, "mem not opened - id(%d)", param->id);

	return te_mem_free(mem, param->addr);
}

bool pvr_device_check_paddr_range(struct pvr_fh *fh, u32 paddr, u32 size)
{
	struct te_mem_ctx *mem;
	int i, rc;

	for (i = 0; i < LX_PVR_MM_ID_MAX; i++) {
		mem = fh->mem[i];
		if (!mem)
			continue;

		rc = te_mem_check_paddr_range(mem, paddr, size);
		if (!rc) // 0 means the range is inside the memory pool
			return true;
	}

	return false;
}

static int ioctl_device(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct pvr_fh *fh = priv;

	switch (cmd) {
	case PVR_IOC_INIT:
		ret = 0;
		break;
	case PVR_IOC_GET_HW_INFO:
		ret = get_hw_info(arg);
		break;
	case PVR_IOC_MM_CACHE_CTRL: {
		struct lx_te_cache_ctrl *p = arg;
		if (!pvr_device_check_paddr_range(fh, p->paddr, p->size))
			return -EFAULT;

		/* vaddr check needed? */

		ret = te_ioctl_cache_ctrl(p);
		break;
	}
	case PVR_IOC_MM_ALLOC:
		ret = ioc_mem_alloc(fh, arg);
		break;
	case PVR_IOC_MM_FREE:
		ret = ioc_mem_free(fh, arg);
		break;
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static int open_device(struct pvr_fh *fh)
{
	return 0;
}

static void close_device(struct pvr_fh *fh)
{
	int i;

	for (i = 0; i < LX_PVR_MM_ID_MAX; i++) {
		if (fh->mem[i])
			te_mem_close(fh->mem[i]);
	}
}

static struct pvr_node core_node = {
	.open = open_device,
	.close = close_device,
	.ioctl = ioctl_device,
};

int pvr_device_init(struct pvr_device *dev)
{
	int ret;

	mutex_init(&dev->mutex);

	dev->node[PVR_DEV_TYPE_CORE] = &core_node;

	init_memory(dev);

	ret = init_hw(dev);
	CHECK_ERROR(ret, return ret, "Error in init_hw");

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_init");

	enable_interrupt();

	return 0;
}

void pvr_device_release(struct pvr_device *dev)
{
	disable_interrupt();

	sub_device_release(dev);

	release_memory(dev);
}

int pvr_device_suspend(struct pvr_device *dev)
{
	int ret;

	disable_interrupt();

	ret = sub_device_suspend(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_suspend(%d)", ret);

	return 0;
}

int pvr_device_resume(struct pvr_device *dev)
{
	int ret;

	init_hw(dev);

	ret = sub_device_resume(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_resume(%d)", ret);

	enable_interrupt();

	return 0;
}
