#ifndef _PE_CHPI_DNR_TBL_O24F22A0_H_
#define _PE_CHPI_DNR_TBL_O24F22A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000594 RW 0x0000_0000
	UINT32 reg_dnr_max_enable               :1;	//(0,RW,0x1) //0 : bypass(or ifc result), 1 : dnr_mux
	UINT32 reg_ifc_max_enable               :1;	//(1,RW,0x00) //0 : dnr result, 1 : ifc_mux
	UINT32 reg_dnr_ifc_sel                  :1;	//(2,RW,0x00) //0 : dnr result, 1 : ifc result
	UINT32 reg_decon_max_sum_sel            :1;	//(3,RW,0x00) //0 : sum, 1 : max
	UINT32 reg_decon_ori_sel                :1;	//(4,RW,0x0) //0: original, 1: v_filter
	UINT32 reg_decon_max_enable             :1;	//(5,RW,0x1) //0: dnr only, 1: dnr+decon
	UINT32 reg_max_decon_dbg_en             :1;	//(6,RW,0x0) //
	UINT32 reg_half_rate_cg_n               :1;	//(7,RW,0x0) //0: cg_on, 1: cg_off
	UINT32 reg_max_dbg_en                   :1;	//(8,RW,0x00) //ac : black, dc : white, mnr : green
	UINT32 reg_dnr_motion_sel               :1;	//(9,RW,0x00) //0: 1:2:1 blurred motion 1: 5x5 blurred motion
	UINT32 reg_tnr_decon_en                 :1;	//(10,RW,0x0) //1: tnr_decon, 0: dnr_decon
	UINT32 reg_face_obj_sel                 :1;	//(11,RW,0x0) //0: dnr obc(4K?¥Ìïò, internal), 1: nd obc(4K Ï¥àÍ≥º(8K), external)
	UINT32 resvd0                           :4;
	UINT32 reg_win_en                       :1;	//(16,RW,0x00) //win control enable	   debug_enable should be '0'
	UINT32 reg_bdr_en                       :1;	//(17,RW,0x00) //border enable
	UINT32 reg_win_inout                    :1;	//(18,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_ipc_motion_en                :1;	//(21,RW,0x0) //hmc_flag ?Ä??=> 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl              :3;	//(24:22,RW,0x00) //0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th                 :7;	//(31:25,RW,0x0) //applied ifc when delta is greater than th
	};
	};
}PE_O24F22_DNR0_DNR_MAX_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000598 RW 0x0000_0000
	UINT32 reg_dbg_en                       :1;	//(0,RW,0x00) //debug bar en
	UINT32 reg_show_f3d                     :1;	//(1,RW,0x00) //
	UINT32 reg_show_bnr                     :1;	//(2,RW,0x00) //show debug bar for bnr	(acness,acness gain, dc_gain)
	UINT32 reg_f3d_mode                     :1;	//(3,RW,0x00) //
	UINT32 reg_acness_or_acness_gain        :1;	//(4,RW,0x00) //0 : acness (blue, green)	1 : acness gain (yellow, red)
	UINT32 resvd                            :27;
	};
	};
}PE_O24F22_DNR0_DNR_DBAR_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200059C RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_detect_level_th              :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O24F22_DNR0_REG_C420_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005A0 RW 0x0000_0000
	UINT32 reg_mnr_enable                   :1;	//(0,RW,0x0) //
	UINT32 reg_mnr_debug                    :1;	//(1,RW,0x00) //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//(2,RW,0x00) //
	UINT32 reg_mnr_chroma_en                :1;	//(3,RW,0x00) //
	UINT32 reg_h_expand                     :2;	//(5:4,RW,0x01) //0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//(7:6,RW,0x01) //0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//(15:8,RW,0xFF) //
	UINT32 reg_snr_th                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_th_max                       :8;	//(31:24,RW,0x20) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005A4 RW 0x0000_0000
	UINT32 reg_mmd_y_max                    :8;	//(7:0,RW,0xFF) //edge th, if(mmd > th) edge
	UINT32 reg_mmd_y_min                    :8;	//(15:8,RW,0x0) //reg_mnr_s2_ratio_min
	UINT32 reg_mmd_x_max                    :8;	//(23:16,RW,0x10) //reg_mnr_s2_ratio_max
	UINT32 reg_mmd_x_min                    :8;	//(31:24,RW,0x30) //reg_mnr_s2_mmd_min
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005A8 RW 0x0000_0000
	UINT32 reg_mnr_debug_mode               :4;	//(3:0,RW,0x00) //0: sel_mmd	1: final_sel_mmd	2: fil_diff_th_map	3: snr_rgn_flag	4: sel_mmd_gain	5: final_gain	6: pattern_flag	7: chroma_gain	8: dist_gain	9: prv mmd map	A: mmd var	B: MNR color gain	C: O24 New, final gain
	UINT32 reg_mnr_debug_en                 :1;	//(4,RW,0x00) //
	UINT32 resvd                            :19;
	UINT32 reg_equal_snr_th                 :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005AC RW 0x0000_0000
	UINT32 reg_blur_sel                     :1;	//(0,RW,0x00) //
	UINT32 reg_pattern_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_equal_th                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_scale                    :8;	//(31:24,RW,0x80) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005B0 RW 0x0000_0000
	UINT32 reg_mmd_fil_x_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_x_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_x_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_x_0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005B4 RW 0x0000_0000
	UINT32 reg_mmd_fil_y_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_y_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_y_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_y_0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005B8 RW 0x0404_0A40
	UINT32 reg_bnr_ac_detail_max            :8;	//(7:0,RW,0x40) //detail gain th
	UINT32 reg_bnr_ac_detail_min            :8;	//(15:8,RW,0xA) //detail gain th
	UINT32 reg_bnr_diff_l                   :8;	//(23:16,RW,0x4) //th used to find big diff point
	UINT32 reg_bnr_diff_p                   :8;	//(31:24,RW,0x4) //th used to find point of inflection
	};
	};
}PE_O24F22_DNR0_DETAIL_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005BC RW 0x0000_0000
	UINT32 reg_dc_bnr_enable                :1;	//(0,RW,0x0) //DC BNR enable	0 := off ( output debug mode )	1  = on
	UINT32 reg_dc_blur_debug_mode           :1;	//(1,RW,0x0) //0: blur, 1: white
	UINT32 reg_dc_blur_sel                  :2;	//(3:2,RW,0x1) //DC blur sel => 0 : 3x3, 1 : 5x5, 2 : 9x5
	UINT32 reg_dc_output_debug_mode         :4;	//(7:4,RW,0x0) //0: bypass	1: motion	2: motion gain	3: sum of variance	4: variance gain	5: edge protection map	6: DC gain without edge protection	7: DC gain with edge protection	8: chroma gain without edge protection	9: chroma gain with edge protection	10: fil_diff_th
	UINT32 reg_en_obj_amf_ctrl              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_obj_gain_mul                 :2;	//(14:13,RW,0x0) //
	UINT32 reg_obj_gain_en                  :1;	//(15,RW,0x0) //
	UINT32 reg_dc_motion_max                :8;	//(23:16,RW,0x30) //dc motion gain th
	UINT32 reg_dc_motion_min                :8;	//(31:24,RW,0x10) //dc motion gain th, if(reg_dc_motion_en == 0) reg_dc_motion_y_max = manual motion gain value
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005C0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_manual_fil_motion_gain       :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_chroma_en                :1;	//(16,RW,0x1) //
	UINT32 reg_fil_manual_en                :1;	//(17,RW,0x0) //
	UINT32 reg_dc_pattern_en                :1;	//(18,RW,0x0) //
	UINT32 reg_luma_gain_en                 :1;	//(19,RW,0x1) //
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x5) //0x5
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x2) //0x2
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x5) //0x5
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005C4 RW 0x0000_0000
	UINT32 reg_dc_var_en                    :1;	//(0,RW,0x0) //0x1
	UINT32 reg_dc_motion_en                 :1;	//(1,RW,0x0) //0x0
	UINT32 reg_dc_protection_en             :1;	//(2,RW,0x0) //0x1
	UINT32 resvd                            :7;
	UINT32 reg_dc_bnr_mastergain            :6;	//(15:10,RW,0x20) //0x20 is max.
	UINT32 reg_dc_bnr_chromagain            :8;	//(23:16,RW,0x20) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_dc_protection_th             :8;	//(31:24,RW,0xA) //
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005C8 RW 0x0000_0000
	UINT32 reg_dc_bnr_var_th3               :8;	//(7:0,RW,0x80) //dc variance gain th
	UINT32 reg_dc_bnr_var_th2               :8;	//(15:8,RW,0x40) //dc variance gain th
	UINT32 reg_dc_bnr_var_th1               :8;	//(23:16,RW,0x25) //dc variance gain th
	UINT32 reg_dc_bnr_var_th0               :8;	//(31:24,RW,0x15) //dc variance gain th, if(reg_dc_var_en == 0) reg_dc_var_y_th0 = manual variance gain value
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005CC RW 0x0000_0000
	UINT32 reg_dc_motion_y_min              :8;	//(7:0,RW,0x0) //motion gain yÏ∂?
	UINT32 reg_dc_motion_y_max              :8;	//(15:8,RW,0xFF) //motion gain yÏ∂?
	UINT32 resvd                            :16;
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005D0 RW 0x0000_0000
	UINT32 reg_dc_var_y_th0                 :8;	//(7:0,RW,0xFF) //variance gain yÏ∂?
	UINT32 reg_dc_var_y_th1                 :8;	//(15:8,RW,0x80) //variance gain yÏ∂?
	UINT32 reg_dc_var_y_th2                 :8;	//(23:16,RW,0x40) //variance gain yÏ∂?
	UINT32 reg_dc_var_y_th3                 :8;	//(31:24,RW,0x0) //variance gain yÏ∂?
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005D4 RW 0xB30B_0B4F
	UINT32 reg_bnr_ac_h_en                  :1;	//(0,RW,0x1) //
	UINT32 reg_bnr_ac_v_en                  :1;	//(1,RW,0x1) //
	UINT32 reg_bnr_ac_h_chroma_en           :1;	//(2,RW,0x1) //
	UINT32 reg_bnr_ac_v_chroma_en           :1;	//(3,RW,0x1) //
	UINT32 reg_bnr_ac_acness_resol_h        :2;	//(5:4,RW,0x0) //1: /2, 2: /4, 3:/ 8
	UINT32 reg_multi_run_mode               :1;	//(6,RW,0x0) //
	UINT32 reg_ac_bnr_gain_yc_sel           :1;	//(7,RW,0x0) //
	UINT32 reg_bnr_ac_diff_min_v_th         :8;	//(15:8,RW,0xB) //minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_diff_min_h_th         :8;	//(23:16,RW,0xB) //minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_iir_gain              :8;	//(31:24,RW,0xB3) //alpha value used in IIR
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005D8 RW 0x0F19_370B
	UINT32 reg_bnr_ac_global_motion_th      :8;	//(7:0,RW,0xB) //0x0B
	UINT32 reg_bnr_ac_h_acness_max          :8;	//(15:8,RW,0x37) //th for acness gain
	UINT32 reg_bnr_ac_h_acness_min          :8;	//(23:16,RW,0x19) //th for acness gain
	UINT32 reg_bnr_ac_bin_th                :8;	//(31:24,RW,0xF) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005DC RW 0x0A20_4060
	UINT32 reg_bnr_ac_motion_3              :8;	//(7:0,RW,0x60) //motion gain xÏ∂?
	UINT32 reg_bnr_ac_motion_2              :8;	//(15:8,RW,0x40) //motion gain xÏ∂?
	UINT32 reg_bnr_ac_motion_1              :8;	//(23:16,RW,0x20) //motion gain xÏ∂?
	UINT32 reg_bnr_ac_motion_0              :8;	//(31:24,RW,0xA) //motion gain xÏ∂?
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005E0 RO 0x0000_0000
	UINT32 c420_tearing_cnt                 :16;	//(15:0,RO,0x0) //
	UINT32 global_motion_iir                :8;	//(23:16,RO,0x0) //
	UINT32 global_dc_gain                   :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005E4 RW 0x3060_A0FF
	UINT32 reg_bnr_ac_motion_y_3            :8;	//(7:0,RW,0xFF) //motion gain yÏ∂?
	UINT32 reg_bnr_ac_motion_y_2            :8;	//(15:8,RW,0xA0) //motion gain yÏ∂?
	UINT32 reg_bnr_ac_motion_y_1            :8;	//(23:16,RW,0x60) //motion gain yÏ∂?
	UINT32 reg_bnr_ac_motion_y_0            :8;	//(31:24,RW,0x30) //motion gain yÏ∂?
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005E8 RW 0x1937_5000
	UINT32 reg_bnr_ac_v_init_offset         :3;	//(2:0,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_h_init_offset         :3;	//(5:3,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_acness_resol_v        :2;	//(7:6,RW,0x00) //0x0 is original, 0x3 : /8
	UINT32 reg_bnr_ac_debug_mode            :4;	//(11:8,RW,0x00) //debug mode 	0 : bypass	1 : block line map	2 : motion	3 : motion gain	4 : pos_gain_H	5 : pos_gain_V	6 : AC BNR gain_H	7 : AC BNR gain_V	8 : Binary map	9 : detail map	10: detail gain	11: fil_motion_th	12: filter level map	13: AC final gain_H	14: AC final gain_V
	UINT32 reg_bnr_ac_hsy_mode              :4;	//(15:12,RW,0x05) //stable init position mode
	UINT32 reg_bnr_ac_v_acness_max          :8;	//(23:16,RW,0x37) //
	UINT32 reg_bnr_ac_v_acness_min          :8;	//(31:24,RW,0x19) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005EC RO 0x0000_0000
	UINT32 acness_v_l                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_g                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005F0 RW 0xFA96_3201
	UINT32 reg_bnr_ac_detail_th4            :8;	//(7:0,RW,0x1) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th3            :8;	//(15:8,RW,0x32) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th2            :8;	//(23:16,RW,0x96) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th1            :8;	//(31:24,RW,0xFA) //detail th used in AC-BNR final mux
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005F4 RW 0x00FF_C0C0
	UINT32 reg_bnr_ac_pos_gain_h2           :8;	//(7:0,RW,0xC0) //SD : 0x40, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h1           :8;	//(15:8,RW,0xC0) //SD : 0x80, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h0           :8;	//(23:16,RW,0xFF) //SD : 0xFF, HD : 0xFF
	UINT32 reg_bnr_ac_detail_gain_th        :8;	//(31:24,RW,0x0) //0x00
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005F8 RW 0x80FF_8040
	UINT32 reg_bnr_ac_pos_gain_l2           :8;	//(7:0,RW,0x40) //SD : 0x40, HD : 0x40
	UINT32 reg_bnr_ac_pos_gain_l1           :8;	//(15:8,RW,0x80) //SD : 0x80, HD : 0x80
	UINT32 reg_bnr_ac_pos_gain_l0           :8;	//(23:16,RW,0xFF) //SD : 0x80, HD : 0xFF
	UINT32 reg_bnr_ac_pos_gain_h3           :8;	//(31:24,RW,0x80) //SD : 0x00, HD : 0x80
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20005FC RO 0x0000_0000
	UINT32 h_init                           :8;	//(7:0,RO,0x0) //
	UINT32 v_init                           :8;	//(15:8,RO,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_vfilter_tearing_cnt          :12;	//(31:20,RO,0x00) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000600 RW 0x0000_0E20
	UINT32 reg_ac_master_c_gain             :8;	//(7:0,RW,0x20) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_ac_bnr_enable                :1;	//(8,RW,0x00) //0 : debug mode, 1 : ac result
	UINT32 reg_ac_bnr_motion_en             :1;	//(9,RW,0x01) //1 : motion gain enable	0 : reg_bnr_ac_motion_y_max = manual motion gain value
	UINT32 reg_ac_bnr_acness_en             :1;	//(10,RW,0x01) //1 : acness gain enable	0 : reg_bnr_ac_acness_y_max = manual acness gain value
	UINT32 reg_ac_bnr_position_en           :1;	//(11,RW,0x01) //1 : position gain enable	0 : reg_bnr_ac_pos_gain_H0_7 = manual position gain value
	UINT32 reg_detail_sel                   :1;	//(12,RW,0x00) //0: old, 1: new
	UINT32 resvd                            :3;
	UINT32 reg_bnr_ac_manual_init_v         :3;	//(18:16,RW,0x00) //force the specific init position for debug
	UINT32 reg_ac_manual_init_en_v          :1;	//(19,RW,0x00) //0 : off, 1 : on
	UINT32 reg_bnr_ac_manual_init_h         :3;	//(22:20,RW,0x00) //force the specific init position for debug
	UINT32 reg_ac_manual_init_en_h          :1;	//(23,RW,0x00) //0 : off, 1 : on
	UINT32 reg_bnr_ac_pos_gain_l3           :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000604 RW 0x0009_8000
	UINT32 reg_acness_sel                   :1;	//(0,RW,0x00) //
	UINT32 reg_g_motion_manual_en           :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :6;
	UINT32 reg_ac_bnr_debug_h_en            :1;	//(8,RW,0x00) //
	UINT32 reg_ac_bnr_debug_v_en            :1;	//(9,RW,0x00) //
	UINT32 reg_ac_master_y_gain             :6;	//(15:10,RW,0x20) //0x20 is max
	UINT32 reg_g_motion_scale               :3;	//(18:16,RW,0x1) //
	UINT32 reg_g_motion_div                 :2;	//(20:19,RW,0x1) //
	UINT32 resvd1                           :10;
	UINT32 reg_ac_flt_level_sel             :1;	//(31,RW,0x1) //0 : weak, 1 : strong
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000608 RW 0xFF00_FF00
	UINT32 reg_ac_detail_gain_y_min         :8;	//(7:0,RW,0x0) //detail gain yÏ∂?
	UINT32 reg_ac_detail_gain_y_max         :8;	//(15:8,RW,0xFF) //detail gain yÏ∂?
	UINT32 reg_bnr_ac_acness_y_min          :8;	//(23:16,RW,0x0) //acness gain y  Ï∂?
	UINT32 reg_bnr_ac_acness_y_max          :8;	//(31:24,RW,0xFF) //acness gain y  Ï∂?
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200060C RW 0xFF00_FF00
	UINT32 reg_ac_detail_alpha2_y_min       :8;	//(7:0,RW,0x0) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	UINT32 reg_ac_detail_alpha2_y_max       :8;	//(15:8,RW,0xFF) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	UINT32 reg_ac_detail_alpha4_y_min       :8;	//(23:16,RW,0x0) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	UINT32 reg_ac_detail_alpha4_y_max       :8;	//(31:24,RW,0xFF) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000610 RW 0x0000_FFFF
	UINT32 reg_g_motion_manual              :8;	//(7:0,RW,0xFF) //
	UINT32 reg_acness_scale_mul             :8;	//(15:8,RW,0xFF) //
	UINT32 reg_bnr_ac_detail_max            :8;	//(23:16,RW,0x0) //
	UINT32 reg_bnr_ac_detail_min            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000614 RW 0x00E8_D800
	UINT32 reg_y_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_y_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_y_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|Î°?[7:0] ?†ÌÉù	1: |y''|/4Î°?[9:2] ?†ÌÉù
	UINT32 resvd1                           :1;
	UINT32 reg_y_drvt2_hcoef_sel            :3;	//(10:8,RW,0x00) //5tap, h[0, 0, 8, 8, 0, -8, -8, -0, -0]/16	7tap, h[0, 4, 6, 6, 0, -6, -6, -4, -0]/16	9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_medge_meth                   :1;	//(11,RW,0x01) //0: 13x3 window (???ºÏù∏?¥Îùº???¥Îãπ?òÎ©¥ Î™®Îëê ?âÏπ†)	1 :13x3 window (?©ÏùÑ Íµ¨Ìï¥??coring)
	UINT32 reg_medge_th                     :8;	//(19:12,RW,0x8D) //diff??th
	UINT32 reg_medge_coring_th              :8;	//(27:20,RW,0xE) //?íÏù¥??th
	UINT32 reg_medge_ch_tap                 :2;	//(29:28,RW,0x00) //0: 13tap	1: 11tap	2: 9tap
	UINT32 reg_edge_meth                    :2;	//(31:30,RW,0x00) //diff??center?¨Ìï® on/off
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000618 RW 0x0C00_3820
	UINT32 reg_edge_ddrvt_gain_y1           :8;	//(7:0,RW,0x20) //
	UINT32 reg_edge_ddrvt_gain_x1           :8;	//(15:8,RW,0x38) //
	UINT32 reg_edge_ddrvt_gain_y0           :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_ddrvt_gain_x0           :8;	//(31:24,RW,0xC) //?êÎûò y edge gain
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200061C RW 0x0000_0000
	UINT32 reg_c_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_c_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_c_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|Î°?[7:0] ?†ÌÉù	1: |y''|/4Î°?[9:2] ?†ÌÉù
	UINT32 resvd1                           :25;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000620 RW 0x1100_6E20
	UINT32 reg_c_edge_gain_y1               :8;	//(7:0,RW,0x20) //
	UINT32 reg_c_edge_gain_x1               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_c_edge_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_c_edge_gain_x0               :8;	//(31:24,RW,0x11) //
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000624 RW 0x0003_1203
	UINT32 reg_crs_para_tap                 :2;	//(1:0,RW,0x03) //0 : 5tap, h[0, 1, 1, 1, 1 ,1]	1 : 4tap, h[0, 0, 1, 1, 1, 1]	2 : 4tap, h[0, 1, 1, 1, 1, 0]	3 : 6tap, h[1, 1, 1, 1, 1, 1]
	UINT32 reg_cdst_th                      :10;	//(11:2,RW,0x080) //Cb, Cr Ï∞®Ïù¥Í∞Ä ??Í∞??¥ÏÉÅ?¥Ïñ¥???†Ìö®
	UINT32 reg_crs_op_tap                   :2;	//(13:12,RW,0x01) //0 : 9 tap	1 : 7 tap	2 : 5 tap
	UINT32 reg_crs_gain_res                 :1;	//(14,RW,0x00) //0: |c diff|Î°?[7:0] ?†ÌÉù	1: |c diff|/4Î°?[9:2] ?†ÌÉù
	UINT32 resvd0                           :1;
	UINT32 reg_cdiff_hcoef_sel              :2;	//(17:16,RW,0x03) //left/right diff??coefficient (Ï¥??©Ï? 255)	0 : h[0x00, 0x08, 0x08, 0x0A, 0x1E, 0xC8]/256	1 : h[0x00, 0x10, 0x10, 0x14, 0x40, 0x8C]/256
	UINT32 resvd1                           :10;
	UINT32 reg_crs_point                    :2;	//(29:28,RW,0x00) //
	UINT32 reg_crs_meth                     :2;	//(31:30,RW,0x00) //0 : (1Ï°∞Í±¥) +  L/R Í∞ÅÍ∞Å ?¥Î? Î∂Ä?∏ÍπåÏßÄ Í∞ôÏ?Í∞Ä	1 : (2Ï°∞Í±¥) +  L/R ?úÎ°ú Î∂Ä?∏ÎèÑ Î∞òÎ??∏Í? 	2 : L/RÎ™®Îëê chroma diffÍ∞Ä thresholdÎ≥¥Îã§ ?∞Í?
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000628 RW 0x0000_6616
	UINT32 reg_crs_gain_y1                  :8;	//(7:0,RW,0x16) //
	UINT32 reg_crs_gain_x1                  :8;	//(15:8,RW,0x66) //
	UINT32 reg_crs_gain_y0                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200062C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000630 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000634 RW 0x2400_0000
	UINT32 reg_ifc_en                       :1;	//(0,RW,0x00) //0 : 0ff / 1 : on
	UINT32 reg_clp_on                       :1;	//(1,RW,0x00) //0 : 0ff / 1 : Max clipping
	UINT32 resvd0                           :2;
	UINT32 reg_edge_en                      :1;	//(4,RW,0x00) //mmd en
	UINT32 resvd1                           :15;
	UINT32 reg_clp_tap                      :2;	//(21:20,RW,0x00) //0 : 13 tap	1 : 11 tap	2 : 9tap
	UINT32 reg_ifc_flt_sel                  :2;	//(23:22,RW,0x00) //3 : cross	2 : multi edge cedge	1 : yedge	0 : default
	UINT32 reg_debug_en                     :2;	//(25:24,RW,0x00) //0 : debug off	1 : blend debug on	2 : debug on
	UINT32 reg_debug_mode                   :4;	//(29:26,RW,0x09) //0 : operation mode	1 : cross check	2 : multi edge	3 : 	4 : cr edge gain	5 : cb edge gain	6 : y edge gain	7 : cross gain	8 : cross blend	9 : multi-edge blend	10 : 	11 : 2Ï∞®Î?Î∂?12 : 	13 : 1Ï∞®Î?Î∂?
	UINT32 reg_bld_tap                      :2;	//(31:30,RW,0x00) //0: ?ÜÏóê 2Í∞?average	1: ?ÜÏóê 1Í∞? center average
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000638 RW 0x0000_0000
	UINT32 reg_f0_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f0_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f0_h1_pos                    :13;	//(30:18,RW,0x0) //
	UINT32 resvd                            :1;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200063C RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :13;	//(12:0,RW,0x0) //
	UINT32 reg_f0_h2_pos                    :13;	//(25:13,RW,0x0) //
	UINT32 resvd                            :6;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000640 RW 0x0000_0000
	UINT32 reg_f1_h1_pos                    :13;	//(12:0,RW,0x0) //
	UINT32 reg_f0_w2_pos                    :13;	//(25:13,RW,0x0) //
	UINT32 resvd                            :6;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000644 RW 0x8004_0000
	UINT32 resvd                            :16;
	UINT32 reg_crs_zero_th                  :8;	//(23:16,RW,0x4) //cross point?êÏÑú cb-cr??0?ºÎ°ú Î≥¥Îäî ?ÅÌïúÍ∞?
	UINT32 reg_dst_cdst_th                  :8;	//(31:24,RW,0x80) //Ï¢åÏö∞ ?ÑÌÑ∞Í≥±Ìï¥Ïß?cdst ?©Ïùò Ï∞®Ïù¥
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000648 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200064C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000650 RW 0x0640_11FF
	UINT32 reg_medge_gain_y1                :8;	//(7:0,RW,0xFF) //
	UINT32 reg_medge_gain_x1                :8;	//(15:8,RW,0x11) //
	UINT32 reg_medge_gain_y0                :8;	//(23:16,RW,0x40) //
	UINT32 reg_medge_gain_x0                :8;	//(31:24,RW,0x6) //1/3Î°?
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000654 RW 0x0010_02A2
	UINT32 reg_crs_op_gain_isel             :2;	//(1:0,RW,0x02) //0 : max	1 : min	2 : average
	UINT32 reg_crs_op_gain_res              :1;	//(2,RW,0x00) //0: [7:0] ?†ÌÉù	1: [9:2] ?†ÌÉù
	UINT32 reg_crs_cdst_flt                 :3;	//(5:3,RW,0x04) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd0                           :1;
	UINT32 reg_crs_cdst_vmdn                :1;	//(7,RW,0x01) //5x5 median/max (v->h)
	UINT32 reg_crs_cdst_op_flt              :3;	//(10:8,RW,0x02) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd1                           :5;
	UINT32 reg_op_wgain_coef1               :2;	//(17:16,RW,0x00) //cross filter??Í≤ΩÏö∞,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef2               :2;	//(19:18,RW,0x00) //cross filter??Í≤ΩÏö∞,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef3               :2;	//(21:20,RW,0x01) //cross filter??Í≤ΩÏö∞,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 resvd2                           :10;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000658 RW 0x8500_DCFF
	UINT32 reg_crs_op_gain_y1               :8;	//(7:0,RW,0xFF) //
	UINT32 reg_crs_op_gain_x1               :8;	//(15:8,RW,0xDC) //
	UINT32 reg_crs_op_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_op_gain_x0               :8;	//(31:24,RW,0x85) //
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200065C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000660 RW 0x2100_0000
	UINT32 resvd0                           :16;
	UINT32 reg_medge_op_th                  :8;	//(23:16,RW,0x0) //Î©Ä?∞Ïó£ÏßÄ ?ÅÏó≠ ?°ÎäîÍ≤?(3?ºÏù∏, Í∞?àò??
	UINT32 reg_mmd_gain_en                  :1;	//(24,RW,0x01) //
	UINT32 reg_mmd_gain_flt                 :2;	//(26:25,RW,0x00) //0: off	1: ?ÖÎ†•??21
	UINT32 reg_mmd_gain_tap                 :2;	//(28:27,RW,0x00) //0: 13	1: 11	2: 9
	UINT32 reg_mmd_gain_res                 :1;	//(29,RW,0x01) //0: [7:0] ?†ÌÉù	1: [9:2] ?†ÌÉù
	UINT32 resvd1                           :2;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000664 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000668 RW 0x0080_B000
	UINT32 reg_mmd_gain_y1                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_gain_x1                  :8;	//(15:8,RW,0xB0) //
	UINT32 reg_mmd_gain_y0                  :8;	//(23:16,RW,0x80) //
	UINT32 reg_mmd_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_IFC_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200066C RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :13;	//(12:0,RW,0x0) //
	UINT32 reg_f1_h2_pos                    :13;	//(25:13,RW,0x0) //
	UINT32 resvd                            :6;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000670 RW 0x0000_0000
	UINT32 reg_f1_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f1_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f1_w2_pos                    :13;	//(30:18,RW,0x0) //
	UINT32 resvd                            :1;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000674 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_SC_BNR_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000678 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_SC_BNR_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200067C RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_SC_BNR_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000680 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_SC_BNR_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000684 RW 0x0000_0100
	UINT32 reg_f2_h2_pos                    :13;	//(12:0,RW,0x0) //
	UINT32 reg_f2_h1_pos                    :13;	//(25:13,RW,0x0) //
	UINT32 resvd                            :6;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000688 RW 0x0000_0000
	UINT32 pre_121_blur_en                  :1;	//(0,RW,0x00) //
	UINT32 pre_median_en                    :1;	//(1,RW,0x00) //
	UINT32 resvd                            :30;
	};
	};
}PE_O24F22_DNR0_C_PRE_BLUR_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200068C RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :13;	//(12:0,RW,0x0) //
	UINT32 reg_f2_w1_pos                    :13;	//(25:13,RW,0x0) //
	UINT32 resvd                            :6;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000690 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f2_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h1_pos                    :13;	//(30:18,RW,0x0) //
	UINT32 resvd                            :1;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000694 RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :13;	//(12:0,RW,0x0) //
	UINT32 reg_f3_w1_pos                    :13;	//(25:13,RW,0x0) //
	UINT32 resvd                            :6;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000698 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f3_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h2_pos                    :13;	//(30:18,RW,0x0) //
	UINT32 resvd                            :1;
	};
	};
}PE_O24F22_DNR0_ELLIPSE_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200069C RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_h_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_h_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_h                :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006A0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_v_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_v_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_v                :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006A4 RW 0x4030_2010
	UINT32 reg_fil_motion_x_th0             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th1             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th2             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th3             :8;	//(31:24,RW,0x40) //
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006A8 RW 0xFF60_4020
	UINT32 reg_fil_motion_y_th0             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th1             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th2             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th3             :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_DNR0_DC_BNR_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006AC RW 0x3020_1001
	UINT32 reg_mmd_sel                      :2;	//(1:0,RW,0x01) //0: mmd_tnr, 1: mmd_mnr, 2: texture, 3: detail
	UINT32 resvd                            :6;
	UINT32 reg_hist_bin_th0                 :8;	//(15:8,RW,0x10) //
	UINT32 reg_hist_bin_th1                 :8;	//(23:16,RW,0x20) //
	UINT32 reg_hist_bin_th2                 :8;	//(31:24,RW,0x30) //
	};
	};
}PE_O24F22_DNR0_SQM_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006B0 RW 0x7060_5040
	UINT32 reg_hist_bin_th3                 :8;	//(7:0,RW,0x40) //
	UINT32 reg_hist_bin_th4                 :8;	//(15:8,RW,0x50) //
	UINT32 reg_hist_bin_th5                 :8;	//(23:16,RW,0x60) //
	UINT32 reg_hist_bin_th6                 :8;	//(31:24,RW,0x70) //
	};
	};
}PE_O24F22_DNR0_SQM_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006B4 RW 0x0461_E046
	UINT32 reg_trans_mmd_th                 :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_edge_a_th                    :10;	//(19:10,RW,0x0) //
	UINT32 reg_edf_mmd_th                   :8;	//(27:20,RW,0x0) //
	UINT32 resvd1                           :4;
	};
	};
}PE_O24F22_DNR0_SQM_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006B8 RW 0x0000_0000
	UINT32 reg_sqm_win_mode_x1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_x0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_sqm_win_mode_mode            :1;	//(30,RW,0x00) //
	UINT32 reg_sqm_win_mode_en              :1;	//(31,RW,0x00) //
	};
	};
}PE_O24F22_DNR0_SQM_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006BC RW 0x0000_0000
	UINT32 reg_sqm_win_mode_y1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_y0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O24F22_DNR0_SQM_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006C0 RW 0x0000_0080
	UINT32 reg_tp_binary_th                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
	};
}PE_O24F22_DNR0_TPD_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006C4 RW 0x0000_0000
	UINT32 reg_win_mode_x1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_x0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_win_mode_mode                :1;	//(30,RW,0x00) //0: inside, 1: outside
	UINT32 reg_win_mode_en                  :1;	//(31,RW,0x00) //
	};
	};
}PE_O24F22_DNR0_WINDOW_MODE_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006C8 RW 0x0000_0000
	UINT32 reg_win_mode_y1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_y0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O24F22_DNR0_WINDOW_MODE_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006D0 RO 0x0000_0000
	UINT32 acness_v_g                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v                         :8;	//(23:16,RO,0x0) //
	UINT32 acness_h                         :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006D4 RO 0x0000_0000
	UINT32 bad_up_cnt                       :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :4;
	UINT32 acness_v_l                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006D8 RO 0x0000_0000
	UINT32 acness_gain_v_l                  :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h_l                  :8;	//(15:8,RO,0x0) //
	UINT32 acness_gain_v_g                  :8;	//(23:16,RO,0x0) //
	UINT32 acness_gain_h_g                  :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006DC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_DNR_STAT_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006E0 RO 0x0000_0000
	UINT32 acness_gain_v                    :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h                    :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_iir                     :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_iir                     :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006E4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_DNR_STAT_8_SC_BNR0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006E8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_DNR_STAT_9_SC_BNR1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006EC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_DNR_STAT_10_SC_BNR2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006F0 RO 0x0000_0000
	UINT32 e_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_0                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_11_SQM_00_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006F4 RO 0x0000_0000
	UINT32 e_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_2                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_12_SQM_01_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006F8 RO 0x0000_0000
	UINT32 e_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_4                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_13_SQM_02_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20006FC RO 0x0000_0000
	UINT32 e_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_6                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_14_SQM_03_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000700 RO 0x0000_0000
	UINT32 f_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_0                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_15_SQM_04_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000704 RO 0x0000_0000
	UINT32 f_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_2                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_16_SQM_05_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000708 RO 0x0000_0000
	UINT32 f_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_4                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_17_SQM_06_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200070C RO 0x0000_0000
	UINT32 f_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_6                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_18_SQM_07_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000710 RO 0x0000_0000
	UINT32 t_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_0                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_19_SQM_08_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000714 RO 0x0000_0000
	UINT32 t_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_2                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_20_SQM_09_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000718 RO 0x0000_0000
	UINT32 t_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_4                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_21_SQM_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200071C RO 0x0000_0000
	UINT32 t_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_6                         :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_22_SQM_11_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000720 RO 0x0000_0000
	UINT32 res_h_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_23_TPD_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000724 RO 0x0000_0000
	UINT32 res_v_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_v_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_24_TPD_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000728 RO 0x0000_0000
	UINT32 res_v_cnt_3                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_3                      :16;	//(31:16,RO,0x0) //
	};
	};
}PE_O24F22_DNR0_DNR_STAT_25_TPD_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000730 RW 0x40302010
	UINT32 reg_fil_motion_x_th3             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th2             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th1             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th0             :8;	//(31:24,RW,0x40) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_15_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000734 RW 0xFF604020
	UINT32 reg_fil_motion_y_th3             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th2             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th1             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th0             :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_DNR0_AC_BNR_16_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000738 RW 0x0000_0000
	UINT32 reg_tearing_y_1                  :4;	//(3:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_tearing_y_0                  :4;	//(11:8,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_tearing_x_1                  :4;	//(19:16,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_tearing_x_0                  :4;	//(27:24,RW,0x0) //
	UINT32 resvd3                           :4;
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200073C RW 0x0000_0000
	UINT32 reg_motion_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_x_0                   :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000740 RW 0x0000_0000
	UINT32 reg_motion_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_y_0                   :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000744 RW 0x0000_0000
	UINT32 reg_global_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_x_0                   :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000748 RW 0x0000_0000
	UINT32 reg_global_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_y_0                   :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200074C RW 0x0000_0000
	UINT32 reg_blend_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_x_0                    :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000750 RW 0x0000_0000
	UINT32 reg_blend_y_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_y_0                    :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000754 RW 0x0000_0000
	UINT32 reg_hmc_x_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_x_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_x_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_x_0                      :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000758 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_y_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_y_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_y_0                      :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200075C RW 0x0000_0000
	UINT32 reg_local_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_x_0                    :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000760 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_y_0                    :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_VFILTER_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000764 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_master_bypass_en             :1;	//(1,RW,0x0) //
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //not used in O24
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align ??ÎßûÏùå)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //not used in O24
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000768 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200076C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000770 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000774 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x13579753) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000778 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x24680864) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200077C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x14703692) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000780 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x6) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0xFF) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000784 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x3) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000788 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200078C RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000790 RW 0x0000_0000
	UINT32 reg_gain_x3                      :8;	//(7:0,RW,255) //
	UINT32 reg_gain_x2                      :8;	//(15:8,RW,176) //
	UINT32 reg_gain_x1                      :8;	//(23:16,RW,170) //
	UINT32 reg_gain_x0                      :8;	//(31:24,RW,50) //
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000794 RW 0x0000_0000
	UINT32 reg_gain_x7                      :8;	//(7:0,RW,255) //
	UINT32 reg_gain_x6                      :8;	//(15:8,RW,255) //
	UINT32 reg_gain_x5                      :8;	//(23:16,RW,255) //
	UINT32 reg_gain_x4                      :8;	//(31:24,RW,255) //
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000798 RW 0x0000_0000
	UINT32 reg_gain_y3                      :8;	//(7:0,RW,64) //
	UINT32 reg_gain_y2                      :8;	//(15:8,RW,72) //
	UINT32 reg_gain_y1                      :8;	//(23:16,RW,200) //
	UINT32 reg_gain_y0                      :8;	//(31:24,RW,255) //
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200079C RW 0x0000_0000
	UINT32 reg_gain_y7                      :8;	//(7:0,RW,64) //
	UINT32 reg_gain_y6                      :8;	//(15:8,RW,64) //
	UINT32 reg_gain_y5                      :8;	//(23:16,RW,64) //
	UINT32 reg_gain_y4                      :8;	//(31:24,RW,64) //
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_11_T;
#if 0
typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007A0 RW 0x0000_0000
	UINT32 reg_lti_en                       :1;	//(0,RW,0x0) //
	UINT32 reg_lti_clipping_mode            :1;	//(1,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap                      :2;	//(4:3,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_lti_gain                     :8;	//(15:8,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_ycm_c_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_ycm_y_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_ycm_band_sel                 :3;	//(30:28,RW,0x0) //
	UINT32 reg_ycm_en                       :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_CTI_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007A4 RW 0x0000_0000
	UINT32 reg_lti_coring_th0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lti_coring_th1               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lti_coring_sm                :3;	//(18:16,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap2                     :2;	//(21:20,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ycm_diff_th                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_CTI_CTRL_3_T;
#endif
typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007A8 RW 0x0000_0000
	UINT32 reg_small_mmd_flat_th            :8;	//(7:0,NA,0x10) //
	UINT32 reg_large_mmd_flat_th            :8;	//(15:8,NA,0x20) //
	UINT32 resvd                            :12;
	UINT32 reg_mmd_chroma_gain_en           :1;	//(28,NA,0x1) //
	UINT32 reg_mmd_dist_kernal_width        :2;	//(30:29,NA,0x2) //
	UINT32 reg_mmd_dist_gain_en             :1;	//(31,NA,0x1) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007AC RW 0x0000_0000
	UINT32 reg_dist_gain_x3                 :8;	//(7:0,NA,0x8) //
	UINT32 reg_dist_gain_x2                 :8;	//(15:8,NA,0x4) //
	UINT32 reg_dist_gain_x1                 :8;	//(23:16,NA,0x2) //
	UINT32 reg_dist_gain_x0                 :8;	//(31:24,NA,0x1) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007B0 RW 0x0000_0000
	UINT32 reg_dist_gain_y3                 :8;	//(7:0,NA,0xC0) //
	UINT32 reg_dist_gain_y2                 :8;	//(15:8,NA,0xD0) //
	UINT32 reg_dist_gain_y1                 :8;	//(23:16,NA,0xE0) //
	UINT32 reg_dist_gain_y0                 :8;	//(31:24,NA,0xFF) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007B4 RW 0x0000_0000
	UINT32 reg_chroma_gain_x3               :8;	//(7:0,NA,40) //
	UINT32 reg_chroma_gain_x2               :8;	//(15:8,NA,20) //
	UINT32 reg_chroma_gain_x1               :8;	//(23:16,NA,10) //
	UINT32 reg_chroma_gain_x0               :8;	//(31:24,NA,5) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007B8 RW 0x0000_0000
	UINT32 reg_chroma_gain_y3               :8;	//(7:0,NA,0x80) //
	UINT32 reg_chroma_gain_y2               :8;	//(15:8,NA,0xA0) //
	UINT32 reg_chroma_gain_y1               :8;	//(23:16,NA,0xC0) //
	UINT32 reg_chroma_gain_y0               :8;	//(31:24,NA,0xFF) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007BC RW 0x0000_0000
	UINT32 reg_i_sel_mmd_x3                 :8;	//(7:0,NA,255) //
	UINT32 reg_i_sel_mmd_x2                 :8;	//(15:8,NA,90) //
	UINT32 reg_i_sel_mmd_x1                 :8;	//(23:16,NA,80) //
	UINT32 reg_i_sel_mmd_x0                 :8;	//(31:24,NA,50) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007C0 RW 0x0000_0000
	UINT32 reg_i_sel_mmd_y3                 :8;	//(7:0,NA,255) //
	UINT32 reg_i_sel_mmd_y2                 :8;	//(15:8,NA,200) //
	UINT32 reg_i_sel_mmd_y1                 :8;	//(23:16,NA,200) //
	UINT32 reg_i_sel_mmd_y0                 :8;	//(31:24,NA,0) //
	};
	};
}PE_O24F22_DNR0_REG_MNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007C4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x13579753) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007C8 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x24680864) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007CC RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x14703692) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007DC RW 0x0000_0000
	UINT32 resvd0                           :14;
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 resvd1                           :8;
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode?êÏÑú 10b ?ÖÎ†•?? ÏºúÏïº ??
	UINT32 resvd2                           :1;
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :5;	//(30:26,RW,0x0) //0: final_gain	1: variance_gain	2: variance - dc frame input	3: variance - original var	4: variance - blur dc map	5: variance - blend dc map	6: variance - final dc map	7: rmmd - l0 mmd	8: rmmd - l0 luma	9: rmmd - refine	A : rmmd - final gain	B: blur map - mmd input luma	C: blur map - mmd gain	D: blur map output	E: PAI	F: RRD	10: diff gain	11: luma gain	12: sel_diff	13: motion shift	14: motion gain	15: skin gain	16: face gain	17: face-skin gain	18: aux luma gain
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x1) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007E0 RW 0x0000_0000
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x1) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x1) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x1) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x5) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20
	UINT32 resvd1                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 resvd2                           :1;
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x5) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x2) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x3) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007E4 RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x7) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0xA) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0xF) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x19) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007E8 RW 0x0020_80FF
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0xFF) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x80) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x20) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007EC RW 0x00C0_783C
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x1E) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0xC) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007F0 RW 0x0804_0080
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x80) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007F4 RW 0x0200_003C
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x20) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_23_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007F8 RW 0x0643_212C
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x12C) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0xC8) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x64) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20007FC RW 0x190C_8384
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x384) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x320) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x190) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000800 RW 0x3E84_0100
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x3E8) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000804 RW 0x1004_0100
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000808 RW 0x1004_0100
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200080C RW 0x0000_0000
	UINT32 reg_block_size_v                 :8;	//(7:0,RW,0x0) //L6 block info
	UINT32 reg_block_size_h                 :8;	//(15:8,RW,0x0) //L6 block info
	UINT32 reg_block_no_v                   :6;	//(21:16,RW,0x0) //L6 block info
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,RW,0x0) //L6 block info
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,RW,0x0) //L6 block info
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000810 RW 0x8201_0000
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
	UINT32 resvd2                           :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000814 RW 0xFF60_0000
	UINT32 reg_120x68_block_no_v            :7;	//(6:0,RW,0x0) //L5 block info
	UINT32 resvd                            :17;
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000818 RW 0x0000_0000
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
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_32_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200081C RW 0x0000_0000
	UINT32 reg_120x68_last_block_size_v     :7;	//(6:0,RW,0x0) //L5 block info
	UINT32 reg_120x68_last_block_size_h     :7;	//(13:7,RW,0x0) //L5 block info
	UINT32 reg_120x68_block_size_v          :7;	//(20:14,RW,0x0) //L5 block info
	UINT32 reg_120x68_block_size_h          :7;	//(27:21,RW,0x0) //L5 block info
	UINT32 resvd                            :4;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_33_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000820 RW 0x0284_B200
	UINT32 reg_l6_var_y_th3                 :10;	//(9:0,RW,0x200) //revived in O20
	UINT32 reg_l6_var_y_th2                 :10;	//(19:10,RW,0x12C) //revived in O20
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x0) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x2) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x2) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x0) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_34_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000824 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_35_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000828 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_36_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200082C RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_37_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000830 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_38_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000834 RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_120x68_block_no_h            :7;	//(30:24,RW,0x0) //
	UINT32 reg_120x68_block_info_force_en   :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_39_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000838 RW 0x0000_0000
	UINT32 reg_dnr0_col_init_next_addr      :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_dnr0_col_init_prev_addr      :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_dnr0_col_init_force_en       :1;	//(31,RW,0x0) //?µÏã† Î™®Îìà Î©îÎ™®Î¶?initial addr
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_40_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200083C RW 0x0000_0000
	UINT32 reg_dnr1_col_init_next_addr      :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_dnr1_col_init_prev_addr      :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_dnr1_col_init_force_en       :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_41_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000840 RW 0x0000_0000
	UINT32 reg_dnr2_col_init_next_addr      :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_dnr2_col_init_prev_addr      :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_dnr2_col_init_force_en       :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_42_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000844 RW 0x0000_0000
	UINT32 reg_dnr3_col_init_next_addr      :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_dnr3_col_init_prev_addr      :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_dnr3_col_init_force_en       :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_43_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000848 RW 0x3264_C8FA
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0xFA) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0xC8) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x32) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_44_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200084C RW 0xFF64_1400
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x14) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_45_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000850 RW 0x3003_1040
	UINT32 reg_bbd_y0                       :13;	//(12:0,RW,0x40) //
	UINT32 reg_bbd_x0                       :13;	//(25:13,RW,0x31) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x1) //
	UINT32 reg_blur2_sim_en                 :1;	//(29,RW,0x1) //
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_46_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000854 RW 0x4871_B399
	UINT32 reg_bbd_y1                       :13;	//(12:0,RW,0x399) //
	UINT32 reg_bbd_x1                       :13;	//(25:13,RW,0x71B) //
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x2) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x2) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_47_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000858 RW 0x0A50_6478
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x78) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x64) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x50) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0xA) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_48_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200085C RW 0xFF32_0A01
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x1) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0xA) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x32) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_49_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000860 RW 0x143C_6EC8
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x14) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_50_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000864 RW 0x5064_788C
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x8C) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x78) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x50) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_51_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000868 RW 0x7882_B4C8
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x82) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x78) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_52_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200086C RW 0x00C8_C800
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0xC8) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_53_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000870 RW 0x0064_C8FA
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0xFA) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_54_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000874 RW 0x0032_C8FF
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0xFF) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x32) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_55_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000878 RW 0x8FF0_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0xFF) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x1) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_56_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200087C RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_aux_luma_en                  :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_57_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000880 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_58_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000884 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_59_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000888 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_60_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200088C RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_61_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000890 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(9:0,RW,0x0) //
	UINT32 resvd                            :22;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_62_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000894 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_63_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000898 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200089C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DC_BNR_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008A8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_64_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008AC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_65_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008B0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_66_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008B4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_67_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_68_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008BC RW 0x0000_0000
	UINT32 reg_var_lowapl_lut_x2            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x1            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x0            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_69_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008C0 RW 0x0000_0000
	UINT32 reg_var_lowapl_lut_y1            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y0            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x3            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_70_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008C4 RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_x0          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y3            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y2            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_71_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008C8 RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_x3          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x2          :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x1          :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_72_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008CC RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_y3          :8;	//(7:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y2          :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y1          :8;	//(23:16,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y0          :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_73_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008D0 RW 0x0000_0000
	UINT32 reg_lowapl_master_blend          :8;	//(7:0,RW,0x0) //
	UINT32 reg_2x2_var_msb_sel              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :23;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_74_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008D4 RW 0x0000_0000
	UINT32 reg_ellipse_offset               :8;	//(7:0,RW,0x0) //
	UINT32 reg_ellipse_master               :8;	//(15:8,RW,0x0) //
	UINT32 resvd                            :11;
	UINT32 reg_sel_output                   :1;	//(27,RW,0x0) //
	UINT32 reg_f3_enable                    :1;	//(28,RW,0x0) //
	UINT32 reg_f2_enable                    :1;	//(29,RW,0x0) //
	UINT32 reg_f1_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f0_enable                    :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_75_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_76_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008DC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_77_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008E0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_78_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008E4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_79_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008E8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_80_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008EC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_81_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_82_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008F4 RW 0x0000_0000
	UINT32 reg_overlap                      :8;	//(7:0,NA,0x80) //* final releaseÎ°??∏Ìï¥ RTL?êÏÑú??"reg_overlap"?ºÎ°ú ?¨Ïö©Ï§??§ÏùåÎ≤ÑÏ†Ñ??Î™ÖÏπ≠ ?ÖÎç∞?¥Ìä∏ ?àÏ†ï)	Í∞Ä?©Î≤î??: 4~128 (0~3 ?¨Ïù¥??Í∞??ÖÎ†•???§Î•ò Î∞úÏÉù)
	UINT32 resvd0                           :20;
	UINT32 reg_col_index                    :2;	//(29:28,NA,0x0) //* final releaseÎ°??∏Ìï¥ RTL?êÏÑú??"reg_boundary_side"?ºÎ°ú ?¨Ïö©Ï§??§ÏùåÎ≤ÑÏ†Ñ??Î™ÖÏπ≠ ?ÖÎç∞?¥Ìä∏ ?àÏ†ï)	Split/Merger???òÌï¥??Decontour Î™®Îìà?Ä 3 2 1 0 ?ºÎ°ú ?∏Îç±???òÏñ¥?àÏúº???§Ï†ï?Ä ?ÑÎûò???´ÏûêÎ•?Ï∞∏Ï°∞	?¥Î? ?ôÏûë?ÅÏù∏ Ï∏°Î©¥?êÏÑú 1Í≥?2???ëÍ∞ô?Ä ?ïÌÉú(?úÎãù ?±Ïóê ?òÌï¥???ÑÏπòÎ•??úÏãú?òÍ∏∞ ?ÑÌï¥ Íµ¨Î≥Ñ)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd1                           :1;
	UINT32 reg_col_mode_en                  :1;	//(31,NA,0x0) //* final releaseÎ°??∏Ìï¥ RTL?êÏÑú??"reg_boundary_en"?ºÎ°ú ?¨Ïö©Ï§??§ÏùåÎ≤ÑÏ†Ñ??Î™ÖÏπ≠ ?ÖÎç∞?¥Ìä∏ ?àÏ†ï)	0 : col_mode off	1 : col_mode on
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_83_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008F8 RW 0x0000_0000
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
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_84_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF20008FC RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :13;	//(12:0,NA,0x87F) //
	UINT32 resvd0                           :3;
	UINT32 reg_rd_roi_x0                    :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_85_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000900 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :13;	//(12:0,NA,0x83F) //
	UINT32 resvd0                           :3;
	UINT32 reg_rd_roi_y0                    :13;	//(28:16,NA,0x29) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_86_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000904 RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd                            :12;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_87_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000908 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd                            :12;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_88_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200090C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_89_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000910 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_90_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000914 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_91_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000918 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_92_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200091C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_93_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000920 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_94_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000924 RW 0x0000_0000
	UINT32 reg_face_demo_x1                 :13;	//(12:0,NA,0x400) //x0 < pos_x < x1 ?ºÎïå ?ôÏûë(2 Î∞∞ÏàòÎ°??§Ï†ï ?ÖÎ†•)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//(28:16,NA,0x1E0) //x0 < pos_x < x1 ?ºÎïå ?ôÏûë(2 Î∞∞ÏàòÎ°??§Ï†ï ?ÖÎ†•)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//(31,NA,0x0) //face gain demo mode ?ôÏûë
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_95_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000928 RW 0x0000_0000
	UINT32 reg_face_demo_y1                 :13;	//(12:0,NA,0x64) //y0 < pos_y < y1 ?ºÎïå ?ôÏûë
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//(28:16,NA,0xA) //y0 < pos_y < y1 ?ºÎïå ?ôÏûë
	UINT32 resvd1                           :3;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_96_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200092C RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x3              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_97_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000930 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y3              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_98_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000934 RW 0x0000_0000
	UINT32 reg_ref_filter_x1                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_x2                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x3                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ref_mmd_sel                  :1;	//(31,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_99_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000938 RW 0x0000_0000
	UINT32 reg_ref_filter_y2                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y3                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x0                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_100_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200093C RW 0x0000_0000
	UINT32 reg_ref_filter_y0                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y1                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_mmd_left_shift           :3;	//(22:20,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_mmd_right_shift              :2;	//(29:28,NA,0x0) //
	UINT32 resvd1                           :2;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_101_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000940 RW 0x0000_0000
	UINT32 reg_margin_bit                   :3;	//(2:0,NA,0x0) //
	UINT32 reg_rand_shift                   :3;	//(5:3,NA,0x0) //
	UINT32 resvd                            :25;
	UINT32 reg_blur_rand_en                 :1;	//(31,NA,0x0) //L6 interpolation ?¥ÌõÑ rand???Ä??enable
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_102_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000944 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_x3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_103_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000948 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_y3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_104_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200094C RW 0x0000_0000
	UINT32 reg_msp_inner_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_x3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_105_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000950 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_y3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_106_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000954 RW 0x0000_0000
	UINT32 reg_msp_rd_init_yy               :32;	//(31:0,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_107_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000958 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cb               :32;	//(31:0,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_108_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200095C RW 0x0000_0000
	UINT32 reg_msp_rd_init_cr               :32;	//(31:0,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_109_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000960 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_x0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x3                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_110_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000964 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_y0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y3                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_111_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000968 RW 0x0000_0000
	UINT32 reg_mnr_var_gain_low             :8;	//(7:0,NA,0x0) //
	UINT32 reg_mnr_pooling_th               :8;	//(15:8,NA,0x0) //
	UINT32 reg_mnr_pooling_max              :8;	//(23:16,NA,0x0) //
	UINT32 reg_mnr_var_left_shift           :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_mmd_edge_chroma_gain_en      :1;	//(30,NA,0x0) //
	UINT32 reg_en_mmd_new                   :1;	//(31,NA,0x0) //O24 new
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200096C RW 0x0000_0000
	UINT32 reg_mnr_var_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_mnr_var_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_mnr_var_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_mnr_var_gain_x3              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000970 RW 0x0000_0000
	UINT32 reg_mnr_var_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_mnr_var_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_mnr_var_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_mnr_var_gain_y3              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000974 RW 0x0000_0000
	UINT32 reg_edge_chroma_gain_x0          :8;	//(7:0,NA,0x0) //
	UINT32 reg_edge_chroma_gain_x1          :8;	//(15:8,NA,0x0) //
	UINT32 reg_edge_chroma_gain_x2          :8;	//(23:16,NA,0x0) //
	UINT32 reg_edge_chroma_gain_x3          :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000978 RW 0x0000_0000
	UINT32 reg_edge_chroma_gain_y0          :8;	//(7:0,NA,0x0) //
	UINT32 reg_edge_chroma_gain_y1          :8;	//(15:8,NA,0x0) //
	UINT32 reg_edge_chroma_gain_y2          :8;	//(23:16,NA,0x0) //
	UINT32 reg_edge_chroma_gain_y3          :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_MNR_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200097C RW 0x0000_0000
	UINT32 reg_l6_blur_luma_ratio           :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_luma_mode            :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_luma_th              :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :11;
	UINT32 reg_amean_filter_en              :1;	//(31,NA,0x0) //a-mean filter en
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_112_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000980 RW 0x0000_0000
	UINT32 reg_l6_blur_chroma_ratio         :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_chroma_mode          :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_chroma_th            :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_113_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000984 RW 0x0000_0000
	UINT32 reg_rd_blur_ratio_c              :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_ratio_y              :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :14;
	UINT32 reg_oai_repeat                   :1;	//(30,NA,0x0) //
	UINT32 reg_rd_blur_en                   :1;	//(31,NA,0x0) //O24 New : RRD enable
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_114_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000988 RW 0x0000_0000
	UINT32 reg_rd_blur_x0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_x1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_x2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_x3                   :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_115_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF200098C RW 0x0000_0000
	UINT32 reg_rd_blur_y0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_y1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_y2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_y3                   :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_116_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000990 RW 0x1357_9753
	UINT32 reg_decon_rd_init_yy             :32;	//(31:0,NA,0x13579753) //Decon 1st RRD seed
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_117_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000994 RW 0x2468_0864
	UINT32 reg_decon_rd_init_cb             :32;	//(31:0,NA,0x24680864) //Decon 1st RRD seed
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_118_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF2000998 RW 0x1470_3692
	UINT32 reg_decon_rd_init_cr             :32;	//(31:0,NA,0x14703692) //Decon 1st RRD seed
	};
	};
}PE_O24F22_DNR0_REG_DECON_CTRL_119_T;


/* OSD DCONTOUR*/
typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012380 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_master_bypass_en             :1;	//(1,RW,0x0) //
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //not used in O24
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align ??ÎßûÏùå)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //not used in O24
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012384 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012388 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301238C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012390 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x13579753) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_4_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012394 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x24680864) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_5_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012398 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x14703692) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_6_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_7_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123A0 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x3) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_8_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123A4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_9_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123A8 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123AC RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x13579753) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123B0 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x24680864) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123B4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x14703692) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123BC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123C0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123C4 RW 0x0000_0000
	UINT32 resvd0                           :14;
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 resvd1                           :8;
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode?êÏÑú 10b ?ÖÎ†•?? ÏºúÏïº ??
	UINT32 resvd2                           :1;
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :5;	//(30:26,RW,0x0) //0: final_gain	1: variance_gain	2: variance - dc frame input	3: variance - original var	4: variance - blur dc map	5: variance - blend dc map	6: variance - final dc map	7: rmmd - l0 mmd	8: rmmd - l0 luma	9: rmmd - refine	A : rmmd - final gain	B: blur map - mmd input luma	C: blur map - mmd gain	D: blur map output	E: PAI	F: RRD	10: diff gain	11: luma gain	12: sel_diff	13: motion shift	14: motion gain	15: skin gain	16: face gain	17: face-skin gain	18: aux luma gain
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x1) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123CC RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x7) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0xA) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0xF) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x19) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123D0 RW 0x0020_80FF
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0xFF) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x80) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x20) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123D4 RW 0x00C0_783C
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x1E) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0xC) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123D8 RW 0x0804_0080
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x80) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123DC RW 0x0200_003C
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x20) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_23_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123E0 RW 0x0643_212C
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x12C) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0xC8) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x64) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123E4 RW 0x190C_8384
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x384) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x320) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x190) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123E8 RW 0x3E84_0100
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x3E8) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123EC RW 0x1004_0100
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123F0 RW 0x1004_0100
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x100) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30123FC RW 0xFF60_0000
	UINT32 reg_120x68_block_no_v            :7;	//(6:0,RW,0x0) //L5 block info
	UINT32 resvd                            :17;
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_32_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012404 RW 0x2000_00C8
	UINT32 reg_120x68_last_block_size_v     :7;	//(6:0,RW,0x0) //L5 block info
	UINT32 reg_120x68_last_block_size_h     :7;	//(13:7,RW,0x0) //L5 block info
	UINT32 reg_120x68_block_size_v          :7;	//(20:14,RW,0x0) //L5 block info
	UINT32 reg_120x68_block_size_h          :7;	//(27:21,RW,0x0) //L5 block info
	UINT32 resvd                            :4;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_33_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_34_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301240C RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_35_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012410 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_36_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012414 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_37_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012418 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_38_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301241C RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_120x68_block_no_h            :7;	//(30:24,RW,0x0) //
	UINT32 reg_120x68_block_info_force_en   :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_39_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012420 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_40_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012424 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_41_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012428 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_42_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301242C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_43_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012430 RW 0x3264_C8FA
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0xFA) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0xC8) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x32) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_44_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012434 RW 0xFF64_1400
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x14) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_45_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_46_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301243C RW 0x4871_B399
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x399) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x71B) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x2) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x2) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_47_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012440 RW 0x0A50_6478
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x78) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x64) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x50) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0xA) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_48_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012444 RW 0xFF32_0A01
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x1) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0xA) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x32) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0xFF) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_49_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012448 RW 0x143C_6EC8
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x14) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_50_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301244C RW 0x5064_788C
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x8C) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x78) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x50) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_51_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012450 RW 0x7882_B4C8
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x82) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x78) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_52_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012454 RW 0x00C8_C800
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0xC8) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_53_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012458 RW 0x0064_C8FA
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0xFA) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_54_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301245C RW 0x0032_C8FF
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0xFF) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x32) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_55_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012460 RW 0x8FF0_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0xFF) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x1) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_56_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012464 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_aux_luma_en                  :1;	//(31,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_57_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012468 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_58_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301246C RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_59_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012470 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_60_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012474 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_61_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012478 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(9:0,RW,0x0) //
	UINT32 resvd                            :22;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_62_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301247C RW 0x8020_8080
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_63_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012480 RW 0x80FF_FF00
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_64_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012484 RW 0x0020_0200
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_65_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012488 RW 0x0020_0200
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_66_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301248C RW 0x0020_0200
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_67_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012490 RW 0x0003_2000
	UINT32 tdata0                           :32;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_68_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012494 RW 0x1ABC_0085
	UINT32 reg_var_lowapl_lut_x2            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x1            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x0            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_69_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012498 RW 0x03C1_90C8
	UINT32 reg_var_lowapl_lut_y1            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y0            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x3            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_70_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301249C RW 0x9909_6320
	UINT32 reg_var_lowapl_blend_x0          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y3            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y2            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_71_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124A0 RW 0x384F_A100
	UINT32 reg_var_lowapl_blend_x3          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x2          :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x1          :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_72_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124A4 RW 0x1004_0100
	UINT32 reg_var_lowapl_blend_y3          :8;	//(7:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y2          :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y1          :8;	//(23:16,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y0          :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_73_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124A8 RW 0x1004_0100
	UINT32 reg_lowapl_master_blend          :8;	//(7:0,RW,0x0) //
	UINT32 reg_2x2_var_msb_sel              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :23;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_74_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124AC RW 0x1000_2010
	UINT32 reg_2nd_var_x_th1                :10;	//(9:0,RW,0x10) //
	UINT32 reg_2nd_var_x_th0                :10;	//(19:10,RW,0x8) //
	UINT32 reg_2nd_luma_y_th7               :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_75_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124B0 RW 0x0140_7900
	UINT32 reg_2nd_var_y_th0                :10;	//(9:0,RW,0x100) //
	UINT32 reg_2nd_var_x_th3                :10;	//(19:10,RW,0x1E) //
	UINT32 reg_2nd_var_x_th2                :10;	//(29:20,RW,0x14) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_76_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124B4 RW 0x0B40_8000
	UINT32 reg_2nd_var_y_th3                :10;	//(9:0,RW,0x0) //
	UINT32 reg_2nd_var_y_th2                :10;	//(19:10,RW,0x20) //
	UINT32 reg_2nd_var_y_th1                :10;	//(29:20,RW,0xB4) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_77_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124B8 RW 0x6030_180C
	UINT32 reg_2nd_diff_x_th0               :8;	//(7:0,RW,0xC) //
	UINT32 reg_2nd_diff_x_th1               :8;	//(15:8,RW,0x18) //
	UINT32 reg_2nd_diff_x_th2               :8;	//(23:16,RW,0x30) //
	UINT32 reg_2nd_diff_x_th3               :8;	//(31:24,RW,0x60) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_78_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124BC RW 0x0020_80FF
	UINT32 reg_2nd_diff_y_th0               :8;	//(7:0,RW,0xFF) //
	UINT32 reg_2nd_diff_y_th1               :8;	//(15:8,RW,0x80) //
	UINT32 reg_2nd_diff_y_th2               :8;	//(23:16,RW,0x20) //
	UINT32 reg_2nd_diff_y_th3               :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_79_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124C0 RW 0x0000_0000
	UINT32 reg_2nd_rd_simple_init_yy        :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_80_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124C4 RW 0x0000_0000
	UINT32 reg_2nd_rd_simple_init_cb        :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_81_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124C8 RW 0x0000_0000
	UINT32 reg_2nd_rd_simple_init_cr        :32;	//(31:0,RW,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_82_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124CC RW 0x0000_0000
	UINT32 reg_overlap_hsize                :8;	//(7:0,NA,0x80) //* final releaseÎ°??∏Ìï¥ RTL?êÏÑú??"reg_overlap"?ºÎ°ú ?¨Ïö©Ï§??§ÏùåÎ≤ÑÏ†Ñ??Î™ÖÏπ≠ ?ÖÎç∞?¥Ìä∏ ?àÏ†ï)	Í∞Ä?©Î≤î??: 4~128 (0~3 ?¨Ïù¥??Í∞??ÖÎ†•???§Î•ò Î∞úÏÉù)
	UINT32 reg_trans_pos                    :6;	//(13:8,NA,0x2) //h_block Í∞úÏàòÎ≥¥Îã§ ?ëÏïÑ????
	UINT32 resvd0                           :10;
	UINT32 reg_original_size_set            :1;	//(24,NA,0x0) //block_info?êÏÑú ND??split ?¥Ï†Ñ???§Î¶¨ÏßÄ???ÖÎ†• ?ÅÏÉÅ???Ä???∏ÌåÖ(E60?êÏÑú 8K 4split/4K 2split?Ä ÏΩîÏñ¥ ?ÖÎ†•???ôÏùº?òÍ∏∞ ?åÎ¨∏??Î≥ÑÎèÑ??Íµ¨Î∂Ñ ?ÑÏöî)	0: 8K	1: 4K
	UINT32 resvd1                           :3;
	UINT32 reg_col_index                    :2;	//(29:28,NA,0x0) //* final releaseÎ°??∏Ìï¥ RTL?êÏÑú??"reg_boundary_side"?ºÎ°ú ?¨Ïö©Ï§??§ÏùåÎ≤ÑÏ†Ñ??Î™ÖÏπ≠ ?ÖÎç∞?¥Ìä∏ ?àÏ†ï)	Split/Merger???òÌï¥??Decontour Î™®Îìà?Ä 3 2 1 0 ?ºÎ°ú ?∏Îç±???òÏñ¥?àÏúº???§Ï†ï?Ä ?ÑÎûò???´ÏûêÎ•?Ï∞∏Ï°∞	?¥Î? ?ôÏûë?ÅÏù∏ Ï∏°Î©¥?êÏÑú 1Í≥?2???ëÍ∞ô?Ä ?ïÌÉú(?úÎãù ?±Ïóê ?òÌï¥???ÑÏπòÎ•??úÏãú?òÍ∏∞ ?ÑÌï¥ Íµ¨Î≥Ñ)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd2                           :1;
	UINT32 reg_col_mode_en                  :1;	//(31,NA,0x0) //* final releaseÎ°??∏Ìï¥ RTL?êÏÑú??"reg_boundary_en"?ºÎ°ú ?¨Ïö©Ï§??§ÏùåÎ≤ÑÏ†Ñ??Î™ÖÏπ≠ ?ÖÎç∞?¥Ìä∏ ?àÏ†ï)	0 : col_mode off	1 : col_mode on
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_83_T;

typedef struct {
	UINT32 uaddr32;
	 union {
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
	};
}PE_O24F22_REG_OSD_DECON_CTRL_84_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124D4 RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x87F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_85_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124D8 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x83F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x29) //
	UINT32 resvd1                           :4;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_86_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124DC RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 reg_out_prev_x                   :12;	//(31:20,NA,0x1E) //Defualt: 30	?¥Ï†Ñ ÏΩîÏñ¥??Î≥¥ÎÇº Í∞íÏùÑ read ?òÎäî ?ÑÏπò(active ?ÅÏó≠???Ä??Ï¢åÌëú)
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_87_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124E0 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 reg_out_next_x                   :12;	//(31:20,NA,0x28) //Defualt: 40	?§Ïùå ÏΩîÏñ¥??Î≥¥ÎÇº Í∞íÏùÑ read ?òÎäî ?ÑÏπò(active ?ÅÏó≠???Ä??Ï¢åÌëú)
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_88_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124E4 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :2;
	UINT32 reg_out_prev_y                   :7;	//(30:24,NA,0x78) //Defualt: 120 (y < block_size)	?§Ïùå ÏΩîÏñ¥??Î≥¥ÎÇº Í∞íÏùÑ read ?òÎäî ?ÑÏπò(active ?ÅÏó≠???Ä??Ï¢åÌëú)
	UINT32 resvd2                           :1;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_89_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124E8 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :2;
	UINT32 reg_out_next_y                   :7;	//(30:24,NA,0x79) //Defualt: 121 (y < block_size)	?§Ïùå ÏΩîÏñ¥??Î≥¥ÎÇº Í∞íÏùÑ read ?òÎäî ?ÑÏπò(active ?ÅÏó≠???Ä??Ï¢åÌëú)
	UINT32 resvd2                           :1;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_90_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124EC RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_91_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124F0 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_92_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124F4 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_93_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124F8 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //1st????Í∞íÏùÑ 2nd_rd_luma?Ä Í≥µÏú†(final releaseÎ°??∏Ìï¥??Î™ÖÏπ≠ ?òÏ†ï Î∂àÍ?. ?§Ïùå Î≤ÑÏ†Ñ ?ÖÎç∞?¥Ìä∏)
	UINT32 resvd1                           :10;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_94_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF30124FC RW 0x0000_0000
	UINT32 reg_face_demo_x1                 :13;	//(12:0,NA,0x400) //x0 < pos_x < x1 ?ºÎïå ?ôÏûë(2 Î∞∞ÏàòÎ°??§Ï†ï ?ÖÎ†•)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//(28:16,NA,0x1E0) //x0 < pos_x < x1 ?ºÎïå ?ôÏûë(2 Î∞∞ÏàòÎ°??§Ï†ï ?ÖÎ†•)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//(31,NA,0x0) //face gain demo mode ?ôÏûë
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_95_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012500 RW 0x0000_0000
	UINT32 reg_face_demo_y1                 :13;	//(12:0,NA,0x64) //y0 < pos_y < y1 ?ºÎïå ?ôÏûë
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//(28:16,NA,0xA) //y0 < pos_y < y1 ?ºÎïå ?ôÏûë
	UINT32 resvd1                           :3;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_96_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012504 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x3              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_97_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012508 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y3              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_98_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301250C RW 0x0000_0000
	UINT32 reg_ref_filter_x1                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_x2                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x3                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ref_mmd_sel                  :1;	//(31,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_99_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012510 RW 0x0000_0000
	UINT32 reg_ref_filter_y2                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y3                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x0                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_100_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012514 RW 0x0000_0000
	UINT32 reg_ref_filter_y0                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y1                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_mmd_left_shift           :3;	//(22:20,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_mmd_right_shift              :2;	//(29:28,NA,0x0) //
	UINT32 resvd1                           :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_101_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012518 RW 0x0000_0000
	UINT32 reg_margin_bit                   :3;	//(2:0,NA,0x0) //
	UINT32 reg_rand_shift                   :3;	//(5:3,NA,0x0) //
	UINT32 resvd                            :26;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_102_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301251C RW 0x0000_0000
	UINT32 reg_msp_outer_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_x3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_103_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012520 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_y3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_104_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012524 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_x3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_105_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012528 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_y3            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_106_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301252C RW 0x0000_0000
	UINT32 reg_msp_rd_init_yy               :32;	//(31:0,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_107_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012530 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cb               :32;	//(31:0,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_108_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012534 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cr               :32;	//(31:0,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_109_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012538 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_x0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x3                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_110_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301253C RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_y0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y3                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_111_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012540 RW 0x0000_0000
	UINT32 reg_l6_blur_luma_ratio           :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_luma_mode            :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_luma_th              :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :11;
	UINT32 reg_amean_filter_en              :1;	//(31,NA,0x0) //a-mean filter en
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_112_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012544 RW 0x0000_0000
	UINT32 reg_l6_blur_chroma_ratio         :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_chroma_mode          :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_chroma_th            :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_113_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012548 RW 0x0000_0000
	UINT32 reg_rd_blur_ratio_c              :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_ratio_y              :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :14;
	UINT32 reg_oai_repeat                   :1;	//(30,NA,0x0) //
	UINT32 reg_rd_blur_en                   :1;	//(31,NA,0x0) //O24 New : RRD enable
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_114_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301254C RW 0x0000_0000
	UINT32 reg_rd_blur_x0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_x1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_x2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_x3                   :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_115_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012550 RW 0x0000_0000
	UINT32 reg_rd_blur_y0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_y1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_y2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_y3                   :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_116_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012554 RW 0x1357_9753
	UINT32 reg_decon_rd_init_yy             :32;	//(31:0,NA,0x13579753) //Decon 1st RRD seed
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_117_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012558 RW 0x2468_0864
	UINT32 reg_decon_rd_init_cb             :32;	//(31:0,NA,0x24680864) //Decon 1st RRD seed
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_118_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301255C RW 0x1470_3692
	UINT32 reg_decon_rd_init_cr             :32;	//(31:0,NA,0x14703692) //Decon 1st RRD seed
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_119_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012560 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_120_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012564 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_121_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF3012568 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_122_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF301256C RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
	};
}PE_O24F22_REG_OSD_DECON_CTRL_123_T;

typedef struct {
	PE_O24F22_DNR0_DNR_MAX_CTRL_T                             dnr_max_ctrl;			//0xF2000594
	PE_O24F22_DNR0_MNR_CTRL_0_T                               mnr_ctrl_0;			//0xF20005A0
	PE_O24F22_DNR0_MNR_CTRL_1_T                               mnr_ctrl_1;			//0xF20005A4
	PE_O24F22_DNR0_MNR_CTRL_2_T                               mnr_ctrl_2;			//0xF20005A8
	PE_O24F22_DNR0_MNR_CTRL_3_T                               mnr_ctrl_3;			//0xF20005AC
	PE_O24F22_DNR0_MNR_CTRL_4_T                               mnr_ctrl_4;			//0xF20005B0
	PE_O24F22_DNR0_MNR_CTRL_5_T                               mnr_ctrl_5;			//0xF20005B4
	PE_O24F22_DNR0_DETAIL_CTRL_T                              detail_ctrl;			//0xF20005B8
	PE_O24F22_DNR0_DC_BNR_CTRL_0_T                            dc_bnr_ctrl_0;		//0xF20005BC
	PE_O24F22_DNR0_DC_BNR_CTRL_1_T                            dc_bnr_ctrl_1;		//0xF20005C0
	PE_O24F22_DNR0_DC_BNR_CTRL_2_T                            dc_bnr_ctrl_2;		//0xF20005C4
	PE_O24F22_DNR0_DC_BNR_CTRL_3_T                            dc_bnr_ctrl_3;		//0xF20005C8
	PE_O24F22_DNR0_DC_BNR_CTRL_4_T                            dc_bnr_ctrl_4;		//0xF20005CC
	PE_O24F22_DNR0_DC_BNR_CTRL_5_T                            dc_bnr_ctrl_5;		//0xF20005D0
	PE_O24F22_DNR0_AC_BNR_CTRL_0_T                            ac_bnr_ctrl_0;		//0xF20005D4
	PE_O24F22_DNR0_AC_BNR_CTRL_1_T                            ac_bnr_ctrl_1;		//0xF20005D8
	PE_O24F22_DNR0_AC_BNR_CTRL_2_T                            ac_bnr_ctrl_2;		//0xF20005DC
	PE_O24F22_DNR0_AC_BNR_CTRL_3_T                            ac_bnr_ctrl_3;		//0xF20005E4
	PE_O24F22_DNR0_AC_BNR_CTRL_4_T                            ac_bnr_ctrl_4;		//0xF20005E8
	PE_O24F22_DNR0_AC_BNR_CTRL_5_T                            ac_bnr_ctrl_5;		//0xF20005F0
	PE_O24F22_DNR0_AC_BNR_CTRL_6_T                            ac_bnr_ctrl_6;		//0xF20005F4
	PE_O24F22_DNR0_AC_BNR_CTRL_7_T                            ac_bnr_ctrl_7;		//0xF20005F8
	PE_O24F22_DNR0_AC_BNR_CTRL_8_T                            ac_bnr_ctrl_8;		//0xF2000600
	PE_O24F22_DNR0_AC_BNR_CTRL_9_T                            ac_bnr_ctrl_9;		//0xF2000604
	PE_O24F22_DNR0_AC_BNR_CTRL_10_T                           ac_bnr_ctrl_10;		//0xF2000608
	PE_O24F22_DNR0_AC_BNR_CTRL_11_T                           ac_bnr_ctrl_11;		//0xF200060C
	PE_O24F22_DNR0_AC_BNR_CTRL_12_T                           ac_bnr_ctrl_12;		//0xF2000610
	PE_O24F22_DNR0_ELLIPSE_CTRL_0_T                           ellipse_ctrl_0;		//0xF2000638
	PE_O24F22_DNR0_ELLIPSE_CTRL_1_T                           ellipse_ctrl_1;		//0xF200063C
	PE_O24F22_DNR0_ELLIPSE_CTRL_2_T                           ellipse_ctrl_2;		//0xF2000640
	PE_O24F22_DNR0_ELLIPSE_CTRL_3_T                           ellipse_ctrl_3;		//0xF200066C
	PE_O24F22_DNR0_ELLIPSE_CTRL_4_T                           ellipse_ctrl_4;		//0xF2000670
	PE_O24F22_DNR0_SC_BNR_CTRL_2_T                            sc_bnr_ctrl_2;			//0xF2000674
	PE_O24F22_DNR0_SC_BNR_CTRL_3_T                            sc_bnr_ctrl_3;			//0xF2000678
	PE_O24F22_DNR0_SC_BNR_CTRL_4_T                            sc_bnr_ctrl_4;			//0xF200067C
	PE_O24F22_DNR0_SC_BNR_CTRL_5_T                            sc_bnr_ctrl_5;			//0xF2000680
	PE_O24F22_DNR0_ELLIPSE_CTRL_5_T                           ellipse_ctrl_5;		//0xF2000684
	PE_O24F22_DNR0_C_PRE_BLUR_CTRL_0_T                        c_pre_blur_ctrl_0;	    //0xF2000688
	PE_O24F22_DNR0_ELLIPSE_CTRL_6_T                           ellipse_ctrl_6;		//0xF200068C
	PE_O24F22_DNR0_ELLIPSE_CTRL_7_T                           ellipse_ctrl_7;	    //0xF2000690
	PE_O24F22_DNR0_ELLIPSE_CTRL_8_T                           ellipse_ctrl_8;		//0xF2000694
	PE_O24F22_DNR0_ELLIPSE_CTRL_9_T                           ellipse_ctrl_9;		//0xF2000698
	PE_O24F22_DNR0_AC_BNR_CTRL_13_T                           ac_bnr_ctrl_13;		//0xF200069C
	PE_O24F22_DNR0_AC_BNR_CTRL_14_T                           ac_bnr_ctrl_14;		//0xF20006A0
	PE_O24F22_DNR0_DC_BNR_CTRL_6_T                            dc_bnr_ctrl_6;			//0xF20006A4
	PE_O24F22_DNR0_DC_BNR_CTRL_7_T                            dc_bnr_ctrl_7;			//0xF20006A8
	PE_O24F22_DNR0_SQM_CTRL_0_T                               sqm_ctrl_0;			//0xF20006AC
	PE_O24F22_DNR0_SQM_CTRL_1_T                               sqm_ctrl_1;			//0xF20006B0
	PE_O24F22_DNR0_SQM_CTRL_2_T                               sqm_ctrl_2;			//0xF20006B4
	PE_O24F22_DNR0_SQM_CTRL_3_T                               sqm_ctrl_3;			//0xF20006B8
	PE_O24F22_DNR0_SQM_CTRL_4_T                               sqm_ctrl_4;			//0xF20006BC
	PE_O24F22_DNR0_AC_BNR_15_T                                ac_bnr_15;				//0xF2000730
	PE_O24F22_DNR0_AC_BNR_16_T                                ac_bnr_16;				//0xF2000734
	PE_O24F22_DNR0_REG_DECON_CTRL_0_T                         reg_decon_ctrl_0;		//0xF2000764
	PE_O24F22_DNR0_REG_DECON_CTRL_1_T                         reg_decon_ctrl_1;		//0xF2000768
	PE_O24F22_DNR0_REG_DECON_CTRL_2_T                         reg_decon_ctrl_2;		//0xF200076C
	PE_O24F22_DNR0_REG_DECON_CTRL_3_T                         reg_decon_ctrl_3;		//0xF2000770
	PE_O24F22_DNR0_REG_DECON_CTRL_4_T                         reg_decon_ctrl_4;		//0xF2000774
	PE_O24F22_DNR0_REG_DECON_CTRL_5_T                         reg_decon_ctrl_5;		//0xF2000778
	PE_O24F22_DNR0_REG_DECON_CTRL_6_T                         reg_decon_ctrl_6;		//0xF200077C
	PE_O24F22_DNR0_REG_DECON_CTRL_7_T                         reg_decon_ctrl_7;		//0xF2000780
	PE_O24F22_DNR0_REG_DECON_CTRL_8_T                         reg_decon_ctrl_8;		//0xF2000784
	PE_O24F22_DNR0_REG_DECON_CTRL_9_T                         reg_decon_ctrl_9;		//0xF2000788
	PE_O24F22_DNR0_REG_DECON_CTRL_10_T                        reg_decon_ctrl_10;	    //0xF200078C
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_8_T                        reg_dc_bnr_ctrl_8;	    //0xF2000790
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_9_T                        reg_dc_bnr_ctrl_9;	    //0xF2000794
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_10_T                       reg_dc_bnr_ctrl_10;	//0xF2000798
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_11_T                       reg_dc_bnr_ctrl_11;	//0xF200079C
	PE_O24F22_DNR0_REG_MNR_CTRL_6_T                           reg_mnr_ctrl_6;		//0xF20007A8
	PE_O24F22_DNR0_REG_MNR_CTRL_7_T                           reg_mnr_ctrl_7;		//0xF20007AC
	PE_O24F22_DNR0_REG_MNR_CTRL_8_T                           reg_mnr_ctrl_8;		//0xF20007B0
	PE_O24F22_DNR0_REG_MNR_CTRL_9_T                           reg_mnr_ctrl_9;		//0xF20007B4
	PE_O24F22_DNR0_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;		//0xF20007B8
	PE_O24F22_DNR0_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;		//0xF20007BC
	PE_O24F22_DNR0_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;		//0xF20007C0
	PE_O24F22_DNR0_REG_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0xF20007C4
	PE_O24F22_DNR0_REG_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0xF20007C8
	PE_O24F22_DNR0_REG_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0xF20007CC
	PE_O24F22_DNR0_REG_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0xF20007D0
	PE_O24F22_DNR0_REG_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0xF20007D4
	PE_O24F22_DNR0_REG_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0xF20007D8
	PE_O24F22_DNR0_REG_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0xF20007DC
	PE_O24F22_DNR0_REG_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0xF20007E0
	PE_O24F22_DNR0_REG_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0xF20007E4
	PE_O24F22_DNR0_REG_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0xF20007E8
	PE_O24F22_DNR0_REG_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0xF20007EC
	PE_O24F22_DNR0_REG_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0xF20007F0
	PE_O24F22_DNR0_REG_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0xF20007F4
	PE_O24F22_DNR0_REG_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0xF20007F8
	PE_O24F22_DNR0_REG_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0xF20007FC
	PE_O24F22_DNR0_REG_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0xF2000800
	PE_O24F22_DNR0_REG_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0xF2000804
	PE_O24F22_DNR0_REG_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0xF2000808
	PE_O24F22_DNR0_REG_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0xF200080C
	PE_O24F22_DNR0_REG_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0xF2000810
	PE_O24F22_DNR0_REG_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0xF2000814
	PE_O24F22_DNR0_REG_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0xF2000818
	PE_O24F22_DNR0_REG_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0xF200081C
	PE_O24F22_DNR0_REG_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0xF2000820
	PE_O24F22_DNR0_REG_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0xF2000824
	PE_O24F22_DNR0_REG_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0xF2000828
	PE_O24F22_DNR0_REG_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0xF200082C
	PE_O24F22_DNR0_REG_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0xF2000830
	PE_O24F22_DNR0_REG_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0xF2000834
	PE_O24F22_DNR0_REG_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0xF2000838
	PE_O24F22_DNR0_REG_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0xF200083C
	PE_O24F22_DNR0_REG_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0xF2000840
	PE_O24F22_DNR0_REG_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0xF2000844
	PE_O24F22_DNR0_REG_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0xF2000848
	PE_O24F22_DNR0_REG_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0xF200084C
	PE_O24F22_DNR0_REG_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0xF2000850
	PE_O24F22_DNR0_REG_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0xF2000854
	PE_O24F22_DNR0_REG_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0xF2000858
	PE_O24F22_DNR0_REG_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0xF200085C
	PE_O24F22_DNR0_REG_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0xF2000860
	PE_O24F22_DNR0_REG_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0xF2000864
	PE_O24F22_DNR0_REG_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0xF2000868
	PE_O24F22_DNR0_REG_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0xF200086C
	PE_O24F22_DNR0_REG_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0xF2000870
	PE_O24F22_DNR0_REG_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0xF2000874
	PE_O24F22_DNR0_REG_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0xF2000878
	PE_O24F22_DNR0_REG_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0xF200087C
	PE_O24F22_DNR0_REG_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0xF2000880
	PE_O24F22_DNR0_REG_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0xF2000884
	PE_O24F22_DNR0_REG_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0xF2000888
	PE_O24F22_DNR0_REG_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0xF200088C
	PE_O24F22_DNR0_REG_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0xF2000890
	PE_O24F22_DNR0_REG_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0xF2000894
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_12_T                       reg_dc_bnr_ctrl_12;//0xF2000898
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_13_T                       reg_dc_bnr_ctrl_13;//0xF200089C
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_14_T                       reg_dc_bnr_ctrl_14;//0xF20008A0
	PE_O24F22_DNR0_REG_DC_BNR_CTRL_15_T                       reg_dc_bnr_ctrl_15;//0xF20008A4
	PE_O24F22_DNR0_REG_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0xF20008A8
	PE_O24F22_DNR0_REG_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0xF20008AC
	PE_O24F22_DNR0_REG_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0xF20008B0
	PE_O24F22_DNR0_REG_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0xF20008B4
	PE_O24F22_DNR0_REG_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0xF20008B8
	PE_O24F22_DNR0_REG_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0xF20008BC
	PE_O24F22_DNR0_REG_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0xF20008C0
	PE_O24F22_DNR0_REG_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0xF20008C4
	PE_O24F22_DNR0_REG_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0xF20008C8
	PE_O24F22_DNR0_REG_DECON_CTRL_73_T                        reg_decon_ctrl_73;	//0xF20008CC
	PE_O24F22_DNR0_REG_DECON_CTRL_74_T                        reg_decon_ctrl_74;	//0xF20008D0
	PE_O24F22_DNR0_REG_DECON_CTRL_75_T                        reg_decon_ctrl_75;	//0xF20008D4
	PE_O24F22_DNR0_REG_DECON_CTRL_76_T                        reg_decon_ctrl_76;	//0xF20008D8
	PE_O24F22_DNR0_REG_DECON_CTRL_77_T                        reg_decon_ctrl_77;	//0xF20008DC
	PE_O24F22_DNR0_REG_DECON_CTRL_78_T                        reg_decon_ctrl_78;	//0xF20008E0
	PE_O24F22_DNR0_REG_DECON_CTRL_79_T                        reg_decon_ctrl_79;	//0xF20008E4
	PE_O24F22_DNR0_REG_DECON_CTRL_80_T                        reg_decon_ctrl_80;	//0xF20008E8
	PE_O24F22_DNR0_REG_DECON_CTRL_81_T                        reg_decon_ctrl_81;	//0xF20008EC
	PE_O24F22_DNR0_REG_DECON_CTRL_82_T                        reg_decon_ctrl_82;	//0xF20008F0
	//PE_O24F22_DNR0_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xF20008F4
	PE_O24F22_DNR0_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xF20008F8
	PE_O24F22_DNR0_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xF20008FC
	PE_O24F22_DNR0_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xF2000900
	PE_O24F22_DNR0_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xF2000904
	PE_O24F22_DNR0_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xF2000908
	PE_O24F22_DNR0_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xF200090C
	PE_O24F22_DNR0_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xF2000910
	PE_O24F22_DNR0_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xF2000914
	PE_O24F22_DNR0_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xF2000918
	PE_O24F22_DNR0_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xF200091C
	PE_O24F22_DNR0_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xF2000920
	PE_O24F22_DNR0_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xF2000924
	PE_O24F22_DNR0_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xF2000928
	PE_O24F22_DNR0_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xF200092C
	PE_O24F22_DNR0_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xF2000930
	PE_O24F22_DNR0_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xF2000934
	PE_O24F22_DNR0_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xF2000938
	PE_O24F22_DNR0_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xF200093C
	PE_O24F22_DNR0_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xF2000940
	PE_O24F22_DNR0_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xF2000944
	PE_O24F22_DNR0_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xF2000948
	PE_O24F22_DNR0_REG_DECON_CTRL_105_T                    reg_decon_ctrl_105;	//0xF200094C
	PE_O24F22_DNR0_REG_DECON_CTRL_106_T                    reg_decon_ctrl_106;	//0xF2000950
	PE_O24F22_DNR0_REG_DECON_CTRL_107_T                    reg_decon_ctrl_107;	//0xF2000954
	PE_O24F22_DNR0_REG_DECON_CTRL_108_T                    reg_decon_ctrl_108;	//0xF2000958
	PE_O24F22_DNR0_REG_DECON_CTRL_109_T                    reg_decon_ctrl_109;	//0xF200095C
	PE_O24F22_DNR0_REG_DECON_CTRL_110_T                    reg_decon_ctrl_110;	//0xF2000960
	PE_O24F22_DNR0_REG_DECON_CTRL_111_T                    reg_decon_ctrl_111;	//0xF2000964
	PE_O24F22_DNR0_MNR_CTRL_13_T                                  mnr_ctrl_13;	//0xF2000968
	PE_O24F22_DNR0_MNR_CTRL_14_T                                  mnr_ctrl_14;	//0xF200096C
	PE_O24F22_DNR0_MNR_CTRL_15_T                                  mnr_ctrl_15;	//0xF2000970
	PE_O24F22_DNR0_MNR_CTRL_16_T                                  mnr_ctrl_16;	//0xF2000974
	PE_O24F22_DNR0_MNR_CTRL_17_T                                  mnr_ctrl_17;	//0xF2000978
	PE_O24F22_DNR0_REG_DECON_CTRL_112_T                    reg_decon_ctrl_112;	//0xF200097C
	PE_O24F22_DNR0_REG_DECON_CTRL_113_T                    reg_decon_ctrl_113;	//0xF2000980
	PE_O24F22_DNR0_REG_DECON_CTRL_114_T                    reg_decon_ctrl_114;	//0xF2000984
	PE_O24F22_DNR0_REG_DECON_CTRL_115_T                    reg_decon_ctrl_115;	//0xF2000988
	PE_O24F22_DNR0_REG_DECON_CTRL_116_T                    reg_decon_ctrl_116;	//0xF200098C
	PE_O24F22_DNR0_REG_DECON_CTRL_117_T                    reg_decon_ctrl_117;	//0xF2000990
	PE_O24F22_DNR0_REG_DECON_CTRL_118_T                    reg_decon_ctrl_118;	//0xF2000994
	PE_O24F22_DNR0_REG_DECON_CTRL_119_T                    reg_decon_ctrl_119;	//0xF2000998
}PE_CHPI_DNR_TBL_O24F22_T;


typedef struct {
	PE_O24F22_REG_OSD_DECON_CTRL_0_T                       reg_decon_ctrl_0;	//0xF3012380
	PE_O24F22_REG_OSD_DECON_CTRL_1_T                       reg_decon_ctrl_1;	//0xF3012384
	PE_O24F22_REG_OSD_DECON_CTRL_2_T                       reg_decon_ctrl_2;	//0xF3012388
	PE_O24F22_REG_OSD_DECON_CTRL_3_T                       reg_decon_ctrl_3;	//0xF301238C
	PE_O24F22_REG_OSD_DECON_CTRL_4_T                       reg_decon_ctrl_4;	//0xF3012390
	PE_O24F22_REG_OSD_DECON_CTRL_5_T                       reg_decon_ctrl_5;	//0xF3012394
	PE_O24F22_REG_OSD_DECON_CTRL_6_T                       reg_decon_ctrl_6;	//0xF3012398
	PE_O24F22_REG_OSD_DECON_CTRL_7_T                       reg_decon_ctrl_7;	//0xF301239C
	PE_O24F22_REG_OSD_DECON_CTRL_8_T                       reg_decon_ctrl_8;	//0xF30123A0
	PE_O24F22_REG_OSD_DECON_CTRL_9_T                       reg_decon_ctrl_9;	//0xF30123A4
	PE_O24F22_REG_OSD_DECON_CTRL_10_T                     reg_decon_ctrl_10;	//0xF30123A8
	PE_O24F22_REG_OSD_DECON_CTRL_11_T                     reg_decon_ctrl_11;	//0xF30123AC
	PE_O24F22_REG_OSD_DECON_CTRL_12_T                     reg_decon_ctrl_12;	//0xF30123B0
	PE_O24F22_REG_OSD_DECON_CTRL_13_T                     reg_decon_ctrl_13;	//0xF30123B4
	PE_O24F22_REG_OSD_DECON_CTRL_14_T                     reg_decon_ctrl_14;	//0xF30123B8
	PE_O24F22_REG_OSD_DECON_CTRL_15_T                     reg_decon_ctrl_15;	//0xF30123BC
	PE_O24F22_REG_OSD_DECON_CTRL_16_T                     reg_decon_ctrl_16;	//0xF30123C0
	PE_O24F22_REG_OSD_DECON_CTRL_17_T                     reg_decon_ctrl_17;	//0xF30123C4
	PE_O24F22_REG_OSD_DECON_CTRL_18_T                     reg_decon_ctrl_18;	//0xF30123C8
	PE_O24F22_REG_OSD_DECON_CTRL_19_T                     reg_decon_ctrl_19;	//0xF30123CC
	PE_O24F22_REG_OSD_DECON_CTRL_20_T                     reg_decon_ctrl_20;	//0xF30123D0
	PE_O24F22_REG_OSD_DECON_CTRL_21_T                     reg_decon_ctrl_21;	//0xF30123D4
	PE_O24F22_REG_OSD_DECON_CTRL_22_T                     reg_decon_ctrl_22;	//0xF30123D8
	PE_O24F22_REG_OSD_DECON_CTRL_23_T                     reg_decon_ctrl_23;	//0xF30123DC
	PE_O24F22_REG_OSD_DECON_CTRL_24_T                     reg_decon_ctrl_24;	//0xF30123E0
	PE_O24F22_REG_OSD_DECON_CTRL_25_T                     reg_decon_ctrl_25;	//0xF30123E4
	PE_O24F22_REG_OSD_DECON_CTRL_26_T                     reg_decon_ctrl_26;	//0xF30123E8
	PE_O24F22_REG_OSD_DECON_CTRL_27_T                     reg_decon_ctrl_27;	//0xF30123EC
	PE_O24F22_REG_OSD_DECON_CTRL_28_T                     reg_decon_ctrl_28;	//0xF30123F0
	PE_O24F22_REG_OSD_DECON_CTRL_29_T                     reg_decon_ctrl_29;	//0xF30123F4
	PE_O24F22_REG_OSD_DECON_CTRL_30_T                     reg_decon_ctrl_30;	//0xF30123F8
	PE_O24F22_REG_OSD_DECON_CTRL_31_T                     reg_decon_ctrl_31;	//0xF30123FC
	PE_O24F22_REG_OSD_DECON_CTRL_32_T                     reg_decon_ctrl_32;	//0xF3012400
	PE_O24F22_REG_OSD_DECON_CTRL_33_T                     reg_decon_ctrl_33;	//0xF3012404
	PE_O24F22_REG_OSD_DECON_CTRL_34_T                     reg_decon_ctrl_34;	//0xF3012408
	PE_O24F22_REG_OSD_DECON_CTRL_35_T                     reg_decon_ctrl_35;	//0xF301240C
	PE_O24F22_REG_OSD_DECON_CTRL_36_T                     reg_decon_ctrl_36;	//0xF3012410
	PE_O24F22_REG_OSD_DECON_CTRL_37_T                     reg_decon_ctrl_37;	//0xF3012414
	PE_O24F22_REG_OSD_DECON_CTRL_38_T                     reg_decon_ctrl_38;	//0xF3012418
	PE_O24F22_REG_OSD_DECON_CTRL_39_T                     reg_decon_ctrl_39;	//0xF301241C
	PE_O24F22_REG_OSD_DECON_CTRL_40_T                     reg_decon_ctrl_40;	//0xF3012420
	PE_O24F22_REG_OSD_DECON_CTRL_41_T                     reg_decon_ctrl_41;	//0xF3012424
	PE_O24F22_REG_OSD_DECON_CTRL_42_T                     reg_decon_ctrl_42;	//0xF3012428
	PE_O24F22_REG_OSD_DECON_CTRL_43_T                     reg_decon_ctrl_43;	//0xF301242C
	PE_O24F22_REG_OSD_DECON_CTRL_44_T                     reg_decon_ctrl_44;	//0xF3012430
	PE_O24F22_REG_OSD_DECON_CTRL_45_T                     reg_decon_ctrl_45;	//0xF3012434
	PE_O24F22_REG_OSD_DECON_CTRL_46_T                     reg_decon_ctrl_46;	//0xF3012438
	PE_O24F22_REG_OSD_DECON_CTRL_47_T                     reg_decon_ctrl_47;	//0xF301243C
	PE_O24F22_REG_OSD_DECON_CTRL_48_T                     reg_decon_ctrl_48;	//0xF3012440
	PE_O24F22_REG_OSD_DECON_CTRL_49_T                     reg_decon_ctrl_49;	//0xF3012444
	PE_O24F22_REG_OSD_DECON_CTRL_50_T                     reg_decon_ctrl_50;	//0xF3012448
	PE_O24F22_REG_OSD_DECON_CTRL_51_T                     reg_decon_ctrl_51;	//0xF301244C
	PE_O24F22_REG_OSD_DECON_CTRL_52_T                     reg_decon_ctrl_52;	//0xF3012450
	PE_O24F22_REG_OSD_DECON_CTRL_53_T                     reg_decon_ctrl_53;	//0xF3012454
	PE_O24F22_REG_OSD_DECON_CTRL_54_T                     reg_decon_ctrl_54;	//0xF3012458
	PE_O24F22_REG_OSD_DECON_CTRL_55_T                     reg_decon_ctrl_55;	//0xF301245C
	PE_O24F22_REG_OSD_DECON_CTRL_56_T                     reg_decon_ctrl_56;	//0xF3012460
	PE_O24F22_REG_OSD_DECON_CTRL_57_T                     reg_decon_ctrl_57;	//0xF3012464
	PE_O24F22_REG_OSD_DECON_CTRL_58_T                     reg_decon_ctrl_58;	//0xF3012468
	PE_O24F22_REG_OSD_DECON_CTRL_59_T                     reg_decon_ctrl_59;	//0xF301246C
	PE_O24F22_REG_OSD_DECON_CTRL_60_T                     reg_decon_ctrl_60;	//0xF3012470
	PE_O24F22_REG_OSD_DECON_CTRL_61_T                     reg_decon_ctrl_61;	//0xF3012474
	PE_O24F22_REG_OSD_DECON_CTRL_62_T                     reg_decon_ctrl_62;	//0xF3012478
	PE_O24F22_REG_OSD_DECON_CTRL_63_T                     reg_decon_ctrl_63;	//0xF301247C
	PE_O24F22_REG_OSD_DECON_CTRL_64_T                     reg_decon_ctrl_64;	//0xF3012480
	PE_O24F22_REG_OSD_DECON_CTRL_65_T                     reg_decon_ctrl_65;	//0xF3012484
	PE_O24F22_REG_OSD_DECON_CTRL_66_T                     reg_decon_ctrl_66;	//0xF3012488
	PE_O24F22_REG_OSD_DECON_CTRL_67_T                     reg_decon_ctrl_67;	//0xF301248C
	PE_O24F22_REG_OSD_DECON_CTRL_68_T                     reg_decon_ctrl_68;	//0xF3012490
	PE_O24F22_REG_OSD_DECON_CTRL_69_T                     reg_decon_ctrl_69;	//0xF3012494
	PE_O24F22_REG_OSD_DECON_CTRL_70_T                     reg_decon_ctrl_70;	//0xF3012498
	PE_O24F22_REG_OSD_DECON_CTRL_71_T                     reg_decon_ctrl_71;	//0xF301249C
	PE_O24F22_REG_OSD_DECON_CTRL_72_T                     reg_decon_ctrl_72;	//0xF30124A0
	PE_O24F22_REG_OSD_DECON_CTRL_73_T                     reg_decon_ctrl_73;	//0xF30124A4
	PE_O24F22_REG_OSD_DECON_CTRL_74_T                     reg_decon_ctrl_74;	//0xF30124A8
	PE_O24F22_REG_OSD_DECON_CTRL_75_T                     reg_decon_ctrl_75;	//0xF30124AC
	PE_O24F22_REG_OSD_DECON_CTRL_76_T                     reg_decon_ctrl_76;	//0xF30124B0
	PE_O24F22_REG_OSD_DECON_CTRL_77_T                     reg_decon_ctrl_77;	//0xF30124B4
	PE_O24F22_REG_OSD_DECON_CTRL_78_T                     reg_decon_ctrl_78;	//0xF30124B8
	PE_O24F22_REG_OSD_DECON_CTRL_79_T                     reg_decon_ctrl_79;	//0xF30124BC
	PE_O24F22_REG_OSD_DECON_CTRL_80_T                     reg_decon_ctrl_80;	//0xF30124C0
	PE_O24F22_REG_OSD_DECON_CTRL_81_T                     reg_decon_ctrl_81;	//0xF30124C4
	PE_O24F22_REG_OSD_DECON_CTRL_82_T                     reg_decon_ctrl_82;	//0xF30124C8
	PE_O24F22_REG_OSD_DECON_CTRL_83_T                     reg_decon_ctrl_83;	//0xF30124CC
	PE_O24F22_REG_OSD_DECON_CTRL_84_T                     reg_decon_ctrl_84;	//0xF30124D0
	PE_O24F22_REG_OSD_DECON_CTRL_85_T                     reg_decon_ctrl_85;	//0xF30124D4
	PE_O24F22_REG_OSD_DECON_CTRL_86_T                     reg_decon_ctrl_86;	//0xF30124D8
	PE_O24F22_REG_OSD_DECON_CTRL_87_T                     reg_decon_ctrl_87;	//0xF30124DC
	PE_O24F22_REG_OSD_DECON_CTRL_88_T                     reg_decon_ctrl_88;	//0xF30124E0
	PE_O24F22_REG_OSD_DECON_CTRL_89_T                     reg_decon_ctrl_89;	//0xF30124E4
	PE_O24F22_REG_OSD_DECON_CTRL_90_T                     reg_decon_ctrl_90;	//0xF30124E8
	PE_O24F22_REG_OSD_DECON_CTRL_91_T                     reg_decon_ctrl_91;	//0xF30124EC
	PE_O24F22_REG_OSD_DECON_CTRL_92_T                     reg_decon_ctrl_92;	//0xF30124F0
	PE_O24F22_REG_OSD_DECON_CTRL_93_T                     reg_decon_ctrl_93;	//0xF30124F4
	PE_O24F22_REG_OSD_DECON_CTRL_94_T                     reg_decon_ctrl_94;	//0xF30124F8
	PE_O24F22_REG_OSD_DECON_CTRL_95_T                     reg_decon_ctrl_95;	//0xF30124FC
	PE_O24F22_REG_OSD_DECON_CTRL_96_T                     reg_decon_ctrl_96;	//0xF3012500
	PE_O24F22_REG_OSD_DECON_CTRL_97_T                     reg_decon_ctrl_97;	//0xF3012504
	PE_O24F22_REG_OSD_DECON_CTRL_98_T                     reg_decon_ctrl_98;	//0xF3012508
	PE_O24F22_REG_OSD_DECON_CTRL_99_T                     reg_decon_ctrl_99;	//0xF301250C
	PE_O24F22_REG_OSD_DECON_CTRL_100_T                   reg_decon_ctrl_100;	//0xF3012510
	PE_O24F22_REG_OSD_DECON_CTRL_101_T                   reg_decon_ctrl_101;	//0xF3012514
	PE_O24F22_REG_OSD_DECON_CTRL_102_T                   reg_decon_ctrl_102;	//0xF3012518
	PE_O24F22_REG_OSD_DECON_CTRL_103_T                   reg_decon_ctrl_103;	//0xF301251C
	PE_O24F22_REG_OSD_DECON_CTRL_104_T                   reg_decon_ctrl_104;	//0xF3012520
	PE_O24F22_REG_OSD_DECON_CTRL_105_T                   reg_decon_ctrl_105;	//0xF3012524
	PE_O24F22_REG_OSD_DECON_CTRL_106_T                   reg_decon_ctrl_106;	//0xF3012528
	PE_O24F22_REG_OSD_DECON_CTRL_107_T                   reg_decon_ctrl_107;	//0xF301252C
	PE_O24F22_REG_OSD_DECON_CTRL_108_T                   reg_decon_ctrl_108;	//0xF3012530
	PE_O24F22_REG_OSD_DECON_CTRL_109_T                   reg_decon_ctrl_109;	//0xF3012534
	PE_O24F22_REG_OSD_DECON_CTRL_110_T                   reg_decon_ctrl_110;	//0xF3012538
	PE_O24F22_REG_OSD_DECON_CTRL_111_T                   reg_decon_ctrl_111;	//0xF301253C
	PE_O24F22_REG_OSD_DECON_CTRL_112_T                   reg_decon_ctrl_112;	//0xF3012540
	PE_O24F22_REG_OSD_DECON_CTRL_113_T                   reg_decon_ctrl_113;	//0xF3012544
	PE_O24F22_REG_OSD_DECON_CTRL_114_T                   reg_decon_ctrl_114;	//0xF3012548
	PE_O24F22_REG_OSD_DECON_CTRL_115_T                   reg_decon_ctrl_115;	//0xF301254C
	PE_O24F22_REG_OSD_DECON_CTRL_116_T                   reg_decon_ctrl_116;	//0xF3012550
	PE_O24F22_REG_OSD_DECON_CTRL_117_T                   reg_decon_ctrl_117;	//0xF3012554
	PE_O24F22_REG_OSD_DECON_CTRL_118_T                   reg_decon_ctrl_118;	//0xF3012558
	PE_O24F22_REG_OSD_DECON_CTRL_119_T                   reg_decon_ctrl_119;	//0xF301255C
	PE_O24F22_REG_OSD_DECON_CTRL_120_T                   reg_decon_ctrl_120;	//0xF3012560
	PE_O24F22_REG_OSD_DECON_CTRL_121_T                   reg_decon_ctrl_121;	//0xF3012564
	PE_O24F22_REG_OSD_DECON_CTRL_122_T                   reg_decon_ctrl_122;	//0xF3012568
	PE_O24F22_REG_OSD_DECON_CTRL_123_T                   reg_decon_ctrl_123;	//0xF301256C
}PE_CHPI_DNR_OSD_TBL_O24F22_T;

//see PE_DDR_O24_DNR_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[15];
}PE_CHPI_DNR_SQM_O24F22_T;

//see PE_DDR_O24_DCNT_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[23];
}PE_CHPI_DNR_DCNT_SQM_O24F22_T;

//see PE_DDR_O24_DCNT_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[23];
}PE_CHPI_LED_DCNT_SQM_O24F22_T;

//see PE_DDR_O24_DNR_USER_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[8];
}PE_CHPI_DNR_USER_O24F22_T;

//see PE_DDR_O24_DCNT_USER_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[8];
}PE_CHPI_DNR_DCNT_USER_O24F22_T;

//see PE_DDR_O24_DCNT_LED_USER_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[8];
}PE_CHPI_LED_DCNT_USER_O24F22_T;
#endif
