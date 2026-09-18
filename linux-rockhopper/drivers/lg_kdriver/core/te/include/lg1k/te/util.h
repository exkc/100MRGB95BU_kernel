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

#ifndef	_LG1K_TE_UTIL_H_
#define	_LG1K_TE_UTIL_H_

#include <linux/types.h>
#include <linux/mm.h>
#include <asm/div64.h>

// DO NOT INCLUDE OTHERS EXCLUDE LINUX KERNEL HEADERS

#define TE_COLOR_NONE		"\x1b[0m"
#define TE_COLOR_RED		"\x1b[1;31m"
#define TE_COLOR_GREEN		"\x1b[1;32m"
#define TE_COLOR_YELLLOW	"\x1b[1;33m"
#define TE_COLOR_YELLOW		"\x1b[1;33m"
#define TE_COLOR_BLUE		"\x1b[1;34m"
#define TE_COLOR_PURPLE		"\x1b[1;35m"
#define TE_COLOR_CYAN		"\x1b[1;36m"

struct te_val_str {
	u32 val;
	const char *str;
};

struct te_type_conv {
	u32 type0;
	u32 type1;
};

u32 te_parse_size(const char *ptr);

char *te_get_readable_size_r(u32 size, char *buf, int max);
char *te_get_readable_size(u32 size);

/* elapsed = ms unit */
char *te_get_readable_bitrate_r(u32 pkt_count, u32 pkt_len, u32 elapsed,
				char *buf, int buf_len);
char *te_get_readable_bitrate(u32 pkt_count, u32 pkt_len, u32 elapsed);

#define get_bitrate_str(count, len, elapsed) \
	te_get_readable_bitrate(count, len, elapsed)

void te_hex_dump(const void *data, u32 size, u8 width);

#define te_dump_stack()	dump_stack()

/*
 * get string from type or type from string
 */
const char *te_find_match_string(const struct te_val_str *list, int len,
				 u32 val, const char *invalid);

#define find_match_string(list, val, invalid) \
	te_find_match_string(list, ARRAY_SIZE(list), val, invalid)

u32 te_find_match_value(const struct te_val_str *list, int len,
			const char *str, u32 invalid);

#define find_match_value(list, str, invalid) \
	te_find_match_value(list, ARRAY_SIZE(list), str, invalid)

/*
 * type conversion
 */
u32 te_convert_to_type1(const struct te_type_conv *list, u32 len, u32 v,
			u32 invalid);
u32 te_convert_to_type0(const struct te_type_conv *list, u32 len, u32 v,
			u32 invalid);

#define convert_to_type1(list, val, invalid) \
	te_convert_to_type1(list, ARRAY_SIZE(list), val, invalid)

#define convert_to_type0(list, val, invalid) \
	te_convert_to_type0(list, ARRAY_SIZE(list), val, invalid)

/*
 * system functions
 */
enum te_time_epoch {
	UNIX_EPOCH_TIME = 0,	/* From 1970 */
	NTP_EPOCH_TIME,		/* From 1900 */
};

struct te_time {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
	int msec;
};

u64 te_get_ms_tick(void);
u64 te_get_us_tick(void);

int te_tick_to_time(u64 value, u32 freq, enum te_time_epoch mode,
		    struct te_time *time);
int te_time_to_tick(struct te_time *time, u32 freq, enum te_time_epoch mode,
		    u64 *tick);
char *te_get_readable_time_r(struct te_time *time, char *buf, int max);
char *te_get_readable_time(struct te_time *time);

/*
 * memory functions
 */
struct te_cache_map {
	phys_addr_t paddr;
	void *vaddr;
	size_t size;
};

enum te_data_direction {
	TE_DATA_BIDIRECTION = 0,	// flush
	TE_DATA_TO_DEVICE,		// clean
	TE_DATA_FROM_DEVICE,		// invalidate
};

void *te_vmap(phys_addr_t addr, size_t size, bool cacheable);
void te_vunmap(void *addr);

int te_cache_sync(phys_addr_t paddr, void *vaddr, size_t size,
		  enum te_data_direction dir);

int te_cache_map_init(struct te_cache_map *map, phys_addr_t addr, size_t size);
void te_cache_map_release(struct te_cache_map *map);
int te_cache_map_sync(struct te_cache_map *map, off_t offset, size_t size,
		      enum te_data_direction dir);

int te_user_mmap(struct vm_area_struct *vma, bool uncached);

/*
 * file access functions
 */
int te_read_file_from_path(const char *path, void **buf, size_t max_size);

/*
 * miscellaneous functions
 */
typedef __printf(2, 3)
void (*printf_func_t)(void *arg, const char *fmt, ...);

#if BITS_PER_LONG == 64
#define te_div64(n, div) (((div) == 0) ? 0 : ((n) / (div)))
#else
static inline __attribute__((const)) u64 __div_u64_32(u64 n, u32 div)
{
	do_div(n, div);
	return n;
}

static inline __attribute__((const)) s64 __div_s64_32(s64 n, u32 div)
{
	if (n < 0) {
		u64 s = -n;
		do_div(s, div);
		n = -s;
	} else {
		do_div(n, div);
	}

	return n;
}

#define __div(n, div) ((n) / (div))

#define te_div64(n, div)                                          \
	((__builtin_constant_p(n) && __builtin_constant_p(div)) ? \
		 __div(n, div) :                                  \
		 (__builtin_types_compatible_p(typeof(n), u32) || \
		  __builtin_types_compatible_p(typeof(n), s32)) ? \
		 __div(n, div) :                                  \
		 __builtin_types_compatible_p(typeof(n), u64) ?   \
		 __div_u64_32(n, div) :                           \
		 __div_s64_32(n, div))
#endif

static inline u32 te_get32(const void *p)
{
	u8 *ptr = (u8 *) p;
	return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3] << 0;
}

static inline u32 te_get24(const void *p)
{
	u8 *ptr = (u8 *) p;
	return ptr[0] << 16 | ptr[1] << 8 | ptr[2] << 0;
}

static inline u32 te_get16(const void *p)
{
	u8 *ptr = (u8 *) p;
	return ptr[0] << 8 | ptr[1] << 0;
}

static inline u64 te_get64(const void *p)
{
	u8 *ptr = (u8 *) p;
	return (u64)te_get32(ptr) << 32 | te_get32(&ptr[4]);
}

static inline void te_put32(const void *p, u32 val)
{
	u8 *ptr = (u8 *) p;
	ptr[0] = (val >> 24) & 0xFF;
	ptr[1] = (val >> 16) & 0xFF;
	ptr[2] = (val >> 8) & 0xFF;
	ptr[3] = (val >> 0) & 0xFF;
}

static inline void te_put16(const void *p, u16 v)
{
	u8 *ptr = (u8 *) p;

	ptr[0] = (v >> 8) & 0xFF;
	ptr[1] = (v >> 0) & 0xFF;
}

static inline u32 te_swap32(u32 val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
	return (val << 16) | (val >> 16);
}

static inline u16 te_swap16(u16 val)
{
	return (val << 8) | (val >> 8);
}

static inline u32 te_get_aligned_size(u32 size, u32 align)
{
	return size - (size % align);
}


/*
 * pcap functions
 */
#define TE_PCAP_MAGIC		0xa1b2c3d4
#define TE_PCAP_VER_MAJOR	2
#define TE_PCAP_VER_MINOR	4

#define TE_PCAP_LINKTYPE_ETHERNET	1
#define TE_PCAP_LINKTYPE_PREDEF0	150 // User predefined number 150 ~
#define TE_PCAP_LINKTYPE_IPV4		228
#define TE_PCAP_LINKTYPE_CA		235

struct te_pcap_hdr {
	u32 magic_number;
	u16 version_major;
	u16 version_minor;
	s32 thiszone;
	u32 sigfigs;
	u32 snaplen;
	u32 network;
};

struct te_pcap_rec_hdr {
	u32 ts_sec;
	u32 ts_usec;
	u32 incl_len;
	u32 orig_len;
};

#endif				/* _LG1K_TE_UTIL_H_ */
