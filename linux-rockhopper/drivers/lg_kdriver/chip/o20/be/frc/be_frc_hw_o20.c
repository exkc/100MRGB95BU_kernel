/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 *	BE FRC module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>		/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>		/**< For ioremap_nocache */
#include "os_util.h"

#include "be_dbg.h"
#include "be_def.h"
#include "../fwi/ipc_def_o20.h"
#include "ipc_drv.h"
#include "be_frc_hw_o20.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

// For temporary
#include "../../../core/de/de_io.h"
#include "de_kapi.h"

#ifdef INCLUDE_KDRV_DE
#include "ipc_cmd_header.h"
#else
#define FRC_PACK_CMD(cmd) cmd
#endif

// For Status Management
#include "../../../core/be/video_status_keeper.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* temporal code (until int,ext frc type interface fixed) */
#undef BE_FRC_HW_O20_TEMP_USE_TYPE_BY_CTRL_SPATH

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#if 0
typedef struct {
	UINT8		u8Judder;
	UINT8		u8Blur;
	UINT8		u8MemcType;
	UINT8		u8LowDelay;
	UINT8		u8MotionPro;	
	UINT8		u8RGBYUV;
} BE_FRC_HW_O20_INFO_T;
#endif

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
//static BE_FRC_HW_O20_INFO_T _beFrcHwO20Info= {0,};
static BE_FRC_HW_O20_INFO_T _gBeFrcHwO20Info= {0,};
static BE_IPC_FRC_MEMC_MODE_T gPreMemcParam;
/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_FRC_HW_O20_Initialize(void)
{
	int ret = RET_OK;

	do {
		memset(&_gBeFrcHwO20Info, 0, sizeof(BE_FRC_HW_O20_INFO_T));
		memset(&gPreMemcParam, 0xff, sizeof(BE_IPC_FRC_MEMC_MODE_T));
		BE_NOTI("Done.\n ");
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Close(void)
{
	int ret = RET_OK;

	do {

	} while (0);

	return ret;
}

int BE_FRC_HW_O20_MemcResume(void)
{
	int ret = RET_OK;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_MEMC_MODE_T, stHwParams);

		stHwParams.uFRCBlur			 = gPreMemcParam.uFRCBlur;
		stHwParams.uFRCJudder		 = gPreMemcParam.uFRCJudder;
		stHwParams.uFRCUserLevel	 = gPreMemcParam.uFRCUserLevel;
		stHwParams.uFRCMotionProEn	 = gPreMemcParam.uFRCMotionProEn;

		/* Send command  to MCU via IPC & Check result */
		ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_MEMC_MODE), &stHwParams, sizeof(BE_IPC_FRC_MEMC_MODE_T));
		if (ret) BREAK_WRONG(ret);

		BE_NOTI("Done.\n ");

	} while(0);

	return ret;
}

int BE_FRC_HW_O20_ControlMemc(LX_BE_FRC_MEMC_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_MEMC_MODE_T, stHwParams);

		BE_TRACE1("%d, %d, %d -> %d, %d, %d\n", pstParams->u8MemcType, pstParams->u8Blur, pstParams->u8Judder,\
			_gBeFrcHwO20Info.u32MemcType, _gBeFrcHwO20Info.u32Blur, _gBeFrcHwO20Info.u32Judder);

		/* change value LX_BE to BE_IPC */
		stHwParams.uFRCBlur		= pstParams->u8Blur == 0xFF ? 0xFFFFFFFF : pstParams->u8Blur;
		stHwParams.uFRCJudder	= pstParams->u8Judder == 0xFF ? 0xFFFFFFFF : pstParams->u8Judder;
		stHwParams.uFRCUserLevel	= pstParams->u8MemcType == 0xFF ? 0xFFFFFFFF : pstParams->u8MemcType;

		 if (stHwParams.uFRCBlur != 0xFFFFFFFF)
			_gBeFrcHwO20Info.u32Blur  = stHwParams.uFRCBlur;

  	        if (stHwParams.uFRCJudder != 0xFFFFFFFF)
			_gBeFrcHwO20Info.u32Judder        = stHwParams.uFRCJudder;

               if (stHwParams.uFRCUserLevel != 0xFFFFFFFF)
			_gBeFrcHwO20Info.u32MemcType  = stHwParams.uFRCUserLevel;

		BE_TRACE1("%d, %d, %d -> %d, %d, %d\n", pstParams->u8MemcType, pstParams->u8Blur, pstParams->u8Judder,\
		_gBeFrcHwO20Info.u32MemcType, _gBeFrcHwO20Info.u32Blur, _gBeFrcHwO20Info.u32Judder);

		BE_FRC_HW_O20_SetMemcMode(&_gBeFrcHwO20Info);
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_SetMemcLowDelay(LX_BE_FRC_LOW_DELAY_T *pstParams)
{
	int ret = RET_OK;
	
	do {
 		BE_TRACE1("%d -> %d\n", pstParams->u32Lowdelay, _gBeFrcHwO20Info.u32LowDelay);
		
		if (pstParams->u32Lowdelay != 0xFFFFFFFF)
			_gBeFrcHwO20Info.u32LowDelay = pstParams->u32Lowdelay;

 		BE_TRACE1("%d -> %d\n", pstParams->u32Lowdelay, _gBeFrcHwO20Info.u32LowDelay);

		BE_FRC_HW_O20_SetMemcMode(&_gBeFrcHwO20Info);

		if (ret) BREAK_WRONG(ret);
	}while (0);

	return ret;
}

int BE_FRC_HW_O20_SetMemcMotionPro(LX_BE_FRC_MOTION_PRO_T *pstParams)
{
	int ret = RET_OK;

	do {
 		BE_TRACE1("%d -> %d\n", pstParams->u32MotionPro, _gBeFrcHwO20Info.u32MotionPro);
		
		 if (pstParams->u32MotionPro != 0xFFFFFFFF)
			_gBeFrcHwO20Info.u32MotionPro= pstParams->u32MotionPro;
 
		BE_FRC_HW_O20_SetMemcMode(&_gBeFrcHwO20Info);

		if (ret) BREAK_WRONG(ret);
	}while (0);

	return ret;
}

int BE_FRC_HW_O20_SetMemcMode(BE_FRC_HW_O20_INFO_T *_gBeFrcHwO20Info)
{
	int ret = RET_OK;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_MEMC_MODE_T, stHwParams);

		/* check error */
		if (!_gBeFrcHwO20Info)
		{
			BE_ERROR("_gBeFrcHwM17Info is null.\n");
			ret=RET_ERROR;	break;
		}

		#if 1	//add uFRCMotionProEn
		if (_gBeFrcHwO20Info->u32LowDelay == 1)
		{
			stHwParams.uFRCUserLevel= LX_BE_FRC_MEMC_DISABLE;
		}
		else
		{
			stHwParams.uFRCUserLevel= _gBeFrcHwO20Info->u32MemcType;
		}
		stHwParams.uFRCBlur	= _gBeFrcHwO20Info->u32Blur;
		stHwParams.uFRCJudder = _gBeFrcHwO20Info->u32Judder;
		stHwParams.uFRCMotionProEn = _gBeFrcHwO20Info->u32MotionPro;
		BE_TRACE1("%d,%d,%d/%d/%d -> MemcType(%d), Blur(%d), Judder(%d), MPro(%d)\n",\
			_gBeFrcHwO20Info->u32MemcType, _gBeFrcHwO20Info->u32Blur,_gBeFrcHwO20Info->u32Judder,\
			_gBeFrcHwO20Info->u32LowDelay, _gBeFrcHwO20Info->u32MotionPro, stHwParams.uFRCUserLevel,\
			stHwParams.uFRCBlur, stHwParams.uFRCJudder, stHwParams.uFRCMotionProEn);
		#else	//org

		if (_gBeFrcHwO20Info->u32LowDelay == 1)
		{
			stHwParams.uFRCBlur	= _gBeFrcHwO20Info->u32Blur;		
			stHwParams.uFRCJudder= _gBeFrcHwO20Info->u32Judder;
			stHwParams.uFRCUserLevel= LX_BE_FRC_MEMC_DISABLE;				
		}
		else if (_gBeFrcHwO20Info->u32MotionPro ==1)
		{
			stHwParams.uFRCUserLevel = LX_BE_FRC_MEMC_MIDIUM;
		}	
		else
		{
			stHwParams.uFRCBlur	= _gBeFrcHwO20Info->u32Blur;
			stHwParams.uFRCJudder= _gBeFrcHwO20Info->u32Judder;
			stHwParams.uFRCUserLevel= _gBeFrcHwO20Info->u32MemcType;	
		}

		BE_TRACE1("%d,%d,%d/%d/%d -> MemcType(%d), Blur(%d), Judder(%d)\n",\
			_gBeFrcHwO20Info->u32MemcType, _gBeFrcHwO20Info->u32Blur,_gBeFrcHwO20Info->u32Judder,\
			_gBeFrcHwO20Info->u32LowDelay, _gBeFrcHwO20Info->u32MotionPro, stHwParams.uFRCUserLevel,\
			stHwParams.uFRCBlur, stHwParams.uFRCJudder);
		#endif

		if(memcmp(&gPreMemcParam,&stHwParams,sizeof(BE_IPC_FRC_MEMC_MODE_T)) != 0)
		{
			/* Send command  to MCU via IPC & Check result */
			ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_MEMC_MODE), &stHwParams, sizeof(BE_IPC_FRC_MEMC_MODE_T));
			if (ret) BREAK_WRONG(ret);

			BE_TRACE1("%d,%d,%d,%d -> uFRCUserLevel(%d), uFRCBlur(%d), uFRCJudder(%d), uFRCMotionProEn(%d)\n",\
				gPreMemcParam.uFRCUserLevel,gPreMemcParam.uFRCBlur, gPreMemcParam.uFRCJudder, gPreMemcParam.uFRCMotionProEn,\
				stHwParams.uFRCUserLevel,stHwParams.uFRCBlur, stHwParams.uFRCJudder, stHwParams.uFRCMotionProEn);

			gPreMemcParam.uFRCBlur = stHwParams.uFRCBlur;
			gPreMemcParam.uFRCJudder = stHwParams.uFRCJudder;
			gPreMemcParam.uFRCUserLevel = stHwParams.uFRCUserLevel;
			gPreMemcParam.uFRCMotionProEn = stHwParams.uFRCMotionProEn;
		}
	}while (0);

	return ret;
}


int BE_FRC_HW_O20_SetConfig(LX_BE_FRC_CFG_T *pstParams)
{
	int ret = RET_OK;
	do {
		/* check error */
		if (!pstParams)
		{
			BE_ERROR("pstParams is null.\n");
			ret=RET_ERROR;	break;
		}
		if (pstParams->cfg_type>LX_BE_FRC_CFG_TYPE_ALL)
		{
			BE_ERROR("cfg_type(%d) is wrong.\n", pstParams->cfg_type);
			ret=RET_ERROR;	break;
		}
		if (pstParams->cfg_type==LX_BE_FRC_CFG_TYPE_NONE)
		{
			BE_ERROR("cfg_type is none.\n");
			ret=RET_ERROR;	break;
		}
		/* use_type */
		if (pstParams->cfg_type&LX_BE_FRC_CFG_TYPE_USE)
		{
			#ifdef BE_FRC_HW_O20_TEMP_USE_TYPE_BY_CTRL_SPATH
			volatile UINT32 *pRdata = NULL;
			do {
				/* TOP CCO_CTRL(0xC8024024) CTRL_SPATH [20]ctrl_sosd_src_hs : 0x0:blended, 0x1:seperate */
				pRdata = (volatile UINT32 *)ioremap(0xC8024024, sizeof(UINT32));
				if (pRdata==NULL)	break;
				pstParams->use_type = (pstParams->use_type<<16)|(((*pRdata)&0x00100000)? 0x1:0x0);//1:ext,0:int
				ret |= BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_USE_TYPE), &(pstParams->use_type), sizeof(UINT32));
			} while(0);
			if (pRdata) iounmap((void *)pRdata);
			#else
			ret |= BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_USE_TYPE), &(pstParams->use_type), sizeof(UINT32));
			#endif
		}
		/* dfr_type */
		if (pstParams->cfg_type==LX_BE_FRC_CFG_TYPE_DFR)
		{
			BE_ERROR("cfg_type is LX_BE_FRC_CFG_TYPE_DFR. under contruct\n");
			ret=RET_OK;	break;
		}
		/* others */
		if (ret) BREAK_WRONG(ret);
	} while (0);
	return ret;
}

int BE_FRC_HW_O20_RunCommand(LX_BE_FRC_CMD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 strLen;
	do {
		/* check error */
		if (!pstParams)
		{
			BE_ERROR("pstParams is null.\n");
			ret=RET_ERROR;	break;
		}
		strLen = strlen(pstParams->str);
		if (strLen>64)	strLen=64;
		ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_B0_RUN_COMMAND), pstParams->str, strLen);
		if (ret) BREAK_WRONG(ret);
		//BE_NOTI("RunCommand : %s (%d)\n",pstParams->str, strLen);
	} while (0);
	return ret;
}

int BE_FRC_HW_O20_Set_Demo_Mode(LX_BE_FRC_DEMO_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {

	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Set_Debug_Box(LX_BE_FRC_ENABLE_DEBUG_BOX_T *pstParams)
{
	int ret = RET_OK;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_ENABLE_DEBUG_BOX_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		if (pstParams->u16FRCDebugBoxOn)
		{
			stHwParams.uDeboxMode = pstParams->u16FRCDebugBoxMode;
		}
		else
		{
			stHwParams.uDeboxMode = 0;
		}

		/* Send command  to MCU via IPC & Check result */
		ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_ENABLE_DEBUG_BOX), &stHwParams, sizeof(BE_IPC_FRC_ENABLE_DEBUG_BOX_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Set_Bypass_Memc_Reg(LX_BE_FRC_MEMC_BYPASS_REGION_T *pstParams)
{
	int ret = RET_OK;

	do {

	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Set_YUV_444_Mode(LX_BE_FRC_COLOR_YUV444_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status = 0;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_COLOR_YUV444_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bFRCProcYUV444 = pstParams->u8ColorYuv == 0xFF ? 0xFFFFFFFF : pstParams->u8ColorYuv;

		/* For Status Management */
		status = (unsigned int)stHwParams.bFRCProcYUV444;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_FRC_RGB_YUV_MODE, status);


		/* Send command  to MCU via IPC & Check result */
		ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_YUV444), &stHwParams, sizeof(BE_IPC_FRC_COLOR_YUV444_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Set_Low_Delay(LX_BE_FRC_LOW_DELAY_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status = 0;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_LOW_DELAY_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bFRCLowDelay	= pstParams->u32Lowdelay;

		/* For Status Management */
		status = (unsigned int)stHwParams.bFRCLowDelay;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_FRC_LOW_DELAY_MODE, status);

		/* Send command  to MCU via IPC & Check result */
		ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_LOW_DELAY), &stHwParams, sizeof(BE_IPC_FRC_LOW_DELAY_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Get_Firmware_Ver(LX_BE_FRC_VERSION_T *pstParams)
{
	int ret = RET_OK;

	do {

	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Force_Frame_Rate(LX_BE_FRC_FRAME_RATE_T *pstParams)
{
	int ret = RET_OK;

	do {

	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Set_Freeze(LX_BE_FRC_FREEZE_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_FRC_FREEZE_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bFRCFreeze	= pstParams->u32Freeze;

		/* For Status Management */
		status = (unsigned int)stHwParams.bFRCFreeze;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_FRC_FREEZE, status);

		/* Send command  to MCU via IPC & Check result */
		ret = BE_KIPC_SetData(FRC_PACK_CMD(BE_FRC_SET_FREEZE), &stHwParams, sizeof(BE_IPC_FRC_FREEZE_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_Update_FrameDelay(LX_BE_LOW_DELAY_T *pstParams)
{
	int ret = RET_OK;

	do {
		//ret = DE_IO_GetLowDelay((unsigned long)pstParams);
		/* Never use DE_IO on BE kdriver */
	} while (0);

	return ret;
}

int BE_FRC_HW_O20_ProcHandler(BE_FRC_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_FRC_PROC_ID_DETAIL_INFO:
		{

		}
		break;

		default: break;
	}

	return RET_OK;
}

/** @} */
