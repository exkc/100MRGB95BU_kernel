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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version 1.0
 *  date        2009.11.14
 *  note
 *  @addtogroup lg1150_base
 *  @{
 */

#ifndef _KDRV_BASE_DRV_H_
#define _KDRV_BASE_DRV_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>

#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/cdev.h>
#include <linux/spinlock.h>

#include <asm/io.h>
#include <asm/atomic.h>
#include <asm/uaccess.h>

#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"

#ifdef USE_QEMU_SYSTEM
#include "qemu_drv.h"
#endif

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
//semaphore
extern spinlock_t g_Base_AVLipsync_Lock;

#define BASE_AVLIPSYNC_LOCK()               {unsigned long __avlipsync_lock_flags; spin_lock_irqsave(&g_Base_AVLipsync_Lock, __avlipsync_lock_flags);
#define BASE_AVLIPSYNC_UNLOCK()             spin_unlock_irqrestore(&g_Base_AVLipsync_Lock, __avlipsync_lock_flags);}

#define BASE_AVLIPSYNC_LOCK_FLAG(flag)      spin_lock_irqsave(&g_Base_AVLipsync_Lock, flag)
#define BASE_AVLIPSYNC_UNLOCK_FLAG(flag)    spin_unlock_irqrestore(&g_Base_AVLipsync_Lock, flag)


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_DRV_H_ */

/** @} */

