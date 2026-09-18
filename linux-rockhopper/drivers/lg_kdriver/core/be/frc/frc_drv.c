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
 *  frc driver file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.16
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
#include "frc_hal.h"
#include "frc_drv.h"

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
#define	BE_FRC_DBG_STATUS_MEMC_MODE		(1<<0)

	UINT32		status;

	LX_BE_FRC_MEMC_MODE_T	memc_mode_param;
}
BE_FRC_DBG_STATUS_T;

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
static BE_FRC_DBG_STATUS_T	g_be_frc_dbg_status = { .status = 0x0 };

/*========================================================================================
	Implementation Group
========================================================================================*/

int BE_FRC_Init(void)
{
	int ret = RET_OK;

	ret = BE_FRC_HAL_Init();

	return ret;
}

int BE_FRC_Close(void)
{
	int ret = RET_OK;

	ret = BE_FRC_HAL_Close();

	return ret;
}

int BE_FRC_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch (cmd)
	{
		case BE_IOW_FRC_CONTROL_MEMC:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Control_Memc(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_DEMO_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Demo_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_DEBUG_BOX:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Debug_Box(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_BYPASS_MEMC_REG:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Bypass_Memc_Reg(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_YUV_444_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_YUV_444_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_LOW_DELAY:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Low_Delay(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_MOTION_PRO:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Motion_Pro(arg);
			#else
			//Added macro code
			#endif
		}
		break;


		case BE_IOR_FRC_GET_FIRMWARE_VER:
		{

			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Get_Firmware_Ver(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_FORCE_FRAME_RATE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Force_Frame_Rate(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_FREEZE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Freeze(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_FRC_UPDATE_FRAME_DELAY:
		{
			ret = BE_FRC_Update_FrameDelay(arg);
		}
		break;

		case BE_IOW_FRC_SET_CONFIG:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_SetConfig(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_RUN_COMMAND:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_RunCommand(arg);
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

int BE_FRC_Control_Memc(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_MEMC_MODE_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_MEMC_MODE_T *)arg, sizeof(LX_BE_FRC_MEMC_MODE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_ControlMemc(&stParams);
		if (ret) BREAK_WRONG(ret);

		g_be_frc_dbg_status.status |= BE_FRC_DBG_STATUS_MEMC_MODE;
		g_be_frc_dbg_status.memc_mode_param = stParams;

	} while (0);

	return ret;
}

int BE_FRC_Set_Demo_Mode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_DEMO_MODE_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_DEMO_MODE_T *)arg, sizeof(LX_BE_FRC_DEMO_MODE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_Demo_Mode(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Set_Debug_Box(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_ENABLE_DEBUG_BOX_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_ENABLE_DEBUG_BOX_T *)arg, sizeof(LX_BE_FRC_ENABLE_DEBUG_BOX_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_Debug_Box(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Set_Bypass_Memc_Reg(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_MEMC_BYPASS_REGION_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_MEMC_BYPASS_REGION_T *)arg, sizeof(LX_BE_FRC_MEMC_BYPASS_REGION_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_Bypass_Memc_Reg(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Set_YUV_444_Mode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_COLOR_YUV444_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_COLOR_YUV444_T *)arg, sizeof(LX_BE_FRC_COLOR_YUV444_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_YUV_444_Mode(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Set_Low_Delay(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_LOW_DELAY_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_LOW_DELAY_T *)arg, sizeof(LX_BE_FRC_LOW_DELAY_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_Low_Delay(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Set_Motion_Pro(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_MOTION_PRO_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_MOTION_PRO_T *)arg, sizeof(LX_BE_FRC_MOTION_PRO_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_Motion_Pro(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Get_Firmware_Ver(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_VERSION_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_BE_FRC_VERSION_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Get_Firmware_Ver(&stParams);
		if (ret) BREAK_WRONG(ret);

		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_FRC_VERSION_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Force_Frame_Rate(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_FRAME_RATE_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_FRAME_RATE_T *)arg, sizeof(LX_BE_FRC_FRAME_RATE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Force_Frame_Rate(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Set_Freeze(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_FREEZE_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_FREEZE_T *)arg, sizeof(LX_BE_FRC_FREEZE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Set_Freeze(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_Update_FrameDelay(unsigned long arg)
{
	int ret = RET_OK;

	LX_BE_LOW_DELAY_T stParams;

	do{
		ret = copy_from_user(&stParams, (LX_BE_LOW_DELAY_T *)arg, sizeof(LX_BE_LOW_DELAY_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_Update_FrameDelay(&stParams);
		if (ret) BREAK_WRONG(ret);
	}while (0);

	return ret;
}

int BE_FRC_SetConfig(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_CFG_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_CFG_T *)arg, sizeof(LX_BE_FRC_CFG_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_SetConfig(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_FRC_RunCommand(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_FRC_CMD_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_FRC_CMD_T *)arg, sizeof(LX_BE_FRC_CMD_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_FRC_HAL_RunCommand(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

static int BE_FRC_PrintDrvStatus(struct seq_file* m, void* data)
{
	static char* na_str = "n/a";
	static __attribute__((unused)) char* invalid_str = "invalid";

	/* print FRC ffirmware version */
	{
		LX_BE_FRC_VERSION_T fw_ver;

		if (RET_OK == BE_FRC_HAL_Get_Firmware_Ver(&fw_ver))
		{
			seq_printf(m, "fw_ver: %d.%d (0x%04x,0x%04x)\n", fw_ver.u16Version, fw_ver.u16Subversion,
																	fw_ver.u16Version, fw_ver.u16Subversion);
		}
		else
		{
			seq_printf(m, "fw_ver: %s\n", na_str);
		}
	}

	/* print MEMC info */
	if (g_be_frc_dbg_status.status & BE_FRC_DBG_STATUS_MEMC_MODE)
	{
		static char* memc_type_str[] = { "off", "low", "mid", "high", "user", "pulldown55" };
		LX_BE_FRC_MEMC_MODE_T* param = &g_be_frc_dbg_status.memc_mode_param;

		seq_printf(m, "memc_type: %s (0x%x)\n", (param->u8MemcType < NELEMENTS(memc_type_str))? memc_type_str[param->u8MemcType]:invalid_str,
														param->u8MemcType );
		seq_printf(m, "memc_blur_level: 0x%x\n", param->u8Blur);
		seq_printf(m, "memc_judder_level: 0x%x\n", param->u8Judder);
	}
	else
	{
		seq_printf(m, "memc_mem_type: %s\n", na_str);
		seq_printf(m, "memc_blur_level: %s\n", na_str);
		seq_printf(m, "memc_judder_level: %s\n", na_str);
	}

	/* TODO: dump other debug status if necessary */

	return RET_OK;
}

int BE_FRC_ProcHandler(BE_FRC_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_TOP_PROC_ID_DETAIL_INFO:
		{
			BE_FRC_PrintDrvStatus(m, data);
		}
		break;

		default:
		{

		}
		break;
	}

	/* call chip dependent proc handler */
	return BE_FRC_HAL_ProcHandler(proc_id, m, data);
}
