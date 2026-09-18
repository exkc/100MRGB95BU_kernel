/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2021 by LG Electronics Inc.

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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     won.hur (won.hur@lge.com) 
 *  @version    1.0
 *  @date       2025-03-19
 *  @note       Additional information.
 */

#ifndef	_HDMI21_CFG_O26_H_
#define	_HDMI21_CFG_O26_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------------------*/
/* Change below definitions when porting to another chip(H15,M16... )                   */
/* -------------------------------------------------------------------------------------*/
#define HDMI21_HAL_O26A0_PHY_SW_VER			0x20250319
	
/* HW mapped address */
#define HDMI21_HAL_O26_ISOL_REG_1			0x00000000
#define HDMI21_HAL_O26_ISOL_REG_2			0x00000000
#define HDMI21_HAL_O26_ISOL_REG_3			0x00000000

#define HDMI21_HAL_O26_ISOL_REG_1_VAL		0x00000000
#define HDMI21_HAL_O26_ISOL_REG_2_VAL		0x00000000
#define HDMI21_HAL_O26_ISOL_REG_3_VAL		0x00000000

#define HDMI21_HAL_O26_EARCPHY_ADDR			0xC8750000
#define HDMI21_HAL_O26_EARCPHY_SIZE			0x400

#define HDMI21_HAL_O26_TOP_ALED_ADDR		0xCA351000
#define HDMI21_HAL_O26_TOP_ALED_SIZE		0x100

// need cofirm
#define HDMI21_HAL_O26_DSC_TOP_ADDR			0xCC500000	// DSC_IP_TOP -> APB
#define HDMI21_HAL_O26_DSC_TOP_SIZE			0x600
// need cofirm
#define HDMI21_HAL_O26_DSC_CORE_ADDR		0xCC505000	// DSC_IP_TOP -> DSC_ENC
#define HDMI21_HAL_O26_DSC_CORE_SIZE		0x98
// need cofirm
#define HDMI21_HAL_O26_FEC_TOP_ADDR			0xCC504000	// DSC_IP_TOP -> FEC_ENC
#define HDMI21_HAL_O26_FEC_TOP_SIZE			0x28

/* RX : PORT 0 */
#define HDMI21_HAL_O26_RX0_CTRL_ADDR		0xC8700000
#define HDMI21_HAL_O26_RX0_CTRL_SIZE		0x10000

#define HDMI21_HAL_O26_RX0_TOP_ADDR			0xC8708000
#define HDMI21_HAL_O26_RX0_TOP_SIZE			0x1000

#define HDMI21_HAL_O26_RX0_ALED_ADDR		0xCA350000
#define HDMI21_HAL_O26_RX0_ALED_SIZE		0x400

#define HDMI21_HAL_O26_RX0_PDC_ADDR			0xC8752000
#define HDMI21_HAL_O26_RX0_PDC_SIZE			0x200

#define HDMI21_HAL_O26_RX0_POSTDR_ADDR		0xC8751000
#define HDMI21_HAL_O26_RX0_POSTDR_SIZE		0x800

/* RX : PORT 1 */
#define HDMI21_HAL_O26_RX1_CTRL_ADDR		0xC8710000
#define HDMI21_HAL_O26_RX1_CTRL_SIZE		0x10000

#define HDMI21_HAL_O26_RX1_TOP_ADDR			0xC8718000
#define HDMI21_HAL_O26_RX1_TOP_SIZE			0x1000

#define HDMI21_HAL_O26_RX1_ALED_ADDR		0xCA350400
#define HDMI21_HAL_O26_RX1_ALED_SIZE		0x400

#define HDMI21_HAL_O26_RX1_PDC_ADDR			0xC8754000
#define HDMI21_HAL_O26_RX1_PDC_SIZE			0x200

#define HDMI21_HAL_O26_RX1_POSTDR_ADDR		0xC8753000
#define HDMI21_HAL_O26_RX1_POSTDR_SIZE		0x800

/* RX : PORT 2 */
#define HDMI21_HAL_O26_RX2_CTRL_ADDR		0xC8720000
#define HDMI21_HAL_O26_RX2_CTRL_SIZE		0x10000

#define HDMI21_HAL_O26_RX2_TOP_ADDR			0xC8728000
#define HDMI21_HAL_O26_RX2_TOP_SIZE			0x1000

#define HDMI21_HAL_O26_RX2_ALED_ADDR		0xCA350800
#define HDMI21_HAL_O26_RX2_ALED_SIZE		0x400

#define HDMI21_HAL_O26_RX2_PDC_ADDR			0xC8756000
#define HDMI21_HAL_O26_RX2_PDC_SIZE			0x200

#define HDMI21_HAL_O26_RX2_POSTDR_ADDR		0xC8755000
#define HDMI21_HAL_O26_RX2_POSTDR_SIZE		0x800

/* RX : PORT 3 */
#define HDMI21_HAL_O26_RX3_CTRL_ADDR		0xC8730000
#define HDMI21_HAL_O26_RX3_CTRL_SIZE		0x10000

#define HDMI21_HAL_O26_RX3_TOP_ADDR			0xC8738000
#define HDMI21_HAL_O26_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_O26_RX3_ALED_ADDR		0xCA350C00
#define HDMI21_HAL_O26_RX3_ALED_SIZE		0x400

#define HDMI21_HAL_O26_RX3_PDC_ADDR			0xC8758000
#define HDMI21_HAL_O26_RX3_PDC_SIZE			0x200

#define HDMI21_HAL_O26_RX3_POSTDR_ADDR		0xC8757000
#define HDMI21_HAL_O26_RX3_POSTDR_SIZE		0x800

/* Interrupt Number */
#define O26_INTERRUPT_GIC_BASE	32	

#define HDMI21_RX_O26_IRQ_TOP_PORT0		(O24_INTERRUPT_GIC_BASE + 148)		/* CPU 0 */
#define HDMI21_RX_O26_IRQ_LINK_PORT0	(O24_INTERRUPT_GIC_BASE + 149)		/* CPU 1 */
#define HDMI21_RX_O26_IRQ_TOP_PORT1		(O24_INTERRUPT_GIC_BASE + 151)		/* CPU 0 */
#define HDMI21_RX_O26_IRQ_LINK_PORT1	(O24_INTERRUPT_GIC_BASE + 152)		/* CPU 1 */
#define HDMI21_RX_O26_IRQ_TOP_PORT2		(O24_INTERRUPT_GIC_BASE + 154)		/* CPU 0 */
#define HDMI21_RX_O26_IRQ_LINK_PORT2	(O24_INTERRUPT_GIC_BASE + 155)		/* CPU 1 */
#define HDMI21_RX_O26_IRQ_TOP_PORT3		(O24_INTERRUPT_GIC_BASE + 157)		/* CPU 0 */
#define HDMI21_RX_O26_IRQ_LINK_PORT3	(O24_INTERRUPT_GIC_BASE + 158)		/* CPU 1 */


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

