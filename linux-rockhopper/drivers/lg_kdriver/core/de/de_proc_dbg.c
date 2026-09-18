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


DE_Func_Debugger_ptr_t DE_Func_Debugger_ptr_array[MAX_DBG_FUNC] =
{
#ifdef ENABLE_PROC_FUNCTION
	DE_DBG_SetPanelType_Idx1,
	DE_DBG_GetFirmwareInfo_Idx2,
	DE_DBG_GetSystemStatus_Idx3,
	DE_DBG_SetInterfaceConfig_Idx4,
	DE_DBG_SetDisplayFormat_Idx5,
	DE_DBG_SetFrameRate_Idx6,
	DE_DBG_GetFrameRate_Idx7,
	DE_DBG_SetDisplayOut_Idx8,
	DE_DBG_SetWinPortSrc_Idx9,
	DE_DBG_SetCviSrcType_IdxA,
	DE_DBG_SetCviFir_IdxB,
	DE_DBG_SetCviCsampleMode_IdxC,
	DE_DBG_GetScalerInfo_IdxD,
	DE_DBG_SetSrcMirror_IdxE,
	DE_DBG_GetInputWin_IdxF,
	DE_DBG_SetInputWin_Idx10,
	DE_DBG_GetOutWin_Idx11,
	DE_DBG_SetOutWin_Idx12,
	DE_DBG_SetWinBlank_Idx13,
	DE_DBG_SetBgColor_Idx14,
	DE_DBG_SetInnerPattern_Idx15,
	DE_DBG_SetActFmtDetect_Idx16,
	DE_DBG_SetZList_Idx17,
	DE_DBG_SetMultiVision_Idx18,
	DE_DBG_MultiWinEnable_Idx19,
	DE_DBG_GetSourceStatus_Idx1A,
	DE_DBG_Set3DInOutCtrl_Idx1B,
	DE_DBG_SetLowDelay_Idx1C,
	DE_DBG_GetLowDelay_Idx1D,
	DE_DBG_SetDvrFmtCtrl_Idx1E,
	DE_DBG_SetUDMode_Idx1F,
	DE_DBG_SetVTM_Idx20,
	DE_DBG_GetVTM_Idx21,
	DE_DBG_SetWinFreeze_Idx22,
	DE_DBG_SetHDMIPort_Idx23,
	DE_DBG_GetCapacity_Idx24,
	DE_DBG_SetCviTpg_Idx25,
	DE_DBG_SetSubWindow_Idx26,
	DE_DBG_SetCve_Idx27,
	DE_DBG_SetCviFreeze_Idx28,
	DE_DBG_SetCviVideoFrameBuffer_Idx29,
	DE_DBG_SetCaptureControl_Idx2A,
	DE_DBG_SetVcs_Idx2B,
	DE_DBG_SetOperation_Idx2C,
	DE_DBG_RegRd_Idx2D,
	DE_DBG_RegWr_Idx2E,
	DE_DBG_SetUart4MCU_Idx2F,
	DE_DBG_SetSubOperation_Idx30,
#endif
};


/*========================================================================================
	Extern variables
========================================================================================*/

extern void *g_args;
/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef ENABLE_PROC_FUNCTION
int DE_DBG_SetPanelType_Idx1 (int iDefArgs)
{
	LX_DE_PANEL_TYPE_T panel_type = LX_PANEL_TYPE_3840;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		panel_type = LX_PANEL_TYPE_3840;
	} else {
		panel_type = *((LX_DE_PANEL_TYPE_T*)g_args);
	}
	//printk("g_args = %d\n",*((LX_DE_PANEL_TYPE_T*)g_args));
	//arg = (LX_DE_PANEL_TYPE_T __user*)&panel_type;
	arg = (unsigned long )&panel_type;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_Init);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_GetFirmwareInfo_Idx2 (int iDefArgs)
{
	LX_DE_FIRMWARE_INFO_T param = { 0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.version = 0 ;
		param.date.day = 0;
		param.date.month = 0;
		param.date.year = 0;
		param.ipc_count = 0;
	} else {
		param.version = ((LX_DE_FIRMWARE_INFO_T *)g_args)->version;
		param.date.day = ((LX_DE_FIRMWARE_INFO_T *)g_args)->date.day;
		param.date.month = ((LX_DE_FIRMWARE_INFO_T *)g_args)->date.month;
		param.date.year = ((LX_DE_FIRMWARE_INFO_T *)g_args)->date.year;
		param.ipc_count = ((LX_DE_FIRMWARE_INFO_T *)g_args)->ipc_count;
	}


	//arg = (LX_DE_FIRMWARE_INFO_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetFirmwareInfo);
	printk("	FirmWare ver. %d (%d/%d/%d).\n", param.version, param.date.year, param.date.month, param.date.day)	;
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_GetSystemStatus_Idx3 (int iDefArgs)
{
	LX_DE_SYS_STATUS_T sysParam;
	unsigned long arg;
	int ret = RET_OK;

	memset( &sysParam, 0, sizeof( LX_DE_SYS_STATUS_T ));

	if (0 == iDefArgs){
		sysParam.status_type = LX_DE_SYS_STATUS_ALL;

	} else {
		sysParam.status_type = ((LX_DE_SYS_STATUS_T *)g_args)->status_type;
		sysParam.display_mirror = ((LX_DE_SYS_STATUS_T *)g_args)->display_mirror;
		sysParam.display_size = ((LX_DE_SYS_STATUS_T *)g_args)->display_size;
		sysParam.display_type = ((LX_DE_SYS_STATUS_T *)g_args)->display_type;
		sysParam.fc_mem = ((LX_DE_SYS_STATUS_T *)g_args)->fc_mem;
		sysParam.frc_type = ((LX_DE_SYS_STATUS_T *)g_args)->frc_type;
		sysParam.trid_type = ((LX_DE_SYS_STATUS_T *)g_args)->trid_type;

	}

	//arg = (LX_DE_SYS_STATUS_T __user*)&sysParam;
	arg = (unsigned long)&sysParam;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetSystemStatus);
	printk("display_type = 0x%x, display_mirror = 0x%x, frc_type = 0x%x,trid_type = 0x%x, fc_mem = 0x%x, display_size = 0x%x,    \n",\
		sysParam.display_type,sysParam.display_mirror,sysParam.frc_type,sysParam.trid_type,sysParam.fc_mem,sysParam.display_size);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetInterfaceConfig_Idx4 (int iDefArgs)
{
	LX_DE_IF_CONFIG_T param;
	LX_DE_SYS_STATUS_T sysParam;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_IF_CONFIG_T ));
	memset( &sysParam, 0, sizeof( LX_DE_SYS_STATUS_T ));

	sysParam.status_type = LX_DE_SYS_STATUS_ALL;
	//arg = (LX_DE_SYS_STATUS_T __user*)&sysParam;
	arg = (unsigned long)&sysParam;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetSystemStatus);


	if (0 == iDefArgs){

		param.config_type = LX_DE_CONFIG_TYPE_ALL;
		param.display_type = sysParam.display_type;
		param.display_mirror = sysParam.display_mirror;
		param.frc_type = sysParam.frc_type;
		param.trid_type = sysParam.trid_type;
	} else {
		param.config_type = ((LX_DE_IF_CONFIG_T *)g_args)->config_type;
		param.display_type = ((LX_DE_IF_CONFIG_T *)g_args)->display_type;
		param.display_mirror = ((LX_DE_IF_CONFIG_T *)g_args)->display_mirror;
		param.frc_type = ((LX_DE_IF_CONFIG_T *)g_args)->frc_type;
		param.trid_type = ((LX_DE_IF_CONFIG_T *)g_args)->trid_type;
	}

	//arg = (LX_DE_IF_CONFIG_T __user*)&param;
	arg = (unsigned long)&param;
	CALL_IO(DE_IO_SetInterfaceConfig);
	printk("Setting done : display_type = 0x%x, display_mirror = 0x%x, frc_type = 0x%x,trid_type = 0x%x\n",\
		param.display_type,param.display_mirror,param.frc_type,param.trid_type);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetDisplayFormat_Idx5 (int iDefArgs)
{
	LX_DE_DIS_FMT_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.dev_type = LX_PANEL_DEV_LCD;
		param.panel_type = LX_PANEL_TYPE_3840;
		param.fr_rate = 60;
		param.h_total = 4096;
		param.v_total = 2048;

		} else {
		param.dev_type = ((LX_DE_DIS_FMT_T *)g_args)->dev_type;
		param.panel_type = ((LX_DE_DIS_FMT_T *)g_args)->panel_type;
		param.fr_rate = ((LX_DE_DIS_FMT_T *)g_args)->fr_rate;
		param.h_total = ((LX_DE_DIS_FMT_T *)g_args)->h_total;
		param.v_total = ((LX_DE_DIS_FMT_T *)g_args)->v_total;
		param.h_active = ((LX_DE_DIS_FMT_T *)g_args)->h_active;
		param.v_active = ((LX_DE_DIS_FMT_T *)g_args)->v_active;

	}

	//arg = (LX_DE_DIS_FMT_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetDisFmt);
	printk("Setting Done: panel_type = %d, fr_rate = %d,h_total = %d,   v_total = %d h_active = %d v_active = %d dev_type = %d\n",\
		param.panel_type,param.fr_rate,param.h_total,param.v_total,param.h_active, param.v_active,param.dev_type);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetFrameRate_Idx6 (int iDefArgs)
{
	LX_DE_FR_RATE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.isForceFreeRun = 0;
		param.fr_rate = 60;
	} else {
		param.isForceFreeRun = ((LX_DE_FR_RATE_T *)g_args)->isForceFreeRun;
		param.fr_rate = ((LX_DE_FR_RATE_T *)g_args)->fr_rate;
	}

	//arg = (LX_DE_FR_RATE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetFrRate);
	printk("Setting Done: isForceFreeRun = %d, fr_rate = %d\n",\
	param.isForceFreeRun,param.fr_rate);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_GetFrameRate_Idx7 (int iDefArgs)
{
	LX_DE_FR_RATE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.isForceFreeRun = 0;
		param.fr_rate = 60;
		} else {
		param.isForceFreeRun = ((LX_DE_FR_RATE_T *)g_args)->isForceFreeRun;
		param.fr_rate = ((LX_DE_FR_RATE_T *)g_args)->fr_rate;
	}

	//arg = (LX_DE_FR_RATE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetOutFrRate);
	printk("fr_rate =%d Hz. FreeRun = %d.\n", param.fr_rate, param.isForceFreeRun);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetDisplayOut_Idx8 (int iDefArgs)
{
	BOOLEAN param = 0;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param = 1;

		} else {
		param = *((BOOLEAN *)g_args);
	}

	//arg = (BOOLEAN __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetDisOut);
	printk("Setting Done: Display Out %d\n",param);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetWinPortSrc_Idx9 (int iDefArgs)
{
	LX_DE_INPUT_SOURCE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.srcId = LX_DE_WIN_MAIN;
		param.srcType = LX_DE_IN_SRC_MVI;
		param.srcPort = 0;
		param.srcAttr = 0;

		} else {
		param.srcId = ((LX_DE_INPUT_SOURCE_T *)g_args)->srcId;
		param.srcType = ((LX_DE_INPUT_SOURCE_T *)g_args)->srcType;
		param.srcPort = ((LX_DE_INPUT_SOURCE_T *)g_args)->srcPort;
		param.srcAttr = ((LX_DE_INPUT_SOURCE_T *)g_args)->srcAttr;
	}

	//arg = (LX_DE_INPUT_SOURCE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetWinPortSrc);
	printk("Setting Done: srcId = %d, srcType = %d,srcPort = %d, srcAttr = %d\n",\
		param.srcId,param.srcType,param.srcPort,param.srcAttr);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCviSrcType_IdxA (int iDefArgs)
{
	LX_DE_CVI_SRC_TYPE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.cvi_channel = LX_DE_CVI_CH_A;
		param.size_offset.hsize= 1920;
		param.size_offset.vsize= 1080;
		param.color = LX_DE_COLOR_601_CVD;
		param.aspect= LX_DE_AR_4_3;
		param.scan = LX_DE_INTERLACED;
		param.bit_res = LX_DE_CVI_10BIT;
		param.c_sample = LX_DE_CVI_444;
		param.de_mode = LX_DE_CVI_HDMI_SYNC_MODE;
		param.sampling= LX_DE_CVI_NORMAL_SAMPLING;
		param.sc_c_sample = LX_DE_SCALER_422;
		param.stability= LX_DE_CVI_SYNC_STD;
		param.field_polarity= LX_DE_CVI_FIELD_ORIGINAL;
		param.yc_delay = LX_DE_CVI_YC_DELAY_ATV;
		param.cvi_port= LX_DE_CVI_CVD;
		param.trid_full_format = LX_DE_CVI_NORMAL_FORMAT;
		param.cvi_input_src = LX_DE_CVI_SRC_ATV;
		param.cvd_color_std = LX_DE_COLOR_PAL_60_RF;

		} else {
		param.cvi_channel = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvi_channel;
		param.size_offset.hsize= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.hsize;
		param.size_offset.vsize= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.vsize;
		param.size_offset.hoffset= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.hoffset;
		param.size_offset.voffset= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->size_offset.voffset;
		param.color = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->color;
		param.aspect= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->aspect;
		param.scan = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->scan;
		param.bit_res = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->bit_res;
		param.c_sample = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->c_sample;
		param.de_mode = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->de_mode;
		param.sampling= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->sampling;
		param.sc_c_sample = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->sc_c_sample;
		param.stability= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->stability;
		param.field_polarity= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->field_polarity;
		param.yc_delay = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->yc_delay;
		param.cvi_port= ((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvi_port;
		param.trid_full_format = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->trid_full_format;
		param.cvi_input_src = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvi_input_src;
		param.cvd_color_std = ((LX_DE_CVI_SRC_TYPE_T *)g_args)->cvd_color_std;

	}

	//arg = (LX_DE_CVI_SRC_TYPE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCviSrcType);
	printk("Setting Done: cvi_channel = %d, size_offset.hsize = %d, size_offset.vsize = %d, size_offset.hoffset = %d,size_offset.voffset = %d, \n\
color = %d, aspect = %d scan = %d bit_res = %d c_sample = %d de_mode = %d sampling = %d sc_c_sample = %d  \n\
stability = %d field_polarity = %d yc_delay = %d cvi_port = %d trid_full_format = %d cvi_input_src = %d cvd_color_std = %d\n",	\
param.cvi_channel,param.size_offset.hsize,param.size_offset.vsize,\
param.size_offset.hoffset,param.size_offset.voffset,param.color,param.aspect,param.scan,param.bit_res,\
param.c_sample,param.de_mode,param.sampling,param.sc_c_sample,param.stability,param.field_polarity,\
param.yc_delay,param.cvi_port,param.trid_full_format,param.cvi_input_src,param.cvd_color_std);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCviFir_IdxB (int iDefArgs)
{
	LX_DE_CVI_FIR_T param = {0, };
	UINT16 coef_FIR_Y_Normal[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_CbCr_Normal[] = {128, 74, 0, -11, 0, 1};
	unsigned long arg;
	int ret = RET_OK;
	int i;

	if (0 == iDefArgs){
		param.cvi_channel = LX_DE_CVI_CH_A;
		param.isEnable = 1;

		for(i=0;i<8;i++){
			param.fir_coef[i] = coef_FIR_Y_Normal[i];
			if(i<6)
				{
					param.fir_coef_CbCr[i] = coef_FIR_CbCr_Normal[i];
				}
			}

		} else {
		param.cvi_channel = ((LX_DE_CVI_FIR_T *)g_args)->cvi_channel;
		param.isEnable = ((LX_DE_CVI_FIR_T *)g_args)->isEnable;
		for(i=0;i<8;i++){
			param.fir_coef[i] = ((LX_DE_CVI_FIR_T *)g_args)->fir_coef[i];
			if(i<6)
				{
					param.fir_coef_CbCr[i] = ((LX_DE_CVI_FIR_T *)g_args)->fir_coef_CbCr[i];
				}
			}
	}

	//arg = (LX_DE_CVI_FIR_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCviFir);
	printk("Setting Done: cvi_channel = %d, isEnable = %d\n",param.cvi_channel,param.isEnable);
	for(i=0;i<8;i++){
				printk("fir_coef[%d] = %d ",i,param.fir_coef[i]);
			}
		printk("\n");
		for(i=0;i<6;i++){
				printk("fir_coef_CbCr[%d] = %d ",i,param.fir_coef_CbCr[i]);
			}
		printk("\n");
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCviCsampleMode_IdxC (int iDefArgs)
{
	LX_DE_CSAMPLE_MODE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.cvi_channel = LX_DE_CVI_CH_A;
		param.is3tap= 1;

		} else {
		param.cvi_channel = ((LX_DE_CSAMPLE_MODE_T *)g_args)->cvi_channel;
		param.is3tap = ((LX_DE_CSAMPLE_MODE_T *)g_args)->is3tap;

	}

	//arg = (LX_DE_CSAMPLE_MODE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCviCsampleMode);
	printk("Setting Done: cvi_channel = %d, is3tap = %d\n",param.cvi_channel,param.is3tap);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_GetScalerInfo_IdxD (int iDefArgs)
{
	LX_DE_SCALER_INFO_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_SCALER_INFO_T ));

	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;

	} else {
		param.win_id = ((LX_DE_SCALER_INFO_T *)g_args)->win_id;
		param.width = ((LX_DE_SCALER_INFO_T *)g_args)->width;
		param.height = ((LX_DE_SCALER_INFO_T *)g_args)->height;
		param.stride = ((LX_DE_SCALER_INFO_T *)g_args)->stride;
		param.sampling = ((LX_DE_SCALER_INFO_T *)g_args)->sampling;
		param.p_y_frame = ((LX_DE_SCALER_INFO_T *)g_args)->p_y_frame;
		param.p_cbcr_frame = ((LX_DE_SCALER_INFO_T *)g_args)->p_cbcr_frame;

	}

	//arg = (LX_DE_SCALER_INFO_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetScalerInfo);
	printk("Width[%d] Height[%d] Stride[%d] \n", param.width, param.height, param.stride);
	printk("sampling[%d] 420(0),422(1),444(1)\n", param.sampling);
	printk("Y frame buffer = 0x%x 	CbCr frame buffer = 0x%x \n", *param.p_y_frame, *param.p_cbcr_frame);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetSrcMirror_IdxE (int iDefArgs)
{
	LX_DE_SRC_MIRROR_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.srcPort = 0;
		param.destPort= 0;
		param.enable = 0;

		} else {
		param.srcPort = ((LX_DE_SRC_MIRROR_T *)g_args)->srcPort;
		param.destPort = ((LX_DE_SRC_MIRROR_T *)g_args)->destPort;
		param.enable = ((LX_DE_SRC_MIRROR_T *)g_args)->enable;
	}

	//arg = (LX_DE_SRC_MIRROR_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetSrcMirror);
	printk("Setting Done: srcPort = %d, destPort = %d enable = %d\n",param.srcPort,param.destPort,param.enable);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_GetInputWin_IdxF (int iDefArgs)
{
	LX_DE_WIN_DIMENSION_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_WIN_DIMENSION_T ));

	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;

	} else {
		param.win_id = ((LX_DE_WIN_DIMENSION_T *)g_args)->win_id;
		param.rect.w= ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.w;
		param.rect.h = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.h;
		param.rect.x = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.x ;
		param.rect.y = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.y;

	}

	//arg = (LX_DE_WIN_DIMENSION_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetInputWin);
	printk("input win(%d)whxy(%d,%d,%d,%d) \n", param.win_id, param.rect.w, param.rect.h, param.rect.x, param.rect.y);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetInputWin_Idx10 (int iDefArgs)
{
	LX_DE_WIN_DIMENSION_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_WIN_DIMENSION_T ));

	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;
		param.rect.w= 1920;
		param.rect.h = 1080;
		param.rect.x = 0 ;
		param.rect.y = 0;

	} else {
		param.win_id = ((LX_DE_WIN_DIMENSION_T *)g_args)->win_id;
		param.rect.w= ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.w;
		param.rect.h = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.h;
		param.rect.x = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.x ;
		param.rect.y = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.y;

	}

	//arg = (LX_DE_WIN_DIMENSION_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetInputWin);
	printk("Setting Done: win_id = %d rect.w = %d rect.h = %d rect.x = %d rect.y = %d\n",\
		param.win_id,param.rect.w,param.rect.h,param.rect.x,param.rect.y);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_GetOutWin_Idx11 (int iDefArgs)
{
	LX_DE_WIN_DIMENSION_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_WIN_DIMENSION_T ));

	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;

	} else {
		param.win_id = ((LX_DE_WIN_DIMENSION_T *)g_args)->win_id;
		param.rect.w= ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.w;
		param.rect.h = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.h;
		param.rect.x = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.x ;
		param.rect.y = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.y;

	}

	//arg = (LX_DE_WIN_DIMENSION_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetOutWin);
	printk("output win(%d)whxy(%d,%d,%d,%d) \n", param.win_id, param.rect.w, param.rect.h, param.rect.x, param.rect.y);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetOutWin_Idx12 (int iDefArgs)
{
	LX_DE_WIN_DIMENSION_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_WIN_DIMENSION_T ));

	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;
		param.rect.w= 3840;
		param.rect.h = 2160;
		param.rect.x = 0 ;
		param.rect.y = 0;

	} else {
		param.win_id = ((LX_DE_WIN_DIMENSION_T *)g_args)->win_id;
		param.rect.w= ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.w;
		param.rect.h = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.h;
		param.rect.x = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.x ;
		param.rect.y = ((LX_DE_WIN_DIMENSION_T *)g_args)->rect.y;

	}

	//arg = (LX_DE_WIN_DIMENSION_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetOutWin);
	printk("Setting Done: win_id = %d rect.w = %d rect.h = %d rect.x = %d rect.y = %d\n",\
		param.win_id,param.rect.w,param.rect.h,param.rect.x,param.rect.y);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetWinBlank_Idx13 (int iDefArgs)
{
	LX_DE_SET_WIN_BLANK_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_SET_WIN_BLANK_T ));

	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;
		param.bEnable= 0;
		param.win_color.r = 0;
		param.win_color.g = 0 ;
		param.win_color.b = 0;
		param.isRGB = 0;

	} else {
		param.win_id = ((LX_DE_SET_WIN_BLANK_T *)g_args)->win_id;
		param.bEnable= ((LX_DE_SET_WIN_BLANK_T *)g_args)->bEnable;
		param.win_color.r = ((LX_DE_SET_WIN_BLANK_T *)g_args)->win_color.r;
		param.win_color.g = ((LX_DE_SET_WIN_BLANK_T *)g_args)->win_color.g ;
		param.win_color.b = ((LX_DE_SET_WIN_BLANK_T *)g_args)->win_color.b;
		param.isRGB= ((LX_DE_SET_WIN_BLANK_T *)g_args)->isRGB;
	}

	//arg = (LX_DE_SET_WIN_BLANK_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetWinBlank);
	printk("Setting Done: win_id = %d bEnable = %d win_color.r = %d win_color.g = %d win_color.b = %d isRGB = %d\n",\
		param.win_id,param.bEnable,param.win_color.r,param.win_color.g,param.win_color.b,param.isRGB);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetBgColor_Idx14 (int iDefArgs)
{
	LX_DE_COLOR_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_COLOR_T ));

	if (0 == iDefArgs){
		param.r = 0;
		param.g = 0 ;
		param.b = 0;

	} else {
		param.r = ((LX_DE_COLOR_T *)g_args)->r;
		param.g = ((LX_DE_COLOR_T *)g_args)->g ;
		param.b = ((LX_DE_COLOR_T *)g_args)->b;
	}

	//arg = (LX_DE_COLOR_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetBgColor);
	printk("Setting Done:  r = %d g = %d b = %d\n",\
		param.r,param.g,param.b);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetInnerPattern_Idx15 (int iDefArgs)
{
	LX_DE_INNER_PATTERN_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_INNER_PATTERN_T ));

	if (0 == iDefArgs){
		param.enable = 0;
		param.type = 0 ;
		param.level = 0;

	} else {
		param.enable = ((LX_DE_INNER_PATTERN_T *)g_args)->enable;
		param.type = ((LX_DE_INNER_PATTERN_T *)g_args)->type ;
		param.level = ((LX_DE_INNER_PATTERN_T *)g_args)->level;
	}

	//arg = (LX_DE_INNER_PATTERN_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetInnerPattern);
	printk("Setting Done:  enable = %d type = %d level = %d\n",	param.enable,param.type,param.level);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetActFmtDetect_Idx16 (int iDefArgs)
{
	LX_DE_ACT_FORMAT_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_ACT_FORMAT_T ));

	if (0 == iDefArgs){
		param.enable = 0;
		param.win_id = 0 ;

	} else {
		param.enable = ((LX_DE_ACT_FORMAT_T *)g_args)->enable;
		param.win_id = ((LX_DE_ACT_FORMAT_T *)g_args)->win_id ;

	}

	//arg = (LX_DE_ACT_FORMAT_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetActFmtDetect);
	printk("Setting Done:  enable = %d win_id = %d \n",	param.enable,param.win_id);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetZList_Idx17 (int iDefArgs)
{
	LX_DE_ZLIST_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_ZLIST_T ));

	if (0 == iDefArgs){
		param.enable = 0;

	} else {
		param.enable = ((LX_DE_ZLIST_T *)g_args)->enable;
		param.z_list[0] = ((LX_DE_ZLIST_T *)g_args)->z_list[0] ;
		param.z_list[1] = ((LX_DE_ZLIST_T *)g_args)->z_list[1] ;
		param.alpha[0] = ((LX_DE_ZLIST_T *)g_args)->alpha[0] ;
		param.alpha[1] = ((LX_DE_ZLIST_T *)g_args)->alpha[1] ;
	}

	//arg = (LX_DE_ZLIST_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetZList);

	printk(" Setting Done: enable = %d z_list[0] = %d z_list[1] = %d alpha[0] = %d alpha[1] = %d\n",\
		param.enable,param.z_list[0],param.z_list[1],param.alpha[0],param.alpha[1]);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetMultiVision_Idx18 (int iDefArgs)
{
	LX_DE_RECT_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_RECT_T ));

	if (0 == iDefArgs){
		param.w = 3840;
		param.h = 2160;

	} else {
		param.w = ((LX_DE_RECT_T *)g_args)->w;
		param.h = ((LX_DE_RECT_T *)g_args)->h ;
		param.x = ((LX_DE_RECT_T *)g_args)->x ;
		param.y = ((LX_DE_RECT_T *)g_args)->y ;

	}

	//arg = (LX_DE_RECT_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetMultiVision);

	printk(" Setting Done: w = %d h = %d x = %d y = %d \n",	param.w,param.h,param.x,param.y);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_MultiWinEnable_Idx19 (int iDefArgs)
{
	BOOLEAN param = 0;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param = 0;

		} else {
		param = *((BOOLEAN *)g_args);
	}

	//arg = (BOOLEAN __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_MultiWinEnable);
	printk("Setting Done: Multi Win Enable %d\n",param);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_GetSourceStatus_Idx1A (int iDefArgs)
{
	LX_DE_SRC_STATUS_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_SRC_STATUS_T ));

	if (0 == iDefArgs){
		param.status_type = LX_DE_SRC_STATUS_ALL;

	} else {
		param.status_type = ((LX_DE_SRC_STATUS_T *)g_args)->status_type;

	}

	//arg = (LX_DE_SRC_STATUS_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetSourceStatus);
	printk("status_type = %d  inSrc[0] = %d inSrc[1] = %d inSrcPort[0] = %d inSrcPort[1] = %d operType = %d\n\
		subOperType = %d operCtrlFlag = %d subOperCtrlFlag = %d\n",\
	param.status_type, param.inSrc[0], param.inSrc[1], param.inSrcPort[0], param.inSrcPort[1],param.operType,\
	param.subOperType,param.operCtrlFlag,param.subOperCtrlFlag);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_Set3DInOutCtrl_Idx1B (int iDefArgs)
{
	LX_DE_3D_INOUT_CTRL_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_3D_INOUT_CTRL_T ));

	if (0 == iDefArgs){
		param.run_mode = 0;
		param.in_img_fmt = 0 ;
		param.in_lr_order = 0;
		param.out_img_fmt = 0 ;
		param.out_lr_order = 0;

	} else {
		param.run_mode = ((LX_DE_3D_INOUT_CTRL_T *)g_args)->run_mode;
		param.in_img_fmt = ((LX_DE_3D_INOUT_CTRL_T *)g_args)->in_img_fmt ;
		param.in_lr_order = ((LX_DE_3D_INOUT_CTRL_T *)g_args)->in_lr_order;
		param.out_img_fmt = ((LX_DE_3D_INOUT_CTRL_T *)g_args)->out_img_fmt ;
		param.out_lr_order = ((LX_DE_3D_INOUT_CTRL_T *)g_args)->out_lr_order;
	}

	//arg = (LX_DE_3D_INOUT_CTRL_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_Set3DInOutCtrl);
	printk("Setting Done:  run_mode = %d in_img_fmt = %d in_lr_order = %d out_img_fmt = %d out_lr_order = %d\n",	param.run_mode,param.in_img_fmt,param.in_lr_order,\
		param.out_img_fmt,param.out_lr_order);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetLowDelay_Idx1C (int iDefArgs)
{
	UINT32 param = 0;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param = 0;

		} else {
		param = *((UINT32 *)g_args);
	}

	//arg = (UINT32 __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetLowDelay);
	printk("Setting Done: Low Delay Mode %d\n",param);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_GetLowDelay_Idx1D (int iDefArgs)
{
	LX_DE_LOW_DELAY_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_LOW_DELAY_T ));

	if (0 == iDefArgs){
		param.wId_enable = 0;

	} else {
		param.wId_enable = ((LX_DE_LOW_DELAY_T *)g_args)->wId_enable;
		param.lock = ((LX_DE_LOW_DELAY_T *)g_args)->lock;
		param.time = ((LX_DE_LOW_DELAY_T *)g_args)->time;
		param.frame = ((LX_DE_LOW_DELAY_T *)g_args)->frame;
		param.locked_time = ((LX_DE_LOW_DELAY_T *)g_args)->locked_time;

	}

	//arg = (LX_DE_LOW_DELAY_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetLowDelay);
	printk("wid[%d] enable[%d] lock[%d] time[%d ms(00.00)] frame[%d(0.00)] locked_time[%d ms(00.00)] \n", \
		param.wId_enable, param.wId_enable, param.lock, param.time, param.frame, param.locked_time);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetDvrFmtCtrl_Idx1E (int iDefArgs)
{
	LX_DE_DVR_DISFMT_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_DVR_DISFMT_T ));

	if (0 == iDefArgs){
		param.bOnOff = 0;
		param.scan = 0 ;
		param.h_size = 0;
		param.v_size = 0 ;
		param.fr_rate = 0;
		param.baseAddr = 0;

	} else {
		param.bOnOff = ((LX_DE_DVR_DISFMT_T *)g_args)->bOnOff;
		param.scan = ((LX_DE_DVR_DISFMT_T *)g_args)->scan ;
		param.h_size = ((LX_DE_DVR_DISFMT_T *)g_args)->h_size;
		param.v_size = ((LX_DE_DVR_DISFMT_T *)g_args)->v_size ;
		param.fr_rate = ((LX_DE_DVR_DISFMT_T *)g_args)->fr_rate;
		param.baseAddr = ((LX_DE_DVR_DISFMT_T *)g_args)->baseAddr;
	}

	//arg = (LX_DE_DVR_DISFMT_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetDvrFmtCtrl);
	printk("Setting Done:  bOnOff = %d scan = %d h_size = %d v_size = %d fr_rate = %d baseAddr = 0x%x\n",	param.bOnOff,param.scan,param.h_size,\
		param.v_size,param.fr_rate,param.baseAddr);

	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetUDMode_Idx1F (int iDefArgs)
{
	BOOLEAN param = 0;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param = 0;
	} else {
		param = *((BOOLEAN *)g_args);
	}
	//arg = (BOOLEAN __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetUDMode);
	printk("Setting Done: Ud Mode %d\n",param);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetVTM_Idx20 (int iDefArgs)
{
	LX_DE_VTM_FRAME_INFO_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;
	int i;

	if (0 == iDefArgs){
		for(i=0;i<3;i++){
			param.y_frame[i] = 0xffffffff;
			param.c_frame[i] = 0xffffffff;
		}
	} else {
			memcpy(&param,((LX_DE_VTM_FRAME_INFO_T *)g_args) ,sizeof(LX_DE_VTM_FRAME_INFO_T));
	}
	//arg = (LX_DE_VTM_FRAME_INFO_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetVTM);
	printk("Setting Done: win_id = %d, address = 0x%08x ",param.win_id,param.address);
	printk("enable = %d, rate = %d\n",param.enable,param.rate);
	printk("frz = %d, stride = %d, sampling = %d\n ",param.frz,param.stride,param.sampling);
	for(i=0;i<3;i++){
		printk("y_frame[%d] = 0x%08x \t c_frame[%d] = 0x%08x\n",i,param.y_frame[i],i,param.c_frame[i]);
		}
	printk("r_idx = %d, mute = 0x%08x\n",param.r_idx,param.mute);
	printk("srcSize.w = %d, srcSize.h = %d ",param.srcSize.w,param.srcSize.h);
	printk("srcSize.x = %d, srcSize.y = %d\n",param.srcSize.x,param.srcSize.y);
	printk("winSize.w = %d, winSize.h = %d ",param.winSize.w,param.winSize.h);
	printk("winSize.x = %d, winSize.y = %d\n",param.winSize.x,param.winSize.y);
	printk("mirror = %d, scan = %d, mem_fd = %d\n ",param.mirror,param.scan,param.mem_fd);
	#ifdef _USE_VT_EXTENTION_
	printk("ext_info.location = %d\n",param.ext_info.location);
	printk("ext_info.crop_size.w = %d, ext_info.crop_size.h = %d ",param.ext_info.crop_size.w,param.ext_info.crop_size.h);
	printk("ext_info.crop_size.x = %d, ext_info.crop_size.y = %d\n",param.ext_info.crop_size.x,param.ext_info.crop_size.y);
	printk("ext_info.w_out_size.w = %d, ext_info.w_out_size.h = %d ",param.ext_info.w_out_size.w,param.ext_info.w_out_size.h);
	printk("ext_info.w_out_size.x = %d, ext_info.w_out_size.y = %d\n",param.ext_info.w_out_size.x,param.ext_info.w_out_size.y);
	printk("ext_info.rate = %d, ext_info.frz = %d\n\n",param.ext_info.rate,param.ext_info.frz);
	#endif
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_GetVTM_Idx21 (int iDefArgs)
{
	LX_DE_VTM_FRAME_INFO_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_VTM_FRAME_INFO_T ));
	if (0 == iDefArgs){
		param.win_id = LX_DE_WIN_MAIN;
	} else {
		memcpy(&param,((LX_DE_VTM_FRAME_INFO_T *)g_args) ,sizeof(LX_DE_VTM_FRAME_INFO_T));
	}
	//arg = (LX_DE_VTM_FRAME_INFO_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetVTM);
	printk("IOCTL Enable = %d, Freeze = %d FrameRate = %d \n\n", param.enable, param.frz, param.rate);
	printk("Stride (%d) Sampling(%d) \n", param.stride, param.sampling);
	printk("frame index size  = %d , freeze = %d rate = %d \n", param.r_idx, param.frz, param.rate);
	printk("frame_0  y_frame =0x%x, c_frame =0x%x \n", param.y_frame[0], param.c_frame[0]);
	printk("frame_1  y_frame =0x%x, c_frame =0x%x \n", param.y_frame[1], param.c_frame[1]);
	printk("frame_2  y_frame =0x%x, c_frame =0x%x \n", param.y_frame[2], param.c_frame[2]);
	printk("source size (x,y,w,h) = (%d, %d, %d, %d ) mute status = %d \n", param.srcSize.x, param.srcSize.y, param.srcSize.w, param.srcSize.h, param.mute);
	printk("window size (x,y,w,h) = (%d, %d, %d, %d ) mirror status = %d \n", param.winSize.x, param.winSize.y, param.winSize.w, param.winSize.h, param.mirror);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetWinFreeze_Idx22 (int iDefArgs)
{
	LX_DE_WIN_FREEZE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.win_id = 0;
		param.bEnable= 0;
		param.location = 0;
	} else {
		memcpy(&param,((LX_DE_WIN_FREEZE_T *)g_args) ,sizeof(LX_DE_WIN_FREEZE_T));
	}
	//arg = (LX_DE_WIN_FREEZE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetWinFreeze);
	printk("Setting Done: win_id = %d, bEnable = %d location = %d\n",param.win_id,param.bEnable,param.location);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetHDMIPort_Idx23 (int iDefArgs)
{
	LX_DE_HDMIPORT_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.win_id = 0;
		param.port_num = 0;
	} else {
		param.win_id = ((LX_DE_HDMIPORT_T *)g_args)->win_id;
		param.port_num = ((LX_DE_HDMIPORT_T *)g_args)->port_num;
	}
	//arg = (LX_DE_HDMIPORT_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetHDMIPort);
	printk("Setting Done: win_id = %d, port_num = %d\n",param.win_id,param.port_num);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_GetCapacity_Idx24 (int iDefArgs)
{
	LX_DE_CAPACITY_T param = { 0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.chip_id = 0 ;
		param.max_win = 2;
		param.max_layer = 2;
	} else {
		memcpy(&param,((LX_DE_CAPACITY_T *)g_args) ,sizeof(LX_DE_CAPACITY_T));
	}
	//arg = (LX_DE_CAPACITY_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetCapacity);
	printk("chip_id %d max_win %d max_layer %d default_3d_out_fmt %d\n", param.chip_id, param.max_win, param.max_layer,param.default_3d_out_fmt);
	printk("max_in_size.w %d max_in_size.h %d max_in_size.x %d max_in_size.y %d\n", param.max_in_size.w, param.max_in_size.h, param.max_in_size.x,param.max_in_size.y);
	printk("max_out_size.w %d max_out_size.h %d max_out_size.x %d max_out_size.y %d\n", param.max_out_size.w, param.max_out_size.h, param.max_out_size.x,param.max_out_size.y);
	printk("max_in_fr_rate %d max_out_fr_rate %d mvir_start_num %d\n", param.max_in_fr_rate, param.max_out_fr_rate, param.mvir_start_num);
	printk("vtm_capa.maxResolution.w %d vtm_capa.maxResolution.h %d vtm_capa.maxResolution.x %d vtm_capa.maxResolution.y %d\n",\
		param.vtm_capa.maxResolution.w, param.vtm_capa.maxResolution.h, param.vtm_capa.maxResolution.x,param.vtm_capa.maxResolution.y);
	printk("vtm_capa.bLeftTopAlign %d vtm_capa.bSupportInputVideoDeInterlacing %d vtm_capa.bSupportDisplayVideoDeInterlacing %d\n",\
		param.vtm_capa.bLeftTopAlign, param.vtm_capa.bSupportInputVideoDeInterlacing, param.vtm_capa.bSupportDisplayVideoDeInterlacing);
	printk("vtm_capa.bSupportScaleUp %d vtm_capa.scaleUpLimitWidth %d vtm_capa.scaleUpLimitHeight %d vtm_capa.bSupportScaleDown %d \n",\
		param.vtm_capa.bSupportScaleUp, param.vtm_capa.scaleUpLimitWidth, param.vtm_capa.scaleUpLimitHeight, param.vtm_capa.bSupportScaleDown);
	printk("vtm_capa.scaleDownLimitWidth %d vtm_capa.scaleDownLimitHeight %d vtm_capa.locationLimit %d\n",\
		param.vtm_capa.scaleDownLimitWidth, param.vtm_capa.scaleDownLimitHeight, param.vtm_capa.locationLimit);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCviTpg_Idx25 (int iDefArgs)
{
	LX_DE_CVI_TPG_T param;
	unsigned long arg;
	int ret = RET_OK;

	memset( &param, 0, sizeof( LX_DE_CVI_TPG_T ));
	if (0 == iDefArgs){
		param.cvi_channel = 0;
		param.isPtnOn = 0 ;
		param.isFrzOn = 0;
		param.isGBR = 0 ;
		param.ptnColor = 0;
	} else {
		memcpy(&param,((LX_DE_CVI_TPG_T *)g_args) ,sizeof(LX_DE_CVI_TPG_T));
	}
	//arg = (LX_DE_CVI_TPG_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCviTpg);
	printk("Setting Done:  cvi_channel = %d isPtnOn = %d isFrzOn = %d isGBR = %d ptnColor = %d \n",	param.cvi_channel,param.isPtnOn,param.isFrzOn,\
		param.isGBR,param.ptnColor);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetSubWindow_Idx26 (int iDefArgs)
{
	LX_DE_SET_SUB_WIN_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.win_id = 0;
	} else {
		param.win_id = ((LX_DE_SET_SUB_WIN_T *)g_args)->win_id;
	}
	//arg = (LX_DE_SET_SUB_WIN_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetSubWindow);
	printk("Setting Done: win_id = %d\n",param.win_id);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCve_Idx27 (int iDefArgs)
{
	LX_DE_CVE_PARAM_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.fb = 0;
	} else {
		param.fb = ((LX_DE_CVE_PARAM_T *)g_args)->fb;
		param.std = ((LX_DE_CVE_PARAM_T *)g_args)->std;
	}
	//arg = (LX_DE_CVE_PARAM_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCve);
	printk("Setting Done: fb = %d std = %d\n",param.fb,param.std);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}


int DE_DBG_SetCviFreeze_Idx28 (int iDefArgs)
{
	LX_DE_CVI_CAPTURE_FREEZE_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.bCaptureOnOff = 0;
	} else {
		param.bCaptureOnOff = ((LX_DE_CVI_CAPTURE_FREEZE_T *)g_args)->bCaptureOnOff;
		param.bCviFreezeOnOff = ((LX_DE_CVI_CAPTURE_FREEZE_T *)g_args)->bCviFreezeOnOff;
	}
	//arg = (LX_DE_CVI_CAPTURE_FREEZE_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCviFreeze);
	printk("Setting Done: bCaptureOnOff = %d bCviFreezeOnOff = %d\n",param.bCaptureOnOff,param.bCviFreezeOnOff);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCviVideoFrameBuffer_Idx29 (int iDefArgs)
{
	LX_DE_CVI_RW_VIDEO_FRAME_T param = {0 };
	unsigned long arg;
	int ret = RET_OK;
	int width,height;

	param.color = NULL;
	if (0 == iDefArgs){
		param.region.win_id = LX_DE_WIN_MAIN;
		param.region.pixelGrabX= 0;
		param.region.pixelGrabY= 0;
		width = param.region.pixelGrabW = 1920;
		height = param.region.pixelGrabH = 1080;
		param.region.colorDepth = 1;
	} else {
		width = ((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.pixelGrabW;
		height = ((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args)->region.pixelGrabH;
		memcpy(&param,((LX_DE_CVI_RW_VIDEO_FRAME_T *)g_args) ,sizeof(LX_DE_CVI_RW_VIDEO_FRAME_T));
	}
//	param.color = (LX_DE_GRAB_COLOR_T *)OS_Malloc(width*height*sizeof(LX_DE_GRAB_COLOR_T));
	param.color = (LX_DE_GRAB_COLOR_T *)vmalloc(width*height*sizeof(LX_DE_GRAB_COLOR_T));
	//printk("vmalloc success\n");
	//arg = (LX_DE_CVI_RW_VIDEO_FRAME_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCviVideoFrameBuffer);
	printk("Setting Done: region.win_id = %d, region.pixelGrabX = %d, region.pixelGrabY = %d, region.pixelGrabW = %d,region.pixelGrabH = %d, \n\
region.realPixelGrabW = %d, region.realPixelGrabH = %d region.colorSpace = %d region.colorDepth = %d color = 0x%x bReadOnOff = %d \n\
frameAddr.phyFrameAddrY8 = %d frameAddr.phyFrameAddrC8 = %d frameAddr.phyFrameAddrY2 = %d frameAddr.phyFrameAddrC2 = %d frameAddr.stride = %d \n",\
	param.region.win_id,param.region.pixelGrabX,param.region.pixelGrabY,param.region.pixelGrabW,param.region.pixelGrabH,param.region.realPixelGrabW,\
	param.region.realPixelGrabH,param.region.colorSpace,param.region.colorDepth,param.color->pixelGrabY,param.bReadOnOff,param.frameAddr.phyFrameAddrY8,\
	param.frameAddr.phyFrameAddrC8,param.frameAddr.phyFrameAddrY2,param.frameAddr.phyFrameAddrC2,param.frameAddr.stride);
#if 0
	if(ret == RET_OK){
		if(param.color)	{
			printk("captured frame address is 0x%08x \n",param.color);
		}
	}
#endif
	if(param.color){
		//OS_Free(param.color);
		vfree(param.color);
	}
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetCaptureControl_Idx2A (int iDefArgs)
{
	LX_DE_CAPTURE_CTRL_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.inWin.w  = 1920;
		param.inWin.h = 1080;
		param.pixelFormat = LX_DE_PIXEL_FORMAT_YCBCR422_8;
		param.location = 1;
	} else {
		memcpy(&param,((LX_DE_CAPTURE_CTRL_T *)g_args) ,sizeof(LX_DE_CAPTURE_CTRL_T));
	}
	//arg = (LX_DE_CAPTURE_CTRL_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetCaptureControl);
	/*printk("Setting Done: win_id = %d, location = %d, inWin.w = %d, inWin.h = %d,inWin.x = %d, inWin.y = %d,\n\
wOutSize = %d hOutSize = %d pixelFormat = %d p_y_frame = 0x%x p_cbcr_frame = 0x%x stride = %d \n",\
	param.win_id,param.location,param.inWin.w,param.inWin.h,param.inWin.x,param.inWin.y,\
	param.wOutSize,param.hOutSize,param.pixelFormat,param.p_y_frame,param.p_cbcr_frame,param.stride);*/
	if(ret == RET_OK){
			printk("Stride[%d]  pixelFormat[%d]\n", param.stride, param.pixelFormat);
			printk("pixelFormat - RGB_10 [0], RGB_8 [1], YCBCR444_10 [2], YCBCR444_8 [3], YCBCR422_10 [4],  \n\
YCBCR422_8 [5], YCBCR420_10 [6], YCBCR420_8 [7] ");
			//printk("Y frame buffer = 0x%x 	CbCr frame buffer = 0x%x \n", (UINT32)param.p_y_frame, (UINT32)param.p_cbcr_frame);
			//printk("wOutSize = %d 	hOutSize = %d \n", (UINT32)param.wOutSize, (UINT32)param.hOutSize);
	}
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetVcs_Idx2B (int iDefArgs)
{
	LX_DE_VCS_IPC_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.inx= 0;
	} else {
		param.inx = ((LX_DE_VCS_IPC_T *)g_args)->inx;
		param.data = ((LX_DE_VCS_IPC_T *)g_args)->data;
	}
	//arg = (LX_DE_VCS_IPC_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetVcs);
	printk("Setting Done: inx = %d data = %d\n",param.inx,param.data);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetOperation_Idx2C (int iDefArgs)
{
	LX_DE_OPERATION_CTRL_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.win_id  = 0;
	} else {
		memcpy(&param,((LX_DE_OPERATION_CTRL_T *)g_args) ,sizeof(LX_DE_OPERATION_CTRL_T));
	}
	//arg = (LX_DE_OPERATION_CTRL_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetOperation);
	printk("Setting Done: win_id = %d, operation = %d, multiCtrl = %d, udCtrl = %d,ctrl3D.run_mode = %d, ctrl3D.in_img_fmt = %d,\n\
	ctrl3D.in_lr_order = %d ctrl3D.out_img_fmt = %d ctrl3D.out_lr_order = %d vencCtrl.bOnOff = 0x%x vencCtrl.scan = 0x%x vencCtrl.hSize = %d \n\
	vencCtrl.vSize = %d vencCtrl.frRate = %d \n",	param.win_id,param.operation,param.multiCtrl,\
	param.udCtrl,param.ctrl3D.run_mode,param.ctrl3D.in_img_fmt,	param.ctrl3D.in_lr_order,param.ctrl3D.out_img_fmt,param.ctrl3D.out_lr_order,\
	param.vencCtrl.bOnOff,param.vencCtrl.scan,param.vencCtrl.hSize,	param.vencCtrl.vSize,param.vencCtrl.frRate);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_RegRd_Idx2D (int iDefArgs)
{
	UINT32 param = 0;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param = 0;
	} else {
		param = *((UINT32 *)g_args);
	}
	//arg = (UINT32 __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_RegRd);
	printk("Register value = 0x%08x\n",param);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_RegWr_Idx2E (int iDefArgs)
{
	LX_DE_REG_WR_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.wr_addr= 0;
	} else {
		param.wr_addr = ((LX_DE_REG_WR_T *)g_args)->wr_addr;
		param.wr_data = ((LX_DE_REG_WR_T *)g_args)->wr_data;
	}
	//arg = (LX_DE_REG_WR_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_RegWr);
	printk("Setting Done: wr_addr = 0x%08x wr_data = 0x%08x\n",param.wr_addr,param.wr_data);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetUart4MCU_Idx2F (int iDefArgs)
{
	BOOLEAN param = 0;
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param = 0;
	} else {
		param = *((BOOLEAN *)g_args);
	}
	//arg = (BOOLEAN __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetUart4MCU);
	printk("MCU Mode = %d\n",param);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}

int DE_DBG_SetSubOperation_Idx30 (int iDefArgs)
{
	LX_DE_SUB_OPERATION_CTRL_T param = {0, };
	unsigned long arg;
	int ret = RET_OK;

	if (0 == iDefArgs){
		param.win_id  = 0;
	} else {
		memcpy(&param,((LX_DE_SUB_OPERATION_CTRL_T *)g_args) ,sizeof(LX_DE_SUB_OPERATION_CTRL_T));
	}
	//arg = (LX_DE_SUB_OPERATION_CTRL_T __user*)&param;
	arg = (unsigned long)&param;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_SetSubOperation);
	printk("Setting Done: win_id = %d, operation = %d, multiCtrl = %d, vencCtrl.bOnOff = 0x%x vencCtrl.scan = 0x%x \n\
	vencCtrl.hSize = %d vencCtrl.vSize = %d vencCtrl.frRate = %d \n",	param.win_id,param.operation,param.capture_enable,\
	param.vencCtrl.bOnOff,param.vencCtrl.scan,param.vencCtrl.hSize,	param.vencCtrl.vSize,param.vencCtrl.frRate);
	OS_Free(g_args);
	g_args = NULL;
	return ret;
}
#endif //#ifdef ENABLE_PROC_FUNCTION

