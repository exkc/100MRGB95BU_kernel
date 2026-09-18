
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

struct dma_buf_te_ioctl_alloc {
	unsigned long long size; /* size of buffer to allocate, in pages */
};

struct dma_buf_te_ioctl_alloc2 {
	unsigned long long size; /* size of buffer to allocate, in pages */

	unsigned long long modifier;
	unsigned int fourcc;
	unsigned int width;
	unsigned int height;
};

#define DMA_BUF_TE_IOCTL_BASE 'E'
#define DMA_BUF_TE_ALLOC _IOR(DMA_BUF_TE_IOCTL_BASE, 0x01, struct dma_buf_te_ioctl_alloc)
#define DMA_BUF_TE_ALLOC2 _IOR(DMA_BUF_TE_IOCTL_BASE, 0x01, struct dma_buf_te_ioctl_alloc2)

static int te = -1;

int alloc(unsigned long long size)
{
	if (te < 0)
		te = open("/dev/dma_buf_te", O_RDWR);
	assert(te >= 0);

	unsigned long long nr_pages = size >> 12;
	int dmabuf = ioctl(te, DMA_BUF_TE_ALLOC, &nr_pages);
	assert(dmabuf >= 0);

	off_t offs = lseek(dmabuf, 0, SEEK_END);
	assert(offs == size);

	return dmabuf;
}

int alloc2(unsigned long long size)
{
	struct dma_buf_te_ioctl_alloc2 param;
	memset(&param, 0, sizeof(param));
	param.size = size >> 12;

	if (te < 0)
		te = open("/dev/dma_buf_te", O_RDWR);
	assert(te >= 0);

	int dmabuf = ioctl(te, DMA_BUF_TE_ALLOC2, &param);
	assert(dmabuf >= 0);

	off_t offs = lseek(dmabuf, 0, SEEK_END);
	assert(offs == size);

	return dmabuf;
}

int main(int argc, char **argv)
{
	alloc(1024*1024);
	alloc(2*1024*1024);
	alloc2(2*1024*1024);

	return 0;
}

