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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     won.hur (won.hur@lge.com) 
 *  @version    1.0
 *  @date       2019-12-17
 *  @note       Additional information.
 */

#ifndef	_HDMI20_CFG_E60_H_
#define	_HDMI20_CFG_E60_H_

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
#define HDMI21_HAL_E60A0_PHY_SW_VER			0x20191217
	
/* HW mapped address */
#define HDMI21_HAL_E60_ISOL_REG_1			0x00000000
#define HDMI21_HAL_E60_ISOL_REG_2			0x00000000
#define HDMI21_HAL_E60_ISOL_REG_3			0x00000000

#define HDMI21_HAL_E60_ISOL_REG_1_VAL		0x00000000
#define HDMI21_HAL_E60_ISOL_REG_2_VAL		0x00000000
#define HDMI21_HAL_E60_ISOL_REG_3_VAL		0x00000000

#define HDMI21_HAL_E60_EARCPHY_ADDR			0xC331A000
#define HDMI21_HAL_E60_EARCPHY_SIZE			0x400

#define HDMI21_HAL_E60_TOP_ALED_ADDR		0xC98A1000
#define HDMI21_HAL_E60_TOP_ALED_SIZE		0x100

#define HDMI21_HAL_E60_DSC_TOP_ADDR			0xC9090000
#define HDMI21_HAL_E60_DSC_TOP_SIZE			0x600

#define HDMI21_HAL_E60_DSC_CORE_ADDR		0xC9095000
#define HDMI21_HAL_E60_DSC_CORE_SIZE		0x98

#define HDMI21_HAL_E60_FEC_TOP_ADDR			0xC9094000
#define HDMI21_HAL_E60_FEC_TOP_SIZE			0x28

/* RX : PORT 0 */
#define HDMI21_HAL_E60_RX0_CTRL_ADDR		0xC3340000
#define HDMI21_HAL_E60_RX0_CTRL_SIZE		0x10000

#define HDMI21_HAL_E60_RX0_TOP_ADDR			0xC3330000
#define HDMI21_HAL_E60_RX0_TOP_SIZE			0x1000

#define HDMI21_HAL_E60_RX0_ALED_ADDR		0xC98A0000
#define HDMI21_HAL_E60_RX0_ALED_SIZE		0x400

#define HDMI21_HAL_E60_RX0_PDC_ADDR			0xC3311000
#define HDMI21_HAL_E60_RX0_PDC_SIZE			0x200

#define HDMI21_HAL_E60_RX0_POSTDR_ADDR		0xC3310000
#define HDMI21_HAL_E60_RX0_POSTDR_SIZE		0x800

/* RX : PORT 1 */
#define HDMI21_HAL_E60_RX1_CTRL_ADDR		0xC3360000
#define HDMI21_HAL_E60_RX1_CTRL_SIZE		0x10000

#define HDMI21_HAL_E60_RX1_TOP_ADDR			0xC3350000
#define HDMI21_HAL_E60_RX1_TOP_SIZE			0x1000

#define HDMI21_HAL_E60_RX1_ALED_ADDR		0xC98A0400
#define HDMI21_HAL_E60_RX1_ALED_SIZE		0x400

#define HDMI21_HAL_E60_RX1_PDC_ADDR			0xC3313000
#define HDMI21_HAL_E60_RX1_PDC_SIZE			0x200

#define HDMI21_HAL_E60_RX1_POSTDR_ADDR		0xC3312000
#define HDMI21_HAL_E60_RX1_POSTDR_SIZE		0x800

/* RX : PORT 2 */
#define HDMI21_HAL_E60_RX2_CTRL_ADDR		0xC3380000
#define HDMI21_HAL_E60_RX2_CTRL_SIZE		0x10000

#define HDMI21_HAL_E60_RX2_TOP_ADDR			0xC3370000
#define HDMI21_HAL_E60_RX2_TOP_SIZE			0x1000

#define HDMI21_HAL_E60_RX2_ALED_ADDR		0xC98A0800
#define HDMI21_HAL_E60_RX2_ALED_SIZE		0x400

#define HDMI21_HAL_E60_RX2_PDC_ADDR			0xC3315000
#define HDMI21_HAL_E60_RX2_PDC_SIZE			0x200

#define HDMI21_HAL_E60_RX2_POSTDR_ADDR		0xC3314000
#define HDMI21_HAL_E60_RX2_POSTDR_SIZE		0x800

/* RX : PORT 3 */
#define HDMI21_HAL_E60_RX3_CTRL_ADDR		0xC33A0000
#define HDMI21_HAL_E60_RX3_CTRL_SIZE		0x10000

#define HDMI21_HAL_E60_RX3_TOP_ADDR			0xC3390000
#define HDMI21_HAL_E60_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_E60_RX3_ALED_ADDR		0xC98A0C00
#define HDMI21_HAL_E60_RX3_ALED_SIZE		0x400

#define HDMI21_HAL_E60_RX3_PDC_ADDR			0xC3317000
#define HDMI21_HAL_E60_RX3_PDC_SIZE			0x200

#define HDMI21_HAL_E60_RX3_POSTDR_ADDR		0xC3316000
#define HDMI21_HAL_E60_RX3_POSTDR_SIZE		0x800

/* Interrupt Number */
#define E60_INTERRUPT_GIC_BASE	32

#define HDMI21_RX_E60_IRQ_TOP_PORT0		(E60_INTERRUPT_GIC_BASE + 105)
#define HDMI21_RX_E60_IRQ_LINK_PORT0	(E60_INTERRUPT_GIC_BASE + 104)
#define HDMI21_RX_E60_IRQ_TOP_PORT1		(E60_INTERRUPT_GIC_BASE + 107)
#define HDMI21_RX_E60_IRQ_LINK_PORT1	(E60_INTERRUPT_GIC_BASE + 106)
#define HDMI21_RX_E60_IRQ_TOP_PORT2		(E60_INTERRUPT_GIC_BASE + 109)
#define HDMI21_RX_E60_IRQ_LINK_PORT2	(E60_INTERRUPT_GIC_BASE + 108)
#define HDMI21_RX_E60_IRQ_TOP_PORT3		(E60_INTERRUPT_GIC_BASE + 111)
#define HDMI21_RX_E60_IRQ_LINK_PORT3	(E60_INTERRUPT_GIC_BASE + 110)


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

