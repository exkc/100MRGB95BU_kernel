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
 *  driver internal header file for tempalte device
 *
 *  @author		author
 *  @version	1.0
 *  @date		20xx.xx.xx
 *
 *  @addtogroup lg115x_template
 *	@{
 */

#ifndef	_TEMPLATE_IMPL_H_
#define	_TEMPLATE_IMPL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_TEMPLATE_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>

#include <linux/dma-mapping.h>
#include <linux/platform_device.h>

#include <linux/errno.h>
#include <linux/string.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
#include <asm/hardware.h>
#endif

#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "debug_util.h"
#include "template_cfg.h"
#include "template_drv.h"
#include "template_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
extern	int		g_template_debug_fd;

#define TEMPLATE_ERROR(format,args...)		DBG_PRINT( g_template_debug_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define TEMPLATE_WARN(format, args...)		DBG_PRINT( g_template_debug_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define TEMPLATE_NOTI(format, args...)		DBG_PRINT( g_template_debug_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define TEMPLATE_INFO(format, args...)		DBG_PRINT( g_template_debug_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define TEMPLATE_DEBUG(format,args...)		DBG_PRINT( g_template_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define TEMPLATE_TRACE(format,args...)		DBG_PRINT( g_template_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)

#define TEMPLATE_CHECK_NONE(__checker,__if_action,fmt,args...)		\
             __CHECK_IF_ERROR(__checker, /*nop*/, __if_action, fmt, ##args)

#define TEMPLATE_CHECK_WARN(__checker,__if_action,fmt,args...)		\
             __CHECK_IF_ERROR(__checker, TEMPLATE_WARN, __if_action , fmt, ##args)

#define TEMPLATE_CHECK_ERROR(__checker,__if_action,fmt,args...)	\
             __CHECK_IF_ERROR(__checker, TEMPLATE_ERROR, __if_action , fmt, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int			rsvd;
}
TEMPLATE_DRV_DATA_T;

typedef struct
{
	struct cdev cdev;
	int			dev_open_cnt;

}
TEMPLATE_DEV_CTX_T;

typedef struct
{
	TEMPLATE_DEV_CTX_T* dev_ctx;
}
TEMPLATE_OBJ_CTX_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _TEMPLATE_DRV_H_ */

/** @} */
