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
 *  @author     taejun.lee (taejun.lee@lge.com) 
 *  @version    1.0
 *  @date       2023-01-11
 *  @note       Additional information.
 */

#ifndef	_HDMI21_CFG_O24_H_
#define	_HDMI21_CFG_O24_H_

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
#define HDMI21_HAL_O24A0_PHY_SW_VER			0x20230111
	
/* HW mapped address */
#define HDMI21_HAL_O24_ISOL_REG_1			0x00000000
#define HDMI21_HAL_O24_ISOL_REG_2			0x00000000
#define HDMI21_HAL_O24_ISOL_REG_3			0x00000000

#define HDMI21_HAL_O24_ISOL_REG_1_VAL		0x00000000
#define HDMI21_HAL_O24_ISOL_REG_2_VAL		0x00000000
#define HDMI21_HAL_O24_ISOL_REG_3_VAL		0x00000000

#define HDMI21_HAL_O24_EARCPHY_ADDR			0xC8D50000
#define HDMI21_HAL_O24_EARCPHY_SIZE			0x400

#define HDMI21_HAL_O24_TOP_ALED_ADDR		0xC8821000
#define HDMI21_HAL_O24_TOP_ALED_SIZE		0x100

// need cofirm
#define HDMI21_HAL_O24_DSC_TOP_ADDR			0xC8CE0000	// DSC_IP_TOP -> APB
#define HDMI21_HAL_O24_DSC_TOP_SIZE			0x600
// need cofirm
#define HDMI21_HAL_O24_DSC_CORE_ADDR		0xC8CE5000	// DSC_IP_TOP -> DSC_ENC
#define HDMI21_HAL_O24_DSC_CORE_SIZE		0x98
// need cofirm
#define HDMI21_HAL_O24_FEC_TOP_ADDR			0xC8CE4000	// DSC_IP_TOP -> FEC_ENC
#define HDMI21_HAL_O24_FEC_TOP_SIZE			0x28

/* RX : PORT 0 */
#define HDMI21_HAL_O24_RX0_CTRL_ADDR		0xC8D00000
#define HDMI21_HAL_O24_RX0_CTRL_SIZE		0x10000

#define HDMI21_HAL_O24_RX0_TOP_ADDR			0xC8D08000
#define HDMI21_HAL_O24_RX0_TOP_SIZE			0x1000

#define HDMI21_HAL_O24_RX0_ALED_ADDR		0xC8820000
#define HDMI21_HAL_O24_RX0_ALED_SIZE		0x400

#define HDMI21_HAL_O24_RX0_PDC_ADDR			0xC8D52000
#define HDMI21_HAL_O24_RX0_PDC_SIZE			0x200

#define HDMI21_HAL_O24_RX0_POSTDR_ADDR		0xC8D51000
#define HDMI21_HAL_O24_RX0_POSTDR_SIZE		0x800

/* RX : PORT 1 */
#define HDMI21_HAL_O24_RX1_CTRL_ADDR		0xC8D10000
#define HDMI21_HAL_O24_RX1_CTRL_SIZE		0x10000

#define HDMI21_HAL_O24_RX1_TOP_ADDR			0xC8D18000
#define HDMI21_HAL_O24_RX1_TOP_SIZE			0x1000

#define HDMI21_HAL_O24_RX1_ALED_ADDR		0xC8820400
#define HDMI21_HAL_O24_RX1_ALED_SIZE		0x400

#define HDMI21_HAL_O24_RX1_PDC_ADDR			0xC8D54000
#define HDMI21_HAL_O24_RX1_PDC_SIZE			0x200

#define HDMI21_HAL_O24_RX1_POSTDR_ADDR		0xC8D53000
#define HDMI21_HAL_O24_RX1_POSTDR_SIZE		0x800

/* RX : PORT 2 */
#define HDMI21_HAL_O24_RX2_CTRL_ADDR		0xC8D20000
#define HDMI21_HAL_O24_RX2_CTRL_SIZE		0x10000

#define HDMI21_HAL_O24_RX2_TOP_ADDR			0xC8D28000
#define HDMI21_HAL_O24_RX2_TOP_SIZE			0x1000

#define HDMI21_HAL_O24_RX2_ALED_ADDR		0xC8820800
#define HDMI21_HAL_O24_RX2_ALED_SIZE		0x400

#define HDMI21_HAL_O24_RX2_PDC_ADDR			0xC8D56000
#define HDMI21_HAL_O24_RX2_PDC_SIZE			0x200

#define HDMI21_HAL_O24_RX2_POSTDR_ADDR		0xC8D55000
#define HDMI21_HAL_O24_RX2_POSTDR_SIZE		0x800

/* RX : PORT 3 */
#define HDMI21_HAL_O24_RX3_CTRL_ADDR		0xC8D30000
#define HDMI21_HAL_O24_RX3_CTRL_SIZE		0x10000

#define HDMI21_HAL_O24_RX3_TOP_ADDR			0xC8D38000
#define HDMI21_HAL_O24_RX3_TOP_SIZE			0x1000

#define HDMI21_HAL_O24_RX3_ALED_ADDR		0xC8820C00
#define HDMI21_HAL_O24_RX3_ALED_SIZE		0x400

#define HDMI21_HAL_O24_RX3_PDC_ADDR			0xC8D58000
#define HDMI21_HAL_O24_RX3_PDC_SIZE			0x200

#define HDMI21_HAL_O24_RX3_POSTDR_ADDR		0xC8D57000
#define HDMI21_HAL_O24_RX3_POSTDR_SIZE		0x800

/* Interrupt Number */
#define O24_INTERRUPT_GIC_BASE	32	

#define HDMI21_RX_O24_IRQ_TOP_PORT0		(O24_INTERRUPT_GIC_BASE + 140)
#define HDMI21_RX_O24_IRQ_LINK_PORT0	(O24_INTERRUPT_GIC_BASE + 141)
#define HDMI21_RX_O24_IRQ_TOP_PORT1		(O24_INTERRUPT_GIC_BASE + 143)
#define HDMI21_RX_O24_IRQ_LINK_PORT1	(O24_INTERRUPT_GIC_BASE + 144)
#define HDMI21_RX_O24_IRQ_TOP_PORT2		(O24_INTERRUPT_GIC_BASE + 146)
#define HDMI21_RX_O24_IRQ_LINK_PORT2	(O24_INTERRUPT_GIC_BASE + 147)
#define HDMI21_RX_O24_IRQ_TOP_PORT3		(O24_INTERRUPT_GIC_BASE + 149)
#define HDMI21_RX_O24_IRQ_LINK_PORT3	(O24_INTERRUPT_GIC_BASE + 150)


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

