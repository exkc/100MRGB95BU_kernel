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

/** @file pe_kwrap_hst.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- histrogram functions
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

#include "pe_hst.h"

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
extern PE_KWRAP_INFO_T _g_pe_info;

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
 * get histogram info
 * - use input struct LX_PE_HST_HISTO_INFO_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetHistogramInfo(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_HST_HISTO1_INFO_T *pp = NULL;
		pp = (LX_PE_HST_HISTO1_INFO_T *)param;
		ret = PE_HST_GetHistogramInfo(pp);
	}
	else
	{
		LX_PE_HST_HISTO_INFO_T *pp = NULL;
		pp = (LX_PE_HST_HISTO_INFO_T *)param;
		ret = PE_HST_GetHistogramInfo(pp);
	}

	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set histogram config
 * - use input struct LX_PE_HST_HISTO_CFG_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetHistoConfig(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	UINT32 i=0;
	PE_KWRAP_INFO_T *p_inf = &_g_pe_info;
	PE_CHECK_KWRAP_FUNC_ON(HST);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_HST_HISTO_CFG_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_HST_HISTO_CFG_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_HST_HISTO_CFG_T *)param;
			PE_KWRAP_DBG_PRINT(HST, \
				"wid:%d, op:src_apl:%d, src_hist:%d, lrc_hist:%d\n", \
				pp->win_id, pp->opr.src_apl_op, pp->opr.src_hist_op, \
				pp->opr.lrc_hist_op);
			/* update hist info */
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				if (pp->win_id==i||pp->win_id==LX_PE_WIN_ALL)
					memcpy(&p_inf->hist_info[i], pp, sizeof(LX_PE_HST_HISTO_CFG_T));
			}
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_HST_HISTO_CFG_T, HST);
			#endif
			ret = PE_HST_SetHistoConfig(pp);
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
 * get histogram config
 * - use input struct LX_PE_HST_HISTO_CFG_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetHistoConfig(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_HST_GetHistoConfig((LX_PE_HST_HISTO_CFG_T *)param);
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
 * get histogram config info from stored value
 * - use input struct LX_PE_HST_HISTO_CFG_T for M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCurHistoConfig(void *param)
{
	int ret = RET_OK;
	PE_KWRAP_INFO_T *p_inf = &_g_pe_info;
	LX_PE_HST_HISTO_CFG_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		pp = (LX_PE_HST_HISTO_CFG_T *)param;
		if (pp->win_id>=LX_PE_WIN_ALL)
		{
			p_inf->hist_info[LX_PE_WIN_0].win_id = pp->win_id;
			memcpy(pp, &p_inf->hist_info[LX_PE_WIN_0], sizeof(LX_PE_HST_HISTO_CFG_T));
		}
		else
		{
			p_inf->hist_info[pp->win_id].win_id = pp->win_id;
			memcpy(pp, &p_inf->hist_info[pp->win_id], sizeof(LX_PE_HST_HISTO_CFG_T));
		}
		PE_KWRAP_DBG_PRINT(HST, \
			"wid:%d, op:src_apl:%d, src_hist:%d, lrc_hist:%d\n", \
			pp->win_id, pp->opr.src_apl_op, pp->opr.src_hist_op, \
			pp->opr.lrc_hist_op);
	}while (0);
	return ret;
}

#define _KWRAP_PE_WIN_

#define _KWRAP_PE_CSC_
/**
 * set xvycc scale value
 * - use input struct LX_PE_CSC_XVYCC_T for M14AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetXvYccScale(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CSC);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get xvycc scale value
 * - use input struct LX_PE_CSC_XVYCC_T for M14AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetXvYccScale(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get apl info
 * - use input struct LX_PE_HST_APL_INFO_T for M16
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetAplInfo(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_HST_GetAplInfo((LX_PE_HST_APL_INFO_T *)param);
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
 * get hdr info
 * - use input struct LX_PE_HST_HDR_INFO_T
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetHdrInfo(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get block apl data
 * - 
 *
 * @param  
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetBlkApl(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_HST_GetBlkApl((LX_PE_HST_BLK_APL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

