/* SPDX-License-Identifier: GPL-2.0-or-later */

extern ntfschar reparse_index_name[];

unsigned int ntfs_make_symlink(ntfs_inode *ni);
unsigned int ntfs_reparse_tag_dt_types(ntfs_volume *vol, unsigned long mref);
int ntfs_reparse_set_wsl_symlink(ntfs_inode *ni,
			const ntfschar *target, int target_len);
int ntfs_reparse_set_wsl_not_symlink(ntfs_inode *ni, mode_t mode);
int ntfs_delete_reparse_index(ntfs_inode *ni);
int ntfs_remove_ntfs_reparse_data(ntfs_inode *ni);
