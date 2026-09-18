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

#ifndef  DE_REG_DEF_O20_INC
#define  DE_REG_DEF_O20_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

#define DE_VERSION_O20_A0 0x24A0


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef O20_DE_BASE
#define DTVSOC_DE_O20_BASE              O20_DE_BASE
#define DTVSOC_CTOP_CTRL_O20_BASE       (O20_TOPCTRL_BASE + 0x10)
#else
#define DTVSOC_DE_O20_BASE              0xC9000000
#define DTVSOC_CTOP_CTRL_O20_BASE       0xC0000000
#endif

#define DE_CVC_REG_O20_OFFSET           0x00000
#define DE_VBI_REG_O20_OFFSET           0x00F00
#define DE_IMX_REG_O20_OFFSET           0x14000
#define DE_SMM_REG_O20_OFFSET           0x01400
#define DE_ND0_REG_O20_OFFSET           0x04000
#define DE_HDR_REG_O20_OFFSET           0x05000
#define DE_SUB_REG_O20_OFFSET           0x06000
#define DE_GSC_REG_O20_OFFSET           0x07000
#define DE_VSD_REG_O20_OFFSET           0x0B000
#define DE_CCO_REG_O20_OFFSET           0x24000

#define DE_HDI_REG_O20_OFFSET           0x00100
#define DE_CVI_REG_O20_OFFSET           0x00200
#define DE_CVD_REG_O20_OFFSET           0x00600

#define DE_IPC_FRM_O20_OFFSET           0x26100
#define DE_IPC_REG_O20_OFFSET           0x26000
#define DE_VDEC_O20_OFFSET              0x26200

#define DE_ATP_REG_O20_OFFSET           0x06600

#define DE_IPC_FRM_O20_BASE             (DTVSOC_DE_O20_BASE + DE_IPC_FRM_O20_OFFSET)
#define DE_IPC_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_IPC_REG_O20_OFFSET)
#define DE_ATP_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_ATP_REG_O20_OFFSET)
#define DE_VBI_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_VBI_REG_O20_OFFSET)
#define DE_CVC_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_CVC_REG_O20_OFFSET)
#define DE_VSD_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_VSD_REG_O20_OFFSET)
#define DE_CCO_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_CCO_REG_O20_OFFSET)
#define DE_IMX_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_IMX_REG_O20_OFFSET)
#define DE_ND0_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_ND0_REG_O20_OFFSET)
#define DE_HDR_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_HDR_REG_O20_OFFSET)
#define DE_SUB_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_SUB_REG_O20_OFFSET)
#define DE_CVI_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_CVI_REG_O20_OFFSET)
#define DE_CVD_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_CVD_REG_O20_OFFSET)
#define DE_ATP_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_ATP_REG_O20_OFFSET)
#define DE_SMM_REG_O20_BASE             (DTVSOC_DE_O20_BASE + DE_SMM_REG_O20_OFFSET)

#define DE_VDEC_O20_BASE                (DTVSOC_DE_O20_BASE + DE_VDEC_O20_OFFSET)


#define VDEC_CPU_IPC_OFFSET			   (0x0E00)
#define VDEC_CPC_IPC_OFFSET			   (0x40 * 2)
#define VDEC_CPD_IPC_OFFSET			   (0x40 * 3)

#define VDEC_CPU_IPC_BASE			   (O20_VDEC_BASE      + VDEC_CPU_IPC_OFFSET)
#define VDEC_CPC_IPC_BASE			   (VDEC_CPU_IPC_BASE  + VDEC_CPC_IPC_OFFSET)
#define VDEC_CPD_IPC_BASE			   (VDEC_CPU_IPC_BASE  + VDEC_CPD_IPC_OFFSET)

#ifdef O20_IRQ_INTR_IDS0
#define O20_IRQ_IPC_BCPU               O20_IRQ_INTR_IDS0
#define O20_IRQ_DE_BCPU                O20_IRQ_INTR_IDS1
#else
#define O20_IRQ_IPC_BCPU               58
#define O20_IRQ_DE_BCPU                59
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

#endif // #ifdef DE_REG_DEF_O20_INC
/**  @} */
