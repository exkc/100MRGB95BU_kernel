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


/** @file be_kapi.h
 *
 *	@author	    won.hur (won.hur@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.25
 *	@see
 */

#ifndef	_BE_KAPI_H_
#define	_BE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
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

#define	BE_IOC_MAGIC		'D'

/* histo bin num [00]~[31]:bin00~bin31 */
#define	BE_FW_HST_BIN	32

#define LX_BE_PQ_NUM_OF_PCC_COEF 9
#define LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA 4

#define PQDB_PHDR_MCC_EN_LENGTH  1
#define PQDB_PHDR_MCC_WB2P_GAIN_LENGTH 3
#define PQDB_PHDR_MCC_WB2P_OFFSET_LENGTH 3
#define PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH 8
#define PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH 8

/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/* common */
#define BE_IOW_UPDATE_FIRMWARE     	_IOW(BE_IOC_MAGIC, 0, BE_FW_DWLD_T)

#define BE_IOW_TOP_SET_BYPASS			_IOW(BE_IOC_MAGIC, 1, LX_BE_BLOCK_BYPASS_T)
#define BE_IOW_TOP_TOGGLE_3D_LR			_IOW(BE_IOC_MAGIC, 2, LX_BE_3D_LR_T)
#define BE_IOW_TOP_SET_3D_CONVERGENCE	_IOW(BE_IOC_MAGIC, 3, LX_BE_3D_CONVERGENCE_T)
#define BE_IOW_TOP_SET_BLACK_BAR		_IOW(BE_IOC_MAGIC, 4, LX_BE_BLACK_BAR_T)
#define BE_IOW_TOP_SET_DEBUG_DISPLAY	_IOW(BE_IOC_MAGIC, 5, LX_BE_DEBUG_DISPLAY_T)
#define BE_IOW_SET_REAL_CINEMA			_IOW(BE_IOC_MAGIC, 6, LX_BE_REAL_CINEMA_T)
#define BE_IOW_SET_ORBIT				_IOW(BE_IOC_MAGIC, 7, LX_BE_ORBIT_T)
#define BE_IOW_SET_LSR					_IOW(BE_IOC_MAGIC, 8, BOOLEAN)
#define BE_IOW_SET_LSR_PARAM			_IOW(BE_IOC_MAGIC, 9, LX_BE_LSR_T)
#define BE_IOW_SET_GSR					_IOW(BE_IOC_MAGIC, 10, LX_BE_GSR_T)
#define BE_IOW_GET_GSR_STATUS			_IOR(BE_IOC_MAGIC, 11, BOOLEAN)
#define BE_IOW_SET_CPC					_IOW(BE_IOC_MAGIC, 12, UINT32)
#define BE_IOR_GET_OSD_ALPHA_APL		_IOWR(BE_IOC_MAGIC, 13, LX_BE_LUT_T)
#define BE_IOW_SET_OSD_RGB_LEVEL		_IOW(BE_IOC_MAGIC, 14, LX_BE_OSD_RGB_LEVEL_T)
#define BE_IOW_SET_DISP_MODE			_IOW(BE_IOC_MAGIC, 15, LX_BE_DISP_MODE_T)
#define BE_IOR_TOP_GET_IRR_STATUS		_IOR(BE_IOC_MAGIC, 16, LX_BE_IRR_STATUS_T)
#define BE_IOW_TOP_SET_IRR_DATA			_IOWR(BE_IOC_MAGIC, 17, LX_BE_LUT_T)
#define BE_IOR_TOP_GET_IRR_DATA			_IOR(BE_IOC_MAGIC, 18, LX_BE_IRR_READ_T)
#define BE_IORW_REG_ACCESS				_IOWR(BE_IOC_MAGIC, 19, BE_REG_RW_T)
#define BE_IOW_ENABLE_DEBUG_PRINT		_IOW(BE_IOC_MAGIC, 20, BE_DEBUG_PRINT_T )
#define BE_IOW_TEST_INPUT_LAG			_IOW(BE_IOC_MAGIC, 21, UINT32)
#define BE_IOW_INPUT_LAG_PATTERN		_IOW(BE_IOC_MAGIC, 22, LX_BE_INPUT_LAG_PATTERN_T)

#define BE_IOC_TOP_MAX	23

/* H3D */
#define BE_IOW_H3D_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX, LX_BE_H3D_MODE_T)
#define BE_IOW_H3D_GET_MODE				_IOR(BE_IOC_MAGIC, BE_IOC_TOP_MAX+1, LX_BE_H3D_MODE_T)
#define BE_IOW_H3D_T3C_DEPTH_LEVEL		_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+2, LX_BE_H3D_T3C_DEPTH_LEVEL_T)
#define BE_IOW_H3D_A3C_DEPTH_LEVEL		_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+3, LX_BE_H3D_A3C_DEPTH_LEVEL_T)
#define BE_IOW_H3D_A3C_AUTOCONVERGENCE	_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+4, LX_BE_H3D_A3C_AUTOCONVERGENCE_T)
#define BE_IOW_H3D_SET_TRIDFMT                   _IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+5, LX_BE_TRIDTV_FMT_CTRL_T)

#define BE_IOC_H3D_MAX					(BE_IOC_TOP_MAX + 6)

/* FRC */
#define BE_IOW_FRC_CONTROL_MEMC        		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX, LX_BE_FRC_MEMC_MODE_T)
//#define BE_IOW_FRC_SET_TRUEMOTION_DEMO 	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+1, BOOLEAN)	//�����Ǵ� ���ΰ�? Ȯ�� �ʿ�. ���� L9���� �����°���.
#define BE_IOW_FRC_SET_DEMO_MODE		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+1, LX_BE_FRC_DEMO_MODE_T)
#define BE_IOW_FRC_SET_DEBUG_BOX			_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+2, LX_BE_FRC_ENABLE_DEBUG_BOX_T)
#define BE_IOW_FRC_SET_BYPASS_MEMC_REG	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+3, LX_BE_FRC_MEMC_BYPASS_REGION_T)
#define BE_IOW_FRC_SET_YUV_444_MODE		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+4, LX_BE_FRC_COLOR_YUV444_T)
#define BE_IOW_FRC_SET_LOW_DELAY			_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+5, LX_BE_FRC_LOW_DELAY_T)
#define BE_IOW_FRC_SET_MOTION_PRO		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+6, LX_BE_FRC_MOTION_PRO_T)
#define BE_IOR_FRC_GET_FIRMWARE_VER		_IOR(BE_IOC_MAGIC, BE_IOC_H3D_MAX+7, LX_BE_FRC_VERSION_T)
#define BE_IOW_FRC_FORCE_FRAME_RATE		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+8, LX_BE_FRC_FRAME_RATE_T)
#define BE_IOW_FRC_SET_FREEZE				_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+9, LX_BE_FRC_FREEZE_T)
#define BE_IOR_FRC_UPDATE_FRAME_DELAY		_IOR(BE_IOC_MAGIC, BE_IOC_H3D_MAX+10, LX_BE_LOW_DELAY_T)
#define BE_IOW_FRC_SET_CONFIG			_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+11, LX_BE_FRC_CFG_T)
#define BE_IOW_FRC_RUN_COMMAND			_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+12, LX_BE_FRC_CMD_T)

#define BE_IOC_FRC_MAX					(BE_IOC_H3D_MAX + 13)

/* LED */
#define BE_IOR_LED_GET_VERSION				_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX, LX_BE_LED_VERSION_T)
#define BE_IOW_LED_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+1, LX_BE_LED_MODE_T)
#define BE_IOW_LED_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+2, LX_BE_LED_CONTROL_T)
#define BE_IOW_LED_GET_APL				_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+3, LX_BE_LED_APL_T)
#define BE_IOW_LED_SET_CLIPPING_VALUE	_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+4, UINT32)
#define BE_IOW_LED_UPDATE_SENSOR_LUX_INFO	_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+5, UINT32)
#define BE_IOW_LED_GET_REG_INFO			_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+6, LX_BE_LED_REG_INFO_T)
#define BE_IOW_LED_SET_UCR				_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+7, LX_BE_LED_REG_INFO_T)

#define BE_IOR_WCG_CALC_FW_LUT_SIZE		_IOWR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+8, LX_BE_WCG_CALC_FW_LUT_SIZE_T)
#define BE_IOR_WCG_GET_FW_LUT			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+9, LX_BE_WCG_FW_LUT_T)
#define BE_IOR_WCG_GET_VERSION			_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+10, LX_BE_WCG_VERSION_T)
#define BE_IOW_WCG_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+11, LX_BE_WCG_MODE_T)
#define BE_IOW_WCG_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+12, LX_BE_WCG_CONTROL_T)

#define BE_IOW_PQ_SET_DPG				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+13, LX_BE_PQ_DPG_T)
#define BE_IOW_PQ_SET_PCC				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+14, LX_BE_PQ_PCC_T)
#define BE_IOW_PQ_SET_GAMMA				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+15, BOOLEAN)
#define BE_IOW_PQ_SET_DEGAMMA			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+16, BOOLEAN)
#define BE_IOW_PQ_SET_PCC_GAMMA			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+17, LX_BE_PQ_PCC_GAMMA_T)
#define BE_IOW_PQ_SET_PCC_MUX_BLEND		_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+18, LX_BE_PQ_PCC_MUX_BLEND_T)
#define BE_IOW_PQ_SET_LUMINENCE_BOOST	_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+19, LX_BE_PQ_LUT_T)

#define BE_IOC_LED_MAX					(BE_IOC_FRC_MAX + 20)

/* PWM */
#define BE_IOW_PWM_SET_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX, BE_PWM_CTRL_T)
#define BE_IOW_PWM_SET_ADAPT_FREQ_CONTROL	_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+1, BE_PWM_ADAPT_FREQ_DB_T)
#define BE_IOW_PWM_SET_FREQUENCY			_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+2, BE_PWM_FREQ_T)
#define BE_IOW_PWM_SET_DUTY_CYCLE			_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+3, BE_PWM_DUTY_T)
#define BE_IOW_PWM_SET_DUTY_RATIO			_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+4, BE_PWM_DUTY_RATIO_T)
#define BE_IOW_PWM_SET_PARAMS				_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+5, LX_BE_PWM_PARAMS_T)
#define BE_IOR_PWM_GET_EXTERNAL_PWM			_IOR(BE_IOC_MAGIC, BE_IOC_LED_MAX+6, BE_EXTERNAL_PWM_T)

#define BE_IOC_PWM_MAX						(BE_IOC_LED_MAX + 7)

#define BE_IOW_STATUS_KEEPER_DBG			_IOW(BE_IOC_MAGIC, BE_IOC_PWM_MAX, BE_SKEEPER_DBG_T)

#define BE_IOC_STATUS_KEEPER_MAX			(BE_IOC_PWM_MAX + 1)

#define BE_IOC_MAXNR						BE_IOC_STATUS_KEEPER_MAX
/* OIF */
/*
#define BE_IOW_OIF_SET_VESA_JEIDA	_IOW(BE_IOC_MAGIC, 190, BOOLEAN)
#define BE_IOW_OIF_SET_BIT_DEPTH
#define BE_IOW_OIF_SET_SELECT_OUTCH
#define BE_IOW_OIF_SET_LVDS_OUTPUT
#define BE_IOW_OIF_SET_LVDS_POWER
#define BE_IOW_OIF_SET_DARK_SCREEN
#define BE_IOW_OIF_SET_LVDS_OUT_CTRL
#define BE_IOW_OIF_SET_LVDS_PORT_SWAP
*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define LX_BE_PWM_PORT_MAX	3

#define LX_BE_SET_DEFAULT_PARAM(structure,name)  \
	structure name;\
	do{\
		memset(&name, 0xFF, sizeof(structure));\
	}while(0);

/*----------------------------------------------------------------------------------------
    Type Definitions (Common)
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32	dbgMask;	// bit 0 : PRINT, bit 1 : ERROR, bit 2 : DEBUG, bit 3: TRACE
	UINT32	funcSupportDbgLevel; // 0 : error, 1 : warning, 2 : ignore
} BE_DEBUG_PRINT_T;

typedef struct
{
	UINT32 u32SizeNum __aligned(8);
	union {
		UINT32 *pu32Data;			// [IN] : pointer, [OUT] : data
		UINT32	compat_pu32Data;
		UINT64	sizer;
	};
} LX_BE_LUT_T;

typedef enum {
	BE_FRC_MC_TYPE_OFF,
	BE_FRC_MC_TYPE_LOW,
	BE_FRC_MC_TYPE_MID,
	BE_FRC_MC_TYPE_HIGH,
	BE_FRC_MC_TYPE_USER,
	BE_FRC_MC_TYPE_55_PULLDOWN
} BE_FRC_MC_TYPE_T;

typedef enum {
	LX_BE_FRC_MEMC_OFF,LX_BE_FRC_MEMC_DISABLE = 0,	/* FW MEMC value (0:off, 1:low, 2:medium,  3:high, 4:user, 5: 55pull down)*/
	LX_BE_FRC_MEMC_LOW,
	LX_BE_FRC_MEMC_MIDIUM,
	LX_BE_FRC_MEMC_HIGH,
	LX_BE_FRC_MEMC_USER,
	LX_BE_FRC_MEMC_PULLDOWN,

	LX_BE_FRC_MEMC_ENABLE = 10,							/* DISABLE MEMC (0:off) BNABLE (Call Recently stored MEMC value) */
	LX_BE_FRC_OPEN,
	LX_BE_FRC_CLOSED,
	LX_BE_FRC_MEMC_MAX
} LX_BE_FRC_CONT_T; //130531 kyungryun.lee

typedef enum {
	BE_REG_RW_TYPE_NONE = 0,
	BE_REG_RW_TYPE_DPPB_TOP,
	BE_REG_RW_TYPE_DPPB_TXM,
	BE_REG_RW_TYPE_DPPB_LED,
	BE_REG_RW_TYPE_FRC_LRX,
	BE_REG_RW_TYPE_FRC_P3D,
	BE_REG_RW_TYPE_FRC_DVI,

	BE_REG_RW_TYPE_MAXNUM
} BE_REG_RW_TYPE_T;

typedef struct
{
	BOOLEAN	isRead;
	BE_REG_RW_TYPE_T type;
	UINT32	addr;
	UINT32	data;
} BE_REG_RW_T;

typedef enum {
	BE_FW_DWLD_TYPE_FRC = 0,
	BE_FW_DWLD_TYPE_WCG,
	BE_FW_DWLD_TYPE_LED,
	BE_FW_DWLD_TYPE_HDR,
	BE_FW_DWLD_TYPE_MAXNUM,

	BE_FW_DWLD_TYPE_ALL = BE_FW_DWLD_TYPE_MAXNUM
} BE_FW_DWLD_TYPE_T;

typedef struct {
	UINT32	size __aligned(8);	// 0 : header or file download
	union {
		CHAR	*pData;	// NULL : header or file download
		UINT32	compat_pData;
		UINT64	sizer;
	};
	BE_FW_DWLD_TYPE_T	type __aligned(8);
} BE_FW_DWLD_T;

typedef enum {
	BE_PWM0 = 0, ///< pwm port0
	BE_PWM1,		///< pwm port1
	BE_PWM2,		///< pwm port2
	BE_PWM3,		///< pwm port3
	BE_PWM_MAX
} BE_PWM_ID_T;

typedef enum {
	BE_PWM_LOW	= 0,		///< PWM Output Signal Cotrol - Low
	BE_PWM_NORMAL,			///< PWM Output Signal Cotrol - Normal
	BE_PWM_HIGH,				///< PWM Output Signal Cotrol - High
	BE_PWM_INVERSION,		///< PWM Output Signal Cotrol - Inversion
} BE_PWM_OUT_CTRL_T;

typedef struct
{
	BE_PWM_ID_T			port;		///< PWM number: PWM0~2.
	BOOLEAN					enable;
	BOOLEAN					pwmMode;	///< freerun(0) / locking(1) mode
	BOOLEAN					lowPowerMode;
	BE_PWM_OUT_CTRL_T		pwmOutput;	///< PWM Output signal control
} BE_PWM_CTRL_T;

typedef struct
{
	UINT32			freq_48nHz;	///< PWM Output Frequency on 48xN Hz Vsync
	UINT32			freq_50nHz; ///< PWM Output Frequency on 50xN Hz Vsync
	UINT32			freq_60nHz; ///< PWM Output Frequency on 60xN Hz Vsync
} BE_PWM_ADAPT_FREQ_DB_T;

typedef struct
{
	BE_PWM_ID_T				port;	///< PWM number: PWM0~2.
	BOOLEAN						enable;
	BE_PWM_ADAPT_FREQ_DB_T	freqDb;	///< PWM Output Frequency DB
} BE_PWM_ADAPT_FREQ_CTRL_T;

typedef struct
{
	BE_PWM_ID_T			port;		///< PWM number: PWM0~2.
	UINT32					frequency;	///< PWM Output Frequency
} BE_PWM_FREQ_T;

typedef struct
{
	BE_PWM_ID_T	port;		///< PWM number: PWM0~2.
	UINT16			duty;		///< Set duty of PWM (0 ~ 255).
	UINT16			offset;		///< PWM Start Position (0 ~ 255).
} BE_PWM_DUTY_T;

typedef struct
{
	BE_PWM_ID_T			port;		///< PWM number: PWM0~2.
	UINT32				percent;	///< PWM duty ratio (0~100)
} BE_PWM_DUTY_RATIO_T;

typedef struct {
	UINT32	enable;			///< On off
	UINT32	type;			///< Pattern Type  0:Black, 1:White
	UINT32	hoffset;		///< horizontal pixel offset
	UINT32	voffset;		///< vertical line offset
	UINT32	hsize;			///< horizontal pixels
	UINT32	vsize;			///< vertical lines
} BE_INPUT_LAG_PATTERN_T;

typedef struct{
	BOOLEAN enable;
	BOOLEAN lockModeEn;
	BE_PWM_OUT_CTRL_T pwmOutput;
	BOOLEAN scanningModeEn;
	BOOLEAN lowPowerModeEn;
	BOOLEAN adaptFreqEn;
	UINT32 frequency;
	BE_PWM_ADAPT_FREQ_DB_T adaptFreqDb;
	UINT32 offset;
	UINT32 duty;
} LX_BE_PWM_PORT_PARAMS_T;

typedef struct{
	UINT32 portMask;
	LX_BE_PWM_PORT_PARAMS_T portParams[LX_BE_PWM_PORT_MAX];
} LX_BE_PWM_PARAMS_T;

/**
 * BE PWM parameter.
 * get PWM Duty value for external port(FRC) .
 *
*/
typedef struct
{
	UINT16			frequency;		///< current frequency (locking mode frequncy)
    	UINT16			duty;		    	///< current duty of PWM (0 ~ 255).
} BE_EXTERNAL_PWM_T;

typedef struct
{
	UINT16  	u16ConvergenceVal;
	UINT16 	u16ConvergenceEnable;	// 0 : Convergence auto disable,
									// 1 : Convergence auto enable with 3D depth info
} LX_BE_3D_CONVERGENCE_T;

typedef struct
{
	UINT16	bOutLR; 	// 0: Left/Top First, 1: Right/Bottom First
	UINT16  	reserved;
} LX_BE_3D_LR_T;

typedef struct
{
	UINT8 	u8BarOn;
	UINT8	u8BarVal;
	UINT8	u8BarStep;
	UINT8	reserved;
} LX_BE_BLACK_BAR_T;

typedef struct
{
	UINT32 	u32RealCinemaEnable;
} LX_BE_REAL_CINEMA_T;

typedef struct
{
	UINT32 	u32DelayMode;
} LX_BE_FRAME_DELAY_MODE_T;
//#if 0 //temp code
typedef struct
{
	unsigned short phdr_mcc_en[PQDB_PHDR_MCC_EN_LENGTH];
	unsigned short phdr_mcc_wb_gain[PQDB_PHDR_MCC_WB2P_GAIN_LENGTH];
	unsigned short phdr_mcc_wb_offset[PQDB_PHDR_MCC_WB2P_OFFSET_LENGTH];
} LX_BE_USER_MCC_DATA_T;

typedef struct
{
	unsigned short phdr_mcc_luma_lut_x[PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH];    ///<0x0000~0x03ff, 8 point x data
	unsigned short phdr_mcc_luma__lut_y[PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH]; ///<0x0000~0x03ff, 8 point y data
	unsigned short phdr_mcc_satu_lut_x[PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH]; ///0x0000~0x03ff, 8 point x data
	unsigned short phdr_mcc_satu_lut_y[PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH];  ///0x0000~0x03ff, 8 point y data
} LX_BE_USER_MCC_LUT_T;
//#endif
typedef struct
{
	unsigned short phdr_mcc_en[PQDB_PHDR_MCC_EN_LENGTH];
	unsigned short phdr_mcc_wb_gain[PQDB_PHDR_MCC_WB2P_GAIN_LENGTH];
	unsigned short phdr_mcc_wb_offset[PQDB_PHDR_MCC_WB2P_OFFSET_LENGTH];
} LX_BE_MCC_DATA_T;

typedef struct
{
	unsigned short phdr_mcc_luma_lut_x[PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH];    ///<0x0000~0x03ff, 8 point x data
	unsigned short phdr_mcc_luma__lut_y[PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH]; ///<0x0000~0x03ff, 8 point y data
	unsigned short phdr_mcc_satu_lut_x[PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH]; ///0x0000~0x03ff, 8 point x data
	unsigned short phdr_mcc_satu_lut_y[PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH];  ///0x0000~0x03ff, 8 point y data
} LX_BE_MCC_LUT_T;

typedef struct
{
	UINT32	bOnOff;
	UINT32	bAutoMode;			// 0 : Justscan mode, 1 : Just/Overscan mode
	UINT32 	bStoreMode;
	UINT32	bPartialFrameMode;
	UINT32	bOsdOverscan;	// for debug
} LX_BE_ORBIT_T;

typedef struct
{
	UINT32	u32LsrMode __aligned(8); 		// 0 : OFF, 1 : LO, 2 : HI
	LX_BE_LUT_T lsrTbl;
} LX_BE_LSR_T;

typedef struct
{
	LX_BE_LUT_T gsrTbl;
} LX_BE_GSR_T;

typedef struct
{
	BOOLEAN bOnOff __aligned(8);
	LX_BE_LUT_T levelTbl;
} LX_BE_OSD_RGB_LEVEL_T;

typedef struct
{
	BOOLEAN bIsIrrInitDone;
	BOOLEAN bIsIrrSuspended;
} LX_BE_IRR_STATUS_T;

typedef struct
{
	BOOLEAN bMemUpdateForRead __aligned(8);
	LX_BE_LUT_T irrData;
} LX_BE_IRR_READ_T;

typedef enum
{
	LX_BE_DISP_RESOLUTION_3840,
	LX_BE_DISP_RESOLUTION_7680,
	LX_BE_DISP_RESOLUTION_MAX
} LX_BE_DISP_RESOLUTION_T;

typedef enum
{
	LX_BE_DISP_FRAME_RATE_30,
	LX_BE_DISP_FRAME_RATE_60,
	LX_BE_DISP_FRAME_RATE_120,
	LX_BE_DISP_FRAME_RATE_VRR,
	LX_BE_DISP_FRAME_RATE_165,
	LX_BE_DISP_FRAME_RATE_MAX
} LX_BE_DISP_FRAME_RATE_T;

typedef struct
{
	LX_BE_DISP_RESOLUTION_T dispResolution;
	LX_BE_DISP_FRAME_RATE_T dispFrameRate;
} LX_BE_DISP_MODE_T;

typedef struct
{
	BOOLEAN bFbdevInitDone;
	BOOLEAN bOsdVReverseOn;
	BOOLEAN bEStreamerOn;
	BOOLEAN bOsdSharpnessWAOn;
	BOOLEAN b4kOSDResolution;
} LX_BE_FBDEV_STATUS_T;

typedef struct
{
	BOOLEAN bFwOsdOrbitInitDone;
	BOOLEAN bFwOsdSrInitDone;
	BOOLEAN bFwEstreamerOn;
} LX_BE_FW_OSD_STATUS_T;

typedef struct
{
	BOOLEAN		bH3DBypass;	//	0: H3D Normal, 1: H3D(2D-3D,Depth Block) Bypass
	BOOLEAN		bFRCBypass;		//	0: FRC Normal, 1: FRC Bypass
	BOOLEAN		bLEDBypass;		//	0: LED Normal, 1: LED Bypass
	BOOLEAN		bHDRBypass;	//	0: HDR Normal, 1: HDR Bypass
	BOOLEAN		bWCGBypass;	//	0: WCG Normal, 1: WCG Bypass
} LX_BE_BLOCK_BYPASS_T;

typedef struct
{
	UINT8	u8H3DDebugDisplay;
	UINT8	u8FRCDebugDisplay;
	UINT8	u8PEDebugDisplay;
	UINT8	u8LEDDebugDisplay;
} LX_BE_DEBUG_DISPLAY_T;

typedef struct
{
	UINT16	bInitA3C;
	UINT16	bInitT3C;
} BE_H3D_INIT_BLOCK_T;  // 0624 kim back to original lx naming to be naming

typedef struct
{
	UINT16	bA3CMode; // 0 : off, 1: on
	UINT16	bT3CMode; // 0 : off, 1: on
} LX_BE_H3D_MODE_T;

typedef struct
{
	UINT32	u32T3CDepthLevel;			// Depth level : 0 ~ 20

} LX_BE_H3D_T3C_DEPTH_LEVEL_T;

typedef struct
{
	UINT32	u32A3CDepthLevel;	// Depth level : 0 ~ 20
} LX_BE_H3D_A3C_DEPTH_LEVEL_T;

typedef struct
{
	UINT32	bA3CAutoConvergence; // 0 : Auto Convergence off, 1 : Auto Convergence on
} LX_BE_H3D_A3C_AUTOCONVERGENCE_T;

typedef enum
{
	LX_INPUT_LR_SEQ = 0,
	LX_INPUT_RL_SEQ,
	LX_INPUT_LR_MAX,
} LX_TRIDTV_INPUT_LR_SEQ_T;

typedef enum
{
	LX_TRIDTV_3DMODE_OFF = 0,
	LX_TRIDTV_3DMODE_ON,
	LX_TRIDTV_3DMODE_2DTO3D,
	LX_TRIDTV_3DMODE_3DTO2D,
	LX_TRIDTV_3DMODE_MAX,
} LX_TRIDTV_3DMODE_FLAG_T;

typedef enum
{
	LX_SC_OUT_SINGLE_2D = 0,
	LX_SC_OUT_SINGLE_TB,
	LX_SC_OUT_SINGLE_SS,
	LX_SC_OUT_SINGLE_FS,
	LX_SC_OUT_DUAL_FHD,
	LX_SC_OUT_DUAL_TB,
	LX_SC_OUT_DUAL_SS,
	LX_SC_OUT_SINGLE_T,
	LX_SC_OUT_SINGLE_LA,
	LX_SC_OUT_MAX,
} LX_TRIDTV_SC_OUTPUT_TYPE_T;

typedef struct{
	LX_TRIDTV_3DMODE_FLAG_T lx_mode;
	LX_TRIDTV_SC_OUTPUT_TYPE_T lx_in_fmt;
	LX_TRIDTV_INPUT_LR_SEQ_T	lx_lr;
	UINT8	depthCtrl;
	SINT8	convCtrl;
	BOOLEAN	bAutoConvMode;
} LX_BE_TRIDTV_FMT_CTRL_T;

typedef struct
{
    	UINT16	u16Version;
    	UINT16	u16Subversion;
} LX_BE_FRC_VERSION_T;

typedef struct
{
	UINT8	u8Blur;							// 0~9 : Blur level
    	UINT8	u8Judder;						// 0~9 : Judder level
    	UINT8	u8MemcType;					// 0 : OFF, 1: LOW, 2:MID, 3:HIGH, 4:USER, 5: PULLDOWN55 : @ref FRC_MC_TYPE_T
    	UINT8	_rsvd;							//reservved
} LX_BE_FRC_MEMC_MODE_T;

typedef struct
{
    	UINT32	u32Lowdelay;					// 0: NORMAL_DELAY, 1:LOW_DELAY
} LX_BE_FRC_LOW_DELAY_T;

typedef struct
{
    	UINT32	u32MotionPro;					// 0: NORMAL_MODE, 1:MOTION_PRO_MODE
} LX_BE_FRC_MOTION_PRO_T;


typedef struct
{
    	UINT16 	u16DemoMode;     				// 0: DEMO_OFF, 1:DEMO_ON
    	UINT16	u16DemoSide;					// 0: DEMO_SIDE_LEFT, 1:DEMO_SIDE_RIGHT
} LX_BE_FRC_DEMO_MODE_T;

typedef struct
{
    	UINT8	u8BypassRegion0;				// Region 0 Bypass 0 : Off, 1 : On
    	UINT8	u8BypassRegion1;				// Region 1 Bypass 0 : Off, 1 : On
    	UINT8	u8BypassRegion2;				// Region 2 Bypass 0 : Off, 1 : On
    	UINT8	u8BypassRegion3;				// Region 3 Bypass 0 : Off, 1 : On
} LX_BE_FRC_MEMC_BYPASS_ENABLE_T;

typedef struct
{
   	UINT16	u16MemcBypassX; 				// Memc Bypass region Start X position
    	UINT16	u16MemcBypassY;				// Memc Bypass region Start Y position
} LX_BE_FRC_MEMC_BYPASS_XY_T;

typedef struct
{
   	UINT16	u16MemcBypassW; 				// Memc Bypass region Width
    	UINT16	u16MemcBypassH;				// Memc Bypass region Height
} LX_BE_FRC_MEMC_BYPASS_WH_T;

typedef struct
{
	LX_BE_FRC_MEMC_BYPASS_ENABLE_T		u32BypassEn;	// Memc Bypass On/Off
	LX_BE_FRC_MEMC_BYPASS_XY_T			u32BypassXY;	// Memc Bypass region Start position X,Y
	LX_BE_FRC_MEMC_BYPASS_WH_T		u32BypassWH;	// Memc Bypass region Start position W,H
} LX_BE_FRC_MEMC_BYPASS_REGION_T;

typedef struct
{
    	UINT32	u32FrameRate; 					// 0 : FREE_RUN, 1: RATE_120HZ, 2: RATE_100HZ, 3: RATE_60HZ, 4: RATE_50HZ
} LX_BE_FRC_FRAME_RATE_T;

typedef struct
{
    	UINT32	u32Freeze;	 					// 0 : FREEZE OFF, 1: FREEZE
} LX_BE_FRC_FREEZE_T;

typedef struct
{
	UINT8 	u8ColorYuv;						// 0: YUV422, 1: YUV444
	UINT8	u8ColorDepth; 					// 0: 10bit, 1:8bit
	UINT8	u8CompMode;					// 0: Compression mode Off, 1:Compression mode On
	UINT8	_rsvd;							//reservved
} LX_BE_FRC_COLOR_YUV444_T;

typedef struct
{
	UINT16	u16FRCDebugBoxOn; 			// 0 : Debug Box Off, 1 : Debug Box On
	UINT16	u16FRCDebugBoxMode;			// FRC Debug Box mode
} LX_BE_FRC_ENABLE_DEBUG_BOX_T;

typedef enum
{
	LX_BE_FRC_CFG_TYPE_NONE = 0x00000000,		///< type none.
	LX_BE_FRC_CFG_TYPE_USE  = 0x00000001,		///< type use.
	LX_BE_FRC_CFG_TYPE_DFR  = 0x00000002,		///< type display frame rate
	LX_BE_FRC_CFG_TYPE_ALL  = 0x00000003		///< all
} LX_BE_FRC_CFG_TYPE;

/**
 *	be frc config
 */
typedef struct
{
	LX_BE_FRC_CFG_TYPE cfg_type;	///< cfg type
	UINT32 use_type;				///< use type, 0:internal, 1:external
	UINT32 dfr_type;				///< display fr type, 0:60hz diplay, 1:120hz diplay
} LX_BE_FRC_CFG_T;

/**
 *	be frc config
 */
typedef struct
{
	char str[256];					///< char
} LX_BE_FRC_CMD_T;

typedef struct
{
	UINT8	u8LEDLutVersion;
	UINT8	u8LEDSubVersion	;
	UINT8	u8PanelSize;
	UINT8	u8PanelType;
} LX_BE_LED_VERSION_T;

typedef struct
{
	UINT32	u32PictureMode;				// 0: Lowest, 1:Low, 2:Medium, 3:High, 4:HDR-Low, 5:HDR-Medium, 6:HDR-High
} LX_BE_LED_MODE_T;

typedef struct
{
	UINT32	u32DimminOn;				// 0 : OFF(smooth),	1 : ON(smooth), 2 : OFF(instant), 3 : ON(instant)
	UINT32	u32StoreMode;				// 0 : OFF,	1 : ON
	UINT32	u32BplOn;				// 0 : OFF,	1 : ON
} LX_BE_LED_CONTROL_T;

typedef struct
{
	UINT16	u16Min;
	UINT16	u16Max;
} LX_BE_LED_APL_T;

typedef struct
{
	BOOLEAN	bCtrl;
	UINT32	u32BitMask;
} LX_BE_LED_SPI_CTRL_T;

typedef struct
{
	BOOLEAN bIsGet;
	BOOLEAN bAiBrightnessAdjEn;
	UINT16 u16SensorLevel;
	UINT16 blooming_mode;
} LX_BE_LED_BPL_DATA_T;

typedef struct
{
	UINT32 AD_MEM_ADDR_CLR;
	UINT32 AD_MEM_DL_SBI_HCOEFF;
	UINT32 AD_MEM_DL_SBI_VCOEFF;
	UINT32 AD_FC_TAB1;
	UINT32 AD_FC_TAB5;
	UINT32 AD_UPPER_DC_LUT;
	UINT32 AD_LOWER_DC_LUT;
	UINT32 AD_MEM_DL_PIXEL_COMP_A;
	UINT32 AD_MEM_DL_PIXEL_COMP_B;
	UINT32 AD_MEM_DL_PIXEL_COMP_C;
	UINT32 AD_MEM_DL_PIXEL_COMP_D;
	UINT32 AD_UMASK_WR_COEFF;
} LX_BE_LED_REG_OFFSET;

typedef struct
{
	UINT32	u32CpuBaseAddr;
	UINT32	u32McuBaseAddr;
	LX_BE_LED_REG_OFFSET regOffset;
} LX_BE_LED_REG_INFO_T;

typedef enum {
	LX_BE_LED_UI_OFF = 0,
	LX_BE_LED_UI_LOW,
	LX_BE_LED_UI_MED,
	LX_BE_LED_UI_HI,
	LX_BE_LED_UI_HDR_LOW,
	LX_BE_LED_UI_HDR_MED,
	LX_BE_LED_UI_HDR_HI,
	LX_BE_LED_UI_HDR_PAT,
	LX_BE_LED_UI_MAX
} LX_BE_LED_UI_TYPE_T; 

typedef enum {
	LX_BE_LED_UI_V2_OFF = 0,
	LX_BE_LED_UI_V2_LOW,
	LX_BE_LED_UI_V2_MED,
	LX_BE_LED_UI_V2_HI,
	LX_BE_LED_UI_V2_HDR_LOW,
	LX_BE_LED_UI_V2_HDR_MED,
	LX_BE_LED_UI_V2_HDR_HI,
	LX_BE_LED_UI_V2_HDR_PAT,
	LX_BE_LED_UI_V2_RTINGS,
	LX_BE_LED_UI_V2_MAX
} LX_BE_LED_UI_TYPE_V2_T;

typedef enum {
	LX_BE_LED_UI_V3_OFF = 0,
	LX_BE_LED_UI_V3_LOW,
	LX_BE_LED_UI_V3_MED,
	LX_BE_LED_UI_V3_HI,
	LX_BE_LED_UI_V3_HDR_LOW,
	LX_BE_LED_UI_V3_HDR_MED,
	LX_BE_LED_UI_V3_HDR_HI,
	LX_BE_LED_UI_V3_HDR_PAT,
	LX_BE_LED_UI_V3_RTINGS,
	LX_BE_LED_UI_V3_MAX
} LX_BE_LED_UI_TYPE_V3_T;

typedef struct
{
	UINT32 u32Size __aligned(8);
	union {
		UINT32 *pu32Ptr;
		UINT32	compat_pu32Ptr;
		UINT64	sizer;
	};
} LX_BE_LED_LUT_INFO_T;

typedef struct
{
	LX_BE_LED_LUT_INFO_T sbiHCoef;
	LX_BE_LED_LUT_INFO_T sbiVCoef;
	LX_BE_LED_LUT_INFO_T lres1TabCoef;
	LX_BE_LED_LUT_INFO_T lres5TabCoef;
} LX_BE_LED_LIGHT_PROFILE_LUT_T;

typedef struct
{
	LX_BE_LED_LUT_INFO_T upperCurve[LX_BE_LED_UI_MAX];
	LX_BE_LED_LUT_INFO_T lowerCurve[LX_BE_LED_UI_MAX];
} LX_BE_LED_DIMMING_CURVE_LUT_T;

typedef struct
{
	UINT32 u32LutVersion __aligned(8);
	LX_BE_LED_LUT_INFO_T pq_common_lut;
	LX_BE_LED_LUT_INFO_T module_lut;
	LX_BE_LED_LUT_INFO_T unsharpMask_lut;
	LX_BE_LED_LIGHT_PROFILE_LUT_T lightProfile_lut;
	LX_BE_LED_DIMMING_CURVE_LUT_T dimmingCurve_lut;
	LX_BE_LED_LUT_INFO_T pqUi_lut[LX_BE_LED_UI_MAX];
	LX_BE_LED_LUT_INFO_T pixelCompensation_lut[LX_BE_LED_UI_MAX];
	LX_BE_LED_LUT_INFO_T sldBvGain;
	UINT32 u32PanelInch __aligned(8);
} LX_BE_LED_LUT_T;

typedef struct
{
	LX_BE_LED_LUT_INFO_T upperCurve[LX_BE_LED_UI_V2_MAX];
	LX_BE_LED_LUT_INFO_T lowerCurve[LX_BE_LED_UI_V2_MAX];
} LX_BE_LED_DIMMING_CURVE_LUT_V2_T;

typedef struct
{
	UINT32 u32LutVersion __aligned(8);
	LX_BE_LED_LUT_INFO_T pq_common_lut;
	LX_BE_LED_LUT_INFO_T module_lut;
	LX_BE_LED_LUT_INFO_T unsharpMask_lut;
	LX_BE_LED_LIGHT_PROFILE_LUT_T lightProfile_lut;
	LX_BE_LED_DIMMING_CURVE_LUT_V2_T dimmingCurve_lut;
	LX_BE_LED_LUT_INFO_T pqUi_lut[LX_BE_LED_UI_V2_MAX];
	LX_BE_LED_LUT_INFO_T pixelCompensation_lut[LX_BE_LED_UI_V2_MAX];
	LX_BE_LED_LUT_INFO_T sldBvGain;
	UINT32 u32PanelInch __aligned(8);
} LX_BE_LED_LUT_V2_T;

typedef struct
{
	LX_BE_LED_LUT_INFO_T upperCurve[LX_BE_LED_UI_V3_MAX];
	LX_BE_LED_LUT_INFO_T lowerCurve[LX_BE_LED_UI_V3_MAX];
} LX_BE_LED_DIMMING_CURVE_LUT_V3_T;

typedef struct
{
	UINT32 u32LutVersion __aligned(8);
	LX_BE_LED_LUT_INFO_T pq_common_lut;
	LX_BE_LED_LUT_INFO_T module_lut;
	LX_BE_LED_LUT_INFO_T unsharpMask_lut;
	LX_BE_LED_LIGHT_PROFILE_LUT_T lightProfile_lut;
	LX_BE_LED_DIMMING_CURVE_LUT_V2_T dimmingCurve_lut;
	LX_BE_LED_LUT_INFO_T pqUi_lut[LX_BE_LED_UI_V3_MAX];
	LX_BE_LED_LUT_INFO_T pixelCompensation_lut[LX_BE_LED_UI_V3_MAX];
	LX_BE_LED_LUT_INFO_T sldBvGain;
	UINT32 u32PanelInch __aligned(8);
} LX_BE_LED_LUT_V3_T;

typedef enum {
	LX_BE_LED_UI_ADJ_v80_off           = 0,
	LX_BE_LED_UI_ADJ_v80_sdr_low       = 1,
	LX_BE_LED_UI_ADJ_v80_sdr_medium    = 2,
	LX_BE_LED_UI_ADJ_v80_sdr_high      = 3,
	LX_BE_LED_UI_ADJ_v80_hdr_low       = 4,
	LX_BE_LED_UI_ADJ_v80_hdr_medium    = 5,
	LX_BE_LED_UI_ADJ_v80_hdr_high      = 6,
	LX_BE_LED_UI_ADJ_v80_hdr_pattern   = 7,
	LX_BE_LED_UI_ADJ_v80_rtings        = 8,
	LX_BE_LED_UI_ADJ_v80_sdr_filmmaker = 9,
	LX_BE_LED_UI_ADJ_v80_hdr_rtings    = 10,
	LX_BE_LED_UI_ADJ_v80_sdr_pattern   = 11,
	LX_BE_LED_UI_ADJ_v80_hdr_game      = 12,
	LX_BE_LED_UI_ADJ_v80_max
} LX_BE_LED_UI_ADJ_v80;

#define LED_DB_UI_ADJ_v80_MAX 13

typedef struct {
	unsigned int size;
	union {
		unsigned int *pData;
		unsigned int compat_pData;
		unsigned long long sizer;
	};
} LX_BE_LED_LUT_INFO_v80;

typedef struct
{
	LX_BE_LED_LUT_INFO_v80 sbiHCoef;
	LX_BE_LED_LUT_INFO_v80 sbiVCoef;
	LX_BE_LED_LUT_INFO_v80 lres1TabCoef;
	LX_BE_LED_LUT_INFO_v80 lres5TabCoef;
} LX_BE_LED_DB_LIGHT_PROFILE_LUT_v80_T;

typedef struct
{
	LX_BE_LED_LUT_INFO_v80 upperCurve[LED_DB_UI_ADJ_v80_MAX];
	LX_BE_LED_LUT_INFO_v80 lowerCurve[LED_DB_UI_ADJ_v80_MAX];
} LX_BE_LED_DB_DIMMING_CURVE_LUT_v80_T;

/* 20250731, https://harmony.lge.com:8443/issue/browse/SICREQ-1174 */
typedef struct {
	unsigned int u32LutVersion;
	LX_BE_LED_LUT_INFO_v80 pq_common_lut;
	LX_BE_LED_LUT_INFO_v80 module_lut;
	LX_BE_LED_DB_LIGHT_PROFILE_LUT_v80_T lightProfile_lut;
	LX_BE_LED_DB_DIMMING_CURVE_LUT_v80_T dimmingCurve_lut;
	LX_BE_LED_LUT_INFO_v80 pqUi_lut[LED_DB_UI_ADJ_v80_MAX];
	LX_BE_LED_LUT_INFO_v80 pixelCompensation_lut[LED_DB_UI_ADJ_v80_MAX];
	LX_BE_LED_LUT_INFO_v80 unsharpMask_lut[LED_DB_UI_ADJ_v80_MAX];
	LX_BE_LED_LUT_INFO_v80 contgain_lut[LED_DB_UI_ADJ_v80_MAX];
	LX_BE_LED_LUT_INFO_v80 blooming_lut[LED_DB_UI_ADJ_v80_MAX];
} LX_BE_LED_DB_LUT_v80_T;

//see enum v4l2_ext_vbe_object_detection_id
typedef enum {
	LX_BE_LED_OBJECT_DETECTION_ID_FACE = 0x01,
	LX_BE_LED_OBJECT_DETECTION_ID_DEPTH = 0x02,
	LX_BE_LED_OBJECT_DETECTION_ID_LIGHT = 0x04,
	LX_BE_LED_OBJECT_DETECTION_ID_LOGO = 0x08,
} LX_BE_LED_object_detection_id;

/* 20250819, https://harmony.lge.com:8443/issue/browse/SICREQ-1197 */
//see struct v4l2_ext_vbe_object_apl_gain
typedef struct {
	LX_BE_LED_object_detection_id id;
	unsigned char enable;
	unsigned char master_gain;
	unsigned char gain_x[4];
	unsigned char gain_y[4];
} LX_BE_LED_object_apl_gain;

//see struct v4l2_ext_vbe_object_apl
typedef struct {
	unsigned int detection_flag;// bitwise values of v4l2_ext_vbe_object_detection_id
	unsigned char apl[80][40];
} LX_BE_LED_object_apl;

typedef struct
{
	UINT32 u32Enable __aligned(8);
	UINT32	u32posNum __aligned(8);
	union {
		UINT16	*pu16posData;
		UINT32	compat_pu16posData;
		UINT64	sizer_posData;
	};
	UINT32	u32rgbTblNum __aligned(8);
	union {
		UINT16	*pu16rgbTblData;
		UINT32	compat_pu16rgbTblData;
		UINT64	sizer_rgbTblData;
	};
} LX_BE_LED_UCR_PARAM_T;

typedef struct
{
	UINT32	u32Size __aligned(8);
	union {
		UINT32	*pu32Data; // [0] : addr, [1] : val, [2] : addr, [3] : val, ...
		UINT32	compat_pu32Data;
		UINT64	sizer;
	};
} LX_BE_WCG_LUT_REG_T;

typedef struct
{
	UINT32	u32LutVersion __aligned(8);
	UINT32	u32TotalSectionNum __aligned(8);
	union {
		UINT16	*pu16SectionData;
		UINT32	compat_pu16SectionData;
		UINT64	sizer;
	};
	LX_BE_WCG_LUT_REG_T	regData __aligned(8);
} LX_BE_WCG_LUT_T;

typedef struct
{
	LX_BE_WCG_LUT_T	wcgLut;			// [IN]
	UINT32	fwWcgLutSize __aligned(8);			// [OUT]
} LX_BE_WCG_CALC_FW_LUT_SIZE_T;

typedef struct
{
	LX_BE_WCG_LUT_T	wcgLut;			// [IN]
	UINT32	fwWcgLutSize __aligned(8);			// [IN]
	union {
		CHAR	*fwWcgLutData;			// [IN] : pointer, [OUT] : data
		UINT32	compat_fwWcgLutData;
		UINT64	sizer;
	};
} LX_BE_WCG_FW_LUT_T;

typedef struct
{
	UINT32	u32WCGLutVersion;
} LX_BE_WCG_VERSION_T;

typedef struct
{
	UINT32	u32PictureMode;			// 0:BT709, 1:SMPTE, 2:EBU, 3:Color Extension, 4:BT2020
} LX_BE_WCG_MODE_T;

typedef struct
{
	UINT32	u32Enable;;
} LX_BE_WCG_CONTROL_T;

typedef struct
{
	UINT32 u32LutVersion __aligned(8);
	UINT32 sizeNum __aligned(8);
	union {
		UINT32 *pData;
		UINT32	compat_pData;
		UINT64	sizer;
	};
} LX_BE_PQ_LUT_T;

typedef struct
{
	LX_BE_PQ_LUT_T rDpgLut;
	LX_BE_PQ_LUT_T gDpgLut;
	LX_BE_PQ_LUT_T bDpgLut;
} LX_BE_PQ_DPG_T;

typedef struct
{
	BOOLEAN bIsGet;
	UINT16 matrix[LX_BE_PQ_NUM_OF_PCC_COEF];  // 3x3 matrix : 00/01/02/10/11/12/20/21/22
} LX_BE_PQ_PCC_T;

typedef struct
{
	BOOLEAN bIsGet;
	BOOLEAN bEotfGammaEn;
	BOOLEAN bOetfGammaEn;
} LX_BE_PQ_PCC_GAMMA_T;

typedef struct
{
	BOOLEAN bIsGet;
	UINT32 u32MuxL3dIn;
	UINT32 u32MuxBlendIn;
	UINT32 u32Mux4pLutIn;
	UINT32 u32MuxOetfOut;
	UINT32 au32B4pLutX[LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA];
	UINT32 au32B4pLutY[LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA];
} LX_BE_PQ_PCC_MUX_BLEND_T;

typedef struct
{
	BOOLEAN bIsGet;

	// 3x3 matrix : 00/01/02/10/11/12/20/21/22
	UINT16 matrix[LX_BE_PQ_NUM_OF_PCC_COEF];  

	// Gamma
	BOOLEAN bEotfGammaEn;
	BOOLEAN bOetfGammaEn;

	// MUX Blend
	UINT32 u32MuxL3dIn;
	UINT32 u32MuxBlendIn;
	UINT32 u32Mux4pLutIn;
	UINT32 u32MuxOetfOut;
	UINT32 au32B4pLutX[LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA];
	UINT32 au32B4pLutY[LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA];
} LX_BE_PQ_PCC_PARAMS_T;

typedef struct
{
	union {
		UINT16	*pu16Eotf;
		UINT32	compat_pu16Eotf;
		UINT64	sizer_Eotf;
	};
	UINT32	u32EotfNum __aligned(8);

	union {
		UINT16	*pu16Oetf;
		UINT32	compat_pu16Oetf;
		UINT64	sizer_Oetf;
	};
	UINT32	u32OetfNum __aligned(8);
} LX_BE_PQ_EOTF_OETF_T;
#if 0
typedef struct {
	unsigned char genlock_PortInit; // GPIO16/GENLOCK_I, GPIO17/GENLOCK_O for Genlock setting
									 // GPIO8 (select Genlock signal A, B) GPO type, Default Value = High
	unsigned char genlock_OnOff;	 // Genlock OnOff
	unsigned char genlock_PortSelect;	 // Select source ( enum PQ_GENLOCK_PORT )
	unsigned char genlock_Status;	  // (Read Only) ( enum PQ_GENLOCK_STATUS )
	unsigned int  genlock_Status_Phase; // (Read Only) Genlock - Current = Diff Phase (0~360)
	unsigned int  phaseShift;	   // for Pixel Delay
}
LX_BE_GENLOCK_T;
#endif
typedef struct {
unsigned int genlock;    // [BIT 0] Genlock 0 = Off, 1 = On
                         // [BIT 1~12] Phase Shift  (0x0 ~ 0xFFF)
}LX_BE_SET_GENLOCK_T;
// when Genlock:Off, Phase Shift: 0         -> Off
// when Genlock:Off, Phase shift: 1~0xfff    -> On
// when Genlock:On,  Phase shift: 0            -> On
// when Genlock:On,  Phase shift: 1~0xfff    -> On

/* GENLOCK get */
typedef struct {
unsigned int genlock_status;
// [BIT 0~3] : PQ_GENLOCK_SYNC_STATUS
// [BIT 4~7] : PQ_GENLOCK_FRAMERATE
// [BIT 8~19]: genlock_Status_Phase (0~4095) (4095 = 1 Frame diff, 2047 = 0.5 Frame)
}LX_BE_GET_GENLOCK_T;
#if 0
typedef enum
{
  V4L2_EXT_VBE_GENLOCK_OFF,
  V4L2_EXT_VBE_GENLOCK_NO_SYNC,    // No Signal
  V4L2_EXT_VBE_GENLOCK_ON_SYNC,    // On Signal
  V4L2_EXT_VBE_GENLOCK_LOCK_DONE,  // Lock is done
  V4L2_EXT_VBE_GENLOCK_FREERUN,
  V4L2_EXT_VBE_GENLOCK_STATUS_RESERVED_1,
  V4L2_EXT_VBE_GENLOCK_STATUS_RESERVED_2,
  V4L2_EXT_VBE_GENLOCK_STATUS_MAX
} V4L2_EXT_VBE_GENLOCK_SYNC_STATUS;

typedef enum
{
  V4L2_EXT_VBE_GENLOCK_24,
  V4L2_EXT_VBE_GENLOCK_25,
  V4L2_EXT_VBE_GENLOCK_30,
  V4L2_EXT_VBE_GENLOCK_50,
  V4L2_EXT_VBE_GENLOCK_60,
  V4L2_EXT_VBE_GENLOCK_100,
  V4L2_EXT_VBE_GENLOCK_120,
  V4L2_EXT_VBE_GENLOCK_UNKNOWN,
  V4L2_EXT_VBE_GENLOCK_FRAMERATE_MAX
} V4L2_EXT_VBE_GENLOCK_FRAMERATE;
#endif
/**
 * de get low delay info
 */
typedef struct {
	UINT32	wId_enable : 4;  // 3:0;	send wId to F/W ans get No_Delay enable status from F/W
	UINT32	lock   : 4;  // 7:4;
	UINT32	time   : 14; // 21:8;
	UINT32	frame  : 10; // 31:22;
	UINT32	locked_time;
}
LX_BE_LOW_DELAY_T;

typedef struct {
	UINT32	enable;			///< On off
	UINT32	type;			///< Pattern Type  0:Black, 1:White
	UINT32	hoffset;		///< horizontal pixel offset
	UINT32	voffset;		///< vertical line offset
	UINT32	hsize;			///< horizontal pixels
	UINT32	vsize;			///< vertical lines
}
LX_BE_INPUT_LAG_PATTERN_T;

typedef enum
{
	BE_SKEEPER_DBG_CMD_INIT = 0,
	BE_SKEEPER_DBG_CMD_UNINIT,
	BE_SKEEPER_DBG_CMD_INIT_HISTORY,
	BE_SKEEPER_DBG_CMD_UNINIT_HISTORY,
	BE_SKEEPER_DBG_CMD_CHECK_STATUS,
	BE_SKEEPER_DBG_CMD_PRINT_MODULE_LIST,
	BE_SKEEPER_DBG_CMD_PRINT_STATUSINDEX,
	BE_SKEEPER_DBG_CMD_PRINTLOG,
	BE_SKEEPER_DBG_CMD_CHANGE_HISTORY_TIME_UNIT,
	BE_SKEEPER_DBG_CMD_CHANGE_HISTORY_LOG_STATUS,
	BE_SKEEPER_DBG_CMD_CHANGE_MODULE_STATUS,
	BE_SKEEPER_DBG_CMD_ENABLE_DBG_PRINT,
	BE_SKEEPER_DBG_CMD_MAXNUM
} BE_SKEEPER_DBG_CMD_TYPE_T;

typedef struct
{
	UINT32	cmd_type	:8,		// Cmd type
			module_type	:8,		// Module Type
			history_type :8,		// History Type
			etcData		:8;		// data field
} BE_SKEEPER_DBG_T;

typedef enum
{
	BE_SKEEPER_FRC_MEMC_MODE = 0,
	BE_SKEEPER_FRC_LOW_DELAY_MODE,
	BE_SKEEPER_FRC_RGB_YUV_MODE,
	BE_SKEEPER_FRC_FREEZE,
	BE_SKEEPER_H3D_3D_MODE,
	BE_SKEEPER_H3D_AUTO_CONVERGENCE,
	BE_SKEEPER_H3D_2D_TO_3D_DEPTH,
	BE_SKEEPER_H3D_3D_DEPTH,
	BE_SKEEPER_H3D_CONVERGENCE,
	BE_SKEEPER_H3D_LR_TOGGLE,
	BE_SKEEPER_STATUS_MAXNUM
} BE_SKEEPER_STATUS_TYPE_T;

typedef struct
{
	union {
		UINT32 udata32;
		struct {
		UINT32 enable    :1; //(00:00)
		UINT32 rsvd0     :31;//(31:01)
		};
	} d0;
	UINT32 rsvd[3];
} LX_BE_IPC_PCCE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _BE_KAPI_H_ */

/** @} */

