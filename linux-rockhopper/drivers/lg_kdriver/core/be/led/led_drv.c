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
 *  led(dppb) driver file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.06
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
#include "led_drv.h"
#include "led_hal.h"

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
#define	BE_LED_DBG_STATUS_LED_MODE	(1<<0)
#define	BE_LED_DBG_STATUS_LED_CTRL	(1<<1)
#define	BE_LED_DBG_STATUS_WCG_MODE	(1<<2)
#define	BE_LED_DBG_STATUS_WCG_CTRL	(1<<3)

	UINT32					status;

	LX_BE_LED_MODE_T 		led_mode_param;
	LX_BE_LED_CONTROL_T 	led_ctrl_param;
	LX_BE_WCG_MODE_T 		wcg_mode_param;
	LX_BE_WCG_CONTROL_T 	wcg_ctrl_param;
}
BE_LED_DBG_STATUS_T;

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
static BE_LED_DBG_STATUS_T	g_be_led_dbg_status = { .status = 0x0 };

/*========================================================================================
	Implementation Group
========================================================================================*/

int BE_LED_Init(void)
{
	int ret = RET_OK;

	ret = BE_LED_HAL_Init();

	return ret;
}

int BE_LED_Close(void)
{
	int ret = RET_OK;

	ret = BE_LED_HAL_Close();

	return ret;
}

int BE_LED_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch (cmd)
	{
		case BE_IOR_LED_GET_VERSION:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_SET_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_CONTROL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_GET_APL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Get_Apl(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_SET_CLIPPING_VALUE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Set_ClippingValue(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_UPDATE_SENSOR_LUX_INFO:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Update_SensorLuxInfo(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_GET_REG_INFO:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Get_RegInfo(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_SET_UCR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Set_Ucr(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_WCG_CALC_FW_LUT_SIZE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Calculate_FWLutSize(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_WCG_GET_FW_LUT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Get_FWLut(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_WCG_GET_VERSION:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_WCG_SET_MODE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_WCG_CONTROL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_DPG:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_Dpg(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_PCC:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_Pcc(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_GAMMA:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_Gamma(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_DEGAMMA:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_DeGamma(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_PCC_GAMMA:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_PccGamma(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_PCC_MUX_BLEND:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_PccMuxBlend(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_PQ_SET_LUMINENCE_BOOST:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_PQ_Set_LuminenceBoost(arg);
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

int BE_LED_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LED_VERSION_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_BE_LED_VERSION_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_LED_HAL_Get_Version(&stParams);
		if (ret) BREAK_WRONG(ret);

		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_LED_VERSION_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_LED_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LED_MODE_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_LED_MODE_T *)arg, sizeof(LX_BE_LED_MODE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_LED_HAL_Set_Mode(&stParams);
		if (ret) BREAK_WRONG(ret);

		g_be_led_dbg_status.status |= BE_LED_DBG_STATUS_LED_MODE;
		g_be_led_dbg_status.led_mode_param = stParams;

	} while (0);

	return ret;
}

int BE_LED_Control(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LED_CONTROL_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_LED_CONTROL_T *)arg, sizeof(LX_BE_LED_CONTROL_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_LED_HAL_Control(&stParams);
		if (ret) BREAK_WRONG(ret);

		g_be_led_dbg_status.status |= BE_LED_DBG_STATUS_LED_CTRL;
		g_be_led_dbg_status.led_ctrl_param = stParams;

	} while (0);

	return ret;
}

int BE_LED_Get_Apl(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LED_APL_T stParams;

	do {
		ret = BE_LED_HAL_Get_Apl(&stParams);
		if (ret) BREAK_WRONG(ret);

		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_LED_APL_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_LED_Set_ClippingValue(unsigned long arg)
{
	int ret = RET_OK;
	UINT32 param;

	do {
		ret = copy_from_user(&param, (UINT32 *)arg, sizeof(UINT32));
		if (ret) BREAK_WRONG(ret);

		ret = BE_LED_HAL_Set_ClippingValue(param);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_LED_Update_SensorLuxInfo(unsigned long arg)
{
	int ret = RET_OK;
	UINT32 param;

	do {
		ret = copy_from_user(&param, (UINT32 *)arg, sizeof(UINT32));
		if (ret) BREAK_WRONG(ret);

		ret = BE_LED_HAL_Update_SensorLuxInfo(param);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_LED_Get_RegInfo(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LED_REG_INFO_T stParams;

	do {
		ret = BE_LED_HAL_Get_RegInfo(&stParams);
		if (ret) BREAK_WRONG(ret);

		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_LED_REG_INFO_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_LED_Set_Ucr(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_LED_UCR_PARAM_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_LED_UCR_PARAM_T *)arg, sizeof(LX_BE_LED_UCR_PARAM_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_LED_HAL_Set_Ucr(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}


int BE_WCG_Calculate_FWLutSize(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_WCG_CALC_FW_LUT_SIZE_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_BE_WCG_CALC_FW_LUT_SIZE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_WCG_HAL_Calculate_FWLutSize(&stParams);
		if (ret) BREAK_WRONG(ret);

		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_WCG_CALC_FW_LUT_SIZE_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_WCG_Get_FWLut(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_WCG_FW_LUT_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_BE_WCG_FW_LUT_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_WCG_HAL_Get_FWLut(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_WCG_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_WCG_VERSION_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_BE_WCG_VERSION_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_WCG_HAL_Get_Version(&stParams);
		if (ret) BREAK_WRONG(ret);

		ret = copy_to_user((void __user *)arg, &stParams, sizeof(LX_BE_WCG_VERSION_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_WCG_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_WCG_MODE_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_WCG_MODE_T *)arg, sizeof(LX_BE_WCG_MODE_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_WCG_HAL_Set_Mode(&stParams);
		if (ret) BREAK_WRONG(ret);

		g_be_led_dbg_status.status |= BE_LED_DBG_STATUS_WCG_MODE;
		g_be_led_dbg_status.wcg_mode_param = stParams;

	} while (0);

	return ret;
}

int BE_WCG_Control(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_WCG_CONTROL_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_WCG_CONTROL_T *)arg, sizeof(LX_BE_WCG_CONTROL_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_WCG_HAL_Control(&stParams);
		if (ret) BREAK_WRONG(ret);

		g_be_led_dbg_status.status |= BE_LED_DBG_STATUS_WCG_CTRL;
		g_be_led_dbg_status.wcg_ctrl_param = stParams;

	} while (0);

	return ret;
}

int BE_PQ_Set_Dpg(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_PQ_DPG_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_PQ_DPG_T *)arg, sizeof(LX_BE_PQ_DPG_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_Dpg(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_PQ_Set_Pcc(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_PQ_PCC_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_PQ_PCC_T *)arg, sizeof(LX_BE_PQ_PCC_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_Pcc(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_PQ_Set_Gamma(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN param;

	do {
		ret = copy_from_user(&param, (BOOLEAN *)arg, sizeof(BOOLEAN));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_Gamma(param);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_PQ_Set_DeGamma(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN param;

	do {
		ret = copy_from_user(&param, (BOOLEAN *)arg, sizeof(BOOLEAN));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_DeGamma(param);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_PQ_Set_PccGamma(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_PQ_PCC_GAMMA_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_PQ_PCC_GAMMA_T *)arg, sizeof(LX_BE_PQ_PCC_GAMMA_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_PccGamma(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_PQ_Set_PccMuxBlend(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_PQ_PCC_MUX_BLEND_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_PQ_PCC_MUX_BLEND_T *)arg, sizeof(LX_BE_PQ_PCC_MUX_BLEND_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_PccMuxBlend(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

int BE_PQ_Set_LuminenceBoost(unsigned long arg)
{
	int ret = RET_OK;
	LX_BE_PQ_LUT_T stParams;

	do {
		ret = copy_from_user(&stParams, (LX_BE_PQ_LUT_T *)arg, sizeof(LX_BE_PQ_LUT_T));
		if (ret) BREAK_WRONG(ret);

		ret = BE_PQ_HAL_Set_LuminenceBoost(&stParams);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

static int BE_LED_PrintDrvStatus(struct seq_file* m, void* data)
{
	char* na_str = "n/a";
	__attribute__((unused)) char* invalid_str = "invalid";

	{
		LX_BE_LED_VERSION_T led_ver;

		if (RET_OK == BE_LED_HAL_Get_Version(&led_ver))
		{
			seq_printf(m, "version.lut_version; 0x%x\n", led_ver.u8LEDLutVersion);
			seq_printf(m, "version.sub_version; 0x%x\n", led_ver.u8LEDSubVersion);
			seq_printf(m, "version.panel_size; 0x%x\n", led_ver.u8PanelSize);
			seq_printf(m, "version.panel_type; 0x%x\n", led_ver.u8PanelType);
		}
		else
		{
			seq_printf(m, "version.lut_version; %s\n", na_str);
			seq_printf(m, "version.sub_version; %s\n", na_str);
			seq_printf(m, "version.panel_size; %s\n", na_str);
			seq_printf(m, "version.panel_type; %s\n", na_str);
		}
	}

	if (g_be_led_dbg_status.status & BE_LED_DBG_STATUS_LED_MODE )
	{
		char* str_lst[] = { "lowest", "low", "medium", "high" };

		LX_BE_LED_MODE_T* param = &g_be_led_dbg_status.led_mode_param;
		seq_printf(m, "led_mode: %s (0x%x)\n",
							(param->u32PictureMode < NELEMENTS(str_lst))? str_lst[param->u32PictureMode]:invalid_str,
							param->u32PictureMode);
	}
	else
	{
		seq_printf(m, "led_mode: %s\n", na_str);
	}

	if (g_be_led_dbg_status.status & BE_LED_DBG_STATUS_LED_CTRL )
	{
		char* str_lst[] = { "off(smooth)", "on(smooth)", "off(instant)", "on(instant)" };

		LX_BE_LED_CONTROL_T* param = &g_be_led_dbg_status.led_ctrl_param;
		seq_printf(m, "led_ctrl: %s (0x%x)\n",
							(param->u32DimminOn < NELEMENTS(str_lst))? str_lst[param->u32DimminOn]:invalid_str,
							param->u32DimminOn);
		seq_printf(m, "led_ctrl.store_mode: %s (0x%x)\n",
							(param->u32StoreMode)? "on":"off", param->u32StoreMode);
		seq_printf(m, "led_ctrl.bpl_on: %s (0x%x)\n",
							(param->u32BplOn)? "on":"off", param->u32BplOn);
	}
	else
	{
		seq_printf(m, "led_ctrl.dimming_mode: %s\n", na_str);
		seq_printf(m, "led_ctrl.store_mode: %s\n", na_str);
	}

	if (g_be_led_dbg_status.status & BE_LED_DBG_STATUS_WCG_MODE )
	{
		LX_BE_WCG_MODE_T* param = &g_be_led_dbg_status.wcg_mode_param;
		seq_printf(m, "wcg_mode.picture_Mode: %d\n", param->u32PictureMode);
	}
	else
	{
		seq_printf(m, "wcg_mode.picture_Mode: %s\n", na_str);
	}

	if (g_be_led_dbg_status.status & BE_LED_DBG_STATUS_WCG_CTRL )
	{
		LX_BE_WCG_CONTROL_T* param = &g_be_led_dbg_status.wcg_ctrl_param;
		seq_printf(m, "wcg_ctrl.enable: %d\n", param->u32Enable);
	}
	else
	{
		seq_printf(m, "wcg_ctrl.enable: %s\n", na_str);
	}

	return RET_OK;
}

int BE_LED_ProcHandler(BE_LED_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_LED_PROC_ID_DETAIL_INFO:
		{
			BE_LED_PrintDrvStatus(m, data);
		}
		break;

		default: break;
	}

	return BE_LED_HAL_ProcHandler(proc_id, m, data);
}

