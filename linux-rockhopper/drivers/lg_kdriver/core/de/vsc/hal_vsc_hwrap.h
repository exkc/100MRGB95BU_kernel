/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file hal_vsc.h
 *
 *  It is the header file for controling VIDEO function.
 *  The header of VIDEO DDI is controlled by this file.
 *
 *  @author	Lee, Jong-Heon(jongheon.lee@lge.com)
 *  @version	0.1
 *  @date		2011.03.18
 *  @note
 *  @see
 */

/*-----------------------------------------------------------------------------
	Header File Guarder
------------------------------------------------------------------------------*/
#ifndef _HAL_VIDEO_DDI_H_
#define _HAL_VIDEO_DDI_H_

#if 0	//not used
/*-----------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 	File Inclusions
------------------------------------------------------------------------------*/
//#include "branches.h"
#ifndef WIN32_SIM // Modified by dilly97: fix include
#include "hal_hwrap_common.h"
#else
#include "common_win32.h"
#endif
//#include "global_configurations.h"


//#include "dil_vsc.h"

/*-----------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/
#define VIDEO_DDI_RECT_T VIDEO_RECT_T

/**
 * Video Window Rect.
 *
 * @see DDI Implementation Guide
*/
#ifndef VIDEO_WID_T
	typedef enum
	{
		VIDEO_WID_MIN	= 0,				/**< WID min */
		VIDEO_WID_0 	= VIDEO_WID_MIN,	/**< WID main window */
		VIDEO_WID_1,						/**< WID sub window */
		VIDEO_WID_2,
		VIDEO_WID_3,
		VIDEO_WID_MAX	= VIDEO_WID_3,		/**< WID max */
		VIDEO_WID_MAXN, 					/**< WID max number */
	} __VIDEO_WID_T;
#define VIDEO_WID_T __VIDEO_WID_T
#endif
	/**
	 * Video Window Rect.
	 *
	 * @see DDI Implementation Guide
	*/
#ifndef VIDEO_RECT_T
	typedef struct
	{
		UINT16		x;	/**< horizontal Start Position in pixel [0,].*/
		UINT16		y;	/**< vertical	Start Position in pixel [0,].*/
		UINT16		w;	/**< horizontal Size(Width)    in pixel [0,].*/
		UINT16		h;	/**< vertical	Size(Height)   in pixel [0,].*/
	} __VIDEO_RECT_T;
#define VIDEO_RECT_T __VIDEO_RECT_T
#endif

typedef enum VSC_INPUT_TYPE
{
	VSC_INPUTSRC_AVD = 0,
	VSC_INPUTSRC_ADC,
	VSC_INPUTSRC_HDMI,
	VSC_INPUTSRC_VDEC,
	VSC_INPUTSRC_JPEG,
        VSC_INPUTSRC_MAX = VSC_INPUTSRC_JPEG,
	VSC_INPUTSRC_MAXN,
} VSC_INPUT_TYPE_T;

typedef struct VSC_INPUT_SRC_INFO
{
	VSC_INPUT_TYPE_T type;
	UINT8 attr;
	UINT8 resourceIndex;
} VSC_INPUT_SRC_INFO_T;

/**
 * Scaler Output Mode.
 *
 * @see HAL Implementation Guide
*/
typedef enum VSC_OUTPUT_MODE
{
	VSC_OUTPUT_DISPLAY_MODE = 0,
	VSC_OUTPUT_VENC_MODE,
	VSC_OUTPUT_MEMORY_MODE,
	VSC_OUTPUT_AVE_MODE,
	VSC_OUTPUT_MAX = VSC_OUTPUT_AVE_MODE,
	VSC_OUTPUT_MAXN,
} VSC_OUTPUT_MODE_T;

typedef enum
{
        VSC_VIDEO_COLOR_OFF,
        VSC_VIDEO_COLOR_WHITE,
}VSC_VIDEO_COLOR_TYPE_T;

/**
 * Color of Video Window.
 *
 * @see DDI Implementation Guide
*/
typedef enum
{
	VIDEO_DDI_WIN_COLOR_BLACK,		/**< window color black */
	VIDEO_DDI_WIN_COLOR_BLUE,		/**< window color blue */
	VIDEO_DDI_WIN_COLOR_GRAY		/**< window color gray */
} VIDEO_DDI_WIN_COLOR_T;

/**
 * Multi Window Mode.
 *
*/
typedef enum
{
	VIDEO_MULTI_WIN_MODE_MIN = 0,
	VIDEO_MULTI_WIN_MODE_OFF = VIDEO_MULTI_WIN_MODE_MIN,
	VIDEO_MULTI_WIN_MODE_PIP,
	VIDEO_MULTI_WIN_MODE_TRANSCODING,
	VIDEO_MULTI_WIN_MODE_2ND_TV,
	VIDEO_MULTI_WIN_MODE_CAPTURE,
	VIDEO_MULTI_WIN_MODE_MAXN,
} VIDEO_MULTI_WIN_MODE_T;

/**
 * Video Input source Information.
 *
 */
typedef struct VIDEO_SRC_INFO
{
	UINT32	Type:8;		/**< ... */
	UINT32	Index:8;	/**< ... */
	UINT32	Attr:8;		/**< ... */
	UINT32	Resv:8;		/**< ... */
} VIDEO_SRC_INFO_T;

/**
 * Video Pixel format
 *
 */
typedef enum
{
	VIDEO_DDI_PIXEL_FORMAT_RGB10,
	VIDEO_DDI_PIXEL_FORMAT_RGB8,
	VIDEO_DDI_PIXEL_FORMAT_YCBCR444_10,
	VIDEO_DDI_PIXEL_FORMAT_YCBCR444_8,
	VIDEO_DDI_PIXEL_FORMAT_YCBCR422_10,
	VIDEO_DDI_PIXEL_FORMAT_YCBCR422_8,
	VIDEO_DDI_PIXEL_FORMAT_YCBCR420_10,
	VIDEO_DDI_PIXEL_FORMAT_YCBCR420_8,
	VIDEO_DDI_PIXEL_FORMAT_ARGB8,
	VIDEO_DDI_PIXEL_FORMAT_ARGB10,
   	VIDEO_DDI_PIXEL_FORMAT_YCSEPARATED,
}VIDEO_DDI_PIXEL_FORMAT_T;

/**
 * Video Capture Info
 *
 */
typedef struct
{
	UINT16 width;
	UINT16 height;
	VIDEO_DDI_PIXEL_FORMAT_T pixelFormat;
	const UINT8* pData;
	const UINT8* pCbCr;
	UINT16* pScanTypeCapImg; // 0:I, 1:P
}VIDEO_DDI_CAPTURE_INFO_T;

/**
 * HDR Mode Information.
 *
 * @see DDI Implementation Guide
 */
typedef enum {
        VSC_HDR_HDR10,
        VSC_HDR_DOLBY,
        VSC_HDR_VP9,
        VSC_HDR_HLG,
        VSC_HDR_PRIME,
        VSC_HDR_DOLBY_LL,
        VSC_HDR_MAX = VSC_HDR_DOLBY_LL,
        VSC_HDR_MAXN,
}VSC_HDR_TYPE_T;

/*
 * HDR Mode Current Information
 *
 * @see DDI Implementation Guide
 */
typedef struct {
        VIDEO_WID_T ewinId;
        VSC_HDR_TYPE_T eHdrMode;
}VSC_HDR_INFO_T;

/**
 * Video Timing Information.
 *
 * @see DDI Implementation Guide
*/
typedef struct
{
   	SINT32 format;	/**< update by LG */
	UINT16 hFreq;	/**< ... */
	UINT16 vFreq;	/**< ... */
	UINT16 hTotal;	/**< ... */
	UINT16 vTotal;	/**< ... */
	UINT16 hPorch;	/**< ... */
	UINT16 vPorch;	/**< ... */
	VIDEO_RECT_T	active;	/**< ... */
	UINT16 scanType;	/**< ... */
	UINT16 phase;	    /**< ... */  // need to check UINT16
	UINT8  mode;	    /**< update by LG */
//	VFE_AVD_AVDECODER_VIDEO_MODE_T  standard;	/**< for color standard*/ // 2012.10.31 yongsu.yoo change this for Late-return of analog color system
	UINT8  vdLock;	/**< for ATV */
} VIDEO_TIMING_INFO_T;

#if 1
/**
 * pixel grab color.
 *
 * @see DDI Implementation Guide
*/
typedef struct
{
	UINT8 pixelGrabCb;	/**< Cb */
	UINT8 pixelGrabY;	/**< Y */
	UINT8 pixelGrabCr;	/**< CR */
}VIDEO_DDI_PIXEL_GRAB_COLOR_T;

/**
 * pixel grab region.
 *
 * @see DDI Implementation Guide
*/
typedef struct
{
	VIDEO_WID_T wID;	/**< select main or sub window */
	UINT32 pixelGrabX;	/**< x position */
	UINT32 pixelGrabY;	/**< y position */
	UINT32 pixelGrabW;	/**< capture width */
	UINT32 pixelGrabH;	/**< capture h */

	UINT32 realPixelGrabW;	/**< real W in memory */
	UINT32 realPixelGrabH;	/**< real H in memory */
	UINT8 colorSpace;	/**< 0: YUV 1:RGB */
}VIDEO_DDI_PIXEL_GRAB_REGION_T;

/**
 * standard pixel color.
 *
 * @see DDI Implementation Guide
*/
typedef struct
{
	UINT16 pixelStandardCb;	/**< standard pixel color Cb */
	UINT16 pixelStandardY;	/**< standard pixel color Y */
	UINT16 pixelStandardCr;	/**< standard pixel color Cr */
}VIDEO_DDI_PIXEL_STANDARD_COLOR_T;

/**
 * color standard.
 *
 * @see DDI Implementation Guide
*/
typedef enum
{
	VIDEO_DDI_COLOR_STANDARD_YUV = 0,
	VIDEO_DDI_COLOR_STANDARD_RGB,
} VIDEO_DDI_COLOR_STANDARD_T;

/**
 * color standard.
 *
 * @see DDI Implementation Guide
*/
typedef enum
{
	VIDEO_DDI_PIXEL_8BIT = 0,
	VIDEO_DDI_PIXEL_10BIT,
} VIDEO_DDI_PIXEL_COLOR_FORMAT_T;

/**
 * capture location
 *
 * @see DDI Implementation Guide
*/
typedef enum
{
	VIDEO_DDI_SCALER_OUTPUT = 0,
	VIDEO_DDI_DISPLAY_OUTPUT,
}VIDEO_DDI_CAPTURE_PLACE_T;
#endif

/**
 * Video output format type for UD display
 */
typedef struct {
	BOOLEAN isUD;
	UINT16 fr_rate;						///< display frame rate
	UINT16 h_total;						///< pixels per line
	UINT16 v_total;						///< lines per frame
}VIDEO_DDI_DIS_FMT_T;

/**
 * Video UD format
 * 2011.11.08 by daegun.park
 */
typedef enum
{
	UD_MODE_FHD,
	UD_MODE_UD,
	UD_MODE_UD_HALF,
}VIDEO_UD_MODE_T;


/**
 * Video Component Index
 *
 */
typedef enum {
	COMP_INDEX_1 = 0,
	COMP_INDEX_2,
	COMP_INDEX_3,	// 20091111 drmyung : add
	NUM_COMP_INPUTS
} VIDEO_COMP_INDEX_T;

/**
 * Video Input signal source definition.
 *
 */
typedef enum VIDEO_SRC_TYPE
{
	VIDEO_SRC_TV	= 0,	/**< TV Input */
	VIDEO_SRC_SCART,		/**< Scart Input */
	VIDEO_SRC_AV,			/**< AV Input */
	VIDEO_SRC_AUTOAV,		/**< Auto AV(SCART) Input */
	VIDEO_SRC_COMP,			/**< Component(YPbPr) Input */
	VIDEO_SRC_RGB,			/**< RGB Input */
	VIDEO_SRC_HDMI,			/**< HDMI Input */
#ifdef INCLUDE_DVR_READY
	VIDEO_SRC_PLAYHDD,		/**< PVR : Recorded Playback mode */
#endif
	VIDEO_SRC_USB,			/**< ... */
	VIDEO_SRC_BT,			/**< ... */
	VIDEO_SRC_MEDIASHARE,	/**< ... */
	VIDEO_SRC_PICWIZARD,	/**< ... */
	VIDEO_SRC_SUPPORT,		/**< ... */
	VIDEO_SRC_BB,			/**< ... */
	VIDEO_SRC_FLASH,		/**< ... */
	VIDEO_SRC_VCS,			/**< ... */
	VIDEO_SRC_INVALID,		/**< Invalid Source Input */
	VIDEO_SRC_MAX = VIDEO_SRC_INVALID,	/**< MAX Input Number */
} VIDEO_SRC_TYPE_T;

/**
 * TV Src Attribute definition.
 *
 */
typedef enum VIDEO_TV_SRC_ATTR
{
	VIDEO_TV_ATTR_ANALOG = 0,	/**< ... */
	VIDEO_TV_ATTR_DIGITAL		/**< ... */

} VIDEO_TV_SRC_ATTR_T;

/**
 * EMF attribute definitions.
 *
 */
typedef enum VIDEO_EMF_SRC_ATTR
{
	VIDEO_EMF_ATTR_PHOTO_MUSIC		= 0,	/**< ... */
	VIDEO_EMF_ATTR_MOVIE,					/**< ... */
	VIDEO_EMF_ATTR_VCS, 	/**< ... */

} VIDEO_EMF_SRC_ATTR_T;

typedef enum VSC_SUB_MODE{
    VSC_SUB_MODE_NONE = 0,
    VSC_SUB_MODE_PIP,
    VSC_SUB_MODE_PBP,
    VSC_SUB_MODE_RESERVED1,
    VSC_SUB_MODE_RESERVED2,
    VSC_SUB_MODE_MAX = VSC_SUB_MODE_RESERVED2,
    VSC_SUB_MODE_MAXN
} VSC_SUB_MODE_T;

typedef enum VSC_SUB_CONNECT_TYPE{
    VSC_SUB_CONNECT_TYPE_NONE = 0,
    VSC_SUB_CONNECT_TYPE_MIRROR,
    VSC_SUB_CONNECT_TYPE_NON_MIRROR,
    VSC_SUB_CONNECT_TYPE_RESERVED1,
    VSC_SUB_CONNECT_TYPE_RESERVED2,
    VSC_SUB_CONNECT_TYPE_MAX = VSC_SUB_CONNECT_TYPE_RESERVED2,
    VSC_SUB_CONNECT_TYPE_MAXN
} VSC_SUB_CONNECT_TYPE_T;

typedef enum VSC_SUB_MEMORY_USE {
    VSC_SUB_MEMORY_USE_NONE = 0,
    VSC_SUB_MEMORY_USE_SINGLE,
    VSC_SUB_MEMORY_USE_MULTI,
    VSC_SUB_MEMORY_USE_RESERVED1,
    VSC_SUB_MEMORY_USE_RESERVED2,
    VSC_SUB_MEMORY_USE_MAX = VSC_SUB_MEMORY_USE_RESERVED2,
    VSC_SUB_MEMORY_USE_MAXN
} VSC_SUB_MEMORY_USE_T;

typedef enum {
	VSC_MGF_TYPE_CIRCLE = 0,
	VSC_MGF_TYPE_RECTANGLE,
	VSC_MGF_TYPE_MAX = VSC_MGF_TYPE_RECTANGLE,
	VSC_MGF_TYPE_MAXN,
} VSC_SUB_SHAPE_T;

typedef struct 
{	
	UINT8 uZorder; // 0: bottom, 1: bottom+1,..
	UINT8 uAlpha; // 0 ~ 255
} VSC_ZORDER_T;

typedef struct VSC_ACTIVE_VIDEO_WINDOW {
    VIDEO_RECT_T original;
    VIDEO_RECT_T active;
} VSC_ACTIVE_VIDEO_WINDOW_T; 

typedef void (*PFN_VSC_NOTIFY_ACTIVE_VIDEO_WINDOW_T) (VIDEO_WID_T wId, VSC_ACTIVE_VIDEO_WINDOW_T *window);

typedef enum VSC_VDO_PORT
{
    VSC_VDO_PORT_MIN = 0,
    VSC_VDO_PORT_0 = VSC_VDO_PORT_MIN,
    VSC_VDO_PORT_1,
    VSC_VDO_PORT_MAX = VSC_VDO_PORT_1,
    VSC_VDO_PORT_MAXN,
}VSC_VDO_PORT_T;

typedef enum {
    VSC_ROTATE_0,
    VSC_ROTATE_90,
    VSC_ROTATE_180,
    VSC_ROTATE_270
} VSC_ROTATE_T;

typedef void (*PFN_VSC_NOTIFY_MUTE_OFF_T) (VIDEO_WID_T wId);

typedef enum
{
    VIDEO_PATTERN_MUX = 0,
    VIDEO_PATTERN_DI_NR,
    VIDEO_PATTERN_SCALER,
    VIDEO_PATTERN_MEMC,
    VIDEO_PATTERN_DISPLAY,
    VIDEO_PATTERN_RESERVED0,
    VIDEO_PATTERN_RESERVED1,
    VIDEO_PATTERN_RESERVED2,
    VIDEO_PATTERN_RESERVED3,
    VIDEO_PATTERN_MAX,
}VIDEO_PATTERN_LOCATION_T;

typedef struct VSC_SCALER_RATIO
{
    int h_scaleup_ratio;
    int v_scaleup_ratio;
    int h_scaledown_ratio;
    int v_scaledown_ratio;
}VSC_SCALER_RATIO_T;

typedef enum {
    VSC_PATTERN_BLACK,
    VSC_PATTERN_WHITE
} VSC_PATTERN_TYPE_T;

typedef struct VSC_INPUT_REGION
{
    VIDEO_RECT_T  inRegion;  // video input size to set
    VIDEO_RECT_T  originalInput;  // original source resolution
} VSC_INPUT_REGION_T;
typedef enum {
	HAL_VSC_HWRAP_INIT,
	HAL_VSC_HWRAP_UNINIT,
	HAL_VSC_HWRAP_CONNECT,
	HAL_VSC_HWRAP_DISONNECT,
	HAL_VSC_HWRAP_SETWINBLANK,
	HAL_VSC_HWRAP_SETIPOPRGN,
	HAL_VSC_HWRAP_SETWINFRZ,
	HAL_VSC_HWRAP_MAX
}HAL_VSC_HWRAP_DEBUG_FUNCNUM;
/*-----------------------------------------------------------------------------
	Extern Variables & Function Prototype Declarations
------------------------------------------------------------------------------*/
DTV_STATUS_T	hal_vsc_hwrap_initialize(void);
DTV_STATUS_T	hal_vsc_hwrap_Uninitialize(void);
DTV_STATUS_T	hal_vsc_hwrap_open(VIDEO_WID_T wId);
DTV_STATUS_T	hal_vsc_hwrap_close(VIDEO_WID_T wId);
DTV_STATUS_T	hal_vsc_hwrap_connect(VIDEO_WID_T wId, VSC_INPUT_SRC_INFO_T vscInput, VSC_OUTPUT_MODE_T outputmode);
DTV_STATUS_T	hal_vsc_hwrap_disconnect(VIDEO_WID_T wId, VSC_INPUT_SRC_INFO_T vscInput, VSC_OUTPUT_MODE_T outputmode);

DTV_STATUS_T	hal_vsc_hwrap_setwinblank(VIDEO_WID_T wId, BOOLEAN bOnOff, VIDEO_DDI_WIN_COLOR_T color);
DTV_STATUS_T	hal_vsc_hwrap_getinputregion(VIDEO_WID_T wId, VIDEO_RECT_T *pInRegion);
DTV_STATUS_T    hal_vsc_hwrap_setinputregion(VIDEO_WID_T wId, VIDEO_RECT_T inRegion, VIDEO_RECT_T originalInput);
DTV_STATUS_T	hal_vsc_hwrap_getoutputregion(VIDEO_WID_T wId, VIDEO_RECT_T *pOutRegion);
DTV_STATUS_T	hal_vsc_hwrap_setoutputregion(VIDEO_WID_T wId, VIDEO_RECT_T outRegion);
DTV_STATUS_T	hal_vsc_hwrap_setinputoutputregion (VIDEO_WID_T wId, VSC_ROTATE_T rotation, VSC_INPUT_REGION_T *pInputRegion, VIDEO_RECT_T *pOutputRegion);
DTV_STATUS_T    hal_vsc_hwrap_setvencmode (UINT16 frame_rate, UINT16 scan_type);
DTV_STATUS_T	hal_vsc_hwrap_setwinfreeze(VIDEO_WID_T wId, BOOLEAN bOnOff, BOOLEAN bAll); // Add "BOOLEAN bAll" parameter, by choonghoon.park 20170203

DTV_STATUS_T    hal_vsc_hwrap_capturevideoframe(VIDEO_DDI_CAPTURE_PLACE_T place, VIDEO_DDI_CAPTURE_INFO_T* pCaptureInfo);
DTV_STATUS_T    hal_vsc_hwrap_freezevideoframebuffer(BOOLEAN bFreezeOn);
DTV_STATUS_T	hal_vsc_hwrap_readvideoframebuffer(VIDEO_WID_T wId, VIDEO_RECT_T *pIn, VIDEO_DDI_PIXEL_STANDARD_COLOR_T *pRead, VIDEO_DDI_COLOR_STANDARD_T *pcolor_standard, VIDEO_DDI_PIXEL_COLOR_FORMAT_T * pPixelColorFormat);
DTV_STATUS_T	hal_vsc_hwrap_writevideoframebuffer(VIDEO_WID_T wId, VIDEO_RECT_T *pIn, VIDEO_DDI_PIXEL_STANDARD_COLOR_T *pWrite);

DTV_STATUS_T	hal_vsc_hwrap_setrgb444mode(BOOLEAN bOnOff);
DTV_STATUS_T    hal_vsc_hwrap_setadaptivestream(VIDEO_WID_T wId, BOOLEAN bOnOff);
DTV_STATUS_T    hal_vsc_hwrap_setdelaybuffer(VIDEO_WID_T wId, UINT8 ubuffer);
DTV_STATUS_T    hal_vsc_hwrap_setsubwinmodeex(VSC_SUB_MODE_T mode, VSC_SUB_CONNECT_TYPE_T connectType, VSC_SUB_MEMORY_USE_T memoryUse);
DTV_STATUS_T    hal_vsc_hwrap_setsubwinshape(VSC_SUB_SHAPE_T shape, VIDEO_RECT_T rect);
DTV_STATUS_T    hal_vsc_hwrap_setzorder(VSC_ZORDER_T *zOrder, UINT8 uWindowNo);

DTV_STATUS_T	hal_vsc_hwrap_registeractivevideowindowcallback(VIDEO_WID_T wId, PFN_VSC_NOTIFY_ACTIVE_VIDEO_WINDOW_T callback);
DTV_STATUS_T	hal_vsc_hwrap_makecoloredvideo(VSC_VIDEO_COLOR_TYPE_T videoColor);

DTV_STATUS_T    hal_vsc_hwrap_hdr_open(VIDEO_WID_T wId);
DTV_STATUS_T    hal_vsc_hwrap_hdr_close(VIDEO_WID_T wId);
DTV_STATUS_T    hal_vsc_hwrap_hdr_connect(VIDEO_WID_T wId, VSC_HDR_TYPE_T eHdrMode);
DTV_STATUS_T    hal_vsc_hwrap_hdr_disconnect(VIDEO_WID_T wId);

DTV_STATUS_T    hal_vsc_hwrap_vdo_connect(VSC_VDO_PORT_T vdo_port, UINT16 vdec_port);
DTV_STATUS_T    hal_vsc_hwrap_vdo_disconnect(VSC_VDO_PORT_T vdo_port, UINT16 vdec_port);

DTV_STATUS_T    hal_vsc_hwrap_rotatevideo(VIDEO_WID_T wId, VSC_ROTATE_T rotation);
DTV_STATUS_T    hal_vsc_hwrap_registermuteoffcallback(PFN_VSC_NOTIFY_MUTE_OFF_T pfnMuteOffCB);

DTV_STATUS_T    hal_vsc_hwrap_getlimitedwindow(VIDEO_WID_T wId, VSC_SCALER_RATIO_T *scalerRatio);
DTV_STATUS_T    hal_vsc_hwrap_setpattern(BOOLEAN bOnOff, VIDEO_WID_T wId, VIDEO_PATTERN_LOCATION_T pattern_location);
void hal_video_debugmenu (void);

DTV_STATUS_T    hal_vsc_hwrap_setvideolatencypattern (BOOLEAN bOnOff, VSC_PATTERN_TYPE_T bPatternType, VIDEO_RECT_T overlayWindow);

/*-----------------------------------------------------------------------------
	Local Constant Definitions
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	Local Type Definitions
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	Global Type Definitions
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
	Global Variables & Function Prototypes Declarations
------------------------------------------------------------------------------*/
 /*-----------------------------------------------------------------------------
	Local Variables & Function Prototypes Declarations
------------------------------------------------------------------------------*/
#endif

#endif /* _HAL_VIDEO_DDI_H_ */
