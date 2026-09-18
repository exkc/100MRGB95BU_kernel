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

/** @file pe_reg_def_m19.h
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

#ifndef _PE_REG_DEF_M19_H_
#define _PE_REG_DEF_M19_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
/* define for using m19a wcp(ov) register
* should be undef, because of m19a ov removed */
/* 20140526, sj.youm, undef for bringup */
#undef PE_HW_M19_USE_M19_WCP_REG

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
/* M19_DE_BASE */
#define PE_M19_DE_BASE				(0xC9000000)

#define PE_M19_HDMI_A_OFST			(0x000100)
#define PE_M19_HDMI_B_OFST			(0x000140)
#define PE_M19_HDMI_C_OFST			(0x000180)
#define PE_M19_HDMI_D_OFST			(0x0001C0)
#define PE_M19_CVI_A_OFST			(0x000200)
#define PE_M19_CVI_B_OFST			(0x000300)
#define PE_M19_CVI_C_OFST			(0x000400)
#define PE_M19_CVI_D_OFST			(0x000500)

#define PE_M19_IMX_OFST				(0x0140B8)
#define PE_M19_HDR_LG_0_OFST		(0x005800)
#define PE_M19_HDR_LG_1_OFST		(0x006800)
#define PE_M19_S2H_OFST				(0x005E00)
#define PE_M19_S2H_2_OFST			(0x006E00)
#define PE_M19_ND0_OFST				(0x003100)
#define PE_M19_ND1_OFST				(0x004100)
#define PE_M19_DNR0_OFST			(0x003500)

#if 0
#define PE_M19_SC_V1_OFST			(0x000044)
#define PE_M19_SC_V2_OFST			(0x000060)
#define PE_M19_SC_H1_OFST			(0x000074)
#define PE_M19_SC_H2_OFST			(0x000090)
#endif

#define PE_M19_GSC_Y_OFST			(0x007500)
#define PE_M19_GSC_Y_G0_OFST		(0x007500)
#define PE_M19_GSC_Y_G1_OFST		(0x0075A4)
#define PE_M19_GSC_C_OFST			(0x007700)
#define PE_M19_GSC_C_G0_OFST		(0x007700)
#define PE_M19_GSC_C_G1_OFST		(0x0077A4)


#define PE_M19_SR_2K_SHP_OFST		(0x009000)
#define PE_M19_SR_2K_MSC_Y_OFST		(0x008600)
#define PE_M19_SR_MSC_Y_OFST		(0x00A000)
#define PE_M19_SR_MSC_C_OFST		(0x00A100)

#define PE_M19_VCP_DISP_OFST		(0x00C400)

#define PE_M19_P1_SHP_L_OFST		(0x00D000)
#define PE_M19_P1_SHP_PSP_OFST		(0x00B220)
#define PE_M19_P1_SHP_PSP_GAIN_OFST	(0x00B400)
#define PE_M19_P1_SHP_OSD_OFST		(0x011C00)

#define PE_M19_P1_CCO_E_OFST		(0x011000)
#define PE_M19_P1_CCO_O_OFST		(0x011500)

#define PE_M19_LED_OFST				(0x020000)
#define PE_M19_LED_RP_OFST			(0x020540)
#define PE_M19_LED_DCNT_OFST		(0x023800)
#define PE_M19_VSD_OFST				(0x00B0B0)

#define PE_M19_REG_WRITE_BASE		(0x0)
#define PE_M19_P1_CCO_EO_DIFF		(PE_M19_P1_CCO_O_OFST - PE_M19_P1_CCO_E_OFST)

#define PE_M19_HDMI_A_BASE			(PE_M19_DE_BASE + PE_M19_HDMI_A_OFST)
#define PE_M19_HDMI_B_BASE			(PE_M19_DE_BASE + PE_M19_HDMI_B_OFST)
#define PE_M19_HDMI_C_BASE			(PE_M19_DE_BASE + PE_M19_HDMI_C_OFST)
#define PE_M19_HDMI_D_BASE			(PE_M19_DE_BASE + PE_M19_HDMI_D_OFST)
#define PE_M19_CVI_A_BASE			(PE_M19_DE_BASE + PE_M19_CVI_A_OFST)
#define PE_M19_CVI_B_BASE			(PE_M19_DE_BASE + PE_M19_CVI_B_OFST)
#define PE_M19_CVI_C_BASE			(PE_M19_DE_BASE + PE_M19_CVI_C_OFST)
#define PE_M19_CVI_D_BASE			(PE_M19_DE_BASE + PE_M19_CVI_D_OFST)

#define PE_M19_IMX_BASE				(PE_M19_DE_BASE + PE_M19_IMX_OFST)

#define PE_M19_HDR_LG_0_BASE		(PE_M19_DE_BASE + PE_M19_HDR_LG_0_OFST)
#define PE_M19_HDR_LG_1_BASE		(PE_M19_DE_BASE + PE_M19_HDR_LG_1_OFST)
#define PE_M19_S2H_BASE				(PE_M19_DE_BASE + PE_M19_S2H_OFST)
#define PE_M19_S2H_2_BASE			(PE_M19_DE_BASE + PE_M19_S2H_2_OFST)
#define PE_M19_HDR10_SIZE			(0x03D8)
#define PE_M19_S2H_SIZE				(0x018C)

#define PE_M19_ND0_BASE				(PE_M19_DE_BASE + PE_M19_ND0_OFST)
#define PE_M19_ND1_BASE				(PE_M19_DE_BASE + PE_M19_ND1_OFST)
#define PE_M19_DNR0_BASE			(PE_M19_DE_BASE + PE_M19_DNR0_OFST)

#define PE_M19_GSC_Y_BASE			(PE_M19_DE_BASE + PE_M19_GSC_Y_OFST)
#define PE_M19_GSC_C_BASE			(PE_M19_DE_BASE + PE_M19_GSC_C_OFST)

#define PE_M19_VCP_DISP_BASE		(PE_M19_DE_BASE + PE_M19_VCP_DISP_OFST)

#define PE_M19_SR_2K_SHP_BASE		(PE_M19_DE_BASE + PE_M19_SR_2K_SHP_OFST)
#define PE_M19_SR_2K_MSC_Y_BASE		(PE_M19_DE_BASE + PE_M19_SR_2K_MSC_Y_OFST)
#define PE_M19_SR_MSC_Y_BASE		(PE_M19_DE_BASE + PE_M19_SR_MSC_Y_OFST)
#define PE_M19_SR_MSC_C_BASE		(PE_M19_DE_BASE + PE_M19_SR_MSC_C_OFST)

#define PE_M19_P1_SHP_L_BASE		(PE_M19_DE_BASE + PE_M19_P1_SHP_L_OFST)
#define PE_M19_P1_SHP_PSP_BASE		(PE_M19_DE_BASE + PE_M19_P1_SHP_PSP_OFST)
#define PE_M19_P1_SHP_PSP_GAIN_BASE	(PE_M19_DE_BASE + PE_M19_P1_SHP_PSP_GAIN_OFST)
#define PE_M19_P1_SHP_OSD_BASE		(PE_M19_DE_BASE + PE_M19_P1_SHP_OSD_OFST)

#define PE_M19_P1_CCO_E_BASE		(PE_M19_DE_BASE + PE_M19_P1_CCO_E_OFST)
#define PE_M19_P1_CCO_O_BASE		(PE_M19_DE_BASE + PE_M19_P1_CCO_O_OFST)

#define PE_M19_LED_BASE				(PE_M19_DE_BASE + PE_M19_LED_OFST)
#define PE_M19_LED_RP_BASE			(PE_M19_DE_BASE + PE_M19_LED_RP_OFST)
#define PE_M19_LED_DCNT_BASE		(PE_M19_DE_BASE + PE_M19_LED_DCNT_OFST)

#define PE_M19_VSD_BASE			(PE_M19_DE_BASE + PE_M19_VSD_OFST)

#define PE_M19_DDR_DB0_BASE			(gMemCfgPe[0].db[0].db_base)
#define PE_M19_DDR_DB0_SIZE			(gMemCfgPe[0].db[0].db_size)
#define PE_M19_DDR_DB1_BASE			(gMemCfgPe[0].db[1].db_base)
#define PE_M19_DDR_DB1_SIZE			(gMemCfgPe[0].db[1].db_size)
#define PE_M19_DDR_DB2_BASE			(gMemCfgPe[0].db[2].db_base)
#define PE_M19_DDR_DB2_SIZE			(gMemCfgPe[0].db[2].db_size)
#define PE_M19_DDR_DB3_BASE			(gMemCfgPe[0].db[3].db_base)
#define PE_M19_DDR_DB3_SIZE			(gMemCfgPe[0].db[3].db_size)

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

#endif	/* _PE_REG_DEF_M19_H_ */

