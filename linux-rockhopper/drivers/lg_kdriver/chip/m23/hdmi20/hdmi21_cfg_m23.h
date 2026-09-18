/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2022 by LG Electronics Inc.

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
 *  @date       2022-04-07
 *  @note       Additional information.
 */

#ifndef	_HDMI20_CFG_M23_H_
#define	_HDMI20_CFG_M23_H_

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
#define HDMI21_HAL_M23A0_PHY_SW_VER			0x20220307
	
/* HW mapped address */
#define HDMI21_HAL_M23_ISOL_REG_1			0x00000000
#define HDMI21_HAL_M23_ISOL_REG_2			0x00000000
#define HDMI21_HAL_M23_ISOL_REG_3			0x00000000

#define HDMI21_HAL_M23_ISOL_REG_1_VAL		0x00000000
#define HDMI21_HAL_M23_ISOL_REG_2_VAL		0x00000000
#define HDMI21_HAL_M23_ISOL_REG_3_VAL		0x00000000

#define HDMI21_HAL_M23_EARCPHY_ADDR			0xC4B40000
#define HDMI21_HAL_M23_EARCPHY_SIZE			0x400

/* Normally ALED TOP(RC) is not separated... M23 has two separated TOP Controls for port 0,1 / 2,3 */
#define HDMI21_HAL_M23_TOP_ALED_ADDR		0xC6180800
#define HDMI21_HAL_M23_TOP_ALED_SIZE		0x100

#define HDMI21_HAL_M23_TOP_ALED_P23_ADDR	0xF3100800
#define HDMI21_HAL_M23_TOP_ALED_P23_SIZE	0x100

#define HDMI21_HAL_M23_DSC_TOP_ADDR			0x0 
#define HDMI21_HAL_M23_DSC_TOP_SIZE			0x0

#define HDMI21_HAL_M23_DSC_CORE_ADDR		0x0
#define HDMI21_HAL_M23_DSC_CORE_SIZE		0x0

#define HDMI21_HAL_M23_FEC_TOP_ADDR			0x0
#define HDMI21_HAL_M23_FEC_TOP_SIZE			0x0

/* RX : PORT 0 */
#define HDMI21_HAL_M23_RX0_CTRL_ADDR		0xC47C0000
#define HDMI21_HAL_M23_RX0_CTRL_SIZE		0x10000

#define HDMI21_HAL_M23_RX0_TOP_ADDR			0xC47C8000
#define HDMI21_HAL_M23_RX0_TOP_SIZE			0x1000

#define HDMI21_HAL_M23_RX0_ALED_ADDR		0xC6180000
#define HDMI21_HAL_M23_RX0_ALED_SIZE		0x400

#define HDMI21_HAL_M23_RX0_PDC_ADDR			0xC4B42000
#define HDMI21_HAL_M23_RX0_PDC_SIZE			0x200

#define HDMI21_HAL_M23_RX0_POSTDR_ADDR		0xC4B41000
#define HDMI21_HAL_M23_RX0_POSTDR_SIZE		0x800

/* RX : PORT 1 */
#define HDMI21_HAL_M23_RX1_CTRL_ADDR		0xC47D0000
#define HDMI21_HAL_M23_RX1_CTRL_SIZE		0x10000

#define HDMI21_HAL_M23_RX1_TOP_ADDR			0xC47D8000
#define HDMI21_HAL_M23_RX1_TOP_SIZE			0x1000

#define HDMI21_HAL_M23_RX1_ALED_ADDR		0xC6180400
#define HDMI21_HAL_M23_RX1_ALED_SIZE		0x400

#define HDMI21_HAL_M23_RX1_PDC_ADDR			0xC4B44000
#define HDMI21_HAL_M23_RX1_PDC_SIZE			0x200

#define HDMI21_HAL_M23_RX1_POSTDR_ADDR		0xC4B43000
#define HDMI21_HAL_M23_RX1_POSTDR_SIZE		0x800

/* RX : PORT 2 */
#define HDMI21_HAL_M23_RX2_CTRL_ADDR		0xC47E0000
#define HDMI21_HAL_M23_RX2_CTRL_SIZE		0x10000

#define HDMI21_HAL_M23_RX2_TOP_ADDR			0xC47E8000
#define HDMI21_HAL_M23_RX2_TOP_SIZE			0x1000

#define HDMI21_HAL_M23_RX2_ALED_ADDR		0xF3100000
#define HDMI21_HAL_M23_RX2_ALED_SIZE		0x400

#define HDMI21_HAL_M23_RX2_PDC_ADDR			0xC6B51000
#define HDMI21_HAL_M23_RX2_PDC_SIZE			0x200

#define HDMI21_HAL_M23_RX2_POSTDR_ADDR		0xC6B50000
#define HDMI21_HAL_M23_RX2_POSTDR_SIZE		0x800

/* RX : PORT 3 */
#define HDMI21_HAL_M23_RX3_CTRL_ADDR		0xC47F0000
#define HDMI21_HAL_M23_RX3_CTRL_SIZE		0x10000

#define HDMI21_HAL_M23_RX3_TOP_ADDR			0xC47F8000
#define HDMI21_HAL_M23_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_M23_RX3_ALED_ADDR		0xF3100400
#define HDMI21_HAL_M23_RX3_ALED_SIZE		0x400

#define HDMI21_HAL_M23_RX3_PDC_ADDR			0xC6B53000
#define HDMI21_HAL_M23_RX3_PDC_SIZE			0x200

#define HDMI21_HAL_M23_RX3_POSTDR_ADDR		0xC6B52000
#define HDMI21_HAL_M23_RX3_POSTDR_SIZE		0x800

/* Interrupt Number */
#define M23_INTERRUPT_GIC_BASE	32

#define HDMI21_RX_M23_IRQ_TOP_PORT0		(M23_INTERRUPT_GIC_BASE + 117)
#define HDMI21_RX_M23_IRQ_LINK_PORT0	(M23_INTERRUPT_GIC_BASE + 118)
#define HDMI21_RX_M23_IRQ_TOP_PORT1		(M23_INTERRUPT_GIC_BASE + 120)
#define HDMI21_RX_M23_IRQ_LINK_PORT1	(M23_INTERRUPT_GIC_BASE + 121)
#define HDMI21_RX_M23_IRQ_TOP_PORT2		(M23_INTERRUPT_GIC_BASE + 123)
#define HDMI21_RX_M23_IRQ_LINK_PORT2	(M23_INTERRUPT_GIC_BASE + 124)
#define HDMI21_RX_M23_IRQ_TOP_PORT3		(M23_INTERRUPT_GIC_BASE + 126)
#define HDMI21_RX_M23_IRQ_LINK_PORT3	(M23_INTERRUPT_GIC_BASE + 127)


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

