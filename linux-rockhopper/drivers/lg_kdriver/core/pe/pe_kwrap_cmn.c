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

/** @file pe_kwrap_cmn.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- common control : cont, bright, hue, sat, gamma, wb, etc.
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

#include "pe_cmn.h"

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
 * set contrast
 * - use input struct LX_PE_CMN_CONTRAST_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetContrast(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMN);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMN_CONTRAST_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMN_CONTRAST_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMN_CONTRAST_T *)param;
			PE_KWRAP_DBG_PRINT(CMN, \
				"wid:%d, cont:%d\n", pp->win_id, pp->contrast);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMN_CONTRAST_T, CMN);
			#endif
			ret = PE_CMN_SetContrast(pp);
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
 * get contrast
 * - use input struct LX_PE_CMN_CONTRAST_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetContrast(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMN_GetContrast((LX_PE_CMN_CONTRAST_T *)param);
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
 * set brightness
 * - use input struct LX_PE_CMN_BRIGHTNESS_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetBrightness(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMN);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMN_BRIGHTNESS_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMN_BRIGHTNESS_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMN_BRIGHTNESS_T *)param;
			PE_KWRAP_DBG_PRINT(CMN, \
				"wid:%d, bri:%d\n", pp->win_id, pp->brightness);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMN_BRIGHTNESS_T, CMN);
			#endif
			ret = PE_CMN_SetBrightness(pp);
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
 * get brightness
 * - use input struct LX_PE_CMN_BRIGHTNESS_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetBrightness(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMN_GetBrightness((LX_PE_CMN_BRIGHTNESS_T *)param);
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
 * set saturation
 * - use input struct LX_PE_CMN_SATURATION_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSaturation(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMN);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMN_SATURATION_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMN_SATURATION_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMN_SATURATION_T *)param;
			PE_KWRAP_DBG_PRINT(CMN, \
				"wid:%d, sat:%d\n", pp->win_id, pp->saturation);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMN_SATURATION_T, CMN);
			#endif
			ret = PE_CMN_SetSaturation(pp);
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
 * get saturation
 * - use input struct LX_PE_CMN_SATURATION_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSaturation(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMN_SetSaturation((LX_PE_CMN_SATURATION_T *)param);
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
 * set hue
 * - use input struct LX_PE_CMN_HUE_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetHue(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMN);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMN_HUE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMN_HUE_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMN_HUE_T *)param;
			PE_KWRAP_DBG_PRINT(CMN, \
				"wid:%d, hue:%d\n", pp->win_id, pp->hue);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMN_HUE_T, CMN);
			#endif
			ret = PE_CMN_SetHue(pp);
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
 * get hue
 * - use input struct LX_PE_CMN_HUE_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetHue(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMN_GetHue((LX_PE_CMN_HUE_T *)param);
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
 * set level control
 * - use input struct LX_PE_CMN_LEVEL_CTRL_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLevelCtrl(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMN);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_O18)
	{
		LX_PE_CMN_LEVEL_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMN_LEVEL_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMN_LEVEL_CTRL_T *)param;
			PE_KWRAP_DBG_PRINT(CMN, \
				"wid:%d, ofs, cen, gain:%d, %d, %d\n", \
			pp->win_id, pp->offset, pp->center, pp->gain);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMN_LEVEL_CTRL_T, CMN);
			#endif
			ret = PE_CMN_SetLevelCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_CMN_SetLevelCtrl.\n", __F__, __L__);
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
 * get level control
 * - use input struct LX_PE_CMN_LEVEL_CTRL_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetLevelCtrl(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMN_GetLevelCtrl((LX_PE_CMN_LEVEL_CTRL_T *)param);
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
 * set vcp level control
 * - use input struct LX_PE_CMN_VCP_LEVEL_CTRL_T for M17
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetVcpLevelCtrl(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMN);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMN_VCP_LEVEL_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMN_VCP_LEVEL_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMN_VCP_LEVEL_CTRL_T *)param;
			PE_KWRAP_DBG_PRINT(CMN, \
				"wid:%d, enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pp->win_id,pp->enable,pp->center_position,\
			pp->contrast,pp->brightness,pp->saturation);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMN_VCP_LEVEL_CTRL_T, CMN);
			#endif
			ret = PE_CMN_SetVcpLevelCtrl(pp);
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
 * get vcp level control
 * - use input struct LX_PE_CMN_VCP_LEVEL_CTRL_T for M17
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetVcpLevelCtrl(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMN_GetVcpLevelCtrl((LX_PE_CMN_VCP_LEVEL_CTRL_T *)param);
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
 * set bypass blocks
 * - use input struct LX_PE_CMN_BYPASS_BLOCKS_T for M17
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetBypassBlocks(void *param)
{
	int ret = RET_ERROR;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		ret = PE_CMN_SetBypassBlocks((LX_PE_CMN_BYPASS_BLOCKS_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
