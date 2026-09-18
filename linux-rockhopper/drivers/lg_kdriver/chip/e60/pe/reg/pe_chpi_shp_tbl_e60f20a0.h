#ifndef _PE_CHPI_SHP_TBL_E60F20A0_H_
#define _PE_CHPI_SHP_TBL_E60F20A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B100 RW
	UINT32 reg_esf_detour_mode              :1;	//0:0	//edge shift filter detour enable
	UINT32 reg_esf_buffer_detour_en         :1;	//1:1	//edge shift filter buffer detour enable
	UINT32 resvd0                           :2;
	UINT32 reg_esf_en                       :1;	//4:4	//edge shift filter enable
	UINT32 resvd1                           :3;
	UINT32 reg_esf_dbg_en                   :1;	//8:8	//edge shift filter debug enable
	UINT32 resvd2                           :23;
	};
	};
}PE_E60F20_VSD1_SHP_ESF_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B104 RW
	UINT32 reg_esf_min_ratio                :8;	//7:0	//edge shift filter min ratio
	UINT32 reg_esf_base                     :8;	//15:8	//edge shift filter base
	UINT32 reg_esf_max_clip                 :8;	//23:16	//edge shift filter max clipping
	UINT32 reg_esf_master_gain              :8;	//31:24	//edge shift filter master gain
	};
	};
}PE_E60F20_VSD1_SHP_ESF_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B108 RW
	UINT32 reg_esf_ltv_offset               :8;	//7:0	//edge shift filter ltv offset
	UINT32 reg_esf_ltv_mul                  :8;	//15:8	//edge shift filter ltv mul
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_VSD1_SHP_ESF_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B150 RW
	UINT32 reg_dp_debug_display             :4;	//3:0	//0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//4:4	//dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//8:8	//dp buffer detour enable
	UINT32 resvd1                           :23;
	};
	};
}PE_E60F20_VSD1_SHP_DP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B160 RW
	UINT32 reg_fd_a_map_h_size              :2;	//1:0	//A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//8:8	//post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//18:16	//pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//20:19	//pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//23:21	//pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B164 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B168 RW
	UINT32 reg_fd_detail_beta_mul           :8;	//7:0	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//15:8	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//23:16	//get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//31:24	//get_t_map (alpha*t_map - beta*a_map)
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B16C RW
	UINT32 reg_fd_a_lut_edge_y0             :8;	//7:0	//A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//15:8	//A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//23:16	//A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//31:24	//A-map edge LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B170 RW
	UINT32 reg_fd_a_lut_detail_y0           :8;	//7:0	//A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//15:8	//A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//23:16	//A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//31:24	//A-map detail LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B174 RW
	UINT32 reg_fd_t_lut_edge_y0             :8;	//7:0	//T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//15:8	//T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//23:16	//T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//31:24	//T-map edge LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B178 RW
	UINT32 reg_fd_t_lut_detail_y0           :8;	//7:0	//T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//15:8	//T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//23:16	//T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//31:24	//T-map detail LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B17C RW
	UINT32 reg_fd_edge_minmax_y0            :8;	//7:0	//Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//15:8	//Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//23:16	//Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//31:24	//Final edge LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B180 RW
	UINT32 reg_fd_edge_minmax_y2            :8;	//7:0	//Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//15:8	//Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//23:16	//Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//31:24	//Final edge LUT, x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B184 RW
	UINT32 reg_fd_detail_minmax_y0          :8;	//7:0	//Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//15:8	//Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//23:16	//Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//31:24	//Final detail LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B188 RW
	UINT32 reg_fd_detail_minmax_y2          :8;	//7:0	//Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//15:8	//Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//23:16	//Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//31:24	//Final detail LUT, x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B18C RW
	UINT32 reg_fd_mnr_gain_e_en             :1;	//0:0	//MNR gain for edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//1:1	//MNR gain for texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//5:4	//s1 h expand
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B190 RW
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//7:0	//s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//23:16	//s1 ratio max
	UINT32 resvd1                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B194 RW
	UINT32 reg_fd_mnr_gain_x0               :8;	//7:0	//MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//15:8	//MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//23:16	//MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//31:24	//MNR gain LUT, y1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_0D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B198 RW
	UINT32 reg_fd_dct_t_lut_y0              :8;	//7:0	//DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//15:8	//DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//23:16	//DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//31:24	//DCT T-map LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_0E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B19C RW
	UINT32 reg_fd_dct_t_lut_y2              :8;	//7:0	//DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//15:8	//DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//23:16	//DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//31:24	//DCT T-map LUT, x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_0F_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1A0 RW
	UINT32 reg_fd_dct_t_lut_y4              :8;	//7:0	//DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//15:8	//DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//23:16	//DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//31:24	//DCT T-map LUT, x5
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1A4 RW
	UINT32 reg_fd_soft_gain_e_en            :1;	//0:0	//Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//1:1	//Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1A8 RW
	UINT32 reg_fd_soft_ratio                :8;	//7:0	//Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//15:8	//Soft edge offset
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1AC RW
	UINT32 reg_fd_soft_score_x0             :8;	//7:0	//Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//15:8	//Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//23:16	//Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//31:24	//Soft edge score, x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1B0 RW
	UINT32 reg_fd_soft_score_y0             :6;	//5:0	//Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//13:8	//Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//21:16	//Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//29:24	//Soft edge score, y3
	UINT32 resvd3                           :2;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1B4 RW
	UINT32 reg_fd_flat_input_sel            :2;	//1:0	//input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//4:4	//1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//8:8	//1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1B8 RW
	UINT32 reg_fd_flat_lut_y0               :8;	//7:0	//Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//15:8	//Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//23:16	//Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//31:24	//Flat region LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1C0 RW
	UINT32 reg_mp_shp_en                    :1;	//0:0	//MP enable
	UINT32 resvd                            :31;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1C4 RW
	UINT32 reg_mp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//31:24	//im gain v
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1C8 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1CC RW
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//7:4	//Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//11:8	//Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//15:12	//Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1D0 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1D4 RW
	UINT32 reg_mp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1D8 RW
	UINT32 reg_mp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1DC RW
	UINT32 reg_mp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1E0 RW
	UINT32 reg_mp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1E4 RW
	UINT32 reg_mp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1E8 RW
	UINT32 reg_mp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1EC RW
	UINT32 reg_mp_coring_en                 :1;	//0:0	//[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//2:1	//[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1F0 RW
	UINT32 reg_mp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_MP_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B1F4 RW
	UINT32 reg_apl_iir_en                   :1;	//0:0	//APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//15:8	//APL gain
	UINT32 resvd1                           :16;
	};
	};
}PE_E60F20_VSD1_SHP_APL_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B200 RW
	UINT32 reg_lc_shp_en                    :1;	//0:0	//LC enable
	UINT32 resvd0                           :3;
	UINT32 reg_lc_gb_en                     :1;	//4:4
	UINT32 resvd1                           :3;
	UINT32 reg_lc_center_target             :8;	//15:8	//center target
	UINT32 reg_lc_center_gain               :8;	//23:16	//center gain
	UINT32 reg_lc_local_gain                :8;	//31:24	//local gain
	};
	};
}PE_E60F20_VSD1_SHP_LC_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B204 RW
	UINT32 reg_lc_gb_y2                     :8;	//7:0	//gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//15:8	//gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//31:24	//gain balancing, x1
	};
	};
}PE_E60F20_VSD1_SHP_LC_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B208 RW
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//31:24	//gain balancing, x3
	};
	};
}PE_E60F20_VSD1_SHP_LC_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B20C RW
	UINT32 reg_lc_coring_en                 :1;	//0:0	//[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//2:1	//[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_LC_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B210 RW
	UINT32 reg_lc_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_LC_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B220 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//13:8	//reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//21:16	//reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//30:24	//reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//31:31	//reg_th_manual_en
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B224 RW
	UINT32 reg_derh_bflt_tap_size           :3;	//2:0	//bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//24:24	//reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//27:26	//edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//31:31	//edge_Y_filter en
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B228 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//13:8	//edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//21:16	//edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B22C RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B230 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B234 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B238 RW
	UINT32 reg_der_a_lut_y0                 :8;	//7:0	//A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//15:8	//A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//23:16	//A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//31:24	//A-map for der LUT, x1
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B23C RW
	UINT32 reg_der_a_lut_y2                 :8;	//7:0	//A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//15:8	//A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//23:16	//A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//31:24	//A-map for de-rining LUT, x3
	};
	};
}PE_E60F20_VSD1_SHP_DER_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B240 RW
	UINT32 reg_sp_shp_en                    :1;	//0:0	//SP enable
	UINT32 resvd                            :31;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B244 RW
	UINT32 reg_sp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B248 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B24C RW
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B250 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B254 RW
	UINT32 reg_sp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B258 RW
	UINT32 reg_sp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B25C RW
	UINT32 reg_sp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B260 RW
	UINT32 reg_sp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B264 RW
	UINT32 reg_sp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B268 RW
	UINT32 reg_sp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B26C RW
	UINT32 reg_sp_coring_en                 :1;	//0:0	//[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//2:1	//[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B270 RW
	UINT32 reg_sp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_SP_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B280 RW
	UINT32 reg_ptiv_enable                  :1;	//0:0	//PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_VSD1_SHP_PTI_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B284 RW
	UINT32 reg_ptih_enable                  :1;	//0:0	//PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_VSD1_SHP_PTI_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B288 RW
	UINT32 reg_pti_coring_en                :1;	//0:0	//[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//2:1	//[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_PTI_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B28C RW
	UINT32 reg_pti_coring_gain_e_b          :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_PTI_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B290 RW
	UINT32 reg_sti_enable                   :1;	//0:0	//STI enable
	UINT32 reg_sti_debug_map_en             :1;	//1:1	//debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//3:2	//mm tap size
	UINT32 reg_sti_avg_tap_size             :2;	//5:4	//avg tap size
	UINT32 reg_sti_ti_mode                  :1;	//6:6	//ti mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//15:8	//master gain
	UINT32 reg_sti_texture_gain             :8;	//23:16	//texture gain
	UINT32 reg_sti_edge_gain                :8;	//31:24	//edge gain
	};
	};
}PE_E60F20_VSD1_SHP_STI_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2A0 RW
	UINT32 reg_tgen_on_off                  :1;	//0:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//4:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//8:8	//
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//19:16	//
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//31:24	//
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2A4 RW
	UINT32 reg_tgen_delta_h_bound           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//26:24	//
	UINT32 resvd3                           :5;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2A8 RW
	UINT32 reg_tgen_rnd_th                  :8;	//7:0	//
	UINT32 reg_tgen_delta_wcurr             :4;	//11:8	//
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//21:16	//
	UINT32 resvd1                           :10;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2AC RW
	UINT32 reg_core0_tgen_rand_init_val_c0  :32;	//31:0	//
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_TGEN_CTRL_03_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2B0 RW
	UINT32 reg_core0_tgen_rand_init_val_c1  :32;	//31:0	//
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_TGEN_CTRL_03_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2B4 RW
	UINT32 reg_core1_tgen_rand_init_val_c0  :32;	//31:0	//
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_TGEN_CTRL_03_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2B8 RW
	UINT32 reg_core1_tgen_rand_init_val_c1  :32;	//31:0	//
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_TGEN_CTRL_03_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2BC RW
	UINT32 reg_tgen_dr_ratio                :3;	//2:0	//
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//13:8	//
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//20:16	//
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//25:24	//
	UINT32 resvd3                           :6;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2C0 RW
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//20:16	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//28:24	//
	UINT32 resvd2                           :3;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2C4 RW
	UINT32 reg_tgen_blur_coef_x2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2C8 RW
	UINT32 reg_tgen_blur_coef_y2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2CC RW
	UINT32 reg_tgen_map_edge_gain           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//23:16	//
	UINT32 reg_tgen_gs_noise                :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2D0 RW
	UINT32 reg_tgen_gain7                   :4;	//3:0	//
	UINT32 reg_tgen_gain6                   :4;	//7:4	//
	UINT32 reg_tgen_gain5                   :4;	//11:8	//
	UINT32 reg_tgen_gain4                   :4;	//15:12	//
	UINT32 reg_tgen_gain3                   :4;	//19:16	//
	UINT32 reg_tgen_gain2                   :4;	//23:20	//
	UINT32 reg_tgen_gain1                   :4;	//27:24	//
	UINT32 reg_tgen_gain0                   :4;	//31:28	//
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2D4 RW
	UINT32 reg_tgen_coring_en               :1;	//0:0	//[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//2:1	//[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2D8 RW
	UINT32 reg_tgen_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_TGEN_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2E0 RW
	UINT32 reg_snr_blur_en                  :1;	//0:0	//SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//5:4	//filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//15:8	//Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//18:16	//SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
	};
}PE_E60F20_VSD1_SHP_SNR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2F0 RW
	UINT32 reg_dctp_en                      :1;	//0:0	//DCT peaking enable
	UINT32 resvd                            :31;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2F4 RW
	UINT32 reg_dctp_filt0_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2F8 RW
	UINT32 reg_dctp_filt0_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B2FC RW
	UINT32 reg_dctp_filt0_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B300 RW
	UINT32 reg_dctp_filt0_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B304 RW
	UINT32 reg_dctp_filt1_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B308 RW
	UINT32 reg_dctp_filt1_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B30C RW
	UINT32 reg_dctp_filt1_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B310 RW
	UINT32 reg_dctp_filt1_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B314 RW
	UINT32 reg_dctp_filt2_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B318 RW
	UINT32 reg_dctp_filt2_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B31C RW
	UINT32 reg_dctp_filt2_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B320 RW
	UINT32 reg_dctp_filt2_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B324 RW
	UINT32 reg_dctp_filt3_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_0D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B328 RW
	UINT32 reg_dctp_filt3_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_0E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B32C RW
	UINT32 reg_dctp_filt3_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_0F_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B330 RW
	UINT32 reg_dctp_filt3_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B334 RW
	UINT32 reg_dctp_filt4_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B338 RW
	UINT32 reg_dctp_filt4_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B33C RW
	UINT32 reg_dctp_filt4_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B340 RW
	UINT32 reg_dctp_filt4_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B344 RW
	UINT32 reg_dctp_filt5_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B348 RW
	UINT32 reg_dctp_filt5_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B34C RW
	UINT32 reg_dctp_filt5_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B350 RW
	UINT32 reg_dctp_filt5_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B354 RW
	UINT32 reg_dctp_text_lut_x0             :8;	//7:0	//DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//15:8	//DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//23:16	//DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//31:24	//DCT peaking texture LUT point, x3
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B358 RW
	UINT32 reg_dctp_text_lut_x4             :8;	//7:0	//DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//15:8	//DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_1A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B35C RW
	UINT32 reg_dctp_edge_lut_y0             :8;	//7:0	//DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//15:8	//DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//23:16	//DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//31:24	//DCT peaking edge LUT point, x1
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_1B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B360 RW
	UINT32 reg_dctp_edge_lut_y2             :8;	//7:0	//DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//15:8	//DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//23:16	//DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//31:24	//DCT peaking edge LUT point, x3
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_1C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B364 RW
	UINT32 reg_dctp_gain                    :8;	//7:0	//DCT peaking master gain
	UINT32 resvd                            :24;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_1D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B368 RW
	UINT32 reg_dctp_coring_en               :1;	//0:0	//[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//2:1	//[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dtcp_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_1E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B36C RW
	UINT32 reg_dctp_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_DCTP_CTRL_1F_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B370 RW
	UINT32 reg_nntg_en                      :1;	//0:0	//4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//5:4	//4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B374 RW
	UINT32 reg_core0_nntg_lsfr_init_1st_c0  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_01_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B378 RW
	UINT32 reg_core0_nntg_lsfr_init_2nd_c0  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_02_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B37C RW
	UINT32 reg_core0_nntg_lsfr_init_3rd_c0  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_03_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B380 RW
	UINT32 reg_core0_nntg_lsfr_init_4th_c0  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_04_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B384 RW
	UINT32 reg_core0_nntg_lsfr_init_5th_c0  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_05_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B388 RW
	UINT32 reg_core0_nntg_lsfr_init_1st_c1  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_01_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B38C RW
	UINT32 reg_core0_nntg_lsfr_init_2nd_c1  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_02_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B390 RW
	UINT32 reg_core0_nntg_lsfr_init_3rd_c1  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_03_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B394 RW
	UINT32 reg_core0_nntg_lsfr_init_4th_c1  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_04_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B398 RW
	UINT32 reg_core0_nntg_lsfr_init_5th_c1  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_05_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B39C RW
	UINT32 reg_core1_nntg_lsfr_init_1st_c0  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_01_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3A0 RW
	UINT32 reg_core1_nntg_lsfr_init_2nd_c0  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_02_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3A4 RW
	UINT32 reg_core1_nntg_lsfr_init_3rd_c0  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_03_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3A8 RW
	UINT32 reg_core1_nntg_lsfr_init_4th_c0  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_04_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3AC RW
	UINT32 reg_core1_nntg_lsfr_init_5th_c0  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_05_C0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3B0 RW
	UINT32 reg_core1_nntg_lsfr_init_1st_c1  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_01_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3B4 RW
	UINT32 reg_core1_nntg_lsfr_init_2nd_c1  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_02_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3B8 RW
	UINT32 reg_core1_nntg_lsfr_init_3rd_c1  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_03_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3BC RW
	UINT32 reg_core1_nntg_lsfr_init_4th_c1  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_04_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3C0 RW
	UINT32 reg_core1_nntg_lsfr_init_5th_c1  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_NNTG_CTRL_05_C1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3C4 RW
	UINT32 reg_nntg_rand_ratio              :8;	//7:0	//4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//14:8	//4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//23:16	//4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3C8 RW
	UINT32 reg_nntg_rand_coef_g00           :4;	//3:0	//4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//7:4	//4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//11:8	//4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//19:16	//4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//23:20	//4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//27:24	//4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3CC RW
	UINT32 reg_nntg_rand_coef_g20           :4;	//3:0	//4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//7:4	//4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//11:8	//4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//19:16	//4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//23:20	//4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//27:24	//4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3D0 RW
	UINT32 reg_nntg_nano_coef_g10           :4;	//3:0	//4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//7:4	//4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//11:8	//4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//19:16	//4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//23:20	//4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//27:24	//4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3D4 RW
	UINT32 reg_nntg_diff_lut_y0             :8;	//7:0	//4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//15:8	//4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//23:16	//4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//31:24	//4K nano-noise diff LUT point, x1
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3D8 RW
	UINT32 reg_nntg_diff_lut_y2             :8;	//7:0	//4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//15:8	//4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//23:16	//4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//31:24	//4K nano-noise diff LUT point, x3
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3DC RW
	UINT32 reg_nntg_edge_lut_y0             :8;	//7:0	//4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//15:8	//4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//23:16	//4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//31:24	//4K nano-noise edge LUT point, x1
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3E0 RW
	UINT32 reg_nntg_edge_lut_y2             :8;	//7:0	//4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//15:8	//4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//23:16	//4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//31:24	//4K nano-noise edge LUT point, x3
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_0D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3E4 RW
	UINT32 reg_nntg_random_gain             :8;	//7:0	//4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//15:8	//4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//23:16	//4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//31:24	//4K nano-noise denoise gain
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_0E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3E8 RW
	UINT32 reg_nntg_coring_en               :1;	//0:0	//[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//2:1	//[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_0F_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3EC RW
	UINT32 reg_nntg_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
	};
}PE_E60F20_VSD1_SHP_NNTG_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3F0 RW
	UINT32 reg_dp_sum_gain                  :8;	//7:0	//DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//9:8	//0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3F4 RW
	UINT32 reg_dp_sum_lut_y0                :8;	//7:0	//dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//15:8	//dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//23:16	//dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//31:24	//dp_sum LUT for delta control, x1
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3F8 RW
	UINT32 reg_dp_sum_lut_y2                :8;	//7:0	//dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//15:8	//dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//23:16	//dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//31:24	//dp_sum LUT for delta control, x3
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B3FC RW
	UINT32 reg_obj_dct_delta_lut_y0         :8;	//7:0	//object dct LUT for delta control, y0
	UINT32 reg_obj_dct_delta_lut_x0         :8;	//15:8	//object dct LUT for delta control, x0
	UINT32 reg_obj_dct_delta_lut_y1         :8;	//23:16	//object dct LUT for delta control, y1
	UINT32 reg_obj_dct_delta_lut_x1         :8;	//31:24	//object dct LUT for delta control, x1
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B400 RW
	UINT32 reg_obj_dct_delta_lut_y2         :8;	//7:0	//object dct LUT for delta control, y2
	UINT32 reg_obj_dct_delta_lut_x2         :8;	//15:8	//object dct LUT for delta control, x2
	UINT32 reg_obj_dct_delta_lut_y3         :8;	//23:16	//object dct LUT for delta control, y3
	UINT32 reg_obj_dct_delta_lut_x3         :8;	//31:24	//object dct LUT for delta control, x3
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B404 RW
	UINT32 reg_obj_tgen_delta_lut_y0        :8;	//7:0	//object tgen LUT for delta control, y0
	UINT32 reg_obj_tgen_delta_lut_x0        :8;	//15:8	//object tgen LUT for delta control, x0
	UINT32 reg_obj_tgen_delta_lut_y1        :8;	//23:16	//object tgen LUT for delta control, y1
	UINT32 reg_obj_tgen_delta_lut_x1        :8;	//31:24	//object tgen LUT for delta control, x1
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B408 RW
	UINT32 reg_obj_tgen_delta_lut_y2        :8;	//7:0	//object tgen LUT for delta control, y2
	UINT32 reg_obj_tgen_delta_lut_x2        :8;	//15:8	//object tgen LUT for delta control, x2
	UINT32 reg_obj_tgen_delta_lut_y3        :8;	//23:16	//object tgen LUT for delta control, y3
	UINT32 reg_obj_tgen_delta_lut_x3        :8;	//31:24	//object tgen LUT for delta control, x3
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B40C RW
	UINT32 reg_obj_lc_delta_lut_y0          :8;	//7:0	//object local contrast LUT for delta control, y0
	UINT32 reg_obj_lc_delta_lut_x0          :8;	//15:8	//object local contrast LUT for delta control, x0
	UINT32 reg_obj_lc_delta_lut_y1          :8;	//23:16	//object local contrast LUT for delta control, y1
	UINT32 reg_obj_lc_delta_lut_x1          :8;	//31:24	//object local contrast LUT for delta control, x1
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B410 RW
	UINT32 reg_obj_lc_delta_lut_y2          :8;	//7:0	//object local contrast LUT for delta control, y2
	UINT32 reg_obj_lc_delta_lut_x2          :8;	//15:8	//object local contrast LUT for delta control, x2
	UINT32 reg_obj_lc_delta_lut_y3          :8;	//23:16	//object local contrast LUT for delta control, y3
	UINT32 reg_obj_lc_delta_lut_x3          :8;	//31:24	//object local contrast LUT for delta control, x3
	};
	};
}PE_E60F20_VSD1_SHP_DP_SUM_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B420 RW
	UINT32 reg_psp_obj_en                   :1;	//0:0	//PSP object contrast enable
	UINT32 resvd                            :31;
	};
	};
}PE_E60F20_VSD1_SHP_PSP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B460 RW
	UINT32 reg_region_text_en               :1;	//0:0	//region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//6:4	//
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//15:8	//
	UINT32 reg_region_text_add_max          :8;	//23:16	//
	UINT32 reg_region_text_cuthif           :3;	//26:24	//
	UINT32 resvd2                           :5;
	};
	};
}PE_E60F20_VSD1_SHP_FD_REGION_TEXT_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B464 RW
	UINT32 reg_region_text_lut_y0           :8;	//7:0	//region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//15:8	//region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//23:16	//region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//31:24	//region texture LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_REGION_TEXT_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B468 RW
	UINT32 reg_region_text_lut_y2           :8;	//7:0	//region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//15:8	//region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//23:16	//region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//31:24	//region texture LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_REGION_TEXT_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B46C RW
	UINT32 reg_tmap_temp_iir_en             :1;	//0:0	//TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//4:4	//TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//15:8	//TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//24:24	//TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B470 RW
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//7:0	//tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//15:8	//tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//23:16	//tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//31:24	//tmap temporal previous blend LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B474 RW
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//7:0	//tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//15:8	//tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//23:16	//tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//31:24	//tmap temporal previous blend LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B478 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//7:0	//tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//15:8	//tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//23:16	//tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//31:24	//tmap temporal iir positive LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B47C RW
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//7:0	//tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//15:8	//tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//23:16	//tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//31:24	//tmap temporal iir positive LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B480 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//7:0	//tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//15:8	//tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//23:16	//tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//31:24	//tmap temporal iir positive LUT , x5
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B484 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//7:0	//tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//15:8	//tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//23:16	//tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//31:24	//tmap temporal iir negative LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B488 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//7:0	//tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//15:8	//tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//23:16	//tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//31:24	//tmap temporal iir negative LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B48C RW
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//7:0	//tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//15:8	//tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//23:16	//tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//31:24	//tmap temporal iir negative LUT , x5
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B490 RW
	UINT32 reg_tmap_stat_win0_start_x       :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B494 RW
	UINT32 reg_tmap_stat_win0_end_x         :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B498 RW
	UINT32 reg_tmap_stat_win1_start_x       :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B49C RW
	UINT32 reg_tmap_stat_win1_end_x         :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
	};
}PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4A0 RW
	UINT32 reg_dj_edf_en                    :1;	//0:0	//edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//1:1	//H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//3:3	//edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//4:4	//0: sum of (cur - center)	1: sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//5:5	//L-type protection
	UINT32 reg_dj_soft_en                   :1;	//6:6	//Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_dj_count_diff_th             :5;	//12:8	//matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//18:16	//000: normal display (hard decision)	001: direction map	010: edge gain	011: g0 gain	100: g1 gain	101: final gain
	UINT32 reg_dj_buffer_detour_en          :1;	//19:19	//dj buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//21:20	//center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//22:22	//neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//23:23	//dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//31:24	//line-variation threshold for edge-direction decision
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4A4 RW
	UINT32 reg_dj_level_th                  :8;	//7:0	//g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//23:16	//neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4A8 RW
	UINT32 reg_dj_g0_cnt_min                :5;	//4:0	//g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//12:8	//g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4AC RW
	UINT32 reg_dj_g1_protect_min            :8;	//7:0	//g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//14:8	//g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//23:16	//edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//31:24	//edge adaptive filter multiplication value
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4B0 RW
	UINT32 reg_dj_dir_sel_c1                :1;	//0:0	//DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//1:1	//DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//2:2	//DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//3:3	//DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4B4 RW
	UINT32 reg_dj_pattern0_0_00             :2;	//1:0	//DJ protect pattern0 [0][0]
	UINT32 reg_dj_pattern0_0_01             :2;	//3:2	//DJ protect pattern0 [0][1]
	UINT32 reg_dj_pattern0_0_02             :2;	//5:4	//DJ protect pattern0 [0][2]
	UINT32 reg_dj_pattern0_0_03             :2;	//7:6	//DJ protect pattern0 [0][3]
	UINT32 reg_dj_pattern0_0_04             :2;	//9:8	//DJ protect pattern0 [0][4]
	UINT32 reg_dj_pattern0_0_05             :2;	//11:10	//DJ protect pattern0 [0][5]
	UINT32 reg_dj_pattern0_0_06             :2;	//13:12	//DJ protect pattern0 [0][6]
	UINT32 reg_dj_pattern0_0_07             :2;	//15:14	//DJ protect pattern0 [0][7]
	UINT32 reg_dj_pattern0_0_08             :2;	//17:16	//DJ protect pattern0 [0][8]
	UINT32 reg_dj_pattern0_0_09             :2;	//19:18	//DJ protect pattern0 [0][9]
	UINT32 reg_dj_pattern0_0_10             :2;	//21:20	//DJ protect pattern0 [0][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4B8 RW
	UINT32 reg_dj_pattern0_1_00             :2;	//1:0	//DJ protect pattern0 [1][0]
	UINT32 reg_dj_pattern0_1_01             :2;	//3:2	//DJ protect pattern0 [1][1]
	UINT32 reg_dj_pattern0_1_02             :2;	//5:4	//DJ protect pattern0 [1][2]
	UINT32 reg_dj_pattern0_1_03             :2;	//7:6	//DJ protect pattern0 [1][3]
	UINT32 reg_dj_pattern0_1_04             :2;	//9:8	//DJ protect pattern0 [1][4]
	UINT32 reg_dj_pattern0_1_05             :2;	//11:10	//DJ protect pattern0 [1][5]
	UINT32 reg_dj_pattern0_1_06             :2;	//13:12	//DJ protect pattern0 [1][6]
	UINT32 reg_dj_pattern0_1_07             :2;	//15:14	//DJ protect pattern0 [1][7]
	UINT32 reg_dj_pattern0_1_08             :2;	//17:16	//DJ protect pattern0 [1][8]
	UINT32 reg_dj_pattern0_1_09             :2;	//19:18	//DJ protect pattern0 [1][9]
	UINT32 reg_dj_pattern0_1_10             :2;	//21:20	//DJ protect pattern0 [1][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4BC RW
	UINT32 reg_dj_pattern0_2_00             :2;	//1:0	//DJ protect pattern0 [2][0]
	UINT32 reg_dj_pattern0_2_01             :2;	//3:2	//DJ protect pattern0 [2][1]
	UINT32 reg_dj_pattern0_2_02             :2;	//5:4	//DJ protect pattern0 [2][2]
	UINT32 reg_dj_pattern0_2_03             :2;	//7:6	//DJ protect pattern0 [2][3]
	UINT32 reg_dj_pattern0_2_04             :2;	//9:8	//DJ protect pattern0 [2][4]
	UINT32 reg_dj_pattern0_2_05             :2;	//11:10	//DJ protect pattern0 [2][5]
	UINT32 reg_dj_pattern0_2_06             :2;	//13:12	//DJ protect pattern0 [2][6]
	UINT32 reg_dj_pattern0_2_07             :2;	//15:14	//DJ protect pattern0 [2][7]
	UINT32 reg_dj_pattern0_2_08             :2;	//17:16	//DJ protect pattern0 [2][8]
	UINT32 reg_dj_pattern0_2_09             :2;	//19:18	//DJ protect pattern0 [2][9]
	UINT32 reg_dj_pattern0_2_10             :2;	//21:20	//DJ protect pattern0 [2][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4C0 RW
	UINT32 reg_dj_pattern0_3_00             :2;	//1:0	//DJ protect pattern0 [3][0]
	UINT32 reg_dj_pattern0_3_01             :2;	//3:2	//DJ protect pattern0 [3][1]
	UINT32 reg_dj_pattern0_3_02             :2;	//5:4	//DJ protect pattern0 [3][2]
	UINT32 reg_dj_pattern0_3_03             :2;	//7:6	//DJ protect pattern0 [3][3]
	UINT32 reg_dj_pattern0_3_04             :2;	//9:8	//DJ protect pattern0 [3][4]
	UINT32 reg_dj_pattern0_3_05             :2;	//11:10	//DJ protect pattern0 [3][5]
	UINT32 reg_dj_pattern0_3_06             :2;	//13:12	//DJ protect pattern0 [3][6]
	UINT32 reg_dj_pattern0_3_07             :2;	//15:14	//DJ protect pattern0 [3][7]
	UINT32 reg_dj_pattern0_3_08             :2;	//17:16	//DJ protect pattern0 [3][8]
	UINT32 reg_dj_pattern0_3_09             :2;	//19:18	//DJ protect pattern0 [3][9]
	UINT32 reg_dj_pattern0_3_10             :2;	//21:20	//DJ protect pattern0 [3][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4C4 RW
	UINT32 reg_dj_pattern0_4_00             :2;	//1:0	//DJ protect pattern0 [4][0]
	UINT32 reg_dj_pattern0_4_01             :2;	//3:2	//DJ protect pattern0 [4][1]
	UINT32 reg_dj_pattern0_4_02             :2;	//5:4	//DJ protect pattern0 [4][2]
	UINT32 reg_dj_pattern0_4_03             :2;	//7:6	//DJ protect pattern0 [4][3]
	UINT32 reg_dj_pattern0_4_04             :2;	//9:8	//DJ protect pattern0 [4][4]
	UINT32 reg_dj_pattern0_4_05             :2;	//11:10	//DJ protect pattern0 [4][5]
	UINT32 reg_dj_pattern0_4_06             :2;	//13:12	//DJ protect pattern0 [4][6]
	UINT32 reg_dj_pattern0_4_07             :2;	//15:14	//DJ protect pattern0 [4][7]
	UINT32 reg_dj_pattern0_4_08             :2;	//17:16	//DJ protect pattern0 [4][8]
	UINT32 reg_dj_pattern0_4_09             :2;	//19:18	//DJ protect pattern0 [4][9]
	UINT32 reg_dj_pattern0_4_10             :2;	//21:20	//DJ protect pattern0 [4][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4C8 RW
	UINT32 reg_dj_pattern0_5_00             :2;	//1:0	//DJ protect pattern0 [5][0]
	UINT32 reg_dj_pattern0_5_01             :2;	//3:2	//DJ protect pattern0 [5][1]
	UINT32 reg_dj_pattern0_5_02             :2;	//5:4	//DJ protect pattern0 [5][2]
	UINT32 reg_dj_pattern0_5_03             :2;	//7:6	//DJ protect pattern0 [5][3]
	UINT32 reg_dj_pattern0_5_04             :2;	//9:8	//DJ protect pattern0 [5][4]
	UINT32 reg_dj_pattern0_5_05             :2;	//11:10	//DJ protect pattern0 [5][5]
	UINT32 reg_dj_pattern0_5_06             :2;	//13:12	//DJ protect pattern0 [5][6]
	UINT32 reg_dj_pattern0_5_07             :2;	//15:14	//DJ protect pattern0 [5][7]
	UINT32 reg_dj_pattern0_5_08             :2;	//17:16	//DJ protect pattern0 [5][8]
	UINT32 reg_dj_pattern0_5_09             :2;	//19:18	//DJ protect pattern0 [5][9]
	UINT32 reg_dj_pattern0_5_10             :2;	//21:20	//DJ protect pattern0 [5][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4CC RW
	UINT32 reg_dj_pattern0_6_00             :2;	//1:0	//DJ protect pattern0 [6][0]
	UINT32 reg_dj_pattern0_6_01             :2;	//3:2	//DJ protect pattern0 [6][1]
	UINT32 reg_dj_pattern0_6_02             :2;	//5:4	//DJ protect pattern0 [6][2]
	UINT32 reg_dj_pattern0_6_03             :2;	//7:6	//DJ protect pattern0 [6][3]
	UINT32 reg_dj_pattern0_6_04             :2;	//9:8	//DJ protect pattern0 [6][4]
	UINT32 reg_dj_pattern0_6_05             :2;	//11:10	//DJ protect pattern0 [6][5]
	UINT32 reg_dj_pattern0_6_06             :2;	//13:12	//DJ protect pattern0 [6][6]
	UINT32 reg_dj_pattern0_6_07             :2;	//15:14	//DJ protect pattern0 [6][7]
	UINT32 reg_dj_pattern0_6_08             :2;	//17:16	//DJ protect pattern0 [6][8]
	UINT32 reg_dj_pattern0_6_09             :2;	//19:18	//DJ protect pattern0 [6][9]
	UINT32 reg_dj_pattern0_6_10             :2;	//21:20	//DJ protect pattern0 [6][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4D0 RW
	UINT32 reg_dj_pattern0_flip0_h          :1;	//0:0	//DJ protect pattern0 flip0, H
	UINT32 reg_dj_pattern0_flip0_v          :1;	//1:1	//DJ protect pattern0 flip0, V
	UINT32 reg_dj_pattern0_flip1_h          :1;	//2:2	//DJ protect pattern0 flip1, H
	UINT32 reg_dj_pattern0_flip1_v          :1;	//3:3	//DJ protect pattern0 flip1, V
	UINT32 reg_dj_pattern0_flip2_h          :1;	//4:4	//DJ protect pattern0 flip2, H
	UINT32 reg_dj_pattern0_flip2_v          :1;	//5:5	//DJ protect pattern0 flip2, V
	UINT32 reg_dj_pattern0_flip3_h          :1;	//6:6	//DJ protect pattern0 flip3, H
	UINT32 reg_dj_pattern0_flip3_v          :1;	//7:7	//DJ protect pattern0 flip3, V
	UINT32 resvd                            :24;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4D4 RW
	UINT32 reg_dj_pattern1_0_00             :2;	//1:0	//DJ protect pattern1 [0][0]
	UINT32 reg_dj_pattern1_0_01             :2;	//3:2	//DJ protect pattern1 [0][1]
	UINT32 reg_dj_pattern1_0_02             :2;	//5:4	//DJ protect pattern1 [0][2]
	UINT32 reg_dj_pattern1_0_03             :2;	//7:6	//DJ protect pattern1 [0][3]
	UINT32 reg_dj_pattern1_0_04             :2;	//9:8	//DJ protect pattern1 [0][4]
	UINT32 reg_dj_pattern1_0_05             :2;	//11:10	//DJ protect pattern1 [0][5]
	UINT32 reg_dj_pattern1_0_06             :2;	//13:12	//DJ protect pattern1 [0][6]
	UINT32 reg_dj_pattern1_0_07             :2;	//15:14	//DJ protect pattern1 [0][7]
	UINT32 reg_dj_pattern1_0_08             :2;	//17:16	//DJ protect pattern1 [0][8]
	UINT32 reg_dj_pattern1_0_09             :2;	//19:18	//DJ protect pattern1 [0][9]
	UINT32 reg_dj_pattern1_0_10             :2;	//21:20	//DJ protect pattern1 [0][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_0D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4D8 RW
	UINT32 reg_dj_pattern1_1_00             :2;	//1:0	//DJ protect pattern1 [1][0]
	UINT32 reg_dj_pattern1_1_01             :2;	//3:2	//DJ protect pattern1 [1][1]
	UINT32 reg_dj_pattern1_1_02             :2;	//5:4	//DJ protect pattern1 [1][2]
	UINT32 reg_dj_pattern1_1_03             :2;	//7:6	//DJ protect pattern1 [1][3]
	UINT32 reg_dj_pattern1_1_04             :2;	//9:8	//DJ protect pattern1 [1][4]
	UINT32 reg_dj_pattern1_1_05             :2;	//11:10	//DJ protect pattern1 [1][5]
	UINT32 reg_dj_pattern1_1_06             :2;	//13:12	//DJ protect pattern1 [1][6]
	UINT32 reg_dj_pattern1_1_07             :2;	//15:14	//DJ protect pattern1 [1][7]
	UINT32 reg_dj_pattern1_1_08             :2;	//17:16	//DJ protect pattern1 [1][8]
	UINT32 reg_dj_pattern1_1_09             :2;	//19:18	//DJ protect pattern1 [1][9]
	UINT32 reg_dj_pattern1_1_10             :2;	//21:20	//DJ protect pattern1 [1][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_0E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4DC RW
	UINT32 reg_dj_pattern1_2_00             :2;	//1:0	//DJ protect pattern1 [2][0]
	UINT32 reg_dj_pattern1_2_01             :2;	//3:2	//DJ protect pattern1 [2][1]
	UINT32 reg_dj_pattern1_2_02             :2;	//5:4	//DJ protect pattern1 [2][2]
	UINT32 reg_dj_pattern1_2_03             :2;	//7:6	//DJ protect pattern1 [2][3]
	UINT32 reg_dj_pattern1_2_04             :2;	//9:8	//DJ protect pattern1 [2][4]
	UINT32 reg_dj_pattern1_2_05             :2;	//11:10	//DJ protect pattern1 [2][5]
	UINT32 reg_dj_pattern1_2_06             :2;	//13:12	//DJ protect pattern1 [2][6]
	UINT32 reg_dj_pattern1_2_07             :2;	//15:14	//DJ protect pattern1 [2][7]
	UINT32 reg_dj_pattern1_2_08             :2;	//17:16	//DJ protect pattern1 [2][8]
	UINT32 reg_dj_pattern1_2_09             :2;	//19:18	//DJ protect pattern1 [2][9]
	UINT32 reg_dj_pattern1_2_10             :2;	//21:20	//DJ protect pattern1 [2][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_0F_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4E0 RW
	UINT32 reg_dj_pattern1_3_00             :2;	//1:0	//DJ protect pattern1 [3][0]
	UINT32 reg_dj_pattern1_3_01             :2;	//3:2	//DJ protect pattern1 [3][1]
	UINT32 reg_dj_pattern1_3_02             :2;	//5:4	//DJ protect pattern1 [3][2]
	UINT32 reg_dj_pattern1_3_03             :2;	//7:6	//DJ protect pattern1 [3][3]
	UINT32 reg_dj_pattern1_3_04             :2;	//9:8	//DJ protect pattern1 [3][4]
	UINT32 reg_dj_pattern1_3_05             :2;	//11:10	//DJ protect pattern1 [3][5]
	UINT32 reg_dj_pattern1_3_06             :2;	//13:12	//DJ protect pattern1 [3][6]
	UINT32 reg_dj_pattern1_3_07             :2;	//15:14	//DJ protect pattern1 [3][7]
	UINT32 reg_dj_pattern1_3_08             :2;	//17:16	//DJ protect pattern1 [3][8]
	UINT32 reg_dj_pattern1_3_09             :2;	//19:18	//DJ protect pattern1 [3][9]
	UINT32 reg_dj_pattern1_3_10             :2;	//21:20	//DJ protect pattern1 [3][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4E4 RW
	UINT32 reg_dj_pattern1_4_00             :2;	//1:0	//DJ protect pattern1 [4][0]
	UINT32 reg_dj_pattern1_4_01             :2;	//3:2	//DJ protect pattern1 [4][1]
	UINT32 reg_dj_pattern1_4_02             :2;	//5:4	//DJ protect pattern1 [4][2]
	UINT32 reg_dj_pattern1_4_03             :2;	//7:6	//DJ protect pattern1 [4][3]
	UINT32 reg_dj_pattern1_4_04             :2;	//9:8	//DJ protect pattern1 [4][4]
	UINT32 reg_dj_pattern1_4_05             :2;	//11:10	//DJ protect pattern1 [4][5]
	UINT32 reg_dj_pattern1_4_06             :2;	//13:12	//DJ protect pattern1 [4][6]
	UINT32 reg_dj_pattern1_4_07             :2;	//15:14	//DJ protect pattern1 [4][7]
	UINT32 reg_dj_pattern1_4_08             :2;	//17:16	//DJ protect pattern1 [4][8]
	UINT32 reg_dj_pattern1_4_09             :2;	//19:18	//DJ protect pattern1 [4][9]
	UINT32 reg_dj_pattern1_4_10             :2;	//21:20	//DJ protect pattern1 [4][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4E8 RW
	UINT32 reg_dj_pattern1_5_00             :2;	//1:0	//DJ protect pattern1 [5][0]
	UINT32 reg_dj_pattern1_5_01             :2;	//3:2	//DJ protect pattern1 [5][1]
	UINT32 reg_dj_pattern1_5_02             :2;	//5:4	//DJ protect pattern1 [5][2]
	UINT32 reg_dj_pattern1_5_03             :2;	//7:6	//DJ protect pattern1 [5][3]
	UINT32 reg_dj_pattern1_5_04             :2;	//9:8	//DJ protect pattern1 [5][4]
	UINT32 reg_dj_pattern1_5_05             :2;	//11:10	//DJ protect pattern1 [5][5]
	UINT32 reg_dj_pattern1_5_06             :2;	//13:12	//DJ protect pattern1 [5][6]
	UINT32 reg_dj_pattern1_5_07             :2;	//15:14	//DJ protect pattern1 [5][7]
	UINT32 reg_dj_pattern1_5_08             :2;	//17:16	//DJ protect pattern1 [5][8]
	UINT32 reg_dj_pattern1_5_09             :2;	//19:18	//DJ protect pattern1 [5][9]
	UINT32 reg_dj_pattern1_5_10             :2;	//21:20	//DJ protect pattern1 [5][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4EC RW
	UINT32 reg_dj_pattern1_6_00             :2;	//1:0	//DJ protect pattern1 [6][0]
	UINT32 reg_dj_pattern1_6_01             :2;	//3:2	//DJ protect pattern1 [6][1]
	UINT32 reg_dj_pattern1_6_02             :2;	//5:4	//DJ protect pattern1 [6][2]
	UINT32 reg_dj_pattern1_6_03             :2;	//7:6	//DJ protect pattern1 [6][3]
	UINT32 reg_dj_pattern1_6_04             :2;	//9:8	//DJ protect pattern1 [6][4]
	UINT32 reg_dj_pattern1_6_05             :2;	//11:10	//DJ protect pattern1 [6][5]
	UINT32 reg_dj_pattern1_6_06             :2;	//13:12	//DJ protect pattern1 [6][6]
	UINT32 reg_dj_pattern1_6_07             :2;	//15:14	//DJ protect pattern1 [6][7]
	UINT32 reg_dj_pattern1_6_08             :2;	//17:16	//DJ protect pattern1 [6][8]
	UINT32 reg_dj_pattern1_6_09             :2;	//19:18	//DJ protect pattern1 [6][9]
	UINT32 reg_dj_pattern1_6_10             :2;	//21:20	//DJ protect pattern1 [6][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4F0 RW
	UINT32 reg_dj_pattern1_flip0_h          :1;	//0:0	//DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//1:1	//DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//2:2	//DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//3:3	//DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4F4 RW
	UINT32 reg_dj_pattern2_0_00             :2;	//1:0	//DJ protect pattern2 [0][0]
	UINT32 reg_dj_pattern2_0_01             :2;	//3:2	//DJ protect pattern2 [0][1]
	UINT32 reg_dj_pattern2_0_02             :2;	//5:4	//DJ protect pattern2 [0][2]
	UINT32 reg_dj_pattern2_0_03             :2;	//7:6	//DJ protect pattern2 [0][3]
	UINT32 reg_dj_pattern2_0_04             :2;	//9:8	//DJ protect pattern2 [0][4]
	UINT32 reg_dj_pattern2_0_05             :2;	//11:10	//DJ protect pattern2 [0][5]
	UINT32 reg_dj_pattern2_0_06             :2;	//13:12	//DJ protect pattern2 [0][6]
	UINT32 reg_dj_pattern2_0_07             :2;	//15:14	//DJ protect pattern2 [0][7]
	UINT32 reg_dj_pattern2_0_08             :2;	//17:16	//DJ protect pattern2 [0][8]
	UINT32 reg_dj_pattern2_0_09             :2;	//19:18	//DJ protect pattern2 [0][9]
	UINT32 reg_dj_pattern2_0_10             :2;	//21:20	//DJ protect pattern2 [0][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4F8 RW
	UINT32 reg_dj_pattern2_1_00             :2;	//1:0	//DJ protect pattern2 [1][0]
	UINT32 reg_dj_pattern2_1_01             :2;	//3:2	//DJ protect pattern2 [1][1]
	UINT32 reg_dj_pattern2_1_02             :2;	//5:4	//DJ protect pattern2 [1][2]
	UINT32 reg_dj_pattern2_1_03             :2;	//7:6	//DJ protect pattern2 [1][3]
	UINT32 reg_dj_pattern2_1_04             :2;	//9:8	//DJ protect pattern2 [1][4]
	UINT32 reg_dj_pattern2_1_05             :2;	//11:10	//DJ protect pattern2 [1][5]
	UINT32 reg_dj_pattern2_1_06             :2;	//13:12	//DJ protect pattern2 [1][6]
	UINT32 reg_dj_pattern2_1_07             :2;	//15:14	//DJ protect pattern2 [1][7]
	UINT32 reg_dj_pattern2_1_08             :2;	//17:16	//DJ protect pattern2 [1][8]
	UINT32 reg_dj_pattern2_1_09             :2;	//19:18	//DJ protect pattern2 [1][9]
	UINT32 reg_dj_pattern2_1_10             :2;	//21:20	//DJ protect pattern2 [1][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B4FC RW
	UINT32 reg_dj_pattern2_2_00             :2;	//1:0	//DJ protect pattern2 [2][0]
	UINT32 reg_dj_pattern2_2_01             :2;	//3:2	//DJ protect pattern2 [2][1]
	UINT32 reg_dj_pattern2_2_02             :2;	//5:4	//DJ protect pattern2 [2][2]
	UINT32 reg_dj_pattern2_2_03             :2;	//7:6	//DJ protect pattern2 [2][3]
	UINT32 reg_dj_pattern2_2_04             :2;	//9:8	//DJ protect pattern2 [2][4]
	UINT32 reg_dj_pattern2_2_05             :2;	//11:10	//DJ protect pattern2 [2][5]
	UINT32 reg_dj_pattern2_2_06             :2;	//13:12	//DJ protect pattern2 [2][6]
	UINT32 reg_dj_pattern2_2_07             :2;	//15:14	//DJ protect pattern2 [2][7]
	UINT32 reg_dj_pattern2_2_08             :2;	//17:16	//DJ protect pattern2 [2][8]
	UINT32 reg_dj_pattern2_2_09             :2;	//19:18	//DJ protect pattern2 [2][9]
	UINT32 reg_dj_pattern2_2_10             :2;	//21:20	//DJ protect pattern2 [2][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B500 RW
	UINT32 reg_dj_pattern2_3_00             :2;	//1:0	//DJ protect pattern2 [3][0]
	UINT32 reg_dj_pattern2_3_01             :2;	//3:2	//DJ protect pattern2 [3][1]
	UINT32 reg_dj_pattern2_3_02             :2;	//5:4	//DJ protect pattern2 [3][2]
	UINT32 reg_dj_pattern2_3_03             :2;	//7:6	//DJ protect pattern2 [3][3]
	UINT32 reg_dj_pattern2_3_04             :2;	//9:8	//DJ protect pattern2 [3][4]
	UINT32 reg_dj_pattern2_3_05             :2;	//11:10	//DJ protect pattern2 [3][5]
	UINT32 reg_dj_pattern2_3_06             :2;	//13:12	//DJ protect pattern2 [3][6]
	UINT32 reg_dj_pattern2_3_07             :2;	//15:14	//DJ protect pattern2 [3][7]
	UINT32 reg_dj_pattern2_3_08             :2;	//17:16	//DJ protect pattern2 [3][8]
	UINT32 reg_dj_pattern2_3_09             :2;	//19:18	//DJ protect pattern2 [3][9]
	UINT32 reg_dj_pattern2_3_10             :2;	//21:20	//DJ protect pattern2 [3][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B504 RW
	UINT32 reg_dj_pattern2_4_00             :2;	//1:0	//DJ protect pattern2 [4][0]
	UINT32 reg_dj_pattern2_4_01             :2;	//3:2	//DJ protect pattern2 [4][1]
	UINT32 reg_dj_pattern2_4_02             :2;	//5:4	//DJ protect pattern2 [4][2]
	UINT32 reg_dj_pattern2_4_03             :2;	//7:6	//DJ protect pattern2 [4][3]
	UINT32 reg_dj_pattern2_4_04             :2;	//9:8	//DJ protect pattern2 [4][4]
	UINT32 reg_dj_pattern2_4_05             :2;	//11:10	//DJ protect pattern2 [4][5]
	UINT32 reg_dj_pattern2_4_06             :2;	//13:12	//DJ protect pattern2 [4][6]
	UINT32 reg_dj_pattern2_4_07             :2;	//15:14	//DJ protect pattern2 [4][7]
	UINT32 reg_dj_pattern2_4_08             :2;	//17:16	//DJ protect pattern2 [4][8]
	UINT32 reg_dj_pattern2_4_09             :2;	//19:18	//DJ protect pattern2 [4][9]
	UINT32 reg_dj_pattern2_4_10             :2;	//21:20	//DJ protect pattern2 [4][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B508 RW
	UINT32 reg_dj_pattern2_5_00             :2;	//1:0	//DJ protect pattern2 [5][0]
	UINT32 reg_dj_pattern2_5_01             :2;	//3:2	//DJ protect pattern2 [5][1]
	UINT32 reg_dj_pattern2_5_02             :2;	//5:4	//DJ protect pattern2 [5][2]
	UINT32 reg_dj_pattern2_5_03             :2;	//7:6	//DJ protect pattern2 [5][3]
	UINT32 reg_dj_pattern2_5_04             :2;	//9:8	//DJ protect pattern2 [5][4]
	UINT32 reg_dj_pattern2_5_05             :2;	//11:10	//DJ protect pattern2 [5][5]
	UINT32 reg_dj_pattern2_5_06             :2;	//13:12	//DJ protect pattern2 [5][6]
	UINT32 reg_dj_pattern2_5_07             :2;	//15:14	//DJ protect pattern2 [5][7]
	UINT32 reg_dj_pattern2_5_08             :2;	//17:16	//DJ protect pattern2 [5][8]
	UINT32 reg_dj_pattern2_5_09             :2;	//19:18	//DJ protect pattern2 [5][9]
	UINT32 reg_dj_pattern2_5_10             :2;	//21:20	//DJ protect pattern2 [5][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_1A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B50C RW
	UINT32 reg_dj_pattern2_6_00             :2;	//1:0	//DJ protect pattern2 [6][0]
	UINT32 reg_dj_pattern2_6_01             :2;	//3:2	//DJ protect pattern2 [6][1]
	UINT32 reg_dj_pattern2_6_02             :2;	//5:4	//DJ protect pattern2 [6][2]
	UINT32 reg_dj_pattern2_6_03             :2;	//7:6	//DJ protect pattern2 [6][3]
	UINT32 reg_dj_pattern2_6_04             :2;	//9:8	//DJ protect pattern2 [6][4]
	UINT32 reg_dj_pattern2_6_05             :2;	//11:10	//DJ protect pattern2 [6][5]
	UINT32 reg_dj_pattern2_6_06             :2;	//13:12	//DJ protect pattern2 [6][6]
	UINT32 reg_dj_pattern2_6_07             :2;	//15:14	//DJ protect pattern2 [6][7]
	UINT32 reg_dj_pattern2_6_08             :2;	//17:16	//DJ protect pattern2 [6][8]
	UINT32 reg_dj_pattern2_6_09             :2;	//19:18	//DJ protect pattern2 [6][9]
	UINT32 reg_dj_pattern2_6_10             :2;	//21:20	//DJ protect pattern2 [6][10]
	UINT32 resvd                            :10;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_1B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B510 RW
	UINT32 reg_dj_pattern2_flip0_h          :1;	//0:0	//DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//1:1	//DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//2:2	//DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//3:3	//DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_1C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B514 RW
	UINT32 reg_dj_soft_g0_mul               :6;	//5:0	//Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//12:8	//Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//23:16	//Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_1D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B518 RW
	UINT32 reg_dj_soft_g1_mul               :6;	//5:0	//Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//12:8	//Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//23:16	//Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_1E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B51C RW
	UINT32 reg_dj_soft_g2_mul               :6;	//5:0	//Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//12:8	//Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//23:16	//Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_1F_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B520 RW
	UINT32 reg_dj_soft_base                 :8;	//7:0	//Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//15:8	//Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//16:16	//Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
	};
}PE_E60F20_VSD1_SHP_DJ_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B524 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_DB_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B528 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_DB_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B560 RW
	UINT32 reg_color_region_en              :1;	//0:0	//color region processing enable
	UINT32 reg_color_region_debug_en        :1;	//1:1	//color region debug map enable
	UINT32 resvd0                           :2;
	UINT32 reg_chr_protection_en            :1;	//4:4	//chroma protection enable
	UINT32 resvd1                           :3;
	UINT32 reg_chr_compensation_en          :1;	//8:8	//chroma compensation enable
	UINT32 resvd2                           :23;
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B564 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B568 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B56C RW
	UINT32 reg_chr_gain_r0_cb_y0            :8;	//7:0	//chroma gain LUT, R0, Cb, y0
	UINT32 reg_chr_gain_r0_cb_x0            :8;	//15:8	//chroma gain LUT, R0, Cb, x0
	UINT32 reg_chr_gain_r0_cb_y1            :8;	//23:16	//chroma gain LUT, R0, Cb, y1
	UINT32 reg_chr_gain_r0_cb_x1            :8;	//31:24	//chroma gain LUT, R0, Cb, x1
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B570 RW
	UINT32 reg_chr_gain_r0_cb_y2            :8;	//7:0	//chroma gain LUT, R0, Cb, y2
	UINT32 reg_chr_gain_r0_cb_x2            :8;	//15:8	//chroma gain LUT, R0, Cb, x2
	UINT32 reg_chr_gain_r0_cb_y3            :8;	//23:16	//chroma gain LUT, R0, Cb, y3
	UINT32 reg_chr_gain_r0_cb_x3            :8;	//31:24	//chroma gain LUT, R0, Cb, x3
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B574 RW
	UINT32 reg_chr_gain_r0_cr_y0            :8;	//7:0	//chroma gain LUT, R0, Cr, y0
	UINT32 reg_chr_gain_r0_cr_x0            :8;	//15:8	//chroma gain LUT, R0, Cr, x0
	UINT32 reg_chr_gain_r0_cr_y1            :8;	//23:16	//chroma gain LUT, R0, Cr, y1
	UINT32 reg_chr_gain_r0_cr_x1            :8;	//31:24	//chroma gain LUT, R0, Cr, x1
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B578 RW
	UINT32 reg_chr_gain_r0_cr_y2            :8;	//7:0	//chroma gain LUT, R0, Cr, y2
	UINT32 reg_chr_gain_r0_cr_x2            :8;	//15:8	//chroma gain LUT, R0, Cr, x2
	UINT32 reg_chr_gain_r0_cr_y3            :8;	//23:16	//chroma gain LUT, R0, Cr, y3
	UINT32 reg_chr_gain_r0_cr_x3            :8;	//31:24	//chroma gain LUT, R0, Cr, x3
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B57C RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B580 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B584 RW
	UINT32 reg_chr_gain_r1_cb_y0            :8;	//7:0	//chroma gain LUT, R1, Cb, y0
	UINT32 reg_chr_gain_r1_cb_x0            :8;	//15:8	//chroma gain LUT, R1, Cb, x0
	UINT32 reg_chr_gain_r1_cb_y1            :8;	//23:16	//chroma gain LUT, R1, Cb, y1
	UINT32 reg_chr_gain_r1_cb_x1            :8;	//31:24	//chroma gain LUT, R1, Cb, x1
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B588 RW
	UINT32 reg_chr_gain_r1_cb_y2            :8;	//7:0	//chroma gain LUT, R1, Cb, y2
	UINT32 reg_chr_gain_r1_cb_x2            :8;	//15:8	//chroma gain LUT, R1, Cb, x2
	UINT32 reg_chr_gain_r1_cb_y3            :8;	//23:16	//chroma gain LUT, R1, Cb, y3
	UINT32 reg_chr_gain_r1_cb_x3            :8;	//31:24	//chroma gain LUT, R1, Cb, x3
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B58C RW
	UINT32 reg_chr_gain_r1_cr_y0            :8;	//7:0	//chroma gain LUT, R1, Cr, y0
	UINT32 reg_chr_gain_r1_cr_x0            :8;	//15:8	//chroma gain LUT, R1, Cr, x0
	UINT32 reg_chr_gain_r1_cr_y1            :8;	//23:16	//chroma gain LUT, R1, Cr, y1
	UINT32 reg_chr_gain_r1_cr_x1            :8;	//31:24	//chroma gain LUT, R1, Cr, x1
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B590 RW
	UINT32 reg_chr_gain_r1_cr_y2            :8;	//7:0	//chroma gain LUT, R1, Cr, y2
	UINT32 reg_chr_gain_r1_cr_x2            :8;	//15:8	//chroma gain LUT, R1, Cr, x2
	UINT32 reg_chr_gain_r1_cr_y3            :8;	//23:16	//chroma gain LUT, R1, Cr, y3
	UINT32 reg_chr_gain_r1_cr_x3            :8;	//31:24	//chroma gain LUT, R1, Cr, x3
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B594 RW
	UINT32 reg_chr_gain_r0_gain             :8;	//7:0	//chroma gain alpha, R0
	UINT32 resvd0                           :8;
	UINT32 reg_chr_gain_r1_gain             :8;	//23:16	//chroma gain alpha, R1
	UINT32 reg_chr_gain_sel                 :1;	//24:24	//0: {3'd0,region_gain}	1: {region_gain,3'd0}
	UINT32 resvd1                           :7;
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_0D_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B598 RW
	UINT32 reg_chr_comp_y0                  :8;	//7:0	//chroma comp. linear mapping, y0
	UINT32 reg_chr_comp_x0                  :8;	//15:8	//chroma comp. linear mapping, x0
	UINT32 reg_chr_comp_y1                  :8;	//23:16	//chroma comp. linear mapping, y1
	UINT32 reg_chr_comp_x1                  :8;	//31:24	//chroma comp. linear mapping, x1
	};
	};
}PE_E60F20_VSD1_SHP_CHROMA_CTRL_0E_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5B0 RW
	UINT32 reg_flick_en                     :1;	//0:0	//frc flicker blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_flick_motion_sel             :2;	//5:4	//SHP FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1                           :2;
	UINT32 reg_flick_blur_type              :2;	//9:8	//frc flicker blur pel selection	0: cur pel[y][x+1]	1: cur pel[y][x-1]	2: average
	UINT32 resvd2                           :22;
	};
	};
}PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5B4 RW
	UINT32 reg_flick_motion_lut_y0          :8;	//7:0	//frc flicker blur motion LUT point, y0
	UINT32 reg_flick_motion_lut_x0          :8;	//15:8	//frc flicker blur motion LUT point, x0
	UINT32 reg_flick_motion_lut_y1          :8;	//23:16	//frc flicker blur motion LUT point, y1
	UINT32 reg_flick_motion_lut_x1          :8;	//31:24	//frc flicker blur motion LUT point, x1
	};
	};
}PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5B8 RW
	UINT32 reg_flick_motion_lut_y2          :8;	//7:0	//frcflicker blur motion LUT point, y2
	UINT32 reg_flick_motion_lut_x2          :8;	//15:8	//frc flicker blur motion LUT point, x2
	UINT32 reg_flick_motion_lut_y3          :8;	//23:16	//frc flicker blur motion LUT point, y3
	UINT32 reg_flick_motion_lut_x3          :8;	//31:24	//frc flicker blur motion LUT point, x3
	};
	};
}PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5BC RW
	UINT32 reg_flick_master_gain            :8;	//7:0	//frc flicker blur master gain
	UINT32 resvd                            :24;
	};
	};
}PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B620 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B624 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B628 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B62C RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B630 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B634 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B638 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B63C RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B640 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B644 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B648 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B64C RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_0B_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B650 RW
	UINT32 tdata0                           :32;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_0C_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B660 RW
	UINT32 reg_motion_prot_adaptive_en      :1;	//0:0	//motion protection enable
	UINT32 resvd                            :31;
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B664 RW
	UINT32 reg_motion_prot_lut_a_y0         :8;	//7:0	//motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0         :8;	//15:8	//motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1         :8;	//23:16	//motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1         :8;	//31:24	//motion gain LUT, A, x1
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B668 RW
	UINT32 reg_motion_prot_lut_a_y2         :8;	//7:0	//motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2         :8;	//15:8	//motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3         :8;	//23:16	//motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3         :8;	//31:24	//motion gain LUT, A, x3
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B66C RW
	UINT32 reg_motion_prot_lut_t_y0         :8;	//7:0	//motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0         :8;	//15:8	//motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1         :8;	//23:16	//motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1         :8;	//31:24	//motion gain LUT, T, x1
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B670 RW
	UINT32 reg_motion_prot_lut_t_y2         :8;	//7:0	//motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2         :8;	//15:8	//motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3         :8;	//23:16	//motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3         :8;	//31:24	//motion gain LUT, T, x3
	};
	};
}PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6B0 RW
	UINT32 reg_core1_win_mot_win_w1_x1      :16;	//15:0	//win_w1_x1
	UINT32 reg_core1_win_mot_win_w1_y1      :16;	//31:16	//win_w1_y1
	};
	};
}PE_E60F20_VSD1_SHP_CORE1_MOT_WIN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6C0 RW
	UINT32 reg_obj_shp_en                   :1;	//0:0	//0 : disable	1 : enable
	UINT32 resvd                            :31;
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6C4 RW
	UINT32 reg_obj_face_gain_lut_y0         :8;	//7:0	//object face gain LUT , y2
	UINT32 reg_obj_face_gain_lut_x0         :8;	//15:8	//object face gain LUT , x2
	UINT32 reg_obj_face_gain_lut_y1         :8;	//23:16	//object face gain LUT , y3
	UINT32 reg_obj_face_gain_lut_x1         :8;	//31:24	//object face gain LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6C8 RW
	UINT32 reg_obj_face_gain_lut_y2         :8;	//7:0	//object face gain LUT , y0
	UINT32 reg_obj_face_gain_lut_x2         :8;	//15:8	//object face gain LUT , x0
	UINT32 reg_obj_face_gain_lut_y3         :8;	//23:16	//object face gain LUT , y1
	UINT32 reg_obj_face_gain_lut_x3         :8;	//31:24	//object face gain LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6CC RW
	UINT32 reg_obj_obj_gain_lut_y0          :8;	//7:0	//object object gain LUT , y2
	UINT32 reg_obj_obj_gain_lut_x0          :8;	//15:8	//object object gain LUT , x2
	UINT32 reg_obj_obj_gain_lut_y1          :8;	//23:16	//object object gain LUT , y3
	UINT32 reg_obj_obj_gain_lut_x1          :8;	//31:24	//object object gain LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6D0 RW
	UINT32 reg_obj_obj_gain_lut_y2          :8;	//7:0	//object object gain LUT , y0
	UINT32 reg_obj_obj_gain_lut_x2          :8;	//15:8	//object object gain LUT , x0
	UINT32 reg_obj_obj_gain_lut_y3          :8;	//23:16	//object object gain LUT , y1
	UINT32 reg_obj_obj_gain_lut_x3          :8;	//31:24	//object object gain LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6D4 RW
	UINT32 reg_obj_final_blend_obj_lut_y0   :8;	//7:0	//object final_blend_obj LUT , y2
	UINT32 reg_obj_final_blend_obj_lut_x0   :8;	//15:8	//object final_blend_obj LUT , x2
	UINT32 reg_obj_final_blend_obj_lut_y1   :8;	//23:16	//object final_blend_obj LUT , y3
	UINT32 reg_obj_final_blend_obj_lut_x1   :8;	//31:24	//object final_blend_obj LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6D8 RW
	UINT32 reg_obj_final_blend_obj_lut_y2   :8;	//7:0	//object final_blend_obj LUT , y0
	UINT32 reg_obj_final_blend_obj_lut_x2   :8;	//15:8	//object final_blend_obj LUT , x0
	UINT32 reg_obj_final_blend_obj_lut_y3   :8;	//23:16	//object final_blend_obj LUT , y1
	UINT32 reg_obj_final_blend_obj_lut_x3   :8;	//31:24	//object final_blend_obj LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6DC RW
	UINT32 reg_obj_final_blend_face_lut_y0  :8;	//7:0	//object final_blend_face LUT , y2
	UINT32 reg_obj_final_blend_face_lut_x0  :8;	//15:8	//object final_blend_face LUT , x2
	UINT32 reg_obj_final_blend_face_lut_y1  :8;	//23:16	//object final_blend_face LUT , y3
	UINT32 reg_obj_final_blend_face_lut_x1  :8;	//31:24	//object final_blend_face LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6E0 RW
	UINT32 reg_obj_final_blend_face_lut_y2  :8;	//7:0	//object final_blend_face LUT , y0
	UINT32 reg_obj_final_blend_face_lut_x2  :8;	//15:8	//object final_blend_face LUT , x0
	UINT32 reg_obj_final_blend_face_lut_y3  :8;	//23:16	//object final_blend_face LUT , y1
	UINT32 reg_obj_final_blend_face_lut_x3  :8;	//31:24	//object final_blend_face LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6E4 RW
	UINT32 reg_obj_master_gain_lut_y0       :8;	//7:0	//object master_gain LUT , y2
	UINT32 reg_obj_master_gain_lut_x0       :8;	//15:8	//object master_gain LUT , x2
	UINT32 reg_obj_master_gain_lut_y1       :8;	//23:16	//object master_gain LUT , y3
	UINT32 reg_obj_master_gain_lut_x1       :8;	//31:24	//object master_gain LUT , x3
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B6E8 RW
	UINT32 reg_obj_master_gain_lut_y2       :8;	//7:0	//object master_gain LUT , y0
	UINT32 reg_obj_master_gain_lut_x2       :8;	//15:8	//object master_gain LUT , x0
	UINT32 reg_obj_master_gain_lut_y3       :8;	//23:16	//object master_gain LUT , y1
	UINT32 reg_obj_master_gain_lut_x3       :8;	//31:24	//object master_gain LUT , x1
	};
	};
}PE_E60F20_VSD1_SHP_OBJ_CTRL_0A_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF022158C RW
	UINT32 cti_en                           :1;	//0 //CTI enable
	UINT32 cti_clipping_mode                :1;	//1 //op mode	'0' : CTI	'1': peaking(for debug)
	UINT32 cti_pre_flt_mode                 :1;	//2 //pre-filtering	0 : off	1 : on
	UINT32 cti_tap                          :2;	//4:3	//CTI filter tap size	'0' : 7-tap	'1': 5-tap	'2': 3_2-tap	'3': 3-tap
	UINT32 resvd0                           :3;
	UINT32 cti_gain                         :8;	//15:8	//CTI gain(3.5u)
	UINT32 cti_debug_mode                   :3;	//18:16	//debug mode	"000" : normal display	"100" : coring map(cb)	"101" : coring map(cr)	"110" : avg(cb)	"111" : avg(cr)
	UINT32 resvd1                           :13;
	};
	};
}PE_E60F20_DNR0_CTI_CTRL_0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0221590 RW
	UINT32 cti_coring_th0                   :8;	//7:0	//CTI coring th0
	UINT32 cti_coring_th1                   :8;	//15:8	//CTI coring th1
	UINT32 cti_coring_smooth                :3;	//18:16	//NOT USED
	UINT32 resvd0                           :1;
	UINT32 reg_cti_tap2                     :2;	//21:20	//CTI coring map size	"00" : 7-tap	"01" : 5-tap	"10" : 3-tap	o.w : 7-tap
	UINT32 resvd1                           :10;
	};
	};
}PE_E60F20_DNR0_CTI_CTRL_1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217A0 RW
	UINT32 reg_lti_en                       :1;	//0 //
	UINT32 reg_lti_clipping_mode            :1;	//1 //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap                      :2;	//4:3	//
	UINT32 resvd1                           :3;
	UINT32 reg_lti_gain                     :8;	//15:8	//
	UINT32 resvd2                           :4;
	UINT32 reg_ycm_c_gain                   :4;	//23:20	//
	UINT32 reg_ycm_y_gain                   :4;	//27:24	//
	UINT32 reg_ycm_band_sel                 :3;	//30:28	//
	UINT32 reg_ycm_en                       :1;	//31 //
	};
	};
}PE_E60F20_DNR0_REG_CTI_CTRL_2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02217A4 RW
	UINT32 reg_lti_coring_th0               :8;	//7:0	//
	UINT32 reg_lti_coring_th1               :8;	//15:8	//
	UINT32 reg_lti_coring_sm                :3;	//18:16	//
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap2                     :2;	//21:20	//
	UINT32 resvd1                           :2;
	UINT32 reg_ycm_diff_th                  :8;	//31:24	//
	};
	};
}PE_E60F20_DNR0_REG_CTI_CTRL_3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5A0 RW
	UINT32 reg_cti_en                       :1;	//0:0	//cti enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_filter_tap_size          :3;	//6:4	//000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_gain                     :8;	//15:8	//gain (3.5u)
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_VSD1_SHP_CTI_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5A4 RW
	UINT32 reg_cti_coring_th0               :8;	//7:0	//coring th0
	UINT32 reg_cti_coring_th1               :8;	//15:8	//coring_th1
	UINT32 reg_cti_coring_map_filter        :3;	//18:16	//000: no filtering	001: 5-tap filtering	010: 7-tap filtering	011: 9-tap filtering	100: 11-tap filtering	101: 13-tap filtering
	UINT32 resvd0                           :1;
	UINT32 reg_cti_coring_tap_size          :3;	//22:20	//000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_debug_mode               :2;	//25:24	//00: normal display	10: coring_map(cb)	11: coring_map(cr)
	UINT32 resvd2                           :6;
	};
	};
}PE_E60F20_VSD1_SHP_CTI_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017B5A8 RW
	UINT32 reg_cti_ycm_en                   :1;	//0:0	//y/c merge enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_ycm_band_sel             :3;	//6:4	//y/c merge band sel
	UINT32 resvd1                           :1;
	UINT32 reg_cti_ycm_diff_th              :8;	//15:8	//y/c merge diff threshold
	UINT32 reg_cti_ycm_y_gain               :4;	//19:16	//y/c merge gain, Y
	UINT32 reg_cti_ycm_c_gain               :4;	//23:20	//y/c merge gain, C
	UINT32 resvd2                           :8;
	};
	};
}PE_E60F20_VSD1_SHP_CTI_CTRL_02_T;

typedef struct
{
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0394E50 RW
	UINT32 reg_blend_lut_en                   :1 ;	// 0:0
	UINT32 reserved01                         :3 ;	// reserved
	UINT32 reg_blend_flat_threshold           :4 ;	// 7:4
	UINT32 reserved02                         :12;	// reserved
	UINT32 reg_blend_amp_weight               :12;	// 31:20
	};
	};
}PE_E60F20_SR_MERGE_BLEND_00_T;

typedef struct
{
	PE_E60F20_VSD1_SHP_ESF_CTRL_00_T                      shp_esf_ctrl_00;	//0xF017B100
	PE_E60F20_VSD1_SHP_ESF_CTRL_01_T                      shp_esf_ctrl_01;	//0xF017B104
	PE_E60F20_VSD1_SHP_ESF_CTRL_02_T                      shp_esf_ctrl_02;	//0xF017B108
	PE_E60F20_VSD1_SHP_DP_CTRL_00_T                        shp_dp_ctrl_00;	//0xF017B150
	PE_E60F20_VSD1_SHP_FD_CTRL_00_T                        shp_fd_ctrl_00;	//0xF017B160
	PE_E60F20_VSD1_SHP_FD_CTRL_01_T                        shp_fd_ctrl_01;	//0xF017B164
	PE_E60F20_VSD1_SHP_FD_CTRL_02_T                        shp_fd_ctrl_02;	//0xF017B168
	PE_E60F20_VSD1_SHP_FD_CTRL_03_T                        shp_fd_ctrl_03;	//0xF017B16C
	PE_E60F20_VSD1_SHP_FD_CTRL_04_T                        shp_fd_ctrl_04;	//0xF017B170
	PE_E60F20_VSD1_SHP_FD_CTRL_05_T                        shp_fd_ctrl_05;	//0xF017B174
	PE_E60F20_VSD1_SHP_FD_CTRL_06_T                        shp_fd_ctrl_06;	//0xF017B178
	PE_E60F20_VSD1_SHP_FD_CTRL_07_T                        shp_fd_ctrl_07;	//0xF017B17C
	PE_E60F20_VSD1_SHP_FD_CTRL_08_T                        shp_fd_ctrl_08;	//0xF017B180
	PE_E60F20_VSD1_SHP_FD_CTRL_09_T                        shp_fd_ctrl_09;	//0xF017B184
	PE_E60F20_VSD1_SHP_FD_CTRL_0A_T                        shp_fd_ctrl_0a;	//0xF017B188
	PE_E60F20_VSD1_SHP_FD_CTRL_0B_T                        shp_fd_ctrl_0b;	//0xF017B18C
	PE_E60F20_VSD1_SHP_FD_CTRL_0C_T                        shp_fd_ctrl_0c;	//0xF017B190
	PE_E60F20_VSD1_SHP_FD_CTRL_0D_T                        shp_fd_ctrl_0d;	//0xF017B194
	PE_E60F20_VSD1_SHP_FD_CTRL_0E_T                        shp_fd_ctrl_0e;	//0xF017B198
	PE_E60F20_VSD1_SHP_FD_CTRL_0F_T                        shp_fd_ctrl_0f;	//0xF017B19C
	PE_E60F20_VSD1_SHP_FD_CTRL_10_T                        shp_fd_ctrl_10;	//0xF017B1A0
	PE_E60F20_VSD1_SHP_FD_CTRL_11_T                        shp_fd_ctrl_11;	//0xF017B1A4
	PE_E60F20_VSD1_SHP_FD_CTRL_12_T                        shp_fd_ctrl_12;	//0xF017B1A8
	PE_E60F20_VSD1_SHP_FD_CTRL_13_T                        shp_fd_ctrl_13;	//0xF017B1AC
	PE_E60F20_VSD1_SHP_FD_CTRL_14_T                        shp_fd_ctrl_14;	//0xF017B1B0
	PE_E60F20_VSD1_SHP_FD_CTRL_15_T                        shp_fd_ctrl_15;	//0xF017B1B4
	PE_E60F20_VSD1_SHP_FD_CTRL_16_T                        shp_fd_ctrl_16;	//0xF017B1B8
	PE_E60F20_VSD1_SHP_MP_CTRL_00_T                        shp_mp_ctrl_00;	//0xF017B1C0
	PE_E60F20_VSD1_SHP_MP_CTRL_01_T                        shp_mp_ctrl_01;	//0xF017B1C4
	PE_E60F20_VSD1_SHP_MP_CTRL_02_T                        shp_mp_ctrl_02;	//0xF017B1C8
	PE_E60F20_VSD1_SHP_MP_CTRL_03_T                        shp_mp_ctrl_03;	//0xF017B1CC
	PE_E60F20_VSD1_SHP_MP_CTRL_04_T                        shp_mp_ctrl_04;	//0xF017B1D0
	PE_E60F20_VSD1_SHP_MP_CTRL_05_T                        shp_mp_ctrl_05;	//0xF017B1D4
	PE_E60F20_VSD1_SHP_MP_CTRL_06_T                        shp_mp_ctrl_06;	//0xF017B1D8
	PE_E60F20_VSD1_SHP_MP_CTRL_07_T                        shp_mp_ctrl_07;	//0xF017B1DC
	PE_E60F20_VSD1_SHP_MP_CTRL_08_T                        shp_mp_ctrl_08;	//0xF017B1E0
	PE_E60F20_VSD1_SHP_MP_CTRL_09_T                        shp_mp_ctrl_09;	//0xF017B1E4
	PE_E60F20_VSD1_SHP_MP_CTRL_0A_T                        shp_mp_ctrl_0a;	//0xF017B1E8
	PE_E60F20_VSD1_SHP_MP_CTRL_0B_T                        shp_mp_ctrl_0b;	//0xF017B1EC
	PE_E60F20_VSD1_SHP_MP_CTRL_0C_T                        shp_mp_ctrl_0c;	//0xF017B1F0
	PE_E60F20_VSD1_SHP_APL_CTRL_00_T                      shp_apl_ctrl_00;	//0xF017B1F4
	PE_E60F20_VSD1_SHP_LC_CTRL_00_T                        shp_lc_ctrl_00;	//0xF017B200
	PE_E60F20_VSD1_SHP_LC_CTRL_01_T                        shp_lc_ctrl_01;	//0xF017B204
	PE_E60F20_VSD1_SHP_LC_CTRL_02_T                        shp_lc_ctrl_02;	//0xF017B208
	PE_E60F20_VSD1_SHP_LC_CTRL_03_T                        shp_lc_ctrl_03;	//0xF017B20C
	PE_E60F20_VSD1_SHP_LC_CTRL_04_T                        shp_lc_ctrl_04;	//0xF017B210
	PE_E60F20_VSD1_SHP_DER_CTRL_00_T                      shp_der_ctrl_00;	//0xF017B220
	PE_E60F20_VSD1_SHP_DER_CTRL_01_T                      shp_der_ctrl_01;	//0xF017B224
	PE_E60F20_VSD1_SHP_DER_CTRL_02_T                      shp_der_ctrl_02;	//0xF017B228
	PE_E60F20_VSD1_SHP_DER_CTRL_03_T                      shp_der_ctrl_03;	//0xF017B22C
	PE_E60F20_VSD1_SHP_DER_CTRL_04_T                      shp_der_ctrl_04;	//0xF017B230
	PE_E60F20_VSD1_SHP_DER_CTRL_05_T                      shp_der_ctrl_05;	//0xF017B234
	PE_E60F20_VSD1_SHP_DER_CTRL_06_T                      shp_der_ctrl_06;	//0xF017B238
	PE_E60F20_VSD1_SHP_DER_CTRL_07_T                      shp_der_ctrl_07;	//0xF017B23C
	PE_E60F20_VSD1_SHP_SP_CTRL_00_T                        shp_sp_ctrl_00;	//0xF017B240
	PE_E60F20_VSD1_SHP_SP_CTRL_01_T                        shp_sp_ctrl_01;	//0xF017B244
	PE_E60F20_VSD1_SHP_SP_CTRL_02_T                        shp_sp_ctrl_02;	//0xF017B248
	PE_E60F20_VSD1_SHP_SP_CTRL_03_T                        shp_sp_ctrl_03;	//0xF017B24C
	PE_E60F20_VSD1_SHP_SP_CTRL_04_T                        shp_sp_ctrl_04;	//0xF017B250
	PE_E60F20_VSD1_SHP_SP_CTRL_05_T                        shp_sp_ctrl_05;	//0xF017B254
	PE_E60F20_VSD1_SHP_SP_CTRL_06_T                        shp_sp_ctrl_06;	//0xF017B258
	PE_E60F20_VSD1_SHP_SP_CTRL_07_T                        shp_sp_ctrl_07;	//0xF017B25C
	PE_E60F20_VSD1_SHP_SP_CTRL_08_T                        shp_sp_ctrl_08;	//0xF017B260
	PE_E60F20_VSD1_SHP_SP_CTRL_09_T                        shp_sp_ctrl_09;	//0xF017B264
	PE_E60F20_VSD1_SHP_SP_CTRL_0A_T                        shp_sp_ctrl_0a;	//0xF017B268
	PE_E60F20_VSD1_SHP_SP_CTRL_0B_T                        shp_sp_ctrl_0b;	//0xF017B26C
	PE_E60F20_VSD1_SHP_SP_CTRL_0C_T                        shp_sp_ctrl_0c;	//0xF017B270
	PE_E60F20_VSD1_SHP_PTI_CTRL_00_T                      shp_pti_ctrl_00;	//0xF017B280
	PE_E60F20_VSD1_SHP_PTI_CTRL_01_T                      shp_pti_ctrl_01;	//0xF017B284
	PE_E60F20_VSD1_SHP_PTI_CTRL_02_T                      shp_pti_ctrl_02;	//0xF017B288
	PE_E60F20_VSD1_SHP_PTI_CTRL_03_T                      shp_pti_ctrl_03;	//0xF017B28C
	PE_E60F20_VSD1_SHP_STI_CTRL_00_T                      shp_sti_ctrl_00;	//0xF017B290
	PE_E60F20_VSD1_SHP_TGEN_CTRL_00_T                    shp_tgen_ctrl_00;	//0xF017B2A0
	PE_E60F20_VSD1_SHP_TGEN_CTRL_01_T                    shp_tgen_ctrl_01;	//0xF017B2A4
	PE_E60F20_VSD1_SHP_TGEN_CTRL_02_T                    shp_tgen_ctrl_02;	//0xF017B2A8
	PE_E60F20_VSD1_SHP_CORE0_TGEN_CTRL_03_C0_T  shp_core0_tgen_ctrl_03_c0;	//0xF017B2AC
	PE_E60F20_VSD1_SHP_CORE0_TGEN_CTRL_03_C1_T  shp_core0_tgen_ctrl_03_c1;	//0xF017B2B0
	PE_E60F20_VSD1_SHP_TGEN_CTRL_04_T                    shp_tgen_ctrl_04;	//0xF017B2BC
	PE_E60F20_VSD1_SHP_TGEN_CTRL_05_T                    shp_tgen_ctrl_05;	//0xF017B2C0
	PE_E60F20_VSD1_SHP_TGEN_CTRL_06_T                    shp_tgen_ctrl_06;	//0xF017B2C4
	PE_E60F20_VSD1_SHP_TGEN_CTRL_07_T                    shp_tgen_ctrl_07;	//0xF017B2C8
	PE_E60F20_VSD1_SHP_TGEN_CTRL_08_T                    shp_tgen_ctrl_08;	//0xF017B2CC
	PE_E60F20_VSD1_SHP_TGEN_CTRL_09_T                    shp_tgen_ctrl_09;	//0xF017B2D0
	PE_E60F20_VSD1_SHP_TGEN_CTRL_0A_T                    shp_tgen_ctrl_0a;	//0xF017B2D4
	PE_E60F20_VSD1_SHP_TGEN_CTRL_0B_T                    shp_tgen_ctrl_0b;	//0xF017B2D8
	PE_E60F20_VSD1_SHP_SNR_CTRL_00_T                      shp_snr_ctrl_00;	//0xF017B2E0
	PE_E60F20_VSD1_SHP_DCTP_CTRL_00_T                    shp_dctp_ctrl_00;	//0xF017B2F0
	PE_E60F20_VSD1_SHP_DCTP_CTRL_01_T                    shp_dctp_ctrl_01;	//0xF017B2F4
	PE_E60F20_VSD1_SHP_DCTP_CTRL_02_T                    shp_dctp_ctrl_02;	//0xF017B2F8
	PE_E60F20_VSD1_SHP_DCTP_CTRL_03_T                    shp_dctp_ctrl_03;	//0xF017B2FC
	PE_E60F20_VSD1_SHP_DCTP_CTRL_04_T                    shp_dctp_ctrl_04;	//0xF017B300
	PE_E60F20_VSD1_SHP_DCTP_CTRL_05_T                    shp_dctp_ctrl_05;	//0xF017B304
	PE_E60F20_VSD1_SHP_DCTP_CTRL_06_T                    shp_dctp_ctrl_06;	//0xF017B308
	PE_E60F20_VSD1_SHP_DCTP_CTRL_07_T                    shp_dctp_ctrl_07;	//0xF017B30C
	PE_E60F20_VSD1_SHP_DCTP_CTRL_08_T                    shp_dctp_ctrl_08;	//0xF017B310
	PE_E60F20_VSD1_SHP_DCTP_CTRL_09_T                    shp_dctp_ctrl_09;	//0xF017B314
	PE_E60F20_VSD1_SHP_DCTP_CTRL_0A_T                    shp_dctp_ctrl_0a;	//0xF017B318
	PE_E60F20_VSD1_SHP_DCTP_CTRL_0B_T                    shp_dctp_ctrl_0b;	//0xF017B31C
	PE_E60F20_VSD1_SHP_DCTP_CTRL_0C_T                    shp_dctp_ctrl_0c;	//0xF017B320
	PE_E60F20_VSD1_SHP_DCTP_CTRL_0D_T                    shp_dctp_ctrl_0d;	//0xF017B324
	PE_E60F20_VSD1_SHP_DCTP_CTRL_0E_T                    shp_dctp_ctrl_0e;	//0xF017B328
	PE_E60F20_VSD1_SHP_DCTP_CTRL_0F_T                    shp_dctp_ctrl_0f;	//0xF017B32C
	PE_E60F20_VSD1_SHP_DCTP_CTRL_10_T                    shp_dctp_ctrl_10;	//0xF017B330
	PE_E60F20_VSD1_SHP_DCTP_CTRL_11_T                    shp_dctp_ctrl_11;	//0xF017B334
	PE_E60F20_VSD1_SHP_DCTP_CTRL_12_T                    shp_dctp_ctrl_12;	//0xF017B338
	PE_E60F20_VSD1_SHP_DCTP_CTRL_13_T                    shp_dctp_ctrl_13;	//0xF017B33C
	PE_E60F20_VSD1_SHP_DCTP_CTRL_14_T                    shp_dctp_ctrl_14;	//0xF017B340
	PE_E60F20_VSD1_SHP_DCTP_CTRL_15_T                    shp_dctp_ctrl_15;	//0xF017B344
	PE_E60F20_VSD1_SHP_DCTP_CTRL_16_T                    shp_dctp_ctrl_16;	//0xF017B348
	PE_E60F20_VSD1_SHP_DCTP_CTRL_17_T                    shp_dctp_ctrl_17;	//0xF017B34C
	PE_E60F20_VSD1_SHP_DCTP_CTRL_18_T                    shp_dctp_ctrl_18;	//0xF017B350
	PE_E60F20_VSD1_SHP_DCTP_CTRL_19_T                    shp_dctp_ctrl_19;	//0xF017B354
	PE_E60F20_VSD1_SHP_DCTP_CTRL_1A_T                    shp_dctp_ctrl_1a;	//0xF017B358
	PE_E60F20_VSD1_SHP_DCTP_CTRL_1B_T                    shp_dctp_ctrl_1b;	//0xF017B35C
	PE_E60F20_VSD1_SHP_DCTP_CTRL_1C_T                    shp_dctp_ctrl_1c;	//0xF017B360
	PE_E60F20_VSD1_SHP_DCTP_CTRL_1D_T                    shp_dctp_ctrl_1d;	//0xF017B364
	PE_E60F20_VSD1_SHP_DCTP_CTRL_1E_T                    shp_dctp_ctrl_1e;	//0xF017B368
	PE_E60F20_VSD1_SHP_DCTP_CTRL_1F_T                    shp_dctp_ctrl_1f;	//0xF017B36C
	PE_E60F20_VSD1_SHP_NNTG_CTRL_00_T                    shp_nntg_ctrl_00;	//0xF017B370
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_01_C0_T  shp_core0_nntg_ctrl_01_c0;	//0xF017B374
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_02_C0_T  shp_core0_nntg_ctrl_02_c0;	//0xF017B378
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_03_C0_T  shp_core0_nntg_ctrl_03_c0;	//0xF017B37C
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_04_C0_T  shp_core0_nntg_ctrl_04_c0;	//0xF017B380
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_05_C0_T  shp_core0_nntg_ctrl_05_c0;	//0xF017B384
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_01_C1_T  shp_core0_nntg_ctrl_01_c1;	//0xF017B388
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_02_C1_T  shp_core0_nntg_ctrl_02_c1;	//0xF017B38C
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_03_C1_T  shp_core0_nntg_ctrl_03_c1;	//0xF017B390
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_04_C1_T  shp_core0_nntg_ctrl_04_c1;	//0xF017B394
	PE_E60F20_VSD1_SHP_CORE0_NNTG_CTRL_05_C1_T  shp_core0_nntg_ctrl_05_c1;	//0xF017B398
	PE_E60F20_VSD1_SHP_NNTG_CTRL_06_T                    shp_nntg_ctrl_06;	//0xF017B3C4
	PE_E60F20_VSD1_SHP_NNTG_CTRL_07_T                    shp_nntg_ctrl_07;	//0xF017B3C8
	PE_E60F20_VSD1_SHP_NNTG_CTRL_08_T                    shp_nntg_ctrl_08;	//0xF017B3CC
	PE_E60F20_VSD1_SHP_NNTG_CTRL_09_T                    shp_nntg_ctrl_09;	//0xF017B3D0
	PE_E60F20_VSD1_SHP_NNTG_CTRL_0A_T                    shp_nntg_ctrl_0a;	//0xF017B3D4
	PE_E60F20_VSD1_SHP_NNTG_CTRL_0B_T                    shp_nntg_ctrl_0b;	//0xF017B3D8
	PE_E60F20_VSD1_SHP_NNTG_CTRL_0C_T                    shp_nntg_ctrl_0c;	//0xF017B3DC
	PE_E60F20_VSD1_SHP_NNTG_CTRL_0D_T                    shp_nntg_ctrl_0d;	//0xF017B3E0
	PE_E60F20_VSD1_SHP_NNTG_CTRL_0E_T                    shp_nntg_ctrl_0e;	//0xF017B3E4
	PE_E60F20_VSD1_SHP_NNTG_CTRL_0F_T                    shp_nntg_ctrl_0f;	//0xF017B3E8
	PE_E60F20_VSD1_SHP_NNTG_CTRL_10_T                    shp_nntg_ctrl_10;	//0xF017B3EC
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_00_T                shp_dp_sum_ctrl_00;	//0xF017B3F0
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_01_T                shp_dp_sum_ctrl_01;	//0xF017B3F4
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_02_T                shp_dp_sum_ctrl_02;	//0xF017B3F8
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_03_T                shp_dp_sum_ctrl_03;	//0xF017B3FC
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_04_T                shp_dp_sum_ctrl_04;	//0xF017B400
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_05_T                shp_dp_sum_ctrl_05;	//0xF017B404
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_06_T                shp_dp_sum_ctrl_06;	//0xF017B408
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_07_T                shp_dp_sum_ctrl_07;	//0xF017B40C
	PE_E60F20_VSD1_SHP_DP_SUM_CTRL_08_T                shp_dp_sum_ctrl_08;	//0xF017B410
	PE_E60F20_VSD1_SHP_PSP_CTRL_00_T                      shp_psp_ctrl_00;	//0xF017B420
	PE_E60F20_VSD1_SHP_FD_REGION_TEXT_00_T          shp_fd_region_text_00;	//0xF017B460
	PE_E60F20_VSD1_SHP_FD_REGION_TEXT_01_T          shp_fd_region_text_01;	//0xF017B464
	PE_E60F20_VSD1_SHP_FD_REGION_TEXT_02_T          shp_fd_region_text_02;	//0xF017B468
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_00_T              shp_fd_tmap_temp_00;	//0xF017B46C
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_01_T              shp_fd_tmap_temp_01;	//0xF017B470
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_02_T              shp_fd_tmap_temp_02;	//0xF017B474
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_03_T              shp_fd_tmap_temp_03;	//0xF017B478
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_04_T              shp_fd_tmap_temp_04;	//0xF017B47C
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_05_T              shp_fd_tmap_temp_05;	//0xF017B480
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_06_T              shp_fd_tmap_temp_06;	//0xF017B484
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_07_T              shp_fd_tmap_temp_07;	//0xF017B488
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_08_T              shp_fd_tmap_temp_08;	//0xF017B48C
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_09_T              shp_fd_tmap_temp_09;	//0xF017B490
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_0A_T              shp_fd_tmap_temp_0a;	//0xF017B494
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_0B_T              shp_fd_tmap_temp_0b;	//0xF017B498
	PE_E60F20_VSD1_SHP_FD_TMAP_TEMP_0C_T              shp_fd_tmap_temp_0c;	//0xF017B49C
	PE_E60F20_VSD1_SHP_DJ_CTRL_00_T                        shp_dj_ctrl_00;	//0xF017B4A0
	PE_E60F20_VSD1_SHP_DJ_CTRL_01_T                        shp_dj_ctrl_01;	//0xF017B4A4
	PE_E60F20_VSD1_SHP_DJ_CTRL_02_T                        shp_dj_ctrl_02;	//0xF017B4A8
	PE_E60F20_VSD1_SHP_DJ_CTRL_03_T                        shp_dj_ctrl_03;	//0xF017B4AC
	PE_E60F20_VSD1_SHP_DJ_CTRL_04_T                        shp_dj_ctrl_04;	//0xF017B4B0
	PE_E60F20_VSD1_SHP_DJ_CTRL_05_T                        shp_dj_ctrl_05;	//0xF017B4B4
	PE_E60F20_VSD1_SHP_DJ_CTRL_06_T                        shp_dj_ctrl_06;	//0xF017B4B8
	PE_E60F20_VSD1_SHP_DJ_CTRL_07_T                        shp_dj_ctrl_07;	//0xF017B4BC
	PE_E60F20_VSD1_SHP_DJ_CTRL_08_T                        shp_dj_ctrl_08;	//0xF017B4C0
	PE_E60F20_VSD1_SHP_DJ_CTRL_09_T                        shp_dj_ctrl_09;	//0xF017B4C4
	PE_E60F20_VSD1_SHP_DJ_CTRL_0A_T                        shp_dj_ctrl_0a;	//0xF017B4C8
	PE_E60F20_VSD1_SHP_DJ_CTRL_0B_T                        shp_dj_ctrl_0b;	//0xF017B4CC
	PE_E60F20_VSD1_SHP_DJ_CTRL_0C_T                        shp_dj_ctrl_0c;	//0xF017B4D0
	PE_E60F20_VSD1_SHP_DJ_CTRL_0D_T                        shp_dj_ctrl_0d;	//0xF017B4D4
	PE_E60F20_VSD1_SHP_DJ_CTRL_0E_T                        shp_dj_ctrl_0e;	//0xF017B4D8
	PE_E60F20_VSD1_SHP_DJ_CTRL_0F_T                        shp_dj_ctrl_0f;	//0xF017B4DC
	PE_E60F20_VSD1_SHP_DJ_CTRL_10_T                        shp_dj_ctrl_10;	//0xF017B4E0
	PE_E60F20_VSD1_SHP_DJ_CTRL_11_T                        shp_dj_ctrl_11;	//0xF017B4E4
	PE_E60F20_VSD1_SHP_DJ_CTRL_12_T                        shp_dj_ctrl_12;	//0xF017B4E8
	PE_E60F20_VSD1_SHP_DJ_CTRL_13_T                        shp_dj_ctrl_13;	//0xF017B4EC
	PE_E60F20_VSD1_SHP_DJ_CTRL_14_T                        shp_dj_ctrl_14;	//0xF017B4F0
	PE_E60F20_VSD1_SHP_DJ_CTRL_15_T                        shp_dj_ctrl_15;	//0xF017B4F4
	PE_E60F20_VSD1_SHP_DJ_CTRL_16_T                        shp_dj_ctrl_16;	//0xF017B4F8
	PE_E60F20_VSD1_SHP_DJ_CTRL_17_T                        shp_dj_ctrl_17;	//0xF017B4FC
	PE_E60F20_VSD1_SHP_DJ_CTRL_18_T                        shp_dj_ctrl_18;	//0xF017B500
	PE_E60F20_VSD1_SHP_DJ_CTRL_19_T                        shp_dj_ctrl_19;	//0xF017B504
	PE_E60F20_VSD1_SHP_DJ_CTRL_1A_T                        shp_dj_ctrl_1a;	//0xF017B508
	PE_E60F20_VSD1_SHP_DJ_CTRL_1B_T                        shp_dj_ctrl_1b;	//0xF017B50C
	PE_E60F20_VSD1_SHP_DJ_CTRL_1C_T                        shp_dj_ctrl_1c;	//0xF017B510
	PE_E60F20_VSD1_SHP_DJ_CTRL_1D_T                        shp_dj_ctrl_1d;	//0xF017B514
	PE_E60F20_VSD1_SHP_DJ_CTRL_1E_T                        shp_dj_ctrl_1e;	//0xF017B518
	PE_E60F20_VSD1_SHP_DJ_CTRL_1F_T                        shp_dj_ctrl_1f;	//0xF017B51C
	PE_E60F20_VSD1_SHP_DJ_CTRL_20_T                        shp_dj_ctrl_20;	//0xF017B520
	PE_E60F20_VSD1_SHP_DB_CTRL_00_T                        shp_db_ctrl_00;	//0xF017B524
	PE_E60F20_VSD1_SHP_DB_CTRL_01_T                        shp_db_ctrl_01;	//0xF017B528
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_00_T                shp_chroma_ctrl_00;	//0xF017B560
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_01_T                shp_chroma_ctrl_01;	//0xF017B564
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_02_T                shp_chroma_ctrl_02;	//0xF017B568
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_03_T                shp_chroma_ctrl_03;	//0xF017B56C
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_04_T                shp_chroma_ctrl_04;	//0xF017B570
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_05_T                shp_chroma_ctrl_05;	//0xF017B574
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_06_T                shp_chroma_ctrl_06;	//0xF017B578
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_07_T                shp_chroma_ctrl_07;	//0xF017B57C
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_08_T                shp_chroma_ctrl_08;	//0xF017B580
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_09_T                shp_chroma_ctrl_09;	//0xF017B584
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_0A_T                shp_chroma_ctrl_0a;	//0xF017B588
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_0B_T                shp_chroma_ctrl_0b;	//0xF017B58C
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_0C_T                shp_chroma_ctrl_0c;	//0xF017B590
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_0D_T                shp_chroma_ctrl_0d;	//0xF017B594
	PE_E60F20_VSD1_SHP_CHROMA_CTRL_0E_T                shp_chroma_ctrl_0e;	//0xF017B598
	PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_00_T          shp_frc_flick_ctrl_00;	//0xF017B5B0
	PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_01_T          shp_frc_flick_ctrl_01;	//0xF017B5B4
	PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_02_T          shp_frc_flick_ctrl_02;	//0xF017B5B8
	PE_E60F20_VSD1_SHP_FRC_FLICK_CTRL_03_T          shp_frc_flick_ctrl_03;	//0xF017B5BC
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_00_T      shp_motion_gain_ctrl_00;	//0xF017B620
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_01_T      shp_motion_gain_ctrl_01;	//0xF017B624
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_02_T      shp_motion_gain_ctrl_02;	//0xF017B628
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_03_T      shp_motion_gain_ctrl_03;	//0xF017B62C
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_04_T      shp_motion_gain_ctrl_04;	//0xF017B630
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_05_T      shp_motion_gain_ctrl_05;	//0xF017B634
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_06_T      shp_motion_gain_ctrl_06;	//0xF017B638
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_07_T      shp_motion_gain_ctrl_07;	//0xF017B63C
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_08_T      shp_motion_gain_ctrl_08;	//0xF017B640
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_09_T      shp_motion_gain_ctrl_09;	//0xF017B644
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_0A_T      shp_motion_gain_ctrl_0a;	//0xF017B648
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_0B_T      shp_motion_gain_ctrl_0b;	//0xF017B64C
	PE_E60F20_VSD1_SHP_MOTION_GAIN_CTRL_0C_T      shp_motion_gain_ctrl_0c;	//0xF017B650
	PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_00_T      shp_motion_prot_ctrl_00;	//0xF017B660
	PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_01_T      shp_motion_prot_ctrl_01;	//0xF017B664
	PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_02_T      shp_motion_prot_ctrl_02;	//0xF017B668
	PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_03_T      shp_motion_prot_ctrl_03;	//0xF017B66C
	PE_E60F20_VSD1_SHP_MOTION_PROT_CTRL_04_T      shp_motion_prot_ctrl_04;	//0xF017B670
	PE_E60F20_VSD1_SHP_OBJ_CTRL_00_T                      shp_obj_ctrl_00;	//0xF017B6C0
	PE_E60F20_VSD1_SHP_OBJ_CTRL_01_T                      shp_obj_ctrl_01;	//0xF017B6C4
	PE_E60F20_VSD1_SHP_OBJ_CTRL_02_T                      shp_obj_ctrl_02;	//0xF017B6C8
	PE_E60F20_VSD1_SHP_OBJ_CTRL_03_T                      shp_obj_ctrl_03;	//0xF017B6CC
	PE_E60F20_VSD1_SHP_OBJ_CTRL_04_T                      shp_obj_ctrl_04;	//0xF017B6D0
	PE_E60F20_VSD1_SHP_OBJ_CTRL_05_T                      shp_obj_ctrl_05;	//0xF017B6D4
	PE_E60F20_VSD1_SHP_OBJ_CTRL_06_T                      shp_obj_ctrl_06;	//0xF017B6D8
	PE_E60F20_VSD1_SHP_OBJ_CTRL_07_T                      shp_obj_ctrl_07;	//0xF017B6DC
	PE_E60F20_VSD1_SHP_OBJ_CTRL_08_T                      shp_obj_ctrl_08;	//0xF017B6E0
	PE_E60F20_VSD1_SHP_OBJ_CTRL_09_T                      shp_obj_ctrl_09;	//0xF017B6E4
	PE_E60F20_VSD1_SHP_OBJ_CTRL_0A_T                      shp_obj_ctrl_0a;	//0xF017B6E8
	PE_E60F20_SR_MERGE_BLEND_00_T                         sr_merge_blend_00; //0xF0394E50
}PE_CHPI_RES_TBL_E60F20_T;

typedef struct {
	PE_E60F20_DNR0_CTI_CTRL_0_T                                    cti_ctrl_0;	//0xF022158C
	PE_E60F20_DNR0_CTI_CTRL_1_T                                    cti_ctrl_1;	//0xF0221590
	PE_E60F20_DNR0_REG_CTI_CTRL_2_T                            reg_cti_ctrl_2;	//0xF02217A0
	PE_E60F20_DNR0_REG_CTI_CTRL_3_T                            reg_cti_ctrl_3;	//0xF02217A4
	PE_E60F20_VSD1_SHP_CTI_CTRL_00_T                          shp_cti_ctrl_00;	//0xF017B5A0
	PE_E60F20_VSD1_SHP_CTI_CTRL_01_T                          shp_cti_ctrl_01;	//0xF017B5A4
	PE_E60F20_VSD1_SHP_CTI_CTRL_02_T                          shp_cti_ctrl_02;	//0xF017B5A8
}PE_CHPI_CTI_TBL_E60F20_T;

//see PE_DDR_E60_SHP_UI_SQM_VSD_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[40];
}PE_CHPI_SHP_UI_SQM_E60F20_T;

//see PE_DDR_E60_SHP_SQM_CMN_VSD_SIZE
typedef struct {
	UINT32     cnt32;
	UINT32     ui32;
	UINT32     data32[51];
}PE_CHPI_SHP_CMN_SQM_E60F20_T;

#endif
