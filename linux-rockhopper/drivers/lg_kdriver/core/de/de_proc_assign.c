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
 *  Linux proc interface for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *  author		LGSI (kanthiraj.s@lge.com)
 *  version		1.0
 *  date		2015.14.10
 *  note		Additional information.
 *
 *  @addtogroup lg1150_de
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "de_drv.h"
#include "de_def.h"
#include "de_proc_cmn.h"
#include "proc_util.h"
#include "debug_util.h"
#include <linux/string.h>
#include "de_io.h"
#include "resource_mgr.h"
#include "debug_util.h"
#include "os_util.h"
#include <linux/kallsyms.h>
#include <linux/vmalloc.h>


DE_Assign_Debug_Gbl_ptr_t DE_Assign_Debug_Gbl_ptr_array[MAX_DBG_FUNC] =
{
	DE_Assign_PanelType_Idx1,
	DE_Assign_FirmwareInfo_Idx2,
	DE_Assign_SysStatus_Idx3,
	DE_Assign_IFConfig_Idx4,
	DE_Assign_DisFmt_Idx5,
	DE_Assign_FrRate_Idx6,
	DE_Assign_FrRate_Idx7,
	DE_Assign_DisOutOnOff_Idx8,
	DE_Assign_InputSource_Idx9,
	DE_Assign_CviSrcType_IdxA,
	DE_Assign_CviFir_IdxB,
	DE_Assign_CSampleMode_IdxC,
	DE_Assign_ScalerInfo_IdxD,
	DE_Assign_SrcMirror_IdxE,
	DE_Assign_WinDimension_IdxF,
	DE_Assign_WinDimension_Idx10,
	DE_Assign_WinDimension_Idx11,
	DE_Assign_WinDimension_Idx12,
	DE_Assign_SetWinBlank_Idx13,
	DE_Assign_Color_Idx14,
	DE_Assign_InnerPattern_Idx15,
	DE_Assign_ActFormat_Idx16,
	DE_Assign_Zlist_Idx17,
	DE_Assign_Rect_Idx18,
	DE_Assign_MultiWinOnOff_Idx19,
	DE_Assign_SrcStatus_Idx1A,
	DE_Assign_3DInOutCtrl_Idx1B,
	DE_Assign_LowDelayModeOnOff_Idx1C,
	DE_Assign_LowDelay_Idx1D,
	DE_Assign_DvrDisFmt_Idx1E,
	DE_Assign_UDModeOnOff_Idx1F,
	DE_Assign_VTM_FrameInfo_Idx20,
	DE_Assign_VTMFrameInfo_Idx21,
	DE_Assign_WinFreeze_Idx22,
	DE_Assign_HDMIPort_Idx23,
	DE_Assign_Capacity_Idx24,
	DE_Assign_CviTpg_Idx25,
	DE_Assign_SetSubWin_Idx26,
	DE_Assign_CveParam_Idx27,
	DE_Assign_CviFreezeOnOff_Idx28,
	DE_Assign_CviRwVideoFrame_Idx29,
	DE_Assign_CaptureCtrl_Idx2A,
	DE_Assign_VcsIpc_Idx2B,
	DE_Assign_OperationCtrl_Idx2C,
	DE_Assign_RegRd_Idx2D,
	DE_Assign_RegWr_Idx2E,
	DE_Assign_UARTMCUMode_Idx2F,
	DE_Assign_SubOperationCtrl_Idx30,
};

/*========================================================================================
	Extern variables
========================================================================================*/

extern void *g_args;
extern DE_FUNCLIST gDE_FuncList[];
/*========================================================================================
	Implementation Group
========================================================================================*/

int DE_Assign_PanelType_Idx1 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_PANEL_TYPE_T *)OS_Malloc(sizeof(LX_DE_PANEL_TYPE_T));
	}
	offsetMax = sizeof(LX_DE_PANEL_TYPE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	*((LX_DE_PANEL_TYPE_T*)g_args) = iArgvalue;
	return ret;
}

int DE_Assign_FirmwareInfo_Idx2 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_FIRMWARE_INFO_T *)OS_Malloc(sizeof(LX_DE_FIRMWARE_INFO_T));
	}
	offsetMax = sizeof(LX_DE_FIRMWARE_INFO_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;
	return ret;
}

int DE_Assign_SysStatus_Idx3(int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_SYS_STATUS_T *)OS_Malloc(sizeof(LX_DE_SYS_STATUS_T));
	}
	offsetMax = sizeof(LX_DE_SYS_STATUS_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;
	printk("status_type = %d\n",((LX_DE_SYS_STATUS_T *)g_args)->status_type);
	return ret;
}

int DE_Assign_IFConfig_Idx4(int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_IF_CONFIG_T *)OS_Malloc(sizeof(LX_DE_IF_CONFIG_T));
	}
	offsetMax = sizeof(LX_DE_IF_CONFIG_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("config_type = %d, display_type = %d,display_mirror = %d,   frc_type = %d trid_type = %d\n",\
	((LX_DE_IF_CONFIG_T *)g_args)->config_type,((LX_DE_IF_CONFIG_T *)g_args)->display_type,((LX_DE_IF_CONFIG_T *)g_args)->display_mirror,\
	((LX_DE_IF_CONFIG_T *)g_args)->frc_type,((LX_DE_IF_CONFIG_T *)g_args)->trid_type);
	return ret;
}

int DE_Assign_DisFmt_Idx5 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_DIS_FMT_T *)OS_Malloc(sizeof(LX_DE_DIS_FMT_T));
	}
	offsetMax = sizeof(LX_DE_DIS_FMT_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("panel_type = %d, fr_rate = %d,h_total = %d,   v_total = %d h_active = %d v_active = %d dev_type = %d\n",\
	((LX_DE_DIS_FMT_T *)g_args)->panel_type,((LX_DE_DIS_FMT_T *)g_args)->fr_rate,((LX_DE_DIS_FMT_T *)g_args)->h_total,\
	((LX_DE_DIS_FMT_T *)g_args)->v_total,((LX_DE_DIS_FMT_T *)g_args)->h_active, ((LX_DE_DIS_FMT_T *)g_args)->v_active,((LX_DE_DIS_FMT_T *)g_args)->dev_type);
	return ret;
}

int DE_Assign_FrRate_Idx6 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_FR_RATE_T *)OS_Malloc(sizeof(LX_DE_FR_RATE_T));
	}
	offsetMax = sizeof(LX_DE_FR_RATE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("isForceFreeRun = %d, fr_rate = %d\n",\
	((LX_DE_FR_RATE_T *)g_args)->isForceFreeRun,((LX_DE_FR_RATE_T *)g_args)->fr_rate);
	return ret;
}

int DE_Assign_FrRate_Idx7 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_FR_RATE_T *)OS_Malloc(sizeof(LX_DE_FR_RATE_T));
	}
	offsetMax = sizeof(LX_DE_FR_RATE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("isForceFreeRun = %d, fr_rate = %d\n",\
	((LX_DE_FR_RATE_T *)g_args)->isForceFreeRun,((LX_DE_FR_RATE_T *)g_args)->fr_rate);
	return ret;
}

int DE_Assign_DisOutOnOff_Idx8 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (BOOLEAN *)OS_Malloc(sizeof(BOOLEAN));
	}
	offsetMax = sizeof(BOOLEAN)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	*((BOOLEAN*)g_args) = iArgvalue;

	printk("DisOut ON/OFF = %d\n",	*((BOOLEAN *)g_args));
	return ret;
}

int DE_Assign_InputSource_Idx9 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_INPUT_SOURCE_T *)OS_Malloc(sizeof(LX_DE_INPUT_SOURCE_T));
	}
	offsetMax = sizeof(LX_DE_INPUT_SOURCE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("srcId = %d, srcType = %d, srcPort = %d,   srcAttr = %d \n",\
	((LX_DE_INPUT_SOURCE_T *)g_args)->srcId,((LX_DE_INPUT_SOURCE_T *)g_args)->srcType,((LX_DE_INPUT_SOURCE_T *)g_args)->srcPort,\
	((LX_DE_INPUT_SOURCE_T *)g_args)->srcAttr);
	return ret;
}

int DE_Assign_CviSrcType_IdxA (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_CVI_SRC_TYPE_T *)OS_Malloc(sizeof(LX_DE_CVI_SRC_TYPE_T));
	}
	offsetMax = sizeof(LX_DE_CVI_SRC_TYPE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("cvi_channel = %d, size_offset.hsize = %d, size_offset.vsize = %d, size_offset.hoffset = %d,size_offset.voffset = %d, \n\
color = %d, aspect = %d scan = %d bit_res = %d c_sample = %d de_mode = %d \n\
sampling = %d sc_c_sample = %d stability = %d field_polarity = %d yc_delay = %d cvi_port = %d trid_full_format = %d\n\
cvi_input_src = %d cvd_color_std = %d\n",\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvi_channel,((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.hsize,((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.vsize,\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.hoffset,((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.voffset,((LX_DE_CVI_SRC_TYPE_T *)g_args)->color,\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->aspect,((LX_DE_CVI_SRC_TYPE_T *)g_args)->scan,((LX_DE_CVI_SRC_TYPE_T *)g_args)->bit_res,\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->c_sample,((LX_DE_CVI_SRC_TYPE_T *)g_args)->de_mode,((LX_DE_CVI_SRC_TYPE_T *)g_args)->sampling,\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->sc_c_sample,((LX_DE_CVI_SRC_TYPE_T *)g_args)->stability,((LX_DE_CVI_SRC_TYPE_T *)g_args)->field_polarity,\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->yc_delay,((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvi_port,((LX_DE_CVI_SRC_TYPE_T *)g_args)->trid_full_format,\
	((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvi_input_src,((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvd_color_std);
	return ret;
}

int DE_Assign_CviFir_IdxB (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;
	int i;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_CVI_FIR_T *)OS_Malloc(sizeof(LX_DE_CVI_FIR_T));
	}
	offsetMax = sizeof(LX_DE_CVI_FIR_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("cvi_channel = %d, isEnable = %d\n",((LX_DE_CVI_FIR_T *)g_args)->cvi_channel,((LX_DE_CVI_FIR_T *)g_args)->isEnable);
	for(i=0;i<8;i++){
		printk("fir_coef[%d] = %d ",i,((LX_DE_CVI_FIR_T *)g_args)->fir_coef[i]);
	}
	printk("\n");
	for(i=0;i<6;i++){
		printk("fir_coef_CbCr[%d] = %d ",i,((LX_DE_CVI_FIR_T *)g_args)->fir_coef_CbCr[i]);
	}
	printk("\n");
	return ret;
}

int DE_Assign_CSampleMode_IdxC (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_CSAMPLE_MODE_T *)OS_Malloc(sizeof(LX_DE_CSAMPLE_MODE_T));
	}
	offsetMax = sizeof(LX_DE_CSAMPLE_MODE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("cvi_channel = %d, is3tap = %d\n",((LX_DE_CSAMPLE_MODE_T *)g_args)->cvi_channel,((LX_DE_CSAMPLE_MODE_T *)g_args)->is3tap);
	return ret;
}

int DE_Assign_ScalerInfo_IdxD (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_SCALER_INFO_T *)OS_Malloc(sizeof(LX_DE_SCALER_INFO_T));
	}
	offsetMax = sizeof(LX_DE_SCALER_INFO_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;
	printk("win_id = %d\n",((LX_DE_SCALER_INFO_T *)g_args)->win_id);
	return ret;
}

int DE_Assign_SrcMirror_IdxE (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_SRC_MIRROR_T *)OS_Malloc(sizeof(LX_DE_SRC_MIRROR_T));
	}
	offsetMax = sizeof(LX_DE_SRC_MIRROR_T)/sizeof(int);
	if(iArgOffset>offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("srcPort = %d, destPort = %d enable = %d\n",((LX_DE_SRC_MIRROR_T *)g_args)->srcPort,((LX_DE_SRC_MIRROR_T *)g_args)->destPort,((LX_DE_SRC_MIRROR_T *)g_args)->enable);
	return ret;
}

int DE_Assign_WinDimension_IdxF (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_WIN_DIMENSION_T *)OS_Malloc(sizeof(LX_DE_WIN_DIMENSION_T));
	}
	offsetMax = sizeof(LX_DE_WIN_DIMENSION_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d\n",((LX_DE_WIN_DIMENSION_T *)g_args)->win_id);
	return ret;
}

int DE_Assign_WinDimension_Idx10 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_WIN_DIMENSION_T *)OS_Malloc(sizeof(LX_DE_WIN_DIMENSION_T));
	}
	offsetMax = sizeof(LX_DE_WIN_DIMENSION_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d rect.w = %d rect.h = %d rect.x = %d rect.y = %d\n",\
		((LX_DE_WIN_DIMENSION_T *)g_args)->win_id,((LX_DE_WIN_DIMENSION_T *)g_args)->rect.w,((LX_DE_WIN_DIMENSION_T *)g_args)->rect.h,\
		((LX_DE_WIN_DIMENSION_T *)g_args)->rect.x,((LX_DE_WIN_DIMENSION_T *)g_args)->rect.y);

	return ret;
}

int DE_Assign_WinDimension_Idx11 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_WIN_DIMENSION_T *)OS_Malloc(sizeof(LX_DE_WIN_DIMENSION_T));
	}
	offsetMax = sizeof(LX_DE_WIN_DIMENSION_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d\n",((LX_DE_WIN_DIMENSION_T *)g_args)->win_id);
	return ret;
}

int DE_Assign_WinDimension_Idx12 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_WIN_DIMENSION_T *)OS_Malloc(sizeof(LX_DE_WIN_DIMENSION_T));
	}
	offsetMax = sizeof(LX_DE_WIN_DIMENSION_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d rect.w = %d rect.h = %d rect.x = %d rect.y = %d\n",\
		((LX_DE_WIN_DIMENSION_T *)g_args)->win_id,((LX_DE_WIN_DIMENSION_T *)g_args)->rect.w,((LX_DE_WIN_DIMENSION_T *)g_args)->rect.h,\
		((LX_DE_WIN_DIMENSION_T *)g_args)->rect.x,((LX_DE_WIN_DIMENSION_T *)g_args)->rect.y);

	return ret;
}

int DE_Assign_SetWinBlank_Idx13 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_SET_WIN_BLANK_T *)OS_Malloc(sizeof(LX_DE_SET_WIN_BLANK_T));
	}
	offsetMax = sizeof(LX_DE_SET_WIN_BLANK_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d bEnable = %d win_color.r = %d win_color.g = %d win_color.b = %d isRGB = %d\n",\
		((LX_DE_SET_WIN_BLANK_T *)g_args)->win_id,((LX_DE_SET_WIN_BLANK_T *)g_args)->bEnable,((LX_DE_SET_WIN_BLANK_T *)g_args)->win_color.r,\
		((LX_DE_SET_WIN_BLANK_T *)g_args)->win_color.g,((LX_DE_SET_WIN_BLANK_T *)g_args)->win_color.b,((LX_DE_SET_WIN_BLANK_T *)g_args)->isRGB);
	return ret;
}

int DE_Assign_Color_Idx14 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_COLOR_T *)OS_Malloc(sizeof(LX_DE_COLOR_T));
	}
	offsetMax = sizeof(LX_DE_COLOR_T)/sizeof(int);
	if(iArgOffset>offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" r = %d g = %d b = %d \n",\
		((LX_DE_COLOR_T *)g_args)->r,((LX_DE_COLOR_T *)g_args)->g,((LX_DE_COLOR_T *)g_args)->b);
	return ret;
}

int DE_Assign_InnerPattern_Idx15 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_INNER_PATTERN_T *)OS_Malloc(sizeof(LX_DE_INNER_PATTERN_T));
	}
	offsetMax = sizeof(LX_DE_INNER_PATTERN_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" enable = %d type = %d level = %d \n",\
		((LX_DE_INNER_PATTERN_T *)g_args)->enable,((LX_DE_INNER_PATTERN_T *)g_args)->type,((LX_DE_INNER_PATTERN_T *)g_args)->level);
	return ret;
}

int DE_Assign_ActFormat_Idx16 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
		g_args = (LX_DE_ACT_FORMAT_T *)OS_Malloc(sizeof(LX_DE_ACT_FORMAT_T));
	}
	offsetMax = sizeof(LX_DE_ACT_FORMAT_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
	}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" enable = %d win_id = %d \n",\
		((LX_DE_ACT_FORMAT_T *)g_args)->enable,((LX_DE_ACT_FORMAT_T *)g_args)->win_id);
	return ret;
}

int DE_Assign_Zlist_Idx17 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_ZLIST_T *)OS_Malloc(sizeof(LX_DE_ZLIST_T));
	}
	offsetMax = sizeof(LX_DE_ZLIST_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" enable = %d z_list[0] = %d z_list[1] = %d alpha[0] = %d alpha[1] = %d\n",\
		((LX_DE_ZLIST_T *)g_args)->enable,((LX_DE_ZLIST_T *)g_args)->z_list[0],((LX_DE_ZLIST_T *)g_args)->z_list[1],\
		((LX_DE_ZLIST_T *)g_args)->alpha[0],((LX_DE_ZLIST_T *)g_args)->alpha[1]);
	return ret;
}

int DE_Assign_Rect_Idx18 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_RECT_T *)OS_Malloc(sizeof(LX_DE_RECT_T));
	}
	offsetMax = sizeof(LX_DE_RECT_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" w = %d h = %d x = %d y = %d \n",\
		((LX_DE_RECT_T *)g_args)->w,((LX_DE_RECT_T *)g_args)->h,((LX_DE_RECT_T *)g_args)->x,((LX_DE_RECT_T *)g_args)->y);
	return ret;
}

int DE_Assign_MultiWinOnOff_Idx19 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (BOOLEAN *)OS_Malloc(sizeof(BOOLEAN));
	}
	offsetMax = sizeof(BOOLEAN)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	*((BOOLEAN*)g_args) = iArgvalue;

	printk("Multi Win ON/OFF = %d\n",	*((BOOLEAN *)g_args));
	return ret;
}

int DE_Assign_SrcStatus_Idx1A (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_SRC_STATUS_T *)OS_Malloc(sizeof(LX_DE_SRC_STATUS_T));
	}
	offsetMax = sizeof(LX_DE_SRC_STATUS_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("status_type = %d\n",((LX_DE_SRC_STATUS_T *)g_args)->status_type);
	return ret;
}

int DE_Assign_3DInOutCtrl_Idx1B (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_3D_INOUT_CTRL_T *)OS_Malloc(sizeof(LX_DE_3D_INOUT_CTRL_T));
	}
	offsetMax = sizeof(LX_DE_3D_INOUT_CTRL_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" run_mode = %d in_img_fmt = %d in_lr_order = %d out_img_fmt = %d out_lr_order = %d\n",\
		((LX_DE_3D_INOUT_CTRL_T *)g_args)->run_mode,((LX_DE_3D_INOUT_CTRL_T *)g_args)->in_img_fmt,((LX_DE_3D_INOUT_CTRL_T *)g_args)->in_lr_order,\
		((LX_DE_3D_INOUT_CTRL_T *)g_args)->out_img_fmt,((LX_DE_3D_INOUT_CTRL_T *)g_args)->out_lr_order);
	return ret;
}

int DE_Assign_LowDelayModeOnOff_Idx1C (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (UINT32 *)OS_Malloc(sizeof(UINT32));
	}
	offsetMax = sizeof(UINT32)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	*((UINT32*)g_args) = iArgvalue;

	printk("Low Delay Mode ON/OFF = %d\n",	*((UINT32 *)g_args));
	return ret;
}

int DE_Assign_LowDelay_Idx1D (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_LOW_DELAY_T *)OS_Malloc(sizeof(LX_DE_LOW_DELAY_T));
	}
	offsetMax = sizeof(LX_DE_LOW_DELAY_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;
	printk("wId_enable = %d\n",((LX_DE_LOW_DELAY_T *)g_args)->wId_enable);
	return ret;
}

int DE_Assign_DvrDisFmt_Idx1E (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_DVR_DISFMT_T *)OS_Malloc(sizeof(LX_DE_DVR_DISFMT_T));
	}
	offsetMax = sizeof(LX_DE_DVR_DISFMT_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk(" bOnOff = %d scan = %d h_size = %d v_size = %d fr_rate = %d baseAddr = 0x%x\n",\
		((LX_DE_DVR_DISFMT_T *)g_args)->bOnOff,((LX_DE_DVR_DISFMT_T *)g_args)->scan,((LX_DE_DVR_DISFMT_T *)g_args)->h_size,\
		((LX_DE_DVR_DISFMT_T *)g_args)->v_size,((LX_DE_DVR_DISFMT_T *)g_args)->fr_rate,((LX_DE_DVR_DISFMT_T *)g_args)->baseAddr);
	return ret;
}

int DE_Assign_UDModeOnOff_Idx1F (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (BOOLEAN *)OS_Malloc(sizeof(BOOLEAN));
	}
	offsetMax = sizeof(BOOLEAN)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	*((BOOLEAN*)g_args) = iArgvalue;

	printk("UD Mode ON/OFF = %d\n",	*((BOOLEAN *)g_args));
	return ret;
}


int DE_Assign_VTM_FrameInfo_Idx20 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;
	int i;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_VTM_FRAME_INFO_T *)OS_Malloc(sizeof(LX_DE_VTM_FRAME_INFO_T));
	}
	offsetMax = sizeof(LX_DE_VTM_FRAME_INFO_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d, address = 0x%08x ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->win_id,((LX_DE_VTM_FRAME_INFO_T *)g_args)->address);
	printk("enable = %d, rate = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->enable,((LX_DE_VTM_FRAME_INFO_T *)g_args)->rate);
	printk("frz = %d, stride = %d, sampling = %d\n ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->frz,((LX_DE_VTM_FRAME_INFO_T *)g_args)->stride,\
		((LX_DE_VTM_FRAME_INFO_T *)g_args)->sampling);
	for(i=0;i<3;i++){
		printk("y_frame[%d] = 0x%08x \t c_frame[%d] = 0x%08x\n",i,((LX_DE_VTM_FRAME_INFO_T *)g_args)->y_frame[i],i,((LX_DE_VTM_FRAME_INFO_T *)g_args)->c_frame[i]);
		}
	printk("r_idx = %d, mute = 0x%08x\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->r_idx,((LX_DE_VTM_FRAME_INFO_T *)g_args)->mute);
	printk("srcSize.w = %d, srcSize.h = %d ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->srcSize.w,((LX_DE_VTM_FRAME_INFO_T *)g_args)->srcSize.h);
	printk("srcSize.x = %d, srcSize.y = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->srcSize.x,((LX_DE_VTM_FRAME_INFO_T *)g_args)->srcSize.y);
	printk("winSize.w = %d, winSize.h = %d ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->winSize.w,((LX_DE_VTM_FRAME_INFO_T *)g_args)->winSize.h);
	printk("winSize.x = %d, winSize.y = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->winSize.x,((LX_DE_VTM_FRAME_INFO_T *)g_args)->winSize.y);
	printk("mirror = %d, scan = %d, mem_fd = %d\n ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->mirror,((LX_DE_VTM_FRAME_INFO_T *)g_args)->scan,\
		((LX_DE_VTM_FRAME_INFO_T *)g_args)->mem_fd);
	#ifdef _USE_VT_EXTENTION_
	printk("ext_info.location = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.location);
	printk("ext_info.crop_size.w = %d, ext_info.crop_size.h = %d ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.crop_size.w,((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.crop_size.h);
	printk("ext_info.crop_size.x = %d, ext_info.crop_size.y = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.crop_size.x,((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.crop_size.y);
	printk("ext_info.w_out_size.w = %d, ext_info.w_out_size.h = %d ",((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.w_out_size.w,((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.w_out_size.h);
	printk("ext_info.w_out_size.x = %d, ext_info.w_out_size.y = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.w_out_size.x,((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.w_out_size.y);
	printk("ext_info.rate = %d, ext_info.frz = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.rate,((LX_DE_VTM_FRAME_INFO_T *)g_args)->ext_info.frz);
	#endif
	return ret;
}

int DE_Assign_VTMFrameInfo_Idx21 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_VTM_FRAME_INFO_T *)OS_Malloc(sizeof(LX_DE_VTM_FRAME_INFO_T));
	}
	offsetMax = sizeof(LX_DE_VTM_FRAME_INFO_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;
	printk("win_id = %d\n",((LX_DE_VTM_FRAME_INFO_T *)g_args)->win_id);
	return ret;
}

int DE_Assign_WinFreeze_Idx22 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_WIN_FREEZE_T *)OS_Malloc(sizeof(LX_DE_WIN_FREEZE_T));
	}
	offsetMax = sizeof(LX_DE_WIN_FREEZE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d, bEnable = %d location = %d\n",((LX_DE_WIN_FREEZE_T *)g_args)->win_id,((LX_DE_WIN_FREEZE_T *)g_args)->bEnable,((LX_DE_WIN_FREEZE_T *)g_args)->location);
	return ret;
}

int DE_Assign_HDMIPort_Idx23 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_HDMIPORT_T *)OS_Malloc(sizeof(LX_DE_HDMIPORT_T));
	}
	offsetMax = sizeof(LX_DE_HDMIPORT_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d, port_num = %d\n",\
	((LX_DE_HDMIPORT_T *)g_args)->win_id,((LX_DE_HDMIPORT_T *)g_args)->port_num);
	return ret;
}

int DE_Assign_Capacity_Idx24 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_CAPACITY_T *)OS_Malloc(sizeof(LX_DE_CAPACITY_T));
	}
	offsetMax = sizeof(LX_DE_CAPACITY_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;
	return ret;
}

int DE_Assign_CviTpg_Idx25 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_CVI_TPG_T *)OS_Malloc(sizeof(LX_DE_CVI_TPG_T));
	}
	offsetMax = sizeof(LX_DE_CVI_TPG_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("cvi_channel = %d, isPtnOn = %d, isFrzOn = %d,   isGBR = %d ptnColor = %d\n",\
	((LX_DE_CVI_TPG_T *)g_args)->cvi_channel,((LX_DE_CVI_TPG_T *)g_args)->isPtnOn,((LX_DE_CVI_TPG_T *)g_args)->isFrzOn,\
	((LX_DE_CVI_TPG_T *)g_args)->isGBR,((LX_DE_CVI_TPG_T *)g_args)->ptnColor);
	return ret;
}

int DE_Assign_SetSubWin_Idx26 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_SET_SUB_WIN_T *)OS_Malloc(sizeof(LX_DE_SET_SUB_WIN_T));
	}
	offsetMax = sizeof(LX_DE_SET_SUB_WIN_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d\n",\
	((LX_DE_SET_SUB_WIN_T *)g_args)->win_id);
	return ret;
}

int DE_Assign_CveParam_Idx27 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_CVE_PARAM_T *)OS_Malloc(sizeof(LX_DE_CVE_PARAM_T));
	}
	offsetMax = sizeof(LX_DE_CVE_PARAM_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("fb = %d, std = %d\n",\
	((LX_DE_CVE_PARAM_T *)g_args)->fb,((LX_DE_CVE_PARAM_T *)g_args)->std);
	return ret;
}

int DE_Assign_CviFreezeOnOff_Idx28 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_CVI_CAPTURE_FREEZE_T *)OS_Malloc(sizeof(LX_DE_CVI_CAPTURE_FREEZE_T));
	}
	offsetMax = sizeof(LX_DE_CVI_CAPTURE_FREEZE_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("bCaptureOnOff = %d, bCviFreezeOnOff = %d\n",\
	((LX_DE_CVI_CAPTURE_FREEZE_T *)g_args)->bCaptureOnOff,((LX_DE_CVI_CAPTURE_FREEZE_T *)g_args)->bCviFreezeOnOff);
	return ret;
}

int DE_Assign_CviRwVideoFrame_Idx29 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_CVI_RW_VIDEO_FRAME_T *)OS_Malloc(sizeof(LX_DE_CVI_RW_VIDEO_FRAME_T));
	}
	offsetMax = sizeof(LX_DE_CVI_RW_VIDEO_FRAME_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("region.win_id = %d, region.pixelGrabX = %d, region.pixelGrabY = %d, region.pixelGrabW = %d,region.pixelGrabH = %d, \n\
region.realPixelGrabW = %d, region.realPixelGrabH = %d region.colorSpace = %d region.colorDepth = %d color = %p bReadOnOff = %d \n\
frameAddr.phyFrameAddrY8 = %d frameAddr.phyFrameAddrC8 = %d frameAddr.phyFrameAddrY2 = %d frameAddr.phyFrameAddrC2 = %d frameAddr.stride = %d \n",\
	((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.win_id,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.pixelGrabX,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.pixelGrabY,\
	((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.pixelGrabW,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.pixelGrabH,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.realPixelGrabW,\
	((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.realPixelGrabH,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.colorSpace,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.colorDepth,\
	((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->color,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->bReadOnOff,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->frameAddr.phyFrameAddrY8,\
	((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->frameAddr.phyFrameAddrC8,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->frameAddr.phyFrameAddrY2,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->frameAddr.phyFrameAddrC2,\
	((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->frameAddr.stride);
	return ret;
}

int DE_Assign_CaptureCtrl_Idx2A (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_CAPTURE_CTRL_T *)OS_Malloc(sizeof(LX_DE_CAPTURE_CTRL_T));
	}
	offsetMax = sizeof(LX_DE_CAPTURE_CTRL_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d, location = %d, inWin.w = %d, inWin.h = %d,inWin.x = %d, inWin.y = %d,\n\
wOutSize = %d hOutSize = %d pixelFormat = %d p_y_frame = %p p_cbcr_frame = %p stride = %d \n",\
	((LX_DE_CAPTURE_CTRL_T *)g_args)->win_id,((LX_DE_CAPTURE_CTRL_T *)g_args)->location,((LX_DE_CAPTURE_CTRL_T *)g_args)->inWin.w,\
	((LX_DE_CAPTURE_CTRL_T *)g_args)->inWin.h,((LX_DE_CAPTURE_CTRL_T *)g_args)->inWin.x,((LX_DE_CAPTURE_CTRL_T *)g_args)->inWin.y,\
	((LX_DE_CAPTURE_CTRL_T *)g_args)->wOutSize,((LX_DE_CAPTURE_CTRL_T *)g_args)->hOutSize,((LX_DE_CAPTURE_CTRL_T *)g_args)->pixelFormat,\
	((LX_DE_CAPTURE_CTRL_T *)g_args)->p_y_frame,((LX_DE_CAPTURE_CTRL_T *)g_args)->p_cbcr_frame,((LX_DE_CAPTURE_CTRL_T *)g_args)->stride);
	return ret;
}

int DE_Assign_VcsIpc_Idx2B (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_VCS_IPC_T *)OS_Malloc(sizeof(LX_DE_VCS_IPC_T));
	}
	offsetMax = sizeof(LX_DE_VCS_IPC_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("inx = %d, data = %d\n",\
	((LX_DE_VCS_IPC_T *)g_args)->inx,((LX_DE_VCS_IPC_T *)g_args)->data);
	return ret;
}

int DE_Assign_OperationCtrl_Idx2C (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_OPERATION_CTRL_T *)OS_Malloc(sizeof(LX_DE_OPERATION_CTRL_T));
	}
	offsetMax = sizeof(LX_DE_OPERATION_CTRL_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d, operation = %d, multiCtrl = %d, udCtrl = %d,ctrl3D.run_mode = %d, ctrl3D.in_img_fmt = %d,\n\
ctrl3D.in_lr_order = %d ctrl3D.out_img_fmt = %d ctrl3D.out_lr_order = %d vencCtrl.bOnOff = 0x%x vencCtrl.scan = 0x%x vencCtrl.hSize = %d \n\
vencCtrl.vSize = %d vencCtrl.frRate = %d \n",\
	((LX_DE_OPERATION_CTRL_T *)g_args)->win_id,((LX_DE_OPERATION_CTRL_T *)g_args)->operation,((LX_DE_OPERATION_CTRL_T *)g_args)->multiCtrl,\
	((LX_DE_OPERATION_CTRL_T *)g_args)->udCtrl,((LX_DE_OPERATION_CTRL_T *)g_args)->ctrl3D.run_mode,((LX_DE_OPERATION_CTRL_T *)g_args)->ctrl3D.in_img_fmt,\
	((LX_DE_OPERATION_CTRL_T *)g_args)->ctrl3D.in_lr_order,((LX_DE_OPERATION_CTRL_T *)g_args)->ctrl3D.out_img_fmt,((LX_DE_OPERATION_CTRL_T *)g_args)->ctrl3D.out_lr_order,\
	((LX_DE_OPERATION_CTRL_T *)g_args)->vencCtrl.bOnOff,((LX_DE_OPERATION_CTRL_T *)g_args)->vencCtrl.scan,((LX_DE_OPERATION_CTRL_T *)g_args)->vencCtrl.hSize,\
	((LX_DE_OPERATION_CTRL_T *)g_args)->vencCtrl.vSize,((LX_DE_OPERATION_CTRL_T *)g_args)->vencCtrl.frRate);
	return ret;
}

int DE_Assign_RegRd_Idx2D (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (UINT32 *)OS_Malloc(sizeof(UINT32));
	}
	offsetMax = sizeof(UINT32)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	*((UINT32*)g_args) = iArgvalue;

	printk("DE Register address to read = 0x%x\n",	*((UINT32 *)g_args));
	return ret;
}

int DE_Assign_RegWr_Idx2E (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_REG_WR_T *)OS_Malloc(sizeof(LX_DE_REG_WR_T));
	}
	offsetMax = sizeof(LX_DE_REG_WR_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("wr_addr = 0x%08x, wr_data = 0x%08x\n",\
	((LX_DE_REG_WR_T *)g_args)->wr_addr,((LX_DE_REG_WR_T *)g_args)->wr_data);
	return ret;
}

int DE_Assign_UARTMCUMode_Idx2F (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (BOOLEAN *)OS_Malloc(sizeof(BOOLEAN));
	}
	offsetMax = sizeof(BOOLEAN)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	*((BOOLEAN*)g_args) = iArgvalue;

	printk("UART MCU mode = %d\n",	*((BOOLEAN *)g_args));
	return ret;
}

int DE_Assign_SubOperationCtrl_Idx30 (int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;
	int offsetMax;

	printk("Function DE_IO_%s iArgNo %d iArgvalue %d \n",gDE_FuncList[iFuncNo-1].sName,iArgOffset,iArgvalue);
	if(g_args == NULL){
	g_args = (LX_DE_SUB_OPERATION_CTRL_T *)OS_Malloc(sizeof(LX_DE_SUB_OPERATION_CTRL_T));
	}
	offsetMax = sizeof(LX_DE_SUB_OPERATION_CTRL_T)/sizeof(int);
	if(iArgOffset>=offsetMax || iArgOffset<0){
		printk("Invalid Offset\n");
		return RET_ERROR;
		}
	((int *)g_args)[iArgOffset] = iArgvalue;

	printk("win_id = %d, operation = %d, capture_enable = %d, vencCtrl.bOnOff = 0x%x vencCtrl.scan = 0x%x \n\
vencCtrl.hSize = %d vencCtrl.vSize = %d vencCtrl.frRate = %d \n",\
	((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->win_id,((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->operation,((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->capture_enable,\
	((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->vencCtrl.bOnOff,((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->vencCtrl.scan,((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->vencCtrl.hSize,\
	((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->vencCtrl.vSize,((LX_DE_SUB_OPERATION_CTRL_T *)g_args)->vencCtrl.frRate);
	return ret;
}


