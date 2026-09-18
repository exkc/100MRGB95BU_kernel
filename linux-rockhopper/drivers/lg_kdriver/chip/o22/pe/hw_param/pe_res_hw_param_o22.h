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

/** @file pe_res_hw_param_o22.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_RES_HW_PARAM_O22_H_
#define	_PE_RES_HW_PARAM_O22_H_

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

typedef union {
	UINT32 udata32;
	struct {						//0xF3410020 RW 0x0E00_0810
	UINT32 reg_new_fd_detail_beta_mul		:8; //(7:0,NA,16) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_detail_alpha_mul		:8; //(15:8,NA,8) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_edge_beta_mul 		:8; //(23:16,NA,0) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_new_fd_edge_alpha_mul		:8; //(31:24,NA,14) //get_t_map (alpha*t_map - beta*a_map)
	};

}PE_O22F22_SHP_NEW_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410024 RW 0x60A0_0020
	UINT32 reg_new_fd_edge_minmax_y0		:8; //(7:0,NA,32) //Final edge LUT, y0
	UINT32 reg_new_fd_edge_minmax_x0		:8; //(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_new_fd_edge_minmax_y1		:8; //(23:16,NA,160) //Final edge LUT, y1
	UINT32 reg_new_fd_edge_minmax_x1		:8; //(31:24,NA,96) //Final edge LUT, x1
	};

}PE_O22F22_SHP_NEW_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410028 RW 0xFFFF_82DC
	UINT32 reg_new_fd_edge_minmax_y2		:8; //(7:0,NA,220) //Final edge LUT, y2
	UINT32 reg_new_fd_edge_minmax_x2		:8; //(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_new_fd_edge_minmax_y3		:8; //(23:16,NA,255) //Final edge LUT, y3
	UINT32 reg_new_fd_edge_minmax_x3		:8; //(31:24,NA,255) //Final edge LUT, x3
	};

}PE_O22F22_SHP_NEW_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341002C RW 0x2860_0040
	UINT32 reg_new_fd_detail_minmax_y0		:8; //(7:0,NA,64) //Final detail LUT, y0
	UINT32 reg_new_fd_detail_minmax_x0		:8; //(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_new_fd_detail_minmax_y1		:8; //(23:16,NA,96) //Final detail LUT, y1
	UINT32 reg_new_fd_detail_minmax_x1		:8; //(31:24,NA,40) //Final detail LUT, x1
	};
}PE_O22F22_SHP_NEW_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410030 RW 0x64A0_4678
	UINT32 reg_new_fd_detail_minmax_y2		:8; //(7:0,NA,120) //Final detail LUT, y2
	UINT32 reg_new_fd_detail_minmax_x2		:8; //(15:8,NA,70) //Final detail LUT, x2
	UINT32 reg_new_fd_detail_minmax_y3		:8; //(23:16,NA,160) //Final detail LUT, y3
	UINT32 reg_new_fd_detail_minmax_x3		:8; //(31:24,NA,100) //Final detail LUT, x3
	};
}PE_O22F22_SHP_NEW_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410034 RW 0x0000_0180
	UINT32 reg_texture_region_alpha 		:8; //(7:0,NA,128) //Final detail LUT, y2
	UINT32 reg_region_text_en_aux			:1; //(8:8,NA,1) //Final detail LUT, y2
	UINT32 reg_obj_shp_en_aux				:1; //(9:9,NA,0) //Final detail LUT, y2
	UINT32 resvd							:22;
	};
}PE_O22F22_SHP_TEXT_REGION_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410100 RW 0x0000_0010
	UINT32 reg_esf_detour_mode				:1; //(0:0,NA,0) //edge shift filter detour enable
	UINT32 reg_esf_buffer_detour_en 		:1; //(1:1,NA,0) //edge shift filter buffer detour enable
	UINT32 resvd0							:2;
	UINT32 reg_esf_en						:1; //(4:4,NA,1) //edge shift filter enable
	UINT32 resvd1							:3;
	UINT32 reg_esf_dbg_en					:1; //(8:8,NA,0) //edge shift filter debug enable
	UINT32 resvd2							:23;
	};
}PE_O22F22_SHP_ESF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410104 RW 0x4040_C814
	UINT32 reg_esf_min_ratio				:8; //(7:0,NA,20) //edge shift filter min ratio
	UINT32 reg_esf_base 					:8; //(15:8,NA,200) //edge shift filter base
	UINT32 reg_esf_max_clip 				:8; //(23:16,NA,64) //edge shift filter max clipping
	UINT32 reg_esf_master_gain				:8; //(31:24,NA,64) //edge shift filter master gain
	};
}PE_O22F22_SHP_ESF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410108 RW 0x0000_0819
	UINT32 reg_esf_ltv_offset				:8; //(7:0,NA,25) //edge shift filter ltv offset
	UINT32 reg_esf_ltv_mul					:8; //(15:8,NA,8) //edge shift filter ltv mul
	UINT32 resvd							:16;
	};
}PE_O22F22_SHP_ESF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410110 RW 0x0000_0000
	UINT32 reg_core0_win_esf_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_esf_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_esf_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_esf_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_esf_win_en 		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_esf_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_esf_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_esf_bdr_en 		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_esf_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_esf_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_esf_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410114 RW 0x0000_0000
	UINT32 reg_core0_win_esf_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core0_win_esf_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE0_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410118 RW 0x086F_0EFF
	UINT32 reg_core0_win_esf_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core0_win_esf_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE0_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341011C RW 0x0000_0000
	UINT32 reg_core0_win_esf_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core0_win_esf_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE0_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410120 RW 0x086F_0EFF
	UINT32 reg_core0_win_esf_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core0_win_esf_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE0_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410130 RW 0x0000_0000
	UINT32 reg_core1_win_esf_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core1_win_esf_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core1_win_esf_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core1_win_esf_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_esf_win_en 		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_esf_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core1_win_esf_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core1_win_esf_bdr_en 		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core1_win_esf_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core1_win_esf_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core1_win_esf_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410134 RW 0x0000_0000
	UINT32 reg_core1_win_esf_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core1_win_esf_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE1_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410138 RW 0x086F_0EFF
	UINT32 reg_core1_win_esf_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core1_win_esf_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE1_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341013C RW 0x0000_0000
	UINT32 reg_core1_win_esf_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core1_win_esf_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE1_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410140 RW 0x086F_0EFF
	UINT32 reg_core1_win_esf_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core1_win_esf_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE1_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410150 RW 0x0000_0000
	UINT32 reg_dp_debug_display 			:4; //(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2) 0010: tgen only 0011: bypass	0100: weight(A) 0101: weight(Texture)	0110: A-map 0111: T-map 1000: soft edge gain map	1001: A-map for der 1010: Motion map	1011: Gain A-map	1100: Gain T-map	1101: Texture region map	1110: object map	1111: face map
	UINT32 reg_dp_detour_en 				:1; //(4:4,NA,0) //dp detour enable
	UINT32 resvd0							:3;
	UINT32 reg_dp_buffer_detour_en			:1; //(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1							:23;
	};
}PE_O22F22_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410160 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size				:2; //(1:0,NA,3) //A-map h size
	UINT32 resvd0							:6;
	UINT32 reg_fd_a_map_post_filter_en		:1; //(8:8,NA,0) //post-mmd enable
	UINT32 resvd1							:7;
	UINT32 reg_fd_pre_a_map_h_size			:3; //(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size			:2; //(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution		:3; //(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410164 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410168 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul			:8; //(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul			:8; //(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul 			:8; //(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul			:8; //(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O22F22_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341016C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0 			:8; //(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0 			:8; //(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1 			:8; //(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1 			:8; //(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410170 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0			:8; //(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0			:8; //(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1			:8; //(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1			:8; //(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410174 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0 			:8; //(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0 			:8; //(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1 			:8; //(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1 			:8; //(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410178 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0			:8; //(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0			:8; //(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1			:8; //(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1			:8; //(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341017C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0			:8; //(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0			:8; //(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1			:8; //(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1			:8; //(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410180 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2			:8; //(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2			:8; //(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3			:8; //(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3			:8; //(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O22F22_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410184 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0			:8; //(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0			:8; //(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1			:8; //(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1			:8; //(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410188 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2			:8; //(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2			:8; //(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3			:8; //(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3			:8; //(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O22F22_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341018C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en 			:1; //(0:0,NA,0) //MNR gain for edge gain enable
	UINT32 reg_fd_mnr_gain_t_en 			:1; //(1:1,NA,0) //MNR gain for texture gain enable
	UINT32 resvd0							:2;
	UINT32 reg_fd_mnr_s1_h_expand			:2; //(5:4,NA,1) //s1 h expand
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410190 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min			:8; //(7:0,NA,0) //s1 mmd min
	UINT32 resvd0							:8;
	UINT32 reg_fd_mnr_s2_ratio_max			:8; //(23:16,NA,32) //s1 ratio max
	UINT32 resvd1							:8;
	};
}PE_O22F22_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410194 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0				:8; //(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1				:8; //(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0				:8; //(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1				:8; //(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O22F22_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410198 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0				:8; //(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0				:8; //(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1				:8; //(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1				:8; //(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341019C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2				:8; //(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2				:8; //(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3				:8; //(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3				:8; //(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O22F22_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101A0 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4				:8; //(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4				:8; //(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5				:8; //(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5				:8; //(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O22F22_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101A4 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en			:1; //(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en			:1; //(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd							:30;
	};
}PE_O22F22_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101A8 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio				:8; //(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset				:8; //(15:8,NA,8) //Soft edge offset
	UINT32 resvd							:16;
	};
}PE_O22F22_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101AC RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0 			:8; //(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1 			:8; //(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2 			:8; //(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3 			:8; //(31:24,NA,64) //Soft edge score, x3
	};
}PE_O22F22_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101B0 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0 			:6; //(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0							:2;
	UINT32 reg_fd_soft_score_y1 			:6; //(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1							:2;
	UINT32 reg_fd_soft_score_y2 			:6; //(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2							:2;
	UINT32 reg_fd_soft_score_y3 			:6; //(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3							:2;
	};
}PE_O22F22_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101B4 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel			:2; //(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0							:2;
	UINT32 reg_fd_flat_protect_e_en 		:1; //(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1							:3;
	UINT32 reg_fd_flat_protect_t_en 		:1; //(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2							:23;
	};
}PE_O22F22_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101B8 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0				:8; //(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0				:8; //(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1				:8; //(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1				:8; //(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O22F22_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101C0 RW 0x0000_0001
	UINT32 reg_mp_shp_en					:1; //(0:0,NA,1) //MP enable
	UINT32 resvd							:31;
	};
}PE_O22F22_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101C4 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain				:7; //(6:0,NA,32) //im os gain
	UINT32 resvd0							:1;
	UINT32 reg_mp_im_us_gain				:7; //(14:8,NA,32) //im us gain
	UINT32 resvd1							:1;
	UINT32 reg_mp_im_gain_h 				:8; //(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v 				:8; //(31:24,NA,24) //im gain v
	};
}PE_O22F22_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101C8 RW 0x0000_4000
	UINT32 resvd0							:8;
	UINT32 reg_mp_lap_weight				:8; //(15:8,NA,64) //Laplacian weight
	UINT32 resvd1							:16;
	};
}PE_O22F22_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101CC RW 0x3000_0300
	UINT32 resvd0							:4;
	UINT32 reg_mp_lap_gain_v_7				:4; //(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5				:4; //(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3				:4; //(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1							:4;
	UINT32 reg_mp_lap_gain_h_7				:4; //(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5				:4; //(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3				:4; //(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O22F22_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101D0 RW 0x0000_0000
	UINT32 resvd0							:8;
	UINT32 reg_mp_dbg_sel					:4; //(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain 1001: lum2 gain o.w : reserved
	UINT32 resvd1							:20;
	};
}PE_O22F22_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101D4 RW 0x0002_0100
	UINT32 reg_mp_gb_en 					:1; //(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0							:3;
	UINT32 reg_mp_gb_mode					:1; //(4:4,NA,0) //delta(x-axis) resolution 0: 8bit 1: 10bit
	UINT32 resvd1							:3;
	UINT32 reg_mp_gb_x1 					:8; //(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1 					:8; //(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101D8 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2 					:8; //(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2 					:8; //(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3 					:8; //(23:16,NA,255) //gain balancing, y3
	UINT32 resvd							:8;
	};
}PE_O22F22_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101DC RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0 				:8; //(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1 				:8; //(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0 				:8; //(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1 				:8; //(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O22F22_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101E0 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0					:8; //(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1					:8; //(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2					:8; //(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0 				:8; //(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O22F22_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101E4 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1 				:8; //(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0 				:8; //(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1 				:8; //(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0					:8; //(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_O22F22_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101E8 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1					:8; //(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2					:8; //(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd							:16;
	};
}PE_O22F22_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101EC RW 0x0000_0037
	UINT32 reg_mp_coring_en 				:1; //(0:0,NA,1) //[MP] 0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode				:2; //(2:1,NA,3) //[MP] 00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_mp_coring_input_sel			:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101F0 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b			:7; //(6:0,NA,24) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_mp_coring_gain_e_w			:7; //(14:8,NA,16) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_mp_coring_gain_t_b			:7; //(22:16,NA,32) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_mp_coring_gain_t_w			:7; //(30:24,NA,32) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34101F4 RW 0x0000_F001
	UINT32 reg_apl_iir_en					:1; //(0:0,NA,1) //APL IIR enable
	UINT32 resvd0							:7;
	UINT32 reg_apl_iir_gain 				:8; //(15:8,NA,240) //APL gain
	UINT32 resvd1							:16;
	};
}PE_O22F22_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410200 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en					:1; //(0:0,NA,1) //LC enable
	UINT32 reserved01                       :3;	// reserved
	UINT32 reg_lc_gb_en                     :1;	// 4:4
	UINT32 reserved02                       :3;	// reserved
	UINT32 reg_lc_center_target 			:8; //(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain				:8; //(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain				:8; //(31:24,NA,255) //local gain
	};
}PE_O22F22_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410204 RW 0x2020_4030
	UINT32 reg_lc_gb_y2 					:8; //(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2 					:8; //(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1 					:8; //(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1 					:8; //(31:24,NA,32) //gain balancing, x1
	};
}PE_O22F22_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410208 RW 0xFF30_4000
	UINT32 resvd							:8;
	UINT32 reg_lc_lap_weight				:8; //(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3 					:8; //(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3 					:8; //(31:24,NA,255) //gain balancing, x3
	};
}PE_O22F22_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341020C RW 0x0000_0037
	UINT32 reg_lc_coring_en 				:1; //(0:0,NA,1) //[LC] 0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode				:2; //(2:1,NA,3) //[LC] 00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_lc_coring_input_sel			:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410210 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b			:7; //(6:0,NA,1) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_lc_coring_gain_e_w			:7; //(14:8,NA,1) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_lc_coring_gain_t_b			:7; //(22:16,NA,8) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_lc_coring_gain_t_w			:7; //(30:24,NA,8) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410220 RW 0x1E04_0100
	UINT32 resvd0							:8;
	UINT32 reg_derh_csft_gain				:6; //(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1							:2;
	UINT32 reg_derh_th_gain_edge			:6; //(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2							:2;
	UINT32 reg_derh_th_manual_th			:7; //(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en			:1; //(31:31,NA,0) //reg_th_manual_en
	};
}PE_O22F22_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410224 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size			:3; //(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0							:21;
	UINT32 reg_derh_amean_en				:1; //(24:24,NA,1) //reg_amean_en
	UINT32 resvd1							:1;
	UINT32 reg_derh_edge_filter_v_tap		:2; //(27:26,NA,1) //edge filter V tap	0: 5tap 1: 3tap others: 1tap
	UINT32 resvd2							:3;
	UINT32 reg_derh_edge_y_filter_en		:1; //(31:31,NA,1) //edge_Y_filter en
	};
}PE_O22F22_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410228 RW 0x0004_0400
	UINT32 resvd0							:8;
	UINT32 reg_derh_edge_filter_gain_w		:6; //(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1							:2;
	UINT32 reg_derh_edge_filter_gain_b		:6; //(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2							:10;
	};
}PE_O22F22_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341022C RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410230 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410234 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410238 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0 				:8; //(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0 				:8; //(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1 				:8; //(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1 				:8; //(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O22F22_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341023C RW 0x8080_5060
	UINT32 reg_der_a_lut_y2 				:8; //(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2 				:8; //(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3 				:8; //(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3 				:8; //(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O22F22_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410240 RW 0x0000_0001
	UINT32 reg_sp_shp_en					:1; //(0:0,NA,1) //SP enable
	UINT32 resvd							:31;
	};
}PE_O22F22_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410244 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain				:7; //(6:0,NA,32) //im os gain
	UINT32 resvd0							:1;
	UINT32 reg_sp_im_us_gain				:7; //(14:8,NA,32) //im us gain
	UINT32 resvd1							:1;
	UINT32 reg_sp_im_gain_h 				:8; //(23:16,NA,32) //im gain h
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410248 RW 0x0000_4000
	UINT32 resvd0							:8;
	UINT32 reg_sp_lap_weight				:8; //(15:8,NA,64) //Laplacian weight
	UINT32 resvd1							:16;
	};
}PE_O22F22_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341024C RW 0x3000_0000
	UINT32 resvd							:20;
	UINT32 reg_sp_lap_gain_h_7				:4; //(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5				:4; //(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3				:4; //(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O22F22_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410250 RW 0x0000_0000
	UINT32 resvd0							:8;
	UINT32 reg_sp_dbg_sel					:4; //(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain 1001: lum2 gain o.w : reserved
	UINT32 resvd1							:20;
	};
}PE_O22F22_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410254 RW 0x0002_0101
	UINT32 reg_sp_gb_en 					:1; //(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0							:3;
	UINT32 reg_sp_gb_mode					:1; //(4:4,NA,0) //delta(x-axis) resolution 0: 8bit 1: 10bit
	UINT32 resvd1							:3;
	UINT32 reg_sp_gb_x1 					:8; //(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1 					:8; //(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410258 RW 0x0080_1008
	UINT32 reg_sp_gb_x2 					:8; //(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2 					:8; //(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3 					:8; //(23:16,NA,128) //gain balancing, y3
	UINT32 resvd							:8;
	};
}PE_O22F22_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341025C RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0 				:8; //(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1 				:8; //(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0 				:8; //(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1 				:8; //(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O22F22_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410260 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0					:8; //(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1					:8; //(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2					:8; //(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0 				:8; //(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O22F22_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410264 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1 				:8; //(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0 				:8; //(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1 				:8; //(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0					:8; //(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_O22F22_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410268 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1					:8; //(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2					:8; //(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd							:16;
	};
}PE_O22F22_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341026C RW 0x0000_0037
	UINT32 reg_sp_coring_en 				:1; //(0:0,NA,1) //[SP] 0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode				:2; //(2:1,NA,3) //[SP] 00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_sp_coring_input_sel			:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410270 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b			:7; //(6:0,NA,24) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_sp_coring_gain_e_w			:7; //(14:8,NA,16) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_sp_coring_gain_t_b			:7; //(22:16,NA,8) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_sp_coring_gain_t_w			:7; //(30:24,NA,8) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410280 RW 0x0000_8028
	UINT32 reg_ptiv_enable					:1; //(0:0,NA,0) //PTI-V enable
	UINT32 resvd0							:1;
	UINT32 reg_ptiv_mm_tap_size 			:2; //(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size			:2; //(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode 				:1; //(6:6,NA,0) //ti mode
	UINT32 resvd1							:1;
	UINT32 reg_ptiv_master_gain 			:8; //(15:8,NA,128) //master gain
	UINT32 resvd2							:16;
	};
}PE_O22F22_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410284 RW 0x0000_FF00
	UINT32 reg_ptih_enable					:1; //(0:0,NA,0) //PTI-H enable
	UINT32 resvd0							:1;
	UINT32 reg_ptih_mm_tap_size 			:2; //(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size			:2; //(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode 				:1; //(6:6,NA,0) //ti mode
	UINT32 resvd1							:1;
	UINT32 reg_ptih_master_gain 			:8; //(15:8,NA,255) //master gain
	UINT32 resvd2							:16;
	};
}PE_O22F22_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410288 RW 0x0000_0037
	UINT32 reg_pti_coring_en				:1; //(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode				:2; //(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_pti_coring_input_sel 		:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341028C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b			:7; //(6:0,NA,24) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_pti_coring_gain_e_w			:7; //(14:8,NA,16) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_pti_coring_gain_t_b			:7; //(22:16,NA,0) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_pti_coring_gain_t_w			:7; //(30:24,NA,0) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410290 RW 0x1010_2014
	UINT32 reg_sti_enable					:1; //(0:0,NA,0) //STI enable
	UINT32 reg_sti_debug_map_en 			:1; //(1:1,NA,0) //debug map enable
	UINT32 reg_sti_mm_tap_size				:2; //(3:2,NA,1) //mm tap size
	UINT32 reg_sti_avg_tap_size 			:2; //(5:4,NA,1) //avg tap size
	UINT32 reg_sti_ti_mode					:1; //(6:6,NA,0) //ti mode
	UINT32 resvd							:1;
	UINT32 reg_sti_master_gain				:8; //(15:8,NA,32) //master gain
	UINT32 reg_sti_texture_gain 			:8; //(23:16,NA,16) //texture gain
	UINT32 reg_sti_edge_gain				:8; //(31:24,NA,16) //edge gain
	};
}PE_O22F22_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102A0 RW 0x8000_0011
	UINT32 reg_tgen_on_off					:1; //(0:0,NA,1) //
	UINT32 resvd0							:3;
	UINT32 reg_tgen_initial_seed_mode		:1; //(4:4,NA,1) //
	UINT32 resvd1							:3;
	UINT32 reg_tgen_dbg_en					:1; //(8:8,NA,0) //
	UINT32 resvd2							:7;
	UINT32 reg_tgen_table_sel				:4; //(19:16,NA,0) //
	UINT32 resvd3							:4;
	UINT32 reg_tgen_master_gain 			:8; //(31:24,NA,128) //
	};
}PE_O22F22_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102A4 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound			:5; //(4:0,NA,16) //
	UINT32 resvd0							:3;
	UINT32 reg_tgen_delta_l_bound			:5; //(12:8,NA,8) //
	UINT32 resvd1							:3;
	UINT32 reg_tgen_delta_max				:7; //(22:16,NA,64) //
	UINT32 resvd2							:1;
	UINT32 reg_tgen_delta_scale 			:3; //(26:24,NA,6) //
	UINT32 resvd3							:5;
	};
}PE_O22F22_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102A8 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th					:8; //(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr 			:4; //(11:8,NA,5) //
	UINT32 resvd0							:4;
	UINT32 reg_tgen_lc_ldr_th				:6; //(21:16,NA,63) //
	UINT32 resvd1							:10;
	};
}PE_O22F22_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102AC RW 0x0000_48AB
	UINT32 reg_core0_tgen_rand_init_val_c0	:32;	//(31:0,NA,18603) //
	};
}PE_O22F22_SHP_CORE0_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102B0 RW 0x0000_48AB
	UINT32 reg_core0_tgen_rand_init_val_c1	:32;	//(31:0,NA,18603) //
	};
}PE_O22F22_SHP_CORE0_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102B4 RW 0x0000_48AB
	UINT32 reg_core1_tgen_rand_init_val_c0	:32;	//(31:0,NA,18603) //
	};
}PE_O22F22_SHP_CORE1_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102B8 RW 0x0000_48AB
	UINT32 reg_core1_tgen_rand_init_val_c1	:32;	//(31:0,NA,18603) //
	};
}PE_O22F22_SHP_CORE1_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102BC RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio				:3; //(2:0,NA,4) //
	UINT32 resvd0							:5;
	UINT32 reg_tgen_dr_th					:6; //(13:8,NA,31) //
	UINT32 resvd1							:2;
	UINT32 reg_tgen_mm_offset				:5; //(20:16,NA,2) //
	UINT32 resvd2							:3;
	UINT32 reg_tgen_mm_sel_mode 			:2; //(25:24,NA,2) //
	UINT32 resvd3							:6;
	};
}PE_O22F22_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102C0 RW 0x0008_0050
	UINT32 resvd0							:16;
	UINT32 reg_tgen_gs_rnd					:5; //(20:16,NA,8) //
	UINT32 resvd1							:3;
	UINT32 reg_tgen_gs_mm					:5; //(28:24,NA,0) //
	UINT32 resvd2							:3;
	};
}PE_O22F22_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102C4 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2			:6; //(5:0,NA,0) //
	UINT32 resvd0							:2;
	UINT32 reg_tgen_blur_coef_x1			:6; //(13:8,NA,8) //
	UINT32 resvd1							:10;
	UINT32 reg_tgen_blur_coef_x0			:6; //(29:24,NA,26) //
	UINT32 resvd2							:2;
	};
}PE_O22F22_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102C8 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2			:6; //(5:0,NA,0) //
	UINT32 resvd0							:2;
	UINT32 reg_tgen_blur_coef_y1			:6; //(13:8,NA,8) //
	UINT32 resvd1							:10;
	UINT32 reg_tgen_blur_coef_y0			:6; //(29:24,NA,26) //
	UINT32 resvd2							:2;
	};
}PE_O22F22_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102CC RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain			:5; //(4:0,NA,31) //
	UINT32 resvd0							:3;
	UINT32 reg_tgen_map_detail_gain 		:5; //(12:8,NA,31) //
	UINT32 resvd1							:3;
	UINT32 reg_tgen_map_offset				:8; //(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise				:6; //(29:24,NA,63) //
	UINT32 resvd2							:2;
	};
}PE_O22F22_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102D0 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7					:4; //(3:0,NA,15) //
	UINT32 reg_tgen_gain6					:4; //(7:4,NA,15) //
	UINT32 reg_tgen_gain5					:4; //(11:8,NA,13) //
	UINT32 reg_tgen_gain4					:4; //(15:12,NA,12) //
	UINT32 reg_tgen_gain3					:4; //(19:16,NA,11) //
	UINT32 reg_tgen_gain2					:4; //(23:20,NA,10) //
	UINT32 reg_tgen_gain1					:4; //(27:24,NA,8) //
	UINT32 reg_tgen_gain0					:4; //(31:28,NA,4) //
	};
}PE_O22F22_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102D4 RW 0x0000_0037
	UINT32 reg_tgen_coring_en				:1; //(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode 			:2; //(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_tgen_coring_input_sel		:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102D8 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b 		:7; //(6:0,NA,0) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_tgen_coring_gain_e_w 		:7; //(14:8,NA,0) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_tgen_coring_gain_t_b 		:7; //(22:16,NA,16) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_tgen_coring_gain_t_w 		:7; //(30:24,NA,16) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102E0 RW 0x0003_0411
	UINT32 reg_snr_blur_en					:1; //(0:0,NA,1) //SNR enable
	UINT32 resvd0							:3;
	UINT32 reg_snr_blur_sel 				:2; //(5:4,NA,1) //filter tap	00: 3x3 01: 5x5 10: 9x5
	UINT32 resvd1							:2;
	UINT32 reg_snr_bilateral_th 			:8; //(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode				:3; //(18:16,NA,3) //SNR blur mode	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2							:13;
	};
}PE_O22F22_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102F0 RW 0x0000_0001
	UINT32 reg_dctp_en						:1; //(0:0,NA,1) //DCT peaking enable
	UINT32 resvd							:31;
	};
}PE_O22F22_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102F4 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0			:12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt0_coef_1			:12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102F8 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2			:12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt0_coef_3			:12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34102FC RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4			:12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt0_coef_5			:12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410300 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6			:12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt0_coef_7			:12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410304 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0			:12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt1_coef_1			:12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410308 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2			:12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt1_coef_3			:12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341030C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4			:12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt1_coef_5			:12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410310 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6			:12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt1_coef_7			:12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410314 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0			:12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt2_coef_1			:12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410318 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2			:12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt2_coef_3			:12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341031C RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4			:12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt2_coef_5			:12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410320 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6			:12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt2_coef_7			:12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410324 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0			:12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt3_coef_1			:12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410328 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2			:12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt3_coef_3			:12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341032C RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4			:12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt3_coef_5			:12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410330 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6			:12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt3_coef_7			:12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410334 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0			:12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt4_coef_1			:12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410338 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2			:12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt4_coef_3			:12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341033C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4			:12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt4_coef_5			:12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410340 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6			:12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt4_coef_7			:12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410344 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0			:12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt5_coef_1			:12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410348 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2			:12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt5_coef_3			:12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341034C RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4			:12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt5_coef_5			:12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410350 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6			:12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0							:4;
	UINT32 reg_dctp_filt5_coef_7			:12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410354 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0 			:8; //(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1 			:8; //(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2 			:8; //(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3 			:8; //(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O22F22_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410358 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4 			:8; //(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5 			:8; //(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd							:16;
	};
}PE_O22F22_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341035C RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0 			:8; //(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0 			:8; //(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1 			:8; //(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1 			:8; //(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O22F22_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410360 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2 			:8; //(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2 			:8; //(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3 			:8; //(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3 			:8; //(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O22F22_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410364 RW 0x0000_0080
	UINT32 reg_dctp_gain					:8; //(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410368 RW 0x0000_0037
	UINT32 reg_dctp_coring_en				:1; //(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode 			:2; //(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_dtcp_coring_input_sel		:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341036C RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b 		:7; //(6:0,NA,0) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_dctp_coring_gain_e_w 		:7; //(14:8,NA,0) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_dctp_coring_gain_t_b 		:7; //(22:16,NA,16) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_dctp_coring_gain_t_w 		:7; //(30:24,NA,16) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410370 RW 0x0000_0001
	UINT32 reg_nntg_en						:1; //(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0							:3;
	UINT32 reg_nntg_debug_mode				:2; //(5:4,NA,0) //4K nano-noise debug mode 0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410374 RW 0x0000_159C
	UINT32 reg_core0_nntg_lsfr_init_1st_c0	:32;	//(31:0,NA,5532) //4K nano-noise LSFR init (1st)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410378 RW 0x2CA3_7199
	UINT32 reg_core0_nntg_lsfr_init_2nd_c0	:32;	//(31:0,NA,748908953) //4K nano-noise LSFR init (2nd)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341037C RW 0x3236_3B62
	UINT32 reg_core0_nntg_lsfr_init_3rd_c0	:32;	//(31:0,NA,842414946) //4K nano-noise LSFR init (3rd)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410380 RW 0xFD1C_D00A
	UINT32 reg_core0_nntg_lsfr_init_4th_c0	:32;	//(31:0,NA,4246523914) //4K nano-noise LSFR init (4th)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410384 RW 0x8C3C_2327
	UINT32 reg_core0_nntg_lsfr_init_5th_c0	:32;	//(31:0,NA,2352751399) //4K nano-noise LSFR init (5th)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410388 RW 0xF275_9828
	UINT32 reg_core0_nntg_lsfr_init_1st_c1	:32;	//(31:0,NA,4067792936) //4K nano-noise LSFR init (1st)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341038C RW 0xFEEA_5094
	UINT32 reg_core0_nntg_lsfr_init_2nd_c1	:32;	//(31:0,NA,4276768916) //4K nano-noise LSFR init (2nd)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410390 RW 0xECBE_ACAA
	UINT32 reg_core0_nntg_lsfr_init_3rd_c1	:32;	//(31:0,NA,3971919018) //4K nano-noise LSFR init (3rd)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410394 RW 0xD9C5_DFEA
	UINT32 reg_core0_nntg_lsfr_init_4th_c1	:32;	//(31:0,NA,3653623786) //4K nano-noise LSFR init (4th)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410398 RW 0x23E8_D99E
	UINT32 reg_core0_nntg_lsfr_init_5th_c1	:32;	//(31:0,NA,602462622) //4K nano-noise LSFR init (5th)
	};
}PE_O22F22_SHP_CORE0_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341039C RW 0x0000_159C
	UINT32 reg_core1_nntg_lsfr_init_1st_c0	:32;	//(31:0,NA,5532) //4K nano-noise LSFR init (1st)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103A0 RW 0x2CA3_7199
	UINT32 reg_core1_nntg_lsfr_init_2nd_c0	:32;	//(31:0,NA,748908953) //4K nano-noise LSFR init (2nd)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103A4 RW 0x3236_3B62
	UINT32 reg_core1_nntg_lsfr_init_3rd_c0	:32;	//(31:0,NA,842414946) //4K nano-noise LSFR init (3rd)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103A8 RW 0xFD1C_D00A
	UINT32 reg_core1_nntg_lsfr_init_4th_c0	:32;	//(31:0,NA,4246523914) //4K nano-noise LSFR init (4th)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103AC RW 0x8C3C_2327
	UINT32 reg_core1_nntg_lsfr_init_5th_c0	:32;	//(31:0,NA,2352751399) //4K nano-noise LSFR init (5th)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103B0 RW 0xF275_9828
	UINT32 reg_core1_nntg_lsfr_init_1st_c1	:32;	//(31:0,NA,4067792936) //4K nano-noise LSFR init (1st)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103B4 RW 0xFEEA_5094
	UINT32 reg_core1_nntg_lsfr_init_2nd_c1	:32;	//(31:0,NA,4276768916) //4K nano-noise LSFR init (2nd)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103B8 RW 0xECBE_ACAA
	UINT32 reg_core1_nntg_lsfr_init_3rd_c1	:32;	//(31:0,NA,3971919018) //4K nano-noise LSFR init (3rd)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103BC RW 0xD9C5_DFEA
	UINT32 reg_core1_nntg_lsfr_init_4th_c1	:32;	//(31:0,NA,3653623786) //4K nano-noise LSFR init (4th)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103C0 RW 0x23E8_D99E
	UINT32 reg_core1_nntg_lsfr_init_5th_c1	:32;	//(31:0,NA,602462622) //4K nano-noise LSFR init (5th)
	};
}PE_O22F22_SHP_CORE1_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103C4 RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio				:8; //(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max				:7; //(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0							:1;
	UINT32 reg_nntg_rand_sum_max			:8; //(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1							:8;
	};
}PE_O22F22_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103C8 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00			:4; //(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01			:4; //(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02			:4; //(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0							:4;
	UINT32 reg_nntg_rand_coef_g10			:4; //(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11			:4; //(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12			:4; //(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103CC RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20			:4; //(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21			:4; //(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22			:4; //(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0							:4;
	UINT32 reg_nntg_nano_coef_g00			:4; //(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01			:4; //(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02			:4; //(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103D0 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10			:4; //(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11			:4; //(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12			:4; //(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0							:4;
	UINT32 reg_nntg_nano_coef_g20			:4; //(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21			:4; //(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22			:4; //(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103D4 RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0 			:8; //(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0 			:8; //(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1 			:8; //(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1 			:8; //(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O22F22_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103D8 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2 			:8; //(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2 			:8; //(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3 			:8; //(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3 			:8; //(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O22F22_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103DC RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0 			:8; //(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0 			:8; //(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1 			:8; //(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1 			:8; //(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O22F22_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103E0 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2 			:8; //(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2 			:8; //(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3 			:8; //(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3 			:8; //(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O22F22_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103E4 RW 0xFF10_088C
	UINT32 reg_nntg_random_gain 			:8; //(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain			:8; //(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain				:8; //(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain			:8; //(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O22F22_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103E8 RW 0x0000_0037
	UINT32 reg_nntg_coring_en				:1; //(0:0,NA,1) //[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode 			:2; //(2:1,NA,3) //[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only 11: enable both edge/texture peaking
	UINT32 resvd0							:1;
	UINT32 reg_nntg_coring_input_sel		:2; //(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1							:26;
	};
}PE_O22F22_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103EC RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b 		:7; //(6:0,NA,0) //edge black gain
	UINT32 resvd0							:1;
	UINT32 reg_nntg_coring_gain_e_w 		:7; //(14:8,NA,0) //edge white gain
	UINT32 resvd1							:1;
	UINT32 reg_nntg_coring_gain_t_b 		:7; //(22:16,NA,16) //texture black gain
	UINT32 resvd2							:1;
	UINT32 reg_nntg_coring_gain_t_w 		:7; //(30:24,NA,16) //texture white gain
	UINT32 resvd3							:1;
	};
}PE_O22F22_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103F0 RW 0x0000_0280
	UINT32 reg_dp_sum_gain					:8; //(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode				:2; //(9:8,NA,2) //0: 8bit mode 	1: 9bit mode	2: 10bit mode (default)
	UINT32 resvd							:22;
	};
}PE_O22F22_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103F4 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0				:8; //(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0				:8; //(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1				:8; //(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1				:8; //(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_O22F22_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103F8 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2				:8; //(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2				:8; //(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3				:8; //(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3				:8; //(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_O22F22_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34103FC RW 0x4080_0070
	UINT32 reg_obj_dct_delta_lut_y0 		:8; //(7:0,NA,112) //object dct LUT for delta control, y0
	UINT32 reg_obj_dct_delta_lut_x0 		:8; //(15:8,NA,0) //object dct LUT for delta control, x0
	UINT32 reg_obj_dct_delta_lut_y1 		:8; //(23:16,NA,128) //object dct LUT for delta control, y1
	UINT32 reg_obj_dct_delta_lut_x1 		:8; //(31:24,NA,64) //object dct LUT for delta control, x1
	};
}PE_O22F22_SHP_DP_SUM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410400 RW 0xffa0_6090
	UINT32 reg_obj_dct_delta_lut_y2 		:8; //(7:0,NA,144) //object dct LUT for delta control, y2
	UINT32 reg_obj_dct_delta_lut_x2 		:8; //(15:8,NA,96) //object dct LUT for delta control, x2
	UINT32 reg_obj_dct_delta_lut_y3 		:8; //(23:16,NA,160) //object dct LUT for delta control, y3
	UINT32 reg_obj_dct_delta_lut_x3 		:8; //(31:24,NA,255) //object dct LUT for delta control, x3
	};
}PE_O22F22_SHP_DP_SUM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410404 RW 0x4080_0070
	UINT32 reg_obj_tgen_delta_lut_y0		:8; //(7:0,NA,112) //object tgen LUT for delta control, y0
	UINT32 reg_obj_tgen_delta_lut_x0		:8; //(15:8,NA,0) //object tgen LUT for delta control, x0
	UINT32 reg_obj_tgen_delta_lut_y1		:8; //(23:16,NA,128) //object tgen LUT for delta control, y1
	UINT32 reg_obj_tgen_delta_lut_x1		:8; //(31:24,NA,64) //object tgen LUT for delta control, x1
	};
}PE_O22F22_SHP_DP_SUM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410408 RW 0xffb0_6090
	UINT32 reg_obj_tgen_delta_lut_y2		:8; //(7:0,NA,144) //object tgen LUT for delta control, y2
	UINT32 reg_obj_tgen_delta_lut_x2		:8; //(15:8,NA,96) //object tgen LUT for delta control, x2
	UINT32 reg_obj_tgen_delta_lut_y3		:8; //(23:16,NA,176) //object tgen LUT for delta control, y3
	UINT32 reg_obj_tgen_delta_lut_x3		:8; //(31:24,NA,255) //object tgen LUT for delta control, x3
	};
}PE_O22F22_SHP_DP_SUM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341040C RW 0x4080_0070
	UINT32 reg_obj_lc_delta_lut_y0			:8; //(7:0,NA,112) //object local contrast LUT for delta control, y0
	UINT32 reg_obj_lc_delta_lut_x0			:8; //(15:8,NA,0) //object local contrast LUT for delta control, x0
	UINT32 reg_obj_lc_delta_lut_y1			:8; //(23:16,NA,128) //object local contrast LUT for delta control, y1
	UINT32 reg_obj_lc_delta_lut_x1			:8; //(31:24,NA,64) //object local contrast LUT for delta control, x1
	};
}PE_O22F22_SHP_DP_SUM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410410 RW 0xffa0_6090
	UINT32 reg_obj_lc_delta_lut_y2			:8; //(7:0,NA,144) //object local contrast LUT for delta control, y2
	UINT32 reg_obj_lc_delta_lut_x2			:8; //(15:8,NA,96) //object local contrast LUT for delta control, x2
	UINT32 reg_obj_lc_delta_lut_y3			:8; //(23:16,NA,160) //object local contrast LUT for delta control, y3
	UINT32 reg_obj_lc_delta_lut_x3			:8; //(31:24,NA,255) //object local contrast LUT for delta control, x3
	};
}PE_O22F22_SHP_DP_SUM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410414 RW 0x2828_0000
	UINT32 reg_dp_sum_cg_lut_y0 			:8; //(7:0,NA,0) //dp_sum LUT for delta_cg control, y0
	UINT32 reg_dp_sum_cg_lut_x0 			:8; //(15:8,NA,0) //dp_sum LUT for delta_cg control, x0
	UINT32 reg_dp_sum_cg_lut_y1 			:8; //(23:16,NA,40) //dp_sum LUT for delta_cg control, y1
	UINT32 reg_dp_sum_cg_lut_x1 			:8; //(31:24,NA,40) //dp_sum LUT for delta_cg control, x1
	};
}PE_O22F22_SHP_DP_SUM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410418 RW 0xFFFF_5050
	UINT32 reg_dp_sum_cg_lut_y2 			:8; //(7:0,NA,80) //dp_sum LUT for delta_cg control, y2
	UINT32 reg_dp_sum_cg_lut_x2 			:8; //(15:8,NA,80) //dp_sum LUT for delta_cg control, x2
	UINT32 reg_dp_sum_cg_lut_y3 			:8; //(23:16,NA,255) //dp_sum LUT for delta_cg control, y3
	UINT32 reg_dp_sum_cg_lut_x3 			:8; //(31:24,NA,255) //dp_sum LUT for delta_cg control, x3
	};
}PE_O22F22_SHP_DP_SUM_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410420 RW 0x0000_0001
	UINT32 reg_psp_obj_en					:1; //(0:0,NA,1) //PSP object contrast enable
	UINT32 resvd							:31;
	};
}PE_O22F22_SHP_PSP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410424 RW 0x2828_0000
	UINT32 reg_dp_sum_obj_lut_y0			:8; //(7:0,NA,0) //dp_sum LUT for object control, y0
	UINT32 reg_dp_sum_obj_lut_x0			:8; //(15:8,NA,0) //dp_sum LUT for object control, x0
	UINT32 reg_dp_sum_obj_lut_y1			:8; //(23:16,NA,40) //dp_sum LUT for object control, y1
	UINT32 reg_dp_sum_obj_lut_x1			:8; //(31:24,NA,40) //dp_sum LUT for object control, x1
	};
}PE_O22F22_SHP_DP_SUM_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410428 RW 0xFFFF_5050
	UINT32 reg_dp_sum_obj_lut_y2			:8; //(7:0,NA,80) //dp_sum LUT for object control, y2
	UINT32 reg_dp_sum_obj_lut_x2			:8; //(15:8,NA,80) //dp_sum LUT for object control, x2
	UINT32 reg_dp_sum_obj_lut_y3			:8; //(23:16,NA,255) //dp_sum LUT for object control, y3
	UINT32 reg_dp_sum_obj_lut_x3			:8; //(31:24,NA,255) //dp_sum LUT for object control, x3
	};
}PE_O22F22_SHP_DP_SUM_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410430 RW 0x0000_0000
	UINT32 reg_core0_core0win_dp_win0_en	:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_core0win_dp_win1_en	:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_core0win_dp_win01_en	:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_core0win_dp_win_outside :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_core0win_dp_win_en 	:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_core0win_dp_bdr_alpha	:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_core0win_dp_bdr_wid	:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_core0win_dp_bdr_en 	:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_core0win_dp_cr5		:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_core0win_dp_cb5		:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_core0win_dp_yy6		:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410434 RW 0x0000_0000
	UINT32 reg_core0_core0win_dp_win_w0_x0	:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core0_core0win_dp_win_w0_y0	:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE0_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410438 RW 0x086F_0EFF
	UINT32 reg_core0_core0win_dp_win_w0_x1	:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core0_core0win_dp_win_w0_y1	:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE0_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341043C RW 0x0000_0000
	UINT32 reg_core0_core0win_dp_win_w1_x0	:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core0_core0win_dp_win_w1_y0	:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE0_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410440 RW 0x086F_0EFF
	UINT32 reg_core0_win_dp_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core0_win_dp_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE0_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410444 RW 0x0000_0000
	UINT32 reg_core1_core1win_dp_win0_en	:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core1_core1win_dp_win1_en	:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core1_core1win_dp_win01_en	:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core1_core1win_dp_win_outside :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_core1win_dp_win_en 	:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core1_core1win_dp_bdr_alpha	:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core1_core1win_dp_bdr_wid	:2; //(14:13,NA,0) //border width
	UINT32 reg_core1_core1win_dp_bdr_en 	:1; //(15:15,NA,0) //border enable
	UINT32 reg_core1_core1win_dp_cr5		:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core1_core1win_dp_cb5		:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core1_core1win_dp_yy6		:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410448 RW 0x0000_0000
	UINT32 reg_core1_core1win_dp_win_w0_x0	:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core1_core1win_dp_win_w0_y0	:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE1_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341044C RW 0x086F_0EFF
	UINT32 reg_core1_core1win_dp_win_w0_x1	:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core1_core1win_dp_win_w0_y1	:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE1_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410450 RW 0x0000_0000
	UINT32 reg_core1_core1win_dp_win_w1_x0	:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core1_core1win_dp_win_w1_y0	:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE1_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410454 RW 0x086F_0EFF
	UINT32 reg_core1_win_dp_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core1_win_dp_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE1_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410460 RW 0x0432_0c40
	UINT32 reg_region_text_en				:1; //(0:0,NA,0) //region texture enable
	UINT32 resvd0							:3;
	UINT32 reg_region_text_cutres			:3; //(6:4,NA,4) //
	UINT32 resvd1							:1;
	UINT32 reg_region_text_add_offset		:8; //(15:8,NA,12) //
	UINT32 reg_region_text_add_max			:8; //(23:16,NA,50) //
	UINT32 reg_region_text_cuthif			:3; //(26:24,NA,4) //
	UINT32 resvd2							:5;
	};
}PE_O22F22_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410464 RW 0x0f50_0410
	UINT32 reg_region_text_lut_y0			:8; //(7:0,NA,16) //region texture LUT , y0
	UINT32 reg_region_text_lut_x0			:8; //(15:8,NA,4) //region texture LUT , x0
	UINT32 reg_region_text_lut_y1			:8; //(23:16,NA,80) //region texture LUT , y1
	UINT32 reg_region_text_lut_x1			:8; //(31:24,NA,15) //region texture LUT , x1
	};
}PE_O22F22_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410468 RW 0x46c8_2380
	UINT32 reg_region_text_lut_y2			:8; //(7:0,NA,128) //region texture LUT , y2
	UINT32 reg_region_text_lut_x2			:8; //(15:8,NA,35) //region texture LUT , x2
	UINT32 reg_region_text_lut_y3			:8; //(23:16,NA,200) //region texture LUT , y3
	UINT32 reg_region_text_lut_x3			:8; //(31:24,NA,70) //region texture LUT , x3
	};
}PE_O22F22_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341046C RW 0x0000_ff00
	UINT32 reg_tmap_temp_iir_en 			:1; //(0:0,NA,0) //TMAP temporal process enable
	UINT32 resvd0							:3;
	UINT32 reg_tmap_temp_init_en			:1; //(4:4,NA,0) //TMAP temporal process initial value setting enable
	UINT32 resvd1							:3;
	UINT32 reg_tmap_temp_init_val			:8; //(15:8,NA,255) //TMAP temporal process initial value
	UINT32 resvd2							:8;
	UINT32 reg_tmap_stat_sel				:1; //(24:24,NA,0) //TMAP temporal process status selection 0 : original tmap status	1 : iir tmap status
	UINT32 resvd3							:7;
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410470 RW 0x2840_0a00
	UINT32 reg_tmap_temp_prev_lut_y0		:8; //(7:0,NA,0) //tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0		:8; //(15:8,NA,10) //tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1		:8; //(23:16,NA,64) //tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1		:8; //(31:24,NA,40) //tmap temporal previous blend LUT , x1
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410474 RW 0x5080_3c60
	UINT32 reg_tmap_temp_prev_lut_y2		:8; //(7:0,NA,96) //tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2		:8; //(15:8,NA,60) //tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3		:8; //(23:16,NA,128) //tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3		:8; //(31:24,NA,80) //tmap temporal previous blend LUT , x3
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410478 RW 0x08d0_00c0
	UINT32 reg_tmap_temp_iir_pos_lut_y0 	:8; //(7:0,NA,192) //tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0 	:8; //(15:8,NA,0) //tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1 	:8; //(23:16,NA,208) //tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1 	:8; //(31:24,NA,8) //tmap temporal iir positive LUT , x1
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341047C RW 0x30f0_10e0
	UINT32 reg_tmap_temp_iir_pos_lut_y2 	:8; //(7:0,NA,224) //tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2 	:8; //(15:8,NA,16) //tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3 	:8; //(23:16,NA,240) //tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3 	:8; //(31:24,NA,48) //tmap temporal iir positive LUT , x3
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410480 RW 0x80c0_60d0
	UINT32 reg_tmap_temp_iir_pos_lut_y4 	:8; //(7:0,NA,208) //tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4 	:8; //(15:8,NA,96) //tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5 	:8; //(23:16,NA,192) //tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5 	:8; //(31:24,NA,128) //tmap temporal iir positive LUT , x5
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410484 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0 	:8; //(7:0,NA,128) //tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0 	:8; //(15:8,NA,0) //tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1 	:8; //(23:16,NA,112) //tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1 	:8; //(31:24,NA,8) //tmap temporal iir negative LUT , x1
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410488 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2 	:8; //(7:0,NA,96) //tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2 	:8; //(15:8,NA,16) //tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3 	:8; //(23:16,NA,80) //tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3 	:8; //(31:24,NA,24) //tmap temporal iir negative LUT , x3
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341048C RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4 	:8; //(7:0,NA,64) //tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4 	:8; //(15:8,NA,32) //tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5 	:8; //(23:16,NA,0) //tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5 	:8; //(31:24,NA,64) //tmap temporal iir negative LUT , x5
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410490 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x		:12;	//(11:0,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd0							:4;
	UINT32 reg_tmap_stat_win0_start_y		:12;	//(27:16,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410494 RW 0x086f_077f
	UINT32 reg_tmap_stat_win0_end_x 		:12;	//(11:0,NA,1919) //tmap temporal texture status window position (window0)
	UINT32 resvd0							:4;
	UINT32 reg_tmap_stat_win0_end_y 		:12;	//(27:16,NA,2159) //tmap temporal texture status window position (window0)
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410498 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x		:12;	//(11:0,NA,1920) //tmap temporal texture status window position (window1)
	UINT32 resvd0							:4;
	UINT32 reg_tmap_stat_win1_start_y		:12;	//(27:16,NA,0) //tmap temporal texture status window position (window1)
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341049C RW 0x0438_0eff
	UINT32 reg_tmap_stat_win1_end_x 		:12;	//(11:0,NA,3839) //tmap temporal texture status window position (window1)
	UINT32 resvd0							:4;
	UINT32 reg_tmap_stat_win1_end_y 		:12;	//(27:16,NA,1080) //tmap temporal texture status window position (window1)
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104A0 RW 0x8010_0179
	UINT32 reg_dj_edf_en					:1; //(0:0,NA,1) //edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en				:1; //(1:1,NA,0) //H/V de-jagging enable
	UINT32 resvd0							:1;
	UINT32 reg_dj_edge_adaptive_en			:1; //(3:3,NA,1) //edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode		:1; //(4:4,NA,1) //0: sum of (cur - center) 1: sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection 		:1; //(5:5,NA,1) //L-type protection
	UINT32 reg_dj_soft_en					:1; //(6:6,NA,1) //Soft DJ enable
	UINT32 resvd1							:1;
	UINT32 reg_dj_count_diff_th 			:5; //(12:8,NA,1) //matchness threshold for edge-direction decision
	UINT32 resvd2							:3;
	UINT32 reg_dj_output_mux				:3; //(18:16,NA,0) //000: normal display (hard decision)	001: direction map	010: edge gain	011: g0 gain	100: g1 gain	101: final gain
	UINT32 reg_dj_buffer_detour_en			:1; //(19:19,NA,0) //dj buffer detour enable
	UINT32 reg_dj_center_blur_mode			:2; //(21:20,NA,1) //center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode				:1; //(22:22,NA,0) //neighbor-pixel averaging : mode for dual edges 0: use 12 direction results 1: use 36 direction results
	UINT32 reg_dj_detour_en 				:1; //(23:23,NA,0) //dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th	:8; //(31:24,NA,128) //line-variation threshold for edge-direction decision
	};
}PE_O22F22_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104A4 RW 0x0080_0000
	UINT32 reg_dj_level_th					:8; //(7:0,NA,0) //g0: level threshold
	UINT32 resvd0							:8;
	UINT32 reg_dj_n_avg_gain				:8; //(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1							:8;
	};
}PE_O22F22_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104A8 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min				:5; //(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0							:3;
	UINT32 reg_dj_g0_mul					:5; //(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1							:19;
	};
}PE_O22F22_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104AC RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min			:8; //(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul					:7; //(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd							:1;
	UINT32 reg_dj_edge_min					:8; //(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul					:8; //(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O22F22_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104B0 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1				:1; //(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2				:1; //(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3				:1; //(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4				:1; //(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd							:28;
	};
}PE_O22F22_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104B4 RW 0x0000_0000
	UINT32 reg_dj_pattern0_0_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [0][0]
	UINT32 reg_dj_pattern0_0_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [0][1]
	UINT32 reg_dj_pattern0_0_02 			:2; //(5:4,NA,0) //DJ protect pattern0 [0][2]
	UINT32 reg_dj_pattern0_0_03 			:2; //(7:6,NA,0) //DJ protect pattern0 [0][3]
	UINT32 reg_dj_pattern0_0_04 			:2; //(9:8,NA,0) //DJ protect pattern0 [0][4]
	UINT32 reg_dj_pattern0_0_05 			:2; //(11:10,NA,0) //DJ protect pattern0 [0][5]
	UINT32 reg_dj_pattern0_0_06 			:2; //(13:12,NA,0) //DJ protect pattern0 [0][6]
	UINT32 reg_dj_pattern0_0_07 			:2; //(15:14,NA,0) //DJ protect pattern0 [0][7]
	UINT32 reg_dj_pattern0_0_08 			:2; //(17:16,NA,0) //DJ protect pattern0 [0][8]
	UINT32 reg_dj_pattern0_0_09 			:2; //(19:18,NA,0) //DJ protect pattern0 [0][9]
	UINT32 reg_dj_pattern0_0_10 			:2; //(21:20,NA,0) //DJ protect pattern0 [0][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104B8 RW 0x0000_0040
	UINT32 reg_dj_pattern0_1_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [1][0]
	UINT32 reg_dj_pattern0_1_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [1][1]
	UINT32 reg_dj_pattern0_1_02 			:2; //(5:4,NA,0) //DJ protect pattern0 [1][2]
	UINT32 reg_dj_pattern0_1_03 			:2; //(7:6,NA,1) //DJ protect pattern0 [1][3]
	UINT32 reg_dj_pattern0_1_04 			:2; //(9:8,NA,0) //DJ protect pattern0 [1][4]
	UINT32 reg_dj_pattern0_1_05 			:2; //(11:10,NA,0) //DJ protect pattern0 [1][5]
	UINT32 reg_dj_pattern0_1_06 			:2; //(13:12,NA,0) //DJ protect pattern0 [1][6]
	UINT32 reg_dj_pattern0_1_07 			:2; //(15:14,NA,0) //DJ protect pattern0 [1][7]
	UINT32 reg_dj_pattern0_1_08 			:2; //(17:16,NA,0) //DJ protect pattern0 [1][8]
	UINT32 reg_dj_pattern0_1_09 			:2; //(19:18,NA,0) //DJ protect pattern0 [1][9]
	UINT32 reg_dj_pattern0_1_10 			:2; //(21:20,NA,0) //DJ protect pattern0 [1][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104BC RW 0x0015_5550
	UINT32 reg_dj_pattern0_2_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [2][0]
	UINT32 reg_dj_pattern0_2_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [2][1]
	UINT32 reg_dj_pattern0_2_02 			:2; //(5:4,NA,1) //DJ protect pattern0 [2][2]
	UINT32 reg_dj_pattern0_2_03 			:2; //(7:6,NA,1) //DJ protect pattern0 [2][3]
	UINT32 reg_dj_pattern0_2_04 			:2; //(9:8,NA,1) //DJ protect pattern0 [2][4]
	UINT32 reg_dj_pattern0_2_05 			:2; //(11:10,NA,1) //DJ protect pattern0 [2][5]
	UINT32 reg_dj_pattern0_2_06 			:2; //(13:12,NA,1) //DJ protect pattern0 [2][6]
	UINT32 reg_dj_pattern0_2_07 			:2; //(15:14,NA,1) //DJ protect pattern0 [2][7]
	UINT32 reg_dj_pattern0_2_08 			:2; //(17:16,NA,1) //DJ protect pattern0 [2][8]
	UINT32 reg_dj_pattern0_2_09 			:2; //(19:18,NA,1) //DJ protect pattern0 [2][9]
	UINT32 reg_dj_pattern0_2_10 			:2; //(21:20,NA,1) //DJ protect pattern0 [2][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104C0 RW 0x0000_0040
	UINT32 reg_dj_pattern0_3_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [3][0]
	UINT32 reg_dj_pattern0_3_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [3][1]
	UINT32 reg_dj_pattern0_3_02 			:2; //(5:4,NA,0) //DJ protect pattern0 [3][2]
	UINT32 reg_dj_pattern0_3_03 			:2; //(7:6,NA,1) //DJ protect pattern0 [3][3]
	UINT32 reg_dj_pattern0_3_04 			:2; //(9:8,NA,0) //DJ protect pattern0 [3][4]
	UINT32 reg_dj_pattern0_3_05 			:2; //(11:10,NA,0) //DJ protect pattern0 [3][5]
	UINT32 reg_dj_pattern0_3_06 			:2; //(13:12,NA,0) //DJ protect pattern0 [3][6]
	UINT32 reg_dj_pattern0_3_07 			:2; //(15:14,NA,0) //DJ protect pattern0 [3][7]
	UINT32 reg_dj_pattern0_3_08 			:2; //(17:16,NA,0) //DJ protect pattern0 [3][8]
	UINT32 reg_dj_pattern0_3_09 			:2; //(19:18,NA,0) //DJ protect pattern0 [3][9]
	UINT32 reg_dj_pattern0_3_10 			:2; //(21:20,NA,0) //DJ protect pattern0 [3][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104C4 RW 0x002A_A040
	UINT32 reg_dj_pattern0_4_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [4][0]
	UINT32 reg_dj_pattern0_4_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [4][1]
	UINT32 reg_dj_pattern0_4_02 			:2; //(5:4,NA,0) //DJ protect pattern0 [4][2]
	UINT32 reg_dj_pattern0_4_03 			:2; //(7:6,NA,1) //DJ protect pattern0 [4][3]
	UINT32 reg_dj_pattern0_4_04 			:2; //(9:8,NA,0) //DJ protect pattern0 [4][4]
	UINT32 reg_dj_pattern0_4_05 			:2; //(11:10,NA,0) //DJ protect pattern0 [4][5]
	UINT32 reg_dj_pattern0_4_06 			:2; //(13:12,NA,2) //DJ protect pattern0 [4][6]
	UINT32 reg_dj_pattern0_4_07 			:2; //(15:14,NA,2) //DJ protect pattern0 [4][7]
	UINT32 reg_dj_pattern0_4_08 			:2; //(17:16,NA,2) //DJ protect pattern0 [4][8]
	UINT32 reg_dj_pattern0_4_09 			:2; //(19:18,NA,2) //DJ protect pattern0 [4][9]
	UINT32 reg_dj_pattern0_4_10 			:2; //(21:20,NA,2) //DJ protect pattern0 [4][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104C8 RW 0x002A_A040
	UINT32 reg_dj_pattern0_5_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [5][0]
	UINT32 reg_dj_pattern0_5_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [5][1]
	UINT32 reg_dj_pattern0_5_02 			:2; //(5:4,NA,0) //DJ protect pattern0 [5][2]
	UINT32 reg_dj_pattern0_5_03 			:2; //(7:6,NA,1) //DJ protect pattern0 [5][3]
	UINT32 reg_dj_pattern0_5_04 			:2; //(9:8,NA,0) //DJ protect pattern0 [5][4]
	UINT32 reg_dj_pattern0_5_05 			:2; //(11:10,NA,0) //DJ protect pattern0 [5][5]
	UINT32 reg_dj_pattern0_5_06 			:2; //(13:12,NA,2) //DJ protect pattern0 [5][6]
	UINT32 reg_dj_pattern0_5_07 			:2; //(15:14,NA,2) //DJ protect pattern0 [5][7]
	UINT32 reg_dj_pattern0_5_08 			:2; //(17:16,NA,2) //DJ protect pattern0 [5][8]
	UINT32 reg_dj_pattern0_5_09 			:2; //(19:18,NA,2) //DJ protect pattern0 [5][9]
	UINT32 reg_dj_pattern0_5_10 			:2; //(21:20,NA,2) //DJ protect pattern0 [5][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104CC RW 0x000A_A040
	UINT32 reg_dj_pattern0_6_00 			:2; //(1:0,NA,0) //DJ protect pattern0 [6][0]
	UINT32 reg_dj_pattern0_6_01 			:2; //(3:2,NA,0) //DJ protect pattern0 [6][1]
	UINT32 reg_dj_pattern0_6_02 			:2; //(5:4,NA,0) //DJ protect pattern0 [6][2]
	UINT32 reg_dj_pattern0_6_03 			:2; //(7:6,NA,1) //DJ protect pattern0 [6][3]
	UINT32 reg_dj_pattern0_6_04 			:2; //(9:8,NA,0) //DJ protect pattern0 [6][4]
	UINT32 reg_dj_pattern0_6_05 			:2; //(11:10,NA,0) //DJ protect pattern0 [6][5]
	UINT32 reg_dj_pattern0_6_06 			:2; //(13:12,NA,2) //DJ protect pattern0 [6][6]
	UINT32 reg_dj_pattern0_6_07 			:2; //(15:14,NA,2) //DJ protect pattern0 [6][7]
	UINT32 reg_dj_pattern0_6_08 			:2; //(17:16,NA,2) //DJ protect pattern0 [6][8]
	UINT32 reg_dj_pattern0_6_09 			:2; //(19:18,NA,2) //DJ protect pattern0 [6][9]
	UINT32 reg_dj_pattern0_6_10 			:2; //(21:20,NA,0) //DJ protect pattern0 [6][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104D0 RW 0x0000_00E4
	UINT32 reg_dj_pattern0_flip0_h			:1; //(0:0,NA,0) //DJ protect pattern0 flip0, H
	UINT32 reg_dj_pattern0_flip0_v			:1; //(1:1,NA,0) //DJ protect pattern0 flip0, V
	UINT32 reg_dj_pattern0_flip1_h			:1; //(2:2,NA,1) //DJ protect pattern0 flip1, H
	UINT32 reg_dj_pattern0_flip1_v			:1; //(3:3,NA,0) //DJ protect pattern0 flip1, V
	UINT32 reg_dj_pattern0_flip2_h			:1; //(4:4,NA,0) //DJ protect pattern0 flip2, H
	UINT32 reg_dj_pattern0_flip2_v			:1; //(5:5,NA,1) //DJ protect pattern0 flip2, V
	UINT32 reg_dj_pattern0_flip3_h			:1; //(6:6,NA,1) //DJ protect pattern0 flip3, H
	UINT32 reg_dj_pattern0_flip3_v			:1; //(7:7,NA,1) //DJ protect pattern0 flip3, V
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104D4 RW 0x0000_5540
	UINT32 reg_dj_pattern1_0_00 			:2; //(1:0,NA,0) //DJ protect pattern1 [0][0]
	UINT32 reg_dj_pattern1_0_01 			:2; //(3:2,NA,0) //DJ protect pattern1 [0][1]
	UINT32 reg_dj_pattern1_0_02 			:2; //(5:4,NA,0) //DJ protect pattern1 [0][2]
	UINT32 reg_dj_pattern1_0_03 			:2; //(7:6,NA,1) //DJ protect pattern1 [0][3]
	UINT32 reg_dj_pattern1_0_04 			:2; //(9:8,NA,1) //DJ protect pattern1 [0][4]
	UINT32 reg_dj_pattern1_0_05 			:2; //(11:10,NA,1) //DJ protect pattern1 [0][5]
	UINT32 reg_dj_pattern1_0_06 			:2; //(13:12,NA,1) //DJ protect pattern1 [0][6]
	UINT32 reg_dj_pattern1_0_07 			:2; //(15:14,NA,1) //DJ protect pattern1 [0][7]
	UINT32 reg_dj_pattern1_0_08 			:2; //(17:16,NA,0) //DJ protect pattern1 [0][8]
	UINT32 reg_dj_pattern1_0_09 			:2; //(19:18,NA,0) //DJ protect pattern1 [0][9]
	UINT32 reg_dj_pattern1_0_10 			:2; //(21:20,NA,0) //DJ protect pattern1 [0][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104D8 RW 0x0020_5542
	UINT32 reg_dj_pattern1_1_00 			:2; //(1:0,NA,2) //DJ protect pattern1 [1][0]
	UINT32 reg_dj_pattern1_1_01 			:2; //(3:2,NA,0) //DJ protect pattern1 [1][1]
	UINT32 reg_dj_pattern1_1_02 			:2; //(5:4,NA,0) //DJ protect pattern1 [1][2]
	UINT32 reg_dj_pattern1_1_03 			:2; //(7:6,NA,1) //DJ protect pattern1 [1][3]
	UINT32 reg_dj_pattern1_1_04 			:2; //(9:8,NA,1) //DJ protect pattern1 [1][4]
	UINT32 reg_dj_pattern1_1_05 			:2; //(11:10,NA,1) //DJ protect pattern1 [1][5]
	UINT32 reg_dj_pattern1_1_06 			:2; //(13:12,NA,1) //DJ protect pattern1 [1][6]
	UINT32 reg_dj_pattern1_1_07 			:2; //(15:14,NA,1) //DJ protect pattern1 [1][7]
	UINT32 reg_dj_pattern1_1_08 			:2; //(17:16,NA,0) //DJ protect pattern1 [1][8]
	UINT32 reg_dj_pattern1_1_09 			:2; //(19:18,NA,0) //DJ protect pattern1 [1][9]
	UINT32 reg_dj_pattern1_1_10 			:2; //(21:20,NA,2) //DJ protect pattern1 [1][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104DC RW 0x0008_1508
	UINT32 reg_dj_pattern1_2_00 			:2; //(1:0,NA,0) //DJ protect pattern1 [2][0]
	UINT32 reg_dj_pattern1_2_01 			:2; //(3:2,NA,2) //DJ protect pattern1 [2][1]
	UINT32 reg_dj_pattern1_2_02 			:2; //(5:4,NA,0) //DJ protect pattern1 [2][2]
	UINT32 reg_dj_pattern1_2_03 			:2; //(7:6,NA,0) //DJ protect pattern1 [2][3]
	UINT32 reg_dj_pattern1_2_04 			:2; //(9:8,NA,1) //DJ protect pattern1 [2][4]
	UINT32 reg_dj_pattern1_2_05 			:2; //(11:10,NA,1) //DJ protect pattern1 [2][5]
	UINT32 reg_dj_pattern1_2_06 			:2; //(13:12,NA,1) //DJ protect pattern1 [2][6]
	UINT32 reg_dj_pattern1_2_07 			:2; //(15:14,NA,0) //DJ protect pattern1 [2][7]
	UINT32 reg_dj_pattern1_2_08 			:2; //(17:16,NA,0) //DJ protect pattern1 [2][8]
	UINT32 reg_dj_pattern1_2_09 			:2; //(19:18,NA,2) //DJ protect pattern1 [2][9]
	UINT32 reg_dj_pattern1_2_10 			:2; //(21:20,NA,0) //DJ protect pattern1 [2][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104E0 RW 0x0002_0420
	UINT32 reg_dj_pattern1_3_00 			:2; //(1:0,NA,0) //DJ protect pattern1 [3][0]
	UINT32 reg_dj_pattern1_3_01 			:2; //(3:2,NA,0) //DJ protect pattern1 [3][1]
	UINT32 reg_dj_pattern1_3_02 			:2; //(5:4,NA,2) //DJ protect pattern1 [3][2]
	UINT32 reg_dj_pattern1_3_03 			:2; //(7:6,NA,0) //DJ protect pattern1 [3][3]
	UINT32 reg_dj_pattern1_3_04 			:2; //(9:8,NA,0) //DJ protect pattern1 [3][4]
	UINT32 reg_dj_pattern1_3_05 			:2; //(11:10,NA,1) //DJ protect pattern1 [3][5]
	UINT32 reg_dj_pattern1_3_06 			:2; //(13:12,NA,0) //DJ protect pattern1 [3][6]
	UINT32 reg_dj_pattern1_3_07 			:2; //(15:14,NA,0) //DJ protect pattern1 [3][7]
	UINT32 reg_dj_pattern1_3_08 			:2; //(17:16,NA,2) //DJ protect pattern1 [3][8]
	UINT32 reg_dj_pattern1_3_09 			:2; //(19:18,NA,0) //DJ protect pattern1 [3][9]
	UINT32 reg_dj_pattern1_3_10 			:2; //(21:20,NA,0) //DJ protect pattern1 [3][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104E4 RW 0x0000_8080
	UINT32 reg_dj_pattern1_4_00 			:2; //(1:0,NA,0) //DJ protect pattern1 [4][0]
	UINT32 reg_dj_pattern1_4_01 			:2; //(3:2,NA,0) //DJ protect pattern1 [4][1]
	UINT32 reg_dj_pattern1_4_02 			:2; //(5:4,NA,0) //DJ protect pattern1 [4][2]
	UINT32 reg_dj_pattern1_4_03 			:2; //(7:6,NA,2) //DJ protect pattern1 [4][3]
	UINT32 reg_dj_pattern1_4_04 			:2; //(9:8,NA,0) //DJ protect pattern1 [4][4]
	UINT32 reg_dj_pattern1_4_05 			:2; //(11:10,NA,0) //DJ protect pattern1 [4][5]
	UINT32 reg_dj_pattern1_4_06 			:2; //(13:12,NA,0) //DJ protect pattern1 [4][6]
	UINT32 reg_dj_pattern1_4_07 			:2; //(15:14,NA,2) //DJ protect pattern1 [4][7]
	UINT32 reg_dj_pattern1_4_08 			:2; //(17:16,NA,0) //DJ protect pattern1 [4][8]
	UINT32 reg_dj_pattern1_4_09 			:2; //(19:18,NA,0) //DJ protect pattern1 [4][9]
	UINT32 reg_dj_pattern1_4_10 			:2; //(21:20,NA,0) //DJ protect pattern1 [4][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104E8 RW 0x0000_2A00
	UINT32 reg_dj_pattern1_5_00 			:2; //(1:0,NA,0) //DJ protect pattern1 [5][0]
	UINT32 reg_dj_pattern1_5_01 			:2; //(3:2,NA,0) //DJ protect pattern1 [5][1]
	UINT32 reg_dj_pattern1_5_02 			:2; //(5:4,NA,0) //DJ protect pattern1 [5][2]
	UINT32 reg_dj_pattern1_5_03 			:2; //(7:6,NA,0) //DJ protect pattern1 [5][3]
	UINT32 reg_dj_pattern1_5_04 			:2; //(9:8,NA,2) //DJ protect pattern1 [5][4]
	UINT32 reg_dj_pattern1_5_05 			:2; //(11:10,NA,2) //DJ protect pattern1 [5][5]
	UINT32 reg_dj_pattern1_5_06 			:2; //(13:12,NA,2) //DJ protect pattern1 [5][6]
	UINT32 reg_dj_pattern1_5_07 			:2; //(15:14,NA,0) //DJ protect pattern1 [5][7]
	UINT32 reg_dj_pattern1_5_08 			:2; //(17:16,NA,0) //DJ protect pattern1 [5][8]
	UINT32 reg_dj_pattern1_5_09 			:2; //(19:18,NA,0) //DJ protect pattern1 [5][9]
	UINT32 reg_dj_pattern1_5_10 			:2; //(21:20,NA,0) //DJ protect pattern1 [5][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104EC RW 0x0000_2A00
	UINT32 reg_dj_pattern1_6_00 			:2; //(1:0,NA,0) //DJ protect pattern1 [6][0]
	UINT32 reg_dj_pattern1_6_01 			:2; //(3:2,NA,0) //DJ protect pattern1 [6][1]
	UINT32 reg_dj_pattern1_6_02 			:2; //(5:4,NA,0) //DJ protect pattern1 [6][2]
	UINT32 reg_dj_pattern1_6_03 			:2; //(7:6,NA,0) //DJ protect pattern1 [6][3]
	UINT32 reg_dj_pattern1_6_04 			:2; //(9:8,NA,2) //DJ protect pattern1 [6][4]
	UINT32 reg_dj_pattern1_6_05 			:2; //(11:10,NA,2) //DJ protect pattern1 [6][5]
	UINT32 reg_dj_pattern1_6_06 			:2; //(13:12,NA,2) //DJ protect pattern1 [6][6]
	UINT32 reg_dj_pattern1_6_07 			:2; //(15:14,NA,0) //DJ protect pattern1 [6][7]
	UINT32 reg_dj_pattern1_6_08 			:2; //(17:16,NA,0) //DJ protect pattern1 [6][8]
	UINT32 reg_dj_pattern1_6_09 			:2; //(19:18,NA,0) //DJ protect pattern1 [6][9]
	UINT32 reg_dj_pattern1_6_10 			:2; //(21:20,NA,0) //DJ protect pattern1 [6][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104F0 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h			:1; //(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v			:1; //(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h			:1; //(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v			:1; //(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd							:28;
	};
}PE_O22F22_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104F4 RW 0x0000_2800
	UINT32 reg_dj_pattern2_0_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [0][0]
	UINT32 reg_dj_pattern2_0_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [0][1]
	UINT32 reg_dj_pattern2_0_02 			:2; //(5:4,NA,0) //DJ protect pattern2 [0][2]
	UINT32 reg_dj_pattern2_0_03 			:2; //(7:6,NA,0) //DJ protect pattern2 [0][3]
	UINT32 reg_dj_pattern2_0_04 			:2; //(9:8,NA,0) //DJ protect pattern2 [0][4]
	UINT32 reg_dj_pattern2_0_05 			:2; //(11:10,NA,2) //DJ protect pattern2 [0][5]
	UINT32 reg_dj_pattern2_0_06 			:2; //(13:12,NA,2) //DJ protect pattern2 [0][6]
	UINT32 reg_dj_pattern2_0_07 			:2; //(15:14,NA,0) //DJ protect pattern2 [0][7]
	UINT32 reg_dj_pattern2_0_08 			:2; //(17:16,NA,0) //DJ protect pattern2 [0][8]
	UINT32 reg_dj_pattern2_0_09 			:2; //(19:18,NA,0) //DJ protect pattern2 [0][9]
	UINT32 reg_dj_pattern2_0_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [0][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104F8 RW 0x0005_0A00
	UINT32 reg_dj_pattern2_1_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [1][0]
	UINT32 reg_dj_pattern2_1_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [1][1]
	UINT32 reg_dj_pattern2_1_02 			:2; //(5:4,NA,0) //DJ protect pattern2 [1][2]
	UINT32 reg_dj_pattern2_1_03 			:2; //(7:6,NA,0) //DJ protect pattern2 [1][3]
	UINT32 reg_dj_pattern2_1_04 			:2; //(9:8,NA,2) //DJ protect pattern2 [1][4]
	UINT32 reg_dj_pattern2_1_05 			:2; //(11:10,NA,2) //DJ protect pattern2 [1][5]
	UINT32 reg_dj_pattern2_1_06 			:2; //(13:12,NA,0) //DJ protect pattern2 [1][6]
	UINT32 reg_dj_pattern2_1_07 			:2; //(15:14,NA,0) //DJ protect pattern2 [1][7]
	UINT32 reg_dj_pattern2_1_08 			:2; //(17:16,NA,1) //DJ protect pattern2 [1][8]
	UINT32 reg_dj_pattern2_1_09 			:2; //(19:18,NA,1) //DJ protect pattern2 [1][9]
	UINT32 reg_dj_pattern2_1_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [1][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34104FC RW 0x0005_4280
	UINT32 reg_dj_pattern2_2_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [2][0]
	UINT32 reg_dj_pattern2_2_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [2][1]
	UINT32 reg_dj_pattern2_2_02 			:2; //(5:4,NA,0) //DJ protect pattern2 [2][2]
	UINT32 reg_dj_pattern2_2_03 			:2; //(7:6,NA,2) //DJ protect pattern2 [2][3]
	UINT32 reg_dj_pattern2_2_04 			:2; //(9:8,NA,2) //DJ protect pattern2 [2][4]
	UINT32 reg_dj_pattern2_2_05 			:2; //(11:10,NA,0) //DJ protect pattern2 [2][5]
	UINT32 reg_dj_pattern2_2_06 			:2; //(13:12,NA,0) //DJ protect pattern2 [2][6]
	UINT32 reg_dj_pattern2_2_07 			:2; //(15:14,NA,1) //DJ protect pattern2 [2][7]
	UINT32 reg_dj_pattern2_2_08 			:2; //(17:16,NA,1) //DJ protect pattern2 [2][8]
	UINT32 reg_dj_pattern2_2_09 			:2; //(19:18,NA,1) //DJ protect pattern2 [2][9]
	UINT32 reg_dj_pattern2_2_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [2][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410500 RW 0x0005_50A0
	UINT32 reg_dj_pattern2_3_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [3][0]
	UINT32 reg_dj_pattern2_3_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [3][1]
	UINT32 reg_dj_pattern2_3_02 			:2; //(5:4,NA,2) //DJ protect pattern2 [3][2]
	UINT32 reg_dj_pattern2_3_03 			:2; //(7:6,NA,2) //DJ protect pattern2 [3][3]
	UINT32 reg_dj_pattern2_3_04 			:2; //(9:8,NA,0) //DJ protect pattern2 [3][4]
	UINT32 reg_dj_pattern2_3_05 			:2; //(11:10,NA,0) //DJ protect pattern2 [3][5]
	UINT32 reg_dj_pattern2_3_06 			:2; //(13:12,NA,1) //DJ protect pattern2 [3][6]
	UINT32 reg_dj_pattern2_3_07 			:2; //(15:14,NA,1) //DJ protect pattern2 [3][7]
	UINT32 reg_dj_pattern2_3_08 			:2; //(17:16,NA,1) //DJ protect pattern2 [3][8]
	UINT32 reg_dj_pattern2_3_09 			:2; //(19:18,NA,1) //DJ protect pattern2 [3][9]
	UINT32 reg_dj_pattern2_3_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [3][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410504 RW 0x0005_4280
	UINT32 reg_dj_pattern2_4_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [4][0]
	UINT32 reg_dj_pattern2_4_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [4][1]
	UINT32 reg_dj_pattern2_4_02 			:2; //(5:4,NA,0) //DJ protect pattern2 [4][2]
	UINT32 reg_dj_pattern2_4_03 			:2; //(7:6,NA,2) //DJ protect pattern2 [4][3]
	UINT32 reg_dj_pattern2_4_04 			:2; //(9:8,NA,2) //DJ protect pattern2 [4][4]
	UINT32 reg_dj_pattern2_4_05 			:2; //(11:10,NA,0) //DJ protect pattern2 [4][5]
	UINT32 reg_dj_pattern2_4_06 			:2; //(13:12,NA,0) //DJ protect pattern2 [4][6]
	UINT32 reg_dj_pattern2_4_07 			:2; //(15:14,NA,1) //DJ protect pattern2 [4][7]
	UINT32 reg_dj_pattern2_4_08 			:2; //(17:16,NA,1) //DJ protect pattern2 [4][8]
	UINT32 reg_dj_pattern2_4_09 			:2; //(19:18,NA,1) //DJ protect pattern2 [4][9]
	UINT32 reg_dj_pattern2_4_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [4][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410508 RW 0x0005_0A00
	UINT32 reg_dj_pattern2_5_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [5][0]
	UINT32 reg_dj_pattern2_5_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [5][1]
	UINT32 reg_dj_pattern2_5_02 			:2; //(5:4,NA,0) //DJ protect pattern2 [5][2]
	UINT32 reg_dj_pattern2_5_03 			:2; //(7:6,NA,0) //DJ protect pattern2 [5][3]
	UINT32 reg_dj_pattern2_5_04 			:2; //(9:8,NA,2) //DJ protect pattern2 [5][4]
	UINT32 reg_dj_pattern2_5_05 			:2; //(11:10,NA,2) //DJ protect pattern2 [5][5]
	UINT32 reg_dj_pattern2_5_06 			:2; //(13:12,NA,0) //DJ protect pattern2 [5][6]
	UINT32 reg_dj_pattern2_5_07 			:2; //(15:14,NA,0) //DJ protect pattern2 [5][7]
	UINT32 reg_dj_pattern2_5_08 			:2; //(17:16,NA,1) //DJ protect pattern2 [5][8]
	UINT32 reg_dj_pattern2_5_09 			:2; //(19:18,NA,1) //DJ protect pattern2 [5][9]
	UINT32 reg_dj_pattern2_5_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [5][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341050C RW 0x0000_2800
	UINT32 reg_dj_pattern2_6_00 			:2; //(1:0,NA,0) //DJ protect pattern2 [6][0]
	UINT32 reg_dj_pattern2_6_01 			:2; //(3:2,NA,0) //DJ protect pattern2 [6][1]
	UINT32 reg_dj_pattern2_6_02 			:2; //(5:4,NA,0) //DJ protect pattern2 [6][2]
	UINT32 reg_dj_pattern2_6_03 			:2; //(7:6,NA,0) //DJ protect pattern2 [6][3]
	UINT32 reg_dj_pattern2_6_04 			:2; //(9:8,NA,0) //DJ protect pattern2 [6][4]
	UINT32 reg_dj_pattern2_6_05 			:2; //(11:10,NA,2) //DJ protect pattern2 [6][5]
	UINT32 reg_dj_pattern2_6_06 			:2; //(13:12,NA,2) //DJ protect pattern2 [6][6]
	UINT32 reg_dj_pattern2_6_07 			:2; //(15:14,NA,0) //DJ protect pattern2 [6][7]
	UINT32 reg_dj_pattern2_6_08 			:2; //(17:16,NA,0) //DJ protect pattern2 [6][8]
	UINT32 reg_dj_pattern2_6_09 			:2; //(19:18,NA,0) //DJ protect pattern2 [6][9]
	UINT32 reg_dj_pattern2_6_10 			:2; //(21:20,NA,0) //DJ protect pattern2 [6][10]
	UINT32 resvd							:10;
	};
}PE_O22F22_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410510 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h			:1; //(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v			:1; //(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h			:1; //(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v			:1; //(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd							:28;
	};
}PE_O22F22_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410514 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul				:6; //(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0							:2;
	UINT32 reg_dj_soft_g0_offset			:5; //(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1							:3;
	UINT32 reg_dj_soft_g0_max				:8; //(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410518 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul				:6; //(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0							:2;
	UINT32 reg_dj_soft_g1_offset			:5; //(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1							:3;
	UINT32 reg_dj_soft_g1_max				:8; //(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341051C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul				:6; //(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0							:2;
	UINT32 reg_dj_soft_g2_offset			:5; //(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1							:3;
	UINT32 reg_dj_soft_g2_max				:8; //(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410520 RW 0x0001_1400
	UINT32 reg_dj_soft_base 				:8; //(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain		:8; //(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en		:1; //(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd							:15;
	};
}PE_O22F22_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410524 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410528 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410530 RW 0x0000_0000
	UINT32 reg_core0_win_dj_win0_en 		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_dj_win1_en 		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_dj_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_dj_win_outside 	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_dj_win_en			:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_dj_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_dj_bdr_wid 		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_dj_bdr_en			:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_dj_cr5 			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_dj_cb5 			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_dj_yy6 			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410534 RW 0x0000_0000
	UINT32 reg_core0_win_dj_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core0_win_dj_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE0_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410538 RW 0x086F_0EFF
	UINT32 reg_core0_win_dj_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core0_win_dj_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE0_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341053C RW 0x0000_0000
	UINT32 reg_core0_win_dj_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core0_win_dj_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE0_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410540 RW 0x086F_0EFF
	UINT32 reg_core0_win_dj_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core0_win_dj_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE0_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410544 RW 0x0000_0000
	UINT32 reg_core1_win_dj_win0_en 		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core1_win_dj_win1_en 		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core1_win_dj_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core1_win_dj_win_outside 	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_dj_win_en			:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_dj_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core1_win_dj_bdr_wid 		:2; //(14:13,NA,0) //border width
	UINT32 reg_core1_win_dj_bdr_en			:1; //(15:15,NA,0) //border enable
	UINT32 reg_core1_win_dj_cr5 			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core1_win_dj_cb5 			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core1_win_dj_yy6 			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410548 RW 0x0000_0000
	UINT32 reg_core1_win_dj_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core1_win_dj_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE1_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341054C RW 0x086F_0EFF
	UINT32 reg_core1_win_dj_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core1_win_dj_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE1_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410550 RW 0x0000_0000
	UINT32 reg_core1_win_dj_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core1_win_dj_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE1_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410554 RW 0x086F_0EFF
	UINT32 reg_core1_win_dj_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core1_win_dj_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE1_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410560 RW 0x0000_0000
	UINT32 reg_color_region_en				:1; //(0:0,NA,0) //color region processing enable
	UINT32 reg_color_region_debug_en		:1; //(1:1,NA,0) //color region debug map enable
	UINT32 resvd0							:2;
	UINT32 reg_chr_protection_en			:1; //(4:4,NA,0) //chroma protection enable
	UINT32 resvd1							:3;
	UINT32 reg_chr_compensation_en			:1; //(8:8,NA,0) //chroma compensation enable
	UINT32 resvd2							:23;
	};
}PE_O22F22_SHP_CHROMA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410564 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CHROMA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410568 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CHROMA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341056C RW 0x28FF_1400
	UINT32 reg_chr_gain_r0_cb_y0			:8; //(7:0,NA,0) //chroma gain LUT, R0, Cb, y0
	UINT32 reg_chr_gain_r0_cb_x0			:8; //(15:8,NA,20) //chroma gain LUT, R0, Cb, x0
	UINT32 reg_chr_gain_r0_cb_y1			:8; //(23:16,NA,255) //chroma gain LUT, R0, Cb, y1
	UINT32 reg_chr_gain_r0_cb_x1			:8; //(31:24,NA,40) //chroma gain LUT, R0, Cb, x1
	};
}PE_O22F22_SHP_CHROMA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410570 RW 0x7800_64FF
	UINT32 reg_chr_gain_r0_cb_y2			:8; //(7:0,NA,255) //chroma gain LUT, R0, Cb, y2
	UINT32 reg_chr_gain_r0_cb_x2			:8; //(15:8,NA,100) //chroma gain LUT, R0, Cb, x2
	UINT32 reg_chr_gain_r0_cb_y3			:8; //(23:16,NA,0) //chroma gain LUT, R0, Cb, y3
	UINT32 reg_chr_gain_r0_cb_x3			:8; //(31:24,NA,120) //chroma gain LUT, R0, Cb, x3
	};
}PE_O22F22_SHP_CHROMA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410574 RW 0x96FF_8200
	UINT32 reg_chr_gain_r0_cr_y0			:8; //(7:0,NA,0) //chroma gain LUT, R0, Cr, y0
	UINT32 reg_chr_gain_r0_cr_x0			:8; //(15:8,NA,130) //chroma gain LUT, R0, Cr, x0
	UINT32 reg_chr_gain_r0_cr_y1			:8; //(23:16,NA,255) //chroma gain LUT, R0, Cr, y1
	UINT32 reg_chr_gain_r0_cr_x1			:8; //(31:24,NA,150) //chroma gain LUT, R0, Cr, x1
	};
}PE_O22F22_SHP_CHROMA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410578 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r0_cr_y2			:8; //(7:0,NA,200) //chroma gain LUT, R0, Cr, y2
	UINT32 reg_chr_gain_r0_cr_x2			:8; //(15:8,NA,255) //chroma gain LUT, R0, Cr, x2
	UINT32 reg_chr_gain_r0_cr_y3			:8; //(23:16,NA,240) //chroma gain LUT, R0, Cr, y3
	UINT32 reg_chr_gain_r0_cr_x3			:8; //(31:24,NA,0) //chroma gain LUT, R0, Cr, x3
	};
}PE_O22F22_SHP_CHROMA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341057C RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CHROMA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410580 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CHROMA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410584 RW 0x96FF_8200
	UINT32 reg_chr_gain_r1_cb_y0			:8; //(7:0,NA,0) //chroma gain LUT, R1, Cb, y0
	UINT32 reg_chr_gain_r1_cb_x0			:8; //(15:8,NA,130) //chroma gain LUT, R1, Cb, x0
	UINT32 reg_chr_gain_r1_cb_y1			:8; //(23:16,NA,255) //chroma gain LUT, R1, Cb, y1
	UINT32 reg_chr_gain_r1_cb_x1			:8; //(31:24,NA,150) //chroma gain LUT, R1, Cb, x1
	};
}PE_O22F22_SHP_CHROMA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410588 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r1_cb_y2			:8; //(7:0,NA,200) //chroma gain LUT, R1, Cb, y2
	UINT32 reg_chr_gain_r1_cb_x2			:8; //(15:8,NA,255) //chroma gain LUT, R1, Cb, x2
	UINT32 reg_chr_gain_r1_cb_y3			:8; //(23:16,NA,240) //chroma gain LUT, R1, Cb, y3
	UINT32 reg_chr_gain_r1_cb_x3			:8; //(31:24,NA,0) //chroma gain LUT, R1, Cb, x3
	};
}PE_O22F22_SHP_CHROMA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341058C RW 0x28FF_1400
	UINT32 reg_chr_gain_r1_cr_y0			:8; //(7:0,NA,0) //chroma gain LUT, R1, Cr, y0
	UINT32 reg_chr_gain_r1_cr_x0			:8; //(15:8,NA,20) //chroma gain LUT, R1, Cr, x0
	UINT32 reg_chr_gain_r1_cr_y1			:8; //(23:16,NA,255) //chroma gain LUT, R1, Cr, y1
	UINT32 reg_chr_gain_r1_cr_x1			:8; //(31:24,NA,40) //chroma gain LUT, R1, Cr, x1
	};
}PE_O22F22_SHP_CHROMA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410590 RW 0x7800_64FF
	UINT32 reg_chr_gain_r1_cr_y2			:8; //(7:0,NA,255) //chroma gain LUT, R1, Cr, y2
	UINT32 reg_chr_gain_r1_cr_x2			:8; //(15:8,NA,100) //chroma gain LUT, R1, Cr, x2
	UINT32 reg_chr_gain_r1_cr_y3			:8; //(23:16,NA,0) //chroma gain LUT, R1, Cr, y3
	UINT32 reg_chr_gain_r1_cr_x3			:8; //(31:24,NA,120) //chroma gain LUT, R1, Cr, x3
	};
}PE_O22F22_SHP_CHROMA_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410594 RW 0x00FF_0000
	UINT32 reg_chr_gain_r0_gain 			:8; //(7:0,NA,0) //chroma gain alpha, R0
	UINT32 resvd0							:8;
	UINT32 reg_chr_gain_r1_gain 			:8; //(23:16,NA,255) //chroma gain alpha, R1
	UINT32 reg_chr_gain_sel 				:1; //(24:24,NA,0) //0: {3'd0,region_gain}	1: {region_gain,3'd0}
	UINT32 resvd1							:7;
	};
}PE_O22F22_SHP_CHROMA_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410598 RW 0x28FF_1400
	UINT32 reg_chr_comp_y0					:8; //(7:0,NA,0) //chroma comp. linear mapping, y0
	UINT32 reg_chr_comp_x0					:8; //(15:8,NA,20) //chroma comp. linear mapping, x0
	UINT32 reg_chr_comp_y1					:8; //(23:16,NA,255) //chroma comp. linear mapping, y1
	UINT32 reg_chr_comp_x1					:8; //(31:24,NA,40) //chroma comp. linear mapping, x1
	};
}PE_O22F22_SHP_CHROMA_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105A0 RW 0x0000_2A60
	UINT32 reg_cti_en						:1; //(0:0,NA,0) //cti enable
	UINT32 resvd0							:3;
	UINT32 reg_cti_filter_tap_size			:3; //(6:4,NA,6) //000: 21 tap	001: 19 tap 010: 17 tap 011: 15 tap 100: 13 tap 101: 11 tap 110:  9 tap
	UINT32 resvd1							:1;
	UINT32 reg_cti_gain 					:8; //(15:8,NA,42) //gain (3.5u)
	UINT32 resvd2							:16;
	};
}PE_O22F22_SHP_CTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105A4 RW 0x0001_1810
	UINT32 reg_cti_coring_th0				:8; //(7:0,NA,16) //coring th0
	UINT32 reg_cti_coring_th1				:8; //(15:8,NA,24) //coring_th1
	UINT32 reg_cti_coring_map_filter		:3; //(18:16,NA,1) //000: no filtering	001: 5-tap filtering	010: 7-tap filtering	011: 9-tap filtering	100: 11-tap filtering	101: 13-tap filtering
	UINT32 resvd0							:1;
	UINT32 reg_cti_coring_tap_size			:3; //(22:20,NA,0) //000: 21 tap	001: 19 tap 010: 17 tap 011: 15 tap 100: 13 tap 101: 11 tap 110:  9 tap
	UINT32 resvd1							:1;
	UINT32 reg_cti_debug_mode				:2; //(25:24,NA,0) //00: normal display 10: coring_map(cb)	11: coring_map(cr)
	UINT32 resvd2							:6;
	};
}PE_O22F22_SHP_CTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105A8 RW 0x0088_0850
	UINT32 reg_cti_ycm_en					:1; //(0:0,NA,0) //y/c merge enable
	UINT32 resvd0							:3;
	UINT32 reg_cti_ycm_band_sel 			:3; //(6:4,NA,5) //y/c merge band sel
	UINT32 resvd1							:1;
	UINT32 reg_cti_ycm_diff_th				:8; //(15:8,NA,8) //y/c merge diff threshold
	UINT32 reg_cti_ycm_y_gain				:4; //(19:16,NA,8) //y/c merge gain, Y
	UINT32 reg_cti_ycm_c_gain				:4; //(23:20,NA,8) //y/c merge gain, C
	UINT32 resvd2							:8;
	};
}PE_O22F22_SHP_CTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105B0 RW 0x0000_0000
	UINT32 reg_flick_en 					:1; //(0:0,NA,0) //frc flicker blur enable
	UINT32 resvd0							:3;
	UINT32 reg_flick_motion_sel 			:2; //(5:4,NA,0) //SHP FRC flicker blur motion map position 422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1							:2;
	UINT32 reg_flick_blur_type				:2; //(9:8,NA,0) //frc flicker blur pel selection	0: cur pel[y][x+1]	1: cur pel[y][x-1]	2: average
	UINT32 resvd2							:22;
	};
}PE_O22F22_SHP_FRC_FLICK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105B4 RW 0x2040_0000
	UINT32 reg_flick_motion_lut_y0			:8; //(7:0,NA,0) //frc flicker blur motion LUT point, y0
	UINT32 reg_flick_motion_lut_x0			:8; //(15:8,NA,0) //frc flicker blur motion LUT point, x0
	UINT32 reg_flick_motion_lut_y1			:8; //(23:16,NA,64) //frc flicker blur motion LUT point, y1
	UINT32 reg_flick_motion_lut_x1			:8; //(31:24,NA,32) //frc flicker blur motion LUT point, x1
	};
}PE_O22F22_SHP_FRC_FLICK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105B8 RW 0x80FF_4080
	UINT32 reg_flick_motion_lut_y2			:8; //(7:0,NA,128) //frcflicker blur motion LUT point, y2
	UINT32 reg_flick_motion_lut_x2			:8; //(15:8,NA,64) //frc flicker blur motion LUT point, x2
	UINT32 reg_flick_motion_lut_y3			:8; //(23:16,NA,255) //frc flicker blur motion LUT point, y3
	UINT32 reg_flick_motion_lut_x3			:8; //(31:24,NA,128) //frc flicker blur motion LUT point, x3
	};
}PE_O22F22_SHP_FRC_FLICK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105BC RW 0x0000_0080
	UINT32 reg_flick_master_gain			:8; //(7:0,NA,128) //frc flicker blur master gain
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_FRC_FLICK_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105C0 RW 0x0000_0000
	UINT32 reg_frc_blur_en					:1; //(0:0,NA,0) //frc blur enable
	UINT32 reg_frc_blur_debug_en			:1; //(1:1,NA,0) //frc blur debug en
	UINT32 resvd							:30;
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105C4 RW 0x1812_0C06
	UINT32 reg_frc_blur_cnt_th0 			:6; //(5:0,NA,6) //frc blur weight smoothing count threshold, 0
	UINT32 resvd0							:2;
	UINT32 reg_frc_blur_cnt_th1 			:6; //(13:8,NA,12) //frc blur weight smoothing count threshold, 1
	UINT32 resvd1							:2;
	UINT32 reg_frc_blur_cnt_th2 			:6; //(21:16,NA,18) //frc blur weight smoothing count threshold, 2
	UINT32 resvd2							:2;
	UINT32 reg_frc_blur_cnt_th3 			:6; //(29:24,NA,24) //frc blur weight smoothing count threshold, 3
	UINT32 resvd3							:2;
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105C8 RW 0x302A_241E
	UINT32 reg_frc_blur_cnt_th4 			:6; //(5:0,NA,30) //frc blur weight smoothing count threshold, 4
	UINT32 resvd0							:2;
	UINT32 reg_frc_blur_cnt_th5 			:6; //(13:8,NA,36) //frc blur weight smoothing count threshold, 5
	UINT32 resvd1							:2;
	UINT32 reg_frc_blur_cnt_th6 			:6; //(21:16,NA,42) //frc blur weight smoothing count threshold, 6
	UINT32 resvd2							:2;
	UINT32 reg_frc_blur_cnt_th7 			:6; //(29:24,NA,48) //frc blur weight smoothing count threshold, 7
	UINT32 resvd3							:2;
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105CC RW 0x8765_4321
	UINT32 reg_frc_blur_val0				:4; //(3:0,NA,1) //frc blur weight smoothing count value, 0
	UINT32 reg_frc_blur_val1				:4; //(7:4,NA,2) //frc blur weight smoothing count value, 1
	UINT32 reg_frc_blur_val2				:4; //(11:8,NA,3) //frc blur weight smoothing count value, 2
	UINT32 reg_frc_blur_val3				:4; //(15:12,NA,4) //frc blur weight smoothing count value, 3
	UINT32 reg_frc_blur_val4				:4; //(19:16,NA,5) //frc blur weight smoothing count value, 4
	UINT32 reg_frc_blur_val5				:4; //(23:20,NA,6) //frc blur weight smoothing count value, 5
	UINT32 reg_frc_blur_val6				:4; //(27:24,NA,7) //frc blur weight smoothing count value, 6
	UINT32 reg_frc_blur_val7				:4; //(31:28,NA,8) //frc blur weight smoothing count value, 7
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105D0 RW 0x0000_0004
	UINT32 reg_frc_blur_coef_x8 			:4; //(3:0,NA,4) //frc blur filter coeff, x, [8]
	UINT32 resvd							:28;
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105D4 RW 0x4444_4433
	UINT32 reg_frc_blur_coef_x0 			:4; //(3:0,NA,3) //frc blur filter coeff, x, [0]/[16]
	UINT32 reg_frc_blur_coef_x1 			:4; //(7:4,NA,3) //frc blur filter coeff, x, [1]/[15]
	UINT32 reg_frc_blur_coef_x2 			:4; //(11:8,NA,4) //frc blur filter coeff, x, [2]/[14]
	UINT32 reg_frc_blur_coef_x3 			:4; //(15:12,NA,4) //frc blur filter coeff, x, [3]/[13]
	UINT32 reg_frc_blur_coef_x4 			:4; //(19:16,NA,4) //frc blur filter coeff, x, [4]/[12]
	UINT32 reg_frc_blur_coef_x5 			:4; //(23:20,NA,4) //frc blur filter coeff, x, [5]/[11]
	UINT32 reg_frc_blur_coef_x6 			:4; //(27:24,NA,4) //frc blur filter coeff, x, [6]/[10]
	UINT32 reg_frc_blur_coef_x7 			:4; //(31:28,NA,4) //frc blur filter coeff, x, [7]/[9]
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105D8 RW 0x0000_0866
	UINT32 reg_frc_blur_coef_y0 			:4; //(3:0,NA,6) //frc blur filter coeff, y, [0]/[4]
	UINT32 reg_frc_blur_coef_y1 			:4; //(7:4,NA,6) //frc blur filter coeff, y, [1]/[3]
	UINT32 reg_frc_blur_coef_y2 			:4; //(11:8,NA,8) //frc blur filter coeff, y, [2]
	UINT32 resvd							:20;
	};
}PE_O22F22_SHP_FRC_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105E0 RW 0x0000_0000
	UINT32 reg_frc_halo_en					:1; //(0:0,NA,0) //frc halo enable
	UINT32 reg_frc_halo_debug_en			:1; //(1:1,NA,0) //frc halo debug en
	UINT32 resvd							:30;
	};
}PE_O22F22_SHP_FRC_HALO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105E4 RW 0x1812_0C06
	UINT32 reg_frc_halo_cnt_th0 			:6; //(5:0,NA,6) //frc halo weight smoothing count threshold, 0
	UINT32 resvd0							:2;
	UINT32 reg_frc_halo_cnt_th1 			:6; //(13:8,NA,12) //frc halo weight smoothing count threshold, 1
	UINT32 resvd1							:2;
	UINT32 reg_frc_halo_cnt_th2 			:6; //(21:16,NA,18) //frc halo weight smoothing count threshold, 2
	UINT32 resvd2							:2;
	UINT32 reg_frc_halo_cnt_th3 			:6; //(29:24,NA,24) //frc halo weight smoothing count threshold, 3
	UINT32 resvd3							:2;
	};
}PE_O22F22_SHP_FRC_HALO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105E8 RW 0x302A_241E
	UINT32 reg_frc_halo_cnt_th4 			:6; //(5:0,NA,30) //frc halo weight smoothing count threshold, 4
	UINT32 resvd0							:2;
	UINT32 reg_frc_halo_cnt_th5 			:6; //(13:8,NA,36) //frc halo weight smoothing count threshold, 5
	UINT32 resvd1							:2;
	UINT32 reg_frc_halo_cnt_th6 			:6; //(21:16,NA,42) //frc halo weight smoothing count threshold, 6
	UINT32 resvd2							:2;
	UINT32 reg_frc_halo_cnt_th7 			:6; //(29:24,NA,48) //frc halo weight smoothing count threshold, 7
	UINT32 resvd3							:2;
	};
}PE_O22F22_SHP_FRC_HALO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105EC RW 0x8765_4321
	UINT32 reg_frc_halo_val0				:4; //(3:0,NA,1) //frc halo weight smoothing count value, 0
	UINT32 reg_frc_halo_val1				:4; //(7:4,NA,2) //frc halo weight smoothing count value, 1
	UINT32 reg_frc_halo_val2				:4; //(11:8,NA,3) //frc halo weight smoothing count value, 2
	UINT32 reg_frc_halo_val3				:4; //(15:12,NA,4) //frc halo weight smoothing count value, 3
	UINT32 reg_frc_halo_val4				:4; //(19:16,NA,5) //frc halo weight smoothing count value, 4
	UINT32 reg_frc_halo_val5				:4; //(23:20,NA,6) //frc halo weight smoothing count value, 5
	UINT32 reg_frc_halo_val6				:4; //(27:24,NA,7) //frc halo weight smoothing count value, 6
	UINT32 reg_frc_halo_val7				:4; //(31:28,NA,8) //frc halo weight smoothing count value, 7
	};
}PE_O22F22_SHP_FRC_HALO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105F0 RW 0x0000_0000
	UINT32 reg_core0_win_frc_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_frc_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_frc_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_frc_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_frc_win_en 		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_frc_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_frc_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_frc_bdr_en 		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_frc_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_frc_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_frc_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105F4 RW 0x0000_0000
	UINT32 reg_core0_win_frc_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core0_win_frc_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE0_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105F8 RW 0x086F_0EFF
	UINT32 reg_core0_win_frc_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core0_win_frc_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE0_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34105FC RW 0x0000_0000
	UINT32 reg_core0_win_frc_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core0_win_frc_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE0_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410600 RW 0x086F_0EFF
	UINT32 reg_core0_win_frc_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core0_win_frc_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE0_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410604 RW 0x0000_0000
	UINT32 reg_core1_win_frc_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core1_win_frc_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core1_win_frc_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core1_win_frc_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_frc_win_en 		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_frc_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core1_win_frc_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core1_win_frc_bdr_en 		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core1_win_frc_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core1_win_frc_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core1_win_frc_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410608 RW 0x0000_0000
	UINT32 reg_core1_win_frc_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core1_win_frc_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE1_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341060C RW 0x086F_0EFF
	UINT32 reg_core1_win_frc_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core1_win_frc_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE1_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410610 RW 0x0000_0000
	UINT32 reg_core1_win_frc_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core1_win_frc_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE1_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410614 RW 0x086F_0EFF
	UINT32 reg_core1_win_frc_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core1_win_frc_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE1_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410620 RW 0x0000_0C00
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410624 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410628 RW 0x0011_001E
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341062C RW 0x0011_001E
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410630 RW 0x0870_0780
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410634 RW 0x8000_3030
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410638 RW 0x0001_0001
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341063C RW 0x0080_0040
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410640 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410644 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410648 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341064C RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410650 RW 0x0870_0780
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410660 RW 0x0000_0000
	UINT32 reg_motion_prot_adaptive_en		:1; //(0:0,NA,0) //motion protection enable
	UINT32 resvd							:31;
	};
}PE_O22F22_SHP_MOTION_PROT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410664 RW 0x4040_0000
	UINT32 reg_motion_prot_lut_a_y0 		:8; //(7:0,NA,0) //motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0 		:8; //(15:8,NA,0) //motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1 		:8; //(23:16,NA,64) //motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1 		:8; //(31:24,NA,64) //motion gain LUT, A, x1
	};
}PE_O22F22_SHP_MOTION_PROT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410668 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_a_y2 		:8; //(7:0,NA,80) //motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2 		:8; //(15:8,NA,110) //motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3 		:8; //(23:16,NA,120) //motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3 		:8; //(31:24,NA,255) //motion gain LUT, A, x3
	};
}PE_O22F22_SHP_MOTION_PROT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341066C RW 0x4040_0000
	UINT32 reg_motion_prot_lut_t_y0 		:8; //(7:0,NA,0) //motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0 		:8; //(15:8,NA,0) //motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1 		:8; //(23:16,NA,64) //motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1 		:8; //(31:24,NA,64) //motion gain LUT, T, x1
	};
}PE_O22F22_SHP_MOTION_PROT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410670 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_t_y2 		:8; //(7:0,NA,80) //motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2 		:8; //(15:8,NA,110) //motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3 		:8; //(23:16,NA,120) //motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3 		:8; //(31:24,NA,255) //motion gain LUT, T, x3
	};
}PE_O22F22_SHP_MOTION_PROT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410680 RW 0x0000_0000
	UINT32 reg_core0_win_mot_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_mot_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_mot_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_mot_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_mot_win_en 		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_mot_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_mot_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_mot_bdr_en 		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_mot_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_mot_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_mot_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410684 RW 0x0000_0000
	UINT32 reg_core0_win_mot_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core0_win_mot_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE0_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410688 RW 0x086F_0EFF
	UINT32 reg_core0_win_mot_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core0_win_mot_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE0_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341068C RW 0x0000_0000
	UINT32 reg_core0_win_mot_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core0_win_mot_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE0_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410690 RW 0x086F_0EFF
	UINT32 reg_core0_win_mot_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core0_win_mot_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE0_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106A0 RW 0x0000_0000
	UINT32 reg_core1_win_mot_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core1_win_mot_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core1_win_mot_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core1_win_mot_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_mot_win_en 		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_mot_bdr_alpha		:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core1_win_mot_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core1_win_mot_bdr_en 		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core1_win_mot_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core1_win_mot_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core1_win_mot_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106A4 RW 0x0000_0000
	UINT32 reg_core1_win_mot_win_w0_x0		:16;	//(15:0,NA,0) //win_w0_x0
	UINT32 reg_core1_win_mot_win_w0_y0		:16;	//(31:16,NA,0) //win_w0_y0
	};
}PE_O22F22_SHP_CORE1_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106A8 RW 0x086F_0EFF
	UINT32 reg_core1_win_mot_win_w0_x1		:16;	//(15:0,NA,3839) //win_w0_x1
	UINT32 reg_core1_win_mot_win_w0_y1		:16;	//(31:16,NA,2159) //win_w0_y1
	};
}PE_O22F22_SHP_CORE1_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106AC RW 0x0000_0000
	UINT32 reg_core1_win_mot_win_w1_x0		:16;	//(15:0,NA,0) //win_w1_x0
	UINT32 reg_core1_win_mot_win_w1_y0		:16;	//(31:16,NA,0) //win_w1_y0
	};
}PE_O22F22_SHP_CORE1_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106B0 RW 0x086F_0EFF
	UINT32 reg_core1_win_mot_win_w1_x1		:16;	//(15:0,NA,3839) //win_w1_x1
	UINT32 reg_core1_win_mot_win_w1_y1		:16;	//(31:16,NA,2159) //win_w1_y1
	};
}PE_O22F22_SHP_CORE1_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106C0 RW 0x0000_0000
	UINT32 reg_obj_shp_en					:1; //(0:0,NA,0) //0 : disable	1 : enable
	UINT32 resvd0							:3;
	UINT32 reg_obj_sel_bit					:1; //(4:4,NA,0) //0 : 7bit 1 : 6bit
	UINT32 resvd1							:27;
	};
}PE_O22F22_SHP_OBJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106C4 RW 0x4080_005a
	UINT32 reg_obj_face_gain_lut_y0 		:8; //(7:0,NA,90) //object face gain LUT , y2
	UINT32 reg_obj_face_gain_lut_x0 		:8; //(15:8,NA,0) //object face gain LUT , x2
	UINT32 reg_obj_face_gain_lut_y1 		:8; //(23:16,NA,128) //object face gain LUT , y3
	UINT32 reg_obj_face_gain_lut_x1 		:8; //(31:24,NA,64) //object face gain LUT , x3
	};
}PE_O22F22_SHP_OBJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106C8 RW 0xc4ff_6090
	UINT32 reg_obj_face_gain_lut_y2 		:8; //(7:0,NA,144) //object face gain LUT , y0
	UINT32 reg_obj_face_gain_lut_x2 		:8; //(15:8,NA,96) //object face gain LUT , x0
	UINT32 reg_obj_face_gain_lut_y3 		:8; //(23:16,NA,255) //object face gain LUT , y1
	UINT32 reg_obj_face_gain_lut_x3 		:8; //(31:24,NA,196) //object face gain LUT , x1
	};
}PE_O22F22_SHP_OBJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106CC RW 0x2080_005a
	UINT32 reg_obj_obj_gain_lut_y0			:8; //(7:0,NA,90) //object object gain LUT , y2
	UINT32 reg_obj_obj_gain_lut_x0			:8; //(15:8,NA,0) //object object gain LUT , x2
	UINT32 reg_obj_obj_gain_lut_y1			:8; //(23:16,NA,128) //object object gain LUT , y3
	UINT32 reg_obj_obj_gain_lut_x1			:8; //(31:24,NA,32) //object object gain LUT , x3
	};
}PE_O22F22_SHP_OBJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106D0 RW 0x90b0_4090
	UINT32 reg_obj_obj_gain_lut_y2			:8; //(7:0,NA,144) //object object gain LUT , y0
	UINT32 reg_obj_obj_gain_lut_x2			:8; //(15:8,NA,64) //object object gain LUT , x0
	UINT32 reg_obj_obj_gain_lut_y3			:8; //(23:16,NA,176) //object object gain LUT , y1
	UINT32 reg_obj_obj_gain_lut_x3			:8; //(31:24,NA,144) //object object gain LUT , x1
	};
}PE_O22F22_SHP_OBJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106D4 RW 0x1090_00ac
	UINT32 reg_obj_final_blend_obj_lut_y0	:8; //(7:0,NA,172) //object final_blend_obj LUT , y2
	UINT32 reg_obj_final_blend_obj_lut_x0	:8; //(15:8,NA,0) //object final_blend_obj LUT , x2
	UINT32 reg_obj_final_blend_obj_lut_y1	:8; //(23:16,NA,144) //object final_blend_obj LUT , y3
	UINT32 reg_obj_final_blend_obj_lut_x1	:8; //(31:24,NA,16) //object final_blend_obj LUT , x3
	};
}PE_O22F22_SHP_OBJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106D8 RW 0x8000_2060
	UINT32 reg_obj_final_blend_obj_lut_y2	:8; //(7:0,NA,96) //object final_blend_obj LUT , y0
	UINT32 reg_obj_final_blend_obj_lut_x2	:8; //(15:8,NA,32) //object final_blend_obj LUT , x0
	UINT32 reg_obj_final_blend_obj_lut_y3	:8; //(23:16,NA,0) //object final_blend_obj LUT , y1
	UINT32 reg_obj_final_blend_obj_lut_x3	:8; //(31:24,NA,128) //object final_blend_obj LUT , x1
	};
}PE_O22F22_SHP_OBJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106DC RW 0x10dc_00c4
	UINT32 reg_obj_final_blend_face_lut_y0	:8; //(7:0,NA,196) //object final_blend_face LUT , y2
	UINT32 reg_obj_final_blend_face_lut_x0	:8; //(15:8,NA,0) //object final_blend_face LUT , x2
	UINT32 reg_obj_final_blend_face_lut_y1	:8; //(23:16,NA,220) //object final_blend_face LUT , y3
	UINT32 reg_obj_final_blend_face_lut_x1	:8; //(31:24,NA,16) //object final_blend_face LUT , x3
	};
}PE_O22F22_SHP_OBJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106E0 RW 0x40ff_20dc
	UINT32 reg_obj_final_blend_face_lut_y2	:8; //(7:0,NA,220) //object final_blend_face LUT , y0
	UINT32 reg_obj_final_blend_face_lut_x2	:8; //(15:8,NA,32) //object final_blend_face LUT , x0
	UINT32 reg_obj_final_blend_face_lut_y3	:8; //(23:16,NA,255) //object final_blend_face LUT , y1
	UINT32 reg_obj_final_blend_face_lut_x3	:8; //(31:24,NA,64) //object final_blend_face LUT , x1
	};
}PE_O22F22_SHP_OBJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106E4 RW 0x3060_0050
	UINT32 reg_obj_master_gain_a_map_lut_y0 		:8; //(7:0,NA,80) //object master_gain LUT , y2
	UINT32 reg_obj_master_gain_a_map_lut_x0 		:8; //(15:8,NA,0) //object master_gain LUT , x2
	UINT32 reg_obj_master_gain_a_map_lut_y1 		:8; //(23:16,NA,96) //object master_gain LUT , y3
	UINT32 reg_obj_master_gain_a_map_lut_x1 		:8; //(31:24,NA,48) //object master_gain LUT , x3
	};
}PE_O22F22_SHP_OBJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106E8 RW 0x9080_6080
	UINT32 reg_obj_master_gain_a_map_lut_y2		:8; //(7:0,NA,128) //object master_gain LUT , y0
	UINT32 reg_obj_master_gain_a_map_lut_x2		:8; //(15:8,NA,96) //object master_gain LUT , x0
	UINT32 reg_obj_master_gain_a_map_lut_y3		:8; //(23:16,NA,128) //object master_gain LUT , y1
	UINT32 reg_obj_master_gain_a_map_lut_x3		:8; //(31:24,NA,144) //object master_gain LUT , x1
	};
}PE_O22F22_SHP_OBJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106EC RW 0x3060_0050
	UINT32 reg_obj_master_gain_t_map_lut_y0 :8; //(7:0,NA,80) //object master_gain LUT , y2
	UINT32 reg_obj_master_gain_t_map_lut_x0 :8; //(15:8,NA,0) //object master_gain LUT , x2
	UINT32 reg_obj_master_gain_t_map_lut_y1 :8; //(23:16,NA,96) //object master_gain LUT , y3
	UINT32 reg_obj_master_gain_t_map_lut_x1 :8; //(31:24,NA,48) //object master_gain LUT , x3
	};
}PE_O22F22_SHP_OBJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34106F0 RW 0x9080_6080
	UINT32 reg_obj_master_gain_t_map_lut_y2 :8; //(7:0,NA,128) //object master_gain LUT , y0
	UINT32 reg_obj_master_gain_t_map_lut_x2 :8; //(15:8,NA,96) //object master_gain LUT , x0
	UINT32 reg_obj_master_gain_t_map_lut_y3 :8; //(23:16,NA,128) //object master_gain LUT , y1
	UINT32 reg_obj_master_gain_t_map_lut_x3 :8; //(31:24,NA,144) //object master_gain LUT , x1
	};
}PE_O22F22_SHP_OBJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107A0 RO 0x0000_0000
	UINT32 reg_core0_mon_core_fin_out_vert_cnt :12; //(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0							:4;
	UINT32 reg_core0_mon_core_fin_in_vert_cnt :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107A4 RO 0x0000_0000
	UINT32 reg_core0_mon_in_vert_cnt		:12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0							:4;
	UINT32 reg_core0_mon_in_hori_cnt		:12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107A8 RO 0x0000_0000
	UINT32 reg_core0_mon_out_vert_cnt		:12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0							:4;
	UINT32 reg_core0_mon_out_hori_cnt		:12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107AC RO 0x0000_0000
	UINT32 reg_core0_mon_fin_out_vert_cnt	:12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0							:4;
	UINT32 reg_core0_mon_fin_in_vert_cnt	:12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107B0 RO 0x0000_0000
	UINT32 reg_core0_mon_shp_i_sucfail		:32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O22F22_SHP_CORE0_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107B4 RO 0x0000_0000
	UINT32 reg_core0_mon_shp_o_sucfail		:32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O22F22_SHP_CORE0_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107D0 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE0_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107D4 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE0_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107D8 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE0_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107DC RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE0_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107E0 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107E4 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_MOTION_GAIN_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107E8 RO 0x0000_0000
	UINT32 ro_edge_status_0 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_1 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_EDGE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107EC RO 0x0000_0000
	UINT32 ro_edge_status_2 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_3 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_EDGE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107F0 RO 0x0000_0000
	UINT32 ro_edge_status_4 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_5 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_EDGE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107F4 RO 0x0000_0000
	UINT32 ro_edge_status_6 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_7 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_EDGE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107F8 RO 0x0000_0000
	UINT32 ro_edge_status_8 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_9 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_EDGE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34107FC RO 0x0000_0000
	UINT32 ro_edge_status_10				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_11				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_EDGE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410800 RO 0x0000_0000
	UINT32 reg_core0_tmap_status_window0	:32;	//(31:0,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410804 RO 0x0000_0000
	UINT32 reg_core0_tmap_status_window1	:32;	//(31:0,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410808 RO 0x0000_0000
	UINT32 reg_core0_tmap_status_0			:16;	//(15:0,NA,0) //
	UINT32 reg_core0_tmap_status_1			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341080C RO 0x0000_0000
	UINT32 reg_core0_tmap_status_2			:16;	//(15:0,NA,0) //
	UINT32 reg_core0_tmap_status_3			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410810 RO 0x0000_0000
	UINT32 reg_core0_tmap_status_4			:16;	//(15:0,NA,0) //
	UINT32 reg_core0_tmap_status_5			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410814 RO 0x0000_0000
	UINT32 reg_core0_tmap_status_6			:16;	//(15:0,NA,0) //
	UINT32 reg_core0_tmap_status_7			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410818 RO 0x0000_0000
	UINT32 reg_core0_tmap_status_8			:16;	//(15:0,NA,0) //
	UINT32 reg_core0_tmap_status_9			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341081C RO 0x0000_0000
	UINT32 reg_core0_tmap_status_10 		:16;	//(15:0,NA,0) //
	UINT32 reg_core0_tmap_status_11 		:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE0_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410820 RW 0x0000_0000
	UINT32 reg_core0_win_face_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_face_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_face_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_face_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_face_win_en		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_face_bdr_alpha 	:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_face_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_face_bdr_en		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_face_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_face_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_face_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410824 RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w0_x0 	:12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w0_y0 	:12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410828 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w0_x1 	:12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w0_y1 	:12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341082C RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w1_x0 	:12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w1_y0 	:12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410830 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w1_x1 	:12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w1_y1 	:12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410834 RW 0x0000_0000
	UINT32 reg_core0_win_face_value 		:8; //(7:0,NA,0) //force face value
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_CORE0_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410838 RW 0x0000_0000
	UINT32 reg_core0_win_body_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_body_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_body_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_body_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_body_win_en		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_body_bdr_alpha 	:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_body_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_body_bdr_en		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_body_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_body_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_body_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE0_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341083C RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w0_x0 	:12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w0_y0 	:12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410840 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w0_x1 	:12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w0_y1 	:12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410844 RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w1_x0 	:12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w1_y0 	:12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410848 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w1_x1 	:12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w1_y1 	:12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE0_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF341084C RW 0x0000_0000
	UINT32 reg_core0_win_body_value 		:8; //(7:0,NA,0) //force body value
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_CORE0_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109A0 RO 0x0000_0000
	UINT32 reg_core1_mon_core_fin_out_vert_cnt :12; //(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0							:4;
	UINT32 reg_core1_mon_core_fin_in_vert_cnt :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109A4 RO 0x0000_0000
	UINT32 reg_core1_mon_in_vert_cnt		:12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0							:4;
	UINT32 reg_core1_mon_in_hori_cnt		:12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109A8 RO 0x0000_0000
	UINT32 reg_core1_mon_out_vert_cnt		:12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0							:4;
	UINT32 reg_core1_mon_out_hori_cnt		:12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109AC RO 0x0000_0000
	UINT32 reg_core1_mon_fin_out_vert_cnt	:12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0							:4;
	UINT32 reg_core1_mon_fin_in_vert_cnt	:12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109B0 RO 0x0000_0000
	UINT32 reg_core1_mon_shp_i_sucfail		:32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O22F22_SHP_CORE1_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109B4 RO 0x0000_0000
	UINT32 reg_core1_mon_shp_o_sucfail		:32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O22F22_SHP_CORE1_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109D0 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE1_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109D4 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE1_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109D8 RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE1_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109DC RO 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_CORE1_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109E0 RO 0x0000_0000
	UINT32 ro_edge_status_0 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_1 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_EDGE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109E4 RO 0x0000_0000
	UINT32 ro_edge_status_2 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_3 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_EDGE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109E8 RO 0x0000_0000
	UINT32 ro_edge_status_4 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_5 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_EDGE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109EC RO 0x0000_0000
	UINT32 ro_edge_status_6 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_7 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_EDGE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109F0 RO 0x0000_0000
	UINT32 ro_edge_status_8 				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_9 				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_EDGE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF34109F4 RO 0x0000_0000
	UINT32 ro_edge_status_10				:16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_11				:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_EDGE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A00 RO 0x0000_0000
	UINT32 reg_core1_tmap_status_window0	:32;	//(31:0,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A04 RO 0x0000_0000
	UINT32 reg_core1_tmap_status_window1	:32;	//(31:0,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A08 RO 0x0000_0000
	UINT32 reg_core1_tmap_status_0			:16;	//(15:0,NA,0) //
	UINT32 reg_core1_tmap_status_1			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A0C RO 0x0000_0000
	UINT32 reg_core1_tmap_status_2			:16;	//(15:0,NA,0) //
	UINT32 reg_core1_tmap_status_3			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A10 RO 0x0000_0000
	UINT32 reg_core1_tmap_status_4			:16;	//(15:0,NA,0) //
	UINT32 reg_core1_tmap_status_5			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A14 RO 0x0000_0000
	UINT32 reg_core1_tmap_status_6			:16;	//(15:0,NA,0) //
	UINT32 reg_core1_tmap_status_7			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A18 RO 0x0000_0000
	UINT32 reg_core1_tmap_status_8			:16;	//(15:0,NA,0) //
	UINT32 reg_core1_tmap_status_9			:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A1C RO 0x0000_0000
	UINT32 reg_core1_tmap_status_10 		:16;	//(15:0,NA,0) //
	UINT32 reg_core1_tmap_status_11 		:16;	//(31:16,NA,0) //
	};
}PE_O22F22_SHP_CORE1_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A20 RW 0x0000_0000
	UINT32 reg_core0_win_face_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_face_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_face_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_face_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_face_win_en		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_face_bdr_alpha 	:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_face_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_face_bdr_en		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_face_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_face_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_face_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A24 RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w0_x0 	:12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w0_y0 	:12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A28 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w0_x1 	:12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w0_y1 	:12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A2C RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w1_x0 	:12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w1_y0 	:12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A30 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w1_x1 	:12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_face_win_w1_y1 	:12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A34 RW 0x0000_0000
	UINT32 reg_core0_win_face_value 		:8; //(7:0,NA,0) //force face value
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_CORE1_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A38 RW 0x0000_0000
	UINT32 reg_core0_win_body_win0_en		:1; //(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_body_win1_en		:1; //(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_body_win01_en		:1; //(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd							:3;
	UINT32 reg_core0_win_body_win_outside	:1; //(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_body_win_en		:1; //(7:7,NA,0) //0: active area = full screen 1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_body_bdr_alpha 	:5; //(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_body_bdr_wid		:2; //(14:13,NA,0) //border width
	UINT32 reg_core0_win_body_bdr_en		:1; //(15:15,NA,0) //border enable
	UINT32 reg_core0_win_body_cr5			:5; //(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_body_cb5			:5; //(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_body_yy6			:6; //(31:26,NA,0) //border color: yy6
	};
}PE_O22F22_SHP_CORE1_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A3C RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w0_x0 	:12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w0_y0 	:12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A40 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w0_x1 	:12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w0_y1 	:12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A44 RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w1_x0 	:12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w1_y0 	:12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A48 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w1_x1 	:12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0							:4;
	UINT32 reg_core0_win_body_win_w1_y1 	:12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1							:4;
	};
}PE_O22F22_SHP_CORE1_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410A4C RW 0x0000_0000
	UINT32 reg_core0_win_body_value 		:8; //(7:0,NA,0) //force body value
	UINT32 resvd							:24;
	};
}PE_O22F22_SHP_CORE1_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410BF0 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410BF4 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410BF8 RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF3410BFC RW 0x0000_0000
	UINT32 tdata0							:32;
	};
}PE_O22F22_SHP_FSW_CTRL_03_T;


/**
 *	shp hw param reg type
 */
 typedef struct {
	PE_O22F22_SHP_NEW_FD_CTRL_00_T                shp_new_fd_ctrl_00;	//0xF3410020
	PE_O22F22_SHP_NEW_FD_CTRL_01_T                shp_new_fd_ctrl_01;	//0xF3410024
	PE_O22F22_SHP_NEW_FD_CTRL_02_T                shp_new_fd_ctrl_02;	//0xF3410028
	PE_O22F22_SHP_NEW_FD_CTRL_03_T                shp_new_fd_ctrl_03;	//0xF341002C
	PE_O22F22_SHP_NEW_FD_CTRL_04_T                shp_new_fd_ctrl_04;	//0xF3410030
	PE_O22F22_SHP_TEXT_REGION_MAP_00_T        shp_text_region_map_00;	//0xF3410034
	PE_O22F22_SHP_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_O22F22_SHP_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_O22F22_SHP_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	PE_O22F22_SHP_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_O22F22_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O22F22_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O22F22_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O22F22_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O22F22_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O22F22_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O22F22_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O22F22_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O22F22_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O22F22_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O22F22_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O22F22_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O22F22_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O22F22_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O22F22_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O22F22_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O22F22_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O22F22_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O22F22_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_O22F22_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O22F22_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O22F22_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O22F22_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_O22F22_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O22F22_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O22F22_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O22F22_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O22F22_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O22F22_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O22F22_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O22F22_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O22F22_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O22F22_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O22F22_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O22F22_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O22F22_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O22F22_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_O22F22_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O22F22_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O22F22_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O22F22_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O22F22_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_O22F22_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O22F22_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O22F22_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O22F22_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O22F22_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O22F22_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O22F22_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O22F22_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O22F22_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O22F22_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O22F22_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O22F22_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O22F22_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O22F22_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O22F22_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O22F22_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O22F22_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O22F22_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O22F22_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O22F22_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O22F22_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_O22F22_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O22F22_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O22F22_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O22F22_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O22F22_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_O22F22_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O22F22_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O22F22_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O22F22_SHP_CORE0_TGEN_CTRL_03_C0_T                shp_core0_tgen_ctrl_03_C0;	//0x024C
	PE_O22F22_SHP_CORE0_TGEN_CTRL_03_C1_T                shp_core0_tgen_ctrl_03_C1;	//0x0250
	PE_O22F22_SHP_CORE1_TGEN_CTRL_03_C0_T                shp_core1_tgen_ctrl_03_C0;	//0x024C
	PE_O22F22_SHP_CORE1_TGEN_CTRL_03_C1_T                shp_core1_tgen_ctrl_03_C1;	//0x0250
	PE_O22F22_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O22F22_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O22F22_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O22F22_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O22F22_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O22F22_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O22F22_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O22F22_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O22F22_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_O22F22_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O22F22_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O22F22_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O22F22_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O22F22_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O22F22_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O22F22_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O22F22_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O22F22_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O22F22_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O22F22_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O22F22_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O22F22_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O22F22_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O22F22_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O22F22_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O22F22_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O22F22_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O22F22_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O22F22_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O22F22_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O22F22_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O22F22_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O22F22_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O22F22_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O22F22_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O22F22_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O22F22_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O22F22_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O22F22_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O22F22_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O22F22_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O22F22_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O22F22_SHP_CORE0_NNTG_CTRL_01_C0_T                      shp_core0_nntg_ctrl_01_C0;	//0x0304
	PE_O22F22_SHP_CORE0_NNTG_CTRL_02_C0_T                      shp_core0_nntg_ctrl_02_C0;	//0x0308
	PE_O22F22_SHP_CORE0_NNTG_CTRL_03_C0_T                      shp_core0_nntg_ctrl_03_C0;	//0x030C
	PE_O22F22_SHP_CORE0_NNTG_CTRL_04_C0_T                      shp_core0_nntg_ctrl_04_C0;	//0x0310
	PE_O22F22_SHP_CORE0_NNTG_CTRL_05_C0_T                      shp_core0_nntg_ctrl_05_C0;	//0x0314
	PE_O22F22_SHP_CORE0_NNTG_CTRL_01_C1_T                      shp_core0_nntg_ctrl_01_C1;	//0x0318
	PE_O22F22_SHP_CORE0_NNTG_CTRL_02_C1_T                      shp_core0_nntg_ctrl_02_C1;	//0x031C
	PE_O22F22_SHP_CORE0_NNTG_CTRL_03_C1_T                      shp_core0_nntg_ctrl_03_C1;	//0x0320
	PE_O22F22_SHP_CORE0_NNTG_CTRL_04_C1_T                      shp_core0_nntg_ctrl_04_C1;	//0x0324
	PE_O22F22_SHP_CORE0_NNTG_CTRL_05_C1_T                      shp_core0_nntg_ctrl_05_C1;	//0x0328
	PE_O22F22_SHP_CORE1_NNTG_CTRL_01_C0_T                      shp_core1_nntg_ctrl_01_C0;	//0x0304
	PE_O22F22_SHP_CORE1_NNTG_CTRL_02_C0_T                      shp_core1_nntg_ctrl_02_C0;	//0x0308
	PE_O22F22_SHP_CORE1_NNTG_CTRL_03_C0_T                      shp_core1_nntg_ctrl_03_C0;	//0x030C
	PE_O22F22_SHP_CORE1_NNTG_CTRL_04_C0_T                      shp_core1_nntg_ctrl_04_C0;	//0x0310
	PE_O22F22_SHP_CORE1_NNTG_CTRL_05_C0_T                      shp_core1_nntg_ctrl_05_C0;	//0x0314
	PE_O22F22_SHP_CORE1_NNTG_CTRL_01_C1_T                      shp_core1_nntg_ctrl_01_C1;	//0x0318
	PE_O22F22_SHP_CORE1_NNTG_CTRL_02_C1_T                      shp_core1_nntg_ctrl_02_C1;	//0x031C
	PE_O22F22_SHP_CORE1_NNTG_CTRL_03_C1_T                      shp_core1_nntg_ctrl_03_C1;	//0x0320
	PE_O22F22_SHP_CORE1_NNTG_CTRL_04_C1_T                      shp_core1_nntg_ctrl_04_C1;	//0x0324
	PE_O22F22_SHP_CORE1_NNTG_CTRL_05_C1_T                      shp_core1_nntg_ctrl_05_C1;	//0x0328
	PE_O22F22_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O22F22_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O22F22_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O22F22_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O22F22_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O22F22_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O22F22_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O22F22_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O22F22_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O22F22_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O22F22_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_O22F22_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O22F22_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O22F22_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_O22F22_SHP_DP_SUM_CTRL_03_T                       shp_dp_sum_ctrl_03;	//0x036C
	PE_O22F22_SHP_DP_SUM_CTRL_04_T                       shp_dp_sum_ctrl_04;	//0x0370
	PE_O22F22_SHP_DP_SUM_CTRL_05_T                       shp_dp_sum_ctrl_05;	//0x0374
	PE_O22F22_SHP_DP_SUM_CTRL_06_T                       shp_dp_sum_ctrl_06;	//0x0378
	PE_O22F22_SHP_DP_SUM_CTRL_07_T                       shp_dp_sum_ctrl_07;	//0x037C
	PE_O22F22_SHP_DP_SUM_CTRL_08_T                       shp_dp_sum_ctrl_08;	//0x0380
	PE_O22F22_SHP_DP_SUM_CTRL_09_T                       shp_dp_sum_ctrl_09;	//0xCC462384
	PE_O22F22_SHP_DP_SUM_CTRL_0A_T                       shp_dp_sum_ctrl_0a;	//0xCC462388
	PE_O22F22_SHP_PSP_CTRL_00_T                          shp_psp_ctrl_00;	    //0x0390
	PE_O22F22_SHP_DP_SUM_CTRL_0B_T                       shp_dp_sum_ctrl_0b;	//0xCC462394
	PE_O22F22_SHP_DP_SUM_CTRL_0C_T                       shp_dp_sum_ctrl_0c;	//0xCC462398
	PE_O22F22_SHP_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O22F22_SHP_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x03C4
	PE_O22F22_SHP_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x03C8
	PE_O22F22_SHP_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O22F22_SHP_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x03D0
	PE_O22F22_SHP_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x03D4
	PE_O22F22_SHP_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x03D8
	PE_O22F22_SHP_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x03DC
	PE_O22F22_SHP_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x03E0
	PE_O22F22_SHP_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x03E4
	PE_O22F22_SHP_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x03E8
	PE_O22F22_SHP_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x03EC
	PE_O22F22_SHP_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O22F22_SHP_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O22F22_SHP_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O22F22_SHP_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O22F22_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O22F22_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O22F22_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O22F22_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O22F22_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O22F22_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O22F22_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O22F22_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O22F22_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O22F22_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O22F22_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O22F22_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O22F22_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O22F22_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O22F22_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O22F22_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O22F22_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O22F22_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O22F22_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O22F22_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O22F22_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O22F22_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O22F22_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O22F22_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O22F22_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O22F22_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O22F22_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O22F22_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O22F22_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O22F22_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O22F22_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O22F22_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O22F22_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	PE_O22F22_SHP_CHROMA_CTRL_00_T                       shp_chroma_ctrl_00;	//0x0500
	PE_O22F22_SHP_CHROMA_CTRL_01_T                       shp_chroma_ctrl_01;	//0x0504
	PE_O22F22_SHP_CHROMA_CTRL_02_T                       shp_chroma_ctrl_02;	//0x0508
	PE_O22F22_SHP_CHROMA_CTRL_03_T                       shp_chroma_ctrl_03;	//0x050C
	PE_O22F22_SHP_CHROMA_CTRL_04_T                       shp_chroma_ctrl_04;	//0x0510
	PE_O22F22_SHP_CHROMA_CTRL_05_T                       shp_chroma_ctrl_05;	//0x0514
	PE_O22F22_SHP_CHROMA_CTRL_06_T                       shp_chroma_ctrl_06;	//0x0518
	PE_O22F22_SHP_CHROMA_CTRL_07_T                       shp_chroma_ctrl_07;	//0x051C
	PE_O22F22_SHP_CHROMA_CTRL_08_T                       shp_chroma_ctrl_08;	//0x0520
	PE_O22F22_SHP_CHROMA_CTRL_09_T                       shp_chroma_ctrl_09;	//0x0524
	PE_O22F22_SHP_CHROMA_CTRL_0A_T                       shp_chroma_ctrl_0a;	//0x0528
	PE_O22F22_SHP_CHROMA_CTRL_0B_T                       shp_chroma_ctrl_0b;	//0x052C
	PE_O22F22_SHP_CHROMA_CTRL_0C_T                       shp_chroma_ctrl_0c;	//0x0530
	PE_O22F22_SHP_CHROMA_CTRL_0D_T                       shp_chroma_ctrl_0d;	//0x0534
	PE_O22F22_SHP_CHROMA_CTRL_0E_T                       shp_chroma_ctrl_0e;	//0x0538
	PE_O22F22_SHP_FRC_FLICK_CTRL_00_T                    shp_frc_flick_ctrl_00;	//0x0560
	PE_O22F22_SHP_FRC_FLICK_CTRL_01_T                    shp_frc_flick_ctrl_01;	//0x0564
	PE_O22F22_SHP_FRC_FLICK_CTRL_02_T                    shp_frc_flick_ctrl_02;	//0x0568
	PE_O22F22_SHP_FRC_FLICK_CTRL_03_T                    shp_frc_flick_ctrl_03;	//0x056C
	PE_O22F22_SHP_FRC_BLUR_CTRL_00_T                     shp_frc_blur_ctrl_00;	//0xCC462570
	PE_O22F22_SHP_FRC_BLUR_CTRL_01_T                     shp_frc_blur_ctrl_01;	//0xCC462574
	PE_O22F22_SHP_FRC_BLUR_CTRL_02_T                     shp_frc_blur_ctrl_02;	//0xCC462578
	PE_O22F22_SHP_FRC_BLUR_CTRL_03_T                     shp_frc_blur_ctrl_03;	//0xCC46257C
	PE_O22F22_SHP_FRC_BLUR_CTRL_04_T                     shp_frc_blur_ctrl_04;	//0xCC462580
	PE_O22F22_SHP_FRC_BLUR_CTRL_05_T                     shp_frc_blur_ctrl_05;	//0xCC462584
	PE_O22F22_SHP_FRC_BLUR_CTRL_06_T                     shp_frc_blur_ctrl_06;	//0xCC462588
	PE_O22F22_SHP_FRC_HALO_CTRL_00_T                     shp_frc_halo_ctrl_00;	//0xCC462590
	PE_O22F22_SHP_FRC_HALO_CTRL_01_T                     shp_frc_halo_ctrl_01;	//0xCC462594
	PE_O22F22_SHP_FRC_HALO_CTRL_02_T                     shp_frc_halo_ctrl_02;	//0xCC462598
	PE_O22F22_SHP_FRC_HALO_CTRL_03_T                     shp_frc_halo_ctrl_03;	//0xCC46259C
	PE_O22F22_SHP_MOTION_GAIN_CTRL_00_T                  shp_motion_gain_ctrl_00;	//0x0600
	PE_O22F22_SHP_MOTION_GAIN_CTRL_01_T                  shp_motion_gain_ctrl_01;	//0x0604
	PE_O22F22_SHP_MOTION_GAIN_CTRL_02_T                  shp_motion_gain_ctrl_02;	//0x0608
	PE_O22F22_SHP_MOTION_GAIN_CTRL_03_T                  shp_motion_gain_ctrl_03;	//0x060C
	PE_O22F22_SHP_MOTION_GAIN_CTRL_04_T                  shp_motion_gain_ctrl_04;	//0x0610
	PE_O22F22_SHP_MOTION_GAIN_CTRL_05_T                  shp_motion_gain_ctrl_05;	//0x0614
	PE_O22F22_SHP_MOTION_GAIN_CTRL_06_T                  shp_motion_gain_ctrl_06;	//0x0618
	PE_O22F22_SHP_MOTION_GAIN_CTRL_07_T                  shp_motion_gain_ctrl_07;	//0x061C
	PE_O22F22_SHP_MOTION_GAIN_CTRL_08_T                  shp_motion_gain_ctrl_08;	//0x0620
	PE_O22F22_SHP_MOTION_GAIN_CTRL_09_T                  shp_motion_gain_ctrl_09;	//0x0624
	PE_O22F22_SHP_MOTION_GAIN_CTRL_0A_T                  shp_motion_gain_ctrl_0a;	//0x0628
	PE_O22F22_SHP_MOTION_GAIN_CTRL_0B_T                  shp_motion_gain_ctrl_0b;	//0x062C
	PE_O22F22_SHP_MOTION_GAIN_CTRL_0C_T                  shp_motion_gain_ctrl_0c;	//0x0630
	PE_O22F22_SHP_MOTION_PROT_CTRL_00_T                  shp_motion_prot_ctrl_00;	//0x0640
	PE_O22F22_SHP_MOTION_PROT_CTRL_01_T                  shp_motion_prot_ctrl_01;	//0x0644
	PE_O22F22_SHP_MOTION_PROT_CTRL_02_T                  shp_motion_prot_ctrl_02;	//0x0648
	PE_O22F22_SHP_MOTION_PROT_CTRL_03_T                  shp_motion_prot_ctrl_03;	//0x064C
	PE_O22F22_SHP_MOTION_PROT_CTRL_04_T                  shp_motion_prot_ctrl_04;	//0x0650
	PE_O22F22_SHP_OBJ_CTRL_00_T                          shp_obj_ctrl_00;	//0x0690
	PE_O22F22_SHP_OBJ_CTRL_01_T                          shp_obj_ctrl_01;	//0x0694
	PE_O22F22_SHP_OBJ_CTRL_02_T                          shp_obj_ctrl_02;	//0x0698
	PE_O22F22_SHP_OBJ_CTRL_03_T                          shp_obj_ctrl_03;	//0x069C
	PE_O22F22_SHP_OBJ_CTRL_04_T                          shp_obj_ctrl_04;	//0x06A0
	PE_O22F22_SHP_OBJ_CTRL_05_T                          shp_obj_ctrl_05;	//0x06A4
	PE_O22F22_SHP_OBJ_CTRL_06_T                          shp_obj_ctrl_06;	//0x06A8
	PE_O22F22_SHP_OBJ_CTRL_07_T                          shp_obj_ctrl_07;	//0x06AC
	PE_O22F22_SHP_OBJ_CTRL_08_T                          shp_obj_ctrl_08;	//0x06B0
	PE_O22F22_SHP_OBJ_CTRL_09_T                          shp_obj_ctrl_09;	//0x06B4
	PE_O22F22_SHP_OBJ_CTRL_0A_T                          shp_obj_ctrl_0a;	//0x06B8
	PE_O22F22_SHP_OBJ_CTRL_0B_T                          shp_obj_ctrl_0b;	//0xCC4626BC
	PE_O22F22_SHP_OBJ_CTRL_0C_T                          shp_obj_ctrl_0c;	//0xCC4626C0
}PE_RES_HW_PARAM_REG_O22F22_T;
typedef struct {
#ifdef PE_HW_O22_BRINGUP
	PE_O22_SHP_NEW_FD_CTRL_00_T                 shp_new_fd_ctrl_00;	//0xCC462014
	PE_O22_SHP_NEW_FD_CTRL_01_T                 shp_new_fd_ctrl_01;	//0xCC462018
	PE_O22_SHP_NEW_FD_CTRL_02_T                 shp_new_fd_ctrl_02;	//0xCC46201C
	PE_O22_SHP_NEW_FD_CTRL_03_T                 shp_new_fd_ctrl_03;	//0xCC462020
	PE_O22_SHP_NEW_FD_CTRL_04_T                 shp_new_fd_ctrl_04;	//0xCC462024
	PE_O22_SHP_TEXT_REGION_MAP_00_T         shp_text_region_map_00;	//0xCC462028
	PE_O22_SHP_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_O22_SHP_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_O22_SHP_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	PE_O22_SHP_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_O22_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O22_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O22_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O22_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O22_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O22_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O22_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O22_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O22_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O22_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O22_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O22_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O22_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O22_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O22_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O22_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O22_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O22_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O22_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_O22_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O22_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O22_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O22_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_O22_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O22_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O22_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O22_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O22_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O22_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O22_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O22_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O22_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O22_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O22_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O22_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O22_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O22_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_O22_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O22_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O22_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O22_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O22_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_O22_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O22_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O22_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O22_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O22_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O22_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O22_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O22_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O22_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O22_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O22_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O22_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O22_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O22_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O22_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O22_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O22_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O22_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O22_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O22_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O22_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_O22_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O22_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O22_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O22_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O22_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_O22_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O22_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O22_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O22_SHP_TGEN_CTRL_03_C0_T                      shp_core0_tgen_ctrl_03;	//0x024C
	PE_O22_SHP_TGEN_CTRL_03_C1_T                      shp_core1_tgen_ctrl_03;	//0x0250
	PE_O22_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O22_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O22_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O22_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O22_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O22_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O22_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O22_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O22_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_O22_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O22_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O22_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O22_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O22_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O22_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O22_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O22_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O22_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O22_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O22_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O22_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O22_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O22_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O22_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O22_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O22_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O22_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O22_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O22_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O22_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O22_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O22_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O22_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O22_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O22_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O22_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O22_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O22_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O22_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O22_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O22_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O22_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O22_SHP_NNTG_CTRL_01_C0_T                      shp_core0_nntg_ctrl_01;	//0x0304
	PE_O22_SHP_NNTG_CTRL_02_C0_T                      shp_core0_nntg_ctrl_02;	//0x0308
	PE_O22_SHP_NNTG_CTRL_03_C0_T                      shp_core0_nntg_ctrl_03;	//0x030C
	PE_O22_SHP_NNTG_CTRL_04_C0_T                      shp_core0_nntg_ctrl_04;	//0x0310
	PE_O22_SHP_NNTG_CTRL_05_C0_T                      shp_core0_nntg_ctrl_05;	//0x0314
	PE_O22_SHP_NNTG_CTRL_01_C1_T                      shp_core1_nntg_ctrl_01;	//0x0318
	PE_O22_SHP_NNTG_CTRL_02_C1_T                      shp_core1_nntg_ctrl_02;	//0x031C
	PE_O22_SHP_NNTG_CTRL_03_C1_T                      shp_core1_nntg_ctrl_03;	//0x0320
	PE_O22_SHP_NNTG_CTRL_04_C1_T                      shp_core1_nntg_ctrl_04;	//0x0324
	PE_O22_SHP_NNTG_CTRL_05_C1_T                      shp_core1_nntg_ctrl_05;	//0x0328
	PE_O22_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O22_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O22_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O22_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O22_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O22_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O22_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O22_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O22_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O22_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O22_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_O22_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O22_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O22_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_O22_SHP_DP_SUM_CTRL_03_T                       shp_dp_sum_ctrl_03;	//0x036C
	PE_O22_SHP_DP_SUM_CTRL_04_T                       shp_dp_sum_ctrl_04;	//0x0370
	PE_O22_SHP_DP_SUM_CTRL_05_T                       shp_dp_sum_ctrl_05;	//0x0374
	PE_O22_SHP_DP_SUM_CTRL_06_T                       shp_dp_sum_ctrl_06;	//0x0378
	PE_O22_SHP_DP_SUM_CTRL_07_T                       shp_dp_sum_ctrl_07;	//0x037C
	PE_O22_SHP_DP_SUM_CTRL_08_T                       shp_dp_sum_ctrl_08;	//0x0380
	PE_O22_SHP_DP_SUM_CTRL_09_T                       shp_dp_sum_ctrl_09;	//0xCC462384
	PE_O22_SHP_DP_SUM_CTRL_0A_T                       shp_dp_sum_ctrl_0a;	//0xCC462388
	PE_O22_SHP_PSP_CTRL_00_T                          shp_psp_ctrl_00;	    //0x0390
	PE_O22_SHP_DP_SUM_CTRL_0B_T                       shp_dp_sum_ctrl_0b;	//0xCC462394
	PE_O22_SHP_DP_SUM_CTRL_0C_T                       shp_dp_sum_ctrl_0c;	//0xCC462398
	PE_O22_SHP_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O22_SHP_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x03C4
	PE_O22_SHP_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x03C8
	PE_O22_SHP_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O22_SHP_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x03D0
	PE_O22_SHP_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x03D4
	PE_O22_SHP_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x03D8
	PE_O22_SHP_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x03DC
	PE_O22_SHP_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x03E0
	PE_O22_SHP_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x03E4
	PE_O22_SHP_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x03E8
	PE_O22_SHP_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x03EC
	PE_O22_SHP_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O22_SHP_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O22_SHP_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O22_SHP_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O22_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O22_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O22_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O22_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O22_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O22_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O22_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O22_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O22_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O22_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O22_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O22_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O22_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O22_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O22_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O22_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O22_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O22_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O22_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O22_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O22_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O22_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O22_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O22_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O22_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O22_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O22_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O22_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O22_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O22_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O22_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O22_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O22_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_00_T                 shp_dj_text_gain_ctrl_00;	//0xCC4624BC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_01_T                 shp_dj_text_gain_ctrl_01;	//0xCC4624C0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_02_T                 shp_dj_text_gain_ctrl_02;	//0xCC4624C4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_03_T                 shp_dj_text_gain_ctrl_03;	//0xCC4624C8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_04_T                 shp_dj_text_gain_ctrl_04;	//0xCC4624CC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_05_T                 shp_dj_text_gain_ctrl_05;	//0xCC4624D0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_06_T                 shp_dj_text_gain_ctrl_06;	//0xCC4624D4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_07_T                 shp_dj_text_gain_ctrl_07;	//0xCC4624D8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_08_T                 shp_dj_text_gain_ctrl_08;	//0xCC4624DC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_09_T                 shp_dj_text_gain_ctrl_09;	//0xCC4624E0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_10_T                 shp_dj_text_gain_ctrl_10;	//0xCC4624E4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_11_T                 shp_dj_text_gain_ctrl_11;	//0xCC4624E8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_12_T                 shp_dj_text_gain_ctrl_12;	//0xCC4624EC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_13_T                 shp_dj_text_gain_ctrl_13;	//0xCC4624F0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_14_T                 shp_dj_text_gain_ctrl_14;	//0xCC4624F4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_15_T                 shp_dj_text_gain_ctrl_15;	//0xCC4624F8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_16_T                 shp_dj_text_gain_ctrl_16;	//0xCC4624FC
	PE_O22_SHP_CHROMA_CTRL_00_T                       shp_chroma_ctrl_00;	//0x0500
	PE_O22_SHP_CHROMA_CTRL_01_T                       shp_chroma_ctrl_01;	//0x0504
	PE_O22_SHP_CHROMA_CTRL_02_T                       shp_chroma_ctrl_02;	//0x0508
	PE_O22_SHP_CHROMA_CTRL_03_T                       shp_chroma_ctrl_03;	//0x050C
	PE_O22_SHP_CHROMA_CTRL_04_T                       shp_chroma_ctrl_04;	//0x0510
	PE_O22_SHP_CHROMA_CTRL_05_T                       shp_chroma_ctrl_05;	//0x0514
	PE_O22_SHP_CHROMA_CTRL_06_T                       shp_chroma_ctrl_06;	//0x0518
	PE_O22_SHP_CHROMA_CTRL_07_T                       shp_chroma_ctrl_07;	//0x051C
	PE_O22_SHP_CHROMA_CTRL_08_T                       shp_chroma_ctrl_08;	//0x0520
	PE_O22_SHP_CHROMA_CTRL_09_T                       shp_chroma_ctrl_09;	//0x0524
	PE_O22_SHP_CHROMA_CTRL_0A_T                       shp_chroma_ctrl_0a;	//0x0528
	PE_O22_SHP_CHROMA_CTRL_0B_T                       shp_chroma_ctrl_0b;	//0x052C
	PE_O22_SHP_CHROMA_CTRL_0C_T                       shp_chroma_ctrl_0c;	//0x0530
	PE_O22_SHP_CHROMA_CTRL_0D_T                       shp_chroma_ctrl_0d;	//0x0534
	PE_O22_SHP_CHROMA_CTRL_0E_T                       shp_chroma_ctrl_0e;	//0x0538
	PE_O22_SHP_FRC_FLICK_CTRL_00_T                    shp_frc_flick_ctrl_00;	//0x0560
	PE_O22_SHP_FRC_FLICK_CTRL_01_T                    shp_frc_flick_ctrl_01;	//0x0564
	PE_O22_SHP_FRC_FLICK_CTRL_02_T                    shp_frc_flick_ctrl_02;	//0x0568
	PE_O22_SHP_FRC_FLICK_CTRL_03_T                    shp_frc_flick_ctrl_03;	//0x056C
	PE_O22_SHP_FRC_BLUR_CTRL_00_T                     shp_frc_blur_ctrl_00;	//0xCC462570
	PE_O22_SHP_FRC_BLUR_CTRL_01_T                     shp_frc_blur_ctrl_01;	//0xCC462574
	PE_O22_SHP_FRC_BLUR_CTRL_02_T                     shp_frc_blur_ctrl_02;	//0xCC462578
	PE_O22_SHP_FRC_BLUR_CTRL_03_T                     shp_frc_blur_ctrl_03;	//0xCC46257C
	PE_O22_SHP_FRC_BLUR_CTRL_04_T                     shp_frc_blur_ctrl_04;	//0xCC462580
	PE_O22_SHP_FRC_BLUR_CTRL_05_T                     shp_frc_blur_ctrl_05;	//0xCC462584
	PE_O22_SHP_FRC_BLUR_CTRL_06_T                     shp_frc_blur_ctrl_06;	//0xCC462588
	PE_O22_SHP_FRC_HALO_CTRL_00_T                     shp_frc_halo_ctrl_00;	//0xCC462590
	PE_O22_SHP_FRC_HALO_CTRL_01_T                     shp_frc_halo_ctrl_01;	//0xCC462594
	PE_O22_SHP_FRC_HALO_CTRL_02_T                     shp_frc_halo_ctrl_02;	//0xCC462598
	PE_O22_SHP_FRC_HALO_CTRL_03_T                     shp_frc_halo_ctrl_03;	//0xCC46259C
	PE_O22_SHP_MOTION_GAIN_CTRL_00_T                  shp_motion_gain_ctrl_00;	//0x0600
	PE_O22_SHP_MOTION_GAIN_CTRL_01_T                  shp_motion_gain_ctrl_01;	//0x0604
	PE_O22_SHP_MOTION_GAIN_CTRL_02_T                  shp_motion_gain_ctrl_02;	//0x0608
	PE_O22_SHP_MOTION_GAIN_CTRL_03_T                  shp_motion_gain_ctrl_03;	//0x060C
	PE_O22_SHP_MOTION_GAIN_CTRL_04_T                  shp_motion_gain_ctrl_04;	//0x0610
	PE_O22_SHP_MOTION_GAIN_CTRL_05_T                  shp_motion_gain_ctrl_05;	//0x0614
	PE_O22_SHP_MOTION_GAIN_CTRL_06_T                  shp_motion_gain_ctrl_06;	//0x0618
	PE_O22_SHP_MOTION_GAIN_CTRL_07_T                  shp_motion_gain_ctrl_07;	//0x061C
	PE_O22_SHP_MOTION_GAIN_CTRL_08_T                  shp_motion_gain_ctrl_08;	//0x0620
	PE_O22_SHP_MOTION_GAIN_CTRL_09_T                  shp_motion_gain_ctrl_09;	//0x0624
	PE_O22_SHP_MOTION_GAIN_CTRL_0A_T                  shp_motion_gain_ctrl_0a;	//0x0628
	PE_O22_SHP_MOTION_GAIN_CTRL_0B_T                  shp_motion_gain_ctrl_0b;	//0x062C
	PE_O22_SHP_MOTION_GAIN_CTRL_0C_T                  shp_motion_gain_ctrl_0c;	//0x0630
	PE_O22_SHP_MOTION_PROT_CTRL_00_T                  shp_motion_prot_ctrl_00;	//0x0640
	PE_O22_SHP_MOTION_PROT_CTRL_01_T                  shp_motion_prot_ctrl_01;	//0x0644
	PE_O22_SHP_MOTION_PROT_CTRL_02_T                  shp_motion_prot_ctrl_02;	//0x0648
	PE_O22_SHP_MOTION_PROT_CTRL_03_T                  shp_motion_prot_ctrl_03;	//0x064C
	PE_O22_SHP_MOTION_PROT_CTRL_04_T                  shp_motion_prot_ctrl_04;	//0x0650
	PE_O22_SHP_OBJ_CTRL_00_T                          shp_obj_ctrl_00;	//0x0690
	PE_O22_SHP_OBJ_CTRL_01_T                          shp_obj_ctrl_01;	//0x0694
	PE_O22_SHP_OBJ_CTRL_02_T                          shp_obj_ctrl_02;	//0x0698
	PE_O22_SHP_OBJ_CTRL_03_T                          shp_obj_ctrl_03;	//0x069C
	PE_O22_SHP_OBJ_CTRL_04_T                          shp_obj_ctrl_04;	//0x06A0
	PE_O22_SHP_OBJ_CTRL_05_T                          shp_obj_ctrl_05;	//0x06A4
	PE_O22_SHP_OBJ_CTRL_06_T                          shp_obj_ctrl_06;	//0x06A8
	PE_O22_SHP_OBJ_CTRL_07_T                          shp_obj_ctrl_07;	//0x06AC
	PE_O22_SHP_OBJ_CTRL_08_T                          shp_obj_ctrl_08;	//0x06B0
	PE_O22_SHP_OBJ_CTRL_09_T                          shp_obj_ctrl_09;	//0x06B4
	PE_O22_SHP_OBJ_CTRL_0A_T                          shp_obj_ctrl_0a;	//0x06B8
	PE_O22_SHP_OBJ_CTRL_0B_T                          shp_obj_ctrl_0b;	//0xCC4626BC
	PE_O22_SHP_OBJ_CTRL_0C_T                          shp_obj_ctrl_0c;	//0xCC4626C0
	#endif
}PE_RES_HW_PARAM_REG_O22_T;

/**
 *	sre 2k shp(srs) hw param reg type
 */
typedef struct {
	PE_O22_2K_SHP_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	PE_O22_2K_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O22_2K_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O22_2K_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O22_2K_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O22_2K_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O22_2K_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O22_2K_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O22_2K_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O22_2K_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O22_2K_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O22_2K_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O22_2K_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O22_2K_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O22_2K_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O22_2K_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O22_2K_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O22_2K_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O22_2K_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O22_2K_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	PE_O22_2K_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O22_2K_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O22_2K_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O22_2K_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	PE_O22_2K_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O22_2K_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O22_2K_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O22_2K_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O22_2K_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O22_2K_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O22_2K_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O22_2K_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O22_2K_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O22_2K_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O22_2K_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O22_2K_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O22_2K_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O22_2K_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	PE_O22_2K_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O22_2K_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O22_2K_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O22_2K_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O22_2K_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	PE_O22_2K_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O22_2K_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O22_2K_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O22_2K_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O22_2K_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O22_2K_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O22_2K_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O22_2K_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O22_2K_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O22_2K_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O22_2K_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O22_2K_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O22_2K_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O22_2K_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O22_2K_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O22_2K_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O22_2K_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O22_2K_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O22_2K_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O22_2K_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O22_2K_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	PE_O22_2K_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O22_2K_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O22_2K_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O22_2K_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O22_2K_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	PE_O22_2K_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O22_2K_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O22_2K_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O22_2K_SHP_TGEN_CTRL_03_T                         shp_tgen_ctrl_03;	//0x024C
	PE_O22_2K_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O22_2K_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O22_2K_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O22_2K_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O22_2K_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O22_2K_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O22_2K_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O22_2K_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O22_2K_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	PE_O22_2K_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O22_2K_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O22_2K_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O22_2K_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O22_2K_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O22_2K_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O22_2K_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O22_2K_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O22_2K_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O22_2K_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O22_2K_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O22_2K_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O22_2K_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O22_2K_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O22_2K_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O22_2K_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O22_2K_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O22_2K_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O22_2K_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O22_2K_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O22_2K_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O22_2K_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O22_2K_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O22_2K_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O22_2K_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O22_2K_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O22_2K_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O22_2K_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O22_2K_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O22_2K_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O22_2K_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O22_2K_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O22_2K_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O22_2K_SHP_NNTG_CTRL_01_T                         shp_nntg_ctrl_01;	//0x0304
	PE_O22_2K_SHP_NNTG_CTRL_02_T                         shp_nntg_ctrl_02;	//0x0308
	PE_O22_2K_SHP_NNTG_CTRL_03_T                         shp_nntg_ctrl_03;	//0x030C
	PE_O22_2K_SHP_NNTG_CTRL_04_T                         shp_nntg_ctrl_04;	//0x0310
	PE_O22_2K_SHP_NNTG_CTRL_05_T                         shp_nntg_ctrl_05;	//0x0314
	PE_O22_2K_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O22_2K_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O22_2K_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O22_2K_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O22_2K_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O22_2K_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O22_2K_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O22_2K_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O22_2K_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O22_2K_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O22_2K_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	PE_O22_2K_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O22_2K_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O22_2K_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_O22_2K_SHP_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O22_2K_SHP_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x3C4
	PE_O22_2K_SHP_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x3C8
	PE_O22_2K_SHP_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O22_2K_SHP_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x3D0
	PE_O22_2K_SHP_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x3D4
	PE_O22_2K_SHP_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x3D8
	PE_O22_2K_SHP_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x3DC
	PE_O22_2K_SHP_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x3E0
	PE_O22_2K_SHP_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x3E4
	PE_O22_2K_SHP_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x3E8
	PE_O22_2K_SHP_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x3EC
	PE_O22_2K_SHP_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O22_2K_SHP_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O22_2K_SHP_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O22_2K_SHP_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O22_2K_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O22_2K_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O22_2K_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O22_2K_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O22_2K_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O22_2K_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O22_2K_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O22_2K_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O22_2K_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O22_2K_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O22_2K_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O22_2K_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O22_2K_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O22_2K_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O22_2K_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O22_2K_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O22_2K_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O22_2K_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O22_2K_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O22_2K_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O22_2K_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O22_2K_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O22_2K_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O22_2K_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O22_2K_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O22_2K_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O22_2K_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O22_2K_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O22_2K_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O22_2K_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O22_2K_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O22_2K_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O22_2K_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T                 shp_dj_text_gain_ctrl_00;	//0xCCC410C0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T                 shp_dj_text_gain_ctrl_01;	//0xCCC410C4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T                 shp_dj_text_gain_ctrl_02;	//0xCCC410C8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T                 shp_dj_text_gain_ctrl_03;	//0xCCC410CC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T                 shp_dj_text_gain_ctrl_04;	//0xCCC410D0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T                 shp_dj_text_gain_ctrl_05;	//0xCCC410D4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T                 shp_dj_text_gain_ctrl_06;	//0xCCC410D8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T                 shp_dj_text_gain_ctrl_07;	//0xCCC410DC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T                 shp_dj_text_gain_ctrl_08;	//0xCCC410E0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T                 shp_dj_text_gain_ctrl_09;	//0xCCC410E4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T                 shp_dj_text_gain_ctrl_10;	//0xCCC410E8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T                 shp_dj_text_gain_ctrl_11;	//0xCCC410EC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T                 shp_dj_text_gain_ctrl_12;	//0xCCC410F0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T                 shp_dj_text_gain_ctrl_13;	//0xCCC410F4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T                 shp_dj_text_gain_ctrl_14;	//0xCCC410F8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T                 shp_dj_text_gain_ctrl_15;	//0xCCC410FC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T                 shp_dj_text_gain_ctrl_16;	//0xCCC41100
	PE_O22_SR_MERGE_MMD_05_T                             sr_merge_mmd_05;	//0x0034
	PE_O22_SR_MERGE_MMD_06_T                             sr_merge_mmd_06;	//0x0038
	PE_O22_SR_MERGE_BLEND_00_T                           sr_merge_blend_00;	//0x0090
}PE_SRS_2K_HW_PARAM_REG_O22_T;

/**
 *	obe hw param reg type
 */
typedef struct {
#ifdef PE_HW_O22_BRINGUP
	PE_O22_VSD_OBE_CTRL_001_T                         reg_obe_ctrl_001;	//0xCC460204
	PE_O22_VSD_OBE_CTRL_002_T                         reg_obe_ctrl_002;	//0xCC460208
	PE_O22_VSD_OBE_CTRL_003_T                         reg_obe_ctrl_003;	//0xCC46020C
	PE_O22_VSD_OBE_CTRL_004_T                         reg_obe_ctrl_004;	//0xCC460210
	PE_O22_VSD_OBE_CTRL_005_T                         reg_obe_ctrl_005;	//0xCC460214
	PE_O22_VSD_OBE_CTRL_025_T                         reg_obe_ctrl_025;	//0xCC460264
	PE_O22_VSD_OBE_CTRL_026_T                         reg_obe_ctrl_026;	//0xCC460268
	PE_O22_VSD_OBE_CTRL_027_T                         reg_obe_ctrl_027;	//0xCC46026C
	PE_O22_VSD_OBE_CTRL_028_T                         reg_obe_ctrl_028;	//0xCC460270
	PE_O22_VSD_OBE_CTRL_029_T                         reg_obe_ctrl_029;	//0xCC460274
	PE_O22_VSD_OBE_CTRL_030_T                         reg_obe_ctrl_030;	//0xCC460278
	PE_O22_VSD_OBE_CTRL_031_T                         reg_obe_ctrl_031;	//0xCC46027C
	PE_O22_VSD_OBE_CTRL_032_T                         reg_obe_ctrl_032;	//0xCC460280
	PE_O22_VSD_OBE_CTRL_033_T                         reg_obe_ctrl_033;	//0xCC460284
	PE_O22_VSD_OBE_CTRL_034_T                         reg_obe_ctrl_034;	//0xCC460288
	PE_O22_VSD_OBE_CTRL_035_T                         reg_obe_ctrl_035;	//0xCC46028C
	PE_O22_VSD_OBE_CTRL_036_T                         reg_obe_ctrl_036;	//0xCC460290
	PE_O22_VSD_OBE_CTRL_037_T                         reg_obe_ctrl_037;	//0xCC460294
	PE_O22_VSD_OBE_CTRL_038_T                         reg_obe_ctrl_038;	//0xCC460298
	PE_O22_VSD_OBE_CTRL_039_T                         reg_obe_ctrl_039;	//0xCC46029C
	PE_O22_VSD_OBE_CTRL_040_T                         reg_obe_ctrl_040;	//0xCC4602A0
	PE_O22_VSD_OBE_CTRL_041_T                         reg_obe_ctrl_041;	//0xCC4602A4
	PE_O22_VSD_OBE_CTRL_042_T                         reg_obe_ctrl_042;	//0xCC4602A8
	PE_O22_VSD_OBE_CTRL_043_T                         reg_obe_ctrl_043;	//0xCC4602AC
	PE_O22_VSD_OBE_CTRL_044_T                         reg_obe_ctrl_044;	//0xCC4602B0
	PE_O22_VSD_OBE_CTRL_045_T                         reg_obe_ctrl_045;	//0xCC4602B4
	PE_O22_VSD_OBE_CTRL_046_T                         reg_obe_ctrl_046;	//0xCC4602B8
	PE_O22_VSD_OBE_CTRL_047_T                         reg_obe_ctrl_047;	//0xCC4602BC
	PE_O22_VSD_OBE_CTRL_048_T                         reg_obe_ctrl_048;	//0xCC4602C0
	PE_O22_VSD_OBE_CTRL_049_T                         reg_obe_ctrl_049;	//0xCC4602C4
	PE_O22_VSD_OBE_CTRL_050_T                         reg_obe_ctrl_050;	//0xCC4602C8
	PE_O22_VSD_OBE_CTRL_051_T                         reg_obe_ctrl_051;	//0xCC4602CC
	PE_O22_VSD_OBE_CTRL_052_T                         reg_obe_ctrl_052;	//0xCC4602D0
	PE_O22_VSD_OBE_CTRL_053_T                         reg_obe_ctrl_053;	//0xCC4602D4
	PE_O22_VSD_OBE_CTRL_054_T                         reg_obe_ctrl_054;	//0xCC4602D8
	PE_O22_VSD_OBE_CTRL_055_T                         reg_obe_ctrl_055;	//0xCC4602DC
	PE_O22_VSD_OBE_CTRL_056_T                         reg_obe_ctrl_056;	//0xCC4602E0
	PE_O22_VSD_OBE_CTRL_057_T                         reg_obe_ctrl_057;	//0xCC4602E4
	PE_O22_VSD_OBE_CTRL_058_T                         reg_obe_ctrl_058;	//0xCC4602E8
	PE_O22_VSD_OBE_CTRL_059_T                         reg_obe_ctrl_059;	//0xCC4602EC
	PE_O22_VSD_OBE_CTRL_060_T                         reg_obe_ctrl_060;	//0xCC4602F0
	PE_O22_VSD_OBE_CTRL_061_T                         reg_obe_ctrl_061;	//0xCC4602F4
	PE_O22_VSD_OBE_CTRL_062_T                         reg_obe_ctrl_062;	//0xCC4602F8
	PE_O22_VSD_OBE_CTRL_063_T                         reg_obe_ctrl_063;	//0xCC4602FC
	PE_O22_VSD_OBE_CTRL_082_T                         reg_obe_ctrl_082;	//0xCC460348
	PE_O22_VSD_OBE_CTRL_083_T                         reg_obe_ctrl_083;	//0xCC46034C
	PE_O22_VSD_OBE_CTRL_084_T                         reg_obe_ctrl_084;	//0xCC460350
	PE_O22_VSD_OBE_CTRL_085_T                         reg_obe_ctrl_085;	//0xCC460354
	PE_O22_VSD_OBE_CTRL_086_T                         reg_obe_ctrl_086;	//0xCC460358
	PE_O22_VSD_OBE_CTRL_087_T                         reg_obe_ctrl_087;	//0xCC46035C
	PE_O22_VSD_OBE_CTRL_088_T                         reg_obe_ctrl_088;	//0xCC460360
	PE_O22_VSD_OBE_CTRL_089_T                         reg_obe_ctrl_089;	//0xCC460364
	PE_O22_VSD_OBE_CTRL_090_T                         reg_obe_ctrl_090;	//0xCC460368
	PE_O22_VSD_OBE_CTRL_091_T                         reg_obe_ctrl_091;	//0xCC46036C
	PE_O22_VSD_OBE_CTRL_092_T                         reg_obe_ctrl_092;	//0xCC460370
	PE_O22_VSD_OBE_CTRL_093_T                         reg_obe_ctrl_093;	//0xCC460374
	PE_O22_VSD_OBE_CTRL_094_T                         reg_obe_ctrl_094;	//0xCC460378
	PE_O22_VSD_OBE_CTRL_095_T                         reg_obe_ctrl_095;	//0xCC46037C
	PE_O22_VSD_OBE_CTRL_096_T                         reg_obe_ctrl_096;	//0xCC460380
	PE_O22_VSD_OBE_CTRL_097_T                         reg_obe_ctrl_097;	//0xCC460384
	PE_O22_VSD_OBE_CTRL_098_T                         reg_obe_ctrl_098;	//0xCC460388
	PE_O22_VSD_OBE_CTRL_099_T                         reg_obe_ctrl_099;	//0xCC46038C
	PE_O22_VSD_OBE_CTRL_100_T                         reg_obe_ctrl_100;	//0xCC460390
	PE_O22_VSD_OBE_CTRL_101_T                         reg_obe_ctrl_101;	//0xCC460394
	PE_O22_VSD_OBE_CTRL_102_T                         reg_obe_ctrl_102;	//0xCC460398
	PE_O22_VSD_OBE_CTRL_103_T                         reg_obe_ctrl_103;	//0xCC46039C
	PE_O22_VSD_OBE_CTRL_104_T                         reg_obe_ctrl_104;	//0xCC4603A0
	PE_O22_VSD_OBE_CTRL_105_T                         reg_obe_ctrl_105;	//0xCC4603A4
	PE_O22_VSD_OBE_CTRL_106_T                         reg_obe_ctrl_106;	//0xCC4603A8
	PE_O22_VSD_OBE_CTRL_107_T                         reg_obe_ctrl_107;	//0xCC4603AC
	PE_O22_VSD_OBE_CTRL_126_T                         reg_obe_ctrl_126;	//0xCC4603F8
	PE_O22_VSD_OBE_CTRL_127_T                         reg_obe_ctrl_127;	//0xCC4603FC
	PE_O22_VSD_OBE_CTRL_136_T                         reg_obe_ctrl_136;	//0xCC460420
	PE_O22_VSD_OBE_CTRL_137_T                         reg_obe_ctrl_137;	//0xCC460424
#endif
}PE_OBE_HW_PARAM_REG_O22_T;


#if 1
/**********************************************************************************
*************************for O22F22 model******************************************
***********************************************************************************/

/**
 *	obc face hw param reg type
 */
typedef struct {
	PE_O22_VSD_OBC_HEAD_PSP_CTRL00_T                                psp_ctrl00;	//0xF3030800
	PE_O22_VSD_OBC_HEAD_PSP_CTRL01_T                                psp_ctrl01;	//0xF3030804
	PE_O22_VSD_OBC_HEAD_PSP_CTRL02_T                                psp_ctrl02;	//0xF3030808
	PE_O22_VSD_OBC_HEAD_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xF303080C
	PE_O22_VSD_OBC_HEAD_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xF3030810
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL0_T                            refine_ctrl0;	//0xF3030870
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL1_T                            refine_ctrl1;	//0xF3030874
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL2_T                            refine_ctrl2;	//0xF3030878
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL3_T                            refine_ctrl3;	//0xF303087C
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL4_T                            refine_ctrl4;	//0xF3030880
}PE_OBC_HEAD_HW_PARAM_REG_O22F22_T;
/**
 *	obc object hw param reg type
 */
typedef struct {

	PE_O22_VSD_OBC_BODY_PSP_CTRL00_T                                psp_ctrl00;	//0xF3030600
	PE_O22_VSD_OBC_BODY_PSP_CTRL01_T                                psp_ctrl01;	//0xF3030604
	PE_O22_VSD_OBC_BODY_PSP_CTRL02_T                                psp_ctrl02;	//0xF3030608
	PE_O22_VSD_OBC_BODY_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xF303060C
	PE_O22_VSD_OBC_BODY_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xF3030610
	PE_O22_VSD_OBC_BODY_REFINE_CTRL0_T                            refine_ctrl0;	//0xF3030670
	PE_O22_VSD_OBC_BODY_REFINE_CTRL1_T                            refine_ctrl1;	//0xF3030674
	PE_O22_VSD_OBC_BODY_REFINE_CTRL2_T                            refine_ctrl2;	//0xF3030678
	PE_O22_VSD_OBC_BODY_REFINE_CTRL3_T                            refine_ctrl3;	//0xF303067C
	PE_O22_VSD_OBC_BODY_REFINE_CTRL4_T                            refine_ctrl4;	//0xF3030680
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T obj_refine_body_gain_ctrl_00;	//0xF3030690
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T obj_refine_body_gain_ctrl_01;	//0xF3030694
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T obj_refine_body_gain_ctrl_02;	//0xF3030698
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T obj_refine_body_gain_ctrl_03;	//0xF303069C
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T obj_refine_body_gain_ctrl_04;	//0xF30306A0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T obj_refine_body_gain_ctrl_05;	//0xF30306A4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T obj_refine_body_gain_ctrl_06;	//0xF30306A8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T obj_refine_body_gain_ctrl_07;	//0xF30306AC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T obj_refine_body_gain_ctrl_08;	//0xF30306B0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T obj_refine_body_gain_ctrl_09;	//0xF30306B4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T obj_refine_body_gain_ctrl_10;	//0xF30306B8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T obj_refine_body_gain_ctrl_11;	//0xF30306BC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T obj_refine_body_gain_ctrl_12;	//0xF30306C0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T obj_refine_body_gain_ctrl_13;	//0xF30306C4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T obj_refine_body_gain_ctrl_14;	//0xF30306C8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T obj_refine_body_gain_ctrl_15;	//0xF30306CC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T obj_refine_body_gain_ctrl_16;	//0xF30306D0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T obj_refine_body_gain_ctrl_17;	//0xF30306D4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T obj_refine_body_gain_ctrl_18;	//0xF30306D8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T obj_refine_body_gain_ctrl_19;	//0xF30306DC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T obj_refine_body_gain_ctrl_20;	//0xF30306E0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T obj_refine_body_gain_ctrl_21;	//0xF30306E4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T obj_refine_body_gain_ctrl_22;	//0xF30306E8 
}PE_OBC_BODY_HW_PARAM_REG_O22F22_T;
/**
 *	obe hw param reg type
 */
typedef struct {
#ifdef PE_HW_O22_BRINGUP
	PE_O22_VSD_OBE_CTRL_001_T                         reg_obe_ctrl_001;	//0xCC460204
	PE_O22_VSD_OBE_CTRL_002_T                         reg_obe_ctrl_002;	//0xCC460208
	PE_O22_VSD_OBE_CTRL_003_T                         reg_obe_ctrl_003;	//0xCC46020C
	PE_O22_VSD_OBE_CTRL_004_T                         reg_obe_ctrl_004;	//0xCC460210
	PE_O22_VSD_OBE_CTRL_005_T                         reg_obe_ctrl_005;	//0xCC460214
	PE_O22_VSD_OBE_CTRL_025_T                         reg_obe_ctrl_025;	//0xCC460264
	PE_O22_VSD_OBE_CTRL_026_T                         reg_obe_ctrl_026;	//0xCC460268
	PE_O22_VSD_OBE_CTRL_027_T                         reg_obe_ctrl_027;	//0xCC46026C
	PE_O22_VSD_OBE_CTRL_086_T                         reg_obe_ctrl_086;	//0xCC460358
	PE_O22_VSD_OBE_CTRL_087_T                         reg_obe_ctrl_087;	//0xCC46035C
	PE_O22_VSD_OBE_CTRL_088_T                         reg_obe_ctrl_088;	//0xCC460360
	PE_O22_VSD_OBE_CTRL_089_T                         reg_obe_ctrl_089;	//0xCC460364
	PE_O22_VSD_OBE_CTRL_090_T                         reg_obe_ctrl_090;	//0xCC460368
	PE_O22_VSD_OBE_CTRL_091_T                         reg_obe_ctrl_091;	//0xCC46036C
	PE_O22_VSD_OBE_CTRL_092_T                         reg_obe_ctrl_092;	//0xCC460370
	PE_O22_VSD_OBE_CTRL_093_T                         reg_obe_ctrl_093;	//0xCC460374
	PE_O22_VSD_OBE_CTRL_094_T                         reg_obe_ctrl_094;	//0xCC460378
	PE_O22_VSD_OBE_CTRL_095_T                         reg_obe_ctrl_095;	//0xCC46037C
	PE_O22_VSD_OBE_CTRL_096_T                         reg_obe_ctrl_096;	//0xCC460380
	PE_O22_VSD_OBE_CTRL_097_T                         reg_obe_ctrl_097;	//0xCC460384
	PE_O22_VSD_OBE_CTRL_098_T                         reg_obe_ctrl_098;	//0xCC460388
	PE_O22_VSD_OBE_CTRL_099_T                         reg_obe_ctrl_099;	//0xCC46038C
	PE_O22_VSD_OBE_CTRL_100_T                         reg_obe_ctrl_100;	//0xCC460390
	PE_O22_VSD_OBE_CTRL_101_T                         reg_obe_ctrl_101;	//0xCC460394
	PE_O22_VSD_OBE_CTRL_102_T                         reg_obe_ctrl_102;	//0xCC460398
	PE_O22_VSD_OBE_CTRL_103_T                         reg_obe_ctrl_103;	//0xCC46039C
	PE_O22_VSD_OBE_CTRL_104_T                         reg_obe_ctrl_104;	//0xCC4603A0
	PE_O22_VSD_OBE_CTRL_105_T                         reg_obe_ctrl_105;	//0xCC4603A4
	PE_O22_VSD_OBE_CTRL_106_T                         reg_obe_ctrl_106;	//0xCC4603A8
	PE_O22_VSD_OBE_CTRL_107_T                         reg_obe_ctrl_107;	//0xCC4603AC
	PE_O22_VSD_OBE_CTRL_126_T                         reg_obe_ctrl_126;	//0xCC4603F8
	PE_O22_VSD_OBE_CTRL_127_T                         reg_obe_ctrl_127;	//0xCC4603FC
	PE_O22_VSD_OBE_CTRL_136_T                         reg_obe_ctrl_136;	//0xCC460420
	PE_O22_VSD_OBE_CTRL_137_T                         reg_obe_ctrl_137;	//0xCC460424
#endif
}PE_OBE_HW_PARAM_REG_O22F22_T;

#endif
/**
 *	shp hw param reg type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_O22_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_O22_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_O22_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_O22_T *data;
	} reg_data;
} PE_RES_HW_PARAM_DATA_O22_T;

/**
 *	sre 2k shp(srs) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_SRS_2K_HW_PARAM_REG_O22_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_SRS_2K_HW_PARAM_REG_O22_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_SRS_2K_HW_PARAM_REG_O22_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_SRS_2K_HW_PARAM_REG_O22_T *data;
	} reg_data;
} PE_SRS_2K_HW_PARAM_DATA_O22_T;


/**
 *	obe hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_OBE_HW_PARAM_REG_O22_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_OBE_HW_PARAM_REG_O22_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_OBE_HW_PARAM_REG_O22_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_OBE_HW_PARAM_REG_O22_T *data;
	} reg_data;
} PE_OBE_HW_PARAM_DATA_O22_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_RES_HW_PARAM_O22_H_ */

