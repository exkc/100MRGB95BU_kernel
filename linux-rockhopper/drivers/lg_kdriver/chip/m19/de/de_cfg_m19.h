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

#ifndef  DE_CFG_M19_INC
#define  DE_CFG_M19_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_model.h"
#include "de_ver_def.h"
#include "de_cfg_def_m19.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define VIDEO_M19_FRAME_DDR_LW_SCR          783
#define VIDEO_M19_FRAME_DDR_LW_CAP          348
#define VIDEO_M19_FRAME_DDR_LW_TNR_IPC      870
#define VIDEO_M19_FRAME_DDR_RW_SCR          783
#define VIDEO_M19_FRAME_DDR_RW_CAP          348
#define VIDEO_M19_FRAME_DDR_RW_TNR_IPC      696
#define VIDEO_M19_FRAME_DDR_SW_VCR          228
#define VIDEO_M19_FRAME_DDR_SW_MDI          138
#define VIDEO_M19_FRAME_DDR_LW_TNM          69
#define VIDEO_M19_FRAME_DDR_LW_CSC          416

#define VIDEO_M19_CODEC_DDR_BASE            (0x70000000)
#define VIDEO_M19_LOWER_DDR_BASE            (0x80000000)

#if (CONFIG_LX_BOARD_FPGA==1)
#define VIDEO_M19_FRAME_DDR_BASE            (0xA0000000)		/* FPGA board */
#else
#define VIDEO_M19_FRAME_DDR_BASE            (0x80000000)		/* SYSTEM board */
#endif
#define VIDEO_M19_FRAME_FIRMWARE_OFFSET     (0x00000000)

#define VIDEO_M19_CODEC_DDR_OFFSET          (0x2000000)

#define VIDEO_M19_ROW2PHY(_r)               (CONV_MEM_ROW2BYTE(_r) | g_FwBase_M19)

#define VIDEO_M19_FIRMWARE_ROW_SIZE_OF_DE   (VIDEO_MEM_FIRMWARE_ROW_SIZE*2)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_OF_LED  (VIDEO_MEM_FIRMWARE_ROW_SIZE)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_OF_IPC  (VIDEO_MEM_FIRMWARE_ROW_SIZE)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_IPC_MC	(1)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_DDR_UP	(1)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_OF_TTX	(1)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_WEB_OS	(1)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_REG_TR	(1)
#define VIDEO_M19_FIRMWARE_ROW_SIZE_DOLBY_HDR	(1)

#define VIDEO_M19_FIRMWARE_ROW_BASE_OF_DE	(VIDEO_M19_FRAME_FIRMWARE_OFFSET/VIDEO_ROW_STRIDE)
#define VIDEO_M19_FIRMWARE_ROW_BASE_OF_LED	(VIDEO_M19_FIRMWARE_ROW_BASE_OF_DE  + VIDEO_M19_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_M19_FIRMWARE_ROW_BASE_OF_IPC	(VIDEO_M19_FIRMWARE_ROW_BASE_OF_LED + VIDEO_M19_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_M19_START_OF_FRAME_MEMORY		(VIDEO_M19_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_M19_FIRMWARE_ROW_SIZE_OF_IPC)

#define VIDEO_M19_ROW_SIZE_OF_FRAME_MEMORY  (VIDEO_M19_FRAME_DDR_LW_SCR + VIDEO_M19_FRAME_DDR_LW_TNR_IPC + VIDEO_M19_FRAME_DDR_RW_SCR + VIDEO_M19_FRAME_DDR_RW_TNR_IPC + VIDEO_M19_FRAME_DDR_SW_VCR + VIDEO_M19_FRAME_DDR_LW_TNM)
#define VIDEO_M19_ROW_SIZE_OF_FRAME_PREW    (VIDEO_M19_FRAME_DDR_LW_CAP + VIDEO_M19_FRAME_DDR_RW_CAP + 32)
#define VIDEO_M19_ROW_SIZE_OF_FRAME_GRAP    (VIDEO_M19_FRAME_DDR_SW_MDI)
#define VIDEO_M19_ROW_SIZE_OF_FRAME_GCSC    (VIDEO_M19_FRAME_DDR_LW_CSC)

#define VIDEO_M19_FIRMWARE_ROW_BASE_IPC_MC	(VIDEO_M19_FIRMWARE_ROW_BASE_OF_IPC                                     )
#define VIDEO_M19_FIRMWARE_ROW_BASE_DDR_UP	(VIDEO_M19_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_M19_FIRMWARE_ROW_SIZE_IPC_MC)
#define VIDEO_M19_FIRMWARE_ROW_BASE_OF_TTX	(VIDEO_M19_FIRMWARE_ROW_BASE_DDR_UP + VIDEO_M19_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_M19_FIRMWARE_ROW_BASE_WEB_OS	(VIDEO_M19_FIRMWARE_ROW_BASE_OF_TTX + VIDEO_M19_FIRMWARE_ROW_SIZE_OF_TTX)
#define VIDEO_M19_FIRMWARE_ROW_BASE_REG_TR	(VIDEO_M19_FIRMWARE_ROW_BASE_WEB_OS + VIDEO_M19_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_M19_FIRMWARE_ROW_BASE_DOLBY_HDR	(VIDEO_M19_FIRMWARE_ROW_BASE_REG_TR + VIDEO_M19_FIRMWARE_ROW_SIZE_REG_TR)


#define VIDEO_M19_FIRMWARE_MEM_BASE_OF_DE   VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_OF_DE)
#define VIDEO_M19_FIRMWARE_MEM_BASE_OF_LED  VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_OF_LED)
#define VIDEO_M19_FIRMWARE_MEM_BASE_OF_IPC  VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_OF_IPC)
#define VIDEO_M19_FIRMWARE_MEM_BASE_DDR_UP	VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_DDR_UP)
#define VIDEO_M19_FIRMWARE_MEM_BASE_OF_TTX	VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_OF_TTX)
#define VIDEO_M19_FIRMWARE_MEM_BASE_WEB_OS	VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_WEB_OS)
#define VIDEO_M19_FIRMWARE_MEM_BASE_REG_TR	VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_REG_TR)
#define VIDEO_M19_FIRMWARE_MEM_BASE_DOLBY_HDR	VIDEO_M19_ROW2PHY(VIDEO_M19_FIRMWARE_ROW_BASE_DOLBY_HDR)

#define VIDEO_M19_MBASE_OF_FRAME_MEMORY     VIDEO_M19_ROW2PHY(VIDEO_M19_START_OF_FRAME_MEMORY)

#define VIDEO_M19_FIRMWARE_MEM_SIZE_OF_DE	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_M19_FIRMWARE_MEM_SIZE_OF_LED	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_M19_FIRMWARE_MEM_SIZE_OF_IPC	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_OF_IPC)
#define VIDEO_M19_FIRMWARE_MEM_SIZE_DDR_UP	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_M19_FIRMWARE_MEM_SIZE_OF_TTX	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_OF_TTX)
#define VIDEO_M19_FIRMWARE_MEM_SIZE_WEB_OS	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_M19_FIRMWARE_MEM_SIZE_REG_TR	CONV_MEM_ROW2BYTE(VIDEO_M19_FIRMWARE_ROW_SIZE_REG_TR)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_MEMORY  CONV_MEM_ROW2BYTE(VIDEO_M19_ROW_SIZE_OF_FRAME_MEMORY)
//#define VIDEO_M19_MEM_SIZE_OF_FRAME_PREW    CONV_MEM_ROW2BYTE(VIDEO_M19_ROW_SIZE_OF_FRAME_PREW)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_GRAP    CONV_MEM_ROW2BYTE(VIDEO_M19_ROW_SIZE_OF_FRAME_GRAP)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_GCSC    CONV_MEM_ROW2BYTE(VIDEO_M19_ROW_SIZE_OF_FRAME_GCSC)

#define VIDEO_M19_FIRMWARE_ROW_OFST_IPC_MC	(0)
#define VIDEO_M19_FIRMWARE_ROW_OFST_DDR_UP	(VIDEO_M19_FIRMWARE_ROW_OFST_IPC_MC + VIDEO_M19_FIRMWARE_ROW_SIZE_IPC_MC)
#define VIDEO_M19_FIRMWARE_ROW_OFST_OF_TTX	(VIDEO_M19_FIRMWARE_ROW_OFST_DDR_UP + VIDEO_M19_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_M19_FIRMWARE_ROW_OFST_WEB_OS	(VIDEO_M19_FIRMWARE_ROW_OFST_OF_TTX + VIDEO_M19_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_M19_FIRMWARE_ROW_OFST_REG_TR	(VIDEO_M19_FIRMWARE_ROW_OFST_WEB_OS + VIDEO_M19_FIRMWARE_ROW_SIZE_OF_TTX)


#if 0
#define VIDEO_M19_MEM_SIZE_OF_FRAME_PREW      ( 71 * 1024 * 1024)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_M15A   (149 * 1024 * 1024) // 149MB ,  2.0GB DDR
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_20GB   ( 93 * 1024 * 1024) //  93MB ,  2.0GB DDR
//#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_20GB   ( 72 * 1024 * 1024) //  72MB ,  2.0GB DDR
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_15GB   (139 * 1024 * 1024) // 139MB ,  1.5GB DDR
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_NODEJ  ( 90 * 1024 * 1024) //  90MB ,  120Hz model with F16
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DELAY     ( 40 * 1024 * 1024) // Additional delay for BT speaker
#define VIDEO_M19_MEM_SIZE_OF_FRAME_HDRFB     ( 90 * 1024 * 1024) //  90MB ,  2.0GB DDR

#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_M16A_BT     (VIDEO_M19_MEM_SIZE_OF_FRAME_DE_M15A + VIDEO_M19_MEM_SIZE_OF_FRAME_DELAY)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_15GB_BT     (VIDEO_M19_MEM_SIZE_OF_FRAME_DE_15GB + VIDEO_M19_MEM_SIZE_OF_FRAME_DELAY)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_20GB_HDRFB  (VIDEO_M19_MEM_SIZE_OF_FRAME_DE_20GB + VIDEO_M19_MEM_SIZE_OF_FRAME_HDRFB)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_NODEJ_BT    (VIDEO_M19_MEM_SIZE_OF_FRAME_DE_NODEJ + VIDEO_M19_MEM_SIZE_OF_FRAME_DELAY)
#endif

// DDR0
//#define VIDEO_M19_MEM_SIZE_OF_FRAME_PREW      (36 * 1024 * 1024) // 28MB(PREW) + 3MB(SUB) + 8MB(GSC0_Y)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_PREW      (72 * 1024 * 1024) // 64MB(PREW) + 3MB(SUB) + 8MB(GSC0_Y)  !!! Test for HDMI Dolby HDR W/A
#define VIDEO_M19_MEM_SIZE_OF_FRAME_PREW_C0   (58 * 1024 * 1024)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_PREW_15GB (28 * 1024 * 1024) // 25MB(PREW) + 3MB(SUB)

// DDR1
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE       (272 * 1024 * 1024) // 271 MB(frame+frc) + 1MB
//#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_C0    (216 * 1024 * 1024) // 216 MB(frame+frc)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_C0    (300 * 1024 * 1024) // 216 MB(frame+frc)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DE_15GB  (163 * 1024 * 1024) // 162 MB(frame+frc) + 1MB

// TBD (on DDR1)
#define VIDEO_M19_MEM_SIZE_OF_FRAME_DELAY    (40 * 1024 * 1024)  // Additional delay for BT speaker
#define VIDEO_M19_MEM_SIZE_OF_VT_2K          ( 9 * 1024 * 1024)  // 9 MB
#define VIDEO_M19_MEM_SIZE_OF_VT_4K          (40 * 1024 * 1024)  // 40 MB(3x12MB + 4MB)
#define VIDEO_M19_MEM_SIZE_OF_VT_2K_C0       (15 * 1024 * 1024)  // 15 MB
#define VIDEO_M19_MEM_SIZE_OF_VT_4K_C0       (60 * 1024 * 1024)  // 60 MB(5x12MB)

#define __DOLBY_NEW_ARCH_IN_M19__

#define VIDEO_M19_HDR_IPC_MEM_SIZE	3*1024*1024 //256KB
#define VIDEO_M19_HDR_IPC_MEM_SIZE_C0        3*1024*1024 //3MB

// M19 map from AVTASK-247 -> AVTASK-277
#define M19_DE_MEM_SIZE_PREW_M0 (70 * 1024 * 1024)  // 58 -> 70 MB
#define M19_DE_MEM_SIZE_FRM_M0  0//(178 * 1024 * 1024)
#define M19_DE_MEM_SIZE_FRM_M1  (148 * 1024 * 1024) //  234 MB(frame) -> 148
#define M19_DE_MEM_SIZE_FRC_M0  (68  * 1024 * 1024) // M0 FRC 75 -> 68

#define M19_DE_MEM_SIZE_BT_M0    0 //( 20 * 1024 * 1024)
#define M19_DE_MEM_SIZE_BT_M1    0 //( 40 * 1024 * 1024)
#define M19_DE_MEM_SIZE_VT_M0    0 //( 40 * 1024 * 1024)
#define M19_DE_MEM_SIZE_VT_M1    ( 36 * 1024 * 1024) // 60 -> 36
#define M19_DE_MEM_SIZE_VT_M1_CMA ( 12 * 1024 * 1024) // 60 -> 36 -> 12(4.5 MR minor)

//#undef __DOLBY_NEW_ARCH_IN_M19__
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
extern UINT32 g_FwBase_M19;

#endif   /* ----- #ifndef DE_CFG_M19_INC  ----- */
/**  @} */
