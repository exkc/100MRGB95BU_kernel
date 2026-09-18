/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  driver interface header for se device. ( used only within kdriver )
 *  this file lists the type, function lists exported to the other module outside SE.
 *
 *  @author     stan.kim@lge.com
 *  @version    2.0
 *  @date       2012.5
 *  @note       Additional information.
 *
 *	@{
 */

#ifndef	_SE_DRV_IMPL_H_
#define	_SE_DRV_IMPL_H_

//#define _SE_STANDALONE_

#ifndef _SE_STANDALONE_

#include "base_types.h"
#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"
#include "proc_util.h"

#else	// _SE_STANDALONE_

typedef struct
{
#ifndef CONFIG_COMPAT
	char*	name;		///< name of memory chunk : for debugging & module param(TODO)
#else
	union
	{
		char*		name;		///< name of memory chunk : for debugging & module param(TODO)
		uint32_t	compat_name;
		uint64_t	sizer;
	};
#endif
	uint32_t	base;		///< physical base address in BYTE!!! of media ip
	uint32_t	size;		///< size in BYTE!!!
} LX_MEMCFG_T;

#define TRUE	1
#define FALSE	0
typedef int BOOLEAN;

// From base_device.h
#define	KDRV_MAJOR_BASE		1100	/* 1100 */
#define SE_MAJOR			(KDRV_MAJOR_BASE+19)
#define	SE_MINOR			0

// Fake Function
typedef int OS_SEM_T;
#define OS_InitMutex(a, b)
#define OS_LockMutex(a)		0
#define OS_UnlockMutex(a)

#endif	// _SE_STANDALONE_

#include "se_drv.h"
#include "se_cfg.h"
#include "../../include/se_kapi.h"

#endif /* _SE_DRV_IMPL_H_ */

/** @} */
