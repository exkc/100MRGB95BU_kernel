#ifndef _PE_SRE_REG_M23A0_H_
#define _PE_SRE_REG_M23A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC570C00 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_M23_2K_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570C04 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570C08 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_M23_2K_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570C0C RW 0x00A9_0000
	UINT32 reg_top_prefetch_cnt             :12;	//(11:0,NA,0) //Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,169) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570C40 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_M23_2K_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570C60 RW 0x1000_0A05
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_GAIN_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570CF0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_M23_2K_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D00 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D08 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_M23_2K_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D0C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D10 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D14 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D18 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D1C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D20 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_M23_2K_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D24 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D28 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_M23_2K_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D2C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_M23_2K_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D30 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_M23_2K_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D34 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_M23_2K_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D38 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D3C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_M23_2K_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D40 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_M23_2K_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D44 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_M23_2K_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D48 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_M23_2K_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D4C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_M23_2K_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D50 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_M23_2K_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D54 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_M23_2K_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D58 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_M23_2K_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D60 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_M23_2K_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D64 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_M23_2K_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D68 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_M23_2K_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D6C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_M23_2K_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D70 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_M23_2K_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D74 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D78 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_M23_2K_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D7C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_M23_2K_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D80 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_M23_2K_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D84 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_M23_2K_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D88 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_M23_2K_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D8C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_2K_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D90 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_2K_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570D94 RW 0x0000_F001
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DA0 RW 0xFFFF_4011
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DA4 RW 0x2020_4030
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DA8 RW 0xFF30_4000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DAC RW 0x0000_0037
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DB0 RW 0x0808_0101
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DC0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_M23_2K_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DC4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_M23_2K_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DC8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_M23_2K_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DCC RW 0x0006_5008
	UINT32 reg_derv_en                      :1;	//(0:0,NA,0) //der-v enable
	UINT32 resvd0                           :2;
	UINT32 reg_derv_bif_en                  :1;	//(3:3,NA,1) //0: disable BiF	1: enable BiF
	UINT32 reg_derv_output_mux              :4;	//(7:4,NA,0) //0xxx: normal display	1000: vertical ringing measure	1001: gain adjusted by curve mapping	101x: bilateral filter output	o.w : not used
	UINT32 reg_derv_bif_manual_th           :8;	//(15:8,NA,80) //bilateral filter threshold
	UINT32 reg_derv_th_gain                 :6;	//(21:16,NA,6) //auto threshold gain, th = th_gain * A
	UINT32 resvd1                           :2;
	UINT32 reg_derv_th_mode                 :1;	//(24:24,NA,0) //th mode	0: auto(A-map)	1: manual
	UINT32 resvd2                           :7;
	};
}PE_M23_2K_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DD0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_M23_2K_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DD4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_M23_2K_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DD8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_M23_2K_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DDC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_M23_2K_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DE0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_M23_2K_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DE4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DE8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_M23_2K_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DEC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_M23_2K_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DF0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_M23_2K_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DF4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DF8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_M23_2K_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570DFC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_M23_2K_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E00 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_M23_2K_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E04 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_M23_2K_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E08 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_M23_2K_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E0C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_2K_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E10 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_2K_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E20 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_M23_2K_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E24 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_M23_2K_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E28 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_2K_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E2C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_2K_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E30 RW 0x1010_2014
	UINT32 reg_sti_enable                   :1;	//(0:0,NA,0) //STI enable
	UINT32 reg_sti_debug_map_en             :1;	//(1:1,NA,0) //debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//(3:2,NA,1) //mm tap size
	UINT32 reg_sti_avg_tap_size             :2;	//(5:4,NA,1) //avg tap size
	UINT32 reg_sti_ti_mode                  :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//(15:8,NA,32) //master gain
	UINT32 reg_sti_texture_gain             :8;	//(23:16,NA,16) //texture gain
	UINT32 reg_sti_edge_gain                :8;	//(31:24,NA,16) //edge gain
	};
}PE_M23_2K_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E40 RW 0x8000_0011
	UINT32 reg_tgen_on_off                  :1;	//(0:0,NA,1) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//(4:4,NA,1) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//(8:8,NA,0) //
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//(19:16,NA,0) //
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//(31:24,NA,128) //
	};
}PE_M23_2K_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E44 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //
	UINT32 resvd3                           :5;
	};
}PE_M23_2K_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E48 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//(21:16,NA,63) //
	UINT32 resvd1                           :10;
	};
}PE_M23_2K_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E4C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //
	};
}PE_M23_2K_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E54 RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio                :3;	//(2:0,NA,4) //
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//(13:8,NA,31) //
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //
	UINT32 resvd3                           :6;
	};
}PE_M23_2K_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E58 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //
	UINT32 resvd2                           :3;
	};
}PE_M23_2K_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E5C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_M23_2K_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E60 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_M23_2K_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E64 RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain           :5;	//(4:0,NA,31) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//(12:8,NA,31) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //
	UINT32 resvd2                           :2;
	};
}PE_M23_2K_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E68 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7                   :4;	//(3:0,NA,15) //
	UINT32 reg_tgen_gain6                   :4;	//(7:4,NA,15) //
	UINT32 reg_tgen_gain5                   :4;	//(11:8,NA,13) //
	UINT32 reg_tgen_gain4                   :4;	//(15:12,NA,12) //
	UINT32 reg_tgen_gain3                   :4;	//(19:16,NA,11) //
	UINT32 reg_tgen_gain2                   :4;	//(23:20,NA,10) //
	UINT32 reg_tgen_gain1                   :4;	//(27:24,NA,8) //
	UINT32 reg_tgen_gain0                   :4;	//(31:28,NA,4) //
	};
}PE_M23_2K_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E6C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_2K_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E70 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_2K_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E74 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_M23_2K_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E80 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_M23_2K_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E84 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E88 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E8C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E90 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E94 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E98 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570E9C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EA0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EA4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EA8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EAC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EB0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EB4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EB8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EBC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EC0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EC4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EC8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570ECC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570ED0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570ED4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570ED8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EDC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EE0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EE4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_M23_2K_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EE8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_M23_2K_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EEC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_M23_2K_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EF0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_M23_2K_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EF4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_M23_2K_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EF8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_2K_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570EFC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_2K_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F00 RW 0x0000_0001
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F04 RW 0x0000_2B38
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F08 RW 0xBDE6_E338
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F0C RW 0xD9F2_01CB
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F10 RW 0x1598_773A
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F14 RW 0x82D2_8A5C
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F2C RW 0x00FF_308C
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F30 RW 0x0E12_0145
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F34 RW 0x01E0_0FEE
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F38 RW 0x0E11_011E
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F3C RW 0x0220_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F40 RW 0x0880_0460
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F44 RW 0x4090_20FF
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F48 RW 0xA400_8040
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F4C RW 0xFF10_088C
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F50 RW 0x0000_0037
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F54 RW 0x1010_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F60 RW 0x0000_0080
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_M23_2K_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F64 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_M23_2K_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570F68 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_M23_2K_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FA0 RW 0x0000_0000
	UINT32 reg_win_dp_win0_en               :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_win_dp_win1_en               :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_win_dp_win01_en              :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dp_win_outside           :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dp_win_en                :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dp_bdr_alpha             :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_win_dp_bdr_wid               :2;	//(14:13,NA,0) //border width
	UINT32 reg_win_dp_bdr_en                :1;	//(15:15,NA,0) //border enable
	UINT32 reg_win_dp_cr5                   :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_win_dp_cb5                   :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_win_dp_yy6                   :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_M23_2K_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FA4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FA8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FAC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FB0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FC0 RW 0x0432_0c40
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FC4 RW 0x0f50_0410
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FC8 RW 0x46c8_2380
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FCC RW 0x0000_ff00
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FD0 RW 0x2840_0a00
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FD4 RW 0x5080_3c60
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FD8 RW 0x08d0_00c0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FDC RW 0x30f0_10e0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FE0 RW 0x80c0_60d0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FE4 RW 0x0870_0080
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FE8 RW 0x1850_1060
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FEC RW 0x4000_2040
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FF4 RW 0x086f_077f
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FF8 RW 0x0000_0780
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570FFC RW 0x0438_0eff
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571000 RW 0x8010_0179
	UINT32 reg_dj_edf_en                    :1;	//(0:0,NA,1) //edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//(1:1,NA,0) //H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//(3:3,NA,1) //edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//(4:4,NA,1) //0: sum of (cur - center)	1:  sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//(5:5,NA,1) //L-type protection
	UINT32 reg_dj_soft_en                   :1;	//(6:6,NA,1) //Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_dj_count_diff_th             :5;	//(12:8,NA,1) //matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//(18:16,NA,0) //000: normal display	001: direction map	010: g0: feature (matchness)	011: g0 : gain	100: g1 : gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_dj_buffer_detour_en          :1;	//(19:19,NA,0) //dj buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//(21:20,NA,1) //center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//(22:22,NA,0) //neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//(23:23,NA,0) //dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//(31:24,NA,128) //line-variation threshold for edge-direction decision
	};
}PE_M23_2K_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571004 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_M23_2K_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571008 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_M23_2K_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57100C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_M23_2K_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571010 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_M23_2K_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571014 RW 0x0000_0000
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
}PE_M23_2K_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571018 RW 0x0000_0040
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
}PE_M23_2K_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57101C RW 0x0015_5550
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
}PE_M23_2K_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571020 RW 0x0000_0040
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
}PE_M23_2K_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571024 RW 0x002A_A040
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
}PE_M23_2K_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571028 RW 0x002A_A040
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
}PE_M23_2K_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57102C RW 0x000A_A040
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
}PE_M23_2K_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571030 RW 0x0000_00E4
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
}PE_M23_2K_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571034 RW 0x0000_5540
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
}PE_M23_2K_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571038 RW 0x0020_5542
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
}PE_M23_2K_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57103C RW 0x0008_1508
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
}PE_M23_2K_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571040 RW 0x0002_0420
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
}PE_M23_2K_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571044 RW 0x0000_8080
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
}PE_M23_2K_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571048 RW 0x0000_2A00
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
}PE_M23_2K_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57104C RW 0x0000_2A00
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
}PE_M23_2K_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571050 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_M23_2K_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571054 RW 0x0000_2800
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
}PE_M23_2K_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571058 RW 0x0005_0A00
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
}PE_M23_2K_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57105C RW 0x0005_4280
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
}PE_M23_2K_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571060 RW 0x0005_50A0
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
}PE_M23_2K_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571064 RW 0x0005_4280
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
}PE_M23_2K_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571068 RW 0x0005_0A00
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
}PE_M23_2K_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57106C RW 0x0000_2800
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
}PE_M23_2K_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571070 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_M23_2K_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571074 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571078 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57107C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_M23_2K_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571080 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_M23_2K_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571090 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571094 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710A0 RW 0x0000_0000
	UINT32 reg_win_dj_win0_en               :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_win_dj_win1_en               :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_win_dj_win01_en              :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dj_win_outside           :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dj_win_en                :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dj_bdr_alpha             :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_win_dj_bdr_wid               :2;	//(14:13,NA,0) //border width
	UINT32 reg_win_dj_bdr_en                :1;	//(15:15,NA,0) //border enable
	UINT32 reg_win_dj_cr5                   :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_win_dj_cb5                   :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_win_dj_yy6                   :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_M23_2K_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710A8 RW 0x0437_077F
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710B0 RW 0x0437_077F
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710C0 RW 0x10BC_4DB3
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710C4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710C8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710CC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710D0 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710D4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710D8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710DC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710E0 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710E4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710E8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710EC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710F0 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710F4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710F8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5710FC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571100 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571200 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571204 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571208 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57120C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_M23_2K_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571210 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_M23_2K_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571214 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_M23_2K_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571260 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571264 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571268 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57126C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571300 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571304 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571308 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57130C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571310 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571314 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC571318 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57131C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC413F0 RW 0x0000_0000
	UINT32 cvd_pattern_detect				:1;
	UINT32 color_bar						:1;
	UINT32 vfy_glb_en						:1;
	UINT32 resvd							:29;
	};
}PE_M23_2K_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5713F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5713F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5713FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_2K_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_M23_2K_SHP_CORE_CTRL_00_T                      shp_core_ctrl_00;	//0xCC570C00
	PE_M23_2K_SHP_CORE_CTRL_01_T                      shp_core_ctrl_01;	//0xCC570C04
	PE_M23_2K_SHP_CORE_CTRL_02_T                      shp_core_ctrl_02;	//0xCC570C08
	PE_M23_2K_SHP_CORE_CTRL_03_T                      shp_core_ctrl_03;	//0xCC570C0C
	UINT32                                                    reserved0;	//0xCC570C10
	UINT32                                                    reserved1;	//0xCC570C14
	UINT32                                                    reserved2;	//0xCC570C18
	UINT32                                                    reserved3;	//0xCC570C1C
	UINT32                                                    reserved4;	//0xCC570C20
	UINT32                                                    reserved5;	//0xCC570C24
	UINT32                                                    reserved6;	//0xCC570C28
	UINT32                                                    reserved7;	//0xCC570C2C
	UINT32                                                    reserved8;	//0xCC570C30
	UINT32                                                    reserved9;	//0xCC570C34
	UINT32                                                   reserved10;	//0xCC570C38
	UINT32                                                   reserved11;	//0xCC570C3C
	PE_M23_2K_SHP_PAT_GEN_CTRL_00_T                shp_pat_gen_ctrl_00;	//0xCC570C40
	UINT32                                                   reserved12;	//0xCC570C44
	UINT32                                                   reserved13;	//0xCC570C48
	UINT32                                                   reserved14;	//0xCC570C4C
	UINT32                                                   reserved15;	//0xCC570C50
	UINT32                                                   reserved16;	//0xCC570C54
	UINT32                                                   reserved17;	//0xCC570C58
	UINT32                                                   reserved18;	//0xCC570C5C
	PE_M23_2K_SHP_GAIN_MAP_CTRL_00_T              shp_gain_map_ctrl_00;	//0xCC570C60
	UINT32                                                   reserved19;	//0xCC570C64
	UINT32                                                   reserved20;	//0xCC570C68
	UINT32                                                   reserved21;	//0xCC570C6C
	UINT32                                                   reserved22;	//0xCC570C70
	UINT32                                                   reserved23;	//0xCC570C74
	UINT32                                                   reserved24;	//0xCC570C78
	UINT32                                                   reserved25;	//0xCC570C7C
	UINT32                                                   reserved26;	//0xCC570C80
	UINT32                                                   reserved27;	//0xCC570C84
	UINT32                                                   reserved28;	//0xCC570C88
	UINT32                                                   reserved29;	//0xCC570C8C
	UINT32                                                   reserved30;	//0xCC570C90
	UINT32                                                   reserved31;	//0xCC570C94
	UINT32                                                   reserved32;	//0xCC570C98
	UINT32                                                   reserved33;	//0xCC570C9C
	UINT32                                                   reserved34;	//0xCC570CA0
	UINT32                                                   reserved35;	//0xCC570CA4
	UINT32                                                   reserved36;	//0xCC570CA8
	UINT32                                                   reserved37;	//0xCC570CAC
	UINT32                                                   reserved38;	//0xCC570CB0
	UINT32                                                   reserved39;	//0xCC570CB4
	UINT32                                                   reserved40;	//0xCC570CB8
	UINT32                                                   reserved41;	//0xCC570CBC
	UINT32                                                   reserved42;	//0xCC570CC0
	UINT32                                                   reserved43;	//0xCC570CC4
	UINT32                                                   reserved44;	//0xCC570CC8
	UINT32                                                   reserved45;	//0xCC570CCC
	UINT32                                                   reserved46;	//0xCC570CD0
	UINT32                                                   reserved47;	//0xCC570CD4
	UINT32                                                   reserved48;	//0xCC570CD8
	UINT32                                                   reserved49;	//0xCC570CDC
	UINT32                                                   reserved50;	//0xCC570CE0
	UINT32                                                   reserved51;	//0xCC570CE4
	UINT32                                                   reserved52;	//0xCC570CE8
	UINT32                                                   reserved53;	//0xCC570CEC
	PE_M23_2K_SHP_DP_CTRL_00_T                          shp_dp_ctrl_00;	//0xCC570CF0
	UINT32                                                   reserved54;	//0xCC570CF4
	UINT32                                                   reserved55;	//0xCC570CF8
	UINT32                                                   reserved56;	//0xCC570CFC
	PE_M23_2K_SHP_FD_CTRL_00_T                          shp_fd_ctrl_00;	//0xCC570D00
	PE_M23_2K_SHP_FD_CTRL_01_T                          shp_fd_ctrl_01;	//0xCC570D04
	PE_M23_2K_SHP_FD_CTRL_02_T                          shp_fd_ctrl_02;	//0xCC570D08
	PE_M23_2K_SHP_FD_CTRL_03_T                          shp_fd_ctrl_03;	//0xCC570D0C
	PE_M23_2K_SHP_FD_CTRL_04_T                          shp_fd_ctrl_04;	//0xCC570D10
	PE_M23_2K_SHP_FD_CTRL_05_T                          shp_fd_ctrl_05;	//0xCC570D14
	PE_M23_2K_SHP_FD_CTRL_06_T                          shp_fd_ctrl_06;	//0xCC570D18
	PE_M23_2K_SHP_FD_CTRL_07_T                          shp_fd_ctrl_07;	//0xCC570D1C
	PE_M23_2K_SHP_FD_CTRL_08_T                          shp_fd_ctrl_08;	//0xCC570D20
	PE_M23_2K_SHP_FD_CTRL_09_T                          shp_fd_ctrl_09;	//0xCC570D24
	PE_M23_2K_SHP_FD_CTRL_0A_T                          shp_fd_ctrl_0a;	//0xCC570D28
	PE_M23_2K_SHP_FD_CTRL_0B_T                          shp_fd_ctrl_0b;	//0xCC570D2C
	PE_M23_2K_SHP_FD_CTRL_0C_T                          shp_fd_ctrl_0c;	//0xCC570D30
	PE_M23_2K_SHP_FD_CTRL_0D_T                          shp_fd_ctrl_0d;	//0xCC570D34
	PE_M23_2K_SHP_FD_CTRL_0E_T                          shp_fd_ctrl_0e;	//0xCC570D38
	PE_M23_2K_SHP_FD_CTRL_0F_T                          shp_fd_ctrl_0f;	//0xCC570D3C
	PE_M23_2K_SHP_FD_CTRL_10_T                          shp_fd_ctrl_10;	//0xCC570D40
	PE_M23_2K_SHP_FD_CTRL_11_T                          shp_fd_ctrl_11;	//0xCC570D44
	PE_M23_2K_SHP_FD_CTRL_12_T                          shp_fd_ctrl_12;	//0xCC570D48
	PE_M23_2K_SHP_FD_CTRL_13_T                          shp_fd_ctrl_13;	//0xCC570D4C
	PE_M23_2K_SHP_FD_CTRL_14_T                          shp_fd_ctrl_14;	//0xCC570D50
	PE_M23_2K_SHP_FD_CTRL_15_T                          shp_fd_ctrl_15;	//0xCC570D54
	PE_M23_2K_SHP_FD_CTRL_16_T                          shp_fd_ctrl_16;	//0xCC570D58
	UINT32                                                   reserved57;	//0xCC570D5C
	PE_M23_2K_SHP_MP_CTRL_00_T                          shp_mp_ctrl_00;	//0xCC570D60
	PE_M23_2K_SHP_MP_CTRL_01_T                          shp_mp_ctrl_01;	//0xCC570D64
	PE_M23_2K_SHP_MP_CTRL_02_T                          shp_mp_ctrl_02;	//0xCC570D68
	PE_M23_2K_SHP_MP_CTRL_03_T                          shp_mp_ctrl_03;	//0xCC570D6C
	PE_M23_2K_SHP_MP_CTRL_04_T                          shp_mp_ctrl_04;	//0xCC570D70
	PE_M23_2K_SHP_MP_CTRL_05_T                          shp_mp_ctrl_05;	//0xCC570D74
	PE_M23_2K_SHP_MP_CTRL_06_T                          shp_mp_ctrl_06;	//0xCC570D78
	PE_M23_2K_SHP_MP_CTRL_07_T                          shp_mp_ctrl_07;	//0xCC570D7C
	PE_M23_2K_SHP_MP_CTRL_08_T                          shp_mp_ctrl_08;	//0xCC570D80
	PE_M23_2K_SHP_MP_CTRL_09_T                          shp_mp_ctrl_09;	//0xCC570D84
	PE_M23_2K_SHP_MP_CTRL_0A_T                          shp_mp_ctrl_0a;	//0xCC570D88
	PE_M23_2K_SHP_MP_CTRL_0B_T                          shp_mp_ctrl_0b;	//0xCC570D8C
	PE_M23_2K_SHP_MP_CTRL_0C_T                          shp_mp_ctrl_0c;	//0xCC570D90
	PE_M23_2K_SHP_APL_CTRL_00_T                        shp_apl_ctrl_00;	//0xCC570D94
	UINT32                                                   reserved58;	//0xCC570D98
	UINT32                                                   reserved59;	//0xCC570D9C
	PE_M23_2K_SHP_LC_CTRL_00_T                          shp_lc_ctrl_00;	//0xCC570DA0
	PE_M23_2K_SHP_LC_CTRL_01_T                          shp_lc_ctrl_01;	//0xCC570DA4
	PE_M23_2K_SHP_LC_CTRL_02_T                          shp_lc_ctrl_02;	//0xCC570DA8
	PE_M23_2K_SHP_LC_CTRL_03_T                          shp_lc_ctrl_03;	//0xCC570DAC
	PE_M23_2K_SHP_LC_CTRL_04_T                          shp_lc_ctrl_04;	//0xCC570DB0
	UINT32                                                   reserved60;	//0xCC570DB4
	UINT32                                                   reserved61;	//0xCC570DB8
	UINT32                                                   reserved62;	//0xCC570DBC
	PE_M23_2K_SHP_DER_CTRL_00_T                        shp_der_ctrl_00;	//0xCC570DC0
	PE_M23_2K_SHP_DER_CTRL_01_T                        shp_der_ctrl_01;	//0xCC570DC4
	PE_M23_2K_SHP_DER_CTRL_02_T                        shp_der_ctrl_02;	//0xCC570DC8
	PE_M23_2K_SHP_DER_CTRL_03_T                        shp_der_ctrl_03;	//0xCC570DCC
	PE_M23_2K_SHP_DER_CTRL_04_T                        shp_der_ctrl_04;	//0xCC570DD0
	PE_M23_2K_SHP_DER_CTRL_05_T                        shp_der_ctrl_05;	//0xCC570DD4
	PE_M23_2K_SHP_DER_CTRL_06_T                        shp_der_ctrl_06;	//0xCC570DD8
	PE_M23_2K_SHP_DER_CTRL_07_T                        shp_der_ctrl_07;	//0xCC570DDC
	PE_M23_2K_SHP_SP_CTRL_00_T                          shp_sp_ctrl_00;	//0xCC570DE0
	PE_M23_2K_SHP_SP_CTRL_01_T                          shp_sp_ctrl_01;	//0xCC570DE4
	PE_M23_2K_SHP_SP_CTRL_02_T                          shp_sp_ctrl_02;	//0xCC570DE8
	PE_M23_2K_SHP_SP_CTRL_03_T                          shp_sp_ctrl_03;	//0xCC570DEC
	PE_M23_2K_SHP_SP_CTRL_04_T                          shp_sp_ctrl_04;	//0xCC570DF0
	PE_M23_2K_SHP_SP_CTRL_05_T                          shp_sp_ctrl_05;	//0xCC570DF4
	PE_M23_2K_SHP_SP_CTRL_06_T                          shp_sp_ctrl_06;	//0xCC570DF8
	PE_M23_2K_SHP_SP_CTRL_07_T                          shp_sp_ctrl_07;	//0xCC570DFC
	PE_M23_2K_SHP_SP_CTRL_08_T                          shp_sp_ctrl_08;	//0xCC570E00
	PE_M23_2K_SHP_SP_CTRL_09_T                          shp_sp_ctrl_09;	//0xCC570E04
	PE_M23_2K_SHP_SP_CTRL_0A_T                          shp_sp_ctrl_0a;	//0xCC570E08
	PE_M23_2K_SHP_SP_CTRL_0B_T                          shp_sp_ctrl_0b;	//0xCC570E0C
	PE_M23_2K_SHP_SP_CTRL_0C_T                          shp_sp_ctrl_0c;	//0xCC570E10
	UINT32                                                   reserved63;	//0xCC570E14
	UINT32                                                   reserved64;	//0xCC570E18
	UINT32                                                   reserved65;	//0xCC570E1C
	PE_M23_2K_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0xCC570E20
	PE_M23_2K_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0xCC570E24
	PE_M23_2K_SHP_PTI_CTRL_02_T                        shp_pti_ctrl_02;	//0xCC570E28
	PE_M23_2K_SHP_PTI_CTRL_03_T                        shp_pti_ctrl_03;	//0xCC570E2C
	PE_M23_2K_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0xCC570E30
	UINT32                                                   reserved66;	//0xCC570E34
	UINT32                                                   reserved67;	//0xCC570E38
	UINT32                                                   reserved68;	//0xCC570E3C
	PE_M23_2K_SHP_TGEN_CTRL_00_T                      shp_tgen_ctrl_00;	//0xCC570E40
	PE_M23_2K_SHP_TGEN_CTRL_01_T                      shp_tgen_ctrl_01;	//0xCC570E44
	PE_M23_2K_SHP_TGEN_CTRL_02_T                      shp_tgen_ctrl_02;	//0xCC570E48
	PE_M23_2K_SHP_TGEN_CTRL_03_T                      shp_tgen_ctrl_03;	//0xCC570E4C
	UINT32                                                   reserved69;	//0xCC570E50
	PE_M23_2K_SHP_TGEN_CTRL_04_T                      shp_tgen_ctrl_04;	//0xCC570E54
	PE_M23_2K_SHP_TGEN_CTRL_05_T                      shp_tgen_ctrl_05;	//0xCC570E58
	PE_M23_2K_SHP_TGEN_CTRL_06_T                      shp_tgen_ctrl_06;	//0xCC570E5C
	PE_M23_2K_SHP_TGEN_CTRL_07_T                      shp_tgen_ctrl_07;	//0xCC570E60
	PE_M23_2K_SHP_TGEN_CTRL_08_T                      shp_tgen_ctrl_08;	//0xCC570E64
	PE_M23_2K_SHP_TGEN_CTRL_09_T                      shp_tgen_ctrl_09;	//0xCC570E68
	PE_M23_2K_SHP_TGEN_CTRL_0A_T                      shp_tgen_ctrl_0a;	//0xCC570E6C
	PE_M23_2K_SHP_TGEN_CTRL_0B_T                      shp_tgen_ctrl_0b;	//0xCC570E70
	PE_M23_2K_SHP_SNR_CTRL_00_T                        shp_snr_ctrl_00;	//0xCC570E74
	UINT32                                                   reserved70;	//0xCC570E78
	UINT32                                                   reserved71;	//0xCC570E7C
	PE_M23_2K_SHP_DCTP_CTRL_00_T                      shp_dctp_ctrl_00;	//0xCC570E80
	PE_M23_2K_SHP_DCTP_CTRL_01_T                      shp_dctp_ctrl_01;	//0xCC570E84
	PE_M23_2K_SHP_DCTP_CTRL_02_T                      shp_dctp_ctrl_02;	//0xCC570E88
	PE_M23_2K_SHP_DCTP_CTRL_03_T                      shp_dctp_ctrl_03;	//0xCC570E8C
	PE_M23_2K_SHP_DCTP_CTRL_04_T                      shp_dctp_ctrl_04;	//0xCC570E90
	PE_M23_2K_SHP_DCTP_CTRL_05_T                      shp_dctp_ctrl_05;	//0xCC570E94
	PE_M23_2K_SHP_DCTP_CTRL_06_T                      shp_dctp_ctrl_06;	//0xCC570E98
	PE_M23_2K_SHP_DCTP_CTRL_07_T                      shp_dctp_ctrl_07;	//0xCC570E9C
	PE_M23_2K_SHP_DCTP_CTRL_08_T                      shp_dctp_ctrl_08;	//0xCC570EA0
	PE_M23_2K_SHP_DCTP_CTRL_09_T                      shp_dctp_ctrl_09;	//0xCC570EA4
	PE_M23_2K_SHP_DCTP_CTRL_0A_T                      shp_dctp_ctrl_0a;	//0xCC570EA8
	PE_M23_2K_SHP_DCTP_CTRL_0B_T                      shp_dctp_ctrl_0b;	//0xCC570EAC
	PE_M23_2K_SHP_DCTP_CTRL_0C_T                      shp_dctp_ctrl_0c;	//0xCC570EB0
	PE_M23_2K_SHP_DCTP_CTRL_0D_T                      shp_dctp_ctrl_0d;	//0xCC570EB4
	PE_M23_2K_SHP_DCTP_CTRL_0E_T                      shp_dctp_ctrl_0e;	//0xCC570EB8
	PE_M23_2K_SHP_DCTP_CTRL_0F_T                      shp_dctp_ctrl_0f;	//0xCC570EBC
	PE_M23_2K_SHP_DCTP_CTRL_10_T                      shp_dctp_ctrl_10;	//0xCC570EC0
	PE_M23_2K_SHP_DCTP_CTRL_11_T                      shp_dctp_ctrl_11;	//0xCC570EC4
	PE_M23_2K_SHP_DCTP_CTRL_12_T                      shp_dctp_ctrl_12;	//0xCC570EC8
	PE_M23_2K_SHP_DCTP_CTRL_13_T                      shp_dctp_ctrl_13;	//0xCC570ECC
	PE_M23_2K_SHP_DCTP_CTRL_14_T                      shp_dctp_ctrl_14;	//0xCC570ED0
	PE_M23_2K_SHP_DCTP_CTRL_15_T                      shp_dctp_ctrl_15;	//0xCC570ED4
	PE_M23_2K_SHP_DCTP_CTRL_16_T                      shp_dctp_ctrl_16;	//0xCC570ED8
	PE_M23_2K_SHP_DCTP_CTRL_17_T                      shp_dctp_ctrl_17;	//0xCC570EDC
	PE_M23_2K_SHP_DCTP_CTRL_18_T                      shp_dctp_ctrl_18;	//0xCC570EE0
	PE_M23_2K_SHP_DCTP_CTRL_19_T                      shp_dctp_ctrl_19;	//0xCC570EE4
	PE_M23_2K_SHP_DCTP_CTRL_1A_T                      shp_dctp_ctrl_1a;	//0xCC570EE8
	PE_M23_2K_SHP_DCTP_CTRL_1B_T                      shp_dctp_ctrl_1b;	//0xCC570EEC
	PE_M23_2K_SHP_DCTP_CTRL_1C_T                      shp_dctp_ctrl_1c;	//0xCC570EF0
	PE_M23_2K_SHP_DCTP_CTRL_1D_T                      shp_dctp_ctrl_1d;	//0xCC570EF4
	PE_M23_2K_SHP_DCTP_CTRL_1E_T                      shp_dctp_ctrl_1e;	//0xCC570EF8
	PE_M23_2K_SHP_DCTP_CTRL_1F_T                      shp_dctp_ctrl_1f;	//0xCC570EFC
	PE_M23_2K_SHP_NNTG_CTRL_00_T                      shp_nntg_ctrl_00;	//0xCC570F00
	PE_M23_2K_SHP_NNTG_CTRL_01_T                      shp_nntg_ctrl_01;	//0xCC570F04
	PE_M23_2K_SHP_NNTG_CTRL_02_T                      shp_nntg_ctrl_02;	//0xCC570F08
	PE_M23_2K_SHP_NNTG_CTRL_03_T                      shp_nntg_ctrl_03;	//0xCC570F0C
	PE_M23_2K_SHP_NNTG_CTRL_04_T                      shp_nntg_ctrl_04;	//0xCC570F10
	PE_M23_2K_SHP_NNTG_CTRL_05_T                      shp_nntg_ctrl_05;	//0xCC570F14
	UINT32                                                   reserved72;	//0xCC570F18
	UINT32                                                   reserved73;	//0xCC570F1C
	UINT32                                                   reserved74;	//0xCC570F20
	UINT32                                                   reserved75;	//0xCC570F24
	UINT32                                                   reserved76;	//0xCC570F28
	PE_M23_2K_SHP_NNTG_CTRL_06_T                      shp_nntg_ctrl_06;	//0xCC570F2C
	PE_M23_2K_SHP_NNTG_CTRL_07_T                      shp_nntg_ctrl_07;	//0xCC570F30
	PE_M23_2K_SHP_NNTG_CTRL_08_T                      shp_nntg_ctrl_08;	//0xCC570F34
	PE_M23_2K_SHP_NNTG_CTRL_09_T                      shp_nntg_ctrl_09;	//0xCC570F38
	PE_M23_2K_SHP_NNTG_CTRL_0A_T                      shp_nntg_ctrl_0a;	//0xCC570F3C
	PE_M23_2K_SHP_NNTG_CTRL_0B_T                      shp_nntg_ctrl_0b;	//0xCC570F40
	PE_M23_2K_SHP_NNTG_CTRL_0C_T                      shp_nntg_ctrl_0c;	//0xCC570F44
	PE_M23_2K_SHP_NNTG_CTRL_0D_T                      shp_nntg_ctrl_0d;	//0xCC570F48
	PE_M23_2K_SHP_NNTG_CTRL_0E_T                      shp_nntg_ctrl_0e;	//0xCC570F4C
	PE_M23_2K_SHP_NNTG_CTRL_0F_T                      shp_nntg_ctrl_0f;	//0xCC570F50
	PE_M23_2K_SHP_NNTG_CTRL_10_T                      shp_nntg_ctrl_10;	//0xCC570F54
	UINT32                                                   reserved77;	//0xCC570F58
	UINT32                                                   reserved78;	//0xCC570F5C
	PE_M23_2K_SHP_DP_SUM_CTRL_00_T                  shp_dp_sum_ctrl_00;	//0xCC570F60
	PE_M23_2K_SHP_DP_SUM_CTRL_01_T                  shp_dp_sum_ctrl_01;	//0xCC570F64
	PE_M23_2K_SHP_DP_SUM_CTRL_02_T                  shp_dp_sum_ctrl_02;	//0xCC570F68
	UINT32                                                   reserved79;	//0xCC570F6C
	UINT32                                                   reserved80;	//0xCC570F70
	UINT32                                                   reserved81;	//0xCC570F74
	UINT32                                                   reserved82;	//0xCC570F78
	UINT32                                                   reserved83;	//0xCC570F7C
	UINT32                                                   reserved84;	//0xCC570F80
	UINT32                                                   reserved85;	//0xCC570F84
	UINT32                                                   reserved86;	//0xCC570F88
	UINT32                                                   reserved87;	//0xCC570F8C
	UINT32                                                   reserved88;	//0xCC570F90
	UINT32                                                   reserved89;	//0xCC570F94
	UINT32                                                   reserved90;	//0xCC570F98
	UINT32                                                   reserved91;	//0xCC570F9C
	PE_M23_2K_SHP_DP_WIN_CTRL_00_T                  shp_dp_win_ctrl_00;	//0xCC570FA0
	PE_M23_2K_SHP_DP_WIN_CTRL_01_T                  shp_dp_win_ctrl_01;	//0xCC570FA4
	PE_M23_2K_SHP_DP_WIN_CTRL_02_T                  shp_dp_win_ctrl_02;	//0xCC570FA8
	PE_M23_2K_SHP_DP_WIN_CTRL_03_T                  shp_dp_win_ctrl_03;	//0xCC570FAC
	PE_M23_2K_SHP_DP_WIN_CTRL_04_T                  shp_dp_win_ctrl_04;	//0xCC570FB0
	UINT32                                                   reserved92;	//0xCC570FB4
	UINT32                                                   reserved93;	//0xCC570FB8
	UINT32                                                   reserved94;	//0xCC570FBC
	PE_M23_2K_SHP_FD_REGION_TEXT_00_T            shp_fd_region_text_00;	//0xCC570FC0
	PE_M23_2K_SHP_FD_REGION_TEXT_01_T            shp_fd_region_text_01;	//0xCC570FC4
	PE_M23_2K_SHP_FD_REGION_TEXT_02_T            shp_fd_region_text_02;	//0xCC570FC8
	PE_M23_2K_SHP_FD_TMAP_TEMP_00_T                shp_fd_tmap_temp_00;	//0xCC570FCC
	PE_M23_2K_SHP_FD_TMAP_TEMP_01_T                shp_fd_tmap_temp_01;	//0xCC570FD0
	PE_M23_2K_SHP_FD_TMAP_TEMP_02_T                shp_fd_tmap_temp_02;	//0xCC570FD4
	PE_M23_2K_SHP_FD_TMAP_TEMP_03_T                shp_fd_tmap_temp_03;	//0xCC570FD8
	PE_M23_2K_SHP_FD_TMAP_TEMP_04_T                shp_fd_tmap_temp_04;	//0xCC570FDC
	PE_M23_2K_SHP_FD_TMAP_TEMP_05_T                shp_fd_tmap_temp_05;	//0xCC570FE0
	PE_M23_2K_SHP_FD_TMAP_TEMP_06_T                shp_fd_tmap_temp_06;	//0xCC570FE4
	PE_M23_2K_SHP_FD_TMAP_TEMP_07_T                shp_fd_tmap_temp_07;	//0xCC570FE8
	PE_M23_2K_SHP_FD_TMAP_TEMP_08_T                shp_fd_tmap_temp_08;	//0xCC570FEC
	PE_M23_2K_SHP_FD_TMAP_TEMP_09_T                shp_fd_tmap_temp_09;	//0xCC570FF0
	PE_M23_2K_SHP_FD_TMAP_TEMP_0A_T                shp_fd_tmap_temp_0a;	//0xCC570FF4
	PE_M23_2K_SHP_FD_TMAP_TEMP_0B_T                shp_fd_tmap_temp_0b;	//0xCC570FF8
	PE_M23_2K_SHP_FD_TMAP_TEMP_0C_T                shp_fd_tmap_temp_0c;	//0xCC570FFC
	PE_M23_2K_SHP_DJ_CTRL_00_T                          shp_dj_ctrl_00;	//0xCC571000
	PE_M23_2K_SHP_DJ_CTRL_01_T                          shp_dj_ctrl_01;	//0xCC571004
	PE_M23_2K_SHP_DJ_CTRL_02_T                          shp_dj_ctrl_02;	//0xCC571008
	PE_M23_2K_SHP_DJ_CTRL_03_T                          shp_dj_ctrl_03;	//0xCC57100C
	PE_M23_2K_SHP_DJ_CTRL_04_T                          shp_dj_ctrl_04;	//0xCC571010
	PE_M23_2K_SHP_DJ_CTRL_05_T                          shp_dj_ctrl_05;	//0xCC571014
	PE_M23_2K_SHP_DJ_CTRL_06_T                          shp_dj_ctrl_06;	//0xCC571018
	PE_M23_2K_SHP_DJ_CTRL_07_T                          shp_dj_ctrl_07;	//0xCC57101C
	PE_M23_2K_SHP_DJ_CTRL_08_T                          shp_dj_ctrl_08;	//0xCC571020
	PE_M23_2K_SHP_DJ_CTRL_09_T                          shp_dj_ctrl_09;	//0xCC571024
	PE_M23_2K_SHP_DJ_CTRL_0A_T                          shp_dj_ctrl_0a;	//0xCC571028
	PE_M23_2K_SHP_DJ_CTRL_0B_T                          shp_dj_ctrl_0b;	//0xCC57102C
	PE_M23_2K_SHP_DJ_CTRL_0C_T                          shp_dj_ctrl_0c;	//0xCC571030
	PE_M23_2K_SHP_DJ_CTRL_0D_T                          shp_dj_ctrl_0d;	//0xCC571034
	PE_M23_2K_SHP_DJ_CTRL_0E_T                          shp_dj_ctrl_0e;	//0xCC571038
	PE_M23_2K_SHP_DJ_CTRL_0F_T                          shp_dj_ctrl_0f;	//0xCC57103C
	PE_M23_2K_SHP_DJ_CTRL_10_T                          shp_dj_ctrl_10;	//0xCC571040
	PE_M23_2K_SHP_DJ_CTRL_11_T                          shp_dj_ctrl_11;	//0xCC571044
	PE_M23_2K_SHP_DJ_CTRL_12_T                          shp_dj_ctrl_12;	//0xCC571048
	PE_M23_2K_SHP_DJ_CTRL_13_T                          shp_dj_ctrl_13;	//0xCC57104C
	PE_M23_2K_SHP_DJ_CTRL_14_T                          shp_dj_ctrl_14;	//0xCC571050
	PE_M23_2K_SHP_DJ_CTRL_15_T                          shp_dj_ctrl_15;	//0xCC571054
	PE_M23_2K_SHP_DJ_CTRL_16_T                          shp_dj_ctrl_16;	//0xCC571058
	PE_M23_2K_SHP_DJ_CTRL_17_T                          shp_dj_ctrl_17;	//0xCC57105C
	PE_M23_2K_SHP_DJ_CTRL_18_T                          shp_dj_ctrl_18;	//0xCC571060
	PE_M23_2K_SHP_DJ_CTRL_19_T                          shp_dj_ctrl_19;	//0xCC571064
	PE_M23_2K_SHP_DJ_CTRL_1A_T                          shp_dj_ctrl_1a;	//0xCC571068
	PE_M23_2K_SHP_DJ_CTRL_1B_T                          shp_dj_ctrl_1b;	//0xCC57106C
	PE_M23_2K_SHP_DJ_CTRL_1C_T                          shp_dj_ctrl_1c;	//0xCC571070
	PE_M23_2K_SHP_DJ_CTRL_1D_T                          shp_dj_ctrl_1d;	//0xCC571074
	PE_M23_2K_SHP_DJ_CTRL_1E_T                          shp_dj_ctrl_1e;	//0xCC571078
	PE_M23_2K_SHP_DJ_CTRL_1F_T                          shp_dj_ctrl_1f;	//0xCC57107C
	PE_M23_2K_SHP_DJ_CTRL_20_T                          shp_dj_ctrl_20;	//0xCC571080
	UINT32                                                   reserved95;	//0xCC571084
	UINT32                                                   reserved96;	//0xCC571088
	UINT32                                                   reserved97;	//0xCC57108C
	PE_M23_2K_SHP_DB_CTRL_00_T                          shp_db_ctrl_00;	//0xCC571090
	PE_M23_2K_SHP_DB_CTRL_01_T                          shp_db_ctrl_01;	//0xCC571094
	UINT32                                                   reserved98;	//0xCC571098
	UINT32                                                   reserved99;	//0xCC57109C
	PE_M23_2K_SHP_DJ_WIN_CTRL_00_T                  shp_dj_win_ctrl_00;	//0xCC5710A0
	PE_M23_2K_SHP_DJ_WIN_CTRL_01_T                  shp_dj_win_ctrl_01;	//0xCC5710A4
	PE_M23_2K_SHP_DJ_WIN_CTRL_02_T                  shp_dj_win_ctrl_02;	//0xCC5710A8
	PE_M23_2K_SHP_DJ_WIN_CTRL_03_T                  shp_dj_win_ctrl_03;	//0xCC5710AC
	PE_M23_2K_SHP_DJ_WIN_CTRL_04_T                  shp_dj_win_ctrl_04;	//0xCC5710B0
	UINT32                                                  reserved100;	//0xCC5710B4
	UINT32                                                  reserved101;	//0xCC5710B8
	UINT32                                                  reserved102;	//0xCC5710BC
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T      shp_dj_text_gain_ctrl_00;	//0xCC5710C0
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T      shp_dj_text_gain_ctrl_01;	//0xCC5710C4
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T      shp_dj_text_gain_ctrl_02;	//0xCC5710C8
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T      shp_dj_text_gain_ctrl_03;	//0xCC5710CC
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T      shp_dj_text_gain_ctrl_04;	//0xCC5710D0
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T      shp_dj_text_gain_ctrl_05;	//0xCC5710D4
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T      shp_dj_text_gain_ctrl_06;	//0xCC5710D8
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T      shp_dj_text_gain_ctrl_07;	//0xCC5710DC
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T      shp_dj_text_gain_ctrl_08;	//0xCC5710E0
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T      shp_dj_text_gain_ctrl_09;	//0xCC5710E4
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T      shp_dj_text_gain_ctrl_10;	//0xCC5710E8
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T      shp_dj_text_gain_ctrl_11;	//0xCC5710EC
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T      shp_dj_text_gain_ctrl_12;	//0xCC5710F0
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T      shp_dj_text_gain_ctrl_13;	//0xCC5710F4
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T      shp_dj_text_gain_ctrl_14;	//0xCC5710F8
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T      shp_dj_text_gain_ctrl_15;	//0xCC5710FC
	PE_M23_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T      shp_dj_text_gain_ctrl_16;	//0xCC571100
	UINT32                                                  reserved103;	//0xCC571104
	UINT32                                                  reserved104;	//0xCC571108
	UINT32                                                  reserved105;	//0xCC57110C
	UINT32                                                  reserved106;	//0xCC571110
	UINT32                                                  reserved107;	//0xCC571114
	UINT32                                                  reserved108;	//0xCC571118
	UINT32                                                  reserved109;	//0xCC57111C
	UINT32                                                  reserved110;	//0xCC571120
	UINT32                                                  reserved111;	//0xCC571124
	UINT32                                                  reserved112;	//0xCC571128
	UINT32                                                  reserved113;	//0xCC57112C
	UINT32                                                  reserved114;	//0xCC571130
	UINT32                                                  reserved115;	//0xCC571134
	UINT32                                                  reserved116;	//0xCC571138
	UINT32                                                  reserved117;	//0xCC57113C
	UINT32                                                  reserved118;	//0xCC571140
	UINT32                                                  reserved119;	//0xCC571144
	UINT32                                                  reserved120;	//0xCC571148
	UINT32                                                  reserved121;	//0xCC57114C
	UINT32                                                  reserved122;	//0xCC571150
	UINT32                                                  reserved123;	//0xCC571154
	UINT32                                                  reserved124;	//0xCC571158
	UINT32                                                  reserved125;	//0xCC57115C
	UINT32                                                  reserved126;	//0xCC571160
	UINT32                                                  reserved127;	//0xCC571164
	UINT32                                                  reserved128;	//0xCC571168
	UINT32                                                  reserved129;	//0xCC57116C
	UINT32                                                  reserved130;	//0xCC571170
	UINT32                                                  reserved131;	//0xCC571174
	UINT32                                                  reserved132;	//0xCC571178
	UINT32                                                  reserved133;	//0xCC57117C
	UINT32                                                  reserved134;	//0xCC571180
	UINT32                                                  reserved135;	//0xCC571184
	UINT32                                                  reserved136;	//0xCC571188
	UINT32                                                  reserved137;	//0xCC57118C
	UINT32                                                  reserved138;	//0xCC571190
	UINT32                                                  reserved139;	//0xCC571194
	UINT32                                                  reserved140;	//0xCC571198
	UINT32                                                  reserved141;	//0xCC57119C
	UINT32                                                  reserved142;	//0xCC5711A0
	UINT32                                                  reserved143;	//0xCC5711A4
	UINT32                                                  reserved144;	//0xCC5711A8
	UINT32                                                  reserved145;	//0xCC5711AC
	UINT32                                                  reserved146;	//0xCC5711B0
	UINT32                                                  reserved147;	//0xCC5711B4
	UINT32                                                  reserved148;	//0xCC5711B8
	UINT32                                                  reserved149;	//0xCC5711BC
	UINT32                                                  reserved150;	//0xCC5711C0
	UINT32                                                  reserved151;	//0xCC5711C4
	UINT32                                                  reserved152;	//0xCC5711C8
	UINT32                                                  reserved153;	//0xCC5711CC
	UINT32                                                  reserved154;	//0xCC5711D0
	UINT32                                                  reserved155;	//0xCC5711D4
	UINT32                                                  reserved156;	//0xCC5711D8
	UINT32                                                  reserved157;	//0xCC5711DC
	UINT32                                                  reserved158;	//0xCC5711E0
	UINT32                                                  reserved159;	//0xCC5711E4
	UINT32                                                  reserved160;	//0xCC5711E8
	UINT32                                                  reserved161;	//0xCC5711EC
	UINT32                                                  reserved162;	//0xCC5711F0
	UINT32                                                  reserved163;	//0xCC5711F4
	UINT32                                                  reserved164;	//0xCC5711F8
	UINT32                                                  reserved165;	//0xCC5711FC
	PE_M23_2K_SHP_CORE_STAT_00_T                      shp_core_stat_00;	//0xCC571200
	PE_M23_2K_SHP_CORE_STAT_01_T                      shp_core_stat_01;	//0xCC571204
	PE_M23_2K_SHP_CORE_STAT_02_T                      shp_core_stat_02;	//0xCC571208
	PE_M23_2K_SHP_CORE_STAT_03_T                      shp_core_stat_03;	//0xCC57120C
	PE_M23_2K_SHP_CORE_STAT_04_T                      shp_core_stat_04;	//0xCC571210
	PE_M23_2K_SHP_CORE_STAT_05_T                      shp_core_stat_05;	//0xCC571214
	UINT32                                                  reserved166;	//0xCC571218
	UINT32                                                  reserved167;	//0xCC57121C
	UINT32                                                  reserved168;	//0xCC571220
	UINT32                                                  reserved169;	//0xCC571224
	UINT32                                                  reserved170;	//0xCC571228
	UINT32                                                  reserved171;	//0xCC57122C
	UINT32                                                  reserved172;	//0xCC571230
	UINT32                                                  reserved173;	//0xCC571234
	UINT32                                                  reserved174;	//0xCC571238
	UINT32                                                  reserved175;	//0xCC57123C
	UINT32                                                  reserved176;	//0xCC571240
	UINT32                                                  reserved177;	//0xCC571244
	UINT32                                                  reserved178;	//0xCC571248
	UINT32                                                  reserved179;	//0xCC57124C
	UINT32                                                  reserved180;	//0xCC571250
	UINT32                                                  reserved181;	//0xCC571254
	UINT32                                                  reserved182;	//0xCC571258
	UINT32                                                  reserved183;	//0xCC57125C
	PE_M23_2K_SHP_CORE_FD_STAT_00_T                shp_core_fd_stat_00;	//0xCC571260
	PE_M23_2K_SHP_CORE_FD_STAT_01_T                shp_core_fd_stat_01;	//0xCC571264
	PE_M23_2K_SHP_CORE_FD_STAT_02_T                shp_core_fd_stat_02;	//0xCC571268
	PE_M23_2K_SHP_CORE_FD_STAT_03_T                shp_core_fd_stat_03;	//0xCC57126C
	UINT32                                                  reserved184;	//0xCC571270
	UINT32                                                  reserved185;	//0xCC571274
	UINT32                                                  reserved186;	//0xCC571278
	UINT32                                                  reserved187;	//0xCC57127C
	UINT32                                                  reserved188;	//0xCC571280
	UINT32                                                  reserved189;	//0xCC571284
	UINT32                                                  reserved190;	//0xCC571288
	UINT32                                                  reserved191;	//0xCC57128C
	UINT32                                                  reserved192;	//0xCC571290
	UINT32                                                  reserved193;	//0xCC571294
	UINT32                                                  reserved194;	//0xCC571298
	UINT32                                                  reserved195;	//0xCC57129C
	UINT32                                                  reserved196;	//0xCC5712A0
	UINT32                                                  reserved197;	//0xCC5712A4
	UINT32                                                  reserved198;	//0xCC5712A8
	UINT32                                                  reserved199;	//0xCC5712AC
	UINT32                                                  reserved200;	//0xCC5712B0
	UINT32                                                  reserved201;	//0xCC5712B4
	UINT32                                                  reserved202;	//0xCC5712B8
	UINT32                                                  reserved203;	//0xCC5712BC
	UINT32                                                  reserved204;	//0xCC5712C0
	UINT32                                                  reserved205;	//0xCC5712C4
	UINT32                                                  reserved206;	//0xCC5712C8
	UINT32                                                  reserved207;	//0xCC5712CC
	UINT32                                                  reserved208;	//0xCC5712D0
	UINT32                                                  reserved209;	//0xCC5712D4
	UINT32                                                  reserved210;	//0xCC5712D8
	UINT32                                                  reserved211;	//0xCC5712DC
	UINT32                                                  reserved212;	//0xCC5712E0
	UINT32                                                  reserved213;	//0xCC5712E4
	UINT32                                                  reserved214;	//0xCC5712E8
	UINT32                                                  reserved215;	//0xCC5712EC
	UINT32                                                  reserved216;	//0xCC5712F0
	UINT32                                                  reserved217;	//0xCC5712F4
	UINT32                                                  reserved218;	//0xCC5712F8
	UINT32                                                  reserved219;	//0xCC5712FC
	PE_M23_2K_SHP_CORE_TMAP_STAT_00_T            shp_core_tmap_stat_00;	//0xCC571300
	PE_M23_2K_SHP_CORE_TMAP_STAT_01_T            shp_core_tmap_stat_01;	//0xCC571304
	PE_M23_2K_SHP_CORE_TMAP_STAT_02_T            shp_core_tmap_stat_02;	//0xCC571308
	PE_M23_2K_SHP_CORE_TMAP_STAT_03_T            shp_core_tmap_stat_03;	//0xCC57130C
	PE_M23_2K_SHP_CORE_TMAP_STAT_04_T            shp_core_tmap_stat_04;	//0xCC571310
	PE_M23_2K_SHP_CORE_TMAP_STAT_05_T            shp_core_tmap_stat_05;	//0xCC571314
	PE_M23_2K_SHP_CORE_TMAP_STAT_06_T            shp_core_tmap_stat_06;	//0xCC571318
	PE_M23_2K_SHP_CORE_TMAP_STAT_07_T            shp_core_tmap_stat_07;	//0xCC57131C
	UINT32                                                  reserved220;	//0xCC571320
	UINT32                                                  reserved221;	//0xCC571324
	UINT32                                                  reserved222;	//0xCC571328
	UINT32                                                  reserved223;	//0xCC57132C
	UINT32                                                  reserved224;	//0xCC571330
	UINT32                                                  reserved225;	//0xCC571334
	UINT32                                                  reserved226;	//0xCC571338
	UINT32                                                  reserved227;	//0xCC57133C
	UINT32                                                  reserved228;	//0xCC571340
	UINT32                                                  reserved229;	//0xCC571344
	UINT32                                                  reserved230;	//0xCC571348
	UINT32                                                  reserved231;	//0xCC57134C
	UINT32                                                  reserved232;	//0xCC571350
	UINT32                                                  reserved233;	//0xCC571354
	UINT32                                                  reserved234;	//0xCC571358
	UINT32                                                  reserved235;	//0xCC57135C
	UINT32                                                  reserved236;	//0xCC571360
	UINT32                                                  reserved237;	//0xCC571364
	UINT32                                                  reserved238;	//0xCC571368
	UINT32                                                  reserved239;	//0xCC57136C
	UINT32                                                  reserved240;	//0xCC571370
	UINT32                                                  reserved241;	//0xCC571374
	UINT32                                                  reserved242;	//0xCC571378
	UINT32                                                  reserved243;	//0xCC57137C
	UINT32                                                  reserved244;	//0xCC571380
	UINT32                                                  reserved245;	//0xCC571384
	UINT32                                                  reserved246;	//0xCC571388
	UINT32                                                  reserved247;	//0xCC57138C
	UINT32                                                  reserved248;	//0xCC571390
	UINT32                                                  reserved249;	//0xCC571394
	UINT32                                                  reserved250;	//0xCC571398
	UINT32                                                  reserved251;	//0xCC57139C
	UINT32                                                  reserved252;	//0xCC5713A0
	UINT32                                                  reserved253;	//0xCC5713A4
	UINT32                                                  reserved254;	//0xCC5713A8
	UINT32                                                  reserved255;	//0xCC5713AC
	UINT32                                                  reserved256;	//0xCC5713B0
	UINT32                                                  reserved257;	//0xCC5713B4
	UINT32                                                  reserved258;	//0xCC5713B8
	UINT32                                                  reserved259;	//0xCC5713BC
	UINT32                                                  reserved260;	//0xCC5713C0
	UINT32                                                  reserved261;	//0xCC5713C4
	UINT32                                                  reserved262;	//0xCC5713C8
	UINT32                                                  reserved263;	//0xCC5713CC
	UINT32                                                  reserved264;	//0xCC5713D0
	UINT32                                                  reserved265;	//0xCC5713D4
	UINT32                                                  reserved266;	//0xCC5713D8
	UINT32                                                  reserved267;	//0xCC5713DC
	UINT32                                                  reserved268;	//0xCC5713E0
	UINT32                                                  reserved269;	//0xCC5713E4
	UINT32                                                  reserved270;	//0xCC5713E8
	UINT32                                                  reserved271;	//0xCC5713EC
	PE_M23_2K_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0xCC5713F0
	PE_M23_2K_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0xCC5713F4
	PE_M23_2K_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0xCC5713F8
	PE_M23_2K_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0xCC5713FC
}PE_SR_2K_SHP_REG_M23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570200 RW 0x0000_0000 represent for 0xCC5B0594 DNR_MAX_CTRL_T
	UINT32 reg_dnr_max_enable				:1; //(0,RW,0x00) //0 : bypass(or ifc result), 1 : dnr_mux
	UINT32 reg_ifc_max_enable				:1; //(1,RW,0x00) //0 : dnr result, 1 : ifc_mux
	UINT32 reg_dnr_ifc_sel					:1; //(2,RW,0x00) //0 : dnr result, 1 : ifc result
	UINT32 reg_decon_max_sum_sel			:1; //(3,RW,0x00) //0 : sum, 1 : max
	UINT32 reg_decon_ori_sel				:1; //(4,RW,0x0) //0: original, 1: v_filter
	UINT32 reg_decon_max_enable 			:1; //(5,RW,0x0) //0: dnr only, 1: dnr+decon
	UINT32 reg_max_decon_dbg_en 			:1; //(6,RW,0x0) //decon : red
	UINT32 reg_half_rate_cg_n				:1; //(7,RW,0x0) //0: cg_on, 1: cg_off
	UINT32 reg_max_dbg_en					:1; //(8,RW,0x00) //ac : yellow dc : blur	mnr : green ac+dc : gray	ac+mnr : white	dc+mnr : black
	UINT32 reg_dnr_motion_sel				:1; //(9,RW,0x00) //0: 1:2:1 blurred motion 1: 5x5 blurred motion
	UINT32 reg_tnr_decon_en 				:1; //(10,RW,0x0) //1: tnr_decon, 0: dnr_decon
	UINT32 reg_face_obj_sel 				:1; //(11,RW,0x0) //0: dnr obc(4K이하, internal), 1: nd obc(4K 초과(8K), external)	Not used in O-series(Only E series)
	UINT32 resvd0							:4;
	UINT32 reg_win_en						:1; //(16,RW,0x00) //win control enable    debug_enable should be '0'
	UINT32 reg_bdr_en						:1; //(17,RW,0x00) //border enable
	UINT32 reg_win_inout					:1; //(18,RW,0x00) //
	UINT32 resvd1							:2;
	UINT32 reg_ipc_motion_en				:1; //(21,RW,0x0) //hmc_flag 대응 => 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl				:3; //(24:22,RW,0x00) //0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th 				:7; //(31:25,RW,0x0) //applied ifc when delta is greater than th
	};
}PE_M23_SRE_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570204 RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_M23_SRE_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC570208 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_M23_SRE_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC57020C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_M23_SRE_VERI_SYS_VERI_3_T;

typedef struct {
	PE_M23_SRE_VERI_SYS_VERI_0_T                                sre_sys_veri_0;	//0xCC570200
	PE_M23_SRE_VERI_SYS_VERI_1_T                                sre_sys_veri_1;	//0xCC570204
	PE_M23_SRE_VERI_SYS_VERI_2_T                                sre_sys_veri_2;	//0xCC570208
	PE_M23_SRE_VERI_SYS_VERI_3_T                                sre_sys_veri_3;	//0xCC57020C
}PE_SRE_VERI_REG_M23_T;

#endif
