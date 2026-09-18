/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file vp_kwrap.h
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     sh.myoung (sh.myoung@lge.com)
 *  @version    1.0
 *  @date       2012-05-01
 *  @note       Additional information.
 *  @note	Mapped to kernel space for SEE TV (harish.singh@lge.com)
 */

#ifndef	_VP_KWRAP_H_
#define	_VP_KWRAP_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_kapi.h"
#include "hdmi_kapi.h"
#include "afe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VP_PRE_ACT_NUM	4

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/* We need to use Error codes for VP */
typedef enum _KWRAP_VP_ERROR_CODES
{
	VP_ERROR_NOT_INITIALIZED,
	VP_ERROR_NULL_ARG,
	VP_ERROR_INVALID_ARG,
	VP_MEM_ALLOCATION_FAILURE,
	VP_ERROR_NONE = 0, //SUCCESS
} kwrap_vp_error_types;

typedef enum
{
	SRC_INPUT_NONE,			///< None input source
	SRC_INPUT_VGA,				///< VGA
	SRC_INPUT_YPBPR,			///< YPbPr
	SRC_INPUT_ATV,				///< ATV
	SRC_INPUT_CVBS,			///< CVBS
	SRC_INPUT_SCART,			///< SCART
	SRC_INPUT_SCART_RGB_BYPASS,	///< SCART RGB Bypass Workaround for H13B0 SCART F/B H/W Bug.
	SRC_INPUT_HDMI,			///< HDMI
	SRC_INPUT_DTV,				///< DTV
	SRC_INPUT_MVI,				///< Media
	SRC_INPUT_JPG,				///< JPEG
	SRC_INPUT_MAX,
}	kwrap_vp_input_src_t;

typedef struct {
	kwrap_vp_input_src_t	Type;   	///< input Source type
	UINT32	Port;					///< input Source port
	UINT32	Attr;					///< attribution port info for External input source
	UINT32	Resv;					///< Reserve parameter
} kwrap_vp_src_info_t;

typedef enum
{
	VP_EXT_2D_FORMAT,					///< 2D format

	//Half format
	VP_EXT_3D_TOPNBOTTOM,				///< top and bottom
	VP_EXT_3D_SIDEBYSIDE,				///< side by side
	VP_EXT_3D_CHECKER_BOARD,			///< check board
	VP_EXT_3D_FRAME_SEQ,				///< frame sequence
	VP_EXT_3D_COLUMN_ALTERNATIVE,		///< column alternate(interleaving) - mpeg
	VP_EXT_3D_LINE_ALTERNATIVE,			///< line alternative half

	//Full format
	VP_EXT_3D_FRAME_PACKING,			///< frame packing
	VP_EXT_3D_FIELD_ALTERNATIVE,		///< field alternate
	VP_EXT_3D_LINE_ALTERNATIVE_FULL,		///<  line alternative full
	VP_EXT_3D_SIDEBYSIDE_FULL,			///< side by side full
	VP_EXT_3D_DUAL,						///< dual stream
	VP_EXT_4K_2K,						///< 4K x 2K format
	VP_EXT_MAX,							///< max number extend info
} kwrap_vp_ext_info_t;

typedef enum
{
	VP_3D_ORDER_RL,	///< R image frist
	VP_3D_ORDER_LR,	///< L image frist
} kwrap_vp_3d_lr_order_t;

typedef enum {
	VP_INTERLACED,		///< interlaced scan
	VP_PROGRESSIVE	///< progressive scan
} kwrap_vp_scan_t;

/**
*	VP Video Timing Information.
*
*/
typedef struct
{
	UINT16				hFreq;		///< horizontal Frequency
	UINT16				vFreq;		///< vertical Frequency

	UINT16				hTotal;		///< horizontal total size
	UINT16				vTotal;		///< vertical total size

	UINT16				hStart;		///< horizontal start position
	UINT16				vStart;		///< vertical start position
	UINT16				hActive;		///< horizontal active size
	UINT16				vActive;		///< vertical active size

	UINT16				scanType;	///< scan type

	UINT16				standard;	///< color standard
	UINT16				vdLock;		///< video lock

	kwrap_vp_ext_info_t		extInfo;		///< extend information for 3D and UD format
	kwrap_vp_3d_lr_order_t	order3D;	///< L or R image first
	UINT32              pixelRepeat;  ///< pixel repetition info.
	UINT32              colordomain;  ///< color domain info.
	UINT32              hdmi444mode;  ///< hdmi 444 mode.
	UINT32	            isDolbyHDR;
	UINT32              isPVOMode;
	UINT32              isHFRMode;
	UINT8               isFreeSyncMode;         ///< AMD FreeSync
	UINT8               isGSyncMode;            ///< NVIdia GSync
	UINT8               isVrrMode;              ///< HDMI2.1 VRR
	UINT8               isFvaMode;              ///< HDMI2.1 FVA
	UINT8               isQmsMode;              ///< HDMI2.1 QMS
	UINT32              qmsTFR;                 ///< HDMI2.1 QMS TFR
	UINT32              qmsBaseRate;            ///< HDMI2.1 QMS base rate
	UINT32              isMConst;               ///< HDMI2.1 VRR
	UINT32              pixelClock;
	UINT32              phyMode;				// 0:3G, 1:6G, 2:FRL 3L3G, 3:3L6G, 4:4L4G, 5:4L8G, 6:4L10G, 7:4L12
	UINT32              isDSC;
	UINT32              isMVI;
	LX_DE_AVI_COLORSPACE_T avi_colorspace;
	UINT32              svp;
	UINT32              cp_streaming;
	UINT32              deepColorMode;          ///< pixel resolution
	UINT32              hdr_type;
} kwrap_vp_timing_info_t;

 /**
 * @brief
 */
typedef enum
{
	VP_CALIB_MODE_COMP		= 0,
	VP_CALIB_MODE_SCARTRGB	= 1,
	VP_CALIB_MODE_RGBPC		= 2,
	VP_CALIB_MODE_AUTO		= 3,
	VP_CALIB_MODE_MAX
}	kwrap_vp_adc_calib_source_t;

/**
 * @brief
 */
typedef struct
{
	kwrap_vp_adc_calib_source_t	calib_src;
	UINT16						red_value;
	UINT16						green_value;
	UINT16						blue_value;
	int							result;
}	kwrap_vp_adc_calib_mode_t;

 /**
  * Mute color
  */
typedef enum
{
	VP_WIN_COLOR_BLACK,		///< black color
	VP_WIN_COLOR_BLUE,		///< blue color
	VP_WIN_COLOR_GRAY,		///< gray color
	VP_WIN_COLOR_MAX			///< max number
}	kwrap_vp_win_color_t;

/**
 * @brief
 *	 - vp cvi input csc info
 */
typedef struct
{
	LX_DE_COLOR_STD_T cStd;			///< color standard
	LX_DE_CVD_COLOR_STD_T cvdStd;	///< cvd color standard
}	kwrap_vp_in_csc_info_t;

/**
 * @brief
 *	 - vp picture info
 */
typedef struct
{
	LX_DE_CVD_COLOR_STD_T	cvd_col_std;				///< cvd color standard
	LX_DE_COLOR_STD_T		cvi_col_std[LX_DE_WIN_MAX];	///< cvi color standard
	LX_DE_COLOR_STD_T		out_col_std;				///< out color standard
	LX_DE_RECT_T			i_win[LX_DE_WIN_MAX];		///< input window
	LX_DE_RECT_T			o_win[LX_DE_WIN_MAX];		///< output window
	BOOLEAN					b_is_dw_md;					///< dual window mode
	UINT32					post_csc_type;				///< post csc type, see PE_KWRAP_POST_CSC_TYPE
	UINT32					pic_src_type[LX_DE_WIN_MAX];///< pic(pe) src type, see LX_PE_SRC_TYPE
	LX_DE_SUB_MODE_T		sub_mode;					///< sub mode
}	kwrap_vp_pic_info_t;

/**
 * @brief
 *	 - vp change info flag
 */
typedef struct
{
	BOOLEAN timingInfoChg;			///< timing change
	BOOLEAN hdmi444modChg;			///< hdmi 444 mode change
	BOOLEAN hdmiDomainChg;			///< hdmi color domain change
	BOOLEAN dispFrRateChg;			///< display frame rate change
}	kwrap_vp_info_chg_flag_t;

/**
 * @brief
 *	 - Multi Window Mode.
 */
typedef enum
{
	KWRAP_VP_MULTI_WIN_MODE_MIN = 0,
	KWRAP_VP_MULTI_WIN_MODE_OFF = KWRAP_VP_MULTI_WIN_MODE_MIN,
	KWRAP_VP_MULTI_WIN_MODE_PIP,
	KWRAP_VP_MULTI_WIN_MODE_MIRROR,
	KWRAP_VP_MULTI_WIN_MODE_TRI,
	KWRAP_VP_MULTI_WIN_MODE_QUAD,
	KWRAP_VP_MULTI_WIN_MODE_TRANSCODING,
	KWRAP_VP_MULTI_WIN_MODE_2ND_TV,
	KWRAP_VP_MULTI_WIN_MODE_CAPTURE,
	KWRAP_VP_MULTI_WIN_MODE_MAXN
} kwrap_vp_multi_win_mode_t;

/**
 * @brief
 *	 - Values need to monitor for any change [As of now for HDMI only]
 */

typedef struct
{
	LX_DE_COLOR_STD_T 		color_std[LX_DE_WIN_MAX];
	LX_DE_HDMI444_MODE_T 	hdmi_444_Mode;
	LX_DE_SCALER_CSAMPLE_T	hdmiScaler[LX_DE_WIN_MAX];
	UINT8 hdmi_sampling;
} kwrap_vp_chg_info_t;

/**
 * @brief
 *	 - Information for frame rate configuration
 */

typedef struct
{
	BOOLEAN isForceFreeRun;
	UINT16 frameRate;
} kwrap_vp_fr_info_t;

/**
 * @brief
 *	 - Structure to define HDMI colorimetry information [colorymetry, colorstd, scaler]
 */
typedef struct
{
	LX_HDMI_COLOR_STATUS_T hdmi_colormetry;
	LX_DE_COLOR_STD_T color;
	LX_DE_SCALER_CSAMPLE_T scaler;
} kwrap_vp_hdmi_color_map_t;

/**
 * @brief
 *	 - Structure to define mapping between kwrap_vp_input_src_t to LX_DE_IN_SRC_T
 */
typedef struct
{
	kwrap_vp_input_src_t vpSrcType;
	LX_DE_IN_SRC_T deSrcType;
} kwrap_vp_src_de_map_t;

typedef void (*PFN_VP_NOTIFY_MUTE_OFF_T) (UINT32 wId);

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int vp_kwrap_initpicinfo(void);
int vp_kwrap_getpicsrcinfo(UINT32 srcId, LX_DE_IN_SRC_T input_src_info);
int vp_kwrap_setinputwin(UINT32 vpSrcId, LX_DE_RECT_T inWin);
int vp_kwrap_setoutwin(UINT32 vpSrcId, LX_DE_RECT_T outWin);
int vp_kwrap_setinputcsc(UINT32 vpSrcId, const kwrap_vp_src_info_t *src_info, const LX_DE_CVI_SRC_TYPE_T *cviInfo);
int vp_kwrap_updateinputcschistory(int win);
int vp_kwrap_checktimingchangeforcsc(UINT32 vpSrcId);
int vp_kwrap_setpicformatinfo(UINT32 vpSrcId, const kwrap_vp_timing_info_t *timing, const LX_DE_CVI_SRC_TYPE_T *cviInfo);

int vp_kwrap_readtiminginfo_frm_cvd(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_readtiminginfo_frm_adc(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_readtiminginfo_frm_vdec(kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_readtiminginfo_frm_hdmi(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc,  kwrap_vp_timing_info_t *bufTiming);

int vp_kwrap_adc_calibration_otp_write(int opt_write_enable);

#if 0	//not used
int vp_kwrap_open(void);
int vp_kwrap_initialize(void);
int vp_kwrap_uninitialize(void);
int vp_kwrap_uninitpicinfo(void);
BOOLEAN vp_kwrap_isinitialized(void);
BOOLEAN vp_kwrap_ismuteon(UINT32 vpSrcId);
int vp_kwrap_setwinblank(UINT32 vpSrcId, BOOLEAN bOnOff, kwrap_vp_win_color_t color, UINT32 type);

int vp_kwrap_setinputsrc(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo);
int vp_kwrap_getinputsrccfg(UINT32 vpSrcId,kwrap_vp_src_info_t *pVpSrcCfg);
int vp_kwrap_setexternalinputsrc(UINT32 vpSrcId, kwrap_vp_src_info_t *pVpSrcInfo);
int vp_kwrap_getcvicfg(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t bufTiming, LX_DE_CVI_SRC_TYPE_T *cviInfo );
int vp_kwrap_setcvicfg(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, LX_DE_CVI_SRC_TYPE_T cviInfo );

int vp_kwrap_resettiminginfo(UINT32 vpSrcId);
int vp_kwrap_readtiminginfo(UINT32 vpSrcId, kwrap_vp_src_info_t vpInputSrc, kwrap_vp_timing_info_t *bufTiming);
int vp_kwrap_gettiminginfo(UINT32 vpSrcId, kwrap_vp_timing_info_t *pVpTimingInfo);

int vp_kwrap_setpostcsc(UINT32 vpSrcId, LX_DE_COLOR_STD_T cStd);
int vp_kwrap_getpicinfo(kwrap_vp_pic_info_t *pInfo);

int vp_kwrap_setfrrate(BOOLEAN isForceFreeRun, UINT16 frameRate);
int vp_kwrap_setoperation(UINT32 vpSrcId, LX_DE_OPERATION_CTRL_T *param);
int vp_kwrap_setsuboperation(LX_DE_SUB_OPERATION_CTRL_T *param);

int vp_kwrap_thread(void);
void	vp_kwrap_debug_test (void);

int vp_kwrap_vertical_reverse(UINT8 mode);
int vp_kwrap_setvcroutsrc(kwrap_vp_input_src_t vpInputSrc, kwrap_vp_input_src_t vpInputSrc_sub, int denc_on_off);

int vp_kwrap_adc_calibration(kwrap_vp_adc_calib_mode_t *pAdc_calib_mode);

int vp_kwrap_getinputwin(UINT32 vpSrcId, LX_DE_RECT_T *pInWin);
int vp_kwrap_getoutwin(UINT32 vpSrcId, LX_DE_RECT_T *pOutWin);
int vp_kwrap_setwindowinfo(LX_DE_WIN_INFO_T *pWinInfo);

int vp_kwrap_setactfmtdetect(LX_DE_ACT_FORMAT_T param);
int vp_kwrap_setquadwinmode( UINT16 bOnOff );
int vp_kwrap_sethdmiport(UINT8 wId, UINT32 hdmi_port);
UINT32 vp_kwrap_gethdmiport(UINT8 wId);
int vp_kwrap_setinputsize(UINT32 vpSrcId, LX_DE_RECT_T inSize);
int vp_kwrap_setdelaybuffer(UINT32 vpSrcId, UINT8 ubuffer);
int vp_kwrap_setsubwinmode(LX_DE_SUB_MODE_T sub_mode);
int vp_kwrap_setsubwinshape(LX_DE_SUB_MGF_SHAPE_T sub_shape, LX_DE_RECT_T orgWin);

int vp_kwrap_setmultiwinenable(BOOLEAN isEnable);

int vp_kwrap_registermuteoffcallback(PFN_VP_NOTIFY_MUTE_OFF_T pfnMuteOffCB);
int vp_kwrap_setvdoconnectinfo(UINT32 vpSrcId, UINT32 port, BOOLEAN connect);
int vp_kwrap_hsc_enable(int enable);
#endif
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

