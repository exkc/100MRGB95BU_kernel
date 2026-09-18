#ifndef _PE_SRE_REG_O26A0_H_
#define _PE_SRE_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00200 RW 0x0000_0000
	UINT32 reg_sys_veri_0                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_SRE_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00204 RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_SRE_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00208 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_SRE_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0020C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_SRE_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O26_SRE_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCCA00200
	PE_O26_SRE_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xCCA00204
	PE_O26_SRE_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xCCA00208
	PE_O26_SRE_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xCCA0020C
}PE_SRE_VERI_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00C00 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 reg_iir_rst                      :1;	//(6:6,NA,0) //Tmap/Text IIR reset (reset to first frame)
	UINT32 resvd1                           :1;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :23;
	};
}PE_O26_2KY_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00C04 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //Processing width  (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //Processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00C08 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O26_2KY_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00C0C RW 0x000A_0000
	UINT32 resvd0                           :16;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,10) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00C40 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //Pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //Pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //Pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O26_2KY_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00C60 RW 0x1000_0A05
	UINT32 reg_gain_map_mmd_div             :4;	//(3:0,NA,5) //3x3 MMD division
	UINT32 reg_gain_map_mmd_mul             :4;	//(7:4,NA,0) //3x3 MMD multiplication
	UINT32 reg_gain_map_mmd_offset          :8;	//(15:8,NA,10) //3x3 MMD offset
	UINT32 resvd0                           :12;
	UINT32 reg_gain_map_mmd_3x3_en          :1;	//(28:28,NA,1) //3x3 MMD multiplication
	UINT32 resvd1                           :3;
	};
}PE_O26_2KY_SHP_GAIN_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00CF0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //Debug display	0 : Nnormal display (output 1)	1 : Normal display (output 2)	2 : TGEN only	3 : Luma adaptive gain map	4 : Weight(A)	5 : Weight(Texture)	6 : A-map	7 : T-map	8 : Soft edge gain map	9 : A-map for der	10: Motion map	11: Text gain map	12: Non-text gain map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //DP detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //DP buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O26_2KY_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D00 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //Post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //Pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //Pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //Pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D08 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //Get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //Get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O26_2KY_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D0C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D10 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D14 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D18 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D1C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D20 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O26_2KY_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D24 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D28 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O26_2KY_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D2C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //Edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //Texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D30 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O26_2KY_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D34 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O26_2KY_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D38 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D3C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O26_2KY_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D40 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O26_2KY_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D44 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O26_2KY_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D48 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O26_2KY_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D4C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O26_2KY_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D50 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O26_2KY_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D54 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //Input selection for flat region LUT	0: a_map	1: t_map	2: max(a_map,t_map)	3: min(255,a_map+t_map) (default)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //Add a flat gain to A-map enable
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //Add a flat gain to T-map enable
	UINT32 resvd2                           :23;
	};
}PE_O26_2KY_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D58 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O26_2KY_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D60 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O26_2KY_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D64 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O26_2KY_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D68 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_2KY_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D6C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_2KY_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D70 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_2KY_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D74 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D78 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //Gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_2KY_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D7C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_2KY_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D80 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //Level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //Level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_2KY_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D84 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //Level-balancing, lum2_y0
	};
}PE_O26_2KY_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D88 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //Level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_2KY_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D8C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D90 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00D94 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_O26_2KY_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DA0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 resvd                            :7;
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //Center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //Center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //Local gain
	};
}PE_O26_2KY_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DA4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //Gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //Gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //Gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //Gain balancing, x1
	};
}PE_O26_2KY_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DA8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //Gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //Gain balancing, x3
	};
}PE_O26_2KY_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DAC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DB0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DC0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O26_2KY_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DC4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //Bilateral filter tap size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //Edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //Edge filter en
	};
}PE_O26_2KY_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DC8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //Edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //Edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O26_2KY_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DCC RW 0x0006_5008
	UINT32 reg_derv_en                      :1;	//(0:0,NA,0) //DER-V enable
	UINT32 resvd0                           :2;
	UINT32 reg_derv_bif_en                  :1;	//(3:3,NA,1) //Bilateral filter	0: disable	1: enable
	UINT32 reg_derv_output_mux              :4;	//(7:4,NA,0) //Display mode	0xxx: normal display	1000: vertical ringing measure	1001: gain adjusted by curve mapping	101x: bilateral filter output	o.w : not used
	UINT32 reg_derv_bif_manual_th           :8;	//(15:8,NA,80) //Bilateral filter threshold
	UINT32 reg_derv_th_gain                 :6;	//(21:16,NA,6) //Auto threshold gain, th = th_gain * A
	UINT32 resvd1                           :2;
	UINT32 reg_derv_th_mode                 :1;	//(24:24,NA,0) //Threshold mode	0: auto(A-map)	1: manual
	UINT32 resvd2                           :7;
	};
}PE_O26_2KY_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DD0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //Center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //Center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_O26_2KY_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DD4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //Gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //Gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_O26_2KY_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DD8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O26_2KY_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DDC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O26_2KY_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DE0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O26_2KY_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DE4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DE8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_2KY_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DEC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_2KY_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DF0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_2KY_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DF4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DF8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //Gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_2KY_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00DFC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_2KY_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E00 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //Level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //Level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_2KY_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E04 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //Level-balancing, lum2_y0
	};
}PE_O26_2KY_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E08 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //Level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_2KY_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E0C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E10 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E20 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //Min-max tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //Average tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_2KY_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E24 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //Min-max tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //Average tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_2KY_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E28 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E2C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E30 RW 0x1010_2014
	UINT32 reg_sti_enable                   :1;	//(0:0,NA,0) //STI enable
	UINT32 reg_sti_debug_map_en             :1;	//(1:1,NA,0) //Debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//(3:2,NA,1) //Min-max tap size
	UINT32 reg_sti_avg_tap_size             :2;	//(5:4,NA,1) //Average tap size
	UINT32 reg_sti_ti_mode                  :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//(15:8,NA,32) //Master gain
	UINT32 reg_sti_texture_gain             :8;	//(23:16,NA,16) //Texture gain
	UINT32 reg_sti_edge_gain                :8;	//(31:24,NA,16) //Edge gain
	};
}PE_O26_2KY_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E40 RW 0x8000_0011
	UINT32 reg_tgen_on_off                  :1;	//(0:0,NA,1) //TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//(4:4,NA,1) //Manual seed mode for rand val
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//(8:8,NA,0) //Debug mode enable
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//(19:16,NA,0) //Mode for rand val
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//(31:24,NA,128) //Master gain
	};
}PE_O26_2KY_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E44 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //R clipping bound for delta
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //L clipping bound for delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //Max threshold for delta
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //Scale factor for delta
	UINT32 resvd3                           :5;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E48 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //Rand val threshold
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //Weight for curr for delta
	UINT32 resvd                            :20;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E4C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //Initial seed value for manual seed mode
	};
}PE_O26_2KY_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E54 RW 0x0202_1F04
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //Min-max offset
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //Min-max selection mode
	UINT32 resvd2                           :6;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E58 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //Rand scale factor for noise delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //Min-max scale factor for noise delta
	UINT32 resvd2                           :3;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E5C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //Noise blur coefficient, x2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //Noise blur coefficient, x1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //Noise blur coefficient, x0
	UINT32 resvd2                           :2;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E60 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //Noise blur coefficient, y2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //Noise blur coefficient, y1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //Noise blur coefficient, y0
	UINT32 resvd2                           :2;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E64 RW 0x3F80_1F1F
	UINT32 resvd0                           :24;
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //Noise gain
	UINT32 resvd1                           :2;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E68 RW 0x48AB_CDFF
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E6C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E70 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E74 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //Filter tap	0: 3x3	1: 5x5	2: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O26_2KY_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E80 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E84 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E88 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E8C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E90 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E94 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E98 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00E9C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EA0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EA4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EA8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EAC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EB0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EB4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EB8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EBC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EC0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EC4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EC8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00ECC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00ED0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00ED4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00ED8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EDC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EE0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EE4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O26_2KY_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EE8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EEC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O26_2KY_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EF0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O26_2KY_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EF4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EF8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00EFC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F00 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F04 RW 0x0000_2B38
	UINT32 reg_nntg_lsfr_init_1st           :32;	//(31:0,NA,11064) //4K nano-noise LSFR init (1st)
	};
}PE_O26_2KY_SHP_NNTG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F08 RW 0xBDE6_E338
	UINT32 reg_nntg_lsfr_init_2nd           :32;	//(31:0,NA,3186025272) //4K nano-noise LSFR init (2nd)
	};
}PE_O26_2KY_SHP_NNTG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F0C RW 0xD9F2_01CB
	UINT32 reg_nntg_lsfr_init_3rd           :32;	//(31:0,NA,3656516043) //4K nano-noise LSFR init (3rd)
	};
}PE_O26_2KY_SHP_NNTG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F10 RW 0x1598_773A
	UINT32 reg_nntg_lsfr_init_4th           :32;	//(31:0,NA,362313530) //4K nano-noise LSFR init (4th)
	};
}PE_O26_2KY_SHP_NNTG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F14 RW 0x82D2_8A5C
	UINT32 reg_nntg_lsfr_init_5th           :32;	//(31:0,NA,2194836060) //4K nano-noise LSFR init (5th)
	};
}PE_O26_2KY_SHP_NNTG_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F2C RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio              :8;	//(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F30 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00           :4;	//(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F34 RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20           :4;	//(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F38 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10           :4;	//(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F3C RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0             :8;	//(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O26_2KY_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F40 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2             :8;	//(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O26_2KY_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F44 RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0             :8;	//(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O26_2KY_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F48 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2             :8;	//(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O26_2KY_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F4C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O26_2KY_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F50 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F54 RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F60 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //DP sum LUT mode	0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O26_2KY_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F64 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //DP sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //DP sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //DP sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //DP sum LUT for delta control, x1
	};
}PE_O26_2KY_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F68 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //DP sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //DP sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //DP sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //DP sum LUT for delta control, x3
	};
}PE_O26_2KY_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F6C RW 0x1830_0200
	UINT32 reg_dp_sum_nt_lut_y0             :8;	//(7:0,NA,0) //DP sum LUT for non-text control, y0
	UINT32 reg_dp_sum_nt_lut_x0             :8;	//(15:8,NA,2) //DP sum LUT for non-text control, x0
	UINT32 reg_dp_sum_nt_lut_y1             :8;	//(23:16,NA,48) //DP sum LUT for non-text control, y1
	UINT32 reg_dp_sum_nt_lut_x1             :8;	//(31:24,NA,24) //DP sum LUT for non-text control, x1
	};
}PE_O26_2KY_SHP_DP_SUM_NT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00F70 RW 0xFFFF_5050
	UINT32 reg_dp_sum_nt_lut_y2             :8;	//(7:0,NA,80) //DP sum LUT for non-text control, y2
	UINT32 reg_dp_sum_nt_lut_x2             :8;	//(15:8,NA,80) //DP sum LUT for non-text control, x2
	UINT32 reg_dp_sum_nt_lut_y3             :8;	//(23:16,NA,255) //DP sum LUT for non-text control, y3
	UINT32 reg_dp_sum_nt_lut_x3             :8;	//(31:24,NA,255) //DP sum LUT for non-text control, x3
	};
}PE_O26_2KY_SHP_DP_SUM_NT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FA0 RW 0x0000_0000
	UINT32 reg_win_dp_win0_en               :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_dp_win1_en               :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_dp_win01_en              :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dp_win_outside           :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_dp_win_en                :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_dp_bdr_alpha             :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_dp_bdr_wid               :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_dp_bdr_en                :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_dp_cr5                   :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_dp_cb5                   :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_dp_yy6                   :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_2KY_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FA4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //Window control, win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //Window control, win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FA8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //Window control, win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //Window control, win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FAC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //Window control, win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //Window control, win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FB0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //Window control, win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //Window control, win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FC0 RW 0x0432_0C40
	UINT32 reg_region_text_en               :1;	//(0:0,NA,0) //Region texture enable
	UINT32 resvd                            :31;
	};
}PE_O26_2KY_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FC4 RW 0x0F50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //Region texture LUT, y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //Region texture LUT, x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //Region texture LUT, y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //Region texture LUT, x1
	};
}PE_O26_2KY_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FC8 RW 0x46C8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //Region texture LUT, y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //Region texture LUT, x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //Region texture LUT, y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //Region texture LUT, x3
	};
}PE_O26_2KY_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FCC RW 0x0000_FF00
	UINT32 reg_tmap_temp_iir_en             :1;	//(0:0,NA,0) //Tmap temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//(4:4,NA,0) //Tmap temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//(15:8,NA,255) //Tmap temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//(24:24,NA,0) //Tmap temporal process status selection	0: original tmap status	1: iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FD0 RW 0x2840_0A00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //Tmap temporal previous blend LUT, y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //Tmap temporal previous blend LUT, x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //Tmap temporal previous blend LUT, y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //Tmap temporal previous blend LUT, x1
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FD4 RW 0x5080_3C60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //Tmap temporal previous blend LUT, y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //Tmap temporal previous blend LUT, x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //Tmap temporal previous blend LUT, y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //Tmap temporal previous blend LUT, x3
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FD8 RW 0x08D0_00C0
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //Tmap temporal iir positive LUT, y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //Tmap temporal iir positive LUT, x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //Tmap temporal iir positive LUT, y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //Tmap temporal iir positive LUT, x1
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FDC RW 0x30F0_10E0
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //Tmap temporal iir positive LUT, y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //Tmap temporal iir positive LUT, x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //Tmap temporal iir positive LUT, y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //Tmap temporal iir positive LUT, x3
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FE0 RW 0x80C0_60D0
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //Tmap temporal iir positive LUT, y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //Tmap temporal iir positive LUT, x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //Tmap temporal iir positive LUT, y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //Tmap temporal iir positive LUT, x5
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FE4 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //Tmap temporal iir negative LUT, y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //Tmap temporal iir negative LUT, x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //Tmap temporal iir negative LUT, y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //Tmap temporal iir negative LUT, x1
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FE8 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //Tmap temporal iir negative LUT, y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //Tmap temporal iir negative LUT, x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //Tmap temporal iir negative LUT, y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //Tmap temporal iir negative LUT, x3
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FEC RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //Tmap temporal iir negative LUT, y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //Tmap temporal iir negative LUT, x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //Tmap temporal iir negative LUT, y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //Tmap temporal iir negative LUT, x5
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FF0 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x       :12;	//(11:0,NA,0) //Tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//(27:16,NA,0) //Tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FF4 RW 0x086F_077F
	UINT32 reg_tmap_stat_win0_end_x         :12;	//(11:0,NA,1919) //Tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//(27:16,NA,2159) //Tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FF8 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x       :12;	//(11:0,NA,1920) //Tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//(27:16,NA,0) //Tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA00FFC RW 0x0438_0EFF
	UINT32 reg_tmap_stat_win1_end_x         :12;	//(11:0,NA,3839) //Tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//(27:16,NA,1080) //Tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01000 RW 0x8010_0179
	UINT32 reg_dj_edf_en                    :1;	//(0:0,NA,1) //Edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//(1:1,NA,0) //H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//(3:3,NA,1) //Edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//(4:4,NA,1) //Line variation mode	0: sum of (cur - center)	1: sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//(5:5,NA,1) //L-type protection
	UINT32 reg_dj_soft_en                   :1;	//(6:6,NA,1) //Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_dj_count_diff_th             :5;	//(12:8,NA,1) //Matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//(18:16,NA,0) //Debug display	0: normal display	1: direction map	2: g0: feature (matchness)	3: g0: gain	4: g1: gain (protection)	5: final gain	6: blur coring map(used for blur-filtering)
	UINT32 reg_dj_buffer_detour_en          :1;	//(19:19,NA,0) //DJ buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//(21:20,NA,1) //Center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//(22:22,NA,0) //Neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//(23:23,NA,0) //DJ detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//(31:24,NA,128) //Line-variation threshold for edge-direction decision
	};
}PE_O26_2KY_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01004 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //Neighborhood pixel averaging: gain
	UINT32 resvd1                           :8;
	};
}PE_O26_2KY_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01008 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O26_2KY_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0100C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //Edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //Edge adaptive filter multiplication value
	};
}PE_O26_2KY_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01010 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O26_2KY_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01014 RW 0x0000_0000
	UINT32 reg_dj_pattern0_0_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [0][0]
	UINT32 reg_dj_pattern0_0_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [0][1]
	UINT32 reg_dj_pattern0_0_02             :2;	//(5:4,NA,0) //DJ protect pattern0 [0][2]
	UINT32 reg_dj_pattern0_0_03             :2;	//(7:6,NA,0) //DJ protect pattern0 [0][3]
	UINT32 reg_dj_pattern0_0_04             :2;	//(9:8,NA,0) //DJ protect pattern0 [0][4]
	UINT32 reg_dj_pattern0_0_05             :2;	//(11:10,NA,0) //DJ protect pattern0 [0][5]
	UINT32 reg_dj_pattern0_0_06             :2;	//(13:12,NA,0) //DJ protect pattern0 [0][6]
	UINT32 reg_dj_pattern0_0_07             :2;	//(15:14,NA,0) //DJ protect pattern0 [0][7]
	UINT32 reg_dj_pattern0_0_08             :2;	//(17:16,NA,0) //DJ protect pattern0 [0][8]
	UINT32 reg_dj_pattern0_0_09             :2;	//(19:18,NA,0) //DJ protect pattern0 [0][9]
	UINT32 reg_dj_pattern0_0_10             :2;	//(21:20,NA,0) //DJ protect pattern0 [0][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01018 RW 0x0000_0040
	UINT32 reg_dj_pattern0_1_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [1][0]
	UINT32 reg_dj_pattern0_1_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [1][1]
	UINT32 reg_dj_pattern0_1_02             :2;	//(5:4,NA,0) //DJ protect pattern0 [1][2]
	UINT32 reg_dj_pattern0_1_03             :2;	//(7:6,NA,1) //DJ protect pattern0 [1][3]
	UINT32 reg_dj_pattern0_1_04             :2;	//(9:8,NA,0) //DJ protect pattern0 [1][4]
	UINT32 reg_dj_pattern0_1_05             :2;	//(11:10,NA,0) //DJ protect pattern0 [1][5]
	UINT32 reg_dj_pattern0_1_06             :2;	//(13:12,NA,0) //DJ protect pattern0 [1][6]
	UINT32 reg_dj_pattern0_1_07             :2;	//(15:14,NA,0) //DJ protect pattern0 [1][7]
	UINT32 reg_dj_pattern0_1_08             :2;	//(17:16,NA,0) //DJ protect pattern0 [1][8]
	UINT32 reg_dj_pattern0_1_09             :2;	//(19:18,NA,0) //DJ protect pattern0 [1][9]
	UINT32 reg_dj_pattern0_1_10             :2;	//(21:20,NA,0) //DJ protect pattern0 [1][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0101C RW 0x0015_5550
	UINT32 reg_dj_pattern0_2_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [2][0]
	UINT32 reg_dj_pattern0_2_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [2][1]
	UINT32 reg_dj_pattern0_2_02             :2;	//(5:4,NA,1) //DJ protect pattern0 [2][2]
	UINT32 reg_dj_pattern0_2_03             :2;	//(7:6,NA,1) //DJ protect pattern0 [2][3]
	UINT32 reg_dj_pattern0_2_04             :2;	//(9:8,NA,1) //DJ protect pattern0 [2][4]
	UINT32 reg_dj_pattern0_2_05             :2;	//(11:10,NA,1) //DJ protect pattern0 [2][5]
	UINT32 reg_dj_pattern0_2_06             :2;	//(13:12,NA,1) //DJ protect pattern0 [2][6]
	UINT32 reg_dj_pattern0_2_07             :2;	//(15:14,NA,1) //DJ protect pattern0 [2][7]
	UINT32 reg_dj_pattern0_2_08             :2;	//(17:16,NA,1) //DJ protect pattern0 [2][8]
	UINT32 reg_dj_pattern0_2_09             :2;	//(19:18,NA,1) //DJ protect pattern0 [2][9]
	UINT32 reg_dj_pattern0_2_10             :2;	//(21:20,NA,1) //DJ protect pattern0 [2][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01020 RW 0x0000_0040
	UINT32 reg_dj_pattern0_3_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [3][0]
	UINT32 reg_dj_pattern0_3_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [3][1]
	UINT32 reg_dj_pattern0_3_02             :2;	//(5:4,NA,0) //DJ protect pattern0 [3][2]
	UINT32 reg_dj_pattern0_3_03             :2;	//(7:6,NA,1) //DJ protect pattern0 [3][3]
	UINT32 reg_dj_pattern0_3_04             :2;	//(9:8,NA,0) //DJ protect pattern0 [3][4]
	UINT32 reg_dj_pattern0_3_05             :2;	//(11:10,NA,0) //DJ protect pattern0 [3][5]
	UINT32 reg_dj_pattern0_3_06             :2;	//(13:12,NA,0) //DJ protect pattern0 [3][6]
	UINT32 reg_dj_pattern0_3_07             :2;	//(15:14,NA,0) //DJ protect pattern0 [3][7]
	UINT32 reg_dj_pattern0_3_08             :2;	//(17:16,NA,0) //DJ protect pattern0 [3][8]
	UINT32 reg_dj_pattern0_3_09             :2;	//(19:18,NA,0) //DJ protect pattern0 [3][9]
	UINT32 reg_dj_pattern0_3_10             :2;	//(21:20,NA,0) //DJ protect pattern0 [3][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01024 RW 0x002A_A040
	UINT32 reg_dj_pattern0_4_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [4][0]
	UINT32 reg_dj_pattern0_4_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [4][1]
	UINT32 reg_dj_pattern0_4_02             :2;	//(5:4,NA,0) //DJ protect pattern0 [4][2]
	UINT32 reg_dj_pattern0_4_03             :2;	//(7:6,NA,1) //DJ protect pattern0 [4][3]
	UINT32 reg_dj_pattern0_4_04             :2;	//(9:8,NA,0) //DJ protect pattern0 [4][4]
	UINT32 reg_dj_pattern0_4_05             :2;	//(11:10,NA,0) //DJ protect pattern0 [4][5]
	UINT32 reg_dj_pattern0_4_06             :2;	//(13:12,NA,2) //DJ protect pattern0 [4][6]
	UINT32 reg_dj_pattern0_4_07             :2;	//(15:14,NA,2) //DJ protect pattern0 [4][7]
	UINT32 reg_dj_pattern0_4_08             :2;	//(17:16,NA,2) //DJ protect pattern0 [4][8]
	UINT32 reg_dj_pattern0_4_09             :2;	//(19:18,NA,2) //DJ protect pattern0 [4][9]
	UINT32 reg_dj_pattern0_4_10             :2;	//(21:20,NA,2) //DJ protect pattern0 [4][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01028 RW 0x002A_A040
	UINT32 reg_dj_pattern0_5_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [5][0]
	UINT32 reg_dj_pattern0_5_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [5][1]
	UINT32 reg_dj_pattern0_5_02             :2;	//(5:4,NA,0) //DJ protect pattern0 [5][2]
	UINT32 reg_dj_pattern0_5_03             :2;	//(7:6,NA,1) //DJ protect pattern0 [5][3]
	UINT32 reg_dj_pattern0_5_04             :2;	//(9:8,NA,0) //DJ protect pattern0 [5][4]
	UINT32 reg_dj_pattern0_5_05             :2;	//(11:10,NA,0) //DJ protect pattern0 [5][5]
	UINT32 reg_dj_pattern0_5_06             :2;	//(13:12,NA,2) //DJ protect pattern0 [5][6]
	UINT32 reg_dj_pattern0_5_07             :2;	//(15:14,NA,2) //DJ protect pattern0 [5][7]
	UINT32 reg_dj_pattern0_5_08             :2;	//(17:16,NA,2) //DJ protect pattern0 [5][8]
	UINT32 reg_dj_pattern0_5_09             :2;	//(19:18,NA,2) //DJ protect pattern0 [5][9]
	UINT32 reg_dj_pattern0_5_10             :2;	//(21:20,NA,2) //DJ protect pattern0 [5][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0102C RW 0x000A_A040
	UINT32 reg_dj_pattern0_6_00             :2;	//(1:0,NA,0) //DJ protect pattern0 [6][0]
	UINT32 reg_dj_pattern0_6_01             :2;	//(3:2,NA,0) //DJ protect pattern0 [6][1]
	UINT32 reg_dj_pattern0_6_02             :2;	//(5:4,NA,0) //DJ protect pattern0 [6][2]
	UINT32 reg_dj_pattern0_6_03             :2;	//(7:6,NA,1) //DJ protect pattern0 [6][3]
	UINT32 reg_dj_pattern0_6_04             :2;	//(9:8,NA,0) //DJ protect pattern0 [6][4]
	UINT32 reg_dj_pattern0_6_05             :2;	//(11:10,NA,0) //DJ protect pattern0 [6][5]
	UINT32 reg_dj_pattern0_6_06             :2;	//(13:12,NA,2) //DJ protect pattern0 [6][6]
	UINT32 reg_dj_pattern0_6_07             :2;	//(15:14,NA,2) //DJ protect pattern0 [6][7]
	UINT32 reg_dj_pattern0_6_08             :2;	//(17:16,NA,2) //DJ protect pattern0 [6][8]
	UINT32 reg_dj_pattern0_6_09             :2;	//(19:18,NA,2) //DJ protect pattern0 [6][9]
	UINT32 reg_dj_pattern0_6_10             :2;	//(21:20,NA,0) //DJ protect pattern0 [6][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01030 RW 0x0000_00E4
	UINT32 reg_dj_pattern0_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern0 flip0, H
	UINT32 reg_dj_pattern0_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern0 flip0, V
	UINT32 reg_dj_pattern0_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern0 flip1, H
	UINT32 reg_dj_pattern0_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern0 flip1, V
	UINT32 reg_dj_pattern0_flip2_h          :1;	//(4:4,NA,0) //DJ protect pattern0 flip2, H
	UINT32 reg_dj_pattern0_flip2_v          :1;	//(5:5,NA,1) //DJ protect pattern0 flip2, V
	UINT32 reg_dj_pattern0_flip3_h          :1;	//(6:6,NA,1) //DJ protect pattern0 flip3, H
	UINT32 reg_dj_pattern0_flip3_v          :1;	//(7:7,NA,1) //DJ protect pattern0 flip3, V
	UINT32 resvd                            :24;
	};
}PE_O26_2KY_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01034 RW 0x0000_5540
	UINT32 reg_dj_pattern1_0_00             :2;	//(1:0,NA,0) //DJ protect pattern1 [0][0]
	UINT32 reg_dj_pattern1_0_01             :2;	//(3:2,NA,0) //DJ protect pattern1 [0][1]
	UINT32 reg_dj_pattern1_0_02             :2;	//(5:4,NA,0) //DJ protect pattern1 [0][2]
	UINT32 reg_dj_pattern1_0_03             :2;	//(7:6,NA,1) //DJ protect pattern1 [0][3]
	UINT32 reg_dj_pattern1_0_04             :2;	//(9:8,NA,1) //DJ protect pattern1 [0][4]
	UINT32 reg_dj_pattern1_0_05             :2;	//(11:10,NA,1) //DJ protect pattern1 [0][5]
	UINT32 reg_dj_pattern1_0_06             :2;	//(13:12,NA,1) //DJ protect pattern1 [0][6]
	UINT32 reg_dj_pattern1_0_07             :2;	//(15:14,NA,1) //DJ protect pattern1 [0][7]
	UINT32 reg_dj_pattern1_0_08             :2;	//(17:16,NA,0) //DJ protect pattern1 [0][8]
	UINT32 reg_dj_pattern1_0_09             :2;	//(19:18,NA,0) //DJ protect pattern1 [0][9]
	UINT32 reg_dj_pattern1_0_10             :2;	//(21:20,NA,0) //DJ protect pattern1 [0][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01038 RW 0x0020_5542
	UINT32 reg_dj_pattern1_1_00             :2;	//(1:0,NA,2) //DJ protect pattern1 [1][0]
	UINT32 reg_dj_pattern1_1_01             :2;	//(3:2,NA,0) //DJ protect pattern1 [1][1]
	UINT32 reg_dj_pattern1_1_02             :2;	//(5:4,NA,0) //DJ protect pattern1 [1][2]
	UINT32 reg_dj_pattern1_1_03             :2;	//(7:6,NA,1) //DJ protect pattern1 [1][3]
	UINT32 reg_dj_pattern1_1_04             :2;	//(9:8,NA,1) //DJ protect pattern1 [1][4]
	UINT32 reg_dj_pattern1_1_05             :2;	//(11:10,NA,1) //DJ protect pattern1 [1][5]
	UINT32 reg_dj_pattern1_1_06             :2;	//(13:12,NA,1) //DJ protect pattern1 [1][6]
	UINT32 reg_dj_pattern1_1_07             :2;	//(15:14,NA,1) //DJ protect pattern1 [1][7]
	UINT32 reg_dj_pattern1_1_08             :2;	//(17:16,NA,0) //DJ protect pattern1 [1][8]
	UINT32 reg_dj_pattern1_1_09             :2;	//(19:18,NA,0) //DJ protect pattern1 [1][9]
	UINT32 reg_dj_pattern1_1_10             :2;	//(21:20,NA,2) //DJ protect pattern1 [1][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0103C RW 0x0008_1508
	UINT32 reg_dj_pattern1_2_00             :2;	//(1:0,NA,0) //DJ protect pattern1 [2][0]
	UINT32 reg_dj_pattern1_2_01             :2;	//(3:2,NA,2) //DJ protect pattern1 [2][1]
	UINT32 reg_dj_pattern1_2_02             :2;	//(5:4,NA,0) //DJ protect pattern1 [2][2]
	UINT32 reg_dj_pattern1_2_03             :2;	//(7:6,NA,0) //DJ protect pattern1 [2][3]
	UINT32 reg_dj_pattern1_2_04             :2;	//(9:8,NA,1) //DJ protect pattern1 [2][4]
	UINT32 reg_dj_pattern1_2_05             :2;	//(11:10,NA,1) //DJ protect pattern1 [2][5]
	UINT32 reg_dj_pattern1_2_06             :2;	//(13:12,NA,1) //DJ protect pattern1 [2][6]
	UINT32 reg_dj_pattern1_2_07             :2;	//(15:14,NA,0) //DJ protect pattern1 [2][7]
	UINT32 reg_dj_pattern1_2_08             :2;	//(17:16,NA,0) //DJ protect pattern1 [2][8]
	UINT32 reg_dj_pattern1_2_09             :2;	//(19:18,NA,2) //DJ protect pattern1 [2][9]
	UINT32 reg_dj_pattern1_2_10             :2;	//(21:20,NA,0) //DJ protect pattern1 [2][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01040 RW 0x0002_0420
	UINT32 reg_dj_pattern1_3_00             :2;	//(1:0,NA,0) //DJ protect pattern1 [3][0]
	UINT32 reg_dj_pattern1_3_01             :2;	//(3:2,NA,0) //DJ protect pattern1 [3][1]
	UINT32 reg_dj_pattern1_3_02             :2;	//(5:4,NA,2) //DJ protect pattern1 [3][2]
	UINT32 reg_dj_pattern1_3_03             :2;	//(7:6,NA,0) //DJ protect pattern1 [3][3]
	UINT32 reg_dj_pattern1_3_04             :2;	//(9:8,NA,0) //DJ protect pattern1 [3][4]
	UINT32 reg_dj_pattern1_3_05             :2;	//(11:10,NA,1) //DJ protect pattern1 [3][5]
	UINT32 reg_dj_pattern1_3_06             :2;	//(13:12,NA,0) //DJ protect pattern1 [3][6]
	UINT32 reg_dj_pattern1_3_07             :2;	//(15:14,NA,0) //DJ protect pattern1 [3][7]
	UINT32 reg_dj_pattern1_3_08             :2;	//(17:16,NA,2) //DJ protect pattern1 [3][8]
	UINT32 reg_dj_pattern1_3_09             :2;	//(19:18,NA,0) //DJ protect pattern1 [3][9]
	UINT32 reg_dj_pattern1_3_10             :2;	//(21:20,NA,0) //DJ protect pattern1 [3][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01044 RW 0x0000_8080
	UINT32 reg_dj_pattern1_4_00             :2;	//(1:0,NA,0) //DJ protect pattern1 [4][0]
	UINT32 reg_dj_pattern1_4_01             :2;	//(3:2,NA,0) //DJ protect pattern1 [4][1]
	UINT32 reg_dj_pattern1_4_02             :2;	//(5:4,NA,0) //DJ protect pattern1 [4][2]
	UINT32 reg_dj_pattern1_4_03             :2;	//(7:6,NA,2) //DJ protect pattern1 [4][3]
	UINT32 reg_dj_pattern1_4_04             :2;	//(9:8,NA,0) //DJ protect pattern1 [4][4]
	UINT32 reg_dj_pattern1_4_05             :2;	//(11:10,NA,0) //DJ protect pattern1 [4][5]
	UINT32 reg_dj_pattern1_4_06             :2;	//(13:12,NA,0) //DJ protect pattern1 [4][6]
	UINT32 reg_dj_pattern1_4_07             :2;	//(15:14,NA,2) //DJ protect pattern1 [4][7]
	UINT32 reg_dj_pattern1_4_08             :2;	//(17:16,NA,0) //DJ protect pattern1 [4][8]
	UINT32 reg_dj_pattern1_4_09             :2;	//(19:18,NA,0) //DJ protect pattern1 [4][9]
	UINT32 reg_dj_pattern1_4_10             :2;	//(21:20,NA,0) //DJ protect pattern1 [4][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01048 RW 0x0000_2A00
	UINT32 reg_dj_pattern1_5_00             :2;	//(1:0,NA,0) //DJ protect pattern1 [5][0]
	UINT32 reg_dj_pattern1_5_01             :2;	//(3:2,NA,0) //DJ protect pattern1 [5][1]
	UINT32 reg_dj_pattern1_5_02             :2;	//(5:4,NA,0) //DJ protect pattern1 [5][2]
	UINT32 reg_dj_pattern1_5_03             :2;	//(7:6,NA,0) //DJ protect pattern1 [5][3]
	UINT32 reg_dj_pattern1_5_04             :2;	//(9:8,NA,2) //DJ protect pattern1 [5][4]
	UINT32 reg_dj_pattern1_5_05             :2;	//(11:10,NA,2) //DJ protect pattern1 [5][5]
	UINT32 reg_dj_pattern1_5_06             :2;	//(13:12,NA,2) //DJ protect pattern1 [5][6]
	UINT32 reg_dj_pattern1_5_07             :2;	//(15:14,NA,0) //DJ protect pattern1 [5][7]
	UINT32 reg_dj_pattern1_5_08             :2;	//(17:16,NA,0) //DJ protect pattern1 [5][8]
	UINT32 reg_dj_pattern1_5_09             :2;	//(19:18,NA,0) //DJ protect pattern1 [5][9]
	UINT32 reg_dj_pattern1_5_10             :2;	//(21:20,NA,0) //DJ protect pattern1 [5][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0104C RW 0x0000_2A00
	UINT32 reg_dj_pattern1_6_00             :2;	//(1:0,NA,0) //DJ protect pattern1 [6][0]
	UINT32 reg_dj_pattern1_6_01             :2;	//(3:2,NA,0) //DJ protect pattern1 [6][1]
	UINT32 reg_dj_pattern1_6_02             :2;	//(5:4,NA,0) //DJ protect pattern1 [6][2]
	UINT32 reg_dj_pattern1_6_03             :2;	//(7:6,NA,0) //DJ protect pattern1 [6][3]
	UINT32 reg_dj_pattern1_6_04             :2;	//(9:8,NA,2) //DJ protect pattern1 [6][4]
	UINT32 reg_dj_pattern1_6_05             :2;	//(11:10,NA,2) //DJ protect pattern1 [6][5]
	UINT32 reg_dj_pattern1_6_06             :2;	//(13:12,NA,2) //DJ protect pattern1 [6][6]
	UINT32 reg_dj_pattern1_6_07             :2;	//(15:14,NA,0) //DJ protect pattern1 [6][7]
	UINT32 reg_dj_pattern1_6_08             :2;	//(17:16,NA,0) //DJ protect pattern1 [6][8]
	UINT32 reg_dj_pattern1_6_09             :2;	//(19:18,NA,0) //DJ protect pattern1 [6][9]
	UINT32 reg_dj_pattern1_6_10             :2;	//(21:20,NA,0) //DJ protect pattern1 [6][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01050 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O26_2KY_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01054 RW 0x0000_2800
	UINT32 reg_dj_pattern2_0_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [0][0]
	UINT32 reg_dj_pattern2_0_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [0][1]
	UINT32 reg_dj_pattern2_0_02             :2;	//(5:4,NA,0) //DJ protect pattern2 [0][2]
	UINT32 reg_dj_pattern2_0_03             :2;	//(7:6,NA,0) //DJ protect pattern2 [0][3]
	UINT32 reg_dj_pattern2_0_04             :2;	//(9:8,NA,0) //DJ protect pattern2 [0][4]
	UINT32 reg_dj_pattern2_0_05             :2;	//(11:10,NA,2) //DJ protect pattern2 [0][5]
	UINT32 reg_dj_pattern2_0_06             :2;	//(13:12,NA,2) //DJ protect pattern2 [0][6]
	UINT32 reg_dj_pattern2_0_07             :2;	//(15:14,NA,0) //DJ protect pattern2 [0][7]
	UINT32 reg_dj_pattern2_0_08             :2;	//(17:16,NA,0) //DJ protect pattern2 [0][8]
	UINT32 reg_dj_pattern2_0_09             :2;	//(19:18,NA,0) //DJ protect pattern2 [0][9]
	UINT32 reg_dj_pattern2_0_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [0][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01058 RW 0x0005_0A00
	UINT32 reg_dj_pattern2_1_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [1][0]
	UINT32 reg_dj_pattern2_1_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [1][1]
	UINT32 reg_dj_pattern2_1_02             :2;	//(5:4,NA,0) //DJ protect pattern2 [1][2]
	UINT32 reg_dj_pattern2_1_03             :2;	//(7:6,NA,0) //DJ protect pattern2 [1][3]
	UINT32 reg_dj_pattern2_1_04             :2;	//(9:8,NA,2) //DJ protect pattern2 [1][4]
	UINT32 reg_dj_pattern2_1_05             :2;	//(11:10,NA,2) //DJ protect pattern2 [1][5]
	UINT32 reg_dj_pattern2_1_06             :2;	//(13:12,NA,0) //DJ protect pattern2 [1][6]
	UINT32 reg_dj_pattern2_1_07             :2;	//(15:14,NA,0) //DJ protect pattern2 [1][7]
	UINT32 reg_dj_pattern2_1_08             :2;	//(17:16,NA,1) //DJ protect pattern2 [1][8]
	UINT32 reg_dj_pattern2_1_09             :2;	//(19:18,NA,1) //DJ protect pattern2 [1][9]
	UINT32 reg_dj_pattern2_1_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [1][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0105C RW 0x0005_4280
	UINT32 reg_dj_pattern2_2_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [2][0]
	UINT32 reg_dj_pattern2_2_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [2][1]
	UINT32 reg_dj_pattern2_2_02             :2;	//(5:4,NA,0) //DJ protect pattern2 [2][2]
	UINT32 reg_dj_pattern2_2_03             :2;	//(7:6,NA,2) //DJ protect pattern2 [2][3]
	UINT32 reg_dj_pattern2_2_04             :2;	//(9:8,NA,2) //DJ protect pattern2 [2][4]
	UINT32 reg_dj_pattern2_2_05             :2;	//(11:10,NA,0) //DJ protect pattern2 [2][5]
	UINT32 reg_dj_pattern2_2_06             :2;	//(13:12,NA,0) //DJ protect pattern2 [2][6]
	UINT32 reg_dj_pattern2_2_07             :2;	//(15:14,NA,1) //DJ protect pattern2 [2][7]
	UINT32 reg_dj_pattern2_2_08             :2;	//(17:16,NA,1) //DJ protect pattern2 [2][8]
	UINT32 reg_dj_pattern2_2_09             :2;	//(19:18,NA,1) //DJ protect pattern2 [2][9]
	UINT32 reg_dj_pattern2_2_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [2][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01060 RW 0x0005_50A0
	UINT32 reg_dj_pattern2_3_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [3][0]
	UINT32 reg_dj_pattern2_3_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [3][1]
	UINT32 reg_dj_pattern2_3_02             :2;	//(5:4,NA,2) //DJ protect pattern2 [3][2]
	UINT32 reg_dj_pattern2_3_03             :2;	//(7:6,NA,2) //DJ protect pattern2 [3][3]
	UINT32 reg_dj_pattern2_3_04             :2;	//(9:8,NA,0) //DJ protect pattern2 [3][4]
	UINT32 reg_dj_pattern2_3_05             :2;	//(11:10,NA,0) //DJ protect pattern2 [3][5]
	UINT32 reg_dj_pattern2_3_06             :2;	//(13:12,NA,1) //DJ protect pattern2 [3][6]
	UINT32 reg_dj_pattern2_3_07             :2;	//(15:14,NA,1) //DJ protect pattern2 [3][7]
	UINT32 reg_dj_pattern2_3_08             :2;	//(17:16,NA,1) //DJ protect pattern2 [3][8]
	UINT32 reg_dj_pattern2_3_09             :2;	//(19:18,NA,1) //DJ protect pattern2 [3][9]
	UINT32 reg_dj_pattern2_3_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [3][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01064 RW 0x0005_4280
	UINT32 reg_dj_pattern2_4_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [4][0]
	UINT32 reg_dj_pattern2_4_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [4][1]
	UINT32 reg_dj_pattern2_4_02             :2;	//(5:4,NA,0) //DJ protect pattern2 [4][2]
	UINT32 reg_dj_pattern2_4_03             :2;	//(7:6,NA,2) //DJ protect pattern2 [4][3]
	UINT32 reg_dj_pattern2_4_04             :2;	//(9:8,NA,2) //DJ protect pattern2 [4][4]
	UINT32 reg_dj_pattern2_4_05             :2;	//(11:10,NA,0) //DJ protect pattern2 [4][5]
	UINT32 reg_dj_pattern2_4_06             :2;	//(13:12,NA,0) //DJ protect pattern2 [4][6]
	UINT32 reg_dj_pattern2_4_07             :2;	//(15:14,NA,1) //DJ protect pattern2 [4][7]
	UINT32 reg_dj_pattern2_4_08             :2;	//(17:16,NA,1) //DJ protect pattern2 [4][8]
	UINT32 reg_dj_pattern2_4_09             :2;	//(19:18,NA,1) //DJ protect pattern2 [4][9]
	UINT32 reg_dj_pattern2_4_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [4][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01068 RW 0x0005_0A00
	UINT32 reg_dj_pattern2_5_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [5][0]
	UINT32 reg_dj_pattern2_5_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [5][1]
	UINT32 reg_dj_pattern2_5_02             :2;	//(5:4,NA,0) //DJ protect pattern2 [5][2]
	UINT32 reg_dj_pattern2_5_03             :2;	//(7:6,NA,0) //DJ protect pattern2 [5][3]
	UINT32 reg_dj_pattern2_5_04             :2;	//(9:8,NA,2) //DJ protect pattern2 [5][4]
	UINT32 reg_dj_pattern2_5_05             :2;	//(11:10,NA,2) //DJ protect pattern2 [5][5]
	UINT32 reg_dj_pattern2_5_06             :2;	//(13:12,NA,0) //DJ protect pattern2 [5][6]
	UINT32 reg_dj_pattern2_5_07             :2;	//(15:14,NA,0) //DJ protect pattern2 [5][7]
	UINT32 reg_dj_pattern2_5_08             :2;	//(17:16,NA,1) //DJ protect pattern2 [5][8]
	UINT32 reg_dj_pattern2_5_09             :2;	//(19:18,NA,1) //DJ protect pattern2 [5][9]
	UINT32 reg_dj_pattern2_5_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [5][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0106C RW 0x0000_2800
	UINT32 reg_dj_pattern2_6_00             :2;	//(1:0,NA,0) //DJ protect pattern2 [6][0]
	UINT32 reg_dj_pattern2_6_01             :2;	//(3:2,NA,0) //DJ protect pattern2 [6][1]
	UINT32 reg_dj_pattern2_6_02             :2;	//(5:4,NA,0) //DJ protect pattern2 [6][2]
	UINT32 reg_dj_pattern2_6_03             :2;	//(7:6,NA,0) //DJ protect pattern2 [6][3]
	UINT32 reg_dj_pattern2_6_04             :2;	//(9:8,NA,0) //DJ protect pattern2 [6][4]
	UINT32 reg_dj_pattern2_6_05             :2;	//(11:10,NA,2) //DJ protect pattern2 [6][5]
	UINT32 reg_dj_pattern2_6_06             :2;	//(13:12,NA,2) //DJ protect pattern2 [6][6]
	UINT32 reg_dj_pattern2_6_07             :2;	//(15:14,NA,0) //DJ protect pattern2 [6][7]
	UINT32 reg_dj_pattern2_6_08             :2;	//(17:16,NA,0) //DJ protect pattern2 [6][8]
	UINT32 reg_dj_pattern2_6_09             :2;	//(19:18,NA,0) //DJ protect pattern2 [6][9]
	UINT32 reg_dj_pattern2_6_10             :2;	//(21:20,NA,0) //DJ protect pattern2 [6][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KY_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01070 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O26_2KY_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01074 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01078 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0107C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O26_2KY_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01080 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O26_2KY_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01090 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01094 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010A0 RW 0x0000_0000
	UINT32 reg_win_dj_win0_en               :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_dj_win1_en               :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_dj_win01_en              :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dj_win_outside           :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_dj_win_en                :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_dj_bdr_alpha             :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_dj_bdr_wid               :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_dj_bdr_en                :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_dj_cr5                   :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_dj_cb5                   :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_dj_yy6                   :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_2KY_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //Window control, win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //Window control, win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010A8 RW 0x0437_077F
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,1919) //Window control, win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,1079) //Window control, win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //Window control, win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //Window control, win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010B0 RW 0x0437_077F
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,1919) //Window control, win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,1079) //Window control, win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010C0 RW 0x10BC_4DB3
	UINT32 reg_dj_text_gain_mmd_mul         :8;	//(7:0,NA,179) //DJ text gain MMD factor
	UINT32 reg_dj_text_gain_avg_mul         :8;	//(15:8,NA,77) //DJ text gain average factor
	UINT32 reg_dj_text_gain_threshold       :10;	//(25:16,NA,188) //DJ text gain threshold
	UINT32 reg_dj_text_gain_all_text_flag   :1;	//(26:26,NA,0) //DJ text gain all text flag
	UINT32 resvd0                           :1;
	UINT32 reg_dj_text_gain_en              :1;	//(28:28,NA,1) //DJ text gain enable
	UINT32 resvd1                           :3;
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010C4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir0_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir0), y0
	UINT32 reg_dj_text_gain_dir0_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir0), x0
	UINT32 reg_dj_text_gain_dir0_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir0), y1
	UINT32 reg_dj_text_gain_dir0_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir0), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010C8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir0_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir0), y2
	UINT32 reg_dj_text_gain_dir0_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir0), x2
	UINT32 reg_dj_text_gain_dir0_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir0), y3
	UINT32 reg_dj_text_gain_dir0_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir0), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010CC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir1_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir1), y0
	UINT32 reg_dj_text_gain_dir1_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir1), x0
	UINT32 reg_dj_text_gain_dir1_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir1), y1
	UINT32 reg_dj_text_gain_dir1_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir1), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010D0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir1_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir1), y2
	UINT32 reg_dj_text_gain_dir1_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir1), x2
	UINT32 reg_dj_text_gain_dir1_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir1), y3
	UINT32 reg_dj_text_gain_dir1_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir1), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010D4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir3_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir3), y0
	UINT32 reg_dj_text_gain_dir3_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir3), x0
	UINT32 reg_dj_text_gain_dir3_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir3), y1
	UINT32 reg_dj_text_gain_dir3_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir3), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010D8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir3_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir3), y2
	UINT32 reg_dj_text_gain_dir3_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir3), x2
	UINT32 reg_dj_text_gain_dir3_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir3), y3
	UINT32 reg_dj_text_gain_dir3_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir3), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010DC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir5_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir5), y0
	UINT32 reg_dj_text_gain_dir5_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir5), x0
	UINT32 reg_dj_text_gain_dir5_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir5), y1
	UINT32 reg_dj_text_gain_dir5_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir5), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010E0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir5_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir5), y2
	UINT32 reg_dj_text_gain_dir5_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir5), x2
	UINT32 reg_dj_text_gain_dir5_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir5), y3
	UINT32 reg_dj_text_gain_dir5_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir5), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010E4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir6_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir6), y0
	UINT32 reg_dj_text_gain_dir6_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir6), x0
	UINT32 reg_dj_text_gain_dir6_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir6), y1
	UINT32 reg_dj_text_gain_dir6_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir6), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010E8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir6_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir6), y2
	UINT32 reg_dj_text_gain_dir6_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir6), x2
	UINT32 reg_dj_text_gain_dir6_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir6), y3
	UINT32 reg_dj_text_gain_dir6_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir6), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010EC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir7_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir7), y0
	UINT32 reg_dj_text_gain_dir7_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir7), x0
	UINT32 reg_dj_text_gain_dir7_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir7), y1
	UINT32 reg_dj_text_gain_dir7_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir7), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010F0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir7_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir7), y2
	UINT32 reg_dj_text_gain_dir7_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir7), x2
	UINT32 reg_dj_text_gain_dir7_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir7), y3
	UINT32 reg_dj_text_gain_dir7_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir7), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010F4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir9_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir9), y0
	UINT32 reg_dj_text_gain_dir9_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir9), x0
	UINT32 reg_dj_text_gain_dir9_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir9), y1
	UINT32 reg_dj_text_gain_dir9_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir9), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010F8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir9_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir9), y2
	UINT32 reg_dj_text_gain_dir9_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir9), x2
	UINT32 reg_dj_text_gain_dir9_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir9), y3
	UINT32 reg_dj_text_gain_dir9_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir9), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA010FC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir11_y0        :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir11), y0
	UINT32 reg_dj_text_gain_dir11_x0        :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir11), x0
	UINT32 reg_dj_text_gain_dir11_y1        :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir11), y1
	UINT32 reg_dj_text_gain_dir11_x1        :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir11), x1
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01100 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir11_y2        :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir11), y2
	UINT32 reg_dj_text_gain_dir11_x2        :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir11), x2
	UINT32 reg_dj_text_gain_dir11_y3        :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir11), y3
	UINT32 reg_dj_text_gain_dir11_x3        :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir11), x3
	};
}PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01110 RW 0x0000_0000
	UINT32 reg_text_gain_en                 :1;	//(0:0,NA,0) //Text gain enable
	UINT32 resvd                            :31;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01114 RW 0x0000_0000
	UINT32 reg_text_gain_lut_y0             :8;	//(7:0,NA,0) //Text gain LUT, y0
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x0             :15;	//(30:16,NA,0) //Text gain LUT, x0
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01118 RW 0x0BB8_0014
	UINT32 reg_text_gain_lut_y1             :8;	//(7:0,NA,20) //Text gain LUT, y1
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x1             :15;	//(30:16,NA,3000) //Text gain LUT, x1
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0111C RW 0x157C_0050
	UINT32 reg_text_gain_lut_y2             :8;	//(7:0,NA,80) //Text gain LUT, y2
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x2             :15;	//(30:16,NA,5500) //Text gain LUT, x2
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01120 RW 0x2328_0096
	UINT32 reg_text_gain_lut_y3             :8;	//(7:0,NA,150) //Text gain LUT, y3
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x3             :15;	//(30:16,NA,9000) //Text gain LUT, x3
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01124 RW 0x2EE0_00C8
	UINT32 reg_text_gain_lut_y4             :8;	//(7:0,NA,200) //Text gain LUT, y4
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x4             :15;	//(30:16,NA,12000) //Text gain LUT, x4
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01128 RW 0x3A98_00E6
	UINT32 reg_text_gain_lut_y5             :8;	//(7:0,NA,230) //Text gain LUT, y5
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x5             :15;	//(30:16,NA,15000) //Text gain LUT, x5
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0112C RW 0x4E20_00FF
	UINT32 reg_text_gain_lut_y6             :8;	//(7:0,NA,255) //Text gain LUT, y6
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x6             :15;	//(30:16,NA,20000) //Text gain LUT, x6
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01130 RW 0x6897_00FF
	UINT32 reg_text_gain_lut_y7             :8;	//(7:0,NA,255) //Text gain LUT, y7
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x7             :15;	//(30:16,NA,26775) //Text gain LUT, x7
	UINT32 resvd1                           :1;
	};
}PE_O26_2KY_SHP_FD_TEXT_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01134 RW 0x0000_FF00
	UINT32 reg_text_temp_iir_en             :1;	//(0:0,NA,0) //Text temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_text_temp_init_en            :1;	//(4:4,NA,0) //Text temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_text_temp_init_val           :8;	//(15:8,NA,255) //Text temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_text_stat_sel                :1;	//(24:24,NA,0) //Text temporal process status selection	0: original tmap status	1: iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01138 RW 0x2840_0A00
	UINT32 reg_text_temp_prev_lut_y0        :8;	//(7:0,NA,0) //Text temporal previous blend LUT, y0
	UINT32 reg_text_temp_prev_lut_x0        :8;	//(15:8,NA,10) //Text temporal previous blend LUT, x0
	UINT32 reg_text_temp_prev_lut_y1        :8;	//(23:16,NA,64) //Text temporal previous blend LUT, y1
	UINT32 reg_text_temp_prev_lut_x1        :8;	//(31:24,NA,40) //Text temporal previous blend LUT, x1
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0113C RW 0x5080_3C60
	UINT32 reg_text_temp_prev_lut_y2        :8;	//(7:0,NA,96) //Text temporal previous blend LUT, y2
	UINT32 reg_text_temp_prev_lut_x2        :8;	//(15:8,NA,60) //Text temporal previous blend LUT, x2
	UINT32 reg_text_temp_prev_lut_y3        :8;	//(23:16,NA,128) //Text temporal previous blend LUT, y3
	UINT32 reg_text_temp_prev_lut_x3        :8;	//(31:24,NA,80) //Text temporal previous blend LUT, x3
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01140 RW 0x08D0_00C0
	UINT32 reg_text_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //Text temporal iir positive LUT, y0
	UINT32 reg_text_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //Text temporal iir positive LUT, x0
	UINT32 reg_text_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //Text temporal iir positive LUT, y1
	UINT32 reg_text_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //Text temporal iir positive LUT, x1
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01144 RW 0x30F0_10E0
	UINT32 reg_text_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //Text temporal iir positive LUT, y2
	UINT32 reg_text_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //Text temporal iir positive LUT, x2
	UINT32 reg_text_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //Text temporal iir positive LUT, y3
	UINT32 reg_text_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //Text temporal iir positive LUT, x3
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01148 RW 0x80C0_60D0
	UINT32 reg_text_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //Text temporal iir positive LUT, y4
	UINT32 reg_text_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //Text temporal iir positive LUT, x4
	UINT32 reg_text_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //Text temporal iir positive LUT, y5
	UINT32 reg_text_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //Text temporal iir positive LUT, x5
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0114C RW 0x0870_0080
	UINT32 reg_text_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //Text temporal iir negative LUT, y0
	UINT32 reg_text_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //Text temporal iir negative LUT, x0
	UINT32 reg_text_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //Text temporal iir negative LUT, y1
	UINT32 reg_text_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //Text temporal iir negative LUT, x1
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01150 RW 0x1850_1060
	UINT32 reg_text_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //Text temporal iir negative LUT, y2
	UINT32 reg_text_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //Text temporal iir negative LUT, x2
	UINT32 reg_text_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //Text temporal iir negative LUT, y3
	UINT32 reg_text_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //Text temporal iir negative LUT, x3
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01154 RW 0x4000_2040
	UINT32 reg_text_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //Text temporal iir negative LUT, y4
	UINT32 reg_text_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //Text temporal iir negative LUT, x4
	UINT32 reg_text_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //Text temporal iir negative LUT, y5
	UINT32 reg_text_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //Text temporal iir negative LUT, x5
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01158 RW 0x0000_0000
	UINT32 reg_text_stat_win0_start_x       :12;	//(11:0,NA,0) //Text temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_text_stat_win0_start_y       :12;	//(27:16,NA,0) //Text temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0115C RW 0x086F_077F
	UINT32 reg_text_stat_win0_end_x         :12;	//(11:0,NA,1919) //Text temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_text_stat_win0_end_y         :12;	//(27:16,NA,2159) //Text temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01160 RW 0x0000_0780
	UINT32 reg_text_stat_win1_start_x       :12;	//(11:0,NA,1920) //Text temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_text_stat_win1_start_y       :12;	//(27:16,NA,0) //Text temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01164 RW 0x0438_0EFF
	UINT32 reg_text_stat_win1_end_x         :12;	//(11:0,NA,3839) //Text temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_text_stat_win1_end_y         :12;	//(27:16,NA,1080) //Text temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_FD_TEXT_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01170 RO 0x0000_0000
	UINT32 ro_text_status_window0           :32;	//(31:0,NA,0) //Tmap temporal text status register (window0)
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01174 RO 0x0000_0000
	UINT32 ro_text_status_window1           :32;	//(31:0,NA,0) //Tmap temporal text status register (window1)
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01178 RO 0x0000_0000
	UINT32 ro_text_status_0                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_1                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0117C RO 0x0000_0000
	UINT32 ro_text_status_2                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_3                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01180 RO 0x0000_0000
	UINT32 ro_text_status_4                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_5                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01184 RO 0x0000_0000
	UINT32 ro_text_status_6                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_7                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01188 RO 0x0000_0000
	UINT32 ro_text_status_8                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_9                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0118C RO 0x0000_0000
	UINT32 ro_text_status_10                :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_11                :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_2KY_SHP_CORE_TEXT_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01190 RW 0x0000_0000
	UINT32 reg_text_blend_sp_der_en         :1;	//(0:0,NA,0) //Text blend enable (SP/DER blend with MMD)
	UINT32 resvd0                           :3;
	UINT32 reg_text_blend_sp_out_en         :1;	//(4:4,NA,0) //Text blend enable (SP text blend)
	UINT32 resvd1                           :3;
	UINT32 reg_text_blend_pti_out_en        :1;	//(8:8,NA,0) //Text blend enable (PTI text blend)
	UINT32 resvd2                           :3;
	UINT32 reg_text_blend_snr_out_en        :1;	//(12:12,NA,0) //Text blend enable (SNR text blend)
	UINT32 resvd3                           :3;
	UINT32 reg_text_dp_sum_sp_en            :1;	//(16:16,NA,0) //DP sum input selection (0: SP coring out, 1: SP text blend out)
	UINT32 resvd4                           :3;
	UINT32 reg_text_dp_sum_pti_en           :1;	//(20:20,NA,0) //DP sum input selection (0: PTI coring out, 1: PTI text blend out)
	UINT32 resvd5                           :3;
	UINT32 reg_text_dp_sum_snr_en           :1;	//(24:24,NA,0) //DP sum input selection (0: SNR coring out, 1: SNR text blend out)
	UINT32 resvd6                           :7;
	};
}PE_O26_2KY_SHP_TEXT_BLEND_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01194 RW 0x5050_0000
	UINT32 reg_text_blend_mmd_lut_y0        :8;	//(7:0,NA,0) //Text blend LUT (SP/DER blend MMD), y0
	UINT32 reg_text_blend_mmd_lut_x0        :8;	//(15:8,NA,0) //Text blend LUT (SP/DER blend MMD), x0
	UINT32 reg_text_blend_mmd_lut_y1        :8;	//(23:16,NA,80) //Text blend LUT (SP/DER blend MMD), y1
	UINT32 reg_text_blend_mmd_lut_x1        :8;	//(31:24,NA,80) //Text blend LUT (SP/DER blend MMD), x1
	};
}PE_O26_2KY_SHP_TEXT_BLEND_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01198 RW 0xFFFF_9696
	UINT32 reg_text_blend_mmd_lut_y2        :8;	//(7:0,NA,150) //Text blend LUT (SP/DER blend MMD), y2
	UINT32 reg_text_blend_mmd_lut_x2        :8;	//(15:8,NA,150) //Text blend LUT (SP/DER blend MMD), x2
	UINT32 reg_text_blend_mmd_lut_y3        :8;	//(23:16,NA,255) //Text blend LUT (SP/DER blend MMD), y3
	UINT32 reg_text_blend_mmd_lut_x3        :8;	//(31:24,NA,255) //Text blend LUT (SP/DER blend MMD), x3
	};
}PE_O26_2KY_SHP_TEXT_BLEND_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0119C RW 0x5AC8_0000
	UINT32 reg_text_blend_sp_lut_y0         :8;	//(7:0,NA,0) //Text blend LUT (SP text blend), y0
	UINT32 reg_text_blend_sp_lut_x0         :8;	//(15:8,NA,0) //Text blend LUT (SP text blend), x0
	UINT32 reg_text_blend_sp_lut_y1         :8;	//(23:16,NA,200) //Text blend LUT (SP text blend), y1
	UINT32 reg_text_blend_sp_lut_x1         :8;	//(31:24,NA,90) //Text blend LUT (SP text blend), x1
	};
}PE_O26_2KY_SHP_TEXT_BLEND_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011A0 RW 0xDCFF_B4FF
	UINT32 reg_text_blend_sp_lut_y2         :8;	//(7:0,NA,255) //Text blend LUT (SP text blend), y2
	UINT32 reg_text_blend_sp_lut_x2         :8;	//(15:8,NA,180) //Text blend LUT (SP text blend), x2
	UINT32 reg_text_blend_sp_lut_y3         :8;	//(23:16,NA,255) //Text blend LUT (SP text blend), y3
	UINT32 reg_text_blend_sp_lut_x3         :8;	//(31:24,NA,220) //Text blend LUT (SP text blend), x3
	};
}PE_O26_2KY_SHP_TEXT_BLEND_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011A4 RW 0x5A00_0000
	UINT32 reg_text_blend_pti_lut_y0        :8;	//(7:0,NA,0) //Text blend LUT (PTI text blend), y0
	UINT32 reg_text_blend_pti_lut_x0        :8;	//(15:8,NA,0) //Text blend LUT (PTI text blend), x0
	UINT32 reg_text_blend_pti_lut_y1        :8;	//(23:16,NA,0) //Text blend LUT (PTI text blend), y1
	UINT32 reg_text_blend_pti_lut_x1        :8;	//(31:24,NA,90) //Text blend LUT (PTI text blend), x1
	};
}PE_O26_2KY_SHP_TEXT_BLEND_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011A8 RW 0xFF00_B400
	UINT32 reg_text_blend_pti_lut_y2        :8;	//(7:0,NA,0) //Text blend LUT (PTI text blend), y2
	UINT32 reg_text_blend_pti_lut_x2        :8;	//(15:8,NA,180) //Text blend LUT (PTI text blend), x2
	UINT32 reg_text_blend_pti_lut_y3        :8;	//(23:16,NA,0) //Text blend LUT (PTI text blend), y3
	UINT32 reg_text_blend_pti_lut_x3        :8;	//(31:24,NA,255) //Text blend LUT (PTI text blend), x3
	};
}PE_O26_2KY_SHP_TEXT_BLEND_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011AC RW 0x50C8_0000
	UINT32 reg_text_blend_snr_lut_y0        :8;	//(7:0,NA,0) //Text blend LUT (SNR text blend), y0
	UINT32 reg_text_blend_snr_lut_x0        :8;	//(15:8,NA,0) //Text blend LUT (SNR text blend), x0
	UINT32 reg_text_blend_snr_lut_y1        :8;	//(23:16,NA,200) //Text blend LUT (SNR text blend), y1
	UINT32 reg_text_blend_snr_lut_x1        :8;	//(31:24,NA,80) //Text blend LUT (SNR text blend), x1
	};
}PE_O26_2KY_SHP_TEXT_BLEND_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011B0 RW 0xFFFF_96FF
	UINT32 reg_text_blend_snr_lut_y2        :8;	//(7:0,NA,255) //Text blend LUT (SNR text blend), y2
	UINT32 reg_text_blend_snr_lut_x2        :8;	//(15:8,NA,150) //Text blend LUT (SNR text blend), x2
	UINT32 reg_text_blend_snr_lut_y3        :8;	//(23:16,NA,255) //Text blend LUT (SNR text blend), y3
	UINT32 reg_text_blend_snr_lut_x3        :8;	//(31:24,NA,255) //Text blend LUT (SNR text blend), x3
	};
}PE_O26_2KY_SHP_TEXT_BLEND_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011B4 RW 0x32FF_0000
	UINT32 reg_text_blend_dpsum_lut_y0      :8;	//(7:0,NA,0) //Text blend LUT (DP sum blend), y0
	UINT32 reg_text_blend_dpsum_lut_x0      :8;	//(15:8,NA,0) //Text blend LUT (DP sum blend), x0
	UINT32 reg_text_blend_dpsum_lut_y1      :8;	//(23:16,NA,255) //Text blend LUT (DP sum blend), y1
	UINT32 reg_text_blend_dpsum_lut_x1      :8;	//(31:24,NA,50) //Text blend LUT (DP sum blend), x1
	};
}PE_O26_2KY_SHP_TEXT_BLEND_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011B8 RW 0xFFFF_78FF
	UINT32 reg_text_blend_dpsum_lut_y2      :8;	//(7:0,NA,255) //Text blend LUT (DP sum blend), y2
	UINT32 reg_text_blend_dpsum_lut_x2      :8;	//(15:8,NA,120) //Text blend LUT (DP sum blend), x2
	UINT32 reg_text_blend_dpsum_lut_y3      :8;	//(23:16,NA,255) //Text blend LUT (DP sum blend), y3
	UINT32 reg_text_blend_dpsum_lut_x3      :8;	//(31:24,NA,255) //Text blend LUT (DP sum blend), x3
	};
}PE_O26_2KY_SHP_TEXT_BLEND_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011BC RW 0x320A_0000
	UINT32 reg_text_blend_dpsum_nt_lut_y0   :8;	//(7:0,NA,0) //Text blend LUT (DP sum blend, non-text), y0
	UINT32 reg_text_blend_dpsum_nt_lut_x0   :8;	//(15:8,NA,0) //Text blend LUT (DP sum blend, non-text), x0
	UINT32 reg_text_blend_dpsum_nt_lut_y1   :8;	//(23:16,NA,10) //Text blend LUT (DP sum blend, non-text), y1
	UINT32 reg_text_blend_dpsum_nt_lut_x1   :8;	//(31:24,NA,50) //Text blend LUT (DP sum blend, non-text), x1
	};
}PE_O26_2KY_SHP_TEXT_BLEND_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011C0 RW 0xFF28_7814
	UINT32 reg_text_blend_dpsum_nt_lut_y2   :8;	//(7:0,NA,20) //Text blend LUT (DP sum blend, non-text), y2
	UINT32 reg_text_blend_dpsum_nt_lut_x2   :8;	//(15:8,NA,120) //Text blend LUT (DP sum blend, non-text), x2
	UINT32 reg_text_blend_dpsum_nt_lut_y3   :8;	//(23:16,NA,40) //Text blend LUT (DP sum blend, non-text), y3
	UINT32 reg_text_blend_dpsum_nt_lut_x3   :8;	//(31:24,NA,255) //Text blend LUT (DP sum blend, non-text), x3
	};
}PE_O26_2KY_SHP_TEXT_BLEND_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011D0 RW 0x0000_0000
	UINT32 reg_force_block_en               :1;	//(0:0,NA,0) //Tmap temporal forcing the number of block enable
	UINT32 resvd0                           :15;
	UINT32 reg_block_no_v                   :7;	//(22:16,NA,0) //Tmap temporal forcing the number of vertical block
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_h                   :8;	//(31:24,NA,0) //Tmap temporal forcing the number of horizontal block
	};
}PE_O26_2KY_SHP_TEMPORAL_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA011D4 RW 0x0000_0000
	UINT32 reg_block_size_v                 :7;	//(6:0,NA,0) //Tmap temporal forcing vertical block size
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,NA,0) //Tmap temporal forcing horizontal block size
	UINT32 resvd1                           :1;
	UINT32 reg_last_block_size_v            :7;	//(22:16,NA,0) //Tmap temporal forcing last vertical block size
	UINT32 resvd2                           :1;
	UINT32 reg_last_block_size_h            :7;	//(30:24,NA,0) //Tmap temporal forcing last horizontal block size
	UINT32 resvd3                           :1;
	};
}PE_O26_2KY_SHP_TEMPORAL_MAP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01200 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01204 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01208 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0120C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter 4K Last = 2160
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter 4K Last = 2160
	UINT32 resvd1                           :4;
	};
}PE_O26_2KY_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01210 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_2KY_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01214 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_2KY_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01218 RW 0x0000_0000
	UINT32 reg_mask_in_ready_en             :1;	//(0:0,NA,0) //Input ready force 1
	UINT32 resvd0                           :3;
	UINT32 reg_mask_out_valid_en            :1;	//(4:4,NA,0) //Output valid force 1
	UINT32 resvd1                           :3;
	UINT32 reg_mask_out_ready_en            :1;	//(8:8,NA,0) //Output ready force 1
	UINT32 resvd2                           :3;
	UINT32 reg_mask_in_valid_en             :1;	//(12:12,NA,0) //Input valid force 1
	UINT32 resvd3                           :19;
	};
}PE_O26_2KY_SHP_CORE_RDY_VLD_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01260 RO 0x0000_0000
	UINT32 reg_status_a_avg                 :32;	//(31:0,NA,0) //FD status register (a_avg)
	};
}PE_O26_2KY_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01264 RO 0x0000_0000
	UINT32 reg_status_t_avg                 :32;	//(31:0,NA,0) //FD status register (t_avg)
	};
}PE_O26_2KY_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01268 RO 0x0000_0000
	UINT32 reg_status_e_avg                 :32;	//(31:0,NA,0) //FD status register (e_avg)
	};
}PE_O26_2KY_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0126C RO 0x0000_0000
	UINT32 reg_status_d_avg                 :32;	//(31:0,NA,0) //FD status register (d_avg)
	};
}PE_O26_2KY_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01300 RO 0x0000_0000
	UINT32 ro_tmap_status_window0           :32;	//(31:0,NA,0) //Tmap temporal texture status register (window0)
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01304 RO 0x0000_0000
	UINT32 ro_tmap_status_window1           :32;	//(31:0,NA,0) //Tmap temporal texture status register (window1)
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01308 RO 0x0000_0000
	UINT32 ro_tmap_status_0                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_1                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0130C RO 0x0000_0000
	UINT32 ro_tmap_status_2                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_3                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01310 RO 0x0000_0000
	UINT32 ro_tmap_status_4                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_5                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01314 RO 0x0000_0000
	UINT32 ro_tmap_status_6                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_7                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01318 RO 0x0000_0000
	UINT32 ro_tmap_status_8                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_9                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0131C RO 0x0000_0000
	UINT32 ro_tmap_status_10                :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_11                :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_2KY_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01320 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_sel_output                   :1;	//(4:4,NA,0x0) //Output selection (0:ellipse gain, 1:box map)
	UINT32 resvd1                           :3;
	UINT32 reg_ellipse_offset               :8;	//(15:8,NA,0x0) //Ellipse gain offset threshold
	UINT32 resvd2                           :12;
	UINT32 reg_ellipse_debug_en             :1;	//(28:28,NA,0x0) //Debug display enable
	UINT32 resvd3                           :3;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01324 RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,NA,0x0) //Ellipse0 position, w, start
	UINT32 reg_f0_h1_pos                    :12;	//(23:12,NA,0x0) //Ellipse0 position, h, start
	UINT32 reg_f0_enable                    :1;	//(24:24,NA,0x0) //Ellipse0 enable
	UINT32 resvd                            :7;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01328 RW 0x0000_0000
	UINT32 reg_f0_w2_pos                    :12;	//(11:0,NA,0x0) //Ellipse0 position, w, end
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,NA,0x0) //Ellipse0 position, h, end
	UINT32 resvd                            :8;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0132C RW 0x0000_0000
	UINT32 reg_f0_e_mul_b                   :9;	//(8:0,NA,0x0) //Ellipse0 factor (V) (4.5bit)
	UINT32 resvd0                           :3;
	UINT32 reg_f0_e_mul_a                   :9;	//(20:12,NA,0x0) //Ellipse0 factor (H) (4.5bit)
	UINT32 resvd1                           :3;
	UINT32 reg_f0_ellipse_master            :8;	//(31:24,NA,0x0) //Ellipse0 master gain
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01330 RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,NA,0x0) //Ellipse1 position, w, start
	UINT32 reg_f1_h1_pos                    :12;	//(23:12,NA,0x0) //Ellipse1 position, h, start
	UINT32 reg_f1_enable                    :1;	//(24:24,NA,0x0) //Ellipse1 enable
	UINT32 resvd                            :7;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01334 RW 0x0000_0000
	UINT32 reg_f1_w2_pos                    :12;	//(11:0,NA,0x0) //Ellipse1 position, w, end
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,NA,0x0) //Ellipse1 position, h, end
	UINT32 resvd                            :8;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01338 RW 0x0000_0000
	UINT32 reg_f1_e_mul_b                   :9;	//(8:0,NA,0x0) //Ellipse1 factor (V) (4.5bit)
	UINT32 resvd0                           :3;
	UINT32 reg_f1_e_mul_a                   :9;	//(20:12,NA,0x0) //Ellipse1 factor (H) (4.5bit)
	UINT32 resvd1                           :3;
	UINT32 reg_f1_ellipse_master            :8;	//(31:24,NA,0x0) //Ellipse1 master gain
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0133C RW 0x0000_0000
	UINT32 reg_f2_w1_pos                    :12;	//(11:0,NA,0x0) //Ellipse2 position, w, start
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,NA,0x0) //Ellipse2 position, h, start
	UINT32 reg_f2_enable                    :1;	//(24:24,NA,0x0) //Ellipse2 enable
	UINT32 resvd                            :7;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01340 RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,NA,0x0) //Ellipse2 position, w, end
	UINT32 reg_f2_h2_pos                    :12;	//(23:12,NA,0x0) //Ellipse2 position, h, end
	UINT32 resvd                            :8;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01344 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,NA,0x0) //Ellipse2 factor (V) (4.5bit)
	UINT32 resvd0                           :3;
	UINT32 reg_f2_e_mul_a                   :9;	//(20:12,NA,0x0) //Ellipse2 factor (H) (4.5bit)
	UINT32 resvd1                           :3;
	UINT32 reg_f2_ellipse_master            :8;	//(31:24,NA,0x0) //Ellipse2 master gain
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01348 RW 0x0000_0000
	UINT32 reg_f3_w1_pos                    :12;	//(11:0,NA,0x0) //Ellipse3 position, w, start
	UINT32 reg_f3_h1_pos                    :12;	//(23:12,NA,0x0) //Ellipse3 position, h, start
	UINT32 reg_f3_enable                    :1;	//(24:24,NA,0x0) //Ellipse3 enable
	UINT32 resvd                            :7;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0134C RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,NA,0x0) //Ellipse3 position, w, end
	UINT32 reg_f3_h2_pos                    :12;	//(23:12,NA,0x0) //Ellipse3 position, h, end
	UINT32 resvd                            :8;
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01350 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,NA,0x0) //Ellipse3 factor (V) (4.5bit)
	UINT32 resvd0                           :3;
	UINT32 reg_f3_e_mul_a                   :9;	//(20:12,NA,0x0) //Ellipse3 factor (H) (4.5bit)
	UINT32 resvd1                           :3;
	UINT32 reg_f3_ellipse_master            :8;	//(31:24,NA,0x0) //Ellipse3 master gain
	};
}PE_O26_2KY_SHP_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01354 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //Ellipse gain LUT, y0
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //Ellipse gain LUT, x0
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //Ellipse gain LUT, y1
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //Ellipse gain LUT, x1
	};
}PE_O26_2KY_SHP_ELLIPSE_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01358 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //Ellipse gain LUT, y2
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //Ellipse gain LUT, x2
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //Ellipse gain LUT, y3
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //Ellipse gain LUT, x3
	};
}PE_O26_2KY_SHP_ELLIPSE_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01360 RW 0x0000_0000
	UINT32 reg_ellips_gain_en               :1;	//(0:0,NA,0) //Ellipse gain enable (0: not use ellipse gain, 1: use ellipse gain)
	UINT32 resvd0                           :3;
	UINT32 reg_luma_dp_blend_en             :1;	//(4:4,NA,0) //Luma blend enable
	UINT32 resvd1                           :3;
	UINT32 reg_luma_dp_blend_debug_sel_en   :1;	//(8:8,NA,0) //Debug mode (0: gain, 1: bypass Y)
	UINT32 resvd2                           :23;
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01364 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //Luma blend LUT, y0
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //Luma blend LUT, x0
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //Luma blend LUT, y1
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //Luma blend LUT, x1
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01368 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //Luma blend LUT, y2
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //Luma blend LUT, x2
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //Luma blend LUT, y3
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //Luma blend LUT, x3
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0136C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y4                  :8;	//(7:0,NA,192) //Luma blend LUT, y4
	UINT32 reg_gain_lut_x4                  :8;	//(15:8,NA,0) //Luma blend LUT, x4
	UINT32 reg_gain_lut_y5                  :8;	//(23:16,NA,192) //Luma blend LUT, y5
	UINT32 reg_gain_lut_x5                  :8;	//(31:24,NA,0) //Luma blend LUT, x5
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01370 RW 0x8020_8020
	UINT32 reg_gain_lut_y6                  :8;	//(7:0,NA,32) //Luma blend LUT, y6
	UINT32 reg_gain_lut_x6                  :8;	//(15:8,NA,128) //Luma blend LUT, x6
	UINT32 reg_gain_lut_y7                  :8;	//(23:16,NA,32) //Luma blend LUT, y7
	UINT32 reg_gain_lut_x7                  :8;	//(31:24,NA,128) //Luma blend LUT, x7
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01374 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y8                  :8;	//(7:0,NA,192) //Luma blend LUT, y8
	UINT32 reg_gain_lut_x8                  :8;	//(15:8,NA,0) //Luma blend LUT, x8
	UINT32 reg_gain_lut_y9                  :8;	//(23:16,NA,192) //Luma blend LUT, y9
	UINT32 reg_gain_lut_x9                  :8;	//(31:24,NA,0) //Luma blend LUT, x9
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01378 RW 0x8020_8020
	UINT32 reg_gain_lut_y10                 :8;	//(7:0,NA,32) //Luma blend LUT, y10
	UINT32 reg_gain_lut_x10                 :8;	//(15:8,NA,128) //Luma blend LUT, x10
	UINT32 reg_gain_lut_y11                 :8;	//(23:16,NA,32) //Luma blend LUT, y11
	UINT32 reg_gain_lut_x11                 :8;	//(31:24,NA,128) //Luma blend LUT, x11
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0137C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y12                 :8;	//(7:0,NA,192) //Luma blend LUT, y12
	UINT32 reg_gain_lut_x12                 :8;	//(15:8,NA,0) //Luma blend LUT, x12
	UINT32 reg_gain_lut_y13                 :8;	//(23:16,NA,192) //Luma blend LUT, y13
	UINT32 reg_gain_lut_x13                 :8;	//(31:24,NA,0) //Luma blend LUT, x13
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01380 RW 0x8020_8020
	UINT32 reg_gain_lut_y14                 :8;	//(7:0,NA,32) //Luma blend LUT, y14
	UINT32 reg_gain_lut_x14                 :8;	//(15:8,NA,128) //Luma blend LUT, x14
	UINT32 reg_gain_lut_y15                 :8;	//(23:16,NA,32) //Luma blend LUT, y15
	UINT32 reg_gain_lut_x15                 :8;	//(31:24,NA,128) //Luma blend LUT, x15
	};
}PE_O26_2KY_SHP_LUMA_BLEND_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01384 RW 0x0000_0000
	UINT32 reg_sm_blender_en                :1;	//(0:0,NA,0) //SM blend (0: OFF, 1: ON)
	UINT32 reg_sm_blender_dly_debug_en      :1;	//(1:1,NA,0) //Output motion map debug enable
	UINT32 reg_sm_blender_inter_debug_en    :1;	//(2:2,NA,0) //Interpolation motion map debug enable
	UINT32 resvd0                           :5;
	UINT32 reg_sm_blender_inter_alpha_value :8;	//(15:08,NA,0) //Interpolation motion map alpha blending debug alpha value (0~255)
	UINT32 reg_sm_blender_inter_alpha_debug_en :1;	//(16:16,NA,0) //Interpolation motion map alpha blending debug enable
	UINT32 resvd1                           :3;
	UINT32 reg_sm_blender_dly_alpha_value   :8;	//(27:20,NA,0) //Output motion map alpha blending debug alpha value (0~255)
	UINT32 reg_sm_blender_dly_alpha_debug_en :1;	//(28:28,NA,0) //Output motion map alpha blending debug enable
	UINT32 resvd2                           :3;
	};
}PE_O26_2KY_SHP_SM_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01388 RW 0x2080_00FF
	UINT32 reg_sm_pre_lut_y0                :8;	//(7:0,NA,255) //SM blend LUT, y0
	UINT32 reg_sm_pre_lut_x0                :8;	//(15:8,NA,0) //SM blend LUT, x0
	UINT32 reg_sm_pre_lut_y1                :8;	//(23:16,NA,128) //SM blend LUT, y1
	UINT32 reg_sm_pre_lut_x1                :8;	//(31:24,NA,32) //SM blend LUT, x1
	};
}PE_O26_2KY_SHP_SM_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0138C RW 0x4040_8000
	UINT32 reg_sm_pre_lut_y2                :8;	//(7:0,NA,0) //SM blend LUT, y2
	UINT32 reg_sm_pre_lut_x2                :8;	//(15:8,NA,128) //SM blend LUT, x2
	UINT32 reg_sm_pre_lut_y3                :8;	//(23:16,NA,64) //SM blend LUT, y3
	UINT32 reg_sm_pre_lut_x3                :8;	//(31:24,NA,64) //SM blend LUT, x3
	};
}PE_O26_2KY_SHP_SM_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA013F0 RW 0x0000_0000
	UINT32 cvd_pattern_detect				:1;
	UINT32 color_bar						:1;
	UINT32 vfy_glb_en						:1;
	UINT32 resvd							:29;
	};
}PE_O26_2KY_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA013F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA013F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA013FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KY_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O26_2KY_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCCA00C00
	PE_O26_2KY_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCCA00C04
	PE_O26_2KY_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCCA00C08
	PE_O26_2KY_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCCA00C0C
	UINT32                                                   reserved0;	//0xCCA00C10
	UINT32                                                   reserved1;	//0xCCA00C14
	UINT32                                                   reserved2;	//0xCCA00C18
	UINT32                                                   reserved3;	//0xCCA00C1C
	UINT32                                                   reserved4;	//0xCCA00C20
	UINT32                                                   reserved5;	//0xCCA00C24
	UINT32                                                   reserved6;	//0xCCA00C28
	UINT32                                                   reserved7;	//0xCCA00C2C
	UINT32                                                   reserved8;	//0xCCA00C30
	UINT32                                                   reserved9;	//0xCCA00C34
	UINT32                                                  reserved10;	//0xCCA00C38
	UINT32                                                  reserved11;	//0xCCA00C3C
	PE_O26_2KY_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCCA00C40
	UINT32                                                  reserved12;	//0xCCA00C44
	UINT32                                                  reserved13;	//0xCCA00C48
	UINT32                                                  reserved14;	//0xCCA00C4C
	UINT32                                                  reserved15;	//0xCCA00C50
	UINT32                                                  reserved16;	//0xCCA00C54
	UINT32                                                  reserved17;	//0xCCA00C58
	UINT32                                                  reserved18;	//0xCCA00C5C
	PE_O26_2KY_SHP_GAIN_MAP_CTRL_00_T             shp_gain_map_ctrl_00;	//0xCCA00C60
	UINT32                                                  reserved19;	//0xCCA00C64
	UINT32                                                  reserved20;	//0xCCA00C68
	UINT32                                                  reserved21;	//0xCCA00C6C
	UINT32                                                  reserved22;	//0xCCA00C70
	UINT32                                                  reserved23;	//0xCCA00C74
	UINT32                                                  reserved24;	//0xCCA00C78
	UINT32                                                  reserved25;	//0xCCA00C7C
	UINT32                                                  reserved26;	//0xCCA00C80
	UINT32                                                  reserved27;	//0xCCA00C84
	UINT32                                                  reserved28;	//0xCCA00C88
	UINT32                                                  reserved29;	//0xCCA00C8C
	UINT32                                                  reserved30;	//0xCCA00C90
	UINT32                                                  reserved31;	//0xCCA00C94
	UINT32                                                  reserved32;	//0xCCA00C98
	UINT32                                                  reserved33;	//0xCCA00C9C
	UINT32                                                  reserved34;	//0xCCA00CA0
	UINT32                                                  reserved35;	//0xCCA00CA4
	UINT32                                                  reserved36;	//0xCCA00CA8
	UINT32                                                  reserved37;	//0xCCA00CAC
	UINT32                                                  reserved38;	//0xCCA00CB0
	UINT32                                                  reserved39;	//0xCCA00CB4
	UINT32                                                  reserved40;	//0xCCA00CB8
	UINT32                                                  reserved41;	//0xCCA00CBC
	UINT32                                                  reserved42;	//0xCCA00CC0
	UINT32                                                  reserved43;	//0xCCA00CC4
	UINT32                                                  reserved44;	//0xCCA00CC8
	UINT32                                                  reserved45;	//0xCCA00CCC
	UINT32                                                  reserved46;	//0xCCA00CD0
	UINT32                                                  reserved47;	//0xCCA00CD4
	UINT32                                                  reserved48;	//0xCCA00CD8
	UINT32                                                  reserved49;	//0xCCA00CDC
	UINT32                                                  reserved50;	//0xCCA00CE0
	UINT32                                                  reserved51;	//0xCCA00CE4
	UINT32                                                  reserved52;	//0xCCA00CE8
	UINT32                                                  reserved53;	//0xCCA00CEC
	PE_O26_2KY_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCCA00CF0
	UINT32                                                  reserved54;	//0xCCA00CF4
	UINT32                                                  reserved55;	//0xCCA00CF8
	UINT32                                                  reserved56;	//0xCCA00CFC
	PE_O26_2KY_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCCA00D00
	PE_O26_2KY_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCCA00D04
	PE_O26_2KY_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCCA00D08
	PE_O26_2KY_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCCA00D0C
	PE_O26_2KY_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCCA00D10
	PE_O26_2KY_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCCA00D14
	PE_O26_2KY_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCCA00D18
	PE_O26_2KY_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCCA00D1C
	PE_O26_2KY_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCCA00D20
	PE_O26_2KY_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCCA00D24
	PE_O26_2KY_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCCA00D28
	PE_O26_2KY_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCCA00D2C
	PE_O26_2KY_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCCA00D30
	PE_O26_2KY_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCCA00D34
	PE_O26_2KY_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCCA00D38
	PE_O26_2KY_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCCA00D3C
	PE_O26_2KY_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCCA00D40
	PE_O26_2KY_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCCA00D44
	PE_O26_2KY_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCCA00D48
	PE_O26_2KY_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCCA00D4C
	PE_O26_2KY_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCCA00D50
	PE_O26_2KY_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCCA00D54
	PE_O26_2KY_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCCA00D58
	UINT32                                                  reserved57;	//0xCCA00D5C
	PE_O26_2KY_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCCA00D60
	PE_O26_2KY_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCCA00D64
	PE_O26_2KY_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCCA00D68
	PE_O26_2KY_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCCA00D6C
	PE_O26_2KY_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCCA00D70
	PE_O26_2KY_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCCA00D74
	PE_O26_2KY_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCCA00D78
	PE_O26_2KY_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCCA00D7C
	PE_O26_2KY_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCCA00D80
	PE_O26_2KY_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCCA00D84
	PE_O26_2KY_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCCA00D88
	PE_O26_2KY_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCCA00D8C
	PE_O26_2KY_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCCA00D90
	PE_O26_2KY_SHP_APL_CTRL_00_T                       shp_apl_ctrl_00;	//0xCCA00D94
	UINT32                                                  reserved58;	//0xCCA00D98
	UINT32                                                  reserved59;	//0xCCA00D9C
	PE_O26_2KY_SHP_LC_CTRL_00_T                         shp_lc_ctrl_00;	//0xCCA00DA0
	PE_O26_2KY_SHP_LC_CTRL_01_T                         shp_lc_ctrl_01;	//0xCCA00DA4
	PE_O26_2KY_SHP_LC_CTRL_02_T                         shp_lc_ctrl_02;	//0xCCA00DA8
	PE_O26_2KY_SHP_LC_CTRL_03_T                         shp_lc_ctrl_03;	//0xCCA00DAC
	PE_O26_2KY_SHP_LC_CTRL_04_T                         shp_lc_ctrl_04;	//0xCCA00DB0
	UINT32                                                  reserved60;	//0xCCA00DB4
	UINT32                                                  reserved61;	//0xCCA00DB8
	UINT32                                                  reserved62;	//0xCCA00DBC
	PE_O26_2KY_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCCA00DC0
	PE_O26_2KY_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCCA00DC4
	PE_O26_2KY_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCCA00DC8
	PE_O26_2KY_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCCA00DCC
	PE_O26_2KY_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCCA00DD0
	PE_O26_2KY_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCCA00DD4
	PE_O26_2KY_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCCA00DD8
	PE_O26_2KY_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCCA00DDC
	PE_O26_2KY_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCCA00DE0
	PE_O26_2KY_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCCA00DE4
	PE_O26_2KY_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCCA00DE8
	PE_O26_2KY_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCCA00DEC
	PE_O26_2KY_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCCA00DF0
	PE_O26_2KY_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCCA00DF4
	PE_O26_2KY_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCCA00DF8
	PE_O26_2KY_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCCA00DFC
	PE_O26_2KY_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCCA00E00
	PE_O26_2KY_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCCA00E04
	PE_O26_2KY_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCCA00E08
	PE_O26_2KY_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCCA00E0C
	PE_O26_2KY_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCCA00E10
	UINT32                                                  reserved63;	//0xCCA00E14
	UINT32                                                  reserved64;	//0xCCA00E18
	UINT32                                                  reserved65;	//0xCCA00E1C
	PE_O26_2KY_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCCA00E20
	PE_O26_2KY_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCCA00E24
	PE_O26_2KY_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCCA00E28
	PE_O26_2KY_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCCA00E2C
	PE_O26_2KY_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCCA00E30
	UINT32                                                  reserved66;	//0xCCA00E34
	UINT32                                                  reserved67;	//0xCCA00E38
	UINT32                                                  reserved68;	//0xCCA00E3C
	PE_O26_2KY_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCCA00E40
	PE_O26_2KY_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCCA00E44
	PE_O26_2KY_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCCA00E48
	PE_O26_2KY_SHP_TGEN_CTRL_03_T                     shp_tgen_ctrl_03;	//0xCCA00E4C
	UINT32                                                  reserved69;	//0xCCA00E50
	PE_O26_2KY_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCCA00E54
	PE_O26_2KY_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCCA00E58
	PE_O26_2KY_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCCA00E5C
	PE_O26_2KY_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCCA00E60
	PE_O26_2KY_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCCA00E64
	PE_O26_2KY_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCCA00E68
	PE_O26_2KY_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCCA00E6C
	PE_O26_2KY_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCCA00E70
	PE_O26_2KY_SHP_SNR_CTRL_00_T                       shp_snr_ctrl_00;	//0xCCA00E74
	UINT32                                                  reserved70;	//0xCCA00E78
	UINT32                                                  reserved71;	//0xCCA00E7C
	PE_O26_2KY_SHP_DCTP_CTRL_00_T                     shp_dctp_ctrl_00;	//0xCCA00E80
	PE_O26_2KY_SHP_DCTP_CTRL_01_T                     shp_dctp_ctrl_01;	//0xCCA00E84
	PE_O26_2KY_SHP_DCTP_CTRL_02_T                     shp_dctp_ctrl_02;	//0xCCA00E88
	PE_O26_2KY_SHP_DCTP_CTRL_03_T                     shp_dctp_ctrl_03;	//0xCCA00E8C
	PE_O26_2KY_SHP_DCTP_CTRL_04_T                     shp_dctp_ctrl_04;	//0xCCA00E90
	PE_O26_2KY_SHP_DCTP_CTRL_05_T                     shp_dctp_ctrl_05;	//0xCCA00E94
	PE_O26_2KY_SHP_DCTP_CTRL_06_T                     shp_dctp_ctrl_06;	//0xCCA00E98
	PE_O26_2KY_SHP_DCTP_CTRL_07_T                     shp_dctp_ctrl_07;	//0xCCA00E9C
	PE_O26_2KY_SHP_DCTP_CTRL_08_T                     shp_dctp_ctrl_08;	//0xCCA00EA0
	PE_O26_2KY_SHP_DCTP_CTRL_09_T                     shp_dctp_ctrl_09;	//0xCCA00EA4
	PE_O26_2KY_SHP_DCTP_CTRL_0A_T                     shp_dctp_ctrl_0a;	//0xCCA00EA8
	PE_O26_2KY_SHP_DCTP_CTRL_0B_T                     shp_dctp_ctrl_0b;	//0xCCA00EAC
	PE_O26_2KY_SHP_DCTP_CTRL_0C_T                     shp_dctp_ctrl_0c;	//0xCCA00EB0
	PE_O26_2KY_SHP_DCTP_CTRL_0D_T                     shp_dctp_ctrl_0d;	//0xCCA00EB4
	PE_O26_2KY_SHP_DCTP_CTRL_0E_T                     shp_dctp_ctrl_0e;	//0xCCA00EB8
	PE_O26_2KY_SHP_DCTP_CTRL_0F_T                     shp_dctp_ctrl_0f;	//0xCCA00EBC
	PE_O26_2KY_SHP_DCTP_CTRL_10_T                     shp_dctp_ctrl_10;	//0xCCA00EC0
	PE_O26_2KY_SHP_DCTP_CTRL_11_T                     shp_dctp_ctrl_11;	//0xCCA00EC4
	PE_O26_2KY_SHP_DCTP_CTRL_12_T                     shp_dctp_ctrl_12;	//0xCCA00EC8
	PE_O26_2KY_SHP_DCTP_CTRL_13_T                     shp_dctp_ctrl_13;	//0xCCA00ECC
	PE_O26_2KY_SHP_DCTP_CTRL_14_T                     shp_dctp_ctrl_14;	//0xCCA00ED0
	PE_O26_2KY_SHP_DCTP_CTRL_15_T                     shp_dctp_ctrl_15;	//0xCCA00ED4
	PE_O26_2KY_SHP_DCTP_CTRL_16_T                     shp_dctp_ctrl_16;	//0xCCA00ED8
	PE_O26_2KY_SHP_DCTP_CTRL_17_T                     shp_dctp_ctrl_17;	//0xCCA00EDC
	PE_O26_2KY_SHP_DCTP_CTRL_18_T                     shp_dctp_ctrl_18;	//0xCCA00EE0
	PE_O26_2KY_SHP_DCTP_CTRL_19_T                     shp_dctp_ctrl_19;	//0xCCA00EE4
	PE_O26_2KY_SHP_DCTP_CTRL_1A_T                     shp_dctp_ctrl_1a;	//0xCCA00EE8
	PE_O26_2KY_SHP_DCTP_CTRL_1B_T                     shp_dctp_ctrl_1b;	//0xCCA00EEC
	PE_O26_2KY_SHP_DCTP_CTRL_1C_T                     shp_dctp_ctrl_1c;	//0xCCA00EF0
	PE_O26_2KY_SHP_DCTP_CTRL_1D_T                     shp_dctp_ctrl_1d;	//0xCCA00EF4
	PE_O26_2KY_SHP_DCTP_CTRL_1E_T                     shp_dctp_ctrl_1e;	//0xCCA00EF8
	PE_O26_2KY_SHP_DCTP_CTRL_1F_T                     shp_dctp_ctrl_1f;	//0xCCA00EFC
	PE_O26_2KY_SHP_NNTG_CTRL_00_T                     shp_nntg_ctrl_00;	//0xCCA00F00
	PE_O26_2KY_SHP_NNTG_CTRL_01_T                     shp_nntg_ctrl_01;	//0xCCA00F04
	PE_O26_2KY_SHP_NNTG_CTRL_02_T                     shp_nntg_ctrl_02;	//0xCCA00F08
	PE_O26_2KY_SHP_NNTG_CTRL_03_T                     shp_nntg_ctrl_03;	//0xCCA00F0C
	PE_O26_2KY_SHP_NNTG_CTRL_04_T                     shp_nntg_ctrl_04;	//0xCCA00F10
	PE_O26_2KY_SHP_NNTG_CTRL_05_T                     shp_nntg_ctrl_05;	//0xCCA00F14
	UINT32                                                  reserved72;	//0xCCA00F18
	UINT32                                                  reserved73;	//0xCCA00F1C
	UINT32                                                  reserved74;	//0xCCA00F20
	UINT32                                                  reserved75;	//0xCCA00F24
	UINT32                                                  reserved76;	//0xCCA00F28
	PE_O26_2KY_SHP_NNTG_CTRL_06_T                     shp_nntg_ctrl_06;	//0xCCA00F2C
	PE_O26_2KY_SHP_NNTG_CTRL_07_T                     shp_nntg_ctrl_07;	//0xCCA00F30
	PE_O26_2KY_SHP_NNTG_CTRL_08_T                     shp_nntg_ctrl_08;	//0xCCA00F34
	PE_O26_2KY_SHP_NNTG_CTRL_09_T                     shp_nntg_ctrl_09;	//0xCCA00F38
	PE_O26_2KY_SHP_NNTG_CTRL_0A_T                     shp_nntg_ctrl_0a;	//0xCCA00F3C
	PE_O26_2KY_SHP_NNTG_CTRL_0B_T                     shp_nntg_ctrl_0b;	//0xCCA00F40
	PE_O26_2KY_SHP_NNTG_CTRL_0C_T                     shp_nntg_ctrl_0c;	//0xCCA00F44
	PE_O26_2KY_SHP_NNTG_CTRL_0D_T                     shp_nntg_ctrl_0d;	//0xCCA00F48
	PE_O26_2KY_SHP_NNTG_CTRL_0E_T                     shp_nntg_ctrl_0e;	//0xCCA00F4C
	PE_O26_2KY_SHP_NNTG_CTRL_0F_T                     shp_nntg_ctrl_0f;	//0xCCA00F50
	PE_O26_2KY_SHP_NNTG_CTRL_10_T                     shp_nntg_ctrl_10;	//0xCCA00F54
	UINT32                                                  reserved77;	//0xCCA00F58
	UINT32                                                  reserved78;	//0xCCA00F5C
	PE_O26_2KY_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCCA00F60
	PE_O26_2KY_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCCA00F64
	PE_O26_2KY_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCCA00F68
	PE_O26_2KY_SHP_DP_SUM_NT_CTRL_01_T           shp_dp_sum_nt_ctrl_01;	//0xCCA00F6C
	PE_O26_2KY_SHP_DP_SUM_NT_CTRL_02_T           shp_dp_sum_nt_ctrl_02;	//0xCCA00F70
	UINT32                                                  reserved79;	//0xCCA00F74
	UINT32                                                  reserved80;	//0xCCA00F78
	UINT32                                                  reserved81;	//0xCCA00F7C
	UINT32                                                  reserved82;	//0xCCA00F80
	UINT32                                                  reserved83;	//0xCCA00F84
	UINT32                                                  reserved84;	//0xCCA00F88
	UINT32                                                  reserved85;	//0xCCA00F8C
	UINT32                                                  reserved86;	//0xCCA00F90
	UINT32                                                  reserved87;	//0xCCA00F94
	UINT32                                                  reserved88;	//0xCCA00F98
	UINT32                                                  reserved89;	//0xCCA00F9C
	PE_O26_2KY_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCCA00FA0
	PE_O26_2KY_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCCA00FA4
	PE_O26_2KY_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCCA00FA8
	PE_O26_2KY_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCCA00FAC
	PE_O26_2KY_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCCA00FB0
	UINT32                                                  reserved90;	//0xCCA00FB4
	UINT32                                                  reserved91;	//0xCCA00FB8
	UINT32                                                  reserved92;	//0xCCA00FBC
	PE_O26_2KY_SHP_FD_REGION_TEXT_00_T           shp_fd_region_text_00;	//0xCCA00FC0
	PE_O26_2KY_SHP_FD_REGION_TEXT_01_T           shp_fd_region_text_01;	//0xCCA00FC4
	PE_O26_2KY_SHP_FD_REGION_TEXT_02_T           shp_fd_region_text_02;	//0xCCA00FC8
	PE_O26_2KY_SHP_FD_TMAP_TEMP_00_T               shp_fd_tmap_temp_00;	//0xCCA00FCC
	PE_O26_2KY_SHP_FD_TMAP_TEMP_01_T               shp_fd_tmap_temp_01;	//0xCCA00FD0
	PE_O26_2KY_SHP_FD_TMAP_TEMP_02_T               shp_fd_tmap_temp_02;	//0xCCA00FD4
	PE_O26_2KY_SHP_FD_TMAP_TEMP_03_T               shp_fd_tmap_temp_03;	//0xCCA00FD8
	PE_O26_2KY_SHP_FD_TMAP_TEMP_04_T               shp_fd_tmap_temp_04;	//0xCCA00FDC
	PE_O26_2KY_SHP_FD_TMAP_TEMP_05_T               shp_fd_tmap_temp_05;	//0xCCA00FE0
	PE_O26_2KY_SHP_FD_TMAP_TEMP_06_T               shp_fd_tmap_temp_06;	//0xCCA00FE4
	PE_O26_2KY_SHP_FD_TMAP_TEMP_07_T               shp_fd_tmap_temp_07;	//0xCCA00FE8
	PE_O26_2KY_SHP_FD_TMAP_TEMP_08_T               shp_fd_tmap_temp_08;	//0xCCA00FEC
	PE_O26_2KY_SHP_FD_TMAP_TEMP_09_T               shp_fd_tmap_temp_09;	//0xCCA00FF0
	PE_O26_2KY_SHP_FD_TMAP_TEMP_0A_T               shp_fd_tmap_temp_0a;	//0xCCA00FF4
	PE_O26_2KY_SHP_FD_TMAP_TEMP_0B_T               shp_fd_tmap_temp_0b;	//0xCCA00FF8
	PE_O26_2KY_SHP_FD_TMAP_TEMP_0C_T               shp_fd_tmap_temp_0c;	//0xCCA00FFC
	PE_O26_2KY_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0xCCA01000
	PE_O26_2KY_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0xCCA01004
	PE_O26_2KY_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0xCCA01008
	PE_O26_2KY_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0xCCA0100C
	PE_O26_2KY_SHP_DJ_CTRL_04_T                         shp_dj_ctrl_04;	//0xCCA01010
	PE_O26_2KY_SHP_DJ_CTRL_05_T                         shp_dj_ctrl_05;	//0xCCA01014
	PE_O26_2KY_SHP_DJ_CTRL_06_T                         shp_dj_ctrl_06;	//0xCCA01018
	PE_O26_2KY_SHP_DJ_CTRL_07_T                         shp_dj_ctrl_07;	//0xCCA0101C
	PE_O26_2KY_SHP_DJ_CTRL_08_T                         shp_dj_ctrl_08;	//0xCCA01020
	PE_O26_2KY_SHP_DJ_CTRL_09_T                         shp_dj_ctrl_09;	//0xCCA01024
	PE_O26_2KY_SHP_DJ_CTRL_0A_T                         shp_dj_ctrl_0a;	//0xCCA01028
	PE_O26_2KY_SHP_DJ_CTRL_0B_T                         shp_dj_ctrl_0b;	//0xCCA0102C
	PE_O26_2KY_SHP_DJ_CTRL_0C_T                         shp_dj_ctrl_0c;	//0xCCA01030
	PE_O26_2KY_SHP_DJ_CTRL_0D_T                         shp_dj_ctrl_0d;	//0xCCA01034
	PE_O26_2KY_SHP_DJ_CTRL_0E_T                         shp_dj_ctrl_0e;	//0xCCA01038
	PE_O26_2KY_SHP_DJ_CTRL_0F_T                         shp_dj_ctrl_0f;	//0xCCA0103C
	PE_O26_2KY_SHP_DJ_CTRL_10_T                         shp_dj_ctrl_10;	//0xCCA01040
	PE_O26_2KY_SHP_DJ_CTRL_11_T                         shp_dj_ctrl_11;	//0xCCA01044
	PE_O26_2KY_SHP_DJ_CTRL_12_T                         shp_dj_ctrl_12;	//0xCCA01048
	PE_O26_2KY_SHP_DJ_CTRL_13_T                         shp_dj_ctrl_13;	//0xCCA0104C
	PE_O26_2KY_SHP_DJ_CTRL_14_T                         shp_dj_ctrl_14;	//0xCCA01050
	PE_O26_2KY_SHP_DJ_CTRL_15_T                         shp_dj_ctrl_15;	//0xCCA01054
	PE_O26_2KY_SHP_DJ_CTRL_16_T                         shp_dj_ctrl_16;	//0xCCA01058
	PE_O26_2KY_SHP_DJ_CTRL_17_T                         shp_dj_ctrl_17;	//0xCCA0105C
	PE_O26_2KY_SHP_DJ_CTRL_18_T                         shp_dj_ctrl_18;	//0xCCA01060
	PE_O26_2KY_SHP_DJ_CTRL_19_T                         shp_dj_ctrl_19;	//0xCCA01064
	PE_O26_2KY_SHP_DJ_CTRL_1A_T                         shp_dj_ctrl_1a;	//0xCCA01068
	PE_O26_2KY_SHP_DJ_CTRL_1B_T                         shp_dj_ctrl_1b;	//0xCCA0106C
	PE_O26_2KY_SHP_DJ_CTRL_1C_T                         shp_dj_ctrl_1c;	//0xCCA01070
	PE_O26_2KY_SHP_DJ_CTRL_1D_T                         shp_dj_ctrl_1d;	//0xCCA01074
	PE_O26_2KY_SHP_DJ_CTRL_1E_T                         shp_dj_ctrl_1e;	//0xCCA01078
	PE_O26_2KY_SHP_DJ_CTRL_1F_T                         shp_dj_ctrl_1f;	//0xCCA0107C
	PE_O26_2KY_SHP_DJ_CTRL_20_T                         shp_dj_ctrl_20;	//0xCCA01080
	UINT32                                                  reserved93;	//0xCCA01084
	UINT32                                                  reserved94;	//0xCCA01088
	UINT32                                                  reserved95;	//0xCCA0108C
	PE_O26_2KY_SHP_DB_CTRL_00_T                         shp_db_ctrl_00;	//0xCCA01090
	PE_O26_2KY_SHP_DB_CTRL_01_T                         shp_db_ctrl_01;	//0xCCA01094
	UINT32                                                  reserved96;	//0xCCA01098
	UINT32                                                  reserved97;	//0xCCA0109C
	PE_O26_2KY_SHP_DJ_WIN_CTRL_00_T                 shp_dj_win_ctrl_00;	//0xCCA010A0
	PE_O26_2KY_SHP_DJ_WIN_CTRL_01_T                 shp_dj_win_ctrl_01;	//0xCCA010A4
	PE_O26_2KY_SHP_DJ_WIN_CTRL_02_T                 shp_dj_win_ctrl_02;	//0xCCA010A8
	PE_O26_2KY_SHP_DJ_WIN_CTRL_03_T                 shp_dj_win_ctrl_03;	//0xCCA010AC
	PE_O26_2KY_SHP_DJ_WIN_CTRL_04_T                 shp_dj_win_ctrl_04;	//0xCCA010B0
	UINT32                                                  reserved98;	//0xCCA010B4
	UINT32                                                  reserved99;	//0xCCA010B8
	UINT32                                                 reserved100;	//0xCCA010BC
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_00_T     shp_dj_text_gain_ctrl_00;	//0xCCA010C0
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_01_T     shp_dj_text_gain_ctrl_01;	//0xCCA010C4
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_02_T     shp_dj_text_gain_ctrl_02;	//0xCCA010C8
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_03_T     shp_dj_text_gain_ctrl_03;	//0xCCA010CC
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_04_T     shp_dj_text_gain_ctrl_04;	//0xCCA010D0
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_05_T     shp_dj_text_gain_ctrl_05;	//0xCCA010D4
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_06_T     shp_dj_text_gain_ctrl_06;	//0xCCA010D8
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_07_T     shp_dj_text_gain_ctrl_07;	//0xCCA010DC
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_08_T     shp_dj_text_gain_ctrl_08;	//0xCCA010E0
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_09_T     shp_dj_text_gain_ctrl_09;	//0xCCA010E4
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_10_T     shp_dj_text_gain_ctrl_10;	//0xCCA010E8
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_11_T     shp_dj_text_gain_ctrl_11;	//0xCCA010EC
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_12_T     shp_dj_text_gain_ctrl_12;	//0xCCA010F0
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_13_T     shp_dj_text_gain_ctrl_13;	//0xCCA010F4
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_14_T     shp_dj_text_gain_ctrl_14;	//0xCCA010F8
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_15_T     shp_dj_text_gain_ctrl_15;	//0xCCA010FC
	PE_O26_2KY_SHP_DJ_TEXT_GAIN_CTRL_16_T     shp_dj_text_gain_ctrl_16;	//0xCCA01100
	UINT32                                                 reserved101;	//0xCCA01104
	UINT32                                                 reserved102;	//0xCCA01108
	UINT32                                                 reserved103;	//0xCCA0110C
	PE_O26_2KY_SHP_FD_TEXT_CTRL_00_T               shp_fd_text_ctrl_00;	//0xCCA01110
	PE_O26_2KY_SHP_FD_TEXT_CTRL_01_T               shp_fd_text_ctrl_01;	//0xCCA01114
	PE_O26_2KY_SHP_FD_TEXT_CTRL_02_T               shp_fd_text_ctrl_02;	//0xCCA01118
	PE_O26_2KY_SHP_FD_TEXT_CTRL_03_T               shp_fd_text_ctrl_03;	//0xCCA0111C
	PE_O26_2KY_SHP_FD_TEXT_CTRL_04_T               shp_fd_text_ctrl_04;	//0xCCA01120
	PE_O26_2KY_SHP_FD_TEXT_CTRL_05_T               shp_fd_text_ctrl_05;	//0xCCA01124
	PE_O26_2KY_SHP_FD_TEXT_CTRL_06_T               shp_fd_text_ctrl_06;	//0xCCA01128
	PE_O26_2KY_SHP_FD_TEXT_CTRL_07_T               shp_fd_text_ctrl_07;	//0xCCA0112C
	PE_O26_2KY_SHP_FD_TEXT_CTRL_08_T               shp_fd_text_ctrl_08;	//0xCCA01130
	PE_O26_2KY_SHP_FD_TEXT_TEMP_00_T               shp_fd_text_temp_00;	//0xCCA01134
	PE_O26_2KY_SHP_FD_TEXT_TEMP_01_T               shp_fd_text_temp_01;	//0xCCA01138
	PE_O26_2KY_SHP_FD_TEXT_TEMP_02_T               shp_fd_text_temp_02;	//0xCCA0113C
	PE_O26_2KY_SHP_FD_TEXT_TEMP_03_T               shp_fd_text_temp_03;	//0xCCA01140
	PE_O26_2KY_SHP_FD_TEXT_TEMP_04_T               shp_fd_text_temp_04;	//0xCCA01144
	PE_O26_2KY_SHP_FD_TEXT_TEMP_05_T               shp_fd_text_temp_05;	//0xCCA01148
	PE_O26_2KY_SHP_FD_TEXT_TEMP_06_T               shp_fd_text_temp_06;	//0xCCA0114C
	PE_O26_2KY_SHP_FD_TEXT_TEMP_07_T               shp_fd_text_temp_07;	//0xCCA01150
	PE_O26_2KY_SHP_FD_TEXT_TEMP_08_T               shp_fd_text_temp_08;	//0xCCA01154
	PE_O26_2KY_SHP_FD_TEXT_TEMP_09_T               shp_fd_text_temp_09;	//0xCCA01158
	PE_O26_2KY_SHP_FD_TEXT_TEMP_0A_T               shp_fd_text_temp_0a;	//0xCCA0115C
	PE_O26_2KY_SHP_FD_TEXT_TEMP_0B_T               shp_fd_text_temp_0b;	//0xCCA01160
	PE_O26_2KY_SHP_FD_TEXT_TEMP_0C_T               shp_fd_text_temp_0c;	//0xCCA01164
	UINT32                                                 reserved104;	//0xCCA01168
	UINT32                                                 reserved105;	//0xCCA0116C
	PE_O26_2KY_SHP_CORE_TEXT_STAT_00_T           shp_core_text_stat_00;	//0xCCA01170
	PE_O26_2KY_SHP_CORE_TEXT_STAT_01_T           shp_core_text_stat_01;	//0xCCA01174
	PE_O26_2KY_SHP_CORE_TEXT_STAT_02_T           shp_core_text_stat_02;	//0xCCA01178
	PE_O26_2KY_SHP_CORE_TEXT_STAT_03_T           shp_core_text_stat_03;	//0xCCA0117C
	PE_O26_2KY_SHP_CORE_TEXT_STAT_04_T           shp_core_text_stat_04;	//0xCCA01180
	PE_O26_2KY_SHP_CORE_TEXT_STAT_05_T           shp_core_text_stat_05;	//0xCCA01184
	PE_O26_2KY_SHP_CORE_TEXT_STAT_06_T           shp_core_text_stat_06;	//0xCCA01188
	PE_O26_2KY_SHP_CORE_TEXT_STAT_07_T           shp_core_text_stat_07;	//0xCCA0118C
	PE_O26_2KY_SHP_TEXT_BLEND_00_T                   shp_text_blend_00;	//0xCCA01190
	PE_O26_2KY_SHP_TEXT_BLEND_01_T                   shp_text_blend_01;	//0xCCA01194
	PE_O26_2KY_SHP_TEXT_BLEND_02_T                   shp_text_blend_02;	//0xCCA01198
	PE_O26_2KY_SHP_TEXT_BLEND_03_T                   shp_text_blend_03;	//0xCCA0119C
	PE_O26_2KY_SHP_TEXT_BLEND_04_T                   shp_text_blend_04;	//0xCCA011A0
	PE_O26_2KY_SHP_TEXT_BLEND_05_T                   shp_text_blend_05;	//0xCCA011A4
	PE_O26_2KY_SHP_TEXT_BLEND_06_T                   shp_text_blend_06;	//0xCCA011A8
	PE_O26_2KY_SHP_TEXT_BLEND_07_T                   shp_text_blend_07;	//0xCCA011AC
	PE_O26_2KY_SHP_TEXT_BLEND_08_T                   shp_text_blend_08;	//0xCCA011B0
	PE_O26_2KY_SHP_TEXT_BLEND_09_T                   shp_text_blend_09;	//0xCCA011B4
	PE_O26_2KY_SHP_TEXT_BLEND_0A_T                   shp_text_blend_0a;	//0xCCA011B8
	PE_O26_2KY_SHP_TEXT_BLEND_0B_T                   shp_text_blend_0b;	//0xCCA011BC
	PE_O26_2KY_SHP_TEXT_BLEND_0C_T                   shp_text_blend_0c;	//0xCCA011C0
	UINT32                                                 reserved106;	//0xCCA011C4
	UINT32                                                 reserved107;	//0xCCA011C8
	UINT32                                                 reserved108;	//0xCCA011CC
	PE_O26_2KY_SHP_TEMPORAL_MAP_00_T               shp_temporal_map_00;	//0xCCA011D0
	PE_O26_2KY_SHP_TEMPORAL_MAP_01_T               shp_temporal_map_01;	//0xCCA011D4
	UINT32                                                 reserved109;	//0xCCA011D8
	UINT32                                                 reserved110;	//0xCCA011DC
	UINT32                                                 reserved111;	//0xCCA011E0
	UINT32                                                 reserved112;	//0xCCA011E4
	UINT32                                                 reserved113;	//0xCCA011E8
	UINT32                                                 reserved114;	//0xCCA011EC
	UINT32                                                 reserved115;	//0xCCA011F0
	UINT32                                                 reserved116;	//0xCCA011F4
	UINT32                                                 reserved117;	//0xCCA011F8
	UINT32                                                 reserved118;	//0xCCA011FC
	PE_O26_2KY_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCCA01200
	PE_O26_2KY_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCCA01204
	PE_O26_2KY_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCCA01208
	PE_O26_2KY_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCCA0120C
	PE_O26_2KY_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCCA01210
	PE_O26_2KY_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCCA01214
	PE_O26_2KY_SHP_CORE_RDY_VLD_MASK_T           shp_core_rdy_vld_mask;	//0xCCA01218
	UINT32                                                 reserved119;	//0xCCA0121C
	UINT32                                                 reserved120;	//0xCCA01220
	UINT32                                                 reserved121;	//0xCCA01224
	UINT32                                                 reserved122;	//0xCCA01228
	UINT32                                                 reserved123;	//0xCCA0122C
	UINT32                                                 reserved124;	//0xCCA01230
	UINT32                                                 reserved125;	//0xCCA01234
	UINT32                                                 reserved126;	//0xCCA01238
	UINT32                                                 reserved127;	//0xCCA0123C
	UINT32                                                 reserved128;	//0xCCA01240
	UINT32                                                 reserved129;	//0xCCA01244
	UINT32                                                 reserved130;	//0xCCA01248
	UINT32                                                 reserved131;	//0xCCA0124C
	UINT32                                                 reserved132;	//0xCCA01250
	UINT32                                                 reserved133;	//0xCCA01254
	UINT32                                                 reserved134;	//0xCCA01258
	UINT32                                                 reserved135;	//0xCCA0125C
	PE_O26_2KY_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCCA01260
	PE_O26_2KY_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCCA01264
	PE_O26_2KY_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCCA01268
	PE_O26_2KY_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCCA0126C
	UINT32                                                 reserved136;	//0xCCA01270
	UINT32                                                 reserved137;	//0xCCA01274
	UINT32                                                 reserved138;	//0xCCA01278
	UINT32                                                 reserved139;	//0xCCA0127C
	UINT32                                                 reserved140;	//0xCCA01280
	UINT32                                                 reserved141;	//0xCCA01284
	UINT32                                                 reserved142;	//0xCCA01288
	UINT32                                                 reserved143;	//0xCCA0128C
	UINT32                                                 reserved144;	//0xCCA01290
	UINT32                                                 reserved145;	//0xCCA01294
	UINT32                                                 reserved146;	//0xCCA01298
	UINT32                                                 reserved147;	//0xCCA0129C
	UINT32                                                 reserved148;	//0xCCA012A0
	UINT32                                                 reserved149;	//0xCCA012A4
	UINT32                                                 reserved150;	//0xCCA012A8
	UINT32                                                 reserved151;	//0xCCA012AC
	UINT32                                                 reserved152;	//0xCCA012B0
	UINT32                                                 reserved153;	//0xCCA012B4
	UINT32                                                 reserved154;	//0xCCA012B8
	UINT32                                                 reserved155;	//0xCCA012BC
	UINT32                                                 reserved156;	//0xCCA012C0
	UINT32                                                 reserved157;	//0xCCA012C4
	UINT32                                                 reserved158;	//0xCCA012C8
	UINT32                                                 reserved159;	//0xCCA012CC
	UINT32                                                 reserved160;	//0xCCA012D0
	UINT32                                                 reserved161;	//0xCCA012D4
	UINT32                                                 reserved162;	//0xCCA012D8
	UINT32                                                 reserved163;	//0xCCA012DC
	UINT32                                                 reserved164;	//0xCCA012E0
	UINT32                                                 reserved165;	//0xCCA012E4
	UINT32                                                 reserved166;	//0xCCA012E8
	UINT32                                                 reserved167;	//0xCCA012EC
	UINT32                                                 reserved168;	//0xCCA012F0
	UINT32                                                 reserved169;	//0xCCA012F4
	UINT32                                                 reserved170;	//0xCCA012F8
	UINT32                                                 reserved171;	//0xCCA012FC
	PE_O26_2KY_SHP_CORE_TMAP_STAT_00_T           shp_core_tmap_stat_00;	//0xCCA01300
	PE_O26_2KY_SHP_CORE_TMAP_STAT_01_T           shp_core_tmap_stat_01;	//0xCCA01304
	PE_O26_2KY_SHP_CORE_TMAP_STAT_02_T           shp_core_tmap_stat_02;	//0xCCA01308
	PE_O26_2KY_SHP_CORE_TMAP_STAT_03_T           shp_core_tmap_stat_03;	//0xCCA0130C
	PE_O26_2KY_SHP_CORE_TMAP_STAT_04_T           shp_core_tmap_stat_04;	//0xCCA01310
	PE_O26_2KY_SHP_CORE_TMAP_STAT_05_T           shp_core_tmap_stat_05;	//0xCCA01314
	PE_O26_2KY_SHP_CORE_TMAP_STAT_06_T           shp_core_tmap_stat_06;	//0xCCA01318
	PE_O26_2KY_SHP_CORE_TMAP_STAT_07_T           shp_core_tmap_stat_07;	//0xCCA0131C
	PE_O26_2KY_SHP_ELLIPSE_CTRL_00_T               shp_ellipse_ctrl_00;	//0xCCA01320
	PE_O26_2KY_SHP_ELLIPSE_CTRL_01_T               shp_ellipse_ctrl_01;	//0xCCA01324
	PE_O26_2KY_SHP_ELLIPSE_CTRL_02_T               shp_ellipse_ctrl_02;	//0xCCA01328
	PE_O26_2KY_SHP_ELLIPSE_CTRL_03_T               shp_ellipse_ctrl_03;	//0xCCA0132C
	PE_O26_2KY_SHP_ELLIPSE_CTRL_04_T               shp_ellipse_ctrl_04;	//0xCCA01330
	PE_O26_2KY_SHP_ELLIPSE_CTRL_05_T               shp_ellipse_ctrl_05;	//0xCCA01334
	PE_O26_2KY_SHP_ELLIPSE_CTRL_06_T               shp_ellipse_ctrl_06;	//0xCCA01338
	PE_O26_2KY_SHP_ELLIPSE_CTRL_07_T               shp_ellipse_ctrl_07;	//0xCCA0133C
	PE_O26_2KY_SHP_ELLIPSE_CTRL_08_T               shp_ellipse_ctrl_08;	//0xCCA01340
	PE_O26_2KY_SHP_ELLIPSE_CTRL_09_T               shp_ellipse_ctrl_09;	//0xCCA01344
	PE_O26_2KY_SHP_ELLIPSE_CTRL_10_T               shp_ellipse_ctrl_10;	//0xCCA01348
	PE_O26_2KY_SHP_ELLIPSE_CTRL_11_T               shp_ellipse_ctrl_11;	//0xCCA0134C
	PE_O26_2KY_SHP_ELLIPSE_CTRL_12_T               shp_ellipse_ctrl_12;	//0xCCA01350
	PE_O26_2KY_SHP_ELLIPSE_LUT_CTRL_00_T       shp_ellipse_lut_ctrl_00;	//0xCCA01354
	PE_O26_2KY_SHP_ELLIPSE_LUT_CTRL_01_T       shp_ellipse_lut_ctrl_01;	//0xCCA01358
	UINT32                                                 reserved172;	//0xCCA0135C
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_00_T         shp_luma_blend_ctrl_00;	//0xCCA01360
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_01_T         shp_luma_blend_ctrl_01;	//0xCCA01364
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_02_T         shp_luma_blend_ctrl_02;	//0xCCA01368
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_03_T         shp_luma_blend_ctrl_03;	//0xCCA0136C
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_04_T         shp_luma_blend_ctrl_04;	//0xCCA01370
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_05_T         shp_luma_blend_ctrl_05;	//0xCCA01374
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_06_T         shp_luma_blend_ctrl_06;	//0xCCA01378
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_07_T         shp_luma_blend_ctrl_07;	//0xCCA0137C
	PE_O26_2KY_SHP_LUMA_BLEND_CTRL_08_T         shp_luma_blend_ctrl_08;	//0xCCA01380
	PE_O26_2KY_SHP_SM_BLEND_CTRL_00_T             shp_sm_blend_ctrl_00;	//0xCCA01384
	PE_O26_2KY_SHP_SM_BLEND_CTRL_01_T             shp_sm_blend_ctrl_01;	//0xCCA01388
	PE_O26_2KY_SHP_SM_BLEND_CTRL_02_T             shp_sm_blend_ctrl_02;	//0xCCA0138C
	UINT32                                                 reserved173;	//0xCCA01390
	UINT32                                                 reserved174;	//0xCCA01394
	UINT32                                                 reserved175;	//0xCCA01398
	UINT32                                                 reserved176;	//0xCCA0139C
	UINT32                                                 reserved177;	//0xCCA013A0
	UINT32                                                 reserved178;	//0xCCA013A4
	UINT32                                                 reserved179;	//0xCCA013A8
	UINT32                                                 reserved180;	//0xCCA013AC
	UINT32                                                 reserved181;	//0xCCA013B0
	UINT32                                                 reserved182;	//0xCCA013B4
	UINT32                                                 reserved183;	//0xCCA013B8
	UINT32                                                 reserved184;	//0xCCA013BC
	UINT32                                                 reserved185;	//0xCCA013C0
	UINT32                                                 reserved186;	//0xCCA013C4
	UINT32                                                 reserved187;	//0xCCA013C8
	UINT32                                                 reserved188;	//0xCCA013CC
	UINT32                                                 reserved189;	//0xCCA013D0
	UINT32                                                 reserved190;	//0xCCA013D4
	UINT32                                                 reserved191;	//0xCCA013D8
	UINT32                                                 reserved192;	//0xCCA013DC
	UINT32                                                 reserved193;	//0xCCA013E0
	UINT32                                                 reserved194;	//0xCCA013E4
	UINT32                                                 reserved195;	//0xCCA013E8
	UINT32                                                 reserved196;	//0xCCA013EC
	PE_O26_2KY_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCCA013F0
	PE_O26_2KY_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCCA013F4
	PE_O26_2KY_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCCA013F8
	PE_O26_2KY_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCCA013FC
}PE_SR_2K_SHP_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02D00 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O26_2K_SUB_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02D04 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //Processing width  (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //Processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02D08 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O26_2K_SUB_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02D0C RW 0x000A_0000
	UINT32 resvd0                           :16;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,10) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02D40 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //Pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //Pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //Pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O26_2K_SUB_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02DF0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //Debug display	0 : normal display (output 1)	1 : normal display (output 2)	2 : tgen only	3 : Luma Adabtive	4 : weight(A)	5 : weight(Texture)	6 : A-map	7 : T-map	8 : soft edge gain map	9 : A-map for der	10: Motion map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //DP detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //DP buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O26_2K_SUB_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E00 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //Post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //Pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //Pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //Pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E08 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //Get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //Get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E0C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E10 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E14 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E18 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E1C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E20 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E24 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E28 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E2C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //Edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //Texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E30 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E34 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E38 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E3C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E40 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E44 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E48 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E4C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E50 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E54 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //Input selection for flat region LUT	0: a_map	1: t_map	2: max(a_map,t_map)	3: min(255,a_map+t_map) (default)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //Add a flat gain to A-map enable
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //Add a flat gain to T-map enable
	UINT32 resvd2                           :23;
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E58 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O26_2K_SUB_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E60 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E64 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E68 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E6C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E70 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E74 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E78 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //Gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E7C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E80 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //Level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //Level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E84 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //Level-balancing, lum2_y0
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E88 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //Level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E8C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02E90 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2K_SUB_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EC0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EC4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //Bilateral filter tap size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //Edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //Edge filter en
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EC8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //Edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //Edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02ECC RW 0x0006_5008
	UINT32 reg_derv_en                      :1;	//(0:0,NA,0) //DER-V enable
	UINT32 resvd0                           :2;
	UINT32 reg_derv_bif_en                  :1;	//(3:3,NA,1) //Bilateral filter	0: disable	1: enable
	UINT32 reg_derv_output_mux              :4;	//(7:4,NA,0) //Display mode	0xxx: normal display	1000: vertical ringing measure	1001: gain adjusted by curve mapping	101x: bilateral filter output	o.w : not used
	UINT32 reg_derv_bif_manual_th           :8;	//(15:8,NA,80) //Bilateral filter threshold
	UINT32 reg_derv_th_gain                 :6;	//(21:16,NA,6) //Auto threshold gain, th = th_gain * A
	UINT32 resvd1                           :2;
	UINT32 reg_derv_th_mode                 :1;	//(24:24,NA,0) //Threshold mode	0: auto(A-map)	1: manual
	UINT32 resvd2                           :7;
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02ED0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //Center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //Center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02ED4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //Gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //Gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02ED8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EDC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O26_2K_SUB_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EE0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EE4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EE8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EEC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EF0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EF4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EF8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //Gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02EFC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F00 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //Level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //Level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F04 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //Level-balancing, lum2_y0
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F08 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //Level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F0C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F10 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2K_SUB_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F20 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //Min-max tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //Average tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_2K_SUB_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F24 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //Min-max tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //Average tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_2K_SUB_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F28 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2K_SUB_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F2C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2K_SUB_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F30 RW 0x1010_2014
	UINT32 reg_sti_enable                   :1;	//(0:0,NA,0) //STI enable
	UINT32 reg_sti_debug_map_en             :1;	//(1:1,NA,0) //Debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//(3:2,NA,1) //Min-max tap size
	UINT32 reg_sti_avg_tap_size             :2;	//(5:4,NA,1) //Average tap size
	UINT32 reg_sti_ti_mode                  :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//(15:8,NA,32) //Master gain
	UINT32 reg_sti_texture_gain             :8;	//(23:16,NA,16) //Texture gain
	UINT32 reg_sti_edge_gain                :8;	//(31:24,NA,16) //Edge gain
	};
}PE_O26_2K_SUB_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F40 RW 0x8000_0011
	UINT32 reg_tgen_on_off                  :1;	//(0:0,NA,1) //TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//(4:4,NA,1) //Manual seed mode for rand val
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//(8:8,NA,0) //Debug mode enable
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//(19:16,NA,0) //Mode for rand val
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//(31:24,NA,128) //Master gain
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F44 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //R clipping bound for delta
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //L clipping bound for delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //Max threshold for delta
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //Scale factor for delta
	UINT32 resvd3                           :5;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F48 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //Rand val threshold
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //Weight for curr for delta
	UINT32 resvd                            :20;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F4C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //Initial seed value for manual seed mode
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F54 RW 0x0202_1F04
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //Min-max offset
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //Min-max selection mode
	UINT32 resvd2                           :6;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F58 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //Rand scale factor for noise delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //Min-max scale factor for noise delta
	UINT32 resvd2                           :3;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F5C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //Noise blur coefficient, x2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //Noise blur coefficient, x1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //Noise blur coefficient, x0
	UINT32 resvd2                           :2;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F60 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //Noise blur coefficient, y2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //Noise blur coefficient, y1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //Noise blur coefficient, y0
	UINT32 resvd2                           :2;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F64 RW 0x3F80_1F1F
	UINT32 resvd0                           :24;
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //Noise gain
	UINT32 resvd1                           :2;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F68 RW 0x48AB_CDFF
	UINT32 tdata0                           :32;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F6C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02F70 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_2K_SUB_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03060 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //DP sum LUT mode	0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O26_2K_SUB_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03064 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //DP sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //DP sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //DP sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //DP sum LUT for delta control, x1
	};
}PE_O26_2K_SUB_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03068 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //DP sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //DP sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //DP sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //DP sum LUT for delta control, x3
	};
}PE_O26_2K_SUB_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA030A0 RW 0x0000_0000
	UINT32 reg_win_dp_win0_en               :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_dp_win1_en               :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_dp_win01_en              :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dp_win_outside           :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_dp_win_en                :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_dp_bdr_alpha             :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_dp_bdr_wid               :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_dp_bdr_en                :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_dp_cr5                   :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_dp_cb5                   :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_dp_yy6                   :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_2K_SUB_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA030A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //Window control, win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //Window control, win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA030A8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //Window control, win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //Window control, win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA030AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //Window control, win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //Window control, win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA030B0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //Window control, win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //Window control, win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03300 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03304 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03308 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0330C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter 4K Last = 2160
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter 4K Last = 2160
	UINT32 resvd1                           :4;
	};
}PE_O26_2K_SUB_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03310 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_2K_SUB_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03314 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_2K_SUB_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03360 RO 0x0000_0000
	UINT32 reg_status_a_avg                 :32;	//(31:0,NA,0) //FD status register (a_avg)
	};
}PE_O26_2K_SUB_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03364 RO 0x0000_0000
	UINT32 reg_status_t_avg                 :32;	//(31:0,NA,0) //FD status register (t_avg)
	};
}PE_O26_2K_SUB_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA03368 RO 0x0000_0000
	UINT32 reg_status_e_avg                 :32;	//(31:0,NA,0) //FD status register (e_avg)
	};
}PE_O26_2K_SUB_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0336C RO 0x0000_0000
	UINT32 reg_status_d_avg                 :32;	//(31:0,NA,0) //FD status register (d_avg)
	};
}PE_O26_2K_SUB_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA034F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2K_SUB_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA034F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2K_SUB_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA034F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2K_SUB_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA034FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2K_SUB_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O26_2K_SUB_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCCA02D00
	PE_O26_2K_SUB_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCCA02D04
	PE_O26_2K_SUB_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCCA02D08
	PE_O26_2K_SUB_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCCA02D0C
	UINT32                                                   reserved0;	//0xCCA02D10
	UINT32                                                   reserved1;	//0xCCA02D14
	UINT32                                                   reserved2;	//0xCCA02D18
	UINT32                                                   reserved3;	//0xCCA02D1C
	UINT32                                                   reserved4;	//0xCCA02D20
	UINT32                                                   reserved5;	//0xCCA02D24
	UINT32                                                   reserved6;	//0xCCA02D28
	UINT32                                                   reserved7;	//0xCCA02D2C
	UINT32                                                   reserved8;	//0xCCA02D30
	UINT32                                                   reserved9;	//0xCCA02D34
	UINT32                                                  reserved10;	//0xCCA02D38
	UINT32                                                  reserved11;	//0xCCA02D3C
	PE_O26_2K_SUB_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCCA02D40
	UINT32                                                  reserved12;	//0xCCA02D44
	UINT32                                                  reserved13;	//0xCCA02D48
	UINT32                                                  reserved14;	//0xCCA02D4C
	UINT32                                                  reserved15;	//0xCCA02D50
	UINT32                                                  reserved16;	//0xCCA02D54
	UINT32                                                  reserved17;	//0xCCA02D58
	UINT32                                                  reserved18;	//0xCCA02D5C
	UINT32                                                  reserved19;	//0xCCA02D60
	UINT32                                                  reserved20;	//0xCCA02D64
	UINT32                                                  reserved21;	//0xCCA02D68
	UINT32                                                  reserved22;	//0xCCA02D6C
	UINT32                                                  reserved23;	//0xCCA02D70
	UINT32                                                  reserved24;	//0xCCA02D74
	UINT32                                                  reserved25;	//0xCCA02D78
	UINT32                                                  reserved26;	//0xCCA02D7C
	UINT32                                                  reserved27;	//0xCCA02D80
	UINT32                                                  reserved28;	//0xCCA02D84
	UINT32                                                  reserved29;	//0xCCA02D88
	UINT32                                                  reserved30;	//0xCCA02D8C
	UINT32                                                  reserved31;	//0xCCA02D90
	UINT32                                                  reserved32;	//0xCCA02D94
	UINT32                                                  reserved33;	//0xCCA02D98
	UINT32                                                  reserved34;	//0xCCA02D9C
	UINT32                                                  reserved35;	//0xCCA02DA0
	UINT32                                                  reserved36;	//0xCCA02DA4
	UINT32                                                  reserved37;	//0xCCA02DA8
	UINT32                                                  reserved38;	//0xCCA02DAC
	UINT32                                                  reserved39;	//0xCCA02DB0
	UINT32                                                  reserved40;	//0xCCA02DB4
	UINT32                                                  reserved41;	//0xCCA02DB8
	UINT32                                                  reserved42;	//0xCCA02DBC
	UINT32                                                  reserved43;	//0xCCA02DC0
	UINT32                                                  reserved44;	//0xCCA02DC4
	UINT32                                                  reserved45;	//0xCCA02DC8
	UINT32                                                  reserved46;	//0xCCA02DCC
	UINT32                                                  reserved47;	//0xCCA02DD0
	UINT32                                                  reserved48;	//0xCCA02DD4
	UINT32                                                  reserved49;	//0xCCA02DD8
	UINT32                                                  reserved50;	//0xCCA02DDC
	UINT32                                                  reserved51;	//0xCCA02DE0
	UINT32                                                  reserved52;	//0xCCA02DE4
	UINT32                                                  reserved53;	//0xCCA02DE8
	UINT32                                                  reserved54;	//0xCCA02DEC
	PE_O26_2K_SUB_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCCA02DF0
	UINT32                                                  reserved55;	//0xCCA02DF4
	UINT32                                                  reserved56;	//0xCCA02DF8
	UINT32                                                  reserved57;	//0xCCA02DFC
	PE_O26_2K_SUB_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCCA02E00
	PE_O26_2K_SUB_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCCA02E04
	PE_O26_2K_SUB_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCCA02E08
	PE_O26_2K_SUB_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCCA02E0C
	PE_O26_2K_SUB_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCCA02E10
	PE_O26_2K_SUB_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCCA02E14
	PE_O26_2K_SUB_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCCA02E18
	PE_O26_2K_SUB_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCCA02E1C
	PE_O26_2K_SUB_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCCA02E20
	PE_O26_2K_SUB_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCCA02E24
	PE_O26_2K_SUB_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCCA02E28
	PE_O26_2K_SUB_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCCA02E2C
	PE_O26_2K_SUB_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCCA02E30
	PE_O26_2K_SUB_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCCA02E34
	PE_O26_2K_SUB_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCCA02E38
	PE_O26_2K_SUB_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCCA02E3C
	PE_O26_2K_SUB_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCCA02E40
	PE_O26_2K_SUB_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCCA02E44
	PE_O26_2K_SUB_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCCA02E48
	PE_O26_2K_SUB_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCCA02E4C
	PE_O26_2K_SUB_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCCA02E50
	PE_O26_2K_SUB_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCCA02E54
	PE_O26_2K_SUB_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCCA02E58
	UINT32                                                 reserved58;	//0xCCA02E5C
	PE_O26_2K_SUB_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCCA02E60
	PE_O26_2K_SUB_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCCA02E64
	PE_O26_2K_SUB_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCCA02E68
	PE_O26_2K_SUB_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCCA02E6C
	PE_O26_2K_SUB_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCCA02E70
	PE_O26_2K_SUB_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCCA02E74
	PE_O26_2K_SUB_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCCA02E78
	PE_O26_2K_SUB_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCCA02E7C
	PE_O26_2K_SUB_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCCA02E80
	PE_O26_2K_SUB_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCCA02E84
	PE_O26_2K_SUB_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCCA02E88
	PE_O26_2K_SUB_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCCA02E8C
	PE_O26_2K_SUB_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCCA02E90
	UINT32                                                 reserved59;	//0xCCA02E94
	UINT32                                                 reserved60;	//0xCCA02E98
	UINT32                                                 reserved61;	//0xCCA02E9C
	UINT32                                                 reserved62;	//0xCCA02EA0
	UINT32                                                 reserved63;	//0xCCA02EA4
	UINT32                                                 reserved64;	//0xCCA02EA8
	UINT32                                                 reserved65;	//0xCCA02EAC
	UINT32                                                 reserved66;	//0xCCA02EB0
	UINT32                                                 reserved67;	//0xCCA02EB4
	UINT32                                                 reserved68;	//0xCCA02EB8
	UINT32                                                 reserved69;	//0xCCA02EBC
	PE_O26_2K_SUB_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCCA02EC0
	PE_O26_2K_SUB_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCCA02EC4
	PE_O26_2K_SUB_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCCA02EC8
	PE_O26_2K_SUB_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCCA02ECC
	PE_O26_2K_SUB_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCCA02ED0
	PE_O26_2K_SUB_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCCA02ED4
	PE_O26_2K_SUB_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCCA02ED8
	PE_O26_2K_SUB_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCCA02EDC
	PE_O26_2K_SUB_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCCA02EE0
	PE_O26_2K_SUB_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCCA02EE4
	PE_O26_2K_SUB_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCCA02EE8
	PE_O26_2K_SUB_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCCA02EEC
	PE_O26_2K_SUB_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCCA02EF0
	PE_O26_2K_SUB_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCCA02EF4
	PE_O26_2K_SUB_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCCA02EF8
	PE_O26_2K_SUB_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCCA02EFC
	PE_O26_2K_SUB_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCCA02F00
	PE_O26_2K_SUB_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCCA02F04
	PE_O26_2K_SUB_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCCA02F08
	PE_O26_2K_SUB_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCCA02F0C
	PE_O26_2K_SUB_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCCA02F10
	UINT32                                                  reserved70;	//0xCCA02F14
	UINT32                                                  reserved71;	//0xCCA02F18
	UINT32                                                  reserved72;	//0xCCA02F1C
	PE_O26_2K_SUB_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCCA02F20
	PE_O26_2K_SUB_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCCA02F24
	PE_O26_2K_SUB_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCCA02F28
	PE_O26_2K_SUB_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCCA02F2C
	PE_O26_2K_SUB_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCCA02F30
	UINT32                                                  reserved73;	//0xCCA02F34
	UINT32                                                  reserved74;	//0xCCA02F38
	UINT32                                                  reserved75;	//0xCCA02F3C
	PE_O26_2K_SUB_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCCA02F40
	PE_O26_2K_SUB_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCCA02F44
	PE_O26_2K_SUB_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCCA02F48
	PE_O26_2K_SUB_SHP_TGEN_CTRL_03_T                     shp_tgen_ctrl_03;	//0xCCA02F4C
	UINT32                                                  reserved76;	//0xCCA02F50
	PE_O26_2K_SUB_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCCA02F54
	PE_O26_2K_SUB_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCCA02F58
	PE_O26_2K_SUB_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCCA02F5C
	PE_O26_2K_SUB_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCCA02F60
	PE_O26_2K_SUB_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCCA02F64
	PE_O26_2K_SUB_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCCA02F68
	PE_O26_2K_SUB_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCCA02F6C
	PE_O26_2K_SUB_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCCA02F70
	UINT32                                                  reserved77;	//0xCCA02F74
	UINT32                                                  reserved78;	//0xCCA02F78
	UINT32                                                  reserved79;	//0xCCA02F7C
	UINT32                                                  reserved80;	//0xCCA02F80
	UINT32                                                  reserved81;	//0xCCA02F84
	UINT32                                                  reserved82;	//0xCCA02F88
	UINT32                                                  reserved83;	//0xCCA02F8C
	UINT32                                                  reserved84;	//0xCCA02F90
	UINT32                                                  reserved85;	//0xCCA02F94
	UINT32                                                  reserved86;	//0xCCA02F98
	UINT32                                                  reserved87;	//0xCCA02F9C
	UINT32                                                  reserved88;	//0xCCA02FA0
	UINT32                                                  reserved89;	//0xCCA02FA4
	UINT32                                                  reserved90;	//0xCCA02FA8
	UINT32                                                  reserved91;	//0xCCA02FAC
	UINT32                                                  reserved92;	//0xCCA02FB0
	UINT32                                                  reserved93;	//0xCCA02FB4
	UINT32                                                  reserved94;	//0xCCA02FB8
	UINT32                                                  reserved95;	//0xCCA02FBC
	UINT32                                                  reserved96;	//0xCCA02FC0
	UINT32                                                  reserved97;	//0xCCA02FC4
	UINT32                                                  reserved98;	//0xCCA02FC8
	UINT32                                                  reserved99;	//0xCCA02FCC
	UINT32                                                 reserved100;	//0xCCA02FD0
	UINT32                                                 reserved101;	//0xCCA02FD4
	UINT32                                                 reserved102;	//0xCCA02FD8
	UINT32                                                 reserved103;	//0xCCA02FDC
	UINT32                                                 reserved104;	//0xCCA02FE0
	UINT32                                                 reserved105;	//0xCCA02FE4
	UINT32                                                 reserved106;	//0xCCA02FE8
	UINT32                                                 reserved107;	//0xCCA02FEC
	UINT32                                                 reserved108;	//0xCCA02FF0
	UINT32                                                 reserved109;	//0xCCA02FF4
	UINT32                                                 reserved110;	//0xCCA02FF8
	UINT32                                                 reserved111;	//0xCCA02FFC
	UINT32                                                 reserved112;	//0xCCA03000
	UINT32                                                 reserved113;	//0xCCA03004
	UINT32                                                 reserved114;	//0xCCA03008
	UINT32                                                 reserved115;	//0xCCA0300C
	UINT32                                                 reserved116;	//0xCCA03010
	UINT32                                                 reserved117;	//0xCCA03014
	UINT32                                                 reserved118;	//0xCCA03018
	UINT32                                                 reserved119;	//0xCCA0301C
	UINT32                                                 reserved120;	//0xCCA03020
	UINT32                                                 reserved121;	//0xCCA03024
	UINT32                                                 reserved122;	//0xCCA03028
	UINT32                                                 reserved123;	//0xCCA0302C
	UINT32                                                 reserved124;	//0xCCA03030
	UINT32                                                 reserved125;	//0xCCA03034
	UINT32                                                 reserved126;	//0xCCA03038
	UINT32                                                 reserved127;	//0xCCA0303C
	UINT32                                                 reserved128;	//0xCCA03040
	UINT32                                                 reserved129;	//0xCCA03044
	UINT32                                                 reserved130;	//0xCCA03048
	UINT32                                                 reserved131;	//0xCCA0304C
	UINT32                                                 reserved132;	//0xCCA03050
	UINT32                                                 reserved133;	//0xCCA03054
	UINT32                                                 reserved134;	//0xCCA03058
	UINT32                                                 reserved135;	//0xCCA0305C
	PE_O26_2K_SUB_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCCA03060
	PE_O26_2K_SUB_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCCA03064
	PE_O26_2K_SUB_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCCA03068
	UINT32                                                 reserved136;	//0xCCA0306C
	UINT32                                                 reserved137;	//0xCCA03070
	UINT32                                                 reserved138;	//0xCCA03074
	UINT32                                                 reserved139;	//0xCCA03078
	UINT32                                                 reserved140;	//0xCCA0307C
	UINT32                                                 reserved141;	//0xCCA03080
	UINT32                                                 reserved142;	//0xCCA03084
	UINT32                                                 reserved143;	//0xCCA03088
	UINT32                                                 reserved144;	//0xCCA0308C
	UINT32                                                 reserved145;	//0xCCA03090
	UINT32                                                 reserved146;	//0xCCA03094
	UINT32                                                 reserved147;	//0xCCA03098
	UINT32                                                 reserved148;	//0xCCA0309C
	PE_O26_2K_SUB_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCCA030A0
	PE_O26_2K_SUB_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCCA030A4
	PE_O26_2K_SUB_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCCA030A8
	PE_O26_2K_SUB_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCCA030AC
	PE_O26_2K_SUB_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCCA030B0
	UINT32                                                 reserved149;	//0xCCA030B4
	UINT32                                                 reserved150;	//0xCCA030B8
	UINT32                                                 reserved151;	//0xCCA030BC
	UINT32                                                 reserved152;	//0xCCA030C0
	UINT32                                                 reserved153;	//0xCCA030C4
	UINT32                                                 reserved154;	//0xCCA030C8
	UINT32                                                 reserved155;	//0xCCA030CC
	UINT32                                                 reserved156;	//0xCCA030D0
	UINT32                                                 reserved157;	//0xCCA030D4
	UINT32                                                 reserved158;	//0xCCA030D8
	UINT32                                                 reserved159;	//0xCCA030DC
	UINT32                                                 reserved160;	//0xCCA030E0
	UINT32                                                 reserved161;	//0xCCA030E4
	UINT32                                                 reserved162;	//0xCCA030E8
	UINT32                                                 reserved163;	//0xCCA030EC
	UINT32                                                 reserved164;	//0xCCA030F0
	UINT32                                                 reserved165;	//0xCCA030F4
	UINT32                                                 reserved166;	//0xCCA030F8
	UINT32                                                 reserved167;	//0xCCA030FC
	UINT32                                                 reserved168;	//0xCCA03100
	UINT32                                                 reserved169;	//0xCCA03104
	UINT32                                                 reserved170;	//0xCCA03108
	UINT32                                                 reserved171;	//0xCCA0310C
	UINT32                                                 reserved172;	//0xCCA03110
	UINT32                                                 reserved173;	//0xCCA03114
	UINT32                                                 reserved174;	//0xCCA03118
	UINT32                                                 reserved175;	//0xCCA0311C
	UINT32                                                 reserved176;	//0xCCA03120
	UINT32                                                 reserved177;	//0xCCA03124
	UINT32                                                 reserved178;	//0xCCA03128
	UINT32                                                 reserved179;	//0xCCA0312C
	UINT32                                                 reserved180;	//0xCCA03130
	UINT32                                                 reserved181;	//0xCCA03134
	UINT32                                                 reserved182;	//0xCCA03138
	UINT32                                                 reserved183;	//0xCCA0313C
	UINT32                                                 reserved184;	//0xCCA03140
	UINT32                                                 reserved185;	//0xCCA03144
	UINT32                                                 reserved186;	//0xCCA03148
	UINT32                                                 reserved187;	//0xCCA0314C
	UINT32                                                 reserved188;	//0xCCA03150
	UINT32                                                 reserved189;	//0xCCA03154
	UINT32                                                 reserved190;	//0xCCA03158
	UINT32                                                 reserved191;	//0xCCA0315C
	UINT32                                                 reserved192;	//0xCCA03160
	UINT32                                                 reserved193;	//0xCCA03164
	UINT32                                                 reserved194;	//0xCCA03168
	UINT32                                                 reserved195;	//0xCCA0316C
	UINT32                                                 reserved196;	//0xCCA03170
	UINT32                                                 reserved197;	//0xCCA03174
	UINT32                                                 reserved198;	//0xCCA03178
	UINT32                                                 reserved199;	//0xCCA0317C
	UINT32                                                 reserved200;	//0xCCA03180
	UINT32                                                 reserved201;	//0xCCA03184
	UINT32                                                 reserved202;	//0xCCA03188
	UINT32                                                 reserved203;	//0xCCA0318C
	UINT32                                                 reserved204;	//0xCCA03190
	UINT32                                                 reserved205;	//0xCCA03194
	UINT32                                                 reserved206;	//0xCCA03198
	UINT32                                                 reserved207;	//0xCCA0319C
	UINT32                                                 reserved208;	//0xCCA031A0
	UINT32                                                 reserved209;	//0xCCA031A4
	UINT32                                                 reserved210;	//0xCCA031A8
	UINT32                                                 reserved211;	//0xCCA031AC
	UINT32                                                 reserved212;	//0xCCA031B0
	UINT32                                                 reserved213;	//0xCCA031B4
	UINT32                                                 reserved214;	//0xCCA031B8
	UINT32                                                 reserved215;	//0xCCA031BC
	UINT32                                                 reserved216;	//0xCCA031C0
	UINT32                                                 reserved217;	//0xCCA031C4
	UINT32                                                 reserved218;	//0xCCA031C8
	UINT32                                                 reserved219;	//0xCCA031CC
	UINT32                                                 reserved220;	//0xCCA031D0
	UINT32                                                 reserved221;	//0xCCA031D4
	UINT32                                                 reserved222;	//0xCCA031D8
	UINT32                                                 reserved223;	//0xCCA031DC
	UINT32                                                 reserved224;	//0xCCA031E0
	UINT32                                                 reserved225;	//0xCCA031E4
	UINT32                                                 reserved226;	//0xCCA031E8
	UINT32                                                 reserved227;	//0xCCA031EC
	UINT32                                                 reserved228;	//0xCCA031F0
	UINT32                                                 reserved229;	//0xCCA031F4
	UINT32                                                 reserved230;	//0xCCA031F8
	UINT32                                                 reserved231;	//0xCCA031FC
	UINT32                                                 reserved232;	//0xCCA03200
	UINT32                                                 reserved233;	//0xCCA03204
	UINT32                                                 reserved234;	//0xCCA03208
	UINT32                                                 reserved235;	//0xCCA0320C
	UINT32                                                 reserved236;	//0xCCA03210
	UINT32                                                 reserved237;	//0xCCA03214
	UINT32                                                 reserved238;	//0xCCA03218
	UINT32                                                 reserved239;	//0xCCA0321C
	UINT32                                                 reserved240;	//0xCCA03220
	UINT32                                                 reserved241;	//0xCCA03224
	UINT32                                                 reserved242;	//0xCCA03228
	UINT32                                                 reserved243;	//0xCCA0322C
	UINT32                                                 reserved244;	//0xCCA03230
	UINT32                                                 reserved245;	//0xCCA03234
	UINT32                                                 reserved246;	//0xCCA03238
	UINT32                                                 reserved247;	//0xCCA0323C
	UINT32                                                 reserved248;	//0xCCA03240
	UINT32                                                 reserved249;	//0xCCA03244
	UINT32                                                 reserved250;	//0xCCA03248
	UINT32                                                 reserved251;	//0xCCA0324C
	UINT32                                                 reserved252;	//0xCCA03250
	UINT32                                                 reserved253;	//0xCCA03254
	UINT32                                                 reserved254;	//0xCCA03258
	UINT32                                                 reserved255;	//0xCCA0325C
	UINT32                                                 reserved256;	//0xCCA03260
	UINT32                                                 reserved257;	//0xCCA03264
	UINT32                                                 reserved258;	//0xCCA03268
	UINT32                                                 reserved259;	//0xCCA0326C
	UINT32                                                 reserved260;	//0xCCA03270
	UINT32                                                 reserved261;	//0xCCA03274
	UINT32                                                 reserved262;	//0xCCA03278
	UINT32                                                 reserved263;	//0xCCA0327C
	UINT32                                                 reserved264;	//0xCCA03280
	UINT32                                                 reserved265;	//0xCCA03284
	UINT32                                                 reserved266;	//0xCCA03288
	UINT32                                                 reserved267;	//0xCCA0328C
	UINT32                                                 reserved268;	//0xCCA03290
	UINT32                                                 reserved269;	//0xCCA03294
	UINT32                                                 reserved270;	//0xCCA03298
	UINT32                                                 reserved271;	//0xCCA0329C
	UINT32                                                 reserved272;	//0xCCA032A0
	UINT32                                                 reserved273;	//0xCCA032A4
	UINT32                                                 reserved274;	//0xCCA032A8
	UINT32                                                 reserved275;	//0xCCA032AC
	UINT32                                                 reserved276;	//0xCCA032B0
	UINT32                                                 reserved277;	//0xCCA032B4
	UINT32                                                 reserved278;	//0xCCA032B8
	UINT32                                                 reserved279;	//0xCCA032BC
	UINT32                                                 reserved280;	//0xCCA032C0
	UINT32                                                 reserved281;	//0xCCA032C4
	UINT32                                                 reserved282;	//0xCCA032C8
	UINT32                                                 reserved283;	//0xCCA032CC
	UINT32                                                 reserved284;	//0xCCA032D0
	UINT32                                                 reserved285;	//0xCCA032D4
	UINT32                                                 reserved286;	//0xCCA032D8
	UINT32                                                 reserved287;	//0xCCA032DC
	UINT32                                                 reserved288;	//0xCCA032E0
	UINT32                                                 reserved289;	//0xCCA032E4
	UINT32                                                 reserved290;	//0xCCA032E8
	UINT32                                                 reserved291;	//0xCCA032EC
	UINT32                                                 reserved292;	//0xCCA032F0
	UINT32                                                 reserved293;	//0xCCA032F4
	UINT32                                                 reserved294;	//0xCCA032F8
	UINT32                                                 reserved295;	//0xCCA032FC
	PE_O26_2K_SUB_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCCA03300
	PE_O26_2K_SUB_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCCA03304
	PE_O26_2K_SUB_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCCA03308
	PE_O26_2K_SUB_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCCA0330C
	PE_O26_2K_SUB_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCCA03310
	PE_O26_2K_SUB_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCCA03314
	UINT32                                                 reserved296;	//0xCCA03318
	UINT32                                                 reserved297;	//0xCCA0331C
	UINT32                                                 reserved298;	//0xCCA03320
	UINT32                                                 reserved299;	//0xCCA03324
	UINT32                                                 reserved300;	//0xCCA03328
	UINT32                                                 reserved301;	//0xCCA0332C
	UINT32                                                 reserved302;	//0xCCA03330
	UINT32                                                 reserved303;	//0xCCA03334
	UINT32                                                 reserved304;	//0xCCA03338
	UINT32                                                 reserved305;	//0xCCA0333C
	UINT32                                                 reserved306;	//0xCCA03340
	UINT32                                                 reserved307;	//0xCCA03344
	UINT32                                                 reserved308;	//0xCCA03348
	UINT32                                                 reserved309;	//0xCCA0334C
	UINT32                                                 reserved310;	//0xCCA03350
	UINT32                                                 reserved311;	//0xCCA03354
	UINT32                                                 reserved312;	//0xCCA03358
	UINT32                                                 reserved313;	//0xCCA0335C
	PE_O26_2K_SUB_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCCA03360
	PE_O26_2K_SUB_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCCA03364
	PE_O26_2K_SUB_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCCA03368
	PE_O26_2K_SUB_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCCA0336C
	UINT32                                                 reserved314;	//0xCCA03370
	UINT32                                                 reserved315;	//0xCCA03374
	UINT32                                                 reserved316;	//0xCCA03378
	UINT32                                                 reserved317;	//0xCCA0337C
	UINT32                                                 reserved318;	//0xCCA03380
	UINT32                                                 reserved319;	//0xCCA03384
	UINT32                                                 reserved320;	//0xCCA03388
	UINT32                                                 reserved321;	//0xCCA0338C
	UINT32                                                 reserved322;	//0xCCA03390
	UINT32                                                 reserved323;	//0xCCA03394
	UINT32                                                 reserved324;	//0xCCA03398
	UINT32                                                 reserved325;	//0xCCA0339C
	UINT32                                                 reserved326;	//0xCCA033A0
	UINT32                                                 reserved327;	//0xCCA033A4
	UINT32                                                 reserved328;	//0xCCA033A8
	UINT32                                                 reserved329;	//0xCCA033AC
	UINT32                                                 reserved330;	//0xCCA033B0
	UINT32                                                 reserved331;	//0xCCA033B4
	UINT32                                                 reserved332;	//0xCCA033B8
	UINT32                                                 reserved333;	//0xCCA033BC
	UINT32                                                 reserved334;	//0xCCA033C0
	UINT32                                                 reserved335;	//0xCCA033C4
	UINT32                                                 reserved336;	//0xCCA033C8
	UINT32                                                 reserved337;	//0xCCA033CC
	UINT32                                                 reserved338;	//0xCCA033D0
	UINT32                                                 reserved339;	//0xCCA033D4
	UINT32                                                 reserved340;	//0xCCA033D8
	UINT32                                                 reserved341;	//0xCCA033DC
	UINT32                                                 reserved342;	//0xCCA033E0
	UINT32                                                 reserved343;	//0xCCA033E4
	UINT32                                                 reserved344;	//0xCCA033E8
	UINT32                                                 reserved345;	//0xCCA033EC
	UINT32                                                 reserved346;	//0xCCA033F0
	UINT32                                                 reserved347;	//0xCCA033F4
	UINT32                                                 reserved348;	//0xCCA033F8
	UINT32                                                 reserved349;	//0xCCA033FC
	UINT32                                                 reserved350;	//0xCCA03400
	UINT32                                                 reserved351;	//0xCCA03404
	UINT32                                                 reserved352;	//0xCCA03408
	UINT32                                                 reserved353;	//0xCCA0340C
	UINT32                                                 reserved354;	//0xCCA03410
	UINT32                                                 reserved355;	//0xCCA03414
	UINT32                                                 reserved356;	//0xCCA03418
	UINT32                                                 reserved357;	//0xCCA0341C
	UINT32                                                 reserved358;	//0xCCA03420
	UINT32                                                 reserved359;	//0xCCA03424
	UINT32                                                 reserved360;	//0xCCA03428
	UINT32                                                 reserved361;	//0xCCA0342C
	UINT32                                                 reserved362;	//0xCCA03430
	UINT32                                                 reserved363;	//0xCCA03434
	UINT32                                                 reserved364;	//0xCCA03438
	UINT32                                                 reserved365;	//0xCCA0343C
	UINT32                                                 reserved366;	//0xCCA03440
	UINT32                                                 reserved367;	//0xCCA03444
	UINT32                                                 reserved368;	//0xCCA03448
	UINT32                                                 reserved369;	//0xCCA0344C
	UINT32                                                 reserved370;	//0xCCA03450
	UINT32                                                 reserved371;	//0xCCA03454
	UINT32                                                 reserved372;	//0xCCA03458
	UINT32                                                 reserved373;	//0xCCA0345C
	UINT32                                                 reserved374;	//0xCCA03460
	UINT32                                                 reserved375;	//0xCCA03464
	UINT32                                                 reserved376;	//0xCCA03468
	UINT32                                                 reserved377;	//0xCCA0346C
	UINT32                                                 reserved378;	//0xCCA03470
	UINT32                                                 reserved379;	//0xCCA03474
	UINT32                                                 reserved380;	//0xCCA03478
	UINT32                                                 reserved381;	//0xCCA0347C
	UINT32                                                 reserved382;	//0xCCA03480
	UINT32                                                 reserved383;	//0xCCA03484
	UINT32                                                 reserved384;	//0xCCA03488
	UINT32                                                 reserved385;	//0xCCA0348C
	UINT32                                                 reserved386;	//0xCCA03490
	UINT32                                                 reserved387;	//0xCCA03494
	UINT32                                                 reserved388;	//0xCCA03498
	UINT32                                                 reserved389;	//0xCCA0349C
	UINT32                                                 reserved390;	//0xCCA034A0
	UINT32                                                 reserved391;	//0xCCA034A4
	UINT32                                                 reserved392;	//0xCCA034A8
	UINT32                                                 reserved393;	//0xCCA034AC
	UINT32                                                 reserved394;	//0xCCA034B0
	UINT32                                                 reserved395;	//0xCCA034B4
	UINT32                                                 reserved396;	//0xCCA034B8
	UINT32                                                 reserved397;	//0xCCA034BC
	UINT32                                                 reserved398;	//0xCCA034C0
	UINT32                                                 reserved399;	//0xCCA034C4
	UINT32                                                 reserved400;	//0xCCA034C8
	UINT32                                                 reserved401;	//0xCCA034CC
	UINT32                                                 reserved402;	//0xCCA034D0
	UINT32                                                 reserved403;	//0xCCA034D4
	UINT32                                                 reserved404;	//0xCCA034D8
	UINT32                                                 reserved405;	//0xCCA034DC
	UINT32                                                 reserved406;	//0xCCA034E0
	UINT32                                                 reserved407;	//0xCCA034E4
	UINT32                                                 reserved408;	//0xCCA034E8
	UINT32                                                 reserved409;	//0xCCA034EC
	PE_O26_2K_SUB_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCCA034F0
	PE_O26_2K_SUB_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCCA034F4
	PE_O26_2K_SUB_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCCA034F8
	PE_O26_2K_SUB_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCCA034FC
}PE_SR_2K_SHP1_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01400 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O26_2KC_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01404 RW 0x0438_03C0
	UINT32 reg_top_width                    :12;	//(11:0,NA,960) //Processing width  (default : 960)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //Processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01408 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O26_2KC_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0140C RW 0x000A_0000
	UINT32 resvd0                           :16;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,10) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01500 RW 0xFFFF_0000
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //Pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //Pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :13;
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //Pattern pixel value (CB)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //Pattern pixel value (CR)
	};
}PE_O26_2KC_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01800 RW 0x8010_0179
	UINT32 reg_cdj_edf_en                   :1;	//(0:0,NA,1) //Edge-directional de-jagging enable
	UINT32 reg_cdj_hv_filter_en             :1;	//(1:1,NA,0) //H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_cdj_edge_adaptive_en         :1;	//(3:3,NA,1) //Edge adaptive filter enable
	UINT32 reg_cdj_line_variation_mode      :1;	//(4:4,NA,1) //Line variation mode	0: sum of (cur - center)	1: sum of adjacent pixel difference
	UINT32 reg_cdj_l_type_protection        :1;	//(5:5,NA,1) //L-type protection
	UINT32 reg_cdj_soft_en                  :1;	//(6:6,NA,1) //Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_cdj_count_diff_th            :5;	//(12:8,NA,1) //Matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_cdj_output_mux               :3;	//(18:16,NA,0) //Debug display	0: normal display	1: direction map	2: g0: feature (matchness)	3: g0: gain	4: g1: gain (protection)	5: final gain	6: blur coring map(used for blur-filtering)
	UINT32 reg_cdj_buffer_detour_en         :1;	//(19:19,NA,0) //DJ buffer detour enable
	UINT32 reg_cdj_center_blur_mode         :2;	//(21:20,NA,1) //Center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_cdj_n_avg_mode               :1;	//(22:22,NA,0) //Neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_cdj_detour_en                :1;	//(23:23,NA,0) //DJ detour enable
	UINT32 reg_cdj_line_variation_diff_th   :8;	//(31:24,NA,128) //Line-variation threshold for edge-direction decision
	};
}PE_O26_2KC_SHP_CDJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01804 RW 0x0080_0000
	UINT32 reg_cdj_level_th                 :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_cdj_n_avg_gain               :8;	//(23:16,NA,128) //Neighborhood pixel averaging: gain
	UINT32 resvd1                           :8;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01808 RW 0x0000_1010
	UINT32 reg_cdj_g0_cnt_min               :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_cdj_g0_mul                   :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0180C RW 0x8010_0840
	UINT32 reg_cdj_g1_protect_min           :8;	//(7:0,NA,64) //g1: min diff th - LR Diff
	UINT32 reg_cdj_g1_mul                   :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_cdj_edge_min                 :8;	//(23:16,NA,16) //Edge adaptive filter min value
	UINT32 reg_cdj_edge_mul                 :8;	//(31:24,NA,128) //Edge adaptive filter multiplication value
	};
}PE_O26_2KC_SHP_CDJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01810 RW 0x0000_0000
	UINT32 reg_cdj_dir_sel_c1               :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_cdj_dir_sel_c2               :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_cdj_dir_sel_c3               :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_cdj_dir_sel_c4               :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01814 RW 0x0000_0000
	UINT32 reg_cdj_pattern0_0_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [0][0]
	UINT32 reg_cdj_pattern0_0_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [0][1]
	UINT32 reg_cdj_pattern0_0_02            :2;	//(5:4,NA,0) //DJ protect pattern0 [0][2]
	UINT32 reg_cdj_pattern0_0_03            :2;	//(7:6,NA,0) //DJ protect pattern0 [0][3]
	UINT32 reg_cdj_pattern0_0_04            :2;	//(9:8,NA,0) //DJ protect pattern0 [0][4]
	UINT32 reg_cdj_pattern0_0_05            :2;	//(11:10,NA,0) //DJ protect pattern0 [0][5]
	UINT32 reg_cdj_pattern0_0_06            :2;	//(13:12,NA,0) //DJ protect pattern0 [0][6]
	UINT32 reg_cdj_pattern0_0_07            :2;	//(15:14,NA,0) //DJ protect pattern0 [0][7]
	UINT32 reg_cdj_pattern0_0_08            :2;	//(17:16,NA,0) //DJ protect pattern0 [0][8]
	UINT32 reg_cdj_pattern0_0_09            :2;	//(19:18,NA,0) //DJ protect pattern0 [0][9]
	UINT32 reg_cdj_pattern0_0_10            :2;	//(21:20,NA,0) //DJ protect pattern0 [0][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01818 RW 0x0000_0040
	UINT32 reg_cdj_pattern0_1_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [1][0]
	UINT32 reg_cdj_pattern0_1_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [1][1]
	UINT32 reg_cdj_pattern0_1_02            :2;	//(5:4,NA,0) //DJ protect pattern0 [1][2]
	UINT32 reg_cdj_pattern0_1_03            :2;	//(7:6,NA,1) //DJ protect pattern0 [1][3]
	UINT32 reg_cdj_pattern0_1_04            :2;	//(9:8,NA,0) //DJ protect pattern0 [1][4]
	UINT32 reg_cdj_pattern0_1_05            :2;	//(11:10,NA,0) //DJ protect pattern0 [1][5]
	UINT32 reg_cdj_pattern0_1_06            :2;	//(13:12,NA,0) //DJ protect pattern0 [1][6]
	UINT32 reg_cdj_pattern0_1_07            :2;	//(15:14,NA,0) //DJ protect pattern0 [1][7]
	UINT32 reg_cdj_pattern0_1_08            :2;	//(17:16,NA,0) //DJ protect pattern0 [1][8]
	UINT32 reg_cdj_pattern0_1_09            :2;	//(19:18,NA,0) //DJ protect pattern0 [1][9]
	UINT32 reg_cdj_pattern0_1_10            :2;	//(21:20,NA,0) //DJ protect pattern0 [1][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0181C RW 0x0015_5550
	UINT32 reg_cdj_pattern0_2_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [2][0]
	UINT32 reg_cdj_pattern0_2_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [2][1]
	UINT32 reg_cdj_pattern0_2_02            :2;	//(5:4,NA,1) //DJ protect pattern0 [2][2]
	UINT32 reg_cdj_pattern0_2_03            :2;	//(7:6,NA,1) //DJ protect pattern0 [2][3]
	UINT32 reg_cdj_pattern0_2_04            :2;	//(9:8,NA,1) //DJ protect pattern0 [2][4]
	UINT32 reg_cdj_pattern0_2_05            :2;	//(11:10,NA,1) //DJ protect pattern0 [2][5]
	UINT32 reg_cdj_pattern0_2_06            :2;	//(13:12,NA,1) //DJ protect pattern0 [2][6]
	UINT32 reg_cdj_pattern0_2_07            :2;	//(15:14,NA,1) //DJ protect pattern0 [2][7]
	UINT32 reg_cdj_pattern0_2_08            :2;	//(17:16,NA,1) //DJ protect pattern0 [2][8]
	UINT32 reg_cdj_pattern0_2_09            :2;	//(19:18,NA,1) //DJ protect pattern0 [2][9]
	UINT32 reg_cdj_pattern0_2_10            :2;	//(21:20,NA,1) //DJ protect pattern0 [2][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01820 RW 0x0000_0040
	UINT32 reg_cdj_pattern0_3_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [3][0]
	UINT32 reg_cdj_pattern0_3_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [3][1]
	UINT32 reg_cdj_pattern0_3_02            :2;	//(5:4,NA,0) //DJ protect pattern0 [3][2]
	UINT32 reg_cdj_pattern0_3_03            :2;	//(7:6,NA,1) //DJ protect pattern0 [3][3]
	UINT32 reg_cdj_pattern0_3_04            :2;	//(9:8,NA,0) //DJ protect pattern0 [3][4]
	UINT32 reg_cdj_pattern0_3_05            :2;	//(11:10,NA,0) //DJ protect pattern0 [3][5]
	UINT32 reg_cdj_pattern0_3_06            :2;	//(13:12,NA,0) //DJ protect pattern0 [3][6]
	UINT32 reg_cdj_pattern0_3_07            :2;	//(15:14,NA,0) //DJ protect pattern0 [3][7]
	UINT32 reg_cdj_pattern0_3_08            :2;	//(17:16,NA,0) //DJ protect pattern0 [3][8]
	UINT32 reg_cdj_pattern0_3_09            :2;	//(19:18,NA,0) //DJ protect pattern0 [3][9]
	UINT32 reg_cdj_pattern0_3_10            :2;	//(21:20,NA,0) //DJ protect pattern0 [3][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01824 RW 0x002A_A040
	UINT32 reg_cdj_pattern0_4_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [4][0]
	UINT32 reg_cdj_pattern0_4_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [4][1]
	UINT32 reg_cdj_pattern0_4_02            :2;	//(5:4,NA,0) //DJ protect pattern0 [4][2]
	UINT32 reg_cdj_pattern0_4_03            :2;	//(7:6,NA,1) //DJ protect pattern0 [4][3]
	UINT32 reg_cdj_pattern0_4_04            :2;	//(9:8,NA,0) //DJ protect pattern0 [4][4]
	UINT32 reg_cdj_pattern0_4_05            :2;	//(11:10,NA,0) //DJ protect pattern0 [4][5]
	UINT32 reg_cdj_pattern0_4_06            :2;	//(13:12,NA,2) //DJ protect pattern0 [4][6]
	UINT32 reg_cdj_pattern0_4_07            :2;	//(15:14,NA,2) //DJ protect pattern0 [4][7]
	UINT32 reg_cdj_pattern0_4_08            :2;	//(17:16,NA,2) //DJ protect pattern0 [4][8]
	UINT32 reg_cdj_pattern0_4_09            :2;	//(19:18,NA,2) //DJ protect pattern0 [4][9]
	UINT32 reg_cdj_pattern0_4_10            :2;	//(21:20,NA,2) //DJ protect pattern0 [4][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01828 RW 0x002A_A040
	UINT32 reg_cdj_pattern0_5_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [5][0]
	UINT32 reg_cdj_pattern0_5_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [5][1]
	UINT32 reg_cdj_pattern0_5_02            :2;	//(5:4,NA,0) //DJ protect pattern0 [5][2]
	UINT32 reg_cdj_pattern0_5_03            :2;	//(7:6,NA,1) //DJ protect pattern0 [5][3]
	UINT32 reg_cdj_pattern0_5_04            :2;	//(9:8,NA,0) //DJ protect pattern0 [5][4]
	UINT32 reg_cdj_pattern0_5_05            :2;	//(11:10,NA,0) //DJ protect pattern0 [5][5]
	UINT32 reg_cdj_pattern0_5_06            :2;	//(13:12,NA,2) //DJ protect pattern0 [5][6]
	UINT32 reg_cdj_pattern0_5_07            :2;	//(15:14,NA,2) //DJ protect pattern0 [5][7]
	UINT32 reg_cdj_pattern0_5_08            :2;	//(17:16,NA,2) //DJ protect pattern0 [5][8]
	UINT32 reg_cdj_pattern0_5_09            :2;	//(19:18,NA,2) //DJ protect pattern0 [5][9]
	UINT32 reg_cdj_pattern0_5_10            :2;	//(21:20,NA,2) //DJ protect pattern0 [5][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0182C RW 0x000A_A040
	UINT32 reg_cdj_pattern0_6_00            :2;	//(1:0,NA,0) //DJ protect pattern0 [6][0]
	UINT32 reg_cdj_pattern0_6_01            :2;	//(3:2,NA,0) //DJ protect pattern0 [6][1]
	UINT32 reg_cdj_pattern0_6_02            :2;	//(5:4,NA,0) //DJ protect pattern0 [6][2]
	UINT32 reg_cdj_pattern0_6_03            :2;	//(7:6,NA,1) //DJ protect pattern0 [6][3]
	UINT32 reg_cdj_pattern0_6_04            :2;	//(9:8,NA,0) //DJ protect pattern0 [6][4]
	UINT32 reg_cdj_pattern0_6_05            :2;	//(11:10,NA,0) //DJ protect pattern0 [6][5]
	UINT32 reg_cdj_pattern0_6_06            :2;	//(13:12,NA,2) //DJ protect pattern0 [6][6]
	UINT32 reg_cdj_pattern0_6_07            :2;	//(15:14,NA,2) //DJ protect pattern0 [6][7]
	UINT32 reg_cdj_pattern0_6_08            :2;	//(17:16,NA,2) //DJ protect pattern0 [6][8]
	UINT32 reg_cdj_pattern0_6_09            :2;	//(19:18,NA,2) //DJ protect pattern0 [6][9]
	UINT32 reg_cdj_pattern0_6_10            :2;	//(21:20,NA,0) //DJ protect pattern0 [6][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01830 RW 0x0000_00E4
	UINT32 reg_cdj_pattern0_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern0 flip0, H
	UINT32 reg_cdj_pattern0_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern0 flip0, V
	UINT32 reg_cdj_pattern0_flip1_h         :1;	//(2:2,NA,1) //DJ protect pattern0 flip1, H
	UINT32 reg_cdj_pattern0_flip1_v         :1;	//(3:3,NA,0) //DJ protect pattern0 flip1, V
	UINT32 reg_cdj_pattern0_flip2_h         :1;	//(4:4,NA,0) //DJ protect pattern0 flip2, H
	UINT32 reg_cdj_pattern0_flip2_v         :1;	//(5:5,NA,1) //DJ protect pattern0 flip2, V
	UINT32 reg_cdj_pattern0_flip3_h         :1;	//(6:6,NA,1) //DJ protect pattern0 flip3, H
	UINT32 reg_cdj_pattern0_flip3_v         :1;	//(7:7,NA,1) //DJ protect pattern0 flip3, V
	UINT32 resvd                            :24;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01834 RW 0x0000_5540
	UINT32 reg_cdj_pattern1_0_00            :2;	//(1:0,NA,0) //DJ protect pattern1 [0][0]
	UINT32 reg_cdj_pattern1_0_01            :2;	//(3:2,NA,0) //DJ protect pattern1 [0][1]
	UINT32 reg_cdj_pattern1_0_02            :2;	//(5:4,NA,0) //DJ protect pattern1 [0][2]
	UINT32 reg_cdj_pattern1_0_03            :2;	//(7:6,NA,1) //DJ protect pattern1 [0][3]
	UINT32 reg_cdj_pattern1_0_04            :2;	//(9:8,NA,1) //DJ protect pattern1 [0][4]
	UINT32 reg_cdj_pattern1_0_05            :2;	//(11:10,NA,1) //DJ protect pattern1 [0][5]
	UINT32 reg_cdj_pattern1_0_06            :2;	//(13:12,NA,1) //DJ protect pattern1 [0][6]
	UINT32 reg_cdj_pattern1_0_07            :2;	//(15:14,NA,1) //DJ protect pattern1 [0][7]
	UINT32 reg_cdj_pattern1_0_08            :2;	//(17:16,NA,0) //DJ protect pattern1 [0][8]
	UINT32 reg_cdj_pattern1_0_09            :2;	//(19:18,NA,0) //DJ protect pattern1 [0][9]
	UINT32 reg_cdj_pattern1_0_10            :2;	//(21:20,NA,0) //DJ protect pattern1 [0][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01838 RW 0x0020_5542
	UINT32 reg_cdj_pattern1_1_00            :2;	//(1:0,NA,2) //DJ protect pattern1 [1][0]
	UINT32 reg_cdj_pattern1_1_01            :2;	//(3:2,NA,0) //DJ protect pattern1 [1][1]
	UINT32 reg_cdj_pattern1_1_02            :2;	//(5:4,NA,0) //DJ protect pattern1 [1][2]
	UINT32 reg_cdj_pattern1_1_03            :2;	//(7:6,NA,1) //DJ protect pattern1 [1][3]
	UINT32 reg_cdj_pattern1_1_04            :2;	//(9:8,NA,1) //DJ protect pattern1 [1][4]
	UINT32 reg_cdj_pattern1_1_05            :2;	//(11:10,NA,1) //DJ protect pattern1 [1][5]
	UINT32 reg_cdj_pattern1_1_06            :2;	//(13:12,NA,1) //DJ protect pattern1 [1][6]
	UINT32 reg_cdj_pattern1_1_07            :2;	//(15:14,NA,1) //DJ protect pattern1 [1][7]
	UINT32 reg_cdj_pattern1_1_08            :2;	//(17:16,NA,0) //DJ protect pattern1 [1][8]
	UINT32 reg_cdj_pattern1_1_09            :2;	//(19:18,NA,0) //DJ protect pattern1 [1][9]
	UINT32 reg_cdj_pattern1_1_10            :2;	//(21:20,NA,2) //DJ protect pattern1 [1][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0183C RW 0x0008_1508
	UINT32 reg_cdj_pattern1_2_00            :2;	//(1:0,NA,0) //DJ protect pattern1 [2][0]
	UINT32 reg_cdj_pattern1_2_01            :2;	//(3:2,NA,2) //DJ protect pattern1 [2][1]
	UINT32 reg_cdj_pattern1_2_02            :2;	//(5:4,NA,0) //DJ protect pattern1 [2][2]
	UINT32 reg_cdj_pattern1_2_03            :2;	//(7:6,NA,0) //DJ protect pattern1 [2][3]
	UINT32 reg_cdj_pattern1_2_04            :2;	//(9:8,NA,1) //DJ protect pattern1 [2][4]
	UINT32 reg_cdj_pattern1_2_05            :2;	//(11:10,NA,1) //DJ protect pattern1 [2][5]
	UINT32 reg_cdj_pattern1_2_06            :2;	//(13:12,NA,1) //DJ protect pattern1 [2][6]
	UINT32 reg_cdj_pattern1_2_07            :2;	//(15:14,NA,0) //DJ protect pattern1 [2][7]
	UINT32 reg_cdj_pattern1_2_08            :2;	//(17:16,NA,0) //DJ protect pattern1 [2][8]
	UINT32 reg_cdj_pattern1_2_09            :2;	//(19:18,NA,2) //DJ protect pattern1 [2][9]
	UINT32 reg_cdj_pattern1_2_10            :2;	//(21:20,NA,0) //DJ protect pattern1 [2][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01840 RW 0x0002_0420
	UINT32 reg_cdj_pattern1_3_00            :2;	//(1:0,NA,0) //DJ protect pattern1 [3][0]
	UINT32 reg_cdj_pattern1_3_01            :2;	//(3:2,NA,0) //DJ protect pattern1 [3][1]
	UINT32 reg_cdj_pattern1_3_02            :2;	//(5:4,NA,2) //DJ protect pattern1 [3][2]
	UINT32 reg_cdj_pattern1_3_03            :2;	//(7:6,NA,0) //DJ protect pattern1 [3][3]
	UINT32 reg_cdj_pattern1_3_04            :2;	//(9:8,NA,0) //DJ protect pattern1 [3][4]
	UINT32 reg_cdj_pattern1_3_05            :2;	//(11:10,NA,1) //DJ protect pattern1 [3][5]
	UINT32 reg_cdj_pattern1_3_06            :2;	//(13:12,NA,0) //DJ protect pattern1 [3][6]
	UINT32 reg_cdj_pattern1_3_07            :2;	//(15:14,NA,0) //DJ protect pattern1 [3][7]
	UINT32 reg_cdj_pattern1_3_08            :2;	//(17:16,NA,2) //DJ protect pattern1 [3][8]
	UINT32 reg_cdj_pattern1_3_09            :2;	//(19:18,NA,0) //DJ protect pattern1 [3][9]
	UINT32 reg_cdj_pattern1_3_10            :2;	//(21:20,NA,0) //DJ protect pattern1 [3][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01844 RW 0x0000_8080
	UINT32 reg_cdj_pattern1_4_00            :2;	//(1:0,NA,0) //DJ protect pattern1 [4][0]
	UINT32 reg_cdj_pattern1_4_01            :2;	//(3:2,NA,0) //DJ protect pattern1 [4][1]
	UINT32 reg_cdj_pattern1_4_02            :2;	//(5:4,NA,0) //DJ protect pattern1 [4][2]
	UINT32 reg_cdj_pattern1_4_03            :2;	//(7:6,NA,2) //DJ protect pattern1 [4][3]
	UINT32 reg_cdj_pattern1_4_04            :2;	//(9:8,NA,0) //DJ protect pattern1 [4][4]
	UINT32 reg_cdj_pattern1_4_05            :2;	//(11:10,NA,0) //DJ protect pattern1 [4][5]
	UINT32 reg_cdj_pattern1_4_06            :2;	//(13:12,NA,0) //DJ protect pattern1 [4][6]
	UINT32 reg_cdj_pattern1_4_07            :2;	//(15:14,NA,2) //DJ protect pattern1 [4][7]
	UINT32 reg_cdj_pattern1_4_08            :2;	//(17:16,NA,0) //DJ protect pattern1 [4][8]
	UINT32 reg_cdj_pattern1_4_09            :2;	//(19:18,NA,0) //DJ protect pattern1 [4][9]
	UINT32 reg_cdj_pattern1_4_10            :2;	//(21:20,NA,0) //DJ protect pattern1 [4][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01848 RW 0x0000_2A00
	UINT32 reg_cdj_pattern1_5_00            :2;	//(1:0,NA,0) //DJ protect pattern1 [5][0]
	UINT32 reg_cdj_pattern1_5_01            :2;	//(3:2,NA,0) //DJ protect pattern1 [5][1]
	UINT32 reg_cdj_pattern1_5_02            :2;	//(5:4,NA,0) //DJ protect pattern1 [5][2]
	UINT32 reg_cdj_pattern1_5_03            :2;	//(7:6,NA,0) //DJ protect pattern1 [5][3]
	UINT32 reg_cdj_pattern1_5_04            :2;	//(9:8,NA,2) //DJ protect pattern1 [5][4]
	UINT32 reg_cdj_pattern1_5_05            :2;	//(11:10,NA,2) //DJ protect pattern1 [5][5]
	UINT32 reg_cdj_pattern1_5_06            :2;	//(13:12,NA,2) //DJ protect pattern1 [5][6]
	UINT32 reg_cdj_pattern1_5_07            :2;	//(15:14,NA,0) //DJ protect pattern1 [5][7]
	UINT32 reg_cdj_pattern1_5_08            :2;	//(17:16,NA,0) //DJ protect pattern1 [5][8]
	UINT32 reg_cdj_pattern1_5_09            :2;	//(19:18,NA,0) //DJ protect pattern1 [5][9]
	UINT32 reg_cdj_pattern1_5_10            :2;	//(21:20,NA,0) //DJ protect pattern1 [5][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0184C RW 0x0000_2A00
	UINT32 reg_cdj_pattern1_6_00            :2;	//(1:0,NA,0) //DJ protect pattern1 [6][0]
	UINT32 reg_cdj_pattern1_6_01            :2;	//(3:2,NA,0) //DJ protect pattern1 [6][1]
	UINT32 reg_cdj_pattern1_6_02            :2;	//(5:4,NA,0) //DJ protect pattern1 [6][2]
	UINT32 reg_cdj_pattern1_6_03            :2;	//(7:6,NA,0) //DJ protect pattern1 [6][3]
	UINT32 reg_cdj_pattern1_6_04            :2;	//(9:8,NA,2) //DJ protect pattern1 [6][4]
	UINT32 reg_cdj_pattern1_6_05            :2;	//(11:10,NA,2) //DJ protect pattern1 [6][5]
	UINT32 reg_cdj_pattern1_6_06            :2;	//(13:12,NA,2) //DJ protect pattern1 [6][6]
	UINT32 reg_cdj_pattern1_6_07            :2;	//(15:14,NA,0) //DJ protect pattern1 [6][7]
	UINT32 reg_cdj_pattern1_6_08            :2;	//(17:16,NA,0) //DJ protect pattern1 [6][8]
	UINT32 reg_cdj_pattern1_6_09            :2;	//(19:18,NA,0) //DJ protect pattern1 [6][9]
	UINT32 reg_cdj_pattern1_6_10            :2;	//(21:20,NA,0) //DJ protect pattern1 [6][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01850 RW 0x0000_0008
	UINT32 reg_cdj_pattern1_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_cdj_pattern1_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_cdj_pattern1_flip1_h         :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_cdj_pattern1_flip1_v         :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01854 RW 0x0000_2800
	UINT32 reg_cdj_pattern2_0_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [0][0]
	UINT32 reg_cdj_pattern2_0_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [0][1]
	UINT32 reg_cdj_pattern2_0_02            :2;	//(5:4,NA,0) //DJ protect pattern2 [0][2]
	UINT32 reg_cdj_pattern2_0_03            :2;	//(7:6,NA,0) //DJ protect pattern2 [0][3]
	UINT32 reg_cdj_pattern2_0_04            :2;	//(9:8,NA,0) //DJ protect pattern2 [0][4]
	UINT32 reg_cdj_pattern2_0_05            :2;	//(11:10,NA,2) //DJ protect pattern2 [0][5]
	UINT32 reg_cdj_pattern2_0_06            :2;	//(13:12,NA,2) //DJ protect pattern2 [0][6]
	UINT32 reg_cdj_pattern2_0_07            :2;	//(15:14,NA,0) //DJ protect pattern2 [0][7]
	UINT32 reg_cdj_pattern2_0_08            :2;	//(17:16,NA,0) //DJ protect pattern2 [0][8]
	UINT32 reg_cdj_pattern2_0_09            :2;	//(19:18,NA,0) //DJ protect pattern2 [0][9]
	UINT32 reg_cdj_pattern2_0_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [0][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01858 RW 0x0005_0A00
	UINT32 reg_cdj_pattern2_1_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [1][0]
	UINT32 reg_cdj_pattern2_1_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [1][1]
	UINT32 reg_cdj_pattern2_1_02            :2;	//(5:4,NA,0) //DJ protect pattern2 [1][2]
	UINT32 reg_cdj_pattern2_1_03            :2;	//(7:6,NA,0) //DJ protect pattern2 [1][3]
	UINT32 reg_cdj_pattern2_1_04            :2;	//(9:8,NA,2) //DJ protect pattern2 [1][4]
	UINT32 reg_cdj_pattern2_1_05            :2;	//(11:10,NA,2) //DJ protect pattern2 [1][5]
	UINT32 reg_cdj_pattern2_1_06            :2;	//(13:12,NA,0) //DJ protect pattern2 [1][6]
	UINT32 reg_cdj_pattern2_1_07            :2;	//(15:14,NA,0) //DJ protect pattern2 [1][7]
	UINT32 reg_cdj_pattern2_1_08            :2;	//(17:16,NA,1) //DJ protect pattern2 [1][8]
	UINT32 reg_cdj_pattern2_1_09            :2;	//(19:18,NA,1) //DJ protect pattern2 [1][9]
	UINT32 reg_cdj_pattern2_1_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [1][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0185C RW 0x0005_4280
	UINT32 reg_cdj_pattern2_2_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [2][0]
	UINT32 reg_cdj_pattern2_2_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [2][1]
	UINT32 reg_cdj_pattern2_2_02            :2;	//(5:4,NA,0) //DJ protect pattern2 [2][2]
	UINT32 reg_cdj_pattern2_2_03            :2;	//(7:6,NA,2) //DJ protect pattern2 [2][3]
	UINT32 reg_cdj_pattern2_2_04            :2;	//(9:8,NA,2) //DJ protect pattern2 [2][4]
	UINT32 reg_cdj_pattern2_2_05            :2;	//(11:10,NA,0) //DJ protect pattern2 [2][5]
	UINT32 reg_cdj_pattern2_2_06            :2;	//(13:12,NA,0) //DJ protect pattern2 [2][6]
	UINT32 reg_cdj_pattern2_2_07            :2;	//(15:14,NA,1) //DJ protect pattern2 [2][7]
	UINT32 reg_cdj_pattern2_2_08            :2;	//(17:16,NA,1) //DJ protect pattern2 [2][8]
	UINT32 reg_cdj_pattern2_2_09            :2;	//(19:18,NA,1) //DJ protect pattern2 [2][9]
	UINT32 reg_cdj_pattern2_2_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [2][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01860 RW 0x0005_50A0
	UINT32 reg_cdj_pattern2_3_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [3][0]
	UINT32 reg_cdj_pattern2_3_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [3][1]
	UINT32 reg_cdj_pattern2_3_02            :2;	//(5:4,NA,2) //DJ protect pattern2 [3][2]
	UINT32 reg_cdj_pattern2_3_03            :2;	//(7:6,NA,2) //DJ protect pattern2 [3][3]
	UINT32 reg_cdj_pattern2_3_04            :2;	//(9:8,NA,0) //DJ protect pattern2 [3][4]
	UINT32 reg_cdj_pattern2_3_05            :2;	//(11:10,NA,0) //DJ protect pattern2 [3][5]
	UINT32 reg_cdj_pattern2_3_06            :2;	//(13:12,NA,1) //DJ protect pattern2 [3][6]
	UINT32 reg_cdj_pattern2_3_07            :2;	//(15:14,NA,1) //DJ protect pattern2 [3][7]
	UINT32 reg_cdj_pattern2_3_08            :2;	//(17:16,NA,1) //DJ protect pattern2 [3][8]
	UINT32 reg_cdj_pattern2_3_09            :2;	//(19:18,NA,1) //DJ protect pattern2 [3][9]
	UINT32 reg_cdj_pattern2_3_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [3][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01864 RW 0x0005_4280
	UINT32 reg_cdj_pattern2_4_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [4][0]
	UINT32 reg_cdj_pattern2_4_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [4][1]
	UINT32 reg_cdj_pattern2_4_02            :2;	//(5:4,NA,0) //DJ protect pattern2 [4][2]
	UINT32 reg_cdj_pattern2_4_03            :2;	//(7:6,NA,2) //DJ protect pattern2 [4][3]
	UINT32 reg_cdj_pattern2_4_04            :2;	//(9:8,NA,2) //DJ protect pattern2 [4][4]
	UINT32 reg_cdj_pattern2_4_05            :2;	//(11:10,NA,0) //DJ protect pattern2 [4][5]
	UINT32 reg_cdj_pattern2_4_06            :2;	//(13:12,NA,0) //DJ protect pattern2 [4][6]
	UINT32 reg_cdj_pattern2_4_07            :2;	//(15:14,NA,1) //DJ protect pattern2 [4][7]
	UINT32 reg_cdj_pattern2_4_08            :2;	//(17:16,NA,1) //DJ protect pattern2 [4][8]
	UINT32 reg_cdj_pattern2_4_09            :2;	//(19:18,NA,1) //DJ protect pattern2 [4][9]
	UINT32 reg_cdj_pattern2_4_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [4][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01868 RW 0x0005_0A00
	UINT32 reg_cdj_pattern2_5_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [5][0]
	UINT32 reg_cdj_pattern2_5_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [5][1]
	UINT32 reg_cdj_pattern2_5_02            :2;	//(5:4,NA,0) //DJ protect pattern2 [5][2]
	UINT32 reg_cdj_pattern2_5_03            :2;	//(7:6,NA,0) //DJ protect pattern2 [5][3]
	UINT32 reg_cdj_pattern2_5_04            :2;	//(9:8,NA,2) //DJ protect pattern2 [5][4]
	UINT32 reg_cdj_pattern2_5_05            :2;	//(11:10,NA,2) //DJ protect pattern2 [5][5]
	UINT32 reg_cdj_pattern2_5_06            :2;	//(13:12,NA,0) //DJ protect pattern2 [5][6]
	UINT32 reg_cdj_pattern2_5_07            :2;	//(15:14,NA,0) //DJ protect pattern2 [5][7]
	UINT32 reg_cdj_pattern2_5_08            :2;	//(17:16,NA,1) //DJ protect pattern2 [5][8]
	UINT32 reg_cdj_pattern2_5_09            :2;	//(19:18,NA,1) //DJ protect pattern2 [5][9]
	UINT32 reg_cdj_pattern2_5_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [5][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0186C RW 0x0000_2800
	UINT32 reg_cdj_pattern2_6_00            :2;	//(1:0,NA,0) //DJ protect pattern2 [6][0]
	UINT32 reg_cdj_pattern2_6_01            :2;	//(3:2,NA,0) //DJ protect pattern2 [6][1]
	UINT32 reg_cdj_pattern2_6_02            :2;	//(5:4,NA,0) //DJ protect pattern2 [6][2]
	UINT32 reg_cdj_pattern2_6_03            :2;	//(7:6,NA,0) //DJ protect pattern2 [6][3]
	UINT32 reg_cdj_pattern2_6_04            :2;	//(9:8,NA,0) //DJ protect pattern2 [6][4]
	UINT32 reg_cdj_pattern2_6_05            :2;	//(11:10,NA,2) //DJ protect pattern2 [6][5]
	UINT32 reg_cdj_pattern2_6_06            :2;	//(13:12,NA,2) //DJ protect pattern2 [6][6]
	UINT32 reg_cdj_pattern2_6_07            :2;	//(15:14,NA,0) //DJ protect pattern2 [6][7]
	UINT32 reg_cdj_pattern2_6_08            :2;	//(17:16,NA,0) //DJ protect pattern2 [6][8]
	UINT32 reg_cdj_pattern2_6_09            :2;	//(19:18,NA,0) //DJ protect pattern2 [6][9]
	UINT32 reg_cdj_pattern2_6_10            :2;	//(21:20,NA,0) //DJ protect pattern2 [6][10]
	UINT32 resvd                            :10;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01870 RW 0x0000_0004
	UINT32 reg_cdj_pattern2_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_cdj_pattern2_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_cdj_pattern2_flip1_h         :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_cdj_pattern2_flip1_v         :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01874 RW 0x00FF_0628
	UINT32 reg_cdj_soft_g0_mul              :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g0_offset           :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g0_max              :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01878 RW 0x00FF_0414
	UINT32 reg_cdj_soft_g1_mul              :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g1_offset           :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g1_max              :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0187C RW 0x00FF_0620
	UINT32 reg_cdj_soft_g2_mul              :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g2_offset           :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g2_max              :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01880 RW 0x0001_1400
	UINT32 reg_cdj_soft_base                :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_cdj_soft_sel_1357_gain       :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_cdj_soft_single_match_en     :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O26_2KC_SHP_CDJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01890 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KC_SHP_CDB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01894 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KC_SHP_CDB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA018A0 RW 0x0000_0000
	UINT32 reg_win_cdj_win0_en              :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_cdj_win1_en              :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_cdj_win01_en             :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_cdj_win_outside          :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_cdj_win_en               :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_cdj_bdr_alpha            :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_cdj_bdr_wid              :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_cdj_bdr_en               :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_cdj_cr5                  :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_cdj_cb5                  :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_cdj_yy6                  :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_2KC_SHP_CDJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA018A4 RW 0x0000_0000
	UINT32 reg_win_cdj_win_w0_x0            :12;	//(11:0,NA,0) //Window control, win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y0            :12;	//(27:16,NA,0) //Window control, win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CDJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA018A8 RW 0x0437_077F
	UINT32 reg_win_cdj_win_w0_x1            :12;	//(11:0,NA,1919) //Window control, win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y1            :12;	//(27:16,NA,1079) //Window control, win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CDJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA018AC RW 0x0000_0000
	UINT32 reg_win_cdj_win_w1_x0            :12;	//(11:0,NA,0) //Window control, win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y0            :12;	//(27:16,NA,0) //Window control, win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CDJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA018B0 RW 0x0437_077F
	UINT32 reg_win_cdj_win_w1_x1            :12;	//(11:0,NA,1919) //Window control, win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y1            :12;	//(27:16,NA,1079) //Window control, win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CDJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01A00 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01A04 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01A08 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01A0C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter 4K Last = 2160
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter 4K Last = 2160
	UINT32 resvd1                           :4;
	};
}PE_O26_2KC_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01A10 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_2KC_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01A14 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_2KC_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01AF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KC_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01AF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KC_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01AF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KC_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA01AFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_2KC_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O26_2KC_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCCA01400
	PE_O26_2KC_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCCA01404
	PE_O26_2KC_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCCA01408
	PE_O26_2KC_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCCA0140C
	UINT32                                                   reserved0;	//0xCCA01410
	UINT32                                                   reserved1;	//0xCCA01414
	UINT32                                                   reserved2;	//0xCCA01418
	UINT32                                                   reserved3;	//0xCCA0141C
	UINT32                                                   reserved4;	//0xCCA01420
	UINT32                                                   reserved5;	//0xCCA01424
	UINT32                                                   reserved6;	//0xCCA01428
	UINT32                                                   reserved7;	//0xCCA0142C
	UINT32                                                   reserved8;	//0xCCA01430
	UINT32                                                   reserved9;	//0xCCA01434
	UINT32                                                  reserved10;	//0xCCA01438
	UINT32                                                  reserved11;	//0xCCA0143C
	UINT32                                                  reserved12;	//0xCCA01440
	UINT32                                                  reserved13;	//0xCCA01444
	UINT32                                                  reserved14;	//0xCCA01448
	UINT32                                                  reserved15;	//0xCCA0144C
	UINT32                                                  reserved16;	//0xCCA01450
	UINT32                                                  reserved17;	//0xCCA01454
	UINT32                                                  reserved18;	//0xCCA01458
	UINT32                                                  reserved19;	//0xCCA0145C
	UINT32                                                  reserved20;	//0xCCA01460
	UINT32                                                  reserved21;	//0xCCA01464
	UINT32                                                  reserved22;	//0xCCA01468
	UINT32                                                  reserved23;	//0xCCA0146C
	UINT32                                                  reserved24;	//0xCCA01470
	UINT32                                                  reserved25;	//0xCCA01474
	UINT32                                                  reserved26;	//0xCCA01478
	UINT32                                                  reserved27;	//0xCCA0147C
	UINT32                                                  reserved28;	//0xCCA01480
	UINT32                                                  reserved29;	//0xCCA01484
	UINT32                                                  reserved30;	//0xCCA01488
	UINT32                                                  reserved31;	//0xCCA0148C
	UINT32                                                  reserved32;	//0xCCA01490
	UINT32                                                  reserved33;	//0xCCA01494
	UINT32                                                  reserved34;	//0xCCA01498
	UINT32                                                  reserved35;	//0xCCA0149C
	UINT32                                                  reserved36;	//0xCCA014A0
	UINT32                                                  reserved37;	//0xCCA014A4
	UINT32                                                  reserved38;	//0xCCA014A8
	UINT32                                                  reserved39;	//0xCCA014AC
	UINT32                                                  reserved40;	//0xCCA014B0
	UINT32                                                  reserved41;	//0xCCA014B4
	UINT32                                                  reserved42;	//0xCCA014B8
	UINT32                                                  reserved43;	//0xCCA014BC
	UINT32                                                  reserved44;	//0xCCA014C0
	UINT32                                                  reserved45;	//0xCCA014C4
	UINT32                                                  reserved46;	//0xCCA014C8
	UINT32                                                  reserved47;	//0xCCA014CC
	UINT32                                                  reserved48;	//0xCCA014D0
	UINT32                                                  reserved49;	//0xCCA014D4
	UINT32                                                  reserved50;	//0xCCA014D8
	UINT32                                                  reserved51;	//0xCCA014DC
	UINT32                                                  reserved52;	//0xCCA014E0
	UINT32                                                  reserved53;	//0xCCA014E4
	UINT32                                                  reserved54;	//0xCCA014E8
	UINT32                                                  reserved55;	//0xCCA014EC
	UINT32                                                  reserved56;	//0xCCA014F0
	UINT32                                                  reserved57;	//0xCCA014F4
	UINT32                                                  reserved58;	//0xCCA014F8
	UINT32                                                  reserved59;	//0xCCA014FC
	PE_O26_2KC_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCCA01500
	UINT32                                                  reserved60;	//0xCCA01504
	UINT32                                                  reserved61;	//0xCCA01508
	UINT32                                                  reserved62;	//0xCCA0150C
	UINT32                                                  reserved63;	//0xCCA01510
	UINT32                                                  reserved64;	//0xCCA01514
	UINT32                                                  reserved65;	//0xCCA01518
	UINT32                                                  reserved66;	//0xCCA0151C
	UINT32                                                  reserved67;	//0xCCA01520
	UINT32                                                  reserved68;	//0xCCA01524
	UINT32                                                  reserved69;	//0xCCA01528
	UINT32                                                  reserved70;	//0xCCA0152C
	UINT32                                                  reserved71;	//0xCCA01530
	UINT32                                                  reserved72;	//0xCCA01534
	UINT32                                                  reserved73;	//0xCCA01538
	UINT32                                                  reserved74;	//0xCCA0153C
	UINT32                                                  reserved75;	//0xCCA01540
	UINT32                                                  reserved76;	//0xCCA01544
	UINT32                                                  reserved77;	//0xCCA01548
	UINT32                                                  reserved78;	//0xCCA0154C
	UINT32                                                  reserved79;	//0xCCA01550
	UINT32                                                  reserved80;	//0xCCA01554
	UINT32                                                  reserved81;	//0xCCA01558
	UINT32                                                  reserved82;	//0xCCA0155C
	UINT32                                                  reserved83;	//0xCCA01560
	UINT32                                                  reserved84;	//0xCCA01564
	UINT32                                                  reserved85;	//0xCCA01568
	UINT32                                                  reserved86;	//0xCCA0156C
	UINT32                                                  reserved87;	//0xCCA01570
	UINT32                                                  reserved88;	//0xCCA01574
	UINT32                                                  reserved89;	//0xCCA01578
	UINT32                                                  reserved90;	//0xCCA0157C
	UINT32                                                  reserved91;	//0xCCA01580
	UINT32                                                  reserved92;	//0xCCA01584
	UINT32                                                  reserved93;	//0xCCA01588
	UINT32                                                  reserved94;	//0xCCA0158C
	UINT32                                                  reserved95;	//0xCCA01590
	UINT32                                                  reserved96;	//0xCCA01594
	UINT32                                                  reserved97;	//0xCCA01598
	UINT32                                                  reserved98;	//0xCCA0159C
	UINT32                                                  reserved99;	//0xCCA015A0
	UINT32                                                 reserved100;	//0xCCA015A4
	UINT32                                                 reserved101;	//0xCCA015A8
	UINT32                                                 reserved102;	//0xCCA015AC
	UINT32                                                 reserved103;	//0xCCA015B0
	UINT32                                                 reserved104;	//0xCCA015B4
	UINT32                                                 reserved105;	//0xCCA015B8
	UINT32                                                 reserved106;	//0xCCA015BC
	UINT32                                                 reserved107;	//0xCCA015C0
	UINT32                                                 reserved108;	//0xCCA015C4
	UINT32                                                 reserved109;	//0xCCA015C8
	UINT32                                                 reserved110;	//0xCCA015CC
	UINT32                                                 reserved111;	//0xCCA015D0
	UINT32                                                 reserved112;	//0xCCA015D4
	UINT32                                                 reserved113;	//0xCCA015D8
	UINT32                                                 reserved114;	//0xCCA015DC
	UINT32                                                 reserved115;	//0xCCA015E0
	UINT32                                                 reserved116;	//0xCCA015E4
	UINT32                                                 reserved117;	//0xCCA015E8
	UINT32                                                 reserved118;	//0xCCA015EC
	UINT32                                                 reserved119;	//0xCCA015F0
	UINT32                                                 reserved120;	//0xCCA015F4
	UINT32                                                 reserved121;	//0xCCA015F8
	UINT32                                                 reserved122;	//0xCCA015FC
	UINT32                                                 reserved123;	//0xCCA01600
	UINT32                                                 reserved124;	//0xCCA01604
	UINT32                                                 reserved125;	//0xCCA01608
	UINT32                                                 reserved126;	//0xCCA0160C
	UINT32                                                 reserved127;	//0xCCA01610
	UINT32                                                 reserved128;	//0xCCA01614
	UINT32                                                 reserved129;	//0xCCA01618
	UINT32                                                 reserved130;	//0xCCA0161C
	UINT32                                                 reserved131;	//0xCCA01620
	UINT32                                                 reserved132;	//0xCCA01624
	UINT32                                                 reserved133;	//0xCCA01628
	UINT32                                                 reserved134;	//0xCCA0162C
	UINT32                                                 reserved135;	//0xCCA01630
	UINT32                                                 reserved136;	//0xCCA01634
	UINT32                                                 reserved137;	//0xCCA01638
	UINT32                                                 reserved138;	//0xCCA0163C
	UINT32                                                 reserved139;	//0xCCA01640
	UINT32                                                 reserved140;	//0xCCA01644
	UINT32                                                 reserved141;	//0xCCA01648
	UINT32                                                 reserved142;	//0xCCA0164C
	UINT32                                                 reserved143;	//0xCCA01650
	UINT32                                                 reserved144;	//0xCCA01654
	UINT32                                                 reserved145;	//0xCCA01658
	UINT32                                                 reserved146;	//0xCCA0165C
	UINT32                                                 reserved147;	//0xCCA01660
	UINT32                                                 reserved148;	//0xCCA01664
	UINT32                                                 reserved149;	//0xCCA01668
	UINT32                                                 reserved150;	//0xCCA0166C
	UINT32                                                 reserved151;	//0xCCA01670
	UINT32                                                 reserved152;	//0xCCA01674
	UINT32                                                 reserved153;	//0xCCA01678
	UINT32                                                 reserved154;	//0xCCA0167C
	UINT32                                                 reserved155;	//0xCCA01680
	UINT32                                                 reserved156;	//0xCCA01684
	UINT32                                                 reserved157;	//0xCCA01688
	UINT32                                                 reserved158;	//0xCCA0168C
	UINT32                                                 reserved159;	//0xCCA01690
	UINT32                                                 reserved160;	//0xCCA01694
	UINT32                                                 reserved161;	//0xCCA01698
	UINT32                                                 reserved162;	//0xCCA0169C
	UINT32                                                 reserved163;	//0xCCA016A0
	UINT32                                                 reserved164;	//0xCCA016A4
	UINT32                                                 reserved165;	//0xCCA016A8
	UINT32                                                 reserved166;	//0xCCA016AC
	UINT32                                                 reserved167;	//0xCCA016B0
	UINT32                                                 reserved168;	//0xCCA016B4
	UINT32                                                 reserved169;	//0xCCA016B8
	UINT32                                                 reserved170;	//0xCCA016BC
	UINT32                                                 reserved171;	//0xCCA016C0
	UINT32                                                 reserved172;	//0xCCA016C4
	UINT32                                                 reserved173;	//0xCCA016C8
	UINT32                                                 reserved174;	//0xCCA016CC
	UINT32                                                 reserved175;	//0xCCA016D0
	UINT32                                                 reserved176;	//0xCCA016D4
	UINT32                                                 reserved177;	//0xCCA016D8
	UINT32                                                 reserved178;	//0xCCA016DC
	UINT32                                                 reserved179;	//0xCCA016E0
	UINT32                                                 reserved180;	//0xCCA016E4
	UINT32                                                 reserved181;	//0xCCA016E8
	UINT32                                                 reserved182;	//0xCCA016EC
	UINT32                                                 reserved183;	//0xCCA016F0
	UINT32                                                 reserved184;	//0xCCA016F4
	UINT32                                                 reserved185;	//0xCCA016F8
	UINT32                                                 reserved186;	//0xCCA016FC
	UINT32                                                 reserved187;	//0xCCA01700
	UINT32                                                 reserved188;	//0xCCA01704
	UINT32                                                 reserved189;	//0xCCA01708
	UINT32                                                 reserved190;	//0xCCA0170C
	UINT32                                                 reserved191;	//0xCCA01710
	UINT32                                                 reserved192;	//0xCCA01714
	UINT32                                                 reserved193;	//0xCCA01718
	UINT32                                                 reserved194;	//0xCCA0171C
	UINT32                                                 reserved195;	//0xCCA01720
	UINT32                                                 reserved196;	//0xCCA01724
	UINT32                                                 reserved197;	//0xCCA01728
	UINT32                                                 reserved198;	//0xCCA0172C
	UINT32                                                 reserved199;	//0xCCA01730
	UINT32                                                 reserved200;	//0xCCA01734
	UINT32                                                 reserved201;	//0xCCA01738
	UINT32                                                 reserved202;	//0xCCA0173C
	UINT32                                                 reserved203;	//0xCCA01740
	UINT32                                                 reserved204;	//0xCCA01744
	UINT32                                                 reserved205;	//0xCCA01748
	UINT32                                                 reserved206;	//0xCCA0174C
	UINT32                                                 reserved207;	//0xCCA01750
	UINT32                                                 reserved208;	//0xCCA01754
	UINT32                                                 reserved209;	//0xCCA01758
	UINT32                                                 reserved210;	//0xCCA0175C
	UINT32                                                 reserved211;	//0xCCA01760
	UINT32                                                 reserved212;	//0xCCA01764
	UINT32                                                 reserved213;	//0xCCA01768
	UINT32                                                 reserved214;	//0xCCA0176C
	UINT32                                                 reserved215;	//0xCCA01770
	UINT32                                                 reserved216;	//0xCCA01774
	UINT32                                                 reserved217;	//0xCCA01778
	UINT32                                                 reserved218;	//0xCCA0177C
	UINT32                                                 reserved219;	//0xCCA01780
	UINT32                                                 reserved220;	//0xCCA01784
	UINT32                                                 reserved221;	//0xCCA01788
	UINT32                                                 reserved222;	//0xCCA0178C
	UINT32                                                 reserved223;	//0xCCA01790
	UINT32                                                 reserved224;	//0xCCA01794
	UINT32                                                 reserved225;	//0xCCA01798
	UINT32                                                 reserved226;	//0xCCA0179C
	UINT32                                                 reserved227;	//0xCCA017A0
	UINT32                                                 reserved228;	//0xCCA017A4
	UINT32                                                 reserved229;	//0xCCA017A8
	UINT32                                                 reserved230;	//0xCCA017AC
	UINT32                                                 reserved231;	//0xCCA017B0
	UINT32                                                 reserved232;	//0xCCA017B4
	UINT32                                                 reserved233;	//0xCCA017B8
	UINT32                                                 reserved234;	//0xCCA017BC
	UINT32                                                 reserved235;	//0xCCA017C0
	UINT32                                                 reserved236;	//0xCCA017C4
	UINT32                                                 reserved237;	//0xCCA017C8
	UINT32                                                 reserved238;	//0xCCA017CC
	UINT32                                                 reserved239;	//0xCCA017D0
	UINT32                                                 reserved240;	//0xCCA017D4
	UINT32                                                 reserved241;	//0xCCA017D8
	UINT32                                                 reserved242;	//0xCCA017DC
	UINT32                                                 reserved243;	//0xCCA017E0
	UINT32                                                 reserved244;	//0xCCA017E4
	UINT32                                                 reserved245;	//0xCCA017E8
	UINT32                                                 reserved246;	//0xCCA017EC
	UINT32                                                 reserved247;	//0xCCA017F0
	UINT32                                                 reserved248;	//0xCCA017F4
	UINT32                                                 reserved249;	//0xCCA017F8
	UINT32                                                 reserved250;	//0xCCA017FC
	PE_O26_2KC_SHP_CDJ_CTRL_00_T                       shp_cdj_ctrl_00;	//0xCCA01800
	PE_O26_2KC_SHP_CDJ_CTRL_01_T                       shp_cdj_ctrl_01;	//0xCCA01804
	PE_O26_2KC_SHP_CDJ_CTRL_02_T                       shp_cdj_ctrl_02;	//0xCCA01808
	PE_O26_2KC_SHP_CDJ_CTRL_03_T                       shp_cdj_ctrl_03;	//0xCCA0180C
	PE_O26_2KC_SHP_CDJ_CTRL_04_T                       shp_cdj_ctrl_04;	//0xCCA01810
	PE_O26_2KC_SHP_CDJ_CTRL_05_T                       shp_cdj_ctrl_05;	//0xCCA01814
	PE_O26_2KC_SHP_CDJ_CTRL_06_T                       shp_cdj_ctrl_06;	//0xCCA01818
	PE_O26_2KC_SHP_CDJ_CTRL_07_T                       shp_cdj_ctrl_07;	//0xCCA0181C
	PE_O26_2KC_SHP_CDJ_CTRL_08_T                       shp_cdj_ctrl_08;	//0xCCA01820
	PE_O26_2KC_SHP_CDJ_CTRL_09_T                       shp_cdj_ctrl_09;	//0xCCA01824
	PE_O26_2KC_SHP_CDJ_CTRL_0A_T                       shp_cdj_ctrl_0a;	//0xCCA01828
	PE_O26_2KC_SHP_CDJ_CTRL_0B_T                       shp_cdj_ctrl_0b;	//0xCCA0182C
	PE_O26_2KC_SHP_CDJ_CTRL_0C_T                       shp_cdj_ctrl_0c;	//0xCCA01830
	PE_O26_2KC_SHP_CDJ_CTRL_0D_T                       shp_cdj_ctrl_0d;	//0xCCA01834
	PE_O26_2KC_SHP_CDJ_CTRL_0E_T                       shp_cdj_ctrl_0e;	//0xCCA01838
	PE_O26_2KC_SHP_CDJ_CTRL_0F_T                       shp_cdj_ctrl_0f;	//0xCCA0183C
	PE_O26_2KC_SHP_CDJ_CTRL_10_T                       shp_cdj_ctrl_10;	//0xCCA01840
	PE_O26_2KC_SHP_CDJ_CTRL_11_T                       shp_cdj_ctrl_11;	//0xCCA01844
	PE_O26_2KC_SHP_CDJ_CTRL_12_T                       shp_cdj_ctrl_12;	//0xCCA01848
	PE_O26_2KC_SHP_CDJ_CTRL_13_T                       shp_cdj_ctrl_13;	//0xCCA0184C
	PE_O26_2KC_SHP_CDJ_CTRL_14_T                       shp_cdj_ctrl_14;	//0xCCA01850
	PE_O26_2KC_SHP_CDJ_CTRL_15_T                       shp_cdj_ctrl_15;	//0xCCA01854
	PE_O26_2KC_SHP_CDJ_CTRL_16_T                       shp_cdj_ctrl_16;	//0xCCA01858
	PE_O26_2KC_SHP_CDJ_CTRL_17_T                       shp_cdj_ctrl_17;	//0xCCA0185C
	PE_O26_2KC_SHP_CDJ_CTRL_18_T                       shp_cdj_ctrl_18;	//0xCCA01860
	PE_O26_2KC_SHP_CDJ_CTRL_19_T                       shp_cdj_ctrl_19;	//0xCCA01864
	PE_O26_2KC_SHP_CDJ_CTRL_1A_T                       shp_cdj_ctrl_1a;	//0xCCA01868
	PE_O26_2KC_SHP_CDJ_CTRL_1B_T                       shp_cdj_ctrl_1b;	//0xCCA0186C
	PE_O26_2KC_SHP_CDJ_CTRL_1C_T                       shp_cdj_ctrl_1c;	//0xCCA01870
	PE_O26_2KC_SHP_CDJ_CTRL_1D_T                       shp_cdj_ctrl_1d;	//0xCCA01874
	PE_O26_2KC_SHP_CDJ_CTRL_1E_T                       shp_cdj_ctrl_1e;	//0xCCA01878
	PE_O26_2KC_SHP_CDJ_CTRL_1F_T                       shp_cdj_ctrl_1f;	//0xCCA0187C
	PE_O26_2KC_SHP_CDJ_CTRL_20_T                       shp_cdj_ctrl_20;	//0xCCA01880
	UINT32                                                 reserved251;	//0xCCA01884
	UINT32                                                 reserved252;	//0xCCA01888
	UINT32                                                 reserved253;	//0xCCA0188C
	PE_O26_2KC_SHP_CDB_CTRL_00_T                       shp_cdb_ctrl_00;	//0xCCA01890
	PE_O26_2KC_SHP_CDB_CTRL_01_T                       shp_cdb_ctrl_01;	//0xCCA01894
	UINT32                                                 reserved254;	//0xCCA01898
	UINT32                                                 reserved255;	//0xCCA0189C
	PE_O26_2KC_SHP_CDJ_WIN_CTRL_00_T               shp_cdj_win_ctrl_00;	//0xCCA018A0
	PE_O26_2KC_SHP_CDJ_WIN_CTRL_01_T               shp_cdj_win_ctrl_01;	//0xCCA018A4
	PE_O26_2KC_SHP_CDJ_WIN_CTRL_02_T               shp_cdj_win_ctrl_02;	//0xCCA018A8
	PE_O26_2KC_SHP_CDJ_WIN_CTRL_03_T               shp_cdj_win_ctrl_03;	//0xCCA018AC
	PE_O26_2KC_SHP_CDJ_WIN_CTRL_04_T               shp_cdj_win_ctrl_04;	//0xCCA018B0
	UINT32                                                 reserved256;	//0xCCA018B4
	UINT32                                                 reserved257;	//0xCCA018B8
	UINT32                                                 reserved258;	//0xCCA018BC
	UINT32                                                 reserved259;	//0xCCA018C0
	UINT32                                                 reserved260;	//0xCCA018C4
	UINT32                                                 reserved261;	//0xCCA018C8
	UINT32                                                 reserved262;	//0xCCA018CC
	UINT32                                                 reserved263;	//0xCCA018D0
	UINT32                                                 reserved264;	//0xCCA018D4
	UINT32                                                 reserved265;	//0xCCA018D8
	UINT32                                                 reserved266;	//0xCCA018DC
	UINT32                                                 reserved267;	//0xCCA018E0
	UINT32                                                 reserved268;	//0xCCA018E4
	UINT32                                                 reserved269;	//0xCCA018E8
	UINT32                                                 reserved270;	//0xCCA018EC
	UINT32                                                 reserved271;	//0xCCA018F0
	UINT32                                                 reserved272;	//0xCCA018F4
	UINT32                                                 reserved273;	//0xCCA018F8
	UINT32                                                 reserved274;	//0xCCA018FC
	UINT32                                                 reserved275;	//0xCCA01900
	UINT32                                                 reserved276;	//0xCCA01904
	UINT32                                                 reserved277;	//0xCCA01908
	UINT32                                                 reserved278;	//0xCCA0190C
	UINT32                                                 reserved279;	//0xCCA01910
	UINT32                                                 reserved280;	//0xCCA01914
	UINT32                                                 reserved281;	//0xCCA01918
	UINT32                                                 reserved282;	//0xCCA0191C
	UINT32                                                 reserved283;	//0xCCA01920
	UINT32                                                 reserved284;	//0xCCA01924
	UINT32                                                 reserved285;	//0xCCA01928
	UINT32                                                 reserved286;	//0xCCA0192C
	UINT32                                                 reserved287;	//0xCCA01930
	UINT32                                                 reserved288;	//0xCCA01934
	UINT32                                                 reserved289;	//0xCCA01938
	UINT32                                                 reserved290;	//0xCCA0193C
	UINT32                                                 reserved291;	//0xCCA01940
	UINT32                                                 reserved292;	//0xCCA01944
	UINT32                                                 reserved293;	//0xCCA01948
	UINT32                                                 reserved294;	//0xCCA0194C
	UINT32                                                 reserved295;	//0xCCA01950
	UINT32                                                 reserved296;	//0xCCA01954
	UINT32                                                 reserved297;	//0xCCA01958
	UINT32                                                 reserved298;	//0xCCA0195C
	UINT32                                                 reserved299;	//0xCCA01960
	UINT32                                                 reserved300;	//0xCCA01964
	UINT32                                                 reserved301;	//0xCCA01968
	UINT32                                                 reserved302;	//0xCCA0196C
	UINT32                                                 reserved303;	//0xCCA01970
	UINT32                                                 reserved304;	//0xCCA01974
	UINT32                                                 reserved305;	//0xCCA01978
	UINT32                                                 reserved306;	//0xCCA0197C
	UINT32                                                 reserved307;	//0xCCA01980
	UINT32                                                 reserved308;	//0xCCA01984
	UINT32                                                 reserved309;	//0xCCA01988
	UINT32                                                 reserved310;	//0xCCA0198C
	UINT32                                                 reserved311;	//0xCCA01990
	UINT32                                                 reserved312;	//0xCCA01994
	UINT32                                                 reserved313;	//0xCCA01998
	UINT32                                                 reserved314;	//0xCCA0199C
	UINT32                                                 reserved315;	//0xCCA019A0
	UINT32                                                 reserved316;	//0xCCA019A4
	UINT32                                                 reserved317;	//0xCCA019A8
	UINT32                                                 reserved318;	//0xCCA019AC
	UINT32                                                 reserved319;	//0xCCA019B0
	UINT32                                                 reserved320;	//0xCCA019B4
	UINT32                                                 reserved321;	//0xCCA019B8
	UINT32                                                 reserved322;	//0xCCA019BC
	UINT32                                                 reserved323;	//0xCCA019C0
	UINT32                                                 reserved324;	//0xCCA019C4
	UINT32                                                 reserved325;	//0xCCA019C8
	UINT32                                                 reserved326;	//0xCCA019CC
	UINT32                                                 reserved327;	//0xCCA019D0
	UINT32                                                 reserved328;	//0xCCA019D4
	UINT32                                                 reserved329;	//0xCCA019D8
	UINT32                                                 reserved330;	//0xCCA019DC
	UINT32                                                 reserved331;	//0xCCA019E0
	UINT32                                                 reserved332;	//0xCCA019E4
	UINT32                                                 reserved333;	//0xCCA019E8
	UINT32                                                 reserved334;	//0xCCA019EC
	UINT32                                                 reserved335;	//0xCCA019F0
	UINT32                                                 reserved336;	//0xCCA019F4
	UINT32                                                 reserved337;	//0xCCA019F8
	UINT32                                                 reserved338;	//0xCCA019FC
	PE_O26_2KC_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCCA01A00
	PE_O26_2KC_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCCA01A04
	PE_O26_2KC_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCCA01A08
	PE_O26_2KC_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCCA01A0C
	PE_O26_2KC_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCCA01A10
	PE_O26_2KC_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCCA01A14
	UINT32                                                 reserved339;	//0xCCA01A18
	UINT32                                                 reserved340;	//0xCCA01A1C
	UINT32                                                 reserved341;	//0xCCA01A20
	UINT32                                                 reserved342;	//0xCCA01A24
	UINT32                                                 reserved343;	//0xCCA01A28
	UINT32                                                 reserved344;	//0xCCA01A2C
	UINT32                                                 reserved345;	//0xCCA01A30
	UINT32                                                 reserved346;	//0xCCA01A34
	UINT32                                                 reserved347;	//0xCCA01A38
	UINT32                                                 reserved348;	//0xCCA01A3C
	UINT32                                                 reserved349;	//0xCCA01A40
	UINT32                                                 reserved350;	//0xCCA01A44
	UINT32                                                 reserved351;	//0xCCA01A48
	UINT32                                                 reserved352;	//0xCCA01A4C
	UINT32                                                 reserved353;	//0xCCA01A50
	UINT32                                                 reserved354;	//0xCCA01A54
	UINT32                                                 reserved355;	//0xCCA01A58
	UINT32                                                 reserved356;	//0xCCA01A5C
	UINT32                                                 reserved357;	//0xCCA01A60
	UINT32                                                 reserved358;	//0xCCA01A64
	UINT32                                                 reserved359;	//0xCCA01A68
	UINT32                                                 reserved360;	//0xCCA01A6C
	UINT32                                                 reserved361;	//0xCCA01A70
	UINT32                                                 reserved362;	//0xCCA01A74
	UINT32                                                 reserved363;	//0xCCA01A78
	UINT32                                                 reserved364;	//0xCCA01A7C
	UINT32                                                 reserved365;	//0xCCA01A80
	UINT32                                                 reserved366;	//0xCCA01A84
	UINT32                                                 reserved367;	//0xCCA01A88
	UINT32                                                 reserved368;	//0xCCA01A8C
	UINT32                                                 reserved369;	//0xCCA01A90
	UINT32                                                 reserved370;	//0xCCA01A94
	UINT32                                                 reserved371;	//0xCCA01A98
	UINT32                                                 reserved372;	//0xCCA01A9C
	UINT32                                                 reserved373;	//0xCCA01AA0
	UINT32                                                 reserved374;	//0xCCA01AA4
	UINT32                                                 reserved375;	//0xCCA01AA8
	UINT32                                                 reserved376;	//0xCCA01AAC
	UINT32                                                 reserved377;	//0xCCA01AB0
	UINT32                                                 reserved378;	//0xCCA01AB4
	UINT32                                                 reserved379;	//0xCCA01AB8
	UINT32                                                 reserved380;	//0xCCA01ABC
	UINT32                                                 reserved381;	//0xCCA01AC0
	UINT32                                                 reserved382;	//0xCCA01AC4
	UINT32                                                 reserved383;	//0xCCA01AC8
	UINT32                                                 reserved384;	//0xCCA01ACC
	UINT32                                                 reserved385;	//0xCCA01AD0
	UINT32                                                 reserved386;	//0xCCA01AD4
	UINT32                                                 reserved387;	//0xCCA01AD8
	UINT32                                                 reserved388;	//0xCCA01ADC
	UINT32                                                 reserved389;	//0xCCA01AE0
	UINT32                                                 reserved390;	//0xCCA01AE4
	UINT32                                                 reserved391;	//0xCCA01AE8
	UINT32                                                 reserved392;	//0xCCA01AEC
	PE_O26_2KC_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCCA01AF0
	PE_O26_2KC_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCCA01AF4
	PE_O26_2KC_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCCA01AF8
	PE_O26_2KC_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCCA01AFC
}PE_SR_2K_SHC_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A00 RW 0x0800_ff00
	UINT32 reg_sr_merge_en                  :1;	//(0:0,NA,0) //0 : core bypass	1 : SR_MERGE enable
	UINT32 resvd0                           :3;
	UINT32 reg_sr_merge_demo_mode_en        :1;	//(4:4,NA,0) //0 : demo mode off	1 : demo mode on
	UINT32 reg_sr_merge_demo_mode           :1;	//(5:5,NA,0) //0 : inside window - SR 	1 : outsie window - SR
	UINT32 resvd1                           :2;
	UINT32 reg_sr_merge_master_gain         :8;	//(15:8,NA,255) //final alpha blending weight 	255 : result = input scale-up image	0   : result = SR_MERGE blended image
	UINT32 reg_sr_merge_ti_en               :1;	//(16:16,NA,0) //0 : TI processing off 	1 : TI processing on
	UINT32 resvd2                           :11;
	UINT32 reg_sr_merge_debug_mode          :4;	//(31:28,NA,0) //0 : SR_MERGE result (default)	1 : mmd blending gain	2 : NR gain	3 : TI gain 	4 : sobel gain 	5 : input residual image	6 : (SR_MERGE output - Scale_Up image)	7 : input video image	8 : motion map	9 : ellipse gain
	};
}PE_O26_SR_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A04 RW 0x0870_0F00
	UINT32 reg_sr_merge_width               :16;	//(15:0,NA,3840) //input image width (default : 3840)
	UINT32 reg_sr_merge_height              :16;	//(31:16,NA,2160) //input image height (default : 2160)
	};
}PE_O26_SR_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A08 RW 0x0000_0000
	UINT32 reg_sr_merge_demo_start_pts_x0   :16;	//(15:0,NA,0) //window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_start_pts_y0   :16;	//(31:16,NA,0) //window start point (for demo mode)
	};
}PE_O26_SR_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A0C RW 0x007f_007f
	UINT32 reg_sr_merge_demo_end_pts_x1     :16;	//(15:0,NA,127) //window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_end_pts_y1     :16;	//(31:16,NA,127) //window end point (for demo mode)
	};
}PE_O26_SR_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A10 RW 0x0000_0000
	UINT32 reg_residual_blur_en             :1;	//(0:0,NA,0) //0 : spatial filter off - use input residual data	1 : spatial filter on - use spatial filter result
	UINT32 resvd                            :31;
	};
}PE_O26_SR_MERGE_SPATIAL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A14 RW 0x0002_4048
	UINT32 reg_residual_blur_filt_00        :4;	//(3:0,NA,8) //blur filter coefficient
	UINT32 reg_residual_blur_filt_01        :4;	//(7:4,NA,4) //blur filter coefficient
	UINT32 reg_residual_blur_filt_02        :4;	//(11:8,NA,0) //blur filter coefficient
	UINT32 reg_residual_blur_filt_10        :4;	//(15:12,NA,4) //blur filter coefficient
	UINT32 reg_residual_blur_filt_11        :4;	//(19:16,NA,2) //blur filter coefficient
	UINT32 reg_residual_blur_filt_12        :4;	//(23:20,NA,0) //blur filter coefficient
	UINT32 resvd                            :8;
	};
}PE_O26_SR_MERGE_SPATIAL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A20 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_mmd_tap_size                 :4;	//(7:4,NA,0) //mmd tap size	0 : 3x3	1 : 5x5
	UINT32 resvd1                           :24;
	};
}PE_O26_SR_MERGE_MMD_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A24 RW 0x1020_0800
	UINT32 reg_mmd_diff_lut_y0              :8;	//(7:0,NA,0) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x0              :8;	//(15:8,NA,8) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y1              :8;	//(23:16,NA,32) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x1              :8;	//(31:24,NA,16) //mmd diff lut x position
	};
}PE_O26_SR_MERGE_MMD_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A28 RW 0x3C10_2040
	UINT32 reg_mmd_diff_lut_y2              :8;	//(7:0,NA,64) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x2              :8;	//(15:8,NA,32) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y3              :8;	//(23:16,NA,16) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x3              :8;	//(31:24,NA,60) //mmd diff lut x position
	};
}PE_O26_SR_MERGE_MMD_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A2C RW 0x82FF_6EFF
	UINT32 reg_mmd_diff_lut_y4              :8;	//(7:0,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x4              :8;	//(15:8,NA,110) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y5              :8;	//(23:16,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x5              :8;	//(31:24,NA,130) //mmd diff lut x position
	};
}PE_O26_SR_MERGE_MMD_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A30 RW 0xAAFF_96FF
	UINT32 reg_mmd_diff_lut_y6              :8;	//(7:0,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x6              :8;	//(15:8,NA,150) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y7              :8;	//(23:16,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x7              :8;	//(31:24,NA,170) //mmd diff lut x position
	};
}PE_O26_SR_MERGE_MMD_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A34 RW 0x2880_14C8
	UINT32 reg_ti_gain_lut_y0               :8;	//(7:0,NA,200) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x0               :8;	//(15:8,NA,20) //ti gain lut x position
	UINT32 reg_ti_gain_lut_y1               :8;	//(23:16,NA,128) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x1               :8;	//(31:24,NA,40) //ti gain lut x position
	};
}PE_O26_SR_MERGE_MMD_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A38 RW 0xA020_5040
	UINT32 reg_ti_gain_lut_y2               :8;	//(7:0,NA,64) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x2               :8;	//(15:8,NA,80) //ti gain lut x position
	UINT32 reg_ti_gain_lut_y3               :8;	//(23:16,NA,32) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x3               :8;	//(31:24,NA,160) //ti gain lut x position
	};
}PE_O26_SR_MERGE_MMD_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A50 RW 0x0000_0003
	UINT32 reg_sobel_mode                   :4;	//(3:0,NA,3) //sobel mode selection 	0: 3x3 	1: 5x5	2: 7x7	3: (7x7 - 3x3) : (default)
	UINT32 resvd                            :28;
	};
}PE_O26_SR_MERGE_SOBEL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A54 RW 0x5014_0400
	UINT32 reg_sobel_lut_y0                 :8;	//(7:0,NA,0) //sobel lut y position
	UINT32 reg_sobel_lut_x0                 :8;	//(15:8,NA,4) //sobel lut x position
	UINT32 reg_sobel_lut_y1                 :8;	//(23:16,NA,20) //sobel lut y position
	UINT32 reg_sobel_lut_x1                 :8;	//(31:24,NA,80) //sobel lut x position
	};
}PE_O26_SR_MERGE_SOBEL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A58 RW 0xE6FF_C864
	UINT32 reg_sobel_lut_y2                 :8;	//(7:0,NA,100) //sobel lut y position
	UINT32 reg_sobel_lut_x2                 :8;	//(15:8,NA,200) //sobel lut x position
	UINT32 reg_sobel_lut_y3                 :8;	//(23:16,NA,255) //sobel lut y position
	UINT32 reg_sobel_lut_x3                 :8;	//(31:24,NA,230) //sobel lut x position
	};
}PE_O26_SR_MERGE_SOBEL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A70 RW 0x0000_0300
	UINT32 reg_nr_gain_en                   :1;	//(0:0,NA,0) //NR Gain enable
	UINT32 resvd0                           :3;
	UINT32 reg_nr_gain_th                   :10;	//(13:4,NA,48) //NR gain threshold
	UINT32 resvd1                           :18;
	};
}PE_O26_SR_MERGE_NR_GAIN_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A74 RW 0x2080_1019
	UINT32 reg_nr_gain_lut_y0               :8;	//(7:0,NA,25) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x0               :8;	//(15:8,NA,16) //nr_gain lut x position
	UINT32 reg_nr_gain_lut_y1               :8;	//(23:16,NA,128) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x1               :8;	//(31:24,NA,32) //nr_gain lut x position
	};
}PE_O26_SR_MERGE_NR_GAIN_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A78 RW 0x4000_3020
	UINT32 reg_nr_gain_lut_y2               :8;	//(7:0,NA,32) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x2               :8;	//(15:8,NA,48) //nr_gain lut x position
	UINT32 reg_nr_gain_lut_y3               :8;	//(23:16,NA,0) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x3               :8;	//(31:24,NA,64) //nr_gain lut x position
	};
}PE_O26_SR_MERGE_NR_GAIN_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A90 RW 0x0200_0021
	UINT32 reg_blend_lut_en                 :1;	//(0:0,NA,1) //blend lut en
	UINT32 resvd                            :19;
	UINT32 reg_blend_amp_weight             :12;	//(31:20,NA,32) //blend weight ('d16: x1, 'd32:x2)
	};
}PE_O26_SR_MERGE_BLEND_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A94 RW 0x0012_0012
	UINT32 reg_blend_lut_y1                 :10;	//(9:0,NA,18) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x1                 :10;	//(25:16,NA,18) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O26_SR_MERGE_BLEND_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A98 RW 0x0008_0008
	UINT32 reg_blend_lut_y0                 :10;	//(9:0,NA,8) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x0                 :10;	//(25:16,NA,8) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O26_SR_MERGE_BLEND_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02A9C RW 0x0080_0080
	UINT32 reg_blend_lut_y3                 :10;	//(9:0,NA,128) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x3                 :10;	//(25:16,NA,128) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O26_SR_MERGE_BLEND_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02AA0 RW 0x0020_0020
	UINT32 reg_blend_lut_y2                 :10;	//(9:0,NA,32) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x2                 :10;	//(25:16,NA,32) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O26_SR_MERGE_BLEND_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B00 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_MERGE_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B04 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :16;	//(15:0,NA,0) //Input vertical counter
	UINT32 reg_mon_in_hori_cnt              :16;	//(31:16,NA,0) //Input horizontal counter
	};
}PE_O26_SR_MERGE_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B08 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :16;	//(15:0,NA,0) //Output vertical counter
	UINT32 reg_mon_out_hori_cnt             :16;	//(31:16,NA,0) //Output horizontal counter
	};
}PE_O26_SR_MERGE_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B0C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :16;	//(15:0,NA,0) //Output previous frame vertical counter
	UINT32 reg_mon_fin_in_vert_cnt          :16;	//(31:16,NA,0) //Input previous frame vertical counter
	};
}PE_O26_SR_MERGE_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B10 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_SR_MERGE_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B14 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_SR_MERGE_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B20 RW 0x0000_0000
	UINT32 reg_ellipse_ctrl_en              :1;	//(0:0,NA,0x0) //0: not use ellipse gain, 1 : use ellipse gain
	UINT32 resvd0                           :3;
	UINT32 reg_sel_output                   :1;	//(4:4,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_ellipse_offset               :8;	//(15:8,NA,0x0) //
	UINT32 resvd2                           :16;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B24 RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f0_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B28 RW 0x0000_0000
	UINT32 reg_f0_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B2C RW 0x0000_0000
	UINT32 reg_f0_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f0_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f0_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B30 RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f1_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f1_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B34 RW 0x0000_0000
	UINT32 reg_f1_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B38 RW 0x0000_0000
	UINT32 reg_f1_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f1_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f1_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B3C RW 0x0000_0000
	UINT32 reg_f2_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f2_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B40 RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f2_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B44 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f2_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f2_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B48 RW 0x0000_0000
	UINT32 reg_f3_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f3_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B4C RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B50 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f3_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f3_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O26_SR_MERGE_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B54 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_MERGE_ELLIPSE_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B58 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //
	};
}PE_O26_SR_MERGE_ELLIPSE_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02B5C RW 0x0000_0000
	UINT32 reg_sm_blender_on_en             :1;	//(0:0,NA,0) //1 : motion on, 0 : motion off = output ready force 1
	UINT32 resvd0                           :3;
	UINT32 reg_sm_blender_en                :1;	//(4:4,NA,0) //1 : sm_blender output, 0, ori sr_merge_out
	UINT32 resvd1                           :27;
	};
}PE_O26_SR_MERGE_SM_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02BF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_MERGE_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02BF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_MERGE_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02BF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_MERGE_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02BFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_MERGE_FSW_CTRL_03_T;

typedef struct {
	PE_O26_SR_MERGE_CTRL_00_T                     sr_merge_ctrl_00;	//0xCCA02A00
	PE_O26_SR_MERGE_CTRL_01_T                     sr_merge_ctrl_01;	//0xCCA02A04
	PE_O26_SR_MERGE_CTRL_02_T                     sr_merge_ctrl_02;	//0xCCA02A08
	PE_O26_SR_MERGE_CTRL_03_T                     sr_merge_ctrl_03;	//0xCCA02A0C
	PE_O26_SR_MERGE_SPATIAL_00_T               sr_merge_spatial_00;	//0xCCA02A10
	PE_O26_SR_MERGE_SPATIAL_01_T               sr_merge_spatial_01;	//0xCCA02A14
	UINT32                                               reserved0;	//0xCCA02A18
	UINT32                                               reserved1;	//0xCCA02A1C
	PE_O26_SR_MERGE_MMD_00_T                       sr_merge_mmd_00;	//0xCCA02A20
	PE_O26_SR_MERGE_MMD_01_T                       sr_merge_mmd_01;	//0xCCA02A24
	PE_O26_SR_MERGE_MMD_02_T                       sr_merge_mmd_02;	//0xCCA02A28
	PE_O26_SR_MERGE_MMD_03_T                       sr_merge_mmd_03;	//0xCCA02A2C
	PE_O26_SR_MERGE_MMD_04_T                       sr_merge_mmd_04;	//0xCCA02A30
	PE_O26_SR_MERGE_MMD_05_T                       sr_merge_mmd_05;	//0xCCA02A34
	PE_O26_SR_MERGE_MMD_06_T                       sr_merge_mmd_06;	//0xCCA02A38
	UINT32                                               reserved2;	//0xCCA02A3C
	UINT32                                               reserved3;	//0xCCA02A40
	UINT32                                               reserved4;	//0xCCA02A44
	UINT32                                               reserved5;	//0xCCA02A48
	UINT32                                               reserved6;	//0xCCA02A4C
	PE_O26_SR_MERGE_SOBEL_00_T                   sr_merge_sobel_00;	//0xCCA02A50
	PE_O26_SR_MERGE_SOBEL_01_T                   sr_merge_sobel_01;	//0xCCA02A54
	PE_O26_SR_MERGE_SOBEL_02_T                   sr_merge_sobel_02;	//0xCCA02A58
	UINT32                                               reserved7;	//0xCCA02A5C
	UINT32                                               reserved8;	//0xCCA02A60
	UINT32                                               reserved9;	//0xCCA02A64
	UINT32                                              reserved10;	//0xCCA02A68
	UINT32                                              reserved11;	//0xCCA02A6C
	PE_O26_SR_MERGE_NR_GAIN_00_T               sr_merge_nr_gain_00;	//0xCCA02A70
	PE_O26_SR_MERGE_NR_GAIN_01_T               sr_merge_nr_gain_01;	//0xCCA02A74
	PE_O26_SR_MERGE_NR_GAIN_02_T               sr_merge_nr_gain_02;	//0xCCA02A78
	UINT32                                              reserved12;	//0xCCA02A7C
	UINT32                                              reserved13;	//0xCCA02A80
	UINT32                                              reserved14;	//0xCCA02A84
	UINT32                                              reserved15;	//0xCCA02A88
	UINT32                                              reserved16;	//0xCCA02A8C
	PE_O26_SR_MERGE_BLEND_00_T                   sr_merge_blend_00;	//0xCCA02A90
	PE_O26_SR_MERGE_BLEND_01_T                   sr_merge_blend_01;	//0xCCA02A94
	PE_O26_SR_MERGE_BLEND_02_T                   sr_merge_blend_02;	//0xCCA02A98
	PE_O26_SR_MERGE_BLEND_03_T                   sr_merge_blend_03;	//0xCCA02A9C
	PE_O26_SR_MERGE_BLEND_04_T                   sr_merge_blend_04;	//0xCCA02AA0
	UINT32                                              reserved17;	//0xCCA02AA4
	UINT32                                              reserved18;	//0xCCA02AA8
	UINT32                                              reserved19;	//0xCCA02AAC
	UINT32                                              reserved20;	//0xCCA02AB0
	UINT32                                              reserved21;	//0xCCA02AB4
	UINT32                                              reserved22;	//0xCCA02AB8
	UINT32                                              reserved23;	//0xCCA02ABC
	UINT32                                              reserved24;	//0xCCA02AC0
	UINT32                                              reserved25;	//0xCCA02AC4
	UINT32                                              reserved26;	//0xCCA02AC8
	UINT32                                              reserved27;	//0xCCA02ACC
	UINT32                                              reserved28;	//0xCCA02AD0
	UINT32                                              reserved29;	//0xCCA02AD4
	UINT32                                              reserved30;	//0xCCA02AD8
	UINT32                                              reserved31;	//0xCCA02ADC
	UINT32                                              reserved32;	//0xCCA02AE0
	UINT32                                              reserved33;	//0xCCA02AE4
	UINT32                                              reserved34;	//0xCCA02AE8
	UINT32                                              reserved35;	//0xCCA02AEC
	UINT32                                              reserved36;	//0xCCA02AF0
	UINT32                                              reserved37;	//0xCCA02AF4
	UINT32                                              reserved38;	//0xCCA02AF8
	UINT32                                              reserved39;	//0xCCA02AFC
	PE_O26_SR_MERGE_CORE_STAT_00_T           sr_merge_core_stat_00;	//0xCCA02B00
	PE_O26_SR_MERGE_CORE_STAT_01_T           sr_merge_core_stat_01;	//0xCCA02B04
	PE_O26_SR_MERGE_CORE_STAT_02_T           sr_merge_core_stat_02;	//0xCCA02B08
	PE_O26_SR_MERGE_CORE_STAT_03_T           sr_merge_core_stat_03;	//0xCCA02B0C
	PE_O26_SR_MERGE_CORE_STAT_04_T           sr_merge_core_stat_04;	//0xCCA02B10
	PE_O26_SR_MERGE_CORE_STAT_05_T           sr_merge_core_stat_05;	//0xCCA02B14
	UINT32                                              reserved40;	//0xCCA02B18
	UINT32                                              reserved41;	//0xCCA02B1C
	PE_O26_SR_MERGE_ELLIPSE_CTRL_00_T     sr_merge_ellipse_ctrl_00;	//0xCCA02B20
	PE_O26_SR_MERGE_ELLIPSE_CTRL_01_T     sr_merge_ellipse_ctrl_01;	//0xCCA02B24
	PE_O26_SR_MERGE_ELLIPSE_CTRL_02_T     sr_merge_ellipse_ctrl_02;	//0xCCA02B28
	PE_O26_SR_MERGE_ELLIPSE_CTRL_03_T     sr_merge_ellipse_ctrl_03;	//0xCCA02B2C
	PE_O26_SR_MERGE_ELLIPSE_CTRL_04_T     sr_merge_ellipse_ctrl_04;	//0xCCA02B30
	PE_O26_SR_MERGE_ELLIPSE_CTRL_05_T     sr_merge_ellipse_ctrl_05;	//0xCCA02B34
	PE_O26_SR_MERGE_ELLIPSE_CTRL_06_T     sr_merge_ellipse_ctrl_06;	//0xCCA02B38
	PE_O26_SR_MERGE_ELLIPSE_CTRL_07_T     sr_merge_ellipse_ctrl_07;	//0xCCA02B3C
	PE_O26_SR_MERGE_ELLIPSE_CTRL_08_T     sr_merge_ellipse_ctrl_08;	//0xCCA02B40
	PE_O26_SR_MERGE_ELLIPSE_CTRL_09_T     sr_merge_ellipse_ctrl_09;	//0xCCA02B44
	PE_O26_SR_MERGE_ELLIPSE_CTRL_10_T     sr_merge_ellipse_ctrl_10;	//0xCCA02B48
	PE_O26_SR_MERGE_ELLIPSE_CTRL_11_T     sr_merge_ellipse_ctrl_11;	//0xCCA02B4C
	PE_O26_SR_MERGE_ELLIPSE_CTRL_12_T     sr_merge_ellipse_ctrl_12;	//0xCCA02B50
	PE_O26_SR_MERGE_ELLIPSE_LUT_CTRL_00_T sr_merge_ellipse_lut_ctrl_00;	//0xCCA02B54
	PE_O26_SR_MERGE_ELLIPSE_LUT_CTRL_01_T sr_merge_ellipse_lut_ctrl_01;	//0xCCA02B58
	PE_O26_SR_MERGE_SM_BLEND_CTRL_00_T   sr_merge_sm_blend_ctrl_00;	//0xCCA02B5C
	UINT32                                              reserved42;	//0xCCA02B60
	UINT32                                              reserved43;	//0xCCA02B64
	UINT32                                              reserved44;	//0xCCA02B68
	UINT32                                              reserved45;	//0xCCA02B6C
	UINT32                                              reserved46;	//0xCCA02B70
	UINT32                                              reserved47;	//0xCCA02B74
	UINT32                                              reserved48;	//0xCCA02B78
	UINT32                                              reserved49;	//0xCCA02B7C
	UINT32                                              reserved50;	//0xCCA02B80
	UINT32                                              reserved51;	//0xCCA02B84
	UINT32                                              reserved52;	//0xCCA02B88
	UINT32                                              reserved53;	//0xCCA02B8C
	UINT32                                              reserved54;	//0xCCA02B90
	UINT32                                              reserved55;	//0xCCA02B94
	UINT32                                              reserved56;	//0xCCA02B98
	UINT32                                              reserved57;	//0xCCA02B9C
	UINT32                                              reserved58;	//0xCCA02BA0
	UINT32                                              reserved59;	//0xCCA02BA4
	UINT32                                              reserved60;	//0xCCA02BA8
	UINT32                                              reserved61;	//0xCCA02BAC
	UINT32                                              reserved62;	//0xCCA02BB0
	UINT32                                              reserved63;	//0xCCA02BB4
	UINT32                                              reserved64;	//0xCCA02BB8
	UINT32                                              reserved65;	//0xCCA02BBC
	UINT32                                              reserved66;	//0xCCA02BC0
	UINT32                                              reserved67;	//0xCCA02BC4
	UINT32                                              reserved68;	//0xCCA02BC8
	UINT32                                              reserved69;	//0xCCA02BCC
	UINT32                                              reserved70;	//0xCCA02BD0
	UINT32                                              reserved71;	//0xCCA02BD4
	UINT32                                              reserved72;	//0xCCA02BD8
	UINT32                                              reserved73;	//0xCCA02BDC
	UINT32                                              reserved74;	//0xCCA02BE0
	UINT32                                              reserved75;	//0xCCA02BE4
	UINT32                                              reserved76;	//0xCCA02BE8
	UINT32                                              reserved77;	//0xCCA02BEC
	PE_O26_SR_MERGE_FSW_CTRL_00_T             sr_merge_fsw_ctrl_00;	//0xCCA02BF0
	PE_O26_SR_MERGE_FSW_CTRL_01_T             sr_merge_fsw_ctrl_01;	//0xCCA02BF4
	PE_O26_SR_MERGE_FSW_CTRL_02_T             sr_merge_fsw_ctrl_02;	//0xCCA02BF8
	PE_O26_SR_MERGE_FSW_CTRL_03_T             sr_merge_fsw_ctrl_03;	//0xCCA02BFC
}PE_SR_MERG_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02800 RW 0x2600_0000
	UINT32 resvd                            :24;
	UINT32 reg_preproc_mask_off             :1;	//(24:24,NA,0) //1 : sr_merge/sr_blend preproc done??Í≥†Î†§?òÏ? ?äÏùå.; 0 : sr_merge/sr_blend preproc done??Í≥†Î†§?òÏó¨, ready/valid masking
	UINT32 reg_lm7_detour                   :1;	//(25:25,NA,1) //1 : lm7 detour
	UINT32 reg_lm3_detour                   :1;	//(26:26,NA,1) //1 : lm3 detour
	UINT32 reg_subuf_detour                 :1;	//(27:27,NA,0) //1 : su buffer detour
	UINT32 reg_sr_blend_detour              :1;	//(28:28,NA,0) //1 : sr_blend detour
	UINT32 reg_sr_merge_detour              :1;	//(29:29,NA,1) //1 : sr_merge detour
	UINT32 reg_motion_path_en               :1;	//(30:30,NA,0) //1 : motion path on, ; 0 : motion path off = output ready force 1; ; -> sr_merge (lagacy) ?¨Ïö©?? Í¥Ä???àÏ??§ÌÑ∞???ôÏùº?òÍ≤å ?§Ï†ï?¥Ïïº ?? (0x015c register)
	UINT32 reg_sr_merge_mode_sel            :1;	//(31:31,NA,0x0) //1: Lagacy mode (SR_MERGE
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02804 RW 0x0f00_0870
	UINT32 reg_sr_merge_top_height          :16;	//(15:0,NA,2160) //input image height (default : 2160); -> lagacy ?ôÏûë ?úÌÇ§?îÎùº?? Íº??§Ï†ï??Í≤?(
	UINT32 reg_sr_merge_top_width           :16;	//(31:16,NA,3840) //input image width (default : 3840); -> lagacy ?ôÏûë ?úÌÇ§?îÎùº?? Íº??§Ï†ï??Í≤?(
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02808 RW 0x0000_0000
	UINT32 reg_su_i_pat_dat                 :10;	//(9:0,NA,0x0) //forcing???∞Ïù¥??Í∞?; pat_dat_f?Ä ?®Íªò ?¨Ïö©?¥Ïïº ??
	UINT32 reg_su_i_pat_dat_f               :1;	//(10:10,NA,0x0) //1 : patttern data forcing
	UINT32 reg_su_i_pat_en                  :1;	//(11:11,NA,0x0) //1 : pattern gen enable (horizontal gradation)
	UINT32 reg_su_i_val_gen                 :1;	//(12:12,NA,0x0) //0 : input valid ; 1 : ?ùÏÑ±??valid ?¨Ïö© / pattern data?Ä ?ïÏÉÅÏ∂úÎ†• Í∞Ä??
	UINT32 resvd0                           :3;
	UINT32 reg_blend_o_pat_dat              :10;	//(25:16,NA,0x0) //forcing???∞Ïù¥??Í∞?; pat_dat_f?Ä ?®Íªò ?¨Ïö©?¥Ïïº ??
	UINT32 reg_blend_o_pat_dat_f            :1;	//(26:26,NA,0x0) //1 : patttern data forcing
	UINT32 reg_blend_o_pat_en               :1;	//(27:27,NA,0x0) //1 : pattern gen enable (horizontal gradation)
	UINT32 reg_blend_o_val_gen              :1;	//(28:28,NA,0x0) //0 : input valid ; 1 : ?ùÏÑ±??valid ?¨Ïö© / pattern data?Ä ?ïÏÉÅÏ∂úÎ†• Í∞Ä??
	UINT32 resvd1                           :3;
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_PAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0280C RW 0x0000_0000
	UINT32 reg_resi_e_i_pat_dat             :11;	//(10:0,NA,0x0) //forcing???∞Ïù¥??Í∞?; pat_dat_f?Ä ?®Íªò ?¨Ïö©?¥Ïïº ??
	UINT32 reg_resi_e_i_pat_dat_f           :1;	//(11:11,NA,0x0) //1 : patttern data forcing
	UINT32 reg_resi_e_i_pat_en              :1;	//(12:12,NA,0x0) //1 : pattern gen enable (horizontal gradation)
	UINT32 reg_resi_e_i_val_gen             :1;	//(13:13,NA,0x0) //0 : input valid ; 1 : ?ùÏÑ±??valid ?¨Ïö© / pattern data?Ä ?ïÏÉÅÏ∂úÎ†• Í∞Ä??
	UINT32 resvd0                           :2;
	UINT32 reg_resi_t_i_pat_dat             :11;	//(26:16,NA,0x0) //forcing???∞Ïù¥??Í∞?; pat_dat_f?Ä ?®Íªò ?¨Ïö©?¥Ïïº ??
	UINT32 reg_resi_t_i_pat_dat_f           :1;	//(27:27,NA,0x0) //1 : patttern data forcing
	UINT32 reg_resi_t_i_pat_en              :1;	//(28:28,NA,0x0) //1 : pattern gen enable (horizontal gradation)
	UINT32 reg_resi_t_i_val_gen             :1;	//(29:29,NA,0x0) //0 : input valid ; 1 : ?ùÏÑ±??valid ?¨Ïö© / pattern data?Ä ?ïÏÉÅÏ∂úÎ†• Í∞Ä??
	UINT32 resvd1                           :2;
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_PAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02810 RW 0x0000_0000
	UINT32 reg_sr_blend_debug_mode_sel      :3;	//(2:0,NA,0x0) //0 : SR_BLEND output ; -- debug_mode_sel = 0??Í≤ΩÏö∞, sr_alpha_dbg_en, blend_force_mode ?ÅÏö© Í∞Ä?? ; 1 : lm4 out (line0, texture); 2 : lm4 out (line0, edge); 3 : 3x3blur out (edge); 4 : 3x3blur out (texture); 5 : pre-alpha out (center)/ 1x3 alpha feeder output; 6 : final alpha (reg_alpha_blur_mode, reg_alpha_blend_sel???∞Îùº Ï∂úÎ†•?òÎäî Í∞íÏù¥ ?¨ÎùºÏß????àÏùå)
	UINT32 reg_dual_sr_alpha_dbg_en         :1;	//(3:3,NA,0x0) //ÏµúÏ¢Ö Ï∂úÎ†•?®Ïóê???úÎ≤à ???†ÌÉùÍ∞Ä??: alpha_blend_post.v; ; 0 : debug display off ; 1 : debug display on ; -- blend Í≤∞Í≥º ?Ä?? alpha Í∞íÏù¥ Ï∂úÎ†•??
	UINT32 reg_dual_sr_img_dbg_mode         :3;	//(6:4,NA,0x0) //reg_dual_sr_img_dbg_en = 1??Í≤ΩÏö∞, ?¨Ïö©Í∞Ä??; ; 0 : residual (input) Ï∂úÎ†• ; 1 : delta final gain; 2 : face map (input) ; 3 : face gain; 4 : luma gain positive; 5 : luma gain negative; 6 : motion map (input); 7 : motion gain
	UINT32 reg_dual_sr_img_dbg_en           :1;	//(7:7,NA,0x0) //genband ?¥Ï†Ñ debug mode ?†ÌÉù : fm_gain.v; 0 : debug display off ; 1 : debug display on
	UINT32 resvd0                           :18;
	UINT32 reg_sr_blend_force_mode          :2;	//(27:26,NA,0x0) //reg_dual_sr_alpha_dbg_en = 0 ??Í≤ΩÏö∞, ?¨Ïö©; ; 0: blend output ; 1: edge force; 2: texture force; ; -> ÏµúÏ¢Ö Ï∂úÎ†•??3Í∞ÄÏßÄ Ï§??òÎÇòÎ°??¥Î≥¥??
	UINT32 reg_sr_blend_lm4_sram_Off        :1;	//(28:28,NA,0x0) //1: lm4 SRAM OFF (Only use single mode); - SR_Blend?êÏÑú single mode ?ºÎïåÎß??¨Ïö© Í∞Ä?? ; - single model??Í≤ΩÏö∞, SRAM?ºÎ°ú Í∞Ä??WE,ME??0?ºÎ°ú tie?òÏó¨ SRAM???ôÏûë?òÏ? ?äÍ≤å ??
	UINT32 reg_sr_blend_tSR_Resi_forcing0   :1;	//(29:29,NA,0x0) //(reg_sr_blend_type_sel); ; 1: single blend mode (edge residual, scaled-up image); -> tsr = texture residual ; -> forcing0 = 0 Í∞íÏúºÎ°?forcing (to core); -> texture residual Í∞íÏù¥ 0?ºÎ°ú ?ÖÎ†•?? ; 0: dual blend mode (edge residual, texture residual, scaled-up image)
	UINT32 resvd1                           :1;
	UINT32 reg_sr_blend_detour              :1;	//(31:31,NA,0x0) //1 : detour (input = output)
	};
}PE_O26_SR_BLEND_SR_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02814 RW 0x0f00_0870
	UINT32 reg_sr_blend_height              :16;	//(15:0,NA,2160) //input image height (default : 2160)
	UINT32 reg_sr_blend_width               :16;	//(31:16,NA,3840) //input image width (default : 3840)
	};
}PE_O26_SR_BLEND_SR_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02818 RW 0x0000_0000
	UINT32 resvd                            :26;
	UINT32 reg_motion_en_t                  :1;	//(26:26,NA,0) //motion blend enable (texture)
	UINT32 reg_motion_en_e                  :1;	//(27:27,NA,0) //motion blend enable (edge)
	UINT32 reg_face_gain_en_t               :1;	//(28:28,NA,0) //face gain enable (texture)
	UINT32 reg_face_gain_en_e               :1;	//(29:29,NA,0) //face gain enable (edge)
	UINT32 reg_luma_blend_en_t              :1;	//(30:30,NA,0) //luma blend enable (Texture)
	UINT32 reg_luma_blend_en_e              :1;	//(31:31,NA,0) //luma blend enable (edge)
	};
}PE_O26_SR_BLEND_SR_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0281C RW 0x0000_0000
	UINT32 reg_resi_blur_manual_t           :8;	//(7:0,NA,0) //residual blur manual (texture)
	UINT32 reg_resi_blur_manual_e           :8;	//(15:8,NA,0) //residual blur manual (edge)
	UINT32 resvd                            :12;
	UINT32 reg_resi_blur_mode_t             :1;	//(28:28,NA,0) //residual blur mode (texture)
	UINT32 reg_resi_blur_mode_e             :1;	//(29:29,NA,0) //residual blur mode (edge)
	UINT32 reg_resi_blur_en_t               :1;	//(30:30,NA,0) //residual blur enable (texture)
	UINT32 reg_resi_blur_en_e               :1;	//(31:31,NA,0) //residual blur enable (edge)
	};
}PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02820 RW 0x0008_1020
	UINT32 reg_resi_blur_eSR_x3             :8;	//(7:0,NA,32) //
	UINT32 reg_resi_blur_eSR_x2             :8;	//(15:8,NA,16) //
	UINT32 reg_resi_blur_eSR_x1             :8;	//(23:16,NA,8) //
	UINT32 reg_resi_blur_eSR_x0             :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_EDGE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02824 RW 0xff40_2000
	UINT32 reg_resi_blur_eSR_y3             :8;	//(7:0,NA,0) //
	UINT32 reg_resi_blur_eSR_y2             :8;	//(15:8,NA,32) //
	UINT32 reg_resi_blur_eSR_y1             :8;	//(23:16,NA,64) //
	UINT32 reg_resi_blur_eSR_y0             :8;	//(31:24,NA,255) //
	};
}PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_EDGE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02828 RW 0x0008_1020
	UINT32 reg_resi_blur_tSR_x3             :8;	//(7:0,NA,32) //
	UINT32 reg_resi_blur_tSR_x2             :8;	//(15:8,NA,16) //
	UINT32 reg_resi_blur_tSR_x1             :8;	//(23:16,NA,8) //
	UINT32 reg_resi_blur_tSR_x0             :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0282C RW 0xff40_2000
	UINT32 reg_resi_blur_tSR_y3             :8;	//(7:0,NA,0) //
	UINT32 reg_resi_blur_tSR_y2             :8;	//(15:8,NA,32) //
	UINT32 reg_resi_blur_tSR_y1             :8;	//(23:16,NA,64) //
	UINT32 reg_resi_blur_tSR_y0             :8;	//(31:24,NA,255) //
	};
}PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02830 RW 0x00ff_00ff
	UINT32 reg_tSR_master_gain              :10;	//(9:0,NA,255) //texture residual master gain
	UINT32 resvd0                           :6;
	UINT32 reg_eSR_master_gain              :10;	//(25:16,NA,255) //edge residual master gain
	UINT32 resvd1                           :6;
	};
}PE_O26_SR_BLEND_SR_BLEND_MASTER_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02834 RW 0x0020_4080
	UINT32 reg_luma_blend_pos_eSR_x3        :8;	//(7:0,NA,128) //
	UINT32 reg_luma_blend_pos_eSR_x2        :8;	//(15:8,NA,64) //
	UINT32 reg_luma_blend_pos_eSR_x1        :8;	//(23:16,NA,32) //
	UINT32 reg_luma_blend_pos_eSR_x0        :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02838 RW 0xc4ff_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_pos_eSR_x5        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_pos_eSR_x4        :8;	//(31:24,NA,196) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0283C RW 0x00ff_ffff
	UINT32 reg_luma_blend_pos_eSR_y3        :8;	//(7:0,NA,255) //
	UINT32 reg_luma_blend_pos_eSR_y2        :8;	//(15:8,NA,255) //
	UINT32 reg_luma_blend_pos_eSR_y1        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_pos_eSR_y0        :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02840 RW 0xffff_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_pos_eSR_y5        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_pos_eSR_y4        :8;	//(31:24,NA,255) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02844 RW 0x0020_4080
	UINT32 reg_luma_blend_neg_eSR_x3        :8;	//(7:0,NA,128) //
	UINT32 reg_luma_blend_neg_eSR_x2        :8;	//(15:8,NA,64) //
	UINT32 reg_luma_blend_neg_eSR_x1        :8;	//(23:16,NA,32) //
	UINT32 reg_luma_blend_neg_eSR_x0        :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02848 RW 0xc4ff_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_neg_eSR_x5        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_neg_eSR_x4        :8;	//(31:24,NA,196) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0284C RW 0x00ff_ffff
	UINT32 reg_luma_blend_neg_eSR_y3        :8;	//(7:0,NA,255) //
	UINT32 reg_luma_blend_neg_eSR_y2        :8;	//(15:8,NA,255) //
	UINT32 reg_luma_blend_neg_eSR_y1        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_neg_eSR_y0        :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02850 RW 0xffff_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_neg_eSR_y5        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_neg_eSR_y4        :8;	//(31:24,NA,255) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02854 RW 0x0040_6090
	UINT32 reg_luma_blend_pos_tSR_x3        :8;	//(7:0,NA,144) //
	UINT32 reg_luma_blend_pos_tSR_x2        :8;	//(15:8,NA,96) //
	UINT32 reg_luma_blend_pos_tSR_x1        :8;	//(23:16,NA,64) //
	UINT32 reg_luma_blend_pos_tSR_x0        :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02858 RW 0xc4ff_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_pos_tSR_x5        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_pos_tSR_x4        :8;	//(31:24,NA,196) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0285C RW 0xa0a0_a090
	UINT32 reg_luma_blend_pos_tSR_y3        :8;	//(7:0,NA,144) //
	UINT32 reg_luma_blend_pos_tSR_y2        :8;	//(15:8,NA,160) //
	UINT32 reg_luma_blend_pos_tSR_y1        :8;	//(23:16,NA,160) //
	UINT32 reg_luma_blend_pos_tSR_y0        :8;	//(31:24,NA,160) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02860 RW 0x7050_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_pos_tSR_y5        :8;	//(23:16,NA,80) //
	UINT32 reg_luma_blend_pos_tSR_y4        :8;	//(31:24,NA,112) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02864 RW 0x0040_6090
	UINT32 reg_luma_blend_neg_tSR_x3        :8;	//(7:0,NA,144) //
	UINT32 reg_luma_blend_neg_tSR_x2        :8;	//(15:8,NA,96) //
	UINT32 reg_luma_blend_neg_tSR_x1        :8;	//(23:16,NA,64) //
	UINT32 reg_luma_blend_neg_tSR_x0        :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02868 RW 0xc4ff_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_neg_tSR_x5        :8;	//(23:16,NA,255) //
	UINT32 reg_luma_blend_neg_tSR_x4        :8;	//(31:24,NA,196) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0286C RW 0xa0a0_a090
	UINT32 reg_luma_blend_neg_tSR_y3        :8;	//(7:0,NA,144) //
	UINT32 reg_luma_blend_neg_tSR_y2        :8;	//(15:8,NA,160) //
	UINT32 reg_luma_blend_neg_tSR_y1        :8;	//(23:16,NA,160) //
	UINT32 reg_luma_blend_neg_tSR_y0        :8;	//(31:24,NA,160) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02870 RW 0x7050_0000
	UINT32 resvd                            :16;
	UINT32 reg_luma_blend_neg_tSR_y5        :8;	//(23:16,NA,80) //
	UINT32 reg_luma_blend_neg_tSR_y4        :8;	//(31:24,NA,112) //
	};
}PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02874 RW 0x0000_0000
	UINT32 reg_face_gain_eSR_x3             :8;	//(7:0,NA,0) //
	UINT32 reg_face_gain_eSR_x2             :8;	//(15:8,NA,0) //
	UINT32 reg_face_gain_eSR_x1             :8;	//(23:16,NA,0) //
	UINT32 reg_face_gain_eSR_x0             :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_EDGE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02878 RW 0x0000_0000
	UINT32 reg_face_gain_eSR_y3             :8;	//(7:0,NA,0) //
	UINT32 reg_face_gain_eSR_y2             :8;	//(15:8,NA,0) //
	UINT32 reg_face_gain_eSR_y1             :8;	//(23:16,NA,0) //
	UINT32 reg_face_gain_eSR_y0             :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_EDGE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0287C RW 0x0000_0000
	UINT32 reg_face_gain_tSR_x3             :8;	//(7:0,NA,0) //
	UINT32 reg_face_gain_tSR_x2             :8;	//(15:8,NA,0) //
	UINT32 reg_face_gain_tSR_x1             :8;	//(23:16,NA,0) //
	UINT32 reg_face_gain_tSR_x0             :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02880 RW 0x0000_0000
	UINT32 reg_face_gain_tSR_y3             :8;	//(7:0,NA,0) //
	UINT32 reg_face_gain_tSR_y2             :8;	//(15:8,NA,0) //
	UINT32 reg_face_gain_tSR_y1             :8;	//(23:16,NA,0) //
	UINT32 reg_face_gain_tSR_y0             :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02884 RW 0x0000_0000
	UINT32 reg_motion_gain_eSR_x3           :8;	//(7:0,NA,0) //
	UINT32 reg_motion_gain_eSR_x2           :8;	//(15:8,NA,0) //
	UINT32 reg_motion_gain_eSR_x1           :8;	//(23:16,NA,0) //
	UINT32 reg_motion_gain_eSR_x0           :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_EDGE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02888 RW 0x0000_0000
	UINT32 reg_motion_gain_eSR_y3           :8;	//(7:0,NA,0) //
	UINT32 reg_motion_gain_eSR_y2           :8;	//(15:8,NA,0) //
	UINT32 reg_motion_gain_eSR_y1           :8;	//(23:16,NA,0) //
	UINT32 reg_motion_gain_eSR_y0           :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_EDGE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0288C RW 0x0000_0000
	UINT32 reg_motion_gain_tSR_x3           :8;	//(7:0,NA,0) //
	UINT32 reg_motion_gain_tSR_x2           :8;	//(15:8,NA,0) //
	UINT32 reg_motion_gain_tSR_x1           :8;	//(23:16,NA,0) //
	UINT32 reg_motion_gain_tSR_x0           :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02890 RW 0x0000_0000
	UINT32 reg_motion_gain_tSR_y3           :8;	//(7:0,NA,0) //
	UINT32 reg_motion_gain_tSR_y2           :8;	//(15:8,NA,0) //
	UINT32 reg_motion_gain_tSR_y1           :8;	//(23:16,NA,0) //
	UINT32 reg_motion_gain_tSR_y0           :8;	//(31:24,NA,0) //
	};
}PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02894 RW 0x4040_8000
	UINT32 resvd                            :8;
	UINT32 reg_gain_hh                      :8;	//(15:8,NA,128) //HH Band gain
	UINT32 reg_gain_hl                      :8;	//(23:16,NA,64) //HL Band gain
	UINT32 reg_gain_lh                      :8;	//(31:24,NA,64) //LH Band gain
	};
}PE_O26_SR_BLEND_SR_BLEND_BAND_GAIN_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02898 RW 0x4408_0000
	UINT32 resvd0                           :12;
	UINT32 reg_alpha_blend_ratio            :8;	//(19:12,NA,128) //RATIO Band alpha_blend
	UINT32 resvd1                           :3;
	UINT32 reg_alpha_blend_sel              :1;	//(23:23,NA,0) //SEL Band alpha_blend
	UINT32 resvd2                           :2;
	UINT32 reg_alpha_blur_mode              :2;	//(27:26,NA,1) //MODE Band alpha_blur
	UINT32 resvd3                           :1;
	UINT32 reg_delta_scale                  :3;	//(31:29,NA,2) //SCALE Band delta
	};
}PE_O26_SR_BLEND_SR_BLEND_ALPHA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0289C RW 0x0008_1020
	UINT32 reg_domi_blend_eSR_x3            :8;	//(7:0,NA,32) //X3 Band domi_blend_eSR
	UINT32 reg_domi_blend_eSR_x2            :8;	//(15:8,NA,16) //X2 Band domi_blend_eSR
	UINT32 reg_domi_blend_eSR_x1            :8;	//(23:16,NA,8) //X1 Band domi_blend_eSR
	UINT32 reg_domi_blend_eSR_x0            :8;	//(31:24,NA,0) //X0 Band domi_blend_eSR
	};
}PE_O26_SR_BLEND_SR_BLEND_ALPHA_EDGE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028A0 RW 0xa0c0_e0ff
	UINT32 reg_domi_blend_eSR_y3            :8;	//(7:0,NA,255) //Y3 Band domi_blend_eSR
	UINT32 reg_domi_blend_eSR_y2            :8;	//(15:8,NA,224) //Y2 Band domi_blend_eSR
	UINT32 reg_domi_blend_eSR_y1            :8;	//(23:16,NA,192) //Y1 Band domi_blend_eSR
	UINT32 reg_domi_blend_eSR_y0            :8;	//(31:24,NA,160) //Y0 Band domi_blend_eSR
	};
}PE_O26_SR_BLEND_SR_BLEND_ALPHA_EDGE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028A4 RW 0x0008_1020
	UINT32 reg_domi_blend_tSR_x3            :8;	//(7:0,NA,32) //X3 Band domi_blend_tSR
	UINT32 reg_domi_blend_tSR_x2            :8;	//(15:8,NA,16) //X2 Band domi_blend_tSR
	UINT32 reg_domi_blend_tSR_x1            :8;	//(23:16,NA,8) //X1 Band domi_blend_tSR
	UINT32 reg_domi_blend_tSR_x0            :8;	//(31:24,NA,0) //X0 Band domi_blend_tSR
	};
}PE_O26_SR_BLEND_SR_BLEND_ALPHA_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028A8 RW 0xa080_4020
	UINT32 reg_domi_blend_tSR_y3            :8;	//(7:0,NA,32) //Y3 Band domi_blend_tSR
	UINT32 reg_domi_blend_tSR_y2            :8;	//(15:8,NA,64) //Y2 Band domi_blend_tSR
	UINT32 reg_domi_blend_tSR_y1            :8;	//(23:16,NA,128) //Y1 Band domi_blend_tSR
	UINT32 reg_domi_blend_tSR_y0            :8;	//(31:24,NA,160) //Y0 Band domi_blend_tSR
	};
}PE_O26_SR_BLEND_SR_BLEND_ALPHA_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028B0 RW 0x0000_0000
	UINT32 reg_ellipse_ctrl_en              :1;	//(0:0,NA,0x0) //0: not use ellipse gain, 1 : use ellipse gain; (
	UINT32 resvd0                           :3;
	UINT32 reg_sel_output                   :1;	//(4:4,NA,0x0) //0 : Ellipse gain; 1 : 255 or 0
	UINT32 resvd1                           :3;
	UINT32 reg_ellipse_offset               :8;	//(15:8,NA,0x0) //OFFSET Band ellipse
	UINT32 resvd2                           :16;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028B4 RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,NA,0x0) //POS Band f0_w1
	UINT32 reg_f0_h1_pos                    :12;	//(23:12,NA,0x0) //POS Band f0_h1
	UINT32 reg_f0_enable                    :1;	//(24:24,NA,0x0) //ENABLE Band f0
	UINT32 resvd                            :7;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028B8 RW 0x0000_0000
	UINT32 reg_f0_w2_pos                    :12;	//(11:0,NA,0x0) //POS Band f0_w2
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,NA,0x0) //POS Band f0_h2
	UINT32 resvd                            :8;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028BC RW 0x0000_0000
	UINT32 reg_f0_e_mul_b                   :9;	//(8:0,NA,0x0) //B Band f0_e_mul
	UINT32 resvd0                           :3;
	UINT32 reg_f0_e_mul_a                   :9;	//(20:12,NA,0x0) //A Band f0_e_mul
	UINT32 resvd1                           :3;
	UINT32 reg_f0_ellipse_master            :8;	//(31:24,NA,0x0) //MASTER Band f0_ellipse
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028C0 RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,NA,0x0) //POS Band f1_w1
	UINT32 reg_f1_h1_pos                    :12;	//(23:12,NA,0x0) //POS Band f1_h1
	UINT32 reg_f1_enable                    :1;	//(24:24,NA,0x0) //ENABLE Band f1
	UINT32 resvd                            :7;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028C4 RW 0x0000_0000
	UINT32 reg_f1_w2_pos                    :12;	//(11:0,NA,0x0) //POS Band f1_w2
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,NA,0x0) //POS Band f1_h2
	UINT32 resvd                            :8;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028C8 RW 0x0000_0000
	UINT32 reg_f1_e_mul_b                   :9;	//(8:0,NA,0x0) //B Band f1_e_mul
	UINT32 resvd0                           :3;
	UINT32 reg_f1_e_mul_a                   :9;	//(20:12,NA,0x0) //A Band f1_e_mul
	UINT32 resvd1                           :3;
	UINT32 reg_f1_ellipse_master            :8;	//(31:24,NA,0x0) //MASTER Band f1_ellipse
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028CC RW 0x0000_0000
	UINT32 reg_f2_w1_pos                    :12;	//(11:0,NA,0x0) //POS Band f2_w1
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,NA,0x0) //POS Band f2_h1
	UINT32 reg_f2_enable                    :1;	//(24:24,NA,0x0) //ENABLE Band f2
	UINT32 resvd                            :7;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028D0 RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,NA,0x0) //POS Band f2_w2
	UINT32 reg_f2_h2_pos                    :12;	//(23:12,NA,0x0) //POS Band f2_h2
	UINT32 resvd                            :8;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028D4 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,NA,0x0) //B Band f2_e_mul
	UINT32 resvd0                           :3;
	UINT32 reg_f2_e_mul_a                   :9;	//(20:12,NA,0x0) //A Band f2_e_mul
	UINT32 resvd1                           :3;
	UINT32 reg_f2_ellipse_master            :8;	//(31:24,NA,0x0) //MASTER Band f2_ellipse
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028D8 RW 0x0000_0000
	UINT32 reg_f3_w1_pos                    :12;	//(11:0,NA,0x0) //POS Band f3_w1
	UINT32 reg_f3_h1_pos                    :12;	//(23:12,NA,0x0) //POS Band f3_h1
	UINT32 reg_f3_enable                    :1;	//(24:24,NA,0x0) //ENABLE Band f3
	UINT32 resvd                            :7;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028DC RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,NA,0x0) //POS Band f3_w2
	UINT32 reg_f3_h2_pos                    :12;	//(23:12,NA,0x0) //POS Band f3_h2
	UINT32 resvd                            :8;
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028E0 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,NA,0x0) //B Band f3_e_mul
	UINT32 resvd0                           :3;
	UINT32 reg_f3_e_mul_a                   :9;	//(20:12,NA,0x0) //A Band f3_e_mul
	UINT32 resvd1                           :3;
	UINT32 reg_f3_ellipse_master            :8;	//(31:24,NA,0x0) //MASTER Band f3_ellipse
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028E4 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //Y0 Band gain_lut
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //X0 Band gain_lut
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //Y1 Band gain_lut
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //X1 Band gain_lut
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028E8 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //Y2 Band gain_lut
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //X2 Band gain_lut
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //Y3 Band gain_lut
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //X3 Band gain_lut
	};
}PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028F0 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028F4 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :16;	//(15:0,NA,0) //Input vertical counter
	UINT32 reg_mon_in_hori_cnt              :16;	//(31:16,NA,0) //Input horizontal counter
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028F8 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :16;	//(15:0,NA,0) //Output vertical counter
	UINT32 reg_mon_out_hori_cnt             :16;	//(31:16,NA,0) //Output horizontal counter
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA028FC RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :16;	//(15:0,NA,0) //Output previous frame vertical counter
	UINT32 reg_mon_fin_in_vert_cnt          :16;	//(31:16,NA,0) //Input previous frame vertical counter
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02900 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02904 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02908 RO 0x0000_0000
	UINT32 reg_resi_e_in_vert_cnt           :16;	//(15:0,NA,0) //Input residual edge vertical counter
	UINT32 reg_resi_e_in_hori_cnt           :16;	//(31:16,NA,0) //Input residual edge horizontal counter
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0290C RO 0x0000_0000
	UINT32 reg_resi_t_out_vert_cnt          :16;	//(15:0,NA,0) //Input residual texture vertical counter
	UINT32 reg_resi_t_out_hori_cnt          :16;	//(31:16,NA,0) //Input residual texture horizontal counter
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02910 RO 0x0000_0000
	UINT32 reg_mot_in_vert_cnt              :16;	//(15:0,NA,0) //Input motion vertical counter
	UINT32 reg_mot_in_hori_cnt              :16;	//(31:16,NA,0) //Input motion horizontal counter
	};
}PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02920 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_SR_BLEND_SR_BLEND_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02924 RO 0x0000_0000
	UINT32 reg_sr_blend_mon_in_vert_cnt     :16;	//(15:0,NA,0) //Input vertical counter
	UINT32 reg_sr_blend_mon_in_hori_cnt     :16;	//(31:16,NA,0) //Input horizontal counter
	};
}PE_O26_SR_BLEND_SR_BLEND_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02928 RO 0x0000_0000
	UINT32 reg_sr_blend_mon_out_vert_cnt    :16;	//(15:0,NA,0) //Output vertical counter
	UINT32 reg_sr_blend_mon_out_hori_cnt    :16;	//(31:16,NA,0) //Output horizontal counter
	};
}PE_O26_SR_BLEND_SR_BLEND_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA0292C RO 0x0000_0000
	UINT32 reg_sr_blend_mon_fin_out_vert_cnt :16;	//(15:0,NA,0) //Output previous frame vertical counter
	UINT32 reg_sr_blend_mon_fin_in_vert_cnt :16;	//(31:16,NA,0) //Input previous frame vertical counter
	};
}PE_O26_SR_BLEND_SR_BLEND_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02930 RO 0x0000_0000
	UINT32 reg_sr_blend_mon_shp_i_sucfail   :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_SR_BLEND_SR_BLEND_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA02934 RO 0x0000_0000
	UINT32 reg_sr_blend_mon_shp_o_sucfail   :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_SR_BLEND_SR_BLEND_STAT_05_T;

typedef struct {
	PE_O26_SR_BLEND_SR_MERGE_TOP_CTRL_00_T            sr_merge_top_ctrl_00;	//0xCCA02800
	PE_O26_SR_BLEND_SR_MERGE_TOP_CTRL_01_T            sr_merge_top_ctrl_01;	//0xCCA02804
	PE_O26_SR_BLEND_SR_MERGE_TOP_PAT_CTRL_00_T    sr_merge_top_pat_ctrl_00;	//0xCCA02808
	PE_O26_SR_BLEND_SR_MERGE_TOP_PAT_CTRL_01_T    sr_merge_top_pat_ctrl_01;	//0xCCA0280C
	PE_O26_SR_BLEND_SR_BLEND_CTRL_00_T                    sr_blend_ctrl_00;	//0xCCA02810
	PE_O26_SR_BLEND_SR_BLEND_CTRL_01_T                    sr_blend_ctrl_01;	//0xCCA02814
	PE_O26_SR_BLEND_SR_BLEND_CTRL_02_T                    sr_blend_ctrl_02;	//0xCCA02818
	PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_CTRL_00_T sr_blend_resi_blur_ctrl_00;	//0xCCA0281C
	PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_EDGE_00_T sr_blend_resi_blur_edge_00;	//0xCCA02820
	PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_EDGE_01_T sr_blend_resi_blur_edge_01;	//0xCCA02824
	PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_TEXT_00_T sr_blend_resi_blur_text_00;	//0xCCA02828
	PE_O26_SR_BLEND_SR_BLEND_RESI_BLUR_TEXT_01_T sr_blend_resi_blur_text_01;	//0xCCA0282C
	PE_O26_SR_BLEND_SR_BLEND_MASTER_GAIN_T            sr_blend_master_gain;	//0xCCA02830
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_00_T  sr_blend_luma_pos_edge_00;	//0xCCA02834
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_01_T  sr_blend_luma_pos_edge_01;	//0xCCA02838
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_02_T  sr_blend_luma_pos_edge_02;	//0xCCA0283C
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_EDGE_03_T  sr_blend_luma_pos_edge_03;	//0xCCA02840
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_00_T  sr_blend_luma_neg_edge_00;	//0xCCA02844
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_01_T  sr_blend_luma_neg_edge_01;	//0xCCA02848
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_02_T  sr_blend_luma_neg_edge_02;	//0xCCA0284C
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_EDGE_03_T  sr_blend_luma_neg_edge_03;	//0xCCA02850
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_00_T  sr_blend_luma_pos_text_00;	//0xCCA02854
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_01_T  sr_blend_luma_pos_text_01;	//0xCCA02858
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_02_T  sr_blend_luma_pos_text_02;	//0xCCA0285C
	PE_O26_SR_BLEND_SR_BLEND_LUMA_POS_TEXT_03_T  sr_blend_luma_pos_text_03;	//0xCCA02860
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_00_T  sr_blend_luma_neg_text_00;	//0xCCA02864
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_01_T  sr_blend_luma_neg_text_01;	//0xCCA02868
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_02_T  sr_blend_luma_neg_text_02;	//0xCCA0286C
	PE_O26_SR_BLEND_SR_BLEND_LUMA_NEG_TEXT_03_T  sr_blend_luma_neg_text_03;	//0xCCA02870
	PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_EDGE_00_T sr_blend_face_gain_edge_00;	//0xCCA02874
	PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_EDGE_01_T sr_blend_face_gain_edge_01;	//0xCCA02878
	PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_TEXT_00_T sr_blend_face_gain_text_00;	//0xCCA0287C
	PE_O26_SR_BLEND_SR_BLEND_FACE_GAIN_TEXT_01_T sr_blend_face_gain_text_01;	//0xCCA02880
	PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_EDGE_00_T sr_blend_motion_gain_edge_00;	//0xCCA02884
	PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_EDGE_01_T sr_blend_motion_gain_edge_01;	//0xCCA02888
	PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_TEXT_00_T sr_blend_motion_gain_text_00;	//0xCCA0288C
	PE_O26_SR_BLEND_SR_BLEND_MOTION_GAIN_TEXT_01_T sr_blend_motion_gain_text_01;	//0xCCA02890
	PE_O26_SR_BLEND_SR_BLEND_BAND_GAIN_00_T          sr_blend_band_gain_00;	//0xCCA02894
	PE_O26_SR_BLEND_SR_BLEND_ALPHA_CTRL_00_T        sr_blend_alpha_ctrl_00;	//0xCCA02898
	PE_O26_SR_BLEND_SR_BLEND_ALPHA_EDGE_00_T        sr_blend_alpha_edge_00;	//0xCCA0289C
	PE_O26_SR_BLEND_SR_BLEND_ALPHA_EDGE_01_T        sr_blend_alpha_edge_01;	//0xCCA028A0
	PE_O26_SR_BLEND_SR_BLEND_ALPHA_TEXT_00_T        sr_blend_alpha_text_00;	//0xCCA028A4
	PE_O26_SR_BLEND_SR_BLEND_ALPHA_TEXT_01_T        sr_blend_alpha_text_01;	//0xCCA028A8
	UINT32                                                    reserved0;	//0xCCA028AC
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_00_T    sr_blend_ellipse_ctrl_00;	//0xCCA028B0
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_01_T    sr_blend_ellipse_ctrl_01;	//0xCCA028B4
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_02_T    sr_blend_ellipse_ctrl_02;	//0xCCA028B8
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_03_T    sr_blend_ellipse_ctrl_03;	//0xCCA028BC
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_04_T    sr_blend_ellipse_ctrl_04;	//0xCCA028C0
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_05_T    sr_blend_ellipse_ctrl_05;	//0xCCA028C4
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_06_T    sr_blend_ellipse_ctrl_06;	//0xCCA028C8
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_07_T    sr_blend_ellipse_ctrl_07;	//0xCCA028CC
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_08_T    sr_blend_ellipse_ctrl_08;	//0xCCA028D0
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_09_T    sr_blend_ellipse_ctrl_09;	//0xCCA028D4
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_10_T    sr_blend_ellipse_ctrl_10;	//0xCCA028D8
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_11_T    sr_blend_ellipse_ctrl_11;	//0xCCA028DC
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_CTRL_12_T    sr_blend_ellipse_ctrl_12;	//0xCCA028E0
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_LUT_CTRL_00_T sr_blend_ellipse_lut_ctrl_00;	//0xCCA028E4
	PE_O26_SR_BLEND_SR_BLEND_ELLIPSE_LUT_CTRL_01_T sr_blend_ellipse_lut_ctrl_01;	//0xCCA028E8
	UINT32                                                    reserved1;	//0xCCA028EC
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_00_T            sr_merge_top_stat_00;	//0xCCA028F0
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_01_T            sr_merge_top_stat_01;	//0xCCA028F4
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_02_T            sr_merge_top_stat_02;	//0xCCA028F8
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_03_T            sr_merge_top_stat_03;	//0xCCA028FC
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_04_T            sr_merge_top_stat_04;	//0xCCA02900
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_05_T            sr_merge_top_stat_05;	//0xCCA02904
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_06_T            sr_merge_top_stat_06;	//0xCCA02908
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_07_T            sr_merge_top_stat_07;	//0xCCA0290C
	PE_O26_SR_BLEND_SR_MERGE_TOP_STAT_08_T            sr_merge_top_stat_08;	//0xCCA02910
	UINT32                                                    reserved2;	//0xCCA02914
	UINT32                                                    reserved3;	//0xCCA02918
	UINT32                                                    reserved4;	//0xCCA0291C
	PE_O26_SR_BLEND_SR_BLEND_STAT_00_T                    sr_blend_stat_00;	//0xCCA02920
	PE_O26_SR_BLEND_SR_BLEND_STAT_01_T                    sr_blend_stat_01;	//0xCCA02924
	PE_O26_SR_BLEND_SR_BLEND_STAT_02_T                    sr_blend_stat_02;	//0xCCA02928
	PE_O26_SR_BLEND_SR_BLEND_STAT_03_T                    sr_blend_stat_03;	//0xCCA0292C
	PE_O26_SR_BLEND_SR_BLEND_STAT_04_T                    sr_blend_stat_04;	//0xCCA02930
	PE_O26_SR_BLEND_SR_BLEND_STAT_05_T                    sr_blend_stat_05;	//0xCCA02934
}PE_SR_BLEND_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15100 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O26_GAV_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15104 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //Processing width  (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //Processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15108 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O26_GAV_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1510C RW 0x000A_0000
	UINT32 resvd0                           :16;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,10) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15140 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //Pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //Pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //Pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O26_GAV_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC151F0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //Debug display	0 : normal display (output 1)	1 : normal display (output 2)	2 : tgen only	3 : Luma Adabtive	4 : weight(A)	5 : weight(Texture)	6 : A-map	7 : T-map	8 : soft edge gain map	9 : A-map for der	10: Motion map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //DP detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //DP buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O26_GAV_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15200 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //Post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //Pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //Pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //Pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O26_GAV_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15204 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_GAV_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15208 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //Get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //Get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O26_GAV_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1520C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15210 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15214 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15218 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1521C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15220 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O26_GAV_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15224 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15228 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O26_GAV_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1522C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //Edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //Texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O26_GAV_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15230 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O26_GAV_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15234 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O26_GAV_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15238 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1523C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O26_GAV_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15240 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O26_GAV_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15244 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O26_GAV_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15248 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O26_GAV_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1524C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O26_GAV_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15250 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O26_GAV_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15254 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //Input selection for flat region LUT	0: a_map	1: t_map	2: max(a_map,t_map)	3: min(255,a_map+t_map) (default)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //Add a flat gain to A-map enable
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //Add a flat gain to T-map enable
	UINT32 resvd2                           :23;
	};
}PE_O26_GAV_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15258 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O26_GAV_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15260 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O26_GAV_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15264 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O26_GAV_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15268 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_GAV_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1526C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_GAV_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15270 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_GAV_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15274 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_GAV_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15278 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //Gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_GAV_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1527C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_GAV_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15280 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //Level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //Level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_GAV_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15284 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //Level-balancing, lum2_y0
	};
}PE_O26_GAV_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15288 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //Level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_GAV_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1528C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_GAV_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15290 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_GAV_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152C0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O26_GAV_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152C4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //Bilateral filter tap size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //Edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //Edge filter en
	};
}PE_O26_GAV_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152C8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //Edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //Edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O26_GAV_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152CC RW 0x0006_5008
	UINT32 reg_derv_en                      :1;	//(0:0,NA,0) //DER-V enable
	UINT32 resvd0                           :2;
	UINT32 reg_derv_bif_en                  :1;	//(3:3,NA,1) //Bilateral filter	0: disable	1: enable
	UINT32 reg_derv_output_mux              :4;	//(7:4,NA,0) //Display mode	0xxx: normal display	1000: vertical ringing measure	1001: gain adjusted by curve mapping	101x: bilateral filter output	o.w : not used
	UINT32 reg_derv_bif_manual_th           :8;	//(15:8,NA,80) //Bilateral filter threshold
	UINT32 reg_derv_th_gain                 :6;	//(21:16,NA,6) //Auto threshold gain, th = th_gain * A
	UINT32 resvd1                           :2;
	UINT32 reg_derv_th_mode                 :1;	//(24:24,NA,0) //Threshold mode	0: auto(A-map)	1: manual
	UINT32 resvd2                           :7;
	};
}PE_O26_GAV_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152D0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //Center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //Center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_O26_GAV_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152D4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //Gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //Gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_O26_GAV_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152D8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O26_GAV_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152DC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O26_GAV_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152E0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O26_GAV_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152E4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O26_GAV_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152E8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_GAV_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152EC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_GAV_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152F0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_GAV_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152F4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_GAV_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152F8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //Gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_GAV_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC152FC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_GAV_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15300 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //Level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //Level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_GAV_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15304 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //Level-balancing, lum2_y0
	};
}PE_O26_GAV_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15308 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //Level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_GAV_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1530C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_GAV_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15310 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_GAV_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15320 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //Min-max tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //Average tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_GAV_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15324 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //Min-max tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //Average tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_GAV_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15328 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_GAV_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1532C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_GAV_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15330 RW 0x1010_2014
	UINT32 reg_sti_enable                   :1;	//(0:0,NA,0) //STI enable
	UINT32 reg_sti_debug_map_en             :1;	//(1:1,NA,0) //Debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//(3:2,NA,1) //Min-max tap size
	UINT32 reg_sti_avg_tap_size             :2;	//(5:4,NA,1) //Average tap size
	UINT32 reg_sti_ti_mode                  :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//(15:8,NA,32) //Master gain
	UINT32 reg_sti_texture_gain             :8;	//(23:16,NA,16) //Texture gain
	UINT32 reg_sti_edge_gain                :8;	//(31:24,NA,16) //Edge gain
	};
}PE_O26_GAV_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15340 RW 0x8000_0011
	UINT32 reg_tgen_on_off                  :1;	//(0:0,NA,1) //TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//(4:4,NA,1) //Manual seed mode for rand val
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//(8:8,NA,0) //Debug mode enable
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//(19:16,NA,0) //Mode for rand val
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//(31:24,NA,128) //Master gain
	};
}PE_O26_GAV_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15344 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //R clipping bound for delta
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //L clipping bound for delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //Max threshold for delta
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //Scale factor for delta
	UINT32 resvd3                           :5;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15348 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //Rand val threshold
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //Weight for curr for delta
	UINT32 resvd                            :20;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1534C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //Initial seed value for manual seed mode
	};
}PE_O26_GAV_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15354 RW 0x0202_1F04
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //Min-max offset
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //Min-max selection mode
	UINT32 resvd2                           :6;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15358 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //Rand scale factor for noise delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //Min-max scale factor for noise delta
	UINT32 resvd2                           :3;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1535C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //Noise blur coefficient, x2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //Noise blur coefficient, x1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //Noise blur coefficient, x0
	UINT32 resvd2                           :2;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15360 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //Noise blur coefficient, y2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //Noise blur coefficient, y1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //Noise blur coefficient, y0
	UINT32 resvd2                           :2;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15364 RW 0x3F80_1F1F
	UINT32 resvd0                           :24;
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //Noise gain
	UINT32 resvd1                           :2;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15368 RW 0x48AB_CDFF
	UINT32 tdata0                           :32;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1536C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15370 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_GAV_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15460 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //DP sum LUT mode	0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O26_GAV_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15464 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //DP sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //DP sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //DP sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //DP sum LUT for delta control, x1
	};
}PE_O26_GAV_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15468 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //DP sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //DP sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //DP sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //DP sum LUT for delta control, x3
	};
}PE_O26_GAV_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC154A0 RW 0x0000_0000
	UINT32 reg_win_dp_win0_en               :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_dp_win1_en               :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_dp_win01_en              :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dp_win_outside           :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_dp_win_en                :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_dp_bdr_alpha             :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_dp_bdr_wid               :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_dp_bdr_en                :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_dp_cr5                   :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_dp_cb5                   :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_dp_yy6                   :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_GAV_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC154A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //Window control, win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //Window control, win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC154A8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //Window control, win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //Window control, win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC154AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //Window control, win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //Window control, win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC154B0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //Window control, win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //Window control, win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15700 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15704 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15708 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1570C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter 4K Last = 2160
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter 4K Last = 2160
	UINT32 resvd1                           :4;
	};
}PE_O26_GAV_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15710 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_GAV_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15714 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_GAV_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15760 RO 0x0000_0000
	UINT32 reg_status_a_avg                 :32;	//(31:0,NA,0) //FD status register (a_avg)
	};
}PE_O26_GAV_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15764 RO 0x0000_0000
	UINT32 reg_status_t_avg                 :32;	//(31:0,NA,0) //FD status register (t_avg)
	};
}PE_O26_GAV_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15768 RO 0x0000_0000
	UINT32 reg_status_e_avg                 :32;	//(31:0,NA,0) //FD status register (e_avg)
	};
}PE_O26_GAV_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1576C RO 0x0000_0000
	UINT32 reg_status_d_avg                 :32;	//(31:0,NA,0) //FD status register (d_avg)
	};
}PE_O26_GAV_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC158F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_GAV_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC158F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_GAV_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC158F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_GAV_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC158FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_GAV_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O26_GAV_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCCC15100
	PE_O26_GAV_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCCC15104
	PE_O26_GAV_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCCC15108
	PE_O26_GAV_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCCC1510C
	UINT32                                                   reserved0;	//0xCCC15110
	UINT32                                                   reserved1;	//0xCCC15114
	UINT32                                                   reserved2;	//0xCCC15118
	UINT32                                                   reserved3;	//0xCCC1511C
	UINT32                                                   reserved4;	//0xCCC15120
	UINT32                                                   reserved5;	//0xCCC15124
	UINT32                                                   reserved6;	//0xCCC15128
	UINT32                                                   reserved7;	//0xCCC1512C
	UINT32                                                   reserved8;	//0xCCC15130
	UINT32                                                   reserved9;	//0xCCC15134
	UINT32                                                  reserved10;	//0xCCC15138
	UINT32                                                  reserved11;	//0xCCC1513C
	PE_O26_GAV_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCCC15140
	UINT32                                                  reserved12;	//0xCCC15144
	UINT32                                                  reserved13;	//0xCCC15148
	UINT32                                                  reserved14;	//0xCCC1514C
	UINT32                                                  reserved15;	//0xCCC15150
	UINT32                                                  reserved16;	//0xCCC15154
	UINT32                                                  reserved17;	//0xCCC15158
	UINT32                                                  reserved18;	//0xCCC1515C
	UINT32                                                  reserved19;	//0xCCC15160
	UINT32                                                  reserved20;	//0xCCC15164
	UINT32                                                  reserved21;	//0xCCC15168
	UINT32                                                  reserved22;	//0xCCC1516C
	UINT32                                                  reserved23;	//0xCCC15170
	UINT32                                                  reserved24;	//0xCCC15174
	UINT32                                                  reserved25;	//0xCCC15178
	UINT32                                                  reserved26;	//0xCCC1517C
	UINT32                                                  reserved27;	//0xCCC15180
	UINT32                                                  reserved28;	//0xCCC15184
	UINT32                                                  reserved29;	//0xCCC15188
	UINT32                                                  reserved30;	//0xCCC1518C
	UINT32                                                  reserved31;	//0xCCC15190
	UINT32                                                  reserved32;	//0xCCC15194
	UINT32                                                  reserved33;	//0xCCC15198
	UINT32                                                  reserved34;	//0xCCC1519C
	UINT32                                                  reserved35;	//0xCCC151A0
	UINT32                                                  reserved36;	//0xCCC151A4
	UINT32                                                  reserved37;	//0xCCC151A8
	UINT32                                                  reserved38;	//0xCCC151AC
	UINT32                                                  reserved39;	//0xCCC151B0
	UINT32                                                  reserved40;	//0xCCC151B4
	UINT32                                                  reserved41;	//0xCCC151B8
	UINT32                                                  reserved42;	//0xCCC151BC
	UINT32                                                  reserved43;	//0xCCC151C0
	UINT32                                                  reserved44;	//0xCCC151C4
	UINT32                                                  reserved45;	//0xCCC151C8
	UINT32                                                  reserved46;	//0xCCC151CC
	UINT32                                                  reserved47;	//0xCCC151D0
	UINT32                                                  reserved48;	//0xCCC151D4
	UINT32                                                  reserved49;	//0xCCC151D8
	UINT32                                                  reserved50;	//0xCCC151DC
	UINT32                                                  reserved51;	//0xCCC151E0
	UINT32                                                  reserved52;	//0xCCC151E4
	UINT32                                                  reserved53;	//0xCCC151E8
	UINT32                                                  reserved54;	//0xCCC151EC
	PE_O26_GAV_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCCC151F0
	UINT32                                                  reserved55;	//0xCCC151F4
	UINT32                                                  reserved56;	//0xCCC151F8
	UINT32                                                  reserved57;	//0xCCC151FC
	PE_O26_GAV_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCCC15200
	PE_O26_GAV_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCCC15204
	PE_O26_GAV_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCCC15208
	PE_O26_GAV_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCCC1520C
	PE_O26_GAV_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCCC15210
	PE_O26_GAV_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCCC15214
	PE_O26_GAV_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCCC15218
	PE_O26_GAV_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCCC1521C
	PE_O26_GAV_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCCC15220
	PE_O26_GAV_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCCC15224
	PE_O26_GAV_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCCC15228
	PE_O26_GAV_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCCC1522C
	PE_O26_GAV_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCCC15230
	PE_O26_GAV_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCCC15234
	PE_O26_GAV_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCCC15238
	PE_O26_GAV_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCCC1523C
	PE_O26_GAV_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCCC15240
	PE_O26_GAV_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCCC15244
	PE_O26_GAV_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCCC15248
	PE_O26_GAV_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCCC1524C
	PE_O26_GAV_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCCC15250
	PE_O26_GAV_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCCC15254
	PE_O26_GAV_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCCC15258
	UINT32                                                  reserved58;	//0xCCC1525C
	PE_O26_GAV_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCCC15260
	PE_O26_GAV_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCCC15264
	PE_O26_GAV_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCCC15268
	PE_O26_GAV_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCCC1526C
	PE_O26_GAV_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCCC15270
	PE_O26_GAV_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCCC15274
	PE_O26_GAV_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCCC15278
	PE_O26_GAV_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCCC1527C
	PE_O26_GAV_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCCC15280
	PE_O26_GAV_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCCC15284
	PE_O26_GAV_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCCC15288
	PE_O26_GAV_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCCC1528C
	PE_O26_GAV_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCCC15290
	UINT32                                                  reserved59;	//0xCCC15294
	UINT32                                                  reserved60;	//0xCCC15298
	UINT32                                                  reserved61;	//0xCCC1529C
	UINT32                                                  reserved62;	//0xCCC152A0
	UINT32                                                  reserved63;	//0xCCC152A4
	UINT32                                                  reserved64;	//0xCCC152A8
	UINT32                                                  reserved65;	//0xCCC152AC
	UINT32                                                  reserved66;	//0xCCC152B0
	UINT32                                                  reserved67;	//0xCCC152B4
	UINT32                                                  reserved68;	//0xCCC152B8
	UINT32                                                  reserved69;	//0xCCC152BC
	PE_O26_GAV_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCCC152C0
	PE_O26_GAV_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCCC152C4
	PE_O26_GAV_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCCC152C8
	PE_O26_GAV_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCCC152CC
	PE_O26_GAV_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCCC152D0
	PE_O26_GAV_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCCC152D4
	PE_O26_GAV_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCCC152D8
	PE_O26_GAV_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCCC152DC
	PE_O26_GAV_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCCC152E0
	PE_O26_GAV_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCCC152E4
	PE_O26_GAV_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCCC152E8
	PE_O26_GAV_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCCC152EC
	PE_O26_GAV_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCCC152F0
	PE_O26_GAV_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCCC152F4
	PE_O26_GAV_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCCC152F8
	PE_O26_GAV_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCCC152FC
	PE_O26_GAV_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCCC15300
	PE_O26_GAV_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCCC15304
	PE_O26_GAV_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCCC15308
	PE_O26_GAV_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCCC1530C
	PE_O26_GAV_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCCC15310
	UINT32                                                  reserved70;	//0xCCC15314
	UINT32                                                  reserved71;	//0xCCC15318
	UINT32                                                  reserved72;	//0xCCC1531C
	PE_O26_GAV_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCCC15320
	PE_O26_GAV_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCCC15324
	PE_O26_GAV_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCCC15328
	PE_O26_GAV_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCCC1532C
	PE_O26_GAV_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCCC15330
	UINT32                                                  reserved73;	//0xCCC15334
	UINT32                                                  reserved74;	//0xCCC15338
	UINT32                                                  reserved75;	//0xCCC1533C
	PE_O26_GAV_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCCC15340
	PE_O26_GAV_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCCC15344
	PE_O26_GAV_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCCC15348
	PE_O26_GAV_SHP_TGEN_CTRL_03_T                     shp_tgen_ctrl_03;	//0xCCC1534C
	UINT32                                                  reserved76;	//0xCCC15350
	PE_O26_GAV_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCCC15354
	PE_O26_GAV_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCCC15358
	PE_O26_GAV_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCCC1535C
	PE_O26_GAV_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCCC15360
	PE_O26_GAV_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCCC15364
	PE_O26_GAV_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCCC15368
	PE_O26_GAV_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCCC1536C
	PE_O26_GAV_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCCC15370
	UINT32                                                  reserved77;	//0xCCC15374
	UINT32                                                  reserved78;	//0xCCC15378
	UINT32                                                  reserved79;	//0xCCC1537C
	UINT32                                                  reserved80;	//0xCCC15380
	UINT32                                                  reserved81;	//0xCCC15384
	UINT32                                                  reserved82;	//0xCCC15388
	UINT32                                                  reserved83;	//0xCCC1538C
	UINT32                                                  reserved84;	//0xCCC15390
	UINT32                                                  reserved85;	//0xCCC15394
	UINT32                                                  reserved86;	//0xCCC15398
	UINT32                                                  reserved87;	//0xCCC1539C
	UINT32                                                  reserved88;	//0xCCC153A0
	UINT32                                                  reserved89;	//0xCCC153A4
	UINT32                                                  reserved90;	//0xCCC153A8
	UINT32                                                  reserved91;	//0xCCC153AC
	UINT32                                                  reserved92;	//0xCCC153B0
	UINT32                                                  reserved93;	//0xCCC153B4
	UINT32                                                  reserved94;	//0xCCC153B8
	UINT32                                                  reserved95;	//0xCCC153BC
	UINT32                                                  reserved96;	//0xCCC153C0
	UINT32                                                  reserved97;	//0xCCC153C4
	UINT32                                                  reserved98;	//0xCCC153C8
	UINT32                                                  reserved99;	//0xCCC153CC
	UINT32                                                 reserved100;	//0xCCC153D0
	UINT32                                                 reserved101;	//0xCCC153D4
	UINT32                                                 reserved102;	//0xCCC153D8
	UINT32                                                 reserved103;	//0xCCC153DC
	UINT32                                                 reserved104;	//0xCCC153E0
	UINT32                                                 reserved105;	//0xCCC153E4
	UINT32                                                 reserved106;	//0xCCC153E8
	UINT32                                                 reserved107;	//0xCCC153EC
	UINT32                                                 reserved108;	//0xCCC153F0
	UINT32                                                 reserved109;	//0xCCC153F4
	UINT32                                                 reserved110;	//0xCCC153F8
	UINT32                                                 reserved111;	//0xCCC153FC
	UINT32                                                 reserved112;	//0xCCC15400
	UINT32                                                 reserved113;	//0xCCC15404
	UINT32                                                 reserved114;	//0xCCC15408
	UINT32                                                 reserved115;	//0xCCC1540C
	UINT32                                                 reserved116;	//0xCCC15410
	UINT32                                                 reserved117;	//0xCCC15414
	UINT32                                                 reserved118;	//0xCCC15418
	UINT32                                                 reserved119;	//0xCCC1541C
	UINT32                                                 reserved120;	//0xCCC15420
	UINT32                                                 reserved121;	//0xCCC15424
	UINT32                                                 reserved122;	//0xCCC15428
	UINT32                                                 reserved123;	//0xCCC1542C
	UINT32                                                 reserved124;	//0xCCC15430
	UINT32                                                 reserved125;	//0xCCC15434
	UINT32                                                 reserved126;	//0xCCC15438
	UINT32                                                 reserved127;	//0xCCC1543C
	UINT32                                                 reserved128;	//0xCCC15440
	UINT32                                                 reserved129;	//0xCCC15444
	UINT32                                                 reserved130;	//0xCCC15448
	UINT32                                                 reserved131;	//0xCCC1544C
	UINT32                                                 reserved132;	//0xCCC15450
	UINT32                                                 reserved133;	//0xCCC15454
	UINT32                                                 reserved134;	//0xCCC15458
	UINT32                                                 reserved135;	//0xCCC1545C
	PE_O26_GAV_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCCC15460
	PE_O26_GAV_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCCC15464
	PE_O26_GAV_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCCC15468
	UINT32                                                 reserved136;	//0xCCC1546C
	UINT32                                                 reserved137;	//0xCCC15470
	UINT32                                                 reserved138;	//0xCCC15474
	UINT32                                                 reserved139;	//0xCCC15478
	UINT32                                                 reserved140;	//0xCCC1547C
	UINT32                                                 reserved141;	//0xCCC15480
	UINT32                                                 reserved142;	//0xCCC15484
	UINT32                                                 reserved143;	//0xCCC15488
	UINT32                                                 reserved144;	//0xCCC1548C
	UINT32                                                 reserved145;	//0xCCC15490
	UINT32                                                 reserved146;	//0xCCC15494
	UINT32                                                 reserved147;	//0xCCC15498
	UINT32                                                 reserved148;	//0xCCC1549C
	PE_O26_GAV_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCCC154A0
	PE_O26_GAV_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCCC154A4
	PE_O26_GAV_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCCC154A8
	PE_O26_GAV_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCCC154AC
	PE_O26_GAV_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCCC154B0
	UINT32                                                 reserved149;	//0xCCC154B4
	UINT32                                                 reserved150;	//0xCCC154B8
	UINT32                                                 reserved151;	//0xCCC154BC
	UINT32                                                 reserved152;	//0xCCC154C0
	UINT32                                                 reserved153;	//0xCCC154C4
	UINT32                                                 reserved154;	//0xCCC154C8
	UINT32                                                 reserved155;	//0xCCC154CC
	UINT32                                                 reserved156;	//0xCCC154D0
	UINT32                                                 reserved157;	//0xCCC154D4
	UINT32                                                 reserved158;	//0xCCC154D8
	UINT32                                                 reserved159;	//0xCCC154DC
	UINT32                                                 reserved160;	//0xCCC154E0
	UINT32                                                 reserved161;	//0xCCC154E4
	UINT32                                                 reserved162;	//0xCCC154E8
	UINT32                                                 reserved163;	//0xCCC154EC
	UINT32                                                 reserved164;	//0xCCC154F0
	UINT32                                                 reserved165;	//0xCCC154F4
	UINT32                                                 reserved166;	//0xCCC154F8
	UINT32                                                 reserved167;	//0xCCC154FC
	UINT32                                                 reserved168;	//0xCCC15500
	UINT32                                                 reserved169;	//0xCCC15504
	UINT32                                                 reserved170;	//0xCCC15508
	UINT32                                                 reserved171;	//0xCCC1550C
	UINT32                                                 reserved172;	//0xCCC15510
	UINT32                                                 reserved173;	//0xCCC15514
	UINT32                                                 reserved174;	//0xCCC15518
	UINT32                                                 reserved175;	//0xCCC1551C
	UINT32                                                 reserved176;	//0xCCC15520
	UINT32                                                 reserved177;	//0xCCC15524
	UINT32                                                 reserved178;	//0xCCC15528
	UINT32                                                 reserved179;	//0xCCC1552C
	UINT32                                                 reserved180;	//0xCCC15530
	UINT32                                                 reserved181;	//0xCCC15534
	UINT32                                                 reserved182;	//0xCCC15538
	UINT32                                                 reserved183;	//0xCCC1553C
	UINT32                                                 reserved184;	//0xCCC15540
	UINT32                                                 reserved185;	//0xCCC15544
	UINT32                                                 reserved186;	//0xCCC15548
	UINT32                                                 reserved187;	//0xCCC1554C
	UINT32                                                 reserved188;	//0xCCC15550
	UINT32                                                 reserved189;	//0xCCC15554
	UINT32                                                 reserved190;	//0xCCC15558
	UINT32                                                 reserved191;	//0xCCC1555C
	UINT32                                                 reserved192;	//0xCCC15560
	UINT32                                                 reserved193;	//0xCCC15564
	UINT32                                                 reserved194;	//0xCCC15568
	UINT32                                                 reserved195;	//0xCCC1556C
	UINT32                                                 reserved196;	//0xCCC15570
	UINT32                                                 reserved197;	//0xCCC15574
	UINT32                                                 reserved198;	//0xCCC15578
	UINT32                                                 reserved199;	//0xCCC1557C
	UINT32                                                 reserved200;	//0xCCC15580
	UINT32                                                 reserved201;	//0xCCC15584
	UINT32                                                 reserved202;	//0xCCC15588
	UINT32                                                 reserved203;	//0xCCC1558C
	UINT32                                                 reserved204;	//0xCCC15590
	UINT32                                                 reserved205;	//0xCCC15594
	UINT32                                                 reserved206;	//0xCCC15598
	UINT32                                                 reserved207;	//0xCCC1559C
	UINT32                                                 reserved208;	//0xCCC155A0
	UINT32                                                 reserved209;	//0xCCC155A4
	UINT32                                                 reserved210;	//0xCCC155A8
	UINT32                                                 reserved211;	//0xCCC155AC
	UINT32                                                 reserved212;	//0xCCC155B0
	UINT32                                                 reserved213;	//0xCCC155B4
	UINT32                                                 reserved214;	//0xCCC155B8
	UINT32                                                 reserved215;	//0xCCC155BC
	UINT32                                                 reserved216;	//0xCCC155C0
	UINT32                                                 reserved217;	//0xCCC155C4
	UINT32                                                 reserved218;	//0xCCC155C8
	UINT32                                                 reserved219;	//0xCCC155CC
	UINT32                                                 reserved220;	//0xCCC155D0
	UINT32                                                 reserved221;	//0xCCC155D4
	UINT32                                                 reserved222;	//0xCCC155D8
	UINT32                                                 reserved223;	//0xCCC155DC
	UINT32                                                 reserved224;	//0xCCC155E0
	UINT32                                                 reserved225;	//0xCCC155E4
	UINT32                                                 reserved226;	//0xCCC155E8
	UINT32                                                 reserved227;	//0xCCC155EC
	UINT32                                                 reserved228;	//0xCCC155F0
	UINT32                                                 reserved229;	//0xCCC155F4
	UINT32                                                 reserved230;	//0xCCC155F8
	UINT32                                                 reserved231;	//0xCCC155FC
	UINT32                                                 reserved232;	//0xCCC15600
	UINT32                                                 reserved233;	//0xCCC15604
	UINT32                                                 reserved234;	//0xCCC15608
	UINT32                                                 reserved235;	//0xCCC1560C
	UINT32                                                 reserved236;	//0xCCC15610
	UINT32                                                 reserved237;	//0xCCC15614
	UINT32                                                 reserved238;	//0xCCC15618
	UINT32                                                 reserved239;	//0xCCC1561C
	UINT32                                                 reserved240;	//0xCCC15620
	UINT32                                                 reserved241;	//0xCCC15624
	UINT32                                                 reserved242;	//0xCCC15628
	UINT32                                                 reserved243;	//0xCCC1562C
	UINT32                                                 reserved244;	//0xCCC15630
	UINT32                                                 reserved245;	//0xCCC15634
	UINT32                                                 reserved246;	//0xCCC15638
	UINT32                                                 reserved247;	//0xCCC1563C
	UINT32                                                 reserved248;	//0xCCC15640
	UINT32                                                 reserved249;	//0xCCC15644
	UINT32                                                 reserved250;	//0xCCC15648
	UINT32                                                 reserved251;	//0xCCC1564C
	UINT32                                                 reserved252;	//0xCCC15650
	UINT32                                                 reserved253;	//0xCCC15654
	UINT32                                                 reserved254;	//0xCCC15658
	UINT32                                                 reserved255;	//0xCCC1565C
	UINT32                                                 reserved256;	//0xCCC15660
	UINT32                                                 reserved257;	//0xCCC15664
	UINT32                                                 reserved258;	//0xCCC15668
	UINT32                                                 reserved259;	//0xCCC1566C
	UINT32                                                 reserved260;	//0xCCC15670
	UINT32                                                 reserved261;	//0xCCC15674
	UINT32                                                 reserved262;	//0xCCC15678
	UINT32                                                 reserved263;	//0xCCC1567C
	UINT32                                                 reserved264;	//0xCCC15680
	UINT32                                                 reserved265;	//0xCCC15684
	UINT32                                                 reserved266;	//0xCCC15688
	UINT32                                                 reserved267;	//0xCCC1568C
	UINT32                                                 reserved268;	//0xCCC15690
	UINT32                                                 reserved269;	//0xCCC15694
	UINT32                                                 reserved270;	//0xCCC15698
	UINT32                                                 reserved271;	//0xCCC1569C
	UINT32                                                 reserved272;	//0xCCC156A0
	UINT32                                                 reserved273;	//0xCCC156A4
	UINT32                                                 reserved274;	//0xCCC156A8
	UINT32                                                 reserved275;	//0xCCC156AC
	UINT32                                                 reserved276;	//0xCCC156B0
	UINT32                                                 reserved277;	//0xCCC156B4
	UINT32                                                 reserved278;	//0xCCC156B8
	UINT32                                                 reserved279;	//0xCCC156BC
	UINT32                                                 reserved280;	//0xCCC156C0
	UINT32                                                 reserved281;	//0xCCC156C4
	UINT32                                                 reserved282;	//0xCCC156C8
	UINT32                                                 reserved283;	//0xCCC156CC
	UINT32                                                 reserved284;	//0xCCC156D0
	UINT32                                                 reserved285;	//0xCCC156D4
	UINT32                                                 reserved286;	//0xCCC156D8
	UINT32                                                 reserved287;	//0xCCC156DC
	UINT32                                                 reserved288;	//0xCCC156E0
	UINT32                                                 reserved289;	//0xCCC156E4
	UINT32                                                 reserved290;	//0xCCC156E8
	UINT32                                                 reserved291;	//0xCCC156EC
	UINT32                                                 reserved292;	//0xCCC156F0
	UINT32                                                 reserved293;	//0xCCC156F4
	UINT32                                                 reserved294;	//0xCCC156F8
	UINT32                                                 reserved295;	//0xCCC156FC
	PE_O26_GAV_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCCC15700
	PE_O26_GAV_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCCC15704
	PE_O26_GAV_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCCC15708
	PE_O26_GAV_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCCC1570C
	PE_O26_GAV_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCCC15710
	PE_O26_GAV_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCCC15714
	UINT32                                                 reserved296;	//0xCCC15718
	UINT32                                                 reserved297;	//0xCCC1571C
	UINT32                                                 reserved298;	//0xCCC15720
	UINT32                                                 reserved299;	//0xCCC15724
	UINT32                                                 reserved300;	//0xCCC15728
	UINT32                                                 reserved301;	//0xCCC1572C
	UINT32                                                 reserved302;	//0xCCC15730
	UINT32                                                 reserved303;	//0xCCC15734
	UINT32                                                 reserved304;	//0xCCC15738
	UINT32                                                 reserved305;	//0xCCC1573C
	UINT32                                                 reserved306;	//0xCCC15740
	UINT32                                                 reserved307;	//0xCCC15744
	UINT32                                                 reserved308;	//0xCCC15748
	UINT32                                                 reserved309;	//0xCCC1574C
	UINT32                                                 reserved310;	//0xCCC15750
	UINT32                                                 reserved311;	//0xCCC15754
	UINT32                                                 reserved312;	//0xCCC15758
	UINT32                                                 reserved313;	//0xCCC1575C
	PE_O26_GAV_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCCC15760
	PE_O26_GAV_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCCC15764
	PE_O26_GAV_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCCC15768
	PE_O26_GAV_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCCC1576C
	UINT32                                                 reserved314;	//0xCCC15770
	UINT32                                                 reserved315;	//0xCCC15774
	UINT32                                                 reserved316;	//0xCCC15778
	UINT32                                                 reserved317;	//0xCCC1577C
	UINT32                                                 reserved318;	//0xCCC15780
	UINT32                                                 reserved319;	//0xCCC15784
	UINT32                                                 reserved320;	//0xCCC15788
	UINT32                                                 reserved321;	//0xCCC1578C
	UINT32                                                 reserved322;	//0xCCC15790
	UINT32                                                 reserved323;	//0xCCC15794
	UINT32                                                 reserved324;	//0xCCC15798
	UINT32                                                 reserved325;	//0xCCC1579C
	UINT32                                                 reserved326;	//0xCCC157A0
	UINT32                                                 reserved327;	//0xCCC157A4
	UINT32                                                 reserved328;	//0xCCC157A8
	UINT32                                                 reserved329;	//0xCCC157AC
	UINT32                                                 reserved330;	//0xCCC157B0
	UINT32                                                 reserved331;	//0xCCC157B4
	UINT32                                                 reserved332;	//0xCCC157B8
	UINT32                                                 reserved333;	//0xCCC157BC
	UINT32                                                 reserved334;	//0xCCC157C0
	UINT32                                                 reserved335;	//0xCCC157C4
	UINT32                                                 reserved336;	//0xCCC157C8
	UINT32                                                 reserved337;	//0xCCC157CC
	UINT32                                                 reserved338;	//0xCCC157D0
	UINT32                                                 reserved339;	//0xCCC157D4
	UINT32                                                 reserved340;	//0xCCC157D8
	UINT32                                                 reserved341;	//0xCCC157DC
	UINT32                                                 reserved342;	//0xCCC157E0
	UINT32                                                 reserved343;	//0xCCC157E4
	UINT32                                                 reserved344;	//0xCCC157E8
	UINT32                                                 reserved345;	//0xCCC157EC
	UINT32                                                 reserved346;	//0xCCC157F0
	UINT32                                                 reserved347;	//0xCCC157F4
	UINT32                                                 reserved348;	//0xCCC157F8
	UINT32                                                 reserved349;	//0xCCC157FC
	UINT32                                                 reserved350;	//0xCCC15800
	UINT32                                                 reserved351;	//0xCCC15804
	UINT32                                                 reserved352;	//0xCCC15808
	UINT32                                                 reserved353;	//0xCCC1580C
	UINT32                                                 reserved354;	//0xCCC15810
	UINT32                                                 reserved355;	//0xCCC15814
	UINT32                                                 reserved356;	//0xCCC15818
	UINT32                                                 reserved357;	//0xCCC1581C
	UINT32                                                 reserved358;	//0xCCC15820
	UINT32                                                 reserved359;	//0xCCC15824
	UINT32                                                 reserved360;	//0xCCC15828
	UINT32                                                 reserved361;	//0xCCC1582C
	UINT32                                                 reserved362;	//0xCCC15830
	UINT32                                                 reserved363;	//0xCCC15834
	UINT32                                                 reserved364;	//0xCCC15838
	UINT32                                                 reserved365;	//0xCCC1583C
	UINT32                                                 reserved366;	//0xCCC15840
	UINT32                                                 reserved367;	//0xCCC15844
	UINT32                                                 reserved368;	//0xCCC15848
	UINT32                                                 reserved369;	//0xCCC1584C
	UINT32                                                 reserved370;	//0xCCC15850
	UINT32                                                 reserved371;	//0xCCC15854
	UINT32                                                 reserved372;	//0xCCC15858
	UINT32                                                 reserved373;	//0xCCC1585C
	UINT32                                                 reserved374;	//0xCCC15860
	UINT32                                                 reserved375;	//0xCCC15864
	UINT32                                                 reserved376;	//0xCCC15868
	UINT32                                                 reserved377;	//0xCCC1586C
	UINT32                                                 reserved378;	//0xCCC15870
	UINT32                                                 reserved379;	//0xCCC15874
	UINT32                                                 reserved380;	//0xCCC15878
	UINT32                                                 reserved381;	//0xCCC1587C
	UINT32                                                 reserved382;	//0xCCC15880
	UINT32                                                 reserved383;	//0xCCC15884
	UINT32                                                 reserved384;	//0xCCC15888
	UINT32                                                 reserved385;	//0xCCC1588C
	UINT32                                                 reserved386;	//0xCCC15890
	UINT32                                                 reserved387;	//0xCCC15894
	UINT32                                                 reserved388;	//0xCCC15898
	UINT32                                                 reserved389;	//0xCCC1589C
	UINT32                                                 reserved390;	//0xCCC158A0
	UINT32                                                 reserved391;	//0xCCC158A4
	UINT32                                                 reserved392;	//0xCCC158A8
	UINT32                                                 reserved393;	//0xCCC158AC
	UINT32                                                 reserved394;	//0xCCC158B0
	UINT32                                                 reserved395;	//0xCCC158B4
	UINT32                                                 reserved396;	//0xCCC158B8
	UINT32                                                 reserved397;	//0xCCC158BC
	UINT32                                                 reserved398;	//0xCCC158C0
	UINT32                                                 reserved399;	//0xCCC158C4
	UINT32                                                 reserved400;	//0xCCC158C8
	UINT32                                                 reserved401;	//0xCCC158CC
	UINT32                                                 reserved402;	//0xCCC158D0
	UINT32                                                 reserved403;	//0xCCC158D4
	UINT32                                                 reserved404;	//0xCCC158D8
	UINT32                                                 reserved405;	//0xCCC158DC
	UINT32                                                 reserved406;	//0xCCC158E0
	UINT32                                                 reserved407;	//0xCCC158E4
	UINT32                                                 reserved408;	//0xCCC158E8
	UINT32                                                 reserved409;	//0xCCC158EC
	PE_O26_GAV_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCCC158F0
	PE_O26_GAV_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCCC158F4
	PE_O26_GAV_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCCC158F8
	PE_O26_GAV_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCCC158FC
}PE_GAV_SHP_REG_O26_T;

#endif
