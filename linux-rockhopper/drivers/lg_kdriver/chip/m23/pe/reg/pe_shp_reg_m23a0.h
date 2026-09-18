#ifndef _PE_SHP_REG_M23A0_H_
#define _PE_SHP_REG_M23A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2000 RW 0x0019_0021
	UINT32 reg_top_actv_sel                 :1;	//(0:0,NA,1) //0: use core pass-through active	1: use active sync delay active
	UINT32 resvd0                           :3;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :7;
	UINT32 reg_top_lsb_copy_mode            :2;	//(21:20,NA,0) //0 : lsb force 0	1 : lsb force 1	2 : lsb force copy [1] -> [0]	3 : LBS FORCE COPY [0] -> [9]
	UINT32 resvd4                           :2;
	UINT32 reg_top_422to444_mode            :1;	//(24:24,NA,0) //0: H-average mode	1: repeatition mode
	UINT32 resvd5                           :3;
	UINT32 reg_top_mode_444                 :1;	//(28:28,NA,0) //0: 422 mode	1: 444 mode
	UINT32 resvd6                           :3;
	};
}PE_M23_VSD_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2004 RW 0x0870_0F00
	UINT32 reg_top_width                    :16;	//(15:0,NA,3840) //processing width (default : 3840)
	UINT32 reg_top_height                   :16;	//(31:16,NA,2160) //processing height (default : 2160)
	};
}PE_M23_VSD_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2008 RW 0x0118_0002
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,0) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,1) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_M23_VSD_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F200C RW 0x0000_000A
	UINT32 reg_top_pic_init_latency         :12;	//(11:0,NA,10) //pic init latency
	UINT32 resvd                            :20;
	};
}PE_M23_VSD_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2010 RW 0x0000_0019
	UINT32 reg_top_update_ctrl              :5;	//(4:0,NA,25) //[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_M23_VSD_SHP_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2014 RW 0x0E00_0810
	UINT32 reg_new_fd_detail_beta_mul       :8;	//(7:0,NA,16) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_detail_alpha_mul      :8;	//(15:8,NA,8) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_edge_beta_mul         :8;	//(23:16,NA,0) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_new_fd_edge_alpha_mul        :8;	//(31:24,NA,14) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_M23_VSD_SHP_NEW_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2018 RW 0x60A0_0020
	UINT32 reg_new_fd_edge_minmax_y0        :8;	//(7:0,NA,32) //Final edge LUT, y0
	UINT32 reg_new_fd_edge_minmax_x0        :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_new_fd_edge_minmax_y1        :8;	//(23:16,NA,160) //Final edge LUT, y1
	UINT32 reg_new_fd_edge_minmax_x1        :8;	//(31:24,NA,96) //Final edge LUT, x1
	};
}PE_M23_VSD_SHP_NEW_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F201C RW 0xFFFF_82DC
	UINT32 reg_new_fd_edge_minmax_y2        :8;	//(7:0,NA,220) //Final edge LUT, y2
	UINT32 reg_new_fd_edge_minmax_x2        :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_new_fd_edge_minmax_y3        :8;	//(23:16,NA,255) //Final edge LUT, y3
	UINT32 reg_new_fd_edge_minmax_x3        :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_M23_VSD_SHP_NEW_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2020 RW 0x2860_0040
	UINT32 reg_new_fd_detail_minmax_y0      :8;	//(7:0,NA,64) //Final detail LUT, y0
	UINT32 reg_new_fd_detail_minmax_x0      :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_new_fd_detail_minmax_y1      :8;	//(23:16,NA,96) //Final detail LUT, y1
	UINT32 reg_new_fd_detail_minmax_x1      :8;	//(31:24,NA,40) //Final detail LUT, x1
	};
}PE_M23_VSD_SHP_NEW_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2024 RW 0x64A0_4678
	UINT32 reg_new_fd_detail_minmax_y2      :8;	//(7:0,NA,120) //Final detail LUT, y2
	UINT32 reg_new_fd_detail_minmax_x2      :8;	//(15:8,NA,70) //Final detail LUT, x2
	UINT32 reg_new_fd_detail_minmax_y3      :8;	//(23:16,NA,160) //Final detail LUT, y3
	UINT32 reg_new_fd_detail_minmax_x3      :8;	//(31:24,NA,100) //Final detail LUT, x3
	};
}PE_M23_VSD_SHP_NEW_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2028 RW 0x0000_0180
	UINT32 resvd0                           :8;
	UINT32 reg_region_text_en_aux           :1;	//(8:8,NA,1) //Final detail LUT, y2
	UINT32 resvd1                           :23;
	};
}PE_M23_VSD_SHP_TEXT_REGION_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2040 RW 0xFFFF_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //pattern pixel value (Cb)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //pattern pixel value (Cr)
	};
}PE_M23_VSD_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2050 RW 0x0F00_0020
	UINT32 reg_out_hgos_head_crop_ptr       :13;	//(12:0,NA,32) //output horizontal gos head crop pointer
	UINT32 resvd0                           :3;
	UINT32 reg_out_hgos_tail_crop_ptr       :13;	//(28:16,NA,3840) //output horizontal gos tail crop pointer
	UINT32 resvd1                           :1;
	UINT32 reg_out_hgos_head_en             :1;	//(30:30,NA,0) //output horizontal gos head crop enable
	UINT32 reg_out_hgos_tail_en             :1;	//(31:31,NA,0) //output horizontal gos tail crop enable
	};
}PE_M23_VSD_SHP_GOS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2060 RW 0x0004_0005
	UINT32 reg_sync_dly_vsync               :16;	//(15:0,NA,5) //v sync (2K
	UINT32 reg_sync_dly_vfp                 :16;	//(31:16,NA,4) //v front porch (2K
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2064 RW 0x0024_0438
	UINT32 reg_sync_dly_va                  :16;	//(15:0,NA,1080) //v active (2K
	UINT32 reg_sync_dly_vbp                 :16;	//(31:16,NA,36) //v back porch (2K
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2068 RW 0x0058_002C
	UINT32 reg_sync_dly_hsync               :16;	//(15:0,NA,44) //h sync (2K
	UINT32 reg_sync_dly_hfp                 :16;	//(31:16,NA,88) //h front porch (2K
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F206C RW 0x0094_0780
	UINT32 reg_sync_dly_ha                  :16;	//(15:0,NA,1920) //h active (2K
	UINT32 reg_sync_dly_hbp                 :16;	//(31:16,NA,148) //h back porch (2K
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2070 RW 0x0000_0060
	UINT32 reg_sync_dly_line_start          :16;	//(15:0,NA,96) //line increase position
	UINT32 reg_sync_dly_actv_sel_in_h_src   :1;	//(16:16,NA,0) //select inverse in ha source
	UINT32 reg_sync_dly_actv_sel_in_v_src   :1;	//(17:17,NA,0) //select inverse in va source
	UINT32 reg_sync_dly_actv_sel_in_h_inv   :1;	//(18:18,NA,0) //inverse in ha
	UINT32 reg_sync_dly_actv_sel_in_v_inv   :1;	//(19:19,NA,0) //inverse in va
	UINT32 reg_sync_dly_actv_sel_out_ha     :1;	//(20:20,NA,0) //select out ha
	UINT32 reg_sync_dly_actv_sel_out_va     :1;	//(21:21,NA,0) //select out va
	UINT32 reg_sync_dly_actv_sel_out_hs     :1;	//(22:22,NA,0) //select out hs
	UINT32 reg_sync_dly_actv_sel_out_vs     :1;	//(23:23,NA,0) //select out vs
	UINT32 reg_sync_dly_tp_update_hv_zero   :1;	//(24:24,NA,0) //sync parameter update
	UINT32 reg_sync_dly_force_out_ha        :1;	//(25:25,NA,0) //force out ha
	UINT32 reg_sync_dly_force_out_va        :1;	//(26:26,NA,0) //force out va
	UINT32 reg_sync_dly_force_out_hs        :1;	//(27:27,NA,0) //force out hs
	UINT32 reg_sync_dly_cnt_rst_h_value_en  :1;	//(28:28,NA,0) //manual cnt h value enable
	UINT32 reg_sync_dly_cnt_rst_v_value_en  :1;	//(29:29,NA,0) //manual cnt v value enable
	UINT32 reg_sync_dly_force_out_vs        :1;	//(30:30,NA,0) //force out vs
	UINT32 reg_sync_dly_force_update        :1;	//(31:31,NA,0) //force update
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2074 RW 0x0007_00b2
	UINT32 reg_sync_dly_sync_h_dly          :16;	//(15:0,NA,178) //pixel delay
	UINT32 reg_sync_dly_sync_v_dly          :16;	//(31:16,NA,7) //line delay
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2078 RW 0x0008_0058
	UINT32 reg_sync_dly_cnt_rst_h_value     :16;	//(15:0,NA,88) //disp_pulse_dly Delay
	UINT32 reg_sync_dly_cnt_rst_v_value     :16;	//(31:16,NA,8) //[RO] disp_pulse_dly Counter
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F207C RW 0x0007_00b2
	UINT32 reg_sync_dly_auto_actv_h_dly     :15;	//(14:0,NA,178) //auto actv pixel delay
	UINT32 reg_sync_dly_auto_actv_gen_en    :1;	//(15:15,NA,0) //auto actv gen enable
	UINT32 reg_sync_dly_auto_actv_v_dly     :15;	//(30:16,NA,7) //auto actv line delay
	UINT32 reg_sync_dly_auto_actv_seam_en   :1;	//(31:31,NA,0) //auto actv seam enable
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2080 RW 0x0007_00b2
	UINT32 reg_sync_dly_auto_sync_h_dly     :15;	//(14:0,NA,178) //auto sync pixel delay
	UINT32 reg_sync_dly_auto_sync_gen_en    :1;	//(15:15,NA,0) //auto sync gen enable
	UINT32 reg_sync_dly_auto_sync_v_dly     :15;	//(30:16,NA,7) //auto sync line delay
	UINT32 reg_sync_dly_auto_sync_seam_en   :1;	//(31:31,NA,0) //auto sync seam enable
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2084 RW 0x0000_0000
	UINT32 reg_sync_dly_normal_number       :16;	//(15:0,NA,0) //protection mode
	UINT32 resvd                            :16;
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2088 RW 0x0000_0000
	UINT32 reg_sync_dly_cnt_h_rst_position  :16;	//(15:0,NA,0) //manual cnt h value position
	UINT32 reg_sync_dly_cnt_v_rst_position  :16;	//(31:16,NA,0) //manual cnt v value position
	};
}PE_M23_VSD_SHP_SYNC_DLY_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2090 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0) //ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0) //ROI mask pixel value (Y)
	UINT32 reg_roi_mask_pix_val_cb          :8;	//(23:16,NA,0) //ROI mask pixel value (Cb)
	UINT32 reg_roi_mask_pix_val_cr          :8;	//(31:24,NA,0) //ROI mask pixel value (Cr)
	};
}PE_M23_VSD_SHP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2094 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :12;	//(11:0,NA,0) //ROI mask window start position, x0
	UINT32 resvd0                           :4;
	UINT32 reg_roi_mask_win_y0              :12;	//(27:16,NA,0) //ROI mask window start position, y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2098 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :12;	//(11:0,NA,0) //ROI mask window end position, x1
	UINT32 resvd0                           :4;
	UINT32 reg_roi_mask_win_y1              :12;	//(27:16,NA,0) //ROI mask window end position, y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20A0 RW 0x0000_0010
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20A4 RW 0x4040_C814
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20A8 RW 0x0000_0819
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20B0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20B4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20B8 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20BC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20C0 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F20F0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map	1011: Gain A-map	1100: Gain T-map	1101: Texture region map	1110: object map	1111: face map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_M23_VSD_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2100 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2104 RW 0x0001_0000
	UINT32 resvd0                           :16;
	UINT32 reg_fd_dj_pre_a_map_h_size       :3;	//(18:16,NA,1) //dj pre-mmd h size (M23)
	UINT32 reg_fd_dj_pre_a_map_v_size       :2;	//(20:19,NA,0) //dj pre-mmd v size (M23)
	UINT32 reg_fd_dj_pre_a_cut_resolution   :3;	//(23:21,NA,0) //dj pre-mmd cut resolution
	UINT32 resvd1                           :8;
	};
}PE_M23_VSD_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2108 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_M23_VSD_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F210C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2110 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2114 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2118 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F211C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2120 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_M23_VSD_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2124 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2128 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_M23_VSD_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F212C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //MNR gain for edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //MNR gain for texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2130 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_M23_VSD_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2134 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_M23_VSD_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2138 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F213C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_M23_VSD_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2140 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_M23_VSD_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2144 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_M23_VSD_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2148 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_M23_VSD_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F214C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_M23_VSD_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2150 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_M23_VSD_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2154 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_M23_VSD_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2158 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_M23_VSD_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2160 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_M23_VSD_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2164 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_M23_VSD_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2168 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_M23_VSD_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F216C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_M23_VSD_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2170 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_M23_VSD_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2174 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2178 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_M23_VSD_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F217C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_M23_VSD_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2180 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_M23_VSD_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2184 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_M23_VSD_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2188 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_M23_VSD_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F218C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2190 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_VSD_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2194 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_M23_VSD_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21A0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 resvd                            :7;
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //local gain
	};
}PE_M23_VSD_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21A4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //gain balancing, x1
	};
}PE_M23_VSD_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21A8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //gain balancing, x3
	};
}PE_M23_VSD_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21AC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21B0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_VSD_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21C0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_M23_VSD_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21C4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_M23_VSD_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21C8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_M23_VSD_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21CC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21D8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_M23_VSD_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21DC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_M23_VSD_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21E0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_M23_VSD_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21E4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21E8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_M23_VSD_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21EC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_M23_VSD_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21F0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_M23_VSD_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21F4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21F8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_M23_VSD_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F21FC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_M23_VSD_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2200 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_M23_VSD_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2204 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_M23_VSD_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2208 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_M23_VSD_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F220C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2210 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_VSD_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2220 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_M23_VSD_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2224 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_M23_VSD_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2228 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F222C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_VSD_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2230 RW 0x1010_2014
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
}PE_M23_VSD_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2240 RW 0x8000_0011
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2244 RW 0x0640_0810
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2248 RW 0x003F_0580
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F224C RW 0x0000_48AB
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2250 RW 0x0000_48AB
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2254 RW 0x0202_1F04
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2258 RW 0x0008_0050
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F225C RW 0x1A00_0800
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2260 RW 0x1A00_0800
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2264 RW 0x3F80_1F1F
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2268 RW 0x48AB_CDFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F226C RW 0x0000_0037
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2270 RW 0x1010_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2274 RW 0x0003_0411
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2280 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2284 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2288 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F228C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2290 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2294 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2298 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F229C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22A0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22A4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22A8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22AC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22B0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22B4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22B8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22BC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22C0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22C4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22C8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22CC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22D0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22D4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22D8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22DC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22E0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22E4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_M23_VSD_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22E8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22EC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_M23_VSD_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22F0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_M23_VSD_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22F4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22F8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dtcp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F22FC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_M23_VSD_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2300 RW 0x0000_0001
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2304 RW 0x0000_159C
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2308 RW 0x2CA3_7199
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F230C RW 0x3236_3B62
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2310 RW 0xFD1C_D00A
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2314 RW 0x8C3C_2327
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2318 RW 0xF275_9828
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F231C RW 0xFEEA_5094
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2320 RW 0xECBE_ACAA
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2324 RW 0xD9C5_DFEA
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2328 RW 0x23E8_D99E
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F232C RW 0x00FF_308C
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2330 RW 0x0E12_0145
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2334 RW 0x01E0_0FEE
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2338 RW 0x0E11_011E
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F233C RW 0x0220_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2340 RW 0x0880_0460
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2344 RW 0x4090_20FF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2348 RW 0xA400_8040
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F234C RW 0xFF10_088C
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2350 RW 0x0000_0037
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2354 RW 0x1010_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2360 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2364 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2368 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F236C RW 0x4080_0070
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2370 RW 0xffa0_6090
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2374 RW 0x4080_0070
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2378 RW 0xffb0_6090
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F237C RW 0x4080_0070
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2380 RW 0xffa0_6090
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2384 RW 0x2828_0000
	UINT32 reg_dp_sum_cg_lut_y0             :8;	//(7:0,NA,0) //dp_sum LUT for delta_cg control, y0
	UINT32 reg_dp_sum_cg_lut_x0             :8;	//(15:8,NA,0) //dp_sum LUT for delta_cg control, x0
	UINT32 reg_dp_sum_cg_lut_y1             :8;	//(23:16,NA,40) //dp_sum LUT for delta_cg control, y1
	UINT32 reg_dp_sum_cg_lut_x1             :8;	//(31:24,NA,40) //dp_sum LUT for delta_cg control, x1
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2388 RW 0xFFFF_5050
	UINT32 reg_dp_sum_cg_lut_y2             :8;	//(7:0,NA,80) //dp_sum LUT for delta_cg control, y2
	UINT32 reg_dp_sum_cg_lut_x2             :8;	//(15:8,NA,80) //dp_sum LUT for delta_cg control, x2
	UINT32 reg_dp_sum_cg_lut_y3             :8;	//(23:16,NA,255) //dp_sum LUT for delta_cg control, y3
	UINT32 reg_dp_sum_cg_lut_x3             :8;	//(31:24,NA,255) //dp_sum LUT for delta_cg control, x3
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2390 RW 0x0000_0001
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_PSP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2394 RW 0x2828_0000
	UINT32 reg_dp_sum_obj_lut_y0            :8;	//(7:0,NA,0) //dp_sum LUT for object control, y0
	UINT32 reg_dp_sum_obj_lut_x0            :8;	//(15:8,NA,0) //dp_sum LUT for object control, x0
	UINT32 reg_dp_sum_obj_lut_y1            :8;	//(23:16,NA,40) //dp_sum LUT for object control, y1
	UINT32 reg_dp_sum_obj_lut_x1            :8;	//(31:24,NA,40) //dp_sum LUT for object control, x1
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2398 RW 0xFFFF_5050
	UINT32 reg_dp_sum_obj_lut_y2            :8;	//(7:0,NA,80) //dp_sum LUT for object control, y2
	UINT32 reg_dp_sum_obj_lut_x2            :8;	//(15:8,NA,80) //dp_sum LUT for object control, x2
	UINT32 reg_dp_sum_obj_lut_y3            :8;	//(23:16,NA,255) //dp_sum LUT for object control, y3
	UINT32 reg_dp_sum_obj_lut_x3            :8;	//(31:24,NA,255) //dp_sum LUT for object control, x3
	};
}PE_M23_VSD_SHP_DP_SUM_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23A0 RW 0x0000_0000
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
}PE_M23_VSD_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23A8 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23B0 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23C0 RW 0x0432_0c40
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23C4 RW 0x0f50_0410
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23C8 RW 0x46c8_2380
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23CC RW 0x0000_ff00
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23D0 RW 0x2840_0a00
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23D4 RW 0x5080_3c60
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23D8 RW 0x08d0_00c0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23DC RW 0x30f0_10e0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23E0 RW 0x80c0_60d0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23E4 RW 0x0870_0080
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23E8 RW 0x1850_1060
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23EC RW 0x4000_2040
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23F4 RW 0x086f_077f
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23F8 RW 0x0000_0780
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F23FC RW 0x0438_0eff
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2400 RW 0x8010_0179
	UINT32 reg_dj_edf_en                    :1;	//(0:0,NA,1) //edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//(1:1,NA,0) //H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//(3:3,NA,1) //edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//(4:4,NA,1) //0: sum of (cur - center)	1: sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//(5:5,NA,1) //L-type protection
	UINT32 reg_dj_soft_en                   :1;	//(6:6,NA,1) //Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_dj_count_diff_th             :5;	//(12:8,NA,1) //matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//(18:16,NA,0) //000: normal display (hard decision)	001: direction map	010: edge gain	011: g0 gain	100: g1 gain	101: final gain
	UINT32 reg_dj_buffer_detour_en          :1;	//(19:19,NA,0) //dj buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//(21:20,NA,1) //center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//(22:22,NA,0) //neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//(23:23,NA,0) //dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//(31:24,NA,128) //line-variation threshold for edge-direction decision
	};
}PE_M23_VSD_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2404 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_M23_VSD_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2408 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_M23_VSD_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F240C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_M23_VSD_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2410 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_M23_VSD_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2414 RW 0x0000_0000
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
}PE_M23_VSD_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2418 RW 0x0000_0040
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
}PE_M23_VSD_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F241C RW 0x0015_5550
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
}PE_M23_VSD_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2420 RW 0x0000_0040
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
}PE_M23_VSD_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2424 RW 0x002A_A040
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
}PE_M23_VSD_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2428 RW 0x002A_A040
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
}PE_M23_VSD_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F242C RW 0x000A_A040
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
}PE_M23_VSD_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2430 RW 0x0000_00E4
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
}PE_M23_VSD_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2434 RW 0x0000_5540
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
}PE_M23_VSD_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2438 RW 0x0020_5542
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
}PE_M23_VSD_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F243C RW 0x0008_1508
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
}PE_M23_VSD_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2440 RW 0x0002_0420
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
}PE_M23_VSD_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2444 RW 0x0000_8080
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
}PE_M23_VSD_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2448 RW 0x0000_2A00
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
}PE_M23_VSD_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F244C RW 0x0000_2A00
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
}PE_M23_VSD_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2450 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_M23_VSD_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2454 RW 0x0000_2800
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
}PE_M23_VSD_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2458 RW 0x0005_0A00
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
}PE_M23_VSD_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F245C RW 0x0005_4280
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
}PE_M23_VSD_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2460 RW 0x0005_50A0
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
}PE_M23_VSD_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2464 RW 0x0005_4280
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
}PE_M23_VSD_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2468 RW 0x0005_0A00
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
}PE_M23_VSD_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F246C RW 0x0000_2800
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
}PE_M23_VSD_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2470 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_M23_VSD_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2474 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2478 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F247C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_M23_VSD_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2480 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_M23_VSD_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2490 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2494 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24A0 RW 0x0000_0000
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
}PE_M23_VSD_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24A8 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24B0 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24BC RW 0x10BC_4DB3
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24C0 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24C4 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24C8 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24CC RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24D0 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24D4 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24D8 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24DC RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24E0 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24E4 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24E8 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24EC RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24F0 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24F4 RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24F8 RW 0x00C0_00C0
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F24FC RW 0x8020_8020
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2500 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2504 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2508 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F250C RW 0x28FF_1400
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2510 RW 0x7800_64FF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2514 RW 0x96FF_8200
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2518 RW 0x00F0_FFC8
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F251C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2520 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2524 RW 0x96FF_8200
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2528 RW 0x00F0_FFC8
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F252C RW 0x28FF_1400
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2530 RW 0x7800_64FF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2534 RW 0x00FF_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2538 RW 0x28FF_1400
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CHROMA_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2550 RW 0x0000_2A60
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2554 RW 0x0001_1810
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2558 RW 0x0088_0850
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2560 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_flick_motion_sel             :2;	//(5:4,NA,0) //SHP FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1                           :26;
	};
}PE_M23_VSD_SHP_FRC_FLICK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2564 RW 0x2040_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_FLICK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2568 RW 0x80FF_4080
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_FLICK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F256C RW 0x0000_0080
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_FLICK_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2570 RW 0x0000_0000
	UINT32 reg_frc_blur_en                  :1;	//(0:0,NA,0) //frc blur enable
	UINT32 reg_frc_blur_debug_en            :1;	//(1:1,NA,0) //frc blur debug en
	UINT32 resvd                            :30;
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2574 RW 0x1812_0C06
	UINT32 reg_frc_blur_cnt_th0             :6;	//(5:0,NA,6) //frc blur weight smoothing count threshold, 0
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th1             :6;	//(13:8,NA,12) //frc blur weight smoothing count threshold, 1
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th2             :6;	//(21:16,NA,18) //frc blur weight smoothing count threshold, 2
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th3             :6;	//(29:24,NA,24) //frc blur weight smoothing count threshold, 3
	UINT32 resvd3                           :2;
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2578 RW 0x302A_241E
	UINT32 reg_frc_blur_cnt_th4             :6;	//(5:0,NA,30) //frc blur weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th5             :6;	//(13:8,NA,36) //frc blur weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th6             :6;	//(21:16,NA,42) //frc blur weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th7             :6;	//(29:24,NA,48) //frc blur weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F257C RW 0x8765_4321
	UINT32 reg_frc_blur_val0                :4;	//(3:0,NA,1) //frc blur weight smoothing count value, 0
	UINT32 reg_frc_blur_val1                :4;	//(7:4,NA,2) //frc blur weight smoothing count value, 1
	UINT32 reg_frc_blur_val2                :4;	//(11:8,NA,3) //frc blur weight smoothing count value, 2
	UINT32 reg_frc_blur_val3                :4;	//(15:12,NA,4) //frc blur weight smoothing count value, 3
	UINT32 reg_frc_blur_val4                :4;	//(19:16,NA,5) //frc blur weight smoothing count value, 4
	UINT32 reg_frc_blur_val5                :4;	//(23:20,NA,6) //frc blur weight smoothing count value, 5
	UINT32 reg_frc_blur_val6                :4;	//(27:24,NA,7) //frc blur weight smoothing count value, 6
	UINT32 reg_frc_blur_val7                :4;	//(31:28,NA,8) //frc blur weight smoothing count value, 7
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2580 RW 0x0000_0004
	UINT32 reg_frc_blur_coef_x8             :4;	//(3:0,NA,4) //frc blur filter coeff, x, [8]
	UINT32 resvd                            :28;
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2584 RW 0x4444_4433
	UINT32 reg_frc_blur_coef_x0             :4;	//(3:0,NA,3) //frc blur filter coeff, x, [0]/[16]
	UINT32 reg_frc_blur_coef_x1             :4;	//(7:4,NA,3) //frc blur filter coeff, x, [1]/[15]
	UINT32 reg_frc_blur_coef_x2             :4;	//(11:8,NA,4) //frc blur filter coeff, x, [2]/[14]
	UINT32 reg_frc_blur_coef_x3             :4;	//(15:12,NA,4) //frc blur filter coeff, x, [3]/[13]
	UINT32 reg_frc_blur_coef_x4             :4;	//(19:16,NA,4) //frc blur filter coeff, x, [4]/[12]
	UINT32 reg_frc_blur_coef_x5             :4;	//(23:20,NA,4) //frc blur filter coeff, x, [5]/[11]
	UINT32 reg_frc_blur_coef_x6             :4;	//(27:24,NA,4) //frc blur filter coeff, x, [6]/[10]
	UINT32 reg_frc_blur_coef_x7             :4;	//(31:28,NA,4) //frc blur filter coeff, x, [7]/[9]
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2588 RW 0x0000_0866
	UINT32 reg_frc_blur_coef_y0             :4;	//(3:0,NA,6) //frc blur filter coeff, y, [0]/[4]
	UINT32 reg_frc_blur_coef_y1             :4;	//(7:4,NA,6) //frc blur filter coeff, y, [1]/[3]
	UINT32 reg_frc_blur_coef_y2             :4;	//(11:8,NA,8) //frc blur filter coeff, y, [2]
	UINT32 resvd                            :20;
	};
}PE_M23_VSD_SHP_FRC_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2590 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_HALO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2594 RW 0x1812_0C06
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_HALO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2598 RW 0x302A_241E
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_HALO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F259C RW 0x8765_4321
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FRC_HALO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F25A0 RW 0x0000_0000
	UINT32 reg_win_frc_win0_en              :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_win_frc_win1_en              :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_win_frc_win01_en             :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_frc_win_outside          :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_frc_win_en               :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_frc_bdr_alpha            :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_win_frc_bdr_wid              :2;	//(14:13,NA,0) //border width
	UINT32 reg_win_frc_bdr_en               :1;	//(15:15,NA,0) //border enable
	UINT32 reg_win_frc_cr5                  :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_win_frc_cb5                  :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_win_frc_yy6                  :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_M23_VSD_SHP_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F25A4 RW 0x0000_0000
	UINT32 reg_win_frc_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F25A8 RW 0x086F_0EFF
	UINT32 reg_win_frc_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F25AC RW 0x0000_0000
	UINT32 reg_win_frc_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F25B0 RW 0x086F_0EFF
	UINT32 reg_win_frc_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2600 RW 0x0000_0C00
	UINT32 reg_motion_gain_pic_rptr_man     :2;	//(1:0,NA,0) //
	UINT32 resvd0                           :1;
	UINT32 reg_motion_gain_pic_rptr_man_en  :1;	//(3:3,NA,0) //
	UINT32 reg_motion_gain_pic_wptr_man     :2;	//(5:4,NA,0) //
	UINT32 resvd1                           :1;
	UINT32 reg_motion_gain_pic_wptr_man_en  :1;	//(7:7,NA,0) //
	UINT32 reg_motion_gain_pic_data_man     :2;	//(9:8,NA,0) //0: test data off	1: 128	2: gradient	3: horizontal box
	UINT32 reg_motion_gain_pic_rptr_on      :1;	//(10:10,NA,1) //
	UINT32 reg_motion_gain_pic_wptr_on      :1;	//(11:11,NA,1) //
	UINT32 reg_motion_gain_pic_wd_man       :4;	//(15:12,NA,0) //x16, {reg_pic_wd_man,4'd0}
	UINT32 reg_motion_gain_pic_wd_man_on    :1;	//(16:16,NA,0) //
	UINT32 reg_motion_gain_pic_rd_lsb_man   :2;	//(18:17,NA,0) //0: [1:0] = 0	1: [1:0] = 3	2: [1:0] = [3:2]	3: [1:0] = [9:8]
	UINT32 reg_motion_gain_ro_buf_wrcnt     :10;	//(28:19,NA,0) //
	UINT32 reg_motion_gain_ro_buf_wrsel     :1;	//(29:29,NA,0) //
	UINT32 resvd2                           :2;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2604 RW 0x0000_0000
	UINT32 reg_motion_gain_in_hoffset       :13;	//(12:0,NA,0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_voffset       :12;	//(27:16,NA,0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2608 RW 0x0011_001E
	UINT32 reg_motion_gain_in_hactive       :13;	//(12:0,NA,30) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vactive       :12;	//(27:16,NA,17) //input window active size
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F260C RW 0x0011_001E
	UINT32 reg_motion_gain_in_hsize         :13;	//(12:0,NA,30) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vsize         :12;	//(27:16,NA,17) //input source total size
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2610 RW 0x0870_0780
	UINT32 reg_motion_gain_out_pic_width    :13;	//(12:0,NA,1920) //width (default: 3840/2)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_pic_height   :12;	//(27:16,NA,2160) //height (default: 2160)
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2614 RW 0x8000_3030
	UINT32 reg_motion_gain_phase_off_h      :6;	//(5:0,NA,-16) //vertical offset of initial pixel position (signed value)  	min: -31	max: +31
	UINT32 resvd0                           :2;
	UINT32 reg_motion_gain_phase_off_v      :6;	//(13:8,NA,-16) //horizontal offset of initial pixel position (signed value)  	min: -31	max: +31
	UINT32 resvd1                           :17;
	UINT32 reg_motion_gain_sampling_mode    :1;	//(31:31,NA,1) //0: normal-auto	1: manual-set
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2618 RW 0x0001_0001
	UINT32 reg_motion_gain_numerator_h      :13;	//(12:0,NA,1) //
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_numerator_v      :12;	//(27:16,NA,1) //
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F261C RW 0x0080_0040
	UINT32 reg_motion_gain_denominator_h    :13;	//(12:0,NA,64) //(default: (3840/2)/30)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_denominator_v    :12;	//(27:16,NA,128) //(default: 2160/17 -> 128)
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2620 RW 0x0000_0000
	UINT32 reg_motion_gain_win0_en          :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_motion_gain_win1_en          :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_motion_gain_win01_en         :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_motion_gain_win_outside      :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_motion_gain_win_en           :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_motion_gain_bdr_alpha        :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_motion_gain_bdr_wid          :2;	//(14:13,NA,0) //border width
	UINT32 reg_motion_gain_bdr_en           :1;	//(15:15,NA,0) //border enable
	UINT32 reg_motion_gain_cr5              :5;	//(20:16,NA,0) //border color : cr5
	UINT32 reg_motion_gain_cb5              :5;	//(25:21,NA,0) //border color : cb5
	UINT32 reg_motion_gain_yy6              :6;	//(31:26,NA,0) //border color : yy6
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2624 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x0        :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y0        :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2628 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x1        :12;	//(11:0,NA,0) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y1        :12;	//(27:16,NA,0) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F262C RW 0x0000_0000
	UINT32 reg_motion_gain_out_hoffset      :13;	//(12:0,NA,0) //output window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_voffset      :12;	//(27:16,NA,0) //output window offset
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2630 RW 0x0870_0780
	UINT32 reg_motion_gain_out_hactive      :13;	//(12:0,NA,1920) //output window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_vactive      :12;	//(27:16,NA,2160) //output window active size
	UINT32 resvd1                           :2;
	UINT32 logo_l7sc_out_sel                :2;	//(31:30,NA,0) //0 : logo_l7sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2640 RW 0x0000_0000
	UINT32 reg_motion_prot_adaptive_en      :1;	//(0:0,NA,0) //motion protection enable
	UINT32 resvd                            :31;
	};
}PE_M23_VSD_SHP_MOTION_PROT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2644 RW 0x4040_0000
	UINT32 reg_motion_prot_lut_a_y0         :8;	//(7:0,NA,0) //motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0         :8;	//(15:8,NA,0) //motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1         :8;	//(23:16,NA,64) //motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1         :8;	//(31:24,NA,64) //motion gain LUT, A, x1
	};
}PE_M23_VSD_SHP_MOTION_PROT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2648 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_a_y2         :8;	//(7:0,NA,80) //motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2         :8;	//(15:8,NA,110) //motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3         :8;	//(23:16,NA,120) //motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3         :8;	//(31:24,NA,255) //motion gain LUT, A, x3
	};
}PE_M23_VSD_SHP_MOTION_PROT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F264C RW 0x4040_0000
	UINT32 reg_motion_prot_lut_t_y0         :8;	//(7:0,NA,0) //motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0         :8;	//(15:8,NA,0) //motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1         :8;	//(23:16,NA,64) //motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1         :8;	//(31:24,NA,64) //motion gain LUT, T, x1
	};
}PE_M23_VSD_SHP_MOTION_PROT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2650 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_t_y2         :8;	//(7:0,NA,80) //motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2         :8;	//(15:8,NA,110) //motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3         :8;	//(23:16,NA,120) //motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3         :8;	//(31:24,NA,255) //motion gain LUT, T, x3
	};
}PE_M23_VSD_SHP_MOTION_PROT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2670 RW 0x0000_0000
	UINT32 reg_win_mot_win0_en              :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_win_mot_win1_en              :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_win_mot_win01_en             :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_mot_win_outside          :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_mot_win_en               :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_mot_bdr_alpha            :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_win_mot_bdr_wid              :2;	//(14:13,NA,0) //border width
	UINT32 reg_win_mot_bdr_en               :1;	//(15:15,NA,0) //border enable
	UINT32 reg_win_mot_cr5                  :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_win_mot_cb5                  :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_win_mot_yy6                  :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_M23_VSD_SHP_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2674 RW 0x0000_0000
	UINT32 reg_win_mot_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2678 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F267C RW 0x0000_0000
	UINT32 reg_win_mot_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2680 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2690 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2694 RW 0x4080_005a
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2698 RW 0xc4ff_6090
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F269C RW 0x2080_005a
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26A0 RW 0x90b0_4090
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26A4 RW 0x1090_00ac
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26A8 RW 0x8000_2060
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26AC RW 0x10dc_00c4
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26B0 RW 0x40ff_20dc
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26B4 RW 0x3060_0050
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26B8 RW 0x9080_6080
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26BC RW 0x3060_0050
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F26C0 RW 0x9080_6080
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_OBJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27A0 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27A4 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27A8 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27AC RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27B0 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_M23_VSD_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27B4 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_M23_VSD_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27D0 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27D4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27D8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27DC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27E0 RO 0x0000_0000
	UINT32 ro_buf_rptr                      :2;	//(1:0,NA,0) //
	UINT32 ro_buf_wptr_d                    :2;	//(3:2,NA,0) //
	UINT32 ro_core_wd_ptr                   :2;	//(5:4,NA,0) //
	UINT32 ro_buf_rcnt                      :10;	//(15:6,NA,0) //(reg_ro_buf_wrsel==1) ? {2'd0,r_ro_buf_rd} : r_buf_rcnt
	UINT32 ro_buf_wcnt                      :10;	//(25:16,NA,0) //(reg_ro_buf_wrsel==1) ? {2'd0,r_ro_buf_wd} : r_buf_wcnt
	UINT32 ro_buf_wre_cnt                   :4;	//(29:26,NA,0) //
	UINT32 resvd                            :2;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27E4 RO 0x0000_0000
	UINT32 ro_out_v_line                    :12;	//(11:0,NA,0) //
	UINT32 resvd0                           :4;
	UINT32 ro_in_v_line                     :12;	//(27:16,NA,0) //
	UINT32 resvd1                           :4;
	};
}PE_M23_VSD_SHP_MOTION_GAIN_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27E8 RO 0x0000_0000
	UINT32 ro_edge_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_M23_VSD_SHP_CORE_EDGE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27EC RO 0x0000_0000
	UINT32 ro_edge_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_M23_VSD_SHP_CORE_EDGE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27F0 RO 0x0000_0000
	UINT32 ro_edge_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_M23_VSD_SHP_CORE_EDGE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27F4 RO 0x0000_0000
	UINT32 ro_edge_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_M23_VSD_SHP_CORE_EDGE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27F8 RO 0x0000_0000
	UINT32 ro_edge_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_M23_VSD_SHP_CORE_EDGE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F27FC RO 0x0000_0000
	UINT32 ro_edge_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_11                :16;	//(31:16,NA,0) //
	};
}PE_M23_VSD_SHP_CORE_EDGE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2800 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2804 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2808 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F280C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2810 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2814 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2818 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F281C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2820 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2824 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2828 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F282C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2830 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2834 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2838 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F283C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2840 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2844 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F2848 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F284C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F28F0 RW 0x0000_0000
	UINT32 reg_drc_apb_write_cont			:2; 	//1:0	drc curv update counter
	UINT32 resvd0							:1;
	UINT32 reg_drc_write_cont				:2; 	//4:3	drc curv update counter
	UINT32 resvd1							:3;
	UINT32 reg_pre_norm 					:8; 	//15:8	IWP - iir weight prev norm
	UINT32 reg_cur_norm 					:8; 	//23:16 IWC - iir weight cur  norm
	UINT32 reg_pre_sc						:8; 	//31:24 IWSP - iir weight scene change prev sc
	};
}PE_M23_VSD_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F28F4 RW 0x0000_0000
	UINT32 reg_cur_sc						:8; 	//7:0	IWSC - iir weight scene change cur sc
	UINT32 reg_ui_gain_w					:8; 	//15:8	UGW - ui gain white
	UINT32 reg_ui_gain_b					:8; 	//23:16 UGB - ui gain black
	UINT32 reg_vy_mode						:2; 	//25:24 ui rgb select
	UINT32 resvd0							:6; 	
	};
}PE_M23_VSD_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F28F8 RW 0x0000_0000
	UINT32 reg_obc_debug					  : 2;	// 1:0, 0: shp result	1 : face map   2 : object map
	};
}PE_M23_VSD_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F28FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VSD_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_M23_VSD_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCC4F2000
	PE_M23_VSD_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCC4F2004
	PE_M23_VSD_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCC4F2008
	PE_M23_VSD_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCC4F200C
	PE_M23_VSD_SHP_CORE_CTRL_04_T                     shp_core_ctrl_04;	//0xCC4F2010
	PE_M23_VSD_SHP_NEW_FD_CTRL_00_T                 shp_new_fd_ctrl_00;	//0xCC4F2014
	PE_M23_VSD_SHP_NEW_FD_CTRL_01_T                 shp_new_fd_ctrl_01;	//0xCC4F2018
	PE_M23_VSD_SHP_NEW_FD_CTRL_02_T                 shp_new_fd_ctrl_02;	//0xCC4F201C
	PE_M23_VSD_SHP_NEW_FD_CTRL_03_T                 shp_new_fd_ctrl_03;	//0xCC4F2020
	PE_M23_VSD_SHP_NEW_FD_CTRL_04_T                 shp_new_fd_ctrl_04;	//0xCC4F2024
	PE_M23_VSD_SHP_TEXT_REGION_MAP_00_T         shp_text_region_map_00;	//0xCC4F2028
	UINT32                                                    reserved0;	//0xCC4F202C
	UINT32                                                    reserved1;	//0xCC4F2030
	UINT32                                                    reserved2;	//0xCC4F2034
	UINT32                                                    reserved3;	//0xCC4F2038
	UINT32                                                    reserved4;	//0xCC4F203C
	PE_M23_VSD_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCC4F2040
	UINT32                                                    reserved5;	//0xCC4F2044
	UINT32                                                    reserved6;	//0xCC4F2048
	UINT32                                                    reserved7;	//0xCC4F204C
	PE_M23_VSD_SHP_GOS_CTRL_00_T                       shp_gos_ctrl_00;	//0xCC4F2050
	UINT32                                                    reserved8;	//0xCC4F2054
	UINT32                                                    reserved9;	//0xCC4F2058
	UINT32                                                   reserved10;	//0xCC4F205C
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_00_T             shp_sync_dly_ctrl_00;	//0xCC4F2060
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_01_T             shp_sync_dly_ctrl_01;	//0xCC4F2064
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_02_T             shp_sync_dly_ctrl_02;	//0xCC4F2068
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_03_T             shp_sync_dly_ctrl_03;	//0xCC4F206C
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_04_T             shp_sync_dly_ctrl_04;	//0xCC4F2070
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_05_T             shp_sync_dly_ctrl_05;	//0xCC4F2074
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_06_T             shp_sync_dly_ctrl_06;	//0xCC4F2078
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_07_T             shp_sync_dly_ctrl_07;	//0xCC4F207C
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_08_T             shp_sync_dly_ctrl_08;	//0xCC4F2080
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_09_T             shp_sync_dly_ctrl_09;	//0xCC4F2084
	PE_M23_VSD_SHP_SYNC_DLY_CTRL_0A_T             shp_sync_dly_ctrl_0a;	//0xCC4F2088
	UINT32                                                   reserved11;	//0xCC4F208C
	PE_M23_VSD_SHP_ROI_MASK_CTRL_00_T             shp_roi_mask_ctrl_00;	//0xCC4F2090
	PE_M23_VSD_SHP_ROI_MASK_CTRL_01_T             shp_roi_mask_ctrl_01;	//0xCC4F2094
	PE_M23_VSD_SHP_ROI_MASK_CTRL_02_T             shp_roi_mask_ctrl_02;	//0xCC4F2098
	UINT32                                                   reserved12;	//0xCC4F209C
	PE_M23_VSD_SHP_ESF_CTRL_00_T                       shp_esf_ctrl_00;	//0xCC4F20A0
	PE_M23_VSD_SHP_ESF_CTRL_01_T                       shp_esf_ctrl_01;	//0xCC4F20A4
	PE_M23_VSD_SHP_ESF_CTRL_02_T                       shp_esf_ctrl_02;	//0xCC4F20A8
	UINT32                                                   reserved13;	//0xCC4F20AC
	PE_M23_VSD_SHP_ESF_WIN_CTRL_00_T               shp_esf_win_ctrl_00;	//0xCC4F20B0
	PE_M23_VSD_SHP_ESF_WIN_CTRL_01_T               shp_esf_win_ctrl_01;	//0xCC4F20B4
	PE_M23_VSD_SHP_ESF_WIN_CTRL_02_T               shp_esf_win_ctrl_02;	//0xCC4F20B8
	PE_M23_VSD_SHP_ESF_WIN_CTRL_03_T               shp_esf_win_ctrl_03;	//0xCC4F20BC
	PE_M23_VSD_SHP_ESF_WIN_CTRL_04_T               shp_esf_win_ctrl_04;	//0xCC4F20C0
	UINT32                                                   reserved14;	//0xCC4F20C4
	UINT32                                                   reserved15;	//0xCC4F20C8
	UINT32                                                   reserved16;	//0xCC4F20CC
	UINT32                                                   reserved17;	//0xCC4F20D0
	UINT32                                                   reserved18;	//0xCC4F20D4
	UINT32                                                   reserved19;	//0xCC4F20D8
	UINT32                                                   reserved20;	//0xCC4F20DC
	UINT32                                                   reserved21;	//0xCC4F20E0
	UINT32                                                   reserved22;	//0xCC4F20E4
	UINT32                                                   reserved23;	//0xCC4F20E8
	UINT32                                                   reserved24;	//0xCC4F20EC
	PE_M23_VSD_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCC4F20F0
	UINT32                                                   reserved25;	//0xCC4F20F4
	UINT32                                                   reserved26;	//0xCC4F20F8
	UINT32                                                   reserved27;	//0xCC4F20FC
	PE_M23_VSD_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCC4F2100
	PE_M23_VSD_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCC4F2104
	PE_M23_VSD_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCC4F2108
	PE_M23_VSD_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCC4F210C
	PE_M23_VSD_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCC4F2110
	PE_M23_VSD_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCC4F2114
	PE_M23_VSD_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCC4F2118
	PE_M23_VSD_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCC4F211C
	PE_M23_VSD_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCC4F2120
	PE_M23_VSD_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCC4F2124
	PE_M23_VSD_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCC4F2128
	PE_M23_VSD_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCC4F212C
	PE_M23_VSD_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCC4F2130
	PE_M23_VSD_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCC4F2134
	PE_M23_VSD_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCC4F2138
	PE_M23_VSD_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCC4F213C
	PE_M23_VSD_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCC4F2140
	PE_M23_VSD_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCC4F2144
	PE_M23_VSD_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCC4F2148
	PE_M23_VSD_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCC4F214C
	PE_M23_VSD_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCC4F2150
	PE_M23_VSD_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCC4F2154
	PE_M23_VSD_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCC4F2158
	UINT32                                                   reserved28;	//0xCC4F215C
	PE_M23_VSD_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCC4F2160
	PE_M23_VSD_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCC4F2164
	PE_M23_VSD_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCC4F2168
	PE_M23_VSD_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCC4F216C
	PE_M23_VSD_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCC4F2170
	PE_M23_VSD_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCC4F2174
	PE_M23_VSD_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCC4F2178
	PE_M23_VSD_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCC4F217C
	PE_M23_VSD_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCC4F2180
	PE_M23_VSD_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCC4F2184
	PE_M23_VSD_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCC4F2188
	PE_M23_VSD_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCC4F218C
	PE_M23_VSD_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCC4F2190
	PE_M23_VSD_SHP_APL_CTRL_00_T                       shp_apl_ctrl_00;	//0xCC4F2194
	UINT32                                                   reserved29;	//0xCC4F2198
	UINT32                                                   reserved30;	//0xCC4F219C
	PE_M23_VSD_SHP_LC_CTRL_00_T                         shp_lc_ctrl_00;	//0xCC4F21A0
	PE_M23_VSD_SHP_LC_CTRL_01_T                         shp_lc_ctrl_01;	//0xCC4F21A4
	PE_M23_VSD_SHP_LC_CTRL_02_T                         shp_lc_ctrl_02;	//0xCC4F21A8
	PE_M23_VSD_SHP_LC_CTRL_03_T                         shp_lc_ctrl_03;	//0xCC4F21AC
	PE_M23_VSD_SHP_LC_CTRL_04_T                         shp_lc_ctrl_04;	//0xCC4F21B0
	UINT32                                                   reserved31;	//0xCC4F21B4
	UINT32                                                   reserved32;	//0xCC4F21B8
	UINT32                                                   reserved33;	//0xCC4F21BC
	PE_M23_VSD_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCC4F21C0
	PE_M23_VSD_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCC4F21C4
	PE_M23_VSD_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCC4F21C8
	PE_M23_VSD_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCC4F21CC
	PE_M23_VSD_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCC4F21D0
	PE_M23_VSD_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCC4F21D4
	PE_M23_VSD_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCC4F21D8
	PE_M23_VSD_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCC4F21DC
	PE_M23_VSD_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCC4F21E0
	PE_M23_VSD_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCC4F21E4
	PE_M23_VSD_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCC4F21E8
	PE_M23_VSD_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCC4F21EC
	PE_M23_VSD_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCC4F21F0
	PE_M23_VSD_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCC4F21F4
	PE_M23_VSD_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCC4F21F8
	PE_M23_VSD_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCC4F21FC
	PE_M23_VSD_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCC4F2200
	PE_M23_VSD_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCC4F2204
	PE_M23_VSD_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCC4F2208
	PE_M23_VSD_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCC4F220C
	PE_M23_VSD_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCC4F2210
	UINT32                                                   reserved34;	//0xCC4F2214
	UINT32                                                   reserved35;	//0xCC4F2218
	UINT32                                                   reserved36;	//0xCC4F221C
	PE_M23_VSD_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCC4F2220
	PE_M23_VSD_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCC4F2224
	PE_M23_VSD_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCC4F2228
	PE_M23_VSD_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCC4F222C
	PE_M23_VSD_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCC4F2230
	UINT32                                                   reserved37;	//0xCC4F2234
	UINT32                                                   reserved38;	//0xCC4F2238
	UINT32                                                   reserved39;	//0xCC4F223C
	PE_M23_VSD_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCC4F2240
	PE_M23_VSD_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCC4F2244
	PE_M23_VSD_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCC4F2248
	PE_M23_VSD_SHP_TGEN_CTRL_03_C0_T               shp_tgen_ctrl_03_c0;	//0xCC4F224C
	PE_M23_VSD_SHP_TGEN_CTRL_03_C1_T               shp_tgen_ctrl_03_c1;	//0xCC4F2250
	PE_M23_VSD_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCC4F2254
	PE_M23_VSD_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCC4F2258
	PE_M23_VSD_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCC4F225C
	PE_M23_VSD_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCC4F2260
	PE_M23_VSD_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCC4F2264
	PE_M23_VSD_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCC4F2268
	PE_M23_VSD_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCC4F226C
	PE_M23_VSD_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCC4F2270
	PE_M23_VSD_SHP_SNR_CTRL_00_T                       shp_snr_ctrl_00;	//0xCC4F2274
	UINT32                                                   reserved40;	//0xCC4F2278
	UINT32                                                   reserved41;	//0xCC4F227C
	PE_M23_VSD_SHP_DCTP_CTRL_00_T                     shp_dctp_ctrl_00;	//0xCC4F2280
	PE_M23_VSD_SHP_DCTP_CTRL_01_T                     shp_dctp_ctrl_01;	//0xCC4F2284
	PE_M23_VSD_SHP_DCTP_CTRL_02_T                     shp_dctp_ctrl_02;	//0xCC4F2288
	PE_M23_VSD_SHP_DCTP_CTRL_03_T                     shp_dctp_ctrl_03;	//0xCC4F228C
	PE_M23_VSD_SHP_DCTP_CTRL_04_T                     shp_dctp_ctrl_04;	//0xCC4F2290
	PE_M23_VSD_SHP_DCTP_CTRL_05_T                     shp_dctp_ctrl_05;	//0xCC4F2294
	PE_M23_VSD_SHP_DCTP_CTRL_06_T                     shp_dctp_ctrl_06;	//0xCC4F2298
	PE_M23_VSD_SHP_DCTP_CTRL_07_T                     shp_dctp_ctrl_07;	//0xCC4F229C
	PE_M23_VSD_SHP_DCTP_CTRL_08_T                     shp_dctp_ctrl_08;	//0xCC4F22A0
	PE_M23_VSD_SHP_DCTP_CTRL_09_T                     shp_dctp_ctrl_09;	//0xCC4F22A4
	PE_M23_VSD_SHP_DCTP_CTRL_0A_T                     shp_dctp_ctrl_0a;	//0xCC4F22A8
	PE_M23_VSD_SHP_DCTP_CTRL_0B_T                     shp_dctp_ctrl_0b;	//0xCC4F22AC
	PE_M23_VSD_SHP_DCTP_CTRL_0C_T                     shp_dctp_ctrl_0c;	//0xCC4F22B0
	PE_M23_VSD_SHP_DCTP_CTRL_0D_T                     shp_dctp_ctrl_0d;	//0xCC4F22B4
	PE_M23_VSD_SHP_DCTP_CTRL_0E_T                     shp_dctp_ctrl_0e;	//0xCC4F22B8
	PE_M23_VSD_SHP_DCTP_CTRL_0F_T                     shp_dctp_ctrl_0f;	//0xCC4F22BC
	PE_M23_VSD_SHP_DCTP_CTRL_10_T                     shp_dctp_ctrl_10;	//0xCC4F22C0
	PE_M23_VSD_SHP_DCTP_CTRL_11_T                     shp_dctp_ctrl_11;	//0xCC4F22C4
	PE_M23_VSD_SHP_DCTP_CTRL_12_T                     shp_dctp_ctrl_12;	//0xCC4F22C8
	PE_M23_VSD_SHP_DCTP_CTRL_13_T                     shp_dctp_ctrl_13;	//0xCC4F22CC
	PE_M23_VSD_SHP_DCTP_CTRL_14_T                     shp_dctp_ctrl_14;	//0xCC4F22D0
	PE_M23_VSD_SHP_DCTP_CTRL_15_T                     shp_dctp_ctrl_15;	//0xCC4F22D4
	PE_M23_VSD_SHP_DCTP_CTRL_16_T                     shp_dctp_ctrl_16;	//0xCC4F22D8
	PE_M23_VSD_SHP_DCTP_CTRL_17_T                     shp_dctp_ctrl_17;	//0xCC4F22DC
	PE_M23_VSD_SHP_DCTP_CTRL_18_T                     shp_dctp_ctrl_18;	//0xCC4F22E0
	PE_M23_VSD_SHP_DCTP_CTRL_19_T                     shp_dctp_ctrl_19;	//0xCC4F22E4
	PE_M23_VSD_SHP_DCTP_CTRL_1A_T                     shp_dctp_ctrl_1a;	//0xCC4F22E8
	PE_M23_VSD_SHP_DCTP_CTRL_1B_T                     shp_dctp_ctrl_1b;	//0xCC4F22EC
	PE_M23_VSD_SHP_DCTP_CTRL_1C_T                     shp_dctp_ctrl_1c;	//0xCC4F22F0
	PE_M23_VSD_SHP_DCTP_CTRL_1D_T                     shp_dctp_ctrl_1d;	//0xCC4F22F4
	PE_M23_VSD_SHP_DCTP_CTRL_1E_T                     shp_dctp_ctrl_1e;	//0xCC4F22F8
	PE_M23_VSD_SHP_DCTP_CTRL_1F_T                     shp_dctp_ctrl_1f;	//0xCC4F22FC
	PE_M23_VSD_SHP_NNTG_CTRL_00_T                     shp_nntg_ctrl_00;	//0xCC4F2300
	PE_M23_VSD_SHP_NNTG_CTRL_01_C0_T               shp_nntg_ctrl_01_c0;	//0xCC4F2304
	PE_M23_VSD_SHP_NNTG_CTRL_02_C0_T               shp_nntg_ctrl_02_c0;	//0xCC4F2308
	PE_M23_VSD_SHP_NNTG_CTRL_03_C0_T               shp_nntg_ctrl_03_c0;	//0xCC4F230C
	PE_M23_VSD_SHP_NNTG_CTRL_04_C0_T               shp_nntg_ctrl_04_c0;	//0xCC4F2310
	PE_M23_VSD_SHP_NNTG_CTRL_05_C0_T               shp_nntg_ctrl_05_c0;	//0xCC4F2314
	PE_M23_VSD_SHP_NNTG_CTRL_01_C1_T               shp_nntg_ctrl_01_c1;	//0xCC4F2318
	PE_M23_VSD_SHP_NNTG_CTRL_02_C1_T               shp_nntg_ctrl_02_c1;	//0xCC4F231C
	PE_M23_VSD_SHP_NNTG_CTRL_03_C1_T               shp_nntg_ctrl_03_c1;	//0xCC4F2320
	PE_M23_VSD_SHP_NNTG_CTRL_04_C1_T               shp_nntg_ctrl_04_c1;	//0xCC4F2324
	PE_M23_VSD_SHP_NNTG_CTRL_05_C1_T               shp_nntg_ctrl_05_c1;	//0xCC4F2328
	PE_M23_VSD_SHP_NNTG_CTRL_06_T                     shp_nntg_ctrl_06;	//0xCC4F232C
	PE_M23_VSD_SHP_NNTG_CTRL_07_T                     shp_nntg_ctrl_07;	//0xCC4F2330
	PE_M23_VSD_SHP_NNTG_CTRL_08_T                     shp_nntg_ctrl_08;	//0xCC4F2334
	PE_M23_VSD_SHP_NNTG_CTRL_09_T                     shp_nntg_ctrl_09;	//0xCC4F2338
	PE_M23_VSD_SHP_NNTG_CTRL_0A_T                     shp_nntg_ctrl_0a;	//0xCC4F233C
	PE_M23_VSD_SHP_NNTG_CTRL_0B_T                     shp_nntg_ctrl_0b;	//0xCC4F2340
	PE_M23_VSD_SHP_NNTG_CTRL_0C_T                     shp_nntg_ctrl_0c;	//0xCC4F2344
	PE_M23_VSD_SHP_NNTG_CTRL_0D_T                     shp_nntg_ctrl_0d;	//0xCC4F2348
	PE_M23_VSD_SHP_NNTG_CTRL_0E_T                     shp_nntg_ctrl_0e;	//0xCC4F234C
	PE_M23_VSD_SHP_NNTG_CTRL_0F_T                     shp_nntg_ctrl_0f;	//0xCC4F2350
	PE_M23_VSD_SHP_NNTG_CTRL_10_T                     shp_nntg_ctrl_10;	//0xCC4F2354
	UINT32                                                   reserved42;	//0xCC4F2358
	UINT32                                                   reserved43;	//0xCC4F235C
	PE_M23_VSD_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCC4F2360
	PE_M23_VSD_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCC4F2364
	PE_M23_VSD_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCC4F2368
	PE_M23_VSD_SHP_DP_SUM_CTRL_03_T                 shp_dp_sum_ctrl_03;	//0xCC4F236C
	PE_M23_VSD_SHP_DP_SUM_CTRL_04_T                 shp_dp_sum_ctrl_04;	//0xCC4F2370
	PE_M23_VSD_SHP_DP_SUM_CTRL_05_T                 shp_dp_sum_ctrl_05;	//0xCC4F2374
	PE_M23_VSD_SHP_DP_SUM_CTRL_06_T                 shp_dp_sum_ctrl_06;	//0xCC4F2378
	PE_M23_VSD_SHP_DP_SUM_CTRL_07_T                 shp_dp_sum_ctrl_07;	//0xCC4F237C
	PE_M23_VSD_SHP_DP_SUM_CTRL_08_T                 shp_dp_sum_ctrl_08;	//0xCC4F2380
	PE_M23_VSD_SHP_DP_SUM_CTRL_09_T                 shp_dp_sum_ctrl_09;	//0xCC4F2384
	PE_M23_VSD_SHP_DP_SUM_CTRL_0A_T                 shp_dp_sum_ctrl_0a;	//0xCC4F2388
	UINT32                                                   reserved44;	//0xCC4F238C
	PE_M23_VSD_SHP_PSP_CTRL_00_T                       shp_psp_ctrl_00;	//0xCC4F2390
	PE_M23_VSD_SHP_DP_SUM_CTRL_0B_T                 shp_dp_sum_ctrl_0b;	//0xCC4F2394
	PE_M23_VSD_SHP_DP_SUM_CTRL_0C_T                 shp_dp_sum_ctrl_0c;	//0xCC4F2398
	UINT32                                                   reserved45;	//0xCC4F239C
	PE_M23_VSD_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCC4F23A0
	PE_M23_VSD_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCC4F23A4
	PE_M23_VSD_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCC4F23A8
	PE_M23_VSD_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCC4F23AC
	PE_M23_VSD_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCC4F23B0
	UINT32                                                   reserved46;	//0xCC4F23B4
	UINT32                                                   reserved47;	//0xCC4F23B8
	UINT32                                                   reserved48;	//0xCC4F23BC
	PE_M23_VSD_SHP_FD_REGION_TEXT_00_T           shp_fd_region_text_00;	//0xCC4F23C0
	PE_M23_VSD_SHP_FD_REGION_TEXT_01_T           shp_fd_region_text_01;	//0xCC4F23C4
	PE_M23_VSD_SHP_FD_REGION_TEXT_02_T           shp_fd_region_text_02;	//0xCC4F23C8
	PE_M23_VSD_SHP_FD_TMAP_TEMP_00_T               shp_fd_tmap_temp_00;	//0xCC4F23CC
	PE_M23_VSD_SHP_FD_TMAP_TEMP_01_T               shp_fd_tmap_temp_01;	//0xCC4F23D0
	PE_M23_VSD_SHP_FD_TMAP_TEMP_02_T               shp_fd_tmap_temp_02;	//0xCC4F23D4
	PE_M23_VSD_SHP_FD_TMAP_TEMP_03_T               shp_fd_tmap_temp_03;	//0xCC4F23D8
	PE_M23_VSD_SHP_FD_TMAP_TEMP_04_T               shp_fd_tmap_temp_04;	//0xCC4F23DC
	PE_M23_VSD_SHP_FD_TMAP_TEMP_05_T               shp_fd_tmap_temp_05;	//0xCC4F23E0
	PE_M23_VSD_SHP_FD_TMAP_TEMP_06_T               shp_fd_tmap_temp_06;	//0xCC4F23E4
	PE_M23_VSD_SHP_FD_TMAP_TEMP_07_T               shp_fd_tmap_temp_07;	//0xCC4F23E8
	PE_M23_VSD_SHP_FD_TMAP_TEMP_08_T               shp_fd_tmap_temp_08;	//0xCC4F23EC
	PE_M23_VSD_SHP_FD_TMAP_TEMP_09_T               shp_fd_tmap_temp_09;	//0xCC4F23F0
	PE_M23_VSD_SHP_FD_TMAP_TEMP_0A_T               shp_fd_tmap_temp_0a;	//0xCC4F23F4
	PE_M23_VSD_SHP_FD_TMAP_TEMP_0B_T               shp_fd_tmap_temp_0b;	//0xCC4F23F8
	PE_M23_VSD_SHP_FD_TMAP_TEMP_0C_T               shp_fd_tmap_temp_0c;	//0xCC4F23FC
	PE_M23_VSD_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0xCC4F2400
	PE_M23_VSD_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0xCC4F2404
	PE_M23_VSD_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0xCC4F2408
	PE_M23_VSD_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0xCC4F240C
	PE_M23_VSD_SHP_DJ_CTRL_04_T                         shp_dj_ctrl_04;	//0xCC4F2410
	PE_M23_VSD_SHP_DJ_CTRL_05_T                         shp_dj_ctrl_05;	//0xCC4F2414
	PE_M23_VSD_SHP_DJ_CTRL_06_T                         shp_dj_ctrl_06;	//0xCC4F2418
	PE_M23_VSD_SHP_DJ_CTRL_07_T                         shp_dj_ctrl_07;	//0xCC4F241C
	PE_M23_VSD_SHP_DJ_CTRL_08_T                         shp_dj_ctrl_08;	//0xCC4F2420
	PE_M23_VSD_SHP_DJ_CTRL_09_T                         shp_dj_ctrl_09;	//0xCC4F2424
	PE_M23_VSD_SHP_DJ_CTRL_0A_T                         shp_dj_ctrl_0a;	//0xCC4F2428
	PE_M23_VSD_SHP_DJ_CTRL_0B_T                         shp_dj_ctrl_0b;	//0xCC4F242C
	PE_M23_VSD_SHP_DJ_CTRL_0C_T                         shp_dj_ctrl_0c;	//0xCC4F2430
	PE_M23_VSD_SHP_DJ_CTRL_0D_T                         shp_dj_ctrl_0d;	//0xCC4F2434
	PE_M23_VSD_SHP_DJ_CTRL_0E_T                         shp_dj_ctrl_0e;	//0xCC4F2438
	PE_M23_VSD_SHP_DJ_CTRL_0F_T                         shp_dj_ctrl_0f;	//0xCC4F243C
	PE_M23_VSD_SHP_DJ_CTRL_10_T                         shp_dj_ctrl_10;	//0xCC4F2440
	PE_M23_VSD_SHP_DJ_CTRL_11_T                         shp_dj_ctrl_11;	//0xCC4F2444
	PE_M23_VSD_SHP_DJ_CTRL_12_T                         shp_dj_ctrl_12;	//0xCC4F2448
	PE_M23_VSD_SHP_DJ_CTRL_13_T                         shp_dj_ctrl_13;	//0xCC4F244C
	PE_M23_VSD_SHP_DJ_CTRL_14_T                         shp_dj_ctrl_14;	//0xCC4F2450
	PE_M23_VSD_SHP_DJ_CTRL_15_T                         shp_dj_ctrl_15;	//0xCC4F2454
	PE_M23_VSD_SHP_DJ_CTRL_16_T                         shp_dj_ctrl_16;	//0xCC4F2458
	PE_M23_VSD_SHP_DJ_CTRL_17_T                         shp_dj_ctrl_17;	//0xCC4F245C
	PE_M23_VSD_SHP_DJ_CTRL_18_T                         shp_dj_ctrl_18;	//0xCC4F2460
	PE_M23_VSD_SHP_DJ_CTRL_19_T                         shp_dj_ctrl_19;	//0xCC4F2464
	PE_M23_VSD_SHP_DJ_CTRL_1A_T                         shp_dj_ctrl_1a;	//0xCC4F2468
	PE_M23_VSD_SHP_DJ_CTRL_1B_T                         shp_dj_ctrl_1b;	//0xCC4F246C
	PE_M23_VSD_SHP_DJ_CTRL_1C_T                         shp_dj_ctrl_1c;	//0xCC4F2470
	PE_M23_VSD_SHP_DJ_CTRL_1D_T                         shp_dj_ctrl_1d;	//0xCC4F2474
	PE_M23_VSD_SHP_DJ_CTRL_1E_T                         shp_dj_ctrl_1e;	//0xCC4F2478
	PE_M23_VSD_SHP_DJ_CTRL_1F_T                         shp_dj_ctrl_1f;	//0xCC4F247C
	PE_M23_VSD_SHP_DJ_CTRL_20_T                         shp_dj_ctrl_20;	//0xCC4F2480
	UINT32                                                   reserved49;	//0xCC4F2484
	UINT32                                                   reserved50;	//0xCC4F2488
	UINT32                                                   reserved51;	//0xCC4F248C
	PE_M23_VSD_SHP_DB_CTRL_00_T                         shp_db_ctrl_00;	//0xCC4F2490
	PE_M23_VSD_SHP_DB_CTRL_01_T                         shp_db_ctrl_01;	//0xCC4F2494
	UINT32                                                   reserved52;	//0xCC4F2498
	UINT32                                                   reserved53;	//0xCC4F249C
	PE_M23_VSD_SHP_DJ_WIN_CTRL_00_T                 shp_dj_win_ctrl_00;	//0xCC4F24A0
	PE_M23_VSD_SHP_DJ_WIN_CTRL_01_T                 shp_dj_win_ctrl_01;	//0xCC4F24A4
	PE_M23_VSD_SHP_DJ_WIN_CTRL_02_T                 shp_dj_win_ctrl_02;	//0xCC4F24A8
	PE_M23_VSD_SHP_DJ_WIN_CTRL_03_T                 shp_dj_win_ctrl_03;	//0xCC4F24AC
	PE_M23_VSD_SHP_DJ_WIN_CTRL_04_T                 shp_dj_win_ctrl_04;	//0xCC4F24B0
	UINT32                                                   reserved54;	//0xCC4F24B4
	UINT32                                                   reserved55;	//0xCC4F24B8
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_00_T     shp_dj_text_gain_ctrl_00;	//0xCC4F24BC
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_01_T     shp_dj_text_gain_ctrl_01;	//0xCC4F24C0
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_02_T     shp_dj_text_gain_ctrl_02;	//0xCC4F24C4
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_03_T     shp_dj_text_gain_ctrl_03;	//0xCC4F24C8
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_04_T     shp_dj_text_gain_ctrl_04;	//0xCC4F24CC
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_05_T     shp_dj_text_gain_ctrl_05;	//0xCC4F24D0
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_06_T     shp_dj_text_gain_ctrl_06;	//0xCC4F24D4
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_07_T     shp_dj_text_gain_ctrl_07;	//0xCC4F24D8
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_08_T     shp_dj_text_gain_ctrl_08;	//0xCC4F24DC
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_09_T     shp_dj_text_gain_ctrl_09;	//0xCC4F24E0
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_10_T     shp_dj_text_gain_ctrl_10;	//0xCC4F24E4
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_11_T     shp_dj_text_gain_ctrl_11;	//0xCC4F24E8
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_12_T     shp_dj_text_gain_ctrl_12;	//0xCC4F24EC
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_13_T     shp_dj_text_gain_ctrl_13;	//0xCC4F24F0
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_14_T     shp_dj_text_gain_ctrl_14;	//0xCC4F24F4
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_15_T     shp_dj_text_gain_ctrl_15;	//0xCC4F24F8
	PE_M23_VSD_SHP_DJ_TEXT_GAIN_CTRL_16_T     shp_dj_text_gain_ctrl_16;	//0xCC4F24FC
	PE_M23_VSD_SHP_CHROMA_CTRL_00_T                 shp_chroma_ctrl_00;	//0xCC4F2500
	PE_M23_VSD_SHP_CHROMA_CTRL_01_T                 shp_chroma_ctrl_01;	//0xCC4F2504
	PE_M23_VSD_SHP_CHROMA_CTRL_02_T                 shp_chroma_ctrl_02;	//0xCC4F2508
	PE_M23_VSD_SHP_CHROMA_CTRL_03_T                 shp_chroma_ctrl_03;	//0xCC4F250C
	PE_M23_VSD_SHP_CHROMA_CTRL_04_T                 shp_chroma_ctrl_04;	//0xCC4F2510
	PE_M23_VSD_SHP_CHROMA_CTRL_05_T                 shp_chroma_ctrl_05;	//0xCC4F2514
	PE_M23_VSD_SHP_CHROMA_CTRL_06_T                 shp_chroma_ctrl_06;	//0xCC4F2518
	PE_M23_VSD_SHP_CHROMA_CTRL_07_T                 shp_chroma_ctrl_07;	//0xCC4F251C
	PE_M23_VSD_SHP_CHROMA_CTRL_08_T                 shp_chroma_ctrl_08;	//0xCC4F2520
	PE_M23_VSD_SHP_CHROMA_CTRL_09_T                 shp_chroma_ctrl_09;	//0xCC4F2524
	PE_M23_VSD_SHP_CHROMA_CTRL_0A_T                 shp_chroma_ctrl_0a;	//0xCC4F2528
	PE_M23_VSD_SHP_CHROMA_CTRL_0B_T                 shp_chroma_ctrl_0b;	//0xCC4F252C
	PE_M23_VSD_SHP_CHROMA_CTRL_0C_T                 shp_chroma_ctrl_0c;	//0xCC4F2530
	PE_M23_VSD_SHP_CHROMA_CTRL_0D_T                 shp_chroma_ctrl_0d;	//0xCC4F2534
	PE_M23_VSD_SHP_CHROMA_CTRL_0E_T                 shp_chroma_ctrl_0e;	//0xCC4F2538
	UINT32                                                   reserved56;	//0xCC4F253C
	UINT32                                                   reserved57;	//0xCC4F2540
	UINT32                                                   reserved58;	//0xCC4F2544
	UINT32                                                   reserved59;	//0xCC4F2548
	UINT32                                                   reserved60;	//0xCC4F254C
	PE_M23_VSD_SHP_CTI_CTRL_00_T                       shp_cti_ctrl_00;	//0xCC4F2550
	PE_M23_VSD_SHP_CTI_CTRL_01_T                       shp_cti_ctrl_01;	//0xCC4F2554
	PE_M23_VSD_SHP_CTI_CTRL_02_T                       shp_cti_ctrl_02;	//0xCC4F2558
	UINT32                                                   reserved61;	//0xCC4F255C
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_00_T           shp_frc_flick_ctrl_00;	//0xCC4F2560
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_01_T           shp_frc_flick_ctrl_01;	//0xCC4F2564
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_02_T           shp_frc_flick_ctrl_02;	//0xCC4F2568
	PE_M23_VSD_SHP_FRC_FLICK_CTRL_03_T           shp_frc_flick_ctrl_03;	//0xCC4F256C
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_00_T             shp_frc_blur_ctrl_00;	//0xCC4F2570
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_01_T             shp_frc_blur_ctrl_01;	//0xCC4F2574
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_02_T             shp_frc_blur_ctrl_02;	//0xCC4F2578
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_03_T             shp_frc_blur_ctrl_03;	//0xCC4F257C
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_04_T             shp_frc_blur_ctrl_04;	//0xCC4F2580
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_05_T             shp_frc_blur_ctrl_05;	//0xCC4F2584
	PE_M23_VSD_SHP_FRC_BLUR_CTRL_06_T             shp_frc_blur_ctrl_06;	//0xCC4F2588
	UINT32                                                   reserved62;	//0xCC4F258C
	PE_M23_VSD_SHP_FRC_HALO_CTRL_00_T             shp_frc_halo_ctrl_00;	//0xCC4F2590
	PE_M23_VSD_SHP_FRC_HALO_CTRL_01_T             shp_frc_halo_ctrl_01;	//0xCC4F2594
	PE_M23_VSD_SHP_FRC_HALO_CTRL_02_T             shp_frc_halo_ctrl_02;	//0xCC4F2598
	PE_M23_VSD_SHP_FRC_HALO_CTRL_03_T             shp_frc_halo_ctrl_03;	//0xCC4F259C
	PE_M23_VSD_SHP_FRC_WIN_CTRL_00_T               shp_frc_win_ctrl_00;	//0xCC4F25A0
	PE_M23_VSD_SHP_FRC_WIN_CTRL_01_T               shp_frc_win_ctrl_01;	//0xCC4F25A4
	PE_M23_VSD_SHP_FRC_WIN_CTRL_02_T               shp_frc_win_ctrl_02;	//0xCC4F25A8
	PE_M23_VSD_SHP_FRC_WIN_CTRL_03_T               shp_frc_win_ctrl_03;	//0xCC4F25AC
	PE_M23_VSD_SHP_FRC_WIN_CTRL_04_T               shp_frc_win_ctrl_04;	//0xCC4F25B0
	UINT32                                                   reserved63;	//0xCC4F25B4
	UINT32                                                   reserved64;	//0xCC4F25B8
	UINT32                                                   reserved65;	//0xCC4F25BC
	UINT32                                                   reserved66;	//0xCC4F25C0
	UINT32                                                   reserved67;	//0xCC4F25C4
	UINT32                                                   reserved68;	//0xCC4F25C8
	UINT32                                                   reserved69;	//0xCC4F25CC
	UINT32                                                   reserved70;	//0xCC4F25D0
	UINT32                                                   reserved71;	//0xCC4F25D4
	UINT32                                                   reserved72;	//0xCC4F25D8
	UINT32                                                   reserved73;	//0xCC4F25DC
	UINT32                                                   reserved74;	//0xCC4F25E0
	UINT32                                                   reserved75;	//0xCC4F25E4
	UINT32                                                   reserved76;	//0xCC4F25E8
	UINT32                                                   reserved77;	//0xCC4F25EC
	UINT32                                                   reserved78;	//0xCC4F25F0
	UINT32                                                   reserved79;	//0xCC4F25F4
	UINT32                                                   reserved80;	//0xCC4F25F8
	UINT32                                                   reserved81;	//0xCC4F25FC
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_00_T       shp_motion_gain_ctrl_00;	//0xCC4F2600
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_01_T       shp_motion_gain_ctrl_01;	//0xCC4F2604
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_02_T       shp_motion_gain_ctrl_02;	//0xCC4F2608
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_03_T       shp_motion_gain_ctrl_03;	//0xCC4F260C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_04_T       shp_motion_gain_ctrl_04;	//0xCC4F2610
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_05_T       shp_motion_gain_ctrl_05;	//0xCC4F2614
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_06_T       shp_motion_gain_ctrl_06;	//0xCC4F2618
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_07_T       shp_motion_gain_ctrl_07;	//0xCC4F261C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_08_T       shp_motion_gain_ctrl_08;	//0xCC4F2620
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_09_T       shp_motion_gain_ctrl_09;	//0xCC4F2624
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0A_T       shp_motion_gain_ctrl_0a;	//0xCC4F2628
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0B_T       shp_motion_gain_ctrl_0b;	//0xCC4F262C
	PE_M23_VSD_SHP_MOTION_GAIN_CTRL_0C_T       shp_motion_gain_ctrl_0c;	//0xCC4F2630
	UINT32                                                   reserved82;	//0xCC4F2634
	UINT32                                                   reserved83;	//0xCC4F2638
	UINT32                                                   reserved84;	//0xCC4F263C
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_00_T       shp_motion_prot_ctrl_00;	//0xCC4F2640
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_01_T       shp_motion_prot_ctrl_01;	//0xCC4F2644
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_02_T       shp_motion_prot_ctrl_02;	//0xCC4F2648
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_03_T       shp_motion_prot_ctrl_03;	//0xCC4F264C
	PE_M23_VSD_SHP_MOTION_PROT_CTRL_04_T       shp_motion_prot_ctrl_04;	//0xCC4F2650
	UINT32                                                   reserved85;	//0xCC4F2654
	UINT32                                                   reserved86;	//0xCC4F2658
	UINT32                                                   reserved87;	//0xCC4F265C
	UINT32                                                   reserved88;	//0xCC4F2660
	UINT32                                                   reserved89;	//0xCC4F2664
	UINT32                                                   reserved90;	//0xCC4F2668
	UINT32                                                   reserved91;	//0xCC4F266C
	PE_M23_VSD_SHP_MOT_WIN_CTRL_00_T               shp_mot_win_ctrl_00;	//0xCC4F2670
	PE_M23_VSD_SHP_MOT_WIN_CTRL_01_T               shp_mot_win_ctrl_01;	//0xCC4F2674
	PE_M23_VSD_SHP_MOT_WIN_CTRL_02_T               shp_mot_win_ctrl_02;	//0xCC4F2678
	PE_M23_VSD_SHP_MOT_WIN_CTRL_03_T               shp_mot_win_ctrl_03;	//0xCC4F267C
	PE_M23_VSD_SHP_MOT_WIN_CTRL_04_T               shp_mot_win_ctrl_04;	//0xCC4F2680
	UINT32                                                   reserved92;	//0xCC4F2684
	UINT32                                                   reserved93;	//0xCC4F2688
	UINT32                                                   reserved94;	//0xCC4F268C
	PE_M23_VSD_SHP_OBJ_CTRL_00_T                       shp_obj_ctrl_00;	//0xCC4F2690
	PE_M23_VSD_SHP_OBJ_CTRL_01_T                       shp_obj_ctrl_01;	//0xCC4F2694
	PE_M23_VSD_SHP_OBJ_CTRL_02_T                       shp_obj_ctrl_02;	//0xCC4F2698
	PE_M23_VSD_SHP_OBJ_CTRL_03_T                       shp_obj_ctrl_03;	//0xCC4F269C
	PE_M23_VSD_SHP_OBJ_CTRL_04_T                       shp_obj_ctrl_04;	//0xCC4F26A0
	PE_M23_VSD_SHP_OBJ_CTRL_05_T                       shp_obj_ctrl_05;	//0xCC4F26A4
	PE_M23_VSD_SHP_OBJ_CTRL_06_T                       shp_obj_ctrl_06;	//0xCC4F26A8
	PE_M23_VSD_SHP_OBJ_CTRL_07_T                       shp_obj_ctrl_07;	//0xCC4F26AC
	PE_M23_VSD_SHP_OBJ_CTRL_08_T                       shp_obj_ctrl_08;	//0xCC4F26B0
	PE_M23_VSD_SHP_OBJ_CTRL_09_T                       shp_obj_ctrl_09;	//0xCC4F26B4
	PE_M23_VSD_SHP_OBJ_CTRL_0A_T                       shp_obj_ctrl_0a;	//0xCC4F26B8
	PE_M23_VSD_SHP_OBJ_CTRL_0B_T                       shp_obj_ctrl_0b;	//0xCC4F26BC
	PE_M23_VSD_SHP_OBJ_CTRL_0C_T                       shp_obj_ctrl_0c;	//0xCC4F26C0
	UINT32                                                   reserved95;	//0xCC4F26C4
	UINT32                                                   reserved96;	//0xCC4F26C8
	UINT32                                                   reserved97;	//0xCC4F26CC
	UINT32                                                   reserved98;	//0xCC4F26D0
	UINT32                                                   reserved99;	//0xCC4F26D4
	UINT32                                                  reserved100;	//0xCC4F26D8
	UINT32                                                  reserved101;	//0xCC4F26DC
	UINT32                                                  reserved102;	//0xCC4F26E0
	UINT32                                                  reserved103;	//0xCC4F26E4
	UINT32                                                  reserved104;	//0xCC4F26E8
	UINT32                                                  reserved105;	//0xCC4F26EC
	UINT32                                                  reserved106;	//0xCC4F26F0
	UINT32                                                  reserved107;	//0xCC4F26F4
	UINT32                                                  reserved108;	//0xCC4F26F8
	UINT32                                                  reserved109;	//0xCC4F26FC
	UINT32                                                  reserved110;	//0xCC4F2700
	UINT32                                                  reserved111;	//0xCC4F2704
	UINT32                                                  reserved112;	//0xCC4F2708
	UINT32                                                  reserved113;	//0xCC4F270C
	UINT32                                                  reserved114;	//0xCC4F2710
	UINT32                                                  reserved115;	//0xCC4F2714
	UINT32                                                  reserved116;	//0xCC4F2718
	UINT32                                                  reserved117;	//0xCC4F271C
	UINT32                                                  reserved118;	//0xCC4F2720
	UINT32                                                  reserved119;	//0xCC4F2724
	UINT32                                                  reserved120;	//0xCC4F2728
	UINT32                                                  reserved121;	//0xCC4F272C
	UINT32                                                  reserved122;	//0xCC4F2730
	UINT32                                                  reserved123;	//0xCC4F2734
	UINT32                                                  reserved124;	//0xCC4F2738
	UINT32                                                  reserved125;	//0xCC4F273C
	UINT32                                                  reserved126;	//0xCC4F2740
	UINT32                                                  reserved127;	//0xCC4F2744
	UINT32                                                  reserved128;	//0xCC4F2748
	UINT32                                                  reserved129;	//0xCC4F274C
	UINT32                                                  reserved130;	//0xCC4F2750
	UINT32                                                  reserved131;	//0xCC4F2754
	UINT32                                                  reserved132;	//0xCC4F2758
	UINT32                                                  reserved133;	//0xCC4F275C
	UINT32                                                  reserved134;	//0xCC4F2760
	UINT32                                                  reserved135;	//0xCC4F2764
	UINT32                                                  reserved136;	//0xCC4F2768
	UINT32                                                  reserved137;	//0xCC4F276C
	UINT32                                                  reserved138;	//0xCC4F2770
	UINT32                                                  reserved139;	//0xCC4F2774
	UINT32                                                  reserved140;	//0xCC4F2778
	UINT32                                                  reserved141;	//0xCC4F277C
	UINT32                                                  reserved142;	//0xCC4F2780
	UINT32                                                  reserved143;	//0xCC4F2784
	UINT32                                                  reserved144;	//0xCC4F2788
	UINT32                                                  reserved145;	//0xCC4F278C
	UINT32                                                  reserved146;	//0xCC4F2790
	UINT32                                                  reserved147;	//0xCC4F2794
	UINT32                                                  reserved148;	//0xCC4F2798
	UINT32                                                  reserved149;	//0xCC4F279C
	PE_M23_VSD_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCC4F27A0
	PE_M23_VSD_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCC4F27A4
	PE_M23_VSD_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCC4F27A8
	PE_M23_VSD_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCC4F27AC
	PE_M23_VSD_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCC4F27B0
	PE_M23_VSD_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCC4F27B4
	UINT32                                                  reserved150;	//0xCC4F27B8
	UINT32                                                  reserved151;	//0xCC4F27BC
	UINT32                                                  reserved152;	//0xCC4F27C0
	UINT32                                                  reserved153;	//0xCC4F27C4
	UINT32                                                  reserved154;	//0xCC4F27C8
	UINT32                                                  reserved155;	//0xCC4F27CC
	PE_M23_VSD_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCC4F27D0
	PE_M23_VSD_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCC4F27D4
	PE_M23_VSD_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCC4F27D8
	PE_M23_VSD_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCC4F27DC
	PE_M23_VSD_SHP_MOTION_GAIN_STAT_00_T       shp_motion_gain_stat_00;	//0xCC4F27E0
	PE_M23_VSD_SHP_MOTION_GAIN_STAT_01_T       shp_motion_gain_stat_01;	//0xCC4F27E4
	PE_M23_VSD_SHP_CORE_EDGE_STAT_00_T           shp_core_edge_stat_00;	//0xCC4F27E8
	PE_M23_VSD_SHP_CORE_EDGE_STAT_01_T           shp_core_edge_stat_01;	//0xCC4F27EC
	PE_M23_VSD_SHP_CORE_EDGE_STAT_02_T           shp_core_edge_stat_02;	//0xCC4F27F0
	PE_M23_VSD_SHP_CORE_EDGE_STAT_03_T           shp_core_edge_stat_03;	//0xCC4F27F4
	PE_M23_VSD_SHP_CORE_EDGE_STAT_04_T           shp_core_edge_stat_04;	//0xCC4F27F8
	PE_M23_VSD_SHP_CORE_EDGE_STAT_05_T           shp_core_edge_stat_05;	//0xCC4F27FC
	PE_M23_VSD_SHP_CORE_TMAP_STAT_00_T           shp_core_tmap_stat_00;	//0xCC4F2800
	PE_M23_VSD_SHP_CORE_TMAP_STAT_01_T           shp_core_tmap_stat_01;	//0xCC4F2804
	PE_M23_VSD_SHP_CORE_TMAP_STAT_02_T           shp_core_tmap_stat_02;	//0xCC4F2808
	PE_M23_VSD_SHP_CORE_TMAP_STAT_03_T           shp_core_tmap_stat_03;	//0xCC4F280C
	PE_M23_VSD_SHP_CORE_TMAP_STAT_04_T           shp_core_tmap_stat_04;	//0xCC4F2810
	PE_M23_VSD_SHP_CORE_TMAP_STAT_05_T           shp_core_tmap_stat_05;	//0xCC4F2814
	PE_M23_VSD_SHP_CORE_TMAP_STAT_06_T           shp_core_tmap_stat_06;	//0xCC4F2818
	PE_M23_VSD_SHP_CORE_TMAP_STAT_07_T           shp_core_tmap_stat_07;	//0xCC4F281C
	PE_M23_VSD_SHP_FACE_WIN_CTRL_00_T             shp_face_win_ctrl_00;	//0xCC4F2820
	PE_M23_VSD_SHP_FACE_WIN_CTRL_01_T             shp_face_win_ctrl_01;	//0xCC4F2824
	PE_M23_VSD_SHP_FACE_WIN_CTRL_02_T             shp_face_win_ctrl_02;	//0xCC4F2828
	PE_M23_VSD_SHP_FACE_WIN_CTRL_03_T             shp_face_win_ctrl_03;	//0xCC4F282C
	PE_M23_VSD_SHP_FACE_WIN_CTRL_04_T             shp_face_win_ctrl_04;	//0xCC4F2830
	PE_M23_VSD_SHP_FACE_WIN_CTRL_05_T             shp_face_win_ctrl_05;	//0xCC4F2834
	PE_M23_VSD_SHP_BODY_WIN_CTRL_00_T             shp_body_win_ctrl_00;	//0xCC4F2838
	PE_M23_VSD_SHP_BODY_WIN_CTRL_01_T             shp_body_win_ctrl_01;	//0xCC4F283C
	PE_M23_VSD_SHP_BODY_WIN_CTRL_02_T             shp_body_win_ctrl_02;	//0xCC4F2840
	PE_M23_VSD_SHP_BODY_WIN_CTRL_03_T             shp_body_win_ctrl_03;	//0xCC4F2844
	PE_M23_VSD_SHP_BODY_WIN_CTRL_04_T             shp_body_win_ctrl_04;	//0xCC4F2848
	PE_M23_VSD_SHP_BODY_WIN_CTRL_05_T             shp_body_win_ctrl_05;	//0xCC4F284C
	UINT32                                                  reserved156;	//0xCC4F2850
	UINT32                                                  reserved157;	//0xCC4F2854
	UINT32                                                  reserved158;	//0xCC4F2858
	UINT32                                                  reserved159;	//0xCC4F285C
	UINT32                                                  reserved160;	//0xCC4F2860
	UINT32                                                  reserved161;	//0xCC4F2864
	UINT32                                                  reserved162;	//0xCC4F2868
	UINT32                                                  reserved163;	//0xCC4F286C
	UINT32                                                  reserved164;	//0xCC4F2870
	UINT32                                                  reserved165;	//0xCC4F2874
	UINT32                                                  reserved166;	//0xCC4F2878
	UINT32                                                  reserved167;	//0xCC4F287C
	UINT32                                                  reserved168;	//0xCC4F2880
	UINT32                                                  reserved169;	//0xCC4F2884
	UINT32                                                  reserved170;	//0xCC4F2888
	UINT32                                                  reserved171;	//0xCC4F288C
	UINT32                                                  reserved172;	//0xCC4F2890
	UINT32                                                  reserved173;	//0xCC4F2894
	UINT32                                                  reserved174;	//0xCC4F2898
	UINT32                                                  reserved175;	//0xCC4F289C
	UINT32                                                  reserved176;	//0xCC4F28A0
	UINT32                                                  reserved177;	//0xCC4F28A4
	UINT32                                                  reserved178;	//0xCC4F28A8
	UINT32                                                  reserved179;	//0xCC4F28AC
	UINT32                                                  reserved180;	//0xCC4F28B0
	UINT32                                                  reserved181;	//0xCC4F28B4
	UINT32                                                  reserved182;	//0xCC4F28B8
	UINT32                                                  reserved183;	//0xCC4F28BC
	UINT32                                                  reserved184;	//0xCC4F28C0
	UINT32                                                  reserved185;	//0xCC4F28C4
	UINT32                                                  reserved186;	//0xCC4F28C8
	UINT32                                                  reserved187;	//0xCC4F28CC
	UINT32                                                  reserved188;	//0xCC4F28D0
	UINT32                                                  reserved189;	//0xCC4F28D4
	UINT32                                                  reserved190;	//0xCC4F28D8
	UINT32                                                  reserved191;	//0xCC4F28DC
	UINT32                                                  reserved192;	//0xCC4F28E0
	UINT32                                                  reserved193;	//0xCC4F28E4
	UINT32                                                  reserved194;	//0xCC4F28E8
	UINT32                                                  reserved195;	//0xCC4F28EC
	PE_M23_VSD_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCC4F28F0
	PE_M23_VSD_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCC4F28F4
	PE_M23_VSD_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCC4F28F8
	PE_M23_VSD_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCC4F28FC
}PE_SHP_REG_M23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0200 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_M23_DTM_DTM_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0204 RW 0x0438_0780
	UINT32 width                            :12;	//(11:0,NA,0x780) //width
	UINT32 resvd0                           :4;
	UINT32 height                           :12;	//(27:16,NA,0x438) //height
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0208 RW 0x0100_0000
	UINT32 resvd0                           :1;
	UINT32 reg_va_cnt_en                    :1;	//(1,NA,0x0) //1: va count enable for DTM_TOP_CTRL_03
	UINT32 dtm_disp_detour                  :1;	//(2,NA,0x0) //1: display tone mapping detour
	UINT32 resvd1                           :1;
	UINT32 reg_use_own_lut_en               :1;	//(4,NA,0x0) //0:use luminanace LUT channel G hif	1:use own LUT hif(B/R)(WR only)
	UINT32 resvd2                           :19;
	UINT32 reg_master_en                    :1;	//(24,NA,0x1) //LUT master enable
	UINT32 resvd3                           :7;
	};
}PE_M23_DTM_DTM_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F020C RO 0x0000_0000
	UINT32 vcnt                             :12;	//(11:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(12,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(13,NA,0x0) //Vertical Active at PE1 output
	UINT32 resvd0                           :2;
	UINT32 vcnt2                            :12;	//(27:16,NA,0x0) //vertical line number
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0210 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_M23_DTM_DTM_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0214 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,NA,0x14) //vdpulse position for register loading
	};
}PE_M23_DTM_DTM_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0218 RW 0x0000_0000
	UINT32 resvd0                           :20;
	UINT32 reg_out_winmode_dly_sel          :2;	//(21:20,NA,0x0) //0: 35T (DTM 23T) 1: 10T (DTM 1T) 2: 11T (DTM 2T)
	UINT32 resvd1                           :2;
	UINT32 reg_ocsc_en                      :1;	//(24,NA,0x0) //
	UINT32 reg_icsc_en                      :1;	//(25,NA,0x0) //
	UINT32 resvd2                           :6;
	};
}PE_M23_DTM_DTM_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F021C RW 0x1000_7D12
	UINT32 reg_icsc_coef1                   :15;	//(14:0,NA,0x7D12) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef0                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0220 RW 0x78A8_1000
	UINT32 reg_icsc_coef3                   :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef2                   :15;	//(30:16,NA,0x78A8) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0224 RW 0x1D0E_0000
	UINT32 reg_icsc_coef5                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef4                   :15;	//(30:16,NA,0x1D0E) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0228 RW 0x1000_0000
	UINT32 reg_icsc_coef7                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef6                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F022C RW 0x18A4_0000
	UINT32 resvd0                           :16;
	UINT32 reg_icsc_coef8                   :15;	//(30:16,NA,0x18A4) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0230 RW 0x0000_7E00
	UINT32 reg_icsc_ofst1                   :11;	//(10:0,NA,0x7E00) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_TOP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0234 RW 0x7E00_0000
	UINT32 reg_icsc_ofst3                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst2                   :11;	//(26:16,NA,0x7E00) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_TOP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0238 RW 0x0000_0000
	UINT32 reg_icsc_ofst5                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst4                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_TOP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F023C RW 0x09D3_00FE
	UINT32 reg_ocsc_coef1                   :15;	//(14:0,NA,0x00FE) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef0                   :15;	//(30:16,NA,0x09D3) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0240 RW 0x02EE_7A98
	UINT32 reg_ocsc_coef3                   :15;	//(14:0,NA,0x7A98) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef2                   :15;	//(30:16,NA,0x02EE) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0244 RW 0x0706_7E62
	UINT32 reg_ocsc_coef5                   :15;	//(14:0,NA,0x7E62) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef4                   :15;	//(30:16,NA,0x0706) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0248 RW 0x799E_7F5C
	UINT32 reg_ocsc_coef7                   :15;	//(14:0,NA,0x7F5C) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef6                   :15;	//(30:16,NA,0x799E) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F024C RW 0x0706_0000
	UINT32 resvd0                           :16;
	UINT32 reg_ocsc_coef8                   :15;	//(30:16,NA,0x0706) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_TOP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0250 RW 0x799E_7F5C
	UINT32 reg_ocsc_ofst1                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_TOP_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0254 RW 0x799E_7F5C
	UINT32 reg_ocsc_ofst3                   :11;	//(10:0,NA,0x0040) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst2                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_TOP_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0258 RW 0x799E_7F5C
	UINT32 reg_ocsc_ofst5                   :11;	//(10:0,NA,0x0200) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst4                   :11;	//(26:16,NA,0x0200) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_TOP_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F025C RW 0x0000_0000
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x000) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0260 RW 0x0780_0438
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0264 RW 0x0780_0438
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0268 RW 0x0F00_0870
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x870) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0xF00) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F026C RW 0x0000_0000
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x000) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0270 RW 0x0780_0438
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0274 RW 0x0780_0438
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0278 RW 0x0F00_0870
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x870) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0xF00) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_M23_DTM_DTM_TOP_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0280 RW 0x0000_0000
	UINT32 dummy_00                         :32;	//(31:0,NA,0x0) //
	};
}PE_M23_DTM_DTM_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0284 RW 0x0000_0000
	UINT32 dummy_01                         :32;	//(31:0,NA,0x0) //
	};
}PE_M23_DTM_DTM_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0288 RW 0x0000_0000
	UINT32 dummy_02                         :32;	//(31:0,NA,0x0) //
	};
}PE_M23_DTM_DTM_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F028C RW 0x0000_0000
	UINT32 dummy_03                         :32;	//(31:0,NA,0x0) //
	};
}PE_M23_DTM_DTM_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0290 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0,NA,0x1) //
	UINT32 resvd                            :31;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0294 RW 0x12A0_7C98
	UINT32 r_csc1st_coef1                   :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0298 RW 0x7775_12A0
	UINT32 r_csc1st_coef3                   :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F029C RW 0x21D7_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02A0 RW 0x12A0_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02A4 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02A8 RW 0x07C0_0600
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02AC RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02B0 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_M23_DTM_DTM_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02C0 RW 0x0000_0000
	UINT32 luminance_lut_enable             :1;	//(0,NA,0x0) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4,NA,0x0) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,NA,0x0) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,NA,0x0) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,NA,0x0) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,NA,0x0) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16,NA,0x0) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :3;
	UINT32 window_cg_disable                :1;	//(20,NA,0x0) //clock gating disable
	UINT32 resvd3                           :11;
	};
}PE_M23_DTM_DTM_LLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02C4 RW 0x0000_0000
	UINT32 win_w0_x0                        :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0                        :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02C8 RW 0x0437_077F
	UINT32 win_w0_x1                        :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1                        :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02CC RW 0x0000_0000
	UINT32 win_w1_x0                        :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0                        :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02D0 RW 0x0437_077F
	UINT32 win_w1_x1                        :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1                        :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_LLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02D4 RW 0x03FF_03FF
	UINT32 hif_llut_wdata_y_33rd            :10;	//(9:0,NA,0x3FF) //Y coordinate of 33rd control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut_wdata_x_33rd            :10;	//(25:16,NA,0x3FF) //X coordinate of 33rd control point
	UINT32 resvd1                           :6;
	};
}PE_M23_DTM_DTM_LLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02D8 RW 0x0000_8000
	UINT32 hif_llut0_address                :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut0_load                   :1;	//(8,NA,0x0) //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load            :1;	//(11,NA,0x0) //0 : LUT load at vactive falling, when hif_llut0_load = 1	1 : LUT load at "hif_llut0_load = 1"
	UINT32 hif_llut0_ai                     :1;	//(12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut0_enable                 :1;	//(15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_DTM_DTM_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02DC RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut0_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_M23_DTM_DTM_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02E0 RW 0x0000_8000
	UINT32 hif_llut1_address                :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut1_load                   :1;	//(8,NA,0x0) //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load            :1;	//(11,NA,0x0) //0 : LUT load at vactive falling, when hif_llut1_load = 1	1 : LUT load at "hif_llut1_load = 1"
	UINT32 hif_llut1_ai                     :1;	//(12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut1_enable                 :1;	//(15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_DTM_DTM_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02E4 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut1_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_M23_DTM_DTM_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02E8 RW 0x0000_8000
	UINT32 hif_llut2_address                :4;	//(3:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load            :1;	//(11,NA,0x0) //0 : LUT load at vactive falling, when hif_dce_load = 1	1 : LUT load at "hif_dce_load = 1"
	UINT32 hif_llut2_ai                     :1;	//(12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut2_enable                 :1;	//(15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_DTM_DTM_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02EC RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut2_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_M23_DTM_DTM_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02F0 RW 0x0000_0000
	UINT32 reg_lut_lum_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_lum_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_lum_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02F4 RW 0x0000_0000
	UINT32 reg_lut_lum_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_lum_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_lum_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02F8 RW 0x0000_0000
	UINT32 reg_lut_sat_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_sat_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_sat_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F02FC RW 0x0000_0000
	UINT32 reg_lut_sat_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_sat_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_sat_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0300 RW 0xFF00_0000
	UINT32 reg_hue_prsv_en                  :1;	//(0,NA,0x0) //enable pin for hue restoration
	UINT32 resvd0                           :3;
	UINT32 reg_sat_prsv_en                  :1;	//(4,NA,0x0) //enable pin for saturation preserving
	UINT32 reg_hue_prsv_detour              :1;	//(5,NA,0x0) //preserving detour
	UINT32 resvd1                           :6;
	UINT32 reg_hue_prsv_cg_disable          :1;	//(12,NA,0x0) //clock gating disable
	UINT32 resvd2                           :3;
	UINT32 reg_sat_prsv_ratio               :8;	//(23:16,NA,0x0) //0:bypass, 255:restored sat
	UINT32 reg_hue_prsv_ratio               :8;	//(31:24,NA,0xFF) //0:bypass, 255:restored hue
	};
}PE_M23_DTM_DTM_HUE_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0304 RW 0x00000000
	UINT32 reg_lum_lut_input_sel            :1;	//(0,NA,0x0) //0:Y 1:max_rgb
	UINT32 resvd0                           :3;
	UINT32 reg_hue_lut_gain_sel             :1;	//(4,NA,0x0) //0:luma 1:saturation
	UINT32 resvd1                           :3;
	UINT32 reg_sat_lut_gain_sel             :1;	//(8,NA,0x0) //0:luma 1:saturation
	UINT32 resvd2                           :23;
	};
}PE_M23_DTM_DTM_HUE_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0310 RW 0x0000_0000
	UINT32 odd_win_w0_x0                    :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y0                    :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_ODD_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0314 RW 0x0437_077F
	UINT32 odd_win_w0_x1                    :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y1                    :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_ODD_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F0318 RW 0x0000_0000
	UINT32 odd_win_w1_x0                    :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y0                    :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_ODD_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F031C RW 0x0437_077F
	UINT32 odd_win_w1_x1                    :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y1                    :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_M23_DTM_DTM_ODD_LLUT_CTRL_04_T;

typedef struct {
	PE_M23_DTM_DTM_TOP_CTRL_00_T                           dtm_top_ctrl_00;	//0xCC4F0200
	PE_M23_DTM_DTM_TOP_CTRL_01_T                           dtm_top_ctrl_01;	//0xCC4F0204
	PE_M23_DTM_DTM_TOP_CTRL_02_T                           dtm_top_ctrl_02;	//0xCC4F0208
	PE_M23_DTM_DTM_TOP_CTRL_03_T                           dtm_top_ctrl_03;	//0xCC4F020C
	PE_M23_DTM_DTM_TOP_CTRL_04_T                           dtm_top_ctrl_04;	//0xCC4F0210
	PE_M23_DTM_DTM_TOP_CTRL_05_T                           dtm_top_ctrl_05;	//0xCC4F0214
	PE_M23_DTM_DTM_TOP_CTRL_06_T                           dtm_top_ctrl_06;	//0xCC4F0218
	PE_M23_DTM_DTM_TOP_CTRL_07_T                           dtm_top_ctrl_07;	//0xCC4F021C
	PE_M23_DTM_DTM_TOP_CTRL_08_T                           dtm_top_ctrl_08;	//0xCC4F0220
	PE_M23_DTM_DTM_TOP_CTRL_09_T                           dtm_top_ctrl_09;	//0xCC4F0224
	PE_M23_DTM_DTM_TOP_CTRL_10_T                           dtm_top_ctrl_10;	//0xCC4F0228
	PE_M23_DTM_DTM_TOP_CTRL_11_T                           dtm_top_ctrl_11;	//0xCC4F022C
	PE_M23_DTM_DTM_TOP_CTRL_12_T                           dtm_top_ctrl_12;	//0xCC4F0230
	PE_M23_DTM_DTM_TOP_CTRL_13_T                           dtm_top_ctrl_13;	//0xCC4F0234
	PE_M23_DTM_DTM_TOP_CTRL_14_T                           dtm_top_ctrl_14;	//0xCC4F0238
	PE_M23_DTM_DTM_TOP_CTRL_15_T                           dtm_top_ctrl_15;	//0xCC4F023C
	PE_M23_DTM_DTM_TOP_CTRL_16_T                           dtm_top_ctrl_16;	//0xCC4F0240
	PE_M23_DTM_DTM_TOP_CTRL_17_T                           dtm_top_ctrl_17;	//0xCC4F0244
	PE_M23_DTM_DTM_TOP_CTRL_18_T                           dtm_top_ctrl_18;	//0xCC4F0248
	PE_M23_DTM_DTM_TOP_CTRL_19_T                           dtm_top_ctrl_19;	//0xCC4F024C
	PE_M23_DTM_DTM_TOP_CTRL_20_T                           dtm_top_ctrl_20;	//0xCC4F0250
	PE_M23_DTM_DTM_TOP_CTRL_21_T                           dtm_top_ctrl_21;	//0xCC4F0254
	PE_M23_DTM_DTM_TOP_CTRL_22_T                           dtm_top_ctrl_22;	//0xCC4F0258
	PE_M23_DTM_DTM_TOP_CTRL_23_T                           dtm_top_ctrl_23;	//0xCC4F025C
	PE_M23_DTM_DTM_TOP_CTRL_24_T                           dtm_top_ctrl_24;	//0xCC4F0260
	PE_M23_DTM_DTM_TOP_CTRL_25_T                           dtm_top_ctrl_25;	//0xCC4F0264
	PE_M23_DTM_DTM_TOP_CTRL_26_T                           dtm_top_ctrl_26;	//0xCC4F0268
	PE_M23_DTM_DTM_TOP_CTRL_27_T                           dtm_top_ctrl_27;	//0xCC4F026C
	PE_M23_DTM_DTM_TOP_CTRL_28_T                           dtm_top_ctrl_28;	//0xCC4F0270
	PE_M23_DTM_DTM_TOP_CTRL_29_T                           dtm_top_ctrl_29;	//0xCC4F0274
	PE_M23_DTM_DTM_TOP_CTRL_30_T                           dtm_top_ctrl_30;	//0xCC4F0278
	UINT32                                                    reserved0;	//0xCC4F027C
	PE_M23_DTM_DTM_FSW_CTRL_00_T                           dtm_fsw_ctrl_00;	//0xCC4F0280
	PE_M23_DTM_DTM_FSW_CTRL_01_T                           dtm_fsw_ctrl_01;	//0xCC4F0284
	PE_M23_DTM_DTM_FSW_CTRL_02_T                           dtm_fsw_ctrl_02;	//0xCC4F0288
	PE_M23_DTM_DTM_FSW_CTRL_03_T                           dtm_fsw_ctrl_03;	//0xCC4F028C
	PE_M23_DTM_DTM_CSC1_CTRL_00_T                         dtm_csc1_ctrl_00;	//0xCC4F0290
	PE_M23_DTM_DTM_CSC1_CTRL_01_T                         dtm_csc1_ctrl_01;	//0xCC4F0294
	PE_M23_DTM_DTM_CSC1_CTRL_02_T                         dtm_csc1_ctrl_02;	//0xCC4F0298
	PE_M23_DTM_DTM_CSC1_CTRL_03_T                         dtm_csc1_ctrl_03;	//0xCC4F029C
	PE_M23_DTM_DTM_CSC1_CTRL_04_T                         dtm_csc1_ctrl_04;	//0xCC4F02A0
	PE_M23_DTM_DTM_CSC1_CTRL_05_T                         dtm_csc1_ctrl_05;	//0xCC4F02A4
	PE_M23_DTM_DTM_CSC1_CTRL_06_T                         dtm_csc1_ctrl_06;	//0xCC4F02A8
	PE_M23_DTM_DTM_CSC1_CTRL_07_T                         dtm_csc1_ctrl_07;	//0xCC4F02AC
	PE_M23_DTM_DTM_CSC1_CTRL_08_T                         dtm_csc1_ctrl_08;	//0xCC4F02B0
	UINT32                                                    reserved1;	//0xCC4F02B4
	UINT32                                                    reserved2;	//0xCC4F02B8
	UINT32                                                    reserved3;	//0xCC4F02BC
	PE_M23_DTM_DTM_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0xCC4F02C0
	PE_M23_DTM_DTM_LLUT_CTRL_01_T                         dtm_llut_ctrl_01;	//0xCC4F02C4
	PE_M23_DTM_DTM_LLUT_CTRL_02_T                         dtm_llut_ctrl_02;	//0xCC4F02C8
	PE_M23_DTM_DTM_LLUT_CTRL_03_T                         dtm_llut_ctrl_03;	//0xCC4F02CC
	PE_M23_DTM_DTM_LLUT_CTRL_04_T                         dtm_llut_ctrl_04;	//0xCC4F02D0
	PE_M23_DTM_DTM_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0xCC4F02D4
	PE_M23_DTM_DTM_LLUT0_IA_CTRL_T                       dtm_llut0_ia_ctrl;	//0xCC4F02D8
	PE_M23_DTM_DTM_LLUT0_IA_DATA_T                       dtm_llut0_ia_data;	//0xCC4F02DC
	PE_M23_DTM_DTM_LLUT1_IA_CTRL_T                       dtm_llut1_ia_ctrl;	//0xCC4F02E0
	PE_M23_DTM_DTM_LLUT1_IA_DATA_T                       dtm_llut1_ia_data;	//0xCC4F02E4
	PE_M23_DTM_DTM_LLUT2_IA_CTRL_T                       dtm_llut2_ia_ctrl;	//0xCC4F02E8
	PE_M23_DTM_DTM_LLUT2_IA_DATA_T                       dtm_llut2_ia_data;	//0xCC4F02EC
	PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_00_T           dtm_lut_lum_sat_ctrl_00;	//0xCC4F02F0
	PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_01_T           dtm_lut_lum_sat_ctrl_01;	//0xCC4F02F4
	PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_02_T           dtm_lut_lum_sat_ctrl_02;	//0xCC4F02F8
	PE_M23_DTM_DTM_LUT_LUM_SAT_CTRL_03_T           dtm_lut_lum_sat_ctrl_03;	//0xCC4F02FC
	PE_M23_DTM_DTM_HUE_SAT_CTRL_00_T                   dtm_hue_sat_ctrl_00;	//0xCC4F0300
	PE_M23_DTM_DTM_HUE_SAT_CTRL_01_T                   dtm_hue_sat_ctrl_01;	//0xCC4F0304
	UINT32                                                    reserved4;	//0xCC4F0308
	UINT32                                                    reserved5;	//0xCC4F030C
	PE_M23_DTM_DTM_ODD_LLUT_CTRL_01_T                 dtm_odd_llut_ctrl_01;	//0xCC4F0310
	PE_M23_DTM_DTM_ODD_LLUT_CTRL_02_T                 dtm_odd_llut_ctrl_02;	//0xCC4F0314
	PE_M23_DTM_DTM_ODD_LLUT_CTRL_03_T                 dtm_odd_llut_ctrl_03;	//0xCC4F0318
	PE_M23_DTM_DTM_ODD_LLUT_CTRL_04_T                 dtm_odd_llut_ctrl_04;	//0xCC4F031C
}PE_VSD_DTM_REG_M23_T;

#endif
