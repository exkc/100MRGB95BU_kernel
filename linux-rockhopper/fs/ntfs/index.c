// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * NTFS kernel index handling. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2004-2005 Anton Altaparmakov
 * Copyright (c) 2024 LG Electronics Co., Ltd.
 * Author(s): Namjae Jeon <linkinjeon@kernel.org>
 */

#include "collate.h"
#include "index.h"
#include "ntfs.h"
#include "malloc.h"
#include "attrlist.h"

/*
 * ntfs_index_entry_inconsistent - Check the consistency of an index entry
 *
 * Make sure data and key do not overflow from entry.
 * As a side effect, an entry with zero length is rejected.
 * This entry must be a full one (no INDEX_ENTRY_END flag), and its
 * length must have been checked beforehand to not overflow from the
 * index record.
 *
 * Returns 0 if no error was found.
 * error otherwise.
 */

int ntfs_index_entry_inconsistent(ntfs_index_context *icx, ntfs_volume *vol,
		const INDEX_ENTRY *ie, COLLATION_RULE collation_rule, u64 inum)
{
	if (icx) {
		INDEX_HEADER *ih;
		u8 *ie_start, *ie_end;

		if (icx->is_in_root)
			ih = &icx->ir->index;
		else
			ih = &icx->ib->index;

		if ((le32_to_cpu(ih->index_length) > le32_to_cpu(ih->allocated_size)) ||
				(le32_to_cpu(ih->index_length) > icx->block_size)) {
			ntfs_error(vol->sb, "%s Index entry(0x%p)'s length is too big.",
					icx->is_in_root ? "Index root" : "Index block",
					(u8 *)icx->entry);
			return -EINVAL;
		}

		ie_start = (u8 *)ih + le32_to_cpu(ih->entries_offset);
		ie_end = (u8 *)ih + le32_to_cpu(ih->index_length);

		if (ie_start > (u8 *)ie ||
		    ie_end <= ((u8 *)ie + ie->length) ||
		    ie->length > le32_to_cpu(ih->allocated_size) ||
		    ie->length > icx->block_size) {
			ntfs_error(vol->sb, "Index entry(0x%p) is out of range from %s",
					(u8 *)icx->entry,
					icx->is_in_root ? "index root" : "index block");
			return -EIO;
		}
	}

	if (ie->key_length &&
	    ((le16_to_cpu(ie->key_length) + offsetof(INDEX_ENTRY, key)) >
	     le16_to_cpu(ie->length))) {
		ntfs_error(vol->sb, "Overflow from index entry in inode %lld\n",
				(long long)inum);
		return -EIO;

	} else {
		if (collation_rule == COLLATION_FILE_NAME) {
			if ((offsetof(INDEX_ENTRY, key.file_name.file_name) +
			     ie->key.file_name.file_name_length	* sizeof(ntfschar)) >
					le16_to_cpu(ie->length)) {
				ntfs_error(vol->sb, "File name overflow from index"
						" entry in inode %lld\n",
						(long long)inum);
				return -EIO;
			}
		} else {
			if (ie->data.vi.data_length &&
			    ((le16_to_cpu(ie->data.vi.data_offset) + le16_to_cpu(ie->data.vi.data_length)) >
			     le16_to_cpu(ie->length))) {
				ntfs_error(vol->sb, "Data overflow from index"
						" entry in inode %lld\n",
						(long long)inum);
				return -EIO;
			}
		}
	}

	return 0;
}

/**
 * ntfs_index_entry_mark_dirty - mark an index entry dirty
 * @ictx:	ntfs index context describing the index entry
 *
 * Mark the index entry described by the index entry context @ictx dirty.
 *
 * If the index entry is in the index root attribute, simply mark the inode
 * containing the index root attribute dirty.  This ensures the mftrecord, and
 * hence the index root attribute, will be written out to disk later.
 *
 * If the index entry is in an index block belonging to the index allocation
 * attribute, set ib_dirty to true, thus index block will be updated during
 * ntfs_index_ctx_put.
 */
void ntfs_index_entry_mark_dirty(ntfs_index_context *ictx)
{
	if (ictx->is_in_root) {
		mark_mft_record_dirty(ictx->actx->ntfs_ino);
	} else if (ictx->ib)
		ictx->ib_dirty = true;
}

static s64 ntfs_ib_vcn_to_pos(ntfs_index_context *icx, VCN vcn)
{
	return vcn << icx->vcn_size_bits;
}

static VCN ntfs_ib_pos_to_vcn(ntfs_index_context *icx, s64 pos)
{
	return pos >> icx->vcn_size_bits;
}

static int ntfs_ib_write(ntfs_index_context *icx, INDEX_BLOCK *ib)
{
	s64 ret, vcn = sle64_to_cpu(ib->index_block_vcn);

	ntfs_debug("vcn: %lld\n", vcn);

	ret = pre_write_mst_fixup((NTFS_RECORD*)ib, icx->block_size);
	if (ret)
		return -EIO;

	ret = ntfs_inode_attr_pwrite(VFS_I(icx->ia_ni),
			ntfs_ib_vcn_to_pos(icx, vcn), icx->block_size,
			(u8 *)ib, icx->sync_write);
	if (ret != icx->block_size) {
		ntfs_error(icx->idx_ni->vol->sb, "Failed to write index block %lld, inode %llu",
				(long long)vcn, (unsigned long long)icx->idx_ni->mft_no);
		return ret;
	}

	return 0;
}

static int ntfs_icx_ib_write(ntfs_index_context *icx)
{
	int err;

	err = ntfs_ib_write(icx, icx->ib);
	if (err)
		return err;

	icx->ib_dirty = false;

	return 0;
}

int ntfs_icx_ib_sync_write(ntfs_index_context *icx)
{
	int ret;

	if (icx->ib_dirty == false)
		return 0;

	icx->sync_write = true;

	ret = ntfs_ib_write(icx, icx->ib);
	if (!ret) {
		ntfs_free(icx->ib);
		icx->ib = NULL;
		icx->ib_dirty = false;
	} else {
		post_write_mst_fixup((NTFS_RECORD*)icx->ib);
		icx->sync_write = false;
	}

	return ret;
}

/**
 * ntfs_index_ctx_get - allocate and initialize a new index context
 * @ni:		ntfs inode with which to initialize the context
 * @name:	name of the which context describes
 * @name_len:	length of the index name
 *
 * Allocate a new index context, initialize it with @ni and return it.
 * Return NULL if allocation failed.
 */
ntfs_index_context *ntfs_index_ctx_get(ntfs_inode *ni,
		ntfschar *name, u32 name_len)
{
	ntfs_index_context *icx;

	ntfs_debug("Entering\n");

	if (!ni)
		return NULL;

	if (ni->nr_extents == -1)
		ni = ni->ext.base_ntfs_ino;

	icx = kmem_cache_alloc(ntfs_index_ctx_cache, GFP_NOFS);
	if (icx)
		*icx = (ntfs_index_context) {
			.idx_ni = ni,
			.name = name,
			.name_len = name_len,
		};
	return icx;
}

static void ntfs_index_ctx_free(ntfs_index_context *icx)
{
	ntfs_debug("Entering\n");

	if (icx->actx) {
		ntfs_attr_put_search_ctx(icx->actx);
		icx->actx = NULL;
	}

	if (!icx->is_in_root) {
		if (icx->ib_dirty)
			ntfs_ib_write(icx, icx->ib);
		ntfs_free(icx->ib);
		icx->ib = NULL;
	}

	if (icx->ia_ni) {
		iput(VFS_I(icx->ia_ni));
		icx->ia_ni = NULL;
	}
}

/**
 * ntfs_index_ctx_put - release an index context
 * @icx:	index context to free
 *
 * Release the index context @icx, releasing all associated resources.
 */
void ntfs_index_ctx_put(ntfs_index_context *icx)
{
	ntfs_index_ctx_free(icx);
	kmem_cache_free(ntfs_index_ctx_cache, icx);
}

/**
 * ntfs_index_ctx_reinit - reinitialize an index context
 * @icx:	index context to reinitialize
 *
 * Reinitialize the index context @icx so it can be used for ntfs_index_lookup.
 */
void ntfs_index_ctx_reinit(ntfs_index_context *icx)
{
	ntfs_debug("Entering\n");

	ntfs_index_ctx_free(icx);

	*icx = (ntfs_index_context) {
		.idx_ni = icx->idx_ni,
		.name = icx->name,
		.name_len = icx->name_len,
	};
}

static leVCN *ntfs_ie_get_vcn_addr(INDEX_ENTRY *ie)
{
	return (leVCN *)((u8 *)ie + le16_to_cpu(ie->length) - sizeof(VCN));
}

/**
 *  Get the subnode vcn to which the index entry refers.
 */
static VCN ntfs_ie_get_vcn(INDEX_ENTRY *ie)
{
	return sle64_to_cpup(ntfs_ie_get_vcn_addr(ie));
}

static INDEX_ENTRY *ntfs_ie_get_first(INDEX_HEADER *ih)
{
	return (INDEX_ENTRY *)((u8 *)ih + le32_to_cpu(ih->entries_offset));
}

static INDEX_ENTRY *ntfs_ie_get_next(INDEX_ENTRY *ie)
{
	return (INDEX_ENTRY *)((char *)ie + le16_to_cpu(ie->length));
}

static u8 *ntfs_ie_get_end(INDEX_HEADER *ih)
{
	return (u8 *)ih + le32_to_cpu(ih->index_length);
}

static int ntfs_ie_end(INDEX_ENTRY *ie)
{
	return ie->flags & INDEX_ENTRY_END || !ie->length;
}

/**
 *  Find the last entry in the index block
 */
static INDEX_ENTRY *ntfs_ie_get_last(INDEX_ENTRY *ie, char *ies_end)
{
	ntfs_debug("Entering\n");

	while ((char *)ie < ies_end && !ntfs_ie_end(ie))
		ie = ntfs_ie_get_next(ie);

	return ie;
}

static INDEX_ENTRY *ntfs_ie_get_by_pos(INDEX_HEADER *ih, int pos)
{
	INDEX_ENTRY *ie;

	ntfs_debug("pos: %d\n", pos);

	ie = ntfs_ie_get_first(ih);

	while (pos-- > 0)
		ie = ntfs_ie_get_next(ie);

	return ie;
}

static INDEX_ENTRY *ntfs_ie_prev(INDEX_HEADER *ih, INDEX_ENTRY *ie)
{
	INDEX_ENTRY *ie_prev = NULL;
	INDEX_ENTRY *tmp;

	ntfs_debug("Entering\n");

	tmp = ntfs_ie_get_first(ih);

	while (tmp != ie) {
		ie_prev = tmp;
		tmp = ntfs_ie_get_next(tmp);
	}

	return ie_prev;
}

static int ntfs_ih_numof_entries(INDEX_HEADER *ih)
{
	int n;
	INDEX_ENTRY *ie;
	u8 *end;

	ntfs_debug("Entering\n");

	end = ntfs_ie_get_end(ih);
	ie = ntfs_ie_get_first(ih);
	for (n = 0; !ntfs_ie_end(ie) && (u8 *)ie < end; n++)
		ie = ntfs_ie_get_next(ie);
	return n;
}

static int ntfs_ih_one_entry(INDEX_HEADER *ih)
{
	return (ntfs_ih_numof_entries(ih) == 1);
}

static int ntfs_ih_zero_entry(INDEX_HEADER *ih)
{
	return (ntfs_ih_numof_entries(ih) == 0);
}

static void ntfs_ie_delete(INDEX_HEADER *ih, INDEX_ENTRY *ie)
{
	u32 new_size;

	ntfs_debug("Entering\n");

	new_size = le32_to_cpu(ih->index_length) - le16_to_cpu(ie->length);
	ih->index_length = cpu_to_le32(new_size);
	memmove(ie, (u8 *)ie + le16_to_cpu(ie->length),
			new_size - ((u8 *)ie - (u8 *)ih));
}

static void ntfs_ie_set_vcn(INDEX_ENTRY *ie, VCN vcn)
{
	*ntfs_ie_get_vcn_addr(ie) = cpu_to_sle64(vcn);
}

/**
 *  Insert @ie index entry at @pos entry. Used @ih values should be ok already.
 */
static void ntfs_ie_insert(INDEX_HEADER *ih, INDEX_ENTRY *ie, INDEX_ENTRY *pos)
{
	int ie_size = le16_to_cpu(ie->length);

	ntfs_debug("Entering\n");

	ih->index_length = cpu_to_le32(le32_to_cpu(ih->index_length) + ie_size);
	memmove((u8 *)pos + ie_size, pos,
			le32_to_cpu(ih->index_length) - ((u8 *)pos - (u8 *)ih) - ie_size);
	memcpy(pos, ie, ie_size);
}

static INDEX_ENTRY *ntfs_ie_dup(INDEX_ENTRY *ie)
{
	INDEX_ENTRY *dup;

	ntfs_debug("Entering\n");

	dup = ntfs_malloc_nofs(le16_to_cpu(ie->length));
	if (dup)
		memcpy(dup, ie, le16_to_cpu(ie->length));

	return dup;
}

static INDEX_ENTRY *ntfs_ie_dup_novcn(INDEX_ENTRY *ie)
{
	INDEX_ENTRY *dup;
	int size = le16_to_cpu(ie->length);

	ntfs_debug("Entering\n");

	if (ie->flags & INDEX_ENTRY_NODE)
		size -= sizeof(VCN);

	dup = ntfs_malloc_nofs(size);
	if (dup) {
		memcpy(dup, ie, size);
		dup->flags &= ~INDEX_ENTRY_NODE;
		dup->length = cpu_to_le16(size);
	}
	return dup;
}

/*
 *		Check the consistency of an index block
 *
 *	Make sure the index block does not overflow from the index record.
 *	The size of block is assumed to have been checked to be what is
 *	defined in the index root.
 *
 *	Returns 0 if no error was found
 *		-1 otherwise (with errno unchanged)
 *
 *      |<--->|  offsetof(INDEX_BLOCK, index)
 *      |     |<--->|  sizeof(INDEX_HEADER)
 *      |     |     |
 *      |     |     | seq          index entries         unused
 *      |=====|=====|=====|===========================|==============|
 *      |     |           |                           |              |
 *      |     |<--------->| entries_offset            |              |
 *      |     |<---------------- index_length ------->|              |
 *      |     |<--------------------- allocated_size --------------->|
 *      |<--------------------------- block_size ------------------->|
 *
 *      size(INDEX_HEADER) <= ent_offset < ind_length <= alloc_size < bk_size
 */
static int ntfs_index_block_inconsistent(ntfs_index_context *icx, INDEX_BLOCK *ib, VCN vcn)
{
	u32 ib_size = (unsigned int)le32_to_cpu(ib->index.allocated_size) +
		offsetof(INDEX_BLOCK, index);
	struct super_block *sb = icx->idx_ni->vol->sb;
	unsigned long long inum = icx->idx_ni->mft_no;

	ntfs_debug("Entering\n");

	if (!ntfs_is_indx_record(ib->magic)) {

		ntfs_error(sb, "Corrupt index block signature: vcn %lld inode %llu\n",
				(long long)vcn, (unsigned long long)icx->idx_ni->mft_no);
		return -1;
	}

	if (sle64_to_cpu(ib->index_block_vcn) != vcn) {

		ntfs_error(sb, "Corrupt index block: VCN (%lld) is different "
				"from expected VCN (%lld) in inode %llu\n",
				(long long)sle64_to_cpu(ib->index_block_vcn),
				(long long)vcn, inum);
		return -1;
	}

	if (ib_size != icx->block_size) {

		ntfs_error(sb, "Corrupt index block : VCN (%lld) of inode %llu "
				"has a size (%u) differing from the index "
				"specified size (%u)\n", (long long)vcn, inum, ib_size,
				icx->block_size);
		return -1;
	}

	if (le32_to_cpu(ib->index.entries_offset) < sizeof(INDEX_HEADER)) {
		ntfs_error(sb, "Invalid index entry offset in inode %lld\n", inum);
		return -1;
	}
	if (le32_to_cpu(ib->index.index_length) <=
	    le32_to_cpu(ib->index.entries_offset)) {
		ntfs_error(sb, "No space for index entries in inode %lld\n", inum);
		return -1;
	}
	if (le32_to_cpu(ib->index.allocated_size) <
	    le32_to_cpu(ib->index.index_length)) {
		ntfs_error(sb, "Index entries overflow in inode %lld\n", inum);
		return -1;
	}

	return 0;
}

static INDEX_ROOT *ntfs_ir_lookup(ntfs_inode *ni, ntfschar *name,
		u32 name_len, ntfs_attr_search_ctx **ctx)
{
	ATTR_RECORD *a;
	INDEX_ROOT *ir = NULL;

	ntfs_debug("Entering\n");
	*ctx = ntfs_attr_get_search_ctx(ni, NULL);
	if (!*ctx) {
		ntfs_error(ni->vol->sb, "%s, Failed to get search context", __FUNCTION__);
		return NULL;
	}

	if (ntfs_attr_lookup(AT_INDEX_ROOT, name, name_len, CASE_SENSITIVE,
				0, NULL, 0, *ctx)) {
		ntfs_error(ni->vol->sb, "Failed to lookup $INDEX_ROOT");
		goto err_out;
	}

	a = (*ctx)->attr;
	if (a->non_resident) {
		ntfs_error(ni->vol->sb, "Non-resident $INDEX_ROOT detected");
		goto err_out;
	}

	ir = (INDEX_ROOT *)((char *)a + le16_to_cpu(a->data.resident.value_offset));
err_out:
	if (!ir) {
		ntfs_attr_put_search_ctx(*ctx);
		*ctx = NULL;
	}
	return ir;
}

static INDEX_ROOT *ntfs_ir_lookup2(ntfs_inode *ni, ntfschar *name, u32 len)
{
	ntfs_attr_search_ctx *ctx;
	INDEX_ROOT *ir;

	ir = ntfs_ir_lookup(ni, name, len, &ctx);
	if (ir)
		ntfs_attr_put_search_ctx(ctx);
	return ir;
}

/**
 * Find a key in the index block.
 */
static int ntfs_ie_lookup(const void *key, const int key_len,
		ntfs_index_context *icx, INDEX_HEADER *ih,
		VCN *vcn, INDEX_ENTRY **ie_out)
{
	INDEX_ENTRY *ie;
	u8 *index_end;
	int rc, item = 0;

	ntfs_debug("Entering\n");

	index_end = ntfs_ie_get_end(ih);

	/*
	 * Loop until we exceed valid memory (corruption case) or until we
	 * reach the last entry.
	 */
	for (ie = ntfs_ie_get_first(ih); ; ie = ntfs_ie_get_next(ie)) {
		/* Bounds checks. */
		if ((u8 *)ie + sizeof(INDEX_ENTRY_HEADER) > index_end ||
				(u8 *)ie + le16_to_cpu(ie->length) > index_end) {
			ntfs_error(icx->idx_ni->vol->sb, "Index entry out of bounds in inode "
					"%llu.\n",
					(unsigned long long)icx->idx_ni->mft_no);
			return -ERANGE;
		}

		/*
		 * The last entry cannot contain a key.  It can however contain
		 * a pointer to a child node in the B+tree so we just break out.
		 */
		if (ntfs_ie_end(ie))
			break;

		/*
		 * Not a perfect match, need to do full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate(icx->idx_ni->vol, icx->cr, key, key_len, &ie->key,
				le16_to_cpu(ie->key_length));
		if (rc == -2) {
			ntfs_error(icx->idx_ni->vol->sb, "Collation error. Perhaps a filename "
					"contains invalid characters?\n");
			return -ERANGE;
		}
		/*
		 * If @key collates before the key of the current entry, there
		 * is definitely no such key in this index but we might need to
		 * descend into the B+tree so we just break out of the loop.
		 */
		if (rc == -1)
			break;

		if (!rc) {
			*ie_out = ie;
			icx->parent_pos[icx->pindex] = item;
			return 0;
		}

		item++;
	}
	/*
	 * We have finished with this index block without success. Check for the
	 * presence of a child node and if not present return with errno ENOENT,
	 * otherwise we will keep searching in another index block.
	 */
	if (!(ie->flags & INDEX_ENTRY_NODE)) {
		ntfs_debug("Index entry wasn't found.\n");
		*ie_out = ie;
		return -ENOENT;
	}

	/* Get the starting vcn of the index_block holding the child node. */
	*vcn = ntfs_ie_get_vcn(ie);
	if (*vcn < 0) {
		ntfs_error(icx->idx_ni->vol->sb, "Negative vcn in inode %llu\n",
				(unsigned long long)icx->idx_ni->mft_no);
		return -EINVAL;
	}

	ntfs_debug("Parent entry number %d\n", item);
	icx->parent_pos[icx->pindex] = item;

	return -EAGAIN;
}

ntfs_inode *ntfs_ia_open(ntfs_index_context *icx, ntfs_inode *ni)
{
	struct inode *ia_vi;

	ia_vi = ntfs_index_iget(VFS_I(ni), icx->name, icx->name_len);
	if (IS_ERR(ia_vi)) {
		ntfs_error(icx->idx_ni->vol->sb, "Failed to open index allocation of inode "
				"%llu", (unsigned long long)ni->mft_no);
		return NULL;
	}

	return NTFS_I(ia_vi);
}

static int ntfs_ib_read(ntfs_index_context *icx, VCN vcn, INDEX_BLOCK *dst)
{
	s64 pos, ret;

	ntfs_debug("vcn: %lld\n", vcn);

	pos = ntfs_ib_vcn_to_pos(icx, vcn);

	ret = ntfs_inode_attr_pread(VFS_I(icx->ia_ni), pos, icx->block_size, (u8 *)dst);
	if (ret != icx->block_size) {
		if (ret == -1)
			ntfs_error(icx->idx_ni->vol->sb, "Failed to read index block");
		else
			ntfs_error(icx->idx_ni->vol->sb, "Failed to read full index block at "
					"%lld\n", (long long)pos);
		return -1;
	}

	post_read_mst_fixup((NTFS_RECORD*)((u8 *)dst), icx->block_size);
	if (ntfs_index_block_inconsistent(icx, dst, vcn))
		return -1;

	return 0;
}

static int ntfs_icx_parent_inc(ntfs_index_context *icx)
{
	icx->pindex++;
	if (icx->pindex >= MAX_PARENT_VCN) {
		ntfs_error(icx->idx_ni->vol->sb, "Index is over %d level deep", MAX_PARENT_VCN);
		return -EOPNOTSUPP;
	}
	return 0;
}

static int ntfs_icx_parent_dec(ntfs_index_context *icx)
{
	icx->pindex--;
	if (icx->pindex < 0) {
		ntfs_error(icx->idx_ni->vol->sb, "Corrupt index pointer (%d)", icx->pindex);
		return -EINVAL;
	}
	return 0;
}

/**
 * ntfs_index_lookup - find a key in an index and return its index entry
 * @key:	[IN] key for which to search in the index
 * @key_len:	[IN] length of @key in bytes
 * @icx:	[IN/OUT] context describing the index and the returned entry
 *
 * Before calling ntfs_index_lookup(), @icx must have been obtained from a
 * call to ntfs_index_ctx_get().
 *
 * Look for the @key in the index specified by the index lookup context @icx.
 * ntfs_index_lookup() walks the contents of the index looking for the @key.
 *
 * If the @key is found in the index, 0 is returned and @icx is setup to
 * describe the index entry containing the matching @key.  @icx->entry is the
 * index entry and @icx->data and @icx->data_len are the index entry data and
 * its length in bytes, respectively.
 *
 * If the @key is not found in the index, -1 is returned, errno = ENOENT and
 * @icx is setup to describe the index entry whose key collates immediately
 * after the search @key, i.e. this is the position in the index at which
 * an index entry with a key of @key would need to be inserted.
 *
 * If an error occurs return -1, set errno to error code and @icx is left
 * untouched.
 *
 * When finished with the entry and its data, call ntfs_index_ctx_put() to free
 * the context and other associated resources.
 *
 * If the index entry was modified, call ntfs_index_entry_mark_dirty() before
 * the call to ntfs_index_ctx_put() to ensure that the changes are written
 * to disk.
 */
int ntfs_index_lookup(const void *key, const int key_len, ntfs_index_context *icx)
{
	VCN old_vcn, vcn;
	ntfs_inode *ni = icx->idx_ni;
	struct super_block *sb = ni->vol->sb;
	INDEX_ROOT *ir;
	INDEX_ENTRY *ie;
	INDEX_BLOCK *ib = NULL;
	int err = 0;

	ntfs_debug("Entering\n");

	if (!key || key_len <= 0) {
		ntfs_error(sb, "key: %p  key_len: %d", key, key_len);
		return -EINVAL;
	}

	ir = ntfs_ir_lookup(ni, icx->name, icx->name_len, &icx->actx);
	if (!ir)
		return -EIO;

	icx->block_size = le32_to_cpu(ir->index_block_size);
	if (icx->block_size < NTFS_BLOCK_SIZE) {
		err = -EINVAL;
		ntfs_error(sb, "Index block size (%d) is smaller than the "
				"sector size (%d)", icx->block_size, NTFS_BLOCK_SIZE);
		goto err_out;
	}

	if (ni->vol->cluster_size <= icx->block_size)
		icx->vcn_size_bits = ni->vol->cluster_size_bits;
	else
		icx->vcn_size_bits = ni->vol->sector_size_bits;

	icx->cr = ir->collation_rule;
	if (!ntfs_is_collation_rule_supported(icx->cr)) {
		err = -EOPNOTSUPP;
		ntfs_error(sb, "Unknown collation rule 0x%x",
				(unsigned int)le32_to_cpu(icx->cr));
		goto err_out;
	}

	old_vcn = VCN_INDEX_ROOT_PARENT;
	err = ntfs_ie_lookup(key, key_len, icx, &ir->index, &vcn, &ie);
	if (err == -ERANGE || err == -EINVAL)
		goto err_out;

	icx->ir = ir;
	if (err != -EAGAIN) {
		icx->is_in_root = true;
		icx->parent_vcn[icx->pindex] = old_vcn;
		goto done;
	}

	/* Child node present, descend into it. */
	icx->ia_ni = ntfs_ia_open(icx, ni);
	if (!icx->ia_ni) {
		err = -ENOENT;
		goto err_out;
	}

	ib = ntfs_malloc_nofs(icx->block_size);
	if (!ib) {
		err = -ENOMEM;
		goto err_out;
	}

descend_into_child_node:
	icx->parent_vcn[icx->pindex] = old_vcn;
	if (ntfs_icx_parent_inc(icx)) {
		err = -EIO;
		goto err_out;
	}
	old_vcn = vcn;

	ntfs_debug("Descend into node with VCN %lld.\n", vcn);

	if (ntfs_ib_read(icx, vcn, ib)) {
		err = -EIO;
		goto err_out;
	}
	err = ntfs_ie_lookup(key, key_len, icx, &ib->index, &vcn, &ie);
	if (err != -EAGAIN) {
		if (err == -EINVAL || err == -ERANGE)
			goto err_out;

		icx->is_in_root = false;
		icx->ib = ib;
		icx->parent_vcn[icx->pindex] = vcn;
		goto done;
	}

	if ((ib->index.flags & NODE_MASK) == LEAF_NODE) {
		ntfs_error(icx->idx_ni->vol->sb, "Index entry with child node found in a leaf "
				"node in inode 0x%llx.\n",
				(unsigned long long)ni->mft_no);
		goto err_out;
	}

	goto descend_into_child_node;
err_out:
	if (icx->actx) {
		ntfs_attr_put_search_ctx(icx->actx);
		icx->actx = NULL;
	}
	ntfs_free(ib);
	if (!err)
		err = -EIO;
	return err;
done:
	icx->entry = ie;
	icx->data = (u8 *)ie + offsetof(INDEX_ENTRY, key);
	icx->data_len = le16_to_cpu(ie->key_length);
	ntfs_debug("Done.\n");
	return err;

}

static INDEX_BLOCK *ntfs_ib_alloc(VCN ib_vcn, u32 ib_size,
		INDEX_HEADER_FLAGS node_type)
{
	INDEX_BLOCK *ib;
	int ih_size = sizeof(INDEX_HEADER);

	ntfs_debug("Entering ib_vcn = %lld ib_size = %u\n", ib_vcn, ib_size);

	ib = ntfs_malloc_nofs(ib_size);
	if (!ib)
		return NULL;

	ib->magic = magic_INDX;
	ib->usa_ofs = cpu_to_le16(sizeof(INDEX_BLOCK));
	ib->usa_count = cpu_to_le16(ib_size / NTFS_BLOCK_SIZE + 1);
	/* Set USN to 1 */
	*(le16 *)((char *)ib + le16_to_cpu(ib->usa_ofs)) = cpu_to_le16(1);
	ib->lsn = 0;
	ib->index_block_vcn = cpu_to_sle64(ib_vcn);
	ib->index.entries_offset = cpu_to_le32((ih_size +
				le16_to_cpu(ib->usa_count) * 2 + 7) & ~7);
	ib->index.index_length = 0;
	ib->index.allocated_size = cpu_to_le32(ib_size -
			(sizeof(INDEX_BLOCK) - ih_size));
	ib->index.flags = node_type;

	return ib;
}

/**
 *  Find the median by going through all the entries
 */
static INDEX_ENTRY *ntfs_ie_get_median(INDEX_HEADER *ih)
{
	INDEX_ENTRY *ie, *ie_start;
	u8 *ie_end;
	int i = 0, median;

	ntfs_debug("Entering\n");

	ie = ie_start = ntfs_ie_get_first(ih);
	ie_end = (u8 *)ntfs_ie_get_end(ih);

	while ((u8 *)ie < ie_end && !ntfs_ie_end(ie)) {
		ie = ntfs_ie_get_next(ie);
		i++;
	}
	/*
	 * NOTE: this could be also the entry at the half of the index block.
	 */
	median = i / 2 - 1;

	ntfs_debug("Entries: %d  median: %d\n", i, median);

	for (i = 0, ie = ie_start; i <= median; i++)
		ie = ntfs_ie_get_next(ie);

	return ie;
}

static s64 ntfs_ibm_vcn_to_pos(ntfs_index_context *icx, VCN vcn)
{
	return ntfs_ib_vcn_to_pos(icx, vcn) / icx->block_size;
}

static s64 ntfs_ibm_pos_to_vcn(ntfs_index_context *icx, s64 pos)
{
	return ntfs_ib_pos_to_vcn(icx, pos * icx->block_size);
}

static int ntfs_ibm_add(ntfs_index_context *icx)
{
	u8 bmp[8];

	ntfs_debug("Entering\n");

	if (ntfs_attr_exist(icx->idx_ni, AT_BITMAP, icx->name, icx->name_len))
		return 0;
	/*
	 * AT_BITMAP must be at least 8 bytes.
	 */
	memset(bmp, 0, sizeof(bmp));
	if (ntfs_attr_add(icx->idx_ni, AT_BITMAP, icx->name, icx->name_len,
				bmp, sizeof(bmp))) {
		ntfs_error(icx->idx_ni->vol->sb, "Failed to add AT_BITMAP");
		return -EINVAL;
	}

	return 0;
}

static int ntfs_ibm_modify(ntfs_index_context *icx, VCN vcn, int set)
{
	u8 byte;
	u64 pos = (u64)ntfs_ibm_vcn_to_pos(icx, vcn);
	u32 bpos = pos / 8;
	u32 bit = 1 << (pos % 8);
	ntfs_inode *bmp_ni;
	struct inode *bmp_vi;
	int ret = 0;

	ntfs_debug("%s vcn: %lld\n", set ? "set" : "clear", vcn);

	bmp_vi = ntfs_attr_iget(VFS_I(icx->idx_ni), AT_BITMAP, icx->name, icx->name_len);
	if (IS_ERR(bmp_vi)) {
		ntfs_error(icx->idx_ni->vol->sb, "Failed to open $BITMAP attribute");
		return PTR_ERR(bmp_vi);
	}

	bmp_ni = NTFS_I(bmp_vi);

	if (set) {
		if (bmp_ni->data_size < bpos + 1) {
			ret = ntfs_attr_truncate(bmp_ni, (bmp_ni->data_size + 8) & ~7);
			if (ret) {
				ntfs_error(icx->idx_ni->vol->sb, "Failed to truncate AT_BITMAP");
				goto err;
			}
			i_size_write(bmp_vi, (loff_t)bmp_ni->data_size);
		}
	}

	if (ntfs_inode_attr_pread(bmp_vi, bpos, 1, &byte) != 1) {
		ret = -EIO;
		ntfs_error(icx->idx_ni->vol->sb, "Failed to read $BITMAP");
		goto err;
	}

	if (set)
		byte |= bit;
	else
		byte &= ~bit;

	if (ntfs_inode_attr_pwrite(bmp_vi, bpos, 1, &byte, false) != 1) {
		ret = -EIO;
		ntfs_error(icx->idx_ni->vol->sb, "Failed to write $Bitmap");
		goto err;
	}

err:
	iput(bmp_vi);
	return ret;
}


static int ntfs_ibm_set(ntfs_index_context *icx, VCN vcn)
{
	return ntfs_ibm_modify(icx, vcn, 1);
}

static int ntfs_ibm_clear(ntfs_index_context *icx, VCN vcn)
{
	return ntfs_ibm_modify(icx, vcn, 0);
}

static VCN ntfs_ibm_get_free(ntfs_index_context *icx)
{
	u8 *bm;
	int bit;
	s64 vcn, byte, size;

	ntfs_debug("Entering\n");

	bm = ntfs_attr_readall(icx->idx_ni, AT_BITMAP,  icx->name, icx->name_len,
			&size);
	if (!bm)
		return (VCN)-1;

	for (byte = 0; byte < size; byte++) {
		if (bm[byte] == 255)
			continue;

		for (bit = 0; bit < 8; bit++) {
			if (!(bm[byte] & (1 << bit))) {
				vcn = ntfs_ibm_pos_to_vcn(icx, byte * 8 + bit);
				goto out;
			}
		}
	}

	vcn = ntfs_ibm_pos_to_vcn(icx, size * 8);
out:
	ntfs_debug("allocated vcn: %lld\n", vcn);

	if (ntfs_ibm_set(icx, vcn))
		vcn = (VCN)-1;

	ntfs_free(bm);
	return vcn;
}

static INDEX_BLOCK *ntfs_ir_to_ib(INDEX_ROOT *ir, VCN ib_vcn)
{
	INDEX_BLOCK *ib;
	INDEX_ENTRY *ie_last;
	char *ies_start, *ies_end;
	int i;

	ntfs_debug("Entering\n");

	ib = ntfs_ib_alloc(ib_vcn, le32_to_cpu(ir->index_block_size), LEAF_NODE);
	if (!ib)
		return NULL;

	ies_start = (char *)ntfs_ie_get_first(&ir->index);
	ies_end   = (char *)ntfs_ie_get_end(&ir->index);
	ie_last   = ntfs_ie_get_last((INDEX_ENTRY *)ies_start, ies_end);
	/*
	 * Copy all entries, including the termination entry
	 * as well, which can never have any data.
	 */
	i = (char *)ie_last - ies_start + le16_to_cpu(ie_last->length);
	memcpy(ntfs_ie_get_first(&ib->index), ies_start, i);

	ib->index.flags = ir->index.flags;
	ib->index.index_length = cpu_to_le32(i +
			le32_to_cpu(ib->index.entries_offset));
	return ib;
}

static void ntfs_ir_nill(INDEX_ROOT *ir)
{
	INDEX_ENTRY *ie_last;
	char *ies_start, *ies_end;

	ntfs_debug("Entering\n");
	/*
	 * TODO: This function could be much simpler.
	 */
	ies_start = (char *)ntfs_ie_get_first(&ir->index);
	ies_end   = (char *)ntfs_ie_get_end(&ir->index);
	ie_last   = ntfs_ie_get_last((INDEX_ENTRY *)ies_start, ies_end);
	/*
	 * Move the index root termination entry forward
	 */
	if ((char *)ie_last > ies_start) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0)
		char *buf = kmalloc(le16_to_cpu(ie_last->length), GFP_KERNEL);

		if (!buf)
			return;

		unsafe_memcpy(buf, (char *)ie_last, le16_to_cpu(ie_last->length),
				/* workaround to avoid fortify */);
		unsafe_memcpy(ies_start, buf, le16_to_cpu(ie_last->length),
				/* workaround to avoid fortify */);
		kfree(buf);
#else

		memmove(ies_start, (char *)ie_last, le16_to_cpu(ie_last->length));
#endif
		ie_last = (INDEX_ENTRY *)ies_start;
	}
}

static int ntfs_ib_copy_tail(ntfs_index_context *icx, INDEX_BLOCK *src,
		INDEX_ENTRY *median, VCN new_vcn)
{
	u8 *ies_end;
	INDEX_ENTRY *ie_head;		/* first entry after the median */
	int tail_size, ret;
	INDEX_BLOCK *dst;

	ntfs_debug("Entering\n");

	dst = ntfs_ib_alloc(new_vcn, icx->block_size,
			src->index.flags & NODE_MASK);
	if (!dst)
		return -ENOMEM;

	ie_head = ntfs_ie_get_next(median);

	ies_end = (u8 *)ntfs_ie_get_end(&src->index);
	tail_size = ies_end - (u8 *)ie_head;
	memcpy(ntfs_ie_get_first(&dst->index), ie_head, tail_size);

	dst->index.index_length = cpu_to_le32(tail_size +
			le32_to_cpu(dst->index.entries_offset));
	ret = ntfs_ib_write(icx, dst);

	ntfs_free(dst);
	return ret;
}

static int ntfs_ib_cut_tail(ntfs_index_context *icx, INDEX_BLOCK *ib,
		INDEX_ENTRY *ie)
{
	char *ies_start, *ies_end;
	INDEX_ENTRY *ie_last;
	int ret;

	ntfs_debug("Entering\n");

	ies_start = (char *)ntfs_ie_get_first(&ib->index);
	ies_end   = (char *)ntfs_ie_get_end(&ib->index);

	ie_last   = ntfs_ie_get_last((INDEX_ENTRY *)ies_start, ies_end);
	if (ie_last->flags & INDEX_ENTRY_NODE)
		ntfs_ie_set_vcn(ie_last, ntfs_ie_get_vcn(ie));

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
	unsafe_memcpy(ie, ie_last, le16_to_cpu(ie_last->length),
			/* alloc is larger than ie_last->length, see ntfs_ie_get_last() */);
#else
	memcpy(ie, ie_last, le16_to_cpu(ie_last->length));
#endif

	ib->index.index_length = cpu_to_le32(((char *)ie - ies_start) +
			le16_to_cpu(ie->length) + le32_to_cpu(ib->index.entries_offset));

	ret = ntfs_ib_write(icx, ib);
	return ret;
}

static int ntfs_ia_add(ntfs_index_context *icx)
{
	int ret;

	ntfs_debug("Entering\n");

	ret = ntfs_ibm_add(icx);
	if (ret)
		return ret;

	if (!ntfs_attr_exist(icx->idx_ni, AT_INDEX_ALLOCATION, icx->name, icx->name_len)) {
		ret = ntfs_attr_add(icx->idx_ni, AT_INDEX_ALLOCATION, icx->name,
					icx->name_len, NULL, 0);
		if (ret) {
			ntfs_error(icx->idx_ni->vol->sb, "Failed to add AT_INDEX_ALLOCATION");
			return ret;
		}
	}

	icx->ia_ni = ntfs_ia_open(icx, icx->idx_ni);
	if (!icx->ia_ni)
		return -ENOENT;

	return 0;
}

static int ntfs_ir_reparent(ntfs_index_context *icx)
{
	ntfs_attr_search_ctx *ctx = NULL;
	INDEX_ROOT *ir;
	INDEX_ENTRY *ie;
	INDEX_BLOCK *ib = NULL;
	VCN new_ib_vcn;
	int ix_root_size;
	int ret = 0;

	ntfs_debug("Entering\n");

	ir = ntfs_ir_lookup2(icx->idx_ni, icx->name, icx->name_len);
	if (!ir) {
		ret = -ENOENT;
		goto out;
	}

	if ((ir->index.flags & NODE_MASK) == SMALL_INDEX) {
		ret = ntfs_ia_add(icx);
		if (ret)
			goto out;
	}

	new_ib_vcn = ntfs_ibm_get_free(icx);
	if (new_ib_vcn < 0) {
		ret = -EINVAL;
		goto out;
	}

	ir = ntfs_ir_lookup2(icx->idx_ni, icx->name, icx->name_len);
	if (!ir) {
		ret = -ENOENT;
		goto clear_bmp;
	}

	ib = ntfs_ir_to_ib(ir, new_ib_vcn);
	if (ib == NULL) {
		ret = -EIO;
		ntfs_error(icx->idx_ni->vol->sb, "Failed to move index root to index block");
		goto clear_bmp;
	}

	ret = ntfs_ib_write(icx, ib);
	if (ret)
		goto clear_bmp;

retry:
	ir = ntfs_ir_lookup(icx->idx_ni, icx->name, icx->name_len, &ctx);
	if (!ir) {
		ret = -ENOENT;
		goto clear_bmp;
	}

	ntfs_ir_nill(ir);

	ie = ntfs_ie_get_first(&ir->index);
	ie->flags |= INDEX_ENTRY_NODE;
	ie->length = cpu_to_le16(sizeof(INDEX_ENTRY_HEADER) + sizeof(VCN));

	ir->index.flags = LARGE_INDEX;
	NInoSetIndexAllocPresent(icx->idx_ni);
	ir->index.index_length = cpu_to_le32(le32_to_cpu(ir->index.entries_offset) +
			le16_to_cpu(ie->length));
	ir->index.allocated_size = ir->index.index_length;

	ix_root_size = sizeof(INDEX_ROOT) - sizeof(INDEX_HEADER) +
		le32_to_cpu(ir->index.allocated_size);
	ret  = ntfs_resident_attr_value_resize(ctx->mrec, ctx->attr, ix_root_size);
	if (ret) {
		/*
		 * When there is no space to build a non-resident
		 * index, we may have to move the root to an extent
		 */
		if ((ret == -ENOSPC) && (ctx->al_entry || !ntfs_inode_add_attrlist(icx->idx_ni))) {
			ntfs_attr_put_search_ctx(ctx);
			ctx = NULL;
			ir = ntfs_ir_lookup(icx->idx_ni, icx->name, icx->name_len, &ctx);
			if (ir && !ntfs_attr_record_move_away(ctx, ix_root_size -
					le32_to_cpu(ctx->attr->data.resident.value_length))) {
				if (ntfs_attrlist_update(ctx->base_ntfs_ino ?
							 ctx->base_ntfs_ino : ctx->ntfs_ino))
					goto clear_bmp;
				ntfs_attr_put_search_ctx(ctx);
				ctx = NULL;
				goto retry;
			}
		}
		goto clear_bmp;
	} else {
		icx->idx_ni->data_size = icx->idx_ni->initialized_size = ix_root_size;
		icx->idx_ni->allocated_size = (ix_root_size  + 7) & ~7;
	}
	ntfs_ie_set_vcn(ie, new_ib_vcn);

err_out:
	ntfs_free(ib);
	if (ctx)
		ntfs_attr_put_search_ctx(ctx);
out:
	return ret;
clear_bmp:
	ntfs_ibm_clear(icx, new_ib_vcn);
	goto err_out;
}

/**
 * ntfs_ir_truncate - Truncate index root attribute
 *
 * Returns 0, error.
 */
static int ntfs_ir_truncate(ntfs_index_context *icx, int data_size)
{
	int ret;

	ntfs_debug("Entering\n");

	/*
	 *  INDEX_ROOT must be resident and its entries can be moved to
	 *  INDEX_BLOCK, so ENOSPC isn't a real error.
	 */
	ret = ntfs_attr_truncate(icx->idx_ni, data_size + offsetof(INDEX_ROOT, index));
	if (!ret) {
		ntfs_sync_inode_size(icx->idx_ni);
		icx->ir = ntfs_ir_lookup2(icx->idx_ni, icx->name, icx->name_len);
		if (!icx->ir)
			return -ENOENT;

		icx->ir->index.allocated_size = cpu_to_le32(data_size);
	} else if (ret != -ENOSPC)
		ntfs_error(icx->idx_ni->vol->sb, "Failed to truncate INDEX_ROOT");

	return ret;
}

/**
 * ntfs_ir_make_space - Make more space for the index root attribute
 */
static int ntfs_ir_make_space(ntfs_index_context *icx, int data_size)
{
	int ret;

	ntfs_debug("Entering\n");

	ret = ntfs_ir_truncate(icx, data_size);
	if (ret == -ENOSPC) {
		ret = ntfs_ir_reparent(icx);
		if (!ret)
			ret = -EAGAIN;
		else
			ntfs_error(icx->idx_ni->vol->sb, "Failed to modify INDEX_ROOT");
	}

	return ret;
}

/*
 * NOTE: 'ie' must be a copy of a real index entry.
 */
static int ntfs_ie_add_vcn(INDEX_ENTRY **ie)
{
	INDEX_ENTRY *p, *old = *ie;

	old->length = cpu_to_le16(le16_to_cpu(old->length) + sizeof(VCN));
	p = ntfs_realloc_nofs(old, le16_to_cpu(old->length),
			le16_to_cpu(old->length) - sizeof(VCN));
	if (!p)
		return -ENOMEM;

	p->flags |= INDEX_ENTRY_NODE;
	*ie = p;
	return 0;
}

static int ntfs_ih_insert(INDEX_HEADER *ih, INDEX_ENTRY *orig_ie, VCN new_vcn,
		int pos)
{
	INDEX_ENTRY *ie_node, *ie;
	int ret = 0;
	VCN old_vcn;

	ntfs_debug("Entering\n");
	ie = ntfs_ie_dup(orig_ie);
	if (!ie)
		return -ENOMEM;

	if (!(ie->flags & INDEX_ENTRY_NODE)) {
		ret = ntfs_ie_add_vcn(&ie);
		if (ret)
			goto out;
	}

	ie_node = ntfs_ie_get_by_pos(ih, pos);
	old_vcn = ntfs_ie_get_vcn(ie_node);
	ntfs_ie_set_vcn(ie_node, new_vcn);

	ntfs_ie_insert(ih, ie, ie_node);
	ntfs_ie_set_vcn(ie_node, old_vcn);
out:
	ntfs_free(ie);
	return ret;
}

static VCN ntfs_icx_parent_vcn(ntfs_index_context *icx)
{
	return icx->parent_vcn[icx->pindex];
}

static VCN ntfs_icx_parent_pos(ntfs_index_context *icx)
{
	return icx->parent_pos[icx->pindex];
}

static int ntfs_ir_insert_median(ntfs_index_context *icx, INDEX_ENTRY *median,
		VCN new_vcn)
{
	u32 new_size;
	int ret;

	ntfs_debug("Entering\n");

	icx->ir = ntfs_ir_lookup2(icx->idx_ni, icx->name, icx->name_len);
	if (!icx->ir)
		return -ENOENT;

	new_size = le32_to_cpu(icx->ir->index.index_length) +
		le16_to_cpu(median->length);
	if (!(median->flags & INDEX_ENTRY_NODE))
		new_size += sizeof(VCN);

	ret = ntfs_ir_make_space(icx, new_size);
	if (ret)
		return ret;

	icx->ir = ntfs_ir_lookup2(icx->idx_ni, icx->name, icx->name_len);
	if (!icx->ir)
		return -ENOENT;

	return ntfs_ih_insert(&icx->ir->index, median, new_vcn,
			ntfs_icx_parent_pos(icx));
}

static int ntfs_ib_split(ntfs_index_context *icx, INDEX_BLOCK *ib);

struct split_info {
	struct list_head entry;
	VCN new_vcn;
	INDEX_BLOCK *ib;
};

/**
 * On success return 0 or -EAGAIN.
 * On error return.
 */
static int ntfs_ib_insert(ntfs_index_context *icx, INDEX_ENTRY *ie, VCN new_vcn,
		struct split_info *si)
{
	INDEX_BLOCK *ib;
	u32 idx_size, allocated_size;
	int err;
	VCN old_vcn;

	ntfs_debug("Entering\n");

	ib = ntfs_malloc_nofs(icx->block_size);
	if (!ib)
		return -ENOMEM;

	old_vcn = ntfs_icx_parent_vcn(icx);

	err = ntfs_ib_read(icx, old_vcn, ib);
	if (err)
		goto err_out;

	idx_size = le32_to_cpu(ib->index.index_length);
	allocated_size = le32_to_cpu(ib->index.allocated_size);
	if (idx_size + le16_to_cpu(ie->length) + sizeof(VCN) > allocated_size) {
		si->ib = ib;
		si->new_vcn = new_vcn;
		return -EAGAIN;
	}

	err = ntfs_ih_insert(&ib->index, ie, new_vcn, ntfs_icx_parent_pos(icx));
	if (err)
		goto err_out;

	err = ntfs_ib_write(icx, ib);

err_out:
	ntfs_free(ib);
	return err;
}

int count = 0;
/**
 * ntfs_ib_split - Split an index block
 */
static int ntfs_ib_split(ntfs_index_context *icx, INDEX_BLOCK *ib)
{
	INDEX_ENTRY *median;
	VCN new_vcn;
	int ret;
	struct split_info *si;
	LIST_HEAD(ntfs_cut_tail_list);

	ntfs_debug("Entering\n");

resplit:
	ret = ntfs_icx_parent_dec(icx);
	if (ret)
		goto out;

	median  = ntfs_ie_get_median(&ib->index);
	new_vcn = ntfs_ibm_get_free(icx);
	if (new_vcn < 0) {
		ret = -EINVAL;
		goto out;
	}

	ret = ntfs_ib_copy_tail(icx, ib, median, new_vcn);
	if (ret) {
		ntfs_ibm_clear(icx, new_vcn);
		goto out;;
	}

	if (ntfs_icx_parent_vcn(icx) == VCN_INDEX_ROOT_PARENT) {
		ret = ntfs_ir_insert_median(icx, median, new_vcn);
		if (ret) {
			ntfs_ibm_clear(icx, new_vcn);
			goto out;;
		}
	} else {
		si = kzalloc(sizeof(struct split_info), GFP_NOFS);
		if (!si) {
			ntfs_ibm_clear(icx, new_vcn);
			ret = -ENOMEM;
			goto out;
		}

		ret = ntfs_ib_insert(icx, median, new_vcn, si);
		if (ret == -EAGAIN) {
			list_add_tail(&si->entry, &ntfs_cut_tail_list);
			ib = si->ib;
			goto resplit;
		} else if (ret) {
			ntfs_free(si->ib);
			kfree(si);
			ntfs_ibm_clear(icx, new_vcn);
			goto out;
		}
		kfree(si);
	}

	ret = ntfs_ib_cut_tail(icx, ib, median);

out:
	while (!list_empty(&ntfs_cut_tail_list)) {
		si = list_last_entry(&ntfs_cut_tail_list, struct split_info, entry);
		ntfs_ibm_clear(icx, si->new_vcn);
		ntfs_free(si->ib);
		list_del(&si->entry);
		kfree(si);
		if (!ret)
			ret = -EAGAIN;
	}

	return ret;
}

int ntfs_ie_add(ntfs_index_context *icx, INDEX_ENTRY *ie)
{
	INDEX_HEADER *ih;
	int allocated_size, new_size;
	int ret;

	while (1) {
		ret = ntfs_index_lookup(&ie->key, le16_to_cpu(ie->key_length), icx);
		if (!ret) {
			ret = -EEXIST;
			ntfs_error(icx->idx_ni->vol->sb, "Index already have such entry");
			goto err_out;
		}
		if (ret != -ENOENT) {
			ntfs_error(icx->idx_ni->vol->sb, "Failed to find place for new entry");
			goto err_out;
		}
		ret = 0;

		if (icx->is_in_root)
			ih = &icx->ir->index;
		else
			ih = &icx->ib->index;

		allocated_size = le32_to_cpu(ih->allocated_size);
		new_size = le32_to_cpu(ih->index_length) + le16_to_cpu(ie->length);

		if (new_size <= allocated_size)
			break;

		ntfs_debug("index block sizes: allocated: %d  needed: %d\n",
				allocated_size, new_size);

		if (icx->is_in_root)
			ret = ntfs_ir_make_space(icx, new_size);
		else
			ret = ntfs_ib_split(icx, icx->ib);
		if (ret && ret != -EAGAIN)
			goto err_out;

		mark_mft_record_dirty(icx->actx->ntfs_ino);
		ntfs_index_ctx_reinit(icx);
	}

	ntfs_ie_insert(ih, ie, icx->entry);
	ntfs_index_entry_mark_dirty(icx);

err_out:
	ntfs_debug("%s\n", ret ? "Failed" : "Done");
	return ret;
}

/**
 * ntfs_index_add_filename - add filename to directory index
 * @ni:		ntfs inode describing directory to which index add filename
 * @fn:		FILE_NAME attribute to add
 * @mref:	reference of the inode which @fn describes
 *
 * Return 0 on success or error with errno set to the error code.
 */
int ntfs_index_add_filename(ntfs_inode *ni, FILE_NAME_ATTR *fn, MFT_REF mref)
{
	INDEX_ENTRY *ie;
	ntfs_index_context *icx;
	int fn_size, ie_size, err;

	ntfs_debug("Entering\n");

	if (!ni || !fn)
		return -EINVAL;

	fn_size = (fn->file_name_length * sizeof(ntfschar)) +
		sizeof(FILE_NAME_ATTR);
	ie_size = (sizeof(INDEX_ENTRY_HEADER) + fn_size + 7) & ~7;

	ie = ntfs_malloc_nofs(ie_size);
	if (!ie)
		return -ENOMEM;

	ie->data.dir.indexed_file = cpu_to_le64(mref);
	ie->length	 = cpu_to_le16(ie_size);
	ie->key_length	 = cpu_to_le16(fn_size);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
	unsafe_memcpy(&ie->key, fn, fn_size,
		      /* "fn_size" was correctly calculated above */);
#else
	memcpy(&ie->key, fn, fn_size);
#endif

	icx = ntfs_index_ctx_get(ni, I30, 4);
	if (!icx) {
		err = -ENOMEM;
		goto out;
	}

	err = ntfs_ie_add(icx, ie);
	ntfs_index_ctx_put(icx);
out:
	ntfs_free(ie);
	return err;
}

static int ntfs_ih_takeout(ntfs_index_context *icx, INDEX_HEADER *ih,
		INDEX_ENTRY *ie, INDEX_BLOCK *ib)
{
	INDEX_ENTRY *ie_roam;
	int freed_space;
	bool full;
	int ret = 0;

	ntfs_debug("Entering\n");

	full = ih->index_length == ih->allocated_size;
	ie_roam = ntfs_ie_dup_novcn(ie);
	if (!ie_roam)
		return -ENOMEM;

	ntfs_ie_delete(ih, ie);

	if (ntfs_icx_parent_vcn(icx) == VCN_INDEX_ROOT_PARENT) {
		/*
		 * Recover the space which may have been freed
		 * while deleting an entry from root index
		 */
		freed_space = le32_to_cpu(ih->allocated_size) -
			le32_to_cpu(ih->index_length);
		if (full && (freed_space > 0) && !(freed_space & 7)) {
			ntfs_ir_truncate(icx, le32_to_cpu(ih->index_length));
			/* do nothing if truncation fails */
		}

		mark_mft_record_dirty(icx->actx->ntfs_ino);
	} else {
		ret = ntfs_ib_write(icx, ib);
		if (ret)
			goto out;
	}

	ntfs_index_ctx_reinit(icx);

	ret = ntfs_ie_add(icx, ie_roam);
out:
	ntfs_free(ie_roam);
	return ret;
}

/**
 *  Used if an empty index block to be deleted has END entry as the parent
 *  in the INDEX_ROOT which is the only one there.
 */
static void ntfs_ir_leafify(ntfs_index_context *icx, INDEX_HEADER *ih)
{
	INDEX_ENTRY *ie;

	ntfs_debug("Entering\n");

	ie = ntfs_ie_get_first(ih);
	ie->flags &= ~INDEX_ENTRY_NODE;
	ie->length = cpu_to_le16(le16_to_cpu(ie->length) - sizeof(VCN));

	ih->index_length = cpu_to_le32(le32_to_cpu(ih->index_length) - sizeof(VCN));
	ih->flags &= ~LARGE_INDEX;
	NInoClearIndexAllocPresent(icx->idx_ni);

	/* Not fatal error */
	ntfs_ir_truncate(icx, le32_to_cpu(ih->index_length));
}

/**
 *  Used if an empty index block to be deleted has END entry as the parent
 *  in the INDEX_ROOT which is not the only one there.
 */
static int ntfs_ih_reparent_end(ntfs_index_context *icx, INDEX_HEADER *ih,
		INDEX_BLOCK *ib)
{
	INDEX_ENTRY *ie, *ie_prev;

	ntfs_debug("Entering\n");

	ie = ntfs_ie_get_by_pos(ih, ntfs_icx_parent_pos(icx));
	ie_prev = ntfs_ie_prev(ih, ie);
	if (!ie_prev)
		return -EIO;
	ntfs_ie_set_vcn(ie, ntfs_ie_get_vcn(ie_prev));

	return ntfs_ih_takeout(icx, ih, ie_prev, ib);
}

static int ntfs_index_rm_leaf(ntfs_index_context *icx)
{
	INDEX_BLOCK *ib = NULL;
	INDEX_HEADER *parent_ih;
	INDEX_ENTRY *ie;
	int ret;

	ntfs_debug("pindex: %d\n", icx->pindex);

	ret = ntfs_icx_parent_dec(icx);
	if (ret)
		return ret;

	ret = ntfs_ibm_clear(icx, icx->parent_vcn[icx->pindex + 1]);
	if (ret)
		return ret;

	if (ntfs_icx_parent_vcn(icx) == VCN_INDEX_ROOT_PARENT)
		parent_ih = &icx->ir->index;
	else {
		ib = ntfs_malloc_nofs(icx->block_size);
		if (!ib)
			return -ENOMEM;

		ret = ntfs_ib_read(icx, ntfs_icx_parent_vcn(icx), ib);
		if (ret)
			goto out;

		parent_ih = &ib->index;
	}

	ie = ntfs_ie_get_by_pos(parent_ih, ntfs_icx_parent_pos(icx));
	if (!ntfs_ie_end(ie)) {
		ret = ntfs_ih_takeout(icx, parent_ih, ie, ib);
		goto out;
	}

	if (ntfs_ih_zero_entry(parent_ih)) {
		if (ntfs_icx_parent_vcn(icx) == VCN_INDEX_ROOT_PARENT) {
			ntfs_ir_leafify(icx, parent_ih);
			goto out;
		}

		ret = ntfs_index_rm_leaf(icx);
		goto out;
	}

	ret = ntfs_ih_reparent_end(icx, parent_ih, ib);
out:
	ntfs_free(ib);
	return ret;
}

static int ntfs_index_rm_node(ntfs_index_context *icx)
{
	int entry_pos, pindex;
	VCN vcn;
	INDEX_BLOCK *ib = NULL;
	INDEX_ENTRY *ie_succ, *ie, *entry = icx->entry;
	INDEX_HEADER *ih;
	u32 new_size;
	int delta, ret;

	ntfs_debug("Entering\n");

	if (!icx->ia_ni) {
		icx->ia_ni = ntfs_ia_open(icx, icx->idx_ni);
		if (!icx->ia_ni)
			return -EINVAL;
	}

	ib = ntfs_malloc_nofs(icx->block_size);
	if (!ib)
		return -ENOMEM;

	ie_succ = ntfs_ie_get_next(icx->entry);
	entry_pos = icx->parent_pos[icx->pindex]++;
	pindex = icx->pindex;
descend:
	vcn = ntfs_ie_get_vcn(ie_succ);
	ret = ntfs_ib_read(icx, vcn, ib);
	if (ret)
		goto out;

	ie_succ = ntfs_ie_get_first(&ib->index);

	ret = ntfs_icx_parent_inc(icx);
	if (ret)
		goto out;

	icx->parent_vcn[icx->pindex] = vcn;
	icx->parent_pos[icx->pindex] = 0;

	if ((ib->index.flags & NODE_MASK) == INDEX_NODE)
		goto descend;

	if (ntfs_ih_zero_entry(&ib->index)) {
		ret = -EIO;
		ntfs_error(icx->idx_ni->vol->sb, "Empty index block");
		goto out;
	}

	ie = ntfs_ie_dup(ie_succ);
	if (!ie) {
		ret = -ENOMEM;
		goto out;
	}

	ret = ntfs_ie_add_vcn(&ie);
	if (ret)
		goto out2;

	ntfs_ie_set_vcn(ie, ntfs_ie_get_vcn(icx->entry));

	if (icx->is_in_root)
		ih = &icx->ir->index;
	else
		ih = &icx->ib->index;

	delta = le16_to_cpu(ie->length) - le16_to_cpu(icx->entry->length);
	new_size = le32_to_cpu(ih->index_length) + delta;
	if (delta > 0) {
		if (icx->is_in_root) {
			ret = ntfs_ir_make_space(icx, new_size);
			if (ret != 0)
				goto out2;

			ih = &icx->ir->index;
			entry = ntfs_ie_get_by_pos(ih, entry_pos);

		} else if (new_size > le32_to_cpu(ih->allocated_size)) {
			icx->pindex = pindex;
			ret = ntfs_ib_split(icx, icx->ib);
			if (!ret)
				ret = -EAGAIN;
			goto out2;
		}
	}

	ntfs_ie_delete(ih, entry);
	ntfs_ie_insert(ih, ie, entry);

	if (icx->is_in_root)
		ret = ntfs_ir_truncate(icx, new_size);
	else
		ret = ntfs_icx_ib_write(icx);
	if (ret)
		goto out2;

	ntfs_ie_delete(&ib->index, ie_succ);

	if (ntfs_ih_zero_entry(&ib->index))
		ret = ntfs_index_rm_leaf(icx);
	else
		ret = ntfs_ib_write(icx, ib);

out2:
	ntfs_free(ie);
out:
	ntfs_free(ib);
	return ret;
}

/**
 * ntfs_index_rm - remove entry from the index
 * @icx:	index context describing entry to delete
 *
 * Delete entry described by @icx from the index. Index context is always
 * reinitialized after use of this function, so it can be used for index
 * lookup once again.
 *
 * Return 0 on success or error with errno set to the error code.
 */
int ntfs_index_rm(ntfs_index_context *icx)
{
	INDEX_HEADER *ih;
	int ret = 0;

	ntfs_debug("Entering\n");

	if (!icx || (!icx->ib && !icx->ir) || ntfs_ie_end(icx->entry)) {
		ret = -EINVAL;
		goto err_out;
	}
	if (icx->is_in_root)
		ih = &icx->ir->index;
	else
		ih = &icx->ib->index;

	if (icx->entry->flags & INDEX_ENTRY_NODE) {
		ret = ntfs_index_rm_node(icx);
		if (ret)
			goto err_out;
	} else if (icx->is_in_root || !ntfs_ih_one_entry(ih)) {
		ntfs_ie_delete(ih, icx->entry);

		if (icx->is_in_root)
			ret = ntfs_ir_truncate(icx, le32_to_cpu(ih->index_length));
		else
			ret = ntfs_icx_ib_write(icx);
		if (ret)
			goto err_out;
	} else {
		ret = ntfs_index_rm_leaf(icx);
		if (ret)
			goto err_out;
	}

	return 0;
err_out:
	return ret;
}

int ntfs_index_remove(ntfs_inode *dir_ni, const void *key, const int keylen)
{
	int ret = 0;
	ntfs_index_context *icx;

	icx = ntfs_index_ctx_get(dir_ni, I30, 4);
	if (!icx)
		return -EINVAL;

	while (1) {
		ret = ntfs_index_lookup(key, keylen, icx);
		if (ret)
			goto err_out;

		ret = ntfs_index_rm(icx);
		if (ret && ret != -EAGAIN)
			goto err_out;
		else if (!ret)
			break;

		mark_mft_record_dirty(icx->actx->ntfs_ino);
		ntfs_index_ctx_reinit(icx);
	}

	mark_mft_record_dirty(icx->actx->ntfs_ino);

	ntfs_index_ctx_put(icx);
	return 0;
err_out:
	ntfs_index_ctx_put(icx);
	ntfs_error(dir_ni->vol->sb, "Delete failed");
	return ret;
}

/*
 * ntfs_index_walk_down - walk down the index tree (leaf bound)
 * until there are no subnode in the first index entry returns
 * the entry at the bottom left in subnode
 */
INDEX_ENTRY *ntfs_index_walk_down(INDEX_ENTRY *ie, ntfs_index_context *ictx)
{
	INDEX_ENTRY *entry;
	s64 vcn;

	entry = ie;
	do {
		vcn = ntfs_ie_get_vcn(entry);
		if (ictx->is_in_root) {
			/* down from level zero */
			ictx->ir = (INDEX_ROOT*)NULL;
			ictx->ib = (INDEX_BLOCK*)ntfs_malloc_nofs(ictx->block_size);
			ictx->pindex = 1;
			ictx->is_in_root = false;
		} else {
			/* down from non-zero level */
			ictx->pindex++;
		}

		ictx->parent_pos[ictx->pindex] = 0;
		ictx->parent_vcn[ictx->pindex] = vcn;
		if (!ntfs_ib_read(ictx, vcn, ictx->ib)) {
			ictx->entry = ntfs_ie_get_first(&ictx->ib->index);
			entry = ictx->entry;
		} else
			entry = (INDEX_ENTRY*)NULL;
	} while (entry && (entry->flags & INDEX_ENTRY_NODE));

	return (entry);
}

/**
 * ntfs_index_walk_up - walk up the index tree (root bound) until
 * there is a valid data entry in parent returns the parent entry
 * or NULL if no more parent.
 */
static INDEX_ENTRY *ntfs_index_walk_up(INDEX_ENTRY *ie,
		ntfs_index_context *ictx)
{
	INDEX_ENTRY *entry;
	s64 vcn;

	entry = ie;
	if (ictx->pindex > 0) {
		do {
			ictx->pindex--;
			if (!ictx->pindex) {
				/* we have reached the root */
				kfree(ictx->ib);
				ictx->ib = (INDEX_BLOCK*)NULL;
				ictx->is_in_root = true;
				/* a new search context is to be allocated */
				if (ictx->actx)
					ntfs_attr_put_search_ctx(ictx->actx);
				ictx->ir = ntfs_ir_lookup(ictx->idx_ni, ictx->name,
						ictx->name_len, &ictx->actx);
				if (ictx->ir)
					entry = ntfs_ie_get_by_pos(&ictx->ir->index,
							ictx->parent_pos[ictx->pindex]);
				else
					entry = (INDEX_ENTRY*)NULL;
			} else {
					/* up into non-root node */
				vcn = ictx->parent_vcn[ictx->pindex];
				if (!ntfs_ib_read(ictx, vcn, ictx->ib)) {
					entry = ntfs_ie_get_by_pos(&ictx->ib->index,
							ictx->parent_pos[ictx->pindex]);
				} else
					entry = (INDEX_ENTRY*)NULL;
			}
		ictx->entry = entry;
		} while (entry && (ictx->pindex > 0) &&
				(entry->flags & INDEX_ENTRY_END));
	} else
		entry = (INDEX_ENTRY*)NULL;

	return (entry);
}

/**
 * ntfs_index_next - get next entry in an index according to collating sequence.
 * Returns next entry or NULL if none.
 *
 * Sample layout :
 *
 *                 +---+---+---+---+---+---+---+---+    n ptrs to subnodes
 *                 |   |   | 10| 25| 33|   |   |   |    n-1 keys in between
 *                 +---+---+---+---+---+---+---+---+    no key in last entry
 *                              | A | A
 *                              | | | +-------------------------------+
 *   +--------------------------+ | +-----+                           |
 *   |                            +--+    |                           |
 *   V                               |    V                           |
 * +---+---+---+---+---+---+---+---+ |  +---+---+---+---+---+---+---+---+
 * | 11| 12| 13| 14| 15| 16| 17|   | |  | 26| 27| 28| 29| 30| 31| 32|   |
 * +---+---+---+---+---+---+---+---+ |  +---+---+---+---+---+---+---+---+
 *                               |   |
 *       +-----------------------+   |
 *       |                           |
 *     +---+---+---+---+---+---+---+---+
 *     | 18| 19| 20| 21| 22| 23| 24|   |
 *     +---+---+---+---+---+---+---+---+
 */
INDEX_ENTRY *ntfs_index_next(INDEX_ENTRY *ie, ntfs_index_context *ictx)
{
	INDEX_ENTRY *next;
	le16 flags;

	/*
	 * lookup() may have returned an invalid node
	 * when searching for a partial key
	 * if this happens, walk up
	 */
	if (ie->flags & INDEX_ENTRY_END)
		next = ntfs_index_walk_up(ie, ictx);
	else {
		/*
		 * get next entry in same node
		 * there is always one after any entry with data
		 */
		next = (INDEX_ENTRY*)((char*)ie + le16_to_cpu(ie->length));
		++ictx->parent_pos[ictx->pindex];
		flags = next->flags;

		/* walk down if it has a subnode */
		if (flags & INDEX_ENTRY_NODE) {
			if (!ictx->ia_ni) {
				ictx->ia_ni = ntfs_ia_open(ictx, ictx->idx_ni);
				BUG_ON(!ictx->ia_ni);
			}

			next = ntfs_index_walk_down(next, ictx);
		} else {

			/* walk up it has no subnode, nor data */
			if (flags & INDEX_ENTRY_END)
				next = ntfs_index_walk_up(next, ictx);
		}
	}

	/* return NULL if stuck at end of a block */
	if (next && (next->flags & INDEX_ENTRY_END))
		next = (INDEX_ENTRY*)NULL;

	return (next);
}
