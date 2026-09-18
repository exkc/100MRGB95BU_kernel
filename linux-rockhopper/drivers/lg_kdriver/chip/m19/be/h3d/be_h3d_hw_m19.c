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
 *  drv file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_h3d_hw_m19.h"
#include "be_def.h"
#include "../fwi/ipc_def_m19.h"
#include "ipc_drv.h"

#include "ipc_cmd_header.h"

// For Status Management
#include "../../../core/be/video_status_keeper.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
//#define USE_BE_IOCTL_MACROS
#define CONV_ENABLE 1
#define CONV_DISABLE 0

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/
/**
 *  main control block for BE device.
 *  each minor device has unique control block
 *
 */
typedef struct {
	BOOLEAN bT3CMode;
} BE_H3D_HW_M19_INFO_T;

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/
static BE_H3D_HW_M19_INFO_T _gBeH3dHwM19Info = {
	.bT3CMode = FALSE,
};

/*========================================================================================
  Implementation Group
  ========================================================================================*/
int BE_H3D_HW_M19_Set_Mode(LX_BE_H3D_MODE_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status = 0;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_H3D_MODE_T, stHwParams);

		if ( pstParams->bT3CMode > 1 )
		{
			BE_ERROR("Invalied params[1: on, 0: off] bT3CMode = %d\n", pstParams->bT3CMode);
			return RET_INVALID_PARAMS; /* out of range (1: on, 0: off) */
		}

		stHwParams.uT3CMode = pstParams->bT3CMode == 0xFFFF ? 0xFFFFFFFF : pstParams->bT3CMode;

		/* For Status Management */
		status = stHwParams.uT3CMode;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_3D_MODE, status);

		ret = BE_KIPC_SetData(H3D_PACK_CMD(BE_H3D_SET_MODE), &stHwParams, sizeof(BE_IPC_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);

		if (stHwParams.uT3CMode != 0xFFFFFFFF)
		{
			_gBeH3dHwM19Info.bT3CMode = (BOOLEAN)stHwParams.uT3CMode;
		}
	} while(0);
	return ret;
}

int BE_H3D_HW_M19_Get_Mode(LX_BE_H3D_MODE_T *pstParams)
{
	int ret = RET_OK;

	do{
		pstParams->bA3CMode = FALSE;
		pstParams->bT3CMode = _gBeH3dHwM19Info.bT3CMode;
	} while(0);
	return ret;
}

int BE_H3D_HW_M19_T3C_Depth_Level(LX_BE_H3D_T3C_DEPTH_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status = 0;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_H3D_T3C_DEPTH_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uT3CDepth = pstParams->u32T3CDepthLevel;

		/* For Status Management */
		status = (unsigned int)stHwParams.uT3CDepth;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_2D_TO_3D_DEPTH, status);

		ret = BE_KIPC_SetData(H3D_PACK_CMD(BE_H3D_T3C_DEPTH_LEVEL), &stHwParams, sizeof(BE_IPC_H3D_T3C_DEPTH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_HW_M19_Set_TridFmt( LX_BE_TRIDTV_FMT_CTRL_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status = 0;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_H3D_MODE_T, stHwParams1);
		IPC_SET_DEFAULT_PARAM(BE_IPC_H3D_T3C_DEPTH_T, stHwParams4);
		IPC_SET_DEFAULT_PARAM(BE_IPC_3D_CONVERGENCE_T, stHwParams5);

		switch (pstParams->lx_mode)
		{
			case LX_TRIDTV_3DMODE_ON:
				{
					stHwParams1.uT3CMode = 0; // 0:off, 1:on
					stHwParams5.bTDConvEnable = CONV_ENABLE;
					stHwParams5.uTDConvVal = (UINT32)(pstParams->convCtrl+10);
				}
				break;

			case LX_TRIDTV_3DMODE_2DTO3D:
				{
					stHwParams1.uT3CMode = 1; // 0:off, 1:on
					stHwParams5.bTDConvEnable = CONV_ENABLE;
					stHwParams5.uTDConvVal = (UINT32)(pstParams->convCtrl+10);
				}
				break;
			case LX_TRIDTV_3DMODE_3DTO2D:
			case LX_TRIDTV_3DMODE_OFF:
				stHwParams1.uT3CMode = 0; // 0:off, 1:on
				stHwParams5.bTDConvEnable = CONV_DISABLE;
				stHwParams5.uTDConvVal = (UINT32)(pstParams->convCtrl+10);
				break;

			default:
				BE_ERROR("lx_mode is invalied param for[M19]\n");
				BREAK_WRONG(-1);
				break;
		}

		/* For Status Management */
		status = stHwParams1.uT3CMode;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_3D_MODE, status);
		status = (0xFFFF0000&(stHwParams5.bTDConvEnable<<16))|(0x0000FFFF&(stHwParams5.uTDConvVal));
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_CONVERGENCE, status);

		if(stHwParams1.uT3CMode == 1)
		{
			/* change value LX_BE to BE_IPC */
			stHwParams4.uT3CDepth = pstParams->depthCtrl;
			/* return unexpected value */
			ret = BE_KIPC_SetData(H3D_PACK_CMD(BE_H3D_T3C_DEPTH_LEVEL), &stHwParams4, sizeof(BE_IPC_H3D_T3C_DEPTH_T));
			if(ret) BREAK_WRONG(ret);
			msleep(20);
		}

		/* return unexpected value */
		ret = BE_KIPC_SetData(H3D_PACK_CMD(BE_H3D_SET_MODE), &stHwParams1, sizeof(BE_IPC_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_3D_CONVERGENCE), (void *)&stHwParams5, sizeof(BE_IPC_3D_CONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);

		_gBeH3dHwM19Info.bT3CMode = (BOOLEAN)stHwParams1.uT3CMode;	
	} while(0);
	return ret;
}

int BE_H3D_HW_M19_ProcHandler(BE_H3D_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_H3D_PROC_ID_DETAIL_INFO:
		{

		}
		break;

		default: break;
	}

	return RET_OK;
}

