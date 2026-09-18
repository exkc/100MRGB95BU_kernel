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

/** @file pe_res_hw_param_m17.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_RES_HW_PARAM_M17_H_
#define	_PE_RES_HW_PARAM_M17_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

#include "pe_shp_l_sd_default_m17.h"
#include "pe_shp_l_hd_default_m17.h"
#include "pe_shp_l_ud_default_m17.h"
#include "pe_shp_l_vr_360_default_m17.h"
#include "pe_shp_l_sd_dtv_default_m17.h"
#include "pe_shp_l_hd_dtv_default_m17.h"
#include "pe_sre_res_sd_default_m17.h"
#include "pe_sre_res_hd_default_m17.h"
#include "pe_sre_res_atv_default_m17.h"
#include "pe_sre_res_vr_360_default_m17.h"
#include "pe_sre_res_sd_dtv_default_m17.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/

/**
 *	shp hw param reg type
 */
typedef struct {
	PE_M17_SHP_ESF_CTRL_00_T						 shp_esf_ctrl_00;	//0x00A0
	PE_M17_SHP_ESF_CTRL_01_T						 shp_esf_ctrl_01;	//0x00A4
	PE_M17_SHP_ESF_CTRL_02_T						 shp_esf_ctrl_02;	//0x00A8
	PE_M17_SHP_DERH_CTRL_05_T						 shp_derh_ctrl_05;	//0x00C4
	PE_M17_SHP_DERH_CTRL_06_T						 shp_derh_ctrl_06;	//0x00C8
	PE_M17_SHP_DERH_CTRL_07_T						 shp_derh_ctrl_07;	//0x00CC
	PE_M17_SHP_DERV_CTRL_0_T						 shp_derv_ctrl_0;	//0x00F0
	PE_M17_SHP_DERV_CTRL_1_T						 shp_derv_ctrl_1;	//0x00F4
	PE_M17_SHP_DERV_CTRL_3_T						 shp_derv_ctrl_3;	//0x00FC
	PE_M17_SHP_DP_CTRL_00_T 						 shp_dp_ctrl_00;	//0x0110
	PE_M17_SHP_DP_CTRL_01_T 						 shp_dp_ctrl_01;	//0x0114
	PE_M17_SHP_DP_CTRL_02_T 						 shp_dp_ctrl_02;	//0x0118
	PE_M17_SHP_DP_CTRL_03_T 						 shp_dp_ctrl_03;	//0x011C
	PE_M17_SHP_DP_CTRL_04_T 						 shp_dp_ctrl_04;	//0x0120
	PE_M17_SHP_DP_CTRL_05_T 						 shp_dp_ctrl_05;	//0x0124
	PE_M17_SHP_DP_CTRL_06_T 						 shp_dp_ctrl_06;	//0x0128
	PE_M17_SHP_DP_CTRL_07_T 						 shp_dp_ctrl_07;	//0x012C
	PE_M17_SHP_SP_CTRL_00_T 						 shp_sp_ctrl_00;	//0x0130
	PE_M17_SHP_SP_CTRL_01_T 						 shp_sp_ctrl_01;	//0x0134
	PE_M17_SHP_SP_CTRL_02_T 						 shp_sp_ctrl_02;	//0x0138
	PE_M17_SHP_SP_CTRL_03_T 						 shp_sp_ctrl_03;	//0x013C
	PE_M17_SHP_SP_CTRL_04_T 						 shp_sp_ctrl_04;	//0x0140
	PE_M17_SHP_SP_CTRL_06_T 						 shp_sp_ctrl_06;	//0x0148
	PE_M17_SHP_SP_CTRL_07_T 						 shp_sp_ctrl_07;	//0x014C
	PE_M17_SHP_SP_CTRL_08_T 						 shp_sp_ctrl_08;	//0x0150
	PE_M17_SHP_SP_CTRL_09_T 						 shp_sp_ctrl_09;	//0x0154
	PE_M17_SHP_SP_CTRL_0A_T 						 shp_sp_ctrl_0a;	//0x0158
	PE_M17_SHP_SP_CTRL_0B_T 						 shp_sp_ctrl_0b;	//0x015C
	PE_M17_SHP_SP_CTRL_0C_T 						 shp_sp_ctrl_0c;	//0x0160
	PE_M17_SHP_MP_CTRL_00_T 						 shp_mp_ctrl_00;	//0x0170
	PE_M17_SHP_MP_CTRL_01_T 						 shp_mp_ctrl_01;	//0x0174
	PE_M17_SHP_MP_CTRL_02_T 						 shp_mp_ctrl_02;	//0x0178
	PE_M17_SHP_MP_CTRL_03_T 						 shp_mp_ctrl_03;	//0x017C
	PE_M17_SHP_MP_CTRL_04_T 						 shp_mp_ctrl_04;	//0x0180
	PE_M17_SHP_MP_CTRL_06_T 						 shp_mp_ctrl_06;	//0x0188
	PE_M17_SHP_MP_CTRL_07_T 						 shp_mp_ctrl_07;	//0x018C
	PE_M17_SHP_MP_CTRL_08_T 						 shp_mp_ctrl_08;	//0x0190
	PE_M17_SHP_MP_CTRL_09_T 						 shp_mp_ctrl_09;	//0x0194
	PE_M17_SHP_MP_CTRL_0A_T 						 shp_mp_ctrl_0a;	//0x0198
	PE_M17_SHP_MP_CTRL_0B_T 						 shp_mp_ctrl_0b;	//0x019C
	PE_M17_SHP_MP_CTRL_0C_T 						 shp_mp_ctrl_0c;	//0x01A0
	PE_M17_SHP_CORING_CTRL_00_T 					 shp_coring_ctrl_00;	//0x01B0
	PE_M17_SHP_CORING_CTRL_01_T 					 shp_coring_ctrl_01;	//0x01B4
	PE_M17_SHP_CORING_CTRL_02_T 					 shp_coring_ctrl_02;	//0x01B8
	PE_M17_SHP_CORING_CTRL_03_T 					 shp_coring_ctrl_03;	//0x01BC
	PE_M17_SHP_CORING_CTRL_04_T 					 shp_coring_ctrl_04;	//0x01C0
	PE_M17_SHP_CORING_CTRL_05_T 					 shp_coring_ctrl_05;	//0x01C4
	PE_M17_SHP_CORING_CTRL_06_T 					 shp_coring_ctrl_06;	//0x01C8
	PE_M17_SHP_CORING_CTRL_07_T 					 shp_coring_ctrl_07;	//0x01CC
	PE_M17_SHP_CORING_CTRL_08_T 					 shp_coring_ctrl_08;	//0x01D0
	PE_M17_SHP_CORING_CTRL_09_T 					 shp_coring_ctrl_09;	//0x01D4
	PE_M17_SHP_PTI_CTRL_00_T						 shp_pti_ctrl_00;	//0x0200
	PE_M17_SHP_PTI_CTRL_01_T						 shp_pti_ctrl_01;	//0x0204
	PE_M17_SHP_STI_CTRL_00_T						 shp_sti_ctrl_00;	//0x0208
	PE_M17_SHP_PSP_CTRL_00_T						 shp_psp_ctrl_00;	//0x0210
	PE_M17_SHP_DJ_CTRL_00_T 						 shp_dj_ctrl_00;	//0x0220
	PE_M17_SHP_DJ_CTRL_01_T 						 shp_dj_ctrl_01;	//0x0224
	PE_M17_SHP_DJ_CTRL_02_T 						 shp_dj_ctrl_02;	//0x0228
	PE_M17_SHP_DJ_CTRL_03_T 						 shp_dj_ctrl_03;	//0x022C
	PE_M17_SHP_SQM_CTRL_00_T						 shp_sqm_ctrl_00;	//0x0260
	PE_M17_SHP_SQM_CTRL_01_T						 shp_sqm_ctrl_01;	//0x0264
	PE_M17_SHP_SQM_CTRL_02_T						 shp_sqm_ctrl_02;	//0x0268
	PE_M17_SHP_SQM_CTRL_03_T						 shp_sqm_ctrl_03;	//0x026C
	PE_M17_SHP_SQM_CTRL_04_T						 shp_sqm_ctrl_04;	//0x0270
	PE_M17_SHP_SQM_CTRL_05_T                         shp_sqm_ctrl_05;	//0x0274
	PE_M17_SHP_CONTRAST_CTRL_00_T                    shp_contrast_ctrl_00;	//0x02C8
	PE_M17_SHP_CONTRAST_CTRL_01_T                    shp_contrast_ctrl_01;	//0x02CC
	PE_M17_SHP_CONTRAST_CTRL_02_T                    shp_contrast_ctrl_02;	//0x02D0
	PE_M17_SHP_CONTRAST_CTRL_03_T                    shp_contrast_ctrl_03;	//0x02D4
	PE_M17_SHP_CONTRAST_CTRL_04_T                    shp_contrast_ctrl_04;	//0x02D8
	PE_M17_SHP_MNR_CTRL_00_T                         shp_mnr_ctrl_00;	//0x02DC
	PE_M17_SHP_MNR_CTRL_01_T                         shp_mnr_ctrl_01;	//0x02E0
	PE_M17_SHP_MNR_CTRL_02_T                         shp_mnr_ctrl_02;	//0x02E4
	PE_M17_SHP_CHROMA_CTRL_00_T                      shp_chroma_ctrl_00;	//0x0400
	PE_M17_SHP_CHROMA_CTRL_01_T                      shp_chroma_ctrl_01;	//0x0404
	PE_M17_SHP_CHROMA_CTRL_02_T                      shp_chroma_ctrl_02;	//0x0408
	PE_M17_SHP_CHROMA_CTRL_03_T                      shp_chroma_ctrl_03;	//0x040C
	PE_M17_SHP_CHROMA_CTRL_04_T                      shp_chroma_ctrl_04;	//0x0410
	PE_M17_SHP_CHROMA_CTRL_05_T                      shp_chroma_ctrl_05;	//0x0414
	PE_M17_SHP_CHROMA_CTRL_06_T                      shp_chroma_ctrl_06;	//0x0418
	PE_M17_SHP_CHROMA_CTRL_07_T                      shp_chroma_ctrl_07;	//0x041C
	PE_M17_SHP_CHROMA_CTRL_08_T                      shp_chroma_ctrl_08;	//0x0420
	PE_M17_SHP_CHROMA_CTRL_09_T                      shp_chroma_ctrl_09;	//0x0424
	PE_M17_SHP_CHROMA_CTRL_0A_T                      shp_chroma_ctrl_0a;	//0x0428
	PE_M17_SHP_CHROMA_CTRL_0B_T                      shp_chroma_ctrl_0b;	//0x042C
	PE_M17_SHP_CHROMA_CTRL_0C_T                      shp_chroma_ctrl_0c;	//0x0430
	PE_M17_SHP_CHROMA_CTRL_0D_T                      shp_chroma_ctrl_0d;	//0x0434
	PE_M17_SHP_MOTION_CTRL_00_T                      shp_motion_ctrl_00;	//0x0440
	PE_M17_SHP_MOTION_CTRL_01_T                      shp_motion_ctrl_01;	//0x0444
	PE_M17_SHP_MOTION_CTRL_02_T                      shp_motion_ctrl_02;	//0x0448
	PE_M17_MOTION_GAIN_CTRL_00_T                     motion_gain_ctrl_00;	//0x0500
	PE_M17_MOTION_GAIN_CTRL_01_T                     motion_gain_ctrl_01;	//0x0504
	PE_M17_MOTION_GAIN_CTRL_02_T                     motion_gain_ctrl_02;	//0x0508
	PE_M17_MOTION_GAIN_CTRL_03_T                     motion_gain_ctrl_03;	//0x050C
	PE_M17_MOTION_GAIN_CTRL_04_T                     motion_gain_ctrl_04;	//0x0510
	PE_M17_MOTION_GAIN_CTRL_05_T                     motion_gain_ctrl_05;	//0x0514
	PE_M17_MOTION_GAIN_CTRL_06_T                     motion_gain_ctrl_06;	//0x0518
	PE_M17_MOTION_GAIN_CTRL_07_T                     motion_gain_ctrl_07;	//0x051C
	PE_M17_MOTION_GAIN_CTRL_08_T                     motion_gain_ctrl_08;	//0x0520
	PE_M17_MOTION_GAIN_CTRL_09_T                     motion_gain_ctrl_09;	//0x0524
	PE_M17_MOTION_GAIN_CTRL_0A_T                     motion_gain_ctrl_0a;	//0x0528
}PE_RES_HW_PARAM_REG_M17_T;

/**
 *	sre shp(srs) hw param reg type
 */
typedef struct {
	PE_M17_SR_SHP_DERH_CTRL_05_T                     shp_derh_ctrl_05;	//0x00C4
	PE_M17_SR_SHP_DERH_CTRL_06_T                     shp_derh_ctrl_06;	//0x00C8
	PE_M17_SR_SHP_DERH_CTRL_07_T                     shp_derh_ctrl_07;	//0x00CC
	PE_M17_SR_SHP_DERV_CTRL_0_T                      shp_derv_ctrl_0;	//0x00F0
	PE_M17_SR_SHP_DERV_CTRL_1_T                      shp_derv_ctrl_1;	//0x00F4
	PE_M17_SR_SHP_DERV_CTRL_3_T                      shp_derv_ctrl_3;	//0x00FC
	PE_M17_SR_SHP_DP_CTRL_00_T                       shp_dp_ctrl_00;	//0x0110
	PE_M17_SR_SHP_DP_CTRL_01_T                       shp_dp_ctrl_01;	//0x0114
	PE_M17_SR_SHP_DP_CTRL_02_T                       shp_dp_ctrl_02;	//0x0118
	PE_M17_SR_SHP_DP_CTRL_03_T                       shp_dp_ctrl_03;	//0x011C
	PE_M17_SR_SHP_DP_CTRL_04_T                       shp_dp_ctrl_04;	//0x0120
	PE_M17_SR_SHP_DP_CTRL_05_T                       shp_dp_ctrl_05;	//0x0124
	PE_M17_SR_SHP_DP_CTRL_06_T                       shp_dp_ctrl_06;	//0x0128
	PE_M17_SR_SHP_DP_CTRL_07_T                       shp_dp_ctrl_07;	//0x012C
	PE_M17_SR_SHP_SP_CTRL_00_T                       shp_sp_ctrl_00;	//0x0130
	PE_M17_SR_SHP_SP_CTRL_01_T                       shp_sp_ctrl_01;	//0x0134
	PE_M17_SR_SHP_SP_CTRL_02_T                       shp_sp_ctrl_02;	//0x0138
	PE_M17_SR_SHP_SP_CTRL_03_T                       shp_sp_ctrl_03;	//0x013C
	PE_M17_SR_SHP_SP_CTRL_04_T                       shp_sp_ctrl_04;	//0x0140
	PE_M17_SR_SHP_SP_CTRL_06_T                       shp_sp_ctrl_06;	//0x0148
	PE_M17_SR_SHP_SP_CTRL_07_T                       shp_sp_ctrl_07;	//0x014C
	PE_M17_SR_SHP_SP_CTRL_08_T                       shp_sp_ctrl_08;	//0x0150
	PE_M17_SR_SHP_SP_CTRL_09_T                       shp_sp_ctrl_09;	//0x0154
	PE_M17_SR_SHP_SP_CTRL_0A_T                       shp_sp_ctrl_0a;	//0x0158
	PE_M17_SR_SHP_SP_CTRL_0B_T                       shp_sp_ctrl_0b;	//0x015C
	PE_M17_SR_SHP_SP_CTRL_0C_T                       shp_sp_ctrl_0c;	//0x0160
	PE_M17_SR_SHP_MP_CTRL_00_T                       shp_mp_ctrl_00;	//0x0170
	PE_M17_SR_SHP_MP_CTRL_01_T                       shp_mp_ctrl_01;	//0x0174
	PE_M17_SR_SHP_MP_CTRL_02_T                       shp_mp_ctrl_02;	//0x0178
	PE_M17_SR_SHP_MP_CTRL_03_T                       shp_mp_ctrl_03;	//0x017C
	PE_M17_SR_SHP_MP_CTRL_04_T                       shp_mp_ctrl_04;	//0x0180
	PE_M17_SR_SHP_MP_CTRL_06_T                       shp_mp_ctrl_06;	//0x0188
	PE_M17_SR_SHP_MP_CTRL_07_T                       shp_mp_ctrl_07;	//0x018C
	PE_M17_SR_SHP_MP_CTRL_08_T                       shp_mp_ctrl_08;	//0x0190
	PE_M17_SR_SHP_MP_CTRL_09_T                       shp_mp_ctrl_09;	//0x0194
	PE_M17_SR_SHP_MP_CTRL_0A_T                       shp_mp_ctrl_0a;	//0x0198
	PE_M17_SR_SHP_MP_CTRL_0B_T                       shp_mp_ctrl_0b;	//0x019C
	PE_M17_SR_SHP_MP_CTRL_0C_T                       shp_mp_ctrl_0c;	//0x01A0
	PE_M17_SR_SHP_CORING_CTRL_00_T                   shp_coring_ctrl_00;	//0x01B0
	PE_M17_SR_SHP_CORING_CTRL_01_T                   shp_coring_ctrl_01;	//0x01B4
	PE_M17_SR_SHP_CORING_CTRL_02_T                   shp_coring_ctrl_02;	//0x01B8
	PE_M17_SR_SHP_CORING_CTRL_03_T                   shp_coring_ctrl_03;	//0x01BC
	PE_M17_SR_SHP_CORING_CTRL_04_T                   shp_coring_ctrl_04;	//0x01C0
	PE_M17_SR_SHP_CORING_CTRL_05_T                   shp_coring_ctrl_05;	//0x01C4
	PE_M17_SR_SHP_CORING_CTRL_06_T                   shp_coring_ctrl_06;	//0x01C8
	PE_M17_SR_SHP_CORING_CTRL_07_T                   shp_coring_ctrl_07;	//0x01CC
	PE_M17_SR_SHP_CORING_CTRL_08_T                   shp_coring_ctrl_08;	//0x01D0
	PE_M17_SR_SHP_CORING_CTRL_09_T                   shp_coring_ctrl_09;	//0x01D4
	PE_M17_SR_SHP_PTI_CTRL_00_T                      shp_pti_ctrl_00;	//0x0200
	PE_M17_SR_SHP_PTI_CTRL_01_T                      shp_pti_ctrl_01;	//0x0204
	PE_M17_SR_SHP_STI_CTRL_00_T                      shp_sti_ctrl_00;	//0x0208
	PE_M17_SR_SHP_DJ_CTRL_00_T                       shp_dj_ctrl_00;	//0x0220
	PE_M17_SR_SHP_DJ_CTRL_01_T                       shp_dj_ctrl_01;	//0x0224
	PE_M17_SR_SHP_DJ_CTRL_02_T                       shp_dj_ctrl_02;	//0x0228
	PE_M17_SR_SHP_DJ_CTRL_03_T                       shp_dj_ctrl_03;	//0x022C
	PE_M17_SR_SHP_SQM_CTRL_00_T                      shp_sqm_ctrl_00;	//0x0260
	PE_M17_SR_SHP_SQM_CTRL_01_T                      shp_sqm_ctrl_01;	//0x0264
	PE_M17_SR_SHP_SQM_CTRL_02_T                      shp_sqm_ctrl_02;	//0x0268
	PE_M17_SR_SHP_SQM_CTRL_03_T                      shp_sqm_ctrl_03;	//0x026C
	PE_M17_SR_SHP_SQM_CTRL_04_T                      shp_sqm_ctrl_04;	//0x0270
	PE_M17_SR_SHP_SQM_CTRL_05_T                      shp_sqm_ctrl_05;	//0x0274
	PE_M17_SR_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0x02A0
	PE_M17_SR_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0x02A4
	PE_M17_SR_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0x02A8
	PE_M17_SR_SHP_TGEN_CTRL_03_T                     shp_tgen_ctrl_03;	//0x02AC
	PE_M17_SR_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0x02B0
	PE_M17_SR_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0x02B4
	PE_M17_SR_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0x02B8
	PE_M17_SR_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0x02BC
	PE_M17_SR_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0x02C0
	PE_M17_SR_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0x02C4
	PE_M17_SR_SHP_CONTRAST_CTRL_00_T                 shp_contrast_ctrl_00;	//0x02C8
	PE_M17_SR_SHP_CONTRAST_CTRL_01_T                 shp_contrast_ctrl_01;	//0x02CC
	PE_M17_SR_SHP_CONTRAST_CTRL_02_T                 shp_contrast_ctrl_02;	//0x02D0
	PE_M17_SR_SHP_CONTRAST_CTRL_03_T                 shp_contrast_ctrl_03;	//0x02D4
	PE_M17_SR_SHP_CONTRAST_CTRL_04_T                 shp_contrast_ctrl_04;	//0x02D8
	PE_M17_SR_SHP_MNR_CTRL_00_T                      shp_mnr_ctrl_00;	//0x02DC
	PE_M17_SR_SHP_MNR_CTRL_01_T                      shp_mnr_ctrl_01;	//0x02E0
	PE_M17_SR_SHP_MNR_CTRL_02_T                      shp_mnr_ctrl_02;	//0x02E4
}PE_SRS_HW_PARAM_REG_M17_T;


/**
 *	shp hw param reg type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_M17_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_M17_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_M17_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_M17_T *data;
	} reg_data;
} PE_RES_HW_PARAM_DATA_M17_T;

/**
 *	sre shp(srs) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_SRS_HW_PARAM_REG_M17_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_SRS_HW_PARAM_REG_M17_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_SRS_HW_PARAM_REG_M17_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_SRS_HW_PARAM_REG_M17_T *data;
	} reg_data;
} PE_SRS_HW_PARAM_DATA_M17_T;

/**
 *	sre hw param reg type
 */

/**
 *	shp hw param data type
 */
/**
 *	sre shp(srs) hw param data type
 */
/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_RES_HW_PARAM_M17_H_ */

