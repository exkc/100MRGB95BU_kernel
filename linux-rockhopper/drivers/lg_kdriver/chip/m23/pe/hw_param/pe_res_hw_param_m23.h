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

/** @file pe_res_hw_param_m23.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_RES_HW_PARAM_M23_H_
#define	_PE_RES_HW_PARAM_M23_H_

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
#ifdef PE_HW_M23_BRINGUP
	PE_M23_VSD_SHP_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_M23_VSD_SHP_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_M23_VSD_SHP_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	PE_M23_VSD_SHP_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_M23_VSD_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_M23_VSD_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_M23_VSD_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_M23_VSD_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_M23_VSD_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_M23_VSD_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_M23_VSD_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_M23_VSD_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_M23_VSD_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_M23_VSD_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_M23_VSD_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_M23_VSD_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_M23_VSD_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_M23_VSD_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_M23_VSD_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_M23_VSD_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_M23_VSD_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_M23_VSD_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_M23_VSD_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_M23_VSD_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_M23_VSD_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_M23_VSD_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_M23_VSD_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_M23_VSD_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_M23_VSD_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_M23_VSD_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_M23_VSD_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_M23_VSD_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_M23_VSD_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_M23_VSD_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_M23_VSD_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_M23_VSD_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_M23_VSD_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_M23_VSD_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_M23_VSD_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_M23_VSD_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_M23_VSD_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_M23_VSD_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_M23_VSD_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_M23_VSD_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_M23_VSD_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_M23_VSD_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_M23_VSD_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_M23_VSD_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_M23_VSD_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_M23_VSD_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_M23_VSD_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_M23_VSD_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_M23_VSD_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_M23_VSD_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_M23_VSD_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_M23_VSD_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_M23_VSD_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_M23_VSD_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_M23_VSD_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_M23_VSD_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_M23_VSD_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_M23_VSD_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_M23_VSD_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_M23_VSD_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_M23_VSD_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_M23_VSD_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_M23_VSD_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_M23_VSD_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_M23_VSD_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_M23_VSD_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_M23_VSD_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_M23_VSD_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_M23_VSD_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_M23_VSD_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_M23_VSD_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_M23_VSD_SHP_TGEN_CTRL_03_C0_T                      shp_core0_tgen_ctrl_03;	//0x024C
	PE_M23_VSD_SHP_TGEN_CTRL_03_C1_T                      shp_core1_tgen_ctrl_03;	//0x0250
	PE_M23_VSD_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_M23_VSD_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_M23_VSD_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_M23_VSD_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_M23_VSD_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_M23_VSD_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_M23_VSD_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_M23_VSD_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_M23_VSD_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_M23_VSD_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_M23_VSD_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_M23_VSD_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_M23_VSD_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_M23_VSD_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_M23_VSD_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_M23_VSD_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_M23_VSD_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_M23_VSD_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_M23_VSD_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_M23_VSD_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_M23_VSD_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_M23_VSD_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_M23_VSD_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_M23_VSD_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_M23_VSD_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_M23_VSD_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_M23_VSD_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_M23_VSD_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_M23_VSD_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_M23_VSD_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_M23_VSD_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_M23_VSD_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_M23_VSD_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_M23_VSD_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_M23_VSD_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_M23_VSD_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_M23_VSD_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_M23_VSD_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_M23_VSD_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_M23_VSD_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_M23_VSD_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_M23_VSD_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_M23_VSD_SHP_NNTG_CTRL_01_C0_T                      shp_core0_nntg_ctrl_01;	//0x0304
	PE_M23_VSD_SHP_NNTG_CTRL_02_C0_T                      shp_core0_nntg_ctrl_02;	//0x0308
	PE_M23_VSD_SHP_NNTG_CTRL_03_C0_T                      shp_core0_nntg_ctrl_03;	//0x030C
	PE_M23_VSD_SHP_NNTG_CTRL_04_C0_T                      shp_core0_nntg_ctrl_04;	//0x0310
	PE_M23_VSD_SHP_NNTG_CTRL_05_C0_T                      shp_core0_nntg_ctrl_05;	//0x0314
	PE_M23_VSD_SHP_NNTG_CTRL_01_C1_T                      shp_core1_nntg_ctrl_01;	//0x0318
	PE_M23_VSD_SHP_NNTG_CTRL_02_C1_T                      shp_core1_nntg_ctrl_02;	//0x031C
	PE_M23_VSD_SHP_NNTG_CTRL_03_C1_T                      shp_core1_nntg_ctrl_03;	//0x0320
	PE_M23_VSD_SHP_NNTG_CTRL_04_C1_T                      shp_core1_nntg_ctrl_04;	//0x0324
	PE_M23_VSD_SHP_NNTG_CTRL_05_C1_T                      shp_core1_nntg_ctrl_05;	//0x0328
	PE_M23_VSD_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_M23_VSD_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_M23_VSD_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_M23_VSD_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_M23_VSD_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_M23_VSD_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_M23_VSD_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_M23_VSD_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_M23_VSD_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_M23_VSD_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_M23_VSD_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_M23_VSD_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_M23_VSD_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_M23_VSD_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_M23_VSD_SHP_DP_SUM_CTRL_03_T                       shp_dp_sum_ctrl_03;	//0x036C
	PE_M23_VSD_SHP_DP_SUM_CTRL_04_T                       shp_dp_sum_ctrl_04;	//0x0370
	PE_M23_VSD_SHP_DP_SUM_CTRL_05_T                       shp_dp_sum_ctrl_05;	//0x0374
	PE_M23_VSD_SHP_DP_SUM_CTRL_06_T                       shp_dp_sum_ctrl_06;	//0x0378
	PE_M23_VSD_SHP_DP_SUM_CTRL_07_T                       shp_dp_sum_ctrl_07;	//0x037C
	PE_M23_VSD_SHP_DP_SUM_CTRL_08_T                       shp_dp_sum_ctrl_08;	//0x0380
	PE_M23_VSD_SHP_DP_SUM_CTRL_09_T                       shp_dp_sum_ctrl_09;	//0xCC462384
	PE_M23_VSD_SHP_DP_SUM_CTRL_0A_T                       shp_dp_sum_ctrl_0a;	//0xCC462388
	PE_M23_VSD_SHP_DP_SUM_CTRL_0B_T                       shp_dp_sum_ctrl_0b;	//0xCC462394
	PE_M23_VSD_SHP_DP_SUM_CTRL_0C_T                       shp_dp_sum_ctrl_0c;	//0xCC462398
	PE_M23_VSD_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_M23_VSD_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_M23_VSD_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_M23_VSD_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_M23_VSD_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_M23_VSD_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_M23_VSD_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_M23_VSD_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_M23_VSD_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_M23_VSD_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_M23_VSD_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_M23_VSD_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_M23_VSD_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_M23_VSD_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_M23_VSD_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_M23_VSD_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_M23_VSD_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_M23_VSD_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_M23_VSD_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_M23_VSD_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_M23_VSD_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_M23_VSD_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_M23_VSD_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_M23_VSD_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_M23_VSD_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_M23_VSD_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_M23_VSD_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_M23_VSD_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_M23_VSD_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_M23_VSD_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_M23_VSD_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_M23_VSD_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_M23_VSD_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_00_T                    shp_frc_flick_ctrl_00;	//0x0560
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_01_T                    shp_frc_flick_ctrl_01;	//0x0564
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_02_T                    shp_frc_flick_ctrl_02;	//0x0568
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_03_T                    shp_frc_flick_ctrl_03;	//0x056C
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_00_T                     shp_frc_blur_ctrl_00;	//0xCC462570
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_01_T                     shp_frc_blur_ctrl_01;	//0xCC462574
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_02_T                     shp_frc_blur_ctrl_02;	//0xCC462578
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_03_T                     shp_frc_blur_ctrl_03;	//0xCC46257C
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_04_T                     shp_frc_blur_ctrl_04;	//0xCC462580
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_05_T                     shp_frc_blur_ctrl_05;	//0xCC462584
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_06_T                     shp_frc_blur_ctrl_06;	//0xCC462588
	PE_M23_VSD_SHP_FRC_HALO_CTRL_00_T                     shp_frc_halo_ctrl_00;	//0xCC462590
	PE_M23_VSD_SHP_FRC_HALO_CTRL_01_T                     shp_frc_halo_ctrl_01;	//0xCC462594
	PE_M23_VSD_SHP_FRC_HALO_CTRL_02_T                     shp_frc_halo_ctrl_02;	//0xCC462598
	PE_M23_VSD_SHP_FRC_HALO_CTRL_03_T                     shp_frc_halo_ctrl_03;	//0xCC46259C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_00_T                  shp_motion_gain_ctrl_00;	//0x0600
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_01_T                  shp_motion_gain_ctrl_01;	//0x0604
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_02_T                  shp_motion_gain_ctrl_02;	//0x0608
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_03_T                  shp_motion_gain_ctrl_03;	//0x060C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_04_T                  shp_motion_gain_ctrl_04;	//0x0610
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_05_T                  shp_motion_gain_ctrl_05;	//0x0614
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_06_T                  shp_motion_gain_ctrl_06;	//0x0618
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_07_T                  shp_motion_gain_ctrl_07;	//0x061C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_08_T                  shp_motion_gain_ctrl_08;	//0x0620
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_09_T                  shp_motion_gain_ctrl_09;	//0x0624
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0A_T                  shp_motion_gain_ctrl_0a;	//0x0628
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0B_T                  shp_motion_gain_ctrl_0b;	//0x062C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0C_T                  shp_motion_gain_ctrl_0c;	//0x0630
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_00_T                  shp_motion_prot_ctrl_00;	//0x0640
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_01_T                  shp_motion_prot_ctrl_01;	//0x0644
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_02_T                  shp_motion_prot_ctrl_02;	//0x0648
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_03_T                  shp_motion_prot_ctrl_03;	//0x064C
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_04_T                  shp_motion_prot_ctrl_04;	//0xCC4F2650
	#endif
}PE_RES_HW_PARAM_REG_M23_T;

/**
 *	sre 2k shp(srs) hw param reg type
 */
typedef struct {
	PE_M23_2K_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_M23_2K_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_M23_2K_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_M23_2K_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_M23_2K_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_M23_2K_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_M23_2K_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_M23_2K_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_M23_2K_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_M23_2K_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_M23_2K_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_M23_2K_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_M23_2K_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_M23_2K_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_M23_2K_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_M23_2K_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_M23_2K_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_M23_2K_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_M23_2K_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_M23_2K_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_M23_2K_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_M23_2K_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_M23_2K_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_M23_2K_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_M23_2K_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_M23_2K_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_M23_2K_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_M23_2K_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_M23_2K_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_M23_2K_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_M23_2K_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_M23_2K_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_M23_2K_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_M23_2K_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_M23_2K_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_M23_2K_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_M23_2K_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_M23_2K_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_M23_2K_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_M23_2K_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_M23_2K_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_M23_2K_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_M23_2K_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_M23_2K_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_M23_2K_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_M23_2K_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_M23_2K_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_M23_2K_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_M23_2K_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_M23_2K_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_M23_2K_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_M23_2K_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_M23_2K_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_M23_2K_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_M23_2K_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_M23_2K_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_M23_2K_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_M23_2K_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_M23_2K_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_M23_2K_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_M23_2K_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_M23_2K_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_M23_2K_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_M23_2K_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_M23_2K_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_M23_2K_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_M23_2K_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_M23_2K_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_M23_2K_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_M23_2K_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_M23_2K_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_M23_2K_SHP_TGEN_CTRL_03_T                         shp_tgen_ctrl_03;	//0x024C
	PE_M23_2K_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_M23_2K_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_M23_2K_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_M23_2K_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_M23_2K_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_M23_2K_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_M23_2K_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_M23_2K_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_M23_2K_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_M23_2K_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_M23_2K_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_M23_2K_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_M23_2K_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_M23_2K_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_M23_2K_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_M23_2K_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_M23_2K_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_M23_2K_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_M23_2K_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_M23_2K_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_M23_2K_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_M23_2K_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_M23_2K_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_M23_2K_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_M23_2K_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_M23_2K_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_M23_2K_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_M23_2K_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_M23_2K_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_M23_2K_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_M23_2K_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_M23_2K_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_M23_2K_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_M23_2K_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_M23_2K_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_M23_2K_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_M23_2K_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_M23_2K_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_M23_2K_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_M23_2K_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_M23_2K_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_M23_2K_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_M23_2K_SHP_NNTG_CTRL_01_T                         shp_nntg_ctrl_01;	//0x0304
	PE_M23_2K_SHP_NNTG_CTRL_02_T                         shp_nntg_ctrl_02;	//0x0308
	PE_M23_2K_SHP_NNTG_CTRL_03_T                         shp_nntg_ctrl_03;	//0x030C
	PE_M23_2K_SHP_NNTG_CTRL_04_T                         shp_nntg_ctrl_04;	//0x0310
	PE_M23_2K_SHP_NNTG_CTRL_05_T                         shp_nntg_ctrl_05;	//0x0314
	PE_M23_2K_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_M23_2K_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_M23_2K_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_M23_2K_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_M23_2K_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_M23_2K_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_M23_2K_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_M23_2K_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_M23_2K_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_M23_2K_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_M23_2K_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_M23_2K_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_M23_2K_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_M23_2K_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_M23_2K_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_M23_2K_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_M23_2K_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_M23_2K_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_M23_2K_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_M23_2K_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_M23_2K_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_M23_2K_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_M23_2K_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_M23_2K_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_M23_2K_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_M23_2K_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_M23_2K_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_M23_2K_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_M23_2K_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_M23_2K_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_M23_2K_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_M23_2K_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_M23_2K_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_M23_2K_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_M23_2K_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_M23_2K_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_M23_2K_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_M23_2K_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_M23_2K_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_M23_2K_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_M23_2K_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_M23_2K_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_M23_2K_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_M23_2K_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_M23_2K_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_M23_2K_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_M23_2K_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
}PE_SRS_2K_HW_PARAM_REG_M23_T;

/**
 *	shp hw param reg type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_M23_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_M23_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_M23_T *data;
	} reg_data;
} PE_RES_HW_PARAM_DATA_M23_T;

/**
 *	sre 2k shp(srs) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_SRS_2K_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_SRS_2K_HW_PARAM_REG_M23_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_SRS_2K_HW_PARAM_REG_M23_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_SRS_2K_HW_PARAM_REG_M23_T *data;
	} reg_data;
} PE_SRS_2K_HW_PARAM_DATA_M23_T;




/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_RES_HW_PARAM_M23_H_ */

