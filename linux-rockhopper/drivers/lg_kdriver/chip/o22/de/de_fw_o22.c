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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.07.16
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "base_types.h"
#include "os_util.h"
#include "proc_util.h"

#include "de_kapi.h"
#include "de_model.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "de_hal_def.h"
#include "mcu/de_int_def.h"
#include "mcu/de_fw_def.h"
#include "mcu/de_fw.h"
#include "de_ipc_def_o22.h"
#include "de_reg_o22.h"
#include "de_cfg_o22.h"
#include "de_fw_o22.h"

#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)
#ifdef USE_VIDEO_FOR_FPGA
#include "de_fw_pak_o22a0_fpga.h"
#else

#ifdef BUILD_FEATURE_y26_board
#include "de_fw_pak_o22a0_y25_o22n3.h"
#elif defined BUILD_FEATURE_y25_board
#include "de_fw_pak_o22a0_y25_o22n3.h"
#elif defined BUILD_FEATURE_y24_board
#include "de_fw_pak_o22a0_y25_o22n2.h"
#elif defined BUILD_FEATURE_y23_board
#include "de_fw_pak_o22a0_y25_o22n.h"
#elif defined BUILD_FEATURE_y22_board
#include "de_fw_pak_o22a0_y25_o22.h"
#else
#include "de_fw_pak_o22a0.h"
#endif

#endif
#include "de_fw1_pak_o22a0.h"
#include "de_fw2_pak_o22a0.h"
#include "de_fw3_pak_o22a0.h"
#include "de_fw4_pak_o22a0.h"
#endif // #if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_O22A0[] = {
#ifdef BUILD_FEATURE_y26_board
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_y25_o22n3), (char *)gDeFirmwareInDDR_PAK_O22A0_y25_o22n3  }
#elif defined BUILD_FEATURE_y25_board
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_y25_o22n3), (char *)gDeFirmwareInDDR_PAK_O22A0_y25_o22n3  }
#elif defined BUILD_FEATURE_y24_board
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_y25_o22n2), (char *)gDeFirmwareInDDR_PAK_O22A0_y25_o22n2  }
#elif defined BUILD_FEATURE_y23_board
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_y25_o22n), (char *)gDeFirmwareInDDR_PAK_O22A0_y25_o22n  }
#elif defined BUILD_FEATURE_y22_board
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_y25_o22), (char *)gDeFirmwareInDDR_PAK_O22A0_y25_o22  }
#else
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0), (char *)gDeFirmwareInDDR_PAK_O22A0  }
#endif
};
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_O22A0_MCU1[] = {
    { 1, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_MCU1),     (char *)gDeFirmwareInDDR_PAK_O22A0_MCU1  }
};
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_O22A0_MCU2[] = {
    { 2, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_MCU2),     (char *)gDeFirmwareInDDR_PAK_O22A0_MCU2  }
};
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_O22A0_MCU3[] = {
    { 3, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_MCU3),     (char *)gDeFirmwareInDDR_PAK_O22A0_MCU3  }
};
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_O22A0_MCU4[] = {
    { 4, 0, sizeof(gDeFirmwareInDDR_PAK_O22A0_MCU4),     (char *)gDeFirmwareInDDR_PAK_O22A0_MCU4  }
};
#endif // #if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/

int DE_FW_O22_DownloadFromBin(void)
{
    int ret = RET_OK;

    return ret;
}

int DE_FW_O22_DownloadFromHead(LX_DE_FW_DWLD_T *pstParams)
{
    int ret = RET_OK;
#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
	__attribute__((unused)) UINT32 year = 0;
	LX_DE_IPC_SYSTEM_MODEL_T system = {.u32Data = 0,};
	LX_DE_FW_DWLD_FR_HD_T *lpDeFirmwareFromHeader = NULL;

	if (!pstParams)	{DE_ERROR("pstParams is null\n");return RET_ERROR;}

#ifdef BUILD_FEATURE_y29_board
	year = 29;
#elif defined BUILD_FEATURE_y28_board
	year = 28;
#elif defined BUILD_FEATURE_y27_board
	year = 27;
#elif defined BUILD_FEATURE_y26_board
	year = 26;
#elif defined BUILD_FEATURE_y25_board
	year = 25;
#elif defined BUILD_FEATURE_y24_board
	year = 24;
#elif defined BUILD_FEATURE_y23_board
	year = 23;
#elif defined BUILD_FEATURE_y22_board
	year = 22;
#endif

	de_cfg_o22_get_hw_opt(&system.u32Data);
	DE_NOTI("panel_resolution:%d, year:%d\n",system.panel_resolution,year);
	if (pstParams->inx==0)
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O22A0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O22A0);
	}
	else if (pstParams->inx==1)
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O22A0_MCU1;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O22A0_MCU1);
	}
	else if (pstParams->inx==2)
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O22A0_MCU2;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O22A0_MCU2);
	}
	else if (pstParams->inx==3)
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O22A0_MCU3;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O22A0_MCU3);
	}
	else if (pstParams->inx==4)
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O22A0_MCU4;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O22A0_MCU4);
	}
	else
	{
		lpDeFirmwareFromHeader = NULL;
		headerSize = 0;
	}

	if (lpDeFirmwareFromHeader != NULL && headerSize > 0)
	{
		for (i=0;i<headerSize;i++) {
			lpDeFirmwareFromHeader[i].cfg = pstParams->cfg;
	        ret = DE_REG_O22_FW_Download((LX_DE_FW_DWLD_T *)&(lpDeFirmwareFromHeader[i]));
	        if (ret) break;
	    }
	}
	else
	{
		DE_NOTI("not support(%d)\n",pstParams->inx);
		return RET_OK;
	}
#endif
    return ret;
}

int DE_FW_O22_Verify(void)
{
    int ret = RET_OK;
#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_FR_HD_T *lpDeFirmwareFromHeader = NULL;

	lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O22A0;
	headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O22A0);

	for (i=0;i<headerSize;i++) {
		lpDeFirmwareFromHeader[i].cfg = 0;
        ret = DE_REG_O22_FW_Verify((LX_DE_FW_DWLD_T *)&(lpDeFirmwareFromHeader[i]));
        if (ret) break;
    }
#endif
    return ret;
}

/**  @} */
