/*
 *
 * (C) COPYRIGHT LGE. All rights reserved.
 *
 */




#ifndef _LINUX_DMA_BUF_UNIFIED_H_
#define _LINUX_DMA_BUF_UNIFIED_H_

#include <linux/types.h>
#include <asm/ioctl.h>

#define DMA_BUF_UNIFIED_VER_MAJOR 1
#define DMA_BUF_UNIFIED_VER_MINOR 0

#define	DMA_UNIFIED_UNCACHED	0
#define	DMA_UNIFIED_CACHED	1

int dma_buf_unified_info(int pid);

struct dma_buf_unified_ioctl_version
{
	int op;    /**< Must be set to DMA_BUF_UNIFIED_ENQ by client, driver will set it to DMA_BUF_UNIFIED_ACK */
	int major; /**< Major version */
	int minor; /**< Minor version */
};

struct dma_buf_unified_ioctl_alloc
{
	unsigned int size; /* size of buffer to allocate, in pages */
	unsigned int map_cached; /* 0: writecombined, 1: cached */
};

struct dma_buf_unified_ioctl_import
{
	unsigned int mem_type;
	unsigned int phys_addr;
	unsigned int size;	/* in pages */
	unsigned int ion_fd;
	unsigned int map_cached; /* 0: writecombined, 1: cached */
};

struct dma_buf_unified_ioctl_from_ion
{
	/* in */
	int ion_fd; /* ion fd */
};

struct dma_buf_unified_ioctl_status
{
	/* in */
	int fd; /* the dma_buf to query, only dma_buf objects exported by this driver is supported */
	/* out */
	int attached_devices; /* number of devices attached (active 'dma_buf_attach's) */
	int device_mappings; /* number of device mappings (active 'dma_buf_map_attachment's) */
	int cpu_mappings;    /* number of cpu mappings (active 'mmap's) */
};

struct dma_buf_unified_ioctl_set_failing
{
	/* in */
	int fd; /* the dma_buf to set failure mode for, only dma_buf objects exported by this driver is supported */

	/* zero = no fail injection, non-zero = inject failure */
	int fail_attach;
	int fail_map;
	int fail_mmap;
};

struct dma_buf_unified_ioctl_buffer_sync
{
	int fd;
	int direction;	// 0: CPU to dev, 1: dev to CPU
};

#define DMA_BUF_UNIFIED_IOCTL_BASE 'E'
/* Below all returning 0 if successful or -errcode except DMA_BUF_UNIFIED_ALLOC which will return fd or -errcode */
#define DMA_BUF_UNIFIED_VERSION         _IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x00, struct dma_buf_unified_ioctl_version)
#define DMA_BUF_UNIFIED_ALLOC           _IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x01, struct dma_buf_unified_ioctl_alloc)
#define DMA_BUF_UNIFIED_QUERY           _IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x02, struct dma_buf_unified_ioctl_status)
#define DMA_BUF_UNIFIED_SET_FAILING     _IOW(DMA_BUF_UNIFIED_IOCTL_BASE, 0x03, struct dma_buf_unified_ioctl_set_failing)
#define DMA_BUF_UNIFIED_ALLOC_CONT      _IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x04, struct dma_buf_unified_ioctl_alloc)
#define DMA_BUF_UNIFIED_IMPORT         _IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x06, struct dma_buf_unified_ioctl_import)
#define DMA_BUF_UNIFIED_FROM_ION        _IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x07, struct dma_buf_unified_ioctl_from_ion)
#define DMA_BUF_UNIFIED_SYNC		_IOR(DMA_BUF_UNIFIED_IOCTL_BASE, 0x08, struct dma_buf_unified_ioctl_buffer_sync)

struct dma_buf_uninfied_ioctl_valid
{
	int fd;
	unsigned int size;
	int owned;
};

#define DMA_BUF_UNIFIED_VALID  _IOWR(DMA_BUF_UNIFIED_IOCTL_BASE, 0xF0, \
                                     struct dma_buf_uninfied_ioctl_valid)

#endif /* _LINUX_DMA_BUF_UNIFIED_H_ */

