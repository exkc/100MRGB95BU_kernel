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

#ifndef  DE_CFG_O18_INC
#define  DE_CFG_O18_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_model.h"
#include "de_ver_def.h"
#include "de_cfg_def_o18.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define VIDEO_O18_FRAME_DDR_LW_SCR          783
#define VIDEO_O18_FRAME_DDR_LW_CAP          348
#define VIDEO_O18_FRAME_DDR_LW_TNR_IPC      870
#define VIDEO_O18_FRAME_DDR_RW_SCR          783
#define VIDEO_O18_FRAME_DDR_RW_CAP          348
#define VIDEO_O18_FRAME_DDR_RW_TNR_IPC      696
#define VIDEO_O18_FRAME_DDR_SW_VCR          228
#define VIDEO_O18_FRAME_DDR_SW_MDI          138
#define VIDEO_O18_FRAME_DDR_LW_TNM          69
#define VIDEO_O18_FRAME_DDR_LW_CSC          416

#define VIDEO_O18_CODEC_DDR_BASE            (0x70000000)
#define VIDEO_O18_LOWER_DDR_BASE            (0x80000000)

#if (CONFIG_LX_BOARD_FPGA==1)
#define VIDEO_O18_FRAME_DDR_BASE            (0xA0000000)		/* FPGA board */
#else
#define VIDEO_O18_FRAME_DDR_BASE            (0x80000000)		/* SYSTEM board */
#endif
#define VIDEO_O18_FRAME_FIRMWARE_OFFSET     (0x00000000)

#define VIDEO_O18_CODEC_DDR_OFFSET          (0x2000000)

#define VIDEO_O18_ROW2PHY(_r)               (CONV_MEM_ROW2BYTE(_r) | g_FwBase_O18)

#define VIDEO_O18_FIRMWARE_ROW_SIZE_OF_DE   (VIDEO_MEM_FIRMWARE_ROW_SIZE*2)
#define VIDEO_O18_FIRMWARE_ROW_SIZE_OF_LED  (VIDEO_MEM_FIRMWARE_ROW_SIZE)
#define VIDEO_O18_FIRMWARE_ROW_SIZE_OF_IPC  (VIDEO_MEM_FIRMWARE_ROW_SIZE)
//#define VIDEO_O18_FIRMWARE_ROW_SIZE_IPC_MC	(1)
//#define VIDEO_O18_FIRMWARE_ROW_SIZE_DDR_UP	(1)
//#define VIDEO_O18_FIRMWARE_ROW_SIZE_OF_TTX	(1)
#define VIDEO_O18_FIRMWARE_ROW_SIZE_WEB_OS	(1)
//#define VIDEO_O18_FIRMWARE_ROW_SIZE_REG_TR	(1)
#define VIDEO_O18_FIRMWARE_ROW_SIZE_DOLBY_HDR	(1)

#ifdef USE_DE_FIRMWARE_RUN_IN_PAK_M16
#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_LED	(VIDEO_O18_FRAME_FIRMWARE_OFFSET/VIDEO_ROW_STRIDE)
#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_LED + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_DE	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_IPC)
#define VIDEO_O18_START_OF_FRAME_MEMORY		(VIDEO_O18_FIRMWARE_ROW_BASE_OF_DE  + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_DE)
#else
#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_DE	(VIDEO_O18_FRAME_FIRMWARE_OFFSET/VIDEO_ROW_STRIDE)
#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_LED	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_DE  + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_LED + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_O18_START_OF_FRAME_MEMORY		(VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_IPC)
#endif

//#define VIDEO_O18_ROW_SIZE_OF_FRAME_MEMORY  (VIDEO_O18_FRAME_DDR_LW_SCR + VIDEO_O18_FRAME_DDR_LW_TNR_IPC + VIDEO_O18_FRAME_DDR_RW_SCR + VIDEO_O18_FRAME_DDR_RW_TNR_IPC + VIDEO_O18_FRAME_DDR_SW_VCR + VIDEO_O18_FRAME_DDR_LW_TNM)
//#define VIDEO_O18_ROW_SIZE_OF_FRAME_PREW    (VIDEO_O18_FRAME_DDR_LW_CAP + VIDEO_O18_FRAME_DDR_RW_CAP + 32)
//#define VIDEO_O18_ROW_SIZE_OF_FRAME_GRAP    (VIDEO_O18_FRAME_DDR_SW_MDI)
//#define VIDEO_O18_ROW_SIZE_OF_FRAME_GCSC    (VIDEO_O18_FRAME_DDR_LW_CSC)

//#define VIDEO_O18_FIRMWARE_ROW_BASE_IPC_MC	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC                                     )
//#define VIDEO_O18_FIRMWARE_ROW_BASE_DDR_UP	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_O18_FIRMWARE_ROW_SIZE_IPC_MC)
//#define VIDEO_O18_FIRMWARE_ROW_BASE_OF_TTX	(VIDEO_O18_FIRMWARE_ROW_BASE_DDR_UP + VIDEO_O18_FIRMWARE_ROW_SIZE_DDR_UP)
//#define VIDEO_O18_FIRMWARE_ROW_BASE_WEB_OS	(VIDEO_O18_FIRMWARE_ROW_BASE_OF_TTX + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_TTX)
//#define VIDEO_O18_FIRMWARE_ROW_BASE_REG_TR	(VIDEO_O18_FIRMWARE_ROW_BASE_WEB_OS + VIDEO_O18_FIRMWARE_ROW_SIZE_WEB_OS)
//#define VIDEO_O18_FIRMWARE_ROW_BASE_DOLBY_HDR	(VIDEO_O18_FIRMWARE_ROW_BASE_REG_TR + VIDEO_O18_FIRMWARE_ROW_SIZE_REG_TR)


#define VIDEO_O18_FIRMWARE_MEM_BASE_OF_DE   VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_OF_DE)
#define VIDEO_O18_FIRMWARE_MEM_BASE_OF_LED  VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_OF_LED)
#define VIDEO_O18_FIRMWARE_MEM_BASE_OF_IPC  VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_OF_IPC)
//#define VIDEO_O18_FIRMWARE_MEM_BASE_DDR_UP	VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_DDR_UP)
//#define VIDEO_O18_FIRMWARE_MEM_BASE_OF_TTX	VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_OF_TTX)
//#define VIDEO_O18_FIRMWARE_MEM_BASE_WEB_OS	VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_WEB_OS)
//#define VIDEO_O18_FIRMWARE_MEM_BASE_REG_TR	VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_REG_TR)
//#define VIDEO_O18_FIRMWARE_MEM_BASE_DOLBY_HDR	VIDEO_O18_ROW2PHY(VIDEO_O18_FIRMWARE_ROW_BASE_DOLBY_HDR)

#define VIDEO_O18_MBASE_OF_FRAME_MEMORY     VIDEO_O18_ROW2PHY(VIDEO_O18_START_OF_FRAME_MEMORY)

#define VIDEO_O18_FIRMWARE_MEM_SIZE_OF_DE	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_O18_FIRMWARE_MEM_SIZE_OF_LED	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_O18_FIRMWARE_MEM_SIZE_OF_IPC	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_OF_IPC)
//#define VIDEO_O18_FIRMWARE_MEM_SIZE_DDR_UP	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_DDR_UP)
//#define VIDEO_O18_FIRMWARE_MEM_SIZE_OF_TTX	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_OF_TTX)
#define VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_WEB_OS)
//#define VIDEO_O18_FIRMWARE_MEM_SIZE_REG_TR	CONV_MEM_ROW2BYTE(VIDEO_O18_FIRMWARE_ROW_SIZE_REG_TR)
//#define VIDEO_O18_MEM_SIZE_OF_FRAME_MEMORY  CONV_MEM_ROW2BYTE(VIDEO_O18_ROW_SIZE_OF_FRAME_MEMORY)
//#define VIDEO_O18_MEM_SIZE_OF_FRAME_PREW    CONV_MEM_ROW2BYTE(VIDEO_O18_ROW_SIZE_OF_FRAME_PREW)
//#define VIDEO_O18_MEM_SIZE_OF_FRAME_GRAP    CONV_MEM_ROW2BYTE(VIDEO_O18_ROW_SIZE_OF_FRAME_GRAP)
//#define VIDEO_O18_MEM_SIZE_OF_FRAME_GCSC    CONV_MEM_ROW2BYTE(VIDEO_O18_ROW_SIZE_OF_FRAME_GCSC)

//#define VIDEO_O18_FIRMWARE_ROW_OFST_IPC_MC	(0)
//#define VIDEO_O18_FIRMWARE_ROW_OFST_DDR_UP	(VIDEO_O18_FIRMWARE_ROW_OFST_IPC_MC + VIDEO_O18_FIRMWARE_ROW_SIZE_IPC_MC)
//#define VIDEO_O18_FIRMWARE_ROW_OFST_OF_TTX	(VIDEO_O18_FIRMWARE_ROW_OFST_DDR_UP + VIDEO_O18_FIRMWARE_ROW_SIZE_DDR_UP)
//#define VIDEO_O18_FIRMWARE_ROW_OFST_WEB_OS	(VIDEO_O18_FIRMWARE_ROW_OFST_OF_TTX + VIDEO_O18_FIRMWARE_ROW_SIZE_WEB_OS)
//#define VIDEO_O18_FIRMWARE_ROW_OFST_REG_TR	(VIDEO_O18_FIRMWARE_ROW_OFST_WEB_OS + VIDEO_O18_FIRMWARE_ROW_SIZE_OF_TTX)


// DDR0
#define VIDEO_O18_MEM_SIZE_OF_MCU1            ( 3 * 1024 * 1024)
#define VIDEO_O18_MEM_SIZE_OF_SHARED_MEM      ( 1 * 1024 * 1024)
#define VIDEO_O18_MEM_SIZE_OF_FRAME_PREW      (35 * 1024 * 1024) // 24MB(PREW) + 3MB(SUB) + 8MB(GSC0_Y)
#define VIDEO_O18_MEM_SIZE_OF_FRAME_PREW_15GB (28 * 1024 * 1024) // 25MB(PREW) + 3MB(SUB)
// DDR1
#define VIDEO_O18_MEM_SIZE_OF_FRAME_DE       (384 * 1024 * 1024) // Y buffer
#define VIDEO_O18_MEM_SIZE_OF_FRAME_C        (382 * 1024 * 1024) // C buffer
#define VIDEO_O18_MEM_SIZE_OF_FRAME_DE_15GB  (163 * 1024 * 1024) // 162 MB(frame+frc) + 1MB

// TBD (on DDR1)
#define VIDEO_O18_MEM_SIZE_OF_FRAME_DELAY    (40 * 1024 * 1024)  // Additional delay for BT speaker
#define VIDEO_O18_MEM_SIZE_OF_VT_2K          (15 * 1024 * 1024)  // 15 MB ( 3MB * 5frame)
#define VIDEO_O18_MEM_SIZE_OF_VT_4K          (60 * 1024 * 1024)  // 60 MB (12MB * 5frame)

//
#define O18_DE_MEM_SIZE_PREW_M0_96 (116 * 1024 * 1024)
#define O18_DE_MEM_SIZE_FRM_M1_96  (178 * 1024 * 1024)
#define O18_DE_MEM_SIZE_FRM_M2_96  (129 * 1024 * 1024)
#define O18_DE_MEM_SIZE_PREW_M0_80 (116 * 1024 * 1024)
#define O18_DE_MEM_SIZE_FRM_M1_80  (119 * 1024 * 1024)
#define O18_DE_MEM_SIZE_FRM_M2_80  (107 * 1024 * 1024)

#define O18_DE_MEM_SIZE_BT_M1    ( 20 * 1024 * 1024)
#define O18_DE_MEM_SIZE_BT_M2    ( 20 * 1024 * 1024)
#define O18_DE_MEM_SIZE_VT_M1    ( 40 * 1024 * 1024)
#define O18_DE_MEM_SIZE_VT_M2    ( 20 * 1024 * 1024)
#define O18_DE_MEM_SIZE_VT_M1_CMA (  8 * 1024 * 1024) // 60 -> 12(4.5 MR minor for 1 ext. buffer)
#define O18_DE_MEM_SIZE_VT_M2_CMA (  4 * 1024 * 1024)


#define VIDEO_O18_HDR_IPC_MEM_SIZE	3*1024*1024 //3MB
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
extern UINT32 g_FwBase_O18;

#endif   /* ----- #ifndef DE_CFG_O18_INC  ----- */
/**  @} */
