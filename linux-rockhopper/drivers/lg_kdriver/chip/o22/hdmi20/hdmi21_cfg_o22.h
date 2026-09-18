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
 *  @date       2021-04-07
 *  @note       Additional information.
 */

#ifndef	_HDMI20_CFG_O22_H_
#define	_HDMI20_CFG_O22_H_

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
#define HDMI21_HAL_O22A0_PHY_SW_VER			0x20210407
	
/* HW mapped address */
#define HDMI21_HAL_O22_ISOL_REG_1			0x00000000
#define HDMI21_HAL_O22_ISOL_REG_2			0x00000000
#define HDMI21_HAL_O22_ISOL_REG_3			0x00000000

#define HDMI21_HAL_O22_ISOL_REG_1_VAL		0x00000000
#define HDMI21_HAL_O22_ISOL_REG_2_VAL		0x00000000
#define HDMI21_HAL_O22_ISOL_REG_3_VAL		0x00000000

#define HDMI21_HAL_O22_EARCPHY_ADDR			0xC8940000
#define HDMI21_HAL_O22_EARCPHY_SIZE			0x400

#define HDMI21_HAL_O22_TOP_ALED_ADDR		0xCA401000
#define HDMI21_HAL_O22_TOP_ALED_SIZE		0x100

#define HDMI21_HAL_O22_DSC_TOP_ADDR			0xC88A0000 
#define HDMI21_HAL_O22_DSC_TOP_SIZE			0x600

#define HDMI21_HAL_O22_DSC_CORE_ADDR		0xC88A5000
#define HDMI21_HAL_O22_DSC_CORE_SIZE		0x98

#define HDMI21_HAL_O22_FEC_TOP_ADDR			0xC88A4000
#define HDMI21_HAL_O22_FEC_TOP_SIZE			0x28

/* RX : PORT 0 */
#define HDMI21_HAL_O22_RX0_CTRL_ADDR		0xC8900000
#define HDMI21_HAL_O22_RX0_CTRL_SIZE		0x10000

#define HDMI21_HAL_O22_RX0_TOP_ADDR			0xC8908000
#define HDMI21_HAL_O22_RX0_TOP_SIZE			0x1000

#define HDMI21_HAL_O22_RX0_ALED_ADDR		0xCA400000
#define HDMI21_HAL_O22_RX0_ALED_SIZE		0x400

#define HDMI21_HAL_O22_RX0_PDC_ADDR			0xC8945000
#define HDMI21_HAL_O22_RX0_PDC_SIZE			0x200

#define HDMI21_HAL_O22_RX0_POSTDR_ADDR		0xC8941000
#define HDMI21_HAL_O22_RX0_POSTDR_SIZE		0x800

/* RX : PORT 1 */
#define HDMI21_HAL_O22_RX1_CTRL_ADDR		0xC8910000
#define HDMI21_HAL_O22_RX1_CTRL_SIZE		0x10000

#define HDMI21_HAL_O22_RX1_TOP_ADDR			0xC8918000
#define HDMI21_HAL_O22_RX1_TOP_SIZE			0x1000

#define HDMI21_HAL_O22_RX1_ALED_ADDR		0xCA400400
#define HDMI21_HAL_O22_RX1_ALED_SIZE		0x400

#define HDMI21_HAL_O22_RX1_PDC_ADDR			0xC8946000
#define HDMI21_HAL_O22_RX1_PDC_SIZE			0x200

#define HDMI21_HAL_O22_RX1_POSTDR_ADDR		0xC8942000
#define HDMI21_HAL_O22_RX1_POSTDR_SIZE		0x800

/* RX : PORT 2 */
#define HDMI21_HAL_O22_RX2_CTRL_ADDR		0xC8920000
#define HDMI21_HAL_O22_RX2_CTRL_SIZE		0x10000

#define HDMI21_HAL_O22_RX2_TOP_ADDR			0xC8928000
#define HDMI21_HAL_O22_RX2_TOP_SIZE			0x1000

#define HDMI21_HAL_O22_RX2_ALED_ADDR		0xCA400800
#define HDMI21_HAL_O22_RX2_ALED_SIZE		0x400

#define HDMI21_HAL_O22_RX2_PDC_ADDR			0xC8947000
#define HDMI21_HAL_O22_RX2_PDC_SIZE			0x200

#define HDMI21_HAL_O22_RX2_POSTDR_ADDR		0xC8943000
#define HDMI21_HAL_O22_RX2_POSTDR_SIZE		0x800

/* RX : PORT 3 */
#define HDMI21_HAL_O22_RX3_CTRL_ADDR		0xC8930000
#define HDMI21_HAL_O22_RX3_CTRL_SIZE		0x10000

#define HDMI21_HAL_O22_RX3_TOP_ADDR			0xC8938000
#define HDMI21_HAL_O22_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_O22_RX3_ALED_ADDR		0xCA400C00
#define HDMI21_HAL_O22_RX3_ALED_SIZE		0x400

#define HDMI21_HAL_O22_RX3_PDC_ADDR			0xC8948000
#define HDMI21_HAL_O22_RX3_PDC_SIZE			0x200

#define HDMI21_HAL_O22_RX3_POSTDR_ADDR		0xC8944000
#define HDMI21_HAL_O22_RX3_POSTDR_SIZE		0x800

/* Interrupt Number */
#define O22_INTERRUPT_GIC_BASE	32

#define HDMI21_RX_O22_IRQ_TOP_PORT0		(O22_INTERRUPT_GIC_BASE + 101)
#define HDMI21_RX_O22_IRQ_LINK_PORT0	(O22_INTERRUPT_GIC_BASE + 102)
#define HDMI21_RX_O22_IRQ_TOP_PORT1		(O22_INTERRUPT_GIC_BASE + 106)
#define HDMI21_RX_O22_IRQ_LINK_PORT1	(O22_INTERRUPT_GIC_BASE + 105)
#define HDMI21_RX_O22_IRQ_TOP_PORT2		(O22_INTERRUPT_GIC_BASE + 109)
#define HDMI21_RX_O22_IRQ_LINK_PORT2	(O22_INTERRUPT_GIC_BASE + 108)
#define HDMI21_RX_O22_IRQ_TOP_PORT3		(O22_INTERRUPT_GIC_BASE + 112)
#define HDMI21_RX_O22_IRQ_LINK_PORT3	(O22_INTERRUPT_GIC_BASE + 111)


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

