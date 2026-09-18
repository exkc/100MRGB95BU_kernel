/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_reg_def_m17.h
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

#ifndef _PE_REG_DEF_M17_H_
#define _PE_REG_DEF_M17_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
/* define for using m17a wcp(ov) register
* should be undef, because of m17a ov removed */
/* 20140526, sj.youm, undef for bringup */
#undef PE_HW_M17_USE_M17_WCP_REG

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
/* M17_DE_BASE */
#define PE_M17_DE_BASE				(0xC9000000)
/*C0*/
#define PE_M17C0_HDMI_A_OFST		(0x000100)
#define PE_M17C0_HDMI_B_OFST		(0x000140)
#define PE_M17C0_HDMI_C_OFST		(0x000180)
#define PE_M17C0_HDMI_D_OFST		(0x0001C0)
#define PE_M17C0_CVI_A_OFST			(0x000200)
#define PE_M17C0_CVI_B_OFST			(0x000300)
#define PE_M17C0_CVI_C_OFST			(0x000400)
#define PE_M17C0_CVI_D_OFST			(0x000500)

#define PE_M17C0_IMX_OFST			(0x0010B8)
#define PE_M17C0_IPP_OFST			(0x001400)
#define PE_M17C0_HDR10_OFST			(0x005800)
#define PE_M17C0_ND_OFST			(0x004100)
#define PE_M17C0_DNR_OFST			(0x004500)

#define PE_M17C0_SC_V1_OFST			(0x000044)
#define PE_M17C0_SC_V2_OFST			(0x000060)
#define PE_M17C0_SC_H1_OFST			(0x000074)
#define PE_M17C0_SC_H2_OFST			(0x000090)

#define PE_M17C0_GSC_Y_OFST			(0x007500)
#define PE_M17C0_GSC_Y_G0_OFST		(0x007500)
#define PE_M17C0_GSC_Y_G1_OFST		(0x0075A4)
#define PE_M17C0_GSC_C_OFST			(0x007700)
#define PE_M17C0_GSC_C_G0_OFST		(0x007700)
#define PE_M17C0_GSC_C_G1_OFST		(0x0077A4)

#define PE_M17C0_VCP_DE_OFST		(0x00C000)
#define PE_M17C0_VCP_DISP_OFST		(0x00C400)

#define PE_M17C0_SR_SHP_OFST		(0x009000)
#define PE_M17C0_SR_SHP_BRG_OFST	(0x009F00)
#define PE_M17C0_SR_PSC_Y_OFST		(0x00A000)
#define PE_M17C0_SR_PSC_C_OFST		(0x00A100)

#define PE_M17C0_P1_SHP_L_OFST		(0x00D000)
#define PE_M17C0_P1_SHP_PSP_OFST	(0x00B26C)

#define PE_M17C0_P1_CCO_E_OFST		(0x025000)
#define PE_M17C0_P1_CCO_O_OFST		(0x025500)

#define PE_M17C0_LED_OFST			(0x020000)
#define PE_M17C0_LED_RP_OFST		(0x020540)
#define PE_M17C0_VSD_OFST			(0x00B0B0)

#define PE_M17C0_REG_WRITE_BASE		(0x0)
#define PE_M17C0_P1_CCO_EO_DIFF		(PE_M17C0_P1_CCO_O_OFST - PE_M17C0_P1_CCO_E_OFST)

#define PE_M17C0_HDMI_A_BASE		(PE_M17_DE_BASE + PE_M17C0_HDMI_A_OFST)
#define PE_M17C0_HDMI_B_BASE		(PE_M17_DE_BASE + PE_M17C0_HDMI_B_OFST)
#define PE_M17C0_HDMI_C_BASE		(PE_M17_DE_BASE + PE_M17C0_HDMI_C_OFST)
#define PE_M17C0_HDMI_D_BASE		(PE_M17_DE_BASE + PE_M17C0_HDMI_D_OFST)
#define PE_M17C0_CVI_A_BASE			(PE_M17_DE_BASE + PE_M17C0_CVI_A_OFST)
#define PE_M17C0_CVI_B_BASE			(PE_M17_DE_BASE + PE_M17C0_CVI_B_OFST)
#define PE_M17C0_CVI_C_BASE			(PE_M17_DE_BASE + PE_M17C0_CVI_C_OFST)
#define PE_M17C0_CVI_D_BASE			(PE_M17_DE_BASE + PE_M17C0_CVI_D_OFST)

#define PE_M17C0_IMX_BASE			(PE_M17_DE_BASE + PE_M17C0_IMX_OFST)
#define PE_M17C0_IPP_BASE			(PE_M17_DE_BASE + PE_M17C0_IPP_OFST)
#define PE_M17C0_HDR10_BASE			(PE_M17_DE_BASE + PE_M17C0_HDR10_OFST)
#define PE_M17C0_ND0_BASE			(PE_M17_DE_BASE + PE_M17C0_ND_OFST)
#define PE_M17C0_DNR0_BASE			(PE_M17_DE_BASE + PE_M17C0_DNR_OFST)

#define PE_M17C0_GSC_Y_BASE			(PE_M17_DE_BASE + PE_M17C0_GSC_Y_OFST)
#define PE_M17C0_GSC_C_BASE			(PE_M17_DE_BASE + PE_M17C0_GSC_C_OFST)

#define PE_M17C0_VCP_DE_BASE		(PE_M17_DE_BASE + PE_M17C0_VCP_DE_OFST)
#define PE_M17C0_VCP_DISP_BASE		(PE_M17_DE_BASE + PE_M17C0_VCP_DISP_OFST)

#define PE_M17C0_SR_SHP_BASE		(PE_M17_DE_BASE + PE_M17C0_SR_SHP_OFST)
#define PE_M17C0_SR_SHP_BRG_BASE	(PE_M17_DE_BASE + PE_M17C0_SR_SHP_BRG_OFST)
#define PE_M17C0_SR_PSC_Y_BASE		(PE_M17_DE_BASE + PE_M17C0_SR_PSC_Y_OFST)
#define PE_M17C0_SR_PSC_C_BASE		(PE_M17_DE_BASE + PE_M17C0_SR_PSC_C_OFST)

#define PE_M17C0_P1_SHP_L_BASE		(PE_M17_DE_BASE + PE_M17C0_P1_SHP_L_OFST)
#define PE_M17C0_P1_SHP_PSP_BASE	(PE_M17_DE_BASE + PE_M17C0_P1_SHP_PSP_OFST)

#define PE_M17C0_P1_CCO_E_BASE		(PE_M17_DE_BASE + PE_M17C0_P1_CCO_E_OFST)
#define PE_M17C0_P1_CCO_O_BASE		(PE_M17_DE_BASE + PE_M17C0_P1_CCO_O_OFST)

#define PE_M17C0_LED_BASE			(PE_M17_DE_BASE + PE_M17C0_LED_OFST)
#define PE_M17C0_LED_RP_BASE		(PE_M17_DE_BASE + PE_M17C0_LED_RP_OFST)

#define PE_M17C0_DDR_DB_BASE		(gMemCfgBe[2].fw[4].fw_base)
#define PE_M17C0_DDR_DB_SIZE		(gMemCfgBe[2].fw[4].fw_size)
#define PE_M17C0_VSD_BASE			(PE_M17_DE_BASE + PE_M17C0_VSD_OFST)

/*B0, A0*/
#define PE_M17_HDMI_A_OFST			(0x000100)
#define PE_M17_HDMI_B_OFST			(0x000140)
#define PE_M17_HDMI_C_OFST			(0x000180)
#define PE_M17_HDMI_D_OFST			(0x0001C0)
#define PE_M17_CVI_A_OFST			(0x000200)
#define PE_M17_CVI_B_OFST			(0x000300)
#define PE_M17_CVI_C_OFST			(0x000400)
#define PE_M17_CVI_D_OFST			(0x000500)

#define PE_M17_IMX_OFST				(0x0010B8)
#define PE_M17_IPP_OFST				(0x001400)
#define PE_M17_HDR10_OFST			(0x005800)
#define PE_M17_ND_OFST				(0x004100)
#define PE_M17_DNR_OFST				(0x008100)

#define PE_M17_SC_V1_OFST			(0x000044)
#define PE_M17_SC_V2_OFST			(0x000060)
#define PE_M17_SC_H1_OFST			(0x000074)
#define PE_M17_SC_H2_OFST			(0x000090)

#define PE_M17_GSC_Y_OFST			(0x007500)
#define PE_M17_GSC_Y_G0_OFST		(0x007500)
#define PE_M17_GSC_Y_G1_OFST		(0x0075A4)
#define PE_M17_GSC_C_OFST			(0x007700)
#define PE_M17_GSC_C_G0_OFST		(0x007700)
#define PE_M17_GSC_C_G1_OFST		(0x0077A4)

#define PE_M17_VCP_DE_OFST			(0x00C000)
#define PE_M17_VCP_DISP_OFST		(0x00C400)

#define PE_M17_SR_SHP_OFST			(0x009000)
#define PE_M17_SR_SHP_BRG_OFST		(0x009F00)
#define PE_M17_SR_PSC_Y_OFST		(0x00A000)
#define PE_M17_SR_PSC_C_OFST		(0x00A100)

#define PE_M17_P1_SHP_L_OFST		(0x00D000)
#define PE_M17_P1_SHP_PSP_OFST		(0x00B26C)

#define PE_M17_P1_CCO_E_OFST		(0x025000)
#define PE_M17_P1_CCO_O_OFST		(0x025500)

#define PE_M17_LED_OFST				(0x020000)
#define PE_M17_LED_RP_OFST			(0x020540)
#define PE_M17_VSD_OFST				(0x00B0B0)

#define PE_M17_REG_WRITE_BASE		(0x0)
#define PE_M17_P1_CCO_EO_DIFF		(PE_M17_P1_CCO_O_OFST - PE_M17_P1_CCO_E_OFST)

#define PE_M17_HDMI_A_BASE			(PE_M17_DE_BASE + PE_M17_HDMI_A_OFST)
#define PE_M17_HDMI_B_BASE			(PE_M17_DE_BASE + PE_M17_HDMI_B_OFST)
#define PE_M17_HDMI_C_BASE			(PE_M17_DE_BASE + PE_M17_HDMI_C_OFST)
#define PE_M17_HDMI_D_BASE			(PE_M17_DE_BASE + PE_M17_HDMI_D_OFST)
#define PE_M17_CVI_A_BASE			(PE_M17_DE_BASE + PE_M17_CVI_A_OFST)
#define PE_M17_CVI_B_BASE			(PE_M17_DE_BASE + PE_M17_CVI_B_OFST)
#define PE_M17_CVI_C_BASE			(PE_M17_DE_BASE + PE_M17_CVI_C_OFST)
#define PE_M17_CVI_D_BASE			(PE_M17_DE_BASE + PE_M17_CVI_D_OFST)

#define PE_M17_IMX_BASE				(PE_M17_DE_BASE + PE_M17_IMX_OFST)
#define PE_M17_IPP_BASE				(PE_M17_DE_BASE + PE_M17_IPP_OFST)
#define PE_M17_HDR10_BASE			(PE_M17_DE_BASE + PE_M17_HDR10_OFST)
#define PE_M17_ND0_BASE				(PE_M17_DE_BASE + PE_M17_ND_OFST)
#define PE_M17_DNR0_BASE			(PE_M17_DE_BASE + PE_M17_DNR_OFST)

#define PE_M17_GSC_Y_BASE			(PE_M17_DE_BASE + PE_M17_GSC_Y_OFST)
#define PE_M17_GSC_C_BASE			(PE_M17_DE_BASE + PE_M17_GSC_C_OFST)

#define PE_M17_VCP_DE_BASE			(PE_M17_DE_BASE + PE_M17_VCP_DE_OFST)
#define PE_M17_VCP_DISP_BASE		(PE_M17_DE_BASE + PE_M17_VCP_DISP_OFST)

#define PE_M17_SR_SHP_BASE			(PE_M17_DE_BASE + PE_M17_SR_SHP_OFST)
#define PE_M17_SR_SHP_BRG_BASE		(PE_M17_DE_BASE + PE_M17_SR_SHP_BRG_OFST)
#define PE_M17_SR_PSC_Y_BASE		(PE_M17_DE_BASE + PE_M17_SR_PSC_Y_OFST)
#define PE_M17_SR_PSC_C_BASE		(PE_M17_DE_BASE + PE_M17_SR_PSC_C_OFST)

#define PE_M17_P1_SHP_L_BASE		(PE_M17_DE_BASE + PE_M17_P1_SHP_L_OFST)
#define PE_M17_P1_SHP_PSP_BASE		(PE_M17_DE_BASE + PE_M17_P1_SHP_PSP_OFST)

#define PE_M17_P1_CCO_E_BASE		(PE_M17_DE_BASE + PE_M17_P1_CCO_E_OFST)
#define PE_M17_P1_CCO_O_BASE		(PE_M17_DE_BASE + PE_M17_P1_CCO_O_OFST)

#define PE_M17_LED_BASE				(PE_M17_DE_BASE + PE_M17_LED_OFST)
#define PE_M17_LED_RP_BASE			(PE_M17_DE_BASE + PE_M17_LED_RP_OFST)

#define PE_M17_DDR_DB_BASE			(gMemCfgBe[2].fw[4].fw_base)
#define PE_M17_DDR_DB_SIZE			(gMemCfgBe[2].fw[4].fw_size)
#define PE_M17_VSD_BASE				(PE_M17_DE_BASE + PE_M17_VSD_OFST)


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

#endif	/* _PE_REG_DEF_M17_H_ */

