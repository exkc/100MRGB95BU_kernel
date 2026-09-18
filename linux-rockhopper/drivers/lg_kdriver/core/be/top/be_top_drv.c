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
 *  be_top driver file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2013.04.27
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
//#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_kapi.h"
#include "be_def.h"
#include "be_reg.h"
#include "fwl_drv.h"
#include "be_top_hal.h"
#include "be_top_drv.h"

#include "video_status_keeper.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
#define	BE_TOP_DBG_STATUS_BYPASS			(1<<0)
#define BE_TOP_DBG_STATUS_TOGGLE_TRID		(1<<1)
#define BE_TOP_DBG_STATUS_TRID_CONVERGENCE	(1<<2)
#define BE_TOP_DBG_STATUS_BLACK_BAR			(1<<3)
#define BE_TOP_DBG_STATUS_REAL_CINEMA		(1<<4)
#define BE_TOP_DBG_STATUS_ORBIT				(1<<5)
#define BE_TOP_DBG_STATUS_LSR				(1<<6)
#define BE_TOP_DBG_STATUS_LSR_PARAM			(1<<7)
#define BE_TOP_DBG_STATUS_GSR				(1<<8)
#define BE_TOP_DBG_STATUS_CPC				(1<<9)
#define BE_TOP_DBG_STATUS_OSD_RGB_LEVEL		(1<<10)
#define BE_TOP_DBG_STATUS_DISP_MODE			(1<<11)
#define BE_TOP_DBG_STATUS_INPUT_LAG			(1<<12)
#define BE_TOP_DBG_STATUS_INPUT_LAG_PATTERN	(1<<13)

	UINT32						status;

	LX_BE_BLOCK_BYPASS_T		bypass_param;
	LX_BE_3D_LR_T				trid_param;
	LX_BE_3D_CONVERGENCE_T		trid_convergence_param;
	LX_BE_BLACK_BAR_T			black_bar_param;

	LX_BE_REAL_CINEMA_T			real_cinema_param;

	LX_BE_ORBIT_T				orbit_param;
	BOOLEAN						lsr_param;
	LX_BE_LSR_T					lsr_param_param;
	LX_BE_GSR_T					gsr_param;
	UINT32						cpc_param;
	LX_BE_OSD_RGB_LEVEL_T		osd_rgb_level_param;
	LX_BE_DISP_MODE_T			disp_mode_param;

	UINT32						lag_param;
	LX_BE_INPUT_LAG_PATTERN_T	lag_paterrn_param;
}
BE_TOP_DBG_STATUS_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern  LX_VP_ST_KEEPER_T *gSKeeperDataBase;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int gHalFuncSupportDbgLevel = BE_DBG_LEVEL_IGNORE;
int g_be_orbit_onoff = 0xff;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static BE_TOP_DBG_STATUS_T g_be_top_dbg_status =
{
	.status = 0x0,

};

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_TOP_PreInit(void)
{
	int ret = RET_OK;

	ret = BE_TOP_HAL_PreInit();

	return ret;
}

int BE_TOP_Init(void)
{
	int ret = RET_OK;

	ret = BE_TOP_HAL_Init();

	return ret;
}

int BE_TOP_Close(void)
{
	int ret = RET_OK;

	ret = BE_TOP_HAL_Close();

	return ret;
}

int BE_TOP_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOW_UPDATE_FIRMWARE:
		{
			BE_FW_DWLD_T stParams;

			ret = copy_from_user(&stParams, (BE_FW_DWLD_T *)arg, sizeof(BE_FW_DWLD_T));
			if(ret) BREAK_WRONG(ret);

			ret = BE_FW_Update(&stParams);
		}
		break;

		case BE_IOW_TOP_SET_BYPASS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Bypass(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_TOGGLE_3D_LR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Toggle_3D_LR(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_3D_CONVERGENCE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_3D_Convergence(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_BLACK_BAR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Black_Bar(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_DEBUG_DISPLAY:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Debug_Display(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_REAL_CINEMA:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Real_Cinema(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_ORBIT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Orbit(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_LSR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_LSR(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TEST_INPUT_LAG:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Input_Lag(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_INPUT_LAG_PATTERN:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Input_Lag_Pattern(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_LSR_PARAM:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_LSRParam(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_GSR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_GSR(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_GET_GSR_STATUS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_GSRStatus(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_CPC:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_CPC(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_GET_OSD_ALPHA_APL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_OSDAlphaAPL(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_OSD_RGB_LEVEL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_OSDRGBLevel(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_DISP_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_DispMode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_TOP_GET_IRR_STATUS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_IrrStatus(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_IRR_DATA:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_IrrData(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_TOP_GET_IRR_DATA:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_IrrData(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IORW_REG_ACCESS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_REG_RegAccess(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_ENABLE_DEBUG_PRINT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_DebugPrint(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		default :
		{
			BE_ERROR("WARNING! WRONG IOCTL CALL!!\n");
			ret = RET_ERROR;
		}
		break;
	}

	return ret;
}

int BE_TOP_Set_DebugPrint(unsigned long arg)
{
	int ret = RET_OK;
	BE_DEBUG_PRINT_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_DEBUG_PRINT_T *)arg, sizeof(BE_DEBUG_PRINT_T));
		if(ret) BREAK_WRONG(ret);

		if(stParams.dbgMask & BE_DBG_PRT_MSK_PRINT) // BE_PRINT
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_PRINT, DBG_COLOR_NONE );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_PRINT );
		}

		if(stParams.dbgMask & BE_DBG_PRT_MSK_ERROR) // BE_ERROR
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_ERROR, DBG_COLOR_UL_RED );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_ERROR );
		}

		if(stParams.dbgMask & BE_DBG_PRT_MSK_DEBUG) // BE_DEBUG
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_DEBUG, DBG_COLOR_NONE );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_DEBUG );
		}

		if(stParams.dbgMask & BE_DBG_PRT_MSK_TRACE) // BE_TRACE
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE, DBG_COLOR_NONE );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE );
		}

		if(stParams.dbgMask & (BE_DBG_PRT_MSK_TRACE+1)) // BE_TRACE1
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, (BE_DBG_PRT_MSK_TRACE+1), DBG_COLOR_NONE );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, (BE_DBG_PRT_MSK_TRACE+1) );
		}

		switch(stParams.funcSupportDbgLevel)
		{
			case 0 :
				gHalFuncSupportDbgLevel = BE_DBG_LEVEL_ERROR;
				break;
			case 1 :
				gHalFuncSupportDbgLevel = BE_DBG_LEVEL_WARN;
				break;
			case 2 :
				gHalFuncSupportDbgLevel = BE_DBG_LEVEL_IGNORE;
				break;
			default :
				gHalFuncSupportDbgLevel = BE_DBG_LEVEL_ERROR;
		}
	} while(0);
	return ret;
}

int BE_TOP_Set_Bypass(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_BLOCK_BYPASS_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_BLOCK_BYPASS_T *)arg, sizeof(LX_BE_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetBypass(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_BYPASS;
		g_be_top_dbg_status.bypass_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Toggle_3D_LR(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_3D_LR_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_3D_LR_T *)arg, sizeof(LX_BE_3D_LR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_Toggle3DLR(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_TOGGLE_TRID;
		g_be_top_dbg_status.trid_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Set_3D_Convergence(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_3D_CONVERGENCE_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_3D_CONVERGENCE_T *)arg, sizeof(LX_BE_3D_CONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_Set3DConvergence(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_TRID_CONVERGENCE;
		g_be_top_dbg_status.trid_convergence_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Set_Black_Bar(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_BLACK_BAR_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_BLACK_BAR_T *)arg, sizeof(LX_BE_BLACK_BAR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetBlackBar(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_BLACK_BAR;
		g_be_top_dbg_status.black_bar_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Set_Debug_Display(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_DEBUG_DISPLAY_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_DEBUG_DISPLAY_T *)arg, sizeof(LX_BE_DEBUG_DISPLAY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetDebugDisplay(&stParams);
		if(ret) BREAK_WRONG(ret);

	} while(0);
	return ret;
}

int BE_TOP_Set_Real_Cinema(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_REAL_CINEMA_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_REAL_CINEMA_T *)arg, sizeof(LX_BE_REAL_CINEMA_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetRealCinema(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_REAL_CINEMA;
		g_be_top_dbg_status.real_cinema_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Set_Orbit(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_ORBIT_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_ORBIT_T *)arg, sizeof(LX_BE_ORBIT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetOrbit(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_ORBIT;
		g_be_top_dbg_status.orbit_param = stParams;
		g_be_orbit_onoff = stParams.bOnOff;

	} while(0);
	return ret;
}

int BE_TOP_Set_LSR(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN param;

	do{
		ret = copy_from_user(&param, (BOOLEAN *)arg, sizeof(BOOLEAN));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetLSR(param);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_LSR;
		g_be_top_dbg_status.lsr_param = param;

	} while(0);
	return ret;
}

int BE_TOP_Set_Input_Lag(unsigned long arg)
{
	int ret = RET_OK;
	UINT32 param;

	do{
		ret = copy_from_user(&param, (UINT32 *)arg, sizeof(UINT32));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetInputLagTest(param);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_INPUT_LAG;
		g_be_top_dbg_status.lag_param = param;

	} while(0);
	return ret;
}

int BE_TOP_Set_Input_Lag_Pattern(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_INPUT_LAG_PATTERN_T param;

	do{
		ret = copy_from_user(&param, (LX_BE_INPUT_LAG_PATTERN_T *)arg, sizeof(LX_BE_INPUT_LAG_PATTERN_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetInputLagPattern(&param);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_INPUT_LAG_PATTERN;
		g_be_top_dbg_status.lag_paterrn_param = param;
	} while(0);
	return ret;
}

int BE_TOP_Set_LSRParam(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LSR_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_LSR_T *)arg, sizeof(LX_BE_LSR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetLSRParam(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_LSR_PARAM;
		g_be_top_dbg_status.lsr_param_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Set_GSR(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_GSR_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_GSR_T *)arg, sizeof(LX_BE_GSR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetGSR(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_GSR;
		g_be_top_dbg_status.gsr_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Get_GSRStatus(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN param;

	do{
		ret = BE_TOP_HAL_GetGSRStatus(&param);
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &param, sizeof(BOOLEAN));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_CPC(unsigned long arg)
{
	int ret = RET_OK;
	UINT32 param;

	do{
		ret = copy_from_user(&param, (UINT32 *)arg, sizeof(UINT32));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetCPC(param);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_CPC;
		g_be_top_dbg_status.cpc_param = param;

	} while(0);
	return ret;
}

int BE_TOP_Get_OSDAlphaAPL(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LUT_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_LUT_T *)arg, sizeof(LX_BE_LUT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_GetOSDAlphaAPL(&stParams);
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_OSDRGBLevel(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_OSD_RGB_LEVEL_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_OSD_RGB_LEVEL_T *)arg, sizeof(LX_BE_OSD_RGB_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetOSDRGBLevel(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_OSD_RGB_LEVEL;
		g_be_top_dbg_status.osd_rgb_level_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Set_DispMode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_DISP_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_DISP_MODE_T *)arg, sizeof(LX_BE_DISP_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetDispMode(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_top_dbg_status.status |= BE_TOP_DBG_STATUS_DISP_MODE;
		g_be_top_dbg_status.disp_mode_param = stParams;

	} while(0);
	return ret;
}

int BE_TOP_Get_IrrStatus(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_IRR_STATUS_T stParams;

	do{
		ret = BE_TOP_HAL_GetIrrStatus(&stParams);
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_IRR_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_IrrData(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LUT_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_LUT_T *)arg, sizeof(LX_BE_LUT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_SetIrrData(&stParams);
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Get_IrrData(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_IRR_READ_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_IRR_READ_T *)arg, sizeof(LX_BE_IRR_READ_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_TOP_HAL_GetIrrData(&stParams);
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

static int BE_TOP_PrintDrvStatus(struct seq_file* m, void* data)
{
	char* na_str = "n/a";

	if ( g_be_top_dbg_status.status & BE_TOP_DBG_STATUS_BYPASS )
	{
		LX_BE_BLOCK_BYPASS_T* param = &g_be_top_dbg_status.bypass_param;

		seq_printf(m, "h3d_bypass: %s\n", (param->bH3DBypass)?"on":"off" );
		seq_printf(m, "frc_bypass: %s\n", (param->bFRCBypass)?"on":"off" );
		seq_printf(m, "led_bypass: %s\n", (param->bLEDBypass)?"on":"off" );
		seq_printf(m, "hdr_bypass: %s\n", (param->bHDRBypass)?"on":"off" );
		seq_printf(m, "wcg_bypass: %s\n", (param->bWCGBypass)?"on":"off" );
	}
	else
	{
		seq_printf(m, "h3d_bypass: %s\n", na_str);
		seq_printf(m, "frc_bypass: %s\n", na_str);
		seq_printf(m, "led_bypass: %s\n", na_str);
		seq_printf(m, "hdr_bypass: %s\n", na_str);
		seq_printf(m, "wcg_bypass: %s\n", na_str);
	}

	if (g_be_top_dbg_status.status & BE_TOP_DBG_STATUS_BLACK_BAR)
	{
		seq_printf(m, "black_bar.on: %s\n", (g_be_top_dbg_status.black_bar_param.u8BarOn)? "on":"off");
		seq_printf(m, "black_bar.var: 0x%x\n", g_be_top_dbg_status.black_bar_param.u8BarVal);
		seq_printf(m, "black_bar.step: 0x%x\n", g_be_top_dbg_status.black_bar_param.u8BarStep);
	}
	else
	{
		seq_printf(m, "black_bar.on: %s\n", na_str);
		seq_printf(m, "black_bar.var: %s\n", na_str);
		seq_printf(m, "black_bar.step: %s\n", na_str);
	}

	if (g_be_top_dbg_status.status & BE_TOP_DBG_STATUS_REAL_CINEMA)
	{
		LX_BE_REAL_CINEMA_T* param = &g_be_top_dbg_status.real_cinema_param;
		seq_printf(m, "real_cinema.enable: 0x%x\n", param->u32RealCinemaEnable);
	}
	else
	{
		seq_printf(m, "real_cinema.enable: %s\n", na_str);
	}

	if (g_be_top_dbg_status.status & BE_TOP_DBG_STATUS_TOGGLE_TRID)
	{
		LX_BE_3D_LR_T* param = &g_be_top_dbg_status.trid_param;
		seq_printf(m, "trid.out_lr: 0x%x\n", param->bOutLR );
	}
	else
	{
		seq_printf(m, "trid.out_lr: %s\n", na_str);
	}

	if (g_be_top_dbg_status.status & BE_TOP_DBG_STATUS_TRID_CONVERGENCE)
	{
		LX_BE_3D_CONVERGENCE_T* param = &g_be_top_dbg_status.trid_convergence_param;

		seq_printf(m, "trid.convergence_en: 0x%x\n", param->u16ConvergenceEnable);
		seq_printf(m, "trid.convergence_val: 0x%x\n", param->u16ConvergenceVal);
	}
	else
	{
		seq_printf(m, "trid.convergence_en: %s\n", na_str);
		seq_printf(m, "trid.convergence_val: %s\n", na_str);
	}

	/* TODO: dump other debug status if necessary */

	return RET_OK;
}

int BE_TOP_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_TOP_PROC_ID_DETAIL_INFO:
		{
			BE_TOP_PrintDrvStatus(m, data);
		}
		break;

		default:
		{

		}
		break;
	}

	/* call chip dependent proc handler */
	BE_TOP_HAL_ProcHandler(proc_id, m, data);

	return RET_OK;
}
