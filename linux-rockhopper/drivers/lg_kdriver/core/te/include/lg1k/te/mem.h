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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-10-12
 *  @note		Additional information.
 */

#ifndef _LG1K_TE_MEM_H_
#define _LG1K_TE_MEM_H_

#include <linux/types.h>

/* default registered memory names */
#define TE_MEM_MCU_NAME		"te_mcu"
#define TE_MEM_SDEC_NAME	"sdec"
#define TE_MEM_SHARED_NAME	"te_shared"
#define TE_MEM_PVR_NAME		"pvr"

struct te_mem_ctx;

typedef u32 te_phys_addr_t;

enum te_mem_region {
	TE_MEM_MCU = 0,
	TE_MEM_SDEC,
	TE_MEM_SHARED,
	TE_MEM_PVR,
	TE_MEM_REGION_MAX,
	TE_MEM_TOTAL = 100,
};

struct te_mem_region_info {
	u32 addr;
	u32 size;
};

enum te_mem_type {
	TE_MEM_TYPE_NORMAL = 0,
	TE_MEM_TYPE_HMA,
	TE_MEM_TYPE_CMA,
	TE_MEM_TYPE_BIGCMA,	/* allocate whole cma area at first time */
};

struct te_mem_info {
	u32 addr;
	u32 size;
	u32 free;
	u32 avail;
};

struct te_mem_region_info *te_get_mem_region_info(enum te_mem_region region);

int te_mem_register(const char *name, u32 addr, u32 size,
		    enum te_mem_type type);
void te_mem_unregister(const char *name);

struct te_mem_ctx *te_mem_open(const char *name);
void te_mem_close(struct te_mem_ctx *mem);

te_phys_addr_t te_mem_alloc_user(struct te_mem_ctx *ctx, size_t size,
				 const char *name, size_t align);
te_phys_addr_t te_mem_alloc(struct te_mem_ctx *ctx, size_t size,
			    const char *name);
int te_mem_free(struct te_mem_ctx *ctx, te_phys_addr_t addr);
int te_mem_get_info(struct te_mem_ctx *ctx, struct te_mem_info *info);
int te_mem_check_paddr_range(struct te_mem_ctx *h, u32 paddr, u32 size);

#endif				/* _LG1K_TE_MEM_H_ */
