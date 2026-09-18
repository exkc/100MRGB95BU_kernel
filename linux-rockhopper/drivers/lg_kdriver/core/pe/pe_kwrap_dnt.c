/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file pe_kwrap_dnt.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- deinterlace and film mode
 *
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
		
#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
		
#include "pe_def.h"

#include "pe_dnt.h"

#include "pe_kwrap.h"
#include "pe_kwrap_def.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/
extern UINT32 g_pe_kwrap_ver_mask;

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

/**
 * set film mode
 * - use input struct LX_PE_DNT_FILMMODE_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetFilmMode(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(DNT);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 ||PE_KDRV_VER_O20 ||PE_KDRV_VER_M19)
	{
		LX_PE_DNT_FILMMODE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DNT_FILMMODE_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DNT_FILMMODE_T *)param;
			PE_KWRAP_DBG_PRINT(DNT, \
				"wid:%d, en:%d\n", pp->win_id, pp->enable);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DNT_FILMMODE_T, DNT);
			#endif
			ret = PE_DNT_SetFilmMode(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get film mode
 * - use input struct LX_PE_DNT_FILMMODE_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetFilmMode(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 ||PE_KDRV_VER_O20 ||PE_KDRV_VER_M19)
	{
		ret = PE_DNT_GetFilmMode((LX_PE_DNT_FILMMODE_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set low delay mode in deinterlacer
 * - use input struct LX_PE_DNT_LD_MODE_T for H15, M14BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLowDelayMode(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(DNT);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 ||PE_KDRV_VER_O20 ||PE_KDRV_VER_M19)
	{
		LX_PE_DNT_LD_MODE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DNT_LD_MODE_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DNT_LD_MODE_T *)param;
			PE_KWRAP_DBG_PRINT(DNT, \
				"wid:%d, en:%d\n", pp->win_id, pp->enable);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DNT_LD_MODE_T, DNT);
			#endif
			ret = PE_DNT_SetLowDelayMode(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get low delay mode in deinterlacer
 * - use input struct LX_PE_DNT_LD_MODE_T for H15, M14BX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetLowDelayMode(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 ||PE_KDRV_VER_O20 ||PE_KDRV_VER_M19)
	{
		ret = PE_DNT_GetLowDelayMode((LX_PE_DNT_LD_MODE_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}


