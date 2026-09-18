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
 *  main internal header for Demod device.
 *
 *  @author	Jeongpil.Yun (jeongpil.yun@lge.com)
 *  @version	1.0
 *  @date	2011.04.03
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#ifndef _DEMOD_IMPL_H_
#define _DEMOD_IMPL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "demod_drv.h"
#include "demod_cfg.h"
#include "demod_kapi.h"
#include "demod_hal.h"
#include "demod_module.h"
#include "demod_hw.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#if defined(DEMOD_CHIP_NAME_o22)
#define DEMOD_I2C_PORT				2
#else
#define DEMOD_I2C_PORT	6
#endif
#define DEMOD_I2C_ADDR	0xB2

#if defined(PLATFORM_FPGA)
// packet error threshold adjust value for o22_fpga test
#define THR_ADJ 1000
#else
#define THR_ADJ 1
#endif
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define LX_LOGM_LEVEL_ALWAYS			(LX_LOGM_LEVEL_TRACE+1)
#define LX_LOGM_LEVEL_PRINT			(LX_LOGM_LEVEL_TRACE+2)

#define LX_LOGM_LEVEL_MCU_ERROR			(LX_LOGM_LEVEL_TRACE+3)
#define LX_LOGM_LEVEL_MCU_PRINT			(LX_LOGM_LEVEL_TRACE+4)
#define LX_LOGM_LEVEL_MCU_DEBUG			(LX_LOGM_LEVEL_TRACE+5)

#define DEMOD_DEBUG_PRINT			printk
//#define DEMOD_PRINT				printk
//#define DEMOD_TRACE				printk

#ifndef DEMOD_TAG
#define DEMOD_TAG ""
#endif

#define DEMOD_ERROR(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_ERROR, DEMOD_TAG format, ##args)
#define DEMOD_WARN(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_WARNING, DEMOD_TAG format, ##args)
#define DEMOD_NOTI(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_NOTI, DEMOD_TAG format, ##args)
#define DEMOD_INFO(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_INFO, DEMOD_TAG format, ##args)
//#define DEMOD_DEBUG(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG, DEMOD_TAG format, ##args)
#define DEMOD_DEBUG(...)			do { } while(0)
#define DEMOD_TRACE(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE, DEMOD_TAG format, ##args)
#define DEMOD_PRINT_ALWAYS(format, args...)	DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_ALWAYS, DEMOD_TAG format, ##args)
#define DEMOD_PRINT(format, args...)		DBG_PRINT(g_demod_debug_fd, LX_LOGM_LEVEL_PRINT, DEMOD_TAG format, ##args)

#define DEMOD_MCU_ERROR(format, args...)	DBG_PRINT( g_demod_debug_fd, LX_LOGM_LEVEL_MCU_ERROR, DEMOD_TAG format, ##args)
#define DEMOD_MCU_PRINT(format, args...)	DBG_PRINT( g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT, DEMOD_TAG format, ##args)
#define DEMOD_MCU_DEBUG(format, args...)	DBG_PRINT( g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG, DEMOD_TAG format, ##args)

#define DEMOD_TRACE_BEGIN()			DEMOD_TRACE("[DEMODDEV:%d] BEGIN   -- %s:%d\n", g_demod_trace_depth++, __FUNCTION__, __LINE__ )
#define DEMOD_TRACE_END()			DEMOD_TRACE("[DEMODDEV:%d] END     -- %s:%d\n", --g_demod_trace_depth, __FUNCTION__, __LINE__ )
#define DEMOD_TRACE_MARK()			DEMOD_TRACE("[DEMODDEV] LOGGING -- %s:%d\n", __FUNCTION__, __LINE__ )

#define DEMOD_NOT_SUPPORTED(s)			{DEMOD_PRINT("^y^[[DEMODDEV]] %s() Not supported (but OK)\n", s); return RET_OK;}
#define DEMOD_RETURN_FAIL(s)			{DEMOD_PRINT("^r^[[DEMODDEV]] FAIL %s()\n", s); return RET_ERROR;}

#define DEMOD_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 			__CHECK_IF_ERROR(__checker, DEMOD_PRINT, __if_action , fmt, ##args )

#define DEMOD_CHECK_ERROR(__checker,__if_action,fmt,args...)   \
			 			__CHECK_IF_ERROR(__checker, DEMOD_ERROR, __if_action , fmt, ##args )

#define DEMOD_ASSERT(__checker)	\
						__CHECK_IF_ERROR( !(__checker), DEMOD_WARN, /* nop */, "[GFXDEV] ASSERT FAILED -- %s:%d\n", __FUNCTION__, __LINE__ )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

#ifdef KDRV_CONFIG_PM
extern int DEMOD_HW_suspend(void);
extern int DEMOD_HW_resume(void);
#endif

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern DEMOD_HAL_T		g_demod_hal;

void DEMOD_SetupMemMap (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMOD_DRV_H_ */

/** @} */
