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
 *  definition header file for APR device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.07.06
 *  note		Additional information.
 *
 *  @addtogroup APR
 *	@{
 */

#ifndef _APR_DEF_H_
#define _APR_DEF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_M17_CHIP_KDRV
//#define USE_KDRV_CODES_FOR_M17
//#undef _DISABLE_ACCESS_TO_EXT_REGISTER_
#undef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
#endif

#if 0
#define USE_KDRV_CODES_FOR_M16
#undef _DISABLE_ACCESS_TO_EXT_REGISTER_
#endif

#if 0
#define USE_KDRV_CODES_FOR_H15
#endif

#if 0
#define USE_KDRV_CODES_FOR_H14
//#define _DISABLE_ACCESS_TO_PE_
#endif

#if 0
#define USE_KDRV_CODES_FOR_M14
#endif

#if 0
#define USE_KDRV_CODES_FOR_H13
#endif

#if 0
//#define USE_KDRV_CODES_FOR_L9  // 3D pattern detect -> d3d of pe/util (gp4: pe_d3d.c/pe_d3d_alg.c)
#endif

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "apr_kapi.h"
#include "pe_kapi.h"
#include "apr_osd.h"
#include "debug_util.h"
	
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define APR_ERROR(format, args...)		DBG_PRINT( g_apr_debug_fd,         \
													LX_LOGM_LEVEL_ERROR,   \
													format,                \
													##args )
#define APR_WARN(format, args...)		DBG_PRINT( g_apr_debug_fd,         \
													LX_LOGM_LEVEL_WARNING, \
													format,                \
													##args )
#define APR_PRINT(format, args...)		DBG_PRINT( g_apr_debug_fd,         \
													LX_LOGM_LEVEL_INFO,    \
													format,                \
													##args )
#define APR_NOTI(format, args...)		DBG_PRINT( g_apr_debug_fd,         \
													LX_LOGM_LEVEL_NOTI,    \
													format,                \
													##args )
#define APR_TRACE(format, args...)		DBG_PRINT( g_apr_debug_fd,         \
													LX_LOGM_LEVEL_TRACE,   \
													format,                \
													##args )

#define CHECK_KNULL(ptr)  if(!ptr) { APR_ERROR("%s: %s is null\n", __F__, #ptr);\
									 ret = RET_ERROR; break; }
#define BREAK_WRONG(val) { APR_ERROR("%s: break wrong %s(0x%x)\n", __F__, #val, val);\
									 ret = RET_ERROR; break; }
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern	int		g_apr_debug_fd;

#endif /* _APR_DEF_H_ */

/** @} */
