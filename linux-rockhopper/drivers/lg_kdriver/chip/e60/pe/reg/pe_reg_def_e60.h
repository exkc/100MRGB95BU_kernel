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

/** @file pe_reg_def_e60.h
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

#ifndef _PE_REG_DEF_E60_H_
#define _PE_REG_DEF_E60_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
/* E60_DE_BASE */
#define PE_E60_DE_BASE				(0xC9000000)

#if 0	//Ref. (see REGISTER/abp_base.h) (E60A0_PQE_FW)
#define APB_DCF_BASE                 0xC9035100
#define APB_CC_BASE                  0xC902E500
#define APB_CC2_BASE                 0xC902F000
#define APB_CVD_BASE                 0xC9000600
#define APB_PDF_BASE                 0xC9000000
#define APB_CVI_A_BASE               0xC9000200
#define APB_CVI_B_BASE               0xC9000300
#define APB_CVI_C_BASE               0xC9000400
#define APB_CVI_D_BASE               0xC9000500
#define APB_MCP_BASE                 0xC9041B00
#define APB_MC_BASE                  0xC903E300
#define APB_ROT_BASE                 0xC9040300
#define APB_ME0_TOP_BASE             0xC9046400
#define APB_ME0_MES_BASE             0xC9047C00
#define APB_ME0_MEP_BASE             0xC9049400
#define APB_ME0_MCU_BASE             0xC904AC00
#define APB_ME0_MCU_SEC_BASE         0xC904B400
#define APB_ME1_TOP_BASE             0xC904D800
#define APB_ME1_MES_BASE             0xC904E400
#define APB_ME1_MEP_BASE             0xC904F000
#define APB_ME1_MCU_BASE             0xC9050000
#define APB_ME0_SPP_BASE             0xC9045000
#define APB_FME_SSD_BASE             0xC9045800
#define APB_FMS_BASE                 0xC9022000
#define APB_FPP_F0_BASE              0xC9007A00
#define APB_BDD_F0_BASE              0xC9007E00
#define APB_OSC0_Y_BASE              0xC9020200
#define APB_OSC1_Y_BASE              0xC9020400
#define APB_OSC0_C_BASE              0xC901E200
#define APB_OSC1_C_BASE              0xC901E400
#define APB_HDR_BUF_DE_BASE          0xC9016200
#define APB_HDR_BUF_HDR_BASE         0xC9016800
#define APB_HDR10_BASE               0xC9016C00
#define APB_SDR2HDR_BASE             0xC9017000
#define APB_HDR_DOLBY_BASE           0xC9017400
#define APB_HDR10_1_BASE             0xC9017C00
#define APB_SDR2HDR_1_BASE           0xC9018000
#define APB_HDR_DOLBY_1_BASE         0xC9018D00
#define APB_HDR_GAV_BASE             0xC9009700
#define APB_IPP_M0_META_BASE         0xC9004A00
#define APB_IPP_M1_META_BASE         0xC9004C00
#define APB_IPP_M0_BASE              0xC9003600
#define APB_SCY_M0_BASE              0xC9003900
#define APB_SCC_M0_BASE              0xC9003A00
#define APB_IPP_M1_BASE              0xC9008700
#define APB_IPP_S0_BASE              0xC9007600
#define APB_BDD_S0_BASE              0xC9007800
#define APB_IPP_C0_BASE              0xC9008400
#define APB_GAV_C0_BASE              0xC9009B00
#define APB_IPP_H0_BASE              0xC9003800
#define APB_IPP_H1_BASE              0xC9008600
#define APB_IPP_M1_CROP_BASE         0xC9004E00
#define APB_IPP_H1_CROP_BASE         0xC9004F00
#define APB_IPP_S0_CROP_BASE         0xC9005000
#define APB_IPP_S0B_CROP_BASE         0xC9005100
#define APB_IPP_C0_CROP_BASE         0xC9005200
#define APB_IPP_G0_CROP_BASE         0xC9005300
#define APB_HDR_EL_CROP_BASE         0xC9005400
#define APB_L3D_BASE                 0xC902E400
#define APB_LED_BASE                 0xC9036400
#define APB_UCR_BASE                 0xC9039200
#define APB_LED_OBC_BASE             0xC9039400
#define APB_LED_GSR_BASE             0xC903BD00
#define APB_OLED_BASE                0xC903A400
#define APB_DECONTOUR_CTRL_BASE         0xC903AC00
#define APB_DECONTOUR_0_BASE         0xC903AD00
#define APB_DECONTOUR_1_BASE         0xC903B100
#define APB_CHIP_INFO_BASE           0xC90D0000
#define APB_CHIP_INFO_DATA_BASE         0xC90D0100
#define APB_SRINF0_BASE              0xC9060000
#define APB_SRINF1_BASE              0xC9061000
#define APB_SRINF2_BASE              0xC9062000
#define APB_SRINF3_BASE              0xC9063000
#define APB_SRINF4_BASE              0xC9064000
#define APB_MCU_BASE                 0xC9026000
#define APB_GSC0_MIF0_BASE           0xC9020700
#define APB_GSC0_MIF1_BASE           0xC9020900
#define APB_GSC1_MIF0_BASE           0xC901E700
#define APB_GSC1_MIF1_BASE           0xC901E900
#define APB_GSC1_MIF2_BASE           0xC901EB00
#define APB_GSC1_MIF3_BASE           0xC901ED00
#define APB_CCO1_MIF0_BASE           0xC9031600
#define APB_CCO1_MIF1_BASE           0xC9031800
#define APB_ME0_MIF_BASE             0xC9044200
#define APB_SSD_MIF_BASE             0xC9044800
#define APB_ME1_MIF_BASE             0xC904D400
#define APB_FMS0_MIF0_BASE           0xC9021A00
#define APB_FMS0_MIF1_BASE           0xC9021C00
#define APB_FMC1_MIF0_BASE           0xC9042300
#define APB_FMC1_MIF1_BASE           0xC9042500
#define APB_FMC1_MIF2_BASE           0xC9042700
#define APB_FMC1_MIF3_BASE           0xC9042900
#define APB_FMC1_MIF4_BASE           0xC9042B00
#define APB_FMC1_MIF5_BASE           0xC9042D00
#define APB_FMC1_MIF6_BASE           0xC9042F00
#define APB_FMC1_MIF7_BASE           0xC9043100
#define APB_OBD_MIF0_BASE            0xC9068D00
#define APB_IMX0_MIF0_BASE           0xC9003E00
#define APB_IMX0_MIF1_BASE           0xC9004100
#define APB_IMX0_MIF2_BASE           0xC9004400
#define APB_IMX0_MIF3_BASE           0xC9004700
#define APB_IMX1_MIF4_BASE           0xC9008A00
#define APB_IMX1_MIF5_BASE           0xC9008D00
#define APB_IMX1_MIF6_BASE           0xC9009000
#define APB_IMX1_MIF7_BASE           0xC9009300
#define APB_ND1_MIF0_BASE            0xC9011500
#define APB_ND1_MIF1_BASE            0xC9011900
#define APB_ND1_MIF2_BASE            0xC9011C00
#define APB_SRE_MIF0_BASE            0xC901CD00
#define APB_SRE_MIF1_BASE            0xC901CF00
#define APB_GSC0_MON_BASE            0xC9020600
#define APB_GSC1_MON_BASE            0xC901E600
#define APB_VSD0_MON_BASE            0xC9029B00
#define APB_VSD1_MON_BASE            0xC902CE00
#define APB_CCO0_MON_BASE            0xC902E200
#define APB_CCO1_MON_BASE            0xC9030200
#define APB_CCO2_MON_BASE            0xC9033200
#define APB_LED0_MON_BASE            0xC9036100
#define APB_LED1_MON_BASE            0xC903A100
#define APB_ME0_MON_BASE             0xC9044100
#define APB_ME1_MON_BASE             0xC904D100
#define APB_FMS_MON_BASE             0xC9021100
#define APB_FMC0_MON_BASE            0xC903E100
#define APB_FMC1_MON_BASE            0xC9041100
#define APB_OBD_MON_BASE             0xC9068100
#define APB_CVI_MON_BASE             0xC9000F00
#define APB_HDR_MON_BASE             0xC9016100
#define APB_IMX0_MON_BASE            0xC9003300
#define APB_IMX0_MON1_BASE           0xC9003400
#define APB_IMX1_MON_BASE            0xC9007300
#define APB_IMX1_MON1_BASE           0xC9007400
#define APB_IMX2_MON_BASE            0xC900B200
#define APB_ND0_MON_BASE             0xC900EB00
#define APB_ND1_MON_BASE             0xC9010B00
#define APB_ND2_MON_BASE             0xC9012B00
#define APB_ND3_MON_BASE             0xC9014B00
#define APB_SRE_MON_BASE             0xC901A100
#define APB_SRE1_MON_BASE            0xC901D200
#define APB_MVI_RA_BASE              0xC9003B00
#define APB_MVI_RB_BASE              0xC9009D00
#define APB_MVI_RC_BASE              0xC9009E00
#define APB_VDO_CORE_BASE            0xC900B400
#define APB_VDO_GMAU_BASE            0xC900B500
#define APB_BODP_RC0_BASE            0xC900BC00
#define APB_BODP_RC1_BASE            0xC900C000
#define APB_VDO_CORE1_BASE           0xC900B600
#define APB_VDO_GMAU1_BASE           0xC900B700
#define APB_VDO_TOP_BASE             0xC900B800
#define APB_VDO_CRC_BASE             0xC900B900
#define APB_VDO_CORE2_BASE           0xC900CC00
#define APB_VDO_GMAU2_BASE           0xC900CD00
#define APB_VDO_TOP1_BASE            0xC900D000
#define APB_VDO_CRC1_BASE            0xC900D100
#define APB_DNR0_MUX_BASE            0xC900EA00
#define APB_DNR1_MUX_BASE            0xC9010A00
#define APB_ND0_BASE                 0xC900E100
#define APB_DNR0_BASE                0xC900E500
#define APB_ND1_BASE                 0xC9010100
#define APB_DNR1_BASE                0xC9010500
#define APB_ND2_BASE                 0xC9012100
#define APB_DNR2_BASE                0xC9012500
#define APB_ND3_BASE                 0xC9014100
#define APB_DNR3_BASE                0xC9014500
#define APB_ND0_OBC_OBJT_BASE         0xC900F100
#define APB_ND0_OBC_FACE_BASE         0xC900F300
#define APB_DNR0_OBC_OBJT_BASE         0xC900ED00
#define APB_DNR0_OBC_FACE_BASE         0xC900EF00
#define APB_OBC_M_SC_BASE            0xC9031E00
#define APB_OBD_BASE                 0xC9068300
#define APB_OSDASR_BASE              0xC9052000
#define APB_OSDYSR_BASE              0xC9056000
#define APB_AFBC0_BASE               0xC9031C00
#define APB_AFBC1_BASE               0xC9031D00
#define APB_MERG_Y_BASE              0xC9030E00
#define APB_MERG_A_BASE              0xC9031200
#define APB_OSD_SHP_Y_BASE           0xC9033400
#define APB_OSD_SHP_A_BASE           0xC9033C00
#define APB_OSD1_SHP_L_BASE          0xC9034400
#define APB_OSD_PREP_STATUS_BASE         0xC9030400
#define APB_OSD_PREP_TOP_BASE         0xC9030500
#define APB_OSD_PREP_IMG0_BASE         0xC9030600
#define APB_OSD_PREP_IMG1_BASE         0xC9030700
#define APB_OSD_PREP_EST_BASE         0xC9030A00
#define APB_OSD_PREP_CSR_BASE         0xC9030B00
#define APB_OSD_POST_STATUS_BASE         0xC9034800
#define APB_OSD_POST_TOP_BASE         0xC9034880
#define APB_OSD_POST_IMG_BASE         0xC9034900
#define APB_OSD_POST_EST_BASE         0xC9034A00
#define APB_OSD_POST_CSR_BASE         0xC9034B00
#define APB_BOSD_MIXER_BASE          0xC9034C00
#define APB_SOSD_MIXER_BASE          0xC9034D00
#define APB_OSD_GSR_BASE             0xC9035200
#define APB_PWM_BASE                 0xC9029100
#define APB_SHC_BASE                 0xC901D400
#define APB_SHC_BRG_BASE             0xC901DC00
#define APB_SRE_COMM_BASE            0xC901AD00
#define APB_MERG_BASE                0xC901C900
#define APB_SCY_2K_BASE              0xC901AE00
#define APB_SCY_4K_BASE              0xC901B700
#define APB_SCY_8K_BASE              0xC901C800
#define APB_SCC_BASE                 0xC901DD00
#define APB_SHY_2K_BASE              0xC901AF00
#define APB_SHY_4K_BASE              0xC901B800
#define APB_SRTRA_BASE               0xC9054000
#define APB_GSC0_CTRL_BASE           0xC9020000
#define APB_GSC1_CTRL_BASE           0xC901E000
#define APB_VSD0_CTRL_BASE           0xC9029000
#define APB_VSD0_CTRL1_BASE          0xC9029700
#define APB_VSD1_CTRL_BASE           0xC902CD00
#define APB_CCO0_CTRL_BASE           0xC902E000
#define APB_CCO0_CTRL1_BASE          0xC902E100
#define APB_CCO1_CTRL_BASE           0xC9030000
#define APB_CCO1_CTRL1_BASE          0xC9030100
#define APB_CCO2_CTRL_BASE           0xC9033000
#define APB_CCO2_CTRL1_BASE          0xC9033100
#define APB_LED0_CTRL_BASE           0xC9036000
#define APB_LED1_CTRL_BASE           0xC903A000
#define APB_ME0_CTRL_BASE            0xC9044000
#define APB_ME1_CTRL_BASE            0xC904D000
#define APB_FMS_CTRL_BASE            0xC9021000
#define APB_FMC0_CTRL_BASE           0xC903E000
#define APB_FMC1_CTRL_BASE           0xC9041000
#define APB_OBD_CTRL_BASE            0xC9068000
#define APB_CVI_CTRL_BASE            0xC9000000
#define APB_IMX0_CTRL_BASE           0xC9003000
#define APB_IMX0_CTRL1_BASE          0xC9003100
#define APB_IMX1_CTRL_BASE           0xC9007000
#define APB_IMX1_CTRL1_BASE          0xC9007100
#define APB_IMX2_CTRL_BASE           0xC900B000
#define APB_GAV_CTRL_BASE            0xC9009600
#define APB_HDR_CTRL_BASE            0xC9016000
#define APB_HDR_CTRL1_BASE           0xC9018400
#define APB_ND0_CTRL_BASE            0xC900E000
#define APB_ND1_CTRL_BASE            0xC9010000
#define APB_ND2_CTRL_BASE            0xC9012000
#define APB_ND3_CTRL_BASE            0xC9014000
#define APB_SRE_CTRL_BASE            0xC901A000
#define APB_SRE1_CTRL_BASE           0xC901D100
#define APB_VCP_DE_BASE              0xC902A000
#define APB_VCP_DISP_BASE            0xC902A000
#define APB_VCP_BOX_BASE             0xC902A000
#define APB_GSC0_VERI_BASE           0xC9020100
#define APB_GSC1_VERI_BASE           0xC901E100
#define APB_VSD0_VERI_BASE           0xC9029800
#define APB_VSD1_VERI_BASE           0xC902CF00
#define APB_CCO0_VERI_BASE           0xC902E300
#define APB_CCO1_VERI_BASE           0xC9030300
#define APB_CCO2_VERI_BASE           0xC9033300
#define APB_LED0_VERI_BASE           0xC9036200
#define APB_LED1_VERI_BASE           0xC903A200
#define APB_ME0_VERI_BASE            0xC904CC00
#define APB_ME1_VERI_BASE            0xC904D200
#define APB_FMS_VERI_BASE            0xC9021200
#define APB_FMC0_VERI_BASE           0xC903E200
#define APB_FMC1_VERI_BASE           0xC9041200
#define APB_OBD_VERI_BASE            0xC9068200
#define APB_CVI_VERI_BASE            0xC9001000
#define APB_HDR_VERI_BASE            0xC9018500
#define APB_IMX0_VERI_BASE           0xC9003500
#define APB_IMX1_VERI_BASE           0xC9007500
#define APB_ND0_VERI_BASE            0xC900EC00
#define APB_ND1_VERI_BASE            0xC9010C00
#define APB_ND2_VERI_BASE            0xC9012C00
#define APB_ND3_VERI_BASE            0xC9014C00
#define APB_SRE_VERI_BASE            0xC901A200
#define APB_SRE1_VERI_BASE           0xC901D300
#define APB_VSD_OBC_OBJT_BASE         0xC9029300
#define APB_VSD_OBC_FACE_BASE         0xC9029500
#define APB_CSR_BASE                 0xC9029900
#define APB_VSD0_GSR_BASE            0xC9029A00
#define APB_DTM_BASE                 0xC9029C00
#define APB_OBE_BASE                 0xC902B000
#define APB_VSD1_SHP_BASE            0xC902C000
#endif

#define PE_E60_P1_CC_OFST			(0x02E500)
#define PE_E60_P1_CC2_OFST			(0x02F000)

#define PE_E60_CVI_A_OFST			(0x000200)
#define PE_E60_CVI_B_OFST			(0x000300)
#define PE_E60_CVI_C_OFST			(0x000400)
#define PE_E60_CVI_D_OFST			(0x000500)

#define PE_E60_LED_OFST				(0x036400)
#define PE_E60_LED_RP_OFST			(0x036940)
#define PE_E60_LED_DCNT_OFST		(0x03AD00)
#define PE_E60_LED_DCNT1_OFST		(0x03B100)

#define PE_E60_GSC_Y_OFST			(0x020200)
#define PE_E60_GSC_Y_G0_OFST		(0x020200)
#define PE_E60_GSC_Y_G1_OFST		(0x020400)
#define PE_E60_GSC_C_OFST			(0x01E200)
#define PE_E60_GSC_C_G0_OFST		(0x01E200)
#define PE_E60_GSC_C_G1_OFST		(0x01E400)

#define PE_E60_ND0_OFST				(0x00E100)
#define PE_E60_ND1_OFST				(0x010100)
#define PE_E60_ND2_OFST				(0x012100)
#define PE_E60_ND3_OFST				(0x014100)
#define PE_E60_DNR0_OFST			(0x00E500)
#define PE_E60_DNR1_OFST			(0x010500)
#define PE_E60_DNR2_OFST			(0x012500)
#define PE_E60_DNR3_OFST			(0x014500)
#define PE_E60_ND_OBC_O_OFST		(0x00ED00)
#define PE_E60_ND_OBC_F_OFST		(0x00EF00)
#define PE_E60_ND0_VERI_OFST		(0x00EC00)

#define PE_E60_IMX_OFST				(0x0030B8)

#define PE_E60_P1_SHP_OSD0_OFST		(0x033C00)
#define PE_E60_P1_SHP_OSD1_OFST		(0x034400)

#define PE_E60_P1_SHP_L_OFST		(0x02C000)
#define PE_E60_P1_VSD_OBC_O_OFST	(0x029300)
#define PE_E60_P1_VSD_OBC_F_OFST	(0x029500)
//#define PE_E60_P1_VSD_RCE_O_OFST	(0x00B200)
//#define PE_E60_P1_VSD_RCE_F_OFST	(0x00B280)
#define PE_E60_P1_VSD_DTM_OFST	(0x029C00)
#define PE_E60_P1_VSD_OBE_OFST	(0x02B000)

#define PE_E60_VCP_DISP_OFST		(0x02A400)
#define PE_E60_VSD0_VERI_OFST		(0x029800)
#define PE_E60_VSD1_VERI_OFST		(0x02CF00)

#define PE_E60_SR_CHR_SHP_OFST		(0x01D400)
#define PE_E60_SR_4K_SHP_OFST		(0x01B800)
#define PE_E60_SR_2K_SHP_OFST		(0x01AF00)
#define PE_E60_SR_MERG_OFST		    (0x01C900)

#define PE_E60_REG_WRITE_BASE		(0x0)

#if 0	//TODO:
#define PE_E60_HDMI_A_OFST			(0x000100)
#define PE_E60_HDMI_B_OFST			(0x000140)
#define PE_E60_HDMI_C_OFST			(0x000180)
#define PE_E60_HDMI_D_OFST			(0x0001C0)

#define PE_E60_IPP_OFST				(0x014400)

#define PE_E60_VSD_OFST				(0x00B0B0)

#define PE_E60_P1_CCO_EO_DIFF		(PE_E60_P1_CCO_O_OFST - PE_E60_P1_CCO_E_OFST)

#define PE_E60_HDMI_A_BASE			(PE_E60_DE_BASE + PE_E60_HDMI_A_OFST)
#define PE_E60_HDMI_B_BASE			(PE_E60_DE_BASE + PE_E60_HDMI_B_OFST)
#define PE_E60_HDMI_C_BASE			(PE_E60_DE_BASE + PE_E60_HDMI_C_OFST)
#define PE_E60_HDMI_D_BASE			(PE_E60_DE_BASE + PE_E60_HDMI_D_OFST)

#define PE_E60_IPP_BASE				(PE_E60_DE_BASE + PE_E60_IPP_OFST)

#define PE_E60_VSD_BASE				(PE_E60_DE_BASE + PE_E60_VSD_OFST)
#endif

#define PE_E60_P1_CC_BASE		(PE_E60_DE_BASE + PE_E60_P1_CC_OFST)
#define PE_E60_P1_CC2_BASE		(PE_E60_DE_BASE + PE_E60_P1_CC2_OFST)

#define PE_E60_CVI_A_BASE			(PE_E60_DE_BASE + PE_E60_CVI_A_OFST)
#define PE_E60_CVI_B_BASE			(PE_E60_DE_BASE + PE_E60_CVI_B_OFST)
#define PE_E60_CVI_C_BASE			(PE_E60_DE_BASE + PE_E60_CVI_C_OFST)
#define PE_E60_CVI_D_BASE			(PE_E60_DE_BASE + PE_E60_CVI_D_OFST)

#define PE_E60_LED_BASE				(PE_E60_DE_BASE + PE_E60_LED_OFST)
#define PE_E60_LED_RP_BASE			(PE_E60_DE_BASE + PE_E60_LED_RP_OFST)
#define PE_E60_LED_DCNT_BASE		(PE_E60_DE_BASE + PE_E60_LED_DCNT_OFST)
#define PE_E60_LED_DCNT1_BASE		(PE_E60_DE_BASE + PE_E60_LED_DCNT1_OFST)

#define PE_E60_GSC_Y_BASE			(PE_E60_DE_BASE + PE_E60_GSC_Y_OFST)
#define PE_E60_GSC_C_BASE			(PE_E60_DE_BASE + PE_E60_GSC_C_OFST)

#define PE_E60_ND0_BASE				(PE_E60_DE_BASE + PE_E60_ND0_OFST)
#define PE_E60_ND1_BASE				(PE_E60_DE_BASE + PE_E60_ND1_OFST)
#define PE_E60_ND2_BASE				(PE_E60_DE_BASE + PE_E60_ND2_OFST)
#define PE_E60_ND3_BASE				(PE_E60_DE_BASE + PE_E60_ND3_OFST)
#define PE_E60_DNR0_BASE			(PE_E60_DE_BASE + PE_E60_DNR0_OFST)
#define PE_E60_DNR1_BASE			(PE_E60_DE_BASE + PE_E60_DNR1_OFST)
#define PE_E60_DNR2_BASE			(PE_E60_DE_BASE + PE_E60_DNR2_OFST)
#define PE_E60_DNR3_BASE			(PE_E60_DE_BASE + PE_E60_DNR3_OFST)
#define PE_E60_ND_OBC_O_BASE		(PE_E60_DE_BASE + PE_E60_ND_OBC_O_OFST)
#define PE_E60_ND_OBC_F_BASE		(PE_E60_DE_BASE + PE_E60_ND_OBC_F_OFST)
#define PE_E60_ND0_VERI_BASE		(PE_E60_DE_BASE + PE_E60_ND0_VERI_OFST)

#define PE_E60_IMX_BASE				(PE_E60_DE_BASE + PE_E60_IMX_OFST)

#define PE_E60_P1_SHP_OSD0_BASE		(PE_E60_DE_BASE + PE_E60_P1_SHP_OSD0_OFST)
#define PE_E60_P1_SHP_OSD1_BASE		(PE_E60_DE_BASE + PE_E60_P1_SHP_OSD1_OFST)

#define PE_E60_P1_SHP_L_BASE		(PE_E60_DE_BASE + PE_E60_P1_SHP_L_OFST)
#define PE_E60_P1_VSD_OBC_O_BASE	(PE_E60_DE_BASE + PE_E60_P1_VSD_OBC_O_OFST)
#define PE_E60_P1_VSD_OBC_F_BASE	(PE_E60_DE_BASE + PE_E60_P1_VSD_OBC_F_OFST)
//#define PE_E60_P1_VSD_RCE_O_BASE	(PE_E60_DE_BASE + PE_E60_P1_VSD_RCE_O_OFST)
//#define PE_E60_P1_VSD_RCE_F_BASE	(PE_E60_DE_BASE + PE_E60_P1_VSD_RCE_F_OFST)
#define PE_E60_P1_VSD_OBE_BASE		(PE_E60_DE_BASE + PE_E60_P1_VSD_OBE_OFST)
#define PE_E60_P1_VSD_DTM_BASE		(PE_E60_DE_BASE + PE_E60_P1_VSD_DTM_OFST)

#define PE_E60_VCP_DISP_BASE		(PE_E60_DE_BASE + PE_E60_VCP_DISP_OFST)
#define PE_E60_VSD0_VERI_BASE		(PE_E60_DE_BASE + PE_E60_VSD0_VERI_OFST)
#define PE_E60_VSD1_VERI_BASE		(PE_E60_DE_BASE + PE_E60_VSD1_VERI_OFST)

#define PE_E60_SR_CHR_SHP_BASE		(PE_E60_DE_BASE + PE_E60_SR_CHR_SHP_OFST)
#define PE_E60_SR_4K_SHP_BASE		(PE_E60_DE_BASE + PE_E60_SR_4K_SHP_OFST)
#define PE_E60_SR_2K_SHP_BASE		(PE_E60_DE_BASE + PE_E60_SR_2K_SHP_OFST)
#define PE_E60_SR_MERG_BASE			(PE_E60_DE_BASE + PE_E60_SR_MERG_OFST)
#define PE_E60_MCU_BASE				(PE_E60_DE_BASE + 0x260C0)
#define PE_E60_CCO1_VERI_BASE		(PE_E60_DE_BASE + 0x30300)

#define PE_E60_H10_0_BASE			(PE_E60_DE_BASE + 0x016C00)
#define PE_E60_H10_1_BASE			(PE_E60_DE_BASE + 0x017C00)
#define PE_E60_S2H_0_BASE			(PE_E60_DE_BASE + 0x017000)
#define PE_E60_S2H_1_BASE			(PE_E60_DE_BASE + 0x018000)
#define PE_E60_HDR_VERI_BASE		(PE_E60_DE_BASE + 0x018500)

#define PE_E60_DDR_DB0_BASE			(gMemCfgPe[0].db[0].db_base)
#define PE_E60_DDR_DB0_SIZE			(gMemCfgPe[0].db[0].db_size)
#define PE_E60_DDR_DB1_BASE			(gMemCfgPe[0].db[1].db_base)
#define PE_E60_DDR_DB1_SIZE			(gMemCfgPe[0].db[1].db_size)
#define PE_E60_DDR_DB2_BASE			(gMemCfgPe[0].db[2].db_base)
#define PE_E60_DDR_DB2_SIZE			(gMemCfgPe[0].db[2].db_size)
#define PE_E60_DDR_DB3_BASE			(gMemCfgPe[0].db[3].db_base)
#define PE_E60_DDR_DB3_SIZE			(gMemCfgPe[0].db[3].db_size)

#define PE_E60F20_DDR_BASE				(PE_E60_DDR_DB0_BASE + 0x00080000)
#define PE_E60F20_DCM_DDR_BASE			(PE_E60_DDR_DB0_BASE + 0x00100000)

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

#endif	/* _PE_REG_DEF_E60_H_ */

