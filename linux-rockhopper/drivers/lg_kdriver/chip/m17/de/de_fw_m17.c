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
#include "de_ipc_def_m17.h"
#include "de_reg_m17.h"
#if (CONFIG_LX_M17_CHIP_FIRMWARE == 1)
#ifdef USE_VIDEO_FOR_FPGA
#include "de_fw_pak_m17c0_fpga.h"
#else
#if defined(INCLUDE_KDRV_SIGNAGE_FHD) || defined(INCLUDE_KDRV_SIGNAGE)
#include "de_fw_pak_m17c0_id_signage.h"
#else
#include "de_fw_pak_m17c0.h"
#endif
#endif
#include "de_fw_pak_m17b0.h"
#endif // #if (CONFIG_LX_M17_CHIP_FIRMWARE == 1)

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
#if (CONFIG_LX_M17_CHIP_FIRMWARE == 1)
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_M17C0[] = {
    { 3, sizeof(gDeFirmwareInDDR_PAK_M17C0),     (char *)gDeFirmwareInDDR_PAK_M17C0  }
};
LX_DE_FW_DWLD_FR_HD_T sDeFirmwareFromHeader_M17B0[] = {
    { 3, sizeof(gDeFirmwareInDDR_PAK_M17B0),     (char *)gDeFirmwareInDDR_PAK_M17B0  }
};
#endif // #if (CONFIG_LX_M17_CHIP_FIRMWARE == 1)

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/

int DE_FW_M17_DownloadFromBin(void)
{
    int ret = RET_OK;

    return ret;
}

int DE_FW_M17_DownloadFromHead(void)
{
    int ret = RET_OK;
#if (CONFIG_LX_M17_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_FR_HD_T *lpDeFirmwareFromHeader = NULL;

	if (lx_chip_rev( ) >= LX_CHIP_REV(M17,C0))
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M17C0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M17C0);
	}
	else
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M17B0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M17B0);
	}
	for (i=0;i<headerSize;i++) {
        ret = DE_REG_M17_FW_Download(&lpDeFirmwareFromHeader[i]);
        if (ret) break;
    }
#endif
    return ret;
}

int DE_FW_M17_Verify(void)
{
    int ret = RET_OK;
#if (CONFIG_LX_M17_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_FR_HD_T *lpDeFirmwareFromHeader = NULL;

	if (lx_chip_rev( ) >= LX_CHIP_REV(M17,C0))
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M17C0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M17C0);
	}
	else
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_M17B0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_M17B0);
	}
    for (i=0;i<headerSize;i++) {
        ret = DE_REG_M17_FW_Verify(&lpDeFirmwareFromHeader[i]);
        if (ret) break;
    }
#endif
    return ret;
}

/**  @} */
