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


/** @file ovi_kapi.h
 *
 *  	application interface header for ovi device
 *
 *	@author	    	dj911.kim
 *	@version		1.0
 *	@note
 *	@date		2012.09.09
 *	@see
 */

#ifndef	_OVI_KAPI_H_
#define	_OVI_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include "base_types.h"

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

#define	LX_OVI_IOC_MAGIC		'o'

/**
@name OVI IOCTL List
ioctl list for ovi device.

@{

@def LX_OVI_IOW_SET_LVDS
Set LVDS parameter

*/

#define LX_OVI_MAX_NUM_OF_MODE_INDEX_CHAR	50

/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define LX_OVI_IOW_SET_DISPLAY_OPTION			_IOW(LX_OVI_IOC_MAGIC, 0, LX_OVI_DISPLAY_INFO_T)
#define LX_OVI_IOW_SET_BYPASS					_IOW(LX_OVI_IOC_MAGIC, 1, LX_OVI_TCON_BYPASS_T)
#define LX_OVI_IOW_SET_COMBINATION				_IOW(LX_OVI_IOC_MAGIC, 2, UINT32)
#define LX_OVI_IOW_SET_SPREAD_SPECTRUM			_IOW(LX_OVI_IOC_MAGIC, 3, LX_OVI_SPREAD_SPECTRUM_T)
#define LX_OVI_IOW_SET_MCU_COMMAND				_IOW(LX_OVI_IOC_MAGIC, 4, LX_OVI_TCON_MCU_CMD_T)
#define LX_OVI_IOW_UPDATE_FIRMWARE				_IOW(LX_OVI_IOC_MAGIC, 5, LX_OVI_TCON_FW_DWLD_T)
#define LX_OVI_IOW_GET_FIRMWARE_VERSION			_IOW(LX_OVI_IOC_MAGIC, 6, LX_OVI_TCON_FW_VER_T)
#define LX_OVI_IOW_SET_FRAMEODC_ENABLE			_IOW(LX_OVI_IOC_MAGIC, 7, BOOLEAN)
#define LX_OVI_IOW_SET_COLORTEMP_ENABLE			_IOW(LX_OVI_IOC_MAGIC, 8, BOOLEAN)
#define LX_OVI_IOW_SET_GAMMA_ENABLE				_IOW(LX_OVI_IOC_MAGIC, 9, BOOLEAN)
#define LX_OVI_IOW_SET_DITHER_ENABLE				_IOW(LX_OVI_IOC_MAGIC, 10, BOOLEAN)
#define LX_OVI_IOW_SET_LINEODC_MODE				_IOW(LX_OVI_IOC_MAGIC, 11, LX_OVI_TCON_LINEOD_MODE_T)
#define LX_OVI_IOW_SET_OD_LUT						_IOW(LX_OVI_IOC_MAGIC, 12, LX_OVI_TCON_OD_DWLD_T)
#define LX_OVI_IOW_SET_DITHER_MODE				_IOW(LX_OVI_IOC_MAGIC, 13, LX_OVI_TCON_DITHER_T)
#define LX_OVI_IOW_SET_COLOR_TEMP				_IOW(LX_OVI_IOC_MAGIC, 14, LX_OVI_TCON_COLOR_TEMP_T)
#define LX_OVI_IOW_SET_GAMMA						_IOW(LX_OVI_IOC_MAGIC, 15, LX_OVI_TCON_GAMMA_T)
#define LX_OVI_IOW_SET_GAMMA_RGBW					_IOW(LX_OVI_IOC_MAGIC, 16, LX_OVI_TCON_GAMMA_RGBW_T)
#define LX_OVI_IORW_GET_TCON_OD_LUT				_IOWR(LX_OVI_IOC_MAGIC, 17, LX_OVI_TCON_OD_DWLD_T)
#define LX_OVI_IOW_SET_MLE_MODE					_IOW(LX_OVI_IOC_MAGIC, 18, LX_OVI_TCON_MLE_MODE_T)
#define LX_OVI_IOW_SET_TSCIC					_IOW(LX_OVI_IOC_MAGIC, 19, LX_OVI_TCON_TSCIC_T)
#define LX_OVI_IOW_SET_TCON_REVERSE				_IOW(LX_OVI_IOC_MAGIC, 20, BOOLEAN)
#define LX_OVI_IOW_SET_LVDS_REVERSE				_IOW(LX_OVI_IOC_MAGIC, 21, BOOLEAN)
#define LX_OVI_IOW_SET_LVDS_BLACK					_IOW(LX_OVI_IOC_MAGIC, 22, BOOLEAN)
#define LX_OVI_IOW_SET_TCON_TPG					_IOW(LX_OVI_IOC_MAGIC, 23, LX_OVI_TCON_TPG_MODE_T)
#define LX_OVI_IOW_SET_CHANNEL_POWER			_IOW(LX_OVI_IOC_MAGIC, 24, BOOLEAN)
#define LX_OVI_IOW_SET_LVDS_FORMAT				_IOW(LX_OVI_IOC_MAGIC, 25, LX_OVI_LVDS_OUT_STD_T)
#define LX_OVI_IOW_SET_LVDS_BIT					_IOW(LX_OVI_IOC_MAGIC, 26, LX_OVI_BIT_DEPTH_T)
#define LX_OVI_IOW_SET_TCON_CLOCK				_IOW(LX_OVI_IOC_MAGIC, 27, BOOLEAN)
#define LX_OVI_IOW_SET_EPI_DATA_SCRAMBLE		_IOW(LX_OVI_IOC_MAGIC, 28, BOOLEAN)
#define LX_OVI_IOW_SET_ADVANCED_10BIT			_IOW(LX_OVI_IOC_MAGIC, 29, BOOLEAN)
#define LX_OVI_IOW_SET_VCOM_PAT_DATA			_IOW(LX_OVI_IOC_MAGIC, 30, LX_OVI_TCON_VCOM_PAT_DATA_T)
#define LX_OVI_IOW_SET_VCOM_PAT_CTRL			_IOW(LX_OVI_IOC_MAGIC, 31, LX_OVI_TCON_VCOM_PAT_CTRL_T)
#define LX_OVI_IOW_SET_DISP_OUTPUT_MODE			_IOW(LX_OVI_IOC_MAGIC, 32, LX_OVI_DISP_OUTPUT_MODE_T)
#define LX_OVI_IOW_DISPLAY_RESUME				_IOW(LX_OVI_IOC_MAGIC, 33, LX_OVI_DISPLAY_INFO_T)
#define LX_OVI_IOW_SET_PEMP_ITUNE 				_IOW(LX_OVI_IOC_MAGIC, 34, LX_OVI_DISP_PEMP_ITUNE_DATA_T)
#define LX_OVI_IOW_ENABLE_DEBUG_PRINT			_IOW(LX_OVI_IOC_MAGIC, 35, LX_OVI_DEBUG_PRINT_T)

#define LX_OVI_IOC_MAXNR	36

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define LX_OVI_TCON_GAMMA 		(1<<0)
#define LX_OVI_TCON_WB			(1<<1)
#define LX_OVI_TCON_LODC		(1<<2)
#define LX_OVI_TCON_ODC			(1<<3)
#define LX_OVI_TCON_LGD_RGBW	(1<<4)
#define LX_OVI_TCON_BOE_RGBW	(1<<5)

/*----------------------------------------------------------------------------------------
    Type Definitions (Common)
----------------------------------------------------------------------------------------*/

typedef enum
{
	LX_OVI_8BIT,					///< 8bit depth
	LX_OVI_10BIT,					///< 10bit depth
	LX_OVI_BIT_MAX
} LX_OVI_BIT_DEPTH_T;

typedef enum
{
	LX_OVI_LVDS_OUT_JEIDA,				///< JEIDA LVDS
	LX_OVI_LVDS_OUT_VESA,					///< VESA LVDS
	LX_OVI_LVDS_OUT_MAX
} LX_OVI_LVDS_OUT_STD_T;

typedef enum
{
	LX_OVI_OUTPUT_LANE_BANDWIDTH_DEFAULT,
	LX_OVI_OUTPUT_LANE_BANDWIDTH_1_5G,
	LX_OVI_OUTPUT_LANE_BANDWIDTH_2_1G,
	LX_OVI_OUTPUT_LANE_BANDWIDTH_3_0G,
	LX_OVI_OUTPUT_LANE_BANDWIDTH_MAX,
} LX_OVI_OUTPUT_LANE_BANDWIDTH_T;

typedef enum {
	LX_OVI_SPREAD_RATIO_1,	// 0.75%
	LX_OVI_SPREAD_RATIO_2,	// 1.00%
	LX_OVI_SPREAD_RATIO_3,	// 1.25%
	LX_OVI_SPREAD_RATIO_4,	// 1.50%
	LX_OVI_SPREAD_RATIO_DEFAULT = LX_OVI_SPREAD_RATIO_3
} LX_OVI_SPREAD_RATIO_T;

#define LX_OVI_SPREAD_SPECTRUM_DEFAULT_PERIOD	70

typedef enum {
	LX_OVI_TCON_FRAMEOD,
	LX_OVI_TCON_LINEOD,
	LX_OVI_TCON_LINEOD_PCID = LX_OVI_TCON_LINEOD,
	LX_OVI_TCON_LINEOD_POD,
	LX_OVI_TCON_OD_BW_DEBUG_ON, // for debug only
	LX_OVI_TCON_OD_BW_DEBUG_OFF // for debug only
} LX_OVI_TCON_OD_MODE_T;

typedef enum {
	LX_OVI_TCON_LODC_V1_0,
	LX_OVI_TCON_LODC_V2_0
} LX_OVI_TCON_LODC_VERSION_T;

typedef enum {
	LX_OVI_TCON_LODC_LEFT_REF,
	LX_OVI_TCON_LODC_RIGHT_REF
} LX_OVI_TCON_LODC_ODDLINE_REF_T;

typedef enum {
	LX_OVI_TCON_LODC_NORMAL_REF,
	LX_OVI_TCON_LODC_REV_REF
} LX_OVI_TCON_LODC_LASTSUBPIX_REF_T;

typedef enum {
	LX_OVI_TCON_DITHER_TRUNC,
	LX_OVI_TCON_DITHER_ROUND,
	LX_OVI_TCON_DITHER_RANDOM
} LX_OVI_TCON_DITHER_T;

typedef enum {
	LX_OVI_TCON_TPG_OFF,
	LX_OVI_TCON_TPG_BLACK,
	LX_OVI_TCON_TPG_WHITE,
	LX_OVI_TCON_TPG_HVBAR,
	LX_OVI_TCON_TPG_HOR16GREY,
	LX_OVI_TCON_TPG_HOR64GREY,
	LX_OVI_TCON_TPG_HOR256GREY,
	LX_OVI_TCON_TPG_HOR1024GREY,
	LX_OVI_TCON_TPG_VER16GREY
} LX_OVI_TCON_TPG_MODE_T;

typedef struct
{
	BOOLEAN bUseInternalSync;
	LX_OVI_TCON_TPG_MODE_T eMode;
} LX_OVI_TCON_PATTERN_GEN_T;

typedef enum {	
	LX_OVI_TCON_HIGH_LUM1_MSE_ON,
	LX_OVI_TCON_HIGH_LUM2,
	LX_OVI_TCON_LOW_POWER1,
	LX_OVI_TCON_MLE_MODE_OFF,
	LX_OVI_TCON_HIGH_LUM1_MSE_OFF,
	LX_OVI_TCON_LOW_POWER2,
	LX_OVI_TCON_LOW_POWER2_SC_OFF,
	LX_OVI_TCON_BOE_CINEMA,
	LX_OVI_TCON_BOE_VIVID,
	LX_OVI_TCON_BOE_UTUBE0,
	LX_OVI_TCON_BOE_UTUBE1,
	LX_OVI_TCON_MLE_MODE_MAX
} LX_OVI_TCON_MLE_MODE_T;

typedef struct
{
	UINT32 version;
} LX_OVI_CONFIG_VER_T;

typedef struct
{
	BOOLEAN 				bEnable;
	LX_OVI_SPREAD_RATIO_T 	eSpreadRatio;
	UINT16 					u16Period;		// default value : LX_OVI_SPREAD_SPECTRUM_DEFAULT_PERIOD
} LX_OVI_SPREAD_SPECTRUM_T;

typedef enum {
	LX_OVI_TCON_FW_LGD = 0,
	LX_OVI_TCON_FW_BOE,
	LX_OVI_TCON_FW_TYPE_MAXNUM,
} LX_OVI_TCON_FW_TYPE_T;

typedef struct 
{
	UINT32	sizeNum __aligned(8);
	union
	{
		void	*pData;
		UINT32	compat_pData;
		UINT64	sizer;
	};
	LX_OVI_TCON_FW_TYPE_T	type __aligned(8);
	BOOLEAN read __aligned(8);
} LX_OVI_TCON_FW_DWLD_T;

typedef struct 
{
	LX_OVI_TCON_FW_TYPE_T	type;
	UINT32	cmd;
} LX_OVI_TCON_MCU_CMD_T;

typedef struct {
	UINT8 b0;
	UINT8 b1;
	UINT8 b2;
} LX_OVI_TCON_BOE_FW_VER_T;

typedef struct 
{
	LX_OVI_TCON_FW_TYPE_T	type __aligned(8);
	union
	{
		void *ver;
		UINT32 compat_ver;
		UINT64 sizer;
	};
} LX_OVI_TCON_FW_VER_T;

typedef struct
{
	UINT32 sizeNum __aligned(8);
	union
	{
		UINT32 *pData;
		UINT32 compat_pData;
		UINT64 sizer;
	};
} LX_OVI_TCON_GAMMA_LUT_T;

typedef struct
{
	UINT32 sizeNum __aligned(8);
	union
	{
		UINT8 *pData;
		UINT32 compat_pData;
		UINT64 sizer;
	};
} LX_OVI_TCON_OD_LUT_T;

typedef struct
{
	BOOLEAN bIsGet;
	LX_OVI_TCON_OD_LUT_T odLut;
	LX_OVI_TCON_OD_MODE_T eMode __aligned(8);
} LX_OVI_TCON_OD_DWLD_T;

typedef struct
{
	BOOLEAN bEnable;
	LX_OVI_TCON_LODC_VERSION_T eVersion;
	LX_OVI_TCON_LODC_ODDLINE_REF_T eRefPrevLine;
	LX_OVI_TCON_LODC_LASTSUBPIX_REF_T eRefLastSubPix;
} LX_OVI_TCON_LINEOD_MODE_T;

typedef struct
{
	BOOLEAN bIsGet;
	UINT32 r_gain;			// red gain	0~255 (192= 1.0gain) // bit[31] : 0 -> setting range 0.5~0.16, 1 -> setting range 0~0.16
	UINT32 g_gain;			// green gain	0~255 (192= 1.0gain) // bit[31] : 0 -> setting range 0.5~0.16, 1 -> setting range 0~0.16
	UINT32 b_gain;			// blue gain	0~255 (192= 1.0gain) // bit[31] : 0 -> setting range 0.5~0.16, 1 -> setting range 0~0.16
	UINT32 r_offset;			// red offset	0~255 (128= zero offset)
	UINT32 g_offset;			// green offset	0~255 (128= zero offset)
	UINT32 b_offset;			// blue offset	0~255 (128= zero offset)
} LX_OVI_TCON_COLOR_TEMP_T;

typedef enum
{
	LX_OVI_WIN_0 = 0,				///< window 0
	LX_OVI_WIN_1,					///< window 1
	LX_OVI_WIN_2,					///< window 2
	LX_OVI_WIN_3,					///< window 3
	LX_OVI_WIN_3_MAX

//	LX_OVI_WIN_ALL,					///< all window
//	LX_OVI_WIN_NUM = LX_PE_WIN_ALL,	///< number of windows
}LX_OVI_WIN_ID_T;

typedef struct
{
	LX_OVI_WIN_ID_T win_id;
	BOOLEAN pcc_eotf_en;
	BOOLEAN pcc_oetf_en;
	BOOLEAN reg_pcc_en;
	BOOLEAN reg_l3d_en;
} LX_OVI_MULTIWIN_GAMUT_T;

typedef struct
{
	BOOLEAN bIsGet;
	LX_OVI_TCON_GAMMA_LUT_T rGammaLut;
	LX_OVI_TCON_GAMMA_LUT_T gGammaLut;
	LX_OVI_TCON_GAMMA_LUT_T bGammaLut;
} LX_OVI_TCON_GAMMA_T;

typedef struct
{
	LX_OVI_TCON_GAMMA_LUT_T rGammaLut;
	LX_OVI_TCON_GAMMA_LUT_T gGammaLut;
	LX_OVI_TCON_GAMMA_LUT_T bGammaLut;
	LX_OVI_TCON_GAMMA_LUT_T wGammaLut;
} LX_OVI_TCON_GAMMA_RGBW_T;

typedef struct
{
	unsigned int addr;
	unsigned int value;
} LX_OVI_REG_T;

typedef struct
{
	char index[LX_OVI_MAX_NUM_OF_MODE_INDEX_CHAR];
	LX_OVI_REG_T* regs __aligned(8);
	UINT32 count __aligned(8);
} LX_OVI_OUTPUT_MODE_T;

typedef enum {
	LX_OVI_PANEL_LVDS,
	LX_OVI_PANEL_EPI,
	LX_OVI_PANEL_EPI_QSAC,
	LX_OVI_PANEL_VX1,
	LX_OVI_PANEL_CEDS,
	LX_OVI_PANEL_INTERFACE_MAX
} LX_OVI_PANEL_INTERFACE_T;

typedef enum {
	LX_OVI_PANEL_RESOLUTION_1024X768 = 0,
	LX_OVI_PANEL_RESOLUTION_1280X720,
	LX_OVI_PANEL_RESOLUTION_1366X768,
	LX_OVI_PANEL_RESOLUTION_1920X1080,
	LX_OVI_PANEL_RESOLUTION_2560X1080,
	LX_OVI_PANEL_RESOLUTION_3840X2160,
	LX_OVI_PANEL_RESOLUTION_5120X2160,
	LX_OVI_PANEL_RESOLUTION_7680X4320,
	LX_OVI_PANEL_RESOLUTION_MAX
} LX_OVI_PANEL_RESOLUTION_T;

typedef enum {
	LX_OVI_FRC_CHIP_NONE,
	LX_OVI_FRC_CHIP_INTERNAL,
	LX_OVI_FRC_CHIP_UD_BE_URSA9,
	LX_OVI_FRC_CHIP_UD_BE_URSA9P,
	LX_OVI_FRC_CHIP_UD_BE_URSA11,
	LX_OVI_FRC_CHIP_UD_BE_URSA11P,
	LX_OVI_FRC_CHIP_UD_BE_F16,
	LX_OVI_FRC_CHIP_8K_BE_URSA17,
	LX_OVI_FRC_CHIP_UD_BE_F20,
	LX_OVI_FRC_CHIP_UD_BE_F22,
	LX_OVI_FRC_CHIP_UD_BE_KLD,
	LX_OVI_FRC_CHIP_TYPE_MAX
} LX_OVI_FRC_CHIP_TYPE_T;

typedef enum {
	LX_OVI_PANEL_CELL_RGB,
	LX_OVI_PANEL_CELL_RGBW,
	LX_OVI_PANEL_CELL_TYPE_MAX
} LX_OVI_PANEL_CELL_TYPE_T;

typedef enum {
	LX_OVI_PANEL_V16,
	LX_OVI_PANEL_V17,
	LX_OVI_PANEL_V18,
	LX_OVI_PANEL_MAX
} LX_OVI_PANEL_VERSION_T;

typedef enum {
	LX_OVI_PANEL_INCH_22,
	LX_OVI_PANEL_INCH_23,
	LX_OVI_PANEL_INCH_24,
	LX_OVI_PANEL_INCH_26,
	LX_OVI_PANEL_INCH_27,
	LX_OVI_PANEL_INCH_28,
	LX_OVI_PANEL_INCH_32,
	LX_OVI_PANEL_INCH_39,
	LX_OVI_PANEL_INCH_40,
	LX_OVI_PANEL_INCH_42,
	LX_OVI_PANEL_INCH_43,
	LX_OVI_PANEL_INCH_47,
	LX_OVI_PANEL_INCH_48,
	LX_OVI_PANEL_INCH_49,
	LX_OVI_PANEL_INCH_50,
	LX_OVI_PANEL_INCH_55,
	LX_OVI_PANEL_INCH_58,
	LX_OVI_PANEL_INCH_60,
	LX_OVI_PANEL_INCH_65,
	LX_OVI_PANEL_INCH_70,
	LX_OVI_PANEL_INCH_75,
	LX_OVI_PANEL_INCH_77,
	LX_OVI_PANEL_INCH_79,
	LX_OVI_PANEL_INCH_84,
	LX_OVI_PANEL_INCH_86,
	LX_OVI_PANEL_INCH_98,
	LX_OVI_PANEL_INCH_105,
	LX_OVI_PANEL_INCH_MAX
} LX_OVI_PANEL_INCH_T;

typedef enum {
	LX_OVI_PANEL_BACKLIGHT_EDGE_LED,
	LX_OVI_PANEL_BACKLIGHT_ALEF_LED,
	LX_OVI_PANEL_BACKLIGHT_DIRECT_M,
	LX_OVI_PANEL_BACKLIGHT_DIRECT_L,
	LX_OVI_PANEL_BACKLIGHT_OLED,
	LX_OVI_PANEL_BACKLIGHT_DIRECT_VI,
	LX_OVI_PANEL_BACKLIGHT_DIRECT_SKY,
	LX_OVI_PANEL_BACKLIGHT_NONE,// STB
	LX_OVI_PANEL_BACKLIGHT_MAX
} LX_OVI_PANEL_BACKLIGHT_T;

typedef enum {
	LX_OVI_PANEL_MAKER_LGD,
	LX_OVI_PANEL_MAKER_AUO,
	LX_OVI_PANEL_MAKER_SHARP,
	LX_OVI_PANEL_MAKER_BOE,
	LX_OVI_PANEL_MAKER_CSOT,
	LX_OVI_PANEL_MAKER_INNOLUX,
	LX_OVI_PANEL_MAKER_LGD_M,
	LX_OVI_PANEL_MAKER_ODM_B,
	LX_OVI_PANEL_MAKER_BOE_TPV,
	LX_OVI_PANEL_MAKER_HKC,
	LX_OVI_PANEL_MAKER_LGD_CA,
	LX_OVI_PANEL_MAKER_MAX
} LX_OVI_PANEL_MAKER_T;

typedef enum {
	LX_OVI_PANEL_LED_BAR_6,
	LX_OVI_PANEL_LED_BAR_8,
	LX_OVI_PANEL_LED_BAR_10,
	LX_OVI_PANEL_LED_BAR_12,
	LX_OVI_PANEL_LED_BAR_15,
	LX_OVI_PANEL_LED_BAR_16,
	LX_OVI_PANEL_LED_BAR_20,
	LX_OVI_PANEL_LED_BAR_24,
	LX_OVI_PANEL_LED_BAR_36,
	LX_OVI_PANEL_LED_BAR_40,
	LX_OVI_PANEL_LED_BAR_48,
	LX_OVI_PANEL_LED_BAR_50,
	LX_OVI_PANEL_LED_BAR_96,
	LX_OVI_PANEL_LED_BAR_240,
	LX_OVI_PANEL_LED_BAR_V8,
	LX_OVI_PANEL_LED_BAR_MAX
} LX_OVI_PANEL_LED_BAR_T;

typedef enum {
	LX_OVI_PANEL_FRAMERATE_60HZ,
	LX_OVI_PANEL_FRAMERATE_120HZ,
	LX_OVI_PANEL_FRAMERATE_60HZ_FIXED,
	LX_OVI_PANEL_FRAMERATE_144Hz,
	LX_OVI_PANEL_FRAMERATE_165Hz,
	LX_OVI_PANEL_FRAMERATE_MAX
} LX_OVI_PANEL_FRAMERATE_T;

typedef struct
{
	UINT32 videoWidth;
	UINT32 videoHeight;
	UINT32 osdWidth;
	UINT32 osdHeight;
} LX_OVI_DISPLAY_OUTPUT_RESOLUTION_T;

typedef union {
 	UINT32 all;
 	struct 
 	{
		UINT32
		SocOptionBIT0	:1,
		SocOptionBIT1	:1,
		SocOptionBIT2	:1,
		SocOptionBIT3	:1,
		SocOptionBIT4	:1,
		SocOptionBIT5	:1,
		SocOptionBIT6	:1,
		SocOptionBIT7	:1,
		SocOptionBIT8	:1,
		SocOptionBIT9	:1,
		SocOptionBIT10	:1,
		SocOptionBIT11	:1,
		SocOptionBIT12	:1,
		SocOptionBIT13	:1,
		SocOptionBIT14	:1,
		SocOptionBIT15	:1,
		SocOptionBIT16	:1,
		SocOptionBIT17	:1,
		SocOptionBIT18	:1,
		SocOptionBIT19	:1,
		SocOptionBIT20	:1,
		SocOptionBIT21	:1,
		SocOptionBIT22	:1,
		SocOptionBIT23	:1,
		SocOptionBIT24	:1,
		SocOptionBIT25	:1,
		SocOptionBIT26	:1,
		SocOptionBIT27	:1,
		SocOptionBIT28	:1,
		SocOptionBIT29	:1,
		SocOptionBIT30	:1,
		SocOptionBIT31	:1;
 	} flags;
} LX_OVI_USER_OPTION_T;

/* Do not add any entry. (The number of bits is fixed : 4 bits) */
typedef enum {
	LX_OVI_PANEL_FR_OPTION_NONE = 0,//no option
	LX_OVI_PANEL_FR_OPTION_01,//amled144, 4K,2K LGD(SCDCRID-3267)
	LX_OVI_PANEL_FR_OPTION_02,//amled144, 2K LGD(SCDCRID-3366)
	LX_OVI_PANEL_FR_OPTION_03,
	LX_OVI_PANEL_FR_OPTION_04,
	LX_OVI_PANEL_FR_OPTION_05,//pmled, 4K IDLED(SCDCRID-3459)
	LX_OVI_PANEL_FR_OPTION_06,
	LX_OVI_PANEL_FR_OPTION_07,
	LX_OVI_PANEL_FR_OPTION_08,
	LX_OVI_PANEL_FR_OPTION_09,
	LX_OVI_PANEL_FR_OPTION_10,
	LX_OVI_PANEL_FR_OPTION_11,
	LX_OVI_PANEL_FR_OPTION_12,
	LX_OVI_PANEL_FR_OPTION_13,
	LX_OVI_PANEL_FR_OPTION_14,
	LX_OVI_PANEL_FR_OPTION_15
} LX_OVI_PANEL_FR_OPTION_T;

typedef struct
{
	LX_OVI_PANEL_INTERFACE_T panelInterface; // From H/W option
	LX_OVI_PANEL_RESOLUTION_T panelResolution; // From H/W option
	LX_OVI_FRC_CHIP_TYPE_T frcChipType; // From H/W option
	LX_OVI_PANEL_CELL_TYPE_T panelCellType;
	LX_OVI_DISPLAY_OUTPUT_RESOLUTION_T dispOutResolution;
	LX_OVI_PANEL_VERSION_T panelVersion;
	LX_OVI_PANEL_INCH_T panelInch;
	LX_OVI_PANEL_MAKER_T panelMaker;
	LX_OVI_PANEL_BACKLIGHT_T panelBacklight; // [From Tool Option]!
	LX_OVI_PANEL_LED_BAR_T panelLedBar;
	LX_OVI_PANEL_FRAMERATE_T panelFramerate; // From H/W option
	LX_OVI_BIT_DEPTH_T lvdsBit;
	LX_OVI_LVDS_OUT_STD_T lvdsType;
	LX_OVI_OUTPUT_LANE_BANDWIDTH_T dispOutLaneBw;
	LX_OVI_USER_OPTION_T userSpecificOption;
} LX_OVI_DISPLAY_INFO_T;

typedef struct
{	// From H/W option
	LX_OVI_PANEL_INTERFACE_T panelInterface;
	LX_OVI_PANEL_RESOLUTION_T panelResolution; // for model option
	LX_OVI_PANEL_RESOLUTION_T dispResolution; // for ovi display option
	LX_OVI_FRC_CHIP_TYPE_T frcChipType;
	LX_OVI_PANEL_BACKLIGHT_T panelBacklight;
	LX_OVI_PANEL_FRAMERATE_T panelFramerate; // for model option
	LX_OVI_PANEL_FRAMERATE_T dispFramerate; // for ovi display option
	BOOLEAN isVx15Byte;
	BOOLEAN isDispForceFreerun;
	LX_OVI_PANEL_FR_OPTION_T panel_fr_option;// panel_frame_rate_option
	UINT32 year_option; // webos22/webos23
	UINT32 wirelessAV;
	UINT32 ovi_in_bit;
	UINT32 oled_boost_x4;
} LX_OVI_HW_DISPLAY_INFO_T;

typedef struct
{
	BOOLEAN bEnable;
	UINT32 u32BlockMask;  // masking bits (ex. LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_DITHER|LX_OVI_TCON_ODC)
} LX_OVI_TCON_BYPASS_T;

typedef struct {
	union
	{
		UINT8 *pu8ControlTbl;
		UINT32 compat_pu8ControlTbl;
		UINT64 sizer_pu8ControlTbl;
	};
	UINT32 u32Ctrlsize __aligned(8);
	union
	{
		UINT32 *pu32TscicTbl;
		UINT32 compat_pu32TscicTbl;
		UINT64 sizer_pu32TscicTbl;
	};
	UINT32 u32TscicSize __aligned(8);
} LX_OVI_TCON_TSCIC_T;

typedef struct {
	BOOLEAN bIsGet;
	BOOLEAN bEnable;
	union
	{
		UINT8 *pu8Config;
		UINT32 compat_pu8Config;
		UINT64 sizer_pu8Config;
	};
	UINT32 u32ConfigSize __aligned(8);
	union
	{
		UINT32 *pu8Data;
		UINT32 compat_pu8Data;
		UINT64 sizer_pu8Data;
	};
	UINT32 u32DataSize __aligned(8);
} LX_OVI_TCON_DEMURA_T;


typedef struct
{
	union
	{
		UINT16 *pu16vcomPattern;
		UINT32 compat_pu16vcomPattern;
		UINT64 sizer_pu16vcomPattern;
	};
	UINT32 sizeNum __aligned(8);
} LX_OVI_TCON_VCOM_PAT_DATA_T;

typedef enum{
	LX_OVI_TCON_VCOM_PAT_CTRL_OFF=0,  // Mandatory Implementation
	LX_OVI_TCON_VCOM_PAT_CTRL_ON,     // Mandatory Implementation
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1, // Optional Implementation, PGEN_VCOM1 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2, // Optional Implementation, PGEN_VCOM2 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3, // Optional Implementation, PGEN_VCOM3 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4, // Optional Implementation, PGEN_VCOM4 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5, // Optional Implementation, PGEN_VCOM5 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6, // Optional Implementation, PGEN_VCOM6 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7, // Optional Implementation, PGEN_VCOM7 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8, // Optional Implementation, PGEN_VCOM8 and CTRL_ON, for available SoC
	LX_OVI_TCON_VCOM_PAT_CTRL_MAX    // Limit to control.
} LX_OVI_TCON_VCOM_PAT_CTRL_T;

typedef enum{
	LX_OVI_DISP_OUTPUT_MODE_4K60 = 0,
	LX_OVI_DISP_OUTPUT_MODE_4K120,
	LX_OVI_DISP_OUTPUT_MODE_4KVRR,
	LX_OVI_DISP_OUTPUT_MODE_4K4K60LR,
	LX_OVI_DISP_OUTPUT_MODE_MAX
} LX_OVI_DISP_OUTPUT_MODE_T;

typedef struct {
	UINT32 frameRate;
	UINT32 hResolution;
	UINT32 vResolution;
} LX_OVI_TCON_OUTPUT_TIMING_T;

typedef struct {
	UINT32	funcSupportDbgLevel; // 0 : error, 1 : warning, 2 : ignore
} LX_OVI_DEBUG_PRINT_T;

typedef struct{
	BOOLEAN bIsGet;
	union
	{
		UINT8 *pPemp;
		UINT32 compat_pPemp;
		UINT64 sizer_pPemp;
	};
	union
	{
		UINT8 *pItune;
		UINT32 compat_pItune;
		UINT64 sizer_pItune;
	};
} LX_OVI_DISP_PEMP_ITUNE_DATA_T;

typedef struct
{
	BOOLEAN bIsGet;
	UINT32 enable __aligned(8);
	UINT32 path __aligned(8); // Signal Path 0 : PCLRC -> LOD, 1 : LOD -> PCLRC
	union {
		UINT8   *pData;
		UINT32	compat_pData;
		UINT64	sizer;
	};
	UINT32 sizeNum __aligned(8);
} LX_OVI_PCLRC_LUT_T;

enum ovi_clk_ctrl_type {
	OVI_CRG_CTRL_TYPE_SRC = 0,
	OVI_CRG_CTRL_TYPE_VRR,
	OVI_CRG_CTRL_TYPE_MAX
};

enum ovi_clk_ctrl_src {
	OVI_CRG_CTRL_SRC_NONE = 0,
	OVI_CRG_CTRL_SRC_VDEC,
	OVI_CRG_CTRL_SRC_HDMI,
	OVI_CRG_CTRL_SRC_ETC,
	OVI_CRG_CTRL_SRC_MAX
};

struct ovi_clk_ctrl {
	enum ovi_clk_ctrl_type type;
	enum ovi_clk_ctrl_src src;
	UINT32 vrr;
};

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _OVI_DRV_H_ */

/** @} */

