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

#ifndef __DMABUF_IMPORTER_H__
#define __DMABUF_IMPORTER_H__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/types.h>

#include <linux/dma-buf.h>


#ifndef MAGIC
#define MAGIC(a,b,c,d)		((a) | (b) << 8 | (c) << 16 | (d) << 24)
#endif

#define DMABUF_IO_MAGIC		MAGIC('d','m','a','b')

struct dmabuf_buffer_io_info {
	unsigned int magic;
	int fd;
	unsigned long long addr;
	unsigned long long size;
};

int dmabuf_helper_test_export_to_fd(struct device *dev,
							dma_addr_t addr, ulong size);


int dmabuf_helper_get_info_from_fd(struct device *dev,
						int fd,
                        dma_addr_t *addr,
                        ulong *size);

int dmabuf_ioctl_test_export(struct device *dev, unsigned long arg);

int dmabuf_ioctl_get_info(struct device *dev, unsigned long arg);

#endif /* __DMABUF_IMPORTER_H__ */

