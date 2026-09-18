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
 *  DVB-CI Command Interface Physical Layer
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version	0.6
 *  date		2010.02.22
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef	_CI_DEBUG_H_
#define	_CI_DEBUG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/types.h>
#include "debug_util.h"

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

extern int g_ci_debug_fd;

enum
{
	LOG_LEVEL_ERROR		= LX_LOGM_LEVEL_ERROR,			/* 0 */
	LOG_LEVEL_WARNING	= LX_LOGM_LEVEL_WARNING,		/* 1 */
	LOG_LEVEL_NOTI		= LX_LOGM_LEVEL_NOTI,			/* 2 */
	LOG_LEVEL_INFO		= LX_LOGM_LEVEL_INFO,			/* 3 */
	LOG_LEVEL_DEBUG		= LX_LOGM_LEVEL_DEBUG,			/* 4 */
	LOG_LEVEL_TRACE		= LX_LOGM_LEVEL_TRACE,			/* 5 */
	LOG_LEVEL_DRV,				/* 6 */
	LOG_LEVEL_ISR,				/* 7 */
	LOG_LEVEL_CIS_INFO,			/* 8 */
	LOG_LEVEL_CIS_TUPLE,		/* 9 */
	LOG_LEVEL_CIS_PARSE,		/* 10 */
	LOG_LEVEL_CIS_ERR,			/* 11 */
	LOG_LEVEL_CIS_CIPLUS,		/* 12 */
	LOG_LEVEL_CIS_TUPLE2,		/* 13 */
	LOG_LEVEL_CIS_PARSE2,		/* 14 */
	LOG_LEVEL_CIS_RSVD2,		/* 15 */ //TODO:Check
	LOG_LEVEL_IO_INFO,			/* 16 */
	LOG_LEVEL_DBG1,				/* 17 */
	LOG_LEVEL_DBG2,				/* 18 */
	LOG_LEVEL_DBG3,				/* 19 */

	LOG_LEVEL_CIS_RSVD3,		/* 20 */ //TODO:Check
	LOG_LEVEL_CIS_RSVD4,		/* 21 */ //TODO:Check
	LOG_LEVEL_CIS_RSVD5,		/* 22 */ //TODO:Check
	LOG_LEVEL_CIS_RSVD6,		/* 23 */ //TODO:Check
	LOG_LEVEL_PROC_LVL1,		/* 24 */
	LOG_LEVEL_PROC_LVL2,		/* 25 */
	LOG_LEVEL_PROC_LVL3,		/* 26 */
	LOG_LEVEL_PROC_LVL4,		/* 27 */
	LOG_LEVEL_CIS_RSVD7,		/* 28 */ //TODO:Check
	LOG_LEVEL_CIS_RSVD8,		/* 29 */ //TODO:Check
	LOG_LEVEL_CIS_RSVD9,		/* 30 */ //TODO:Check
	LOG_LEVEL_MONITOR,			/* 31 */
};


#define CI_LOG(type,fmt,args...)		LOGM_PRINT(g_ci_debug_fd, LOG_LEVEL_##type, fmt, ##args)

#define LOG_ERROR(fmt,args...)			CI_LOG(ERROR,fmt,##args)
#define LOG_WARNING(fmt,args...)		CI_LOG(WARNING,fmt,##args)
#define LOG_NOTI(fmt,args...)			CI_LOG(NOTI,fmt,##args)
#define LOG_INFO(fmt,args...)			CI_LOG(INFO,fmt,##args)
#define LOG_DEBUG(fmt,args...)			CI_LOG(DEBUG,fmt,##args)
#define LOG_TRACE(fmt,args...)			CI_LOG(TRACE,fmt,##args)
#define LOG_DRV(fmt,args...)			CI_LOG(DRV,fmt,##args)
#define LOG_ISR(fmt,args...)			CI_LOG(ISR,fmt,##args)
#define LOG_CIS_INFO(fmt,args...)		CI_LOG(CIS_INFO,fmt,##args)
#define LOG_CIS_TUPLE(fmt,args...)		CI_LOG(CIS_TUPLE,fmt,##args)
#define LOG_CIS_PARSE(fmt,args...)		CI_LOG(CIS_PARSE,fmt,##args)
#define LOG_CIS_ERR(fmt,args...)		CI_LOG(CIS_ERR,fmt,##args)
#define LOG_CIS_CIPLUS(fmt,args...)		CI_LOG(CIS_CIPLUS,fmt,##args)
#define LOG_CIS_TUPLE2(fmt,args...)		CI_LOG(CIS_TUPLE2,fmt,##args)
#define LOG_CIS_PARSE2(fmt,args...)		CI_LOG(CIS_PARSE2,fmt,##args)
#define LOG_IO_INFO(fmt,args...)		CI_LOG(IO_INFO,fmt,##args)
#define LOG_DBG1(fmt,args...)			CI_LOG(DBG1,fmt,##args)
#define LOG_DBG2(fmt,args...)			CI_LOG(DBG2,fmt,##args)
#define LOG_DBG3(fmt,args...)			CI_LOG(DBG3,fmt,##args)
#define LOG_PROC_LVL1(fmt,args...)		CI_LOG(PROC_LVL1,fmt,##args)
#define LOG_PROC_LVL2(fmt,args...)		CI_LOG(PROC_LVL2,fmt,##args) //not used
#define LOG_PROC_LVL3(fmt,args...)		CI_LOG(PROC_LVL3,fmt,##args) //not used
#define LOG_PROC_LVL4(fmt,args...)		CI_LOG(PROC_LVL4,fmt,##args)
#define LOG_DMA_DRV(fmt,args...)		CI_LOG(DMA_DRV,fmt,##args)
#define LOG_DMA_DBG1(fmt,args...)		CI_LOG(DMA_DBG1,fmt,##args)
#define LOG_DMA_DBG2(fmt,args...)		CI_LOG(DMA_DBG2,fmt,##args)
#define LOG_MONITOR(fmt,args...)		CI_LOG(MONITOR,fmt,##args)

#define LOG_DRV2(format, args...)		LOG_DRV("  " format, ##args)


#define	cim_time_ms(_start, _end)			\
		do {								\
			LOG_NOTI("elapsed[%lld ms]\n",	ktime_to_ms(ktime_sub(_end, _start)));	\
		} while(0)

#define	cim_time_us_io(_start, _end, _size)	\
		do {								\
			LOG_NOTI("size[%d], elapsed[%lld us] %s\n",				\
					_size, ktime_to_us(ktime_sub(_end, _start)),	\
					(_size)? "<<S>>" : "<<F>>");					\
		} while(0)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
	__CHECK_IF_ERROR(__checker, LOG_ERROR, __if_action , fmt, ##args )

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _CI_DEBUG_H_ */



