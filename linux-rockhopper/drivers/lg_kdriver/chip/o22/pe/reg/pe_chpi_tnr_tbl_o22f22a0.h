#ifndef _PE_CHPI_TNR_TBL_O22F22A0_H_
#define _PE_CHPI_TNR_TBL_O22F22A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif


typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000140 RW 0x0000_0000
	UINT32 reg_tnr_en                       :1;	//(0:0,RW,0x00) //
	UINT32 reg_hw_col_data_copy_en          :1;	//(1:1,RW,0x00) //E20
	UINT32 reg_sc_detect_hres               :1;	//(2:2,RW,0x00) //
	UINT32 reg_clc_nt_pal                   :1;	//(3:3,RW,0x00) //
	UINT32 reg_clc_mem_wr_mode              :2;	//(5:4,RW,0x00) //
	UINT32 reg_sad_8x3_res                  :2;	//(7:6,RW,0x00) //
	UINT32 reg_sad_8x3_iir_en               :1;	//(8:8,RW,0x00) //
	UINT32 reg_sad_8x3_chroma_en            :1;	//(9:9,RW,0x00) //
	UINT32 reg_minfo_sw                     :2;	//(11:10,RW,0x00) //
	UINT32 reg_minfo_mode10                 :2;	//(13:12,RW,0x00) //[0] minfo debug enable : ipc_m, ipc_st, tnr_m, tnr_mv, clc
	UINT32 reg_minfo_flt                    :2;	//(15:14,RW,0x00) //
	UINT32 reg_tnr_single_en                :1;	//(16:16,RW,0x00) //TNR half_rate	: This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 reg_decon_blend_en               :1;	//(17,RW,0x0) //chg
	UINT32 reg_minfo_mode32                 :2;	//(19:18,RW,0x00) //
	UINT32 reg_minfo_mode74                 :4;	//(23:20,RW,0x00) //
	UINT32 reg_sad_8x3_iir_alpha            :8;	//(31:24,RW,0x0) //for TNR, DNR
	};
	};
}PE_O22F22_ND0_TNR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000144 RW 0x0000_0000
	UINT32 reg_dbg_show                     :4;	//(3:0,RW,0x00) //
	UINT32 reg_ma_motion_iir_alpha          :8;	//(11:4,RW,0x00) //for decontour, new
	UINT32 reg_ma_motion_iir_en             :1;	//(12,RW,0x0) //for decontour, new
	UINT32 reg_ma_motion_chroma_en          :1;	//(13,RW,0x0) //for decontour, new
	UINT32 reg_ma_motion_res                :2;	//(15:14,RW,0x0) //for decontour, new
	UINT32 reg_dbg_tnrw                     :2;	//(17:16,RW,0x00) //TNR WriteÎ•??†ÌÉù?©Îãà?? 	0 = TNR Ï∂úÎ†• (T)	1 = TNR ?ÑÏû¨ ?ÖÎ†• (T)	2 = TNR ?¥Ï†Ñ ?ÖÎ†• (T-1)
	UINT32 reg_ma_motion_lsb6_sel           :1;	//(18,RW,0x0) //for decontour, new
	UINT32 reg_sad_8x3_lsb6_sel             :1;	//(19,RW,0x0) //new
	UINT32 reg_tnri_debug_mode              :2;	//(21:20,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 reg_minfo_mode118                :4;	//(27:24,RW,0x00) //
	UINT32 reg_sc_scale2                    :3;	//(30:28,RW,0x00) //
	UINT32 resvd1                           :1;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000148 RW 0x0000_0000
	UINT32 sc_en                            :1;	//(0,RW,0x0) //scene change detection enable
	UINT32 sc_max_flt_en                    :1;	//(1,RW,0x0) //scene change: temporal max filter enable
	UINT32 sc_calc_prev_hist                :1;	//(2,RW,0x0) //scene change: calculation mode for previous histogram	0:= delay current histogram	1 = compute histogram for previous data
	UINT32 sc_chroma_en                     :1;	//(3,RW,0x00) //scene change: use of chroma histogram difference
	UINT32 sc_scale                         :3;	//(6:4,RW,0x0) //bit-select from 21bit scene change measure to 8-bit measure	0 := sc_measure[21 -1 :21-8]	1 = sc_measure [21 -3 :21-10]	2 = sc_measure [21 -5 :21-12]	3 = sc_measure [21 -7 :21-14]	4 = sc_measure [21 -9 :21-16]	5 = sc_measure [21-11:21-18]	6 = sc_measure [21-13:21-20]	7 = sc_measure [21-141:21-21]
	UINT32 resvd0                           :1;
	UINT32 sc_max_flt_tap                   :3;	//(10:8,RW,0x0) //scene change: temporal max filter tap
	UINT32 resvd1                           :1;
	UINT32 sc_chroma_gain                   :3;	//(14:12,RW,0x0) //scene change: gain of chroma histogram difference	0 := x1	1 = x1/2	2 = x1/4	3 = x1/8	4 = x1/16	5 = x1/32
	UINT32 sc_out_mode                      :1;	//(15,RW,0x00) //TNR_STATUS_04: scene change measure update mode	0:= update every frame	1 = update only if the scene_measure is larger than "sc_th_memc"
	UINT32 sc_th_ma                         :8;	//(23:16,RW,0x00) //scene change threshold for MA
	UINT32 sc_th_memc                       :8;	//(31:24,RW,0x00) //scene change threshold for MEMC
	};
	};
}PE_O22F22_ND0_TNR_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF200014C RW 0x0000_0000
	UINT32 show_dbg_bar_scale               :3;	//(2:0,RW,0x00) //debug bar scale
	UINT32 resvd0                           :1;
	UINT32 show_dbg_bar_en                  :4;	//(7:4,RW,0x00) //debug bar enable
	UINT32 resvd1                           :8;
	UINT32 show_dbg_bar0_mux                :4;	//(19:16,RW,0x00) //input mux for the lowest debug bar	0x0 := x_peak	0x1 = motion vector variance	0x2 = motion vector H	0x3 = motion vector V	0x4 = abs(NR-P2)	0x5 = abs(NR-CC)	0x6 = MA motion	0x7 = spatial variance	0x8 = scene change
	UINT32 show_dbg_bar1_mux                :4;	//(23:20,RW,0x00) //input mux for 2nd debug bar
	UINT32 show_dbg_bar2_mux                :4;	//(27:24,RW,0x00) //input mux for 3rd debug bar
	UINT32 show_dbg_bar3_mux                :4;	//(31:28,RW,0x00) //input mux for the highest debug bar
	};
	};
}PE_O22F22_ND0_TNR_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000150 RW 0x0000_0000
	UINT32 manual_debug_bar_09              :8;	//(7:0,RW,0x0) //for manual debug mode ( reg_mux : 1001)
	UINT32 manual_debug_bar_10              :8;	//(15:8,RW,0x0) //for manual debug mode ( reg_mux : 1010)
	UINT32 manual_debug_bar_11              :8;	//(23:16,RW,0x0) //for manual debug mode ( reg_mux : 1011)
	UINT32 manual_debug_bar_12              :8;	//(31:24,RW,0x0) //for manual debug mode ( reg_mux : 1100)
	};
	};
}PE_O22F22_ND0_TNR_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;	struct {						//0xF2000154 RW 0x0000_0000
	UINT32 reg_mamc_blend_mode              :2;	//(1:0,RW,0x00) //
	UINT32 reg_mamc_blend_mv_max_or_sum     :1;	//(2,RW,0x00) //0: max, 1: sum
	UINT32 reg_mamc_ma_sad_cut              :1;	//(3,RW,0x00) //0: 6b, 1:2b
	UINT32 reg_mamc_mc_sad_cut              :1;	//(4,RW,0x00) //0: 6b, 1:2b
	UINT32 resvd0                           :11;
	UINT32 reg_mv_pv_fix_v                  :4;	//(19:16,RW,0x00) //
	UINT32 reg_mv_pv_fix_h                  :5;	//(24:20,RW,0x0) //
	UINT32 resvd1                           :6;
	UINT32 reg_mv_pv_fix_en                 :1;	//(31,RW,0x00) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000158 RW 0x0000_0000
	UINT32 reg_me_lb_base                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_me_pv_base                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_me_lb_polarity               :1;	//(16,RW,0x00) //
	UINT32 resvd                            :15;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF200015C RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//(5:4,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_sc_en                        :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :23;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000160 RW 0x0000_0000
	UINT32 reg_mv_h_fix_val                 :5;	//(4:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_mv_v_fix_val                 :4;	//(11:8,RW,0x00) //
	UINT32 reg_mv_h_fix_fb_val              :5;	//(16:12,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_mv_v_fix_fb_val              :4;	//(23:20,RW,0x00) //
	UINT32 reg_debug_sel                    :4;	//(27:24,RW,0x00) //
	UINT32 reg_lb_monitor_sel               :2;	//(29:28,RW,0x00) //
	UINT32 reg_mv_fb_fix                    :1;	//(30,RW,0x00) //
	UINT32 reg_mv_fix                       :1;	//(31,RW,0x00) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000164 RW 0x0000_0000
	UINT32 reg_sad_base                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lb_smooth_clip               :6;	//(13:8,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_pv_smooth_clip               :6;	//(21:16,RW,0x0) //
	UINT32 resvd2                           :10;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000168 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF200016C RW 0x8000_0000
	UINT32 lb_smooth_en                     :1;	//(0,RW,0x0) //
	UINT32 pv_smooth_en                     :1;	//(1,RW,0x0) //
	UINT32 pmv_hist_en                      :1;	//(2,RW,0x0) //new
	UINT32 reg_yonly_me_en                  :1;	//(3,RW,0x0) //new
	UINT32 resvd                            :27;
	UINT32 reg_me_n15_protection            :1;	//(31,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000170 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000174 RW 0x0000_0000
	UINT32 reg_min_sad_ratio                :8;	//(7:0,RW,0x00) //new
	UINT32 reg_lb_cost_ratio                :8;	//(15:8,RW,0x00) //new
	UINT32 reg_zero_sad_ratio               :8;	//(23:16,RW,0x00) //new
	UINT32 reg_zero_mv_blk_mv_sel           :2;	//(25:24,RW,0x0) //chg
	UINT32 resvd0                           :2;
	UINT32 reg_zero_sad_adv                 :1;	//(28,RW,0x0) //chg
	UINT32 resvd1                           :3;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000178 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF200017C RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000180 RW 0x0000_0000
	UINT32 reg_sad_acc_mode                 :2;	//(1:0,RW,0x00) //
	UINT32 reg_bmv_fix_en                   :1;	//(2,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 reg_bmv_fix_v                    :4;	//(7:4,RW,0x00) //
	UINT32 reg_bmv_fix_h                    :5;	//(12:8,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_n_hblk                       :4;	//(19:16,RW,0x00) //
	UINT32 reg_n_vblk                       :5;	//(24:20,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_use_fw_gmv_en                :1;	//(29,RW,0x0) //new
	UINT32 reg_col_overlap_en               :1;	//(30,RW,0x0) //new
	UINT32 reg_col_data_share_en            :1;	//(31,RW,0x0) //new
	};
	};
}PE_O22F22_ND0_TNR_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000184 RW 0x0000_0000
	UINT32 reg_blk_vsize                    :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_blk_hsize                    :12;	//(27:16,RW,0x00) //
	UINT32 resvd1                           :4;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000188 RW 0x0000_0000
	UINT32 reg_bsad_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 reg_bmv_rst_mode                 :1;	//(3,RW,0x00) //
	UINT32 reg_gsad_scale                   :3;	//(6:4,RW,0x00) //
	UINT32 resvd                            :1;
	UINT32 reg_gmv_gmv_tl                   :7;	//(14:8,RW,0x0) //
	UINT32 reg_gmv_gmv_tl_en                :1;	//(15,RW,0x0) //
	UINT32 reg_bmv_gmv_tl                   :7;	//(22:16,RW,0x0) //
	UINT32 reg_bmv_gmv_tl_en                :1;	//(23,RW,0x0) //
	UINT32 reg_bmv_pmv_tl                   :7;	//(30:24,RW,0x0) //
	UINT32 reg_bmv_pmv_tl_en                :1;	//(31,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF200018C RW 0x0000_0000
	UINT32 bmv_coring_th                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_col_overlap_mode             :2;	//(9:8,RW,0x0) //new
	UINT32 resvd0                           :2;
	UINT32 reg_tl_equal_off                 :1;	//(12,RW,0x0) //new
	UINT32 resvd1                           :3;
	UINT32 gmv_0mv_tl                       :7;	//(22:16,RW,0x0) //0MV ?ÅÌñ•?•Ïùò Í∞ïÎèÑ Ï°∞Ï†à : x10??bypass?¥Í≥† ?íÏùÑ ?òÎ°ù Í∞ïÌïòÍ≤??ÅÌñ•??Ï§?
	UINT32 gmv_0mv_tl_en                    :1;	//(23,RW,0x00) //Global MV??0MV Î≥¥ÎÑà?§Î? Ï§?Í≤ÉÏù∏Í∞Ä?
	UINT32 bmv_0mv_tl                       :7;	//(30:24,RW,0x0) //0MV ?ÅÌñ•?•Ïùò Í∞ïÎèÑ Ï°∞Ï†à : x10??bypass?¥Í≥† ?íÏùÑ ?òÎ°ù Í∞ïÌïòÍ≤??ÅÌñ•??Ï§?
	UINT32 bmv_0mv_tl_en                    :1;	//(31,RW,0x00) //Large Block MV??0MV Î≥¥ÎÑà?§Î? Ï§?Í≤ÉÏù∏Í∞Ä?
	};
	};
}PE_O22F22_ND0_TNR_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000190 RW 0x0000_0000
	UINT32 reg_detail_beta_mul              :8;	//(7:0,RW,0x0) //
	UINT32 reg_detail_alpha_mul             :8;	//(15:8,RW,0x0) //
	UINT32 reg_edge_beta_mul                :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_alpha_mul               :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000194 RW 0x0000_0000
	UINT32 reg_svar_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 reg_sad_8x3_res2                 :2;	//(9:8,RW,0x00) //
	UINT32 resvd1                           :22;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000198 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF200019C RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001A0 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 reg_ombc_en                      :1;	//(1,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_luma_gain_en                 :1;	//(4,RW,0x00) //
	UINT32 reg_crgn_gain_en                 :1;	//(5,RW,0x00) //
	UINT32 reg_chroma_sad_res               :2;	//(7:6,RW,0x00) //
	UINT32 resvd2                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//(13:12,RW,0x00) //
	UINT32 resvd3                           :2;
	UINT32 reg_avg_cmp_en                   :1;	//(16,RW,0x00) //
	UINT32 reg_avg_cmp_res                  :3;	//(19:17,RW,0x00) //
	UINT32 reg_debug_sel                    :4;	//(23:20,RW,0x00) //
	UINT32 resvd4                           :4;
	UINT32 reg_cnt_mode                     :3;	//(30:28,RW,0x00) //
	UINT32 reg_chroma_sad_en                :1;	//(31,RW,0x00) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001A4 RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_skin_master_gain             :8;	//(31:24,RW,0xFF) //new
	};
	};
}PE_O22F22_ND0_TNR_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001A8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001AC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001B0 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001B4 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001B8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001BC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001C0 RO 0x0000_0000
	UINT32 w_gsad                           :8;	//(7:0,RO,0x0) //
	UINT32 w_gmv_h                          :5;	//(12:8,RO,0x00) //
	UINT32 w_gmv_v                          :4;	//(16:13,RO,0x00) //
	UINT32 resvd                            :7;
	UINT32 w_apl_detail                     :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_STATUS_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001C4 RO 0x0000_0000
	UINT32 w_apl_motion                     :8;	//(7:0,RO,0x0) //
	UINT32 w_apl_mc_sad                     :8;	//(15:8,RO,0x0) //
	UINT32 w_apl_var                        :8;	//(23:16,RO,0x0) //
	UINT32 w_apl_edge                       :8;	//(31:24,RO,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_STATUS_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001C8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O22F22_ND0_TNR_STATUS_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001CC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
	};
}PE_O22F22_ND0_TNR_STATUS_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001D0 RW 0x0000_0000
	UINT32 main_lut_indir_addr              :6;	//(5:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 main_lut_ai_enable               :1;	//(12,RW,0x00) //TNR Main-LUT Ctrl. AI enable
	UINT32 resvd1                           :2;
	UINT32 main_lut_load                    :1;	//(15,RW,0x00) //
	UINT32 resvd2                           :16;
	};
	};
}PE_O22F22_ND0_TNR_MAIN_LUT_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001D4 RW 0x0000_0000
	UINT32 main_lut_indir_data0             :32;	//(31:0,RW,0x0000_0000) //TNR Main-LUT Ctrl. Indirect Access Data 0 63:32 (MSB8u:Biggest, LSB8u:Smallest)
	};
	};
}PE_O22F22_ND0_TNR_MAIN_LUT_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001DC RO 0x0000_0000
	UINT32 sc_measure                       :8;	//(7:0,RO,0x0) //scene change detection measure
	UINT32 apl_y                            :8;	//(15:8,RO,0x0) //
	UINT32 sc_measure_16                    :16;	//(31:16,RO,0x0) //scene change measure (16b)
	};
	};
}PE_O22F22_ND0_TNR_STATUS_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001E0 RW 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 reg_gf_gain                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_blur_coef                    :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_32_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001E4 RW 0x0000_0000
	UINT32 same_protection_en               :1;	//(0,RW,0x00) //
	UINT32 reg_p_mv0_only                   :1;	//(1,RW,0x00) //
	UINT32 reg_p_non_mv0_only               :1;	//(2,RW,0x00) //new
	UINT32 reg_final_lut_en                 :1;	//(3,RW,0x00) //new
	UINT32 resvd0                           :4;
	UINT32 reg_same_sad_th                  :8;	//(15:8,RW,0x00) //
	UINT32 reg_move_step                    :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_33_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001E8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_34_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001EC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_35_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001F0 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_36_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001F4 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_37_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001F8 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_38_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20001FC RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_39_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20002E0 RW 0x0000_0000
	UINT32 mmd_vtap_yy                      :2;	//(1:0,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd0                           :2;
	UINT32 mmd_htap_yy                      :2;	//(5:4,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd1                           :2;
	UINT32 mmd_vtap_cc                      :2;	//(9:8,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd2                           :2;
	UINT32 mmd_htap_cc                      :2;	//(13:12,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd3                           :2;
	UINT32 reg_chroma_mmd_en                :1;	//(16,RW,0x00) //0 := off	1 := on
	UINT32 resvd4                           :15;
	};
	};
}PE_O22F22_ND0_MMD_CTRL_T;


typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003D0 RW 0x0000_0000
	UINT32 resvd0                           :2;
	UINT32 reg_a_normalize_en               :1;	//(2,RW,0x00) //
	UINT32 reg_t_normalize_en               :1;	//(3,RW,0x00) //
	UINT32 reg_t_cut_resolution             :2;	//(5:4,RW,0x00) //
	UINT32 reg_ne_normalize_en              :1;	//(6,RW,0x00) //
	UINT32 resvd1                           :9;
	UINT32 reg_cross_th_ne                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_cross_th                     :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_40_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003D4 RW 0x0000_0000
	UINT32 reg_mul_base_t                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_mul_base_e                   :8;	//(15:8,RW,0x0) //
	UINT32 resvd                            :16;
	};
	};
}PE_O22F22_ND0_TNR_CTRL_41_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003D8 RW 0x0000_0000
	UINT32 reg_a_lut_edge_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_a_lut_edge_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_a_lut_edge_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_a_lut_edge_x1                :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_42_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003DC RW 0x0000_0000
	UINT32 reg_a_lut_detail_y0              :8;	//(7:0,RW,0x0) //
	UINT32 reg_a_lut_detail_x0              :8;	//(15:8,RW,0x0) //
	UINT32 reg_a_lut_detail_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_a_lut_detail_x1              :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_43_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003E0 RW 0x0000_0000
	UINT32 reg_t_lut_edge_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_t_lut_edge_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_t_lut_edge_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_t_lut_edge_x1                :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_44_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003E4 RW 0x0000_0000
	UINT32 reg_t_lut_detail_y0              :8;	//(7:0,RW,0x0) //
	UINT32 reg_t_lut_detail_x0              :8;	//(15:8,RW,0x0) //
	UINT32 reg_t_lut_detail_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_t_lut_detail_x1              :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003E8 RW 0x0000_0000
	UINT32 reg_edge_minmax_y0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_edge_minmax_x0               :8;	//(15:8,RW,0x0) //
	UINT32 reg_edge_minmax_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_minmax_x1               :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_46_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003EC RW 0x0000_0000
	UINT32 reg_detail_minmax_y0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_detail_minmax_x0             :8;	//(15:8,RW,0x0) //
	UINT32 reg_detail_minmax_y1             :8;	//(23:16,RW,0x0) //
	UINT32 reg_detail_minmax_x1             :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_47_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20003F0 RW 0x0000_0000
	UINT32 reg_sel_ne_type                  :2;	//(1:0,RW,0x00) //0:(Y - TNR_Y), 1:(Y - SNR_Y), 2:(C - SNR_C)
	UINT32 reg_sel_re_type                  :1;	//(2,RW,0x00) //0:(still region), 1:(flat region)
	UINT32 resvd0                           :1;
	UINT32 reg_sel_at_mode                  :2;	//(5:4,RW,0x00) //0:(A), 1:(T), 2:(max(A,T)), 3:(A,T separate)
	UINT32 resvd1                           :2;
	UINT32 reg_hist_xscale                  :3;	//(10:8,RW,0x00) //histogram x-axi resolution ( 0: 0,1,2??, 1: 0,2,4??
	UINT32 resvd2                           :1;
	UINT32 reg_hist_yscale                  :2;	//(13:12,RW,0x00) //histogram cut resolution
	UINT32 resvd3                           :2;
	UINT32 reg_th_atmap                     :8;	//(23:16,RW,0x0) //at_map threshold ( flat rgion valid threshold )
	UINT32 reg_th_motion                    :8;	//(31:24,RW,0x0) //motion threshiold ( still region valid threshold )
	};
	};
}PE_O22F22_ND0_TNR_CTRL_48_T;


typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF2000498 RW 0x0000_0000
	UINT32 minfo_tnr_rd_m_delay             :4;	//(3:0,RW,0x00) //0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd0                           :4;
	UINT32 minfo_tnr_rd_mv_delay            :4;	//(11:8,RW,0x00) //0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd1                           :4;
	UINT32 minfo_tnr_wr_m_delay             :4;	//(19:16,RW,0x00) //0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	UINT32 minfo_lstart_delay               :4;	//(23:20,RW,0x00) //0 := delay (-4)	1 = delay (-3)	2 = delay (-2)	3 = delay (-1)	4 = delay ( 0)	5 = delay (+1)	6 = delay (+2)	7 = delay (+3)
	UINT32 minfo_clc_offset                 :2;	//(25:24,RW,0x00) //
	UINT32 resvd2                           :2;
	UINT32 minfo_tnr_wr_mv_delay            :4;	//(31:28,RW,0x00) //0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	};
	};
}PE_O22F22_ND0_TNR_ETC_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20004A0 RW 0x0000_0000
	UINT32 reg_sad_mc_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_56_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20004A4 RW 0x0000_0000
	UINT32 reg_sad_mc_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_57_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20004A8 RW 0x0000_0000
	UINT32 reg_abs_mv_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_58_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20004AC RW 0x0000_0000
	UINT32 reg_abs_mv_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_59_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20004B0 RW 0x0000_0000
	UINT32 reg_sad_ma_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_60_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF20004B4 RW 0x0000_0000
	UINT32 reg_sad_ma_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
	};
}PE_O22F22_ND0_TNR_CTRL_61_T;

typedef struct {
	PE_O22F22_ND0_TNR_CTRL_00_T                                   tnr_ctrl_00;	//0xF2000140
	PE_O22F22_ND0_TNR_CTRL_01_T                                   tnr_ctrl_01;	//0xF2000144
	PE_O22F22_ND0_TNR_CTRL_02_T                                   tnr_ctrl_02;	//0xF2000148
	PE_O22F22_ND0_TNR_CTRL_03_T                                   tnr_ctrl_03;	//0xF200014C
	PE_O22F22_ND0_TNR_CTRL_04_T                                   tnr_ctrl_04;	//0xF2000150
	PE_O22F22_ND0_TNR_CTRL_05_T                                   tnr_ctrl_05;	//0xF2000154
	PE_O22F22_ND0_TNR_CTRL_06_T                                   tnr_ctrl_06;	//0xF2000158
	PE_O22F22_ND0_TNR_CTRL_07_T                                   tnr_ctrl_07;	//0xF200015C
	PE_O22F22_ND0_TNR_CTRL_08_T                                   tnr_ctrl_08;	//0xF2000160
	PE_O22F22_ND0_TNR_CTRL_09_T                                   tnr_ctrl_09;	//0xF2000164
	PE_O22F22_ND0_TNR_CTRL_10_T                                   tnr_ctrl_10;	//0xF2000168
	PE_O22F22_ND0_TNR_CTRL_11_T                                   tnr_ctrl_11;	//0xF200016C
	PE_O22F22_ND0_TNR_CTRL_12_T                                   tnr_ctrl_12;	//0xF2000170
	PE_O22F22_ND0_TNR_CTRL_13_T                                   tnr_ctrl_13;	//0xF2000174
	PE_O22F22_ND0_TNR_CTRL_14_T                                   tnr_ctrl_14;	//0xF2000178
	PE_O22F22_ND0_TNR_CTRL_15_T                                   tnr_ctrl_15;	//0xF200017C
	PE_O22F22_ND0_TNR_CTRL_16_T                                   tnr_ctrl_16;	//0xF2000180
	PE_O22F22_ND0_TNR_CTRL_17_T                                   tnr_ctrl_17;	//0xF2000184
	PE_O22F22_ND0_TNR_CTRL_18_T                                   tnr_ctrl_18;	//0xF2000188
	PE_O22F22_ND0_TNR_CTRL_19_T                                   tnr0_ctrl_19;	//0xF200018C
	PE_O22F22_ND0_TNR_CTRL_19_T                                   tnr1_ctrl_19;	//0xF200318C
	PE_O22F22_ND0_TNR_CTRL_19_T                                   tnr2_ctrl_19;	//0xF200518C
	PE_O22F22_ND0_TNR_CTRL_19_T                                   tnr3_ctrl_19;	//0xF200718C
	PE_O22F22_ND0_TNR_CTRL_20_T                                   tnr_ctrl_20;	//0xF2000190
	PE_O22F22_ND0_TNR_CTRL_21_T                                   tnr_ctrl_21;	//0xF2000194
	PE_O22F22_ND0_TNR_CTRL_22_T                                   tnr_ctrl_22;	//0xF2000198
	PE_O22F22_ND0_TNR_CTRL_23_T                                   tnr_ctrl_23;	//0xF200019C
	PE_O22F22_ND0_TNR_CTRL_24_T                                   tnr_ctrl_24;	//0xF20001A0
	PE_O22F22_ND0_TNR_CTRL_25_T                                   tnr_ctrl_25;	//0xF20001A4
	PE_O22F22_ND0_TNR_CTRL_26_T                                   tnr_ctrl_26;	//0xF20001A8
	PE_O22F22_ND0_TNR_CTRL_27_T                                   tnr_ctrl_27;	//0xF20001AC
	PE_O22F22_ND0_TNR_CTRL_28_T                                   tnr_ctrl_28;	//0xF20001B0
	PE_O22F22_ND0_TNR_CTRL_29_T                                   tnr_ctrl_29;	//0xF20001B4
	PE_O22F22_ND0_TNR_CTRL_30_T                                   tnr_ctrl_30;	//0xF20001B8
	PE_O22F22_ND0_TNR_CTRL_31_T                                   tnr_ctrl_31;	//0xF20001BC
	PE_O22F22_ND0_TNR_CTRL_32_T                                   tnr_ctrl_32;	//0xF20001E0
	PE_O22F22_ND0_TNR_CTRL_33_T                                   tnr_ctrl_33;	//0xF20001E4
	PE_O22F22_ND0_TNR_CTRL_34_T                                   tnr_ctrl_34;	//0xF20001E8
	PE_O22F22_ND0_TNR_CTRL_35_T                                   tnr_ctrl_35;	//0xF20001EC
	PE_O22F22_ND0_TNR_CTRL_36_T                                   tnr_ctrl_36;	//0xF20001F0
	PE_O22F22_ND0_TNR_CTRL_37_T                                   tnr_ctrl_37;	//0xF20001F4
	PE_O22F22_ND0_TNR_CTRL_38_T                                   tnr_ctrl_38;	//0xF20001F8
	PE_O22F22_ND0_TNR_CTRL_39_T                                   tnr_ctrl_39;	//0xF20001FC
	PE_O22F22_ND0_MMD_CTRL_T                                         mmd_ctrl;	//0xF20002E0
	PE_O22F22_ND0_TNR_CTRL_40_T                                   tnr_ctrl_40;	//0xF20003D0
	PE_O22F22_ND0_TNR_CTRL_41_T                                   tnr_ctrl_41;	//0xF20003D4
	PE_O22F22_ND0_TNR_CTRL_42_T                                   tnr_ctrl_42;	//0xF20003D8
	PE_O22F22_ND0_TNR_CTRL_43_T                                   tnr_ctrl_43;	//0xF20003DC
	PE_O22F22_ND0_TNR_CTRL_44_T                                   tnr_ctrl_44;	//0xF20003E0
	PE_O22F22_ND0_TNR_CTRL_45_T                                   tnr_ctrl_45;	//0xF20003E4
	PE_O22F22_ND0_TNR_CTRL_46_T                                   tnr_ctrl_46;	//0xF20003E8
	PE_O22F22_ND0_TNR_CTRL_47_T                                   tnr_ctrl_47;	//0xF20003EC
	PE_O22F22_ND0_TNR_CTRL_48_T                                   tnr_ctrl_48;	//0xF20003F0
	PE_O22F22_ND0_TNR_ETC_CTRL_02_T                           tnr_etc_ctrl_02;	//0xF2000498
	PE_O22F22_ND0_TNR_CTRL_56_T                                   tnr_ctrl_56;	//0xF20004A0
	PE_O22F22_ND0_TNR_CTRL_57_T                                   tnr_ctrl_57;	//0xF20004A4
	PE_O22F22_ND0_TNR_CTRL_58_T                                   tnr_ctrl_58;	//0xF20004A8
	PE_O22F22_ND0_TNR_CTRL_59_T                                   tnr_ctrl_59;	//0xF20004AC
	PE_O22F22_ND0_TNR_CTRL_60_T                                   tnr_ctrl_60;	//0xF20004B0
	PE_O22F22_ND0_TNR_CTRL_61_T                                   tnr_ctrl_61;	//0xF20004B4
}PE_CHPI_TNR_TBL_O22F22_T;

//see PE_DDR_O22_TNR_SQM_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[11];
}PE_CHPI_TNR_SQM_O22F22_T;

//see LX_PE_NRD_TNR1_CMN_LUT__SIZE
//see LX_PE_NRD_TNR1_CMN_GAIN_SIZE
//see LX_PE_NRD_TNR1_CMN_BUFF_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[36];
}PE_CHPI_TNR_USER_O22F22_T;

#endif
