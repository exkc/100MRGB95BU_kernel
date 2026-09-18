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

/** @file pe_res_hw_param_o20.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_RES_HW_PARAM_O20_H_
#define	_PE_RES_HW_PARAM_O20_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

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
#ifdef PE_HW_O20_BRINGUP
	PE_O20_SHP_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_O20_SHP_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_O20_SHP_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	PE_O20_SHP_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_O20_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O20_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O20_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O20_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O20_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O20_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O20_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O20_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O20_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O20_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O20_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O20_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O20_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O20_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O20_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O20_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O20_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O20_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O20_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_O20_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O20_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O20_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O20_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_O20_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O20_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O20_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O20_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O20_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O20_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O20_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O20_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O20_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O20_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O20_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O20_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O20_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O20_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_O20_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O20_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O20_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O20_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O20_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_O20_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O20_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O20_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O20_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O20_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O20_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O20_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O20_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O20_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O20_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O20_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O20_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O20_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O20_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O20_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O20_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O20_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O20_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O20_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O20_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O20_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_O20_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O20_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O20_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O20_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O20_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_O20_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O20_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O20_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O20_SHP_TGEN_CTRL_03_C0_T                      shp_core0_tgen_ctrl_03;	//0x024C
	PE_O20_SHP_TGEN_CTRL_03_C1_T                      shp_core1_tgen_ctrl_03;	//0x0250
	PE_O20_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O20_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O20_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O20_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O20_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O20_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O20_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O20_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O20_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_O20_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O20_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O20_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O20_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O20_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O20_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O20_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O20_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O20_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O20_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O20_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O20_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O20_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O20_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O20_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O20_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O20_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O20_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O20_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O20_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O20_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O20_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O20_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O20_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O20_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O20_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O20_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O20_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O20_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O20_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O20_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O20_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O20_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O20_SHP_NNTG_CTRL_01_C0_T                      shp_core0_nntg_ctrl_01;	//0x0304
	PE_O20_SHP_NNTG_CTRL_02_C0_T                      shp_core0_nntg_ctrl_02;	//0x0308
	PE_O20_SHP_NNTG_CTRL_03_C0_T                      shp_core0_nntg_ctrl_03;	//0x030C
	PE_O20_SHP_NNTG_CTRL_04_C0_T                      shp_core0_nntg_ctrl_04;	//0x0310
	PE_O20_SHP_NNTG_CTRL_05_C0_T                      shp_core0_nntg_ctrl_05;	//0x0314
	PE_O20_SHP_NNTG_CTRL_01_C1_T                      shp_core1_nntg_ctrl_01;	//0x0318
	PE_O20_SHP_NNTG_CTRL_02_C1_T                      shp_core1_nntg_ctrl_02;	//0x031C
	PE_O20_SHP_NNTG_CTRL_03_C1_T                      shp_core1_nntg_ctrl_03;	//0x0320
	PE_O20_SHP_NNTG_CTRL_04_C1_T                      shp_core1_nntg_ctrl_04;	//0x0324
	PE_O20_SHP_NNTG_CTRL_05_C1_T                      shp_core1_nntg_ctrl_05;	//0x0328
	PE_O20_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O20_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O20_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O20_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O20_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O20_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O20_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O20_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O20_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O20_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O20_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_O20_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O20_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O20_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_O20_SHP_DP_SUM_CTRL_03_T                       shp_dp_sum_ctrl_03;	//0x036C
	PE_O20_SHP_DP_SUM_CTRL_04_T                       shp_dp_sum_ctrl_04;	//0x0370
	PE_O20_SHP_DP_SUM_CTRL_05_T                       shp_dp_sum_ctrl_05;	//0x0374
	PE_O20_SHP_DP_SUM_CTRL_06_T                       shp_dp_sum_ctrl_06;	//0x0378
	PE_O20_SHP_DP_SUM_CTRL_07_T                       shp_dp_sum_ctrl_07;	//0x037C
	PE_O20_SHP_DP_SUM_CTRL_08_T                       shp_dp_sum_ctrl_08;	//0x0380
	PE_O20_SHP_PSP_CTRL_00_T                          shp_psp_ctrl_00;	    //0x0390
	PE_O20_SHP_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O20_SHP_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x03C4
	PE_O20_SHP_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x03C8
	PE_O20_SHP_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O20_SHP_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x03D0
	PE_O20_SHP_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x03D4
	PE_O20_SHP_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x03D8
	PE_O20_SHP_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x03DC
	PE_O20_SHP_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x03E0
	PE_O20_SHP_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x03E4
	PE_O20_SHP_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x03E8
	PE_O20_SHP_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x03EC
	PE_O20_SHP_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O20_SHP_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O20_SHP_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O20_SHP_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O20_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O20_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O20_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O20_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O20_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O20_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O20_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O20_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O20_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O20_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O20_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O20_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O20_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O20_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O20_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O20_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O20_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O20_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O20_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O20_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O20_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O20_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O20_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O20_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O20_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O20_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O20_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O20_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O20_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O20_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O20_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O20_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O20_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	PE_O20_SHP_DB_CTRL_00_T                           shp_db_ctrl_00;	//0x0490
	PE_O20_SHP_DB_CTRL_01_T                           shp_db_ctrl_01;	//0x0494
	PE_O20_SHP_CHROMA_CTRL_00_T                       shp_chroma_ctrl_00;	//0x0500
	PE_O20_SHP_CHROMA_CTRL_01_T                       shp_chroma_ctrl_01;	//0x0504
	PE_O20_SHP_CHROMA_CTRL_02_T                       shp_chroma_ctrl_02;	//0x0508
	PE_O20_SHP_CHROMA_CTRL_03_T                       shp_chroma_ctrl_03;	//0x050C
	PE_O20_SHP_CHROMA_CTRL_04_T                       shp_chroma_ctrl_04;	//0x0510
	PE_O20_SHP_CHROMA_CTRL_05_T                       shp_chroma_ctrl_05;	//0x0514
	PE_O20_SHP_CHROMA_CTRL_06_T                       shp_chroma_ctrl_06;	//0x0518
	PE_O20_SHP_CHROMA_CTRL_07_T                       shp_chroma_ctrl_07;	//0x051C
	PE_O20_SHP_CHROMA_CTRL_08_T                       shp_chroma_ctrl_08;	//0x0520
	PE_O20_SHP_CHROMA_CTRL_09_T                       shp_chroma_ctrl_09;	//0x0524
	PE_O20_SHP_CHROMA_CTRL_0A_T                       shp_chroma_ctrl_0a;	//0x0528
	PE_O20_SHP_CHROMA_CTRL_0B_T                       shp_chroma_ctrl_0b;	//0x052C
	PE_O20_SHP_CHROMA_CTRL_0C_T                       shp_chroma_ctrl_0c;	//0x0530
	PE_O20_SHP_CHROMA_CTRL_0D_T                       shp_chroma_ctrl_0d;	//0x0534
	PE_O20_SHP_CHROMA_CTRL_0E_T                       shp_chroma_ctrl_0e;	//0x0538
	PE_O20_SHP_FRC_FLICK_CTRL_00_T                    shp_frc_flick_ctrl_00;	//0x0560
	PE_O20_SHP_FRC_FLICK_CTRL_01_T                    shp_frc_flick_ctrl_01;	//0x0564
	PE_O20_SHP_FRC_FLICK_CTRL_02_T                    shp_frc_flick_ctrl_02;	//0x0568
	PE_O20_SHP_FRC_FLICK_CTRL_03_T                    shp_frc_flick_ctrl_03;	//0x056C
	PE_O20_SHP_MOTION_GAIN_CTRL_00_T                  shp_motion_gain_ctrl_00;	//0x0600
	PE_O20_SHP_MOTION_GAIN_CTRL_01_T                  shp_motion_gain_ctrl_01;	//0x0604
	PE_O20_SHP_MOTION_GAIN_CTRL_02_T                  shp_motion_gain_ctrl_02;	//0x0608
	PE_O20_SHP_MOTION_GAIN_CTRL_03_T                  shp_motion_gain_ctrl_03;	//0x060C
	PE_O20_SHP_MOTION_GAIN_CTRL_04_T                  shp_motion_gain_ctrl_04;	//0x0610
	PE_O20_SHP_MOTION_GAIN_CTRL_05_T                  shp_motion_gain_ctrl_05;	//0x0614
	PE_O20_SHP_MOTION_GAIN_CTRL_06_T                  shp_motion_gain_ctrl_06;	//0x0618
	PE_O20_SHP_MOTION_GAIN_CTRL_07_T                  shp_motion_gain_ctrl_07;	//0x061C
	PE_O20_SHP_MOTION_GAIN_CTRL_08_T                  shp_motion_gain_ctrl_08;	//0x0620
	PE_O20_SHP_MOTION_GAIN_CTRL_09_T                  shp_motion_gain_ctrl_09;	//0x0624
	PE_O20_SHP_MOTION_GAIN_CTRL_0A_T                  shp_motion_gain_ctrl_0a;	//0x0628
	PE_O20_SHP_MOTION_GAIN_CTRL_0B_T                  shp_motion_gain_ctrl_0b;	//0x062C
	PE_O20_SHP_MOTION_GAIN_CTRL_0C_T                  shp_motion_gain_ctrl_0c;	//0x0630
	PE_O20_SHP_MOTION_PROT_CTRL_00_T                  shp_motion_prot_ctrl_00;	//0x0640
	PE_O20_SHP_MOTION_PROT_CTRL_01_T                  shp_motion_prot_ctrl_01;	//0x0644
	PE_O20_SHP_MOTION_PROT_CTRL_02_T                  shp_motion_prot_ctrl_02;	//0x0648
	PE_O20_SHP_MOTION_PROT_CTRL_03_T                  shp_motion_prot_ctrl_03;	//0x064C
	PE_O20_SHP_MOTION_PROT_CTRL_04_T                  shp_motion_prot_ctrl_04;	//0x0650
	PE_O20_SHP_OBJ_CTRL_00_T                          shp_obj_ctrl_00;	//0x0690
	PE_O20_SHP_OBJ_CTRL_01_T                          shp_obj_ctrl_01;	//0x0694
	PE_O20_SHP_OBJ_CTRL_02_T                          shp_obj_ctrl_02;	//0x0698
	PE_O20_SHP_OBJ_CTRL_03_T                          shp_obj_ctrl_03;	//0x069C
	PE_O20_SHP_OBJ_CTRL_04_T                          shp_obj_ctrl_04;	//0x06A0
	PE_O20_SHP_OBJ_CTRL_05_T                          shp_obj_ctrl_05;	//0x06A4
	PE_O20_SHP_OBJ_CTRL_06_T                          shp_obj_ctrl_06;	//0x06A8
	PE_O20_SHP_OBJ_CTRL_07_T                          shp_obj_ctrl_07;	//0x06AC
	PE_O20_SHP_OBJ_CTRL_08_T                          shp_obj_ctrl_08;	//0x06B0
	PE_O20_SHP_OBJ_CTRL_09_T                          shp_obj_ctrl_09;	//0x06B4
	PE_O20_SHP_OBJ_CTRL_0A_T                          shp_obj_ctrl_0a;	//0x06B8
	#endif
}PE_RES_HW_PARAM_REG_O20_T;

/**
 *	sre shp(srs) hw param reg type
 */
typedef struct {
#ifndef PE_HW_O20_BRINGUP
	PE_O20_SHP_4K_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_O20_SHP_4K_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_O20_SHP_4K_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	PE_O20_SHP_4K_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_O20_SHP_4K_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O20_SHP_4K_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O20_SHP_4K_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O20_SHP_4K_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O20_SHP_4K_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O20_SHP_4K_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O20_SHP_4K_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O20_SHP_4K_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O20_SHP_4K_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O20_SHP_4K_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O20_SHP_4K_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O20_SHP_4K_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O20_SHP_4K_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O20_SHP_4K_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O20_SHP_4K_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O20_SHP_4K_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O20_SHP_4K_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O20_SHP_4K_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O20_SHP_4K_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_O20_SHP_4K_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O20_SHP_4K_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O20_SHP_4K_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O20_SHP_4K_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O20_SHP_4K_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O20_SHP_4K_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O20_SHP_4K_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O20_SHP_4K_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O20_SHP_4K_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O20_SHP_4K_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O20_SHP_4K_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O20_SHP_4K_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O20_SHP_4K_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O20_SHP_4K_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O20_SHP_4K_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O20_SHP_4K_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O20_SHP_4K_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O20_SHP_4K_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_O20_SHP_4K_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O20_SHP_4K_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O20_SHP_4K_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O20_SHP_4K_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O20_SHP_4K_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O20_SHP_4K_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O20_SHP_4K_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O20_SHP_4K_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O20_SHP_4K_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O20_SHP_4K_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O20_SHP_4K_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O20_SHP_4K_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O20_SHP_4K_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O20_SHP_4K_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O20_SHP_4K_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O20_SHP_4K_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O20_SHP_4K_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O20_SHP_4K_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O20_SHP_4K_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O20_SHP_4K_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O20_SHP_4K_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_O20_SHP_4K_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O20_SHP_4K_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O20_SHP_4K_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O20_SHP_4K_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O20_SHP_4K_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_O20_SHP_4K_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O20_SHP_4K_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O20_SHP_4K_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O20_SHP_4K_CORE0_TGEN_CTRL_03_T                   shp_core0_tgen_ctrl_03;	//0x024C
	PE_O20_SHP_4K_CORE1_TGEN_CTRL_03_T                   shp_core1_tgen_ctrl_03;	//0x0250
	PE_O20_SHP_4K_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O20_SHP_4K_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O20_SHP_4K_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O20_SHP_4K_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O20_SHP_4K_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O20_SHP_4K_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O20_SHP_4K_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O20_SHP_4K_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O20_SHP_4K_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_O20_SHP_4K_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O20_SHP_4K_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O20_SHP_4K_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O20_SHP_4K_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O20_SHP_4K_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O20_SHP_4K_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O20_SHP_4K_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O20_SHP_4K_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O20_SHP_4K_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O20_SHP_4K_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O20_SHP_4K_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O20_SHP_4K_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O20_SHP_4K_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O20_SHP_4K_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O20_SHP_4K_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O20_SHP_4K_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O20_SHP_4K_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O20_SHP_4K_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O20_SHP_4K_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O20_SHP_4K_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O20_SHP_4K_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O20_SHP_4K_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O20_SHP_4K_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O20_SHP_4K_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O20_SHP_4K_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O20_SHP_4K_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O20_SHP_4K_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O20_SHP_4K_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O20_SHP_4K_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O20_SHP_4K_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O20_SHP_4K_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O20_SHP_4K_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O20_SHP_4K_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O20_SHP_4K_CORE0_NNTG_CTRL_01_T                   shp_core0_nntg_ctrl_01;	//0x0304
	PE_O20_SHP_4K_CORE0_NNTG_CTRL_02_T                   shp_core0_nntg_ctrl_02;	//0x0308
	PE_O20_SHP_4K_CORE0_NNTG_CTRL_03_T                   shp_core0_nntg_ctrl_03;	//0x030C
	PE_O20_SHP_4K_CORE0_NNTG_CTRL_04_T                   shp_core0_nntg_ctrl_04;	//0x0310
	PE_O20_SHP_4K_CORE0_NNTG_CTRL_05_T                   shp_core0_nntg_ctrl_05;	//0x0314
	PE_O20_SHP_4K_CORE1_NNTG_CTRL_01_T                   shp_core1_nntg_ctrl_01;	//0x0318
	PE_O20_SHP_4K_CORE1_NNTG_CTRL_02_T                   shp_core1_nntg_ctrl_02;	//0x031C
	PE_O20_SHP_4K_CORE1_NNTG_CTRL_03_T                   shp_core1_nntg_ctrl_03;	//0x0320
	PE_O20_SHP_4K_CORE1_NNTG_CTRL_04_T                   shp_core1_nntg_ctrl_04;	//0x0324
	PE_O20_SHP_4K_CORE1_NNTG_CTRL_05_T                   shp_core1_nntg_ctrl_05;	//0x0328
	PE_O20_SHP_4K_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O20_SHP_4K_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O20_SHP_4K_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O20_SHP_4K_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O20_SHP_4K_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O20_SHP_4K_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O20_SHP_4K_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O20_SHP_4K_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O20_SHP_4K_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O20_SHP_4K_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O20_SHP_4K_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_O20_SHP_4K_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	#endif
}PE_SRS_HW_PARAM_REG_O20_T;

/**
 *	sre 2k shp(srs) hw param reg type
 */
typedef struct {
	PE_O20_SHP_2K_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_O20_SHP_2K_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O20_SHP_2K_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O20_SHP_2K_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O20_SHP_2K_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O20_SHP_2K_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O20_SHP_2K_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O20_SHP_2K_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O20_SHP_2K_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O20_SHP_2K_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O20_SHP_2K_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O20_SHP_2K_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O20_SHP_2K_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O20_SHP_2K_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O20_SHP_2K_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O20_SHP_2K_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O20_SHP_2K_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O20_SHP_2K_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O20_SHP_2K_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O20_SHP_2K_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_O20_SHP_2K_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O20_SHP_2K_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O20_SHP_2K_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O20_SHP_2K_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_O20_SHP_2K_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O20_SHP_2K_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O20_SHP_2K_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O20_SHP_2K_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O20_SHP_2K_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O20_SHP_2K_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O20_SHP_2K_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O20_SHP_2K_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O20_SHP_2K_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O20_SHP_2K_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O20_SHP_2K_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O20_SHP_2K_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O20_SHP_2K_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O20_SHP_2K_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_O20_SHP_2K_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O20_SHP_2K_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O20_SHP_2K_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O20_SHP_2K_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O20_SHP_2K_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_O20_SHP_2K_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O20_SHP_2K_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O20_SHP_2K_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O20_SHP_2K_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O20_SHP_2K_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O20_SHP_2K_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O20_SHP_2K_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O20_SHP_2K_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O20_SHP_2K_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O20_SHP_2K_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O20_SHP_2K_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O20_SHP_2K_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O20_SHP_2K_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O20_SHP_2K_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O20_SHP_2K_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O20_SHP_2K_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O20_SHP_2K_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O20_SHP_2K_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O20_SHP_2K_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O20_SHP_2K_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O20_SHP_2K_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_O20_SHP_2K_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O20_SHP_2K_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O20_SHP_2K_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O20_SHP_2K_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O20_SHP_2K_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_O20_SHP_2K_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O20_SHP_2K_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O20_SHP_2K_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O20_SHP_2K_TGEN_CTRL_03_T                         shp_tgen_ctrl_03;	//0x024C
	PE_O20_SHP_2K_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O20_SHP_2K_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O20_SHP_2K_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O20_SHP_2K_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O20_SHP_2K_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O20_SHP_2K_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O20_SHP_2K_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O20_SHP_2K_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O20_SHP_2K_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_O20_SHP_2K_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O20_SHP_2K_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O20_SHP_2K_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O20_SHP_2K_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O20_SHP_2K_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O20_SHP_2K_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O20_SHP_2K_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O20_SHP_2K_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O20_SHP_2K_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O20_SHP_2K_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O20_SHP_2K_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O20_SHP_2K_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O20_SHP_2K_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O20_SHP_2K_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O20_SHP_2K_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O20_SHP_2K_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O20_SHP_2K_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O20_SHP_2K_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O20_SHP_2K_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O20_SHP_2K_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O20_SHP_2K_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O20_SHP_2K_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O20_SHP_2K_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O20_SHP_2K_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O20_SHP_2K_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O20_SHP_2K_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O20_SHP_2K_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O20_SHP_2K_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O20_SHP_2K_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O20_SHP_2K_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O20_SHP_2K_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O20_SHP_2K_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O20_SHP_2K_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O20_SHP_2K_NNTG_CTRL_01_T                         shp_nntg_ctrl_01;	//0x0304
	PE_O20_SHP_2K_NNTG_CTRL_02_T                         shp_nntg_ctrl_02;	//0x0308
	PE_O20_SHP_2K_NNTG_CTRL_03_T                         shp_nntg_ctrl_03;	//0x030C
	PE_O20_SHP_2K_NNTG_CTRL_04_T                         shp_nntg_ctrl_04;	//0x0310
	PE_O20_SHP_2K_NNTG_CTRL_05_T                         shp_nntg_ctrl_05;	//0x0314
	PE_O20_SHP_2K_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O20_SHP_2K_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O20_SHP_2K_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O20_SHP_2K_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O20_SHP_2K_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O20_SHP_2K_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O20_SHP_2K_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O20_SHP_2K_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O20_SHP_2K_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O20_SHP_2K_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O20_SHP_2K_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_O20_SHP_2K_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O20_SHP_2K_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O20_SHP_2K_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_O20_SHP_2K_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O20_SHP_2K_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x3C4
	PE_O20_SHP_2K_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x3C8
	PE_O20_SHP_2K_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O20_SHP_2K_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x3D0
	PE_O20_SHP_2K_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x3D4
	PE_O20_SHP_2K_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x3D8
	PE_O20_SHP_2K_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x3DC
	PE_O20_SHP_2K_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x3E0
	PE_O20_SHP_2K_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x3E4
	PE_O20_SHP_2K_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x3E8
	PE_O20_SHP_2K_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x3EC
	PE_O20_SHP_2K_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O20_SHP_2K_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O20_SHP_2K_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O20_SHP_2K_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O20_SHP_2K_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O20_SHP_2K_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O20_SHP_2K_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O20_SHP_2K_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O20_SHP_2K_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O20_SHP_2K_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O20_SHP_2K_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O20_SHP_2K_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O20_SHP_2K_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O20_SHP_2K_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O20_SHP_2K_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O20_SHP_2K_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O20_SHP_2K_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O20_SHP_2K_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O20_SHP_2K_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O20_SHP_2K_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O20_SHP_2K_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O20_SHP_2K_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O20_SHP_2K_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O20_SHP_2K_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O20_SHP_2K_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O20_SHP_2K_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O20_SHP_2K_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O20_SHP_2K_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O20_SHP_2K_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O20_SHP_2K_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O20_SHP_2K_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O20_SHP_2K_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O20_SHP_2K_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O20_SHP_2K_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O20_SHP_2K_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O20_SHP_2K_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O20_SHP_2K_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	PE_O20_SHP_2K_DB_CTRL_00_T                           shp_db_ctrl_00;	//0x0490
	PE_O20_SHP_2K_DB_CTRL_01_T                           shp_db_ctrl_01;	//0x0494	
	SRE_O20_SR_MERGE_MMD_05_T                         sr_merge_mmd_05;	//0x0034
	SRE_O20_SR_MERGE_MMD_06_T                         sr_merge_mmd_06;	//0x0038
	SRE_O20_SR_MERGE_BLEND_00_T                       sr_merge_blend_00;	//0x0090
}PE_SRS_2K_HW_PARAM_REG_O20_T;
/**
 *	obc face hw param reg type
 */
typedef struct {
	PE_O20_VSD_PSP_CTRL00_T                               psp_ctrl00;	//0x0000
	PE_O20_VSD_PSP_CTRL01_T                               psp_ctrl01;	//0x0004
	PE_O20_VSD_PSP_CTRL02_T                               psp_ctrl02;	//0x0008
	PE_O20_VSD_EDGE_TH_T                                  edge_th;	//0x000C
	PE_O20_VSD_FG_POSITION_T                              fg_position;	//0x0010
	PE_O20_VSD_REG_PERSPECT_GAIN_CTRL_0_T                 reg_perspect_gain_ctrl_0;	//0x0014
	PE_O20_VSD_REG_PERSPECT_LUT_X_0_T                     reg_perspect_lut_x_0;	//0x0018
	PE_O20_VSD_REG_PERSPECT_LUT_X_1_T                     reg_perspect_lut_x_1;	//0x001C
	PE_O20_VSD_REG_PERSPECT_LUT_X_2_T                     reg_perspect_lut_x_2;	//0x0020
	PE_O20_VSD_RESERVED4_T                                reserved4;	//0x0024
	PE_O20_VSD_RESERVED5_T                                reserved5;	//0x0028
	PE_O20_VSD_RESERVED6_T                                reserved6;	//0x002C
	PE_O20_VSD_RESERVED7_T                                reserved7;	//0x0030
	PE_O20_VSD_PROB_MAP_T                                 prob_map;	//0x0034
	PE_O20_VSD_ELLIPS_MAP_T                               ellips_map;	//0x0038
	PE_O20_VSD_PROB_DIFF_MAP_T                            prob_diff_map;	//0x003C
	PE_O20_VSD_OBJECT_MAP_T                               object_map;	//0x0040
	PE_O20_VSD_BLUR_MAP_T                                 blur_map;	//0x0044
	PE_O20_VSD_DISPLAY_DEBUG_MAP_T                        display_debug_map;	//0x0048
	PE_O20_VSD_PSP_IIR_T                                  psp_iir;	//0x004C
	PE_O20_VSD_PSP_GAIN_T                                 psp_gain;	//0x0050
	PE_O20_VSD_VRTX_CPC_CTRL_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O20_VSD_BLUR_HCOEF01_T                             blur_hcoef01;	//0x0060
	PE_O20_VSD_BLUR_HCOEF23_T                             blur_hcoef23;	//0x0064
	PE_O20_VSD_BLUR_HCOEF45_T                             blur_hcoef45;	//0x0068
	PE_O20_VSD_BLUR_HCOEF67_T                             blur_hcoef67;	//0x006C
	PE_O20_VSD_BLUR_HCOEF8_T                              blur_hcoef8;	//0x0070
	PE_O20_VSD_BLUR_VCOEF01_T                             blur_vcoef01;	//0x0074
	PE_O20_VSD_BLUR_VCOEF23_T                             blur_vcoef23;	//0x0078
	PE_O20_VSD_BLUR_VCOEF4_T                              blur_vcoef4;	//0x007C
	PE_O20_VSD_L5_GAIN_LUT1_T                             l5_gain_lut1;	//0x0100
	PE_O20_VSD_L5_GAIN_LUT2_T                             l5_gain_lut2;	//0x0104
	PE_O20_VSD_L0_GAIN_LUT1_T                             l0_gain_lut1;	//0x0108
	PE_O20_VSD_L0_GAIN_LUT2_T                             l0_gain_lut2;	//0x010C
	PE_O20_VSD_EDGE_WIN_H_T                               edge_win_h;	//0x0110
	PE_O20_VSD_EDGE_WIN_V_T                               edge_win_v;	//0x0114
	PE_O20_VSD_PSP_IIR1_T                                 psp_iir1;	//0x0128
	PE_O20_VSD_BG_MEASURE_CTRL_T                          bg_measure_ctrl;	//0x012C
	PE_O20_VSD_FACE0_SET_T                                face0_set;	//0x0144
	PE_O20_VSD_FACE1_SET_T                                face1_set;	//0x0148
	PE_O20_VSD_FACE2_SET_T                                face2_set;	//0x014C
	PE_O20_VSD_FACE3_SET_T                                face3_set;	//0x0150
	PE_O20_VSD_ELLIPS0_SET_T                              ellips0_set;	//0x0154
	PE_O20_VSD_ELLIPS1_SET_T                              ellips1_set;	//0x0158
	PE_O20_VSD_ELLIPS2_SET_T                              ellips2_set;	//0x015C
	PE_O20_VSD_ELLIPS3_SET_T                              ellips3_set;	//0x0160
}PE_OBC_FACE_HW_PARAM_REG_O20_T;
/**
 *	obc object hw param reg type
 */
typedef struct {
	PE_O20_VSD_PSP_CTRL00_O_T                               psp_ctrl00;	//0x0000
	PE_O20_VSD_PSP_CTRL01_O_T                               psp_ctrl01;	//0x0004
	PE_O20_VSD_PSP_CTRL02_O_T                               psp_ctrl02;	//0x0008
	PE_O20_VSD_EDGE_TH_O_T                                  edge_th;	//0x000C
	PE_O20_VSD_FG_POSITION_O_T                              fg_position;	//0x0010
	PE_O20_VSD_PERSPECT_LUT_X0_O_T                          perspect_lut_x0;	//0x0014
	PE_O20_VSD_PERSPECT_LUT_X1_O_T                          perspect_lut_x1;	//0x0018
	PE_O20_VSD_PERSPECT_LUT_X2_O_T                          perspect_lut_x2;	//0x001C
	PE_O20_VSD_PERSPECT_LUT_X3_O_T                          perspect_lut_x3;	//0x0020
	PE_O20_VSD_PERSPECT_LUT_Y0_O_T                          perspect_lut_y0;	//0x0024
	PE_O20_VSD_PERSPECT_LUT_Y1_O_T                          perspect_lut_y1;	//0x0028
	PE_O20_VSD_PERSPECT_LUT_Y2_O_T                          perspect_lut_y2;	//0x002C
	PE_O20_VSD_PERSPECT_LUT_Y3_O_T                          perspect_lut_y3;	//0x0030
	PE_O20_VSD_PROB_MAP_O_T                                 prob_map;	//0x0034
	PE_O20_VSD_ELLIPS_MAP_O_T                               ellips_map;	//0x0038
	PE_O20_VSD_PROB_DIFF_MAP_O_T                            prob_diff_map;	//0x003C
	PE_O20_VSD_OBJECT_MAP_O_T                               object_map;	//0x0040
	PE_O20_VSD_BLUR_MAP_O_T                                 blur_map;	//0x0044
	PE_O20_VSD_DISPLAY_DEBUG_MAP_O_T                        display_debug_map;	//0x0048
	PE_O20_VSD_PSP_IIR_O_T                                  psp_iir;	//0x004C
	PE_O20_VSD_PSP_GAIN_O_T                                 psp_gain;	//0x0050
	PE_O20_VSD_VRTX_CPC_CTRL_O_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O20_VSD_BLUR_HCOEF01_O_T                             blur_hcoef01;	//0x0060
	PE_O20_VSD_BLUR_HCOEF23_O_T                             blur_hcoef23;	//0x0064
	PE_O20_VSD_BLUR_HCOEF45_O_T                             blur_hcoef45;	//0x0068
	PE_O20_VSD_BLUR_HCOEF67_O_T                             blur_hcoef67;	//0x006C
	PE_O20_VSD_BLUR_HCOEF8_O_T                              blur_hcoef8;	//0x0070
	PE_O20_VSD_BLUR_VCOEF01_O_T                             blur_vcoef01;	//0x0074
	PE_O20_VSD_BLUR_VCOEF23_O_T                             blur_vcoef23;	//0x0078
	PE_O20_VSD_BLUR_VCOEF4_O_T                              blur_vcoef4;	//0x007C
	PE_O20_VSD_L5_GAIN_LUT1_O_T                             l5_gain_lut1;	//0x0100
	PE_O20_VSD_L5_GAIN_LUT2_O_T                             l5_gain_lut2;	//0x0104
	PE_O20_VSD_L0_GAIN_LUT1_O_T                             l0_gain_lut1;	//0x0108
	PE_O20_VSD_L0_GAIN_LUT2_O_T                             l0_gain_lut2;	//0x010C
	PE_O20_VSD_EDGE_WIN_H_O_T                               edge_win_h;	//0x0110
	PE_O20_VSD_EDGE_WIN_V_O_T                               edge_win_v;	//0x0114
	PE_O20_VSD_PSP_IIR1_O_T                                 psp_iir1;	//0x0128
	PE_O20_VSD_BG_MEASURE_CTRL_O_T                          bg_measure_ctrl;	//0x012C
	PE_O20_VSD_FACE0_SET_O_T                                face0_set;	//0x0144
	PE_O20_VSD_FACE1_SET_O_T                                face1_set;	//0x0148
	PE_O20_VSD_FACE2_SET_O_T                                face2_set;	//0x014C
	PE_O20_VSD_FACE3_SET_O_T                                face3_set;	//0x0150
	PE_O20_VSD_ELLIPS0_SET_O_T                              ellips0_set;	//0x0154
	PE_O20_VSD_ELLIPS1_SET_O_T                              ellips1_set;	//0x0158
	PE_O20_VSD_ELLIPS2_SET_O_T                              ellips2_set;	//0x015C
	PE_O20_VSD_ELLIPS3_SET_O_T                              ellips3_set;	//0x0160
}PE_OBC_OBJT_HW_PARAM_REG_O20_T;

/**
 *	rce face hw param reg type
 */
typedef struct {
	PE_O20_REG_RCE_FACE_CTRL_00_T                     reg_rce_face_ctrl_00;	//0x0000
	PE_O20_REG_RCE_FACE_CTRL_01_T                     reg_rce_face_ctrl_01;	//0x0004
	PE_O20_REG_RCE_FACE_CTRL_02_T                     reg_rce_face_ctrl_02;	//0x0008
	PE_O20_REG_RCE_FACE_CTRL_03_T                     reg_rce_face_ctrl_03;	//0x000C
	PE_O20_REG_RCE_FACE_CTRL_04_T                     reg_rce_face_ctrl_04;	//0x0010
	PE_O20_REG_RCE_FACE_CTRL_05_T                     reg_rce_face_ctrl_05;	//0x0014
	PE_O20_REG_RCE_FACE_CTRL_06_T                     reg_rce_face_ctrl_06;	//0x0018
	PE_O20_REG_RCE_FACE_CTRL_07_T                     reg_rce_face_ctrl_07;	//0x001C
	PE_O20_REG_RCE_FACE_CTRL_08_T                     reg_rce_face_ctrl_08;	//0x0020
	PE_O20_REG_RCE_FACE_CTRL_09_T                     reg_rce_face_ctrl_09;	//0x0024
	PE_O20_REG_RCE_FACE_CTRL_10_T                     reg_rce_face_ctrl_10;	//0x0028
	PE_O20_REG_RCE_FACE_CTRL_11_T                     reg_rce_face_ctrl_11;	//0x002C
	PE_O20_REG_RCE_FACE_CTRL_12_T                     reg_rce_face_ctrl_12;	//0x0030
	PE_O20_REG_RCE_FACE_CTRL_13_T                     reg_rce_face_ctrl_13;	//0x0034
	PE_O20_REG_RCE_FACE_CTRL_14_T                     reg_rce_face_ctrl_14;	//0x0038
	PE_O20_REG_RCE_FACE_CTRL_15_T                     reg_rce_face_ctrl_15;	//0x003C
	PE_O20_REG_RCE_FACE_CTRL_16_T                     reg_rce_face_ctrl_16;	//0x0040
	PE_O20_REG_RCE_FACE_CTRL_17_T                     reg_rce_face_ctrl_17;	//0x0044
	PE_O20_REG_RCE_FACE_CTRL_18_T                     reg_rce_face_ctrl_18;	//0x0048
	PE_O20_REG_RCE_FACE_CTRL_19_T                     reg_rce_face_ctrl_19;	//0x004C
	PE_O20_REG_RCE_FACE_CTRL_20_T                     reg_rce_face_ctrl_20;	//0x0050
	PE_O20_REG_RCE_FACE_CTRL_21_T                     reg_rce_face_ctrl_21;	//0x0054
	PE_O20_REG_RCE_FACE_CTRL_22_T                     reg_rce_face_ctrl_22;	//0x0058
	PE_O20_REG_RCE_FACE_CTRL_23_T                     reg_rce_face_ctrl_23;	//0x005C
	PE_O20_REG_RCE_FACE_CTRL_24_T                     reg_rce_face_ctrl_24;	//0x0060
	PE_O20_REG_RCE_FACE_CTRL_25_T                     reg_rce_face_ctrl_25;	//0x0064
	PE_O20_REG_RCE_FACE_CTRL_26_T                     reg_rce_face_ctrl_26;	//0x0068
	PE_O20_REG_RCE_FACE_CTRL_27_T                     reg_rce_face_ctrl_27;	//0x006C
	PE_O20_REG_RCE_FACE_CTRL_28_T                     reg_rce_face_ctrl_28;	//0x0070
	PE_O20_REG_RCE_FACE_CTRL_29_T                     reg_rce_face_ctrl_29;	//0x0074
	PE_O20_REG_RCE_FACE_CTRL_30_T                     reg_rce_face_ctrl_30;	//0x0078
	PE_O20_REG_RCE_FACE_CTRL_31_T                     reg_rce_face_ctrl_31;	//0x007C
}PE_RCE_FACE_HW_PARAM_REG_O20_T;
/**
 *	rce objt hw param reg type
 */
typedef struct {
	PE_O20_REG_RCE_OBJT_CTRL_00_T                     reg_rce_objt_ctrl_00;	//0x0000
	PE_O20_REG_RCE_OBJT_CTRL_01_T                     reg_rce_objt_ctrl_01;	//0x0004
	PE_O20_REG_RCE_OBJT_CTRL_02_T                     reg_rce_objt_ctrl_02;	//0x0008
	PE_O20_REG_RCE_OBJT_CTRL_03_T                     reg_rce_objt_ctrl_03;	//0x000C
	PE_O20_REG_RCE_OBJT_CTRL_04_T                     reg_rce_objt_ctrl_04;	//0x0010
	PE_O20_REG_RCE_OBJT_CTRL_05_T                     reg_rce_objt_ctrl_05;	//0x0014
	PE_O20_REG_RCE_OBJT_CTRL_06_T                     reg_rce_objt_ctrl_06;	//0x0018
	PE_O20_REG_RCE_OBJT_CTRL_07_T                     reg_rce_objt_ctrl_07;	//0x001C
	PE_O20_REG_RCE_OBJT_CTRL_08_T                     reg_rce_objt_ctrl_08;	//0x0020
	PE_O20_REG_RCE_OBJT_CTRL_09_T                     reg_rce_objt_ctrl_09;	//0x0024
	PE_O20_REG_RCE_OBJT_CTRL_10_T                     reg_rce_objt_ctrl_10;	//0x0028
	PE_O20_REG_RCE_OBJT_CTRL_11_T                     reg_rce_objt_ctrl_11;	//0x002C
	PE_O20_REG_RCE_OBJT_CTRL_12_T                     reg_rce_objt_ctrl_12;	//0x0030
	PE_O20_REG_RCE_OBJT_CTRL_13_T                     reg_rce_objt_ctrl_13;	//0x0034
	PE_O20_REG_RCE_OBJT_CTRL_14_T                     reg_rce_objt_ctrl_14;	//0x0038
	PE_O20_REG_RCE_OBJT_CTRL_15_T                     reg_rce_objt_ctrl_15;	//0x003C
	PE_O20_REG_RCE_OBJT_CTRL_16_T                     reg_rce_objt_ctrl_16;	//0x0040
	PE_O20_REG_RCE_OBJT_CTRL_17_T                     reg_rce_objt_ctrl_17;	//0x0044
	PE_O20_REG_RCE_OBJT_CTRL_18_T                     reg_rce_objt_ctrl_18;	//0x0048
	PE_O20_REG_RCE_OBJT_CTRL_19_T                     reg_rce_objt_ctrl_19;	//0x004C
	PE_O20_REG_RCE_OBJT_CTRL_20_T                     reg_rce_objt_ctrl_20;	//0x0050
	PE_O20_REG_RCE_OBJT_CTRL_21_T                     reg_rce_objt_ctrl_21;	//0x0054
	PE_O20_REG_RCE_OBJT_CTRL_22_T                     reg_rce_objt_ctrl_22;	//0x0058
	PE_O20_REG_RCE_OBJT_CTRL_23_T                     reg_rce_objt_ctrl_23;	//0x005C
	PE_O20_REG_RCE_OBJT_CTRL_24_T                     reg_rce_objt_ctrl_24;	//0x0060
	PE_O20_REG_RCE_OBJT_CTRL_25_T                     reg_rce_objt_ctrl_25;	//0x0064
	PE_O20_REG_RCE_OBJT_CTRL_26_T                     reg_rce_objt_ctrl_26;	//0x0068
	PE_O20_REG_RCE_OBJT_CTRL_27_T                     reg_rce_objt_ctrl_27;	//0x006C
	PE_O20_REG_RCE_OBJT_CTRL_28_T                     reg_rce_objt_ctrl_28;	//0x0070
	PE_O20_REG_RCE_OBJT_CTRL_29_T                     reg_rce_objt_ctrl_29;	//0x0074
	PE_O20_REG_RCE_OBJT_CTRL_30_T                     reg_rce_objt_ctrl_30;	//0x0078
	PE_O20_REG_RCE_OBJT_CTRL_31_T                     reg_rce_objt_ctrl_31;	//0x007C

}PE_RCE_OBJT_HW_PARAM_REG_O20_T;

/**
 *	shp hw param reg type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_RES_HW_PARAM_DATA_O20_T;

/**
 *	sre shp(srs) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_SRS_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_SRS_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_SRS_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_SRS_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_SRS_HW_PARAM_DATA_O20_T;

/**
 *	sre 2k shp(srs) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_SRS_2K_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_SRS_2K_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_SRS_2K_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_SRS_2K_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_SRS_2K_HW_PARAM_DATA_O20_T;
/**
 *	obc face hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_OBC_FACE_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_OBC_FACE_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_OBC_FACE_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_OBC_FACE_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_OBC_FACE_HW_PARAM_DATA_O20_T;
/**
 *	obc objt hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_OBC_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_OBC_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_OBC_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_OBC_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_OBC_OBJT_HW_PARAM_DATA_O20_T;
/**
 *	rce face hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_RCE_FACE_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RCE_FACE_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RCE_FACE_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RCE_FACE_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_RCE_FACE_HW_PARAM_DATA_O20_T;
/**
 *	rce objt hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_RCE_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RCE_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RCE_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RCE_OBJT_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_RCE_OBJT_HW_PARAM_DATA_O20_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_RES_HW_PARAM_O20_H_ */

