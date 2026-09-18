/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Exports for attribute list attribute handling.
 * Originated from Linux-NTFS project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 * Copyright (c) 2004 Yura Pakhuchiy
 */

#ifndef _NTFS_ATTRLIST_H
#define _NTFS_ATTRLIST_H

#include "attrib.h"

/**
 * ntfs_attrlist_mark_dirty - set the attribute list dirty
 * @ni:		ntfs inode which base inode contain dirty attribute list
 *
 * Set the attribute list dirty so it is written out later (at the latest at
 * ntfs_inode_close() time).
 *
 * This function cannot fail.
 */
static inline void ntfs_attrlist_mark_dirty(ntfs_inode *ni)
{
	if (ni->nr_extents == -1)
		NInoSetAttrListDirty(ni->ext.base_ntfs_ino);
	else
		NInoSetAttrListDirty(ni);
}

extern int ntfs_attrlist_need(ntfs_inode *ni);
extern int ntfs_attrlist_entry_add(ntfs_inode *ni, ATTR_RECORD *attr);
extern int ntfs_attrlist_entry_rm(ntfs_attr_search_ctx *ctx);
extern int ntfs_attrlist_update(ntfs_inode *base_ni);

#endif /* defined _NTFS_ATTRLIST_H */
