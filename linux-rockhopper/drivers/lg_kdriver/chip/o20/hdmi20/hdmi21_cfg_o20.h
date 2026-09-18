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
 *  @date       2019-04-24
 *  @note       Additional information.
 */

#ifndef	_HDMI20_CFG_O20_H_
#define	_HDMI20_CFG_O20_H_

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
#define HDMI21_HAL_O20A0_PHY_SW_VER			0x20190424
	
/* HW mapped address */
#define HDMI21_HAL_O20_ISOL_REG_1			0x00000000
#define HDMI21_HAL_O20_ISOL_REG_2			0x00000000
#define HDMI21_HAL_O20_ISOL_REG_3			0x00000000

#define HDMI21_HAL_O20_ISOL_REG_1_VAL		0x00000000
#define HDMI21_HAL_O20_ISOL_REG_2_VAL		0x00000000
#define HDMI21_HAL_O20_ISOL_REG_3_VAL		0x00000000

#define HDMI21_HAL_O20_EARCPHY_ADDR			0xC331A000
#define HDMI21_HAL_O20_EARCPHY_SIZE			0x400

#define HDMI21_HAL_O20_TOP_ALED_ADDR		0xC36C1000
#define HDMI21_HAL_O20_TOP_ALED_SIZE		0x100

#define HDMI21_HAL_O20_DSC_TOP_ADDR			0xC9060000
#define HDMI21_HAL_O20_DSC_TOP_SIZE			0x450

#define HDMI21_HAL_O20_DSC_CORE_ADDR		0xC9065000
#define HDMI21_HAL_O20_DSC_CORE_SIZE		0x98

#define HDMI21_HAL_O20_FEC_TOP_ADDR			0xC9064000
#define HDMI21_HAL_O20_FEC_TOP_SIZE			0x28

/* RX : PORT 0 */
#define HDMI21_HAL_O20_RX0_CTRL_ADDR		0xC9110000
#define HDMI21_HAL_O20_RX0_CTRL_SIZE		0x10000

#define HDMI21_HAL_O20A0_RX0_TOP_ADDR		0xC9108000
#define HDMI21_HAL_O20A0_RX0_TOP_SIZE		0x1000

#define HDMI21_HAL_O20B0_RX0_TOP_ADDR		0xC9100000
#define HDMI21_HAL_O20B0_RX0_TOP_SIZE		0x1000

#define HDMI21_HAL_O20_RX0_ALED_ADDR		0xC36C0000
#define HDMI21_HAL_O20_RX0_ALED_SIZE		0x400

#define HDMI21_HAL_O20_RX0_PDC_ADDR			0xC3311000
#define HDMI21_HAL_O20_RX0_PDC_SIZE			0x200

#define HDMI21_HAL_O20_RX0_POSTDR_ADDR		0xC3310000
#define HDMI21_HAL_O20_RX0_POSTDR_SIZE		0x800

/* RX : PORT 1 */
#define HDMI21_HAL_O20_RX1_CTRL_ADDR		0xC9130000
#define HDMI21_HAL_O20_RX1_CTRL_SIZE		0x10000

#define HDMI21_HAL_O20_RX1_TOP_ADDR			0xC9128000
#define HDMI21_HAL_O20_RX1_TOP_SIZE			0x1000

#define HDMI21_HAL_O20A0_RX1_TOP_ADDR		0xC9128000
#define HDMI21_HAL_O20A0_RX1_TOP_SIZE		0x1000

#define HDMI21_HAL_O20B0_RX1_TOP_ADDR		0xC9120000
#define HDMI21_HAL_O20B0_RX1_TOP_SIZE		0x1000

#define HDMI21_HAL_O20_RX1_ALED_ADDR		0xC36C0400
#define HDMI21_HAL_O20_RX1_ALED_SIZE		0x400

#define HDMI21_HAL_O20_RX1_PDC_ADDR			0xC3313000
#define HDMI21_HAL_O20_RX1_PDC_SIZE			0x200

#define HDMI21_HAL_O20_RX1_POSTDR_ADDR		0xC3312000
#define HDMI21_HAL_O20_RX1_POSTDR_SIZE		0x800

/* RX : PORT 2 */
#define HDMI21_HAL_O20_RX2_CTRL_ADDR		0xC9150000
#define HDMI21_HAL_O20_RX2_CTRL_SIZE		0x10000

#define HDMI21_HAL_O20A0_RX2_TOP_ADDR			0xC9148000
#define HDMI21_HAL_O20A0_RX2_TOP_SIZE			0x1000

#define HDMI21_HAL_O20B0_RX2_TOP_ADDR		0xC9140000
#define HDMI21_HAL_O20B0_RX2_TOP_SIZE		0x1000

#define HDMI21_HAL_O20_RX2_ALED_ADDR		0xC36C0800
#define HDMI21_HAL_O20_RX2_ALED_SIZE		0x400

#define HDMI21_HAL_O20_RX2_PDC_ADDR			0xC3315000
#define HDMI21_HAL_O20_RX2_PDC_SIZE			0x200

#define HDMI21_HAL_O20_RX2_POSTDR_ADDR		0xC3314000
#define HDMI21_HAL_O20_RX2_POSTDR_SIZE		0x800

/* RX : PORT 3 */
#define HDMI21_HAL_O20_RX3_CTRL_ADDR		0xC9170000
#define HDMI21_HAL_O20_RX3_CTRL_SIZE		0x10000

#define HDMI21_HAL_O20A0_RX3_TOP_ADDR			0xC9168000
#define HDMI21_HAL_O20A0_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_O20B0_RX3_TOP_ADDR			0xC9160000
#define HDMI21_HAL_O20B0_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_O20_RX3_ALED_ADDR		0xC36C0C00
#define HDMI21_HAL_O20_RX3_ALED_SIZE		0x400

#define HDMI21_HAL_O20_RX3_PDC_ADDR			0xC3317000
#define HDMI21_HAL_O20_RX3_PDC_SIZE			0x200

#define HDMI21_HAL_O20_RX3_POSTDR_ADDR		0xC3316000
#define HDMI21_HAL_O20_RX3_POSTDR_SIZE		0x800

/* RX : PORT 4 */
#define HDMI21_HAL_O20_RX4_CTRL_ADDR		0xC9190000
#define HDMI21_HAL_O20_RX4_CTRL_SIZE		0x10000

#define HDMI21_HAL_O20A0_RX4_TOP_ADDR		0xC9188000
#define HDMI21_HAL_O20A0_RX4_TOP_SIZE		0x1000

#define HDMI21_HAL_O20B0_RX4_TOP_ADDR		0xC9180000
#define HDMI21_HAL_O20B0_RX4_TOP_SIZE		0x1000

#define HDMI21_HAL_O20_RX4_ALED_ADDR		0xC36C1C00
#define HDMI21_HAL_O20_RX4_ALED_SIZE		0x400

#define HDMI21_HAL_O20_RX4_PDC_ADDR			0xC3319000
#define HDMI21_HAL_O20_RX4_PDC_SIZE			0x200

#define HDMI21_HAL_O20_RX4_POSTDR_ADDR		0xC3318000
#define HDMI21_HAL_O20_RX4_POSTDR_SIZE		0x800

/* Interrupt Number */
#define O20_INTERRUPT_GIC_BASE	32

#define HDMI21_RX_O20_IRQ_TOP_PORT0		(O20_INTERRUPT_GIC_BASE + 74)
#define HDMI21_RX_O20_IRQ_LINK_PORT0	(O20_INTERRUPT_GIC_BASE + 75)
#define HDMI21_RX_O20_IRQ_TOP_PORT1		(O20_INTERRUPT_GIC_BASE + 77)
#define HDMI21_RX_O20_IRQ_LINK_PORT1	(O20_INTERRUPT_GIC_BASE + 78)
#define HDMI21_RX_O20_IRQ_TOP_PORT2		(O20_INTERRUPT_GIC_BASE + 80)
#define HDMI21_RX_O20_IRQ_LINK_PORT2	(O20_INTERRUPT_GIC_BASE + 81)
#define HDMI21_RX_O20_IRQ_TOP_PORT3		(O20_INTERRUPT_GIC_BASE + 83)
#define HDMI21_RX_O20_IRQ_LINK_PORT3	(O20_INTERRUPT_GIC_BASE + 84)
#define HDMI21_RX_O20_IRQ_TOP_PORT4		(O20_INTERRUPT_GIC_BASE + 129)
#define HDMI21_RX_O20_IRQ_LINK_PORT4	(O20_INTERRUPT_GIC_BASE + 130)


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

