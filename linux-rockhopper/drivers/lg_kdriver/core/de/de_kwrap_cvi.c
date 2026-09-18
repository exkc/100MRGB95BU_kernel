/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file de_cvi_kadp.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		dongho7.park (dongho7.park@lge.com)
 *
 *  @version	1.0
 *  @date		2010-02-07
 *  @note		Additional information.
 *
 * 	some functions from de_kadp.c are moved here by
 * 	srinivasan.shanmugam@lge.com on 2015-04-16
 *
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define DISABLE_LGSI_CODE_RESTRUCTING /* this is to disable LGSI code refactoring changes */

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
//#include "unistd.h"
//#include "osa_kadp.h"
//#include "debug_kadp.h"
#include "de_kwrap.h"
#include "de_kapi.h"
#include "afe_kapi.h"
#include "afe_kwrap.h"
#include "hdmi_kapi.h"
#include "../../hdmi20/hdmi20_kwarp.h"
//#include "hdmi_kwrap.h"
#include "de_kwrap_defs.h"

#include "linux/syscalls.h"
#include "de_qkb.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/sched.h>

#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "de_drv.h"
#include "de_mem.h"

#include "de_model.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#include "mcu/de_int.h"
#include "de_io.h"
#include "de_hal.h"

#include "resource_mgr.h"
#include "history_mgr.h"
#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 20111115, sj.youm, hdmi scl_c_sample 444 or 422 결정을 위에서 내려오는 값으로 사용하기 위해 */
#define DE_SET_SCL_C_SAMPLING_BY_HDMI444MODE

#define SEE_TV
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
// workaround code for horizontal picture shaking on component 480i
// extern BOOLEAN _g_de_IsADCSrcChange;	//110817, wonsik.do

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
// extern int g_de_kap_logm_fd;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
// static int _de_kwrap_hex15bit_to_int(UINT32 hex_number);
// static int _de_kwrap_hex11bit_to_int(UINT32 hex_number);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
//extern LX_DE_CTX_T		g_de_ctx;


// CVI FIR coefficient for Y - 11 Tap,Cbcr - 11 Tap
// const UINT16 coef_FIR_Y_Normal[] = {256, 0, 0, 0, 0, 0, 0, 0};
// const UINT16 coef_FIR_Y_Double[] = {256, 0, 0, 0, 0, 0, 0, 0};
// const UINT16 coef_FIR_Y_Quad[] = {64, 56, 34, 12, 0, -6, 0, 0};	// 55 >> 56 --> sum 254 >> 256

// const UINT16 coef_FIR_H13_CVD_CbCr_Normal[] = {160, 49, -1, 0, 0, 0};//{128, 79, 0, -19, 0, 4};//	// CVI FIR Filter for 1 pixel & 422
// const UINT16 coef_FIR_CbCr_Normal[] = {128, 74, 0, -11, 0, 1};//{128, 79, 0, -19, 0, 4};//	// CVI FIR Filter for 1 pixel & 422
// const UINT16 coef_FIR_CbCr_Double[] = {160, 0, 49, 0, -1, 0};	// 55 >> 56 --> sum 254 >> 256
// const UINT16 coef_FIR_CbCr_Quad[] = {64, 56, 34, 12, 0, -6};


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
#if 0	//not used
/* LGSI code restructing for the function "de_kwrap_SetCviSrcType" */
static void de_kwrap_setcvisrcparams_scart_rgb_1( LX_DE_CVI_SRC_TYPE_T *param )
{
	LX_AFE_ADC_TIMING_INFO_T adc_time_info = { 0, };

#ifdef INCLUDE_KDRV_AFE
	if ( afe_kwrap_adc_get_timing_info(&adc_time_info) < 0 )
		DE_ERROR("[de_kwrap]afe_kwrap_adc_get_timing_info fail.\n");
#endif

	if (adc_time_info.u16_VFreq > 550)	{
		// 60Hz(480i)
		param->size_offset.hsize = 704;
		param->size_offset.vsize = 480;
		param->size_offset.hoffset	= 0x9a;
		param->size_offset.voffset	= 0xD;
	}
	else {
		// 50Hz(576i)
		param->size_offset.hsize = 704;
		param->size_offset.vsize = 576;
		param->size_offset.hoffset	= 165;
		param->size_offset.voffset	= 18;
	}

	param->scan = LX_DE_INTERLACED;
	param->yc_delay = LX_DE_CVI_YC_DELAY_BYPASS;
	param->trid_full_format = LX_DE_CVI_NORMAL_FORMAT;
	param->de_mode = LX_DE_CVI_NORMAL_SYNC_MODE;
	param->bit_res = LX_DE_CVI_10BIT;
	param->c_sample = LX_DE_CVI_444;
	param->sampling = LX_DE_CVI_NORMAL_SAMPLING; // VGA 도 우선 normal 만 지원함.
	param->cvi_port = LX_DE_CVI_ADC;

	{
		param->color = LX_DE_COLOR_RGBEX;
		param->aspect = LX_DE_AR_4_3;

		param->sampling = LX_DE_CVI_DOUBLE_SAMPLING;
		param->size_offset.hsize *= 2;
			//								param.size_offset.hoffset *= 2;

		param->sc_c_sample = LX_DE_SCALER_422;
		param->stability = LX_DE_CVI_SYNC_STD;
		param->field_polarity = LX_DE_CVI_FIELD_ORIGINAL;
	}

	param->cvi_input_src = LX_DE_CVI_SRC_YPBPR;

	param->cvd_color_std = 0;

	DE_PRINT("$$$ cvisrctype SCART RGB hsize[%d], vsize[%d], hoffset[%d], voffset[%d], scan[%d] $$$\n", param->size_offset.hsize, param->size_offset.vsize, param->size_offset.hoffset, param->size_offset.voffset, param->scan);
	DE_PRINT("[de_kwrap]SetCviSrcType for ADC.\n");
}

static void de_kwrap_setcvisrcparams_vga_ypbpr( LX_DE_CVI_SRC_TYPE_T *param, kwrap_de_input_src_t source )
{
	LX_AFE_ADC_TIMING_INFO_T adc_time_info = { 0, };

#ifdef INCLUDE_KDRV_AFE
	// workaround code for horizontal picture shaking on component 480i
	if (_g_de_IsADCSrcChange)
	{
		adc_time_info.u16_HActive = 720;
		adc_time_info.u16_VActive = 480;
		adc_time_info.u16_HStart = 0;
		adc_time_info.u16_VStart = 0;
		if (source == INPUT_SRC_VGA)
			adc_time_info.u8_ScanType = LX_DE_PROGRESSIVE;
		else
			adc_time_info.u8_ScanType = LX_DE_INTERLACED;
	}
	else if ( afe_kwrap_adc_get_timing_info(&adc_time_info) < 0 )
		DE_ERROR("[de_kwrap]afe_kwrap_adc_get_timing_info fail.\n");
#endif

	param->size_offset.hsize = adc_time_info.u16_HActive;
	param->size_offset.vsize = adc_time_info.u16_VActive;
	param->size_offset.hoffset = adc_time_info.u16_HStart;
	param->size_offset.voffset = adc_time_info.u16_VStart;
	param->scan = adc_time_info.u8_ScanType;
	param->yc_delay = LX_DE_CVI_YC_DELAY_BYPASS;
	param->trid_full_format = LX_DE_CVI_NORMAL_FORMAT;
	if ( param->size_offset.hsize > DE_MAX_INPUT_HSIZE  || param->size_offset.vsize > DE_MAX_INPUT_VSIZE )
	{
		param->size_offset.hsize = 720;
		param->size_offset.vsize = 480;
		param->size_offset.hoffset = 0;
		param->size_offset.voffset = 0;
		param->scan = LX_DE_INTERLACED;
	}
	param->de_mode = LX_DE_CVI_NORMAL_SYNC_MODE;
	param->bit_res = LX_DE_CVI_10BIT;
	param->c_sample = LX_DE_CVI_444;
	param->sampling = LX_DE_CVI_NORMAL_SAMPLING; // VGA 도 우선 normal 만 지원함.
	param->cvi_port = LX_DE_CVI_ADC;

	if (source == INPUT_SRC_VGA)
	{
		param->color = LX_DE_COLOR_RGBEX;
		param->aspect = LX_DE_AR_4_3;
		if (param->scan == LX_DE_INTERLACED)
		{
			param->sc_c_sample = LX_DE_SCALER_422;	// L8 HW constraint
		}
		else
		{
			param->sc_c_sample = LX_DE_SCALER_444;
		}
		param->stability = LX_DE_CVI_SYNC_STD;
		param->field_polarity = LX_DE_CVI_FIELD_ORIGINAL;
	}
	else // component inputs
	{
		if (param->size_offset.hsize >= DE_H1024_IS_HD ) //HD format criteria of L8 DE
		{
			param->color = LX_DE_COLOR_709;
			param->aspect = LX_DE_AR_16_9;
		}
		else // SD
		{
			param->color = LX_DE_COLOR_601;
			param->aspect = LX_DE_AR_4_3;

#ifdef COMP_4X_OVERSAMPLING
			if ( (param->size_offset.vsize == 480) || (param->size_offset.vsize == 576) || (param->size_offset.vsize == 483)  )
			{
				param->sampling = LX_DE_CVI_QUAD_SAMPLING;
				param->size_offset.hsize *= 4;
				param->size_offset.hoffset *= 4;
			}
#else
			if ( ((param->size_offset.vsize == 480) || (param->size_offset.vsize == 576)|| (param->size_offset.vsize == 483)) && param->scan == LX_DE_INTERLACED )
			{
				param->sampling = LX_DE_CVI_DOUBLE_SAMPLING;
				param->size_offset.hsize *= 2;
				param->size_offset.hoffset *= 2;
			}
#endif

		}
		param->sc_c_sample = LX_DE_SCALER_422;
		param->stability = LX_DE_CVI_SYNC_STD;
		param->field_polarity = LX_DE_CVI_FIELD_ORIGINAL;
	}

	if (source == INPUT_SRC_VGA)
		param->cvi_input_src = LX_DE_CVI_SRC_VGA;
	else
		param->cvi_input_src = LX_DE_CVI_SRC_YPBPR;

	param->cvd_color_std = 0;

	DE_PRINT("$$$ cvisrctype hsize[%d], vsize[%d], hoffset[%d], voffset[%d], scan[%d] $$$\n", param->size_offset.hsize, param->size_offset.vsize, param->size_offset.hoffset, param->size_offset.voffset, param->scan);
	DE_PRINT("[de_kwrap]SetCviSrcType for ADC.\n");
}

static void de_kwrap_setcvisrcparams_atv_cvbs_svideo( LX_DE_CVI_SRC_TYPE_T *param, kwrap_de_input_src_t source )
{
	LX_AFE_CVD_TIMING_INFO_T cvd_time_info = { 0, };

#ifdef INCLUDE_KDRV_AFE
	if ( afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &cvd_time_info) < 0 )
		DE_ERROR("[de_kwrap]afe_kwrap_cvd_get_timing_info fail.\n");
#endif

	param->size_offset.hoffset = cvd_time_info.u16_HStart;
	param->size_offset.voffset = cvd_time_info.u16_VStart;
	param->size_offset.hsize = cvd_time_info.u16_HSize;
	param->size_offset.vsize = cvd_time_info.u16_VSize;
	param->trid_full_format = LX_DE_CVI_NORMAL_FORMAT;

#if 0
	if (source == INPUT_SRC_ATV)
		param->yc_delay = LX_DE_CVI_YC_DELAY_ATV;
	else
		param->yc_delay = LX_DE_CVI_YC_DELAY_OTHERS;
#endif /* #if 0 */

	param->yc_delay = LX_DE_CVI_YC_DELAY_OTHERS;
	param->de_mode = LX_DE_CVI_HDMI_SYNC_MODE;
		/* [L8-A0 WR][L8-B0 WR]  CVD line jitter  --> work around: CVD DE mode로 동작*/

	//if ( param->de_mode == LX_DE_CVI_HDMI_SYNC_MODE )
	{
		param->size_offset.hoffset = 0;
		param->size_offset.voffset = 0;
	}

	param->bit_res = LX_DE_CVI_10BIT;
	param->c_sample = LX_DE_CVI_444;
	param->sampling = LX_DE_CVI_NORMAL_SAMPLING;

	param->scan = LX_DE_INTERLACED;
	param->color = LX_DE_COLOR_601_CVD;	// 7.5IRE vs 16(64)
	param->aspect = LX_DE_AR_4_3;
	param->sc_c_sample = LX_DE_SCALER_422;
	param->cvi_port = LX_DE_CVI_CVD;
	param->stability = LX_DE_CVI_SYNC_STD;
	param->field_polarity = LX_DE_CVI_FIELD_ORIGINAL;

	if (source == INPUT_SRC_ATV)
	{
		param->yc_delay = LX_DE_CVI_YC_DELAY_ATV;
		param->cvi_input_src = LX_DE_CVI_SRC_ATV;

		if (cvd_time_info.cvd_standard == LX_NTSC_M)
			param->cvd_color_std = LX_DE_COLOR_NTSC_M_RF;
		else if (cvd_time_info.cvd_standard == LX_NTSC_443)
			param->cvd_color_std = LX_DE_COLOR_NTSC_443_RF;
		else if (cvd_time_info.cvd_standard == LX_PAL_BG)
			param->cvd_color_std = LX_DE_COLOR_PAL_RF;
		else if (cvd_time_info.cvd_standard == LX_PAL_M)
			param->cvd_color_std = LX_DE_COLOR_PAL_M_RF;
		else if (cvd_time_info.cvd_standard == LX_PAL_CN)
			param->cvd_color_std = LX_DE_COLOR_PAL_NC_RF;
		else if (cvd_time_info.cvd_standard == LX_PAL_60)
			param->cvd_color_std = LX_DE_COLOR_PAL_60_RF;
		else if (cvd_time_info.cvd_standard == LX_SECAM)
			param->cvd_color_std = LX_DE_COLOR_SECAM_RF;
		else
			param->cvd_color_std = LX_DE_COLOR_UNKNOWN;

	}
	else if ((source == INPUT_SRC_CVBS_1) || (source == INPUT_SRC_CVBS_2) || (source == INPUT_SRC_CVBS_3))
	{
		param->cvi_input_src = LX_DE_CVI_SRC_CVBS;

		if (cvd_time_info.cvd_standard == LX_NTSC_M)
			param->cvd_color_std = LX_DE_COLOR_NTSC_M;
		else if (cvd_time_info.cvd_standard == LX_NTSC_443)
			param->cvd_color_std = LX_DE_COLOR_NTSC_443;
		else if (cvd_time_info.cvd_standard == LX_PAL_BG)
			param->cvd_color_std = LX_DE_COLOR_PAL;
		else if (cvd_time_info.cvd_standard == LX_PAL_M)
			param->cvd_color_std = LX_DE_COLOR_PAL_M;
		else if (cvd_time_info.cvd_standard == LX_PAL_CN)
			param->cvd_color_std = LX_DE_COLOR_PAL_NC;
		else if (cvd_time_info.cvd_standard == LX_PAL_60)
			param->cvd_color_std = LX_DE_COLOR_PAL_60;
		else if (cvd_time_info.cvd_standard == LX_SECAM)
			param->cvd_color_std = LX_DE_COLOR_SECAM;
		else
			param->cvd_color_std = LX_DE_COLOR_UNKNOWN;
	}
	else
	{
		param->cvi_input_src = LX_DE_CVI_SRC_SVIDEO;
		param->cvd_color_std = LX_DE_COLOR_DEFAULT;
	}

	DE_PRINT("[de_kwrap]SetCviSrcType for CVD.\n");
}

static void de_kwrap_setcvisrcparams_scart( LX_DE_CVI_SRC_TYPE_T *param, kwrap_de_input_src_t source )
{
	LX_AFE_SCART_ID_T scart_id;
	LX_AFE_CVD_TIMING_INFO_T cvd_time_info = { 0, };
	LX_AFE_SCART_AR_T scart_ar = LX_SCART_AR_INVALID;

	if ( source == INPUT_SRC_SCART_1)
	{
		scart_id = LX_SCART_ID_1;
	}
	else
	{
		scart_id = LX_SCART_ID_2;
	}

#ifdef INCLUDE_KDRV_AFE
	if ( afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &cvd_time_info) < 0 )
		DE_ERROR("[de_kwrap]afe_kwrap_cvd_get_timing_info fail.\n");
#endif

	param->size_offset.hoffset = cvd_time_info.u16_HStart;
	param->size_offset.voffset = cvd_time_info.u16_VStart;
	param->size_offset.hsize = cvd_time_info.u16_HSize;
	param->size_offset.vsize = cvd_time_info.u16_VSize;
	param->yc_delay = LX_DE_CVI_YC_DELAY_OTHERS;
	param->trid_full_format = LX_DE_CVI_NORMAL_FORMAT;

	param->de_mode = LX_DE_CVI_HDMI_SYNC_MODE;
	/* [L8-A0 WR][L8-B0 WR]  CVD line jitter  --> work around: CVD DE mode로 동작*/

	//if ( param->de_mode == LX_DE_CVI_HDMI_SYNC_MODE )
	{
		param->size_offset.hoffset = 0;
		param->size_offset.voffset = 0;
	}

	param->bit_res = LX_DE_CVI_10BIT;
	param->c_sample = LX_DE_CVI_444;
	param->sampling = LX_DE_CVI_NORMAL_SAMPLING;
	param->scan = LX_DE_INTERLACED;
	param->color = LX_DE_COLOR_601_CVD;	// 7.5IRE vs 16(64)
	param->sc_c_sample = LX_DE_SCALER_422;
	param->cvi_port = LX_DE_CVI_CVD;
	param->stability = LX_DE_CVI_SYNC_STD;
	param->field_polarity = LX_DE_CVI_FIELD_ORIGINAL;	// [L9-B0] CVD field reversed --> original

#ifdef INCLUDE_KDRV_AFE
	if ( afe_kwrap_get_scart_ar(scart_id, &scart_ar) < 0 )
		DE_ERROR("[de_kwrap]afe_kwrap_get_scart_ar fail.\n");
#endif

	if ( scart_ar == LX_SCART_AR_16_9)
	{
		param->aspect = LX_DE_AR_16_9;
	}
	else
	{
		param->aspect = LX_DE_AR_4_3;
	}

	param->cvi_input_src = LX_DE_CVI_SRC_SCART;

	if (cvd_time_info.cvd_standard == LX_NTSC_M)
		param->cvd_color_std = LX_DE_COLOR_NTSC_M;
	else if (cvd_time_info.cvd_standard == LX_NTSC_443)
		param->cvd_color_std = LX_DE_COLOR_NTSC_443;
	else if (cvd_time_info.cvd_standard == LX_PAL_BG)
		param->cvd_color_std = LX_DE_COLOR_PAL;
	else if (cvd_time_info.cvd_standard == LX_PAL_M)
		param->cvd_color_std = LX_DE_COLOR_PAL_M;
	else if (cvd_time_info.cvd_standard == LX_PAL_CN)
		param->cvd_color_std = LX_DE_COLOR_PAL_NC;
	else if (cvd_time_info.cvd_standard == LX_PAL_60)
		param->cvd_color_std = LX_DE_COLOR_PAL_60;
	else if (cvd_time_info.cvd_standard == LX_SECAM)
		param->cvd_color_std = LX_DE_COLOR_SECAM;
	else
		param->cvd_color_std = LX_DE_COLOR_UNKNOWN;

	DE_PRINT("[de_kwrap]SetCviSrcType for SCART.\n");
}

static void de_kwrap_setcvisrcparams_hdmi_timeinfo( LX_DE_CVI_SRC_TYPE_T *param )
{
	LX_HDMI_TIMING_INFO_T hdmi_time_info = { 0, };
	LX_HDMI_STATUS_T hdmiStatus = { 0, };
	UINT8 hdmi_sampling = 0;
	UINT8 hdmi_phys_port = de_kwrap_gethdmiport(param->cvi_channel);
#ifdef USE_VP_HDMI_API
	ret = vp_kwrap_hdmi_rx_gettiminginfo(hdmi_phys_port, &hdmi_time_info, CALL_FROM_KERNEL);
	if(ret != RET_OK) DE_ERROR("vp_kwrap_hdmi_rx_gettiminginfo fail");
	ret = vp_kwrap_hdmi_rx_gethdmistate(hdmi_phys_port, &hdmiStatus);
	if(ret != RET_OK) DE_ERROR("vp_kwrap_hdmi_rx_gethdmistate fail");
#else
#ifdef SEE_TV //hdmi building is issue
#else
	if(hdmi_kwrap_check20port(hdmi_phys_port)){
		if( hdmi20_kwrap_rx_gettiminginfo((UINT8)hdmi20_kwrap_get_connectedport(), &hdmi_time_info, 1) < 0)
			DE_ERROR("[de_kwrap] hdmi20_kwrap_rx_gettiminginfo fail\n");

		if ( hdmi20_kwrap_rx_gethdmistate((UINT8)hdmi20_kwrap_get_connectedport(), &hdmiStatus) < 0 )
			DE_ERROR("[de_kwrap]hdmi_kwrap_gethdmitiminginfo fail.\n");
	}
	else{
		hdmi_time_info.prt_num = hdmi_phys_port;
		if ( hdmi_kwrap_gethdmitiminginfo(&hdmi_time_info) < 0 )
			DE_ERROR("[de_kwrap]hdmi_kwrap_gethdmitiminginfo fail.\n");

		hdmiStatus.prt_num = hdmi_phys_port;
		if ( hdmi_kwrap_gethdmistate(&hdmiStatus) < 0 )
			DE_ERROR("[de_kwrap]hdmi_kwrap_gethdmistate fail.\n");
	}
#endif
#endif

	param->size_offset.hsize = hdmi_time_info.hActive;
	param->size_offset.vsize = hdmi_time_info.vActive;
	param->size_offset.hoffset = 0;	//hdmi_time_info.hStart;
	param->size_offset.voffset = 0;	//hdmi_time_info.vStart;
	param->de_mode = LX_DE_CVI_HDMI_SYNC_MODE;

	if (hdmi_time_info.extInfo == LX_HDMI_EXT_3D_FRAMEPACK)
		param->trid_full_format = LX_DE_CVI_3D_FRAMEPACK;
	else if (hdmi_time_info.extInfo == LX_HDMI_EXT_3D_FIELD_ALTERNATIVE)
		param->trid_full_format = LX_DE_CVI_3D_FIELD_ALTERNATIVE;
	else if (hdmi_time_info.extInfo == LX_HDMI_EXT_3D_LINE_ALTERNATIVE)
		param->trid_full_format = LX_DE_CVI_3D_ROW_INTERLEAVING;
	else if (hdmi_time_info.extInfo == LX_HDMI_EXT_3D_SBSFULL)
		param->trid_full_format = LX_DE_CVI_3D_SBSFULL;
	else
		param->trid_full_format = LX_DE_CVI_NORMAL_FORMAT;

	param->bit_res = LX_DE_CVI_10BIT;	// 10bit 으로 고정 DE HW 요청 2010. 04.05
	param->c_sample = LX_DE_CVI_444;	// fixed 8bit 3ch

	if ( de_kwrap_gethdmisamplemode(hdmi_time_info.hActive, hdmi_time_info.vActive, hdmi_time_info.scanType, &hdmi_sampling ) < 0 )
		DE_ERROR("[de_kwrap]de_kwrap_gethdmisamplemode fail.\n");

	if (hdmiStatus.pixelRepet == 1)
		hdmi_sampling = LX_DE_CVI_DOUBLE_SAMPLING;
	else if (hdmiStatus.pixelRepet == 2)
		hdmi_sampling = LX_DE_CVI_QUAD_SAMPLING;

	param->sampling = hdmi_sampling;
	param->scan = hdmi_time_info.scanType;
	param->yc_delay = LX_DE_CVI_YC_DELAY_BYPASS;
	param->cvi_port = LX_DE_CVI_EXT_A;
}

static void de_kwrap_setcvisrcparams_hdmi( LX_DE_CVI_SRC_TYPE_T *param )
{
	LX_HDMI_COLOR_STATUS_T hdmi_colormetry = LX_HDMI_CS_FULL_RGB;
	LX_HDMI_ASPECTRATIO_T hdmi_aspectratio = { 0, };
	LX_DE_HDMI444_MODE_T hdmi_444_mode = LX_DE_HDMI444_NONE;
	UINT8 hdmi_phys_port = de_kwrap_gethdmiport(param->cvi_channel);

	de_kwrap_setcvisrcparams_hdmi_timeinfo( param );

#ifdef USE_VP_HDMI_API
	ret = vp_kwrap_hdmi_rx_getcolordomain(hdmi_phys_port, &hdmi_colormetry);
	if(ret != RET_OK) DE_ERROR("vp_kwrap_hdmi_rx_getcolordomain fail");
	ret = vp_kwrap_hdmi_rx_getaspectratio(hdmi_phys_port, &hdmi_aspectratio);
	if(ret != RET_OK) DE_ERROR("vp_kwrap_hdmi_rx_getaspectratio fail");
#else
#ifdef SEE_TV //Enable once hdmi header file is updated
#else
	if(hdmi_kwrap_check20port(hdmi_phys_port)){
		if( hdmi20_kwrap_rx_getcolordomain((UINT8)hdmi20_kwrap_get_connectedport(), &hdmi_colormetry) < 0)
			DE_ERROR("[de_kwrap]hdmi20_kwrap_rx_getcolordomain fail.\n");

		if(hdmi20_kwrap_rx_getaspectratio((UINT8)hdmi20_kwrap_get_connectedport(), &hdmi_aspectratio) < 0)
			DE_ERROR("[de_kwrap]hdmi20_kwrap_rx_getaspectratio fail\n");

	}
	else{
		if ( hdmi_kwrap_gethdmicolordomain(hdmi_phys_port, &hdmi_colormetry) < 0 )
			DE_ERROR("[de_kwrap]hdmi_kwrap_gethdmicolordomain fail.\n");
		if ( hdmi_kwrap_gethdmiaspectratio(hdmi_phys_port, &hdmi_aspectratio) < 0 )
			DE_ERROR("[de_kwrap]hdmi_kwrap_gethdmiaspectratio fail.\n");
	}
#endif
#endif
	switch (hdmi_colormetry)
	{
		case LX_HDMI_CS_FULL_RGB:
		case LX_DVI_CS_FULL_RGB:
			param->color = LX_DE_COLOR_RGBEX;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;

		case LX_HDMI_CS_LIMITED_RGB:
			param->color = LX_DE_COLOR_RGB;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;

		case LX_HDMI_CS_YCBCR422_601:
			param->color = LX_DE_COLOR_601;
			param->sc_c_sample = LX_DE_SCALER_422;
			break;

		case LX_HDMI_CS_YCBCR444_601:
			param->color = LX_DE_COLOR_601;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;

		case LX_HDMI_CS_YCBCR422_709:
			param->color = LX_DE_COLOR_709;
			param->sc_c_sample = LX_DE_SCALER_422;
			break;

		case LX_HDMI_CS_YCBCR444_709:
			param->color = LX_DE_COLOR_709;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;

		case LX_HDMI_CS_XVYCC422_601:
			param->color = LX_DE_COLOR_XVYCC601;
			param->sc_c_sample = LX_DE_SCALER_422;
			break;

		case LX_HDMI_CS_XVYCC444_601:
			param->color = LX_DE_COLOR_XVYCC601;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;

		case LX_HDMI_CS_XVYCC422_709:
			param->color = LX_DE_COLOR_XVYCC709;
			param->sc_c_sample = LX_DE_SCALER_422;
			break;

		case LX_HDMI_CS_XVYCC444_709:
			param->color = LX_DE_COLOR_XVYCC709;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;

		default:
			param->color = LX_DE_COLOR_RGBEX;
			param->sc_c_sample = LX_DE_SCALER_444;
			break;
	}

	if (hdmi_aspectratio.eAspectRatio == LX_HDMI_AVI_PICTURE_ARC_16_9)
	{
		param->aspect = LX_DE_AR_16_9;
	}
	else
	{
		param->aspect = LX_DE_AR_4_3;
	}

#ifdef DE_SET_SCL_C_SAMPLING_BY_HDMI444MODE
	/* 1. sc_c_sample은 hdmi 444 mode에 의해 1차 결정됨. */
	de_kwrap_gethdmi444mode(&hdmi_444_mode);

	if ( (hdmi_444_mode == LX_DE_HDMI444_ON) && (param->scan == LX_DE_PROGRESSIVE) )
		param->sc_c_sample = LX_DE_SCALER_444;
	else
		param->sc_c_sample = LX_DE_SCALER_422;

	DE_PRINT("[%s,%d] sc_c_sample:[%d], by hdmi444md:[%d]\n",__F__,__L__,param->sc_c_sample,hdmi_444_mode);

#if 0
	/* 2. chip 제약사항 적용. */
	if (param->sc_c_sample == LX_DE_SCALER_444)
	{
		if (param->scan == LX_DE_INTERLACED)
		{
			param->sc_c_sample = LX_DE_SCALER_422;	// L8/L9 HW constraint
		}
	}
#endif /* #if 0 */
#else	//org
	if ((param->sc_c_sample == LX_DE_SCALER_444) && (param->scan == LX_DE_INTERLACED))
	{
		param->sc_c_sample = LX_DE_SCALER_422;	// L8/L9 HW constraint
	}

//Harish:Review comment
//Below if can be reduced by making else of above if statement
	/*20110420, sj.youm, hdmi non pc label for 480p,720p,1080p -> 422*/
	if (param->sc_c_sample == LX_DE_SCALER_444)
	{
		de_kwrap_gethdmi444mode(&hdmi_444_mode);

		if (hdmi_444_mode != LX_DE_HDMI444_ON)
		{
			param->sc_c_sample = LX_DE_SCALER_422;
			DE_PRINT("[%s,%d] tv or non pc  --> chg to 422\n",__FUNCTION__,__LINE__);
		}
		else
		{
			DE_PRINT("[%s,%d] pc or pc label --> 444\n",__FUNCTION__,__LINE__);
		}
	}
#endif	// DE_SET_SCL_C_SAMPLING_BY_HDMI444MODE

	/* ToDo: 720x288 이 1440x288 처럼 TV Res 에 포함 되어야 함. */
	/* 현재 GP3/Gp4 모두 default 에 해당되어 PC Res 로 판단됨 */

	param->stability = LX_DE_CVI_SYNC_STD;
	param->field_polarity = LX_DE_CVI_FIELD_ORIGINAL;

	param->cvi_input_src = LX_DE_CVI_SRC_HDMI;
	param->cvd_color_std = 0;

	DE_PRINT("[de_kwrap]SetCviSrcType for HDMI.\n");
}

#define IS_VGA_YPBPR( _x_ ) 		( ( _x_ == INPUT_SRC_VGA ) || \
									( _x_ == INPUT_SRC_YPBPR_1 ) || \
									( _x_ == INPUT_SRC_YPBPR_2 ) ) ? \
									1 : 0


#define IS_ATV_CVBS_SVIDEO( _x_ ) 	( ( _x_ == INPUT_SRC_ATV ) || \
									( _x_ == INPUT_SRC_CVBS_1 ) || \
									( _x_ == INPUT_SRC_CVBS_2 ) || \
									( _x_ == INPUT_SRC_CVBS_3 ) || \
									( _x_ == INPUT_SRC_SVIDEO_1 ) || \
									( _x_ == INPUT_SRC_SVIDEO_2 ) ) ? \
									1 : 0

#define IS_SCART_1_2( _x_ ) 		( ( _x_ == INPUT_SRC_SCART_1 ) || \
									( _x_ == INPUT_SRC_SCART_2 ) ) ? \
									1 : 0

#define IS_HDMI( _x_ ) 				( ( _x_ == INPUT_SRC_HDMI_A ) || \
									( _x_ == INPUT_SRC_HDMI_B ) || \
									( _x_ == INPUT_SRC_HDMI_C ) || \
									( _x_ == INPUT_SRC_HDMI_D) ) ? \
									1 : 0
/**
 *	set source configuration of captured video input
 *
 */
int de_kwrap_setcvisrctype(UINT8 wId, kwrap_de_input_src_t source)
{
	LX_DE_CVI_SRC_TYPE_T param;
	int ret = RET_ERROR;
	BOOLEAN bCviCsampleMode = FALSE;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	if (source >= INPUT_SRC_DTV)
		return ret;

	// assign main source to channel A
	if (wId < 1)	param.cvi_channel = LX_DE_CVI_CH_A;
	else			param.cvi_channel = LX_DE_CVI_CH_B;

	memset(&param, 0, sizeof(LX_DE_CVI_SRC_TYPE_T));

	if ( INPUT_SRC_SCART_RGB_1 == source )
	{
		de_kwrap_setcvisrcparams_scart_rgb_1( &param );
	}
	else if ( IS_VGA_YPBPR( source ) )
	{
		de_kwrap_setcvisrcparams_vga_ypbpr( &param, source );
	}
	else if ( IS_ATV_CVBS_SVIDEO( source ) )
	{
		de_kwrap_setcvisrcparams_atv_cvbs_svideo( &param, source );
	}
	else if ( IS_SCART_1_2( source ) )
	{
		de_kwrap_setcvisrcparams_scart( &param, source );
	}
	else if ( IS_HDMI( source ) )
	{
		de_kwrap_setcvisrcparams_hdmi( &param );
	}

	DE_NOTI("[de_kwrap]SetCviSrcType. source =%d \n"\
			"          hsize %d, vsize %d, hoffset %d, voffset %d, scan %d, color %d aspect %d\n"\
			"          c_sample %d, sc_c_sample %d, sampling %d, cvi_input_src:%d, cvd_color_std:%d\n",\
			source, param.size_offset.hsize,param.size_offset.vsize,param.size_offset.hoffset,param.size_offset.voffset,\
			param.scan,param.color,param.aspect,param.c_sample,param.sc_c_sample,param.sampling,\
			param.cvi_input_src,param.cvd_color_std);

	if ( param.sc_c_sample == LX_DE_SCALER_422 )
	{
		bCviCsampleMode = TRUE;
	}

	if ( de_kwrap_setcvicsamplemode(wId, bCviCsampleMode) < 0 )
		DE_ERROR("[de_kwrap][L8-A0 WR] de_kwrap_setcvicsamplemode fail.\n");

	//cvi_fir_mode = param.sampling;

	//if ( de_kwrap_SetCviFIR(wId, cvi_fir_mode, param.cvi_input_src) < 0 )
		//DE_ERROR("[de_kwrap]de_kwrap_SetCviFIR fail.\n");

//	DE_LOCK();
//	DE_TRACE_BEGIN();

	//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CVI_SRC_TYPE, &param);
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_SRC_TYPE,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

//	DE_TRACE_END();
//	DE_UNLOCK();

	return ret;
}


int de_kwrap_setcvisrc(LX_DE_CVI_SRC_TYPE_T *param)
{
	int ret = RET_ERROR;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CVI_SRC_TYPE, param);
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_SRC_TYPE,(unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

	DE_NOTI("[de_kwrap]SetCviSrcType.\n"\
		"          hsize %d, vsize %d, hoffset %d, voffset %d, scan %d, color %d aspect %d\n"\
		"          c_sample %d, sc_c_sample %d, sampling %d, cvi_input_src:%d, cvd_color_std:%d, de_mode:%d\n",\
		param->size_offset.hsize,param->size_offset.vsize,param->size_offset.hoffset,param->size_offset.voffset,\
		param->scan,param->color,param->aspect,param->c_sample,param->sc_c_sample,param->sampling,\
		param->cvi_input_src,param->cvd_color_std,param->de_mode);
	}while(0);
func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}


/**
 *	set CVI FIR coefficient.
 *
 */
int de_kwrap_setcvifir(UINT8 wId, LX_DE_CVI_SAMPLING_MODE_T sample_mode, LX_DE_CVI_INPUT_SRC_T cvi_input_src)
{
	int ret = RET_ERROR;
	LX_DE_CVI_FIR_T param = { 0, };
	int i;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	if (wId < 1)	param.cvi_channel = LX_DE_CVI_CH_A;
	else			param.cvi_channel = LX_DE_CVI_CH_B;

	switch (sample_mode)
	{
		case LX_DE_CVI_NORMAL_SAMPLING:
		{
			param.isEnable = TRUE;
			for (i=0;i<NUM_OF_CVI_FIR_COEF;i++)
				{
					param.fir_coef[i] = coef_FIR_Y_Normal[i];

					if (i<(NUM_OF_CVI_FIR_COEF-2))
					{
						if (cvi_input_src == LX_DE_CVI_SRC_ATV || cvi_input_src == LX_DE_CVI_SRC_CVBS)
							param.fir_coef_CbCr[i] = coef_FIR_H13_CVD_CbCr_Normal[i];
						else
							param.fir_coef_CbCr[i] = coef_FIR_CbCr_Normal[i];
					}
				}
			}
			break;
		case LX_DE_CVI_DOUBLE_SAMPLING:
			{
				param.isEnable = TRUE;
				for (i=0;i<NUM_OF_CVI_FIR_COEF;i++)
				{
					param.fir_coef[i] = coef_FIR_Y_Double[i];
					if (i<(NUM_OF_CVI_FIR_COEF-2))
						param.fir_coef_CbCr[i] = coef_FIR_CbCr_Double[i];
				}
			}
			break;

		case LX_DE_CVI_QUAD_SAMPLING:
			{
				param.isEnable = TRUE;
				for (i=0;i<NUM_OF_CVI_FIR_COEF;i++)
				{
					param.fir_coef[i] = coef_FIR_Y_Quad[i];
					if (i<(NUM_OF_CVI_FIR_COEF-2))
						param.fir_coef_CbCr[i] = coef_FIR_CbCr_Quad[i];
				}
			}
			break;

		default:
			break;
	}

	//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CVI_FIR, &param);
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_FIR,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}


/**
 *	set CVI window mute for ADC ooooonly
 *
 */
int de_kwrap_setcvitpg(UINT8 wId, BOOLEAN isPtnOn, LX_DE_CVI_TPG_COLOR_T ptnColor)
{
	int ret = RET_ERROR;
	LX_DE_CVI_TPG_T param;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

//	DE_LOCK();
	//DE_TRACE_BEGIN();

	if (wId < 1)	param.cvi_channel = LX_DE_CVI_CH_A;
	else			param.cvi_channel = LX_DE_CVI_CH_B;

	param.isPtnOn = param.isFrzOn = isPtnOn;
	param.ptnColor = ptnColor;
	param.isGBR = FALSE;

	//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CVI_TPG, &param);
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_TPG,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set CVI color sub sample mode
 *
 */
int de_kwrap_setcvicsamplemode(UINT8 wId, BOOLEAN enable)
{
	int ret = RET_ERROR;
	LX_DE_CSAMPLE_MODE_T param;

//	CHECK_DEV_FD(g_de_ctx.dev_fd);

//	DE_LOCK();
//	DE_TRACE_BEGIN();

	if (wId < 1)	param.cvi_channel = LX_DE_CVI_CH_A;
	else			param.cvi_channel = LX_DE_CVI_CH_B;

	param.is3tap = enable;
	//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CVI_CSAMPLE_MODE, &param);
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_CSAMPLE_MODE,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

//	DE_TRACE_END();
//	DE_UNLOCK();

	return ret;
}


/**
 * de cvi video frame buffer freeze to read/write video frame before cvi csc parameter for self-diagnosis.
 */
int de_kwrap_setcvifreeze(LX_DE_CVI_CAPTURE_FREEZE_T cap_freeze)
{
	int ret = RET_ERROR;
	LX_DE_CVI_CAPTURE_FREEZE_T param;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	memcpy(&param, &cap_freeze, sizeof(param));

//	ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CVI_FREEZE, &param);
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_FREEZE,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );


func_exit:

//	DE_TRACE_END();
//	DE_UNLOCK();

	return ret;
}

/**
 * de read/write video frame before cvi csc parameter for self-diagnosis.
 */
int de_kwrap_set_cvirwvideoframebuffer(LX_DE_CVI_RW_VIDEO_FRAME_T param)
{
	int ret = RET_ERROR;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_PRINT("[de_kwrap] Set_CviRWVideoFrameBuffer win %d, (x,y,w,h)=(%d,%d,%d,%d), bReadOnOff = %d\n", param.region.win_id,
									 	param.region.pixelGrabX,
										param.region.pixelGrabY,
										param.region.pixelGrabW,
										param.region.pixelGrabH,
										param.bReadOnOff);
	//ret = ioctl(g_de_ctx.dev_fd, DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER, &param);
	ret = resource_mgr_ioctl(DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * select SCART RGB Bypass mode or CVD Overlay mode.
 */
int de_kwrap_setscartrgbbypassmode(int Bypass_Enable)
{
	int ret = RET_ERROR;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_PRINT("[de_kwrap] SetScartRGBBypassMode %d\n", Bypass_Enable);
	//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_SCART_RGB_BYPASS_MODE, &Bypass_Enable);
	ret = resource_mgr_ioctl(DE_IOW_SET_SCART_RGB_BYPASS_MODE,(unsigned long)&Bypass_Enable,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * de read/write video frame before cvi csc parameter for self-diagnosis.
 */
int de_kwrap_read_cvivideoframebuffer(LX_DE_CVI_RW_VIDEO_FRAME_T param, UINT16 hoffset, UINT16 voffset)
{
	int ret = RET_ERROR;

	//	CHECK_DEV_FD(g_de_ctx.dev_fd);

	//	DE_LOCK();
	//	DE_TRACE_BEGIN();

	UINT32 reg_read_tmp, reg_write_tmp;
	UINT32 i,j;
	UINT32 PixelSumY, PixelSumCb, PixelSumCr;
	UINT32 PixelY, PixelCb, PixelCr;
	int PixelY_CSC = 0, PixelCb_CSC = 0, PixelCr_CSC = 0;
	UINT32 CSC_Enable;
	UINT32 data_en_mode;
	int csc_coeff_0, csc_coeff_1, csc_coeff_2, csc_coeff_3, csc_coeff_4, csc_coeff_5,  csc_coeff_6, csc_coeff_7, csc_coeff_8;
	int csc_off_0, csc_off_1, csc_off_2, csc_off_3,  csc_off_4, csc_off_5;
	int h_size, data_in_sel;

	UINT32 cvi_base_diff = 0;

	if ( lx_chip_rev( ) >= LX_CHIP_REV(M17,A0) )
		cvi_base_diff = 0x01000000;
	else
		cvi_base_diff = 0x0;

	SYS_IO_ReadRegArray(0xC8000200 + cvi_base_diff, 4,&reg_read_tmp);	// TOP_CTRL
	data_in_sel = (reg_read_tmp >> 14) & 0xf;
	data_en_mode = (reg_read_tmp >> 31) & 0x1;

	SYS_IO_ReadRegArray(0xC8000208 + cvi_base_diff,4, &reg_read_tmp);	// SIZE_CTRL
	h_size = reg_read_tmp & 0x1fff;

	if( (data_in_sel == 9) && (h_size == 1440) )	//Component AND pixel repeatation mode ?
		param.region.pixelGrabX = param.region.pixelGrabX << 1;

	if( data_en_mode == 1)
	{
		SYS_IO_ReadRegArray(0xC8000248 + cvi_base_diff,4, &reg_read_tmp);	// OFFSET_READ

		hoffset = reg_read_tmp & 0x1FFF;
		voffset = (reg_read_tmp >> 16) & 0x1FFF;
	}
	else
	{
		SYS_IO_ReadRegArray(0xC8000204 + cvi_base_diff,4, &reg_read_tmp);	// OFFSET_CTRL

		hoffset = reg_read_tmp & 0x1FFF;
		voffset = (reg_read_tmp >> 16) & 0x1FFF;
	}

	DE_NOTI("[de_kwrap] win %d, (x,y,w,h)=(%d,%d,%d,%d), bReadOnOff = %d\n", param.region.win_id,
			param.region.pixelGrabX,
			param.region.pixelGrabY,
			param.region.pixelGrabW,
			param.region.pixelGrabH,
			param.bReadOnOff);


	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff,4 ,&reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp & 0x80000000;
	reg_write_tmp |= 0x00008000;
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff, 4,&reg_write_tmp);	// Enable pixel sum

	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp | (param.region.pixelGrabX + hoffset) | ( (param.region.pixelGrabX + hoffset + param.region.pixelGrabW - 1) << 16);
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff, 4,&reg_write_tmp);	// enter start_pos_x and end_pos_x

	reg_write_tmp = (param.region.pixelGrabY + voffset) | ( (param.region.pixelGrabY + voffset + param.region.pixelGrabH - 1) << 16);
	SYS_IO_WriteRegArray(0xC800026C + cvi_base_diff,4,&reg_write_tmp);	// enter start_pos_x and end_pos_x

	msleep(100);

	SYS_IO_ReadRegArray(0xC8000270 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_STATUS0
	PixelSumY = reg_read_tmp;
	SYS_IO_ReadRegArray(0xC8000274 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_STATUS1
	PixelSumCb = reg_read_tmp;
	SYS_IO_ReadRegArray(0xC8000278 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_STATUS2
	PixelSumCr = reg_read_tmp;

	DE_PRINT("[de_kwrap] (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelSumY,
			PixelSumCb,
			PixelSumCr);

	PixelY = PixelSumY / (param.region.pixelGrabH * param.region.pixelGrabW);
	PixelCb = PixelSumCb / (param.region.pixelGrabH * param.region.pixelGrabW);
	PixelCr = PixelSumCr / (param.region.pixelGrabH * param.region.pixelGrabW);

	DE_NOTI("[de_kwrap] Before CSC (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelY, PixelCb, PixelCr);

	SYS_IO_ReadRegArray(0xC8000240 + cvi_base_diff,4, &reg_read_tmp);	// CSC_CTRL7
	CSC_Enable = (reg_read_tmp >> 1) & 0x1;

	if(CSC_Enable == 1)
	{
		SYS_IO_ReadRegArray(0xC8000224 + cvi_base_diff, 4,&reg_read_tmp);	// CSC_CTRL0
		csc_coeff_1 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_0 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000228 + cvi_base_diff,4, &reg_read_tmp);	// CSC_CTRL1
		csc_coeff_3 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_2 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC800022C + cvi_base_diff,4, &reg_read_tmp);	// CSC_CTRL2
		csc_coeff_5 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_4 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000230 + cvi_base_diff, 4,&reg_read_tmp);	// CSC_CTRL3
		csc_coeff_7 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_6 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000234 + cvi_base_diff,4, &reg_read_tmp);	// CSC_CTRL4
		csc_off_0 = _de_kwrap_hex11bit_to_int(reg_read_tmp & 0x7FF);
		csc_coeff_8 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000238 + cvi_base_diff, 4,&reg_read_tmp);	// CSC_CTRL5
		csc_off_2 = _de_kwrap_hex11bit_to_int(reg_read_tmp & 0x7FF);
		csc_off_1 = _de_kwrap_hex11bit_to_int( (reg_read_tmp >> 16 ) & 0x7FF);

		SYS_IO_ReadRegArray(0xC800023C + cvi_base_diff,4, &reg_read_tmp);	// CSC_CTRL6
		csc_off_4 = _de_kwrap_hex11bit_to_int(reg_read_tmp & 0x7FF);
		csc_off_3 = _de_kwrap_hex11bit_to_int( (reg_read_tmp >> 16 ) & 0x7FF);

		SYS_IO_ReadRegArray(0xC8000240 + cvi_base_diff,4, &reg_read_tmp);	// CSC_CTRL6
		csc_off_5 = _de_kwrap_hex11bit_to_int( (reg_read_tmp >> 16 ) & 0x7FF);

		PixelY_CSC = (int)( csc_coeff_0*(PixelY + csc_off_0) + csc_coeff_1*(PixelCb + csc_off_1) + csc_coeff_2*(PixelCr + csc_off_2)) / 4096 + csc_off_3;
		PixelCb_CSC = (int)( csc_coeff_3*(PixelY + csc_off_0) + csc_coeff_4*(PixelCb + csc_off_1) + csc_coeff_5*(PixelCr + csc_off_2)) / 4096 + csc_off_4;
		PixelCr_CSC = (int)( csc_coeff_6*(PixelY + csc_off_0) + csc_coeff_7*(PixelCb + csc_off_1) + csc_coeff_8*(PixelCr + csc_off_2) ) / 4096 + csc_off_5;

		DE_PRINT("[de_kwrap] csc_coeff_0(%d),_1(%d),_2(%d)\n", csc_coeff_0, csc_coeff_1, csc_coeff_2);
		DE_PRINT("[de_kwrap] csc_coeff_3(%d),_4(%d),_5(%d)\n", csc_coeff_3, csc_coeff_4, csc_coeff_5);
		DE_PRINT("[de_kwrap] csc_coeff_6(%d),_7(%d),_8(%d)\n", csc_coeff_6, csc_coeff_7, csc_coeff_8);
		DE_PRINT("[de_kwrap] csc_offset_0(%d),_1(%d),_2(%d)\n", csc_off_0, csc_off_1, csc_off_2);
		DE_PRINT("[de_kwrap] csc_offset_3(%d),_4(%d),_5(%d)\n", csc_off_3, csc_off_4, csc_off_5);
	}
	else
	{
		DE_NOTI("[de_kwrap] CSC Bypass !!! \n");
	}

	if(PixelY_CSC < 0)
		PixelY_CSC = 0;
	if(PixelCb_CSC <0)
		PixelCb_CSC = 0;
	if(PixelCr_CSC < 0)
		PixelCr_CSC = 0;

	DE_NOTI("[de_kwrap] After CSC (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelY_CSC, PixelCb_CSC, PixelCr_CSC);

	for (i=0; i<param.region.pixelGrabH; i++)
	{
		for (j=0;j<param.region.pixelGrabW;j++)
		{
			(param.color +j+ (i*param.region.pixelGrabW) )->pixelGrabY = PixelY_CSC;
			(param.color +j+ (i*param.region.pixelGrabW) )->pixelGrabCb = PixelCb_CSC;
			(param.color +j+ (i*param.region.pixelGrabW) )->pixelGrabCr = PixelCr_CSC;
		}
	}

	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp & 0xFFFF7FFF;
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff,4,&reg_write_tmp);	// Disable pixel sum

	ret = RET_OK;

	return ret;
}


int de_kwrap_read_cvivideoframebuffer_4k(LX_DE_CVI_RW_VIDEO_FRAME_T param, UINT16 hoffset, UINT16 voffset, int cvi_b_mode)
{
	int ret = RET_ERROR;

	//	CHECK_DEV_FD(g_de_ctx.dev_fd);

	//	DE_LOCK();
	//	DE_TRACE_BEGIN();

	UINT32 reg_read_tmp, reg_write_tmp;
	UINT32 i,j;
	UINT32 PixelSumY, PixelSumCb, PixelSumCr;
	UINT32 PixelY, PixelCb, PixelCr;
	int PixelY_CSC = 0, PixelCb_CSC = 0, PixelCr_CSC = 0;
	UINT32 CSC_Enable;
	UINT32 data_en_mode;
	int csc_coeff_0, csc_coeff_1, csc_coeff_2, csc_coeff_3, csc_coeff_4, csc_coeff_5,  csc_coeff_6, csc_coeff_7, csc_coeff_8;
	int csc_off_0, csc_off_1, csc_off_2, csc_off_3,  csc_off_4, csc_off_5;
	int h_size, data_in_sel;
	int cvi_b_offset = 0;
	UINT32 cvi_base_diff = 0;

	if ( lx_chip_rev( ) >= LX_CHIP_REV(M17,A0) )
		cvi_base_diff = 0x01000000;
	else
		cvi_base_diff = 0x0;

	if (cvi_b_mode > 0)
		cvi_b_offset = 0x100;

	SYS_IO_ReadRegArray(0xC8000200 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// TOP_CTRL
	data_in_sel = (reg_read_tmp >> 14) & 0xf;
	data_en_mode = (reg_read_tmp >> 31) & 0x1;

	SYS_IO_ReadRegArray(0xC8000208 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// SIZE_CTRL
	h_size = reg_read_tmp & 0x1fff;

	if( (data_in_sel == 9) && (h_size == 1440) )	//Component AND pixel repeatation mode ?
		param.region.pixelGrabX = param.region.pixelGrabX << 1;

	if( data_en_mode == 1)
	{
		SYS_IO_ReadRegArray(0xC8000248 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// OFFSET_READ

		hoffset = reg_read_tmp & 0x1FFF;
		voffset = (reg_read_tmp >> 16) & 0x1FFF;
	}
	else
	{
		SYS_IO_ReadRegArray(0xC8000204 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// OFFSET_CTRL

		hoffset = reg_read_tmp & 0x1FFF;
		voffset = (reg_read_tmp >> 16) & 0x1FFF;
	}

	DE_PRINT("[de_kwrap] win %d, (x,y,w,h)=(%d,%d,%d,%d), bReadOnOff = %d\n", param.region.win_id,
			param.region.pixelGrabX,
			param.region.pixelGrabY,
			param.region.pixelGrabW,
			param.region.pixelGrabH,
			param.bReadOnOff);


	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp & 0x80000000;
	reg_write_tmp |= 0x00008000;
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff + cvi_b_offset,4,&reg_write_tmp);	// Enable pixel sum

	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp | (param.region.pixelGrabX + hoffset) | ( (param.region.pixelGrabX + hoffset + param.region.pixelGrabW - 1) << 16);
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff + cvi_b_offset,4,&reg_write_tmp);	// enter start_pos_x and end_pos_x

	reg_write_tmp = (param.region.pixelGrabY + voffset) | ( (param.region.pixelGrabY + voffset + param.region.pixelGrabH - 1) << 16);
	SYS_IO_WriteRegArray(0xC800026C + cvi_base_diff + cvi_b_offset, 4,&reg_write_tmp);	// enter start_pos_x and end_pos_x

	msleep(100);

	SYS_IO_ReadRegArray(0xC8000270 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// PIX_SUM_STATUS0
	PixelSumY = reg_read_tmp;
	SYS_IO_ReadRegArray(0xC8000274 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// PIX_SUM_STATUS1
	PixelSumCb = reg_read_tmp;
	SYS_IO_ReadRegArray(0xC8000278 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// PIX_SUM_STATUS2
	PixelSumCr = reg_read_tmp;

	DE_PRINT("[de_kwrap] (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelSumY,
			PixelSumCb,
			PixelSumCr);

	PixelY = PixelSumY / (param.region.pixelGrabH * param.region.pixelGrabW);
	PixelCb = PixelSumCb / (param.region.pixelGrabH * param.region.pixelGrabW);
	PixelCr = PixelSumCr / (param.region.pixelGrabH * param.region.pixelGrabW);

	DE_PRINT("[de_kwrap] Before CSC (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelY, PixelCb, PixelCr);

	SYS_IO_ReadRegArray(0xC8000240 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL7
	CSC_Enable = (reg_read_tmp >> 1) & 0x1;

	if(CSC_Enable == 1)
	{
		SYS_IO_ReadRegArray(0xC8000224 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL0
		csc_coeff_1 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_0 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000228 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL1
		csc_coeff_3 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_2 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC800022C + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL2
		csc_coeff_5 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_4 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000230 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL3
		csc_coeff_7 = _de_kwrap_hex15bit_to_int(reg_read_tmp & 0x7FFF);
		csc_coeff_6 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000234 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL4
		csc_off_0 = _de_kwrap_hex11bit_to_int(reg_read_tmp & 0x7FF);
		csc_coeff_8 = _de_kwrap_hex15bit_to_int( (reg_read_tmp >> 16) & 0x7FFF );

		SYS_IO_ReadRegArray(0xC8000238 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL5
		csc_off_2 = _de_kwrap_hex11bit_to_int(reg_read_tmp & 0x7FF);
		csc_off_1 = _de_kwrap_hex11bit_to_int( (reg_read_tmp >> 16 ) & 0x7FF);

		SYS_IO_ReadRegArray(0xC800023C + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL6
		csc_off_4 = _de_kwrap_hex11bit_to_int(reg_read_tmp & 0x7FF);
		csc_off_3 = _de_kwrap_hex11bit_to_int( (reg_read_tmp >> 16 ) & 0x7FF);

		SYS_IO_ReadRegArray(0xC8000240 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// CSC_CTRL6
		csc_off_5 = _de_kwrap_hex11bit_to_int( (reg_read_tmp >> 16 ) & 0x7FF);

		PixelY_CSC = (int)( csc_coeff_0*(PixelY + csc_off_0) + csc_coeff_1*(PixelCb + csc_off_1) + csc_coeff_2*(PixelCr + csc_off_2)) / 4096 + csc_off_3;
		PixelCb_CSC = (int)( csc_coeff_3*(PixelY + csc_off_0) + csc_coeff_4*(PixelCb + csc_off_1) + csc_coeff_5*(PixelCr + csc_off_2)) / 4096 + csc_off_4;
		PixelCr_CSC = (int)( csc_coeff_6*(PixelY + csc_off_0) + csc_coeff_7*(PixelCb + csc_off_1) + csc_coeff_8*(PixelCr + csc_off_2) ) / 4096 + csc_off_5;

		DE_PRINT("[de_kwrap] csc_coeff_0(%d),_1(%d),_2(%d)\n", csc_coeff_0, csc_coeff_1, csc_coeff_2);
		DE_PRINT("[de_kwrap] csc_coeff_3(%d),_4(%d),_5(%d)\n", csc_coeff_3, csc_coeff_4, csc_coeff_5);
		DE_PRINT("[de_kwrap] csc_coeff_6(%d),_7(%d),_8(%d)\n", csc_coeff_6, csc_coeff_7, csc_coeff_8);
		DE_PRINT("[de_kwrap] csc_offset_0(%d),_1(%d),_2(%d)\n", csc_off_0, csc_off_1, csc_off_2);
		DE_PRINT("[de_kwrap] csc_offset_3(%d),_4(%d),_5(%d)\n", csc_off_3, csc_off_4, csc_off_5);
	}
	else
	{
		DE_PRINT("[de_kwrap] CSC Bypass !!! \n");
	}

	if(PixelY_CSC < 0)
		PixelY_CSC = 0;
	if(PixelCb_CSC <0)
		PixelCb_CSC = 0;
	if(PixelCr_CSC < 0)
		PixelCr_CSC = 0;

	DE_PRINT("[de_kwrap] After CSC (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelY_CSC, PixelCb_CSC, PixelCr_CSC);

	for (i=0; i<param.region.pixelGrabH; i++)
	{
		for (j=0;j<param.region.pixelGrabW;j++)
		{
			(param.color +j+ (i*param.region.pixelGrabW) )->pixelGrabY = PixelY_CSC;
			(param.color +j+ (i*param.region.pixelGrabW) )->pixelGrabCb = PixelCb_CSC;
			(param.color +j+ (i*param.region.pixelGrabW) )->pixelGrabCr = PixelCr_CSC;
		}
	}

	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff + cvi_b_offset,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp & 0xFFFF7FFF;
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff + cvi_b_offset,4, &reg_write_tmp);	// Disable pixel sum

	ret = RET_OK;

	return ret;
}

int de_kwrap_debugenable_cvivideoframebuffer(int enable)
{
	int ret = RET_OK;

	UINT32 reg_read_tmp, reg_write_tmp;

	UINT32 cvi_base_diff = 0;

	if ( lx_chip_rev( ) >= LX_CHIP_REV(M17,A0) )
		cvi_base_diff = 0x01000000;
	else
		cvi_base_diff = 0x0;

	SYS_IO_ReadRegArray(0xC8000268 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	if(enable)
		reg_write_tmp = reg_read_tmp | 0x80000000;
	else
		reg_write_tmp = reg_read_tmp & 0x7FFFFFFF;
	SYS_IO_WriteRegArray(0xC8000268 + cvi_base_diff,4,&reg_write_tmp);	// Enable debug

	SYS_IO_ReadRegArray(0xC8000368 + cvi_base_diff,4, &reg_read_tmp);	// PIX_SUM_CTRL0
	if(enable)
		reg_write_tmp = reg_read_tmp | 0x80000000;
	else
		reg_write_tmp = reg_read_tmp & 0x7FFFFFFF;
	SYS_IO_WriteRegArray(0xC8000368 + cvi_base_diff, 4,&reg_write_tmp);	// Enable debug

	return ret;
}

static int _de_kwrap_hex15bit_to_int(UINT32 hex_number)
{
	UINT32 hex_tmp;
	int ret;

	hex_tmp = (hex_number + 0x4000) & 0x7FFF;

	ret = (int)hex_tmp - 0x4000;

	return ret;
}

static int _de_kwrap_hex11bit_to_int(UINT32 hex_number)
{
	UINT32 hex_tmp;
	int ret;

	hex_tmp = (hex_number + 0x400) & 0x7FF;

	ret = (int)hex_tmp - 0x400;

	return ret;
}
#endif

