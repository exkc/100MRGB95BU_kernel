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

/** @file pe_reg_def_m23.h
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

#ifndef _PE_REG_DEF_M23_H_
#define _PE_REG_DEF_M23_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#if 0	//Ref. (see REGISTER/abp_base.h) (M23A0_PQE_FW_FPGA)
#define PE_M23_CC_BASE                  0xCC4B1000   //( 0xCC4B1000, 0xCC4B1494)
#define PE_M23_CC2_BASE                 0xCC4B1500   //( 0xCC4B1500, 0xCC4B1A40)
#define PE_M23_CVD_BASE                 0xCC690700   //( 0xCC690700, 0xCC690F90)
#define PE_M23_CVI_A_BASE               0xCC690200   //( 0xCC690200, 0xCC6902F0)
#define PE_M23_CVI_B_BASE               0xCC690300   //( 0xCC690300, 0xCC6903F0)
#define PE_M23_DBGOSD_BASE              0xCC4B0900   //( 0xCC4B0900, 0xCC4B0918)
#define PE_M23_DBG_PIP_BASE             0xCC4B2900   //( 0xCC4B2900, 0xCC4B294C)
#define PE_M23_DCF_BASE                 0xCC4B0A00   //( 0xCC4B0A00, 0xCC4B0A4C)
#define PE_M23_DNE0_BASE                0xCC770300   //( 0xCC770300, 0xCC77094C)
#define PE_M23_MCP_BASE                 0xCC8E0800   //( 0xCC8E0800, 0xCC8E0D2C)
#define PE_M23_MC_BASE                  0xCC8E0000   //( 0xCC8E0000, 0xCC8E00EC)
#define PE_M23_ME0_TOP_BASE             0xCC9C2400   //( 0xCC9C2400, 0xCC9C2F94)
#define PE_M23_ME0_MES_BASE             0xCC9C3C00   //( 0xCC9C3C04, 0xCC9C5208)
#define PE_M23_ME0_MEP_BASE             0xCC9C5400   //( 0xCC9C5400, 0xCC9C6714)
#define PE_M23_ME0_MCU_BASE             0xCC9C6C00   //( 0xCC9C6C00, 0xCC9C73D4)
#define PE_M23_ME0_MCU_SEC_BASE         0xCC9C7400   //( 0xCC9C7400, 0xCC9C86BC)
#define PE_M23_ME1_TOP_BASE             0xCC9C9500   //( 0xCC9C9500, 0xCC9C9994)
#define PE_M23_ME1_MES_BASE             0xCC9CA100   //( 0xCC9CA104, 0xCC9CA908)
#define PE_M23_ME1_MEP_BASE             0xCC9CAD00   //( 0xCC9CAD00, 0xCC9CB814)
#define PE_M23_ME1_MCU_BASE             0xCC9CBD00   //( 0xCC9CBD00, 0xCC9CCD20)
#define PE_M23_ME0_SPP_BASE             0xCC9C1000   //( 0xCC9C1000, 0xCC9C13E8)
#define PE_M23_FME_SSD_BASE             0xCC9C1800   //( 0xCC9C1800, 0xCC9C1FF8)
#define PE_M23_FMS_BASE                 0xCC951000   //( 0xCC951000, 0xCC951AA8)
#define PE_M23_FPP_F0_BASE              0xCC6D1600   //( 0xCC6D1600, 0xCC6D1878)
#define PE_M23_BDD_F0_BASE              0xCC6D2000   //( 0xCC6D2000, 0xCC6D25A0)
#define PE_M23_GSC_Y_BASE               0xCC830500   //( 0xCC830500, 0xCC8306E8)
#define PE_M23_GSC_C_BASE               0xCC830800   //( 0xCC830800, 0xCC8309E8)
#define PE_M23_HDR_BUF_DE_BASE          0xCC620200   //( 0xCC620200, 0xCC6202D4)
#define PE_M23_HDR_BUF_HDR_BASE         0xCC620600   //( 0xCC620600, 0xCC62060C)
#define PE_M23_HDR10_BASE               0xCC620800   //( 0xCC620800, 0xCC620C40)
#define PE_M23_IPP_M0_META_BASE         0xCC8C0200   //( 0xCC8C0200, 0xCC8C03FC)
#define PE_M23_GAV_HDR_S_BASE           0xCC6D3700   //( 0xCC6D3700, 0xCC6D39BC)
#define PE_M23_IPP_M0_BASE              0xCC6D0400   //( 0xCC6D0400, 0xCC6D0540)
#define PE_M23_IPP_S0_BASE              0xCC6D0800   //( 0xCC6D0800, 0xCC6D08AC)
#define PE_M23_IPP_C0_BASE              0xCC6D0A00   //( 0xCC6D0A00, 0xCC6D0A84)
#define PE_M23_IPP_G0_BASE              0xCC6D3B00   //( 0xCC6D3B00, 0xCC6D3BD8)
#define PE_M23_IPP_H0_BASE              0xCC6D0C00   //( 0xCC6D0C00, 0xCC6D0C3C)
#define PE_M23_L3D_BASE                 0xCC4B0F00   //( 0xCC4B0F00, 0xCC4B0F74)
#define PE_M23_LED_BASE                 0xCC430000   //( 0xCC430000, 0xCC43218C)
#define PE_M23_LED_BV_DSC_BASE          0xCC432800   //( 0xCC432800, 0xCC432848)
#define PE_M23_LED_BV_USC_BASE          0xCC432A00   //( 0xCC432A00, 0xCC432ACC)
#define PE_M23_MCU_BASE                 0xCC080000   //( 0xCC080000, 0xCC0800F8)
#define PE_M23_MCU_IPC_BASE             0xCC0A0000   //( 0xCC0A0000, 0xCC0A03FC)
#define PE_M23_MCU_EDMA_BASE            0xCC0C0000   //( 0xCC0C0000, 0xCC0C0014)
#define PE_M23_MCU_GK_AND_IPC_BASE      0xCCE00000   //( 0xCCE00000, 0xCCE00FFC)
#define PE_M23_IMX_MIF0_BASE            0xCC6D2A00   //( 0xCC6D2A00, 0xCC6D2C04)
#define PE_M23_IMX_MIF1_BASE            0xCC6D2D00   //( 0xCC6D2D00, 0xCC6D2E0C)
#define PE_M23_ND0_MIF_BASE             0xCC5B0E00   //( 0xCC5B0E00, 0xCC5B0FE8)
#define PE_M23_SRE_MIF_BASE             0xCC573100   //( 0xCC573100, 0xCC5731E8)
#define PE_M23_CCO_MIF0_BASE            0xCC4B0C00   //( 0xCC4B0C00, 0xCC4B0D00)
#define PE_M23_ME0_MIF_BASE             0xCC9C0200   //( 0xCC9C0200, 0xCC9C07AC)
#define PE_M23_FMS_MIF0_BASE            0xCC950A00   //( 0xCC950A00, 0xCC950BC8)
#define PE_M23_FMC_MIF0_BASE            0xCC8E1800   //( 0xCC8E1800, 0xCC8E198C)
#define PE_M23_FMC_MIF1_BASE            0xCC8E1A00   //( 0xCC8E1A00, 0xCC8E1B9C)
#define PE_M23_DNE_MIF0_BASE            0xCC772100   //( 0xCC772100, 0xCC7722BC)
#define PE_M23_CVI_MON_BASE             0xCC691000   //( 0xCC691000, 0xCC6910FC)
#define PE_M23_HDR_MON_BASE             0xCC620100   //( 0xCC620100, 0xCC6201FC)
#define PE_M23_IMX_MON_BASE             0xCC6D0B00   //( 0xCC6D0B00, 0xCC6D0BFC)
#define PE_M23_VDO_MON_BASE             0xCC710100   //( 0xCC710100, 0xCC7101FC)
#define PE_M23_ND0_MON_BASE             0xCC5B0D00   //( 0xCC5B0D00, 0xCC5B0DFC)
#define PE_M23_SRE_MON_BASE             0xCC570100   //( 0xCC570100, 0xCC5701FC)
#define PE_M23_FMC_MON_BASE             0xCC8E1100   //( 0xCC8E1100, 0xCC8E11FC)
#define PE_M23_GSC_MON_BASE             0xCC830B00   //( 0xCC830B00, 0xCC830BFC)
#define PE_M23_VSD_MON_BASE             0xCC4F4000   //( 0xCC4F4000, 0xCC4F40FC)
#define PE_M23_CCO_MON_BASE             0xCC4B0B00   //( 0xCC4B0B00, 0xCC4B0BFC)
#define PE_M23_LED_MON_BASE             0xCC433100   //( 0xCC433100, 0xCC4331FC)
#define PE_M23_ME0_MON_BASE             0xCC9C0100   //( 0xCC9C0100, 0xCC9C01FC)
#define PE_M23_FMS_MON_BASE             0xCC950100   //( 0xCC950100, 0xCC9501FC)
#define PE_M23_DNE_MON_BASE             0xCC770100   //( 0xCC770100, 0xCC7701FC)
#define PE_M23_MVI_RA_BASE              0xCC6D1A00   //( 0xCC6D1A00, 0xCC6D1A1C)
#define PE_M23_MVI_RB_BASE              0xCC6D0F00   //( 0xCC6D0F00, 0xCC6D0F1C)
#define PE_M23_VDO_CORE_BASE            0xCC710300   //( 0xCC710300, 0xCC7103FC)
#define PE_M23_VDO_GMAU_BASE            0xCC710400   //( 0xCC710400, 0xCC7104FC)
#define PE_M23_VDO_TOP_BASE             0xCC710700   //( 0xCC710700, 0xCC7107FC)
#define PE_M23_VDO_CRC_BASE             0xCC710800   //( 0xCC710800, 0xCC7108EC)
#define PE_M23_VDO_BODP_RC0_BASE         0xCC710900   //( 0xCC710900, 0xCC71091C)
#define PE_M23_DNR0_MUX_BASE            0xCC5B0A00   //( 0xCC5B0A00, 0xCC5B0A94)
#define PE_M23_DNR1_MUX_BASE            0xCCC00A00   //( 0xCCC00A00, 0xCCC00A94)
#define PE_M23_ND0_BASE                 0xCC5B0100   //( 0xCC5B0100, 0xCC5B04E4)
#define PE_M23_DNR0_BASE                0xCC5B0500   //( 0xCC5B0500, 0xCC5B0998)
#define PE_M23_AFBC0_BASE               0xCC4B0800   //( 0xCC4B0800, 0xCC4B08FC)
#define PE_M23_OSD_STATUS_BASE          0xCC4B0100   //( 0xCC4B0100, 0xCC4B013C)
#define PE_M23_OSD_COMMON_BASE          0xCC4B0100   //( 0xCC4B0140, 0xCC4B0170)
#define PE_M23_OSD_BOSD_BASE            0xCC4B0100   //( 0xCC4B0280, 0xCC4B02E4)
#define PE_M23_OSD_IMAGE0_BASE          0xCC4B0300   //( 0xCC4B0300, 0xCC4B03EC)
#define PE_M23_OSD_CURSOR_BASE          0xCC4B0600   //( 0xCC4B0600, 0xCC4B067C)
#define PE_M23_PWM_BASE                 0xCC4F0100   //( 0xCC4F0100, 0xCC4F01FC)
#define PE_M23_ROT_BASE                 0xCC8E1200   //( 0xCC8E1200, 0xCC8E1398)
#define PE_M23_SRE_COMM_BASE            0xCC570300   //( 0xCC570300, 0xCC570318)
#define PE_M23_SCY_2K_BASE              0xCC570B00   //( 0xCC570B00, 0xCC570B24)
#define PE_M23_SCY_4K_BASE              0xCC571C00   //( 0xCC571C00, 0xCC571CA0)
#define PE_M23_SCC_4K_BASE              0xCC572500   //( 0xCC572500, 0xCC57258C)
#define PE_M23_SRE_MUX_BASE             0xCC570500   //( 0xCC570500, 0xCC570594)
#define PE_M23_SHY_2K_BASE              0xCC570C00   //( 0xCC570C00, 0xCC5713FC)
#define PE_M23_CVI_CTRL_BASE            0xCC690000   //( 0xCC690000, 0xCC6900FC)
#define PE_M23_IMX_CTRL_BASE            0xCC6D0000   //( 0xCC6D0000, 0xCC6D00FC)
#define PE_M23_IMX_CTRL1_BASE           0xCC6D0100   //( 0xCC6D0100, 0xCC6D01F4)
#define PE_M23_GAV_CTRL_BASE            0xCC6D3600   //( 0xCC6D3600, 0xCC6D36FC)
#define PE_M23_VDO_CTRL_BASE            0xCC710000   //( 0xCC710000, 0xCC7100FC)
#define PE_M23_HDR_CTRL_BASE            0xCC620000   //( 0xCC620000, 0xCC6200FC)
#define PE_M23_HDR_CTRL1_BASE           0xCCCC2000   //( 0xCCCC2000, 0xCCCC20FC)
#define PE_M23_ND0_CTRL_BASE            0xCC5B0000   //( 0xCC5B0000, 0xCC5B00FC)
#define PE_M23_SRE_CTRL_BASE            0xCC570000   //( 0xCC570000, 0xCC5700FC)
#define PE_M23_GSC_CTRL_BASE            0xCC830000   //( 0xCC830000, 0xCC8300F8)
#define PE_M23_VSD_CTRL_BASE            0xCC4F0000   //( 0xCC4F0000, 0xCC4F00FC)
#define PE_M23_VSD_CTRL1_BASE           0xCC4F0B00   //( 0xCC4F0B1C, 0xCC4F0BD8)
#define PE_M23_CCO_CTRL_BASE            0xCC4B0000   //( 0xCC4B0000, 0xCC4B00FC)
#define PE_M23_CCO_CTRL1_BASE           0xCC4B0E00   //( 0xCC4B0E14, 0xCC4B0EBC)
#define PE_M23_LED_CTRL_BASE            0xCC433000   //( 0xCC433000, 0xCC4330FC)
#define PE_M23_ME0_CTRL_BASE            0xCC9C0000   //( 0xCC9C0000, 0xCC9C00FC)
#define PE_M23_FMC_CTRL_BASE            0xCC8E1000   //( 0xCC8E1000, 0xCC8E10FC)
#define PE_M23_FMS_CTRL_BASE            0xCC950000   //( 0xCC950000, 0xCC9500FC)
#define PE_M23_DNE_CTRL_BASE            0xCC770000   //( 0xCC770000, 0xCC7700FC)
#define PE_M23_VCP_DE_BASE              0xCC4F1000   //( 0xCC4F1000, 0xCC4F12D8)
#define PE_M23_VCP_DISP_BASE            0xCC4F1000   //( 0xCC4F1400, 0xCC4F1954)
#define PE_M23_CVI_VERI_BASE            0xCC691100   //( 0xCC691100, 0xCC69110C)
#define PE_M23_HDR_VERI_BASE            0xCC622100   //( 0xCC622100, 0xCC62210C)
#define PE_M23_IMX_VERI_BASE            0xCC6D0D00   //( 0xCC6D0D00, 0xCC6D0DAC)
#define PE_M23_VDO_VERI_BASE            0xCC710200   //( 0xCC710200, 0xCC71020C)
#define PE_M23_ND0_VERI_BASE            0xCC5B1100   //( 0xCC5B1100, 0xCC5B110C)
#define PE_M23_SRE_VERI_BASE            0xCC570200   //( 0xCC570200, 0xCC57020C)
#define PE_M23_FMC_VERI_BASE            0xCC8E1400   //( 0xCC8E1400, 0xCC8E140C)
#define PE_M23_GSC_VERI_BASE            0xCC830100   //( 0xCC830100, 0xCC83010C)
#define PE_M23_VSD_VERI_BASE            0xCC4F3F00   //( 0xCC4F3F00, 0xCC4F3F0C)
#define PE_M23_CCO_VERI_BASE            0xCC4B2200   //( 0xCC4B2200, 0xCC4B228C)
#define PE_M23_LED_VERI_BASE            0xCC433200   //( 0xCC433200, 0xCC43320C)
#define PE_M23_ME0_VERI_BASE            0xCC9C8C00   //( 0xCC9C8C00, 0xCC9C8C0C)
#define PE_M23_FMS_VERI_BASE            0xCC950200   //( 0xCC950200, 0xCC95020C)
#define PE_M23_DNE_VERI_BASE            0xCC770200   //( 0xCC770200, 0xCC77020C)
#define PE_M23_DTM_BASE                 0xCC4F0200   //( 0xCC4F0200, 0xCC4F031C)
#define PE_M23_VSD_SHP_BASE             0xCC4F2000   //( 0xCC4F2000, 0xCC4F28FC)
#endif
#define PE_M23_DE_BASE				(0xCC000000)
#define PE_M23_P1_CC_OFST			(0x4B1000)
#define PE_M23_P1_CC2_OFST			(0x4B1500)
#define PE_M23_CVI_A_OFST			(0x690200)
#define PE_M23_CVI_B_OFST			(0x690300)
#define PE_M23_GSC_Y_OFST			(0x830500)
#define PE_M23_GSC_C_OFST			(0x830800)
#define PE_M23_ND0_OFST				(0x5B0100)
#define PE_M23_DNR0_OFST			(0x5B0500)
#define PE_M23_ND0_VERI_OFST		(0x5B1100)
#define PE_M23_IMX_OFST				(0x6D00B8)
#define PE_M23_P1_SHP_L_OFST		(0x4F2000)
#define PE_M23_P1_VSD_DTM_OFST		(0x4F0200)
#define PE_M23_VCP_DISP_OFST		(0x4F1400)
#define PE_M23_VSD0_VERI_OFST		(0x4F3F00)
#define PE_M23_SR_2K_SHP_OFST		(0x570C00)

#define PE_M23_REG_WRITE_BASE		(0x0)
#define PE_M23_P1_CC_BASE			(PE_M23_DE_BASE + PE_M23_P1_CC_OFST)
#define PE_M23_P1_CC2_BASE			(PE_M23_DE_BASE + PE_M23_P1_CC2_OFST)
#define PE_M23_CVI_A_BASE			(PE_M23_DE_BASE + PE_M23_CVI_A_OFST)
#define PE_M23_CVI_B_BASE			(PE_M23_DE_BASE + PE_M23_CVI_B_OFST)
#define PE_M23_GSC_Y_BASE			(PE_M23_DE_BASE + PE_M23_GSC_Y_OFST)
#define PE_M23_GSC_C_BASE			(PE_M23_DE_BASE + PE_M23_GSC_C_OFST)
#define PE_M23_ND0_BASE				(PE_M23_DE_BASE + PE_M23_ND0_OFST)
#define PE_M23_DNR0_BASE			(PE_M23_DE_BASE + PE_M23_DNR0_OFST)
#define PE_M23_ND0_VERI_BASE		(PE_M23_DE_BASE + PE_M23_ND0_VERI_OFST)
#define PE_M23_IMX_BASE				(PE_M23_DE_BASE + PE_M23_IMX_OFST)
#define PE_M23_P1_SHP_L_BASE		(PE_M23_DE_BASE + PE_M23_P1_SHP_L_OFST)
#define PE_M23_P1_VSD_DTM_BASE		(PE_M23_DE_BASE + PE_M23_P1_VSD_DTM_OFST)
#define PE_M23_VCP_DISP_BASE		(PE_M23_DE_BASE + PE_M23_VCP_DISP_OFST)
#define PE_M23_VSD0_VERI_BASE		(PE_M23_DE_BASE + PE_M23_VSD0_VERI_OFST)
#define PE_M23_SR_2K_SHP_BASE		(PE_M23_DE_BASE + PE_M23_SR_2K_SHP_OFST)
#define PE_M23_CCO_VERI_BASE		(PE_M23_DE_BASE + 0x4B2200)
#define PE_M23_SRE_VERI_BASE		(PE_M23_DE_BASE + 0x570200)

#define PE_M23_HDR10_BASE           0xCC620800



#ifdef INCLUDE_KDRV_DE
#define PE_M23_DDR_DB0_BASE			(g_pe_db.base)
#define PE_M23_DDR_DB0_SIZE			(g_pe_db.size)
#define PE_M23_DDR_HDR_BASE			(g_pe_hdr.base)
#define PE_M23_DDR_HDR_SIZE			(g_pe_hdr.size)
#else
#define PE_M23_DDR_DB0_BASE			(0)
#define PE_M23_DDR_DB0_SIZE			(0)
#define PE_M23_DDR_HDR_BASE			(0)
#define PE_M23_DDR_HDR_SIZE			(0)
#endif

#define PE_M23_DDR_DB_BASE			(PE_M23_DDR_DB0_BASE)
#define PE_M23_DDR_DB_SIZE			(PE_M23_DDR_DB0_SIZE+PE_M23_DDR_HDR_SIZE)

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

#endif	/* _PE_REG_DEF_M23_H_ */

