/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Defines for NTFS kernel index handling.  Part of the Linux-NTFS
 * project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 */

#ifndef _LINUX_NTFS_INDEX_H
#define _LINUX_NTFS_INDEX_H

#include <linux/fs.h>

#include "attrib.h"
#include "mft.h"
#include "aops.h"

#define  VCN_INDEX_ROOT_PARENT  ((VCN)-2)

#define MAX_PARENT_VCN	32

/**
 * @idx_ni:	index inode containing the @entry described by this context
 * @entry:	index entry (points into @ir or @ia)
 * @data:	index entry data (points into @entry)
 * @data_len:	length in bytes of @data
 * @is_in_root:	'true' if @entry is in @ir and 'false' if it is in @ia
 * @ir:		index root if @is_in_root and NULL otherwise
 * @actx:	attribute search context if @is_in_root and NULL otherwise
 * @base_ni:	base inode if @is_in_root and NULL otherwise
 * @ia:		index block if @is_in_root is 'false' and NULL otherwise
 * @page:	page if @is_in_root is 'false' and NULL otherwise
 *
 * @idx_ni is the index inode this context belongs to.
 *
 * @entry is the index entry described by this context.  @data and @data_len
 * are the index entry data and its length in bytes, respectively.  @data
 * simply points into @entry.  This is probably what the user is interested in.
 *
 * If @is_in_root is 'true', @entry is in the index root attribute @ir described
 * by the attribute search context @actx and the base inode @base_ni.  @ia and
 * @page are NULL in this case.
 *
 * If @is_in_root is 'false', @entry is in the index allocation attribute and @ia
 * and @page point to the index allocation block and the mapped, locked page it
 * is in, respectively.  @ir, @actx and @base_ni are NULL in this case.
 *
 * To obtain a context call ntfs_index_ctx_get().
 *
 * We use this context to allow ntfs_index_lookup() to return the found index
 * @entry and its @data without having to allocate a buffer and copy the @entry
 * and/or its @data into it.
 *
 * When finished with the @entry and its @data, call ntfs_index_ctx_put() to
 * free the context and other associated resources.
 *
 * If the index entry was modified, call flush_dcache_index_entry_page()
 * immediately after the modification and either ntfs_index_entry_mark_dirty()
 * or ntfs_index_entry_write() before the call to ntfs_index_ctx_put() to
 * ensure that the changes are written to disk.
 */
typedef struct {
	ntfs_inode *idx_ni;
	ntfschar *name;
	u32 name_len;
	INDEX_ENTRY *entry;
	COLLATION_RULE cr;
	void *data;
	u16 data_len;
	bool is_in_root;
	INDEX_ROOT *ir;
	ntfs_attr_search_ctx *actx;
	INDEX_BLOCK *ib;
	ntfs_inode *base_ni;
	INDEX_ALLOCATION *ia;
	struct page *page;
	ntfs_inode *ia_ni;
	int parent_pos[MAX_PARENT_VCN];  /* parent entries' positions */
	VCN parent_vcn[MAX_PARENT_VCN]; /* entry's parent nodes */
	int pindex;          /* maximum it's the number of the parent nodes  */
	bool ib_dirty;
	u32 block_size;
	u8 vcn_size_bits;
	bool sync_write;
} ntfs_index_context;

int ntfs_index_entry_inconsistent(ntfs_index_context *icx, ntfs_volume *vol,
		const INDEX_ENTRY *ie, COLLATION_RULE collation_rule, u64 inum);
//extern ntfs_index_context *ntfs_index_ctx_get(ntfs_inode *idx_ni);
ntfs_index_context *ntfs_index_ctx_get(ntfs_inode *ni, ntfschar *name,
		u32 name_len);
extern void ntfs_index_ctx_put(ntfs_index_context *ictx);

extern int ntfs_index_lookup(const void *key, const int key_len,
		ntfs_index_context *ictx);

/**
 * ntfs_index_entry_flush_dcache_page - flush_dcache_page() for index entries
 * @ictx:	ntfs index context describing the index entry
 *
 * Call flush_dcache_page() for the page in which an index entry resides.
 *
 * This must be called every time an index entry is modified, just after the
 * modification.
 *
 * If the index entry is in the index root attribute, simply flush the page
 * containing the mft record containing the index root attribute.
 *
 * If the index entry is in an index block belonging to the index allocation
 * attribute, simply flush the page cache page containing the index block.
 */
static inline void ntfs_index_entry_flush_dcache_page(ntfs_index_context *ictx)
{
	if (!ictx->is_in_root)
		flush_dcache_page(ictx->page);
}

void ntfs_index_entry_mark_dirty(ntfs_index_context *ictx);
int ntfs_index_add_filename(ntfs_inode *ni, FILE_NAME_ATTR *fn, MFT_REF mref);
int ntfs_index_remove(ntfs_inode *ni, const void *key, const int keylen);
ntfs_inode *ntfs_ia_open(ntfs_index_context *icx, ntfs_inode *ni);
INDEX_ENTRY *ntfs_index_walk_down(INDEX_ENTRY *ie, ntfs_index_context *ictx);
INDEX_ENTRY *ntfs_index_next(INDEX_ENTRY *ie, ntfs_index_context *ictx);
int ntfs_index_rm(ntfs_index_context *icx);
void ntfs_index_ctx_reinit(ntfs_index_context *icx);
int ntfs_ie_add(ntfs_index_context *icx, INDEX_ENTRY *ie);
int ntfs_icx_ib_sync_write(ntfs_index_context *icx);

#endif /* _LINUX_NTFS_INDEX_H */
