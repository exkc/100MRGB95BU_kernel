// SPDX-License-Identifier: GPL-2.0-or-later
/**
 * Copyright (c) 2024 LG Electronics Co., Ltd.
 * Author(s): Namjae Jeon <linkinjeon@kernel.org>
 */

#ifndef _LINUX_NTFS_IOMAP_H
#define _LINUX_NTFS_IOMAP_H

#include <linux/pagemap.h>
#include <linux/iomap.h>

#include "volume.h"
#include "inode.h"

extern const struct iomap_ops ntfs_write_iomap_ops;
extern const struct iomap_ops ntfs_read_iomap_ops;
extern const struct iomap_ops ntfs_page_mkwrite_iomap_ops;
extern const struct iomap_ops ntfs_dio_iomap_ops;
extern const struct iomap_writeback_ops ntfs_writeback_ops;
#endif /* _LINUX_NTFS_IOMAP_H */
