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
#include "de_ipc_def_m19.h"
#include "de_reg_m19.h"
#if (CONFIG_LX_M19_CHIP_FIRMWARE == 1)
#ifdef USE_VIDEO_FOR_FPGA
#include "de_fw_pak_m19a0_fpga.h"
#else
#include "de_fw_pak_m19a0.h"
#include "de_fw_pak_m19a0_y20.h"
#endif
#endif // #if (CONFIG_LX_M19_CHIP_FIRMWARE == 1)

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
#if (CONFIG_LX_M19_CHIP_FIRMWARE == 1)
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_M19A0[] = {
    { 0, 0, sizeof(gDeFirmwareInDDR_PAK_M19A0),     (char *)gDeFirmwareInDDR_PAK_M19A0  }
};
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_M19A0_Y20[] = {
	{ 0, 0, sizeof(gDeFirmwareInDDR_PAK_M19A0_Y20), (char *)gDeFirmwareInDDR_PAK_M19A0_Y20 }
};
#endif // #if (CONFIG_LX_M19_CHIP_FIRMWARE == 1)

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/

int DE_FW_M19_DownloadFromBin(void)
{
    int ret = RET_OK;

    return ret;
}

static int _get_fwopt(void)
{
	int pqefw = 0;
	char hw_opt[24];

	if (RET_OK==OS_ScanKernelCmdline("dispopts=%s", hw_opt))
	{
		if(strstr(hw_opt,"pqegps"))
		{
			pqefw  = 1;
		}
	}
	DE_NOTI("support y20_gp_scaler ? => %s", pqefw?"YES":"NO");
	return pqefw;
}


int DE_FW_M19_DownloadFromHead(LX_DE_FW_DWLD_T *pstParams)
{
    int ret = RET_OK;
#if (CONFIG_LX_M19_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_FR_HD_T *lpDeFirmwareFromHeader = NULL;

	if (!pstParams)	{DE_ERROR("pstParams is null\n");return RET_ERROR;}

	if (pstParams->inx!=0)	{DE_NOTI("not support(%d)\n",pstParams->inx);return RET_OK;}

	if(_get_fwopt()) {
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M19A0_Y20;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M19A0_Y20);
	}
	else {
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M19A0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M19A0);
	}
	
	for (i=0;i<headerSize;i++) {
		lpDeFirmwareFromHeader[i].cfg = pstParams->cfg;
        ret = DE_REG_M19_FW_Download((LX_DE_FW_DWLD_T *)&(lpDeFirmwareFromHeader[i]));
        if (ret) break;
    }
#endif
    return ret;
}

int DE_FW_M19_Verify(void)
{
    int ret = RET_OK;
#if (CONFIG_LX_M19_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_FR_HD_T *lpDeFirmwareFromHeader = NULL;

	if(_get_fwopt()) {
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M19A0_Y20;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M19A0_Y20);
	}
	else {
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M19A0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M19A0);
	}

	for (i=0;i<headerSize;i++) {
		lpDeFirmwareFromHeader[i].cfg = 0;
        ret = DE_REG_M19_FW_Verify((LX_DE_FW_DWLD_T *)&(lpDeFirmwareFromHeader[i]));
        if (ret) break;
    }
#endif
    return ret;
}

/**  @} */
