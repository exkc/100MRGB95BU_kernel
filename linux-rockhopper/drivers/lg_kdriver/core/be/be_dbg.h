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
 *  dbg header file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2012.08.01
 *  note		debug print macro.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_DBG_H_
#define _BE_DBG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define BE_DBG_PRT_IDX_PRINT	 	BE_DBG_PRT_IDX_TRACE
#define BE_DBG_PRT_IDX_ERROR	 	LX_LOGM_LEVEL_ERROR
#define BE_DBG_PRT_IDX_NOTI	 	LX_LOGM_LEVEL_NOTI
#define BE_DBG_PRT_IDX_DEBUG	 	LX_LOGM_LEVEL_DEBUG
#define BE_DBG_PRT_IDX_TRACE	 	LX_LOGM_LEVEL_TRACE

#define BE_DBG_PRT_MSK_PRINT	(1UL << BE_DBG_PRT_IDX_PRINT)
#define BE_DBG_PRT_MSK_ERROR	(1UL << BE_DBG_PRT_IDX_ERROR)
#define BE_DBG_PRT_MSK_DEBUG	(1UL << BE_DBG_PRT_IDX_DEBUG)
#define BE_DBG_PRT_MSK_TRACE	(1UL << BE_DBG_PRT_IDX_TRACE)

#define BE_DBG_LEVEL_ERROR	0
#define BE_DBG_LEVEL_WARN	1
#define BE_DBG_LEVEL_IGNORE	2

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define BE_PRINT(format, args...)		DBG_PRINT ( g_be_debug_fd, BE_DBG_PRT_IDX_PRINT, format, ##args )
#define BE_ERROR(format, args...)		DBG_PRINTX ( g_be_debug_fd, BE_DBG_PRT_IDX_ERROR, format, ##args )
#define BE_NOTI(format, args...)		DBG_PRINTX ( g_be_debug_fd, BE_DBG_PRT_IDX_NOTI, format, ##args )
#define BE_DEBUG(format, args...)		DBG_PRINT ( g_be_debug_fd, BE_DBG_PRT_IDX_DEBUG, format, ##args )
#define BE_TRACE(format, args...)		DBG_PRINTX( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE, format"\n", ##args )
#define BE_TRACE1(format, args...)		DBG_PRINTX( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE+1, format"\n", ##args )
#define BE_TRACE7(format, args...)		DBG_PRINTX( g_be_debug_fd, 7, format, ##args )
#define BE_TRACE8(format, args...)		DBG_PRINTX( g_be_debug_fd, 8, format, ##args )
#define BE_TRACE9(format, args...)		DBG_PRINTX( g_be_debug_fd, 9, format, ##args )
#define BE_TRACE1_PWM(format, args...)	DBG_PRINT ( g_be_debug_fd, 11, format, ##args )
#define BE_TRACE2_PWM(format, args...)	DBG_PRINT ( g_be_debug_fd, 12, format, ##args )
#define BE_TRACE3_PWM(format, args...)	DBG_PRINT ( g_be_debug_fd, 13, format, ##args )
#define BE_PRINT_PWM(format, args...)	DBG_PRINT ( g_be_debug_fd, 14, format, ##args )
#define BE_PRINT_EVT(format, args...)	DBG_PRINT ( g_be_debug_fd, 15, format, ##args )
#define BE_PRINT_SYN(format, args...)	DBG_PRINT ( g_be_debug_fd, 16, format, ##args )
#define BE_PRINT_DPC(format, args...)	DBG_PRINT ( g_be_debug_fd, 17, format, ##args )
#define BE_PRINT_LDIM(format, args...)	DBG_PRINT ( g_be_debug_fd, 18, format, ##args )
#define BE_PRINT_OBJ(format, args...)	DBG_PRINT ( g_be_debug_fd, 19, format, ##args )

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int		g_be_debug_fd;
extern int gHalFuncSupportDbgLevel;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _BE_DRV_H_ */

/** @} */


