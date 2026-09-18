#ifndef _PE_CHPI_DNR_TBL_F20A0_H_
#define _PE_CHPI_DNR_TBL_F20A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221594 RW
	UINT32 reg_dnr_max_enable               :1;	//0 //0 : bypass(or ifc result), 1 : dnr_mux
	UINT32 reg_ifc_max_enable               :1;	//1 //0 : dnr result, 1 : ifc_mux
	UINT32 reg_dnr_ifc_sel                  :1;	//2 //0 : dnr result, 1 : ifc result
	UINT32 reg_decon_max_sum_sel            :1;	//3 //0 : sum, 1 : max
	UINT32 reg_decon_ori_sel                :1;	//4 //0: original, 1: v_filter
	UINT32 reg_decon_max_enable             :1;	//5 //0: dnr only, 1: dnr+decon
	UINT32 reg_max_decon_dbg_en             :1;	//6 //
	UINT32 reg_half_rate_cg_n               :1;	//7 //0: cg_on, 1: cg_off
	UINT32 reg_max_dbg_en                   :1;	//8 //ac : black, dc : white, mnr : green
	UINT32 reg_dnr_motion_sel               :1;	//9 //0: 1:2:1 blurred motion 1: 5x5 blurred motion
	UINT32 reg_tnr_decon_en                 :1;	//10 //1: tnr_decon, 0: dnr_decon
	UINT32 resvd0                           :5;
	UINT32 reg_win_en                       :1;	//16 //win control enable	   debug_enable should be '0'
	UINT32 reg_bdr_en                       :1;	//17 //border enable
	UINT32 reg_win_inout                    :1;	//18 //
	UINT32 resvd1                           :2;
	UINT32 reg_ipc_motion_en                :1;	//21 //hmc_flag 대응 => 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl              :3;	//24:22	//0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th                 :7;	//31:25	//applied ifc when delta is greater than th
	};
	};
}PE_F20_DNR0_DNR_MAX_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215A0 RW
	UINT32 reg_mnr_enable                   :1;	//0 //
	UINT32 reg_mnr_blur_debug               :1;	//1 //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//2 //
	UINT32 reg_mnr_chroma_en                :1;	//3 //
	UINT32 reg_h_expand                     :2;	//5:4	//0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//7:6	//0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//15:8	//
	UINT32 reg_snr_th                       :8;	//23:16	//
	UINT32 reg_th_max                       :8;	//31:24	//
	};
	};
}PE_F20_DNR0_MNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215A4 RW
	UINT32 reg_mmd_y_max                    :8;	//7:0	//edge th, if(mmd > th) edge
	UINT32 reg_mmd_y_min                    :8;	//15:8	//reg_mnr_s2_ratio_min
	UINT32 reg_mmd_x_max                    :8;	//23:16	//reg_mnr_s2_ratio_max
	UINT32 reg_mmd_x_min                    :8;	//31:24	//reg_mnr_s2_mmd_min
	};
	};
}PE_F20_DNR0_MNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215A8 RW
	UINT32 reg_mnr_debug_mode               :4;	//3:0	//0: sel_mmd	1: final_sel_mmd	2: fil_diff_th_map	3: snr_rgn_flag	4: sel_mmd_gain	5: final_gain	6: pattern_flag	7: chroma_gain	8: dist_gain
	UINT32 reg_mnr_debug_en                 :1;	//4 //
	UINT32 resvd                            :19;
	UINT32 reg_equal_snr_th                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_MNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215AC RW
	UINT32 reg_blur_sel                     :1;	//0 //
	UINT32 reg_pattern_en                   :1;	//1 //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//15:8	//
	UINT32 reg_equal_th                     :8;	//23:16	//
	UINT32 reg_mmd_scale                    :8;	//31:24	//
	};
	};
}PE_F20_DNR0_MNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215B0 RW
	UINT32 reg_mmd_fil_x_3                  :8;	//7:0	//
	UINT32 reg_mmd_fil_x_2                  :8;	//15:8	//
	UINT32 reg_mmd_fil_x_1                  :8;	//23:16	//
	UINT32 reg_mmd_fil_x_0                  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_MNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215B4 RW
	UINT32 reg_mmd_fil_y_3                  :8;	//7:0	//
	UINT32 reg_mmd_fil_y_2                  :8;	//15:8	//
	UINT32 reg_mmd_fil_y_1                  :8;	//23:16	//
	UINT32 reg_mmd_fil_y_0                  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_MNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215B8 RW
	UINT32 reg_bnr_ac_detail_max            :8;	//7:0	//detail gain th
	UINT32 reg_bnr_ac_detail_min            :8;	//15:8	//detail gain th
	UINT32 reg_bnr_diff_l                   :8;	//23:16	//th used to find big diff point
	UINT32 reg_bnr_diff_p                   :8;	//31:24	//th used to find point of inflection
	};
	};
}PE_F20_DNR0_DETAIL_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215BC RW
	UINT32 reg_dc_bnr_enable                :1;	//0 //DC BNR enable	0 := off ( output debug mode )	1  = on
	UINT32 reg_dc_blur_debug_mode           :1;	//1 //0: blur, 1: white
	UINT32 reg_dc_blur_sel                  :2;	//3:2	//DC blur sel => 0 : 3x3, 1 : 5x5, 2 : 9x5
	UINT32 reg_dc_output_debug_mode         :4;	//7:4	//0: bypass	1: motion	2: motion gain	3: sum of variance	4: variance gain	5: edge protection map	6: DC gain without edge protection	7: DC gain with edge protection	8: chroma gain without edge protection	9: chroma gain with edge protection	10: fil_diff_th
	UINT32 reg_en_obj_amf_ctrl              :1;	//8 //
	UINT32 resvd                            :4;
	UINT32 reg_obj_gain_mul                 :2;	//14:13	//
	UINT32 reg_obj_gain_en                  :1;	//15 //
	UINT32 reg_dc_motion_max                :8;	//23:16	//dc motion gain th
	UINT32 reg_dc_motion_min                :8;	//31:24	//dc motion gain th, if(reg_dc_motion_en == 0) reg_dc_motion_y_max = manual motion gain value
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215C0 RW
	UINT32 resvd                            :8;
	UINT32 reg_manual_fil_motion_gain       :8;	//15:8	//
	UINT32 reg_var_chroma_en                :1;	//16 //
	UINT32 reg_fil_manual_en                :1;	//17 //
	UINT32 reg_dc_pattern_en                :1;	//18 //
	UINT32 reg_luma_gain_en                 :1;	//19 //
	UINT32 reg_var_v_gain                   :4;	//23:20	//0x5
	UINT32 reg_var_h_gain                   :4;	//27:24	//0x2
	UINT32 reg_var_cut_resolution           :4;	//31:28	//0x5
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215C4 RW
	UINT32 reg_dc_var_en                    :1;	//0 //0x1
	UINT32 reg_dc_motion_en                 :1;	//1 //0x0
	UINT32 reg_dc_protection_en             :1;	//2 //0x1
	UINT32 resvd                            :7;
	UINT32 reg_dc_bnr_mastergain            :6;	//15:10	//0x20 is max.
	UINT32 reg_dc_bnr_chromagain            :8;	//23:16	//max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_dc_protection_th             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215C8 RW
	UINT32 reg_dc_bnr_var_th3               :8;	//7:0	//dc variance gain th
	UINT32 reg_dc_bnr_var_th2               :8;	//15:8	//dc variance gain th
	UINT32 reg_dc_bnr_var_th1               :8;	//23:16	//dc variance gain th
	UINT32 reg_dc_bnr_var_th0               :8;	//31:24	//dc variance gain th, if(reg_dc_var_en == 0) reg_dc_var_y_th0 = manual variance gain value
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215CC RW
	UINT32 reg_dc_motion_y_min              :8;	//7:0	//motion gain y축
	UINT32 reg_dc_motion_y_max              :8;	//15:8	//motion gain y축
	UINT32 resvd                            :16;
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215D0 RW
	UINT32 reg_dc_var_y_th0                 :8;	//7:0	//variance gain y축
	UINT32 reg_dc_var_y_th1                 :8;	//15:8	//variance gain y축
	UINT32 reg_dc_var_y_th2                 :8;	//23:16	//variance gain y축
	UINT32 reg_dc_var_y_th3                 :8;	//31:24	//variance gain y축
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215D4 RW
	UINT32 reg_bnr_ac_h_en                  :1;	//0 //
	UINT32 reg_bnr_ac_v_en                  :1;	//1 //
	UINT32 reg_bnr_ac_h_chroma_en           :1;	//2 //
	UINT32 reg_bnr_ac_v_chroma_en           :1;	//3 //
	UINT32 reg_bnr_ac_acness_resol_h        :2;	//5:4	//1: /2, 2: /4, 3:/ 8
	UINT32 reg_multi_run_mode               :1;	//6 //
	UINT32 reg_ac_bnr_gain_yc_sel           :1;	//7 //
	UINT32 reg_bnr_ac_diff_min_v_th         :8;	//15:8	//minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_diff_min_h_th         :8;	//23:16	//minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_iir_gain              :8;	//31:24	//alpha value used in IIR
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215D8 RW
	UINT32 reg_bnr_ac_global_motion_th      :8;	//7:0	//0x0B
	UINT32 reg_bnr_ac_h_acness_max          :8;	//15:8	//th for acness gain
	UINT32 reg_bnr_ac_h_acness_min          :8;	//23:16	//th for acness gain
	UINT32 reg_bnr_ac_bin_th                :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215DC RW
	UINT32 reg_bnr_ac_motion_3              :8;	//7:0	//motion gain x축
	UINT32 reg_bnr_ac_motion_2              :8;	//15:8	//motion gain x축
	UINT32 reg_bnr_ac_motion_1              :8;	//23:16	//motion gain x축
	UINT32 reg_bnr_ac_motion_0              :8;	//31:24	//motion gain x축
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215E4 RW
	UINT32 reg_bnr_ac_motion_y_3            :8;	//7:0	//motion gain y축
	UINT32 reg_bnr_ac_motion_y_2            :8;	//15:8	//motion gain y축
	UINT32 reg_bnr_ac_motion_y_1            :8;	//23:16	//motion gain y축
	UINT32 reg_bnr_ac_motion_y_0            :8;	//31:24	//motion gain y축
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215E8 RW
	UINT32 reg_bnr_ac_v_init_offset         :3;	//2:0	//offset for init position
	UINT32 reg_bnr_ac_h_init_offset         :3;	//5:3	//offset for init position
	UINT32 reg_bnr_ac_acness_resol_v        :2;	//7:6	//0x0 is original, 0x3 : /8
	UINT32 reg_bnr_ac_debug_mode            :4;	//11:8	//debug mode 	0 : bypass	1 : block line map	2 : motion	3 : motion gain	4 : pos_gain_H	5 : pos_gain_V	6 : AC BNR gain_H	7 : AC BNR gain_V	8 : Binary map	9 : detail map	10: detail gain	11: fil_motion_th	12: filter level map	13: AC final gain_H	14: AC final gain_V
	UINT32 reg_bnr_ac_hsy_mode              :4;	//15:12	//stable init position mode
	UINT32 reg_bnr_ac_v_acness_max          :8;	//23:16	//
	UINT32 reg_bnr_ac_v_acness_min          :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215F0 RW
	UINT32 reg_bnr_ac_detail_th4            :8;	//7:0	//detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th3            :8;	//15:8	//detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th2            :8;	//23:16	//detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th1            :8;	//31:24	//detail th used in AC-BNR final mux
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215F4 RW
	UINT32 reg_bnr_ac_pos_gain_h2           :8;	//7:0	//SD : 0x40, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h1           :8;	//15:8	//SD : 0x80, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h0           :8;	//23:16	//SD : 0xFF, HD : 0xFF
	UINT32 reg_bnr_ac_detail_gain_th        :8;	//31:24	//0x00
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02215F8 RW
	UINT32 reg_bnr_ac_pos_gain_l2           :8;	//7:0	//SD : 0x40, HD : 0x40
	UINT32 reg_bnr_ac_pos_gain_l1           :8;	//15:8	//SD : 0x80, HD : 0x80
	UINT32 reg_bnr_ac_pos_gain_l0           :8;	//23:16	//SD : 0x80, HD : 0xFF
	UINT32 reg_bnr_ac_pos_gain_h3           :8;	//31:24	//SD : 0x00, HD : 0x80
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221600 RW
	UINT32 reg_ac_master_c_gain             :8;	//7:0	//max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_ac_bnr_enable                :1;	//8 //0 : debug mode, 1 : ac result
	UINT32 reg_ac_bnr_motion_en             :1;	//9 //1 : motion gain enable	0 : reg_bnr_ac_motion_y_max = manual motion gain value
	UINT32 reg_ac_bnr_acness_en             :1;	//10 //1 : acness gain enable	0 : reg_bnr_ac_acness_y_max = manual acness gain value
	UINT32 reg_ac_bnr_position_en           :1;	//11 //1 : position gain enable	0 : reg_bnr_ac_pos_gain_H0_7 = manual position gain value
	UINT32 reg_detail_sel                   :1;	//12 //0: old, 1: new
	UINT32 resvd                            :3;
	UINT32 reg_bnr_ac_manual_init_v         :3;	//18:16	//force the specific init position for debug
	UINT32 reg_ac_manual_init_en_v          :1;	//19 //0 : off, 1 : on
	UINT32 reg_bnr_ac_manual_init_h         :3;	//22:20	//force the specific init position for debug
	UINT32 reg_ac_manual_init_en_h          :1;	//23 //0 : off, 1 : on
	UINT32 reg_bnr_ac_pos_gain_l3           :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221604 RW
	UINT32 reg_acness_sel                   :1;	//0 //
	UINT32 reg_g_motion_manual_en           :1;	//1 //
	UINT32 resvd0                           :6;
	UINT32 reg_ac_bnr_debug_h_en            :1;	//8 //
	UINT32 reg_ac_bnr_debug_v_en            :1;	//9 //
	UINT32 reg_ac_master_y_gain             :6;	//15:10	//0x20 is max
	UINT32 reg_g_motion_scale               :3;	//18:16	//
	UINT32 reg_g_motion_div                 :2;	//20:19	//
	UINT32 resvd1                           :10;
	UINT32 reg_ac_flt_level_sel             :1;	//31 //0 : weak, 1 : strong
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221608 RW
	UINT32 reg_ac_detail_gain_y_min         :8;	//7:0	//detail gain y축
	UINT32 reg_ac_detail_gain_y_max         :8;	//15:8	//detail gain y축
	UINT32 reg_bnr_ac_acness_y_min          :8;	//23:16	//acness gain y  축
	UINT32 reg_bnr_ac_acness_y_max          :8;	//31:24	//acness gain y  축
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022160C RW
	UINT32 reg_ac_detail_alpha2_y_min       :8;	//7:0	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	UINT32 reg_ac_detail_alpha2_y_max       :8;	//15:8	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	UINT32 reg_ac_detail_alpha4_y_min       :8;	//23:16	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	UINT32 reg_ac_detail_alpha4_y_max       :8;	//31:24	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221610 RW
	UINT32 reg_g_motion_manual              :8;	//7:0	//
	UINT32 reg_acness_scale_mul             :8;	//15:8	//
	UINT32 reg_bnr_ac_detail_max            :8;	//23:16	//
	UINT32 reg_bnr_ac_detail_min            :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022166C RW
	UINT32 reg_sc_bnr_en                    :1;	//0 //
	UINT32 reg_sc_bnr_manual_h_en           :1;	//1 //
	UINT32 reg_scene_ch_flag                :1;	//2 //
	UINT32 reg_iir_en                       :1;	//3 //
	UINT32 reg_scale_mul_h                  :9;	//12:4	//
	UINT32 reg_scale_div_h                  :4;	//16:13	//
	UINT32 reg_sc_bnr_manual_v_en           :1;	//17 //
	UINT32 reg_sc_bnr_en_h                  :1;	//18 //
	UINT32 reg_sc_bnr_en_v                  :1;	//19 //
	UINT32 resvd                            :2;
	UINT32 reg_avg_scale_mul_h              :4;	//25:22	//
	UINT32 reg_avg_scale_div_h              :3;	//28:26	//
	UINT32 reg_max_index_diff_th            :3;	//31:29	//
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221670 RW
	UINT32 reg_post2_iir_gain               :8;	//7:0	//
	UINT32 reg_frm_cnt_th                   :8;	//15:8	//
	UINT32 reg_bin_ratio_th                 :8;	//23:16	//
	UINT32 reg_detect_th                    :8;	//31:24	//
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221674 RW
	UINT32 reg_bin_ratio_div                :8;	//7:0	//
	UINT32 reg_bin_ratio_mul                :8;	//15:8	//
	UINT32 reg_min_bin_th                   :8;	//23:16	//
	UINT32 reg_detector_iir_gain            :8;	//31:24	//
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221678 RW
	UINT32 reg_grid_th1                     :8;	//7:0	//
	UINT32 reg_grid_th2                     :8;	//15:8	//
	UINT32 reg_grid_th3                     :8;	//23:16	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022167C RW
	UINT32 reg_pos_gain_th                  :8;	//7:0	//
	UINT32 resvd                            :11;
	UINT32 reg_scale_div_v                  :4;	//22:19	//
	UINT32 reg_scale_mul_v                  :9;	//31:23	//
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221680 RW
	UINT32 reg_pos_gain_3                   :8;	//7:0	//block line 에서 +3 떨어진 지점의 gain
	UINT32 reg_pos_gain_2                   :8;	//15:8	//누적 diff_sum에 대한 scaling 값_분자
	UINT32 reg_pos_gain_1                   :8;	//23:16	//block line 에서 +1 떨어진 지점의 gain
	UINT32 reg_pos_gain_0                   :8;	//31:24	//block line 에서 +2 떨어진 지점의 gain
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221684 RW
	UINT32 reg_sc_bnr_debug_en              :1;	//0 //
	UINT32 reg_sc_bnr_debug_mode            :3;	//3:1	//
	UINT32 reg_avg_scale_div_v              :3;	//6:4	//
	UINT32 reg_avg_scale_mul_v              :4;	//10:7	//
	UINT32 resvd                            :13;
	UINT32 reg_acness_th                    :8;	//31:24	//
	};
	};
}PE_F20_DNR0_SC_BNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022169C RW
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_h_l              :8;	//15:8	//
	UINT32 reg_acness_gain_h_g              :8;	//23:16	//
	UINT32 reg_acness_gain_h                :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216A0 RW
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_v_l              :8;	//15:8	//
	UINT32 reg_acness_gain_v_g              :8;	//23:16	//
	UINT32 reg_acness_gain_v                :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216A4 RW
	UINT32 reg_fil_motion_x_th0             :8;	//7:0	//
	UINT32 reg_fil_motion_x_th1             :8;	//15:8	//
	UINT32 reg_fil_motion_x_th2             :8;	//23:16	//
	UINT32 reg_fil_motion_x_th3             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216A8 RW
	UINT32 reg_fil_motion_y_th0             :8;	//7:0	//
	UINT32 reg_fil_motion_y_th1             :8;	//15:8	//
	UINT32 reg_fil_motion_y_th2             :8;	//23:16	//
	UINT32 reg_fil_motion_y_th3             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_DC_BNR_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216AC RW
	UINT32 reg_mmd_sel                      :2;	//1:0	//0: mmd_tnr, 1: mmd_mnr, 2: texture, 3: detail
	UINT32 resvd                            :6;
	UINT32 reg_hist_bin_th0                 :8;	//15:8	//
	UINT32 reg_hist_bin_th1                 :8;	//23:16	//
	UINT32 reg_hist_bin_th2                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_SQM_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216B0 RW
	UINT32 reg_hist_bin_th3                 :8;	//7:0	//
	UINT32 reg_hist_bin_th4                 :8;	//15:8	//
	UINT32 reg_hist_bin_th5                 :8;	//23:16	//
	UINT32 reg_hist_bin_th6                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_SQM_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216B4 RW
	UINT32 reg_trans_mmd_th                 :8;	//7:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_edge_a_th                    :10;	//19:10	//
	UINT32 reg_edf_mmd_th                   :8;	//27:20	//
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_DNR0_SQM_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216B8 RW
	UINT32 reg_sqm_win_mode_x1              :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_x0              :13;	//28:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_sqm_win_mode_mode            :1;	//30 //
	UINT32 reg_sqm_win_mode_en              :1;	//31 //
	};
	};
}PE_F20_DNR0_SQM_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02216BC RW
	UINT32 reg_sqm_win_mode_y1              :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_y0              :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
	};
}PE_F20_DNR0_SQM_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221730 RW
	UINT32 reg_fil_motion_x_th3             :8;	//7:0	//
	UINT32 reg_fil_motion_x_th2             :8;	//15:8	//
	UINT32 reg_fil_motion_x_th1             :8;	//23:16	//
	UINT32 reg_fil_motion_x_th0             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221734 RW
	UINT32 reg_fil_motion_y_th3             :8;	//7:0	//
	UINT32 reg_fil_motion_y_th2             :8;	//15:8	//
	UINT32 reg_fil_motion_y_th1             :8;	//23:16	//
	UINT32 reg_fil_motion_y_th0             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_AC_BNR_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221764 RW
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//0 //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//1 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_1st_out_rd_out_clip          :1;	//2 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//7 //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//8 //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//9 //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//10 //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//11 //0: 12-bit full	1: 1st_out_rd 입력 /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_1st_out_rd_min_alpha         :8;	//27:20	//
	UINT32 reg_1st_out_rd_bit               :3;	//30:28	//
	UINT32 reg_1st_out_rd_on                :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221768 RW
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022176C RW
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221770 RW
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221774 RW
	UINT32 reg_1st_out_rd_init_yy           :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221778 RW
	UINT32 reg_1st_out_rd_init_cb           :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022177C RW
	UINT32 reg_1st_out_rd_init_cr           :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221780 RW
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//7:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//11 //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//27:20	//
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221784 RW
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//29:28	//
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//31:30	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221788 RW
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022178C RW
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221790 RW
	UINT32 reg_gain_x3                      :8;	//7:0	//
	UINT32 reg_gain_x2                      :8;	//15:8	//
	UINT32 reg_gain_x1                      :8;	//23:16	//
	UINT32 reg_gain_x0                      :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221794 RW
	UINT32 reg_gain_x7                      :8;	//7:0	//
	UINT32 reg_gain_x6                      :8;	//15:8	//
	UINT32 reg_gain_x5                      :8;	//23:16	//
	UINT32 reg_gain_x4                      :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221798 RW
	UINT32 reg_gain_y3                      :8;	//7:0	//
	UINT32 reg_gain_y2                      :8;	//15:8	//
	UINT32 reg_gain_y1                      :8;	//23:16	//
	UINT32 reg_gain_y0                      :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022179C RW
	UINT32 reg_gain_y7                      :8;	//7:0	//
	UINT32 reg_gain_y6                      :8;	//15:8	//
	UINT32 reg_gain_y5                      :8;	//23:16	//
	UINT32 reg_gain_y4                      :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217A8 RW
	UINT32 reg_small_mmd_flat_th            :8;	//7:0	//
	UINT32 reg_large_mmd_flat_th            :8;	//15:8	//
	UINT32 resvd                            :12;
	UINT32 reg_mmd_chroma_gain_en           :1;	//28 //
	UINT32 reg_mmd_dist_kernal_width        :2;	//30:29	//
	UINT32 reg_mmd_dist_gain_en             :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217AC RW
	UINT32 reg_dist_gain_x3                 :8;	//7:0	//
	UINT32 reg_dist_gain_x2                 :8;	//15:8	//
	UINT32 reg_dist_gain_x1                 :8;	//23:16	//
	UINT32 reg_dist_gain_x0                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217B0 RW
	UINT32 reg_dist_gain_y3                 :8;	//7:0	//
	UINT32 reg_dist_gain_y2                 :8;	//15:8	//
	UINT32 reg_dist_gain_y1                 :8;	//23:16	//
	UINT32 reg_dist_gain_y0                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217B4 RW
	UINT32 reg_chroma_gain_x3               :8;	//7:0	//
	UINT32 reg_chroma_gain_x2               :8;	//15:8	//
	UINT32 reg_chroma_gain_x1               :8;	//23:16	//
	UINT32 reg_chroma_gain_x0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217B8 RW
	UINT32 reg_chroma_gain_y3               :8;	//7:0	//
	UINT32 reg_chroma_gain_y2               :8;	//15:8	//
	UINT32 reg_chroma_gain_y1               :8;	//23:16	//
	UINT32 reg_chroma_gain_y0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217BC RW
	UINT32 reg_i_sel_mmd_x3                 :8;	//7:0	//
	UINT32 reg_i_sel_mmd_x2                 :8;	//15:8	//
	UINT32 reg_i_sel_mmd_x1                 :8;	//23:16	//
	UINT32 reg_i_sel_mmd_x0                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217C0 RW
	UINT32 reg_i_sel_mmd_y3                 :8;	//7:0	//
	UINT32 reg_i_sel_mmd_y2                 :8;	//15:8	//
	UINT32 reg_i_sel_mmd_y1                 :8;	//23:16	//
	UINT32 reg_i_sel_mmd_y0                 :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_MNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217C4 RW
	UINT32 reg_2nd_out_rd_init_yy           :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217C8 RW
	UINT32 reg_2nd_out_rd_init_cb           :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217CC RW
	UINT32 reg_2nd_out_rd_init_cr           :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217D0 RW
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217D4 RW
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217D8 RW
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217DC RW
	UINT32 reg_blur_lb_var_cut_res          :4;	//3:0	//>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//6 //
	UINT32 reg_l6_var_2x2_bit               :1;	//7 //12b인 L6_var를 10b으로 cut할 때, 1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//13:8	//
	UINT32 reg_1st_debug_en                 :1;	//14 //
	UINT32 reg_l6_var_csc_en                :1;	//15 //ND에선 사용 안 함
	UINT32 reg_force_block_no_h             :6;	//21:16	//
	UINT32 reg_4k_5x3_mode_en               :1;	//22 //0: 5x5(u2, u1, cc, d1, d2) , 1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//23 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_rd_clip                      :1;	//24 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_input_csc_en                 :1;	//25 //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :4;	//29:26	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_2x2_blur	11: skin_gain	12: face_gain	13: face_skin_gain	14: input_blur
	UINT32 reg_force_block_no_en            :1;	//30 //
	UINT32 reg_decon_1st_en                 :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217E0 RW
	UINT32 reg_var_chroma_en                :1;	//0 //
	UINT32 resvd0                           :1;
	UINT32 reg_blur_final_size              :1;	//2 //0: new_2x2, 1: new_3x3
	UINT32 resvd1                           :1;
	UINT32 reg_blur_div_zero                :1;	//4 //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//6:5	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//8:7	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//11:9	//0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//12 //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//13 //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//14 //not used in O20
	UINT32 resvd2                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//16 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//17 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//18 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//19 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//23:20	//
	UINT32 reg_var_h_gain                   :4;	//27:24	//
	UINT32 reg_var_cut_resolution           :4;	//31:28	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217E4 RW
	UINT32 reg_decon_diff_x_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_x_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_x_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_x_th3             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217E8 RW
	UINT32 reg_decon_diff_y_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_y_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_y_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_y_th3             :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217EC RW
	UINT32 reg_decon_var_x_th2              :10;	//9:0	//
	UINT32 reg_decon_var_x_th1              :10;	//19:10	//
	UINT32 reg_decon_var_x_th0              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217F0 RW
	UINT32 reg_decon_var_y_th1              :10;	//9:0	//
	UINT32 reg_decon_var_y_th0              :10;	//19:10	//
	UINT32 reg_decon_var_x_th3              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217F4 RW
	UINT32 reg_decon_luma_x_th0             :10;	//9:0	//
	UINT32 reg_decon_var_y_th3              :10;	//19:10	//
	UINT32 reg_decon_var_y_th2              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217F8 RW
	UINT32 reg_decon_luma_x_th3             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th2             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th1             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217FC RW
	UINT32 reg_decon_luma_x_th6             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th5             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th4             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221800 RW
	UINT32 reg_decon_luma_y_th1             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th0             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th7             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221804 RW
	UINT32 reg_decon_luma_y_th4             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th3             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th2             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221808 RW
	UINT32 reg_decon_luma_y_th7             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th6             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th5             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022180C RW
	UINT32 reg_block_size_v                 :8;	//7:0	//
	UINT32 reg_block_size_h                 :8;	//15:8	//
	UINT32 reg_block_no_v                   :6;	//21:16	//
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//29:24	//
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221810 RW
	UINT32 reg_last_block_size_v            :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//19:16	//
	UINT32 reg_diff_shift                   :3;	//22:20	//
	UINT32 reg_osd_run_mode                 :1;	//23 //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//24 //
	UINT32 reg_alpha_blur_mode              :2;	//26:25	//0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//28:27	//
	UINT32 reg_diff_use_seldiff             :1;	//29 //
	UINT32 reg_diff_calc_mode               :2;	//31:30	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221814 RW
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//9:0	//not used in m16p3
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//19:10	//not used in m16p3
	UINT32 reg_lb_var_cut_res               :4;	//23:20	//cut resolution after (var * LB_var)
	UINT32 reg_master_gain                  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221818 RW
	UINT32 reg_l6_var_x_th2                 :10;	//9:0	//revived in O20
	UINT32 reg_l6_var_x_th1                 :10;	//19:10	//revived in O20
	UINT32 reg_l6_var_x_th0                 :10;	//29:20	//revived in O20
	UINT32 reg_lb_var_opt                   :1;	//30 //0: L6_var, 1: L6_var 2x2smooth
	UINT32 reg_lb_var_en                    :1;	//31 //use L6_var when making var map
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_32_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022181C RW
	UINT32 reg_l6_var_y_th1                 :10;	//9:0	//revived in O20
	UINT32 reg_l6_var_y_th0                 :10;	//19:10	//revived in O20
	UINT32 reg_l6_var_x_th3                 :10;	//29:20	//revived in O20
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_33_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221820 RW
	UINT32 reg_l6_var_y_th3                 :10;	//9:0	//revived in O20
	UINT32 reg_l6_var_y_th2                 :10;	//19:10	//revived in O20
	UINT32 reg_l6_pel_trunc                 :2;	//21:20	//
	UINT32 reg_var_v_cut                    :2;	//23:22	//
	UINT32 reg_var_h_cut                    :2;	//25:24	//
	UINT32 reg_var_t7_offset                :2;	//27:26	//
	UINT32 reg_decon_rd_simple_bit          :3;	//30:28	//
	UINT32 reg_decon_rd_simple_on           :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_34_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221824 RW
	UINT32 reg_decon_rd_simple_init_yy      :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_35_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221828 RW
	UINT32 reg_decon_rd_simple_init_cb      :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_36_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022182C RW
	UINT32 reg_decon_rd_simple_init_cr      :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_37_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221830 RW
	UINT32 reg_rd_min_pel_cb                :12;	//11:0	//
	UINT32 reg_rd_min_pel_yy                :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//30:28	//
	UINT32 reg_decon_rd_on                  :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_38_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221834 RW
	UINT32 reg_rd_max_pel_yy                :12;	//11:0	//
	UINT32 reg_rd_min_pel_cr                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_39_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221838 RW
	UINT32 reg_rd_max_pel_cr                :12;	//11:0	//
	UINT32 reg_rd_max_pel_cb                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_40_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022183C RW
	UINT32 reg_rd_init_yy                   :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_41_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221840 RW
	UINT32 reg_rd_init_cb                   :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_42_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221844 RW
	UINT32 reg_rd_init_cr                   :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_43_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221848 RW
	UINT32 reg_motion_gain_x3               :8;	//7:0	//
	UINT32 reg_motion_gain_x2               :8;	//15:8	//
	UINT32 reg_motion_gain_x1               :8;	//23:16	//
	UINT32 reg_motion_gain_x0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_44_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022184C RW
	UINT32 reg_motion_gain_y3               :8;	//7:0	//
	UINT32 reg_motion_gain_y2               :8;	//15:8	//
	UINT32 reg_motion_gain_y1               :8;	//23:16	//
	UINT32 reg_motion_gain_y0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221850 RW
	UINT32 reg_bbd_y0                       :12;	//11:0	//
	UINT32 reg_bbd_x0                       :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//28 //
	UINT32 reg_blur2_sim_en                 :1;	//29 //
	UINT32 reg_amf_lut_bit                  :1;	//30 //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_46_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221854 RW
	UINT32 reg_bbd_y1                       :12;	//11:0	//
	UINT32 reg_bbd_x1                       :12;	//23:12	//
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//28:26	//
	UINT32 reg_blur2_sim_ratio              :3;	//31:29	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_47_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221858 RW
	UINT32 reg_lut_blur_sim_x3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_x2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_x1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_x0              :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_48_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022185C RW
	UINT32 reg_lut_blur_sim_y3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_y2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_y1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_y0              :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_49_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221860 RW
	UINT32 reg_lut_skin_yy_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_yy_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_yy_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_yy_x0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_50_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221864 RW
	UINT32 reg_lut_skin_cb_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cb_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cb_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cb_x0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_51_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221868 RW
	UINT32 reg_lut_skin_cr_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cr_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cr_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cr_x0               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_52_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022186C RW
	UINT32 reg_lut_skin_y3                  :8;	//7:0	//
	UINT32 reg_lut_skin_y2                  :8;	//15:8	//
	UINT32 reg_lut_skin_y1                  :8;	//23:16	//
	UINT32 reg_lut_skin_y0                  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_53_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221870 RW
	UINT32 reg_lut_face_x3                  :8;	//7:0	//
	UINT32 reg_lut_face_x2                  :8;	//15:8	//
	UINT32 reg_lut_face_x1                  :8;	//23:16	//
	UINT32 reg_lut_face_x0                  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_54_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221874 RW
	UINT32 reg_lut_face_y3                  :8;	//7:0	//
	UINT32 reg_lut_face_y2                  :8;	//15:8	//
	UINT32 reg_lut_face_y1                  :8;	//23:16	//
	UINT32 reg_lut_face_y0                  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_55_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221878 RW
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//19 //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//27:20	//
	UINT32 reg_face_shft                    :2;	//29:28	//0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//30 //
	UINT32 reg_skin_en                      :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_56_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022187C RW
	UINT32 reg_l6_var_diff_dist_h           :4;	//3:0	//
	UINT32 reg_l6_var_diff_dist_w           :4;	//7:4	//
	UINT32 resvd                            :24;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_57_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221880 RW
	UINT32 reg_l6_var_diff_th_cr            :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_cb            :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_yy            :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_58_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221884 RW
	UINT32 reg_l6_var_diff_th_yy3           :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_yy2           :10;	//19:10	//
	UINT32 resvd                            :12;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_59_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221888 RW
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_60_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022188C RW
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_61_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221890 RW
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_62_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221894 RW
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//23:16	//
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_63_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221898 RW
	UINT32 reg_psp_blur_y_max               :8;	//7:0	//
	UINT32 reg_psp_blur_y_min               :8;	//15:8	//
	UINT32 reg_psp_blur_x_max               :8;	//23:16	//
	UINT32 reg_psp_blur_x_min               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022189C RW
	UINT32 reg_psp_blend_x_th3              :8;	//7:0	//
	UINT32 reg_psp_blend_x_th2              :8;	//15:8	//
	UINT32 reg_psp_blend_x_th1              :8;	//23:16	//
	UINT32 reg_psp_blend_x_th0              :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218A0 RW
	UINT32 reg_psp_blend_y_th1              :8;	//7:0	//
	UINT32 reg_psp_blend_y_th0              :8;	//15:8	//
	UINT32 reg_psp_blend_x_th5              :8;	//23:16	//
	UINT32 reg_psp_blend_x_th4              :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218A4 RW
	UINT32 reg_psp_blend_y_th5              :8;	//7:0	//
	UINT32 reg_psp_blend_y_th4              :8;	//15:8	//
	UINT32 reg_psp_blend_y_th3              :8;	//23:16	//
	UINT32 reg_psp_blend_y_th2              :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DC_BNR_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218A8 RW
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//15:8	//
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_64_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218AC RW
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_v_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_65_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218B0 RW
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_h_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_66_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218B4 RW
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_max_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_67_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218B8 RW
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_low_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_68_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218BC RW
	UINT32 reg_diff_mul                     :4;	//3:0	//
	UINT32 reg_2nd_diff_shift               :3;	//6:4	//
	UINT32 reg_2nd_alpha_blur_mode          :1;	//7 //0: no blur, 1: 5x1 blur
	UINT32 reg_2nd_debug_mode               :3;	//10:8	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: blur result	6: osd_flag	7: bypass
	UINT32 reg_odd_sel                      :1;	//11 //
	UINT32 reg_2nd_osd_run_mode             :1;	//12 //
	UINT32 reg_2nd_rd_simple_bit            :3;	//15:13	//
	UINT32 reg_2nd_rd_simple_on             :1;	//16 //
	UINT32 reg_input_csc_en                 :1;	//17 //
	UINT32 reg_2nd_var_v_gain               :2;	//19:18	//
	UINT32 reg_2nd_var_h_gain               :2;	//21:20	//
	UINT32 reg_2nd_var_cut_resolution       :3;	//24:22	//
	UINT32 reg_2nd_var_chroma_en            :1;	//25 //
	UINT32 reg_2nd_var_sel_tmp              :2;	//27:26	//0: 3x3, 1: 9x3, 2: 17x3, 3: 18x3
	UINT32 reg_2nd_fil_sel_tmp              :2;	//29:28	//0: 3x3, 1: 9x3, 2: 17x3
	UINT32 reg_2nd_debug_en                 :1;	//30 //
	UINT32 reg_decon_2nd_en                 :1;	//31 //
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_69_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218C0 RW
	UINT32 reg_2nd_luma_x_th2               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th1               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th0               :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_444_mode                     :1;	//31 //0: repeat, 1: avg
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_70_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218C4 RW
	UINT32 reg_2nd_luma_x_th5               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th4               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th3               :10;	//29:20	//
	UINT32 reg_2nd_luma_bit_opt             :2;	//31:30	//0: lower 10bit w/ clipping, 1: mid 10bit w/ clipping, 2: higher 10bit
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_71_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218C8 RW
	UINT32 reg_2nd_luma_y_th0               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th7               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th6               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_72_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218CC RW
	UINT32 reg_2nd_luma_y_th3               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th2               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th1               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_73_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218D0 RW
	UINT32 reg_2nd_luma_y_th6               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th5               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th4               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_74_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218D4 RW
	UINT32 reg_2nd_var_x_th1                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th0                :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th7               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_75_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218D8 RW
	UINT32 reg_2nd_var_y_th0                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th3                :10;	//19:10	//
	UINT32 reg_2nd_var_x_th2                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_76_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218DC RW
	UINT32 reg_2nd_var_y_th3                :10;	//9:0	//
	UINT32 reg_2nd_var_y_th2                :10;	//19:10	//
	UINT32 reg_2nd_var_y_th1                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_77_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218E0 RW
	UINT32 reg_2nd_diff_x_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_x_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_x_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_x_th3               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_78_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218E4 RW
	UINT32 reg_2nd_diff_y_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_y_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_y_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_y_th3               :8;	//31:24	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_79_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218E8 RW
	UINT32 reg_2nd_rd_simple_init_yy        :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_80_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218EC RW
	UINT32 reg_2nd_rd_simple_init_cb        :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_81_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218F0 RW
	UINT32 reg_2nd_rd_simple_init_cr        :32;	//31:0	//
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_82_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02218F4 RW
	UINT32 reg_overlap_hsize                :8;	//7:0	//* final release로 인해 RTL에서는 "reg_overlap"으로 사용중(다음버전에 명칭 업데이트 예정)	가용범위 : 4~128 (0~3 사이의 값 입력시 오류 발생)
	UINT32 reg_trans_pos                    :6;	//13:8	//h_block 개수보다 작아야 함
	UINT32 resvd0                           :14;
	UINT32 reg_col_index                    :2;	//29:28	//* final release로 인해 RTL에서는 "reg_boundary_side"으로 사용중(다음버전에 명칭 업데이트 예정)	Split/Merger에 의해서 Decontour 모듈은 3 2 1 0 으로 인덱싱 되어있으나 설정은 아래의 숫자를 참조	내부 동작적인 측면에서 1과 2는 똑같은 형태(튜닝 등에 의해서 위치를 표시하기 위해 구별)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd1                           :1;
	UINT32 reg_col_mode_en                  :1;	//31 //* final release로 인해 RTL에서는 "reg_boundary_en"으로 사용중(다음버전에 명칭 업데이트 예정)	0 : col_mode off	1 : col_mode on
	};
	};
}PE_F20_DNR0_REG_DECON_CTRL_83_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F00 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_ND0_OBC_OBJT_PSP_CTRL00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F04 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :7;	//22:16	//Number of hblock
	UINT32 resvd2                           :1;
	UINT32 reg_l5_hei                       :7;	//30:24	//Number of vblock
	UINT32 resvd3                           :1;
	};
	};
}PE_F20_ND0_OBC_OBJT_PSP_CTRL01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F08 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line 경계에서 repeat 시킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//9 //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//15 //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction의 H margin
	};
	};
}PE_F20_ND0_OBC_OBJT_PSP_CTRL02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F0C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :3;
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : 후보 box 영역에 대한 threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : 후보 box 영역에 대한 threshold
	};
	};
}PE_F20_ND0_OBC_OBJT_EDGE_TH_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F10 RW
	UINT32 reg_force_w1_pos                 :7;	//6:0	//(w1, h1)
	UINT32 resvd0                           :1;
	UINT32 reg_force_h1_pos                 :7;	//14:8	//(w1, h1)
	UINT32 resvd1                           :1;
	UINT32 reg_force_w2_pos                 :7;	//22:16	//(w2, h2)
	UINT32 resvd2                           :1;
	UINT32 reg_force_h2_pos                 :7;	//30:24	//(w2, h2)
	UINT32 reg_force_pos_en                 :1;	//31 //forced FG box posotion
	};
	};
}PE_F20_ND0_OBC_OBJT_FG_POSITION_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F14 RW
	UINT32 reg_perspect_lut_x_0             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F18 RW
	UINT32 reg_perspect_lut_x_1             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F1C RW
	UINT32 reg_perspect_lut_x_2             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F20 RW
	UINT32 reg_perspect_lut_x_3             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F24 RW
	UINT32 reg_perspect_lut_y_0             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F28 RW
	UINT32 reg_perspect_lut_y_1             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F2C RW
	UINT32 reg_perspect_lut_y_2             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F30 RW
	UINT32 reg_perspect_lut_y_3             :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F34 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
	};
}PE_F20_ND0_OBC_OBJT_PROB_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F38 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (1)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
	};
}PE_F20_ND0_OBC_OBJT_ELLIPS_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F3C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
	};
}PE_F20_ND0_OBC_OBJT_PROB_DIFF_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F40 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (알고리즘 parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (알고리즘 parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
	};
}PE_F20_ND0_OBC_OBJT_OBJECT_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F44 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd                            :31;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F4C RW
	UINT32 reg_psp_iir_alpha                :6;	//5:0	//IIR Alpha blending rate (0 ~ 1) 	6bit 기준이고 3A = 90%
	UINT32 resvd                            :25;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial시 사용( data reset)
	};
	};
}PE_F20_ND0_OBC_OBJT_PSP_IIR_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F50 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
	};
}PE_F20_ND0_OBC_OBJT_PSP_GAIN_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F5C RW
	UINT32 reg_vrtx_gain_tl_i               :8;	//7:0	//
	UINT32 reg_vrtx_gain_tr_i               :8;	//15:8	//
	UINT32 reg_vrtx_gain_bl_i               :8;	//23:16	//
	UINT32 reg_vrtx_gain_br_i               :8;	//31:24	//
	};
	};
}PE_F20_ND0_OBC_OBJT_VRTX_CPC_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F60 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_HCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F64 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_HCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F68 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_HCOEF45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F6C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_HCOEF67_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F70 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_HCOEF8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F74 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_VCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F78 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_VCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221F7C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_ND0_OBC_OBJT_BLUR_VCOEF4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222000 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
	};
}PE_F20_ND0_OBC_OBJT_L5_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222004 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
	};
}PE_F20_ND0_OBC_OBJT_L5_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222008 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
	};
}PE_F20_ND0_OBC_OBJT_L0_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022200C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
	};
}PE_F20_ND0_OBC_OBJT_L0_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222010 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_ND0_OBC_OBJT_EDGE_WIN_H_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222014 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_ND0_OBC_OBJT_EDGE_WIN_V_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222028 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :6;	//9:4	//threshold of lower
	UINT32 resvd1                           :2;
	UINT32 th_upper                         :6;	//17:12	//threshold of upper
	UINT32 resvd2                           :2;
	UINT32 prc_step                         :6;	//25:20	//same protection step
	UINT32 resvd3                           :6;
	};
	};
}PE_F20_ND0_OBC_OBJT_PSP_IIR1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022202C RW
	UINT32 bg_measure_en                    :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 h_num                            :4;	//7:4	//divide hsize
	UINT32 v_num                            :4;	//11:8	//divide vsize
	UINT32 obj_th0                          :6;	//17:12	//threshold of minimum gain
	UINT32 resvd1                           :2;
	UINT32 obj_th1                          :8;	//27:20	//threshold of bin counting
	UINT32 resvd2                           :4;
	};
	};
}PE_F20_ND0_OBC_OBJT_BG_MEASURE_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222100 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_ND0_OBC_FACE_PSP_CTRL00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222104 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :7;	//22:16	//Number of hblock
	UINT32 resvd2                           :1;
	UINT32 reg_l5_hei                       :7;	//30:24	//Number of vblock
	UINT32 resvd3                           :1;
	};
	};
}PE_F20_ND0_OBC_FACE_PSP_CTRL01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222108 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line 경계에서 repeat 시킬 h pixel 개수
	UINT32 resvd                            :1;
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//15 //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction의 H margin
	};
	};
}PE_F20_ND0_OBC_FACE_PSP_CTRL02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022210C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :3;
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : 후보 box 영역에 대한 threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : 후보 box 영역에 대한 threshold
	};
	};
}PE_F20_ND0_OBC_FACE_EDGE_TH_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222110 RW
	UINT32 reg_force_w1_pos                 :7;	//6:0	//(w1, h1)
	UINT32 resvd0                           :1;
	UINT32 reg_force_h1_pos                 :7;	//14:8	//(w1, h1)
	UINT32 resvd1                           :1;
	UINT32 reg_force_w2_pos                 :7;	//22:16	//(w2, h2)
	UINT32 resvd2                           :1;
	UINT32 reg_force_h2_pos                 :7;	//30:24	//(w2, h2)
	UINT32 reg_force_pos_en                 :1;	//31 //forced FG box posotion
	};
	};
}PE_F20_ND0_OBC_FACE_FG_POSITION_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222114 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222118 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022211C RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222120 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222124 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222128 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022212C RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222130 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_ND0_OBC_FACE_RESERVED7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222134 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
	};
}PE_F20_ND0_OBC_FACE_PROB_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222138 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (only face mode on)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
	};
}PE_F20_ND0_OBC_FACE_ELLIPS_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022213C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
	};
}PE_F20_ND0_OBC_FACE_PROB_DIFF_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222140 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (알고리즘 parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (알고리즘 parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
	};
}PE_F20_ND0_OBC_FACE_OBJECT_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222144 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd                            :31;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022214C RW
	UINT32 reg_psp_iir_alpha                :6;	//5:0	//IIR Alpha blending rate (0 ~ 1) 	6bit 기준이고 3A = 90%
	UINT32 resvd                            :25;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial시 사용( data reset)
	};
	};
}PE_F20_ND0_OBC_FACE_PSP_IIR_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222150 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
	};
}PE_F20_ND0_OBC_FACE_PSP_GAIN_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022215C RW
	UINT32 reg_vrtx_gain_tl_i               :8;	//7:0	//
	UINT32 reg_vrtx_gain_tr_i               :8;	//15:8	//
	UINT32 reg_vrtx_gain_bl_i               :8;	//23:16	//
	UINT32 reg_vrtx_gain_br_i               :8;	//31:24	//
	};
	};
}PE_F20_ND0_OBC_FACE_VRTX_CPC_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222160 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_HCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222164 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_HCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222168 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_HCOEF45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022216C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_HCOEF67_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222170 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_HCOEF8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222174 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_VCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222178 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_VCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022217C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_ND0_OBC_FACE_BLUR_VCOEF4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222200 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
	};
}PE_F20_ND0_OBC_FACE_L5_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222204 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
	};
}PE_F20_ND0_OBC_FACE_L5_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222208 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
	};
}PE_F20_ND0_OBC_FACE_L0_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022220C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
	};
}PE_F20_ND0_OBC_FACE_L0_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222210 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_ND0_OBC_FACE_EDGE_WIN_H_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222214 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_ND0_OBC_FACE_EDGE_WIN_V_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222228 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :6;	//9:4	//threshold of lower
	UINT32 resvd1                           :2;
	UINT32 th_upper                         :6;	//17:12	//threshold of upper
	UINT32 resvd2                           :2;
	UINT32 prc_step                         :6;	//25:20	//same protection step
	UINT32 resvd3                           :6;
	};
	};
}PE_F20_ND0_OBC_FACE_PSP_IIR1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022222C RW
	UINT32 bg_measure_en                    :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 h_num                            :4;	//7:4	//divide hsize
	UINT32 v_num                            :4;	//11:8	//divide vsize
	UINT32 obj_th0                          :6;	//17:12	//threshold of minimum gain
	UINT32 resvd1                           :2;
	UINT32 obj_th1                          :8;	//27:20	//threshold of bin counting
	UINT32 resvd2                           :4;
	};
	};
}PE_F20_ND0_OBC_FACE_BG_MEASURE_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222244 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
	};
}PE_F20_ND0_OBC_FACE_FACE0_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222248 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
	};
}PE_F20_ND0_OBC_FACE_FACE1_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022224C RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
	};
}PE_F20_ND0_OBC_FACE_FACE2_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222250 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
	};
}PE_F20_ND0_OBC_FACE_FACE3_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222254 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_ND0_OBC_FACE_ELLIPS0_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222258 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_ND0_OBC_FACE_ELLIPS1_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022225C RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_ND0_OBC_FACE_ELLIPS2_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0222260 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_ND0_OBC_FACE_ELLIPS3_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD04 RW
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//0 //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//1 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.	(F20 delete)
	UINT32 reg_1st_out_rd_out_clip          :1;	//2 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.	(F20 delete)
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//7 //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//8 //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//9 //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//10 //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//11 //0: 12-bit full	1: 1st_out_rd 입력 /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_1st_out_rd_min_alpha         :8;	//27:20	//
	UINT32 reg_1st_out_rd_bit               :3;	//30:28	//
	UINT32 reg_1st_out_rd_on                :1;	//31 //default = '0', RD off
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD08 RW
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD0C RW
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD10 RW
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD14 RW
	UINT32 reg_1st_out_rd_init_yy           :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD18 RW
	UINT32 reg_1st_out_rd_init_cb           :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD1C RW
	UINT32 reg_1st_out_rd_init_cr           :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD20 RW
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//7:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//11 //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//27:20	//
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//31 //default = '0', RD off
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD24 RW
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//29:28	//
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//31:30	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD28 RW
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD2C RW
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD30 RW
	UINT32 reg_2nd_out_rd_init_yy           :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD34 RW
	UINT32 reg_2nd_out_rd_init_cb           :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD38 RW
	UINT32 reg_2nd_out_rd_init_cr           :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD3C RW
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//31:0	//Not used in F20
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD40 RW
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//31:0	//Not used in F20
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD44 RW
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//31:0	//Not used in F20
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD48 RW
	UINT32 reg_blur_lb_var_cut_res          :4;	//3:0	//>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//6 //
	UINT32 reg_l6_var_2x2_bit               :1;	//7 //1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//13:8	//Not used in F20
	UINT32 reg_1st_debug_en                 :1;	//14 //
	UINT32 reg_l6_var_csc_en                :1;	//15 //(Not used in F20, gate 문제로 제거)ND에선 사용 안 함
	UINT32 reg_force_block_no_h             :6;	//21:16	//Not used in F20
	UINT32 reg_4k_5x3_mode_en               :1;	//22 //0: 5x5(u2, u1, cc, d1, d2) , 1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//23 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_rd_clip                      :1;	//24 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_input_csc_en                 :1;	//25 //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :4;	//29:26	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_var_2x2	11: skin	12: face	13: face_skin	14: input_blur
	UINT32 reg_force_block_no_en            :1;	//30 //Not used in F20
	UINT32 reg_decon_1st_en                 :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD4C RW
	UINT32 reg_var_chroma_en                :1;	//0 //
	UINT32 resvd0                           :1;
	UINT32 reg_blur_final_size              :1;	//2 //0: new_2x2, 1: new_3x3
	UINT32 resvd1                           :1;
	UINT32 reg_blur_div_zero                :1;	//4 //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//6:5	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//8:7	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//11:9	//0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//12 //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//13 //not used in O20 -> 신호 자체는 연결되어있음(F20)
	UINT32 reg_led_10b_mode_diff_pel        :1;	//14 //not used in O20
	UINT32 reg_l6_var_debug_en              :1;	//15 //reg_lb_var_en = 1 일때 동작
	UINT32 reg_luma_bit_opt                 :1;	//16 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//17 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//18 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//19 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//23:20	//
	UINT32 reg_var_h_gain                   :4;	//27:24	//
	UINT32 reg_var_cut_resolution           :4;	//31:28	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD50 RW
	UINT32 reg_decon_diff_x_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_x_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_x_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_x_th3             :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD54 RW
	UINT32 reg_decon_diff_y_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_y_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_y_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_y_th3             :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD58 RW
	UINT32 reg_decon_var_x_th2              :10;	//9:0	//
	UINT32 reg_decon_var_x_th1              :10;	//19:10	//
	UINT32 reg_decon_var_x_th0              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD5C RW
	UINT32 reg_decon_var_y_th1              :10;	//9:0	//
	UINT32 reg_decon_var_y_th0              :10;	//19:10	//
	UINT32 reg_decon_var_x_th3              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CD60 RW
	UINT32 reg_decon_luma_x_th0             :10;	//9:0	//
	UINT32 reg_decon_var_y_th3              :10;	//19:10	//
	UINT32 reg_decon_var_y_th2              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_23_T;
typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDBC RW
	UINT32 reg_decon_luma_x_th3             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th2             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th1             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDC0 RW
	UINT32 reg_decon_luma_x_th6             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th5             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th4             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDC4 RW
	UINT32 reg_decon_luma_y_th1             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th0             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th7             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDC8 RW
	UINT32 reg_decon_luma_y_th4             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th3             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th2             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDCC RW
	UINT32 reg_decon_luma_y_th7             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th6             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th5             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDD0 RW
	UINT32 reg_block_size_v                 :8;	//7:0	//
	UINT32 reg_block_size_h                 :8;	//15:8	//
	UINT32 reg_block_no_v                   :6;	//21:16	//
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//29:24	//
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDD4 RW
	UINT32 reg_last_block_size_v            :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//19:16	//
	UINT32 reg_diff_shift                   :3;	//22:20	//
	UINT32 reg_osd_run_mode                 :1;	//23 //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//24 //Not used in F20
	UINT32 reg_alpha_blur_mode              :2;	//26:25	//0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//28:27	//Not used in F20
	UINT32 reg_diff_use_seldiff             :1;	//29 //
	UINT32 reg_diff_calc_mode               :2;	//31:30	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDD8 RW
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//9:0	//Not used in F20
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//19:10	//Not used in F20
	UINT32 reg_lb_var_cut_res               :4;	//23:20	//
	UINT32 reg_master_gain                  :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDDC RW
	UINT32 reg_l6_var_x_th2                 :10;	//9:0	//
	UINT32 reg_l6_var_x_th1                 :10;	//19:10	//
	UINT32 reg_l6_var_x_th0                 :10;	//29:20	//
	UINT32 reg_lb_var_opt                   :1;	//30 //
	UINT32 reg_lb_var_en                    :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_32_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDE0 RW
	UINT32 reg_l6_var_y_th1                 :10;	//9:0	//
	UINT32 reg_l6_var_y_th0                 :10;	//19:10	//
	UINT32 reg_l6_var_x_th3                 :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_33_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDE4 RW
	UINT32 reg_l6_var_y_th3                 :10;	//9:0	//
	UINT32 reg_l6_var_y_th2                 :10;	//19:10	//
	UINT32 reg_l6_pel_trunc                 :2;	//21:20	//
	UINT32 reg_var_v_cut                    :2;	//23:22	//
	UINT32 reg_var_h_cut                    :2;	//25:24	//
	UINT32 reg_var_t7_offset                :2;	//27:26	//
	UINT32 reg_decon_rd_simple_bit          :3;	//30:28	//
	UINT32 reg_decon_rd_simple_on           :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_34_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDE8 RW
	UINT32 reg_decon_rd_simple_init_yy      :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_35_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDEC RW
	UINT32 reg_decon_rd_simple_init_cb      :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_36_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDF0 RW
	UINT32 reg_decon_rd_simple_init_cr      :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_37_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDF4 RW
	UINT32 reg_rd_min_pel_cb                :12;	//11:0	//
	UINT32 reg_rd_min_pel_yy                :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//30:28	//
	UINT32 reg_decon_rd_on                  :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_38_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDF8 RW
	UINT32 reg_rd_max_pel_yy                :12;	//11:0	//
	UINT32 reg_rd_min_pel_cr                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_39_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CDFC RW
	UINT32 reg_rd_max_pel_cr                :12;	//11:0	//
	UINT32 reg_rd_max_pel_cb                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_40_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE00 RW
	UINT32 reg_rd_init_yy                   :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_41_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE04 RW
	UINT32 reg_rd_init_cb                   :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_42_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE08 RW
	UINT32 reg_rd_init_cr                   :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_43_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE0C RW
	UINT32 reg_motion_gain_x3               :8;	//7:0	//
	UINT32 reg_motion_gain_x2               :8;	//15:8	//
	UINT32 reg_motion_gain_x1               :8;	//23:16	//
	UINT32 reg_motion_gain_x0               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_44_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE10 RW
	UINT32 reg_motion_gain_y3               :8;	//7:0	//
	UINT32 reg_motion_gain_y2               :8;	//15:8	//
	UINT32 reg_motion_gain_y1               :8;	//23:16	//
	UINT32 reg_motion_gain_y0               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE14 RW
	UINT32 reg_bbd_y0                       :12;	//11:0	//Operated on O20(4K)
	UINT32 reg_bbd_x0                       :12;	//23:12	//Operated on O20(4K)
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//28 //
	UINT32 reg_blur2_sim_en                 :1;	//29 //
	UINT32 reg_amf_lut_bit                  :1;	//30 //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_46_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE18 RW
	UINT32 reg_bbd_y1                       :12;	//11:0	//Operated on O20(4K)
	UINT32 reg_bbd_x1                       :12;	//23:12	//Operated on O20(4K)
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//28:26	//
	UINT32 reg_blur2_sim_ratio              :3;	//31:29	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_47_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE1C RW
	UINT32 reg_lut_blur_sim_x3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_x2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_x1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_x0              :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_48_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE20 RW
	UINT32 reg_lut_blur_sim_y3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_y2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_y1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_y0              :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_49_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE24 RW
	UINT32 reg_lut_skin_yy_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_yy_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_yy_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_yy_x0               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_50_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE28 RW
	UINT32 reg_lut_skin_cb_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cb_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cb_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cb_x0               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_51_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE2C RW
	UINT32 reg_lut_skin_cr_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cr_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cr_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cr_x0               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_52_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE30 RW
	UINT32 reg_lut_skin_y3                  :8;	//7:0	//
	UINT32 reg_lut_skin_y2                  :8;	//15:8	//
	UINT32 reg_lut_skin_y1                  :8;	//23:16	//
	UINT32 reg_lut_skin_y0                  :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_53_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE34 RW
	UINT32 reg_lut_face_x3                  :8;	//7:0	//
	UINT32 reg_lut_face_x2                  :8;	//15:8	//
	UINT32 reg_lut_face_x1                  :8;	//23:16	//
	UINT32 reg_lut_face_x0                  :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_54_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE38 RW
	UINT32 reg_lut_face_y3                  :8;	//7:0	//
	UINT32 reg_lut_face_y2                  :8;	//15:8	//
	UINT32 reg_lut_face_y1                  :8;	//23:16	//
	UINT32 reg_lut_face_y0                  :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_55_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE3C RW
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//19 //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//27:20	//
	UINT32 reg_face_shft                    :2;	//29:28	//0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//30 //
	UINT32 reg_skin_en                      :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_56_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE40 RW
	UINT32 reg_l6_var_diff_dist_h           :4;	//3:0	//
	UINT32 reg_l6_var_diff_dist_w           :4;	//7:4	//
	UINT32 resvd                            :24;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_57_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE44 RW
	UINT32 reg_l6_var_diff_th_cr            :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_cb            :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_yy            :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_58_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE48 RW
	UINT32 reg_l6_var_diff_th_yy3           :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_yy2           :10;	//19:10	//
	UINT32 resvd                            :12;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_59_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE4C RW
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_60_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE50 RW
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_61_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE54 RW
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_62_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE58 RW
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//23:16	//
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_63_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE5C RW
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//15:8	//
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_64_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE60 RW
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_v_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_65_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE64 RW
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_h_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_66_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE68 RW
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_max_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_67_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE6C RW
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_low_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_68_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE70 RW
	UINT32 reg_diff_mul                     :4;	//3:0	//
	UINT32 reg_2nd_diff_shift               :3;	//6:4	//Not used in F20
	UINT32 reg_2nd_alpha_blur_mode          :1;	//7 //0: no blur, 1: 5x1 blur
	UINT32 reg_2nd_debug_mode               :3;	//10:8	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: blur result	6: osd_flag	7: bypass
	UINT32 reg_odd_sel                      :1;	//11 //
	UINT32 reg_2nd_osd_run_mode             :1;	//12 //
	UINT32 reg_2nd_rd_simple_bit            :3;	//15:13	//
	UINT32 reg_2nd_rd_simple_on             :1;	//16 //
	UINT32 reg_input_csc_en                 :1;	//17 //
	UINT32 reg_2nd_var_v_gain               :2;	//19:18	//
	UINT32 reg_2nd_var_h_gain               :2;	//21:20	//
	UINT32 reg_2nd_var_cut_resolution       :3;	//24:22	//
	UINT32 reg_2nd_var_chroma_en            :1;	//25 //
	UINT32 reg_2nd_var_sel_tmp              :2;	//27:26	//0: 3x3, 1: 9x3, 2: 17x3, 3: 18x3
	UINT32 reg_2nd_fil_sel_tmp              :2;	//29:28	//0: 3x3, 1: 9x3, 2: 17x3
	UINT32 reg_2nd_debug_en                 :1;	//30 //
	UINT32 reg_decon_2nd_en                 :1;	//31 //
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_69_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE74 RW
	UINT32 reg_2nd_luma_x_th2               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th1               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th0               :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_444_mode                     :1;	//31 //0: repeat, 1: avg
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_70_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE78 RW
	UINT32 reg_2nd_luma_x_th5               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th4               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th3               :10;	//29:20	//
	UINT32 reg_2nd_luma_bit_opt             :2;	//31:30	//0: lower 10bit w/ clipping, 1: mid 10bit w/ clipping, 2: higher 10bit
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_71_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE7C RW
	UINT32 reg_2nd_luma_y_th0               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th7               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th6               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_72_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE80 RW
	UINT32 reg_2nd_luma_y_th3               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th2               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th1               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_73_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE84 RW
	UINT32 reg_2nd_luma_y_th6               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th5               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th4               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_74_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE88 RW
	UINT32 reg_2nd_var_x_th1                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th0                :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th7               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_75_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE8C RW
	UINT32 reg_2nd_var_y_th0                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th3                :10;	//19:10	//
	UINT32 reg_2nd_var_x_th2                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_76_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE90 RW
	UINT32 reg_2nd_var_y_th3                :10;	//9:0	//
	UINT32 reg_2nd_var_y_th2                :10;	//19:10	//
	UINT32 reg_2nd_var_y_th1                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_77_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE94 RW
	UINT32 reg_2nd_diff_x_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_x_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_x_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_x_th3               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_78_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE98 RW
	UINT32 reg_2nd_diff_y_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_y_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_y_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_y_th3               :8;	//31:24	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_79_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CE9C RW
	UINT32 reg_2nd_rd_simple_init_yy        :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_80_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CEA0 RW
	UINT32 reg_2nd_rd_simple_init_cb        :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_81_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CEA4 RW
	UINT32 reg_2nd_rd_simple_init_cr        :32;	//31:0	//
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_82_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF036CEA8 RW
	UINT32 reg_overlap_hsize                :8;	//7:0	//* final release로 인해 RTL에서는 "reg_overlap"으로 사용중(다음버전에 명칭 업데이트 예정)	가용범위 : 4~128 (0~3 사이의 값 입력시 오류 발생)
	UINT32 reg_trans_pos                    :6;	//13:8	//h_block 개수보다 작아야 함
	UINT32 resvd0                           :14;
	UINT32 reg_col_index                    :2;	//29:28	//* final release로 인해 RTL에서는 "reg_boundary_side"으로 사용중(다음버전에 명칭 업데이트 예정)	Split/Merger에 의해서 Decontour 모듈은 3 2 1 0 으로 인덱싱 되어있으나 설정은 아래의 숫자를 참조	내부 동작적인 측면에서 1과 2는 똑같은 형태(튜닝 등에 의해서 위치를 표시하기 위해 구별)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd1                           :1;
	UINT32 reg_col_mode_en                  :1;	//31 //* final release로 인해 RTL에서는 "reg_boundary_en"으로 사용중(다음버전에 명칭 업데이트 예정)	0 : col_mode off	1 : col_mode on
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_83_T;


typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEAC RW
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//1:0	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//3:2	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//5:4	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//7:6	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//9:8	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//11:10	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//28 //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//29 //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//30 //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_84_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEB0 RW
	UINT32 reg_rd_roi_x1                    :12;	//11:0	//실제 좌표에서 /2를 한 값을 입력해야 함(다음 버전 업데이트)
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//27:16	//실제 좌표에서 /2를 한 값을 입력해야 함(다음 버전 업데이트)
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_85_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEB4 RW
	UINT32 reg_rd_roi_y1                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_86_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEB8 RW
	UINT32 reg_1st_rd_luma_x1               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x0               :10;	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_prev_x                   :12;	//31:20	//Defualt: 30	이전 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_87_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEBC RW
	UINT32 reg_1st_rd_luma_x3               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x2               :10;	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_next_x                   :12;	//31:20	//Defualt: 40	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_88_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEC0 RW
	UINT32 reg_1st_rd_luma_x5               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_prev_y                   :7;	//30:24	//Defualt: 120	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_89_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEC4 RW
	UINT32 reg_1st_rd_luma_x7               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_next_y                   :7;	//30:24	//Defualt: 121	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_90_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CEC8 RW
	UINT32 reg_1st_rd_luma_y1               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_91_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CECC RW
	UINT32 reg_1st_rd_luma_y3               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_92_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CED0 RW
	UINT32 reg_1st_rd_luma_y5               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_93_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF036CED4 RW
	UINT32 reg_1st_rd_luma_y7               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
	};
}PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_94_T;


typedef struct {
	PE_F20_DNR0_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xF0221594
	PE_F20_DNR0_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xF02215A0
	PE_F20_DNR0_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xF02215A4
	PE_F20_DNR0_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xF02215A8
	PE_F20_DNR0_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xF02215AC
	PE_F20_DNR0_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xF02215B0
	PE_F20_DNR0_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xF02215B4
	PE_F20_DNR0_DETAIL_CTRL_T                                  detail_ctrl;	//0xF02215B8
	PE_F20_DNR0_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xF02215BC
	PE_F20_DNR0_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xF02215C0
	PE_F20_DNR0_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xF02215C4
	PE_F20_DNR0_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xF02215C8
	PE_F20_DNR0_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xF02215CC
	PE_F20_DNR0_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xF02215D0
	PE_F20_DNR0_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xF02215D4
	PE_F20_DNR0_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xF02215D8
	PE_F20_DNR0_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xF02215DC
	PE_F20_DNR0_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xF02215E4
	PE_F20_DNR0_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xF02215E8
	PE_F20_DNR0_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xF02215F0
	PE_F20_DNR0_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xF02215F4
	PE_F20_DNR0_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xF02215F8
	PE_F20_DNR0_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xF0221600
	PE_F20_DNR0_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xF0221604
	PE_F20_DNR0_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xF0221608
	PE_F20_DNR0_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xF022160C
	PE_F20_DNR0_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xF0221610
	PE_F20_DNR0_SC_BNR_CTRL_0_T                              sc_bnr_ctrl_0;	//0xF022166C
	PE_F20_DNR0_SC_BNR_CTRL_1_T                              sc_bnr_ctrl_1;	//0xF0221670
	PE_F20_DNR0_SC_BNR_CTRL_2_T                              sc_bnr_ctrl_2;	//0xF0221674
	PE_F20_DNR0_SC_BNR_CTRL_3_T                              sc_bnr_ctrl_3;	//0xF0221678
	PE_F20_DNR0_SC_BNR_CTRL_4_T                              sc_bnr_ctrl_4;	//0xF022167C
	PE_F20_DNR0_SC_BNR_CTRL_5_T                              sc_bnr_ctrl_5;	//0xF0221680
	PE_F20_DNR0_SC_BNR_CTRL_6_T                              sc_bnr_ctrl_6;	//0xF0221684
	PE_F20_DNR0_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xF022169C
	PE_F20_DNR0_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xF02216A0
	PE_F20_DNR0_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xF02216A4
	PE_F20_DNR0_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xF02216A8
	PE_F20_DNR0_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xF02216AC
	PE_F20_DNR0_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xF02216B0
	PE_F20_DNR0_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xF02216B4
	PE_F20_DNR0_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xF02216B8
	PE_F20_DNR0_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xF02216BC
	PE_F20_DNR0_AC_BNR_15_T                                      ac_bnr_15;	//0xF0221730
	PE_F20_DNR0_AC_BNR_16_T                                      ac_bnr_16;	//0xF0221734
	PE_F20_DNR0_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xF0221764
	PE_F20_DNR0_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xF0221768
	PE_F20_DNR0_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xF022176C
	PE_F20_DNR0_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xF0221770
	PE_F20_DNR0_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xF0221774
	PE_F20_DNR0_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xF0221778
	PE_F20_DNR0_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xF022177C
	PE_F20_DNR0_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xF0221780
	PE_F20_DNR0_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xF0221784
	PE_F20_DNR0_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xF0221788
	PE_F20_DNR0_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xF022178C
	PE_F20_DNR0_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xF0221790
	PE_F20_DNR0_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xF0221794
	PE_F20_DNR0_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xF0221798
	PE_F20_DNR0_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xF022179C
	PE_F20_DNR0_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xF02217A8
	PE_F20_DNR0_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xF02217AC
	PE_F20_DNR0_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xF02217B0
	PE_F20_DNR0_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xF02217B4
	PE_F20_DNR0_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xF02217B8
	PE_F20_DNR0_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xF02217BC
	PE_F20_DNR0_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xF02217C0
	PE_F20_DNR0_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xF02217C4
	PE_F20_DNR0_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xF02217C8
	PE_F20_DNR0_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xF02217CC
	PE_F20_DNR0_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xF02217D0
	PE_F20_DNR0_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xF02217D4
	PE_F20_DNR0_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xF02217D8
	PE_F20_DNR0_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xF02217DC
	PE_F20_DNR0_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xF02217E0
	PE_F20_DNR0_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xF02217E4
	PE_F20_DNR0_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xF02217E8
	PE_F20_DNR0_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xF02217EC
	PE_F20_DNR0_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xF02217F0
	PE_F20_DNR0_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xF02217F4
	PE_F20_DNR0_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xF02217F8
	PE_F20_DNR0_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xF02217FC
	PE_F20_DNR0_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xF0221800
	PE_F20_DNR0_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xF0221804
	PE_F20_DNR0_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xF0221808
	PE_F20_DNR0_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xF022180C
	PE_F20_DNR0_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xF0221810
	PE_F20_DNR0_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xF0221814
	PE_F20_DNR0_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xF0221818
	PE_F20_DNR0_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xF022181C
	PE_F20_DNR0_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xF0221820
	PE_F20_DNR0_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xF0221824
	PE_F20_DNR0_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xF0221828
	PE_F20_DNR0_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xF022182C
	PE_F20_DNR0_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xF0221830
	PE_F20_DNR0_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xF0221834
	PE_F20_DNR0_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xF0221838
	PE_F20_DNR0_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xF022183C
	PE_F20_DNR0_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xF0221840
	PE_F20_DNR0_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xF0221844
	PE_F20_DNR0_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xF0221848
	PE_F20_DNR0_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xF022184C
	PE_F20_DNR0_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xF0221850
	PE_F20_DNR0_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xF0221854
	PE_F20_DNR0_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xF0221858
	PE_F20_DNR0_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xF022185C
	PE_F20_DNR0_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xF0221860
	PE_F20_DNR0_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xF0221864
	PE_F20_DNR0_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xF0221868
	PE_F20_DNR0_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xF022186C
	PE_F20_DNR0_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xF0221870
	PE_F20_DNR0_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xF0221874
	PE_F20_DNR0_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xF0221878
	PE_F20_DNR0_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xF022187C
	PE_F20_DNR0_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xF0221880
	PE_F20_DNR0_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xF0221884
	PE_F20_DNR0_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xF0221888
	PE_F20_DNR0_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xF022188C
	PE_F20_DNR0_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xF0221890
	PE_F20_DNR0_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xF0221894
	PE_F20_DNR0_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xF0221898
	PE_F20_DNR0_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xF022189C
	PE_F20_DNR0_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xF02218A0
	PE_F20_DNR0_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xF02218A4
	PE_F20_DNR0_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xF02218A8
	PE_F20_DNR0_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xF02218AC
	PE_F20_DNR0_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xF02218B0
	PE_F20_DNR0_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xF02218B4
	PE_F20_DNR0_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xF02218B8
	PE_F20_DNR0_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xF02218BC
	PE_F20_DNR0_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xF02218C0
	PE_F20_DNR0_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xF02218C4
	PE_F20_DNR0_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xF02218C8
	PE_F20_DNR0_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xF02218CC
	PE_F20_DNR0_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xF02218D0
	PE_F20_DNR0_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xF02218D4
	PE_F20_DNR0_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xF02218D8
	PE_F20_DNR0_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xF02218DC
	PE_F20_DNR0_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xF02218E0
	PE_F20_DNR0_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xF02218E4
	PE_F20_DNR0_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xF02218E8
	PE_F20_DNR0_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xF02218EC
	PE_F20_DNR0_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xF02218F0
	//PE_F20_DNR0_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xF02218F4
}PE_CHPI_DNR_TBL_F20_T;

typedef struct {
	PE_F20_ND0_OBC_OBJT_PSP_CTRL00_T                            psp_ctrl00_o;	//0xF0221F00
	PE_F20_ND0_OBC_OBJT_PSP_CTRL01_T                            psp_ctrl01_o;	//0xF0221F04
	PE_F20_ND0_OBC_OBJT_PSP_CTRL02_T                            psp_ctrl02_o;	//0xF0221F08
	PE_F20_ND0_OBC_OBJT_EDGE_TH_T                                  edge_th_o;	//0xF0221F0C
	PE_F20_ND0_OBC_OBJT_FG_POSITION_T                          fg_position_o;	//0xF0221F10
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X0_T                  perspect_lut_x0_o;	//0xF0221F14
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X1_T                  perspect_lut_x1_o;	//0xF0221F18
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X2_T                  perspect_lut_x2_o;	//0xF0221F1C
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_X3_T                  perspect_lut_x3_o;	//0xF0221F20
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y0_T                  perspect_lut_y0_o;	//0xF0221F24
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y1_T                  perspect_lut_y1_o;	//0xF0221F28
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y2_T                  perspect_lut_y2_o;	//0xF0221F2C
	PE_F20_ND0_OBC_OBJT_PERSPECT_LUT_Y3_T                  perspect_lut_y3_o;	//0xF0221F30
	PE_F20_ND0_OBC_OBJT_PROB_MAP_T                                prob_map_o;	//0xF0221F34
	PE_F20_ND0_OBC_OBJT_ELLIPS_MAP_T                            ellips_map_o;	//0xF0221F38
	PE_F20_ND0_OBC_OBJT_PROB_DIFF_MAP_T                      prob_diff_map_o;	//0xF0221F3C
	PE_F20_ND0_OBC_OBJT_OBJECT_MAP_T                            object_map_o;	//0xF0221F40
	PE_F20_ND0_OBC_OBJT_BLUR_MAP_T                                blur_map_o;	//0xF0221F44
	PE_F20_ND0_OBC_OBJT_PSP_IIR_T                                  psp_iir_o;	//0xF0221F4C
	PE_F20_ND0_OBC_OBJT_PSP_GAIN_T                                psp_gain_o;	//0xF0221F50
	PE_F20_ND0_OBC_OBJT_VRTX_CPC_CTRL_T                      vrtx_cpc_ctrl_o;	//0xF0221F5C
	PE_F20_ND0_OBC_OBJT_BLUR_HCOEF01_T                        blur_hcoef01_o;	//0xF0221F60
	PE_F20_ND0_OBC_OBJT_BLUR_HCOEF23_T                        blur_hcoef23_o;	//0xF0221F64
	PE_F20_ND0_OBC_OBJT_BLUR_HCOEF45_T                        blur_hcoef45_o;	//0xF0221F68
	PE_F20_ND0_OBC_OBJT_BLUR_HCOEF67_T                        blur_hcoef67_o;	//0xF0221F6C
	PE_F20_ND0_OBC_OBJT_BLUR_HCOEF8_T                          blur_hcoef8_o;	//0xF0221F70
	PE_F20_ND0_OBC_OBJT_BLUR_VCOEF01_T                        blur_vcoef01_o;	//0xF0221F74
	PE_F20_ND0_OBC_OBJT_BLUR_VCOEF23_T                        blur_vcoef23_o;	//0xF0221F78
	PE_F20_ND0_OBC_OBJT_BLUR_VCOEF4_T                          blur_vcoef4_o;	//0xF0221F7C
	PE_F20_ND0_OBC_OBJT_L5_GAIN_LUT1_T                        l5_gain_lut1_o;	//0xF0222000
	PE_F20_ND0_OBC_OBJT_L5_GAIN_LUT2_T                        l5_gain_lut2_o;	//0xF0222004
	PE_F20_ND0_OBC_OBJT_L0_GAIN_LUT1_T                        l0_gain_lut1_o;	//0xF0222008
	PE_F20_ND0_OBC_OBJT_L0_GAIN_LUT2_T                        l0_gain_lut2_o;	//0xF022200C
	PE_F20_ND0_OBC_OBJT_EDGE_WIN_H_T                            edge_win_h_o;	//0xF0222010
	PE_F20_ND0_OBC_OBJT_EDGE_WIN_V_T                            edge_win_v_o;	//0xF0222014
	PE_F20_ND0_OBC_OBJT_PSP_IIR1_T                                psp_iir1_o;	//0xF0222028
	PE_F20_ND0_OBC_OBJT_BG_MEASURE_CTRL_T                  bg_measure_ctrl_o;	//0xF022202C
	PE_F20_ND0_OBC_FACE_PSP_CTRL00_T                            psp_ctrl00_f;	//0xF0222100
	PE_F20_ND0_OBC_FACE_PSP_CTRL01_T                            psp_ctrl01_f;	//0xF0222104
	PE_F20_ND0_OBC_FACE_PSP_CTRL02_T                            psp_ctrl02_f;	//0xF0222108
	PE_F20_ND0_OBC_FACE_EDGE_TH_T                                  edge_th_f;	//0xF022210C
	PE_F20_ND0_OBC_FACE_FG_POSITION_T                          fg_position_f;	//0xF0222110
	PE_F20_ND0_OBC_FACE_RESERVED0_T                              reserved0_f;	//0xF0222114
	PE_F20_ND0_OBC_FACE_RESERVED1_T                              reserved1_f;	//0xF0222118
	PE_F20_ND0_OBC_FACE_RESERVED2_T                              reserved2_f;	//0xF022211C
	PE_F20_ND0_OBC_FACE_RESERVED3_T                              reserved3_f;	//0xF0222120
	PE_F20_ND0_OBC_FACE_RESERVED4_T                              reserved4_f;	//0xF0222124
	PE_F20_ND0_OBC_FACE_RESERVED5_T                              reserved5_f;	//0xF0222128
	PE_F20_ND0_OBC_FACE_RESERVED6_T                              reserved6_f;	//0xF022212C
	PE_F20_ND0_OBC_FACE_RESERVED7_T                              reserved7_f;	//0xF0222130
	PE_F20_ND0_OBC_FACE_PROB_MAP_T                                prob_map_f;	//0xF0222134
	PE_F20_ND0_OBC_FACE_ELLIPS_MAP_T                            ellips_map_f;	//0xF0222138
	PE_F20_ND0_OBC_FACE_PROB_DIFF_MAP_T                      prob_diff_map_f;	//0xF022213C
	PE_F20_ND0_OBC_FACE_OBJECT_MAP_T                            object_map_f;	//0xF0222140
	PE_F20_ND0_OBC_FACE_BLUR_MAP_T                                blur_map_f;	//0xF0222144
	PE_F20_ND0_OBC_FACE_PSP_IIR_T                                  psp_iir_f;	//0xF022214C
	PE_F20_ND0_OBC_FACE_PSP_GAIN_T                                psp_gain_f;	//0xF0222150
	PE_F20_ND0_OBC_FACE_VRTX_CPC_CTRL_T                      vrtx_cpc_ctrl_f;	//0xF022215C
	PE_F20_ND0_OBC_FACE_BLUR_HCOEF01_T                        blur_hcoef01_f;	//0xF0222160
	PE_F20_ND0_OBC_FACE_BLUR_HCOEF23_T                        blur_hcoef23_f;	//0xF0222164
	PE_F20_ND0_OBC_FACE_BLUR_HCOEF45_T                        blur_hcoef45_f;	//0xF0222168
	PE_F20_ND0_OBC_FACE_BLUR_HCOEF67_T                        blur_hcoef67_f;	//0xF022216C
	PE_F20_ND0_OBC_FACE_BLUR_HCOEF8_T                          blur_hcoef8_f;	//0xF0222170
	PE_F20_ND0_OBC_FACE_BLUR_VCOEF01_T                        blur_vcoef01_f;	//0xF0222174
	PE_F20_ND0_OBC_FACE_BLUR_VCOEF23_T                        blur_vcoef23_f;	//0xF0222178
	PE_F20_ND0_OBC_FACE_BLUR_VCOEF4_T                          blur_vcoef4_f;	//0xF022217C
	PE_F20_ND0_OBC_FACE_L5_GAIN_LUT1_T                        l5_gain_lut1_f;	//0xF0222200
	PE_F20_ND0_OBC_FACE_L5_GAIN_LUT2_T                        l5_gain_lut2_f;	//0xF0222204
	PE_F20_ND0_OBC_FACE_L0_GAIN_LUT1_T                        l0_gain_lut1_f;	//0xF0222208
	PE_F20_ND0_OBC_FACE_L0_GAIN_LUT2_T                        l0_gain_lut2_f;	//0xF022220C
	PE_F20_ND0_OBC_FACE_EDGE_WIN_H_T                            edge_win_h_f;	//0xF0222210
	PE_F20_ND0_OBC_FACE_EDGE_WIN_V_T                            edge_win_v_f;	//0xF0222214
	PE_F20_ND0_OBC_FACE_PSP_IIR1_T                                psp_iir1_f;	//0xF0222228
	PE_F20_ND0_OBC_FACE_BG_MEASURE_CTRL_T                  bg_measure_ctrl_f;	//0xF022222C
	PE_F20_ND0_OBC_FACE_FACE0_SET_T                              face0_set_f;	//0xF0222244
	PE_F20_ND0_OBC_FACE_FACE1_SET_T                              face1_set_f;	//0xF0222248
	PE_F20_ND0_OBC_FACE_FACE2_SET_T                              face2_set_f;	//0xF022224C
	PE_F20_ND0_OBC_FACE_FACE3_SET_T                              face3_set_f;	//0xF0222250
	PE_F20_ND0_OBC_FACE_ELLIPS0_SET_T                          ellips0_set_f;	//0xF0222254
	PE_F20_ND0_OBC_FACE_ELLIPS1_SET_T                          ellips1_set_f;	//0xF0222258
	PE_F20_ND0_OBC_FACE_ELLIPS2_SET_T                          ellips2_set_f;	//0xF022225C
	PE_F20_ND0_OBC_FACE_ELLIPS3_SET_T                          ellips3_set_f;	//0xF0222260
}PE_CHPI_DNR_PSP_TBL_F20_T;

typedef struct {
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_0_T                 reg_decon_ctrl_0;	//0xF036CD04
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_1_T                 reg_decon_ctrl_1;	//0xF036CD08
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_2_T                 reg_decon_ctrl_2;	//0xF036CD0C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_3_T                 reg_decon_ctrl_3;	//0xF036CD10
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_4_T                 reg_decon_ctrl_4;	//0xF036CD14
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_5_T                 reg_decon_ctrl_5;	//0xF036CD18
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_6_T                 reg_decon_ctrl_6;	//0xF036CD1C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_7_T                 reg_decon_ctrl_7;	//0xF036CD20
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_8_T                 reg_decon_ctrl_8;	//0xF036CD24
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_9_T                 reg_decon_ctrl_9;	//0xF036CD28
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_10_T               reg_decon_ctrl_10;	//0xF036CD2C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_11_T               reg_decon_ctrl_11;	//0xF036CD30
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_12_T               reg_decon_ctrl_12;	//0xF036CD34
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_13_T               reg_decon_ctrl_13;	//0xF036CD38
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_14_T               reg_decon_ctrl_14;	//0xF036CD3C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_15_T               reg_decon_ctrl_15;	//0xF036CD40
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_16_T               reg_decon_ctrl_16;	//0xF036CD44
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_17_T               reg_decon_ctrl_17;	//0xF036CD48
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_18_T               reg_decon_ctrl_18;	//0xF036CD4C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_19_T               reg_decon_ctrl_19;	//0xF036CD50
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_20_T               reg_decon_ctrl_20;	//0xF036CD54
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_21_T               reg_decon_ctrl_21;	//0xF036CD58
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_22_T               reg_decon_ctrl_22;	//0xF036CD5C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_23_T               reg_decon_ctrl_23;	//0xF036CD60
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_24_T               reg_decon_ctrl_24;	//0xF036CDBC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_25_T               reg_decon_ctrl_25;	//0xF036CDC0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_26_T               reg_decon_ctrl_26;	//0xF036CDC4
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_27_T               reg_decon_ctrl_27;	//0xF036CDC8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_28_T               reg_decon_ctrl_28;	//0xF036CDCC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_29_T               reg_decon_ctrl_29;	//0xF036CDD0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_30_T               reg_decon_ctrl_30;	//0xF036CDD4
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_31_T               reg_decon_ctrl_31;	//0xF036CDD8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_32_T               reg_decon_ctrl_32;	//0xF036CDDC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_33_T               reg_decon_ctrl_33;	//0xF036CDE0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_34_T               reg_decon_ctrl_34;	//0xF036CDE4
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_35_T               reg_decon_ctrl_35;	//0xF036CDE8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_36_T               reg_decon_ctrl_36;	//0xF036CDEC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_37_T               reg_decon_ctrl_37;	//0xF036CDF0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_38_T               reg_decon_ctrl_38;	//0xF036CDF4
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_39_T               reg_decon_ctrl_39;	//0xF036CDF8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_40_T               reg_decon_ctrl_40;	//0xF036CDFC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_41_T               reg_decon_ctrl_41;	//0xF036CE00
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_42_T               reg_decon_ctrl_42;	//0xF036CE04
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_43_T               reg_decon_ctrl_43;	//0xF036CE08
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_44_T               reg_decon_ctrl_44;	//0xF036CE0C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_45_T               reg_decon_ctrl_45;	//0xF036CE10
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_46_T               reg_decon_ctrl_46;	//0xF036CE14
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_47_T               reg_decon_ctrl_47;	//0xF036CE18
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_48_T               reg_decon_ctrl_48;	//0xF036CE1C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_49_T               reg_decon_ctrl_49;	//0xF036CE20
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_50_T               reg_decon_ctrl_50;	//0xF036CE24
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_51_T               reg_decon_ctrl_51;	//0xF036CE28
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_52_T               reg_decon_ctrl_52;	//0xF036CE2C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_53_T               reg_decon_ctrl_53;	//0xF036CE30
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_54_T               reg_decon_ctrl_54;	//0xF036CE34
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_55_T               reg_decon_ctrl_55;	//0xF036CE38
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_56_T               reg_decon_ctrl_56;	//0xF036CE3C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_57_T               reg_decon_ctrl_57;	//0xF036CE40
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_58_T               reg_decon_ctrl_58;	//0xF036CE44
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_59_T               reg_decon_ctrl_59;	//0xF036CE48
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_60_T               reg_decon_ctrl_60;	//0xF036CE4C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_61_T               reg_decon_ctrl_61;	//0xF036CE50
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_62_T               reg_decon_ctrl_62;	//0xF036CE54
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_63_T               reg_decon_ctrl_63;	//0xF036CE58
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_64_T               reg_decon_ctrl_64;	//0xF036CE5C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_65_T               reg_decon_ctrl_65;	//0xF036CE60
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_66_T               reg_decon_ctrl_66;	//0xF036CE64
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_67_T               reg_decon_ctrl_67;	//0xF036CE68
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_68_T               reg_decon_ctrl_68;	//0xF036CE6C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_69_T               reg_decon_ctrl_69;	//0xF036CE70
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_70_T               reg_decon_ctrl_70;	//0xF036CE74
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_71_T               reg_decon_ctrl_71;	//0xF036CE78
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_72_T               reg_decon_ctrl_72;	//0xF036CE7C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_73_T               reg_decon_ctrl_73;	//0xF036CE80
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_74_T               reg_decon_ctrl_74;	//0xF036CE84
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_75_T               reg_decon_ctrl_75;	//0xF036CE88
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_76_T               reg_decon_ctrl_76;	//0xF036CE8C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_77_T               reg_decon_ctrl_77;	//0xF036CE90
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_78_T               reg_decon_ctrl_78;	//0xF036CE94
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_79_T               reg_decon_ctrl_79;	//0xF036CE98
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_80_T               reg_decon_ctrl_80;	//0xF036CE9C
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_81_T               reg_decon_ctrl_81;	//0xF036CEA0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_82_T               reg_decon_ctrl_82;	//0xF036CEA4
	//PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_83_T               reg_decon_ctrl_83;	//0xF036CEA8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_84_T               reg_decon_ctrl_84;	//0xF036CEAC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_85_T               reg_decon_ctrl_85;	//0xF036CEB0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_86_T               reg_decon_ctrl_86;	//0xF036CEB4
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_87_T               reg_decon_ctrl_87;	//0xF036CEB8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_88_T               reg_decon_ctrl_88;	//0xF036CEBC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_89_T               reg_decon_ctrl_89;	//0xF036CEC0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_90_T               reg_decon_ctrl_90;	//0xF036CEC4
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_91_T               reg_decon_ctrl_91;	//0xF036CEC8
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_92_T               reg_decon_ctrl_92;	//0xF036CECC
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_93_T               reg_decon_ctrl_93;	//0xF036CED0
	PE_F20_LED_DECONTOUR_0_REG_DECON_CTRL_94_T               reg_decon_ctrl_94;	//0xF036CED4
}PE_CHPI_DNR_LED_TBL_F20_T;

//see PE_DDR_O20_DNR_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[15];
}PE_CHPI_DNR_SQM_F20_T;

//see PE_DDR_O20_DCNT_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[23];
}PE_CHPI_DNR_DCNT_SQM_F20_T;

//see PE_DDR_O20_DCNT_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[23];
}PE_CHPI_LED_DCNT_SQM_F20_T;

//see PE_DDR_O20_DNR_USER_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[8];
}PE_CHPI_DNR_USER_F20_T;

//see PE_DDR_O20_DCNT_USER_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[8];
}PE_CHPI_DNR_DCNT_USER_F20_T;

//see PE_DDR_O20_DCNT_LED_USER_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[8];
}PE_CHPI_LED_DCNT_USER_F20_T;
#endif
