// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * NTFS kernel directory inode operations.
 * Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2006 Anton Altaparmakov
 * Copyright (c) 2024 LG Electronics Co., Ltd.
 * Author(s): Namjae Jeon <linkinjeon@kernel.org>
 */

#include <linux/exportfs.h>
#include <linux/iversion.h>

#include "ntfs.h"
#include "malloc.h"
#include "time.h"
#include "index.h"
#include "security.h"
#include "reparse.h"
#include "ea.h"

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 12, 0)
#include <linux/cred.h>
#endif

static inline int ntfs_check_bad_char(const unsigned short *wc,
		unsigned int wc_len)
{
	int i;

	for (i = 0; i < wc_len; i++) {
		if ((wc[i] < 0x0020) ||
		    (wc[i] == 0x0022) || (wc[i] == 0x002A) || (wc[i] == 0x002F) ||
		    (wc[i] == 0x003A) || (wc[i] == 0x003C) || (wc[i] == 0x003E) ||
		    (wc[i] == 0x003F) || (wc[i] == 0x005C) || (wc[i] == 0x007C))
		    return -EINVAL;
	}

	return 0;
}

/**
 * ntfs_lookup - find the inode represented by a dentry in a directory inode
 * @dir_ino:	directory inode in which to look for the inode
 * @dent:	dentry representing the inode to look for
 * @flags:	lookup flags
 *
 * In short, ntfs_lookup() looks for the inode represented by the dentry @dent
 * in the directory inode @dir_ino and if found attaches the inode to the
 * dentry @dent.
 *
 * In more detail, the dentry @dent specifies which inode to look for by
 * supplying the name of the inode in @dent->d_name.name. ntfs_lookup()
 * converts the name to Unicode and walks the contents of the directory inode
 * @dir_ino looking for the converted Unicode name. If the name is found in the
 * directory, the corresponding inode is loaded by calling ntfs_iget() on its
 * inode number and the inode is associated with the dentry @dent via a call to
 * d_splice_alias().
 *
 * If the name is not found in the directory, a NULL inode is inserted into the
 * dentry @dent via a call to d_add(). The dentry is then termed a negative
 * dentry.
 *
 * Only if an actual error occurs, do we return an error via ERR_PTR().
 *
 * In order to handle the case insensitivity issues of NTFS with regards to the
 * dcache and the dcache requiring only one dentry per directory, we deal with
 * dentry aliases that only differ in case in ->ntfs_lookup() while maintaining
 * a case sensitive dcache. This means that we get the full benefit of dcache
 * speed when the file/directory is looked up with the same case as returned by
 * ->ntfs_readdir() but that a lookup for any other case (or for the short file
 * name) will not find anything in dcache and will enter ->ntfs_lookup()
 * instead, where we search the directory for a fully matching file name
 * (including case) and if that is not found, we search for a file name that
 * matches with different case and if that has non-POSIX semantics we return
 * that. We actually do only one search (case sensitive) and keep tabs on
 * whether we have found a case insensitive match in the process.
 *
 * To simplify matters for us, we do not treat the short vs long filenames as
 * two hard links but instead if the lookup matches a short filename, we
 * return the dentry for the corresponding long filename instead.
 *
 * There are three cases we need to distinguish here:
 *
 * 1) @dent perfectly matches (i.e. including case) a directory entry with a
 *    file name in the WIN32 or POSIX namespaces. In this case
 *    ntfs_lookup_inode_by_name() will return with name set to NULL and we
 *    just d_splice_alias() @dent.
 * 2) @dent matches (not including case) a directory entry with a file name in
 *    the WIN32 namespace. In this case ntfs_lookup_inode_by_name() will return
 *    with name set to point to a kmalloc()ed ntfs_name structure containing
 *    the properly cased little endian Unicode name. We convert the name to the
 *    current NLS code page, search if a dentry with this name already exists
 *    and if so return that instead of @dent.  At this point things are
 *    complicated by the possibility of 'disconnected' dentries due to NFS
 *    which we deal with appropriately (see the code comments).  The VFS will
 *    then destroy the old @dent and use the one we returned.  If a dentry is
 *    not found, we allocate a new one, d_splice_alias() it, and return it as
 *    above.
 * 3) @dent matches either perfectly or not (i.e. we don't care about case) a
 *    directory entry with a file name in the DOS namespace. In this case
 *    ntfs_lookup_inode_by_name() will return with name set to point to a
 *    kmalloc()ed ntfs_name structure containing the mft reference (cpu endian)
 *    of the inode. We use the mft reference to read the inode and to find the
 *    file name in the WIN32 namespace corresponding to the matched short file
 *    name. We then convert the name to the current NLS code page, and proceed
 *    searching for a dentry with this name, etc, as in case 2), above.
 *
 * Locking: Caller must hold i_mutex on the directory.
 */
static struct dentry *ntfs_lookup(struct inode *dir_ino, struct dentry *dent,
		unsigned int flags)
{
	ntfs_volume *vol = NTFS_SB(dir_ino->i_sb);
	struct inode *dent_inode;
	ntfschar *uname;
	ntfs_name *name = NULL;
	MFT_REF mref;
	unsigned long dent_ino;
	int uname_len;

	ntfs_debug("Looking up %pd in directory inode 0x%lx.",
			dent, dir_ino->i_ino);
	/* Convert the name of the dentry to Unicode. */
	uname_len = ntfs_nlstoucs(vol, dent->d_name.name, dent->d_name.len,
				  &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_debug("Failed to convert name to Unicode.");
		return ERR_PTR(uname_len);
	}
	mutex_lock(&NTFS_I(dir_ino)->mrec_lock);
	mref = ntfs_lookup_inode_by_name(NTFS_I(dir_ino), uname, uname_len,
			&name);
	mutex_unlock(&NTFS_I(dir_ino)->mrec_lock);
	kmem_cache_free(ntfs_name_cache, uname);
	if (!IS_ERR_MREF(mref)) {
		dent_ino = MREF(mref);
		ntfs_debug("Found inode 0x%lx. Calling ntfs_iget.", dent_ino);
		dent_inode = ntfs_iget(vol->sb, dent_ino);
		if (!IS_ERR(dent_inode)) {
			/* Consistency check. */
			if (is_bad_inode(dent_inode) || MSEQNO(mref) ==
					NTFS_I(dent_inode)->seq_no ||
					dent_ino == FILE_MFT) {
				/* Perfect WIN32/POSIX match. -- Case 1. */
				if (!name) {
					ntfs_debug("Done.  (Case 1.)");
					return d_splice_alias(dent_inode, dent);
				}
				/*
				 * We are too indented.  Handle imperfect
				 * matches and short file names further below.
				 */
				goto handle_name;
			}
			ntfs_error(vol->sb, "Found stale reference to inode "
					"0x%lx (reference sequence number = "
					"0x%x, inode sequence number = 0x%x), "
					"returning -EIO. Run chkdsk.",
					dent_ino, MSEQNO(mref),
					NTFS_I(dent_inode)->seq_no);
			iput(dent_inode);
			dent_inode = ERR_PTR(-EIO);
		} else
			ntfs_error(vol->sb, "ntfs_iget(0x%lx) failed with "
					"error code %li.", dent_ino,
					PTR_ERR(dent_inode));
		kfree(name);
		/* Return the error code. */
		return ERR_CAST(dent_inode);
	}
	/* It is guaranteed that @name is no longer allocated at this point. */
	if (MREF_ERR(mref) == -ENOENT) {
		ntfs_debug("Entry was not found, adding negative dentry.");
		/* The dcache will handle negative entries. */
		d_add(dent, NULL);
		ntfs_debug("Done.");
		return NULL;
	}
	ntfs_error(vol->sb, "ntfs_lookup_ino_by_name() failed with error "
			"code %i.", -MREF_ERR(mref));
	return ERR_PTR(MREF_ERR(mref));
	// TODO: Consider moving this lot to a separate function! (AIA)
handle_name:
	{
		MFT_RECORD *m;
		ntfs_attr_search_ctx *ctx;
		ntfs_inode *ni = NTFS_I(dent_inode);
		int err;
		struct qstr nls_name;

		nls_name.name = NULL;
		if (name->type != FILE_NAME_DOS) {			/* Case 2. */
			ntfs_debug("Case 2.");
			nls_name.len = (unsigned)ntfs_ucstonls(vol,
					(ntfschar*)&name->name, name->len,
					(unsigned char**)&nls_name.name, 0);
			kfree(name);
		} else /* if (name->type == FILE_NAME_DOS) */ {		/* Case 3. */
			FILE_NAME_ATTR *fn;

			ntfs_debug("Case 3.");
			kfree(name);

			/* Find the WIN32 name corresponding to the matched DOS name. */
			ni = NTFS_I(dent_inode);
			m = map_mft_record(ni);
			if (IS_ERR(m)) {
				err = PTR_ERR(m);
				m = NULL;
				ctx = NULL;
				goto err_out;
			}
			ctx = ntfs_attr_get_search_ctx(ni, m);
			if (unlikely(!ctx)) {
				err = -ENOMEM;
				goto err_out;
			}
			do {
				ATTR_RECORD *a;
				u32 val_len;

				err = ntfs_attr_lookup(AT_FILE_NAME, NULL, 0, 0, 0,
						NULL, 0, ctx);
				if (unlikely(err)) {
					ntfs_error(vol->sb, "Inode corrupt: No WIN32 "
							"namespace counterpart to DOS "
							"file name. Run chkdsk.");
					if (err == -ENOENT)
						err = -EIO;
					goto err_out;
				}
				/* Consistency checks. */
				a = ctx->attr;
				if (a->non_resident || a->flags)
					goto eio_err_out;
				val_len = le32_to_cpu(a->data.resident.value_length);
				if (le16_to_cpu(a->data.resident.value_offset) +
						val_len > le32_to_cpu(a->length))
					goto eio_err_out;
				fn = (FILE_NAME_ATTR*)((u8*)ctx->attr + le16_to_cpu(
							ctx->attr->data.resident.value_offset));
				if ((u32)(fn->file_name_length * sizeof(ntfschar) +
							sizeof(FILE_NAME_ATTR)) > val_len)
					goto eio_err_out;
			} while (fn->file_name_type != FILE_NAME_WIN32);

			/* Convert the found WIN32 name to current NLS code page. */
			nls_name.len = (unsigned int)ntfs_ucstonls(vol,
					(ntfschar*)&fn->file_name, fn->file_name_length,
					(unsigned char**)&nls_name.name, 0);

			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(ni);
		}
		m = NULL;
		ctx = NULL;

		/* Check if a conversion error occurred. */
		if ((int)nls_name.len < 0) {
			err = (int)nls_name.len;
			goto err_out;
		}
		nls_name.hash = full_name_hash(dent, nls_name.name, nls_name.len);

		dent = d_add_ci(dent, dent_inode, &nls_name);
		kfree(nls_name.name);
		return dent;

eio_err_out:
		ntfs_error(vol->sb, "Illegal file name attribute. Run chkdsk.");
		err = -EIO;
err_out:
		if (ctx)
			ntfs_attr_put_search_ctx(ctx);
		if (m)
			unmap_mft_record(ni);
		iput(dent_inode);
		ntfs_error(vol->sb, "Failed, returning error code %i.", err);
		return ERR_PTR(err);
	}
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static ntfs_inode *__ntfs_create(struct mnt_idmap *idmap, struct inode *dir,
		ntfschar *name, u8 name_len, mode_t mode, dev_t dev,
		ntfschar *target, int target_len)
#else
static ntfs_inode *__ntfs_create(struct user_namespace *mnt_userns, struct inode *dir,
		ntfschar *name, u8 name_len, mode_t mode, dev_t dev,
		ntfschar *target, int target_len)
#endif
#else
static ntfs_inode *__ntfs_create(struct inode *dir,
		ntfschar *name, u8 name_len, mode_t mode, dev_t dev,
		ntfschar *target, int target_len)
#endif
{
	ntfs_inode *dir_ni = NTFS_I(dir);
	ntfs_volume *vol = dir_ni->vol;
	ntfs_inode *ni;
	int rollback_data = 0, rollback_sd = 0;
	FILE_NAME_ATTR *fn = NULL;
	STANDARD_INFORMATION *si = NULL;
	int err = 0, fn_len, si_len;
	struct inode *vi;
	MFT_RECORD *ni_mrec, *dni_mrec;
	struct super_block *sb = dir_ni->vol->sb;
	leMFT_REF parent_mft_ref;
	MFT_REF child_mft_ref;
	__le16 ea_size;

	vi = new_inode(vol->sb);
	if (!vi)
		return ERR_PTR(-ENOMEM);

	ntfs_init_big_inode(vi);
	ni = NTFS_I(vi);
	ni->vol = dir_ni->vol;
	ni->name_len = 0;
	ni->name = NULL;

	/*
	 * Set the appropriate mode, attribute type, and name.  For
	 * directories, also setup the index values to the defaults.
	 */
	if (S_ISDIR(mode)) {
		mode = S_IFDIR | S_IRWXUGO;
		mode &= ~vol->dmask;

		NInoSetMstProtected(ni);
		ni->itype.index.block_size = 4096;
		ni->itype.index.block_size_bits = ntfs_ffs(4096) - 1;
		ni->itype.index.collation_rule = COLLATION_FILE_NAME;
		if (vol->cluster_size <= ni->itype.index.block_size) {
			ni->itype.index.vcn_size = vol->cluster_size;
			ni->itype.index.vcn_size_bits =
				vol->cluster_size_bits;
		} else {
			ni->itype.index.vcn_size = vol->sector_size;
			ni->itype.index.vcn_size_bits =
				vol->sector_size_bits;
		}
	} else {
		mode = S_IFREG | S_IRWXUGO;
		mode &= ~vol->fmask;
	}

	if (IS_RDONLY(vi))
		mode &= ~S_IWUGO;

	vi->i_uid = vol->uid;
	vi->i_gid = vol->gid;
	vi->i_mode = mode;

	/*
	 * Set the file size to 0, the ntfs inode sizes are set to 0 by
	 * the call to ntfs_init_big_inode() below.
	 */
	vi->i_size = 0;
	vi->i_blocks = 0;

	inode_inc_iversion(vi);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 6, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	simple_inode_init_ts(vi);
	ni->i_crtime = inode_get_ctime(vi);
#else
	ni->i_crtime = vi->i_mtime = vi->i_atime = inode_set_ctime_current(vi);
#endif
#else
	ni->i_crtime = vi->i_mtime = vi->i_atime = vi->i_ctime = current_time(vi);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	inode_set_mtime_to_ts(dir, ni->i_crtime);
	inode_set_ctime_to_ts(dir, ni->i_crtime);
#else
	dir->i_mtime = dir->i_ctime = ni->i_crtime;
#endif
	mark_inode_dirty(dir);

	err = ntfs_mft_record_alloc(dir_ni->vol, mode, &ni, NULL,
				    &ni_mrec);
	if (err) {
		iput(vi);
		return ERR_PTR(err);
	}

	/*
	 * Prevent iget and writeback from finding this inode.
	 * Caller must call d_instantiate_new instead of d_instantiate.
	 */
	spin_lock(&vi->i_lock);
	vi->i_state = I_NEW | I_CREATING;
	spin_unlock(&vi->i_lock);

	/* Add the inode to the inode hash for the superblock. */
	vi->i_ino = ni->mft_no;
	inode_set_iversion(vi, 1);
	insert_inode_hash(vi);

	mutex_lock_nested(&ni->mrec_lock, NTFS_INODE_MUTEX_NORMAL);
	mutex_lock_nested(&dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT);
	if (NInoBeingDeleted(dir_ni)) {
		err = -ENOENT;
		goto err_out;
	}

	dni_mrec = map_mft_record(dir_ni);
	if (IS_ERR(dni_mrec)) {
		ntfs_error(dir_ni->vol->sb, "failed to map mft record for file %ld.\n",
			   dir_ni->mft_no);
		err = -EIO;
		goto err_out;
	}
	parent_mft_ref = MK_LE_MREF(dir_ni->mft_no,
				    le16_to_cpu(dni_mrec->sequence_number));
	unmap_mft_record(dir_ni);

	/*
	 * Create STANDARD_INFORMATION attribute. Write STANDARD_INFORMATION
	 * version 1.2, windows will upgrade it to version 3 if needed.
	 */
	si_len = offsetof(STANDARD_INFORMATION, file_attributes) +
		sizeof(FILE_ATTR_FLAGS) + 12;
	si = ntfs_malloc_nofs(si_len);
	if (!si) {
		err = -ENOMEM;
		goto err_out;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	si->creation_time = si->last_data_change_time = utc2ntfs(ni->i_crtime);
#else
	si->creation_time = si->last_data_change_time = utc2ntfs(ni->i_crtime);
#endif
	si->last_mft_change_time = si->last_access_time = si->creation_time;

	if (!S_ISREG(mode) && !S_ISDIR(mode))
		si->file_attributes = FILE_ATTR_SYSTEM;

	/* Add STANDARD_INFORMATION to inode. */
	err = ntfs_attr_add(ni, AT_STANDARD_INFORMATION, AT_UNNAMED, 0, (u8*)si,
			si_len);
	if (err) {
		ntfs_error(sb, "Failed to add STANDARD_INFORMATION attribute.\n");
		goto err_out;
	}

	err = ntfs_sd_add_everyone(ni);
	if (err)
		goto err_out;
	rollback_sd = 1;

	if (S_ISDIR(mode)) {
		INDEX_ROOT *ir = NULL;
		INDEX_ENTRY *ie;
		int ir_len, index_len;

		/* Create INDEX_ROOT attribute. */
		index_len = sizeof(INDEX_HEADER) + sizeof(INDEX_ENTRY_HEADER);
		ir_len = offsetof(INDEX_ROOT, index) + index_len;
		ir = ntfs_malloc_nofs(ir_len);
		if (!ir) {
			err = -ENOMEM;
			goto err_out;
		}
		ir->type = AT_FILE_NAME;
		ir->collation_rule = COLLATION_FILE_NAME;
		ir->index_block_size = cpu_to_le32(ni->vol->index_record_size);
		if (ni->vol->cluster_size <= ni->vol->index_record_size)
			ir->clusters_per_index_block =
				ni->vol->index_record_size >>
				ni->vol->cluster_size_bits;
		else
			ir->clusters_per_index_block =
				ni->vol->index_record_size >>
				ni->vol->sector_size_bits;
		ir->index.entries_offset = cpu_to_le32(sizeof(INDEX_HEADER));
		ir->index.index_length = cpu_to_le32(index_len);
		ir->index.allocated_size = cpu_to_le32(index_len);
		ie = (INDEX_ENTRY*)((u8*)ir + sizeof(INDEX_ROOT));
		ie->length = cpu_to_le16(sizeof(INDEX_ENTRY_HEADER));
		ie->key_length = 0;
		ie->flags = INDEX_ENTRY_END;

		/* Add INDEX_ROOT attribute to inode. */
		err = ntfs_attr_add(ni, AT_INDEX_ROOT, I30, 4, (u8*)ir, ir_len);
		if (err) {
			ntfs_free(ir);
			ntfs_error(vi->i_sb, "Failed to add INDEX_ROOT attribute.\n");
			goto err_out;
		}
		ntfs_free(ir);
		err = ntfs_attr_open(ni, AT_INDEX_ROOT, I30, 4);
		if (err)
			goto err_out;
	} else {
		/* Add DATA attribute to inode. */
		err = ntfs_attr_add(ni, AT_DATA, AT_UNNAMED, 0, NULL, 0);
		if (err) {
			ntfs_error(dir_ni->vol->sb, "Failed to add DATA attribute.\n");
			goto err_out;
		}
		rollback_data = 1;

		err = ntfs_attr_open(ni, AT_DATA, AT_UNNAMED, 0);
		if (err)
			goto err_out;

		if (S_ISLNK(mode)) {
			err = ntfs_reparse_set_wsl_symlink(ni, target, target_len);
		} else if (S_ISBLK(mode) || S_ISCHR(mode) || S_ISSOCK(mode) ||
			   S_ISFIFO(mode)) {
			si->file_attributes = FILE_ATTRIBUTE_RECALL_ON_OPEN;
			ni->flags = FILE_ATTRIBUTE_RECALL_ON_OPEN;
			err = ntfs_reparse_set_wsl_not_symlink(ni, mode);
		}
		if (err)
			goto err_out;
	}

	/* Create FILE_NAME attribute. */
	fn_len = sizeof(FILE_NAME_ATTR) + name_len * sizeof(ntfschar);
	fn = ntfs_malloc_nofs(fn_len);
	if (!fn) {
		err = -ENOMEM;
		goto err_out;
	}

	fn->parent_directory = parent_mft_ref;
	fn->file_name_length = name_len;
	fn->file_name_type = FILE_NAME_POSIX;
	fn->type.ea.packed_ea_size = ea_size;
	if (S_ISDIR(mode)) {
		fn->file_attributes = FILE_ATTR_DUP_FILE_NAME_INDEX_PRESENT;
		fn->allocated_size = fn->data_size = 0;
	} else {
		fn->data_size = cpu_to_sle64(ni->data_size);
		fn->allocated_size = cpu_to_sle64(ni->allocated_size);
	}
	if (!S_ISREG(mode) && !S_ISDIR(mode))
		fn->file_attributes = FILE_ATTR_SYSTEM;
	fn->creation_time = fn->last_data_change_time = utc2ntfs(ni->i_crtime);
	fn->last_mft_change_time = fn->last_access_time = fn->creation_time;
	memcpy(fn->file_name, name, name_len * sizeof(ntfschar));

	/* Add FILE_NAME attribute to inode. */
	err = ntfs_attr_add(ni, AT_FILE_NAME, AT_UNNAMED, 0, (u8*)fn, fn_len);
	if (err) {
		ntfs_error(sb, "Failed to add FILE_NAME attribute.\n");
		goto err_out;
	}

	child_mft_ref = MK_MREF(ni->mft_no,
				le16_to_cpu(ni_mrec->sequence_number));
	/* Set hard links count and directory flag. */
	ni_mrec->link_count = cpu_to_le16(1);
	mark_mft_record_dirty(ni);

	/* Add FILE_NAME attribute to index. */
	err = ntfs_index_add_filename(dir_ni, fn, child_mft_ref);
	if (err) {
		ntfs_error(sb, "Failed to add entry to the index");
		goto err_out;
	}

	unmap_mft_record(ni);
	mutex_unlock(&dir_ni->mrec_lock);
	mutex_unlock(&ni->mrec_lock);

	/* Set the sequence number. */
	vi->i_generation = ni->seq_no;
	set_nlink(vi, 1);
	if (S_ISDIR(mode)) {
		vi->i_op = &ntfs_dir_inode_ops;
		vi->i_fop = &ntfs_dir_ops;
		vi->i_mapping->a_ops = &ntfs_normal_aops;
	} else if (S_ISLNK(mode)) {
		vi->i_op = &ntfs_symlink_inode_operations;
		vi->i_mapping->a_ops = &ntfs_normal_aops;
	} else if (S_ISCHR(mode) || S_ISBLK(mode) || S_ISFIFO(mode) || S_ISSOCK(mode)) {
		vi->i_op = &ntfs_special_inode_operations;
		init_special_inode(vi, vi->i_mode, dev);
	} else {
		vi->i_op = &ntfs_file_inode_ops;
		vi->i_fop = &ntfs_file_ops;
		vi->i_mapping->a_ops = &ntfs_normal_aops;
	}

#ifdef CONFIG_NTFS_FS_POSIX_ACL
	if (!S_ISLNK(mode) && (sb->s_flags & SB_POSIXACL)) {
		err = ntfs_init_acl(idmap, vi, dir);
		if (err)
			goto err_out;
	} else
#endif
	{
		vi->i_flags |= S_NOSEC;
	}

	/* Done! */
	ntfs_free(fn);
	ntfs_free(si);
	ntfs_debug("Done.\n");
	return ni;

err_out:
	ntfs_error(sb, "Failed %d.\n", err);

	if (rollback_sd)
		ntfs_attr_remove(ni, AT_SECURITY_DESCRIPTOR, AT_UNNAMED, 0);

	if (rollback_data)
		ntfs_attr_remove(ni, AT_DATA, AT_UNNAMED, 0);
	/*
	 * Free extent MFT records (should not exist any with current
	 * ntfs_create implementation, but for any case if something will be
	 * changed in the future).
	 */
	while (ni->nr_extents != 0) {
		int err2;

		err2 = ntfs_mft_record_free(ni->vol, *(ni->ext.extent_ntfs_inos));
		if (err2)
			ntfs_error(sb, "Failed to free extent MFT record. Leaving inconsistent metadata.\n");
		ntfs_ext_inode_close(*(ni->ext.extent_ntfs_inos));
	}
	if (ntfs_mft_record_free(ni->vol, ni))
		ntfs_error(sb, "Failed to free MFT record. Leaving inconsistent metadata. Run chkdsk.\n");
	unmap_mft_record(ni);
	ntfs_free(fn);
	ntfs_free(si);

	mutex_unlock(&dir_ni->mrec_lock);
	mutex_unlock(&ni->mrec_lock);

	remove_inode_hash(vi);
	discard_new_inode(vi);
	return ERR_PTR(err);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static int ntfs_create(struct mnt_idmap *idmap, struct inode *dir,
		struct dentry *dentry, umode_t mode, bool excl)
#else
static int ntfs_create(struct user_namespace *mnt_userns, struct inode *dir,
		struct dentry *dentry, umode_t mode, bool excl)
#endif
#else
static int ntfs_create(struct inode *dir, struct dentry *dentry, umode_t mode,
		bool excl)
#endif
{
	ntfs_volume *vol = NTFS_SB(dir->i_sb);
	ntfs_inode *ni;
	ntfschar *uname;
	int uname_len, err;

	if (NVolShutdown(vol))
		return -EIO;

	uname_len = ntfs_nlstoucs(vol, dentry->d_name.name, dentry->d_name.len,
				  &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_error(vol->sb, "Failed to convert name to unicode.");
		return uname_len;
	}

	err = ntfs_check_bad_char(uname, uname_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, uname);
		return err;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
	ni = __ntfs_create(idmap, dir, uname, uname_len, S_IFREG | mode, 0, NULL, 0);
#else
	ni = __ntfs_create(mnt_userns, dir, uname, uname_len, S_IFREG | mode, 0, NULL, 0);
#endif
#else
	ni = __ntfs_create(dir, uname, uname_len, S_IFREG | mode, 0, NULL, 0);
#endif
	kmem_cache_free(ntfs_name_cache, uname);
	if (IS_ERR(ni))
		return PTR_ERR(ni);

	d_instantiate_new(dentry, VFS_I(ni));

	return 0;
}

static int ntfs_check_unlinkable_dir(ntfs_attr_search_ctx *ctx, FILE_NAME_ATTR *fn)
{
	int link_count;
	int ret;
	ntfs_inode *ni = ctx->base_ntfs_ino ? ctx->base_ntfs_ino : ctx->ntfs_ino;
	MFT_RECORD *ni_mrec = ctx->base_mrec ? ctx->base_mrec : ctx->mrec;

	ret = ntfs_check_empty_dir(ni, ni_mrec);
	if (!ret || ret != -ENOTEMPTY)
		return ret;

	link_count = le16_to_cpu(ni_mrec->link_count);
	/*
	 * Directory is non-empty, so we can unlink only if there is more than
	 * one "real" hard link, i.e. links aren't different DOS and WIN32 names
	 */
	if ((link_count == 1) ||
	    (link_count == 2 && fn->file_name_type == FILE_NAME_DOS)) {
		ret = -ENOTEMPTY;
		ntfs_debug("Non-empty directory without hard links\n");
		goto no_hardlink;
	}

	ret = 0;
no_hardlink:
	return ret;
}

static int ntfs_test_inode_attr(struct inode *vi, void *data)
{
	ntfs_inode *ni = NTFS_I(vi);
	unsigned long mft_no = (unsigned long)data;

	if (ni->mft_no != mft_no)
		return 0;
	if (NInoAttr(ni) || ni->nr_extents == -1)
		return 1;
	else
		return 0;
}

/**
 * ntfs_delete - delete file or directory from ntfs volume
 * @ni:         ntfs inode for object to delte
 * @dir_ni:     ntfs inode for directory in which delete object
 * @name:       unicode name of the object to delete
 * @name_len:   length of the name in unicode characters
 *
 * @ni is always closed after the call to this function (even if it failed),
 * user does not need to call ntfs_inode_close himself.
 */
static int ntfs_delete(ntfs_inode *ni, ntfs_inode *dir_ni, ntfschar *name, u8 name_len)
{
	ntfs_attr_search_ctx *actx = NULL;
	FILE_NAME_ATTR *fn = NULL;
	bool looking_for_dos_name = false, looking_for_win32_name = false;
	bool case_sensitive_match = true;
	int err = 0;
	MFT_RECORD *ni_mrec;
	mode_t type;
	struct super_block *sb;
	struct inode *vi = VFS_I(ni);

	ntfs_debug("Entering.\n");

	type = vi->i_mode;
	sb = dir_ni->vol->sb;

	if (ni->nr_extents == -1)
		ni = ni->ext.base_ntfs_ino;
	if (dir_ni->nr_extents == -1)
		dir_ni = dir_ni->ext.base_ntfs_ino;
	/*
	 * Search for FILE_NAME attribute with such name. If it's in POSIX or
	 * WIN32_AND_DOS namespace, then simply remove it from index and inode.
	 * If filename in DOS or in WIN32 namespace, then remove DOS name first,
	 * only then remove WIN32 name.
	 */
	actx = ntfs_attr_get_search_ctx(ni, NULL);
	if (!actx) {
		ntfs_error(sb, "%s, Failed to get search context", __FUNCTION__);
		return -ENOMEM;
	}
search:
	while ((err = ntfs_attr_lookup(AT_FILE_NAME, AT_UNNAMED, 0, CASE_SENSITIVE,
				0, NULL, 0, actx)) == 0) {
#ifdef DEBUG
		unsigned char *s;
#endif
		bool case_sensitive = IGNORE_CASE;

		fn = (FILE_NAME_ATTR*)((u8*)actx->attr +
				le16_to_cpu(actx->attr->data.resident.value_offset));
#ifdef DEBUG
		s = ntfs_attr_name_get(ni->vol, fn->file_name, fn->file_name_length);
		ntfs_debug("name: '%s'  type: %d  dos: %d  win32: %d  "
				"case: %d\n", s, fn->file_name_type,
				looking_for_dos_name, looking_for_win32_name,
				case_sensitive_match);
		ntfs_attr_name_free(&s);
#endif
		if (looking_for_dos_name) {
			if (fn->file_name_type == FILE_NAME_DOS)
				break;
			continue;
		}
		if (looking_for_win32_name) {
			if  (fn->file_name_type == FILE_NAME_WIN32)
				break;
			continue;
		}

		/* Ignore hard links from other directories */
		if (dir_ni->mft_no != MREF_LE(fn->parent_directory)) {
			ntfs_debug("MFT record numbers don't match "
					"(%lu != %lu)\n", dir_ni->mft_no,
					MREF_LE(fn->parent_directory));
			continue;
		}

		if (fn->file_name_type == FILE_NAME_POSIX || case_sensitive_match)
			case_sensitive = CASE_SENSITIVE;

		if (ntfs_names_are_equal(fn->file_name, fn->file_name_length,
					name, name_len, case_sensitive,
					ni->vol->upcase, ni->vol->upcase_len)) {
			if (fn->file_name_type == FILE_NAME_WIN32) {
				looking_for_dos_name = true;
				ntfs_attr_reinit_search_ctx(actx);
				continue;
			}
			if (fn->file_name_type == FILE_NAME_DOS)
				looking_for_dos_name = true;
			break;
		}
	}
	if (err) {
		/*
		 * If case sensitive search failed, then try once again
		 * ignoring case.
		 */
		if (err == -ENOENT && case_sensitive_match) {
			case_sensitive_match = false;
			ntfs_attr_reinit_search_ctx(actx);
			goto search;
		}
		goto err_out;
	}

	err = ntfs_check_unlinkable_dir(actx, fn);
	if (err)
		goto err_out;

	err = ntfs_index_remove(dir_ni, fn, le32_to_cpu(actx->attr->data.resident.value_length));
	if (err)
		goto err_out;

	err = ntfs_attr_record_rm(actx);
	if (err)
		goto err_out;

	ni_mrec = actx->base_mrec ? actx->base_mrec : actx->mrec;
	ni_mrec->link_count = cpu_to_le16(le16_to_cpu(ni_mrec->link_count) - 1);
	drop_nlink(VFS_I(ni));

	mark_mft_record_dirty(ni);
	if (looking_for_dos_name) {
		looking_for_dos_name = false;
		looking_for_win32_name = true;
		ntfs_attr_reinit_search_ctx(actx);
		goto search;
	}

	/* TODO: Update object id, quota and securiry indexes if required. */
	/*
	 * If hard link count is not equal to zero then we are done. In other
	 * case there are no reference to this inode left, so we should free all
	 * non-resident attributes and mark all MFT record as not in use.
	 */
	if (ni_mrec->link_count == 0) {
		struct inode *attr_vi;

		NInoSetBeingDeleted(ni);
		ntfs_delete_reparse_index(ni);

		while ((attr_vi = ilookup5(sb, ni->mft_no, ntfs_test_inode_attr,
					   (void *)ni->mft_no)) != NULL) {
			clear_nlink(attr_vi);
			iput(attr_vi);
		}
	}

	ntfs_attr_put_search_ctx(actx);
	ntfs_debug("Done.\n");
	return 0;
err_out:
	ntfs_attr_put_search_ctx(actx);
	return err;
}

static int ntfs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct inode *vi = dentry->d_inode;
	struct super_block *sb = dir->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	int err = 0;
	ntfs_inode *ni = NTFS_I(vi);
	ntfs_inode *dir_ni = NTFS_I(dir);
	ntfschar *uname = NULL;
	int uname_len;

	if (NVolShutdown(vol))
		return -EIO;

	uname_len = ntfs_nlstoucs(vol, dentry->d_name.name, dentry->d_name.len,
				  &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to Unicode.");
		return -ENOMEM;
	}

	err = ntfs_check_bad_char(uname, uname_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, uname);
		return err;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

	mutex_lock_nested(&ni->mrec_lock, NTFS_INODE_MUTEX_NORMAL);
	mutex_lock_nested(&dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT);
	err = ntfs_delete(ni, NTFS_I(dir), uname, uname_len);
	if (err)
		goto out;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	inode_set_mtime_to_ts(dir, inode_set_ctime_current(dir));
	mark_inode_dirty(dir);
	inode_set_ctime_to_ts(vi, inode_get_ctime(dir));
	if (vi->i_nlink)
		mark_inode_dirty(vi);
#else
	vi->i_mtime = vi->i_atime = current_time(vi);
#endif
out:
	kmem_cache_free(ntfs_name_cache, uname);
	mutex_unlock(&dir_ni->mrec_lock);
	mutex_unlock(&ni->mrec_lock);

	return err;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static int ntfs_mkdir(struct mnt_idmap *idmap, struct inode *dir,
		struct dentry *dentry, umode_t mode)
#else
static int ntfs_mkdir(struct user_namespace *mnt_userns, struct inode *dir,
		struct dentry *dentry, umode_t mode)
#endif
#else
static int ntfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
#endif
{
	struct super_block *sb = dir->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	int err = 0;
	ntfs_inode *ni;
	ntfschar *uname;
	int uname_len;

	if (NVolShutdown(vol))
		return -EIO;

	uname_len = ntfs_nlstoucs(vol, dentry->d_name.name, dentry->d_name.len,
				  &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to unicode.");
		return -ENOMEM;
	}

	err = ntfs_check_bad_char(uname, uname_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, uname);
		return err;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
	ni = __ntfs_create(idmap, dir, uname, uname_len, S_IFDIR | mode, 0, NULL, 0);
#else
	ni = __ntfs_create(mnt_userns, dir, uname, uname_len, S_IFDIR | mode, 0, NULL, 0);
#endif
#else
	ni = __ntfs_create(dir, uname, uname_len, S_IFDIR | mode, 0, NULL, 0);
#endif
	kmem_cache_free(ntfs_name_cache, uname);
	if (IS_ERR(ni)) {
		err = PTR_ERR(ni);
		goto out;
	}

	d_instantiate_new(dentry, VFS_I(ni));
out:
	return err;
}

static int ntfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *vi = dentry->d_inode;
	struct super_block *sb = dir->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	int err = 0;
	ntfs_inode *ni, *dir_ni = NTFS_I(dir);
	ntfschar *uname = NULL;
	int uname_len;

	if (NVolShutdown(vol))
		return -EIO;

	ni = NTFS_I(vi);
	uname_len = ntfs_nlstoucs(vol, dentry->d_name.name, dentry->d_name.len,
				  &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to unicode.");
		return -ENOMEM;
	}

	err = ntfs_check_bad_char(uname, uname_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, uname);
		return err;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

	mutex_lock_nested(&ni->mrec_lock, NTFS_INODE_MUTEX_NORMAL);
	mutex_lock_nested(&dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT);
	err = ntfs_delete(ni, NTFS_I(dir), uname, uname_len);
	if (err)
		goto out;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	inode_set_mtime_to_ts(vi, inode_set_atime_to_ts(vi, current_time(vi)));
#else
	vi->i_mtime = vi->i_atime = current_time(vi);
#endif
out:
	kmem_cache_free(ntfs_name_cache, uname);
	mutex_unlock(&dir_ni->mrec_lock);
	mutex_unlock(&ni->mrec_lock);

	return err;
}

/**
 * __ntfs_link - create hard link for file or directory
 * @ni:		ntfs inode for object to create hard link
 * @dir_ni:	ntfs inode for directory in which new link should be placed
 * @name:	unicode name of the new link
 * @name_len:	length of the name in unicode characters
 *
 * NOTE: At present we allow creating hardlinks to directories, we use them
 * in a temporary state during rename. But it's defenitely bad idea to have
 * hard links to directories as a result of operation.
 */
static int __ntfs_link(ntfs_inode *ni, ntfs_inode *dir_ni, ntfschar *name, u8 name_len)
{
	struct super_block *sb;
	struct inode *vi = VFS_I(ni);
	FILE_NAME_ATTR *fn = NULL;
	int fn_len, err = 0;
	MFT_RECORD *dir_mrec = NULL, *ni_mrec = NULL;
	mode_t type;

	ntfs_debug("Entering.\n");

	sb = dir_ni->vol->sb;
	if (NInoBeingDeleted(dir_ni) || NInoBeingDeleted(ni))
		return -ENOENT;

	type = VFS_I(ni)->i_mode;

	ni_mrec = map_mft_record(ni);
	if (IS_ERR(ni_mrec)) {
		err = -EIO;
		goto err_out;
	}

	if (le16_to_cpu(ni_mrec->link_count) == 0) {
		err = -ENOENT;
		goto err_out;
	}

	/* Create FILE_NAME attribute. */
	fn_len = sizeof(FILE_NAME_ATTR) + name_len * sizeof(ntfschar);
	fn = ntfs_malloc_nofs(fn_len);
	if (!fn) {
		err = -ENOMEM;
		goto err_out;
	}

	dir_mrec = map_mft_record(dir_ni);
	if (IS_ERR(dir_mrec)) {
		err = -EIO;
		goto err_out;
	}

	fn->parent_directory = MK_LE_MREF(dir_ni->mft_no,
			le16_to_cpu(dir_mrec->sequence_number));
	unmap_mft_record(dir_ni);
	fn->file_name_length = name_len;
	fn->file_name_type = FILE_NAME_POSIX;
	fn->file_attributes = ni->flags;
	if (ni_mrec->flags & MFT_RECORD_IS_DIRECTORY) {
		fn->file_attributes |= FILE_ATTR_DUP_FILE_NAME_INDEX_PRESENT;
		fn->allocated_size = fn->data_size = 0;
	} else {
		if (NInoSparse(ni))
			fn->allocated_size =
				cpu_to_sle64(ni->itype.compressed.size);
		else
			fn->allocated_size = cpu_to_sle64(ni->allocated_size);
		fn->data_size = cpu_to_sle64(ni->data_size);
	}

	fn->creation_time = utc2ntfs(ni->i_crtime);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 6, 0)
	fn->last_data_change_time = utc2ntfs(inode_get_mtime(vi));
	fn->last_mft_change_time = utc2ntfs(inode_get_ctime(vi));
	fn->last_access_time = utc2ntfs(inode_get_atime(vi));
#else
	fn->last_data_change_time = utc2ntfs(vi->i_mtime);
	fn->last_mft_change_time = utc2ntfs(vi->i_ctime);
	fn->last_access_time = utc2ntfs(vi->i_atime);
#endif
	memcpy(fn->file_name, name, name_len * sizeof(ntfschar));

	/* Add FILE_NAME attribute to index. */
	err = ntfs_index_add_filename(dir_ni, fn, MK_MREF(ni->mft_no,
					le16_to_cpu(ni_mrec->sequence_number)));
	if (err) {
		ntfs_error(sb, "Failed to add filename to the index");
		goto err_out;
	}
	/* Add FILE_NAME attribute to inode. */
	err = ntfs_attr_add(ni, AT_FILE_NAME, AT_UNNAMED, 0, (u8*)fn, fn_len);
	if (err) {
		ntfs_error(sb, "Failed to add FILE_NAME attribute.\n");
		/* Try to remove just added attribute from index. */
		if (ntfs_index_remove(dir_ni, fn, fn_len))
			goto rollback_failed;
		goto err_out;
	}
	/* Increment hard links count. */
	ni_mrec->link_count = cpu_to_le16(le16_to_cpu(ni_mrec->link_count) + 1);
	inc_nlink(VFS_I(ni));

	/* Done! */
	mark_mft_record_dirty(ni);
	ntfs_free(fn);
	unmap_mft_record(ni);

	ntfs_debug("Done.\n");

	return 0;
rollback_failed:
	ntfs_error(sb, "Rollback failed. Leaving inconsistent metadata.\n");
err_out:
	ntfs_free(fn);
	if (!IS_ERR_OR_NULL(ni_mrec))
		unmap_mft_record(ni);
	return err;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static int ntfs_rename(struct mnt_idmap *idmap, struct inode *old_dir,
		struct dentry *old_dentry, struct inode *new_dir,
		struct dentry *new_dentry, unsigned int flags)
#else
static int ntfs_rename(struct user_namespace *mnt_userns, struct inode *old_dir,
		struct dentry *old_dentry, struct inode *new_dir,
		struct dentry *new_dentry, unsigned int flags)
#endif
#else
static int ntfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		struct inode *new_dir, struct dentry *new_dentry,
		unsigned int flags)
#endif
{
	struct inode *old_inode, *new_inode = NULL;
	int err = 0;
	int is_dir;
	struct super_block *sb = old_dir->i_sb;
	ntfschar *uname_new = NULL;
	ntfschar *uname_old = NULL;
	int new_name_len;
	int old_name_len;
	ntfs_volume *vol = NTFS_SB(sb);
	ntfs_inode *old_ni, *new_ni = NULL, *old_dir_ni = NTFS_I(old_dir), *new_dir_ni = NTFS_I(new_dir);

	if (NVolShutdown(old_dir_ni->vol))
		return -EIO;

	if (flags & (RENAME_EXCHANGE | RENAME_WHITEOUT))
		return -EINVAL;

	new_name_len = ntfs_nlstoucs(NTFS_I(new_dir)->vol, new_dentry->d_name.name,
				     new_dentry->d_name.len, &uname_new,
				     NTFS_MAX_NAME_LEN);
	if (new_name_len < 0) {
		if (new_name_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to unicode.");
		return -ENOMEM;
	}

	err = ntfs_check_bad_char(uname_new, new_name_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, uname_new);
		return err;
	}

	old_name_len = ntfs_nlstoucs(NTFS_I(old_dir)->vol, old_dentry->d_name.name,
				     old_dentry->d_name.len, &uname_old,
				     NTFS_MAX_NAME_LEN);
	if (old_name_len < 0) {
		kmem_cache_free(ntfs_name_cache, uname_new);
		if (old_name_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to unicode.");
		return -ENOMEM;
	}

	old_inode = old_dentry->d_inode;
	new_inode = new_dentry->d_inode;
	old_ni = NTFS_I(old_inode);

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

	mutex_lock_nested(&old_ni->mrec_lock, NTFS_INODE_MUTEX_NORMAL);
	mutex_lock_nested(&old_dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT);

	if (NInoBeingDeleted(old_ni) || NInoBeingDeleted(old_dir_ni)) {
		err = -ENOENT;
		goto unlock_old;
	}

	is_dir = S_ISDIR(old_inode->i_mode);

	if (new_inode) {
		new_ni = NTFS_I(new_inode);
		mutex_lock_nested(&new_ni->mrec_lock, NTFS_INODE_MUTEX_NORMAL_2);
		if (old_dir != new_dir) {
			mutex_lock_nested(&new_dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT_2);
			if (NInoBeingDeleted(new_dir_ni)) {
				err = -ENOENT;
				goto err_out;
			}
		}

		if (NInoBeingDeleted(new_ni)) {
			err = -ENOENT;
			goto err_out;
		}

		if (is_dir) {
			MFT_RECORD *ni_mrec;

			ni_mrec = map_mft_record(NTFS_I(new_inode));
			if (IS_ERR(ni_mrec)) {
				err = -EIO;
				goto err_out;
			}
			err = ntfs_check_empty_dir(NTFS_I(new_inode), ni_mrec);
			unmap_mft_record(NTFS_I(new_inode));
			if (err)
				goto err_out;
		}

		err = ntfs_delete(new_ni, new_dir_ni, uname_new, new_name_len);
		if (err)
			goto err_out;
	} else {
		if (old_dir != new_dir) {
			mutex_lock_nested(&new_dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT_2);
			if (NInoBeingDeleted(new_dir_ni)) {
				err = -ENOENT;
				goto err_out;
			}
		}
	}

	err = __ntfs_link(old_ni, new_dir_ni, uname_new, new_name_len);
	if (err)
		goto err_out;

	err = ntfs_delete(old_ni, old_dir_ni, uname_old, old_name_len);
	if (err) {
		int err2;

		ntfs_error(sb, "Failed to delete old ntfs inode(%ld) in old dir, err : %d\n",
				old_ni->mft_no, err);
		err2 = ntfs_delete(old_ni, new_dir_ni, uname_new, new_name_len);
		if (err2)
			ntfs_error(sb, "Failed to delete old ntfs inode in new dir, err : %d\n",
					err2);
		goto err_out;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 6, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	simple_rename_timestamp(old_dir, old_dentry, new_dir, new_dentry);
#else
	old_dir->i_mtime = inode_set_ctime_current(old_dir);
	if (old_dir != new_dir)
		new_dir->i_mtime = new_dir->i_atime = inode_set_ctime_current(new_dir);
	inode_set_ctime_current(old_inode);
	if (new_inode)
		inode_set_ctime_current(new_inode);
#endif
#else
	old_dir->i_ctime = old_dir->i_mtime = current_time(old_dir);
	if (old_dir != new_dir)
		new_dir->i_ctime = new_dir->i_mtime = new_dir->i_atime = current_time(new_dir);
	old_inode->i_ctime = current_time(old_inode);
	if (new_inode)
		new_inode->i_ctime = current_time(new_inode);
#endif
	mark_inode_dirty(old_inode);
	mark_inode_dirty(old_dir);
	if (old_dir != new_dir)
		mark_inode_dirty(new_dir);
	if (new_inode)
		mark_inode_dirty(old_inode);

	inode_inc_iversion(new_dir);

err_out:
	if (old_dir != new_dir)
		mutex_unlock(&new_dir_ni->mrec_lock);
	if (new_inode)
		mutex_unlock(&new_ni->mrec_lock);

unlock_old:
	mutex_unlock(&old_dir_ni->mrec_lock);
	mutex_unlock(&old_ni->mrec_lock);
	if (uname_new)
		kmem_cache_free(ntfs_name_cache, uname_new);
	if (uname_old)
		kmem_cache_free(ntfs_name_cache, uname_old);

	return err;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static int ntfs_symlink(struct mnt_idmap *idmap, struct inode *dir,
		struct dentry *dentry, const char *symname)
#else
static int ntfs_symlink(struct user_namespace *mnt_userns, struct inode *dir,
		struct dentry *dentry, const char *symname)
#endif
#else
static int ntfs_symlink(struct inode *dir, struct dentry *dentry,
		const char *symname)
#endif
{
	struct super_block *sb = dir->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	struct inode *vi;
	int err = 0;
	ntfs_inode *ni;
	ntfschar *usrc;
	ntfschar *utarget;
	int usrc_len;
	int utarget_len;
	int symlen = strlen(symname);

	if (NVolShutdown(vol))
		return -EIO;

	usrc_len = ntfs_nlstoucs(vol, dentry->d_name.name,
				 dentry->d_name.len, &usrc, NTFS_MAX_NAME_LEN);
	if (usrc_len < 0) {
		if (usrc_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to "
					"Unicode.");
		err =  -ENOMEM;
		goto out;
	}

	err = ntfs_check_bad_char(usrc, usrc_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, usrc);
		goto out;
	}

	utarget_len = ntfs_nlstoucs(vol, symname, symlen, &utarget,
				    PATH_MAX);
	if (utarget_len < 0) {
		if (utarget_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert target name to "
					"Unicode.");
		err =  -ENOMEM;
		kmem_cache_free(ntfs_name_cache, usrc);
		goto out;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
	ni = __ntfs_create(idmap, dir, usrc, usrc_len, S_IFLNK | 0777, 0,
			utarget, utarget_len);
#else
	ni = __ntfs_create(mnt_userns, dir, usrc, usrc_len, S_IFLNK | 0777, 0,
			utarget, utarget_len);
#endif
#else
	ni = __ntfs_create(dir, usrc, usrc_len, S_IFLNK | 0777, 0,
			utarget, utarget_len);
#endif
	kmem_cache_free(ntfs_name_cache, usrc);
	kvfree(utarget);
	if (IS_ERR(ni)) {
		err = PTR_ERR(ni);
		goto out;
	}

	vi = VFS_I(ni);
	vi->i_size = symlen;
	d_instantiate_new(dentry, vi);
out:
	return err;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static int ntfs_mknod(struct mnt_idmap *idmap, struct inode *dir,
		struct dentry *dentry, umode_t mode, dev_t rdev)
#else
static int ntfs_mknod(struct user_namespace *mnt_userns, struct inode *dir,
		struct dentry *dentry, umode_t mode, dev_t rdev)
#endif
#else
static int ntfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode,
		dev_t rdev)
#endif
{
	struct super_block *sb = dir->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	int err = 0;
	ntfs_inode *ni;
	ntfschar *uname = NULL;
	int uname_len;

	if (NVolShutdown(vol))
		return -EIO;

	uname_len = ntfs_nlstoucs(vol, dentry->d_name.name,
			dentry->d_name.len, &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to "
					"Unicode.");
		return -ENOMEM;
	}

	err = ntfs_check_bad_char(uname, uname_len);
	if (err) {
		kmem_cache_free(ntfs_name_cache, uname);
		return err;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

	switch (mode & S_IFMT) {
	case S_IFCHR:
	case S_IFBLK:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
		ni = __ntfs_create(idmap, dir, uname, uname_len,
#else
		ni = __ntfs_create(mnt_userns, dir, uname, uname_len,
#endif
#else
		ni = __ntfs_create(dir, uname, uname_len,
#endif
				mode, rdev, NULL, 0);
		break;
	default:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 12, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
		ni = __ntfs_create(idmap, dir, uname, uname_len,
#else
		ni = __ntfs_create(mnt_userns, dir, uname, uname_len,
#endif
#else
		ni = __ntfs_create(dir, uname, uname_len,
#endif
				mode, 0, NULL, 0);
	}

	kmem_cache_free(ntfs_name_cache, uname);
	if (IS_ERR(ni)) {
		err = PTR_ERR(ni);
		goto out;
	}

	d_instantiate_new(dentry, VFS_I(ni));
out:
	return err;
}

static int ntfs_link(struct dentry *old_dentry, struct inode *dir,
		struct dentry *dentry)
{
	struct inode *vi = old_dentry->d_inode;
	struct super_block *sb = vi->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	ntfschar *uname = NULL;
	int uname_len;
	int err;
	ntfs_inode *ni = NTFS_I(vi), *dir_ni = NTFS_I(dir);

	if (NVolShutdown(vol))
		return -EIO;

	uname_len = ntfs_nlstoucs(vol, dentry->d_name.name,
			dentry->d_name.len, &uname, NTFS_MAX_NAME_LEN);
	if (uname_len < 0) {
		if (uname_len != -ENAMETOOLONG)
			ntfs_error(sb, "Failed to convert name to unicode.");
		err = -ENOMEM;
		goto out;
	}

	if (!(vol->vol_flags & VOLUME_IS_DIRTY))
		ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY);

	ihold(vi);
	mutex_lock_nested(&ni->mrec_lock, NTFS_INODE_MUTEX_NORMAL);
	mutex_lock_nested(&dir_ni->mrec_lock, NTFS_INODE_MUTEX_PARENT);
	err = __ntfs_link(NTFS_I(vi), NTFS_I(dir), uname, uname_len);
	if (err) {
		iput(vi);
		printk("failed to create link, err = %d\n", err);
		goto out;
	}

	inode_inc_iversion(dir);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 6, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	simple_inode_init_ts(dir);
#else
	dir->i_mtime = dir->i_atime = inode_set_ctime_current(dir);
#endif
#else
	dir->i_mtime = dir->i_atime = dir->i_ctime = current_time(dir);
#endif

	inode_inc_iversion(vi);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 6, 0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	simple_inode_init_ts(vi);
#else
	vi->i_mtime = vi->i_atime = inode_set_ctime_current(vi);
#endif
#else
	vi->i_mtime = vi->i_atime = vi->i_ctime = current_time(vi);
#endif

	/* timestamp is already written, so mark_inode_dirty() is unneeded. */
	d_instantiate(dentry, vi);

out:
	mutex_unlock(&dir_ni->mrec_lock);
	mutex_unlock(&ni->mrec_lock);
	ntfs_free(uname);
	return err;
}

/**
 * Inode operations for directories.
 */
const struct inode_operations ntfs_dir_inode_ops = {
	.lookup		= ntfs_lookup,	/* VFS: Lookup directory. */
	.create		= ntfs_create,
	.unlink		= ntfs_unlink,
	.mkdir		= ntfs_mkdir,
	.rmdir		= ntfs_rmdir,
	.rename		= ntfs_rename,
	.get_acl	= ntfs_get_acl,
	.set_acl	= ntfs_set_acl,
	.listxattr	= ntfs_listxattr,
	.setattr	= ntfs_setattr,
	.getattr	= ntfs_getattr,
	.symlink	= ntfs_symlink,
	.mknod		= ntfs_mknod,
	.link		= ntfs_link,
};

/**
 * ntfs_get_parent - find the dentry of the parent of a given directory dentry
 * @child_dent:		dentry of the directory whose parent directory to find
 *
 * Find the dentry for the parent directory of the directory specified by the
 * dentry @child_dent.  This function is called from
 * fs/exportfs/expfs.c::find_exported_dentry() which in turn is called from the
 * default ->decode_fh() which is export_decode_fh() in the same file.
 *
 * The code is based on the ext3 ->get_parent() implementation found in
 * fs/ext3/namei.c::ext3_get_parent().
 *
 * Note: ntfs_get_parent() is called with @d_inode(child_dent)->i_mutex down.
 *
 * Return the dentry of the parent directory on success or the error code on
 * error (IS_ERR() is true).
 */
static struct dentry *ntfs_get_parent(struct dentry *child_dent)
{
	struct inode *vi = d_inode(child_dent);
	ntfs_inode *ni = NTFS_I(vi);
	MFT_RECORD *mrec;
	ntfs_attr_search_ctx *ctx;
	ATTR_RECORD *attr;
	FILE_NAME_ATTR *fn;
	unsigned long parent_ino;
	int err;

	ntfs_debug("Entering for inode 0x%lx.", vi->i_ino);
	/* Get the mft record of the inode belonging to the child dentry. */
	mrec = map_mft_record(ni);
	if (IS_ERR(mrec))
		return ERR_CAST(mrec);
	/* Find the first file name attribute in the mft record. */
	ctx = ntfs_attr_get_search_ctx(ni, mrec);
	if (unlikely(!ctx)) {
		unmap_mft_record(ni);
		return ERR_PTR(-ENOMEM);
	}
try_next:
	err = ntfs_attr_lookup(AT_FILE_NAME, NULL, 0, CASE_SENSITIVE, 0, NULL,
			0, ctx);
	if (unlikely(err)) {
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		if (err == -ENOENT)
			ntfs_error(vi->i_sb, "Inode 0x%lx does not have a "
					"file name attribute.  Run chkdsk.",
					vi->i_ino);
		return ERR_PTR(err);
	}
	attr = ctx->attr;
	if (unlikely(attr->non_resident))
		goto try_next;
	fn = (FILE_NAME_ATTR *)((u8 *)attr +
			le16_to_cpu(attr->data.resident.value_offset));
	if (unlikely((u8 *)fn + le32_to_cpu(attr->data.resident.value_length) >
			(u8*)attr + le32_to_cpu(attr->length)))
		goto try_next;
	/* Get the inode number of the parent directory. */
	parent_ino = MREF_LE(fn->parent_directory);
	/* Release the search context and the mft record of the child. */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(ni);

	return d_obtain_alias(ntfs_iget(vi->i_sb, parent_ino));
}

static struct inode *ntfs_nfs_get_inode(struct super_block *sb,
		u64 ino, u32 generation)
{
	struct inode *inode;

	inode = ntfs_iget(sb, ino);
	if (!IS_ERR(inode)) {
		if (is_bad_inode(inode) || inode->i_generation != generation) {
			iput(inode);
			inode = ERR_PTR(-ESTALE);
		}
	}

	return inode;
}

static struct dentry *ntfs_fh_to_dentry(struct super_block *sb, struct fid *fid,
		int fh_len, int fh_type)
{
	return generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    ntfs_nfs_get_inode);
}

static struct dentry *ntfs_fh_to_parent(struct super_block *sb, struct fid *fid,
		int fh_len, int fh_type)
{
	return generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    ntfs_nfs_get_inode);
}

/**
 * Export operations allowing NFS exporting of mounted NTFS partitions.
 *
 * We use the default ->encode_fh() for now.  Note that they
 * use 32 bits to store the inode number which is an unsigned long so on 64-bit
 * architectures is usually 64 bits so it would all fail horribly on huge
 * volumes.  I guess we need to define our own encode and decode fh functions
 * that store 64-bit inode numbers at some point but for now we will ignore the
 * problem...
 *
 * We also use the default ->get_name() helper (used by ->decode_fh() via
 * fs/exportfs/expfs.c::find_exported_dentry()) as that is completely fs
 * independent.
 *
 * The default ->get_parent() just returns -EACCES so we have to provide our
 * own and the default ->get_dentry() is incompatible with NTFS due to not
 * allowing the inode number 0 which is used in NTFS for the system file $MFT
 * and due to using iget() whereas NTFS needs ntfs_iget().
 */
const struct export_operations ntfs_export_ops = {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 7, 0)
	.encode_fh = generic_encode_ino32_fh,
#endif
	.get_parent	= ntfs_get_parent,	/* Find the parent of a given
						   directory. */
	.fh_to_dentry	= ntfs_fh_to_dentry,
	.fh_to_parent	= ntfs_fh_to_parent,
};
