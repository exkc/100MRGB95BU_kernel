/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Defines for runlist handling in NTFS Linux kernel driver.
 * Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 * Copyright (c) 2002 Richard Russon
 */

#ifndef _LINUX_NTFS_RUNLIST_H
#define _LINUX_NTFS_RUNLIST_H

#include "volume.h"

/**
 * runlist_element - in memory vcn to lcn mapping array element
 * @vcn:	starting vcn of the current array element
 * @lcn:	starting lcn of the current array element
 * @length:	length in clusters of the current array element
 *
 * The last vcn (in fact the last vcn + 1) is reached when length == 0.
 *
 * When lcn == -1 this means that the count vcns starting at vcn are not
 * physically allocated (i.e. this is a hole / data is sparse).
 */
typedef struct {	/* In memory vcn to lcn mapping structure element. */
	VCN vcn;	/* vcn = Starting virtual cluster number. */
	LCN lcn;	/* lcn = Starting logical cluster number. */
	s64 length;	/* Run length in clusters. */
} runlist_element;

/**
 * runlist - in memory vcn to lcn mapping array including a read/write lock
 * @rl:		pointer to an array of runlist elements
 * @lock:	read/write spinlock for serializing access to @rl
 *
 */
typedef struct {
	runlist_element *rl;
	struct rw_semaphore lock;
	size_t count;
} runlist;

static inline void ntfs_init_runlist(runlist *rl)
{
	rl->rl = NULL;
	init_rwsem(&rl->lock);
	rl->count = 0;
}

typedef enum {
	LCN_DELALLOC		= -1,
	LCN_HOLE		= -2,
	LCN_RL_NOT_MAPPED	= -3,
	LCN_ENOENT		= -4,
	LCN_ENOMEM		= -5,
	LCN_EIO			= -6,
	LCN_EINVAL		= -7,
} LCN_SPECIAL_VALUES;

extern runlist_element *ntfs_runlists_merge(runlist *d_runlist,
				     runlist_element *srl, size_t s_rl_count,
				     size_t *new_rl_count);

extern runlist_element *ntfs_mapping_pairs_decompress(const ntfs_volume *vol,
		const ATTR_RECORD *attr, runlist *old_runlist,
		size_t *new_rl_count);

extern LCN ntfs_rl_vcn_to_lcn(const runlist_element *rl, const VCN vcn);
extern runlist_element *ntfs_rl_find_vcn_nolock(runlist_element *rl, const VCN vcn);

extern int ntfs_get_size_for_mapping_pairs(const ntfs_volume *vol,
		const runlist_element *rl, const VCN first_vcn,
		const VCN last_vcn, int max_mp_size);

extern int ntfs_mapping_pairs_build(const ntfs_volume *vol, s8 *dst,
		const int dst_len, const runlist_element *rl,
		const VCN first_vcn, const VCN last_vcn, VCN *const stop_vcn,
		runlist_element **stop_rl, unsigned int *de_cluster_count);

extern int ntfs_rl_truncate_nolock(const ntfs_volume *vol,
		runlist *const runlist, const s64 new_length);

int ntfs_rl_punch_nolock(const ntfs_volume *vol, runlist *const runlist,
		const VCN start, const s64 length);

int ntfs_rl_sparse(runlist_element *rl);

s64 ntfs_rl_get_compressed_size(ntfs_volume *vol, runlist_element *rl);
extern runlist_element *ntfs_rl_insert_range(runlist_element *dst_rl, int dst_cnt,
					     runlist_element *src_rl, int src_cnt,
					     size_t *new_cnt);
extern runlist_element *ntfs_rl_punch_hole(runlist_element *dst_rl, int dst_cnt,
					   VCN start_vcn, VCN len,
					   runlist_element **punch_rl,
					   size_t *new_rl_cnt);
extern runlist_element *ntfs_rl_collapse_range(runlist_element *dst_rl, int dst_cnt,
					       VCN start_vcn, VCN len,
					       runlist_element **punch_rl,
					       size_t *new_rl_cnt);

#endif /* _LINUX_NTFS_RUNLIST_H */
