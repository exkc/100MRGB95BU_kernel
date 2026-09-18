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
 *  date			2015.07.17
 *  note			Additional information.
 *
 */


#ifndef	_EMMC_DRV_H_
#define	_EMMC_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "emmc_cfg.h"

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
#define	EMMC_PRINT(format, args...)		DBG_PRINT(  g_emmc_debug_fd, EMMC_MSG_TRACE, format, ##args)
#define	EMMC_TRACE(format, args...)		DBG_PRINTX( g_emmc_debug_fd, EMMC_MSG_TRACE, format, ##args)
#define	EMMC_DEBUG(format, args...)		DBG_PRINT( g_emmc_debug_fd, EMMC_MSG_DEBUG, format, ##args)
#define	EMMC_ERROR(format, args...)		DBG_PRINT( g_emmc_debug_fd, EMMC_MSG_ERROR, format, ##args)
#define	EMMC_NOTI(format, args...)		DBG_PRINT( g_emmc_debug_fd, EMMC_MSG_NOTI, format, ##args)


#define EMMC_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 __CHECK_IF_ERROR(__checker, EMMC_ERROR, __if_action , fmt, ##args )


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	EMMC_MSG_ERROR = LX_LOGM_LEVEL_ERROR,
	EMMC_MSG_WARN = LX_LOGM_LEVEL_WARNING,
	EMMC_MSG_NOTI = LX_LOGM_LEVEL_NOTI,
	EMMC_MSG_INFO = LX_LOGM_LEVEL_INFO,
	EMMC_MSG_DEBUG = LX_LOGM_LEVEL_DEBUG,
	EMMC_MSG_TRACE = LX_LOGM_LEVEL_TRACE,
	EMMC_MSG_NORMAL = (LX_LOGM_LEVEL_TRACE + 1),		// print
	EMMC_MSG_VSYNC = (LX_LOGM_LEVEL_TRACE + 2),		// vsync
	EMMC_MSG_TIMER = (LX_LOGM_LEVEL_TRACE + 3),		// timer
	EMMC_MSG_INTER = (LX_LOGM_LEVEL_TRACE + 4),		// interrupt

	EMMC_MSG_INDEX_COUNT
} EMMC_MSG_TYPE_T;

typedef struct
{
	void			(*init)				(void);
	int				(*ioctl)			(unsigned int cmd, unsigned int arg);

} emmc_driver_t;

typedef struct
{
	unsigned int    (*GetEmmcIntap)(void);
	unsigned int    (*SetEmmcIntap)(unsigned int intab);
	unsigned int    (*GetEmmcOuttap)(void);
	unsigned int    (*SetEmmcOuttap)(unsigned int outtap);
	unsigned int    (*GetEmmcHostDS)(void);
	unsigned int    (*SetEmmcHostDS)(unsigned int ds);
	unsigned int    (*TopRegDump)(void);
	unsigned int    (*CntrRegDump)(void);
} emmc_func_t;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void     EMMC_PreInit(void);
int      EMMC_Init(void);
void     EMMC_Cleanup(void);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int g_emmc_debug_fd;
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _EMMC_DRV_H_ */

/** @} */
