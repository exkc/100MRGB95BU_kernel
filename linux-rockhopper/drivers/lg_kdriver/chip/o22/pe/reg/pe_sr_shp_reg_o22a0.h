#ifndef _PE_SRE_REG_O22A0_H_
#define _PE_SRE_REG_O22A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40C00 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O22_2K_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40C04 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40C08 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O22_2K_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40C0C RW 0x00A9_0000
	UINT32 reg_top_prefetch_cnt             :12;	//(11:0,NA,0) //Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,169) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40C40 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O22_2K_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40C60 RW 0x1000_0A05
	UINT32 reg_gain_map_mmd_div             :4;	//(3:0,NA,5) //3x3 mmd division
	UINT32 reg_gain_map_mmd_mul             :4;	//(7:4,NA,0) //3x3 mmd multiplication
	UINT32 reg_gain_map_mmd_offset          :8;	//(15:8,NA,10) //3x3 mmd offset
	UINT32 resvd0                           :12;
	UINT32 reg_gain_map_mmd_3x3_en          :1;	//(28:28,NA,1) //3x3 mmd multiplication
	UINT32 resvd1                           :3;
	};
}PE_O22_2K_SHP_GAIN_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40CF0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O22_2K_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D00 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D08 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O22_2K_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D0C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D10 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D14 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D18 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D1C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D20 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O22_2K_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D24 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D28 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O22_2K_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D2C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D30 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O22_2K_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D34 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O22_2K_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D38 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D3C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O22_2K_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D40 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O22_2K_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D44 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O22_2K_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D48 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O22_2K_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D4C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O22_2K_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D50 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O22_2K_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D54 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_O22_2K_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D58 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O22_2K_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D60 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O22_2K_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D64 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O22_2K_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D68 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O22_2K_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D6C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O22_2K_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D70 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O22_2K_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D74 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D78 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O22_2K_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D7C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O22_2K_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D80 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O22_2K_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D84 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_O22_2K_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D88 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O22_2K_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D8C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D90 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40D94 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_O22_2K_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DA0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 reserved01                       :3;	// reserved
	UINT32 reg_lc_gb_en                     :1;	// 4:4
	UINT32 reserved02                       :3;	// reserved
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //local gain
	};
}PE_O22_2K_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DA4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //gain balancing, x1
	};
}PE_O22_2K_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DA8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //gain balancing, x3
	};
}PE_O22_2K_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DAC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DB0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DC0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O22_2K_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DC4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_O22_2K_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DC8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O22_2K_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DCC RW 0x0006_5008
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
}PE_O22_2K_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DD0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_O22_2K_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DD4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_O22_2K_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DD8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O22_2K_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DDC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O22_2K_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DE0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O22_2K_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DE4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DE8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O22_2K_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DEC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O22_2K_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DF0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O22_2K_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DF4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DF8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O22_2K_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40DFC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O22_2K_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E00 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O22_2K_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E04 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_O22_2K_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E08 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O22_2K_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E0C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E10 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E20 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O22_2K_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E24 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O22_2K_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E28 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E2C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E30 RW 0x1010_2014
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
}PE_O22_2K_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E40 RW 0x8000_0011
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
}PE_O22_2K_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E44 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //
	UINT32 resvd3                           :5;
	};
}PE_O22_2K_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E48 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//(21:16,NA,63) //
	UINT32 resvd1                           :10;
	};
}PE_O22_2K_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E4C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //
	};
}PE_O22_2K_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E54 RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio                :3;	//(2:0,NA,4) //
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//(13:8,NA,31) //
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //
	UINT32 resvd3                           :6;
	};
}PE_O22_2K_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E58 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //
	UINT32 resvd2                           :3;
	};
}PE_O22_2K_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E5C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O22_2K_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E60 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O22_2K_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E64 RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain           :5;	//(4:0,NA,31) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//(12:8,NA,31) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //
	UINT32 resvd2                           :2;
	};
}PE_O22_2K_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E68 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7                   :4;	//(3:0,NA,15) //
	UINT32 reg_tgen_gain6                   :4;	//(7:4,NA,15) //
	UINT32 reg_tgen_gain5                   :4;	//(11:8,NA,13) //
	UINT32 reg_tgen_gain4                   :4;	//(15:12,NA,12) //
	UINT32 reg_tgen_gain3                   :4;	//(19:16,NA,11) //
	UINT32 reg_tgen_gain2                   :4;	//(23:20,NA,10) //
	UINT32 reg_tgen_gain1                   :4;	//(27:24,NA,8) //
	UINT32 reg_tgen_gain0                   :4;	//(31:28,NA,4) //
	};
}PE_O22_2K_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E6C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E70 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E74 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O22_2K_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E80 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O22_2K_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E84 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E88 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E8C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E90 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E94 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E98 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40E9C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EA0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EA4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EA8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EAC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EB0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EB4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EB8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EBC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EC0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EC4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EC8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40ECC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40ED0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40ED4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40ED8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EDC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EE0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EE4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O22_2K_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EE8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_O22_2K_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EEC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O22_2K_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EF0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O22_2K_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EF4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O22_2K_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EF8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40EFC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F00 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F04 RW 0x0000_2B38
	UINT32 reg_nntg_lsfr_init_1st           :32;	//(31:0,NA,11064) //4K nano-noise LSFR init (1st)
	};
}PE_O22_2K_SHP_NNTG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F08 RW 0xBDE6_E338
	UINT32 reg_nntg_lsfr_init_2nd           :32;	//(31:0,NA,3186025272) //4K nano-noise LSFR init (2nd)
	};
}PE_O22_2K_SHP_NNTG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F0C RW 0xD9F2_01CB
	UINT32 reg_nntg_lsfr_init_3rd           :32;	//(31:0,NA,3656516043) //4K nano-noise LSFR init (3rd)
	};
}PE_O22_2K_SHP_NNTG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F10 RW 0x1598_773A
	UINT32 reg_nntg_lsfr_init_4th           :32;	//(31:0,NA,362313530) //4K nano-noise LSFR init (4th)
	};
}PE_O22_2K_SHP_NNTG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F14 RW 0x82D2_8A5C
	UINT32 reg_nntg_lsfr_init_5th           :32;	//(31:0,NA,2194836060) //4K nano-noise LSFR init (5th)
	};
}PE_O22_2K_SHP_NNTG_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F2C RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio              :8;	//(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_O22_2K_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F30 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00           :4;	//(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F34 RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20           :4;	//(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F38 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10           :4;	//(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F3C RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0             :8;	//(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O22_2K_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F40 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2             :8;	//(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O22_2K_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F44 RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0             :8;	//(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O22_2K_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F48 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2             :8;	//(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O22_2K_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F4C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O22_2K_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F50 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_2K_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F54 RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_2K_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F60 RW 0x0000_0080
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O22_2K_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F64 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_O22_2K_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40F68 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_O22_2K_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FA0 RW 0x0000_0000
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
}PE_O22_2K_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FA4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FA8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FAC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FB0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FC0 RW 0x0432_0c40
	UINT32 reg_region_text_en               :1;	//(0:0,NA,0) //region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//(6:4,NA,4) //
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//(15:8,NA,12) //
	UINT32 reg_region_text_add_max          :8;	//(23:16,NA,50) //
	UINT32 reg_region_text_cuthif           :3;	//(26:24,NA,4) //
	UINT32 resvd2                           :5;
	};
}PE_O22_2K_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FC4 RW 0x0f50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //region texture LUT , x1
	};
}PE_O22_2K_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FC8 RW 0x46c8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //region texture LUT , x3
	};
}PE_O22_2K_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FCC RW 0x0000_ff00
	UINT32 reg_tmap_temp_iir_en             :1;	//(0:0,NA,0) //TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//(4:4,NA,0) //TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//(15:8,NA,255) //TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//(24:24,NA,0) //TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FD0 RW 0x2840_0a00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //tmap temporal previous blend LUT , x1
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FD4 RW 0x5080_3c60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //tmap temporal previous blend LUT , x3
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FD8 RW 0x08d0_00c0
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir positive LUT , x1
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FDC RW 0x30f0_10e0
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //tmap temporal iir positive LUT , x3
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FE0 RW 0x80c0_60d0
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //tmap temporal iir positive LUT , x5
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FE4 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir negative LUT , x1
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FE8 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //tmap temporal iir negative LUT , x3
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FEC RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //tmap temporal iir negative LUT , x5
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FF0 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x       :12;	//(11:0,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FF4 RW 0x086f_077f
	UINT32 reg_tmap_stat_win0_end_x         :12;	//(11:0,NA,1919) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//(27:16,NA,2159) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FF8 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x       :12;	//(11:0,NA,1920) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40FFC RW 0x0438_0eff
	UINT32 reg_tmap_stat_win1_end_x         :12;	//(11:0,NA,3839) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//(27:16,NA,1080) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41000 RW 0x8010_0179
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
}PE_O22_2K_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41004 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O22_2K_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41008 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O22_2K_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4100C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O22_2K_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41010 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O22_2K_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41014 RW 0x0000_0000
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
}PE_O22_2K_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41018 RW 0x0000_0040
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
}PE_O22_2K_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4101C RW 0x0015_5550
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
}PE_O22_2K_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41020 RW 0x0000_0040
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
}PE_O22_2K_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41024 RW 0x002A_A040
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
}PE_O22_2K_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41028 RW 0x002A_A040
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
}PE_O22_2K_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4102C RW 0x000A_A040
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
}PE_O22_2K_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41030 RW 0x0000_00E4
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
}PE_O22_2K_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41034 RW 0x0000_5540
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
}PE_O22_2K_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41038 RW 0x0020_5542
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
}PE_O22_2K_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4103C RW 0x0008_1508
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
}PE_O22_2K_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41040 RW 0x0002_0420
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
}PE_O22_2K_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41044 RW 0x0000_8080
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
}PE_O22_2K_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41048 RW 0x0000_2A00
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
}PE_O22_2K_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4104C RW 0x0000_2A00
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
}PE_O22_2K_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41050 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O22_2K_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41054 RW 0x0000_2800
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
}PE_O22_2K_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41058 RW 0x0005_0A00
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
}PE_O22_2K_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4105C RW 0x0005_4280
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
}PE_O22_2K_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41060 RW 0x0005_50A0
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
}PE_O22_2K_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41064 RW 0x0005_4280
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
}PE_O22_2K_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41068 RW 0x0005_0A00
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
}PE_O22_2K_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4106C RW 0x0000_2800
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
}PE_O22_2K_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41070 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O22_2K_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41074 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41078 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4107C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41080 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O22_2K_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41090 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41094 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410A0 RW 0x0000_0000
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
}PE_O22_2K_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410A8 RW 0x0437_077F
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410B0 RW 0x0437_077F
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410C0 RW 0x10BC_4DB3
	UINT32 reg_dj_text_gain_mmd_mul         :8;	//(7:0,NA,179) //DJ control register
	UINT32 reg_dj_text_gain_avg_mul         :8;	//(15:8,NA,77) //DJ control register
	UINT32 reg_dj_text_gain_threshold       :10;	//(25:16,NA,188) //DJ control register
	UINT32 reg_dj_text_gain_all_text_flag   :1;	//(26:26,NA,0) //DJ control register
	UINT32 resvd0                           :1;
	UINT32 reg_dj_text_gain_en              :1;	//(28:28,NA,1) //DJ control register
	UINT32 resvd1                           :3;
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410C4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir0_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir0_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410C8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir0_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir0_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir0_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir0_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410CC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir1_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir1_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410D0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir1_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir1_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir1_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir1_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410D4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir3_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir3_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410D8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir3_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir3_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir3_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir3_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410DC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir5_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir5_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410E0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir5_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir5_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir5_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir5_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410E4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir6_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir6_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410E8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir6_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir6_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir6_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir6_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410EC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir7_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir7_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410F0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir7_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir7_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir7_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir7_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410F4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir9_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir9_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410F8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir9_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir9_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir9_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir9_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC410FC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir11_y0        :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x0        :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir11_y1        :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x1        :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41100 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir11_y2        :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir11_x2        :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir11_y3        :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir11_x3        :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41200 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41204 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41208 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4120C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41210 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O22_2K_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41214 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O22_2K_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41260 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41264 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41268 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4126C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41300 RO 0x0000_0000
	UINT32 ro_tmap_status_window0           :32;	//(31:0,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41304 RO 0x0000_0000
	UINT32 ro_tmap_status_window1           :32;	//(31:0,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41308 RO 0x0000_0000
	UINT32 ro_tmap_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4130C RO 0x0000_0000
	UINT32 ro_tmap_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41310 RO 0x0000_0000
	UINT32 ro_tmap_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41314 RO 0x0000_0000
	UINT32 ro_tmap_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41318 RO 0x0000_0000
	UINT32 ro_tmap_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4131C RO 0x0000_0000
	UINT32 ro_tmap_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_11                :16;	//(31:16,NA,0) //
	};
}PE_O22_2K_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC413F0 RW 0x0000_0000
	UINT32 cvd_pattern_detect				:1;
	UINT32 color_bar						:1;
	UINT32 vfy_glb_en						:1;
	UINT32 resvd							:29;
	};
}PE_O22_2K_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC413F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC413F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC413FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHP_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41400 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O22_2K_SHC_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41404 RW 0x0438_03C0
	UINT32 reg_top_width                    :12;	//(11:0,NA,960) //processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41408 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O22_2K_SHC_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4140C RW 0x00A9_0000
	UINT32 resvd0                           :16;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,169) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41500 RW 0xFFFF_0000
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :13;
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //pattern pixel value (Y)
	};
}PE_O22_2K_SHC_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41800 RW 0x8010_0179
	UINT32 reg_cdj_edf_en                   :1;	//(0:0,NA,1) //edge-directional de-jagging enable
	UINT32 reg_cdj_hv_filter_en             :1;	//(1:1,NA,0) //H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_cdj_edge_adaptive_en         :1;	//(3:3,NA,1) //edge adaptive filter enable
	UINT32 reg_cdj_line_variation_mode      :1;	//(4:4,NA,1) //0: sum of (cur - center)	1:  sum of adjacent pixel difference
	UINT32 reg_cdj_l_type_protection        :1;	//(5:5,NA,1) //L-type protection
	UINT32 reg_cdj_soft_en                  :1;	//(6:6,NA,1) //Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_cdj_count_diff_th            :5;	//(12:8,NA,1) //matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_cdj_output_mux               :3;	//(18:16,NA,0) //000: normal display	001: direction map	010: g0: feature (matchness)	011: g0 : gain	100: g1 : gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_cdj_buffer_detour_en         :1;	//(19:19,NA,0) //dj buffer detour enable
	UINT32 reg_cdj_center_blur_mode         :2;	//(21:20,NA,1) //center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_cdj_n_avg_mode               :1;	//(22:22,NA,0) //neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_cdj_detour_en                :1;	//(23:23,NA,0) //dejagging detour enable
	UINT32 reg_cdj_line_variation_diff_th   :8;	//(31:24,NA,128) //line-variation threshold for edge-direction decision
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41804 RW 0x0080_0000
	UINT32 reg_cdj_level_th                 :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_cdj_n_avg_gain               :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41808 RW 0x0000_1010
	UINT32 reg_cdj_g0_cnt_min               :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_cdj_g0_mul                   :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4180C RW 0x8010_0840
	UINT32 reg_cdj_g1_protect_min           :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_cdj_g1_mul                   :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_cdj_edge_min                 :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_cdj_edge_mul                 :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41810 RW 0x0000_0000
	UINT32 reg_cdj_dir_sel_c1               :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_cdj_dir_sel_c2               :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_cdj_dir_sel_c3               :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_cdj_dir_sel_c4               :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41814 RW 0x0000_0000
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41818 RW 0x0000_0040
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4181C RW 0x0015_5550
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41820 RW 0x0000_0040
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41824 RW 0x002A_A040
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41828 RW 0x002A_A040
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4182C RW 0x000A_A040
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41830 RW 0x0000_00E4
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41834 RW 0x0000_5540
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41838 RW 0x0020_5542
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4183C RW 0x0008_1508
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41840 RW 0x0002_0420
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41844 RW 0x0000_8080
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41848 RW 0x0000_2A00
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4184C RW 0x0000_2A00
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41850 RW 0x0000_0008
	UINT32 reg_cdj_pattern1_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_cdj_pattern1_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_cdj_pattern1_flip1_h         :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_cdj_pattern1_flip1_v         :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41854 RW 0x0000_2800
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41858 RW 0x0005_0A00
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4185C RW 0x0005_4280
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41860 RW 0x0005_50A0
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41864 RW 0x0005_4280
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41868 RW 0x0005_0A00
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4186C RW 0x0000_2800
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
}PE_O22_2K_SHC_SHP_CDJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41870 RW 0x0000_0004
	UINT32 reg_cdj_pattern2_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_cdj_pattern2_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_cdj_pattern2_flip1_h         :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_cdj_pattern2_flip1_v         :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41874 RW 0x00FF_0628
	UINT32 reg_cdj_soft_g0_mul              :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g0_offset           :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g0_max              :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41878 RW 0x00FF_0414
	UINT32 reg_cdj_soft_g1_mul              :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g1_offset           :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g1_max              :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4187C RW 0x00FF_0620
	UINT32 reg_cdj_soft_g2_mul              :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g2_offset           :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g2_max              :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41880 RW 0x0001_1400
	UINT32 reg_cdj_soft_base                :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_cdj_soft_sel_1357_gain       :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_cdj_soft_single_match_en     :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O22_2K_SHC_SHP_CDJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41890 RW 0x0000_0100
	UINT32 reg_cdir_blur_detour             :1;	//(0:0,NA,0) //dir blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_cdir_blur_buf_detour         :1;	//(4:4,NA,0) //dir blur buffer detour enable
	UINT32 resvd1                           :3;
	UINT32 reg_cdir_blur_en                 :1;	//(8:8,NA,1) //dir blur enable
	UINT32 resvd2                           :23;
	};
}PE_O22_2K_SHC_SHP_CDIR_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41894 RW 0x0040_000A
	UINT32 reg_cdir_blur_base               :8;	//(7:0,NA,10) //dir blur base
	UINT32 resvd0                           :8;
	UINT32 reg_cdir_blur_gain               :8;	//(23:16,NA,64) //dir blur gain
	UINT32 resvd1                           :8;
	};
}PE_O22_2K_SHC_SHP_CDIR_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC418A0 RW 0x0000_0000
	UINT32 reg_win_cdj_win0_en              :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_win_cdj_win1_en              :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_win_cdj_win01_en             :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_cdj_win_outside          :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_cdj_win_en               :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_cdj_bdr_alpha            :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_win_cdj_bdr_wid              :2;	//(14:13,NA,0) //border width
	UINT32 reg_win_cdj_bdr_en               :1;	//(15:15,NA,0) //border enable
	UINT32 reg_win_cdj_cr5                  :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_win_cdj_cb5                  :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_win_cdj_yy6                  :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC418A4 RW 0x0000_0000
	UINT32 reg_win_cdj_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC418A8 RW 0x0437_077F
	UINT32 reg_win_cdj_win_w0_x1            :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y1            :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC418AC RW 0x0000_0000
	UINT32 reg_win_cdj_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC418B0 RW 0x0437_077F
	UINT32 reg_win_cdj_win_w1_x1            :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y1            :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41A00 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41A04 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41A08 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41A0C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O22_2K_SHC_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41A10 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O22_2K_SHC_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41A14 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O22_2K_SHC_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41AF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHC_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41AF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHC_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41AF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHC_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41AFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_2K_SHC_SHP_FSW_CTRL_03_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A00 RW 0x0800_ff00
	UINT32 reg_sr_merge_en                  :1;	//(0:0,NA,0) //0 : core bypass	1 : SR_MERGE enable
	UINT32 resvd0                           :3;
	UINT32 reg_sr_merge_demo_mode_en        :1;	//(4:4,NA,0) //0 : demo mode off	1 : demo mode on
	UINT32 reg_sr_merge_demo_mode           :1;	//(5:5,NA,0) //0 : inside window - SR 	1 : outsie window - SR
	UINT32 resvd1                           :2;
	UINT32 reg_sr_merge_master_gain         :8;	//(15:8,NA,255) //final alpha blending weight 	255 : result = input scale-up image	0   : result = SR_MERGE blended image
	UINT32 reg_sr_merge_ti_en               :1;	//(16:16,NA,0) //0 : TI processing off 	1 : TI processing on
	UINT32 resvd2                           :11;
	UINT32 reg_sr_merge_debug_mode          :3;	//(30:28,NA,0) //0 : SR_MERGE result (default)	1 : mmd blending gain	2 : NR gain	3 : TI gain 	4 : sobel gain 	5 : input residual image	6 : (SR_MERGE output - Scale_Up image)
	UINT32 resvd3                           :1;
	};
}PE_O22_SR_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A04 RW 0x0870_0F00
	UINT32 reg_sr_merge_width               :16;	//(15:0,NA,3840) //input image width (default : 3840)
	UINT32 reg_sr_merge_height              :16;	//(31:16,NA,2160) //input image height (default : 2160)
	};
}PE_O22_SR_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A08 RW 0x0000_0000
	UINT32 reg_sr_merge_demo_start_pts_x0   :16;	//(15:0,NA,0) //window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_start_pts_y0   :16;	//(31:16,NA,0) //window start point (for demo mode)
	};
}PE_O22_SR_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A0C RW 0x007f_007f
	UINT32 reg_sr_merge_demo_end_pts_x1     :16;	//(15:0,NA,127) //window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_end_pts_y1     :16;	//(31:16,NA,127) //window end point (for demo mode)
	};
}PE_O22_SR_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A10 RW 0x0000_0000
	UINT32 reg_residual_blur_en             :1;	//(0:0,NA,0) //0 : spatial filter off - use input residual data	1 : spatial filter on - use spatial filter result
	UINT32 resvd                            :31;
	};
}PE_O22_SR_MERGE_SPATIAL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A14 RW 0x0002_4048
	UINT32 reg_residual_blur_filt_00        :4;	//(3:0,NA,8) //blur filter coefficient
	UINT32 reg_residual_blur_filt_01        :4;	//(7:4,NA,4) //blur filter coefficient
	UINT32 reg_residual_blur_filt_02        :4;	//(11:8,NA,0) //blur filter coefficient
	UINT32 reg_residual_blur_filt_10        :4;	//(15:12,NA,4) //blur filter coefficient
	UINT32 reg_residual_blur_filt_11        :4;	//(19:16,NA,2) //blur filter coefficient
	UINT32 reg_residual_blur_filt_12        :4;	//(23:20,NA,0) //blur filter coefficient
	UINT32 resvd                            :8;
	};
}PE_O22_SR_MERGE_SPATIAL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A20 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_mmd_tap_size                 :4;	//(7:4,NA,0) //mmd tap size	0 : 3x3	1 : 5x5
	UINT32 resvd1                           :24;
	};
}PE_O22_SR_MERGE_MMD_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A24 RW 0x1020_0800
	UINT32 reg_mmd_diff_lut_y0              :8;	//(7:0,NA,0) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x0              :8;	//(15:8,NA,8) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y1              :8;	//(23:16,NA,32) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x1              :8;	//(31:24,NA,16) //mmd diff lut x position
	};
}PE_O22_SR_MERGE_MMD_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A28 RW 0x3C10_2040
	UINT32 reg_mmd_diff_lut_y2              :8;	//(7:0,NA,64) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x2              :8;	//(15:8,NA,32) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y3              :8;	//(23:16,NA,16) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x3              :8;	//(31:24,NA,60) //mmd diff lut x position
	};
}PE_O22_SR_MERGE_MMD_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A2C RW 0x82FF_6EFF
	UINT32 reg_mmd_diff_lut_y4              :8;	//(7:0,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x4              :8;	//(15:8,NA,110) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y5              :8;	//(23:16,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x5              :8;	//(31:24,NA,130) //mmd diff lut x position
	};
}PE_O22_SR_MERGE_MMD_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A30 RW 0xAAFF_96FF
	UINT32 reg_mmd_diff_lut_y6              :8;	//(7:0,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x6              :8;	//(15:8,NA,150) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y7              :8;	//(23:16,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x7              :8;	//(31:24,NA,170) //mmd diff lut x position
	};
}PE_O22_SR_MERGE_MMD_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A34 RW 0x2880_14C8
	UINT32 reg_ti_gain_lut_y0               :8;	//(7:0,NA,200) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x0               :8;	//(15:8,NA,20) //ti gain lut x position
	UINT32 reg_ti_gain_lut_y1               :8;	//(23:16,NA,128) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x1               :8;	//(31:24,NA,40) //ti gain lut x position
	};
}PE_O22_SR_MERGE_MMD_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A38 RW 0xA020_5040
	UINT32 reg_ti_gain_lut_y2               :8;	//(7:0,NA,64) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x2               :8;	//(15:8,NA,80) //ti gain lut x position
	UINT32 reg_ti_gain_lut_y3               :8;	//(23:16,NA,32) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x3               :8;	//(31:24,NA,160) //ti gain lut x position
	};
}PE_O22_SR_MERGE_MMD_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A50 RW 0x0000_0003
	UINT32 reg_sobel_mode                   :4;	//(3:0,NA,3) //sobel mode selection 	0: 3x3 	1: 5x5	2: 7x7	3: (7x7 - 3x3) : (default)
	UINT32 resvd                            :28;
	};
}PE_O22_SR_MERGE_SOBEL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A54 RW 0x5014_0400
	UINT32 reg_sobel_lut_y0                 :8;	//(7:0,NA,0) //sobel lut y position
	UINT32 reg_sobel_lut_x0                 :8;	//(15:8,NA,4) //sobel lut x position
	UINT32 reg_sobel_lut_y1                 :8;	//(23:16,NA,20) //sobel lut y position
	UINT32 reg_sobel_lut_x1                 :8;	//(31:24,NA,80) //sobel lut x position
	};
}PE_O22_SR_MERGE_SOBEL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A58 RW 0xE6FF_C864
	UINT32 reg_sobel_lut_y2                 :8;	//(7:0,NA,100) //sobel lut y position
	UINT32 reg_sobel_lut_x2                 :8;	//(15:8,NA,200) //sobel lut x position
	UINT32 reg_sobel_lut_y3                 :8;	//(23:16,NA,255) //sobel lut y position
	UINT32 reg_sobel_lut_x3                 :8;	//(31:24,NA,230) //sobel lut x position
	};
}PE_O22_SR_MERGE_SOBEL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A70 RW 0x0000_0300
	UINT32 reg_nr_gain_en                   :1;	//(0:0,NA,0) //NR Gain enable
	UINT32 resvd0                           :3;
	UINT32 reg_nr_gain_th                   :10;	//(13:4,NA,48) //NR gain threshold
	UINT32 resvd1                           :18;
	};
}PE_O22_SR_MERGE_NR_GAIN_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A74 RW 0x2080_1019
	UINT32 reg_nr_gain_lut_y0               :8;	//(7:0,NA,25) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x0               :8;	//(15:8,NA,16) //nr_gain lut x position
	UINT32 reg_nr_gain_lut_y1               :8;	//(23:16,NA,128) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x1               :8;	//(31:24,NA,32) //nr_gain lut x position
	};
}PE_O22_SR_MERGE_NR_GAIN_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A78 RW 0x4000_3020
	UINT32 reg_nr_gain_lut_y2               :8;	//(7:0,NA,32) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x2               :8;	//(15:8,NA,48) //nr_gain lut x position
	UINT32 reg_nr_gain_lut_y3               :8;	//(23:16,NA,0) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x3               :8;	//(31:24,NA,64) //nr_gain lut x position
	};
}PE_O22_SR_MERGE_NR_GAIN_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A90 RW 0x0020_0021
	UINT32 reg_blend_lut_en                 :1;	//(0:0,NA,1) //blend lut en
	UINT32 resvd                            :19;
	UINT32 reg_blend_amp_weight             :12;	//(31:20,NA,32) //blend weight ('d16: x1, 'd32:x2)
	};
}PE_O22_SR_MERGE_BLEND_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A94 RW 0x0012_0012
	UINT32 reg_blend_lut_y1                 :10;	//(9:0,NA,18) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x1                 :10;	//(25:16,NA,18) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O22_SR_MERGE_BLEND_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A98 RW 0x0008_0008
	UINT32 reg_blend_lut_y0                 :10;	//(9:0,NA,8) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x0                 :10;	//(25:16,NA,8) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O22_SR_MERGE_BLEND_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42A9C RW 0x0080_0080
	UINT32 reg_blend_lut_y3                 :10;	//(9:0,NA,128) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x3                 :10;	//(25:16,NA,128) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O22_SR_MERGE_BLEND_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42AA0 RW 0x0020_0020
	UINT32 reg_blend_lut_y2                 :10;	//(9:0,NA,32) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x2                 :10;	//(25:16,NA,32) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O22_SR_MERGE_BLEND_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42B00 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SR_MERGE_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42B04 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :16;	//(15:0,NA,0) //Input vertical counter
	UINT32 reg_mon_in_hori_cnt              :16;	//(31:16,NA,0) //Input horizontal counter
	};
}PE_O22_SR_MERGE_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42B08 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :16;	//(15:0,NA,0) //Output vertical counter
	UINT32 reg_mon_out_hori_cnt             :16;	//(31:16,NA,0) //Output horizontal counter
	};
}PE_O22_SR_MERGE_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42B0C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :16;	//(15:0,NA,0) //Output previous frame vertical counter
	UINT32 reg_mon_fin_in_vert_cnt          :16;	//(31:16,NA,0) //Input previous frame vertical counter
	};
}PE_O22_SR_MERGE_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42B10 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O22_SR_MERGE_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42B14 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O22_SR_MERGE_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42BF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SR_MERGE_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42BF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SR_MERGE_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42BF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SR_MERGE_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC42BFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SR_MERGE_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40200 RW 0x0000_0000
	UINT32 reg_sys_veri_0                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_SR_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40204 RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_SR_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC40208 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_SR_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4020C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_SR_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O22_2K_SHP_CORE_CTRL_00_T                      shp_core_ctrl_00;	//0xCCC40C00
	PE_O22_2K_SHP_CORE_CTRL_01_T                      shp_core_ctrl_01;	//0xCCC40C04
	PE_O22_2K_SHP_CORE_CTRL_02_T                      shp_core_ctrl_02;	//0xCCC40C08
	PE_O22_2K_SHP_CORE_CTRL_03_T                      shp_core_ctrl_03;	//0xCCC40C0C
	UINT32                                                    reserved0;	//0xCCC40C10
	UINT32                                                    reserved1;	//0xCCC40C14
	UINT32                                                    reserved2;	//0xCCC40C18
	UINT32                                                    reserved3;	//0xCCC40C1C
	UINT32                                                    reserved4;	//0xCCC40C20
	UINT32                                                    reserved5;	//0xCCC40C24
	UINT32                                                    reserved6;	//0xCCC40C28
	UINT32                                                    reserved7;	//0xCCC40C2C
	UINT32                                                    reserved8;	//0xCCC40C30
	UINT32                                                    reserved9;	//0xCCC40C34
	UINT32                                                   reserved10;	//0xCCC40C38
	UINT32                                                   reserved11;	//0xCCC40C3C
	PE_O22_2K_SHP_PAT_GEN_CTRL_00_T                shp_pat_gen_ctrl_00;	//0xCCC40C40
	UINT32                                                   reserved12;	//0xCCC40C44
	UINT32                                                   reserved13;	//0xCCC40C48
	UINT32                                                   reserved14;	//0xCCC40C4C
	UINT32                                                   reserved15;	//0xCCC40C50
	UINT32                                                   reserved16;	//0xCCC40C54
	UINT32                                                   reserved17;	//0xCCC40C58
	UINT32                                                   reserved18;	//0xCCC40C5C
	PE_O22_2K_SHP_GAIN_MAP_CTRL_00_T              shp_gain_map_ctrl_00;	//0xCCC40C60
	UINT32                                                   reserved19;	//0xCCC40C64
	UINT32                                                   reserved20;	//0xCCC40C68
	UINT32                                                   reserved21;	//0xCCC40C6C
	UINT32                                                   reserved22;	//0xCCC40C70
	UINT32                                                   reserved23;	//0xCCC40C74
	UINT32                                                   reserved24;	//0xCCC40C78
	UINT32                                                   reserved25;	//0xCCC40C7C
	UINT32                                                   reserved26;	//0xCCC40C80
	UINT32                                                   reserved27;	//0xCCC40C84
	UINT32                                                   reserved28;	//0xCCC40C88
	UINT32                                                   reserved29;	//0xCCC40C8C
	UINT32                                                   reserved30;	//0xCCC40C90
	UINT32                                                   reserved31;	//0xCCC40C94
	UINT32                                                   reserved32;	//0xCCC40C98
	UINT32                                                   reserved33;	//0xCCC40C9C
	UINT32                                                   reserved34;	//0xCCC40CA0
	UINT32                                                   reserved35;	//0xCCC40CA4
	UINT32                                                   reserved36;	//0xCCC40CA8
	UINT32                                                   reserved37;	//0xCCC40CAC
	UINT32                                                   reserved38;	//0xCCC40CB0
	UINT32                                                   reserved39;	//0xCCC40CB4
	UINT32                                                   reserved40;	//0xCCC40CB8
	UINT32                                                   reserved41;	//0xCCC40CBC
	UINT32                                                   reserved42;	//0xCCC40CC0
	UINT32                                                   reserved43;	//0xCCC40CC4
	UINT32                                                   reserved44;	//0xCCC40CC8
	UINT32                                                   reserved45;	//0xCCC40CCC
	UINT32                                                   reserved46;	//0xCCC40CD0
	UINT32                                                   reserved47;	//0xCCC40CD4
	UINT32                                                   reserved48;	//0xCCC40CD8
	UINT32                                                   reserved49;	//0xCCC40CDC
	UINT32                                                   reserved50;	//0xCCC40CE0
	UINT32                                                   reserved51;	//0xCCC40CE4
	UINT32                                                   reserved52;	//0xCCC40CE8
	UINT32                                                   reserved53;	//0xCCC40CEC
	PE_O22_2K_SHP_DP_CTRL_00_T                          shp_dp_ctrl_00;	//0xCCC40CF0
	UINT32                                                   reserved54;	//0xCCC40CF4
	UINT32                                                   reserved55;	//0xCCC40CF8
	UINT32                                                   reserved56;	//0xCCC40CFC
	PE_O22_2K_SHP_FD_CTRL_00_T                          shp_fd_ctrl_00;	//0xCCC40D00
	PE_O22_2K_SHP_FD_CTRL_01_T                          shp_fd_ctrl_01;	//0xCCC40D04
	PE_O22_2K_SHP_FD_CTRL_02_T                          shp_fd_ctrl_02;	//0xCCC40D08
	PE_O22_2K_SHP_FD_CTRL_03_T                          shp_fd_ctrl_03;	//0xCCC40D0C
	PE_O22_2K_SHP_FD_CTRL_04_T                          shp_fd_ctrl_04;	//0xCCC40D10
	PE_O22_2K_SHP_FD_CTRL_05_T                          shp_fd_ctrl_05;	//0xCCC40D14
	PE_O22_2K_SHP_FD_CTRL_06_T                          shp_fd_ctrl_06;	//0xCCC40D18
	PE_O22_2K_SHP_FD_CTRL_07_T                          shp_fd_ctrl_07;	//0xCCC40D1C
	PE_O22_2K_SHP_FD_CTRL_08_T                          shp_fd_ctrl_08;	//0xCCC40D20
	PE_O22_2K_SHP_FD_CTRL_09_T                          shp_fd_ctrl_09;	//0xCCC40D24
	PE_O22_2K_SHP_FD_CTRL_0A_T                          shp_fd_ctrl_0a;	//0xCCC40D28
	PE_O22_2K_SHP_FD_CTRL_0B_T                          shp_fd_ctrl_0b;	//0xCCC40D2C
	PE_O22_2K_SHP_FD_CTRL_0C_T                          shp_fd_ctrl_0c;	//0xCCC40D30
	PE_O22_2K_SHP_FD_CTRL_0D_T                          shp_fd_ctrl_0d;	//0xCCC40D34
	PE_O22_2K_SHP_FD_CTRL_0E_T                          shp_fd_ctrl_0e;	//0xCCC40D38
	PE_O22_2K_SHP_FD_CTRL_0F_T                          shp_fd_ctrl_0f;	//0xCCC40D3C
	PE_O22_2K_SHP_FD_CTRL_10_T                          shp_fd_ctrl_10;	//0xCCC40D40
	PE_O22_2K_SHP_FD_CTRL_11_T                          shp_fd_ctrl_11;	//0xCCC40D44
	PE_O22_2K_SHP_FD_CTRL_12_T                          shp_fd_ctrl_12;	//0xCCC40D48
	PE_O22_2K_SHP_FD_CTRL_13_T                          shp_fd_ctrl_13;	//0xCCC40D4C
	PE_O22_2K_SHP_FD_CTRL_14_T                          shp_fd_ctrl_14;	//0xCCC40D50
	PE_O22_2K_SHP_FD_CTRL_15_T                          shp_fd_ctrl_15;	//0xCCC40D54
	PE_O22_2K_SHP_FD_CTRL_16_T                          shp_fd_ctrl_16;	//0xCCC40D58
	UINT32                                                   reserved57;	//0xCCC40D5C
	PE_O22_2K_SHP_MP_CTRL_00_T                          shp_mp_ctrl_00;	//0xCCC40D60
	PE_O22_2K_SHP_MP_CTRL_01_T                          shp_mp_ctrl_01;	//0xCCC40D64
	PE_O22_2K_SHP_MP_CTRL_02_T                          shp_mp_ctrl_02;	//0xCCC40D68
	PE_O22_2K_SHP_MP_CTRL_03_T                          shp_mp_ctrl_03;	//0xCCC40D6C
	PE_O22_2K_SHP_MP_CTRL_04_T                          shp_mp_ctrl_04;	//0xCCC40D70
	PE_O22_2K_SHP_MP_CTRL_05_T                          shp_mp_ctrl_05;	//0xCCC40D74
	PE_O22_2K_SHP_MP_CTRL_06_T                          shp_mp_ctrl_06;	//0xCCC40D78
	PE_O22_2K_SHP_MP_CTRL_07_T                          shp_mp_ctrl_07;	//0xCCC40D7C
	PE_O22_2K_SHP_MP_CTRL_08_T                          shp_mp_ctrl_08;	//0xCCC40D80
	PE_O22_2K_SHP_MP_CTRL_09_T                          shp_mp_ctrl_09;	//0xCCC40D84
	PE_O22_2K_SHP_MP_CTRL_0A_T                          shp_mp_ctrl_0a;	//0xCCC40D88
	PE_O22_2K_SHP_MP_CTRL_0B_T                          shp_mp_ctrl_0b;	//0xCCC40D8C
	PE_O22_2K_SHP_MP_CTRL_0C_T                          shp_mp_ctrl_0c;	//0xCCC40D90
	PE_O22_2K_SHP_APL_CTRL_00_T                        shp_apl_ctrl_00;	//0xCCC40D94
	UINT32                                                   reserved58;	//0xCCC40D98
	UINT32                                                   reserved59;	//0xCCC40D9C
	PE_O22_2K_SHP_LC_CTRL_00_T                          shp_lc_ctrl_00;	//0xCCC40DA0
	PE_O22_2K_SHP_LC_CTRL_01_T                          shp_lc_ctrl_01;	//0xCCC40DA4
	PE_O22_2K_SHP_LC_CTRL_02_T                          shp_lc_ctrl_02;	//0xCCC40DA8
	PE_O22_2K_SHP_LC_CTRL_03_T                          shp_lc_ctrl_03;	//0xCCC40DAC
	PE_O22_2K_SHP_LC_CTRL_04_T                          shp_lc_ctrl_04;	//0xCCC40DB0
	UINT32                                                   reserved60;	//0xCCC40DB4
	UINT32                                                   reserved61;	//0xCCC40DB8
	UINT32                                                   reserved62;	//0xCCC40DBC
	PE_O22_2K_SHP_DER_CTRL_00_T                        shp_der_ctrl_00;	//0xCCC40DC0
	PE_O22_2K_SHP_DER_CTRL_01_T                        shp_der_ctrl_01;	//0xCCC40DC4
	PE_O22_2K_SHP_DER_CTRL_02_T                        shp_der_ctrl_02;	//0xCCC40DC8
	PE_O22_2K_SHP_DER_CTRL_03_T                        shp_der_ctrl_03;	//0xCCC40DCC
	PE_O22_2K_SHP_DER_CTRL_04_T                        shp_der_ctrl_04;	//0xCCC40DD0
	PE_O22_2K_SHP_DER_CTRL_05_T                        shp_der_ctrl_05;	//0xCCC40DD4
	PE_O22_2K_SHP_DER_CTRL_06_T                        shp_der_ctrl_06;	//0xCCC40DD8
	PE_O22_2K_SHP_DER_CTRL_07_T                        shp_der_ctrl_07;	//0xCCC40DDC
	PE_O22_2K_SHP_SP_CTRL_00_T                          shp_sp_ctrl_00;	//0xCCC40DE0
	PE_O22_2K_SHP_SP_CTRL_01_T                          shp_sp_ctrl_01;	//0xCCC40DE4
	PE_O22_2K_SHP_SP_CTRL_02_T                          shp_sp_ctrl_02;	//0xCCC40DE8
	PE_O22_2K_SHP_SP_CTRL_03_T                          shp_sp_ctrl_03;	//0xCCC40DEC
	PE_O22_2K_SHP_SP_CTRL_04_T                          shp_sp_ctrl_04;	//0xCCC40DF0
	PE_O22_2K_SHP_SP_CTRL_05_T                          shp_sp_ctrl_05;	//0xCCC40DF4
	PE_O22_2K_SHP_SP_CTRL_06_T                          shp_sp_ctrl_06;	//0xCCC40DF8
	PE_O22_2K_SHP_SP_CTRL_07_T                          shp_sp_ctrl_07;	//0xCCC40DFC
	PE_O22_2K_SHP_SP_CTRL_08_T                          shp_sp_ctrl_08;	//0xCCC40E00
	PE_O22_2K_SHP_SP_CTRL_09_T                          shp_sp_ctrl_09;	//0xCCC40E04
	PE_O22_2K_SHP_SP_CTRL_0A_T                          shp_sp_ctrl_0a;	//0xCCC40E08
	PE_O22_2K_SHP_SP_CTRL_0B_T                          shp_sp_ctrl_0b;	//0xCCC40E0C
	PE_O22_2K_SHP_SP_CTRL_0C_T                          shp_sp_ctrl_0c;	//0xCCC40E10
	UINT32                                                   reserved63;	//0xCCC40E14
	UINT32                                                   reserved64;	//0xCCC40E18
	UINT32                                                   reserved65;	//0xCCC40E1C
	PE_O22_2K_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0xCCC40E20
	PE_O22_2K_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0xCCC40E24
	PE_O22_2K_SHP_PTI_CTRL_02_T                        shp_pti_ctrl_02;	//0xCCC40E28
	PE_O22_2K_SHP_PTI_CTRL_03_T                        shp_pti_ctrl_03;	//0xCCC40E2C
	PE_O22_2K_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0xCCC40E30
	UINT32                                                   reserved66;	//0xCCC40E34
	UINT32                                                   reserved67;	//0xCCC40E38
	UINT32                                                   reserved68;	//0xCCC40E3C
	PE_O22_2K_SHP_TGEN_CTRL_00_T                      shp_tgen_ctrl_00;	//0xCCC40E40
	PE_O22_2K_SHP_TGEN_CTRL_01_T                      shp_tgen_ctrl_01;	//0xCCC40E44
	PE_O22_2K_SHP_TGEN_CTRL_02_T                      shp_tgen_ctrl_02;	//0xCCC40E48
	PE_O22_2K_SHP_TGEN_CTRL_03_T                      shp_tgen_ctrl_03;	//0xCCC40E4C
	UINT32                                                   reserved69;	//0xCCC40E50
	PE_O22_2K_SHP_TGEN_CTRL_04_T                      shp_tgen_ctrl_04;	//0xCCC40E54
	PE_O22_2K_SHP_TGEN_CTRL_05_T                      shp_tgen_ctrl_05;	//0xCCC40E58
	PE_O22_2K_SHP_TGEN_CTRL_06_T                      shp_tgen_ctrl_06;	//0xCCC40E5C
	PE_O22_2K_SHP_TGEN_CTRL_07_T                      shp_tgen_ctrl_07;	//0xCCC40E60
	PE_O22_2K_SHP_TGEN_CTRL_08_T                      shp_tgen_ctrl_08;	//0xCCC40E64
	PE_O22_2K_SHP_TGEN_CTRL_09_T                      shp_tgen_ctrl_09;	//0xCCC40E68
	PE_O22_2K_SHP_TGEN_CTRL_0A_T                      shp_tgen_ctrl_0a;	//0xCCC40E6C
	PE_O22_2K_SHP_TGEN_CTRL_0B_T                      shp_tgen_ctrl_0b;	//0xCCC40E70
	PE_O22_2K_SHP_SNR_CTRL_00_T                        shp_snr_ctrl_00;	//0xCCC40E74
	UINT32                                                   reserved70;	//0xCCC40E78
	UINT32                                                   reserved71;	//0xCCC40E7C
	PE_O22_2K_SHP_DCTP_CTRL_00_T                      shp_dctp_ctrl_00;	//0xCCC40E80
	PE_O22_2K_SHP_DCTP_CTRL_01_T                      shp_dctp_ctrl_01;	//0xCCC40E84
	PE_O22_2K_SHP_DCTP_CTRL_02_T                      shp_dctp_ctrl_02;	//0xCCC40E88
	PE_O22_2K_SHP_DCTP_CTRL_03_T                      shp_dctp_ctrl_03;	//0xCCC40E8C
	PE_O22_2K_SHP_DCTP_CTRL_04_T                      shp_dctp_ctrl_04;	//0xCCC40E90
	PE_O22_2K_SHP_DCTP_CTRL_05_T                      shp_dctp_ctrl_05;	//0xCCC40E94
	PE_O22_2K_SHP_DCTP_CTRL_06_T                      shp_dctp_ctrl_06;	//0xCCC40E98
	PE_O22_2K_SHP_DCTP_CTRL_07_T                      shp_dctp_ctrl_07;	//0xCCC40E9C
	PE_O22_2K_SHP_DCTP_CTRL_08_T                      shp_dctp_ctrl_08;	//0xCCC40EA0
	PE_O22_2K_SHP_DCTP_CTRL_09_T                      shp_dctp_ctrl_09;	//0xCCC40EA4
	PE_O22_2K_SHP_DCTP_CTRL_0A_T                      shp_dctp_ctrl_0a;	//0xCCC40EA8
	PE_O22_2K_SHP_DCTP_CTRL_0B_T                      shp_dctp_ctrl_0b;	//0xCCC40EAC
	PE_O22_2K_SHP_DCTP_CTRL_0C_T                      shp_dctp_ctrl_0c;	//0xCCC40EB0
	PE_O22_2K_SHP_DCTP_CTRL_0D_T                      shp_dctp_ctrl_0d;	//0xCCC40EB4
	PE_O22_2K_SHP_DCTP_CTRL_0E_T                      shp_dctp_ctrl_0e;	//0xCCC40EB8
	PE_O22_2K_SHP_DCTP_CTRL_0F_T                      shp_dctp_ctrl_0f;	//0xCCC40EBC
	PE_O22_2K_SHP_DCTP_CTRL_10_T                      shp_dctp_ctrl_10;	//0xCCC40EC0
	PE_O22_2K_SHP_DCTP_CTRL_11_T                      shp_dctp_ctrl_11;	//0xCCC40EC4
	PE_O22_2K_SHP_DCTP_CTRL_12_T                      shp_dctp_ctrl_12;	//0xCCC40EC8
	PE_O22_2K_SHP_DCTP_CTRL_13_T                      shp_dctp_ctrl_13;	//0xCCC40ECC
	PE_O22_2K_SHP_DCTP_CTRL_14_T                      shp_dctp_ctrl_14;	//0xCCC40ED0
	PE_O22_2K_SHP_DCTP_CTRL_15_T                      shp_dctp_ctrl_15;	//0xCCC40ED4
	PE_O22_2K_SHP_DCTP_CTRL_16_T                      shp_dctp_ctrl_16;	//0xCCC40ED8
	PE_O22_2K_SHP_DCTP_CTRL_17_T                      shp_dctp_ctrl_17;	//0xCCC40EDC
	PE_O22_2K_SHP_DCTP_CTRL_18_T                      shp_dctp_ctrl_18;	//0xCCC40EE0
	PE_O22_2K_SHP_DCTP_CTRL_19_T                      shp_dctp_ctrl_19;	//0xCCC40EE4
	PE_O22_2K_SHP_DCTP_CTRL_1A_T                      shp_dctp_ctrl_1a;	//0xCCC40EE8
	PE_O22_2K_SHP_DCTP_CTRL_1B_T                      shp_dctp_ctrl_1b;	//0xCCC40EEC
	PE_O22_2K_SHP_DCTP_CTRL_1C_T                      shp_dctp_ctrl_1c;	//0xCCC40EF0
	PE_O22_2K_SHP_DCTP_CTRL_1D_T                      shp_dctp_ctrl_1d;	//0xCCC40EF4
	PE_O22_2K_SHP_DCTP_CTRL_1E_T                      shp_dctp_ctrl_1e;	//0xCCC40EF8
	PE_O22_2K_SHP_DCTP_CTRL_1F_T                      shp_dctp_ctrl_1f;	//0xCCC40EFC
	PE_O22_2K_SHP_NNTG_CTRL_00_T                      shp_nntg_ctrl_00;	//0xCCC40F00
	PE_O22_2K_SHP_NNTG_CTRL_01_T                      shp_nntg_ctrl_01;	//0xCCC40F04
	PE_O22_2K_SHP_NNTG_CTRL_02_T                      shp_nntg_ctrl_02;	//0xCCC40F08
	PE_O22_2K_SHP_NNTG_CTRL_03_T                      shp_nntg_ctrl_03;	//0xCCC40F0C
	PE_O22_2K_SHP_NNTG_CTRL_04_T                      shp_nntg_ctrl_04;	//0xCCC40F10
	PE_O22_2K_SHP_NNTG_CTRL_05_T                      shp_nntg_ctrl_05;	//0xCCC40F14
	UINT32                                                   reserved72;	//0xCCC40F18
	UINT32                                                   reserved73;	//0xCCC40F1C
	UINT32                                                   reserved74;	//0xCCC40F20
	UINT32                                                   reserved75;	//0xCCC40F24
	UINT32                                                   reserved76;	//0xCCC40F28
	PE_O22_2K_SHP_NNTG_CTRL_06_T                      shp_nntg_ctrl_06;	//0xCCC40F2C
	PE_O22_2K_SHP_NNTG_CTRL_07_T                      shp_nntg_ctrl_07;	//0xCCC40F30
	PE_O22_2K_SHP_NNTG_CTRL_08_T                      shp_nntg_ctrl_08;	//0xCCC40F34
	PE_O22_2K_SHP_NNTG_CTRL_09_T                      shp_nntg_ctrl_09;	//0xCCC40F38
	PE_O22_2K_SHP_NNTG_CTRL_0A_T                      shp_nntg_ctrl_0a;	//0xCCC40F3C
	PE_O22_2K_SHP_NNTG_CTRL_0B_T                      shp_nntg_ctrl_0b;	//0xCCC40F40
	PE_O22_2K_SHP_NNTG_CTRL_0C_T                      shp_nntg_ctrl_0c;	//0xCCC40F44
	PE_O22_2K_SHP_NNTG_CTRL_0D_T                      shp_nntg_ctrl_0d;	//0xCCC40F48
	PE_O22_2K_SHP_NNTG_CTRL_0E_T                      shp_nntg_ctrl_0e;	//0xCCC40F4C
	PE_O22_2K_SHP_NNTG_CTRL_0F_T                      shp_nntg_ctrl_0f;	//0xCCC40F50
	PE_O22_2K_SHP_NNTG_CTRL_10_T                      shp_nntg_ctrl_10;	//0xCCC40F54
	UINT32                                                   reserved77;	//0xCCC40F58
	UINT32                                                   reserved78;	//0xCCC40F5C
	PE_O22_2K_SHP_DP_SUM_CTRL_00_T                  shp_dp_sum_ctrl_00;	//0xCCC40F60
	PE_O22_2K_SHP_DP_SUM_CTRL_01_T                  shp_dp_sum_ctrl_01;	//0xCCC40F64
	PE_O22_2K_SHP_DP_SUM_CTRL_02_T                  shp_dp_sum_ctrl_02;	//0xCCC40F68
	UINT32                                                   reserved79;	//0xCCC40F6C
	UINT32                                                   reserved80;	//0xCCC40F70
	UINT32                                                   reserved81;	//0xCCC40F74
	UINT32                                                   reserved82;	//0xCCC40F78
	UINT32                                                   reserved83;	//0xCCC40F7C
	UINT32                                                   reserved84;	//0xCCC40F80
	UINT32                                                   reserved85;	//0xCCC40F84
	UINT32                                                   reserved86;	//0xCCC40F88
	UINT32                                                   reserved87;	//0xCCC40F8C
	UINT32                                                   reserved88;	//0xCCC40F90
	UINT32                                                   reserved89;	//0xCCC40F94
	UINT32                                                   reserved90;	//0xCCC40F98
	UINT32                                                   reserved91;	//0xCCC40F9C
	PE_O22_2K_SHP_DP_WIN_CTRL_00_T                  shp_dp_win_ctrl_00;	//0xCCC40FA0
	PE_O22_2K_SHP_DP_WIN_CTRL_01_T                  shp_dp_win_ctrl_01;	//0xCCC40FA4
	PE_O22_2K_SHP_DP_WIN_CTRL_02_T                  shp_dp_win_ctrl_02;	//0xCCC40FA8
	PE_O22_2K_SHP_DP_WIN_CTRL_03_T                  shp_dp_win_ctrl_03;	//0xCCC40FAC
	PE_O22_2K_SHP_DP_WIN_CTRL_04_T                  shp_dp_win_ctrl_04;	//0xCCC40FB0
	UINT32                                                   reserved92;	//0xCCC40FB4
	UINT32                                                   reserved93;	//0xCCC40FB8
	UINT32                                                   reserved94;	//0xCCC40FBC
	PE_O22_2K_SHP_FD_REGION_TEXT_00_T            shp_fd_region_text_00;	//0xCCC40FC0
	PE_O22_2K_SHP_FD_REGION_TEXT_01_T            shp_fd_region_text_01;	//0xCCC40FC4
	PE_O22_2K_SHP_FD_REGION_TEXT_02_T            shp_fd_region_text_02;	//0xCCC40FC8
	PE_O22_2K_SHP_FD_TMAP_TEMP_00_T                shp_fd_tmap_temp_00;	//0xCCC40FCC
	PE_O22_2K_SHP_FD_TMAP_TEMP_01_T                shp_fd_tmap_temp_01;	//0xCCC40FD0
	PE_O22_2K_SHP_FD_TMAP_TEMP_02_T                shp_fd_tmap_temp_02;	//0xCCC40FD4
	PE_O22_2K_SHP_FD_TMAP_TEMP_03_T                shp_fd_tmap_temp_03;	//0xCCC40FD8
	PE_O22_2K_SHP_FD_TMAP_TEMP_04_T                shp_fd_tmap_temp_04;	//0xCCC40FDC
	PE_O22_2K_SHP_FD_TMAP_TEMP_05_T                shp_fd_tmap_temp_05;	//0xCCC40FE0
	PE_O22_2K_SHP_FD_TMAP_TEMP_06_T                shp_fd_tmap_temp_06;	//0xCCC40FE4
	PE_O22_2K_SHP_FD_TMAP_TEMP_07_T                shp_fd_tmap_temp_07;	//0xCCC40FE8
	PE_O22_2K_SHP_FD_TMAP_TEMP_08_T                shp_fd_tmap_temp_08;	//0xCCC40FEC
	PE_O22_2K_SHP_FD_TMAP_TEMP_09_T                shp_fd_tmap_temp_09;	//0xCCC40FF0
	PE_O22_2K_SHP_FD_TMAP_TEMP_0A_T                shp_fd_tmap_temp_0a;	//0xCCC40FF4
	PE_O22_2K_SHP_FD_TMAP_TEMP_0B_T                shp_fd_tmap_temp_0b;	//0xCCC40FF8
	PE_O22_2K_SHP_FD_TMAP_TEMP_0C_T                shp_fd_tmap_temp_0c;	//0xCCC40FFC
	PE_O22_2K_SHP_DJ_CTRL_00_T                          shp_dj_ctrl_00;	//0xCCC41000
	PE_O22_2K_SHP_DJ_CTRL_01_T                          shp_dj_ctrl_01;	//0xCCC41004
	PE_O22_2K_SHP_DJ_CTRL_02_T                          shp_dj_ctrl_02;	//0xCCC41008
	PE_O22_2K_SHP_DJ_CTRL_03_T                          shp_dj_ctrl_03;	//0xCCC4100C
	PE_O22_2K_SHP_DJ_CTRL_04_T                          shp_dj_ctrl_04;	//0xCCC41010
	PE_O22_2K_SHP_DJ_CTRL_05_T                          shp_dj_ctrl_05;	//0xCCC41014
	PE_O22_2K_SHP_DJ_CTRL_06_T                          shp_dj_ctrl_06;	//0xCCC41018
	PE_O22_2K_SHP_DJ_CTRL_07_T                          shp_dj_ctrl_07;	//0xCCC4101C
	PE_O22_2K_SHP_DJ_CTRL_08_T                          shp_dj_ctrl_08;	//0xCCC41020
	PE_O22_2K_SHP_DJ_CTRL_09_T                          shp_dj_ctrl_09;	//0xCCC41024
	PE_O22_2K_SHP_DJ_CTRL_0A_T                          shp_dj_ctrl_0a;	//0xCCC41028
	PE_O22_2K_SHP_DJ_CTRL_0B_T                          shp_dj_ctrl_0b;	//0xCCC4102C
	PE_O22_2K_SHP_DJ_CTRL_0C_T                          shp_dj_ctrl_0c;	//0xCCC41030
	PE_O22_2K_SHP_DJ_CTRL_0D_T                          shp_dj_ctrl_0d;	//0xCCC41034
	PE_O22_2K_SHP_DJ_CTRL_0E_T                          shp_dj_ctrl_0e;	//0xCCC41038
	PE_O22_2K_SHP_DJ_CTRL_0F_T                          shp_dj_ctrl_0f;	//0xCCC4103C
	PE_O22_2K_SHP_DJ_CTRL_10_T                          shp_dj_ctrl_10;	//0xCCC41040
	PE_O22_2K_SHP_DJ_CTRL_11_T                          shp_dj_ctrl_11;	//0xCCC41044
	PE_O22_2K_SHP_DJ_CTRL_12_T                          shp_dj_ctrl_12;	//0xCCC41048
	PE_O22_2K_SHP_DJ_CTRL_13_T                          shp_dj_ctrl_13;	//0xCCC4104C
	PE_O22_2K_SHP_DJ_CTRL_14_T                          shp_dj_ctrl_14;	//0xCCC41050
	PE_O22_2K_SHP_DJ_CTRL_15_T                          shp_dj_ctrl_15;	//0xCCC41054
	PE_O22_2K_SHP_DJ_CTRL_16_T                          shp_dj_ctrl_16;	//0xCCC41058
	PE_O22_2K_SHP_DJ_CTRL_17_T                          shp_dj_ctrl_17;	//0xCCC4105C
	PE_O22_2K_SHP_DJ_CTRL_18_T                          shp_dj_ctrl_18;	//0xCCC41060
	PE_O22_2K_SHP_DJ_CTRL_19_T                          shp_dj_ctrl_19;	//0xCCC41064
	PE_O22_2K_SHP_DJ_CTRL_1A_T                          shp_dj_ctrl_1a;	//0xCCC41068
	PE_O22_2K_SHP_DJ_CTRL_1B_T                          shp_dj_ctrl_1b;	//0xCCC4106C
	PE_O22_2K_SHP_DJ_CTRL_1C_T                          shp_dj_ctrl_1c;	//0xCCC41070
	PE_O22_2K_SHP_DJ_CTRL_1D_T                          shp_dj_ctrl_1d;	//0xCCC41074
	PE_O22_2K_SHP_DJ_CTRL_1E_T                          shp_dj_ctrl_1e;	//0xCCC41078
	PE_O22_2K_SHP_DJ_CTRL_1F_T                          shp_dj_ctrl_1f;	//0xCCC4107C
	PE_O22_2K_SHP_DJ_CTRL_20_T                          shp_dj_ctrl_20;	//0xCCC41080
	UINT32                                                   reserved95;	//0xCCC41084
	UINT32                                                   reserved96;	//0xCCC41088
	UINT32                                                   reserved97;	//0xCCC4108C
	PE_O22_2K_SHP_DB_CTRL_00_T                          shp_db_ctrl_00;	//0xCCC41090
	PE_O22_2K_SHP_DB_CTRL_01_T                          shp_db_ctrl_01;	//0xCCC41094
	UINT32                                                   reserved98;	//0xCCC41098
	UINT32                                                   reserved99;	//0xCCC4109C
	PE_O22_2K_SHP_DJ_WIN_CTRL_00_T                  shp_dj_win_ctrl_00;	//0xCCC410A0
	PE_O22_2K_SHP_DJ_WIN_CTRL_01_T                  shp_dj_win_ctrl_01;	//0xCCC410A4
	PE_O22_2K_SHP_DJ_WIN_CTRL_02_T                  shp_dj_win_ctrl_02;	//0xCCC410A8
	PE_O22_2K_SHP_DJ_WIN_CTRL_03_T                  shp_dj_win_ctrl_03;	//0xCCC410AC
	PE_O22_2K_SHP_DJ_WIN_CTRL_04_T                  shp_dj_win_ctrl_04;	//0xCCC410B0
	UINT32                                                  reserved100;	//0xCCC410B4
	UINT32                                                  reserved101;	//0xCCC410B8
	UINT32                                                  reserved102;	//0xCCC410BC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T      shp_dj_text_gain_ctrl_00;	//0xCCC410C0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T      shp_dj_text_gain_ctrl_01;	//0xCCC410C4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T      shp_dj_text_gain_ctrl_02;	//0xCCC410C8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T      shp_dj_text_gain_ctrl_03;	//0xCCC410CC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T      shp_dj_text_gain_ctrl_04;	//0xCCC410D0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T      shp_dj_text_gain_ctrl_05;	//0xCCC410D4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T      shp_dj_text_gain_ctrl_06;	//0xCCC410D8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T      shp_dj_text_gain_ctrl_07;	//0xCCC410DC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T      shp_dj_text_gain_ctrl_08;	//0xCCC410E0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T      shp_dj_text_gain_ctrl_09;	//0xCCC410E4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T      shp_dj_text_gain_ctrl_10;	//0xCCC410E8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T      shp_dj_text_gain_ctrl_11;	//0xCCC410EC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T      shp_dj_text_gain_ctrl_12;	//0xCCC410F0
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T      shp_dj_text_gain_ctrl_13;	//0xCCC410F4
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T      shp_dj_text_gain_ctrl_14;	//0xCCC410F8
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T      shp_dj_text_gain_ctrl_15;	//0xCCC410FC
	PE_O22_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T      shp_dj_text_gain_ctrl_16;	//0xCCC41100
	UINT32                                                  reserved103;	//0xCCC41104
	UINT32                                                  reserved104;	//0xCCC41108
	UINT32                                                  reserved105;	//0xCCC4110C
	UINT32                                                  reserved106;	//0xCCC41110
	UINT32                                                  reserved107;	//0xCCC41114
	UINT32                                                  reserved108;	//0xCCC41118
	UINT32                                                  reserved109;	//0xCCC4111C
	UINT32                                                  reserved110;	//0xCCC41120
	UINT32                                                  reserved111;	//0xCCC41124
	UINT32                                                  reserved112;	//0xCCC41128
	UINT32                                                  reserved113;	//0xCCC4112C
	UINT32                                                  reserved114;	//0xCCC41130
	UINT32                                                  reserved115;	//0xCCC41134
	UINT32                                                  reserved116;	//0xCCC41138
	UINT32                                                  reserved117;	//0xCCC4113C
	UINT32                                                  reserved118;	//0xCCC41140
	UINT32                                                  reserved119;	//0xCCC41144
	UINT32                                                  reserved120;	//0xCCC41148
	UINT32                                                  reserved121;	//0xCCC4114C
	UINT32                                                  reserved122;	//0xCCC41150
	UINT32                                                  reserved123;	//0xCCC41154
	UINT32                                                  reserved124;	//0xCCC41158
	UINT32                                                  reserved125;	//0xCCC4115C
	UINT32                                                  reserved126;	//0xCCC41160
	UINT32                                                  reserved127;	//0xCCC41164
	UINT32                                                  reserved128;	//0xCCC41168
	UINT32                                                  reserved129;	//0xCCC4116C
	UINT32                                                  reserved130;	//0xCCC41170
	UINT32                                                  reserved131;	//0xCCC41174
	UINT32                                                  reserved132;	//0xCCC41178
	UINT32                                                  reserved133;	//0xCCC4117C
	UINT32                                                  reserved134;	//0xCCC41180
	UINT32                                                  reserved135;	//0xCCC41184
	UINT32                                                  reserved136;	//0xCCC41188
	UINT32                                                  reserved137;	//0xCCC4118C
	UINT32                                                  reserved138;	//0xCCC41190
	UINT32                                                  reserved139;	//0xCCC41194
	UINT32                                                  reserved140;	//0xCCC41198
	UINT32                                                  reserved141;	//0xCCC4119C
	UINT32                                                  reserved142;	//0xCCC411A0
	UINT32                                                  reserved143;	//0xCCC411A4
	UINT32                                                  reserved144;	//0xCCC411A8
	UINT32                                                  reserved145;	//0xCCC411AC
	UINT32                                                  reserved146;	//0xCCC411B0
	UINT32                                                  reserved147;	//0xCCC411B4
	UINT32                                                  reserved148;	//0xCCC411B8
	UINT32                                                  reserved149;	//0xCCC411BC
	UINT32                                                  reserved150;	//0xCCC411C0
	UINT32                                                  reserved151;	//0xCCC411C4
	UINT32                                                  reserved152;	//0xCCC411C8
	UINT32                                                  reserved153;	//0xCCC411CC
	UINT32                                                  reserved154;	//0xCCC411D0
	UINT32                                                  reserved155;	//0xCCC411D4
	UINT32                                                  reserved156;	//0xCCC411D8
	UINT32                                                  reserved157;	//0xCCC411DC
	UINT32                                                  reserved158;	//0xCCC411E0
	UINT32                                                  reserved159;	//0xCCC411E4
	UINT32                                                  reserved160;	//0xCCC411E8
	UINT32                                                  reserved161;	//0xCCC411EC
	UINT32                                                  reserved162;	//0xCCC411F0
	UINT32                                                  reserved163;	//0xCCC411F4
	UINT32                                                  reserved164;	//0xCCC411F8
	UINT32                                                  reserved165;	//0xCCC411FC
	PE_O22_2K_SHP_CORE_STAT_00_T                      shp_core_stat_00;	//0xCCC41200
	PE_O22_2K_SHP_CORE_STAT_01_T                      shp_core_stat_01;	//0xCCC41204
	PE_O22_2K_SHP_CORE_STAT_02_T                      shp_core_stat_02;	//0xCCC41208
	PE_O22_2K_SHP_CORE_STAT_03_T                      shp_core_stat_03;	//0xCCC4120C
	PE_O22_2K_SHP_CORE_STAT_04_T                      shp_core_stat_04;	//0xCCC41210
	PE_O22_2K_SHP_CORE_STAT_05_T                      shp_core_stat_05;	//0xCCC41214
	UINT32                                                  reserved166;	//0xCCC41218
	UINT32                                                  reserved167;	//0xCCC4121C
	UINT32                                                  reserved168;	//0xCCC41220
	UINT32                                                  reserved169;	//0xCCC41224
	UINT32                                                  reserved170;	//0xCCC41228
	UINT32                                                  reserved171;	//0xCCC4122C
	UINT32                                                  reserved172;	//0xCCC41230
	UINT32                                                  reserved173;	//0xCCC41234
	UINT32                                                  reserved174;	//0xCCC41238
	UINT32                                                  reserved175;	//0xCCC4123C
	UINT32                                                  reserved176;	//0xCCC41240
	UINT32                                                  reserved177;	//0xCCC41244
	UINT32                                                  reserved178;	//0xCCC41248
	UINT32                                                  reserved179;	//0xCCC4124C
	UINT32                                                  reserved180;	//0xCCC41250
	UINT32                                                  reserved181;	//0xCCC41254
	UINT32                                                  reserved182;	//0xCCC41258
	UINT32                                                  reserved183;	//0xCCC4125C
	PE_O22_2K_SHP_CORE_FD_STAT_00_T                shp_core_fd_stat_00;	//0xCCC41260
	PE_O22_2K_SHP_CORE_FD_STAT_01_T                shp_core_fd_stat_01;	//0xCCC41264
	PE_O22_2K_SHP_CORE_FD_STAT_02_T                shp_core_fd_stat_02;	//0xCCC41268
	PE_O22_2K_SHP_CORE_FD_STAT_03_T                shp_core_fd_stat_03;	//0xCCC4126C
	UINT32                                                  reserved184;	//0xCCC41270
	UINT32                                                  reserved185;	//0xCCC41274
	UINT32                                                  reserved186;	//0xCCC41278
	UINT32                                                  reserved187;	//0xCCC4127C
	UINT32                                                  reserved188;	//0xCCC41280
	UINT32                                                  reserved189;	//0xCCC41284
	UINT32                                                  reserved190;	//0xCCC41288
	UINT32                                                  reserved191;	//0xCCC4128C
	UINT32                                                  reserved192;	//0xCCC41290
	UINT32                                                  reserved193;	//0xCCC41294
	UINT32                                                  reserved194;	//0xCCC41298
	UINT32                                                  reserved195;	//0xCCC4129C
	UINT32                                                  reserved196;	//0xCCC412A0
	UINT32                                                  reserved197;	//0xCCC412A4
	UINT32                                                  reserved198;	//0xCCC412A8
	UINT32                                                  reserved199;	//0xCCC412AC
	UINT32                                                  reserved200;	//0xCCC412B0
	UINT32                                                  reserved201;	//0xCCC412B4
	UINT32                                                  reserved202;	//0xCCC412B8
	UINT32                                                  reserved203;	//0xCCC412BC
	UINT32                                                  reserved204;	//0xCCC412C0
	UINT32                                                  reserved205;	//0xCCC412C4
	UINT32                                                  reserved206;	//0xCCC412C8
	UINT32                                                  reserved207;	//0xCCC412CC
	UINT32                                                  reserved208;	//0xCCC412D0
	UINT32                                                  reserved209;	//0xCCC412D4
	UINT32                                                  reserved210;	//0xCCC412D8
	UINT32                                                  reserved211;	//0xCCC412DC
	UINT32                                                  reserved212;	//0xCCC412E0
	UINT32                                                  reserved213;	//0xCCC412E4
	UINT32                                                  reserved214;	//0xCCC412E8
	UINT32                                                  reserved215;	//0xCCC412EC
	UINT32                                                  reserved216;	//0xCCC412F0
	UINT32                                                  reserved217;	//0xCCC412F4
	UINT32                                                  reserved218;	//0xCCC412F8
	UINT32                                                  reserved219;	//0xCCC412FC
	PE_O22_2K_SHP_CORE_TMAP_STAT_00_T            shp_core_tmap_stat_00;	//0xCCC41300
	PE_O22_2K_SHP_CORE_TMAP_STAT_01_T            shp_core_tmap_stat_01;	//0xCCC41304
	PE_O22_2K_SHP_CORE_TMAP_STAT_02_T            shp_core_tmap_stat_02;	//0xCCC41308
	PE_O22_2K_SHP_CORE_TMAP_STAT_03_T            shp_core_tmap_stat_03;	//0xCCC4130C
	PE_O22_2K_SHP_CORE_TMAP_STAT_04_T            shp_core_tmap_stat_04;	//0xCCC41310
	PE_O22_2K_SHP_CORE_TMAP_STAT_05_T            shp_core_tmap_stat_05;	//0xCCC41314
	PE_O22_2K_SHP_CORE_TMAP_STAT_06_T            shp_core_tmap_stat_06;	//0xCCC41318
	PE_O22_2K_SHP_CORE_TMAP_STAT_07_T            shp_core_tmap_stat_07;	//0xCCC4131C
	UINT32                                                  reserved220;	//0xCCC41320
	UINT32                                                  reserved221;	//0xCCC41324
	UINT32                                                  reserved222;	//0xCCC41328
	UINT32                                                  reserved223;	//0xCCC4132C
	UINT32                                                  reserved224;	//0xCCC41330
	UINT32                                                  reserved225;	//0xCCC41334
	UINT32                                                  reserved226;	//0xCCC41338
	UINT32                                                  reserved227;	//0xCCC4133C
	UINT32                                                  reserved228;	//0xCCC41340
	UINT32                                                  reserved229;	//0xCCC41344
	UINT32                                                  reserved230;	//0xCCC41348
	UINT32                                                  reserved231;	//0xCCC4134C
	UINT32                                                  reserved232;	//0xCCC41350
	UINT32                                                  reserved233;	//0xCCC41354
	UINT32                                                  reserved234;	//0xCCC41358
	UINT32                                                  reserved235;	//0xCCC4135C
	UINT32                                                  reserved236;	//0xCCC41360
	UINT32                                                  reserved237;	//0xCCC41364
	UINT32                                                  reserved238;	//0xCCC41368
	UINT32                                                  reserved239;	//0xCCC4136C
	UINT32                                                  reserved240;	//0xCCC41370
	UINT32                                                  reserved241;	//0xCCC41374
	UINT32                                                  reserved242;	//0xCCC41378
	UINT32                                                  reserved243;	//0xCCC4137C
	UINT32                                                  reserved244;	//0xCCC41380
	UINT32                                                  reserved245;	//0xCCC41384
	UINT32                                                  reserved246;	//0xCCC41388
	UINT32                                                  reserved247;	//0xCCC4138C
	UINT32                                                  reserved248;	//0xCCC41390
	UINT32                                                  reserved249;	//0xCCC41394
	UINT32                                                  reserved250;	//0xCCC41398
	UINT32                                                  reserved251;	//0xCCC4139C
	UINT32                                                  reserved252;	//0xCCC413A0
	UINT32                                                  reserved253;	//0xCCC413A4
	UINT32                                                  reserved254;	//0xCCC413A8
	UINT32                                                  reserved255;	//0xCCC413AC
	UINT32                                                  reserved256;	//0xCCC413B0
	UINT32                                                  reserved257;	//0xCCC413B4
	UINT32                                                  reserved258;	//0xCCC413B8
	UINT32                                                  reserved259;	//0xCCC413BC
	UINT32                                                  reserved260;	//0xCCC413C0
	UINT32                                                  reserved261;	//0xCCC413C4
	UINT32                                                  reserved262;	//0xCCC413C8
	UINT32                                                  reserved263;	//0xCCC413CC
	UINT32                                                  reserved264;	//0xCCC413D0
	UINT32                                                  reserved265;	//0xCCC413D4
	UINT32                                                  reserved266;	//0xCCC413D8
	UINT32                                                  reserved267;	//0xCCC413DC
	UINT32                                                  reserved268;	//0xCCC413E0
	UINT32                                                  reserved269;	//0xCCC413E4
	UINT32                                                  reserved270;	//0xCCC413E8
	UINT32                                                  reserved271;	//0xCCC413EC
	PE_O22_2K_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0xCCC413F0
	PE_O22_2K_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0xCCC413F4
	PE_O22_2K_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0xCCC413F8
	PE_O22_2K_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0xCCC413FC
}PE_SR_2K_SHP_REG_O22_T;

typedef struct {
	PE_O22_2K_SHC_SHP_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0xCCC41400
	PE_O22_2K_SHC_SHP_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0xCCC41404
	PE_O22_2K_SHC_SHP_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0xCCC41408
	PE_O22_2K_SHC_SHP_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0xCCC4140C
	UINT32                                                    reserved0;	//0xCCC41410
	UINT32                                                    reserved1;	//0xCCC41414
	UINT32                                                    reserved2;	//0xCCC41418
	UINT32                                                    reserved3;	//0xCCC4141C
	UINT32                                                    reserved4;	//0xCCC41420
	UINT32                                                    reserved5;	//0xCCC41424
	UINT32                                                    reserved6;	//0xCCC41428
	UINT32                                                    reserved7;	//0xCCC4142C
	UINT32                                                    reserved8;	//0xCCC41430
	UINT32                                                    reserved9;	//0xCCC41434
	UINT32                                                   reserved10;	//0xCCC41438
	UINT32                                                   reserved11;	//0xCCC4143C
	UINT32                                                   reserved12;	//0xCCC41440
	UINT32                                                   reserved13;	//0xCCC41444
	UINT32                                                   reserved14;	//0xCCC41448
	UINT32                                                   reserved15;	//0xCCC4144C
	UINT32                                                   reserved16;	//0xCCC41450
	UINT32                                                   reserved17;	//0xCCC41454
	UINT32                                                   reserved18;	//0xCCC41458
	UINT32                                                   reserved19;	//0xCCC4145C
	UINT32                                                   reserved20;	//0xCCC41460
	UINT32                                                   reserved21;	//0xCCC41464
	UINT32                                                   reserved22;	//0xCCC41468
	UINT32                                                   reserved23;	//0xCCC4146C
	UINT32                                                   reserved24;	//0xCCC41470
	UINT32                                                   reserved25;	//0xCCC41474
	UINT32                                                   reserved26;	//0xCCC41478
	UINT32                                                   reserved27;	//0xCCC4147C
	UINT32                                                   reserved28;	//0xCCC41480
	UINT32                                                   reserved29;	//0xCCC41484
	UINT32                                                   reserved30;	//0xCCC41488
	UINT32                                                   reserved31;	//0xCCC4148C
	UINT32                                                   reserved32;	//0xCCC41490
	UINT32                                                   reserved33;	//0xCCC41494
	UINT32                                                   reserved34;	//0xCCC41498
	UINT32                                                   reserved35;	//0xCCC4149C
	UINT32                                                   reserved36;	//0xCCC414A0
	UINT32                                                   reserved37;	//0xCCC414A4
	UINT32                                                   reserved38;	//0xCCC414A8
	UINT32                                                   reserved39;	//0xCCC414AC
	UINT32                                                   reserved40;	//0xCCC414B0
	UINT32                                                   reserved41;	//0xCCC414B4
	UINT32                                                   reserved42;	//0xCCC414B8
	UINT32                                                   reserved43;	//0xCCC414BC
	UINT32                                                   reserved44;	//0xCCC414C0
	UINT32                                                   reserved45;	//0xCCC414C4
	UINT32                                                   reserved46;	//0xCCC414C8
	UINT32                                                   reserved47;	//0xCCC414CC
	UINT32                                                   reserved48;	//0xCCC414D0
	UINT32                                                   reserved49;	//0xCCC414D4
	UINT32                                                   reserved50;	//0xCCC414D8
	UINT32                                                   reserved51;	//0xCCC414DC
	UINT32                                                   reserved52;	//0xCCC414E0
	UINT32                                                   reserved53;	//0xCCC414E4
	UINT32                                                   reserved54;	//0xCCC414E8
	UINT32                                                   reserved55;	//0xCCC414EC
	UINT32                                                   reserved56;	//0xCCC414F0
	UINT32                                                   reserved57;	//0xCCC414F4
	UINT32                                                   reserved58;	//0xCCC414F8
	UINT32                                                   reserved59;	//0xCCC414FC
	PE_O22_2K_SHC_SHP_PAT_GEN_CTRL_00_T                   shp_pat_gen_ctrl_00;	//0xCCC41500
	UINT32                                                   reserved60;	//0xCCC41504
	UINT32                                                   reserved61;	//0xCCC41508
	UINT32                                                   reserved62;	//0xCCC4150C
	UINT32                                                   reserved63;	//0xCCC41510
	UINT32                                                   reserved64;	//0xCCC41514
	UINT32                                                   reserved65;	//0xCCC41518
	UINT32                                                   reserved66;	//0xCCC4151C
	UINT32                                                   reserved67;	//0xCCC41520
	UINT32                                                   reserved68;	//0xCCC41524
	UINT32                                                   reserved69;	//0xCCC41528
	UINT32                                                   reserved70;	//0xCCC4152C
	UINT32                                                   reserved71;	//0xCCC41530
	UINT32                                                   reserved72;	//0xCCC41534
	UINT32                                                   reserved73;	//0xCCC41538
	UINT32                                                   reserved74;	//0xCCC4153C
	UINT32                                                   reserved75;	//0xCCC41540
	UINT32                                                   reserved76;	//0xCCC41544
	UINT32                                                   reserved77;	//0xCCC41548
	UINT32                                                   reserved78;	//0xCCC4154C
	UINT32                                                   reserved79;	//0xCCC41550
	UINT32                                                   reserved80;	//0xCCC41554
	UINT32                                                   reserved81;	//0xCCC41558
	UINT32                                                   reserved82;	//0xCCC4155C
	UINT32                                                   reserved83;	//0xCCC41560
	UINT32                                                   reserved84;	//0xCCC41564
	UINT32                                                   reserved85;	//0xCCC41568
	UINT32                                                   reserved86;	//0xCCC4156C
	UINT32                                                   reserved87;	//0xCCC41570
	UINT32                                                   reserved88;	//0xCCC41574
	UINT32                                                   reserved89;	//0xCCC41578
	UINT32                                                   reserved90;	//0xCCC4157C
	UINT32                                                   reserved91;	//0xCCC41580
	UINT32                                                   reserved92;	//0xCCC41584
	UINT32                                                   reserved93;	//0xCCC41588
	UINT32                                                   reserved94;	//0xCCC4158C
	UINT32                                                   reserved95;	//0xCCC41590
	UINT32                                                   reserved96;	//0xCCC41594
	UINT32                                                   reserved97;	//0xCCC41598
	UINT32                                                   reserved98;	//0xCCC4159C
	UINT32                                                   reserved99;	//0xCCC415A0
	UINT32                                                  reserved100;	//0xCCC415A4
	UINT32                                                  reserved101;	//0xCCC415A8
	UINT32                                                  reserved102;	//0xCCC415AC
	UINT32                                                  reserved103;	//0xCCC415B0
	UINT32                                                  reserved104;	//0xCCC415B4
	UINT32                                                  reserved105;	//0xCCC415B8
	UINT32                                                  reserved106;	//0xCCC415BC
	UINT32                                                  reserved107;	//0xCCC415C0
	UINT32                                                  reserved108;	//0xCCC415C4
	UINT32                                                  reserved109;	//0xCCC415C8
	UINT32                                                  reserved110;	//0xCCC415CC
	UINT32                                                  reserved111;	//0xCCC415D0
	UINT32                                                  reserved112;	//0xCCC415D4
	UINT32                                                  reserved113;	//0xCCC415D8
	UINT32                                                  reserved114;	//0xCCC415DC
	UINT32                                                  reserved115;	//0xCCC415E0
	UINT32                                                  reserved116;	//0xCCC415E4
	UINT32                                                  reserved117;	//0xCCC415E8
	UINT32                                                  reserved118;	//0xCCC415EC
	UINT32                                                  reserved119;	//0xCCC415F0
	UINT32                                                  reserved120;	//0xCCC415F4
	UINT32                                                  reserved121;	//0xCCC415F8
	UINT32                                                  reserved122;	//0xCCC415FC
	UINT32                                                  reserved123;	//0xCCC41600
	UINT32                                                  reserved124;	//0xCCC41604
	UINT32                                                  reserved125;	//0xCCC41608
	UINT32                                                  reserved126;	//0xCCC4160C
	UINT32                                                  reserved127;	//0xCCC41610
	UINT32                                                  reserved128;	//0xCCC41614
	UINT32                                                  reserved129;	//0xCCC41618
	UINT32                                                  reserved130;	//0xCCC4161C
	UINT32                                                  reserved131;	//0xCCC41620
	UINT32                                                  reserved132;	//0xCCC41624
	UINT32                                                  reserved133;	//0xCCC41628
	UINT32                                                  reserved134;	//0xCCC4162C
	UINT32                                                  reserved135;	//0xCCC41630
	UINT32                                                  reserved136;	//0xCCC41634
	UINT32                                                  reserved137;	//0xCCC41638
	UINT32                                                  reserved138;	//0xCCC4163C
	UINT32                                                  reserved139;	//0xCCC41640
	UINT32                                                  reserved140;	//0xCCC41644
	UINT32                                                  reserved141;	//0xCCC41648
	UINT32                                                  reserved142;	//0xCCC4164C
	UINT32                                                  reserved143;	//0xCCC41650
	UINT32                                                  reserved144;	//0xCCC41654
	UINT32                                                  reserved145;	//0xCCC41658
	UINT32                                                  reserved146;	//0xCCC4165C
	UINT32                                                  reserved147;	//0xCCC41660
	UINT32                                                  reserved148;	//0xCCC41664
	UINT32                                                  reserved149;	//0xCCC41668
	UINT32                                                  reserved150;	//0xCCC4166C
	UINT32                                                  reserved151;	//0xCCC41670
	UINT32                                                  reserved152;	//0xCCC41674
	UINT32                                                  reserved153;	//0xCCC41678
	UINT32                                                  reserved154;	//0xCCC4167C
	UINT32                                                  reserved155;	//0xCCC41680
	UINT32                                                  reserved156;	//0xCCC41684
	UINT32                                                  reserved157;	//0xCCC41688
	UINT32                                                  reserved158;	//0xCCC4168C
	UINT32                                                  reserved159;	//0xCCC41690
	UINT32                                                  reserved160;	//0xCCC41694
	UINT32                                                  reserved161;	//0xCCC41698
	UINT32                                                  reserved162;	//0xCCC4169C
	UINT32                                                  reserved163;	//0xCCC416A0
	UINT32                                                  reserved164;	//0xCCC416A4
	UINT32                                                  reserved165;	//0xCCC416A8
	UINT32                                                  reserved166;	//0xCCC416AC
	UINT32                                                  reserved167;	//0xCCC416B0
	UINT32                                                  reserved168;	//0xCCC416B4
	UINT32                                                  reserved169;	//0xCCC416B8
	UINT32                                                  reserved170;	//0xCCC416BC
	UINT32                                                  reserved171;	//0xCCC416C0
	UINT32                                                  reserved172;	//0xCCC416C4
	UINT32                                                  reserved173;	//0xCCC416C8
	UINT32                                                  reserved174;	//0xCCC416CC
	UINT32                                                  reserved175;	//0xCCC416D0
	UINT32                                                  reserved176;	//0xCCC416D4
	UINT32                                                  reserved177;	//0xCCC416D8
	UINT32                                                  reserved178;	//0xCCC416DC
	UINT32                                                  reserved179;	//0xCCC416E0
	UINT32                                                  reserved180;	//0xCCC416E4
	UINT32                                                  reserved181;	//0xCCC416E8
	UINT32                                                  reserved182;	//0xCCC416EC
	UINT32                                                  reserved183;	//0xCCC416F0
	UINT32                                                  reserved184;	//0xCCC416F4
	UINT32                                                  reserved185;	//0xCCC416F8
	UINT32                                                  reserved186;	//0xCCC416FC
	UINT32                                                  reserved187;	//0xCCC41700
	UINT32                                                  reserved188;	//0xCCC41704
	UINT32                                                  reserved189;	//0xCCC41708
	UINT32                                                  reserved190;	//0xCCC4170C
	UINT32                                                  reserved191;	//0xCCC41710
	UINT32                                                  reserved192;	//0xCCC41714
	UINT32                                                  reserved193;	//0xCCC41718
	UINT32                                                  reserved194;	//0xCCC4171C
	UINT32                                                  reserved195;	//0xCCC41720
	UINT32                                                  reserved196;	//0xCCC41724
	UINT32                                                  reserved197;	//0xCCC41728
	UINT32                                                  reserved198;	//0xCCC4172C
	UINT32                                                  reserved199;	//0xCCC41730
	UINT32                                                  reserved200;	//0xCCC41734
	UINT32                                                  reserved201;	//0xCCC41738
	UINT32                                                  reserved202;	//0xCCC4173C
	UINT32                                                  reserved203;	//0xCCC41740
	UINT32                                                  reserved204;	//0xCCC41744
	UINT32                                                  reserved205;	//0xCCC41748
	UINT32                                                  reserved206;	//0xCCC4174C
	UINT32                                                  reserved207;	//0xCCC41750
	UINT32                                                  reserved208;	//0xCCC41754
	UINT32                                                  reserved209;	//0xCCC41758
	UINT32                                                  reserved210;	//0xCCC4175C
	UINT32                                                  reserved211;	//0xCCC41760
	UINT32                                                  reserved212;	//0xCCC41764
	UINT32                                                  reserved213;	//0xCCC41768
	UINT32                                                  reserved214;	//0xCCC4176C
	UINT32                                                  reserved215;	//0xCCC41770
	UINT32                                                  reserved216;	//0xCCC41774
	UINT32                                                  reserved217;	//0xCCC41778
	UINT32                                                  reserved218;	//0xCCC4177C
	UINT32                                                  reserved219;	//0xCCC41780
	UINT32                                                  reserved220;	//0xCCC41784
	UINT32                                                  reserved221;	//0xCCC41788
	UINT32                                                  reserved222;	//0xCCC4178C
	UINT32                                                  reserved223;	//0xCCC41790
	UINT32                                                  reserved224;	//0xCCC41794
	UINT32                                                  reserved225;	//0xCCC41798
	UINT32                                                  reserved226;	//0xCCC4179C
	UINT32                                                  reserved227;	//0xCCC417A0
	UINT32                                                  reserved228;	//0xCCC417A4
	UINT32                                                  reserved229;	//0xCCC417A8
	UINT32                                                  reserved230;	//0xCCC417AC
	UINT32                                                  reserved231;	//0xCCC417B0
	UINT32                                                  reserved232;	//0xCCC417B4
	UINT32                                                  reserved233;	//0xCCC417B8
	UINT32                                                  reserved234;	//0xCCC417BC
	UINT32                                                  reserved235;	//0xCCC417C0
	UINT32                                                  reserved236;	//0xCCC417C4
	UINT32                                                  reserved237;	//0xCCC417C8
	UINT32                                                  reserved238;	//0xCCC417CC
	UINT32                                                  reserved239;	//0xCCC417D0
	UINT32                                                  reserved240;	//0xCCC417D4
	UINT32                                                  reserved241;	//0xCCC417D8
	UINT32                                                  reserved242;	//0xCCC417DC
	UINT32                                                  reserved243;	//0xCCC417E0
	UINT32                                                  reserved244;	//0xCCC417E4
	UINT32                                                  reserved245;	//0xCCC417E8
	UINT32                                                  reserved246;	//0xCCC417EC
	UINT32                                                  reserved247;	//0xCCC417F0
	UINT32                                                  reserved248;	//0xCCC417F4
	UINT32                                                  reserved249;	//0xCCC417F8
	UINT32                                                  reserved250;	//0xCCC417FC
	PE_O22_2K_SHC_SHP_CDJ_CTRL_00_T                           shp_cdj_ctrl_00;	//0xCCC41800
	PE_O22_2K_SHC_SHP_CDJ_CTRL_01_T                           shp_cdj_ctrl_01;	//0xCCC41804
	PE_O22_2K_SHC_SHP_CDJ_CTRL_02_T                           shp_cdj_ctrl_02;	//0xCCC41808
	PE_O22_2K_SHC_SHP_CDJ_CTRL_03_T                           shp_cdj_ctrl_03;	//0xCCC4180C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_04_T                           shp_cdj_ctrl_04;	//0xCCC41810
	PE_O22_2K_SHC_SHP_CDJ_CTRL_05_T                           shp_cdj_ctrl_05;	//0xCCC41814
	PE_O22_2K_SHC_SHP_CDJ_CTRL_06_T                           shp_cdj_ctrl_06;	//0xCCC41818
	PE_O22_2K_SHC_SHP_CDJ_CTRL_07_T                           shp_cdj_ctrl_07;	//0xCCC4181C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_08_T                           shp_cdj_ctrl_08;	//0xCCC41820
	PE_O22_2K_SHC_SHP_CDJ_CTRL_09_T                           shp_cdj_ctrl_09;	//0xCCC41824
	PE_O22_2K_SHC_SHP_CDJ_CTRL_0A_T                           shp_cdj_ctrl_0a;	//0xCCC41828
	PE_O22_2K_SHC_SHP_CDJ_CTRL_0B_T                           shp_cdj_ctrl_0b;	//0xCCC4182C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_0C_T                           shp_cdj_ctrl_0c;	//0xCCC41830
	PE_O22_2K_SHC_SHP_CDJ_CTRL_0D_T                           shp_cdj_ctrl_0d;	//0xCCC41834
	PE_O22_2K_SHC_SHP_CDJ_CTRL_0E_T                           shp_cdj_ctrl_0e;	//0xCCC41838
	PE_O22_2K_SHC_SHP_CDJ_CTRL_0F_T                           shp_cdj_ctrl_0f;	//0xCCC4183C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_10_T                           shp_cdj_ctrl_10;	//0xCCC41840
	PE_O22_2K_SHC_SHP_CDJ_CTRL_11_T                           shp_cdj_ctrl_11;	//0xCCC41844
	PE_O22_2K_SHC_SHP_CDJ_CTRL_12_T                           shp_cdj_ctrl_12;	//0xCCC41848
	PE_O22_2K_SHC_SHP_CDJ_CTRL_13_T                           shp_cdj_ctrl_13;	//0xCCC4184C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_14_T                           shp_cdj_ctrl_14;	//0xCCC41850
	PE_O22_2K_SHC_SHP_CDJ_CTRL_15_T                           shp_cdj_ctrl_15;	//0xCCC41854
	PE_O22_2K_SHC_SHP_CDJ_CTRL_16_T                           shp_cdj_ctrl_16;	//0xCCC41858
	PE_O22_2K_SHC_SHP_CDJ_CTRL_17_T                           shp_cdj_ctrl_17;	//0xCCC4185C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_18_T                           shp_cdj_ctrl_18;	//0xCCC41860
	PE_O22_2K_SHC_SHP_CDJ_CTRL_19_T                           shp_cdj_ctrl_19;	//0xCCC41864
	PE_O22_2K_SHC_SHP_CDJ_CTRL_1A_T                           shp_cdj_ctrl_1a;	//0xCCC41868
	PE_O22_2K_SHC_SHP_CDJ_CTRL_1B_T                           shp_cdj_ctrl_1b;	//0xCCC4186C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_1C_T                           shp_cdj_ctrl_1c;	//0xCCC41870
	PE_O22_2K_SHC_SHP_CDJ_CTRL_1D_T                           shp_cdj_ctrl_1d;	//0xCCC41874
	PE_O22_2K_SHC_SHP_CDJ_CTRL_1E_T                           shp_cdj_ctrl_1e;	//0xCCC41878
	PE_O22_2K_SHC_SHP_CDJ_CTRL_1F_T                           shp_cdj_ctrl_1f;	//0xCCC4187C
	PE_O22_2K_SHC_SHP_CDJ_CTRL_20_T                           shp_cdj_ctrl_20;	//0xCCC41880
	UINT32                                                  reserved251;	//0xCCC41884
	UINT32                                                  reserved252;	//0xCCC41888
	UINT32                                                  reserved253;	//0xCCC4188C
	PE_O22_2K_SHC_SHP_CDIR_BLUR_CTRL_00_T               shp_cdir_blur_ctrl_00;	//0xCCC41890
	PE_O22_2K_SHC_SHP_CDIR_BLUR_CTRL_01_T               shp_cdir_blur_ctrl_01;	//0xCCC41894
	UINT32                                                  reserved254;	//0xCCC41898
	UINT32                                                  reserved255;	//0xCCC4189C
	PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_00_T                   shp_cdj_win_ctrl_00;	//0xCCC418A0
	PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_01_T                   shp_cdj_win_ctrl_01;	//0xCCC418A4
	PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_02_T                   shp_cdj_win_ctrl_02;	//0xCCC418A8
	PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_03_T                   shp_cdj_win_ctrl_03;	//0xCCC418AC
	PE_O22_2K_SHC_SHP_CDJ_WIN_CTRL_04_T                   shp_cdj_win_ctrl_04;	//0xCCC418B0
	UINT32                                                  reserved256;	//0xCCC418B4
	UINT32                                                  reserved257;	//0xCCC418B8
	UINT32                                                  reserved258;	//0xCCC418BC
	UINT32                                                  reserved259;	//0xCCC418C0
	UINT32                                                  reserved260;	//0xCCC418C4
	UINT32                                                  reserved261;	//0xCCC418C8
	UINT32                                                  reserved262;	//0xCCC418CC
	UINT32                                                  reserved263;	//0xCCC418D0
	UINT32                                                  reserved264;	//0xCCC418D4
	UINT32                                                  reserved265;	//0xCCC418D8
	UINT32                                                  reserved266;	//0xCCC418DC
	UINT32                                                  reserved267;	//0xCCC418E0
	UINT32                                                  reserved268;	//0xCCC418E4
	UINT32                                                  reserved269;	//0xCCC418E8
	UINT32                                                  reserved270;	//0xCCC418EC
	UINT32                                                  reserved271;	//0xCCC418F0
	UINT32                                                  reserved272;	//0xCCC418F4
	UINT32                                                  reserved273;	//0xCCC418F8
	UINT32                                                  reserved274;	//0xCCC418FC
	UINT32                                                  reserved275;	//0xCCC41900
	UINT32                                                  reserved276;	//0xCCC41904
	UINT32                                                  reserved277;	//0xCCC41908
	UINT32                                                  reserved278;	//0xCCC4190C
	UINT32                                                  reserved279;	//0xCCC41910
	UINT32                                                  reserved280;	//0xCCC41914
	UINT32                                                  reserved281;	//0xCCC41918
	UINT32                                                  reserved282;	//0xCCC4191C
	UINT32                                                  reserved283;	//0xCCC41920
	UINT32                                                  reserved284;	//0xCCC41924
	UINT32                                                  reserved285;	//0xCCC41928
	UINT32                                                  reserved286;	//0xCCC4192C
	UINT32                                                  reserved287;	//0xCCC41930
	UINT32                                                  reserved288;	//0xCCC41934
	UINT32                                                  reserved289;	//0xCCC41938
	UINT32                                                  reserved290;	//0xCCC4193C
	UINT32                                                  reserved291;	//0xCCC41940
	UINT32                                                  reserved292;	//0xCCC41944
	UINT32                                                  reserved293;	//0xCCC41948
	UINT32                                                  reserved294;	//0xCCC4194C
	UINT32                                                  reserved295;	//0xCCC41950
	UINT32                                                  reserved296;	//0xCCC41954
	UINT32                                                  reserved297;	//0xCCC41958
	UINT32                                                  reserved298;	//0xCCC4195C
	UINT32                                                  reserved299;	//0xCCC41960
	UINT32                                                  reserved300;	//0xCCC41964
	UINT32                                                  reserved301;	//0xCCC41968
	UINT32                                                  reserved302;	//0xCCC4196C
	UINT32                                                  reserved303;	//0xCCC41970
	UINT32                                                  reserved304;	//0xCCC41974
	UINT32                                                  reserved305;	//0xCCC41978
	UINT32                                                  reserved306;	//0xCCC4197C
	UINT32                                                  reserved307;	//0xCCC41980
	UINT32                                                  reserved308;	//0xCCC41984
	UINT32                                                  reserved309;	//0xCCC41988
	UINT32                                                  reserved310;	//0xCCC4198C
	UINT32                                                  reserved311;	//0xCCC41990
	UINT32                                                  reserved312;	//0xCCC41994
	UINT32                                                  reserved313;	//0xCCC41998
	UINT32                                                  reserved314;	//0xCCC4199C
	UINT32                                                  reserved315;	//0xCCC419A0
	UINT32                                                  reserved316;	//0xCCC419A4
	UINT32                                                  reserved317;	//0xCCC419A8
	UINT32                                                  reserved318;	//0xCCC419AC
	UINT32                                                  reserved319;	//0xCCC419B0
	UINT32                                                  reserved320;	//0xCCC419B4
	UINT32                                                  reserved321;	//0xCCC419B8
	UINT32                                                  reserved322;	//0xCCC419BC
	UINT32                                                  reserved323;	//0xCCC419C0
	UINT32                                                  reserved324;	//0xCCC419C4
	UINT32                                                  reserved325;	//0xCCC419C8
	UINT32                                                  reserved326;	//0xCCC419CC
	UINT32                                                  reserved327;	//0xCCC419D0
	UINT32                                                  reserved328;	//0xCCC419D4
	UINT32                                                  reserved329;	//0xCCC419D8
	UINT32                                                  reserved330;	//0xCCC419DC
	UINT32                                                  reserved331;	//0xCCC419E0
	UINT32                                                  reserved332;	//0xCCC419E4
	UINT32                                                  reserved333;	//0xCCC419E8
	UINT32                                                  reserved334;	//0xCCC419EC
	UINT32                                                  reserved335;	//0xCCC419F0
	UINT32                                                  reserved336;	//0xCCC419F4
	UINT32                                                  reserved337;	//0xCCC419F8
	UINT32                                                  reserved338;	//0xCCC419FC
	PE_O22_2K_SHC_SHP_CORE_STAT_00_T                         shp_core_stat_00;	//0xCCC41A00
	PE_O22_2K_SHC_SHP_CORE_STAT_01_T                         shp_core_stat_01;	//0xCCC41A04
	PE_O22_2K_SHC_SHP_CORE_STAT_02_T                         shp_core_stat_02;	//0xCCC41A08
	PE_O22_2K_SHC_SHP_CORE_STAT_03_T                         shp_core_stat_03;	//0xCCC41A0C
	PE_O22_2K_SHC_SHP_CORE_STAT_04_T                         shp_core_stat_04;	//0xCCC41A10
	PE_O22_2K_SHC_SHP_CORE_STAT_05_T                         shp_core_stat_05;	//0xCCC41A14
	UINT32                                                  reserved339;	//0xCCC41A18
	UINT32                                                  reserved340;	//0xCCC41A1C
	UINT32                                                  reserved341;	//0xCCC41A20
	UINT32                                                  reserved342;	//0xCCC41A24
	UINT32                                                  reserved343;	//0xCCC41A28
	UINT32                                                  reserved344;	//0xCCC41A2C
	UINT32                                                  reserved345;	//0xCCC41A30
	UINT32                                                  reserved346;	//0xCCC41A34
	UINT32                                                  reserved347;	//0xCCC41A38
	UINT32                                                  reserved348;	//0xCCC41A3C
	UINT32                                                  reserved349;	//0xCCC41A40
	UINT32                                                  reserved350;	//0xCCC41A44
	UINT32                                                  reserved351;	//0xCCC41A48
	UINT32                                                  reserved352;	//0xCCC41A4C
	UINT32                                                  reserved353;	//0xCCC41A50
	UINT32                                                  reserved354;	//0xCCC41A54
	UINT32                                                  reserved355;	//0xCCC41A58
	UINT32                                                  reserved356;	//0xCCC41A5C
	UINT32                                                  reserved357;	//0xCCC41A60
	UINT32                                                  reserved358;	//0xCCC41A64
	UINT32                                                  reserved359;	//0xCCC41A68
	UINT32                                                  reserved360;	//0xCCC41A6C
	UINT32                                                  reserved361;	//0xCCC41A70
	UINT32                                                  reserved362;	//0xCCC41A74
	UINT32                                                  reserved363;	//0xCCC41A78
	UINT32                                                  reserved364;	//0xCCC41A7C
	UINT32                                                  reserved365;	//0xCCC41A80
	UINT32                                                  reserved366;	//0xCCC41A84
	UINT32                                                  reserved367;	//0xCCC41A88
	UINT32                                                  reserved368;	//0xCCC41A8C
	UINT32                                                  reserved369;	//0xCCC41A90
	UINT32                                                  reserved370;	//0xCCC41A94
	UINT32                                                  reserved371;	//0xCCC41A98
	UINT32                                                  reserved372;	//0xCCC41A9C
	UINT32                                                  reserved373;	//0xCCC41AA0
	UINT32                                                  reserved374;	//0xCCC41AA4
	UINT32                                                  reserved375;	//0xCCC41AA8
	UINT32                                                  reserved376;	//0xCCC41AAC
	UINT32                                                  reserved377;	//0xCCC41AB0
	UINT32                                                  reserved378;	//0xCCC41AB4
	UINT32                                                  reserved379;	//0xCCC41AB8
	UINT32                                                  reserved380;	//0xCCC41ABC
	UINT32                                                  reserved381;	//0xCCC41AC0
	UINT32                                                  reserved382;	//0xCCC41AC4
	UINT32                                                  reserved383;	//0xCCC41AC8
	UINT32                                                  reserved384;	//0xCCC41ACC
	UINT32                                                  reserved385;	//0xCCC41AD0
	UINT32                                                  reserved386;	//0xCCC41AD4
	UINT32                                                  reserved387;	//0xCCC41AD8
	UINT32                                                  reserved388;	//0xCCC41ADC
	UINT32                                                  reserved389;	//0xCCC41AE0
	UINT32                                                  reserved390;	//0xCCC41AE4
	UINT32                                                  reserved391;	//0xCCC41AE8
	UINT32                                                  reserved392;	//0xCCC41AEC
	PE_O22_2K_SHC_SHP_FSW_CTRL_00_T                           shp_fsw_ctrl_00;	//0xCCC41AF0
	PE_O22_2K_SHC_SHP_FSW_CTRL_01_T                           shp_fsw_ctrl_01;	//0xCCC41AF4
	PE_O22_2K_SHC_SHP_FSW_CTRL_02_T                           shp_fsw_ctrl_02;	//0xCCC41AF8
	PE_O22_2K_SHC_SHP_FSW_CTRL_03_T                           shp_fsw_ctrl_03;	//0xCCC41AFC
}PE_SR_2K_SHC_REG_O22_T;


typedef struct {
	PE_O22_SR_MERGE_CTRL_00_T                     sr_merge_ctrl_00;	//0xCCC42A00
	PE_O22_SR_MERGE_CTRL_01_T                     sr_merge_ctrl_01;	//0xCCC42A04
	PE_O22_SR_MERGE_CTRL_02_T                     sr_merge_ctrl_02;	//0xCCC42A08
	PE_O22_SR_MERGE_CTRL_03_T                     sr_merge_ctrl_03;	//0xCCC42A0C
	PE_O22_SR_MERGE_SPATIAL_00_T               sr_merge_spatial_00;	//0xCCC42A10
	PE_O22_SR_MERGE_SPATIAL_01_T               sr_merge_spatial_01;	//0xCCC42A14
	UINT32                                                    reserved0;	//0xCCC42A18
	UINT32                                                    reserved1;	//0xCCC42A1C
	PE_O22_SR_MERGE_MMD_00_T                       sr_merge_mmd_00;	//0xCCC42A20
	PE_O22_SR_MERGE_MMD_01_T                       sr_merge_mmd_01;	//0xCCC42A24
	PE_O22_SR_MERGE_MMD_02_T                       sr_merge_mmd_02;	//0xCCC42A28
	PE_O22_SR_MERGE_MMD_03_T                       sr_merge_mmd_03;	//0xCCC42A2C
	PE_O22_SR_MERGE_MMD_04_T                       sr_merge_mmd_04;	//0xCCC42A30
	PE_O22_SR_MERGE_MMD_05_T                       sr_merge_mmd_05;	//0xCCC42A34
	PE_O22_SR_MERGE_MMD_06_T                       sr_merge_mmd_06;	//0xCCC42A38
	UINT32                                                    reserved2;	//0xCCC42A3C
	UINT32                                                    reserved3;	//0xCCC42A40
	UINT32                                                    reserved4;	//0xCCC42A44
	UINT32                                                    reserved5;	//0xCCC42A48
	UINT32                                                    reserved6;	//0xCCC42A4C
	PE_O22_SR_MERGE_SOBEL_00_T                   sr_merge_sobel_00;	//0xCCC42A50
	PE_O22_SR_MERGE_SOBEL_01_T                   sr_merge_sobel_01;	//0xCCC42A54
	PE_O22_SR_MERGE_SOBEL_02_T                   sr_merge_sobel_02;	//0xCCC42A58
	UINT32                                                    reserved7;	//0xCCC42A5C
	UINT32                                                    reserved8;	//0xCCC42A60
	UINT32                                                    reserved9;	//0xCCC42A64
	UINT32                                                   reserved10;	//0xCCC42A68
	UINT32                                                   reserved11;	//0xCCC42A6C
	PE_O22_SR_MERGE_NR_GAIN_00_T               sr_merge_nr_gain_00;	//0xCCC42A70
	PE_O22_SR_MERGE_NR_GAIN_01_T               sr_merge_nr_gain_01;	//0xCCC42A74
	PE_O22_SR_MERGE_NR_GAIN_02_T               sr_merge_nr_gain_02;	//0xCCC42A78
	UINT32                                                   reserved12;	//0xCCC42A7C
	UINT32                                                   reserved13;	//0xCCC42A80
	UINT32                                                   reserved14;	//0xCCC42A84
	UINT32                                                   reserved15;	//0xCCC42A88
	UINT32                                                   reserved16;	//0xCCC42A8C
	PE_O22_SR_MERGE_BLEND_00_T                   sr_merge_blend_00;	//0xCCC42A90
	PE_O22_SR_MERGE_BLEND_01_T                   sr_merge_blend_01;	//0xCCC42A94
	PE_O22_SR_MERGE_BLEND_02_T                   sr_merge_blend_02;	//0xCCC42A98
	PE_O22_SR_MERGE_BLEND_03_T                   sr_merge_blend_03;	//0xCCC42A9C
	PE_O22_SR_MERGE_BLEND_04_T                   sr_merge_blend_04;	//0xCCC42AA0
	UINT32                                                   reserved17;	//0xCCC42AA4
	UINT32                                                   reserved18;	//0xCCC42AA8
	UINT32                                                   reserved19;	//0xCCC42AAC
	UINT32                                                   reserved20;	//0xCCC42AB0
	UINT32                                                   reserved21;	//0xCCC42AB4
	UINT32                                                   reserved22;	//0xCCC42AB8
	UINT32                                                   reserved23;	//0xCCC42ABC
	UINT32                                                   reserved24;	//0xCCC42AC0
	UINT32                                                   reserved25;	//0xCCC42AC4
	UINT32                                                   reserved26;	//0xCCC42AC8
	UINT32                                                   reserved27;	//0xCCC42ACC
	UINT32                                                   reserved28;	//0xCCC42AD0
	UINT32                                                   reserved29;	//0xCCC42AD4
	UINT32                                                   reserved30;	//0xCCC42AD8
	UINT32                                                   reserved31;	//0xCCC42ADC
	UINT32                                                   reserved32;	//0xCCC42AE0
	UINT32                                                   reserved33;	//0xCCC42AE4
	UINT32                                                   reserved34;	//0xCCC42AE8
	UINT32                                                   reserved35;	//0xCCC42AEC
	UINT32                                                   reserved36;	//0xCCC42AF0
	UINT32                                                   reserved37;	//0xCCC42AF4
	UINT32                                                   reserved38;	//0xCCC42AF8
	UINT32                                                   reserved39;	//0xCCC42AFC
	PE_O22_SR_MERGE_CORE_STAT_00_T           sr_merge_core_stat_00;	//0xCCC42B00
	PE_O22_SR_MERGE_CORE_STAT_01_T           sr_merge_core_stat_01;	//0xCCC42B04
	PE_O22_SR_MERGE_CORE_STAT_02_T           sr_merge_core_stat_02;	//0xCCC42B08
	PE_O22_SR_MERGE_CORE_STAT_03_T           sr_merge_core_stat_03;	//0xCCC42B0C
	PE_O22_SR_MERGE_CORE_STAT_04_T           sr_merge_core_stat_04;	//0xCCC42B10
	PE_O22_SR_MERGE_CORE_STAT_05_T           sr_merge_core_stat_05;	//0xCCC42B14
	UINT32                                                   reserved40;	//0xCCC42B18
	UINT32                                                   reserved41;	//0xCCC42B1C
	UINT32                                                   reserved42;	//0xCCC42B20
	UINT32                                                   reserved43;	//0xCCC42B24
	UINT32                                                   reserved44;	//0xCCC42B28
	UINT32                                                   reserved45;	//0xCCC42B2C
	UINT32                                                   reserved46;	//0xCCC42B30
	UINT32                                                   reserved47;	//0xCCC42B34
	UINT32                                                   reserved48;	//0xCCC42B38
	UINT32                                                   reserved49;	//0xCCC42B3C
	UINT32                                                   reserved50;	//0xCCC42B40
	UINT32                                                   reserved51;	//0xCCC42B44
	UINT32                                                   reserved52;	//0xCCC42B48
	UINT32                                                   reserved53;	//0xCCC42B4C
	UINT32                                                   reserved54;	//0xCCC42B50
	UINT32                                                   reserved55;	//0xCCC42B54
	UINT32                                                   reserved56;	//0xCCC42B58
	UINT32                                                   reserved57;	//0xCCC42B5C
	UINT32                                                   reserved58;	//0xCCC42B60
	UINT32                                                   reserved59;	//0xCCC42B64
	UINT32                                                   reserved60;	//0xCCC42B68
	UINT32                                                   reserved61;	//0xCCC42B6C
	UINT32                                                   reserved62;	//0xCCC42B70
	UINT32                                                   reserved63;	//0xCCC42B74
	UINT32                                                   reserved64;	//0xCCC42B78
	UINT32                                                   reserved65;	//0xCCC42B7C
	UINT32                                                   reserved66;	//0xCCC42B80
	UINT32                                                   reserved67;	//0xCCC42B84
	UINT32                                                   reserved68;	//0xCCC42B88
	UINT32                                                   reserved69;	//0xCCC42B8C
	UINT32                                                   reserved70;	//0xCCC42B90
	UINT32                                                   reserved71;	//0xCCC42B94
	UINT32                                                   reserved72;	//0xCCC42B98
	UINT32                                                   reserved73;	//0xCCC42B9C
	UINT32                                                   reserved74;	//0xCCC42BA0
	UINT32                                                   reserved75;	//0xCCC42BA4
	UINT32                                                   reserved76;	//0xCCC42BA8
	UINT32                                                   reserved77;	//0xCCC42BAC
	UINT32                                                   reserved78;	//0xCCC42BB0
	UINT32                                                   reserved79;	//0xCCC42BB4
	UINT32                                                   reserved80;	//0xCCC42BB8
	UINT32                                                   reserved81;	//0xCCC42BBC
	UINT32                                                   reserved82;	//0xCCC42BC0
	UINT32                                                   reserved83;	//0xCCC42BC4
	UINT32                                                   reserved84;	//0xCCC42BC8
	UINT32                                                   reserved85;	//0xCCC42BCC
	UINT32                                                   reserved86;	//0xCCC42BD0
	UINT32                                                   reserved87;	//0xCCC42BD4
	UINT32                                                   reserved88;	//0xCCC42BD8
	UINT32                                                   reserved89;	//0xCCC42BDC
	UINT32                                                   reserved90;	//0xCCC42BE0
	UINT32                                                   reserved91;	//0xCCC42BE4
	UINT32                                                   reserved92;	//0xCCC42BE8
	UINT32                                                   reserved93;	//0xCCC42BEC
	PE_O22_SR_MERGE_FSW_CTRL_00_T             sr_merge_fsw_ctrl_00;	//0xCCC42BF0
	PE_O22_SR_MERGE_FSW_CTRL_01_T             sr_merge_fsw_ctrl_01;	//0xCCC42BF4
	PE_O22_SR_MERGE_FSW_CTRL_02_T             sr_merge_fsw_ctrl_02;	//0xCCC42BF8
	PE_O22_SR_MERGE_FSW_CTRL_03_T             sr_merge_fsw_ctrl_03;	//0xCCC42BFC
}PE_SR_MERG_REG_O22_T;

typedef struct {
	PE_O22_SR_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCCC40200
	PE_O22_SR_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xCCC40204
	PE_O22_SR_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xCCC40208
	PE_O22_SR_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xCCC4020C
}PE_SR_VERI_REG_O22_T;

#endif
