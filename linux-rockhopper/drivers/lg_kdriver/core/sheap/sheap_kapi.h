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

#ifndef _SHEAP_KAPI_H_
#define _SHEAP_KAPI_H_

#include <linux/ioctl.h>
#include <linux/types.h>

/**
 * DOC: Secure DMA-BUF Allocator Userspace API
 */

/* Valid FD_FLAGS are O_CLOEXEC, O_RDONLY, O_WRONLY, O_RDWR */
#define SHEAP_VALID_FD_FLAGS (O_CLOEXEC | O_ACCMODE)

/* Currently no heap flags */
#define SHEAP_VALID_HEAP_FLAGS (0)

/**
 * struct sheap_alloc_data - metadata passed from userspace for
 *                                  allocations.
 * @len:        size of the allocation.
 * @fd:         will be populated with a fd which provides the handle
 *              to the allocated dma-buf.
 * @fd_flags:   file descriptor flags used when allocating.
 * 				O_CLOEXEC flag should be set.
 * 				O_RDONLY, O_WRONLY, O_RDWR flags are allowed to be set.
 * @heap_flags: flags passed to heap(currently not allowed)
 *
 * provided by userspace as an argument to the ioctl
*/

struct sheap_alloc_data {
	__u64 len;
	__u32 fd;
	__u32 fd_flags;
	__u64 heap_flags;
};

/**
 * struct sheap_attach_data - metadata passed from userspace for
 * 								get phy addr of dma buf.
 * @fd:			file descriptor handle to the allocated dma-buf.
 * @paddr:		sg dma address(physical address) of dma-buf.
*/

struct sheap_attach_data {
	__u32 fd;
	__u64 paddr;
};

#define SHEAP_IOC_MAGIC 's'

/**
 * SHEAP_IOCTL_ALLOC - allocate secure dma-buf from protected pool.
 *
 * This IOCTL command performs secure dma-buf memory allocation on sheap device.
 * uses the _IOWR macro to specify the read/write nature of the command.
 *
 * Takes a sheap_alloc_data struct and returns it with the fd field
 * populated with the dmabuf handle of the allocation.
 */
#define SHEAP_IOCTL_ALLOC _IOWR(SHEAP_IOC_MAGIC, 0, struct sheap_alloc_data)

/**
 * SHEAP_IOCTL_ATTACH - import secure dma-buf to get the phy address.
 *
 * This IOCTL command performs secure dma-buf attachment to get phy address.
 * uses the _IOWR macro to specify the read/write nature of the command.
 *
 * Takes a dma-buf fd in sheap_attach_data struct and
 * returns it with the phy addr from imported dma-buf handle.
 */
#define SHEAP_IOCTL_ATTACH _IOWR(SHEAP_IOC_MAGIC, 1, struct sheap_attach_data)

#endif /* _SHEAP_KAPI_H_ */