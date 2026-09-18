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

/** @file pe_reg_def_o24.h
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

#ifndef _PE_REG_DEF_O24_H_
#define _PE_REG_DEF_O24_H_

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
/* O24_DE_BASE */
#define PE_O24_DE_BASE				(0xCC000000)

#if 0	//Ref. (see REGISTER/abp_base.h) (O24A0_PQE_FW)
#define APB_DECON_BASE               0xCC862100   //( 0xCC862100, 0xCC8622FC)
#define APB_CC_BASE                  0xCC861000   //( 0xCC861000, 0xCC8615D8)
#define APB_CC2_BASE                 0xCC861600   //( 0xCC861600, 0xCC861BC8)
#define APB_CVD_BASE                 0xCCCC0700   //( 0xCCCC0700, 0xCCCC0F90)
#define APB_CVI_A_BASE               0xCCCC0200   //( 0xCCCC0200, 0xCCCC02FC)
#define APB_CVI_B_BASE               0xCCCC0300   //( 0xCCCC0300, 0xCCCC03FC)
#define APB_CVI_C_BASE               0xCCCC0400   //( 0xCCCC0400, 0xCCCC04FC)
#define APB_CVI_D_BASE               0xCCCC0500   //( 0xCCCC0500, 0xCCCC05FC)
#define APB_CVI_E_BASE               0xCCCC0600   //( 0xCCCC0600, 0xCCCC06FC)
#define APB_DBGOSD_BASE              0xCC860900   //( 0xCC860900, 0xCC860918)
#define APB_DCF_BASE                 0xCC860A00   //( 0xCC860A00, 0xCC860A5C)
#define APB_DDS_BASE                 0xCC861C00   //( 0xCC861C00, 0xCC861C44)
#define APB_DNE0_BASE                0xCC880300   //( 0xCC880300, 0xCC88094C)
#define APB_DNE1_BASE                0xCC881200   //( 0xCC881200, 0xCC88184C)
#define APB_DNNR_BASE                0xCC680000   //( 0xCC680000, 0xCC680FFC)
#define APB_DNSR_BASE                0xCC660000   //( 0xCC660000, 0xCC660FFC)
#define APB_MCP_BASE                 0xCC420800   //( 0xCC420800, 0xCC420D44)
#define APB_MC_BASE                  0xCC420000   //( 0xCC420000, 0xCC4200EC)
#define APB_ME0_TOP_BASE             0xCC4A2400   //( 0xCC4A2400, 0xCC4A2FE4)
#define APB_ME0_MES_BASE             0xCC4A3C00   //( 0xCC4A3C04, 0xCC4A520C)
#define APB_ME0_MEP_BASE             0xCC4A5400   //( 0xCC4A5400, 0xCC4A6758)
#define APB_ME0_MCU_BASE             0xCC4A6C00   //( 0xCC4A6C00, 0xCC4A73D4)
#define APB_ME0_MCU_SEC_BASE         0xCC4A7400   //( 0xCC4A7400, 0xCC4A86BC)
#define APB_ME1_TOP_BASE             0xCC8A0800   //( 0xCC8A0800, 0xCC8A0CBC)
#define APB_ME1_MES_BASE             0xCC8A1400   //( 0xCC8A1404, 0xCC8A1C0C)
#define APB_ME1_MEP_BASE             0xCC8A2000   //( 0xCC8A2000, 0xCC8A2B50)
#define APB_ME1_MCU_BASE             0xCC8A3000   //( 0xCC8A3000, 0xCC8A4020)
#define APB_ME0_SPP_BASE             0xCC4A1000   //( 0xCC4A1000, 0xCC4A13E8)
#define APB_FME_SSD_BASE             0xCC4A1800   //( 0xCC4A1800, 0xCC4A2240)
#define APB_FMS_BASE                 0xCC4E1000   //( 0xCC4E1000, 0xCC4E1FDC)
#define APB_FPP_F0_BASE              0xCC821600   //( 0xCC821600, 0xCC821878)
#define APB_BDD_F0_BASE              0xCC822000   //( 0xCC822000, 0xCC8224A0)
#define APB_GSC_CORE_BASE            0xCC460200   //( 0xCC460200, 0xCC460220)
#define APB_GSC_GPD_BASE             0xCC460400   //( 0xCC460400, 0xCC46041C)
#define APB_OSC0_Y_BASE              0xCC460600   //( 0xCC460600, 0xCC460744)
#define APB_OSC0_C_BASE              0xCC460800   //( 0xCC460800, 0xCC460930)
#define APB_OSC1_Y_BASE              0xCC460A00   //( 0xCC460A00, 0xCC460AA0)
#define APB_OSC1_C_BASE              0xCC460C00   //( 0xCC460C00, 0xCC460C8C)
#define APB_OSC2_BASE                0xCC460E00   //( 0xCC460E00, 0xCC460EA0)
#define APB_OSC3_BASE                0xCC461000   //( 0xCC461000, 0xCC4610A0)
#define APB_SMTH_BASE                0xCC461200   //( 0xCC461200, 0xCC461230)
#define APB_OLB_BASE                 0xCC461400   //( 0xCC461400, 0xCC461454)
#define APB_HDR_BUF_DE_BASE          0xCCC10200   //( 0xCCC10200, 0xCCC10378)
#define APB_HDR_BUF_HDR_BASE         0xCCC10600   //( 0xCCC10600, 0xCCC107DC)
#define APB_HDR10_E_BASE             0xCCC10800   //( 0xCCC10800, 0xCCC10CC8)
#define APB_HDR10_O_BASE             0xCCC11A00   //( 0xCCC11A00, 0xCCC11EC8)
#define APB_HDR_DOLBY_BASE           0xCCC11000   //( 0xCCC11000, 0xCCC11998)
#define APB_HDR_DOLBY1_BASE          0xCCC12200   //( 0xCCC12200, 0xCCC12B98)
#define APB_IPP_M0_META_BASE         0xCC820200   //( 0xCC820200, 0xCC8203FC)
#define APB_IPP_M1_META_BASE         0xCC822700   //( 0xCC822700, 0xCC8228FC)
#define APB_GAV_HDR_S_BASE           0xCC823800   //( 0xCC823800, 0xCC823B48)
#define APB_AMG0_HEAD_BASE           0xCC824900   //( 0xCC824900, 0xCC824BFC)
#define APB_AMG1_BODY_BASE           0xCC824C00   //( 0xCC824C20, 0xCC824E38)
#define APB_AMG2_MTB_BASE            0xCC825800   //( 0xCC825800, 0xCC8259F4)
#define APB_AMG3_GRM_BASE            0xCC826000   //( 0xCC826000, 0xCC8262FC)
#define APB_GAV_SHP_BASE             0xCC825000   //( 0xCC825000, 0xCC8257FC)
#define APB_IPP_M0_BASE              0xCC820400   //( 0xCC820400, 0xCC820554)
#define APB_IPP_M1_BASE              0xCC820600   //( 0xCC820600, 0xCC820754)
#define APB_IPP_S0_BASE              0xCC820800   //( 0xCC820800, 0xCC8208DC)
#define APB_IPP_C0_BASE              0xCC820A00   //( 0xCC820A00, 0xCC820A88)
#define APB_IPP_D0_BASE              0xCC824000   //( 0xCC824000, 0xCC824090)
#define APB_IPP_D1_BASE              0xCC824200   //( 0xCC824200, 0xCC8242A8)
#define APB_IPP_G0_BASE              0xCC823C00   //( 0xCC823C00, 0xCC823D20)
#define APB_IPP_H0_BASE              0xCC820C00   //( 0xCC820C00, 0xCC820C3C)
#define APB_IPP_H1_BASE              0xCC820E00   //( 0xCC820E00, 0xCC820E3C)
#define APB_BDD_M0_BASE              0xCC824400   //( 0xCC824400, 0xCC8245C4)
#define APB_BDD_M1_BASE              0xCC824600   //( 0xCC824600, 0xCC8247C4)
#define APB_DOLBY1B_BASE             0xCC824F00   //( 0xCC824F00, 0xCC824F28)
#define APB_IPP_G0_SCY_BASE          0xCC823E00   //( 0xCC823E00, 0xCC823EA0)
#define APB_IPP_G0_SCC_BASE          0xCC823F00   //( 0xCC823F00, 0xCC823F8C)
#define APB_L3D_BASE                 0xCC860F00   //( 0xCC860F00, 0xCC860F74)
#define APB_LED_BASE                 0xCC8E0000   //( 0xCC8E0000, 0xCC8E22DC)
#define APB_UCR_BASE                 0xCC8E2E00   //( 0xCC8E2E00, 0xCC8E2E6C)
#define APB_GSR_BASE                 0xCC8E2A00   //( 0xCC8E2A00, 0xCC8E2AC0)
#define APB_OLED_BASE                0xCC8E3000   //( 0xCC8E3000, 0xCC8E3614)
#define APB_DECONTOUR_BASE           0xCC8E3800   //( 0xCC8E3800, 0xCC8E3848)
#define APB_CHIP_INFO_BASE           0xCC8F0000   //( 0xCC8F0000, 0xCC8F00C4)
#define APB_CHIP_INFO_DATA_BASE      0xCC8F0100   //( 0xCC8F0100, 0xCC8FC0FC)
#define APB_BV_DSC_BASE              0xCC8E4000   //( 0xCC8E4000, 0xCC8E4048)
#define APB_BV_USC_BASE              0xCC8E4200   //( 0xCC8E4200, 0xCC8E42CC)
#define APB_MCU_BASE                 0xCC080000   //( 0xCC080000, 0xCC0800F8)
#define APB_MCU_GK_AXI_BASE          0xCC081000   //( 0xCC081000, 0xCC081408)
#define APB_MCU_IPC_BASE             0xCC0A0000   //( 0xCC0A0000, 0xCC0A03FC)
#define APB_MCU_EDMA_BASE            0xCC0C0000   //( 0xCC0C0000, 0xCC0C0014)
#define APB_MCU_I2C_BASE             0xCC0E0000   //( 0xCC0E0000, 0xCC0E0024)
#define APB_MCU_GK_AND_IPC_BASE      0xCCE00000   //( 0xCCE00000, 0xCCE00FFC)
#define APB_MGI_RD_BASE              0xCC821D00   //( 0xCC821D00, 0xCC821D68)
#define APB_MGI_RE_BASE              0xCC821E00   //( 0xCC821E00, 0xCC821E90)
#define APB_IMX_GPD_BASE             0xCC821F00   //( 0xCC821F00, 0xCC821F1C)
#define APB_IMX_MIF0_BASE            0xCC822900   //( 0xCC822900, 0xCC822C24)
#define APB_IMX_MIF1_BASE            0xCC822D00   //( 0xCC822D00, 0xCC823030)
#define APB_IMX_MIF2_BASE            0xCC823100   //( 0xCC823100, 0xCC8233B8)
#define APB_IMX_MIF3_BASE            0xCC823400   //( 0xCC823400, 0xCC8236C0)
#define APB_ND0_MIF_BASE             0xCCC60E00   //( 0xCCC60E00, 0xCCC61078)
#define APB_ND1_MIF_BASE             0xCCC90E00   //( 0xCCC90E00, 0xCCC90FE8)
#define APB_SRE_MIF_BASE             0xCC623800   //( 0xCC623800, 0xCC623934)
#define APB_SRE1_MIF_BASE            0xCC623A00   //( 0xCC623A00, 0xCC623ACC)
#define APB_GSC_MIF0_BASE            0xCC461700   //( 0xCC461700, 0xCC4617C8)
#define APB_GSC_MIF1_BASE            0xCC461900   //( 0xCC461900, 0xCC4619EC)
#define APB_CCO_MIF0_BASE            0xCC860C00   //( 0xCC860C00, 0xCC860D00)
#define APB_CCO_MIF1_BASE            0xCC862900   //( 0xCC862900, 0xCC862A00)
#define APB_ME0_MIF_BASE             0xCC4A0200   //( 0xCC4A0200, 0xCC4A0588)
#define APB_SSD_MIF_BASE             0xCC4A0800   //( 0xCC4A0800, 0xCC4A0B28)
#define APB_ME1_MIF_BASE             0xCC8A0400   //( 0xCC8A0400, 0xCC8A0644)
#define APB_FMS_MIF0_BASE            0xCC4E0A00   //( 0xCC4E0A00, 0xCC4E0D50)
#define APB_FMC_MIF0_BASE            0xCC421800   //( 0xCC421800, 0xCC421990)
#define APB_FMC_MIF1_BASE            0xCC421A00   //( 0xCC421A00, 0xCC421BA0)
#define APB_FMC_MIF2_BASE            0xCC421C00   //( 0xCC421C00, 0xCC421D08)
#define APB_FMC_MIF3_BASE            0xCC421E00   //( 0xCC421E00, 0xCC421F08)
#define APB_CVI_MON_BASE             0xCCCC1000   //( 0xCCCC1000, 0xCCCC10FC)
#define APB_HDR_MON_BASE             0xCCC10100   //( 0xCCC10100, 0xCCC101FC)
#define APB_IMX_MON_BASE             0xCC820B00   //( 0xCC820B00, 0xCC820BFC)
#define APB_VDO_MON_BASE             0xCCC30100   //( 0xCCC30100, 0xCCC301FC)
#define APB_ND0_MON_BASE             0xCCC60D00   //( 0xCCC60D00, 0xCCC60DFC)
#define APB_ND1_MON_BASE             0xCCC90D00   //( 0xCCC90D00, 0xCCC90DFC)
#define APB_SRE_MON_BASE             0xCC620100   //( 0xCC620100, 0xCC6201FC)
#define APB_FMC_MON_BASE             0xCC421100   //( 0xCC421100, 0xCC4211FC)
#define APB_GSC_MON_BASE             0xCC461600   //( 0xCC461600, 0xCC4616FC)
#define APB_VSD_MON_BASE             0xCCA24000   //( 0xCCA24000, 0xCCA240FC)
#define APB_CCO_MON_BASE             0xCC860B00   //( 0xCC860B00, 0xCC860BFC)
#define APB_LED_MON_BASE             0xCC8E3E00   //( 0xCC8E3E00, 0xCC8E3EFC)
#define APB_ME0_MON_BASE             0xCC4A0100   //( 0xCC4A0100, 0xCC4A01FC)
#define APB_ME1_MON_BASE             0xCC8A0100   //( 0xCC8A0100, 0xCC8A01FC)
#define APB_FMS_MON_BASE             0xCC4E0100   //( 0xCC4E0100, 0xCC4E01FC)
#define APB_DNE_MON_BASE             0xCC880100   //( 0xCC880100, 0xCC8801FC)
#define APB_MVI_RA_BASE              0xCC821A00   //( 0xCC821A00, 0xCC821A24)
#define APB_MVI_RB_BASE              0xCC821B00   //( 0xCC821B00, 0xCC821B24)
#define APB_MVI_RC_BASE              0xCC821C00   //( 0xCC821C00, 0xCC821C24)
#define APB_VDO_BODP_RC0_BASE        0xCCC30900   //( 0xCCC30900, 0xCCC3095C)
#define APB_VDO_CORE_BASE            0xCCC30300   //( 0xCCC30300, 0xCCC303FC)
#define APB_VDO_GMAU_BASE            0xCCC30400   //( 0xCCC30400, 0xCCC304FC)
#define APB_VDO_CORE1_BASE           0xCCC30500   //( 0xCCC30500, 0xCCC305FC)
#define APB_VDO_GMAU1_BASE           0xCCC30600   //( 0xCCC30600, 0xCCC306FC)
#define APB_VDO_TOP_BASE             0xCCC30700   //( 0xCCC30700, 0xCCC307FC)
#define APB_VDO_CRC_BASE             0xCCC30800   //( 0xCCC30800, 0xCCC308EC)
#define APB_VDO_CORE2_BASE           0xCCC31100   //( 0xCCC31100, 0xCCC311EC)
#define APB_VDO_GMAU2_BASE           0xCCC31200   //( 0xCCC31200, 0xCCC312EC)
#define APB_VDO_TOP1_BASE            0xCCC31500   //( 0xCCC31500, 0xCCC315FC)
#define APB_VDO_CRC1_BASE            0xCCC31600   //( 0xCCC31600, 0xCCC316EC)
#define APB_DNR0_MUX_BASE            0xCCC60B00   //( 0xCCC60B00, 0xCCC60B94)
#define APB_DNR1_MUX_BASE            0xCCC90A00   //( 0xCCC90A00, 0xCCC90A94)
#define APB_ND0_BASE                 0xCCC60100   //( 0xCCC60100, 0xCCC604E4)
#define APB_DNR0_BASE                0xCCC60500   //( 0xCCC60500, 0xCCC60AFC)
#define APB_ND1_BASE                 0xCCC90100   //( 0xCCC90100, 0xCCC904E4)
#define APB_DNR1_BASE                0xCCC90500   //( 0xCCC90500, 0xCCC90948)
#define APB_NPP_N0_BASE              0xCC821400   //( 0xCC821400, 0xCC8214FC)
#define APB_AFBC0_BASE               0xCC860800   //( 0xCC860800, 0xCC8608FC)
#define APB_AFBC1_BASE               0xCC862800   //( 0xCC862800, 0xCC8628FC)
#define APB_AFRC0_BASE               0xCC863500   //( 0xCC863500, 0xCC86359C)
#define APB_AFRC1_BASE               0xCC863600   //( 0xCC863600, 0xCC86369C)
#define APB_OSD_SHP_BASE             0xCC861D00   //( 0xCC861D00, 0xCC861FFC)
#define APB_OSD_STATUS_BASE          0xCC860100   //( 0xCC860100, 0xCC86013C)
#define APB_OSD_COMMON_BASE          0xCC860140   //( 0xCC860140, 0xCC860170)
#define APB_OSD_SOSD_BASE            0xCC860180   //( 0xCC860180, 0xCC8601DC)
#define APB_OSD_BOSD_BASE            0xCC860200   //( 0xCC860200, 0xCC8602E4)
#define APB_OSD_IMAGE0_BASE          0xCC860300   //( 0xCC860300, 0xCC8603EC)
#define APB_OSD_IMAGE0_1_BASE        0xCC860400   //( 0xCC860400, 0xCC8604EC)
#define APB_OSD_IMAGE1_BASE          0xCC860500   //( 0xCC860500, 0xCC8605EC)
#define APB_OSD_CURSOR_BASE          0xCC860600   //( 0xCC860600, 0xCC8606CC)
#define APB_OSD_HDRUI_BASE           0xCC860700   //( 0xCC860700, 0xCC8607D8)
#define APB_PWM_BASE                 0xCCA20100   //( 0xCCA20100, 0xCCA201FC)
#define APB_ROT_BASE                 0xCC421200   //( 0xCC421200, 0xCC421398)
#define APB_SHC_BASE                 0xCC621400   //( 0xCC621400, 0xCC621AFC)
#define APB_SRE_COMM_BASE            0xCC620300   //( 0xCC620300, 0xCC620584)
#define APB_SR_MERG_BASE             0xCC622A00   //( 0xCC622A00, 0xCC622BFC)
#define APB_NR_MERG_BASE             0xCC622800   //( 0xCC622800, 0xCC62288C)
#define APB_SCY_SW_BASE              0xCC620B00   //( 0xCC620B00, 0xCC620BA0)
#define APB_SCY_4K_BASE              0xCC621C00   //( 0xCC621C00, 0xCC621CA0)
#define APB_SCC_4K_BASE              0xCC622500   //( 0xCC622500, 0xCC62258C)
#define APB_SCY1_SW_BASE             0xCC622C00   //( 0xCC622C00, 0xCC622CA0)
#define APB_SCC1_4K_BASE             0xCC623500   //( 0xCC623500, 0xCC62358C)
#define APB_SRE_MUX_BASE             0xCC620600   //( 0xCC620600, 0xCC620694)
#define APB_SHY1_2K_BASE             0xCC622D00   //( 0xCC622D00, 0xCC6234FC)
#define APB_SHY_2K_BASE              0xCC620C00   //( 0xCC620C00, 0xCC6213FC)
#define APB_CVI_CTRL_BASE            0xCCCC0000   //( 0xCCCC0000, 0xCCCC00FC)
#define APB_IMX_CTRL_BASE            0xCC820000   //( 0xCC820000, 0xCC8200FC)
#define APB_IMX_CTRL1_BASE           0xCC820100   //( 0xCC820100, 0xCC8201FC)
#define APB_GAV_CTRL_BASE            0xCC823700   //( 0xCC823700, 0xCC8237FC)
#define APB_VDO_CTRL_BASE            0xCCC30000   //( 0xCCC30000, 0xCCC300FC)
#define APB_HDR_CTRL_BASE            0xCCC10000   //( 0xCCC10000, 0xCCC100FC)
#define APB_HDR_CTRL1_BASE           0xCCC12000   //( 0xCCC12000, 0xCCC120FC)
#define APB_ND0_CTRL_BASE            0xCCC60000   //( 0xCCC60000, 0xCCC600FC)
#define APB_ND1_CTRL_BASE            0xCCC90000   //( 0xCCC90000, 0xCCC900FC)
#define APB_SRE_CTRL_BASE            0xCC620000   //( 0xCC620000, 0xCC6200FC)
#define APB_GSC_CTRL_BASE            0xCC460000   //( 0xCC460000, 0xCC4600FC)
#define APB_VSD_CTRL_BASE            0xCCA20000   //( 0xCCA20000, 0xCCA200FC)
#define APB_VSD_CTRL1_BASE           0xCCA20B00   //( 0xCCA20B18, 0xCCA20BEC)
#define APB_CCO_CTRL_BASE            0xCC860000   //( 0xCC860000, 0xCC8600FC)
#define APB_CCO_CTRL1_BASE           0xCC860E00   //( 0xCC860E00, 0xCC860EFC)
#define APB_LED_CTRL_BASE            0xCC8E3D00   //( 0xCC8E3D00, 0xCC8E3DFC)
#define APB_ME0_CTRL_BASE            0xCC4A0000   //( 0xCC4A0000, 0xCC4A00FC)
#define APB_ME1_CTRL_BASE            0xCC8A0000   //( 0xCC8A0000, 0xCC8A00FC)
#define APB_FMC_CTRL_BASE            0xCC421000   //( 0xCC421000, 0xCC4210FC)
#define APB_FMS_CTRL_BASE            0xCC4E0000   //( 0xCC4E0000, 0xCC4E00FC)
#define APB_DNE_CTRL_BASE            0xCC880000   //( 0xCC880000, 0xCC8800FC)
#define APB_VCP_DE_BASE              0xCCA21000   //( 0xCCA21000, 0xCCA212D8)
#define APB_VCP_DISP_BASE            0xCCA21000   //( 0xCCA21400, 0xCCA21954)
#define APB_VCP_BOX_BASE             0xCCA21000   //( 0xCCA21C00, 0xCCA21DF4)
#define APB_CVI_VERI_BASE            0xCCCC1100   //( 0xCCCC1100, 0xCCCC110C)
#define APB_HDR_VERI_BASE            0xCCC12100   //( 0xCCC12100, 0xCCC1210C)
#define APB_IMX_VERI_BASE            0xCC820D00   //( 0xCC820D00, 0xCC820DAC)
#define APB_ND0_VERI_BASE            0xCCC61100   //( 0xCCC61100, 0xCCC6110C)
#define APB_ND1_VERI_BASE            0xCCC91100   //( 0xCCC91100, 0xCCC9110C)
#define APB_SRE_VERI_BASE            0xCC620200   //( 0xCC620200, 0xCC62020C)
#define APB_FMC_VERI_BASE            0xCC421400   //( 0xCC421400, 0xCC42140C)
#define APB_GSC_VERI_BASE            0xCC460100   //( 0xCC460100, 0xCC46010C)
#define APB_VSD_VERI_BASE            0xCCA23F00   //( 0xCCA23F00, 0xCCA23F0C)
#define APB_CCO_VERI_BASE            0xCC862300   //( 0xCC862300, 0xCC86238C)
#define APB_LED_VERI_BASE            0xCC8E3F00   //( 0xCC8E3F00, 0xCC8E3F0C)
#define APB_ME0_VERI_BASE            0xCC4A8C00   //( 0xCC4A8C00, 0xCC4A8C0C)
#define APB_ME1_VERI_BASE            0xCC8A0200   //( 0xCC8A0200, 0xCC8A020C)
#define APB_FMS_VERI_BASE            0xCC4E0200   //( 0xCC4E0200, 0xCC4E020C)
#define APB_DNE_VERI_BASE            0xCC880200   //( 0xCC880200, 0xCC88020C)
#define APB_OBC_M_SC_BASE            0xCC863300   //( 0xCC863300, 0xCC8633FC)
#define APB_OBC_P_SC_BASE            0xCC863400   //( 0xCC863400, 0xCC8634FC)
#define APB_OBC_BODY_BASE            0xCCA20500   //( 0xCCA20500, 0xCCA205F0)
#define APB_OBC_HEAD_BASE            0xCCA20700   //( 0xCCA20700, 0xCCA20780)
#define APB_CSR_BASE                 0xCCA23C00   //( 0xCCA23C00, 0xCCA23D48)
#define APB_VSD_GSR_BASE             0xCCA23E00   //( 0xCCA23E90, 0xCCA23EC0)
#define APB_OBE_BASE                 0xCCA20200   //( 0xCCA20200, 0xCCA20424)
#define APB_DTM_BASE                 0xCCA20C00   //( 0xCCA20C00, 0xCCA20CFC)
#define APB_VSD_SHP_BASE             0xCCA22000   //( 0xCCA22000, 0xCCA228FC)
#endif

#if 1   //TODO:
#define PE_O24_P1_CC_OFST			(0x861000)
#define PE_O24_P1_CC2_OFST			(0x861600)

#define PE_O24_CVI_A_OFST			(0xCC0200)
#define PE_O24_CVI_B_OFST			(0xCC0300)
#define PE_O24_CVI_C_OFST			(0xCC0400)
#define PE_O24_CVI_D_OFST			(0xCC0500)
#define PE_O24_CVI_E_OFST			(0xCC0600)

#define PE_O24_AMG_HEAD_OFST		(0x824900)
#define PE_O24_AMG_BODY_OFST		(0x824C20)
#define PE_O24_AMG_MTB_OFST			(0x825800)
#define PE_O24_AMG_GRM_OFST			(0x826000)

#define PE_O24_CCO_DCNT_OFST		(0x862100)

#define PE_O24_OSC0_Y_OFST			(0x460600)
#define PE_O24_OSC1_Y_OFST			(0x460A00)
#define PE_O24_OSC0_C_OFST			(0x460800)
#define PE_O24_OSC1_C_OFST			(0x460C00)
#define PE_O24_OSC2_YC_OFST			(0x460E00)
#define PE_O24_OSC3_YC_OFST			(0x461000)


#define PE_O24_ND0_OFST				(0xC60100)
#define PE_O24_ND1_OFST				(0xC90100)
#define PE_O24_DNR0_OFST			(0xC60500)
#define PE_O24_DNR1_OFST			(0xC90500)
#define PE_O24_ND0_VERI_OFST		(0xC61100)
#define PE_O24_ND1_VERI_OFST		(0xC91100)

#define PE_O24_IMX_OFST				(0x8200B8)

#define PE_O24_P1_VSD_SHP_L_OFST	(0xA22000)
#define PE_O24_P1_VSD_OBC_BODY_OFST	(0xA20500)
#define PE_O24_P1_VSD_OBC_HEAD_OFST	(0xA20700)
#define PE_O24_P1_VSD_OBC_M_SC_OFST (0x863300)
#define PE_O24_P1_VSD_DTM_OFST		(0xA20C00)
#define PE_O24_P1_VSD_OBE_OFST		(0xA20200)
#define PE_O24_OSD_ORD_OFST		    (0x860480)


#define PE_O24_VCP_DISP_OFST		(0xA21400)
#define PE_O24_OLB_OFST				(0x461400)
#define PE_O24_VSD0_VERI_OFST		(0xA23F00)

#define PE_O24_SR_2K_SHP0_OFST		(0x620C00)
#define PE_O24_SR_2K_SHP1_OFST		(0x622D00)
#define PE_O24_SR_2K_SHC_OFST		(0x621400)
#define PE_O24_SR_MERG_OFST		    (0x622A00)
#define PE_O24_GAV_SHP_OFST		    (0x825000)

#define PE_O24_REG_WRITE_BASE		(0x0)

#if 0	//TODO:
#define PE_O24_HDMI_A_OFST			(0x000100)
#define PE_O24_HDMI_B_OFST			(0x000140)
#define PE_O24_HDMI_C_OFST			(0x000180)
#define PE_O24_HDMI_D_OFST			(0x0001C0)

#define PE_O24_IPP_OFST				(0x014400)

#define PE_O24_VSD_OFST				(0x00B0B0)

#define PE_O24_P1_CCO_EO_DIFF		(PE_O24_P1_CCO_O_OFST - PE_O24_P1_CCO_E_OFST)

#define PE_O24_HDMI_A_BASE			(PE_O24_DE_BASE + PE_O24_HDMI_A_OFST)
#define PE_O24_HDMI_B_BASE			(PE_O24_DE_BASE + PE_O24_HDMI_B_OFST)
#define PE_O24_HDMI_C_BASE			(PE_O24_DE_BASE + PE_O24_HDMI_C_OFST)
#define PE_O24_HDMI_D_BASE			(PE_O24_DE_BASE + PE_O24_HDMI_D_OFST)

#define PE_O24_IPP_BASE				(PE_O24_DE_BASE + PE_O24_IPP_OFST)

#define PE_O24_VSD_BASE				(PE_O24_DE_BASE + PE_O24_VSD_OFST)
#endif  //#if 0	//TODO:

#define PE_O24_P1_CC_BASE			(PE_O24_DE_BASE + PE_O24_P1_CC_OFST)
#define PE_O24_P1_CC2_BASE			(PE_O24_DE_BASE + PE_O24_P1_CC2_OFST)

#define PE_O24_CVI_A_BASE			(PE_O24_DE_BASE + PE_O24_CVI_A_OFST)
#define PE_O24_CVI_B_BASE			(PE_O24_DE_BASE + PE_O24_CVI_B_OFST)
#define PE_O24_CVI_C_BASE			(PE_O24_DE_BASE + PE_O24_CVI_C_OFST)
#define PE_O24_CVI_D_BASE			(PE_O24_DE_BASE + PE_O24_CVI_D_OFST)
#define PE_O24_AMG_BODY_BASE		(PE_O24_DE_BASE + PE_O24_AMG_BODY_OFST)
#define PE_O24_AMG_HEAD_BASE		(PE_O24_DE_BASE + PE_O24_AMG_HEAD_OFST)
#define PE_O24_AMG_MTB_BASE			(PE_O24_DE_BASE + PE_O24_AMG_MTB_OFST)
#define PE_O24_AMG_GRM_BASE			(PE_O24_DE_BASE + PE_O24_AMG_GRM_OFST)

#define PE_O24_CCO_DCNT_BASE		(PE_O24_DE_BASE + PE_O24_CCO_DCNT_OFST)

#define PE_O24_OSC0_Y_BASE			(PE_O24_DE_BASE + PE_O24_OSC0_Y_OFST)
#define PE_O24_OSC1_Y_BASE			(PE_O24_DE_BASE + PE_O24_OSC1_Y_OFST)
#define PE_O24_OSC0_C_BASE			(PE_O24_DE_BASE + PE_O24_OSC0_C_OFST)
#define PE_O24_OSC1_C_BASE			(PE_O24_DE_BASE + PE_O24_OSC1_C_OFST)
#define PE_O24_OSC2_YC_BASE			(PE_O24_DE_BASE + PE_O24_OSC2_YC_OFST)
#define PE_O24_OSC3_YC_BASE			(PE_O24_DE_BASE + PE_O24_OSC3_YC_OFST)


#define PE_O24_ND0_BASE				(PE_O24_DE_BASE + PE_O24_ND0_OFST)
#define PE_O24_ND1_BASE				(PE_O24_DE_BASE + PE_O24_ND1_OFST)
#define PE_O24_DNR0_BASE			(PE_O24_DE_BASE + PE_O24_DNR0_OFST)
#define PE_O24_DNR1_BASE			(PE_O24_DE_BASE + PE_O24_DNR1_OFST)
#define PE_O24_ND0_VERI_BASE		(PE_O24_DE_BASE + PE_O24_ND0_VERI_OFST)
#define PE_O24_ND1_VERI_BASE		(PE_O24_DE_BASE + PE_O24_ND1_VERI_OFST)


#define PE_O24_IMX_BASE				(PE_O24_DE_BASE + PE_O24_IMX_OFST)

#define PE_O24_P1_VSD_SHP_L_BASE		(PE_O24_DE_BASE + PE_O24_P1_VSD_SHP_L_OFST)
#define PE_O24_P1_VSD_OBC_BODY_BASE	(PE_O24_DE_BASE + PE_O24_P1_VSD_OBC_BODY_OFST)
#define PE_O24_P1_VSD_OBC_HEAD_BASE	(PE_O24_DE_BASE + PE_O24_P1_VSD_OBC_HEAD_OFST)
#define PE_O24_P1_VSD_OBC_M_SC_BASE	(PE_O24_DE_BASE + PE_O24_P1_VSD_OBC_M_SC_OFST)
#define PE_O24_P1_VSD_OBE_BASE		(PE_O24_DE_BASE + PE_O24_P1_VSD_OBE_OFST)
#define PE_O24_P1_VSD_DTM_BASE		(PE_O24_DE_BASE + PE_O24_P1_VSD_DTM_OFST)

#define PE_O24_VCP_DISP_BASE		(PE_O24_DE_BASE + PE_O24_VCP_DISP_OFST)
#define PE_O24_OLB_BASE				(PE_O24_DE_BASE + PE_O24_OLB_OFST)
#define PE_O24_VSD0_VERI_BASE		(PE_O24_DE_BASE + PE_O24_VSD0_VERI_OFST)

#define PE_O24_SR_2K_SHP0_BASE		(PE_O24_DE_BASE + PE_O24_SR_2K_SHP0_OFST)
#define PE_O24_SR_2K_SHP1_BASE		(PE_O24_DE_BASE + PE_O24_SR_2K_SHP1_OFST)
#define PE_O24_SR_2K_SHC_BASE		(PE_O24_DE_BASE + PE_O24_SR_2K_SHC_OFST)
#define PE_O24_SR_MERG_BASE			(PE_O24_DE_BASE + PE_O24_SR_MERG_OFST)
#define PE_O24_GAV_SHP_BASE			(PE_O24_DE_BASE + PE_O24_GAV_SHP_OFST)
#define PE_O24_SR_VERI_BASE			(PE_O24_DE_BASE + 0xC40200)
#define PE_O24_MCU_BASE				(PE_O24_DE_BASE + 0x080000)
#define PE_O24_CCO_VERI_BASE		(PE_O24_DE_BASE + 0x862300)
#define PE_O24_OSD_ORD_BASE		    (PE_O24_DE_BASE + PE_O24_OSD_ORD_OFST)
#endif  //#if 0	//TODO:

#ifdef INCLUDE_KDRV_DE
#define PE_O24_DDR_DB0_BASE			(g_pe_db.base)
#define PE_O24_DDR_DB0_SIZE			(g_pe_db.size)

#define PE_O24_DDR_DB_BASE			(g_pe_db.base)
#define PE_O24_DDR_DB_SIZE			(g_pe_db.size+g_pe_hdr.size)

/* PE_O24F22_DDR_BASE : base + 512k */
#define PE_O24F22_DDR_BASE			(PE_O24_DDR_DB0_BASE + 0x00080000)
/* PE_O24F22_DCM_DDR_BASE : base + 1M */
#define PE_O24F22_DCM_DDR_BASE		(PE_O24_DDR_DB0_BASE + 0x00100000)
/* PE_O24F22_DBC_DDR_BASE : base + 1M + 200k */
#define PE_O24F22_DBC_DDR_BASE		(PE_O24_DDR_DB0_BASE + 0x00132000)
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

#endif	/* _PE_REG_DEF_O24_H_ */

