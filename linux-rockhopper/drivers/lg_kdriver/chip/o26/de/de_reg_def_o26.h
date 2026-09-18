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
 * date       2011.02.17
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DE_REG_DEF_O26_INC
#define  DE_REG_DEF_O26_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_IPC_REG_O26_BASE             0xCC080000
#define DE_VDEC_O26_BASE                0xCC0A0000
#define DE_IPC_GEN_O26_BASE             (DE_VDEC_O26_BASE + 0x200)

#define DE_MCU_EDMA_O26_BASE            0xCC0C0000

/* REG_VSD_SHP_SHP_FSW_CTRL_03_T shp_fsw_ctrl_03 */
#define DE_MUTE_O26_BASE                0xCC9528FC

/* REG_CCO_VERI_SYS_VERI_10_T video_delay_sts0 */
#define DE_FW_STATUS_O26_BASE           0xCC882328
#define DE_FW_DARINFO_O26_BASE          0xCCC10E00
#define DE_IMX_VERI_15_O26_BASE         0xCCC10E3C

#define DE_MCU_WDOG0_O26_BASE           0xCC020000
#define DE_MCU_WDOG1_O26_BASE           0xCC060000

/* see chip/o26/os/linux_irqs.h */
#ifdef O26_IRQ_INTR_PQE_IPC_CPU
#define O26_IRQ_IPC_BCPU               O26_IRQ_INTR_PQE_IPC_CPU
#define O26_IRQ_IPC2_BCPU              O26_IRQ_INTR_PQE_IPC2_CPU
#define O26_IRQ_IPC3_BCPU              O26_IRQ_INTR_PQE_IPC3_CPU
#define O26_IRQ_DE_BCPU                O26_IRQ_INTR_PQE_LOC_CPU
#else
#define O26_IRQ_IPC_BCPU               (32+80)
#define O26_IRQ_IPC2_BCPU              (32+81)
#define O26_IRQ_IPC3_BCPU              (32+82)
#define O26_IRQ_DE_BCPU                (32+83)
#endif

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

#endif // #ifdef DE_REG_DEF_O26_INC
/**  @} */
