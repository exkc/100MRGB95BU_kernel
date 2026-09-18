/*
 * vb2_gen_memop.h - memory allocator for videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 * Modifier: Harish Chandra Singh <harish.singh@lge.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#ifndef _VB2_GEN_MEMOP_H
#define _VB2_GEN_MEMOP_H

#include <media/videobuf2-v4l2.h>
#include <media/videobuf2-memops.h>
#include "hma_alloc.h"

struct vb2_gen_buf {
	void				*vaddr;
	unsigned long int		phyAddr;
	struct frame_vector		*vec;
	enum dma_data_direction		dma_dir;
	unsigned long			size;
	refcount_t			refcount;
	//atomic_t			refcount;
	struct vb2_vmarea_handler	handler;
	struct dma_buf			*dbuf;
	char *mem_pool;
};

#endif

