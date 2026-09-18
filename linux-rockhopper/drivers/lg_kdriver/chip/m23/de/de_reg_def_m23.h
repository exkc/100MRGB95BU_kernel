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

#ifndef  DE_REG_DEF_M23_INC
#define  DE_REG_DEF_M23_INC

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
#define DE_IPC_REG_M23_BASE             0xCC080000
#define DE_VDEC_M23_BASE                0xCC0A0000
#define DE_IPC_GEN_M23_BASE             (DE_VDEC_M23_BASE + 0x200)

#define DE_MUTE_M23_BASE                0xCC4F28FC // VSD_SHP SHP_FSW_CTRL_03
#define DE_FW_STATUS_M23_BASE           0xCC4B2228 // CCO_VERI SYS_VERI_10

#if 0	//legacy
#define DE_INT_STATUS_M23_BASE          0xCC8C0D00 // ipc interrupt bit (~ 0xCC8C0D24) : AVTASK-607, IMX_VERI SYS_VERI_0 ~ SYS_VERI_9
#define DE_INT_TOPND1_M23_BASE          0xCCC00010 // ND1 interrupt clear : AVTASK-607, ND1_CTRL INTR_REG
#endif

/* see linux_irqs.h */
#ifdef M23_IRQ_INTR_PQE_CPU_IPC
#define M23_IRQ_IPC_BCPU               M23_IRQ_INTR_PQE_CPU_IPC
#define M23_IRQ_DE_BCPU                M23_IRQ_INTR_PQE_CPU_LOC
#else
#define M23_IRQ_IPC_BCPU               (32+112)
#define M23_IRQ_DE_BCPU                (32+113)
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

#endif // #ifdef DE_REG_DEF_M23_INC
/**  @} */
