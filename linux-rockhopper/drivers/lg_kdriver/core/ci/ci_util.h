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
 *  driver interface header for ci device. ( used only within kdriver )
 *	ci device will teach you how to make device driver with new platform.
 *
 *  @author		Srinivasan Shanmugam	(srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef	_CI_UTIL_H_
#define	_CI_UTIL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "ci_debug.h"
#include "ci_kapi.h"

#include "base_device.h"
#include "os_util.h"
#include "debug_util.h"
#include "proc_util.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

const char* ci_get_delaystr(UINT32 type);

extern void *ci_malloc(int size);
extern void *ci_zalloc(int size);
extern void ci_free(void *mem);

extern void ci_sleep(int delay);

struct proc_dir_entry *ci_proc_get_base_dir(void);
struct proc_dir_entry *ci_proc_create_entry(char *name,
								struct proc_dir_entry *parent,
								OS_PROC_DESC_TABLE_T *table,
								OS_PROC_READ_FUNC_T rd_func,
								OS_PROC_WRITE_FUNC_T wr_func);
struct proc_dir_entry *ci_proc_create_entry_ex(char *name,
								OS_PROC_DESC_TABLE_T *table,
								OS_PROC_READ_FUNC_T rd_func,
								OS_PROC_WRITE_FUNC_T wr_func);

extern int ci_proc_remove_entry(char *module_name);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _CI_UTIL_H_ */


