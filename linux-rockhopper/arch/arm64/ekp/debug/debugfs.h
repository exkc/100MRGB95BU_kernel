/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __EKP_DEBUGFS_H
#define __EKP_DEBUGFS_H

#ifdef CONFIG_EKP_DEBUGFS

#include <linux/compiler.h>
#include <linux/dcache.h>
#include <linux/seq_file.h>

struct ekp_debugfs_ops {
	int (*show)(struct seq_file *m);
	int (*store)(const char __user *buf, size_t size);
};

struct ekp_debugfs_attr {
	const char *name;
	struct ekp_debugfs_ops *ops;
};

#define __DEFINE_EKP_DEBUGFS(__name, __show, __store)	\
static struct ekp_debugfs_ops __name = {		\
	.show  = __show,				\
	.store = __store,				\
}

#define DEFINE_EKP_DEBUGFS_RO(__name)	\
	__DEFINE_EKP_DEBUGFS(__name, __name ## _show, NULL)

#define DEFINE_EKP_DEBUGFS_WO(__name)	\
	__DEFINE_EKP_DEBUGFS(__name, NULL, __name ## _store)

#define DEFINE_EKP_DEBUGFS_RW(__name)	\
	__DEFINE_EKP_DEBUGFS(__name, __name ## _show, __name ## _store)

extern void __init ekp_debugfs_create_files(struct ekp_debugfs_attr *attrs,
					    int count, struct dentry *parent);

#define ekp_debugfs_create(__parent, __attrs)	\
	ekp_debugfs_create_files(__attrs, ARRAY_SIZE(__attrs), __parent)

extern void __init ekp_debugfs_state_init(struct dentry *parent);

#ifdef CONFIG_EKP_DEBUGFS_SYSINFO
extern void __init ekp_debugfs_sysinfo_init(struct dentry *parent);
#else
static inline void ekp_debugfs_sysinfo_init(struct dentry *parent) {}
#endif

#ifdef CONFIG_EKP_DEBUGFS_TEST_HELPERS
extern void __init ekp_debugfs_test_helpers_init(struct dentry *parent);
#else
static inline void ekp_debugfs_test_helpers_init(struct dentry *parent) {}
#endif

#endif /* CONFIG_EKP_DEBUGFS */

#endif /* __EKP_DEBUGFS_H */
