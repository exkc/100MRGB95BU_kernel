 	/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		justine.jeong
 *  @version	1.0
 *  @date		2018-05-29
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/module.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"


#include "os_util.h"
#include "base_device.h"
#include "de_def.h"
#include "hal/ipc_phys_hal.h"
#include "vsc_bwm.h"

#include "v4l2_vsc_event.h"

//#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
//#include "aspectratiodrv/aspectratiodrv.h"
#include <export_vsc_adapter.h>
#include <export_vsc_orbit_adapter.h>

//#endif
#include "resource_mgr.h"
#include "de_kwrap.h"
#include "pe_kwrap.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_hdr.h"
#include "vpq_hwrap_pe.h"
#include "../hdmi20/hdmi20_kwarp.h"
#include "v4l2_vpq_latency.h"
#include "v4l2_vpq_be.h"
#ifdef INCLUDE_KDRV_OVI
#include "ovi_kapi.h"
#include "../ovi/ovi_hal.h"
#endif

//#include "hdr_kwrap_defs.h"
//#include "hdr_kwrap.h"
//#include "dovi_hdr.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
#define VSC_ORBIT_DRV_CALCULATE

#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1 || CONFIG_LX_M23_CHIP_FIRMWARE == 1 || CONFIG_LX_O24_CHIP_FIRMWARE == 1 || CONFIG_LX_O26_CHIP_FIRMWARE == 1)
#define VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
#define VSC_ORBIT_DRV_CALCULATE
#else
#undef VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
#define VSC_ORBIT_DRV_CALCULATE
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vsc_config {
	int open;
	struct v4l2_ext_vsc_connect_info inout_info;
	struct v4l2_ext_vsc_vdo_mode vdo_mode;
	enum v4l2_ext_vsc_win_color mute;
	enum v4l2_ext_vsc_hdr_type hdr_type;
	struct v4l2_ext_vsc_win_region win_info;
	struct v4l2_ext_vsc_win_prop sub_mode;
	struct v4l2_ext_vsc_zorder order;
	struct v4l2_ext_vsc_zorder_info zorder_info;
	enum v4l2_ext_vsc_pattern pat;
	struct v4l2_ext_vsc_latency_pattern_info lag_pat;
	BOOLEAN freeze;
	UINT32 frame_delay;
	BOOLEAN seamless;
	BOOLEAN rgb444;
	BOOLEAN cvi_frz;
	BOOLEAN sub_occupied;
	BOOLEAN en_local_mute;
	enum vsc_feedback_position pos;
	struct v4l2_ext_vsc_orbit_policy orbit_policy;
	struct v4l2_ext_vsc_orbit_window orbit_win;
	struct v4l2_ext_vsc_orbit_window calculated_orbit_win;
	struct v4l2_ext_vsc_orbit_move orbit_move;
	UINT32 colordomain;//see LX_HDMI_COLOR_STATUS_T
	UINT32 ipc_mode;
	UINT32 keep_submode;
	UINT32 ptp; // pixel to pixel mode
	UINT32 pid;
//#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
	struct v4l2_ext_vsc_aspectratio_policy aspectratio_policy;
	struct v4l2_ext_video_rect calculated_input_rect;
	struct v4l2_ext_video_rect calculated_output_rect;
//#endif
	UINT32 socts;
	enum v4l2_ext_vsc_scan_mode scan_mode;
};
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
struct vsc_config vsc_config[LX_DE_WIN_MAX] = { 0 };
UINT8 ghdmiphyport[LX_DE_WIN_MAX];
kwrap_vp_timing_info_t gbufTiming[LX_DE_WIN_MAX];
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _vsc_vp_periodictask(UINT32 winid);
static int _vsc_cvicfgfromhdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo);
static int _vsc_cvicfgfromcvd(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo, char flag);
static int _vsc_cvicfgfromadc(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int _vsc_check_fr(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t srcTiming, UINT16 *frameRate);
static int _vsc_read_cvi_pixel(LX_DE_CVI_RW_VIDEO_FRAME_T param, int cvi_b_mode);
int vsc_external_library(UINT16 wId, UINT16 afd, UINT16 par_width, UINT16 par_height, LX_DE_WIN_INFO_T *win_info);
void v4l2_vsc_update_pulldown(UINT32 type);
int test_read_cvi_pixel_BarPixelGrab(void);
int vsc_get_dev_info(int win, int param);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

#define TBL_NUM(X)	(sizeof(X) /sizeof((X)[0]))

typedef struct O_ENUM {
	int 	PreEnum;
	int PostEnum;
} s0_enum;

static const s0_enum ATV_COLOR_TYPE[ ] =
{	/// LX_AFE_VIDEO_SYSTEM_T			LX_DE_CVD_COLOR_STD_T
	{	LX_DEFAULT, 				LX_DE_COLOR_UNKNOWN},
	{	LX_NTSC_M,					LX_DE_COLOR_NTSC_M_RF},
	{	LX_NTSC_J,					LX_DE_COLOR_NTSC_M_RF},
	{	LX_NTSC_443,				LX_DE_COLOR_NTSC_443_RF},
	{	LX_PAL_BG,					LX_DE_COLOR_PAL_RF},
	{	LX_PAL_N,					LX_DE_COLOR_PAL_RF},
	{	LX_PAL_M,					LX_DE_COLOR_PAL_M_RF},
	{	LX_PAL_CN,					LX_DE_COLOR_PAL_NC_RF},
	{	LX_PAL_60,					LX_DE_COLOR_PAL_60_RF},
	{	LX_SECAM,					LX_DE_COLOR_SECAM_RF},
	{	LX_NON_STANDARD,			LX_DE_COLOR_UNKNOWN},
	{	LX_MULTI,					LX_DE_COLOR_UNKNOWN},
	{	LX_VIDEO_SYSTEM_NUM,		LX_DE_COLOR_UNKNOWN},
};

static const s0_enum CVD_COLOR_TYPE[ ] =
{	/// LX_AFE_VIDEO_SYSTEM_T			LX_DE_CVD_COLOR_STD_T
	{	LX_DEFAULT, 				LX_DE_COLOR_UNKNOWN},
	{	LX_NTSC_M,					LX_DE_COLOR_NTSC_M},
	{	LX_NTSC_J,					LX_DE_COLOR_NTSC_M},
	{	LX_NTSC_443,				LX_DE_COLOR_NTSC_443},
	{	LX_PAL_BG,					LX_DE_COLOR_PAL},
	{	LX_PAL_N,					LX_DE_COLOR_PAL},
	{	LX_PAL_M,					LX_DE_COLOR_PAL_M},
	{	LX_PAL_CN,					LX_DE_COLOR_PAL_NC},
	{	LX_PAL_60,					LX_DE_COLOR_PAL_60},
	{	LX_SECAM,					LX_DE_COLOR_SECAM},
	{	LX_NON_STANDARD,			LX_DE_COLOR_UNKNOWN},
	{	LX_MULTI,					LX_DE_COLOR_UNKNOWN},
	{	LX_VIDEO_SYSTEM_NUM,		LX_DE_COLOR_UNKNOWN},
};


static const kwrap_vp_hdmi_color_map_t HDMI_COLORMETRY_MAP[] =
{
	{	LX_HDMI_CS_FULL_RGB, LX_DE_COLOR_RGBEX, LX_DE_SCALER_444},
	{	LX_DVI_CS_FULL_RGB, LX_DE_COLOR_RGBEX, LX_DE_SCALER_444},
	{	LX_HDMI_CS_LIMITED_RGB, LX_DE_COLOR_RGB, LX_DE_SCALER_444},
	{	LX_HDMI_CS_YCBCR422_601, LX_DE_COLOR_601, LX_DE_SCALER_422},
	{	LX_HDMI_CS_YCBCR444_601, LX_DE_COLOR_601, LX_DE_SCALER_444},
	{	LX_HDMI_CS_YCBCR422_709, LX_DE_COLOR_709, LX_DE_SCALER_422},
	{	LX_HDMI_CS_YCBCR444_709, LX_DE_COLOR_709, LX_DE_SCALER_444},
	{	LX_HDMI_CS_XVYCC422_601, LX_DE_COLOR_XVYCC601, LX_DE_SCALER_422},
	{	LX_HDMI_CS_XVYCC444_601, LX_DE_COLOR_XVYCC601, LX_DE_SCALER_444},
	{	LX_HDMI_CS_XVYCC422_709, LX_DE_COLOR_XVYCC709, LX_DE_SCALER_422},
	{	LX_HDMI_CS_XVYCC444_709, LX_DE_COLOR_XVYCC709, LX_DE_SCALER_444},
	{	LX_HDMI_CS_YCBCR420_601, LX_DE_COLOR_601, LX_DE_SCALER_420},
	{	LX_HDMI_CS_YCBCR420_709, LX_DE_COLOR_709, LX_DE_SCALER_420},
	{	LX_HDMI_CS_XVYCC420_601, LX_DE_COLOR_XVYCC601, LX_DE_SCALER_420},
	{	LX_HDMI_CS_XVYCC420_709, LX_DE_COLOR_XVYCC709, LX_DE_SCALER_420},
	{	LX_HDMI_CS_SYCC420_601, LX_DE_COLOR_601, LX_DE_SCALER_420},
	{	LX_HDMI_CS_ADOBEYCC420_601, LX_DE_COLOR_601, LX_DE_SCALER_420},
	{	LX_HDMI_CS_YCBCR444_2020_CL, LX_DE_COLOR_2020_CL, LX_DE_SCALER_444},
	{	LX_HDMI_CS_YCBCR444_2020_NCL, LX_DE_COLOR_2020_NCL, LX_DE_SCALER_444},
	{	LX_HDMI_CS_YCBCR422_2020_CL, LX_DE_COLOR_2020_CL, LX_DE_SCALER_422},
	{	LX_HDMI_CS_YCBCR422_2020_NCL, LX_DE_COLOR_2020_NCL, LX_DE_SCALER_422},
	{	LX_HDMI_CS_YCBCR420_2020_CL, LX_DE_COLOR_2020_CL, LX_DE_SCALER_420},
	{	LX_HDMI_CS_YCBCR420_2020_NCL, LX_DE_COLOR_2020_NCL, LX_DE_SCALER_420},
};

/*CVI default configuration */
static LX_DE_CVI_SRC_TYPE_T cvi_common_config[SRC_INPUT_MAX] ;/*= 
  {cvi_channel   ,size_offset,color, aspect, scan, bit_res, c_sample, de_mode, sampling, sc_c_sample, stability, field_polarity, yc_delay, cvi_port, trid_full_format, cvi_input_src, cvd_color_std },
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_444,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_VGA,LX_DE_COLOR_DEFAULT},//NONE [Unused]
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_RGBEX,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_444,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_ADC,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_VGA,LX_DE_COLOR_DEFAULT},//VGA
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_ADC,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_YPBPR,LX_DE_COLOR_DEFAULT},//YPbPr
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601_CVD,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_ATV,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_ATV,LX_DE_COLOR_DEFAULT},//ATV
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601_CVD,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_OTHERS,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_CVBS,LX_DE_COLOR_DEFAULT},//CVBS
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601_CVD,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_OTHERS,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_SCART,LX_DE_COLOR_DEFAULT},//SCART
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_RGB,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_ADC,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_YPBPR,LX_DE_COLOR_PAL},//SCART_BYPASS
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_RGB,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_444,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_EXT_A,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_HDMI,LX_DE_COLOR_DEFAULT},//HDMI
	{},{},{},{}
};*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static UINT32 _g_curr_pulldown = 0;
static UINT32 _g_prev_pulldown = 0;

ASPECTRATIO_CALLBACK_T  *vsc_AspectratioCallbackFp;
ORBIT_CALLBACK_T  *vsc_OrbitCallbackFp;

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
extern int DE_IO_SetSharedMem(unsigned long arg);
static int _venc_control(unsigned int id, LX_DE_DVR_ON_T flag, unsigned short w, unsigned short h,\
						unsigned short w_sub1, unsigned short h_sub1, \
						unsigned short w_sub2, unsigned short h_sub2, \
						enum vsc_feedback_position pos, LX_DE_SCAN_T scan)
{
	int ret = 0;
	unsigned int fr = 0;
	LX_DE_DVR_DISFMT_T param;

	param.id = id;
	param.bOnOff = flag;
	param.h_size = w;
	param.v_size = h;
	param.h_size_sub1 = w_sub1;
	param.v_size_sub1 = h_sub1;
	param.h_size_sub2 = w_sub2;
	param.v_size_sub2 = h_sub2;
	param.scan	 = scan;
#if 0 // TVPLAT-197103
	if(pos > FB_WITHOUT_OSD) { // miracast-tx scenario
		if(h < 720) // 720x480@60Hz
			fr = 60;
		else        // 1280x720@30Hz
			fr = 30;
	}
	else
#endif
	{
		fr = 60; // don't care
	}
	param.fr_rate = fr;
	param.fb_pos = flag?pos:0;

	if(param.bOnOff && ((w > 1920)||( h >1080))) {
		unsigned int c = 8; // alloc ext buffer
		DE_IO_SetSharedMem((unsigned long)&c);
	}
	
	ret = resource_mgr_ioctl(DE_IOW_SET_DVR_FMT_CTRL,(unsigned long)&param,1);

	if(!param.bOnOff) {
		unsigned int c = 7; // free ext buffer
		DE_IO_SetSharedMem((unsigned long)&c);
	}

	DE_NOTI("set venc id(%d) %s(%d) (%dx%d)(%dx%d)(%dx%d) fb_pos(%d) fr(%d) scan(%d)", \
		id, flag?"ON":"OFF", flag, w, h, w_sub1, h_sub1, w_sub2, h_sub2, pos, fr, scan);

	return ret;
}

static int _set_venc_instance(unsigned int id, unsigned short w_id0, unsigned short h_id0, unsigned short w_id1, unsigned short h_id1, unsigned short w_id2, unsigned short h_id2)
{
	int flag = (w_id0+w_id1+w_id2)>0?LX_DE_DVR_FACEBOOK_CHAT:LX_DE_DVR_OFF;
	_venc_control(id, flag, w_id0, h_id0, w_id1, h_id1, w_id2, h_id2, FB_NONE, 1);
	return 0;
}


int vsc_open_info(BOOLEAN flag, UINT8 win, UINT8 open_count)
{
	int ret = 0;
	UINT32 pid;
	LX_DE_INPUT_SOURCE_T src;
	pid = task_tgid_nr(current);
	vsc_config[win].open = (flag)?1:0;

	if(vsc_config[0].socts==1) return ret; // for SOCTSSIC-176197

	// initialize sub path resource
	if(flag == 0 && win == 1 && vsc_config[win].pid==pid) {
		if(vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_VENC)
		{
			memset(&src, 0, sizeof(LX_DE_INPUT_SOURCE_T));
			src.srcId = 2;
			//ret = _venc_control(LX_DE_DVR_OFF, 320, 240, 0, 0, 0, 0, 0, 1);
			ret = _set_venc_instance(0,0,0,0,0,0,0);
			ret = resource_mgr_ioctl(DE_IOW_SET_WIN_PORT_SRC,(unsigned long)&src,1);
			DE_NOTI("release sub-venc resource(srcId:%d)",src.srcId);
		}
	}
	DE_NOTI("win[%d], open_count[%d] pid[%d]", win, open_count, pid);
	return ret;
}

int vsc_init_config(void)
{
	UINT32 i;
	UINT32 is_socts = 0;
	char systemd_opt[24];

	memset(systemd_opt,0,24);
	if (RET_OK==OS_ScanKernelCmdline("systemd.unit=%s", systemd_opt))
	{
		systemd_opt[23] = '\0';
		if (strstr(systemd_opt,"socts.target"))
		{
			is_socts = 1;
		}
	}

	for (i=0; i<LX_DE_WIN_MAX; i++)
	{
		vsc_config[i].socts = is_socts;
	}

	return 0;
}

// start VIDIOC_S_EXT_CTRLS
int vsc_set_input(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_connect_info *p)
{
	int ret = 0;
	LX_DE_INPUT_SOURCE_T src;
	UINT32 vdo_port;
	UINT32 prev_out;

	LX_DE_RECT_T inout_win;
	LX_DE_WIN_INFO_T win_info;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].inout_info, sizeof(struct v4l2_ext_vsc_connect_info));
		//DE_NOTI("Get type[%d] index[%d] out_mode[%d]", p->in.src, p->in.index, p->out);
		return ret;
	}

	if(p->in.src > V4L2_EXT_VSC_INPUT_SRC_FB+1) return -1;
	if(p->in.index > 16) return -2;
	if(p->out > V4L2_EXT_VSC_DEST_AVE) return -3;

	prev_out = vsc_config[win].inout_info.out;
	memset(&vsc_config[win].inout_info, 0, sizeof(struct v4l2_ext_vsc_connect_info));
	memset(&src, 0, sizeof(LX_DE_INPUT_SOURCE_T));
	src.srcId = win;
	vdo_port = win;

	if(p->out == V4L2_EXT_VSC_DEST_VENC) {
		vsc_config[win].pid = task_tgid_nr(current);
		src.srcId = 2; // for ATV rec.
	}
	if(p->in.src == V4L2_EXT_VSC_INPUT_SRC_NONE && prev_out == V4L2_EXT_VSC_DEST_VENC) {
		src.srcId = 2;
		vdo_port = 2;
		vsc_config[win].win_info.out.w = 0;
		vsc_config[win].win_info.out.h = 0;
		//ret = _venc_control(LX_DE_DVR_OFF, 320, 240, 0, 0, 0, 0, 0, 0);
		if(vsc_config[2].win_info.out.w == 0)
			ret = _set_venc_instance(0,0,0,0,0,0,0);
		if(ret) DE_ERROR("set venc error");
	}

	gbufTiming[win].hActive = 0;
	gbufTiming[win].vActive = 0;
	gbufTiming[win].scanType= 0;
	gbufTiming[win].vFreq   = 0;
	gbufTiming[win].svp     = 0;
	 gbufTiming[win].isDSC   = 0;

	switch(p->in.src)
	{
		case V4L2_EXT_VSC_INPUT_SRC_AVD:
			src.srcAttr = p->in.attr;
			if(p->in.attr == 1)
				src.srcType = LX_DE_IN_SRC_CVBS;
			else if(p->in.attr == 0)
				src.srcType = LX_DE_IN_SRC_ATV;
			else
				src.srcType = LX_DE_IN_SRC_NONE;
			break;
		case V4L2_EXT_VSC_INPUT_SRC_ADC:
			src.srcType = LX_DE_IN_SRC_YPBPR;
			break;
		case V4L2_EXT_VSC_INPUT_SRC_HDMI:
			src.srcType = LX_DE_IN_SRC_HDMI;
			src.srcAttr = p->in.index;
			src.hdmiPort = p->in.index;
			ghdmiphyport[win] = p->in.index;
			break;
		case V4L2_EXT_VSC_INPUT_SRC_VDEC:
			src.srcType = LX_DE_IN_SRC_MVI;
			src.srcAttr = win; //set win_id from minor number !!!
			src.hdmiPort = p->in.index;
			if ( lx_chip_rev( ) < LX_CHIP_REV(O24,A0) ) {
				if(win>0)
					vdo_port = 2; //AVTASK-674
			}
			break;
		case V4L2_EXT_VSC_INPUT_SRC_JPEG:
			src.srcType = LX_DE_IN_SRC_CPU;
			//vdo_port = 2;
			break;
		case V4L2_EXT_VSC_INPUT_SRC_FB:
			src.srcType = LX_DE_IN_SRC_FB;
			vdo_port = 0;
			break;
#ifdef V4L2_EXT_VSC_INPUT_SRC_DP
		case V4L2_EXT_VSC_INPUT_SRC_DP:
			DE_NOTI("not support input - DP");
			return -NOT_SUPPORTED;
#endif
		default:
			src.srcType = LX_DE_IN_SRC_NONE;
			vdo_port = 2;
			inout_win.x = 0;
			inout_win.y = 0;
			inout_win.w = 0;
			inout_win.h = 0;
			ret = vp_kwrap_setoutwin((UINT32)(win>1)?(win+1):win,  inout_win);

			memset(&win_info, 0, sizeof(LX_DE_WIN_INFO_T));
			win_info.wId = win;
			if(win == 2) win_info.wId = LX_DE_WIN_3;
			if(win == 3) win_info.wId = LX_DE_WIN_4;
			resource_mgr_ioctl(DE_IOW_SET_WIN_INFO,(unsigned long)&win_info,1);

			DE_NOTI("disconnect & close out window id[%d] (0x0)", (win>1)?(win+1):win);
			break;
	}

	if (lx_chip() == LX_CHIP_M23)
	{
		if (vdo_port == 2)	vdo_port = 1;//not support port 2
	}

	switch(p->out)
	{
		case V4L2_EXT_VSC_DEST_VENC:
			if(p->in.src==V4L2_EXT_VSC_INPUT_SRC_JPEG) {
				src.srcType = LX_DE_IN_SRC_MVI;
				src.srcAttr = win;
				DE_NOTI("cam-venc (%d/%d)", src.srcType, src.srcAttr);
			}
			break;
		case V4L2_EXT_VSC_DEST_DISPLAY:
			//DE_NOTI("##4##Get type[%d] index[%d] out_mode[%d] win[%d] p_out[%d]", p->in.src, p->in.index, p->out, win, p->out);
			if(win == 2) { // for o24 quad window(id=2,3): AVTASK-1038 / AVTASK-1253
				src.srcId = LX_DE_WIN_3;

			}
			if(win == 3) {
				src.srcId = LX_DE_WIN_4;
			}
			break;
		case V4L2_EXT_VSC_DEST_NONE:
			if ((win == 2 || win ==3) && prev_out == V4L2_EXT_VSC_DEST_DISPLAY) {
				src.srcId = (win == 2)? LX_DE_WIN_3:LX_DE_WIN_4;
				DE_NOTI("disconnect win %d -> srcId %d\n",win,src.srcId);
			}
			break;

		case V4L2_EXT_VSC_DEST_MEMORY:
		default:
			break;
	}
	src.srcPort = vdo_port;
#if 1 // SOCTSSIC-52466
	//DE_NOTI("is %s\n",(vsc_config[0].socts==0)? "normal":"socts");
	if (vsc_config[0].socts == 0)
	{
		if(vsc_config[1].win_info.out.w + vsc_config[2].win_info.out.w + vsc_config[3].win_info.out.w > 0 && prev_out == V4L2_EXT_VSC_DEST_VENC)
		{
			if(vsc_config[2].win_info.out.w > 0)
				_set_venc_instance(1, vsc_config[2].win_info.out.w, vsc_config[2].win_info.out.h, 0,0,0,0);
			else {
				_set_venc_instance(0, vsc_config[1].win_info.out.w, vsc_config[1].win_info.out.h, 0,0,0,0);
				ret = resource_mgr_ioctl(DE_IOW_SET_WIN_PORT_SRC,(unsigned long)&src,1);
			}
			DE_NOTI("_set_venc_instance(%d/%d/%d)", vsc_config[1].win_info.out.w, vsc_config[2].win_info.out.w, vsc_config[3].win_info.out.w);

			memcpy(&vsc_config[win].inout_info, p, sizeof(struct v4l2_ext_vsc_connect_info));

			if(vsc_config[win].sub_mode.win_mode != V4L2_EXT_VSC_WIN_MODE_PBP /* QEVENTTWTT-6249 */){
			return 0;
			}
		}
	}
#endif
	ret = resource_mgr_ioctl(DE_IOW_SET_WIN_PORT_SRC,(unsigned long)&src,1);
	if(ret) DE_ERROR("set WIN_PORT_SRC error");

	memcpy(&vsc_config[win].inout_info, p, sizeof(struct v4l2_ext_vsc_connect_info));

#if 1 // SCDCR-694 (sub_mode  setting for 4 hdmi w/a)
	if(win == 3 && src.srcType == LX_DE_IN_SRC_HDMI) {
		UINT32 multi_win = 0, i;
		LX_DE_SUB_MODE_T sub_mode;
		multi_win = 4;
		sub_mode = 11;
		ret = resource_mgr_ioctl(DE_IOW_SET_SUB_MODE,(unsigned long)&sub_mode,1);
		ret = resource_mgr_ioctl(DE_IOW_MULTI_WIN_ENABLE,(unsigned long)&multi_win,1);		
		for(i=0;i<4;i++) {
			src.srcType = LX_DE_IN_SRC_HDMI;
			src.srcAttr = ghdmiphyport[i];
			src.hdmiPort = ghdmiphyport[i];
			ret = resource_mgr_ioctl(DE_IOW_SET_WIN_PORT_SRC,(unsigned long)&src,1);
		}
		DE_NOTI("Force quad video mode");
	}
#endif

	DE_NOTI("win[%d] src[%d] index[%d] attr[%d] out[%d] vdop[%d] pid[%d]", \
		win, p->in.src, p->in.index, p->in.attr, p->out, vdo_port, vsc_config[win].pid);

	vp_kwrap_getpicsrcinfo(win, src.srcType);

#ifdef USE_BRINGUP_CMD
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
	{
		__run_bringup_cmd(0, 0);
	}
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		__run_bringup_cmd(0, 0);
	}

#endif

	if (win == 0)
	{
		struct vsc_bwm_cfg bwm_cfg;
		bwm_cfg.input = p->in.src;
		vsc_bwm_set_config(VSC_BWM_OPT_INPUT, &bwm_cfg);
	}

#ifdef INCLUDE_KDRV_OVI
	if (win == 0) {
		struct ovi_clk_ctrl clk_ctrl;
		clk_ctrl.type = OVI_CRG_CTRL_TYPE_SRC;
		if (p->in.src == V4L2_EXT_VSC_INPUT_SRC_VDEC) {
			clk_ctrl.src = OVI_CRG_CTRL_SRC_VDEC;
		} else if (p->in.src == V4L2_EXT_VSC_INPUT_SRC_HDMI) {
			clk_ctrl.src = OVI_CRG_CTRL_SRC_HDMI;
		} else if (p->in.src == V4L2_EXT_VSC_INPUT_SRC_NONE) {
			clk_ctrl.src = OVI_CRG_CTRL_SRC_NONE;
		} else {
			clk_ctrl.src = OVI_CRG_CTRL_SRC_ETC;
		}
		ovi_hal_clk_ctrl(&clk_ctrl);
	}
#endif

	return ret;
}

int vsc_set_aspectratio_policy(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_aspectratio_policy *p)
{
	int ret = 0;
	LX_DE_WIN_INFO_T win_info;
	struct v4l2_ext_video_rect calculated_input_rect, in_res;
	struct v4l2_ext_video_rect calculated_output_rect, out_win;
	LX_DE_SRC_STATUS_T srcStatus;
	int count = 0;
	srcStatus.win_id = win;
	srcStatus.status_type = LX_DE_SRC_STATUS_VDEC_INFO;
	srcStatus.inSrc[0] = 0;
	srcStatus.inSrcPort[win] = win;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].aspectratio_policy, sizeof(struct v4l2_ext_vsc_aspectratio_policy));
		return ret;
	}
	memcpy(&vsc_config[win].aspectratio_policy, p, sizeof(struct v4l2_ext_vsc_aspectratio_policy));
	do {
		count++;
		ret = de_kwrap_getsourcestatus(&srcStatus);

		in_res.x = in_res.y = 0;
		in_res.w = srcStatus.vdecInfo.h_size;
		in_res.h = srcStatus.vdecInfo.v_size;
		out_win.x = /*p->out.x;*/vsc_config[win].aspectratio_policy.out.x;
		out_win.y = /*p->out.y;*/vsc_config[win].aspectratio_policy.out.y;
		out_win.w = /*p->out.w;*/vsc_config[win].aspectratio_policy.out.w;
		out_win.h = /*p->out.h;*/vsc_config[win].aspectratio_policy.out.h;
		if(in_res.w == 0 || in_res.h == 0){
			DE_ERROR("win[%d] no input[%d/%d] count[%d]",win, in_res.w, in_res.h, count);
			msleep(10);
			if(count > 3)break;
			continue;
		}
		srcStatus.vdecInfo.par_width = (srcStatus.vdecInfo.par_width==0)?1:srcStatus.vdecInfo.par_width;
		srcStatus.vdecInfo.par_height = (srcStatus.vdecInfo.par_height==0)?1:srcStatus.vdecInfo.par_height;
		DE_NOTI("win[%d] out[%dx%d] justscan[%d], aspect_ratio[%d] rotate[%d] : afd[%d]par[%dx%d]", win, out_win.w, \
			out_win.h, vsc_config[win].aspectratio_policy.setting_policy.just_scan, vsc_config[win].aspectratio_policy.setting_policy.aspect_ratio, \
			vsc_config[win].aspectratio_policy.setting_policy.rotate, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height);

#ifdef VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
		vsc_AspectratioCallbackFp = (ASPECTRATIO_CALLBACK_T *)vsc_getAspectratioCallbackFp();
		if(vsc_AspectratioCallbackFp == NULL)  {DE_ERROR("pfn is NULL");return -1;}
		ret = vsc_AspectratioCallbackFp->pfnAspectratiodrvCalculate(in_res, out_win, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height, \
			vsc_config[win].aspectratio_policy.system_policy, vsc_config[win].aspectratio_policy.setting_policy, &calculated_input_rect, &calculated_output_rect);
		if(ret) {
			DE_ERROR("return error from ext library(aspectratiodrvCalculateWindow)");
			return -1;
		}
		memcpy(&vsc_config[win].calculated_input_rect, &calculated_input_rect, sizeof(struct v4l2_ext_video_rect));
		memcpy(&vsc_config[win].calculated_output_rect, &calculated_output_rect, sizeof(struct v4l2_ext_video_rect));
#endif

		DE_NOTI("system_policy.out=[%d/%d/%d/%d]", out_win.x,out_win.y, out_win.w, out_win.h);

		win_info.in_size.x = 0;
		win_info.in_size.y = 0;
		win_info.in_size.w = srcStatus.vdecInfo.h_size;
		win_info.in_size.h = srcStatus.vdecInfo.v_size;;

		win_info.in_win.x = calculated_input_rect.x;
		win_info.in_win.y = calculated_input_rect.y;
		win_info.in_win.w = calculated_input_rect.w;
		win_info.in_win.h = calculated_input_rect.h;

		win_info.out_win.x = calculated_output_rect.x;
		win_info.out_win.y = calculated_output_rect.y;
		win_info.out_win.w = calculated_output_rect.w;
		win_info.out_win.h = calculated_output_rect.h;
		win_info.wId = win;
		win_info.rot = 0;
		win_info.resize_ani_flag = 0;
#if 1
		if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
			win_info.wId = LX_DE_WIN_3;
		if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
			win_info.wId = LX_DE_WIN_4;

		resource_mgr_ioctl(DE_IOW_SET_WIN_INFO,(unsigned long)&win_info,1);
		DE_NOTI("SET_WIN_INFO ipc : src %dx%d , in win=%dx%d(%d,%d) , out win=%dx%d(%d,%d)", \
			win_info.in_size.w, win_info.in_size.h,\
			win_info.in_win.w, win_info.in_win.h, win_info.in_win.x, win_info.in_win.y,\
			win_info.out_win.w, win_info.out_win.h, win_info.out_win.x, win_info.out_win.y);
#endif
		break;
	}while(1);
	return ret;
}
//#endif

int vsc_set_win_info(BOOLEAN flag, UINT8 win, UINT8 ani, struct v4l2_ext_vsc_win_region *p)
{
	int ret = 0;
	LX_DE_WIN_INFO_T win_info;
	LX_DE_RECT_T inout_win;
	int count = 0;

//#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
	struct v4l2_ext_video_rect calculated_input_rect, in_res;
	struct v4l2_ext_video_rect calculated_output_rect, out_win;
	LX_DE_SRC_STATUS_T srcStatus;
	srcStatus.win_id = win;
	srcStatus.status_type = LX_DE_SRC_STATUS_VDEC_INFO;
	srcStatus.inSrc[0] = 0;
	srcStatus.inSrcPort[win] = win;	
//#endif
	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].win_info, sizeof(struct v4l2_ext_vsc_win_region));
		return ret;
	}

	if(p->rotation >= 7) return -1;

	memcpy(&vsc_config[win].win_info, p, sizeof(struct v4l2_ext_vsc_win_region));
	memset(&win_info, 0, sizeof(LX_DE_WIN_INFO_T));

	win_info.wId = win;
	win_info.rot = (LX_DE_ROTATE_INFO_T)p->rotation;
	win_info.in_size.w = p->in.res.w;
	win_info.in_size.h = p->in.res.h;
	win_info.in_win.x  = p->in.crop.x;
	win_info.in_win.y  = p->in.crop.y;
	win_info.in_win.w  = p->in.crop.w;
	win_info.in_win.h  = p->in.crop.h;
	win_info.out_win.x = p->out.x;
	win_info.out_win.y = p->out.y;
	win_info.out_win.w = p->out.w;
	win_info.out_win.h = p->out.h;
	win_info.resize_ani_flag = (vsc_config[win].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_HDMI)?0:ani; // modify for https://harmony.lge.com:8443/issue/browse/SICBIT-5073
	if(vsc_config[win].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_VDEC || vsc_config[win].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_JPEG) {
		win_info.resize_ani_flag = (vsc_config[win].sub_occupied)?0:ani; // http://hlm.lge.com/issue/browse/TVPLAT-530312
	}
	if((vsc_config[win].seamless == 0) || (win > 0) || (vsc_config[1].sub_mode.win_mode > 0/*SDOSTE-323*/))
		win_info.resize_ani_flag = 0; // SICBIT-9085 , SICDTV-16102

	// call DARC libracy (external *.ko from HE lab)
//#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
	if(vsc_config[win].seamless == 2) {
		do {
			count++;
			srcStatus.inSrcPort[0] = win;
			ret = de_kwrap_getsourcestatus(&srcStatus);

			in_res.x = in_res.y = 0;
			in_res.w = srcStatus.vdecInfo.h_size;
			in_res.h = srcStatus.vdecInfo.v_size;
			out_win.x = vsc_config[win].aspectratio_policy.out.x;
			out_win.y = vsc_config[win].aspectratio_policy.out.y;
			out_win.w = vsc_config[win].aspectratio_policy.out.w;
			out_win.h = vsc_config[win].aspectratio_policy.out.h;
			if(in_res.w == 0 || in_res.h == 0){
				DE_ERROR("win[%d] no input[%d/%d] count[%d]",win, in_res.w, in_res.h, count);
				msleep(10);
				if(count > 3)break;
				continue;
			}

			srcStatus.vdecInfo.par_width = (srcStatus.vdecInfo.par_width==0)?1:srcStatus.vdecInfo.par_width;
			srcStatus.vdecInfo.par_height = (srcStatus.vdecInfo.par_height==0)?1:srcStatus.vdecInfo.par_height;
			DE_NOTI("system_policy.out[%dx%d] justscan[%d], aspect_ratio[%d] rotate[%d] : afd[%d]par[%dx%d]", out_win.w, \
				out_win.h, vsc_config[win].aspectratio_policy.setting_policy.just_scan, vsc_config[win].aspectratio_policy.setting_policy.aspect_ratio, \
				vsc_config[win].aspectratio_policy.setting_policy.rotate, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height);
#ifdef VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
			vsc_AspectratioCallbackFp = (ASPECTRATIO_CALLBACK_T *)vsc_getAspectratioCallbackFp();
			if(vsc_AspectratioCallbackFp == NULL)  {DE_ERROR("pfn is NULL");return -1;}
			ret = vsc_AspectratioCallbackFp->pfnAspectratiodrvCalculate(p->in.res, out_win, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height, \
				vsc_config[win].aspectratio_policy.system_policy, vsc_config[win].aspectratio_policy.setting_policy, &calculated_input_rect, &calculated_output_rect);
			if(ret) {
				DE_ERROR("return error from ext library(aspectratiodrvCalculateWindow)");
				return -1;
			}
			else {
				memcpy(&vsc_config[win].calculated_input_rect, &calculated_input_rect, sizeof(struct v4l2_ext_video_rect));
				memcpy(&vsc_config[win].calculated_output_rect, &calculated_output_rect, sizeof(struct v4l2_ext_video_rect));

				win_info.in_win.x = calculated_input_rect.x;
				win_info.in_win.y = calculated_input_rect.y;
				win_info.in_win.w = calculated_input_rect.w;
				win_info.in_win.h = calculated_input_rect.h;

				win_info.out_win.x = calculated_output_rect.x;
				win_info.out_win.y = calculated_output_rect.y;
				win_info.out_win.w = calculated_output_rect.w;
				win_info.out_win.h = calculated_output_rect.h;
			}
			DE_NOTI("calculated window in[%dx%d:%d,%d] out[%dx%d:%d,%d]", win_info.in_win.w, win_info.in_win.h, win_info.in_win.x, win_info.in_win.y, \
				win_info.out_win.w, win_info.out_win.h, win_info.out_win.x,win_info.out_win.y);
			break;
		}while(1);
//#endif
	}
	else {
		DE_NOTI("no darc");
	}
#else
//	if(vsc_config[0].seamless == 2) {
//		ret = vsc_external_library(0, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height, &win_info);
//	}
#endif
	inout_win.x = win_info.in_win.x;
	inout_win.y = win_info.in_win.y;
	inout_win.w = win_info.in_win.w;
	inout_win.h = win_info.in_win.h;
	ret = vp_kwrap_setinputwin((UINT32)win,  inout_win);
	inout_win.x = win_info.out_win.x;
	inout_win.y = win_info.out_win.y;
	inout_win.w = win_info.out_win.w;
	inout_win.h = win_info.out_win.h;
	ret = vp_kwrap_setoutwin((UINT32)win,  inout_win);

	if(vsc_config[win].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_FB) {
		LX_DE_SCAN_T scan_type ;
		if(p->rotation>1)
			scan_type = LX_DE_PROGRESSIVE;
		else
			scan_type = (LX_DE_SCAN_T)p->rotation;
		_venc_control(0, LX_DE_DVR_MIRACAST_TX, p->out.w, p->out.h, 0, 0, 0, 0, vsc_config[0].pos, scan_type);
	}
	else if(win > 0 && \
			vsc_config[1].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_JPEG && \
			vsc_config[1].inout_info.out == V4L2_EXT_VSC_DEST_VENC) {
		unsigned short w,h, w_s1, h_s1, w_s2, h_s2;
		w   = vsc_config[1].win_info.out.w;
		h   = vsc_config[1].win_info.out.h;
		w   = vsc_config[2].win_info.out.w?vsc_config[2].win_info.out.w:w;
		h   = vsc_config[2].win_info.out.h?vsc_config[2].win_info.out.h:h;
		w_s1 = vsc_config[2].win_info.out.w;
		h_s1 = vsc_config[2].win_info.out.h;
		w_s2 = 0; //vsc_config[3].win_info.out.w;
		h_s2 = 0; //vsc_config[3].win_info.out.h;
		vsc_set_fbpos(FB_NONE);
		_venc_control((win>>1), LX_DE_DVR_FACEBOOK_CHAT, w, h, w_s1, h_s1, w_s2, h_s2, vsc_config[0].pos, 1);
	}
	else {
		if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
			win_info.wId = LX_DE_WIN_3;
		if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
			win_info.wId = LX_DE_WIN_4;
		ret = resource_mgr_ioctl(DE_IOW_SET_WIN_INFO,(unsigned long)&win_info,1);
	}

	DE_NOTI("wId[%d] : Rot[%d] size[%dx%d] In[%dx%d(%d,%d)] Out[%dx%d(%d,%d)] VENC[%d] Ani[%d]", \
		win, win_info.rot, \
		win_info.in_size.w, win_info.in_size.h, \
		win_info.in_win.w, win_info.in_win.h, win_info.in_win.x, win_info.in_win.y,  \
		win_info.out_win.w, win_info.out_win.h, win_info.out_win.x, win_info.out_win.y,\
		(vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_VENC)?1:0, win_info.resize_ani_flag);

#ifdef USE_BRINGUP_CMD
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
	{
		__run_bringup_cmd(1, p->in.res.w);
	}
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		__run_bringup_cmd(1, p->in.res.w);
	}
#endif
	return ret;
}

#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
#ifndef V4L2_EXT_VSC_WIN_MODE_HDR2SDR
#define V4L2_EXT_VSC_WIN_MODE_HDR2SDR	9
#endif
#endif

int vsc_set_sub_mode(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_win_prop *p)
{
	int ret = 0;
	UINT32 win_mode;
	LX_DE_SUB_MODE_T sub_mode;
	UINT32 multi_win = 0;
#ifdef INCLUDE_KDRV_PE
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
	LX_PE_DEFAULT_SETTINGS_T dflt_param;
#endif
	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].sub_mode, sizeof(struct v4l2_ext_vsc_win_prop));
		return ret;
	}
#if 0 // 20220818 remove w/a of sub mode mask(QEVENTTWTT-238)
	if(p->win_mode == 3 || p->win_mode == 4)
		vsc_config[0].keep_submode = p->win_mode;

	if((vsc_config[0].keep_submode == 3) && (p->win_mode==V4L2_EXT_VSC_WIN_MODE_NONE)) {
		DE_NOTI("set win_mode = PipMaskOn, QEVENTTWON-7354");
		return 0;
	}
	else if(vsc_config[0].keep_submode == 4) {
		sub_mode = LX_DE_SUB_MODE_NONE;
		resource_mgr_ioctl(DE_IOW_SET_SUB_MODE,(unsigned long)&sub_mode,1);
		vsc_config[0].keep_submode = 0;
		DE_NOTI("set win_mode = PipMaskOff");
	}
#endif // #if 0
	if(p->win_mode > 9) return -1; // max win_mode = 4(PipMaskOff)
	if(p->mirror_mode > V4L2_EXT_VSC_MIRROR_MODE_OFF) return -1;
	if(p->mem_type > V4L2_EXT_VSC_MEMORY_TYPE_MULTI) return -1;

	memcpy(&vsc_config[win].sub_mode, p, sizeof(struct v4l2_ext_vsc_win_prop));
	memset(&sub_mode, 0, sizeof(LX_DE_SUB_MODE_T));

	win_mode = p->win_mode;
	switch(win_mode)
	{
		case V4L2_EXT_VSC_WIN_MODE_PBP :
			multi_win = 2;
			sub_mode = LX_DE_SUB_MODE_PBP;//LX_DE_SUB_MODE_PBP;
			break;
		case V4L2_EXT_VSC_WIN_MODE_PIP :
			multi_win = 1;
			if(p->mirror_mode == V4L2_EXT_VSC_MIRROR_MODE_ON && p->mem_type == V4L2_EXT_VSC_MEMORY_TYPE_MULTI)
			{
				sub_mode = LX_DE_SUB_MODE_LIVEZOOM; // live zoom
			}
			else if(p->mirror_mode == V4L2_EXT_VSC_MIRROR_MODE_ON && p->mem_type == V4L2_EXT_VSC_MEMORY_TYPE_SINGLE)
			{
				sub_mode = LX_DE_SUB_MODE_MAGZOOM; // magnifier
			}
			else if(p->mirror_mode == V4L2_EXT_VSC_MIRROR_MODE_OFF && p->mem_type == V4L2_EXT_VSC_MEMORY_TYPE_MULTI)
			{
				sub_mode = LX_DE_SUB_MODE_PIP; // overlay miracast
			}
			else
			{
				sub_mode = LX_DE_SUB_MODE_NONE;
			}
			break;
		case 3 :
			#if 0
			// skip set sub_mode
			DE_NOTI("skip set sub_mode[%d]", p->win_mode);
			return 0;
			#else
			if(p->mirror_mode == V4L2_EXT_VSC_MIRROR_MODE_OFF && p->mem_type == V4L2_EXT_VSC_MEMORY_TYPE_MULTI)
			{
				sub_mode = LX_DE_SUB_MODE_PBP; // Dual monitor(SCDCR-5190, AVTASK-962)
			}
			#endif
			break;
		#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
		case V4L2_EXT_VSC_WIN_MODE_HDR2SDR :
			multi_win = 2;
			sub_mode = LX_DE_SUB_MODE_HDR2SDR;
			break;
		#endif
		default :
			sub_mode = LX_DE_SUB_MODE_NONE;
			break;
	}
	if(vsc_config[win].sub_occupied == (BOOLEAN)1 && sub_mode == LX_DE_SUB_MODE_NONE) {
		sub_mode = LX_DE_SUB_MODE_OCCUPIED; //  SCDCR-5536
	}

	ret = resource_mgr_ioctl(DE_IOW_SET_SUB_MODE,(unsigned long)&sub_mode,1);

	ret |= resource_mgr_ioctl(DE_IOW_MULTI_WIN_ENABLE,(unsigned long)&multi_win,1);

	DE_NOTI("[win:%d] Sub mode [%d] - 0:none, 1:pip, 2:pbp",win,sub_mode);

#ifdef INCLUDE_KDRV_PE
	cur_inf_param.win_id = dflt_param.win_id= win;
	/* get pre display info */
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	cur_inf_param.info_type = LX_PE_INFO_MISC;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	/**
	* causion, these items only in this function :
	* mul_win
	*/
	cur_inf_param.mul_win = (UINT32)multi_win;
	cur_inf_param.sub_mode= (UINT32)sub_mode;
	//DE_NOTI("pe Sub mode[%d] pre:%d cur:%d", dflt_param.win_id,pre_inf_param.sub_mode,sub_mode);
	/* set default */
	if (pre_inf_param.mul_win != cur_inf_param.mul_win || \
		pre_inf_param.sub_mode != cur_inf_param.sub_mode)
	{
 		/* set disp info */
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		ret = vpq_hwrap_setdefaultsettings((void *)&dflt_param);
 	}
#endif
	return ret;
}

/* LX_DE_ZLIST_T zlist;
BOOLEAN enable; 			///< z-list on/off (off : hw default order, win0-bottom/win1-top)
UINT32 z_list[2];			///< index : order(0->top, 1->bottom) , value : win_id
UINT32 alpha[2];			///< index : order(0->top, 1->bottom) , value : blending alpha */
/* struct v4l2_ext_vsc_zorder *p     /// SCDCR-1607 (2018/07/06)
win;                                     ///< window id
zorder;                                ///< 0 : bottom , 1: top
alpha;                                  ///< value */
/* echo 4 1 0 1 255 > /proc/lg/de/v4l2_vsc_debug_func // main : top , alpha : 255
     echo 4 1 1 0 100 > /proc/lg/de/v4l2_vsc_debug_func // sub   : bot , alpha : 100
     echo 4 1 0 0 0    > /proc/lg/de/v4l2_vsc_debug_func // main : bot , alpha : 0
     echo 4 1 1 1 0    > /proc/lg/de/v4l2_vsc_debug_func // sub   : top , alpha : 0 */
static LX_DE_ZLIST_T zlist = { 0 };
int vsc_set_zorder(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_zorder *p)
{
	int ret = 0;
#ifdef INCLUDE_KDRV_PE
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
#endif

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].order, sizeof(struct v4l2_ext_vsc_zorder));
		return ret;
	}

	memcpy(&vsc_config[win].order, p, sizeof(struct v4l2_ext_vsc_zorder));

	if(p->zorder > 1) // for negative TC (SOCTSSIC-185503)
	{
		DE_ERROR("invalid order value %d", p->zorder);
		return -1;
	}

	if(win) {
		zlist.z_list[1] = 1;
		zlist.z_list[0] = 0;
		zlist.alpha[1]	= vsc_config[0].order.alpha;
	}

	zlist.enable = TRUE;

	if(win > 1) {DE_NOTI("mask win[%d]\n", win); return 0;}

	if(p->zorder == 1)
	{
		zlist.z_list[0] = win;
		zlist.z_list[1] = (win==0)?1:0;
		zlist.alpha[0]	= p->alpha;
	}
	else if(p->zorder == 0)
	{
		zlist.z_list[1] = win;
		zlist.z_list[0] = (win==0)?1:0;
		zlist.alpha[1]	= p->alpha;
	}

#ifdef INCLUDE_KDRV_PE
	if(win <0x2)
	{
		cur_inf_param.win_id = win;
		/* get pre display info */
		ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
		cur_inf_param.info_type = LX_PE_INFO_ZORDER;
		memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
		cur_inf_param.zoder[0] = (UINT32)zlist.z_list[0];
		cur_inf_param.zoder[1] = (UINT32)zlist.z_list[1];
		if (pre_inf_param.zoder[0] != cur_inf_param.zoder[0]||\
			pre_inf_param.zoder[1] != cur_inf_param.zoder[1])
		{
			/* set disp info */
			ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		}
	}
#endif
	DE_NOTI("win[%d] zorder[%s] alpha[%d]", win, p->zorder==0?"BOT":"TOP", p->alpha);
	/*if(win)*/ { // update after set win_1  :   SCDCR-1607 (2018/07/06 16:01)
		ret = resource_mgr_ioctl(DE_IOW_SET_ZLIST,(unsigned long)&zlist,1);
		DE_NOTI("z_list[0:top]=win_%d, z_list[1:bot]=win_%d, alpha[0:top]=%d, alpha[1:bot]=%d",\
			zlist.z_list[0], zlist.z_list[1], zlist.alpha[0], zlist.alpha[1]);
	}

	return ret;
}

int vsc_set_zorder_info(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_zorder_info *p)
{
	int ret = 0;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].order, sizeof(struct v4l2_ext_vsc_zorder_info));
		return ret;
	}

	memcpy(&vsc_config[win].zorder_info, p, sizeof(struct v4l2_ext_vsc_zorder_info));

	if(p->z[0].zorder == p->z[1].zorder)
	{
		DE_NOTI("invalid zorder [%d:%d]", p->z[0].zorder, p->z[1].zorder);
		//return -1;
		p->z[1].zorder = (p->z[0].zorder==1)?0:1;
	}

	zlist.enable = TRUE;

	zlist.z_list[0] = p->z[0].zorder;
	zlist.z_list[1] = (p->z[0].zorder == 1)?0:1;
	zlist.alpha[0]	= p->z[0].alpha;
	zlist.alpha[1]	= p->z[1].alpha;
	ret = resource_mgr_ioctl(DE_IOW_SET_ZLIST,(unsigned long)&zlist,1);
	DE_NOTI("z_list[0:top]=win_%d, z_list[1:bot]=win_%d, alpha[0:top]=%d, alpha[1:bot]=%d",\
			zlist.z_list[0], zlist.z_list[1], zlist.alpha[0], zlist.alpha[1]);
	return ret;
}

int vsc_set_latency_pattern(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_latency_pattern_info *p)
{
	int ret = 0;
	LX_DE_LATENCY_MEASURE_T l_pat;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].lag_pat, sizeof(struct v4l2_ext_vsc_latency_pattern_info));
		return ret;
	}

	memcpy(&vsc_config[win].order, p, sizeof(struct v4l2_ext_vsc_zorder));

	// check - how do i know on/off value from this patameter
	if(p->r.w != 0 || p->r.h)
		l_pat.bOnOff = 1;
	else
		l_pat.bOnOff = 0;

	l_pat.color = (p->p==V4L2_EXT_VSC_PATTERN_BLACK)?0:1;
	l_pat.rect.x = p->r.x;
	l_pat.rect.y = p->r.y;
	l_pat.rect.w = p->r.w;
	l_pat.rect.h = p->r.h;

	ret = resource_mgr_ioctl(DE_IOW_SET_LATENCY_MEASURE,(unsigned long)&l_pat,1);

	DE_NOTI("Latency measure  color[%d], rect[%dx%d]", l_pat.color, l_pat.rect.w, l_pat.rect.h);

	return ret;
}

int vsc_set_quad_mode(BOOLEAN flag, UINT8 win, unsigned int *p)
{
	int ret = 0;
	LX_DE_SUB_MODE_T param;
#ifdef INCLUDE_KDRV_PE
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
#endif

	if(!p) return -1;

	if(!flag)//get
	{
		//
		return ret;
	}

	switch(*p)
	{
		case 1:
			param = LX_DE_SUB_MODE_QUADWIN;
			break;
		case 2:
			param = LX_DE_SUB_MODE_TRIWIN;
			break;
		case 0:
		default:
			param = LX_DE_SUB_MODE_NONE;
			break;			
	}

	ret = resource_mgr_ioctl(DE_IOW_SET_SUB_MODE,(unsigned long)&param,1);

	DE_NOTI("sub_mode[%d]  0(none),1(quad),2(tri)", param);
#ifdef INCLUDE_KDRV_PE
		cur_inf_param.win_id = win;
		/* get pre display info */
		ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
		cur_inf_param.info_type = LX_PE_INFO_MISC;
		memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
		/**
		* causion, these items only in this function :
		* mul_win
		*/
		cur_inf_param.sub_mode= (UINT32)param;
		/* set default */
		if (pre_inf_param.sub_mode != cur_inf_param.sub_mode)
		{
			/* set disp info */
			ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		}
#endif

	return ret;
}

int vsc_set_vdo_mode(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_vdo_mode *p)
{
	int ret = 0;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].vdo_mode, sizeof(struct v4l2_ext_vsc_vdo_mode));
		return ret;
	}

	memcpy(&vsc_config[win].vdo_mode, p, sizeof(struct v4l2_ext_vsc_vdo_mode));


	//ret = resource_mgr_ioctl(DE_IOW_SET_VDO_MODE,(unsigned long)&vdo_info,1);
	// call vdec api
	// call pe api

	DE_NOTI("vdo_mode  vdo[%d], vdec[%d]", p->vdo_port, p->vdec_port);

	return ret;

}

int vsc_set_read_cvi_pixel(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_pixel_color_info *p)
{
	int ret = 0;
	LX_DE_CVI_RW_VIDEO_FRAME_T cvi_video_frame_buffer;

	if(!p) return -1;

	if(flag)//set
	{
		DE_ERROR("not support");
		return ret;
	}
	p->format = V4L2_EXT_VSC_COLOR_PIXEL_FORMAT_YUV;
	p->depth  = V4L2_EXT_VSC_COLOR_PIXEL_10BIT;

	cvi_video_frame_buffer.region.win_id = 0;
	cvi_video_frame_buffer.region.pixelGrabX = (unsigned int)p->r.x;
	cvi_video_frame_buffer.region.pixelGrabY = (unsigned int)p->r.y;
	cvi_video_frame_buffer.region.pixelGrabW = (unsigned int)p->r.w;
	cvi_video_frame_buffer.region.pixelGrabH = (unsigned int)p->r.h;
	cvi_video_frame_buffer.bReadOnOff = TRUE;
	cvi_video_frame_buffer.color = (LX_DE_GRAB_COLOR_T	*)p->p_data;

	// KADP_DE_Read_CviVideoFrameBuffer_4K
	ret = _vsc_read_cvi_pixel(cvi_video_frame_buffer, 0);

	return ret;
}

// end VIDIOC_S_EXT_CTRLS


// start VIDIOC_S_CTRL
int vsc_set_mute(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_SET_WIN_BLANK_T mute;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].mute, sizeof(enum v4l2_ext_vsc_win_color));
		return ret;
	}

	memcpy(&vsc_config[win].mute, p, sizeof(enum v4l2_ext_vsc_win_color));

	memset(&mute, 0, sizeof(LX_DE_SET_WIN_BLANK_T));
	mute.win_id = win;
	mute.bEnable = (*p)?1:0;
	mute.isRGB = 0;
	if(*p==1)//black
	{
		mute.win_color.r = 128;
		mute.win_color.g =	 0;
		mute.win_color.b = 128;
	}
	else if(*p==2)//blue
	{
		mute.win_color.r = 120;
		mute.win_color.g =	28;
		mute.win_color.b = 212;
	}
	else if(*p==3)//gray
	{
		mute.win_color.r = 128;
		mute.win_color.g = 128;
		mute.win_color.b = 128;
	}
	else
	{
		mute.win_color.r = 128;
		mute.win_color.g =	 0;
		mute.win_color.b = 128;
	}
	if(*p > 3) return -1;

	DE_NOTI("Mute win[%d] %d", mute.win_id, mute.bEnable);

	if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		mute.win_id = LX_DE_WIN_3;
	if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		mute.win_id = LX_DE_WIN_4;
	ret = resource_mgr_ioctl(DE_IOW_SET_WIN_BLANK,(unsigned long)&mute,1);

#ifdef INCLUDE_KDRV_PE
	KWRAP_PE_SetMuteInfo((unsigned int)win, (unsigned int)(*p));
#endif

	return ret;
}

int vsc_set_freeze(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	//BOOLEAN *pFreeze = &vsc_config[win].freeze;
	LX_DE_WIN_FREEZE_T freeze;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].freeze, sizeof(BOOLEAN));
		return ret;
	}

	if(*p < 0 || *p > 1) return -1;
	vsc_config[win].freeze = (BOOLEAN)*p;

	freeze.win_id = win;
	freeze.bEnable = (BOOLEAN)*p;
	freeze.location = LX_DE_FREEZE_DISP;

	ret = resource_mgr_ioctl(DE_IOW_SET_WIN_FREEZE,(unsigned long)&freeze,1);

	return ret;
}

int vsc_set_pattern(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_PATTERN_T pattern;
	LX_DE_SET_DBG_T stParams;
	int i = 0;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].pat, sizeof(enum v4l2_ext_vsc_pattern));
		return ret;
	}

	vsc_config[win].pat = (enum v4l2_ext_vsc_pattern)*p;

	stParams.win_id = pattern.win_id = win;
	pattern.bOnOff = (*p>0)?1:0;
	switch(*p)
	{
		case V4L2_EXT_VSC_PATTERN_MUX:
			pattern.location = LX_DE_PAT_INPUT;
			break;
		case V4L2_EXT_VSC_PATTERN_DI_NR:
			pattern.location = LX_DE_PAT_ND;
			break;
		case V4L2_EXT_VSC_PATTERN_SCALER:
			pattern.location = LX_DE_PAT_SRE;
			break;
		case V4L2_EXT_VSC_PATTERN_MEMC:
			pattern.location = LX_DE_PAT_WCP;
			break;
		case V4L2_EXT_VSC_PATTERN_DISPLAY:
			pattern.location = LX_DE_PAT_LED;
			break;
		default:
			pattern.bOnOff = 0;
			break;
	}

	if(pattern.bOnOff == 0)
	{
		for(i=0;i<=LX_DE_PAT_LED;i++)
		{
			pattern.location = i;
			memcpy(&stParams.pattern, &pattern, sizeof(pattern));
			ret = resource_mgr_ioctl(DE_IOW_SET_PATTERN,(unsigned long)&stParams,1);
		}
	}
	else
	{
		memcpy(&stParams.pattern, &pattern, sizeof(pattern));
		ret = resource_mgr_ioctl(DE_IOW_SET_PATTERN,(unsigned long)&stParams,1);
	}

	DE_NOTI("Pattern onoff[%d] loc[%d]", pattern.bOnOff, pattern.location);

	return ret;
}


int vsc_set_scanmode(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_SCAN_MODE_T stParams;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].scan_mode, sizeof(enum v4l2_ext_vsc_scan_mode));
		return ret;
	}

	vsc_config[win].scan_mode = (enum v4l2_ext_vsc_scan_mode)*p;
	stParams.wId=  win;
	memcpy(&stParams.scan_mode, p, sizeof(enum v4l2_ext_vsc_scan_mode));
	ret = resource_mgr_ioctl(DE_IOW_SET_SCAN_MODE,(unsigned long)&stParams,1);
	DE_NOTI("Scan mode[%d]: %d", stParams.wId, stParams.scan_mode);

	return ret;
}


int vsc_set_frame_delay(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_SET_DELAY_BUFFER_T f_delay;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].frame_delay, sizeof(UINT32));
		return ret;
	}

	if(*p < 0 || *p > 5) return -1;

	vsc_config[win].frame_delay = (UINT32)*p;

	f_delay.win_id = win;
	f_delay.ubuffer = (UINT32)*p;

	ret = resource_mgr_ioctl(DE_IOW_SET_FRAME_DELAY,(unsigned long)&f_delay,1);

	DE_NOTI("Frame delay [%d]", f_delay.ubuffer);

	return ret;
}

int vsc_set_adaptives_stream(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_ACT_FORMAT_T seamless_info;
#ifdef INCLUDE_KDRV_PE
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
	LX_PE_DEFAULT_SETTINGS_T dft_param;
#endif

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].seamless, sizeof(BOOLEAN));
		return ret;
	}

	if(*p > 2) return -1;

	vsc_config[win].seamless = (BOOLEAN)*p;

	seamless_info.win_id = win;
	seamless_info.enable = *p;

	if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		seamless_info.win_id = LX_DE_WIN_3;
	if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		seamless_info.win_id = LX_DE_WIN_4;

	ret = resource_mgr_ioctl(DE_IOW_SET_ACT_FMT_DETECT,(unsigned long)&seamless_info,1);

	DE_NOTI("Seamless flag  win_id[%d] - on/off[%d]", win, *p);
	
#ifdef INCLUDE_KDRV_PE
	/* get pre display info */
	cur_inf_param.win_id = win;
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	cur_inf_param.info_type = LX_PE_INFO_MISC;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	cur_inf_param.act_fmt = (UINT32)*p;
	/* set default */
	if (pre_inf_param.act_fmt != cur_inf_param.act_fmt)
	{
		/* set display info */
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		/* set default settings */
		dft_param.win_id = cur_inf_param.win_id;
		ret = vpq_hwrap_setdefaultsettings((void *)&dft_param);
	}
#endif
	return ret;
}

int vsc_set_rgb444(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_HDMI444_MODE_T hdmi444;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].rgb444, sizeof(BOOLEAN));
		return ret;
	}
	if(*p > 1) return -1;
	vsc_config[win].rgb444 = (BOOLEAN)*p;

	hdmi444 = (*p==1) ? LX_DE_HDMI444_ON : LX_DE_HDMI444_OFF;
	ret = de_kwrap_sethdmi444mode((UINT32)win, hdmi444);

	DE_NOTI("win[%d] rgb444 [%d]", win, (hdmi444>LX_DE_HDMI444_OFF)?1:0);

	if (win == 0)
	{
		struct vsc_bwm_cfg bwm_cfg;
		bwm_cfg.hdmi444 = (*p==1) ? 1:0;
		vsc_bwm_set_config(VSC_BWM_OPT_HDMI444, &bwm_cfg);
	}

	return ret;
}

/* see LX_DE_HDR_IPC_MODE_T */
int vsc_set_hdr_ipc_type(UINT8 wid, UINT32 ipc_mode, UINT32 from)
{
	LX_DE_HDR_IPC_MODE_T hdr_mode;
	if(wid == 2) {
		hdr_mode.ucWinID = LX_DE_WIN_3;//3rd window (fw:LX_DE_WIN_SUB2)
	}
	else if(wid == 3) {
		hdr_mode.ucWinID = LX_DE_WIN_4;//4th window (fw:LX_DE_WIN_SUB3)
	}
	else {
		hdr_mode.ucWinID = wid;
	}
	hdr_mode.eIpcMode = ipc_mode;
	hdr_mode.eFrom = from;
	return resource_mgr_ioctl(DE_IOW_IPC_SET_HDR_MODE,(unsigned long)&hdr_mode,1);
}

int vsc_set_hdr_type(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	UINT32 ipc_mode;
	LX_PE_HDR_MODE_INFO_T hdr_info;
	LX_PE_HDR_OP_MD_T *hdr_info_op;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].hdr_type, sizeof(enum v4l2_ext_vsc_hdr_type));
		return ret;
	}

	if(*p >= 9) return -1;

	vsc_config[win].hdr_type = (enum v4l2_ext_vsc_hdr_type)*p;

	/* convert user enum to kdrv enum */
	/* 0~5:off,h10,dovi,hlg,tech,ll -> 0~5:off,doby,hdr10,tech,s2h,hlg */
	if (*p==V4L2_EXT_VSC_HDR_TYPE_SDR)				ipc_mode = LX_HDR_TYPE_OFF;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_HDR10)		ipc_mode = LX_HDR_TYPE_HDR10;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_DOLBY)		ipc_mode = LX_HDR_TYPE_DOLBY;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_HLG)			ipc_mode = LX_HDR_TYPE_HLG;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_PRIME)		ipc_mode = LX_HDR_TYPE_TECHNICOLOR;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_DOLBY_LL)	ipc_mode = LX_HDR_TYPE_DOLBY_LL;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_DOLBY_RF)	ipc_mode = LX_HDR_TYPE_DOLBY_RF;
	else											ipc_mode = LX_HDR_TYPE_OFF;

	ret = vsc_set_hdr_ipc_type(win,ipc_mode,LX_HDR_MODE_FROM_SCL);

	DE_NOTI("hdr type : flag:%d, win:%d, type:%d, ipc:%d\n",flag,win,*p,ipc_mode);

	hdr_info.win_id = win;
	hdr_info_op = (LX_PE_HDR_OP_MD_T *)&hdr_info.data[0];
	hdr_info_op->connect = ipc_mode;
#ifdef INCLUDE_KDRV_PE
	ret |= vpq_hwrap_sethdropmodeinfo(VPQ_HWRAP_HDR_MI_CONNECT,&hdr_info);
#endif

	if (win == 0)
	{
		struct vsc_bwm_cfg bwm_cfg;
		bwm_cfg.hdr = *p;
		vsc_bwm_set_config(VSC_BWM_OPT_HDR, &bwm_cfg);
	}

#if 0
	UINT32 ipc_mode;
	LX_PE_HDR_MODE_INFO_T hdr_info;
	LX_PE_HDR_OP_MD_T *hdr_info_op;
	dovi_frame_size sFrameSize;
	E_HDR_CNTL_PATH eHDRCntlPath;
	UINT8 unWinID = win;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].hdr_type, sizeof(enum v4l2_ext_hdr_mode));
		return ret;
	}

	if(*p >= V4L2_EXT_HDR_MODE_MAX) return -1;

	vsc_config[win].hdr_type = (enum v4l2_ext_hdr_mode)*p;

	//hdr_mode.ucWinID = win;
	//hdr_mode.eIpcMode =
	//hdr_mode.eFrom =
	switch(vsc_config[win].hdr_type)
	{
		case	V4L2_EXT_VSC_HDR_TYPE_DOLBY:
		case	V4L2_EXT_VSC_HDR_TYPE_DOLBY_LL:
			{
				int iRet;
				if(vsc_config[win].inout_info.in.src == 	V4L2_EXT_VSC_INPUT_SRC_HDMI) {
					LX_HDR_MODE_T eHDRMode = LX_HDR_TYPE_DOLBY;

					if(vsc_config[win].hdr_type == V4L2_EXT_VSC_HDR_TYPE_DOLBY)
						eHDRCntlPath = E_HDMI_CNTRL_PATH;
					else
						eHDRCntlPath == E_HDMI_LL_CNTRL_PATH;
					//eHDRCntlPath = E_HDMI_CNTRL_PATH;
					sFrameSize.width 	= gbufTiming[0].hActive;
					sFrameSize.height	= gbufTiming[0].vActive;
					UINT32 unConfigCnt = 1;//default
					if(KWRAP_HDR_SetPQConfig(unWinID,LX_HDR_TYPE_DOLBY,unConfigCnt,"/var/wrongfile.cfg") != RET_OK){
						DE_NOTI("HDR Set PQ Config failed for Window [%d]\n",unWinID);
					}
					if(KWRAP_HDR_Init(unWinID,eHDRMode,eHDRCntlPath,sFrameSize) != RET_OK){
						DE_NOTI("HDR Init failed for Window [%d]\n",unWinID);
						ret = RET_ERROR;
					}
					if(KWRAP_HDR_Start(unWinID,eHDRCntlPath) != RET_OK){
						DE_NOTI("HDR Start failed for Window [%d]\n",unWinID);
						ret = RET_ERROR;
					}
					DE_NOTI("DOLBY HDR THread started!!!!!!!!!!!!!!!!!!!!!\n");
				}
			}
			break;
			case V4L2_EXT_VSC_HDR_TYPE_SDR:
			{
				if(vsc_config[win].inout_info.in.src == 	V4L2_EXT_VSC_INPUT_SRC_HDMI) {
					if(KWRAP_HDR_Stop(unWinID) != RET_OK){
						DE_NOTI("Failed to stop HDR mode for [%d] Window\n",unWinID);
						ret = RET_ERROR;
					}

					if(KWRAP_HDR_Uninit(unWinID) != RET_OK){
						DE_NOTI("HDR UnInit failed for Window [%d]\n",unWinID);
						ret = RET_ERROR;
					}
					DE_NOTI("DOLBY HDR THread stopped!!!!!!!!!!!!!!!!!!!!!\n");
				}
			}
			break;
	}

	/* convert user enum to kdrv enum */
	/* 0~5:off,h10,dovi,hlg,tech,ll -> 0~5:off,doby,hdr10,tech,s2h,hlg */
	if (*p==V4L2_EXT_VSC_HDR_TYPE_SDR)				ipc_mode = LX_HDR_TYPE_OFF;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_HDR10)		ipc_mode = LX_HDR_TYPE_HDR10;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_DOLBY)		ipc_mode = LX_HDR_TYPE_DOLBY;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_HLG)			ipc_mode = LX_HDR_TYPE_HLG;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_PRIME)		ipc_mode = LX_HDR_TYPE_TECHNICOLOR;
	else if (*p==V4L2_EXT_VSC_HDR_TYPE_DOLBY_LL)	ipc_mode = LX_HDR_TYPE_DOLBY_LL;
	else											ipc_mode = LX_HDR_TYPE_OFF;

	ret = vsc_set_hdr_ipc_type(win,ipc_mode,LX_HDR_MODE_FROM_SCL);

	DE_NOTI("hdr type : flag:%d, win:%d, type:%d, ipc:%d\n",flag,win,*p,ipc_mode);

	hdr_info.win_id = win;
	hdr_info_op = (LX_PE_HDR_OP_MD_T *)&hdr_info.data[0];
	hdr_info_op->connect = ipc_mode;
	ret |= vpq_hwrap_sethdropmodeinfo(VPQ_HWRAP_HDR_MI_CONNECT,&hdr_info);
#endif
	return ret;
}

int vsc_set_cvi_frz(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	unsigned int cvi_frz;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].cvi_frz, sizeof(BOOLEAN));
		return ret;
	}
	if(*p < 0 || *p > 1) return -1;

	cvi_frz = *p;
	ret = resource_mgr_ioctl(DE_IOW_SET_CVI_FREEZE,(unsigned long)&cvi_frz,1);

	DE_NOTI("cvi frz [%d]", *p);

	return ret;
}

int vsc_set_sub_occupy(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_SUB_MODE_T sub_mode;
#ifdef INCLUDE_KDRV_PE
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
#endif

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].sub_occupied, sizeof(BOOLEAN));
		return ret;
	}

	if(*p > 1) return -1;

	sub_mode = (*p==1) ? LX_DE_SUB_MODE_OCCUPIED : LX_DE_SUB_MODE_NONE;
	vsc_config[win].sub_occupied = *p;

	if ( lx_chip_rev( ) < LX_CHIP_REV(O20,A0) ) { // skip this control for m16p3
		return ret;
	}

	if(vsc_config[1].inout_info.out == V4L2_EXT_VSC_DEST_VENC && sub_mode == LX_DE_SUB_MODE_OCCUPIED)
	{
		LX_DE_INPUT_SOURCE_T src;
		memset (&src, 0, sizeof(LX_DE_INPUT_SOURCE_T));
		src.srcId = 1;
		ret = resource_mgr_ioctl(DE_IOW_SET_WIN_PORT_SRC,(unsigned long)&src,1); // close win_1(venc)
		gbufTiming[0].hActive = 0; // reset timing info
		DE_NOTI("w/a : close win_1 by sub_occupied & reset timing_info");
	}

	//if(vsc_config[1].sub_mode.win_mode > V4L2_EXT_VSC_WIN_MODE_NONE)
	if(vsc_config[1].sub_mode.win_mode > V4L2_EXT_VSC_WIN_MODE_NONE && vsc_config[1].inout_info.in.src > V4L2_EXT_VSC_INPUT_SRC_NONE) //SICREQ-273
	{
		DE_NOTI("skip sub_occupied");
	}
	else {
	ret = resource_mgr_ioctl(DE_IOW_SET_SUB_MODE,(unsigned long)&sub_mode,1);
	}
	DE_NOTI("sub_occupied [%d] win_mode[%d]", *p, vsc_config[1].sub_mode.win_mode);
	
#ifdef INCLUDE_KDRV_PE
	cur_inf_param.win_id = win;
	/* get pre display info */
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	cur_inf_param.info_type = LX_PE_INFO_MISC;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	/**
	* causion, these items only in this function :
	* mul_win
	*/
	cur_inf_param.sub_mode= (UINT32)sub_mode;
	/* set default */
	if (pre_inf_param.sub_mode != cur_inf_param.sub_mode)
	{
		/* set disp info */
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
	}
#endif
	return ret;
}

int vsc_set_local_mute(BOOLEAN flag, UINT8 win, SINT32 *p)
{
	int ret = 0;
	LX_DE_SET_WIN_BLANK_T param;

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].en_local_mute, sizeof(BOOLEAN));
		return ret;
	}

	vsc_config[win].en_local_mute = *p;

	memset(&param, 0, sizeof(LX_DE_SET_WIN_BLANK_T));
	param.bEnable = 0;
	if(*p == 0) 	 // enable local mute
		param.isRGB = 4;	   // b'100
	else if(*p == 1) // disable local mute
		param.isRGB = 6;	   // b'110
	ret = resource_mgr_ioctl(DE_IOW_SET_WIN_BLANK,(unsigned long)&param,1);

	DE_NOTI(" %s", (*p>0)?"enable":"disable");

	return ret;
}

int vsc_set_ipc_mode(BOOLEAN flag, UINT8 win, UINT32 *p)
{
	int ret = 0;
	UINT32 ipc_mode;
	UINT32 a, b;
	OS_FILE_T proc_fp;
	char str[32];

	if(!p) return -1;

	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].ipc_mode, sizeof(UINT32));
		return ret;
	}
	vsc_config[win].ipc_mode = ipc_mode = (UINT32)*p;

	if(RET_OK != OS_OpenFile(&proc_fp, "/proc/lg/de/v4l2_vsc_debug_func", O_RDWR, 0666)) {
		DE_ERROR("file open fail");
		return -1;
	}

/*
	*p = 0 --> field_merge(de-interlacer on)
	*p = 1 --> line_double(de-interlacer on)
	*p = 2 --> top_only
*/
/*
	IPCOFF 1 0 --> top field 만 출력
	IPCOFF 1 1 --> bottom field 만 출력
	IPCOFF 1 2 --> double
	IPCOFF 0 0 --> 정상 De-int
*/
	switch(*p) {
		case 0:
			a = 1;
			b = 0;
			break;
		case 1:
			a = 1;
			b = 2;
			break;
		case 2:
		default:
			a = b = 0;
			break;
	}
	memset(str, 0, sizeof(str));
	sprintf(str, "15 ipcoff %d %d end" ,a, b);
	OS_WriteFile(&proc_fp, str, sizeof(str));

	DE_NOTI("IPCMode(=De-interlacling)  [%d] (0:on,1:double,2:top_only", ipc_mode);
	OS_CloseFile(&proc_fp);

	return ret;
}

int vsc_set_orbit_policy(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_orbit_policy *p)
{
	int ret = 0;
#ifdef VSC_ORBIT_DRV_CALCULATE
	LX_DE_ORBIT_T orbit_win_window, orbit_win_move;

	struct v4l2_ext_vsc_orbit_position calculated_orbit_position;
	struct v4l2_ext_video_rect source;
	struct v4l2_ext_video_rect input;
	struct v4l2_ext_video_rect output;

	if(!p) return -1;
	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].orbit_policy, sizeof(struct v4l2_ext_vsc_orbit_policy));
		return ret;
	}

	memcpy(&vsc_config[win].orbit_policy, p, sizeof(struct v4l2_ext_vsc_orbit_policy));

	do {
		// Resolution from source region
		source.x = source.y = 0;
		source.w = vsc_config[win].win_info.in.res.w;
		source.h = vsc_config[win].win_info.in.res.h;
		// Resolution from crop region
		input.x =  vsc_config[win].win_info.in.crop.x;
		input.y =  vsc_config[win].win_info.in.crop.y;
		input.w =  vsc_config[win].win_info.in.crop.w;
		input.h =  vsc_config[win].win_info.in.crop.h;
		// Resolution from output region
		output.x = vsc_config[win].win_info.out.x;
		output.y = vsc_config[win].win_info.out.y;
		output.w = vsc_config[win].win_info.out.w;
		output.h = vsc_config[win].win_info.out.h;

		vsc_OrbitCallbackFp = (ORBIT_CALLBACK_T *)vsc_getOrbitCallbackFp();
		if(vsc_OrbitCallbackFp == NULL)  {DE_ERROR("pfn is NULL");return -1;}
		if(vsc_OrbitCallbackFp->pfnCalculateOrbitPosition) {
			vsc_OrbitCallbackFp->pfnCalculateOrbitPosition(source,input,output,vsc_config[win].orbit_policy,&calculated_orbit_position);
			DE_NOTI("getOrbit : win[%d] calculated vid psosition(orbit_move) %d,%d(%dx%d)", win,\
				calculated_orbit_position.orbit_move.video_output.x, calculated_orbit_position.orbit_move.video_output.y,\
				calculated_orbit_position.orbit_move.video_output.w, calculated_orbit_position.orbit_move.video_output.h);
		}

		orbit_win_window.wId = win;
		orbit_win_window.type = 0;
		orbit_win_window.osd_input.w = calculated_orbit_position.orbit_window.osd_input.w;
		orbit_win_window.osd_input.h = calculated_orbit_position.orbit_window.osd_input.h;
		orbit_win_window.osd_input.x = calculated_orbit_position.orbit_window.osd_input.x;
		orbit_win_window.osd_input.y = calculated_orbit_position.orbit_window.osd_input.y;
		orbit_win_window.video_input.w = calculated_orbit_position.orbit_window.video_input.w;
		orbit_win_window.video_input.h = calculated_orbit_position.orbit_window.video_input.h;
		orbit_win_window.video_input.x = calculated_orbit_position.orbit_window.video_input.x;
		orbit_win_window.video_input.y = calculated_orbit_position.orbit_window.video_input.y;
		orbit_win_window.osd_output.w = calculated_orbit_position.orbit_window.osd_output.w;
		orbit_win_window.osd_output.h = calculated_orbit_position.orbit_window.osd_output.h;
		orbit_win_window.osd_output.x = calculated_orbit_position.orbit_window.osd_output.x;
		orbit_win_window.osd_output.y = calculated_orbit_position.orbit_window.osd_output.y;
		orbit_win_window.video_output.w = calculated_orbit_position.orbit_window.video_output.w;
		orbit_win_window.video_output.h = calculated_orbit_position.orbit_window.video_output.h;
		orbit_win_window.video_output.x = calculated_orbit_position.orbit_window.video_output.x;
		orbit_win_window.video_output.y = calculated_orbit_position.orbit_window.video_output.y;

		orbit_win_move.wId = win;
		orbit_win_move.type = 1;
		orbit_win_move.osd_input.w = calculated_orbit_position.orbit_move.osd_input.w;
		orbit_win_move.osd_input.h = calculated_orbit_position.orbit_move.osd_input.h;
		orbit_win_move.osd_input.x = calculated_orbit_position.orbit_move.osd_input.x;
		orbit_win_move.osd_input.y = calculated_orbit_position.orbit_move.osd_input.y;
		orbit_win_move.video_input.w = calculated_orbit_position.orbit_move.video_input.w;
		orbit_win_move.video_input.h = calculated_orbit_position.orbit_move.video_input.h;
		orbit_win_move.video_input.x = calculated_orbit_position.orbit_move.video_input.x;
		orbit_win_move.video_input.y = calculated_orbit_position.orbit_move.video_input.y;
		orbit_win_move.osd_output.w = calculated_orbit_position.orbit_move.osd_output.w;
		orbit_win_move.osd_output.h = calculated_orbit_position.orbit_move.osd_output.h;
		orbit_win_move.osd_output.x = calculated_orbit_position.orbit_move.osd_output.x;
		orbit_win_move.osd_output.y = calculated_orbit_position.orbit_move.osd_output.y;
		orbit_win_move.video_output.w = calculated_orbit_position.orbit_move.video_output.w;
		orbit_win_move.video_output.h = calculated_orbit_position.orbit_move.video_output.h;
		orbit_win_move.video_output.x = calculated_orbit_position.orbit_move.video_output.x;
		orbit_win_move.video_output.y = calculated_orbit_position.orbit_move.video_output.y;

	} while(0);
	if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		orbit_win_window.wId = orbit_win_move.wId = LX_DE_WIN_3;
	if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		orbit_win_window.wId = orbit_win_move.wId = LX_DE_WIN_4;
	ret = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_win_window,1);
	ret |= resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_win_move,1);
#endif
	return ret;
}

int vsc_set_orbit_window(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_orbit_window *p)
{
	int ret = 0;
	LX_DE_ORBIT_T orbit_win;
	struct v4l2_ext_vsc_orbit_window calculated_orbit_window;

	if(!p) return -1;
	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].orbit_win, sizeof(struct v4l2_ext_vsc_orbit_window));
		return ret;
	}

	memcpy(&vsc_config[win].orbit_win, p, sizeof(struct v4l2_ext_vsc_orbit_window));

	do {
		orbit_win.wId = win;
		orbit_win.type = 0;
		orbit_win.osd_input.w = p->osd_input.w;
		orbit_win.osd_input.h = p->osd_input.h;
		orbit_win.osd_input.x = p->osd_input.x;
		orbit_win.osd_input.y = p->osd_input.y;
		orbit_win.video_input.w = p->video_input.w;
		orbit_win.video_input.h = p->video_input.h;
		orbit_win.video_input.x = p->video_input.x;
		orbit_win.video_input.y = p->video_input.y;
		orbit_win.osd_output.w = p->osd_output.w;
		orbit_win.osd_output.h = p->osd_output.h;
		orbit_win.osd_output.x = p->osd_output.x;
		orbit_win.osd_output.y = p->osd_output.y;
		orbit_win.video_output.w = p->video_output.w;
		orbit_win.video_output.h = p->video_output.h;
		orbit_win.video_output.x = p->video_output.x;
		orbit_win.video_output.y = p->video_output.y;

		if(vsc_config[win].seamless < 2)
			break;

#ifdef VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
		vsc_AspectratioCallbackFp = (ASPECTRATIO_CALLBACK_T *)vsc_getAspectratioCallbackFp();
		if(vsc_AspectratioCallbackFp == NULL)  {DE_ERROR("pfn is NULL");return -1;}

		if(vsc_AspectratioCallbackFp->pfnOrbitdrvWindowConvert && vsc_AspectratioCallbackFp->pfnOrbitdrvMoveConvert) {
			ret = vsc_AspectratioCallbackFp->pfnOrbitdrvWindowConvert(vsc_config[win].aspectratio_policy.system_policy,vsc_config[win].calculated_input_rect,vsc_config[win].calculated_output_rect,vsc_config[win].orbit_win,&calculated_orbit_window);
			memcpy(&vsc_config[win].calculated_orbit_win, &calculated_orbit_window, sizeof(struct v4l2_ext_vsc_orbit_window));
			DE_NOTI("WindowConvert : orbit_window in[%d,%d %dx%d] out[%d,%d %dx%d]", calculated_orbit_window.video_input.x, calculated_orbit_window.video_input.y, calculated_orbit_window.video_input.w, calculated_orbit_window.video_input.h,\
				calculated_orbit_window.video_output.x, calculated_orbit_window.video_output.y, calculated_orbit_window.video_output.w, calculated_orbit_window.video_output.h);

		orbit_win.wId = win;
		orbit_win.type = 0;
		orbit_win.osd_input.w = calculated_orbit_window.osd_input.w;
		orbit_win.osd_input.h = calculated_orbit_window.osd_input.h;
		orbit_win.osd_input.x = calculated_orbit_window.osd_input.x;
		orbit_win.osd_input.y = calculated_orbit_window.osd_input.y;
		orbit_win.video_input.w = calculated_orbit_window.video_input.w;
		orbit_win.video_input.h = calculated_orbit_window.video_input.h;
		orbit_win.video_input.x = calculated_orbit_window.video_input.x;
		orbit_win.video_input.y = calculated_orbit_window.video_input.y;
		orbit_win.osd_output.w = calculated_orbit_window.osd_output.w;
		orbit_win.osd_output.h = calculated_orbit_window.osd_output.h;
		orbit_win.osd_output.x = calculated_orbit_window.osd_output.x;
		orbit_win.osd_output.y = calculated_orbit_window.osd_output.y;
		orbit_win.video_output.w = calculated_orbit_window.video_output.w;
		orbit_win.video_output.h = calculated_orbit_window.video_output.h;
		orbit_win.video_output.x = calculated_orbit_window.video_output.x;
		orbit_win.video_output.y = calculated_orbit_window.video_output.y;

		}
#endif
	} while(0);
	if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		orbit_win.wId = LX_DE_WIN_3;
	if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		orbit_win.wId = LX_DE_WIN_4;
	ret = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_win,1);

	DE_NOTI("win%d: vi[%dx%d(%d,%d)] oi[%dx%d(%d,%d)] vo[%dx%d(%d,%d)] oo[%dx%d(%d,%d)]", win, \
		orbit_win.video_input.w, orbit_win.video_input.h, orbit_win.video_input.x, orbit_win.video_input.y,\
		orbit_win.osd_input.w, orbit_win.osd_input.h, orbit_win.osd_input.x, orbit_win.osd_input.y,\
		orbit_win.video_output.w, orbit_win.video_output.h, orbit_win.video_output.x, orbit_win.video_output.y,\
		orbit_win.osd_output.w, orbit_win.osd_output.h, orbit_win.osd_output.x, orbit_win.osd_output.y);
	return ret;
}

int vsc_set_orbit_move(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_orbit_move *p)
{
	int ret = 0;
	LX_DE_ORBIT_T orbit_move;
	struct v4l2_ext_vsc_orbit_move calculated_orbit_move;

	if(!p) return -1;
	if(!flag)//get
	{
		memcpy(p, &vsc_config[win].orbit_move, sizeof(struct v4l2_ext_vsc_orbit_move));
		return ret;
	}

	memcpy(&vsc_config[win].orbit_move, p, sizeof(struct v4l2_ext_vsc_orbit_move));

	do {
		orbit_move.wId = win;
		orbit_move.type = 1;
		orbit_move.osd_input.w = p->osd_input.w;
		orbit_move.osd_input.h = p->osd_input.h;
		orbit_move.osd_input.x = p->osd_input.x;
		orbit_move.osd_input.y = p->osd_input.y;
		orbit_move.video_input.w = p->video_input.w;
		orbit_move.video_input.h = p->video_input.h;
		orbit_move.video_input.x = p->video_input.x;
		orbit_move.video_input.y = p->video_input.y;
		orbit_move.osd_output.w = p->osd_output.w;
		orbit_move.osd_output.h = p->osd_output.h;
		orbit_move.osd_output.x = p->osd_output.x;
		orbit_move.osd_output.y = p->osd_output.y;
		orbit_move.video_output.w = p->video_output.w;
		orbit_move.video_output.h = p->video_output.h;
		orbit_move.video_output.x = p->video_output.x;
		orbit_move.video_output.y = p->video_output.y;

		if(vsc_config[win].seamless < 2)
			break;

#ifdef VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
		vsc_AspectratioCallbackFp = (ASPECTRATIO_CALLBACK_T *)vsc_getAspectratioCallbackFp();
		if(vsc_AspectratioCallbackFp == NULL)  {DE_ERROR("pfn is NULL");return -1;}
	
		if(vsc_AspectratioCallbackFp->pfnOrbitdrvWindowConvert && vsc_AspectratioCallbackFp->pfnOrbitdrvMoveConvert) {
			ret = vsc_AspectratioCallbackFp->pfnOrbitdrvMoveConvert(vsc_config[win].aspectratio_policy.system_policy, vsc_config[win].orbit_win, vsc_config[win].calculated_orbit_win, vsc_config[win].orbit_move, &calculated_orbit_move);
			DE_NOTI("MoveConvert :calculated_orbit_move: in[%d,%d %dx%d] out[%d,%d %dx%d]", calculated_orbit_move.video_input.x, calculated_orbit_move.video_input.y, calculated_orbit_move.video_input.w, calculated_orbit_move.video_input.h,\
				calculated_orbit_move.video_output.x, calculated_orbit_move.video_output.y, calculated_orbit_move.video_output.w, calculated_orbit_move.video_output.h);

			orbit_move.wId = win;
			orbit_move.type = 1;
			orbit_move.osd_input.w = calculated_orbit_move.osd_input.w;
			orbit_move.osd_input.h = calculated_orbit_move.osd_input.h;
			orbit_move.osd_input.x = calculated_orbit_move.osd_input.x;
			orbit_move.osd_input.y = calculated_orbit_move.osd_input.y;
			orbit_move.video_input.w = calculated_orbit_move.video_input.w;
			orbit_move.video_input.h = calculated_orbit_move.video_input.h;
			orbit_move.video_input.x = calculated_orbit_move.video_input.x;
			orbit_move.video_input.y = calculated_orbit_move.video_input.y;
			orbit_move.osd_output.w = calculated_orbit_move.osd_output.w;
			orbit_move.osd_output.h = calculated_orbit_move.osd_output.h;
			orbit_move.osd_output.x = calculated_orbit_move.osd_output.x;
			orbit_move.osd_output.y = calculated_orbit_move.osd_output.y;
			orbit_move.video_output.w = calculated_orbit_move.video_output.w;
			orbit_move.video_output.h = calculated_orbit_move.video_output.h;
			orbit_move.video_output.x = calculated_orbit_move.video_output.x;
			orbit_move.video_output.y = calculated_orbit_move.video_output.y;
		}
		else {
			DE_NOTI("vsc_AspectratioCallbackFp->pfnOrbitdrvMoveConvert is null");
		}
#endif
	} while(0);
	if(win == 2 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		orbit_move.wId = LX_DE_WIN_3;
	if(win == 3 && vsc_config[win].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
		orbit_move.wId = LX_DE_WIN_4;
	ret = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_move,1);

	DE_NOTI("win%d: vi[%dx%d(%d,%d)] oi[%dx%d(%d,%d)] vo[%dx%d(%d,%d)] oo[%dx%d(%d,%d)]", win, \
		orbit_move.video_input.w, orbit_move.video_input.h, orbit_move.video_input.x, orbit_move.video_input.y,\
		orbit_move.osd_input.w, orbit_move.osd_input.h, orbit_move.osd_input.x, orbit_move.osd_input.y,\
		orbit_move.video_output.w, orbit_move.video_output.h, orbit_move.video_output.x, orbit_move.video_output.y,\
		orbit_move.osd_output.w, orbit_move.osd_output.h, orbit_move.osd_output.x, orbit_move.osd_output.y);

	return ret;
}

int v4l2_vsc_keep_submode(int flag)
{
	LX_DE_SUB_MODE_T sub_mode;

	vsc_config[0].keep_submode = flag;

	if(flag==4) { // by terminating of overlay-app (3:PipMaskOn, 4:PipMaskOff)
		sub_mode = LX_DE_SUB_MODE_NONE;
		resource_mgr_ioctl(DE_IOW_SET_SUB_MODE,(unsigned long)&sub_mode,1);
		DE_NOTI("set submode = NONE");
	}

	return 0;
}

int vsc_set_pixeltopixel(BOOLEAN flag, UINT8 win, UINT32 *p)
{
	int ret = 0;
	UINT32 mode;
	if(!flag)//get
	{
		memcpy(p, &vsc_config[0].ptp, sizeof(UINT32));
		return ret;

	}
	mode = vsc_config[0].ptp = *p;
	ret = resource_mgr_ioctl(DE_IOW_SET_PIXELTOPIXEL,(unsigned long)&mode, 1);

	DE_NOTI("mode = %d", mode);

	return ret;
}

int v4l2_vsc_switchmcu(int id)
{
	unsigned int mcu = 1;//to mcu0

	if (id==1)		mcu = 2;//to mcu1
	else if (id==9)	mcu = 0;//to cpu

	return resource_mgr_ioctl(DE_IOW_SET_UART_FOR_MCU,(unsigned long)&mcu,1);
}

// end VIDIOC_S_CTRL
void vsc_v4l2_vp_thread(void)
{
	UINT32 i;

	do {
		for(i = 0 ; i < 4 ; i++)
		{
			if(vsc_config[i].inout_info.in.src > V4L2_EXT_VSC_INPUT_SRC_NONE)
			{
				_vsc_vp_periodictask(i);
			}
		}
	}while(0);
}

void vsc_v4l2_vp_init(void)
{
#ifdef INCLUDE_KDRV_HDMI20
	KWARP_HDMI20_Open();
	KWARP_HDMI20_RX_Initialize();
#endif
}

static void _vsc_vp_change_hdmi_src(UINT32 vpSrcId, UINT32 attr, UINT32 port, struct v4l2_ext_vsc_win_region *p_win, struct v4l2_ext_vsc_orbit_window *p_orbit_win, struct v4l2_ext_vsc_orbit_window *p_orbit_move)
{
	int iRet = RET_ERROR;
	LX_DE_INPUT_SOURCE_T src;
	LX_DE_WIN_INFO_T win_info;
	LX_DE_ORBIT_T orbit_win;
	LX_DE_ORBIT_T orbit_move;;

	src.srcId = vpSrcId;
	src.srcType = LX_DE_IN_SRC_HDMI;
	src.srcAttr = attr/*0~3:phys, 5:HDMI_PORT_DSC*/;
	src.srcPort = 0;
	src.hdmiPort = port;/*0~3:phys*/
	iRet = resource_mgr_ioctl(DE_IOW_SET_WIN_PORT_SRC,(unsigned long)&src,1);
	if(iRet) DE_ERROR("error [%d]", iRet);

	win_info.wId = vpSrcId;
	win_info.rot = (LX_DE_ROTATE_INFO_T)p_win->rotation;
	win_info.in_size.w = p_win->in.res.w;
	win_info.in_size.h = p_win->in.res.h;
	win_info.in_win.x  = p_win->in.crop.x;
	win_info.in_win.y  = p_win->in.crop.y;
	win_info.in_win.w  = p_win->in.crop.w;
	win_info.in_win.h  = p_win->in.crop.h;
	win_info.out_win.x = p_win->out.x;
	win_info.out_win.y = p_win->out.y;
	win_info.out_win.w = p_win->out.w;
	win_info.out_win.h = p_win->out.h;
	win_info.resize_ani_flag = 0;
	iRet = resource_mgr_ioctl(DE_IOW_SET_WIN_INFO,(unsigned long)&win_info,1);
	if(iRet) DE_ERROR("error [%d]", iRet);

	orbit_move.wId = vpSrcId;
	orbit_move.type = 0;
	orbit_win.osd_input.w = p_orbit_win->osd_input.w;
	orbit_win.osd_input.h = p_orbit_win->osd_input.h;
	orbit_win.osd_input.x = p_orbit_win->osd_input.x;
	orbit_win.osd_input.y = p_orbit_win->osd_input.y;
	orbit_win.video_input.w = p_orbit_win->video_input.w;
	orbit_win.video_input.h = p_orbit_win->video_input.h;
	orbit_win.video_input.x = p_orbit_win->video_input.x;
	orbit_win.video_input.y = p_orbit_win->video_input.y;
	orbit_win.osd_output.w = p_orbit_win->osd_output.w;
	orbit_win.osd_output.h = p_orbit_win->osd_output.h;
	orbit_win.osd_output.x = p_orbit_win->osd_output.x;
	orbit_win.osd_output.y = p_orbit_win->osd_output.y;
	orbit_win.video_output.w = p_orbit_win->video_output.w;
	orbit_win.video_output.h = p_orbit_win->video_output.h;
	orbit_win.video_output.x = p_orbit_win->video_output.x;
	orbit_win.video_output.y = p_orbit_win->video_output.y;
	iRet = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_win,1);

	orbit_move.wId = vpSrcId;
	orbit_move.type = 1;
	orbit_move.osd_input.w = p_orbit_move->osd_input.w;
	orbit_move.osd_input.h = p_orbit_move->osd_input.h;
	orbit_move.osd_input.x = p_orbit_move->osd_input.x;
	orbit_move.osd_input.y = p_orbit_move->osd_input.y;
	orbit_move.video_input.w = p_orbit_move->video_input.w;
	orbit_move.video_input.h = p_orbit_move->video_input.h;
	orbit_move.video_input.x = p_orbit_move->video_input.x;
	orbit_move.video_input.y = p_orbit_move->video_input.y;
	orbit_move.osd_output.w = p_orbit_move->osd_output.w;
	orbit_move.osd_output.h = p_orbit_move->osd_output.h;
	orbit_move.osd_output.x = p_orbit_move->osd_output.x;
	orbit_move.osd_output.y = p_orbit_move->osd_output.y;
	orbit_move.video_output.w = p_orbit_move->video_output.w;
	orbit_move.video_output.h = p_orbit_move->video_output.h;
	orbit_move.video_output.x = p_orbit_move->video_output.x;
	orbit_move.video_output.y = p_orbit_move->video_output.y;
	iRet = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_move,1);

	DE_NOTI("DSC : attr[%d:%s], port[%d], src[%dx%d] out_win[%dx%d]", \
		attr, attr>3?"DSC":"NONE", port, \
		win_info.in_size.w, win_info.in_size.h, \
		win_info.out_win.w, win_info.out_win.h);
	DE_NOTI("orbit move : %dx%d(%d,%d)", \
		p_orbit_move->video_output.w, p_orbit_move->video_output.h, p_orbit_move->video_output.x, p_orbit_move->video_output.y);
	return;
}

void v4l2_vsc_update_pulldown(UINT32 type)
{
	char hw_opt[24];
	UINT32 pulldown = 0;
	if(RET_OK==OS_ScanKernelCmdline("hwopt=%s", hw_opt))
	{
		if (hw_opt[4] == '0') // 60hz output
		{
			if (type==4 || type==5)	pulldown = 1;
		}
	}
	_g_curr_pulldown = pulldown;

	DE_NOTI("memc_type : %d  --> _g_curr_pulldown : %d", type, _g_curr_pulldown);
	return;
}

static void _vsc_vp_periodictask(UINT32 winid)
{
	int iRet = RET_ERROR;
	LX_DE_CVI_SRC_TYPE_T  		cviInfo = {0, };
	static struct vsc_config prev_info[4];
	static int timing_changed[4] = {0,0,0,0};

	kwrap_vp_timing_info_t bufTiming;
	static kwrap_vp_timing_info_t	prev_bufTiming[4] = {0,};
	//static kwrap_vp_chg_info_t prev_HdmiConfig[4] = { 0, };

	kwrap_vp_src_info_t vpInputSrc;
	static int prevhdmiport[4] = {-1,-1,-1,-1};

	kwrap_vp_fr_info_t frameRateInfo = {FALSE,0};
	
	#ifdef INCLUDE_KDRV_PE
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
	#endif

	memset(&bufTiming, 0, sizeof(kwrap_vp_timing_info_t));

	switch(vsc_config[winid].inout_info.in.src)
	{
		case V4L2_EXT_VSC_INPUT_SRC_HDMI:
			{
			vpInputSrc.Type = SRC_INPUT_HDMI;
			vpInputSrc.Attr = ghdmiphyport[winid];
				iRet = vp_kwrap_readtiminginfo_frm_hdmi(winid, vpInputSrc, &bufTiming);
				if(iRet) DE_ERROR("invalid timing info from hdmi");
			}
			break;
		case V4L2_EXT_VSC_INPUT_SRC_AVD:
			{
				vpInputSrc.Type = SRC_INPUT_ATV;
				if(vsc_config[winid].inout_info.in.attr == 1)
				{
					vpInputSrc.Type = SRC_INPUT_CVBS;
				}
				else if(vsc_config[winid].inout_info.in.attr == 0)
				{
					vpInputSrc.Type = SRC_INPUT_ATV;
				}
				else
					DE_ERROR("invalid addr of AVD input");
				iRet = vp_kwrap_readtiminginfo_frm_cvd(vpInputSrc, &bufTiming);
			}
			break;
		case V4L2_EXT_VSC_INPUT_SRC_ADC:
			{
			vpInputSrc.Type = SRC_INPUT_YPBPR;
			iRet = vp_kwrap_readtiminginfo_frm_adc(vpInputSrc, &bufTiming);
			}
			break;
		case V4L2_EXT_VSC_INPUT_SRC_VDEC:
			{
			vpInputSrc.Type = SRC_INPUT_MVI;
			vpInputSrc.Port = winid;
			iRet = vp_kwrap_readtiminginfo_frm_vdec(vpInputSrc, &bufTiming);
			bufTiming.isMVI = 1;
			}
			break;
		case V4L2_EXT_VSC_INPUT_SRC_JPEG:
			{
			vpInputSrc.Type = SRC_INPUT_JPG;
			vpInputSrc.Port = winid;
			iRet = vp_kwrap_readtiminginfo_frm_vdec(vpInputSrc, &bufTiming);
			bufTiming.isMVI = 1;
			}
			break;
		default:
			return;
	}

	if(prev_info[winid].inout_info.in.src != vsc_config[winid].inout_info.in.src) {
		timing_changed[winid] = 1;
	}
	else if(prevhdmiport[winid] != ghdmiphyport[winid]) {
		timing_changed[winid] = 2;
	}
	else if (prev_bufTiming[winid].hActive != bufTiming.hActive || \
		prev_bufTiming[winid].vActive != bufTiming.vActive || \
		prev_bufTiming[winid].vFreq        != bufTiming.vFreq || \
		prev_bufTiming[winid].scanType != bufTiming.scanType) {
		timing_changed[winid] = 3;
	}
	else if (prev_bufTiming[winid].colordomain != bufTiming.colordomain || \
		prev_bufTiming[winid].hdmi444mode != bufTiming.hdmi444mode) {
		timing_changed[winid] = 4;
	}
	else if (gbufTiming[winid].hActive != bufTiming.hActive) {
		timing_changed[winid] = 5;
	}
	else if (prev_bufTiming[winid].phyMode != bufTiming.phyMode) {
		if(vsc_config[winid].inout_info.in.src==V4L2_EXT_VSC_INPUT_SRC_HDMI)
			timing_changed[winid] = 6;
	}
	else if (prev_bufTiming[winid].isDSC != bufTiming.isDSC) {
		if(vsc_config[winid].inout_info.in.src==V4L2_EXT_VSC_INPUT_SRC_HDMI)
			timing_changed[winid] = 7;
	}
	else if (prev_bufTiming[winid].isFreeSyncMode != bufTiming.isFreeSyncMode || \
		prev_bufTiming[winid].isGSyncMode         != bufTiming.isGSyncMode ||    \
		prev_bufTiming[winid].isFreeSyncMode      != bufTiming.isFreeSyncMode || \
		prev_bufTiming[winid].isMConst            != bufTiming.isMConst||        \
		prev_bufTiming[winid].isQmsMode            != bufTiming.isQmsMode|| \
		prev_bufTiming[winid].isFvaMode           != bufTiming.isFvaMode) { // TBD. see AVTASK-539(isMConst)
		if(vsc_config[winid].inout_info.in.src==V4L2_EXT_VSC_INPUT_SRC_HDMI) {
			timing_changed[winid] = 8;
		}
			DE_NOTI("QmsMode[%d] MConst[%d] FreeSyncMode[%d]", \
				bufTiming.isQmsMode, bufTiming.isMConst, bufTiming.isFreeSyncMode);
	}
	else if (winid == 0 && (_g_prev_pulldown != _g_curr_pulldown)) {
		timing_changed[winid] = 9;
		_g_prev_pulldown = _g_curr_pulldown;
	}
	else {
		timing_changed[winid] = 0;
	}
	if(timing_changed[winid] > 0)
	{
		DE_NOTI(">>>>>>>  timing_changed[%d] = %d  <<<<<<<\n",winid,timing_changed[winid]);

		prevhdmiport[winid] = ghdmiphyport[winid];
		vsc_config[winid].colordomain = bufTiming.colordomain;
		memcpy((void *)&(prev_bufTiming[winid]),(void *)&bufTiming,sizeof(bufTiming));
		memcpy((void *)&(prev_info[winid]),(void *)&vsc_config[winid],sizeof(struct vsc_config));

		//Copy default CVI configuration
		memcpy(&cviInfo,&cvi_common_config[vpInputSrc.Type],sizeof(LX_DE_CVI_SRC_TYPE_T));

		switch(vsc_config[winid].inout_info.in.src)
		{
			case V4L2_EXT_VSC_INPUT_SRC_HDMI:
				{
					_vsc_cvicfgfromhdmi(winid,vpInputSrc,bufTiming,&cviInfo);
					cviInfo.cvi_input_src = LX_DE_CVI_SRC_HDMI;
					cviInfo.cvi_channel = (LX_DE_CVI_CHANNEL_T)winid;
					cviInfo.cvi_port = LX_DE_CVI_EXT_A;
					cviInfo.cvi_game_info.isMConst  = (UINT32)bufTiming.isMConst;
					cviInfo.cvi_game_info.isQmsMode = (UINT32)bufTiming.isQmsMode;
					cviInfo.cvi_game_info.isFvaMode = ((UINT32)bufTiming.isFvaMode>1)?1:0;
					cviInfo.cvi_game_info.fvaFactor = bufTiming.isFvaMode;

					if(bufTiming.isDSC) // HDMI2.1 DSC
					{
						//iRet = KWARP_HDMI20_RX_Set_ExecuteDscModule(vpInputSrc.Attr);
						//if(iRet) DE_ERROR("error from ExecuteDscModule [%d]", iRet);
						_vsc_vp_change_hdmi_src(winid, \
							5/*HDMI_PORT_DSC*/, \
							vsc_config[winid].inout_info.in.index, \
							&vsc_config[winid].win_info,\
							&vsc_config[winid].orbit_win, \
							(struct v4l2_ext_vsc_orbit_window *)&vsc_config[winid].orbit_move);
						DE_NOTI("set HDMI21_DSC path");
					}
					else if(gbufTiming[winid].isDSC > 0) // previous isDSC
					{
						_vsc_vp_change_hdmi_src(winid, \
							vsc_config[winid].inout_info.in.index, \
							vsc_config[winid].inout_info.in.index, \
							&vsc_config[winid].win_info, \
							&vsc_config[winid].orbit_win, \
							(struct v4l2_ext_vsc_orbit_window *)&vsc_config[winid].orbit_move);
						DE_NOTI("restore previous HDMI port[%d]", vsc_config[winid].inout_info.in.index);
					}
				}
				break;
			case V4L2_EXT_VSC_INPUT_SRC_AVD:
				{
					if(vsc_config[winid].inout_info.in.attr == 1)
					{
						_vsc_cvicfgfromcvd(winid, vpInputSrc, bufTiming, &cviInfo, 0/*0:av,1:atv*/);
						cviInfo.cvi_input_src = LX_DE_CVI_SRC_CVBS;
					}
					else if(vsc_config[winid].inout_info.in.attr == 0)
					{
						_vsc_cvicfgfromcvd(winid, vpInputSrc, bufTiming, &cviInfo, 1/*0:av,1:atv*/);
						cviInfo.cvi_input_src = LX_DE_CVI_SRC_ATV;
					}
					else
						DE_ERROR("invalid addr of AVD input");
					cviInfo.cvi_channel = (LX_DE_CVI_CHANNEL_T)winid;
					cviInfo.size_offset.hsize = bufTiming.hActive;
					cviInfo.size_offset.vsize = bufTiming.vActive;
					cviInfo.cvi_port = LX_DE_CVI_CVD;
					DE_NOTI("[cvi_src_avd]wid: %d, attr:%d, input_src : %d\n",\
						winid, vsc_config[winid].inout_info.in.attr,cviInfo.cvi_input_src);
					if(vsc_config[winid].inout_info.out == V4L2_EXT_VSC_DEST_VENC) {
						vsc_set_fbpos(FB_NONE);
						iRet = _venc_control(0, LX_DE_DVR_ATV_REC, bufTiming.hActive, bufTiming.vActive, \
											0, 0, 0, 0, vsc_config[0].pos, 0);
						if(iRet) DE_ERROR("set venc error");
					}
				}
				break;
			case V4L2_EXT_VSC_INPUT_SRC_ADC:
				{
					_vsc_cvicfgfromadc(winid, vpInputSrc, bufTiming, &cviInfo);
					cviInfo.cvi_input_src = LX_DE_CVI_SRC_YPBPR;
					cviInfo.cvi_channel = (LX_DE_CVI_CHANNEL_T)winid;
					cviInfo.size_offset.hsize = bufTiming.hActive;
					cviInfo.size_offset.vsize = bufTiming.vActive;
					cviInfo.size_offset.hoffset = bufTiming.hStart;
					cviInfo.size_offset.voffset = bufTiming.vStart;
					cviInfo.scan = bufTiming.scanType;
					cviInfo.cvi_port = LX_DE_CVI_ADC;
				}
				break;
			default:
				break;
		}

		// common info
		cviInfo.cvi_split_info.rate = bufTiming.vFreq;

		if(vsc_config[winid].inout_info.in.src < V4L2_EXT_VSC_INPUT_SRC_VDEC)
			iRet = resource_mgr_ioctl(DE_IOW_SET_CVI_SRC_TYPE,(unsigned long)&cviInfo,CALL_FROM_KERNEL);
			// set color metry info for PE default
		/* get pre display info */
#ifdef INCLUDE_KDRV_PE
		cur_inf_param.win_id = winid;
		iRet = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);

		cur_inf_param.info_type = LX_PE_INFO_MODE;
		memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));

		if(bufTiming.colordomain >= LX_HDMI_CS_YCBCR420_601 && bufTiming.colordomain <= LX_HDMI_CS_YCBCR420_2020_NCL)
		{
			cur_inf_param.mode.is_420= 0x1;
		}
		else
		{
			cur_inf_param.mode.is_420= 0x0;
		}
		/* get is dsc */
		cur_inf_param.mode.is_dsc = bufTiming.isDSC;
		/* set disp info */
		if (pre_inf_param.mode.is_420 != cur_inf_param.mode.is_420 || \
			pre_inf_param.mode.is_dsc != cur_inf_param.mode.is_dsc)
		{
			iRet = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		}
		iRet = vp_kwrap_setpicformatinfo(winid, &bufTiming, &cviInfo);
		vp_kwrap_checktimingchangeforcsc(winid);
		DE_NOTI("win[%d] h/v %d/%d , fr %d/10Hz ,%s[%d], dsc[%d], %s", \
			winid, bufTiming.hActive, bufTiming.vActive, bufTiming.vFreq, \
			(vpInputSrc.Type<SRC_INPUT_DTV)?"phy_port":" ", ghdmiphyport[winid],\
			cur_inf_param.mode.is_dsc, \
			(bufTiming.svp==1)?"svp=1":" ");
#endif

		memcpy(&gbufTiming[winid], &bufTiming, sizeof(kwrap_vp_timing_info_t));

#ifdef INCLUDE_KDRV_PE
		v4l2_vpq_update_inputSrc(vpInputSrc.Type);
		v4l2_vpq_update_vFreq(bufTiming.vFreq);
		v4l2_vpq_update_scanType(bufTiming.scanType);
#endif
#ifdef INCLUDE_KDRV_BE
		v4l2_vpq_detect_vFreq(bufTiming.vFreq);
#endif
		if(winid == 0)
		{
			UINT32 skip_set_frate = (lx_chip() == LX_CHIP_M23 && bufTiming.hActive == 0 && bufTiming.vActive == 0 && bufTiming.vFreq == 0)? 1:0;
			if (!skip_set_frate) {
				_vsc_check_fr(vpInputSrc,bufTiming,&frameRateInfo.frameRate);
				DE_NOTI("set_frate set_frate:%d\n",frameRateInfo.frameRate);
				resource_mgr_ioctl(DE_IOW_SET_FR_RATE,(unsigned long)&frameRateInfo, CALL_FROM_KERNEL);
			}
			else {
				DE_NOTI("skip_set_frate");//TVWBS_23-4970
			}
		}

#ifdef INCLUDE_KDRV_HDMI20
		if(vsc_config[winid].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_HDMI) {
			if(bufTiming.isDSC) {
				iRet = KWARP_HDMI20_RX_Set_ExecuteDscModule(vpInputSrc.Attr);
				if(iRet) DE_ERROR("error from ExecuteDscModule [%d]", iRet);
			}
		}
#endif

		if (winid == 0)
		{
			struct vsc_bwm_cfg bwm_cfg;
			bwm_cfg.size.w = bufTiming.hActive;
			bwm_cfg.size.h = bufTiming.vActive;
			bwm_cfg.size.rate = bufTiming.vFreq;
			vsc_bwm_set_config(VSC_BWM_OPT_SIZE, &bwm_cfg);
		}
	}
	else
	{
		//DE_ERROR("INput is not changed...........\n");
	}
	iRet = vp_kwrap_setinputcsc(winid,&vpInputSrc,&cviInfo);
}


static int _vsc_cvicfgfromcvd(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo, char flag)
{
	int ret = RET_OK;
	const s0_enum *pColorTbl;
	int i;

	/*Harish:: Why are we setting LX_DE_CVI_HDMI_SYNC_MODE??
			   What does really mean by HDMI sync mode.
	*/
	cviInfo->scan = LX_DE_INTERLACED;
	cviInfo->de_mode = LX_DE_CVI_HDMI_SYNC_MODE;

	cviInfo->c_sample = LX_DE_CVI_444; // initial value, SICDTV-15487
	cviInfo->sc_c_sample = LX_DE_SCALER_422;

	if ( cviInfo->de_mode == LX_DE_CVI_HDMI_SYNC_MODE )
	{
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
	}

	switch(flag)
	{
		default:
		case 0:
			pColorTbl = &CVD_COLOR_TYPE[0];
			for (i = 0; i < TBL_NUM(CVD_COLOR_TYPE) ; i++, pColorTbl++)
			{
				if (bufTiming.standard == pColorTbl->PreEnum)
				{
					cviInfo->cvd_color_std = pColorTbl->PostEnum;
					break;
				}
				cviInfo->cvd_color_std = pColorTbl->PostEnum;
			}
			break;
		case 1:
			pColorTbl = &ATV_COLOR_TYPE[0];
			for (i = 0; i < TBL_NUM(ATV_COLOR_TYPE) ; i++, pColorTbl++)
			{
				if (bufTiming.standard == pColorTbl->PreEnum)
				{
					cviInfo->cvd_color_std = pColorTbl->PostEnum;
					break;
				}
				cviInfo->cvd_color_std = pColorTbl->PostEnum;
			}
			break;
	}

	return ret;
}


static int _vsc_cvicfgfromhdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo)
{
	int ret = RET_OK;

	LX_HDMI_ASPECTRATIO_T hdmi_aspectratio = { 0, };
	LX_DE_COLOR_STD_T color = LX_DE_COLOR_RGB;
	LX_DE_SCALER_CSAMPLE_T scaler = LX_DE_SCALER_444;
	LX_DE_CAPACITY_T capa;
	LX_DE_HDMI444_MODE_T hdmi_444_mode = LX_DE_HDMI444_NONE;
	LX_HDMI_COLOR_STATUS_T pColorDomain;
	int cnt;
	LX_DE_CVI_3D_FULL_INFO_T de3DFormatType = LX_DE_CVI_NORMAL_FORMAT;

	cviInfo->c_sample = LX_DE_CVI_444; // initial value, SICDTV-15487

	if (vpSrcId>=LX_DE_WIN_MAX)		{DE_NOTI("vpSrcId(%d) is wrong\n",vpSrcId);return RET_ERROR;}

#ifdef USE_VIDEO_FOR_FPGA
	pColorDomain = LX_HDMI_CS_YCBCR444_709;
#endif

#ifdef INCLUDE_KDRV_HDMI20
	ret = KWARP_HDMI20_RX_GetAspectRatio(vpInputSrc.Attr, &hdmi_aspectratio);
	if(RET_ERROR == ret)
		return ret;
#endif
	{
		cviInfo->size_offset.hsize = bufTiming.hActive;
		cviInfo->size_offset.vsize = bufTiming.vActive;
		DE_NOTI("[%s,%d] source size comes from HDMI module.  h/v [%d/%d]\n",\
			__F__,__L__, bufTiming.hActive, bufTiming.vActive);
	}

	cviInfo->size_offset.hoffset = 0;	//hdmi_time_info.hStart;
	cviInfo->size_offset.voffset = 0;	//hdmi_time_info.vStart;
	cviInfo->de_mode = (bufTiming.isPVOMode) ? LX_DE_CVI_HDMI_SYNC_MODE_PVO : LX_DE_CVI_HDMI_SYNC_MODE;
	cviInfo->scan    = bufTiming.scanType;
	if ( lx_chip_rev( ) >= LX_CHIP_REV(O22,A0) ) {
		cviInfo->bit_res = (LX_DE_CVI_BITRES_T)bufTiming.deepColorMode;
	}

	if (cviInfo->sampling == LX_DE_CVI_DOUBLE_SAMPLING)
	{
		 cviInfo->size_offset.hsize = bufTiming.hActive *2;
	}
	else if (cviInfo->sampling == LX_DE_CVI_QUAD_SAMPLING)
	{
		cviInfo->size_offset.hsize = bufTiming.hActive *4;
	}

	/* Get VP to CVI 3D format conversion */
	//cviInfo->trid_full_format = vp_kwrap_getdefull3dformattype(bufTiming.extInfo);

	if (bufTiming.extInfo== VP_EXT_3D_FRAME_PACKING)
		de3DFormatType = LX_DE_CVI_3D_FRAMEPACK;
	else if (bufTiming.extInfo == VP_EXT_3D_FIELD_ALTERNATIVE)
		de3DFormatType = LX_DE_CVI_3D_FIELD_ALTERNATIVE;
	else if (bufTiming.extInfo == VP_EXT_3D_LINE_ALTERNATIVE_FULL)
		de3DFormatType = LX_DE_CVI_3D_ROW_INTERLEAVING;
	else if (bufTiming.extInfo == VP_EXT_3D_SIDEBYSIDE_FULL)
		de3DFormatType = LX_DE_CVI_3D_SBSFULL;
	else if (bufTiming.extInfo == VP_EXT_4K_2K)
		de3DFormatType = LX_DE_CVI_4K_2K;

	cviInfo->trid_full_format = de3DFormatType;
	ret = de_kwrap_getcapacity(&capa);

	//vp_kwrap_gethdmicolormetry(vpSrcId, &color, &scaler);
#ifdef INCLUDE_KDRV_HDMI20
	ret = KWARP_HDMI20_RX_GetColorDomain(vpInputSrc.Attr, &pColorDomain);
#endif
	for(cnt=0;cnt < (sizeof(HDMI_COLORMETRY_MAP)/sizeof(kwrap_vp_hdmi_color_map_t));cnt++)
	{
		if(HDMI_COLORMETRY_MAP[cnt].hdmi_colormetry == pColorDomain){
			color = HDMI_COLORMETRY_MAP[cnt].color;
			scaler= HDMI_COLORMETRY_MAP[cnt].scaler;
			break;
		}
	}
	cviInfo->color = color;
	if(cviInfo->color == LX_DE_COLOR_RGB)
		cviInfo->c_sample = LX_DE_CVI_444;
	cviInfo->sc_c_sample = scaler;
	if (hdmi_aspectratio.eAspectRatio == LX_HDMI_AVI_PICTURE_ARC_16_9)
		cviInfo->aspect = LX_DE_AR_16_9;
	else
		cviInfo->aspect = LX_DE_AR_4_3;

	/* 1. sc_c_sample: for hdmi 444 mode of user */
	de_kwrap_gethdmi444mode(vpSrcId, &hdmi_444_mode);

	if(cviInfo->sc_c_sample == LX_DE_SCALER_420)
		cviInfo->c_sample = LX_DE_CVI_420;
	else if(cviInfo->sc_c_sample == LX_DE_SCALER_422)
		cviInfo->c_sample = LX_DE_CVI_422;

	if (hdmi_444_mode == LX_DE_HDMI444_ON){
		cviInfo->sc_c_sample = LX_DE_SCALER_444;
	}
	else if (hdmi_444_mode == LX_DE_HDMI444_OFF)
	{
		if ( lx_chip_rev( ) >= LX_CHIP_REV(E60,A0) ) {
			cviInfo->sc_c_sample = LX_DE_SCALER_422;
		}
		else {
			if(cviInfo->size_offset.vsize < 2200)/*4k only*/ {
				cviInfo->sc_c_sample = LX_DE_SCALER_422;
			}
		}
	}

	/* 2. chip limitation. */
	if (cviInfo->sc_c_sample == LX_DE_SCALER_444 && cviInfo->scan == LX_DE_INTERLACED)
	{
		cviInfo->sc_c_sample = LX_DE_SCALER_422;	// L8/L9 HW constraint
	}

	/* HDMI2.0 422 w/o (time:357/367) */
	if(bufTiming.pixelRepeat){
		if(capa.chip_id == 4) cviInfo->c_sample = LX_DE_CVI_422;
		cviInfo->sampling = LX_DE_CVI_DOUBLE_SAMPLING;
		cviInfo->size_offset.hsize = bufTiming.hActive *2;
	}

	/* game mode info from HDMI2.1 (webos4.5) */
	cviInfo->cvi_game_info.isFreeSyncMode = bufTiming.isFreeSyncMode;
	cviInfo->cvi_game_info.isGSyncMode    = bufTiming.isGSyncMode;
	cviInfo->cvi_game_info.isVrrMode      = bufTiming.isVrrMode;
	cviInfo->cvi_game_info.isFvaMode      = bufTiming.isFvaMode;
	cviInfo->cvi_game_info.isMConst       = bufTiming.isMConst;

	cviInfo->cvi_frl_info.pixelClock     = bufTiming.pixelClock;
	cviInfo->cvi_frl_info.phyMode        = bufTiming.phyMode;
	cviInfo->avi_colorspace_info         = bufTiming.avi_colorspace;

	DE_NOTI("-----------------------------------------\n");
	DE_NOTI("wid:%d, port:%d, cvi_h,v:%d,%d\n",vpSrcId,vpInputSrc.Attr,cviInfo->size_offset.hsize,cviInfo->size_offset.vsize);
	DE_NOTI("c_sample:%d, sc_c_sample:%d by hdmi444md:%d bit:%d\n",cviInfo->c_sample,cviInfo->sc_c_sample,hdmi_444_mode,cviInfo->bit_res);
	DE_NOTI("domain:%d, color:%d, scaler:%d, csc:%d\n",pColorDomain,color,scaler, bufTiming.avi_colorspace);
	DE_NOTI("timing: %d x %d (%d), repeat:%d\n",bufTiming.hActive,bufTiming.vActive,bufTiming.vFreq,bufTiming.pixelRepeat);
	DE_NOTI("fsync:%d, gsync:%d, vrr:%d, fva:%d, mconst[%d]\n",\
		bufTiming.isFreeSyncMode,bufTiming.isGSyncMode,bufTiming.isVrrMode,bufTiming.isFvaMode,bufTiming.isMConst);
	DE_NOTI("pixelClock:%d, phyMode:%d, dsc:%d\n",bufTiming.pixelClock, bufTiming.phyMode, bufTiming.isDSC);
	DE_NOTI("-----------------------------------------\n");

	return ret;
}

static int _vsc_cvicfgfromadc(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;

	cviInfo->c_sample = LX_DE_CVI_444; // initial value, SICDTV-15487

	if ( cviInfo->size_offset.hsize > DE_MAX_INPUT_HSIZE  || cviInfo->size_offset.vsize > DE_MAX_INPUT_VSIZE )
	{
		cviInfo->size_offset.hsize = 0;
		cviInfo->size_offset.vsize = 0;
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
		cviInfo->scan = LX_DE_INTERLACED;
	}

	if (cviInfo->size_offset.hsize >= DE_H1024_IS_HD ) //HD format criteria of L8 DE
	{
		cviInfo->color = LX_DE_COLOR_709;
		cviInfo->aspect = LX_DE_AR_16_9;
	}
	else // SD
	{
		cviInfo->color = LX_DE_COLOR_601;
		cviInfo->aspect = LX_DE_AR_4_3;
	}

	return ret;
}

#define u16CHK_RANGE(X,Y,offset)		((UINT16) ((X) + (offset) - (Y)) <= (offset*2))

static int _vsc_check_fr(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t srcTiming, UINT16 *frameRate)
{
	if(!frameRate) return -1;

	if(srcTiming.vFreq > 900)
	{
		srcTiming.vFreq = srcTiming.vFreq >> 1;
		if (u16CHK_RANGE(srcTiming.vFreq,500,5))
			*frameRate = 50;
		else if (u16CHK_RANGE(srcTiming.vFreq,600,5))
			*frameRate = 60;
	}
	else if (srcTiming.vFreq > 550)
	{
		*frameRate = 60;
	}
	else
	{
		if (u16CHK_RANGE(srcTiming.vFreq,500,5) || u16CHK_RANGE(srcTiming.vFreq,250,5))
			*frameRate = 50;
		else if (u16CHK_RANGE(srcTiming.vFreq,600,5) || u16CHK_RANGE(srcTiming.vFreq,300,5))
			*frameRate = 60;
		else
		{
			if ( (vpInputSrc.Type > SRC_INPUT_YPBPR) && (vpInputSrc.Type < SRC_INPUT_HDMI) )
				*frameRate = 60;
			else
			{
				if (u16CHK_RANGE(srcTiming.vFreq,240,5) && _g_prev_pulldown==1)//&& (TRUE == _KADP_VP_CheckPullDownMode()))
					*frameRate = 48;
				else
					*frameRate = 60;
			}
		}
	}

	 if (vpInputSrc.Type == SRC_INPUT_VGA)
		*frameRate = 60;

	//DE_NOTI("[VP] Retuen Frame Rate[%d] vFreq[%d/10]\n", *frameRate, srcTiming.vFreq);

	return RET_OK;
}

static int _hex11bit2int(UINT32 hex_number)
{
	UINT32 hex_tmp;
	hex_tmp = (hex_number + 0x400) & 0x7FF;
	return (int)hex_tmp - 0x400;
}

static int _hex15bit2int(UINT32 hex_number)
{
	UINT32 hex_tmp;
	hex_tmp = (hex_number + 0x4000) & 0x7FFF;
	return (int)hex_tmp - 0x4000;
}

#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#endif
static void _read32(unsigned int addr, unsigned int *data)
{
	#ifdef INCLUDE_KDRV_SYS
	int ret = 0;
	ret = SYS_IO_ReadRegArray(addr, 4, (void *)data);
	#endif
}
static void _write32(unsigned int addr, unsigned int data)
{
	#ifdef INCLUDE_KDRV_SYS
	SYS_IO_WriteRegArray(addr, 4, &data);
	#endif
}
static int _vsc_read_cvi_pixel(LX_DE_CVI_RW_VIDEO_FRAME_T param, int cvi_b_mode)
{
#define GRAB_NOTI if(0) DE_NOTI

	int ret = RET_ERROR;

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
	UINT32 cvi_base_diff = 0, offset_pix_sum;
	UINT32 hoffset, voffset;
	UINT32 o20_hdmi_clk = 0;

	if ( lx_chip_rev( ) >= LX_CHIP_REV(O24,A0) )
		cvi_base_diff = 0x04CC0000;
	else if ( lx_chip_rev( ) >= LX_CHIP_REV(M23,A0) )
		cvi_base_diff = 0x04690000;
	else if ( lx_chip_rev( ) >= LX_CHIP_REV(O22,A0) )
		cvi_base_diff = 0x04840000;
	else if ( lx_chip_rev( ) >= LX_CHIP_REV(M17,A0) )
		cvi_base_diff = 0x01000000;
	else
		cvi_base_diff = 0x0;

	if ( lx_chip_rev( ) >= LX_CHIP_REV(O20,A0) )
		offset_pix_sum = 4;
	else
		offset_pix_sum = 0;


	if (cvi_b_mode > 0)
		cvi_b_offset = 0x100;

	_read32(0xC8000200 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// TOP_CTRL
	data_in_sel = (reg_read_tmp >> 14) & 0xf;
	data_en_mode = (reg_read_tmp >> 31) & 0x1;

	_read32(0xC8000208 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// SIZE_CTRL
	h_size = reg_read_tmp & 0x1fff;

	if( (data_in_sel == 9) && (h_size == 1440) )	//Component AND pixel repeatation mode ?
		param.region.pixelGrabX = param.region.pixelGrabX << 1;

	//if ( lx_chip_rev( ) >= LX_CHIP_REV(O20,A0) && lx_chip_rev( ) < LX_CHIP_REV(M23,A0)) {
	if (LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23)) { // o20, o22, o24
		if((data_in_sel != 8)&&(data_in_sel != 9)) // hdmi only
		{
			o20_hdmi_clk = 2;
		}
	}

	if( data_en_mode == 1)
	{
		_read32(0xC8000248 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// OFFSET_READ

		hoffset = reg_read_tmp & 0x1FFF;
		voffset = (reg_read_tmp >> 16) & 0x1FFF;
	}
	else
	{
		_read32(0xC8000204 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// OFFSET_CTRL

		hoffset = reg_read_tmp & 0x1FFF;
		voffset = (reg_read_tmp >> 16) & 0x1FFF;
	}

	GRAB_NOTI("[kadp_de] win %d, (x,y,w,h)=(%d,%d,%d,%d), bReadOnOff = %d\n", param.region.win_id,
			param.region.pixelGrabX,
			param.region.pixelGrabY,
			param.region.pixelGrabW,
			param.region.pixelGrabH,
			param.bReadOnOff);

	param.region.pixelGrabX = param.region.pixelGrabX >> o20_hdmi_clk;  // o20 hdmi only ?

	_read32(0xC8000268 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp & 0x80000000;
	reg_write_tmp |= 0x00008000;
	_write32(0xC8000268 + cvi_base_diff + cvi_b_offset, reg_write_tmp);	// Enable pixel sum

	_read32(0xC8000268 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp | (param.region.pixelGrabX + hoffset) | ( (param.region.pixelGrabX + hoffset + param.region.pixelGrabW - 1) << 16);
	_write32(0xC8000268 + cvi_base_diff + cvi_b_offset, reg_write_tmp);	// enter start_pos_x and end_pos_x

	reg_write_tmp = (param.region.pixelGrabY + voffset) | ( (param.region.pixelGrabY + voffset + param.region.pixelGrabH - 1) << 16);
	_write32(0xC800026C + cvi_base_diff + cvi_b_offset, reg_write_tmp);	// enter start_pos_x and end_pos_x

	msleep(100);

	_read32(0xC8000270 + cvi_base_diff + cvi_b_offset + offset_pix_sum, &reg_read_tmp);	// PIX_SUM_STATUS0
	PixelSumY = reg_read_tmp;
	_read32(0xC8000274 + cvi_base_diff + cvi_b_offset + offset_pix_sum, &reg_read_tmp);	// PIX_SUM_STATUS1
	PixelSumCb = reg_read_tmp;
	_read32(0xC8000278 + cvi_base_diff + cvi_b_offset + offset_pix_sum, &reg_read_tmp);	// PIX_SUM_STATUS2
	PixelSumCr = reg_read_tmp;

	GRAB_NOTI("[kadp_de] (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelSumY,
			PixelSumCb,
			PixelSumCr);

	PixelY = PixelSumY / (param.region.pixelGrabH * param.region.pixelGrabW);
	PixelCb = PixelSumCb / (param.region.pixelGrabH * param.region.pixelGrabW);
	PixelCr = PixelSumCr / (param.region.pixelGrabH * param.region.pixelGrabW);

	GRAB_NOTI("[kadp_de] Before CSC (Y,Cb,Cr)=(%d,%d,%d)\n",
			PixelY, PixelCb, PixelCr);

	_read32(0xC8000240 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL7
	CSC_Enable = (reg_read_tmp >> 1) & 0x1;

	if(CSC_Enable == 1)
	{
		_read32(0xC8000224 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL0
		csc_coeff_1 = _hex15bit2int(reg_read_tmp & 0x7FFF);
		csc_coeff_0 = _hex15bit2int( (reg_read_tmp >> 16) & 0x7FFF );

		_read32(0xC8000228 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL1
		csc_coeff_3 = _hex15bit2int(reg_read_tmp & 0x7FFF);
		csc_coeff_2 = _hex15bit2int( (reg_read_tmp >> 16) & 0x7FFF );

		_read32(0xC800022C + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL2
		csc_coeff_5 = _hex15bit2int(reg_read_tmp & 0x7FFF);
		csc_coeff_4 = _hex15bit2int( (reg_read_tmp >> 16) & 0x7FFF );

		_read32(0xC8000230 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL3
		csc_coeff_7 = _hex15bit2int(reg_read_tmp & 0x7FFF);
		csc_coeff_6 = _hex15bit2int( (reg_read_tmp >> 16) & 0x7FFF );

		_read32(0xC8000234 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL4
		csc_off_0 = _hex11bit2int(reg_read_tmp & 0x7FF);
		csc_coeff_8 = _hex15bit2int( (reg_read_tmp >> 16) & 0x7FFF );

		_read32(0xC8000238 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL5
		csc_off_2 = _hex11bit2int(reg_read_tmp & 0x7FF);
		csc_off_1 = _hex11bit2int( (reg_read_tmp >> 16 ) & 0x7FF);

		_read32(0xC800023C + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL6
		csc_off_4 = _hex11bit2int(reg_read_tmp & 0x7FF);
		csc_off_3 = _hex11bit2int( (reg_read_tmp >> 16 ) & 0x7FF);

		_read32(0xC8000240 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// CSC_CTRL6
		csc_off_5 = _hex11bit2int( (reg_read_tmp >> 16 ) & 0x7FF);

		PixelY_CSC = (int)( csc_coeff_0*(PixelY + csc_off_0) + csc_coeff_1*(PixelCb + csc_off_1) + csc_coeff_2*(PixelCr + csc_off_2)) / 4096 + csc_off_3;
		PixelCb_CSC = (int)( csc_coeff_3*(PixelY + csc_off_0) + csc_coeff_4*(PixelCb + csc_off_1) + csc_coeff_5*(PixelCr + csc_off_2)) / 4096 + csc_off_4;
		PixelCr_CSC = (int)( csc_coeff_6*(PixelY + csc_off_0) + csc_coeff_7*(PixelCb + csc_off_1) + csc_coeff_8*(PixelCr + csc_off_2) ) / 4096 + csc_off_5;

		GRAB_NOTI("[kadp_de] csc_coeff_0(%d),_1(%d),_2(%d)\n", csc_coeff_0, csc_coeff_1, csc_coeff_2);
		GRAB_NOTI("[kadp_de] csc_coeff_3(%d),_4(%d),_5(%d)\n", csc_coeff_3, csc_coeff_4, csc_coeff_5);
		GRAB_NOTI("[kadp_de] csc_coeff_6(%d),_7(%d),_8(%d)\n", csc_coeff_6, csc_coeff_7, csc_coeff_8);
		GRAB_NOTI("[kadp_de] csc_offset_0(%d),_1(%d),_2(%d)\n", csc_off_0, csc_off_1, csc_off_2);
		GRAB_NOTI("[kadp_de] csc_offset_3(%d),_4(%d),_5(%d)\n", csc_off_3, csc_off_4, csc_off_5);
	}
	else
	{
		GRAB_NOTI("[kadp_de] CSC Bypass !!! \n");
	}

	if(PixelY_CSC < 0)
		PixelY_CSC = 0;
	if(PixelCb_CSC <0)
		PixelCb_CSC = 0;
	if(PixelCr_CSC < 0)
		PixelCr_CSC = 0;

	GRAB_NOTI("[kadp_de] After CSC (Y,Cb,Cr)=(%d,%d,%d)\n",
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

	_read32(0xC8000268 + cvi_base_diff + cvi_b_offset, &reg_read_tmp);	// PIX_SUM_CTRL0
	reg_write_tmp = reg_read_tmp & 0xFFFF7FFF;
	_write32(0xC8000268 + cvi_base_diff + cvi_b_offset, reg_write_tmp);	// Disable pixel sum

	ret = RET_OK;

	return ret;
}

int test_read_cvi_pixel_BarPixelGrab(void)
{
	UINT32	array_colorbar_level_Y[8] = {0,};
	UINT32	array_colorbar_level_Cb[8] = {0,};
	UINT32	array_colorbar_level_Cr[8] = {0,};
	UINT32 hActive, vActive, scanType;
	int					ret = RET_OK;
	UINT32 				vpSrcId;
	UINT32 x_pos,y_pos,width,height,i,j;
	int colorbar_count, colorbar_max, block_size;
	BOOLEAN bReadOnOff;
	LX_DE_GRAB_COLOR_T *pRead=NULL;
	LX_DE_CVI_RW_VIDEO_FRAME_T cvi_video_frame_buffer;
	//LX_DE_CVI_CAPTURE_FREEZE_T cvi_cap_freeze;
	//int rc;

	DE_NOTI("8 Color Bar pixel grab\n");

	vpSrcId = 0;

	hActive = gbufTiming[0].hActive;
	vActive = gbufTiming[0].vActive;
	scanType = gbufTiming[0].scanType;

	DE_NOTI(" hActive = %d \n", hActive);
	DE_NOTI(" vActive = %d \n", vActive);
	DE_NOTI(" scanType= %d (%s)\n", scanType, scanType ? "PROG":"INTR");

	width = 10;
	height = 10;
	colorbar_max = 8;
	block_size = hActive / colorbar_max;

	//It is always true

	bReadOnOff = TRUE;
	pRead = (LX_DE_GRAB_COLOR_T *)malloc(width*height*sizeof(LX_DE_GRAB_COLOR_T));

	if (!pRead)
	{
		DE_NOTI("^R^ERROR!!! [%s:%d] pRead, malloc fail.", __FUNCTION__, __LINE__);
		goto func_exit;
	}

	DE_NOTI(" ========================\n");

	for (colorbar_count = 0; colorbar_count <colorbar_max; colorbar_count++)
	{
		x_pos = (block_size * colorbar_count) + (block_size>>1);
		if (scanType)
			y_pos = vActive/2;
		else
			y_pos = vActive/4;

		cvi_video_frame_buffer.region.win_id = LX_DE_WIN_MAIN;
		cvi_video_frame_buffer.region.pixelGrabX = x_pos;
		cvi_video_frame_buffer.region.pixelGrabY = y_pos;
		cvi_video_frame_buffer.region.pixelGrabW = width;
		cvi_video_frame_buffer.region.pixelGrabH = height;
		cvi_video_frame_buffer.region.colorDepth = 1; //10bits

		cvi_video_frame_buffer.bReadOnOff = bReadOnOff;

		if (bReadOnOff)
		{
			cvi_video_frame_buffer.color = (LX_DE_GRAB_COLOR_T *)pRead;
		}

		if( lx_chip_rev() >= LX_CHIP_REV(M17,C0))	//If M17C0, O18
		{
			//rc = KADP_DE_Read_CviVideoFrameBuffer_4K(cvi_video_frame_buffer, 0, 0, 0);
			_vsc_read_cvi_pixel(cvi_video_frame_buffer, 0);
		}

		if (bReadOnOff)
		{
			for (i=0; i<height; i++)
			{
				//											DE_NOTI("\n row[%03d] ",i);
				for (j=0;j<width;j++)
				{
					array_colorbar_level_Y[colorbar_count] += (pRead +j+i)->pixelGrabY;
					array_colorbar_level_Cb[colorbar_count] +=(pRead +j+i)->pixelGrabCb;
					array_colorbar_level_Cr[colorbar_count] += (pRead +j+i)->pixelGrabCr;
				}
			}
		}

		array_colorbar_level_Y[colorbar_count] /= (height * width);
		array_colorbar_level_Cb[colorbar_count] /= (height * width);
		array_colorbar_level_Cr[colorbar_count] /= (height * width);

		DE_NOTI("[%d][G:%03d][B:%03d][R:%03d]", colorbar_count,\
			array_colorbar_level_Y[colorbar_count],\
			array_colorbar_level_Cb[colorbar_count],\
			array_colorbar_level_Cr[colorbar_count]);
	}

	DE_NOTI(" ========================\n");

func_exit:
	if (pRead)	{free(pRead);pRead=NULL;}
	return ret;
}

struct v4l2_ext_vsc_input_src_info vsc_v4l2_get_input(UINT8 win)
{
	struct v4l2_ext_vsc_input_src_info input_type;

	//input_type.src = vsc_config[win].inout_info.in.src;
	memcpy((void *)&input_type,(void *)&vsc_config[win].inout_info.in,sizeof(struct v4l2_ext_vsc_input_src_info));
	return input_type;
}

int vsc_get_timinginfo(UINT8 win, kwrap_vp_timing_info_t *ti)
{
	int ret = 0;
	if(!ti) return RET_ERROR;
	if(win>=LX_DE_WIN_MAX) return RET_ERROR;

	memcpy(ti, &gbufTiming[win], sizeof(kwrap_vp_timing_info_t));
	ti->cp_streaming = (UINT32)vsc_config[win].seamless;
	ti->hdr_type     = (UINT32)vsc_config[win].hdr_type;
	return ret;
}

int vsc_get_submode(unsigned int *sub_mode)
{
	*sub_mode = (unsigned int)vsc_config[0].sub_mode.win_mode;
	return 0;
}

int vsc_set_fbpos(enum vsc_feedback_position pos)
{
	// 0:fb disable (ATV Rec.) 1:video only, 2:with osd, 3:osd ony
	vsc_config[0].pos = pos;
	return 0;
}

int vsc_get_dev_info(int win, int param)
{
	int ret = -1;

	if (win >= LX_DE_WIN_MAX) {
		return -1;
	}

	switch(param)
	{
		case vdev_open:
			ret = vsc_config[win].open; break;
		case connect_src:
			ret = vsc_config[win].inout_info.in.src; break;
		case connect_index:
			ret = vsc_config[win].inout_info.in.index; break;
		case connect_attr:
			ret = vsc_config[win].inout_info.in.attr; break;
		case output_mode:
			ret = vsc_config[win].inout_info.out; break;
		case mute:
			ret = vsc_config[win].mute; break;
		case hdr:
			ret = vsc_config[win].hdr_type; break;
		case source_x:
			ret = vsc_config[win].win_info.in.res.x; break;
		case source_y:
			ret = vsc_config[win].win_info.in.res.y; break;
		case source_w:
			ret = vsc_config[win].win_info.in.res.w; break;
		case source_h:
			ret = vsc_config[win].win_info.in.res.h; break;
		case crop_x:
			ret = vsc_config[win].win_info.in.crop.x; break;
		case crop_y:
			ret = vsc_config[win].win_info.in.crop.y; break;
		case crop_w:
			ret = vsc_config[win].win_info.in.crop.w; break;
		case crop_h:
			ret = vsc_config[win].win_info.in.crop.h; break;
		case out_x:
			ret = vsc_config[win].win_info.out.x; break;
		case out_y:
			ret = vsc_config[win].win_info.out.y; break;
		case out_w:
			ret = vsc_config[win].win_info.out.w; break;
		case out_h:
			ret = vsc_config[win].win_info.out.h; break;
		case rotation:
			ret = vsc_config[win].win_info.rotation; break;
		case freeze:
			ret = vsc_config[win].freeze; break;
		case rgb444:
			ret = vsc_config[win].rgb444; break;
		case adaptive:
			ret = vsc_config[win].seamless; break;
		case frame_delay:
			ret = vsc_config[win].frame_delay; break;
		case property_window:
			ret = vsc_config[win].sub_mode.win_mode; break;
		case property_mirror:
			ret = vsc_config[win].sub_mode.mirror_mode; break;
		case property_memory:
			ret = vsc_config[win].sub_mode.mem_type; break;
		case zorder_value:
			ret = vsc_config[win].order.zorder; break;
		case zorder_alpha:
			ret = vsc_config[win].order.alpha; break;
		case pattern:
			ret = vsc_config[win].pat; break;
		case limited_win_ratio_h_scaleup:
		case limited_win_ratio_v_scaleup:
		case limited_win_ratio_h_scaledown:
		case limited_win_ratio_v_scaledown:
			ret = 0; break;
		case socts_option:
			ret = vsc_config[win].socts; break;
		default:
			ret = 0; break;
	}
	return ret;
}

#ifdef INCLUDE_KDRV_PE
extern int vpq_hwrap_getblackleveltype(UINT32 wId);
#endif
/* if skip or no err, return 0 */
int vsc_check_csc_err(char *str)
{
	int ret = 0;
	unsigned int mute;
	int csc_type0,csc_type1;//0;ycbcr, 1:rgb
	int is_mismatch = 0;
	int colordomain,blackleveltype;
	enum v4l2_ext_vsc_input_src src;
	static int pre_blackleveltype = -1;
	static int pre_colordomain = -1;

	#ifdef INCLUDE_KDRV_PE
	src = vsc_config[0].inout_info.in.src;

	if (!str)	return ret;
	if (src != V4L2_EXT_VSC_INPUT_SRC_HDMI)	return ret;

	ipc_phys_hal_CheckMute(0,&mute);
	if (mute > 0)	return ret;

	colordomain = (int)vsc_config[0].colordomain;//see LX_HDMI_COLOR_STATUS_T
	blackleveltype = vpq_hwrap_getblackleveltype(0);//see enum v4l2_ext_vpq_black_level_type

	if (pre_colordomain==colordomain && pre_blackleveltype==blackleveltype)	return ret;

	switch (colordomain)
	{
		case LX_HDMI_CS_FULL_RGB:
		case LX_HDMI_CS_LIMITED_RGB:
		case LX_DVI_CS_FULL_RGB:
			csc_type0 = 1;
			break;
		default:
			csc_type0 = 0;
			break;
	}

	switch (blackleveltype)
	{
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LINEAR_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LIMIT_HIGH:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LINEAR_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LIMIT_HIGH:
			csc_type1 = 1;
			break;
		default:
			csc_type1 = 0;
			break;
	}
	if (csc_type0!=csc_type1)	 is_mismatch = 1;

	DE_NOTI("RPT_CSC : %s, HDMI:%s(%d), PQ:%s(%d)\n",(!is_mismatch)? "OK":"ERR",\
		(!csc_type0)? "YUV":"RGB",colordomain,(!csc_type1)? "YUV":"RGB",blackleveltype);

	if (is_mismatch > 0)
	{
		snprintf(str,64,"RPT_CSC : %s, HDMI:%s(%d), PQ:%s(%d)",(!is_mismatch)? "OK":"ERR",\
			(!csc_type0)? "YUV":"RGB",colordomain,(!csc_type1)? "YUV":"RGB",blackleveltype);
		ret = -1;
	}

	pre_colordomain = colordomain;
	pre_blackleveltype = blackleveltype;
	#endif

	return ret;
}

#include "mcu/de_ipc.h"
int vsc_check_fw_err(char *str)
{
	int ret = 0;

	if(!str) return -1;
	ret = VIDEO_Err_String_From_MCU(str);
	if(str[0] == 0)
		ret = 0; // no errors
	else
		ret = 1;
	return ret;
}

int vsc_check_cvi_err(char *str)
{
	int ret = 0;
	unsigned int mute = 0;
	static unsigned int prev_mute = 0;
	unsigned int str_len;
	char meta_err[] = "HDMI Dolby vision - meta_data error by source";
	char signal_err[] = "invalid cvi signal detected from external inputs";
	char no_signal[] = "no signal";

	if(!str) return -1;
	if(vsc_config[0].mute == 0) { // in case of global mute-off
		ipc_phys_hal_CheckMute(0,&mute);
		if(mute == 56) { // HDMI dolby vision meta error
			str_len = sizeof(meta_err);
			if(str_len > 64) str_len = 64;
			memcpy(str, meta_err, str_len);
		}
		else if(mute == 2 || (mute > 104 && mute < 146)) { // <CVI>
			str_len = sizeof(signal_err);
			if(str_len > 64) str_len = 64;
			memcpy(str, signal_err, str_len);
			mute = 2;
		}
		else if(mute > 25000) { // no signal (25xxx)
			str_len = sizeof(no_signal);
			if(str_len > 64) str_len = 64;
			memcpy(str, no_signal, str_len);
			mute = 25001;
		}
	}
	if(str[0] == 0)
		ret = 0; // no errors
	else {
		if(mute != prev_mute)
			ret = 1;
	}
	prev_mute = mute;
	return ret;
}

int vsc_check_vrr_freq(unsigned int *p) // To display current input frequency of vrr
{
	int ret = 0;
	LX_DE_FW_STATUS_REG_T fw_status;

	if(!p) return -1;
	ret = ipc_phys_hal_CheckFwStatus(0, (void *)&fw_status);
	*p = fw_status.reg_1.frate_vrr;

	return ret;
}
int vsc_external_library(UINT16 wId, UINT16 afd, UINT16 par_width, UINT16 par_height, LX_DE_WIN_INFO_T *win_info)
{
	int ret = 0;
#define PANNEL_WIDTH   3840
#define PANNEL_HEIGHT  2160

	win_info->wId = wId;
	win_info->rot = (LX_DE_ROTATE_INFO_T)vsc_config[wId].win_info.rotation;
	win_info->in_size.w = vsc_config[wId].win_info.in.res.w;
	win_info->in_size.h = vsc_config[wId].win_info.in.res.h;
	win_info->in_win.x  = vsc_config[wId].win_info.in.crop.x;
	win_info->in_win.y  = vsc_config[wId].win_info.in.crop.y;
	win_info->in_win.w  = vsc_config[wId].win_info.in.crop.w;
	win_info->in_win.h  = vsc_config[wId].win_info.in.crop.h;
	win_info->out_win.x = vsc_config[wId].win_info.out.x;
	win_info->out_win.y = vsc_config[wId].win_info.out.y;
	win_info->out_win.w = vsc_config[wId].win_info.out.w;
	win_info->out_win.h = vsc_config[wId].win_info.out.h;
	win_info->resize_ani_flag = 0;
	
	if ((PANNEL_WIDTH*win_info->in_size.h) > (PANNEL_HEIGHT*win_info->in_size.w))
	{
		// portrait
		win_info->out_win.h = PANNEL_HEIGHT;
		win_info->out_win.w = (PANNEL_HEIGHT*vsc_config[0].win_info.in.res.w)/vsc_config[0].win_info.in.res.h;
		win_info->out_win.y = 0;
		win_info->out_win.x = (PANNEL_WIDTH-vsc_config[0].win_info.in.res.w)/2;
	}
	else
	{
		// landscape
		win_info->out_win.w = PANNEL_WIDTH;
		win_info->out_win.h = (PANNEL_WIDTH*vsc_config[0].win_info.in.res.h)/vsc_config[0].win_info.in.res.w;
		win_info->out_win.y = (PANNEL_HEIGHT-win_info->out_win.h)/2;
		win_info->out_win.x = 0;
	}
	return ret;
}

int vsc_handle_darc_event(void)
{

	int ret = 0;
	int i = 0;
	LX_DE_WIN_INFO_T win_info;
	LX_DE_SRC_STATUS_T srcStatus;

//#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
	struct v4l2_ext_video_rect src;
	struct v4l2_ext_video_rect calculated_input_rect;
	struct v4l2_ext_video_rect calculated_output_rect, out_win;
	struct v4l2_ext_vsc_orbit_window orbit_window;
	struct v4l2_ext_vsc_orbit_move calculated_orbit_move;
	//ASPECTRATIO_CALLBACK_T * pfn;
//#endif
	srcStatus.status_type = LX_DE_SRC_STATUS_VDEC_INFO;
	srcStatus.inSrc[0] = 0;
	srcStatus.inSrcPort[0] = 0;

	do {
//#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
		if(vsc_config[i].inout_info.in.src == V4L2_EXT_VSC_INPUT_SRC_NONE) continue;
		DE_NOTI("vsc_config[%d].seamless = %d", i, vsc_config[i].seamless);
		if(vsc_config[i].seamless != 2) continue;
		srcStatus.win_id = i;
		srcStatus.inSrcPort[i] = i;
		ret = de_kwrap_getsourcestatus(&srcStatus);

		DE_NOTI("event from pqe fw(%d): afd[%d]par[%dx%d] src[%dx%d] fr[%d]", i, \
			srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height, \
			srcStatus.vdecInfo.h_size,srcStatus.vdecInfo.v_size, srcStatus.vdecInfo.v_freq);

		if(vsc_config[i].seamless == 2) {
			src.x = 0;
			src.y = 0;
			src.w  = srcStatus.vdecInfo.h_size;
			src.h = srcStatus.vdecInfo.v_size;
			src.x = src.y = 0;
			out_win.x = vsc_config[i].aspectratio_policy.out.x;
			out_win.y = vsc_config[i].aspectratio_policy.out.y;
			out_win.w = vsc_config[i].aspectratio_policy.out.w;
			out_win.h = vsc_config[i].aspectratio_policy.out.h;
			if(src.w == 0 || src.h == 0){DE_ERROR("invalid src size[%d/%d] return", src.w, src.h);return 0;}

			srcStatus.vdecInfo.par_width = (srcStatus.vdecInfo.par_width==0)?1:srcStatus.vdecInfo.par_width;
			srcStatus.vdecInfo.par_height = (srcStatus.vdecInfo.par_height==0)?1:srcStatus.vdecInfo.par_height;
			DE_NOTI("wid[%d], system_policy.out[%dx%d] justscan[%d], aspect_ratio[%d] rotate[%d] : afd[%d]par[%dx%d]", i, out_win.w, \
				out_win.h, vsc_config[i].aspectratio_policy.setting_policy.just_scan,vsc_config[i].aspectratio_policy.setting_policy.aspect_ratio, \
				vsc_config[i].aspectratio_policy.setting_policy.rotate, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height);
#ifdef VSC_ASPECTRATIO_DRV_CALCULATE_WINDOW
			vsc_AspectratioCallbackFp = (ASPECTRATIO_CALLBACK_T *)vsc_getAspectratioCallbackFp();
			if(vsc_AspectratioCallbackFp == NULL) {DE_ERROR("pfn is NULL");continue;}
			ret = vsc_AspectratioCallbackFp->pfnAspectratiodrvCalculate(src, out_win, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height, \
				vsc_config[i].aspectratio_policy.system_policy, vsc_config[i].aspectratio_policy.setting_policy, &calculated_input_rect, &calculated_output_rect);
			if(ret) {
				DE_ERROR("ret erorr aspectratiodrvCalculateWindow win_id[%d]", i);
				break;
			}

			win_info.in_size.x = 0;
			win_info.in_size.y = 0;
			win_info.in_size.w = srcStatus.vdecInfo.h_size;
			win_info.in_size.h = srcStatus.vdecInfo.v_size;
			
			win_info.in_win.x = calculated_input_rect.x;
			win_info.in_win.y = calculated_input_rect.y;
			win_info.in_win.w = calculated_input_rect.w;
			win_info.in_win.h = calculated_input_rect.h;

			win_info.out_win.x = calculated_output_rect.x;
			win_info.out_win.y = calculated_output_rect.y;
			win_info.out_win.w = calculated_output_rect.w;
			win_info.out_win.h = calculated_output_rect.h;
			win_info.wId = i;
			win_info.rot = 0;
			win_info.resize_ani_flag = 0;

			if(i == 2 && vsc_config[i].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
				win_info.wId = LX_DE_WIN_3;
			if(i == 3 && vsc_config[i].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
				win_info.wId = LX_DE_WIN_4;

			resource_mgr_ioctl(DE_IOW_SET_WIN_INFO,(unsigned long)&win_info,1);
			DE_NOTI("win[%d] src %dx%d , in win=%dx%d(%d,%d) , out win=%dx%d(%d,%d)", i,\
				win_info.in_size.w, win_info.in_size.h,\
				win_info.in_win.w, win_info.in_win.h, win_info.in_win.x, win_info.in_win.y,\
				win_info.out_win.w, win_info.out_win.h, win_info.out_win.x, win_info.out_win.y);

			// TBD - 20220530 need to work
			if(vsc_AspectratioCallbackFp->pfnOrbitdrvWindowConvert && vsc_AspectratioCallbackFp->pfnOrbitdrvMoveConvert) {
				LX_DE_ORBIT_T orbit_win;
				LX_DE_ORBIT_T orbit_move;

				ret = vsc_AspectratioCallbackFp->pfnOrbitdrvWindowConvert(vsc_config[i].aspectratio_policy.system_policy,calculated_input_rect,calculated_output_rect,vsc_config[i].orbit_win,&orbit_window);
				memcpy(&vsc_config[i].calculated_orbit_win, &orbit_window, sizeof(struct v4l2_ext_vsc_orbit_window));
				DE_NOTI("WindowConvert : orbit_window in[%d,%d %dx%d] out[%d,%d %dx%d]", orbit_window.video_input.x, orbit_window.video_input.y, orbit_window.video_input.w, orbit_window.video_input.h,\
					orbit_window.video_output.x, orbit_window.video_output.y, orbit_window.video_output.w, orbit_window.video_output.h);

				ret = vsc_AspectratioCallbackFp->pfnOrbitdrvMoveConvert(vsc_config[i].aspectratio_policy.system_policy, vsc_config[i].orbit_win, orbit_window, vsc_config[i].orbit_move, &calculated_orbit_move);
				DE_NOTI("MoveConvert :calculated_orbit_move: in[%d,%d %dx%d] out[%d,%d %dx%d]", calculated_orbit_move.video_input.x, calculated_orbit_move.video_input.y, calculated_orbit_move.video_input.w, calculated_orbit_move.video_input.h,\
					calculated_orbit_move.video_output.x, calculated_orbit_move.video_output.y, calculated_orbit_move.video_output.w, calculated_orbit_move.video_output.h);


				orbit_win.wId = i;
				orbit_win.type = 0;
				orbit_win.osd_input.w = orbit_window.osd_input.w;
				orbit_win.osd_input.h = orbit_window.osd_input.h;
				orbit_win.osd_input.x = orbit_window.osd_input.x;
				orbit_win.osd_input.y = orbit_window.osd_input.y;
				orbit_win.video_input.w = orbit_window.video_input.w;
				orbit_win.video_input.h = orbit_window.video_input.h;
				orbit_win.video_input.x = orbit_window.video_input.x;
				orbit_win.video_input.y = orbit_window.video_input.y;
				orbit_win.osd_output.w = orbit_window.osd_output.w;
				orbit_win.osd_output.h = orbit_window.osd_output.h;
				orbit_win.osd_output.x = orbit_window.osd_output.x;
				orbit_win.osd_output.y = orbit_window.osd_output.y;
				orbit_win.video_output.w = orbit_window.video_output.w;
				orbit_win.video_output.h = orbit_window.video_output.h;
				orbit_win.video_output.x = orbit_window.video_output.x;
				orbit_win.video_output.y = orbit_window.video_output.y;				
				if(i == 2 && vsc_config[i].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
					orbit_win.wId = LX_DE_WIN_3;
				if(i == 3 && vsc_config[i].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
					orbit_win.wId = LX_DE_WIN_4;

				ret = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_win,1);

				orbit_move.wId = i;
				orbit_move.type = 1;
				orbit_move.osd_input.w = calculated_orbit_move.osd_input.w;
				orbit_move.osd_input.h = calculated_orbit_move.osd_input.h;
				orbit_move.osd_input.x = calculated_orbit_move.osd_input.x;
				orbit_move.osd_input.y = calculated_orbit_move.osd_input.y;
				orbit_move.video_input.w = calculated_orbit_move.video_input.w;
				orbit_move.video_input.h = calculated_orbit_move.video_input.h;
				orbit_move.video_input.x = calculated_orbit_move.video_input.x;
				orbit_move.video_input.y = calculated_orbit_move.video_input.y;
				orbit_move.osd_output.w = calculated_orbit_move.osd_output.w;
				orbit_move.osd_output.h = calculated_orbit_move.osd_output.h;
				orbit_move.osd_output.x = calculated_orbit_move.osd_output.x;
				orbit_move.osd_output.y = calculated_orbit_move.osd_output.y;
				orbit_move.video_output.w = calculated_orbit_move.video_output.w;
				orbit_move.video_output.h = calculated_orbit_move.video_output.h;
				orbit_move.video_output.x = calculated_orbit_move.video_output.x;
				orbit_move.video_output.y = calculated_orbit_move.video_output.y;

				if(i == 2 && vsc_config[i].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
					orbit_move.wId = LX_DE_WIN_3;
				if(i == 3 && vsc_config[i].inout_info.out == V4L2_EXT_VSC_DEST_DISPLAY)
					orbit_move.wId = LX_DE_WIN_4;

				ret = resource_mgr_ioctl(DE_IOW_SET_ORBIT,(unsigned long)&orbit_move,1);

			}
			else
			{
				DE_NOTI("no handler for orbit window&move");
			}
//#endif
		}

#else
		if(vsc_config[0].seamless == 2) {
				// call darc library funtion from external *.ko
				ret = vsc_external_library(0, srcStatus.vdecInfo.afd, srcStatus.vdecInfo.par_width, srcStatus.vdecInfo.par_height, &win_info);
				if(ret) break;

				resource_mgr_ioctl(DE_IOW_SET_WIN_INFO,(unsigned long)&win_info,1);
				DE_NOTI("src %dx%d , in win=%dx%d(%d,%d) , out win=%dx%d(%d,%d)", \
					win_info.in_size.w, win_info.in_size.h,\
					win_info.in_win.w, win_info.in_win.h, win_info.in_win.x, win_info.in_win.y,\
					win_info.out_win.w, win_info.out_win.h, win_info.out_win.x, win_info.out_win.y);
		}
#endif //#ifdef V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
	} while(i++<2);
	return 0;
}
