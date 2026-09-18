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
 *  h3d(3d depth) driver file for BE device
 *
 *  author		won.hur
 *  version		1.0
 *  date		2012.04.27
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
#include "be_def.h"

#include "be_kapi.h"
#include "h3d_hal.h"
#include "h3d_drv.h"

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
	UINT32	status;

#define BE_H3D_DBG_STATUS_SET_MODE					(1<<0)
#define BE_H3D_DBG_STATUS_T3C_DEPTH					(1<<1)
#define BE_H3D_DBG_STATUS_A3C_DEPTH					(1<<2)
#define BE_H3D_DBG_STATUS_A3C_AUTO_CONVERGENCE		(1<<3)
#define BE_H3D_DBG_STATUS_TRID_FORMAT				(1<<4)

	LX_BE_H3D_MODE_T				mode_param;
	LX_BE_H3D_T3C_DEPTH_LEVEL_T 	t3c_depth_param;
	LX_BE_H3D_A3C_DEPTH_LEVEL_T 	a3c_depth_param;
	LX_BE_H3D_A3C_AUTOCONVERGENCE_T a3c_auto_convergence_param;
	LX_BE_TRIDTV_FMT_CTRL_T 		trid_fmt_param;
}
BE_H3D_DBG_STATUS_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static BE_H3D_DBG_STATUS_T	g_be_h3d_dbg_status = { .status = 0x0 };

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_H3D_Init(void)
{
	int ret = RET_OK;

	ret = BE_H3D_HAL_Init();

	return ret;
}

int BE_H3D_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOW_H3D_SET_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_GET_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Get_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_T3C_DEPTH_LEVEL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_T3C_Depth_Level(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_A3C_DEPTH_LEVEL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_A3C_Depth_Level(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_A3C_AUTOCONVERGENCE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_A3C_AutoConvergence(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_SET_TRIDFMT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Set_Trid_Fmt(arg);
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

int BE_H3D_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_H3D_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_H3D_MODE_T *)arg, sizeof(LX_BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_H3D_HAL_Set_Mode(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_h3d_dbg_status.status |= BE_H3D_DBG_STATUS_SET_MODE;
		g_be_h3d_dbg_status.mode_param = stParams;

	} while(0);
	return ret;
}

int BE_H3D_Get_Mode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_H3D_MODE_T stParams;

	do{
		ret = BE_H3D_HAL_Get_Mode(&stParams);
		ret = copy_to_user((LX_BE_H3D_MODE_T *)arg, &stParams, sizeof(LX_BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);

	} while(0);
	return ret;
}

int BE_H3D_T3C_Depth_Level(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_H3D_T3C_DEPTH_LEVEL_T stParams;

	do{
		ret = copy_from_user(&stParams,(LX_BE_H3D_T3C_DEPTH_LEVEL_T *)arg, sizeof(LX_BE_H3D_T3C_DEPTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_H3D_HAL_T3C_Depth_Level(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_h3d_dbg_status.status |= BE_H3D_DBG_STATUS_T3C_DEPTH;
		g_be_h3d_dbg_status.t3c_depth_param = stParams;

	} while(0);
	return ret;
}

int BE_H3D_A3C_Depth_Level(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_H3D_A3C_DEPTH_LEVEL_T stParams;

	do{
		ret = copy_from_user(&stParams,(LX_BE_H3D_A3C_DEPTH_LEVEL_T *)arg, sizeof(LX_BE_H3D_A3C_DEPTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_H3D_HAL_A3C_Depth_Level(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_h3d_dbg_status.status |= BE_H3D_DBG_STATUS_A3C_DEPTH;
		g_be_h3d_dbg_status.a3c_depth_param = stParams;

	} while(0);
	return ret;
}

int BE_H3D_A3C_AutoConvergence(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_H3D_A3C_AUTOCONVERGENCE_T stParams;

	do{
		ret = copy_from_user(&stParams,(LX_BE_H3D_A3C_AUTOCONVERGENCE_T *)arg, sizeof(LX_BE_H3D_A3C_AUTOCONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);

		ret =  BE_H3D_HAL_A3C_AutoConvergence(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_h3d_dbg_status.status |= BE_H3D_DBG_STATUS_A3C_AUTO_CONVERGENCE;
		g_be_h3d_dbg_status.a3c_auto_convergence_param = stParams;

	} while(0);
	return ret;
}

int BE_H3D_Set_Trid_Fmt( unsigned long arg)
{

	int ret = RET_OK;
	LX_BE_TRIDTV_FMT_CTRL_T stParams;

	do{
		ret = copy_from_user(&stParams,(LX_BE_TRIDTV_FMT_CTRL_T *)arg, sizeof(LX_BE_TRIDTV_FMT_CTRL_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_H3D_HAL_Set_Trid_Fmt(&stParams);
		if(ret) BREAK_WRONG(ret);

		g_be_h3d_dbg_status.status |= BE_H3D_DBG_STATUS_TRID_FORMAT;
		g_be_h3d_dbg_status.trid_fmt_param = stParams;

	} while(0);
	return ret;
}

static int BE_H3D_PrintDrvStatus(struct seq_file* m, void* data)
{
	char* na_str = "n/a";
	__attribute__((unused)) char* invalid_str = "invalid";

	if (g_be_h3d_dbg_status.status & BE_H3D_DBG_STATUS_SET_MODE)
	{
		LX_BE_H3D_MODE_T* param = &g_be_h3d_dbg_status.mode_param;

		seq_printf(m, "a3c_mode: %s (0x%x)\n", (param->bA3CMode)?"on":"off", param->bA3CMode);
		seq_printf(m, "t3c_mode: %s (0x%x)\n", (param->bT3CMode)?"on":"off", param->bT3CMode);
	}
	else
	{
		seq_printf(m, "a3c_mode: %s\n", na_str);
		seq_printf(m, "t3c_mode: %s\n", na_str);
	}

	if (g_be_h3d_dbg_status.status & BE_H3D_DBG_STATUS_T3C_DEPTH)
	{
		LX_BE_H3D_T3C_DEPTH_LEVEL_T* param = &g_be_h3d_dbg_status.t3c_depth_param;
		seq_printf(m, "t3c_depth_level: %d (0x%x)\n", param->u32T3CDepthLevel, param->u32T3CDepthLevel);
	}
	else
	{
		seq_printf(m, "t3c_depth_level: %s\n", na_str);
	}
	if (g_be_h3d_dbg_status.status & BE_H3D_DBG_STATUS_A3C_DEPTH)
	{
		LX_BE_H3D_A3C_DEPTH_LEVEL_T* param = &g_be_h3d_dbg_status.a3c_depth_param;
		seq_printf(m, "a3c_depth_level: %d (0x%x)\n", param->u32A3CDepthLevel, param->u32A3CDepthLevel);
	}
	else
	{
		seq_printf(m, "a3c_depth_level: %s\n", na_str);
	}

	if (g_be_h3d_dbg_status.status & BE_H3D_DBG_STATUS_A3C_AUTO_CONVERGENCE)
	{
		LX_BE_H3D_A3C_AUTOCONVERGENCE_T* param = &g_be_h3d_dbg_status.a3c_auto_convergence_param;
		seq_printf(m, "a3c_auto_convergence: %s (0x%x)\n", (param->bA3CAutoConvergence)? "on":"off",
																param->bA3CAutoConvergence);
	}
	else
	{
		seq_printf(m, "a3c_auto_convergence: %s\n", na_str);
	}

	if (g_be_h3d_dbg_status.status & BE_H3D_DBG_STATUS_TRID_FORMAT)
	{
		LX_BE_TRIDTV_FMT_CTRL_T* param = &g_be_h3d_dbg_status.trid_fmt_param;

		seq_printf(m, "trid_fmt.mode: 0x%x\n", param->lx_mode);
		seq_printf(m, "trid_fmt.sc_output_type: 0x%x\n", param->lx_in_fmt);
		seq_printf(m, "trid_fmt.lr_seq: 0x%x\n", param->lx_lr);
		seq_printf(m, "trid_fmt.depth_ctrl: %d (0x%x)\n", param->depthCtrl, param->depthCtrl);
		seq_printf(m, "trid_fmt.conv_ctrl: %d (0x%x)\n", param->convCtrl, param->convCtrl);
		seq_printf(m, "trid_fmt.auto_conv_mode: %s (0x%x)\n", (param->bAutoConvMode)? "on":"off", param->bAutoConvMode);
	}
	else
	{
		seq_printf(m, "trid_fmt.mode: %s\n", na_str);
		seq_printf(m, "trid_fmt.sc_output_type: %s\n", na_str);
		seq_printf(m, "trid_fmt.lr_seq: %s\n", na_str);
		seq_printf(m, "trid_fmt.depth_ctrl: %s\n", na_str);
		seq_printf(m, "trid_fmt.conv_ctrl: %s\n", na_str);
		seq_printf(m, "trid_fmt.auto_conv_mode: %s\n", na_str);
	}

	/* TODO: dump other debug status if necessary */

	return RET_OK;
}

int BE_H3D_ProcHandler( BE_H3D_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_H3D_PROC_ID_DETAIL_INFO:
		{
			BE_H3D_PrintDrvStatus(m,data);
		}
		break;

		default:
		{

		}
		break;
	}

	/* call chip dependent proc handler */
	BE_H3D_HAL_ProcHandler(proc_id, m, data);

	return RET_OK;
}


