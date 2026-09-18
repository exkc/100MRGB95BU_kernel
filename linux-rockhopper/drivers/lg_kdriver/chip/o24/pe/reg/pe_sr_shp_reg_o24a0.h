#ifndef _PE_SRE_REG_O24A0_H_
#define _PE_SRE_REG_O24A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC620200 RW 0x0000_0000
	UINT32 reg_sys_veri_0                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O24_SR_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620204 RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O24_SR_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620208 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O24_SR_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						////0xCC62020C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O24_SR_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O24_SR_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCC620200
	PE_O24_SR_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xCC620204
	PE_O24_SR_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xCC620208
	PE_O24_SR_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xCC62020C
}PE_SR_VERI_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C00 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O24_2K_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C04 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C08 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_2K_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C0C RW 0x00A9_0000
	UINT32 reg_top_prefetch_cnt             :12;	//(11:0,NA,0) //Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,169) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C40 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O24_2K_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C60 RW 0x1000_0A05
	UINT32 reg_gain_map_mmd_div             :4;	//(3:0,NA,5) //3x3 mmd division
	UINT32 reg_gain_map_mmd_mul             :4;	//(7:4,NA,0) //3x3 mmd multiplication
	UINT32 reg_gain_map_mmd_offset          :8;	//(15:8,NA,10) //3x3 mmd offset
	UINT32 resvd0                           :12;
	UINT32 reg_gain_map_mmd_3x3_en          :1;	//(28:28,NA,1) //3x3 mmd multiplication
	UINT32 resvd1                           :3;
	};
}PE_O24_2K_SHP_GAIN_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620CF0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: Luma Adabtive	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O24_2K_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D00 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D08 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O24_2K_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D0C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D10 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D14 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D18 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D1C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D20 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O24_2K_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D24 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D28 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O24_2K_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D2C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D30 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O24_2K_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D34 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O24_2K_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D38 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D3C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O24_2K_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D40 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O24_2K_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D44 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O24_2K_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D48 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O24_2K_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D4C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O24_2K_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D50 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O24_2K_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D54 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_O24_2K_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D58 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O24_2K_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D60 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O24_2K_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D64 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O24_2K_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D68 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O24_2K_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D6C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O24_2K_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D70 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O24_2K_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D74 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D78 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O24_2K_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D7C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O24_2K_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D80 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O24_2K_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D84 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_O24_2K_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D88 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O24_2K_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D8C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D90 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620D94 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_O24_2K_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DA0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 resvd                            :7;
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //local gain
	};
}PE_O24_2K_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DA4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //gain balancing, x1
	};
}PE_O24_2K_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DA8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //gain balancing, x3
	};
}PE_O24_2K_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DAC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DB0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DC0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O24_2K_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DC4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_O24_2K_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DC8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O24_2K_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DCC RW 0x0006_5008
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
}PE_O24_2K_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DD0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_O24_2K_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DD4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_O24_2K_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DD8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O24_2K_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DDC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O24_2K_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DE0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O24_2K_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DE4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DE8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O24_2K_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DEC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O24_2K_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DF0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O24_2K_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DF4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DF8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O24_2K_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620DFC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O24_2K_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E00 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O24_2K_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E04 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_O24_2K_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E08 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O24_2K_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E0C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E10 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E20 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O24_2K_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E24 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O24_2K_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E28 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E2C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E30 RW 0x1010_2014
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
}PE_O24_2K_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E40 RW 0x8000_0011
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
}PE_O24_2K_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E44 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //
	UINT32 resvd3                           :5;
	};
}PE_O24_2K_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E48 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//(21:16,NA,63) //
	UINT32 resvd1                           :10;
	};
}PE_O24_2K_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E4C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //
	};
}PE_O24_2K_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E54 RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio                :3;	//(2:0,NA,4) //
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//(13:8,NA,31) //
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //
	UINT32 resvd3                           :6;
	};
}PE_O24_2K_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E58 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //
	UINT32 resvd2                           :3;
	};
}PE_O24_2K_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E5C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O24_2K_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E60 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O24_2K_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E64 RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain           :5;	//(4:0,NA,31) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//(12:8,NA,31) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //
	UINT32 resvd2                           :2;
	};
}PE_O24_2K_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E68 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7                   :4;	//(3:0,NA,15) //
	UINT32 reg_tgen_gain6                   :4;	//(7:4,NA,15) //
	UINT32 reg_tgen_gain5                   :4;	//(11:8,NA,13) //
	UINT32 reg_tgen_gain4                   :4;	//(15:12,NA,12) //
	UINT32 reg_tgen_gain3                   :4;	//(19:16,NA,11) //
	UINT32 reg_tgen_gain2                   :4;	//(23:20,NA,10) //
	UINT32 reg_tgen_gain1                   :4;	//(27:24,NA,8) //
	UINT32 reg_tgen_gain0                   :4;	//(31:28,NA,4) //
	};
}PE_O24_2K_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E6C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E70 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E74 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O24_2K_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E80 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O24_2K_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E84 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E88 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E8C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E90 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E94 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E98 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620E9C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EA0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EA4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EA8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EAC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EB0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EB4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EB8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EBC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EC0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EC4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EC8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620ECC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620ED0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620ED4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620ED8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EDC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EE0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EE4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O24_2K_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EE8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_O24_2K_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EEC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O24_2K_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EF0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O24_2K_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EF4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O24_2K_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EF8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620EFC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F00 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F04 RW 0x0000_2B38
	UINT32 reg_nntg_lsfr_init_1st           :32;	//(31:0,NA,11064) //4K nano-noise LSFR init (1st)
	};
}PE_O24_2K_SHP_NNTG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F08 RW 0xBDE6_E338
	UINT32 reg_nntg_lsfr_init_2nd           :32;	//(31:0,NA,3186025272) //4K nano-noise LSFR init (2nd)
	};
}PE_O24_2K_SHP_NNTG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F0C RW 0xD9F2_01CB
	UINT32 reg_nntg_lsfr_init_3rd           :32;	//(31:0,NA,3656516043) //4K nano-noise LSFR init (3rd)
	};
}PE_O24_2K_SHP_NNTG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F10 RW 0x1598_773A
	UINT32 reg_nntg_lsfr_init_4th           :32;	//(31:0,NA,362313530) //4K nano-noise LSFR init (4th)
	};
}PE_O24_2K_SHP_NNTG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F14 RW 0x82D2_8A5C
	UINT32 reg_nntg_lsfr_init_5th           :32;	//(31:0,NA,2194836060) //4K nano-noise LSFR init (5th)
	};
}PE_O24_2K_SHP_NNTG_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F2C RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio              :8;	//(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_O24_2K_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F30 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00           :4;	//(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F34 RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20           :4;	//(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F38 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10           :4;	//(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F3C RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0             :8;	//(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O24_2K_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F40 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2             :8;	//(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O24_2K_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F44 RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0             :8;	//(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O24_2K_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F48 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2             :8;	//(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O24_2K_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F4C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O24_2K_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F50 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_2K_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F54 RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_2K_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F60 RW 0x0000_0080
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O24_2K_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F64 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_O24_2K_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620F68 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_O24_2K_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FA0 RW 0x0000_0000
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
}PE_O24_2K_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FA4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FA8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FAC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FB0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FC0 RW 0x0432_0c40
	UINT32 reg_region_text_en               :1;	//(0:0,NA,0) //region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//(6:4,NA,4) //
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//(15:8,NA,12) //
	UINT32 reg_region_text_add_max          :8;	//(23:16,NA,50) //
	UINT32 reg_region_text_cuthif           :3;	//(26:24,NA,4) //
	UINT32 resvd2                           :5;
	};
}PE_O24_2K_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FC4 RW 0x0f50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //region texture LUT , x1
	};
}PE_O24_2K_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FC8 RW 0x46c8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //region texture LUT , x3
	};
}PE_O24_2K_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FCC RW 0x0000_ff00
	UINT32 reg_tmap_temp_iir_en             :1;	//(0:0,NA,0) //TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//(4:4,NA,0) //TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//(15:8,NA,255) //TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//(24:24,NA,0) //TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FD0 RW 0x2840_0a00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //tmap temporal previous blend LUT , x1
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FD4 RW 0x5080_3c60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //tmap temporal previous blend LUT , x3
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FD8 RW 0x08d0_00c0
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir positive LUT , x1
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FDC RW 0x30f0_10e0
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //tmap temporal iir positive LUT , x3
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FE0 RW 0x80c0_60d0
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //tmap temporal iir positive LUT , x5
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FE4 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir negative LUT , x1
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FE8 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //tmap temporal iir negative LUT , x3
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FEC RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //tmap temporal iir negative LUT , x5
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FF0 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x       :12;	//(11:0,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FF4 RW 0x086f_077f
	UINT32 reg_tmap_stat_win0_end_x         :12;	//(11:0,NA,1919) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//(27:16,NA,2159) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FF8 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x       :12;	//(11:0,NA,1920) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620FFC RW 0x0438_0eff
	UINT32 reg_tmap_stat_win1_end_x         :12;	//(11:0,NA,3839) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//(27:16,NA,1080) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621000 RW 0x8010_0179
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
}PE_O24_2K_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621004 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O24_2K_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621008 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O24_2K_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62100C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O24_2K_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621010 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O24_2K_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621014 RW 0x0000_0000
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
}PE_O24_2K_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621018 RW 0x0000_0040
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
}PE_O24_2K_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62101C RW 0x0015_5550
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
}PE_O24_2K_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621020 RW 0x0000_0040
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
}PE_O24_2K_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621024 RW 0x002A_A040
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
}PE_O24_2K_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621028 RW 0x002A_A040
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
}PE_O24_2K_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62102C RW 0x000A_A040
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
}PE_O24_2K_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621030 RW 0x0000_00E4
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
}PE_O24_2K_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621034 RW 0x0000_5540
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
}PE_O24_2K_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621038 RW 0x0020_5542
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
}PE_O24_2K_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62103C RW 0x0008_1508
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
}PE_O24_2K_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621040 RW 0x0002_0420
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
}PE_O24_2K_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621044 RW 0x0000_8080
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
}PE_O24_2K_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621048 RW 0x0000_2A00
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
}PE_O24_2K_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62104C RW 0x0000_2A00
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
}PE_O24_2K_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621050 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O24_2K_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621054 RW 0x0000_2800
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
}PE_O24_2K_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621058 RW 0x0005_0A00
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
}PE_O24_2K_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62105C RW 0x0005_4280
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
}PE_O24_2K_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621060 RW 0x0005_50A0
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
}PE_O24_2K_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621064 RW 0x0005_4280
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
}PE_O24_2K_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621068 RW 0x0005_0A00
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
}PE_O24_2K_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62106C RW 0x0000_2800
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
}PE_O24_2K_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621070 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O24_2K_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621074 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621078 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62107C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621080 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O24_2K_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621090 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621094 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210A0 RW 0x0000_0000
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
}PE_O24_2K_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210A8 RW 0x0437_077F
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210B0 RW 0x0437_077F
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210C0 RW 0x10BC_4DB3
	UINT32 reg_dj_text_gain_mmd_mul         :8;	//(7:0,NA,179) //DJ control register
	UINT32 reg_dj_text_gain_avg_mul         :8;	//(15:8,NA,77) //DJ control register
	UINT32 reg_dj_text_gain_threshold       :10;	//(25:16,NA,188) //DJ control register
	UINT32 reg_dj_text_gain_all_text_flag   :1;	//(26:26,NA,0) //DJ control register
	UINT32 resvd0                           :1;
	UINT32 reg_dj_text_gain_en              :1;	//(28:28,NA,1) //DJ control register
	UINT32 resvd1                           :3;
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210C4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir0_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir0_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210C8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir0_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir0_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir0_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir0_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210CC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir1_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir1_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210D0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir1_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir1_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir1_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir1_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210D4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir3_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir3_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210D8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir3_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir3_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir3_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir3_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210DC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir5_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir5_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210E0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir5_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir5_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir5_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir5_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210E4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir6_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir6_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210E8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir6_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir6_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir6_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir6_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210EC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir7_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir7_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210F0 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir7_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir7_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir7_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir7_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210F4 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir9_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir9_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210F8 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir9_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir9_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir9_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir9_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6210FC RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir11_y0        :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x0        :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir11_y1        :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x1        :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621100 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir11_y2        :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir11_x2        :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir11_y3        :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir11_x3        :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621200 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621204 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621208 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter(0~3839)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter(0~3839)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62120C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter 4K Last = 2160
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter 4K Last = 2160
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621210 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O24_2K_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621214 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O24_2K_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621218 RW 0x0000_0000
	UINT32 reg_mask_in_ready_en             :1;	//(0:0,NA,0) //1 : input ready force 1
	UINT32 resvd0                           :3;
	UINT32 reg_mask_out_valid_en            :1;	//(4:4,NA,0) //1 : output valid force 1
	UINT32 resvd1                           :3;
	UINT32 reg_mask_out_ready_en            :1;	//(8:8,NA,0) //1 : output ready force 1
	UINT32 resvd2                           :3;
	UINT32 reg_mask_in_valid_en             :1;	//(12:12,NA,0) //1 : input valid force 1
	UINT32 resvd3                           :19;
	};
}PE_O24_2K_SHP_CORE_RDY_VLD_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621260 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621264 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621268 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62126C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621300 RO 0x0000_0000
	UINT32 ro_tmap_status_window0           :32;	//(31:0,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621304 RO 0x0000_0000
	UINT32 ro_tmap_status_window1           :32;	//(31:0,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621308 RO 0x0000_0000
	UINT32 ro_tmap_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62130C RO 0x0000_0000
	UINT32 ro_tmap_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621310 RO 0x0000_0000
	UINT32 ro_tmap_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621314 RO 0x0000_0000
	UINT32 ro_tmap_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621318 RO 0x0000_0000
	UINT32 ro_tmap_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62131C RO 0x0000_0000
	UINT32 ro_tmap_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_11                :16;	//(31:16,NA,0) //
	};
}PE_O24_2K_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621320 RW 0x0000_0000
	UINT32 reg_ellipse_ctrl_en              :1;	//(0:0,NA,0x0) //Not use
	UINT32 resvd0                           :3;
	UINT32 reg_sel_output                   :1;	//(4:4,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_ellipse_offset               :8;	//(15:8,NA,0x0) //
	UINT32 resvd2                           :12;
	UINT32 reg_ellipse_debug_en             :1;	//(28:28,NA,0x0) //
	UINT32 resvd3                           :3;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621324 RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f0_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621328 RW 0x0000_0000
	UINT32 reg_f0_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62132C RW 0x0000_0000
	UINT32 reg_f0_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f0_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f0_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621330 RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f1_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f1_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621334 RW 0x0000_0000
	UINT32 reg_f1_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621338 RW 0x0000_0000
	UINT32 reg_f1_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f1_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f1_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62133C RW 0x0000_0000
	UINT32 reg_f2_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f2_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621340 RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f2_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621344 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f2_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f2_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621348 RW 0x0000_0000
	UINT32 reg_f3_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f3_enable                    :1;	//(24:24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62134C RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621350 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f3_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f3_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_2K_SHP_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621354 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //
	};
}PE_O24_2K_SHP_ELLIPSE_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621358 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //
	};
}PE_O24_2K_SHP_ELLIPSE_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621360 RW 0x0000_0000
	UINT32 reg_ellips_gain_en               :1;	//(0:0,NA,0) //0: not use ellipse gain, 1 : use ellipse gain
	UINT32 resvd0                           :3;
	UINT32 reg_luma_dp_blend_en             :1;	//(4:4,NA,0) //luma_dp_blend_en
	UINT32 resvd1                           :3;
	UINT32 reg_luma_dp_blend_debug_sel_en   :1;	//(8:8,NA,0) //0 : gain, 1: bypass Y
	UINT32 resvd2                           :23;
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621364 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621368 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62136C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y4                  :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x4                  :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y5                  :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x5                  :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621370 RW 0x8020_8020
	UINT32 reg_gain_lut_y6                  :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x6                  :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y7                  :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x7                  :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621374 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y8                  :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x8                  :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y9                  :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x9                  :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621378 RW 0x8020_8020
	UINT32 reg_gain_lut_y10                 :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x10                 :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y11                 :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x11                 :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62137C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y12                 :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x12                 :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y13                 :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x13                 :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621380 RW 0x8020_8020
	UINT32 reg_gain_lut_y14                 :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x14                 :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y15                 :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x15                 :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_2K_SHP_LUMA_BLEND_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621384 RW 0x0000_0000
	UINT32 reg_sm_blender_en                :1;	//(0:0,NA,0) //0 : OFF, 1 : ON
	UINT32 reg_sm_blender_dly_debug_en      :1;	//(1:1,NA,0) //output motion map debug
	UINT32 reg_sm_blender_inter_debug_en    :1;	//(2:2,NA,0) //interpolation motion map debug
	UINT32 resvd0                           :5;
	UINT32 reg_sm_blender_inter_alpha_value :8;	//(15:08,NA,0) //0~255 alpha value
	UINT32 reg_sm_blender_inter_alpha_debug_en :1;	//(16:16,NA,0) //interpolation motion map alpha blending debug
	UINT32 resvd1                           :3;
	UINT32 reg_sm_blender_dly_alpha_value   :8;	//(27:20,NA,0) //0~255 alpha value
	UINT32 reg_sm_blender_dly_alpha_debug_en :1;	//(28:28,NA,0) //output motion map alpha blending debug
	UINT32 resvd2                           :3;
	};
}PE_O24_2K_SHP_SM_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621388 RW 0x8020_8020
	UINT32 reg_sm_pre_lut_y0                :8;	//(7:0,NA,192) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x0                :8;	//(15:8,NA,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_y1                :8;	//(23:16,NA,192) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x1                :8;	//(31:24,NA,0) //SM Blend LUT
	};
}PE_O24_2K_SHP_SM_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62138C RW 0x8020_8020
	UINT32 reg_sm_pre_lut_y2                :8;	//(7:0,NA,32) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x2                :8;	//(15:8,NA,128) //SM Blend LUT
	UINT32 reg_sm_pre_lut_y3                :8;	//(23:16,NA,32) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x3                :8;	//(31:24,NA,128) //SM Blend LUT
	};
}PE_O24_2K_SHP_SM_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6213F0 RW 0x0000_0000
	UINT32 cvd_pattern_detect				:1;
	UINT32 color_bar						:1;
	UINT32 vfy_glb_en						:1;
	UINT32 resvd							:29;
	};
}PE_O24_2K_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6213F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6213F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6213FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O24_2K_SHP_CORE_CTRL_00_T                      shp_core_ctrl_00;	//0xCC620C00
	PE_O24_2K_SHP_CORE_CTRL_01_T                      shp_core_ctrl_01;	//0xCC620C04
	PE_O24_2K_SHP_CORE_CTRL_02_T                      shp_core_ctrl_02;	//0xCC620C08
	PE_O24_2K_SHP_CORE_CTRL_03_T                      shp_core_ctrl_03;	//0xCC620C0C
	UINT32                                                    reserved0;	//0xCC620C10
	UINT32                                                    reserved1;	//0xCC620C14
	UINT32                                                    reserved2;	//0xCC620C18
	UINT32                                                    reserved3;	//0xCC620C1C
	UINT32                                                    reserved4;	//0xCC620C20
	UINT32                                                    reserved5;	//0xCC620C24
	UINT32                                                    reserved6;	//0xCC620C28
	UINT32                                                    reserved7;	//0xCC620C2C
	UINT32                                                    reserved8;	//0xCC620C30
	UINT32                                                    reserved9;	//0xCC620C34
	UINT32                                                   reserved10;	//0xCC620C38
	UINT32                                                   reserved11;	//0xCC620C3C
	PE_O24_2K_SHP_PAT_GEN_CTRL_00_T                shp_pat_gen_ctrl_00;	//0xCC620C40
	UINT32                                                   reserved12;	//0xCC620C44
	UINT32                                                   reserved13;	//0xCC620C48
	UINT32                                                   reserved14;	//0xCC620C4C
	UINT32                                                   reserved15;	//0xCC620C50
	UINT32                                                   reserved16;	//0xCC620C54
	UINT32                                                   reserved17;	//0xCC620C58
	UINT32                                                   reserved18;	//0xCC620C5C
	PE_O24_2K_SHP_GAIN_MAP_CTRL_00_T              shp_gain_map_ctrl_00;	//0xCC620C60
	UINT32                                                   reserved19;	//0xCC620C64
	UINT32                                                   reserved20;	//0xCC620C68
	UINT32                                                   reserved21;	//0xCC620C6C
	UINT32                                                   reserved22;	//0xCC620C70
	UINT32                                                   reserved23;	//0xCC620C74
	UINT32                                                   reserved24;	//0xCC620C78
	UINT32                                                   reserved25;	//0xCC620C7C
	UINT32                                                   reserved26;	//0xCC620C80
	UINT32                                                   reserved27;	//0xCC620C84
	UINT32                                                   reserved28;	//0xCC620C88
	UINT32                                                   reserved29;	//0xCC620C8C
	UINT32                                                   reserved30;	//0xCC620C90
	UINT32                                                   reserved31;	//0xCC620C94
	UINT32                                                   reserved32;	//0xCC620C98
	UINT32                                                   reserved33;	//0xCC620C9C
	UINT32                                                   reserved34;	//0xCC620CA0
	UINT32                                                   reserved35;	//0xCC620CA4
	UINT32                                                   reserved36;	//0xCC620CA8
	UINT32                                                   reserved37;	//0xCC620CAC
	UINT32                                                   reserved38;	//0xCC620CB0
	UINT32                                                   reserved39;	//0xCC620CB4
	UINT32                                                   reserved40;	//0xCC620CB8
	UINT32                                                   reserved41;	//0xCC620CBC
	UINT32                                                   reserved42;	//0xCC620CC0
	UINT32                                                   reserved43;	//0xCC620CC4
	UINT32                                                   reserved44;	//0xCC620CC8
	UINT32                                                   reserved45;	//0xCC620CCC
	UINT32                                                   reserved46;	//0xCC620CD0
	UINT32                                                   reserved47;	//0xCC620CD4
	UINT32                                                   reserved48;	//0xCC620CD8
	UINT32                                                   reserved49;	//0xCC620CDC
	UINT32                                                   reserved50;	//0xCC620CE0
	UINT32                                                   reserved51;	//0xCC620CE4
	UINT32                                                   reserved52;	//0xCC620CE8
	UINT32                                                   reserved53;	//0xCC620CEC
	PE_O24_2K_SHP_DP_CTRL_00_T                          shp_dp_ctrl_00;	//0xCC620CF0
	UINT32                                                   reserved54;	//0xCC620CF4
	UINT32                                                   reserved55;	//0xCC620CF8
	UINT32                                                   reserved56;	//0xCC620CFC
	PE_O24_2K_SHP_FD_CTRL_00_T                          shp_fd_ctrl_00;	//0xCC620D00
	PE_O24_2K_SHP_FD_CTRL_01_T                          shp_fd_ctrl_01;	//0xCC620D04
	PE_O24_2K_SHP_FD_CTRL_02_T                          shp_fd_ctrl_02;	//0xCC620D08
	PE_O24_2K_SHP_FD_CTRL_03_T                          shp_fd_ctrl_03;	//0xCC620D0C
	PE_O24_2K_SHP_FD_CTRL_04_T                          shp_fd_ctrl_04;	//0xCC620D10
	PE_O24_2K_SHP_FD_CTRL_05_T                          shp_fd_ctrl_05;	//0xCC620D14
	PE_O24_2K_SHP_FD_CTRL_06_T                          shp_fd_ctrl_06;	//0xCC620D18
	PE_O24_2K_SHP_FD_CTRL_07_T                          shp_fd_ctrl_07;	//0xCC620D1C
	PE_O24_2K_SHP_FD_CTRL_08_T                          shp_fd_ctrl_08;	//0xCC620D20
	PE_O24_2K_SHP_FD_CTRL_09_T                          shp_fd_ctrl_09;	//0xCC620D24
	PE_O24_2K_SHP_FD_CTRL_0A_T                          shp_fd_ctrl_0a;	//0xCC620D28
	PE_O24_2K_SHP_FD_CTRL_0B_T                          shp_fd_ctrl_0b;	//0xCC620D2C
	PE_O24_2K_SHP_FD_CTRL_0C_T                          shp_fd_ctrl_0c;	//0xCC620D30
	PE_O24_2K_SHP_FD_CTRL_0D_T                          shp_fd_ctrl_0d;	//0xCC620D34
	PE_O24_2K_SHP_FD_CTRL_0E_T                          shp_fd_ctrl_0e;	//0xCC620D38
	PE_O24_2K_SHP_FD_CTRL_0F_T                          shp_fd_ctrl_0f;	//0xCC620D3C
	PE_O24_2K_SHP_FD_CTRL_10_T                          shp_fd_ctrl_10;	//0xCC620D40
	PE_O24_2K_SHP_FD_CTRL_11_T                          shp_fd_ctrl_11;	//0xCC620D44
	PE_O24_2K_SHP_FD_CTRL_12_T                          shp_fd_ctrl_12;	//0xCC620D48
	PE_O24_2K_SHP_FD_CTRL_13_T                          shp_fd_ctrl_13;	//0xCC620D4C
	PE_O24_2K_SHP_FD_CTRL_14_T                          shp_fd_ctrl_14;	//0xCC620D50
	PE_O24_2K_SHP_FD_CTRL_15_T                          shp_fd_ctrl_15;	//0xCC620D54
	PE_O24_2K_SHP_FD_CTRL_16_T                          shp_fd_ctrl_16;	//0xCC620D58
	UINT32                                                   reserved57;	//0xCC620D5C
	PE_O24_2K_SHP_MP_CTRL_00_T                          shp_mp_ctrl_00;	//0xCC620D60
	PE_O24_2K_SHP_MP_CTRL_01_T                          shp_mp_ctrl_01;	//0xCC620D64
	PE_O24_2K_SHP_MP_CTRL_02_T                          shp_mp_ctrl_02;	//0xCC620D68
	PE_O24_2K_SHP_MP_CTRL_03_T                          shp_mp_ctrl_03;	//0xCC620D6C
	PE_O24_2K_SHP_MP_CTRL_04_T                          shp_mp_ctrl_04;	//0xCC620D70
	PE_O24_2K_SHP_MP_CTRL_05_T                          shp_mp_ctrl_05;	//0xCC620D74
	PE_O24_2K_SHP_MP_CTRL_06_T                          shp_mp_ctrl_06;	//0xCC620D78
	PE_O24_2K_SHP_MP_CTRL_07_T                          shp_mp_ctrl_07;	//0xCC620D7C
	PE_O24_2K_SHP_MP_CTRL_08_T                          shp_mp_ctrl_08;	//0xCC620D80
	PE_O24_2K_SHP_MP_CTRL_09_T                          shp_mp_ctrl_09;	//0xCC620D84
	PE_O24_2K_SHP_MP_CTRL_0A_T                          shp_mp_ctrl_0a;	//0xCC620D88
	PE_O24_2K_SHP_MP_CTRL_0B_T                          shp_mp_ctrl_0b;	//0xCC620D8C
	PE_O24_2K_SHP_MP_CTRL_0C_T                          shp_mp_ctrl_0c;	//0xCC620D90
	PE_O24_2K_SHP_APL_CTRL_00_T                        shp_apl_ctrl_00;	//0xCC620D94
	UINT32                                                   reserved58;	//0xCC620D98
	UINT32                                                   reserved59;	//0xCC620D9C
	PE_O24_2K_SHP_LC_CTRL_00_T                          shp_lc_ctrl_00;	//0xCC620DA0
	PE_O24_2K_SHP_LC_CTRL_01_T                          shp_lc_ctrl_01;	//0xCC620DA4
	PE_O24_2K_SHP_LC_CTRL_02_T                          shp_lc_ctrl_02;	//0xCC620DA8
	PE_O24_2K_SHP_LC_CTRL_03_T                          shp_lc_ctrl_03;	//0xCC620DAC
	PE_O24_2K_SHP_LC_CTRL_04_T                          shp_lc_ctrl_04;	//0xCC620DB0
	UINT32                                                   reserved60;	//0xCC620DB4
	UINT32                                                   reserved61;	//0xCC620DB8
	UINT32                                                   reserved62;	//0xCC620DBC
	PE_O24_2K_SHP_DER_CTRL_00_T                        shp_der_ctrl_00;	//0xCC620DC0
	PE_O24_2K_SHP_DER_CTRL_01_T                        shp_der_ctrl_01;	//0xCC620DC4
	PE_O24_2K_SHP_DER_CTRL_02_T                        shp_der_ctrl_02;	//0xCC620DC8
	PE_O24_2K_SHP_DER_CTRL_03_T                        shp_der_ctrl_03;	//0xCC620DCC
	PE_O24_2K_SHP_DER_CTRL_04_T                        shp_der_ctrl_04;	//0xCC620DD0
	PE_O24_2K_SHP_DER_CTRL_05_T                        shp_der_ctrl_05;	//0xCC620DD4
	PE_O24_2K_SHP_DER_CTRL_06_T                        shp_der_ctrl_06;	//0xCC620DD8
	PE_O24_2K_SHP_DER_CTRL_07_T                        shp_der_ctrl_07;	//0xCC620DDC
	PE_O24_2K_SHP_SP_CTRL_00_T                          shp_sp_ctrl_00;	//0xCC620DE0
	PE_O24_2K_SHP_SP_CTRL_01_T                          shp_sp_ctrl_01;	//0xCC620DE4
	PE_O24_2K_SHP_SP_CTRL_02_T                          shp_sp_ctrl_02;	//0xCC620DE8
	PE_O24_2K_SHP_SP_CTRL_03_T                          shp_sp_ctrl_03;	//0xCC620DEC
	PE_O24_2K_SHP_SP_CTRL_04_T                          shp_sp_ctrl_04;	//0xCC620DF0
	PE_O24_2K_SHP_SP_CTRL_05_T                          shp_sp_ctrl_05;	//0xCC620DF4
	PE_O24_2K_SHP_SP_CTRL_06_T                          shp_sp_ctrl_06;	//0xCC620DF8
	PE_O24_2K_SHP_SP_CTRL_07_T                          shp_sp_ctrl_07;	//0xCC620DFC
	PE_O24_2K_SHP_SP_CTRL_08_T                          shp_sp_ctrl_08;	//0xCC620E00
	PE_O24_2K_SHP_SP_CTRL_09_T                          shp_sp_ctrl_09;	//0xCC620E04
	PE_O24_2K_SHP_SP_CTRL_0A_T                          shp_sp_ctrl_0a;	//0xCC620E08
	PE_O24_2K_SHP_SP_CTRL_0B_T                          shp_sp_ctrl_0b;	//0xCC620E0C
	PE_O24_2K_SHP_SP_CTRL_0C_T                          shp_sp_ctrl_0c;	//0xCC620E10
	UINT32                                                   reserved63;	//0xCC620E14
	UINT32                                                   reserved64;	//0xCC620E18
	UINT32                                                   reserved65;	//0xCC620E1C
	PE_O24_2K_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0xCC620E20
	PE_O24_2K_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0xCC620E24
	PE_O24_2K_SHP_PTI_CTRL_02_T                        shp_pti_ctrl_02;	//0xCC620E28
	PE_O24_2K_SHP_PTI_CTRL_03_T                        shp_pti_ctrl_03;	//0xCC620E2C
	PE_O24_2K_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0xCC620E30
	UINT32                                                   reserved66;	//0xCC620E34
	UINT32                                                   reserved67;	//0xCC620E38
	UINT32                                                   reserved68;	//0xCC620E3C
	PE_O24_2K_SHP_TGEN_CTRL_00_T                      shp_tgen_ctrl_00;	//0xCC620E40
	PE_O24_2K_SHP_TGEN_CTRL_01_T                      shp_tgen_ctrl_01;	//0xCC620E44
	PE_O24_2K_SHP_TGEN_CTRL_02_T                      shp_tgen_ctrl_02;	//0xCC620E48
	PE_O24_2K_SHP_TGEN_CTRL_03_T                      shp_tgen_ctrl_03;	//0xCC620E4C
	UINT32                                                   reserved69;	//0xCC620E50
	PE_O24_2K_SHP_TGEN_CTRL_04_T                      shp_tgen_ctrl_04;	//0xCC620E54
	PE_O24_2K_SHP_TGEN_CTRL_05_T                      shp_tgen_ctrl_05;	//0xCC620E58
	PE_O24_2K_SHP_TGEN_CTRL_06_T                      shp_tgen_ctrl_06;	//0xCC620E5C
	PE_O24_2K_SHP_TGEN_CTRL_07_T                      shp_tgen_ctrl_07;	//0xCC620E60
	PE_O24_2K_SHP_TGEN_CTRL_08_T                      shp_tgen_ctrl_08;	//0xCC620E64
	PE_O24_2K_SHP_TGEN_CTRL_09_T                      shp_tgen_ctrl_09;	//0xCC620E68
	PE_O24_2K_SHP_TGEN_CTRL_0A_T                      shp_tgen_ctrl_0a;	//0xCC620E6C
	PE_O24_2K_SHP_TGEN_CTRL_0B_T                      shp_tgen_ctrl_0b;	//0xCC620E70
	PE_O24_2K_SHP_SNR_CTRL_00_T                        shp_snr_ctrl_00;	//0xCC620E74
	UINT32                                                   reserved70;	//0xCC620E78
	UINT32                                                   reserved71;	//0xCC620E7C
	PE_O24_2K_SHP_DCTP_CTRL_00_T                      shp_dctp_ctrl_00;	//0xCC620E80
	PE_O24_2K_SHP_DCTP_CTRL_01_T                      shp_dctp_ctrl_01;	//0xCC620E84
	PE_O24_2K_SHP_DCTP_CTRL_02_T                      shp_dctp_ctrl_02;	//0xCC620E88
	PE_O24_2K_SHP_DCTP_CTRL_03_T                      shp_dctp_ctrl_03;	//0xCC620E8C
	PE_O24_2K_SHP_DCTP_CTRL_04_T                      shp_dctp_ctrl_04;	//0xCC620E90
	PE_O24_2K_SHP_DCTP_CTRL_05_T                      shp_dctp_ctrl_05;	//0xCC620E94
	PE_O24_2K_SHP_DCTP_CTRL_06_T                      shp_dctp_ctrl_06;	//0xCC620E98
	PE_O24_2K_SHP_DCTP_CTRL_07_T                      shp_dctp_ctrl_07;	//0xCC620E9C
	PE_O24_2K_SHP_DCTP_CTRL_08_T                      shp_dctp_ctrl_08;	//0xCC620EA0
	PE_O24_2K_SHP_DCTP_CTRL_09_T                      shp_dctp_ctrl_09;	//0xCC620EA4
	PE_O24_2K_SHP_DCTP_CTRL_0A_T                      shp_dctp_ctrl_0a;	//0xCC620EA8
	PE_O24_2K_SHP_DCTP_CTRL_0B_T                      shp_dctp_ctrl_0b;	//0xCC620EAC
	PE_O24_2K_SHP_DCTP_CTRL_0C_T                      shp_dctp_ctrl_0c;	//0xCC620EB0
	PE_O24_2K_SHP_DCTP_CTRL_0D_T                      shp_dctp_ctrl_0d;	//0xCC620EB4
	PE_O24_2K_SHP_DCTP_CTRL_0E_T                      shp_dctp_ctrl_0e;	//0xCC620EB8
	PE_O24_2K_SHP_DCTP_CTRL_0F_T                      shp_dctp_ctrl_0f;	//0xCC620EBC
	PE_O24_2K_SHP_DCTP_CTRL_10_T                      shp_dctp_ctrl_10;	//0xCC620EC0
	PE_O24_2K_SHP_DCTP_CTRL_11_T                      shp_dctp_ctrl_11;	//0xCC620EC4
	PE_O24_2K_SHP_DCTP_CTRL_12_T                      shp_dctp_ctrl_12;	//0xCC620EC8
	PE_O24_2K_SHP_DCTP_CTRL_13_T                      shp_dctp_ctrl_13;	//0xCC620ECC
	PE_O24_2K_SHP_DCTP_CTRL_14_T                      shp_dctp_ctrl_14;	//0xCC620ED0
	PE_O24_2K_SHP_DCTP_CTRL_15_T                      shp_dctp_ctrl_15;	//0xCC620ED4
	PE_O24_2K_SHP_DCTP_CTRL_16_T                      shp_dctp_ctrl_16;	//0xCC620ED8
	PE_O24_2K_SHP_DCTP_CTRL_17_T                      shp_dctp_ctrl_17;	//0xCC620EDC
	PE_O24_2K_SHP_DCTP_CTRL_18_T                      shp_dctp_ctrl_18;	//0xCC620EE0
	PE_O24_2K_SHP_DCTP_CTRL_19_T                      shp_dctp_ctrl_19;	//0xCC620EE4
	PE_O24_2K_SHP_DCTP_CTRL_1A_T                      shp_dctp_ctrl_1a;	//0xCC620EE8
	PE_O24_2K_SHP_DCTP_CTRL_1B_T                      shp_dctp_ctrl_1b;	//0xCC620EEC
	PE_O24_2K_SHP_DCTP_CTRL_1C_T                      shp_dctp_ctrl_1c;	//0xCC620EF0
	PE_O24_2K_SHP_DCTP_CTRL_1D_T                      shp_dctp_ctrl_1d;	//0xCC620EF4
	PE_O24_2K_SHP_DCTP_CTRL_1E_T                      shp_dctp_ctrl_1e;	//0xCC620EF8
	PE_O24_2K_SHP_DCTP_CTRL_1F_T                      shp_dctp_ctrl_1f;	//0xCC620EFC
	PE_O24_2K_SHP_NNTG_CTRL_00_T                      shp_nntg_ctrl_00;	//0xCC620F00
	PE_O24_2K_SHP_NNTG_CTRL_01_T                      shp_nntg_ctrl_01;	//0xCC620F04
	PE_O24_2K_SHP_NNTG_CTRL_02_T                      shp_nntg_ctrl_02;	//0xCC620F08
	PE_O24_2K_SHP_NNTG_CTRL_03_T                      shp_nntg_ctrl_03;	//0xCC620F0C
	PE_O24_2K_SHP_NNTG_CTRL_04_T                      shp_nntg_ctrl_04;	//0xCC620F10
	PE_O24_2K_SHP_NNTG_CTRL_05_T                      shp_nntg_ctrl_05;	//0xCC620F14
	UINT32                                                   reserved72;	//0xCC620F18
	UINT32                                                   reserved73;	//0xCC620F1C
	UINT32                                                   reserved74;	//0xCC620F20
	UINT32                                                   reserved75;	//0xCC620F24
	UINT32                                                   reserved76;	//0xCC620F28
	PE_O24_2K_SHP_NNTG_CTRL_06_T                      shp_nntg_ctrl_06;	//0xCC620F2C
	PE_O24_2K_SHP_NNTG_CTRL_07_T                      shp_nntg_ctrl_07;	//0xCC620F30
	PE_O24_2K_SHP_NNTG_CTRL_08_T                      shp_nntg_ctrl_08;	//0xCC620F34
	PE_O24_2K_SHP_NNTG_CTRL_09_T                      shp_nntg_ctrl_09;	//0xCC620F38
	PE_O24_2K_SHP_NNTG_CTRL_0A_T                      shp_nntg_ctrl_0a;	//0xCC620F3C
	PE_O24_2K_SHP_NNTG_CTRL_0B_T                      shp_nntg_ctrl_0b;	//0xCC620F40
	PE_O24_2K_SHP_NNTG_CTRL_0C_T                      shp_nntg_ctrl_0c;	//0xCC620F44
	PE_O24_2K_SHP_NNTG_CTRL_0D_T                      shp_nntg_ctrl_0d;	//0xCC620F48
	PE_O24_2K_SHP_NNTG_CTRL_0E_T                      shp_nntg_ctrl_0e;	//0xCC620F4C
	PE_O24_2K_SHP_NNTG_CTRL_0F_T                      shp_nntg_ctrl_0f;	//0xCC620F50
	PE_O24_2K_SHP_NNTG_CTRL_10_T                      shp_nntg_ctrl_10;	//0xCC620F54
	UINT32                                                   reserved77;	//0xCC620F58
	UINT32                                                   reserved78;	//0xCC620F5C
	PE_O24_2K_SHP_DP_SUM_CTRL_00_T                  shp_dp_sum_ctrl_00;	//0xCC620F60
	PE_O24_2K_SHP_DP_SUM_CTRL_01_T                  shp_dp_sum_ctrl_01;	//0xCC620F64
	PE_O24_2K_SHP_DP_SUM_CTRL_02_T                  shp_dp_sum_ctrl_02;	//0xCC620F68
	UINT32                                                   reserved79;	//0xCC620F6C
	UINT32                                                   reserved80;	//0xCC620F70
	UINT32                                                   reserved81;	//0xCC620F74
	UINT32                                                   reserved82;	//0xCC620F78
	UINT32                                                   reserved83;	//0xCC620F7C
	UINT32                                                   reserved84;	//0xCC620F80
	UINT32                                                   reserved85;	//0xCC620F84
	UINT32                                                   reserved86;	//0xCC620F88
	UINT32                                                   reserved87;	//0xCC620F8C
	UINT32                                                   reserved88;	//0xCC620F90
	UINT32                                                   reserved89;	//0xCC620F94
	UINT32                                                   reserved90;	//0xCC620F98
	UINT32                                                   reserved91;	//0xCC620F9C
	PE_O24_2K_SHP_DP_WIN_CTRL_00_T                  shp_dp_win_ctrl_00;	//0xCC620FA0
	PE_O24_2K_SHP_DP_WIN_CTRL_01_T                  shp_dp_win_ctrl_01;	//0xCC620FA4
	PE_O24_2K_SHP_DP_WIN_CTRL_02_T                  shp_dp_win_ctrl_02;	//0xCC620FA8
	PE_O24_2K_SHP_DP_WIN_CTRL_03_T                  shp_dp_win_ctrl_03;	//0xCC620FAC
	PE_O24_2K_SHP_DP_WIN_CTRL_04_T                  shp_dp_win_ctrl_04;	//0xCC620FB0
	UINT32                                                   reserved92;	//0xCC620FB4
	UINT32                                                   reserved93;	//0xCC620FB8
	UINT32                                                   reserved94;	//0xCC620FBC
	PE_O24_2K_SHP_FD_REGION_TEXT_00_T            shp_fd_region_text_00;	//0xCC620FC0
	PE_O24_2K_SHP_FD_REGION_TEXT_01_T            shp_fd_region_text_01;	//0xCC620FC4
	PE_O24_2K_SHP_FD_REGION_TEXT_02_T            shp_fd_region_text_02;	//0xCC620FC8
	PE_O24_2K_SHP_FD_TMAP_TEMP_00_T                shp_fd_tmap_temp_00;	//0xCC620FCC
	PE_O24_2K_SHP_FD_TMAP_TEMP_01_T                shp_fd_tmap_temp_01;	//0xCC620FD0
	PE_O24_2K_SHP_FD_TMAP_TEMP_02_T                shp_fd_tmap_temp_02;	//0xCC620FD4
	PE_O24_2K_SHP_FD_TMAP_TEMP_03_T                shp_fd_tmap_temp_03;	//0xCC620FD8
	PE_O24_2K_SHP_FD_TMAP_TEMP_04_T                shp_fd_tmap_temp_04;	//0xCC620FDC
	PE_O24_2K_SHP_FD_TMAP_TEMP_05_T                shp_fd_tmap_temp_05;	//0xCC620FE0
	PE_O24_2K_SHP_FD_TMAP_TEMP_06_T                shp_fd_tmap_temp_06;	//0xCC620FE4
	PE_O24_2K_SHP_FD_TMAP_TEMP_07_T                shp_fd_tmap_temp_07;	//0xCC620FE8
	PE_O24_2K_SHP_FD_TMAP_TEMP_08_T                shp_fd_tmap_temp_08;	//0xCC620FEC
	PE_O24_2K_SHP_FD_TMAP_TEMP_09_T                shp_fd_tmap_temp_09;	//0xCC620FF0
	PE_O24_2K_SHP_FD_TMAP_TEMP_0A_T                shp_fd_tmap_temp_0a;	//0xCC620FF4
	PE_O24_2K_SHP_FD_TMAP_TEMP_0B_T                shp_fd_tmap_temp_0b;	//0xCC620FF8
	PE_O24_2K_SHP_FD_TMAP_TEMP_0C_T                shp_fd_tmap_temp_0c;	//0xCC620FFC
	PE_O24_2K_SHP_DJ_CTRL_00_T                          shp_dj_ctrl_00;	//0xCC621000
	PE_O24_2K_SHP_DJ_CTRL_01_T                          shp_dj_ctrl_01;	//0xCC621004
	PE_O24_2K_SHP_DJ_CTRL_02_T                          shp_dj_ctrl_02;	//0xCC621008
	PE_O24_2K_SHP_DJ_CTRL_03_T                          shp_dj_ctrl_03;	//0xCC62100C
	PE_O24_2K_SHP_DJ_CTRL_04_T                          shp_dj_ctrl_04;	//0xCC621010
	PE_O24_2K_SHP_DJ_CTRL_05_T                          shp_dj_ctrl_05;	//0xCC621014
	PE_O24_2K_SHP_DJ_CTRL_06_T                          shp_dj_ctrl_06;	//0xCC621018
	PE_O24_2K_SHP_DJ_CTRL_07_T                          shp_dj_ctrl_07;	//0xCC62101C
	PE_O24_2K_SHP_DJ_CTRL_08_T                          shp_dj_ctrl_08;	//0xCC621020
	PE_O24_2K_SHP_DJ_CTRL_09_T                          shp_dj_ctrl_09;	//0xCC621024
	PE_O24_2K_SHP_DJ_CTRL_0A_T                          shp_dj_ctrl_0a;	//0xCC621028
	PE_O24_2K_SHP_DJ_CTRL_0B_T                          shp_dj_ctrl_0b;	//0xCC62102C
	PE_O24_2K_SHP_DJ_CTRL_0C_T                          shp_dj_ctrl_0c;	//0xCC621030
	PE_O24_2K_SHP_DJ_CTRL_0D_T                          shp_dj_ctrl_0d;	//0xCC621034
	PE_O24_2K_SHP_DJ_CTRL_0E_T                          shp_dj_ctrl_0e;	//0xCC621038
	PE_O24_2K_SHP_DJ_CTRL_0F_T                          shp_dj_ctrl_0f;	//0xCC62103C
	PE_O24_2K_SHP_DJ_CTRL_10_T                          shp_dj_ctrl_10;	//0xCC621040
	PE_O24_2K_SHP_DJ_CTRL_11_T                          shp_dj_ctrl_11;	//0xCC621044
	PE_O24_2K_SHP_DJ_CTRL_12_T                          shp_dj_ctrl_12;	//0xCC621048
	PE_O24_2K_SHP_DJ_CTRL_13_T                          shp_dj_ctrl_13;	//0xCC62104C
	PE_O24_2K_SHP_DJ_CTRL_14_T                          shp_dj_ctrl_14;	//0xCC621050
	PE_O24_2K_SHP_DJ_CTRL_15_T                          shp_dj_ctrl_15;	//0xCC621054
	PE_O24_2K_SHP_DJ_CTRL_16_T                          shp_dj_ctrl_16;	//0xCC621058
	PE_O24_2K_SHP_DJ_CTRL_17_T                          shp_dj_ctrl_17;	//0xCC62105C
	PE_O24_2K_SHP_DJ_CTRL_18_T                          shp_dj_ctrl_18;	//0xCC621060
	PE_O24_2K_SHP_DJ_CTRL_19_T                          shp_dj_ctrl_19;	//0xCC621064
	PE_O24_2K_SHP_DJ_CTRL_1A_T                          shp_dj_ctrl_1a;	//0xCC621068
	PE_O24_2K_SHP_DJ_CTRL_1B_T                          shp_dj_ctrl_1b;	//0xCC62106C
	PE_O24_2K_SHP_DJ_CTRL_1C_T                          shp_dj_ctrl_1c;	//0xCC621070
	PE_O24_2K_SHP_DJ_CTRL_1D_T                          shp_dj_ctrl_1d;	//0xCC621074
	PE_O24_2K_SHP_DJ_CTRL_1E_T                          shp_dj_ctrl_1e;	//0xCC621078
	PE_O24_2K_SHP_DJ_CTRL_1F_T                          shp_dj_ctrl_1f;	//0xCC62107C
	PE_O24_2K_SHP_DJ_CTRL_20_T                          shp_dj_ctrl_20;	//0xCC621080
	UINT32                                                   reserved95;	//0xCC621084
	UINT32                                                   reserved96;	//0xCC621088
	UINT32                                                   reserved97;	//0xCC62108C
	PE_O24_2K_SHP_DB_CTRL_00_T                          shp_db_ctrl_00;	//0xCC621090
	PE_O24_2K_SHP_DB_CTRL_01_T                          shp_db_ctrl_01;	//0xCC621094
	UINT32                                                   reserved98;	//0xCC621098
	UINT32                                                   reserved99;	//0xCC62109C
	PE_O24_2K_SHP_DJ_WIN_CTRL_00_T                  shp_dj_win_ctrl_00;	//0xCC6210A0
	PE_O24_2K_SHP_DJ_WIN_CTRL_01_T                  shp_dj_win_ctrl_01;	//0xCC6210A4
	PE_O24_2K_SHP_DJ_WIN_CTRL_02_T                  shp_dj_win_ctrl_02;	//0xCC6210A8
	PE_O24_2K_SHP_DJ_WIN_CTRL_03_T                  shp_dj_win_ctrl_03;	//0xCC6210AC
	PE_O24_2K_SHP_DJ_WIN_CTRL_04_T                  shp_dj_win_ctrl_04;	//0xCC6210B0
	UINT32                                                  reserved100;	//0xCC6210B4
	UINT32                                                  reserved101;	//0xCC6210B8
	UINT32                                                  reserved102;	//0xCC6210BC
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_00_T      shp_dj_text_gain_ctrl_00;	//0xCC6210C0
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_01_T      shp_dj_text_gain_ctrl_01;	//0xCC6210C4
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_02_T      shp_dj_text_gain_ctrl_02;	//0xCC6210C8
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_03_T      shp_dj_text_gain_ctrl_03;	//0xCC6210CC
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_04_T      shp_dj_text_gain_ctrl_04;	//0xCC6210D0
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_05_T      shp_dj_text_gain_ctrl_05;	//0xCC6210D4
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_06_T      shp_dj_text_gain_ctrl_06;	//0xCC6210D8
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_07_T      shp_dj_text_gain_ctrl_07;	//0xCC6210DC
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_08_T      shp_dj_text_gain_ctrl_08;	//0xCC6210E0
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_09_T      shp_dj_text_gain_ctrl_09;	//0xCC6210E4
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_10_T      shp_dj_text_gain_ctrl_10;	//0xCC6210E8
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_11_T      shp_dj_text_gain_ctrl_11;	//0xCC6210EC
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_12_T      shp_dj_text_gain_ctrl_12;	//0xCC6210F0
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_13_T      shp_dj_text_gain_ctrl_13;	//0xCC6210F4
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_14_T      shp_dj_text_gain_ctrl_14;	//0xCC6210F8
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_15_T      shp_dj_text_gain_ctrl_15;	//0xCC6210FC
	PE_O24_2K_SHP_DJ_TEXT_GAIN_CTRL_16_T      shp_dj_text_gain_ctrl_16;	//0xCC621100
	UINT32                                                  reserved103;	//0xCC621104
	UINT32                                                  reserved104;	//0xCC621108
	UINT32                                                  reserved105;	//0xCC62110C
	UINT32                                                  reserved106;	//0xCC621110
	UINT32                                                  reserved107;	//0xCC621114
	UINT32                                                  reserved108;	//0xCC621118
	UINT32                                                  reserved109;	//0xCC62111C
	UINT32                                                  reserved110;	//0xCC621120
	UINT32                                                  reserved111;	//0xCC621124
	UINT32                                                  reserved112;	//0xCC621128
	UINT32                                                  reserved113;	//0xCC62112C
	UINT32                                                  reserved114;	//0xCC621130
	UINT32                                                  reserved115;	//0xCC621134
	UINT32                                                  reserved116;	//0xCC621138
	UINT32                                                  reserved117;	//0xCC62113C
	UINT32                                                  reserved118;	//0xCC621140
	UINT32                                                  reserved119;	//0xCC621144
	UINT32                                                  reserved120;	//0xCC621148
	UINT32                                                  reserved121;	//0xCC62114C
	UINT32                                                  reserved122;	//0xCC621150
	UINT32                                                  reserved123;	//0xCC621154
	UINT32                                                  reserved124;	//0xCC621158
	UINT32                                                  reserved125;	//0xCC62115C
	UINT32                                                  reserved126;	//0xCC621160
	UINT32                                                  reserved127;	//0xCC621164
	UINT32                                                  reserved128;	//0xCC621168
	UINT32                                                  reserved129;	//0xCC62116C
	UINT32                                                  reserved130;	//0xCC621170
	UINT32                                                  reserved131;	//0xCC621174
	UINT32                                                  reserved132;	//0xCC621178
	UINT32                                                  reserved133;	//0xCC62117C
	UINT32                                                  reserved134;	//0xCC621180
	UINT32                                                  reserved135;	//0xCC621184
	UINT32                                                  reserved136;	//0xCC621188
	UINT32                                                  reserved137;	//0xCC62118C
	UINT32                                                  reserved138;	//0xCC621190
	UINT32                                                  reserved139;	//0xCC621194
	UINT32                                                  reserved140;	//0xCC621198
	UINT32                                                  reserved141;	//0xCC62119C
	UINT32                                                  reserved142;	//0xCC6211A0
	UINT32                                                  reserved143;	//0xCC6211A4
	UINT32                                                  reserved144;	//0xCC6211A8
	UINT32                                                  reserved145;	//0xCC6211AC
	UINT32                                                  reserved146;	//0xCC6211B0
	UINT32                                                  reserved147;	//0xCC6211B4
	UINT32                                                  reserved148;	//0xCC6211B8
	UINT32                                                  reserved149;	//0xCC6211BC
	UINT32                                                  reserved150;	//0xCC6211C0
	UINT32                                                  reserved151;	//0xCC6211C4
	UINT32                                                  reserved152;	//0xCC6211C8
	UINT32                                                  reserved153;	//0xCC6211CC
	UINT32                                                  reserved154;	//0xCC6211D0
	UINT32                                                  reserved155;	//0xCC6211D4
	UINT32                                                  reserved156;	//0xCC6211D8
	UINT32                                                  reserved157;	//0xCC6211DC
	UINT32                                                  reserved158;	//0xCC6211E0
	UINT32                                                  reserved159;	//0xCC6211E4
	UINT32                                                  reserved160;	//0xCC6211E8
	UINT32                                                  reserved161;	//0xCC6211EC
	UINT32                                                  reserved162;	//0xCC6211F0
	UINT32                                                  reserved163;	//0xCC6211F4
	UINT32                                                  reserved164;	//0xCC6211F8
	UINT32                                                  reserved165;	//0xCC6211FC
	PE_O24_2K_SHP_CORE_STAT_00_T                      shp_core_stat_00;	//0xCC621200
	PE_O24_2K_SHP_CORE_STAT_01_T                      shp_core_stat_01;	//0xCC621204
	PE_O24_2K_SHP_CORE_STAT_02_T                      shp_core_stat_02;	//0xCC621208
	PE_O24_2K_SHP_CORE_STAT_03_T                      shp_core_stat_03;	//0xCC62120C
	PE_O24_2K_SHP_CORE_STAT_04_T                      shp_core_stat_04;	//0xCC621210
	PE_O24_2K_SHP_CORE_STAT_05_T                      shp_core_stat_05;	//0xCC621214
	PE_O24_2K_SHP_CORE_RDY_VLD_MASK_T            shp_core_rdy_vld_mask;	//0xCC621218
	UINT32                                                  reserved166;	//0xCC62121C
	UINT32                                                  reserved167;	//0xCC621220
	UINT32                                                  reserved168;	//0xCC621224
	UINT32                                                  reserved169;	//0xCC621228
	UINT32                                                  reserved170;	//0xCC62122C
	UINT32                                                  reserved171;	//0xCC621230
	UINT32                                                  reserved172;	//0xCC621234
	UINT32                                                  reserved173;	//0xCC621238
	UINT32                                                  reserved174;	//0xCC62123C
	UINT32                                                  reserved175;	//0xCC621240
	UINT32                                                  reserved176;	//0xCC621244
	UINT32                                                  reserved177;	//0xCC621248
	UINT32                                                  reserved178;	//0xCC62124C
	UINT32                                                  reserved179;	//0xCC621250
	UINT32                                                  reserved180;	//0xCC621254
	UINT32                                                  reserved181;	//0xCC621258
	UINT32                                                  reserved182;	//0xCC62125C
	PE_O24_2K_SHP_CORE_FD_STAT_00_T                shp_core_fd_stat_00;	//0xCC621260
	PE_O24_2K_SHP_CORE_FD_STAT_01_T                shp_core_fd_stat_01;	//0xCC621264
	PE_O24_2K_SHP_CORE_FD_STAT_02_T                shp_core_fd_stat_02;	//0xCC621268
	PE_O24_2K_SHP_CORE_FD_STAT_03_T                shp_core_fd_stat_03;	//0xCC62126C
	UINT32                                                  reserved183;	//0xCC621270
	UINT32                                                  reserved184;	//0xCC621274
	UINT32                                                  reserved185;	//0xCC621278
	UINT32                                                  reserved186;	//0xCC62127C
	UINT32                                                  reserved187;	//0xCC621280
	UINT32                                                  reserved188;	//0xCC621284
	UINT32                                                  reserved189;	//0xCC621288
	UINT32                                                  reserved190;	//0xCC62128C
	UINT32                                                  reserved191;	//0xCC621290
	UINT32                                                  reserved192;	//0xCC621294
	UINT32                                                  reserved193;	//0xCC621298
	UINT32                                                  reserved194;	//0xCC62129C
	UINT32                                                  reserved195;	//0xCC6212A0
	UINT32                                                  reserved196;	//0xCC6212A4
	UINT32                                                  reserved197;	//0xCC6212A8
	UINT32                                                  reserved198;	//0xCC6212AC
	UINT32                                                  reserved199;	//0xCC6212B0
	UINT32                                                  reserved200;	//0xCC6212B4
	UINT32                                                  reserved201;	//0xCC6212B8
	UINT32                                                  reserved202;	//0xCC6212BC
	UINT32                                                  reserved203;	//0xCC6212C0
	UINT32                                                  reserved204;	//0xCC6212C4
	UINT32                                                  reserved205;	//0xCC6212C8
	UINT32                                                  reserved206;	//0xCC6212CC
	UINT32                                                  reserved207;	//0xCC6212D0
	UINT32                                                  reserved208;	//0xCC6212D4
	UINT32                                                  reserved209;	//0xCC6212D8
	UINT32                                                  reserved210;	//0xCC6212DC
	UINT32                                                  reserved211;	//0xCC6212E0
	UINT32                                                  reserved212;	//0xCC6212E4
	UINT32                                                  reserved213;	//0xCC6212E8
	UINT32                                                  reserved214;	//0xCC6212EC
	UINT32                                                  reserved215;	//0xCC6212F0
	UINT32                                                  reserved216;	//0xCC6212F4
	UINT32                                                  reserved217;	//0xCC6212F8
	UINT32                                                  reserved218;	//0xCC6212FC
	PE_O24_2K_SHP_CORE_TMAP_STAT_00_T            shp_core_tmap_stat_00;	//0xCC621300
	PE_O24_2K_SHP_CORE_TMAP_STAT_01_T            shp_core_tmap_stat_01;	//0xCC621304
	PE_O24_2K_SHP_CORE_TMAP_STAT_02_T            shp_core_tmap_stat_02;	//0xCC621308
	PE_O24_2K_SHP_CORE_TMAP_STAT_03_T            shp_core_tmap_stat_03;	//0xCC62130C
	PE_O24_2K_SHP_CORE_TMAP_STAT_04_T            shp_core_tmap_stat_04;	//0xCC621310
	PE_O24_2K_SHP_CORE_TMAP_STAT_05_T            shp_core_tmap_stat_05;	//0xCC621314
	PE_O24_2K_SHP_CORE_TMAP_STAT_06_T            shp_core_tmap_stat_06;	//0xCC621318
	PE_O24_2K_SHP_CORE_TMAP_STAT_07_T            shp_core_tmap_stat_07;	//0xCC62131C
	PE_O24_2K_SHP_ELLIPSE_CTRL_00_T                shp_ellipse_ctrl_00;	//0xCC621320
	PE_O24_2K_SHP_ELLIPSE_CTRL_01_T                shp_ellipse_ctrl_01;	//0xCC621324
	PE_O24_2K_SHP_ELLIPSE_CTRL_02_T                shp_ellipse_ctrl_02;	//0xCC621328
	PE_O24_2K_SHP_ELLIPSE_CTRL_03_T                shp_ellipse_ctrl_03;	//0xCC62132C
	PE_O24_2K_SHP_ELLIPSE_CTRL_04_T                shp_ellipse_ctrl_04;	//0xCC621330
	PE_O24_2K_SHP_ELLIPSE_CTRL_05_T                shp_ellipse_ctrl_05;	//0xCC621334
	PE_O24_2K_SHP_ELLIPSE_CTRL_06_T                shp_ellipse_ctrl_06;	//0xCC621338
	PE_O24_2K_SHP_ELLIPSE_CTRL_07_T                shp_ellipse_ctrl_07;	//0xCC62133C
	PE_O24_2K_SHP_ELLIPSE_CTRL_08_T                shp_ellipse_ctrl_08;	//0xCC621340
	PE_O24_2K_SHP_ELLIPSE_CTRL_09_T                shp_ellipse_ctrl_09;	//0xCC621344
	PE_O24_2K_SHP_ELLIPSE_CTRL_10_T                shp_ellipse_ctrl_10;	//0xCC621348
	PE_O24_2K_SHP_ELLIPSE_CTRL_11_T                shp_ellipse_ctrl_11;	//0xCC62134C
	PE_O24_2K_SHP_ELLIPSE_CTRL_12_T                shp_ellipse_ctrl_12;	//0xCC621350
	PE_O24_2K_SHP_ELLIPSE_LUT_CTRL_00_T        shp_ellipse_lut_ctrl_00;	//0xCC621354
	PE_O24_2K_SHP_ELLIPSE_LUT_CTRL_01_T        shp_ellipse_lut_ctrl_01;	//0xCC621358
	UINT32                                                  reserved219;	//0xCC62135C
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_00_T          shp_luma_blend_ctrl_00;	//0xCC621360
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_01_T          shp_luma_blend_ctrl_01;	//0xCC621364
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_02_T          shp_luma_blend_ctrl_02;	//0xCC621368
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_03_T          shp_luma_blend_ctrl_03;	//0xCC62136C
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_04_T          shp_luma_blend_ctrl_04;	//0xCC621370
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_05_T          shp_luma_blend_ctrl_05;	//0xCC621374
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_06_T          shp_luma_blend_ctrl_06;	//0xCC621378
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_07_T          shp_luma_blend_ctrl_07;	//0xCC62137C
	PE_O24_2K_SHP_LUMA_BLEND_CTRL_08_T          shp_luma_blend_ctrl_08;	//0xCC621380
	PE_O24_2K_SHP_SM_BLEND_CTRL_00_T              shp_sm_blend_ctrl_00;	//0xCC621384
	PE_O24_2K_SHP_SM_BLEND_CTRL_01_T              shp_sm_blend_ctrl_01;	//0xCC621388
	PE_O24_2K_SHP_SM_BLEND_CTRL_02_T              shp_sm_blend_ctrl_02;	//0xCC62138C
	UINT32                                                  reserved220;	//0xCC621390
	UINT32                                                  reserved221;	//0xCC621394
	UINT32                                                  reserved222;	//0xCC621398
	UINT32                                                  reserved223;	//0xCC62139C
	UINT32                                                  reserved224;	//0xCC6213A0
	UINT32                                                  reserved225;	//0xCC6213A4
	UINT32                                                  reserved226;	//0xCC6213A8
	UINT32                                                  reserved227;	//0xCC6213AC
	UINT32                                                  reserved228;	//0xCC6213B0
	UINT32                                                  reserved229;	//0xCC6213B4
	UINT32                                                  reserved230;	//0xCC6213B8
	UINT32                                                  reserved231;	//0xCC6213BC
	UINT32                                                  reserved232;	//0xCC6213C0
	UINT32                                                  reserved233;	//0xCC6213C4
	UINT32                                                  reserved234;	//0xCC6213C8
	UINT32                                                  reserved235;	//0xCC6213CC
	UINT32                                                  reserved236;	//0xCC6213D0
	UINT32                                                  reserved237;	//0xCC6213D4
	UINT32                                                  reserved238;	//0xCC6213D8
	UINT32                                                  reserved239;	//0xCC6213DC
	UINT32                                                  reserved240;	//0xCC6213E0
	UINT32                                                  reserved241;	//0xCC6213E4
	UINT32                                                  reserved242;	//0xCC6213E8
	UINT32                                                  reserved243;	//0xCC6213EC
	PE_O24_2K_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0xCC6213F0
	PE_O24_2K_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0xCC6213F4
	PE_O24_2K_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0xCC6213F8
	PE_O24_2K_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0xCC6213FC
}PE_SR_2K_SHP_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621400 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O24_2K_SHC_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621404 RW 0x0438_03C0
	UINT32 reg_top_width                    :12;	//(11:0,NA,960) //processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621408 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_2K_SHC_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62140C RW 0x00A9_0000
	UINT32 resvd0                           :16;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,169) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621500 RW 0xFFFF_0000
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :13;
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //pattern pixel value (Y)
	};
}PE_O24_2K_SHC_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621800 RW 0x8010_0179
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
}PE_O24_2K_SHC_CDJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621804 RW 0x0080_0000
	UINT32 reg_cdj_level_th                 :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_cdj_n_avg_gain               :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O24_2K_SHC_CDJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621808 RW 0x0000_1010
	UINT32 reg_cdj_g0_cnt_min               :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_cdj_g0_mul                   :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O24_2K_SHC_CDJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62180C RW 0x8010_0840
	UINT32 reg_cdj_g1_protect_min           :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_cdj_g1_mul                   :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_cdj_edge_min                 :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_cdj_edge_mul                 :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O24_2K_SHC_CDJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621810 RW 0x0000_0000
	UINT32 reg_cdj_dir_sel_c1               :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_cdj_dir_sel_c2               :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_cdj_dir_sel_c3               :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_cdj_dir_sel_c4               :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O24_2K_SHC_CDJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621814 RW 0x0000_0000
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
}PE_O24_2K_SHC_CDJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621818 RW 0x0000_0040
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
}PE_O24_2K_SHC_CDJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62181C RW 0x0015_5550
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
}PE_O24_2K_SHC_CDJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621820 RW 0x0000_0040
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
}PE_O24_2K_SHC_CDJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621824 RW 0x002A_A040
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
}PE_O24_2K_SHC_CDJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621828 RW 0x002A_A040
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
}PE_O24_2K_SHC_CDJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62182C RW 0x000A_A040
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
}PE_O24_2K_SHC_CDJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621830 RW 0x0000_00E4
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
}PE_O24_2K_SHC_CDJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621834 RW 0x0000_5540
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
}PE_O24_2K_SHC_CDJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621838 RW 0x0020_5542
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
}PE_O24_2K_SHC_CDJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62183C RW 0x0008_1508
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
}PE_O24_2K_SHC_CDJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621840 RW 0x0002_0420
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
}PE_O24_2K_SHC_CDJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621844 RW 0x0000_8080
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
}PE_O24_2K_SHC_CDJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621848 RW 0x0000_2A00
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
}PE_O24_2K_SHC_CDJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62184C RW 0x0000_2A00
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
}PE_O24_2K_SHC_CDJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621850 RW 0x0000_0008
	UINT32 reg_cdj_pattern1_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_cdj_pattern1_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_cdj_pattern1_flip1_h         :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_cdj_pattern1_flip1_v         :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O24_2K_SHC_CDJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621854 RW 0x0000_2800
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
}PE_O24_2K_SHC_CDJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621858 RW 0x0005_0A00
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
}PE_O24_2K_SHC_CDJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62185C RW 0x0005_4280
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
}PE_O24_2K_SHC_CDJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621860 RW 0x0005_50A0
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
}PE_O24_2K_SHC_CDJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621864 RW 0x0005_4280
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
}PE_O24_2K_SHC_CDJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621868 RW 0x0005_0A00
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
}PE_O24_2K_SHC_CDJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62186C RW 0x0000_2800
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
}PE_O24_2K_SHC_CDJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621870 RW 0x0000_0004
	UINT32 reg_cdj_pattern2_flip0_h         :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_cdj_pattern2_flip0_v         :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_cdj_pattern2_flip1_h         :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_cdj_pattern2_flip1_v         :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O24_2K_SHC_CDJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621874 RW 0x00FF_0628
	UINT32 reg_cdj_soft_g0_mul              :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g0_offset           :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g0_max              :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHC_CDJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621878 RW 0x00FF_0414
	UINT32 reg_cdj_soft_g1_mul              :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g1_offset           :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g1_max              :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHC_CDJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62187C RW 0x00FF_0620
	UINT32 reg_cdj_soft_g2_mul              :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g2_offset           :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g2_max              :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O24_2K_SHC_CDJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621880 RW 0x0001_1400
	UINT32 reg_cdj_soft_base                :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_cdj_soft_sel_1357_gain       :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_cdj_soft_single_match_en     :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O24_2K_SHC_CDJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621890 RW 0x0000_0100
	UINT32 reg_cdir_blur_detour             :1;	//(0:0,NA,0) //dir blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_cdir_blur_buf_detour         :1;	//(4:4,NA,0) //dir blur buffer detour enable
	UINT32 resvd1                           :3;
	UINT32 reg_cdir_blur_en                 :1;	//(8:8,NA,1) //dir blur enable
	UINT32 resvd2                           :23;
	};
}PE_O24_2K_SHC_CDIR_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621894 RW 0x0040_000A
	UINT32 reg_cdir_blur_base               :8;	//(7:0,NA,10) //dir blur base
	UINT32 resvd0                           :8;
	UINT32 reg_cdir_blur_gain               :8;	//(23:16,NA,64) //dir blur gain
	UINT32 resvd1                           :8;
	};
}PE_O24_2K_SHC_CDIR_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6218A0 RW 0x0000_0000
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
}PE_O24_2K_SHC_CDJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6218A4 RW 0x0000_0000
	UINT32 reg_win_cdj_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CDJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6218A8 RW 0x0437_077F
	UINT32 reg_win_cdj_win_w0_x1            :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y1            :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CDJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6218AC RW 0x0000_0000
	UINT32 reg_win_cdj_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CDJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6218B0 RW 0x0437_077F
	UINT32 reg_win_cdj_win_w1_x1            :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y1            :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CDJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621A00 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621A04 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621A08 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621A0C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_2K_SHC_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621A10 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O24_2K_SHC_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621A14 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O24_2K_SHC_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621AF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHC_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621AF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHC_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621AF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHC_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC621AFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_2K_SHC_FSW_CTRL_03_T;

typedef struct {
	PE_O24_2K_SHC_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0xCC621400
	PE_O24_2K_SHC_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0xCC621404
	PE_O24_2K_SHC_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0xCC621408
	PE_O24_2K_SHC_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0xCC62140C
	UINT32                                                    reserved0;	//0xCC621410
	UINT32                                                    reserved1;	//0xCC621414
	UINT32                                                    reserved2;	//0xCC621418
	UINT32                                                    reserved3;	//0xCC62141C
	UINT32                                                    reserved4;	//0xCC621420
	UINT32                                                    reserved5;	//0xCC621424
	UINT32                                                    reserved6;	//0xCC621428
	UINT32                                                    reserved7;	//0xCC62142C
	UINT32                                                    reserved8;	//0xCC621430
	UINT32                                                    reserved9;	//0xCC621434
	UINT32                                                   reserved10;	//0xCC621438
	UINT32                                                   reserved11;	//0xCC62143C
	UINT32                                                   reserved12;	//0xCC621440
	UINT32                                                   reserved13;	//0xCC621444
	UINT32                                                   reserved14;	//0xCC621448
	UINT32                                                   reserved15;	//0xCC62144C
	UINT32                                                   reserved16;	//0xCC621450
	UINT32                                                   reserved17;	//0xCC621454
	UINT32                                                   reserved18;	//0xCC621458
	UINT32                                                   reserved19;	//0xCC62145C
	UINT32                                                   reserved20;	//0xCC621460
	UINT32                                                   reserved21;	//0xCC621464
	UINT32                                                   reserved22;	//0xCC621468
	UINT32                                                   reserved23;	//0xCC62146C
	UINT32                                                   reserved24;	//0xCC621470
	UINT32                                                   reserved25;	//0xCC621474
	UINT32                                                   reserved26;	//0xCC621478
	UINT32                                                   reserved27;	//0xCC62147C
	UINT32                                                   reserved28;	//0xCC621480
	UINT32                                                   reserved29;	//0xCC621484
	UINT32                                                   reserved30;	//0xCC621488
	UINT32                                                   reserved31;	//0xCC62148C
	UINT32                                                   reserved32;	//0xCC621490
	UINT32                                                   reserved33;	//0xCC621494
	UINT32                                                   reserved34;	//0xCC621498
	UINT32                                                   reserved35;	//0xCC62149C
	UINT32                                                   reserved36;	//0xCC6214A0
	UINT32                                                   reserved37;	//0xCC6214A4
	UINT32                                                   reserved38;	//0xCC6214A8
	UINT32                                                   reserved39;	//0xCC6214AC
	UINT32                                                   reserved40;	//0xCC6214B0
	UINT32                                                   reserved41;	//0xCC6214B4
	UINT32                                                   reserved42;	//0xCC6214B8
	UINT32                                                   reserved43;	//0xCC6214BC
	UINT32                                                   reserved44;	//0xCC6214C0
	UINT32                                                   reserved45;	//0xCC6214C4
	UINT32                                                   reserved46;	//0xCC6214C8
	UINT32                                                   reserved47;	//0xCC6214CC
	UINT32                                                   reserved48;	//0xCC6214D0
	UINT32                                                   reserved49;	//0xCC6214D4
	UINT32                                                   reserved50;	//0xCC6214D8
	UINT32                                                   reserved51;	//0xCC6214DC
	UINT32                                                   reserved52;	//0xCC6214E0
	UINT32                                                   reserved53;	//0xCC6214E4
	UINT32                                                   reserved54;	//0xCC6214E8
	UINT32                                                   reserved55;	//0xCC6214EC
	UINT32                                                   reserved56;	//0xCC6214F0
	UINT32                                                   reserved57;	//0xCC6214F4
	UINT32                                                   reserved58;	//0xCC6214F8
	UINT32                                                   reserved59;	//0xCC6214FC
	PE_O24_2K_SHC_PAT_GEN_CTRL_00_T                   shp_pat_gen_ctrl_00;	//0xCC621500
	UINT32                                                   reserved60;	//0xCC621504
	UINT32                                                   reserved61;	//0xCC621508
	UINT32                                                   reserved62;	//0xCC62150C
	UINT32                                                   reserved63;	//0xCC621510
	UINT32                                                   reserved64;	//0xCC621514
	UINT32                                                   reserved65;	//0xCC621518
	UINT32                                                   reserved66;	//0xCC62151C
	UINT32                                                   reserved67;	//0xCC621520
	UINT32                                                   reserved68;	//0xCC621524
	UINT32                                                   reserved69;	//0xCC621528
	UINT32                                                   reserved70;	//0xCC62152C
	UINT32                                                   reserved71;	//0xCC621530
	UINT32                                                   reserved72;	//0xCC621534
	UINT32                                                   reserved73;	//0xCC621538
	UINT32                                                   reserved74;	//0xCC62153C
	UINT32                                                   reserved75;	//0xCC621540
	UINT32                                                   reserved76;	//0xCC621544
	UINT32                                                   reserved77;	//0xCC621548
	UINT32                                                   reserved78;	//0xCC62154C
	UINT32                                                   reserved79;	//0xCC621550
	UINT32                                                   reserved80;	//0xCC621554
	UINT32                                                   reserved81;	//0xCC621558
	UINT32                                                   reserved82;	//0xCC62155C
	UINT32                                                   reserved83;	//0xCC621560
	UINT32                                                   reserved84;	//0xCC621564
	UINT32                                                   reserved85;	//0xCC621568
	UINT32                                                   reserved86;	//0xCC62156C
	UINT32                                                   reserved87;	//0xCC621570
	UINT32                                                   reserved88;	//0xCC621574
	UINT32                                                   reserved89;	//0xCC621578
	UINT32                                                   reserved90;	//0xCC62157C
	UINT32                                                   reserved91;	//0xCC621580
	UINT32                                                   reserved92;	//0xCC621584
	UINT32                                                   reserved93;	//0xCC621588
	UINT32                                                   reserved94;	//0xCC62158C
	UINT32                                                   reserved95;	//0xCC621590
	UINT32                                                   reserved96;	//0xCC621594
	UINT32                                                   reserved97;	//0xCC621598
	UINT32                                                   reserved98;	//0xCC62159C
	UINT32                                                   reserved99;	//0xCC6215A0
	UINT32                                                  reserved100;	//0xCC6215A4
	UINT32                                                  reserved101;	//0xCC6215A8
	UINT32                                                  reserved102;	//0xCC6215AC
	UINT32                                                  reserved103;	//0xCC6215B0
	UINT32                                                  reserved104;	//0xCC6215B4
	UINT32                                                  reserved105;	//0xCC6215B8
	UINT32                                                  reserved106;	//0xCC6215BC
	UINT32                                                  reserved107;	//0xCC6215C0
	UINT32                                                  reserved108;	//0xCC6215C4
	UINT32                                                  reserved109;	//0xCC6215C8
	UINT32                                                  reserved110;	//0xCC6215CC
	UINT32                                                  reserved111;	//0xCC6215D0
	UINT32                                                  reserved112;	//0xCC6215D4
	UINT32                                                  reserved113;	//0xCC6215D8
	UINT32                                                  reserved114;	//0xCC6215DC
	UINT32                                                  reserved115;	//0xCC6215E0
	UINT32                                                  reserved116;	//0xCC6215E4
	UINT32                                                  reserved117;	//0xCC6215E8
	UINT32                                                  reserved118;	//0xCC6215EC
	UINT32                                                  reserved119;	//0xCC6215F0
	UINT32                                                  reserved120;	//0xCC6215F4
	UINT32                                                  reserved121;	//0xCC6215F8
	UINT32                                                  reserved122;	//0xCC6215FC
	UINT32                                                  reserved123;	//0xCC621600
	UINT32                                                  reserved124;	//0xCC621604
	UINT32                                                  reserved125;	//0xCC621608
	UINT32                                                  reserved126;	//0xCC62160C
	UINT32                                                  reserved127;	//0xCC621610
	UINT32                                                  reserved128;	//0xCC621614
	UINT32                                                  reserved129;	//0xCC621618
	UINT32                                                  reserved130;	//0xCC62161C
	UINT32                                                  reserved131;	//0xCC621620
	UINT32                                                  reserved132;	//0xCC621624
	UINT32                                                  reserved133;	//0xCC621628
	UINT32                                                  reserved134;	//0xCC62162C
	UINT32                                                  reserved135;	//0xCC621630
	UINT32                                                  reserved136;	//0xCC621634
	UINT32                                                  reserved137;	//0xCC621638
	UINT32                                                  reserved138;	//0xCC62163C
	UINT32                                                  reserved139;	//0xCC621640
	UINT32                                                  reserved140;	//0xCC621644
	UINT32                                                  reserved141;	//0xCC621648
	UINT32                                                  reserved142;	//0xCC62164C
	UINT32                                                  reserved143;	//0xCC621650
	UINT32                                                  reserved144;	//0xCC621654
	UINT32                                                  reserved145;	//0xCC621658
	UINT32                                                  reserved146;	//0xCC62165C
	UINT32                                                  reserved147;	//0xCC621660
	UINT32                                                  reserved148;	//0xCC621664
	UINT32                                                  reserved149;	//0xCC621668
	UINT32                                                  reserved150;	//0xCC62166C
	UINT32                                                  reserved151;	//0xCC621670
	UINT32                                                  reserved152;	//0xCC621674
	UINT32                                                  reserved153;	//0xCC621678
	UINT32                                                  reserved154;	//0xCC62167C
	UINT32                                                  reserved155;	//0xCC621680
	UINT32                                                  reserved156;	//0xCC621684
	UINT32                                                  reserved157;	//0xCC621688
	UINT32                                                  reserved158;	//0xCC62168C
	UINT32                                                  reserved159;	//0xCC621690
	UINT32                                                  reserved160;	//0xCC621694
	UINT32                                                  reserved161;	//0xCC621698
	UINT32                                                  reserved162;	//0xCC62169C
	UINT32                                                  reserved163;	//0xCC6216A0
	UINT32                                                  reserved164;	//0xCC6216A4
	UINT32                                                  reserved165;	//0xCC6216A8
	UINT32                                                  reserved166;	//0xCC6216AC
	UINT32                                                  reserved167;	//0xCC6216B0
	UINT32                                                  reserved168;	//0xCC6216B4
	UINT32                                                  reserved169;	//0xCC6216B8
	UINT32                                                  reserved170;	//0xCC6216BC
	UINT32                                                  reserved171;	//0xCC6216C0
	UINT32                                                  reserved172;	//0xCC6216C4
	UINT32                                                  reserved173;	//0xCC6216C8
	UINT32                                                  reserved174;	//0xCC6216CC
	UINT32                                                  reserved175;	//0xCC6216D0
	UINT32                                                  reserved176;	//0xCC6216D4
	UINT32                                                  reserved177;	//0xCC6216D8
	UINT32                                                  reserved178;	//0xCC6216DC
	UINT32                                                  reserved179;	//0xCC6216E0
	UINT32                                                  reserved180;	//0xCC6216E4
	UINT32                                                  reserved181;	//0xCC6216E8
	UINT32                                                  reserved182;	//0xCC6216EC
	UINT32                                                  reserved183;	//0xCC6216F0
	UINT32                                                  reserved184;	//0xCC6216F4
	UINT32                                                  reserved185;	//0xCC6216F8
	UINT32                                                  reserved186;	//0xCC6216FC
	UINT32                                                  reserved187;	//0xCC621700
	UINT32                                                  reserved188;	//0xCC621704
	UINT32                                                  reserved189;	//0xCC621708
	UINT32                                                  reserved190;	//0xCC62170C
	UINT32                                                  reserved191;	//0xCC621710
	UINT32                                                  reserved192;	//0xCC621714
	UINT32                                                  reserved193;	//0xCC621718
	UINT32                                                  reserved194;	//0xCC62171C
	UINT32                                                  reserved195;	//0xCC621720
	UINT32                                                  reserved196;	//0xCC621724
	UINT32                                                  reserved197;	//0xCC621728
	UINT32                                                  reserved198;	//0xCC62172C
	UINT32                                                  reserved199;	//0xCC621730
	UINT32                                                  reserved200;	//0xCC621734
	UINT32                                                  reserved201;	//0xCC621738
	UINT32                                                  reserved202;	//0xCC62173C
	UINT32                                                  reserved203;	//0xCC621740
	UINT32                                                  reserved204;	//0xCC621744
	UINT32                                                  reserved205;	//0xCC621748
	UINT32                                                  reserved206;	//0xCC62174C
	UINT32                                                  reserved207;	//0xCC621750
	UINT32                                                  reserved208;	//0xCC621754
	UINT32                                                  reserved209;	//0xCC621758
	UINT32                                                  reserved210;	//0xCC62175C
	UINT32                                                  reserved211;	//0xCC621760
	UINT32                                                  reserved212;	//0xCC621764
	UINT32                                                  reserved213;	//0xCC621768
	UINT32                                                  reserved214;	//0xCC62176C
	UINT32                                                  reserved215;	//0xCC621770
	UINT32                                                  reserved216;	//0xCC621774
	UINT32                                                  reserved217;	//0xCC621778
	UINT32                                                  reserved218;	//0xCC62177C
	UINT32                                                  reserved219;	//0xCC621780
	UINT32                                                  reserved220;	//0xCC621784
	UINT32                                                  reserved221;	//0xCC621788
	UINT32                                                  reserved222;	//0xCC62178C
	UINT32                                                  reserved223;	//0xCC621790
	UINT32                                                  reserved224;	//0xCC621794
	UINT32                                                  reserved225;	//0xCC621798
	UINT32                                                  reserved226;	//0xCC62179C
	UINT32                                                  reserved227;	//0xCC6217A0
	UINT32                                                  reserved228;	//0xCC6217A4
	UINT32                                                  reserved229;	//0xCC6217A8
	UINT32                                                  reserved230;	//0xCC6217AC
	UINT32                                                  reserved231;	//0xCC6217B0
	UINT32                                                  reserved232;	//0xCC6217B4
	UINT32                                                  reserved233;	//0xCC6217B8
	UINT32                                                  reserved234;	//0xCC6217BC
	UINT32                                                  reserved235;	//0xCC6217C0
	UINT32                                                  reserved236;	//0xCC6217C4
	UINT32                                                  reserved237;	//0xCC6217C8
	UINT32                                                  reserved238;	//0xCC6217CC
	UINT32                                                  reserved239;	//0xCC6217D0
	UINT32                                                  reserved240;	//0xCC6217D4
	UINT32                                                  reserved241;	//0xCC6217D8
	UINT32                                                  reserved242;	//0xCC6217DC
	UINT32                                                  reserved243;	//0xCC6217E0
	UINT32                                                  reserved244;	//0xCC6217E4
	UINT32                                                  reserved245;	//0xCC6217E8
	UINT32                                                  reserved246;	//0xCC6217EC
	UINT32                                                  reserved247;	//0xCC6217F0
	UINT32                                                  reserved248;	//0xCC6217F4
	UINT32                                                  reserved249;	//0xCC6217F8
	UINT32                                                  reserved250;	//0xCC6217FC
	PE_O24_2K_SHC_CDJ_CTRL_00_T                           shp_cdj_ctrl_00;	//0xCC621800
	PE_O24_2K_SHC_CDJ_CTRL_01_T                           shp_cdj_ctrl_01;	//0xCC621804
	PE_O24_2K_SHC_CDJ_CTRL_02_T                           shp_cdj_ctrl_02;	//0xCC621808
	PE_O24_2K_SHC_CDJ_CTRL_03_T                           shp_cdj_ctrl_03;	//0xCC62180C
	PE_O24_2K_SHC_CDJ_CTRL_04_T                           shp_cdj_ctrl_04;	//0xCC621810
	PE_O24_2K_SHC_CDJ_CTRL_05_T                           shp_cdj_ctrl_05;	//0xCC621814
	PE_O24_2K_SHC_CDJ_CTRL_06_T                           shp_cdj_ctrl_06;	//0xCC621818
	PE_O24_2K_SHC_CDJ_CTRL_07_T                           shp_cdj_ctrl_07;	//0xCC62181C
	PE_O24_2K_SHC_CDJ_CTRL_08_T                           shp_cdj_ctrl_08;	//0xCC621820
	PE_O24_2K_SHC_CDJ_CTRL_09_T                           shp_cdj_ctrl_09;	//0xCC621824
	PE_O24_2K_SHC_CDJ_CTRL_0A_T                           shp_cdj_ctrl_0a;	//0xCC621828
	PE_O24_2K_SHC_CDJ_CTRL_0B_T                           shp_cdj_ctrl_0b;	//0xCC62182C
	PE_O24_2K_SHC_CDJ_CTRL_0C_T                           shp_cdj_ctrl_0c;	//0xCC621830
	PE_O24_2K_SHC_CDJ_CTRL_0D_T                           shp_cdj_ctrl_0d;	//0xCC621834
	PE_O24_2K_SHC_CDJ_CTRL_0E_T                           shp_cdj_ctrl_0e;	//0xCC621838
	PE_O24_2K_SHC_CDJ_CTRL_0F_T                           shp_cdj_ctrl_0f;	//0xCC62183C
	PE_O24_2K_SHC_CDJ_CTRL_10_T                           shp_cdj_ctrl_10;	//0xCC621840
	PE_O24_2K_SHC_CDJ_CTRL_11_T                           shp_cdj_ctrl_11;	//0xCC621844
	PE_O24_2K_SHC_CDJ_CTRL_12_T                           shp_cdj_ctrl_12;	//0xCC621848
	PE_O24_2K_SHC_CDJ_CTRL_13_T                           shp_cdj_ctrl_13;	//0xCC62184C
	PE_O24_2K_SHC_CDJ_CTRL_14_T                           shp_cdj_ctrl_14;	//0xCC621850
	PE_O24_2K_SHC_CDJ_CTRL_15_T                           shp_cdj_ctrl_15;	//0xCC621854
	PE_O24_2K_SHC_CDJ_CTRL_16_T                           shp_cdj_ctrl_16;	//0xCC621858
	PE_O24_2K_SHC_CDJ_CTRL_17_T                           shp_cdj_ctrl_17;	//0xCC62185C
	PE_O24_2K_SHC_CDJ_CTRL_18_T                           shp_cdj_ctrl_18;	//0xCC621860
	PE_O24_2K_SHC_CDJ_CTRL_19_T                           shp_cdj_ctrl_19;	//0xCC621864
	PE_O24_2K_SHC_CDJ_CTRL_1A_T                           shp_cdj_ctrl_1a;	//0xCC621868
	PE_O24_2K_SHC_CDJ_CTRL_1B_T                           shp_cdj_ctrl_1b;	//0xCC62186C
	PE_O24_2K_SHC_CDJ_CTRL_1C_T                           shp_cdj_ctrl_1c;	//0xCC621870
	PE_O24_2K_SHC_CDJ_CTRL_1D_T                           shp_cdj_ctrl_1d;	//0xCC621874
	PE_O24_2K_SHC_CDJ_CTRL_1E_T                           shp_cdj_ctrl_1e;	//0xCC621878
	PE_O24_2K_SHC_CDJ_CTRL_1F_T                           shp_cdj_ctrl_1f;	//0xCC62187C
	PE_O24_2K_SHC_CDJ_CTRL_20_T                           shp_cdj_ctrl_20;	//0xCC621880
	UINT32                                                  reserved251;	//0xCC621884
	UINT32                                                  reserved252;	//0xCC621888
	UINT32                                                  reserved253;	//0xCC62188C
	PE_O24_2K_SHC_CDIR_BLUR_CTRL_00_T               shp_cdir_blur_ctrl_00;	//0xCC621890
	PE_O24_2K_SHC_CDIR_BLUR_CTRL_01_T               shp_cdir_blur_ctrl_01;	//0xCC621894
	UINT32                                                  reserved254;	//0xCC621898
	UINT32                                                  reserved255;	//0xCC62189C
	PE_O24_2K_SHC_CDJ_WIN_CTRL_00_T                   shp_cdj_win_ctrl_00;	//0xCC6218A0
	PE_O24_2K_SHC_CDJ_WIN_CTRL_01_T                   shp_cdj_win_ctrl_01;	//0xCC6218A4
	PE_O24_2K_SHC_CDJ_WIN_CTRL_02_T                   shp_cdj_win_ctrl_02;	//0xCC6218A8
	PE_O24_2K_SHC_CDJ_WIN_CTRL_03_T                   shp_cdj_win_ctrl_03;	//0xCC6218AC
	PE_O24_2K_SHC_CDJ_WIN_CTRL_04_T                   shp_cdj_win_ctrl_04;	//0xCC6218B0
	UINT32                                                  reserved256;	//0xCC6218B4
	UINT32                                                  reserved257;	//0xCC6218B8
	UINT32                                                  reserved258;	//0xCC6218BC
	UINT32                                                  reserved259;	//0xCC6218C0
	UINT32                                                  reserved260;	//0xCC6218C4
	UINT32                                                  reserved261;	//0xCC6218C8
	UINT32                                                  reserved262;	//0xCC6218CC
	UINT32                                                  reserved263;	//0xCC6218D0
	UINT32                                                  reserved264;	//0xCC6218D4
	UINT32                                                  reserved265;	//0xCC6218D8
	UINT32                                                  reserved266;	//0xCC6218DC
	UINT32                                                  reserved267;	//0xCC6218E0
	UINT32                                                  reserved268;	//0xCC6218E4
	UINT32                                                  reserved269;	//0xCC6218E8
	UINT32                                                  reserved270;	//0xCC6218EC
	UINT32                                                  reserved271;	//0xCC6218F0
	UINT32                                                  reserved272;	//0xCC6218F4
	UINT32                                                  reserved273;	//0xCC6218F8
	UINT32                                                  reserved274;	//0xCC6218FC
	UINT32                                                  reserved275;	//0xCC621900
	UINT32                                                  reserved276;	//0xCC621904
	UINT32                                                  reserved277;	//0xCC621908
	UINT32                                                  reserved278;	//0xCC62190C
	UINT32                                                  reserved279;	//0xCC621910
	UINT32                                                  reserved280;	//0xCC621914
	UINT32                                                  reserved281;	//0xCC621918
	UINT32                                                  reserved282;	//0xCC62191C
	UINT32                                                  reserved283;	//0xCC621920
	UINT32                                                  reserved284;	//0xCC621924
	UINT32                                                  reserved285;	//0xCC621928
	UINT32                                                  reserved286;	//0xCC62192C
	UINT32                                                  reserved287;	//0xCC621930
	UINT32                                                  reserved288;	//0xCC621934
	UINT32                                                  reserved289;	//0xCC621938
	UINT32                                                  reserved290;	//0xCC62193C
	UINT32                                                  reserved291;	//0xCC621940
	UINT32                                                  reserved292;	//0xCC621944
	UINT32                                                  reserved293;	//0xCC621948
	UINT32                                                  reserved294;	//0xCC62194C
	UINT32                                                  reserved295;	//0xCC621950
	UINT32                                                  reserved296;	//0xCC621954
	UINT32                                                  reserved297;	//0xCC621958
	UINT32                                                  reserved298;	//0xCC62195C
	UINT32                                                  reserved299;	//0xCC621960
	UINT32                                                  reserved300;	//0xCC621964
	UINT32                                                  reserved301;	//0xCC621968
	UINT32                                                  reserved302;	//0xCC62196C
	UINT32                                                  reserved303;	//0xCC621970
	UINT32                                                  reserved304;	//0xCC621974
	UINT32                                                  reserved305;	//0xCC621978
	UINT32                                                  reserved306;	//0xCC62197C
	UINT32                                                  reserved307;	//0xCC621980
	UINT32                                                  reserved308;	//0xCC621984
	UINT32                                                  reserved309;	//0xCC621988
	UINT32                                                  reserved310;	//0xCC62198C
	UINT32                                                  reserved311;	//0xCC621990
	UINT32                                                  reserved312;	//0xCC621994
	UINT32                                                  reserved313;	//0xCC621998
	UINT32                                                  reserved314;	//0xCC62199C
	UINT32                                                  reserved315;	//0xCC6219A0
	UINT32                                                  reserved316;	//0xCC6219A4
	UINT32                                                  reserved317;	//0xCC6219A8
	UINT32                                                  reserved318;	//0xCC6219AC
	UINT32                                                  reserved319;	//0xCC6219B0
	UINT32                                                  reserved320;	//0xCC6219B4
	UINT32                                                  reserved321;	//0xCC6219B8
	UINT32                                                  reserved322;	//0xCC6219BC
	UINT32                                                  reserved323;	//0xCC6219C0
	UINT32                                                  reserved324;	//0xCC6219C4
	UINT32                                                  reserved325;	//0xCC6219C8
	UINT32                                                  reserved326;	//0xCC6219CC
	UINT32                                                  reserved327;	//0xCC6219D0
	UINT32                                                  reserved328;	//0xCC6219D4
	UINT32                                                  reserved329;	//0xCC6219D8
	UINT32                                                  reserved330;	//0xCC6219DC
	UINT32                                                  reserved331;	//0xCC6219E0
	UINT32                                                  reserved332;	//0xCC6219E4
	UINT32                                                  reserved333;	//0xCC6219E8
	UINT32                                                  reserved334;	//0xCC6219EC
	UINT32                                                  reserved335;	//0xCC6219F0
	UINT32                                                  reserved336;	//0xCC6219F4
	UINT32                                                  reserved337;	//0xCC6219F8
	UINT32                                                  reserved338;	//0xCC6219FC
	PE_O24_2K_SHC_CORE_STAT_00_T                         shp_core_stat_00;	//0xCC621A00
	PE_O24_2K_SHC_CORE_STAT_01_T                         shp_core_stat_01;	//0xCC621A04
	PE_O24_2K_SHC_CORE_STAT_02_T                         shp_core_stat_02;	//0xCC621A08
	PE_O24_2K_SHC_CORE_STAT_03_T                         shp_core_stat_03;	//0xCC621A0C
	PE_O24_2K_SHC_CORE_STAT_04_T                         shp_core_stat_04;	//0xCC621A10
	PE_O24_2K_SHC_CORE_STAT_05_T                         shp_core_stat_05;	//0xCC621A14
	UINT32                                                  reserved339;	//0xCC621A18
	UINT32                                                  reserved340;	//0xCC621A1C
	UINT32                                                  reserved341;	//0xCC621A20
	UINT32                                                  reserved342;	//0xCC621A24
	UINT32                                                  reserved343;	//0xCC621A28
	UINT32                                                  reserved344;	//0xCC621A2C
	UINT32                                                  reserved345;	//0xCC621A30
	UINT32                                                  reserved346;	//0xCC621A34
	UINT32                                                  reserved347;	//0xCC621A38
	UINT32                                                  reserved348;	//0xCC621A3C
	UINT32                                                  reserved349;	//0xCC621A40
	UINT32                                                  reserved350;	//0xCC621A44
	UINT32                                                  reserved351;	//0xCC621A48
	UINT32                                                  reserved352;	//0xCC621A4C
	UINT32                                                  reserved353;	//0xCC621A50
	UINT32                                                  reserved354;	//0xCC621A54
	UINT32                                                  reserved355;	//0xCC621A58
	UINT32                                                  reserved356;	//0xCC621A5C
	UINT32                                                  reserved357;	//0xCC621A60
	UINT32                                                  reserved358;	//0xCC621A64
	UINT32                                                  reserved359;	//0xCC621A68
	UINT32                                                  reserved360;	//0xCC621A6C
	UINT32                                                  reserved361;	//0xCC621A70
	UINT32                                                  reserved362;	//0xCC621A74
	UINT32                                                  reserved363;	//0xCC621A78
	UINT32                                                  reserved364;	//0xCC621A7C
	UINT32                                                  reserved365;	//0xCC621A80
	UINT32                                                  reserved366;	//0xCC621A84
	UINT32                                                  reserved367;	//0xCC621A88
	UINT32                                                  reserved368;	//0xCC621A8C
	UINT32                                                  reserved369;	//0xCC621A90
	UINT32                                                  reserved370;	//0xCC621A94
	UINT32                                                  reserved371;	//0xCC621A98
	UINT32                                                  reserved372;	//0xCC621A9C
	UINT32                                                  reserved373;	//0xCC621AA0
	UINT32                                                  reserved374;	//0xCC621AA4
	UINT32                                                  reserved375;	//0xCC621AA8
	UINT32                                                  reserved376;	//0xCC621AAC
	UINT32                                                  reserved377;	//0xCC621AB0
	UINT32                                                  reserved378;	//0xCC621AB4
	UINT32                                                  reserved379;	//0xCC621AB8
	UINT32                                                  reserved380;	//0xCC621ABC
	UINT32                                                  reserved381;	//0xCC621AC0
	UINT32                                                  reserved382;	//0xCC621AC4
	UINT32                                                  reserved383;	//0xCC621AC8
	UINT32                                                  reserved384;	//0xCC621ACC
	UINT32                                                  reserved385;	//0xCC621AD0
	UINT32                                                  reserved386;	//0xCC621AD4
	UINT32                                                  reserved387;	//0xCC621AD8
	UINT32                                                  reserved388;	//0xCC621ADC
	UINT32                                                  reserved389;	//0xCC621AE0
	UINT32                                                  reserved390;	//0xCC621AE4
	UINT32                                                  reserved391;	//0xCC621AE8
	UINT32                                                  reserved392;	//0xCC621AEC
	PE_O24_2K_SHC_FSW_CTRL_00_T                           shp_fsw_ctrl_00;	//0xCC621AF0
	PE_O24_2K_SHC_FSW_CTRL_01_T                           shp_fsw_ctrl_01;	//0xCC621AF4
	PE_O24_2K_SHC_FSW_CTRL_02_T                           shp_fsw_ctrl_02;	//0xCC621AF8
	PE_O24_2K_SHC_FSW_CTRL_03_T                           shp_fsw_ctrl_03;	//0xCC621AFC
}PE_SR_2K_SHC_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A00 RW 0x0800_ff00
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
}PE_O24_SR_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A04 RW 0x0870_0F00
	UINT32 reg_sr_merge_width               :16;	//(15:0,NA,3840) //input image width (default : 3840)
	UINT32 reg_sr_merge_height              :16;	//(31:16,NA,2160) //input image height (default : 2160)
	};
}PE_O24_SR_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A08 RW 0x0000_0000
	UINT32 reg_sr_merge_demo_start_pts_x0   :16;	//(15:0,NA,0) //window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_start_pts_y0   :16;	//(31:16,NA,0) //window start point (for demo mode)
	};
}PE_O24_SR_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A0C RW 0x007f_007f
	UINT32 reg_sr_merge_demo_end_pts_x1     :16;	//(15:0,NA,127) //window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_end_pts_y1     :16;	//(31:16,NA,127) //window end point (for demo mode)
	};
}PE_O24_SR_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A10 RW 0x0000_0000
	UINT32 reg_residual_blur_en             :1;	//(0:0,NA,0) //0 : spatial filter off - use input residual data	1 : spatial filter on - use spatial filter result
	UINT32 resvd                            :31;
	};
}PE_O24_SR_MERGE_SPATIAL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A14 RW 0x0002_4048
	UINT32 reg_residual_blur_filt_00        :4;	//(3:0,NA,8) //blur filter coefficient
	UINT32 reg_residual_blur_filt_01        :4;	//(7:4,NA,4) //blur filter coefficient
	UINT32 reg_residual_blur_filt_02        :4;	//(11:8,NA,0) //blur filter coefficient
	UINT32 reg_residual_blur_filt_10        :4;	//(15:12,NA,4) //blur filter coefficient
	UINT32 reg_residual_blur_filt_11        :4;	//(19:16,NA,2) //blur filter coefficient
	UINT32 reg_residual_blur_filt_12        :4;	//(23:20,NA,0) //blur filter coefficient
	UINT32 resvd                            :8;
	};
}PE_O24_SR_MERGE_SPATIAL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A20 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_mmd_tap_size                 :4;	//(7:4,NA,0) //mmd tap size	0 : 3x3	1 : 5x5
	UINT32 resvd1                           :24;
	};
}PE_O24_SR_MERGE_MMD_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A24 RW 0x1020_0800
	UINT32 reg_mmd_diff_lut_y0              :8;	//(7:0,NA,0) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x0              :8;	//(15:8,NA,8) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y1              :8;	//(23:16,NA,32) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x1              :8;	//(31:24,NA,16) //mmd diff lut x position
	};
}PE_O24_SR_MERGE_MMD_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A28 RW 0x3C10_2040
	UINT32 reg_mmd_diff_lut_y2              :8;	//(7:0,NA,64) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x2              :8;	//(15:8,NA,32) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y3              :8;	//(23:16,NA,16) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x3              :8;	//(31:24,NA,60) //mmd diff lut x position
	};
}PE_O24_SR_MERGE_MMD_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A2C RW 0x82FF_6EFF
	UINT32 reg_mmd_diff_lut_y4              :8;	//(7:0,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x4              :8;	//(15:8,NA,110) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y5              :8;	//(23:16,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x5              :8;	//(31:24,NA,130) //mmd diff lut x position
	};
}PE_O24_SR_MERGE_MMD_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A30 RW 0xAAFF_96FF
	UINT32 reg_mmd_diff_lut_y6              :8;	//(7:0,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x6              :8;	//(15:8,NA,150) //mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y7              :8;	//(23:16,NA,255) //mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x7              :8;	//(31:24,NA,170) //mmd diff lut x position
	};
}PE_O24_SR_MERGE_MMD_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A34 RW 0x2880_14C8
	UINT32 reg_ti_gain_lut_y0               :8;	//(7:0,NA,200) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x0               :8;	//(15:8,NA,20) //ti gain lut x position
	UINT32 reg_ti_gain_lut_y1               :8;	//(23:16,NA,128) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x1               :8;	//(31:24,NA,40) //ti gain lut x position
	};
}PE_O24_SR_MERGE_MMD_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A38 RW 0xA020_5040
	UINT32 reg_ti_gain_lut_y2               :8;	//(7:0,NA,64) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x2               :8;	//(15:8,NA,80) //ti gain lut x position
	UINT32 reg_ti_gain_lut_y3               :8;	//(23:16,NA,32) //ti gain lut y position
	UINT32 reg_ti_gain_lut_x3               :8;	//(31:24,NA,160) //ti gain lut x position
	};
}PE_O24_SR_MERGE_MMD_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A50 RW 0x0000_0003
	UINT32 reg_sobel_mode                   :4;	//(3:0,NA,3) //sobel mode selection 	0: 3x3 	1: 5x5	2: 7x7	3: (7x7 - 3x3) : (default)
	UINT32 resvd                            :28;
	};
}PE_O24_SR_MERGE_SOBEL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A54 RW 0x5014_0400
	UINT32 reg_sobel_lut_y0                 :8;	//(7:0,NA,0) //sobel lut y position
	UINT32 reg_sobel_lut_x0                 :8;	//(15:8,NA,4) //sobel lut x position
	UINT32 reg_sobel_lut_y1                 :8;	//(23:16,NA,20) //sobel lut y position
	UINT32 reg_sobel_lut_x1                 :8;	//(31:24,NA,80) //sobel lut x position
	};
}PE_O24_SR_MERGE_SOBEL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A58 RW 0xE6FF_C864
	UINT32 reg_sobel_lut_y2                 :8;	//(7:0,NA,100) //sobel lut y position
	UINT32 reg_sobel_lut_x2                 :8;	//(15:8,NA,200) //sobel lut x position
	UINT32 reg_sobel_lut_y3                 :8;	//(23:16,NA,255) //sobel lut y position
	UINT32 reg_sobel_lut_x3                 :8;	//(31:24,NA,230) //sobel lut x position
	};
}PE_O24_SR_MERGE_SOBEL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A70 RW 0x0000_0300
	UINT32 reg_nr_gain_en                   :1;	//(0:0,NA,0) //NR Gain enable
	UINT32 resvd0                           :3;
	UINT32 reg_nr_gain_th                   :10;	//(13:4,NA,48) //NR gain threshold
	UINT32 resvd1                           :18;
	};
}PE_O24_SR_MERGE_NR_GAIN_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A74 RW 0x2080_1019
	UINT32 reg_nr_gain_lut_y0               :8;	//(7:0,NA,25) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x0               :8;	//(15:8,NA,16) //nr_gain lut x position
	UINT32 reg_nr_gain_lut_y1               :8;	//(23:16,NA,128) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x1               :8;	//(31:24,NA,32) //nr_gain lut x position
	};
}PE_O24_SR_MERGE_NR_GAIN_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A78 RW 0x4000_3020
	UINT32 reg_nr_gain_lut_y2               :8;	//(7:0,NA,32) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x2               :8;	//(15:8,NA,48) //nr_gain lut x position
	UINT32 reg_nr_gain_lut_y3               :8;	//(23:16,NA,0) //nr_gain lut y position
	UINT32 reg_nr_gain_lut_x3               :8;	//(31:24,NA,64) //nr_gain lut x position
	};
}PE_O24_SR_MERGE_NR_GAIN_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A90 RW 0x0020_0021
	UINT32 reg_blend_lut_en                 :1;	//(0:0,NA,1) //blend lut en
	UINT32 resvd                            :19;
	UINT32 reg_blend_amp_weight             :12;	//(31:20,NA,32) //blend weight ('d16: x1, 'd32:x2)
	};
}PE_O24_SR_MERGE_BLEND_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A94 RW 0x0012_0012
	UINT32 reg_blend_lut_y1                 :10;	//(9:0,NA,18) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x1                 :10;	//(25:16,NA,18) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O24_SR_MERGE_BLEND_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A98 RW 0x0008_0008
	UINT32 reg_blend_lut_y0                 :10;	//(9:0,NA,8) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x0                 :10;	//(25:16,NA,8) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O24_SR_MERGE_BLEND_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622A9C RW 0x0080_0080
	UINT32 reg_blend_lut_y3                 :10;	//(9:0,NA,128) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x3                 :10;	//(25:16,NA,128) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O24_SR_MERGE_BLEND_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622AA0 RW 0x0020_0020
	UINT32 reg_blend_lut_y2                 :10;	//(9:0,NA,32) //blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x2                 :10;	//(25:16,NA,32) //blend lut x position
	UINT32 resvd1                           :6;
	};
}PE_O24_SR_MERGE_BLEND_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B00 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_SR_MERGE_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B04 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :16;	//(15:0,NA,0) //Input vertical counter
	UINT32 reg_mon_in_hori_cnt              :16;	//(31:16,NA,0) //Input horizontal counter
	};
}PE_O24_SR_MERGE_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B08 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :16;	//(15:0,NA,0) //Output vertical counter
	UINT32 reg_mon_out_hori_cnt             :16;	//(31:16,NA,0) //Output horizontal counter
	};
}PE_O24_SR_MERGE_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B0C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :16;	//(15:0,NA,0) //Output previous frame vertical counter
	UINT32 reg_mon_fin_in_vert_cnt          :16;	//(31:16,NA,0) //Input previous frame vertical counter
	};
}PE_O24_SR_MERGE_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B10 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O24_SR_MERGE_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B14 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O24_SR_MERGE_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B20 RW 0x0000_0000
	UINT32 reg_ellipse_ctrl_en              :1;	//(0:0,NA,0x0) //0: not use ellipse gain, 1 : use ellipse gain
	UINT32 resvd0                           :3;
	UINT32 reg_sel_output                   :1;	//(4:4,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_ellipse_offset               :8;	//(15:8,NA,0x0) //
	UINT32 resvd2                           :16;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B24 RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f0_enable                    :1;	//(24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B28 RW 0x0000_0000
	UINT32 reg_f0_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B2C RW 0x0000_0000
	UINT32 reg_f0_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f0_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f0_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B30 RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f1_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f1_enable                    :1;	//(24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B34 RW 0x0000_0000
	UINT32 reg_f1_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B38 RW 0x0000_0000
	UINT32 reg_f1_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f1_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f1_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B3C RW 0x0000_0000
	UINT32 reg_f2_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f2_enable                    :1;	//(24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B40 RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f2_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B44 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f2_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f2_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B48 RW 0x0000_0000
	UINT32 reg_f3_w1_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 reg_f3_enable                    :1;	//(24,NA,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B4C RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,NA,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B50 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_f3_e_mul_a                   :9;	//(20:12,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_f3_ellipse_master            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_SR_MERGE_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B54 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //
	};
}PE_O24_SR_MERGE_ELLIPSE_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B58 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //
	};
}PE_O24_SR_MERGE_ELLIPSE_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622B5C RW 0x0000_0000
	UINT32 reg_sm_blender_on_en             :1;	//(0:0,NA,0) //1 : motion on, 0 : motion off = output ready force 1
	UINT32 resvd0                           :3;
	UINT32 reg_sm_blender_en                :1;	//(4:4,NA,0) //1 : sm_blender output, 0, ori sr_merge_out
	UINT32 resvd1                           :27;
	};
}PE_O24_SR_MERGE_SM_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622BF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_SR_MERGE_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622BF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_SR_MERGE_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622BF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_SR_MERGE_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC622BFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_SR_MERGE_FSW_CTRL_03_T;

typedef struct {
	PE_O24_SR_MERGE_CTRL_00_T                     sr_merge_ctrl_00;	//0xCC622A00
	PE_O24_SR_MERGE_CTRL_01_T                     sr_merge_ctrl_01;	//0xCC622A04
	PE_O24_SR_MERGE_CTRL_02_T                     sr_merge_ctrl_02;	//0xCC622A08
	PE_O24_SR_MERGE_CTRL_03_T                     sr_merge_ctrl_03;	//0xCC622A0C
	PE_O24_SR_MERGE_SPATIAL_00_T               sr_merge_spatial_00;	//0xCC622A10
	PE_O24_SR_MERGE_SPATIAL_01_T               sr_merge_spatial_01;	//0xCC622A14
	UINT32                                                    reserved0;	//0xCC622A18
	UINT32                                                    reserved1;	//0xCC622A1C
	PE_O24_SR_MERGE_MMD_00_T                       sr_merge_mmd_00;	//0xCC622A20
	PE_O24_SR_MERGE_MMD_01_T                       sr_merge_mmd_01;	//0xCC622A24
	PE_O24_SR_MERGE_MMD_02_T                       sr_merge_mmd_02;	//0xCC622A28
	PE_O24_SR_MERGE_MMD_03_T                       sr_merge_mmd_03;	//0xCC622A2C
	PE_O24_SR_MERGE_MMD_04_T                       sr_merge_mmd_04;	//0xCC622A30
	PE_O24_SR_MERGE_MMD_05_T                       sr_merge_mmd_05;	//0xCC622A34
	PE_O24_SR_MERGE_MMD_06_T                       sr_merge_mmd_06;	//0xCC622A38
	UINT32                                                    reserved2;	//0xCC622A3C
	UINT32                                                    reserved3;	//0xCC622A40
	UINT32                                                    reserved4;	//0xCC622A44
	UINT32                                                    reserved5;	//0xCC622A48
	UINT32                                                    reserved6;	//0xCC622A4C
	PE_O24_SR_MERGE_SOBEL_00_T                   sr_merge_sobel_00;	//0xCC622A50
	PE_O24_SR_MERGE_SOBEL_01_T                   sr_merge_sobel_01;	//0xCC622A54
	PE_O24_SR_MERGE_SOBEL_02_T                   sr_merge_sobel_02;	//0xCC622A58
	UINT32                                                    reserved7;	//0xCC622A5C
	UINT32                                                    reserved8;	//0xCC622A60
	UINT32                                                    reserved9;	//0xCC622A64
	UINT32                                                   reserved10;	//0xCC622A68
	UINT32                                                   reserved11;	//0xCC622A6C
	PE_O24_SR_MERGE_NR_GAIN_00_T               sr_merge_nr_gain_00;	//0xCC622A70
	PE_O24_SR_MERGE_NR_GAIN_01_T               sr_merge_nr_gain_01;	//0xCC622A74
	PE_O24_SR_MERGE_NR_GAIN_02_T               sr_merge_nr_gain_02;	//0xCC622A78
	UINT32                                                   reserved12;	//0xCC622A7C
	UINT32                                                   reserved13;	//0xCC622A80
	UINT32                                                   reserved14;	//0xCC622A84
	UINT32                                                   reserved15;	//0xCC622A88
	UINT32                                                   reserved16;	//0xCC622A8C
	PE_O24_SR_MERGE_BLEND_00_T                   sr_merge_blend_00;	//0xCC622A90
	PE_O24_SR_MERGE_BLEND_01_T                   sr_merge_blend_01;	//0xCC622A94
	PE_O24_SR_MERGE_BLEND_02_T                   sr_merge_blend_02;	//0xCC622A98
	PE_O24_SR_MERGE_BLEND_03_T                   sr_merge_blend_03;	//0xCC622A9C
	PE_O24_SR_MERGE_BLEND_04_T                   sr_merge_blend_04;	//0xCC622AA0
	UINT32                                                   reserved17;	//0xCC622AA4
	UINT32                                                   reserved18;	//0xCC622AA8
	UINT32                                                   reserved19;	//0xCC622AAC
	UINT32                                                   reserved20;	//0xCC622AB0
	UINT32                                                   reserved21;	//0xCC622AB4
	UINT32                                                   reserved22;	//0xCC622AB8
	UINT32                                                   reserved23;	//0xCC622ABC
	UINT32                                                   reserved24;	//0xCC622AC0
	UINT32                                                   reserved25;	//0xCC622AC4
	UINT32                                                   reserved26;	//0xCC622AC8
	UINT32                                                   reserved27;	//0xCC622ACC
	UINT32                                                   reserved28;	//0xCC622AD0
	UINT32                                                   reserved29;	//0xCC622AD4
	UINT32                                                   reserved30;	//0xCC622AD8
	UINT32                                                   reserved31;	//0xCC622ADC
	UINT32                                                   reserved32;	//0xCC622AE0
	UINT32                                                   reserved33;	//0xCC622AE4
	UINT32                                                   reserved34;	//0xCC622AE8
	UINT32                                                   reserved35;	//0xCC622AEC
	UINT32                                                   reserved36;	//0xCC622AF0
	UINT32                                                   reserved37;	//0xCC622AF4
	UINT32                                                   reserved38;	//0xCC622AF8
	UINT32                                                   reserved39;	//0xCC622AFC
	PE_O24_SR_MERGE_CORE_STAT_00_T           sr_merge_core_stat_00;	//0xCC622B00
	PE_O24_SR_MERGE_CORE_STAT_01_T           sr_merge_core_stat_01;	//0xCC622B04
	PE_O24_SR_MERGE_CORE_STAT_02_T           sr_merge_core_stat_02;	//0xCC622B08
	PE_O24_SR_MERGE_CORE_STAT_03_T           sr_merge_core_stat_03;	//0xCC622B0C
	PE_O24_SR_MERGE_CORE_STAT_04_T           sr_merge_core_stat_04;	//0xCC622B10
	PE_O24_SR_MERGE_CORE_STAT_05_T           sr_merge_core_stat_05;	//0xCC622B14
	UINT32                                                   reserved40;	//0xCC622B18
	UINT32                                                   reserved41;	//0xCC622B1C
	PE_O24_SR_MERGE_ELLIPSE_CTRL_00_T     sr_merge_ellipse_ctrl_00;	//0xCC622B20
	PE_O24_SR_MERGE_ELLIPSE_CTRL_01_T     sr_merge_ellipse_ctrl_01;	//0xCC622B24
	PE_O24_SR_MERGE_ELLIPSE_CTRL_02_T     sr_merge_ellipse_ctrl_02;	//0xCC622B28
	PE_O24_SR_MERGE_ELLIPSE_CTRL_03_T     sr_merge_ellipse_ctrl_03;	//0xCC622B2C
	PE_O24_SR_MERGE_ELLIPSE_CTRL_04_T     sr_merge_ellipse_ctrl_04;	//0xCC622B30
	PE_O24_SR_MERGE_ELLIPSE_CTRL_05_T     sr_merge_ellipse_ctrl_05;	//0xCC622B34
	PE_O24_SR_MERGE_ELLIPSE_CTRL_06_T     sr_merge_ellipse_ctrl_06;	//0xCC622B38
	PE_O24_SR_MERGE_ELLIPSE_CTRL_07_T     sr_merge_ellipse_ctrl_07;	//0xCC622B3C
	PE_O24_SR_MERGE_ELLIPSE_CTRL_08_T     sr_merge_ellipse_ctrl_08;	//0xCC622B40
	PE_O24_SR_MERGE_ELLIPSE_CTRL_09_T     sr_merge_ellipse_ctrl_09;	//0xCC622B44
	PE_O24_SR_MERGE_ELLIPSE_CTRL_10_T     sr_merge_ellipse_ctrl_10;	//0xCC622B48
	PE_O24_SR_MERGE_ELLIPSE_CTRL_11_T     sr_merge_ellipse_ctrl_11;	//0xCC622B4C
	PE_O24_SR_MERGE_ELLIPSE_CTRL_12_T     sr_merge_ellipse_ctrl_12;	//0xCC622B50
	PE_O24_SR_MERGE_ELLIPSE_LUT_CTRL_00_T sr_merge_ellipse_lut_ctrl_00;	//0xCC622B54
	PE_O24_SR_MERGE_ELLIPSE_LUT_CTRL_01_T sr_merge_ellipse_lut_ctrl_01;	//0xCC622B58
	PE_O24_SR_MERGE_SM_BLEND_CTRL_00_T   sr_merge_sm_blend_ctrl_00;	//0xCC622B5C
	UINT32                                                   reserved42;	//0xCC622B60
	UINT32                                                   reserved43;	//0xCC622B64
	UINT32                                                   reserved44;	//0xCC622B68
	UINT32                                                   reserved45;	//0xCC622B6C
	UINT32                                                   reserved46;	//0xCC622B70
	UINT32                                                   reserved47;	//0xCC622B74
	UINT32                                                   reserved48;	//0xCC622B78
	UINT32                                                   reserved49;	//0xCC622B7C
	UINT32                                                   reserved50;	//0xCC622B80
	UINT32                                                   reserved51;	//0xCC622B84
	UINT32                                                   reserved52;	//0xCC622B88
	UINT32                                                   reserved53;	//0xCC622B8C
	UINT32                                                   reserved54;	//0xCC622B90
	UINT32                                                   reserved55;	//0xCC622B94
	UINT32                                                   reserved56;	//0xCC622B98
	UINT32                                                   reserved57;	//0xCC622B9C
	UINT32                                                   reserved58;	//0xCC622BA0
	UINT32                                                   reserved59;	//0xCC622BA4
	UINT32                                                   reserved60;	//0xCC622BA8
	UINT32                                                   reserved61;	//0xCC622BAC
	UINT32                                                   reserved62;	//0xCC622BB0
	UINT32                                                   reserved63;	//0xCC622BB4
	UINT32                                                   reserved64;	//0xCC622BB8
	UINT32                                                   reserved65;	//0xCC622BBC
	UINT32                                                   reserved66;	//0xCC622BC0
	UINT32                                                   reserved67;	//0xCC622BC4
	UINT32                                                   reserved68;	//0xCC622BC8
	UINT32                                                   reserved69;	//0xCC622BCC
	UINT32                                                   reserved70;	//0xCC622BD0
	UINT32                                                   reserved71;	//0xCC622BD4
	UINT32                                                   reserved72;	//0xCC622BD8
	UINT32                                                   reserved73;	//0xCC622BDC
	UINT32                                                   reserved74;	//0xCC622BE0
	UINT32                                                   reserved75;	//0xCC622BE4
	UINT32                                                   reserved76;	//0xCC622BE8
	UINT32                                                   reserved77;	//0xCC622BEC
	PE_O24_SR_MERGE_FSW_CTRL_00_T             sr_merge_fsw_ctrl_00;	//0xCC622BF0
	PE_O24_SR_MERGE_FSW_CTRL_01_T             sr_merge_fsw_ctrl_01;	//0xCC622BF4
	PE_O24_SR_MERGE_FSW_CTRL_02_T             sr_merge_fsw_ctrl_02;	//0xCC622BF8
	PE_O24_SR_MERGE_FSW_CTRL_03_T             sr_merge_fsw_ctrl_03;	//0xCC622BFC
}PE_SR_MERG_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825000 RW 0x0000_0020
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O24_GAV_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825004 RW 0x0438_0780
	UINT32 reg_top_width                    :12;	//(11:0,NA,1920) //processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//(27:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825008 RW 0x0118_0001
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_GAV_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82500C RW 0x00A9_0000
	UINT32 reg_top_prefetch_cnt             :12;	//(11:0,NA,0) //Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//(27:16,NA,169) //Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825040 RW 0x0000_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O24_GAV_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825060 RW 0x1000_0A05
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_GAIN_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8250F0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O24_GAV_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825100 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O24_GAV_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825104 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825108 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O24_GAV_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82510C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825110 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825114 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825118 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82511C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825120 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O24_GAV_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825124 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825128 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O24_GAV_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82512C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825130 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O24_GAV_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825134 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O24_GAV_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825138 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82513C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O24_GAV_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825140 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O24_GAV_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825144 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O24_GAV_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825148 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O24_GAV_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82514C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O24_GAV_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825150 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O24_GAV_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825154 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_O24_GAV_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825158 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O24_GAV_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825160 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O24_GAV_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825164 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O24_GAV_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825168 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O24_GAV_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82516C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O24_GAV_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825170 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O24_GAV_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825174 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O24_GAV_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825178 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O24_GAV_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82517C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O24_GAV_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825180 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O24_GAV_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825184 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_O24_GAV_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825188 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O24_GAV_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82518C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825190 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_GAV_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825194 RW 0x0000_F001
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251A0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 resvd                            :7;
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //local gain
	};
}PE_O24_GAV_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251A4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //gain balancing, x1
	};
}PE_O24_GAV_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251A8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //gain balancing, x3
	};
}PE_O24_GAV_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251AC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251B0 RW 0x0808_0101
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251C0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O24_GAV_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251C4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_O24_GAV_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251C8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O24_GAV_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251CC RW 0x0006_5008
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
}PE_O24_GAV_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251D0 RW 0x0000_0008
	UINT32 reg_derv_csft_gain               :6;	//(5:0,NA,8) //center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//(8:8,NA,0) //center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}PE_O24_GAV_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251D4 RW 0x0000_0000
	UINT32 reg_derv_gain_b                  :7;	//(6:0,NA,0) //gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//(14:8,NA,0) //gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}PE_O24_GAV_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251D8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O24_GAV_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251DC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O24_GAV_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251E0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O24_GAV_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251E4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O24_GAV_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251E8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O24_GAV_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251EC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O24_GAV_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251F0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O24_GAV_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251F4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O24_GAV_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251F8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O24_GAV_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8251FC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O24_GAV_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825200 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O24_GAV_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825204 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_O24_GAV_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825208 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O24_GAV_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82520C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825210 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_GAV_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825220 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O24_GAV_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825224 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O24_GAV_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825228 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82522C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_GAV_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825230 RW 0x1010_2014
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
}PE_O24_GAV_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825240 RW 0x8000_0011
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
}PE_O24_GAV_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825244 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //
	UINT32 resvd3                           :5;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825248 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//(21:16,NA,63) //
	UINT32 resvd1                           :10;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82524C RW 0x0000_48AB
	UINT32 reg_tgen_rand_x0                 :32;	//(31:0,NA,18603) //
	};
}PE_O24_GAV_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825254 RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio                :3;	//(2:0,NA,4) //
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//(13:8,NA,31) //
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //
	UINT32 resvd3                           :6;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825258 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //
	UINT32 resvd2                           :3;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82525C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825260 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825264 RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain           :5;	//(4:0,NA,31) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//(12:8,NA,31) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //
	UINT32 resvd2                           :2;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825268 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7                   :4;	//(3:0,NA,15) //
	UINT32 reg_tgen_gain6                   :4;	//(7:4,NA,15) //
	UINT32 reg_tgen_gain5                   :4;	//(11:8,NA,13) //
	UINT32 reg_tgen_gain4                   :4;	//(15:12,NA,12) //
	UINT32 reg_tgen_gain3                   :4;	//(19:16,NA,11) //
	UINT32 reg_tgen_gain2                   :4;	//(23:20,NA,10) //
	UINT32 reg_tgen_gain1                   :4;	//(27:24,NA,8) //
	UINT32 reg_tgen_gain0                   :4;	//(31:28,NA,4) //
	};
}PE_O24_GAV_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82526C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825270 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_GAV_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825274 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O24_GAV_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825280 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825284 RW 0x0FED_0F99
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825288 RW 0x025B_0046
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82528C RW 0x002B_0FF1
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825290 RW 0x0FDC_0FE1
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825294 RW 0x0F68_0050
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825298 RW 0x04DD_0EA8
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82529C RW 0x0FB1_0F17
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252A0 RW 0x0FF8_0002
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252A4 RW 0x0F63_0059
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252A8 RW 0x04FE_0E92
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252AC RW 0x0FAE_0F08
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252B0 RW 0x0FFA_0004
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252B4 RW 0x0F58_0063
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252B8 RW 0x0516_0E86
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252BC RW 0x0FA9_0F00
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252C0 RW 0x0FFA_0007
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252C4 RW 0x0F68_0050
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252C8 RW 0x04DD_0EA8
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252CC RW 0x0FB1_0F17
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252D0 RW 0x0FF8_0002
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252D4 RW 0x0FB5_0005
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252D8 RW 0x0394_0F62
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252DC RW 0x0FD7_0F93
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252E0 RW 0x0FF3_0FF4
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252E4 RW 0x8040_2000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252E8 RW 0x0000_FFC4
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252EC RW 0x4040_2080
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252F0 RW 0xC000_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252F4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252F8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8252FC RW 0x1010_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825300 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825304 RW 0x0000_2B38
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825308 RW 0xBDE6_E338
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82530C RW 0xD9F2_01CB
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825310 RW 0x1598_773A
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825314 RW 0x82D2_8A5C
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82532C RW 0x00FF_308C
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825330 RW 0x0E12_0145
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825334 RW 0x01E0_0FEE
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825338 RW 0x0E11_011E
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82533C RW 0x0220_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825340 RW 0x0880_0460
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825344 RW 0x4090_20FF
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825348 RW 0xA400_8040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82534C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O24_GAV_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825350 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825354 RW 0x1010_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825360 RW 0x0000_0080
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O24_GAV_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825364 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_O24_GAV_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825368 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_O24_GAV_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253A0 RW 0x0000_0000
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
}PE_O24_GAV_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253A8 RW 0x0437_077F
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,1919) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,1079) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253B0 RW 0x0437_077F
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,1919) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,1079) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253C0 RW 0x0432_0c40
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253C4 RW 0x0f50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //region texture LUT , x1
	};
}PE_O24_GAV_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253C8 RW 0x46c8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //region texture LUT , x3
	};
}PE_O24_GAV_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253CC RW 0x0000_ff00
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253D0 RW 0x2840_0a00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //tmap temporal previous blend LUT , x1
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253D4 RW 0x5080_3c60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //tmap temporal previous blend LUT , x3
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253D8 RW 0x08d0_00c0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253DC RW 0x30f0_10e0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253E0 RW 0x80c0_60d0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253E4 RW 0x0870_0080
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253E8 RW 0x1850_1060
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253EC RW 0x4000_2040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253F4 RW 0x086f_077f
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253F8 RW 0x0000_0780
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8253FC RW 0x0438_0eff
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825400 RW 0x8010_0179
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
}PE_O24_GAV_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825404 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O24_GAV_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825408 RW 0x0000_1010
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82540C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O24_GAV_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825410 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825414 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825418 RW 0x0000_0040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82541C RW 0x0015_5550
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825420 RW 0x0000_0040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825424 RW 0x002A_A040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825428 RW 0x002A_A040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82542C RW 0x000A_A040
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825430 RW 0x0000_00E4
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825434 RW 0x0000_5540
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825438 RW 0x0020_5542
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82543C RW 0x0008_1508
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
}PE_O24_GAV_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825440 RW 0x0002_0420
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
}PE_O24_GAV_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825444 RW 0x0000_8080
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825448 RW 0x0000_2A00
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82544C RW 0x0000_2A00
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825450 RW 0x0000_0008
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825454 RW 0x0000_2800
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825458 RW 0x0005_0A00
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82545C RW 0x0005_4280
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825460 RW 0x0005_50A0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825464 RW 0x0005_4280
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825468 RW 0x0005_0A00
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82546C RW 0x0000_2800
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825470 RW 0x0000_0004
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825474 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O24_GAV_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825478 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}

PE_O24_GAV_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82547C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}

PE_O24_GAV_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825480 RW 0x0001_1400
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825490 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825494 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254A8 RW 0x0437_077F
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254AC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254B0 RW 0x0437_077F
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254C0 RW 0x10BC_4DB3
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254C4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254C8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254CC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254D0 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254D4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254D8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254DC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254E0 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254E4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254E8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254EC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254F0 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254F4 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254F8 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8254FC RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825500 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825600 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825604 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825608 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82560C RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_GAV_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825610 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O24_GAV_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825614 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O24_GAV_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825660 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825664 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825668 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82566C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825700 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825704 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825708 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82570C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825710 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825714 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825718 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82571C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8257F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8257F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8257F8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8257FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_GAV_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O24_GAV_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCC825000
	PE_O24_GAV_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCC825004
	PE_O24_GAV_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCC825008
	PE_O24_GAV_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCC82500C
	UINT32                                                    reserved0;	//0xCC825010
	UINT32                                                    reserved1;	//0xCC825014
	UINT32                                                    reserved2;	//0xCC825018
	UINT32                                                    reserved3;	//0xCC82501C
	UINT32                                                    reserved4;	//0xCC825020
	UINT32                                                    reserved5;	//0xCC825024
	UINT32                                                    reserved6;	//0xCC825028
	UINT32                                                    reserved7;	//0xCC82502C
	UINT32                                                    reserved8;	//0xCC825030
	UINT32                                                    reserved9;	//0xCC825034
	UINT32                                                   reserved10;	//0xCC825038
	UINT32                                                   reserved11;	//0xCC82503C
	PE_O24_GAV_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCC825040
	UINT32                                                   reserved12;	//0xCC825044
	UINT32                                                   reserved13;	//0xCC825048
	UINT32                                                   reserved14;	//0xCC82504C
	UINT32                                                   reserved15;	//0xCC825050
	UINT32                                                   reserved16;	//0xCC825054
	UINT32                                                   reserved17;	//0xCC825058
	UINT32                                                   reserved18;	//0xCC82505C
	PE_O24_GAV_SHP_GAIN_MAP_CTRL_00_T             shp_gain_map_ctrl_00;	//0xCC825060
	UINT32                                                   reserved19;	//0xCC825064
	UINT32                                                   reserved20;	//0xCC825068
	UINT32                                                   reserved21;	//0xCC82506C
	UINT32                                                   reserved22;	//0xCC825070
	UINT32                                                   reserved23;	//0xCC825074
	UINT32                                                   reserved24;	//0xCC825078
	UINT32                                                   reserved25;	//0xCC82507C
	UINT32                                                   reserved26;	//0xCC825080
	UINT32                                                   reserved27;	//0xCC825084
	UINT32                                                   reserved28;	//0xCC825088
	UINT32                                                   reserved29;	//0xCC82508C
	UINT32                                                   reserved30;	//0xCC825090
	UINT32                                                   reserved31;	//0xCC825094
	UINT32                                                   reserved32;	//0xCC825098
	UINT32                                                   reserved33;	//0xCC82509C
	UINT32                                                   reserved34;	//0xCC8250A0
	UINT32                                                   reserved35;	//0xCC8250A4
	UINT32                                                   reserved36;	//0xCC8250A8
	UINT32                                                   reserved37;	//0xCC8250AC
	UINT32                                                   reserved38;	//0xCC8250B0
	UINT32                                                   reserved39;	//0xCC8250B4
	UINT32                                                   reserved40;	//0xCC8250B8
	UINT32                                                   reserved41;	//0xCC8250BC
	UINT32                                                   reserved42;	//0xCC8250C0
	UINT32                                                   reserved43;	//0xCC8250C4
	UINT32                                                   reserved44;	//0xCC8250C8
	UINT32                                                   reserved45;	//0xCC8250CC
	UINT32                                                   reserved46;	//0xCC8250D0
	UINT32                                                   reserved47;	//0xCC8250D4
	UINT32                                                   reserved48;	//0xCC8250D8
	UINT32                                                   reserved49;	//0xCC8250DC
	UINT32                                                   reserved50;	//0xCC8250E0
	UINT32                                                   reserved51;	//0xCC8250E4
	UINT32                                                   reserved52;	//0xCC8250E8
	UINT32                                                   reserved53;	//0xCC8250EC
	PE_O24_GAV_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCC8250F0
	UINT32                                                   reserved54;	//0xCC8250F4
	UINT32                                                   reserved55;	//0xCC8250F8
	UINT32                                                   reserved56;	//0xCC8250FC
	PE_O24_GAV_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCC825100
	PE_O24_GAV_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCC825104
	PE_O24_GAV_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCC825108
	PE_O24_GAV_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCC82510C
	PE_O24_GAV_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCC825110
	PE_O24_GAV_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCC825114
	PE_O24_GAV_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCC825118
	PE_O24_GAV_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCC82511C
	PE_O24_GAV_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCC825120
	PE_O24_GAV_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCC825124
	PE_O24_GAV_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCC825128
	PE_O24_GAV_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCC82512C
	PE_O24_GAV_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCC825130
	PE_O24_GAV_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCC825134
	PE_O24_GAV_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCC825138
	PE_O24_GAV_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCC82513C
	PE_O24_GAV_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCC825140
	PE_O24_GAV_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCC825144
	PE_O24_GAV_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCC825148
	PE_O24_GAV_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCC82514C
	PE_O24_GAV_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCC825150
	PE_O24_GAV_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCC825154
	PE_O24_GAV_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCC825158
	UINT32                                                   reserved57;	//0xCC82515C
	PE_O24_GAV_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCC825160
	PE_O24_GAV_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCC825164
	PE_O24_GAV_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCC825168
	PE_O24_GAV_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCC82516C
	PE_O24_GAV_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCC825170
	PE_O24_GAV_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCC825174
	PE_O24_GAV_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCC825178
	PE_O24_GAV_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCC82517C
	PE_O24_GAV_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCC825180
	PE_O24_GAV_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCC825184
	PE_O24_GAV_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCC825188
	PE_O24_GAV_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCC82518C
	PE_O24_GAV_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCC825190
	PE_O24_GAV_SHP_APL_CTRL_00_T                       shp_apl_ctrl_00;	//0xCC825194
	UINT32                                                   reserved58;	//0xCC825198
	UINT32                                                   reserved59;	//0xCC82519C
	PE_O24_GAV_SHP_LC_CTRL_00_T                         shp_lc_ctrl_00;	//0xCC8251A0
	PE_O24_GAV_SHP_LC_CTRL_01_T                         shp_lc_ctrl_01;	//0xCC8251A4
	PE_O24_GAV_SHP_LC_CTRL_02_T                         shp_lc_ctrl_02;	//0xCC8251A8
	PE_O24_GAV_SHP_LC_CTRL_03_T                         shp_lc_ctrl_03;	//0xCC8251AC
	PE_O24_GAV_SHP_LC_CTRL_04_T                         shp_lc_ctrl_04;	//0xCC8251B0
	UINT32                                                   reserved60;	//0xCC8251B4
	UINT32                                                   reserved61;	//0xCC8251B8
	UINT32                                                   reserved62;	//0xCC8251BC
	PE_O24_GAV_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCC8251C0
	PE_O24_GAV_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCC8251C4
	PE_O24_GAV_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCC8251C8
	PE_O24_GAV_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCC8251CC
	PE_O24_GAV_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCC8251D0
	PE_O24_GAV_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCC8251D4
	PE_O24_GAV_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCC8251D8
	PE_O24_GAV_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCC8251DC
	PE_O24_GAV_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCC8251E0
	PE_O24_GAV_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCC8251E4
	PE_O24_GAV_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCC8251E8
	PE_O24_GAV_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCC8251EC
	PE_O24_GAV_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCC8251F0
	PE_O24_GAV_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCC8251F4
	PE_O24_GAV_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCC8251F8
	PE_O24_GAV_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCC8251FC
	PE_O24_GAV_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCC825200
	PE_O24_GAV_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCC825204
	PE_O24_GAV_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCC825208
	PE_O24_GAV_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCC82520C
	PE_O24_GAV_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCC825210
	UINT32                                                   reserved63;	//0xCC825214
	UINT32                                                   reserved64;	//0xCC825218
	UINT32                                                   reserved65;	//0xCC82521C
	PE_O24_GAV_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCC825220
	PE_O24_GAV_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCC825224
	PE_O24_GAV_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCC825228
	PE_O24_GAV_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCC82522C
	PE_O24_GAV_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCC825230
	UINT32                                                   reserved66;	//0xCC825234
	UINT32                                                   reserved67;	//0xCC825238
	UINT32                                                   reserved68;	//0xCC82523C
	PE_O24_GAV_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCC825240
	PE_O24_GAV_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCC825244
	PE_O24_GAV_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCC825248
	PE_O24_GAV_SHP_TGEN_CTRL_03_T                     shp_tgen_ctrl_03;	//0xCC82524C
	UINT32                                                   reserved69;	//0xCC825250
	PE_O24_GAV_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCC825254
	PE_O24_GAV_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCC825258
	PE_O24_GAV_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCC82525C
	PE_O24_GAV_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCC825260
	PE_O24_GAV_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCC825264
	PE_O24_GAV_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCC825268
	PE_O24_GAV_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCC82526C
	PE_O24_GAV_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCC825270
	PE_O24_GAV_SHP_SNR_CTRL_00_T                       shp_snr_ctrl_00;	//0xCC825274
	UINT32                                                   reserved70;	//0xCC825278
	UINT32                                                   reserved71;	//0xCC82527C
	PE_O24_GAV_SHP_DCTP_CTRL_00_T                     shp_dctp_ctrl_00;	//0xCC825280
	PE_O24_GAV_SHP_DCTP_CTRL_01_T                     shp_dctp_ctrl_01;	//0xCC825284
	PE_O24_GAV_SHP_DCTP_CTRL_02_T                     shp_dctp_ctrl_02;	//0xCC825288
	PE_O24_GAV_SHP_DCTP_CTRL_03_T                     shp_dctp_ctrl_03;	//0xCC82528C
	PE_O24_GAV_SHP_DCTP_CTRL_04_T                     shp_dctp_ctrl_04;	//0xCC825290
	PE_O24_GAV_SHP_DCTP_CTRL_05_T                     shp_dctp_ctrl_05;	//0xCC825294
	PE_O24_GAV_SHP_DCTP_CTRL_06_T                     shp_dctp_ctrl_06;	//0xCC825298
	PE_O24_GAV_SHP_DCTP_CTRL_07_T                     shp_dctp_ctrl_07;	//0xCC82529C
	PE_O24_GAV_SHP_DCTP_CTRL_08_T                     shp_dctp_ctrl_08;	//0xCC8252A0
	PE_O24_GAV_SHP_DCTP_CTRL_09_T                     shp_dctp_ctrl_09;	//0xCC8252A4
	PE_O24_GAV_SHP_DCTP_CTRL_0A_T                     shp_dctp_ctrl_0a;	//0xCC8252A8
	PE_O24_GAV_SHP_DCTP_CTRL_0B_T                     shp_dctp_ctrl_0b;	//0xCC8252AC
	PE_O24_GAV_SHP_DCTP_CTRL_0C_T                     shp_dctp_ctrl_0c;	//0xCC8252B0
	PE_O24_GAV_SHP_DCTP_CTRL_0D_T                     shp_dctp_ctrl_0d;	//0xCC8252B4
	PE_O24_GAV_SHP_DCTP_CTRL_0E_T                     shp_dctp_ctrl_0e;	//0xCC8252B8
	PE_O24_GAV_SHP_DCTP_CTRL_0F_T                     shp_dctp_ctrl_0f;	//0xCC8252BC
	PE_O24_GAV_SHP_DCTP_CTRL_10_T                     shp_dctp_ctrl_10;	//0xCC8252C0
	PE_O24_GAV_SHP_DCTP_CTRL_11_T                     shp_dctp_ctrl_11;	//0xCC8252C4
	PE_O24_GAV_SHP_DCTP_CTRL_12_T                     shp_dctp_ctrl_12;	//0xCC8252C8
	PE_O24_GAV_SHP_DCTP_CTRL_13_T                     shp_dctp_ctrl_13;	//0xCC8252CC
	PE_O24_GAV_SHP_DCTP_CTRL_14_T                     shp_dctp_ctrl_14;	//0xCC8252D0
	PE_O24_GAV_SHP_DCTP_CTRL_15_T                     shp_dctp_ctrl_15;	//0xCC8252D4
	PE_O24_GAV_SHP_DCTP_CTRL_16_T                     shp_dctp_ctrl_16;	//0xCC8252D8
	PE_O24_GAV_SHP_DCTP_CTRL_17_T                     shp_dctp_ctrl_17;	//0xCC8252DC
	PE_O24_GAV_SHP_DCTP_CTRL_18_T                     shp_dctp_ctrl_18;	//0xCC8252E0
	PE_O24_GAV_SHP_DCTP_CTRL_19_T                     shp_dctp_ctrl_19;	//0xCC8252E4
	PE_O24_GAV_SHP_DCTP_CTRL_1A_T                     shp_dctp_ctrl_1a;	//0xCC8252E8
	PE_O24_GAV_SHP_DCTP_CTRL_1B_T                     shp_dctp_ctrl_1b;	//0xCC8252EC
	PE_O24_GAV_SHP_DCTP_CTRL_1C_T                     shp_dctp_ctrl_1c;	//0xCC8252F0
	PE_O24_GAV_SHP_DCTP_CTRL_1D_T                     shp_dctp_ctrl_1d;	//0xCC8252F4
	PE_O24_GAV_SHP_DCTP_CTRL_1E_T                     shp_dctp_ctrl_1e;	//0xCC8252F8
	PE_O24_GAV_SHP_DCTP_CTRL_1F_T                     shp_dctp_ctrl_1f;	//0xCC8252FC
	PE_O24_GAV_SHP_NNTG_CTRL_00_T                     shp_nntg_ctrl_00;	//0xCC825300
	PE_O24_GAV_SHP_NNTG_CTRL_01_T                     shp_nntg_ctrl_01;	//0xCC825304
	PE_O24_GAV_SHP_NNTG_CTRL_02_T                     shp_nntg_ctrl_02;	//0xCC825308
	PE_O24_GAV_SHP_NNTG_CTRL_03_T                     shp_nntg_ctrl_03;	//0xCC82530C
	PE_O24_GAV_SHP_NNTG_CTRL_04_T                     shp_nntg_ctrl_04;	//0xCC825310
	PE_O24_GAV_SHP_NNTG_CTRL_05_T                     shp_nntg_ctrl_05;	//0xCC825314
	UINT32                                                   reserved72;	//0xCC825318
	UINT32                                                   reserved73;	//0xCC82531C
	UINT32                                                   reserved74;	//0xCC825320
	UINT32                                                   reserved75;	//0xCC825324
	UINT32                                                   reserved76;	//0xCC825328
	PE_O24_GAV_SHP_NNTG_CTRL_06_T                     shp_nntg_ctrl_06;	//0xCC82532C
	PE_O24_GAV_SHP_NNTG_CTRL_07_T                     shp_nntg_ctrl_07;	//0xCC825330
	PE_O24_GAV_SHP_NNTG_CTRL_08_T                     shp_nntg_ctrl_08;	//0xCC825334
	PE_O24_GAV_SHP_NNTG_CTRL_09_T                     shp_nntg_ctrl_09;	//0xCC825338
	PE_O24_GAV_SHP_NNTG_CTRL_0A_T                     shp_nntg_ctrl_0a;	//0xCC82533C
	PE_O24_GAV_SHP_NNTG_CTRL_0B_T                     shp_nntg_ctrl_0b;	//0xCC825340
	PE_O24_GAV_SHP_NNTG_CTRL_0C_T                     shp_nntg_ctrl_0c;	//0xCC825344
	PE_O24_GAV_SHP_NNTG_CTRL_0D_T                     shp_nntg_ctrl_0d;	//0xCC825348
	PE_O24_GAV_SHP_NNTG_CTRL_0E_T                     shp_nntg_ctrl_0e;	//0xCC82534C
	PE_O24_GAV_SHP_NNTG_CTRL_0F_T                     shp_nntg_ctrl_0f;	//0xCC825350
	PE_O24_GAV_SHP_NNTG_CTRL_10_T                     shp_nntg_ctrl_10;	//0xCC825354
	UINT32                                                   reserved77;	//0xCC825358
	UINT32                                                   reserved78;	//0xCC82535C
	PE_O24_GAV_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCC825360
	PE_O24_GAV_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCC825364
	PE_O24_GAV_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCC825368
	UINT32                                                   reserved79;	//0xCC82536C
	UINT32                                                   reserved80;	//0xCC825370
	UINT32                                                   reserved81;	//0xCC825374
	UINT32                                                   reserved82;	//0xCC825378
	UINT32                                                   reserved83;	//0xCC82537C
	UINT32                                                   reserved84;	//0xCC825380
	UINT32                                                   reserved85;	//0xCC825384
	UINT32                                                   reserved86;	//0xCC825388
	UINT32                                                   reserved87;	//0xCC82538C
	UINT32                                                   reserved88;	//0xCC825390
	UINT32                                                   reserved89;	//0xCC825394
	UINT32                                                   reserved90;	//0xCC825398
	UINT32                                                   reserved91;	//0xCC82539C
	PE_O24_GAV_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCC8253A0
	PE_O24_GAV_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCC8253A4
	PE_O24_GAV_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCC8253A8
	PE_O24_GAV_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCC8253AC
	PE_O24_GAV_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCC8253B0
	UINT32                                                   reserved92;	//0xCC8253B4
	UINT32                                                   reserved93;	//0xCC8253B8
	UINT32                                                   reserved94;	//0xCC8253BC
	PE_O24_GAV_SHP_FD_REGION_TEXT_00_T           shp_fd_region_text_00;	//0xCC8253C0
	PE_O24_GAV_SHP_FD_REGION_TEXT_01_T           shp_fd_region_text_01;	//0xCC8253C4
	PE_O24_GAV_SHP_FD_REGION_TEXT_02_T           shp_fd_region_text_02;	//0xCC8253C8
	PE_O24_GAV_SHP_FD_TMAP_TEMP_00_T               shp_fd_tmap_temp_00;	//0xCC8253CC
	PE_O24_GAV_SHP_FD_TMAP_TEMP_01_T               shp_fd_tmap_temp_01;	//0xCC8253D0
	PE_O24_GAV_SHP_FD_TMAP_TEMP_02_T               shp_fd_tmap_temp_02;	//0xCC8253D4
	PE_O24_GAV_SHP_FD_TMAP_TEMP_03_T               shp_fd_tmap_temp_03;	//0xCC8253D8
	PE_O24_GAV_SHP_FD_TMAP_TEMP_04_T               shp_fd_tmap_temp_04;	//0xCC8253DC
	PE_O24_GAV_SHP_FD_TMAP_TEMP_05_T               shp_fd_tmap_temp_05;	//0xCC8253E0
	PE_O24_GAV_SHP_FD_TMAP_TEMP_06_T               shp_fd_tmap_temp_06;	//0xCC8253E4
	PE_O24_GAV_SHP_FD_TMAP_TEMP_07_T               shp_fd_tmap_temp_07;	//0xCC8253E8
	PE_O24_GAV_SHP_FD_TMAP_TEMP_08_T               shp_fd_tmap_temp_08;	//0xCC8253EC
	PE_O24_GAV_SHP_FD_TMAP_TEMP_09_T               shp_fd_tmap_temp_09;	//0xCC8253F0
	PE_O24_GAV_SHP_FD_TMAP_TEMP_0A_T               shp_fd_tmap_temp_0a;	//0xCC8253F4
	PE_O24_GAV_SHP_FD_TMAP_TEMP_0B_T               shp_fd_tmap_temp_0b;	//0xCC8253F8
	PE_O24_GAV_SHP_FD_TMAP_TEMP_0C_T               shp_fd_tmap_temp_0c;	//0xCC8253FC
	PE_O24_GAV_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0xCC825400
	PE_O24_GAV_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0xCC825404
	PE_O24_GAV_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0xCC825408
	PE_O24_GAV_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0xCC82540C
	PE_O24_GAV_SHP_DJ_CTRL_04_T                         shp_dj_ctrl_04;	//0xCC825410
	PE_O24_GAV_SHP_DJ_CTRL_05_T                         shp_dj_ctrl_05;	//0xCC825414
	PE_O24_GAV_SHP_DJ_CTRL_06_T                         shp_dj_ctrl_06;	//0xCC825418
	PE_O24_GAV_SHP_DJ_CTRL_07_T                         shp_dj_ctrl_07;	//0xCC82541C
	PE_O24_GAV_SHP_DJ_CTRL_08_T                         shp_dj_ctrl_08;	//0xCC825420
	PE_O24_GAV_SHP_DJ_CTRL_09_T                         shp_dj_ctrl_09;	//0xCC825424
	PE_O24_GAV_SHP_DJ_CTRL_0A_T                         shp_dj_ctrl_0a;	//0xCC825428
	PE_O24_GAV_SHP_DJ_CTRL_0B_T                         shp_dj_ctrl_0b;	//0xCC82542C
	PE_O24_GAV_SHP_DJ_CTRL_0C_T                         shp_dj_ctrl_0c;	//0xCC825430
	PE_O24_GAV_SHP_DJ_CTRL_0D_T                         shp_dj_ctrl_0d;	//0xCC825434
	PE_O24_GAV_SHP_DJ_CTRL_0E_T                         shp_dj_ctrl_0e;	//0xCC825438
	PE_O24_GAV_SHP_DJ_CTRL_0F_T                         shp_dj_ctrl_0f;	//0xCC82543C
	PE_O24_GAV_SHP_DJ_CTRL_10_T                         shp_dj_ctrl_10;	//0xCC825440
	PE_O24_GAV_SHP_DJ_CTRL_11_T                         shp_dj_ctrl_11;	//0xCC825444
	PE_O24_GAV_SHP_DJ_CTRL_12_T                         shp_dj_ctrl_12;	//0xCC825448
	PE_O24_GAV_SHP_DJ_CTRL_13_T                         shp_dj_ctrl_13;	//0xCC82544C
	PE_O24_GAV_SHP_DJ_CTRL_14_T                         shp_dj_ctrl_14;	//0xCC825450
	PE_O24_GAV_SHP_DJ_CTRL_15_T                         shp_dj_ctrl_15;	//0xCC825454
	PE_O24_GAV_SHP_DJ_CTRL_16_T                         shp_dj_ctrl_16;	//0xCC825458
	PE_O24_GAV_SHP_DJ_CTRL_17_T                         shp_dj_ctrl_17;	//0xCC82545C
	PE_O24_GAV_SHP_DJ_CTRL_18_T                         shp_dj_ctrl_18;	//0xCC825460
	PE_O24_GAV_SHP_DJ_CTRL_19_T                         shp_dj_ctrl_19;	//0xCC825464
	PE_O24_GAV_SHP_DJ_CTRL_1A_T                         shp_dj_ctrl_1a;	//0xCC825468
	PE_O24_GAV_SHP_DJ_CTRL_1B_T                         shp_dj_ctrl_1b;	//0xCC82546C
	PE_O24_GAV_SHP_DJ_CTRL_1C_T                         shp_dj_ctrl_1c;	//0xCC825470
	PE_O24_GAV_SHP_DJ_CTRL_1D_T                         shp_dj_ctrl_1d;	//0xCC825474
	PE_O24_GAV_SHP_DJ_CTRL_1E_T                         shp_dj_ctrl_1e;	//0xCC825478
	PE_O24_GAV_SHP_DJ_CTRL_1F_T                         shp_dj_ctrl_1f;	//0xCC82547C
	PE_O24_GAV_SHP_DJ_CTRL_20_T                         shp_dj_ctrl_20;	//0xCC825480
	UINT32                                                   reserved95;	//0xCC825484
	UINT32                                                   reserved96;	//0xCC825488
	UINT32                                                   reserved97;	//0xCC82548C
	PE_O24_GAV_SHP_DB_CTRL_00_T                         shp_db_ctrl_00;	//0xCC825490
	PE_O24_GAV_SHP_DB_CTRL_01_T                         shp_db_ctrl_01;	//0xCC825494
	UINT32                                                   reserved98;	//0xCC825498
	UINT32                                                   reserved99;	//0xCC82549C
	PE_O24_GAV_SHP_DJ_WIN_CTRL_00_T                 shp_dj_win_ctrl_00;	//0xCC8254A0
	PE_O24_GAV_SHP_DJ_WIN_CTRL_01_T                 shp_dj_win_ctrl_01;	//0xCC8254A4
	PE_O24_GAV_SHP_DJ_WIN_CTRL_02_T                 shp_dj_win_ctrl_02;	//0xCC8254A8
	PE_O24_GAV_SHP_DJ_WIN_CTRL_03_T                 shp_dj_win_ctrl_03;	//0xCC8254AC
	PE_O24_GAV_SHP_DJ_WIN_CTRL_04_T                 shp_dj_win_ctrl_04;	//0xCC8254B0
	UINT32                                                  reserved100;	//0xCC8254B4
	UINT32                                                  reserved101;	//0xCC8254B8
	UINT32                                                  reserved102;	//0xCC8254BC
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_00_T     shp_dj_text_gain_ctrl_00;	//0xCC8254C0
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_01_T     shp_dj_text_gain_ctrl_01;	//0xCC8254C4
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_02_T     shp_dj_text_gain_ctrl_02;	//0xCC8254C8
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_03_T     shp_dj_text_gain_ctrl_03;	//0xCC8254CC
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_04_T     shp_dj_text_gain_ctrl_04;	//0xCC8254D0
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_05_T     shp_dj_text_gain_ctrl_05;	//0xCC8254D4
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_06_T     shp_dj_text_gain_ctrl_06;	//0xCC8254D8
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_07_T     shp_dj_text_gain_ctrl_07;	//0xCC8254DC
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_08_T     shp_dj_text_gain_ctrl_08;	//0xCC8254E0
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_09_T     shp_dj_text_gain_ctrl_09;	//0xCC8254E4
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_10_T     shp_dj_text_gain_ctrl_10;	//0xCC8254E8
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_11_T     shp_dj_text_gain_ctrl_11;	//0xCC8254EC
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_12_T     shp_dj_text_gain_ctrl_12;	//0xCC8254F0
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_13_T     shp_dj_text_gain_ctrl_13;	//0xCC8254F4
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_14_T     shp_dj_text_gain_ctrl_14;	//0xCC8254F8
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_15_T     shp_dj_text_gain_ctrl_15;	//0xCC8254FC
	PE_O24_GAV_SHP_DJ_TEXT_GAIN_CTRL_16_T     shp_dj_text_gain_ctrl_16;	//0xCC825500
	UINT32                                                  reserved103;	//0xCC825504
	UINT32                                                  reserved104;	//0xCC825508
	UINT32                                                  reserved105;	//0xCC82550C
	UINT32                                                  reserved106;	//0xCC825510
	UINT32                                                  reserved107;	//0xCC825514
	UINT32                                                  reserved108;	//0xCC825518
	UINT32                                                  reserved109;	//0xCC82551C
	UINT32                                                  reserved110;	//0xCC825520
	UINT32                                                  reserved111;	//0xCC825524
	UINT32                                                  reserved112;	//0xCC825528
	UINT32                                                  reserved113;	//0xCC82552C
	UINT32                                                  reserved114;	//0xCC825530
	UINT32                                                  reserved115;	//0xCC825534
	UINT32                                                  reserved116;	//0xCC825538
	UINT32                                                  reserved117;	//0xCC82553C
	UINT32                                                  reserved118;	//0xCC825540
	UINT32                                                  reserved119;	//0xCC825544
	UINT32                                                  reserved120;	//0xCC825548
	UINT32                                                  reserved121;	//0xCC82554C
	UINT32                                                  reserved122;	//0xCC825550
	UINT32                                                  reserved123;	//0xCC825554
	UINT32                                                  reserved124;	//0xCC825558
	UINT32                                                  reserved125;	//0xCC82555C
	UINT32                                                  reserved126;	//0xCC825560
	UINT32                                                  reserved127;	//0xCC825564
	UINT32                                                  reserved128;	//0xCC825568
	UINT32                                                  reserved129;	//0xCC82556C
	UINT32                                                  reserved130;	//0xCC825570
	UINT32                                                  reserved131;	//0xCC825574
	UINT32                                                  reserved132;	//0xCC825578
	UINT32                                                  reserved133;	//0xCC82557C
	UINT32                                                  reserved134;	//0xCC825580
	UINT32                                                  reserved135;	//0xCC825584
	UINT32                                                  reserved136;	//0xCC825588
	UINT32                                                  reserved137;	//0xCC82558C
	UINT32                                                  reserved138;	//0xCC825590
	UINT32                                                  reserved139;	//0xCC825594
	UINT32                                                  reserved140;	//0xCC825598
	UINT32                                                  reserved141;	//0xCC82559C
	UINT32                                                  reserved142;	//0xCC8255A0
	UINT32                                                  reserved143;	//0xCC8255A4
	UINT32                                                  reserved144;	//0xCC8255A8
	UINT32                                                  reserved145;	//0xCC8255AC
	UINT32                                                  reserved146;	//0xCC8255B0
	UINT32                                                  reserved147;	//0xCC8255B4
	UINT32                                                  reserved148;	//0xCC8255B8
	UINT32                                                  reserved149;	//0xCC8255BC
	UINT32                                                  reserved150;	//0xCC8255C0
	UINT32                                                  reserved151;	//0xCC8255C4
	UINT32                                                  reserved152;	//0xCC8255C8
	UINT32                                                  reserved153;	//0xCC8255CC
	UINT32                                                  reserved154;	//0xCC8255D0
	UINT32                                                  reserved155;	//0xCC8255D4
	UINT32                                                  reserved156;	//0xCC8255D8
	UINT32                                                  reserved157;	//0xCC8255DC
	UINT32                                                  reserved158;	//0xCC8255E0
	UINT32                                                  reserved159;	//0xCC8255E4
	UINT32                                                  reserved160;	//0xCC8255E8
	UINT32                                                  reserved161;	//0xCC8255EC
	UINT32                                                  reserved162;	//0xCC8255F0
	UINT32                                                  reserved163;	//0xCC8255F4
	UINT32                                                  reserved164;	//0xCC8255F8
	UINT32                                                  reserved165;	//0xCC8255FC
	PE_O24_GAV_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCC825600
	PE_O24_GAV_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCC825604
	PE_O24_GAV_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCC825608
	PE_O24_GAV_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCC82560C
	PE_O24_GAV_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCC825610
	PE_O24_GAV_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCC825614
	UINT32                                                  reserved166;	//0xCC825618
	UINT32                                                  reserved167;	//0xCC82561C
	UINT32                                                  reserved168;	//0xCC825620
	UINT32                                                  reserved169;	//0xCC825624
	UINT32                                                  reserved170;	//0xCC825628
	UINT32                                                  reserved171;	//0xCC82562C
	UINT32                                                  reserved172;	//0xCC825630
	UINT32                                                  reserved173;	//0xCC825634
	UINT32                                                  reserved174;	//0xCC825638
	UINT32                                                  reserved175;	//0xCC82563C
	UINT32                                                  reserved176;	//0xCC825640
	UINT32                                                  reserved177;	//0xCC825644
	UINT32                                                  reserved178;	//0xCC825648
	UINT32                                                  reserved179;	//0xCC82564C
	UINT32                                                  reserved180;	//0xCC825650
	UINT32                                                  reserved181;	//0xCC825654
	UINT32                                                  reserved182;	//0xCC825658
	UINT32                                                  reserved183;	//0xCC82565C
	PE_O24_GAV_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCC825660
	PE_O24_GAV_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCC825664
	PE_O24_GAV_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCC825668
	PE_O24_GAV_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCC82566C
	UINT32                                                  reserved184;	//0xCC825670
	UINT32                                                  reserved185;	//0xCC825674
	UINT32                                                  reserved186;	//0xCC825678
	UINT32                                                  reserved187;	//0xCC82567C
	UINT32                                                  reserved188;	//0xCC825680
	UINT32                                                  reserved189;	//0xCC825684
	UINT32                                                  reserved190;	//0xCC825688
	UINT32                                                  reserved191;	//0xCC82568C
	UINT32                                                  reserved192;	//0xCC825690
	UINT32                                                  reserved193;	//0xCC825694
	UINT32                                                  reserved194;	//0xCC825698
	UINT32                                                  reserved195;	//0xCC82569C
	UINT32                                                  reserved196;	//0xCC8256A0
	UINT32                                                  reserved197;	//0xCC8256A4
	UINT32                                                  reserved198;	//0xCC8256A8
	UINT32                                                  reserved199;	//0xCC8256AC
	UINT32                                                  reserved200;	//0xCC8256B0
	UINT32                                                  reserved201;	//0xCC8256B4
	UINT32                                                  reserved202;	//0xCC8256B8
	UINT32                                                  reserved203;	//0xCC8256BC
	UINT32                                                  reserved204;	//0xCC8256C0
	UINT32                                                  reserved205;	//0xCC8256C4
	UINT32                                                  reserved206;	//0xCC8256C8
	UINT32                                                  reserved207;	//0xCC8256CC
	UINT32                                                  reserved208;	//0xCC8256D0
	UINT32                                                  reserved209;	//0xCC8256D4
	UINT32                                                  reserved210;	//0xCC8256D8
	UINT32                                                  reserved211;	//0xCC8256DC
	UINT32                                                  reserved212;	//0xCC8256E0
	UINT32                                                  reserved213;	//0xCC8256E4
	UINT32                                                  reserved214;	//0xCC8256E8
	UINT32                                                  reserved215;	//0xCC8256EC
	UINT32                                                  reserved216;	//0xCC8256F0
	UINT32                                                  reserved217;	//0xCC8256F4
	UINT32                                                  reserved218;	//0xCC8256F8
	UINT32                                                  reserved219;	//0xCC8256FC
	PE_O24_GAV_SHP_CORE_TMAP_STAT_00_T           shp_core_tmap_stat_00;	//0xCC825700
	PE_O24_GAV_SHP_CORE_TMAP_STAT_01_T           shp_core_tmap_stat_01;	//0xCC825704
	PE_O24_GAV_SHP_CORE_TMAP_STAT_02_T           shp_core_tmap_stat_02;	//0xCC825708
	PE_O24_GAV_SHP_CORE_TMAP_STAT_03_T           shp_core_tmap_stat_03;	//0xCC82570C
	PE_O24_GAV_SHP_CORE_TMAP_STAT_04_T           shp_core_tmap_stat_04;	//0xCC825710
	PE_O24_GAV_SHP_CORE_TMAP_STAT_05_T           shp_core_tmap_stat_05;	//0xCC825714
	PE_O24_GAV_SHP_CORE_TMAP_STAT_06_T           shp_core_tmap_stat_06;	//0xCC825718
	PE_O24_GAV_SHP_CORE_TMAP_STAT_07_T           shp_core_tmap_stat_07;	//0xCC82571C
	UINT32                                                  reserved220;	//0xCC825720
	UINT32                                                  reserved221;	//0xCC825724
	UINT32                                                  reserved222;	//0xCC825728
	UINT32                                                  reserved223;	//0xCC82572C
	UINT32                                                  reserved224;	//0xCC825730
	UINT32                                                  reserved225;	//0xCC825734
	UINT32                                                  reserved226;	//0xCC825738
	UINT32                                                  reserved227;	//0xCC82573C
	UINT32                                                  reserved228;	//0xCC825740
	UINT32                                                  reserved229;	//0xCC825744
	UINT32                                                  reserved230;	//0xCC825748
	UINT32                                                  reserved231;	//0xCC82574C
	UINT32                                                  reserved232;	//0xCC825750
	UINT32                                                  reserved233;	//0xCC825754
	UINT32                                                  reserved234;	//0xCC825758
	UINT32                                                  reserved235;	//0xCC82575C
	UINT32                                                  reserved236;	//0xCC825760
	UINT32                                                  reserved237;	//0xCC825764
	UINT32                                                  reserved238;	//0xCC825768
	UINT32                                                  reserved239;	//0xCC82576C
	UINT32                                                  reserved240;	//0xCC825770
	UINT32                                                  reserved241;	//0xCC825774
	UINT32                                                  reserved242;	//0xCC825778
	UINT32                                                  reserved243;	//0xCC82577C
	UINT32                                                  reserved244;	//0xCC825780
	UINT32                                                  reserved245;	//0xCC825784
	UINT32                                                  reserved246;	//0xCC825788
	UINT32                                                  reserved247;	//0xCC82578C
	UINT32                                                  reserved248;	//0xCC825790
	UINT32                                                  reserved249;	//0xCC825794
	UINT32                                                  reserved250;	//0xCC825798
	UINT32                                                  reserved251;	//0xCC82579C
	UINT32                                                  reserved252;	//0xCC8257A0
	UINT32                                                  reserved253;	//0xCC8257A4
	UINT32                                                  reserved254;	//0xCC8257A8
	UINT32                                                  reserved255;	//0xCC8257AC
	UINT32                                                  reserved256;	//0xCC8257B0
	UINT32                                                  reserved257;	//0xCC8257B4
	UINT32                                                  reserved258;	//0xCC8257B8
	UINT32                                                  reserved259;	//0xCC8257BC
	UINT32                                                  reserved260;	//0xCC8257C0
	UINT32                                                  reserved261;	//0xCC8257C4
	UINT32                                                  reserved262;	//0xCC8257C8
	UINT32                                                  reserved263;	//0xCC8257CC
	UINT32                                                  reserved264;	//0xCC8257D0
	UINT32                                                  reserved265;	//0xCC8257D4
	UINT32                                                  reserved266;	//0xCC8257D8
	UINT32                                                  reserved267;	//0xCC8257DC
	UINT32                                                  reserved268;	//0xCC8257E0
	UINT32                                                  reserved269;	//0xCC8257E4
	UINT32                                                  reserved270;	//0xCC8257E8
	UINT32                                                  reserved271;	//0xCC8257EC
	PE_O24_GAV_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCC8257F0
	PE_O24_GAV_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCC8257F4
	PE_O24_GAV_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCC8257F8
	PE_O24_GAV_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCC8257FC
}PE_GAV_SHP_REG_O24_T;

#endif
