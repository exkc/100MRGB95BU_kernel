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

/** @file pe_reg_def_o20.h
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

#ifndef _PE_REG_DEF_O20_H_
#define _PE_REG_DEF_O20_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
/* define for using o20a wcp(ov) register
* should be undef, because of o20a ov removed */
/* 20140526, sj.youm, undef for bringup */
#undef PE_HW_O20_USE_O20_WCP_REG

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
/* O20_DE_BASE */
#define PE_O20_DE_BASE				(0xC9000000)

#define PE_O20_HDMI_A_OFST			(0x000100)
#define PE_O20_HDMI_B_OFST			(0x000140)
#define PE_O20_HDMI_C_OFST			(0x000180)
#define PE_O20_HDMI_D_OFST			(0x0001C0)
#define PE_O20_CVI_A_OFST			(0x000200)
#define PE_O20_CVI_B_OFST			(0x000300)
#define PE_O20_CVI_C_OFST			(0x000400)
#define PE_O20_CVI_D_OFST			(0x000500)

#define PE_O20_IMX_OFST				(0x0140B8)
#define PE_O20_IPP_OFST				(0x014400)

#define PE_O20_ND0_OFST				(0x018100)
#define PE_O20_ND1_OFST				(0x01A100)
#define PE_O20_DNR0_OFST			(0x018500)
#define PE_O20_DNR1_OFST			(0x01A500)
#define PE_O20_ND_OBC_O_OFST		(0x019200)
#define PE_O20_ND_OBC_F_OFST		(0x019400)

#if 0
#define PE_O20_SC_V1_OFST			(0x000044)
#define PE_O20_SC_V2_OFST			(0x000060)
#define PE_O20_SC_H1_OFST			(0x000074)
#define PE_O20_SC_H2_OFST			(0x000090)
#endif

#define PE_O20_GSC_Y_OFST			(0x007500)
#define PE_O20_GSC_Y_G0_OFST		(0x007500)
#define PE_O20_GSC_Y_G1_OFST		(0x0075A4)
#define PE_O20_GSC_C_OFST			(0x007700)
#define PE_O20_GSC_C_G0_OFST		(0x007700)
#define PE_O20_GSC_C_G1_OFST		(0x0077A4)


#define PE_O20_SR_CHR_SHP_OFST		(0x008F00)
#define PE_O20_SR_2K_SHP_OFST		(0x008700)
#define PE_O20_SR_MERG_OFST		    (0x009C00)

#define PE_O20_VCP_DISP_OFST		(0x00C400)
#define PE_O20_VSD_VERI_OFST		(0x00B800)

#define PE_O20_P1_SHP_L_OFST		(0x00D000)
#define PE_O20_P1_VSD_OBC_O_OFST	(0x00B300)
#define PE_O20_P1_VSD_OBC_F_OFST	(0x00B500)
#define PE_O20_P1_VSD_RCE_O_OFST	(0x00B200)
#define PE_O20_P1_VSD_RCE_F_OFST	(0x00B280)
#define PE_O20_P1_VSD_DTM_OFST	(0x00BC00)
#define PE_O20_P1_SHP_OSD0_OFST		(0x011C00)
#define PE_O20_P1_SHP_OSD1_OFST		(0x012300)

#define PE_O20_P1_CCO_E_OFST		(0x011000)
#define PE_O20_P1_CCO_O_OFST		(0x011500)
#define PE_O20_P1_CCO2_E_OFST		(0x012A00)
#define PE_O20_P1_CCO2_O_OFST		(0x012E00)

#define PE_O20_LED_OFST				(0x020000)
#define PE_O20_LED_RP_OFST			(0x020540)
#define PE_O20_LED_DCNT_OFST		(0x023800)
#define PE_O20_VSD_OFST				(0x00B0B0)
#define PE_O20_ND0_VERI_OFST        (0x019100)

#define PE_O20_REG_WRITE_BASE		(0x0)
#define PE_O20_P1_CCO_EO_DIFF		(PE_O20_P1_CCO_O_OFST - PE_O20_P1_CCO_E_OFST)

#define PE_O20_HDMI_A_BASE			(PE_O20_DE_BASE + PE_O20_HDMI_A_OFST)
#define PE_O20_HDMI_B_BASE			(PE_O20_DE_BASE + PE_O20_HDMI_B_OFST)
#define PE_O20_HDMI_C_BASE			(PE_O20_DE_BASE + PE_O20_HDMI_C_OFST)
#define PE_O20_HDMI_D_BASE			(PE_O20_DE_BASE + PE_O20_HDMI_D_OFST)
#define PE_O20_CVI_A_BASE			(PE_O20_DE_BASE + PE_O20_CVI_A_OFST)
#define PE_O20_CVI_B_BASE			(PE_O20_DE_BASE + PE_O20_CVI_B_OFST)
#define PE_O20_CVI_C_BASE			(PE_O20_DE_BASE + PE_O20_CVI_C_OFST)
#define PE_O20_CVI_D_BASE			(PE_O20_DE_BASE + PE_O20_CVI_D_OFST)

#define PE_O20_IMX_BASE				(PE_O20_DE_BASE + PE_O20_IMX_OFST)
#define PE_O20_IPP_BASE				(PE_O20_DE_BASE + PE_O20_IPP_OFST)

#define PE_O20_H10_E_BASE			(PE_O20_DE_BASE + 0x003800)
#define PE_O20_H10_O_BASE			(PE_O20_DE_BASE + 0x004800)
#define PE_O20_H10_P_BASE			(PE_O20_DE_BASE + 0x003E00)
#define PE_O20_S2H_E_BASE			(PE_O20_DE_BASE + 0x003C00)
#define PE_O20_S2H_O_BASE			(PE_O20_DE_BASE + 0x004C00)
#define PE_O20_GAV_BASE				(PE_O20_DE_BASE + 0x017700)
#define PE_O20_H10_SIZE				(0x03D0)
#define PE_O20_H10_P_SIZE			(0x01A0)
#define PE_O20_S2H_SIZE				(0x01C4)
#define PE_O20_GAV_SIZE				(0x03A4)

#define PE_O20_ND0_BASE				(PE_O20_DE_BASE + PE_O20_ND0_OFST)
#define PE_O20_ND1_BASE				(PE_O20_DE_BASE + PE_O20_ND1_OFST)
#define PE_O20_DNR0_BASE			(PE_O20_DE_BASE + PE_O20_DNR0_OFST)
#define PE_O20_DNR1_BASE			(PE_O20_DE_BASE + PE_O20_DNR1_OFST)
#define PE_O20_ND_OBC_O_BASE		(PE_O20_DE_BASE + PE_O20_ND_OBC_O_OFST)
#define PE_O20_ND_OBC_F_BASE		(PE_O20_DE_BASE + PE_O20_ND_OBC_F_OFST)

#define PE_O20_GSC_Y_BASE			(PE_O20_DE_BASE + PE_O20_GSC_Y_OFST)
#define PE_O20_GSC_C_BASE			(PE_O20_DE_BASE + PE_O20_GSC_C_OFST)

#define PE_O20_VCP_DISP_BASE		(PE_O20_DE_BASE + PE_O20_VCP_DISP_OFST)
#define PE_O20_VSD_VERI_BASE		(PE_O20_DE_BASE + PE_O20_VSD_VERI_OFST)

#define PE_O20_SR_CHR_SHP_BASE		(PE_O20_DE_BASE + PE_O20_SR_CHR_SHP_OFST)
#define PE_O20_SR_2K_SHP_BASE		(PE_O20_DE_BASE + PE_O20_SR_2K_SHP_OFST)
#define PE_O20_SR_MERG_BASE			(PE_O20_DE_BASE + PE_O20_SR_MERG_OFST)

#define PE_O20_P1_SHP_L_BASE		(PE_O20_DE_BASE + PE_O20_P1_SHP_L_OFST)
#define PE_O20_P1_VSD_OBC_O_BASE	(PE_O20_DE_BASE + PE_O20_P1_VSD_OBC_O_OFST)
#define PE_O20_P1_VSD_OBC_F_BASE	(PE_O20_DE_BASE + PE_O20_P1_VSD_OBC_F_OFST)
#define PE_O20_P1_VSD_RCE_O_BASE	(PE_O20_DE_BASE + PE_O20_P1_VSD_RCE_O_OFST)
#define PE_O20_P1_VSD_RCE_F_BASE	(PE_O20_DE_BASE + PE_O20_P1_VSD_RCE_F_OFST)
#define PE_O20_P1_VSD_DTM_BASE		(PE_O20_DE_BASE + PE_O20_P1_VSD_DTM_OFST)
#define PE_O20_P1_SHP_OSD0_BASE		(PE_O20_DE_BASE + PE_O20_P1_SHP_OSD0_OFST)
#define PE_O20_P1_SHP_OSD1_BASE		(PE_O20_DE_BASE + PE_O20_P1_SHP_OSD1_OFST)

#define PE_O20_P1_CCO_E_BASE		(PE_O20_DE_BASE + PE_O20_P1_CCO_E_OFST)
#define PE_O20_P1_CCO_O_BASE		(PE_O20_DE_BASE + PE_O20_P1_CCO_O_OFST)
#define PE_O20_P1_CCO2_E_BASE		(PE_O20_DE_BASE + PE_O20_P1_CCO2_E_OFST)
#define PE_O20_P1_CCO2_O_BASE		(PE_O20_DE_BASE + PE_O20_P1_CCO2_O_OFST)

#define PE_O20_LED_BASE				(PE_O20_DE_BASE + PE_O20_LED_OFST)
#define PE_O20_LED_RP_BASE			(PE_O20_DE_BASE + PE_O20_LED_RP_OFST)
#define PE_O20_LED_DCNT_BASE		(PE_O20_DE_BASE + PE_O20_LED_DCNT_OFST)

#define PE_O20_VSD_BASE				(PE_O20_DE_BASE + PE_O20_VSD_OFST)
#define PE_O20_MCU_BASE				(PE_O20_DE_BASE + 0x260D8)
#define PE_O20_CCO_VERI_BASE		(PE_O20_DE_BASE + 0x12200)
#define PE_O20_ND0_VERI_BASE		(PE_O20_DE_BASE + PE_O20_ND0_VERI_OFST)

#ifdef PQE_NEW_MAP
#define PE_O20_DDR_DB0_BASE			(g_pe_db.base)
#define PE_O20_DDR_DB0_SIZE			(g_pe_db.size)
#define PE_O20_DDR_DB1_BASE			(g_pe_hdr.base)
#define PE_O20_DDR_DB1_SIZE			(g_pe_hdr.size)
#define PE_O20_DDR_DB2_BASE			(0)
#define PE_O20_DDR_DB2_SIZE			(0)
#define PE_O20_DDR_DB3_BASE			(0)
#define PE_O20_DDR_DB3_SIZE			(0)
#else
#define PE_O20_DDR_DB0_BASE			(gMemCfgPe[0].db[0].db_base)
#define PE_O20_DDR_DB0_SIZE			(gMemCfgPe[0].db[0].db_size)
#define PE_O20_DDR_DB1_BASE			(gMemCfgPe[0].db[1].db_base)
#define PE_O20_DDR_DB1_SIZE			(gMemCfgPe[0].db[1].db_size)
#define PE_O20_DDR_DB2_BASE			(gMemCfgPe[0].db[2].db_base)
#define PE_O20_DDR_DB2_SIZE			(gMemCfgPe[0].db[2].db_size)
#define PE_O20_DDR_DB3_BASE			(gMemCfgPe[0].db[3].db_base)
#define PE_O20_DDR_DB3_SIZE			(gMemCfgPe[0].db[3].db_size)
#endif

#define PE_F20_DDR_BASE				(PE_O20_DDR_DB0_BASE + 0x80000)

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

#endif	/* _PE_REG_DEF_O20_H_ */

