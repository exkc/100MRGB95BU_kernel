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

/** @file pe_chpi_dnr_hw_o26f22.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CHPI_DNR_HW_O26F22_H_
#define	_PE_CHPI_DNR_HW_O26F22_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	PE_CHPI_DNR_O26F22_DNR_SD,		///< sd
	PE_CHPI_DNR_O26F22_DNR_HD_I,	///< hd
	PE_CHPI_DNR_O26F22_DNR_HD_P,	///< hd
	PE_CHPI_DNR_O26F22_DNR_UD,		///< ud
	PE_CHPI_DNR_O26F22_DNR_UD_8K,		///< ud
	PE_CHPI_DNR_O26F22_DNR_NUM		///< max num
}
PE_CHPI_DNR_HW_O26F22_DNR_FMT;


typedef enum
{
	PE_CHPI_DNR_O26F22_OSD_SD,		///< ud
	PE_CHPI_DNR_O26F22_OSD_HD,		///< ud
	PE_CHPI_DNR_O26F22_OSD_UD,		///< ud
	PE_CHPI_DNR_O26F22_OSD_NUM		///< max num
}
PE_CHPI_DNR_HW_O26F22_OSD_FMT;


typedef union {
	UINT32 udata32;
	struct {						//0xF3012380 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_master_bypass_en             :1;	//(1,RW,0x0) //
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //not used in O26
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //not used in O26
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_0_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012384 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_1_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012388 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_2_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301238C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_3_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012390 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x13579753) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_4_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012394 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x24680864) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_5_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012398 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x14703692) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_6_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301239C RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x6) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0xFF) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_7_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123A0 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x3) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_8_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123A4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_9_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123A8 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_10_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123AC RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x13579753) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_11_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123B0 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x24680864) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_12_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123B4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x14703692) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_13_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_14_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123BC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_15_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123C0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_16_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123C4 RW 0x0000_0000
	UINT32 resvd0                           :14;
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 resvd1                           :8;
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 resvd2                           :1;
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :5;	//(30:26,RW,0x0) //0: final_gain	1: variance_gain	2: variance - dc frame input	3: variance - original var	4: variance - blur dc map	5: variance - blend dc map	6: variance - final dc map	7: rmmd - l0 mmd	8: rmmd - l0 luma	9: rmmd - refine	A : rmmd - final gain	B: blur map - mmd input luma	C: blur map - mmd gain	D: blur map output	E: PAI	F: RRD	10: diff gain	11: luma gain	12: sel_diff	13: motion shift	14: motion gain	15: skin gain	16: face gain	17: face-skin gain	18: aux luma gain
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x1) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_17_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123C8 RW 0x0000_0000
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x1) //
	UINT32 resvd0                           :1;
	UINT32 reg_blur_final_size              :1;	//(2,RW,0x1) //0: new_2x2, 1: new_3x3
	UINT32 resvd1                           :1;
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x1) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x1) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x1) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x5) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20
	UINT32 resvd2                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//(18,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x5) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x2) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x3) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_18_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123CC RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x7) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0xA) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0xF) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x19) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_19_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123D0 RW 0x0020_80FF
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0xFF) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x80) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x20) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_20_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123D4 RW 0x00C0_783C
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x1E) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0xC) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_21_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123D8 RW 0x0804_0080
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x80) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_22_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123DC RW 0x0200_003C
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x20) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_23_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123E0 RW 0x0643_212C
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x12C) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0xC8) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x64) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_24_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123E4 RW 0x190C_8384
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x384) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x320) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x190) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_25_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123E8 RW 0x3E84_0100
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x3E8) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_26_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123EC RW 0x1004_0100
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_27_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123F0 RW 0x1004_0100
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_28_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123F4 RW 0x0000_0000
	UINT32 reg_block_size_v                 :8;	//(7:0,RW,0x0) //
	UINT32 reg_block_size_h                 :8;	//(15:8,RW,0x0) //
	UINT32 reg_block_no_v                   :6;	//(21:16,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_29_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123F8 RW 0x8201_0000
	UINT32 reg_last_block_size_v            :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//(19:16,RW,0x1) //
	UINT32 reg_diff_shift                   :3;	//(22:20,RW,0x0) //
	UINT32 reg_osd_run_mode                 :1;	//(23,RW,0x0) //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//(24,RW,0x0) //not used in E60
	UINT32 reg_alpha_blur_mode              :2;	//(26:25,RW,0x1) //0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//(28:27,RW,0x0) //not used in E60
	UINT32 reg_diff_use_seldiff             :1;	//(29,RW,0x0) //
	UINT32 reg_diff_calc_mode               :2;	//(31:30,RW,0x2) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_30_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30123FC RW 0xFF60_0000
	UINT32 reg_120x68_block_no_v            :7;	//(6:0,RW,0x0) //L5 block info
	UINT32 resvd                            :17;
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_31_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012400 RW 0xC003_212C
	UINT32 reg_var_lowapl_v_cut             :2;	//(1:0,RW,0x0) //
	UINT32 reg_var_lowapl_h_cut             :2;	//(3:2,RW,0x0) //
	UINT32 reg_var_lowapl_t7_offset         :2;	//(5:4,RW,0x0) //
	UINT32 reg_var_lowapl_bit_opt           :1;	//(6,RW,0x0) //
	UINT32 reg_var_lowapl_chroma_en         :1;	//(7,RW,0x0) //
	UINT32 reg_var_lowapl_v_gain            :4;	//(11:8,RW,0x0) //
	UINT32 reg_var_lowapl_h_gain            :4;	//(15:12,RW,0x0) //
	UINT32 reg_var_lowapl_cut_resolution    :4;	//(19:16,RW,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_32_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012404 RW 0x2000_00C8
	UINT32 reg_120x68_last_block_size_v     :7;	//(6:0,RW,0x0) //L5 block info
	UINT32 reg_120x68_last_block_size_h     :7;	//(13:7,RW,0x0) //L5 block info
	UINT32 reg_120x68_block_size_v          :7;	//(20:14,RW,0x0) //L5 block info
	UINT32 reg_120x68_block_size_h          :7;	//(27:21,RW,0x0) //L5 block info
	UINT32 resvd                            :4;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_33_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012408 RW 0x0284_B200
	UINT32 reg_l6_var_y_th3                 :10;	//(9:0,RW,0x200) //revived in O20
	UINT32 reg_l6_var_y_th2                 :10;	//(19:10,RW,0x12C) //revived in O20
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x0) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x2) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x2) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x0) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_34_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301240C RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_35_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012410 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_36_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012414 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_37_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012418 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_38_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301241C RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_120x68_block_no_h            :7;	//(30:24,RW,0x0) //
	UINT32 reg_120x68_block_info_force_en   :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_39_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012420 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_40_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012424 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_41_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012428 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_42_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301242C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_43_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012430 RW 0x3264_C8FA
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0xFA) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0xC8) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x32) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_44_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012434 RW 0xFF64_1400
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x14) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0xFF) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_45_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012438 RW 0x3003_1040
	UINT32 reg_bbd_y0                       :12;	//(11:0,RW,0x40) //
	UINT32 reg_bbd_x0                       :12;	//(23:12,RW,0x31) //
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x1) //
	UINT32 reg_blur2_sim_en                 :1;	//(29,RW,0x1) //
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_46_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301243C RW 0x4871_B399
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x399) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x71B) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x2) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x2) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_47_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012440 RW 0x0A50_6478
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x78) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x64) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x50) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0xA) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_48_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012444 RW 0xFF32_0A01
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x1) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0xA) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x32) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0xFF) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_49_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012448 RW 0x143C_6EC8
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x14) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_50_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301244C RW 0x5064_788C
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x8C) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x78) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x50) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_51_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012450 RW 0x7882_B4C8
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x82) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x78) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_52_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012454 RW 0x00C8_C800
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0xC8) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_53_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012458 RW 0x0064_C8FA
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0xFA) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_54_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301245C RW 0x0032_C8FF
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0xFF) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x32) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_55_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012460 RW 0x8FF0_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0xFF) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x1) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_56_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012464 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_aux_luma_en                  :1;	//(31,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_57_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012468 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_58_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301246C RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_59_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012470 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_60_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012474 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_61_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012478 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(9:0,RW,0x0) //
	UINT32 resvd                            :22;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_62_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301247C RW 0x8020_8080
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_63_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012480 RW 0x80FF_FF00
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_64_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012484 RW 0x0020_0200
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_65_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012488 RW 0x0020_0200
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_66_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301248C RW 0x0020_0200
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_67_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012490 RW 0x0003_2000
	UINT32 tdata0                           :32;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_68_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012494 RW 0x1ABC_0085
	UINT32 reg_var_lowapl_lut_x2            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x1            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x0            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_69_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012498 RW 0x03C1_90C8
	UINT32 reg_var_lowapl_lut_y1            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y0            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x3            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_70_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301249C RW 0x9909_6320
	UINT32 reg_var_lowapl_blend_x0          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y3            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y2            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_71_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124A0 RW 0x384F_A100
	UINT32 reg_var_lowapl_blend_x3          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x2          :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x1          :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_72_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124A4 RW 0x1004_0100
	UINT32 reg_var_lowapl_blend_y3          :8;	//(7:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y2          :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y1          :8;	//(23:16,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y0          :8;	//(31:24,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_73_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124A8 RW 0x1004_0100
	UINT32 reg_lowapl_master_blend          :8;	//(7:0,RW,0x0) //
	UINT32 reg_2x2_var_msb_sel              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_74_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124AC RW 0x1000_2010
	UINT32 reg_2nd_var_x_th1                :10;	//(9:0,RW,0x10) //
	UINT32 reg_2nd_var_x_th0                :10;	//(19:10,RW,0x8) //
	UINT32 reg_2nd_luma_y_th7               :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_75_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124B0 RW 0x0140_7900
	UINT32 reg_2nd_var_y_th0                :10;	//(9:0,RW,0x100) //
	UINT32 reg_2nd_var_x_th3                :10;	//(19:10,RW,0x1E) //
	UINT32 reg_2nd_var_x_th2                :10;	//(29:20,RW,0x14) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_76_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124B4 RW 0x0B40_8000
	UINT32 reg_2nd_var_y_th3                :10;	//(9:0,RW,0x0) //
	UINT32 reg_2nd_var_y_th2                :10;	//(19:10,RW,0x20) //
	UINT32 reg_2nd_var_y_th1                :10;	//(29:20,RW,0xB4) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_77_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124B8 RW 0x6030_180C
	UINT32 reg_2nd_diff_x_th0               :8;	//(7:0,RW,0xC) //
	UINT32 reg_2nd_diff_x_th1               :8;	//(15:8,RW,0x18) //
	UINT32 reg_2nd_diff_x_th2               :8;	//(23:16,RW,0x30) //
	UINT32 reg_2nd_diff_x_th3               :8;	//(31:24,RW,0x60) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_78_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124BC RW 0x0020_80FF
	UINT32 reg_2nd_diff_y_th0               :8;	//(7:0,RW,0xFF) //
	UINT32 reg_2nd_diff_y_th1               :8;	//(15:8,RW,0x80) //
	UINT32 reg_2nd_diff_y_th2               :8;	//(23:16,RW,0x20) //
	UINT32 reg_2nd_diff_y_th3               :8;	//(31:24,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_79_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124C0 RW 0x0000_0000
	UINT32 reg_2nd_rd_simple_init_yy        :32;	//(31:0,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_80_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124C4 RW 0x0000_0000
	UINT32 reg_2nd_rd_simple_init_cb        :32;	//(31:0,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_81_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124C8 RW 0x0000_0000
	UINT32 reg_2nd_rd_simple_init_cr        :32;	//(31:0,RW,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_82_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124CC RW 0x0000_0000
	UINT32 reg_overlap_hsize                :8;	//(7:0,NA,0x80) //* final release로 인해 RTL에서는 "reg_overlap"으로 사용중(다음버전에 명칭 업데이트 예정)	가용범위 : 4~128 (0~3 사이의 값 입력시 오류 발생)
	UINT32 reg_trans_pos                    :6;	//(13:8,NA,0x2) //h_block 개수보다 작아야 함
	UINT32 resvd0                           :10;
	UINT32 reg_original_size_set            :1;	//(24,NA,0x0) //block_info에서 ND의 split 이전의 오리지널 입력 영상에 대한 세팅(E60에서 8K 4split/4K 2split은 코어 입력이 동일하기 때문에 별도의 구분 필요)	0: 8K	1: 4K
	UINT32 resvd1                           :3;
	UINT32 reg_col_index                    :2;	//(29:28,NA,0x0) //* final release로 인해 RTL에서는 "reg_boundary_side"으로 사용중(다음버전에 명칭 업데이트 예정)	Split/Merger에 의해서 Decontour 모듈은 3 2 1 0 으로 인덱싱 되어있으나 설정은 아래의 숫자를 참조	내부 동작적인 측면에서 1과 2는 똑같은 형태(튜닝 등에 의해서 위치를 표시하기 위해 구별)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd2                           :1;
	UINT32 reg_col_mode_en                  :1;	//(31,NA,0x0) //* final release로 인해 RTL에서는 "reg_boundary_en"으로 사용중(다음버전에 명칭 업데이트 예정)	0 : col_mode off	1 : col_mode on
	};
}PE_O26F22_REG_OSD_DECON_CTRL_83_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124D0 RW 0x0000_0000
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//(1:0,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//(3:2,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//(9:8,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//(28,NA,0x1) //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x1) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x1) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_84_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124D4 RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x87F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_85_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124D8 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x83F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x29) //
	UINT32 resvd1                           :4;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_86_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124DC RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_prev_x                   :12;	//(31:20,NA,0x1E) //Defualt: 30	이전 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
}PE_O26F22_REG_OSD_DECON_CTRL_87_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124E0 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_next_x                   :12;	//(31:20,NA,0x28) //Defualt: 40	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
}PE_O26F22_REG_OSD_DECON_CTRL_88_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124E4 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_prev_y                   :7;	//(30:24,NA,0x78) //Defualt: 120 (y < block_size)	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_89_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124E8 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_next_y                   :7;	//(30:24,NA,0x79) //Defualt: 121 (y < block_size)	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_90_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124EC RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_91_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124F0 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_92_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124F4 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_93_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124F8 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_94_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF30124FC RW 0x0000_0000
	UINT32 reg_face_demo_x1                 :13;	//(12:0,NA,0x400) //x0 < pos_x < x1 일때 동작(2 배수로 설정 입력)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//(28:16,NA,0x1E0) //x0 < pos_x < x1 일때 동작(2 배수로 설정 입력)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//(31,NA,0x0) //face gain demo mode 동작
	};
}PE_O26F22_REG_OSD_DECON_CTRL_95_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012500 RW 0x0000_0000
	UINT32 reg_face_demo_y1                 :13;	//(12:0,NA,0x64) //y0 < pos_y < y1 일때 동작
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//(28:16,NA,0xA) //y0 < pos_y < y1 일때 동작
	UINT32 resvd1                           :3;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_96_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012504 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x3              :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_97_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012508 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y3              :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_98_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301250C RW 0x0000_0000
	UINT32 reg_ref_filter_x1                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_x2                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x3                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ref_mmd_sel                  :1;	//(31,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_99_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012510 RW 0x0000_0000
	UINT32 reg_ref_filter_y2                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y3                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x0                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_100_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012514 RW 0x0000_0000
	UINT32 reg_ref_filter_y0                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y1                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_mmd_left_shift           :3;	//(22:20,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_mmd_right_shift              :2;	//(29:28,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_101_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012518 RW 0x0000_0000
	UINT32 reg_margin_bit                   :3;	//(2:0,NA,0x0) //
	UINT32 reg_rand_shift                   :3;	//(5:3,NA,0x0) //
	UINT32 resvd                            :26;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_102_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301251C RW 0x0000_0000
	UINT32 reg_msp_outer_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_x3            :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_103_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012520 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_y3            :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_104_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012524 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_x3            :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_105_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012528 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_y3            :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_106_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301252C RW 0x0000_0000
	UINT32 reg_msp_rd_init_yy               :32;	//(31:0,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_107_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012530 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cb               :32;	//(31:0,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_108_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012534 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cr               :32;	//(31:0,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_109_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012538 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_x0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x3                :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_110_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301253C RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_y0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y3                :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_111_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012540 RW 0x0000_0000
	UINT32 reg_l6_blur_luma_ratio           :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_luma_mode            :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_luma_th              :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :11;
	UINT32 reg_amean_filter_en              :1;	//(31,NA,0x0) //a-mean filter en
	};
}PE_O26F22_REG_OSD_DECON_CTRL_112_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012544 RW 0x0000_0000
	UINT32 reg_l6_blur_chroma_ratio         :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_chroma_mode          :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_chroma_th            :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_113_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012548 RW 0x0000_0000
	UINT32 reg_rd_blur_ratio_c              :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_ratio_y              :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :14;
	UINT32 reg_oai_repeat                   :1;	//(30,NA,0x0) //
	UINT32 reg_rd_blur_en                   :1;	//(31,NA,0x0) //O26 New : RRD enable
	};
}PE_O26F22_REG_OSD_DECON_CTRL_114_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301254C RW 0x0000_0000
	UINT32 reg_rd_blur_x0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_x1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_x2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_x3                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_115_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012550 RW 0x0000_0000
	UINT32 reg_rd_blur_y0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_y1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_y2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_y3                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26F22_REG_OSD_DECON_CTRL_116_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012554 RW 0x1357_9753
	UINT32 reg_decon_rd_init_yy             :32;	//(31:0,NA,0x13579753) //Decon 1st RRD seed
	};
}PE_O26F22_REG_OSD_DECON_CTRL_117_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012558 RW 0x2468_0864
	UINT32 reg_decon_rd_init_cb             :32;	//(31:0,NA,0x24680864) //Decon 1st RRD seed
	};
}PE_O26F22_REG_OSD_DECON_CTRL_118_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301255C RW 0x1470_3692
	UINT32 reg_decon_rd_init_cr             :32;	//(31:0,NA,0x14703692) //Decon 1st RRD seed
	};
}PE_O26F22_REG_OSD_DECON_CTRL_119_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012560 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_120_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012564 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_121_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3012568 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_122_PARAM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF301256C RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26F22_REG_OSD_DECON_CTRL_123_PARAM_T;

typedef struct {
	PE_O26F22_REG_OSD_DECON_CTRL_0_PARAM_T                       reg_decon_ctrl_0;	//0xF3012380
	PE_O26F22_REG_OSD_DECON_CTRL_1_PARAM_T                       reg_decon_ctrl_1;	//0xF3012384
	PE_O26F22_REG_OSD_DECON_CTRL_2_PARAM_T                       reg_decon_ctrl_2;	//0xF3012388
	PE_O26F22_REG_OSD_DECON_CTRL_3_PARAM_T                       reg_decon_ctrl_3;	//0xF301238C
	PE_O26F22_REG_OSD_DECON_CTRL_4_PARAM_T                       reg_decon_ctrl_4;	//0xF3012390
	PE_O26F22_REG_OSD_DECON_CTRL_5_PARAM_T                       reg_decon_ctrl_5;	//0xF3012394
	PE_O26F22_REG_OSD_DECON_CTRL_6_PARAM_T                       reg_decon_ctrl_6;	//0xF3012398
	PE_O26F22_REG_OSD_DECON_CTRL_7_PARAM_T                       reg_decon_ctrl_7;	//0xF301239C
	PE_O26F22_REG_OSD_DECON_CTRL_8_PARAM_T                       reg_decon_ctrl_8;	//0xF30123A0
	PE_O26F22_REG_OSD_DECON_CTRL_9_PARAM_T                       reg_decon_ctrl_9;	//0xF30123A4
	PE_O26F22_REG_OSD_DECON_CTRL_10_PARAM_T                     reg_decon_ctrl_10;	//0xF30123A8
	PE_O26F22_REG_OSD_DECON_CTRL_11_PARAM_T                     reg_decon_ctrl_11;	//0xF30123AC
	PE_O26F22_REG_OSD_DECON_CTRL_12_PARAM_T                     reg_decon_ctrl_12;	//0xF30123B0
	PE_O26F22_REG_OSD_DECON_CTRL_13_PARAM_T                     reg_decon_ctrl_13;	//0xF30123B4
	PE_O26F22_REG_OSD_DECON_CTRL_14_PARAM_T                     reg_decon_ctrl_14;	//0xF30123B8
	PE_O26F22_REG_OSD_DECON_CTRL_15_PARAM_T                     reg_decon_ctrl_15;	//0xF30123BC
	PE_O26F22_REG_OSD_DECON_CTRL_16_PARAM_T                     reg_decon_ctrl_16;	//0xF30123C0
	PE_O26F22_REG_OSD_DECON_CTRL_17_PARAM_T                     reg_decon_ctrl_17;	//0xF30123C4
	PE_O26F22_REG_OSD_DECON_CTRL_18_PARAM_T                     reg_decon_ctrl_18;	//0xF30123C8
	PE_O26F22_REG_OSD_DECON_CTRL_19_PARAM_T                     reg_decon_ctrl_19;	//0xF30123CC
	PE_O26F22_REG_OSD_DECON_CTRL_20_PARAM_T                     reg_decon_ctrl_20;	//0xF30123D0
	PE_O26F22_REG_OSD_DECON_CTRL_21_PARAM_T                     reg_decon_ctrl_21;	//0xF30123D4
	PE_O26F22_REG_OSD_DECON_CTRL_22_PARAM_T                     reg_decon_ctrl_22;	//0xF30123D8
	PE_O26F22_REG_OSD_DECON_CTRL_23_PARAM_T                     reg_decon_ctrl_23;	//0xF30123DC
	PE_O26F22_REG_OSD_DECON_CTRL_24_PARAM_T                     reg_decon_ctrl_24;	//0xF30123E0
	PE_O26F22_REG_OSD_DECON_CTRL_25_PARAM_T                     reg_decon_ctrl_25;	//0xF30123E4
	PE_O26F22_REG_OSD_DECON_CTRL_26_PARAM_T                     reg_decon_ctrl_26;	//0xF30123E8
	PE_O26F22_REG_OSD_DECON_CTRL_27_PARAM_T                     reg_decon_ctrl_27;	//0xF30123EC
	PE_O26F22_REG_OSD_DECON_CTRL_28_PARAM_T                     reg_decon_ctrl_28;	//0xF30123F0
	PE_O26F22_REG_OSD_DECON_CTRL_29_PARAM_T                     reg_decon_ctrl_29;	//0xF30123F4
	PE_O26F22_REG_OSD_DECON_CTRL_30_PARAM_T                     reg_decon_ctrl_30;	//0xF30123F8
	PE_O26F22_REG_OSD_DECON_CTRL_31_PARAM_T                     reg_decon_ctrl_31;	//0xF30123FC
	PE_O26F22_REG_OSD_DECON_CTRL_32_PARAM_T                     reg_decon_ctrl_32;	//0xF3012400
	PE_O26F22_REG_OSD_DECON_CTRL_33_PARAM_T                     reg_decon_ctrl_33;	//0xF3012404
	PE_O26F22_REG_OSD_DECON_CTRL_34_PARAM_T                     reg_decon_ctrl_34;	//0xF3012408
	PE_O26F22_REG_OSD_DECON_CTRL_35_PARAM_T                     reg_decon_ctrl_35;	//0xF301240C
	PE_O26F22_REG_OSD_DECON_CTRL_36_PARAM_T                     reg_decon_ctrl_36;	//0xF3012410
	PE_O26F22_REG_OSD_DECON_CTRL_37_PARAM_T                     reg_decon_ctrl_37;	//0xF3012414
	PE_O26F22_REG_OSD_DECON_CTRL_38_PARAM_T                     reg_decon_ctrl_38;	//0xF3012418
	PE_O26F22_REG_OSD_DECON_CTRL_39_PARAM_T                     reg_decon_ctrl_39;	//0xF301241C
	PE_O26F22_REG_OSD_DECON_CTRL_40_PARAM_T                     reg_decon_ctrl_40;	//0xF3012420
	PE_O26F22_REG_OSD_DECON_CTRL_41_PARAM_T                     reg_decon_ctrl_41;	//0xF3012424
	PE_O26F22_REG_OSD_DECON_CTRL_42_PARAM_T                     reg_decon_ctrl_42;	//0xF3012428
	PE_O26F22_REG_OSD_DECON_CTRL_43_PARAM_T                     reg_decon_ctrl_43;	//0xF301242C
	PE_O26F22_REG_OSD_DECON_CTRL_44_PARAM_T                     reg_decon_ctrl_44;	//0xF3012430
	PE_O26F22_REG_OSD_DECON_CTRL_45_PARAM_T                     reg_decon_ctrl_45;	//0xF3012434
	PE_O26F22_REG_OSD_DECON_CTRL_46_PARAM_T                     reg_decon_ctrl_46;	//0xF3012438
	PE_O26F22_REG_OSD_DECON_CTRL_47_PARAM_T                     reg_decon_ctrl_47;	//0xF301243C
	PE_O26F22_REG_OSD_DECON_CTRL_48_PARAM_T                     reg_decon_ctrl_48;	//0xF3012440
	PE_O26F22_REG_OSD_DECON_CTRL_49_PARAM_T                     reg_decon_ctrl_49;	//0xF3012444
	PE_O26F22_REG_OSD_DECON_CTRL_50_PARAM_T                     reg_decon_ctrl_50;	//0xF3012448
	PE_O26F22_REG_OSD_DECON_CTRL_51_PARAM_T                     reg_decon_ctrl_51;	//0xF301244C
	PE_O26F22_REG_OSD_DECON_CTRL_52_PARAM_T                     reg_decon_ctrl_52;	//0xF3012450
	PE_O26F22_REG_OSD_DECON_CTRL_53_PARAM_T                     reg_decon_ctrl_53;	//0xF3012454
	PE_O26F22_REG_OSD_DECON_CTRL_54_PARAM_T                     reg_decon_ctrl_54;	//0xF3012458
	PE_O26F22_REG_OSD_DECON_CTRL_55_PARAM_T                     reg_decon_ctrl_55;	//0xF301245C
	PE_O26F22_REG_OSD_DECON_CTRL_56_PARAM_T                     reg_decon_ctrl_56;	//0xF3012460
	PE_O26F22_REG_OSD_DECON_CTRL_57_PARAM_T                     reg_decon_ctrl_57;	//0xF3012464
	PE_O26F22_REG_OSD_DECON_CTRL_58_PARAM_T                     reg_decon_ctrl_58;	//0xF3012468
	PE_O26F22_REG_OSD_DECON_CTRL_59_PARAM_T                     reg_decon_ctrl_59;	//0xF301246C
	PE_O26F22_REG_OSD_DECON_CTRL_60_PARAM_T                     reg_decon_ctrl_60;	//0xF3012470
	PE_O26F22_REG_OSD_DECON_CTRL_61_PARAM_T                     reg_decon_ctrl_61;	//0xF3012474
	PE_O26F22_REG_OSD_DECON_CTRL_62_PARAM_T                     reg_decon_ctrl_62;	//0xF3012478
	PE_O26F22_REG_OSD_DECON_CTRL_63_PARAM_T                     reg_decon_ctrl_63;	//0xF301247C
	PE_O26F22_REG_OSD_DECON_CTRL_64_PARAM_T                     reg_decon_ctrl_64;	//0xF3012480
	PE_O26F22_REG_OSD_DECON_CTRL_65_PARAM_T                     reg_decon_ctrl_65;	//0xF3012484
	PE_O26F22_REG_OSD_DECON_CTRL_66_PARAM_T                     reg_decon_ctrl_66;	//0xF3012488
	PE_O26F22_REG_OSD_DECON_CTRL_67_PARAM_T                     reg_decon_ctrl_67;	//0xF301248C
	PE_O26F22_REG_OSD_DECON_CTRL_68_PARAM_T                     reg_decon_ctrl_68;	//0xF3012490
	PE_O26F22_REG_OSD_DECON_CTRL_69_PARAM_T                     reg_decon_ctrl_69;	//0xF3012494
	PE_O26F22_REG_OSD_DECON_CTRL_70_PARAM_T                     reg_decon_ctrl_70;	//0xF3012498
	PE_O26F22_REG_OSD_DECON_CTRL_71_PARAM_T                     reg_decon_ctrl_71;	//0xF301249C
	PE_O26F22_REG_OSD_DECON_CTRL_72_PARAM_T                     reg_decon_ctrl_72;	//0xF30124A0
	PE_O26F22_REG_OSD_DECON_CTRL_73_PARAM_T                     reg_decon_ctrl_73;	//0xF30124A4
	PE_O26F22_REG_OSD_DECON_CTRL_74_PARAM_T                     reg_decon_ctrl_74;	//0xF30124A8
	PE_O26F22_REG_OSD_DECON_CTRL_75_PARAM_T                     reg_decon_ctrl_75;	//0xF30124AC
	PE_O26F22_REG_OSD_DECON_CTRL_76_PARAM_T                     reg_decon_ctrl_76;	//0xF30124B0
	PE_O26F22_REG_OSD_DECON_CTRL_77_PARAM_T                     reg_decon_ctrl_77;	//0xF30124B4
	PE_O26F22_REG_OSD_DECON_CTRL_78_PARAM_T                     reg_decon_ctrl_78;	//0xF30124B8
	PE_O26F22_REG_OSD_DECON_CTRL_79_PARAM_T                     reg_decon_ctrl_79;	//0xF30124BC
	PE_O26F22_REG_OSD_DECON_CTRL_80_PARAM_T                     reg_decon_ctrl_80;	//0xF30124C0
	PE_O26F22_REG_OSD_DECON_CTRL_81_PARAM_T                     reg_decon_ctrl_81;	//0xF30124C4
	PE_O26F22_REG_OSD_DECON_CTRL_82_PARAM_T                     reg_decon_ctrl_82;	//0xF30124C8
	PE_O26F22_REG_OSD_DECON_CTRL_83_PARAM_T                     reg_decon_ctrl_83;	//0xF30124CC
	PE_O26F22_REG_OSD_DECON_CTRL_84_PARAM_T                     reg_decon_ctrl_84;	//0xF30124D0
	PE_O26F22_REG_OSD_DECON_CTRL_85_PARAM_T                     reg_decon_ctrl_85;	//0xF30124D4
	PE_O26F22_REG_OSD_DECON_CTRL_86_PARAM_T                     reg_decon_ctrl_86;	//0xF30124D8
	PE_O26F22_REG_OSD_DECON_CTRL_87_PARAM_T                     reg_decon_ctrl_87;	//0xF30124DC
	PE_O26F22_REG_OSD_DECON_CTRL_88_PARAM_T                     reg_decon_ctrl_88;	//0xF30124E0
	PE_O26F22_REG_OSD_DECON_CTRL_89_PARAM_T                     reg_decon_ctrl_89;	//0xF30124E4
	PE_O26F22_REG_OSD_DECON_CTRL_90_PARAM_T                     reg_decon_ctrl_90;	//0xF30124E8
	PE_O26F22_REG_OSD_DECON_CTRL_91_PARAM_T                     reg_decon_ctrl_91;	//0xF30124EC
	PE_O26F22_REG_OSD_DECON_CTRL_92_PARAM_T                     reg_decon_ctrl_92;	//0xF30124F0
	PE_O26F22_REG_OSD_DECON_CTRL_93_PARAM_T                     reg_decon_ctrl_93;	//0xF30124F4
	PE_O26F22_REG_OSD_DECON_CTRL_94_PARAM_T                     reg_decon_ctrl_94;	//0xF30124F8
	PE_O26F22_REG_OSD_DECON_CTRL_95_PARAM_T                     reg_decon_ctrl_95;	//0xF30124FC
	PE_O26F22_REG_OSD_DECON_CTRL_96_PARAM_T                     reg_decon_ctrl_96;	//0xF3012500
	PE_O26F22_REG_OSD_DECON_CTRL_97_PARAM_T                     reg_decon_ctrl_97;	//0xF3012504
	PE_O26F22_REG_OSD_DECON_CTRL_98_PARAM_T                     reg_decon_ctrl_98;	//0xF3012508
	PE_O26F22_REG_OSD_DECON_CTRL_99_PARAM_T                     reg_decon_ctrl_99;	//0xF301250C
	PE_O26F22_REG_OSD_DECON_CTRL_100_PARAM_T                   reg_decon_ctrl_100;	//0xF3012510
	PE_O26F22_REG_OSD_DECON_CTRL_101_PARAM_T                   reg_decon_ctrl_101;	//0xF3012514
	PE_O26F22_REG_OSD_DECON_CTRL_102_PARAM_T                   reg_decon_ctrl_102;	//0xF3012518
	PE_O26F22_REG_OSD_DECON_CTRL_103_PARAM_T                   reg_decon_ctrl_103;	//0xF301251C
	PE_O26F22_REG_OSD_DECON_CTRL_104_PARAM_T                   reg_decon_ctrl_104;	//0xF3012520
	PE_O26F22_REG_OSD_DECON_CTRL_105_PARAM_T                   reg_decon_ctrl_105;	//0xF3012524
	PE_O26F22_REG_OSD_DECON_CTRL_106_PARAM_T                   reg_decon_ctrl_106;	//0xF3012528
	PE_O26F22_REG_OSD_DECON_CTRL_107_PARAM_T                   reg_decon_ctrl_107;	//0xF301252C
	PE_O26F22_REG_OSD_DECON_CTRL_108_PARAM_T                   reg_decon_ctrl_108;	//0xF3012530
	PE_O26F22_REG_OSD_DECON_CTRL_109_PARAM_T                   reg_decon_ctrl_109;	//0xF3012534
	PE_O26F22_REG_OSD_DECON_CTRL_110_PARAM_T                   reg_decon_ctrl_110;	//0xF3012538
	PE_O26F22_REG_OSD_DECON_CTRL_111_PARAM_T                   reg_decon_ctrl_111;	//0xF301253C
	PE_O26F22_REG_OSD_DECON_CTRL_112_PARAM_T                   reg_decon_ctrl_112;	//0xF3012540
	PE_O26F22_REG_OSD_DECON_CTRL_113_PARAM_T                   reg_decon_ctrl_113;	//0xF3012544
	PE_O26F22_REG_OSD_DECON_CTRL_114_PARAM_T                   reg_decon_ctrl_114;	//0xF3012548
	PE_O26F22_REG_OSD_DECON_CTRL_115_PARAM_T                   reg_decon_ctrl_115;	//0xF301254C
	PE_O26F22_REG_OSD_DECON_CTRL_116_PARAM_T                   reg_decon_ctrl_116;	//0xF3012550
	PE_O26F22_REG_OSD_DECON_CTRL_117_PARAM_T                   reg_decon_ctrl_117;	//0xF3012554
	PE_O26F22_REG_OSD_DECON_CTRL_118_PARAM_T                   reg_decon_ctrl_118;	//0xF3012558
	PE_O26F22_REG_OSD_DECON_CTRL_119_PARAM_T                   reg_decon_ctrl_119;	//0xF301255C
	PE_O26F22_REG_OSD_DECON_CTRL_120_PARAM_T                   reg_decon_ctrl_120;	//0xF3012560
	PE_O26F22_REG_OSD_DECON_CTRL_121_PARAM_T                   reg_decon_ctrl_121;	//0xF3012564
	PE_O26F22_REG_OSD_DECON_CTRL_122_PARAM_T                   reg_decon_ctrl_122;	//0xF3012568
	PE_O26F22_REG_OSD_DECON_CTRL_123_PARAM_T                   reg_decon_ctrl_123;	//0xF301256C
}PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int PE_CHPI_DNR_HW_O26F22_SetDefault(void);
extern int PE_CHPI_DNR_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams);
extern int PE_CHPI_DNR_HW_O26F22_SetCtrl(void *pstParams);
extern int PE_CHPI_DNR_HW_O26F22_SetDcntCtrl(void *pstParams);
extern int PE_CHPI_DNR_HW_O26F22_SetEnable(UINT32 *onoff);
extern int PE_CHPI_DNR_HW_O26F22_GetCtrl(void);
extern int PE_CHPI_DNR_HW_O26F22_GetDcntCtrl(void);
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CHPI_DNR_HW_O26F22_H_ */
