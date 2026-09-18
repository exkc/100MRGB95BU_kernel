#ifndef _PE_SHP_REG_O22A0_H_
#define _PE_SHP_REG_O22A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC462000 RW 0x0019_0021
	UINT32 reg_top_actv_sel                 :1;	//(0:0,NA,1) //0: use core pass-through active	1: use active sync delay active
	UINT32 resvd0                           :3;
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//(12:12,NA,0) //Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :7;
	UINT32 reg_top_lsb_copy_mode            :2;	//(21:20,NA,0) //0 : lsb force 0	1 : lsb force 1	2 : lsb force copy [1] -> [0]
	UINT32 resvd4                           :2;
	UINT32 reg_top_422to444_mode            :1;	//(24:24,NA,0) //0: H-average mode	1: repeatition mode
	UINT32 resvd5                           :3;
	UINT32 reg_top_mode_444                 :1;	//(28:28,NA,0) //0: 422 mode	1: 444 mode
	UINT32 resvd6                           :1;
	UINT32 reg_obc_debug                    :2;	//(31:30,NA,0) //0: shp result 	1 : face map	2 : object map
	};
}PE_O22_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462004 RW 0x0870_0F00
	UINT32 reg_top_width                    :16;	//(15:0,NA,3840) //processing width (default : 3840)
	UINT32 reg_top_height                   :16;	//(31:16,NA,2160) //processing height (default : 2160)
	};
}PE_O22_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462008 RW 0x0118_0002
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,0) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,1) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O22_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46200C RW 0x0000_000A
	UINT32 reg_top_pic_init_latency         :12;	//(11:0,NA,10) //pic init latency
	UINT32 resvd                            :20;
	};
}PE_O22_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462010 RW 0x0000_0019
	UINT32 reg_top_update_ctrl              :5;	//(4:0,NA,25) //[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_O22_SHP_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462014 RW 0x0E00_0810
	UINT32 reg_new_fd_detail_beta_mul       :8;	//(7:0,NA,16) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_detail_alpha_mul      :8;	//(15:8,NA,8) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_edge_beta_mul         :8;	//(23:16,NA,0) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_new_fd_edge_alpha_mul        :8;	//(31:24,NA,14) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O22_SHP_NEW_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462018 RW 0x60A0_0020
	UINT32 reg_new_fd_edge_minmax_y0        :8;	//(7:0,NA,32) //Final edge LUT, y0
	UINT32 reg_new_fd_edge_minmax_x0        :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_new_fd_edge_minmax_y1        :8;	//(23:16,NA,160) //Final edge LUT, y1
	UINT32 reg_new_fd_edge_minmax_x1        :8;	//(31:24,NA,96) //Final edge LUT, x1
	};
}PE_O22_SHP_NEW_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46201C RW 0xFFFF_82DC
	UINT32 reg_new_fd_edge_minmax_y2        :8;	//(7:0,NA,220) //Final edge LUT, y2
	UINT32 reg_new_fd_edge_minmax_x2        :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_new_fd_edge_minmax_y3        :8;	//(23:16,NA,255) //Final edge LUT, y3
	UINT32 reg_new_fd_edge_minmax_x3        :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O22_SHP_NEW_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462020 RW 0x2860_0040
	UINT32 reg_new_fd_detail_minmax_y0      :8;	//(7:0,NA,64) //Final detail LUT, y0
	UINT32 reg_new_fd_detail_minmax_x0      :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_new_fd_detail_minmax_y1      :8;	//(23:16,NA,96) //Final detail LUT, y1
	UINT32 reg_new_fd_detail_minmax_x1      :8;	//(31:24,NA,40) //Final detail LUT, x1
	};
}PE_O22_SHP_NEW_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462024 RW 0x64A0_4678
	UINT32 reg_new_fd_detail_minmax_y2      :8;	//(7:0,NA,120) //Final detail LUT, y2
	UINT32 reg_new_fd_detail_minmax_x2      :8;	//(15:8,NA,70) //Final detail LUT, x2
	UINT32 reg_new_fd_detail_minmax_y3      :8;	//(23:16,NA,160) //Final detail LUT, y3
	UINT32 reg_new_fd_detail_minmax_x3      :8;	//(31:24,NA,100) //Final detail LUT, x3
	};
}PE_O22_SHP_NEW_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462028 RW 0x0000_0180
	UINT32 reg_texture_region_alpha         :8;	//(7:0,NA,128) //Final detail LUT, y2
	UINT32 reg_region_text_en_aux           :1;	//(8:8,NA,1) //Final detail LUT, y2
	UINT32 reg_obj_shp_en_aux               :1;	//(9:9,NA,0) //Final detail LUT, y2
	UINT32 resvd                            :22;
	};
}PE_O22_SHP_TEXT_REGION_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462040 RW 0xFFFF_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //pattern pixel value (Cb)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //pattern pixel value (Cr)
	};
}PE_O22_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462050 RW 0x0F00_0020
	UINT32 reg_out_hgos_head_crop_ptr       :13;	//(12:0,NA,32) //output horizontal gos head crop pointer
	UINT32 resvd0                           :3;
	UINT32 reg_out_hgos_tail_crop_ptr       :13;	//(28:16,NA,3840) //output horizontal gos tail crop pointer
	UINT32 resvd1                           :1;
	UINT32 reg_out_hgos_head_en             :1;	//(30:30,NA,0) //output horizontal gos head crop enable
	UINT32 reg_out_hgos_tail_en             :1;	//(31:31,NA,0) //output horizontal gos tail crop enable
	};
}PE_O22_SHP_GOS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462060 RW 0x0004_0005
	UINT32 reg_sync_dly_vsync               :16;	//(15:0,NA,5) //v sync (2K
	UINT32 reg_sync_dly_vfp                 :16;	//(31:16,NA,4) //v front porch (2K
	};
}PE_O22_SHP_SYNC_DLY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462064 RW 0x0024_0438
	UINT32 reg_sync_dly_va                  :16;	//(15:0,NA,1080) //v active (2K
	UINT32 reg_sync_dly_vbp                 :16;	//(31:16,NA,36) //v back porch (2K
	};
}PE_O22_SHP_SYNC_DLY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462068 RW 0x0058_002C
	UINT32 reg_sync_dly_hsync               :16;	//(15:0,NA,44) //h sync (2K
	UINT32 reg_sync_dly_hfp                 :16;	//(31:16,NA,88) //h front porch (2K
	};
}PE_O22_SHP_SYNC_DLY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46206C RW 0x0094_0780
	UINT32 reg_sync_dly_ha                  :16;	//(15:0,NA,1920) //h active (2K
	UINT32 reg_sync_dly_hbp                 :16;	//(31:16,NA,148) //h back porch (2K
	};
}PE_O22_SHP_SYNC_DLY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462070 RW 0x0000_0060
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
}PE_O22_SHP_SYNC_DLY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462074 RW 0x000A_00F3
	UINT32 reg_sync_dly_sync_h_dly          :16;	//(15:0,NA,243) //pixel delay
	UINT32 reg_sync_dly_sync_v_dly          :16;	//(31:16,NA,10) //line delay
	};
}PE_O22_SHP_SYNC_DLY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462078 RW 0x0008_0058
	UINT32 reg_sync_dly_cnt_rst_h_value     :16;	//(15:0,NA,88) //disp_pulse_dly Delay
	UINT32 reg_sync_dly_cnt_rst_v_value     :16;	//(31:16,NA,8) //[RO] disp_pulse_dly Counter
	};
}PE_O22_SHP_SYNC_DLY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46207C RW 0x000A_00F3
	UINT32 reg_sync_dly_auto_actv_h_dly     :15;	//(14:0,NA,243) //auto actv pixel delay
	UINT32 reg_sync_dly_auto_actv_gen_en    :1;	//(15:15,NA,0) //auto actv gen enable
	UINT32 reg_sync_dly_auto_actv_v_dly     :15;	//(30:16,NA,10) //auto actv line delay
	UINT32 reg_sync_dly_auto_actv_seam_en   :1;	//(31:31,NA,0) //auto actv seam enable
	};
}PE_O22_SHP_SYNC_DLY_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462080 RW 0x000A_00F3
	UINT32 reg_sync_dly_auto_sync_h_dly     :15;	//(14:0,NA,243) //auto sync pixel delay
	UINT32 reg_sync_dly_auto_sync_gen_en    :1;	//(15:15,NA,0) //auto sync gen enable
	UINT32 reg_sync_dly_auto_sync_v_dly     :15;	//(30:16,NA,10) //auto sync line delay
	UINT32 reg_sync_dly_auto_sync_seam_en   :1;	//(31:31,NA,0) //auto sync seam enable
	};
}PE_O22_SHP_SYNC_DLY_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462084 RW 0x0000_0000
	UINT32 reg_sync_dly_normal_number       :16;	//(15:0,NA,0) //protection mode
	UINT32 resvd                            :16;
	};
}PE_O22_SHP_SYNC_DLY_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462088 RW 0x0000_0000
	UINT32 reg_sync_dly_cnt_h_rst_position  :16;	//(15:0,NA,0) //manual cnt h value position
	UINT32 reg_sync_dly_cnt_v_rst_position  :16;	//(31:16,NA,0) //manual cnt v value position
	};
}PE_O22_SHP_SYNC_DLY_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462090 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0) //ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0) //ROI mask pixel value (Y)
	UINT32 reg_roi_mask_pix_val_cb          :8;	//(23:16,NA,0) //ROI mask pixel value (Cb)
	UINT32 reg_roi_mask_pix_val_cr          :8;	//(31:24,NA,0) //ROI mask pixel value (Cr)
	};
}PE_O22_SHP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462094 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :12;	//(11:0,NA,0) //ROI mask window start position, x0
	UINT32 resvd0                           :4;
	UINT32 reg_roi_mask_win_y0              :12;	//(27:16,NA,0) //ROI mask window start position, y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462098 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :12;	//(11:0,NA,0) //ROI mask window end position, x1
	UINT32 resvd0                           :4;
	UINT32 reg_roi_mask_win_y1              :12;	//(27:16,NA,0) //ROI mask window end position, y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620A0 RW 0x0000_0010
	UINT32 reg_esf_detour_mode              :1;	//(0:0,NA,0) //edge shift filter detour enable
	UINT32 reg_esf_buffer_detour_en         :1;	//(1:1,NA,0) //edge shift filter buffer detour enable
	UINT32 resvd0                           :2;
	UINT32 reg_esf_en                       :1;	//(4:4,NA,1) //edge shift filter enable
	UINT32 resvd1                           :3;
	UINT32 reg_esf_dbg_en                   :1;	//(8:8,NA,0) //edge shift filter debug enable
	UINT32 resvd2                           :23;
	};
}PE_O22_SHP_ESF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620A4 RW 0x4040_C814
	UINT32 reg_esf_min_ratio                :8;	//(7:0,NA,20) //edge shift filter min ratio
	UINT32 reg_esf_base                     :8;	//(15:8,NA,200) //edge shift filter base
	UINT32 reg_esf_max_clip                 :8;	//(23:16,NA,64) //edge shift filter max clipping
	UINT32 reg_esf_master_gain              :8;	//(31:24,NA,64) //edge shift filter master gain
	};
}PE_O22_SHP_ESF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620A8 RW 0x0000_0819
	UINT32 reg_esf_ltv_offset               :8;	//(7:0,NA,25) //edge shift filter ltv offset
	UINT32 reg_esf_ltv_mul                  :8;	//(15:8,NA,8) //edge shift filter ltv mul
	UINT32 resvd                            :16;
	};
}PE_O22_SHP_ESF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620B0 RW 0x0000_0000
	UINT32 reg_win_esf_win0_en              :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_win_esf_win1_en              :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_win_esf_win01_en             :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_esf_win_outside          :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_esf_win_en               :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_esf_bdr_alpha            :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_win_esf_bdr_wid              :2;	//(14:13,NA,0) //border width
	UINT32 reg_win_esf_bdr_en               :1;	//(15:15,NA,0) //border enable
	UINT32 reg_win_esf_cr5                  :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_win_esf_cb5                  :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_win_esf_yy6                  :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_O22_SHP_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620B4 RW 0x0000_0000
	UINT32 reg_win_esf_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620B8 RW 0x086F_0EFF
	UINT32 reg_win_esf_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620BC RW 0x0000_0000
	UINT32 reg_win_esf_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620C0 RW 0x086F_0EFF
	UINT32 reg_win_esf_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4620F0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map	1011: Gain A-map	1100: Gain T-map	1101: Texture region map	1110: object map	1111: face map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O22_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462100 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462104 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462108 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O22_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46210C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O22_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462110 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O22_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462114 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O22_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462118 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O22_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46211C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O22_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462120 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O22_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462124 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O22_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462128 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O22_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46212C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //MNR gain for edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //MNR gain for texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462130 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O22_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462134 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O22_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462138 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O22_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46213C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O22_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462140 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O22_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462144 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O22_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462148 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O22_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46214C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O22_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462150 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O22_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462154 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_O22_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462158 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O22_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462160 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O22_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462164 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O22_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462168 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O22_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46216C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O22_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462170 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O22_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462174 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462178 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O22_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46217C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O22_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462180 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O22_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462184 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_O22_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462188 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O22_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46218C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462190 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462194 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_O22_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621A0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 reserved01                       :3;	// reserved
	UINT32 reg_lc_gb_en                     :1;	// 4:4
	UINT32 reserved02                       :3;	// reserved
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //local gain
	};
}PE_O22_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621A4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //gain balancing, x1
	};
}PE_O22_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621A8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //gain balancing, x3
	};
}PE_O22_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621AC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621B0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621C0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O22_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621C4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_O22_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621C8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O22_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621CC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621D8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O22_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621DC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O22_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621E0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O22_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621E4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621E8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O22_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621EC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O22_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621F0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O22_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621F4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621F8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O22_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4621FC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O22_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462200 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O22_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462204 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_O22_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462208 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O22_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46220C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462210 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462220 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O22_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462224 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O22_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462228 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46222C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462230 RW 0x1010_2014
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
}PE_O22_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462240 RW 0x8000_0011
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
}PE_O22_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462244 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //
	UINT32 resvd3                           :5;
	};
}PE_O22_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462248 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//(21:16,NA,63) //
	UINT32 resvd1                           :10;
	};
}PE_O22_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46224C RW 0x0000_48AB
	UINT32 reg_tgen_rand_init_val_c0        :32;	//(31:0,NA,18603) //
	};
}PE_O22_SHP_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462250 RW 0x0000_48AB
	UINT32 reg_tgen_rand_init_val_c1        :32;	//(31:0,NA,18603) //
	};
}PE_O22_SHP_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462254 RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio                :3;	//(2:0,NA,4) //
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//(13:8,NA,31) //
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //
	UINT32 resvd3                           :6;
	};
}PE_O22_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462258 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //
	UINT32 resvd2                           :3;
	};
}PE_O22_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46225C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O22_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462260 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O22_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462264 RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain           :5;	//(4:0,NA,31) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//(12:8,NA,31) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //
	UINT32 resvd2                           :2;
	};
}PE_O22_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462268 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7                   :4;	//(3:0,NA,15) //
	UINT32 reg_tgen_gain6                   :4;	//(7:4,NA,15) //
	UINT32 reg_tgen_gain5                   :4;	//(11:8,NA,13) //
	UINT32 reg_tgen_gain4                   :4;	//(15:12,NA,12) //
	UINT32 reg_tgen_gain3                   :4;	//(19:16,NA,11) //
	UINT32 reg_tgen_gain2                   :4;	//(23:20,NA,10) //
	UINT32 reg_tgen_gain1                   :4;	//(27:24,NA,8) //
	UINT32 reg_tgen_gain0                   :4;	//(31:28,NA,4) //
	};
}PE_O22_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46226C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462270 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462274 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O22_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462280 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O22_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462284 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462288 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46228C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462290 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462294 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462298 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46229C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622A0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622A4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622A8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622AC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622B0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622B4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622B8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622BC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622C0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622C4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622C8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622CC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622D0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622D4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622D8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622DC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622E0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622E4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O22_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622E8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_O22_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622EC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O22_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622F0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O22_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622F4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O22_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622F8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dtcp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4622FC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462300 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462304 RW 0x0000_159C
	UINT32 reg_nntg_lsfr_init_1st_c0        :32;	//(31:0,NA,5532) //4K nano-noise LSFR init (1st)
	};
}PE_O22_SHP_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462308 RW 0x2CA3_7199
	UINT32 reg_nntg_lsfr_init_2nd_c0        :32;	//(31:0,NA,748908953) //4K nano-noise LSFR init (2nd)
	};
}PE_O22_SHP_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46230C RW 0x3236_3B62
	UINT32 reg_nntg_lsfr_init_3rd_c0        :32;	//(31:0,NA,842414946) //4K nano-noise LSFR init (3rd)
	};
}PE_O22_SHP_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462310 RW 0xFD1C_D00A
	UINT32 reg_nntg_lsfr_init_4th_c0        :32;	//(31:0,NA,4246523914) //4K nano-noise LSFR init (4th)
	};
}PE_O22_SHP_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462314 RW 0x8C3C_2327
	UINT32 reg_nntg_lsfr_init_5th_c0        :32;	//(31:0,NA,2352751399) //4K nano-noise LSFR init (5th)
	};
}PE_O22_SHP_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462318 RW 0xF275_9828
	UINT32 reg_nntg_lsfr_init_1st_c1        :32;	//(31:0,NA,4067792936) //4K nano-noise LSFR init (1st)
	};
}PE_O22_SHP_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46231C RW 0xFEEA_5094
	UINT32 reg_nntg_lsfr_init_2nd_c1        :32;	//(31:0,NA,4276768916) //4K nano-noise LSFR init (2nd)
	};
}PE_O22_SHP_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462320 RW 0xECBE_ACAA
	UINT32 reg_nntg_lsfr_init_3rd_c1        :32;	//(31:0,NA,3971919018) //4K nano-noise LSFR init (3rd)
	};
}PE_O22_SHP_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462324 RW 0xD9C5_DFEA
	UINT32 reg_nntg_lsfr_init_4th_c1        :32;	//(31:0,NA,3653623786) //4K nano-noise LSFR init (4th)
	};
}PE_O22_SHP_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462328 RW 0x23E8_D99E
	UINT32 reg_nntg_lsfr_init_5th_c1        :32;	//(31:0,NA,602462622) //4K nano-noise LSFR init (5th)
	};
}PE_O22_SHP_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46232C RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio              :8;	//(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_O22_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462330 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00           :4;	//(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462334 RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20           :4;	//(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462338 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10           :4;	//(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46233C RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0             :8;	//(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O22_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462340 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2             :8;	//(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O22_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462344 RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0             :8;	//(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O22_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462348 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2             :8;	//(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O22_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46234C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O22_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462350 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O22_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462354 RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O22_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462360 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O22_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462364 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_O22_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462368 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_O22_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46236C RW 0x4080_0070
	UINT32 reg_obj_dct_delta_lut_y0         :8;	//(7:0,NA,112) //object dct LUT for delta control, y0
	UINT32 reg_obj_dct_delta_lut_x0         :8;	//(15:8,NA,0) //object dct LUT for delta control, x0
	UINT32 reg_obj_dct_delta_lut_y1         :8;	//(23:16,NA,128) //object dct LUT for delta control, y1
	UINT32 reg_obj_dct_delta_lut_x1         :8;	//(31:24,NA,64) //object dct LUT for delta control, x1
	};
}PE_O22_SHP_DP_SUM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462370 RW 0xffa0_6090
	UINT32 reg_obj_dct_delta_lut_y2         :8;	//(7:0,NA,144) //object dct LUT for delta control, y2
	UINT32 reg_obj_dct_delta_lut_x2         :8;	//(15:8,NA,96) //object dct LUT for delta control, x2
	UINT32 reg_obj_dct_delta_lut_y3         :8;	//(23:16,NA,160) //object dct LUT for delta control, y3
	UINT32 reg_obj_dct_delta_lut_x3         :8;	//(31:24,NA,255) //object dct LUT for delta control, x3
	};
}PE_O22_SHP_DP_SUM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462374 RW 0x4080_0070
	UINT32 reg_obj_tgen_delta_lut_y0        :8;	//(7:0,NA,112) //object tgen LUT for delta control, y0
	UINT32 reg_obj_tgen_delta_lut_x0        :8;	//(15:8,NA,0) //object tgen LUT for delta control, x0
	UINT32 reg_obj_tgen_delta_lut_y1        :8;	//(23:16,NA,128) //object tgen LUT for delta control, y1
	UINT32 reg_obj_tgen_delta_lut_x1        :8;	//(31:24,NA,64) //object tgen LUT for delta control, x1
	};
}PE_O22_SHP_DP_SUM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462378 RW 0xffb0_6090
	UINT32 reg_obj_tgen_delta_lut_y2        :8;	//(7:0,NA,144) //object tgen LUT for delta control, y2
	UINT32 reg_obj_tgen_delta_lut_x2        :8;	//(15:8,NA,96) //object tgen LUT for delta control, x2
	UINT32 reg_obj_tgen_delta_lut_y3        :8;	//(23:16,NA,176) //object tgen LUT for delta control, y3
	UINT32 reg_obj_tgen_delta_lut_x3        :8;	//(31:24,NA,255) //object tgen LUT for delta control, x3
	};
}PE_O22_SHP_DP_SUM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46237C RW 0x4080_0070
	UINT32 reg_obj_lc_delta_lut_y0          :8;	//(7:0,NA,112) //object local contrast LUT for delta control, y0
	UINT32 reg_obj_lc_delta_lut_x0          :8;	//(15:8,NA,0) //object local contrast LUT for delta control, x0
	UINT32 reg_obj_lc_delta_lut_y1          :8;	//(23:16,NA,128) //object local contrast LUT for delta control, y1
	UINT32 reg_obj_lc_delta_lut_x1          :8;	//(31:24,NA,64) //object local contrast LUT for delta control, x1
	};
}PE_O22_SHP_DP_SUM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462380 RW 0xffa0_6090
	UINT32 reg_obj_lc_delta_lut_y2          :8;	//(7:0,NA,144) //object local contrast LUT for delta control, y2
	UINT32 reg_obj_lc_delta_lut_x2          :8;	//(15:8,NA,96) //object local contrast LUT for delta control, x2
	UINT32 reg_obj_lc_delta_lut_y3          :8;	//(23:16,NA,160) //object local contrast LUT for delta control, y3
	UINT32 reg_obj_lc_delta_lut_x3          :8;	//(31:24,NA,255) //object local contrast LUT for delta control, x3
	};
}PE_O22_SHP_DP_SUM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462384 RW 0x2828_0000
	UINT32 reg_dp_sum_cg_lut_y0             :8;	//(7:0,NA,0) //dp_sum LUT for delta_cg control, y0
	UINT32 reg_dp_sum_cg_lut_x0             :8;	//(15:8,NA,0) //dp_sum LUT for delta_cg control, x0
	UINT32 reg_dp_sum_cg_lut_y1             :8;	//(23:16,NA,40) //dp_sum LUT for delta_cg control, y1
	UINT32 reg_dp_sum_cg_lut_x1             :8;	//(31:24,NA,40) //dp_sum LUT for delta_cg control, x1
	};
}PE_O22_SHP_DP_SUM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462388 RW 0xFFFF_5050
	UINT32 reg_dp_sum_cg_lut_y2             :8;	//(7:0,NA,80) //dp_sum LUT for delta_cg control, y2
	UINT32 reg_dp_sum_cg_lut_x2             :8;	//(15:8,NA,80) //dp_sum LUT for delta_cg control, x2
	UINT32 reg_dp_sum_cg_lut_y3             :8;	//(23:16,NA,255) //dp_sum LUT for delta_cg control, y3
	UINT32 reg_dp_sum_cg_lut_x3             :8;	//(31:24,NA,255) //dp_sum LUT for delta_cg control, x3
	};
}PE_O22_SHP_DP_SUM_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462390 RW 0x0000_0001
	UINT32 reg_psp_obj_en                   :1;	//(0:0,NA,1) //PSP object contrast enable
	UINT32 resvd                            :31;
	};
}PE_O22_SHP_PSP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462394 RW 0x2828_0000
	UINT32 reg_dp_sum_obj_lut_y0            :8;	//(7:0,NA,0) //dp_sum LUT for object control, y0
	UINT32 reg_dp_sum_obj_lut_x0            :8;	//(15:8,NA,0) //dp_sum LUT for object control, x0
	UINT32 reg_dp_sum_obj_lut_y1            :8;	//(23:16,NA,40) //dp_sum LUT for object control, y1
	UINT32 reg_dp_sum_obj_lut_x1            :8;	//(31:24,NA,40) //dp_sum LUT for object control, x1
	};
}PE_O22_SHP_DP_SUM_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462398 RW 0xFFFF_5050
	UINT32 reg_dp_sum_obj_lut_y2            :8;	//(7:0,NA,80) //dp_sum LUT for object control, y2
	UINT32 reg_dp_sum_obj_lut_x2            :8;	//(15:8,NA,80) //dp_sum LUT for object control, x2
	UINT32 reg_dp_sum_obj_lut_y3            :8;	//(23:16,NA,255) //dp_sum LUT for object control, y3
	UINT32 reg_dp_sum_obj_lut_x3            :8;	//(31:24,NA,255) //dp_sum LUT for object control, x3
	};
}PE_O22_SHP_DP_SUM_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623A0 RW 0x0000_0000
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
}PE_O22_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623A8 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623B0 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623C0 RW 0x0432_0c40
	UINT32 reg_region_text_en               :1;	//(0:0,NA,0) //region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//(6:4,NA,4) //
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//(15:8,NA,12) //
	UINT32 reg_region_text_add_max          :8;	//(23:16,NA,50) //
	UINT32 reg_region_text_cuthif           :3;	//(26:24,NA,4) //
	UINT32 resvd2                           :5;
	};
}PE_O22_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623C4 RW 0x0f50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //region texture LUT , x1
	};
}PE_O22_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623C8 RW 0x46c8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //region texture LUT , x3
	};
}PE_O22_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623CC RW 0x0000_ff00
	UINT32 reg_tmap_temp_iir_en             :1;	//(0:0,NA,0) //TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//(4:4,NA,0) //TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//(15:8,NA,255) //TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//(24:24,NA,0) //TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O22_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623D0 RW 0x2840_0a00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //tmap temporal previous blend LUT , x1
	};
}PE_O22_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623D4 RW 0x5080_3c60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //tmap temporal previous blend LUT , x3
	};
}PE_O22_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623D8 RW 0x08d0_00c0
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir positive LUT , x1
	};
}PE_O22_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623DC RW 0x30f0_10e0
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //tmap temporal iir positive LUT , x3
	};
}PE_O22_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623E0 RW 0x80c0_60d0
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //tmap temporal iir positive LUT , x5
	};
}PE_O22_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623E4 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir negative LUT , x1
	};
}PE_O22_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623E8 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //tmap temporal iir negative LUT , x3
	};
}PE_O22_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623EC RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //tmap temporal iir negative LUT , x5
	};
}PE_O22_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623F0 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x       :12;	//(11:0,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623F4 RW 0x086f_077f
	UINT32 reg_tmap_stat_win0_end_x         :12;	//(11:0,NA,1919) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//(27:16,NA,2159) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623F8 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x       :12;	//(11:0,NA,1920) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4623FC RW 0x0438_0eff
	UINT32 reg_tmap_stat_win1_end_x         :12;	//(11:0,NA,3839) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//(27:16,NA,1080) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462400 RW 0x8010_0179
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
}PE_O22_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462404 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O22_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462408 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O22_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46240C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O22_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462410 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O22_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462414 RW 0x0000_0000
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
}PE_O22_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462418 RW 0x0000_0040
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
}PE_O22_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46241C RW 0x0015_5550
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
}PE_O22_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462420 RW 0x0000_0040
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
}PE_O22_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462424 RW 0x002A_A040
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
}PE_O22_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462428 RW 0x002A_A040
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
}PE_O22_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46242C RW 0x000A_A040
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
}PE_O22_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462430 RW 0x0000_00E4
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
}PE_O22_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462434 RW 0x0000_5540
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
}PE_O22_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462438 RW 0x0020_5542
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
}PE_O22_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46243C RW 0x0008_1508
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
}PE_O22_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462440 RW 0x0002_0420
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
}PE_O22_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462444 RW 0x0000_8080
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
}PE_O22_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462448 RW 0x0000_2A00
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
}PE_O22_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46244C RW 0x0000_2A00
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
}PE_O22_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462450 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O22_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462454 RW 0x0000_2800
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
}PE_O22_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462458 RW 0x0005_0A00
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
}PE_O22_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46245C RW 0x0005_4280
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
}PE_O22_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462460 RW 0x0005_50A0
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
}PE_O22_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462464 RW 0x0005_4280
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
}PE_O22_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462468 RW 0x0005_0A00
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
}PE_O22_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46246C RW 0x0000_2800
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
}PE_O22_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462470 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O22_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462474 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462478 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46247C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462480 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O22_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462490 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462494 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624A0 RW 0x0000_0000
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
}PE_O22_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624A8 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624B0 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624BC RW 0x10BC_4DB3
	UINT32 reg_dj_text_gain_mmd_mul         :8;	//(7:0,NA,10) //DJ control register
	UINT32 reg_dj_text_gain_avg_mul         :8;	//(15:8,NA,20) //DJ control register
	UINT32 reg_dj_text_gain_threshold       :10;	//(25:16,NA,100) //DJ control register
	UINT32 reg_dj_text_gain_all_text_flag   :1;	//(26:26,NA,0) //DJ control register
	UINT32 resvd0                           :1;
	UINT32 reg_dj_text_gain_en              :1;	//(28:28,NA,1) //DJ control register
	UINT32 resvd1                           :3;
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624C0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir0_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir0_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624C4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir0_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir0_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir0_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir0_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624C8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir1_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir1_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624CC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir1_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir1_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir1_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir1_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624D0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir3_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir3_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624D4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir3_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir3_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir3_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir3_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624D8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir5_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir5_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624DC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir5_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir5_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir5_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir5_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624E0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir6_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir6_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624E4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir6_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir6_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir6_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir6_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624E8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir7_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir7_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624EC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir7_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir7_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir7_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir7_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624F0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir9_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir9_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624F4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir9_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir9_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir9_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir9_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624F8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir11_y0        :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x0        :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir11_y1        :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x1        :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4624FC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir11_y2        :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir11_x2        :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir11_y3        :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir11_x3        :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O22_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462500 RW 0x0000_0000
	UINT32 reg_color_region_en              :1;	//(0:0,NA,0) //color region processing enable
	UINT32 reg_color_region_debug_en        :1;	//(1:1,NA,0) //color region debug map enable
	UINT32 resvd0                           :2;
	UINT32 reg_chr_protection_en            :1;	//(4:4,NA,0) //chroma protection enable
	UINT32 resvd1                           :3;
	UINT32 reg_chr_compensation_en          :1;	//(8:8,NA,0) //chroma compensation enable
	UINT32 resvd2                           :23;
	};
}PE_O22_SHP_CHROMA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462504 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CHROMA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462508 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CHROMA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46250C RW 0x28FF_1400
	UINT32 reg_chr_gain_r0_cb_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R0, Cb, y0
	UINT32 reg_chr_gain_r0_cb_x0            :8;	//(15:8,NA,20) //chroma gain LUT, R0, Cb, x0
	UINT32 reg_chr_gain_r0_cb_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R0, Cb, y1
	UINT32 reg_chr_gain_r0_cb_x1            :8;	//(31:24,NA,40) //chroma gain LUT, R0, Cb, x1
	};
}PE_O22_SHP_CHROMA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462510 RW 0x7800_64FF
	UINT32 reg_chr_gain_r0_cb_y2            :8;	//(7:0,NA,255) //chroma gain LUT, R0, Cb, y2
	UINT32 reg_chr_gain_r0_cb_x2            :8;	//(15:8,NA,100) //chroma gain LUT, R0, Cb, x2
	UINT32 reg_chr_gain_r0_cb_y3            :8;	//(23:16,NA,0) //chroma gain LUT, R0, Cb, y3
	UINT32 reg_chr_gain_r0_cb_x3            :8;	//(31:24,NA,120) //chroma gain LUT, R0, Cb, x3
	};
}PE_O22_SHP_CHROMA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462514 RW 0x96FF_8200
	UINT32 reg_chr_gain_r0_cr_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R0, Cr, y0
	UINT32 reg_chr_gain_r0_cr_x0            :8;	//(15:8,NA,130) //chroma gain LUT, R0, Cr, x0
	UINT32 reg_chr_gain_r0_cr_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R0, Cr, y1
	UINT32 reg_chr_gain_r0_cr_x1            :8;	//(31:24,NA,150) //chroma gain LUT, R0, Cr, x1
	};
}PE_O22_SHP_CHROMA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462518 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r0_cr_y2            :8;	//(7:0,NA,200) //chroma gain LUT, R0, Cr, y2
	UINT32 reg_chr_gain_r0_cr_x2            :8;	//(15:8,NA,255) //chroma gain LUT, R0, Cr, x2
	UINT32 reg_chr_gain_r0_cr_y3            :8;	//(23:16,NA,240) //chroma gain LUT, R0, Cr, y3
	UINT32 reg_chr_gain_r0_cr_x3            :8;	//(31:24,NA,0) //chroma gain LUT, R0, Cr, x3
	};
}PE_O22_SHP_CHROMA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46251C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CHROMA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462520 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CHROMA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462524 RW 0x96FF_8200
	UINT32 reg_chr_gain_r1_cb_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R1, Cb, y0
	UINT32 reg_chr_gain_r1_cb_x0            :8;	//(15:8,NA,130) //chroma gain LUT, R1, Cb, x0
	UINT32 reg_chr_gain_r1_cb_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R1, Cb, y1
	UINT32 reg_chr_gain_r1_cb_x1            :8;	//(31:24,NA,150) //chroma gain LUT, R1, Cb, x1
	};
}PE_O22_SHP_CHROMA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462528 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r1_cb_y2            :8;	//(7:0,NA,200) //chroma gain LUT, R1, Cb, y2
	UINT32 reg_chr_gain_r1_cb_x2            :8;	//(15:8,NA,255) //chroma gain LUT, R1, Cb, x2
	UINT32 reg_chr_gain_r1_cb_y3            :8;	//(23:16,NA,240) //chroma gain LUT, R1, Cb, y3
	UINT32 reg_chr_gain_r1_cb_x3            :8;	//(31:24,NA,0) //chroma gain LUT, R1, Cb, x3
	};
}PE_O22_SHP_CHROMA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46252C RW 0x28FF_1400
	UINT32 reg_chr_gain_r1_cr_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R1, Cr, y0
	UINT32 reg_chr_gain_r1_cr_x0            :8;	//(15:8,NA,20) //chroma gain LUT, R1, Cr, x0
	UINT32 reg_chr_gain_r1_cr_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R1, Cr, y1
	UINT32 reg_chr_gain_r1_cr_x1            :8;	//(31:24,NA,40) //chroma gain LUT, R1, Cr, x1
	};
}PE_O22_SHP_CHROMA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462530 RW 0x7800_64FF
	UINT32 reg_chr_gain_r1_cr_y2            :8;	//(7:0,NA,255) //chroma gain LUT, R1, Cr, y2
	UINT32 reg_chr_gain_r1_cr_x2            :8;	//(15:8,NA,100) //chroma gain LUT, R1, Cr, x2
	UINT32 reg_chr_gain_r1_cr_y3            :8;	//(23:16,NA,0) //chroma gain LUT, R1, Cr, y3
	UINT32 reg_chr_gain_r1_cr_x3            :8;	//(31:24,NA,120) //chroma gain LUT, R1, Cr, x3
	};
}PE_O22_SHP_CHROMA_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462534 RW 0x00FF_0000
	UINT32 reg_chr_gain_r0_gain             :8;	//(7:0,NA,0) //chroma gain alpha, R0
	UINT32 resvd0                           :8;
	UINT32 reg_chr_gain_r1_gain             :8;	//(23:16,NA,255) //chroma gain alpha, R1
	UINT32 reg_chr_gain_sel                 :1;	//(24:24,NA,0) //0: {3'd0,region_gain}	1: {region_gain,3'd0}
	UINT32 resvd1                           :7;
	};
}PE_O22_SHP_CHROMA_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462538 RW 0x28FF_1400
	UINT32 reg_chr_comp_y0                  :8;	//(7:0,NA,0) //chroma comp. linear mapping, y0
	UINT32 reg_chr_comp_x0                  :8;	//(15:8,NA,20) //chroma comp. linear mapping, x0
	UINT32 reg_chr_comp_y1                  :8;	//(23:16,NA,255) //chroma comp. linear mapping, y1
	UINT32 reg_chr_comp_x1                  :8;	//(31:24,NA,40) //chroma comp. linear mapping, x1
	};
}PE_O22_SHP_CHROMA_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462550 RW 0x0000_2A60
	UINT32 reg_cti_en                       :1;	//(0:0,NA,0) //cti enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_filter_tap_size          :3;	//(6:4,NA,6) //000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_gain                     :8;	//(15:8,NA,42) //gain (3.5u)
	UINT32 resvd2                           :16;
	};
}PE_O22_SHP_CTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462554 RW 0x0001_1810
	UINT32 reg_cti_coring_th0               :8;	//(7:0,NA,16) //coring th0
	UINT32 reg_cti_coring_th1               :8;	//(15:8,NA,24) //coring_th1
	UINT32 reg_cti_coring_map_filter        :3;	//(18:16,NA,1) //000: no filtering	001: 5-tap filtering	010: 7-tap filtering	011: 9-tap filtering	100: 11-tap filtering	101: 13-tap filtering
	UINT32 resvd0                           :1;
	UINT32 reg_cti_coring_tap_size          :3;	//(22:20,NA,0) //000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_debug_mode               :2;	//(25:24,NA,0) //00: normal display	10: coring_map(cb)	11: coring_map(cr)
	UINT32 resvd2                           :6;
	};
}PE_O22_SHP_CTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462558 RW 0x0088_0850
	UINT32 reg_cti_ycm_en                   :1;	//(0:0,NA,0) //y/c merge enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_ycm_band_sel             :3;	//(6:4,NA,5) //y/c merge band sel
	UINT32 resvd1                           :1;
	UINT32 reg_cti_ycm_diff_th              :8;	//(15:8,NA,8) //y/c merge diff threshold
	UINT32 reg_cti_ycm_y_gain               :4;	//(19:16,NA,8) //y/c merge gain, Y
	UINT32 reg_cti_ycm_c_gain               :4;	//(23:20,NA,8) //y/c merge gain, C
	UINT32 resvd2                           :8;
	};
}PE_O22_SHP_CTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462560 RW 0x0000_0000
	UINT32 reg_flick_en                     :1;	//(0:0,NA,0) //frc flicker blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_flick_motion_sel             :2;	//(5:4,NA,0) //SHP FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1                           :2;
	UINT32 reg_flick_blur_type              :2;	//(9:8,NA,0) //frc flicker blur pel selection	0: cur pel[y][x+1]	1: cur pel[y][x-1]	2: average
	UINT32 resvd2                           :22;
	};
}PE_O22_SHP_FRC_FLICK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462564 RW 0x2040_0000
	UINT32 reg_flick_motion_lut_y0          :8;	//(7:0,NA,0) //frc flicker blur motion LUT point, y0
	UINT32 reg_flick_motion_lut_x0          :8;	//(15:8,NA,0) //frc flicker blur motion LUT point, x0
	UINT32 reg_flick_motion_lut_y1          :8;	//(23:16,NA,64) //frc flicker blur motion LUT point, y1
	UINT32 reg_flick_motion_lut_x1          :8;	//(31:24,NA,32) //frc flicker blur motion LUT point, x1
	};
}PE_O22_SHP_FRC_FLICK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462568 RW 0x80FF_4080
	UINT32 reg_flick_motion_lut_y2          :8;	//(7:0,NA,128) //frcflicker blur motion LUT point, y2
	UINT32 reg_flick_motion_lut_x2          :8;	//(15:8,NA,64) //frc flicker blur motion LUT point, x2
	UINT32 reg_flick_motion_lut_y3          :8;	//(23:16,NA,255) //frc flicker blur motion LUT point, y3
	UINT32 reg_flick_motion_lut_x3          :8;	//(31:24,NA,128) //frc flicker blur motion LUT point, x3
	};
}PE_O22_SHP_FRC_FLICK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46256C RW 0x0000_0080
	UINT32 reg_flick_master_gain            :8;	//(7:0,NA,128) //frc flicker blur master gain
	UINT32 resvd                            :24;
	};
}PE_O22_SHP_FRC_FLICK_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462570 RW 0x0000_0000
	UINT32 reg_frc_blur_en                  :1;	//(0:0,NA,0) //frc blur enable
	UINT32 reg_frc_blur_debug_en            :1;	//(1:1,NA,0) //frc blur debug en
	UINT32 resvd                            :30;
	};
}PE_O22_SHP_FRC_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462574 RW 0x1812_0C06
	UINT32 reg_frc_blur_cnt_th0             :6;	//(5:0,NA,6) //frc blur weight smoothing count threshold, 0
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th1             :6;	//(13:8,NA,12) //frc blur weight smoothing count threshold, 1
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th2             :6;	//(21:16,NA,18) //frc blur weight smoothing count threshold, 2
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th3             :6;	//(29:24,NA,24) //frc blur weight smoothing count threshold, 3
	UINT32 resvd3                           :2;
	};
}PE_O22_SHP_FRC_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462578 RW 0x302A_241E
	UINT32 reg_frc_blur_cnt_th4             :6;	//(5:0,NA,30) //frc blur weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th5             :6;	//(13:8,NA,36) //frc blur weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th6             :6;	//(21:16,NA,42) //frc blur weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th7             :6;	//(29:24,NA,48) //frc blur weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_O22_SHP_FRC_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46257C RW 0x8765_4321
	UINT32 reg_frc_blur_val0                :4;	//(3:0,NA,1) //frc blur weight smoothing count value, 0
	UINT32 reg_frc_blur_val1                :4;	//(7:4,NA,2) //frc blur weight smoothing count value, 1
	UINT32 reg_frc_blur_val2                :4;	//(11:8,NA,3) //frc blur weight smoothing count value, 2
	UINT32 reg_frc_blur_val3                :4;	//(15:12,NA,4) //frc blur weight smoothing count value, 3
	UINT32 reg_frc_blur_val4                :4;	//(19:16,NA,5) //frc blur weight smoothing count value, 4
	UINT32 reg_frc_blur_val5                :4;	//(23:20,NA,6) //frc blur weight smoothing count value, 5
	UINT32 reg_frc_blur_val6                :4;	//(27:24,NA,7) //frc blur weight smoothing count value, 6
	UINT32 reg_frc_blur_val7                :4;	//(31:28,NA,8) //frc blur weight smoothing count value, 7
	};
}PE_O22_SHP_FRC_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462580 RW 0x0000_0004
	UINT32 reg_frc_blur_coef_x8             :4;	//(3:0,NA,4) //frc blur filter coeff, x, [8]
	UINT32 resvd                            :28;
	};
}PE_O22_SHP_FRC_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462584 RW 0x4444_4433
	UINT32 reg_frc_blur_coef_x0             :4;	//(3:0,NA,3) //frc blur filter coeff, x, [0]/[16]
	UINT32 reg_frc_blur_coef_x1             :4;	//(7:4,NA,3) //frc blur filter coeff, x, [1]/[15]
	UINT32 reg_frc_blur_coef_x2             :4;	//(11:8,NA,4) //frc blur filter coeff, x, [2]/[14]
	UINT32 reg_frc_blur_coef_x3             :4;	//(15:12,NA,4) //frc blur filter coeff, x, [3]/[13]
	UINT32 reg_frc_blur_coef_x4             :4;	//(19:16,NA,4) //frc blur filter coeff, x, [4]/[12]
	UINT32 reg_frc_blur_coef_x5             :4;	//(23:20,NA,4) //frc blur filter coeff, x, [5]/[11]
	UINT32 reg_frc_blur_coef_x6             :4;	//(27:24,NA,4) //frc blur filter coeff, x, [6]/[10]
	UINT32 reg_frc_blur_coef_x7             :4;	//(31:28,NA,4) //frc blur filter coeff, x, [7]/[9]
	};
}PE_O22_SHP_FRC_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462588 RW 0x0000_0866
	UINT32 reg_frc_blur_coef_y0             :4;	//(3:0,NA,6) //frc blur filter coeff, y, [0]/[4]
	UINT32 reg_frc_blur_coef_y1             :4;	//(7:4,NA,6) //frc blur filter coeff, y, [1]/[3]
	UINT32 reg_frc_blur_coef_y2             :4;	//(11:8,NA,8) //frc blur filter coeff, y, [2]
	UINT32 resvd                            :20;
	};
}PE_O22_SHP_FRC_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462590 RW 0x0000_0000
	UINT32 reg_frc_halo_en                  :1;	//(0:0,NA,0) //frc halo enable
	UINT32 reg_frc_halo_debug_en            :1;	//(1:1,NA,0) //frc halo debug en
	UINT32 resvd                            :30;
	};
}PE_O22_SHP_FRC_HALO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462594 RW 0x1812_0C06
	UINT32 reg_frc_halo_cnt_th0             :6;	//(5:0,NA,6) //frc halo weight smoothing count threshold, 0
	UINT32 resvd0                           :2;
	UINT32 reg_frc_halo_cnt_th1             :6;	//(13:8,NA,12) //frc halo weight smoothing count threshold, 1
	UINT32 resvd1                           :2;
	UINT32 reg_frc_halo_cnt_th2             :6;	//(21:16,NA,18) //frc halo weight smoothing count threshold, 2
	UINT32 resvd2                           :2;
	UINT32 reg_frc_halo_cnt_th3             :6;	//(29:24,NA,24) //frc halo weight smoothing count threshold, 3
	UINT32 resvd3                           :2;
	};
}PE_O22_SHP_FRC_HALO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462598 RW 0x302A_241E
	UINT32 reg_frc_halo_cnt_th4             :6;	//(5:0,NA,30) //frc halo weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_halo_cnt_th5             :6;	//(13:8,NA,36) //frc halo weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_halo_cnt_th6             :6;	//(21:16,NA,42) //frc halo weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_halo_cnt_th7             :6;	//(29:24,NA,48) //frc halo weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_O22_SHP_FRC_HALO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46259C RW 0x8765_4321
	UINT32 reg_frc_halo_val0                :4;	//(3:0,NA,1) //frc halo weight smoothing count value, 0
	UINT32 reg_frc_halo_val1                :4;	//(7:4,NA,2) //frc halo weight smoothing count value, 1
	UINT32 reg_frc_halo_val2                :4;	//(11:8,NA,3) //frc halo weight smoothing count value, 2
	UINT32 reg_frc_halo_val3                :4;	//(15:12,NA,4) //frc halo weight smoothing count value, 3
	UINT32 reg_frc_halo_val4                :4;	//(19:16,NA,5) //frc halo weight smoothing count value, 4
	UINT32 reg_frc_halo_val5                :4;	//(23:20,NA,6) //frc halo weight smoothing count value, 5
	UINT32 reg_frc_halo_val6                :4;	//(27:24,NA,7) //frc halo weight smoothing count value, 6
	UINT32 reg_frc_halo_val7                :4;	//(31:28,NA,8) //frc halo weight smoothing count value, 7
	};
}PE_O22_SHP_FRC_HALO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4625A0 RW 0x0000_0000
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
}PE_O22_SHP_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4625A4 RW 0x0000_0000
	UINT32 reg_win_frc_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4625A8 RW 0x086F_0EFF
	UINT32 reg_win_frc_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4625AC RW 0x0000_0000
	UINT32 reg_win_frc_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4625B0 RW 0x086F_0EFF
	UINT32 reg_win_frc_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462600 RW 0x0000_0C00
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
}PE_O22_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462604 RW 0x0000_0000
	UINT32 reg_motion_gain_in_hoffset       :13;	//(12:0,NA,0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_voffset       :12;	//(27:16,NA,0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462608 RW 0x0011_001E
	UINT32 reg_motion_gain_in_hactive       :13;	//(12:0,NA,30) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vactive       :12;	//(27:16,NA,17) //input window active size
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46260C RW 0x0011_001E
	UINT32 reg_motion_gain_in_hsize         :13;	//(12:0,NA,30) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vsize         :12;	//(27:16,NA,17) //input source total size
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462610 RW 0x0870_0780
	UINT32 reg_motion_gain_out_pic_width    :13;	//(12:0,NA,1920) //width (default: 3840/2)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_pic_height   :12;	//(27:16,NA,2160) //height (default: 2160)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462614 RW 0x8000_3030
	UINT32 reg_motion_gain_phase_off_h      :6;	//(5:0,NA,-16) //vertical offset of initial pixel position (signed value)  	min: -31	max: +31
	UINT32 resvd0                           :2;
	UINT32 reg_motion_gain_phase_off_v      :6;	//(13:8,NA,-16) //horizontal offset of initial pixel position (signed value)  	min: -31	max: +31
	UINT32 resvd1                           :17;
	UINT32 reg_motion_gain_sampling_mode    :1;	//(31:31,NA,1) //0: normal-auto	1: manual-set
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462618 RW 0x0001_0001
	UINT32 reg_motion_gain_numerator_h      :13;	//(12:0,NA,1) //
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_numerator_v      :12;	//(27:16,NA,1) //
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46261C RW 0x0080_0040
	UINT32 reg_motion_gain_denominator_h    :13;	//(12:0,NA,64) //(default: (3840/2)/30)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_denominator_v    :12;	//(27:16,NA,128) //(default: 2160/17 -> 128)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462620 RW 0x0000_0000
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
}PE_O22_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462624 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x0        :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y0        :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462628 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x1        :12;	//(11:0,NA,0) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y1        :12;	//(27:16,NA,0) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46262C RW 0x0000_0000
	UINT32 reg_motion_gain_out_hoffset      :13;	//(12:0,NA,0) //output window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_voffset      :12;	//(27:16,NA,0) //output window offset
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462630 RW 0x0870_0780
	UINT32 reg_motion_gain_out_hactive      :13;	//(12:0,NA,1920) //output window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_vactive      :12;	//(27:16,NA,2160) //output window active size
	UINT32 resvd1                           :2;
//#if (SOC_DEVICE < O22A0)
//	UINT32 reg_motion_forcing               :2;		//31:30
//#else
	UINT32 logo_l7sc_out_sel                :2;	//(31:30,NA,0) //0 : logo_l7sc_out	1 : 	2 : '0'	3 : '1'
//#endif
	};
}PE_O22_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462640 RW 0x0000_0000
	UINT32 reg_motion_prot_adaptive_en      :1;	//(0:0,NA,0) //motion protection enable
	UINT32 resvd                            :31;
	};
}PE_O22_SHP_MOTION_PROT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462644 RW 0x4040_0000
	UINT32 reg_motion_prot_lut_a_y0         :8;	//(7:0,NA,0) //motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0         :8;	//(15:8,NA,0) //motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1         :8;	//(23:16,NA,64) //motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1         :8;	//(31:24,NA,64) //motion gain LUT, A, x1
	};
}PE_O22_SHP_MOTION_PROT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462648 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_a_y2         :8;	//(7:0,NA,80) //motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2         :8;	//(15:8,NA,110) //motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3         :8;	//(23:16,NA,120) //motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3         :8;	//(31:24,NA,255) //motion gain LUT, A, x3
	};
}PE_O22_SHP_MOTION_PROT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46264C RW 0x4040_0000
	UINT32 reg_motion_prot_lut_t_y0         :8;	//(7:0,NA,0) //motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0         :8;	//(15:8,NA,0) //motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1         :8;	//(23:16,NA,64) //motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1         :8;	//(31:24,NA,64) //motion gain LUT, T, x1
	};
}PE_O22_SHP_MOTION_PROT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462650 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_t_y2         :8;	//(7:0,NA,80) //motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2         :8;	//(15:8,NA,110) //motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3         :8;	//(23:16,NA,120) //motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3         :8;	//(31:24,NA,255) //motion gain LUT, T, x3
	};
}PE_O22_SHP_MOTION_PROT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462670 RW 0x0000_0000
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
}PE_O22_SHP_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462674 RW 0x0000_0000
	UINT32 reg_win_mot_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462678 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46267C RW 0x0000_0000
	UINT32 reg_win_mot_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462680 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462690 RW 0x0000_0000
	UINT32 reg_obj_shp_en                   :1;	//(0:0,NA,0) //0 : disable	1 : enable
	UINT32 resvd0                           :3;
	UINT32 reg_obj_sel_bit                  :1;	//(4:4,NA,0) //0 : 7bit	1 : 6bit
	UINT32 resvd1                           :27;
	};
}PE_O22_SHP_OBJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462694 RW 0x4080_005a
	UINT32 reg_obj_face_gain_lut_y0         :8;	//(7:0,NA,90) //object face gain LUT , y2
	UINT32 reg_obj_face_gain_lut_x0         :8;	//(15:8,NA,0) //object face gain LUT , x2
	UINT32 reg_obj_face_gain_lut_y1         :8;	//(23:16,NA,128) //object face gain LUT , y3
	UINT32 reg_obj_face_gain_lut_x1         :8;	//(31:24,NA,64) //object face gain LUT , x3
	};
}PE_O22_SHP_OBJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462698 RW 0xc4ff_6090
	UINT32 reg_obj_face_gain_lut_y2         :8;	//(7:0,NA,144) //object face gain LUT , y0
	UINT32 reg_obj_face_gain_lut_x2         :8;	//(15:8,NA,96) //object face gain LUT , x0
	UINT32 reg_obj_face_gain_lut_y3         :8;	//(23:16,NA,255) //object face gain LUT , y1
	UINT32 reg_obj_face_gain_lut_x3         :8;	//(31:24,NA,196) //object face gain LUT , x1
	};
}PE_O22_SHP_OBJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46269C RW 0x2080_005a
	UINT32 reg_obj_obj_gain_lut_y0          :8;	//(7:0,NA,90) //object object gain LUT , y2
	UINT32 reg_obj_obj_gain_lut_x0          :8;	//(15:8,NA,0) //object object gain LUT , x2
	UINT32 reg_obj_obj_gain_lut_y1          :8;	//(23:16,NA,128) //object object gain LUT , y3
	UINT32 reg_obj_obj_gain_lut_x1          :8;	//(31:24,NA,32) //object object gain LUT , x3
	};
}PE_O22_SHP_OBJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626A0 RW 0x90b0_4090
	UINT32 reg_obj_obj_gain_lut_y2          :8;	//(7:0,NA,144) //object object gain LUT , y0
	UINT32 reg_obj_obj_gain_lut_x2          :8;	//(15:8,NA,64) //object object gain LUT , x0
	UINT32 reg_obj_obj_gain_lut_y3          :8;	//(23:16,NA,176) //object object gain LUT , y1
	UINT32 reg_obj_obj_gain_lut_x3          :8;	//(31:24,NA,144) //object object gain LUT , x1
	};
}PE_O22_SHP_OBJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626A4 RW 0x1090_00ac
	UINT32 reg_obj_final_blend_obj_lut_y0   :8;	//(7:0,NA,172) //object final_blend_obj LUT , y2
	UINT32 reg_obj_final_blend_obj_lut_x0   :8;	//(15:8,NA,0) //object final_blend_obj LUT , x2
	UINT32 reg_obj_final_blend_obj_lut_y1   :8;	//(23:16,NA,144) //object final_blend_obj LUT , y3
	UINT32 reg_obj_final_blend_obj_lut_x1   :8;	//(31:24,NA,16) //object final_blend_obj LUT , x3
	};
}PE_O22_SHP_OBJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626A8 RW 0x8000_2060
	UINT32 reg_obj_final_blend_obj_lut_y2   :8;	//(7:0,NA,96) //object final_blend_obj LUT , y0
	UINT32 reg_obj_final_blend_obj_lut_x2   :8;	//(15:8,NA,32) //object final_blend_obj LUT , x0
	UINT32 reg_obj_final_blend_obj_lut_y3   :8;	//(23:16,NA,0) //object final_blend_obj LUT , y1
	UINT32 reg_obj_final_blend_obj_lut_x3   :8;	//(31:24,NA,128) //object final_blend_obj LUT , x1
	};
}PE_O22_SHP_OBJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626AC RW 0x10dc_00c4
	UINT32 reg_obj_final_blend_face_lut_y0  :8;	//(7:0,NA,196) //object final_blend_face LUT , y2
	UINT32 reg_obj_final_blend_face_lut_x0  :8;	//(15:8,NA,0) //object final_blend_face LUT , x2
	UINT32 reg_obj_final_blend_face_lut_y1  :8;	//(23:16,NA,220) //object final_blend_face LUT , y3
	UINT32 reg_obj_final_blend_face_lut_x1  :8;	//(31:24,NA,16) //object final_blend_face LUT , x3
	};
}PE_O22_SHP_OBJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626B0 RW 0x40ff_20dc
	UINT32 reg_obj_final_blend_face_lut_y2  :8;	//(7:0,NA,220) //object final_blend_face LUT , y0
	UINT32 reg_obj_final_blend_face_lut_x2  :8;	//(15:8,NA,32) //object final_blend_face LUT , x0
	UINT32 reg_obj_final_blend_face_lut_y3  :8;	//(23:16,NA,255) //object final_blend_face LUT , y1
	UINT32 reg_obj_final_blend_face_lut_x3  :8;	//(31:24,NA,64) //object final_blend_face LUT , x1
	};
}PE_O22_SHP_OBJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626B4 RW 0x3060_0050
	UINT32 reg_obj_master_gain_a_map_lut_y0 :8;	//(7:0,NA,80) //object master_gain LUT , y2
	UINT32 reg_obj_master_gain_a_map_lut_x0 :8;	//(15:8,NA,0) //object master_gain LUT , x2
	UINT32 reg_obj_master_gain_a_map_lut_y1 :8;	//(23:16,NA,96) //object master_gain LUT , y3
	UINT32 reg_obj_master_gain_a_map_lut_x1 :8;	//(31:24,NA,48) //object master_gain LUT , x3
	};
}PE_O22_SHP_OBJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626B8 RW 0x9080_6080
	UINT32 reg_obj_master_gain_a_map_lut_y2 :8;	//(7:0,NA,128) //object master_gain LUT , y0
	UINT32 reg_obj_master_gain_a_map_lut_x2 :8;	//(15:8,NA,96) //object master_gain LUT , x0
	UINT32 reg_obj_master_gain_a_map_lut_y3 :8;	//(23:16,NA,128) //object master_gain LUT , y1
	UINT32 reg_obj_master_gain_a_map_lut_x3 :8;	//(31:24,NA,144) //object master_gain LUT , x1
	};
}PE_O22_SHP_OBJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626BC RW 0x3060_0050
	UINT32 reg_obj_master_gain_t_map_lut_y0 :8;	//(7:0,NA,80) //object master_gain LUT , y2
	UINT32 reg_obj_master_gain_t_map_lut_x0 :8;	//(15:8,NA,0) //object master_gain LUT , x2
	UINT32 reg_obj_master_gain_t_map_lut_y1 :8;	//(23:16,NA,96) //object master_gain LUT , y3
	UINT32 reg_obj_master_gain_t_map_lut_x1 :8;	//(31:24,NA,48) //object master_gain LUT , x3
	};
}PE_O22_SHP_OBJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4626C0 RW 0x9080_6080
	UINT32 reg_obj_master_gain_t_map_lut_y2 :8;	//(7:0,NA,128) //object master_gain LUT , y0
	UINT32 reg_obj_master_gain_t_map_lut_x2 :8;	//(15:8,NA,96) //object master_gain LUT , x0
	UINT32 reg_obj_master_gain_t_map_lut_y3 :8;	//(23:16,NA,128) //object master_gain LUT , y1
	UINT32 reg_obj_master_gain_t_map_lut_x3 :8;	//(31:24,NA,144) //object master_gain LUT , x1
	};
}PE_O22_SHP_OBJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627A0 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627A4 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627A8 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627AC RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627B0 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O22_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627B4 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O22_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627D0 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627D4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627D8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627DC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627E0 RO 0x0000_0000
	UINT32 ro_buf_rptr                      :2;	//(1:0,NA,0) //
	UINT32 ro_buf_wptr_d                    :2;	//(3:2,NA,0) //
	UINT32 ro_core_wd_ptr                   :2;	//(5:4,NA,0) //
	UINT32 ro_buf_rcnt                      :10;	//(15:6,NA,0) //(reg_ro_buf_wrsel==1) ? {2'd0,r_ro_buf_rd} : r_buf_rcnt
	UINT32 ro_buf_wcnt                      :10;	//(25:16,NA,0) //(reg_ro_buf_wrsel==1) ? {2'd0,r_ro_buf_wd} : r_buf_wcnt
	UINT32 ro_buf_wre_cnt                   :4;	//(29:26,NA,0) //
	UINT32 resvd                            :2;
	};
}PE_O22_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627E4 RO 0x0000_0000
	UINT32 ro_out_v_line                    :12;	//(11:0,NA,0) //
	UINT32 resvd0                           :4;
	UINT32 ro_in_v_line                     :12;	//(27:16,NA,0) //
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_MOTION_GAIN_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627E8 RO 0x0000_0000
	UINT32 ro_edge_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_EDGE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627EC RO 0x0000_0000
	UINT32 ro_edge_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_EDGE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627F0 RO 0x0000_0000
	UINT32 ro_edge_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_EDGE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627F4 RO 0x0000_0000
	UINT32 ro_edge_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_EDGE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627F8 RO 0x0000_0000
	UINT32 ro_edge_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_EDGE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4627FC RO 0x0000_0000
	UINT32 ro_edge_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_11                :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_EDGE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462800 RO 0x0000_0000
	UINT32 ro_tmap_status_window0           :32;	//(31:0,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462804 RO 0x0000_0000
	UINT32 ro_tmap_status_window1           :32;	//(31:0,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462808 RO 0x0000_0000
	UINT32 ro_tmap_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46280C RO 0x0000_0000
	UINT32 ro_tmap_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462810 RO 0x0000_0000
	UINT32 ro_tmap_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462814 RO 0x0000_0000
	UINT32 ro_tmap_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462818 RO 0x0000_0000
	UINT32 ro_tmap_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46281C RO 0x0000_0000
	UINT32 ro_tmap_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_11                :16;	//(31:16,NA,0) //
	};
}PE_O22_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462820 RW 0x0000_0000
	UINT32 reg_core0_win_face_win0_en       :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_face_win1_en       :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_face_win01_en      :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_face_win_outside   :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_face_win_en        :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_face_bdr_alpha     :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_face_bdr_wid       :2;	//(14:13,NA,0) //border width
	UINT32 reg_core0_win_face_bdr_en        :1;	//(15:15,NA,0) //border enable
	UINT32 reg_core0_win_face_cr5           :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_face_cb5           :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_face_yy6           :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_O22_SHP_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462824 RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w0_x0     :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w0_y0     :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462828 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w0_x1     :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w0_y1     :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46282C RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w1_x0     :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w1_y0     :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462830 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w1_x1     :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w1_y1     :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462834 RW 0x0000_0000
	UINT32 reg_core0_win_face_value         :8;	//(7:0,NA,0) //force face value
	UINT32 resvd                            :24;
	};
}PE_O22_SHP_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462838 RW 0x0000_0000
	UINT32 reg_core0_win_body_win0_en       :1;	//(0:0,NA,0) //1: select only window0 as active area
	UINT32 reg_core0_win_body_win1_en       :1;	//(1:1,NA,0) //1: select only window1 as active area
	UINT32 reg_core0_win_body_win01_en      :1;	//(2:2,NA,0) //1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_body_win_outside   :1;	//(6:6,NA,0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_body_win_en        :1;	//(7:7,NA,0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_body_bdr_alpha     :5;	//(12:8,NA,0) //border alpha for alpha-blending
	UINT32 reg_core0_win_body_bdr_wid       :2;	//(14:13,NA,0) //border width
	UINT32 reg_core0_win_body_bdr_en        :1;	//(15:15,NA,0) //border enable
	UINT32 reg_core0_win_body_cr5           :5;	//(20:16,NA,0) //border color: cr5
	UINT32 reg_core0_win_body_cb5           :5;	//(25:21,NA,0) //border color: cb5
	UINT32 reg_core0_win_body_yy6           :6;	//(31:26,NA,0) //border color: yy6
	};
}PE_O22_SHP_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46283C RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w0_x0     :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w0_y0     :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462840 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w0_x1     :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w0_y1     :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462844 RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w1_x0     :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w1_y0     :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC462848 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w1_x1     :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w1_y1     :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_SHP_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46284C RW 0x0000_0000
	UINT32 reg_core0_win_body_value         :8;	//(7:0,NA,0) //force body value
	UINT32 resvd                            :24;
	};
}PE_O22_SHP_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4628F0 RW 0x0000_0000
	UINT32 reg_drc_apb_write_cont			:2;		//1:0	drc curv update counter
	UINT32 resvd0							:1;
	UINT32 reg_drc_write_cont				:2;		//4:3	drc curv update counter
	UINT32 resvd1							:3;
	UINT32 reg_pre_norm						:8;		//15:8	IWP - iir weight prev norm
	UINT32 reg_cur_norm						:8;		//23:16	IWC - iir weight cur  norm
	UINT32 reg_pre_sc						:8;		//31:24	IWSP - iir weight scene change prev sc
	};
}PE_O22_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4628F4 RW 0x0000_0000
	UINT32 reg_cur_sc						:8;		//7:0	IWSC - iir weight scene change cur sc
	UINT32 reg_ui_gain_w					:8;		//15:8	UGW - ui gain white
	UINT32 reg_ui_gain_b					:8;		//23:16 UGB - ui gain black
	UINT32 reg_vy_mode                      :2;		//25:24 ui rgb select
	UINT32 resvd0							:6;		
	};
}PE_O22_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4628F8 RW 0x0000_0000
	UINT32 reg_obc_debug                      : 2;  // 1:0, 0: shp result   1 : face map   2 : object map
	};
}PE_O22_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4628FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_SHP_FSW_CTRL_03_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460700 RW 0x08700F00
	UINT32 reg_img_wid                      :12;	//(11:0,RW,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//(27:16,RW,0x870) //vertical resolution   2160
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_OBC_HEAD_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460704 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,RW,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,RW,0x10) //Block size       16
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :8;	//(23:16,RW,0xF0) //Number of hblock 240
	UINT32 reg_l5_hei                       :8;	//(31:24,RW,0x87) //Number of vblock 135
	};
}PE_O22_VSD_OBC_HEAD_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460708 RW 0x00
	UINT32 reg_vs_inv                       :1;	//(0,RW,0x00) //vs inversion
	UINT32 reg_psp_en                       :1;	//(1,RW,0x00) //psp enable : ?�체 enable
	UINT32 reg_hist_sel                     :2;	//(3:2,RW,0x00) //histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//(8:4,RW,0x00) //line 경계?�서 repeat ?�킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//(9,RW,0x00) //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//(14:10,RW,0x00) //frame 경계?�서 repeat ?�킬 v line 개수
	UINT32 reserved                         :1;	//(15,RW,0x00) //fg memory??mee off
	UINT32 reg_margin_hei                   :8;	//(23:16,RW,0x00) //edge extraction??V margin
	UINT32 reg_margin_wid                   :8;	//(31:24,RW,0x00) //edge extraction??H margin
	};
}PE_O22_VSD_OBC_HEAD_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46070C RW 0x3F3F0000
	UINT32 y0_point                         :6;	//(5:0,NA,0x00) //control point of Y0
	UINT32 resvd0                           :2;
	UINT32 x0_point                         :6;	//(13:8,NA,0x00) //control point of X0
	UINT32 resvd1                           :2;
	UINT32 y1_point                         :6;	//(21:16,NA,0x3F) //control point of Y1
	UINT32 resvd2                           :2;
	UINT32 x1_point                         :6;	//(29:24,NA,0x3F) //control point of X1
	UINT32 resvd3                           :2;
	};
}PE_O22_VSD_OBC_HEAD_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460710 RW 0x3F3F3F3F
	UINT32 y2_point                         :6;	//(5:0,NA,0x3F) //control point of Y2
	UINT32 resvd0                           :2;
	UINT32 x2_point                         :6;	//(13:8,NA,0x3F) //control point of X2
	UINT32 resvd1                           :2;
	UINT32 y3_point                         :6;	//(21:16,NA,0x3F) //control point of Y3
	UINT32 resvd2                           :2;
	UINT32 x3_point                         :6;	//(29:24,NA,0x3F) //control point of X3
	UINT32 resvd3                           :2;
	};
}PE_O22_VSD_OBC_HEAD_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460748 RW 0x00030000
	UINT32 reg_sel_sync_gain                :2;	//(1:0,RW,0x0) //refine 0 vs, 1 va, 2 num
	UINT32 reg_sel_sync_fifo                :2;	//(3:2,RW,0x0) //refine fifo 0 vs, 1 va, 2 num
	UINT32 reg_debug_test                   :1;	//(4,RW,0x0) //
	UINT32 reg_start_pulse                  :1;	//(5,RW,0x0) //0 vs, 1 va
	UINT32 reg_pic_init_sel                 :1;	//(6,RW,0x0) //3x3 blur 0 vs, 1 va
	UINT32 resvd                            :1;
	UINT32 refine_num                       :12;	//(19:8,RW,0x0) //start pulse from V falling : num*256
	UINT32 fifo_num                         :12;	//(31:20,RW,0x0) //start pulse from V falling : num*256
	};
}PE_O22_VSD_OBC_HEAD_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460770 RW 0x12C00080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x00) //reset cnt 12bit(0~4095)
	};
}PE_O22_VSD_OBC_HEAD_REFINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460774 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
}PE_O22_VSD_OBC_HEAD_REFINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460778 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
}PE_O22_VSD_OBC_HEAD_REFINE_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46077C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O22_VSD_OBC_HEAD_REFINE_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460780 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O22_VSD_OBC_HEAD_REFINE_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460200 RW 0x8310_0000
	UINT32 resvd0                           :16;
	UINT32 reg_debug_mode                   :4;	//(19:16,NA,0x0) //0: normal	1: RCE_P ( R,G,B )	2: RCE_L ( R,G,B )	3: head_gain (W = R&G&B )	4: body_gain (W = R&G&B ) 	5: txtr_bain (W = R&G&B ) 	6: FACE+BODY (R = head_gain , G = body gain, B = 0)	7: FACE+BODY+TXTR (R = head_gain , G = body gain, B = txtr_gain)	8:face_body_blend (W = R&G&B )	9:final_blend(W = R&G&B )
	UINT32 reg_out_winmode_dly_sel          :2;	//(21:20,NA,0x1) //0: 43T (DTM 23T)	1: 21T (DTM 1T)	2: 22T (DTM 2T)
	UINT32 resvd1                           :2;
	UINT32 reg_ocsc_en                      :1;	//(24,NA,0x1) //
	UINT32 reg_icsc_en                      :1;	//(25,NA,0x1) //
	UINT32 resvd2                           :5;
	UINT32 reg_obe_en                       :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_000_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460204 RW 0x1E00_10E0
	UINT32 reg_heigt                        :16;	//(15:0,NA,0x10E0) //4320
	UINT32 reg_width                        :16;	//(31:16,NA,0x1E00) //7680
	};
}PE_O22_VSD_OBE_CTRL_001_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460208 RW 0x0000_0000
	UINT32 reg_bg_body_hist_th              :8;	//(7:0,NA,0x00) //
	UINT32 reg_bg_head_hist_th              :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_hist_th                 :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_hist_th                 :8;	//(31:24,NA,0x00) //
	};
}PE_O22_VSD_OBE_CTRL_002_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46020C RW 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 reg_bg_txtr_hist_th              :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_hist_th                 :8;	//(31:24,NA,0x00) //
	};
}PE_O22_VSD_OBE_CTRL_003_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460210 RW 0x0000_0000
	UINT32 reg_sat_prsv_ratio               :8;	//(7:0,NA,0x00) //
	UINT32 reg_hue_prsv_ratio               :8;	//(15:8,NA,0x00) //
	UINT32 reg_sat_prsv_en                  :1;	//(16,NA,0x0) //
	UINT32 reg_hue_prsv_en                  :1;	//(17,NA,0x0) //
	UINT32 resvd                            :13;
	UINT32 reg_hsp_en                       :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_004_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460214 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,NA,0x0000_0000) //
	};
}PE_O22_VSD_OBE_CTRL_005_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460218 RW 0x0000_0000
	UINT32 reg_ind_addr_ai                  :9;	//(8:0,NA,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_ind_ai                       :1;	//(12,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ind_load                     :1;	//(15,NA,0x0) //not use
	UINT32 resvd2                           :16;
	};
}PE_O22_VSD_OBE_IND_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46021C RW 0x0000_0000
	UINT32 reg_ind_data_wr                  :32;	//(31:0,NA,0x0000_0000) //not use
	};
}PE_O22_VSD_OBE_IND_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460220 RW 0x0000_0000
	UINT32 reg_ind_data_rd                  :32;	//(31:0,NA,0x0000_0000) //
	};
}PE_O22_VSD_OBE_IND_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460224 RW 0x1000_7D12
	UINT32 reg_icsc_coef1                   :15;	//(14:0,NA,0x7D12) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef0                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_009_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460228 RW 0x78A8_1000
	UINT32 reg_icsc_coef3                   :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef2                   :15;	//(30:16,NA,0x78A8) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_010_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46022C RW 0x1D0E_0000
	UINT32 reg_icsc_coef5                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef4                   :15;	//(30:16,NA,0x1D0E) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_011_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460230 RW 0x1000_0000
	UINT32 reg_icsc_coef7                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef6                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_012_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460234 RW 0x18A4_0000
	UINT32 resvd0                           :16;
	UINT32 reg_icsc_coef8                   :15;	//(30:16,NA,0x18A4) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_013_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460238 RW 0x0000_7E00
	UINT32 reg_icsc_ofst1                   :11;	//(10:0,NA,0x7E00) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_OBE_CTRL_014_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46023C RW 0x7E00_0000
	UINT32 reg_icsc_ofst3                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst2                   :11;	//(26:16,NA,0x7E00) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_OBE_CTRL_015_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460240 RW 0x0000_0000
	UINT32 reg_icsc_ofst5                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst4                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_OBE_CTRL_016_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460244 RW 0x09D3_00FE
	UINT32 reg_ocsc_coef1                   :15;	//(14:0,NA,0x00FE) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef0                   :15;	//(30:16,NA,0x09D3) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_017_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460248 RW 0x02EE_7A98
	UINT32 reg_ocsc_coef3                   :15;	//(14:0,NA,0x7A98) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef2                   :15;	//(30:16,NA,0x02EE) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_018_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46024C RW 0x0706_7E62
	UINT32 reg_ocsc_coef5                   :15;	//(14:0,NA,0x7E62) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef4                   :15;	//(30:16,NA,0x0706) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_019_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460250 RW 0x799E_7F5C
	UINT32 reg_ocsc_coef7                   :15;	//(14:0,NA,0x7F5C) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef6                   :15;	//(30:16,NA,0x799E) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_020_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460254 RW 0x0706_0000
	UINT32 resvd0                           :16;
	UINT32 reg_ocsc_coef8                   :15;	//(30:16,NA,0x0706) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_OBE_CTRL_021_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460258 RW 0x0000_0000
	UINT32 reg_ocsc_ofst1                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_OBE_CTRL_022_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46025C RW 0x0000_0040
	UINT32 reg_ocsc_ofst3                   :11;	//(10:0,NA,0x0040) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst2                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_OBE_CTRL_023_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460260 RW 0x0200_0200
	UINT32 reg_ocsc_ofst5                   :11;	//(10:0,NA,0x0200) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst4                   :11;	//(26:16,NA,0x0200) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_OBE_CTRL_024_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460264 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_txtr_master_gain             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x00) //
	};
}PE_O22_VSD_OBE_CTRL_025_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460268 RW 0x0080_0080
	UINT32 reg_final_blend_lut_y2           :8;	//(7:0,NA,0x80) //
	UINT32 reg_final_blend_lut_x2           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y3           :8;	//(23:16,NA,0x80) //
	UINT32 reg_final_blend_lut_x3           :8;	//(31:24,NA,0x00) //for RCE_P, RCE_L blending
	};
}PE_O22_VSD_OBE_CTRL_026_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46026C RW 0x0080_0080
	UINT32 reg_final_blend_lut_y0           :8;	//(7:0,NA,0x80) //
	UINT32 reg_final_blend_lut_x0           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y1           :8;	//(23:16,NA,0x80) //
	UINT32 reg_final_blend_lut_x1           :8;	//(31:24,NA,0x00) //for RCE_P, RCE_L blending
	};
}PE_O22_VSD_OBE_CTRL_027_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460270 RW 0x0000_0000
	UINT32 reg_head_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_028_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460274 RW 0x0000_0000
	UINT32 reg_head_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_029_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460278 RW 0x0000_0000
	UINT32 reg_head_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_030_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46027C RW 0x0000_0000
	UINT32 reg_head_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_031_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460280 RW 0x0000_0000
	UINT32 reg_head_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_032_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460284 RW 0x0000_0000
	UINT32 reg_head_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_033_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460288 RW 0x0000_0000
	UINT32 reg_head_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_034_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46028C RW 0x0000_0000
	UINT32 reg_head_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_035_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460290 RW 0x0000_0000
	UINT32 reg_head_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_036_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460294 RW 0x0000_0000
	UINT32 reg_head_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_037_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460298 RW 0x0000_0000
	UINT32 reg_head_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_038_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46029C RW 0x0000_0000
	UINT32 reg_head_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_039_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602A0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_040_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602A4 RW 0x0000_0000
	UINT32 reg_head_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_041_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602A8 RW 0x0000_0000
	UINT32 reg_head_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_042_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602AC RW 0x0000_0000
	UINT32 reg_head_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_043_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602B0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_044_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602B4 RW 0x0000_0000
	UINT32 reg_head_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_045_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602B8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_046_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602BC RW 0x0000_0000
	UINT32 reg_body_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_047_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602C0 RW 0x0000_0000
	UINT32 reg_body_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_048_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602C4 RW 0x0000_0000
	UINT32 reg_body_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_049_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602C8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_050_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602CC RW 0x0000_0000
	UINT32 reg_body_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_051_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602D0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_052_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602D4 RW 0x0000_0000
	UINT32 reg_body_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_053_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602D8 RW 0x0000_0000
	UINT32 reg_body_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_054_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602DC RW 0x0000_0000
	UINT32 reg_body_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_055_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602E0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_056_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602E4 RW 0x0000_0000
	UINT32 reg_body_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_057_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602E8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_058_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602EC RW 0x0000_0000
	UINT32 reg_body_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_059_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602F0 RW 0x0000_0000
	UINT32 reg_body_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_060_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602F4 RW 0x0000_0000
	UINT32 reg_body_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_061_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602F8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_062_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4602FC RW 0x0000_0000
	UINT32 reg_body_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_063_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460300 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_064_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460304 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_065_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460308 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_066_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46030C RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_067_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460310 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_068_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460314 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_069_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460318 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_070_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46031C RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_071_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460320 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_072_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460324 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_073_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460328 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_074_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46032C RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_075_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460330 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_076_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460334 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_077_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460338 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_078_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46033C RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_079_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460340 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_080_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460344 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_081_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460348 RW 0x0000_0000
	UINT32 reg_head_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_gain_lut_x3             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O22_VSD_OBE_CTRL_082_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46034C RW 0x0000_0000
	UINT32 reg_head_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_gain_lut_x1             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O22_VSD_OBE_CTRL_083_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460350 RW 0x0000_0000
	UINT32 reg_body_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_gain_lut_x3             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O22_VSD_OBE_CTRL_084_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460354 RW 0x0000_0000
	UINT32 reg_body_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_gain_lut_x1             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O22_VSD_OBE_CTRL_085_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460358 RW 0x0000_0000
	UINT32 reg_body_head_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x3             :8;	//(31:24,NA,0x00) //body-head
	};
}PE_O22_VSD_OBE_CTRL_086_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46035C RW 0x0000_0000
	UINT32 reg_body_head_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x1             :8;	//(31:24,NA,0x00) //
	};
}PE_O22_VSD_OBE_CTRL_087_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460360 RW 0x0000_0000
	UINT32 reg_head_body_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x3             :8;	//(31:24,NA,0x00) //head-body
	};
}PE_O22_VSD_OBE_CTRL_088_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460364 RW 0x0000_0000
	UINT32 reg_head_body_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x1             :8;	//(31:24,NA,0x00) //
	};
}PE_O22_VSD_OBE_CTRL_089_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460368 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_090_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46036C RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_091_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460370 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_092_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460374 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_093_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460378 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_094_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46037C RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_095_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460380 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_096_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460384 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_097_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460388 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_098_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46038C RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_099_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460390 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460394 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460398 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46039C RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603A0 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603A4 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603A8 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603AC RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603B0 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603B4 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603B8 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_110_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603BC RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_111_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603C0 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_112_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603C4 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_113_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603C8 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_114_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603CC RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_115_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603D0 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_116_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603D4 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_117_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603D8 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_118_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603DC RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_119_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603E0 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_120_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603E4 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_121_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603E8 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_122_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603EC RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_123_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603F0 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_124_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603F4 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_OBE_CTRL_125_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603F8 RW 0x0000_0000
	UINT32 reg_txtr_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x3             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O22_VSD_OBE_CTRL_126_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4603FC RW 0x0000_0000
	UINT32 reg_txtr_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x1             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O22_VSD_OBE_CTRL_127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460400 RW 0x0000_0000
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x000) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_128_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460404 RW 0x0780_0438
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_129_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460408 RW 0x0780_0438
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_130_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46040C RW 0x0F00_0870
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x870) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0xF00) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_131_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460410 RW 0x0000_0000
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x000) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_132_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460414 RW 0x0780_0438
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_133_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460418 RW 0x0780_0438
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_134_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46041C RW 0x0F00_0870
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x870) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0xF00) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_O22_VSD_OBE_CTRL_135_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460420 RW 0x0000_0000
	UINT32 reg_hist_body_gain_lut_y2        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x2        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y3        :8;	//(23:16,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x3        :8;	//(31:24,NA,0x00) //o22/f22 4pt for hist
	};
}PE_O22_VSD_OBE_CTRL_136_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460424 RW 0x0000_0000
	UINT32 reg_hist_body_gain_lut_y0        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x0        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y1        :8;	//(23:16,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x1        :8;	//(31:24,NA,0x00) //o22/f22 4pt for hist
	};
}PE_O22_VSD_OBE_CTRL_137_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460C00 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O22_VSD_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C04 RW 0x0438_0780
	UINT32 width                            :12;	//(11:0,NA,0x780) //width
	UINT32 resvd0                           :4;
	UINT32 height                           :12;	//(27:16,NA,0x438) //height
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C08 RW 0x0100_0000
	UINT32 resvd0                           :1;
	UINT32 reg_va_cnt_en                    :1;	//(1,NA,0x0) //1: va count enable for DTM_TOP_CTRL_03
	UINT32 dtm_disp_detour                  :1;	//(2,NA,0x0) //1: display tone mapping detour
	UINT32 resvd1                           :1;
	UINT32 reg_use_own_lut_en               :1;	//(4,NA,0x0) //0:use luminanace LUT channel G hif	1:use own LUT hif(B/R)(WR only)
	UINT32 resvd2                           :19;
	UINT32 reg_master_en                    :1;	//(24,NA,0x1) //LUT master enable
	UINT32 resvd3                           :7;
	};
}PE_O22_VSD_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C0C RO 0x0000_0000
	UINT32 vcnt                             :12;	//(11:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(12,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(13,NA,0x0) //Vertical Active at PE1 output
	UINT32 resvd0                           :2;
	UINT32 vcnt2                            :12;	//(27:16,NA,0x0) //vertical line number
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C10 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_O22_VSD_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C14 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,NA,0x14) //vdpulse position for register loading
	};
}PE_O22_VSD_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C20 RW 0x0000_0000
	UINT32 dummy_00                         :32;	//(31:0,NA,0x0) //
	};
}PE_O22_VSD_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C24 RW 0x0000_0000
	UINT32 dummy_01                         :32;	//(31:0,NA,0x0) //
	};
}PE_O22_VSD_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C28 RW 0x0000_0000
	UINT32 dummy_02                         :32;	//(31:0,NA,0x0) //
	};
}PE_O22_VSD_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C2C RW 0x0000_0000
	UINT32 dummy_03                         :32;	//(31:0,NA,0x0) //
	};
}PE_O22_VSD_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C40 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0,NA,0x1) //
	UINT32 resvd                            :31;
	};
}PE_O22_VSD_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C44 RW 0x12A0_7C98
	UINT32 r_csc1st_coef1                   :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C48 RW 0x7775_12A0
	UINT32 r_csc1st_coef3                   :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C4C RW 0x21D7_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C50 RW 0x12A0_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C54 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_VSD_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C58 RW 0x07C0_0600
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C5C RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C60 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_VSD_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C70 RW 0x0000_0000
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
}PE_O22_VSD_LLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C74 RW 0x0000_0000
	UINT32 win_w0_x0                        :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0                        :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C78 RW 0x0437_077F
	UINT32 win_w0_x1                        :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1                        :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C7C RW 0x0000_0000
	UINT32 win_w1_x0                        :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0                        :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C80 RW 0x0437_077F
	UINT32 win_w1_x1                        :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1                        :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_LLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C84 RW 0x03FF_03FF
	UINT32 hif_llut_wdata_y_33rd            :10;	//(9:0,NA,0x3FF) //Y coordinate of 33rd control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut_wdata_x_33rd            :10;	//(25:16,NA,0x3FF) //X coordinate of 33rd control point
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_LLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C88 RW 0x0000_8000
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
}PE_O22_VSD_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C8C RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut0_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C90 RW 0x0000_8000
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
}PE_O22_VSD_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C94 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut1_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C98 RW 0x0000_8000
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
}PE_O22_VSD_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C9C RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut2_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O22_VSD_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CA0 RW 0x0000_0000
	UINT32 reg_lut_lum_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_lum_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_lum_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_O22_VSD_LUT_LUM_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CA4 RW 0x0000_0000
	UINT32 reg_lut_lum_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_lum_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_lum_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_O22_VSD_LUT_LUM_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CA8 RW 0x0000_0000
	UINT32 reg_lut_sat_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_sat_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_sat_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_O22_VSD_LUT_LUM_SAT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CAC RW 0x0000_0000
	UINT32 reg_lut_sat_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_sat_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_sat_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_O22_VSD_LUT_LUM_SAT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CE0 RW 0xFF00_0000
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
}PE_O22_VSD_HUE_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CE4 RW 0x00000000
	UINT32 reg_lum_lut_input_sel            :1;	//(0,NA,0x0) //0:Y 1:max_rgb
	UINT32 resvd0                           :3;
	UINT32 reg_hue_lut_gain_sel             :1;	//(4,NA,0x0) //0:luma 1:saturation
	UINT32 resvd1                           :3;
	UINT32 reg_sat_lut_gain_sel             :1;	//(8,NA,0x0) //0:luma 1:saturation
	UINT32 resvd2                           :23;
	};
}PE_O22_VSD_HUE_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CF0 RW 0x0000_0000
	UINT32 odd_win_w0_x0                    :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y0                    :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_ODD_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CF4 RW 0x0437_077F
	UINT32 odd_win_w0_x1                    :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y1                    :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_ODD_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CF8 RW 0x0000_0000
	UINT32 odd_win_w1_x0                    :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y0                    :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_ODD_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460CFC RW 0x0437_077F
	UINT32 odd_win_w1_x1                    :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y1                    :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_ODD_LLUT_CTRL_04_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460500 RW 0x08700F00
	UINT32 reg_img_wid                      :12;	//(11:0,RW,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//(27:16,RW,0x870) //vertical resolution   2160
	UINT32 resvd1                           :4;
	};
}PE_O22_VSD_OBC_BODY_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460504 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,RW,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,RW,0x10) //Block size       16
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :8;	//(23:16,RW,0xF0) //Number of hblock 240
	UINT32 reg_l5_hei                       :8;	//(31:24,RW,0x87) //Number of vblock 135
	};
}PE_O22_VSD_OBC_BODY_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460508 RW 0x00
	UINT32 reg_vs_inv                       :1;	//(0,RW,0x00) //vs inversion
	UINT32 reg_psp_en                       :1;	//(1,RW,0x00) //psp enable : ?�체 enable
	UINT32 reg_hist_sel                     :2;	//(3:2,RW,0x00) //histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//(8:4,RW,0x00) //line 경계?�서 repeat ?�킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//(9,RW,0x00) //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//(14:10,RW,0x00) //frame 경계?�서 repeat ?�킬 v line 개수
	UINT32 reserved                         :1;	//(15,RW,0x00) //fg memory??mee off
	UINT32 reg_margin_hei                   :8;	//(23:16,RW,0x00) //edge extraction??V margin
	UINT32 reg_margin_wid                   :8;	//(31:24,RW,0x00) //edge extraction??H margin
	};
}PE_O22_VSD_OBC_BODY_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46050C RW 0x3F3F0000
	UINT32 y0_point                         :6;	//(5:0,NA,0x00) //control point of Y0
	UINT32 resvd0                           :2;
	UINT32 x0_point                         :6;	//(13:8,NA,0x00) //control point of X0
	UINT32 resvd1                           :2;
	UINT32 y1_point                         :6;	//(21:16,NA,0x3F) //control point of Y1
	UINT32 resvd2                           :2;
	UINT32 x1_point                         :6;	//(29:24,NA,0x3F) //control point of X1
	UINT32 resvd3                           :2;
	};
}PE_O22_VSD_OBC_BODY_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460510 RW 0x3F3F3F3F
	UINT32 y2_point                         :6;	//(5:0,NA,0x3F) //control point of Y2
	UINT32 resvd0                           :2;
	UINT32 x2_point                         :6;	//(13:8,NA,0x3F) //control point of X2
	UINT32 resvd1                           :2;
	UINT32 y3_point                         :6;	//(21:16,NA,0x3F) //control point of Y3
	UINT32 resvd2                           :2;
	UINT32 x3_point                         :6;	//(29:24,NA,0x3F) //control point of X3
	UINT32 resvd3                           :2;
	};
}PE_O22_VSD_OBC_BODY_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460548 RW 0x00000000
	UINT32 reg_sel_sync_gain                :2;	//(1:0,RW,0x0) //refine 0 vs, 1 va, 2 num
	UINT32 reg_sel_sync_fifo                :2;	//(3:2,RW,0x0) //refine fifo 0 vs, 1 va, 2 num
	UINT32 reg_debug_test                   :1;	//(4,RW,0x0) //
	UINT32 reg_start_pulse                  :1;	//(5,RW,0x0) //0 vs, 1 va
	UINT32 reg_pic_init_sel                 :1;	//(6,RW,0x0) //3x3 blur 0 vs, 1 va
	UINT32 resvd                            :1;
	UINT32 refine_num                       :12;	//(19:8,RW,0x0) //start pulse from V falling : num*256
	UINT32 fifo_num                         :12;	//(31:20,RW,0x0) //start pulse from V falling : num*256
	};
}PE_O22_VSD_OBC_BODY_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460570 RW 0x12C00080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x00) //reset cnt 12bit(0~4095)
	};
}PE_O22_VSD_OBC_BODY_REFINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460574 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
}PE_O22_VSD_OBC_BODY_REFINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460578 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
}PE_O22_VSD_OBC_BODY_REFINE_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46057C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O22_VSD_OBC_BODY_REFINE_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460580 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O22_VSD_OBC_BODY_REFINE_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460590 RW 0x0438_0780
	UINT32 reg_rgn_gain_width               :13;	//(12:0,NA,1920) //processing width (default : 3840/2 = 1920)
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_height              :13;	//(28:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460594 RW 0x0064_012C
	UINT32 reg_rgn_gain_position_x2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x1         :13;	//(28:16,NA,100) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460598 RW 0x027F_0354
	UINT32 reg_rgn_gain_position_x4         :13;	//(12:0,NA,852) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x3         :13;	//(28:16,NA,639) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46059C RW 0x0429_0519
	UINT32 reg_rgn_gain_position_x6         :13;	//(12:0,NA,1305) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x5         :13;	//(28:16,NA,1065) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605A0 RW 0x0609_06DE
	UINT32 reg_rgn_gain_position_x8         :13;	//(12:0,NA,1758) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x7         :13;	//(28:16,NA,1545) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605A4 RW 0x0096_012C
	UINT32 reg_rgn_gain_position_y2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y1         :13;	//(28:16,NA,150) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605A8 RW 0x039C_0514
	UINT32 reg_rgn_gain_position_y4         :13;	//(12:0,NA,1300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y3         :13;	//(28:16,NA,924) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605AC RW 0x0708_07D0
	UINT32 reg_rgn_gain_position_y6         :13;	//(12:0,NA,2000) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y5         :13;	//(28:16,NA,1800) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605B0 RW 0x6464_6464
	UINT32 reg_rgn_gain_41                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_31                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_21                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_11                  :8;	//(31:24,NA,100) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605B4 RW 0x6464_6464
	UINT32 reg_rgn_gain_81                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_71                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_61                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_51                  :8;	//(31:24,NA,100) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605B8 RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_42                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_32                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_22                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_12                  :8;	//(31:24,NA,110) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605BC RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_82                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_72                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_62                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_52                  :8;	//(31:24,NA,110) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605C0 RW 0x8080_8080
	UINT32 reg_rgn_gain_43                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_33                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_23                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_13                  :8;	//(31:24,NA,128) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605C4 RW 0x8080_8080
	UINT32 reg_rgn_gain_83                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_73                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_63                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_53                  :8;	//(31:24,NA,128) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605C8 RW 0x8080_8080
	UINT32 reg_rgn_gain_44                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_34                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_24                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_14                  :8;	//(31:24,NA,128) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605CC RW 0x8080_8080
	UINT32 reg_rgn_gain_84                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_74                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_64                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_54                  :8;	//(31:24,NA,128) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605D0 RW 0x6464_6464
	UINT32 reg_rgn_gain_45                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_35                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_25                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_15                  :8;	//(31:24,NA,100) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605D4 RW 0x6464_6464
	UINT32 reg_rgn_gain_85                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_75                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_65                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_55                  :8;	//(31:24,NA,100) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605D8 RW 0x5050_5050
	UINT32 reg_rgn_gain_46                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_36                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_26                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_16                  :8;	//(31:24,NA,80) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605DC RW 0x5050_5050
	UINT32 reg_rgn_gain_86                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_76                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_66                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_56                  :8;	//(31:24,NA,80) //
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605E0 RW 0x0000_8001
	UINT32 reg_rgn_gain_en                  :1;	//(0:0,NA,1) //
	UINT32 resvd0                           :7;
	UINT32 reg_rgn_gain_bnd_gain            :8;	//(15:8,NA,128) //
	UINT32 resvd1                           :16;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605E4 RW 0x0000_077F
	UINT32 reg_rgn_gain_bnd_x1              :13;	//(12:0,NA,1919) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_x0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4605E8 RW 0x0000_0437
	UINT32 reg_rgn_gain_bnd_y1              :13;	//(12:0,NA,1079) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_y0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A00 RW 0x0001_5101
	UINT32 reg_amg_en                       :1;	//(0:0,NA,1) //AMG core enable
	UINT32 resvd0                           :3;
	UINT32 reg_fsm_mode_sel                 :2;	//(5:4,NA,0) //FSM mode selection	0: run core with 1-init	1: run core with 2-init	2: run core with 4-init
	UINT32 reg_fsm_rst                      :1;	//(6:6,NA,0) //Manual reset FSM
	UINT32 reg_fsm_auto_rst_en              :1;	//(7:7,NA,0) //Auto reset FSM enable (for abnormal init case)
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,1) //0: sync-based, 1: valid-based
	UINT32 reg_manual_run_cnt_en            :1;	//(9:9,NA,0) //Manual run count (run ID) enable
	UINT32 reg_manual_run_cnt               :2;	//(11:10,NA,0) //Manual run count (run ID)	0: run state 0 (HEAD histogram)	1: run state 1 (HEAD gen map)	2: run state 2 (BODY histogram)	3: run state 3 (BODY gen map)
	UINT32 reg_420to422_flt_en              :1;	//(12:12,NA,1) //420 to 422 filter enable	0: repeatition mode	1: 2-tab average mode
	UINT32 reg_420to422_buf_mode            :1;	//(13:13,NA,0) //420 to 422 ring-buffer mode
	UINT32 reg_420to422_rpt_cnt             :2;	//(15:14,NA,1) //420 to 422 vertical repeat count
	UINT32 reg_422to444_flt_en              :1;	//(16:16,NA,1) //422 to 444 filter enable	0: repeatition mode	1: 2-tab average mode
	UINT32 resvd1                           :15;
	};
}PE_O22_AMG0_HEAD_AMG_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A04 RW 0x0087_00F0
	UINT32 reg_wid                          :8;	//(7:0,NA,240) //processing width (default: 240)
	UINT32 resvd0                           :8;
	UINT32 reg_hei                          :8;	//(23:16,NA,135) //processing height (default: 135)
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_AMG_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A08 RW 0x0118_0001
	UINT32 reg_use_extern_valid             :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_use_blank_period_cnt         :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O22_AMG0_HEAD_AMG_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A0C RW 0x3210_0064
	UINT32 reg_pic_delay_d2i                :16;	//(15:0,NA,100) //Delay of done to next init
	UINT32 reg_pic_delay_i2s                :8;	//(23:16,NA,16) //Delay of init to start
	UINT32 reg_flush_cnt                    :8;	//(31:24,NA,50) //Flush counter
	};
}PE_O22_AMG0_HEAD_AMG_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A10 RW 0x0000_0019
	UINT32 reg_update_ctrl                  :5;	//(4:0,NA,25) //[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_O22_AMG0_HEAD_AMG_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A20 RW 0x0242_0242
	UINT32 reg_hist_coef0_hb                :3;	//(2:0,NA,2) //Histogram coefficient, 0 (HEAD/BODY)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_coef1_hb                :3;	//(6:4,NA,4) //Histogram coefficient, 1 (HEAD/BODY)
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef2_hb                :3;	//(10:8,NA,2) //Histogram coefficient, 2 (HEAD/BODY)
	UINT32 resvd2                           :5;
	UINT32 reg_hist_coef0_depth             :3;	//(18:16,NA,2) //Histogram coefficient, 0 (Depth)
	UINT32 resvd3                           :1;
	UINT32 reg_hist_coef1_depth             :3;	//(22:20,NA,4) //Histogram coefficient, 1 (Depth)
	UINT32 resvd4                           :1;
	UINT32 reg_hist_coef2_depth             :3;	//(26:24,NA,2) //Histogram coefficient, 2 (Depth)
	UINT32 resvd5                           :5;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A24 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0: Y	1: Cb	2: Cr	3: Depth
	UINT32 resvd                            :30;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A28 RO 0x0000_0000
	UINT32 reg_read_hist_00_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 0)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_00_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 0)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A2C RO 0x0000_0000
	UINT32 reg_read_hist_01_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 1)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_01_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 1)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A30 RO 0x0000_0000
	UINT32 reg_read_hist_02_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 2)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_02_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 2)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A34 RO 0x0000_0000
	UINT32 reg_read_hist_03_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 3)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_03_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 3)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A38 RO 0x0000_0000
	UINT32 reg_read_hist_04_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 4)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_04_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 4)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A3C RO 0x0000_0000
	UINT32 reg_read_hist_05_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 5)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_05_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 5)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A40 RO 0x0000_0000
	UINT32 reg_read_hist_06_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 6)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_06_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 6)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A44 RO 0x0000_0000
	UINT32 reg_read_hist_07_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 7)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_07_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 7)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A48 RO 0x0000_0000
	UINT32 reg_read_hist_08_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 8)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_08_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 8)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A4C RO 0x0000_0000
	UINT32 reg_read_hist_09_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 9)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_09_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 9)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A50 RO 0x0000_0000
	UINT32 reg_read_hist_10_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 10)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_10_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 10)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A54 RO 0x0000_0000
	UINT32 reg_read_hist_11_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 11)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_11_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 11)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A58 RO 0x0000_0000
	UINT32 reg_read_hist_12_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 12)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_12_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 12)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A5C RO 0x0000_0000
	UINT32 reg_read_hist_13_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 13)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_13_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 13)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A60 RO 0x0000_0000
	UINT32 reg_read_hist_14_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 14)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_14_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 14)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A64 RO 0x0000_0000
	UINT32 reg_read_hist_15_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 15)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_15_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 15)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A68 RO 0x0000_0000
	UINT32 reg_read_hist_16_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 16)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_16_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 16)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A6C RO 0x0000_0000
	UINT32 reg_read_hist_17_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 17)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_17_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 17)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A70 RO 0x0000_0000
	UINT32 reg_read_hist_18_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 18)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_18_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 18)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A74 RO 0x0000_0000
	UINT32 reg_read_hist_19_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 19)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_19_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 19)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A78 RO 0x0000_0000
	UINT32 reg_read_hist_20_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 20)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_20_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 20)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A7C RO 0x0000_0000
	UINT32 reg_read_hist_21_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 21)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_21_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 21)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A80 RO 0x0000_0000
	UINT32 reg_read_hist_22_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 22)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_22_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 22)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A84 RO 0x0000_0000
	UINT32 reg_read_hist_23_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 23)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_23_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 23)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A88 RO 0x0000_0000
	UINT32 reg_read_hist_24_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 24)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_24_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 24)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A8C RO 0x0000_0000
	UINT32 reg_read_hist_25_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 25)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_25_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 25)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A90 RO 0x0000_0000
	UINT32 reg_read_hist_26_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 26)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_26_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 26)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A94 RO 0x0000_0000
	UINT32 reg_read_hist_27_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 27)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_27_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 27)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A98 RO 0x0000_0000
	UINT32 reg_read_hist_28_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 28)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_28_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 28)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4A9C RO 0x0000_0000
	UINT32 reg_read_hist_29_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 29)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_29_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 29)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AA0 RO 0x0000_0000
	UINT32 reg_read_hist_30_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 30)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_30_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 30)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AA4 RO 0x0000_0000
	UINT32 reg_read_hist_31_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 31)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_31_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 31)
	UINT32 resvd1                           :1;
	};
}PE_O22_AMG0_HEAD_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AB0 RW 0x0000_0101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0: Probability map	1: Ellipse gain map	2: Probability map (FG)	3: Probability map (BG)	4: Probability map (diff)	5: Box map	6: Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,0) //Object map output mux selection	0: HEAD/BODY	1: Blending	2: Depth only	3: Adding
	UINT32 resvd3                           :18;
	};
}PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AB4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
}PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AB8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ABC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AC0 RW 0x0000_0000
	UINT32 reg_box_fg_cand_en               :1;	//(0:0,NA,0) //FG candidate box set enable
	UINT32 resvd0                           :3;
	UINT32 reg_box0_add_set1_en             :1;	//(4:4,NA,0) //Additional box0 set1 enable
	UINT32 reg_box1_add_set1_en             :1;	//(5:5,NA,0) //Additional box1 set1 enable
	UINT32 reg_box2_add_set1_en             :1;	//(6:6,NA,0) //Additional box2 set1 enable
	UINT32 reg_box3_add_set1_en             :1;	//(7:7,NA,0) //Additional box3 set1 enable
	UINT32 reg_box0_add_set2_en             :1;	//(8:8,NA,0) //Additional box0 set2 enable
	UINT32 reg_box1_add_set2_en             :1;	//(9:9,NA,0) //Additional box1 set2 enable
	UINT32 reg_box2_add_set2_en             :1;	//(10:10,NA,0) //Additional box2 set2 enable
	UINT32 reg_box3_add_set2_en             :1;	//(11:11,NA,0) //Additional box3 set2 enable
	UINT32 reg_box0_opt_en                  :1;	//(12:12,NA,0) //Optional box0 set enable
	UINT32 reg_box1_opt_en                  :1;	//(13:13,NA,0) //Optional box1 set enable
	UINT32 reg_box2_opt_en                  :1;	//(14:14,NA,0) //Optional box2 set enable
	UINT32 reg_box3_opt_en                  :1;	//(15:15,NA,0) //Optional box3 set enable
	UINT32 reg_additional_box_en            :1;	//(16:16,NA,0) //Additional box enable	- 0: disable (default, replaced to optional box enable)	- 1: enable
	UINT32 resvd1                           :15;
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AC4 RW 0x0000_0000
	UINT32 reg_box_fg_cand_w1               :8;	//(7:0,NA,0) //Box (FG candidate) position, w, start
	UINT32 reg_box_fg_cand_w2               :8;	//(15:8,NA,0) //Box (FG candidate) position, w, end
	UINT32 reg_box_fg_cand_h1               :8;	//(23:16,NA,0) //Box (FG candidate) position, h, start
	UINT32 reg_box_fg_cand_h2               :8;	//(31:24,NA,0) //Box (FG candidate) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AC8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ACC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AD0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AD4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AD8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ADC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AE0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AE4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AE8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AEC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AF0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4AF4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
}PE_O22_AMG0_HEAD_BOX_SET_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B00 RW 0x0000_0000
	UINT32 reg_fg_cand_e_mul_a              :9;	//(8:0,NA,0) //Ellipse (FG candidate) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_fg_cand_e_mul_b              :9;	//(24:16,NA,0) //Ellipse (FG candidate) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_fg_cand_ellipse_en           :1;	//(31:31,NA,0) //Ellipse (FG candidate) gain gen enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B04 RW 0x0000_0000
	UINT32 reg_fg_cand_ellipse_master       :8;	//(7:0,NA,0) //Ellipse (FG candidate) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_fg_cand_ellipse_offset       :8;	//(23:16,NA,0) //Ellipse (FG candidate) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 0) gain gen enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 1) gain gen enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 2) gain gen enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 3) gain gen enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
}PE_O22_AMG0_HEAD_ELLIPSE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
}PE_O22_AMG0_HEAD_LUT_PROB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
}PE_O22_AMG0_HEAD_LUT_PROB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4B80 RW 0x0000_00CC
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
}PE_O22_AMG0_HEAD_BLUR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4C20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0: use manual value	1: use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0: use IIR result	1: use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
}PE_O22_AMG0_HEAD_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4C24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
}PE_O22_AMG0_HEAD_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4C30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
}PE_O22_AMG0_HEAD_LUT_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4C34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
}PE_O22_AMG0_HEAD_LUT_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4C38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
}PE_O22_AMG0_HEAD_LUT_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CC0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :8;	//(7:0,NA,0) //Top input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :8;	//(15:8,NA,0) //Top input (pel, Y) previous frame vertical counter
	UINT32 reg_mon_in_pel_y_vert_cnt        :8;	//(23:16,NA,0) //Top input (pel, Y) vertical counter
	UINT32 reg_mon_in_pel_y_hori_cnt        :8;	//(31:24,NA,0) //Top input (pel, Y) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_TOP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CC4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :8;	//(7:0,NA,0) //Top input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :8;	//(15:8,NA,0) //Top input (pel, C) previous frame vertical counter
	UINT32 reg_mon_in_pel_c_vert_cnt        :8;	//(23:16,NA,0) //Top input (pel, C) vertical counter
	UINT32 reg_mon_in_pel_c_hori_cnt        :8;	//(31:24,NA,0) //Top input (pel, C) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_TOP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CC8 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :8;	//(7:0,NA,0) //Top input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :8;	//(15:8,NA,0) //Top input (depth map) previous frame vertical counter
	UINT32 reg_mon_in_depth_vert_cnt        :8;	//(23:16,NA,0) //Top input (depth map) vertical counter
	UINT32 reg_mon_in_depth_hori_cnt        :8;	//(31:24,NA,0) //Top input (depth map) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_TOP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CCC RO 0x0000_0000
	UINT32 reg_mon_in_iir_sucfail           :8;	//(7:0,NA,0) //Top input (IIR feedback) success/fail monitoring register
	UINT32 reg_mon_in_iir_fin_vert          :8;	//(15:8,NA,0) //Top input (IIR feedback) previous frame vertical counter
	UINT32 reg_mon_in_iir_vert_cnt          :8;	//(23:16,NA,0) //Top input (IIR feedback) vertical counter
	UINT32 reg_mon_in_iir_hori_cnt          :8;	//(31:24,NA,0) //Top input (IIR feedback) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_TOP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CD0 RO 0x0000_0000
	UINT32 reg_mon_out_iir_sucfail          :8;	//(7:0,NA,0) //Top output (IIR out) success/fail monitoring register
	UINT32 reg_mon_out_iir_fin_vert         :8;	//(15:8,NA,0) //Top output (IIR out) previous frame vertical counter
	UINT32 reg_mon_out_iir_vert_cnt         :8;	//(23:16,NA,0) //Top output (IIR out) vertical counter
	UINT32 reg_mon_out_iir_hori_cnt         :8;	//(31:24,NA,0) //Top output (IIR out) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_TOP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CD4 RO 0x0000_0000
	UINT32 reg_top_run_1st_done             :1;	//(0:0,NA,0) //Top 1st-run done pulse
	UINT32 reg_top_run_2nd_done             :1;	//(1:1,NA,0) //Top 2nd-run done pulse (core 2nd-run and mifw done)
	UINT32 reg_top_run_3rd_done             :1;	//(2:2,NA,0) //Top 3rd-run done pulse
	UINT32 reg_top_run_4th_done             :1;	//(3:3,NA,0) //Top 4th-run done pulse (core 4rd-run and mifw done)
	UINT32 reg_top_done_intr_1st            :1;	//(4:4,NA,0) //Top 1st-run done flag
	UINT32 reg_top_done_intr_2nd            :1;	//(5:5,NA,0) //Top 2nd-run done flag
	UINT32 reg_top_done_intr_3rd            :1;	//(6:6,NA,0) //Top 3rd-run done flag
	UINT32 reg_top_done_intr_4th            :1;	//(7:7,NA,0) //Top 4th-run done flag
	UINT32 reg_mifw_iir_pic_end_flag        :1;	//(8:8,NA,0) //MIF write done flag
	UINT32 resvd0                           :1;
	UINT32 reg_run_head_flag                :1;	//(10:10,NA,0) //HEAD run flag
	UINT32 reg_run_body_flag                :1;	//(11:11,NA,0) //BODY run flag
	UINT32 reg_abnomral_init_oc             :1;	//(12:12,NA,0) //Abnormal init occurred
	UINT32 resvd1                           :19;
	};
}PE_O22_AMG0_HEAD_AMG_TOP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CD8 RO 0x0000_0000
	UINT32 reg_mon_in_pel_sucfail           :8;	//(7:0,NA,0) //Core input (pel) success/fail monitoring register
	UINT32 reg_mon_in_pel_fin_vert          :8;	//(15:8,NA,0) //Core input (pel) previous frame vertical counter
	UINT32 reg_mon_in_pel_vert_cnt          :8;	//(23:16,NA,0) //Core input (pel) vertical counter
	UINT32 reg_mon_in_pel_hori_cnt          :8;	//(31:24,NA,0) //Core input (pel) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CDC RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :8;	//(7:0,NA,0) //Core input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :8;	//(15:8,NA,0) //Core input (depth map) previous frame vertical counter
	UINT32 reg_mon_in_depth_vert_cnt        :8;	//(23:16,NA,0) //Core input (depth map) vertical counter
	UINT32 reg_mon_in_depth_hori_cnt        :8;	//(31:24,NA,0) //Core input (depth map) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CE0 RO 0x0000_0000
	UINT32 reg_mon_in_iir_sucfail           :8;	//(7:0,NA,0) //Core input (IIR feedback) success/fail monitoring register
	UINT32 reg_mon_in_iir_fin_vert          :8;	//(15:8,NA,0) //Core input (IIR feedback) previous frame vertical counter
	UINT32 reg_mon_in_iir_vert_cnt          :8;	//(23:16,NA,0) //Core input (IIR feedback) vertical counter
	UINT32 reg_mon_in_iir_hori_cnt          :8;	//(31:24,NA,0) //Core input (IIR feedback) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CE4 RO 0x0000_0000
	UINT32 reg_mon_out_iir_sucfail          :8;	//(7:0,NA,0) //Core output (IIR out) success/fail monitoring register
	UINT32 reg_mon_out_iir_fin_vert         :8;	//(15:8,NA,0) //Core output (IIR out) previous frame vertical counter
	UINT32 reg_mon_out_iir_vert_cnt         :8;	//(23:16,NA,0) //Core output (IIR out) vertical counter
	UINT32 reg_mon_out_iir_hori_cnt         :8;	//(31:24,NA,0) //Core output (IIR out) horizontal counter
	};
}PE_O22_AMG0_HEAD_AMG_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CE8 RO 0x0000_0000
	UINT32 reg_run_1st_done                 :1;	//(0:0,NA,0) //Core 1st-run done pulse
	UINT32 reg_run_2nd_done                 :1;	//(1:1,NA,0) //Core 2nd-run done pulse
	UINT32 reg_run_3rd_done                 :1;	//(2:2,NA,0) //Core 3rd-run done pulse
	UINT32 reg_run_4th_done                 :1;	//(3:3,NA,0) //Core 4th-run done pulse
	UINT32 reg_run_1st_flag                 :1;	//(4:4,NA,0) //Core 1st-run processing flag
	UINT32 reg_run_2nd_flag                 :1;	//(5:5,NA,0) //Core 2nd-run processing flag
	UINT32 reg_run_3rd_flag                 :1;	//(6:6,NA,0) //Core 3rd-run processing flag
	UINT32 reg_run_4th_flag                 :1;	//(7:7,NA,0) //Core 4th-run processing flag
	UINT32 reg_run_cnt                      :2;	//(9:8,NA,0) //Run count (run ID)
	UINT32 reg_st_amg                       :5;	//(14:10,NA,0) //FSM state
	UINT32 resvd                            :17;
	};
}PE_O22_AMG0_HEAD_AMG_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_AMG0_HEAD_AMG_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_AMG0_HEAD_AMG_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_AMG0_HEAD_AMG_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4CFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_AMG0_HEAD_AMG_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4D20 RW 0x0242_0242
	UINT32 reg_hist_coef0_hb                :3;	//(2:0,NA,2) //Histogram coefficient, 0 (HEAD/BODY)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_coef1_hb                :3;	//(6:4,NA,4) //Histogram coefficient, 1 (HEAD/BODY)
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef2_hb                :3;	//(10:8,NA,2) //Histogram coefficient, 2 (HEAD/BODY)
	UINT32 resvd2                           :5;
	UINT32 reg_hist_coef0_depth             :3;	//(18:16,NA,2) //Histogram coefficient, 0 (Depth)
	UINT32 resvd3                           :1;
	UINT32 reg_hist_coef1_depth             :3;	//(22:20,NA,4) //Histogram coefficient, 1 (Depth)
	UINT32 resvd4                           :1;
	UINT32 reg_hist_coef2_depth             :3;	//(26:24,NA,2) //Histogram coefficient, 2 (Depth)
	UINT32 resvd5                           :5;
	};
}PE_O22_AMG1_BODY_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4D24 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0: Y	1: Cb	2: Cr	3: Depth
	UINT32 resvd                            :30;
	};
}PE_O22_AMG1_BODY_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DB0 RW 0x0000_1101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0: Probability map	1: Ellipse gain map	2: Probability map (FG)	3: Probability map (BG)	4: Probability map (diff)	5: Box map	6: Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,1) //Object map output mux selection	0: HEAD/BODY	1: Blending	2: Depth only	3: Adding
	UINT32 resvd3                           :18;
	};
}PE_O22_AMG1_BODY_OBJT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DB4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
}PE_O22_AMG1_BODY_OBJT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DB8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_OBJT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DBC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG1_BODY_OBJT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DC0 RW 0x0000_0000
	UINT32 reg_box_fg_cand_en               :1;	//(0:0,NA,0) //FG candidate box set enable
	UINT32 resvd0                           :3;
	UINT32 reg_box0_add_set1_en             :1;	//(4:4,NA,0) //Additional box0 set1 enable
	UINT32 reg_box1_add_set1_en             :1;	//(5:5,NA,0) //Additional box1 set1 enable
	UINT32 reg_box2_add_set1_en             :1;	//(6:6,NA,0) //Additional box2 set1 enable
	UINT32 reg_box3_add_set1_en             :1;	//(7:7,NA,0) //Additional box3 set1 enable
	UINT32 reg_box0_add_set2_en             :1;	//(8:8,NA,0) //Additional box0 set2 enable
	UINT32 reg_box1_add_set2_en             :1;	//(9:9,NA,0) //Additional box1 set2 enable
	UINT32 reg_box2_add_set2_en             :1;	//(10:10,NA,0) //Additional box2 set2 enable
	UINT32 reg_box3_add_set2_en             :1;	//(11:11,NA,0) //Additional box3 set2 enable
	UINT32 reg_box0_opt_en                  :1;	//(12:12,NA,0) //Optional box0 set enable
	UINT32 reg_box1_opt_en                  :1;	//(13:13,NA,0) //Optional box1 set enable
	UINT32 reg_box2_opt_en                  :1;	//(14:14,NA,0) //Optional box2 set enable
	UINT32 reg_box3_opt_en                  :1;	//(15:15,NA,0) //Optional box3 set enable
	UINT32 reg_additional_box_en            :1;	//(16:16,NA,0) //Additional box enable	- 0: disable (default, replaced to optional box enable)	- 1: enable
	UINT32 resvd1                           :15;
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DC4 RW 0x0000_0000
	UINT32 reg_box_fg_cand_w1               :8;	//(7:0,NA,0) //Box (FG candidate) position, w, start
	UINT32 reg_box_fg_cand_w2               :8;	//(15:8,NA,0) //Box (FG candidate) position, w, end
	UINT32 reg_box_fg_cand_h1               :8;	//(23:16,NA,0) //Box (FG candidate) position, h, start
	UINT32 reg_box_fg_cand_h2               :8;	//(31:24,NA,0) //Box (FG candidate) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DC8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DCC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DD0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DD4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DD8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DDC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DE0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DE4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DE8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DEC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DF0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4DF4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
}PE_O22_AMG1_BODY_BOX_SET_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E00 RW 0x0000_0000
	UINT32 reg_fg_cand_e_mul_a              :9;	//(8:0,NA,0) //Ellipse (FG candidate) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_fg_cand_e_mul_b              :9;	//(24:16,NA,0) //Ellipse (FG candidate) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_fg_cand_ellipse_en           :1;	//(31:31,NA,0) //Ellipse (FG candidate) gain gen enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E04 RW 0x0000_0000
	UINT32 reg_fg_cand_ellipse_master       :8;	//(7:0,NA,0) //Ellipse (FG candidate) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_fg_cand_ellipse_offset       :8;	//(23:16,NA,0) //Ellipse (FG candidate) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 0) gain gen enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 1) gain gen enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 2) gain gen enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 3) gain gen enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
}PE_O22_AMG1_BODY_ELLIPSE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
}PE_O22_AMG1_BODY_LUT_PROB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
}PE_O22_AMG1_BODY_LUT_PROB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E80 RW 0x0000_00CC
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
}PE_O22_AMG1_BODY_BLUR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E90 RW 0x5014_0000
	UINT32 reg_lut_depth_map_y0             :8;	//(7:0,NA,0) //LUT (depth map) control point, y0
	UINT32 reg_lut_depth_map_x0             :8;	//(15:8,NA,0) //LUT (depth map) control point, x0
	UINT32 reg_lut_depth_map_y1             :8;	//(23:16,NA,20) //LUT (depth map) control point, y1
	UINT32 reg_lut_depth_map_x1             :8;	//(31:24,NA,80) //LUT (depth map) control point, x1
	};
}PE_O22_AMG1_BODY_LUT_DEPTH_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4E94 RW 0xFFFF_6E6E
	UINT32 reg_lut_depth_map_y2             :8;	//(7:0,NA,110) //LUT (depth map) control point, y2
	UINT32 reg_lut_depth_map_x2             :8;	//(15:8,NA,110) //LUT (depth map) control point, x2
	UINT32 reg_lut_depth_map_y3             :8;	//(23:16,NA,255) //LUT (depth map) control point, y3
	UINT32 reg_lut_depth_map_x3             :8;	//(31:24,NA,255) //LUT (depth map) control point, x3
	};
}PE_O22_AMG1_BODY_LUT_DEPTH_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EA0 RW 0xC090_6030
	UINT32 reg_region_position_x1           :8;	//(7:0,NA,48) //Region gain position, x1
	UINT32 reg_region_position_x2           :8;	//(15:8,NA,96) //Region gain position, x2
	UINT32 reg_region_position_x3           :8;	//(23:16,NA,144) //Region gain position, x3
	UINT32 reg_region_position_x4           :8;	//(31:24,NA,192) //Region gain position, x4
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EA4 RW 0xEFEF_EFEF
	UINT32 reg_region_position_x5           :8;	//(7:0,NA,239) //Region gain position, x5
	UINT32 reg_region_position_x6           :8;	//(15:8,NA,239) //Region gain position, x6
	UINT32 reg_region_position_x7           :8;	//(23:16,NA,239) //Region gain position, x7
	UINT32 reg_region_position_x8           :8;	//(31:24,NA,239) //Region gain position, x8
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EA8 RW 0x7D73_5A28
	UINT32 reg_region_position_y1           :8;	//(7:0,NA,40) //Region gain position, y1
	UINT32 reg_region_position_y2           :8;	//(15:8,NA,90) //Region gain position, y2
	UINT32 reg_region_position_y3           :8;	//(23:16,NA,115) //Region gain position, y3
	UINT32 reg_region_position_y4           :8;	//(31:24,NA,125) //Region gain position, y4
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EAC RW 0x0000_8686
	UINT32 reg_region_position_y5           :8;	//(7:0,NA,134) //Region gain position, y5
	UINT32 reg_region_position_y6           :8;	//(15:8,NA,134) //Region gain position, y6
	UINT32 resvd                            :16;
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EB0 RW 0x0000_0000
	UINT32 reg_region_gain_en_11            :2;	//(1:0,NA,0) //Region gain enable, 11
	UINT32 reg_region_gain_en_21            :2;	//(3:2,NA,0) //Region gain enable, 21
	UINT32 reg_region_gain_en_31            :2;	//(5:4,NA,0) //Region gain enable, 31
	UINT32 reg_region_gain_en_41            :2;	//(7:6,NA,0) //Region gain enable, 41
	UINT32 reg_region_gain_en_51            :2;	//(9:8,NA,0) //Region gain enable, 51
	UINT32 reg_region_gain_en_61            :2;	//(11:10,NA,0) //Region gain enable, 61
	UINT32 reg_region_gain_en_71            :2;	//(13:12,NA,0) //Region gain enable, 71
	UINT32 reg_region_gain_en_81            :2;	//(15:14,NA,0) //Region gain enable, 81
	UINT32 reg_region_gain_en_12            :2;	//(17:16,NA,0) //Region gain enable, 12
	UINT32 reg_region_gain_en_22            :2;	//(19:18,NA,0) //Region gain enable, 22
	UINT32 reg_region_gain_en_32            :2;	//(21:20,NA,0) //Region gain enable, 32
	UINT32 reg_region_gain_en_42            :2;	//(23:22,NA,0) //Region gain enable, 42
	UINT32 reg_region_gain_en_52            :2;	//(25:24,NA,0) //Region gain enable, 52
	UINT32 reg_region_gain_en_62            :2;	//(27:26,NA,0) //Region gain enable, 62
	UINT32 reg_region_gain_en_72            :2;	//(29:28,NA,0) //Region gain enable, 72
	UINT32 reg_region_gain_en_82            :2;	//(31:30,NA,0) //Region gain enable, 82
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EB4 RW 0x0000_0000
	UINT32 reg_region_gain_en_13            :2;	//(1:0,NA,0) //Region gain enable, 13
	UINT32 reg_region_gain_en_23            :2;	//(3:2,NA,0) //Region gain enable, 23
	UINT32 reg_region_gain_en_33            :2;	//(5:4,NA,0) //Region gain enable, 33
	UINT32 reg_region_gain_en_43            :2;	//(7:6,NA,0) //Region gain enable, 43
	UINT32 reg_region_gain_en_53            :2;	//(9:8,NA,0) //Region gain enable, 53
	UINT32 reg_region_gain_en_63            :2;	//(11:10,NA,0) //Region gain enable, 63
	UINT32 reg_region_gain_en_73            :2;	//(13:12,NA,0) //Region gain enable, 73
	UINT32 reg_region_gain_en_83            :2;	//(15:14,NA,0) //Region gain enable, 83
	UINT32 reg_region_gain_en_14            :2;	//(17:16,NA,0) //Region gain enable, 14
	UINT32 reg_region_gain_en_24            :2;	//(19:18,NA,0) //Region gain enable, 24
	UINT32 reg_region_gain_en_34            :2;	//(21:20,NA,0) //Region gain enable, 34
	UINT32 reg_region_gain_en_44            :2;	//(23:22,NA,0) //Region gain enable, 44
	UINT32 reg_region_gain_en_54            :2;	//(25:24,NA,0) //Region gain enable, 54
	UINT32 reg_region_gain_en_64            :2;	//(27:26,NA,0) //Region gain enable, 64
	UINT32 reg_region_gain_en_74            :2;	//(29:28,NA,0) //Region gain enable, 74
	UINT32 reg_region_gain_en_84            :2;	//(31:30,NA,0) //Region gain enable, 84
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EB8 RW 0x0000_0000
	UINT32 reg_region_gain_en_15            :2;	//(1:0,NA,0) //Region gain enable, 15
	UINT32 reg_region_gain_en_25            :2;	//(3:2,NA,0) //Region gain enable, 25
	UINT32 reg_region_gain_en_35            :2;	//(5:4,NA,0) //Region gain enable, 35
	UINT32 reg_region_gain_en_45            :2;	//(7:6,NA,0) //Region gain enable, 45
	UINT32 reg_region_gain_en_55            :2;	//(9:8,NA,0) //Region gain enable, 55
	UINT32 reg_region_gain_en_65            :2;	//(11:10,NA,0) //Region gain enable, 65
	UINT32 reg_region_gain_en_75            :2;	//(13:12,NA,0) //Region gain enable, 75
	UINT32 reg_region_gain_en_85            :2;	//(15:14,NA,0) //Region gain enable, 85
	UINT32 reg_region_gain_en_16            :2;	//(17:16,NA,0) //Region gain enable, 16
	UINT32 reg_region_gain_en_26            :2;	//(19:18,NA,0) //Region gain enable, 26
	UINT32 reg_region_gain_en_36            :2;	//(21:20,NA,0) //Region gain enable, 36
	UINT32 reg_region_gain_en_46            :2;	//(23:22,NA,0) //Region gain enable, 46
	UINT32 reg_region_gain_en_56            :2;	//(25:24,NA,0) //Region gain enable, 56
	UINT32 reg_region_gain_en_66            :2;	//(27:26,NA,0) //Region gain enable, 66
	UINT32 reg_region_gain_en_76            :2;	//(29:28,NA,0) //Region gain enable, 76
	UINT32 reg_region_gain_en_86            :2;	//(31:30,NA,0) //Region gain enable, 86
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EBC RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,128) //Region gain, 11
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,128) //Region gain, 21
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,128) //Region gain, 31
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,128) //Region gain, 41
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EC0 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,128) //Region gain, 51
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,128) //Region gain, 61
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,128) //Region gain, 71
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,128) //Region gain, 81
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EC4 RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,128) //Region gain, 12
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,128) //Region gain, 22
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,128) //Region gain, 32
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,128) //Region gain, 42
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EC8 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,128) //Region gain, 52
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,128) //Region gain, 62
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,128) //Region gain, 72
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,128) //Region gain, 82
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ECC RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,128) //Region gain, 13
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,128) //Region gain, 23
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,128) //Region gain, 33
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,128) //Region gain, 43
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ED0 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,128) //Region gain, 53
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,128) //Region gain, 63
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,128) //Region gain, 73
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,128) //Region gain, 83
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ED4 RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,128) //Region gain, 14
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,128) //Region gain, 24
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,128) //Region gain, 34
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,128) //Region gain, 44
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4ED8 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,128) //Region gain, 54
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,128) //Region gain, 64
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,128) //Region gain, 74
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,128) //Region gain, 84
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EDC RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,128) //Region gain, 15
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,128) //Region gain, 25
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,128) //Region gain, 35
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,128) //Region gain, 45
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EE0 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,128) //Region gain, 55
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,128) //Region gain, 65
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,128) //Region gain, 75
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,128) //Region gain, 85
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EE4 RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,128) //Region gain, 16
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,128) //Region gain, 26
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,128) //Region gain, 36
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,128) //Region gain, 46
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EE8 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,128) //Region gain, 56
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,128) //Region gain, 66
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,128) //Region gain, 76
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,128) //Region gain, 86
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EEC RW 0x8600_EF00
	UINT32 reg_region_bnd_x0                :8;	//(7:0,NA,0) //Region bound, x0
	UINT32 reg_region_bnd_x1                :8;	//(15:8,NA,239) //Region bound, x1
	UINT32 reg_region_bnd_y0                :8;	//(23:16,NA,0) //Region bound, y0
	UINT32 reg_region_bnd_y1                :8;	//(31:24,NA,134) //Region bound, y1
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EF0 RW 0x0000_0080
	UINT32 reg_region_bnd_gain              :8;	//(7:0,NA,128) //Region bound gain
	UINT32 resvd                            :24;
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4EF4 RW 0x0000_0110
	UINT32 reg_region_gain_offset0          :8;	//(7:0,NA,16) //Region gain offset0
	UINT32 reg_region_gain_offset1          :8;	//(15:8,NA,1) //Region gain offset1
	UINT32 resvd                            :16;
	};
}PE_O22_AMG1_BODY_REGION_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F00 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_u_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y0
	UINT32 reg_lut_depth_iir_u_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, up) control point, x0
	UINT32 reg_lut_depth_iir_u_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y1
	UINT32 reg_lut_depth_iir_u_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, up) control point, x1
	};
}PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F04 RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_u_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y2
	UINT32 reg_lut_depth_iir_u_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, up) control point, x2
	UINT32 reg_lut_depth_iir_u_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y3
	UINT32 reg_lut_depth_iir_u_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, up) control point, x3
	};
}PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F08 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_d_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y0
	UINT32 reg_lut_depth_iir_d_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, down) control point, x0
	UINT32 reg_lut_depth_iir_d_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y1
	UINT32 reg_lut_depth_iir_d_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, down) control point, x1
	};
}PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F0C RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_d_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y2
	UINT32 reg_lut_depth_iir_d_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, down) control point, x2
	UINT32 reg_lut_depth_iir_d_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y3
	UINT32 reg_lut_depth_iir_d_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, down) control point, x3
	};
}PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F10 RW 0x3FFF_00FF
	UINT32 reg_lut_depth_body_y0            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y0
	UINT32 reg_lut_depth_body_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth>body), x0
	UINT32 reg_lut_depth_body_y1            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y1
	UINT32 reg_lut_depth_body_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth>body), x1
	};
}PE_O22_AMG1_BODY_LUT_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F14 RW 0xFFFF_7EFF
	UINT32 reg_lut_depth_body_y2            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y2
	UINT32 reg_lut_depth_body_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth>body), x2
	UINT32 reg_lut_depth_body_y3            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y3
	UINT32 reg_lut_depth_body_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth>body), x3
	};
}PE_O22_AMG1_BODY_LUT_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F18 RW 0x3F20_0000
	UINT32 reg_lut_body_depth_y0            :8;	//(7:0,NA,0) //LUT (depth body blend) control point (for depth<=body), y0
	UINT32 reg_lut_body_depth_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth<=body), x0
	UINT32 reg_lut_body_depth_y1            :8;	//(23:16,NA,32) //LUT (depth body blend) control point (for depth<=body), y1
	UINT32 reg_lut_body_depth_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth<=body), x1
	};
}PE_O22_AMG1_BODY_LUT_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F1C RW 0xFF58_7E58
	UINT32 reg_lut_body_depth_y2            :8;	//(7:0,NA,88) //LUT (depth body blend) control point (for depth<=body), y2
	UINT32 reg_lut_body_depth_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth<=body), x2
	UINT32 reg_lut_body_depth_y3            :8;	//(23:16,NA,88) //LUT (depth body blend) control point (for depth<=body), y3
	UINT32 reg_lut_body_depth_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth<=body), x3
	};
}PE_O22_AMG1_BODY_LUT_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0: use manual value	1: use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0: use IIR result	1: use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
}PE_O22_AMG1_BODY_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
}PE_O22_AMG1_BODY_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
}PE_O22_AMG1_BODY_LUT_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
}PE_O22_AMG1_BODY_LUT_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8C4F38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
}PE_O22_AMG1_BODY_LUT_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483200 RW 0x0000_0000
	UINT32 g0_pic_init                      :1;	//(0,RW,0x00) //[FW PIC_INIT] OBC HEAD
	UINT32 g1_pic_init                      :1;	//(1,RW,0x00) //[FW PIC_INIT] OBC BODY
	UINT32 g2_pic_init                      :1;	//(2,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 g3_pic_init                      :1;	//(3,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 g4_pic_init                      :1;	//(4,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 g5_pic_init                      :1;	//(5,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 g6_pic_init                      :1;	//(6,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 g7_pic_init                      :1;	//(7,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 resvd                            :8;
	UINT32 g0_auto_init                     :1;	//(16,RW,0x00) //[AUTO PIC_INIT] OBC HEAD
	UINT32 g1_auto_init                     :1;	//(17,RW,0x00) //[AUTO PIC_INIT] OBC BODY
	UINT32 g2_auto_init                     :1;	//(18,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g3_auto_init                     :1;	//(19,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g4_auto_init                     :1;	//(20,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g5_auto_init                     :1;	//(21,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g6_auto_init                     :1;	//(22,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g7_auto_init                     :1;	//(23,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g0_pic_init_mask                 :1;	//(24,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g1_pic_init_mask                 :1;	//(25,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g2_pic_init_mask                 :1;	//(26,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g3_pic_init_mask                 :1;	//(27,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g4_pic_init_mask                 :1;	//(28,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g5_pic_init_mask                 :1;	//(29,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g6_pic_init_mask                 :1;	//(30,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g7_pic_init_mask                 :1;	//(31,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	};
}PE_VSD_OBC_M_SC_PIC_INIT_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483204 RW 0x0000_0000
	UINT32 g0_pic_start                     :1;	//(0,RW,0x00) //[FW PIC_START] OBC HEAD
	UINT32 g1_pic_start                     :1;	//(1,RW,0x00) //[FW PIC_START] OBC BODY
	UINT32 g2_pic_start                     :1;	//(2,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 g3_pic_start                     :1;	//(3,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 g4_pic_start                     :1;	//(4,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 g5_pic_start                     :1;	//(5,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 g6_pic_start                     :1;	//(6,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 g7_pic_start                     :1;	//(7,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 resvd                            :8;
	UINT32 g0_auto_half_en                  :1;	//(16,RW,0x00) //[AUTO_PIC_INIT HALF EN] OBC HEAD
	UINT32 g1_auto_half_en                  :1;	//(17,RW,0x00) //[AUTO_PIC_INIT HALF EN] OBC BODY
	UINT32 g2_auto_half_en                  :1;	//(18,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g3_auto_half_en                  :1;	//(19,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g4_auto_half_en                  :1;	//(20,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g5_auto_half_en                  :1;	//(21,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g6_auto_half_en                  :1;	//(22,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g7_auto_half_en                  :1;	//(23,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g0_pic_start_mask                :1;	//(24,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g1_pic_start_mask                :1;	//(25,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g2_pic_start_mask                :1;	//(26,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g3_pic_start_mask                :1;	//(27,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g4_pic_start_mask                :1;	//(28,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g5_pic_start_mask                :1;	//(29,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g6_pic_start_mask                :1;	//(30,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g7_pic_start_mask                :1;	//(31,RW,0x00) //[DEBUG][FW PIC_START MASK]
	};
}PE_VSD_OBC_M_SC_PIC_START_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483208 RW 0x7644_2200
	UINT32 idx_src_g0_auto_init             :3;	//(2:0,RW,0x00) //Source Selection of G0_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd0                           :1;
	UINT32 idx_src_g1_auto_init             :3;	//(6:4,RW,0x00) //Source Selection of G1_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd1                           :1;
	UINT32 idx_src_g2_auto_init             :3;	//(10:8,RW,0x02) //Source Selection of G2_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd2                           :1;
	UINT32 idx_src_g3_auto_init             :3;	//(14:12,RW,0x02) //Source Selection of G3_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd3                           :1;
	UINT32 idx_src_g4_auto_init             :3;	//(18:16,RW,0x04) //Source Selection of G4_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd4                           :1;
	UINT32 idx_src_g5_auto_init             :3;	//(22:20,RW,0x04) //Source Selection of G5_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd5                           :1;
	UINT32 idx_src_g6_auto_init             :3;	//(26:24,RW,0x06) //Source Selection of G6_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd6                           :1;
	UINT32 idx_src_g7_auto_init             :3;	//(30:28,RW,0x07) //Source Selection of G7_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd7                           :1;
	};
}PE_VSD_OBC_M_SC_CTRL_AUTO_INIT_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48320C RW 0xCA87_6420
	UINT32 idx_src_i0_intr_pulse            :3;	//(2:0,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i0_intr_pulse            :1;	//(3,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i1_intr_pulse            :3;	//(6:4,RW,0x02) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i1_intr_pulse            :1;	//(7,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i2_intr_pulse            :3;	//(10:8,RW,0x04) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i2_intr_pulse            :1;	//(11,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i3_intr_pulse            :3;	//(14:12,RW,0x06) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i3_intr_pulse            :1;	//(15,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i4_intr_pulse            :3;	//(18:16,RW,0x07) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i4_intr_pulse            :1;	//(19,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i5_intr_pulse            :3;	//(22:20,RW,0x00) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i5_intr_pulse            :1;	//(23,RW,0x01) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i6_intr_pulse            :3;	//(26:24,RW,0x02) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i6_intr_pulse            :1;	//(27,RW,0x01) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	UINT32 idx_src_i7_intr_pulse            :3;	//(30:28,RW,0x04) //Source Selection of INTR_I7_INTR_PULSE	 "000" := LENCON0_READY_RIS / BOSD_PULSE	 "001"  = AFBC0_RST_ACK_FAL / BOSD_I_VA_FAL	 "010"  = AFBC0_READY_RIS   / BOSD_I_VS_FAL	 "011"  = LENCON0_START     / BOSD_I_VS_RIS	 "100"  = LENCON1_READY_RIS / SOSD_PULSE	 "101"  = AFBC1_RST_ACK_FAL / SOSD_I_VA_FAL	 "110"  = AFBC1_READY_RIS   / SOSD_I_VS_FAL	 "111"  = LENCON1_START     / SOSD_I_VS_RIS
	UINT32 sel_src_i7_intr_pulse            :1;	//(31,RW,0x01) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SIGNAL FROM AFBC/LENCON	 '1'  = GROUP OF DISPLAY SYNC
	};
}PE_VSD_OBC_M_SC_CTRL_INTR_PULSE_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483210 RW 0x0000_0000
	UINT32 intr_i0_intr_pulse               :1;	//(0,RW,0x00) //[SRC_PULSE] s0_src_pulse
	UINT32 intr_i1_intr_pulse               :1;	//(1,RW,0x00) //[SRC_PULSE] s2_src_pulse
	UINT32 intr_i2_intr_pulse               :1;	//(2,RW,0x00) //[SRC_PULSE] s4_src_pulse
	UINT32 intr_i3_intr_pulse               :1;	//(3,RW,0x00) //[SRC_PULSE] s6_src_pulse
	UINT32 intr_i4_intr_pulse               :1;	//(4,RW,0x00) //[SRC_PULSE] s7_src_pulse
	UINT32 intr_i5_intr_pulse               :1;	//(5,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i6_intr_pulse               :1;	//(6,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i7_intr_pulse               :1;	//(7,RW,0x00) //[SRC_PULSE] SOSD_VA_FAL
	UINT32 intr_g0_pic_end                  :1;	//(8,RW,0x00) //[FRAME_END] GAV
	UINT32 intr_g1_pic_end                  :1;	//(9,RW,0x00) //[FRAME_END]
	UINT32 intr_g2_pic_end                  :1;	//(10,RW,0x00) //[FRAME_END]
	UINT32 intr_g3_pic_end                  :1;	//(11,RW,0x00) //[FRAME_END]
	UINT32 intr_g4_pic_end                  :1;	//(12,RW,0x00) //[FRAME_END]
	UINT32 intr_g5_pic_end                  :1;	//(13,RW,0x00) //[FRAME_END]
	UINT32 intr_g6_pic_end                  :1;	//(14,RW,0x00) //[FRAME_END]
	UINT32 intr_g7_pic_end                  :1;	//(15,RW,0x00) //[FRAME_END]
	UINT32 intr_obc_head_pic_end            :1;	//(16,RW,0x00) //OBC HEAD PIC_END
	UINT32 intr_obc_body_pic_end            :1;	//(17,RW,0x00) //OBC BODY PIC_END
	UINT32 resvd                            :14;
	};
}PE_VSD_OBC_M_SC_INTR_PE_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483214 RW 0xFFFF_FFFF
	UINT32 mask_i0_src_pulse                :1;	//(0,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i1_src_pulse                :1;	//(1,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i2_src_pulse                :1;	//(2,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i3_src_pulse                :1;	//(3,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i4_src_pulse                :1;	//(4,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i5_src_pulse                :1;	//(5,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i6_src_pulse                :1;	//(6,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i7_src_pulse                :1;	//(7,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g0_pic_end                  :1;	//(8,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g1_pic_end                  :1;	//(9,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g2_pic_end                  :1;	//(10,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g3_pic_end                  :1;	//(11,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g4_pic_end                  :1;	//(12,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g5_pic_end                  :1;	//(13,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g6_pic_end                  :1;	//(14,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g7_pic_end                  :1;	//(15,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_obc_head_pic_end            :1;	//(16,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_obc_body_pic_end            :1;	//(17,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 resvd                            :14;
	};
}PE_VSD_OBC_M_SC_INTR_MASK_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483218 RW 0x0000_0000
	UINT32 mux_i0_src_pulse                 :1;	//(0,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i1_src_pulse                 :1;	//(1,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i2_src_pulse                 :1;	//(2,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i3_src_pulse                 :1;	//(3,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i4_src_pulse                 :1;	//(4,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i5_src_pulse                 :1;	//(5,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i6_src_pulse                 :1;	//(6,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i7_src_pulse                 :1;	//(7,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g0_pic_end                   :1;	//(8,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g1_pic_end                   :1;	//(9,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g2_pic_end                   :1;	//(10,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g3_pic_end                   :1;	//(11,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g4_pic_end                   :1;	//(12,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g5_pic_end                   :1;	//(13,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g6_pic_end                   :1;	//(14,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g7_pic_end                   :1;	//(15,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_obc_head_pic_end             :1;	//(16,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_obc_body_pic_end             :1;	//(17,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 resvd                            :14;
	};
}PE_VSD_OBC_M_SC_INTR_MUX_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48321C RW 0xFFFF_FFFF
	UINT32 en_i0_src_pulse                  :1;	//(0,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i1_src_pulse                  :1;	//(1,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i2_src_pulse                  :1;	//(2,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i3_src_pulse                  :1;	//(3,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i4_src_pulse                  :1;	//(4,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i5_src_pulse                  :1;	//(5,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i6_src_pulse                  :1;	//(6,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i7_src_pulse                  :1;	//(7,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g0_pic_end                    :1;	//(8,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g1_pic_end                    :1;	//(9,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g2_pic_end                    :1;	//(10,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g3_pic_end                    :1;	//(11,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g4_pic_end                    :1;	//(12,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g5_pic_end                    :1;	//(13,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g6_pic_end                    :1;	//(14,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g7_pic_end                    :1;	//(15,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_obc_head_pic_end              :1;	//(16,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_obc_body_pic_end              :1;	//(17,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 resvd                            :14;
	};
}PE_VSD_OBC_M_SC_INTR_EN_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483220 RW 0x0000_0011
	UINT32 mif_r_logo_gain_line_inc         :2;	//(1:0,NA,0x01) //
	UINT32 mif_r_logo_gain_pf_flag_en       :1;	//(2:2,NA,0x00) //
	UINT32 mif_r_logo_gain_manual_en        :1;	//(3:3,NA,0x00) //
	UINT32 mif_r_logo_gain_en               :1;	//(4:4,NA,0x01) //
	UINT32 mif_r_logo_vreverse              :1;	//(5:5,NA,0x00) //
	UINT32 resvd0                           :2;
	UINT32 logo_l4sc_out_sel                :2;	//(9:8,NA,0x0) //0 : logo_l4sc_out	1 : 	2 : '0'	3 : '1'
	UINT32 resvd1                           :6;
	UINT32 mif_r_logo_gain_voffset          :9;	//(24:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :5;
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0x0) //Logo L4 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0x0) //Logo L4 de_clk clock gating
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_00_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483224 RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :12;	//(27:16,NA,0x0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_01_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483228 RW 0x0087_00F0
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x0F0) //input window active size (240x135)
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :12;	//(27:16,NA,0x087) //input window active size (240x135)
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_02_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48322C RW 0x0087_00F0
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x0F0) //input source total size (240x135)
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :12;	//(27:16,NA,0x087) //input source total size (240x135)
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_03_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483230 RW 0x0087_00F0
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x0F0) //width
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :12;	//(27:16,NA,0x087) //height
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_04_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483234 RW 0x0000_0000
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x00) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x00) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :17;
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_05_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483238 RW 0x0087_00F0
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x0F0) //
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :12;	//(27:16,NA,0x087) //
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_06_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48323C RW 0x0087_00F0
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x0F0) //
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :12;	//(27:16,NA,0x087) //
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_07_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483240 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win01_en                         :1;	//(2:2,NA,0x0) //1:  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_08_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483244 RW 0x0000_0000
	UINT32 win_w0_x0                        :12;	//(11:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0                        :12;	//(27:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_09_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483248 RW 0x0000_0000
	UINT32 win_w0_x1                        :12;	//(11:0,NA,0x0) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1                        :12;	//(27:16,NA,0x0) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_10_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48324C RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_out_voffset                  :12;	//(27:16,NA,0x0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_11_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483250 RW 0x0087_00F0
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x0F0) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_out_vactive                  :12;	//(27:16,NA,0x087) //input window active size
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_12_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483254 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_13_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483258 RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_STAT_00_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48325C RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_STAT_01_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483260 RW 0x0000_0011
	UINT32 mif_r_logo_gain_line_inc         :2;	//(1:0,NA,0x01) //
	UINT32 mif_r_logo_gain_pf_flag_en       :1;	//(2:2,NA,0x00) //
	UINT32 mif_r_logo_gain_manual_en        :1;	//(3:3,NA,0x00) //
	UINT32 mif_r_logo_gain_en               :1;	//(4:4,NA,0x01) //
	UINT32 mif_r_logo_vreverse              :1;	//(5:5,NA,0x00) //
	UINT32 resvd0                           :2;
	UINT32 logo_l4sc_out_sel                :2;	//(9:8,NA,0x0) //0 : logo_l4sc_out	1 : 	2 : '0'	3 : '1'
	UINT32 resvd1                           :6;
	UINT32 mif_r_logo_gain_voffset          :9;	//(24:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :5;
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0x0) //Logo L4 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0x0) //Logo L4 de_clk clock gating
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_00_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483264 RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :12;	//(27:16,NA,0x0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_01_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483268 RW 0x0087_00F0
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x0F0) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :12;	//(27:16,NA,0x087) //input window active size
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_02_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48326C RW 0x0087_00F0
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x0F0) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :12;	//(27:16,NA,0x087) //input source total size
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_03_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483270 RW 0x0087_00F0
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x0F0) //width
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :12;	//(27:16,NA,0x087) //height
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_04_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483274 RW 0x0000_0000
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x00) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x00) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :17;
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_05_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483278 RW 0x0087_00F0
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x0F0) //
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :12;	//(27:16,NA,0x087) //
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_06_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48327C RW 0x0087_00F0
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x0F0) //
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :12;	//(27:16,NA,0x087) //
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_07_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483280 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win01_en                         :1;	//(2:2,NA,0x0) //1:  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_08_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483284 RW 0x0000_0000
	UINT32 win_w0_x0                        :12;	//(11:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0                        :12;	//(27:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_09_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483288 RW 0x0000_0000
	UINT32 win_w0_x1                        :12;	//(11:0,NA,0x0) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1                        :12;	//(27:16,NA,0x0) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_10_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48328C RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_out_voffset                  :12;	//(27:16,NA,0x0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_11_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483290 RW 0x0087_00F0
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x0F0) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_out_vactive                  :12;	//(27:16,NA,0x087) //input window active size
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_12_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483294 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_13_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC483298 RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_STAT_00_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48329C RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_VSD_OBC_M_SC_OBC_BODY_L4SC_STAT_01_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832B0 RW 0x0000_0000
	UINT32 reg_path_reset_en_obc_h          :1;	//(0,RW,0x01) //AUTO RESET ENABLE FOR ASYNC_BRIDGE ON Video	 '0' := DISABLE	 '1'  = RESET BY PIC_INIT
	UINT32 reg_path_reset_en_obc_b          :1;	//(1,RW,0x01) //AUTO RESET ENABLE FOR ASYNC_BRIDGE ON OSD	 '0' := DISABLE	 '1'  = RESET BY PIC_INIT
	UINT32 resvd                            :30;
	};
}PE_VSD_OBC_M_SC_CTRL_BLOCK_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832B4 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_VSD_OBC_M_SC_CTRL_BLOCK1_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832B8 RW 0x0000_0000
	UINT32 reg_obc_head_clk_cg              :1;	//(0,RW,0x00) //[DEBUG] OBC HEAD Clock Gating ON	0 := Off	1 := On
	UINT32 reg_obc_body_clk_cg              :1;	//(1,RW,0x00) //[DEBUG] OBC BODY Clock Gating ON	0 := Off	1 := On
	UINT32 resvd                            :30;
	};
}PE_VSD_OBC_M_SC_CTRL_CG_ON_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832C0 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G0_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832C4 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G1_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832C8 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G2_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832CC RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G3_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832D0 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G4_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832D4 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G5_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832D8 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G6_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832DC RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}PE_VSD_OBC_M_SC_PIC_INIT_G7_TIMER_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832E4 RW 0x0000_0000
	UINT32 info_timer_run                   :24;	//(23:0,RW,0x0000_0000) //Processing Timer 값 * 1024	60Hz frame = 1/60, clock = 396Mhz, 	frame clock 수 = 396M/60 = 6.6 M
	UINT32 idx_end_src                      :3;	//(26:24,RW,0x00) //0 := G0_PIC_END	 X  = GX_PIC_END
	UINT32 sel_end_src                      :1;	//(27,RW,0x00) //'0' := PIC_END_RIS	 '1'  = PIC_END_RIS & PIC_2ND
	UINT32 idx_start_src                    :3;	//(30:28,RW,0x00) //0 := G0_PIC_START/INIT	 X  = GX_PIC_START/INIT
	UINT32 sel_start_src                    :1;	//(31,RW,0x00) //'0' := PIC_START	 '1'  = PIC_INIT
	};
}PE_VSD_OBC_M_SC_DBG_TIMER_RUN_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832E8 RW 0x0000_4000
	UINT32 rw_gx_pic_start_end              :1;	//(0:0,RW,0x0) //'0' := read	 '1'  = write
	UINT32 dly_gx_pic_start_end             :23;	//(23:1,RW,0x0000_2000) //idx_gx_pic_start_end = 0 ~ 7 이면	  dly_g0/~/g7_start = 0x2000 (0x4000/2)	idx_gx_pic_start_end = 8 ~ 15 이면	  dly_g0/~/g7_end_to = 0x00_192D ((396M/60*1)/1024)	idx_gx_pic_start_end = 16 ~ 23 이면	  dly_g0/~/g7_end_dly = 0x00_192D ((396M/60*1)/1024)
	UINT32 ctrl_gx_pic_start_end            :3;	//(26:24,RW,0x0) //idx_gx_pic_start_end = 0 ~ 7 이면	  ctrl_g0/~/g7_start ctrl[2:0]	idx_gx_pic_start_end = 8 ~ 15 이면	  ctrl_g0/~/g7_end[26] := pic end time out end pluse	  ctrl_g0/~/g7_end[25] := pic end time init sel '0' : master, '1' : delay init	  ctrl_g0/~/g7_end[24] := pic end time out en	idx_gx_pic_start_end = 16 ~ 23 이면	  ctrl_g0/~/g7_end[26] := pic end delay out end pluse	  ctrl_g0/~/g7_end[25] := pic end delay init sel '0' : master, '1' : delay init	  ctrl_g0/~/g7_end[24] := pic end delay en
	UINT32 idx_gx_pic_start_end             :5;	//(31:27,RW,0x0) //'0' ~ '7'  := g0_pic_start   ~ g7_pic_start	 '8' ~ '15' := g0_pic_end_to  ~ g7_pic_end_to	 '16'~ '23' := g0_pic_end_dly ~ g7_pic_end_dly
	};
}PE_VSD_OBC_M_SC_GX_PIC_START_END_PROC_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832EC RW 0x0000_0000
	UINT32 ctrl_monitor                     :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_VSD_OBC_M_SC_CTRL_MONITOR_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832F0 RW 0x0000_00FF
	UINT32 g0_pic_end_en                    :1;	//(0,RW,0x01) //[PIC END EN] OBC HEAD
	UINT32 g1_pic_end_en                    :1;	//(1,RW,0x01) //[PIC END EN] OBC BODY
	UINT32 g2_pic_end_en                    :1;	//(2,RW,0x01) //[NOT AVAILABLE][PIC END EN]
	UINT32 g3_pic_end_en                    :1;	//(3,RW,0x01) //[NOT AVAILABLE][PIC END EN]
	UINT32 g4_pic_end_en                    :1;	//(4,RW,0x01) //[NOT AVAILABLE][PIC END EN]
	UINT32 g5_pic_end_en                    :1;	//(5,RW,0x01) //[NOT AVAILABLE][PIC END EN]
	UINT32 g6_pic_end_en                    :1;	//(6,RW,0x01) //[NOT AVAILABLE][PIC END EN]
	UINT32 g7_pic_end_en                    :1;	//(7,RW,0x01) //[NOT AVAILABLE][PIC END EN]
	UINT32 b0_pic_end_en                    :1;	//(8,RW,0x00) //NA
	UINT32 b1_pic_end_en                    :1;	//(9,RW,0x00) //NA
	UINT32 b2_pic_end_en                    :1;	//(10,RW,0x00) //NA
	UINT32 b3_pic_end_en                    :1;	//(11,RW,0x00) //NA
	UINT32 b4_pic_end_en                    :1;	//(12,RW,0x00) //NA
	UINT32 b5_pic_end_en                    :1;	//(13,RW,0x00) //NA
	UINT32 b6_pic_end_en                    :1;	//(14,RW,0x00) //NA
	UINT32 b7_pic_end_en                    :1;	//(15,RW,0x00) //NA
	UINT32 pic_end_g0_force_en              :1;	//(16,RW,0x00) //
	UINT32 pic_end_g1_force_en              :1;	//(17,RW,0x00) //
	UINT32 pic_end_g2_force_en              :1;	//(18,RW,0x00) //
	UINT32 pic_end_g3_force_en              :1;	//(19,RW,0x00) //
	UINT32 pic_end_g4_force_en              :1;	//(20,RW,0x00) //
	UINT32 pic_end_g5_force_en              :1;	//(21,RW,0x00) //
	UINT32 pic_end_g6_force_en              :1;	//(22,RW,0x00) //
	UINT32 pic_end_g7_force_en              :1;	//(23,RW,0x00) //
	UINT32 pic_end_g0_force_value           :1;	//(24,RW,0x00) //
	UINT32 pic_end_g1_force_value           :1;	//(25,RW,0x00) //
	UINT32 pic_end_g2_force_value           :1;	//(26,RW,0x00) //
	UINT32 pic_end_g3_force_value           :1;	//(27,RW,0x00) //
	UINT32 pic_end_g4_force_value           :1;	//(28,RW,0x00) //
	UINT32 pic_end_g5_force_value           :1;	//(29,RW,0x00) //
	UINT32 pic_end_g6_force_value           :1;	//(30,RW,0x00) //
	UINT32 pic_end_g7_force_value           :1;	//(31,RW,0x00) //
	};
}PE_VSD_OBC_M_SC_CTRL_PIC_END_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832F4 RO 0x0000_0000
	UINT32 g0_pic_end                       :1;	//(0,RO,0x00) //[PIC END] OBC HEAD
	UINT32 g1_pic_end                       :1;	//(1,RO,0x00) //[PIC END] OBC BODY
	UINT32 g2_pic_end                       :1;	//(2,RO,0x00) //[NOT AVAILABLE][PIC END]
	UINT32 g3_pic_end                       :1;	//(3,RO,0x00) //[NOT AVAILABLE][PIC END]
	UINT32 g4_pic_end                       :1;	//(4,RO,0x00) //[NOT AVAILABLE][PIC END]
	UINT32 g5_pic_end                       :1;	//(5,RO,0x00) //[NOT AVAILABLE][PIC END]
	UINT32 g6_pic_end                       :1;	//(6,RO,0x00) //[NOT AVAILABLE][PIC END]
	UINT32 g7_pic_end                       :1;	//(7,RO,0x00) //[NOT AVAILABLE][PIC END]
	UINT32 b0_pic_end                       :1;	//(8,RO,0x00) //NA
	UINT32 b1_pic_end                       :1;	//(9,RO,0x00) //NA
	UINT32 b2_pic_end                       :1;	//(10,RO,0x00) //NA
	UINT32 b3_pic_end                       :1;	//(11,RO,0x00) //NA
	UINT32 b4_pic_end                       :1;	//(12,RO,0x00) //NA
	UINT32 b5_pic_end                       :1;	//(13,RO,0x00) //NA
	UINT32 b6_pic_end                       :1;	//(14,RO,0x00) //NA
	UINT32 b7_pic_end                       :1;	//(15,RO,0x00) //NA
	UINT32 g0_pic_end_init                  :1;	//(16,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g1_pic_end_init                  :1;	//(17,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g2_pic_end_init                  :1;	//(18,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g3_pic_end_init                  :1;	//(19,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g4_pic_end_init                  :1;	//(20,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g5_pic_end_init                  :1;	//(21,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g6_pic_end_init                  :1;	//(22,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g7_pic_end_init                  :1;	//(23,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 resvd                            :8;
	};
}PE_VSD_OBC_M_SC_INFO_PIC_END_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832F8 RW 0x0000_0000
	UINT32 rst_async_bridge                 :8;	//(7 : 0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 reg_gate_tx_obc_h_en             :1;	//(12,RW,0x00) //
	UINT32 reg_gate_tx_obc_h_dp_sel         :3;	//(15:13,RW,0x00) //0 : disable mon_pat                  	1 :  8b grad pat                     	2 :  8b ramp pat                     	3 :  8b ramp pat with R moving       	4 : 10b grad pat                     	5 : 10b ramp pat                     	6 : 10b ramp pat with L moving       	7 : 10b grad pat MISMATCH MAP OUTPUT
	UINT32 reg_gate_tx_obc_b_en             :1;	//(16,RW,0x00) //
	UINT32 reg_gate_tx_obc_b_dp_sel         :3;	//(19:17,RW,0x00) //0 : disable mon_pat                  	1 :  8b grad pat                     	2 :  8b ramp pat                     	3 :  8b ramp pat with R moving       	4 : 10b grad pat                     	5 : 10b ramp pat                     	6 : 10b ramp pat with L moving       	7 : 10b grad pat MISMATCH MAP OUTPUT
	UINT32 resvd1                           :4;
	UINT32 reg_ctrl_fpga                    :8;	//(31:24,RW,0x0000_0000) //: ctrl Gpio
	};
}PE_VSD_OBC_M_SC_CTRL_GPIO_O22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4832FC RW 0x0000_0000
	UINT32 reg_ctrl_gmau                    :32;	//(31:0,RW,0x0) //
	};
}PE_VSD_OBC_M_SC_CTRL_GMAU_O22_T;

typedef struct {
	PE_O22_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCC462000
	PE_O22_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCC462004
	PE_O22_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCC462008
	PE_O22_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCC46200C
	PE_O22_SHP_CORE_CTRL_04_T                     shp_core_ctrl_04;	//0xCC462010
	PE_O22_SHP_NEW_FD_CTRL_00_T                 shp_new_fd_ctrl_00;	//0xCC462014
	PE_O22_SHP_NEW_FD_CTRL_01_T                 shp_new_fd_ctrl_01;	//0xCC462018
	PE_O22_SHP_NEW_FD_CTRL_02_T                 shp_new_fd_ctrl_02;	//0xCC46201C
	PE_O22_SHP_NEW_FD_CTRL_03_T                 shp_new_fd_ctrl_03;	//0xCC462020
	PE_O22_SHP_NEW_FD_CTRL_04_T                 shp_new_fd_ctrl_04;	//0xCC462024
	PE_O22_SHP_TEXT_REGION_MAP_00_T         shp_text_region_map_00;	//0xCC462028
	UINT32                                                    reserved0;	//0xCC46202C
	UINT32                                                    reserved1;	//0xCC462030
	UINT32                                                    reserved2;	//0xCC462034
	UINT32                                                    reserved3;	//0xCC462038
	UINT32                                                    reserved4;	//0xCC46203C
	PE_O22_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCC462040
	UINT32                                                    reserved5;	//0xCC462044
	UINT32                                                    reserved6;	//0xCC462048
	UINT32                                                    reserved7;	//0xCC46204C
	PE_O22_SHP_GOS_CTRL_00_T                       shp_gos_ctrl_00;	//0xCC462050
	UINT32                                                    reserved8;	//0xCC462054
	UINT32                                                    reserved9;	//0xCC462058
	UINT32                                                   reserved10;	//0xCC46205C
	PE_O22_SHP_SYNC_DLY_CTRL_00_T             shp_sync_dly_ctrl_00;	//0xCC462060
	PE_O22_SHP_SYNC_DLY_CTRL_01_T             shp_sync_dly_ctrl_01;	//0xCC462064
	PE_O22_SHP_SYNC_DLY_CTRL_02_T             shp_sync_dly_ctrl_02;	//0xCC462068
	PE_O22_SHP_SYNC_DLY_CTRL_03_T             shp_sync_dly_ctrl_03;	//0xCC46206C
	PE_O22_SHP_SYNC_DLY_CTRL_04_T             shp_sync_dly_ctrl_04;	//0xCC462070
	PE_O22_SHP_SYNC_DLY_CTRL_05_T             shp_sync_dly_ctrl_05;	//0xCC462074
	PE_O22_SHP_SYNC_DLY_CTRL_06_T             shp_sync_dly_ctrl_06;	//0xCC462078
	PE_O22_SHP_SYNC_DLY_CTRL_07_T             shp_sync_dly_ctrl_07;	//0xCC46207C
	PE_O22_SHP_SYNC_DLY_CTRL_08_T             shp_sync_dly_ctrl_08;	//0xCC462080
	PE_O22_SHP_SYNC_DLY_CTRL_09_T             shp_sync_dly_ctrl_09;	//0xCC462084
	PE_O22_SHP_SYNC_DLY_CTRL_0A_T             shp_sync_dly_ctrl_0a;	//0xCC462088
	UINT32                                                   reserved11;	//0xCC46208C
	PE_O22_SHP_ROI_MASK_CTRL_00_T             shp_roi_mask_ctrl_00;	//0xCC462090
	PE_O22_SHP_ROI_MASK_CTRL_01_T             shp_roi_mask_ctrl_01;	//0xCC462094
	PE_O22_SHP_ROI_MASK_CTRL_02_T             shp_roi_mask_ctrl_02;	//0xCC462098
	UINT32                                                   reserved12;	//0xCC46209C
	PE_O22_SHP_ESF_CTRL_00_T                       shp_esf_ctrl_00;	//0xCC4620A0
	PE_O22_SHP_ESF_CTRL_01_T                       shp_esf_ctrl_01;	//0xCC4620A4
	PE_O22_SHP_ESF_CTRL_02_T                       shp_esf_ctrl_02;	//0xCC4620A8
	UINT32                                                   reserved13;	//0xCC4620AC
	PE_O22_SHP_ESF_WIN_CTRL_00_T               shp_esf_win_ctrl_00;	//0xCC4620B0
	PE_O22_SHP_ESF_WIN_CTRL_01_T               shp_esf_win_ctrl_01;	//0xCC4620B4
	PE_O22_SHP_ESF_WIN_CTRL_02_T               shp_esf_win_ctrl_02;	//0xCC4620B8
	PE_O22_SHP_ESF_WIN_CTRL_03_T               shp_esf_win_ctrl_03;	//0xCC4620BC
	PE_O22_SHP_ESF_WIN_CTRL_04_T               shp_esf_win_ctrl_04;	//0xCC4620C0
	UINT32                                                   reserved14;	//0xCC4620C4
	UINT32                                                   reserved15;	//0xCC4620C8
	UINT32                                                   reserved16;	//0xCC4620CC
	UINT32                                                   reserved17;	//0xCC4620D0
	UINT32                                                   reserved18;	//0xCC4620D4
	UINT32                                                   reserved19;	//0xCC4620D8
	UINT32                                                   reserved20;	//0xCC4620DC
	UINT32                                                   reserved21;	//0xCC4620E0
	UINT32                                                   reserved22;	//0xCC4620E4
	UINT32                                                   reserved23;	//0xCC4620E8
	UINT32                                                   reserved24;	//0xCC4620EC
	PE_O22_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCC4620F0
	UINT32                                                   reserved25;	//0xCC4620F4
	UINT32                                                   reserved26;	//0xCC4620F8
	UINT32                                                   reserved27;	//0xCC4620FC
	PE_O22_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCC462100
	PE_O22_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCC462104
	PE_O22_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCC462108
	PE_O22_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCC46210C
	PE_O22_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCC462110
	PE_O22_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCC462114
	PE_O22_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCC462118
	PE_O22_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCC46211C
	PE_O22_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCC462120
	PE_O22_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCC462124
	PE_O22_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCC462128
	PE_O22_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCC46212C
	PE_O22_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCC462130
	PE_O22_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCC462134
	PE_O22_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCC462138
	PE_O22_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCC46213C
	PE_O22_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCC462140
	PE_O22_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCC462144
	PE_O22_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCC462148
	PE_O22_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCC46214C
	PE_O22_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCC462150
	PE_O22_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCC462154
	PE_O22_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCC462158
	UINT32                                                   reserved28;	//0xCC46215C
	PE_O22_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCC462160
	PE_O22_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCC462164
	PE_O22_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCC462168
	PE_O22_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCC46216C
	PE_O22_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCC462170
	PE_O22_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCC462174
	PE_O22_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCC462178
	PE_O22_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCC46217C
	PE_O22_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCC462180
	PE_O22_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCC462184
	PE_O22_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCC462188
	PE_O22_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCC46218C
	PE_O22_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCC462190
	PE_O22_SHP_APL_CTRL_00_T                       shp_apl_ctrl_00;	//0xCC462194
	UINT32                                                   reserved29;	//0xCC462198
	UINT32                                                   reserved30;	//0xCC46219C
	PE_O22_SHP_LC_CTRL_00_T                         shp_lc_ctrl_00;	//0xCC4621A0
	PE_O22_SHP_LC_CTRL_01_T                         shp_lc_ctrl_01;	//0xCC4621A4
	PE_O22_SHP_LC_CTRL_02_T                         shp_lc_ctrl_02;	//0xCC4621A8
	PE_O22_SHP_LC_CTRL_03_T                         shp_lc_ctrl_03;	//0xCC4621AC
	PE_O22_SHP_LC_CTRL_04_T                         shp_lc_ctrl_04;	//0xCC4621B0
	UINT32                                                   reserved31;	//0xCC4621B4
	UINT32                                                   reserved32;	//0xCC4621B8
	UINT32                                                   reserved33;	//0xCC4621BC
	PE_O22_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCC4621C0
	PE_O22_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCC4621C4
	PE_O22_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCC4621C8
	PE_O22_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCC4621CC
	PE_O22_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCC4621D0
	PE_O22_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCC4621D4
	PE_O22_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCC4621D8
	PE_O22_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCC4621DC
	PE_O22_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCC4621E0
	PE_O22_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCC4621E4
	PE_O22_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCC4621E8
	PE_O22_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCC4621EC
	PE_O22_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCC4621F0
	PE_O22_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCC4621F4
	PE_O22_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCC4621F8
	PE_O22_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCC4621FC
	PE_O22_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCC462200
	PE_O22_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCC462204
	PE_O22_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCC462208
	PE_O22_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCC46220C
	PE_O22_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCC462210
	UINT32                                                   reserved34;	//0xCC462214
	UINT32                                                   reserved35;	//0xCC462218
	UINT32                                                   reserved36;	//0xCC46221C
	PE_O22_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCC462220
	PE_O22_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCC462224
	PE_O22_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCC462228
	PE_O22_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCC46222C
	PE_O22_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCC462230
	UINT32                                                   reserved37;	//0xCC462234
	UINT32                                                   reserved38;	//0xCC462238
	UINT32                                                   reserved39;	//0xCC46223C
	PE_O22_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCC462240
	PE_O22_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCC462244
	PE_O22_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCC462248
	PE_O22_SHP_TGEN_CTRL_03_C0_T               shp_tgen_ctrl_03_c0;	//0xCC46224C
	PE_O22_SHP_TGEN_CTRL_03_C1_T               shp_tgen_ctrl_03_c1;	//0xCC462250
	PE_O22_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCC462254
	PE_O22_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCC462258
	PE_O22_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCC46225C
	PE_O22_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCC462260
	PE_O22_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCC462264
	PE_O22_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCC462268
	PE_O22_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCC46226C
	PE_O22_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCC462270
	PE_O22_SHP_SNR_CTRL_00_T                       shp_snr_ctrl_00;	//0xCC462274
	UINT32                                                   reserved40;	//0xCC462278
	UINT32                                                   reserved41;	//0xCC46227C
	PE_O22_SHP_DCTP_CTRL_00_T                     shp_dctp_ctrl_00;	//0xCC462280
	PE_O22_SHP_DCTP_CTRL_01_T                     shp_dctp_ctrl_01;	//0xCC462284
	PE_O22_SHP_DCTP_CTRL_02_T                     shp_dctp_ctrl_02;	//0xCC462288
	PE_O22_SHP_DCTP_CTRL_03_T                     shp_dctp_ctrl_03;	//0xCC46228C
	PE_O22_SHP_DCTP_CTRL_04_T                     shp_dctp_ctrl_04;	//0xCC462290
	PE_O22_SHP_DCTP_CTRL_05_T                     shp_dctp_ctrl_05;	//0xCC462294
	PE_O22_SHP_DCTP_CTRL_06_T                     shp_dctp_ctrl_06;	//0xCC462298
	PE_O22_SHP_DCTP_CTRL_07_T                     shp_dctp_ctrl_07;	//0xCC46229C
	PE_O22_SHP_DCTP_CTRL_08_T                     shp_dctp_ctrl_08;	//0xCC4622A0
	PE_O22_SHP_DCTP_CTRL_09_T                     shp_dctp_ctrl_09;	//0xCC4622A4
	PE_O22_SHP_DCTP_CTRL_0A_T                     shp_dctp_ctrl_0a;	//0xCC4622A8
	PE_O22_SHP_DCTP_CTRL_0B_T                     shp_dctp_ctrl_0b;	//0xCC4622AC
	PE_O22_SHP_DCTP_CTRL_0C_T                     shp_dctp_ctrl_0c;	//0xCC4622B0
	PE_O22_SHP_DCTP_CTRL_0D_T                     shp_dctp_ctrl_0d;	//0xCC4622B4
	PE_O22_SHP_DCTP_CTRL_0E_T                     shp_dctp_ctrl_0e;	//0xCC4622B8
	PE_O22_SHP_DCTP_CTRL_0F_T                     shp_dctp_ctrl_0f;	//0xCC4622BC
	PE_O22_SHP_DCTP_CTRL_10_T                     shp_dctp_ctrl_10;	//0xCC4622C0
	PE_O22_SHP_DCTP_CTRL_11_T                     shp_dctp_ctrl_11;	//0xCC4622C4
	PE_O22_SHP_DCTP_CTRL_12_T                     shp_dctp_ctrl_12;	//0xCC4622C8
	PE_O22_SHP_DCTP_CTRL_13_T                     shp_dctp_ctrl_13;	//0xCC4622CC
	PE_O22_SHP_DCTP_CTRL_14_T                     shp_dctp_ctrl_14;	//0xCC4622D0
	PE_O22_SHP_DCTP_CTRL_15_T                     shp_dctp_ctrl_15;	//0xCC4622D4
	PE_O22_SHP_DCTP_CTRL_16_T                     shp_dctp_ctrl_16;	//0xCC4622D8
	PE_O22_SHP_DCTP_CTRL_17_T                     shp_dctp_ctrl_17;	//0xCC4622DC
	PE_O22_SHP_DCTP_CTRL_18_T                     shp_dctp_ctrl_18;	//0xCC4622E0
	PE_O22_SHP_DCTP_CTRL_19_T                     shp_dctp_ctrl_19;	//0xCC4622E4
	PE_O22_SHP_DCTP_CTRL_1A_T                     shp_dctp_ctrl_1a;	//0xCC4622E8
	PE_O22_SHP_DCTP_CTRL_1B_T                     shp_dctp_ctrl_1b;	//0xCC4622EC
	PE_O22_SHP_DCTP_CTRL_1C_T                     shp_dctp_ctrl_1c;	//0xCC4622F0
	PE_O22_SHP_DCTP_CTRL_1D_T                     shp_dctp_ctrl_1d;	//0xCC4622F4
	PE_O22_SHP_DCTP_CTRL_1E_T                     shp_dctp_ctrl_1e;	//0xCC4622F8
	PE_O22_SHP_DCTP_CTRL_1F_T                     shp_dctp_ctrl_1f;	//0xCC4622FC
	PE_O22_SHP_NNTG_CTRL_00_T                     shp_nntg_ctrl_00;	//0xCC462300
	PE_O22_SHP_NNTG_CTRL_01_C0_T               shp_nntg_ctrl_01_c0;	//0xCC462304
	PE_O22_SHP_NNTG_CTRL_02_C0_T               shp_nntg_ctrl_02_c0;	//0xCC462308
	PE_O22_SHP_NNTG_CTRL_03_C0_T               shp_nntg_ctrl_03_c0;	//0xCC46230C
	PE_O22_SHP_NNTG_CTRL_04_C0_T               shp_nntg_ctrl_04_c0;	//0xCC462310
	PE_O22_SHP_NNTG_CTRL_05_C0_T               shp_nntg_ctrl_05_c0;	//0xCC462314
	PE_O22_SHP_NNTG_CTRL_01_C1_T               shp_nntg_ctrl_01_c1;	//0xCC462318
	PE_O22_SHP_NNTG_CTRL_02_C1_T               shp_nntg_ctrl_02_c1;	//0xCC46231C
	PE_O22_SHP_NNTG_CTRL_03_C1_T               shp_nntg_ctrl_03_c1;	//0xCC462320
	PE_O22_SHP_NNTG_CTRL_04_C1_T               shp_nntg_ctrl_04_c1;	//0xCC462324
	PE_O22_SHP_NNTG_CTRL_05_C1_T               shp_nntg_ctrl_05_c1;	//0xCC462328
	PE_O22_SHP_NNTG_CTRL_06_T                     shp_nntg_ctrl_06;	//0xCC46232C
	PE_O22_SHP_NNTG_CTRL_07_T                     shp_nntg_ctrl_07;	//0xCC462330
	PE_O22_SHP_NNTG_CTRL_08_T                     shp_nntg_ctrl_08;	//0xCC462334
	PE_O22_SHP_NNTG_CTRL_09_T                     shp_nntg_ctrl_09;	//0xCC462338
	PE_O22_SHP_NNTG_CTRL_0A_T                     shp_nntg_ctrl_0a;	//0xCC46233C
	PE_O22_SHP_NNTG_CTRL_0B_T                     shp_nntg_ctrl_0b;	//0xCC462340
	PE_O22_SHP_NNTG_CTRL_0C_T                     shp_nntg_ctrl_0c;	//0xCC462344
	PE_O22_SHP_NNTG_CTRL_0D_T                     shp_nntg_ctrl_0d;	//0xCC462348
	PE_O22_SHP_NNTG_CTRL_0E_T                     shp_nntg_ctrl_0e;	//0xCC46234C
	PE_O22_SHP_NNTG_CTRL_0F_T                     shp_nntg_ctrl_0f;	//0xCC462350
	PE_O22_SHP_NNTG_CTRL_10_T                     shp_nntg_ctrl_10;	//0xCC462354
	UINT32                                                   reserved42;	//0xCC462358
	UINT32                                                   reserved43;	//0xCC46235C
	PE_O22_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCC462360
	PE_O22_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCC462364
	PE_O22_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCC462368
	PE_O22_SHP_DP_SUM_CTRL_03_T                 shp_dp_sum_ctrl_03;	//0xCC46236C
	PE_O22_SHP_DP_SUM_CTRL_04_T                 shp_dp_sum_ctrl_04;	//0xCC462370
	PE_O22_SHP_DP_SUM_CTRL_05_T                 shp_dp_sum_ctrl_05;	//0xCC462374
	PE_O22_SHP_DP_SUM_CTRL_06_T                 shp_dp_sum_ctrl_06;	//0xCC462378
	PE_O22_SHP_DP_SUM_CTRL_07_T                 shp_dp_sum_ctrl_07;	//0xCC46237C
	PE_O22_SHP_DP_SUM_CTRL_08_T                 shp_dp_sum_ctrl_08;	//0xCC462380
	PE_O22_SHP_DP_SUM_CTRL_09_T                 shp_dp_sum_ctrl_09;	//0xCC462384
	PE_O22_SHP_DP_SUM_CTRL_0A_T                 shp_dp_sum_ctrl_0a;	//0xCC462388
	UINT32                                                   reserved44;	//0xCC46238C
	PE_O22_SHP_PSP_CTRL_00_T                       shp_psp_ctrl_00;	//0xCC462390
	PE_O22_SHP_DP_SUM_CTRL_0B_T                 shp_dp_sum_ctrl_0b;	//0xCC462394
	PE_O22_SHP_DP_SUM_CTRL_0C_T                 shp_dp_sum_ctrl_0c;	//0xCC462398
	UINT32                                                   reserved45;	//0xCC46239C
	PE_O22_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCC4623A0
	PE_O22_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCC4623A4
	PE_O22_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCC4623A8
	PE_O22_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCC4623AC
	PE_O22_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCC4623B0
	UINT32                                                   reserved46;	//0xCC4623B4
	UINT32                                                   reserved47;	//0xCC4623B8
	UINT32                                                   reserved48;	//0xCC4623BC
	PE_O22_SHP_FD_REGION_TEXT_00_T           shp_fd_region_text_00;	//0xCC4623C0
	PE_O22_SHP_FD_REGION_TEXT_01_T           shp_fd_region_text_01;	//0xCC4623C4
	PE_O22_SHP_FD_REGION_TEXT_02_T           shp_fd_region_text_02;	//0xCC4623C8
	PE_O22_SHP_FD_TMAP_TEMP_00_T               shp_fd_tmap_temp_00;	//0xCC4623CC
	PE_O22_SHP_FD_TMAP_TEMP_01_T               shp_fd_tmap_temp_01;	//0xCC4623D0
	PE_O22_SHP_FD_TMAP_TEMP_02_T               shp_fd_tmap_temp_02;	//0xCC4623D4
	PE_O22_SHP_FD_TMAP_TEMP_03_T               shp_fd_tmap_temp_03;	//0xCC4623D8
	PE_O22_SHP_FD_TMAP_TEMP_04_T               shp_fd_tmap_temp_04;	//0xCC4623DC
	PE_O22_SHP_FD_TMAP_TEMP_05_T               shp_fd_tmap_temp_05;	//0xCC4623E0
	PE_O22_SHP_FD_TMAP_TEMP_06_T               shp_fd_tmap_temp_06;	//0xCC4623E4
	PE_O22_SHP_FD_TMAP_TEMP_07_T               shp_fd_tmap_temp_07;	//0xCC4623E8
	PE_O22_SHP_FD_TMAP_TEMP_08_T               shp_fd_tmap_temp_08;	//0xCC4623EC
	PE_O22_SHP_FD_TMAP_TEMP_09_T               shp_fd_tmap_temp_09;	//0xCC4623F0
	PE_O22_SHP_FD_TMAP_TEMP_0A_T               shp_fd_tmap_temp_0a;	//0xCC4623F4
	PE_O22_SHP_FD_TMAP_TEMP_0B_T               shp_fd_tmap_temp_0b;	//0xCC4623F8
	PE_O22_SHP_FD_TMAP_TEMP_0C_T               shp_fd_tmap_temp_0c;	//0xCC4623FC
	PE_O22_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0xCC462400
	PE_O22_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0xCC462404
	PE_O22_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0xCC462408
	PE_O22_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0xCC46240C
	PE_O22_SHP_DJ_CTRL_04_T                         shp_dj_ctrl_04;	//0xCC462410
	PE_O22_SHP_DJ_CTRL_05_T                         shp_dj_ctrl_05;	//0xCC462414
	PE_O22_SHP_DJ_CTRL_06_T                         shp_dj_ctrl_06;	//0xCC462418
	PE_O22_SHP_DJ_CTRL_07_T                         shp_dj_ctrl_07;	//0xCC46241C
	PE_O22_SHP_DJ_CTRL_08_T                         shp_dj_ctrl_08;	//0xCC462420
	PE_O22_SHP_DJ_CTRL_09_T                         shp_dj_ctrl_09;	//0xCC462424
	PE_O22_SHP_DJ_CTRL_0A_T                         shp_dj_ctrl_0a;	//0xCC462428
	PE_O22_SHP_DJ_CTRL_0B_T                         shp_dj_ctrl_0b;	//0xCC46242C
	PE_O22_SHP_DJ_CTRL_0C_T                         shp_dj_ctrl_0c;	//0xCC462430
	PE_O22_SHP_DJ_CTRL_0D_T                         shp_dj_ctrl_0d;	//0xCC462434
	PE_O22_SHP_DJ_CTRL_0E_T                         shp_dj_ctrl_0e;	//0xCC462438
	PE_O22_SHP_DJ_CTRL_0F_T                         shp_dj_ctrl_0f;	//0xCC46243C
	PE_O22_SHP_DJ_CTRL_10_T                         shp_dj_ctrl_10;	//0xCC462440
	PE_O22_SHP_DJ_CTRL_11_T                         shp_dj_ctrl_11;	//0xCC462444
	PE_O22_SHP_DJ_CTRL_12_T                         shp_dj_ctrl_12;	//0xCC462448
	PE_O22_SHP_DJ_CTRL_13_T                         shp_dj_ctrl_13;	//0xCC46244C
	PE_O22_SHP_DJ_CTRL_14_T                         shp_dj_ctrl_14;	//0xCC462450
	PE_O22_SHP_DJ_CTRL_15_T                         shp_dj_ctrl_15;	//0xCC462454
	PE_O22_SHP_DJ_CTRL_16_T                         shp_dj_ctrl_16;	//0xCC462458
	PE_O22_SHP_DJ_CTRL_17_T                         shp_dj_ctrl_17;	//0xCC46245C
	PE_O22_SHP_DJ_CTRL_18_T                         shp_dj_ctrl_18;	//0xCC462460
	PE_O22_SHP_DJ_CTRL_19_T                         shp_dj_ctrl_19;	//0xCC462464
	PE_O22_SHP_DJ_CTRL_1A_T                         shp_dj_ctrl_1a;	//0xCC462468
	PE_O22_SHP_DJ_CTRL_1B_T                         shp_dj_ctrl_1b;	//0xCC46246C
	PE_O22_SHP_DJ_CTRL_1C_T                         shp_dj_ctrl_1c;	//0xCC462470
	PE_O22_SHP_DJ_CTRL_1D_T                         shp_dj_ctrl_1d;	//0xCC462474
	PE_O22_SHP_DJ_CTRL_1E_T                         shp_dj_ctrl_1e;	//0xCC462478
	PE_O22_SHP_DJ_CTRL_1F_T                         shp_dj_ctrl_1f;	//0xCC46247C
	PE_O22_SHP_DJ_CTRL_20_T                         shp_dj_ctrl_20;	//0xCC462480
	UINT32                                                   reserved49;	//0xCC462484
	UINT32                                                   reserved50;	//0xCC462488
	UINT32                                                   reserved51;	//0xCC46248C
	PE_O22_SHP_DB_CTRL_00_T                         shp_db_ctrl_00;	//0xCC462490
	PE_O22_SHP_DB_CTRL_01_T                         shp_db_ctrl_01;	//0xCC462494
	UINT32                                                   reserved52;	//0xCC462498
	UINT32                                                   reserved53;	//0xCC46249C
	PE_O22_SHP_DJ_WIN_CTRL_00_T                 shp_dj_win_ctrl_00;	//0xCC4624A0
	PE_O22_SHP_DJ_WIN_CTRL_01_T                 shp_dj_win_ctrl_01;	//0xCC4624A4
	PE_O22_SHP_DJ_WIN_CTRL_02_T                 shp_dj_win_ctrl_02;	//0xCC4624A8
	PE_O22_SHP_DJ_WIN_CTRL_03_T                 shp_dj_win_ctrl_03;	//0xCC4624AC
	PE_O22_SHP_DJ_WIN_CTRL_04_T                 shp_dj_win_ctrl_04;	//0xCC4624B0
	UINT32                                                   reserved54;	//0xCC4624B4
	UINT32                                                   reserved55;	//0xCC4624B8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_00_T     shp_dj_text_gain_ctrl_00;	//0xCC4624BC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_01_T     shp_dj_text_gain_ctrl_01;	//0xCC4624C0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_02_T     shp_dj_text_gain_ctrl_02;	//0xCC4624C4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_03_T     shp_dj_text_gain_ctrl_03;	//0xCC4624C8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_04_T     shp_dj_text_gain_ctrl_04;	//0xCC4624CC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_05_T     shp_dj_text_gain_ctrl_05;	//0xCC4624D0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_06_T     shp_dj_text_gain_ctrl_06;	//0xCC4624D4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_07_T     shp_dj_text_gain_ctrl_07;	//0xCC4624D8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_08_T     shp_dj_text_gain_ctrl_08;	//0xCC4624DC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_09_T     shp_dj_text_gain_ctrl_09;	//0xCC4624E0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_10_T     shp_dj_text_gain_ctrl_10;	//0xCC4624E4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_11_T     shp_dj_text_gain_ctrl_11;	//0xCC4624E8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_12_T     shp_dj_text_gain_ctrl_12;	//0xCC4624EC
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_13_T     shp_dj_text_gain_ctrl_13;	//0xCC4624F0
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_14_T     shp_dj_text_gain_ctrl_14;	//0xCC4624F4
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_15_T     shp_dj_text_gain_ctrl_15;	//0xCC4624F8
	PE_O22_SHP_DJ_TEXT_GAIN_CTRL_16_T     shp_dj_text_gain_ctrl_16;	//0xCC4624FC
	PE_O22_SHP_CHROMA_CTRL_00_T                 shp_chroma_ctrl_00;	//0xCC462500
	PE_O22_SHP_CHROMA_CTRL_01_T                 shp_chroma_ctrl_01;	//0xCC462504
	PE_O22_SHP_CHROMA_CTRL_02_T                 shp_chroma_ctrl_02;	//0xCC462508
	PE_O22_SHP_CHROMA_CTRL_03_T                 shp_chroma_ctrl_03;	//0xCC46250C
	PE_O22_SHP_CHROMA_CTRL_04_T                 shp_chroma_ctrl_04;	//0xCC462510
	PE_O22_SHP_CHROMA_CTRL_05_T                 shp_chroma_ctrl_05;	//0xCC462514
	PE_O22_SHP_CHROMA_CTRL_06_T                 shp_chroma_ctrl_06;	//0xCC462518
	PE_O22_SHP_CHROMA_CTRL_07_T                 shp_chroma_ctrl_07;	//0xCC46251C
	PE_O22_SHP_CHROMA_CTRL_08_T                 shp_chroma_ctrl_08;	//0xCC462520
	PE_O22_SHP_CHROMA_CTRL_09_T                 shp_chroma_ctrl_09;	//0xCC462524
	PE_O22_SHP_CHROMA_CTRL_0A_T                 shp_chroma_ctrl_0a;	//0xCC462528
	PE_O22_SHP_CHROMA_CTRL_0B_T                 shp_chroma_ctrl_0b;	//0xCC46252C
	PE_O22_SHP_CHROMA_CTRL_0C_T                 shp_chroma_ctrl_0c;	//0xCC462530
	PE_O22_SHP_CHROMA_CTRL_0D_T                 shp_chroma_ctrl_0d;	//0xCC462534
	PE_O22_SHP_CHROMA_CTRL_0E_T                 shp_chroma_ctrl_0e;	//0xCC462538
	UINT32                                                   reserved56;	//0xCC46253C
	UINT32                                                   reserved57;	//0xCC462540
	UINT32                                                   reserved58;	//0xCC462544
	UINT32                                                   reserved59;	//0xCC462548
	UINT32                                                   reserved60;	//0xCC46254C
	PE_O22_SHP_CTI_CTRL_00_T                       shp_cti_ctrl_00;	//0xCC462550
	PE_O22_SHP_CTI_CTRL_01_T                       shp_cti_ctrl_01;	//0xCC462554
	PE_O22_SHP_CTI_CTRL_02_T                       shp_cti_ctrl_02;	//0xCC462558
	UINT32                                                   reserved61;	//0xCC46255C
	PE_O22_SHP_FRC_FLICK_CTRL_00_T           shp_frc_flick_ctrl_00;	//0xCC462560
	PE_O22_SHP_FRC_FLICK_CTRL_01_T           shp_frc_flick_ctrl_01;	//0xCC462564
	PE_O22_SHP_FRC_FLICK_CTRL_02_T           shp_frc_flick_ctrl_02;	//0xCC462568
	PE_O22_SHP_FRC_FLICK_CTRL_03_T           shp_frc_flick_ctrl_03;	//0xCC46256C
	PE_O22_SHP_FRC_BLUR_CTRL_00_T             shp_frc_blur_ctrl_00;	//0xCC462570
	PE_O22_SHP_FRC_BLUR_CTRL_01_T             shp_frc_blur_ctrl_01;	//0xCC462574
	PE_O22_SHP_FRC_BLUR_CTRL_02_T             shp_frc_blur_ctrl_02;	//0xCC462578
	PE_O22_SHP_FRC_BLUR_CTRL_03_T             shp_frc_blur_ctrl_03;	//0xCC46257C
	PE_O22_SHP_FRC_BLUR_CTRL_04_T             shp_frc_blur_ctrl_04;	//0xCC462580
	PE_O22_SHP_FRC_BLUR_CTRL_05_T             shp_frc_blur_ctrl_05;	//0xCC462584
	PE_O22_SHP_FRC_BLUR_CTRL_06_T             shp_frc_blur_ctrl_06;	//0xCC462588
	UINT32                                                   reserved62;	//0xCC46258C
	PE_O22_SHP_FRC_HALO_CTRL_00_T             shp_frc_halo_ctrl_00;	//0xCC462590
	PE_O22_SHP_FRC_HALO_CTRL_01_T             shp_frc_halo_ctrl_01;	//0xCC462594
	PE_O22_SHP_FRC_HALO_CTRL_02_T             shp_frc_halo_ctrl_02;	//0xCC462598
	PE_O22_SHP_FRC_HALO_CTRL_03_T             shp_frc_halo_ctrl_03;	//0xCC46259C
	PE_O22_SHP_FRC_WIN_CTRL_00_T               shp_frc_win_ctrl_00;	//0xCC4625A0
	PE_O22_SHP_FRC_WIN_CTRL_01_T               shp_frc_win_ctrl_01;	//0xCC4625A4
	PE_O22_SHP_FRC_WIN_CTRL_02_T               shp_frc_win_ctrl_02;	//0xCC4625A8
	PE_O22_SHP_FRC_WIN_CTRL_03_T               shp_frc_win_ctrl_03;	//0xCC4625AC
	PE_O22_SHP_FRC_WIN_CTRL_04_T               shp_frc_win_ctrl_04;	//0xCC4625B0
	UINT32                                                   reserved63;	//0xCC4625B4
	UINT32                                                   reserved64;	//0xCC4625B8
	UINT32                                                   reserved65;	//0xCC4625BC
	UINT32                                                   reserved66;	//0xCC4625C0
	UINT32                                                   reserved67;	//0xCC4625C4
	UINT32                                                   reserved68;	//0xCC4625C8
	UINT32                                                   reserved69;	//0xCC4625CC
	UINT32                                                   reserved70;	//0xCC4625D0
	UINT32                                                   reserved71;	//0xCC4625D4
	UINT32                                                   reserved72;	//0xCC4625D8
	UINT32                                                   reserved73;	//0xCC4625DC
	UINT32                                                   reserved74;	//0xCC4625E0
	UINT32                                                   reserved75;	//0xCC4625E4
	UINT32                                                   reserved76;	//0xCC4625E8
	UINT32                                                   reserved77;	//0xCC4625EC
	UINT32                                                   reserved78;	//0xCC4625F0
	UINT32                                                   reserved79;	//0xCC4625F4
	UINT32                                                   reserved80;	//0xCC4625F8
	UINT32                                                   reserved81;	//0xCC4625FC
	PE_O22_SHP_MOTION_GAIN_CTRL_00_T       shp_motion_gain_ctrl_00;	//0xCC462600
	PE_O22_SHP_MOTION_GAIN_CTRL_01_T       shp_motion_gain_ctrl_01;	//0xCC462604
	PE_O22_SHP_MOTION_GAIN_CTRL_02_T       shp_motion_gain_ctrl_02;	//0xCC462608
	PE_O22_SHP_MOTION_GAIN_CTRL_03_T       shp_motion_gain_ctrl_03;	//0xCC46260C
	PE_O22_SHP_MOTION_GAIN_CTRL_04_T       shp_motion_gain_ctrl_04;	//0xCC462610
	PE_O22_SHP_MOTION_GAIN_CTRL_05_T       shp_motion_gain_ctrl_05;	//0xCC462614
	PE_O22_SHP_MOTION_GAIN_CTRL_06_T       shp_motion_gain_ctrl_06;	//0xCC462618
	PE_O22_SHP_MOTION_GAIN_CTRL_07_T       shp_motion_gain_ctrl_07;	//0xCC46261C
	PE_O22_SHP_MOTION_GAIN_CTRL_08_T       shp_motion_gain_ctrl_08;	//0xCC462620
	PE_O22_SHP_MOTION_GAIN_CTRL_09_T       shp_motion_gain_ctrl_09;	//0xCC462624
	PE_O22_SHP_MOTION_GAIN_CTRL_0A_T       shp_motion_gain_ctrl_0a;	//0xCC462628
	PE_O22_SHP_MOTION_GAIN_CTRL_0B_T       shp_motion_gain_ctrl_0b;	//0xCC46262C
	PE_O22_SHP_MOTION_GAIN_CTRL_0C_T       shp_motion_gain_ctrl_0c;	//0xCC462630
	UINT32                                                   reserved82;	//0xCC462634
	UINT32                                                   reserved83;	//0xCC462638
	UINT32                                                   reserved84;	//0xCC46263C
	PE_O22_SHP_MOTION_PROT_CTRL_00_T       shp_motion_prot_ctrl_00;	//0xCC462640
	PE_O22_SHP_MOTION_PROT_CTRL_01_T       shp_motion_prot_ctrl_01;	//0xCC462644
	PE_O22_SHP_MOTION_PROT_CTRL_02_T       shp_motion_prot_ctrl_02;	//0xCC462648
	PE_O22_SHP_MOTION_PROT_CTRL_03_T       shp_motion_prot_ctrl_03;	//0xCC46264C
	PE_O22_SHP_MOTION_PROT_CTRL_04_T       shp_motion_prot_ctrl_04;	//0xCC462650
	UINT32                                                   reserved85;	//0xCC462654
	UINT32                                                   reserved86;	//0xCC462658
	UINT32                                                   reserved87;	//0xCC46265C
	UINT32                                                   reserved88;	//0xCC462660
	UINT32                                                   reserved89;	//0xCC462664
	UINT32                                                   reserved90;	//0xCC462668
	UINT32                                                   reserved91;	//0xCC46266C
	PE_O22_SHP_MOT_WIN_CTRL_00_T               shp_mot_win_ctrl_00;	//0xCC462670
	PE_O22_SHP_MOT_WIN_CTRL_01_T               shp_mot_win_ctrl_01;	//0xCC462674
	PE_O22_SHP_MOT_WIN_CTRL_02_T               shp_mot_win_ctrl_02;	//0xCC462678
	PE_O22_SHP_MOT_WIN_CTRL_03_T               shp_mot_win_ctrl_03;	//0xCC46267C
	PE_O22_SHP_MOT_WIN_CTRL_04_T               shp_mot_win_ctrl_04;	//0xCC462680
	UINT32                                                   reserved92;	//0xCC462684
	UINT32                                                   reserved93;	//0xCC462688
	UINT32                                                   reserved94;	//0xCC46268C
	PE_O22_SHP_OBJ_CTRL_00_T                       shp_obj_ctrl_00;	//0xCC462690
	PE_O22_SHP_OBJ_CTRL_01_T                       shp_obj_ctrl_01;	//0xCC462694
	PE_O22_SHP_OBJ_CTRL_02_T                       shp_obj_ctrl_02;	//0xCC462698
	PE_O22_SHP_OBJ_CTRL_03_T                       shp_obj_ctrl_03;	//0xCC46269C
	PE_O22_SHP_OBJ_CTRL_04_T                       shp_obj_ctrl_04;	//0xCC4626A0
	PE_O22_SHP_OBJ_CTRL_05_T                       shp_obj_ctrl_05;	//0xCC4626A4
	PE_O22_SHP_OBJ_CTRL_06_T                       shp_obj_ctrl_06;	//0xCC4626A8
	PE_O22_SHP_OBJ_CTRL_07_T                       shp_obj_ctrl_07;	//0xCC4626AC
	PE_O22_SHP_OBJ_CTRL_08_T                       shp_obj_ctrl_08;	//0xCC4626B0
	PE_O22_SHP_OBJ_CTRL_09_T                       shp_obj_ctrl_09;	//0xCC4626B4
	PE_O22_SHP_OBJ_CTRL_0A_T                       shp_obj_ctrl_0a;	//0xCC4626B8
	PE_O22_SHP_OBJ_CTRL_0B_T                       shp_obj_ctrl_0b;	//0xCC4626BC
	PE_O22_SHP_OBJ_CTRL_0C_T                       shp_obj_ctrl_0c;	//0xCC4626C0
	UINT32                                                   reserved95;	//0xCC4626C4
	UINT32                                                   reserved96;	//0xCC4626C8
	UINT32                                                   reserved97;	//0xCC4626CC
	UINT32                                                   reserved98;	//0xCC4626D0
	UINT32                                                   reserved99;	//0xCC4626D4
	UINT32                                                  reserved100;	//0xCC4626D8
	UINT32                                                  reserved101;	//0xCC4626DC
	UINT32                                                  reserved102;	//0xCC4626E0
	UINT32                                                  reserved103;	//0xCC4626E4
	UINT32                                                  reserved104;	//0xCC4626E8
	UINT32                                                  reserved105;	//0xCC4626EC
	UINT32                                                  reserved106;	//0xCC4626F0
	UINT32                                                  reserved107;	//0xCC4626F4
	UINT32                                                  reserved108;	//0xCC4626F8
	UINT32                                                  reserved109;	//0xCC4626FC
	UINT32                                                  reserved110;	//0xCC462700
	UINT32                                                  reserved111;	//0xCC462704
	UINT32                                                  reserved112;	//0xCC462708
	UINT32                                                  reserved113;	//0xCC46270C
	UINT32                                                  reserved114;	//0xCC462710
	UINT32                                                  reserved115;	//0xCC462714
	UINT32                                                  reserved116;	//0xCC462718
	UINT32                                                  reserved117;	//0xCC46271C
	UINT32                                                  reserved118;	//0xCC462720
	UINT32                                                  reserved119;	//0xCC462724
	UINT32                                                  reserved120;	//0xCC462728
	UINT32                                                  reserved121;	//0xCC46272C
	UINT32                                                  reserved122;	//0xCC462730
	UINT32                                                  reserved123;	//0xCC462734
	UINT32                                                  reserved124;	//0xCC462738
	UINT32                                                  reserved125;	//0xCC46273C
	UINT32                                                  reserved126;	//0xCC462740
	UINT32                                                  reserved127;	//0xCC462744
	UINT32                                                  reserved128;	//0xCC462748
	UINT32                                                  reserved129;	//0xCC46274C
	UINT32                                                  reserved130;	//0xCC462750
	UINT32                                                  reserved131;	//0xCC462754
	UINT32                                                  reserved132;	//0xCC462758
	UINT32                                                  reserved133;	//0xCC46275C
	UINT32                                                  reserved134;	//0xCC462760
	UINT32                                                  reserved135;	//0xCC462764
	UINT32                                                  reserved136;	//0xCC462768
	UINT32                                                  reserved137;	//0xCC46276C
	UINT32                                                  reserved138;	//0xCC462770
	UINT32                                                  reserved139;	//0xCC462774
	UINT32                                                  reserved140;	//0xCC462778
	UINT32                                                  reserved141;	//0xCC46277C
	UINT32                                                  reserved142;	//0xCC462780
	UINT32                                                  reserved143;	//0xCC462784
	UINT32                                                  reserved144;	//0xCC462788
	UINT32                                                  reserved145;	//0xCC46278C
	UINT32                                                  reserved146;	//0xCC462790
	UINT32                                                  reserved147;	//0xCC462794
	UINT32                                                  reserved148;	//0xCC462798
	UINT32                                                  reserved149;	//0xCC46279C
	PE_O22_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCC4627A0
	PE_O22_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCC4627A4
	PE_O22_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCC4627A8
	PE_O22_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCC4627AC
	PE_O22_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCC4627B0
	PE_O22_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCC4627B4
	UINT32                                                  reserved150;	//0xCC4627B8
	UINT32                                                  reserved151;	//0xCC4627BC
	UINT32                                                  reserved152;	//0xCC4627C0
	UINT32                                                  reserved153;	//0xCC4627C4
	UINT32                                                  reserved154;	//0xCC4627C8
	UINT32                                                  reserved155;	//0xCC4627CC
	PE_O22_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCC4627D0
	PE_O22_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCC4627D4
	PE_O22_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCC4627D8
	PE_O22_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCC4627DC
	PE_O22_SHP_MOTION_GAIN_STAT_00_T       shp_motion_gain_stat_00;	//0xCC4627E0
	PE_O22_SHP_MOTION_GAIN_STAT_01_T       shp_motion_gain_stat_01;	//0xCC4627E4
	PE_O22_SHP_CORE_EDGE_STAT_00_T           shp_core_edge_stat_00;	//0xCC4627E8
	PE_O22_SHP_CORE_EDGE_STAT_01_T           shp_core_edge_stat_01;	//0xCC4627EC
	PE_O22_SHP_CORE_EDGE_STAT_02_T           shp_core_edge_stat_02;	//0xCC4627F0
	PE_O22_SHP_CORE_EDGE_STAT_03_T           shp_core_edge_stat_03;	//0xCC4627F4
	PE_O22_SHP_CORE_EDGE_STAT_04_T           shp_core_edge_stat_04;	//0xCC4627F8
	PE_O22_SHP_CORE_EDGE_STAT_05_T           shp_core_edge_stat_05;	//0xCC4627FC
	PE_O22_SHP_CORE_TMAP_STAT_00_T           shp_core_tmap_stat_00;	//0xCC462800
	PE_O22_SHP_CORE_TMAP_STAT_01_T           shp_core_tmap_stat_01;	//0xCC462804
	PE_O22_SHP_CORE_TMAP_STAT_02_T           shp_core_tmap_stat_02;	//0xCC462808
	PE_O22_SHP_CORE_TMAP_STAT_03_T           shp_core_tmap_stat_03;	//0xCC46280C
	PE_O22_SHP_CORE_TMAP_STAT_04_T           shp_core_tmap_stat_04;	//0xCC462810
	PE_O22_SHP_CORE_TMAP_STAT_05_T           shp_core_tmap_stat_05;	//0xCC462814
	PE_O22_SHP_CORE_TMAP_STAT_06_T           shp_core_tmap_stat_06;	//0xCC462818
	PE_O22_SHP_CORE_TMAP_STAT_07_T           shp_core_tmap_stat_07;	//0xCC46281C
	PE_O22_SHP_FACE_WIN_CTRL_00_T             shp_face_win_ctrl_00;	//0xCC462820
	PE_O22_SHP_FACE_WIN_CTRL_01_T             shp_face_win_ctrl_01;	//0xCC462824
	PE_O22_SHP_FACE_WIN_CTRL_02_T             shp_face_win_ctrl_02;	//0xCC462828
	PE_O22_SHP_FACE_WIN_CTRL_03_T             shp_face_win_ctrl_03;	//0xCC46282C
	PE_O22_SHP_FACE_WIN_CTRL_04_T             shp_face_win_ctrl_04;	//0xCC462830
	PE_O22_SHP_FACE_WIN_CTRL_05_T             shp_face_win_ctrl_05;	//0xCC462834
	PE_O22_SHP_BODY_WIN_CTRL_00_T             shp_body_win_ctrl_00;	//0xCC462838
	PE_O22_SHP_BODY_WIN_CTRL_01_T             shp_body_win_ctrl_01;	//0xCC46283C
	PE_O22_SHP_BODY_WIN_CTRL_02_T             shp_body_win_ctrl_02;	//0xCC462840
	PE_O22_SHP_BODY_WIN_CTRL_03_T             shp_body_win_ctrl_03;	//0xCC462844
	PE_O22_SHP_BODY_WIN_CTRL_04_T             shp_body_win_ctrl_04;	//0xCC462848
	PE_O22_SHP_BODY_WIN_CTRL_05_T             shp_body_win_ctrl_05;	//0xCC46284C
	UINT32                                                  reserved156;	//0xCC462850
	UINT32                                                  reserved157;	//0xCC462854
	UINT32                                                  reserved158;	//0xCC462858
	UINT32                                                  reserved159;	//0xCC46285C
	UINT32                                                  reserved160;	//0xCC462860
	UINT32                                                  reserved161;	//0xCC462864
	UINT32                                                  reserved162;	//0xCC462868
	UINT32                                                  reserved163;	//0xCC46286C
	UINT32                                                  reserved164;	//0xCC462870
	UINT32                                                  reserved165;	//0xCC462874
	UINT32                                                  reserved166;	//0xCC462878
	UINT32                                                  reserved167;	//0xCC46287C
	UINT32                                                  reserved168;	//0xCC462880
	UINT32                                                  reserved169;	//0xCC462884
	UINT32                                                  reserved170;	//0xCC462888
	UINT32                                                  reserved171;	//0xCC46288C
	UINT32                                                  reserved172;	//0xCC462890
	UINT32                                                  reserved173;	//0xCC462894
	UINT32                                                  reserved174;	//0xCC462898
	UINT32                                                  reserved175;	//0xCC46289C
	UINT32                                                  reserved176;	//0xCC4628A0
	UINT32                                                  reserved177;	//0xCC4628A4
	UINT32                                                  reserved178;	//0xCC4628A8
	UINT32                                                  reserved179;	//0xCC4628AC
	UINT32                                                  reserved180;	//0xCC4628B0
	UINT32                                                  reserved181;	//0xCC4628B4
	UINT32                                                  reserved182;	//0xCC4628B8
	UINT32                                                  reserved183;	//0xCC4628BC
	UINT32                                                  reserved184;	//0xCC4628C0
	UINT32                                                  reserved185;	//0xCC4628C4
	UINT32                                                  reserved186;	//0xCC4628C8
	UINT32                                                  reserved187;	//0xCC4628CC
	UINT32                                                  reserved188;	//0xCC4628D0
	UINT32                                                  reserved189;	//0xCC4628D4
	UINT32                                                  reserved190;	//0xCC4628D8
	UINT32                                                  reserved191;	//0xCC4628DC
	UINT32                                                  reserved192;	//0xCC4628E0
	UINT32                                                  reserved193;	//0xCC4628E4
	UINT32                                                  reserved194;	//0xCC4628E8
	UINT32                                                  reserved195;	//0xCC4628EC
	PE_O22_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCC4628F0
	PE_O22_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCC4628F4
	PE_O22_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCC4628F8
	PE_O22_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCC4628FC
}PE_SHP_REG_O22_T;

typedef struct {
	PE_O22_VSD_OBE_CTRL_000_T                         reg_obe_ctrl_000;	//0xCC460200
	PE_O22_VSD_OBE_CTRL_001_T                         reg_obe_ctrl_001;	//0xCC460204
	PE_O22_VSD_OBE_CTRL_002_T                         reg_obe_ctrl_002;	//0xCC460208
	PE_O22_VSD_OBE_CTRL_003_T                         reg_obe_ctrl_003;	//0xCC46020C
	PE_O22_VSD_OBE_CTRL_004_T                         reg_obe_ctrl_004;	//0xCC460210
	PE_O22_VSD_OBE_CTRL_005_T                         reg_obe_ctrl_005;	//0xCC460214
	PE_O22_VSD_OBE_IND_CTRL_0_T                     reg_obe_ind_ctrl_0;	//0xCC460218
	PE_O22_VSD_OBE_IND_CTRL_1_T                     reg_obe_ind_ctrl_1;	//0xCC46021C
	PE_O22_VSD_OBE_IND_CTRL_2_T                     reg_obe_ind_ctrl_2;	//0xCC460220
	PE_O22_VSD_OBE_CTRL_009_T                         reg_obe_ctrl_009;	//0xCC460224
	PE_O22_VSD_OBE_CTRL_010_T                         reg_obe_ctrl_010;	//0xCC460228
	PE_O22_VSD_OBE_CTRL_011_T                         reg_obe_ctrl_011;	//0xCC46022C
	PE_O22_VSD_OBE_CTRL_012_T                         reg_obe_ctrl_012;	//0xCC460230
	PE_O22_VSD_OBE_CTRL_013_T                         reg_obe_ctrl_013;	//0xCC460234
	PE_O22_VSD_OBE_CTRL_014_T                         reg_obe_ctrl_014;	//0xCC460238
	PE_O22_VSD_OBE_CTRL_015_T                         reg_obe_ctrl_015;	//0xCC46023C
	PE_O22_VSD_OBE_CTRL_016_T                         reg_obe_ctrl_016;	//0xCC460240
	PE_O22_VSD_OBE_CTRL_017_T                         reg_obe_ctrl_017;	//0xCC460244
	PE_O22_VSD_OBE_CTRL_018_T                         reg_obe_ctrl_018;	//0xCC460248
	PE_O22_VSD_OBE_CTRL_019_T                         reg_obe_ctrl_019;	//0xCC46024C
	PE_O22_VSD_OBE_CTRL_020_T                         reg_obe_ctrl_020;	//0xCC460250
	PE_O22_VSD_OBE_CTRL_021_T                         reg_obe_ctrl_021;	//0xCC460254
	PE_O22_VSD_OBE_CTRL_022_T                         reg_obe_ctrl_022;	//0xCC460258
	PE_O22_VSD_OBE_CTRL_023_T                         reg_obe_ctrl_023;	//0xCC46025C
	PE_O22_VSD_OBE_CTRL_024_T                         reg_obe_ctrl_024;	//0xCC460260
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
	PE_O22_VSD_OBE_CTRL_064_T                         reg_obe_ctrl_064;	//0xCC460300
	PE_O22_VSD_OBE_CTRL_065_T                         reg_obe_ctrl_065;	//0xCC460304
	PE_O22_VSD_OBE_CTRL_066_T                         reg_obe_ctrl_066;	//0xCC460308
	PE_O22_VSD_OBE_CTRL_067_T                         reg_obe_ctrl_067;	//0xCC46030C
	PE_O22_VSD_OBE_CTRL_068_T                         reg_obe_ctrl_068;	//0xCC460310
	PE_O22_VSD_OBE_CTRL_069_T                         reg_obe_ctrl_069;	//0xCC460314
	PE_O22_VSD_OBE_CTRL_070_T                         reg_obe_ctrl_070;	//0xCC460318
	PE_O22_VSD_OBE_CTRL_071_T                         reg_obe_ctrl_071;	//0xCC46031C
	PE_O22_VSD_OBE_CTRL_072_T                         reg_obe_ctrl_072;	//0xCC460320
	PE_O22_VSD_OBE_CTRL_073_T                         reg_obe_ctrl_073;	//0xCC460324
	PE_O22_VSD_OBE_CTRL_074_T                         reg_obe_ctrl_074;	//0xCC460328
	PE_O22_VSD_OBE_CTRL_075_T                         reg_obe_ctrl_075;	//0xCC46032C
	PE_O22_VSD_OBE_CTRL_076_T                         reg_obe_ctrl_076;	//0xCC460330
	PE_O22_VSD_OBE_CTRL_077_T                         reg_obe_ctrl_077;	//0xCC460334
	PE_O22_VSD_OBE_CTRL_078_T                         reg_obe_ctrl_078;	//0xCC460338
	PE_O22_VSD_OBE_CTRL_079_T                         reg_obe_ctrl_079;	//0xCC46033C
	PE_O22_VSD_OBE_CTRL_080_T                         reg_obe_ctrl_080;	//0xCC460340
	PE_O22_VSD_OBE_CTRL_081_T                         reg_obe_ctrl_081;	//0xCC460344
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
	PE_O22_VSD_OBE_CTRL_108_T                         reg_obe_ctrl_108;	//0xCC4603B0
	PE_O22_VSD_OBE_CTRL_109_T                         reg_obe_ctrl_109;	//0xCC4603B4
	PE_O22_VSD_OBE_CTRL_110_T                         reg_obe_ctrl_110;	//0xCC4603B8
	PE_O22_VSD_OBE_CTRL_111_T                         reg_obe_ctrl_111;	//0xCC4603BC
	PE_O22_VSD_OBE_CTRL_112_T                         reg_obe_ctrl_112;	//0xCC4603C0
	PE_O22_VSD_OBE_CTRL_113_T                         reg_obe_ctrl_113;	//0xCC4603C4
	PE_O22_VSD_OBE_CTRL_114_T                         reg_obe_ctrl_114;	//0xCC4603C8
	PE_O22_VSD_OBE_CTRL_115_T                         reg_obe_ctrl_115;	//0xCC4603CC
	PE_O22_VSD_OBE_CTRL_116_T                         reg_obe_ctrl_116;	//0xCC4603D0
	PE_O22_VSD_OBE_CTRL_117_T                         reg_obe_ctrl_117;	//0xCC4603D4
	PE_O22_VSD_OBE_CTRL_118_T                         reg_obe_ctrl_118;	//0xCC4603D8
	PE_O22_VSD_OBE_CTRL_119_T                         reg_obe_ctrl_119;	//0xCC4603DC
	PE_O22_VSD_OBE_CTRL_120_T                         reg_obe_ctrl_120;	//0xCC4603E0
	PE_O22_VSD_OBE_CTRL_121_T                         reg_obe_ctrl_121;	//0xCC4603E4
	PE_O22_VSD_OBE_CTRL_122_T                         reg_obe_ctrl_122;	//0xCC4603E8
	PE_O22_VSD_OBE_CTRL_123_T                         reg_obe_ctrl_123;	//0xCC4603EC
	PE_O22_VSD_OBE_CTRL_124_T                         reg_obe_ctrl_124;	//0xCC4603F0
	PE_O22_VSD_OBE_CTRL_125_T                         reg_obe_ctrl_125;	//0xCC4603F4
	PE_O22_VSD_OBE_CTRL_126_T                         reg_obe_ctrl_126;	//0xCC4603F8
	PE_O22_VSD_OBE_CTRL_127_T                         reg_obe_ctrl_127;	//0xCC4603FC
	PE_O22_VSD_OBE_CTRL_128_T                         reg_obe_ctrl_128;	//0xCC460400
	PE_O22_VSD_OBE_CTRL_129_T                         reg_obe_ctrl_129;	//0xCC460404
	PE_O22_VSD_OBE_CTRL_130_T                         reg_obe_ctrl_130;	//0xCC460408
	PE_O22_VSD_OBE_CTRL_131_T                         reg_obe_ctrl_131;	//0xCC46040C
	PE_O22_VSD_OBE_CTRL_132_T                         reg_obe_ctrl_132;	//0xCC460410
	PE_O22_VSD_OBE_CTRL_133_T                         reg_obe_ctrl_133;	//0xCC460414
	PE_O22_VSD_OBE_CTRL_134_T                         reg_obe_ctrl_134;	//0xCC460418
	PE_O22_VSD_OBE_CTRL_135_T                         reg_obe_ctrl_135;	//0xCC46041C
	PE_O22_VSD_OBE_CTRL_136_T                         reg_obe_ctrl_136;	//0xCC460420
	PE_O22_VSD_OBE_CTRL_137_T                         reg_obe_ctrl_137;	//0xCC460424
}PE_VSD_OBE_REG_O22_T;

typedef struct {
	PE_O22_VSD_TOP_CTRL_00_T                           dtm_top_ctrl_00;	//0xCC460C00
	PE_O22_VSD_TOP_CTRL_01_T                           dtm_top_ctrl_01;	//0xCC460C04
	PE_O22_VSD_TOP_CTRL_02_T                           dtm_top_ctrl_02;	//0xCC460C08
	PE_O22_VSD_TOP_CTRL_03_T                           dtm_top_ctrl_03;	//0xCC460C0C
	PE_O22_VSD_TOP_CTRL_04_T                           dtm_top_ctrl_04;	//0xCC460C10
	PE_O22_VSD_TOP_CTRL_05_T                           dtm_top_ctrl_05;	//0xCC460C14
	UINT32                                                    reserved0;	//0xCC460C18
	UINT32                                                    reserved1;	//0xCC460C1C
	PE_O22_VSD_FSW_CTRL_00_T                           dtm_fsw_ctrl_00;	//0xCC460C20
	PE_O22_VSD_FSW_CTRL_01_T                           dtm_fsw_ctrl_01;	//0xCC460C24
	PE_O22_VSD_FSW_CTRL_02_T                           dtm_fsw_ctrl_02;	//0xCC460C28
	PE_O22_VSD_FSW_CTRL_03_T                           dtm_fsw_ctrl_03;	//0xCC460C2C
	UINT32                                                    reserved2;	//0xCC460C30
	UINT32                                                    reserved3;	//0xCC460C34
	UINT32                                                    reserved4;	//0xCC460C38
	UINT32                                                    reserved5;	//0xCC460C3C
	PE_O22_VSD_CSC1_CTRL_00_T                         dtm_csc1_ctrl_00;	//0xCC460C40
	PE_O22_VSD_CSC1_CTRL_01_T                         dtm_csc1_ctrl_01;	//0xCC460C44
	PE_O22_VSD_CSC1_CTRL_02_T                         dtm_csc1_ctrl_02;	//0xCC460C48
	PE_O22_VSD_CSC1_CTRL_03_T                         dtm_csc1_ctrl_03;	//0xCC460C4C
	PE_O22_VSD_CSC1_CTRL_04_T                         dtm_csc1_ctrl_04;	//0xCC460C50
	PE_O22_VSD_CSC1_CTRL_05_T                         dtm_csc1_ctrl_05;	//0xCC460C54
	PE_O22_VSD_CSC1_CTRL_06_T                         dtm_csc1_ctrl_06;	//0xCC460C58
	PE_O22_VSD_CSC1_CTRL_07_T                         dtm_csc1_ctrl_07;	//0xCC460C5C
	PE_O22_VSD_CSC1_CTRL_08_T                         dtm_csc1_ctrl_08;	//0xCC460C60
	UINT32                                                    reserved6;	//0xCC460C64
	UINT32                                                    reserved7;	//0xCC460C68
	UINT32                                                    reserved8;	//0xCC460C6C
	PE_O22_VSD_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0xCC460C70
	PE_O22_VSD_LLUT_CTRL_01_T                         dtm_llut_ctrl_01;	//0xCC460C74
	PE_O22_VSD_LLUT_CTRL_02_T                         dtm_llut_ctrl_02;	//0xCC460C78
	PE_O22_VSD_LLUT_CTRL_03_T                         dtm_llut_ctrl_03;	//0xCC460C7C
	PE_O22_VSD_LLUT_CTRL_04_T                         dtm_llut_ctrl_04;	//0xCC460C80
	PE_O22_VSD_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0xCC460C84
	PE_O22_VSD_LLUT0_IA_CTRL_T                       dtm_llut0_ia_ctrl;	//0xCC460C88
	PE_O22_VSD_LLUT0_IA_DATA_T                       dtm_llut0_ia_data;	//0xCC460C8C
	PE_O22_VSD_LLUT1_IA_CTRL_T                       dtm_llut1_ia_ctrl;	//0xCC460C90
	PE_O22_VSD_LLUT1_IA_DATA_T                       dtm_llut1_ia_data;	//0xCC460C94
	PE_O22_VSD_LLUT2_IA_CTRL_T                       dtm_llut2_ia_ctrl;	//0xCC460C98
	PE_O22_VSD_LLUT2_IA_DATA_T                       dtm_llut2_ia_data;	//0xCC460C9C
	PE_O22_VSD_LUT_LUM_SAT_CTRL_00_T           dtm_lut_lum_sat_ctrl_00;	//0xCC460CA0
	PE_O22_VSD_LUT_LUM_SAT_CTRL_01_T           dtm_lut_lum_sat_ctrl_01;	//0xCC460CA4
	PE_O22_VSD_LUT_LUM_SAT_CTRL_02_T           dtm_lut_lum_sat_ctrl_02;	//0xCC460CA8
	PE_O22_VSD_LUT_LUM_SAT_CTRL_03_T           dtm_lut_lum_sat_ctrl_03;	//0xCC460CAC
	UINT32                                                    reserved9;	//0xCC460CB0
	UINT32                                                   reserved10;	//0xCC460CB4
	UINT32                                                   reserved11;	//0xCC460CB8
	UINT32                                                   reserved12;	//0xCC460CBC
	UINT32                                                   reserved13;	//0xCC460CC0
	UINT32                                                   reserved14;	//0xCC460CC4
	UINT32                                                   reserved15;	//0xCC460CC8
	UINT32                                                   reserved16;	//0xCC460CCC
	UINT32                                                   reserved17;	//0xCC460CD0
	UINT32                                                   reserved18;	//0xCC460CD4
	UINT32                                                   reserved19;	//0xCC460CD8
	UINT32                                                   reserved20;	//0xCC460CDC
	PE_O22_VSD_HUE_SAT_CTRL_00_T                   dtm_hue_sat_ctrl_00;	//0xCC460CE0
	PE_O22_VSD_HUE_SAT_CTRL_01_T                   dtm_hue_sat_ctrl_01;	//0xCC460CE4
	UINT32                                                   reserved21;	//0xCC460CE8
	UINT32                                                   reserved22;	//0xCC460CEC
	PE_O22_VSD_ODD_LLUT_CTRL_01_T                 dtm_odd_llut_ctrl_01;	//0xCC460CF0
	PE_O22_VSD_ODD_LLUT_CTRL_02_T                 dtm_odd_llut_ctrl_02;	//0xCC460CF4
	PE_O22_VSD_ODD_LLUT_CTRL_03_T                 dtm_odd_llut_ctrl_03;	//0xCC460CF8
	PE_O22_VSD_ODD_LLUT_CTRL_04_T                 dtm_odd_llut_ctrl_04;	//0xCC460CFC
}PE_VSD_DTM_REG_O22_T;

typedef struct {
	PE_O22_VSD_OBC_HEAD_PSP_CTRL00_T                                psp_ctrl00;	//0xCC460700
	PE_O22_VSD_OBC_HEAD_PSP_CTRL01_T                                psp_ctrl01;	//0xCC460704
	PE_O22_VSD_OBC_HEAD_PSP_CTRL02_T                                psp_ctrl02;	//0xCC460708
	PE_O22_VSD_OBC_HEAD_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xCC46070C
	PE_O22_VSD_OBC_HEAD_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xCC460710
	UINT32                                                    reserved0;	//0xCC460714
	UINT32                                                    reserved1;	//0xCC460718
	UINT32                                                    reserved2;	//0xCC46071C
	UINT32                                                    reserved3;	//0xCC460720
	UINT32                                                    reserved4;	//0xCC460724
	UINT32                                                    reserved5;	//0xCC460728
	UINT32                                                    reserved6;	//0xCC46072C
	UINT32                                                    reserved7;	//0xCC460730
	UINT32                                                    reserved8;	//0xCC460734
	UINT32                                                    reserved9;	//0xCC460738
	UINT32                                                   reserved10;	//0xCC46073C
	UINT32                                                   reserved11;	//0xCC460740
	UINT32                                                   reserved12;	//0xCC460744
	PE_O22_VSD_OBC_HEAD_DISPLAY_DEBUG_MAP_T                  display_debug_map;	//0xCC460748
	UINT32                                                   reserved13;	//0xCC46074C
	UINT32                                                   reserved14;	//0xCC460750
	UINT32                                                   reserved15;	//0xCC460754
	UINT32                                                   reserved16;	//0xCC460758
	UINT32                                                   reserved17;	//0xCC46075C
	UINT32                                                   reserved18;	//0xCC460760
	UINT32                                                   reserved19;	//0xCC460764
	UINT32                                                   reserved20;	//0xCC460768
	UINT32                                                   reserved21;	//0xCC46076C
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL0_T                            refine_ctrl0;	//0xCC460770
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL1_T                            refine_ctrl1;	//0xCC460774
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL2_T                            refine_ctrl2;	//0xCC460778
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL3_T                            refine_ctrl3;	//0xCC46077C
	PE_O22_VSD_OBC_HEAD_REFINE_CTRL4_T                            refine_ctrl4;	//0xCC460780
}PE_VSD_OBC_HEAD_REG_O22_T;

typedef struct {
	PE_O22_VSD_OBC_BODY_PSP_CTRL00_T                                psp_ctrl00;	//0xCC460500
	PE_O22_VSD_OBC_BODY_PSP_CTRL01_T                                psp_ctrl01;	//0xCC460504
	PE_O22_VSD_OBC_BODY_PSP_CTRL02_T                                psp_ctrl02;	//0xCC460508
	PE_O22_VSD_OBC_BODY_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xCC46050C
	PE_O22_VSD_OBC_BODY_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xCC460510
	UINT32                                                    reserved0;	//0xCC460514
	UINT32                                                    reserved1;	//0xCC460518
	UINT32                                                    reserved2;	//0xCC46051C
	UINT32                                                    reserved3;	//0xCC460520
	UINT32                                                    reserved4;	//0xCC460524
	UINT32                                                    reserved5;	//0xCC460528
	UINT32                                                    reserved6;	//0xCC46052C
	UINT32                                                    reserved7;	//0xCC460530
	UINT32                                                    reserved8;	//0xCC460534
	UINT32                                                    reserved9;	//0xCC460538
	UINT32                                                   reserved10;	//0xCC46053C
	UINT32                                                   reserved11;	//0xCC460540
	UINT32                                                   reserved12;	//0xCC460544
	PE_O22_VSD_OBC_BODY_DISPLAY_DEBUG_MAP_T                  display_debug_map;	//0xCC460548
	UINT32                                                   reserved13;	//0xCC46054C
	UINT32                                                   reserved14;	//0xCC460550
	UINT32                                                   reserved15;	//0xCC460554
	UINT32                                                   reserved16;	//0xCC460558
	UINT32                                                   reserved17;	//0xCC46055C
	UINT32                                                   reserved18;	//0xCC460560
	UINT32                                                   reserved19;	//0xCC460564
	UINT32                                                   reserved20;	//0xCC460568
	UINT32                                                   reserved21;	//0xCC46056C
	PE_O22_VSD_OBC_BODY_REFINE_CTRL0_T                            refine_ctrl0;	//0xCC460570
	PE_O22_VSD_OBC_BODY_REFINE_CTRL1_T                            refine_ctrl1;	//0xCC460574
	PE_O22_VSD_OBC_BODY_REFINE_CTRL2_T                            refine_ctrl2;	//0xCC460578
	PE_O22_VSD_OBC_BODY_REFINE_CTRL3_T                            refine_ctrl3;	//0xCC46057C
	PE_O22_VSD_OBC_BODY_REFINE_CTRL4_T                            refine_ctrl4;	//0xCC460580
	UINT32                                                   reserved22;	//0xCC460584
	UINT32                                                   reserved23;	//0xCC460588
	UINT32                                                   reserved24;	//0xCC46058C
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T obj_refine_body_gain_ctrl_00;	//0xCC460590
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T obj_refine_body_gain_ctrl_01;	//0xCC460594
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T obj_refine_body_gain_ctrl_02;	//0xCC460598
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T obj_refine_body_gain_ctrl_03;	//0xCC46059C
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T obj_refine_body_gain_ctrl_04;	//0xCC4605A0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T obj_refine_body_gain_ctrl_05;	//0xCC4605A4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T obj_refine_body_gain_ctrl_06;	//0xCC4605A8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T obj_refine_body_gain_ctrl_07;	//0xCC4605AC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T obj_refine_body_gain_ctrl_08;	//0xCC4605B0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T obj_refine_body_gain_ctrl_09;	//0xCC4605B4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T obj_refine_body_gain_ctrl_10;	//0xCC4605B8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T obj_refine_body_gain_ctrl_11;	//0xCC4605BC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T obj_refine_body_gain_ctrl_12;	//0xCC4605C0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T obj_refine_body_gain_ctrl_13;	//0xCC4605C4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T obj_refine_body_gain_ctrl_14;	//0xCC4605C8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T obj_refine_body_gain_ctrl_15;	//0xCC4605CC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T obj_refine_body_gain_ctrl_16;	//0xCC4605D0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T obj_refine_body_gain_ctrl_17;	//0xCC4605D4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T obj_refine_body_gain_ctrl_18;	//0xCC4605D8
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T obj_refine_body_gain_ctrl_19;	//0xCC4605DC
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T obj_refine_body_gain_ctrl_20;	//0xCC4605E0
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T obj_refine_body_gain_ctrl_21;	//0xCC4605E4
	PE_O22_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T obj_refine_body_gain_ctrl_22;	//0xCC4605E8
}PE_VSD_OBC_BODY_REG_O22_T;

typedef struct {
	PE_O22_AMG0_HEAD_AMG_TOP_CTRL_00_T                     amg_top_ctrl_00;	//0xCC8C4A00
	PE_O22_AMG0_HEAD_AMG_TOP_CTRL_01_T                     amg_top_ctrl_01;	//0xCC8C4A04
	PE_O22_AMG0_HEAD_AMG_TOP_CTRL_02_T                     amg_top_ctrl_02;	//0xCC8C4A08
	PE_O22_AMG0_HEAD_AMG_TOP_CTRL_03_T                     amg_top_ctrl_03;	//0xCC8C4A0C
	PE_O22_AMG0_HEAD_AMG_TOP_CTRL_04_T                     amg_top_ctrl_04;	//0xCC8C4A10
	UINT32                                                    reserved0;	//0xCC8C4A14
	UINT32                                                    reserved1;	//0xCC8C4A18
	UINT32                                                    reserved2;	//0xCC8C4A1C
	PE_O22_AMG0_HEAD_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xCC8C4A20
	PE_O22_AMG0_HEAD_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xCC8C4A24
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_00_T                 histogram_stat_00;	//0xCC8C4A28
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_01_T                 histogram_stat_01;	//0xCC8C4A2C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_02_T                 histogram_stat_02;	//0xCC8C4A30
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_03_T                 histogram_stat_03;	//0xCC8C4A34
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_04_T                 histogram_stat_04;	//0xCC8C4A38
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_05_T                 histogram_stat_05;	//0xCC8C4A3C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_06_T                 histogram_stat_06;	//0xCC8C4A40
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_07_T                 histogram_stat_07;	//0xCC8C4A44
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_08_T                 histogram_stat_08;	//0xCC8C4A48
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_09_T                 histogram_stat_09;	//0xCC8C4A4C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_10_T                 histogram_stat_10;	//0xCC8C4A50
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_11_T                 histogram_stat_11;	//0xCC8C4A54
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_12_T                 histogram_stat_12;	//0xCC8C4A58
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_13_T                 histogram_stat_13;	//0xCC8C4A5C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_14_T                 histogram_stat_14;	//0xCC8C4A60
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_15_T                 histogram_stat_15;	//0xCC8C4A64
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_16_T                 histogram_stat_16;	//0xCC8C4A68
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_17_T                 histogram_stat_17;	//0xCC8C4A6C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_18_T                 histogram_stat_18;	//0xCC8C4A70
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_19_T                 histogram_stat_19;	//0xCC8C4A74
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_20_T                 histogram_stat_20;	//0xCC8C4A78
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_21_T                 histogram_stat_21;	//0xCC8C4A7C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_22_T                 histogram_stat_22;	//0xCC8C4A80
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_23_T                 histogram_stat_23;	//0xCC8C4A84
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_24_T                 histogram_stat_24;	//0xCC8C4A88
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_25_T                 histogram_stat_25;	//0xCC8C4A8C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_26_T                 histogram_stat_26;	//0xCC8C4A90
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_27_T                 histogram_stat_27;	//0xCC8C4A94
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_28_T                 histogram_stat_28;	//0xCC8C4A98
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_29_T                 histogram_stat_29;	//0xCC8C4A9C
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_30_T                 histogram_stat_30;	//0xCC8C4AA0
	PE_O22_AMG0_HEAD_HISTOGRAM_STAT_31_T                 histogram_stat_31;	//0xCC8C4AA4
	UINT32                                                    reserved3;	//0xCC8C4AA8
	UINT32                                                    reserved4;	//0xCC8C4AAC
	PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xCC8C4AB0
	PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xCC8C4AB4
	PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xCC8C4AB8
	PE_O22_AMG0_HEAD_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xCC8C4ABC
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_00_T                     box_set_ctrl_00;	//0xCC8C4AC0
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_01_T                     box_set_ctrl_01;	//0xCC8C4AC4
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_02_T                     box_set_ctrl_02;	//0xCC8C4AC8
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_03_T                     box_set_ctrl_03;	//0xCC8C4ACC
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_04_T                     box_set_ctrl_04;	//0xCC8C4AD0
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_05_T                     box_set_ctrl_05;	//0xCC8C4AD4
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_06_T                     box_set_ctrl_06;	//0xCC8C4AD8
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_07_T                     box_set_ctrl_07;	//0xCC8C4ADC
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_08_T                     box_set_ctrl_08;	//0xCC8C4AE0
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_09_T                     box_set_ctrl_09;	//0xCC8C4AE4
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_10_T                     box_set_ctrl_10;	//0xCC8C4AE8
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_11_T                     box_set_ctrl_11;	//0xCC8C4AEC
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_12_T                     box_set_ctrl_12;	//0xCC8C4AF0
	PE_O22_AMG0_HEAD_BOX_SET_CTRL_13_T                     box_set_ctrl_13;	//0xCC8C4AF4
	UINT32                                                    reserved5;	//0xCC8C4AF8
	UINT32                                                    reserved6;	//0xCC8C4AFC
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xCC8C4B00
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xCC8C4B04
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xCC8C4B08
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xCC8C4B0C
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xCC8C4B10
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xCC8C4B14
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xCC8C4B18
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xCC8C4B1C
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xCC8C4B20
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xCC8C4B24
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xCC8C4B28
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xCC8C4B2C
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xCC8C4B30
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xCC8C4B34
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xCC8C4B38
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xCC8C4B3C
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xCC8C4B40
	PE_O22_AMG0_HEAD_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xCC8C4B44
	UINT32                                                    reserved7;	//0xCC8C4B48
	UINT32                                                    reserved8;	//0xCC8C4B4C
	PE_O22_AMG0_HEAD_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xCC8C4B50
	PE_O22_AMG0_HEAD_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xCC8C4B54
	UINT32                                                    reserved9;	//0xCC8C4B58
	UINT32                                                   reserved10;	//0xCC8C4B5C
	PE_O22_AMG0_HEAD_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xCC8C4B60
	PE_O22_AMG0_HEAD_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xCC8C4B64
	PE_O22_AMG0_HEAD_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xCC8C4B68
	PE_O22_AMG0_HEAD_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xCC8C4B6C
	PE_O22_AMG0_HEAD_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xCC8C4B70
	PE_O22_AMG0_HEAD_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xCC8C4B74
	PE_O22_AMG0_HEAD_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xCC8C4B78
	PE_O22_AMG0_HEAD_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xCC8C4B7C
	PE_O22_AMG0_HEAD_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xCC8C4B80
	UINT32                                                   reserved11;	//0xCC8C4B84
	UINT32                                                   reserved12;	//0xCC8C4B88
	UINT32                                                   reserved13;	//0xCC8C4B8C
	UINT32                                                   reserved14;	//0xCC8C4B90
	UINT32                                                   reserved15;	//0xCC8C4B94
	UINT32                                                   reserved16;	//0xCC8C4B98
	UINT32                                                   reserved17;	//0xCC8C4B9C
	UINT32                                                   reserved18;	//0xCC8C4BA0
	UINT32                                                   reserved19;	//0xCC8C4BA4
	UINT32                                                   reserved20;	//0xCC8C4BA8
	UINT32                                                   reserved21;	//0xCC8C4BAC
	UINT32                                                   reserved22;	//0xCC8C4BB0
	UINT32                                                   reserved23;	//0xCC8C4BB4
	UINT32                                                   reserved24;	//0xCC8C4BB8
	UINT32                                                   reserved25;	//0xCC8C4BBC
	UINT32                                                   reserved26;	//0xCC8C4BC0
	UINT32                                                   reserved27;	//0xCC8C4BC4
	UINT32                                                   reserved28;	//0xCC8C4BC8
	UINT32                                                   reserved29;	//0xCC8C4BCC
	UINT32                                                   reserved30;	//0xCC8C4BD0
	UINT32                                                   reserved31;	//0xCC8C4BD4
	UINT32                                                   reserved32;	//0xCC8C4BD8
	UINT32                                                   reserved33;	//0xCC8C4BDC
	UINT32                                                   reserved34;	//0xCC8C4BE0
	UINT32                                                   reserved35;	//0xCC8C4BE4
	UINT32                                                   reserved36;	//0xCC8C4BE8
	UINT32                                                   reserved37;	//0xCC8C4BEC
	UINT32                                                   reserved38;	//0xCC8C4BF0
	UINT32                                                   reserved39;	//0xCC8C4BF4
	UINT32                                                   reserved40;	//0xCC8C4BF8
	UINT32                                                   reserved41;	//0xCC8C4BFC
	UINT32                                                   reserved42;	//0xCC8C4C00
	UINT32                                                   reserved43;	//0xCC8C4C04
	UINT32                                                   reserved44;	//0xCC8C4C08
	UINT32                                                   reserved45;	//0xCC8C4C0C
	UINT32                                                   reserved46;	//0xCC8C4C10
	UINT32                                                   reserved47;	//0xCC8C4C14
	UINT32                                                   reserved48;	//0xCC8C4C18
	UINT32                                                   reserved49;	//0xCC8C4C1C
	PE_O22_AMG0_HEAD_IIR_CTRL_00_T                             iir_ctrl_00;	//0xCC8C4C20
	PE_O22_AMG0_HEAD_IIR_CTRL_01_T                             iir_ctrl_01;	//0xCC8C4C24
	UINT32                                                   reserved50;	//0xCC8C4C28
	UINT32                                                   reserved51;	//0xCC8C4C2C
	PE_O22_AMG0_HEAD_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xCC8C4C30
	PE_O22_AMG0_HEAD_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xCC8C4C34
	PE_O22_AMG0_HEAD_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xCC8C4C38
	UINT32                                                   reserved52;	//0xCC8C4C3C
	UINT32                                                   reserved53;	//0xCC8C4C40
	UINT32                                                   reserved54;	//0xCC8C4C44
	UINT32                                                   reserved55;	//0xCC8C4C48
	UINT32                                                   reserved56;	//0xCC8C4C4C
	UINT32                                                   reserved57;	//0xCC8C4C50
	UINT32                                                   reserved58;	//0xCC8C4C54
	UINT32                                                   reserved59;	//0xCC8C4C58
	UINT32                                                   reserved60;	//0xCC8C4C5C
	UINT32                                                   reserved61;	//0xCC8C4C60
	UINT32                                                   reserved62;	//0xCC8C4C64
	UINT32                                                   reserved63;	//0xCC8C4C68
	UINT32                                                   reserved64;	//0xCC8C4C6C
	UINT32                                                   reserved65;	//0xCC8C4C70
	UINT32                                                   reserved66;	//0xCC8C4C74
	UINT32                                                   reserved67;	//0xCC8C4C78
	UINT32                                                   reserved68;	//0xCC8C4C7C
	UINT32                                                   reserved69;	//0xCC8C4C80
	UINT32                                                   reserved70;	//0xCC8C4C84
	UINT32                                                   reserved71;	//0xCC8C4C88
	UINT32                                                   reserved72;	//0xCC8C4C8C
	UINT32                                                   reserved73;	//0xCC8C4C90
	UINT32                                                   reserved74;	//0xCC8C4C94
	UINT32                                                   reserved75;	//0xCC8C4C98
	UINT32                                                   reserved76;	//0xCC8C4C9C
	UINT32                                                   reserved77;	//0xCC8C4CA0
	UINT32                                                   reserved78;	//0xCC8C4CA4
	UINT32                                                   reserved79;	//0xCC8C4CA8
	UINT32                                                   reserved80;	//0xCC8C4CAC
	UINT32                                                   reserved81;	//0xCC8C4CB0
	UINT32                                                   reserved82;	//0xCC8C4CB4
	UINT32                                                   reserved83;	//0xCC8C4CB8
	UINT32                                                   reserved84;	//0xCC8C4CBC
	PE_O22_AMG0_HEAD_AMG_TOP_STAT_00_T                     amg_top_stat_00;	//0xCC8C4CC0
	PE_O22_AMG0_HEAD_AMG_TOP_STAT_01_T                     amg_top_stat_01;	//0xCC8C4CC4
	PE_O22_AMG0_HEAD_AMG_TOP_STAT_02_T                     amg_top_stat_02;	//0xCC8C4CC8
	PE_O22_AMG0_HEAD_AMG_TOP_STAT_03_T                     amg_top_stat_03;	//0xCC8C4CCC
	PE_O22_AMG0_HEAD_AMG_TOP_STAT_04_T                     amg_top_stat_04;	//0xCC8C4CD0
	PE_O22_AMG0_HEAD_AMG_TOP_STAT_05_T                     amg_top_stat_05;	//0xCC8C4CD4
	PE_O22_AMG0_HEAD_AMG_CORE_STAT_00_T                   amg_core_stat_00;	//0xCC8C4CD8
	PE_O22_AMG0_HEAD_AMG_CORE_STAT_01_T                   amg_core_stat_01;	//0xCC8C4CDC
	PE_O22_AMG0_HEAD_AMG_CORE_STAT_02_T                   amg_core_stat_02;	//0xCC8C4CE0
	PE_O22_AMG0_HEAD_AMG_CORE_STAT_03_T                   amg_core_stat_03;	//0xCC8C4CE4
	PE_O22_AMG0_HEAD_AMG_CORE_STAT_04_T                   amg_core_stat_04;	//0xCC8C4CE8
	UINT32                                                   reserved85;	//0xCC8C4CEC
	PE_O22_AMG0_HEAD_AMG_FSW_CTRL_00_T                     amg_fsw_ctrl_00;	//0xCC8C4CF0
	PE_O22_AMG0_HEAD_AMG_FSW_CTRL_01_T                     amg_fsw_ctrl_01;	//0xCC8C4CF4
	PE_O22_AMG0_HEAD_AMG_FSW_CTRL_02_T                     amg_fsw_ctrl_02;	//0xCC8C4CF8
	PE_O22_AMG0_HEAD_AMG_FSW_CTRL_03_T                     amg_fsw_ctrl_03;	//0xCC8C4CFC
}PE_AMG_HEAD_REG_O22_T;

typedef struct {
	PE_O22_AMG1_BODY_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xCC8C4D20
	PE_O22_AMG1_BODY_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xCC8C4D24
	UINT32                                                    reserved0;	//0xCC8C4D28
	UINT32                                                    reserved1;	//0xCC8C4D2C
	UINT32                                                    reserved2;	//0xCC8C4D30
	UINT32                                                    reserved3;	//0xCC8C4D34
	UINT32                                                    reserved4;	//0xCC8C4D38
	UINT32                                                    reserved5;	//0xCC8C4D3C
	UINT32                                                    reserved6;	//0xCC8C4D40
	UINT32                                                    reserved7;	//0xCC8C4D44
	UINT32                                                    reserved8;	//0xCC8C4D48
	UINT32                                                    reserved9;	//0xCC8C4D4C
	UINT32                                                   reserved10;	//0xCC8C4D50
	UINT32                                                   reserved11;	//0xCC8C4D54
	UINT32                                                   reserved12;	//0xCC8C4D58
	UINT32                                                   reserved13;	//0xCC8C4D5C
	UINT32                                                   reserved14;	//0xCC8C4D60
	UINT32                                                   reserved15;	//0xCC8C4D64
	UINT32                                                   reserved16;	//0xCC8C4D68
	UINT32                                                   reserved17;	//0xCC8C4D6C
	UINT32                                                   reserved18;	//0xCC8C4D70
	UINT32                                                   reserved19;	//0xCC8C4D74
	UINT32                                                   reserved20;	//0xCC8C4D78
	UINT32                                                   reserved21;	//0xCC8C4D7C
	UINT32                                                   reserved22;	//0xCC8C4D80
	UINT32                                                   reserved23;	//0xCC8C4D84
	UINT32                                                   reserved24;	//0xCC8C4D88
	UINT32                                                   reserved25;	//0xCC8C4D8C
	UINT32                                                   reserved26;	//0xCC8C4D90
	UINT32                                                   reserved27;	//0xCC8C4D94
	UINT32                                                   reserved28;	//0xCC8C4D98
	UINT32                                                   reserved29;	//0xCC8C4D9C
	UINT32                                                   reserved30;	//0xCC8C4DA0
	UINT32                                                   reserved31;	//0xCC8C4DA4
	UINT32                                                   reserved32;	//0xCC8C4DA8
	UINT32                                                   reserved33;	//0xCC8C4DAC
	PE_O22_AMG1_BODY_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xCC8C4DB0
	PE_O22_AMG1_BODY_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xCC8C4DB4
	PE_O22_AMG1_BODY_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xCC8C4DB8
	PE_O22_AMG1_BODY_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xCC8C4DBC
	PE_O22_AMG1_BODY_BOX_SET_CTRL_00_T                     box_set_ctrl_00;	//0xCC8C4DC0
	PE_O22_AMG1_BODY_BOX_SET_CTRL_01_T                     box_set_ctrl_01;	//0xCC8C4DC4
	PE_O22_AMG1_BODY_BOX_SET_CTRL_02_T                     box_set_ctrl_02;	//0xCC8C4DC8
	PE_O22_AMG1_BODY_BOX_SET_CTRL_03_T                     box_set_ctrl_03;	//0xCC8C4DCC
	PE_O22_AMG1_BODY_BOX_SET_CTRL_04_T                     box_set_ctrl_04;	//0xCC8C4DD0
	PE_O22_AMG1_BODY_BOX_SET_CTRL_05_T                     box_set_ctrl_05;	//0xCC8C4DD4
	PE_O22_AMG1_BODY_BOX_SET_CTRL_06_T                     box_set_ctrl_06;	//0xCC8C4DD8
	PE_O22_AMG1_BODY_BOX_SET_CTRL_07_T                     box_set_ctrl_07;	//0xCC8C4DDC
	PE_O22_AMG1_BODY_BOX_SET_CTRL_08_T                     box_set_ctrl_08;	//0xCC8C4DE0
	PE_O22_AMG1_BODY_BOX_SET_CTRL_09_T                     box_set_ctrl_09;	//0xCC8C4DE4
	PE_O22_AMG1_BODY_BOX_SET_CTRL_10_T                     box_set_ctrl_10;	//0xCC8C4DE8
	PE_O22_AMG1_BODY_BOX_SET_CTRL_11_T                     box_set_ctrl_11;	//0xCC8C4DEC
	PE_O22_AMG1_BODY_BOX_SET_CTRL_12_T                     box_set_ctrl_12;	//0xCC8C4DF0
	PE_O22_AMG1_BODY_BOX_SET_CTRL_13_T                     box_set_ctrl_13;	//0xCC8C4DF4
	UINT32                                                   reserved34;	//0xCC8C4DF8
	UINT32                                                   reserved35;	//0xCC8C4DFC
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xCC8C4E00
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xCC8C4E04
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xCC8C4E08
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xCC8C4E0C
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xCC8C4E10
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xCC8C4E14
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xCC8C4E18
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xCC8C4E1C
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xCC8C4E20
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xCC8C4E24
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xCC8C4E28
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xCC8C4E2C
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xCC8C4E30
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xCC8C4E34
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xCC8C4E38
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xCC8C4E3C
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xCC8C4E40
	PE_O22_AMG1_BODY_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xCC8C4E44
	UINT32                                                   reserved36;	//0xCC8C4E48
	UINT32                                                   reserved37;	//0xCC8C4E4C
	PE_O22_AMG1_BODY_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xCC8C4E50
	PE_O22_AMG1_BODY_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xCC8C4E54
	UINT32                                                   reserved38;	//0xCC8C4E58
	UINT32                                                   reserved39;	//0xCC8C4E5C
	PE_O22_AMG1_BODY_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xCC8C4E60
	PE_O22_AMG1_BODY_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xCC8C4E64
	PE_O22_AMG1_BODY_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xCC8C4E68
	PE_O22_AMG1_BODY_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xCC8C4E6C
	PE_O22_AMG1_BODY_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xCC8C4E70
	PE_O22_AMG1_BODY_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xCC8C4E74
	PE_O22_AMG1_BODY_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xCC8C4E78
	PE_O22_AMG1_BODY_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xCC8C4E7C
	PE_O22_AMG1_BODY_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xCC8C4E80
	UINT32                                                   reserved40;	//0xCC8C4E84
	UINT32                                                   reserved41;	//0xCC8C4E88
	UINT32                                                   reserved42;	//0xCC8C4E8C
	PE_O22_AMG1_BODY_LUT_DEPTH_CTRL_00_T                 lut_depth_ctrl_00;	//0xCC8C4E90
	PE_O22_AMG1_BODY_LUT_DEPTH_CTRL_01_T                 lut_depth_ctrl_01;	//0xCC8C4E94
	UINT32                                                   reserved43;	//0xCC8C4E98
	UINT32                                                   reserved44;	//0xCC8C4E9C
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_00_T             region_gain_ctrl_00;	//0xCC8C4EA0
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_01_T             region_gain_ctrl_01;	//0xCC8C4EA4
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_02_T             region_gain_ctrl_02;	//0xCC8C4EA8
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_03_T             region_gain_ctrl_03;	//0xCC8C4EAC
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_04_T             region_gain_ctrl_04;	//0xCC8C4EB0
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_05_T             region_gain_ctrl_05;	//0xCC8C4EB4
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_06_T             region_gain_ctrl_06;	//0xCC8C4EB8
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_07_T             region_gain_ctrl_07;	//0xCC8C4EBC
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_08_T             region_gain_ctrl_08;	//0xCC8C4EC0
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_09_T             region_gain_ctrl_09;	//0xCC8C4EC4
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_10_T             region_gain_ctrl_10;	//0xCC8C4EC8
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_11_T             region_gain_ctrl_11;	//0xCC8C4ECC
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_12_T             region_gain_ctrl_12;	//0xCC8C4ED0
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_13_T             region_gain_ctrl_13;	//0xCC8C4ED4
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_14_T             region_gain_ctrl_14;	//0xCC8C4ED8
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_15_T             region_gain_ctrl_15;	//0xCC8C4EDC
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_16_T             region_gain_ctrl_16;	//0xCC8C4EE0
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_17_T             region_gain_ctrl_17;	//0xCC8C4EE4
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_18_T             region_gain_ctrl_18;	//0xCC8C4EE8
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_19_T             region_gain_ctrl_19;	//0xCC8C4EEC
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_20_T             region_gain_ctrl_20;	//0xCC8C4EF0
	PE_O22_AMG1_BODY_REGION_GAIN_CTRL_21_T             region_gain_ctrl_21;	//0xCC8C4EF4
	UINT32                                                   reserved45;	//0xCC8C4EF8
	UINT32                                                   reserved46;	//0xCC8C4EFC
	PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T         lut_depth_iir_ctrl_00;	//0xCC8C4F00
	PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T         lut_depth_iir_ctrl_01;	//0xCC8C4F04
	PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T         lut_depth_iir_ctrl_02;	//0xCC8C4F08
	PE_O22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T         lut_depth_iir_ctrl_03;	//0xCC8C4F0C
	PE_O22_AMG1_BODY_LUT_BLD_CTRL_00_T                     lut_bld_ctrl_00;	//0xCC8C4F10
	PE_O22_AMG1_BODY_LUT_BLD_CTRL_01_T                     lut_bld_ctrl_01;	//0xCC8C4F14
	PE_O22_AMG1_BODY_LUT_BLD_CTRL_02_T                     lut_bld_ctrl_02;	//0xCC8C4F18
	PE_O22_AMG1_BODY_LUT_BLD_CTRL_03_T                     lut_bld_ctrl_03;	//0xCC8C4F1C
	PE_O22_AMG1_BODY_IIR_CTRL_00_T                             iir_ctrl_00;	//0xCC8C4F20
	PE_O22_AMG1_BODY_IIR_CTRL_01_T                             iir_ctrl_01;	//0xCC8C4F24
	UINT32                                                   reserved47;	//0xCC8C4F28
	UINT32                                                   reserved48;	//0xCC8C4F2C
	PE_O22_AMG1_BODY_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xCC8C4F30
	PE_O22_AMG1_BODY_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xCC8C4F34
	PE_O22_AMG1_BODY_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xCC8C4F38
}PE_AMG_BODY_REG_O22_T;
typedef struct {
	UINT32                                                   reserved[21];	//0xCC480480~0xCC4804D0
}PE_OSD_ORD_REG_O22_T;

typedef struct {
	PE_VSD_OBC_M_SC_PIC_INIT_O22_T                                    pic_init;	//0xCC483200
	PE_VSD_OBC_M_SC_PIC_START_O22_T                                  pic_start;	//0xCC483204
	PE_VSD_OBC_M_SC_CTRL_AUTO_INIT_O22_T                        ctrl_auto_init;	//0xCC483208
	PE_VSD_OBC_M_SC_CTRL_INTR_PULSE_O22_T                      ctrl_intr_pulse;	//0xCC48320C
	PE_VSD_OBC_M_SC_INTR_PE_O22_T                                    intr_reg;	//0xCC483210
	PE_VSD_OBC_M_SC_INTR_MASK_O22_T                                  intr_mask;	//0xCC483214
	PE_VSD_OBC_M_SC_INTR_MUX_O22_T                                    intr_mux;	//0xCC483218
	PE_VSD_OBC_M_SC_INTR_EN_O22_T                                      intr_en;	//0xCC48321C
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_00_O22_T          obc_head_l4sc_ctrl_00;	//0xCC483220
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_01_O22_T          obc_head_l4sc_ctrl_01;	//0xCC483224
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_02_O22_T          obc_head_l4sc_ctrl_02;	//0xCC483228
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_03_O22_T          obc_head_l4sc_ctrl_03;	//0xCC48322C
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_04_O22_T          obc_head_l4sc_ctrl_04;	//0xCC483230
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_05_O22_T          obc_head_l4sc_ctrl_05;	//0xCC483234
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_06_O22_T          obc_head_l4sc_ctrl_06;	//0xCC483238
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_07_O22_T          obc_head_l4sc_ctrl_07;	//0xCC48323C
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_08_O22_T          obc_head_l4sc_ctrl_08;	//0xCC483240
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_09_O22_T          obc_head_l4sc_ctrl_09;	//0xCC483244
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_10_O22_T          obc_head_l4sc_ctrl_10;	//0xCC483248
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_11_O22_T          obc_head_l4sc_ctrl_11;	//0xCC48324C
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_12_O22_T          obc_head_l4sc_ctrl_12;	//0xCC483250
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_CTRL_13_O22_T          obc_head_l4sc_ctrl_13;	//0xCC483254
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_STAT_00_O22_T          obc_head_l4sc_stat_00;	//0xCC483258
	PE_VSD_OBC_M_SC_OBC_HEAD_L4SC_STAT_01_O22_T          obc_head_l4sc_stat_01;	//0xCC48325C
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_00_O22_T          obc_body_l4sc_ctrl_00;	//0xCC483260
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_01_O22_T          obc_body_l4sc_ctrl_01;	//0xCC483264
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_02_O22_T          obc_body_l4sc_ctrl_02;	//0xCC483268
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_03_O22_T          obc_body_l4sc_ctrl_03;	//0xCC48326C
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_04_O22_T          obc_body_l4sc_ctrl_04;	//0xCC483270
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_05_O22_T          obc_body_l4sc_ctrl_05;	//0xCC483274
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_06_O22_T          obc_body_l4sc_ctrl_06;	//0xCC483278
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_07_O22_T          obc_body_l4sc_ctrl_07;	//0xCC48327C
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_08_O22_T          obc_body_l4sc_ctrl_08;	//0xCC483280
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_09_O22_T          obc_body_l4sc_ctrl_09;	//0xCC483284
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_10_O22_T          obc_body_l4sc_ctrl_10;	//0xCC483288
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_11_O22_T          obc_body_l4sc_ctrl_11;	//0xCC48328C
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_12_O22_T          obc_body_l4sc_ctrl_12;	//0xCC483290
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_CTRL_13_O22_T          obc_body_l4sc_ctrl_13;	//0xCC483294
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_STAT_00_O22_T          obc_body_l4sc_stat_00;	//0xCC483298
	PE_VSD_OBC_M_SC_OBC_BODY_L4SC_STAT_01_O22_T          obc_body_l4sc_stat_01;	//0xCC48329C
	UINT32                                                    reserved0;	//0xCC4832A0
	UINT32                                                    reserved1;	//0xCC4832A4
	UINT32                                                    reserved2;	//0xCC4832A8
	UINT32                                                    reserved3;	//0xCC4832AC
	PE_VSD_OBC_M_SC_CTRL_BLOCK_O22_T                                ctrl_block;	//0xCC4832B0
	PE_VSD_OBC_M_SC_CTRL_BLOCK1_O22_T                              ctrl_block1;	//0xCC4832B4
	PE_VSD_OBC_M_SC_CTRL_CG_ON_O22_T                                ctrl_cg_on;	//0xCC4832B8
	UINT32                                                    reserved4;	//0xCC4832BC
	PE_VSD_OBC_M_SC_PIC_INIT_G0_TIMER_O22_T                  pic_init_g0_timer;	//0xCC4832C0
	PE_VSD_OBC_M_SC_PIC_INIT_G1_TIMER_O22_T                  pic_init_g1_timer;	//0xCC4832C4
	PE_VSD_OBC_M_SC_PIC_INIT_G2_TIMER_O22_T                  pic_init_g2_timer;	//0xCC4832C8
	PE_VSD_OBC_M_SC_PIC_INIT_G3_TIMER_O22_T                  pic_init_g3_timer;	//0xCC4832CC
	PE_VSD_OBC_M_SC_PIC_INIT_G4_TIMER_O22_T                  pic_init_g4_timer;	//0xCC4832D0
	PE_VSD_OBC_M_SC_PIC_INIT_G5_TIMER_O22_T                  pic_init_g5_timer;	//0xCC4832D4
	PE_VSD_OBC_M_SC_PIC_INIT_G6_TIMER_O22_T                  pic_init_g6_timer;	//0xCC4832D8
	PE_VSD_OBC_M_SC_PIC_INIT_G7_TIMER_O22_T                  pic_init_g7_timer;	//0xCC4832DC
	UINT32                                                    reserved5;	//0xCC4832E0
	PE_VSD_OBC_M_SC_DBG_TIMER_RUN_O22_T                          dbg_timer_run;	//0xCC4832E4
	PE_VSD_OBC_M_SC_GX_PIC_START_END_PROC_O22_T          gx_pic_start_end_proc;	//0xCC4832E8
	PE_VSD_OBC_M_SC_CTRL_MONITOR_O22_T                            ctrl_monitor;	//0xCC4832EC
	PE_VSD_OBC_M_SC_CTRL_PIC_END_O22_T                            ctrl_pic_end;	//0xCC4832F0
	PE_VSD_OBC_M_SC_INFO_PIC_END_O22_T                            info_pic_end;	//0xCC4832F4
	PE_VSD_OBC_M_SC_CTRL_GPIO_O22_T                                  ctrl_gpio;	//0xCC4832F8
	PE_VSD_OBC_M_SC_CTRL_GMAU_O22_T                                  ctrl_gmau;	//0xCC4832FC
}PE_VSD_OBC_M_SC_REG_O22_T;


#endif
