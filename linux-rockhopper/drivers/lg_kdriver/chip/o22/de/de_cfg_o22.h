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
 * date       2011.04.06
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DE_CFG_O22_INC
#define  DE_CFG_O22_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_model.h"
#include "de_ver_def.h"
#include "de_cfg_def_o22.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#if 0	//not used
#define VIDEO_O22_FRAME_DDR_LW_SCR          783
#define VIDEO_O22_FRAME_DDR_LW_CAP          348
#define VIDEO_O22_FRAME_DDR_LW_TNR_IPC      870
#define VIDEO_O22_FRAME_DDR_RW_SCR          783
#define VIDEO_O22_FRAME_DDR_RW_CAP          348
#define VIDEO_O22_FRAME_DDR_RW_TNR_IPC      696
#define VIDEO_O22_FRAME_DDR_SW_VCR          228
#define VIDEO_O22_FRAME_DDR_SW_MDI          138
#define VIDEO_O22_FRAME_DDR_LW_TNM          69
#define VIDEO_O22_FRAME_DDR_LW_CSC          416

#define VIDEO_O22_CODEC_DDR_BASE            (0x70000000)
#define VIDEO_O22_LOWER_DDR_BASE            (0x80000000)

#if (CONFIG_LX_BOARD_FPGA==1)
#define VIDEO_O22_FRAME_DDR_BASE            (0xA0000000)		/* FPGA board */
#else
#define VIDEO_O22_FRAME_DDR_BASE            (0x80000000)		/* SYSTEM board */
#endif
#define VIDEO_O22_FRAME_FIRMWARE_OFFSET     (0x00000000)

#define VIDEO_O22_CODEC_DDR_OFFSET          (0x2000000)

#define VIDEO_O22_ROW2PHY(_r)               (CONV_MEM_ROW2BYTE(_r) | g_FwBase_O22)

#define VIDEO_O22_FIRMWARE_ROW_SIZE_OF_DE   (VIDEO_MEM_FIRMWARE_ROW_SIZE*2)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_OF_LED  (VIDEO_MEM_FIRMWARE_ROW_SIZE)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_OF_IPC  (VIDEO_MEM_FIRMWARE_ROW_SIZE)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_IPC_MC	(1)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_DDR_UP	(1)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_OF_TTX	(1)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_WEB_OS	(1)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_REG_TR	(1)
#define VIDEO_O22_FIRMWARE_ROW_SIZE_DOLBY_HDR	(1)

#define VIDEO_O22_FIRMWARE_ROW_BASE_OF_DE	(VIDEO_O22_FRAME_FIRMWARE_OFFSET/VIDEO_ROW_STRIDE)
#define VIDEO_O22_FIRMWARE_ROW_BASE_OF_LED	(VIDEO_O22_FIRMWARE_ROW_BASE_OF_DE  + VIDEO_O22_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_O22_FIRMWARE_ROW_BASE_OF_IPC	(VIDEO_O22_FIRMWARE_ROW_BASE_OF_LED + VIDEO_O22_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_O22_START_OF_FRAME_MEMORY		(VIDEO_O22_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_O22_FIRMWARE_ROW_SIZE_OF_IPC)

#define VIDEO_O22_ROW_SIZE_OF_FRAME_MEMORY  (VIDEO_O22_FRAME_DDR_LW_SCR + VIDEO_O22_FRAME_DDR_LW_TNR_IPC + VIDEO_O22_FRAME_DDR_RW_SCR + VIDEO_O22_FRAME_DDR_RW_TNR_IPC + VIDEO_O22_FRAME_DDR_SW_VCR + VIDEO_O22_FRAME_DDR_LW_TNM)
#define VIDEO_O22_ROW_SIZE_OF_FRAME_PREW    (VIDEO_O22_FRAME_DDR_LW_CAP + VIDEO_O22_FRAME_DDR_RW_CAP + 32)
#define VIDEO_O22_ROW_SIZE_OF_FRAME_GRAP    (VIDEO_O22_FRAME_DDR_SW_MDI)
#define VIDEO_O22_ROW_SIZE_OF_FRAME_GCSC    (VIDEO_O22_FRAME_DDR_LW_CSC)

#define VIDEO_O22_FIRMWARE_ROW_BASE_IPC_MC	(VIDEO_O22_FIRMWARE_ROW_BASE_OF_IPC                                     )
#define VIDEO_O22_FIRMWARE_ROW_BASE_DDR_UP	(VIDEO_O22_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_O22_FIRMWARE_ROW_SIZE_IPC_MC)
#define VIDEO_O22_FIRMWARE_ROW_BASE_OF_TTX	(VIDEO_O22_FIRMWARE_ROW_BASE_DDR_UP + VIDEO_O22_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_O22_FIRMWARE_ROW_BASE_WEB_OS	(VIDEO_O22_FIRMWARE_ROW_BASE_OF_TTX + VIDEO_O22_FIRMWARE_ROW_SIZE_OF_TTX)
#define VIDEO_O22_FIRMWARE_ROW_BASE_REG_TR	(VIDEO_O22_FIRMWARE_ROW_BASE_WEB_OS + VIDEO_O22_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_O22_FIRMWARE_ROW_BASE_DOLBY_HDR	(VIDEO_O22_FIRMWARE_ROW_BASE_REG_TR + VIDEO_O22_FIRMWARE_ROW_SIZE_REG_TR)

#define VIDEO_O22_FIRMWARE_MEM_BASE_OF_DE   VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_OF_DE)
#define VIDEO_O22_FIRMWARE_MEM_BASE_OF_LED  VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_OF_LED)
#define VIDEO_O22_FIRMWARE_MEM_BASE_OF_IPC  VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_OF_IPC)
#define VIDEO_O22_FIRMWARE_MEM_BASE_DDR_UP	VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_DDR_UP)
#define VIDEO_O22_FIRMWARE_MEM_BASE_OF_TTX	VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_OF_TTX)
#define VIDEO_O22_FIRMWARE_MEM_BASE_WEB_OS	VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_WEB_OS)
#define VIDEO_O22_FIRMWARE_MEM_BASE_REG_TR	VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_REG_TR)
#define VIDEO_O22_FIRMWARE_MEM_BASE_DOLBY_HDR	VIDEO_O22_ROW2PHY(VIDEO_O22_FIRMWARE_ROW_BASE_DOLBY_HDR)

#define VIDEO_O22_MBASE_OF_FRAME_MEMORY     VIDEO_O22_ROW2PHY(VIDEO_O22_START_OF_FRAME_MEMORY)


#define VIDEO_O22_FIRMWARE_MEM_SIZE_OF_DE	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_O22_FIRMWARE_MEM_SIZE_OF_LED	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_O22_FIRMWARE_MEM_SIZE_OF_IPC	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_OF_IPC)
#define VIDEO_O22_FIRMWARE_MEM_SIZE_DDR_UP	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_O22_FIRMWARE_MEM_SIZE_OF_TTX	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_OF_TTX)
#define VIDEO_O22_FIRMWARE_MEM_SIZE_WEB_OS	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_O22_FIRMWARE_MEM_SIZE_REG_TR	CONV_MEM_ROW2BYTE(VIDEO_O22_FIRMWARE_ROW_SIZE_REG_TR)
#define VIDEO_O22_MEM_SIZE_OF_FRAME_MEMORY  CONV_MEM_ROW2BYTE(VIDEO_O22_ROW_SIZE_OF_FRAME_MEMORY)
//#define VIDEO_O22_MEM_SIZE_OF_FRAME_PREW    CONV_MEM_ROW2BYTE(VIDEO_O22_ROW_SIZE_OF_FRAME_PREW)
#define VIDEO_O22_MEM_SIZE_OF_FRAME_GRAP    CONV_MEM_ROW2BYTE(VIDEO_O22_ROW_SIZE_OF_FRAME_GRAP)
#define VIDEO_O22_MEM_SIZE_OF_FRAME_GCSC    CONV_MEM_ROW2BYTE(VIDEO_O22_ROW_SIZE_OF_FRAME_GCSC)

#define VIDEO_O22_FIRMWARE_ROW_OFST_IPC_MC	(0)
#define VIDEO_O22_FIRMWARE_ROW_OFST_DDR_UP	(VIDEO_O22_FIRMWARE_ROW_OFST_IPC_MC + VIDEO_O22_FIRMWARE_ROW_SIZE_IPC_MC)
#define VIDEO_O22_FIRMWARE_ROW_OFST_OF_TTX	(VIDEO_O22_FIRMWARE_ROW_OFST_DDR_UP + VIDEO_O22_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_O22_FIRMWARE_ROW_OFST_WEB_OS	(VIDEO_O22_FIRMWARE_ROW_OFST_OF_TTX + VIDEO_O22_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_O22_FIRMWARE_ROW_OFST_REG_TR	(VIDEO_O22_FIRMWARE_ROW_OFST_WEB_OS + VIDEO_O22_FIRMWARE_ROW_SIZE_OF_TTX)
#endif

#define VIDEO_O22_FW_SHARED_OFST_VTM		(0)
#define VIDEO_O22_FW_SHARED_SIZE_VTM		(32*1024)
#define VIDEO_O22_FW_SHARED_OFST_VTV		(VIDEO_O22_FW_SHARED_OFST_VTM+VIDEO_O22_FW_SHARED_SIZE_VTM)
#define VIDEO_O22_FW_SHARED_SIZE_VTV		(32*1024)
#define VIDEO_O22_FW_SHARED_OFST_GPS		(VIDEO_O22_FW_SHARED_OFST_VTV+VIDEO_O22_FW_SHARED_SIZE_VTV)
#define VIDEO_O22_FW_SHARED_SIZE_GPS		(32*1024)
#define VIDEO_O22_FW_SHARED_OFST_DLY		(VIDEO_O22_FW_SHARED_OFST_GPS+VIDEO_O22_FW_SHARED_SIZE_GPS)
#define VIDEO_O22_FW_SHARED_SIZE_DLY		(32*1024)
#define VIDEO_O22_FW_SHARED_OFST_FPP		(VIDEO_O22_FW_SHARED_OFST_DLY+VIDEO_O22_FW_SHARED_SIZE_DLY)
#define VIDEO_O22_FW_SHARED_SIZE_FPP		(1*1024*1024)
#define VIDEO_O22_FW_SHARED_OFST_FPP_DNN	(VIDEO_O22_FW_SHARED_OFST_FPP+(32*1024))

#define VIDEO_O22_FW_SHARED_OFST_MVI		(VIDEO_O22_FW_SHARED_OFST_FPP+VIDEO_O22_FW_SHARED_SIZE_FPP)
#define VIDEO_O22_FW_SHARED_SIZE_MVI		(32*1024)

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
extern int de_cfg_o22_preinit(void);
extern int de_cfg_o22_init(void);
extern int de_cfg_o22_cleanup(void);
extern int de_cfg_o22_get_hw_opt(UINT32 *opt);

#endif   /* ----- #ifndef DE_CFG_O22_INC  ----- */
/**  @} */
