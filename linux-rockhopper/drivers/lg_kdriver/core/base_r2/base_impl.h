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

#ifndef __KDRV_BASE_IMPL_H__
#define __KDRV_BASE_IMPL_H__

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

#define lg1k_logm_error(format, args...)        DBG_PRINT(lg1k_core_logm_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define lg1k_logm_warn(format, args...)         DBG_PRINT(lg1k_core_logm_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define lg1k_logm_noti(format, args...)         DBG_PRINT(lg1k_core_logm_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define lg1k_logm_debug(format, args...)        DBG_PRINT(lg1k_core_logm_fd, LX_LOGM_LEVEL_DEBUG, format ,##args)

#define lg1k_logm_os_debug(format, args...)     DBG_PRINT(lg1k_core_logm_fd, 10, format ,##args)
#define lg1k_logm_proc_debug(format, args...)   DBG_PRINT(lg1k_core_logm_fd, 11, format ,##args)
#define lg1k_logm_memcfg_debug(format, args...) DBG_PRINT(lg1k_core_logm_fd, 12, format ,##args)

void lg1k_os_frwk_init(void);
void lg1k_os_frwk_cleanup(void);

void lg1k_memcfg_frwk_init(void);
void lg1k_memcfg_frwk_cleanup(void);

void lg1k_proc_frwk_init(void);
void lg1k_proc_frwk_cleanup(void);

void lg1k_board_frwk_init(void);
void lg1k_board_frwk_cleanup(void);

void lg1k_kdrv_preinit_driver(void);
void lg1k_kdrv_init_driver(void);
void lg1k_kdrv_cleanup_driver(void);

void BASE_DEVMEM_DumpMemCfg(struct seq_file* m, UINT32 opt); // legacy interface

u32 get_base_chip_plt(void);
u32 get_base_board_opt(void);

extern int lg1k_core_logm_fd;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __KDRV_BASE_IMPL_H__ */

/** @} */

