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

/** @file pe_reg_def_o26.h
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

#ifndef _PE_REG_DEF_O26_H_
#define _PE_REG_DEF_O26_H_

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
#if 0	//Ref. (see include/register/o26_ref/abp_base.h) (o26_base)
#define APB_LCEVC_BASE               0xCC250E00   //( 0xCC250E00, 0xCC250F18)
#define APB_CC_BASE                  0xCC881000   //( 0xCC881000, 0xCC8815D8)
#define APB_CC2_BASE                 0xCC881600   //( 0xCC881600, 0xCC881BC8)
#define APB_CCO_DEC_BASE             0xCC882000   //( 0xCC882000, 0xCC882238)
#define APB_L3D_BASE                 0xCC880F00   //( 0xCC880F00, 0xCC880F74)
#define APB_OBC_M_SC_BASE            0xCC883300   //( 0xCC883300, 0xCC8833FC)
#define APB_OBC_P_SC_BASE            0xCC883400   //( 0xCC883400, 0xCC8834FC)
#define APB_OSD_SHP_BASE             0xCC881D00   //( 0xCC881D00, 0xCC881FFC)
#define APB_CVD_BASE                 0xCC4E1700   //( 0xCC4E1700, 0xCC4E1F90)
#define APB_CVI_A_BASE               0xCC4E0200   //( 0xCC4E0200, 0xCC4E034C)
#define APB_CVI_B_BASE               0xCC4E0400   //( 0xCC4E0400, 0xCC4E054C)
#define APB_CVI_C_BASE               0xCC4E0600   //( 0xCC4E0600, 0xCC4E074C)
#define APB_CVI_D_BASE               0xCC4E0800   //( 0xCC4E0800, 0xCC4E094C)
#define APB_DBGOSD_BASE              0xCC880900   //( 0xCC880900, 0xCC880918)
#define APB_DCF_BASE                 0xCC880A00   //( 0xCC880A00, 0xCC880A5C)
#define APB_DNSR0_BASE               0xCC480000   //( 0xCC480000, 0xCC480FFC)
#define APB_DNSR1_BASE               0xCC4A0000   //( 0xCC4A0000, 0xCC4A0FFC)
#define APB_MC_BASE                  0xCCC40000   //( 0xCCC40000, 0xCCC400EC)
#define APB_MCP_BASE                 0xCCC40800   //( 0xCCC40800, 0xCCC40D44)
#define APB_ME0_TOP_BASE             0xCCCA2400   //( 0xCCCA2400, 0xCCCA2FE4)
#define APB_ME0_MES_BASE             0xCCCA3C00   //( 0xCCCA3C04, 0xCCCA520C)
#define APB_ME0_MEP_BASE             0xCCCA5400   //( 0xCCCA5400, 0xCCCA6758)
#define APB_ME0_MCU_BASE             0xCCCA6C00   //( 0xCCCA6C00, 0xCCCA73D4)
#define APB_ME0_MCU_SEC_BASE         0xCCCA7400   //( 0xCCCA7400, 0xCCCA86BC)
#define APB_ME1_TOP_BASE             0xCCCD0800   //( 0xCCCD0800, 0xCCCD0CBC)
#define APB_ME1_MES_BASE             0xCCCD1400   //( 0xCCCD1404, 0xCCCD1C0C)
#define APB_ME1_MEP_BASE             0xCCCD2000   //( 0xCCCD2000, 0xCCCD2B50)
#define APB_ME1_MCU_BASE             0xCCCD3000   //( 0xCCCD3000, 0xCCCD4020)
#define APB_ME0_SPP_BASE             0xCCCA1000   //( 0xCCCA1000, 0xCCCA13E8)
#define APB_FME_SSD_BASE             0xCCCA1800   //( 0xCCCA1800, 0xCCCA2240)
#define APB_FMS_BASE                 0xCC301000   //( 0xCC301000, 0xCC301FDC)
#define APB_FPP_F0_BASE              0xCCC11600   //( 0xCCC11600, 0xCCC11878)
#define APB_BDD_F0_BASE              0xCCC12000   //( 0xCCC12000, 0xCCC124D8)
#define APB_GSC_CORE_BASE            0xCCC70200   //( 0xCCC70200, 0xCCC70244)
#define APB_GPD_BASE                 0xCCC70400   //( 0xCCC70400, 0xCCC70420)
#define APB_OSC0_Y_BASE              0xCCC70600   //( 0xCCC70600, 0xCCC70760)
#define APB_OSC0_C_BASE              0xCCC70800   //( 0xCCC70800, 0xCCC70958)
#define APB_OSC1_Y_BASE              0xCCC70A00   //( 0xCCC70A00, 0xCCC70B58)
#define APB_OSC1_C_BASE              0xCCC70C00   //( 0xCCC70C00, 0xCCC70D58)
#define APB_OSC2_Y_BASE              0xCCC70E00   //( 0xCCC70E00, 0xCCC7119C)
#define APB_OSC2_C_BASE              0xCCC71200   //( 0xCCC71200, 0xCCC714F0)
#define APB_OSC3_Y_BASE              0xCCC71600   //( 0xCCC71600, 0xCCC7199C)
#define APB_OSC3_C_BASE              0xCCC71A00   //( 0xCCC71A00, 0xCCC71CF0)
#define APB_OSD_PRE_BASE             0xCCC71E00   //( 0xCCC71E00, 0xCCC71FC0)
#define APB_SMTH_BASE                0xCCC72000   //( 0xCCC72000, 0xCCC72030)
#define APB_VLB_BASE                 0xCCC72200   //( 0xCCC72200, 0xCCC722A8)
#define APB_GLB_BASE                 0xCCC72400   //( 0xCCC72400, 0xCCC724A8)
#define APB_HDR_BUF_DE_BASE          0xCC230200   //( 0xCC230200, 0xCC23048C)
#define APB_HDR_BUF_HDR_BASE         0xCC230600   //( 0xCC230600, 0xCC2307DC)
#define APB_HDR10_E_BASE             0xCC230800   //( 0xCC230800, 0xCC230DFC)
#define APB_HDR10_O_BASE             0xCC231A00   //( 0xCC231A00, 0xCC231F94)
#define APB_HDR_DOLBY_BASE           0xCC231000   //( 0xCC231000, 0xCC231998)
#define APB_HDR_DOLBY1_BASE          0xCC232200   //( 0xCC232200, 0xCC232B98)
#define APB_IPP_M0_META_BASE         0xCCC10200   //( 0xCCC10200, 0xCCC103FC)
#define APB_IPP_M1_META_BASE         0xCCC12700   //( 0xCCC12700, 0xCCC128FC)
#define APB_GAV_HDR_S_BASE           0xCCC13800   //( 0xCCC13800, 0xCCC13CEC)
#define APB_AMG0_HEAD_BASE           0xCCC14A00   //( 0xCCC14A00, 0xCCC14CFC)
#define APB_AMG1_BODY_BASE           0xCCC14D00   //( 0xCCC14D20, 0xCCC14F38)
#define APB_AMG2_MTB_BASE            0xCCC15900   //( 0xCCC15900, 0xCCC15AF4)
#define APB_AMG3_GRM_BASE            0xCCC16100   //( 0xCCC16100, 0xCCC163FC)
#define APB_GAV_SHP_BASE             0xCCC15100   //( 0xCCC15100, 0xCCC158FC)
#define APB_IPP_M0_BASE              0xCCC10400   //( 0xCCC10400, 0xCCC105BC)
#define APB_IPP_M1_BASE              0xCCC10600   //( 0xCCC10600, 0xCCC107BC)
#define APB_IPP_S0_BASE              0xCCC10800   //( 0xCCC10800, 0xCCC10934)
#define APB_IPP_C0_BASE              0xCCC10A00   //( 0xCCC10A00, 0xCCC10B34)
#define APB_IPP_D0_BASE              0xCCC14100   //( 0xCCC14100, 0xCCC14234)
#define APB_IPP_D1_BASE              0xCCC14300   //( 0xCCC14300, 0xCCC14434)
#define APB_IPP_G0_BASE              0xCCC13D00   //( 0xCCC13D00, 0xCCC13E48)
#define APB_IPP_H0_BASE              0xCCC10D00   //( 0xCCC10D00, 0xCCC10D3C)
#define APB_IPP_H1_BASE              0xCCC10F00   //( 0xCCC10F00, 0xCCC10F3C)
#define APB_BDD_M0_BASE              0xCCC14500   //( 0xCCC14500, 0xCCC146C4)
#define APB_BDD_M1_BASE              0xCCC14700   //( 0xCCC14700, 0xCCC148C4)
#define APB_DOLBY1B_BASE             0xCCC15000   //( 0xCCC15000, 0xCCC15028)
#define APB_IPP_G0_SCY_BASE          0xCCC13F00   //( 0xCCC13F00, 0xCCC13FF4)
#define APB_IPP_G0_SCC_BASE          0xCCC14000   //( 0xCCC14000, 0xCCC140EC)
#define APB_UCR_BASE                 0xCC902E00   //( 0xCC902E00, 0xCC902E6C)
#define APB_GSR_BASE                 0xCC902A00   //( 0xCC902A00, 0xCC902AC0)
#define APB_LED_BASE                 0xCC900000   //( 0xCC900000, 0xCC9022E8)
#define APB_OLED_BASE                0xCC903000   //( 0xCC903000, 0xCC90375C)
#define APB_CHIP_INFO_BASE           0xCC910000   //( 0xCC910000, 0xCC9100DC)
#define APB_CHIP_INFO_DATA_BASE      0xCC910100   //( 0xCC910100, 0xCC91C0FC)
#define APB_BV_DSC_BASE              0xCC904000   //( 0xCC904000, 0xCC904048)
#define APB_BV_USC_BASE              0xCC904200   //( 0xCC904200, 0xCC9042CC)
#define APB_MCU_BASE                 0xCC080000   //( 0xCC080000, 0xCC0800F8)
#define APB_MCU_GK_AXI_BASE          0xCC081000   //( 0xCC081000, 0xCC08140C)
#define APB_MCU_IPC_BASE             0xCC0A0000   //( 0xCC0A0000, 0xCC0A03FC)
#define APB_MCU_EDMA_BASE            0xCC0C0000   //( 0xCC0C0000, 0xCC0C0014)
#define APB_MCU_I2C_BASE             0xCC0E0000   //( 0xCC0E0000, 0xCC0E0024)
#define APB_MCU_GK_AND_IPC_BASE      0xCCE00000   //( 0xCCE00000, 0xCCE00FFC)
#define APB_MGI_RD_BASE              0xCCC11D00   //( 0xCCC11D00, 0xCCC11D68)
#define APB_MGI_RE_BASE              0xCCC11E00   //( 0xCCC11E00, 0xCCC11E90)
#define APB_IMX_GPD_BASE             0xCCC11F00   //( 0xCCC11F00, 0xCCC11F1C)
#define APB_IMX_MIF0_BASE            0xCCC12900   //( 0xCCC12900, 0xCCC12BD4)
#define APB_IMX_MIF1_BASE            0xCCC12D00   //( 0xCCC12D00, 0xCCC12FF4)
#define APB_IMX_MIF2_BASE            0xCCC13100   //( 0xCCC13100, 0xCCC13354)
#define APB_IMX_MIF3_BASE            0xCCC13400   //( 0xCCC13400, 0xCCC1365C)
#define APB_ND0_MIF_BASE             0xCC290E00   //( 0xCC290E00, 0xCC291078)
#define APB_ND1_MIF_BASE             0xCC2C1000   //( 0xCC2C1000, 0xCC2C1228)
#define APB_ND2_MIF_BASE             0xCC2C1300   //( 0xCC2C1300, 0xCC2C13C4)
#define APB_SRE_MIF_BASE             0xCCA03900   //( 0xCCA03900, 0xCCA03AE8)
#define APB_SRE1_MIF_BASE            0xCCA03B00   //( 0xCCA03B00, 0xCCA03BF0)
#define APB_GSC_MIF0_BASE            0xCCC73700   //( 0xCCC73700, 0xCCC737C8)
#define APB_GSC_MIF1_BASE            0xCCC73900   //( 0xCCC73900, 0xCCC739EC)
#define APB_CCO_MIF0_BASE            0xCC880C00   //( 0xCC880C00, 0xCC880D4C)
#define APB_ME0_MIF_BASE             0xCCCA0200   //( 0xCCCA0200, 0xCCCA0588)
#define APB_SSD_MIF_BASE             0xCCCA0800   //( 0xCCCA0800, 0xCCCA0B28)
#define APB_ME1_MIF_BASE             0xCCCD0400   //( 0xCCCD0400, 0xCCCD0644)
#define APB_FMS_MIF0_BASE            0xCC300A00   //( 0xCC300A00, 0xCC300CC4)
#define APB_FMC_MIF0_BASE            0xCCC41800   //( 0xCCC41800, 0xCCC41990)
#define APB_FMC_MIF1_BASE            0xCCC41A00   //( 0xCCC41A00, 0xCCC41BA0)
#define APB_FMC_MIF2_BASE            0xCCC41C00   //( 0xCCC41C00, 0xCCC41D08)
#define APB_FMC_MIF3_BASE            0xCCC41E00   //( 0xCCC41E00, 0xCCC41F08)
#define APB_CVI_MON_BASE             0xCC4E2000   //( 0xCC4E2000, 0xCC4E20FC)
#define APB_HDR_MON_BASE             0xCC230100   //( 0xCC230100, 0xCC2301FC)
#define APB_IMX_MON_BASE             0xCCC10C00   //( 0xCCC10C00, 0xCCC10CFC)
#define APB_VDO_MON_BASE             0xCC250100   //( 0xCC250100, 0xCC2501FC)
#define APB_ND0_MON_BASE             0xCC290D00   //( 0xCC290D00, 0xCC290DFC)
#define APB_ND1_MON_BASE             0xCC2C0F00   //( 0xCC2C0F00, 0xCC2C0FFC)
#define APB_SRE_MON_BASE             0xCCA00100   //( 0xCCA00100, 0xCCA001FC)
#define APB_FMC_MON_BASE             0xCCC41100   //( 0xCCC41100, 0xCCC411FC)
#define APB_GSC_MON_BASE             0xCCC73600   //( 0xCCC73600, 0xCCC736FC)
#define APB_VSD_MON_BASE             0xCC954000   //( 0xCC954000, 0xCC9540FC)
#define APB_CCO_MON_BASE             0xCC880B00   //( 0xCC880B00, 0xCC880BFC)
#define APB_LED_MON_BASE             0xCC903E00   //( 0xCC903E00, 0xCC903EFC)
#define APB_ME0_MON_BASE             0xCCCA0100   //( 0xCCCA0100, 0xCCCA01FC)
#define APB_ME1_MON_BASE             0xCCCD0100   //( 0xCCCD0100, 0xCCCD01FC)
#define APB_FMS_MON_BASE             0xCC300100   //( 0xCC300100, 0xCC3001FC)
#define APB_MVI_RA_BASE              0xCCC11A00   //( 0xCCC11A00, 0xCCC11A24)
#define APB_MVI_RB_BASE              0xCCC11B00   //( 0xCCC11B00, 0xCCC11B24)
#define APB_MVI_RC_BASE              0xCCC11C00   //( 0xCCC11C00, 0xCCC11C24)
#define APB_VDO_BODP_RC0_BASE        0xCC250A00   //( 0xCC250A00, 0xCC250A5C)
#define APB_VDO_CORE_BASE            0xCC250300   //( 0xCC250300, 0xCC2503FC)
#define APB_VDO_GMAU_BASE            0xCC250400   //( 0xCC250400, 0xCC2504FC)
#define APB_VDO_CORE1_BASE           0xCC250500   //( 0xCC250500, 0xCC2505EC)
#define APB_VDO_GMAU1_BASE           0xCC250600   //( 0xCC250600, 0xCC2506EC)
#define APB_VDO_TOP_BASE             0xCC250700   //( 0xCC250700, 0xCC2508EC)
#define APB_VDO_CRC_BASE             0xCC250900   //( 0xCC250900, 0xCC2509EC)
#define APB_DNR0_MUX_BASE            0xCC290C00   //( 0xCC290C00, 0xCC290C94)
#define APB_DNR1_MUX_BASE            0xCC2C0A00   //( 0xCC2C0A00, 0xCC2C0A94)
#define APB_ND0_BASE                 0xCC290100   //( 0xCC290100, 0xCC2904F0)
#define APB_DNR0_BASE                0xCC290500   //( 0xCC290500, 0xCC290B5C)
#define APB_ND1_BASE                 0xCC2C0100   //( 0xCC2C0100, 0xCC2C04F0)
#define APB_DNR1_BASE                0xCC2C0500   //( 0xCC2C0500, 0xCC2C0948)
#define APB_ND2_BASE                 0xCC2C0B00   //( 0xCC2C0B00, 0xCC2C0EF0)
#define APB_AFBC0_BASE               0xCCC72600   //( 0xCCC72600, 0xCCC726FC)
#define APB_AFBC1_BASE               0xCCC72800   //( 0xCCC72800, 0xCCC728FC)
#define APB_AFBC2_BASE               0xCCC72A00   //( 0xCCC72A00, 0xCCC72AFC)
#define APB_AFBC3_BASE               0xCCC72C00   //( 0xCCC72C00, 0xCCC72CFC)
#define APB_AFRC0_BASE               0xCCC72E00   //( 0xCCC72E00, 0xCCC72ECC)
#define APB_AFRC1_BASE               0xCCC73000   //( 0xCCC73000, 0xCCC730CC)
#define APB_AFRC2_BASE               0xCCC73200   //( 0xCCC73200, 0xCCC732CC)
#define APB_AFRC3_BASE               0xCCC73400   //( 0xCCC73400, 0xCCC734CC)
#define APB_OSD_STATUS_BASE          0xCC880100   //( 0xCC880100, 0xCC88013C)
#define APB_OSD_COMMON_BASE          0xCC880140   //( 0xCC880140, 0xCC880170)
#define APB_OSD_BOSD_BASE            0xCC880200   //( 0xCC880200, 0xCC8802E4)
#define APB_OSD_IMAGE0_BASE          0xCC880300   //( 0xCC880300, 0xCC8803FC)
#define APB_OSD_IMAGE0_1_BASE        0xCC880400   //( 0xCC880400, 0xCC8804EC)
#define APB_OSD_CURSOR_BASE          0xCC880600   //( 0xCC880600, 0xCC8806FC)
#define APB_OSD_HDRUI_BASE           0xCC880700   //( 0xCC880700, 0xCC8807D8)
#define APB_PWM_BASE                 0xCC950100   //( 0xCC950100, 0xCC9501FC)
#define APB_ROT_BASE                 0xCCC41200   //( 0xCCC41200, 0xCCC41398)
#define APB_SRE_COMM_BASE            0xCCA00300   //( 0xCCA00304, 0xCCA005A4)
#define APB_SR_MERG_BASE             0xCCA02A00   //( 0xCCA02A00, 0xCCA02BFC)
#define APB_SR_BLEND_BASE            0xCCA02800   //( 0xCCA02800, 0xCCA02934)
#define APB_SCY_SW_BASE              0xCCA00B00   //( 0xCCA00B00, 0xCCA00BA0)
#define APB_SCY_4K_BASE              0xCCA01C00   //( 0xCCA01C00, 0xCCA01CA0)
#define APB_SCC_4K_BASE              0xCCA02500   //( 0xCCA02500, 0xCCA0258C)
#define APB_SCY1_SW_BASE             0xCCA02C00   //( 0xCCA02C00, 0xCCA02CA0)
#define APB_SCC1_4K_BASE             0xCCA03500   //( 0xCCA03500, 0xCCA0358C)
#define APB_SRE_MUX_BASE             0xCCA00600   //( 0xCCA00600, 0xCCA00694)
#define APB_SHP_2KC_BASE             0xCCA01400   //( 0xCCA01400, 0xCCA01AFC)
#define APB_SHP_2KY_BASE             0xCCA00C00   //( 0xCCA00C00, 0xCCA013FC)
#define APB_SHP_SUB_BASE             0xCCA02D00   //( 0xCCA02D00, 0xCCA034FC)
#define APB_SLB_BASE                 0xCCA03600   //( 0xCCA03600, 0xCCA036F8)
#define APB_CVI_CTRL_BASE            0xCC4E0000   //( 0xCC4E0000, 0xCC4E00FC)
#define APB_VDO_CTRL_BASE            0xCC250000   //( 0xCC250000, 0xCC2500FC)
#define APB_IMX_CTRL_BASE            0xCCC10000   //( 0xCCC10000, 0xCCC100FC)
#define APB_IMX_CTRL1_BASE           0xCCC10100   //( 0xCCC10100, 0xCCC101FC)
#define APB_GAV_CTRL_BASE            0xCCC13700   //( 0xCCC13700, 0xCCC137FC)
#define APB_HDR_CTRL_BASE            0xCC230000   //( 0xCC230000, 0xCC2300FC)
#define APB_HDR_CTRL1_BASE           0xCC232000   //( 0xCC232000, 0xCC2320FC)
#define APB_ND0_CTRL_BASE            0xCC290000   //( 0xCC290000, 0xCC2900FC)
#define APB_ND1_CTRL_BASE            0xCC2C0000   //( 0xCC2C0000, 0xCC2C00FC)
#define APB_SRE_CTRL_BASE            0xCCA00000   //( 0xCCA00000, 0xCCA000FC)
#define APB_OBS_CTRL_BASE            0xCCA03700   //( 0xCCA03700, 0xCCA037FC)
#define APB_GSC_CTRL_BASE            0xCCC70000   //( 0xCCC70000, 0xCCC700FC)
#define APB_VSD_CTRL_BASE            0xCC950000   //( 0xCC950000, 0xCC9500FC)
#define APB_VSD_CTRL1_BASE           0xCC950B00   //( 0xCC950B18, 0xCC950BFC)
#define APB_CCO_CTRL_BASE            0xCC880000   //( 0xCC880000, 0xCC8800FC)
#define APB_CCO_CTRL1_BASE           0xCC880E00   //( 0xCC880E00, 0xCC880EFC)
#define APB_LED_CTRL_BASE            0xCC903D00   //( 0xCC903D00, 0xCC903DFC)
#define APB_ME0_CTRL_BASE            0xCCCA0000   //( 0xCCCA0000, 0xCCCA00FC)
#define APB_ME1_CTRL_BASE            0xCCCD0000   //( 0xCCCD0000, 0xCCCD00FC)
#define APB_FMC_CTRL_BASE            0xCCC41000   //( 0xCCC41000, 0xCCC410FC)
#define APB_FMS_CTRL_BASE            0xCC300000   //( 0xCC300000, 0xCC3000FC)
#define APB_VCP_DE_BASE              0xCC951000   //( 0xCC951000, 0xCC9512D8)
#define APB_VCP_DISP_BASE            0xCC951000   //( 0xCC951400, 0xCC95199C)
#define APB_VCP_BOX_BASE             0xCC951000   //( 0xCC951C00, 0xCC951DF4)
#define APB_CVI_VERI_BASE            0xCC4E2100   //( 0xCC4E2100, 0xCC4E211C)
#define APB_HDR_VERI_BASE            0xCC232100   //( 0xCC232100, 0xCC232110)
#define APB_IMX_VERI_BASE            0xCCC10E00   //( 0xCCC10E00, 0xCCC10EDC)
#define APB_ND0_VERI_BASE            0xCC291100   //( 0xCC291100, 0xCC29111C)
#define APB_ND1_VERI_BASE            0xCC2C1600   //( 0xCC2C1600, 0xCC2C160C)
#define APB_SRE_VERI_BASE            0xCCA00200   //( 0xCCA00200, 0xCCA0020C)
#define APB_FMC_VERI_BASE            0xCCC41400   //( 0xCCC41400, 0xCCC4140C)
#define APB_GSC_VERI_BASE            0xCCC70100   //( 0xCCC70100, 0xCCC7011C)
#define APB_VSD_VERI_BASE            0xCC953F00   //( 0xCC953F00, 0xCC953F1C)
#define APB_CCO_VERI_BASE            0xCC882300   //( 0xCC882300, 0xCC88238C)
#define APB_LED_VERI_BASE            0xCC903F00   //( 0xCC903F00, 0xCC903F0C)
#define APB_ME0_VERI_BASE            0xCCCA8C00   //( 0xCCCA8C00, 0xCCCA8C0C)
#define APB_ME1_VERI_BASE            0xCCCD0200   //( 0xCCCD0200, 0xCCCD020C)
#define APB_FMS_VERI_BASE            0xCC300200   //( 0xCC300200, 0xCC30020C)
#define APB_DTM_TOP_BASE             0xCC950C00   //( 0xCC950C00, 0xCC950CF0)
#define APB_LOC_BASE                 0xCC950D00   //( 0xCC950D00, 0xCC950DB8)
#define APB_DTM_BASE                 0xCC950E00   //( 0xCC950E00, 0xCC950F40)
#define APB_OBC_BODY_BASE            0xCC950500   //( 0xCC950500, 0xCC9505F0)
#define APB_OBC_HEAD_BASE            0xCC950700   //( 0xCC950700, 0xCC9507E8)
#define APB_BG_BASE                  0xCC950900   //( 0xCC950900, 0xCC9509F0)
#define APB_CSR_BASE                 0xCC953C00   //( 0xCC953C00, 0xCC953D48)
#define APB_VSD_GSR_BASE             0xCC953E00   //( 0xCC953E90, 0xCC953EC0)
#define APB_OBE_BASE                 0xCC950200   //( 0xCC950200, 0xCC950444)
#define APB_VSD_SHP_BASE             0xCC952000   //( 0xCC952000, 0xCC9528FC)
#endif

#define PE_O26_CC_BASE               0xCC881000   //( 0xCC881000, 0xCC8815D8)
#define PE_O26_CC2_BASE              0xCC881600   //( 0xCC881600, 0xCC881BC8)
#define PE_O26_CCO_DEC_BASE          0xCC882000   //( 0xCC882000, 0xCC882238)
#define PE_O26_CCO_VERI_BASE         0xCC882300   //( 0xCC882300, 0xCC88238C)
#define PE_O26_OSD_ORD_BASE          0xCC880480
#define PE_O26_CVI_A_BASE            0xCC4E0200   //( 0xCC4E0200, 0xCC4E034C)
#define PE_O26_CVI_B_BASE            0xCC4E0400   //( 0xCC4E0400, 0xCC4E054C)
#define PE_O26_CVI_C_BASE            0xCC4E0600   //( 0xCC4E0600, 0xCC4E074C)
#define PE_O26_CVI_D_BASE            0xCC4E0800   //( 0xCC4E0800, 0xCC4E094C)
#define PE_O26_OSC0_Y_BASE           0xCCC70600   //( 0xCCC70600, 0xCCC70760)
#define PE_O26_OSC0_C_BASE           0xCCC70800   //( 0xCCC70800, 0xCCC70958)
#define PE_O26_OSC1_Y_BASE           0xCCC70A00   //( 0xCCC70A00, 0xCCC70B58)
#define PE_O26_OSC1_C_BASE           0xCCC70C00   //( 0xCCC70C00, 0xCCC70D58)
#define PE_O26_OSC2_Y_BASE           0xCCC70E00   //( 0xCCC70E00, 0xCCC7119C)
#define PE_O26_OSC2_C_BASE           0xCCC71200   //( 0xCCC71200, 0xCCC714F0)
#define PE_O26_OSC3_Y_BASE           0xCCC71600   //( 0xCCC71600, 0xCCC7199C)
#define PE_O26_OSC3_C_BASE           0xCCC71A00   //( 0xCCC71A00, 0xCCC71CF0)
#define PE_O26_ND0_BASE              0xCC290100   //( 0xCC290100, 0xCC2904F0)
#define PE_O26_ND1_BASE              0xCC2C0100   //( 0xCC2C0100, 0xCC2C04F0)
#define PE_O26_ND2_BASE              0xCC2C0B00   //( 0xCC2C0B00, 0xCC2C0EF0)
#define PE_O26_DNR0_BASE             0xCC290500   //( 0xCC290500, 0xCC290B5C)
#define PE_O26_DNR1_BASE             0xCC2C0500   //( 0xCC2C0500, 0xCC2C0948)
#define PE_O26_ND0_VERI_BASE         0xCC291100   //( 0xCC291100, 0xCC29111C)
#define PE_O26_ND1_VERI_BASE         0xCC2C1600   //( 0xCC2C1600, 0xCC2C160C)
#define PE_O26_IMX_BASE              0xCCC100B8
#define PE_O26_SR_2K_SHP0_BASE       0xCCA00C00   //( 0xCCA00C00, 0xCCA013FC)
#define PE_O26_SR_2K_SHP1_BASE       0xCCA02D00   //( 0xCCA02D00, 0xCCA034FC)
#define PE_O26_SR_2K_SHC_BASE        0xCCA01400   //( 0xCCA01400, 0xCCA01AFC)
#define PE_O26_SR_MERG_BASE          0xCCA02A00   //( 0xCCA02A00, 0xCCA02BFC)
#define PE_O26_SR_BLEND_BASE         0xCCA02800   //( 0xCCA02800, 0xCCA02934)
#define PE_O26_GAV_SHP_BASE          0xCCC15100   //( 0xCCC15100, 0xCCC158FC)
#define PE_O26_SRE_VERI_BASE         0xCCA00200   //( 0xCCA00200, 0xCCA0020C)
#define PE_O26_VCP_DISP_BASE         0xCC951400   //( 0xCC951400, 0xCC95199C)
#define PE_O26_VLB_BASE              0xCCC72200   //( 0xCCC72200, 0xCCC722A8)
#define PE_O26_VSD_VERI_BASE         0xCC953F00   //( 0xCC953F00, 0xCC953F1C)
#define PE_O26_FMC_VERI_BASE         0xCCC41400   //( 0xCCC41400, 0xCCC4140C)
#define PE_O26_AMG0_HEAD_BASE        0xCCC14A00   //( 0xCCC14A00, 0xCCC14CFC)
#define PE_O26_AMG1_BODY_BASE        0xCCC14D20   //( 0xCCC14D20, 0xCCC14F38)
#define PE_O26_AMG2_MTB_BASE         0xCCC15900   //( 0xCCC15900, 0xCCC15AF4)
#define PE_O26_AMG3_GRM_BASE         0xCCC16100   //( 0xCCC16100, 0xCCC163FC)
#define PE_O26_VSD_SHP_BASE          0xCC952000   //( 0xCC952000, 0xCC9528FC)
#define PE_O26_DTM_BASE              0xCC950E00   //( 0xCC950E00, 0xCC950F40)
#define PE_O26_LOC_BASE              0xCC950D00   //( 0xCC950D00, 0xCC950DB8)
#define PE_O26_OBC_BODY_BASE         0xCC950500   //( 0xCC950500, 0xCC9505F0)
#define PE_O26_OBC_HEAD_BASE         0xCC950700   //( 0xCC950700, 0xCC9507E8)
#define PE_O26_OBE_BASE              0xCC950200   //( 0xCC950200, 0xCC950444)
#define PE_O26_REG_WRITE_BASE		(0x0)

#if 0   //TODO:
#define PE_O26_MCU_BASE              0xCC080000   //( 0xCC080000, 0xCC0800F8)
#endif

#ifdef INCLUDE_KDRV_DE
#define PE_O26_DDR_DB0_BASE			(g_pe_db.base)
#define PE_O26_DDR_DB0_SIZE			(g_pe_db.size)

#define PE_O26_DDR_DB_BASE			(g_pe_db.base)
#define PE_O26_DDR_DB_SIZE			(g_pe_db.size+g_pe_hdr.size)

/* PE_O26F22_DDR_BASE : base + 512k + 128k*/
#define PE_O26F22_DDR_BASE			(PE_O26_DDR_DB0_BASE + 0x000A0000)
/* PE_O26F22_DCM_DDR_BASE : base + 1M + 128k */
#define PE_O26F22_DCM_DDR_BASE		(PE_O26_DDR_DB0_BASE + 0x00120000)
/* PE_O26F22_DBC_DDR_BASE : base + 1M + 200k  + 128k*/
#define PE_O26F22_DBC_DDR_BASE		(PE_O26_DDR_DB0_BASE + 0x00152000)
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

#endif	/* _PE_REG_DEF_O26_H_ */

