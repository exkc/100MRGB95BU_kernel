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

#ifdef USE_KDRV_CODES_FOR_O18
#include "de_def.h"
#include "de_hal_def.h"
#include "mcu/de_int_def.h"
#include "mcu/de_fw_def.h"
#include "mcu/de_fw.h"
#include "de_ipc_def_o18.h"
#include "de_reg_o18.h"
#if (CONFIG_LX_O18_CHIP_FIRMWARE == 1)
#ifdef USE_VIDEO_FOR_FPGA
#include "de_fw_pak_o18a0_FPGA.h"
#else
#include "de_fw_pak_o18a0.h"
#endif
#endif // #if (CONFIG_LX_O18_CHIP_FIRMWARE == 1)

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
#if (CONFIG_LX_O18_CHIP_FIRMWARE == 1)
LX_DE_FW_DWLD_T sDeFirmwareFromHeader_O18A0[] = {
    { 3, 0, sizeof(gDeFirmwareInDDR_PAK_O18A0),     (char *)gDeFirmwareInDDR_PAK_O18A0       },
#ifdef ENABLE_O18_MCU1
    { 4, 0, sizeof(gDeFirmwareInDDR_PAK_O18A0_MCU1),(char *)gDeFirmwareInDDR_PAK_O18A0_MCU1  }
#endif
};
#endif // #if (CONFIG_LX_O18_CHIP_FIRMWARE == 1)

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/

int DE_FW_O18_DownloadFromBin(void)
{
    int ret = RET_OK;

    return ret;
}

int DE_FW_O18_DownloadFromHead(LX_DE_FW_DWLD_T *pstParams)
{
    int ret = RET_OK;
#if (CONFIG_LX_O18_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_T *lpDeFirmwareFromHeader = NULL;

	if (!pstParams)	{DE_ERROR("pstParams is null\n");return RET_ERROR;}

	if (pstParams->inx>0)	{DE_NOTI("not support(%d)\n",pstParams->inx);return RET_OK;}

	if (lx_chip_rev( ) >= LX_CHIP_REV(O18,A0))
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O18A0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O18A0);
	}
	for (i=0;i<headerSize;i++) {
        ret = DE_REG_O18_FW_Download(&lpDeFirmwareFromHeader[i]);
        if (ret) break;
    }
#endif
    return ret;
}

int DE_FW_O18_Verify(void)
{
    int ret = RET_OK;
#if (CONFIG_LX_O18_CHIP_FIRMWARE == 1)
	int i;
	int headerSize = 0;
    LX_DE_FW_DWLD_T *lpDeFirmwareFromHeader = NULL;

	if (lx_chip_rev( ) >= LX_CHIP_REV(O18,A0))
	{
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_O18A0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_O18A0);
	}
    for (i=0;i<headerSize;i++) {
        ret = DE_REG_O18_FW_Verify(&lpDeFirmwareFromHeader[i]);
        if (ret) break;
    }
#endif
    return ret;
}
#endif

/**  @} */
