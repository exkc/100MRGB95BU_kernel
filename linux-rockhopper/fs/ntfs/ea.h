/* SPDX-License-Identifier: GPL-2.0-or-later */

extern const struct xattr_handler *const ntfs_xattr_handlers[];

int ntfs_ea_set_wsl_not_symlink(ntfs_inode *ni, mode_t mode, dev_t dev);
int ntfs_get_ea(struct inode *inode, const char *name, size_t name_len,
		void *buffer, size_t size);
int ntfs_set_ntfs_ea(ntfs_inode *ni, char *value, size_t size, int flags);
int ntfs_ea_get_wsl_inode(struct inode *inode, dev_t *rdevp, unsigned int flags);
int ntfs_ea_set_wsl_inode(struct inode *inode, dev_t rdev, __le16 *ea_size);
int ntfs_remove_ntfs_ea(ntfs_inode *ni);
ssize_t ntfs_listxattr(struct dentry *dentry, char *buffer, size_t size);

#ifdef CONFIG_NTFS_FS_POSIX_ACL
struct posix_acl *ntfs_get_acl(struct mnt_idmap *idmap, struct dentry *dentry,
			       int type);
int ntfs_set_acl(struct mnt_idmap *idmap, struct dentry *dentry,
		 struct posix_acl *acl, int type);
int ntfs_init_acl(struct mnt_idmap *idmap, struct inode *inode,
		  struct inode *dir);
#else
#define ntfs_get_acl NULL
#define ntfs_set_acl NULL
#endif
