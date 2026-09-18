/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  CI register details. ( used only within kdriver )
 *
 *  @author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2015.1.1
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef __CI_IOCTL_H__
#define __CI_IOCTL_H__

#include <linux/types.h>
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


typedef struct
{
	unsigned int ioctl_num;
	int (*func)(CI_DEV_T *cidev, void* arg);
	const char *name;
} DEV_IOCTL_FUNC_T;

#define IOCTL_FUNC_TYPE(cmd, func) \
	{cmd, func, #func}

extern const struct file_operations ci_fops_base;

extern int ci_open(struct inode *inode, struct file *filp);
extern int ci_close(struct inode *inode, struct file *filp);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __CI_IOCTL_H__ */


