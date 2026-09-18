/**
 * @Title      proc file system for  memory profiling
 * @Copyright  Copyright (c) LG Electronics All Rights Reserved
 * @License    Strictly Confidential.
*/


/**
 * @file mali_kbase_um_procfs.h
 * Header file for mem profiles entries in procfs
 *
 */

#ifndef _KBASE_UM_PROCFS_H
#define _KBASE_UM_PROCFS_H

#include <mali_kbase.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

/**
 * @brief Remove entry from Mali memory profile procfs
 */
void kbasep_um_procfs_remove(struct kbase_context *kctx, struct kbase_device *kbdev);

/**
 * @brief Insert @p data to the procfs file so it can be read by userspace
 *
 * The function takes ownership of @p data and frees it later when new data
 * is inserted.
 *
 * If the procfs entry corresponding to the @p kctx doesn't exist,
 * an attempt will be made to create it.
 *
 * @param kctx The context whose procfs file @p data should be inserted to
 */
int kbasep_um_procfs_insert(struct kbase_context *kctx, struct kbase_device *kbdev);
#endif  /*_KBASE_UM_DEBUGFS_H*/

