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
 *	OVI module control Drivers linux module
 *
 *  author     dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/interrupt.h>
#include <linux/seq_file.h>

#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hal.h"
#include "m17/ovi/ovi_hw_m17.h"
#include "o18/ovi/ovi_hw_o18.h"
#include "m19/ovi/ovi_hw_m19.h"
#include "o20/ovi/ovi_hw_o20.h"
#include "e60/ovi/ovi_hw_e60.h"
#include "o22/ovi/ovi_hw_o22.h"
#include "m23/ovi/ovi_hw_m23.h"
#include "o24/ovi/ovi_hw_o24.h"
#include "o26/ovi/ovi_hw_o26.h"

// Add here for register header file
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* SCDCR-4006 */
#define OVI_HAL_PM_INFO(_level,_type,_result)	\
	do {\
		pr_info("LowPower::%s::video::ovi0::0::%s-%s::%s::%s::ovi\n",\
			_level,current->group_leader->comm,current->comm,_type,_result);\
	} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int (*pfnOviHwPreInitialize)(void);
	int (*pfnOviHwInitialize)(void);
	int (*pfnOviHwClose)(void);
	int (*pfnOviHwSuspend)(void);
	int (*pfnOviHwEarlyResume)(void);
	int (*pfnOviHwResume)(void);

	int (*pfnOviHwSetDisplayOption)(LX_OVI_DISPLAY_INFO_T *pstParams);
	int (*pfnOviHwSetBypass)(LX_OVI_TCON_BYPASS_T *pstParams);
	int (*pfnOviHwSetCombination)(UINT32 param);
	int (*pfnOviHwSetSpreadSpectrum)(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
	int (*pfnOviHwSetMcuCommand)(LX_OVI_TCON_MCU_CMD_T *pstParams);
	int (*pfnOviHwUpdateFirmware)(LX_OVI_TCON_FW_DWLD_T *pstParams);
	int (*pfnOviHwGetFirmwareVersion)(LX_OVI_TCON_FW_VER_T *pstParams);
	int (*pfnOviHwSetOdLut)(LX_OVI_TCON_OD_DWLD_T *pstParams);
	int (*pfnOviHwSetLodLut)(LX_OVI_TCON_OD_DWLD_T *pstParams);
	int (*pfnOviHwSetPodLut)(LX_OVI_TCON_OD_DWLD_T *pstParams);
	int (*pfnOviHwSetFrameOdcEnable)(BOOLEAN bParam);
	int (*pfnOviHwSetColorTempEnable)(BOOLEAN bParam);
	int (*pfnOviHwSetGammaEnable)(BOOLEAN bParam);
	int (*pfnOviHwSetDitherEnable)(BOOLEAN bParam);
	int (*pfnOviHwSetLineOdcMode)(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
	int (*pfnOviHwSetDitherMode)(LX_OVI_TCON_DITHER_T enParam);
	int (*pfnOviHwSetColorTemp)(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
	int (*pfnOviHwSetMultiWindowGamut)(LX_OVI_MULTIWIN_GAMUT_T *pstParams);
	int (*pfnOviHwGetMultiWindowGamut)(LX_OVI_MULTIWIN_GAMUT_T *pstParams);
	int (*pfnOviHwSetGamma)(LX_OVI_TCON_GAMMA_T *pstParams);
	int (*pfnOviHwSetGammaRGBW)(LX_OVI_TCON_GAMMA_RGBW_T *pstParams);
	int (*pfnOviHwGetOdLut)(LX_OVI_TCON_OD_DWLD_T *pstParams);
	int (*pfnOviHwSetMleMode)(LX_OVI_TCON_MLE_MODE_T enParam);
	int (*pfnOviHwSetTscic)(LX_OVI_TCON_TSCIC_T *pstParams);
	int (*pfnOviHwSetDemura)(LX_OVI_TCON_DEMURA_T *pstParams);
	int (*pfnOviHwSetTconHReverse)(BOOLEAN bParam);
	int (*pfnOviHwSetLvdsHReverse)(BOOLEAN bParam);
	int (*pfnOviHwSetPatternGenerator)(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
	int (*pfnOviHwSetChannelPower)(BOOLEAN bParam);
	int (*pfnOviHwSetLvdsFormat)(LX_OVI_LVDS_OUT_STD_T enParam);
	int (*pfnOviHwSetLvdsBitDepth)(LX_OVI_BIT_DEPTH_T enParam);
	int (*pfnOviHwSetLvdsBlack)(BOOLEAN bParam);
	int (*pfnOviHwSetClock)(BOOLEAN bParam);
	int (*pfnOviHwSetEpiDataScramble)(BOOLEAN bParam);
	int (*pfnOviHwSetAdvanced10bit)(BOOLEAN bParam);
	int (*pfnOviHwSetVCOMPatternData)(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam);
	int (*pfnOviHwSetVCOMPatternCtrl)(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam);
	int (*pfnOviHwSetDispOutputMode)(LX_OVI_DISP_OUTPUT_MODE_T enParam);
	int (*pfnOviHwDisplayResume)(LX_OVI_DISPLAY_INFO_T *pstParams);
	int (*pfnOviHwSetPempItune)(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams);
	int (*pfnOviHwGetLockStatus)(BOOLEAN *pbParam);
	int (*pfnOviHwSetPmMode)(UINT32 u32Param);
	int (*pfnOviHwUpdateChipInfoHeader)(void);
	int (*pfnOviHwSetPCLRC)(LX_OVI_PCLRC_LUT_T *pstParams);
	int (*pfnOviHwSetDispOutMute)(UINT32 u32Param);
	int (*pfnOviHwSetDClock)(UINT32 *pu32Param);
	int (*pfnOviHwSetOutputTiming)(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams);
	int (*pfnOviHwGetStatus)(UINT32 *pu32Param);
	int (*pfnOviHwProcHandler)(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);
	int (*pfnOviHwClkCtrl)(struct ovi_clk_ctrl *p_ctrl);

	// Initialize on OVI_HAL_PreInit or before
	int (*pfnOviHwGetHWDisplayOption)(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
} OVI_HW_FUNCTION_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static OVI_HW_FUNCTION_T _gstOviHwFunction;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
* OVI Module Pre Initialize
*
* @param void
* @return int
*/
int OVI_HAL_PreInit(void)
{
	int ret = RET_OK;

	if(0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O26 A0\n");
		_gstOviHwFunction.pfnOviHwPreInitialize 		= OVI_HW_O26_PreInitialize;
		if (!_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
		{
			OVI_HW_O26_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O26_GetHWDisplayOption;
		}
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O24 A0\n");
		_gstOviHwFunction.pfnOviHwPreInitialize 		= OVI_HW_O24_PreInitialize;
		if (!_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
		{
			OVI_HW_O24_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O24_GetHWDisplayOption;
		}
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		OVI_PRINT("OVI chip revision is set to M23 A0\n");
		_gstOviHwFunction.pfnOviHwPreInitialize 		= OVI_HW_M23_PreInitialize;
		if (!_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
		{
			OVI_HW_M23_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_M23_GetHWDisplayOption;
		}
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O22 A0\n");
		_gstOviHwFunction.pfnOviHwPreInitialize 		= OVI_HW_O22_PreInitialize;
		_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O22_GetHWDisplayOption;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		OVI_PRINT("OVI chip revision is set to E60 A0\n");
		_gstOviHwFunction.pfnOviHwPreInitialize 		= OVI_HW_E60_PreInitialize;
		if (!_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
		{
			OVI_HW_E60_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_E60_GetHWDisplayOption;
		}
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O20 A0\n");
		_gstOviHwFunction.pfnOviHwPreInitialize			= OVI_HW_O20_PreInitialize;
		if (!_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
		{
			OVI_HW_O20_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O20_GetHWDisplayOption;
		}
	}
#endif
	else
	{
		OVI_ERROR("OVI ERROR! Unknown chip revision at OVI module\n");
		_gstOviHwFunction.pfnOviHwPreInitialize			= NULL;
		_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= NULL;
		ret = RET_ERROR;
	}

	if(_gstOviHwFunction.pfnOviHwPreInitialize)
	{
		ret = _gstOviHwFunction.pfnOviHwPreInitialize();
	}

	return ret;
}

/**
* OVI Module Initialize
*
* @param void
* @return int
*/
int OVI_HAL_Init(void)
{
	int ret = RET_OK;

	_gstOviHwFunction.pfnOviHwSetDispOutMute = NULL;
	_gstOviHwFunction.pfnOviHwSetDClock = NULL;
	_gstOviHwFunction.pfnOviHwGetStatus = NULL;
	_gstOviHwFunction.pfnOviHwSetOutputTiming = NULL;

	if(0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O26 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_O26_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= OVI_HW_O26_Suspend;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_O26_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_O26_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_O26_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass 			= OVI_HW_O26_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_O26_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_O26_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand 		= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_O26_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_O26_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_O26_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_O26_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_O26_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_O26_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_O26_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_O26_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= OVI_HW_O26_SetMultiWinGamut;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= OVI_HW_O26_GetMultiWinGamut;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_O26_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_O26_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_O26_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_O26_SetTconHReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_O26_SetLvdsHReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_O26_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_O26_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_O26_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_O26_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_O26_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_O26_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_O26_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_O26_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_O26_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_O26_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode 	= OVI_HW_O26_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_O26_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= OVI_HW_O26_SetPempItune;
		_gstOviHwFunction.pfnOviHwGetLockStatus 		= OVI_HW_O26_GetLockStatus;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= OVI_HW_O26_SetPmMode;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = OVI_HW_O26_UpdateChipInfoHeader;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_O26_Close;
		_gstOviHwFunction.pfnOviHwSetDispOutMute		= OVI_HW_O26_SetDispOutMute;
		_gstOviHwFunction.pfnOviHwSetDClock 			= OVI_HW_O26_SetDClock;
		_gstOviHwFunction.pfnOviHwSetOutputTiming 		= OVI_HW_O26_SetOutputTiming;
		_gstOviHwFunction.pfnOviHwGetStatus 			= OVI_HW_O26_GetStatus;
		_gstOviHwFunction.pfnOviHwClkCtrl 				= ovi_hw_o26_clk_ctrl;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_O26_ProcHandler;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O24 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_O24_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= OVI_HW_O24_Suspend;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_O24_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_O24_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_O24_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass 			= OVI_HW_O24_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_O24_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_O24_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand 		= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_O24_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_O24_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_O24_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_O24_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_O24_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_O24_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_O24_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_O24_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= OVI_HW_O24_SetMultiWinGamut;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= OVI_HW_O24_GetMultiWinGamut;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_O24_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_O24_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_O24_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_O24_SetTconHReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_O24_SetLvdsHReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_O24_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_O24_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_O24_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_O24_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_O24_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_O24_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_O24_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_O24_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_O24_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_O24_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode 	= OVI_HW_O24_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_O24_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= OVI_HW_O24_SetPempItune;
		_gstOviHwFunction.pfnOviHwGetLockStatus 		= OVI_HW_O24_GetLockStatus;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= OVI_HW_O24_SetPmMode;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = OVI_HW_O24_UpdateChipInfoHeader;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_O24_Close;
		_gstOviHwFunction.pfnOviHwSetDispOutMute		= OVI_HW_O24_SetDispOutMute;
		_gstOviHwFunction.pfnOviHwSetDClock 			= OVI_HW_O24_SetDClock;
		_gstOviHwFunction.pfnOviHwGetStatus 			= OVI_HW_O24_GetStatus;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_O24_ProcHandler;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		OVI_PRINT("OVI chip revision is set to M23 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_M23_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= OVI_HW_M23_Suspend;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_M23_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_M23_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_M23_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass 			= OVI_HW_M23_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_M23_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_M23_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand 		= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_M23_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= OVI_HW_M23_SetLodLut;
		_gstOviHwFunction.pfnOviHwSetPodLut				= OVI_HW_M23_SetPodLut;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_M23_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_M23_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_M23_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_M23_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_M23_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_M23_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_M23_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_M23_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= OVI_HW_M23_SetGammaRGBW;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_M23_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_M23_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= OVI_HW_M23_SetDemura;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_M23_SetTconHReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_M23_SetLvdsHReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_M23_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_M23_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_M23_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_M23_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_M23_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_M23_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_M23_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_M23_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_M23_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_M23_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode 	= OVI_HW_M23_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_M23_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= OVI_HW_M23_SetPempItune;
		_gstOviHwFunction.pfnOviHwGetLockStatus 		= OVI_HW_M23_GetLockStatus;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= OVI_HW_M23_SetPmMode;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader	= NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= OVI_HW_M23_SetPCLRC;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_M23_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_M23_ProcHandler;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O22 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_O22_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= OVI_HW_O22_Suspend;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_O22_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_O22_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_O22_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass 			= OVI_HW_O22_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_O22_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_O22_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand 		= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_O22_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_O22_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_O22_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_O22_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_O22_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_O22_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_O22_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_O22_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_O22_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_O22_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_O22_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_O22_SetTconHReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_O22_SetLvdsHReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_O22_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_O22_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_O22_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_O22_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_O22_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_O22_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_O22_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_O22_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_O22_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_O22_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode 	= OVI_HW_O22_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_O22_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= OVI_HW_O22_SetPempItune;
		_gstOviHwFunction.pfnOviHwGetLockStatus 		= OVI_HW_O22_GetLockStatus;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= OVI_HW_O22_SetPmMode;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = OVI_HW_O22_UpdateChipInfoHeader;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_O22_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_O22_ProcHandler;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		OVI_PRINT("OVI chip revision is set to E60 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_E60_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= OVI_HW_E60_Suspend;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_E60_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_E60_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_E60_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass 			= OVI_HW_E60_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_E60_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_E60_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand 		= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= NULL;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_E60_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_E60_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_E60_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= NULL;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_E60_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_E60_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_E60_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= NULL;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_E60_SetTconHReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_E60_SetLvdsHReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_E60_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_E60_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_E60_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_E60_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_E60_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= NULL;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= NULL;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= NULL;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_E60_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_E60_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode 	= OVI_HW_E60_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_E60_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= OVI_HW_E60_SetPempItune;
		_gstOviHwFunction.pfnOviHwGetLockStatus			= OVI_HW_E60_GetLockStatus;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_E60_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_E60_ProcHandler;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O20 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_O20_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= OVI_HW_O20_Suspend;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_O20_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_O20_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_O20_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass 			= OVI_HW_O20_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_O20_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_O20_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand 		= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_O20_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_O20_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_O20_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_O20_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_O20_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_O20_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_O20_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_O20_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_O20_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_O20_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_O20_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_O20_SetTconHReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_O20_SetLvdsHReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_O20_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_O20_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_O20_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_O20_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_O20_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_O20_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_O20_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_O20_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_O20_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_O20_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode 	= OVI_HW_O20_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_O20_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= OVI_HW_O20_SetPempItune;
		_gstOviHwFunction.pfnOviHwGetLockStatus			= NULL;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= OVI_HW_O20_SetPmMode;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_O20_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_O20_ProcHandler;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		OVI_PRINT("OVI chip revision is set to M19 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_M19_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= NULL;
		_gstOviHwFunction.pfnOviHwEarlyResume			= OVI_HW_M19_EarlyResume;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_M19_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_M19_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass				= OVI_HW_M19_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_M19_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_M19_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand			= OVI_HW_M19_SetMcuCommand;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= OVI_HW_M19_UpdateFirmware;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= OVI_HW_M19_GetFirmwareVersion;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_M19_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_M19_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_M19_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_M19_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_M19_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_M19_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_M19_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_M19_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_M19_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= OVI_HW_M19_SetGammaRGBW;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_M19_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= OVI_HW_M19_SetMleMode;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_M19_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_M19_SetTconReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_M19_SetLvdsReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_M19_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_M19_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_M19_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_M19_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_M19_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_M19_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_M19_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_M19_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_M19_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_M19_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode		= NULL;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_M19_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= NULL;
		_gstOviHwFunction.pfnOviHwGetLockStatus			= NULL;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_M19_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_M19_ProcHandler;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		OVI_PRINT("OVI chip revision is set to O18 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_O18_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= NULL;
		_gstOviHwFunction.pfnOviHwEarlyResume			= NULL;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_O18_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_O18_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass				= OVI_HW_O18_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_O18_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_O18_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_O18_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_O18_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_O18_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_O18_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_O18_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_O18_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_O18_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_O18_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_O18_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_O18_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= NULL;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_O18_SetTconReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_O18_SetLvdsReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_O18_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_O18_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_O18_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_O18_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_O18_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_O18_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= NULL;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= NULL;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= NULL;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= NULL;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode		= OVI_HW_O18_SetDispOutputMode;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_O18_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= NULL;
		_gstOviHwFunction.pfnOviHwGetLockStatus			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_O18_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_O18_ProcHandler;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		OVI_PRINT("OVI chip revision is set to M17 A0\n");
		_gstOviHwFunction.pfnOviHwInitialize			= OVI_HW_M17_Initialize;
		_gstOviHwFunction.pfnOviHwSuspend				= NULL;
		_gstOviHwFunction.pfnOviHwEarlyResume			= NULL;
		_gstOviHwFunction.pfnOviHwResume				= OVI_HW_M17_Resume;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= OVI_HW_M17_SetDisplayOption;
		_gstOviHwFunction.pfnOviHwSetBypass				= OVI_HW_M17_SetBypass;
		_gstOviHwFunction.pfnOviHwSetCombination		= OVI_HW_M17_SetCombination;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= OVI_HW_M17_SetSpreadSpectrum;
		_gstOviHwFunction.pfnOviHwSetMcuCommand			= OVI_HW_M17_SetMcuCommand;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= OVI_HW_M17_UpdateFirmware;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= OVI_HW_M17_GetFirmwareVersion;
		_gstOviHwFunction.pfnOviHwSetOdLut				= OVI_HW_M17_SetOdLut;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable 	= OVI_HW_M17_SetFrameOdcEnable;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= OVI_HW_M17_SetColorTempEnable;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= OVI_HW_M17_SetGammaEnable;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= OVI_HW_M17_SetDitherEnable;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= OVI_HW_M17_SetLineOdcMode;
		_gstOviHwFunction.pfnOviHwSetDitherMode 		= OVI_HW_M17_SetDitherMode;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= OVI_HW_M17_SetColorTemp;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= OVI_HW_M17_SetGamma;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= OVI_HW_M17_SetGammaRGBW;
		_gstOviHwFunction.pfnOviHwGetOdLut				= OVI_HW_M17_GetOdLut;
		_gstOviHwFunction.pfnOviHwSetMleMode			= OVI_HW_M17_SetMleMode;
		_gstOviHwFunction.pfnOviHwSetTscic				= OVI_HW_M17_SetTscic;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= OVI_HW_M17_SetTconReverse;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= OVI_HW_M17_SetLvdsReverse;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= OVI_HW_M17_SetPatternGenerator;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= OVI_HW_M17_SetChannelPower;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat 		= OVI_HW_M17_SetLvdsFormat;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= OVI_HW_M17_SetLvdsBitDepth;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= OVI_HW_M17_SetLvdsBlack;
		_gstOviHwFunction.pfnOviHwSetClock				= OVI_HW_M17_SetClock;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= OVI_HW_M17_SetEpiDataScramble;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= OVI_HW_M17_SetAdvanced10bit;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= OVI_HW_M17_SetVCOMPatternData;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= OVI_HW_M17_SetVCOMPatternCtrl;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode		= NULL;
		_gstOviHwFunction.pfnOviHwDisplayResume 		= OVI_HW_M17_DisplayResume;
		_gstOviHwFunction.pfnOviHwSetPempItune			= NULL;
		_gstOviHwFunction.pfnOviHwGetLockStatus			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose 				= OVI_HW_M17_Close;
		_gstOviHwFunction.pfnOviHwProcHandler			= OVI_HW_M17_ProcHandler;
	}
#endif
	else
	{
		OVI_ERROR("OVI ERROR! Unknown chip revision at OVI module\n");
		_gstOviHwFunction.pfnOviHwInitialize    		= NULL;
		_gstOviHwFunction.pfnOviHwSuspend				= NULL;
		_gstOviHwFunction.pfnOviHwEarlyResume			= NULL;
		_gstOviHwFunction.pfnOviHwResume	    		= NULL;
		_gstOviHwFunction.pfnOviHwSetDisplayOption		= NULL;
		_gstOviHwFunction.pfnOviHwSetBypass				= NULL;
		_gstOviHwFunction.pfnOviHwSetCombination		= NULL;
		_gstOviHwFunction.pfnOviHwSetSpreadSpectrum 	= NULL;
		_gstOviHwFunction.pfnOviHwSetMcuCommand			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateFirmware		= NULL;
		_gstOviHwFunction.pfnOviHwGetFirmwareVersion	= NULL;
		_gstOviHwFunction.pfnOviHwSetOdLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetLodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetPodLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetFrameOdcEnable		= NULL;
		_gstOviHwFunction.pfnOviHwSetColorTempEnable	= NULL;
		_gstOviHwFunction.pfnOviHwSetGammaEnable		= NULL;
		_gstOviHwFunction.pfnOviHwSetDitherEnable		= NULL;
		_gstOviHwFunction.pfnOviHwSetLineOdcMode		= NULL;
		_gstOviHwFunction.pfnOviHwSetDitherMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetColorTemp			= NULL;
		_gstOviHwFunction.pfnOviHwSetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwGetMultiWindowGamut	= NULL;
		_gstOviHwFunction.pfnOviHwSetGamma				= NULL;
		_gstOviHwFunction.pfnOviHwSetGammaRGBW			= NULL;
		_gstOviHwFunction.pfnOviHwGetOdLut				= NULL;
		_gstOviHwFunction.pfnOviHwSetMleMode			= NULL;
		_gstOviHwFunction.pfnOviHwSetTscic				= NULL;
		_gstOviHwFunction.pfnOviHwSetDemura				= NULL;
		_gstOviHwFunction.pfnOviHwSetTconHReverse		= NULL;
		_gstOviHwFunction.pfnOviHwSetLvdsHReverse		= NULL;
		_gstOviHwFunction.pfnOviHwSetPatternGenerator	= NULL;
		_gstOviHwFunction.pfnOviHwSetChannelPower		= NULL;
		_gstOviHwFunction.pfnOviHwSetLvdsFormat			= NULL;
		_gstOviHwFunction.pfnOviHwSetLvdsBitDepth		= NULL;
		_gstOviHwFunction.pfnOviHwSetLvdsBlack			= NULL;
		_gstOviHwFunction.pfnOviHwSetClock				= NULL;
		_gstOviHwFunction.pfnOviHwSetEpiDataScramble	= NULL;
		_gstOviHwFunction.pfnOviHwSetAdvanced10bit		= NULL;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternData	= NULL;
		_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl	= NULL;
		_gstOviHwFunction.pfnOviHwSetDispOutputMode		= NULL;
		_gstOviHwFunction.pfnOviHwDisplayResume			= NULL;
		_gstOviHwFunction.pfnOviHwSetPempItune			= NULL;
		_gstOviHwFunction.pfnOviHwGetLockStatus			= NULL;
		_gstOviHwFunction.pfnOviHwSetPmMode 			= NULL;
		_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader  = NULL;
		_gstOviHwFunction.pfnOviHwSetPCLRC				= NULL;
		_gstOviHwFunction.pfnOviHwClose					= NULL;
		_gstOviHwFunction.pfnOviHwProcHandler			= NULL;
		ret = RET_ERROR;
	}

	if(_gstOviHwFunction.pfnOviHwInitialize)
	{
		ret = _gstOviHwFunction.pfnOviHwInitialize();
	}

	return ret;
}

int OVI_HAL_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
	{
		ret = _gstOviHwFunction.pfnOviHwGetHWDisplayOption(pstParams);
	}
	else
	{
		// For use prior to OVI_HAL_PreInit (ex. de_cfg_preinit)
		if(0)
		{

		}
#ifdef INCLUDE_O26_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		{
			OVI_HW_O26_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O26_GetHWDisplayOption;
		}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		{
			OVI_HW_O24_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O24_GetHWDisplayOption;
		}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		{
			OVI_HW_M23_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_M23_GetHWDisplayOption;
		}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		{
			OVI_HW_O22_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O22_GetHWDisplayOption;
		}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		{
			OVI_HW_E60_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_E60_GetHWDisplayOption;
		}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
		{
			OVI_HW_O20_HWDisplayOptionInit();
			_gstOviHwFunction.pfnOviHwGetHWDisplayOption	= OVI_HW_O20_GetHWDisplayOption;
		}
#endif
		else
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}

		if(_gstOviHwFunction.pfnOviHwGetHWDisplayOption)
		{
			ret = _gstOviHwFunction.pfnOviHwGetHWDisplayOption(pstParams);
		}
	}

	return ret;
}

int OVI_HAL_Suspend(void)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSuspend)
	{
		ret = _gstOviHwFunction.pfnOviHwSuspend();
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_EarlyResume(void)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwEarlyResume)
	{
		ret = _gstOviHwFunction.pfnOviHwEarlyResume();
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_Resume(void)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwResume)
	{
		ret = _gstOviHwFunction.pfnOviHwResume();
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetDisplayOption)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDisplayOption(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetBypass)
	{
		ret = _gstOviHwFunction.pfnOviHwSetBypass(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetCombination(UINT32 param)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetCombination)
	{
		ret = _gstOviHwFunction.pfnOviHwSetCombination(param);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetSpreadSpectrum)
	{
		ret = _gstOviHwFunction.pfnOviHwSetSpreadSpectrum(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetMcuCommand(LX_OVI_TCON_MCU_CMD_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetMcuCommand)
	{
		ret = _gstOviHwFunction.pfnOviHwSetMcuCommand(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_UpdateFirmware(LX_OVI_TCON_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwUpdateFirmware)
	{
		ret = _gstOviHwFunction.pfnOviHwUpdateFirmware(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_GetFirmwareVersion(LX_OVI_TCON_FW_VER_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwGetFirmwareVersion)
	{
		ret = _gstOviHwFunction.pfnOviHwGetFirmwareVersion(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetOdLut)
	{
		ret = _gstOviHwFunction.pfnOviHwSetOdLut(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetLodLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetLodLut)
	{
		ret = _gstOviHwFunction.pfnOviHwSetLodLut(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetPodLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetPodLut)
	{
		ret = _gstOviHwFunction.pfnOviHwSetPodLut(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetFrameOdcEnable)
	{
		ret = _gstOviHwFunction.pfnOviHwSetFrameOdcEnable(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetColorTempEnable)
	{
		ret = _gstOviHwFunction.pfnOviHwSetColorTempEnable(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetGammaEnable)
	{
		ret = _gstOviHwFunction.pfnOviHwSetGammaEnable(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetDitherEnable)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDitherEnable(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("BE_INT_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetLineOdcMode)
	{
		ret = _gstOviHwFunction.pfnOviHwSetLineOdcMode(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetDitherMode)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDitherMode(enParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetColorTemp)
	{
		ret = _gstOviHwFunction.pfnOviHwSetColorTemp(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetMultiWindow_Gamut(LX_OVI_MULTIWIN_GAMUT_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetMultiWindowGamut)
	{
		ret = _gstOviHwFunction.pfnOviHwSetMultiWindowGamut(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_GetMultiWindow_Gamut(LX_OVI_MULTIWIN_GAMUT_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwGetMultiWindowGamut)
	{
		ret = _gstOviHwFunction.pfnOviHwGetMultiWindowGamut(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetGamma)
	{
		ret = _gstOviHwFunction.pfnOviHwSetGamma(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetGammaRGBW)
	{
		ret = _gstOviHwFunction.pfnOviHwSetGammaRGBW(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwGetOdLut)
	{
		ret = _gstOviHwFunction.pfnOviHwGetOdLut(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetMleMode(LX_OVI_TCON_MLE_MODE_T enParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetMleMode)
	{
		ret = _gstOviHwFunction.pfnOviHwSetMleMode(enParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetTscic)
	{
		ret = _gstOviHwFunction.pfnOviHwSetTscic(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetDemura(LX_OVI_TCON_DEMURA_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetDemura)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDemura(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}


int OVI_HAL_SetTconHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetTconHReverse)
	{
		ret = _gstOviHwFunction.pfnOviHwSetTconHReverse(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetLvdsHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetLvdsHReverse)
	{
		ret = _gstOviHwFunction.pfnOviHwSetLvdsHReverse(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetPatternGenerator)
	{
		ret = _gstOviHwFunction.pfnOviHwSetPatternGenerator(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetChannelPower)
	{
		ret = _gstOviHwFunction.pfnOviHwSetChannelPower(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	OVI_HAL_PM_INFO("info", bParam ? "ch_on" : "ch_off", ret == RET_OK ? "OK" : "NG");

	return ret;
}

int OVI_HAL_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetLvdsFormat)
	{
		ret = _gstOviHwFunction.pfnOviHwSetLvdsFormat(enParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetLvdsBitDepth)
	{
		ret = _gstOviHwFunction.pfnOviHwSetLvdsBitDepth(enParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetLvdsBlack)
	{
		ret = _gstOviHwFunction.pfnOviHwSetLvdsBlack(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetClock)
	{
		ret = _gstOviHwFunction.pfnOviHwSetClock(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetEpiDataScramble)
	{
		ret = _gstOviHwFunction.pfnOviHwSetEpiDataScramble(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetAdvanced10bit)
	{
		ret = _gstOviHwFunction.pfnOviHwSetAdvanced10bit(bParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetVCOMPatternData)
	{
		ret = _gstOviHwFunction.pfnOviHwSetVCOMPatternData(pstParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl)
	{
		ret = _gstOviHwFunction.pfnOviHwSetVCOMPatternCtrl(enParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetDispOutputMode)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDispOutputMode(enParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwDisplayResume)
	{
		ret = _gstOviHwFunction.pfnOviHwDisplayResume(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetPempItune)
	{
		ret = _gstOviHwFunction.pfnOviHwSetPempItune(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int  OVI_HAL_GetLockStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwGetLockStatus)
	{
		ret = _gstOviHwFunction.pfnOviHwGetLockStatus(pbParam);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetPmMode)
	{
		ret = _gstOviHwFunction.pfnOviHwSetPmMode(u32Param);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	OVI_HAL_PM_INFO("info", "set_mode", ret == RET_OK ? "OK" : "NG");

	return ret;
}

int OVI_HAL_UpdateChipInfoHeader(void)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwUpdateChipInfoHeader)
	{
		ret = _gstOviHwFunction.pfnOviHwUpdateChipInfoHeader();
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI	ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI	WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetPCLRC(LX_OVI_PCLRC_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetPCLRC)
	{
		ret = _gstOviHwFunction.pfnOviHwSetPCLRC(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetDispOutMute(UINT32 u32Param)
{
	int ret = RET_ERROR;

	if(_gstOviHwFunction.pfnOviHwSetDispOutMute)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDispOutMute(u32Param);
	}

	return ret;
}

int OVI_HAL_SetDClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetDClock)
	{
		ret = _gstOviHwFunction.pfnOviHwSetDClock(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_SetOutputTiming(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwSetOutputTiming)
	{
		ret = _gstOviHwFunction.pfnOviHwSetOutputTiming(pstParams);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int OVI_HAL_GetStatus(UINT32 *pstParams)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwGetStatus)
	{
		ret = _gstOviHwFunction.pfnOviHwGetStatus(pstParams);
	}
	else
	{
		// not support
	}

	return ret;
}

int ovi_hal_clk_ctrl(struct ovi_clk_ctrl *p_ctrl)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwClkCtrl)
	{
		ret = _gstOviHwFunction.pfnOviHwClkCtrl(p_ctrl);
	}
	else
	{
		// not support
	}

	return ret;
}

int OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	if(_gstOviHwFunction.pfnOviHwProcHandler)
	{
		ret = _gstOviHwFunction.pfnOviHwProcHandler(proc_id, m, data);
	}
	else
	{
		if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_ERROR)
		{
			OVI_PRINT("OVI  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gOVIHalFuncSupportDbgLevel == OVI_DBG_LEVEL_WARN)
		{
			OVI_PRINT("OVI  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

/** @} */
