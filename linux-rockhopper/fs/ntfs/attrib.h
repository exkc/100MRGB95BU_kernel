/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Defines for attribute handling in NTFS Linux kernel driver.
 * Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 * Copyright (c) 2002 Richard Russon
 */

#ifndef _LINUX_NTFS_ATTRIB_H
#define _LINUX_NTFS_ATTRIB_H

#include "endian.h"
#include "dir.h"

extern ntfschar AT_UNNAMED[];

/**
 * ntfs_attr_search_ctx - used in attribute search functions
 * @mrec:	buffer containing mft record to search
 * @attr:	attribute record in @mrec where to begin/continue search
 * @is_first:	if true ntfs_attr_lookup() begins search with @attr, else after
 *
 * Structure must be initialized to zero before the first call to one of the
 * attribute search functions. Initialize @mrec to point to the mft record to
 * search, and @attr to point to the first attribute within @mrec (not necessary
 * if calling the _first() functions), and set @is_first to 'true' (not necessary
 * if calling the _first() functions).
 *
 * If @is_first is 'true', the search begins with @attr. If @is_first is 'false',
 * the search begins after @attr. This is so that, after the first call to one
 * of the search attribute functions, we can call the function again, without
 * any modification of the search context, to automagically get the next
 * matching attribute.
 */
typedef struct {
	MFT_RECORD *mrec;
	bool mapped_mrec;
	ATTR_RECORD *attr;
	bool is_first;
	ntfs_inode *ntfs_ino;
	ATTR_LIST_ENTRY *al_entry;
	ntfs_inode *base_ntfs_ino;
	MFT_RECORD *base_mrec;
	bool mapped_base_mrec;
	ATTR_RECORD *base_attr;
} ntfs_attr_search_ctx;

typedef enum {                  /* ways of processing holes when expanding */
	HOLES_NO,
	HOLES_OK,
	HOLES_DELAY
} hole_type;

extern int ntfs_map_runlist_nolock(ntfs_inode *ni, VCN vcn,
		ntfs_attr_search_ctx *ctx);
extern int ntfs_map_runlist(ntfs_inode *ni, VCN vcn);

extern LCN ntfs_attr_vcn_to_lcn_nolock(ntfs_inode *ni, const VCN vcn,
		const bool write_locked);

extern runlist_element *ntfs_attr_find_vcn_nolock(ntfs_inode *ni,
		const VCN vcn, ntfs_attr_search_ctx *ctx);
extern runlist_element *__ntfs_attr_find_vcn_nolock(runlist *runlist,
						     const VCN vcn);
extern int ntfs_attr_map_whole_runlist(ntfs_inode *ni);

int ntfs_attr_lookup(const ATTR_TYPE type, const ntfschar *name,
		const u32 name_len, const IGNORE_CASE_BOOL ic,
		const VCN lowest_vcn, const u8 *val, const u32 val_len,
		ntfs_attr_search_ctx *ctx);

extern int load_attribute_list(ntfs_inode *base_ni,
			       u8 *al_start, const s64 size);

static inline s64 ntfs_attr_size(const ATTR_RECORD *a)
{
	if (!a->non_resident)
		return (s64)le32_to_cpu(a->data.resident.value_length);
	return sle64_to_cpu(a->data.non_resident.data_size);
}

extern void ntfs_attr_reinit_search_ctx(ntfs_attr_search_ctx *ctx);
extern ntfs_attr_search_ctx *ntfs_attr_get_search_ctx(ntfs_inode *ni,
		MFT_RECORD *mrec);
extern void ntfs_attr_put_search_ctx(ntfs_attr_search_ctx *ctx);

extern int ntfs_attr_size_bounds_check(const ntfs_volume *vol,
		const ATTR_TYPE type, const s64 size);
extern int ntfs_attr_can_be_non_resident(const ntfs_volume *vol,
		const ATTR_TYPE type);
extern int ntfs_attr_can_be_resident(const ntfs_volume *vol,
		const ATTR_TYPE type);
extern int ntfs_attr_map_cluster(ntfs_inode *ni, VCN vcn_start, LCN *lcn_start,
		LCN *lcn_count, VCN max_clu_count, bool *balloc, bool update_mp);
extern int ntfs_attr_record_resize(MFT_RECORD *m, ATTR_RECORD *a, u32 new_size);
extern int ntfs_resident_attr_value_resize(MFT_RECORD *m, ATTR_RECORD *a,
		const u32 new_size);

extern int ntfs_attr_make_non_resident(ntfs_inode *ni, const u32 data_size);

extern int ntfs_attr_set(ntfs_inode *ni, const s64 ofs, const s64 cnt,
		const u8 val);
extern int ntfs_attr_set_initialized_size(ntfs_inode *ni, loff_t new_size);
int ntfs_attr_open(ntfs_inode *ni, const ATTR_TYPE type,
		ntfschar *name, u32 name_len);
void ntfs_attr_close(ntfs_inode *n);
int ntfs_attr_fallocate(ntfs_inode *ni, loff_t start, loff_t byte_len, bool keep_size);
int ntfs_non_resident_attr_insert_range(ntfs_inode *ni, VCN start_vcn, VCN len);
int ntfs_non_resident_attr_collapse_range(ntfs_inode *ni, VCN start_vcn, VCN len);
int ntfs_non_resident_attr_punch_hole(ntfs_inode *ni, VCN start_vcn, VCN len);
int __ntfs_attr_truncate_vfs(ntfs_inode *ni, const s64 newsize,
		const s64 i_size);
int ntfs_attr_expand(ntfs_inode *ni, const s64 newsize, const s64 prealloc_size);
int ntfs_attr_truncate_i(ntfs_inode *ni, const s64 newsize, hole_type holes);
int ntfs_attr_truncate(ntfs_inode *ni, const s64 newsize);
int ntfs_attr_rm(ntfs_inode *ni);
int ntfs_attr_exist(ntfs_inode *ni, const ATTR_TYPE type, ntfschar *name,
		u32 name_len);
int ntfs_attr_remove(ntfs_inode *ni, const ATTR_TYPE type, ntfschar *name,
		u32 name_len);
int ntfs_attr_record_rm(ntfs_attr_search_ctx *ctx);
int ntfs_attr_record_move_to(ntfs_attr_search_ctx *ctx, ntfs_inode *ni);
int ntfs_attr_add(ntfs_inode *ni, ATTR_TYPE type,
		ntfschar *name, u8 name_len, u8 *val, s64 size);
int ntfs_attr_record_move_away(ntfs_attr_search_ctx *ctx, int extra);
char *ntfs_attr_name_get(const ntfs_volume *vol, const ntfschar *uname,
		const int uname_len);
void ntfs_attr_name_free(unsigned char **name);
void *ntfs_attr_readall(ntfs_inode *ni, const ATTR_TYPE type,
		ntfschar *name, u32 name_len, s64 *data_size);
int ntfs_resident_attr_record_add(ntfs_inode *ni, ATTR_TYPE type,
		ntfschar *name, u8 name_len, u8 *val, u32 size,
		ATTR_FLAGS flags);
int ntfs_attr_update_mapping_pairs(ntfs_inode *ni, VCN from_vcn);
runlist_element *ntfs_attr_vcn_to_rl(ntfs_inode *ni, VCN vcn, LCN *lcn);

/**
 * ntfs_attrs_walk - syntactic sugar for walking all attributes in an inode
 * @ctx:	initialised attribute search context
 *
 * Syntactic sugar for walking attributes in an inode.
 *
 * Return 0 on success and -1 on error with errno set to the error code from
 * ntfs_attr_lookup().
 *
 * Example: When you want to enumerate all attributes in an open ntfs inode
 *	    @ni, you can simply do:
 *
 *	int err;
 *	ntfs_attr_search_ctx *ctx = ntfs_attr_get_search_ctx(ni, NULL);
 *	if (!ctx)
 *		// Error code is in errno. Handle this case.
 *	while (!(err = ntfs_attrs_walk(ctx))) {
 *		ATTR_RECORD *attr = ctx->attr;
 *		// attr now contains the next attribute. Do whatever you want
 *		// with it and then just continue with the while loop.
 *	}
 *	if (err && errno != ENOENT)
 *		// Ooops. An error occurred! You should handle this case.
 *	// Now finished with all attributes in the inode.
 */
static __inline__ int ntfs_attrs_walk(ntfs_attr_search_ctx *ctx)
{
	return ntfs_attr_lookup(AT_UNUSED, NULL, 0, CASE_SENSITIVE, 0,
			NULL, 0, ctx);
}
#endif /* _LINUX_NTFS_ATTRIB_H */
