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


/** @file de_kapi.h
 *
 *	application interface header for de device
 *
 *	@author		dongho7.park (dongho7.park@lge.com)
 *	@version		0.6a
 *	@date		2009.12.30
 *
 *	@addtogroup lg1150_de
 *	@{
 */

#ifndef _DE_KAPI_H_
#define _DE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define _USE_VT_EXTENTION_
#define USE_V4L2_IOCTL

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#ifndef USE_XTENSA
#include "base_types.h"
#endif
#include "gps_dma.h"
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

//#include "rpu_ext_config.h"
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

#define DE_IOC_MAGIC		'a'
/**
@name DE IOCTL List
ioctl list for de device.

@{
@def DE_IOW_DE_INIT
Initialize de module.
device open and reset
set default register for clock, csc etc.
enable irq and set intr mask
load ucode

@def DE_IOR_GET_FIRMWARE_INFO
Reads de firmware information( version and update info).

@def DE_IOW_SET_BG_COLOR
set background color (non-active region color).
L8 support back_color y(8bit) cb(4bit) cr(4bit) at window compose block(OV)

@def DE_IOR_GET_OUT_FR_RATE
get display output frame rate (50 or 60).

@def DE_IOW_SET_WIN_BLANK
set window blank, to support mote control.
L8 support dark_color y(8bit) cb(4bit) cr(4bit) at window compose block(OV)

@def DE_IOR_GET_INPUT_WIN
get scaler input window size and position.
depend on source size and crop.

@def DE_IOR_GET_OUT_WIN
get scaler output window size and position.
depend on display size and picture mode.

@def DE_IOW_SET_INPUT_WIN
set scaler input window size and position.
depend on source size and crop.

@def DE_IOW_SET_OUT_WIN
set scaler output window size and position.
depend on display size and picture mode.

@def DE_IOW_SET_DIS_OUT
on/off de display output

@def DE_IOW_SET_DIS_FMT
set de display size and frame rate, etc.
depend on panel attribute.
display parameter setting (DE1A DISP_PARAM0~3)

@def DE_IOW_SET_FR_RATE
set display frame rate and mode(forced freerun or not).

@def DE_IOW_SET_IRE_PATTERN
set color and IRE levels of full pattern.
used for factory adjustment.

@def DE_IOW_MULTI_WIN_ENABLE
enable/disable multi window mode including split window mode.
used for auto demo mode on/off of 60Hz display(PDP).
also set picture quality parameters for enhanced side of window.

@def DE_IOW_SET_SPREAD
set LVDS spread spectrum for 60Hz mode (PDP).
for above 120Hz mode, FRC controls LVDS spread spectrum
also see the CTOP CTR54[31:0] control register of SSPLL

@def DE_IOW_SET_CVI_SRC_TYPE
set captured(external) video source attribute.
channel A or B, size, offset, color, scan type, aspect ratio).

@def DE_IOW_SET_CVI_CSC
send color space conversion matrix and offset for each external source information.
RGB to YCbYr.

@def DE_IOW_SET_POST_CSC
send color space conversion matrix for post processing block
YCbCr to RGB.

@def DE_IOR_GET_MVI_COLORIMETRY
get MVI source colorimetry information.

@def DE_IOW_SET_CVE
set de CVE parameter.
select CVE feedback path and timing parameters.

@def DE_IOW_SET_VCS
set de VCS parameter.
transfer information of VCS to MCU part via IPC

@def DE_IOR_GET_CAPTURE_WIN
get de captured video size and offset

@def DE_IOW_SET_CAPTURE_WIN
set de captured video size and offset

@def DE_IOW_SET_ECANVAS
set de ecanvas on/off and ecanvas source path

@def DE_IOW_FW_DOWNLOAD
downdload Firmware of DE

@def DE_IOW_SET_CVI_FIR
set FIR coefficient of captured video source.

@def DE_IOW_SET_CVI_TPG
set test pattern generator of captured video source.

@def DE_IOW_SET_CVI_CSAMPLE_MODE
set captured source color sub-sampling method.

@def DE_IOW_SET_CVI_SYNC_RESHAPE
reshape captured input sync timing for PC source.

@def DE_IOR_GET_CVI_INFO
get CVI frame rate for external inputs.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------
	Catogorize the IOCTL command as mentioned below in to reduce cyclomatic complexity based on switch-case
	1. system
	2. source
	3. window
	4. control
	5. Operation
	6. Misc

	Maximum IOCTL in any category should not be more then 20 [Yellow level for cyclomatic complexity]
	Order of Macros regarding ioctl categories and categories enum must be same like SYSTEM ioctl starts
	first so DE_SYSTEM_IOCTL is also first enum. This will help directly map ioctl to it's category type
----------------------------------------------------------------------------------------*/
//DM MetaData size
#define MAX_DM_MD_SIZE 512
//DM OTT MetaData size
#ifdef HDR_HW5_SUPPORT
#define MAX_DM_OTT_MD_SIZE 66626
#else
#define MAX_DM_OTT_MD_SIZE 3*1024
#endif
//Maximum number of windows supported for Dolby HDR IP
#define DOLBY_MAX_WIN 1
#define MAX_FRAMES	2

//Maximum IOCTL of any category
#define DE_IOC_MINNR	0
#define DE_MAX_IOCTL_IN_CATAGORY 20

//Let assume DE will have maximum 10 IOCTL categories of commands
#define MAX_IOCTL_CATEGORIES	10

//system IOCTL
#define DE_SYSTEM_IOCTL_BASE_NR	DE_IOC_MINNR
//Source related ioctl
#define DE_SRC_IOCTL_BASE_NR	(DE_SYSTEM_IOCTL_BASE_NR+DE_MAX_IOCTL_IN_CATAGORY)
//window composer ioctl
#define DE_WIN_IOCTL_BASE_NR	(DE_SRC_IOCTL_BASE_NR+DE_MAX_IOCTL_IN_CATAGORY)
//control related ioctl
#define DE_CNTL_IOCTL_BASE_NR	(DE_WIN_IOCTL_BASE_NR+DE_MAX_IOCTL_IN_CATAGORY)
//operation ioctl
#define DE_OP_IOCTL_BASE_NR		(DE_CNTL_IOCTL_BASE_NR+DE_MAX_IOCTL_IN_CATAGORY)
//miscellaneous ioctls
#define DE_MISC_IOCTL_BASE_NR	(DE_OP_IOCTL_BASE_NR+DE_MAX_IOCTL_IN_CATAGORY)
//Dolby HDR IP ioctls
#define DE_DHDR_IP_IOCTL_BASE_NR	(DE_MISC_IOCTL_BASE_NR+DE_MAX_IOCTL_IN_CATAGORY)

#define DE_DHDR_IP_SIMUATION 0
#define GMLUT_MAX_DIM 17
#define DEF_G2L_LUT_SIZE_2P 8
#define DEF_G2L_LUT_SIZE (1<<DEF_G2L_LUT_SIZE_2P)

typedef enum{
	DE_SYSTEM_IOCTL = 0,
	DE_SRC_IOCTL = 1,
	DE_WIN_IOCTL = 2,
	DE_CNTL_IOCTL = 3,
	DE_OP_IOCTL = 4,
	DE_MISC_IOCTL = 5,
	DE_DHDR_IP_IOCTL = 6,
} DE_IOCTL_TYPE_T;



// system (11) [system ioctl - 11]

#define DE_IOW_DE_INIT						_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR, LX_DE_PANEL_TYPE_T )
#define DE_IOR_GET_FIRMWARE_INFO			_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+1, LX_DE_FIRMWARE_INFO_T )
#define DE_IOW_FW_DOWNLOAD				_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+2, LX_DE_FW_DWLD_T)
#define DE_IOW_SET_IF_CONFIG				_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+3, LX_DE_IF_CONFIG_T)
#define DE_IOR_GET_CAPACITY				_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+4, LX_DE_CAPACITY_T)
#define DE_IOW_SET_OUTPUT_MODE			_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+5, LX_DE_OUTPUT_MODE_T)
#define DE_IOW_SET_DIS_FMT				_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+6, LX_DE_DIS_FMT_T)
#define DE_IOW_SET_FR_RATE				_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+7, LX_DE_FR_RATE_T)
#define DE_IOR_GET_OUT_FR_RATE			_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+8, LX_DE_FR_RATE_T)
#define DE_IOW_SET_DIS_OUT				_IOW(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+9, BOOLEAN)
#define DE_IOR_GET_SYS_STATUS				_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+10, LX_DE_SYS_STATUS_T)
#define DE_IOW_SET_HDMITX_INFO			_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+11, LX_DE_HDMITX_OUTPUT_INFO_T)
#define DE_IOR_GET_MEM_INFO				_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+12, LX_DE_MEM_SYS_INFO_T)
#define DE_IOR_GET_TIME_DIFF				_IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+13, UINT32)
#define DE_IOR_GET_VIDEO_DELAY_INT			   _IOR(DE_IOC_MAGIC, DE_SYSTEM_IOCTL_BASE_NR+14, LX_DE_CB_INFO_T)

// ======================================================================================
// source (8) [source ioctl - 8]

#define DE_IOW_SET_WIN_PORT_SRC			_IOW(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR, LX_DE_INPUT_SOURCE_T)
#define DE_IOW_SET_CVI_SRC_TYPE			_IOW(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+1, LX_DE_CVI_SRC_TYPE_T)
#define DE_IOW_SET_CVI_FIR					_IOW(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+2, LX_DE_CVI_FIR_T )
#define DE_IOW_SET_CVI_CSAMPLE_MODE		_IOW(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+3, LX_DE_CSAMPLE_MODE_T )
#define DE_IOR_GET_MVI_COLORIMETRY		_IOR(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+4, LX_DE_MVI_COLORIMETRY_T)
#define DE_IOW_SET_CVI_HDMIPORT			_IOW(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+5, LX_DE_HDMIPORT_T)
#define DE_IOR_GET_SRC_STATUS				_IOR(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+6, LX_DE_SRC_STATUS_T)
#define DE_IOW_SET_SRC_MIRROR				_IOW(DE_IOC_MAGIC, DE_SRC_IOCTL_BASE_NR+7, LX_DE_SRC_MIRROR_T)

// ======================================================================================
// window composer (5) [window ioctl - 13]

#define DE_IOR_GET_INPUT_WIN				_IOR(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR, LX_DE_WIN_DIMENSION_T)
#define DE_IOR_GET_OUT_WIN				_IOR(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+1, LX_DE_WIN_DIMENSION_T)
#define DE_IOW_SET_INPUT_WIN				_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+2, LX_DE_WIN_DIMENSION_T)
#define DE_IOW_SET_OUT_WIN				_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+3, LX_DE_WIN_DIMENSION_T)
#define DE_IOW_SET_ZLIST					_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+4, LX_DE_ZLIST_T)
#define DE_IOW_SET_MULTI_VISION			_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+5, LX_DE_RECT_T)
#define DE_IOW_SET_WIN_BLANK				_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+6, LX_DE_SET_WIN_BLANK_T)
#define DE_IOW_SET_BG_COLOR				_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+7, LX_DE_COLOR_T)
#define DE_IOW_SET_INNER_PATTERN			_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+8, LX_DE_INNER_PATTERN_T)
#define DE_IOW_SET_CVI_TPG					_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+9, LX_DE_CVI_TPG_T)
#define DE_IOW_SET_SUB_WIN				_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+10, LX_DE_SET_SUB_WIN_T)
#define DE_IOR_GET_OUT_WIN_CACHED		_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+11, LX_DE_WIN_DIMENSION_T)
#define DE_IOW_SET_SUB_MODE				_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+12, LX_DE_SUB_MODE_T)
#define DE_IOW_GET_SUB_MODE				_IOR(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+13, LX_DE_SUB_MODE_T)
#define DE_IOW_SET_SUB_SHAPE			_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+14, LX_DE_SUB_SHAPE_T)
#define DE_IOW_SET_SRC_SIZE 			_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+15, LX_DE_SOURCE_SIZE_WIN_T)
#define DE_IOR_GET_SRC_SIZE 			_IOR(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+16, LX_DE_SOURCE_SIZE_WIN_T)
#define DE_IOW_SET_WIN_INFO 			_IOW(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+17, LX_DE_WIN_INFO_T)
#define DE_IOR_GET_WIN_INFO 			_IOR(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+18, LX_DE_WIN_INFO_T)
#define DE_IOW_SET_ORBIT  				_IOR(DE_IOC_MAGIC, DE_WIN_IOCTL_BASE_NR+19, LX_DE_ORBIT_T)


// ======================================================================================
//Control IOCTLs [control ioctl - 5]

#define DE_IOW_SET_LOW_DELAY				_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR, UINT32)
#define DE_IOR_GET_LOW_DELAY				_IOR(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+1, LX_DE_LOW_DELAY_T)
#define DE_IOW_SET_FRAME_DELAY			_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+2, LX_DE_SET_DELAY_BUFFER_T)
// freeze
#define DE_IOW_SET_WIN_FREEZE				_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+3, LX_DE_WIN_FREEZE_T)
#define DE_IOW_SET_ACT_FMT_DETECT			_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+4, LX_DE_ACT_FORMAT_T)
#define DE_IOW_SET_ROTATE				_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+5, LX_DE_ROTATE_INFO_T)
#define DE_IOW_SET_PATTERN				_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+6, LX_DE_PATTERN_T)
#define DE_IOW_SET_LATENCY_MEASURE		_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+7, LX_DE_LATENCY_MEASURE_T)
#define DE_IOW_SET_SCAN_MODE		_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+8, LX_DE_SCAN_MODE_T)
#define DE_IOW_SET_PIXELTOPIXEL		_IOW(DE_IOC_MAGIC, DE_CNTL_IOCTL_BASE_NR+9, UINT32)

// ======================================================================================
// operation (10 +?) [Operation ioctl - 14]
#define DE_IOW_SET_3D_INOUT_CTRL  		_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR, LX_DE_3D_INOUT_CTRL_T)
#define DE_IOW_SET_UD_MODE				_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+1, BOOLEAN)
#define DE_IOW_MULTI_WIN_ENABLE			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+2, BOOLEAN)
#define DE_IOR_GET_SCALER_INFO			_IOR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+3, LX_DE_SCALER_INFO_T)
#define DE_IOW_SET_SIGNAGE_MODE			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+4, BOOLEAN)
#define DE_IOW_DUAL_MODE_ENABLE			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+5, BOOLEAN)

// MEM interface - VCR(CVE), VENC(DVR), GPU, CAPTURE
#define DE_IOW_SET_CVE						_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+6, LX_DE_CVE_PARAM_T)
#define DE_IOW_SET_DVR_FMT_CTRL			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+7, LX_DE_DVR_DISFMT_T)
#define DE_IOW_SET_VTM						_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+8, LX_DE_VTM_FRAME_INFO_T)
#define DE_IOR_GET_VTM						_IOR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+9, LX_DE_VTM_FRAME_INFO_T)
#define DE_IOW_SET_CAPTURE				_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+10, LX_DE_CAPTURE_CTRL_T)     // ioctl for legacy capture (will be removed.)
#define DE_IOW_GET_VTM_BUFFER			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+10, LX_DE_VTM_FRAME_INFO_T)
#define DE_IOW_GET_FPP_INFO				_IOWR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+11, UINT32)


// pixel grab - read/write from video frame before CVI csc parameter for self-diagnosis.
#define DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER	_IOWR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+11, LX_DE_CVI_RW_VIDEO_FRAME_T)

// gpsc dma
#define DE_IOW_GPSDMA_START				_IOWR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+12, LX_DE_GPSDMA_PARAM_T)

// VTG - read/write from video frame before CVI csc parameter for self-diagnosis.
#define DE_IOWR_SET_VTM_BLOCK_STATE		_IOWR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+12, LX_DE_VTM_BLOCK_STATE_T)
#define DE_IOW_SET_VCS						_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+13, LX_DE_VCS_IPC_T)
#define DE_IOW_SET_OPERATION				_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+14, LX_DE_OPERATION_CTRL_T)// IOCTL 96, 32, 16 sum
#define DE_IOW_SET_SUB_OPERATION			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+15, LX_DE_SUB_OPERATION_CTRL_T)			// IOCTL 10, 84 sum
#define DE_IOW_SET_DOLBY_HDR			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+16, LX_DE_DOLBYHDR_INFO_T)
#define DE_IOW_SET_GCP_MODE 			_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+16, LX_DE_GCP_INFO_T)
#define DE_IOR_GET_DOLBY_HDR_INT			_IOR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+17, UINT32)
#define DE_IOR_GET_GCP_INT			   _IOR(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+17, UINT32)

// M17(M16+) new feature
#define DE_IOW_SET_SRC_SYNC_LOW_DELAY		_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+18, UINT32)
#define DE_IOW_SET_HIGH_FRAME_RATE		_IOW(DE_IOC_MAGIC, DE_OP_IOCTL_BASE_NR+19, UINT32)

// ======================================================================================
// for DE debug (12) [miscellaneous ioctl - 10]
#define DE_IOR_REG_RD					_IOR(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR, UINT32)
#define DE_IOW_REG_WR					_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+1, LX_DE_REG_WR_T)
#define DE_IOR_GET_DBG					_IOR(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+2, LX_DE_SET_DBG_T)
#define DE_IOW_SET_DBG					_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+3, LX_DE_SET_DBG_T)
#define DE_IOW_SET_UART_FOR_MCU		_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+4, BOOLEAN)
// ioctl for h13 verification
#define DE_IOW_SET_EVAL_DBG				_IOWR(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+5, LX_DE_SET_EVAL_DBG_T)
// work-around
#define DE_IOW_SET_SCART_RGB_BYPASS_MODE	_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+6, int)
#define DE_IOW_SET_DEINTERLACE				_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+7, BOOLEAN)
// de freeze sub scaler frame in msc-r or subscaler path
#define DE_IOW_SET_SUB_SC_FREEZE		_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+8, BOOLEAN)
// de cvi video frame buffer freeze to read/write video frame before cvi csc parameter for self-diagnosis.
#define DE_IOW_SET_CVI_FREEZE			_IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+9, LX_DE_CVI_CAPTURE_FREEZE_T)
#define DE_IOW_IPC_SET_HDR_MODE  _IOW(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+10, LX_DE_HDR_IPC_MODE_T)
#define DE_IOWR_TEST_CMD          _IOWR(DE_IOC_MAGIC, DE_MISC_IOCTL_BASE_NR+11, LX_DE_TEST_CMD_T)

// ========================================================================================
//DE Dolby HDR ip ioctls
#define DE_DHDR_IP_IORW_INIT		_IOWR(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR,LX_DOLBY_IOCTL_INIT_T)
#define DE_DHDR_IP_IOR_HDMI_MD_READ	_IOR(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+1,LX_DOLBY_IOCTL_HDMI_MD_T)
#define DE_DHDR_IP_IOR_OTT_MD_READ	_IOR(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+2,LX_DOLBY_OTT_MD_IOCTL_T)
#define DE_DHDR_IP_IOW_CONFIG		_IOW(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+3,LX_DOLBY_IOCTL_CONFIG_REG_T)
#define DE_DHDR_IP_IOW_LUT_CONFIG	_IOW(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+4,LX_DOLBY_IOCTL_CONFIG_LUT_T)
#define DE_DHDR_IP_IOW_START		_IOW(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+5,UINT8)
#define DE_DHDR_IP_IORW_UNINIT		_IOWR(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+6,UINT8)
#define DE_DHDR_IP_IOW_MDREAD_UNBLOCK	_IOR(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+7,UINT8)
#define DE_DHDR_IP_IOW_GET_CONFIG	_IOW(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+8,LX_DOLBY_IOCTL_CONFIG_REG_T)
#define DE_DHDR_IP_IOW_SET_HDMI_MD_PATH	_IOW(DE_IOC_MAGIC,DE_DHDR_IP_IOCTL_BASE_NR+9,LX_DOLBY_IOCTL_MD_PATH_T)


#define DE_IOC_MAXNR				200

#define MAX_HISTORY_SIZE	DE_IOC_MAXNR

typedef enum E_IOCTL_CMD_HISTORY_ORDER
{
	E_HIST_LATEST = 0,
	E_HIST_OLDEST,
} _E_HISTORY_ORDER;

//To retrieve complete history
#define DE_HISTORY_IOCTL			_IOR(DE_IOC_MAGIC, DE_IOC_MAXNR+1, UINT32)

//Defining Macro to get IOCTL category
#define GET_IOCTL_CATEGORY(__CMD__)	(_IOC_NR(__CMD__)/DE_MAX_IOCTL_IN_CATAGORY)
#define GET_IOCTL_NR(__CMD__)	_IOC_NR(__CMD__)

/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * de display (panel) type, full HD or HD.
 */
typedef enum {
	LX_PANEL_TYPE_1920 = 0, ///< full HD@60Hz
	LX_PANEL_TYPE_1366,		///< WXGA(HD)
	LX_PANEL_TYPE_1024,		///< 1024x768
	LX_PANEL_TYPE_1365,		///< 1365x768
	LX_PANEL_TYPE_3840,		///< 3840x2160@60Hz
	LX_PANEL_TYPE_1280,		///< 1280x720
	LX_PANEL_TYPE_720,		///< 720x480
	LX_PANEL_TYPE_640,		///< 640x480
	LX_PANEL_TYPE_576,		///< 720x576
	LX_PANEL_TYPE_1920_120P,///< 1920x1080@120Hz
	LX_PANEL_TYPE_3840_120P,///< 3840x2160@120Hz
	LX_PANEL_TYPE_MAX		///< max number
}
LX_DE_PANEL_TYPE_T;


/**
 * de display (panel) device type
 */
typedef enum {
	LX_PANEL_DEV_LCD, 		///< LCD/LED device
	LX_PANEL_DEV_PDP,		///< PDP device
	LX_PANEL_DEV_OLED,		///< OLED device
	LX_PANEL_DEV_BOX,		///< CP box device
	LX_PANEL_DEV_GTV_STB,		///< Set-top box device for GTV
	LX_PANEL_DEV_MAX		///< max number
}
LX_DE_PANEL_DEV_T;

/**
 * de date type for firmware version info.
 */
typedef struct {
	UINT16 year;			///< year
	UINT16 month;			///< month
	UINT16 day;				///< day
}
LX_DE_DATE_T;

/**
 * de firmware u-code information.
 */
typedef struct {
	UINT32	version;		///< firmware version
	LX_DE_DATE_T date;		///< updated date
	UINT32 ipc_count;       ///< counter for ipc loop test
}
LX_DE_FIRMWARE_INFO_T;

/**
 * de source window index.
 */
typedef enum {
	LX_DE_WIN_MAIN = 0, ///< main window
	LX_DE_WIN_0    = LX_DE_WIN_MAIN,
	LX_DE_WIN_SUB,		///< sub window
	LX_DE_WIN_1    = LX_DE_WIN_SUB,
	LX_DE_WIN_2, /// venc
	LX_DE_WIN_3, ///< 3rd window (fw:LX_DE_WIN_SUB2)
	LX_DE_WIN_4, ///< 4th window (fw:LX_DE_WIN_SUB3)
	LX_DE_WIN_MAX,	///< max number
}
LX_DE_WIN_ID_T;

/**
 * de horizontal(vertical) start, size in pixel.
 */
typedef struct
{
	UINT16		w;	///< horizontal Size(Width)    in pixel
	UINT16		h;	///< vertical	Size(Height)   in pixel
	UINT16		x;	///< horizontal Start Position in pixel
	UINT16		y;	///< vertical	Start Position in pixel
}
LX_DE_RECT_T;

/**
 * de input window horizontal(vertical) start, size information.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;	///< window index
	LX_DE_RECT_T rect;		///< window demension(w,h,x,y)
}
LX_DE_WIN_DIMENSION_T;

/**
 * de inner pattern type
 */
typedef enum {
	LX_DE_PATTERN_FULL_GRAY = 0, 	///< full white
	LX_DE_PATTERN_WHITE_BOX, 		///< white box on black background
	LX_DE_PATTERN_WHITE_BOX_MOVING, ///< white box on black background with position
	LX_DE_PATTERN_DYNAMIC_INNER, 	///< white box on black background with full white in entering
	LX_DE_PATTERN_MAX 				///< max number
}
LX_DE_PATTERN_TYPE_T;

/**
 * de inner pattern parameter
 */
typedef struct {
	UINT32 enable;				///< inner pattern enable, 0:off,1:on
	LX_DE_PATTERN_TYPE_T type;	///< pattern type
	UINT32 level;				///< level, 0~255
}
LX_DE_INNER_PATTERN_T;

/**
 * de display nonactive region color parameter.
 * de window color for no signal or mute time.
 */
typedef struct {
	UINT8  r;	///< red
	UINT8  g;	///< green
	UINT8  b;	///< blue
}
LX_DE_COLOR_T;

/**
 * de enable input window blank and define window color(black or blue).
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;			///< window index
	BOOLEAN bEnable;				///< mute enable
	LX_DE_COLOR_T win_color;		///< mute color
	BOOLEAN	isRGB;					///< mute color domain
}
LX_DE_SET_WIN_BLANK_T;

/**
 * de input source parameter.
 */
typedef enum {
	LX_DE_SRC_CVI  ,				///< captured external video input
	LX_DE_SRC_MVI  ,				///< video from MPEG decoder A
	LX_DE_SRC_CPU  ,				///< video from system memory A
	LX_DE_SRC_NONE ,				///< No Video
	LX_DE_SRC_MAX					///< Max
}
LX_DE_INPUT_SRC_T;

/**
 * de output format type.
 */
typedef struct {
	LX_DE_PANEL_TYPE_T panel_type;		///< display size
	UINT16 fr_rate;						///< display frame rate
	UINT16 h_total;						///< pixels per line
	UINT16 v_total;						///< lines per frame
	UINT16 h_active;					///< active pixel per line
	UINT16 v_active;					///< active lines per frame
	LX_DE_PANEL_DEV_T dev_type;			///< display device type
}
LX_DE_DIS_FMT_T;

/**
 * de output frame rate mode.
 */
typedef struct {
//	LX_DE_WIN_ID_T win_id;			///< window index --> window ID is not needed
	BOOLEAN isForceFreeRun;			///< enable forced free run mode
	UINT16 fr_rate;				///< frame rate
}
LX_DE_FR_RATE_T;

/**
 * de region type of graped pixels.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;
	UINT32 pixelGrabX;		///< x position
	UINT32 pixelGrabY;		///< y position
	UINT32 pixelGrabW;		///< capture width
	UINT32 pixelGrabH;		///< capture h

	UINT32 realPixelGrabW;	///< real W in memory
	UINT32 realPixelGrabH;	///< real H in memory
	UINT8 colorSpace;		///< 0: YUV 1:RGB
	UINT8 colorDepth;		///< 0: 8bit 1: 10bit
}
LX_DE_GRAB_REGION_T;

/**
 * de color type of graped pixels.
 */
typedef struct
{
	UINT32 pixelGrabCb;		///< Cb or B
	UINT32 pixelGrabY;		///< Y or G
	UINT32 pixelGrabCr;		///< CR or R
}
LX_DE_GRAB_COLOR_T;

/**
 * de scan type parameter.
 */
typedef enum {
	LX_DE_INTERLACED,		///< interlaced scan
	LX_DE_PROGRESSIVE		///< progressive scan
}
LX_DE_SCAN_T;

/**
 * de mvi 3D Video Information.
 *
 */
typedef enum
{
    //interim format - half
	LX_DE_MVI_3D_CHECKERBOARD = 0,		///< 3D check board format
	LX_DE_MVI_3D_COLUMN_INTERLEAVING,	///< 3D column interleaving format
	LX_DE_MVI_3D_ROW_INTERLEAVING,		///< 3D row interleaving format(line alternative)
	LX_DE_MVI_3D_SIDEBYSIDE,			///< 3D Side by Side format
	LX_DE_MVI_3D_TOPNBOTTOM,			///< 3D top and bottom format
	LX_DE_MVI_3D_FRAMESEQ,				///< 3D frame sequence format

    //Full format
	LX_DE_MVI_3D_FRAMEPACK,		    ///< 3D frame packing format
	LX_DE_MVI_3D_FIELD_ALTERNATIVE,	    ///< 3D field alternative format
	LX_DE_MVI_3D_LINE_ALTERNATIVE,		///< 3D line alternative format
	LX_DE_MVI_3D_SIDEBYSIDE_FULL,		///< 3D Side by Side full format
	LX_DE_MVI_3D_DUALSTREAM,			///< 3D dual stream format
    //  From UI, 3D ON?Ì¸é¼­ ¾Æ·¡ Format?Ì ³Ñ¾î¿?¸é 2D to 3D °¡ µÊ
	LX_DE_MVI_3D_2DTO3D,				///< 3D format for2D TO 3D..... INPUT_TYPE_2DTO3D
	LX_DE_MVI_2D,						///< 2D format

    LX_DE_MVI_3D_FORMAT_MAX,

} LX_DE_MVI_3D_INFO_T;

/**
 * de mvi 3D L/R order
 *
 */
 typedef enum
{
	LX_DE_MVI_3D_R_FIRST = 0,			///< right first
	LX_DE_MVI_3D_L_FIRST,			    ///< left first
	LX_DE_MVI_3D_LR_ORDER_MAX			///< max number
}
LX_DE_MVI_3D_LR_ORDER_T;

/**
 * location of pattern
 */
typedef enum {
	LX_DE_PAT_INPUT, // mvi / cvi
	LX_DE_PAT_ND,
	LX_DE_PAT_SRE,
	LX_DE_PAT_WCP,
	LX_DE_PAT_LED,

	LX_DE_PAT_FMC,   // remove after hal code is merged
}
LX_DE_PATTERN_LOCATION_T;

/**
 * control of pattern
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;
	BOOLEAN bOnOff;
	LX_DE_PATTERN_LOCATION_T location;
}
LX_DE_PATTERN_T;

/*
 * pattern & position for latency measure
 */
typedef struct
{
	BOOLEAN bOnOff;
	UINT32 color;  // 0:black, 1:white
	LX_DE_RECT_T rect;
} LX_DE_LATENCY_MEASURE_T;

/**
 * de Debug set type.
 */
 typedef enum {
	LX_DE_DBG_PIXEL_SHIFT = 0,			///< HDMI 13.5 MHz CSC 422 Issue - Pixel Shift
	LX_DE_DBG_SYNC_POSITION = 1,		///< source sync position value for HDMI & RGB
	LX_DE_DBG_CVI_RESET = 2,			///< CVI reset information of CTOP

	LX_DE_DBG_DEVICE_STATUS,
	LX_DE_DBG_TRACE_IOCTL,
	LX_DE_DBG_MISC_DATA,
	LX_DE_DBG_IPC_TEST,
	LX_DE_DBG_VERIFY_FW,
	LX_DE_DBG_SCALER_TPG,
	LX_DE_DBG_TRACE_IPC,
	LX_DE_DBG_VTM_TEST = 10,
	LX_DE_DBG_MUTE_TEST,
	LX_DE_DBG_RESUME_TEST,
	LX_DE_DBG_MUTE_DISABLE,
	LX_DE_DBG_UHD_SETUP,
	LX_DE_DBG_LOCAL_MUTE_TIME = 15,
	LX_DE_DBG_SET_D1_OUT,
	LX_DE_DBG_TEST_HDMI_PIXEL_DELAY, // 17
	LX_DE_DBG_SET_PATTERN,           // 18
	LX_DE_DBG_SET_LATENCY_MEASURE,	 // 19

	LX_DE_DBG_MAX						///< max number
}
LX_DE_DBG_SET_TYPE_T;


/**
 * de Debug set debug type.
 */
typedef struct {
	LX_DE_WIN_ID_T			win_id;			///< window index
	LX_DE_DBG_SET_TYPE_T	type;			///< debug set type
	BOOLEAN					bParam;			///< BOOLEAN parameter
	UINT32					u32Param;		///< UINT32 parameter 1
	UINT32					u32ParamOne;	///< UINT32 parameter 2
	LX_DE_PATTERN_T         pattern;
	LX_DE_LATENCY_MEASURE_T latency_measure;
}
LX_DE_SET_DBG_T;

/**
 * de video timing parameter of vdec interface.
 * used for adaptaion & DDI
 */
typedef struct {
	UINT16 h_size;								///< mvi picture horizontal size
	UINT16 v_size;								///< mvi picture vertical size
	UINT16 h_start;								///< mvi picture horizontal position
	UINT16 v_start;								///< mvi picture vertical position
	LX_DE_SCAN_T isProg;						///< mvi picture scan type(0 : interlace, 1 : progressive)
	UINT16 v_freq;								///< mvi picture vertical frequency
	LX_DE_MVI_3D_INFO_T  mvi_3dfmt_info;		///< MVI 3D Format Information
	LX_DE_MVI_3D_LR_ORDER_T  mvi_3dlr_order;	///< MVI 3D LR Order Information
	UINT32 svp;
	UINT16 afd;
	UINT16 par_width;
	UINT16 par_height;
}
LX_DE_MPEG_TIMING_INFO_T;

/**
 * de cvi source size offset parameter.
 */
typedef struct {
	UINT16	hsize;		///< horizontal pixels
	UINT16	vsize;		///< vertical lines
	UINT16	hoffset;		///< horizontal pixel offset
	UINT16	voffset;	///< vertical line offset
}
LX_DE_CVI_DIMENSION_T;

/**
 * de cvi source color format type.
 */
typedef enum
{
	LX_DE_COLOR_601,		///< SD
	LX_DE_COLOR_709,		///< HD
	LX_DE_COLOR_RGB,		///< PC/DVI 16~235
	LX_DE_COLOR_RGBEX,		///< PC/DVI 0~255
	LX_DE_COLOR_XVYCC601,	///< HDMI deep color for SD
	LX_DE_COLOR_XVYCC709,	///< HDMI deep color for HD
	LX_DE_COLOR_601_CVD,	///< CVBS through CVD
	LX_DE_COLOR_2020_CL,	///< BT.2020 Constant Luminance
	LX_DE_COLOR_2020_NCL,	///< BT.2020 Non-constant Luminace
	LX_DE_COLOR_NOT_DEFINED
}
LX_DE_COLOR_STD_T;

/**
 * de cvi source aspect ratio type.
 */
typedef enum
{
	LX_DE_AR_4_3,		///< 4:3
	LX_DE_AR_16_9		///< 16:9
}
LX_DE_AR_T;


/**
 * de cvi channels type.
 */
typedef enum
{
	LX_DE_CVI_CH_A,		///< channel A
	LX_DE_CVI_CH_B,		///< channel B
	LX_DE_CVI_CH_C,		///< channel C
	LX_DE_CVI_CH_D		///< channel D
}
LX_DE_CVI_CHANNEL_T;

/**
 * de cvi bit resolution.
 */
typedef enum
{
	LX_DE_CVI_10BIT,	///< 10 bit
	LX_DE_CVI_8BIT,		///< 8 bit
	LX_DE_CVI_12BIT,	///< 12 bit
	LX_DE_CVI_16BIT,	///< 16 bit
}
LX_DE_CVI_BITRES_T;

/**
 * de cvi chroma sampling.
 */
typedef enum
{
	LX_DE_CVI_422,	///< 16bit 422 chroma sampling
	LX_DE_CVI_444,	///< 24bit 444 chroma sampling
	LX_DE_CVI_420	///< 12bit 420 chroma sampling
}
LX_DE_CVI_CSAMPLE_T;

/**
 * de scaler operating chroma sampling.
 */
typedef enum
{
	LX_DE_SCALER_420,	///< YUV 420 chroma sampling
	LX_DE_SCALER_422,	///< YUV 422 chroma sampling
	LX_DE_SCALER_444,	///< YUV 444 chroma sampling
}
LX_DE_SCALER_CSAMPLE_T;

/**
 * de cvi data enable mode.
 * hv offsets must be set to zero
 */
typedef enum
{
	LX_DE_CVI_NORMAL_SYNC_MODE,		///< sync mode for CVD, ADC
	LX_DE_CVI_HDMI_SYNC_MODE,		///< sync mode for HDMI CEA (M16B0, M16+ default)
	LX_DE_CVI_HDMI_SYNC_MODE_PVO	///< sync mode for HDMI	PVO
}
LX_DE_CVI_SYNC_MODE_T;

/**
 * de cvi data sampling mode.
 */
typedef enum
{
	LX_DE_CVI_NORMAL_SAMPLING,	///< sync mode for CVD, ADC
	LX_DE_CVI_DOUBLE_SAMPLING,	///< sync mode for HDMI
	LX_DE_CVI_QUAD_SAMPLING		///< sync mode for HDMI
}
LX_DE_CVI_SAMPLING_MODE_T;

/**
 * de cvi data sync stability.
 */
typedef enum
{
	LX_DE_CVI_SYNC_STD,			///< sync is stable
	LX_DE_CVI_SYNC_NONSTD		///< sync is unstable
}
LX_DE_CVI_SYNC_STABILITY_T;

/**
 * de cvi field polarity.
 */
typedef enum
{
	LX_DE_CVI_FIELD_ORIGINAL,		///< original field polarity
	LX_DE_CVI_FIELD_REVERSED		///< reversed field polarity
}
LX_DE_CVI_FIELD_POLARITY_T;

/**
 * de cvi yc delay.
 */
typedef enum
{
	LX_DE_CVI_YC_DELAY_BYPASS,		///< yc_delay_mode_r = 0, yc_delay_mode_b = 0, yc_delay_mode_g = 0
	LX_DE_CVI_YC_DELAY_ATV,			///< yc_delay_mode_r = 0, yc_delay_mode_b = 3, yc_delay_mode_g = 2
	LX_DE_CVI_YC_DELAY_OTHERS		///< yc_delay_mode_r = 0, yc_delay_mode_b = 2, yc_delay_mode_g = 1
}
LX_DE_CVI_YC_DELAY_T;

/**
 * de cvi port select. for [L9]
 */
typedef enum
{
	LX_DE_CVI_EXT_A,  ///<
	LX_DE_CVI_EXT_B,  ///<
	LX_DE_CVI_CVD,	  ///<
	LX_DE_CVI_ADC	  ///<
}
LX_DE_CVI_PORT_T;

/**
 * de cvi 3D Video Full Information. for[L9]
 *
 */
typedef enum
{
	LX_DE_CVI_NORMAL_FORMAT = 0,		///< 2D format
	LX_DE_CVI_3D_FRAMEPACK,				///< 3D frame packing format
	LX_DE_CVI_3D_SBSFULL,				///< 3D Side by Side Full format
	LX_DE_CVI_3D_FIELD_ALTERNATIVE,		///< 3D field alternative format
	LX_DE_CVI_3D_ROW_INTERLEAVING,		///< 3D row interleaving format(line alternative)
	LX_DE_CVI_3D_COLUMN_INTERLEAVING,	///< 3D column interleaving format
	LX_DE_CVI_4K_2K,						///< 4K x 2K format
} LX_DE_CVI_3D_FULL_INFO_T;

/**
 * de cvi source type Information. for[L9]
 *
 */
typedef enum
{
	// Component Analog ports
	LX_DE_CVI_SRC_VGA,
	LX_DE_CVI_SRC_YPBPR,

	// Composite Analog ports
	LX_DE_CVI_SRC_ATV,
	LX_DE_CVI_SRC_CVBS,

	// Seperate Analog Ports
	LX_DE_CVI_SRC_SVIDEO,

	// SCART port
	LX_DE_CVI_SRC_SCART,

	// HDMI ports
	LX_DE_CVI_SRC_HDMI,

	LX_DE_CVI_SRC_NUM,

} LX_DE_CVI_INPUT_SRC_T;

/**
 * de cvi game mode from HDMI 2.1
 *
 */
typedef struct
{
	UINT32 isFreeSyncMode  : 8; //  7:0   :
	UINT32 isGSyncMode     : 8; // 15:8   :
	UINT32 isVrrMode	   : 8; // 23:16  :
	UINT32 isFvaMode	   : 1; // 24	 :
	UINT32 isMConst	       : 1; // 25	 : MConst flag
	UINT32 isQmsMode       : 1; // 26 : QMS falg
	UINT32 fvaFactor      : 5; // 27:31 : FVA factor
} LX_DE_CVI_GAME_MODE_T;

/**
 * This enum is used to set CVD PQ Value to selected Color System
 * @see AFE_IOW_SET_3DCOMB_VALUE
 */

typedef enum {
	LX_DE_COLOR_DEFAULT		= 0,		///< Default CVD Params
	LX_DE_COLOR_NTSC_M		= 1,		///< CVD Params for NTSC_M AV inputs
	LX_DE_COLOR_NTSC_M_RF	= 2,		///< CVD Params for NTSC_M RF input
	LX_DE_COLOR_PAL			= 3,		///< CVD Params for NTSC_M AV inputs
	LX_DE_COLOR_PAL_RF		= 4,		///< CVD Params for NTSC_M RF input
	LX_DE_COLOR_SECAM		= 5,		///< CVD Params for NTSC_M AV inputs
	LX_DE_COLOR_SECAM_RF	= 6,		///< CVD Params for NTSC_M RF input
	LX_DE_COLOR_NTSC_443	= 7,		///< CVD Params for NTSC_443 AV inputs
	LX_DE_COLOR_NTSC_443_RF = 8,		///< CVD Params for NTSC_443 RF input
	LX_DE_COLOR_PAL_60		= 9,		///< CVD Params for PAL_60 AV inputs
	LX_DE_COLOR_PAL_60_RF	= 10,		///< CVD Params for PAL_60 RF input
	LX_DE_COLOR_PAL_M		= 11,		///< CVD Params for PAL_M AV inputs
	LX_DE_COLOR_PAL_M_RF	= 12,		///< CVD Params for PAL_M RF input
	LX_DE_COLOR_PAL_NC		= 13,		///< CVD Params for PAL_NC AV inputs
	LX_DE_COLOR_PAL_NC_RF	= 14,		///< CVD Params for PAL_NC RF input
	LX_DE_COLOR_UNKNOWN   	= 15,		///< CVD Params for Color System Unkown
	LX_DE_COLOR_NUM			= 16,
} LX_DE_CVD_COLOR_STD_T;

typedef enum {
	LX_DE_CVI_SPLIT_OFF		= 0, // no split
	LX_DE_CVI_SPLIT_1X2		= 1, // 1x2
	LX_DE_CVI_SPLIT_1X4		= 2, // 1x4
	LX_DE_CVI_SPLIT_1X2_DUP = 3, // 1x2, duplicate mode
	LX_DE_CVI_SPLIT_MAX
} LX_DE_CVI_SPLIT_MODE_T;

/**
 * de attribute for split info from external HDMI switch.
 */
typedef struct {
	LX_DE_CVI_BITRES_T bpp;
	LX_DE_CVI_SPLIT_MODE_T split_mode;
	UINT16 overlap; // 0:off, 1~:pixels
	UINT16 width;
	UINT16 height;
	UINT16 rate;
}
LX_DE_CVI_SPLIT_INFO_T;

/**
 * de attribute for HDMI2.1 FRL
 */
typedef struct {
	UINT32                     pixelClock;
	UINT32                     phyMode;           /// 0:3G, 1:6G, 2:FRL 3L3G, 3:3L6G, 4:4L4G, 5:4L8G, 6:4L10G, 7:4L12
}
LX_DE_CVI_FRL_INFO_T;

/**
 * HDMI AVI Color Space.
 * AVI Color Space TYPE is defined.
 */
typedef enum
{
	LX_DE_AVI_COLORSPACE_RGB = 0,			///< RGB
	LX_DE_AVI_COLORSPACE_YCBCR422,		///< YCbCr422
	LX_DE_AVI_COLORSPACE_YCBCR444,		///< YCbCr444
	LX_DE_AVI_COLORSPACE_YCBCR420,		///< YCbCr420
	LX_DE_AVI_COLORSPACE_MAX		,		///< Max
	//LX_HDMI_AVI_COLORSPACE_FUTURE			///< Future
} LX_DE_AVI_COLORSPACE_T;

/**
 * de cvi source attribute type.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T		   cvi_channel;		  ///< CVI channel A or B
	LX_DE_CVI_DIMENSION_T	   size_offset;		  ///< h/v size offset
	LX_DE_COLOR_STD_T		   color;			  ///< color space 601,709,PC
	LX_DE_AR_T				   aspect;			  ///< aspect ratio 4:3 or 16:9
	LX_DE_SCAN_T			   scan;			  ///< interlaced or progressive
	LX_DE_CVI_BITRES_T		   bit_res;			  ///< bit resolution 10bit(0) or 8bit(1)
	LX_DE_CVI_CSAMPLE_T		   c_sample;		  ///< chroma sampling mode 422(0) or 444(1)
	LX_DE_CVI_SYNC_MODE_T	   de_mode;			  ///< internal data enable mode generated from sync(0) or de(1)
	LX_DE_CVI_SAMPLING_MODE_T  sampling;		  ///< external input sampling: noraml(0), double(1), quadrature(2)
	LX_DE_SCALER_CSAMPLE_T	   sc_c_sample;		  ///< scaler chroma sampling mode YUV420(0) YUV422(1) YUV444(2)
	union
	{
		LX_DE_CVI_SYNC_STABILITY_T stability;		  ///< stable sync(0), unstable sync(1)
		LX_DE_AVI_COLORSPACE_T	   avi_colorspace_info; ///< HDMI AVI Color Space.
		UINT32                     sizer;
	};
	LX_DE_CVI_FIELD_POLARITY_T field_polarity;	  ///< original field polarity(0), reversed field polarity(1)
	LX_DE_CVI_YC_DELAY_T	   yc_delay;
	LX_DE_CVI_PORT_T		   cvi_port;		  ///< cvi port select. for [L9]
	LX_DE_CVI_3D_FULL_INFO_T   trid_full_format;  ///< 3D Video Full Information. for [L9]
	LX_DE_CVI_INPUT_SRC_T	   cvi_input_src;	  ///< cvi source type Information. for[L9]
	LX_DE_CVD_COLOR_STD_T	   cvd_color_std;	  ///< CVD color mode for[L9]
	LX_DE_CVI_GAME_MODE_T      cvi_game_info;
	LX_DE_CVI_SPLIT_INFO_T     cvi_split_info;
	LX_DE_CVI_FRL_INFO_T       cvi_frl_info;
}
LX_DE_CVI_SRC_TYPE_T;

/**
 * de captured source FIR control parameter.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isEnable;					///< fir enable
	UINT16 fir_coef[8];					///< fir coefficient
	UINT16 fir_coef_CbCr[6];			///< CbCr fir coefficient, add from L9 B0, by sh.myoung 201108
}
LX_DE_CVI_FIR_T;

/**
 * de cvi test pattern gen. pattern type.
 */
typedef enum
{
	LX_DE_CVI_TPG_WHITE,		///< white
	LX_DE_CVI_TPG_YELLOW,		///< yellow
	LX_DE_CVI_TPG_CYAN,			///< cyan
	LX_DE_CVI_TPG_GREEN,		///< green
	LX_DE_CVI_TPG_MAGENTA,		///< magenta
	LX_DE_CVI_TPG_RED,			///< red
	LX_DE_CVI_TPG_BLUE,			///< blue
	LX_DE_CVI_TPG_BLACK,		///< black
	LX_DE_CVI_TPG_GRADATION_H,	///< horizontal gradation
	LX_DE_CVI_TPG_GRADATION_V,	///< vertical gradation
	LX_DE_CVI_TPG_GRADATION_C,	///< color gradation
	LX_DE_CVI_TPG_GRADATION_YC, ///< Y/C gradation
	LX_DE_CVI_TPG_BW			///< black and white
}
LX_DE_CVI_TPG_COLOR_T;

/**
 * de captured test pattern generator.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isPtnOn;					///< pattern enable
	BOOLEAN isFrzOn;					///< freeze enable
	BOOLEAN isGBR;						///< pattern color space
	LX_DE_CVI_TPG_COLOR_T ptnColor;		///< pattern color
}
LX_DE_CVI_TPG_T;

/**
 * de captured source color sub-sampling parameter.(for YUV422)
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN is3tap;					///< sub_sample(0), 3-tap-filter[1:2:1] (1)
}
LX_DE_CSAMPLE_MODE_T;

/**
 * de captured source sync status parameter.(for debug)
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN h;					///< hsync status
	BOOLEAN v;					///< vsync status
	BOOLEAN de;					///< de status
	BOOLEAN valid;				///< source valid
	UINT16 lnum;				///< current line number
}
LX_DE_CVI_SYNC_STATUS_T;

/**
 * de colorimetry information of mpeg decoder (vdec).
 * used for kdriver
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;	///< window index
	LX_DE_COLOR_STD_T colorimetry;	///< colorimetry of MPEG (601 or 709)
}
LX_DE_MVI_COLORIMETRY_T;

/**
 * de video layer type definition.
 * layer order of video,osd1,2,3 can be changed
 */

typedef enum {
	LX_SURFACE_VIDEO = 0,	///< video layer
	LX_SURFACE_OSD1 = 1,	///< osd layer 1
	LX_SURFACE_OSD2 = 2,	///< osd layer 2
	LX_SURFACE_OSD3 = 3,	///< osd layer 3
	LX_SURFACE_CURSOR = 4,	///< osd cursor layer
	LX_SURFACE_MAX			///< max number
}
LX_DE_SURFACE_T;

/**
 * de video layer(z-order) control type.
 */

typedef struct {
	BOOLEAN enable;				///< z-list on/off (off : hw default order, win0-bottom/win1-top)
	UINT32 z_list[2];			///< index : order(0->top, 1->bottom) , value : win_id
	UINT32 alpha[2];			///< index : order(0->top, 1->bottom) , value : blending alpha
}
LX_DE_ZLIST_T;

/* ############### DE CVE  ################ */

/**
 * de DENC path selection
 * with OSD: set RGB to YUV mdm csc and mdm csc enable(use default csc coef.)
 * w/o OSD(PE1): set RGB to YUV mdm csc and mdm csc enable(use default csc coef.)
 * refer DE0B_CTRL/MDM_CTRL/MDM_CSC_COEF
 * w/o OSD(OV) : mdm csc disable
 */
typedef enum {
	LX_DE_CVE_WITH_OSD = 0,		///< Denc path feedback with OSD(DE end)
	LX_DE_CVE_WITHOUT_OSD,		///< Denc path feedback w/o OSD(select OV or PE1)
	LX_DE_CVE_FROM_SRC			///< Denc path from source ( original aspect ratio)
}
LX_DE_CVE_PATH_T;

/**
 * de DENC timing standard
 * PAL and SECAM have same sync parameters
 */
typedef enum {
	LX_DE_CVE_NTSC = 0,		///< Denc type is NTSC 60Hz
	LX_DE_CVE_PAL,			///< Denc type is PAL 50Hz
	LX_DE_CVE_SECAM			///< Denc type is SECAM 50Hz
}
LX_DE_CVE_TIMING_T;

/**
 * de CVE parameter.
 *
*/
typedef struct
{
	LX_DE_CVE_PATH_T	fb;		///< CVE feedback path (0: with OSD 1: w/o OSD, 2: src)
	LX_DE_CVE_TIMING_T std;		///< CVE timing selection(0: NTSC 1: PAL 2:SECAM)
}
LX_DE_CVE_PARAM_T;

/**
 * de register value read type.
 */

typedef struct {
	UINT32 wr_addr; ///< register address
	UINT32 wr_data; ///< write data
}
LX_DE_REG_WR_T;


/**
 * IPC for VCS
 * index of IPC for VCS
 * 0  : frame_inx
 * 1  : pic_info
 * 2  : frame_rate
 * 3  : aspect_ratio
 * 4  : picture_size
 * 5  : h_offset
 * 6  : v_offset
 * 7  : frameupdated
 * 8  : y_frame_base_address
 * 9  : c_frame_base_address
 * 10 : y_frame_offset
 * 11 : c_frame_offset
 * 12 : stride
 * 13 : pixel_aspect_ratio
 * 14 : vdi_framepackarrange
 * 15 : vdi_ptsinfo
 */
typedef struct
{
	UINT32			inx;		///< index of vcs for IPC
	UINT32			data;		///< data of vcs for IPC
}
LX_DE_VCS_IPC_T;

/* cfg define of LX_DE_FW_DWLD_T */
/* DE_FW_CFG_DOWNLOAD_HEADER : copy header to ddr (memcpy) */
/* DE_FW_CFG_CPY_TO_DDR_SKIP : skip copy to ddr (just stall off) */
/* DE_FW_CFG_COPY_BIN_TO_DDR : copy file to ddr (kernel_read) */
/* DE_FW_CFG_COPY_USR_TO_DDR : copy user bin to ddr (copy_from_user) */
/* DE_FW_CFG_COPY_MAP_TO_DDR : malloc bin and copy bin to ddr (memcpy) */
/* DE_FW_CFG_BIN_PATH_INFO   : bin path info (kernel read) */
/* DE_FW_CFG_PRINT_USR_STR   : print usr str (logm noti) */
#define DE_FW_CFG_DOWNLOAD_HEADER   0
#define DE_FW_CFG_CPY_TO_DDR_SKIP   1
#define DE_FW_CFG_COPY_BIN_TO_DDR   2
#define DE_FW_CFG_COPY_USR_TO_DDR   3
#define DE_FW_CFG_COPY_MAP_TO_DDR   4
#define DE_FW_CFG_BIN_PATH_INFO     5
#define DE_FW_CFG_PRINT_USR_STR     10
#define DE_FW_CFG_MAX_NUM           11

/**
 * de FW Download.
 */
typedef struct {
	int  inx;					///< inx --> index of Firmware
	int  cfg;					///< cfg --> config of Firmware download, 1:resume(bin)
	int  size;					///< size  --> size of Firmware
	union
	{
		char *pData;				///< data  --> pointer carring data of Firmware
		UINT32 compat_pData;
		UINT64 sizer;
	};
}
LX_DE_FW_DWLD_T;

/**
 * de FW Download (from header).
 */
typedef struct {
	int  inx;					///< inx --> index of Firmware
	int  cfg;					///< cfg --> config of Firmware download, 1:resume(bin)
	int  size;					///< size  --> size of Firmware
	char *pData;				///< data  --> pointer carring data of Firmware
}
LX_DE_FW_DWLD_FR_HD_T;

/**
 * de DVR on type
 */
typedef enum {
	LX_DE_DVR_OFF,				///< off
	LX_DE_DVR_ATV_REC,			///< ATV Rec.
	LX_DE_DVR_MIRACAST_TX,		///< Miracast Tx
	LX_DE_DVR_FACEBOOK_CHAT		///< Facebook chatting
}
LX_DE_DVR_ON_T;

/**
 * de DVR display format control. (de -> venc)
 */
typedef struct {
	LX_DE_DVR_ON_T bOnOff;
	LX_DE_SCAN_T scan;
	UINT16 h_size;
	UINT16 v_size;
	UINT32 fr_rate;
	UINT32 baseAddr;
	UINT32 fb_pos;   // 0:fb disable (ATV Rec.) 1:video only, 2:with osd, 3:osd ony
	UINT16 h_size_sub1;
	UINT16 v_size_sub1;
	UINT16 h_size_sub2;
	UINT16 v_size_sub2;
	UINT32 id;       // instance id
}
LX_DE_DVR_DISFMT_T;

typedef struct {
	UINT32 phyFrameAddrY8;
	UINT32 phyFrameAddrC8;
	UINT32 phyFrameAddrY2;
	UINT32 phyFrameAddrC2;
	UINT32 stride;
}
LX_DE_FRAME_ADDR;

/**
 * de read/write video frame before CVI csc parameter for self-diagnosis.
 */
typedef struct
{
	LX_DE_GRAB_REGION_T region; ///< grapped region
	union
	{
		LX_DE_GRAB_COLOR_T	*color; ///< grapped pixels color value
		UINT32				compat_color;
		UINT64				sizer;
	};
	BOOLEAN bReadOnOff;			/// Read(True), Write(False)
	LX_DE_FRAME_ADDR frameAddr;// phy address
}
LX_DE_CVI_RW_VIDEO_FRAME_T;

/**
 * * de read/write video frame before CVI csc parameter for self-diagnosis.
 * */
typedef struct
{
	LX_DE_WIN_ID_T win_id;
	LX_DE_FRAME_ADDR frameAddr;// phy address
	LX_DE_SCALER_CSAMPLE_T csample;
	LX_DE_RECT_T rect;
}
LX_DE_CVI_RW_PREW_FRAME_T;

/**
 * input port for multi window
 */
typedef enum {
	LX_DE_PORT_MVI,
	LX_DE_PORT_CVD,
	LX_DE_PORT_ADC,
	LX_DE_PORT_HDMI
}
LX_DE_INPUT_PORT;

/**
 * de source for multi window
 */
typedef enum {
	LX_DE_MULTI_IN_CVD_ADC,
	LX_DE_MULTI_IN_CVD_HDMI,
	LX_DE_MULTI_IN_CVD_MVI,
	LX_DE_MULTI_IN_CVD_CPU,
	LX_DE_MULTI_IN_CVD_CVD,
	LX_DE_MULTI_IN_ADC_CVD,
	LX_DE_MULTI_IN_ADC_HDMI,
	LX_DE_MULTI_IN_ADC_MVI,
	LX_DE_MULTI_IN_ADC_CPU,
	LX_DE_MULTI_IN_ADC_ADC,
	LX_DE_MULTI_IN_HDMI_CVD,
	LX_DE_MULTI_IN_HDMI_ADC,
	LX_DE_MULTI_IN_HDMI_MVI,
	LX_DE_MULTI_IN_HDMI_CPU,
	LX_DE_MULTI_IN_HDMI_HDMI,
	LX_DE_MULTI_IN_MVI_CVD,
	LX_DE_MULTI_IN_MVI_ADC,
	LX_DE_MULTI_IN_MVI_HDMI,
	LX_DE_MULTI_IN_MVI_CPU,
	LX_DE_MULTI_IN_MVI_MVI,
	LX_DE_MULTI_IN_CPU_CVD,
	LX_DE_MULTI_IN_CPU_ADC,
	LX_DE_MULTI_IN_CPU_HDMI,
	LX_DE_MULTI_IN_CPU_MVI,
	LX_DE_MULTI_IN_CPU_CPU,

	LX_DE_MULTI_IN_MVA_MVB,
	LX_DE_MULTI_IN_HDMIA_HDMIB,
	LX_DE_MULTI_IN_MAX
}
LX_DE_MULTI_SRC_T;

/**
 * de input port for multi window source mapping
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;					///< window index
	LX_DE_INPUT_PORT in_port;			///< input port for multi window
}
LX_DE_MULTI_WIN_SRC_T;


/**
 * capture/freeze on or off for cvi capture
 */
typedef struct {
	BOOLEAN bCaptureOnOff;
	BOOLEAN bCviFreezeOnOff;			///< input port for multi window
}
LX_DE_CVI_CAPTURE_FREEZE_T;

/**
 * PQ Firmware Control
 */
typedef struct {
	UINT8 enable;
}
LX_DE_PQ_FIRMWARE_CTRL;

/**
 * PE1 Sharpness Coring Control_05
 */
typedef struct {
	UINT8 gt_th0;
	UINT8 gt_th1;
}
LX_DE_SHP_CORING_CTRL_05;

/**
 * PE1 Sharpness Coring Control_06
 */
typedef struct {
	UINT8 gt_th0a;
	UINT8 gt_th0b;
}
LX_DE_SHP_CORING_CTRL_06;

/**
 * PE1 Sharpness Coring Control_09
 */
typedef struct {
	UINT8 edge_gain_b;
	UINT8 edge_gain_w;
	UINT8 texture_gain_b;
    UINT8 texture_gain_w;
}
LX_DE_SHP_CORING_CTRL_09;

/**
 * PE1 Sharpness DP Control_01
 */
typedef struct {
	UINT8 edge_gain_b;
	UINT8 edge_gain_w;
	UINT8 texture_gain_b;
    UINT8 texture_gain_w;
}
LX_DE_SHP_DP_CTRL_01;


/**
 * PE1 Sharpness DERH Control_08
 */
typedef struct {
	UINT8  e_gain_th1;
	UINT8  e_gain_th2;
}
LX_DE_SHP_DERH_CTRL_0B;

/**
 * PE1 FMD Control
 */
typedef struct {
	UINT8 fmd_enable;
}
LX_DE_FMD_CTRL;

/**
 * Mute Control
 */
typedef struct {
	UINT8 mute_enable;
}
LX_DE_MUTE_CTRL;

/**
 * TNR Auto Control
 */
typedef struct {
	UINT8 auto_enable;
}
LX_DE_TNR_CTRL;

/**
 * Scaler Control
 */
typedef struct {
	UINT8 set_cnt;
}
LX_DE_SCL_CTRL;

/**
 * SRC Info
 */
typedef struct {
	UINT8 dtv_play_type;
}
LX_DE_SRC_INFO;

/**
 * PQ Firmware IPC Control
 */
typedef struct {
    LX_DE_PQ_FIRMWARE_CTRL    pq_firmware_ctrl;
    LX_DE_SHP_CORING_CTRL_05  shp_coring_ctrl_05;
	LX_DE_SHP_CORING_CTRL_06  shp_coring_ctrl_06;
    LX_DE_SHP_CORING_CTRL_09  shp_coring_ctrl_09;
    LX_DE_SHP_DP_CTRL_01      shp_dp_ctrl_01;
    LX_DE_SHP_DERH_CTRL_0B    shp_derh_ctrl_0B;
    LX_DE_FMD_CTRL            fmd_ctrl;
    LX_DE_MUTE_CTRL           mute_ctrl;
    LX_DE_TNR_CTRL            TNR_ctrl;
    LX_DE_SCL_CTRL            scl_ctrl;
    LX_DE_SRC_INFO            src_info;
}
LX_DE_PQ_IPC_CTRL;

typedef struct {
	UINT32 start : 12;
	UINT32 count : 12;
	UINT32 winId : 4;
} PQL_TABLE_HEAD_T;

/**
 * de parameter as to capture raw image used for debugging
 */
typedef struct {
	UINT32	mode;
	UINT32	*base_addr;
	UINT32	size;
}
LX_DE_PAR_CAPTURE_RAW_IMAGE_T;

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
LX_DE_LOW_DELAY_T;

/**
 *  * 3D formatter running mode parameter.
 *   * select 3D formatter operation mode. it controls 3D mode ON/OFF.
 *    */
typedef enum
{
	LX_DE_3D_RUNMODE_OFF = 0,	///< 2D mode, 3D off(bypass)
	LX_DE_3D_RUNMODE_ON,		///< 3D mode, 3D on
	LX_DE_3D_RUNMODE_3DTO2D,	///< 3D input 2D output
	LX_DE_3D_RUNMODE_2DTO3D,	///< 3D input 2D output
	LX_DE_3D_RUNMODE_MAX		///< max number
}
LX_DE_3D_RUNMODE_T;

/**
 *  * 3D formatter image format parameter.
 *   * used for input image format and output image format.
 *    */
typedef enum {
	LX_DE_3D_IMG_IN_TOPNBOTTOM = 0,		///< top and bottom
	LX_DE_3D_IMG_IN_SIDEBYSIDE,			///< side by side
	LX_DE_3D_IMG_IN_QUINCUNX,				///< quincunx
	LX_DE_3D_IMG_IN_CHECKERBOARD,			///< check board
	LX_DE_3D_IMG_IN_FRAMEPACKING,			///< frame packing
	LX_DE_3D_IMG_IN_FRAMEINTERLACE,		///< frame packing interlace
	LX_DE_3D_IMG_IN_FIELDALTERNATE,		///< field alternate
	LX_DE_3D_IMG_IN_FRAMESEQ,				///< frame sequence
	LX_DE_3D_IMG_IN_LINEALTERNATIVE,		///< line alternative full
	LX_DE_3D_IMG_IN_SIDEBYSIDE_FULL,		///< side by side full
	LX_DE_3D_IMG_IN_DUAL_HD,				///< dual HD e.g.) One is mpeg-2 ts, the other is mpeg-4 ts scenario
	LX_DE_3D_IMG_IN_COLUMNALTERNATIVE,		///< column alternate(interleaving) - mpeg
	LX_DE_3D_IMG_IN_LINEALTERNATIVE_HALF,	///< line alternative half
	LX_DE_3D_IMG_IN_MAX					///< max number
}
LX_DE_3D_IMG_FMT_IN_T;

/**
 *  * 3D formatter image format parameter.
 *   * used for input image format and output image format.
 *    */
typedef enum {
	LX_DE_3D_IMG_OUT_SINGLE_2D    = 0,	///< single nomal
	LX_DE_3D_IMG_OUT_SINGLE_TB,			///< top and bottom
	LX_DE_3D_IMG_OUT_SINGLE_SS,			///< side by side
	LX_DE_3D_IMG_OUT_SINGLE_FS,			///< Frame Sequential(Interleaving)
	LX_DE_3D_IMG_OUT_DUAL_FULL,			///< dual screen
	LX_DE_3D_IMG_OUT_DUAL_TB,			///< dual top and bottom for H13 internal type
	LX_DE_3D_IMG_OUT_DUAL_SS,			///< dual side by side for H13 internal type
	LX_DE_3D_IMG_OUT_SINGLE_LA,			///< line alternative
	LX_DE_3D_IMG_OUT_MAX				///< max number
}
LX_DE_3D_IMG_FMT_OUT_T;

/**
 *  * 3D formatter Left Roght order parameter.
 *   * used for input image and output image.
 *    */
typedef enum
{
	LX_DE_3D_LR_ORDER_R_FIRST = 0,		///< right first
	LX_DE_3D_LR_ORDER_L_FIRST,			///< left first
	LX_DE_3D_LR_ORDER_MAX				///< max number
}
LX_DE_3D_LR_ORDER_T;

/**
 *  * 3D formatter input/output control type.
 *   *  0xFF   : invalid
 *    *  Others :   valid
 *     */
typedef struct {
	LX_DE_3D_RUNMODE_T		run_mode;			///< select formatter operation mode. it controls 3D mode ON/OFF.
	LX_DE_3D_IMG_FMT_IN_T		in_img_fmt;			///< input image format(top/bottom, sidebyside, checkboard, frame, field seq, dual 2d)
	LX_DE_3D_LR_ORDER_T 		in_lr_order;		///< input left/right first order
	LX_DE_3D_IMG_FMT_OUT_T 	out_img_fmt;		///< output image format(top/bottom, sidebyside, checkboard, frame, field seq)
	LX_DE_3D_LR_ORDER_T  	out_lr_order;		///< output left/right first order
}
LX_DE_3D_INOUT_CTRL_T;

/////////////////////////H13//////////////////////////////////////////////////
typedef enum {
	LX_DE_HDMI444_NONE,
	LX_DE_HDMI444_OFF,
	LX_DE_HDMI444_ON,
	LX_DE_HDMI444_MAX
}	LX_DE_HDMI444_MODE_T;

typedef enum {
	LX_DE_DIRECT_INPUT,
	LX_DE_DIRECT_OUTPUT,
	LX_DE_DIRECT_MAX
}	LX_DE_DIRECT_T;

typedef enum
{
	LX_DE_RW_SET,
	LX_DE_RW_GET,
	LX_DE_RW_MAX
}	LX_DE_RW_T;

typedef struct {
	LX_DE_WIN_ID_T  		win_id;
	LX_DE_RECT_T 		rect;
	LX_DE_DIRECT_T		direct_type;
	LX_DE_RW_T			rw_type;
} LX_DE_WIN_CONFIG_T;


typedef enum {
	LX_DE_IN_SRC_NONE,
	LX_DE_IN_SRC_VGA,
	LX_DE_IN_SRC_YPBPR,
	LX_DE_IN_SRC_ATV,
	LX_DE_IN_SRC_CVBS,
	LX_DE_IN_SRC_SCART,
	LX_DE_IN_SRC_HDMI,
	LX_DE_IN_SRC_MVI,
	LX_DE_IN_SRC_CPU,
	LX_DE_IN_SRC_FB,
	LX_DE_IN_SRC_MAX
} LX_DE_IN_SRC_T;


typedef struct {
	LX_DE_WIN_ID_T 		win_id;			///< Display window index
	LX_DE_IN_SRC_T 		inputSrc;		///< Input source type
	UINT32				inputSrcPort;	///< Input port info (CVI_A,CVI_B, MVI_0,1,2,3)
	UINT32				inputResv;		///< Reserve parameter
} LX_DE_INPUT_CFG_T;


typedef enum
{
	LX_DE_OPER_ONE_WIN,				///< No Video
	LX_DE_OPER_TWO_WIN,
   	LX_DE_OPER_3D,
	LX_DE_OPER_UD,
	LX_DE_OPER_VENC,
	LX_DE_OPER_MAX
}	LX_DE_OPER_CONFIG_T;

typedef enum
{
	LX_DE_UD_OFF,
	LX_DE_UD_ON,		// 4k x 2k
	LX_DE_UD_HALF,		// 2k x 2k
	LX_DE_UD_MAX,		// 2k x 2k
} LX_DE_UD_CTRL_T;

typedef struct
{
	BOOLEAN bOnOff;
	LX_DE_SCAN_T scan;
	UINT16	hSize;
	UINT16 	vSize;
	UINT16 	frRate;
}	LX_DE_VENC_FMT_T;

/**
 *	DE operation.
 *
 */
typedef struct
{
	LX_DE_WIN_ID_T 		win_id;			///< De window index
	LX_DE_OPER_CONFIG_T	operation;		///< operation flag

	UINT32				multiCtrl;		// use Two window
	LX_DE_UD_CTRL_T	udCtrl;			// UD mode
	LX_DE_3D_INOUT_CTRL_T 	ctrl3D;		// use 3D mode
	LX_DE_VENC_FMT_T	vencCtrl;		// use for venc src format
}	LX_DE_OPERATION_CTRL_T;

typedef enum
{
	LX_DE_SUB_OPER_OFF,			///<
	LX_DE_SUB_OPER_CAPTURE,		///<
	LX_DE_SUB_OPER_VENC,			///<
	LX_DE_SUB_OPER_SCART_OUT,	///<
	LX_DE_SUB_OPER_MAX
}	LX_DE_SUB_OPER_CONFIG_T;

/**
 *	DE sub operation.
 *
 */
typedef struct
{
	LX_DE_WIN_ID_T 				win_id;			///< De window index
	LX_DE_SUB_OPER_CONFIG_T	operation;		///< De window index

	UINT32						capture_enable;	// for capture
	LX_DE_VENC_FMT_T			vencCtrl;		// use for venc src format
}	LX_DE_SUB_OPERATION_CTRL_T;

/*
 * de location for capture.
 */
typedef enum
{
	LX_DE_LOCATION_SOURCE,		///< DE Input Source
	LX_DE_LOCATION_DISPLAY,		///< Display Source
	LX_DE_LOCATION_OSD,
	LX_DE_LOCATION_BACKGROUND,  ///< bg sub path capture (https://harmony.lge.com:8443/issue/browse/SICREQ-1132)
	LX_DE_LOCATION_MAX			///< MAX
}	LX_DE_LOCATION_T;

/*
 * de pixel format parameter.
 */
typedef enum
{
	LX_DE_PIXEL_FORMAT_RGB_10,
	LX_DE_PIXEL_FORMAT_RGB_8,
	LX_DE_PIXEL_FORMAT_YCBCR444_10,
	LX_DE_PIXEL_FORMAT_YCBCR444_8,
	LX_DE_PIXEL_FORMAT_YCBCR422_10,
	LX_DE_PIXEL_FORMAT_YCBCR422_8,
	LX_DE_PIXEL_FORMAT_YCBCR420_10,
	LX_DE_PIXEL_FORMAT_YCBCR420_8,
	LX_DE_PIXEL_FORMAT_MAX
}	LX_DE_PIXEL_FORMAT_T;

/*
 * de capture type.
 */
typedef struct
{
	LX_DE_WIN_ID_T 			win_id;			///< De window index
	LX_DE_LOCATION_T		location;		///< direction info of source for capture
	LX_DE_RECT_T 			inWin;			///< input window for capture
	UINT16					wOutSize;		///< output width size for capture
	UINT16		 			hOutSize;		///< output height size for capture
	LX_DE_PIXEL_FORMAT_T	pixelFormat;	///< pixel data format
	union
	{
		UINT8 					*p_y_frame;		///< y frame data start address
		UINT32					compat_p_y_frame;
		UINT64					sizer_p_y_frame;
	};
	union
	{
		UINT8 					*p_cbcr_frame;	///< cbcr frame data start address
		UINT32					compat_p_cbcr_frame;
		UINT64					sizer_p_cbcr_frame;
	};
	UINT32					stride;			///< stride size
}	LX_DE_CAPTURE_CTRL_T;

typedef enum
{
	LX_DE_CONFIG_TYPE_ALL,			///<for setting all config
	LX_DE_CONFIG_TYPE_DISPLAY_DEVICE,
	LX_DE_CONFIG_TYPE_DISPLAY_MIRROR,
	LX_DE_CONFIG_TYPE_FRC,
	LX_DE_CONFIG_TYPE_3D,
	LX_DE_CONFIG_TYPE_MAX,
}	LX_DE_CONFIG_T;

typedef enum {
	LX_DE_DIS_DEV_LCD, 	///< LCD/LED device
	LX_DE_DIS_DEV_PDP,	///< PDP device
	LX_DE_DIS_DEV_OLED,	///< OLED device
	LX_DE_DIS_DEV_CP,		///< CP box device
	LX_DE_DIS_DEV_STB,	///< Set-top box device
	LX_DE_DIS_DEV_MAX		///< max number
}	LX_DE_DISPLAY_DEVICE_T;

typedef enum {
	LX_DE_DIS_MIRROR_OFF, 	///< diaplay mirror off
	LX_DE_DIS_MIRROR_X, 		///< diaplay mirror x position
	LX_DE_DIS_MIRROR_Y, 		///< diaplay mirror y position
	LX_DE_DIS_MIRROR_X_Y, 	///< diaplay mirror x, y position
	LX_DE_DIS_MIRROR_MAX		///< max number
}	LX_DE_DISPLAY_MIRROR_T;

typedef enum
{
	LX_DE_FRC_PATH_INTERNAL,
	LX_DE_FRC_PATH_EXTERNAL,
	LX_DE_FRC_PATH_MAX,
} LX_DE_FRC_PATH_T;

typedef enum
{
	LX_DE_3D_CTRL_OFF,
	LX_DE_3D_CTRL_ON,
	LX_DE_3D_CTRL_MAX,
} LX_DE_3D_CTRL_T;

/*
 * default : DIS_DEV - LCD,  FRC Path - Internal, 3D ctrl -ON
 */
typedef	struct
{
	LX_DE_CONFIG_T	config_type;

	LX_DE_DISPLAY_DEVICE_T	display_type;
	LX_DE_DISPLAY_MIRROR_T display_mirror;
	LX_DE_FRC_PATH_T		frc_type;
	LX_DE_3D_CTRL_T			trid_type;

}	LX_DE_IF_CONFIG_T;

typedef enum
{
	LX_DE_SYS_STATUS_ALL,
	LX_DE_SYS_STATUS_DISPALY_DEVICE,
	LX_DE_SYS_STATUS_DISPALY_MIRROR,
	LX_DE_SYS_STATUS_FRC,
	LX_DE_SYS_STATUS_3D,
	LX_DE_SYS_STATUS_FC_MEM,
	LX_DE_SYS_STATUS_DISPALY_SIZE,
	LX_DE_SYS_STATUS_MAX
}	LX_DE_SYS_STATUS_CONFIG_T;

/*
 * default : DIS_DEV - LCD,  FRC Path - Internal, 3D ctrl -ON
 */
typedef	struct
{
	LX_DE_SYS_STATUS_CONFIG_T	status_type; //type

	LX_DE_DISPLAY_DEVICE_T	display_type;		///< display type
	LX_DE_DISPLAY_MIRROR_T 	display_mirror;		///< display mirror type
	LX_DE_FRC_PATH_T		frc_type;
	LX_DE_3D_CTRL_T			trid_type;
	UINT32 				 	fc_mem;		// DDR address for capture
	LX_DE_PANEL_TYPE_T 		display_size;		///< display size
}	LX_DE_SYS_STATUS_T;

typedef enum
{
	LX_DE_SRC_STATUS_ALL,
	LX_DE_SRC_STATUS_INPUT_SRC,
	LX_DE_SRC_STATUS_OPER,
	LX_DE_SRC_STATUS_SUB_OPER,
	LX_DE_SRC_STATUS_VDEC_INFO,
	LX_DE_SRC_STATUS_MAX
}	LX_DE_SRC_STATUS_CONFIG_T;

/*
 * default : DIS_DEV - LCD,  FRC Path - Internal, 3D ctrl -ON
 */
typedef	struct
{
	LX_DE_WIN_ID_T				win_id;

	LX_DE_SRC_STATUS_CONFIG_T	status_type;

	LX_DE_IN_SRC_T 				inSrc[2];		///< Input source type
	UINT32						inSrcPort[2];	///< Input port info (CVI_A,CVI_B, MVI_0,1,2,3)

	LX_DE_OPER_CONFIG_T		operType;
	LX_DE_SUB_OPER_CONFIG_T	subOperType;
	UINT16						operCtrlFlag;
	UINT16						subOperCtrlFlag;
	LX_DE_MPEG_TIMING_INFO_T vdecInfo;
}	LX_DE_SRC_STATUS_T;

/*
 * de Scaler Info type.
 */
typedef struct
{
	LX_DE_WIN_ID_T 				win_id;			///< De window index
	UINT16						width;			///< stride size
	UINT16						height;			///< stride size
	UINT32						stride;			///< stride size
	LX_DE_SCALER_CSAMPLE_T		sampling;		///< data format
	union
	{
		UINT8 						*p_y_frame;		///< y frame data start address
		UINT32						compat_p_y_frame;
		UINT64						sizer_p_y_frame;
	};
	union
	{
		UINT8 						*p_cbcr_frame;	///< cbcr frame data start address
		UINT32						compat_p_cbcr_frame;
		UINT64						sizer_p_cbcr_frame;
	};
}	LX_DE_SCALER_INFO_T;

typedef enum
{
	LX_DE_CVI_EXT_2D_FORMAT,				///< 2D format
	LX_DE_CVI_EXT_3D_FRAMEPACK,			///< 3D frame packing format
	LX_DE_CVI_EXT_3D_FIELD_ALTERNATIVE,	///< 3D field alternative format
	LX_DE_CVI_EXT_3D_LINE_ALTERNATIVE, 	///< 3D line alternative format(row interleaving)
	LX_DE_CVI_EXT_3D_SBSFULL,				///< 3D Side by Side Full format
	LX_DE_CVI_EXT_3D_L_DEPTH,			///< 3D L + Depth format
	LX_DE_CVI_EXT_3D_L_GRAPHICS,			///< 3D L + Depth + Graphics format
	LX_DE_CVI_EXT_3D_TNB,					///< 3D Top and Bottim format
	LX_DE_CVI_EXT_3D_SBS,					///< 3D Side by Side Half format
	LX_DE_CVI_EXT_4K_2K,					///< 4K x 2K format
	LX_DE_CVI_EXT_MAX						///< Ext format Max
} LX_DE_CVI_EXT_FORMAT_INFO_T;

/**
 * de cvi source attribute type.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T	   cvi_channel;		///< CVI channel A or B
	LX_DE_CVI_INPUT_SRC_T	   input_src;			///< cvi source type Information.
	LX_DE_CVI_DIMENSION_T	   size_offset;		///< h/v size offset
	LX_DE_SCAN_T			   scan;				///< interlaced or progressive
	LX_DE_CVI_EXT_FORMAT_INFO_T   extInfo;		///< extend format Information.
	LX_DE_CVI_SYNC_MODE_T	   de_mode;			///< internal data enable mode generated from sync(0) or de(1)
	LX_DE_COLOR_STD_T		   color;				///< color space 601,709,RGB
	LX_DE_CVD_COLOR_STD_T	   cvd_color_std;		///< CVD color mode
	LX_DE_CVI_YC_DELAY_T	   yc_delay;			///< CVD yc delay
	LX_DE_CVI_SAMPLING_MODE_T  sampling_rate;	///< external input sampling: noraml(0), double(1), quadrature(2)
	LX_DE_SCALER_CSAMPLE_T	   	sc_sample;		///< scaler sampling mode YUV420(0) YUV422(1) YUV444(2)
	UINT16						fir_c_enable;	///< c fir enable
}
LX_DE_CVI_SRC_T;

/**
 * de Debug argument for evaluation.
 */
typedef enum {
	LX_DE_EVAL_CMD_DBI,
	LX_DE_EVAL_CMD_MAX
}
LX_DE_EVAL_CMD_T;

typedef struct {
	int  argc __aligned(8);
	union
	{
		char **argv;
		UINT32 compat_argv;
		UINT64 sizer;
	};
}
LX_DE_EVAL_ARG_T;

typedef struct {
	LX_DE_EVAL_CMD_T cmd;
	LX_DE_EVAL_ARG_T arg;
	union
	{
		UINT32 *prm;
		UINT32 compat_prm;
		UINT64 sizer;
	};
	UINT32 size;
}
LX_DE_SET_EVAL_DBG_T;

//////////////////////////////////////////////////////////new

/**
 * de input source path parameter.
 */
typedef struct {
	LX_DE_WIN_ID_T		srcId;		///< Source index
	LX_DE_IN_SRC_T 		srcType;	///< Input source type
	UINT32				srcPort;	///< Input source port info
	UINT32				srcAttr;	///< Input source addribute
	UINT32				hdmiPort;	///< Input source hdmi port
} LX_DE_INPUT_SOURCE_T;

/**
 * de display device index.
 */
typedef enum {
	LX_DE_OUT_DEV_NONE,	///< Video To Display
	LX_DE_OUT_DEV_VTD,	///< Video To Display
	LX_DE_OUT_DEV_VTV,	///< Video To Venc
	LX_DE_OUT_DEV_VTC,	///< Video To Capture
	LX_DE_OUT_DEV_VTM,	///< Video To Memory
	LX_DE_OUT_DEV_VTS,	///< Video To Scart-Out
	LX_DE_OUT_DEV_MAX
} 	LX_DE_OUTPUT_DEVICE_T;

/**
 * de display device path parameter.
 */
typedef struct {
	LX_DE_WIN_ID_T			srcId;		///< Source index
	LX_DE_OUTPUT_DEVICE_T 	outDev;	    ///< output device type
	UINT16					devId;		///< device port info
} LX_DE_OUTPUT_MODE_T;

/**
 * de vt extention parameter which has the write-only property.
 */
typedef struct {
	LX_DE_LOCATION_T            location;   ///< capture location source(0)/display(0) [ro]
	LX_DE_RECT_T				crop_size;	///< source crop size infomation [wo]
	LX_DE_RECT_T				w_out_size; ///< window size infomation [wo]
	UINT32                      rate;       ///< frame rate [rw]
	UINT8               frz;        ///< flag of freeze(1) / release(0) [rw]
	UINT8               isSecure;        ///< secure(1) / non-secure(0)
	UINT8               frc_mode;   ///<  0 : auto, 1 : forced off
	UINT8               reserved;
} LX_DE_VT_EXTENTION_INFO_T;

#define MAX_VTG_BUFFER 5
/* New parameters for supporting VTM(Video To Memory)  */
/*
 * de Video To Memory type. - context of shared memory
 */
typedef struct
{
	LX_DE_WIN_ID_T              win_id;     ///< De window index  [rw]
	UINT32                      address;    ///< physical header address [rw]
	BOOLEAN                     enable;     ///< enable control [rw]
	UINT32                      rate;       ///< frame rate [rw]
	UINT8               frz;        ///< flag of freeze(1) / release(0) [rw]
	UINT8               isSecure;        ///< secure(1) / non-secure(0)
	UINT8               location;		/// <source(0) / display(1)
	UINT8               reserved;
	UINT32                      stride;     ///< stride size [ro]
	LX_DE_SCALER_CSAMPLE_T      sampling;   ///< data format [ro]
	UINT32                      y_frame[MAX_VTG_BUFFER]; ///< y frame data start address [ro] idx=0,1,2
	UINT32                      c_frame[MAX_VTG_BUFFER]; ///< cbcr frame data start address [ro] idx=0,1,2
	UINT32                      r_idx;      ///< read frame index [ro]
	UINT32                      mute;       ///< mute status [ro]
	LX_DE_RECT_T                srcSize;    ///< source size infomation [rw]
	LX_DE_RECT_T                winSize;    ///< window size infomation [rw]
	UINT16                      mirror;     ///< mirror info.
	UINT16                      scan;       ///< scan info.	[ro]
	SINT32                      mem_fd;	    ///< file descriptor for frame memory [rw]
#ifdef _USE_VT_EXTENTION_
	LX_DE_VT_EXTENTION_INFO_T   ext_info;   ///< extention parameter [wo]
#endif
} LX_DE_VTM_FRAME_INFO_T;

typedef struct
{
	LX_DE_WIN_ID_T              win_id;     ///< De window index  [rw]
	UINT32                      address;    ///< physical header address [rw]
	BOOLEAN                     enable;     ///< enable control [rw]
} LX_DE_VTG_INFO_T;


/**
 * de Video To Memory type. - check/update info to allow VTM function for each window.
 */
typedef struct {
	LX_DE_WIN_ID_T	win_id;			///< window index
	UINT32		cmd;			// 0:Get 1:Set
	UINT32		VTMBlock;		///< 1(VTM not allowed)
	UINT32		Reserved;
} LX_DE_VTM_BLOCK_STATE_T;


/**
 * de structures to support SW dolby HDR
 */
typedef struct
{
	UINT32		y_frame;
	UINT32		c_frame;
} LX_DE_FRAMEBUFFER_T;

typedef enum {
	LX_DE_BPP_8,
	LX_DE_BPP_10_PACKED,
	LX_DE_BPP_10_SPLIT,
	LX_DE_BPP_10_TUNNELED_PACKED,  // Tunneled RGB packed.
	LX_DE_BPP_10_TUNNELED_SPLIT,   // Tunneled RGB split, G plainer and RB plainer.
} LX_DE_BPP_TYPE_T;

typedef struct
{
	LX_DE_SCALER_CSAMPLE_T		sampling;
	LX_DE_BPP_TYPE_T		bitdepth;
	UINT32		stride;
	UINT32		width;
	UINT32		height;
	UINT32		PTS;
} LX_DE_FRAMEINFO_T;

typedef struct
{
	UINT32		address;
	BOOLEAN		enable;
	UINT32		mute;
	UINT32		r_idx;
	UINT32		rate;
	LX_DE_FRAMEINFO_T		bl_info[3];
	LX_DE_FRAMEINFO_T		el_info[3];
	LX_DE_FRAMEINFO_T		out_info[3];
	LX_DE_FRAMEBUFFER_T			bl_buf[3];
	LX_DE_FRAMEBUFFER_T			el_buf[3];
	LX_DE_FRAMEBUFFER_T			out_buf[3];

//	UINT32 out_lut[3];

	UINT32		pqe_meta_idx; //
	UINT32		reserved[ 2 ];
} LX_DE_DOLBYHDR_INFO_T;

typedef struct
{
	UINT32		address;
	BOOLEAN		enable;
	UINT32		mute;
	UINT32		r_idx;
	UINT32		rate;
	LX_DE_FRAMEINFO_T		bl_info[3];
	LX_DE_FRAMEINFO_T		el_info[3];
	LX_DE_FRAMEINFO_T		out_info[3];
	LX_DE_FRAMEBUFFER_T			bl_buf[3];
	LX_DE_FRAMEBUFFER_T			el_buf[3];
	LX_DE_FRAMEBUFFER_T			out_buf[3];

//	UINT32 out_lut[3];

	UINT32		pqe_meta_idx; //
	UINT16 		frz;
	UINT16		frz_idx;
	UINT16		reserved[2];
} LX_DE_GCP_INFO_T; // for General Capture Path


/**
 * de display device index.
 */
typedef enum {
	LX_DE_FREEZE_DISP,		///< Display
	LX_DE_FREEZE_INPUT,	///< Input
	LX_DE_FREEZE_SUB,		///< sub
	LX_DE_FREEZE_MAX
} 	LX_DE_FREEZE_LOCATION_T;

/**
 * de enable image freezing in each windows.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;			///< window index
	BOOLEAN bEnable;				///< freeze enable
	LX_DE_FREEZE_LOCATION_T location;	///< freeze location
} LX_DE_WIN_FREEZE_T;

/**
 * de enable source mirror mode in each windows.
 */
typedef struct {
	UINT8 srcPort;		///< vdec source port
	UINT8 destPort;		///< mirror port
	UINT8 enable;		///< mirror enable
} LX_DE_SRC_MIRROR_T;

/**
 * de active format detection control in external inputs.
 */
typedef enum
{
	LX_DE_SEAMLESS_OFF		,
	LX_DE_SEAMLESS_SIZE		,
	LX_DE_SEAMLESS_ROTATION	,  // for Airplay rotate (AVTASK-374, SCDCR-2583)
	LX_DE_SEAMLESS_MAX		,
} LX_DE_SEAMLESS_TYPE_T;

typedef union {
	UINT32 udata32;
	struct {
		LX_DE_SEAMLESS_TYPE_T enable     :16;	//15:0	///< active format detection enable
		LX_DE_WIN_ID_T win_id            :16;	//31:16	///< change format flag => window id (webos4.0)
	};
} LX_DE_ACT_FORMAT_T;

/**
 *  tag information to firmware.
 */
typedef struct {
	UINT32 system_info;     ///< 0xDECAFE00 + 1:ASIC,2:FPGA
	UINT32 firmware_base;   ///<
	UINT32 de_frame_base;   ///< O18 Y base (G bus)
	UINT32 de_grab_base;    ///<
	UINT32 de_prew_base;    ///<
	UINT32 be_frame_base;   ///<
	UINT32 de_shared_base;  ///<
	UINT32 de_frame_size;   ///< O18 Y size (G bus)
	UINT32 de_hdr_base;     ///<
	UINT32 de_bt_base;     ///<
	UINT32 de_vt_base;      ///<
	UINT32 de_prew_size;	///<

	// for O18
	UINT32 de_frame_baseC;   ///< O18 C base (E bus)
	UINT32 de_frame_sizeC;   ///< O18 C sieze (E bus)
	UINT32 de_prew_baseC;    ///<
	UINT32 de_bt_baseC;     ///<
	UINT32 de_vt_baseC;      ///<
} LX_DE_IPC_SYSTEM_T;


/**
*  tag information to firmware. for webos4.0 O18
*/
typedef struct {
	UINT32 base;
	UINT32 size;
} LX_DE_IPC_SYSTEM_MEM_T;

typedef enum
{
	LX_DE_IPC_SET_TYPE_CONSUMER,
	LX_DE_IPC_SET_TYPE_COMMERCIAL,
	LX_DE_IPC_SET_TYPE_SIGNAGE,
	LX_DE_IPC_SET_TYPE_MAX
} LX_DE_IPC_SET_TYPE_T;

typedef enum
{
	LX_DE_IPC_PANEL_TYPE_LCD,
	LX_DE_IPC_PANEL_TYPE_OLED,
	LX_DE_IPC_PANEL_TYPE_BOX,
	LX_DE_IPC_PANEL_TYPE_MAX
} LX_DE_IPC_PANEL_TYPE_T;

typedef enum
{
	LX_DE_IPC_PANEL_MAKER_LGD,
	LX_DE_IPC_PANEL_MAKER_SHARP,
	LX_DE_IPC_PANEL_MAKER_BOE,
	LX_DE_IPC_PANEL_MAKER_INNOLUX,
	LX_DE_IPC_PANEL_MAKER_MAX
} LX_DE_IPC_PANEL_MAKER_T;

typedef enum
{
	LX_DE_IPC_PANEL_RESOLUTION_3840x2160,
	LX_DE_IPC_PANEL_RESOLUTION_1920x1080,
	LX_DE_IPC_PANEL_RESOLUTION_1366x768,
	LX_DE_IPC_PANEL_RESOLUTION_1280x720,
	LX_DE_IPC_PANEL_RESOLUTION_720x480,
	LX_DE_IPC_PANEL_RESOLUTION_7680X4320,
	LX_DE_IPC_PANEL_RESOLUTION_MAX
} LX_DE_IPC_PANEL_RESOLUTION_T;

typedef enum
{
	LX_DE_IPC_PANEL_FRAME_RATE_120Hz,
	LX_DE_IPC_PANEL_FRAME_RATE_60Hz,
	LX_DE_IPC_PANEL_FRAME_RATE_60Hz_FIXED,
	LX_DE_IPC_PANEL_FRAME_RATE_144Hz,
	LX_DE_IPC_PANEL_FRAME_RATE_165Hz,
	LX_DE_IPC_PANEL_FRAME_RATE_240Hz,
	LX_DE_IPC_PANEL_FRAME_RATE_MAX
} LX_DE_IPC_PANEL_FRAME_RATE_T;

typedef enum
{
	LX_DE_IPC_PQE_OUT_BIT_10,
	LX_DE_IPC_PQE_OUT_BIT_11,
	LX_DE_IPC_PQE_OUT_BIT_12,
	LX_DE_IPC_PQE_OUT_BIT_13,
	LX_DE_IPC_PQE_OUT_BIT_MAX
} LX_DE_IPC_PQE_OUT_BIT_T;

typedef enum
{
	LX_DE_IPC_EXTERNAL_CHIP_NONE,
	LX_DE_IPC_EXTERNAL_CHIP_USE,
	LX_DE_IPC_EXTERNAL_CHIP_KLD,
	LX_DE_IPC_EXTERNAL_CHIP_MAX
} LX_DE_IPC_EXTERNAL_CHIP_T;

typedef enum
{
	LX_DE_IPC_TCON_SCRAMBLE_OFF = 0,
	LX_DE_IPC_TCON_SCRAMBLE_ON = 1
} LX_DE_IPC_TCON_SCRAMBLE_T;

typedef enum
{
	LX_DE_IPC_EXT_WIRELESS_CHIP_NONE = 0,
	LX_DE_IPC_EXT_WIRELESS_CHIP_USE = 1
} LX_DE_IPC_EXT_WIRELESS_CHIP_T;

typedef enum
{
	LX_DE_IPC_PANEL_CARRY_OVER_NOT,
	LX_DE_IPC_PANEL_CARRY_OVER,
	LX_DE_IPC_PANEL_CARRY_OVER_MAX
} LX_DE_IPC_PANEL_CARRY_OVER_T;

typedef enum
{
	LX_DE_IPC_PANEL_VX1_4BYTE = 0,
	LX_DE_IPC_PANEL_VX1_5BYTE = 1
} LX_DE_IPC_PANEL_VX1_BYTE_T;

typedef union {
	UINT32 u32Data;
	struct {
		LX_DE_IPC_PANEL_TYPE_T			panel_type			:3;	 // [2:0] panel type / 0:LCD, 1:OLED, 2:BOX
		LX_DE_IPC_SET_TYPE_T			set_type			:3;	 // [5:3] set type
		LX_DE_IPC_PANEL_MAKER_T			panel_maker			:3;  // [8:6] panel_maker
		LX_DE_IPC_PANEL_RESOLUTION_T	panel_resolution	:4;  // [12:9] panel_resolution
		UINT32                          panel_frame_rate	:2;	 // [14:13] panel_frame_rate
		LX_DE_IPC_EXTERNAL_CHIP_T		external_chip 		:2;  // [16:15] external_chip
		LX_DE_IPC_TCON_SCRAMBLE_T		tcon_Scramble		:1;  // [17] tcon_Scramble
		UINT32                          socts               :1;  // [18] socts mode
		UINT32                          reserved            :5;  // [23:19] RSVD
		UINT32                          panel_fr_option     :4;  // [27:24] panel_frame_rate option
		LX_DE_IPC_EXT_WIRELESS_CHIP_T	ext_wireless_chip	:1;	 // [28] external wireless chip
		LX_DE_IPC_PANEL_CARRY_OVER_T	panel_carry_over	:2;	 // [30:29] panel_carry_over
		LX_DE_IPC_PANEL_VX1_BYTE_T 		vx1_byte        	:1;  // [31] VX1_BYTE
	};
} LX_DE_IPC_SYSTEM_MODEL_T;

typedef union {
	UINT32 u32Data;
	struct {
		LX_DE_IPC_PANEL_FRAME_RATE_T	panel_frame_rate4	:4;  // [ 3: 0] panel_frame_rate
		LX_DE_IPC_PQE_OUT_BIT_T			pqe_out_bit			:4;  // [ 7: 4] pqe_out_bit
		UINT32                          oled_boost_x4		:1;  // [ 8: 8] oled_boost_x4
		UINT32                          reserved            :23; // [31: 9] RSVD
	};
} LX_DE_IPC_SYSTEM_MODEL1_T;

typedef struct {
	LX_DE_WIN_ID_T win_id;
	LX_DE_RECT_T rect;
	UINT32 delay; // (msec)
} LX_DE_VIDEO_DELAY_INFO_T;

typedef struct {
	LX_DE_VIDEO_DELAY_INFO_T owin_sync;
	LX_DE_VIDEO_DELAY_INFO_T win[LX_DE_WIN_MAX];
} LX_DE_VIDEO_DELAY_INFO_MEM_T;

typedef struct {
	UINT32 sys_time_diff;
	LX_DE_VIDEO_DELAY_INFO_T owin_sync;
	LX_DE_VIDEO_DELAY_INFO_T  video_delay_info[LX_DE_WIN_MAX];
} LX_DE_CB_INFO_T;

/* Do not edit */
typedef struct {
	LX_DE_IPC_SYSTEM_MEM_T     sys_time;      // [wo], 4 word (UINT32 sec,msec,usec, rsv)
	LX_DE_IPC_SYSTEM_MEM_T     sys_time_diff; // [ro], time diff
	LX_DE_IPC_SYSTEM_MEM_T     video_delay_info;   // [ro], UINT32 win_id, LX_DE_RECT_T rect, UINT32 delay(msec value)
	LX_DE_IPC_SYSTEM_MEM_T     de_gps; // [ro], GP-Scaler control
} FW_SHARED_MEM_INFO_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 asic            :4;   // [3:0] FPGA:2, ASIC:1
		UINT32 chip_version	   :4;   // [8:4] A0:0, B0:1
		UINT32 magic_word      :24;  // [31:9] 0xDECAFE
	};
} LX_DE_SYSTEM_VERSION_T;

typedef struct {
	LX_DE_IPC_SYSTEM_MEM_T     de_prew;
	LX_DE_IPC_SYSTEM_MEM_T     de_frm_m1;
	LX_DE_IPC_SYSTEM_MEM_T     de_frm_m2;
	LX_DE_IPC_SYSTEM_MEM_T     de_vt_m1;
	LX_DE_IPC_SYSTEM_MEM_T     de_vt_m2;
	LX_DE_IPC_SYSTEM_MEM_T     de_hdr;
	LX_DE_IPC_SYSTEM_MEM_T     vdec_pool_0;
	LX_DE_IPC_SYSTEM_MEM_T     vdec_pool_1;
	LX_DE_IPC_SYSTEM_MEM_T     de_gps;
	LX_DE_IPC_SYSTEM_MEM_T     de_gps_crc;
} LX_DE_MEM_SYS_INFO_T;

/***************************************************************/
/* !!!! Do not use (will be removed) !!!! */
/***************************************************************/
typedef struct {
	LX_DE_SYSTEM_VERSION_T      system_info; // 0xDECAFE00 + 1:ASIC,2:FPGA
	LX_DE_IPC_SYSTEM_MODEL_T  	model;		// STB, HD/FHD panel type info.
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu0;   // MCU0 firmware
	LX_DE_IPC_SYSTEM_MEM_T		de_prew;	// M0 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_frm_m1;	// M1 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_frm_m2;	// M2 BUS

	LX_DE_IPC_SYSTEM_MEM_T		de_bt_m1;	// M1 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_bt_m2;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_vt_m1;	// M1 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_vt_m2;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_hdr;		// dolby lut

	LX_DE_IPC_SYSTEM_MEM_T		be_fpp;		// M0 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_frc0;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_frc1;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_frc2;	// M1 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_wcg;   	// WCG LUT
	LX_DE_IPC_SYSTEM_MEM_T		fpp_info;   //
	LX_DE_IPC_SYSTEM_MEM_T		vdec_pool_0; // vdec dpb address
	LX_DE_IPC_SYSTEM_MEM_T		vdec_pool_1; // vdec dpb address

	FW_SHARED_MEM_INFO_T		shared_mem_info;	// video delay

	LX_DE_IPC_SYSTEM_MEM_T		pe_db; // tnr,scl,sr
	LX_DE_IPC_SYSTEM_MEM_T		pe_hdr; // hdr10

	LX_DE_IPC_SYSTEM_MEM_T		fw_dnn;    // fw dnn
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu1;   // MCU1 firmware(DNN-SR)
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu2;   // MCU2 firmware(IPU)(face detection)
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu3;   // MCU3 firmware(LNE)(2k to 4k)
	LX_DE_IPC_SYSTEM_MEM_T		fw_shared; // fw shared
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu4;   // MCU4 firmware(LNE)(4k to 4k)

	LX_DE_IPC_SYSTEM_MEM_T		be_led;   	// LED LUT
	LX_DE_IPC_SYSTEM_MEM_T		be_phdr;   	// post HDR/OLED data
	LX_DE_IPC_SYSTEM_MEM_T		be_chipinfo;// Chip Info

	LX_DE_IPC_SYSTEM_MEM_T		lne_pool; // lne
} LX_DE_IPC_SYSTEM_INFO_T;
/***************************************************************/

/**
 * window and hdmi link .
 */
typedef struct {
	LX_DE_WIN_ID_T		win_id;		///< window index
	UINT32              port_num;
} LX_DE_HDMIPORT_T;

/**
 * de vt capacity parameters.
 */
 typedef struct {
	LX_DE_RECT_T           maxResolution;
	UINT8                  bLeftTopAlign;
	UINT8                  bSupportInputVideoDeInterlacing;
	UINT8                  bSupportDisplayVideoDeInterlacing;
	UINT8                  bSupportScaleUp;
	UINT32                 scaleUpLimitWidth;
	UINT32                 scaleUpLimitHeight;
	UINT8                  bSupportScaleDown;
	UINT32                 scaleDownLimitWidth;
	UINT32                 scaleDownLimitHeight;
	UINT32                 locationLimit;  ///< 0:source only, 1:display only, 2: dual location
} LX_DE_VT_CAPA_PARAM_T;

/**
 * get the capacity of chip .
 */
typedef struct {
	UINT32                 chip_id;
	LX_DE_WIN_ID_T         max_win;		///< max window number for visible plane
	UINT32                 max_layer;      ///< max layer of z-order
	LX_DE_RECT_T           max_in_size;    ///< max size of input window
	LX_DE_RECT_T           max_out_size;	///< max size of output window
	UINT32                 max_in_fr_rate;
	UINT32                 max_out_fr_rate;
	UINT32                 mvir_start_num;
	LX_DE_3D_IMG_FMT_OUT_T default_3d_out_fmt;
	LX_DE_VT_CAPA_PARAM_T  vtm_capa;
	UINT32                 user_bin_num;//0 : not support user fwload, else : number
} LX_DE_CAPACITY_T;

/**
 * set sub window index.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;
} LX_DE_SET_SUB_WIN_T;

/**
 * set delay buffer.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;
	UINT32 ubuffer;
	UINT32 pool_base[2];
	UINT32 pool_size[2];
} LX_DE_SET_DELAY_BUFFER_T;

/**
 * set sub window type (PIP / PBP).
 */
typedef enum
{
	LX_DE_SUB_MODE_NONE,
	LX_DE_SUB_MODE_PIP,
	LX_DE_SUB_MODE_PBP,
	LX_DE_SUB_MODE_TWIN_OFF,
	LX_DE_SUB_MODE_HDR2SDR = LX_DE_SUB_MODE_TWIN_OFF,  // 3, HDR2SDR
	LX_DE_SUB_MODE_TWIN_ON,	 // PIP & Twin on

	LX_DE_SUB_MODE_LIVEZOOM,
	LX_DE_SUB_MODE_MAGZOOM,
	LX_DE_SUB_MODE_QUADWIN, // 7
	LX_DE_SUB_MODE_TRIWIN,

	LX_DE_SUB_MODE_OCCUPIED,// 9, for 4kHFR & 8k
	LX_DE_SUB_MODE_DUALMON, // 10

	LX_DE_SUB_MODE_QUADVID = 12,
	LX_DE_SUB_MODE_MAXN
} LX_DE_SUB_MODE_T;

/**
 * set sub window shape (CIRCLE / RECTANGLE).
 */
typedef enum
{
	LX_DE_MGF_TYPE_CIRCLE = 0,
	LX_DE_MGF_TYPE_RECTANGLE,
	LX_DE_MGF_TYPE_MAX = LX_DE_MGF_TYPE_RECTANGLE,
	LX_DE_MGF_TYPE_MAXN,
} LX_DE_SUB_MGF_SHAPE_T;

/**
 * set sub window info for  magnify mode.
 */
typedef struct {
	LX_DE_SUB_MGF_SHAPE_T sub_shape;
	LX_DE_RECT_T      org_win;
} LX_DE_SUB_SHAPE_T;

typedef enum {
	LX_DE_HDMITX_CLK_27M,
	LX_DE_HDMITX_CLK_74_25M,
	LX_DE_HDMITX_CLK_148_5M,
	LX_DE_HDMITX_CLK_297M,
	LX_DE_HDMITX_CLK_594M,
	LX_DE_HDMITX_CLK_MAX,
} LX_DE_HDMITX_CLK_T;

typedef struct {
	UINT32 width;
	UINT32 height;
	UINT32 frate;
}LX_DE_HDMITX_OUTPUT_INFO_T;

typedef struct {
	LX_DE_WIN_ID_T win_id;
	LX_DE_RECT_T inSize;
	LX_DE_RECT_T inWin;
}LX_DE_SOURCE_SIZE_WIN_T;

/*
 * HDR IPC mode enum
 */
typedef enum {
	LX_HDR_TYPE_OFF,// STD Buf Mode
	LX_HDR_TYPE_DOLBY,
	LX_HDR_TYPE_HDR10,
	LX_HDR_TYPE_TECHNICOLOR,
	LX_HDR_TYPE_SDR2HDR,
	LX_HDR_TYPE_HLG,// BBC, NHK  M17-B0
	LX_HDR_TYPE_DOLBY_LL,
	LX_HDR_TYPE_HDR2SDR,
	LX_HDR_TYPE_DOLBY_RF,
	LX_HDR_TYPE_MAX
}LX_HDR_MODE_T;

/*
 * Dolby features enum
 */
typedef enum {
	LX_DOVI_FEATURE_PD,// Precision detail feature
	LX_DOVI_FEATURE_MAX
}LX_DOVI_FEATURE_T;


/*
 * HDR IPC mode from where
 */
typedef enum {
	LX_HDR_MODE_FROM_SCL,
	LX_HDR_MODE_FROM_DOVI,
	LX_HDR_MODE_FROM_PQ,
	LX_HDR_MODE_FROM_DBG,
	LX_HDR_MODE_FROM_MAX
}LX_HDR_MODE_FROM_T;

/*
 * HDR_IPC_MODE
 */
typedef struct {
	UINT8 ucWinID;
	LX_HDR_MODE_T eIpcMode;
	LX_HDR_MODE_FROM_T eFrom;
}LX_DE_HDR_IPC_MODE_T;

/*
 * Dolby IPC Dolby Mode
 */
typedef struct {
	UINT8 ucWinID;
	LX_HDR_MODE_T eIpcMode;
	LX_HDR_MODE_FROM_T eFrom;
}LX_DOLBY_IOCTL_IPC_MODE_T;

/*
 * Dolby feature enable/disable IPC
 */
typedef struct {
	UINT8 ucWinID;
	UINT8 ucFlag; /* Enable:1 Disable:0 */
	LX_DOVI_FEATURE_T eDoviFeature;
}LX_DOLBY_IOCTL_IPC_FEATURE_T;

/**
 * hdr mode
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;
	LX_HDR_MODE_T hdr_mode;
}LX_DE_HDR_MODE_T;

/*
 * Dolby HDR mode
 */
typedef enum {
	LX_DOLBY_DEFAULT_MODE,
	LX_DOLBY_OTT_MODE,
	LX_DOLBY_RF_MODE,
	LX_DOLBY_HDMI_MODE,
	LX_DOLBY_HDMI_LL_MODE
}LX_DOLBY_MODE_T;

/*
 * Dolby HDR Register Map
 */
typedef struct {
	UINT32 unSize;
	UINT32 unHwAddr;
	volatile void *unPtrVirtAddr __aligned(8);
}LX_DOLBY_REG_MAP_T;

/*
 * * Dolby HDMI MD Descrambler MD type
 */
typedef enum {
	LX_DOLBY_HDMI_MDSW_DESC,
	LX_DOLBY_HDMI_MDHW_DESC,
	LX_DOLBY_HDMI_NOMD_DESC,
	LX_DOLBY_HDMI_DESC_MAX
}LX_DOLBY_HDMI_MDDESC_METHOD;
/**
 * Dolby HDR IP init
 */
typedef struct {
	LX_DOLBY_REG_MAP_T	sDoviOTTMDMap;
	LX_DOLBY_REG_MAP_T 	sDoviLUTMap; //3D,TC and GL LUT RAM base address [all will be consecutive]
	LX_DOLBY_REG_MAP_T 	sDoviRegMap; //DM and composer register RAM base address
	LX_DOLBY_REG_MAP_T	sSyncInfoMap; //Passing information about valid index between CPU and F/W
	LX_DOLBY_REG_MAP_T	sDoviDDRMap;
	LX_DOLBY_MODE_T	eCurMode;
	LX_DOLBY_HDMI_MDDESC_METHOD eHdmiDescMethod;
	UINT32 unHdmiYbuffer;
	UINT32 unHdmiUVbuffer;
	UINT32 reserved;
}LX_DOLBY_IO_MAP_T;//CR::change the name

/*
 * Dolby Ioctl Init Struture
 */
typedef struct {

	union
	{
		LX_DOLBY_IO_MAP_T *sptrDolbyInit;
		UINT32 compat_sptrDolbyInit;
		UINT64 sizer;
	};
	UINT8 ucWinID __aligned(8);
}LX_DOLBY_IOCTL_INIT_T;

typedef enum _E_DM_DATA_TYPE
{
	E_DM_BASE = 0, //only base, no extension
	E_DM_FULL_BE,  //Full metadata, big endian format
	E_DM_FULL_LE   //Full metadata little endian format
} LX_DOLBY_DM_MD_TYPE;

/*
 * Dolby HDR HDMI MetaData
 * Updated name to LX_DOLBY_DM_MD_T
 */
typedef struct {
	UINT32 usSize; //Return size will be in bytes
	UINT8 ucDMMetaData[MAX_DM_MD_SIZE];
}LX_DOLBY_DM_MD_T;

/*
 * Dolby HDR OTT MetaData
 * Updated name to LX_DOLBY_DM_OTT_MD_T
 */
typedef struct {
	UINT32 usSize; //Return size will be in bytes
	UINT8 ucDMMetaData[MAX_DM_OTT_MD_SIZE];
}LX_DOLBY_DM_OTT_MD_T;
/*
 * Dolby HDMI MetaData IOCTL struct
 */
typedef struct {
	union
	{
		LX_DOLBY_DM_MD_TYPE *eMDType;
		UINT32 compat_eMDType;
		UINT64 sizer_eMDType;
	};
	union
	{
		LX_DOLBY_DM_MD_T *sptrMetadata;
		UINT32 compat_sptrMetadata;
		UINT64 sizer_sptrMetadata;
	};
	UINT8	ucWinID __aligned(8);
}LX_DOLBY_IOCTL_HDMI_MD_T;

/*
 *Dolby HDR OTT MetaData
 * Updated name to LX_DOLBY_OTT_MD_T
 */
typedef struct {
	union
	{
		UINT32 *nptrInfo;
		UINT32 compat_nptrInfo;
		UINT64 sizer;
	};
	UINT8 ucWinID __aligned(8);
}LX_DOLBY_OTT_MD_IOCTL_T;

/*
 * Dolby HDR Composer & DM change
 */
typedef enum {
	LX_DOLBY_NO_CHNAGE,
	LX_DOLBY_COMP_CHANGE,
	LX_DOLBY_DM_CHANGE,
	LX_DOLBY_COMP_DM_CHANGE
}LX_DOLBY_COMP_DM_CHANGE_T;

#if 1
/*
 * Dolby HDR Composer Register Map
 * CR:: Need to include from dolby spec api header file
 */
typedef struct {
	UINT32 Composer_Mode;
	UINT32 VDR_Resolution;
	UINT32 Bit_Depth;
	UINT32 Coefficient_Log2_Denominator;
	UINT32 BL_Num_Pivots_Y;
	UINT32 BL_Pivot[5];
	UINT32 BL_Order;
	UINT32 BL_Coefficient_Y[8][3];
	UINT32 EL_NLQ_Offset_Y;
	UINT32 EL_Coefficient_Y[3];
	UINT32 Mapping_IDC_U;
	UINT32 BL_Num_Pivots_U;
	UINT32 BL_Pivot_U[3];
	UINT32 BL_Order_U;
	UINT32 BL_Coefficient_U[4][3];
	UINT32 MMR_Coefficient_U[22][2];
	UINT32 MMR_Order_U;
	UINT32 EL_NLQ_Offset_U;
	UINT32 EL_Coefficient_U[3];
	UINT32 Mapping_IDC_V;
	UINT32 BL_Num_Pivots_V;
	UINT32 BL_Pivot_V[3];
	UINT32 BL_Order_V;
	UINT32 BL_Coefficient_V[4][3];
	UINT32 MMR_Coefficient_V[22][2];
	UINT32 MMR_Order_V;
	UINT32 EL_NLQ_Offset_V;
	UINT32 EL_Coefficient_V[3];
}LX_DOLBY_COMP_REG_T;

/*
 * Dolby HDR DM Register Map
 */
typedef struct {
#if 0
    UINT32 IP_Version;                    /**< @brief Address 0x00 */
    UINT32 Control;                       /**< @brief Address 0x04 */
    UINT32 Metadata_Program_Start;        /**< @brief Address 0x08 */
    UINT32 Metadata_Program_Finish;       /**< @brief Address 0x0C */
    UINT32 Interrupt_Raw;                 /**< @brief Address 0x10 */
    UINT32 Interrupt_Enable;              /**< @brief Address 0x14 */
#endif
	UINT32 SRange;
	UINT32 Srange_Inverse;
	UINT32 Frame_Format_1;
	UINT32 Frame_Format_2;
	UINT32 Frame_Pixel_Def;
	UINT32 Y2RGB_Coefficient_1;
	UINT32 Y2RGB_Coefficient_2;
	UINT32 Y2RGB_Coefficient_3;
	UINT32 Y2RGB_Coefficient_4;
	UINT32 Y2RGB_Coefficient_5;
	UINT32 Y2RGB_Offset_1;
	UINT32 Y2RGB_Offset_2;
	UINT32 Y2RGB_Offset_3;
	UINT32 EOTF;
	UINT32 Sparam_1;
	UINT32 Sparam_2;
	UINT32 Sgamma;
	UINT32 A2B_Coefficient_1;
	UINT32 A2B_Coefficient_2;
	UINT32 A2B_Coefficient_3;
	UINT32 A2B_Coefficient_4;
	UINT32 A2B_Coefficient_5;
	UINT32 C2D_Coefficient_1;
	UINT32 C2D_Coefficient_2;
	UINT32 C2D_Coefficient_3;
	UINT32 C2D_Coefficient_4;
	UINT32 C2D_Coefficient_5;
	UINT32 C2D_Offset;
	UINT32 Chroma_Weight;
	UINT32 mFilter_Scale;
	UINT32 msWeight;
	UINT32 Hunt_Value;
	UINT32 Saturation_Gain;
	UINT32 Min_C_1;
	UINT32 Min_C_2;
	UINT32 Max_C;
	UINT32 C1_Inverse;
	UINT32 C2_Inverse;
	UINT32 C3_Inverse;
	UINT32 pixDef;
	UINT32 Active_area_left_top;
	UINT32 Active_area_bottom_right;
}LX_DOLBY_DM_REG_T;

/** @brief Composer and DM registers for IPCORE */
typedef struct
{
#if 0
    UINT32 IP_Version;                    /**< @brief Address 0x00 */
    UINT32 Control;                       /**< @brief Address 0x04 */
    UINT32 Metadata_Program_Start;        /**< @brief Address 0x08 */
    UINT32 Metadata_Program_Finish;       /**< @brief Address 0x0C */
    UINT32 Interrupt_Raw;                 /**< @brief Address 0x10 */
    UINT32 Interrupt_Enable;              /**< @brief Address 0x14 */
#endif
    UINT32 SRange;                        /**< @brief Address 0x18 */
    UINT32 Srange_Inverse;                /**< @brief Address 0x1C */
    UINT32 Frame_Format_1;                /**< @brief Address 0x20 */
    UINT32 Frame_Format_2;                /**< @brief Address 0x24 */
    UINT32 Frame_Pixel_Def;               /**< @brief Address 0x28 */
    UINT32 Y2RGB_Coefficient_1;           /**< @brief Address 0x2C */
    UINT32 Y2RGB_Coefficient_2;           /**< @brief Address 0x30 */
    UINT32 Y2RGB_Coefficient_3;           /**< @brief Address 0x34 */
    UINT32 Y2RGB_Coefficient_4;           /**< @brief Address 0x38 */
    UINT32 Y2RGB_Coefficient_5;           /**< @brief Address 0x3C */
    UINT32 Y2RGB_Offset_1;                /**< @brief Address 0x40 */
    UINT32 Y2RGB_Offset_2;                /**< @brief Address 0x44 */
    UINT32 Y2RGB_Offset_3;                /**< @brief Address 0x48 */
    UINT32 EOTF;                          /**< @brief Address 0x4C */
    UINT32 Sparam_1;                      /**< @brief Address 0x50 */
    UINT32 Sparam_2;                      /**< @brief Address 0x54 */
    UINT32 Sgamma;                        /**< @brief Address 0x58 */
    UINT32 A2B_Coefficient_1;             /**< @brief Address 0x5C */
    UINT32 A2B_Coefficient_2;             /**< @brief Address 0x60 */
    UINT32 A2B_Coefficient_3;             /**< @brief Address 0x64 */
    UINT32 A2B_Coefficient_4;             /**< @brief Address 0x68 */
    UINT32 A2B_Coefficient_5;             /**< @brief Address 0x6C */
    UINT32 C2D_Coefficient_1;             /**< @brief Address 0x70 */
    UINT32 C2D_Coefficient_2;             /**< @brief Address 0x74 */
    UINT32 C2D_Coefficient_3;             /**< @brief Address 0x78 */
    UINT32 C2D_Coefficient_4;             /**< @brief Address 0x7C */
    UINT32 C2D_Coefficient_5;             /**< @brief Address 0x80 */
    UINT32 C2D_Offset;                    /**< @brief Address 0x84 */
    UINT32 Chroma_Weight;                 /**< @brief Address 0x88 */
    UINT32 mFilter_Scale;                 /**< @brief Address 0x8C */
    UINT32 msWeight;                      /**< @brief Address 0x90 */
    UINT32 Hunt_Value;                    /**< @brief Address 0x94 */
    UINT32 Saturation_Gain;               /**< @brief Address 0x98 */
    UINT32 Min_C_1;                       /**< @brief Address 0x9C */
    UINT32 Min_C_2;                       /**< @brief Address 0xA0 */
    UINT32 Max_C;                         /**< @brief Address 0xA4 */
    UINT32 C1_Inverse;                    /**< @brief Address 0xA8 */
    UINT32 C2_Inverse;                    /**< @brief Address 0xAC */
    UINT32 C3_Inverse;                    /**< @brief Address 0xB0 */
    UINT32 pixDef;                        /**< @brief Address 0xB4 */
    UINT32 reserved_dm[4];                /**< @brief Address 0xB8-0xC4 */
    UINT32 Composer_Mode;                 /**< @brief Address 0xC8 */
    UINT32 VDR_Resolution;                /**< @brief Address 0xCC */
    UINT32 Bit_Depth;                     /**< @brief Address 0xD0 */
    UINT32 Coefficient_Log2_Denominator;  /**< @brief Address 0xD4 */
    UINT32 BL_Num_Pivots_Y;               /**< @brief Address 0xD8 */
    UINT32 BL_Pivot[5];                   /**< @brief Address 0xDC-0xEC */
    UINT32 BL_Order;                      /**< @brief Address 0xF0 */
    UINT32 BL_Coefficient_Y[8][3];        /**< @brief Address 0xF4-0x150 */
    UINT32 EL_NLQ_Offset_Y;               /**< @brief Address 0x154 */
    UINT32 EL_Coefficient_Y[3];           /**< @brief Address 0x158-0x160 */
    UINT32 Mapping_IDC_U;                 /**< @brief Address 0x164 */
    UINT32 BL_Num_Pivots_U;               /**< @brief Address 0x168 */
    UINT32 BL_Pivot_U[3];                 /**< @brief Address 0x16C-0x174 */
    UINT32 BL_Order_U;                    /**< @brief Address 0x178 */
    UINT32 BL_Coefficient_U[4][3];        /**< @brief Address 0x17C-0x1A8 */
    UINT32 MMR_Coefficient_U[22][2];      /**< @brief Address 0x1AC-0x258 */
    UINT32 MMR_Order_U;                   /**< @brief Address 0x25C */
    UINT32 EL_NLQ_Offset_U;               /**< @brief Address 0x260 */
    UINT32 EL_Coefficient_U[3];           /**< @brief Address 0x264-0x26C */
    UINT32 Mapping_IDC_V;                 /**< @brief Address 0x270 */
    UINT32 BL_Num_Pivots_V;               /**< @brief Address 0x274 */
    UINT32 BL_Pivot_V[3];                 /**< @brief Address 0x278-0x280 */
    UINT32 BL_Order_V;                    /**< @brief Address 0x284 */
    UINT32 BL_Coefficient_V[4][3];        /**< @brief Address 0x288-0x2B4 */
    UINT32 MMR_Coefficient_V[22][2];      /**< @brief Address 0x2B8-0x364 */
    UINT32 MMR_Order_V;                   /**< @brief Address 0x368 */
    UINT32 EL_NLQ_Offset_V;               /**< @brief Address 0x36C */
    UINT32 EL_Coefficient_V[3];           /**< @brief Address 0x370-0x378 */
    UINT32 reserved_comp[8];              /**< @brief Address 0x37C-0x398 */
    UINT32 reserved_diag[11];             /**< @brief Diagnostic registers Not written by control path Address 0x39C-0x3C4 */
    UINT32 reserved_ipcore[2];            /**< @brief Address 0x3C8-0x3CC */
    UINT32 Active_area_top_left_Slice_0;      /**< @brief Address 0x3D0  */
    UINT32 Active_area_bottom_right_Slice_0;  /**< @brief Address 0x3D4  */
    UINT32 Active_area_top_left_Slice_1;      /**< @brief Address 0x3D8  */
    UINT32 Active_area_bottom_right_Slice_1;  /**< @brief Address 0x3DC  */
    UINT32 Active_area_top_left_Slice_2;      /**< @brief Address 0x3E0  */
    UINT32 Active_area_bottom_right_Slice_2;  /**< @brief Address 0x3E4  */
    UINT32 Active_area_top_left_Slice_3;      /**< @brief Address 0x3E8  */
    UINT32 Active_area_bottom_right_Slice_3;  /**< @brief Address 0x3EC  */
}  LX_DOLBY_IP_REG_T;
#ifdef HDR_HW5_SUPPORT
typedef struct register_comp_s
{
    UINT32 LOG2_COEF;
    UINT32 BL_PIV_NUM_Y;
    UINT32 BL_PIV_Y[5];
    UINT32 BL_ORDER_Y;
    UINT32 BL_COEF_Y[8][3];
    UINT32 MAP_IDC_U;
    UINT32 BL_PIV_NUM_U;
    UINT32 BL_PIV_U[3];
    UINT32 BL_ORDER_U;
    UINT32 BL_COEF_U[4][3];
    UINT32 MMR_COEF_U[22][2];
    UINT32 MMR_ORDER_U;
    UINT32 MAP_IDC_V;
    UINT32 BL_PIV_NUM_V;
    UINT32 BL_PIV_V[3];
    UINT32 BL_ORDER_V;
    UINT32 BL_COEF_V[4][3];
    UINT32 MMR_COEF_V[22][2];
    UINT32 MMR_ORDER_V;
} register_comp_t;
#define IPCORE_VERSION_MAJOR 5
#define IPCORE_VERSION_MINOR 1

/** @brief Composer and DM registers for IPCORE */
typedef struct register_ipcore1_s
{
#if 1
    UINT32 IP_VER;                   /* 0X000 */
    UINT32 CNTRL;                    /* 0X004 */
    UINT32 MD_PGM_START;             /* 0X008 */
    UINT32 MD_PGM_FIN;               /* 0X00C */
    UINT32 INT_RAW;                  /* 0X010 */
    UINT32 INT_EN;                   /* 0X014 */
#endif
    UINT32 SRANGE;                   /* 0X018 */
    UINT32 SRANGE_INV;               /* 0X01C */
    UINT32 Y2RGB_COEF[5];            /* 0X020 - 0X030 */
    UINT32 Y2RGB_OFF[3];             /* 0X034 - 0X03C */
    UINT32 EOTF_A_VALUE;             /* 0X040 */
    UINT32 EOTF_B_VALUE;             /* 0X044 */
    UINT32 EOTF_GAMMA;               /* 0X048 */
    UINT32 CLR_SP;                   /* 0X04C */
    UINT32 EOTF_BETA_1;              /* 0X050 */
    UINT32 R2LMS_COEF[5];            /* 0X054 - 0X064 */
    UINT32 R2RGB_COEF[5];            /* 0X068 - 0X078 */
    UINT32 L2IPT_COEF[2];            /* 0X07C - 0X080 */
    UINT32 LMAX_VALUE;               /* 0X084 */
    UINT32 CLAMP_MIN_VALUE;          /* 0X088 */
    UINT32 CLAMP_MAX_VALUE;          /* 0X08C */
    UINT32 MD_SCALE_REG;             /* 0X090 */
    UINT32 VDR_RES;                  /* 0X094 */
    UINT32 BIT_DEPTH;                /* 0X098 */
    register_comp_t comp;              /* 0X09C - 0X310 */
    UINT32 INP_FRM_ST;               /* 0X314 */
    UINT32 OP_FRM_ST;                /* 0X318 */
    UINT32 CRC_CNTRL;                /* 0X31C */
    UINT32 INP_FRM_CRC;              /* 0X320 */
    UINT32 COMP_OP_FRM_CRC;          /* 0X324 */
    UINT32 OP_INT_FRM_CRC;           /* 0X328 */
    UINT32 ICSC_LUT_CRC;             /* 0X32C */
    UINT32 L1_MINMAX;                /* 0X330 */
    UINT32 L1_MID_L4_STD;            /* 0X334 */
    UINT32 DEBUG_LUT_CNTRL_REG;      /* 0X338 */
    UINT32 ICSCLUT_RDADDR;           /* 0X33C */
    UINT32 ICSCLUT_RDDATA;           /* 0X340 */
} LX_DOLBY_O22_IP_CORE1_REG_T;

typedef struct register_ipcore1b_s
{
    UINT32 IP_VER;                   /* 0X000 */
    UINT32 CNTRL;                    /* 0X004 */
    UINT32 MD_PGM_START;             /* 0X008 */
    UINT32 MD_PGM_FIN;               /* 0X00C */
    UINT32 INT_RAW;                  /* 0X010 */
    UINT32 INT_EN;                   /* 0X014 */
    UINT32 VDR_RES;                  /* 0X018 */
    UINT32 INP_FRM_ST;               /* 0X01C */
    UINT32 RESERVED;                 /* 0X020 */
    UINT32 CRC_CNTRL;                /* 0X024 */
    UINT32 INP_FRM_CRC;              /* 0X028 */
} LX_DOLBY_O22_IP_CORE1B_REG_T;

typedef struct register_ipcore2_s
{
#if 1
    UINT32 IP_VER;                   /* 0X000 */
    UINT32 CNTRL;                    /* 0X004 */
    UINT32 MD_PGM_START;             /* 0X008 */
    UINT32 MD_PGM_FIN;               /* 0X00C */
    UINT32 INT_RAW;                  /* 0X010 */
    UINT32 INT_EN;                   /* 0X014 */
#endif
    UINT32 SRANGE;                   /* 0X018 */
    UINT32 SRANGE_INV;               /* 0X01C */
    UINT32 Y2RGB_COEF[5];            /* 0X020 - 0X030 */
    UINT32 Y2RGB_OFF[3];             /* 0X034 - 0X03C */
    UINT32 EOTF_A_VALUE;             /* 0X040 */
    UINT32 EOTF_B_VALUE;             /* 0X044 */
    UINT32 EOTF_GAMMA;               /* 0X048 */
    UINT32 LMAX_VALUE;               /* 0X04C */
    UINT32 CLAMP_MIN_VALUE;          /* 0X050 */
    UINT32 CLAMP_MAX_VALUE;          /* 0X054 */
    UINT32 CLR_SP;                   /* 0X058 */
    UINT32 EOTF_BETA_1;              /* 0X05C */
    UINT32 R2LMS_COEF[5];            /* 0X060 - 0X070 */
    UINT32 LMS2IPT_COEF[5];          /* 0X074 - 0X084 */
    UINT32 PREMAP_A;                 /* 0X088 */
    UINT32 PREMAP_B;                 /* 0X08C */
    UINT32 POSTMAP_A;                /* 0X090 */
    UINT32 POSTMAP_B;                /* 0X094 */
    UINT32 LIN_OFFSET[3];            /* 0X098 - 0X0A0 */
    UINT32 L2NLLUT_SCALE;            /* 0X0A4 */
    UINT32 LMIN_T;                   /* 0X0A8 */
    UINT32 LMAX_T;                   /* 0X0AC */
    UINT32 TRANGE_REG;               /* 0X0B0 */
    UINT32 TRANGE_OVER_ONE;          /* 0X0B4 */
    UINT32 TGAMMA_REG;               /* 0X0B8 */
    UINT32 CHR_UP_420_422_COEF[2];   /* 0X0BC - 0X0C0 */
    UINT32 IPT2LMS_COEF[5];          /* 0X0C4 - 0X0D4 */
    UINT32 LMS2RGB_COEF[5];          /* 0X0D8 - 0X0E8 */
    UINT32 RGB2YUV_COEF[5];          /* 0X0EC - 0X0FC */
    UINT32 RGB2YUV_OFFSET[3];        /* 0X100 - 0X108 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 L1L4_RGB2RGB_COEF[5];     /* 0X10C - 0X11C */
    UINT32 L1L4_SCALE_REG;           /* 0X120 */
    UINT32 ICSC_BYPASS_PATH_REG[3];  /* 0X124 - 0X12C */
    UINT32 OCSC_RGB2RGB_COEF[5];     /* 0X130 - 0X140 */
    UINT32 OCSC_RGB2RGB_MIN;         /* 0X144 */
    UINT32 OCSC_RGB2RGB_MAX;         /* 0X148 */
#endif
    UINT32 CVM_CONTROL_REGISTER;     /* 0X14C */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 CVM_SUBTYPE1_SCALE_REG[2]; /* 0X150 - 0X154 */
#endif
    UINT32 tmin_pq;                  /* 0X158 */
    UINT32 tmax_pq;                  /* 0X15C */
    UINT32 ROI_Y1_Y2[5];             /* 0X160 - 0X170 */
    UINT32 ROI_X1_X2_S0[5];          /* 0X174 - 0X184 */
    UINT32 ROI_X1_X2_S1[5];          /* 0X188 - 0X198 */
    UINT32 ROI_X1_X2_S2[5];          /* 0X19C - 0X1AC */
    UINT32 ROI_X1_X2_S3[5];          /* 0X1B0 - 0X1C0 */
    UINT32 TMI_DYNA_SMIN;            /* 0X1C4 */
    UINT32 TMI_DYNA_SMAX;            /* 0X1C8 */
    UINT32 TMI_DYNA_SMID;            /* 0X1CC */
    UINT32 TMI_DYNA_TMIN;            /* 0X1D0 */
    UINT32 TMI_DYNA_TMAX;            /* 0X1D4 */
    UINT32 TMI_DYNA_TMID;            /* 0X1D8 */
    UINT32 TMI_DYNA_SLOPE_MIN;       /* 0X1DC */
    UINT32 TMI_DYNA_SLOP_MINSCALE;   /* 0X1E0 */
    UINT32 TMI_DYNA_SLOPE_MAX;       /* 0X1E4 */
    UINT32 TMI_DYNA_SLOPE_MAXSCALE;  /* 0X1E8 */
    UINT32 TMI_DYNA_SLOPE_MID;       /* 0X1EC */
    UINT32 TMI_DYNA_SLOPE_MIDSCALE;  /* 0X1F0 */
    UINT32 TMI_DYNA_C2L;             /* 0X1F4 */
    UINT32 TMI_DYNA_C2LSCALE;        /* 0X1F8 */
    UINT32 TMI_DYNA_C3L;             /* 0X1FC */
    UINT32 TMI_DYNA_C3LSCALE;        /* 0X200 */
    UINT32 TMI_DYNA_C2U;             /* 0X204 */
    UINT32 TMI_DYNA_C2USCALE;        /* 0X208 */
    UINT32 TMI_DYNA_C3U;             /* 0X20C */
    UINT32 TMI_DYNA_C3USCALE;        /* 0X210 */
    UINT32 TMI_STAT_SMIN;            /* 0X214 */
    UINT32 TMI_STAT_SMAX;            /* 0X218 */
    UINT32 TMI_STAT_SMID;            /* 0X21C */
    UINT32 TMI_STAT_TMIN;            /* 0X220 */
    UINT32 TMI_STAT_TMAX;            /* 0X224 */
    UINT32 TMI_STAT_TMID;            /* 0X228 */
    UINT32 TMI_STAT_SLOPE_MIN;       /* 0X22C */
    UINT32 TMI_STAT_SLOP_MINSCALE;   /* 0X230 */
    UINT32 TMI_STAT_SLOPE_MAX;       /* 0X234 */
    UINT32 TMI_STAT_SLOPE_MAXSCALE;  /* 0X238 */
    UINT32 TMI_STAT_SLOPE_MID;       /* 0X23C */
    UINT32 TMI_STAT_SLOPE_MIDSCALE;  /* 0X240 */
    UINT32 TMI_STAT_C2L;             /* 0X244 */
    UINT32 TMI_STAT_C2LSCALE;        /* 0X248 */
    UINT32 TMI_STAT_C3L;             /* 0X24C */
    UINT32 TMI_STAT_C3LSCALE;        /* 0X250 */
    UINT32 TMI_STAT_C2U;             /* 0X254 */
    UINT32 TMI_STAT_C2USCALE;        /* 0X258 */
    UINT32 TMI_STAT_C3U;             /* 0X25C */
    UINT32 TMI_STAT_C3USCALE;        /* 0X260 */
    UINT32 LOCAL_MAP_STRENGTH;       /* 0X264 */
    UINT32 SHARPENING_FACTOR;        /* 0X268 */
    UINT32 TRIM_SLOPE;               /* 0X26C */
    UINT32 TRIM_OFFSET;              /* 0X270 */
    UINT32 TRIM_POWER;               /* 0X274 */
    UINT32 TRIM_A;                   /* 0X278 */
    UINT32 TRIM_B;                   /* 0X27C */
    UINT32 SATURATION_GAIN;          /* 0X280 */
    UINT32 SMI_A;                    /* 0X284 */
    UINT32 SMI_ASCALE;               /* 0X288 */
    UINT32 SMI_B;                    /* 0X28C */
    UINT32 SMI_BSCALE;               /* 0X290 */
    UINT32 SMI_C;                    /* 0X294 */
    UINT32 SMI_CSCALE;               /* 0X298 */
    UINT32 ANGLE_XMIN;               /* 0X29C */
    UINT32 V7_ANGX[7];               /* 0X2A0 - 0X2B8 */
    UINT32 V7_SAT[7];                /* 0X2BC - 0X2D4 */
    UINT32 V7_ROT[7];                /* 0X2D8 - 0X2F0 */
    UINT32 DENOM[6];                 /* 0X2F4 - 0X308 */
    UINT32 RESERVED;                 /* 0X30C */
    UINT32 TMINMAX_PQINV_LO;         /* 0X310 */
    UINT32 TMINMAX_PQINV_HI;         /* 0X314 */
    UINT32 AMBIENT_COMP_PQ;          /* 0X318 */
    UINT32 AMBIENT_COMP_MIN;         /* 0X31C */
    UINT32 TAI_NORM_SMAX;            /* 0X320 */
    UINT32 TAI_NORM_SMID;            /* 0X324 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 TAI_NORM_SMIN;            /* 0X328 */
#endif
    UINT32 TAI_NORM_TMIN;            /* 0X32C */
    UINT32 TAI_NORM_TMID;            /* 0X330 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR == 0)
    UINT32 TAI_NORM_SLOPE;           /* 0X330 */
    UINT32 TAI_NORM_SLOPE_SCALE;     /* 0X334 */
#endif
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 TAI_NORM_TMAX;            /* 0X334 */
    UINT32 TAI_NORM_SLOPE_MIN;       /* 0X338 */
    UINT32 TAI_NORM_SLOPE_MINSCALE;  /* 0X33C */
    UINT32 TAI_NORM_SLOPE_MID;       /* 0X340 */
    UINT32 TAI_NORM_SLOPE_MIDSCALE;  /* 0X344 */
    UINT32 TAI_NORM_SLOPE_MAX;       /* 0X348 */
    UINT32 TAI_NORM_SLOPE_MAXSCALE;  /* 0X34C */
#endif
    UINT32 TAI_NORM_C2L;             /* 0X350 */
    UINT32 TAI_NORM_C2LSCALE;        /* 0X354 */
    UINT32 TAI_NORM_C3L;             /* 0X358 */
    UINT32 TAI_NORM_C3LSCALE;        /* 0X35C */
    UINT32 TAI_NORM_C2U;             /* 0X360 */
    UINT32 TAI_NORM_C2USCALE;        /* 0X364 */
    UINT32 TAI_NORM_C3U;             /* 0X368 */
    UINT32 TAI_NORM_C3USCALE;        /* 0X36C */
    UINT32 DM3_rolloff;              /* 0X370 */
    UINT32 DM3_SoR;                  /* 0X374 */
    UINT32 DM3_SoRscale;             /* 0X378 */
    UINT32 DM3_c[3];                 /* 0X37C - 0X384 */
    UINT32 DM3_scale_c1c2;           /* 0X388 */
    UINT32 DM3_scale_c3;             /* 0X38C */
    UINT32 SCI_DYNA_a;               /* 0X390 */
    UINT32 SCI_DYNA_b;               /* 0X394 */
    UINT32 SCI_DYNA_c;               /* 0X398 */
    UINT32 SCI_DYNA_d;               /* 0X39C */
    UINT32 SCI_DYNA_e;               /* 0X3A0 */
    UINT32 SCI_DYNA_scale_ab;        /* 0X3A4 */
    UINT32 SCI_DYNA_scale_cd;        /* 0X3A8 */
    UINT32 SCI_DYNA_scale_e;         /* 0X3AC */
    UINT32 SCI_STAT_a;               /* 0X3B0 */
    UINT32 SCI_STAT_b;               /* 0X3B4 */
    UINT32 SCI_STAT_c;               /* 0X3B8 */
    UINT32 SCI_STAT_d;               /* 0X3BC */
    UINT32 SCI_STAT_e;               /* 0X3C0 */
    UINT32 SCI_STAT_scale_ab;        /* 0X3C4 */
    UINT32 SCI_STAT_scale_cd;        /* 0X3C8 */
    UINT32 SCI_STAT_scale_e;         /* 0X3CC */
    UINT32 TMS_DYNA_a;               /* 0X3D0 */
    UINT32 TMS_DYNA_b;               /* 0X3D4 */
    UINT32 TMS_DYNA_c;               /* 0X3D8 */
    UINT32 TMS_DYNA_LB;              /* 0X3DC */
    UINT32 TMS_DYNA_UB;              /* 0X3E0 */
    UINT32 TMS_DYNA_scale_ab;        /* 0X3E4 */
    UINT32 TMS_DYNA_scale_c;         /* 0X3E8 */
    UINT32 TMS_DYNA_scale_lbub;      /* 0X3EC */
    UINT32 TMS_STAT_a;               /* 0X3F0 */
    UINT32 TMS_STAT_b;               /* 0X3F4 */
    UINT32 TMS_STAT_c;               /* 0X3F8 */
    UINT32 TMS_STAT_lb;              /* 0X3FC */
    UINT32 TMS_STAT_ub;              /* 0X400 */
    UINT32 TMS_STAT_scale_ab;        /* 0X404 */
    UINT32 TMS_STAT_scale_c;         /* 0X408 */
    UINT32 TMS_STAT_scale_lbub;      /* 0X40C */
    UINT32 SMS_DYNA_a;               /* 0X410 */
    UINT32 SMS_DYNA_b;               /* 0X414 */
    UINT32 SMS_DYNA_LB;              /* 0X418 */
    UINT32 SMS_DYNA_UB;              /* 0X41C */
    UINT32 SMS_DYNA_scale_ab;        /* 0X420 */
    UINT32 SMS_DYNA_scale_lbub;      /* 0X424 */
    UINT32 SMS_STAT_a;               /* 0X428 */
    UINT32 SMS_STAT_b;               /* 0X42C */
    UINT32 SMS_STAT_lb;              /* 0X430 */
    UINT32 SMS_STAT_ub;              /* 0X434 */
    UINT32 SMS_STAT_scale_ab;        /* 0X438 */
    UINT32 SMS_STAT_scale_lbub;      /* 0X43C */
    UINT32 PYR1_EDGE_WT01;           /* 0X440 */
    UINT32 PYR2_EDGE_WT01;           /* 0X444 */
    UINT32 PYR3_EDGE_WT01;           /* 0X448 */
    UINT32 PYR4_EDGE_WT01;           /* 0X44C */
    UINT32 PYR5_EDGE_WT01;           /* 0X450 */
    UINT32 PYR6_EDGE_WT01;           /* 0X454 */
    UINT32 PYR7_EDGE_WT01;           /* 0X458 */
    UINT32 FLT_IMG_RES;              /* 0X45C */
    UINT32 VDR_RES;                  /* 0X460 */
    UINT32 BIT_DEPTH;                /* 0X464 */
    register_comp_t comp;              /* 0X468 - 0X6DC */
    UINT32 RAW_METADATA_LENGTH;      /* 0X6E0 */
    UINT32 RAW_METADATA[128];        /* 0X6E4 - 0X8E0 */
    UINT32 INP_FRM_ST;               /* 0X8E4 */
    UINT32 OP_FRM_ST;                /* 0X8E8 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 L1_MINMAX;                /* 0X8EC */
    UINT32 L1_MID_L4_STD;            /* 0X8F0 */
#endif
    UINT32 CRC_CNTRL;                /* 0X8F4 */
    UINT32 INP_FRM_CRC;              /* 0X8F8 */
    UINT32 COMP_OP_FRM_CRC;          /* 0X8FC */
    UINT32 OP_FRM_CRC;               /* 0X900 */
    UINT32 UPSCL_OP_FRM_CRC;         /* 0X904 */
    UINT32 ICSC_LUT_CRC;             /* 0X908 */
    UINT32 OCSC_LUT_CRC;             /* 0X90C */
    UINT32 CVM_TAILUT_CRC;           /* 0X910 */
    UINT32 CVM_SMILUT_CRC;           /* 0X914 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 CVM_LITE_TMILUT_CRC;      /* 0X918 */
    UINT32 CVM_LITE_SMILUT_CRC;      /* 0X91C */
    UINT32 CVM_LITE_TMSLUT_CRC;      /* 0X920 */
    UINT32 CVM_LITE_SMSLUT_CRC;      /* 0X924 */
    UINT32 CVM_LITE_TMI2LUT_CRC;     /* 0X928 */
    UINT32 CVM_LITE_SMI2LUT_CRC;     /* 0X92C */
    UINT32 CVM_LITE_TMS2LUT_CRC;     /* 0X930 */
    UINT32 CVM_LITE_SMS2LUT_CRC;     /* 0X934 */
#endif
    UINT32 DEBUG_LUT_CNTRL_REG;      /* 0X938 */
    UINT32 CVM_TAILUT_RDADDR;        /* 0X93C */
    UINT32 CVM_SMILUT_RDADDR;        /* 0X940 */
    UINT32 ICSCLUT_RDADDR;           /* 0X944 */
    UINT32 OCSCLUT_RDADDR;           /* 0X948 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 CVM_LITE_TMILUT_RDADDR;   /* 0X94C */
    UINT32 CVM_LITE_SMILUT_RDADDR;   /* 0X950 */
    UINT32 CVM_LITE_TMSLUT_RDADDR;   /* 0X954 */
    UINT32 CVM_LITE_SMSLUT_RDADDR;   /* 0X958 */
    UINT32 CVM_LITE_TMI2LUT_RDADDR;  /* 0X95C */
    UINT32 CVM_LITE_SMI2LUT_RDADDR;  /* 0X960 */
    UINT32 CVM_LITE_TMS2LUT_RDADDR;  /* 0X964 */
    UINT32 CVM_LITE_SMS2LUT_RDADDR;  /* 0X968 */
#endif
    UINT32 CVM_TAILUT_RDDATA;        /* 0X96C */
    UINT32 CVM_SMILUT_RDDATA;        /* 0X970 */
    UINT32 ICSCLUT_RDDATA;           /* 0X974 */
    UINT32 OCSCLUT_RDDATA;           /* 0X978 */
#if (IPCORE_VERSION_MAJOR == 5) && (IPCORE_VERSION_MINOR > 0)
    UINT32 CVM_LITE_TMILUT_RDDATA;   /* 0X97C */
    UINT32 CVM_LITE_SMILUT_RDDATA;   /* 0X980 */
    UINT32 CVM_LITE_TMSLUT_RDDATA;   /* 0X984 */
    UINT32 CVM_LITE_SMSLUT_RDDATA;   /* 0X988 */
    UINT32 CVM_LITE_TMI2LUT_RDDATA;  /* 0X98C */
    UINT32 CVM_LITE_SMI2LUT_RDDATA;  /* 0X990 */
    UINT32 CVM_LITE_TMS2LUT_RDDATA;  /* 0X994 */
    UINT32 CVM_LITE_SMS2LUT_RDDATA;  /* 0X998 */
#endif
} LX_DOLBY_O22_IP_CORE2_REG_T;
#endif
/*
 * Dolby HDR Composer & DM configiuratio
 */
typedef struct {
	LX_DOLBY_IP_REG_T sDoviIPReg;
	LX_DOLBY_COMP_REG_T sCompRegMap;
	LX_DOLBY_DM_REG_T sDMRegMap;
	LX_DOLBY_COMP_DM_CHANGE_T eCompDMChange;
}LX_DOLBY_CONFIG_REG_T;
/*
 * dolby Composer & DM ioctl struct
 */
typedef struct {
	LX_DOLBY_CONFIG_REG_T *sDolbyConfig __aligned(8);
	UINT8 ucWinID __aligned(8);
}LX_DOLBY_IOCTL_CONFIG_REG_T;
#else
/** @brief Composer and DM registers for IPCORE */
typedef struct
{
#if 0
    UINT32 IP_Version;                    /**< @brief Address 0x00 */
    UINT32 Control;                       /**< @brief Address 0x04 */
    UINT32 Metadata_Program_Start;        /**< @brief Address 0x08 */
    UINT32 Metadata_Program_Finish;       /**< @brief Address 0x0C */
    UINT32 Interrupt_Raw;                 /**< @brief Address 0x10 */
    UINT32 Interrupt_Enable;              /**< @brief Address 0x14 */
#endif
    UINT32 SRange;                        /**< @brief Address 0x18 */
    UINT32 Srange_Inverse;                /**< @brief Address 0x1C */
    UINT32 Frame_Format_1;                /**< @brief Address 0x20 */
    UINT32 Frame_Format_2;                /**< @brief Address 0x24 */
    UINT32 Frame_Pixel_Def;               /**< @brief Address 0x28 */
    UINT32 Y2RGB_Coefficient_1;           /**< @brief Address 0x2C */
    UINT32 Y2RGB_Coefficient_2;           /**< @brief Address 0x30 */
    UINT32 Y2RGB_Coefficient_3;           /**< @brief Address 0x34 */
    UINT32 Y2RGB_Coefficient_4;           /**< @brief Address 0x38 */
    UINT32 Y2RGB_Coefficient_5;           /**< @brief Address 0x3C */
    UINT32 Y2RGB_Offset_1;                /**< @brief Address 0x40 */
    UINT32 Y2RGB_Offset_2;                /**< @brief Address 0x44 */
    UINT32 Y2RGB_Offset_3;                /**< @brief Address 0x48 */
    UINT32 EOTF;                          /**< @brief Address 0x4C */
    UINT32 Sparam_1;                      /**< @brief Address 0x50 */
    UINT32 Sparam_2;                      /**< @brief Address 0x54 */
    UINT32 Sgamma;                        /**< @brief Address 0x58 */
    UINT32 A2B_Coefficient_1;             /**< @brief Address 0x5C */
    UINT32 A2B_Coefficient_2;             /**< @brief Address 0x60 */
    UINT32 A2B_Coefficient_3;             /**< @brief Address 0x64 */
    UINT32 A2B_Coefficient_4;             /**< @brief Address 0x68 */
    UINT32 A2B_Coefficient_5;             /**< @brief Address 0x6C */
    UINT32 C2D_Coefficient_1;             /**< @brief Address 0x70 */
    UINT32 C2D_Coefficient_2;             /**< @brief Address 0x74 */
    UINT32 C2D_Coefficient_3;             /**< @brief Address 0x78 */
    UINT32 C2D_Coefficient_4;             /**< @brief Address 0x7C */
    UINT32 C2D_Coefficient_5;             /**< @brief Address 0x80 */
    UINT32 C2D_Offset;                    /**< @brief Address 0x84 */
    UINT32 Chroma_Weight;                 /**< @brief Address 0x88 */
    UINT32 mFilter_Scale;                 /**< @brief Address 0x8C */
    UINT32 msWeight;                      /**< @brief Address 0x90 */
    UINT32 Hunt_Value;                    /**< @brief Address 0x94 */
    UINT32 Saturation_Gain;               /**< @brief Address 0x98 */
    UINT32 Min_C_1;                       /**< @brief Address 0x9C */
    UINT32 Min_C_2;                       /**< @brief Address 0xA0 */
    UINT32 Max_C;                         /**< @brief Address 0xA4 */
    UINT32 C1_Inverse;                    /**< @brief Address 0xA8 */
    UINT32 C2_Inverse;                    /**< @brief Address 0xAC */
    UINT32 C3_Inverse;                    /**< @brief Address 0xB0 */
    UINT32 pixDef;                        /**< @brief Address 0xB4 */
    #if DTV_IP_CORE_VERSION == 2
    UINT32 reserved_dm[4];                /**< @brief Address 0xB8-0xC4 */
    #else
    UINT32 Active_area_top_left;          /**< @brief Address 0xB8 */
    UINT32 Active_area_bottom_right;      /**< @brief Address 0xBC */
    UINT32 reserved_dm[2];                /**< @brief Address 0xC0-0xC4 */
    #endif
    UINT32 Composer_Mode;                 /**< @brief Address 0xC8 */
    UINT32 VDR_Resolution;                /**< @brief Address 0xCC */
    UINT32 Bit_Depth;                     /**< @brief Address 0xD0 */
    UINT32 Coefficient_Log2_Denominator;  /**< @brief Address 0xD4 */
    UINT32 BL_Num_Pivots_Y;               /**< @brief Address 0xD8 */
    UINT32 BL_Pivot[5];                   /**< @brief Address 0xDC-0xEC */
    UINT32 BL_Order;                      /**< @brief Address 0xF0 */
    UINT32 BL_Coefficient_Y[8][3];        /**< @brief Address 0xF4-0x150 */
    UINT32 EL_NLQ_Offset_Y;               /**< @brief Address 0x154 */
    UINT32 EL_Coefficient_Y[3];           /**< @brief Address 0x158-0x160 */
    UINT32 Mapping_IDC_U;                 /**< @brief Address 0x164 */
    UINT32 BL_Num_Pivots_U;               /**< @brief Address 0x168 */
    UINT32 BL_Pivot_U[3];                 /**< @brief Address 0x16C-0x174 */
    UINT32 BL_Order_U;                    /**< @brief Address 0x178 */
    UINT32 BL_Coefficient_U[4][3];        /**< @brief Address 0x17C-0x1A8 */
    UINT32 MMR_Coefficient_U[22][2];      /**< @brief Address 0x1AC-0x258 */
    UINT32 MMR_Order_U;                   /**< @brief Address 0x25C */
    UINT32 EL_NLQ_Offset_U;               /**< @brief Address 0x260 */
    UINT32 EL_Coefficient_U[3];           /**< @brief Address 0x264-0x26C */
    UINT32 Mapping_IDC_V;                 /**< @brief Address 0x270 */
    UINT32 BL_Num_Pivots_V;               /**< @brief Address 0x274 */
    UINT32 BL_Pivot_V[3];                 /**< @brief Address 0x278-0x280 */
    UINT32 BL_Order_V;                    /**< @brief Address 0x284 */
    UINT32 BL_Coefficient_V[4][3];        /**< @brief Address 0x288-0x2B4 */
    UINT32 MMR_Coefficient_V[22][2];      /**< @brief Address 0x2B8-0x364 */
    UINT32 MMR_Order_V;                   /**< @brief Address 0x368 */
    UINT32 EL_NLQ_Offset_V;               /**< @brief Address 0x36C */
    UINT32 EL_Coefficient_V[3];           /**< @brief Address 0x370-0x378 */
    UINT32 reserved_comp[8];              /**< @brief Address 0x37C-0x398 */
    #if DTV_IP_CORE_VERSION == 2
    UINT32 reserved_diag[11];             /**< @brief Diagnostic registers
                                                        Not written by control path
                                                        Address 0x39C-0x3C4 */
    UINT32 reserved_ipcore[2];            /**< @brief Address 0x3C8-0x3CC */
    UINT32 Active_area_top_left_Slice_0;      /**< @brief Address 0x3D0  */
    UINT32 Active_area_bottom_right_Slice_0;  /**< @brief Address 0x3D4  */
    UINT32 Active_area_top_left_Slice_1;      /**< @brief Address 0x3D8  */
    UINT32 Active_area_bottom_right_Slice_1;  /**< @brief Address 0x3DC  */
    UINT32 Active_area_top_left_Slice_2;      /**< @brief Address 0x3E0  */
    UINT32 Active_area_bottom_right_Slice_2;  /**< @brief Address 0x3E4  */
    UINT32 Active_area_top_left_Slice_3;      /**< @brief Address 0x3E8  */
    UINT32 Active_area_bottom_right_Slice_3;  /**< @brief Address 0x3EC  */
    #endif
}  LX_DOLBY_IP_REG_T;

/*
 * Dolby HDR Composer & DM configiuratio
 */
typedef struct {
	LX_DOLBY_IP_REG_T sDoviIPReg;
	LX_DOLBY_COMP_DM_CHANGE_T eCompDMChange;
}LX_DOLBY_CONFIG_REG_T;

/*
 * dolby Composer & DM ioctl struct
 */
typedef struct {
	LX_DOLBY_CONFIG_REG_T *sDolbyConfig __aligned(8);
	UINT8 ucWinID __aligned(8);
}LX_DOLBY_IOCTL_CONFIG_REG_T;

#endif
/*
 * Dolby HDR LUT config
 */
typedef struct {
	UINT32 unFrameNum;
	UINT8 ucWinID;
}LX_DOLBY_IOCTL_CONFIG_LUT_T;

/*
 * Dolby OTT MetaData Type from MCU
 */
typedef enum
{
	LX_IPC_TYPE_END,
	LX_IPC_TYPE_DOVI_PTS,
	LX_IPC_TYPE_DOVE_META_COMP,
	LX_IPC_TYPE_DOVI_META_DM,
}LX_IPC_TYPE_T;

/*
 * Dolby OTT MetaData from MCU
 */
typedef struct
{
	LX_IPC_TYPE_T eIpcType;
	UINT32 unSize;
	UINT8 ucData[0];
}LX_DOLBY_OTT_MD_DATA_T;

/*
 * HW block giving Dolby HDMI Metadata
 */
typedef enum
{
	E_MD_HDR_HDMI_HW,
	E_MD_IPP_M0,
	E_MD_PATH_MAX
}LX_HDR_HDMI_MD_PATH_T;

typedef struct {
	LX_HDR_HDMI_MD_PATH_T e_md_path;
	UINT8 ucWinID;
}LX_DOLBY_IOCTL_MD_PATH_T;


/*
 * rotation info from platform
 */
typedef enum {
     LX_DE_ROTATE_0,
     LX_DE_ROTATE_90,
     LX_DE_ROTATE_180,
     LX_DE_ROTATE_270,
     LX_DE_ROTATE_HFLIP,
     LX_DE_ROTATE_VFLIP,
     LX_DE_ROTATE_THROUGH,
     LX_DE_ROTATE_MAX
} LX_DE_ROTATE_INFO_T;

typedef struct {
	UINT32 onfoff;
	UINT32 dbg_control;
	LX_DE_RECT_T dbg_rect;
}LX_DE_NETWORK_SYNC_T;

/*
* Rotate, source size, input/output window from platform
*/
typedef struct {
	LX_DE_WIN_ID_T wId;
	LX_DE_ROTATE_INFO_T rot : 16;
	UINT16 resize_ani_flag : 16;
	LX_DE_RECT_T in_size;
	LX_DE_RECT_T in_win;
	LX_DE_RECT_T out_win;
} LX_DE_WIN_INFO_T;

/*
 * vdec ipc
 */
typedef union {
	UINT32 udata32;
	struct {						//0xC8026200
	UINT32 frame_idx						:8; //7:0	//frame index,
	UINT32 resvd0							:2;
	UINT32 dpb_map_type 					:4; //13:10 //0 : Raster map, 1 : HEVC Packed UD, 5 : G1 Decoder 8x4, 11 : AV1
	UINT32 resvd1							:1;
	UINT32 smart_balancing_en				:1; //15 //1: Smart Balancing Enable, 0 : Disable
	UINT32 smart_balancing_mode 			:2; //17:16 //0: 1:1 Mode	1: 1:3 Mode 2: 3:1 Mode
	UINT32 vdisp_instance_number		:5; //22:18
	UINT32 film_grain_synthesis 	:1; //23	BODP film grain mode
	UINT32 chroma_sample_position		:3; //26:24 //0: type0, 1: type1, 2: type2, 3: type3, 4: type4, 5: type5, 7: invalid
	UINT32 resvd2							:1; //
	UINT32 active_format_desc				:4; //31:28 //active_format_desc // 0:invalid, 1~f: MPEG2/H.264 AFD

	};
}REG_VDO_IPC_FRAME_IDX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC8026208
	UINT32 frame_rate_residual                :16;	//15:0	//frame rate residual
	UINT32 frame_rate_div                     :16;	//31:16	//frame rate division
	};
}REG_VDO_IPC_FRAME_RATE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC8026210
	UINT32 height                           :16;	//15:0	//Picture Height
	UINT32 width                            :16;	//31:16	//Picture Width
	};
}REG_VDO_IPC_PICTURE_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC8026204
	UINT32 display_mode                     :2;	//1:0	//Display Mode	01 : Top Field Display	10 : Bottom Field Dipslay	11 : Frame Display
	UINT32 resvd0                           :1;
	UINT32 vdec_paused                      :1;	//3 //
	UINT32 color_sample                     :2;	//5:4	//for MJPEG
	UINT32 hevc_bit_mode                    :2;	//7:6	//0 : 8bit, 1 : 10 bit
	UINT32 initial_frame                    :1;	//8
	UINT32 underrun                         :2;	//9:10
	UINT32 flush                            :1;	//11
	UINT32 scan_inform_n                    :4;	//15:12
	UINT32 rotation_inform					:2; // Rotation angle information, 00 : 0¡Æ,01 : 90¡Æ,10 : 180¡Æ,11 : 270¡Æ(-90¡Æ)
	UINT32 resvd1                           :12;
	UINT32 low_delay_mode                   :1; //30	// low delay mode(camera, widi, miracast, cloud game) (0 : nomal mode 1 : low delay mode)
	UINT32 svp                              :1; //31    // svp mode bit 0 : non-svp, 1 : svp
	};
}REG_VDO_IPC_DISPLAY_INFO_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 par_height         :16;   // 15:0 pixel aspect ratio of height
	UINT32 par_width          :16;   // 31:16	//pixel aspect ratio of width
	};
} REG_VDO_IPC_PIXEL_ASPECT_RATIO_T;

typedef union {
        UINT32 udata32;
        struct {                                                //0xCC0A0038
        UINT32 sei_fpa                          :8;        //7:0        //3D SEI
        UINT32 lr_order                         :2;        //9:8        //0: right, 1: left, 2: none
        UINT32 resvd                            :22;
        };
}REG_VDO_IPC_FRAME_PACK_ARRANGE_T;


typedef struct {
	REG_VDO_IPC_FRAME_IDX_T    frame_idx         ;	// 0x00
	REG_VDO_IPC_DISPLAY_INFO_T display_info      ;	// 0x04
	REG_VDO_IPC_FRAME_RATE_T   frame_rate        ;	// 0x08
	UINT32 aspect_ratio      ;	// 0x0c
	REG_VDO_IPC_PICTURE_SIZE_T picture_size      ;	// 0x10
	UINT32 h_offset          ;	// 0x14
	UINT32 v_offset          ;	// 0x18
	UINT32 update            ;	// 0x1c
	UINT32 y_frame_base      ;	// 0x20
	UINT32 c_frame_base      ;	// 0x24
	UINT32 y_frame_offset    ;	// 0x28
	UINT32 c_frame_offset    ;	// 0x2c
	UINT32 stride            ;	// 0x30
	//UINT32 pixel_aspect_ratio;	// 0x34
	REG_VDO_IPC_PIXEL_ASPECT_RATIO_T par;	//0x34
	REG_VDO_IPC_FRAME_PACK_ARRANGE_T frame_pack_arrange;	// 0x38
	UINT32 pts_info          ;	// 0x3c
} LX_DE_VDEC_IPC_REG_T;

/*
* GP-Scaler control
*/
typedef struct {
	UINT32 enable;
	UINT32 gps_id;
	UINT32 vdec_id;
	UINT32 shared_mem_base;
	UINT32 width;
	UINT32 height;
	UINT32 buffer_addr_y[3];
	UINT32 buffer_addr_c[3];
	UINT32 buf_idx;
	UINT32 stride; // y stride
	UINT32 max_w;
	UINT32 max_h;
	UINT32 bbd_id;
	UINT32 bbd_en;
	UINT32 bbd_xw;
	UINT32 bbd_yh;
	UINT32 pix_fmt;   // ===> 0:420, 1:422, 2:ARGB, 3:ABGR, 4:RGBA
	UINT32 pix_alp;   // ===> user alpha
	UINT32 src_attr;      // source attribute (0:none, 1:interlace, 2:mjpeg)
} LX_DE_GPS_CTRL_T;


// gps-dma api
typedef union {
   UINT32 udata32;
   struct {
     UINT32 dpb_map_type : 4;
     UINT32 bpp          : 2;
     LX_DE_SCAN_T 	scan		 : 1;
     UINT32 		fieldId		 : 1;
	 UINT32 cs           :2;
     UINT32 rsvd         : 22;
   };
} WEBCODEC_IPC_DPB_INFO_T;

typedef struct {
    // destination
    int dst;     // 0:external buffer(from vdec), 1:internal buffer(venc buffer)
    // dpb_address
    UINT32 dpb_y_frame_base;
    UINT32 dpb_c_frame_base;
    // dpb_size
    UINT32 dpb_width;
    UINT32 dpb_height;
    // dpb_type
    WEBCODEC_IPC_DPB_INFO_T dpb_type;
    // target address
    UINT32 out_y_frame_base;
    UINT32 out_c_frame_base;
    // target size
    UINT32 out_width;
    UINT32 out_height;

    UINT32 crc_y_base;
    UINT32 crc_c_base;
    UINT32 crc_mode;
} LX_DE_GPSDMA_IPC_T;

typedef struct {
	struct source_frame_info src_info;
	struct target_frame_info dst_info;
}
LX_DE_GPSDMA_PARAM_T;

typedef struct {
	LX_DE_WIN_ID_T wId;
	UINT32              type; // 0:window, 1:move
	LX_DE_RECT_T 		osd_input;
	LX_DE_RECT_T 		video_input;
	LX_DE_RECT_T 		osd_output;
	LX_DE_RECT_T 		video_output;
} LX_DE_ORBIT_T;


typedef union {
	UINT32 udata32;
	struct {      //0xC902E328 RW 0x0000_0000
		UINT32 video_delay	 :20; //(19:0) measured video delay (us resolution)
		UINT32 reserved         :2;  //(21:20)
		UINT32 pic_init         :1;  //(22)  auto/fast pic init
		UINT32 vrr              :1;  //(23)  vrr/gsync/freesync on/off
		UINT32 justscan         :1;  //(24)  justscan on/off
		UINT32 frc              :1;  //(25)  frn on/off
		UINT32 frame_delay      :2;  //(27:26) frame buffer delay (DE_IPC_SET_FRAME_DELAY)
		UINT32 prew             :1;  //(28)  IPP pre-write on/off
		UINT32 skip_nd0         :1;  //(29)  skipND0 on/off
		UINT32 low_delay        :1;  //(30)  low delay on/off
		UINT32 dco_lock         :1;  //(31)  DCO lock status
	};
}REG_CCO0_VERI_SYS_VERI_10_T;

typedef union {
	UINT32 udata32;
	struct {      //0xC902E32C RW 0x0000_0000
		UINT32 frate_in        :8;  //(7:0)  input frame rate
		UINT32 frate_out       :8;  //(15:8) output frame rate
		UINT32 frate_vrr					 :16; //(31:16) vrr input frame rate
	};
}REG_CCO0_VERI_SYS_VERI_11_T;

typedef struct {
	REG_CCO0_VERI_SYS_VERI_10_T reg_0;
	REG_CCO0_VERI_SYS_VERI_11_T reg_1;
} LX_DE_FW_STATUS_REG_T;

typedef struct {
	int  cfg;
	int  state;//-1:ng,0:ok,1:busy
	int  size;
	union
	{
		char *cmd;
		UINT32 compat_cmd;
		UINT64 sizer;
	};
} LX_DE_TEST_CMD_T;

#define _GET_DE_IOCTL_TYPE(CMD) (_IOC_NR(CMD))

typedef struct {
	UINT32 magic;
	LX_DE_VDEC_IPC_REG_T mvi[8];
} LX_DE_DDR_MVI_T;

typedef union {
	UINT32 u32;
	struct {
	UINT32 idx_num    :3; //[ 2:0] idx_num(1~7)
	UINT32 reserved0  :28;//[30:3] reserved0
	UINT32 magic      :1; //[31] magic bit(backward compatibility)
	};
} LX_DE_IPC_INIT_HEAD_T;

typedef struct {
	LX_DE_IPC_INIT_HEAD_T head;
	struct {
		UINT32 data;
		UINT32 size;
	} u[7];
} LX_DE_IPC_INIT_DATA_T;

/*
 * de-interlace scan mode enum
 */
typedef enum {
     LX_DE_SCAN_MODE_FIELD_MERGE,
     LX_DE_SCAN_MODE_LINE_DOUBLER,
     LX_DE_SCAN_MODE_INTER_FIELD,
     LX_DE_SCAN_MODE_MAX
} LX_DE_SCAN_MODE_TYPE_T;

typedef struct {
	LX_DE_WIN_ID_T wId;
	LX_DE_SCAN_MODE_TYPE_T scan_mode;
} LX_DE_SCAN_MODE_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_DRV_H_ */

/** @} */
