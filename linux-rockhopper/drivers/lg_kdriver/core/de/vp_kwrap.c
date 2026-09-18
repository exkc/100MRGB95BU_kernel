/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file vp_kwrap.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author	sh.myoung (sh.myoung@lge.com)
 *  @version	1.0
 *  @date		2012-05-01
 *  @note		Additional information.
 *  @note		Moved to kernel for SEETV (harish.singh@lge.com)
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "vp_kwrap.h"
#include "vp_kwrap_hdmi.h"
#include "de_kwrap.h"
#include "afe_kwrap.h"
#include "pe_kwrap.h"
#include "vpq_hwrap.h"
//#include "pe_kapi.h"
#include "../hdmi20/hdmi20_kwarp.h"
//#include "afe_kapi.h"
#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#endif
#include "os_util.h"
#include "de_def.h"
#include "de_model.h"
#include "vpq_hwrap_pe.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define KWRAP_VP 			"kwrap-vp"
#define JPEG_FROM_CPU_TO_VP
#undef AUTO_INPUT_SET

#define H13_SCART_RGB_WORKAROUND
#define SC_DBG

#define SEE_TV
/** modify checking the range of available frame rate for Y18 SOC(M16++/O18)
* 20170728, justine.jeong
*/
#define NEW_FR_CHECK_FOR_Y18

/** add checking pic info
* 20130222, sj.youm,
*	- fix post csc to y709_rgb for dual window,
*	- to avoid changing sub reddish on face when main DTV to ATV on DW mode
* 20130222, sj.youm,
*	- fix atv fmt to ntsc on dw_mode
*	- to avoid over-peaking on sub when main atv ch change(sometimes)
*/
#define VP_KWRAP_ADD_CHK_PIC_INFO

/** add using set input csc on vp task
* 20131014, sj.youm,
*	- Do undef,
*	if you want to avoid overlap setting between TV vs. VP task, for main win.
*/
#undef KWRAP_VP_USE_SET_MAIN_INPUT_CSC_ON_VP_TASK

typedef struct
{
	void *dev_mtx;	/* mutex(semaphore) for VP */
	int	ref_cnt;		/* refrence count */
}
vp_lx_cxt_t;

#define KWRAP_VP_WID_TO_STR(_x)	((_x==0)? "Main":"Sub")

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
//extern int vdec_kwrap_getdisplayrunningstatus(int de_id, LX_DE_MPEG_TIMING_INFO_T *deinfo);
extern int vsc_get_dev_info(int win, int param);


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int g_vp_logm_fd = -1;

UINT32	target_R = 0;
UINT32	target_G = 0;
UINT32	target_B = 0;
UINT32	target_Y = 0;
UINT32	target_Cb = 0;
UINT32	target_Cr = 0;

LX_DE_CVI_SRC_TYPE_T  		prev_cviInfo = {0, };

typedef struct O_ENUM {
	int 	PreEnum;
	int	PostEnum;
} s0_enum;

void (*gpfnCallBackMuteOff)(UINT32 vpSrcId);

#ifdef USE_VIDEO_FOR_FPGA
int g_vp_kwrap_dbg_cvisrctype = 0;//0:normal,1:4K60p,2:4K120p,3:2K60,4:2K60i,5:2K120p,6:3K60p,7:3K120p
module_param_named(pqe_cvisrctype, g_vp_kwrap_dbg_cvisrctype, int, 0644);
#endif

int vp_kwrap_resettiminginfo(UINT32 vpSrcId);
int vp_kwrap_setvcroutsrc(kwrap_vp_input_src_t vpInputSrc, kwrap_vp_input_src_t vpInputSrc_sub, int denc_on_off);
int vp_kwrap_setinputsrc(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo);
int vp_kwrap_setexternalinputsrc(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo);

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#if 0	//not used
static int vp_kwrap_periodictask(UINT32 vpSrcId);
static int vp_kwrap_inputsrcapply(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo);
static int vp_kwrap_checkexternalinputsrc(UINT32 vpSrcId,kwrap_vp_input_src_t vpOtherSrcType, kwrap_vp_src_info_t *pVpSrcInfo);
static BOOLEAN vp_kwrap_checktiminginfo(UINT32 vpSrcId, kwrap_vp_timing_info_t bufVpTiming);
static int vp_kwrap_checkpicinfo(UINT32 wId);
static LX_PE_SRC_TYPE vp_kwrap_convvptopicsrcinfo(kwrap_vp_input_src_t vpSrcType);
//static int vp_kwrap_setpicformatinfo(UINT32 vpSrcId, const kwrap_vp_timing_info_t *timing, const LX_DE_CVI_SRC_TYPE_T *cviInfo);
//static int vp_kwrap_setpicreversemodeinfo(UINT32 mode_on);

static int vp_kwrap_checkfrrate(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t srcTiming, UINT16 *frameRate);
static int vp_kwrap_set3dfrrate(LX_DE_3D_INOUT_CTRL_T ctrl3D);
static BOOLEAN vp_kwrap_checkpulldownmode(void);
static int vp_kwrap_gethdmicolormetry(UINT32 vpSrcId, LX_DE_COLOR_STD_T *color, LX_DE_SCALER_CSAMPLE_T *scaler);

/* Restrctured Code */
/* For KADP_VP_Periodic_Task */
static kwrap_vp_info_chg_flag_t vp_kwrap_getchangedinputinfo(UINT32 vpSrcId,kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming,kwrap_vp_chg_info_t *prevHdmiInfo);
static int vp_kwrap_updateframerate(UINT32 vpSrcId,kwrap_vp_src_info_t vpInputSrc,kwrap_vp_timing_info_t bufTiming,kwrap_vp_fr_info_t *frameRateInfo);
static int vp_kwrap_getcolorstd(kwrap_vp_src_info_t vpInputSrc,kwrap_vp_timing_info_t bufTiming,LX_DE_CVI_SRC_TYPE_T cviInfo,LX_DE_COLOR_STD_T *color_std);
static BOOLEAN vp_kwrap_iscvisource(kwrap_vp_input_src_t srcType);

/* For CVI config */
static int vp_kwrap_gethdmiaspectratio(UINT32 vpSrcId, LX_HDMI_ASPECTRATIO_T *hdmi_aspectratio);
static int vp_kwrap_getcvicfg_vga(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int vp_kwrap_getcvicfg_ypbpr(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int vp_kwrap_getcvicfg_atv(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int vp_kwrap_getcvicfg_cvbs(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int vp_kwrap_getcvicfg_scart(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int vp_kwrap_getcvicfg_scart_rgbbypass(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
static int vp_kwrap_getdefull3dformattype(kwrap_vp_ext_info_t vp3DFormatType);
static int vp_kwrap_getcvicfg_hdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );

/* For timinig info */
int vp_kwrap_readtiminginfo_frm_adc(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_readtiminginfo_frm_cvd(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_readtiminginfo_frm_hdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_readtiminginfo_frm_vdec(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);

/* Pic format info */
static int vp_kwrap_getpeformattype(kwrap_vp_input_src_t vpSrcType,const kwrap_vp_timing_info_t *timing,LX_PE_FMT_TYPE *peFmt,LX_PE_HDMI_TYPE hdmiType);
static int vp_kwrap_getpecolorstdtype(kwrap_vp_input_src_t vpSrcType,const LX_DE_CVI_SRC_TYPE_T *cviInfo,LX_PE_CSTD_TYPE *peColorStd);

/* For Setting major operational mode of TV */
static int vp_kwrap_statetransition_onewin(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper);
static int vp_kwrap_statetransition_mulwin(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper);
static int vp_kwrap_statetransition_3d(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper);
static int vp_kwrap_statetransition_ud(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper);
static int vp_kwrap_statetransition_venc(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper);

static int vp_kwrap_substatetransition_off(LX_DE_SUB_OPERATION_CTRL_T *param,LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper);
static  int vp_kwrap_substatetransition_capture(LX_DE_SUB_OPERATION_CTRL_T *param,LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper);
static int vp_kwrap_substatetransition_scartout(LX_DE_SUB_OPERATION_CTRL_T *param, LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper);
static int vp_kwrap_substatetransition_venc(LX_DE_SUB_OPERATION_CTRL_T *param, LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper);

static int vp_kwrap_checkmuteoff(UINT32 vpSrcId, kwrap_vp_timing_info_t *pBufTiming);
#endif
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#if 0
static vp_lx_cxt_t		g_vp_ctx =
{
	.dev_mtx	= NULL,
	.ref_cnt 	= 0,
};
#endif
static kwrap_vp_src_info_t	_gVPInputSrcCfg[LX_DE_WIN_MAX] = {{ SRC_INPUT_NONE, 0, 0, 0}, {SRC_INPUT_NONE, 0, 0, 0},\
																{SRC_INPUT_NONE, 0, 0, 0}, {SRC_INPUT_NONE, 0, 0, 0}};
static kwrap_vp_src_info_t	_gVPInputSrcTemp[LX_DE_WIN_MAX] = {{ SRC_INPUT_NONE, 0, 0, 0}, {SRC_INPUT_NONE, 0, 0, 0},\
																{SRC_INPUT_NONE, 0, 0, 0}, {SRC_INPUT_NONE, 0, 0, 0}};
static kwrap_vp_timing_info_t	_gCurVpTiming[LX_DE_WIN_MAX] = {{ 0, }, {0, } };
// static LX_DE_OPER_CONFIG_T	_gCurTVOperState = LX_DE_OPER_ONE_WIN; /* Current Operation state of TV */
// static LX_DE_SUB_OPER_CONFIG_T	_gCurTVSubOperState = LX_DE_SUB_OPER_OFF; /* Current sub-operation state of TV */
// static kwrap_vp_info_chg_flag_t	_gCurInfoChg[LX_DE_WIN_MAX] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
static UINT32	_gVPInputChg[LX_DE_WIN_MAX] = {0, 0, 0, 0};
static UINT32	_gVPInWinChg[LX_DE_WIN_MAX] = {0, 0, 0, 0};
// static UINT32	_gVPHdmiPort[LX_DE_WIN_MAX] = {0, 0, 0, 0};
// static UINT32	_gVPInSizeChg[LX_DE_WIN_MAX] = {0, 0, 0, 0};
// static BOOLEAN _gVPMuteOnOff[LX_DE_WIN_MAX] = {TRUE,TRUE,TRUE,TRUE};
static LX_DE_RECT_T _gVPInWin[LX_DE_WIN_MAX] = {{0,0,0,0},{0,0,0,0}};
// static LX_DE_RECT_T _gVPInSize[LX_DE_WIN_MAX] = {{0,0,0,0},{0,0,0,0}};
static LX_DE_RECT_T _gVPInSizeFromThread[LX_DE_WIN_MAX] = {{0,0,0,0},{0,0,0,0}};
// static UINT16 _gVPQuadWin = 0;
static UINT16 _gAdaptive_ = 0;
static UINT16 _gAdaptive_update_win = 0;
#define UPDATE_INPUT_WIN_COUNTER        2
// static LX_DE_FIRMWARE_INFO_T _gVersion = { 0 };
static int _gVPNoFirstFrame = 0;


// static BOOLEAN	_gVP_INIT	= FALSE;
static UINT32	_g_vp_kwrap_pic_info_init = 0;
BOOLEAN	 _gVP_DebugPrintOn	= FALSE;
BOOLEAN	 _gVP_DebugHdrOn	= FALSE;//HDR(0:normal/1:OFF/2:DOLBY/3:HDR10/4:TECH/5:S2H/6:HLG)
//static kwrap_vp_src_info_t	_gVPInputSrcCfg[2] = {0 , };

static kwrap_vp_pic_info_t _gVP_PicInfo;

#if 0	//not used
static LX_DE_3D_INOUT_CTRL_T _gVP3DMode = {LX_DE_3D_RUNMODE_OFF, LX_DE_3D_IMG_IN_MAX, \
			LX_DE_3D_LR_ORDER_L_FIRST, LX_DE_3D_IMG_OUT_SINGLE_2D, LX_DE_3D_LR_ORDER_L_FIRST };

static const s0_enum ATV_COLOR_TYPE[ ] =
{	/// LX_AFE_VIDEO_SYSTEM_T 			LX_DE_CVD_COLOR_STD_T
	{	LX_DEFAULT,					LX_DE_COLOR_UNKNOWN},
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
{	/// LX_AFE_VIDEO_SYSTEM_T 			LX_DE_CVD_COLOR_STD_T
	{	LX_DEFAULT,					LX_DE_COLOR_UNKNOWN},
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
#endif

static const s0_enum MVI_3D_TYPE[ ] =
{	/// LX_DE_MVI_3D_INFO_T			 			KADP_VP_EXT_INFO_T
	{	LX_DE_MVI_2D,							VP_EXT_2D_FORMAT},
	{	LX_DE_MVI_3D_CHECKERBOARD,			VP_EXT_3D_CHECKER_BOARD},
	{	LX_DE_MVI_3D_COLUMN_INTERLEAVING,		VP_EXT_3D_COLUMN_ALTERNATIVE},
	{	LX_DE_MVI_3D_ROW_INTERLEAVING,			VP_EXT_3D_LINE_ALTERNATIVE},
	{	LX_DE_MVI_3D_SIDEBYSIDE,				VP_EXT_3D_SIDEBYSIDE},
	{	LX_DE_MVI_3D_TOPNBOTTOM,				VP_EXT_3D_TOPNBOTTOM},
	{	LX_DE_MVI_3D_FRAMESEQ,					VP_EXT_3D_FRAME_SEQ},
	{	LX_DE_MVI_3D_FRAMEPACK,				VP_EXT_3D_FRAME_PACKING},
	{	LX_DE_MVI_3D_FIELD_ALTERNATIVE,			VP_EXT_3D_FIELD_ALTERNATIVE},
	{	LX_DE_MVI_3D_LINE_ALTERNATIVE,			VP_EXT_3D_LINE_ALTERNATIVE_FULL},
	{	LX_DE_MVI_3D_SIDEBYSIDE_FULL,			VP_EXT_3D_SIDEBYSIDE_FULL},
	{	LX_DE_MVI_3D_DUALSTREAM,				VP_EXT_3D_DUAL},
	{	LX_DE_MVI_3D_2DTO3D,					VP_EXT_2D_FORMAT},
	{	LX_DE_MVI_3D_FORMAT_MAX,				VP_EXT_2D_FORMAT},
};

static const s0_enum HDMI_3D_TYPE[ ] =
{	/// LX_HDMI_EXT_FORMAT_INFO_T		 			KADP_VP_EXT_INFO_T
	{	LX_HDMI_EXT_2D_FORMAT,					VP_EXT_2D_FORMAT},
	{	LX_HDMI_EXT_3D_FRAMEPACK,				VP_EXT_3D_FRAME_PACKING},
	{	LX_HDMI_EXT_3D_FIELD_ALTERNATIVE,		VP_EXT_3D_FIELD_ALTERNATIVE},
	{	LX_HDMI_EXT_3D_LINE_ALTERNATIVE,		VP_EXT_3D_LINE_ALTERNATIVE_FULL},
	{	LX_HDMI_EXT_3D_SBSFULL,					VP_EXT_3D_SIDEBYSIDE_FULL},
	{	LX_HDMI_EXT_3D_TNB,						VP_EXT_3D_TOPNBOTTOM},
	{	LX_HDMI_EXT_3D_SBS,						VP_EXT_3D_SIDEBYSIDE},
	{	LX_HDMI_EXT_4K_2K,						VP_EXT_4K_2K},
	{	LX_HDMI_EXT_MAX,						VP_EXT_2D_FORMAT},
};

#if 0	//not used
/*CVI default configuration */
LX_DE_CVI_SRC_TYPE_T cvi_common_config[SRC_INPUT_MAX] = {\
////{cvi_channel   ,size_offset,color, aspect, scan, bit_res, c_sample, de_mode, sampling, sc_c_sample, stability, field_polarity, yc_delay, cvi_port, trid_full_format, cvi_input_src, cvd_color_std }
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_444,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_VGA,LX_DE_COLOR_DEFAULT},//NONE [Unused]
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_RGBEX,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_444,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_ADC,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_VGA,LX_DE_COLOR_DEFAULT},//VGA
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_ADC,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_YPBPR,LX_DE_COLOR_DEFAULT},//YPbPr
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601_CVD,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_ATV,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_ATV,LX_DE_COLOR_DEFAULT},//ATV
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601_CVD,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_OTHERS,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_CVBS,LX_DE_COLOR_DEFAULT},//CVBS
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_601_CVD,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_OTHERS,LX_DE_CVI_CVD,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_SCART,LX_DE_COLOR_DEFAULT},//SCART
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_RGB,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_NORMAL_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_422,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_ADC,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_YPBPR,LX_DE_COLOR_PAL},//SCART_BYPASS
	{LX_DE_CVI_CH_A,{0,0,0,0,},LX_DE_COLOR_RGB,LX_DE_AR_4_3,LX_DE_INTERLACED,LX_DE_CVI_10BIT,LX_DE_CVI_444,LX_DE_CVI_HDMI_SYNC_MODE,LX_DE_CVI_NORMAL_SAMPLING,LX_DE_SCALER_444,LX_DE_CVI_SYNC_STD,LX_DE_CVI_FIELD_ORIGINAL,LX_DE_CVI_YC_DELAY_BYPASS,LX_DE_CVI_EXT_A,LX_DE_CVI_NORMAL_FORMAT,LX_DE_CVI_SRC_HDMI,LX_DE_COLOR_DEFAULT},//HDMI
};

/* HDMI colorimetry map */
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
#endif

/* VP SRC type to DE SRC type mapping */
kwrap_vp_src_de_map_t VP_TO_DE_SRC_MAP[] =
{
	{SRC_INPUT_NONE,LX_DE_IN_SRC_NONE},
	{SRC_INPUT_VGA,LX_DE_IN_SRC_VGA},
	{SRC_INPUT_YPBPR,LX_DE_IN_SRC_YPBPR},
	{SRC_INPUT_SCART_RGB_BYPASS,LX_DE_IN_SRC_YPBPR},
	{SRC_INPUT_ATV,LX_DE_IN_SRC_ATV},
	{SRC_INPUT_CVBS,LX_DE_IN_SRC_CVBS},
	{SRC_INPUT_SCART,LX_DE_IN_SRC_SCART},
	{SRC_INPUT_HDMI,LX_DE_IN_SRC_HDMI},
	{SRC_INPUT_DTV,LX_DE_IN_SRC_MVI},
	{SRC_INPUT_MVI,LX_DE_IN_SRC_MVI},
	{SRC_INPUT_JPG,LX_DE_IN_SRC_MVI}
};

// static UINT32 use_input_window_wa = 0;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* debug message wrapper */
#if 0
#define VP_NOTI(fmt, args...) 	KADP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_NOTI, fmt, ##args)
#define VP_PRINT(fmt, args...) 	KADP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_INFO, fmt, ##args)
#define VP_WARN(fmt, args...) 	KADP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_WARNING, fmt, ##args)
#define VP_ERROR(fmt, args...) 	KADP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_ERROR, fmt, ##args)
#define VP_DEBUG(fmt, args...) 	KADP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_DEBUG, fmt, ##args)
#define VP_TRACE(fmt, args...) 	KADP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_TRACE, fmt, ##args)

#define VP_TRACE_BEGIN()		VP_TRACE("[vp] %s:%d -- BEGIN\n", __F__, __L__)
#define VP_TRACE_END()			VP_TRACE("[vp] %s:%d -- END\n", __F__, __L__ )
#define VP_TRACE_MARK()			VP_TRACE("[vp] %s:%d -- TRACE !!!\n", __F__, __L__ )

/* DE device mutex */
#define VP_INIT_LOCK()			g_vp_ctx.dev_mtx = KADP_OSA_OpenSema("kwrap-vp-mtx", LX_OSA_GLOBAL_SEMA, 1);
#define VP_LOCK()				(void)KADP_OSA_LockSema( g_vp_ctx.dev_mtx, LX_OSA_INF_WAIT)
#define VP_UNLOCK()				(void)KADP_OSA_UnlockSema( g_vp_ctx.dev_mtx )

#define VP_CHECK_CODE(__checker,__if_action,fmt,args...)   \
						__CHECK_IF_ERROR(__checker, VP_ERROR, __if_action , fmt, ##args )

#define VP_BREAK_WRONG(arg)           { VP_ERROR("[VP] Wrong (0x%x)\n", arg); ret = RET_ERROR; }
#define CHECK_NULL(ptr)  		if (!ptr) { VP_ERROR("[VP] %s is Null\n", #ptr); return RET_ERROR; }
#define CHECK_SRC_ID(ptr) 	if (ptr>=LX_DE_WIN_MAX) { VP_ERROR("[VP] srcId[%d] is wrong.\n", ptr); return RET_ERROR; }

#else
#define	VP_ERROR(format, args...)		DBG_PRINT(  g_de_debug_fd,        \
													LX_LOGM_LEVEL_ERROR,  \
													format,               \
													##args)
#define	VP_WARN(format, args...)		DBG_PRINT(  g_de_debug_fd,        \
													LX_LOGM_LEVEL_WARNING,\
													format,               \
													##args)
#define	VP_PRINT(format, args...)		DBG_PRINT(  g_de_debug_fd,        \
													LX_LOGM_LEVEL_INFO,   \
													format,               \
													##args)
#define	VP_NOTI(format, args...)		DBG_PRINT( g_de_debug_fd,         \
													LX_LOGM_LEVEL_NOTI,   \
													format,               \
													##args)
#define	VP_DEBUG(format, args...)		DBG_PRINT( g_de_debug_fd,         \
													LX_LOGM_LEVEL_DEBUG,   \
													format,               \
													##args)
#define	VP_TRACE(format, args...)		DBG_PRINT( g_de_debug_fd,         \
													LX_LOGM_LEVEL_TRACE,  \
													format,               \
													##args)

#define VP_TRACE_BEGIN()		{}
#define VP_TRACE_END()			{}
#define VP_TRACE_MARK()			{}

/* DE device mutex */
#define VP_INIT_LOCK()			{}
#define VP_LOCK()				{}
#define VP_UNLOCK()				{}

#define VP_CHECK_CODE(__checker,__if_action,fmt,args...)  {}

#define VP_BREAK_WRONG(arg)           {}
#define CHECK_SRC_ID(ptr) 	{}
#undef CHECK_NULL
#define CHECK_NULL(ptr)     {}
#endif
#define TBL_NUM(X)	(sizeof(X) /sizeof((X)[0]))
#define u16CHK_RANGE(X,Y,offset)		((UINT16) ((X) + (offset) - (Y)) <= (offset*2))

/**
 * vp_kwrap_initpicinfo
 * @param 	void
 * @return 	int
 */
int vp_kwrap_initpicinfo(void)
{
	int	ret = RET_OK;
	if (!_g_vp_kwrap_pic_info_init)
	{
		VP_NOTI("[VP] initpicinfo\n");
		memset(&_gVP_PicInfo,0x0,sizeof(kwrap_vp_pic_info_t));	//init _gVP_PicInfo
		_gVP_PicInfo.post_csc_type = 0xff;
		_gVP_PicInfo.pic_src_type[LX_DE_WIN_0] = (UINT32)LX_PE_SRC_NUM;
		_gVP_PicInfo.pic_src_type[LX_DE_WIN_1] = (UINT32)LX_PE_SRC_NUM;
		_gVP_PicInfo.pic_src_type[LX_DE_WIN_2] = (UINT32)LX_PE_SRC_NUM;
		_gVP_PicInfo.pic_src_type[LX_DE_WIN_3] = (UINT32)LX_PE_SRC_NUM;
		_g_vp_kwrap_pic_info_init = 1;
	}
	return ret;
}

static UINT32 _g_kwrap_vp_inputcschistory[LX_DE_WIN_MAX] = {0x0,0x0,0x0,0x0};
int vp_kwrap_updateinputcschistory(int win)
{
	_g_kwrap_vp_inputcschistory[win] = (_g_kwrap_vp_inputcschistory[win]<<1)|0x1;
	return RET_OK;
}

/**
* Check if the given source type is input to CVI
*
* @param srcType	[IN] KADP_VP_INPUT_SRC_T
* @return BOOLEAN
*/
static BOOLEAN vp_kwrap_iscvisource(kwrap_vp_input_src_t srcType)
{
	switch(srcType)
	{
		case SRC_INPUT_VGA:
		case SRC_INPUT_YPBPR:
		case SRC_INPUT_ATV:
		case SRC_INPUT_CVBS:
		case SRC_INPUT_SCART:
		case SRC_INPUT_SCART_RGB_BYPASS:
		case SRC_INPUT_HDMI:
		{
			return TRUE;
		}
		default:
			return FALSE;
	}
}
/**
 * conv vp src type to pic src type.
 *
 * @param   vpSrcType [in] KADP_VP_INPUT_SRC_T
 * @return  LX_PE_SRC_TYPE
 * @see		func. description
 * @author
 */
static LX_PE_SRC_TYPE vp_kwrap_convvptopicsrcinfo(kwrap_vp_input_src_t vpSrcType)
{
	LX_PE_SRC_TYPE src_type = LX_PE_SRC_NUM;

	switch (vpSrcType)
	{
		case SRC_INPUT_ATV:
			src_type = LX_PE_SRC_ATV;
			break;
		case SRC_INPUT_CVBS:
			src_type = LX_PE_SRC_CVBS;
			break;
		case SRC_INPUT_SCART:
		case SRC_INPUT_SCART_RGB_BYPASS:
			src_type = LX_PE_SRC_SCART;
			break;
		case SRC_INPUT_VGA:
			src_type = LX_PE_SRC_RGBPC;
			break;
		case SRC_INPUT_YPBPR:
			src_type = LX_PE_SRC_COMP;
			break;
		case SRC_INPUT_HDMI:
			src_type = LX_PE_SRC_HDMI;
			break;
		case SRC_INPUT_DTV:
		case SRC_INPUT_JPG:
		case SRC_INPUT_MVI:
		default:
			src_type = LX_PE_SRC_DTV;
			break;
	}

	if (_gVP_DebugPrintOn)
	{
		VP_DEBUG("[VP][%s,%d]vpSrcType:%d, pe src_type:%d\n", \
			__F__, __L__, vpSrcType, src_type);
	}

	return src_type;
}
/**
 * Get(update) picture format type.
 *
 * @param   vpSrcType [in] KADP_VP_INPUT_SRC_T
 * @param   timing [in] kwrap_vp_timing_info_t *
 * @param   peFmt [in] LX_PE_FMT_TYPE *
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
static int vp_kwrap_getpeformattype(kwrap_vp_input_src_t vpSrcType,const kwrap_vp_timing_info_t *timing,\
								LX_PE_FMT_TYPE *peFmt,LX_PE_HDMI_TYPE hdmiType)
{
	switch (vpSrcType)
	{
		case SRC_INPUT_ATV:
		case SRC_INPUT_CVBS:
		case SRC_INPUT_SCART:
		case SRC_INPUT_SCART_RGB_BYPASS:
			{
				/* fmt_type */
				*peFmt = LX_PE_FMT_SD;
			}
			break;
		case SRC_INPUT_HDMI:
			{
				/* fmt_type */ //sync to libpqdb 20200225
				if(hdmiType == LX_PE_HDMI_PC)
				{
					if (timing->hActive <= 900)
					{
						*peFmt = LX_PE_FMT_SD;
					}
					else if (timing->hActive <= 1930 && timing->vActive <= 1090)
					{
						*peFmt = LX_PE_FMT_HD;
					}
					else if ((timing->hActive >= 3830 && timing->hActive <= 5006)	&&\
						(timing->vActive >= 2150 && timing->vActive <= 2170))
					{
						*peFmt = LX_PE_FMT_UHD;
					}
					else if (timing->hActive > 4096 || timing->vActive > 2160)
					{
						*peFmt = LX_PE_FMT_UHD_8K;
					}
					else
					{
						*peFmt = LX_PE_FMT_HD;
					}
				}
				else // hdmi tv
				{
					if (timing->vActive <= 576+73)	
					{
						*peFmt = LX_PE_FMT_SD;
					}
					else if (timing->vActive <= 1080+540)
					{
						*peFmt = LX_PE_FMT_HD;
					}
					else if (timing->vActive <= 2160+540)
					{
						*peFmt = LX_PE_FMT_UHD;
					}
					else
					{
						*peFmt = LX_PE_FMT_UHD_8K;
					}
				}
			}
			break;
		default:
			{
				/* fmt_type */ //sync to libpqdb 20200225
				if (timing->vActive <= 576+73)	
				{
					*peFmt = LX_PE_FMT_SD;
				}
				else if (timing->vActive <= 1080+540)
				{
					*peFmt = LX_PE_FMT_HD;
				}
				else if (timing->vActive <= 2160+540)
				{
					*peFmt = LX_PE_FMT_UHD;
				}
				else
				{
					*peFmt = LX_PE_FMT_UHD_8K;
				}
				/* cstd_type : skip cstd update */
			}
			break;
	}

	return RET_OK;
}

/*
* Get PE color standard Type
*
* @param	vpSrcType 	[IN] KADP_VP_INPUT_SRC_T
* @param 	cviInfo 	[IN] LX_DE_CVI_SRC_TYPE_T *
* @param    peColorStd	[IN/OUT] LX_PE_CSTD_TYPE *
* @return int
*/
static int vp_kwrap_getpecolorstdtype(kwrap_vp_input_src_t vpSrcType,const LX_DE_CVI_SRC_TYPE_T *cviInfo,LX_PE_CSTD_TYPE *peColorStd)
{
	/* Initialize with invalid data */
	LX_DE_CVD_COLOR_STD_T cvd_color_std = LX_DE_COLOR_UNKNOWN;

	/* cstd_type */
	#ifdef VP_KWRAP_ADD_CHK_PIC_INFO
	cvd_color_std = (_gVP_PicInfo.b_is_dw_md && \
		vpSrcType == SRC_INPUT_ATV)? \
		LX_DE_COLOR_DEFAULT:cviInfo->cvd_color_std;
	#else
	cvd_color_std = cviInfo->cvd_color_std;
	#endif
	/**
	* if(cvd_color_std == LX_DE_COLOR_UNKNOWN)
	* abnormal -> skip cstd update.
	*/
	if(cvd_color_std != LX_DE_COLOR_UNKNOWN)
	{
		switch (cvd_color_std)
		{
			case LX_DE_COLOR_DEFAULT:
			case LX_DE_COLOR_NTSC_M:
			case LX_DE_COLOR_NTSC_M_RF:
			case LX_DE_COLOR_NTSC_443:
			case LX_DE_COLOR_NTSC_443_RF:
				*peColorStd = LX_PE_CSTD_NTSC;
				break;
			case LX_DE_COLOR_SECAM:
			case LX_DE_COLOR_SECAM_RF:
				*peColorStd = LX_PE_CSTD_SECAM;
				break;
			default:
				*peColorStd = LX_PE_CSTD_PAL;
				break;
		}
	}

	return RET_OK;
}
/**
 * checktimingchangeforcsc
 *
 * @param   vpSrcId [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int vp_kwrap_checktimingchangeforcsc(UINT32 vpSrcId)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_updatecnt_icsc(vpSrcId);
#endif
	return ret;
}

/**
 * set input csc
 *
 * @param   vpSrcId [in] UINT32
 * @param   *src_info [in] kwrap_vp_src_info_t
 * @param   *cviInfo [in] LX_DE_CVI_SRC_TYPE_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int vp_kwrap_setinputcsc(UINT32 vpSrcId, const kwrap_vp_src_info_t *src_info, const LX_DE_CVI_SRC_TYPE_T *cviInfo)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_PE
	PE_KWRAP_CTRL_T param = {.wid = 0};
	int internal_csc_flag =0;
	LX_PE_CSC_INPUT_T csc_param;
	int output_mode;
	vpq_hwrap_info_t curr_cntinfo;

	CHECK_NULL(src_info);
	CHECK_NULL(cviInfo);
	CHECK_SRC_ID(vpSrcId);

	curr_cntinfo = vpq_hwrap_get_vpq_hwrap_info();//get curr info
	output_mode = vsc_get_dev_info(vpSrcId, 4);// 4: output_mode
	if(FALSE == vp_kwrap_iscvisource(src_info->Type))	return RET_OK;

	/* choose setting method - internel decision or externel(from platform) */
	if (curr_cntinfo.pre_icsc_updatecnt[vpSrcId] == curr_cntinfo.icsc_updatecnt[vpSrcId])//not timing change
	{
		if((output_mode != V4L2_EXT_VSC_DEST_VENC)&& (vpSrcId == 1)) // (win ==1  & PBP mode)
		{
			if(curr_cntinfo.blackleveltype[vpSrcId]==curr_cntinfo.pre_blackleveltype[vpSrcId])
			{
				return RET_OK; // skip setting
			}
		}
		else
			return RET_OK; // skip setting
	}
	DE_NOTI("src[%d]:%d,%d,%d,%d, color,std:%d,%d, history:%08x, output_mode:%d, pre_cnt:%d, cnt:%d, pre_blk:%d, blk:%d\n",vpSrcId,\
		src_info->Type,src_info->Port,src_info->Attr,src_info->Resv,\
		cviInfo->color,cviInfo->cvd_color_std,_g_kwrap_vp_inputcschistory[vpSrcId],output_mode,\
		curr_cntinfo.pre_icsc_updatecnt[vpSrcId],curr_cntinfo.icsc_updatecnt[vpSrcId],\
		curr_cntinfo.pre_blackleveltype[vpSrcId],curr_cntinfo.blackleveltype[vpSrcId]);
	vpq_hwrap_saveprecnt_icsc(vpSrcId, curr_cntinfo.icsc_updatecnt[vpSrcId]);
	if (vpSrcId == 0)
	{
		#ifdef KWRAP_VP_USE_SET_MAIN_INPUT_CSC_ON_VP_TASK
		param.wid = LX_PE_WIN_0;
		#else
		if (_gVP_DebugPrintOn)	//for debug
		{
			DE_NOTI("check skip(%08x)\n",_g_kwrap_vp_inputcschistory[vpSrcId]);
		}
		if (_g_kwrap_vp_inputcschistory[vpSrcId] > 0x0)		return RET_OK;
		param.wid = vpSrcId;
		internal_csc_flag = 1;
		#endif
	}
	else if(output_mode == V4L2_EXT_VSC_DEST_VENC)
	{
		param.wid = LX_PE_WIN_1;
		internal_csc_flag =1;
	}
	else if(vpSrcId == 1)
	{
		if (_g_kwrap_vp_inputcschistory[vpSrcId] > 0x0)
		{
			internal_csc_flag = 0;
			csc_param.win_id = vpSrcId;
		}
		else
		{
			internal_csc_flag = 1;
			param.wid = vpSrcId;
		}
	}
	else
	{
		internal_csc_flag = 1;
		param.wid = vpSrcId;
	}

	/*set csc*/
	if (internal_csc_flag == 1)//choose csc coeff by driver
	{
		switch (cviInfo->color)
		{
			case LX_DE_COLOR_RGB:
			case LX_DE_COLOR_RGBEX:
				param.data = PE_KWRAP_INPUT_CSC_RGB_Y709_LINEAR;
				break;
			case LX_DE_COLOR_601_CVD:
				if (cviInfo->cvd_color_std==LX_DE_COLOR_NTSC_M_RF || \
					cviInfo->cvd_color_std==LX_DE_COLOR_PAL_M_RF)
				{
					param.data = PE_KWRAP_INPUT_CSC_EXPEND_CVD;
				}
				else
				{
					param.data = PE_KWRAP_INPUT_CSC_BYPASS;
				}
				break;
			case LX_DE_COLOR_601:
			case LX_DE_COLOR_709:
			case LX_DE_COLOR_XVYCC601:
			case LX_DE_COLOR_XVYCC709:
			default:
				param.data = PE_KWRAP_INPUT_CSC_BYPASS;
				break;
		}
		#ifdef INCLUDE_KDRV_PE
		if( lx_chip_rev( ) >= LX_CHIP_REV(O20,A0) )
		{
			memset(&csc_param,0,sizeof(LX_PE_CSC_INPUT_T));
			csc_param.win_id = param.wid;
			switch (param.data)
			{
				case PE_KWRAP_INPUT_CSC_BYPASS:
					csc_param.enable = PE_ICSC_Y709_BYPASS;
					break;
				case PE_KWRAP_INPUT_CSC_LIMIT:
					csc_param.enable = PE_ICSC_Y709_LINEAR_LIMIT_HIGH;
					break;
				case PE_KWRAP_INPUT_CSC_EXPEND:
					csc_param.enable = PE_ICSC_Y709_COMP_LOW;
					break;
				case PE_KWRAP_INPUT_CSC_EXPEND_CVD:
					csc_param.enable = PE_ICSC_AV_RF_EXTENSION;
					break;
				case PE_KWRAP_INPUT_CSC_RGB_Y709_LINEAR:
					csc_param.enable = PE_ICSC_RGB_Y709_LINEAR_LOW;
					break;
				case PE_KWRAP_INPUT_CSC_RGB_Y709_LIMIT:
					csc_param.enable = PE_ICSC_RGB_Y709_LIMIT_HIGH;
					break;
				case PE_KWRAP_INPUT_CSC_RGB_Y601_LINEAR:
					csc_param.enable = PE_ICSC_RGB_Y601_LINEAR_LOW;
					break;
				case PE_KWRAP_INPUT_CSC_RGB_Y601_LIMIT:
					csc_param.enable = PE_ICSC_RGB_Y601_LIMIT_HIGH;
					break;
				case PE_KWRAP_INPUT_CSC_RGB_Y601_SECAM:
					csc_param.enable = PE_ICSC_RGB_Y601_LINEAR_LOW;
					break;
				default:
					csc_param.enable = PE_ICSC_Y709_BYPASS;
					break;
			}
			ret = vpq_hwrap_setinputcscparam(&csc_param);
			VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] KWRAP_PE_SetInputCscParam() error \n", __L__);
		}
		else
		{
			ret = KWRAP_PE_SetInputCscCtrl(&param);
			VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] KWRAP_PE_SetInputCscCtrl() error \n", __L__);
		}
		#endif
	}
	else //choose csc coeff by platform
	{
		csc_param.enable = (1 + vpq_hwrap_getblackleveltype(vpSrcId));
		ret = vpq_hwrap_setinputcscparam(&csc_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] KWRAP_PE_SetInputCscParam() error \n", __L__);
	}
	vpq_hwrap_setpreblacklevel(vpSrcId,curr_cntinfo.blackleveltype[vpSrcId]);
	DE_NOTI("[set]wid:%d, data:%d\n",param.wid,param.data);
#endif
	return ret;
}

/*
* Set Pic src Info
*
* @param	srcId 		[IN] UINT32
* @param 	inputinfo 		[IN] const vsc_v4l2_get_input 
* @return int
*/
int vp_kwrap_getpicsrcinfo(UINT32 srcId, LX_DE_IN_SRC_T input_src_info)
{
	int ret = RET_OK;
	UINT32 win_id = 0;
	kwrap_vp_src_info_t *pSrcCfg = NULL;
	CHECK_SRC_ID(srcId);

	if (srcId<1)
	{
		win_id = 0;
	}
	else
	{
	#ifdef PE_EXTEND_WINID
		win_id = srcId;
	#else
		win_id = 1;
	#endif
	}

	pSrcCfg = &_gVPInputSrcCfg[win_id];

	switch (input_src_info)
	{
		case LX_DE_IN_SRC_ATV:
			pSrcCfg->Type = SRC_INPUT_ATV;
			break;
		case LX_DE_IN_SRC_CVBS:
			pSrcCfg->Type = SRC_INPUT_CVBS;
			break;
		case LX_DE_IN_SRC_SCART:
			pSrcCfg->Type = SRC_INPUT_SCART;
			break;
		case LX_DE_IN_SRC_VGA:
			pSrcCfg->Type = SRC_INPUT_VGA;
			break;
		case LX_DE_IN_SRC_YPBPR:
			pSrcCfg->Type = SRC_INPUT_YPBPR;
			break;
		case LX_DE_IN_SRC_HDMI:
			pSrcCfg->Type = SRC_INPUT_HDMI;
			break;
		case LX_DE_IN_SRC_MVI:
			pSrcCfg->Type = SRC_INPUT_MVI;
			break;
		case LX_DE_IN_SRC_CPU:
		default:
			pSrcCfg->Type = SRC_INPUT_JPG;
			break;
	}
	return ret;
}

/**
* set vp input window
*
* @param vpSrcId [IN] UINT32
* @param inWin [IN] LX_DE_RECT_T
*
* @return int
*/
int vp_kwrap_setinputwin(UINT32 vpSrcId, LX_DE_RECT_T inWin)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T inf_param;
	CHECK_SRC_ID(vpSrcId);

	_gVPInWin[vpSrcId].x = inWin.x;
	_gVPInWin[vpSrcId].y = inWin.y;
	_gVPInWin[vpSrcId].w = inWin.w;
	_gVPInWin[vpSrcId].h = inWin.h;

	if (_gVPInputChg[vpSrcId] > 0)
	{
		VP_LOCK();
		_gVPInWinChg[vpSrcId] = 1;
		VP_UNLOCK();
	}

	if (_gAdaptive_)
	{
		VP_LOCK();
		_gVPInWinChg[vpSrcId] = UPDATE_INPUT_WIN_COUNTER;
		_gAdaptive_update_win = 1;
		VP_UNLOCK();
	}

	/* vp hdr fake mode */
	if (vpSrcId==LX_DE_WIN_0 && _gVP_DebugHdrOn)
	{
		UINT32 data[2];
		LX_HDR_MODE_T i_IpcMode = (_gVP_DebugHdrOn-1);
		de_kwrap_setipchdrmode(LX_DE_WIN_0,i_IpcMode,LX_HDR_MODE_FROM_DBG);
		data[0] = vpSrcId;
		data[1] = (UINT32)i_IpcMode;
//		KWRAP_PE_SetHdrConnect(data);
		if (_gVP_DebugPrintOn)
			VP_DEBUG("[VP] TEST HdrOn:%d,IpcMd:%d(1~7:OFF,DOVI,H10,TCH,S2H,HLG,LL)\n", \
				_gVP_DebugHdrOn, i_IpcMode);
	}
#if 0
	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Set wId[%d] Window in_xywh(%d,%d,%d,%d)*** Chg Status[%d]", \
			vpSrcId, inWin.x, inWin.y, inWin.w, inWin.h, _gVPInWinChg[vpSrcId]);

	if(_gAdaptive_ == 0 && _gVPInSizeFromThread[vpSrcId].w == 0)
	{
		_gVPInSizeFromThread[vpSrcId].w = inWin.w;
		_gVPInSizeFromThread[vpSrcId].h = inWin.h;
		_gVPNoFirstFrame = 2;
	}
	if(use_input_window_wa)
	{
		ret = de_kwrap_setsourcesizewin(vpSrcId, &_gVPInSizeFromThread[vpSrcId], &inWin);
	}
	ret |= de_kwrap_setinputwin(vpSrcId, &inWin);

	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] : de_kwrap_setinputwin function return error \n", __L__);
#endif
	memcpy(&(_gVP_PicInfo.i_win[vpSrcId]), &inWin, sizeof(LX_DE_RECT_T));

	inf_param.win_id = (vpSrcId<1)? LX_PE_WIN_0:LX_PE_WIN_1;
	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&inf_param);
	inf_param.info_type = LX_PE_INFO_IN_WIN;
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);

	inf_param.in_win.x_ofst = (UINT32)inWin.x;
	inf_param.in_win.y_ofst = (UINT32)inWin.y;
	inf_param.in_win.h_size = (UINT32)inWin.w;
	inf_param.in_win.v_size = (UINT32)inWin.h;
	/* set display info */
	ret = vpq_hwrap_setpicdisplayinfo((void *)&inf_param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);
#endif

	return ret;
}

/**
* set vp output window
*
* @param vpSrcId [IN] UINT32
* @param outWin [IN] LX_DE_RECT_T
*
* @return int
*/
int vp_kwrap_setoutwin(UINT32 vpSrcId, LX_DE_RECT_T outWin)
{
	int ret = RET_ERROR;
	LX_PE_INF_DISPLAY_T inf_param;
	CHECK_SRC_ID(vpSrcId);
#if 0
	//outWin.x = _gDeOutWin[vpSrcId].x = outWin.x;
	//outWin.y = _gDeOutWin[vpSrcId].y = outWin.y;
	//outWin.w = _gDeOutWin[vpSrcId].w = outWin.w;
	//outWin.h = _gDeOutWin[vpSrcId].h = outWin.h;

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Set wId[%d] Window out_xywh(%d,%d,%d,%d)***", \
			vpSrcId,outWin.x, outWin.y, outWin.w, outWin.h);

	ret = de_kwrap_setoutwin((UINT8)vpSrcId, &outWin);
#endif
	memcpy(&(_gVP_PicInfo.o_win[vpSrcId]), &outWin, sizeof(LX_DE_RECT_T));

	inf_param.win_id = (vpSrcId<1)? LX_PE_WIN_0:LX_PE_WIN_1;
	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&inf_param);
	inf_param.info_type = LX_PE_INFO_OUT_WIN;
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);
	inf_param.out_win.x_ofst = (UINT32)outWin.x;
	inf_param.out_win.y_ofst = (UINT32)outWin.y;
	inf_param.out_win.h_size = (UINT32)outWin.w;
	inf_param.out_win.v_size = (UINT32)outWin.h;
	/* set display info */
	ret = vpq_hwrap_setpicdisplayinfo((void *)&inf_param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);
#endif
	return ret;
}

/**
 * Get timing infor from 3Channel ADC
 *
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN/OUT] kwrap_vp_timing_info_t *
 *
 * @return int
 */
int vp_kwrap_readtiminginfo_frm_adc(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming)
{
	int ret = RET_OK;
	LX_AFE_ADC_TIMING_INFO_T	adc_timing;

	memset(&adc_timing , 0 , sizeof(LX_AFE_ADC_TIMING_INFO_T));

#ifdef INCLUDE_KDRV_AFE
	//if (afe_kwrap_isopen() == RET_ERROR)	{
		//ret = RET_ERROR;
		//goto func_exit;
	//}

//	ret = afe_kwrap_adc_get_timing_info(&adc_timing);
//	if (RET_OK != ret) goto func_exit;
#endif

	bufTiming->hFreq	= adc_timing.u16_HFreq;
	bufTiming->vFreq	= adc_timing.u16_VFreq;
	bufTiming->hTotal	= adc_timing.u16_HTotal;
	bufTiming->vTotal	= adc_timing.u16_VTotal;
	bufTiming->hStart 	= adc_timing.u16_HStart;
	bufTiming->vStart 	= adc_timing.u16_VStart;
	bufTiming->hActive 	= adc_timing.u16_HActive;
	bufTiming->vActive 	= adc_timing.u16_VActive;
	bufTiming->scanType = adc_timing.u8_ScanType;
	bufTiming->standard = LX_NON_STANDARD;
	bufTiming->vdLock 	= TRUE;
	bufTiming->extInfo 	= VP_EXT_2D_FORMAT;
	bufTiming->order3D 	= VP_3D_ORDER_LR;

// func_exit:
	return ret;
}

/**
 * Read timing infor from CVD
 *
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN/OUT] kwrap_vp_timing_info_t *
 *
 * @return int
 */
int vp_kwrap_readtiminginfo_frm_cvd(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming)
{
	int ret = RET_OK;

	BOOLEAN		cvdSync;
	LX_AFE_CVD_TIMING_INFO_T	cvd_timing= {0, };

	memset(&cvd_timing , 0 , sizeof(LX_AFE_CVD_TIMING_INFO_T));

	/*if (afe_kwrap_isopen() == RET_ERROR){
		ret = RET_ERROR;
		goto func_exit;
	}*/

#ifdef INCLUDE_KDRV_AFE
	ret = afe_kwrap_cvd_sync_exist(LX_CVD_MAIN, &cvdSync);
	if (RET_OK != ret) goto func_exit;

	if (cvdSync)
	{
		ret = afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &cvd_timing);
		if (RET_OK != ret) goto func_exit;

		bufTiming->hFreq	= cvd_timing.u16_HFreq;
		bufTiming->vFreq	= cvd_timing.u16_VFreq;
		bufTiming->hTotal	= 0;
		bufTiming->vTotal	= 0;
		bufTiming->hStart 	= cvd_timing.u16_HStart;
		bufTiming->vStart 	= cvd_timing.u16_VStart;
		bufTiming->hActive 	= cvd_timing.u16_HSize;
		bufTiming->vActive 	= cvd_timing.u16_VSize;
		bufTiming->scanType = VP_INTERLACED;
		bufTiming->standard = cvd_timing.cvd_standard;
		bufTiming->vdLock 	= TRUE;
		bufTiming->extInfo 	= VP_EXT_2D_FORMAT;
		bufTiming->order3D 	= VP_3D_ORDER_LR;
	}
	else
	{
		if (vpInputSrc.Type == SRC_INPUT_ATV)
		{
			ret = afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &cvd_timing);
			if (RET_OK != ret) goto func_exit;

			bufTiming->hFreq	= cvd_timing.u16_HFreq;
			bufTiming->vFreq	= cvd_timing.u16_VFreq;
			bufTiming->hTotal	= 0;
			bufTiming->vTotal	= 0;
			bufTiming->hStart 	= cvd_timing.u16_HStart;
			bufTiming->vStart 	= cvd_timing.u16_VStart;
			bufTiming->hActive 	= cvd_timing.u16_HSize;
			bufTiming->vActive 	= cvd_timing.u16_VSize;
			bufTiming->scanType = VP_INTERLACED;
			bufTiming->standard = LX_NON_STANDARD;
			bufTiming->vdLock 	= FALSE;
			bufTiming->extInfo 	= VP_EXT_2D_FORMAT;
			bufTiming->order3D 	= VP_3D_ORDER_LR;
		}
		else
		{
			bufTiming->hFreq	= 0;
			bufTiming->vFreq	= 0;
			bufTiming->hTotal	= 0;
			bufTiming->vTotal	= 0;
			bufTiming->hStart 	= 0;
			bufTiming->vStart 	= 0;
			bufTiming->hActive 	= 0;
			bufTiming->vActive 	= 0;
			bufTiming->scanType = VP_INTERLACED;
			bufTiming->standard = LX_NON_STANDARD;
			bufTiming->vdLock 	= FALSE;
			bufTiming->extInfo 	= VP_EXT_2D_FORMAT;
			bufTiming->order3D 	= VP_3D_ORDER_LR;
		}
	}
#endif

func_exit:

	return ret;
}

#ifdef USE_VIDEO_FOR_FPGA
int vp_kwrap_dbg_cvisrctype(UINT32 vpSrcId, LX_HDMI_TIMING_INFO_T *hdmi_timing, kwrap_vp_timing_info_t *bufTiming)
{
	int type = g_vp_kwrap_dbg_cvisrctype;

	if (!hdmi_timing || !bufTiming)
	{
		return RET_OK;
	}

	hdmi_timing->vFreq = 600;
	hdmi_timing->hActive = 3840;
	hdmi_timing->vActive = 2160;
	hdmi_timing->scanType = 1;
	bufTiming->colordomain = LX_HDMI_CS_YCBCR444_709;

	//0:normal,1:4K60p,2:4K120p,3:2K60,4:2K60i,5:2K120p,6:3K60p,7:3K120p
	switch (type)
	{
		case 2:
			hdmi_timing->vFreq = 1200;
			break;
		case 3:
		case 4:
		case 5:
			hdmi_timing->hActive = 1920;
			hdmi_timing->vActive = 1080;
			if (type == 4)	hdmi_timing->scanType = 0;
			if (type == 5)	hdmi_timing->vFreq = 1200;
			break;
		case 6:
		case 7:
			hdmi_timing->hActive = 2880;
			hdmi_timing->vActive = 1620;
			if (type == 7)	hdmi_timing->vFreq = 1200;
			break;
		default:
			break;
	}

	return RET_OK;
}
#endif

/**
 * Read timing info from HDMI
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN/OUT] kwrap_vp_timing_info_t
 *
 * @return int
 */
int vp_kwrap_readtiminginfo_frm_hdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming)
{
	int ret = RET_ERROR;
	static UINT8	prev_isDolbyHDR = 0;

	LX_HDMI_TIMING_INFO_T		hdmi_timing	= {0, };
	int i = 0;
	const s0_enum *pExtInfoTbl;

	memset(&hdmi_timing , 0 , sizeof(LX_HDMI_TIMING_INFO_T));

#ifdef USE_VIDEO_FOR_FPGA
	ret = vp_kwrap_dbg_cvisrctype(vpSrcId,&hdmi_timing,bufTiming);
#endif

#ifdef INCLUDE_KDRV_HDMI20
	ret = KWARP_HDMI20_RX_GetTimingInfo(vpInputSrc.Attr, &hdmi_timing, 1);
#endif

	if (RET_OK != ret) goto func_exit;

	bufTiming->hFreq	= hdmi_timing.hFreq;
	bufTiming->vFreq	= hdmi_timing.vFreq;
	bufTiming->hTotal	= hdmi_timing.hTotal;
	bufTiming->vTotal	= hdmi_timing.vTotal;
	bufTiming->hStart 	= hdmi_timing.hStart;
	bufTiming->vStart 	= hdmi_timing.vStart;
	bufTiming->hActive 	= hdmi_timing.hActive;
	bufTiming->vActive 	= hdmi_timing.vActive;
	bufTiming->scanType = hdmi_timing.scanType;
	bufTiming->standard = LX_NON_STANDARD;
	bufTiming->vdLock 	= FALSE;
	bufTiming->pixelRepeat = hdmi_timing.PixelRepeat;
	bufTiming->isDolbyHDR  = hdmi_timing.isDolbyHDR;
	bufTiming->isPVOMode   = hdmi_timing.isPVOMode;
	bufTiming->isFreeSyncMode = hdmi_timing.isFreeSyncMode;
	bufTiming->isGSyncMode    = hdmi_timing.isGSyncMode;
	bufTiming->isVrrMode      = hdmi_timing.isVrrMode;
	bufTiming->isFvaMode      = hdmi_timing.isFvaMode;
	bufTiming->isMConst       = hdmi_timing.isMConst;
	bufTiming->pixelClock = hdmi_timing.pixelClock;
	bufTiming->phyMode    = hdmi_timing.phyMode;
	bufTiming->isDSC      = hdmi_timing.isDSC;
	bufTiming->avi_colorspace = (LX_DE_AVI_COLORSPACE_T)hdmi_timing.csc;
	bufTiming->isQmsMode      = hdmi_timing.isQmsMode;
	bufTiming->qmsTFR         = hdmi_timing.qmsTFR;
	bufTiming->qmsBaseRate    = hdmi_timing.qmsBaseRate;
	bufTiming->deepColorMode  = hdmi_timing.deepColorMode;

	if(prev_isDolbyHDR != hdmi_timing.isDolbyHDR)
		VP_NOTI("$$$$$$$$$$$  hdmi_timing.isDolbyHDR   = %d", hdmi_timing.isDolbyHDR);
	prev_isDolbyHDR = hdmi_timing.isDolbyHDR;

	pExtInfoTbl = &HDMI_3D_TYPE[0];
	for (i = 0; i < TBL_NUM(HDMI_3D_TYPE) ; i++, pExtInfoTbl++)
	{
		if (hdmi_timing.extInfo == pExtInfoTbl->PreEnum)
		{
			bufTiming->extInfo = pExtInfoTbl->PostEnum;
			break;
		}
		bufTiming->extInfo = pExtInfoTbl->PostEnum;
	}

	bufTiming->order3D 	= VP_3D_ORDER_LR;

#ifdef INCLUDE_KDRV_HDMI20
	ret = KWARP_HDMI20_RX_GetColorDomain(vpInputSrc.Attr, (LX_HDMI_COLOR_STATUS_T *)&(bufTiming->colordomain));
	if (RET_OK != ret) goto func_exit;
#endif
	ret = de_kwrap_gethdmi444mode(vpSrcId, (LX_DE_HDMI444_MODE_T *)&(bufTiming->hdmi444mode));

func_exit:
	return ret;
}

/**
 * Read timing info from VDEC
 *
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN/OUT] kwrap_vp_timing_info_t
 *
 * @return int
 */
int vp_kwrap_readtiminginfo_frm_vdec(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming)
{
	int ret = RET_ERROR;

	LX_DE_MPEG_TIMING_INFO_T	vdec_timing = {0, };
	int i = 0;
	const s0_enum *pExtInfoTbl;
	LX_DE_CAPACITY_T capa;
	LX_DE_SRC_STATUS_T srcStatus;
	UINT32 win_id = 0;

	ret = de_kwrap_getcapacity(&capa);
	if (RET_OK != ret) return ret;

	memset(&vdec_timing , 0 , sizeof(LX_DE_MPEG_TIMING_INFO_T));

	win_id = vpInputSrc.Port;
	if (vpInputSrc.Type == SRC_INPUT_JPG)
	{
	#ifdef JPEG_FROM_CPU_TO_VP
		vpInputSrc.Port = vpInputSrc.Port + capa.mvir_start_num;
	#else
		vpInputSrc.Port = vpInputSrc.Port;
	#endif
	}
	//ret = vdec_kwrap_getdisplayrunningstatus((int)vpInputSrc.Port, &vdec_timing);
	if (RET_OK != ret){
		goto func_exit;
	}

	memset(&srcStatus,0,sizeof(srcStatus));
	srcStatus.win_id = win_id;//20240626, Prevent timing error(not support wid(2)) in photo input
	srcStatus.status_type  = LX_DE_SRC_STATUS_VDEC_INFO;
	srcStatus.inSrcPort[0] = vpInputSrc.Port;
	srcStatus.inSrcPort[1] = vpInputSrc.Port;
	ret = de_kwrap_getsourcestatus(&srcStatus);
	if (RET_OK != ret){
		goto func_exit;
	}

	vdec_timing.v_freq  = srcStatus.vdecInfo.v_freq;
	vdec_timing.h_start = srcStatus.vdecInfo.h_start;
	vdec_timing.v_start = srcStatus.vdecInfo.v_start;
	vdec_timing.h_size  = srcStatus.vdecInfo.h_size;
	vdec_timing.v_size  = srcStatus.vdecInfo.v_size;
	vdec_timing.isProg  = srcStatus.vdecInfo.isProg;
	if (vdec_timing.isProg==LX_DE_INTERLACED)
	{
		vdec_timing.v_freq = vdec_timing.v_freq*2;
	}

	bufTiming->hFreq	= 0;
	bufTiming->vFreq	= (vdec_timing.v_freq/10);
	bufTiming->hTotal	= 0;
	bufTiming->vTotal	= 0;
	bufTiming->hStart 	= vdec_timing.h_start;
	bufTiming->vStart 	= vdec_timing.v_start;
	bufTiming->hActive 	= vdec_timing.h_size;
	bufTiming->vActive 	= vdec_timing.v_size;
	bufTiming->scanType = vdec_timing.isProg;
	bufTiming->standard = LX_NON_STANDARD;
	bufTiming->vdLock 	= FALSE;
	bufTiming->svp      = srcStatus.vdecInfo.svp;

	if (bufTiming->hActive == 0 && bufTiming->vActive == 0)
	{
		bufTiming->extInfo = VP_EXT_2D_FORMAT;
	}
	else
	{
		pExtInfoTbl = &MVI_3D_TYPE[0];
		for (i = 0; i < TBL_NUM(MVI_3D_TYPE) ; i++, pExtInfoTbl++)
		{
			if (vdec_timing.mvi_3dfmt_info == pExtInfoTbl->PreEnum)
			{
				bufTiming->extInfo = pExtInfoTbl->PostEnum;
				break;
			}
			bufTiming->extInfo = pExtInfoTbl->PostEnum;
		}
	}
	bufTiming->order3D 	= VP_3D_ORDER_LR;

func_exit:
	return ret;
}

/*
* Set Pic Format Info
*
* @param	srcId 		[IN] UINT32
* @param 	timing 		[IN] const kwrap_vp_timing_info_t *
* @param    cviInfo		[IN] const LX_DE_CVI_SRC_TYPE_T *
* @return int
*/
int vp_kwrap_setpicformatinfo(UINT32 srcId, const kwrap_vp_timing_info_t *timing, const LX_DE_CVI_SRC_TYPE_T *cviInfo)
{
	int ret = RET_OK;
	UINT32 win_id = 0;
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
	LX_PE_DEFAULT_SETTINGS_T dft_param;
	kwrap_vp_src_info_t *pSrcCfg = NULL;

	CHECK_SRC_ID(srcId);

	if (srcId<1)
	{
		win_id = 0;
		cur_inf_param.win_id = LX_PE_WIN_0;
	}
	else
	{
		#ifdef PE_EXTEND_WINID
		win_id = srcId;
		cur_inf_param.win_id = (LX_PE_WIN_ID)srcId;
		#else
		win_id = 1;
		cur_inf_param.win_id = LX_PE_WIN_1;
		#endif
	}
	pSrcCfg = &_gVPInputSrcCfg[win_id];

	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);
#endif
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	cur_inf_param.info_type = LX_PE_INFO_PIC_FORMAT;
	/**
	* causion, these items only in this function :
	* src_type, fmt_type, cstd_type, in_f_rate, fr_type,
	* in_h_size, in_v_size, scan_type
	*/

	/* src_type */
	cur_inf_param.src_type = vp_kwrap_convvptopicsrcinfo(pSrcCfg->Type);

	/*Get PE format type */
	if(timing->vActive > 0 && timing->hActive > 0)	//@null video, no change format
	{
		vp_kwrap_getpeformattype(pSrcCfg->Type,timing,&(cur_inf_param.fmt_type),cur_inf_param.hdmi_type);
	}

	/*Get PE standard type: Only get standard in-case of analog src */
	if(pSrcCfg->Type == SRC_INPUT_ATV || pSrcCfg->Type == SRC_INPUT_CVBS || pSrcCfg->Type == SRC_INPUT_SCART \
		|| pSrcCfg->Type == SRC_INPUT_SCART_RGB_BYPASS){
			vp_kwrap_getpecolorstdtype(pSrcCfg->Type,cviInfo,&(cur_inf_param.cstd_type));
	}

	/* in_fr, fr_type */
	cur_inf_param.in_f_rate = timing->vFreq;
	if ((timing->vFreq>495 && timing->vFreq<505) || \
		(timing->vFreq>245 && timing->vFreq<255))
	{
		cur_inf_param.fr_type = LX_PE_FR_50HZ;
	}
	else
	{
		cur_inf_param.fr_type = LX_PE_FR_60HZ;
	}

	/* h, v size */
	cur_inf_param.in_h_size = timing->hActive;
	cur_inf_param.in_v_size = timing->vActive;
	/* scan_type */
	if (timing->scanType==VP_INTERLACED)
	{
		cur_inf_param.scan_type = LX_PE_SCAN_INTERLACE;
	}
	else
	{
		cur_inf_param.scan_type = LX_PE_SCAN_PROGRESS;
	}
	/* set default */
	if (pre_inf_param.src_type != cur_inf_param.src_type || \
		pre_inf_param.fmt_type != cur_inf_param.fmt_type || \
		pre_inf_param.cstd_type != cur_inf_param.cstd_type || \
		pre_inf_param.in_f_rate != cur_inf_param.in_f_rate || \
		pre_inf_param.fr_type != cur_inf_param.fr_type || \
		pre_inf_param.in_h_size != cur_inf_param.in_h_size || \
		pre_inf_param.in_v_size != cur_inf_param.in_v_size || \
		pre_inf_param.scan_type != cur_inf_param.scan_type)
	{
		if (1)//_gVP_DebugPrintOn)
		{
			DE_NOTI("[VP][inf]in_src:%d,cvd_std:%d,"\
				"hvAct:%d,%d,vF:%d,scan:%d\n", \
				pSrcCfg->Type, cviInfo->cvd_color_std, \
				timing->hActive, timing->vActive, \
				timing->vFreq, timing->scanType);
			DE_NOTI("[VP][set]wid:%d,src:%d->%d,fmt:%d->%d,cstd:%d->%d,"\
				"fr:%d(%d)->%d(%d),h,v:%d,%d->%d,%d,scan:%d->%d\n", \
				cur_inf_param.win_id, \
				pre_inf_param.src_type, cur_inf_param.src_type, \
				pre_inf_param.fmt_type, cur_inf_param.fmt_type, \
				pre_inf_param.cstd_type, cur_inf_param.cstd_type, \
				pre_inf_param.fr_type, pre_inf_param.in_f_rate, \
				cur_inf_param.fr_type, cur_inf_param.in_f_rate, \
				pre_inf_param.in_h_size, pre_inf_param.in_v_size, \
				cur_inf_param.in_h_size, cur_inf_param.in_v_size, \
				pre_inf_param.scan_type, cur_inf_param.scan_type);
		}

		/* set disp info */
#ifdef INCLUDE_KDRV_PE
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, \
			"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);

		/* set default settings */
		dft_param.win_id = cur_inf_param.win_id;
		ret = vpq_hwrap_setdefaultsettings((void *)&dft_param);
		VP_CHECK_CODE( ret != RET_OK, ret = RET_ERROR, \
			"[VP %d] vpq_hwrap_setdefaultsettings( ) function return error \n", __L__);
#endif
		/* update pic src type on pic info */
		_gVP_PicInfo.pic_src_type[win_id] = (UINT32)cur_inf_param.src_type;
	}
	return ret;
}

/**
 * check external input source depending on specification.
 *
 * @param vpSrcId		[IN] UINT32
 * @param pVpSrcInfo	[IN] kwrap_vp_src_info_t *
 *
 * @return int
 */
static int vp_kwrap_checkexternalinputsrc(UINT32 vpSrcId,kwrap_vp_input_src_t vpOtherSrcType, kwrap_vp_src_info_t *pVpSrcInfo)
{
	int ret = RET_OK;

	// need Add  cheak H/W dependency
	// W/ or W/O ACE chip and FRC chip
	VP_PRINT("[VP] %s(%d)  \n", 	__F__, __L__);

	switch (pVpSrcInfo->Type)
	{
		case SRC_INPUT_VGA:
			{
				if (vpOtherSrcType == SRC_INPUT_YPBPR || \
					(vpOtherSrcType == SRC_INPUT_SCART || vpOtherSrcType == SRC_INPUT_SCART_RGB_BYPASS) )
					ret = RET_ERROR;
			}
			break;

		case SRC_INPUT_YPBPR:
			{
				if (vpOtherSrcType == SRC_INPUT_VGA || \
					(vpOtherSrcType == SRC_INPUT_SCART || vpOtherSrcType == SRC_INPUT_SCART_RGB_BYPASS) )
					ret = RET_ERROR;
			}
			break;

		case SRC_INPUT_ATV:
			{
				if (vpOtherSrcType == SRC_INPUT_CVBS || \
					(vpOtherSrcType == SRC_INPUT_SCART || vpOtherSrcType == SRC_INPUT_SCART_RGB_BYPASS) )
					ret = RET_ERROR;
			}
			break;

		case SRC_INPUT_CVBS:
			{
				if (vpOtherSrcType == SRC_INPUT_ATV || \
					(vpOtherSrcType == SRC_INPUT_SCART || vpOtherSrcType == SRC_INPUT_SCART_RGB_BYPASS) )
					ret = RET_ERROR;
			}
			break;

		case SRC_INPUT_SCART:
		case SRC_INPUT_SCART_RGB_BYPASS:
			{
				if (vpOtherSrcType == SRC_INPUT_VGA || vpOtherSrcType == SRC_INPUT_YPBPR || \
					vpOtherSrcType == SRC_INPUT_ATV || vpOtherSrcType == SRC_INPUT_CVBS )
					ret = RET_ERROR;
			}
			break;
		default :
			break;
	}

	if (ret == RET_ERROR)
		VP_ERROR("[VP %d] Not Support :: SrcId[%d] Current Input Type[%d]  Other Input Type[%d] \n", \
				__L__, vpSrcId, pVpSrcInfo->Type, vpOtherSrcType);

	return ret;
}

/**
 * reset timing info
 *
 * @param vpSrcId			[IN] UINT32
 *
 * @return int
 */
int vp_kwrap_resettiminginfo(UINT32 vpSrcId)
{
	CHECK_SRC_ID(vpSrcId);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] srcID[%d]  \n", vpSrcId);

	_gCurVpTiming[vpSrcId].hFreq = 0;
	_gCurVpTiming[vpSrcId].vFreq = 0;
	_gCurVpTiming[vpSrcId].hTotal = 0;
	_gCurVpTiming[vpSrcId].vTotal = 0;

	_gCurVpTiming[vpSrcId].hStart = 0;
	_gCurVpTiming[vpSrcId].vStart = 0;
	_gCurVpTiming[vpSrcId].hActive = 0;
	_gCurVpTiming[vpSrcId].vActive = 0;

	_gCurVpTiming[vpSrcId].scanType = VP_INTERLACED;
	_gCurVpTiming[vpSrcId].standard = LX_NON_STANDARD;
	_gCurVpTiming[vpSrcId].vdLock = FALSE;

	_gCurVpTiming[vpSrcId].extInfo	= VP_EXT_2D_FORMAT;
	_gCurVpTiming[vpSrcId].order3D 	= VP_3D_ORDER_LR;

	return RET_OK;
}

/**
 * set VCR out
 *
 * @param VpInputSrc		[IN] kwrap_vp_src_info_t *
 * @param vpInputSrc_sub 	[IN] kwrap_vp_input_src_t
 * @param int				[IN] denc_on_off
 * @return int
 */
int vp_kwrap_setvcroutsrc(kwrap_vp_input_src_t vpInputSrc, kwrap_vp_input_src_t vpInputSrc_sub, int denc_on_off)
{
	int ret = RET_OK;
	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] vpInputsrc[%d] vpInputsrc_sub[%d] on_off[%d] \n", vpInputSrc, vpInputSrc_sub, denc_on_off);

#if 0
	if (vpInputSrc == SRC_INPUT_DTV) {
		if (denc_on_off)
			KADP_DENC_OnOff(TRUE);
		else
			KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_MONITOR);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_DAC, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);
	}
	else if (vpInputSrc == SRC_INPUT_ATV) {
		KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_CVBS1_WITHOUT_CLAMPING);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_CVBS_WITHOUT_CLAMPING, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);
	}
	else if ( (vpInputSrc == SRC_INPUT_CVBS) || (vpInputSrc == SRC_INPUT_SCART) ) {
		KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_CVBS1_WITHOUT_CLAMPING);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_CVBS_WITH_CLAMPING_AV, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);	// for AV input : bypass clamping & cvd clamping should operate.
	}
	else if ( (vpInputSrc == SRC_INPUT_MVI) || (vpInputSrc == SRC_INPUT_JPG) ) {
		if (denc_on_off)
			KADP_DENC_OnOff(TRUE);
		else
			KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_MONITOR);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_DAC, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);
	}
	else if ( (vpInputSrc_sub == SRC_INPUT_CVBS) || (vpInputSrc_sub == SRC_INPUT_SCART) ) {
		KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_CVBS1_WITH_CLAMPING);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_CVBS_WITH_CLAMPING_AV, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);	// for AV Recording : cvd clamping should operate. (bypass clamping ? don't care)
	}
	else if (vpInputSrc_sub == SRC_INPUT_ATV) {
		KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_CVBS1_WITHOUT_CLAMPING);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_CVBS_WITHOUT_CLAMPING, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);	// for ATV Background Recording
	}
	else {
		KADP_DENC_OnOff(FALSE);
		KADP_DENC_Set_Source(LX_DENC_SOURCE_CVBS1_WITH_CLAMPING);
		KADP_AFE_CVD_Bypass_Control(CVD_BYPASS_CVBS_WITH_CLAMPING, CVD_BYPASS_DAC, CVD_BYPASS_CVBS_IN1);	// not watching ATV/AV, not recording ATV/AV
	}
#endif

	return ret;
}

/**
 * set windows to blank
 *
 * @param vpSrcId		[IN] UINT32
 * @param pVpSrcInfo	[IN/OUT] kwrap_vp_src_info_t
 * @return int
 */
static int vp_kwrap_inputsrcapply(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo) //apply
{
	int ret = RET_OK;
	LX_DE_INPUT_SOURCE_T	deInputSrc = {LX_DE_WIN_MAX, LX_DE_IN_SRC_NONE, 0};
	int cnt = 0, size = sizeof(VP_TO_DE_SRC_MAP)/sizeof(kwrap_vp_src_de_map_t);
	LX_DE_CAPACITY_T capa;

	CHECK_NULL(pVpSrcInfo);
	CHECK_SRC_ID(vpSrcId);

#ifdef SEE_TV
#else
	if(lx_chip_rev() >= LX_CHIP_REV(H15, A0) && lx_chip_rev() < LX_CHIP_REV(M16, A0) && !_gVPQuadWin) {/*H15 only*/
		if(pVpSrcInfo->Type >= SRC_INPUT_VGA && pVpSrcInfo->Type <= SRC_INPUT_HDMI && pVpSrcInfo->Port == 1){
			pVpSrcInfo->Port = 2;
			VP_PRINT("[VP] %s(%d) force to use ch_C for 2nd path sourced from CVI.(type=%d port_changed=%d)\n", __F__, __L__, pVpSrcInfo->Type, pVpSrcInfo->Port);

		}
	}
#endif

	ret = de_kwrap_getcapacity(&capa);
	if (RET_OK != ret) return ret;

	deInputSrc.srcId= vpSrcId;

	for(cnt =0; cnt < size; cnt++)
	{
		if(VP_TO_DE_SRC_MAP[cnt].vpSrcType == pVpSrcInfo->Type){
			deInputSrc.srcType = VP_TO_DE_SRC_MAP[cnt].deSrcType;
			break;
		}
	}

	/*if(cnt == size || pVpSrcInfo->Type == SRC_INPUT_VGA ){
		VP_BREAK_WRONG(pVpSrcInfo->Type);
		return ret;
	}
	else*/ if(pVpSrcInfo->Type == SRC_INPUT_JPG ){
		#ifdef JPEG_FROM_CPU_TO_VP
			deInputSrc.srcType = LX_DE_IN_SRC_CPU;
			deInputSrc.srcPort = pVpSrcInfo->Port + capa.mvir_start_num;
		#else
			deInputSrc.srcType = LX_DE_IN_SRC_MVI;
			deInputSrc.srcPort = pVpSrcInfo->Port;
		#endif
	}
	else {
		deInputSrc.srcPort = pVpSrcInfo->Port;
		deInputSrc.srcAttr = pVpSrcInfo->Attr;
	}

	_gVPInSizeFromThread[vpSrcId].x = 0;
	_gVPInSizeFromThread[vpSrcId].y = 0;
	_gVPInSizeFromThread[vpSrcId].w = 0;
	_gVPInSizeFromThread[vpSrcId].h = 0;

	_gVPNoFirstFrame = 0; // initialize

#ifdef AUTO_INPUT_SET
	ret = vp_kwrap_setexternalinputsrc(vpSrcId, pVpSrcInfo);
	if (RET_OK != ret) return ret;
#endif
	ret = de_kwrap_setwinsrcport(&deInputSrc);
	if (RET_OK != ret)
	{
		VP_ERROR("[VP %d] Not Support :: SrcId[%d] Main Input Type[%d]  Sub Input Type[%d] \n", \
			__L__, vpSrcId, _gVPInputSrcCfg[LX_DE_WIN_0].Type, _gVPInputSrcCfg[LX_DE_WIN_1].Type);

		return ret;
	}

	//Reset timing and other info of global structure

	if (memcmp(&_gVPInputSrcCfg[vpSrcId], pVpSrcInfo, sizeof(kwrap_vp_src_info_t))  != 0)
		vp_kwrap_resettiminginfo(vpSrcId);

	_gVPInputSrcCfg[vpSrcId].Type = pVpSrcInfo->Type;
	_gVPInputSrcCfg[vpSrcId].Port = pVpSrcInfo->Port;
	_gVPInputSrcCfg[vpSrcId].Attr = pVpSrcInfo->Attr;
	_gVPInputSrcCfg[vpSrcId].Resv = pVpSrcInfo->Resv;

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] SrcId = %d  Type = %d  Port = %d  Attr = %d Resv =%d \n",\
			vpSrcId, pVpSrcInfo->Type, pVpSrcInfo->Port, pVpSrcInfo->Attr, pVpSrcInfo->Resv);


	return ret;
}

/**
 * set input source path of scaler windows
 *
 * @param vpSrcId		[IN] UINT32
 * @param pVpSrcInfo	[IN] kwrap_vp_src_info_t *
 *
 * @return int
 */
int vp_kwrap_setinputsrc(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo)
{
	int ret = RET_OK;

	CHECK_NULL(pVpSrcInfo);
	CHECK_SRC_ID(vpSrcId);
	VP_CHECK_CODE(pVpSrcInfo->Type>=SRC_INPUT_MAX, \
		return RET_ERROR, "[VP %d] SrcType[%d] is wrong.\n", __L__, pVpSrcInfo->Type);
#ifdef SEE_TV
#else
	if(lx_chip_rev() < LX_CHIP_REV(M16, A0) && pVpSrcInfo->Type == SRC_INPUT_VGA)
		VP_WARN("[VP %d] VGA is not supported.", __L__);
#endif
	do {
		if (memcmp(&_gVPInputSrcCfg[vpSrcId], pVpSrcInfo, sizeof(kwrap_vp_src_info_t))  != 0)
			vp_kwrap_resettiminginfo(vpSrcId);

		if (_gVP_DebugPrintOn)
			VP_DEBUG("[VP] SrcId = %d  Type = %d  Port = %d  Attr = %d Resv =%d \n",\
				vpSrcId, pVpSrcInfo->Type, pVpSrcInfo->Port, pVpSrcInfo->Attr, pVpSrcInfo->Resv);

		_gVPInputSrcTemp[vpSrcId].Type = pVpSrcInfo->Type;
		_gVPInputSrcTemp[vpSrcId].Port = pVpSrcInfo->Port;
		_gVPInputSrcTemp[vpSrcId].Attr = pVpSrcInfo->Attr;
		_gVPInputSrcTemp[vpSrcId].Resv = pVpSrcInfo->Resv;

		// init input window
		_gVPInWin[vpSrcId].x = 0;
		_gVPInWin[vpSrcId].y = 0;
		_gVPInWin[vpSrcId].w = 0;
		_gVPInWin[vpSrcId].h = 0;

		if (_gVPInputSrcCfg[vpSrcId].Type == SRC_INPUT_NONE || _gVPInputSrcTemp[vpSrcId].Type == SRC_INPUT_NONE)
		{
			vp_kwrap_inputsrcapply(vpSrcId, &_gVPInputSrcTemp[vpSrcId]);
		}
		else
		{
			VP_LOCK();
			_gVPInputChg[vpSrcId] = 1;
			VP_UNLOCK();
		}
	}while (0);

	return ret;
}

/**
 * set external input source path
 *
 * @param vpSrcId		[IN] UINT32
 * @param pVpSrcInfo	[IN] kwrap_vp_src_info_t *
 *
 * @return int
 */
int vp_kwrap_setexternalinputsrc(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo)
{
	int ret = RET_OK;

	kwrap_vp_input_src_t otherSrcType = SRC_INPUT_NONE;

	CHECK_NULL(pVpSrcInfo);
	CHECK_SRC_ID(vpSrcId);

	//Harish:: We are not checking return type so no use of calling this API
	if (vpSrcId == LX_DE_WIN_MAIN)
		otherSrcType =_gVPInputSrcCfg[LX_DE_WIN_SUB].Type;
	else
		otherSrcType =_gVPInputSrcCfg[LX_DE_WIN_MAIN].Type;

	//Harish: This API is also not required as don't bother about result
	vp_kwrap_checkexternalinputsrc(vpSrcId,otherSrcType, pVpSrcInfo);
	//ret = vp_kwrap_checkexternalinputsrc(vpSrcId, pVpSrcInfo);
	//if (ret) break;

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] SrcID[%d]  srcType[%d] \n", vpSrcId, pVpSrcInfo->Type );


	//vport_output = LX_AFE_VPORT_OUT_A;

	// ACE Chip - Path and Power control
	switch (pVpSrcInfo->Type)
	{
		case SRC_INPUT_VGA:
			{
				VP_ERROR("[VP %d] Wrong SrcType = %d  \n", __L__, pVpSrcInfo->Type);
				ret = RET_ERROR;
			} break;

		case SRC_INPUT_YPBPR:
			{
#ifdef INCLUDE_KDRV_AFE
				afe_kwrap_cvd_disconnectmodule();
				afe_kwrap_cvd_disablemodule();
//				afe_kwrap_adc_enablemodule();
//				afe_kwrap_adc_connectmodule(LX_ADC_INPUT_SOURCE_YPBPR, pVpSrcInfo->Attr);
#endif
			} break;

		case SRC_INPUT_ATV:
		case SRC_INPUT_CVBS:
			{
#ifdef INCLUDE_KDRV_AFE
//				afe_kwrap_adc_disconnectmodule();
//				afe_kwrap_adc_disablemodule();
				afe_kwrap_cvd_enablemodule();

				if (pVpSrcInfo->Type == SRC_INPUT_ATV)
					afe_kwrap_cvd_connectmodule(LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF, pVpSrcInfo->Attr);
				else
					afe_kwrap_cvd_connectmodule(LX_CVD_INPUT_SOURCE_ATTRIBUTE_AV, pVpSrcInfo->Attr);
#endif

			} break;

		case SRC_INPUT_SCART:
			{
#ifdef INCLUDE_KDRV_AFE
				afe_kwrap_cvd_enablemodule();
				afe_kwrap_cvd_connectmodule(LX_CVD_INPUT_SOURCE_ATTRIBUTE_SCART, pVpSrcInfo->Attr);
//				afe_kwrap_adc_enablemodule();

				//KADP_AFE_ADC_ConnectModule(LX_ADC_INPUT_SOURCE_RGB_SCART, pVpSrcInfo->Attr);
				/* for SCART RGB, Port Number of ADC is fixed to COMP1 port */
				/* 00:ypbpr1, 01:ypbpr2 */
				/* Valid Port Number should be recieved from TV M/W */
//				afe_kwrap_adc_connectmodule(LX_ADC_INPUT_SOURCE_RGB_SCART, 1);
#endif

			} break;

		case SRC_INPUT_SCART_RGB_BYPASS:
			{
#if 0
#ifdef SC_DBG
				lvds_source = LX_AFE_LVDS_SOURCE_3CH;
				KADP_AFE_LVDS_Src_Control(lvds_sel, lvds_power, lvds_type, lvds_source, lvds_mode);

				if ( (otherSrcType != SRC_INPUT_SCART) || (otherSrcType != SRC_INPUT_SCART_RGB_BYPASS) )
				{
					KADP_AFE_CVD_POWER_CONTROL(1);
					KADP_AFE_ADC_POWER_CONTROL(1);
				}

				/* HDMI1.4 code deleted by request of Mr.Wonsik.Do 2018.04.02 */
				//if (otherSrcType != SRC_INPUT_HDMI)
				//	KADP_HDMI_POWER_CONTROL(0);

				KADP_AFE_ADC_Set_Source_Type(LX_ADC_INPUT_SOURCE_RGB_SCART, LX_ADC_YPbPr_IN1);
				//KADP_AFE_ADC_Set_Source_Type(LX_ADC_INPUT_SOURCE_YPBPR, pVpSrcInfo->Attr);
				KADP_AFE_CVD_Set_Source_Type(LX_CVD_MAIN, LX_CVD_INPUT_SOURCE_CVBS, pVpSrcInfo->Attr, LX_AFE_CVBS_NONE, LX_CVD_INPUT_SOURCE_ATTRIBUTE_SCART);	// 	LX_AFE_CVBS_IN3 = 3,		///< CVBS_Input_3 scart
				KADP_AFE_CVD_SetSyncDetectionForTuning(FALSE);	//130206 : DTV only tunning
				//KADP_AFE_Select_Vport_Output(LX_AFE_VPORT_OUT_CVD, vport_output);
				KADP_AFE_ADC_Enable_Periodic_Signal_Info_Read(1);
				KADP_AFE_CVD_Start_Timer(LX_CVD_MAIN, 0);

				KADP_AFE_Set_Scart_Overlay(TRUE);
#endif
#endif
			} break;
		default :
			{
				VP_ERROR("[vp_kwrap_setexternalinputsrc] This API is only for ADC calibration\n");
			} break;
	}
#ifdef PIONEER_PLATFORM
	// SCART out source control
	if ( (pVpSrcInfo->Type == SRC_INPUT_ATV) || (otherSrcType == SRC_INPUT_ATV) )	// ATV Recording
		vp_kwrap_setvcroutsrc(SRC_INPUT_ATV, SRC_INPUT_NONE, 0);
	else if (vpSrcId == LX_DE_WIN_MAIN)
		vp_kwrap_setvcroutsrc(pVpSrcInfo->Type, SRC_INPUT_NONE, 1);
#endif

	return ret;
}

#if 0	//not used
/**
 * video device open
 * @param 	void
 * @return 	int
 */
int vp_kwrap_Open(void)
{
	int	ret = RET_OK;

#ifdef SEE_TV
#else
	kwrap_initsystem();
#endif
	VP_NOTI("[VP] VP open\n");

	ret = de_kwrap_open();
	VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open DE module\n", __L__);

//	ret = be_kwrap_open();
	VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open BE module\n", __L__);

	//ret = pe_kwrap_open();
	VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open PE module\n", __L__);

	//ret = apr_kwrap_open();
	VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open APR module\n", __L__);

	/*
	ret = afe_kwrap_open();
	VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open AFE module\n", __L__);

	ret = denv_kwrap_open();
	VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open DENC module\n", __L__);
	*/

	VP_INIT_LOCK();

	return ret;
}

/**
 * Initialize VP Block(DE, BE, PE, External input)
 * @param 	void
 * @return 	int
 */
int vp_kwrap_initialize(void)
{
	int	ret = RET_OK;

	if (!_gVP_INIT)
	{
		VP_NOTI("[VP] Initialize ");

#ifdef SEE_TV
#else
		if(lx_chip_rev() < LX_CHIP_REV(M17, C0))
		{
			use_input_window_wa = 1;
			VP_NOTI("Activate W/A code for input window !!!");
		}
#endif
		//ret = de_kwrap_init(TRUE);	/* FullHD */
		VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open DE initialize\n", __L__);

//		ret = be_kwrap_initialize(NULL);
		VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open BE initialize\n", __L__);

		//ret = pe_kwrap_init();
		VP_CHECK_CODE( ret < 0, ret = RET_ERROR, "[VP %d] Can't open PE initialize\n", __L__);

		de_kwrap_setcve(LX_DE_CVE_FROM_SRC, LX_DE_CVE_PAL);

		#ifdef V4L2_VSC_BBD_USE_PRIV
		#else
		vp_kwrap_initactivewin();
		#endif

		gpfnCallBackMuteOff = NULL;
		vp_kwrap_initpicinfo();
		_gVP_INIT = TRUE;

		ret |= de_kwrap_getfirmwareinfo(&_gVersion);
	}

	return ret;
}

/**
 * Uninitialize VP Block(DE, BE, PE, External input)
 * @param 	void
 * @return 	int
 */
 int vp_kwrap_uninitialize(void)
{
	VP_NOTI("[VP] close\n");

	//apr_kwrap_close();
	//pe_kwrap_close();
//	be_kwrap_close();
	de_kwrap_close();

	vp_kwrap_uninitpicinfo();

	#ifdef V4L2_VSC_BBD_USE_PRIV
	#else
	vp_kwrap_uninitactivewin();
	#endif

	_gVP_INIT = FALSE;
	return RET_OK;
}

/**
 * vp_kwrap_uninitpicinfo
 * @param 	void
 * @return 	int
 */
int vp_kwrap_uninitpicinfo(void)
{
	_g_vp_kwrap_pic_info_init = 0;
	return RET_OK;
}

/**
 * Check VP Initialized or not
 * @param 	void
 * @return 	BOOLEAN
 */
BOOLEAN vp_kwrap_isinitialized(void)
{
	return _gVP_INIT;
}

void vp_kwrap_dbg_initialize(void)
{
#if 0
	g_vp_logm_fd = KADP_LOGM_ObjRegister(KADP_VP);
	if (g_vp_logm_fd < 0)
	{
		printf("[%s:%u] fail register logm\n", __F__, __L__);
		return;
	}

	KADP_LOGM_BitMaskEnable(g_vp_logm_fd, LX_LOGM_LEVEL_NOTI);
	KADP_LOGM_BitMaskEnable(g_vp_logm_fd, LX_LOGM_LEVEL_ERROR);
	KADP_LOGM_BitMaskEnable(g_vp_logm_fd, LX_LOGM_LEVEL_WARNING);
#else
#endif
}

void vp_kwrap_dbg_shutdown(void)
{
	//int ret;

#if 0
	ret = KADP_LOGM_ObjDeregister(KADP_VP);
	if (ret < 0)
	{
		printf("[%s:%u] fail deregister logm\n", __F__, __L__);
		return;
	}
#else
#endif
	g_vp_logm_fd = -1;
}


/**
 * check mute on
 *
 * @param vpSrcId [IN] UINT32
 *
 * @return BOOLEAN
 */
BOOLEAN vp_kwrap_Ismuteon(UINT32 vpSrcId)
{
	BOOLEAN bOnOff = TRUE;
	if (vpSrcId<LX_DE_WIN_MAX)
	{
		bOnOff = _gVPMuteOnOff[vpSrcId];
	}
	return bOnOff;
}

/**
 * set windows to blank
 *
 * @param vpSrcId		[IN] UINT32
 * @param bOnOff		[IN] BOOLEAN
 * @param color		[IN] KADP_VP_WIN_COLOR_T
 * @param type		[IN] UINT32	0: DE  1: FRC
 *
 * @return int
 */

enum {
	_SC_MAIN = LX_DE_WIN_0,
	_SC_SUB   = LX_DE_WIN_1,
	_SC_SUB1,
	_SC_SUB2,
	_FRC,
	_MUTE_NUM_MAX,
};

int vp_kwrap_setwinblank(UINT32 vpSrcId, BOOLEAN bOnOff, kwrap_vp_win_color_t color, UINT32 type)
{
	int ret = RET_ERROR;
	int idx = _SC_MAIN;
	static UINT32 mute[_MUTE_NUM_MAX] = {0, 0, 0};
	static kwrap_vp_win_color_t muteColor[_MUTE_NUM_MAX] = {0, 0, 0};

	CHECK_SRC_ID(vpSrcId);

	if (type  == 1)	    idx = _FRC;
	else				    idx = vpSrcId;

	mute[idx] = bOnOff;
	muteColor[idx] = color;

#ifdef INCLUDE_KDRV_AFE
	// ATV Channel Change
	if (SRC_INPUT_ATV ==	_gVPInputSrcCfg[vpSrcId].Type)
	{
		if (_gVP_DebugPrintOn)
			VP_DEBUG("[VP] [ATV] Mode[%s] : srcId[%d]  bOnOff[%d] color[%d]  \n",\
				type ? "FRC":"DE", vpSrcId, bOnOff,color);
		afe_kwrap_cvd_atv_channel_change(bOnOff);
	}
#endif

	if (idx ==_FRC)
	{
		if (mute[_FRC])
		{
			ret = de_kwrap_setwinblank(LX_DE_WIN_0, mute[_FRC], muteColor[_FRC]);
			ret = de_kwrap_setwinblank(LX_DE_WIN_1, mute[_FRC], muteColor[_FRC]);
		}
		else //---------------- FRC unmute ��  Main/PIP mute recover
		{
			ret = de_kwrap_setwinblank(LX_DE_WIN_0, mute[_SC_MAIN], muteColor[_SC_MAIN]);
			ret = de_kwrap_setwinblank(LX_DE_WIN_1, mute[_SC_SUB], muteColor[_SC_SUB]);
		}
	}
	else
	{
		if (!mute[_FRC])
		{
			ret = de_kwrap_setwinblank(vpSrcId, bOnOff, color);
		}
	}

	/* update mute on,off */
	if (idx<LX_DE_WIN_MAX)
	{
		_gVPMuteOnOff[idx] = bOnOff;
	}

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Mode[%s] : srcId[%d]  bOnOff[%d] color[%d]  \n",\
				type ? "FRC":"DE", vpSrcId, bOnOff,color);

	return ret;
}

/**
 * thread to check source timing info.
 *
 * @param void
 *
 * @return int
 */
int vp_kwrap_thread(void)
{
	int ret = RET_OK;
	int i;
	static UINT16 prev_hActive[LX_DE_WIN_MAX] = {0}, prev_vActive[LX_DE_WIN_MAX] = {0};

	do {
		if (_gVP_INIT == FALSE)
		{
			VP_DEBUG("[VP] Thread Skip in the uninit \n");
			break;
		}

		for(i=0;i<LX_DE_WIN_MAX;i++)
		{
			if (_gVPInputChg[i] > 0)
			{
				VP_LOCK();
				_gVPInputChg[i] = _gVPInputChg[i] - 1;
				VP_UNLOCK();
				vp_kwrap_inputsrcapply(i, &_gVPInputSrcTemp[i]);

				if (_gVPInputChg[i] > 0)
				{
					VP_LOCK();
					_gVPInWinChg[i] = 0;
					VP_UNLOCK();
					if(_gVPInputSrcCfg[i].Type < SRC_INPUT_DTV )
						vp_kwrap_setinputwin(i, _gVPInWin[i]);
				}
			}

			if (_gVPInputSrcCfg[i].Type != SRC_INPUT_NONE)
				vp_kwrap_periodictask(i);

			if(use_input_window_wa)
			{
				if((_gVPInputSrcCfg[i].Type == SRC_INPUT_DTV || _gVPInputSrcCfg[i].Type == SRC_INPUT_MVI) && _gAdaptive_)
				{
					if(	_gVPInSizeFromThread[i].w != prev_hActive[i] || _gVPInSizeFromThread[i].h != prev_vActive[i])
					{
						_gAdaptive_update_win = 0;
						_gVPInWinChg[i] = 0;
						VP_WARN("Source size changed win[%d], %d/%d -> %d/%d", i, prev_hActive[i], prev_vActive[i], _gVPInSizeFromThread[i].w, _gVPInSizeFromThread[i].h);

						// gld4tv W/A code (screen mute problem of web-browser)
						if(_gVPInSizeFromThread[i].w < _gVPInWin[i].w || _gVPInSizeFromThread[i].h < _gVPInWin[i].h)
						{
							de_kwrap_setinputwin(i, &_gVPInSizeFromThread[i]);
						}
					}
					else
					{
						if(_gVPInWinChg[i] == 0 && _gAdaptive_update_win == 1) // apply at seamless mode
						{
							de_kwrap_setinputwin(i, &_gVPInWin[i]);
							_gAdaptive_update_win = 0;
							VP_WARN("update input window for adapdive after %d frames. src size[%d/%d] in win[%d/%d]", UPDATE_INPUT_WIN_COUNTER,\
								_gVPInSizeFromThread[i].w, _gVPInSizeFromThread[i].h, _gVPInWin[i].w, _gVPInWin[i].h);
						}
						else
						{
							if( _gVPInWinChg[i] == (UPDATE_INPUT_WIN_COUNTER - 1) )
							{
								de_kwrap_setinputwin(i, &_gVPInWin[i]);
								VP_WARN("update input window ...");
							}
							_gVPInWinChg[i]--;
						}
					}
				}
				prev_hActive[i] = _gVPInSizeFromThread[i].w;
				prev_vActive[i] = _gVPInSizeFromThread[i].h;
			}
			//DE_ERROR("VP kernel thread running current input type is %d\n",_gVPInputSrcCfg[i].Type);
		}
	} while (0);

	return ret;
}

 /**
 * Get timing info.
 *
 * @param vpSrcId			[IN] UINT32
 * @param pVpTimingInfo		[IN/OUT] kwrap_vp_timing_info_t *
 *
 * @return int
 */
int vp_kwrap_gettiminginfo(UINT32 vpSrcId, kwrap_vp_timing_info_t *pVpTimingInfo)
{
	int ret = RET_OK;

	CHECK_NULL(pVpTimingInfo);
	CHECK_SRC_ID(vpSrcId);

	pVpTimingInfo->hFreq = _gCurVpTiming[vpSrcId].hFreq;
	pVpTimingInfo->vFreq = _gCurVpTiming[vpSrcId].vFreq;
	pVpTimingInfo->hTotal = _gCurVpTiming[vpSrcId].hTotal;
	pVpTimingInfo->vTotal = _gCurVpTiming[vpSrcId].vTotal;
	pVpTimingInfo->hStart = _gCurVpTiming[vpSrcId].hStart;
	pVpTimingInfo->vStart = _gCurVpTiming[vpSrcId].vStart;
	pVpTimingInfo->hActive = _gCurVpTiming[vpSrcId].hActive;
	pVpTimingInfo->vActive = _gCurVpTiming[vpSrcId].vActive;
	pVpTimingInfo->scanType = _gCurVpTiming[vpSrcId].scanType;
	pVpTimingInfo->standard = _gCurVpTiming[vpSrcId].standard;
	pVpTimingInfo->vdLock = _gCurVpTiming[vpSrcId].vdLock;

	pVpTimingInfo->extInfo = _gCurVpTiming[vpSrcId].extInfo;
	pVpTimingInfo->order3D = _gCurVpTiming[vpSrcId].order3D;
	return ret;
}


/**
 * get color  & scaler c sample info of HDMI
 *
 * @param color		[IN/OUT] LX_DE_COLOR_STD_T *
 * @param scaler	[IN/OUT] LX_DE_SCALER_CSAMPLE_T *
 *
 * @return int
 */
static int vp_kwrap_gethdmicolormetry(UINT32 vpSrcId,LX_DE_COLOR_STD_T *color, LX_DE_SCALER_CSAMPLE_T *scaler)
{
	int ret = RET_ERROR;
	LX_HDMI_COLOR_STATUS_T hdmi_colormetry = LX_HDMI_CS_FULL_RGB;
	static UINT32 pre_hdmi_colormetry[LX_DE_WIN_MAX] = {0xff,0xff,0xff,0xff};
	static UINT32 pre_color[LX_DE_WIN_MAX] = {0xff,0xff,0xff,0xff};
	static UINT32 pre_scaler[LX_DE_WIN_MAX] = {0xff,0xff,0xff,0xff};
	UINT8 hdmi_phys_port = de_kwrap_gethdmiport(vpSrcId);
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;

	UINT32	cnt = 0;

#ifdef USE_VP_HDMI_API
	ret = vp_kwrap_hdmi_rx_getcolordomain(hdmi_phys_port, &hdmi_colormetry);
	if(ret != RET_OK) VP_ERROR("vp_kwrap_hdmi_rx_getcolordomain fail");
#else
/*	if(hdmi20_kwrap_rx_getcolordomain((UINT8)hdmi_phys_port, &hdmi_colormetry) < 0)
		VP_ERROR("[VP]hdmi20_kwrap_rx_getcolordomain fail.\n");*/
#endif
	//set default values
	*color = LX_DE_COLOR_RGBEX;
	*scaler = LX_DE_SCALER_444;

	for(cnt=0;cnt < (sizeof(HDMI_COLORMETRY_MAP)/sizeof(kwrap_vp_hdmi_color_map_t));cnt++)
	{
		if(HDMI_COLORMETRY_MAP[cnt].hdmi_colormetry == hdmi_colormetry){
			*color = HDMI_COLORMETRY_MAP[cnt].color;
			*scaler= HDMI_COLORMETRY_MAP[cnt].scaler;
			break;
		}
	}
	// set color metry info for PE default
	cur_inf_param.win_id = LX_PE_WIN_0;
	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);
#endif
	cur_inf_param.info_type = LX_PE_INFO_MODE;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));

	if(hdmi_colormetry>= LX_HDMI_CS_YCBCR420_601 && hdmi_colormetry<=LX_HDMI_CS_YCBCR420_2020_NCL)
	{
		cur_inf_param.mode.is_420= 0x1;
	}
	else
	{
		cur_inf_param.mode.is_420= 0x0;
	}
	/* set default */
	if (pre_inf_param.mode.is_420 != cur_inf_param.mode.is_420)
	{
		if (_gVP_DebugPrintOn)
		{
			VP_DEBUG("[VP][%s,%d][set]is_420:%d\n", __F__, __L__, cur_inf_param.mode.is_420);
		}
		/* set disp info */
#ifdef INCLUDE_KDRV_PE
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, \
			"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);
#endif
	}

	/* add compare, too many prints */
	if (_gVP_DebugPrintOn)
	{
		if (pre_hdmi_colormetry[vpSrcId] != hdmi_colormetry || \
			pre_color[vpSrcId] != *color || pre_scaler[vpSrcId] != *scaler)
		{
				VP_DEBUG("[VP]HDMIColor : colormetry:%d, color,scaler:%d,%d\n",\
					hdmi_colormetry, *color, *scaler);
			pre_hdmi_colormetry[vpSrcId] = hdmi_colormetry;
			pre_color[vpSrcId] = *color;
			pre_scaler[vpSrcId] = *scaler;
		}
	}
	return RET_OK;
}

/**
 * Get HDMI video aspect ratio
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_gethdmiaspectratio(UINT32 vpSrcId,LX_HDMI_ASPECTRATIO_T *hdmi_aspectratio)
{
	int ret = RET_OK;
	UINT8 hdmi_phys_port = de_kwrap_gethdmiport(vpSrcId);
#ifdef USE_VP_HDMI_API
	ret = vp_kwrap_hdmi_rx_getaspectratio(hdmi_phys_port, hdmi_aspectratio);
	if(ret != RET_OK) VP_ERROR("vp_kwrap_hdmi_rx_getaspectratio fail");
#else
	/*if(hdmi20_kwrap_isopen() == RET_ERROR ){
		return RET_ERROR;
	}else {
		if(hdmi20_kwrap_rx_getaspectratio((UINT8)hdmi_phys_port, hdmi_aspectratio) < 0)
			VP_ERROR("[kwrap_de]hdmi20_kwrap_rx_getaspectratio fail.\n");
	}*/
#endif
	return ret;
}


/**
 * Get CVI configuration for VGA
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_vga(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;

	if ( cviInfo->size_offset.hsize > DE_MAX_INPUT_HSIZE  || cviInfo->size_offset.vsize > DE_MAX_INPUT_VSIZE )
	{
		cviInfo->size_offset.hsize = 720;
		cviInfo->size_offset.vsize = 480;
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
		cviInfo->scan = LX_DE_INTERLACED;
	}

	if (cviInfo->scan == LX_DE_INTERLACED)
	{
		cviInfo->sc_c_sample = LX_DE_SCALER_422;	// L8 HW constraint
	}
	else
	{
		cviInfo->sc_c_sample = LX_DE_SCALER_444;
	}

	return ret;
}

/**
 * Get CVI configuration for YPbPr input
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_ypbpr(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;

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

#ifdef SEE_TV
#else
		if (lx_chip_rev() < LX_CHIP_REV(M16, A0))
		{
			if ( ((cviInfo->size_offset.vsize == 480) || (cviInfo->size_offset.vsize == 576)|| (cviInfo->size_offset.vsize == 483)) && cviInfo->scan == LX_DE_INTERLACED )
			{
				cviInfo->sampling = LX_DE_CVI_DOUBLE_SAMPLING;
				cviInfo->size_offset.hsize *= 2;
				cviInfo->size_offset.hoffset *= 2;
			}
		}
#endif
	}

	return ret;
}

/**
 * Get CVI configuration for ATV input
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_atv(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;
	const s0_enum *pColorTbl;
	int i;

	/*Harish:: Why are we setting LX_DE_CVI_HDMI_SYNC_MODE??
			   What does really mean by HDMI sync mode.
	*/
	cviInfo->scan = LX_DE_INTERLACED;
	if ( cviInfo->de_mode == LX_DE_CVI_HDMI_SYNC_MODE )
	{
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
	}

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

	return ret;
}

/**
 * Get CVI configuration for CVBS input
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_cvbs(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;
	const s0_enum *pColorTbl;
	int i;

	cviInfo->scan = LX_DE_INTERLACED;
	if ( cviInfo->de_mode == LX_DE_CVI_HDMI_SYNC_MODE )
	{
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
	}

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

	return ret;
}

/**
 * Get CVI configuration for SCART input
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_scart(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;
	const s0_enum *pColorTbl;
	int i=0;

	LX_AFE_SCART_ID_T scart_id;
	LX_AFE_SCART_AR_T scart_ar = LX_SCART_AR_INVALID;

	cviInfo->scan = LX_DE_INTERLACED;
	if ( vpInputSrc.Attr == 0)			scart_id = LX_SCART_ID_1;
	else								scart_id = LX_SCART_ID_2;

	if ( cviInfo->de_mode == LX_DE_CVI_HDMI_SYNC_MODE )
	{
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
	}

#ifdef INCLUDE_KDRV_AFE
	if ( afe_kwrap_get_scart_ar(scart_id, &scart_ar) < 0 )
		VP_ERROR("[kwrap_vp]KADP_AFE_Get_Scart_AR fail.\n");
#endif

	if ( scart_ar == LX_SCART_AR_16_9)
		cviInfo->aspect = LX_DE_AR_16_9;
	else
		cviInfo->aspect = LX_DE_AR_4_3;

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

	return ret;
}

/**
 * Get CVI configuration for Scart RGB Bypass
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_scart_rgbbypass(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;

	/*Harish::
			Does SCART [RGB] supports HD content?? [Do we need to check DE_MAX_INPUT_SIZE]
	*/
	LX_AFE_SCART_ID_T scart_id;
	LX_AFE_SCART_AR_T scart_ar = LX_SCART_AR_INVALID;

	if ( vpInputSrc.Attr == 0)			scart_id = LX_SCART_ID_1;
	else								scart_id = LX_SCART_ID_2;

	if ( cviInfo->size_offset.hsize > DE_MAX_INPUT_HSIZE  || cviInfo->size_offset.vsize > DE_MAX_INPUT_VSIZE )
	{
		cviInfo->size_offset.hsize = 0;
		cviInfo->size_offset.vsize = 0;
		//cviInfo->size_offset.hsize = STD_601_H_RES;
		//cviInfo->size_offset.vsize = STD_601_V_RES;
		cviInfo->size_offset.hoffset = 0;
		cviInfo->size_offset.voffset = 0;
		cviInfo->scan = LX_DE_INTERLACED;
	}

	if (bufTiming.vFreq > 550)
		cviInfo->cvd_color_std = LX_DE_COLOR_NTSC_M;
	else
		cviInfo->cvd_color_std = LX_DE_COLOR_PAL;

#ifdef INCLUDE_KDRV_AFE
	if ( afe_kwrap_get_scart_ar(scart_id, &scart_ar) < 0 )
		VP_ERROR("[kwrap_de]afe_kwrap_get_scart_ar fail.\n");
#endif

	if ( scart_ar == LX_SCART_AR_16_9)
		cviInfo->aspect = LX_DE_AR_16_9;
	else
		cviInfo->aspect = LX_DE_AR_4_3;

	return ret;
}

/**
 * Convert VP to DE 3D format Type
 *
 * @param vp3DFormatType			[IN] KADP_VP_EXT_INFO_T
 *
 * @return int
 */
static int vp_kwrap_getdefull3dformattype(kwrap_vp_ext_info_t vp3DFormatType)
{
	LX_DE_CVI_3D_FULL_INFO_T de3DFormatType = LX_DE_CVI_NORMAL_FORMAT;

	if (vp3DFormatType== VP_EXT_3D_FRAME_PACKING)
		de3DFormatType = LX_DE_CVI_3D_FRAMEPACK;
	else if (vp3DFormatType == VP_EXT_3D_FIELD_ALTERNATIVE)
		de3DFormatType = LX_DE_CVI_3D_FIELD_ALTERNATIVE;
	else if (vp3DFormatType == VP_EXT_3D_LINE_ALTERNATIVE_FULL)
		de3DFormatType = LX_DE_CVI_3D_ROW_INTERLEAVING;
	else if (vp3DFormatType == VP_EXT_3D_SIDEBYSIDE_FULL)
		de3DFormatType = LX_DE_CVI_3D_SBSFULL;
	else if (vp3DFormatType == VP_EXT_4K_2K)
		de3DFormatType = LX_DE_CVI_4K_2K;

	return de3DFormatType;
}

/**
 * Get CVI configuration for HDMI source
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
static int vp_kwrap_getcvicfg_hdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;

	LX_HDMI_ASPECTRATIO_T hdmi_aspectratio = { 0, };
	LX_DE_COLOR_STD_T color = LX_DE_COLOR_RGB;
	LX_DE_SCALER_CSAMPLE_T scaler = LX_DE_SCALER_444;
	LX_DE_CAPACITY_T capa;
	LX_DE_HDMI444_MODE_T hdmi_444_mode = LX_DE_HDMI444_NONE;

	ret = vp_kwrap_gethdmiaspectratio(vpSrcId, &hdmi_aspectratio);
	if(RET_ERROR == ret)
		return ret;

	if(_gVPInSizeChg[vpSrcId])
	{
		cviInfo->size_offset.hsize = _gVPInSize[vpSrcId].w;
		cviInfo->size_offset.vsize = _gVPInSize[vpSrcId].h;
		_gVPInSizeChg[vpSrcId] = 0;
		VP_DEBUG("[%s,%d] source size comes from platform.  h/v [%d/%d]\n",\
			__F__,__L__, _gVPInSize[vpSrcId].w, _gVPInSize[vpSrcId].h);
	}
	else
	{
		cviInfo->size_offset.hsize = bufTiming.hActive;
		cviInfo->size_offset.vsize = bufTiming.vActive;
		VP_DEBUG("[%s,%d] source size comes from HDMI module.  h/v [%d/%d]\n",\
			__F__,__L__, bufTiming.hActive, bufTiming.vActive);
	}

	cviInfo->size_offset.hoffset = 0;	//hdmi_time_info.hStart;
	cviInfo->size_offset.voffset = 0;	//hdmi_time_info.vStart;
	cviInfo->de_mode = (bufTiming.isPVOMode) ? LX_DE_CVI_HDMI_SYNC_MODE_PVO : LX_DE_CVI_HDMI_SYNC_MODE;

	if (cviInfo->sampling == LX_DE_CVI_DOUBLE_SAMPLING)
	{
		 cviInfo->size_offset.hsize = bufTiming.hActive *2;
	}
	else if (cviInfo->sampling == LX_DE_CVI_QUAD_SAMPLING)
	{
		cviInfo->size_offset.hsize = bufTiming.hActive *4;
	}

	/* Get VP to CVI 3D format conversion */
	cviInfo->trid_full_format = vp_kwrap_getdefull3dformattype(bufTiming.extInfo);

	ret = de_kwrap_getcapacity(&capa);
	if(capa.max_in_size.w == 1920 && capa.max_in_size.h == 2160) // in case of H13
	{
		if (cviInfo->trid_full_format == LX_DE_CVI_4K_2K)
			cviInfo->size_offset.hsize = cviInfo->size_offset.hsize >> 1;
	}

	vp_kwrap_gethdmicolormetry(vpSrcId, &color, &scaler);

	cviInfo->color = color;
	cviInfo->sc_c_sample = scaler;

	if (hdmi_aspectratio.eAspectRatio == LX_HDMI_AVI_PICTURE_ARC_16_9)
		cviInfo->aspect = LX_DE_AR_16_9;
	else
		cviInfo->aspect = LX_DE_AR_4_3;

	/* 1. sc_c_sample: for hdmi 444 mode of user */
	de_kwrap_gethdmi444mode(&hdmi_444_mode);

	if(cviInfo->sc_c_sample == LX_DE_SCALER_420)
		cviInfo->c_sample = LX_DE_CVI_420;

	if (hdmi_444_mode == LX_DE_HDMI444_ON){
		cviInfo->sc_c_sample = LX_DE_SCALER_444;
	}
	else if (hdmi_444_mode == LX_DE_HDMI444_OFF)
		cviInfo->sc_c_sample = LX_DE_SCALER_422;

	VP_PRINT("[%s,%d] sc_c_sample:[%d], by hdmi444md:[%d]\n",__F__,__L__, cviInfo->sc_c_sample,hdmi_444_mode);

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

	return ret;
}

/**
 * Get CVI configuration for all sources
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 * @param cviInfo			[IN/OUT] LX_DE_CVI_SRC_TYPE_T *
 *
 * @return int
 */
int vp_kwrap_getcvicfg(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo )
{
	int ret = RET_OK;

	CHECK_NULL(cviInfo);
	CHECK_SRC_ID(vpSrcId);

	if (vpInputSrc.Type >= SRC_INPUT_DTV)
	{
		memset((void *)cviInfo , 0 , sizeof(LX_DE_CVI_SRC_TYPE_T));
		VP_ERROR("[VP %d] Wrong Source Type = %d  \n", __L__, vpInputSrc.Type);
		ret = RET_ERROR;
		return ret;
	}

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] %s(%d) srcID[%d]  srcType[%d]\n", __F__, __L__, vpSrcId, vpInputSrc.Type );

	//(vpSrcId < 1) ? (cviInfo->cvi_channel = LX_DE_CVI_CH_A) : (cviInfo->cvi_channel = LX_DE_CVI_CH_B);

	//Harish:: Didn't get this logic
	//how CVI channel is connected with window. I think TV can support upto
	//2 windows as of now whose values can 0 or 1 so in that case CVI channel will
	//be either LX_DE_CVI_CH_A or LX_DE_CVI_CH_B, Main Path is via CVI channel A
	//and sub-path is via CVI channel B
	cviInfo->cvi_channel = (LX_DE_CVI_CHANNEL_T)vpSrcId;

	//common configuration
	cviInfo->size_offset.hsize = bufTiming.hActive;
	cviInfo->size_offset.vsize = bufTiming.vActive;
	cviInfo->size_offset.hoffset = bufTiming.hStart;
	cviInfo->size_offset.voffset = bufTiming.vStart;
	cviInfo->scan = bufTiming.scanType;

	switch (vpInputSrc.Type)
	{
		case SRC_INPUT_VGA:
			{
				ret = vp_kwrap_getcvicfg_vga(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_vp]SetCviSrcType for VGA.\n");
			} break;

		case SRC_INPUT_YPBPR:
			{
				ret = vp_kwrap_getcvicfg_ypbpr(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_vp]SetCviSrcType for YPBPR.\n");
			} break;

		case SRC_INPUT_ATV:
			{
				ret = vp_kwrap_getcvicfg_atv(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_vp]SetCviSrcType for ATV.\n");
			} break;

		case SRC_INPUT_CVBS:
			{
				ret = vp_kwrap_getcvicfg_cvbs(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_vp]SetCviSrcType for CVBS.\n");
			} break;

		case SRC_INPUT_SCART:
			{
				ret = vp_kwrap_getcvicfg_scart(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_vp]SetCviSrcType for SCART.\n");
			} break;

		case SRC_INPUT_SCART_RGB_BYPASS:
			{
				ret = vp_kwrap_getcvicfg_scart_rgbbypass(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_vp]SetCviSrcType for SCART RGB Bypass.\n");

			} break;

		case SRC_INPUT_HDMI:
			{
				ret = vp_kwrap_getcvicfg_hdmi(vpSrcId,vpInputSrc,bufTiming,cviInfo);
				VP_PRINT("[kwrap_de]SetCviSrcType for HDMI.\n");

			} break;
		default:
			{
				memset((void *)cviInfo , 0 , sizeof(LX_DE_CVI_SRC_TYPE_T));
				VP_ERROR("[VP %d] Wrong Source Type = %d  \n", __L__, vpInputSrc.Type);
				ret = RET_ERROR;
			}break;
	}

	if (1)//_gVP_DebugPrintOn)
	{
		DE_NOTI("[VP]GetCVICfg. channel= %d, trid_full_format = %d\n"\
			"          hsize %d, vsize %d, hoffset %d, voffset %d, scan %d, color %d aspect %d\n"\
			"          c_sample %d, sc_c_sample %d, sampling %d, cvi_input_src:%d, cvd_color_std:%d, pixRpt:%d, de_mode:%d\n",\
			cviInfo->cvi_channel,cviInfo->trid_full_format,\
			cviInfo->size_offset.hsize,cviInfo->size_offset.vsize,cviInfo->size_offset.hoffset,cviInfo->size_offset.voffset,\
			cviInfo->scan,cviInfo->color,cviInfo->aspect,cviInfo->c_sample,cviInfo->sc_c_sample,cviInfo->sampling,\
			cviInfo->cvi_input_src,cviInfo->cvd_color_std, bufTiming.pixelRepeat, cviInfo->de_mode);
		if(vpInputSrc.Type==SRC_INPUT_HDMI)
		{
			VP_NOTI("HDMI2.1 info : FreeSync[%s],GSync[%s],Vrr[%s],Fva[%s],MConst[%d]",\
				cviInfo->cvi_game_info.isFreeSyncMode?"ON":"OFF",\
				cviInfo->cvi_game_info.isGSyncMode?"ON":"OFF",\
				cviInfo->cvi_game_info.isVrrMode?"ON":"OFF",\
				cviInfo->cvi_game_info.isFvaMode?"ON":"OFF",\
				cviInfo->cvi_game_info.isMConst);
		}
	}

	return ret;
}

/**
 * set cvi source attribute type to DE.
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param cviInfo			[IN] LX_DE_CVI_SRC_TYPE_T
 *
 * @return int
 */
int vp_kwrap_setcvicfg(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, LX_DE_CVI_SRC_TYPE_T cviInfo )
{
	int ret = RET_OK;
	//LX_DE_CVI_SAMPLING_MODE_T cvi_fir_mode;
	//kwrap_vp_in_csc_info_t inCscInfo;
	UINT8 hdmi_phys_port = de_kwrap_gethdmiport(vpSrcId);

	CHECK_SRC_ID(vpSrcId);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP]SetCVICfg. src Id:%d, type:%d,port:%d,attr:%d\n",vpSrcId,vpInputSrc.Type,vpInputSrc.Port,vpInputSrc.Attr);

	if(lx_chip_rev() >= LX_CHIP_REV(H15, A0) && lx_chip_rev() < LX_CHIP_REV(M16, A0))/*H15 only*/
	{
		if(!_gVPQuadWin && cviInfo.cvi_channel == LX_DE_CVI_CH_B)
		{
			cviInfo.cvi_channel = LX_DE_CVI_CH_C;
			if (_gVP_DebugPrintOn)
				VP_DEBUG("[VP] %s(%d) force to use CVI ch_C for 2nd path(%d)\n", __F__, __L__, cviInfo.cvi_channel);
		}
	}

	do {
		if (vpInputSrc.Type >= SRC_INPUT_DTV)
		{
			if (_gVP_DebugPrintOn)
				VP_DEBUG("[VP] %s(%d) Wrong Source Type = %d  \n", __F__, __L__, vpInputSrc.Type);
			ret = RET_ERROR;
			break;
		}

		// for 1 Pixel color loss of CbCr data
		if ( cviInfo.sc_c_sample == LX_DE_SCALER_422 )
		{
			if ( de_kwrap_setcvicsamplemode(vpSrcId, TRUE) < 0 )
				VP_ERROR("[kwrap_vp] de_kwrap_setcvicsamplemode fail.\n");
		}
		else
		{
			if ( de_kwrap_setcvicsamplemode(vpSrcId, FALSE) < 0 )
				VP_ERROR("[kwrap_vp] de_kwrap_setcvicsamplemode fail.\n");
		}

		//cvi_fir_mode = cviInfo.sampling;

		//if ( KADP_DE_SetCviFIR(vpSrcId, cvi_fir_mode, cviInfo.cvi_input_src) < 0 )
			//VP_ERROR("[kwrap_vp]KADP_DE_SetCviFIR fail.\n");

		if(vpInputSrc.Type == SRC_INPUT_HDMI)
			de_kwrap_sethdmiport(vpSrcId, hdmi_phys_port);

		de_kwrap_setcvisrc(&cviInfo);

		/* set input csc */
		if (_gCurInfoChg[vpSrcId].timingInfoChg || _gCurInfoChg[vpSrcId].hdmiDomainChg){
			//inCscInfo.cStd = cviInfo.color;
			//inCscInfo.cvdStd = cviInfo.cvd_color_std;
			ret = vp_kwrap_setinputcsc((UINT32)cviInfo.cvi_channel,&vpInputSrc,&cviInfo);
			VP_CHECK_CODE( ret != RET_OK, ret = RET_ERROR, "[VP %d] vp_kwrap_setinputcsc( ) function return error \n", __L__);
		}

		_gVP_PicInfo.cvd_col_std = cviInfo.cvd_color_std;

		#ifdef PE_EXTEND_WINID
		_gVP_PicInfo.cvi_col_std[vpSrcId] = cviInfo.color;
		#else
		if (vpSrcId < 1)
			_gVP_PicInfo.cvi_col_std[LX_DE_WIN_0] = cviInfo.color;
		else
			_gVP_PicInfo.cvi_col_std[LX_DE_WIN_1] = cviInfo.color;
		#endif

//		ret = KADP_VP_SetInputWin(vpSrcId, _gVPInWin[vpSrcId]);  // 20160511   remove (video mute after 50Hz->60Hz of ATV)
	} while (0);

	return ret;

}

/**
 * Check if timinig infor is changed
 *
 * @param vpSrcId			[IN] UINT32
 * @param bufTiming			[IN] kwrap_vp_timing_info_t
 *
 * @return int
 */
static BOOLEAN vp_kwrap_checktiminginfo(UINT32 vpSrcId, kwrap_vp_timing_info_t bufTiming)
{
	CHECK_SRC_ID(vpSrcId);

	if(_gVPInSizeChg[vpSrcId])	// trigger for platform's source size
	{
		bufTiming.hActive = _gVPInSize[vpSrcId].w;
		bufTiming.vActive = _gVPInSize[vpSrcId].h;
	}

	if (_gVP_DebugPrintOn)
	{
		if (_gCurVpTiming[vpSrcId].hFreq		!= bufTiming.hFreq)
			VP_DEBUG("HFreq[vpSrcId:%4d]    [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].hFreq   , bufTiming.hFreq );
		if (_gCurVpTiming[vpSrcId].vFreq		!= bufTiming.vFreq)
			VP_DEBUG("VFreq[vpSrcId:%4d]    [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].vFreq   , bufTiming.vFreq );
		if (_gCurVpTiming[vpSrcId].hTotal		!= bufTiming.hTotal)
			VP_DEBUG("HTotal[vpSrcId:%4d]   [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].hTotal  , bufTiming.hTotal );
		if (_gCurVpTiming[vpSrcId].vTotal		!= bufTiming.vTotal)
			VP_DEBUG("VTotal[vpSrcId:%4d]   [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].vTotal  , bufTiming.vTotal );
		if (_gCurVpTiming[vpSrcId].hStart		!= bufTiming.hStart)
			VP_DEBUG("hStart[vpSrcId:%4d]   [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].hStart  , bufTiming.hStart );
		if (_gCurVpTiming[vpSrcId].vStart		!= bufTiming.vStart)
			VP_DEBUG("vStart[vpSrcId:%4d]   [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].vStart  , bufTiming.vStart );
		if (_gCurVpTiming[vpSrcId].hActive	!= bufTiming.hActive)
			VP_DEBUG("hActive[vpSrcId:%4d]   [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].hActive  , bufTiming.hActive );
		if (_gCurVpTiming[vpSrcId].vActive	!= bufTiming.vActive)
			VP_DEBUG("vActive[vpSrcId:%4d]   [%4d:%4d]  \n", vpSrcId, _gCurVpTiming[vpSrcId].vActive  , bufTiming.vActive );
		if (_gCurVpTiming[vpSrcId].scanType	!= bufTiming.scanType)
			VP_DEBUG("ScanType[vpSrcId:%4d] [%s:%s]  \n", vpSrcId, _gCurVpTiming[vpSrcId].scanType?"P":"I", bufTiming.scanType?"P":"I" );
		if (_gCurVpTiming[vpSrcId].standard	!= bufTiming.standard)
			VP_PRINT("standard[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].standard    , bufTiming.standard );
		if (_gCurVpTiming[vpSrcId].vdLock	!= bufTiming.vdLock)
			VP_DEBUG("vdLock[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].vdLock    , bufTiming.vdLock );
		if (_gCurVpTiming[vpSrcId].extInfo		!= bufTiming.extInfo)
			VP_DEBUG("extInfo[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].extInfo    , bufTiming.extInfo);
		if (_gCurVpTiming[vpSrcId].order3D	!= bufTiming.order3D)
			VP_DEBUG("video_LR_order[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].order3D    , bufTiming.order3D);
		if (_gCurVpTiming[vpSrcId].isDolbyHDR	!= bufTiming.isDolbyHDR)
			VP_DEBUG("isDolbyHDR[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].isDolbyHDR    , bufTiming.isDolbyHDR);
		if (_gCurVpTiming[vpSrcId].isFreeSyncMode	!= bufTiming.isFreeSyncMode)
			VP_DEBUG("isFreeSyncMode[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].isFreeSyncMode    , bufTiming.isFreeSyncMode);
		if (_gCurVpTiming[vpSrcId].isGSyncMode	!= bufTiming.isGSyncMode)
			VP_DEBUG("isGSyncMode[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].isGSyncMode    , bufTiming.isGSyncMode);
		if (_gCurVpTiming[vpSrcId].isVrrMode	!= bufTiming.isVrrMode)
			VP_DEBUG("isVrrMode[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].isVrrMode    , bufTiming.isVrrMode);
		if (_gCurVpTiming[vpSrcId].isFvaMode	!= bufTiming.isFvaMode)
			VP_DEBUG("isFvaMode[vpSrcId:%4d] [%4d:%4d]  \n\n", vpSrcId, _gCurVpTiming[vpSrcId].isFvaMode    , bufTiming.isFvaMode);
	}

	/**************************************************************
	   2. Check what is changed and following is when current signal is changed.
	 **************************************************************/
	if (	(_gCurVpTiming[vpSrcId].hFreq	!= bufTiming.hFreq)	    || \
		(_gCurVpTiming[vpSrcId].vFreq	!= bufTiming.vFreq)         || \
		(_gCurVpTiming[vpSrcId].hTotal	!= bufTiming.hTotal)        || \
		(_gCurVpTiming[vpSrcId].vTotal	!= bufTiming.vTotal)        || \
		(_gCurVpTiming[vpSrcId].hStart	!= bufTiming.hStart)        || \
		(_gCurVpTiming[vpSrcId].vStart	!= bufTiming.vStart)        || \
		(_gCurVpTiming[vpSrcId].hActive	!= bufTiming.hActive)       || \
		(_gCurVpTiming[vpSrcId].vActive	!= bufTiming.vActive)       || \
		(_gCurVpTiming[vpSrcId].scanType != bufTiming.scanType)	    || \
		(_gCurVpTiming[vpSrcId].standard != bufTiming.standard)     || \
		(_gCurVpTiming[vpSrcId].vdLock	!= bufTiming.vdLock)        || \
		(_gCurVpTiming[vpSrcId].extInfo	!= bufTiming.extInfo)       || \
		(_gCurVpTiming[vpSrcId].order3D	!= bufTiming.order3D)       || \
		(_gCurVpTiming[vpSrcId].isDolbyHDR != bufTiming.isDolbyHDR) || \
		(_gCurVpTiming[vpSrcId].isFreeSyncMode != bufTiming.isFreeSyncMode) || \
		(_gCurVpTiming[vpSrcId].isGSyncMode != bufTiming.isGSyncMode)       || \
		(_gCurVpTiming[vpSrcId].isVrrMode != bufTiming.isVrrMode)           || \
		(_gCurVpTiming[vpSrcId].isFvaMode != bufTiming.isFvaMode))
	{
		if(_gVPInSizeChg[vpSrcId])	VP_DEBUG("[%s,%d] trigger by platform's source size configure\n",__F__,__L__);

		return TRUE;
	}
	else
		return FALSE;
}

/**
 * Read timing info for different sources
 *
 * @param vpSrcId			[IN] UINT32
 * @param vpInputSrc		[IN] kwrap_vp_src_info_t
 * @param bufTiming			[IN/OUT] kwrap_vp_timing_info_t
 *
 * @return int
 */
int vp_kwrap_readtiminginfo(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming)
{
	int ret = RET_OK;

	CHECK_NULL(bufTiming);
	CHECK_SRC_ID(vpSrcId);

	switch (vpInputSrc.Type)
	{
		case SRC_INPUT_VGA:
		case SRC_INPUT_YPBPR:
		case SRC_INPUT_SCART_RGB_BYPASS:
			{
				ret = vp_kwrap_readtiminginfo_frm_adc(vpInputSrc, bufTiming);
			} break;

		case SRC_INPUT_ATV:
		case SRC_INPUT_CVBS:
		case SRC_INPUT_SCART:
			{
				ret = vp_kwrap_readtiminginfo_frm_cvd(vpInputSrc, bufTiming);
			} break;

		case SRC_INPUT_HDMI:
			{
				ret = vp_kwrap_readtiminginfo_frm_hdmi(vpSrcId,vpInputSrc, bufTiming);
			} break;

		case SRC_INPUT_DTV:
		case SRC_INPUT_JPG:
		case SRC_INPUT_MVI:
			{
				ret = vp_kwrap_readtiminginfo_frm_vdec(vpInputSrc, bufTiming);
			} break;

		default:
			break;
	}

	return ret;
}

/**
* Get the changed timing information,HDMI color sampling and colorimetry info
*
* @param vpSrcId			[IN] UINT32
* @param vpInputSrc			[IN] kwrap_vp_src_info_t
* @param bufTiming         	[IN/OUT] kwrap_vp_timing_info_t *
* @param prevHdmiInfo		[IN/OUT] KADP_VP_CHG_INFO_T *
* @return kwrap_vp_info_chg_flag_t [changed information types]
*/
static kwrap_vp_info_chg_flag_t vp_kwrap_getchangedinputinfo(UINT32 vpSrcId,kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming,kwrap_vp_chg_info_t *prevHdmiInfo)
{
	kwrap_vp_info_chg_flag_t updatedChgFlag = {FALSE,FALSE,FALSE,FALSE};
	LX_DE_HDMI444_MODE_T 	currHdmi_444_Mode = LX_DE_HDMI444_NONE;
	LX_DE_COLOR_STD_T 		hdmiColor = LX_DE_COLOR_RGB;
	LX_DE_SCALER_CSAMPLE_T 	hdmiScaler = LX_DE_SCALER_444;
	UINT8					hdmi_sampling	= LX_DE_CVI_NORMAL_SAMPLING;
	BOOLEAN					bCurPdMode;
	static BOOLEAN			bPrePdMode = FALSE;

	if(vp_kwrap_readtiminginfo(vpSrcId, vpInputSrc, bufTiming) != RET_OK){
		return updatedChgFlag;
	}

#if 1
	_gCurInfoChg[vpSrcId].timingInfoChg = FALSE;
	_gCurInfoChg[vpSrcId].hdmi444modChg = FALSE;
	_gCurInfoChg[vpSrcId].hdmiDomainChg = FALSE;
	_gCurInfoChg[vpSrcId].dispFrRateChg = FALSE;
#endif /* #if 0 */

#if 0
	if ((bufTiming->hActive == 0) && (bufTiming->vActive == 0))
		return updatedChgFlag;
#endif /* #if 0 */

	//**************************************************************
	// 2. Check what is  changed and following is when current signal is changed.
	//**************************************************************

	if(vpInputSrc.Type == SRC_INPUT_HDMI){

		if (de_kwrap_gethdmisamplemode(bufTiming->hActive, bufTiming->vActive, bufTiming->scanType, &hdmi_sampling ) < 0 )
			VP_ERROR("[kwrap_de]de_kwrap_gethdmisamplemode fail.\n");

		if (hdmi_sampling > LX_DE_CVI_NORMAL_SAMPLING)
		{
			bufTiming->hTotal	= bufTiming->hTotal	/ (hdmi_sampling *2);
			bufTiming->hActive 	= bufTiming->hActive / (hdmi_sampling *2);
		}

		prevHdmiInfo->hdmi_sampling = hdmi_sampling;

		de_kwrap_gethdmi444mode(&currHdmi_444_Mode);

		if (prevHdmiInfo->hdmi_444_Mode != currHdmi_444_Mode)
		{
			updatedChgFlag.hdmi444modChg = TRUE;
			prevHdmiInfo->hdmi_444_Mode = currHdmi_444_Mode;
#if 1
			_gCurInfoChg[vpSrcId].hdmi444modChg = TRUE;
#endif /* #if 0 */
			VP_NOTI("[VP]  Chang HDMI CFG  444Mode [%d] (0:None 1:OFF 2:ON)\n", currHdmi_444_Mode);
		}

		if ( bufTiming->hActive >  0 && bufTiming->vActive > 0)
		{
			vp_kwrap_gethdmicolormetry(vpSrcId, &hdmiColor, &hdmiScaler);

			if (prevHdmiInfo->color_std[vpSrcId] != hdmiColor || prevHdmiInfo->hdmiScaler[vpSrcId] != hdmiScaler)
			{
				updatedChgFlag.hdmiDomainChg = TRUE;
#if 1
				_gCurInfoChg[vpSrcId].hdmiDomainChg = TRUE;
#endif /* #if 0 */

				VP_NOTI("[VP]  Change HDMI ColorMetry  prev_color_std[%d], hdmiColor[%d], prev_hdmiScaler[%d], hdmiScaler[%d]\n", \
					prevHdmiInfo->color_std[vpSrcId], hdmiColor, prevHdmiInfo->hdmiScaler[vpSrcId], hdmiScaler);
			}
			prevHdmiInfo->hdmiScaler[vpSrcId] = hdmiScaler;
		}
	}

	if ( TRUE == vp_kwrap_checktiminginfo(vpSrcId, *bufTiming))
	{
		updatedChgFlag.timingInfoChg = TRUE;
#if 1
		_gCurInfoChg[vpSrcId].timingInfoChg = TRUE;
#endif /* #if 0 */
	}

	if (vpSrcId == LX_DE_WIN_0)	//main only
	{
		bCurPdMode = vp_kwrap_checkpulldownmode();
		if (bPrePdMode != bCurPdMode)
		{
			updatedChgFlag.dispFrRateChg = TRUE;
#if 1
			_gCurInfoChg[vpSrcId].dispFrRateChg = TRUE;
#endif /* #if 0 */
			VP_NOTI("[VP]  Change PdMode %d -> %d\n", bPrePdMode? 1:0, bCurPdMode? 1:0);
			bPrePdMode = bCurPdMode;
		}
	}

	return updatedChgFlag;
}

/**
* Update frame rate based on timing information
*
* @param vpSrcId			[IN] UINT32
* @param vpInputSrc			[IN] kwrap_vp_src_info_t
* @param bufTiming         	[IN] kwrap_vp_timing_info_t
* @param frameRateInfo		[IN/OUT] KADP_VP_FR_INFO_T *
* @return int
*/
static int vp_kwrap_updateframerate(UINT32 vpSrcId,kwrap_vp_src_info_t vpInputSrc,kwrap_vp_timing_info_t bufTiming,kwrap_vp_fr_info_t *frameRateInfo)
{
	int ret = RET_OK;
	UINT16 preFrameRate;
	LX_DE_DIS_FMT_T dis_fmt = {LX_PANEL_TYPE_1920, 0, 0, 0, 0, 0, LX_PANEL_DEV_LCD};

	///< start Check Frame rate >///
	if (vpSrcId == 0)
	{
		//Harish:: We should have checked earlier vFreq then only we reach here so not required to check this
		if (bufTiming.vFreq == 0)
		{
			if (_gVP_DebugPrintOn)
				VP_DEBUG("[VP] %s(%d)  Frame Rate Set Skip vpSrcId[%d]  vFreq[%d]\n", __F__, __L__, vpSrcId, bufTiming.vFreq);
			return RET_ERROR;
		}
		else
		{
			de_kwrap_getoutfrrate(&(frameRateInfo->isForceFreeRun), &preFrameRate);

			ret = vp_kwrap_checkfrrate(vpInputSrc, bufTiming, &(frameRateInfo->frameRate));

			if (_gCurTVOperState == LX_DE_OPER_3D)
			{
				//Harish: Instead use global src info variable for main window
				if (vpInputSrc.Type == SRC_INPUT_MVI)
				{
					//  seemless for 3D operation of 24Hz or 48Hz Netflex source  at mvi input source
					if ( (preFrameRate == 48) && ( u16CHK_RANGE(bufTiming.vFreq,480,5)  || u16CHK_RANGE(bufTiming.vFreq,240,5) ) )
					{
						if (_gVP_DebugPrintOn)
							VP_DEBUG("[VP] skip 3D set pre Frame Rate[%d] source frame rate [%d]\n", preFrameRate, bufTiming.vFreq);

						return RET_ERROR;
					}
				}
				else
				{
					VP_NOTI("[VP]  and changing timinginfo in 3D ON operation \n");
					//if (_gVP_DebugPrintOn)
						//VP_DEBUG("[VP] set frame rate in 3D operation and changing timinginfo\n");

					//ret = vp_kwrap_set3dfrrate(_gVP3DMode);
				}
			}
			else if (_gCurTVOperState == LX_DE_OPER_UD)
			{
				de_kwrap_getdisfmt(&dis_fmt);
				if (dis_fmt.panel_type == LX_PANEL_TYPE_3840)
				{
					if (u16CHK_RANGE(bufTiming.vFreq,240,5))
						frameRateInfo->frameRate = 24;
					else if (u16CHK_RANGE(bufTiming.vFreq,250,5))
						frameRateInfo->frameRate = 25	;
					else if (u16CHK_RANGE(bufTiming.vFreq,300,5))
						frameRateInfo->frameRate = 30;

					if (_gVP_DebugPrintOn)
						VP_DEBUG("[VP] set frame rate[%d Hz] at the PANEL 3840 & UD ON\n", frameRateInfo->frameRate);
				}
			}
		}
	}
	else /* No need to set frame rate in-case of sub-window */
		return RET_ERROR;

	return ret;
}

/**
* Get color standard based on source type
*
* @param vpInputSrc			[IN] kwrap_vp_src_info_t
* @param bufTiming         	[IN] kwrap_vp_timing_info_t
* @param cviInfo			[IN] LX_DE_CVI_SRC_TYPE_T
* @param color_std			[IN/OUT] LX_DE_COLOR_STD_T *
* @return int
*/
static int vp_kwrap_getcolorstd(kwrap_vp_src_info_t vpInputSrc,kwrap_vp_timing_info_t bufTiming,LX_DE_CVI_SRC_TYPE_T cviInfo,LX_DE_COLOR_STD_T *color_std)
{
	int ret = RET_OK;

	switch (vpInputSrc.Type)
	{
		case SRC_INPUT_VGA:
		case SRC_INPUT_YPBPR:
		case SRC_INPUT_ATV:
		case SRC_INPUT_CVBS:
		case SRC_INPUT_SCART:
		case SRC_INPUT_SCART_RGB_BYPASS:
		case SRC_INPUT_HDMI:
			{
				*color_std = cviInfo.color;
			} break;

		case SRC_INPUT_JPG:
			/** 20140119, sj.youm, LX_DE_COLOR_709 to LX_DE_COLOR_601
			*	- for color sacturation issue on rgb input such as png,bmp
			*	- because of csc mismatching between decoder and pe(601 limit vs. 709 exp)
			*	- to avoid this, changed 709(exp) to 601(exp) */

			*color_std = LX_DE_COLOR_601;
			break;

		case SRC_INPUT_DTV:
			{
				/** 20140930, sj.youm, instead of KADP_DE_GetMviColorimetry()
				*	- if h>=1024, color 709, else color 601 */
				if (bufTiming.hActive >= DE_H1024_IS_HD)
				{
					*color_std = LX_DE_COLOR_709;
				}
				else
				{
					*color_std = LX_DE_COLOR_601;
				}
			} break;

		case SRC_INPUT_MVI:
			/** 20140930, sj.youm, instead of KADP_DE_GetMviColorimetry()
			*	- fix color 601 */

			*color_std = LX_DE_COLOR_601;
			break;

		case  SRC_INPUT_NONE:
		case SRC_INPUT_MAX:
		default:
			break;
	}

	return ret;
}

/**
* Run periodically to check change in timing and other information of input sources
*
* @param vpSrcId			[IN] UINT32
* @return int
*/
static int vp_kwrap_periodictask(UINT32 vpSrcId)
{
	static	kwrap_vp_chg_info_t prev_HdmiConfig = \
		{ {LX_DE_COLOR_NOT_DEFINED, LX_DE_COLOR_NOT_DEFINED, LX_DE_COLOR_NOT_DEFINED, LX_DE_COLOR_NOT_DEFINED},\
		LX_DE_HDMI444_NONE, {0xFF, 0xFF, 0xFF, 0xFF},0};
	LX_DE_COLOR_STD_T 			color_std = LX_DE_COLOR_NOT_DEFINED;
	kwrap_vp_src_info_t			vpInputSrc = { SRC_INPUT_NONE, 0, 0, 0};
	kwrap_vp_timing_info_t 		bufTiming = {0, };
	LX_DE_CVI_SRC_TYPE_T  		cviInfo = {0, }, cviInfo_null = {0, };
	kwrap_vp_fr_info_t			frameRateInfo = {FALSE,0};
	kwrap_vp_info_chg_flag_t	infoChgFlag = {FALSE,FALSE,FALSE,FALSE};
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	UINT64 time;
#else
	struct timespec time;
#endif
	int ret = RET_OK;

#ifdef VP_KWRAP_ADD_CHK_PIC_INFO
	vp_kwrap_checkpicinfo(vpSrcId);
#endif

	memset(&bufTiming,0x0,sizeof(kwrap_vp_timing_info_t));	//init bufTiming
	memcpy(&vpInputSrc, &_gVPInputSrcCfg[vpSrcId], sizeof(kwrap_vp_src_info_t));

	//Copy default CVI configuration
	memcpy(&cviInfo,&cvi_common_config[vpInputSrc.Type],sizeof(LX_DE_CVI_SRC_TYPE_T));

	//STEP2: else if change in timing info configure all
	infoChgFlag = vp_kwrap_getchangedinputinfo(vpSrcId,vpInputSrc, &bufTiming,&prev_HdmiConfig);
	//This is little dirty need to find better way
	if(vpInputSrc.Type == SRC_INPUT_HDMI)
		cviInfo.sampling = prev_HdmiConfig.hdmi_sampling;

	if (lx_chip_rev() >= LX_CHIP_REV(M16P, A0))
	{
		#ifdef V4L2_VSC_BBD_USE_PRIV
		#else
		if (vpSrcId==0)			vp_kwrap_checkactivevideowindowmain(vpSrcId, &bufTiming);
		else if (vpSrcId==1)	vp_kwrap_checkactivevideowindowsub(vpSrcId, &bufTiming);
		#endif

		vp_kwrap_checkmuteoff(vpSrcId, &bufTiming);
	}

	if(use_input_window_wa)
	{
		if(_gVPNoFirstFrame == 1) // second update of input window
		{
			if(_gVPInWin[vpSrcId].w > _gVPInSizeFromThread[vpSrcId].w)
			{
				_gVPInWin[vpSrcId].w = _gVPInSizeFromThread[vpSrcId].w;
			}
			if(_gVPInWin[vpSrcId].h > _gVPInSizeFromThread[vpSrcId].h)
			{
				_gVPInWin[vpSrcId].h = _gVPInSizeFromThread[vpSrcId].h;
			}
			de_kwrap_setinputwin(vpSrcId, &_gVPInWin[vpSrcId]);
			_gVPNoFirstFrame--;
			VP_NOTI("@@condition of ARC setting -> update input window. count[%d]@@\n", _gVPNoFirstFrame);
		}
	}
	//based on the infoChgFlag configure effected blocks [CVI/CVE/DENC/PostCSC/Pic format etc]
	//STEP3: else if change in HDMI colorimetry/sampling mode then configure CVI/PostCsc
	//ALL:
	if(!infoChgFlag.hdmi444modChg && !infoChgFlag.timingInfoChg && \
		!infoChgFlag.hdmiDomainChg && !infoChgFlag.dispFrRateChg)
		goto func_exit;

/* 20180330, remove for HDMI2.1 VRR game mode
	if ((bufTiming.hActive == 0) && (bufTiming.vActive == 0))
		goto func_exit;
*/
	/*  store source size & set to firmware */
	if(use_input_window_wa)
	{ // should be removed for gld4tv O18/M16++
		_gVPInSizeFromThread[vpSrcId].x = 0;
		_gVPInSizeFromThread[vpSrcId].y = 0;
		_gVPInSizeFromThread[vpSrcId].w = bufTiming.hActive;
		_gVPInSizeFromThread[vpSrcId].h = bufTiming.vActive;
		if(infoChgFlag.timingInfoChg)
		{
			static UINT32 prev_w=0, prev_h=0;
			ret = de_kwrap_setsourcesizewin(vpSrcId, &_gVPInSizeFromThread[vpSrcId], &_gVPInWin[vpSrcId]);
			if(_gVPNoFirstFrame > 0) // first update of input window
			{
				if(_gVPInWin[vpSrcId].w > _gVPInSizeFromThread[vpSrcId].w)
				{
					_gVPInWin[vpSrcId].w = _gVPInSizeFromThread[vpSrcId].w;
				}
				if(_gVPInWin[vpSrcId].h > _gVPInSizeFromThread[vpSrcId].h)
				{
					_gVPInWin[vpSrcId].h = _gVPInSizeFromThread[vpSrcId].h;
				}
				de_kwrap_setinputwin(vpSrcId, &_gVPInWin[vpSrcId]);
				_gVPNoFirstFrame--;
				VP_NOTI("condition of ARC setting -> update input window. count[%d]\n", _gVPNoFirstFrame);
			}
			if(prev_w != bufTiming.hActive || prev_h != bufTiming.vActive)//WOSLQEVENT-117134  (Power-off problem)
			{
				VP_NOTI("### Source size changed...flag[%d]  %d/%d",infoChgFlag.timingInfoChg, bufTiming.hActive, bufTiming.vActive);
			}
			prev_w = bufTiming.hActive;
			prev_h = bufTiming.vActive;
		}
	}

	/* Configure CVI for any change in timing/hdmiDomain/hdmi sampling mode */
	if(vp_kwrap_iscvisource(vpInputSrc.Type)){
		if(bufTiming.isDolbyHDR)
			vp_kwrap_setcvicfg(vpSrcId, vpInputSrc, cviInfo_null);
	//1. configure CVI
		if(RET_OK == vp_kwrap_getcvicfg(vpSrcId, vpInputSrc, bufTiming, &cviInfo)){
			memcpy(&prev_cviInfo,&cviInfo, sizeof(LX_DE_CVI_SRC_TYPE_T));
			vp_kwrap_setcvicfg(vpSrcId, vpInputSrc, cviInfo);
			// 20180330 if(infoChgFlag.timingInfoChg) ret |= KADP_DE_SetInputWin(vpSrcId, &_gVPInWin[vpSrcId]);
		}
	}
	else {
			if( vpInputSrc.Type == SRC_INPUT_DTV || vpInputSrc.Type == SRC_INPUT_MVI){
				if ( bufTiming.vFreq < 550 ){
						de_kwrap_setcve(LX_DE_CVE_FROM_SRC, LX_DE_CVE_PAL);
//						KADP_DENC_Set_Output_Video_Standard(LX_DENC_PAL_BG);
					}
					else {
						de_kwrap_setcve(LX_DE_CVE_FROM_SRC, LX_DE_CVE_NTSC);
//						KADP_DENC_Set_Output_Video_Standard(LX_DENC_NTSC_M);
					}
				}
			if(_gVPInSizeChg[vpSrcId])
			{
				_gVPInSizeChg[vpSrcId] = 0;
				VP_DEBUG("[%s,%d] source size comes from platform with mvi.  h/v [%d/%d]\n",\
					__F__,__L__, _gVPInSize[vpSrcId].w, _gVPInSize[vpSrcId].h);
			}
		}

	/*2. configure PostCsc is only required in case of timing change or hdmiDomainchg
		 If source is set first time then there must be timing change.
	*/

	if(RET_OK == vp_kwrap_getcolorstd(vpInputSrc, bufTiming, cviInfo, &color_std))
		prev_HdmiConfig.color_std[vpSrcId] = color_std;

	if (vpSrcId < 1)
	{
		_gVP_PicInfo.out_col_std = color_std;
	}

	if(infoChgFlag.hdmiDomainChg || infoChgFlag.timingInfoChg){
			ret = vp_kwrap_setpostcsc(vpSrcId, color_std);

			VP_CHECK_CODE( ret != RET_OK, ret = RET_ERROR, \
				"[VP %d] vp_kwrap_setpostcsc( ) function return error \n", __L__);
	}

	//3. configure pic format
	/*********************************/
	/* set pe format info and default */
	ret = vp_kwrap_setpicformatinfo(vpSrcId, &bufTiming, &cviInfo);
	VP_CHECK_CODE( ret != RET_OK, ret = RET_ERROR, \
		"[VP %d] vp_kwrap_setpicformatinfo( ) function return error \n", __L__);
	/*********************************/

	/*4. frame rate configuration only required if timing info changed */
	if(infoChgFlag.timingInfoChg || infoChgFlag.dispFrRateChg){
		//4. configure frame rate
		if( RET_OK ==vp_kwrap_updateframerate(vpSrcId,vpInputSrc,bufTiming,&frameRateInfo))
			vp_kwrap_setfrrate(frameRateInfo.isForceFreeRun, frameRateInfo.frameRate);

		if((_gCurVpTiming[vpSrcId].vFreq != bufTiming.vFreq))
		{
			UINT32 hfr = 0;
			static UINT64 prev_msec_tick = 0;
			UINT64 curr_msec_tick = 0;

			// same condition with tvservice & gstreamer
			if(    (bufTiming.vFreq >= 610) \
				&& ((bufTiming.hActive > 1920) || (bufTiming.vActive > 1440)) \
				&& (!vp_kwrap_iscvisource(vpInputSrc.Type)) \
				&& (vpSrcId < 1))
			{
				hfr = 1;
			}
			else
			{
				hfr = 0;
			}
			_gCurVpTiming[vpSrcId].isHFRMode = hfr;
			ret = de_kwrap_sethighframerate(hfr);
#ifdef SEE_TV
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
			time = ktime_get_ns();//nanosec timer
			curr_msec_tick = time/1000000;
#else
			time = current_kernel_time(); //nanosec timer
    		curr_msec_tick = time.tv_nsec/1000000;
#endif
#else
			curr_msec_tick = KADP_OSA_ReadMsTicks();
#endif //SEETV
			if(curr_msec_tick > (prev_msec_tick + 2000))
			{
				VP_NOTI("4k HFR mode [%s]  fr[%d/10Hz] w/h[%dx%d]", \
					(hfr==0)?"OFF":"ON", bufTiming.vFreq, bufTiming.hActive, bufTiming.vActive);
			}
			prev_msec_tick = curr_msec_tick;
		}
	}

func_exit:
	/*Update timinig info in global structure */
	memcpy(&_gCurVpTiming[vpSrcId], &bufTiming, sizeof(bufTiming));

	return ret;
}

/**
*	connection info of VDO resource
*     connect : 0-disconnect, 1-connect
*
* @param vpSrcId			[IN] UINT32
* @param port			[IN] UINT32
* @param connect			[IN] BOOLEAN
* @return int
*/
int vp_kwrap_setvdoconnectInfo(UINT32 vpSrcId, UINT32 port, BOOLEAN connect)
{
	int ret = RET_OK;

	switch(connect)
	{
		case 0: // if main window disconnect, set hfr mode to off.
			if((vpSrcId == 0) && (_gCurVpTiming[vpSrcId].isHFRMode))
			{
				_gCurVpTiming[vpSrcId].isHFRMode = 0;
				ret = de_kwrap_sethighframerate(0);
				VP_NOTI("4k HFR mode off from VDO disconnect");
			}
			else
			{
				//
			}
			break;
		case 1:
		default:
			break;
	}

	return ret;
}

/**
*	enable multi windows mode for 60Hz mode(PDP)
*
* @param isEnable			[IN] BOOLEAN
* @return int
*/
int vp_kwrap_setmultiwinenable(BOOLEAN isEnable)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;

	ret = de_kwrap_setmultiwinenable(isEnable);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] MultiWinEnable = %d \n", isEnable);

	cur_inf_param.win_id = LX_PE_WIN_0;
	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);
#endif
	cur_inf_param.info_type = LX_PE_INFO_MISC;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	/**
	* causion, these items only in this function :
	* mul_win
	*/
	cur_inf_param.mul_win = isEnable;
	/* set default */
	if (pre_inf_param.mul_win != cur_inf_param.mul_win)
	{
		if (_gVP_DebugPrintOn)
		{
			VP_DEBUG("[VP][%s,%d][set]mul:%d\n", __F__, __L__, cur_inf_param.mul_win);
		}
		/* set disp info */
#ifdef INCLUDE_KDRV_PE
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, \
			"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);
#endif
	}
	return ret;
}

/*
* Handle state transition for ONE window state
*
* @param vpSrcId			[IN] UINT32
* @param param				[IN/OUT] LX_DE_OPERATION_CTRL_T *
* @param finalOper         	[IN/OUT] LX_DE_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_statetransition_onewin(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper)
{
	int ret = RET_OK;
	LX_DE_3D_INOUT_CTRL_T temp3D = {0xff, 0xff, 0xff, 0xff, 0xff};
	LX_DE_RECT_T outRegion = {0, 0, 0, 0};

	/* New state */
	switch(param->operation)
	{
		case LX_DE_OPER_ONE_WIN:
			{
				*finalOper = LX_DE_OPER_ONE_WIN;
				goto func_exit;
			}break;
		case LX_DE_OPER_TWO_WIN:
			{
				vp_kwrap_setoutwin(vpSrcId, outRegion);

				if(!_gVPQuadWin)
					vp_kwrap_setmultiwinenable((BOOLEAN)param->multiCtrl);
				else
					VP_DEBUG("[VP] quad win mode\n");

				if (!param->multiCtrl){
					*finalOper = LX_DE_OPER_ONE_WIN;
					VP_DEBUG("[%s,%d] Already in SingleWindow State \n",__F__,__L__);
					goto func_exit;
				}

				*finalOper = LX_DE_OPER_TWO_WIN;

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Multi Window = %d \n", param->multiCtrl);

			}break;
		case LX_DE_OPER_3D:
			{
				/* We are already in single window mode*/
				if (param->ctrl3D.run_mode == LX_DE_3D_RUNMODE_OFF || param->ctrl3D.run_mode == LX_DE_3D_RUNMODE_MAX){
					VP_DEBUG("[%s,%d] Already in SingleWindow State \n",__F__,__L__);
					goto func_exit;
				}

				temp3D.run_mode  = param->ctrl3D.run_mode;
				temp3D.in_img_fmt = param->ctrl3D.in_img_fmt;
				temp3D.in_lr_order = LX_DE_3D_LR_ORDER_L_FIRST;	//param->ctrl3D.in_lr_order;
				temp3D.out_img_fmt = param->ctrl3D.out_img_fmt;
				temp3D.out_lr_order = param->ctrl3D.out_lr_order;

				ret = vp_kwrap_set3dfrrate(param->ctrl3D);
				ret = de_kwrap_3dinoutctrl(&temp3D);

				*finalOper = LX_DE_OPER_3D;

				memcpy(&_gVP3DMode, &param->ctrl3D, sizeof(LX_DE_3D_INOUT_CTRL_T));

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] 3D mode(off/on/3dto2d/2dto3d)[%d]    input format [%d] out ofrmat [%d] out lr order [%d]\n",\
						param->ctrl3D.run_mode, param->ctrl3D.in_img_fmt, param->ctrl3D.out_img_fmt, param->ctrl3D.out_lr_order);

			}break;
		case LX_DE_OPER_UD:
			{
				/* Preset state is Single Window mode so no need to proceed further */
				if (param->udCtrl == LX_DE_UD_OFF || param->udCtrl == LX_DE_UD_MAX){
					VP_DEBUG("[%s,%d] Already in SingleWindow State \n",__F__,__L__);

					goto func_exit;
				}

				ret = de_kwrap_setudmode((BOOLEAN)param->udCtrl);

				*finalOper = LX_DE_OPER_UD;

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] UD = 0x%x \n", param->udCtrl);

			}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]Operaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle state transition for MultipleWindow window state
*
* @param vpSrcId			[IN] UINT32
* @param param				[IN/OUT] LX_DE_OPERATION_CTRL_T *
* @param finalOper         	[IN/OUT] LX_DE_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_statetransition_mulwin(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper)
{
	int ret = RET_OK;
	LX_DE_RECT_T outRegion = {0, 0, 0, 0};
	LX_DE_3D_INOUT_CTRL_T temp3D = {0xff, 0xff, 0xff, 0xff, 0xff};

	/* New state */
	switch(param->operation)
	{
		case LX_DE_OPER_ONE_WIN:
		{
			ret = vp_kwrap_setmultiwinenable(FALSE);
			if(RET_OK == ret){
				ret = vp_kwrap_setoutwin(1, outRegion);
				if(RET_OK == ret)
					*finalOper = LX_DE_OPER_ONE_WIN;
				else
					goto func_exit;
			}
			else
				goto func_exit;

		}break;
		case LX_DE_OPER_TWO_WIN:
			{
				vp_kwrap_setoutwin(vpSrcId, outRegion);

				if(!_gVPQuadWin)
					vp_kwrap_setmultiwinenable((BOOLEAN)param->multiCtrl);
				else
					VP_DEBUG("[VP] quad win mode\n");

				if (param->multiCtrl)	*finalOper = LX_DE_OPER_TWO_WIN;
				else					*finalOper = LX_DE_OPER_ONE_WIN;

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Multi Window = %d \n", param->multiCtrl);

			}break;
		case LX_DE_OPER_3D:
			{
				/* Allow 3Dto2D and 3D_off in multiwin state*/
				if (param->ctrl3D.run_mode != LX_DE_3D_RUNMODE_OFF && param->ctrl3D.run_mode != LX_DE_3D_RUNMODE_3DTO2D)
				{
					VP_DEBUG("[%s,%d] Not allowed 3D mode (%d) in multiwin state\n",__F__,__L__, param->ctrl3D.run_mode);
					goto func_exit;
				}

				temp3D.run_mode  = param->ctrl3D.run_mode;
				temp3D.in_img_fmt = param->ctrl3D.in_img_fmt;
				temp3D.in_lr_order = LX_DE_3D_LR_ORDER_L_FIRST;	//param->ctrl3D.in_lr_order;
				temp3D.out_img_fmt = param->ctrl3D.out_img_fmt;
				temp3D.out_lr_order = param->ctrl3D.out_lr_order;

				ret = vp_kwrap_set3dfrrate(param->ctrl3D);
				ret = de_kwrap_3dinoutctrl(&temp3D);

				*finalOper = LX_DE_OPER_TWO_WIN; /*stay in current state*/

				memcpy(&_gVP3DMode, &param->ctrl3D, sizeof(LX_DE_3D_INOUT_CTRL_T));

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] 3D mode(off/on/3dto2d/2dto3d)[%d]    input format [%d] out ofrmat [%d] out lr order [%d]\n",\
						param->ctrl3D.run_mode, param->ctrl3D.in_img_fmt, param->ctrl3D.out_img_fmt, param->ctrl3D.out_lr_order);

			}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]Operaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle state transition for 3D state
*
* @param vpSrcId			[IN] UINT32
* @param param				[IN/OUT] LX_DE_OPERATION_CTRL_T *
* @param finalOper         	[IN/OUT] LX_DE_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_statetransition_3d(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper)
{
	int ret = RET_OK;
	LX_DE_3D_INOUT_CTRL_T temp3D = {0xff, 0xff, 0xff, 0xff, 0xff};

	/* New state */
	switch(param->operation)
	{
		case LX_DE_OPER_ONE_WIN:
		{
			temp3D.run_mode  = LX_DE_3D_RUNMODE_OFF;
			de_kwrap_3dinoutctrl(&temp3D);
			vp_kwrap_set3dfrrate(temp3D);
			*finalOper = LX_DE_OPER_ONE_WIN;
		}break;
		case LX_DE_OPER_3D:
		{
			/*State parameter values can be changed like in/out image format, order */
			temp3D.run_mode  = param->ctrl3D.run_mode;
			temp3D.in_img_fmt = param->ctrl3D.in_img_fmt;
			temp3D.in_lr_order = LX_DE_3D_LR_ORDER_L_FIRST;	//param->ctrl3D.in_lr_order;
			temp3D.out_img_fmt = param->ctrl3D.out_img_fmt;
			temp3D.out_lr_order = param->ctrl3D.out_lr_order;

			ret = vp_kwrap_set3dfrrate(param->ctrl3D);
			ret = de_kwrap_3dinoutctrl(&temp3D);

			if (param->ctrl3D.run_mode == LX_DE_3D_RUNMODE_OFF || param->ctrl3D.run_mode == LX_DE_3D_RUNMODE_MAX)
				*finalOper = LX_DE_OPER_ONE_WIN;
			else
				*finalOper = LX_DE_OPER_3D;

			memcpy(&_gVP3DMode, &param->ctrl3D, sizeof(LX_DE_3D_INOUT_CTRL_T));

			if (_gVP_DebugPrintOn)
				VP_DEBUG("[VP] 3D mode(off/on/3dto2d/2dto3d)[%d]    input format [%d] out ofrmat [%d] out lr order [%d]\n",\
					param->ctrl3D.run_mode, param->ctrl3D.in_img_fmt, param->ctrl3D.out_img_fmt, param->ctrl3D.out_lr_order);

		}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]Operaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVOperState);
				goto func_exit;
			}
	}


func_exit:
	return ret;
}

/*
* Handle state transition for UD state
*
* @param vpSrcId			[IN] UINT32
* @param param				[IN/OUT] LX_DE_OPERATION_CTRL_T *
* @param finalOper         	[IN/OUT] LX_DE_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_statetransition_ud(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper)
{
	int ret = RET_OK;

	/* New state */
	switch(param->operation)
	{
		case LX_DE_OPER_ONE_WIN:
		{
			de_kwrap_setudmode(FALSE);
			*finalOper = LX_DE_OPER_ONE_WIN;
		}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]Operaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle state transition for VENC[Analog recording] state
*
* @param vpSrcId			[IN] UINT32
* @param param				[IN/OUT] LX_DE_OPERATION_CTRL_T *
* @param finalOper         	[IN/OUT] LX_DE_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_statetransition_venc(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param, LX_DE_OPER_CONFIG_T *finalOper)
{
	int ret = RET_OK;

	/* New state */
	switch(param->operation)
	{
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]Operaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Set operation type and state transition
*
* @param vpSrcId			[IN] UINT32
* @param param				[IN/OUT] LX_DE_OPERATION_CTRL_T *
* @return int
*/
int vp_kwrap_setoperation(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param)
{
	int ret = RET_OK;
	LX_DE_OPER_CONFIG_T  tempOper = LX_DE_OPER_ONE_WIN;

	CHECK_NULL(param);
	CHECK_SRC_ID(vpSrcId);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Present OperId[%d] New OperId[%d]\n", _gCurTVOperState, param->operation);


	switch(_gCurTVOperState)
	{
		case LX_DE_OPER_ONE_WIN:
			{
				ret = vp_kwrap_statetransition_onewin(vpSrcId, param,&tempOper);
			}break;
		case LX_DE_OPER_TWO_WIN:
			{
				ret = vp_kwrap_statetransition_mulwin(vpSrcId, param, &tempOper);
			}break;
		case LX_DE_OPER_3D:
			{
				ret = vp_kwrap_statetransition_3d(vpSrcId, param, &tempOper);
			}break;
		case LX_DE_OPER_UD:
			{
				ret = vp_kwrap_statetransition_ud(vpSrcId, param, &tempOper);
			}break;
		case LX_DE_OPER_VENC:
			{
				ret = vp_kwrap_statetransition_venc(vpSrcId, param, &tempOper);
			}break;
		default:
			{
				VP_BREAK_WRONG(param->operation);
			}break;
	}

	if(RET_OK == ret){
		ret = de_kwrap_setoperation(param);

		if(RET_OK == ret){
			_gCurTVOperState = tempOper;
		}
		else
			VP_ERROR("[%s,%d] de_kwrap_setoperation( ) function return error.\n",__F__,__L__);
	}

	return ret;
}

/*
* Handle substate transition for OFF [no sub-operation]state
*
* @param param				[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param subParam         	[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param finalSubOper		[IN/OUT] LX_DE_SUB_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_substatetransition_off(LX_DE_SUB_OPERATION_CTRL_T *param,LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper)
{
	int ret = RET_OK;

	switch (param->operation)
	{
		case LX_DE_SUB_OPER_OFF:
			{
				/* Nothing to do*/
				*finalSubOper = LX_DE_SUB_OPER_OFF;
				goto func_exit;
			}break;
		case LX_DE_SUB_OPER_CAPTURE:
			{
				if (param->capture_enable == 0){
					/* Nothing to do*/
					*finalSubOper = LX_DE_SUB_OPER_OFF;
					goto func_exit;
				}

				subParam->win_id = 0;
				subParam->capture_enable = param->capture_enable;
				*finalSubOper = LX_DE_SUB_OPER_CAPTURE;

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Sub Oper Capture  = %s \n", (param->capture_enable == 1)?"Enable":"Disable");

			}break;
		case LX_DE_SUB_OPER_VENC:
			{
				if (param->vencCtrl.bOnOff == 0){
					*finalSubOper = LX_DE_SUB_OPER_OFF;
					goto func_exit;
				}

				if (param->vencCtrl.hSize > 1920 ||	param->vencCtrl.vSize > 1080)
				{
					VP_ERROR("[VP %d] Sub Oper VENC parameter error hSize[%d] || vSize [%d].\n", \
						__L__, param->vencCtrl.hSize, param->vencCtrl.vSize);
					ret = RET_ERROR;
					goto func_exit;
				}

				subParam->win_id = 0;
				memcpy(&(subParam->vencCtrl), &(param->vencCtrl), sizeof(LX_DE_VENC_FMT_T));
				*finalSubOper = LX_DE_SUB_OPER_VENC;

				de_kwrap_setsubwindow(param->win_id);
				ret = de_kwrap_setdvrfmtctrl(param->vencCtrl.bOnOff, param->vencCtrl.scan, param->vencCtrl.hSize, param->vencCtrl.vSize, param->vencCtrl.frRate);
				de_kwrap_setsubwindow(0);

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Sub Oper VENC  [0x%x] scan[%s], hSize[%d], vSize[%d] frRate[%d] \n",\
						param->vencCtrl.bOnOff,(param->vencCtrl.scan==1)?"P":"I",\
						param->vencCtrl.hSize, param->vencCtrl.vSize, param->vencCtrl.frRate);

			}break;
		case LX_DE_SUB_OPER_SCART_OUT:
			{
				if (param->capture_enable == 0){
					*finalSubOper = LX_DE_SUB_OPER_OFF;
					goto func_exit;
				}

				subParam->win_id = 0;
				subParam->capture_enable = param->capture_enable;
				*finalSubOper = LX_DE_SUB_OPER_SCART_OUT;

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Sub Oper Scart Out  = %s \n", (param->capture_enable == 1)?"Enable":"Disable");

			}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]SubOperaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle substate transition for capture state
*
* @param param				[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param subParam         	[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param finalSubOper		[IN/OUT] LX_DE_SUB_OPER_CONFIG_T *
* @return int
*/
static  int vp_kwrap_substatetransition_capture(LX_DE_SUB_OPERATION_CTRL_T *param,LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper)
{
	int ret = RET_OK;
	LX_DE_CAPTURE_CTRL_T capParam;

	switch (param->operation)
	{
		case LX_DE_SUB_OPER_OFF:
			{
				subParam->win_id = 0;
				subParam->capture_enable = 0;

				memset( &capParam, 0, sizeof( LX_DE_CAPTURE_CTRL_T ));
				ret = de_kwrap_framecapture(subParam->capture_enable, &capParam);
				if(RET_OK == ret)
					*finalSubOper = LX_DE_SUB_OPER_OFF;
				else
					goto func_exit;
			}break;
		case LX_DE_SUB_OPER_CAPTURE:
			{
				if (param->capture_enable == 0)
				{
					subParam->win_id = 0;
					subParam->capture_enable = param->capture_enable;
					memset( &capParam, 0, sizeof( LX_DE_CAPTURE_CTRL_T ));
					ret = de_kwrap_framecapture(subParam->capture_enable, &capParam);
					*finalSubOper = LX_DE_SUB_OPER_OFF;
				}
				else {
					*finalSubOper = LX_DE_SUB_OPER_CAPTURE;
					goto func_exit;
				}

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Sub Oper Capture  = %s \n", (param->capture_enable == 1)?"Enable":"Disable");

			}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]SubOperaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVSubOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle substate transition for scart-out[Not for M16] state
*
* @param param				[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param subParam         	[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param finalSubOper		[IN/OUT] LX_DE_SUB_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_substatetransition_scartout(LX_DE_SUB_OPERATION_CTRL_T *param, LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper)
{
	int ret = RET_OK;

	switch (param->operation)
	{
		case LX_DE_SUB_OPER_OFF:
			{
				subParam->win_id = 0;
				subParam->capture_enable = 0;
				*finalSubOper = LX_DE_SUB_OPER_OFF;

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Disable Prev OperId[%d] \n", _gCurTVSubOperState);

			}break;
		case LX_DE_SUB_OPER_SCART_OUT:
			{
				if (param->capture_enable == 0){
					subParam->win_id = 0;
					subParam->capture_enable = param->capture_enable;
					*finalSubOper = LX_DE_SUB_OPER_OFF;
				}
				else {
					*finalSubOper = LX_DE_SUB_OPER_SCART_OUT;
					goto func_exit;
				}

				if (_gVP_DebugPrintOn)
					VP_DEBUG("[VP] Sub Oper Scart Out  = %s \n", (param->capture_enable == 1)?"Enable":"Disable");

			}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]SubOperaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVSubOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle substate transition for VENC[Analog channel recording] state
*
* @param param				[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param subParam         	[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @param finalSubOper		[IN/OUT] LX_DE_SUB_OPER_CONFIG_T *
* @return int
*/
static int vp_kwrap_substatetransition_venc(LX_DE_SUB_OPERATION_CTRL_T *param, LX_DE_SUB_OPERATION_CTRL_T *subParam, LX_DE_SUB_OPER_CONFIG_T *finalSubOper)
{
	int ret = RET_OK;

	switch (param->operation)
	{
		case LX_DE_SUB_OPER_OFF:
			{
				de_kwrap_setsubwindow(param->win_id);
				subParam->vencCtrl.bOnOff = 0;
				ret = de_kwrap_setdvrfmtctrl(param->vencCtrl.bOnOff, param->vencCtrl.scan, param->vencCtrl.hSize, param->vencCtrl.vSize, param->vencCtrl.frRate);
				de_kwrap_setsubwindow(0);
				*finalSubOper = LX_DE_SUB_OPER_OFF;

			}break;
		case LX_DE_SUB_OPER_VENC:
			{
				if (param->vencCtrl.hSize > 1920 ||	param->vencCtrl.vSize > 1080)
				{
					VP_ERROR("[VP %d] Sub Oper VENC parameter error hSize[%d] || vSize [%d].\n", \
						__L__, param->vencCtrl.hSize, param->vencCtrl.vSize);
					ret = RET_ERROR;
					goto func_exit;
				}

				subParam->win_id = 0;
				memcpy(&subParam->vencCtrl, &param->vencCtrl, sizeof(LX_DE_VENC_FMT_T));
				*finalSubOper = LX_DE_SUB_OPER_VENC;

				de_kwrap_setsubwindow(param->win_id);
				ret = de_kwrap_setdvrfmtctrl(param->vencCtrl.bOnOff, param->vencCtrl.scan, param->vencCtrl.hSize, param->vencCtrl.vSize, param->vencCtrl.frRate);
				de_kwrap_setsubwindow(0);

				if (param->vencCtrl.bOnOff == 0){
					*finalSubOper = LX_DE_SUB_OPER_OFF;
				}
				else {
					*finalSubOper = LX_DE_SUB_OPER_VENC;
					goto func_exit;
				}
			}break;
		default:
			{
				ret = RET_ERROR;
				VP_ERROR("[%s,%d] [%d]SubOperaton not supported in this state[%d]. \n",__F__,__L__,param->operation,_gCurTVSubOperState);
				goto func_exit;
			}
	}

func_exit:
	return ret;
}

/*
* Handle substate setting and transition handling
*
* @param param				[IN/OUT] LX_DE_SUB_OPERATION_CTRL_T *
* @return int
*/
int KADP_VP_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *param)
{
	int ret = RET_OK;
	LX_DE_SUB_OPER_CONFIG_T  tempSubOper = LX_DE_SUB_OPER_OFF;
	LX_DE_SUB_OPERATION_CTRL_T subOper = {0, LX_DE_SUB_OPER_OFF, 0, {0, 0, 0, 0, 0}};

	CHECK_NULL(param);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Prev Sub OperId[%d] Curr Sub OperId[%d]\n", _gCurTVSubOperState, param->operation);

	if (_gCurTVSubOperState != param->operation && \
		param->operation > LX_DE_SUB_OPER_OFF && _gCurTVSubOperState > LX_DE_SUB_OPER_OFF)
	{
		VP_ERROR("[VP] Prev Sub OperId[%d] differs from Curr Sub OperId[%d]\n", _gCurTVSubOperState, param->operation);
		return ret = RET_ERROR;
	}

	subOper.operation = param->operation;

	/*Based on the present state call state change functions */
	switch(_gCurTVSubOperState)
	{
		case LX_DE_SUB_OPER_OFF:
			{
				ret = vp_kwrap_substatetransition_off(param,&subOper,&tempSubOper);
			}break;
		case LX_DE_SUB_OPER_CAPTURE:
			{
				ret = vp_kwrap_substatetransition_capture(param,&subOper,&tempSubOper);
			}break;
		case LX_DE_SUB_OPER_SCART_OUT:
			{
				ret = vp_kwrap_substatetransition_scartout(param,&subOper,&tempSubOper);
			}break;
		case LX_DE_SUB_OPER_VENC:
			{
				ret = vp_kwrap_substatetransition_venc(param,&subOper,&tempSubOper);
			}break;

	default:
			{
				VP_ERROR("[%s,%d] KADP Unsupported Sub-operation\n",__F__,__L__);
			}break;
	}

	if(RET_OK == ret){
		ret = de_kwrap_setsuboperation(&subOper);
		if(RET_ERROR == ret){
			VP_ERROR("[%s,%d] KADP_DE_SetSubOperation( ) function return error.\n",__F__,__L__);
		}
	}
	else {
			VP_ERROR("[%s,%d] Sub State transition Error\n",__F__,__L__);
		}

	return ret;
}

/**
 * get vp window info.
 *
 * @param   *pInfo [in] kwrap_vp_pic_info_t
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KADP_VP_GetPicInfo(kwrap_vp_pic_info_t *pInfo)
{
	CHECK_NULL(pInfo);
	memcpy(pInfo, &_gVP_PicInfo, sizeof(kwrap_vp_pic_info_t));
	return RET_OK;
}

/**
 * check picture info.
 *	- additionally set post csc in dw mode
 *
 * @param   wId [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
static int vp_kwrap_checkpicinfo(UINT32 wId)
{
	int ret = RET_OK;
	BOOLEAN b_is_dw_md=FALSE;
	LX_DE_RECT_T *p_out_win0 = &(_gVP_PicInfo.o_win[LX_DE_WIN_MAIN]);
	LX_DE_RECT_T *p_out_win1 = &(_gVP_PicInfo.o_win[LX_DE_WIN_SUB]);

	CHECK_SRC_ID(wId);

	/* main only */
	if (wId!=LX_DE_WIN_MAIN)
		return RET_OK;
	/* check dw mode */
	#if 0	//20151102, sj.youm, change condition for dw_md
	b_is_dw_md = (_gCurTVOperState == LX_DE_OPER_TWO_WIN && \
		p_out_win0->w==p_out_win1->w && p_out_win0->h==p_out_win1->h && \
		p_out_win0->w>0 && p_out_win0->h>0 && p_out_win0->x==0)? TRUE:FALSE;
	#else
	b_is_dw_md = (_gVP_PicInfo.sub_mode==LX_DE_SUB_MODE_PBP)? TRUE:FALSE;
	#endif
	if (_gVP_PicInfo.b_is_dw_md!=b_is_dw_md)
	{
		if (_gVP_DebugPrintOn)
		{
			VP_DEBUG("[VP][%s,%d][inf]wId:%d, opr:%d, sub_mode:%d,"\
				"o_win:[0]%d,%d,%d,%d, [1]%d,%d,%d,%d\n", \
				__F__, __L__, wId,_gCurTVOperState, _gVP_PicInfo.sub_mode, \
				p_out_win0->x, p_out_win0->y, p_out_win0->w, \
				p_out_win0->h, p_out_win1->x, p_out_win1->y, \
				p_out_win1->w, p_out_win1->h);
			VP_DEBUG("[VP][%s,%d][set]dwMd:%d -> %d, "\
				"set post csc(prev std:%d)\n", \
				__F__, __L__, _gVP_PicInfo.b_is_dw_md? 1:0, \
				b_is_dw_md? 1:0, _gVP_PicInfo.out_col_std);
		}
		_gVP_PicInfo.b_is_dw_md=b_is_dw_md;
		ret = vp_kwrap_setpostcsc(LX_DE_WIN_MAIN, _gVP_PicInfo.out_col_std);
		VP_CHECK_CODE( ret != RET_OK, return RET_ERROR, \
			"[VP %d] vp_kwrap_setpostcsc( ) function return error \n", __L__);
	}
	return ret;
}


#if 0
/**
 * set(update) picture reverse mode info.
 *	- set mode.is_reverse
 *
 * @param   mode_on [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
static int vp_kwrap_setpicreversemodeinfo(UINT32 mode_on)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T param;
	param.win_id = LX_PE_WIN_0;		// don't care win, fix win_0

	/* get pre display info */
	ret = KWRAP_PE_GetCurPicDisplayInfo((void *)&param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] KWRAP_PE_GetCurPicDisplayInfo( ) function return error \n", __L__);
	/* reverse mode */
	param.mode.is_reverse = mode_on? 1:0;
	if (_gVP_DebugPrintOn)
	{
		VP_DEBUG("[VP][%s,%d][set]wid:%d, is_reverse:%d\n", \
			__F__, __L__, param.win_id, param.mode.is_reverse);
	}
	/* set display info */
	ret = KWRAP_PE_SetPicDisplayInfo((void *)&param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] KWRAP_PE_SetPicDisplayInfo( ) function return error \n", __L__);
	return ret;
}
#endif

/**
 * set post csc
 *
 * @param   wId [in] UINT32
 * @param   cStd [in] LX_DE_COLOR_STD_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int vp_kwrap_setpostcsc(UINT32 vpSrcId, LX_DE_COLOR_STD_T cStd)
{
	int ret = RET_OK;
	PE_KWRAP_CTRL_T param;

	CHECK_SRC_ID(vpSrcId);

	if (vpSrcId>LX_DE_WIN_MAIN)
	{
		if (_gVP_DebugPrintOn)	//for debug
		{
			VP_DEBUG("[VP]w(%d):not support.\n", vpSrcId);
		}
		return RET_OK;
	}
	param.wid = LX_PE_WIN_0;
	#ifdef VP_KWRAP_ADD_CHK_PIC_INFO
	if (_gVP_PicInfo.b_is_dw_md)
	{
		cStd=LX_DE_COLOR_601;
	}
	#endif
	/* use y to rgb expend */
	switch (cStd)
	{
		case LX_DE_COLOR_2020_CL:
			param.data = LX_PE_POST_CSC_2020_CL_EXP;
			break;
		case LX_DE_COLOR_2020_NCL:
			param.data = LX_PE_POST_CSC_2020_NCL_EX;
			break;
		case LX_DE_COLOR_601:
		case LX_DE_COLOR_601_CVD:
		case LX_DE_COLOR_XVYCC601:
			param.data = LX_PE_POST_CSC_Y601_EXPEND;
			break;
		case LX_DE_COLOR_709:
		case LX_DE_COLOR_XVYCC709:
		case LX_DE_COLOR_RGB:
		case LX_DE_COLOR_RGBEX:
		default:
			param.data = LX_PE_POST_CSC_Y709_EXPEND;
			break;
	}

	if (_gVP_DebugPrintOn)	//for debug
	{
		VP_DEBUG("[VP][%s,%d][inf]bIsDwMd:%d,"\
			" cStd:%d, [set]wid:%d, data:%d\n", __F__, __L__, \
			_gVP_PicInfo.b_is_dw_md? 1:0, cStd, param.wid, param.data);
	}

#ifdef INCLUDE_KDRV_PE
	ret = KWRAP_PE_SetPostCscCtrl(&param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] KWRAP_PE_SetPostCscCtrl() error \n", __L__);
#endif

	_gVP_PicInfo.post_csc_type = (UINT32)param.data;
	return ret;
}

/**
 * set display vertical reverse.
 *
 * @param   mode [in] UINT8
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int vp_kwrap_vertical_reverse(UINT8 mode)
{
	int ret = RET_ERROR;
#if 0
	LX_DE_IF_CONFIG_T ifConfig = {LX_DE_CONFIG_TYPE_DISPLAY_MIRROR, LX_DE_DIS_DEV_LCD, LX_DE_DIS_MIRROR_OFF,  LX_DE_FRC_PATH_INTERNAL, LX_DE_3D_CTRL_ON };
    BE_SET_DEFAULT_PARAM(be_display_type_t, beParam);
   	LX_DE_SYS_STATUS_T sysParam;

	do {
		memset( &sysParam, 0, sizeof( LX_DE_SYS_STATUS_T ));
		sysParam.status_type = LX_DE_SYS_STATUS_ALL;
		de_kwrap_getsysstatus(&sysParam);

		if (sysParam.display_type != LX_DE_DIS_DEV_MAX && sysParam.display_mirror != LX_DE_DIS_MIRROR_MAX)
		{
			ifConfig.display_type = sysParam.display_type;
			ifConfig.display_mirror = sysParam.display_mirror;
			ifConfig.frc_type = sysParam.frc_type;
			ifConfig.trid_type = sysParam.trid_type;
		}

		if (mode)
		{
			ifConfig.display_mirror = LX_DE_DIS_MIRROR_Y;
			beParam.u32BEPanelReverse = 1;
		}
		else
		{
			ifConfig.display_mirror = LX_DE_DIS_MIRROR_OFF;
			beParam.u32BEPanelReverse = 0;
		}

		/* Step 1. Set params for DE control */
		ret = de_kwrap_setifconfig(&ifConfig);
		VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] de_kwrap_setifconfig( ) function return error \n", __L__);
		/* Step 2. Set reverse mode for PE window control */
		ret = vp_kwrap_setpicreversemodeinfo(mode? 1:0);
		VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] vp_kwrap_setpicreversemodeinfo( ) error \n", __L__);
		 /* Step 3. Set params for BE control */
		ret = be_kwrap_top_set_display_type(&beParam);
		VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] be_kwrap_top_set_display_type( ) error \n", __L__);

		if (_gVP_DebugPrintOn)
			VP_DEBUG("[VP] Set Vertical Reverse mode[%d] \n", mode);
	}while (0);
#endif
	return ret;
}

/**
 * get frame rate for setting frame rate.
 *
 * @param   vpInputSrc [in] kwrap_vp_src_info_t
 * @param   srcTiming [in] kwrap_vp_timing_info_t
  * @param  frameRates [out] UINT16 *
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
static int vp_kwrap_checkfrrate(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t srcTiming, UINT16 *frameRate)
{
	CHECK_NULL(frameRate);

	if(srcTiming.vFreq > 900)
	{
		srcTiming.vFreq = srcTiming.vFreq >> 1;
		if (u16CHK_RANGE(srcTiming.vFreq,500,5))
			*frameRate = 50;
		else if (u16CHK_RANGE(srcTiming.vFreq,600,5))
			*frameRate = 60;
	}
#ifdef NEW_FR_CHECK_FOR_Y18
	else if (srcTiming.vFreq > 550)
	{
		*frameRate = 60;
	}
	else
	{
		if (u16CHK_RANGE(srcTiming.vFreq,500,5) || u16CHK_RANGE(srcTiming.vFreq,250,5))
			*frameRate = 50;
		else
		{
			if ( (vpInputSrc.Type > SRC_INPUT_YPBPR) && (vpInputSrc.Type < SRC_INPUT_HDMI) )
				*frameRate = 60;
			else
			{
				if (u16CHK_RANGE(srcTiming.vFreq,240,5) && (TRUE == vp_kwrap_checkpulldownmode()))
					*frameRate = 48;
				else
					*frameRate = 60;
			}
		}
	}
#else
	else if (srcTiming.vFreq > 550)
	{
		if ( (srcTiming.vFreq == 599) ||((vpInputSrc.Type > SRC_INPUT_YPBPR) && (vpInputSrc.Type < SRC_INPUT_HDMI)) )
			*frameRate = 59;
		else
			*frameRate = 60;
	}
	else
	{
		if (u16CHK_RANGE(srcTiming.vFreq,500,5) || u16CHK_RANGE(srcTiming.vFreq,250,5))
			*frameRate = 50;
		else
		{
			if ( (vpInputSrc.Type > SRC_INPUT_YPBPR) && (vpInputSrc.Type < SRC_INPUT_HDMI) )
				*frameRate = 59;
			else
			{
				if (u16CHK_RANGE(srcTiming.vFreq,240,5) && (TRUE == vp_kwrap_checkpulldownmode()))
					*frameRate = 48;
				else
					*frameRate = 60;
			}
		}
	}
#endif
	 if (vpInputSrc.Type == SRC_INPUT_VGA)
		*frameRate = 60;

#ifdef USE_CPBOX
	*frameRate = 60;
#endif

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Retuen Frame Rate[%d] \n", *frameRate);

	return RET_OK;
}

/**
 * set display frame rate.
 *
 * @param   ctrl3D [in] LX_DE_3D_INOUT_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
static int vp_kwrap_set3dfrrate(LX_DE_3D_INOUT_CTRL_T ctrl3D)
{
	int ret = RET_OK;
	BOOLEAN isForceFreeRun = 0;
	UINT16 preFrameRate = 0, frameRate = 0;

	de_kwrap_getoutfrrate(&isForceFreeRun, &preFrameRate);

	if (ctrl3D.run_mode == LX_DE_3D_RUNMODE_ON)
	{
		if (ctrl3D.out_img_fmt > LX_DE_3D_IMG_OUT_SINGLE_SS && ctrl3D.out_img_fmt < LX_DE_3D_IMG_OUT_SINGLE_LA)
		{
			if (u16CHK_RANGE(_gCurVpTiming[LX_DE_WIN_0].vFreq,480,5) || u16CHK_RANGE(_gCurVpTiming[LX_DE_WIN_0].vFreq,240,5))
				frameRate = 48;
			//else if (u16CHK_RANGE(_gCurVpTiming[LX_DE_WIN_0].vFreq,250,5))
				//frameRate = 50;
			//else if (u16CHK_RANGE(_gCurVpTiming[LX_DE_WIN_0].vFreq,300,5))
				//frameRate = 60;
		}
		else
		{
			vp_kwrap_checkfrrate(_gVPInputSrcCfg[LX_DE_WIN_0], _gCurVpTiming[LX_DE_WIN_0], &frameRate);
		}
	}
	else if (ctrl3D.run_mode == LX_DE_3D_RUNMODE_3DTO2D)
	{
		//LX_DE_SYS_STATUS_T sysInfo = {LX_DE_SYS_STATUS_FRC, 0, 0, 0, 0};
		//KADP_DE_GetSysStatus(&sysInfo);

		if (ctrl3D.out_img_fmt == LX_DE_3D_IMG_OUT_SINGLE_2D) // sysInfo.frc_type == LX_DE_FRC_PATH_INTERNAL);
		{
			if (u16CHK_RANGE(_gCurVpTiming[LX_DE_WIN_0].vFreq,480,5))
				frameRate = 48;
			else if (u16CHK_RANGE(_gCurVpTiming[LX_DE_WIN_0].vFreq,240,5))
			{
				if (TRUE == vp_kwrap_checkpulldownmode())
					frameRate = 48;
				else
					frameRate = 60;
			}
		}
	}
	else
	{
		vp_kwrap_checkfrrate(_gVPInputSrcCfg[LX_DE_WIN_0], _gCurVpTiming[LX_DE_WIN_0], &frameRate);
	}

	if (frameRate > 0)
	{
		if (_gVP_DebugPrintOn)
			VP_DEBUG("[VP] Pre FrRate[%d] Cur FrRate[%d] in 3D operation \n", preFrameRate, frameRate);

		if (preFrameRate == frameRate)
			return ret;

		ret = vp_kwrap_setfrrate(isForceFreeRun, frameRate);
	}
	else
	{
		if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP]  Skip set FrRate[%d] in 3D operation \n", preFrameRate);
	}
	return ret;
}


/**
 * set display frame rate.
 *
 * @param   isForceFreeRun [in] BOOLEAN
 * @param   frameRates [in] UINT16
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int vp_kwrap_setfrrate(BOOLEAN isForceFreeRun, UINT16 frameRate)
{
	int ret = RET_ERROR;

	ret = de_kwrap_setfrrate(isForceFreeRun, frameRate);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Set Frame Rate[%d] FreeRun[%d]\n", frameRate, isForceFreeRun);

	VP_CHECK_CODE( ret != RET_OK, return ret, "[VP %d] : de_kwrap_setfrrate function return error \n", __L__);

	return ret;
}

/**
 * Check pull down mode
 *	- 24p Src to 48hz FrRate, if m16 && internal frc && memc pulldown
 *
 * @param   void
 * @return  BOOLEAN
 * @see		func. description
 * @author
 */
static BOOLEAN vp_kwrap_checkpulldownmode(void)
{
	BOOLEAN bCurPdMode = 0;
#if 0
	static BOOLEAN bPrePdMode = FALSE;
	be_frc_info_t frc_info = {0,0,{LX_BE_FRC_CFG_TYPE_NONE,0},{0,0,0,0}};
	UINT32 pd_stat = 0;
	LX_BE_FRC_CFG_T	*p_cfg = &(frc_info.cfg);
	LX_BE_FRC_MEMC_MODE_T *p_memc = &(frc_info.memc);
	bCurPdMode = FALSE;
	if (lx_chip_rev()>=LX_CHIP_REV(M17,A0) || lx_chip_rev()>=LX_CHIP_REV(M16,A0))//M16P,M16
	{
		do {
			if (RET_OK != be_kwrap_frc_getcurinfo(&frc_info))		{pd_stat=10;break;}	//check error
			if (!(p_cfg->cfg_type&LX_BE_FRC_CFG_TYPE_USE))			{pd_stat=11;break;}	//check update
			if (p_cfg->use_type)									{pd_stat=12;break;}	//check internal
			if (p_cfg->dfr_type)									{pd_stat=13;break;}	//check 60hz diplay
			if (p_memc->u8MemcType!=LX_BE_FRC_MEMC_PULLDOWN)		{pd_stat=14;break;}	//check pulldown
			if (!frc_info.pd_en)									{pd_stat=15;break;}	//check pulldown enable
			if (_gVPInputSrcTemp[LX_DE_WIN_0].Type<SRC_INPUT_HDMI)	{pd_stat=16;break;}	//check hdmi,dtv,mvi,jpg input
			if (_gVPInputSrcTemp[LX_DE_WIN_0].Type>SRC_INPUT_JPG)	{pd_stat=17;break;}	//check hdmi,dtv,mvi,jpg input
			if (_gVP_PicInfo.sub_mode == LX_DE_SUB_MODE_PBP)		{pd_stat=18;break;}	//check two win
			bCurPdMode = TRUE;
		} while(0);
	}
	else
	{
		pd_stat=99;
	}
	be_kwrap_frc_setpulldownstate(pd_stat);
	if (bPrePdMode != bCurPdMode)
	{
		if (_gVP_DebugPrintOn)
		{
			VP_DEBUG("[VP] PdMode:%d->%d, en,st,cf,use,dfr,mc,src,sub:0x%x,%d,0x%x,%d,%d,%d,%d,%d\n", \
			bPrePdMode? 1:0, bCurPdMode? 1:0, frc_info.pd_en, frc_info.pd_stat, \
			p_cfg->cfg_type, p_cfg->use_type, p_cfg->dfr_type, p_memc->u8MemcType, \
			_gVPInputSrcTemp[LX_DE_WIN_0].Type, _gVP_PicInfo.sub_mode);
		}
		bPrePdMode = bCurPdMode;
	}
#endif	
	return bCurPdMode;
}

/**
* get vp input src cfg
*
* @param vpSrcId [IN] UINT32
* @param *pVpSrcCfg [IN] kwrap_vp_src_info_t
*
* @return int
*/
int vp_kwrap_getinputsrccfg(UINT32 vpSrcId,kwrap_vp_src_info_t *pVpSrcCfg)
{
	int ret = RET_ERROR;

	CHECK_NULL(pVpSrcCfg);
	CHECK_SRC_ID(vpSrcId);

	do {
		pVpSrcCfg->Type = _gVPInputSrcCfg[vpSrcId].Type;
		pVpSrcCfg->Port = _gVPInputSrcCfg[vpSrcId].Port;
		pVpSrcCfg->Attr = _gVPInputSrcCfg[vpSrcId].Attr;
		pVpSrcCfg->Resv = _gVPInputSrcCfg[vpSrcId].Resv;
		ret = RET_OK;
	} while (0);
	return ret;
}

/**
* get vp input window info
*
* @param vpSrcId [IN] UINT32
* @param *pInWin [IN] LX_DE_RECT_T
*
* @return int
*/
int vp_kwrap_getinputwin(UINT32 vpSrcId, LX_DE_RECT_T *pInWin)
{
	int ret = RET_ERROR;
	LX_DE_RECT_T 	inWin = {0, 0, 0, 0};

	CHECK_NULL(pInWin);
	CHECK_SRC_ID(vpSrcId);

	ret = de_kwrap_getinputwin((UINT8)vpSrcId, &inWin);

	pInWin->x	= inWin.x;
	pInWin->y	= inWin.y;
	pInWin->w	= inWin.w;
	pInWin->h	= inWin.h;

	VP_PRINT("[VP] Get Input Window[%d] whxy(%d,%d,%d,%d)\n", \
		vpSrcId, pInWin->w, pInWin->h, pInWin->x, pInWin->y);

	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] : vp_kwrap_getinputwin function return error \n", __L__);

	return ret;
}

/**
* get vp output window info
*
* @param vpSrcId [IN] UINT32
* @param *pOutWin [IN] LX_DE_RECT_T
*
* @return int
*/
int vp_kwrap_getoutwin(UINT32 vpSrcId, LX_DE_RECT_T *pOutWin)
{
	int ret = RET_ERROR;
	LX_DE_RECT_T 	outWin = {0, 0, 0, 0};

	CHECK_NULL(pOutWin);
	CHECK_SRC_ID(vpSrcId);

	ret = de_kwrap_getoutwin((UINT8)vpSrcId, &outWin);

	pOutWin->x	= outWin.x;
	pOutWin->y	= outWin.y;
	pOutWin->w	= outWin.w;
	pOutWin->h	= outWin.h;

	VP_PRINT("[VP] Get Output Window[%d] whxy(%d,%d,%d,%d)\n", \
		vpSrcId, pOutWin->w, pOutWin->h, pOutWin->x, pOutWin->y);

	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] : vp_kwrap_getoutwin function return error \n", __L__);

	return ret;
}

/**
* set rotate, source size, in/out window info
*
* @param pWinInfo [IN] LX_DE_WIN_INFO_T
*
* @return int
*/
int vp_kwrap_setwindowinfo(LX_DE_WIN_INFO_T *pWinInfo)
{
	int ret = RET_ERROR;

	ret = de_kwrap_setwindowinfo(pWinInfo);

	return ret;
}


/**
 * 	detecting actual format from specific pixel value
 *	@param param [In] LX_DE_ACT_FORMAT_T
 * 	@return int
 */
int vp_kwrap_setactfmtdetect(LX_DE_ACT_FORMAT_T param)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
	LX_PE_DEFAULT_SETTINGS_T dft_param;

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] ActFmtDetect enable:%d, \n", \
			param.enable);

	_gAdaptive_ = param.enable;

	ret = de_kwrap_setactfmtdetect(param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] de_kwrap_setactfmtdetect( ) function return error \n", __L__);

	cur_inf_param.win_id = LX_PE_WIN_0;
	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	cur_inf_param.info_type = LX_PE_INFO_MISC;
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	cur_inf_param.act_fmt = (UINT32)param.enable;
	/* set default */
	if (pre_inf_param.act_fmt != cur_inf_param.act_fmt)
	{
		if (_gVP_DebugPrintOn)
		{
			VP_DEBUG("[VP] set pic_disp act_fmt:%d -> %d\n", \
				pre_inf_param.act_fmt, cur_inf_param.act_fmt);
		}
		/* set display info */
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, \
			"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);
		/* set default settings */
		dft_param.win_id = cur_inf_param.win_id;
		ret = vpq_hwrap_setdefaultsettings((void *)&dft_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, \
			"[VP %d] vpq_hwrap_setdefaultsettings( ) function return error \n", __L__);
	}
#endif
	return ret;
}

/**
 * 	set current quad window mode
 *	@param param [In] LX_DE_ACT_FORMAT_T
 * 	@return int
 */
int vp_kwrap_setquadwinmode( UINT16 bOnOff )
{
	int multi_win_mode = 0;

	_gVPQuadWin = bOnOff;

	multi_win_mode = _gVPQuadWin?4:0;

	vp_kwrap_setmultiwinenable(multi_win_mode);

	VP_NOTI("[VP] quadwin[%d]  multiwinenable[%d] (0:0ff,4:quad)\n", _gVPQuadWin, multi_win_mode);

	return RET_OK;
}

/**
 * 	set current win_id & hdmi port
 *	@param param [In] wId, hdmi_port
 * 	@return int
 */
int vp_kwrap_sethdmiport(UINT8 wId, UINT32 hdmi_port)
{
	CHECK_SRC_ID(wId);
	_gVPHdmiPort[wId] = hdmi_port;
	return de_kwrap_sethdmiport(wId, hdmi_port);
}

/**
 * 	set current win_id & hdmi port
 *	@param param [In] wId, hemi_port
 * 	@return int
 */
UINT32 vp_kwrap_gethdmiport(UINT8 wId)
{
	CHECK_SRC_ID(wId);
	return _gVPHdmiPort[wId];
}

/**
* set vp input size information
*
* @param vpSrcId [IN] UINT32
* @param inWin [IN] LX_DE_RECT_T
*
* @return int
*/
int vp_kwrap_setinputsize(UINT32 vpSrcId, LX_DE_RECT_T inSize)
{
	int ret = RET_OK;

	CHECK_SRC_ID(vpSrcId);

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Set wId[%d] Window size_xywh(%d,%d,%d,%d) ===enter===", \
			vpSrcId, inSize.x, inSize.y, inSize.w, inSize.h);

	_gCurVpTiming[vpSrcId].hActive	= 0;
	_gCurVpTiming[vpSrcId].vActive	= 0;

	_gVPInSize[vpSrcId].x = inSize.x;
	_gVPInSize[vpSrcId].y = inSize.y;
	_gVPInSize[vpSrcId].w = inSize.w;
	_gVPInSize[vpSrcId].h = inSize.h;

	_gVPInSizeChg[vpSrcId] = 1;
	_gVPInWinChg[vpSrcId] = UPDATE_INPUT_WIN_COUNTER;

	if (_gVP_DebugPrintOn)
		VP_DEBUG("[VP] Set wId[%d] Window size_xywh(%d,%d,%d,%d)*** Chg Status[%d]", \
			vpSrcId, inSize.x, inSize.y, inSize.w, inSize.h, _gVPInWinChg[vpSrcId]);

	return ret;
}

/**
 * 	set delay buffer number
 *	@param param [In] wId, hemi_port
 * 	@return int
 */
int vp_kwrap_setdelaybuffer(UINT32 vpSrcId, UINT8 ubuffer)
{
	int ret = RET_OK;

	ret = de_kwrap_setdelaybuffer(vpSrcId, ubuffer);

	return ret;
}

/**
 * 	set current sub window mode (PIP/PBP)
 *	@param param [In] wId, hemi_port
 * 	@return int
 */
int vp_kwrap_setsubwinmode(LX_DE_SUB_MODE_T sub_mode)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T cur_inf_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;

	ret = de_kwrap_setsubwinmode(sub_mode);
	_gVP_PicInfo.sub_mode = sub_mode;

	cur_inf_param.win_id =LX_PE_WIN_0;
	/* get pre display info */
#ifdef INCLUDE_KDRV_PE
	ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
	VP_CHECK_CODE( ret != RET_OK, return ret, \
		"[VP %d] vpq_hwrap_getpicdisplayinfo( ) function return error \n", __L__);
	cur_inf_param.info_type = LX_PE_INFO_MISC;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
	cur_inf_param.sub_mode = sub_mode;
	/* set default */
	if (pre_inf_param.sub_mode != cur_inf_param.sub_mode)
	{
		if (_gVP_DebugPrintOn)
		{
			VP_DEBUG("[VP][%s,%d][set]wid:%d,sub_mod:%d\n", \
				__F__, __L__, cur_inf_param.win_id, cur_inf_param.sub_mode);
		}
		/* set disp info */
		ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		VP_CHECK_CODE( ret != RET_OK, return ret, \
			"[VP %d] vpq_hwrap_setpicdisplayinfo( ) function return error \n", __L__);
	}
#endif
	return ret;
}

/**
 * 	set current sub window shaping & original size
 *	@param param [In] wId, hemi_port
 * 	@return int
 */
int vp_kwrap_setsubwinshape(LX_DE_SUB_MGF_SHAPE_T sub_shape, LX_DE_RECT_T orgWin)
{
	int ret = RET_OK;

	ret = de_kwrap_setsubwinshape(sub_shape, orgWin);

	return ret;
}

static int vp_kwrap_checkmuteoff(UINT32 vpSrcId, kwrap_vp_timing_info_t *pBufTiming)
{
	int ret = RET_OK;
	// mute status
	// O18   : 0xC900D6FC
	// M16+ : 0xC900D7EC
	UINT32 mute_address = 0xC900D6FC;
	UINT32 data;
	static UINT32 prev_mute[2];
	UINT32 curr_mute[2];

	if(gpfnCallBackMuteOff == NULL) return RET_OK;
	if(vpSrcId > 1)                 return RET_ERROR;

	if(lx_chip_rev( ) >= LX_CHIP_REV( O18, A0))
	{
		mute_address = 0xC900D6FC;
	}
	else
	{
		mute_address = 0xC900D7EC;
	}
	#ifdef SEE_TV//Need to check
		ret = SYS_IO_ReadRegArray(mute_address,4,&data);
	#else
		KADP_SYS_RegReadSimple(mute_address, &data);
	#endif

	curr_mute[vpSrcId] = (data >> (16*vpSrcId)) & 0xFFFF;

	if(curr_mute[vpSrcId] == 0 && curr_mute[vpSrcId] != prev_mute[vpSrcId])
	{
		gpfnCallBackMuteOff(vpSrcId);
		VP_NOTI("WIN[%d] MUTE_OFF\n", vpSrcId);
	}

	prev_mute[vpSrcId] = curr_mute[vpSrcId];

	return ret;
}

int vp_kwrap_registermuteoffcallback(PFN_VP_NOTIFY_MUTE_OFF_T pfnMuteOffCB)
{
	int ret = RET_OK;

	if(pfnMuteOffCB == NULL)
	{
		gpfnCallBackMuteOff = NULL;
	}
	else
	{
		if (gpfnCallBackMuteOff != NULL)
		{
		VP_NOTI("already registered cb = %p, gpfnCBm = %p\n", pfnMuteOffCB, gpfnCallBackMuteOff);
		ret = RET_ERROR;
		}
		else
		{
		/* register cb */
		gpfnCallBackMuteOff = pfnMuteOffCB;
		VP_NOTI("register cb = %p, gpfnCBm = %p\n", pfnMuteOffCB, gpfnCallBackMuteOff);
		}
	}

	return ret;
}

int vp_kwrap_hsc_enable(int enable)
{
	int ret = RET_OK;
	// hsc_enable
	// O18/M16++ : 0xC9001404[8]
	UINT32 hsc_enable_address = 0xC9001404;
	UINT32 data;

	if(lx_chip_rev( ) < LX_CHIP_REV(M17, C0))
		return RET_ERROR;

	#ifdef SEE_TV//Need to check
		ret = SYS_IO_ReadRegArray(hsc_enable_address,4,&data);
	#else
		KADP_SYS_RegReadSimple(hsc_enable_address, &data);
	#endif

	if(enable)
		data |= 0x00000100;
	else
		data &= 0xFFFFFEFF;

	#ifdef SEE_TV//Need to check
		ret = SYS_IO_WriteRegArray(hsc_enable_address,4,&data);
	#else
		KADP_SYS_RegWriteSimple(hsc_enable_address, data);
	#endif

	return ret;
}
#endif

