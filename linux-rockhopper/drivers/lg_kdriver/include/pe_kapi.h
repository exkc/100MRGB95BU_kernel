/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_kapi.h
 *
 *  application interface header for picture enhance modules.
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

#ifndef	_PE_KAPI_H_
#define	_PE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#ifndef USE_XTENSA
#include "base_types.h"
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#ifndef CONFIG_LX_O26_CHIP_FIRMWARE
#define CONFIG_LX_O26_CHIP_FIRMWARE     0
#endif
#ifndef CONFIG_LX_O24_CHIP_FIRMWARE
#define CONFIG_LX_O24_CHIP_FIRMWARE     0
#endif
#ifndef CONFIG_LX_M23_CHIP_FIRMWARE
#define CONFIG_LX_M23_CHIP_FIRMWARE     0
#endif
#ifndef CONFIG_LX_O22_CHIP_FIRMWARE
#define CONFIG_LX_O22_CHIP_FIRMWARE     0
#endif
#ifndef CONFIG_LX_E60_CHIP_FIRMWARE
#define CONFIG_LX_E60_CHIP_FIRMWARE     0
#endif
#ifndef CONFIG_LX_O20_CHIP_FIRMWARE
#define CONFIG_LX_O20_CHIP_FIRMWARE     0
#endif

#define	PE_IOC_MAGIC		'a'
#define PE_IOC_MAXNR		100

#define LX_PE_CMG_TBLPOINT			8
#define LX_PE_CMG_REGION_MAX		15
#define LX_PE_CMG_REGION_NUM		(LX_PE_CMG_REGION_MAX+1)
#define LX_PE_CMG_DELTANUM			6
#define LX_PE_CMG_DELTA_SETNUM		2

#define PE_NUM_OF_CSC_COEF	9
#define PE_NUM_OF_CSC_OFST	6

/* if defined, for extend winid */
#define PE_EXTEND_WINID

/* define for DRC*/
#define LX_PE_CM_GLOBAL_POINT		4
#define LX_PE_CM_LOCAL_POINT		6
#define LX_PE_CM_LOCAL_CURVE		17
#define LX_PE_CM_FREE_POINT			6
#define LX_PE_CM_LOCAL_CURVE_FW		6
#define LX_PE_CM_LOCAL_CURVE_FW2	11

#define PE_SUPPORT_EXT_INNER_PATTERN
#define PE_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE 17

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_IOWR_PKT					_IOWR(PE_IOC_MAGIC, 0, LX_PE_PKT_T)
#define PE_IOWR_TEST_CMD			_IOWR(PE_IOC_MAGIC, 1, LX_PE_TEST_CMD_T)

#define PE_ITEM_PKTRW(_str)			PE_PKTRW_##_str
#define PE_ITEM_PKTMODL(_str)		PE_PKTMODL_##_str
#define PE_ITEM_PKTFUNC(_str)		PE_PKTFUNC_##_str

#define PE_PKTINFO_RWTYPE_POS		24
#define PE_PKTINFO_RWTYPE_BITS		0x000000ff
#define PE_PKTINFO_MODLTYPE_POS		16
#define PE_PKTINFO_MODLTYPE_BITS	0x000000ff
#define PE_PKTINFO_FUNCTYPE_POS		0
#define PE_PKTINFO_FUNCTYPE_BITS	0x0000ffff

#define PE_PKTINFO_RWTYPE_MAXNUM	PE_PKTINFO_RWTYPE_BITS
#define PE_PKTINFO_MODLTYPE_MAXNUM	PE_PKTINFO_MODLTYPE_BITS
#define PE_PKTINFO_FUNCTYPE_MAXNUM	PE_PKTINFO_FUNCTYPE_BITS

#define PE_LSHIFT_DATA(_val, _bits, _pos)	(((_val)&(_bits))<<(_pos))
#define PE_DATA_MASK(_bits, _pos)			((_bits)<<(_pos))
#define PE_RSHIFT_DATA(_val, _bits, _pos)	(((_val)&PE_DATA_MASK((_bits),(_pos)))>>(_pos))

#define PE_SET_PKTINFO_RWTYPE(_info,_type)	\
	_info = (( (_info) & ~(PE_DATA_MASK(PE_PKTINFO_RWTYPE_BITS,PE_PKTINFO_RWTYPE_POS)) ) \
			| (PE_LSHIFT_DATA(_type,PE_PKTINFO_RWTYPE_BITS,PE_PKTINFO_RWTYPE_POS)))
#define PE_GET_PKTINFO_RWTYPE(_info)	PE_RSHIFT_DATA(_info, PE_PKTINFO_RWTYPE_BITS, PE_PKTINFO_RWTYPE_POS)

#define PE_SET_PKTINFO_MODLTYPE(_info,_type)	\
	_info = (( (_info) & ~(PE_DATA_MASK(PE_PKTINFO_MODLTYPE_BITS,PE_PKTINFO_MODLTYPE_POS)) ) \
			| (PE_LSHIFT_DATA(_type,PE_PKTINFO_MODLTYPE_BITS,PE_PKTINFO_MODLTYPE_POS)))
#define PE_GET_PKTINFO_MODLTYPE(_info)	PE_RSHIFT_DATA(_info, PE_PKTINFO_MODLTYPE_BITS, PE_PKTINFO_MODLTYPE_POS)

#define PE_SET_PKTINFO_FUNCTYPE(_info,_type)	\
	_info = (( (_info) & ~(PE_DATA_MASK(PE_PKTINFO_FUNCTYPE_BITS,PE_PKTINFO_FUNCTYPE_POS)) ) \
			| (PE_LSHIFT_DATA(_type,PE_PKTINFO_FUNCTYPE_BITS,PE_PKTINFO_FUNCTYPE_POS)))
#define PE_GET_PKTINFO_FUNCTYPE(_info)	PE_RSHIFT_DATA(_info, PE_PKTINFO_FUNCTYPE_BITS, PE_PKTINFO_FUNCTYPE_POS)

#if 0
/**
* temporally define v4l2 CID for ?LGSR
*/
#define V4L2_CID_EXT_TMP_LGSR_BASE (V4L2_CID_USER_EXT_PQ_BASE + 0x500)
#define V4L2_CID_EXT_TMP_LGSR_UI_ONOFF (V4L2_CID_EXT_TMP_LGSR_BASE + 0)
#define V4L2_CID_EXT_TMP_LGSR_DDR_ADDR (V4L2_CID_EXT_TMP_LGSR_BASE + 1)
#define V4L2_CID_EXT_TMP_LGSR_DDR_DOWNLOAD_DONE (V4L2_CID_EXT_TMP_LGSR_BASE + 2)
#define V4L2_CID_EXT_TMP_LGSR_SRSQM (V4L2_CID_EXT_TMP_LGSR_BASE + 3)
#define V4L2_CID_EXT_TMP_LGSR_CROP_POSITION (V4L2_CID_EXT_TMP_LGSR_BASE + 4)
#define V4L2_CID_EXT_TMP_LGSR_TRA_HALT (V4L2_CID_EXT_TMP_LGSR_BASE + 5)
#define V4L2_CID_EXT_TMP_LGSR_TRA_RUN (V4L2_CID_EXT_TMP_LGSR_BASE + 6)
#define V4L2_CID_EXT_TMP_LGSR_USER_READY (V4L2_CID_EXT_TMP_LGSR_BASE + 7)
#define V4L2_CID_EXT_TMP_LGSR_LNE_STATUS (V4L2_CID_EXT_TMP_LGSR_BASE + 8)
#define V4L2_CID_EXT_TMP_LGSR_TRA_STATUS (V4L2_CID_EXT_TMP_LGSR_BASE + 9)
#define V4L2_CID_EXT_TMP_LGSR_VALID_RUN (V4L2_CID_EXT_TMP_LGSR_BASE + 10)
#define V4L2_CID_EXT_TMP_LGSR_DEMO_MODE (V4L2_CID_EXT_TMP_LGSR_BASE + 11)
#define V4L2_CID_EXT_TMP_LGSR_ACCL_SRSQM (V4L2_CID_EXT_TMP_LGSR_BASE + 12)
#define V4L2_CID_EXT_TMP_LGSR_ACCL_TRA (V4L2_CID_EXT_TMP_LGSR_BASE + 13)
#define V4L2_CID_EXT_TMP_LGSR_RESUME_INIT (V4L2_CID_EXT_TMP_LGSR_BASE + 14)

#endif

#define V4L2_EXT_DEV_NO_LGSR     241
#define V4L2_CID_EXT_LGSR_BASE 0x983E00
#define V4L2_CID_EXT_LGSR_UI_ONOFF 			(V4L2_CID_EXT_LGSR_BASE + 0)
#define V4L2_CID_EXT_LGSR_DDR_ADDR 			(V4L2_CID_EXT_LGSR_BASE + 1)
#define V4L2_CID_EXT_LGSR_DDR_DOWNLOAD_DONE (V4L2_CID_EXT_LGSR_BASE + 2)
#define V4L2_CID_EXT_LGSR_SRSQM 			(V4L2_CID_EXT_LGSR_BASE + 3)
#define V4L2_CID_EXT_LGSR_CROP_POSITION 	(V4L2_CID_EXT_LGSR_BASE + 4)
#define V4L2_CID_EXT_LGSR_TRA_HALT 			(V4L2_CID_EXT_LGSR_BASE + 5)
#define V4L2_CID_EXT_LGSR_TRA_RUN 			(V4L2_CID_EXT_LGSR_BASE + 6)
#define V4L2_CID_EXT_LGSR_USER_READY 		(V4L2_CID_EXT_LGSR_BASE + 7)
#define V4L2_CID_EXT_LGSR_LNE_STATUS 		(V4L2_CID_EXT_LGSR_BASE + 8)
#define V4L2_CID_EXT_LGSR_TRA_STATUS 		(V4L2_CID_EXT_LGSR_BASE + 9)
#define V4L2_CID_EXT_LGSR_VALID_RUN 		(V4L2_CID_EXT_LGSR_BASE + 10)
#define V4L2_CID_EXT_LGSR_DEMO_MODE 		(V4L2_CID_EXT_LGSR_BASE + 11)
#define V4L2_CID_EXT_LGSR_ACCL_SRSQM 		(V4L2_CID_EXT_LGSR_BASE + 12)
#define V4L2_CID_EXT_LGSR_ACCL_TRA 			(V4L2_CID_EXT_LGSR_BASE + 13)
#define V4L2_CID_EXT_LGSR_RESUME_STATUS		(V4L2_CID_EXT_LGSR_BASE + 14)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	int cfg;
	int state;//-1:ng,0:ok,1:busy
	int size;
	union
	{
		char *cmd;
		UINT32 compat_cmd;
		UINT64 sizer;
	};
} LX_PE_TEST_CMD_T;

/**
 *	pe window index enumeration
 */
typedef enum
{
	LX_PE_WIN_0 = 0,				///< window 0
	LX_PE_WIN_1,					///< window 1
	#ifdef PE_EXTEND_WINID
	LX_PE_WIN_2,					///< window 2
	LX_PE_WIN_3,					///< window 3
	#endif

	LX_PE_WIN_ALL,					///< all window
	LX_PE_WIN_NUM = LX_PE_WIN_ALL,	///< number of windows
}
LX_PE_WIN_ID;

/**
 *	pe externel chip window index enumeration
 */
typedef enum
{
	LX_PE_EXTRN_CHIP_WIN_0 = 0xf0,			///< window 0
	LX_PE_EXTRN_CHIP_WIN_1,					///< window 1
	LX_PE_WIN_EXTRN_CHIP_2,					///< window 2
	LX_PE_WIN_EXTRN_CHIP_3,					///< window 3

	LX_PE_WIN_EXTRN_CHIP_ALL,								///< all window
	LX_PE_WIN_EXTRN_CHIP_NUM = LX_PE_WIN_EXTRN_CHIP_ALL,	///< number of windows
}
LX_PE_EXTRN_CHIP_WIN_ID;


/**
 *	pe debug type enumeration
 */
typedef enum
{
	LX_PE_DBG_NONE		= 0x0,	///< set nothing, reserved
	LX_PE_DBG_LV		= 0x1,	///< debug print level on, off
	LX_PE_DBG_BY		= 0x2,	///< bypass mode on, off
	LX_PE_DBG_FW		= 0x4,	///< fw ctrl on, off
	LX_PE_DBG_ALL		= LX_PE_DBG_LV|LX_PE_DBG_BY|LX_PE_DBG_FW	///< set all
}
LX_PE_DBG_TYPE;

/**
 *	pe level type enumeration
 */
typedef enum
{
	LX_PE_LEVEL_MOTION		= 0x1,	///< select only motion level
	LX_PE_LEVEL_NOISE		= 0x2,	///< select only noise level
	LX_PE_LEVEL_PEAKPOS		= 0x4,	///< select only peak pos level
	LX_PE_LEVEL_ALL			= 0x7	///< set all
}
LX_PE_LEVEL_TYPE;

/**
 *	pe source type enumeration
 */
typedef enum
{
	LX_PE_SRC_DTV = 0,		///< digital
	LX_PE_SRC_ATV,			///< atv
	LX_PE_SRC_CVBS,			///< cvbs, s-video
	LX_PE_SRC_SCART,		///< scart
	LX_PE_SRC_COMP,			///< component
	LX_PE_SRC_RGBPC,		///< rgb-pc
	LX_PE_SRC_HDMI,			///< hdmi
	LX_PE_SRC_NUM			///< max num
}
LX_PE_SRC_TYPE;

/**
 *	pe format type enumeration
 */
typedef enum
{
	LX_PE_FMT_SD = 0,		///< sd  input, hor size ~1023
	LX_PE_FMT_HD,			///< hd  input, hor size 1024~2000
	LX_PE_FMT_UHD,			///< uhd input, hor size 2001 ~
	LX_PE_FMT_UHD_8K,		///< 8k uhd input, hor size 4096 ~, ver 2160 ~
	LX_PE_FMT_NUM			///< max num
}
LX_PE_FMT_TYPE;

/**
 *	pe color standard type enumeration
 */
typedef enum
{
	LX_PE_CSTD_NTSC,		///< ntsc
	LX_PE_CSTD_PAL,			///< pal
	LX_PE_CSTD_SECAM,		///< secam
	LX_PE_CSTD_NUM			///< max num
}
LX_PE_CSTD_TYPE;

/**
 *	pe hdmi type enumeration
 */
typedef enum
{
	LX_PE_HDMI_TV = 0,		///< hdmi tv
	LX_PE_HDMI_PC,			///< hdmi pc
	LX_PE_HDMI_NUM			///< max num
}
LX_PE_HDMI_TYPE;

/**
 *	pe scart type enumeration
 */
typedef enum
{
	LX_PE_SCART_AV = 0,		///< scart av
	LX_PE_SCART_RGB,		///< scart rgb
	LX_PE_SCART_NUM			///< max num
}
LX_PE_SCART_TYPE;

/**
 *	pe frame rate type enumeration
 */
typedef enum
{
	LX_PE_FR_60HZ = 0,		///< frame rate 60hz,30hz,24hz
	LX_PE_FR_50HZ,			///< frame rate 50hz,25hz
	LX_PE_FR_NUM			///< max num
}
LX_PE_FR_TYPE;

/**
 *	pe output type enumeration
 *  - causion : keep the category(run, ud, 3d, pip)
 */
typedef enum
{
	LX_PE_OUT_2D = 0,		///< run mode, single normal
	LX_PE_OUT_3D_2D,		///< run mode, 3d to 2d
	LX_PE_OUT_2D_3D,		///< run mode, 2d to 3d
	LX_PE_OUT_UD,			///< ud mode, ud
	LX_PE_OUT_TB,			///< 3d mode, top and bottom
	LX_PE_OUT_SS,			///< 3d mode, side by side
	LX_PE_OUT_FS,			///< 3d mode, frame sequential
	LX_PE_OUT_LA,			///< 3d mode, line alternative
	LX_PE_OUT_DUAL_TB,		///< 3d mode, dual screen Top n Bottom
	LX_PE_OUT_DUAL_SS,		///< 3d mode, dual screen Side by Side
	LX_PE_OUT_DUAL_FULL,	///< 3d mode, dual screen Full
	LX_PE_OUT_PIP,			///< pip mode, pip screen
	LX_PE_OUT_NUM			///< max num
}
LX_PE_OUT_TYPE;

/**
 *	pe scan type enumeration
 */
typedef enum
{
	LX_PE_SCAN_INTERLACE = 0,	///< scan type interlace
	LX_PE_SCAN_PROGRESS,		///< scan type progress
	LX_PE_SCAN_NUM				///< max num
}
LX_PE_SCAN_TYPE;

/**
 *	pe dtv play type enumeration
 */
typedef enum
{
	LX_PE_DTV_NORMAL = 0,	///< dtv type normal
	LX_PE_DTV_FILEPLAY,		///< dtv type fileplay
	LX_PE_DTV_HDDPLAY,		///< dtv type hddplay
	LX_PE_DTV_PHOTOPLAY,	///< dtv type photoplay
	LX_PE_DTV_TESTPIC,		///< dtv type test picture
	LX_PE_DTV_CAMERA,		///< dtv type camera
	LX_PE_DTV_INVALID,		///< dtv type invalid, not dtv
	LX_PE_DTV_NUM			///< max num
}
LX_PE_DTV_TYPE;

/**
 *	pe hdd src type enumeration
 */
typedef enum
{
	LX_PE_HDD_SRC_DTV = 0,		///< hdd src dtv
	LX_PE_HDD_SRC_ATV60,		///< hdd src atv 60
	LX_PE_HDD_SRC_ATV50,		///< hdd src atv 50
	LX_PE_HDD_SRC_AV60,			///< hdd src av 60
	LX_PE_HDD_SRC_AV50,			///< hdd src av 50
	LX_PE_HDD_SRC_SCARTRGB,		///< hdd src scart rgb
	LX_PE_HDD_SRC_INVALID,		///< hdd src invalid, not hdd
	LX_PE_HDD_SRC_NUM			///< max num
}
LX_PE_HDD_SRC_TYPE;

/**
 * pe 3D formatter image format parameter.
 * see LX_3D_IMG_FMT_IN_T
 */
typedef enum
{
	LX_PE_3D_IN_TB = 0,		///< top and bottom
	LX_PE_3D_IN_SS,			///< side by side
	LX_PE_3D_IN_QC,			///< quincunx
	LX_PE_3D_IN_CB,			///< check board
	LX_PE_3D_IN_FP,			///< frame packing
	LX_PE_3D_IN_FPI,		///< frame packing interlace
	LX_PE_3D_IN_FA,			///< field alternate
	LX_PE_3D_IN_FS,			///< frame sequence
	LX_PE_3D_IN_LA,			///< line alternate
	LX_PE_3D_IN_SSF,		///< side by side full
	LX_PE_3D_IN_DUAL,		///< dual HD
	LX_PE_3D_IN_CA,			///< column alternate
	LX_PE_3D_IN_LAH,		///< line alternate half
	LX_PE_3D_IN_NUM			///< max number
}
LX_PE_3D_IN_TYPE;

/**
 *	pe dynamic contrast enhancement color domain enumeration
 */
typedef enum
{
	LX_PE_YC_DOMAIN = 0,	///< yc domain
	LX_PE_HSV_DOMAIN,		///< hsv domain
	LX_PE_KTD_DOMAIN,		///< ktd domain
	LX_PE_DOMAIN_NUM		///< max num
}
LX_PE_COLOR_DOMAIN;

/**
 *	pe post csc type enumeration
 */
typedef enum
{
	LX_PE_POST_CSC_BYPASS = 0,	///< bypass
	LX_PE_POST_CSC_Y709_EXPEND,	///< ycbcr709 to gbr expend
	LX_PE_POST_CSC_Y709_LINEAR,	///< ycbcr709 to gbr linear
	LX_PE_POST_CSC_Y601_EXPEND,	///< ycbcr601 to gbr expend
	LX_PE_POST_CSC_Y601_LINEAR,	///< ycbcr601 to gbr linear
	LX_PE_POST_CSC_2020_NCL_EX,	///< ycbcr2020 to gbr expend(NCL)
	LX_PE_POST_CSC_2020_NCL_LI,	///< ycbcr2020 to gbr linear(NCL)
	LX_PE_POST_CSC_2020_CL_EXP,	///< ycbcr2020 to gbr expend(CL)
	LX_PE_POST_CSC_2020_CL_LIN,	///< ycbcr2020 to gbr linear(CL)
	LX_PE_POST_CSC_YGBR_INVERS,	///< ycbcr to gbr inverse
	LX_PE_POST_CSC_NUM			///< max num
}
LX_PE_POST_CSC_TYPE;

/**
 *	pe hdr csc type enumeration
 */
typedef enum
{
	LX_PE_HDR_CSC_NONE = 0,			///< none
	LX_PE_HDR_CSC_BYPASS,			///< bypass
	LX_PE_HDR_CSC_DEFAULT,			///< default
	LX_PE_HDR_CSC_DEFAULT1,			///< default1
	LX_PE_HDR_CSC_MANUAL,			///< manual
	LX_PE_HDR_CSC_Y709_GBR_LIN,		///< ycbcr709 to gbr linear
	LX_PE_HDR_CSC_Y709_GBR_EXP,		///< ycbcr709 to gbr expend
	LX_PE_HDR_CSC_2020_GBR_EXP,		///< ycbcr2020 to gbr expend
	LX_PE_HDR_CSC_GBR_Y709_LIN,		///< gbr to ycbcr709 linear
	LX_PE_HDR_CSC_GBR_Y709_LIM,		///< gbr to ycbcr709 limit
	LX_PE_HDR_CSC_GBR_2020_LIM,		///< gbr to ycbcr2020 limit
	LX_PE_HDR_CSC_NUM				///< max num
}
LX_PE_HDR_CSC_TYPE;

/**
 *	pe info type enumeration
 */
typedef enum
{
	LX_PE_INFO_NONE = 0,			///< none
	LX_PE_INFO_DEFAULT,				///< bypass
	LX_PE_INFO_PQ_MODE,			///< default1
	LX_PE_INFO_IN_WIN,			///< manual
	LX_PE_INFO_OUT_WIN,			///< manual
	LX_PE_INFO_PIC_FORMAT,			///< manual
	LX_PE_INFO_PIC_OPER,			///< manual
	LX_PE_INFO_MODE,			///< default
	LX_PE_INFO_MISC,			///< act_fmt, mul_win, sub_mode
	LX_PE_INFO_ZORDER,			///< act_fmt, mul_win, sub_mode
	LX_PE_INFO_NUM				///<set all member
}
LX_PE_INFO_TYPE;


/**
 *	packet type descripter for read, write, init
 */
typedef enum
{
	PE_ITEM_PKTRW(INIT)	= 0,	///< init type
	PE_ITEM_PKTRW(SET)	= 1,	///< set type
	PE_ITEM_PKTRW(GET)	= 2,	///< get type
	PE_ITEM_PKTRW(NUM),			///< rw type number
	PE_ITEM_PKTRW(MAX)	= PE_PKTINFO_RWTYPE_MAXNUM	///< max
}
LX_PE_PKT_RWTYPE;

/**
 *	packet type descripter for pe modules
 */
typedef enum
{
	PE_ITEM_PKTMODL(INIT)		= 0,	///< using init module
	PE_ITEM_PKTMODL(DEFAULT)	= 1,	///< set default settings on each module
	PE_ITEM_PKTMODL(DBG)		= 2,	///< set debug settings on each module
	PE_ITEM_PKTMODL(CMN)		= 3,	///< using common module
	PE_ITEM_PKTMODL(CSC)		= 4,	///< using csc module
	PE_ITEM_PKTMODL(CMG)		= 5,	///< using color manege module
	PE_ITEM_PKTMODL(NRD)		= 6,	///< using noise reduction module
	PE_ITEM_PKTMODL(DNT)		= 7,	///< using deinterlacer module
	PE_ITEM_PKTMODL(SHP)		= 8,	///< using sharpness module
	PE_ITEM_PKTMODL(CCM)		= 9,	///< using color correction module
	PE_ITEM_PKTMODL(DCM)		= 10,	///< using dynamic contrast module
	PE_ITEM_PKTMODL(WIN)		= 11,	///< using window control module
	PE_ITEM_PKTMODL(ETC)		= 12,	///< using etc(misc) control module
	PE_ITEM_PKTMODL(HST)		= 13,	///< using histogram module
	PE_ITEM_PKTMODL(HDR)		= 14,	///< using hdr module
	PE_ITEM_PKTMODL(NUM),				///< module type number
	PE_ITEM_PKTMODL(MAX)		= PE_PKTINFO_MODLTYPE_MAXNUM	///< max
}
LX_PE_PKT_MODLTYPE;


//Each category might have maximum 16 codes [Cyclomatic complexity of function must be less then 10 but as of now let's make it less then 20]
//because each function can be used to handle a category
#define LX_PE_INIT_START_CODE		0x0100 					//[256-511]
#define LX_PE_CMN_START_CODE		0x0200 					//[512-767]
#define LX_PE_CSC_START_CODE		0x0300 					//[768-1023]
#define LX_PE_CMG_START_CODE		0x0400   				//[1024-1279]
#define LX_PE_NRD_DNR_START_CODE	0x0500 //DNR				//[1280-1535]
#define LX_PE_NRD_TNR_START_CODE	0x0600 //TNR				//[1536-1791]
#define LX_PE_DNT_START_CODE		0x0700					//[1792-2047]
#define LX_PE_SHP_RE_START_CODE		0x0800 // [RE/SC/DE/EE]	//[2048-2303]
#define LX_PE_SHP_SR_START_CODE 	0x0900 //SR				//[2304-2559]
#define LX_PE_CCM_START_CODE		0x0A00					//[2560-2815]
#define LX_PE_DCM_START_CODE		0x0B00					//[2816-3071]
#define LX_PE_MISC_START_CODE		0x0C00					//[3072-3327]
#define LX_PE_HST_START_CODE		0x0D00					//[3328-3583]
#define LX_PE_HDR_START_CODE		0x0E00					//[3584-3839]

/**
 *	packet type descripter for functions
 */
typedef enum
{
	PE_ITEM_PKTFUNC(LX_PE_INIT_SETTINS_T)		= LX_PE_INIT_START_CODE,	///< using struct LX_PE_INIT_SETTINS_T
	PE_ITEM_PKTFUNC(LX_PE_DEFAULT_SETTINGS_T)	= LX_PE_INIT_START_CODE+1,	///< using struct LX_PE_DEFAULT_SETTINGS_T
	PE_ITEM_PKTFUNC(LX_PE_DBG_SETTINGS_T)		= LX_PE_INIT_START_CODE+2,	///< using struct LX_PE_DBG_SETTINGS_T

	PE_ITEM_PKTFUNC(LX_PE_CMN_CONTRAST_T)		= LX_PE_CMN_START_CODE,	///< using struct LX_PE_CMN_CONTRAST_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_BRIGHTNESS_T)		= LX_PE_CMN_START_CODE+1,	///< using struct LX_PE_CMN_BRIGHTNESS_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_SATURATION_T)		= LX_PE_CMN_START_CODE+2,	///< using struct LX_PE_CMN_SATURATION_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_HUE_T)			= LX_PE_CMN_START_CODE+3,	///< using struct LX_PE_CMN_HUE_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_LEVEL_CTRL_T)		= LX_PE_CMN_START_CODE+4,	///< using struct LX_PE_CMN_LEVEL_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_VCP_LEVEL_CTRL_T)	= LX_PE_CMN_START_CODE+5,	///< using struct LX_PE_CMN_VCP_LEVEL_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_BYPASS_BLOCKS_T)	= LX_PE_CMN_START_CODE+6,	///< using struct LX_PE_CMN_BYPASS_BLOCKS_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_DDR_PQ_PARAM_T)	= LX_PE_CMN_START_CODE+7,	///< using struct LX_PE_CMN_DDR_PQ_PARAM_T

	PE_ITEM_PKTFUNC(LX_PE_CSC_XVYCC_T)			= LX_PE_CSC_START_CODE,	///< using struct LX_PE_CSC_XVYCC_T
	PE_ITEM_PKTFUNC(LX_PE_CSC_GAMUT_T)			= LX_PE_CSC_START_CODE+1,	///< using struct LX_PE_CSC_GAMUT_T
	PE_ITEM_PKTFUNC(LX_PE_CSC_POST_T)			= LX_PE_CSC_START_CODE+2,	///< using struct LX_PE_CSC_POST_T
	PE_ITEM_PKTFUNC(LX_PE_CSC_INPUT_T)			= LX_PE_CSC_START_CODE+3,	///< using struct LX_PE_CSC_INPUT_T

	PE_ITEM_PKTFUNC(LX_PE_CMG_ENABLE_T)			= LX_PE_CMG_START_CODE,	///< using struct LX_PE_CMG_ENABLE_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_ENABLE_T)	= LX_PE_CMG_START_CODE+1,	///< using struct LX_PE_CMG_REGION_ENABLE_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_T)			= LX_PE_CMG_START_CODE+2,	///< using struct LX_PE_CMG_REGION_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_CTRL_T)	= LX_PE_CMG_START_CODE+3,	///< using struct LX_PE_CMG_REGION_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_GLOBAL_CTRL_T)	= LX_PE_CMG_START_CODE+4,	///< using struct LX_PE_CMG_GLOBAL_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_COLOR_CTRL_T)		= LX_PE_CMG_START_CODE+5,	///< using struct LX_PE_CMG_COLOR_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_CW_CTRL_T)		= LX_PE_CMG_START_CODE+6,	///< using struct LX_PE_CCM_CW_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_CW_GAIN_CTRL_T)	= LX_PE_CMG_START_CODE+7,	///< using struct LX_PE_CMG_CW_GAIN_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_SAT_GAIN_LUT_T)	= LX_PE_CMG_START_CODE+8,	///< using struct LX_PE_CMG_SAT_GAIN_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_EXT_PATTERN_INFO_T)	= LX_PE_CMG_START_CODE+9,	///< using struct LX_PE_EXT_PATTERN_INFO_T

	PE_ITEM_PKTFUNC(LX_PE_NRD_SUDO_DNR_CMN_T)	= LX_PE_NRD_DNR_START_CODE,		///< using struct LX_PE_NRD_SUDO_DNR_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR2_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+2,	///< using struct LX_PE_NRD_DNR2_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR3_CMN_T)		= LX_PE_NRD_DNR_START_CODE+3,	///< using struct LX_PE_NRD_DNR3_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR4_CMN_T)		= LX_PE_NRD_DNR_START_CODE+4,	///< using struct LX_PE_NRD_DNR4_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR4_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+5,	///< using struct LX_PE_NRD_DNR4_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR5_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+6,	///< using struct LX_PE_NRD_DNR5_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR6_CMN_T)		= LX_PE_NRD_DNR_START_CODE+7,	///< using struct LX_PE_NRD_DNR6_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR6_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+8,	///< using struct LX_PE_NRD_DNR6_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR7_CMN_T)		= LX_PE_NRD_DNR_START_CODE+9,	///< using struct LX_PE_NRD_DNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR7_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+10,	///< using struct LX_PE_NRD_DNR7_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR8_CMN_T)		= LX_PE_NRD_DNR_START_CODE+11,	///< using struct LX_PE_NRD_DNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR8_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+12,	///< using struct LX_PE_NRD_DNR7_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR9_CMN_T)		= LX_PE_NRD_DNR_START_CODE+13,	///< using struct LX_PE_NRD_DNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR9_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+14,	///< using struct LX_PE_NRD_DNR7_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_LED_DNR_CMN_T)		= LX_PE_NRD_DNR_START_CODE+15,	///< using struct LX_PE_LED_DNR_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_LED_DNR_DETAIL_T)		= LX_PE_NRD_DNR_START_CODE+16,	///< using struct LX_PE_LED_DNR_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR_CMN_T)		= LX_PE_NRD_DNR_START_CODE+17,	///< using struct LX_PE_NRD_DNR_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_EASY_DNR_CMN_T)	= LX_PE_NRD_DNR_START_CODE+18,	///< using struct LX_PE_NRD_EASY_DNR_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR_DETAIL_T)	    = LX_PE_NRD_DNR_START_CODE+19,	///< using struct LX_PE_NRD_DNR5_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_LED_DCNT_CMN_T)		= LX_PE_NRD_DNR_START_CODE+20,	///< using struct LX_PE_LED_DNR_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_LED_DCNT_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+21,	///< using struct LX_PE_LED_DNR_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DCNT_CMN_T)		= LX_PE_NRD_DNR_START_CODE+22,	///< using struct LX_PE_NRD_DCNT_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DCNT_DETAIL_T)	= LX_PE_NRD_DNR_START_CODE+23,	///< using struct LX_PE_NRD_DCNT_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR_SQM_CMN_T)	= LX_PE_NRD_DNR_START_CODE+24,	///< using struct LX_PE_NRD_DNR_SQM_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_LED_DCNT_SQM_CMN_T)	= LX_PE_NRD_DNR_START_CODE+25,	///< using struct LX_PE_LED_DCNT_SQM_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DCNT_SQM_CMN_T)	= LX_PE_NRD_DNR_START_CODE+26,	///< using struct LX_PE_NRD_DCNT_SQM_CMN_T

	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_CMN_T)		= LX_PE_NRD_TNR_START_CODE,	///< using struct LX_PE_NRD_TNR_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_DETAIL_T)		= LX_PE_NRD_TNR_START_CODE+1,	///< using struct LX_PE_NRD_TNR_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND_CMN_T)		= LX_PE_NRD_TNR_START_CODE+2,	///< using struct LX_PE_NRD_TNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND_DETAIL_T)	= LX_PE_NRD_TNR_START_CODE+3,	///< using struct LX_PE_NRD_TNR7_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR5_CMN_T)		= LX_PE_NRD_TNR_START_CODE+6,	///< using struct LX_PE_NRD_TNR5_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR5_DETAIL_T)	= LX_PE_NRD_TNR_START_CODE+7,	///< using struct LX_PE_NRD_TNR5_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR6_CMN_T)		= LX_PE_NRD_TNR_START_CODE+8,	///< using struct LX_PE_NRD_TNR6_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR7_CMN_T)		= LX_PE_NRD_TNR_START_CODE+9,	///< using struct LX_PE_NRD_TNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR8_CMN_T)		= LX_PE_NRD_TNR_START_CODE+10,	///< using struct LX_PE_NRD_TNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR6_DETAIL_T)	= LX_PE_NRD_TNR_START_CODE+11,	///< using struct LX_PE_NRD_TNR6_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR7_DETAIL_T)	= LX_PE_NRD_TNR_START_CODE+12,	///< using struct LX_PE_NRD_TNR7_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND1_CMN_T)	= LX_PE_NRD_TNR_START_CODE+13,	///< using struct LX_PE_NRD_TNR7_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND1_DETAIL_T)	= LX_PE_NRD_TNR_START_CODE+14,	///< using struct LX_PE_NRD_TNR7_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_SQM_CMN_T)	= LX_PE_NRD_TNR_START_CODE+15,	///< using struct LX_PE_NRD_TNR_SQM_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND_SQM_CMN_T)	= LX_PE_NRD_TNR_START_CODE+16,	///< using struct LX_PE_NRD_TNR2ND_SQM_CMN_T

	PE_ITEM_PKTFUNC(LX_PE_DNT_FILMMODE_T)		= LX_PE_DNT_START_CODE,	///< using struct LX_PE_DNT_FILMMODE_T
	PE_ITEM_PKTFUNC(LX_PE_DNT_LD_MODE_T)		= LX_PE_DNT_START_CODE+1,	///< using struct LX_PE_DNT_LD_MODE_T

	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_CMN_T)		= LX_PE_SHP_RE_START_CODE+1,	///< using struct LX_PE_SHP_RE1_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_HOR_T)		= LX_PE_SHP_RE_START_CODE+2,	///< using struct LX_PE_SHP_RE1_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_VER_T)		= LX_PE_SHP_RE_START_CODE+3,	///< using struct LX_PE_SHP_RE1_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_MISC_T)		= LX_PE_SHP_RE_START_CODE+4,	///< using struct LX_PE_SHP_RE1_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EE1_T)			= LX_PE_SHP_RE_START_CODE+5,	///< using struct LX_PE_SHP_EE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_DE1_T)			= LX_PE_SHP_RE_START_CODE+6,	///< using struct LX_PE_SHP_DE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_CMN_T)		= LX_PE_SHP_RE_START_CODE+7,	///< using struct LX_PE_SHP_RE2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_CMN_T)		= LX_PE_SHP_RE_START_CODE+8,	///< using struct LX_PE_SHP_RE3_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_HOR_T)		= LX_PE_SHP_RE_START_CODE+9,	///< using struct LX_PE_SHP_RE2_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_VER_T)		= LX_PE_SHP_RE_START_CODE+10,	///< using struct LX_PE_SHP_RE2_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_MISC_T)		= LX_PE_SHP_RE_START_CODE+11,	///< using struct LX_PE_SHP_RE2_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_MISC_T)		= LX_PE_SHP_RE_START_CODE+12,	///< using struct LX_PE_SHP_RE3_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE4_MISC_T)		= LX_PE_SHP_RE_START_CODE+13,	///< using struct LX_PE_SHP_RE4_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE4_CMN_T)		= LX_PE_SHP_RE_START_CODE+14,	///< using struct LX_PE_SHP_RE3_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_HOR_T)		= LX_PE_SHP_RE_START_CODE+15,	///< using struct LX_PE_SHP_RE3_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_VER_T)		= LX_PE_SHP_RE_START_CODE+16,	///< using struct LX_PE_SHP_RE3_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE5_MISC_T)		= LX_PE_SHP_RE_START_CODE+17,	///< using struct LX_PE_SHP_RE5_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EE2_T)			= LX_PE_SHP_RE_START_CODE+18,	///< using struct LX_PE_SHP_EE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_DE2_T)			= LX_PE_SHP_RE_START_CODE+19,	///< using struct LX_PE_SHP_DE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_PSP_T)			= LX_PE_SHP_RE_START_CODE+20,	///< using struct LX_PE_SHP_PSP_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE5_CMN_T)		= LX_PE_SHP_RE_START_CODE+21,	///< using struct LX_PE_SHP_RE5_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE4_HOR_T)		= LX_PE_SHP_RE_START_CODE+22,	///< using struct LX_PE_SHP_RE4_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE4_VER_T)		= LX_PE_SHP_RE_START_CODE+23,	///< using struct LX_PE_SHP_RE4_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE6_MISC_T)		= LX_PE_SHP_RE_START_CODE+24,	///< using struct LX_PE_SHP_RE6_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EE3_T)			= LX_PE_SHP_RE_START_CODE+25,	///< using struct LX_PE_SHP_EE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_DE3_T)			= LX_PE_SHP_RE_START_CODE+26,	///< using struct LX_PE_SHP_DE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_PSEUDO_CMN_T)	= LX_PE_SHP_RE_START_CODE+27,	///< using struct LX_PE_SHP_RE_PSEUDO_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_PSEUDO_HOR_T)	= LX_PE_SHP_RE_START_CODE+28,	///< using struct LX_PE_SHP_RE_PSEUDO_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_PSEUDO_VER_T)	= LX_PE_SHP_RE_START_CODE+29,	///< using struct LX_PE_SHP_RE_PSEUDO_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_PSEUDO_EE_T)		= LX_PE_SHP_RE_START_CODE+30,	///< using struct LX_PE_SHP_PSEUDO_EE_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_PSEUDO_DE_T)		= LX_PE_SHP_RE_START_CODE+31,	///< using struct LX_PE_SHP_PSEUDO_DE_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE6_CMN_T)		= LX_PE_SHP_RE_START_CODE+32,	///< using struct LX_PE_SHP_RE6_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE5_HOR_T)		= LX_PE_SHP_RE_START_CODE+33,	///< using struct LX_PE_SHP_RE4_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE5_VER_T)		= LX_PE_SHP_RE_START_CODE+34,	///< using struct LX_PE_SHP_RE4_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE7_MISC_T)		= LX_PE_SHP_RE_START_CODE+35,	///< using struct LX_PE_SHP_RE7_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EE4_T)			= LX_PE_SHP_RE_START_CODE+36,	///< using struct LX_PE_SHP_EE4_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_DE4_T)			= LX_PE_SHP_RE_START_CODE+37,	///< using struct LX_PE_SHP_DE4_T
	PE_ITEM_PKTFUNC(LX_PE_VSD_OBC_CONT_T)		= LX_PE_SHP_RE_START_CODE+38,	///< using struct LX_PE_VSD_OBC_CONT_T
	PE_ITEM_PKTFUNC(LX_PE_VSD_OBC_LUT_T)		= LX_PE_SHP_RE_START_CODE+39,	///< using struct LX_PE_VSD_OBC_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_EASY_CMN_T)	= LX_PE_SHP_RE_START_CODE+40,	///< using struct LX_PE_SHP_RE_EASY_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_EASY_HOR_T)	= LX_PE_SHP_RE_START_CODE+41,	///< using struct LX_PE_SHP_RE_EASY_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_EASY_VER_T)	= LX_PE_SHP_RE_START_CODE+42,	///< using struct LX_PE_SHP_RE_EASY_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EASY_EE_T)		= LX_PE_SHP_RE_START_CODE+43,	///< using struct LX_PE_SHP_PSEUDO_EE_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_EASY_DE_T)		= LX_PE_SHP_RE_START_CODE+44,	///< using struct LX_PE_SHP_PSEUDO_DE_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_SQM_CMN_T)		= LX_PE_SHP_RE_START_CODE+45,	///< using struct LX_PE_SHP_RE_SQM_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE_SQM_DETAIL_T)	= LX_PE_SHP_RE_START_CODE+46,	///< using struct LX_PE_SHP_RE_SQM_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_SQM_CMN_T)	= LX_PE_SHP_RE_START_CODE+47,	///< using struct LX_PE_SHP_SR2K_SQM_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_SQM_DETAIL_T)= LX_PE_SHP_RE_START_CODE+48,	///< using struct LX_PE_SHP_SR2K_SQM_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_VSD_OBC1_CONT_T)		= LX_PE_SHP_RE_START_CODE+49,	///< using struct LX_PE_VSD_OBC_CONT_T

	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE_CMN_T) 		= LX_PE_SHP_SR_START_CODE+5,	///< using struct LX_PE_SHP_SR_RE_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE_HOR_T)		= LX_PE_SHP_SR_START_CODE+6,	///< using struct LX_PE_SHP_SR_RE_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE_VER_T)		= LX_PE_SHP_SR_START_CODE+7,	///< using struct LX_PE_SHP_SR_RE_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE_MISC_T)		= LX_PE_SHP_SR_START_CODE+8,	///< using struct LX_PE_SHP_SR_RE_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_EE_T)			= LX_PE_SHP_SR_START_CODE+9,	///< using struct LX_PE_SHP_SR_EE_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_DE_T)			= LX_PE_SHP_SR_START_CODE+10,	///< using struct LX_PE_SHP_SR_DE_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE2_CMN_T) 	= LX_PE_SHP_SR_START_CODE+12,	///< using struct LX_PE_SHP_SR_RE2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE2_HOR_T)		= LX_PE_SHP_SR_START_CODE+13,	///< using struct LX_PE_SHP_SR_RE2_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE2_VER_T)		= LX_PE_SHP_SR_START_CODE+14,	///< using struct LX_PE_SHP_SR_RE2_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE2_MISC_T)	= LX_PE_SHP_SR_START_CODE+15,	///< using struct LX_PE_SHP_SR_RE2_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_EE2_T)			= LX_PE_SHP_SR_START_CODE+16,	///< using struct LX_PE_SHP_SR_EE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_DE2_T)			= LX_PE_SHP_SR_START_CODE+17,	///< using struct LX_PE_SHP_SR_DE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE3_CMN_T) 	= LX_PE_SHP_SR_START_CODE+20,	///< using struct LX_PE_SHP_SR_RE2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE3_HOR_T)		= LX_PE_SHP_SR_START_CODE+21,	///< using struct LX_PE_SHP_SR_RE2_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE3_VER_T)		= LX_PE_SHP_SR_START_CODE+22,	///< using struct LX_PE_SHP_SR_RE2_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE3_MISC_T)	= LX_PE_SHP_SR_START_CODE+23,	///< using struct LX_PE_SHP_SR_RE2_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_EE3_T)			= LX_PE_SHP_SR_START_CODE+24,	///< using struct LX_PE_SHP_SR_EE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_DE3_T)			= LX_PE_SHP_SR_START_CODE+25,	///< using struct LX_PE_SHP_SR_DE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE4_CMN_T) 	= LX_PE_SHP_SR_START_CODE+26,	///< using struct LX_PE_SHP_SR_RE2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE4_HOR_T)		= LX_PE_SHP_SR_START_CODE+27,	///< using struct LX_PE_SHP_SR_RE2_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE4_VER_T)		= LX_PE_SHP_SR_START_CODE+28,	///< using struct LX_PE_SHP_SR_RE2_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_RE4_MISC_T)	= LX_PE_SHP_SR_START_CODE+29,	///< using struct LX_PE_SHP_SR_RE2_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_EE4_T)			= LX_PE_SHP_SR_START_CODE+30,	///< using struct LX_PE_SHP_SR_EE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR_DE4_T)			= LX_PE_SHP_SR_START_CODE+31,	///< using struct LX_PE_SHP_SR_DE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_RE_CMN_T) 	= LX_PE_SHP_SR_START_CODE+32,	///< using struct LX_PE_SHP_SR_RE2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_RE_HOR_T)	= LX_PE_SHP_SR_START_CODE+33,	///< using struct LX_PE_SHP_SR_RE2_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_RE_VER_T)	= LX_PE_SHP_SR_START_CODE+34,	///< using struct LX_PE_SHP_SR_RE2_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_RE_MISC_T)	= LX_PE_SHP_SR_START_CODE+35,	///< using struct LX_PE_SHP_SR_RE2_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_EE_T)		= LX_PE_SHP_SR_START_CODE+36,	///< using struct LX_PE_SHP_SR_EE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_DE_T)		= LX_PE_SHP_SR_START_CODE+37,	///< using struct LX_PE_SHP_SR_DE2_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_EASY_CMN_T) 	= LX_PE_SHP_SR_START_CODE+38,	///< using struct LX_PE_SHP_SR2K_EASY_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_EASY_DE_T) 	= LX_PE_SHP_SR_START_CODE+39,	///< using struct LX_PE_SHP_SR2K_EASY_DE_T

	PE_ITEM_PKTFUNC(LX_PE_CCM_GAMMALUT_T)		= LX_PE_CCM_START_CODE,	///< using struct LX_PE_CCM_GAMMALUT_T
	PE_ITEM_PKTFUNC(LX_PE_CCM_PIXEL_REPLACE_T)	= LX_PE_CCM_START_CODE+1,	///< using struct LX_PE_CCM_PIXEL_REPLACE_T
	PE_ITEM_PKTFUNC(LX_PE_CCM_WB_T)				= LX_PE_CCM_START_CODE+2,	///< using struct LX_PE_CCM_WB_T
	PE_ITEM_PKTFUNC(LX_PE_CCM_AUTO_CR_T)		= LX_PE_CCM_START_CODE+3,	///< using struct LX_PE_CCM_AUTO_CR_T

	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_CONF_T)		= LX_PE_DCM_START_CODE,	///< using struct LX_PE_DCM_DCE_CONF_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_LUT_T)		= LX_PE_DCM_START_CODE+1,	///< using struct LX_PE_DCM_DCE_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DSE_LUT_T)		= LX_PE_DCM_START_CODE+2,	///< using struct LX_PE_DCM_DSE_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_BLENDING_T)		= LX_PE_DCM_START_CODE+3,	///< using struct LX_PE_DCM_BLENDING_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH0_T)	= LX_PE_DCM_START_CODE+4,	///< using struct LX_PE_DCM_DCE_SMOOTH0_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH1_T)	= LX_PE_DCM_START_CODE+5,	///< using struct LX_PE_DCM_DCE_SMOOTH1_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DRC_MODE_T)		= LX_PE_DCM_START_CODE+6,	///< using struct LX_PE_DCM_DRC_MODE_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_HDR_LUT_T)		= LX_PE_DCM_START_CODE+7,	///< using struct LX_PE_DCM_HDR_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_HDR_MODE_T)		= LX_PE_DCM_START_CODE+8,	///< using struct LX_PE_DCM_HDR_MODE_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DSE_CTRL_T)		= LX_PE_DCM_START_CODE+9,	///< using struct LX_PE_DCM_DSE_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DSE_CTRL2_T)		= LX_PE_DCM_START_CODE+10,	///< using struct LX_PE_DCM_DSE_CTRL2_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DRC_CUV_T)		= LX_PE_DCM_START_CODE+11,	///< using struct LX_PE_DCM_DRC_CUV_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DRC_CONT_T)		= LX_PE_DCM_START_CODE+12,	///< using struct LX_PE_DCM_DRC_CONT_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_OBC_CTRL_T)		= LX_PE_DCM_START_CODE+13,	///< using struct LX_PE_DCM_OBC_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_OBC_DATA_T)		= LX_PE_DCM_START_CODE+14,	///< using struct LX_PE_DCM_OBC_DATA_T

	PE_ITEM_PKTFUNC(LX_PE_ETC_TBL_T)			= LX_PE_MISC_START_CODE,	///< using struct LX_PE_ETC_TBL_T
	PE_ITEM_PKTFUNC(LX_PE_INF_DISPLAY_T)		= LX_PE_MISC_START_CODE+1,	///< using struct LX_PE_INF_DISPLAY_T
	PE_ITEM_PKTFUNC(LX_PE_INF_LEVEL_T)			= LX_PE_MISC_START_CODE+2,	///< using struct LX_PE_INF_LEVEL_T

	PE_ITEM_PKTFUNC(LX_PE_HST_HISTO_INFO_T)		= LX_PE_HST_START_CODE,	///< using struct LX_PE_HST_HISTO_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HST_HISTO_CFG_T)		= LX_PE_HST_START_CODE+1,	///< using struct LX_PE_HST_HISTO_CFG_T
	PE_ITEM_PKTFUNC(LX_PE_HST_APL_INFO_T)		= LX_PE_HST_START_CODE+2,	///< using struct LX_PE_HST_APL_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HST_HDR_INFO_T)		= LX_PE_HST_START_CODE+3,	///< using struct LX_PE_HST_HDR_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HST_BLK_APL_T)		= LX_PE_HST_START_CODE+4,	///< using struct LX_PE_HST_BLK_APL_T

	PE_ITEM_PKTFUNC(LX_PE_HDR_HISTO_INFO_T)		= LX_PE_HDR_START_CODE,	///< using struct LX_PE_HDR_HISTO_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_CSC_T)			= LX_PE_HDR_START_CODE+1,	///< using struct LX_PE_HDR_CSC_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_TONEMAP_LUT_T)	= LX_PE_HDR_START_CODE+2,	///< using struct LX_PE_HDR_TONEMAP_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_EOTF_LUT_T)		= LX_PE_HDR_START_CODE+3,	///< using struct LX_PE_HDR_EOTF_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_OETF_LUT_T)		= LX_PE_HDR_START_CODE+4,	///< using struct LX_PE_HDR_OETF_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_INFO_T)			= LX_PE_HDR_START_CODE+5,	///< using struct LX_PE_HDR_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_3D_LUT_INFO_T)	= LX_PE_HDR_START_CODE+6,	///< using struct LX_PE_HDR_3D_LUT_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_GAMMA_EN_T)		= LX_PE_HDR_START_CODE+7,	///< using struct LX_PE_HDR_GAMMA_EN_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_CCR_T)			= LX_PE_HDR_START_CODE+8,	///< using struct LX_PE_HDR_CCR_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_YGAIN_LUT_T)		= LX_PE_HDR_START_CODE+9,	///< using struct LX_PE_HDR_YGAIN_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_MODE_INFO_T)		= LX_PE_HDR_START_CODE+10,	///< using struct LX_PE_HDR_MODE_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_HDR_LLLUT_T)			= LX_PE_HDR_START_CODE+11,	///< using struct LX_PE_HDR_LLLUT_T

	PE_ITEM_PKTFUNC(MAX)						= PE_PKTINFO_FUNCTYPE_MAXNUM	///< max
}
LX_PE_PKT_FUNCTYPE;
/**
 *	platform type descripter for pe modules
 */
typedef enum
{
	LX_PE_PLATFORM_WEBOS		= 0,	///< webos DB
	LX_PE_PLATFORM_NUM					///<basic(easy) DB
}
LX_PE_DBTYPE;

/**
 *	pe packet
 */
typedef struct
{
	UINT32 info;	///< [31:24]LX_PE_PKT_RWTYPE | [23:16]LX_PE_PKT_MODLTYPE | [15:0]LX_PE_PKT_FUNCTYPE
	UINT32 size;	///< size of data
	union
	{
		void *data;		///< packet data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_PKT_T;

/**
 *	pe firmware control parameter type
 */
typedef struct
{
	UINT32 ctrl_en;		//< fw control enable or not
	UINT32 dbg_en;		///< dbg print enable or not
}
LX_PE_DBG_FWI_CTRL_T;

/**
 *	pe debug settings control parameter type (only for debug)
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_DBG_TYPE type;		///< debug type
	UINT32 print_lvl;			///< pe debug print level
	UINT32 bypass;				///< bypass each module
	LX_PE_DBG_FWI_CTRL_T fwc;	///< fw ctrl
}
LX_PE_DBG_SETTINGS_T;

/**
 *	pe default settings control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID	win_id;		///< window id
}
LX_PE_DEFAULT_SETTINGS_T;

/**
 *	pe initial settings control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 suspend_mode;		///< suspend mode, 0:off(default), 1:on
}
LX_PE_INIT_SETTINS_T;

/***************************************************************************/
/* CMN : Common */
/***************************************************************************/
/**
 *	pe contrast control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT16 contrast;		///< contrast value
}
LX_PE_CMN_CONTRAST_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT16 contrast;		///< contrast value
	UINT8  setbycsc;
}
LX_PE_CMN1_CONTRAST_T;

/**
 *	pe brightness control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 brightness;		///< brightness value
}
LX_PE_CMN_BRIGHTNESS_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 brightness;		///< brightness value
	UINT8  setbycsc;
}
LX_PE_CMN1_BRIGHTNESS_T;

/**
 *	pe saturation control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 saturation;		///< saturation value
}
LX_PE_CMN_SATURATION_T;

/**
 *	pe hue control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 hue;				///< hue value
}
LX_PE_CMN_HUE_T;

/**
 *	pe level control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 offset;			///< display input y offset, 0~512~1023
    UINT16 center;			///< center position for y gain control, 0~128~255
    UINT16 gain;			///< display input y gain, 0~128~255
	UINT16 tp_on;			///< test pattern on,off
}
LX_PE_CMN_LEVEL_CTRL_T;


/**
 *	pe vcp level control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 enable;			///< enable
    UINT16 center_position;	///< center_position
    UINT16 contrast;		///< contrast
	UINT16 brightness;		///< brighness
	UINT16 saturation;		///< saturation
}
LX_PE_CMN_VCP_LEVEL_CTRL_T;

/**
 *	pe bypass blocks parameter type
 */
typedef struct
{
	UINT32 u32BlockMask;	// masking bits
	BOOLEAN bOnOff;			// 0: normal operation, 1 : bypass/off,
} LX_PE_CMN_BYPASS_BLOCKS_T;

/**
 *	pe ddr reg read
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 dnr____buff[5+2];  ///< new common ui
	UINT32 deconnd___buff[5+2];
	UINT32 deconled__buff[5+2];
	UINT32 tnr0__sqm[11+2];	 ///< *new sqm(ui)
	UINT32 tnr1__sqm[11+2];	 ///< *new sqm(ui)
	UINT32 dnr___sqmui[19+2]; ///< new sqm ui
	UINT32 deconnd__sqmui[23+2];
	UINT32 deconled_sqmui[23+2];
	UINT32 shp_ui_sqm_2k[29+2];		     ///< *new shp_ui_sqm_2k[29];
	UINT32 shp_sqm_cmn_2k[11+2];		     ///< *new shp_sqm_cmn_2k[11];
	UINT32 shp_ui_sqm_vsd[30+2];		     ///< *new shp_ui_sqm_vsd[30];
	UINT32 shp_sqm_cmn_vsd[19+2];		 ///< *new shp_sqm_cmn_vsd[19];
} LX_PE_CMN_DDR_PQ_PARAM_T;

/***************************************************************************/
/* CCM : Color Correctin Module */
/***************************************************************************/
/**
 *	pe gamma lut control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 size;			///< size of lut_data
	union
	{
		UINT32 *data;			///< [29:20]R | [19:10]B | [9:0]G
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_CCM_GAMMALUT_T;

/**
 *	pe gamma pixel replacement control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 pxl_rep_r;		///< R value for pixel replacement, 1:on, 0:off, default:0
	UINT8 pxl_rep_g;		///< G value for pixel replacement, 1:on, 0:off, default:0
	UINT8 pxl_rep_b;		///< B value for pixel replacement, 1:on, 0:off, default:0
}
LX_PE_CCM_PIXEL_REPLACE_T;

/**
 *	pe white balance control parameter type
 */
typedef struct {
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 r_gain;			///< red gain, 		0~255(192= 1.0 gain)
	UINT8 g_gain;			///< green gain, 	0~255(192= 1.0 gain)
	UINT8 b_gain;			///< blue gain, 	0~255(192= 1.0 gain)
	UINT8 r_offset; 		///< red offset,	0~255(128= zero offset)
	UINT8 g_offset; 		///< green offset,	0~255(128= zero offset)
	UINT8 b_offset; 		///< blue offset,	0~255(128= zero offset)
}
LX_PE_CCM_WB_T;

/**
 *	pe left right mismatch correction control parameter type
 */
typedef struct {
	UINT8 enable;			///< enable LRCR, 1:on, 0:off
	UINT8 th_max_hist;		///< if(max_hist > th_max_hist), auto cr does not apply
	UINT8 th_valid_bins;	///< if(n_valid_bins > th_valid_bins), auto cr does not apply
	UINT8 adj_th0;			///< adjustment threshold 0
	UINT8 adj_th1;			///< adjustment threshold 1
}
LX_PE_CCM_AUTO_CR_T;

/***************************************************************************/
/* DCM : Dynamic Contrast Module */
/***************************************************************************/
/**
 *	pe dynamic contrast enhancement configuration parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	LX_PE_COLOR_DOMAIN domain;		///< color domain.
    UINT32 min_pos;					///< the min position, default "26"(0~255(0%~100%))
	UINT32 max_pos;					///< the max position, default "220"(0~255(0%~100%))
}
LX_PE_DCM_DCE_CONF_T;

/**
 *	pe dynamic contrast lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	union
	{
		UINT32 *data;				///< [9:0] y data, [25:16] x data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_DCM_DCE_LUT_T;
/**
 *	pe dynamic contrast lut parameter type - o20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 lumalut_y[32];
	UINT32 lumalut_x[32];
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
}
LX_PE_DCM_DCE_LUT1_T;

/**
 *	pe dynamic contrast lut parameter type - o20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 lumalut_y[4][32];
	UINT32 lumalut_x[4][32];
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
}
LX_PE_DCM_DCE_LUT2_T;

/**
 *	pe dynamic saturation lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	union
	{
		UINT32 *data;				///< [9:0] y data, [25:16] x data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_DCM_DSE_LUT_T;


/**
 *	pe dynamic contrast bypass blending control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 color_out_gain;		///< dce out gain, 1(0%)~128(200%)~255(400%) (forbidden 0)
	UINT32 region_sel;			///< LSB : select region 0
	UINT32 color_region_en;		///< color region apply for dce y
	UINT32 y_grad_gain;			///< Gradient of Y  signal,0x0:128to0, 0x1:64to0, 0x2:32to0, 0x3:16to0
	UINT32 cb_grad_gain;		///< Gradient of Cb signal,0x0:128to0, 0x1:64to0, 0x2:32to0, 0x3:16to0
	UINT32 cr_grad_gain;		///< Gradient of Cr signal,0x0:128to0, 0x1:64to0, 0x2:32to0, 0x3:16to0
	UINT32 y_range_min;			///< y_range_min : 0~1023
	UINT32 y_range_max;			///< y_range_max : 0~1023
	UINT32 cb_range_min;		///< cb_range_min : 0~1023
	UINT32 cb_range_max;		///< cb_range_max : 0~1023
	UINT32 cr_range_min;		///< cr_range_min : 0~1023
	UINT32 cr_range_max;		///< cr_range_max : 0~1023
}
LX_PE_DCM_BLENDING_T;

/**
 *	pe dynamic blur control parameter type
 *	- use for dce on hsv domain
 *	ver.0, for H13Bx,M14Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 avg_filter_tap;		///< luma blur for DCE(0:3x3,1:5x5,2:7x7)
	UINT32 edge_map_tap;		///< edge-map tap size for blending(0:7x5,1:5x5,2:3x3)
	UINT32 e_to_w_th_x0;		///< edge to weight : x0(0~255)
	UINT32 e_to_w_th_x1;		///< edge to weight : x1(0~255)
	UINT32 e_to_w_th_y0;		///< edge to weight : y0(0~255)
	UINT32 e_to_w_th_y1;		///< edge to weight : y2(0~255)
	UINT32 chroma_blur_mode;	///< chroma blur for DCE(0:blur off,1:blur only)
	UINT32 blur_v_gain;			///< 0x0 : blur V <-> 0xF : original V
}
LX_PE_DCM_DCE_SMOOTH0_T;

/**
 *	pe dynamic blur control parameter type
 *	- use for dce on hsv domain
 *	ver.1, for H14x,M14Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 sc_map_sel;			///< 0x0:MAX(e,t map),0x1:t map,0x2:e map
	UINT32 sc_amap_filter_tap;	///< amap, 0x0~0x3 : 5,7,9,15-tap
	UINT32 amap_gain;			///< e map gain:(2.3u)0x0=0 ~ 0x8=1.0 ~ 0x1F=3.99x
	UINT32 tmap_gain;			///< t map gain:(2.3u)0x0=0 ~ 0x8=1.0 ~ 0x1F=3.99x
	UINT32 e_to_w_th_x0;		///< edge to weight : x0
	UINT32 e_to_w_th_x1;		///< edge to weight : x1
	UINT32 e_to_w_th_y0;		///< edge to weight : y0
	UINT32 e_to_w_th_y1;		///< edge to weight : y1
	UINT32 blur_v_gain;			///< 0x0 : blur V <-> 0xF : original V
}
LX_PE_DCM_DCE_SMOOTH1_T;

/**
 *	pe drc mode
 *	for H15x
 */
typedef enum
{
	LX_PE_DRC_NONE = 0, 		///< NONE
	LX_PE_DRC_UI	  , 		///< ui
	LX_PE_DRC_DC_BYPASS,		///< bypass
	LX_PE_DRC_PIC_MODE,		    ///< picturemode
	LX_PE_DRC_UI_PICM,		    ///< ui & picturemode
	LX_PE_DRC_NUM				///<set all member
}
LX_PE_DCM_DRC_MODE_TYPE;
	
typedef struct
{
	LX_PE_WIN_ID win_id;        ///< window id
	LX_PE_DCM_DRC_MODE_TYPE db_type;
	UINT32 dc_mode;             ///< dc mode, 0:off,1:low,2:medium,3:high
	UINT32 dc_bypass;           ///< dc bypass
	UINT32 dc_sc_cnt;           ///< scene change count, 0~15
	UINT32 picture_mode;///< picture_mode 1:smart 2:vivid 4:normal 8:hdr_eff 16:aps 32:movie 64:game 128:sprts 256:eco 512:hdr_vv 1024:hdr_sd 2048:photo 4096:exp1 8192:exp2
}
LX_PE_DCM_DRC_MODE_T;

/**
 *	pe hdr lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	union
	{
		UINT32 *data;				///< [9:0] y data, [25:16] x data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_DCM_HDR_LUT_T;

/**
 *	pe hdr mode control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 half_mode;		///< enable half mode, 1:on, 0:off
}
LX_PE_DCM_HDR_MODE_T;

/**
*	pe dynamic saturation control parameter type
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 saturation_cr_mode; 						///< low saturation_cr_mode
	UINT32 saturation_region_gain; 					///< saturation_region_gainposition
	UINT32 y_range_min;								///< y_range_min
	UINT32 y_range_max;								///< y_range_max
	UINT32 x_range_min;								///< x_range_min
	UINT32 x_range_max;								///< x_range_max
	UINT8 region_onoff[LX_PE_CMG_REGION_NUM];		///< region_onoff
}
LX_PE_DCM_DSE_CTRL_T;

/**
*	pe dynamic saturation control parameter type
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  saturation_cr_mode; 						///< low saturation_cr_mode
	UINT32 saturation_region_gain; 					///< saturation_region_gainposition
	UINT32 dse_h_x[LX_PE_CMG_TBLPOINT];				///< hue x_range_max
	UINT32 dse_h_y[LX_PE_CMG_TBLPOINT];				///< hue y_range_min
	UINT32 dse_y_x[LX_PE_CMG_TBLPOINT];				///< Y x_range_max
	UINT32 dse_y_y[LX_PE_CMG_TBLPOINT];				///< Y y_range_min
	UINT8  region_onoff[LX_PE_CMG_REGION_NUM];		///< region_onoff
	UINT8  chroma_gain_en;							///< chroma_gain_en
	UINT32 dce_chr_gain1;							///< dce_chr_gain1
	UINT32 dce_chr_gain2;							///< dce_chr_gain2
	UINT32 dce_chr_alpha1;							///< dce_chr_alpha1
	UINT32 dce_chr_alpha2;							///< dce_chr_alpha2
}
LX_PE_DCM_DSE_CTRL2_T;

/**
*	pe dynamic saturation control parameter type
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  chroma_gain_en;
	UINT16 chroma_chr_gain1;
	UINT16 chroma_chr_gain2;
	UINT16 chroma_chr_alpha1;
	UINT16 chroma_chr_alpha2;
	UINT8  dtm_hue_gain; ///< 0~255
	UINT8  dtm_sat_gain; ///< 0~255
}
LX_PE_DCM_DSE_CTRL3_T;
/**
*   E60 
*	pe dynamic saturation control parameter type
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  chroma_gain_en;
	UINT16 chroma_cb_gain1;
	UINT16 chroma_cb_gain2;
	UINT16 chroma_cr_gain1;
	UINT16 chroma_cr_gain2;
	UINT16 chroma_alpha1;
	UINT16 chroma_alpha2;
	UINT8  dtm_hue_gain;     ///< 0~255
	UINT8  dtm_sat_gain;     ///< 0~255
}
LX_PE_DCM_DSE_CTRL4_T;

/**
*   O22 
*	pe dynamic saturation control parameter type
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  chroma_gain_en;
	UINT16 chroma_cb_gain1;
	UINT16 chroma_cb_gain2;
	UINT16 chroma_cr_gain1;
	UINT16 chroma_cr_gain2;
	UINT16 chroma_alpha1;
	UINT16 chroma_alpha2;
	UINT8  dtm_hue_gain;     ///< 0~255
	UINT8  dtm_sat_gain;     ///< 0~255
	UINT8  luma_gain_x[4]; //ï¿½ß°ï¿½  
 	UINT8  luma_gain_y[4]; //ï¿½ß°ï¿½
 	UINT8  sat_gain_x[4]; //ï¿½ß°ï¿½
 	UINT8  sat_gain_y[4]; //ï¿½ß°ï¿½
}
LX_PE_DCM_DSE_CTRL5_T;

/**
*   O26
*	pe dynamic saturation control parameter type
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  chroma_gain_en;
	UINT16 chroma_cb_gain1;
	UINT16 chroma_cb_gain2;
	UINT16 chroma_cr_gain1;
	UINT16 chroma_cr_gain2;
	UINT16 chroma_alpha1;
	UINT16 chroma_alpha2;
	UINT8  dtm_hue_gain;     ///< 0~255
	UINT8  dtm_sat_gain;     ///< 0~255
	UINT8  dtm_target_hue_gain; ///Ãß°¡
	UINT8  dtm_target_sat_gain; ///Ãß°¡
	UINT8  luma_gain_x[8]; // 4->8
 	UINT8  luma_gain_y[8]; // 4->8
 	UINT8  sat_gain_x[8]; // 4->8
 	UINT8  sat_gain_y[8]; // 4->8
	UINT8  dtm_hue_gain_x[10]; ///Ãß°¡
 	UINT8  dtm_hue_gain_y[8]; ///Ãß°¡
 	UINT8  dtm_sat_gain_x[8]; ///Ãß°¡
 	UINT8  dtm_sat_gain_y[8]; ///Ãß°¡
 	UINT8  dtm_val_gain_x[8]; ///Ãß°¡
 	UINT8  dtm_val_gain_y[8]; ///Ãß°¡
}
LX_PE_DCM_DSE_CTRL6_T;


/**
*	local contrast data
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	SINT32 pre_norm;						///pre normal IIR filter
	SINT32 cur_norm;						///current normal IIR filter
	SINT32 pre_sc;							///pre scene change IIR filter
	SINT32 cur_sc;							///current scene change IIR filter
	SINT32 ui_gain_w;						///UI white gain
	SINT32 ui_gain_b;						///UI black gain
	SINT32 vy_mode;							///V_Y_mode
}
LX_PE_DCM_DRC_CONT_T;

/**
*	o22 local contrast data
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	SINT32 pre_norm;						///pre normal IIR filter
	SINT32 cur_norm;						///current normal IIR filter
	SINT32 pre_sc;							///pre scene change IIR filter
	SINT32 cur_sc;							///current scene change IIR filter
	SINT32 ui_gain_w;						///UI white gain
	SINT32 ui_gain_b;						///UI black gain
	SINT32 vy_mode;							///V_Y_mode
	UINT16 apl_lut_x[4]; //ï¿½ß°ï¿½ 
	UINT16 apl_lut_y[4]; //ï¿½ß°ï¿½ 
	UINT16 txt_lut_x[4]; //ï¿½ß°ï¿½
	UINT16 txt_lut_y[4]; //ï¿½ß°ï¿½
	UINT16 dark_lut_x[4]; //ï¿½ß°ï¿½ 
	UINT16 dark_lut_y[4]; //ï¿½ß°ï¿½ 
	UINT16 bright_lut_x[4]; //ï¿½ß°ï¿½ 
	UINT16 bright_lut_y[4]; //ï¿½ß°ï¿½ 
}
LX_PE_DCM_DRC_CONT1_T;

/**
*	webos23 local contrast data
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window 
	SINT32 ui_mode_loc;					///ui
	SINT32 pre_norm;						///pre normal IIR filter
	SINT32 cur_norm;						///current normal IIR filter
	SINT32 pre_sc;							///pre scene change IIR filter
	SINT32 cur_sc;							///current scene change IIR filter
	SINT32 ui_gain_w;						///UI white gain
	SINT32 ui_gain_b;						///UI black gain
	SINT32 vy_mode;							///V_Y_mode
	UINT16 apl_lut_x[4];
	UINT16 apl_lut_y[4];
	UINT16 txt_lut_x[4];
	UINT16 txt_lut_y[4];
	UINT16 dark_lut_x[4];
	UINT16 dark_lut_y[4];
	UINT16 bright_lut_x[4];
	UINT16 bright_lut_y[4];
    UINT16 nHead_lut_x[4]; //ï¿½ß°ï¿½ 
    UINT16 nHead_lut_y[4]; //ï¿½ß°ï¿½ 
    UINT16 nBody_lut_x[4]; //ï¿½ß°ï¿½ 
    UINT16 nBody_lut_y[4]; //ï¿½ß°ï¿½ 
    UINT16 nText_lut_x[4]; //ï¿½ß°ï¿½ 
    UINT16 nText_lut_y[4]; //ï¿½ß°ï¿½ 
}
LX_PE_DCM_DRC_CONT2_T;

/**
*	webos26 o26 local contrast data
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window 
	SINT32 ui_mode_loc;					///ui
	SINT32 pre_norm;						///pre normal IIR filter
	SINT32 cur_norm;						///current normal IIR filter
	SINT32 pre_sc;							///pre scene change IIR filter
	SINT32 cur_sc;							///current scene change IIR filter
	SINT32 ui_gain_w;						///UI white gain
	SINT32 ui_gain_b;						///UI black gain
	SINT32 vy_mode;							///V_Y_mode
	UINT16 apl_lut_x[4];
	UINT16 apl_lut_y[4];
	UINT16 txt_lut_x[8];
	UINT16 txt_lut_y[8];
	UINT16 dark_lut_x[4];
	UINT16 dark_lut_y[4];
	UINT16 bright_lut_x[4];
	UINT16 bright_lut_y[4];
    UINT16 nHead_lut_x[4]; //ï¿½ß°ï¿½ 
    UINT16 nHead_lut_y[4]; //ï¿½ß°ï¿½ 
    UINT16 nBody_lut_x[4]; //ï¿½ß°ï¿½ 
    UINT16 nBody_lut_y[4]; //ï¿½ß°ï¿½ 
    UINT16 nText_lut_x[4]; //ï¿½ß°ï¿½ 
    UINT16 nText_lut_y[4]; //ï¿½ß°ï¿½ 
    SINT32 y_ma_sel;
	SINT32 t_ma_sel;
	UINT16 bapp_y_lut_x[4];
	UINT16 bapp_y_lut_y[4];
	UINT16 bapp_t_lut_x[4];
	UINT16 bapp_t_lut_y[4];
}
LX_PE_DCM_DRC_CONT3_T;


/**
*	drc lut
*/
typedef struct
{
	SINT32 global_apl[LX_PE_CM_GLOBAL_POINT];	///global_apl
	SINT32 local_apl[LX_PE_CM_LOCAL_POINT];		///local_apl
	SINT32 cuv_gain_w;						///CURV white gain
	SINT32 cuv_gain_b;						///CURV black gain
	SINT32 n1p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW];	///n1p_trans_curv
	SINT32 n2p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW];	///n1p_trans_curv
	SINT32 n3p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW];	///n1p_trans_curv
	SINT32 n4p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW];	///n1p_trans_curv
}
LX_PE_DCM_DRC_CUV_T;

typedef struct
{
	SINT32 global_apl[LX_PE_CM_GLOBAL_POINT];	///global_apl
	SINT32 local_apl[LX_PE_CM_LOCAL_POINT];		///local_apl
	SINT32 cuv_gain_w;						///CURV white gain
	SINT32 cuv_gain_b;						///CURV black gain
	SINT32 n1p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW2];	///n1p_trans_curv
	SINT32 n2p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW2];	///n1p_trans_curv
	SINT32 n3p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW2];	///n1p_trans_curv
	SINT32 n4p_trans_curv[LX_PE_CM_FREE_POINT][LX_PE_CM_LOCAL_CURVE_FW2];	///n1p_trans_curv
}
LX_PE_DCM_DRC_CUV2_T;


/**
*	OBC control to be removed
*/

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	BOOLEAN bOBC_enable;
	UINT16	object_fg_x[8];
	UINT16	object_fg_y[8];
	UINT16	object_bg_x[8];
	UINT16	object_bg_y[8];
	UINT8	fg_gain_x0;
	UINT8	fg_gain_x1;
	UINT8	fg_gain_y0;
	UINT8	fg_gain_y1;
	UINT8	bg_gain_x0;
	UINT8	bg_gain_x1;
	UINT8	bg_gain_y0;
	UINT8	bg_gain_y1;
}
LX_PE_DCM_OBC_CTRL_T;

/**
*	get OBC data
*/

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8	object_relibility;	//[31:24]	0xc900b26c
	UINT16	object_fg_apl;		//[31:22]	0xc900b270
	UINT16	object_fg_pel_num;	//[21:6]
	UINT16	object_bg_apl;		//[31:22]	0xc900b274
	UINT16	object_bg_pel_num;	//[21:6]
	UINT8	object_boxw2;		//[31:24]	0xc900b278
	UINT8	object_boxw1;		//[23:16]
	UINT8	object_boxh2;		//[15:8]
	UINT8	object_boxh1;		//[7:0]
	UINT16	object_data00;	//dummy buffer
	UINT16	object_data01;	//dummy buffer
	UINT16	object_data02;	//dummy buffer
	UINT16	object_data03;	//dummy buffer
	UINT16	object_data04;	//dummy buffer
	UINT16	object_data05;	//dummy buffer
	UINT16	object_data06;	//dummy buffer
	UINT16	object_data07;	//dummy buffer
	UINT16	object_data08;	//dummy buffer
	UINT16	object_data09;	//dummy buffer
	UINT16	object_data10;	//dummy buffer
	UINT16	object_data11;	//dummy buffer
}
LX_PE_DCM_OBC_DATA_T;

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8	object_relibility;	//[31:24]	0xc900b26c
	UINT16	object_fg_apl;		//[31:22]	0xc900b270
	UINT16	object_fg_pel_num;	//[21:6]
	UINT16	object_bg_apl;		//[31:22]	0xc900b274
	UINT16	object_bg_pel_num;	//[21:6]
	UINT8	object_boxw2;		//[31:24]	0xc900b278
	UINT8	object_boxw1;		//[23:16]
	UINT8	object_boxh2;		//[15:8]
	UINT8	object_boxh1;		//[7:0]
	UINT16	object_data00;	//dummy buffer
	UINT16	object_data01;	//dummy buffer
	UINT16	object_data02;	//dummy buffer
	UINT16	object_data03;	//dummy buffer
	UINT16	object_data04;	//dummy buffer
	UINT16	object_data05;	//dummy buffer
	UINT16	object_data06;	//dummy buffer
	UINT16	object_data07;	//dummy buffer
	UINT16	object_data08;	//dummy buffer
	UINT16	object_data09;	//dummy buffer
	UINT16	object_data10;	//dummy buffer
	UINT16	object_data11;	//dummy buffer
	UINT8	face_relibility;	//[31:24]	0xc900b26c
	UINT16	face_fg_apl;		//[31:22]	0xc900b270
	UINT16	face_fg_pel_num;	//[21:6]
	UINT16	face_bg_apl;		//[31:22]	0xc900b274
	UINT16	face_bg_pel_num;	//[21:6]
	UINT8	face_boxw2;		//[31:24]	0xc900b278
	UINT8	face_boxw1;		//[23:16]
	UINT8	face_boxh2;		//[15:8]
	UINT8	face_boxh1;		//[7:0]
	UINT16	face_data00;	//dummy buffer
	UINT16	face_data01;	//dummy buffer
	UINT16	face_data02;	//dummy buffer
	UINT16	face_data03;	//dummy buffer
	UINT16	face_data04;	//dummy buffer
	UINT16	face_data05;	//dummy buffer
	UINT16	face_data06;	//dummy buffer
	UINT16	face_data07;	//dummy buffer
	UINT16	face_data08;	//dummy buffer
	UINT16	face_data09;	//dummy buffer
	UINT16	face_data10;	//dummy buffer
	UINT16	face_data11;	//dummy buffer
}
LX_PE_DCM_OBC1_DATA_T;


typedef struct
{
	union
	{
		UINT16 *pAddrData;			///< [29:20]R | [19:10]B | [9:0]G
		UINT32 compat_data;
		UINT64 sizer;
	};
	UINT32 sizeOfItem;
	UINT32 lengthOfData;
	UINT32 sizeOfData;
}
LX_PE_DCM_LIB_DB_T;

typedef struct
{
	LX_PE_DCM_LIB_DB_T dynContDB;
	LX_PE_DCM_LIB_DB_T aplDB;
	LX_PE_DCM_LIB_DB_T aiGainDB;
	LX_PE_DCM_LIB_DB_T stabilzerDB;
	UINT32 contrast_gain[17]; // added since f22 210915
}
LX_PE_DCM_LIB_DB_ALL_T;

typedef struct
{
	UINT32 input_freq[PE_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
	UINT32 contrast_gain[PE_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
	UINT32 brightness_gain[PE_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
}
LX_PE_DCM_DBC_DB_T;

/**
*	OBC static control
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	BOOLEAN bOBC_enable;
	UINT8	fg_gain_x0;
	UINT8	fg_gain_x1;
	UINT8	fg_gain_y0;
	UINT8	fg_gain_y1;
	UINT8	bg_gain_x0;
	UINT8	bg_gain_x1;
	UINT8	bg_gain_y0;
	UINT8	bg_gain_y1;
}
LX_PE_VSD_OBC_CONT_T;
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	BOOLEAN bOBC_enable;
	UINT8	fg_gain_x0;
	UINT8	fg_gain_x1;
	UINT8	fg_gain_y0;
	UINT8	fg_gain_y1;
	UINT8	bg_gain_x0;
	UINT8	bg_gain_x1;
	UINT8	bg_gain_y0;
	UINT8	bg_gain_y1;
	BOOLEAN	bOBC_sat_enable;                      //[1]	0xC900B27C	
	BOOLEAN	bOBC_ch_bst_enable;               //[0]	0xC900B27C	
	UINT16	reg_yy_lut_pts_x0;	//[25:16]	0xC900B280
	UINT16	reg_yy_lut_pts_x1;	//[9:0]	0xC900B280
	UINT16	reg_yy_lut_pts_x2;	//[25:16]	0xC900B284
	UINT16	reg_yy_lut_pts_x3;	//[9:0]	0xC900B284
	UINT8	reg_yy_lut_pts_y0;	//[31:24]	0xC900B288
	UINT8	reg_yy_lut_pts_y1;	//[23:16]	0xC900B288
	UINT8	reg_yy_lut_pts_y2;	//[15:8]	0xC900B288
	UINT8	reg_yy_lut_pts_y3;	//[7:0]	0xC900B288
	UINT8	reg_cc_lut_pts_x0;	//[31:24]	0xC900B28C
	UINT8	reg_cc_lut_pts_y0;	//[23:16]	0xC900B28C
	UINT8	reg_cc_lut_pts_x1;	//[15:8]	0xC900B28C
	UINT8	reg_cc_lut_pts_y1;	//[7:0]	0xC900B28C
	UINT8	reg_cc_lut_pts_x2;	//[31:24]	0xC900B290
	UINT8	reg_cc_lut_pts_y2;	//[23:16]	0xC900B290
	UINT8	reg_cc_lut_pts_x3;	//[15:8]	0xC900B290
	UINT8	reg_cc_lut_pts_y3;	//[7:0]	0xC900B290
	UINT8	reg_cbst_lut_pts_x0;	//[31:24]	0xC900B294
	UINT8	reg_cbst_lut_pts_y0;	//[23:16]	0xC900B294
	UINT8	reg_cbst_lut_pts_x1;	//[15:8]	0xC900B294
	UINT8	reg_cbst_lut_pts_y1;	//[7:0]	0xC900B294
	UINT8	reg_cbst_lut_pts_x2;	//[31:24]	0xC900B298
	UINT8	reg_cbst_lut_pts_y2;	//[23:16]	0xC900B298
	UINT8	reg_cbst_lut_pts_x3;	//[15:8]	0xC900B298
	UINT8	reg_cbst_lut_pts_y3;	//[7:0]	0xC900B298
}
LX_PE_VSD_OBC1_CONT_T;

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  obj_fg_gain_x[2];
	UINT8  obj_fg_gain_y[2];
	UINT8  obj_bg_gain_x[2];
	UINT8  obj_bg_gain_y[2];
	UINT8  obj_sat_enable;
	UINT8  obj_ch_bst_enable;
	UINT16 obj_yy_lut_pts_x[4];
	UINT8  obj_yy_lut_pts_y[4];
	UINT8  obj_cc_lut_pts_x[4];
	UINT8  obj_cc_lut_pts_y[4];
	UINT8  obj_cbst_lut_pts_x[4];
	UINT8  obj_cbst_lut_pts_y[4];
	UINT8  face_fg_gain_x[2];
	UINT8  face_fg_gain_y[2];
	UINT8  face_bg_gain_x[2];
	UINT8  face_bg_gain_y[2];
	UINT8  face_sat_enable;
	UINT8  face_ch_bst_enable;
	UINT16 face_yy_lut_pts_x[4];
	UINT8  face_yy_lut_pts_y[4];
	UINT8  face_cc_lut_pts_x[4];
	UINT8  face_cc_lut_pts_y[4];
	UINT8  face_cbst_lut_pts_x[4];
	UINT8  face_cbst_lut_pts_y[4];
	UINT8  face_obj_lut_x[4];
	UINT8  face_obj_lut_y[4];
	UINT8  obj_face_lut_x[4];
	UINT8  obj_face_lut_y[4];
}
LX_PE_VSD_OBC2_CONT_T;

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 head_gain_x[2];
	UINT8 head_gain_y[2];
	UINT8 body_gain_x[2];
	UINT8 body_gain_y[2];
}
LX_PE_VSD_OBC3_CONT_T;

//O22
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 head_gain_x[4];
	UINT8 head_gain_y[4];
	UINT8 body_gain_x[4];
	UINT8 body_gain_y[4];
}
LX_PE_VSD_OBC4_CONT_T;

/**
*	OBC control
*/

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT16	object_fg_x[8];
	UINT16	object_fg_y[8];
	UINT16	object_bg_x[8];
	UINT16	object_bg_y[8];
}
LX_PE_VSD_OBC_LUT_T;

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT16	object_fg_x[8];
	UINT16	object_fg_y[8];
	UINT16	object_bg_x[8];
	UINT16	object_bg_y[8];
	UINT16	face_fg_x[8];
	UINT16	face_fg_y[8];
	UINT16	face_bg_x[8];
	UINT16	face_bg_y[8];
}
LX_PE_VSD_OBC1_LUT_T;
typedef struct
{
	 LX_PE_WIN_ID win_id;		 ///< window id
	 UINT16	 head_g_lut_x[6];
	 UINT16	 head_g_lut_y[6];
	 UINT16	 head_b_lut_x[6];
	 UINT16	 head_b_lut_y[6];
	 UINT16	 head_r_lut_x[6];
	 UINT16	 head_r_lut_y[6];
	 UINT16	 body_g_lut_x[6];
	 UINT16	 body_g_lut_y[6];
	 UINT16	 body_b_lut_x[6];
	 UINT16	 body_b_lut_y[6];
	 UINT16	 body_r_lut_x[6];
	 UINT16	 body_r_lut_y[6];
}
 LX_PE_VSD_OBC2_LUT_T;

 /**
 *	 dtm lut control
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT32 size;				///< lut step, size of data,
	union
	{
		UINT32 *data;				///< [9:0] y data, [25:16] x data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_DCM_DTM_LUT_T;


typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT16 head_apl;
	UINT16 body_apl;
}
LX_PE_VSD_OBC1_DATA_T;

//webos4tv7.0 o22
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT16 head_apl;
	UINT16 body_apl;
	UINT16 head_map_apl;
	UINT16 depth_map_apl;
}
LX_PE_VSD_OBC2_DATA_T;

/**
 *	dynamic chroma lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	union
	{
		UINT32 *data;				///< [9:0] y data, [25:16] x data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_DCM_CHR_LUT_T;
typedef struct
{
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
}
LX_PE_DCM_CHR_LUT1_T;


/***************************************************************************/
/* HST : Histogram Module */
/***************************************************************************/
/** ~O18/M16P3
 *	pe histogram information parameter type
 *	- status[0] : [25:16]hist_bin_max, [09:00]hist_bin_min
 *	- status[1] : [25:16]hist_v_max, [09:00]hist_v_min
 *	- status[2] : [28:08]hist_max_bin_val, [05:00]hist_max_bin_num
 *	- status[3] : [21:00]hist_diff_sum
 *	- status[4] : [20:00]hist_detect_rgn_num
 *	- status[5] : [07:00]saturation status
 *	- status[6] : [07:00]motion status(from tnr block)
 *	- status[7] : [17:00]texture measure
 *	- status[8] : reserved
 *	- status[9] : reserved
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_COLOR_DOMAIN domain;	///< color domain
	UINT32 histo_ready;			///< histogram is valid, if 1, invalid otherwise.
	UINT32 average[3];			///< the average of all luma in the specified region Y or RGB
    UINT32 min;					///< the min of all luma in the specified region
	UINT32 max;					///< the max of all luma in the specified region
    UINT32 histogram[96];		///< histogram data of luma(histo[0~31]1st,[32~63]2nd,[64~95]3rd)
    UINT32 status[10];			///< histogram status
}
LX_PE_HST_HISTO_INFO_T;

/** O20
 *	pe histogram information parameter type
 *	- status[0] : [25:16]hist_bin_max, [09:00]hist_bin_min
 *	- status[1] : [25:16]hist_v_max, [09:00]hist_v_min
 *	- status[2] : [28:08]hist_max_bin_val, [05:00]hist_max_bin_num
 *	- status[3] : [21:00]hist_diff_sum
 *	- status[4] : [20:00]hist_detect_rgn_num
 *	- status[5] : [07:00]saturation status
 *	- status[6] : [07:00]motion status(from tnr block)
 *	- status[7] : [17:00]texture measure
 *	- status[8] : reserved
 *	- status[9] : reserved
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_COLOR_DOMAIN domain;	///< color domain
	UINT32 histo_ready;			///< histogram is valid, if 1, invalid otherwise.
	UINT32 average[3];			///< the average of all luma in the specified region Y or RGB
    UINT32 min;					///< the min of all luma in the specified region
	UINT32 max;					///< the max of all luma in the specified region
    UINT32 histogram[192];		///< histogram data of luma(histo[0~127]1st,[128~159]2nd,[160~191]3rd)
    UINT32 status[10];			///< histogram status
}
LX_PE_HST_HISTO1_INFO_T;

/** O24
 *	pe histogram information parameter type
 *	- status[0] : [25:16]hist_bin_max, [09:00]hist_bin_min
 *	- status[1] : [25:16]hist_v_max, [09:00]hist_v_min
 *	- status[2] : [28:08]hist_max_bin_val, [05:00]hist_max_bin_num
 *	- status[3] : [21:00]hist_diff_sum
 *	- status[4] : [20:00]hist_detect_rgn_num
 *	- status[5] : [07:00]saturation status
 *	- status[6] : [07:00]motion status(from tnr block)
 *	- status[7] : [17:00]texture measure
 *	- status[8] : reserved
 *	- status[9] : reserved
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_COLOR_DOMAIN domain;	///< color domain
	UINT32 histo_ready;			///< histogram is valid, if 1, invalid otherwise.
	UINT32 average[3];			///< the average of all luma in the specified region Y or RGB
    UINT32 min;					///< the min of all luma in the specified region
	UINT32 max;					///< the max of all luma in the specified region
    UINT32 histogram[4][192];		///< histogram data of luma(histo[0~127]1st,[128~159]2nd,[160~191]3rd)
    UINT32 status[10];			///< histogram status
}
LX_PE_HST_HISTO2_INFO_T;


/**
 *	pe apl information parameter type
 */
typedef struct
{
	UINT32 status[2];          ///< apl status
}
LX_PE_HST_APL_INFO_T;

/**
 *	pe histogram operation parameter type
 */
typedef struct
{
	UINT32 src_apl_op;	///< src apl loading operation, 0:run, 1:stop
	UINT32 src_hist_op;	///< src histogarm loading operation, 0:run, 1:stop
	UINT32 lrc_hist_op;	///< lrcr histogarm loading operation, 0:run, 1:stop
}
LX_PE_HST_HISTO_OPR_T;

/**
 *	pe histogram configuration parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_HST_HISTO_OPR_T opr;	///< histo operation
}
LX_PE_HST_HISTO_CFG_T;

/**
 *	pe hdr information parameter type
 *	- status[0]  : min
 *	- status[1]  : max
 *	- status[2]  : bistogram bin 00
 *	- ......
 *	- status[33] : bistogram bin 31
 *	- others     : reserved
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
    UINT32 status[40];			///< histogram status
}
LX_PE_HST_HDR_INFO_T;

/**
 *	pe dynamic contrast lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< size of block apl table in ddr reg type
	union
	{
		UINT32 *data;				///< [9:0] apl_0, [19:10] apl_1, [29:20] apl_2
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HST_BLK_APL_T;

/**
 *	pe blok apl ddr reg type
 */
typedef struct
{
	UINT32 apl_0                    :10;	//9:0
	UINT32 apl_1                    :10;	//19:10
	UINT32 apl_2                    :10;	//29:20
}
LX_PE_HST_BLK_APL_DDR_REG_T;

/***************************************************************************/
/* HDR */
/***************************************************************************/
/**
 *	pe hdr histo information parameter type
 *	- status[0]   : bistogram0 bin 000
 *	- ......
 *	- status[127] : bistogram1 bin 127
 *	- others      : reserved
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
    UINT32 status[300];			///< histogram status
}
LX_PE_HDR_HISTO_INFO_T;

/**
 *	pe hdr csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT32 type0;						///< type, see LX_PE_HDR_CSC_TYPE
	UINT16 coef0[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 ofst0[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
	UINT32 type1;						///< type, see LX_PE_HDR_CSC_TYPE
	UINT16 coef1[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 ofst1[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
	UINT32 type2;						///< type, see LX_PE_HDR_CSC_TYPE
	UINT16 coef2[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 ofst2[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
}
LX_PE_HDR_CSC_T;

/**
 *	pe hdr tone map lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 oper;				///< operation, [11:8]version [7:4]ctrl [3:0]hdrpath
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	union
	{
		UINT32 *data;				///< [9:0] y data, [25:16] x data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HDR_TONEMAP_LUT_T;

/**
 *	pe hdr eotf lut control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of lut_data
	union
	{
		UINT32 *data;			///< [31:0] lut data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HDR_EOTF_LUT_T;

/**
 *	pe hdr oetf lut control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of lut_data
	union
	{
		UINT32 *data;			///< [31:16] E | [15:0] O
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HDR_OETF_LUT_T;

/**
 *	pe hdr information parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of lut_data
	union
	{
		UINT32 *data;			///< [31:16] E | [15:0] O
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HDR_INFO_T;

/**
 *	pe hdr 3d lut info parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of lut_data
	union
	{
		UINT32 *data;			///< lut data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HDR_3D_LUT_INFO_T;

/**
 *	pe gamma enable parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 data[5];			///< data
}
LX_PE_HDR_GAMMA_EN_T;

/**
 *	pe color correction parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 data[30];		///< data
}
LX_PE_HDR_CCR_T;

/**
 *	pe hdr ygain lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of lut_data
	union
	{
		UINT32 *data;			///< lut data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_HDR_YGAIN_LUT_T;

/**
 *	pe hdr operation mode
 */
typedef union
{
	UINT32 udata32;
	struct {
	UINT32 connect      : 4;	///<  3: 0, connect,    0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg,7:h2s, see LX_HDR_MODE_T
	UINT32 hdrtone      : 4;	///<  7: 4, hdr tone,   0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg,7:h2s, see LX_HDR_MODE_T
	UINT32 hdrcase      : 4;    ///< 11: 8, hdr case,   0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg,7:h2s, see LX_HDR_MODE_T
	UINT32 colmtry      : 3;    ///< 14:12, colorimetry,0:601,1:709,2:2020
	UINT32 hdr_off      : 2;    ///< 16:15, hdr_off,    0:normal,1:hdr_off,2:pcc_only
	UINT32 cur_mod      : 4;	///< 20:17, cur_mod(RO),0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg,7:h2s, see LX_HDR_MODE_T
	UINT32 sup_mod      : 4;	///< 24:21, sup_mod,[25]prime, 0:no,1:yes
	};
}
LX_PE_HDR_OP_MD_T;

/**
 *	pe hdr mode info.
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 data[5];			///< data, [0]:LX_PE_HDR_OP_MD_T, [1]~[4]:reserved
}
LX_PE_HDR_MODE_INFO_T;

/**
*	pe hdr lllut
*/
typedef struct
{
	LX_PE_WIN_ID win_id;
	unsigned char lllut_en;
	unsigned char lllut_csc_en;
	unsigned short lllut_r[128];
	unsigned short lllut_g[128];
	unsigned short lllut_b[128];
	short matrix[9];
	unsigned char blend_in_sel;
	short r2y_matrix[3];
	unsigned short blend_lut_x[6];
	unsigned short blend_lut_y[6];
	unsigned short hue_gain;
	unsigned short sat_gain;
}
LX_PE_HDR_LLLUT_T;

/***************************************************************************/
/* WIN : Window control */
/***************************************************************************/

/***************************************************************************/
/* CSC : Color Space Conversion */
/***************************************************************************/
/**
 *	pe xvYCC control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 enable;			///< enable xvYCC, 1:on, 0:off
	UINT8 scaler;			///< scaling factor, 0~255(255 = x1.0)
}
LX_PE_CSC_XVYCC_T;

/**
 *	pe color gamut control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT16 matrix[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix, primary color correction
}
LX_PE_CSC_GAMUT_T;

/**
 *	pe post csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT32 type;						///< type, see LX_PE_POST_CSC_TYPE
	UINT16 matrix[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 offset[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
	UINT16 coeff0[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix 0
	UINT16 coeff1[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix 1
	UINT16 offst0[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset 0
}
LX_PE_CSC_POST_T;

/**
 *	input csc type(Ref:v4l2_ext_vpq_black_level_type in videodev2-ext.h)
 */
typedef enum
{
    PE_ICSC_OFF,
    PE_ICSC_Y709_LINEAR_LIMIT_HIGH,
    PE_ICSC_Y709_BYPASS,
    PE_ICSC_RGB_Y709_LINEAR_LOW,
    PE_ICSC_RGB_Y709_LIMIT_HIGH,
    PE_ICSC_Y709_COMP_LOW,
    PE_ICSC_AV_RF_EXTENSION,
    PE_ICSC_RGB_BT2020_LINEAR_LOW,
    PE_ICSC_RGB_BT2020_LIMIT_HIGH,
    PE_ICSC_RGB_Y601_LINEAR_LOW,
    PE_ICSC_RGB_Y601_LIMIT_HIGH,
    PE_ICSC_Y709_LINEAR_LIMIT_HIGH_420,	///< 20191011,add new for hdmi420(AVTASK-273)
    PE_ICSC_MAX
}
LX_PE_ICSC_TYPE;

/**
 *	input csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT32 enable;						///< see LX_PE_ICSC_TYPE
	UINT16 matrix[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 offset[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
}
LX_PE_CSC_INPUT_T;

/**
*	post lllut  parameter type o20
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  lllut_en; 
	UINT8  lllut_csc_en; 
	UINT16 lllut_r[128];
	UINT16 lllut_g[128];
	UINT16 lllut_b[128];
	UINT16 matrix[9];
	UINT8  blend_in_sel;
	UINT16 r2y_matrix[3];
	UINT16 blend_lut_x[6];
	UINT16 blend_lut_y[6];
	UINT8  hue_gain;
	UINT8  sat_gain;
}
LX_PE_CSC_LLLUT_CTRL_T;

/**
*	csc_post_pcc_lut  parameter type o26
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 sat_gain;
	UINT32 hue_comp_gain;
	UINT32 sat_comp_gain;
	UINT32 luma_gain_lut_x[4];
	UINT32 luma_gain_lut_y[4];
	UINT32 sat_gain_lut_x[5];
	UINT32 sat_gain_lut_y[5];
}
LX_PE_CSC_POST_PCC_CTRL_T;

/***************************************************************************/
/* CMG : Color Management */
/***************************************************************************/

/**
 *	pe color enhancement enable parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 enable;			///< cen enable, 0:off,1:on
}
LX_PE_CMG_ENABLE_T;

/**
 *	pe color enhancement region enable parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 enable[LX_PE_CMG_REGION_NUM];			///< enable region 0 ~ 15
	UINT8 show_region[LX_PE_CMG_REGION_NUM];	///< show region 0 ~ 15, for debug
}
LX_PE_CMG_REGION_ENABLE_T;

/**
 *	pe color enhancement region parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;					///< window id
	UINT32 region_num;						///< region number, 0~15
	UINT16 hue_x[LX_PE_CMG_TBLPOINT];		///< hue input, 0~512~1023(0~360~720 degree)
	UINT8 hue_g[LX_PE_CMG_TBLPOINT];		///< hue gain, 0~127
	UINT8 sat_x[LX_PE_CMG_TBLPOINT];		///< saturation input, 0~100
	UINT8 sat_g[LX_PE_CMG_TBLPOINT];		///< saturation gain, 0~127
	UINT8 val_x[LX_PE_CMG_TBLPOINT];		///< value input, 0~255
	UINT8 val_g[LX_PE_CMG_TBLPOINT];		///< value gain, 0~127
}
LX_PE_CMG_REGION_T;

/**
 *	pe color enhancement region parameter type for all region
 */
typedef struct
{
	UINT16 hue_x[LX_PE_CMG_TBLPOINT];		///< hue input, 0~512~1023(0~360~720 degree)
	UINT8 hue_g[LX_PE_CMG_TBLPOINT];		///< hue gain, 0~127
	UINT8 sat_x[LX_PE_CMG_TBLPOINT];		///< saturation input, 0~100
	UINT8 sat_g[LX_PE_CMG_TBLPOINT];		///< saturation gain, 0~127
	UINT8 val_x[LX_PE_CMG_TBLPOINT];		///< value input, 0~255
	UINT8 val_g[LX_PE_CMG_TBLPOINT];		///< value gain, 0~127
}
LX_PE_CMG_REGION_ONE_T;

/**
 *	pe color enhancement region parameter type for all region
 */
typedef struct
{
	LX_PE_WIN_ID win_id;					///< window id
	LX_PE_CMG_REGION_ONE_T cen_region_lut[LX_PE_CMG_REGION_NUM];
}
LX_PE_CMG_REGION_ALL_T;

/**
 *	pe color enhancement region control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT32 region_num;							///< region number, 0~15
	SINT8 region_delta[LX_PE_CMG_DELTANUM];		///< region delta(offset), -128 ~ 127, [0]h [1]s [2]v [3]g [4]b [5]r
	UINT8 master_gain;							///< region master gain, 0~128~255
	UINT32 dynamic_ui;
}
LX_PE_CMG_REGION_CTRL_T;

/**
 *	pe color enhancement global control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	SINT16 global_delta[LX_PE_CMG_DELTANUM];	///< global gain,-512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
}
LX_PE_CMG_GLOBAL_CTRL_T;

/**
 *	pe color enhancement color control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT16 saturation;		///< saturation gain
}
LX_PE_CMG_COLOR_CTRL_T;

/**
 *  pe clear white control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 cw_en;			///< clear white enable
	UINT32 gain_sel;		///< Y-CR gain sel, '0' = use Y level gain, '1' = use CR region gain
	UINT32 gain_x[5];		///< gain table x0~4
	UINT32 gain_y[5];		///< gain table y0~4
	UINT32 region_sel;		///< color region sel 1=enable, bit control.(0x0 ~ 0xff)
	UINT32 region_gain;		///< color region gain, default : "64"( 0 ~ 255(1~400%))
}
LX_PE_CMG_CW_CTRL_T;

/**
 *  pe clear white control parameter type o20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16  cw_hue_x[LX_PE_CMG_TBLPOINT];
    UINT8   cw_hue_y[LX_PE_CMG_TBLPOINT];
    UINT8   cw_sat_x[LX_PE_CMG_TBLPOINT];
    UINT8   cw_sat_y[LX_PE_CMG_TBLPOINT];
    UINT8   cw_val_x[LX_PE_CMG_TBLPOINT];
    UINT8   cw_val_y[LX_PE_CMG_TBLPOINT];
}
LX_PE_CMG_CW_TABLE_CTRL_T;

/**
 *  pe clear white rgb gain control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 g_gain;			///< User Control, G_Gain  (resolution = 2^(-9), 0~192~255)
	UINT32 b_gain;			///< User Control, B_Gain  (resolution = 2^(-9), 0~192~255)
	UINT32 r_gain;			///< User Control, R_Gain  (resolution = 2^(-9), 0~192~255)
}
LX_PE_CMG_CW_GAIN_CTRL_T;

/**
 *	pe saturation gain LUT type
 */
typedef struct
{
    LX_PE_WIN_ID win_id;    ///< window id
    UINT32       x[9];      ///< dynamic saturation gainLUT_x
    UINT32       y[9];      ///< dynamic saturation gainLUT_y
}
LX_PE_CMG_SAT_GAIN_LUT_T;

/**
 *  pe vspcc control parameter type o20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8	satTarget;
	UINT8	objMapGainLUT_x[4];
	UINT8	objMapGainLUT_y[4];
	UINT8	faceMapGainLUT_x[4];
	UINT8	faceMapGainLUT_y[4];
	UINT16	hue_x[LX_PE_CMG_TBLPOINT];
	UINT8 	hue_g[LX_PE_CMG_TBLPOINT];
	UINT8 	sat_x[LX_PE_CMG_TBLPOINT];
	UINT8 	sat_g[LX_PE_CMG_TBLPOINT];
	UINT8 	val_x[LX_PE_CMG_TBLPOINT];
	UINT8 	val_g[LX_PE_CMG_TBLPOINT];
}
LX_PE_CMG_VSPCC_CTRL_T;
/**
*	pe saturation control parameter type o20
*/
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  saturation_cr_mode; 						///< low saturation_cr_mode
	UINT16 saturation_region_gain; 					///< saturation_region_gainposition
	UINT16 dse_h_x[LX_PE_CMG_TBLPOINT];				///< hue x_range_max
	UINT16 dse_h_y[LX_PE_CMG_TBLPOINT];				///< hue y_range_min
	UINT16 dse_y_x[LX_PE_CMG_TBLPOINT];				///< Y x_range_max
	UINT16 dse_y_y[LX_PE_CMG_TBLPOINT];				///< Y y_range_min
	UINT16 sSaturationLUT_x[16];
	UINT16 sSaturationLUT_y[16];
	UINT8  region_onoff[LX_PE_CMG_REGION_NUM];		///< region_onoff
}
LX_PE_CMG_DSE_CTRL_T;

/******************/
/* for webOs26 O26**/
/******************/

// o26
/**
 *	pe color enhancement region parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;					///< window id
	UINT32 region_num;						///< region number, 0~15
	UINT8  aiGainNum;	//Ãß°¡ o26
	UINT16 hue_x[LX_PE_CMG_TBLPOINT];		///< hue input, 0~512~1023(0~360~720 degree)
	UINT8 hue_g[LX_PE_CMG_TBLPOINT];		///< hue gain, 0~127
	UINT8 sat_x[LX_PE_CMG_TBLPOINT];		///< saturation input, 0~100
	UINT8 sat_g[LX_PE_CMG_TBLPOINT];		///< saturation gain, 0~127
	UINT8 val_x[LX_PE_CMG_TBLPOINT];		///< value input, 0~255
	UINT8 val_g[LX_PE_CMG_TBLPOINT];		///< value gain, 0~127
}
LX_PE_CMG_REGION2_T;

/**
 *  pe vspcc control parameter type o26
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8	headMap0Gain;
	UINT8	headMap0GainLUT_x[4];
	UINT8	headMap0GainLUT_y[4];
	UINT8	bodyMap0Gain;
	UINT8	bodyMap0GainLUT_x[4];
	UINT8	bodyMap0GainLUT_y[4];
	UINT8	textMap0Gain;
	UINT8	textMap0GainLUT_x[4];
	UINT8	textMap0GainLUT_y[4];
	UINT8	motionMap0Gain;
	UINT8	motionMap0GainLUT_x[4];
	UINT8	motionMap0GainLUT_y[4];
	UINT8	headMap1Gain;
	UINT8	headMap1GainLUT_x[4];
	UINT8	headMap1GainLUT_y[4];
	UINT8	bodyMap1Gain;
	UINT8	bodyMap1GainLUT_x[4];
	UINT8	bodyMap1GainLUT_y[4];
	UINT8	textMap1Gain;
	UINT8	textMap1GainLUT_x[4];
	UINT8	textMap1GainLUT_y[4];
	UINT8	motionMap1Gain;
	UINT8	motionMap1GainLUT_x[4];
	UINT8	motionMap1GainLUT_y[4];
}
LX_PE_CMG_VSPCC2_CTRL_T;



/***************************************************************************/
/* NRD : Noise Reduction*/
/***************************************************************************/
/**
 *	pe digital noise reduction control EASY parameter type
 *	for every chip while bringup
 */
 /**
 *dnr_max,  	reg_dnr_max_enable,      	data[0],
 *dc_bnr, 	reg_dc_bnr_enable,         	data[1],
 *dc_bnr, 	reg_dc_bnr_mastergain,  	data[2],
 *dc_bnr, 	reg_dc_bnr_chromagain,  	data[3],
 *ac_bnr, 	reg_bnr_ac_h_en,           	data[4],
 *ac_bnr, 	reg_bnr_ac_v_en,           	data[5],
 *ac_bnr, 	reg_bnr_ac_h_chroma_en,    data[6],
 *ac_bnr, 	reg_bnr_ac_v_chroma_en,    data[7],
 *ac_bnr, 	reg_ac_master_y_gain,      	data[8],
 *mnr,    		reg_mnr_enable,            	data[9],
 *mnr,    		reg_mnr_master_gain,      	data[10]
 *mnr,    		reg_mnr_chroma_en,         	data[11]
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 data[12];	///< dnr data
}
LX_PE_NRD_SUDO_DNR_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 data[12];	///< dnr data
}
LX_PE_NRD_EASY_DNR_CMN_T;
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT16 data[12];	///< dnr data
}
LX_PE_NRD_EASY_DCNT_CMN_T;
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 data[12];	///< dnr data
}
LX_PE_LED_EASY_DCNT_CMN_T;




/**
 *	pe digital noise reduction detailed control parameter type
 *	ver.5, for H15Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* dc bnr 18 */
	UINT8 reg_dc_var_en;				///< dc_bnr_ctrl_2, 0, dc_var_en
	UINT8 reg_dc_motion_en;				///< dc_bnr_ctrl_2, 1, dc_motion_en
	UINT8 reg_dc_protection_en;			///< dc_bnr_ctrl_2, 2, dc_protection_en
	UINT8 reg_dc_detail_en;				///< dc_bnr_ctrl_2, 3, dc_detail_en
	UINT8 reg_dc_blur_sel;				///< dc_bnr_ctrl_0, 2, dc_blur_sel
	UINT8 reg_dc_motion_max;			///< dc_bnr_ctrl_0, 23:16, dc_motion_max
	UINT8 reg_dc_motion_min;			///< dc_bnr_ctrl_0, 31:24, dc_motion_min
	UINT8 reg_dc_detail_max;			///< dc_bnr_ctrl_1,  7: 0, dc_detail_max
	UINT8 reg_dc_detail_min;			///< dc_bnr_ctrl_1, 15: 8, dc_detail_min
	UINT8 reg_var_v_gain;				///< dc_bnr_ctrl_1, 23:20, var_v_gain
	UINT8 reg_var_h_gain;				///< dc_bnr_ctrl_1, 27:24, var_h_gain
	UINT8 reg_var_cut_resolution;		///< dc_bnr_ctrl_1, 31:28, var_cut_resolution
	UINT8 reg_dc_global_motion_th;		///< dc_bnr_ctrl_2,  7: 4, dc_global_motion_th
	UINT8 reg_dc_protection_th;			///< dc_bnr_ctrl_2, 31:24, dc_protection_th
	UINT8 reg_dc_bnr_var_th0;			///< dc_bnr_ctrl_3, 31:24, dc_bnr_var_th0
	UINT8 reg_dc_bnr_var_th1;			///< dc_bnr_ctrl_3, 23:16, dc_bnr_var_th1
	UINT8 reg_dc_bnr_var_th2;			///< dc_bnr_ctrl_3, 15: 8, dc_bnr_var_th2
	UINT8 reg_dc_bnr_var_th3;			///< dc_bnr_ctrl_3,  7: 0, dc_bnr_var_th3
	/* ac bnr 27 */
	UINT8 reg_bnr_ac_diff_min_v_th;		///< ac_bnr_ctrl_0, 15: 8, bnr_ac_diff_min_v_th
	UINT8 reg_bnr_ac_diff_min_h_th;		///< ac_bnr_ctrl_0, 23:16, bnr_ac_diff_min_h_th
	UINT8 reg_bnr_ac_global_motion_th;	///< ac_bnr_ctrl_1,  7: 0, bnr_ac_global_motion_th
	UINT8 reg_bnr_ac_h_acness_max;		///< ac_bnr_ctrl_1, 15: 8, reg_bnr_ac_h_acness_max
	UINT8 reg_bnr_ac_h_acness_min;		///< ac_bnr_ctrl_1, 23:16, reg_bnr_ac_h_acness_min
	UINT8 reg_bnr_ac_v_acness_max;		///< ac_bnr_ctrl_4, 23:16, reg_bnr_ac_v_acness_max
	UINT8 reg_bnr_ac_v_acness_min;		///< ac_bnr_ctrl_4, 31:24, reg_bnr_ac_v_acness_min
	UINT8 reg_bnr_ac_motion_0;			///< ac_bnr_ctrl_2, 31:24, reg_bnr_ac_motion_0
	UINT8 reg_bnr_ac_motion_1;			///< ac_bnr_ctrl_2, 24:16, reg_bnr_ac_motion_1
	UINT8 reg_bnr_ac_motion_2;			///< ac_bnr_ctrl_2, 15: 8, reg_bnr_ac_motion_2
	UINT8 reg_bnr_ac_motion_3;			///< ac_bnr_ctrl_2,  7: 0, reg_bnr_ac_motion_3
	UINT8 reg_bnr_ac_detail_th1;		///< ac_bnr_ctrl_5, 31:24, bnr_ac_detail_th1
	UINT8 reg_bnr_ac_detail_th2;		///< ac_bnr_ctrl_5, 23:16, bnr_ac_detail_th2
	UINT8 reg_bnr_ac_detail_th3;		///< ac_bnr_ctrl_5, 15: 8, bnr_ac_detail_th3
	UINT8 reg_bnr_ac_detail_th4;		///< ac_bnr_ctrl_5,  7: 0, bnr_ac_detail_th4
	UINT8 reg_bnr_ac_pos_gain_h0;		///< ac_bnr_ctrl_6, 23:16, bnr_ac_pos_gain_h0
	UINT8 reg_bnr_ac_pos_gain_h1;		///< ac_bnr_ctrl_6, 15: 8, bnr_ac_pos_gain_h1
	UINT8 reg_bnr_ac_pos_gain_h2;		///< ac_bnr_ctrl_6,  7: 0, bnr_ac_pos_gain_h2
	UINT8 reg_bnr_ac_pos_gain_h3;		///< ac_bnr_ctrl_7, 31:24, bnr_ac_pos_gain_h3
	UINT8 reg_bnr_ac_pos_gain_l0;		///< ac_bnr_ctrl_7, 23:16, bnr_ac_pos_gain_l0
	UINT8 reg_bnr_ac_pos_gain_l1;		///< ac_bnr_ctrl_7, 15: 8, bnr_ac_pos_gain_l1
	UINT8 reg_bnr_ac_pos_gain_l2;		///< ac_bnr_ctrl_7,  7: 0, bnr_ac_pos_gain_l2
	UINT8 reg_bnr_ac_pos_gain_l3;		///< ac_bnr_ctrl_8, 31:24, bnr_ac_pos_gain_l3
	UINT8 reg_bnr_ac_detail_max;		///< detail_ctrl,  7: 0, bnr_ac_detail_max
	UINT8 reg_bnr_ac_detail_min;		///< detail_ctrl, 15: 8, bnr_ac_detail_min
	UINT8 reg_bnr_diff_l;				///< detail_ctrl, 23:16, bnr_diff_l
	UINT8 reg_bnr_diff_p;				///< detail_ctrl, 31:24, bnr_diff_p
	/* mnr 18 */
	UINT8 reg_h_expand;					///< mnr_ctrl_0, 4, h_expand
	UINT8 reg_gain_flt_size;			///< mnr_ctrl_0, 5, gain_flt_size
	UINT8 reg_mnr_s1_mmd_min;			///< mnr_ctrl_1,  7: 0, mnr_s1_mmd_min
	UINT8 reg_mnr_s2_ratio_min;			///< mnr_ctrl_1, 15: 8, mnr_s2_ratio_min
	UINT8 reg_mnr_s2_ratio_max;			///< mnr_ctrl_1, 23:16, mnr_s2_ratio_max
	UINT8 reg_mnr_s2_mmd_min;			///< mnr_ctrl_1, 31:24, mnr_s2_mmd_min
	UINT8 reg_filter_x0;				///< mnr_ctrl_3,  7: 0, filter_x0
	UINT8 reg_filter_x1;				///< mnr_ctrl_3, 15: 8, filter_x1
	UINT8 reg_filter_y0;				///< mnr_ctrl_3, 23:16, filter_y0
	UINT8 reg_filter_y1;				///< mnr_ctrl_3, 31:24, filter_y1
	UINT8 reg_motion_mnr_en;			///< mnr_ctrl_4, 0, motion_mnr_en
	UINT8 reg_motion_mnr_filter;		///< mnr_ctrl_4, 1, motion_mnr_filter
	UINT8 reg_mnr_motion_min;			///< mnr_ctrl_4, 23:16, mnr_motion_min
	UINT8 reg_mnr_motion_max;			///< mnr_ctrl_4, 31:24, mnr_motion_max
	UINT8 reg_motion_mnr_x0;			///< mnr_ctrl_5,  7: 0, motion_mnr_x0
	UINT8 reg_motion_mnr_x1;			///< mnr_ctrl_5, 15: 8, motion_mnr_x1
	UINT8 reg_motion_mnr_y0;			///< mnr_ctrl_5, 23:16, motion_mnr_y0
	UINT8 reg_motion_mnr_y1;			///< mnr_ctrl_5, 31:24, motion_mnr_y1
}
LX_PE_NRD_DNR5_DETAIL_T;

#define LX_PE_NRD_DNR6_CMN_DATA_SIZE	15
#define LX_PE_NRD_DNR6_DTL_DCBNR_SIZE	30
#define LX_PE_NRD_DNR6_DTL_ACBNR_SIZE	28
#define LX_PE_NRD_DNR6_DTL_MSQNR_SIZE	17

/**
 *	pe digital noise reduction common control parameter type
 *	ver.6, for H15
 *  001._[MAX_CTRL]_0xC8007194_[0____]_1_UINT8__common[00]:_dnr_max_ctrl,__reg_dnr_max_enable,
 *  002._[DC_BNR__]_0xC80071BC_[0____]_1_UINT8__common[01]:_dc_bnr_ctrl_0,_reg_dc_bnr_enable,
 *  003._[DC_BNR__]_0xC80071C4_[15:10]_6_UINT8__common[02]:_dc_bnr_ctrl_2,_reg_dc_bnr_mastergain,
 *  004._[DC_BNR__]_0xC80071C4_[23:16]_8_UINT8__common[03]:_dc_bnr_ctrl_2,_reg_dc_bnr_chromagain,
 *  005._[AC_BNR__]_0xC80071D4_[0____]_1_UINT8__common[04]:_ac_bnr_ctrl_0,_reg_bnr_ac_h_en,
 *  006._[AC_BNR__]_0xC80071D4_[1____]_1_UINT8__common[05]:_ac_bnr_ctrl_0,_reg_bnr_ac_v_en,
 *  007._[AC_BNR__]_0xC80071D4_[2____]_1_UINT8__common[06]:_ac_bnr_ctrl_0,_reg_bnr_ac_h_chroma_en,
 *  008._[AC_BNR__]_0xC80071D4_[3____]_1_UINT8__common[07]:_ac_bnr_ctrl_0,_reg_bnr_ac_v_chroma_en,
 *  009._[AC_BNR__]_0xC80071D4_[5:4__]_2_UINT8__common[08]:_ac_bnr_ctrl_0,_reg_bnr_ac_acness_resol_h,
 *  010._[AC_BNR__]_0xC8007204_[15:10]_6_UINT8__common[09]:_ac_bnr_ctrl_9,_reg_ac_master_gain,
 *  011._[MNR_____]_0xC80071A0_[0____]_1_UINT8__common[10]:_mnr_ctrl_0,____reg_mnr_enable,
 *  012._[MNR_____]_0xC80071A0_[15:8_]_8_UINT8__common[11]:_mnr_ctrl_0,____reg_mnr_master_gain,
 *  013._[MNR_____]_0xC80071A0_[23:16]_8_UINT8__common[12]:_mnr_ctrl_0,____reg_chroma_master_gain,
 *  014._[MNR_____]_0xC80071A8_[23:16]_8_UINT8__common[13]:_mnr_ctrl_2,____reg_mnr_v_gain,
 *  015._[MNR_____]_0xC80071A8_[31:24]_8_UINT8__common[14]:_mnr_ctrl_2,____reg_mnr_h_gain,
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 data[LX_PE_NRD_DNR6_CMN_DATA_SIZE];	///< dnr data
}
LX_PE_NRD_DNR6_CMN_T;
/**
 *	pe digital noise reduction detail control parameter type
 *	ver.6, for H15
 *  016._[DC_BNR__]_0xC80071C4_[0____]_1_UINT8__dc_bnr[00]:_dc_bnr_ctrl_2,_reg_dc_var_en,
 *  017._[DC_BNR__]_0xC80071C4_[1____]_1_UINT8__dc_bnr[01]:_dc_bnr_ctrl_2,_reg_dc_motion_en,
 *  018._[DC_BNR__]_0xC80071C4_[2____]_1_UINT8__dc_bnr[02]:_dc_bnr_ctrl_2,_reg_dc_protection_en,
 *  019._[DC_BNR__]_0xC80071C4_[3____]_1_UINT8__dc_bnr[03]:_dc_bnr_ctrl_2,_reg_dc_detail_en,
 *  020._[DC_BNR__]_0xC80071BC_[3:2__]_2_UINT8__dc_bnr[04]:_dc_bnr_ctrl_0,_reg_dc_blur_sel,
 *  021._[DC_BNR__]_0xC80071BC_[23:16]_8_UINT8__dc_bnr[05]:_dc_bnr_ctrl_0,_reg_dc_motion_max,
 *  022._[DC_BNR__]_0xC80071BC_[31:24]_8_UINT8__dc_bnr[06]:_dc_bnr_ctrl_0,_reg_dc_motion_min,
 *  023._[DC_BNR__]_0xC80071C0_[7:0__]_8_UINT8__dc_bnr[07]:_dc_bnr_ctrl_1,_reg_dc_detail_max,
 *  024._[DC_BNR__]_0xC80071C0_[15:8_]_8_UINT8__dc_bnr[08]:_dc_bnr_ctrl_1,_reg_dc_detail_min,
 *  025._[DC_BNR__]_0xC80071C0_[23:20]_4_UINT8__dc_bnr[09]:_dc_bnr_ctrl_1,_reg_var_v_gain,
 *  026._[DC_BNR__]_0xC80071C0_[27:24]_4_UINT8__dc_bnr[10]:_dc_bnr_ctrl_1,_reg_var_h_gain,
 *  027._[DC_BNR__]_0xC80071C0_[31:28]_4_UINT8__dc_bnr[11]:_dc_bnr_ctrl_1,_reg_var_cut_resolution,
 *  028._[DC_BNR__]_0xC80071C4_[7:4__]_4_UINT8__dc_bnr[12]:_dc_bnr_ctrl_2,_reg_dc_global_motion_th,
 *  029._[DC_BNR__]_0xC80071C4_[31:24]_8_UINT8__dc_bnr[13]:_dc_bnr_ctrl_2,_reg_dc_protection_th,
 *  030._[DC_BNR__]_0xC80071C8_[7:0__]_8_UINT8__dc_bnr[14]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th3,
 *  031._[DC_BNR__]_0xC80071C8_[15:8_]_8_UINT8__dc_bnr[15]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th2,
 *  032._[DC_BNR__]_0xC80071C8_[23:16]_8_UINT8__dc_bnr[16]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th1,
 *  033._[DC_BNR__]_0xC80071C8_[31:24]_8_UINT8__dc_bnr[17]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th0,
 *  034._[DC_BNR__]_0xC80071C4_[8____]_1_UINT8__dc_bnr[18]:_dc_bnr_ctrl_2,_reg_detail_sel,
 *  035._[DETAIL__]_0xC80071B8_[7:0__]_8_UINT8__dc_bnr[19]:_detail_ctrl,___reg_bnr_ac_detail_max,
 *  036._[DETAIL__]_0xC80071B8_[15:8_]_8_UINT8__dc_bnr[20]:_detail_ctrl,___reg_bnr_ac_detail_min,
 *  037._[DETAIL__]_0xC80071B8_[23:16]_8_UINT8__dc_bnr[21]:_detail_ctrl,___reg_bnr_diff_l,
 *  038._[DETAIL__]_0xC80071B8_[31:24]_8_UINT8__dc_bnr[22]:_detail_ctrl,___reg_bnr_diff_p,
 *  039._[SC_BNR__]_0xC800726C_[0____]_1_UINT8__dc_bnr[23]:_sc_bnr_ctrl_0,_reg_sc_bnr_en,
 *  040._[SC_BNR__]_0xC8007280_[7:0__]_8_UINT8__dc_bnr[24]:_sc_bnr_ctrl_5,_reg_pos_gain_3,
 *  041._[SC_BNR__]_0xC8007280_[15:8_]_8_UINT8__dc_bnr[25]:_sc_bnr_ctrl_5,_reg_pos_gain_2,
 *  042._[SC_BNR__]_0xC8007280_[23:16]_8_UINT8__dc_bnr[26]:_sc_bnr_ctrl_5,_reg_pos_gain_1,
 *  043._[TEXTURE_]_0xC800728C_[2:0__]_3_UINT8__dc_bnr[27]:_texture_ctrl_0,reg_texture_cnt_div,
 *  044._[TEXTURE_]_0xC800728C_[15:8_]_8_UINT8__dc_bnr[28]:_texture_ctrl_0,reg_texture_cnt_mul,
 *  045._[TEXTURE_]_0xC800728C_[31:24]_8_UINT8__dc_bnr[29]:_texture_ctrl_0,reg_cross_th,
 *  046._[AC_BNR__]_0xC80071D4_[15:8_]_8_UINT8__ac_bnr[00]:_ac_bnr_ctrl_0,_reg_bnr_ac_diff_min_v_th,
 *  047._[AC_BNR__]_0xC80071D4_[23:16]_8_UINT8__ac_bnr[01]:_ac_bnr_ctrl_0,_reg_bnr_ac_diff_min_h_th,
 *  048._[AC_BNR__]_0xC80071D8_[7:0__]_8_UINT8__ac_bnr[02]:_ac_bnr_ctrl_1,_reg_bnr_ac_global_motion_th,
 *  049._[AC_BNR__]_0xC80071D8_[15:8_]_8_UINT8__ac_bnr[03]:_ac_bnr_ctrl_1,_reg_bnr_ac_h_acness_max,
 *  050._[AC_BNR__]_0xC80071E8_[23:16]_8_UINT8__ac_bnr[04]:_ac_bnr_ctrl_4,_reg_bnr_ac_v_acness_max,
 *  051._[AC_BNR__]_0xC80071D8_[23:16]_8_UINT8__ac_bnr[05]:_ac_bnr_ctrl_1,_reg_bnr_ac_h_acness_min,
 *  052._[AC_BNR__]_0xC80071E8_[31:24]_8_UINT8__ac_bnr[06]:_ac_bnr_ctrl_4,_reg_bnr_ac_v_acness_min,
 *  053._[AC_BNR__]_0xC80071E8_[7:6__]_2_UINT8__ac_bnr[07]:_ac_bnr_ctrl_4,_reg_bnr_ac_acness_resol_v,
 *  054._[AC_BNR__]_0xC80071DC_[7:0__]_8_UINT8__ac_bnr[08]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_3,
 *  055._[AC_BNR__]_0xC80071DC_[15:8_]_8_UINT8__ac_bnr[09]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_2,
 *  056._[AC_BNR__]_0xC80071DC_[23:16]_8_UINT8__ac_bnr[10]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_1,
 *  057._[AC_BNR__]_0xC80071DC_[31:24]_8_UINT8__ac_bnr[11]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_0,
 *  058._[AC_BNR__]_0xC80071E4_[7:0__]_8_UINT8__ac_bnr[12]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_3,
 *  059._[AC_BNR__]_0xC80071E4_[15:8_]_8_UINT8__ac_bnr[13]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_2,
 *  060._[AC_BNR__]_0xC80071E4_[23:16]_8_UINT8__ac_bnr[14]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_1,
 *  061._[AC_BNR__]_0xC80071E4_[31:24]_8_UINT8__ac_bnr[15]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_0,
 *  062._[AC_BNR__]_0xC80071F4_[31:24]_8_UINT8__ac_bnr[16]:_ac_bnr_ctrl_6,_reg_bnr_ac_detail_gain_th,
 *  063._[AC_BNR__]_0xC80071F0_[7:0__]_8_UINT8__ac_bnr[17]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th4,
 *  064._[AC_BNR__]_0xC80071F0_[15:8_]_8_UINT8__ac_bnr[18]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th3,
 *  065._[AC_BNR__]_0xC80071F0_[23:16]_8_UINT8__ac_bnr[19]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th2,
 *  066._[AC_BNR__]_0xC80071F0_[31:24]_8_UINT8__ac_bnr[20]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th1,
 *  067._[AC_BNR__]_0xC80071F8_[31:24]_8_UINT8__ac_bnr[21]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_h3,
 *  068._[AC_BNR__]_0xC80071F4_[7:0__]_8_UINT8__ac_bnr[22]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h2,
 *  069._[AC_BNR__]_0xC80071F4_[15:8_]_8_UINT8__ac_bnr[23]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h1,
 *  070._[AC_BNR__]_0xC80071F4_[23:16]_8_UINT8__ac_bnr[24]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h0,
 *  071._[AC_BNR__]_0xC80071F8_[7:0__]_8_UINT8__ac_bnr[25]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l2,
 *  072._[AC_BNR__]_0xC80071F8_[15:8_]_8_UINT8__ac_bnr[26]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l1,
 *  073._[AC_BNR__]_0xC80071F8_[23:16]_8_UINT8__ac_bnr[27]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l0,
 *  074._[MNR_____]_0xC80071A0_[5:4__]_2_UINT8__mosqnr[00]:_mnr_ctrl_0,____reg_h_expand,
 *  075._[MNR_____]_0xC80071A0_[6____]_1_UINT8__mosqnr[01]:_mnr_ctrl_0,____reg_gain_flt_size,
 *  076._[MNR_____]_0xC80071A4_[7:0__]_8_UINT8__mosqnr[02]:_mnr_ctrl_1,____reg_mnr_s1_mmd_min,
 *  077._[MNR_____]_0xC80071A4_[15:8_]_8_UINT8__mosqnr[03]:_mnr_ctrl_1,____reg_mnr_s2_ratio_min,
 *  078._[MNR_____]_0xC80071A4_[23:16]_8_UINT8__mosqnr[04]:_mnr_ctrl_1,____reg_mnr_s2_ratio_max,
 *  079._[MNR_____]_0xC80071A4_[31:24]_8_UINT8__mosqnr[05]:_mnr_ctrl_1,____reg_mnr_s2_mmd_min,
 *  080._[MNR_____]_0xC80071AC_[7:0__]_8_UINT8__mosqnr[06]:_mnr_ctrl_3,____reg_filter_x0,
 *  081._[MNR_____]_0xC80071AC_[15:8_]_8_UINT8__mosqnr[07]:_mnr_ctrl_3,____reg_filter_x1,
 *  082._[MNR_____]_0xC80071AC_[23:16]_8_UINT8__mosqnr[08]:_mnr_ctrl_3,____reg_filter_y0,
 *  083._[MNR_____]_0xC80071AC_[31:24]_8_UINT8__mosqnr[09]:_mnr_ctrl_3,____reg_filter_y1,
 *  084._[MNR_____]_0xC80071B0_[0____]_1_UINT8__mosqnr[10]:_mnr_ctrl_4,____reg_motion_mnr_en,
 *  085._[MNR_____]_0xC80071B0_[2:1__]_2_UINT8__mosqnr[11]:_mnr_ctrl_4,____reg_motion_mnr_filter,
 *  086._[MNR_____]_0xC80071B0_[4:3__]_2_UINT8__mosqnr[12]:_mnr_ctrl_4,____reg_motion_mnr_filter_c,
 *  087._[MNR_____]_0xC80071B0_[6:5__]_2_UINT8__mosqnr[13]:_mnr_ctrl_4,____reg_mnr_filter,
 *  088._[MNR_____]_0xC80071B0_[8:7__]_2_UINT8__mosqnr[14]:_mnr_ctrl_4,____reg_mnr_filter_c,
 *  089._[MNR_____]_0xC80071B0_[23:16]_8_UINT8__mosqnr[15]:_mnr_ctrl_4,____reg_mnr_motion_min,
 *  090._[MNR_____]_0xC80071B0_[31:24]_8_UINT8__mosqnr[16]:_mnr_ctrl_4,____reg_mnr_motion_max,
 */
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8 dc_bnr[LX_PE_NRD_DNR6_DTL_DCBNR_SIZE];	///< dc bnr
	UINT8 ac_bnr[LX_PE_NRD_DNR6_DTL_ACBNR_SIZE];	///< ac bnr
	UINT8 mosqnr[LX_PE_NRD_DNR6_DTL_MSQNR_SIZE];	///< mnr
}
LX_PE_NRD_DNR6_DETAIL_T;


/**
 * CHIP_DNR_DB_M16_T for HAL_VPQ_SetMpegNoiseReduction
 * 01  MAX_CTRL  	 reg_dnr_max_enable 		  	0x0094 0
 * 02  DC_BNR	 reg_dc_bnr_enable			0x00BC	 0
 * 03  DC_BNR	 reg_dc_bnr_mastergain		0x00C4	 15:10
 * 04  DC_BNR	 reg_dc_bnr_chromagain		0x00C4	 23:16
 * 05  AC_BNR	 reg_bnr_ac_h_en			  	0x00D4 0
 * 06  AC_BNR	 reg_bnr_ac_v_en			  	0x00D4 1
 * 07  AC_BNR	 reg_bnr_ac_h_chroma_en 	  	0x00D4 2
 * 08  AC_BNR	 reg_bnr_ac_v_chroma_en 	  	0x00D4 3
 * 09  AC_BNR	 reg_ac_master_gain 		  	0x0104 15:10
 * 10  MNR		 reg_mnr_enable 			  	0x00A0 0
 * 11  MNR		 reg_mnr_master_gain		  	0x00A0 15:8
 * 12  MNR		 reg_mnr_chroma_en			0x00A0	 3
 *-------------------------------------------------------------
 * 13  DC_BNR	 reg_dc_var_en				0x00C4	 0
 * 14  DC_BNR	 reg_dc_motion_en				0x00C4	 1
 * 15  DC_BNR	 reg_dc_protection_en			0x00C4	 2
 * 16  DC_BNR	 reg_dc_detail_en				0x00C4	 3
 * 17  DC_BNR	 reg_dc_blur_sel			  	0x00BC 3:2
 * 18  DC_BNR	 reg_dc_motion_max			0x00BC	 23:16
 * 19  DC_BNR	 reg_dc_motion_min			0x00BC	 31:24
 * 20  DC_BNR	 reg_var_v_gain 			  	0x00C0 23:20
 * 21  DC_BNR	 reg_var_h_gain 			  	0x00C0 27:24
 * 22  DC_BNR	 reg_var_cut_resolution 	  	0x00C0 31:28
 * 23  DC_BNR	 reg_dc_protection_th			0x00C4	 31:24
 * 24  DC_BNR	 reg_dc_bnr_var_th3 		  	0x00C8 7:0
 * 25  DC_BNR	 reg_dc_bnr_var_th2 		  	0x00C8 15:8
 * 26  DC_BNR	 reg_dc_bnr_var_th1 		  	0x00C8 23:16
 * 27  DC_BNR	 reg_dc_bnr_var_th0 		  	0x00C8 31:24
 * 28  DETAIL	 	 reg_bnr_diff_L 			  	0x00B8 23:16
 * 29  DETAIL	 	 reg_bnr_diff_P 			  	0x00B8 31:24
 * 30  SC_BNR	 reg_sc_bnr_en				0x016C	 0
 * 31  SC_BNR	 reg_pos_gain_3 			  	0x0180 7:0
 * 32  SC_BNR	 reg_pos_gain_2 			  	0x0180 15:8
 * 33  SC_BNR	 reg_pos_gain_1 			  	0x0180 23:16
 * 34  TEXTURE	 reg_texture_cnt_div		  	0x018C 2:0
 * 35  TEXTURE	 reg_texture_cnt_mul		 	0x018C 15:8
 * 36  TEXTURE	 reg_cross_th					0x018C	 31:24
 *--------------------------------------------------------------
 * 37  AC_BNR	 reg_bnr_ac_diff_min_v_th		0x00D4	 15:8
 * 38  AC_BNR	 reg_bnr_ac_diff_min_h_th		0x00D4	 23:16
 * 39  AC_BNR	 reg_bnr_ac_global_motion_th 	0x00D8  7:0
 * 40  AC_BNR	 reg_bnr_ac_h_acness_max	  	0x00D8 15:8
 * 41  AC_BNR	 reg_bnr_ac_v_acness_max	  	0x00E8  23:16
 * 42  AC_BNR	 reg_bnr_ac_h_acness_min	  	0x00D8 23:16
 * 43  AC_BNR	 reg_bnr_ac_v_acness_min	  	0x00E8  31:24
 * 44  AC_BNR	 reg_bnr_ac_acness_resol_H		0x00D4	 5:4
 * 45  AC_BNR	 reg_bnr_ac_acness_resol_V		0x00E8	 7:6
 * 46  AC_BNR	 reg_bnr_ac_motion_3		  	0x00DC  7:0
 * 47  AC_BNR	 reg_bnr_ac_motion_2		 	0x00DC  15:8
 * 48  AC_BNR	 reg_bnr_ac_motion_1		  	0x00DC  23:16
 * 49  AC_BNR	 reg_bnr_ac_motion_0		  	0x00DC 31:24
 * 50  AC_BNR	 reg_bnr_ac_motion_y_3		0x00E4	  7:0
 * 51  AC_BNR	 reg_bnr_ac_motion_y_2		0x00E4	  15:8
 * 52  AC_BNR	 reg_bnr_ac_motion_y_1		0x00E4	  23:16
 * 53  AC_BNR	 reg_bnr_ac_motion_y_0		0x00E4	 31:24
 * 54  AC_BNR	 reg_bnr_ac_detail_gain_th		0x00F4	 31:24
 * 55  DETAIL	 	reg_bnr_ac_detail_max			0x00B8	 7:0
 * 56  DETAIL	 	reg_bnr_ac_detail_min			0x00B8	 15:8
 * 57  AC_BNR	 reg_bnr_ac_detail_th4			0x00F0	 7:0
 * 58  AC_BNR	 reg_bnr_ac_detail_th3			0x00F0	 15:8
 * 59  AC_BNR	 reg_bnr_ac_detail_th2			0x00F0	 23:16
 * 60  AC_BNR	 reg_bnr_ac_detail_th1			0x00F0	 31:24
 * 61  AC_BNR	 reg_bnr_ac_pos_gain_H3 	  	0x00F8  31:24
 * 62  AC_BNR	 reg_bnr_ac_pos_gain_H2 	 	0x00F4  7:0
 * 63  AC_BNR	 reg_bnr_ac_pos_gain_H1 	 	0x00F4  15:8
 * 64  AC_BNR	 reg_bnr_ac_pos_gain_H0 		0x00F4  23:16
 * 65  AC_BNR	 reg_bnr_ac_pos_gain_L2 	  	0x00F8  7:0
 * 66  AC_BNR	 reg_bnr_ac_pos_gain_L1 	  	0x00F8  15:8
 * 67  AC_BNR	 reg_bnr_ac_pos_gain_L0 	  	0x00F8  23:16
 *-------------------------------------------------------------
 * 68  MNR		 reg_h_expand				0x00A0	 5:4
 * 69  MNR		 reg_gain_flt_size				0x00A0	 6
 * 70  MNR		 reg_mmd_y_max				0x00A4	 7:0
 * 71  MNR		 reg_mmd_y_min				0x00A4	 15:8
 * 72  MNR		 reg_mmd_x_max				0x00A4	 23:16
 * 73  MNR		 reg_mmd_x_min				0x00A4	 31:24
 * 74  MNR		 reg_blur_sel					0x00AC	 0
**/

#define LX_PE_NRD_DNR7_CMN_DATA_SIZE	12
#define LX_PE_NRD_DNR7_DTL_DCBNR_SIZE	24
#define LX_PE_NRD_DNR7_DTL_ACBNR_SIZE	31
#define LX_PE_NRD_DNR7_DTL_MSQNR_SIZE	7

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 data[LX_PE_NRD_DNR7_CMN_DATA_SIZE];	///< dnr data
}
LX_PE_NRD_DNR7_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8 dc_bnr[LX_PE_NRD_DNR7_DTL_DCBNR_SIZE];	///< dc bnr
	UINT8 ac_bnr[LX_PE_NRD_DNR7_DTL_ACBNR_SIZE];	///< ac bnr
	UINT8 mosqnr[LX_PE_NRD_DNR7_DTL_MSQNR_SIZE];	///< mnr
}
LX_PE_NRD_DNR7_DETAIL_T;

/**
 * CHIP_DNR_DB_M16P_T for HAL_VPQ_SetMpegNoiseReduction
 */

#define LX_PE_NRD_DNR8_CMN_DATA_SIZE	46
#define LX_PE_NRD_DNR8_DTL_DCBNR_SIZE	37
#define LX_PE_NRD_DNR8_DTL_ACBNR_SIZE	31
#define LX_PE_NRD_DNR8_DTL_MSQNR_SIZE	6
#define LX_PE_NRD_DNR8_DTL_DCONT_SIZE	5

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 data[LX_PE_NRD_DNR8_CMN_DATA_SIZE];	///< dnr data
}
LX_PE_NRD_DNR8_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8 dc_bnr[LX_PE_NRD_DNR8_DTL_DCBNR_SIZE];	///< dc bnr
	UINT8 ac_bnr[LX_PE_NRD_DNR8_DTL_ACBNR_SIZE];	///< ac bnr
	UINT8 mosqnr[LX_PE_NRD_DNR8_DTL_MSQNR_SIZE];	///< mnr
	UINT8 decont[LX_PE_NRD_DNR8_DTL_DCONT_SIZE];	///< mnr
}
LX_PE_NRD_DNR8_DETAIL_T;


/**
 * HAL_VPQ_SetMpegNoiseReduction O18
 */
 
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 dnr______ui[29];	///< common(ui)
}
LX_PE_NRD_DNR9_CMN_T;

/* for webOs4.5 O18*/
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr__ui_val;	///< common(ui)
	UINT8  dnr______ui[19];	///< common(ui)
	UINT32 dnr____buff[5];   ///< new ui
}
LX_PE_NRD_DNR1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8 dnr_____mnr[29];	///< dc bnr
	UINT8 dnr___dcbnr[59];	///< ac bnr
	UINT8 dnr___acbnr[23];	///< ac bnr
	UINT16 dnr____dcnt[71]; ///< decontour
}
LX_PE_NRD_DNR9_DETAIL_T;

/* for webOs4.5 O18*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8 dnr_____mnr[29];	///< dc bnr
	UINT8 dnr___dcbnr[59];	///< ac bnr
	UINT8 dnr___acbnr[23];	///< ac bnr
}
LX_PE_NRD_DNR1_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 dnrled___ui[10];	///< common(ui)
}
LX_PE_LED_DNR_CMN_T;

/**
 * HAL_VPQ_SetMpegNoiseReduction O18
 */

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 dnrled_dcnt[71]; 	///< decontour
}
LX_PE_LED_DNR_DETAIL_T;


/**
 * HAL_VPQ_SetMpegNoiseReduction O18 WebOS4.5
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT16 deconnd_____ui[12];
	UINT32 deconnd___buff[5];
}
LX_PE_NRD_DCNT1_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconnd____cmn[71];
}
LX_PE_NRD_DCNT1_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconledui_val;	///< common(ui)
	UINT16 deconled____ui[12];
	UINT32 deconled__buff[5];
}
LX_PE_LED_DCNT1_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconled___cmn[71];
}
LX_PE_LED_DCNT1_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  tnr___val;	     ///<  ui value
	UINT32 tnr0__sqm[11];	 ///< *new sqm(ui)
}
LX_PE_NRD_TNR_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  tnr___val;	     ///<  ui value
	UINT32 tnr1__sqm[11];	 ///< *new sqm(ui)
}
LX_PE_NRD_TNR2ND_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr_____val;	     ///< ui value
	UINT32 dnr___sqmui[19];  ///< new sqm ui
}
LX_PE_NRD_DNR_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd____val;	     ///< ui value
	UINT32 deconnd__sqmui[23];
}
LX_PE_NRD_DCNT_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconled___val;	     ///< ui value
	UINT32 deconled_sqmui[23];
}
LX_PE_LED_DCNT_SQM1_CMN_T;

/**
 * HAL_VPQ_SetMpegNoiseReduction M16P3
 */

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr__ui_val;	///< common(ui)
	UINT8  dnr______ui[8];	///< common(ui)
	UINT32 dnr____buff[5];   ///< new ui
}
LX_PE_NRD_DNR2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8	dnr_____mnr[6]; ///< dc bnr
	UINT8	dnr___dcbnr[37]; ///< dc bnr
	UINT8	dnr___acbnr[31]; ///< ac bnr
}
LX_PE_NRD_DNR2_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconnd____cmn[61];
}
LX_PE_NRD_DCNT2_DETAIL_T;

/******************/
/* for webOs5.0 O20**/
/******************/


typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr__ui_val;	///< common(ui)
	UINT32 dnr______ui[13];	///< common(ui)
	UINT32 dnr____buff[8];   ///< dnr____buff
}
LX_PE_NRD_DNR3_CMN_T;

// o22, o24
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8 dnr_____mnr[6];	///< mnr
	UINT8 dnr___dcbnr[34];	///< dc bnr
	UINT8 dnr___acbnr[31];	///< ac bnr
}
LX_PE_NRD_DNR3_DETAIL_T;

/******************/
/* for webOs26 O26**/
/******************/

// o26
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr__ui_val;	///< common(ui)
	UINT32 dnr______ui[11];	///< common(ui)
	UINT32 dnr____buff[8];   ///< dnr____buff
}
LX_PE_NRD_DNR4_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT32 dnr_____mnr[15]; ///< dc bnr
	UINT8  dnr___dcbnr[33]; ///< dc bnr
	UINT8  dnr___acbnr[31]; ///< ac bnr 
}
LX_PE_NRD_DNR4_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr_____val;	     ///< ui value
	UINT32 dnr___sqmui[17];  ///< new sqm ui
}
LX_PE_NRD_DNR_SQM3_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT32 deconnd_____ui[15];
	UINT32 deconnd___buff[8];
}
LX_PE_NRD_DCNT2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconnd____cmn[63];
	UINT8  deconnd___face[24];
}
LX_PE_NRD_DCNT3_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconledui_val;	///< common(ui)
	UINT32 deconled____ui[15];
	UINT32 deconled__buff[8];
}
LX_PE_LED_DCNT2_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconled___cmn[63];
	UINT8  deconled__face[24];
}
LX_PE_LED_DCNT2_DETAIL_T;
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr_____val;	     ///< ui value
	UINT32 dnr___sqmui[15];  ///< new sqm ui
}
LX_PE_NRD_DNR_SQM2_CMN_T;

/******************/
/* for webOs7.0 O22**/
/******************/
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT32 deconnd_____ui[14];
	UINT32 deconnd___buff[8];
}
LX_PE_NRD_DCNT3_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconnd____cmn[77];
	UINT8  deconnd___face[32];
}
LX_PE_NRD_DCNT4_DETAIL_T;


/*=============F20========================*/

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  dnr__ui_val;	///< common(ui)
	UINT32 dnr______ui[13];	///< common(ui)
	UINT32 dnr____buff[8];   ///< dnr____buff
	UINT32 dnr___sqmui[15];  ///< new sqm ui
	UINT8  dnr_____mnr[6];	///< mnr
	UINT8  dnr___dcbnr[34];	///< dc bnr
	UINT8  dnr___acbnr[31];	///< ac bnr
}
LX_PE_NRD_DNR_ALL_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT32 deconnd_____ui[15];
	UINT32 deconnd___buff[8];
	UINT32 deconnd__sqmui[23];
	UINT16 deconnd____cmn[63];
	UINT8  deconnd___face[24];
	UINT32 deconled____ui[15];
	UINT32 deconled__buff[8];
	UINT32 deconled_sqmui[23];
	UINT16 deconled___cmn[63];
	UINT8  deconled__face[24];
}
LX_PE_NRD_DCNT_ALL_CMN_T;

/*=============F22========================*/

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT32 deconnd_____ui[14];
	UINT32 deconnd___buff[8];
	UINT32 deconnd__sqmui[23];
	UINT16 deconnd____cmn[77];
	UINT8  deconnd___face[32];
}
LX_PE_NRD_DCNT1_ALL_CMN_T;


/*=============O24========================*/

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd____val;	     ///< ui value
	UINT32 deconnd__sqmui[27];
}
LX_PE_NRD_DCNT_SQM2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconnd____cmn[77];
	UINT8  deconnd___face[28];
}
LX_PE_NRD_DCNT5_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd_ui_val;	///< common(ui)
	UINT32 deconcco____ui[22];
	UINT32 deconcco__buff[8];
}
LX_PE_CCO_DCNT1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8  deconnd____val;	     ///< ui value
	UINT32 deconcco_sqmui[35];
}
LX_PE_CCO_DCNT_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT16 deconcco___cmn[51];
	UINT8  deconcco__face[20];
}
LX_PE_CCO_DCNT1_DETAIL_T;


/********************************************
*********************************************
 * common type - HAL_VPQ_SetMpegNoiseReduction
 *********************************************
 *********************************************/
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_DNR_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_DNR_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_DCNT_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}LX_PE_NRD_DCNT_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_LED_DCNT_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}LX_PE_LED_DCNT_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_TNR_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_TNR2ND_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_DNR_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_DCNT_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_LED_DCNT_SQM_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_CCO_DCNT_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}LX_PE_CCO_DCNT_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_CCO_DCNT_SQM_CMN_T;



#define LX_PE_NRD_TNR5_CMN_LUT_SIZE		16
#define LX_PE_NRD_TNR5_DTL_S_M_SIZE		24
#define LX_PE_NRD_TNR5_DTL_EDF_SIZE		29
#define LX_PE_NRD_TNR5_DTL_M_C_SIZE		27
#define LX_PE_NRD_TNR5_SUB_LUT_SIZE		8
/**
 *	pe temporal noise reduction common control parameter type
 *	ver.5, for H15
 *  001._[TNR_MC__]_0xC8004140_[0____]_UINT8__tnr_en_____:__________________reg_tnr_en
 *  002._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[00]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_76,
 *  003._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[01]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_54,
 *  004._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[02]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_32,
 *  005._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[03]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_10,
 *  006._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[04]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_76,
 *  007._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[05]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_54,
 *  008._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[06]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_32,
 *  009._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[07]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_10,
 *  010._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  011._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  012._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  013._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  014._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  015._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  016._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  017._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  018._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[00]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_76,
 *  019._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[01]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_54,
 *  020._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[02]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_32,
 *  021._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[03]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_10,
 *  022._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[04]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_76,
 *  023._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[05]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_54,
 *  024._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[06]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_32,
 *  025._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[07]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_10,
 *  026._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  027._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  028._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  029._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  030._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  031._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  032._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  033._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  034._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[00]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_76,
 *  035._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[01]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_54,
 *  036._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[02]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_32,
 *  037._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[03]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_10,
 *  038._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[04]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_76,
 *  039._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[05]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_54,
 *  040._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[06]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_32,
 *  041._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[07]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_10,
 *  042._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  043._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  044._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  045._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  046._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  047._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  048._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  049._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  050._[TNR_SUB_]_0xc80061a0_[31:0_]_UINT32_lut_sub[00]_:_ma_tnr_ctrl_00,_weak_x3210,
 *  051._[TNR_SUB_]_0xc80061a4_[31:0_]_UINT32_lut_sub[01]_:_ma_tnr_ctrl_01,_weak_x7654,
 *  052._[TNR_SUB_]_0xc80061a8_[31:0_]_UINT32_lut_sub[02]_:_ma_tnr_ctrl_02,_weak_y3210,
 *  053._[TNR_SUB_]_0xc80061ac_[31:0_]_UINT32_lut_sub[03]_:_ma_tnr_ctrl_03,_weak_y7654,
 *  054._[TNR_SUB_]_0xc80061b0_[31:0_]_UINT32_lut_sub[04]_:_ma_tnr_ctrl_04,_strong_x3210,
 *  055._[TNR_SUB_]_0xc80061b4_[31:0_]_UINT32_lut_sub[05]_:_ma_tnr_ctrl_05,_strong_x7654,
 *  056._[TNR_SUB_]_0xc80061b8_[31:0_]_UINT32_lut_sub[06]_:_ma_tnr_ctrl_06,_strong_y3210,
 *  057._[TNR_SUB_]_0xc80061bc_[31:0_]_UINT32_lut_sub[07]_:_ma_tnr_ctrl_07,_strong_y7654,
 */
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8  tnr_en;									///< tnr enable
	UINT32 lut_lm[LX_PE_NRD_TNR5_CMN_LUT_SIZE];		///< lut low margin
	UINT32 lut_ui[LX_PE_NRD_TNR5_CMN_LUT_SIZE];		///< lut base
	UINT32 lut_hm[LX_PE_NRD_TNR5_CMN_LUT_SIZE];		///< lut high margin
	UINT32 lut_sub[LX_PE_NRD_TNR5_SUB_LUT_SIZE];	///< lut sub
}
LX_PE_NRD_TNR5_CMN_T;
/**
 *	pe temporal noise reduction common control parameter type
 *	ver.6, for M16 same as H15
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8  tnr_en;									///< tnr enable
	UINT32 lut_lm[LX_PE_NRD_TNR5_CMN_LUT_SIZE];		///< lut low margin
	UINT32 lut_ui[LX_PE_NRD_TNR5_CMN_LUT_SIZE];		///< lut base
	UINT32 lut_hm[LX_PE_NRD_TNR5_CMN_LUT_SIZE];		///< lut high margin
}
LX_PE_NRD_TNR6_CMN_T;


/**
 *	pe temporal noise reduction detail control parameter type
 *	ver.5, for H15
 *  050._[TNR_ME__]_0xC8004140_[7:6__]_2_UINT8__s_m[00]_:_tnr_ctrl_00,_reg_sad_8x3_res,
 *  051._[TNR_ME__]_0xC8004140_[8____]_1_UINT8__s_m[01]_:_tnr_ctrl_00,_reg_sad_8x3_iir_en,
 *  052._[TNR_ME__]_0xC8004140_[31:24]_8_UINT8__s_m[02]_:_tnr_ctrl_00,_reg_sad_8x3_iir_alpha,
 *  053._[TNR_SC__]_0xC8004148_[0____]_1_UINT8__s_m[03]_:_tnr_ctrl_02,_sc_en,
 *  054._[TNR_SC__]_0xC8004148_[23:16]_8_UINT8__s_m[04]_:_tnr_ctrl_02,_sc_th_ma,
 *  055._[TNR_SM__]_0xc8004164_[6:0__]_7_UINT8__s_m[05]_:_tnr_ctrl_09,_sad_base,
 *  056._[TNR_SM__]_0xc800416C_[0____]_1_UINT8__s_m[06]_:_tnr_ctrl_11,_lb_smooth_en,
 *  057._[TNR_SM__]_0xc8004188_[2:0__]_3_UINT8__s_m[07]_:_tnr_ctrl_18,_bsad_scale,
 *  058._[TNR_SM__]_0xc8004188_[6:4__]_3_UINT8__s_m[08]_:_tnr_ctrl_18,_gsad_scale,
 *  059._[TNR_SM__]_0xc8004188_[15___]_1_UINT8__s_m[09]_:_tnr_ctrl_18,_gmv_gmv_tl_en,
 *  060._[TNR_SM__]_0xc8004188_[23___]_1_UINT8__s_m[10]_:_tnr_ctrl_18,_bmv_gmv_tl_en,
 *  061._[TNR_SM__]_0xc8004188_[31___]_1_UINT8__s_m[11]_:_tnr_ctrl_18,_bmv_pmv_tl_en,
 *  062._[TNR_SM__]_0xc8004188_[14:8_]_7_UINT8__s_m[12]_:_tnr_ctrl_18,_gmv_gmv_tl,
 *  063._[TNR_SM__]_0xc8004188_[22:16]_7_UINT8__s_m[13]_:_tnr_ctrl_18,_bmv_gmv_tl,
 *  064._[TNR_SM__]_0xc8004188_[30:24]_7_UINT8__s_m[14]_:_tnr_ctrl_18,_bmv_pmv_tl,
 *  065._[TNR_SM__]_0xc800418c_[23___]_1_UINT8__s_m[15]_:_tnr_ctrl_19,_gmv_0mv_tl_en,
 *  066._[TNR_SM__]_0xc800418c_[31___]_1_UINT8__s_m[16]_:_tnr_ctrl_19,_bmv_0mv_tl_en,
 *  067._[TNR_SM__]_0xc800418c_[22:16]_7_UINT8__s_m[17]_:_tnr_ctrl_19,_gmv_0mv_tl,
 *  068._[TNR_SM__]_0xc800418c_[30:24]_7_UINT8__s_m[18]_:_tnr_ctrl_19,_bmv_0mv_tl,
 *  069._[TNR_SM__]_0xc8004164_[13:8_]_6_UINT8__s_m[19]_:_tnr_ctrl_09,_lb_smooth_clip,
 *  070._[TNR_SM__]_0xc8004158_[7:0__]_8_UINT8__s_m[20]_:_tnr_ctrl_06,_me_lb_sad_base,
 *  071._[TNR_SM__]_0xc800416C_[1____]_1_UINT8__s_m[21]_:_tnr_ctrl_11,_pv_smooth_en,
 *  072._[TNR_SM__]_0xc8004164_[21:16]_6_UINT8__s_m[22]_:_tnr_ctrl_09,_pv_smooth_clip,
 *  073._[TNR_SM__]_0xc8004158_[15:8_]_8_UINT8__s_m[23]_:_tnr_ctrl_06,_pv_smooth_sad_base,
 *  074._[TNR_EDF_]_0xc8004190_[31:24]_8_UINT8__edf[00]_:_tnr_ctrl_20,_reg_edge_alpha_mul,
 *  075._[TNR_EDF_]_0xc8004190_[23:16]_8_UINT8__edf[01]_:_tnr_ctrl_20,_reg_edge_beta_mul,
 *  076._[TNR_EDF_]_0xc8004190_[15:8_]_8_UINT8__edf[02]_:_tnr_ctrl_20,_reg_detail_alpha_mul,
 *  077._[TNR_EDF_]_0xc8004190_[7:0__]_8_UINT8__edf[03]_:_tnr_ctrl_20,_reg_detail_beta_mul,
 *  078._[TNR_EDF_]_0xc80043d0_[5:4__]_2_UINT8__edf[04]_:_tnr_ctrl_40,_reg_t_cut_resolution,
 *  079._[TNR_EDF_]_0xc80043d8_[31:24]_8_UINT8__edf[05]_:_tnr_ctrl_42,_reg_a_lut_edge_x1,
 *  080._[TNR_EDF_]_0xc80043d8_[23:16]_8_UINT8__edf[06]_:_tnr_ctrl_42,_reg_a_lut_edge_y1,
 *  081._[TNR_EDF_]_0xc80043d8_[15:8_]_8_UINT8__edf[07]_:_tnr_ctrl_42,_reg_a_lut_edge_x0,
 *  082._[TNR_EDF_]_0xc80043d8_[7:0__]_8_UINT8__edf[08]_:_tnr_ctrl_42,_reg_a_lut_edge_y0,
 *  083._[TNR_EDF_]_0xc80043dc_[31:24]_8_UINT8__edf[09]_:_tnr_ctrl_43,_reg_a_lut_detail_x1,
 *  084._[TNR_EDF_]_0xc80043dc_[23:16]_8_UINT8__edf[10]_:_tnr_ctrl_43,_reg_a_lut_detail_y1,
 *  085._[TNR_EDF_]_0xc80043dc_[15:8_]_8_UINT8__edf[11]_:_tnr_ctrl_43,_reg_a_lut_detail_x0,
 *  086._[TNR_EDF_]_0xc80043dc_[7:0__]_8_UINT8__edf[12]_:_tnr_ctrl_43,_reg_a_lut_detail_y0,
 *  087._[TNR_EDF_]_0xc80043e0_[31:24]_8_UINT8__edf[13]_:_tnr_ctrl_44,_reg_t_lut_edge_x1,
 *  088._[TNR_EDF_]_0xc80043e0_[23:16]_8_UINT8__edf[14]_:_tnr_ctrl_44,_reg_t_lut_edge_y1,
 *  089._[TNR_EDF_]_0xc80043e0_[15:8_]_8_UINT8__edf[15]_:_tnr_ctrl_44,_reg_t_lut_edge_x0,
 *  090._[TNR_EDF_]_0xc80043e0_[7:0__]_8_UINT8__edf[16]_:_tnr_ctrl_44,_reg_t_lut_edge_y0,
 *  091._[TNR_EDF_]_0xc80043e4_[31:24]_8_UINT8__edf[17]_:_tnr_ctrl_45,_reg_t_lut_detail_x1,
 *  092._[TNR_EDF_]_0xc80043e4_[23:16]_8_UINT8__edf[18]_:_tnr_ctrl_45,_reg_t_lut_detail_y1,
 *  093._[TNR_EDF_]_0xc80043e4_[15:8_]_8_UINT8__edf[19]_:_tnr_ctrl_45,_reg_t_lut_detail_x0,
 *  094._[TNR_EDF_]_0xc80043e4_[7:0__]_8_UINT8__edf[20]_:_tnr_ctrl_45,_reg_t_lut_detail_y0,
 *  095._[TNR_EDF_]_0xc80043e8_[31:24]_8_UINT8__edf[21]_:_tnr_ctrl_46,_reg_final_lut_edge_x1,
 *  096._[TNR_EDF_]_0xc80043e8_[23:16]_8_UINT8__edf[22]_:_tnr_ctrl_46,_reg_final_lut_edge_y1,
 *  097._[TNR_EDF_]_0xc80043e8_[15:8_]_8_UINT8__edf[23]_:_tnr_ctrl_46,_reg_final_lut_edge_x0,
 *  098._[TNR_EDF_]_0xc80043e8_[7:0__]_8_UINT8__edf[24]_:_tnr_ctrl_46,_reg_final_lut_edge_y0,
 *  099._[TNR_EDF_]_0xc80043ec_[31:24]_8_UINT8__edf[25]_:_tnr_ctrl_47,_reg_final_lut_detail_x1,
 *  100._[TNR_EDF_]_0xc80043ec_[23:16]_8_UINT8__edf[26]_:_tnr_ctrl_47,_reg_final_lut_detail_y1,
 *  101._[TNR_EDF_]_0xc80043ec_[15:8_]_8_UINT8__edf[27]_:_tnr_ctrl_47,_reg_final_lut_detail_x0,
 *  102._[TNR_EDF_]_0xc80043ec_[7:0__]_8_UINT8__edf[28]_:_tnr_ctrl_47,_reg_final_lut_detail_y0,
 *  103._[TNR_MC__]_0xc80041a0_[4____]_1_UINT8__m_c[00]_:_tnr_ctrl_24,_reg_luma_gain_en,
 *  104._[TNR_MC__]_0xc80041a0_[5____]_1_UINT8__m_c[01]_:_tnr_ctrl_24,_reg_skin_gain_en,
 *  105._[TNR_MC__]_0xc80041b4_[0____]_1_UINT8__m_c[02]_:_tnr_ctrl_29,_reg_dir_blur_en,
 *  106._[TNR_MC__]_0xc80041b4_[15:8_]_8_UINT8__m_c[03]_:_tnr_ctrl_29,_reg_dir_blur_gain,
 *  107._[TNR_MC__]_0xc80041b4_[31:24]_8_UINT8__m_c[04]_:_tnr_ctrl_29,_reg_diff_limit,
 *  108._[TNR_MC__]_0xc80041b8_[0____]_1_UINT8__m_c[05]_:_tnr_ctrl_30,_reg_denoise_filter_en,
 *  109._[TNR_MC__]_0xc80041b8_[15:8_]_8_UINT8__m_c[06]_:_tnr_ctrl_30,_reg_denoise_gain,
 *  110._[TNR_MC__]_0xc80041b8_[5:4__]_2_UINT8__m_c[07]_:_tnr_ctrl_30,_reg_denoise_cut_resolution,
 *  111._[TNR_MC__]_0xc80041b8_[22:16]_7_UINT8__m_c[08]_:_tnr_ctrl_30,_reg_denoise_G0,
 *  112._[TNR_MC__]_0xc80041bc_[28:24]_5_UINT8__m_c[09]_:_tnr_ctrl_31,_reg_denoise_G1,
 *  113._[TNR_MC__]_0xc80041bc_[20:16]_5_UINT8__m_c[10]_:_tnr_ctrl_31,_reg_denoise_G2,
 *  114._[TNR_MC__]_0xc80041bc_[12:8_]_5_UINT8__m_c[11]_:_tnr_ctrl_31,_reg_denoise_G3,
 *  115._[TNR_MC__]_0xc80041bc_[4:0__]_5_UINT8__m_c[12]_:_tnr_ctrl_31,_reg_denoise_G4,
 *  116._[TNR_MC__]_0xc80041a4_[0____]_1_UINT8__m_c[13]_:_tnr_ctrl_25,_reg_flat_y_blur_en,
 *  117._[TNR_MC__]_0xc80041a4_[5:4__]_2_UINT8__m_c[14]_:_tnr_ctrl_25,_reg_flat_y_cut_resolution,
 *  118._[TNR_MC__]_0xc80041a4_[13:8_]_6_UINT8__m_c[15]_:_tnr_ctrl_25,_reg_flat_y_G0,
 *  119._[TNR_MC__]_0xc80041a4_[31:28]_4_UINT8__m_c[16]_:_tnr_ctrl_25,_reg_flat_y_G1,
 *  120._[TNR_MC__]_0xc80041a4_[27:24]_4_UINT8__m_c[17]_:_tnr_ctrl_25,_reg_flat_y_G2,
 *  121._[TNR_MC__]_0xc80041a4_[23:20]_4_UINT8__m_c[18]_:_tnr_ctrl_25,_reg_flat_y_G3,
 *  122._[TNR_MC__]_0xc80041a4_[19:16]_4_UINT8__m_c[19]_:_tnr_ctrl_25,_reg_flat_y_G4,
 *  123._[TNR_MC__]_0xc80041a8_[0____]_1_UINT8__m_c[20]_:_tnr_ctrl_26,_reg_flat_c_blur_en,
 *  124._[TNR_MC__]_0xc80041a8_[5:4__]_2_UINT8__m_c[21]_:_tnr_ctrl_26,_reg_flat_c_cut_resolution,
 *  125._[TNR_MC__]_0xc80041a8_[13:8_]_6_UINT8__m_c[22]_:_tnr_ctrl_26,_reg_flat_c_G0,
 *  126._[TNR_MC__]_0xc80041a8_[31:28]_4_UINT8__m_c[23]_:_tnr_ctrl_26,_reg_flat_c_G1,
 *  127._[TNR_MC__]_0xc80041a8_[27:24]_4_UINT8__m_c[24]_:_tnr_ctrl_26,_reg_flat_c_G2,
 *  128._[TNR_MC__]_0xc80041a8_[23:20]_4_UINT8__m_c[25]_:_tnr_ctrl_26,_reg_flat_c_G3,
 *  129._[TNR_MC__]_0xc80041a8_[19:16]_4_UINT8__m_c[26]_:_tnr_ctrl_26,_reg_flat_c_G4,
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 s_m[LX_PE_NRD_TNR5_DTL_S_M_SIZE];		///< me,sc,sm
	UINT8 edf[LX_PE_NRD_TNR5_DTL_EDF_SIZE];		///< edf
	UINT8 m_c[LX_PE_NRD_TNR5_DTL_M_C_SIZE];		///< mc
}
LX_PE_NRD_TNR5_DETAIL_T;

#define LX_PE_NRD_TNR7_CMN_LUT__SIZE 16
#define LX_PE_NRD_TNR7_CMN_GAIN_SIZE 5
#define LX_PE_NRD_TNR7_CMN_BUFF_SIZE 32
#define LX_PE_NRD_TNR6_DTL_CTL_SIZE 21
#define LX_PE_NRD_TNR6_DTL_MAE_SIZE 30
#define LX_PE_NRD_TNR6_DTL_MC__SIZE 58
#define LX_PE_NRD_TNR6_DTL_EDF_SIZE 36
#define LX_PE_NRD_TNR6_DTL_BLD_SIZE 24
/**
 *	pe temporal noise reduction common control parameter type
 *	ver.7, for M16 same as M16P
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8  tnr_en;			///< tnr enable(ui)
	UINT32 tnr_lut[LX_PE_NRD_TNR7_CMN_LUT__SIZE];		///< lut (ui)
	UINT32 tnr_lut_gain[LX_PE_NRD_TNR7_CMN_GAIN_SIZE];	///< gian (ui)
	UINT32 tnr_lut_buff[LX_PE_NRD_TNR7_CMN_BUFF_SIZE];	///< buff (ui)
}
LX_PE_NRD_TNR7_CMN_T;

/**
 *	pe temporal noise reduction detail control parameter type
 *	ver.6, for M16P
*/
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  tnr_ctl[LX_PE_NRD_TNR6_DTL_CTL_SIZE]; 	///< tnr_ctrl
	UINT8  tnr_mae[LX_PE_NRD_TNR6_DTL_MAE_SIZE]; 	///< tnr_ma
	UINT8  tnr__mc[LX_PE_NRD_TNR6_DTL_MC__SIZE]; 	///< tnr_mc
	UINT8  tnr_edf[LX_PE_NRD_TNR6_DTL_EDF_SIZE]; 	///< tnr_df
	UINT8  tnr_bld[LX_PE_NRD_TNR6_DTL_BLD_SIZE]; 	///< tnr_blend
}
LX_PE_NRD_TNR6_DETAIL_T;

/**
 *	pe temporal noise reduction common control parameter type
 *	ver.8, for M16 same as O18, M16P3
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8  tnr0___en;		///< tnr enable(ui)
	UINT32 tnr0__lut[16]; 	///< lut (ui)
	UINT32 tnr0_gain[5]; 	///< gian (ui)
	UINT32 tnr0_buff[32];	///< buff (ui)
}
LX_PE_NRD_TNR8_CMN_T;
/**
 *	pe temporal noise reduction common control parameter type
 *	ver.8, for  O18
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8  tnr1___en;		///< tnr enable(ui)
	UINT32 tnr1__lut[16]; 	///< lut (ui)
	UINT32 tnr1_gain[5]; 	///< gian (ui)
	UINT32 tnr1_buff[32];	///< buff (ui)
}
LX_PE_NRD_TNR2ND1_CMN_T;

/**
 *	pe temporal noise reduction detail control parameter type
 *	ver.7, for O18
*/
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  tnr0__ctl[21];	///< tnr_ctrl
	UINT8  tnr0___ma[2];	///< tnr_ma
	UINT8  tnr0___me[11];	///< tnr_me
	UINT8  tnr0__mlb[13];	///< tnr_melb
	UINT8  tnr0___mc[15];	///< tnr_mc
	UINT8  tnr0_blnd[24];	///< tnr_blend
}
LX_PE_NRD_TNR7_DETAIL_T;

/**
 *	pe temporal noise reduction detail control parameter type
 *	ver.7, for O18
*/
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  tnr1__ctl[21];	///< tnr_ctrl
	UINT8  tnr1___ma[2];	///< tnr_ma
	UINT8  tnr1___me[11];	///< tnr_me
	UINT8  tnr1__mlb[13];	///< tnr_melb
	UINT8  tnr1___mc[15];	///< tnr_mc
	UINT8  tnr1_blnd[24];	///< tnr_blend
}
LX_PE_NRD_TNR2ND1_DETAIL_T;

/**
 *	pe temporal noise reduction detail control parameter type
 *	ver.7, for M16P3
*/
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8	tnr0__ctl[21];	 ///< tnr_ctrl
	UINT8	tnr0___ma[2];	 ///< tnr_ma
	UINT8	tnr0___me[12];	 ///< tnr_me
	UINT8	tnr0__mlb[15];	 ///< tnr_melb
	UINT8	tnr0___mc[26];	 ///< tnr_mc
	UINT8   tnr0__edf[36];	 ///< tnr_df
	UINT8	tnr0_blnd[24];	 ///< tnr_blend
}
LX_PE_NRD_TNR1_DETAIL_T;

/**
 *	pe temporal noise reduction detail control parameter type
 *	ver.7, for O18
*/
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8	tnr1__ctl[21];	 ///< tnr_ctrl
	UINT8	tnr1___ma[2];	 ///< tnr_ma
	UINT8	tnr1___me[12];	 ///< tnr_me
	UINT8	tnr1__mlb[15];	 ///< tnr_melb
	UINT8	tnr1___mc[26];	 ///< tnr_mc
	UINT8   tnr1__edf[36];	 ///< tnr_df
	UINT8	tnr1_blnd[24];	 ///< tnr_blend
}
LX_PE_NRD_TNR2ND2_DETAIL_T;

/*****************************/
/** O20***********************/
#define LX_PE_NRD_TNR1_CMN_LUT__SIZE 16
#define LX_PE_NRD_TNR1_CMN_GAIN_SIZE 5
#define LX_PE_NRD_TNR1_CMN_BUFF_SIZE 15

/**
 *	pe temporal noise reduction common control parameter type
 *	ver.8, for M16 same as O20
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT32 tnr0___en;		///< tnr enable(ui)
	UINT32 tnr0__lut[16]; 	///< lut (ui)
	UINT32 tnr0_gain[5]; 	///< gian (ui)
	UINT32 tnr0_buff[15];	///< buff (ui)
}
LX_PE_NRD_TNR1_CMN_T;
/**
 *	pe temporal noise reduction common control parameter type
 *	ver.8, for  O20
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT32 tnr1___en;		///< tnr enable(ui)
	UINT32 tnr1__lut[16]; 	///< lut (ui)
	UINT32 tnr1_gain[5]; 	///< gian (ui)
	UINT32 tnr1_buff[15];	///< buff (ui)
}
LX_PE_NRD_TNR2ND2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  tnr0__ctl[21];	///< tnr_ctrl
	UINT8  tnr0___ma[2];	///< tnr_ma
	UINT8  tnr0___me[8];	///< tnr_me
	UINT8  tnr0__mlb[15];	///< tnr_melb
	UINT16 tnr0___mc[31];	///< tnr_mc
	UINT8  tnr0_blnd[24];	///< tnr_blend
}
LX_PE_NRD_TNR2_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8	tnr1__ctl[21];	 ///< tnr_ctrl
	UINT8	tnr1___ma[2];	 ///< tnr_ma
	UINT8	tnr1___me[8];	 ///< tnr_me
	UINT8	tnr1__mlb[15];	 ///< tnr_melb
	UINT16	tnr1___mc[31];	 ///< tnr_mc
	UINT8	tnr1_blnd[24];	 ///< tnr_blend
}
LX_PE_NRD_TNR2ND3_DETAIL_T;

/*****************************/
/** O26***********************/
/**
 *	pe temporal noise reduction common control parameter type
 *	ver.0x80, for O26
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT32 tnr0_face_gain[4]; ///< face gain (ui) added @o26, SICREG-1154
}
LX_PE_NRD_TNR_FACE_T;


/**
 * common type - HAL_VPQ_SetNoiseReduction
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;			///< dnr______ui[29] common(ui)
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_TNR_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;			///< dnr______ui[29] common(ui)
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_TNR_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;			///< dnr______ui[29] common(ui)
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_TNR2ND_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;			///< dnr______ui[29] common(ui)
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_NRD_TNR2ND_DETAIL_T;

/*=============F20========================*/

/**
 *	pe temporal noise reduction all control parameter type
 *	ver.8, for F20
*/
typedef struct
{
	LX_PE_WIN_ID win_id;							///< window id
	UINT8  tnr___val;	     ///<  ui value
	UINT32 tnr0___en;		///< tnr enable(ui)
	UINT32 tnr0__lut[16];	///< lut (ui)
	UINT32 tnr0_gain[5];	///< gian (ui)
	UINT32 tnr0_buff[15];	///< buff (ui)
	UINT32 tnr0__sqm[11];	///< sqm(ui)
	UINT8  tnr0__ctl[21];	///< tnr_ctrl
	UINT8  tnr0___ma[2];	///< tnr_ma
	UINT8  tnr0___me[8];	///< tnr_me
	UINT8  tnr0__mlb[15];	///< tnr_melb
	UINT16 tnr0___mc[31];	///< tnr_mc
	UINT8  tnr0_blnd[24];	///< tnr_blend
}
LX_PE_NRD_TNR_ALL_CMN_T;


/***************************************************************************/
/* DNT : Deinterlace */
/***************************************************************************/

/**
 *	pe deinterlacer, film(3:2,2:2 pull down) mode control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 enable;			///< enable film mode, 1:on, 0:off
}
LX_PE_DNT_FILMMODE_T;

/**
 *	pe deinterlacer, low delay mode control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 enable;			///< enable low delay mode, 1:on, 0:off
}
LX_PE_DNT_LD_MODE_T;

/***************************************************************************/
/* SHP : Sharpness */
/***************************************************************************/
/**
 *	pe resolution enhancement(RE) pseudo control(ver.1) parameter type
 *	for every chip
 */
typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ui_main_post[4];        ///< shp_ui_main_post[14];
}
LX_PE_SHP_RE_PSEUDO_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;                           ///< window id
	UINT8  shp_ui_h_main[2];            ///< shp_ui_h_main[2];
}
LX_PE_SHP_RE_PSEUDO_HOR_T;

typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ui_v_main[2];            ///< shp_ui_v_main[2];
}
LX_PE_SHP_RE_PSEUDO_VER_T;

typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ee[4];
}
LX_PE_SHP_PSEUDO_EE_T;

typedef struct
{
	LX_PE_WIN_ID win_id;                ///< window id
	UINT8  shp_de[4];
}
LX_PE_SHP_PSEUDO_DE_T;

typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ui_vsd[20];    ///< shp_ui_vsd[20];
}
LX_PE_SHP_RE_EASY_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;                ///< window id
	UINT8  shp_ui_h_main[2];            ///< shp_ui_h_main[2];
}
LX_PE_SHP_RE_EASY_HOR_T;

typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ui_v_main[2];            ///< shp_ui_v_main[2];
}
LX_PE_SHP_RE_EASY_VER_T;

typedef struct
{
	LX_PE_WIN_ID win_id;                ///< window id
	UINT8  shp_de_vsd[4];
}
LX_PE_SHP_RE_EASY_DE_T;

typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ui_main_2k[4];        ///< shp_ui_main_post[4];
	UINT8  shp_ui_h_main_2k[2];            ///< shp_ui_h_main[2];
	UINT8  shp_ui_v_main_2k[2];            ///< shp_ui_v_main[2];
	UINT8  shp_ui_ee_2k[4];
}
LX_PE_SHP_SR2K_EASY_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;                ///< window id
	UINT8  shp_de_2k[4];
}
LX_PE_SHP_SR2K_EASY_DE_T;

typedef struct
{
	LX_PE_WIN_ID win_id;      ///< window id
	UINT8  shp_ee[4];
}
LX_PE_SHP_EASY_EE_T;

typedef struct
{
	LX_PE_WIN_ID win_id;                ///< window id
	UINT8  shp_de[4];
}
LX_PE_SHP_EASY_DE_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.1, for H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT8 edge_y_filter_en;			///< edge_Y_filter_en
	UINT8 reg_csft_gain;			///< reg_csft_gain: center shift gain(1.5u)
	UINT8 edge_filter_white_gain;	///< edge filter white gain
	UINT8 edge_filter_black_gain;	///< edge filter black gain
	UINT8 a_gen_width;				///< a_gen_widt
	UINT8 mp_horizontal_gain;		///< horizontal gain(3.5u)
	UINT8 sp_horizontal_gain;		///< horizontal gain(3.5u)
}
LX_PE_SHP_RE1_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.1, for H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 der_v_en;			///< der-v enable
	UINT8 bif_manual_th;	///< bilateral filter threshold
	UINT8 csft_gain;		///< center-shift gain (1.5u)
	UINT8 gain_b;			///< gain(b) : 2.5u
	UINT8 gain_w;			///< gain(w): 2.5u
	UINT8 der_gain_mapping;	///< weight selection for weighted average of bif and inpu
	UINT8 mmd_sel;			///< a-gen. siz
	UINT8 mp_vertical_gain;	///< vertical gain(3.5u)
	UINT8 sp_vertical_gain;	///< vertical gain(3.5u)
}
LX_PE_SHP_RE1_VER_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.1, for H13
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 mp_texture_gain_b;	///< MP: texture gain(b)
	UINT8 mp_texture_gain_w;	///< MP: texture gain(w)
	UINT8 sp_texture_gain_b;	///< SP: texture gain(b)
	UINT8 sp_texture_gain_w;	///< SP: texture gain(w)
}
LX_PE_SHP_DE1_T;


/*######################SR##############################*/
/**
 *	SR scaler filter coefficient control parameter type
 */

/**
 *	sr (post)scaler filter coefficient control parameter type
 */

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 iu_scale_coeff0_0;  	///<
	UINT32 iu_scale_coeff0_1; 	///<
	UINT32 iu_scale_coeff0_2;  	///<
	UINT32 iu_scale_coeff0_3;  	///<
	UINT32 iu_scale_coeff1_0;  	///<
	UINT32 iu_scale_coeff1_1;  	///<
	UINT32 iu_scale_coeff1_2;  	///<
	UINT32 iu_scale_coeff1_3;  	///<
}
LX_PE_SHP_SR_SCLFILTER_COEFF_T;


/**
 *	sr resolution enhancement(RE) normal control(ver.3) parameter type
 *	ver.3, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* shp_ui_main_pre[8] */
	UINT8 mp_white_gain;				///< white gain
	UINT8 mp_black_gain;				///< black gain
	UINT8 sp_white_gain;				///< white gain
	UINT8 sp_black_gain;				///< black gain
	UINT8 mp_lap_h_mode;				///< "Laplacian H mode""000"" : H3(V3)""001"" : H4(V4)""010"" : H5(V5)""011"" : H6(V6)""100"" : H7(V7)"
	UINT8 sp_lap_h_mode;				///< """00"" : H3""01"" : H5""10"" : H7""11"" : Not used"
	UINT8 mp_lap_v_mode;				///< "Laplacian V mode""000"" : H3(V3)""001"" : H4(V4)""010"" : H5(V5)""011"" : H6(V6)""100"" : H7(V7)"
	UINT8 sp_lap_v_mode;				///< "0' : V3'1' : V5"
	/* shp_ti_ui_main_pre[5] */
	UINT8 reg_master_gain_pti_v;		///< reg_master_gain_PTI-V
	UINT8 reg_master_gain_pti_h; 		///< reg_master_gain_PTI-H
	UINT8 reg_master_gain_sti; 			///< reg_master_gain_STI
	UINT8 reg_edge_gain_sti; 			///< reg_edge_gain_STI
	UINT8 reg_texture_gain_sti;			///< reg_texture_gain_STI
	/*shp_tgen_ui_main_pre[10]*/
	UINT8 tg_map_edge_gain;				///< tg_map_edge_gain
	UINT8 tg_map_detail_gain;			///< tg_map_detail_gain
	UINT8 tg_map_offset;				///< tg_map_offset
	UINT8 tg_gs_noise;					///< tg_gs_noise
	UINT8 tg_blur_coef_x0;				///< tg_blur_coef_x0
	UINT8 tg_blur_coef_x1;				///< tg_blur_coef_x1
	UINT8 tg_blur_coef_x2;				///< tg_blur_coef_x2
	UINT8 tg_blur_coef_y0;				///< tg_blur_coef_y0
	UINT8 tg_blur_coef_y1;				///< tg_blur_coef_y1
	UINT8 tg_blur_coef_y2;				///< tg_blur_coef_y2
}
LX_PE_SHP_SR_RE_CMN_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.2) parameter type
 *	ver.3, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* shp_ui_h_main_pre[10] */
	UINT8 reg_csft_gain;				///<"reg_csft_gain: center shift gain(1.5u)deringing/LTI same setting."
	UINT8 edge_filter_white_gain;		///<"edge filter white gain (2.4u)"
	UINT8 edge_filter_black_gain;		///<"edge filter black gain  (2.4u)"
	UINT8 a_gen_width;					///<"a_gen_widthwidth size for dynamic range"
	UINT8 mp_horizontal_gain;	  		///<horizontal gain(3.5u)
	UINT8 sp_horizontal_gain;			///<horizontal gain(3.5u)
	UINT8 e_gain_th1;					///<A to edge gain: th1
	UINT8 e_gain_th2;					///<A to edge gain: th2
	UINT8 f_gain_th1;					///<A to flat gain: th1
	UINT8 f_gain_th2;					///<A to flat gain: th2
}
LX_PE_SHP_SR_RE_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.3) parameter type
 *	ver.3, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/*shp_ui_v_main_pre[9] */
	UINT8 bif_manual_th;				///< bilateral filter threshold
	UINT8 csft_gain;					///< center-shift gain (1.5u)
	UINT8 gain_b;						///< gain(b) : 2.5u
	UINT8 gain_w;						///< gain(w): 2.5u
	UINT8 mmd_sel;						///< "a-gen. size""000"" : 11 tap""001"" : 9-tap""010"" : 7-tap""011"" : 5-tap""100"" : 3-tap o.w   : 11-tap"
	UINT8 mp_vertical_gain;				///< vertical gain(3.5u)
	UINT8 sp_vertical_gain;				///< vertical gain(3.5u)
	UINT8 gain_th1;						///< A-to-weight: th1
	UINT8 gain_th2;						///< A-to-weight: th2
}
LX_PE_SHP_SR_RE_VER_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.3, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* shp_cmn_pre[23]*/
	UINT8 edge_Y_filter_en;				///<edge_Y_filter en
	UINT8 e_gain_max;					///<"A to edge weight: gain2.4u"
	UINT8 f_gain_max;					///<A to flat weight: gain
	UINT8 der_v_en;						///<der-v enable
	UINT8 der_gain_mapping;				///<"weight selection for weighted average of bif and input""00"" : A-to weight""01"" : A-map""10  : A-to weight""11"" : A-map"
	UINT8 max_sel;						///<"A-expansion size (H)""000"" : do not expand""001"" : 3-tap""010"" : 5-tap""011"" : 7-tap""100"" : 9-tap""101"" : 11-tapo.w   : do not expand"
	UINT8 mp_laplacian_weight;			///<Weight for Laplacian operator output
	UINT8 sp_laplacian_weight;			///<Weight for Laplacian operator output
	UINT8 flat_filter_en;				///<flat filter en
	UINT8 flat_filter_type;				///<"flat filter fype'0' : bi-lateral filter'1': average filter"
	UINT8 flat_filter_gain;				///<flat filter gain(2.4u)
	UINT8 edf_en;						///<edge-directional de-jagging enable
	UINT8 center_blur_mode;				///<"center-pixel averaging for edge-direction calculation'0' : use original pixel'1' : use avg. pixel"
	UINT8 count_diff_th;				///<matchness threshod for edge-direction decision
	UINT8 n_avg_mode;					///<"neighbor-pixel averaging : mode for dual edges'0' : use 12 direction results'1' : use 36 direction results"
	UINT8 line_variation_diff_threshold;///<line-variation threshold for edge-direction decision
	UINT8 level_th;						///<g0: level threshold
	UINT8 protect_th;					///<G1: protect threshold
	UINT8 n_avg_gain;					///<neighborhood pixel averaing : gain
	UINT8 reg_g0_cnt_min;				///<G0 : edf_count_min
	UINT8 reg_g0_mul;					///<G0 : n x ( Count - min_cnt_th )
	UINT8 reg_g1_protect_min;			///<G1 : Min diff th - LR Diff
	UINT8 reg_g1_mul;					///<G1 : n x ( th - LR_Diff )
	/* shp_map_cmn_pre[36]*/
	UINT8 reg_cross_th_sc;				///<"<A-gain for edge filter>edge-map gain(2.5u)edge map"
	UINT8 reg_cross_th;					///<
	UINT8 reg_mul_base_t;				///<
	UINT8 reg_mul_base_e;				///<
	UINT8 reg_a_map_h_size;				///<
	UINT8 reg_a_nomalize_en;			///<nomalize by mulbase
	UINT8 reg_edge_alpha_mul;			///<get_t_map (alpha*t_map - beta*a_map)
	UINT8 reg_edge_beta_mul;			///<get_t_map (alpha*t_map - beta*a_map)
	UINT8 reg_a_lut_edge_x0;			///<reg_a_lut_edge
	UINT8 reg_a_lut_edge_y0;			///<reg_a_lut_edge
	UINT8 reg_a_lut_edge_x1;			///<reg_a_lut_edge
	UINT8 reg_a_lut_edge_y1;			///<reg_a_lut_edge
	UINT8 reg_a_lut_detail_x0;			///<reg_a_lut_detail
	UINT8 reg_a_lut_detail_y0;			///<reg_a_lut_detail
	UINT8 reg_a_lut_detail_x1;			///<reg_a_lut_detail
	UINT8 reg_a_lut_detail_y1;			///<reg_a_lut_detail
	UINT8 reg_edge_minmax_x0;			///<reg_edge_minmax
	UINT8 reg_edge_minmax_y0;			///<reg_edge_minmax
	UINT8 reg_edge_minmax_x1;			///<reg_edge_minmax
	UINT8 reg_edge_minmax_y1;			///<reg_edge_minmax
	UINT8 reg_t_cut_resolution;			///<
	UINT8 reg_t_nomalize_en;			///<nomalize by mulbase
	UINT8 reg_detail_alpha_mul;			///<get e_map (alpha*a_map - beta*t_map)
	UINT8 reg_detail_beta_mul;			///<get e_map (alpha*a_map - beta*t_map)
	UINT8 reg_t_lut_edge_x0;			///<reg_t_lut_edge
	UINT8 reg_t_lut_edge_y0;			///<reg_t_lut_edge
	UINT8 reg_t_lut_edge_x1;			///<reg_t_lut_edge
	UINT8 reg_t_lut_edge_y1;			///<reg_t_lut_edge
	UINT8 reg_t_lut_detail_x0;			///<reg_t_lut_detail
	UINT8 reg_t_lut_detail_y0;			///<reg_t_lut_detail
	UINT8 reg_t_lut_detail_x1;			///<reg_t_lut_detail
	UINT8 reg_t_lut_detail_y1;			///<reg_t_lut_detail
	UINT8 reg_detail_minmax_x0;			///<reg_detail_minmax
	UINT8 reg_detail_minmax_y0;			///<reg_detail_minmax
	UINT8 reg_detail_minmax_x1;			///<reg_detail_minmax
	UINT8 reg_detail_minmax_y1;			///<reg_detail_minmax
	/* shp_balance_pre[42]*/
	UINT8 mp_gb_en;						///< "0 : disable'1' : enable"
	UINT8 mp_gb_mode;					///< "delta(x-axis) resolution'0' : 8bit'1' : 10bit"
	UINT8 mp_gb_x1;						///< mp_gb_x1
	UINT8 mp_gb_x2;						///< mp_gb_x2
	UINT8 mp_gb_y1;						///< mp_gb_y1
	UINT8 mp_gb_y2;						///< mp_gb_y2
	UINT8 mp_gb_y3;						///< mp_gb_y3
	UINT8 sp_gb_en;						///< "0 : disable'1' : enable"
	UINT8 sp_gb_mode;					///< "delta(x-axis) resolution'0' : 8bit'1' : 10bit"
	UINT8 sp_gb_x1;						///< sp_gb_x1
	UINT8 sp_gb_x2;						///< sp_gb_x2
	UINT8 sp_gb_y1;						///< sp_gb_y1
	UINT8 sp_gb_y2;						///< sp_gb_y2
	UINT8 sp_gb_y3;						///< sp_gb_y3
	UINT8 mp_lum1_x_L0;					///< mp_lum1_x_L0
	UINT8 mp_lum1_x_L1;					///< mp_lum1_x_L1
	UINT8 mp_lum1_x_H0;					///< mp_lum1_x_H0
	UINT8 mp_lum1_x_H1;					///< mp_lum1_x_H1
	UINT8 mp_lum1_y0;					///< mp_lum1_y0
	UINT8 mp_lum1_y1;					///< mp_lum1_y1
	UINT8 mp_lum1_y2;					///< mp_lum1_y2
	UINT8 mp_lum2_x_L0;					///< mp_lum2_x_L0
	UINT8 mp_lum2_x_L1;					///< mp_lum2_x_L1
	UINT8 mp_lum2_x_H0;					///< mp_lum2_x_H0
	UINT8 mp_lum2_x_H1;					///< mp_lum2_x_H1
	UINT8 mp_lum2_y0;					///< mp_lum2_y0
	UINT8 mp_lum2_y1;					///< mp_lum2_y1
	UINT8 mp_lum2_y2;					///< mp_lum2_y2
	UINT8 sp_lum1_x_L0;					///< sp_lum1_x_L0
	UINT8 sp_lum1_x_L1;					///< sp_lum1_x_L1
	UINT8 sp_lum1_x_H0;					///< sp_lum1_x_H
	UINT8 sp_lum1_x_H1;					///< sp_lum1_x_H
	UINT8 sp_lum1_y0;					///< sp_lum1_y0
	UINT8 sp_lum1_y1;					///< sp_lum1_y1
	UINT8 sp_lum1_y2;					///< sp_lum1_y2
	UINT8 sp_lum2_x_L0;					///< sp_lum2_x_L0
	UINT8 sp_lum2_x_L1;					///< sp_lum2_x_L1
	UINT8 sp_lum2_x_H0;					///< sp_lum2_x_H0
	UINT8 sp_lum2_x_H1;					///< sp_lum2_x_H1
	UINT8 sp_lum2_y0;					///< sp_lum2_y0
	UINT8 sp_lum2_y1;					///< sp_lum2_y1
	UINT8 sp_lum2_y2;					///< sp_lum2_y2
	/* shp_ti_cmn_pre[9]*/
	UINT8 reg_ti_enable_pti_v;			///< reg_ti_enable
	UINT8 reg_mm_tap_size_pti_v;		///< reg_mm_tap_size
	UINT8 reg_avg_tap_size_pti_v;		///< reg_avg_tap_size
	UINT8 reg_ti_enable_pti_h;			///< reg_ti_enable
	UINT8 reg_mm_tap_size_pti_h;		///< reg_mm_tap_size
	UINT8 reg_avg_tap_size_pti_h;		///< reg_avg_tap_size
	UINT8 reg_enable_sti;				///< reg_ti_enable
	UINT8 reg_mm_tap_size_sti;			///< reg_mm_tap_size
	UINT8 reg_avg_tap_size_sti;			///< reg_avg_tap_size
	/* shp_tgen_cmn_pre[23]*/
	UINT8 tgen_on_off;					///< tgen_on_off
	UINT8 tg_delta_H_bound;				///< tg_delta_H_bound
	UINT8 tg_delta_L_bound;				///< tg_delta_L_bound
	UINT8 tg_delta_max;					///< tg_delta_max
	UINT8 tg_delta_scale;				///< tg_delta_scale
	UINT8 tg_rnd_th;					///< tg_rnd_th
	UINT8 tg_delta_wcurr;				///< tg_delta_wcurr
	UINT8 tg_lc_ldr_th;					///< tg_lc_ldr_th
	UINT8 tg_dr_ratio;					///< tg_dr_ratio
	UINT8 tg_dr_th;						///< tg_dr_th
	UINT8 tg_mm_offset;					///< tg_mm_offset
	UINT8 tg_mm_sel_mode;				///< tg_mm_sel_mode
	UINT8 tg_lavg_th;					///< tg_lavg_th
	UINT8 tg_gs_rnd;					///< = tg_gs_rnd(.yml) * tg_ls_mv >> 5
	UINT8 tg_gs_mm;						///< = tg_gs_mm(.yml) * tg_ls_mv >> 5
	UINT8 tg_gain0;						///<	 tg_gain0
	UINT8 tg_gain1;						///< tg_gain1
	UINT8 tg_gain2;						///< tg_gain2
	UINT8 tg_gain3;						///< tg_gain3
	UINT8 tg_gain4;						///< tg_gain4
	UINT8 tg_gain5;						///< tg_gain5
	UINT8 tg_gain6;						///< tg_gain6
	UINT8 tg_gain7;						///< tg_gain7
}
LX_PE_SHP_SR_RE_MISC_T;

/**
 *	sr edge enhancement(EE) control parameter type
 *	ver.1, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 mp_edge_gain_b;	///< MP: edge gain(b) : 2.5u
	UINT8 mp_edge_gain_w;	///< MP: edge gain(w)
	UINT8 sp_edge_gain_b;	///< SP: edge gain(b) : 2.5u
	UINT8 sp_edge_gain_w;	///< SP: edge gain(w)
}
LX_PE_SHP_SR_EE_T;

/**
 *	sr detail enhancement(DE) control parameter type
 *	ver.1, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 mp_texture_gain_b;	///< MP: texture gain(b)
	UINT8 mp_texture_gain_w;	///< MP: texture gain(w)
	UINT8 sp_texture_gain_b;	///< SP: texture gain(b)
	UINT8 sp_texture_gain_w;	///< SP: texture gain(w)
}
LX_PE_SHP_SR_DE_T;


/**
 *	pe sr resolution enhancement(pre RE) normal control(ver.2) parameter type
 *	ver.2, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 shp_ui_main_pre[13];
	UINT8 shp_ti_ui_main_pre[3];
	UINT8 shp_tgen_ui_main_pre[10];
}
LX_PE_SHP_SR_RE2_CMN_T;

/**
 *	pe sr resolution enhancement(pre RE) misc. control parameter type
 *	ver.2, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 shp_cmn_pre[30];
	UINT8 shp_map_cmn_pre[48];
	UINT8 shp_balance_pre[52];
	UINT8 shp_ti_cmn_pre[12];
	UINT8 shp_tgen_cmn_pre[23];
}
LX_PE_SHP_SR_RE2_MISC_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.3, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main[12];
}
LX_PE_SHP_SR_RE2_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.3, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main[6];
}
LX_PE_SHP_SR_RE2_VER_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.2, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee[6];
}
LX_PE_SHP_SR_EE2_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.2, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de[6];
}
LX_PE_SHP_SR_DE2_T;

/**
 *	pe sr resolution enhancement(pre RE) normal control(ver.2) parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_pre[14];          ///< shp_ui_main_pre[14];
	UINT8  shp_ti_ui_main_pre[3];       ///< shp_ti_ui_main_pre[3];
	UINT8  shp_tgen_ui_main_pre[8];     ///< shp_tgen_ui_main_pre[8];
}
LX_PE_SHP_SR_RE3_CMN_T;

/**
 *	pe sr resolution enhancement(pre RE) misc. control parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_pre[30];             ///< shp_cmn_pre[30];
	UINT8  shp_map_cmn_pre[49];         ///< shp_map_cmn_pre[49];
	UINT8  shp_balance_pre[53];         ///< shp_balance_pre[53];
	UINT8  shp_ti_cmn_pre[12];           ///< shp_ti_cmn_pre[12];
	UINT8  shp_tgen_cmn_pre[23];        ///< shp_tgen_cmn_pre[23];
}
LX_PE_SHP_SR_RE3_MISC_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main_pre[7];       ///< shp_ui_h_main_pre[7];
}
LX_PE_SHP_SR_RE3_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main_pre[6];        ///< shp_ui_v_main_pre[6];
}
LX_PE_SHP_SR_RE3_VER_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_pre[10];               ///< shp_ee_pre[8];
}
LX_PE_SHP_SR_EE3_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de_pre[10];               ///< shp_de_pre[10];
}
LX_PE_SHP_SR_DE3_T;

/*=============O18========================*/

/**
 *	pe sr resolution enhancement(pre RE) normal control(ver.4) parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_4k[11]; 		 	///< shp_ui_main_4k[11];
	UINT8  shp_ti_ui_main_4k[3];		///< shp_ti_ui_main_4k[3];
}
LX_PE_SHP_SR_RE4_CMN_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main_4k[6];       ///< shp_ui_h_main_pre[7];
}
LX_PE_SHP_SR_RE4_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.4) parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main_4k[2];        ///< shp_ui_v_main_pre[6];
}
LX_PE_SHP_SR_RE4_VER_T;

/**
 *	pe sr resolution enhancement(pre RE) misc. control parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_4k[21]; 				///< shp_cmn_4k[21];
	UINT8  shp_map_cmn_4k[20]; 			///< shp_map_cmn_4k[20];
	UINT8  shp_balance_4k[30]; 			///< shp_balance_4k[30];
	UINT8  shp_ti_cmn_4k[12];			///< shp_ti_cmn_4k[12];
	UINT8  shp_simple_snr_4k[3];		///< shp_simple_snr_4k[3];
}
LX_PE_SHP_SR_RE4_MISC_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.4, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_4k[14];               ///< shp_ee_pre[8];
}
LX_PE_SHP_SR_EE4_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.3, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de_4k[14];               ///< shp_de_pre[10];
}
LX_PE_SHP_SR_DE4_T;

/**
 *	pe sr 2k resolution enhancement(pre RE) normal control(ver.4) parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_2k[14]; 			///< shp_ui_main_2k[14];
	UINT8  shp_ti_ui_main_2k[3];		///< shp_ti_ui_main_2k[3];
}
LX_PE_SHP_SR2K_RE_CMN_T;

/**
 *	pe sr 2k resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main_2k[6];	    	///< shp_ui_h_main_2k[6];
}
LX_PE_SHP_SR2K_RE_HOR_T;

/**
 *	pe sr 2k  resolution enhancement(RE) vertical control(ver.4) parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main_2k[2];        ///< shp_ui_v_main_pre[6];
}
LX_PE_SHP_SR2K_RE_VER_T;

/**
 *	pe sr 2k  resolution enhancement(pre RE) misc. control parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_2k[19]; 				///< shp_cmn_2k[19];
	UINT8  shp_djg_2k[8];				///< shp_djg_2k[8];
	UINT8  shp_map_cmn_2k[20]; 			///< shp_map_cmn_2k[20];
	UINT8  shp_balance_2k[30]; 			///< shp_balance_2k[30];
	UINT8  shp_ti_cmn_2k[12];			///< shp_ti_cmn_2k[12];
	UINT8  shp_simple_snr_2k[3];		///< shp_simple_snr_2k[3];
}
LX_PE_SHP_SR2K_RE_MISC_T;

/**
 *	pe sr 2k edge enhancement(EE) control parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_2k[14];               ///< shp_ee_pre[8];
}
LX_PE_SHP_SR2K_EE_T;

/**
 *	pe sr 2k  detail enhancement(DE) control parameter type
 *	ver.3, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de_2k[14];               ///< shp_de_pre[10];
}
LX_PE_SHP_SR2K_DE_T;
/*=============O20========================*/
/**
 *	pe resolution enhancement(RE) normal control(ver.1) parameter type
 *	ver.1, for O20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT8  shp_ui_main_vsd[15];     ///< shp_ui_main_vsd[15];
 	UINT8  shp_face_obj_vsd[8]; 	///< *new shp_face_obj_vsd[8]; 
}
LX_PE_SHP_RE1_CMN_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.1, for O20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_vsd[25];				///< shp_cmn_vsd[23];
	UINT8  shp_djg_vsd[8];				///< shp_djg_vsd[8];
	UINT8  shp_map_cmn_vsd[12];			///< shp_map_cmn_vsd[20];
	UINT8  shp_balance_vsd[30];			///< shp_balance_vsd[30];
	UINT8  shp_ti_cmn_vsd[14]; 			///< shp_ti_cmn_vsd[12];
	UINT8  shp_chroma_vsd[5];			///< shp_chroma_vsd[5];
}
LX_PE_SHP_RE1_MISC_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.1, for O20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_vsd[28];				///< shp_ee_vsd[28];
}
LX_PE_SHP_EE1_T;

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_ui_sqm_vsd[40];  ///< *new shp_ui_sqm_2k[29];
}
LX_PE_SHP_RE_SQM2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm_____val;	     ///< ui value
	UINT32 shp_sqm_cmn_vsd[51];		 ///< *new shp_sqm_cmn_2k[11];
}
LX_PE_SHP_RE_SQM2_DETAIL_T;

/**
 *	pe sr 2k  resolution enhancement(pre RE) misc. control parameter type
 *	for O20
 */

typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_2k[12]; 			///< shp_ui_main_2k[12];
	UINT16  shp_dnn_sr_vsd[17];			///< shp_dnn_sr_vsd[9] -> [17], SICREQ-529 ;
	UINT32 shp_luma_en_2k;              ///< added SICREQ-529
}
LX_PE_SHP_SR2K_RE1_CMN_T;
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_2k[17]; 				///< shp_cmn_2k[19];
	UINT8  shp_djg_2k[8];				///< shp_djg_2k[8];
	UINT8  shp_map_cmn_2k[12]; 			///< shp_map_cmn_2k[20];
	UINT8  shp_balance_2k[30]; 			///< shp_balance_2k[30];
	UINT8  shp_ti_cmn_2k[14];			///< shp_ti_cmn_2k[12];
}
LX_PE_SHP_SR2K_RE1_MISC_T;
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_2k[28];               ///< shp_ee_pre[8];
}
LX_PE_SHP_SR2K_EE1_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm___val;	///< ui value
	UINT32 shp_ui_sqm_2k[39];		 ///< *new shp_ui_sqm_vsd[39];
}
LX_PE_SHP_SR2K_SQM2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_sqm_cmn_2k[43];		 ///< *new shp_sqm_cmn_vsd[43];
}
LX_PE_SHP_SR2K_SQM2_DETAIL_T;


/*=============F20========================*/
/**
 *	pe resolution enhancement(RE) parameter type
 *	ver.1, for F20
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_val;
 	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT8  shp_face_obj_vsd[8];
	UINT32 shp_ui_sqm_vsd[40];
	UINT32 shp_sqm_cmn_vsd[51];
	UINT16 shp_dnn_sr_vsd[9];			///< shp_dnn_sr_vsd[9];
}
LX_PE_SHP_ALL_CMN_T;
/*=============F22========================*/
/**
 *	pe resolution enhancement(RE) parameter type
 *	ver.1, for F22
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_val;
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT16 shp_dnn_sr_vsd[9];
	UINT8  shp_face_obj_vsd[25];// diff from o20
	UINT32 shp_ui_sqm_vsd[40];
	UINT32 shp_sqm_cmn_vsd[71];// diff from o20
}
LX_PE_SHP1_ALL_CMN_T;

/*=============E60========================*/

/**
 *	pe sr 2k  resolution enhancement(pre RE) misc. control parameter type
 *	for O20
 */
 
//2k
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_2k[12]; 			///< shp_ui_main_2k[12];
}
LX_PE_SHP_SR2K_RE2_CMN_T;

//4k
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_4k[12]; 			///< shp_ui_main_4k[12];
	UINT16  shp_dnn_sr_4k[9];			///< shp_dnn_sr_vsd[9];
}
LX_PE_SHP_SR4K_RE1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_4k[17]; 				///< shp_cmn_4k[19];
	UINT8  shp_djg_4k[8];				///< shp_djg_4k[8];
	UINT8  shp_map_cmn_4k[12]; 			///< shp_map_cmn_4k[20];
	UINT8  shp_balance_4k[30]; 			///< shp_balance_4k[30];
	UINT8  shp_ti_cmn_4k[14];			///< shp_ti_cmn_4k[12];
}
LX_PE_SHP_SR4K_RE1_MISC_T;
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_4k[28];               ///< shp_ee_pre[8];
}
LX_PE_SHP_SR4K_EE1_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm___val;	///< ui value
	UINT32 shp_ui_sqm_4k[39];		 ///< *new shp_ui_sqm_vsd[39];
}
LX_PE_SHP_SR4K_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_sqm_cmn_4k[43];		 ///< *new shp_sqm_cmn_vsd[43];
}
LX_PE_SHP_SR4K_SQM1_DETAIL_T;

//VSD
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm_____val;	     ///< ui value
	UINT32 shp_sqm_cmn_vsd[67];		 ///< *new shp_sqm_cmn_2k[11];
}
LX_PE_SHP_RE_SQM3_DETAIL_T;

/*=============O22========================*/
/**
 *	pe resolution enhancement(RE) normal control(ver.1) parameter type
 *	ver.1, for O22
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT8  shp_ui_main_vsd[15];     ///< shp_ui_main_vsd[15];
 	UINT8  shp_face_obj_vsd[25]; 	///< *new shp_face_obj_vsd[8];
 	UINT32 shp_luma_en_vsd;         ///< added SICREQ-529
}
LX_PE_SHP_RE2_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm_____val;	     ///< ui value
	UINT32 shp_sqm_cmn_vsd[71];		 ///< *new shp_sqm_cmn_2k[11];
}
LX_PE_SHP_RE_SQM4_DETAIL_T;

/*=============O22n2========================*/

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_ui_sqm_vsd[50];  //// shp_ui_sqm_vsd[40] -> shp_ui_sqm_vsd[50]  <- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½ <1>ï¿½ï¿½
}
LX_PE_SHP_RE_SQM3_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm___val;	///< ui value
	UINT32 shp_ui_sqm_2k[49];///< shp_ui_sqm_2k[39] -> ?shp_ui_sqm_2k[49] <- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½ <2>ï¿½ï¿½ 
}
LX_PE_SHP_SR2K_SQM3_CMN_T;

/*=============O24========================*/

// requested SICREQ-529

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_sqm_cmn_2k[51];	///<shp_sqm_cmn_2k[43] -> shp_sqm_cmn_2k[51] <- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½ <3>ï¿½ï¿½
}
LX_PE_SHP_SR2K_SQM3_DETAIL_T;
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT8  shp_luma_ylut_2k[16];     ///< 
 	UINT8  shp_luma_ylut_vsd[16]; 	///<  
}
LX_PE_SHP_ELLIPS_LUT_T;

//for window 1,2,3
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	LX_PE_SHP_SR2K_RE1_CMN_T sr_sub_cmn_ui;
	LX_PE_SHP_SR2K_SQM3_CMN_T sr_sub_sqm_ui;	
}
LX_PE_SHP_SR_RE1_CMN_SUB_T;

//for window 1,2,3
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	LX_PE_SHP_SR2K_RE1_MISC_T sr_sub_misc;
	LX_PE_SHP_SR2K_SQM3_DETAIL_T sr_sub_sqm_cmn;
}
LX_PE_SHP_SR_RE1_MISC_SUB_T;

/*=============O26========================*/

// requested SICREQ-1181
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT8  shp_ui_main_vsd[15];     ///< shp_ui_main_vsd[15];
 	UINT8  shp_face_obj_vsd[17]; 	///< *new shp_face_obj_vsd[8];
 	UINT32 shp_luma_en_vsd;         ///< added SICREQ-529
}
LX_PE_SHP_RE3_CMN_T;


typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_ui_sqm_vsd[65];  //// shp_ui_sqm_vsd[50];  ¡æ shp_ui_sqm_vsd[65];
}
LX_PE_SHP_RE_SQM4_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm_____val;	     ///< ui value
	UINT32 shp_sqm_cmn_vsd[87];		 ///< shp_sqm_cmn_vsd[71];  ¡æ shp_sqm_cmn_vsd[87];
}
LX_PE_SHP_RE_SQM5_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm___val;	///< ui value
	UINT32 shp_ui_sqm_2k[57];///< shp_ui_sqm_2k[49];  ¡æ shp_ui_sqm_2k[57];
}
LX_PE_SHP_SR2K_SQM4_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_sqm_cmn_2k[59];	///<shp_sqm_cmn_2k[43] -> shp_sqm_cmn_2k[51] <- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½ <3>ï¿½ï¿½
}
LX_PE_SHP_SR2K_SQM4_DETAIL_T;

//for window 1,2,3
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	LX_PE_SHP_SR2K_RE1_CMN_T sr_sub_cmn_ui;
	LX_PE_SHP_SR2K_SQM4_CMN_T sr_sub_sqm_ui;	
}
LX_PE_SHP_SR_RE2_CMN_SUB_T;

//for window 1,2,3
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	LX_PE_SHP_SR2K_RE1_MISC_T sr_sub_misc;
	LX_PE_SHP_SR2K_SQM4_DETAIL_T sr_sub_sqm_cmn;
}
LX_PE_SHP_SR_RE2_MISC_SUB_T;


/*#############################PE1################################*/




/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.3, for H15
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* shp_cmn_post[23]*/
	UINT8 edge_Y_filter_en;				///<edge_Y_filter en
	UINT8 e_gain_max;					///<"A to edge weight: gain2.4u"
	UINT8 f_gain_max;					///<A to flat weight: gain
	UINT8 der_v_en;						///<der-v enable
	UINT8 der_gain_mapping;				///<"weight selection for weighted average of bif and input""00"" : A-to weight""01"" : A-map""10  : A-to weight""11"" : A-map"
	UINT8 max_sel;						///<"A-expansion size (H)""000"" : do not expand""001"" : 3-tap""010"" : 5-tap""011"" : 7-tap""100"" : 9-tap""101"" : 11-tapo.w   : do not expand"
	UINT8 mp_laplacian_weight;			///<Weight for Laplacian operator output
	UINT8 sp_laplacian_weight;			///<Weight for Laplacian operator output
	UINT8 flat_filter_en;				///<flat filter en
	UINT8 flat_filter_type;				///<"flat filter fype'0' : bi-lateral filter'1': average filter"
	UINT8 flat_filter_gain;				///<flat filter gain(2.4u)
	UINT8 edf_en;						///<edge-directional de-jagging enable
	UINT8 center_blur_mode;				///<"center-pixel averaging for edge-direction calculation'0' : use original pixel'1' : use avg. pixel"
	UINT8 count_diff_th;				///<matchness threshod for edge-direction decision
	UINT8 n_avg_mode;					///<"neighbor-pixel averaging : mode for dual edges'0' : use 12 direction results'1' : use 36 direction results"
	UINT8 line_variation_diff_threshold;///<line-variation threshold for edge-direction decision
	UINT8 level_th;						///<g0: level threshold
	UINT8 protect_th;					///<G1: protect threshold
	UINT8 n_avg_gain;					///<neighborhood pixel averaing : gain
	UINT8 reg_g0_cnt_min;				///<G0 : edf_count_min
	UINT8 reg_g0_mul;					///<G0 : n x ( Count - min_cnt_th )
	UINT8 reg_g1_protect_min;			///<G1 : Min diff th - LR Diff
	UINT8 reg_g1_mul;					///<G1 : n x ( th - LR_Diff )
	/* shp_map_cmn_post[36]*/
	UINT8 reg_cross_th_sc;				///<"<A-gain for edge filter>edge-map gain(2.5u)edge map"
	UINT8 reg_cross_th;					///<
	UINT8 reg_mul_base_t;				///<
	UINT8 reg_mul_base_e;				///<
	UINT8 reg_a_map_h_size;				///<
	UINT8 reg_a_nomalize_en;			///<nomalize by mulbase
	UINT8 reg_edge_alpha_mul;			///<get_t_map (alpha*t_map - beta*a_map)
	UINT8 reg_edge_beta_mul;			///<get_t_map (alpha*t_map - beta*a_map)
	UINT8 reg_a_lut_edge_x0;			///<reg_a_lut_edge
	UINT8 reg_a_lut_edge_y0;			///<reg_a_lut_edge
	UINT8 reg_a_lut_edge_x1;			///<reg_a_lut_edge
	UINT8 reg_a_lut_edge_y1;			///<reg_a_lut_edge
	UINT8 reg_a_lut_detail_x0;			///<reg_a_lut_detail
	UINT8 reg_a_lut_detail_y0;			///<reg_a_lut_detail
	UINT8 reg_a_lut_detail_x1;			///<reg_a_lut_detail
	UINT8 reg_a_lut_detail_y1;			///<reg_a_lut_detail
	UINT8 reg_edge_minmax_x0;			///<reg_edge_minmax
	UINT8 reg_edge_minmax_y0;			///<reg_edge_minmax
	UINT8 reg_edge_minmax_x1;			///<reg_edge_minmax
	UINT8 reg_edge_minmax_y1;			///<reg_edge_minmax
	UINT8 reg_t_cut_resolution;			///<
	UINT8 reg_t_nomalize_en;			///<nomalize by mulbase
	UINT8 reg_detail_alpha_mul;			///<get e_map (alpha*a_map - beta*t_map)
	UINT8 reg_detail_beta_mul;			///<get e_map (alpha*a_map - beta*t_map)
	UINT8 reg_t_lut_edge_x0;			///<reg_t_lut_edge
	UINT8 reg_t_lut_edge_y0;			///<reg_t_lut_edge
	UINT8 reg_t_lut_edge_x1;			///<reg_t_lut_edge
	UINT8 reg_t_lut_edge_y1;			///<reg_t_lut_edge
	UINT8 reg_t_lut_detail_x0;			///<reg_t_lut_detail
	UINT8 reg_t_lut_detail_y0;			///<reg_t_lut_detail
	UINT8 reg_t_lut_detail_x1;			///<reg_t_lut_detail
	UINT8 reg_t_lut_detail_y1;			///<reg_t_lut_detail
	UINT8 reg_detail_minmax_x0;			///<reg_detail_minmax
	UINT8 reg_detail_minmax_y0;			///<reg_detail_minmax
	UINT8 reg_detail_minmax_x1;			///<reg_detail_minmax
	UINT8 reg_detail_minmax_y1;			///<reg_detail_minmax
	/* shp_balance_post[42]*/
	UINT8 mp_gb_en;						///< "0 : disable'1' : enable"
	UINT8 mp_gb_mode;					///< "delta(x-axis) resolution'0' : 8bit'1' : 10bit"
	UINT8 mp_gb_x1;						///< mp_gb_x1
	UINT8 mp_gb_x2;						///< mp_gb_x2
	UINT8 mp_gb_y1;						///< mp_gb_y1
	UINT8 mp_gb_y2;						///< mp_gb_y2
	UINT8 mp_gb_y3;						///< mp_gb_y3
	UINT8 sp_gb_en;						///< "0 : disable'1' : enable"
	UINT8 sp_gb_mode;					///< "delta(x-axis) resolution'0' : 8bit'1' : 10bit"
	UINT8 sp_gb_x1;						///< sp_gb_x1
	UINT8 sp_gb_x2;						///< sp_gb_x2
	UINT8 sp_gb_y1;						///< sp_gb_y1
	UINT8 sp_gb_y2;						///< sp_gb_y2
	UINT8 sp_gb_y3;						///< sp_gb_y3
	UINT8 mp_lum1_x_L0;					///< mp_lum1_x_L0
	UINT8 mp_lum1_x_L1;					///< mp_lum1_x_L1
	UINT8 mp_lum1_x_H0;					///< mp_lum1_x_H0
	UINT8 mp_lum1_x_H1;					///< mp_lum1_x_H1
	UINT8 mp_lum1_y0;					///< mp_lum1_y0
	UINT8 mp_lum1_y1;					///< mp_lum1_y1
	UINT8 mp_lum1_y2;					///< mp_lum1_y2
	UINT8 mp_lum2_x_L0;					///< mp_lum2_x_L0
	UINT8 mp_lum2_x_L1;					///< mp_lum2_x_L1
	UINT8 mp_lum2_x_H0;					///< mp_lum2_x_H0
	UINT8 mp_lum2_x_H1;					///< mp_lum2_x_H1
	UINT8 mp_lum2_y0;					///< mp_lum2_y0
	UINT8 mp_lum2_y1;					///< mp_lum2_y1
	UINT8 mp_lum2_y2;					///< mp_lum2_y2
	UINT8 sp_lum1_x_L0;					///< sp_lum1_x_L0
	UINT8 sp_lum1_x_L1;					///< sp_lum1_x_L1
	UINT8 sp_lum1_x_H0;					///< sp_lum1_x_H
	UINT8 sp_lum1_x_H1;					///< sp_lum1_x_H
	UINT8 sp_lum1_y0;					///< sp_lum1_y0
	UINT8 sp_lum1_y1;					///< sp_lum1_y1
	UINT8 sp_lum1_y2;					///< sp_lum1_y2
	UINT8 sp_lum2_x_L0;					///< sp_lum2_x_L0
	UINT8 sp_lum2_x_L1;					///< sp_lum2_x_L1
	UINT8 sp_lum2_x_H0;					///< sp_lum2_x_H0
	UINT8 sp_lum2_x_H1;					///< sp_lum2_x_H1
	UINT8 sp_lum2_y0;					///< sp_lum2_y0
	UINT8 sp_lum2_y1;					///< sp_lum2_y1
	UINT8 sp_lum2_y2;					///< sp_lum2_y2
	/* shp_ti_cmn_post[9]*/
	UINT8 reg_ti_enable_pti_v;				///< reg_ti_enable
	UINT8 reg_mm_tap_size_pti_v;			///< reg_mm_tap_size
	UINT8 reg_avg_tap_size_pti_v;			///< reg_avg_tap_size
	UINT8 reg_ti_enable_pti_h;				///< reg_ti_enable
	UINT8 reg_mm_tap_size_pti_h;			///< reg_mm_tap_size
	UINT8 reg_avg_tap_size_pti_h;			///< reg_avg_tap_size
	UINT8 reg_enable_sti;					///< reg_ti_enable
	UINT8 reg_mm_tap_size_sti;				///< reg_mm_tap_size
	UINT8 reg_avg_tap_size_sti;				///< reg_avg_tap_size
	/* shp_cti_cmn_post[8]*/
	UINT8 cti_en;						///< cti enable
	UINT8 coring_th0;					///<
	UINT8 coring_th1;					///<
	UINT8 coring_map_filter;			///< """000"" : no filtering""001"" : 5-tap filtering""010"" : 7-tap filtering""011"" : 9-tap filtering""100: : 11-tap filtering""101"" : 13-tap filtering"
	UINT8 coring_tap_size;				///< """000"" 21 tap""001"" 19 tap""010"" 17 tap""011"" 15 tap""100"" 13 tap""101"" 11 tap""110""  9 tap"
	UINT8 ycm_en1;						///< ycm1 enable
	UINT8 ycm_band_sel;					///< ycm_band_sel
	UINT8 ycm_diff_th;					///< ycm_diff_th
	/* shp_tgen_cmn_post[23]*/
	UINT8 tgen_on_off;					///< tgen_on_off
	UINT8 tg_delta_H_bound;				///< tg_delta_H_bound
	UINT8 tg_delta_L_bound;				///< tg_delta_L_bound
	UINT8 tg_delta_max;					///< tg_delta_max
	UINT8 tg_delta_scale;				///< tg_delta_scale
	UINT8 tg_rnd_th;					///< tg_rnd_th
	UINT8 tg_delta_wcurr;				///< tg_delta_wcurr
	UINT8 tg_lc_ldr_th;					///< tg_lc_ldr_th
	UINT8 tg_dr_ratio;					///< tg_dr_ratio
	UINT8 tg_dr_th;						///< tg_dr_th
	UINT8 tg_mm_offset;					///< tg_mm_offset
	UINT8 tg_mm_sel_mode;				///< tg_mm_sel_mode
	UINT8 tg_lavg_th;					///< tg_lavg_th
	UINT8 tg_gs_rnd;					///< = tg_gs_rnd(.yml) * tg_ls_mv >> 5
	UINT8 tg_gs_mm;						///< = tg_gs_mm(.yml) * tg_ls_mv >> 5
	UINT8 tg_gain0;						///<	 tg_gain0
	UINT8 tg_gain1;						///< tg_gain1
	UINT8 tg_gain2;						///< tg_gain2
	UINT8 tg_gain3;						///< tg_gain3
	UINT8 tg_gain4;						///< tg_gain4
	UINT8 tg_gain5;						///< tg_gain5
	UINT8 tg_gain6;						///< tg_gain6
	UINT8 tg_gain7;						///< tg_gain7
}
LX_PE_SHP_RE4_MISC_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.2, for H13Bx, M14Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 reg_csft_gain;				///< reg_csft_gain: center shift gain(1.5u)
	UINT8 edge_filter_white_gain;		///< edge filter white gain upper 2bit: int, lower 4 bit: float, max: 63(dec) 3.9999
	UINT8 edge_filter_black_gain;		///< edge filter black gain
	UINT8 a_gen_width;					///< width size for dynamic range
	UINT8 mp_horizontal_gain;			///< horizontal gain(3.5u)
	UINT8 sp_horizontal_gain;			///< horizontal gain(3.5u)
	UINT8 e_gain_th1;					///< a to edge gain: th1
	UINT8 e_gain_th2;					///< a to edge gain: th2
	UINT8 f_gain_th1;					///< a to flat gain: th1
	UINT8 f_gain_th2;					///< a to flat gain: th2
	UINT8 coring_th;					///< coring_th
	UINT8 y_gain;						///< y_gain
	UINT8 c_gain;						///< c_gain
}
LX_PE_SHP_RE2_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.2, for H13Bx, M14Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 bif_manual_th;				///< bilateral filter threshold
	UINT8 csft_gain;					///< center-shift gain (1.5u)
	UINT8 gain_b;						///< gain(b) : 2.5u
	UINT8 gain_w;						///< gain(w): 2.5u
	UINT8 mmd_sel;						///< "000" : 11 tap,"001" : 9-tap,"010" : 7-tap,"011" : 5-tap,"100" : 3-tap ,o.w   : 11-tap
	UINT8 mp_vertical_gain;				///< vertical gain(3.5u)
	UINT8 sp_vertical_gain;				///< vertical gain(3.5u)
	UINT8 gain_th1;						///< a-to-weight: th1
	UINT8 gain_th2;						///< a-to-weight: th2
}
LX_PE_SHP_RE2_VER_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.2, for H13Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* cti */
	UINT8 cti_en;						///< cti enable
	UINT8 coring_th0;					///< th with coring th0 mmd
	UINT8 coring_th1;					///< coring_th1
	UINT8 coring_map_filter;			///< "000" : no ,"001" : 5-tap ,"010" : 7-tap ,"011" : 9-tap ,100: : 11-tap ,"101" : 13-tap
	UINT8 coring_tap_size;				///< "000" 21 tap,"001" 19 tap,"010" 17 tap,"011" 15 tap,"100" 13 tap,"101" 11 tap,"110"  9 tap
	UINT8 ycm_en1;						///< y c miss matching.
	UINT8 ycm_band_sel;					///< ycm_band_sel
	UINT8 ycm_diff_th;					///< ycm_diff_th
	/* h */
	UINT8 edge_y_filter_en;				///< edge_y_filter_en
	UINT8 e_gain_max;					///< a to edge weight: gain
	UINT8 f_gain_max;					///< a to flat weight: gain
	UINT8 mp_lap_h_mode;				///< "000" : h3,"001" : h4,"010" : h5,"011" : h6,"100" : h7
	UINT8 sp_lap_h_mode;				///< "00" : h3,"01" : h5,"10" : h7,"11" : not used
	/* v */
	UINT8 der_v_en;						///< der-v enable
	UINT8 der_gain_mapping;				///< "00" : a-to weight,"01" : a-map,"10  : a-to weight,"11" : a-map
	UINT8 max_sel;						///< ,"000" : do not expand,"001" : 3-tap,"010" : 5-tap,"011" : 7-tap,"100" : 9-tap,"101" : 11-tap,o.w   : do not expand
	UINT8 mp_lap_v_mode;				///< laplacian v mode,"000" : v3,"001" : v4,"010" : v5,"011" : v6,"100" : v7
	UINT8 sp_lap_v_mode;				///< 0' : v3,'1' : v5
	/* cmm */
	UINT8 mp_sobel_weight;				///< weight for sobel operator output
	UINT8 mp_laplacian_weight;			///< weight for laplacian operator output
	UINT8 sp_sobel_weight;				///< weight for sobel operator output
	UINT8 sp_laplacian_weight;			///< weight for laplacian operator output
	UINT8 flat_en;						///< flat-filter enable
	UINT8 flat_filter_type;				///< '0' : bi-lateral filter,'1': average filter
	/*d_jag*/
	UINT8 edf_en;						///< edge-directional de-jagging enable
	UINT8 center_blur_en;				///< '0' : use original pixel,'1' : use avg. pixel
	UINT8 count_diff_th;				///< matchness threshod for edge-direction decision
	UINT8 n_avg_mode;					///< mode for dual edges,'0' : use 12 direction results,'1' : use 36 direction results
	UINT8 line_variation_diff_th;		///< line-variation threshold for edge-direction decision
	UINT8 level_th;						///< g0: level threshold
	UINT8 protect_th;					///< g1: protect threshold
	UINT8 n_avg_gain;					///< neighborhood pixel averaing : gain
	UINT8 edf_count_min;				///< g0 : edf_count_min
	UINT8 edf_count_max;				///< g0 : edf_count_max
	UINT8 dj_h_count_min;				///< g0 : dj_h_count_min
	UINT8 dj_h_count_max;				///< g0 : dj_h_count_max
	UINT8 dj_v_count_min;				///< g0 : dj_v_count_min
	UINT8 dj_v_count_max;				///< g0 : dj_v_count_max
	/*e_map*/
	UINT8 amap2_sel;					///< "00" : 5-tap,"01" : 7-tap,"10" : 9-tap,"11" : 15-tap
	UINT8 amap_gain;					///< edge-map gain
	UINT8 ga_max;						///< <a to edge weight control>
	UINT8 ga_th0;						///< th0
	UINT8 ga_th1;						///< th1
	/*t_map*/
	UINT8 amap1_sel;					///< "00" : 15-tap,"01" : 9-tap,"10" : 7-tap,"11" : 5-tap
	UINT8 tmap_max_sel;					///< "000" : bypass,"001" : 5-tap,"010" : 7-tap,"011" : 9-tap,"100" : 11-tap,"101" : 13-tap,"110" : 15-tap,"111" : 17-tap
	UINT8 avg_sel;						///< "00" : bypass,"01" : 3x1 average [1 2 1],"10" : 5x1 average [1 2 2 2 1 ],"11" : bypass
	UINT8 tmap_gain;					///< texture-map gain(2.5u)
	UINT8 gt_th0;						///< th0
	UINT8 gt_th0a;						///< th0a
	UINT8 gt_th0b;						///< th0b
	UINT8 gt_th1;						///< th1
	UINT8 gt_gain0a;					///< gain(th0a) : 1.5u
	UINT8 gt_gain0b;					///< gain(th0b) : 1.5u
	UINT8 gt_max;						///< gain(th1) :1.5u
	UINT8 a2tw_en;						///< strong edge protection ,'0': disable,'1': enable
	UINT8 a2tw_th0;						///< strong edge: th0
	UINT8 a2tw_th1;						///< strong edge: th1
	UINT8 exp_mode;						///< "00" : bypass,"01" : 3-tap expansion,"10" : 5-tap expansion,"11" : bypass
	UINT8 coring_mode1;					///< coring mode "00" : remove 0,"01" : remove 0/1,"10" : remove 0/1/2,"11" : remove 0/1/2/3
	UINT8 coring_mode2;					///< coring mode,"00" : remove 0,"01" : remove 0/1,"10" : remove 0/1/2,"11" : remove 0/1/2/3
	UINT8 g_th0;						///< <edge/texture blending> th0
	UINT8 g_th1;						///< th1
	UINT16 var_th;						///< flat region rejection threshold if variance < var_th, reject the region
	/*ti-h*/
	UINT8 enable;						///< ti-h enable
	UINT8 coring_step;					///< n : 2^n (transition width)
	UINT8 gain0_en;						///< gain0 enable
	UINT8 gain1_en;						///< gain1 enable
	UINT8 gain0_th0;					///< gain0_th0
	UINT8 gain1_th1;					///< gain1_th1
	UINT8 gain1_div_mode;				///< gain1: div mode,"00" : div by 32,"01" : div by 16,"10" : div by 8,"11" : div by 64
}
LX_PE_SHP_RE2_MISC_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.3, for M14Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* h 5 */
	UINT8 edge_y_filter_en;				///< edge_y_filter_en
	UINT8 e_gain_max;					///< a to edge weight: gain
	UINT8 f_gain_max;					///< a to flat weight: gain
	UINT8 mp_lap_h_mode;				///< "000" : h3,"001" : h4,"010" : h5,"011" : h6,"100" : h7
	UINT8 sp_lap_h_mode;				///< "00" : h3,"01" : h5,"10" : h7,"11" : not used
	/* v 5 */
	UINT8 der_v_en;						///< der-v enable
	UINT8 der_gain_mapping;				///< "00" : a-to weight,"01" : a-map,"10  : a-to weight,"11" : a-map
	UINT8 max_sel;						///< ,"000" : do not expand,"001" : 3-tap,"010" : 5-tap,"011" : 7-tap,"100" : 9-tap,"101" : 11-tap,o.w   : do not expand
	UINT8 mp_lap_v_mode;				///< laplacian v mode,"000" : v3,"001" : v4,"010" : v5,"011" : v6,"100" : v7
	UINT8 sp_lap_v_mode;				///< 0' : v3,'1' : v5
	/* cmm 6 */
	UINT8 mp_sobel_weight;				///< weight for sobel operator output
	UINT8 mp_laplacian_weight;			///< weight for laplacian operator output
	UINT8 sp_sobel_weight;				///< weight for sobel operator output
	UINT8 sp_laplacian_weight;			///< weight for laplacian operator output
	UINT8 flat_en;						///< flat-filter enable
	UINT8 flat_filter_type;				///< '0' : bi-lateral filter,'1': average filter
	/*d_jag 12 */
	UINT8 edf_en;						///< edge-directional de-jagging enable
	UINT8 center_blur_mode;				///< [m14b]center-pixel averaging for edge-direction calculation,0:use original pixel, 1:use avg. pixel
	UINT8 count_diff_th;				///< matchness threshod for edge-direction decision
	UINT8 n_avg_mode;					///< mode for dual edges,'0' : use 12 direction results,'1' : use 36 direction results
	UINT8 line_variation_diff_th;		///< line-variation threshold for edge-direction decision
	UINT8 level_th;						///< g0: level threshold
	UINT8 protect_th;					///< g1: protect threshold
	UINT8 n_avg_gain;					///< neighborhood pixel averaing : gain
	UINT8 reg_g0_cnt_min;				///< [m14b]G0 : edf_count_min
	UINT8 reg_g0_mul;					///< [m14b]G0 : n x ( Count - min_cnt_th )
	UINT8 reg_g1_protect_min;			///< [m14b]G1 : Min diff th - LR Diff
	UINT8 reg_g1_mul;					///< [m14b]G1 : n x ( th - LR_Diff )
	/*e_map 5 */
	UINT8 amap2_sel;					///< "00" : 5-tap,"01" : 7-tap,"10" : 9-tap,"11" : 15-tap
	UINT8 amap_gain;					///< edge-map gain
	UINT8 ga_max;						///< <a to edge weight control>
	UINT8 ga_th0;						///< th0
	UINT8 ga_th1;						///< th1
	/*t_map 22*/
	UINT8 amap1_sel;					///< "00" : 15-tap,"01" : 9-tap,"10" : 7-tap,"11" : 5-tap
	UINT8 tmap_max_sel;					///< "000" : bypass,"001" : 5-tap,"010" : 7-tap,"011" : 9-tap,"100" : 11-tap,"101" : 13-tap,"110" : 15-tap,"111" : 17-tap
	UINT8 avg_sel;						///< "00" : bypass,"01" : 3x1 average [1 2 1],"10" : 5x1 average [1 2 2 2 1 ],"11" : bypass
	UINT8 tmap_gain;					///< texture-map gain(2.5u)
	UINT8 gt_th0;						///< th0
	UINT8 gt_th0a;						///< th0a
	UINT8 gt_th0b;						///< th0b
	UINT8 gt_th1;						///< th1
	UINT8 gt_gain0a;					///< gain(th0a) : 1.5u
	UINT8 gt_gain0b;					///< gain(th0b) : 1.5u
	UINT8 gt_max;						///< gain(th1) :1.5u
	UINT8 a2tw_en;						///< strong edge protection ,'0': disable,'1': enable
	UINT8 a2tw_th0;						///< strong edge: th0
	UINT8 a2tw_th1;						///< strong edge: th1
	UINT8 exp_mode;						///< "00" : bypass,"01" : 3-tap expansion,"10" : 5-tap expansion,"11" : bypass
	UINT8 coring_mode1;					///< coring mode "00" : remove 0,"01" : remove 0/1,"10" : remove 0/1/2,"11" : remove 0/1/2/3
	UINT8 coring_mode2;					///< coring mode,"00" : remove 0,"01" : remove 0/1,"10" : remove 0/1/2,"11" : remove 0/1/2/3
	UINT8 g_th0;						///< <edge/texture blending> th0
	UINT8 g_th1;						///< th1
	UINT8 var_h_th;						///< [m14b]flat region rejection threshold (H-Direction T-Map)if variance < var_th, reject the region
	UINT8 var_v_th;						///< [m14b]flat region rejection threshold (V-Direction T-Map)if variance < var_th, reject the region
	UINT8 tmap_sc_var_th;				///< [m14b]flat region rejection threshold (for SC T-Map)if variance < var_th, reject the region
	/*ti-h 7 */
	UINT8 enable;						///< ti-h enable
	UINT8 coring_step;					///< n : 2^n (transition width)
	UINT8 gain0_en;						///< gain0 enable
	UINT8 gain1_en;						///< gain1 enable
	UINT8 gain0_th0;					///< gain0_th0
	UINT8 gain0_th1;					///< [m14b]gain0_th1
	UINT8 gain1_div_mode;				///< gain1: div mode,"00" : div by 32,"01" : div by 16,"10" : div by 8,"11" : div by 64
	/* cti 8 */
	UINT8 cti_en;						///< cti enable
	UINT8 coring_th0;					///< th with coring th0 mmd
	UINT8 coring_th1;					///< coring_th1
	UINT8 coring_map_filter;			///< "000" : no ,"001" : 5-tap ,"010" : 7-tap ,"011" : 9-tap ,100: : 11-tap ,"101" : 13-tap
	UINT8 coring_tap_size;				///< "000" 21 tap,"001" 19 tap,"010" 17 tap,"011" 15 tap,"100" 13 tap,"101" 11 tap,"110"  9 tap
	UINT8 ycm_en1;						///< y c miss matching.
	UINT8 ycm_band_sel;					///< ycm_band_sel
	UINT8 ycm_diff_th;					///< ycm_diff_th
}
LX_PE_SHP_RE3_MISC_T;

/**
 *	pe resolution enhancement(RE) normal control(ver.4) parameter type
 *	ver.4, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 shp_ui_main_post[13];
	UINT8 shp_ti_ui_main_post[3];
	UINT8 shp_cti_ui_main_post[4];
	UINT8 shp_tgen_ui_main_post[10];
}
LX_PE_SHP_RE4_CMN_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.3, for H15C, M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 shp_cmn_post[30];
	UINT8 shp_map_cmn_post[48];
	UINT8 shp_balance_post[52];
	UINT8 shp_ti_cmn_post[12];
	UINT8 shp_cti_cmn_post[8];
	UINT8 shp_tgen_cmn_post[23];
}
LX_PE_SHP_RE5_MISC_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.3, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main[12];
}
LX_PE_SHP_RE3_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.3, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main[6];
}
LX_PE_SHP_RE3_VER_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.2, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee[6];
}
LX_PE_SHP_EE2_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.2, for M16
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de[6];
}
LX_PE_SHP_DE2_T;

/*=================M16P & M16PP=================================*/

/**
 *	pe resolution enhancement(RE) normal control(ver.5) parameter type
 *	ver.5, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_post[14];        ///< shp_ui_main_post[14];
	UINT8  shp_ti_ui_main_post[3];      ///< shp_ti_ui_main_post[3];
	UINT8  shp_cti_ui_main_post[4];     ///< m16P -shp_cti_cmn_post[1], m16pp-shp_cti_cmn_post[4];
}
LX_PE_SHP_RE5_CMN_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.6, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_post[30];            ///< shp_cmn_post[30];
	UINT8  shp_map_cmn_post[49];        ///< shp_map_cmn_post[49];
	UINT8  shp_balance_post[53];        ///< shp_balance_post[53];
	UINT8  shp_ti_cmn_post[12];         ///< shp_ti_cmn_post[12];
	UINT8  shp_simple_snr_post[3];      ///< shp_simple_snr_post[3];
	UINT8  shp_cti_cmn_post[8];         ///< m16P -shp_cti_cmn_post[7], m16pp -shp_cti_cmn_post[8];
	UINT8  shp_motion_post[9];       	///< shp_motion_post[23];
	UINT8  shp_chroma_post[5];    		///< shp_chroma_post[10];
}
LX_PE_SHP_RE6_MISC_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.4, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main_post[7];		///< shp_ui_h_main_post[7];
}
LX_PE_SHP_RE4_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.4, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main_post[2];       ///< shp_ui_v_main_post[2];
}
LX_PE_SHP_RE4_VER_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_post[8];              ///< shp_ee_post[8];
}
LX_PE_SHP_EE3_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.3, for M16P
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de_post[8];              ///< shp_de_post[8];
}
LX_PE_SHP_DE3_T;


typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  iir_en;						//uIIREnBit
	UINT8  psp_en;						//uPspEnBit
	UINT8  chroma_protection_en;		//uChrmProtectEnBit
	UINT8  map_master_gain;				//uMapGain
	UINT8  iir_gain;					//uIIRGain
	UINT16 cb_offset_gain;				//uCbOffset
	UINT16 cr_offset_gain;				//uCrOffset
	UINT8  position_lut_x[16];			//0~255, uPerspectiveLUT_x
	UINT8  position_lut_y[16];			//0~255 uPerspectiveLUT_y
	UINT16 psp_lut_x[17];				//0~1024 uLumaLUT_x
	UINT16 psp_lut_y[17];				//0~1024 uLumaLUT_y
}
LX_PE_SHP_PSP_T;

/*==================O18===========================*/
/**
 *	pe resolution enhancement(RE) normal control(ver.6) parameter type
 *	ver.6, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_main_vsd[15];        ///< shp_ui_main_vsd[15];
	UINT8  shp_ti_ui_main_vsd[3];      ///< shp_ti_ui_main_vsd[3];
	UINT8  shp_cti_ui_main_vsd[4];     ///< shp_cti_ui_main_vsd[4];
}
LX_PE_SHP_RE6_CMN_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.5) parameter type
 *	ver.5, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_h_main_vsd[6];		///< shp_ui_h_main_vsd[7];
}
LX_PE_SHP_RE5_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.5) parameter type
 *	ver.5, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_ui_v_main_vsd[2];       ///< shp_ui_v_main_vsd[2];
}
LX_PE_SHP_RE5_VER_T;
/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.6, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8  shp_cmn_vsd[23];				///< shp_cmn_vsd[23];
	UINT8  shp_djg_vsd[8];				///< shp_djg_vsd[8];
	UINT8  shp_map_cmn_vsd[20];			///< shp_map_cmn_vsd[20];
	UINT8  shp_balance_vsd[30];			///< shp_balance_vsd[30];
	UINT8  shp_ti_cmn_vsd[12]; 			///< shp_ti_cmn_vsd[12];
	UINT8  shp_simple_snr_vsd[3];		///< shp_simple_snr_vsd[3];
	UINT8  shp_cti_cmn_vsd[8]; 			///< shp_cti_cmn_vsd[8];
	UINT8  shp_motion_vsd[9];			///< shp_motion_vsd[9];
	UINT8  shp_chroma_vsd[5];			///< shp_chroma_vsd[5];
}
LX_PE_SHP_RE7_MISC_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_ee_vsd[14];				///< shp_ee_vsd[14];
}
LX_PE_SHP_EE4_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.4, for O18
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_de_vsd[14];				///< shp_ee_vsd[14];
}
LX_PE_SHP_DE4_T;

typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_ui_sqm_vsd[30];  ///< *new shp_ui_sqm_2k[29];
}
LX_PE_SHP_RE_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm_____val;	     ///< ui value
	UINT32 shp_sqm_cmn_vsd[19];		 ///< *new shp_sqm_cmn_2k[11];
}
LX_PE_SHP_RE_SQM1_DETAIL_T;



typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm___val;	     ///< ui value
	UINT32 shp_ui_sqm_2k[29];		 ///< *new shp_ui_sqm_vsd[30];
}
LX_PE_SHP_SR2K_SQM1_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8  shp_sqm____val;	     ///< ui value
	UINT32 shp_sqm_cmn_2k[11];		 ///< *new shp_sqm_cmn_vsd[19];
}
LX_PE_SHP_SR2K_SQM1_DETAIL_T;


typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_RE_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_RE_SQM_DETAIL_T;



typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_SR2K_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_SR2K_SQM_DETAIL_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_SR4K_SQM_CMN_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_SR4K_SQM_DETAIL_T;

#if 0
/**
 * common type - HAL_VPQ_SetSharpness
 */
	
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_RE_CMN_T;

/**
 * common type - HAL_VPQ_SetSharpness
 */
	
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_DE1_T;

typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_SR2K_RE_CMN_T;

/**
 * common type - HAL_VPQ_SetSharpness
 */
	
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 oper;			///< operation
	UINT32 size;			///< size of data
	union
	{
		UINT32 *data;
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_SHP_SR2K_DE_T;
#endif

/***************************************************************************/
/* ETC : misc. */
/***************************************************************************/
/**
 *	pe misc. table parameter type
 */
typedef struct
{
	UINT32 func_num;			///< func number(depending on chip version)
	UINT32 oper;				///< operation
	UINT32 size;				///< the number of data
	union
	{
		UINT32 *data;			///< lut data
		UINT32 compat_data;
		UINT64 sizer;
	};
}
LX_PE_ETC_TBL_T;

/***************************************************************************/
/* ETC : info. */
/***************************************************************************/
/**
 *	pe operation mode
 */
typedef struct
{
	UINT32 is_reverse   : 1;	///< 0, reverse mode, 1:yes,0:no(default)
	UINT32 is_oled      : 1;	///< 1, oled, 1:yes,0:no(default)
	UINT32 is_colmetry  : 3;    ///< 2:3, colorimetry, 0:601,1:709,2:2020
	UINT32 is_vr        : 1;    ///< 4, vr360 0 off, 1  on
	UINT32 is_420       : 1;    ///< 5, hdmi 420 1, else 0
	UINT32 is_orbit     : 1;    ///< 6,orbit 1, else 0
	UINT32 is_dsc       : 1;    ///< 7,dsc 1, else 0
	UINT32 hdr_type     : 3;    ///< 8:10, SDR:0, DOLBY:1, HDR10:2, HLG:3, TECHNICOLOR:4, HDREFFECT:5
}
LX_PE_INF_OP_MODE_T;

/**
 * pe window info.(offset, size)
 */
typedef struct
{
	UINT32 x_ofst;			///< x offset
	UINT32 y_ofst;			///< y offset
	UINT32 h_size;			///< horizontal size
	UINT32 v_size;			///< vertical size
}
LX_PE_INF_WIN_T;

/**
 *	pe display info.
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	LX_PE_INFO_TYPE info_type;		///< info type flag
	LX_PE_SRC_TYPE src_type;		///< pe source type,  			LX_PE_INFO_PIC_FORMAT
	LX_PE_FMT_TYPE fmt_type;		///< pe format type , 			LX_PE_INFO_PIC_FORMAT
	UINT32 in_h_size;				///< input horizontal active size, 	LX_PE_INFO_PIC_FORMAT
	UINT32 in_v_size;				///< input vertical active size, 		LX_PE_INFO_PIC_FORMAT
	LX_PE_FR_TYPE fr_type;			///< pe frame rate type, 			LX_PE_INFO_PIC_FORMAT
	UINT32 in_f_rate;				///< input frame rate(x10 hz),		LX_PE_INFO_PIC_FORMAT
	LX_PE_SCAN_TYPE scan_type;		///< pe scan type, 				LX_PE_INFO_PIC_FORMAT
	LX_PE_CSTD_TYPE cstd_type;		///< pe color standard type, 		LX_PE_INFO_PIC_FORMAT
	LX_PE_HDMI_TYPE hdmi_type;		///< pe hdmi type, 				LX_PE_INFO_DEFAULT
	LX_PE_SCART_TYPE scart_type;	///< pe scart type, 				LX_PE_INFO_DEFAULT
	LX_PE_DTV_TYPE dtv_type;		///< pe dtv play type, 			LX_PE_INFO_DEFAULT
	LX_PE_HDD_SRC_TYPE hdd_type;	///< hdd src type, 				LX_PE_INFO_DEFAULT
	LX_PE_INF_WIN_T in_win;			///< input window, 				LX_PE_INFO_IN_WIN
	LX_PE_INF_WIN_T out_win;		///< output window, 				LX_PE_INFO_OUT_WIN
	UINT32 act_fmt;					///< active format(see seamless mode), 			LX_PE_INFO_MISC
	UINT32 mul_win;					///< multi window mode, 0124:one,pip,mirror,quad, 	LX_PE_INFO_MISC
	UINT32 sub_mode;				///< see LX_DE_SUB_MODE_T, 				LX_PE_INFO_MISC
	LX_PE_INF_OP_MODE_T mode;		///< operation mode, 			LX_PE_INFO_MODE
	UINT32 zoder[2];				///< index : order(0->top, 1->bottom) , value : win_id,  see LX_DE_ZLIST_T
}
LX_PE_INF_DISPLAY_T;

/**
 *	pe level info.
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	LX_PE_LEVEL_TYPE sel;			///< pe level select. see LX_PE_LEVEL_TYPE
	UINT32 noise_level;				///< pe tnr noise level
	UINT32 peakpos_level;			///< pe tnr peak pos level
	UINT32 motion_level;			///< pe motion level
}
LX_PE_INF_LEVEL_T;

#ifdef PE_SUPPORT_EXT_INNER_PATTERN
#define LX_PE_MAX_EXT_PATTERN_GRADATION_LINE (4)		// it depends on chip limitation
#define LX_PE_MAX_EXT_PATTERN_WINBOX (10)				// it depends on chip limitation
#define MAX_EXT_PATTERN_GRADATION_H_STRIDE_SIZE (254)				// it depends on chip limitation
#define EXT_PATTERN_GRADATION_H_STRIDE_STEP (2)				// it depends on chip limitation
#define MAX_EXT_PATTERN_GRADATION_V_STRIDE_SIZE (127)				// it depends on chip limitation
#define EXT_PATTERN_GRADATION_V_STRIDE_STEP (1)				// it depends on chip limitation
#define EXT_PATTERN_WIDTH (3840)				// it depends on chip limitation
#define EXT_PATTERN_HEIGHT (2160)				// it depends on chip limitation

typedef enum {
	LX_PE_EXT_PATTERN_WINBOX,
	LX_PE_EXT_PATTERN_GRADATION,
} LX_PE_EXT_PATTERN_MODE_T;

typedef enum {
	LX_PE_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL,
	LX_PE_EXT_PATTERN_GRADATION_DIRECTION_VERTICAL,
	LX_PE_EXT_PATTERN_GRADATION_DIRECTION_MAX
} LX_PE_EXT_PATTERN_GRADATION_DIRECTION_T;

typedef struct {
	UINT32 lineIdx;		// gradation line index
	UINT32 start_R;		// 1st gradation block's red level as a 10bit resolution
	UINT32 start_G;		// 1st gradation block's green level as a 10bit resolution
	UINT32 start_B;		// 1st gradation block's blue level as a 10bit resolution
	UINT32 step_R;		// step size for next gradation block
	UINT32 step_G;		// step size for next gradation block
	UINT32 step_B;		// step size for next gradation block
	UINT32 strideSize;	// gradation block's width(horizontal mode)/height(vertical mode)
} LX_PE_EXT_PATTERN_GRADATION_LINE_ATTR_T;

typedef struct {
	UINT32 numGrad;	// number of gradation lines in a screen
	LX_PE_EXT_PATTERN_GRADATION_DIRECTION_T eGradMode;
	LX_PE_EXT_PATTERN_GRADATION_LINE_ATTR_T stLineAttr[LX_PE_MAX_EXT_PATTERN_GRADATION_LINE];
} LX_PE_EXT_PATTERN_GRADATION_INFO_T;

typedef struct {
	UINT32 winIdx;	// window layer index. 0:background(bottom layer), ... , 10?:top layer
	UINT32 x;
	UINT32 y;
	UINT32 w;
	UINT32 h;
	UINT32 fill_R;  // 10 bit resolution
	UINT32 fill_G;  // 10 bit resolution
	UINT32 fill_B;  // 10 bit resolution
} LX_PE_EXT_PATTERN_WINBOX_WINDOW_ATTR_T;


typedef struct {
	UINT32 u8NumWin;	// number of windows in a screen(including background window)
	LX_PE_EXT_PATTERN_WINBOX_WINDOW_ATTR_T stWinBoxAttr[LX_PE_MAX_EXT_PATTERN_WINBOX];
} LX_PE_EXT_PATTERN_WINBOX_INFO_T;

typedef struct {
	LX_PE_WIN_ID win_id;
	UINT32 bOnOff;
	LX_PE_EXT_PATTERN_MODE_T eMode;
	LX_PE_EXT_PATTERN_GRADATION_INFO_T stGradInfo;
	LX_PE_EXT_PATTERN_WINBOX_INFO_T stWinboxInfo;
} LX_PE_CMG_EXT_PATTERN_INFO_T;
#endif /* PE_SUPPORT_EXT_INNER_PATTERN */

/**
*  tag information to firmware. for webos4.0 O18
*/
typedef struct {
	UINT32 base;
	UINT32 size;
} LX_PE_IPC_SYSTEM_MEM_T;

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_KAPI_H_ */

