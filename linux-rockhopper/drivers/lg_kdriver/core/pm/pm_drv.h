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
 *  main driver implementation for pm device.
 *	pm device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_pm
 */


#ifndef	_PM_DRV_H_
#define	_PM_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "pm_cfg.h"
#include "pm_kapi.h"

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
#define	PM_PRINT(format, args...)		DBG_PRINT(  g_pm_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)
#define	PM_TRACE(format, args...)		DBG_PRINTX( g_pm_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)
#define	PM_DEBUG(format, args...)		DBG_PRINT( g_pm_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define	PM_ERROR(format, args...)		DBG_PRINT( g_pm_debug_fd, LX_LOGM_LEVEL_ERROR, format, ##args)
#define	PM_NOTI(format, args...)		DBG_PRINT( g_pm_debug_fd, LX_LOGM_LEVEL_NOTI, format, ##args)


#define PM_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 __CHECK_IF_ERROR(__checker, PM_ERROR, __if_action , fmt, ##args )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	PM_MSG_ERROR = LX_LOGM_LEVEL_ERROR,
	PM_MSG_WARN = LX_LOGM_LEVEL_WARNING,
	PM_MSG_NOTI = LX_LOGM_LEVEL_NOTI,
	PM_MSG_INFO = LX_LOGM_LEVEL_INFO,
	PM_MSG_DEBUG = LX_LOGM_LEVEL_DEBUG,
	PM_MSG_TRACE = LX_LOGM_LEVEL_TRACE,
	PM_MSG_NORMAL = (LX_LOGM_LEVEL_TRACE + 1),	// print
	PM_MSG_VSYNC = (LX_LOGM_LEVEL_TRACE + 2),		// vsync
	PM_MSG_TIMER = (LX_LOGM_LEVEL_TRACE + 3),		// timer
	PM_MSG_INTER = (LX_LOGM_LEVEL_TRACE + 4),		// interrupt

	PM_MSG_INDEX_COUNT
} PM_MSG_TYPE_T;

typedef struct
{
	void			(*init)				(void);
	int				(*ioctl)			(unsigned int cmd, unsigned long arg);
	int				(*suspend)			(void);
	int				(*resume)			(void);
	int				(*prepare)			(void);
} pms_driver_t;

typedef struct
{
	void			(*init)		(void);
	void			(*cleanup)	(void);
} pms_proc_t;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     PM_PreInit(void);
extern	int      PM_Init(void);
extern	void     PM_Cleanup(void);
int		PM_Init(void);
void	PM_Cleanup(void);

extern int PM_GetClockGating(u32 Module, u32 SubModule, u32 *state);
extern int PM_SetClockGating(u32 Module, u32 SubModule, u32 state);

/* FOR M16 ONLY */
extern unsigned int pm_m16_get_vdec0_clock_select(void);
extern void pm_m16_set_vdec0_clock_select(unsigned int state);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_pm_debug_fd;
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PM_DRV_H_ */

/** @} */
