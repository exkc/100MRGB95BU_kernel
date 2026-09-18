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
 *  util function for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-03-28
 *  @note		Additional information.
 */

#include <linux/ctype.h>
#include <asm/cacheflush.h>
#include <linux/dma-mapping.h>
#include <linux/file.h>
#include <linux/time.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
#include <linux/kernel_read_file.h>
#include <asm/cacheflush.h>
#endif
#include "os_util.h"
#include "te_impl.h"

#define STR_BUF_SIZE	32
#define NUM_STR_BUF	4

static DEFINE_SPINLOCK(util_lock);

static char *get_str_buf(void)
{
	static char str_buf[NUM_STR_BUF][STR_BUF_SIZE];
	static int str_buf_idx;
	char *str;
	unsigned long flags;

	spin_lock_irqsave(&util_lock, flags);
	str = str_buf[str_buf_idx];
	if (++str_buf_idx >= NUM_STR_BUF)
		str_buf_idx = 0;
	spin_unlock_irqrestore(&util_lock, flags);

	return str;
}

u32 te_parse_size(const char *ptr)
{
	char *endptr;
	u32 ret = simple_strtoul(ptr, &endptr, 0);

	switch (*endptr) {
	case 'M':
	case 'm':
		ret <<= 20;
		break;
	case 'K':
	case 'k':
		ret <<= 10;
		break;

	default:
		break;
	}

	return ret;
}

char *te_get_readable_size_r(u32 size, char *buf, int max)
{
	int i = 0;
	u32 remained = 0;
	const char *units[] = { "B", "KB", "MB", "GB" };

	while (size >= 1024) {
		remained = size % 1024;
		size /= 1024;
		i++;
	}
	remained = remained * 1000 / 1024;

	if (remained)
		snprintf(buf, max, "%u.%03u%s", size, remained, units[i]);
	else
		snprintf(buf, max, "%u%s", size, units[i]);

	return buf;
}

char *te_get_readable_size(u32 size)
{
	char *s = get_str_buf();

	return te_get_readable_size_r(size, s, STR_BUF_SIZE);
}

char *te_get_readable_bitrate_r(u32 pkt_count, u32 pkt_len, u32 elapsed,
				char *buf, int buf_len)
{
	u32 data_xfer;
	u32 speed_hi, speed_lo;

	if (elapsed == 0 || pkt_len == 0) {
		snprintf(buf, buf_len, "N/A");
		return buf;
	}

	/*
	   bit rate(Kbit/s) = pkt_count * pkt_len * 8 * 1000 / 1024 / elapsed_ms
	   = pkt_count * pkt_len * 125 / 16 / elased_ms
	 */

	/* consider the floating overflow */
	if (pkt_count >= (0xFFFFFFFF / pkt_len / 125))
		data_xfer = (pkt_count * pkt_len) / 16 * 125 / elapsed;
	else
		data_xfer = pkt_count * pkt_len * 125 / 16 / elapsed;

	speed_hi = data_xfer / 1024;
	speed_lo = (data_xfer % 1024) * 1000 / 1024;

	snprintf(buf, buf_len, "%2u.%03uMbit/s", speed_hi, speed_lo);

	return buf;
}

char *te_get_readable_bitrate(u32 pkt_count, u32 pkt_len, u32 elapsed /* ms */ )
{
	char *s = get_str_buf();

	return te_get_readable_bitrate_r(pkt_count, pkt_len, elapsed, s,
					 STR_BUF_SIZE);
}

void te_hex_dump(const void *data, u32 size, u8 width)
{
#define LINE_BUF_LEN	512
#define HEX_DUMP_PRINT(fmt, args...) \
	pos += snprintf(line + pos, LINE_BUF_LEN - pos, fmt, ##args)

	int idx, len, pos;
	char *line;
	u32 addr = 0;
	const u8 *ptr = data;
	int count = size;

	if (width != 1 && width != 2 && width != 4)
		width = 1;

	line = kmalloc(LINE_BUF_LEN, GFP_KERNEL);
	if (!line)
		return;

	while (count > 0) {
		pos = 0;
		HEX_DUMP_PRINT("%04x:", addr);

		len = (count > 16) ? 16 : count;
		idx = 0;
		while (idx < len) {
			if (width == 4)
				HEX_DUMP_PRINT(" %08x", TE_GET32(ptr + idx));
			else if (width == 2)
				HEX_DUMP_PRINT(" %04x", TE_GET16(ptr + idx));
			else if (width == 1)
				HEX_DUMP_PRINT(" %02x", *(ptr + idx));
			idx += width;
		}

		/* add spaces */
		while (idx < 16) {
			if (width == 4)
				HEX_DUMP_PRINT("%9s", "");
			else if (width == 2)
				HEX_DUMP_PRINT("%5s", "");
			else if (width == 1)
				HEX_DUMP_PRINT("%3s", "");
			idx += width;
		}

		HEX_DUMP_PRINT("    ");
		for (idx = 0; idx < len; idx++) {
			if (isascii(ptr[idx]) && isprint(ptr[idx]))
				line[pos++] = ptr[idx];
			else
				line[pos++] = '.';
		}
		line[pos] = 0;	/* NULL termination */

		log_noti("%s\n", line);

		ptr += len;
		addr += len;

		count -= len;
	}
	kfree(line);
}

const char *te_find_match_string(const struct te_val_str *list, int count,
				 u32 val, const char *invalid)
{
	while (count--) {
		if (list->val == val)
			return list->str;
		list++;
	}

	return invalid;
}

u32 te_find_match_value(const struct te_val_str *list, int count,
			const char *str, u32 invalid)
{
	while (count--) {
		if (!strcasecmp(str, list->str))
			return list->val;
		list++;
	}

	return invalid;
}

u32 te_convert_to_type1(const struct te_type_conv *list, u32 len, u32 v,
			u32 invalid)
{
	int i;
	const struct te_type_conv *l = list;

	for (i = 0; i < len; i++) {
		if (l->type0 == v)
			return l->type1;
		l++;
	}

	return invalid;
}

u32 te_convert_to_type0(const struct te_type_conv *list, u32 len, u32 v,
			u32 invalid)
{
	int i;
	const struct te_type_conv *l = list;

	for (i = 0; i < len; i++) {
		if (l->type1 == v)
			return l->type0;
		l++;
	}

	return invalid;
}


u64 te_get_ms_tick(void)
{
	ktime_t t = ktime_get();
	return (u64)ktime_to_ms(t);
}

u64 te_get_us_tick(void)
{
	ktime_t t = ktime_get();
	return (u64)ktime_to_us(t);
}

/** memory functions **/

void *te_vmap(phys_addr_t addr, size_t size, bool cacheable)
{
	if (cacheable)
		return vmap_phys_cache(addr, size);
	else
		return vmap_phys(addr, size);
}

void te_vunmap(void *addr)
{
	vunmap_phys(addr);
}

static inline void __cache_inval(phys_addr_t paddr, void *vaddr, size_t size)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
	unsigned long start;

	start = (unsigned long)vaddr;

	dcache_inval_poc(start, start + size);
#else

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,3)
	__dma_map_area(vaddr, size, DMA_FROM_DEVICE);
#else
	dmac_map_area(vaddr, size, DMA_FROM_DEVICE);
#endif

#ifndef __aarch64__
	outer_inv_range(paddr, paddr + size);
#endif

#endif // KERNEL 6.11
}

static inline void __cache_clean(phys_addr_t paddr, void *vaddr, size_t size)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
	unsigned long start;

	start = (unsigned long)vaddr;

	dcache_clean_poc(start, start + size);
#else

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,3)
	__dma_map_area(vaddr, size, DMA_TO_DEVICE);
#else
	dmac_map_area(vaddr, size, DMA_TO_DEVICE);
#endif

#ifndef __aarch64__
	outer_clean_range(paddr, paddr + size);
#endif

#endif // KERNEL 6.11
}

static inline void __cache_flush(phys_addr_t paddr, void *vaddr, size_t size)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
	unsigned long start;

	start = (unsigned long)vaddr;

	dcache_clean_inval_poc(start, start + size);
#else

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	__dma_flush_area(vaddr, size);
#else
	__dma_flush_range(vaddr, vaddr + size);
#endif

#ifndef __aarch64__
	outer_flush_range(paddr, paddr + size);
#endif
#endif // KERNEL 6.11
}

int te_cache_sync(phys_addr_t paddr, void *vaddr, size_t size,
		  enum te_data_direction dir)
{
	log_info(TE_COLOR_GREEN "cache_sync: %pa(%p)++%zd, dir=%d"
		 TE_COLOR_NONE, &paddr, vaddr, size, dir);

	if (dir == TE_DATA_TO_DEVICE)
		__cache_clean(paddr, vaddr, size);
	else if (dir == TE_DATA_FROM_DEVICE)
		__cache_inval(paddr, vaddr, size);
	else
		__cache_flush(paddr, vaddr, size);

	return 0;
}

/**
 * te_cache_map_init - Initialize struct te_cache_map
 *
 * Return: 0 on success, -ENOMEM if vmap failed
 */
int te_cache_map_init(struct te_cache_map *map, phys_addr_t addr, size_t size)
{
	map->paddr = addr;
	map->size = size;
	map->vaddr = te_vmap(addr, size, true);

	return map->vaddr ? 0 : -ENOMEM;
}

void te_cache_map_release(struct te_cache_map *map)
{
	te_vunmap(map->vaddr);
}

int te_cache_map_sync(struct te_cache_map *map, off_t offset, size_t size,
		      enum te_data_direction dir)
{
	uintptr_t vaddr;
	phys_addr_t paddr;

	if (offset >= map->size || (offset + size) > map->size) {
		log_error("invalid param : offset(%lx) size(%zx)\n", offset,
			  size);
		return -EINVAL;
	}

	vaddr = (uintptr_t)map->vaddr + offset;
	paddr = map->paddr + offset;

	te_cache_sync(paddr, (void *)vaddr, size, dir);

	return 0;
}

int te_user_mmap(struct vm_area_struct *vma, bool uncached)
{
	struct te_mem_region_info *info;
	unsigned long paddr = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long size = vma->vm_end - vma->vm_start;

	log_info("range:%08lx++%lx, paddr:%08lx, flags:%lx, uncached:%d\n",
		 vma->vm_start, size, paddr, vma->vm_flags, uncached);

	info = te_get_mem_region_info(TE_MEM_TOTAL);
	if ((paddr < info->addr) ||
	    (paddr + size) > (info->addr + info->size)) {
		log_error("invalid addrees range(%08lx++%lx)", paddr, size);
		return -ENXIO;
	}

	//to prevent swapout
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0))
	vm_flags_set (vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
#elif (LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0))
	vma->vm_flags |= VM_RESERVED;
#else
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
#endif

	if (uncached) {
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}

	return remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size,
			       vma->vm_page_prot);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static int legacy_read_file_from_path(const char *path, void **buf,
				      size_t max_size)
{
	int ret;
	struct file *f;
	loff_t i_size, pos;
	char *data;

	/*
	 * Refer to fw_get_filesystem_firmware in drivers/base/firmware_class.c
	 * and use kernel_read_file_from_path from kernel 4.6
	 */
	f = filp_open(path, O_RDONLY, 0);
	if (IS_ERR(f)) {
		log_error("Can't open file '%s'\n", path);
		return PTR_ERR(f);
	}

	i_size = i_size_read(file_inode(f));
	if (i_size <= 0) {
		log_error("Can't get file size(%lld)\n", i_size);
		ret = -EINVAL;
		goto err_size;
	}

	if (max_size > 0 && i_size > max_size) {
		log_error("Filesize(%lld) over max_size(%zu)\n",
			  i_size, max_size);
		ret = -EFBIG;
		goto err_size;
	}

	data = vmalloc(i_size + 1);
	if (!data) {
		ret = -ENOMEM;
		goto err_malloc;
	}

	pos = 0;
	while (pos < i_size) {
		ret = kernel_read(f, pos, data + pos, i_size - pos);
		if (ret < 0)
			goto err_read;

		if (ret == 0)
			break;

		pos += ret;
	}

	if (pos != i_size) {
		ret = -EIO;
		goto err_read;
	}
	data[i_size] = 0;	/* add NULL ternmination for string parsing */

	fput(f);

	*buf = data;

	return pos;

err_read:
	vfree(data);
err_malloc:
err_size:
	fput(f);

	return ret;
}
#endif

/**
 * te_read_file_from_path - Read file from path
 * @path: file path to read file
 * @buf: allocated memory using vmalloc
 * @max_size: max size to be loaded
 * @is_fw: the binary is firmware or not
 *
 * NOTE: vfree must be called after using it
 *
 * Return: length of bytes read if succeed or negative integer on error.
 */
int te_read_file_from_path(const char *path, void **buf, size_t max_size)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
	size_t size;
	enum kernel_read_file_id id = READING_UNKNOWN;

	size = kernel_read_file_from_path(path, 0, buf, max_size, NULL, id);
	if (size < 0) {
		log_error("%s read failed - %zu", path, size);
		return size;
	}

	return size;
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	loff_t size;
	int rc;
	enum kernel_read_file_id id = READING_UNKNOWN;

	rc = kernel_read_file_from_path(path, buf, &size, max_size, id);
	if (rc < 0) {
		log_error("%s read failed - %d", path, rc);
		return rc;
	}

	return size;
#else
	return legacy_read_file_from_path(path, buf, max_size);
#endif //KERNEL < 5.4.0
}

/**
 * te_tick_to_time - Convert tick to @struct te_time
 *
 * It makes @struct te_time using @freq based tick value
 */
int te_tick_to_time(u64 tick, u32 freq, enum te_time_epoch mode,
		    struct te_time *time)
{
	u64 v;
	s64 sec;
	struct tm tm;

	if (!freq)
		return -EINVAL;

	v = do_div(tick, freq);
	if (v) {
		v = v * 1000;
		do_div(v, freq);
	}
	time->msec = v;

	// Now tick is a total seconds
	if (mode == NTP_EPOCH_TIME)
		sec = (s64)tick - 2208988800UL;
	else
		sec = tick;

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,8,0)
	time_to_tm(sec, 0, &tm);
#else
	time64_to_tm(sec, 0, &tm);
#endif

	time->year = tm.tm_year + 1900;
	time->mon = tm.tm_mon + 1;
	time->day = tm.tm_mday;
	time->hour = tm.tm_hour;
	time->min = tm.tm_min;
	time->sec = tm.tm_sec;

	return 0;
}

/**
 * te_time_to_tick - Convert @struct te_time to tick
 *
 * Return: 0 on success,
 * -EIVAL if epoch is NTP_EPOCH_TIME and year is under 1900 or
 * epoch is UNIX_EPOCH_TIME and year is under 1970
 */
int te_time_to_tick(struct te_time *time, u32 freq, enum te_time_epoch mode,
		    u64 *tick)
{
	time64_t t;

	if (!freq)
		return -EINVAL;

	if (mode == NTP_EPOCH_TIME) {
		if (time->year < 1900)
			return -EINVAL;
	} else {
		if (time->year < 1970)
			return -EINVAL;
	}

	t = mktime64(time->year, time->mon, time->day,
		     time->hour, time->min, time->sec);

	if (mode == NTP_EPOCH_TIME)
		t += 2208988800UL;

	*tick = t * freq;
	if (time->msec) {
		*tick += ((u64)time->msec * freq / 1000);
	}

	return 0;
}

char *te_get_readable_time_r(struct te_time *time, char *buf, int max)
{
	/* FORMAT => 2019-03-20 16:36:12.032 */
	snprintf(buf, max, "%d-%02d-%02d %02d:%02d:%02d.%03d",
		 time->year, time->mon, time->day,
		 time->hour, time->min, time->sec, time->msec);

	return buf;
}

char *te_get_readable_time(struct te_time *time)
{
	char *s = get_str_buf();

	return te_get_readable_time_r(time, s, STR_BUF_SIZE);
}
