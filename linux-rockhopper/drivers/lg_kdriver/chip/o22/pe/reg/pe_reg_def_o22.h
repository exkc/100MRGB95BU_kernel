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

/** @file pe_reg_def_o22.h
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

#ifndef _PE_REG_DEF_O22_H_
#define _PE_REG_DEF_O22_H_

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
/* O22_DE_BASE */
#define PE_O22_DE_BASE				(0xCC000000)

#if 0	//Ref. (see REGISTER/abp_base.h) (O22A0_PQE_FW)
#define APB_CC_BASE                  0xCC481000   //( 0xCC481000, 0xCC481494)
#define APB_CC2_BASE                 0xCC481500   //( 0xCC481500, 0xCC481A40)
#define APB_CC2_E_BASE               0xCC482A00   //( 0xCC482A00, 0xCC482B1C)
#define APB_CC2_O_BASE               0xCC482E00   //( 0xCC482E00, 0xCC482F1C)
#define APB_CVD_BASE                 0xCC840700   //( 0xCC840700, 0xCC840F90)
#define APB_CVI_A_BASE               0xCC840200   //( 0xCC840200, 0xCC8402F0)
#define APB_CVI_B_BASE               0xCC840300   //( 0xCC840300, 0xCC8403F0)
#define APB_CVI_C_BASE               0xCC840400   //( 0xCC840400, 0xCC8404F0)
#define APB_CVI_D_BASE               0xCC840500   //( 0xCC840500, 0xCC8405F0)
#define APB_CVI_E_BASE               0xCC840600   //( 0xCC840600, 0xCC8406F0)
#define APB_DBGOSD_BASE              0xCC480900   //( 0xCC480900, 0xCC480918)
#define APB_DCF_BASE                 0xCC480A00   //( 0xCC480A00, 0xCC480A4C)
#define APB_DNE0_BASE                0xCC880300   //( 0xCC880300, 0xCC88094C)
#define APB_DNE1_BASE                0xCC881200   //( 0xCC881200, 0xCC88184C)
#define APB_DNNR_BASE                0xCC3A0000   //( 0xCC3A0000, 0xCC3A0FFC)
#define APB_DNSR_BASE                0xCC380000   //( 0xCC380000, 0xCC380FFC)
#define APB_DSC_BASE                 0xCC8A0000   //( 0xCC8A0000, 0xCC8A0044)
#define APB_MCP_BASE                 0xCC4C0800   //( 0xCC4C0800, 0xCC4C0D44)
#define APB_MC_BASE                  0xCC4C0000   //( 0xCC4C0000, 0xCC4C00E8)
#define APB_ME0_TOP_BASE             0xCC9C2400   //( 0xCC9C2400, 0xCC9C2FE4)
#define APB_ME0_MES_BASE             0xCC9C3C00   //( 0xCC9C3C04, 0xCC9C520C)
#define APB_ME0_MEP_BASE             0xCC9C5400   //( 0xCC9C5400, 0xCC9C6758)
#define APB_ME0_MCU_BASE             0xCC9C6C00   //( 0xCC9C6C00, 0xCC9C73D4)
#define APB_ME0_MCU_SEC_BASE         0xCC9C7400   //( 0xCC9C7400, 0xCC9C86BC)
#define APB_ME1_TOP_BASE             0xCC300800   //( 0xCC300800, 0xCC300CBC)
#define APB_ME1_MES_BASE             0xCC301400   //( 0xCC301404, 0xCC301C0C)
#define APB_ME1_MEP_BASE             0xCC302000   //( 0xCC302000, 0xCC302B50)
#define APB_ME1_MCU_BASE             0xCC303000   //( 0xCC303000, 0xCC304020)
#define APB_ME0_SPP_BASE             0xCC9C1000   //( 0xCC9C1000, 0xCC9C13E8)
#define APB_FME_SSD_BASE             0xCC9C1800   //( 0xCC9C1800, 0xCC9C2240)
#define APB_FMS_BASE                 0xCC341000   //( 0xCC341000, 0xCC341FDC)
#define APB_FPP_F0_BASE              0xCC8C1600   //( 0xCC8C1600, 0xCC8C1878)
#define APB_BDD_F0_BASE              0xCC8C2000   //( 0xCC8C2000, 0xCC8C24A0)
#define APB_GSC_Y_BASE               0xCC500500   //( 0xCC500500, 0xCC500738)
#define APB_GSC_C_BASE               0xCC500800   //( 0xCC500800, 0xCC500A38)
#define APB_HDR_BUF_DE_BASE          0xCCCC0200   //( 0xCCCC0200, 0xCCCC02DC)
#define APB_HDR_BUF_HDR_BASE         0xCCCC0600   //( 0xCCCC0600, 0xCCCC07DC)
#define APB_HDR10_E_BASE             0xCCCC0800   //( 0xCCCC0800, 0xCCCC0C78)
#define APB_HDR10_O_BASE             0xCCCC1A00   //( 0xCCCC1A00, 0xCCCC1E78)
#define APB_HDR_DOLBY_BASE           0xCCCC1000   //( 0xCCCC1000, 0xCCCC1998)
#define APB_HDR_DOLBY1_BASE          0xCCCC2200   //( 0xCCCC2200, 0xCCCC2B98)
#define APB_IPP_M0_META_BASE         0xCC8C0200   //( 0xCC8C0200, 0xCC8C03FC)
#define APB_IPP_M1_META_BASE         0xCC8C2800   //( 0xCC8C2800, 0xCC8C29FC)
#define APB_GAV_HDR_S_BASE           0xCC8C3700   //( 0xCC8C3700, 0xCC8C3AA4)
#define APB_AMG0_HEAD_BASE           0xCC8C4A00   //( 0xCC8C4A00, 0xCC8C4CFC)
#define APB_AMG1_BODY_BASE           0xCC8C4D00   //( 0xCC8C4D20, 0xCC8C4F38)
#define APB_IPP_M0_BASE              0xCC8C0400   //( 0xCC8C0400, 0xCC8C0544)
#define APB_IPP_M1_BASE              0xCC8C0600   //( 0xCC8C0600, 0xCC8C0744)
#define APB_IPP_S0_BASE              0xCC8C0800   //( 0xCC8C0800, 0xCC8C08DC)
#define APB_IPP_C0_BASE              0xCC8C0A00   //( 0xCC8C0A00, 0xCC8C0A84)
#define APB_IPP_G0_BASE              0xCC8C3B00   //( 0xCC8C3B00, 0xCC8C3BD8)
#define APB_IPP_D0_BASE              0xCC8C4100   //( 0xCC8C4100, 0xCC8C4188)
#define APB_IPP_D1_BASE              0xCC8C4300   //( 0xCC8C4300, 0xCC8C4394)
#define APB_IPP_H0_BASE              0xCC8C0C00   //( 0xCC8C0C00, 0xCC8C0C3C)
#define APB_IPP_H1_BASE              0xCC8C0E00   //( 0xCC8C0E00, 0xCC8C0E3C)
#define APB_BDD_M0_BASE              0xCC8C4500   //( 0xCC8C4500, 0xCC8C46C4)
#define APB_BDD_M1_BASE              0xCC8C4700   //( 0xCC8C4700, 0xCC8C48C4)
#define APB_DOLBY1B_BASE             0xCC8C5000   //( 0xCC8C5000, 0xCC8C5028)
#define APB_L3D_BASE                 0xCC480F00   //( 0xCC480F00, 0xCC480F74)
#define APB_LED_BASE                 0xCC400000   //( 0xCC400000, 0xCC402150)
#define APB_UCR_BASE                 0xCC402E00   //( 0xCC402E00, 0xCC402E5C)
#define APB_LED_GSR_BASE             0xCC402A00   //( 0xCC402A00, 0xCC402AC0)
#define APB_OLED_BASE                0xCC403000   //( 0xCC403000, 0xCC403550)
#define APB_DECONTOUR_BASE           0xCC403800   //( 0xCC403800, 0xCC403848)
#define APB_CHIP_INFO_BASE           0xCC410000   //( 0xCC410000, 0xCC4100C4)
#define APB_CHIP_INFO_DATA_BASE         0xCC410100   //( 0xCC410100, 0xCC41C0FC)
#define APB_MCU_BASE                 0xCC080000   //( 0xCC080000, 0xCC0800F8)
#define APB_MCU_IPC_BASE             0xCC0A0000   //( 0xCC0A0000, 0xCC0A03FC)
#define APB_MCU_EDMA_BASE            0xCC0C0000   //( 0xCC0C0000, 0xCC0C0014)
#define APB_MCU_I2C_BASE             0xCC0E0000   //( 0xCC0E0000, 0xCC0E0024)
#define APB_MCU_GK_AND_IPC_BASE         0xCCE00000   //( 0xCCE00000, 0xCCE00FFC)
#define APB_MGI_R_BASE               0xCC8C4900   //( 0xCC8C4900, 0xCC8C4960)
#define APB_IMX_MIF0_BASE            0xCC8C2A00   //( 0xCC8C2A00, 0xCC8C2CF0)
#define APB_IMX_MIF1_BASE            0xCC8C2D00   //( 0xCC8C2D00, 0xCC8C2F84)
#define APB_IMX_MIF2_BASE            0xCC8C3000   //( 0xCC8C3000, 0xCC8C3254)
#define APB_IMX_MIF3_BASE            0xCC8C3300   //( 0xCC8C3300, 0xCC8C350C)
#define APB_ND0_MIF_BASE             0xCC800E00   //( 0xCC800E00, 0xCC800FE8)
#define APB_ND1_MIF_BASE             0xCCC00E00   //( 0xCCC00E00, 0xCCC00EB8)
#define APB_SRE_MIF_BASE             0xCCC43100   //( 0xCCC43100, 0xCCC431C4)
#define APB_GSC_MIF0_BASE            0xCC500C00   //( 0xCC500C00, 0xCC500C80)
#define APB_GSC_MIF1_BASE            0xCC500E00   //( 0xCC500E00, 0xCC500EC8)
#define APB_CCO_MIF0_BASE            0xCC480C00   //( 0xCC480C00, 0xCC480CFC)
#define APB_CCO_MIF1_BASE            0xCC482800   //( 0xCC482800, 0xCC482900)
#define APB_ME0_MIF_BASE             0xCC9C0200   //( 0xCC9C0200, 0xCC9C0588)
#define APB_SSD_MIF_BASE             0xCC9C0800   //( 0xCC9C0800, 0xCC9C0B28)
#define APB_ME1_MIF_BASE             0xCC300400   //( 0xCC300400, 0xCC300644)
#define APB_FMS_MIF0_BASE            0xCC340A00   //( 0xCC340A00, 0xCC340D50)
#define APB_FMC_MIF0_BASE            0xCC4C1800   //( 0xCC4C1800, 0xCC4C19A0)
#define APB_FMC_MIF1_BASE            0xCC4C1A00   //( 0xCC4C1A00, 0xCC4C1BB0)
#define APB_FMC_MIF2_BASE            0xCC4C1C00   //( 0xCC4C1C00, 0xCC4C1D08)
#define APB_FMC_MIF3_BASE            0xCC4C1E00   //( 0xCC4C1E00, 0xCC4C1F08)
#define APB_DNE_MIF0_BASE            0xCC882100   //( 0xCC882100, 0xCC8822BC)
#define APB_DNE_MIF1_BASE            0xCC882700   //( 0xCC882700, 0xCC8828BC)
#define APB_CVI_MON_BASE             0xCC841000   //( 0xCC841000, 0xCC8410FC)
#define APB_HDR_MON_BASE             0xCCCC0100   //( 0xCCCC0100, 0xCCCC01FC)
#define APB_IMX_MON_BASE             0xCC8C0B00   //( 0xCC8C0B00, 0xCC8C0BFC)
#define APB_VDO_MON_BASE             0xCCC80100   //( 0xCCC80100, 0xCCC801FC)
#define APB_ND0_MON_BASE             0xCC800D00   //( 0xCC800D00, 0xCC800DFC)
#define APB_ND1_MON_BASE             0xCCC00D00   //( 0xCCC00D00, 0xCCC00DFC)
#define APB_SRE_MON_BASE             0xCCC40100   //( 0xCCC40100, 0xCCC401FC)
#define APB_FMC_MON_BASE             0xCC4C1100   //( 0xCC4C1100, 0xCC4C11FC)
#define APB_GSC_MON_BASE             0xCC500B00   //( 0xCC500B00, 0xCC500BFC)
#define APB_VSD_MON_BASE             0xCC464000   //( 0xCC464000, 0xCC4640FC)
#define APB_CCO_MON_BASE             0xCC480B00   //( 0xCC480B00, 0xCC480BFC)
#define APB_LED_MON_BASE             0xCC403E00   //( 0xCC403E00, 0xCC403EFC)
#define APB_ME0_MON_BASE             0xCC9C0100   //( 0xCC9C0100, 0xCC9C01FC)
#define APB_ME1_MON_BASE             0xCC300100   //( 0xCC300100, 0xCC3001FC)
#define APB_FMS_MON_BASE             0xCC340100   //( 0xCC340100, 0xCC3401FC)
#define APB_DNE_MON_BASE             0xCC880100   //( 0xCC880100, 0xCC8801FC)
#define APB_MVI_RA_BASE              0xCC8C1A00   //( 0xCC8C1A00, 0xCC8C1A1C)
#define APB_MVI_RB_BASE              0xCC8C1B00   //( 0xCC8C1B00, 0xCC8C1B1C)
#define APB_MVI_RC_BASE              0xCC8C0F00   //( 0xCC8C0F00, 0xCC8C0F1C)
#define APB_VDO_CORE_BASE            0xCCC80300   //( 0xCCC80300, 0xCCC803FC)
#define APB_VDO_GMAU_BASE            0xCCC80400   //( 0xCCC80400, 0xCCC804FC)
#define APB_VDO_CORE1_BASE           0xCCC80500   //( 0xCCC80500, 0xCCC805FC)
#define APB_VDO_GMAU1_BASE           0xCCC80600   //( 0xCCC80600, 0xCCC806FC)
#define APB_VDO_TOP_BASE             0xCCC80700   //( 0xCCC80700, 0xCCC807FC)
#define APB_VDO_CRC_BASE             0xCCC80800   //( 0xCCC80800, 0xCCC808EC)
#define APB_BODP_RC0_BASE            0xCCC80900   //( 0xCCC80900, 0xCCC8091C)
#define APB_BODP_RC1_BASE            0xCCC80D00   //( 0xCCC80D00, 0xCCC80D1C)
#define APB_VDO_CORE2_BASE           0xCCC81100   //( 0xCCC81100, 0xCCC811EC)
#define APB_VDO_GMAU2_BASE           0xCCC81200   //( 0xCCC81200, 0xCCC812EC)
#define APB_VDO_TOP1_BASE            0xCCC81500   //( 0xCCC81500, 0xCCC815FC)
#define APB_VDO_CRC1_BASE            0xCCC81600   //( 0xCCC81600, 0xCCC816EC)
#define APB_DNR0_MUX_BASE            0xCC800A00   //( 0xCC800A00, 0xCC800A94)
#define APB_DNR1_MUX_BASE            0xCCC00A00   //( 0xCCC00A00, 0xCCC00A94)
#define APB_ND0_BASE                 0xCC800100   //( 0xCC800100, 0xCC8004E4)
#define APB_DNR0_BASE                0xCC800500   //( 0xCC800500, 0xCC800998)
#define APB_ND1_BASE                 0xCCC00100   //( 0xCCC00100, 0xCCC004E4)
#define APB_AFBC0_BASE               0xCC480800   //( 0xCC480800, 0xCC4808FC)
#define APB_AFBC1_BASE               0xCC482700   //( 0xCC482700, 0xCC4827FC)
#define APB_OSD0_SHP_BASE            0xCC481C00   //( 0xCC481C00, 0xCC481EFC)
#define APB_OSD1_SHP_BASE            0xCC482300   //( 0xCC482300, 0xCC4825FC)
#define APB_OSD_STATUS_BASE          0xCC480100   //( 0xCC480100, 0xCC48013C)
#define APB_OSD_COMMON_BASE          0xCC480100   //( 0xCC480140, 0xCC480170)
#define APB_OSD_SOSD_BASE            0xCC480100   //( 0xCC480180, 0xCC4801DC)
#define APB_OSD_BOSD_BASE            0xCC480100   //( 0xCC480200, 0xCC4802E4)
#define APB_OSD_IMAGE0_BASE          0xCC480300   //( 0xCC480300, 0xCC4803EC)
#define APB_OSD_IMAGE0_1_BASE         0xCC480400   //( 0xCC480400, 0xCC4804EC)
#define APB_OSD_IMAGE1_BASE          0xCC480500   //( 0xCC480500, 0xCC4805EC)
#define APB_OSD_CURSOR_BASE          0xCC480600   //( 0xCC480600, 0xCC48069C)
#define APB_OSD_HDRUI_BASE           0xCC480700   //( 0xCC480700, 0xCC4807D8)
#define APB_PWM_BASE                 0xCC460100   //( 0xCC460100, 0xCC4601FC)
#define APB_ROT_BASE                 0xCC4C1200   //( 0xCC4C1200, 0xCC4C1398)
#define APB_SHC_BASE                 0xCCC41400   //( 0xCCC41400, 0xCCC41AFC)
#define APB_SRE_COMM_BASE            0xCCC40300   //( 0xCCC40300, 0xCCC403FC)
#define APB_SR_MERG_BASE             0xCCC42A00   //( 0xCCC42A00, 0xCCC42BFC)
#define APB_NR_MERG_BASE             0xCCC42800   //( 0xCCC42800, 0xCCC4288C)
#define APB_SRE_MUX_BASE             0xCCC40500   //( 0xCCC40500, 0xCCC40594)
#define APB_SCY_2K_BASE              0xCCC40B00   //( 0xCCC40B00, 0xCCC40BA0)
#define APB_SCY_4K_BASE              0xCCC41C00   //( 0xCCC41C00, 0xCCC41CA0)
#define APB_SCC_4K_BASE              0xCCC42500   //( 0xCCC42500, 0xCCC4258C)
#define APB_SHY_2K_BASE              0xCCC40C00   //( 0xCCC40C00, 0xCCC413FC)
#define APB_CVI_CTRL_BASE            0xCC840000   //( 0xCC840000, 0xCC8400FC)
#define APB_IMX_CTRL_BASE            0xCC8C0000   //( 0xCC8C0000, 0xCC8C00FC)
#define APB_IMX_CTRL1_BASE           0xCC8C0100   //( 0xCC8C0100, 0xCC8C01FC)
#define APB_GAV_CTRL_BASE            0xCC8C3600   //( 0xCC8C3600, 0xCC8C36FC)
#define APB_VDO_CTRL_BASE            0xCCC80000   //( 0xCCC80000, 0xCCC800FC)
#define APB_HDR_CTRL_BASE            0xCCCC0000   //( 0xCCCC0000, 0xCCCC00FC)
#define APB_HDR_CTRL1_BASE           0xCCCC2000   //( 0xCCCC2000, 0xCCCC20FC)
#define APB_ND0_CTRL_BASE            0xCC800000   //( 0xCC800000, 0xCC8000FC)
#define APB_ND1_CTRL_BASE            0xCCC00000   //( 0xCCC00000, 0xCCC000FC)
#define APB_SRE_CTRL_BASE            0xCCC40000   //( 0xCCC40000, 0xCCC400FC)
#define APB_GSC_CTRL_BASE            0xCC500000   //( 0xCC500000, 0xCC5000FC)
#define APB_VSD_CTRL_BASE            0xCC460000   //( 0xCC460000, 0xCC4600FC)
#define APB_VSD_CTRL1_BASE           0xCC460B00   //( 0xCC460B1C, 0xCC460BD0)
#define APB_CCO_CTRL_BASE            0xCC480000   //( 0xCC480000, 0xCC4800FC)
#define APB_CCO_CTRL1_BASE           0xCC480E00   //( 0xCC480E14, 0xCC480EBC)
#define APB_LED_CTRL_BASE            0xCC403D00   //( 0xCC403D00, 0xCC403DFC)
#define APB_ME0_CTRL_BASE            0xCC9C0000   //( 0xCC9C0000, 0xCC9C00FC)
#define APB_ME1_CTRL_BASE            0xCC300000   //( 0xCC300000, 0xCC3000FC)
#define APB_FMC_CTRL_BASE            0xCC4C1000   //( 0xCC4C1000, 0xCC4C10FC)
#define APB_FMS_CTRL_BASE            0xCC340000   //( 0xCC340000, 0xCC3400FC)
#define APB_DNE_CTRL_BASE            0xCC880000   //( 0xCC880000, 0xCC8800FC)
#define APB_VCP_DE_BASE              0xCC461000   //( 0xCC461000, 0xCC4612D8)
#define APB_VCP_DISP_BASE            0xCC461000   //( 0xCC461400, 0xCC461954)
#define APB_VCP_BOX_BASE             0xCC461000   //( 0xCC461C00, 0xCC461DF4)
#define APB_VCP2_DE_BASE             0xCC463000   //( 0xCC463000, 0xCC4632D8)
#define APB_VCP2_DISP_BASE           0xCC463000   //( 0xCC463400, 0xCC463954)
#define APB_CVI_VERI_BASE            0xCC841100   //( 0xCC841100, 0xCC84110C)
#define APB_HDR_VERI_BASE            0xCCCC2100   //( 0xCCCC2100, 0xCCCC210C)
#define APB_IMX_VERI_BASE            0xCC8C0D00   //( 0xCC8C0D00, 0xCC8C0DAC)
#define APB_ND0_VERI_BASE            0xCC801100   //( 0xCC801100, 0xCC80110C)
#define APB_ND1_VERI_BASE            0xCCC01100   //( 0xCCC01100, 0xCCC0110C)
#define APB_SRE_VERI_BASE            0xCCC40200   //( 0xCCC40200, 0xCCC4020C)
#define APB_FMC_VERI_BASE            0xCC4C1400   //( 0xCC4C1400, 0xCC4C140C)
#define APB_GSC_VERI_BASE            0xCC500100   //( 0xCC500100, 0xCC50010C)
#define APB_VSD_VERI_BASE            0xCC463F00   //( 0xCC463F00, 0xCC463F0C)
#define APB_CCO_VERI_BASE            0xCC482200   //( 0xCC482200, 0xCC48228C)
#define APB_LED_VERI_BASE            0xCC403F00   //( 0xCC403F00, 0xCC403F0C)
#define APB_ME0_VERI_BASE            0xCC9C8C00   //( 0xCC9C8C00, 0xCC9C8C0C)
#define APB_ME1_VERI_BASE            0xCC300200   //( 0xCC300200, 0xCC30020C)
#define APB_FMS_VERI_BASE            0xCC340200   //( 0xCC340200, 0xCC34020C)
#define APB_DNE_VERI_BASE            0xCC880200   //( 0xCC880200, 0xCC88020C)
#define APB_OBC_M_SC_BASE            0xCC483200   //( 0xCC483200, 0xCC4832FC)
#define APB_OBC_P_SC_BASE            0xCC483300   //( 0xCC483300, 0xCC4833FC)
#define APB_OBC_BODY_BASE            0xCC460500   //( 0xCC460500, 0xCC4605E8)
#define APB_OBC_HEAD_BASE            0xCC460700   //( 0xCC460700, 0xCC460780)
#define APB_CSR_BASE                 0xCC463C00   //( 0xCC463C00, 0xCC463D48)
#define APB_VSD_GSR_BASE             0xCC463E00   //( 0xCC463E90, 0xCC463EC0)
#define APB_OBE_BASE                 0xCC460200   //( 0xCC460200, 0xCC460424)
#define APB_DTM_BASE                 0xCC460C00   //( 0xCC460C00, 0xCC460CFC)
#define APB_VSD_SHP_BASE             0xCC462000   //( 0xCC462000, 0xCC4628FC)
#define APB_VSD_SM_BASE              0xCC464100   //( 0xCC464100, 0xCC464154)

#endif

#define PE_O22_P1_CC_OFST			(0x481000)
#define PE_O22_P1_CC2_OFST			(0x481500)

#define PE_O22_CVI_A_OFST			(0x840200)
#define PE_O22_CVI_B_OFST			(0x840300)
#define PE_O22_CVI_C_OFST			(0x840400)
#define PE_O22_CVI_D_OFST			(0x840500)
#define PE_O22_CVI_E_OFST			(0x840600)

#define PE_O22_AMG_HEAD_OFST		(0x8C4A00)
//#define PE_O22_AMG_HEAD_OFST		(0x8C4CFC)
#define PE_O22_AMG_BODY_OFST		(0x8C4D20)
//#define PE_O22_AMG_BODY_OFST		(0x8C4F38)

#define PE_O22_LED_DCNT_OFST		(0x403800)

#define PE_O22_GSC_Y_OFST			(0x500500)
#define PE_O22_GSC_C_OFST			(0x500800)

#define PE_O22_ND0_OFST				(0x800100)
#define PE_O22_ND1_OFST				(0xC00100)
#define PE_O22_DNR0_OFST			(0x800500)
#define PE_O22_ND0_VERI_OFST		(0x801100)
#define PE_O22_ND1_VERI_OFST		(0xC01100)

#define PE_O22_IMX_OFST				(0x8C00B8)

#define PE_O22_P1_SHP_L_OFST		(0x462000)
#define PE_O22_P1_VSD_OBC_BODY_OFST	(0x460500)
#define PE_O22_P1_VSD_OBC_HEAD_OFST	(0x460700)
#define PE_O22_P1_VSD_OBC_M_SC_OFST (0x483200)
#define PE_O22_P1_VSD_DTM_OFST		(0x460C00)
#define PE_O22_P1_VSD_OBE_OFST		(0x460200)
#define PE_O22_OSD_ORD_OFST		    (0x480480)


#define PE_O22_VCP_DISP_OFST		(0x461400)
#define PE_O22_VSD0_VERI_OFST		(0x463F00)

#define PE_O22_SR_2K_SHP_OFST		(0xC40C00)
#define PE_O22_SR_2K_SHC_OFST		(0xC41400)
#define PE_O22_SR_MERG_OFST		    (0xC42A00)

#define PE_O22_REG_WRITE_BASE		(0x0)

#if 0	//TODO:
#define PE_O22_HDMI_A_OFST			(0x000100)
#define PE_O22_HDMI_B_OFST			(0x000140)
#define PE_O22_HDMI_C_OFST			(0x000180)
#define PE_O22_HDMI_D_OFST			(0x0001C0)

#define PE_O22_IPP_OFST				(0x014400)

#define PE_O22_VSD_OFST				(0x00B0B0)

#define PE_O22_P1_CCO_EO_DIFF		(PE_O22_P1_CCO_O_OFST - PE_O22_P1_CCO_E_OFST)

#define PE_O22_HDMI_A_BASE			(PE_O22_DE_BASE + PE_O22_HDMI_A_OFST)
#define PE_O22_HDMI_B_BASE			(PE_O22_DE_BASE + PE_O22_HDMI_B_OFST)
#define PE_O22_HDMI_C_BASE			(PE_O22_DE_BASE + PE_O22_HDMI_C_OFST)
#define PE_O22_HDMI_D_BASE			(PE_O22_DE_BASE + PE_O22_HDMI_D_OFST)

#define PE_O22_IPP_BASE				(PE_O22_DE_BASE + PE_O22_IPP_OFST)

#define PE_O22_VSD_BASE				(PE_O22_DE_BASE + PE_O22_VSD_OFST)
#endif

#define PE_O22_P1_CC_BASE			(PE_O22_DE_BASE + PE_O22_P1_CC_OFST)
#define PE_O22_P1_CC2_BASE			(PE_O22_DE_BASE + PE_O22_P1_CC2_OFST)

#define PE_O22_CVI_A_BASE			(PE_O22_DE_BASE + PE_O22_CVI_A_OFST)
#define PE_O22_CVI_B_BASE			(PE_O22_DE_BASE + PE_O22_CVI_B_OFST)
#define PE_O22_CVI_C_BASE			(PE_O22_DE_BASE + PE_O22_CVI_C_OFST)
#define PE_O22_CVI_D_BASE			(PE_O22_DE_BASE + PE_O22_CVI_D_OFST)
#define PE_O22_AMG_BODY_BASE		(PE_O22_DE_BASE + PE_O22_AMG_BODY_OFST)
#define PE_O22_AMG_HEAD_BASE		(PE_O22_DE_BASE + PE_O22_AMG_HEAD_OFST)

#define PE_O22_LED_DCNT_BASE		(PE_O22_DE_BASE + PE_O22_LED_DCNT_OFST)

#define PE_O22_GSC_Y_BASE			(PE_O22_DE_BASE + PE_O22_GSC_Y_OFST)
#define PE_O22_GSC_C_BASE			(PE_O22_DE_BASE + PE_O22_GSC_C_OFST)

#define PE_O22_ND0_BASE				(PE_O22_DE_BASE + PE_O22_ND0_OFST)
#define PE_O22_ND1_BASE				(PE_O22_DE_BASE + PE_O22_ND1_OFST)
#define PE_O22_DNR0_BASE			(PE_O22_DE_BASE + PE_O22_DNR0_OFST)
#define PE_O22_ND0_VERI_BASE		(PE_O22_DE_BASE + PE_O22_ND0_VERI_OFST)
#define PE_O22_ND1_VERI_BASE		(PE_O22_DE_BASE + PE_O22_ND1_VERI_OFST)


#define PE_O22_IMX_BASE				(PE_O22_DE_BASE + PE_O22_IMX_OFST)

#define PE_O22_P1_SHP_L_BASE		(PE_O22_DE_BASE + PE_O22_P1_SHP_L_OFST)
#define PE_O22_P1_VSD_OBC_BODY_BASE	(PE_O22_DE_BASE + PE_O22_P1_VSD_OBC_BODY_OFST)
#define PE_O22_P1_VSD_OBC_HEAD_BASE	(PE_O22_DE_BASE + PE_O22_P1_VSD_OBC_HEAD_OFST)
#define PE_O22_P1_VSD_OBC_M_SC_BASE	(PE_O22_DE_BASE + PE_O22_P1_VSD_OBC_M_SC_OFST)
#define PE_O22_P1_VSD_OBE_BASE		(PE_O22_DE_BASE + PE_O22_P1_VSD_OBE_OFST)
#define PE_O22_P1_VSD_DTM_BASE		(PE_O22_DE_BASE + PE_O22_P1_VSD_DTM_OFST)

#define PE_O22_VCP_DISP_BASE		(PE_O22_DE_BASE + PE_O22_VCP_DISP_OFST)
#define PE_O22_VSD0_VERI_BASE		(PE_O22_DE_BASE + PE_O22_VSD0_VERI_OFST)

#define PE_O22_SR_2K_SHP_BASE		(PE_O22_DE_BASE + PE_O22_SR_2K_SHP_OFST)
#define PE_O22_SR_2K_SHC_BASE		(PE_O22_DE_BASE + PE_O22_SR_2K_SHC_OFST)
#define PE_O22_SR_MERG_BASE			(PE_O22_DE_BASE + PE_O22_SR_MERG_OFST)
#define PE_O22_SR_VERI_BASE			(PE_O22_DE_BASE + 0xC40200)
#define PE_O22_MCU_BASE				(PE_O22_DE_BASE + 0x080000)
#define PE_O22_CCO_VERI_BASE		(PE_O22_DE_BASE + 0x482200)
#define PE_O22_OSD_ORD_BASE		    (PE_O22_DE_BASE + PE_O22_OSD_ORD_OFST)

#define PE_O22_H10_0_BASE			(PE_O22_DE_BASE + 0xCC0800)
#define PE_O22_H10_1_BASE			(PE_O22_DE_BASE + 0xCC1A00)
#define PE_O22_HDR_VERI_BASE		(PE_O22_DE_BASE + 0xCC2100)

#ifdef INCLUDE_KDRV_DE
#define PE_O22_DDR_DB0_BASE			(g_pe_db.base)
#define PE_O22_DDR_DB0_SIZE			(g_pe_db.size)
#define PE_O22_DDR_DB1_BASE			(g_pe_hdr.base)
#define PE_O22_DDR_DB1_SIZE			(g_pe_hdr.size)

/* PE_O22F22_DDR_BASE : base + 512k */
#define PE_O22F22_DDR_BASE			(PE_O22_DDR_DB0_BASE + 0x00080000)
/* PE_O22F22_DCM_DDR_BASE : base + 1M */
#define PE_O22F22_DCM_DDR_BASE		(PE_O22_DDR_DB0_BASE + 0x00100000)
/* PE_O22F22_DBC_DDR_BASE : base + 1M + 200k */
#define PE_O22F22_DBC_DDR_BASE		(PE_O22_DDR_DB0_BASE + 0x00132000)
#endif

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

#endif	/* _PE_REG_DEF_O22_H_ */

