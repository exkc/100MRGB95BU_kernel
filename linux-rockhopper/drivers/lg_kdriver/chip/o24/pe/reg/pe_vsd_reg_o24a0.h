#ifndef _PE_SHP_REG_O24A0_H_
#define _PE_SHP_REG_O24A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22000 RW 0x0019_0021
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
}PE_O24_VSD_SHP_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22004 RW 0x0870_0F00
	UINT32 reg_top_width                    :16;	//(15:0,NA,3840) //processing width (default : 3840)
	UINT32 reg_top_height                   :16;	//(31:16,NA,2160) //processing height (default : 2160)
	};
}PE_O24_VSD_SHP_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22008 RW 0x0118_0002
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,0) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,1) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_VSD_SHP_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2200C RW 0x0000_000A
	UINT32 reg_top_pic_init_latency         :12;	//(11:0,NA,10) //pic init latency
	UINT32 resvd                            :20;
	};
}PE_O24_VSD_SHP_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22010 RW 0x0000_0019
	UINT32 reg_top_update_ctrl              :5;	//(4:0,NA,25) //[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_O24_VSD_SHP_SHP_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22014 RW 0x0E00_0810
	UINT32 reg_new_fd_detail_beta_mul       :8;	//(7:0,NA,16) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_detail_alpha_mul      :8;	//(15:8,NA,8) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_edge_beta_mul         :8;	//(23:16,NA,0) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_new_fd_edge_alpha_mul        :8;	//(31:24,NA,14) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22018 RW 0x60A0_0020
	UINT32 reg_new_fd_edge_minmax_y0        :8;	//(7:0,NA,32) //Final edge LUT, y0
	UINT32 reg_new_fd_edge_minmax_x0        :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_new_fd_edge_minmax_y1        :8;	//(23:16,NA,160) //Final edge LUT, y1
	UINT32 reg_new_fd_edge_minmax_x1        :8;	//(31:24,NA,96) //Final edge LUT, x1
	};
}PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2201C RW 0xFFFF_82DC
	UINT32 reg_new_fd_edge_minmax_y2        :8;	//(7:0,NA,220) //Final edge LUT, y2
	UINT32 reg_new_fd_edge_minmax_x2        :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_new_fd_edge_minmax_y3        :8;	//(23:16,NA,255) //Final edge LUT, y3
	UINT32 reg_new_fd_edge_minmax_x3        :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22020 RW 0x2860_0040
	UINT32 reg_new_fd_detail_minmax_y0      :8;	//(7:0,NA,64) //Final detail LUT, y0
	UINT32 reg_new_fd_detail_minmax_x0      :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_new_fd_detail_minmax_y1      :8;	//(23:16,NA,96) //Final detail LUT, y1
	UINT32 reg_new_fd_detail_minmax_x1      :8;	//(31:24,NA,40) //Final detail LUT, x1
	};
}PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22024 RW 0x64A0_4678
	UINT32 reg_new_fd_detail_minmax_y2      :8;	//(7:0,NA,120) //Final detail LUT, y2
	UINT32 reg_new_fd_detail_minmax_x2      :8;	//(15:8,NA,70) //Final detail LUT, x2
	UINT32 reg_new_fd_detail_minmax_y3      :8;	//(23:16,NA,160) //Final detail LUT, y3
	UINT32 reg_new_fd_detail_minmax_x3      :8;	//(31:24,NA,100) //Final detail LUT, x3
	};
}PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22028 RW 0x0000_0180
	UINT32 reg_texture_region_alpha         :8;	//(7:0,NA,128) //Final detail LUT, y2
	UINT32 reg_region_text_en_aux           :1;	//(8:8,NA,1) //Final detail LUT, y2
	UINT32 reg_obj_shp_en_aux               :1;	//(9:9,NA,0) //Final detail LUT, y2
	UINT32 resvd                            :22;
	};
}PE_O24_VSD_SHP_SHP_TEXT_REGION_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22040 RW 0xFFFF_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //pattern pixel value (Cb)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //pattern pixel value (Cr)
	};
}PE_O24_VSD_SHP_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22050 RW 0x0F00_0020
	UINT32 reg_out_hgos_head_crop_ptr       :13;	//(12:0,NA,32) //output horizontal gos head crop pointer
	UINT32 resvd0                           :3;
	UINT32 reg_out_hgos_tail_crop_ptr       :13;	//(28:16,NA,3840) //output horizontal gos tail crop pointer
	UINT32 resvd1                           :1;
	UINT32 reg_out_hgos_head_en             :1;	//(30:30,NA,0) //output horizontal gos head crop enable
	UINT32 reg_out_hgos_tail_en             :1;	//(31:31,NA,0) //output horizontal gos tail crop enable
	};
}PE_O24_VSD_SHP_SHP_GOS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22060 RW 0x0004_0005
	UINT32 reg_sync_dly_vsync               :16;	//(15:0,NA,5) //v sync (2K
	UINT32 reg_sync_dly_vfp                 :16;	//(31:16,NA,4) //v front porch (2K
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22064 RW 0x0024_0438
	UINT32 reg_sync_dly_va                  :16;	//(15:0,NA,1080) //v active (2K
	UINT32 reg_sync_dly_vbp                 :16;	//(31:16,NA,36) //v back porch (2K
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22068 RW 0x0058_002C
	UINT32 reg_sync_dly_hsync               :16;	//(15:0,NA,44) //h sync (2K
	UINT32 reg_sync_dly_hfp                 :16;	//(31:16,NA,88) //h front porch (2K
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2206C RW 0x0094_0780
	UINT32 reg_sync_dly_ha                  :16;	//(15:0,NA,1920) //h active (2K
	UINT32 reg_sync_dly_hbp                 :16;	//(31:16,NA,148) //h back porch (2K
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22070 RW 0x0000_0060
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
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22074 RW 0x000A_00F3
	UINT32 reg_sync_dly_sync_h_dly          :16;	//(15:0,NA,243) //pixel delay
	UINT32 reg_sync_dly_sync_v_dly          :16;	//(31:16,NA,10) //line delay
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22078 RW 0x0008_0058
	UINT32 reg_sync_dly_cnt_rst_h_value     :16;	//(15:0,NA,88) //disp_pulse_dly Delay
	UINT32 reg_sync_dly_cnt_rst_v_value     :16;	//(31:16,NA,8) //[RO] disp_pulse_dly Counter
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2207C RW 0x000A_00F3
	UINT32 reg_sync_dly_auto_actv_h_dly     :15;	//(14:0,NA,243) //auto actv pixel delay
	UINT32 reg_sync_dly_auto_actv_gen_en    :1;	//(15:15,NA,0) //auto actv gen enable
	UINT32 reg_sync_dly_auto_actv_v_dly     :15;	//(30:16,NA,10) //auto actv line delay
	UINT32 reg_sync_dly_auto_actv_seam_en   :1;	//(31:31,NA,0) //auto actv seam enable
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22080 RW 0x000A_00F3
	UINT32 reg_sync_dly_auto_sync_h_dly     :15;	//(14:0,NA,243) //auto sync pixel delay
	UINT32 reg_sync_dly_auto_sync_gen_en    :1;	//(15:15,NA,0) //auto sync gen enable
	UINT32 reg_sync_dly_auto_sync_v_dly     :15;	//(30:16,NA,10) //auto sync line delay
	UINT32 reg_sync_dly_auto_sync_seam_en   :1;	//(31:31,NA,0) //auto sync seam enable
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22084 RW 0x0000_0000
	UINT32 reg_sync_dly_normal_number       :16;	//(15:0,NA,0) //protection mode
	UINT32 resvd                            :16;
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22088 RW 0x0000_0000
	UINT32 reg_sync_dly_cnt_h_rst_position  :16;	//(15:0,NA,0) //manual cnt h value position
	UINT32 reg_sync_dly_cnt_v_rst_position  :16;	//(31:16,NA,0) //manual cnt v value position
	};
}PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22090 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0) //ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0) //ROI mask pixel value (Y)
	UINT32 reg_roi_mask_pix_val_cb          :8;	//(23:16,NA,0) //ROI mask pixel value (Cb)
	UINT32 reg_roi_mask_pix_val_cr          :8;	//(31:24,NA,0) //ROI mask pixel value (Cr)
	};
}PE_O24_VSD_SHP_SHP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22094 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :12;	//(11:0,NA,0) //ROI mask window start position, x0
	UINT32 resvd0                           :4;
	UINT32 reg_roi_mask_win_y0              :12;	//(27:16,NA,0) //ROI mask window start position, y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22098 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :12;	//(11:0,NA,0) //ROI mask window end position, x1
	UINT32 resvd0                           :4;
	UINT32 reg_roi_mask_win_y1              :12;	//(27:16,NA,0) //ROI mask window end position, y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220A0 RW 0x0000_0010
	UINT32 reg_esf_detour_mode              :1;	//(0:0,NA,0) //edge shift filter detour enable
	UINT32 reg_esf_buffer_detour_en         :1;	//(1:1,NA,0) //edge shift filter buffer detour enable
	UINT32 resvd0                           :2;
	UINT32 reg_esf_en                       :1;	//(4:4,NA,1) //edge shift filter enable
	UINT32 resvd1                           :3;
	UINT32 reg_esf_dbg_en                   :1;	//(8:8,NA,0) //edge shift filter debug enable
	UINT32 resvd2                           :23;
	};
}PE_O24_VSD_SHP_SHP_ESF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220A4 RW 0x4040_C814
	UINT32 reg_esf_min_ratio                :8;	//(7:0,NA,20) //edge shift filter min ratio
	UINT32 reg_esf_base                     :8;	//(15:8,NA,200) //edge shift filter base
	UINT32 reg_esf_max_clip                 :8;	//(23:16,NA,64) //edge shift filter max clipping
	UINT32 reg_esf_master_gain              :8;	//(31:24,NA,64) //edge shift filter master gain
	};
}PE_O24_VSD_SHP_SHP_ESF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220A8 RW 0x0000_0819
	UINT32 reg_esf_ltv_offset               :8;	//(7:0,NA,25) //edge shift filter ltv offset
	UINT32 reg_esf_ltv_mul                  :8;	//(15:8,NA,8) //edge shift filter ltv mul
	UINT32 resvd                            :16;
	};
}PE_O24_VSD_SHP_SHP_ESF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220B0 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220B4 RW 0x0000_0000
	UINT32 reg_win_esf_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220B8 RW 0x086F_0EFF
	UINT32 reg_win_esf_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220BC RW 0x0000_0000
	UINT32 reg_win_esf_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220C0 RW 0x086F_0EFF
	UINT32 reg_win_esf_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_esf_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA220F0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :4;	//(3:0,NA,0) //0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: luma_adaptive gain	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map	1011: Gain A-map	1100: Gain T-map	1101: Texture region map	1110: object map	1111: face map
	UINT32 reg_dp_detour_en                 :1;	//(4:4,NA,0) //dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(8:8,NA,0) //dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_O24_VSD_SHP_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22100 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22104 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22108 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2210C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22110 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22114 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22118 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2211C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22120 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22124 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22128 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2212C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //MNR gain for edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //MNR gain for texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22130 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22134 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22138 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2213C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22140 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22144 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22148 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2214C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22150 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22154 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22158 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O24_VSD_SHP_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22160 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22164 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22168 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2216C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22170 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22174 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22178 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2217C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22180 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22184 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //level-balancing, lum2_y0
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22188 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2218C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22190 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22194 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_O24_VSD_SHP_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221A0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 resvd                            :7;
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //local gain
	};
}PE_O24_VSD_SHP_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221A4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //gain balancing, x1
	};
}PE_O24_VSD_SHP_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221A8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //gain balancing, x3
	};
}PE_O24_VSD_SHP_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221AC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221B0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221C0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221C4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //edge_Y_filter en
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221C8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221CC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221D8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221DC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221E0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221E4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221E8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221EC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221F0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221F4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221F8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA221FC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //level-balancing, lum1_x_H1
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22200 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //level-balancing, lum2_x_L0
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22204 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //level-balancing, lum2_y0
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22208 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2220C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22210 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22220 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O24_VSD_SHP_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22224 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //master gain
	UINT32 resvd2                           :16;
	};
}PE_O24_VSD_SHP_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22228 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2222C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22230 RW 0x1010_2014
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
}PE_O24_VSD_SHP_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22240 RW 0x8000_0011
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
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22244 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //
	UINT32 resvd3                           :5;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22248 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//(21:16,NA,63) //
	UINT32 resvd1                           :10;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2224C RW 0x0000_48AB
	UINT32 reg_tgen_rand_init_val_c0        :32;	//(31:0,NA,18603) //
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22250 RW 0x0000_48AB
	UINT32 reg_tgen_rand_init_val_c1        :32;	//(31:0,NA,18603) //
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22254 RW 0x0202_1F04
	UINT32 reg_tgen_dr_ratio                :3;	//(2:0,NA,4) //
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//(13:8,NA,31) //
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //
	UINT32 resvd3                           :6;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22258 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //
	UINT32 resvd2                           :3;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2225C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22260 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //
	UINT32 resvd2                           :2;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22264 RW 0x3F80_1F1F
	UINT32 reg_tgen_map_edge_gain           :5;	//(4:0,NA,31) //
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//(12:8,NA,31) //
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//(23:16,NA,128) //
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //
	UINT32 resvd2                           :2;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22268 RW 0x48AB_CDFF
	UINT32 reg_tgen_gain7                   :4;	//(3:0,NA,15) //
	UINT32 reg_tgen_gain6                   :4;	//(7:4,NA,15) //
	UINT32 reg_tgen_gain5                   :4;	//(11:8,NA,13) //
	UINT32 reg_tgen_gain4                   :4;	//(15:12,NA,12) //
	UINT32 reg_tgen_gain3                   :4;	//(19:16,NA,11) //
	UINT32 reg_tgen_gain2                   :4;	//(23:20,NA,10) //
	UINT32 reg_tgen_gain1                   :4;	//(27:24,NA,8) //
	UINT32 reg_tgen_gain0                   :4;	//(31:28,NA,4) //
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2226C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22270 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22274 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O24_VSD_SHP_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22280 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22284 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22288 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2228C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22290 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22294 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22298 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2229C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222A0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222A4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222A8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222AC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222B0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222B4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222B8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222BC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222C0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222C4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222C8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222CC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222D0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222D4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222D8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222DC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222E0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222E4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222E8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222EC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222F0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222F4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222F8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dtcp_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA222FC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22300 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22304 RW 0x0000_159C
	UINT32 reg_nntg_lsfr_init_1st_c0        :32;	//(31:0,NA,5532) //4K nano-noise LSFR init (1st)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22308 RW 0x2CA3_7199
	UINT32 reg_nntg_lsfr_init_2nd_c0        :32;	//(31:0,NA,748908953) //4K nano-noise LSFR init (2nd)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2230C RW 0x3236_3B62
	UINT32 reg_nntg_lsfr_init_3rd_c0        :32;	//(31:0,NA,842414946) //4K nano-noise LSFR init (3rd)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22310 RW 0xFD1C_D00A
	UINT32 reg_nntg_lsfr_init_4th_c0        :32;	//(31:0,NA,4246523914) //4K nano-noise LSFR init (4th)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22314 RW 0x8C3C_2327
	UINT32 reg_nntg_lsfr_init_5th_c0        :32;	//(31:0,NA,2352751399) //4K nano-noise LSFR init (5th)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22318 RW 0xF275_9828
	UINT32 reg_nntg_lsfr_init_1st_c1        :32;	//(31:0,NA,4067792936) //4K nano-noise LSFR init (1st)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2231C RW 0xFEEA_5094
	UINT32 reg_nntg_lsfr_init_2nd_c1        :32;	//(31:0,NA,4276768916) //4K nano-noise LSFR init (2nd)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22320 RW 0xECBE_ACAA
	UINT32 reg_nntg_lsfr_init_3rd_c1        :32;	//(31:0,NA,3971919018) //4K nano-noise LSFR init (3rd)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22324 RW 0xD9C5_DFEA
	UINT32 reg_nntg_lsfr_init_4th_c1        :32;	//(31:0,NA,3653623786) //4K nano-noise LSFR init (4th)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22328 RW 0x23E8_D99E
	UINT32 reg_nntg_lsfr_init_5th_c1        :32;	//(31:0,NA,602462622) //4K nano-noise LSFR init (5th)
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2232C RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio              :8;	//(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22330 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00           :4;	//(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22334 RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20           :4;	//(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22338 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10           :4;	//(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2233C RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0             :8;	//(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22340 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2             :8;	//(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22344 RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0             :8;	//(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22348 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2             :8;	//(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2234C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22350 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22354 RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b         :7;	//(6:0,NA,0) //edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//(14:8,NA,0) //edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//(22:16,NA,16) //texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//(30:24,NA,16) //texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22360 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22364 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //dp_sum LUT for delta control, x1
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22368 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //dp_sum LUT for delta control, x3
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2236C RW 0x4080_0070
	UINT32 reg_obj_dct_delta_lut_y0         :8;	//(7:0,NA,112) //object dct LUT for delta control, y0
	UINT32 reg_obj_dct_delta_lut_x0         :8;	//(15:8,NA,0) //object dct LUT for delta control, x0
	UINT32 reg_obj_dct_delta_lut_y1         :8;	//(23:16,NA,128) //object dct LUT for delta control, y1
	UINT32 reg_obj_dct_delta_lut_x1         :8;	//(31:24,NA,64) //object dct LUT for delta control, x1
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22370 RW 0xffa0_6090
	UINT32 reg_obj_dct_delta_lut_y2         :8;	//(7:0,NA,144) //object dct LUT for delta control, y2
	UINT32 reg_obj_dct_delta_lut_x2         :8;	//(15:8,NA,96) //object dct LUT for delta control, x2
	UINT32 reg_obj_dct_delta_lut_y3         :8;	//(23:16,NA,160) //object dct LUT for delta control, y3
	UINT32 reg_obj_dct_delta_lut_x3         :8;	//(31:24,NA,255) //object dct LUT for delta control, x3
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22374 RW 0x4080_0070
	UINT32 reg_obj_tgen_delta_lut_y0        :8;	//(7:0,NA,112) //object tgen LUT for delta control, y0
	UINT32 reg_obj_tgen_delta_lut_x0        :8;	//(15:8,NA,0) //object tgen LUT for delta control, x0
	UINT32 reg_obj_tgen_delta_lut_y1        :8;	//(23:16,NA,128) //object tgen LUT for delta control, y1
	UINT32 reg_obj_tgen_delta_lut_x1        :8;	//(31:24,NA,64) //object tgen LUT for delta control, x1
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22378 RW 0xffb0_6090
	UINT32 reg_obj_tgen_delta_lut_y2        :8;	//(7:0,NA,144) //object tgen LUT for delta control, y2
	UINT32 reg_obj_tgen_delta_lut_x2        :8;	//(15:8,NA,96) //object tgen LUT for delta control, x2
	UINT32 reg_obj_tgen_delta_lut_y3        :8;	//(23:16,NA,176) //object tgen LUT for delta control, y3
	UINT32 reg_obj_tgen_delta_lut_x3        :8;	//(31:24,NA,255) //object tgen LUT for delta control, x3
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2237C RW 0x4080_0070
	UINT32 reg_obj_lc_delta_lut_y0          :8;	//(7:0,NA,112) //object local contrast LUT for delta control, y0
	UINT32 reg_obj_lc_delta_lut_x0          :8;	//(15:8,NA,0) //object local contrast LUT for delta control, x0
	UINT32 reg_obj_lc_delta_lut_y1          :8;	//(23:16,NA,128) //object local contrast LUT for delta control, y1
	UINT32 reg_obj_lc_delta_lut_x1          :8;	//(31:24,NA,64) //object local contrast LUT for delta control, x1
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22380 RW 0xffa0_6090
	UINT32 reg_obj_lc_delta_lut_y2          :8;	//(7:0,NA,144) //object local contrast LUT for delta control, y2
	UINT32 reg_obj_lc_delta_lut_x2          :8;	//(15:8,NA,96) //object local contrast LUT for delta control, x2
	UINT32 reg_obj_lc_delta_lut_y3          :8;	//(23:16,NA,160) //object local contrast LUT for delta control, y3
	UINT32 reg_obj_lc_delta_lut_x3          :8;	//(31:24,NA,255) //object local contrast LUT for delta control, x3
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22384 RW 0x2828_0000
	UINT32 reg_dp_sum_cg_lut_y0             :8;	//(7:0,NA,0) //dp_sum LUT for delta_cg control, y0
	UINT32 reg_dp_sum_cg_lut_x0             :8;	//(15:8,NA,0) //dp_sum LUT for delta_cg control, x0
	UINT32 reg_dp_sum_cg_lut_y1             :8;	//(23:16,NA,40) //dp_sum LUT for delta_cg control, y1
	UINT32 reg_dp_sum_cg_lut_x1             :8;	//(31:24,NA,40) //dp_sum LUT for delta_cg control, x1
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22388 RW 0xFFFF_5050
	UINT32 reg_dp_sum_cg_lut_y2             :8;	//(7:0,NA,80) //dp_sum LUT for delta_cg control, y2
	UINT32 reg_dp_sum_cg_lut_x2             :8;	//(15:8,NA,80) //dp_sum LUT for delta_cg control, x2
	UINT32 reg_dp_sum_cg_lut_y3             :8;	//(23:16,NA,255) //dp_sum LUT for delta_cg control, y3
	UINT32 reg_dp_sum_cg_lut_x3             :8;	//(31:24,NA,255) //dp_sum LUT for delta_cg control, x3
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22390 RW 0x0000_0001
	UINT32 reg_psp_obj_en                   :1;	//(0:0,NA,1) //PSP object contrast enable
	UINT32 resvd                            :31;
	};
}PE_O24_VSD_SHP_SHP_PSP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22394 RW 0x2828_0000
	UINT32 reg_dp_sum_obj_lut_y0            :8;	//(7:0,NA,0) //dp_sum LUT for object control, y0
	UINT32 reg_dp_sum_obj_lut_x0            :8;	//(15:8,NA,0) //dp_sum LUT for object control, x0
	UINT32 reg_dp_sum_obj_lut_y1            :8;	//(23:16,NA,40) //dp_sum LUT for object control, y1
	UINT32 reg_dp_sum_obj_lut_x1            :8;	//(31:24,NA,40) //dp_sum LUT for object control, x1
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22398 RW 0xFFFF_5050
	UINT32 reg_dp_sum_obj_lut_y2            :8;	//(7:0,NA,80) //dp_sum LUT for object control, y2
	UINT32 reg_dp_sum_obj_lut_x2            :8;	//(15:8,NA,80) //dp_sum LUT for object control, x2
	UINT32 reg_dp_sum_obj_lut_y3            :8;	//(23:16,NA,255) //dp_sum LUT for object control, y3
	UINT32 reg_dp_sum_obj_lut_x3            :8;	//(31:24,NA,255) //dp_sum LUT for object control, x3
	};
}PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223A0 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223A8 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w0_x1             :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223B0 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w1_x1             :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223C0 RW 0x0432_0c40
	UINT32 reg_region_text_en               :1;	//(0:0,NA,0) //region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//(6:4,NA,4) //
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//(15:8,NA,12) //
	UINT32 reg_region_text_add_max          :8;	//(23:16,NA,50) //
	UINT32 reg_region_text_cuthif           :3;	//(26:24,NA,4) //
	UINT32 resvd2                           :5;
	};
}PE_O24_VSD_SHP_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223C4 RW 0x0f50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //region texture LUT , x1
	};
}PE_O24_VSD_SHP_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223C8 RW 0x46c8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //region texture LUT , x3
	};
}PE_O24_VSD_SHP_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223CC RW 0x0000_ff00
	UINT32 reg_tmap_temp_iir_en             :1;	//(0:0,NA,0) //TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//(4:4,NA,0) //TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//(15:8,NA,255) //TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//(24:24,NA,0) //TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223D0 RW 0x2840_0a00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //tmap temporal previous blend LUT , x1
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223D4 RW 0x5080_3c60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //tmap temporal previous blend LUT , x3
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223D8 RW 0x08d0_00c0
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir positive LUT , x1
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223DC RW 0x30f0_10e0
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //tmap temporal iir positive LUT , x3
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223E0 RW 0x80c0_60d0
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //tmap temporal iir positive LUT , x5
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223E4 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //tmap temporal iir negative LUT , x1
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223E8 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //tmap temporal iir negative LUT , x3
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223EC RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //tmap temporal iir negative LUT , x5
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223F0 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x       :12;	//(11:0,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223F4 RW 0x086f_077f
	UINT32 reg_tmap_stat_win0_end_x         :12;	//(11:0,NA,1919) //tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//(27:16,NA,2159) //tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223F8 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x       :12;	//(11:0,NA,1920) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//(27:16,NA,0) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA223FC RW 0x0438_0eff
	UINT32 reg_tmap_stat_win1_end_x         :12;	//(11:0,NA,3839) //tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//(27:16,NA,1080) //tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22400 RW 0x8010_0179
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22404 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22408 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//(12:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2240C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //edge adaptive filter multiplication value
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22410 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22414 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22418 RW 0x0000_0040
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2241C RW 0x0015_5550
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22420 RW 0x0000_0040
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22424 RW 0x002A_A040
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22428 RW 0x002A_A040
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2242C RW 0x000A_A040
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22430 RW 0x0000_00E4
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22434 RW 0x0000_5540
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22438 RW 0x0020_5542
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2243C RW 0x0008_1508
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22440 RW 0x0002_0420
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22444 RW 0x0000_8080
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22448 RW 0x0000_2A00
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2244C RW 0x0000_2A00
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22450 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22454 RW 0x0000_2800
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22458 RW 0x0005_0A00
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2245C RW 0x0005_4280
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22460 RW 0x0005_50A0
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22464 RW 0x0005_4280
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22468 RW 0x0005_0A00
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2246C RW 0x0000_2800
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
}PE_O24_VSD_SHP_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22470 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22474 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22478 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2247C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22480 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O24_VSD_SHP_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22490 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22494 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224A0 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224A8 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w0_x1             :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224B0 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w1_x1             :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224BC RW 0x10BC_4DB3
	UINT32 reg_dj_text_gain_mmd_mul         :8;	//(7:0,NA,10) //DJ control register
	UINT32 reg_dj_text_gain_avg_mul         :8;	//(15:8,NA,20) //DJ control register
	UINT32 reg_dj_text_gain_threshold       :10;	//(25:16,NA,100) //DJ control register
	UINT32 reg_dj_text_gain_all_text_flag   :1;	//(26:26,NA,0) //DJ control register
	UINT32 resvd0                           :1;
	UINT32 reg_dj_text_gain_en              :1;	//(28:28,NA,1) //DJ control register
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224C0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir0_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir0_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir0_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224C4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir0_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir0_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir0_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir0_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224C8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir1_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir1_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir1_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224CC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir1_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir1_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir1_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir1_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224D0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir3_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir3_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir3_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224D4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir3_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir3_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir3_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir3_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224D8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir5_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir5_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir5_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224DC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir5_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir5_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir5_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir5_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224E0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir6_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir6_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir6_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224E4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir6_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir6_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir6_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir6_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224E8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir7_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir7_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir7_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224EC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir7_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir7_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir7_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir7_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224F0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir9_y0         :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x0         :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir9_y1         :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir9_x1         :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224F4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir9_y2         :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir9_x2         :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir9_y3         :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir9_x3         :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224F8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir11_y0        :8;	//(7:0,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x0        :8;	//(15:8,NA,0) //DJ control register
	UINT32 reg_dj_text_gain_dir11_y1        :8;	//(23:16,NA,192) //DJ control register
	UINT32 reg_dj_text_gain_dir11_x1        :8;	//(31:24,NA,0) //DJ control register
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA224FC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir11_y2        :8;	//(7:0,NA,32) //Final dj_text_gain LUT, y2
	UINT32 reg_dj_text_gain_dir11_x2        :8;	//(15:8,NA,128) //Final dj_text_gain LUT, x2
	UINT32 reg_dj_text_gain_dir11_y3        :8;	//(23:16,NA,32) //Final dj_text_gain LUT, y3
	UINT32 reg_dj_text_gain_dir11_x3        :8;	//(31:24,NA,128) //Final dj_text_gain LUT, x3
	};
}PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22500 RW 0x0000_0000
	UINT32 reg_color_region_en              :1;	//(0:0,NA,0) //color region processing enable
	UINT32 reg_color_region_debug_en        :1;	//(1:1,NA,0) //color region debug map enable
	UINT32 resvd0                           :2;
	UINT32 reg_chr_protection_en            :1;	//(4:4,NA,0) //chroma protection enable
	UINT32 resvd1                           :3;
	UINT32 reg_chr_compensation_en          :1;	//(8:8,NA,0) //chroma compensation enable
	UINT32 resvd2                           :23;
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22504 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22508 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2250C RW 0x28FF_1400
	UINT32 reg_chr_gain_r0_cb_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R0, Cb, y0
	UINT32 reg_chr_gain_r0_cb_x0            :8;	//(15:8,NA,20) //chroma gain LUT, R0, Cb, x0
	UINT32 reg_chr_gain_r0_cb_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R0, Cb, y1
	UINT32 reg_chr_gain_r0_cb_x1            :8;	//(31:24,NA,40) //chroma gain LUT, R0, Cb, x1
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22510 RW 0x7800_64FF
	UINT32 reg_chr_gain_r0_cb_y2            :8;	//(7:0,NA,255) //chroma gain LUT, R0, Cb, y2
	UINT32 reg_chr_gain_r0_cb_x2            :8;	//(15:8,NA,100) //chroma gain LUT, R0, Cb, x2
	UINT32 reg_chr_gain_r0_cb_y3            :8;	//(23:16,NA,0) //chroma gain LUT, R0, Cb, y3
	UINT32 reg_chr_gain_r0_cb_x3            :8;	//(31:24,NA,120) //chroma gain LUT, R0, Cb, x3
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22514 RW 0x96FF_8200
	UINT32 reg_chr_gain_r0_cr_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R0, Cr, y0
	UINT32 reg_chr_gain_r0_cr_x0            :8;	//(15:8,NA,130) //chroma gain LUT, R0, Cr, x0
	UINT32 reg_chr_gain_r0_cr_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R0, Cr, y1
	UINT32 reg_chr_gain_r0_cr_x1            :8;	//(31:24,NA,150) //chroma gain LUT, R0, Cr, x1
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22518 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r0_cr_y2            :8;	//(7:0,NA,200) //chroma gain LUT, R0, Cr, y2
	UINT32 reg_chr_gain_r0_cr_x2            :8;	//(15:8,NA,255) //chroma gain LUT, R0, Cr, x2
	UINT32 reg_chr_gain_r0_cr_y3            :8;	//(23:16,NA,240) //chroma gain LUT, R0, Cr, y3
	UINT32 reg_chr_gain_r0_cr_x3            :8;	//(31:24,NA,0) //chroma gain LUT, R0, Cr, x3
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2251C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22520 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22524 RW 0x96FF_8200
	UINT32 reg_chr_gain_r1_cb_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R1, Cb, y0
	UINT32 reg_chr_gain_r1_cb_x0            :8;	//(15:8,NA,130) //chroma gain LUT, R1, Cb, x0
	UINT32 reg_chr_gain_r1_cb_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R1, Cb, y1
	UINT32 reg_chr_gain_r1_cb_x1            :8;	//(31:24,NA,150) //chroma gain LUT, R1, Cb, x1
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22528 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r1_cb_y2            :8;	//(7:0,NA,200) //chroma gain LUT, R1, Cb, y2
	UINT32 reg_chr_gain_r1_cb_x2            :8;	//(15:8,NA,255) //chroma gain LUT, R1, Cb, x2
	UINT32 reg_chr_gain_r1_cb_y3            :8;	//(23:16,NA,240) //chroma gain LUT, R1, Cb, y3
	UINT32 reg_chr_gain_r1_cb_x3            :8;	//(31:24,NA,0) //chroma gain LUT, R1, Cb, x3
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2252C RW 0x28FF_1400
	UINT32 reg_chr_gain_r1_cr_y0            :8;	//(7:0,NA,0) //chroma gain LUT, R1, Cr, y0
	UINT32 reg_chr_gain_r1_cr_x0            :8;	//(15:8,NA,20) //chroma gain LUT, R1, Cr, x0
	UINT32 reg_chr_gain_r1_cr_y1            :8;	//(23:16,NA,255) //chroma gain LUT, R1, Cr, y1
	UINT32 reg_chr_gain_r1_cr_x1            :8;	//(31:24,NA,40) //chroma gain LUT, R1, Cr, x1
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22530 RW 0x7800_64FF
	UINT32 reg_chr_gain_r1_cr_y2            :8;	//(7:0,NA,255) //chroma gain LUT, R1, Cr, y2
	UINT32 reg_chr_gain_r1_cr_x2            :8;	//(15:8,NA,100) //chroma gain LUT, R1, Cr, x2
	UINT32 reg_chr_gain_r1_cr_y3            :8;	//(23:16,NA,0) //chroma gain LUT, R1, Cr, y3
	UINT32 reg_chr_gain_r1_cr_x3            :8;	//(31:24,NA,120) //chroma gain LUT, R1, Cr, x3
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22534 RW 0x00FF_0000
	UINT32 reg_chr_gain_r0_gain             :8;	//(7:0,NA,0) //chroma gain alpha, R0
	UINT32 resvd0                           :8;
	UINT32 reg_chr_gain_r1_gain             :8;	//(23:16,NA,255) //chroma gain alpha, R1
	UINT32 reg_chr_gain_sel                 :1;	//(24:24,NA,0) //0: {3'd0,region_gain}	1: {region_gain,3'd0}
	UINT32 resvd1                           :7;
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22538 RW 0x28FF_1400
	UINT32 reg_chr_comp_y0                  :8;	//(7:0,NA,0) //chroma comp. linear mapping, y0
	UINT32 reg_chr_comp_x0                  :8;	//(15:8,NA,20) //chroma comp. linear mapping, x0
	UINT32 reg_chr_comp_y1                  :8;	//(23:16,NA,255) //chroma comp. linear mapping, y1
	UINT32 reg_chr_comp_x1                  :8;	//(31:24,NA,40) //chroma comp. linear mapping, x1
	};
}PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22550 RW 0x0000_2A60
	UINT32 reg_cti_en                       :1;	//(0:0,NA,0) //cti enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_filter_tap_size          :3;	//(6:4,NA,6) //000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_gain                     :8;	//(15:8,NA,42) //gain (3.5u)
	UINT32 resvd2                           :16;
	};
}PE_O24_VSD_SHP_SHP_CTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22554 RW 0x0001_1810
	UINT32 reg_cti_coring_th0               :8;	//(7:0,NA,16) //coring th0
	UINT32 reg_cti_coring_th1               :8;	//(15:8,NA,24) //coring_th1
	UINT32 reg_cti_coring_map_filter        :3;	//(18:16,NA,1) //000: no filtering	001: 5-tap filtering	010: 7-tap filtering	011: 9-tap filtering	100: 11-tap filtering	101: 13-tap filtering
	UINT32 resvd0                           :1;
	UINT32 reg_cti_coring_tap_size          :3;	//(22:20,NA,0) //000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_debug_mode               :2;	//(25:24,NA,0) //00: normal display	10: coring_map(cb)	11: coring_map(cr)
	UINT32 resvd2                           :6;
	};
}PE_O24_VSD_SHP_SHP_CTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22558 RW 0x0088_0850
	UINT32 reg_cti_ycm_en                   :1;	//(0:0,NA,0) //y/c merge enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_ycm_band_sel             :3;	//(6:4,NA,5) //y/c merge band sel
	UINT32 resvd1                           :1;
	UINT32 reg_cti_ycm_diff_th              :8;	//(15:8,NA,8) //y/c merge diff threshold
	UINT32 reg_cti_ycm_y_gain               :4;	//(19:16,NA,8) //y/c merge gain, Y
	UINT32 reg_cti_ycm_c_gain               :4;	//(23:20,NA,8) //y/c merge gain, C
	UINT32 resvd2                           :8;
	};
}PE_O24_VSD_SHP_SHP_CTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22560 RW 0x0000_0000
	UINT32 reg_flick_en                     :1;	//(0:0,NA,0) //frc flicker blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_flick_motion_sel             :2;	//(5:4,NA,0) //SHP FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1                           :2;
	UINT32 reg_flick_blur_type              :2;	//(9:8,NA,0) //frc flicker blur pel selection	0: cur pel[y][x+1]	1: cur pel[y][x-1]	2: average
	UINT32 resvd2                           :22;
	};
}PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22564 RW 0x2040_0000
	UINT32 reg_flick_motion_lut_y0          :8;	//(7:0,NA,0) //frc flicker blur motion LUT point, y0
	UINT32 reg_flick_motion_lut_x0          :8;	//(15:8,NA,0) //frc flicker blur motion LUT point, x0
	UINT32 reg_flick_motion_lut_y1          :8;	//(23:16,NA,64) //frc flicker blur motion LUT point, y1
	UINT32 reg_flick_motion_lut_x1          :8;	//(31:24,NA,32) //frc flicker blur motion LUT point, x1
	};
}PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22568 RW 0x80FF_4080
	UINT32 reg_flick_motion_lut_y2          :8;	//(7:0,NA,128) //frcflicker blur motion LUT point, y2
	UINT32 reg_flick_motion_lut_x2          :8;	//(15:8,NA,64) //frc flicker blur motion LUT point, x2
	UINT32 reg_flick_motion_lut_y3          :8;	//(23:16,NA,255) //frc flicker blur motion LUT point, y3
	UINT32 reg_flick_motion_lut_x3          :8;	//(31:24,NA,128) //frc flicker blur motion LUT point, x3
	};
}PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2256C RW 0x0000_0080
	UINT32 reg_flick_master_gain            :8;	//(7:0,NA,128) //frc flicker blur master gain
	UINT32 resvd                            :24;
	};
}PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22570 RW 0x0000_0000
	UINT32 reg_force_block_en               :1;	//(0:0,NA,0) //frc blur weight smoothing count threshold, 0
	UINT32 resvd0                           :15;
	UINT32 reg_block_no_v                   :7;	//(22:16,NA,0) //frc blur weight smoothing count threshold, 2
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_h                   :7;	//(30:24,NA,0) //frc blur weight smoothing count threshold, 3
	UINT32 resvd2                           :1;
	};
}PE_O24_VSD_SHP_SHP_TEMPORAL_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22574 RW 0x1812_0C06
	UINT32 reg_block_size_v                 :7;	//(6:0,NA,0) //frc blur weight smoothing count threshold, 0
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,NA,0) //frc blur weight smoothing count threshold, 1
	UINT32 resvd1                           :1;
	UINT32 reg_last_block_size_v            :7;	//(22:16,NA,0) //frc blur weight smoothing count threshold, 2
	UINT32 resvd2                           :1;
	UINT32 reg_last_block_size_h            :7;	//(30:24,NA,0) //frc blur weight smoothing count threshold, 3
	UINT32 resvd3                           :1;
	};
}PE_O24_VSD_SHP_SHP_TEMPORAL_MAP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22578 RW 0x302A_241E
	UINT32 reg_frc_blur_cnt_th4             :6;	//(5:0,NA,30) //frc blur weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th5             :6;	//(13:8,NA,36) //frc blur weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th6             :6;	//(21:16,NA,42) //frc blur weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th7             :6;	//(29:24,NA,48) //frc blur weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2257C RW 0x8765_4321
	UINT32 reg_frc_blur_val0                :4;	//(3:0,NA,1) //frc blur weight smoothing count value, 0
	UINT32 reg_frc_blur_val1                :4;	//(7:4,NA,2) //frc blur weight smoothing count value, 1
	UINT32 reg_frc_blur_val2                :4;	//(11:8,NA,3) //frc blur weight smoothing count value, 2
	UINT32 reg_frc_blur_val3                :4;	//(15:12,NA,4) //frc blur weight smoothing count value, 3
	UINT32 reg_frc_blur_val4                :4;	//(19:16,NA,5) //frc blur weight smoothing count value, 4
	UINT32 reg_frc_blur_val5                :4;	//(23:20,NA,6) //frc blur weight smoothing count value, 5
	UINT32 reg_frc_blur_val6                :4;	//(27:24,NA,7) //frc blur weight smoothing count value, 6
	UINT32 reg_frc_blur_val7                :4;	//(31:28,NA,8) //frc blur weight smoothing count value, 7
	};
}PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22580 RW 0x0000_0004
	UINT32 reg_frc_blur_coef_x8             :4;	//(3:0,NA,4) //frc blur filter coeff, x, [8]
	UINT32 resvd                            :28;
	};
}PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22584 RW 0x4444_4433
	UINT32 reg_frc_blur_coef_x0             :4;	//(3:0,NA,3) //frc blur filter coeff, x, [0]/[16]
	UINT32 reg_frc_blur_coef_x1             :4;	//(7:4,NA,3) //frc blur filter coeff, x, [1]/[15]
	UINT32 reg_frc_blur_coef_x2             :4;	//(11:8,NA,4) //frc blur filter coeff, x, [2]/[14]
	UINT32 reg_frc_blur_coef_x3             :4;	//(15:12,NA,4) //frc blur filter coeff, x, [3]/[13]
	UINT32 reg_frc_blur_coef_x4             :4;	//(19:16,NA,4) //frc blur filter coeff, x, [4]/[12]
	UINT32 reg_frc_blur_coef_x5             :4;	//(23:20,NA,4) //frc blur filter coeff, x, [5]/[11]
	UINT32 reg_frc_blur_coef_x6             :4;	//(27:24,NA,4) //frc blur filter coeff, x, [6]/[10]
	UINT32 reg_frc_blur_coef_x7             :4;	//(31:28,NA,4) //frc blur filter coeff, x, [7]/[9]
	};
}PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22588 RW 0x0000_0866
	UINT32 reg_frc_blur_coef_y0             :4;	//(3:0,NA,6) //frc blur filter coeff, y, [0]/[4]
	UINT32 reg_frc_blur_coef_y1             :4;	//(7:4,NA,6) //frc blur filter coeff, y, [1]/[3]
	UINT32 reg_frc_blur_coef_y2             :4;	//(11:8,NA,8) //frc blur filter coeff, y, [2]
	UINT32 resvd                            :20;
	};
}PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22590 RW 0x0000_0000
	UINT32 reg_frc_halo_en                  :1;	//(0:0,NA,0) //frc halo enable
	UINT32 reg_frc_halo_debug_en            :1;	//(1:1,NA,0) //frc halo debug en
	UINT32 resvd                            :30;
	};
}PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22594 RW 0x1812_0C06
	UINT32 reg_frc_halo_cnt_th0             :6;	//(5:0,NA,6) //frc halo weight smoothing count threshold, 0
	UINT32 resvd0                           :2;
	UINT32 reg_frc_halo_cnt_th1             :6;	//(13:8,NA,12) //frc halo weight smoothing count threshold, 1
	UINT32 resvd1                           :2;
	UINT32 reg_frc_halo_cnt_th2             :6;	//(21:16,NA,18) //frc halo weight smoothing count threshold, 2
	UINT32 resvd2                           :2;
	UINT32 reg_frc_halo_cnt_th3             :6;	//(29:24,NA,24) //frc halo weight smoothing count threshold, 3
	UINT32 resvd3                           :2;
	};
}PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22598 RW 0x302A_241E
	UINT32 reg_frc_halo_cnt_th4             :6;	//(5:0,NA,30) //frc halo weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_halo_cnt_th5             :6;	//(13:8,NA,36) //frc halo weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_halo_cnt_th6             :6;	//(21:16,NA,42) //frc halo weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_halo_cnt_th7             :6;	//(29:24,NA,48) //frc halo weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2259C RW 0x8765_4321
	UINT32 reg_frc_halo_val0                :4;	//(3:0,NA,1) //frc halo weight smoothing count value, 0
	UINT32 reg_frc_halo_val1                :4;	//(7:4,NA,2) //frc halo weight smoothing count value, 1
	UINT32 reg_frc_halo_val2                :4;	//(11:8,NA,3) //frc halo weight smoothing count value, 2
	UINT32 reg_frc_halo_val3                :4;	//(15:12,NA,4) //frc halo weight smoothing count value, 3
	UINT32 reg_frc_halo_val4                :4;	//(19:16,NA,5) //frc halo weight smoothing count value, 4
	UINT32 reg_frc_halo_val5                :4;	//(23:20,NA,6) //frc halo weight smoothing count value, 5
	UINT32 reg_frc_halo_val6                :4;	//(27:24,NA,7) //frc halo weight smoothing count value, 6
	UINT32 reg_frc_halo_val7                :4;	//(31:28,NA,8) //frc halo weight smoothing count value, 7
	};
}PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA225A0 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA225A4 RW 0x0000_0000
	UINT32 reg_win_frc_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA225A8 RW 0x086F_0EFF
	UINT32 reg_win_frc_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA225AC RW 0x0000_0000
	UINT32 reg_win_frc_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA225B0 RW 0x086F_0EFF
	UINT32 reg_win_frc_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_frc_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22600 RW 0x0000_0C00
	UINT32 mif_r_motion_gain_line_inc       :2;	//(1:0,NA,0x00) //
	UINT32 mif_r_motion_gain_pf_flag_en     :1;	//(2:2,NA,0x00) //
	UINT32 mif_r_motion_gain_manual_en      :1;	//(3:3,NA,0x00) //
	UINT32 mif_r_motion_gain_en             :1;	//(4:4,NA,0x00) //
	UINT32 mif_r_motion_vreverse            :1;	//(5:5,NA,0x00) //
	UINT32 resvd0                           :2;
	UINT32 motion_gain_l5sc_out_sel         :2;	//(9:8,NA,0x0) //0 : motion_gain_l5sc_out	1 :	2 : '0'	3 : '1'
	UINT32 resvd1                           :2;
	UINT32 shp_mgs_mode                     :1;	//(12,NA,0x0) //shp mgs only mode :	shp_mgs_mode:1	csr_mgs_mode:0	csr mgs only mode :	shp_mgs_mode:0	csr_mgs_mode:1
	UINT32 crs_mgs_mode                     :1;	//(13,NA,0x0) //shp mgs only mode :	shp_mgs_mode:1	csr_mgs_mode:0	csr mgs only mode :	shp_mgs_mode:0	csr_mgs_mode:1
	UINT32 resvd2                           :2;
	UINT32 mif_r_motion_gain_voffset        :9;	//(24:16,NA,0x0) //MRD V offset
	UINT32 resvd3                           :5;
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0x0) //motion gain disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0x0) //motion gain de_clk clock gating
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22604 RW 0x0000_0000
	UINT32 reg_motion_gain_in_hoffset       :13;	//(12:0,NA,0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_voffset       :12;	//(27:16,NA,0) //input window offset
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22608 RW 0x0011_001E
	UINT32 reg_motion_gain_in_hactive       :13;	//(12:0,NA,30) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vactive       :12;	//(27:16,NA,17) //input window active size
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2260C RW 0x0011_001E
	UINT32 reg_motion_gain_in_hsize         :13;	//(12:0,NA,30) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vsize         :12;	//(27:16,NA,17) //input source total size
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22610 RW 0x0870_0780
	UINT32 reg_motion_gain_out_pic_width    :13;	//(12:0,NA,1920) //width (default: 3840/2)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_pic_height   :12;	//(27:16,NA,2160) //height (default: 2160)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22614 RW 0x8000_3030
	UINT32 reg_motion_gain_phase_off_h      :6;	//(5:0,NA,-16) //vertical offset of initial pixel position (signed value)  	min: -31	max: +31
	UINT32 resvd0                           :2;
	UINT32 reg_motion_gain_phase_off_v      :6;	//(13:8,NA,-16) //horizontal offset of initial pixel position (signed value)  	min: -31	max: +31
	UINT32 resvd1                           :17;
	UINT32 reg_motion_gain_sampling_mode    :1;	//(31:31,NA,1) //0: normal-auto	1: manual-set
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22618 RW 0x0001_0001
	UINT32 reg_motion_gain_numerator_h      :13;	//(12:0,NA,1) //
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_numerator_v      :12;	//(27:16,NA,1) //
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2261C RW 0x0080_0040
	UINT32 reg_motion_gain_denominator_h    :13;	//(12:0,NA,64) //(default: (3840/2)/30)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_denominator_v    :12;	//(27:16,NA,128) //(default: 2160/17 -> 128)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22620 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22624 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x0        :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y0        :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22628 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x1        :12;	//(11:0,NA,0) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y1        :12;	//(27:16,NA,0) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2262C RW 0x0000_0000
	UINT32 reg_motion_gain_out_hoffset      :13;	//(12:0,NA,0) //output window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_voffset      :12;	//(27:16,NA,0) //output window offset
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22630 RW 0x0870_0780
	UINT32 reg_motion_gain_out_hactive      :13;	//(12:0,NA,1920) //output window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_vactive      :12;	//(27:16,NA,2160) //output window active size
	UINT32 resvd1                           :2;
	UINT32 logo_l7sc_out_sel                :2;	//(31:30,NA,0) //0 : logo_l7sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22640 RW 0x0000_0000
	UINT32 reg_motion_prot_adaptive_en      :1;	//(0:0,NA,0) //motion protection enable
	UINT32 resvd                            :31;
	};
}PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22644 RW 0x4040_0000
	UINT32 reg_motion_prot_lut_a_y0         :8;	//(7:0,NA,0) //motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0         :8;	//(15:8,NA,0) //motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1         :8;	//(23:16,NA,64) //motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1         :8;	//(31:24,NA,64) //motion gain LUT, A, x1
	};
}PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22648 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_a_y2         :8;	//(7:0,NA,80) //motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2         :8;	//(15:8,NA,110) //motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3         :8;	//(23:16,NA,120) //motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3         :8;	//(31:24,NA,255) //motion gain LUT, A, x3
	};
}PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2264C RW 0x4040_0000
	UINT32 reg_motion_prot_lut_t_y0         :8;	//(7:0,NA,0) //motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0         :8;	//(15:8,NA,0) //motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1         :8;	//(23:16,NA,64) //motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1         :8;	//(31:24,NA,64) //motion gain LUT, T, x1
	};
}PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22650 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_t_y2         :8;	//(7:0,NA,80) //motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2         :8;	//(15:8,NA,110) //motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3         :8;	//(23:16,NA,120) //motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3         :8;	//(31:24,NA,255) //motion gain LUT, T, x3
	};
}PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22670 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22674 RW 0x0000_0000
	UINT32 reg_win_mot_win_w0_x0            :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w0_y0            :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22678 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w0_x1            :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w0_y1            :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2267C RW 0x0000_0000
	UINT32 reg_win_mot_win_w1_x0            :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w1_y0            :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22680 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w1_x1            :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_mot_win_w1_y1            :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22690 RW 0x0000_0000
	UINT32 reg_obj_shp_en                   :1;	//(0:0,NA,0) //0 : disable	1 : enable
	UINT32 resvd0                           :3;
	UINT32 reg_obj_sel_bit                  :1;	//(4:4,NA,0) //0 : 7bit	1 : 6bit
	UINT32 resvd1                           :27;
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22694 RW 0x4080_005a
	UINT32 reg_obj_face_gain_lut_y0         :8;	//(7:0,NA,90) //object face gain LUT , y2
	UINT32 reg_obj_face_gain_lut_x0         :8;	//(15:8,NA,0) //object face gain LUT , x2
	UINT32 reg_obj_face_gain_lut_y1         :8;	//(23:16,NA,128) //object face gain LUT , y3
	UINT32 reg_obj_face_gain_lut_x1         :8;	//(31:24,NA,64) //object face gain LUT , x3
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22698 RW 0xc4ff_6090
	UINT32 reg_obj_face_gain_lut_y2         :8;	//(7:0,NA,144) //object face gain LUT , y0
	UINT32 reg_obj_face_gain_lut_x2         :8;	//(15:8,NA,96) //object face gain LUT , x0
	UINT32 reg_obj_face_gain_lut_y3         :8;	//(23:16,NA,255) //object face gain LUT , y1
	UINT32 reg_obj_face_gain_lut_x3         :8;	//(31:24,NA,196) //object face gain LUT , x1
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2269C RW 0x2080_005a
	UINT32 reg_obj_obj_gain_lut_y0          :8;	//(7:0,NA,90) //object object gain LUT , y2
	UINT32 reg_obj_obj_gain_lut_x0          :8;	//(15:8,NA,0) //object object gain LUT , x2
	UINT32 reg_obj_obj_gain_lut_y1          :8;	//(23:16,NA,128) //object object gain LUT , y3
	UINT32 reg_obj_obj_gain_lut_x1          :8;	//(31:24,NA,32) //object object gain LUT , x3
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226A0 RW 0x90b0_4090
	UINT32 reg_obj_obj_gain_lut_y2          :8;	//(7:0,NA,144) //object object gain LUT , y0
	UINT32 reg_obj_obj_gain_lut_x2          :8;	//(15:8,NA,64) //object object gain LUT , x0
	UINT32 reg_obj_obj_gain_lut_y3          :8;	//(23:16,NA,176) //object object gain LUT , y1
	UINT32 reg_obj_obj_gain_lut_x3          :8;	//(31:24,NA,144) //object object gain LUT , x1
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226A4 RW 0x1090_00ac
	UINT32 reg_obj_final_blend_obj_lut_y0   :8;	//(7:0,NA,172) //object final_blend_obj LUT , y2
	UINT32 reg_obj_final_blend_obj_lut_x0   :8;	//(15:8,NA,0) //object final_blend_obj LUT , x2
	UINT32 reg_obj_final_blend_obj_lut_y1   :8;	//(23:16,NA,144) //object final_blend_obj LUT , y3
	UINT32 reg_obj_final_blend_obj_lut_x1   :8;	//(31:24,NA,16) //object final_blend_obj LUT , x3
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226A8 RW 0x8000_2060
	UINT32 reg_obj_final_blend_obj_lut_y2   :8;	//(7:0,NA,96) //object final_blend_obj LUT , y0
	UINT32 reg_obj_final_blend_obj_lut_x2   :8;	//(15:8,NA,32) //object final_blend_obj LUT , x0
	UINT32 reg_obj_final_blend_obj_lut_y3   :8;	//(23:16,NA,0) //object final_blend_obj LUT , y1
	UINT32 reg_obj_final_blend_obj_lut_x3   :8;	//(31:24,NA,128) //object final_blend_obj LUT , x1
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226AC RW 0x10dc_00c4
	UINT32 reg_obj_final_blend_face_lut_y0  :8;	//(7:0,NA,196) //object final_blend_face LUT , y2
	UINT32 reg_obj_final_blend_face_lut_x0  :8;	//(15:8,NA,0) //object final_blend_face LUT , x2
	UINT32 reg_obj_final_blend_face_lut_y1  :8;	//(23:16,NA,220) //object final_blend_face LUT , y3
	UINT32 reg_obj_final_blend_face_lut_x1  :8;	//(31:24,NA,16) //object final_blend_face LUT , x3
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226B0 RW 0x40ff_20dc
	UINT32 reg_obj_final_blend_face_lut_y2  :8;	//(7:0,NA,220) //object final_blend_face LUT , y0
	UINT32 reg_obj_final_blend_face_lut_x2  :8;	//(15:8,NA,32) //object final_blend_face LUT , x0
	UINT32 reg_obj_final_blend_face_lut_y3  :8;	//(23:16,NA,255) //object final_blend_face LUT , y1
	UINT32 reg_obj_final_blend_face_lut_x3  :8;	//(31:24,NA,64) //object final_blend_face LUT , x1
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226B4 RW 0x3060_0050
	UINT32 reg_obj_master_gain_a_map_lut_y0 :8;	//(7:0,NA,80) //object master_gain LUT , y2
	UINT32 reg_obj_master_gain_a_map_lut_x0 :8;	//(15:8,NA,0) //object master_gain LUT , x2
	UINT32 reg_obj_master_gain_a_map_lut_y1 :8;	//(23:16,NA,96) //object master_gain LUT , y3
	UINT32 reg_obj_master_gain_a_map_lut_x1 :8;	//(31:24,NA,48) //object master_gain LUT , x3
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226B8 RW 0x9080_6080
	UINT32 reg_obj_master_gain_a_map_lut_y2 :8;	//(7:0,NA,128) //object master_gain LUT , y0
	UINT32 reg_obj_master_gain_a_map_lut_x2 :8;	//(15:8,NA,96) //object master_gain LUT , x0
	UINT32 reg_obj_master_gain_a_map_lut_y3 :8;	//(23:16,NA,128) //object master_gain LUT , y1
	UINT32 reg_obj_master_gain_a_map_lut_x3 :8;	//(31:24,NA,144) //object master_gain LUT , x1
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226BC RW 0x3060_0050
	UINT32 reg_obj_master_gain_t_map_lut_y0 :8;	//(7:0,NA,80) //object master_gain LUT , y2
	UINT32 reg_obj_master_gain_t_map_lut_x0 :8;	//(15:8,NA,0) //object master_gain LUT , x2
	UINT32 reg_obj_master_gain_t_map_lut_y1 :8;	//(23:16,NA,96) //object master_gain LUT , y3
	UINT32 reg_obj_master_gain_t_map_lut_x1 :8;	//(31:24,NA,48) //object master_gain LUT , x3
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA226C0 RW 0x9080_6080
	UINT32 reg_obj_master_gain_t_map_lut_y2 :8;	//(7:0,NA,128) //object master_gain LUT , y0
	UINT32 reg_obj_master_gain_t_map_lut_x2 :8;	//(15:8,NA,96) //object master_gain LUT , x0
	UINT32 reg_obj_master_gain_t_map_lut_y3 :8;	//(23:16,NA,128) //object master_gain LUT , y1
	UINT32 reg_obj_master_gain_t_map_lut_x3 :8;	//(31:24,NA,144) //object master_gain LUT , x1
	};
}PE_O24_VSD_SHP_SHP_OBJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227A0 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//(11:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//(27:16,NA,0) //Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227A4 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :12;	//(11:0,NA,0) //Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//(27:16,NA,0) //Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227A8 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :12;	//(11:0,NA,0) //Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//(27:16,NA,0) //Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227AC RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//(11:0,NA,0) //Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//(27:16,NA,0) //Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227B0 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O24_VSD_SHP_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227B4 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O24_VSD_SHP_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227D0 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227D4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227D8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227DC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227E0 RO 0x0000_0000
	UINT32 ro_buf_rptr                      :2;	//(1:0,NA,0) //
	UINT32 ro_buf_wptr_d                    :2;	//(3:2,NA,0) //
	UINT32 ro_core_wd_ptr                   :2;	//(5:4,NA,0) //
	UINT32 ro_buf_rcnt                      :10;	//(15:6,NA,0) //(reg_ro_buf_wrsel==1) ? {2'd0,r_ro_buf_rd} : r_buf_rcnt
	UINT32 ro_buf_wcnt                      :10;	//(25:16,NA,0) //(reg_ro_buf_wrsel==1) ? {2'd0,r_ro_buf_wd} : r_buf_wcnt
	UINT32 ro_buf_wre_cnt                   :4;	//(29:26,NA,0) //
	UINT32 resvd                            :2;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227E4 RO 0x0000_0000
	UINT32 ro_out_v_line                    :12;	//(11:0,NA,0) //
	UINT32 resvd0                           :4;
	UINT32 ro_in_v_line                     :12;	//(27:16,NA,0) //
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_MOTION_GAIN_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227E8 RO 0x0000_0000
	UINT32 ro_edge_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227EC RO 0x0000_0000
	UINT32 ro_edge_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227F0 RO 0x0000_0000
	UINT32 ro_edge_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227F4 RO 0x0000_0000
	UINT32 ro_edge_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227F8 RO 0x0000_0000
	UINT32 ro_edge_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA227FC RO 0x0000_0000
	UINT32 ro_edge_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_edge_status_11                :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22800 RO 0x0000_0000
	UINT32 ro_tmap_status_window0           :32;	//(31:0,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22804 RO 0x0000_0000
	UINT32 ro_tmap_status_window1           :32;	//(31:0,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22808 RO 0x0000_0000
	UINT32 ro_tmap_status_0                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_1                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2280C RO 0x0000_0000
	UINT32 ro_tmap_status_2                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_3                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22810 RO 0x0000_0000
	UINT32 ro_tmap_status_4                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_5                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22814 RO 0x0000_0000
	UINT32 ro_tmap_status_6                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_7                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22818 RO 0x0000_0000
	UINT32 ro_tmap_status_8                 :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_9                 :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2281C RO 0x0000_0000
	UINT32 ro_tmap_status_10                :16;	//(15:0,NA,0) //
	UINT32 ro_tmap_status_11                :16;	//(31:16,NA,0) //
	};
}PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22820 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22824 RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w0_x0     :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w0_y0     :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22828 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w0_x1     :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w0_y1     :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2282C RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w1_x0     :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w1_y0     :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22830 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w1_x1     :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w1_y1     :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22834 RW 0x0000_0000
	UINT32 reg_core0_win_face_value         :8;	//(7:0,NA,0) //force face value
	UINT32 resvd                            :24;
	};
}PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22838 RW 0x0000_0000
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
}PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2283C RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w0_x0     :12;	//(11:0,NA,0) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w0_y0     :12;	//(27:16,NA,0) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22840 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w0_x1     :12;	//(11:0,NA,3839) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w0_y1     :12;	//(27:16,NA,2159) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22844 RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w1_x0     :12;	//(11:0,NA,0) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w1_y0     :12;	//(27:16,NA,0) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22848 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w1_x1     :12;	//(11:0,NA,3839) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w1_y1     :12;	//(27:16,NA,2159) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2284C RW 0x0000_0000
	UINT32 reg_core0_win_body_value         :8;	//(7:0,NA,0) //force body value
	UINT32 resvd                            :24;
	};
}PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22850 RW 0x0000_0000
	UINT32 reg_luma_dp_blend_en             :1;	//(0:0,NA,0) //luma_dp_blend_en
	UINT32 resvd0                           :7;
	UINT32 reg_luma_dp_blend_debug_sel_en   :1;	//(8:8,NA,0) //0 : gain, 1: bypass Y
	UINT32 resvd1                           :23;
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22854 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22858 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2285C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y4                  :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x4                  :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y5                  :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x5                  :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22860 RW 0x8020_8020
	UINT32 reg_gain_lut_y6                  :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x6                  :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y7                  :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x7                  :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22864 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y8                  :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x8                  :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y9                  :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x9                  :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22868 RW 0x8020_8020
	UINT32 reg_gain_lut_y10                 :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x10                 :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y11                 :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x11                 :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2286C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y12                 :8;	//(7:0,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x12                 :8;	//(15:8,NA,0) //Luma Blend LUT
	UINT32 reg_gain_lut_y13                 :8;	//(23:16,NA,192) //Luma Blend LUT
	UINT32 reg_gain_lut_x13                 :8;	//(31:24,NA,0) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22870 RW 0x8020_8020
	UINT32 reg_gain_lut_y14                 :8;	//(7:0,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x14                 :8;	//(15:8,NA,128) //Luma Blend LUT
	UINT32 reg_gain_lut_y15                 :8;	//(23:16,NA,32) //Luma Blend LUT
	UINT32 reg_gain_lut_x15                 :8;	//(31:24,NA,128) //Luma Blend LUT
	};
}PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22874 RW 0x0001_0003
	UINT32 resvd0                           :16;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //pre-mmd cut resolution
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_SHP_SHP_SMTH_MMD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22878 RW 0x8080_8007
	UINT32 reg_textgain_en                  :1;	//(0,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(2,NA,0x1) //
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 reg_head_body_sel                :1;	//(6,NA,0x0) //0:max, 1:sum
	UINT32 resvd1                           :1;
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2287C RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22880 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22884 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22888 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2288C RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22890 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22894 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA22898 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2289C RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228A0 RW 0x0000_0000
	UINT32 reg_cr_smth_control_en           :2;	//(1:0,NA,0) //0: alpha blending	1: original	2: 7x7 blur
	UINT32 resvd0                           :2;
	UINT32 reg_cb_smth_control_en           :2;	//(5:4,NA,0) //0: alpha blending	1: original	2: 7x7 blur
	UINT32 resvd1                           :2;
	UINT32 reg_yy_smth_control_en           :2;	//(9:8,NA,0) //0: alpha blending	1: original	2: 7x7 blur
	UINT32 resvd2                           :22;
	};
}PE_O24_VSD_SHP_SHP_SMTH_CON_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228F0 RW 0x0000_0000
	UINT32 reg_drc_apb_write_cont			:2;		//1:0	drc curv update counter
	UINT32 resvd0							:1;
	UINT32 reg_drc_write_cont				:2;		//4:3	drc curv update counter
	UINT32 resvd1							:3;
	UINT32 reg_pre_norm						:8;		//15:8	IWP - iir weight prev norm
	UINT32 reg_cur_norm						:8;		//23:16	IWC - iir weight cur  norm
	UINT32 reg_pre_sc						:8;		//31:24	IWSP - iir weight scene change prev sc
	};
}PE_O24_VSD_SHP_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228F4 RW 0x0000_0000
	UINT32 reg_cur_sc						:8;		//7:0	IWSC - iir weight scene change cur sc
	UINT32 reg_ui_gain_w					:8;		//15:8	UGW - ui gain white
	UINT32 reg_ui_gain_b					:8;		//23:16 UGB - ui gain black
	UINT32 reg_vy_mode                      :2;		//25:24 ui rgb select
	UINT32 resvd0							:6;		
	};
}PE_O24_VSD_SHP_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228F8 RW 0x0000_0000
	UINT32 reg_obc_debug                      : 2;  // 1:0, 0: shp result   1 : face map   2 : object map
	};
}PE_O24_VSD_SHP_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VSD_SHP_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O24_VSD_SHP_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCCA22000
	PE_O24_VSD_SHP_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCCA22004
	PE_O24_VSD_SHP_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCCA22008
	PE_O24_VSD_SHP_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCCA2200C
	PE_O24_VSD_SHP_SHP_CORE_CTRL_04_T                     shp_core_ctrl_04;	//0xCCA22010
	PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_00_T                 shp_new_fd_ctrl_00;	//0xCCA22014
	PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_01_T                 shp_new_fd_ctrl_01;	//0xCCA22018
	PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_02_T                 shp_new_fd_ctrl_02;	//0xCCA2201C
	PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_03_T                 shp_new_fd_ctrl_03;	//0xCCA22020
	PE_O24_VSD_SHP_SHP_NEW_FD_CTRL_04_T                 shp_new_fd_ctrl_04;	//0xCCA22024
	PE_O24_VSD_SHP_SHP_TEXT_REGION_MAP_00_T         shp_text_region_map_00;	//0xCCA22028
	UINT32                                                    reserved0;	//0xCCA2202C
	UINT32                                                    reserved1;	//0xCCA22030
	UINT32                                                    reserved2;	//0xCCA22034
	UINT32                                                    reserved3;	//0xCCA22038
	UINT32                                                    reserved4;	//0xCCA2203C
	PE_O24_VSD_SHP_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCCA22040
	UINT32                                                    reserved5;	//0xCCA22044
	UINT32                                                    reserved6;	//0xCCA22048
	UINT32                                                    reserved7;	//0xCCA2204C
	PE_O24_VSD_SHP_SHP_GOS_CTRL_00_T                       shp_gos_ctrl_00;	//0xCCA22050
	UINT32                                                    reserved8;	//0xCCA22054
	UINT32                                                    reserved9;	//0xCCA22058
	UINT32                                                   reserved10;	//0xCCA2205C
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_00_T             shp_sync_dly_ctrl_00;	//0xCCA22060
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_01_T             shp_sync_dly_ctrl_01;	//0xCCA22064
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_02_T             shp_sync_dly_ctrl_02;	//0xCCA22068
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_03_T             shp_sync_dly_ctrl_03;	//0xCCA2206C
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_04_T             shp_sync_dly_ctrl_04;	//0xCCA22070
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_05_T             shp_sync_dly_ctrl_05;	//0xCCA22074
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_06_T             shp_sync_dly_ctrl_06;	//0xCCA22078
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_07_T             shp_sync_dly_ctrl_07;	//0xCCA2207C
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_08_T             shp_sync_dly_ctrl_08;	//0xCCA22080
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_09_T             shp_sync_dly_ctrl_09;	//0xCCA22084
	PE_O24_VSD_SHP_SHP_SYNC_DLY_CTRL_0A_T             shp_sync_dly_ctrl_0a;	//0xCCA22088
	UINT32                                                   reserved11;	//0xCCA2208C
	PE_O24_VSD_SHP_SHP_ROI_MASK_CTRL_00_T             shp_roi_mask_ctrl_00;	//0xCCA22090
	PE_O24_VSD_SHP_SHP_ROI_MASK_CTRL_01_T             shp_roi_mask_ctrl_01;	//0xCCA22094
	PE_O24_VSD_SHP_SHP_ROI_MASK_CTRL_02_T             shp_roi_mask_ctrl_02;	//0xCCA22098
	UINT32                                                   reserved12;	//0xCCA2209C
	PE_O24_VSD_SHP_SHP_ESF_CTRL_00_T                       shp_esf_ctrl_00;	//0xCCA220A0
	PE_O24_VSD_SHP_SHP_ESF_CTRL_01_T                       shp_esf_ctrl_01;	//0xCCA220A4
	PE_O24_VSD_SHP_SHP_ESF_CTRL_02_T                       shp_esf_ctrl_02;	//0xCCA220A8
	UINT32                                                   reserved13;	//0xCCA220AC
	PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_00_T               shp_esf_win_ctrl_00;	//0xCCA220B0
	PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_01_T               shp_esf_win_ctrl_01;	//0xCCA220B4
	PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_02_T               shp_esf_win_ctrl_02;	//0xCCA220B8
	PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_03_T               shp_esf_win_ctrl_03;	//0xCCA220BC
	PE_O24_VSD_SHP_SHP_ESF_WIN_CTRL_04_T               shp_esf_win_ctrl_04;	//0xCCA220C0
	UINT32                                                   reserved14;	//0xCCA220C4
	UINT32                                                   reserved15;	//0xCCA220C8
	UINT32                                                   reserved16;	//0xCCA220CC
	UINT32                                                   reserved17;	//0xCCA220D0
	UINT32                                                   reserved18;	//0xCCA220D4
	UINT32                                                   reserved19;	//0xCCA220D8
	UINT32                                                   reserved20;	//0xCCA220DC
	UINT32                                                   reserved21;	//0xCCA220E0
	UINT32                                                   reserved22;	//0xCCA220E4
	UINT32                                                   reserved23;	//0xCCA220E8
	UINT32                                                   reserved24;	//0xCCA220EC
	PE_O24_VSD_SHP_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCCA220F0
	UINT32                                                   reserved25;	//0xCCA220F4
	UINT32                                                   reserved26;	//0xCCA220F8
	UINT32                                                   reserved27;	//0xCCA220FC
	PE_O24_VSD_SHP_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCCA22100
	PE_O24_VSD_SHP_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCCA22104
	PE_O24_VSD_SHP_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCCA22108
	PE_O24_VSD_SHP_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCCA2210C
	PE_O24_VSD_SHP_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCCA22110
	PE_O24_VSD_SHP_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCCA22114
	PE_O24_VSD_SHP_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCCA22118
	PE_O24_VSD_SHP_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCCA2211C
	PE_O24_VSD_SHP_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCCA22120
	PE_O24_VSD_SHP_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCCA22124
	PE_O24_VSD_SHP_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCCA22128
	PE_O24_VSD_SHP_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCCA2212C
	PE_O24_VSD_SHP_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCCA22130
	PE_O24_VSD_SHP_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCCA22134
	PE_O24_VSD_SHP_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCCA22138
	PE_O24_VSD_SHP_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCCA2213C
	PE_O24_VSD_SHP_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCCA22140
	PE_O24_VSD_SHP_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCCA22144
	PE_O24_VSD_SHP_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCCA22148
	PE_O24_VSD_SHP_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCCA2214C
	PE_O24_VSD_SHP_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCCA22150
	PE_O24_VSD_SHP_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCCA22154
	PE_O24_VSD_SHP_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCCA22158
	UINT32                                                   reserved28;	//0xCCA2215C
	PE_O24_VSD_SHP_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCCA22160
	PE_O24_VSD_SHP_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCCA22164
	PE_O24_VSD_SHP_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCCA22168
	PE_O24_VSD_SHP_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCCA2216C
	PE_O24_VSD_SHP_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCCA22170
	PE_O24_VSD_SHP_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCCA22174
	PE_O24_VSD_SHP_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCCA22178
	PE_O24_VSD_SHP_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCCA2217C
	PE_O24_VSD_SHP_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCCA22180
	PE_O24_VSD_SHP_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCCA22184
	PE_O24_VSD_SHP_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCCA22188
	PE_O24_VSD_SHP_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCCA2218C
	PE_O24_VSD_SHP_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCCA22190
	PE_O24_VSD_SHP_SHP_APL_CTRL_00_T                       shp_apl_ctrl_00;	//0xCCA22194
	UINT32                                                   reserved29;	//0xCCA22198
	UINT32                                                   reserved30;	//0xCCA2219C
	PE_O24_VSD_SHP_SHP_LC_CTRL_00_T                         shp_lc_ctrl_00;	//0xCCA221A0
	PE_O24_VSD_SHP_SHP_LC_CTRL_01_T                         shp_lc_ctrl_01;	//0xCCA221A4
	PE_O24_VSD_SHP_SHP_LC_CTRL_02_T                         shp_lc_ctrl_02;	//0xCCA221A8
	PE_O24_VSD_SHP_SHP_LC_CTRL_03_T                         shp_lc_ctrl_03;	//0xCCA221AC
	PE_O24_VSD_SHP_SHP_LC_CTRL_04_T                         shp_lc_ctrl_04;	//0xCCA221B0
	UINT32                                                   reserved31;	//0xCCA221B4
	UINT32                                                   reserved32;	//0xCCA221B8
	UINT32                                                   reserved33;	//0xCCA221BC
	PE_O24_VSD_SHP_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCCA221C0
	PE_O24_VSD_SHP_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCCA221C4
	PE_O24_VSD_SHP_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCCA221C8
	PE_O24_VSD_SHP_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCCA221CC
	PE_O24_VSD_SHP_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCCA221D0
	PE_O24_VSD_SHP_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCCA221D4
	PE_O24_VSD_SHP_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCCA221D8
	PE_O24_VSD_SHP_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCCA221DC
	PE_O24_VSD_SHP_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCCA221E0
	PE_O24_VSD_SHP_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCCA221E4
	PE_O24_VSD_SHP_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCCA221E8
	PE_O24_VSD_SHP_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCCA221EC
	PE_O24_VSD_SHP_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCCA221F0
	PE_O24_VSD_SHP_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCCA221F4
	PE_O24_VSD_SHP_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCCA221F8
	PE_O24_VSD_SHP_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCCA221FC
	PE_O24_VSD_SHP_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCCA22200
	PE_O24_VSD_SHP_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCCA22204
	PE_O24_VSD_SHP_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCCA22208
	PE_O24_VSD_SHP_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCCA2220C
	PE_O24_VSD_SHP_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCCA22210
	UINT32                                                   reserved34;	//0xCCA22214
	UINT32                                                   reserved35;	//0xCCA22218
	UINT32                                                   reserved36;	//0xCCA2221C
	PE_O24_VSD_SHP_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCCA22220
	PE_O24_VSD_SHP_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCCA22224
	PE_O24_VSD_SHP_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCCA22228
	PE_O24_VSD_SHP_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCCA2222C
	PE_O24_VSD_SHP_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCCA22230
	UINT32                                                   reserved37;	//0xCCA22234
	UINT32                                                   reserved38;	//0xCCA22238
	UINT32                                                   reserved39;	//0xCCA2223C
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCCA22240
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCCA22244
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCCA22248
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_03_C0_T               shp_tgen_ctrl_03_c0;	//0xCCA2224C
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_03_C1_T               shp_tgen_ctrl_03_c1;	//0xCCA22250
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCCA22254
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCCA22258
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCCA2225C
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCCA22260
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCCA22264
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCCA22268
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCCA2226C
	PE_O24_VSD_SHP_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCCA22270
	PE_O24_VSD_SHP_SHP_SNR_CTRL_00_T                       shp_snr_ctrl_00;	//0xCCA22274
	UINT32                                                   reserved40;	//0xCCA22278
	UINT32                                                   reserved41;	//0xCCA2227C
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_00_T                     shp_dctp_ctrl_00;	//0xCCA22280
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_01_T                     shp_dctp_ctrl_01;	//0xCCA22284
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_02_T                     shp_dctp_ctrl_02;	//0xCCA22288
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_03_T                     shp_dctp_ctrl_03;	//0xCCA2228C
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_04_T                     shp_dctp_ctrl_04;	//0xCCA22290
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_05_T                     shp_dctp_ctrl_05;	//0xCCA22294
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_06_T                     shp_dctp_ctrl_06;	//0xCCA22298
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_07_T                     shp_dctp_ctrl_07;	//0xCCA2229C
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_08_T                     shp_dctp_ctrl_08;	//0xCCA222A0
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_09_T                     shp_dctp_ctrl_09;	//0xCCA222A4
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_0A_T                     shp_dctp_ctrl_0a;	//0xCCA222A8
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_0B_T                     shp_dctp_ctrl_0b;	//0xCCA222AC
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_0C_T                     shp_dctp_ctrl_0c;	//0xCCA222B0
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_0D_T                     shp_dctp_ctrl_0d;	//0xCCA222B4
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_0E_T                     shp_dctp_ctrl_0e;	//0xCCA222B8
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_0F_T                     shp_dctp_ctrl_0f;	//0xCCA222BC
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_10_T                     shp_dctp_ctrl_10;	//0xCCA222C0
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_11_T                     shp_dctp_ctrl_11;	//0xCCA222C4
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_12_T                     shp_dctp_ctrl_12;	//0xCCA222C8
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_13_T                     shp_dctp_ctrl_13;	//0xCCA222CC
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_14_T                     shp_dctp_ctrl_14;	//0xCCA222D0
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_15_T                     shp_dctp_ctrl_15;	//0xCCA222D4
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_16_T                     shp_dctp_ctrl_16;	//0xCCA222D8
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_17_T                     shp_dctp_ctrl_17;	//0xCCA222DC
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_18_T                     shp_dctp_ctrl_18;	//0xCCA222E0
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_19_T                     shp_dctp_ctrl_19;	//0xCCA222E4
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_1A_T                     shp_dctp_ctrl_1a;	//0xCCA222E8
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_1B_T                     shp_dctp_ctrl_1b;	//0xCCA222EC
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_1C_T                     shp_dctp_ctrl_1c;	//0xCCA222F0
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_1D_T                     shp_dctp_ctrl_1d;	//0xCCA222F4
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_1E_T                     shp_dctp_ctrl_1e;	//0xCCA222F8
	PE_O24_VSD_SHP_SHP_DCTP_CTRL_1F_T                     shp_dctp_ctrl_1f;	//0xCCA222FC
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_00_T                     shp_nntg_ctrl_00;	//0xCCA22300
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_01_C0_T               shp_nntg_ctrl_01_c0;	//0xCCA22304
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_02_C0_T               shp_nntg_ctrl_02_c0;	//0xCCA22308
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_03_C0_T               shp_nntg_ctrl_03_c0;	//0xCCA2230C
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_04_C0_T               shp_nntg_ctrl_04_c0;	//0xCCA22310
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_05_C0_T               shp_nntg_ctrl_05_c0;	//0xCCA22314
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_01_C1_T               shp_nntg_ctrl_01_c1;	//0xCCA22318
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_02_C1_T               shp_nntg_ctrl_02_c1;	//0xCCA2231C
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_03_C1_T               shp_nntg_ctrl_03_c1;	//0xCCA22320
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_04_C1_T               shp_nntg_ctrl_04_c1;	//0xCCA22324
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_05_C1_T               shp_nntg_ctrl_05_c1;	//0xCCA22328
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_06_T                     shp_nntg_ctrl_06;	//0xCCA2232C
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_07_T                     shp_nntg_ctrl_07;	//0xCCA22330
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_08_T                     shp_nntg_ctrl_08;	//0xCCA22334
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_09_T                     shp_nntg_ctrl_09;	//0xCCA22338
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_0A_T                     shp_nntg_ctrl_0a;	//0xCCA2233C
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_0B_T                     shp_nntg_ctrl_0b;	//0xCCA22340
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_0C_T                     shp_nntg_ctrl_0c;	//0xCCA22344
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_0D_T                     shp_nntg_ctrl_0d;	//0xCCA22348
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_0E_T                     shp_nntg_ctrl_0e;	//0xCCA2234C
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_0F_T                     shp_nntg_ctrl_0f;	//0xCCA22350
	PE_O24_VSD_SHP_SHP_NNTG_CTRL_10_T                     shp_nntg_ctrl_10;	//0xCCA22354
	UINT32                                                   reserved42;	//0xCCA22358
	UINT32                                                   reserved43;	//0xCCA2235C
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCCA22360
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCCA22364
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCCA22368
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_03_T                 shp_dp_sum_ctrl_03;	//0xCCA2236C
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_04_T                 shp_dp_sum_ctrl_04;	//0xCCA22370
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_05_T                 shp_dp_sum_ctrl_05;	//0xCCA22374
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_06_T                 shp_dp_sum_ctrl_06;	//0xCCA22378
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_07_T                 shp_dp_sum_ctrl_07;	//0xCCA2237C
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_08_T                 shp_dp_sum_ctrl_08;	//0xCCA22380
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_09_T                 shp_dp_sum_ctrl_09;	//0xCCA22384
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_0A_T                 shp_dp_sum_ctrl_0a;	//0xCCA22388
	UINT32                                                   reserved44;	//0xCCA2238C
	PE_O24_VSD_SHP_SHP_PSP_CTRL_00_T                       shp_psp_ctrl_00;	//0xCCA22390
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_0B_T                 shp_dp_sum_ctrl_0b;	//0xCCA22394
	PE_O24_VSD_SHP_SHP_DP_SUM_CTRL_0C_T                 shp_dp_sum_ctrl_0c;	//0xCCA22398
	UINT32                                                   reserved45;	//0xCCA2239C
	PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCCA223A0
	PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCCA223A4
	PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCCA223A8
	PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCCA223AC
	PE_O24_VSD_SHP_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCCA223B0
	UINT32                                                   reserved46;	//0xCCA223B4
	UINT32                                                   reserved47;	//0xCCA223B8
	UINT32                                                   reserved48;	//0xCCA223BC
	PE_O24_VSD_SHP_SHP_FD_REGION_TEXT_00_T           shp_fd_region_text_00;	//0xCCA223C0
	PE_O24_VSD_SHP_SHP_FD_REGION_TEXT_01_T           shp_fd_region_text_01;	//0xCCA223C4
	PE_O24_VSD_SHP_SHP_FD_REGION_TEXT_02_T           shp_fd_region_text_02;	//0xCCA223C8
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_00_T               shp_fd_tmap_temp_00;	//0xCCA223CC
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_01_T               shp_fd_tmap_temp_01;	//0xCCA223D0
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_02_T               shp_fd_tmap_temp_02;	//0xCCA223D4
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_03_T               shp_fd_tmap_temp_03;	//0xCCA223D8
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_04_T               shp_fd_tmap_temp_04;	//0xCCA223DC
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_05_T               shp_fd_tmap_temp_05;	//0xCCA223E0
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_06_T               shp_fd_tmap_temp_06;	//0xCCA223E4
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_07_T               shp_fd_tmap_temp_07;	//0xCCA223E8
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_08_T               shp_fd_tmap_temp_08;	//0xCCA223EC
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_09_T               shp_fd_tmap_temp_09;	//0xCCA223F0
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_0A_T               shp_fd_tmap_temp_0a;	//0xCCA223F4
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_0B_T               shp_fd_tmap_temp_0b;	//0xCCA223F8
	PE_O24_VSD_SHP_SHP_FD_TMAP_TEMP_0C_T               shp_fd_tmap_temp_0c;	//0xCCA223FC
	PE_O24_VSD_SHP_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0xCCA22400
	PE_O24_VSD_SHP_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0xCCA22404
	PE_O24_VSD_SHP_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0xCCA22408
	PE_O24_VSD_SHP_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0xCCA2240C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_04_T                         shp_dj_ctrl_04;	//0xCCA22410
	PE_O24_VSD_SHP_SHP_DJ_CTRL_05_T                         shp_dj_ctrl_05;	//0xCCA22414
	PE_O24_VSD_SHP_SHP_DJ_CTRL_06_T                         shp_dj_ctrl_06;	//0xCCA22418
	PE_O24_VSD_SHP_SHP_DJ_CTRL_07_T                         shp_dj_ctrl_07;	//0xCCA2241C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_08_T                         shp_dj_ctrl_08;	//0xCCA22420
	PE_O24_VSD_SHP_SHP_DJ_CTRL_09_T                         shp_dj_ctrl_09;	//0xCCA22424
	PE_O24_VSD_SHP_SHP_DJ_CTRL_0A_T                         shp_dj_ctrl_0a;	//0xCCA22428
	PE_O24_VSD_SHP_SHP_DJ_CTRL_0B_T                         shp_dj_ctrl_0b;	//0xCCA2242C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_0C_T                         shp_dj_ctrl_0c;	//0xCCA22430
	PE_O24_VSD_SHP_SHP_DJ_CTRL_0D_T                         shp_dj_ctrl_0d;	//0xCCA22434
	PE_O24_VSD_SHP_SHP_DJ_CTRL_0E_T                         shp_dj_ctrl_0e;	//0xCCA22438
	PE_O24_VSD_SHP_SHP_DJ_CTRL_0F_T                         shp_dj_ctrl_0f;	//0xCCA2243C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_10_T                         shp_dj_ctrl_10;	//0xCCA22440
	PE_O24_VSD_SHP_SHP_DJ_CTRL_11_T                         shp_dj_ctrl_11;	//0xCCA22444
	PE_O24_VSD_SHP_SHP_DJ_CTRL_12_T                         shp_dj_ctrl_12;	//0xCCA22448
	PE_O24_VSD_SHP_SHP_DJ_CTRL_13_T                         shp_dj_ctrl_13;	//0xCCA2244C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_14_T                         shp_dj_ctrl_14;	//0xCCA22450
	PE_O24_VSD_SHP_SHP_DJ_CTRL_15_T                         shp_dj_ctrl_15;	//0xCCA22454
	PE_O24_VSD_SHP_SHP_DJ_CTRL_16_T                         shp_dj_ctrl_16;	//0xCCA22458
	PE_O24_VSD_SHP_SHP_DJ_CTRL_17_T                         shp_dj_ctrl_17;	//0xCCA2245C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_18_T                         shp_dj_ctrl_18;	//0xCCA22460
	PE_O24_VSD_SHP_SHP_DJ_CTRL_19_T                         shp_dj_ctrl_19;	//0xCCA22464
	PE_O24_VSD_SHP_SHP_DJ_CTRL_1A_T                         shp_dj_ctrl_1a;	//0xCCA22468
	PE_O24_VSD_SHP_SHP_DJ_CTRL_1B_T                         shp_dj_ctrl_1b;	//0xCCA2246C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_1C_T                         shp_dj_ctrl_1c;	//0xCCA22470
	PE_O24_VSD_SHP_SHP_DJ_CTRL_1D_T                         shp_dj_ctrl_1d;	//0xCCA22474
	PE_O24_VSD_SHP_SHP_DJ_CTRL_1E_T                         shp_dj_ctrl_1e;	//0xCCA22478
	PE_O24_VSD_SHP_SHP_DJ_CTRL_1F_T                         shp_dj_ctrl_1f;	//0xCCA2247C
	PE_O24_VSD_SHP_SHP_DJ_CTRL_20_T                         shp_dj_ctrl_20;	//0xCCA22480
	UINT32                                                   reserved49;	//0xCCA22484
	UINT32                                                   reserved50;	//0xCCA22488
	UINT32                                                   reserved51;	//0xCCA2248C
	PE_O24_VSD_SHP_SHP_DB_CTRL_00_T                         shp_db_ctrl_00;	//0xCCA22490
	PE_O24_VSD_SHP_SHP_DB_CTRL_01_T                         shp_db_ctrl_01;	//0xCCA22494
	UINT32                                                   reserved52;	//0xCCA22498
	UINT32                                                   reserved53;	//0xCCA2249C
	PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_00_T                 shp_dj_win_ctrl_00;	//0xCCA224A0
	PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_01_T                 shp_dj_win_ctrl_01;	//0xCCA224A4
	PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_02_T                 shp_dj_win_ctrl_02;	//0xCCA224A8
	PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_03_T                 shp_dj_win_ctrl_03;	//0xCCA224AC
	PE_O24_VSD_SHP_SHP_DJ_WIN_CTRL_04_T                 shp_dj_win_ctrl_04;	//0xCCA224B0
	UINT32                                                   reserved54;	//0xCCA224B4
	UINT32                                                   reserved55;	//0xCCA224B8
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_00_T     shp_dj_text_gain_ctrl_00;	//0xCCA224BC
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_01_T     shp_dj_text_gain_ctrl_01;	//0xCCA224C0
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_02_T     shp_dj_text_gain_ctrl_02;	//0xCCA224C4
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_03_T     shp_dj_text_gain_ctrl_03;	//0xCCA224C8
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_04_T     shp_dj_text_gain_ctrl_04;	//0xCCA224CC
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_05_T     shp_dj_text_gain_ctrl_05;	//0xCCA224D0
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_06_T     shp_dj_text_gain_ctrl_06;	//0xCCA224D4
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_07_T     shp_dj_text_gain_ctrl_07;	//0xCCA224D8
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_08_T     shp_dj_text_gain_ctrl_08;	//0xCCA224DC
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_09_T     shp_dj_text_gain_ctrl_09;	//0xCCA224E0
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_10_T     shp_dj_text_gain_ctrl_10;	//0xCCA224E4
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_11_T     shp_dj_text_gain_ctrl_11;	//0xCCA224E8
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_12_T     shp_dj_text_gain_ctrl_12;	//0xCCA224EC
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_13_T     shp_dj_text_gain_ctrl_13;	//0xCCA224F0
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_14_T     shp_dj_text_gain_ctrl_14;	//0xCCA224F4
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_15_T     shp_dj_text_gain_ctrl_15;	//0xCCA224F8
	PE_O24_VSD_SHP_SHP_DJ_TEXT_GAIN_CTRL_16_T     shp_dj_text_gain_ctrl_16;	//0xCCA224FC
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_00_T                 shp_chroma_ctrl_00;	//0xCCA22500
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_01_T                 shp_chroma_ctrl_01;	//0xCCA22504
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_02_T                 shp_chroma_ctrl_02;	//0xCCA22508
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_03_T                 shp_chroma_ctrl_03;	//0xCCA2250C
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_04_T                 shp_chroma_ctrl_04;	//0xCCA22510
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_05_T                 shp_chroma_ctrl_05;	//0xCCA22514
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_06_T                 shp_chroma_ctrl_06;	//0xCCA22518
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_07_T                 shp_chroma_ctrl_07;	//0xCCA2251C
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_08_T                 shp_chroma_ctrl_08;	//0xCCA22520
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_09_T                 shp_chroma_ctrl_09;	//0xCCA22524
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0A_T                 shp_chroma_ctrl_0a;	//0xCCA22528
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0B_T                 shp_chroma_ctrl_0b;	//0xCCA2252C
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0C_T                 shp_chroma_ctrl_0c;	//0xCCA22530
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0D_T                 shp_chroma_ctrl_0d;	//0xCCA22534
	PE_O24_VSD_SHP_SHP_CHROMA_CTRL_0E_T                 shp_chroma_ctrl_0e;	//0xCCA22538
	UINT32                                                   reserved56;	//0xCCA2253C
	UINT32                                                   reserved57;	//0xCCA22540
	UINT32                                                   reserved58;	//0xCCA22544
	UINT32                                                   reserved59;	//0xCCA22548
	UINT32                                                   reserved60;	//0xCCA2254C
	PE_O24_VSD_SHP_SHP_CTI_CTRL_00_T                       shp_cti_ctrl_00;	//0xCCA22550
	PE_O24_VSD_SHP_SHP_CTI_CTRL_01_T                       shp_cti_ctrl_01;	//0xCCA22554
	PE_O24_VSD_SHP_SHP_CTI_CTRL_02_T                       shp_cti_ctrl_02;	//0xCCA22558
	UINT32                                                   reserved61;	//0xCCA2255C
	PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_00_T           shp_frc_flick_ctrl_00;	//0xCCA22560
	PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_01_T           shp_frc_flick_ctrl_01;	//0xCCA22564
	PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_02_T           shp_frc_flick_ctrl_02;	//0xCCA22568
	PE_O24_VSD_SHP_SHP_FRC_FLICK_CTRL_03_T           shp_frc_flick_ctrl_03;	//0xCCA2256C
	PE_O24_VSD_SHP_SHP_TEMPORAL_MAP_00_T               shp_temporal_map_00;	//0xCCA22570
	PE_O24_VSD_SHP_SHP_TEMPORAL_MAP_01_T               shp_temporal_map_01;	//0xCCA22574
	PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_02_T             shp_frc_blur_ctrl_02;	//0xCCA22578
	PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_03_T             shp_frc_blur_ctrl_03;	//0xCCA2257C
	PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_04_T             shp_frc_blur_ctrl_04;	//0xCCA22580
	PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_05_T             shp_frc_blur_ctrl_05;	//0xCCA22584
	PE_O24_VSD_SHP_SHP_FRC_BLUR_CTRL_06_T             shp_frc_blur_ctrl_06;	//0xCCA22588
	UINT32                                                   reserved62;	//0xCCA2258C
	PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_00_T             shp_frc_halo_ctrl_00;	//0xCCA22590
	PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_01_T             shp_frc_halo_ctrl_01;	//0xCCA22594
	PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_02_T             shp_frc_halo_ctrl_02;	//0xCCA22598
	PE_O24_VSD_SHP_SHP_FRC_HALO_CTRL_03_T             shp_frc_halo_ctrl_03;	//0xCCA2259C
	PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_00_T               shp_frc_win_ctrl_00;	//0xCCA225A0
	PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_01_T               shp_frc_win_ctrl_01;	//0xCCA225A4
	PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_02_T               shp_frc_win_ctrl_02;	//0xCCA225A8
	PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_03_T               shp_frc_win_ctrl_03;	//0xCCA225AC
	PE_O24_VSD_SHP_SHP_FRC_WIN_CTRL_04_T               shp_frc_win_ctrl_04;	//0xCCA225B0
	UINT32                                                   reserved63;	//0xCCA225B4
	UINT32                                                   reserved64;	//0xCCA225B8
	UINT32                                                   reserved65;	//0xCCA225BC
	UINT32                                                   reserved66;	//0xCCA225C0
	UINT32                                                   reserved67;	//0xCCA225C4
	UINT32                                                   reserved68;	//0xCCA225C8
	UINT32                                                   reserved69;	//0xCCA225CC
	UINT32                                                   reserved70;	//0xCCA225D0
	UINT32                                                   reserved71;	//0xCCA225D4
	UINT32                                                   reserved72;	//0xCCA225D8
	UINT32                                                   reserved73;	//0xCCA225DC
	UINT32                                                   reserved74;	//0xCCA225E0
	UINT32                                                   reserved75;	//0xCCA225E4
	UINT32                                                   reserved76;	//0xCCA225E8
	UINT32                                                   reserved77;	//0xCCA225EC
	UINT32                                                   reserved78;	//0xCCA225F0
	UINT32                                                   reserved79;	//0xCCA225F4
	UINT32                                                   reserved80;	//0xCCA225F8
	UINT32                                                   reserved81;	//0xCCA225FC
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_00_T       shp_motion_gain_ctrl_00;	//0xCCA22600
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_01_T       shp_motion_gain_ctrl_01;	//0xCCA22604
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_02_T       shp_motion_gain_ctrl_02;	//0xCCA22608
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_03_T       shp_motion_gain_ctrl_03;	//0xCCA2260C
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_04_T       shp_motion_gain_ctrl_04;	//0xCCA22610
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_05_T       shp_motion_gain_ctrl_05;	//0xCCA22614
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_06_T       shp_motion_gain_ctrl_06;	//0xCCA22618
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_07_T       shp_motion_gain_ctrl_07;	//0xCCA2261C
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_08_T       shp_motion_gain_ctrl_08;	//0xCCA22620
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_09_T       shp_motion_gain_ctrl_09;	//0xCCA22624
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_0A_T       shp_motion_gain_ctrl_0a;	//0xCCA22628
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_0B_T       shp_motion_gain_ctrl_0b;	//0xCCA2262C
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_CTRL_0C_T       shp_motion_gain_ctrl_0c;	//0xCCA22630
	UINT32                                                   reserved82;	//0xCCA22634
	UINT32                                                   reserved83;	//0xCCA22638
	UINT32                                                   reserved84;	//0xCCA2263C
	PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_00_T       shp_motion_prot_ctrl_00;	//0xCCA22640
	PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_01_T       shp_motion_prot_ctrl_01;	//0xCCA22644
	PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_02_T       shp_motion_prot_ctrl_02;	//0xCCA22648
	PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_03_T       shp_motion_prot_ctrl_03;	//0xCCA2264C
	PE_O24_VSD_SHP_SHP_MOTION_PROT_CTRL_04_T       shp_motion_prot_ctrl_04;	//0xCCA22650
	UINT32                                                   reserved85;	//0xCCA22654
	UINT32                                                   reserved86;	//0xCCA22658
	UINT32                                                   reserved87;	//0xCCA2265C
	UINT32                                                   reserved88;	//0xCCA22660
	UINT32                                                   reserved89;	//0xCCA22664
	UINT32                                                   reserved90;	//0xCCA22668
	UINT32                                                   reserved91;	//0xCCA2266C
	PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_00_T               shp_mot_win_ctrl_00;	//0xCCA22670
	PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_01_T               shp_mot_win_ctrl_01;	//0xCCA22674
	PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_02_T               shp_mot_win_ctrl_02;	//0xCCA22678
	PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_03_T               shp_mot_win_ctrl_03;	//0xCCA2267C
	PE_O24_VSD_SHP_SHP_MOT_WIN_CTRL_04_T               shp_mot_win_ctrl_04;	//0xCCA22680
	UINT32                                                   reserved92;	//0xCCA22684
	UINT32                                                   reserved93;	//0xCCA22688
	UINT32                                                   reserved94;	//0xCCA2268C
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_00_T                       shp_obj_ctrl_00;	//0xCCA22690
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_01_T                       shp_obj_ctrl_01;	//0xCCA22694
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_02_T                       shp_obj_ctrl_02;	//0xCCA22698
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_03_T                       shp_obj_ctrl_03;	//0xCCA2269C
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_04_T                       shp_obj_ctrl_04;	//0xCCA226A0
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_05_T                       shp_obj_ctrl_05;	//0xCCA226A4
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_06_T                       shp_obj_ctrl_06;	//0xCCA226A8
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_07_T                       shp_obj_ctrl_07;	//0xCCA226AC
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_08_T                       shp_obj_ctrl_08;	//0xCCA226B0
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_09_T                       shp_obj_ctrl_09;	//0xCCA226B4
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_0A_T                       shp_obj_ctrl_0a;	//0xCCA226B8
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_0B_T                       shp_obj_ctrl_0b;	//0xCCA226BC
	PE_O24_VSD_SHP_SHP_OBJ_CTRL_0C_T                       shp_obj_ctrl_0c;	//0xCCA226C0
	UINT32                                                   reserved95;	//0xCCA226C4
	UINT32                                                   reserved96;	//0xCCA226C8
	UINT32                                                   reserved97;	//0xCCA226CC
	UINT32                                                   reserved98;	//0xCCA226D0
	UINT32                                                   reserved99;	//0xCCA226D4
	UINT32                                                  reserved100;	//0xCCA226D8
	UINT32                                                  reserved101;	//0xCCA226DC
	UINT32                                                  reserved102;	//0xCCA226E0
	UINT32                                                  reserved103;	//0xCCA226E4
	UINT32                                                  reserved104;	//0xCCA226E8
	UINT32                                                  reserved105;	//0xCCA226EC
	UINT32                                                  reserved106;	//0xCCA226F0
	UINT32                                                  reserved107;	//0xCCA226F4
	UINT32                                                  reserved108;	//0xCCA226F8
	UINT32                                                  reserved109;	//0xCCA226FC
	UINT32                                                  reserved110;	//0xCCA22700
	UINT32                                                  reserved111;	//0xCCA22704
	UINT32                                                  reserved112;	//0xCCA22708
	UINT32                                                  reserved113;	//0xCCA2270C
	UINT32                                                  reserved114;	//0xCCA22710
	UINT32                                                  reserved115;	//0xCCA22714
	UINT32                                                  reserved116;	//0xCCA22718
	UINT32                                                  reserved117;	//0xCCA2271C
	UINT32                                                  reserved118;	//0xCCA22720
	UINT32                                                  reserved119;	//0xCCA22724
	UINT32                                                  reserved120;	//0xCCA22728
	UINT32                                                  reserved121;	//0xCCA2272C
	UINT32                                                  reserved122;	//0xCCA22730
	UINT32                                                  reserved123;	//0xCCA22734
	UINT32                                                  reserved124;	//0xCCA22738
	UINT32                                                  reserved125;	//0xCCA2273C
	UINT32                                                  reserved126;	//0xCCA22740
	UINT32                                                  reserved127;	//0xCCA22744
	UINT32                                                  reserved128;	//0xCCA22748
	UINT32                                                  reserved129;	//0xCCA2274C
	UINT32                                                  reserved130;	//0xCCA22750
	UINT32                                                  reserved131;	//0xCCA22754
	UINT32                                                  reserved132;	//0xCCA22758
	UINT32                                                  reserved133;	//0xCCA2275C
	UINT32                                                  reserved134;	//0xCCA22760
	UINT32                                                  reserved135;	//0xCCA22764
	UINT32                                                  reserved136;	//0xCCA22768
	UINT32                                                  reserved137;	//0xCCA2276C
	UINT32                                                  reserved138;	//0xCCA22770
	UINT32                                                  reserved139;	//0xCCA22774
	UINT32                                                  reserved140;	//0xCCA22778
	UINT32                                                  reserved141;	//0xCCA2277C
	UINT32                                                  reserved142;	//0xCCA22780
	UINT32                                                  reserved143;	//0xCCA22784
	UINT32                                                  reserved144;	//0xCCA22788
	UINT32                                                  reserved145;	//0xCCA2278C
	UINT32                                                  reserved146;	//0xCCA22790
	UINT32                                                  reserved147;	//0xCCA22794
	UINT32                                                  reserved148;	//0xCCA22798
	UINT32                                                  reserved149;	//0xCCA2279C
	PE_O24_VSD_SHP_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCCA227A0
	PE_O24_VSD_SHP_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCCA227A4
	PE_O24_VSD_SHP_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCCA227A8
	PE_O24_VSD_SHP_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCCA227AC
	PE_O24_VSD_SHP_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCCA227B0
	PE_O24_VSD_SHP_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCCA227B4
	UINT32                                                  reserved150;	//0xCCA227B8
	UINT32                                                  reserved151;	//0xCCA227BC
	UINT32                                                  reserved152;	//0xCCA227C0
	UINT32                                                  reserved153;	//0xCCA227C4
	UINT32                                                  reserved154;	//0xCCA227C8
	UINT32                                                  reserved155;	//0xCCA227CC
	PE_O24_VSD_SHP_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCCA227D0
	PE_O24_VSD_SHP_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCCA227D4
	PE_O24_VSD_SHP_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCCA227D8
	PE_O24_VSD_SHP_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCCA227DC
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_STAT_00_T       shp_motion_gain_stat_00;	//0xCCA227E0
	PE_O24_VSD_SHP_SHP_MOTION_GAIN_STAT_01_T       shp_motion_gain_stat_01;	//0xCCA227E4
	PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_00_T           shp_core_edge_stat_00;	//0xCCA227E8
	PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_01_T           shp_core_edge_stat_01;	//0xCCA227EC
	PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_02_T           shp_core_edge_stat_02;	//0xCCA227F0
	PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_03_T           shp_core_edge_stat_03;	//0xCCA227F4
	PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_04_T           shp_core_edge_stat_04;	//0xCCA227F8
	PE_O24_VSD_SHP_SHP_CORE_EDGE_STAT_05_T           shp_core_edge_stat_05;	//0xCCA227FC
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_00_T           shp_core_tmap_stat_00;	//0xCCA22800
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_01_T           shp_core_tmap_stat_01;	//0xCCA22804
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_02_T           shp_core_tmap_stat_02;	//0xCCA22808
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_03_T           shp_core_tmap_stat_03;	//0xCCA2280C
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_04_T           shp_core_tmap_stat_04;	//0xCCA22810
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_05_T           shp_core_tmap_stat_05;	//0xCCA22814
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_06_T           shp_core_tmap_stat_06;	//0xCCA22818
	PE_O24_VSD_SHP_SHP_CORE_TMAP_STAT_07_T           shp_core_tmap_stat_07;	//0xCCA2281C
	PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_00_T             shp_face_win_ctrl_00;	//0xCCA22820
	PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_01_T             shp_face_win_ctrl_01;	//0xCCA22824
	PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_02_T             shp_face_win_ctrl_02;	//0xCCA22828
	PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_03_T             shp_face_win_ctrl_03;	//0xCCA2282C
	PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_04_T             shp_face_win_ctrl_04;	//0xCCA22830
	PE_O24_VSD_SHP_SHP_FACE_WIN_CTRL_05_T             shp_face_win_ctrl_05;	//0xCCA22834
	PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_00_T             shp_body_win_ctrl_00;	//0xCCA22838
	PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_01_T             shp_body_win_ctrl_01;	//0xCCA2283C
	PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_02_T             shp_body_win_ctrl_02;	//0xCCA22840
	PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_03_T             shp_body_win_ctrl_03;	//0xCCA22844
	PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_04_T             shp_body_win_ctrl_04;	//0xCCA22848
	PE_O24_VSD_SHP_SHP_BODY_WIN_CTRL_05_T             shp_body_win_ctrl_05;	//0xCCA2284C
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_00_T         shp_luma_blend_ctrl_00;	//0xCCA22850
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_01_T         shp_luma_blend_ctrl_01;	//0xCCA22854
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_02_T         shp_luma_blend_ctrl_02;	//0xCCA22858
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_03_T         shp_luma_blend_ctrl_03;	//0xCCA2285C
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_04_T         shp_luma_blend_ctrl_04;	//0xCCA22860
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_05_T         shp_luma_blend_ctrl_05;	//0xCCA22864
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_06_T         shp_luma_blend_ctrl_06;	//0xCCA22868
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_07_T         shp_luma_blend_ctrl_07;	//0xCCA2286C
	PE_O24_VSD_SHP_SHP_LUMA_BLEND_CTRL_08_T         shp_luma_blend_ctrl_08;	//0xCCA22870
	PE_O24_VSD_SHP_SHP_SMTH_MMD_CTRL_00_T             shp_smth_mmd_ctrl_00;	//0xCCA22874
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_00_T           shp_smth_gain_ctrl_00;	//0xCCA22878
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_01_T           shp_smth_gain_ctrl_01;	//0xCCA2287C
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_02_T           shp_smth_gain_ctrl_02;	//0xCCA22880
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_03_T           shp_smth_gain_ctrl_03;	//0xCCA22884
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_04_T           shp_smth_gain_ctrl_04;	//0xCCA22888
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_05_T           shp_smth_gain_ctrl_05;	//0xCCA2288C
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_06_T           shp_smth_gain_ctrl_06;	//0xCCA22890
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_07_T           shp_smth_gain_ctrl_07;	//0xCCA22894
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_08_T           shp_smth_gain_ctrl_08;	//0xCCA22898
	PE_O24_VSD_SHP_SHP_SMTH_GAIN_CTRL_09_T           shp_smth_gain_ctrl_09;	//0xCCA2289C
	PE_O24_VSD_SHP_SHP_SMTH_CON_CTRL_00_T             shp_smth_con_ctrl_00;	//0xCCA228A0
	UINT32                                                  reserved156;	//0xCCA228A4
	UINT32                                                  reserved157;	//0xCCA228A8
	UINT32                                                  reserved158;	//0xCCA228AC
	UINT32                                                  reserved159;	//0xCCA228B0
	UINT32                                                  reserved160;	//0xCCA228B4
	UINT32                                                  reserved161;	//0xCCA228B8
	UINT32                                                  reserved162;	//0xCCA228BC
	UINT32                                                  reserved163;	//0xCCA228C0
	UINT32                                                  reserved164;	//0xCCA228C4
	UINT32                                                  reserved165;	//0xCCA228C8
	UINT32                                                  reserved166;	//0xCCA228CC
	UINT32                                                  reserved167;	//0xCCA228D0
	UINT32                                                  reserved168;	//0xCCA228D4
	UINT32                                                  reserved169;	//0xCCA228D8
	UINT32                                                  reserved170;	//0xCCA228DC
	UINT32                                                  reserved171;	//0xCCA228E0
	UINT32                                                  reserved172;	//0xCCA228E4
	UINT32                                                  reserved173;	//0xCCA228E8
	UINT32                                                  reserved174;	//0xCCA228EC
	PE_O24_VSD_SHP_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCCA228F0
	PE_O24_VSD_SHP_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCCA228F4
	PE_O24_VSD_SHP_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCCA228F8
	PE_O24_VSD_SHP_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCCA228FC
}PE_VSD_SHP_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20500 RW 0x08700F00
	UINT32 reg_img_wid                      :13;	//(12:0,NA,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :3;
	UINT32 reg_img_hei                      :13;	//(28:16,NA,0x870) //vertical resolution   2160
	UINT32 resvd1                           :2;
	UINT32 reg_psp_detour_en                :1;	//(31:31,NA,0x0) //0 : obc enable	1 : obc_detour(obc : no dleay value 0, video : no delay in->out)
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20504 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,NA,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,NA,0x10) //Block size       16
	UINT32 resvd1                           :18;
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20508 RW 0x00
	UINT32 reg_vs_inv                       :1;	//(0,NA,0x00) //vs inversion
	UINT32 reg_psp_en                       :1;	//(1,NA,0x00) //1 : obc enable(obc : delay obc_res, video : delay in->out)	0 : obc_bypass(obc : delay value 0, video : delay in->out)
	UINT32 reg_hist_sel                     :2;	//(3:2,NA,0x00) //histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//(8:4,NA,0x00) //line 경계?�서 repeat ?�킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//(9,NA,0x00) //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//(14:10,NA,0x00) //frame 경계?�서 repeat ?�킬 v line 개수
	UINT32 reserved                         :1;	//(15,NA,0x00) //fg memory??mee off
	UINT32 reg_margin_hei                   :8;	//(23:16,NA,0x00) //edge extraction??V margin
	UINT32 reg_margin_wid                   :8;	//(31:24,NA,0x00) //edge extraction??H margin
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2050C RW 0x3F3F0000
	UINT32 y0_point                         :8;	//(7:0,NA,0x00) //control point of Y0
	UINT32 x0_point                         :8;	//(15:8,NA,0x00) //control point of X0
	UINT32 y1_point                         :8;	//(23:16,NA,0x3F) //control point of Y1
	UINT32 x1_point                         :8;	//(31:24,NA,0x3F) //control point of X1
	};
}PE_O24_VSD_OBC_BODY_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20510 RW 0x3F3F3F3F
	UINT32 y2_point                         :8;	//(7:0,NA,0x3F) //control point of Y2
	UINT32 x2_point                         :8;	//(15:8,NA,0x3F) //control point of X2
	UINT32 y3_point                         :8;	//(23:16,NA,0x3F) //control point of Y3
	UINT32 x3_point                         :8;	//(31:24,NA,0x3F) //control point of X3
	};
}PE_O24_VSD_OBC_BODY_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20514 RW 0x008700F0
	UINT32 reg_blk_wid                      :9;	//(8:0,NA,0xF0) //Number of hblock 240
	UINT32 resvd0                           :7;
	UINT32 reg_blk_hei                      :9;	//(24:16,NA,0x87) //Number of vblock 135
	UINT32 resvd1                           :7;
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20518 RW 0x00000000
	UINT32 reg_comp_img_wid                 :13;	//(12:0,NA,0x00) //horizontal composition resolution
	UINT32 resvd0                           :3;
	UINT32 reg_comp_img_hei                 :13;	//(28:16,NA,0x00) //vertical composition resolution
	UINT32 resvd1                           :2;
	UINT32 reg_comp_en                      :1;	//(31,NA,0x0) //Composition enable
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2051C RW 0x00000000
	UINT32 reg_comp_win_x0                  :13;	//(12:0,NA,0x0) //Composition window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y0                  :13;	//(28:16,NA,0x0) //Composition window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20520 RW 0x00000000
	UINT32 reg_comp_win_x1                  :13;	//(12:0,NA,0x0) //Composition window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y1                  :13;	//(28:16,NA,0x0) //Composition window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_PSP_CTRL06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20524 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0x0) //ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0x0) //ROI mask pixel value (Y)
	UINT32 reg_comp_value                   :8;	//(23:16,NA,0x0) //Composition pixel value (Y)
	UINT32 reg_comp_3x3_blur_value          :8;	//(31:24,NA,0x0) //Composition pixel value (Y) value * 4
	};
}PE_O24_VSD_OBC_BODY_PSP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20528 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :13;	//(12:0,NA,0x0) //ROI mask window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y0              :13;	//(28:16,NA,0x0) //ROI mask window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_PSP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2052C RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :13;	//(12:0,NA,0x0) //ROI mask window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y1              :13;	//(28:16,NA,0x0) //ROI mask window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_PSP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20530 RW 0x000E0E0E
	UINT32 reg_3x3_wgt_u1_00                :8;	//(7:0,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_u1_01                :8;	//(15:8,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_u1_02                :8;	//(23:16,NA,0x0E) //weight_value
	UINT32 resvd                            :7;
	UINT32 reg_3x3_wgt_bypass_en            :1;	//(31:31,NA,0x0) //0 : bypass value, 1 : weight value
	};
}PE_O24_VSD_OBC_BODY_PSP_3X3_BLUR_WGT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20534 RW 0x000E0F0E
	UINT32 reg_3x3_wgt_cc_00                :8;	//(7:0,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_cc_01                :8;	//(15:8,NA,0x0F) //weight_value
	UINT32 reg_3x3_wgt_cc_02                :8;	//(23:16,NA,0x0E) //weight_value
	UINT32 resvd                            :8;
	};
}PE_O24_VSD_OBC_BODY_PSP_3X3_BLUR_WGT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20538 RW 0x000E0E0E
	UINT32 reg_3x3_wgt_d1_00                :8;	//(7:0,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_d1_01                :8;	//(15:8,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_d1_02                :8;	//(23:16,NA,0x0E) //weight_value
	UINT32 resvd                            :8;
	};
}PE_O24_VSD_OBC_BODY_PSP_3X3_BLUR_WGT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2053C RW 0x00000000
	UINT32 reg_comp_3x3_blur_img_wid        :13;	//(12:0,NA,0x00) //horizontal composition resolution
	UINT32 resvd0                           :3;
	UINT32 reg_comp_3x3_blur_img_hei        :13;	//(28:16,NA,0x00) //vertical composition resolution
	UINT32 resvd1                           :2;
	UINT32 reg_comp_3x3_blur_en             :1;	//(31,NA,0x0) //Composition enable
	};
}PE_O24_VSD_OBC_BODY_PSP_COMP_3X3_BLUR_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20540 RW 0x00000000
	UINT32 reg_comp_3x3_blur_win_x0         :13;	//(12:0,NA,0x0) //Composition window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_comp_3x3_blur_win_y0         :13;	//(28:16,NA,0x0) //Composition window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_PSP_COMP_3X3_BLUR_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20544 RW 0x00000000
	UINT32 reg_comp_3x3_blur_win_x1         :13;	//(12:0,NA,0x0) //Composition window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_comp_3x3_blur_win_y1         :13;	//(28:16,NA,0x0) //Composition window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_PSP_COMP_3X3_BLUR_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20548 RW 0x00002802
	UINT32 reg_sel_sync_gain                :2;	//(1:0,NA,0x2) //depth_map prfetch start : 0 num, 1 vs, 2 va
	UINT32 reg_sel_sync_fifo                :2;	//(3:2,NA,0x0) //depth_map queue start : 0 num, 1 vs, 2 va
	UINT32 reg_debug_test                   :1;	//(4,NA,0x0) //
	UINT32 reg_start_pulse                  :1;	//(5,NA,0x0) //depth_map xd_arbit start : 0 vs, 1 va
	UINT32 reg_pic_init_sel                 :1;	//(6,NA,0x0) //3x3 blur, 3x3 sample_blur init : 0 vs, 1 va
	UINT32 resvd                            :1;
	UINT32 refine_num                       :12;	//(19:8,NA,0x28) //depth_map prfetch start : num*256
	UINT32 fifo_num                         :12;	//(31:20,NA,0x0) //depth_map queue start num : num*256
	};
}PE_O24_VSD_OBC_BODY_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2054C RW 0x00000000
	UINT32 reg_force_enable                 :1;	//(0:0,NA,0x0) //0 : off, 1 : on
	UINT32 resvd0                           :7;
	UINT32 reg_force_threshold              :8;	//(15:8,NA,0x0) //force threshold : 0~255
	UINT32 reg_force_value                  :8;	//(23:16,NA,0x0) //force value : 0~255
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_OBC_BODY_PSP_FORCE_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20570 RW 0x12C00080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x00) //reset cnt 12bit(0~4095)
	};
}PE_O24_VSD_OBC_BODY_REFINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20574 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
}PE_O24_VSD_OBC_BODY_REFINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20578 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
}PE_O24_VSD_OBC_BODY_REFINE_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2057C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O24_VSD_OBC_BODY_REFINE_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20580 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O24_VSD_OBC_BODY_REFINE_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20590 RW 0x0438_0780
	UINT32 reg_rgn_gain_width               :13;	//(12:0,NA,1920) //processing width (default : 3840/2 = 1920)
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_height              :13;	//(28:16,NA,1080) //processing height (default : 1080)
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20594 RW 0x0064_012C
	UINT32 reg_rgn_gain_position_x2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x1         :13;	//(28:16,NA,100) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20598 RW 0x027F_0354
	UINT32 reg_rgn_gain_position_x4         :13;	//(12:0,NA,852) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x3         :13;	//(28:16,NA,639) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2059C RW 0x0429_0519
	UINT32 reg_rgn_gain_position_x6         :13;	//(12:0,NA,1305) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x5         :13;	//(28:16,NA,1065) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205A0 RW 0x0609_06DE
	UINT32 reg_rgn_gain_position_x8         :13;	//(12:0,NA,1758) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x7         :13;	//(28:16,NA,1545) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205A4 RW 0x0096_012C
	UINT32 reg_rgn_gain_position_y2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y1         :13;	//(28:16,NA,150) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205A8 RW 0x039C_0514
	UINT32 reg_rgn_gain_position_y4         :13;	//(12:0,NA,1300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y3         :13;	//(28:16,NA,924) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205AC RW 0x0708_07D0
	UINT32 reg_rgn_gain_position_y6         :13;	//(12:0,NA,2000) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y5         :13;	//(28:16,NA,1800) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205B0 RW 0x6464_6464
	UINT32 reg_rgn_gain_41                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_31                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_21                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_11                  :8;	//(31:24,NA,100) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205B4 RW 0x6464_6464
	UINT32 reg_rgn_gain_81                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_71                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_61                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_51                  :8;	//(31:24,NA,100) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205B8 RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_42                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_32                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_22                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_12                  :8;	//(31:24,NA,110) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205BC RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_82                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_72                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_62                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_52                  :8;	//(31:24,NA,110) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205C0 RW 0x8080_8080
	UINT32 reg_rgn_gain_43                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_33                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_23                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_13                  :8;	//(31:24,NA,128) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205C4 RW 0x8080_8080
	UINT32 reg_rgn_gain_83                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_73                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_63                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_53                  :8;	//(31:24,NA,128) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205C8 RW 0x8080_8080
	UINT32 reg_rgn_gain_44                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_34                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_24                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_14                  :8;	//(31:24,NA,128) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205CC RW 0x8080_8080
	UINT32 reg_rgn_gain_84                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_74                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_64                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_54                  :8;	//(31:24,NA,128) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205D0 RW 0x6464_6464
	UINT32 reg_rgn_gain_45                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_35                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_25                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_15                  :8;	//(31:24,NA,100) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205D4 RW 0x6464_6464
	UINT32 reg_rgn_gain_85                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_75                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_65                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_55                  :8;	//(31:24,NA,100) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205D8 RW 0x5050_5050
	UINT32 reg_rgn_gain_46                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_36                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_26                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_16                  :8;	//(31:24,NA,80) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205DC RW 0x5050_5050
	UINT32 reg_rgn_gain_86                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_76                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_66                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_56                  :8;	//(31:24,NA,80) //
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205E0 RW 0x0000_8001
	UINT32 reg_rgn_gain_en                  :1;	//(0:0,NA,1) //
	UINT32 resvd0                           :7;
	UINT32 reg_rgn_gain_bnd_gain            :8;	//(15:8,NA,128) //
	UINT32 resvd1                           :16;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205E4 RW 0x0000_077F
	UINT32 reg_rgn_gain_bnd_x1              :13;	//(12:0,NA,1919) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_x0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205E8 RW 0x0000_0437
	UINT32 reg_rgn_gain_bnd_y1              :13;	//(12:0,NA,1079) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_y0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA205F0 RW 0x87800870
	UINT32 reg_lm_vsize                     :13;	//(12:0,NA,0x870) //Vsize of 2P input	2160
	UINT32 resvd0                           :3;
	UINT32 reg_lm_hsize                     :13;	//(28:16,NA,0x780) //Hsize of 2P input	3840/2P = 1920
	UINT32 resvd1                           :2;
	UINT32 buffer_en                        :1;	//(31:31,NA,0x1) //
	};
}PE_O24_VSD_OBC_BODY_BUFFER_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20700 RW 0x08700F00
	UINT32 reg_img_wid                      :13;	//(12:0,NA,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :3;
	UINT32 reg_img_hei                      :13;	//(28:16,NA,0x870) //vertical resolution   2160
	UINT32 resvd1                           :2;
	UINT32 reg_psp_detour_en                :1;	//(31:31,NA,0x0) //not_use
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20704 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,NA,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,NA,0x10) //Block size       16
	UINT32 resvd1                           :18;
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20708 RW 0x00
	UINT32 reg_vs_inv                       :1;	//(0,NA,0x00) //vs inversion
	UINT32 reg_psp_en                       :1;	//(1,NA,0x00) //1 : obc enable(obc : obc_res, video : delay in->out)	0 : obc_bypass(obc : value 0, video : delay in->out)
	UINT32 reg_hist_sel                     :2;	//(3:2,NA,0x00) //histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//(8:4,NA,0x00) //line 경계?�서 repeat ?�킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//(9,NA,0x00) //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//(14:10,NA,0x00) //frame 경계?�서 repeat ?�킬 v line 개수
	UINT32 reserved                         :1;	//(15,NA,0x00) //fg memory??mee off
	UINT32 reg_margin_hei                   :8;	//(23:16,NA,0x00) //edge extraction??V margin
	UINT32 reg_margin_wid                   :8;	//(31:24,NA,0x00) //edge extraction??H margin
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2070C RW 0x3F3F0000
	UINT32 y0_point                         :8;	//(7:0,NA,0x00) //control point of Y0
	UINT32 x0_point                         :8;	//(15:8,NA,0x00) //control point of X0
	UINT32 y1_point                         :8;	//(23:16,NA,0x3F) //control point of Y1
	UINT32 x1_point                         :8;	//(31:24,NA,0x3F) //control point of X1
	};
}PE_O24_VSD_OBC_HEAD_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20710 RW 0x3F3F3F3F
	UINT32 y2_point                         :8;	//(7:0,NA,0x3F) //control point of Y2
	UINT32 x2_point                         :8;	//(15:8,NA,0x3F) //control point of X2
	UINT32 y3_point                         :8;	//(23:16,NA,0x3F) //control point of Y3
	UINT32 x3_point                         :8;	//(31:24,NA,0x3F) //control point of X3
	};
}PE_O24_VSD_OBC_HEAD_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20714 RW 0x008700F0
	UINT32 reg_blk_wid                      :9;	//(8:0,NA,0xF0) //Number of hblock 240
	UINT32 resvd0                           :7;
	UINT32 reg_blk_hei                      :9;	//(24:16,NA,0x87) //Number of vblock 135
	UINT32 resvd1                           :7;
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20718 RW 0x00000000
	UINT32 reg_comp_img_wid                 :13;	//(12:0,NA,0x00) //horizontal composition resolution
	UINT32 resvd0                           :3;
	UINT32 reg_comp_img_hei                 :13;	//(28:16,NA,0x00) //vertical composition resolution
	UINT32 resvd1                           :2;
	UINT32 reg_comp_en                      :1;	//(31,NA,0x0) //Composition enable
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2071C RW 0x00000000
	UINT32 reg_comp_win_x0                  :13;	//(12:0,NA,0x0) //Composition window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y0                  :13;	//(28:16,NA,0x0) //Composition window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20720 RW 0x00000000
	UINT32 reg_comp_win_x1                  :13;	//(12:0,NA,0x0) //Composition window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y1                  :13;	//(28:16,NA,0x0) //Composition window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_HEAD_PSP_CTRL06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20724 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0x0) //ROI mask enable
	UINT32 resvd0                           :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0x0) //ROI mask pixel value (Y)
	UINT32 reg_comp_value                   :8;	//(23:16,NA,0x0) //Composition pixel value (Y)
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_OBC_HEAD_PSP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20728 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :13;	//(12:0,NA,0x0) //ROI mask window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y0              :13;	//(28:16,NA,0x0) //ROI mask window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_HEAD_PSP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2072C RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :13;	//(12:0,NA,0x0) //ROI mask window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y1              :13;	//(28:16,NA,0x0) //ROI mask window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O24_VSD_OBC_HEAD_PSP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20748 RW 0x00002802
	UINT32 reg_sel_sync_gain                :2;	//(1:0,NA,0x2) //refine 0 vs, 1 va, 2 num
	UINT32 reg_sel_sync_fifo                :2;	//(3:2,NA,0x0) //refine fifo 0 vs, 1 va, 2 num
	UINT32 reg_debug_test                   :1;	//(4,NA,0x0) //
	UINT32 reg_start_pulse                  :1;	//(5,NA,0x0) //0 vs, 1 va
	UINT32 reg_pic_init_sel                 :1;	//(6,NA,0x0) //3x3 blur 0 vs, 1 va
	UINT32 resvd                            :1;
	UINT32 refine_num                       :12;	//(19:8,NA,0x28) //start pulse from V falling : num*256
	UINT32 fifo_num                         :12;	//(31:20,NA,0x0) //start pulse from V falling : num*256
	};
}PE_O24_VSD_OBC_HEAD_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2074C RW 0x00000000
	UINT32 reg_force_enable                 :1;	//(0:0,NA,0x0) //0 : off, 1 : on
	UINT32 resvd0                           :7;
	UINT32 reg_force_threshold              :8;	//(15:8,NA,0x0) //force threshold : 0~255
	UINT32 reg_force_value                  :8;	//(23:16,NA,0x0) //force value : 0~255
	UINT32 resvd1                           :8;
	};
}PE_O24_VSD_OBC_HEAD_PSP_FORCE_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20770 RW 0x12C00080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x00) //reset cnt 12bit(0~4095)
	};
}PE_O24_VSD_OBC_HEAD_REFINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20774 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
}PE_O24_VSD_OBC_HEAD_REFINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20778 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
}PE_O24_VSD_OBC_HEAD_REFINE_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2077C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O24_VSD_OBC_HEAD_REFINE_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20780 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O24_VSD_OBC_HEAD_REFINE_CTRL4_T;

typedef struct {
	PE_O24_VSD_OBC_BODY_PSP_CTRL00_T                                psp_ctrl00;	//0xCCA20500
	PE_O24_VSD_OBC_BODY_PSP_CTRL01_T                                psp_ctrl01;	//0xCCA20504
	PE_O24_VSD_OBC_BODY_PSP_CTRL02_T                                psp_ctrl02;	//0xCCA20508
	PE_O24_VSD_OBC_BODY_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xCCA2050C
	PE_O24_VSD_OBC_BODY_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xCCA20510
	PE_O24_VSD_OBC_BODY_PSP_CTRL03_T                                psp_ctrl03;	//0xCCA20514
	PE_O24_VSD_OBC_BODY_PSP_CTRL04_T                                psp_ctrl04;	//0xCCA20518
	PE_O24_VSD_OBC_BODY_PSP_CTRL05_T                                psp_ctrl05;	//0xCCA2051C
	PE_O24_VSD_OBC_BODY_PSP_CTRL06_T                                psp_ctrl06;	//0xCCA20520
	PE_O24_VSD_OBC_BODY_PSP_ROI_MASK_CTRL_00_T            psp_roi_mask_ctrl_00;	//0xCCA20524
	PE_O24_VSD_OBC_BODY_PSP_ROI_MASK_CTRL_01_T            psp_roi_mask_ctrl_01;	//0xCCA20528
	PE_O24_VSD_OBC_BODY_PSP_ROI_MASK_CTRL_02_T            psp_roi_mask_ctrl_02;	//0xCCA2052C
	PE_O24_VSD_OBC_BODY_PSP_3X3_BLUR_WGT_00_T              psp_3x3_blur_wgt_00;	//0xCCA20530
	PE_O24_VSD_OBC_BODY_PSP_3X3_BLUR_WGT_01_T              psp_3x3_blur_wgt_01;	//0xCCA20534
	PE_O24_VSD_OBC_BODY_PSP_3X3_BLUR_WGT_02_T              psp_3x3_blur_wgt_02;	//0xCCA20538
	PE_O24_VSD_OBC_BODY_PSP_COMP_3X3_BLUR_00_T            psp_comp_3x3_blur_00;	//0xCCA2053C
	PE_O24_VSD_OBC_BODY_PSP_COMP_3X3_BLUR_01_T            psp_comp_3x3_blur_01;	//0xCCA20540
	PE_O24_VSD_OBC_BODY_PSP_COMP_3X3_BLUR_02_T            psp_comp_3x3_blur_02;	//0xCCA20544
	PE_O24_VSD_OBC_BODY_DISPLAY_DEBUG_MAP_T                  display_debug_map;	//0xCCA20548
	PE_O24_VSD_OBC_BODY_PSP_FORCE_VALUE_T                      psp_force_value;	//0xCCA2054C
	UINT32                                                    reserved0;	//0xCCA20550
	UINT32                                                    reserved1;	//0xCCA20554
	UINT32                                                    reserved2;	//0xCCA20558
	UINT32                                                    reserved3;	//0xCCA2055C
	UINT32                                                    reserved4;	//0xCCA20560
	UINT32                                                    reserved5;	//0xCCA20564
	UINT32                                                    reserved6;	//0xCCA20568
	UINT32                                                    reserved7;	//0xCCA2056C
	PE_O24_VSD_OBC_BODY_REFINE_CTRL0_T                            refine_ctrl0;	//0xCCA20570
	PE_O24_VSD_OBC_BODY_REFINE_CTRL1_T                            refine_ctrl1;	//0xCCA20574
	PE_O24_VSD_OBC_BODY_REFINE_CTRL2_T                            refine_ctrl2;	//0xCCA20578
	PE_O24_VSD_OBC_BODY_REFINE_CTRL3_T                            refine_ctrl3;	//0xCCA2057C
	PE_O24_VSD_OBC_BODY_REFINE_CTRL4_T                            refine_ctrl4;	//0xCCA20580
	UINT32                                                    reserved8;	//0xCCA20584
	UINT32                                                    reserved9;	//0xCCA20588
	UINT32                                                   reserved10;	//0xCCA2058C
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T obj_refine_body_gain_ctrl_00;	//0xCCA20590
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T obj_refine_body_gain_ctrl_01;	//0xCCA20594
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T obj_refine_body_gain_ctrl_02;	//0xCCA20598
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T obj_refine_body_gain_ctrl_03;	//0xCCA2059C
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T obj_refine_body_gain_ctrl_04;	//0xCCA205A0
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T obj_refine_body_gain_ctrl_05;	//0xCCA205A4
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T obj_refine_body_gain_ctrl_06;	//0xCCA205A8
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T obj_refine_body_gain_ctrl_07;	//0xCCA205AC
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T obj_refine_body_gain_ctrl_08;	//0xCCA205B0
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T obj_refine_body_gain_ctrl_09;	//0xCCA205B4
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T obj_refine_body_gain_ctrl_10;	//0xCCA205B8
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T obj_refine_body_gain_ctrl_11;	//0xCCA205BC
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T obj_refine_body_gain_ctrl_12;	//0xCCA205C0
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T obj_refine_body_gain_ctrl_13;	//0xCCA205C4
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T obj_refine_body_gain_ctrl_14;	//0xCCA205C8
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T obj_refine_body_gain_ctrl_15;	//0xCCA205CC
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T obj_refine_body_gain_ctrl_16;	//0xCCA205D0
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T obj_refine_body_gain_ctrl_17;	//0xCCA205D4
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T obj_refine_body_gain_ctrl_18;	//0xCCA205D8
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T obj_refine_body_gain_ctrl_19;	//0xCCA205DC
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T obj_refine_body_gain_ctrl_20;	//0xCCA205E0
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T obj_refine_body_gain_ctrl_21;	//0xCCA205E4
	PE_O24_VSD_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T obj_refine_body_gain_ctrl_22;	//0xCCA205E8
	UINT32                                                   reserved11;	//0xCCA205EC
	PE_O24_VSD_OBC_BODY_BUFFER_CTRL0_T                            buffer_ctrl0;	//0xCCA205F0
}PE_VSD_OBC_BODY_REG_O24_T;

typedef struct {
	PE_O24_VSD_OBC_HEAD_PSP_CTRL00_T                                psp_ctrl00;	//0xCCA20700
	PE_O24_VSD_OBC_HEAD_PSP_CTRL01_T                                psp_ctrl01;	//0xCCA20704
	PE_O24_VSD_OBC_HEAD_PSP_CTRL02_T                                psp_ctrl02;	//0xCCA20708
	PE_O24_VSD_OBC_HEAD_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xCCA2070C
	PE_O24_VSD_OBC_HEAD_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xCCA20710
	PE_O24_VSD_OBC_HEAD_PSP_CTRL03_T                                psp_ctrl03;	//0xCCA20714
	PE_O24_VSD_OBC_HEAD_PSP_CTRL04_T                                psp_ctrl04;	//0xCCA20718
	PE_O24_VSD_OBC_HEAD_PSP_CTRL05_T                                psp_ctrl05;	//0xCCA2071C
	PE_O24_VSD_OBC_HEAD_PSP_CTRL06_T                                psp_ctrl06;	//0xCCA20720
	PE_O24_VSD_OBC_HEAD_PSP_ROI_MASK_CTRL_00_T            psp_roi_mask_ctrl_00;	//0xCCA20724
	PE_O24_VSD_OBC_HEAD_PSP_ROI_MASK_CTRL_01_T            psp_roi_mask_ctrl_01;	//0xCCA20728
	PE_O24_VSD_OBC_HEAD_PSP_ROI_MASK_CTRL_02_T            psp_roi_mask_ctrl_02;	//0xCCA2072C
	UINT32                                                    reserved0;	//0xCCA20730
	UINT32                                                    reserved1;	//0xCCA20734
	UINT32                                                    reserved2;	//0xCCA20738
	UINT32                                                    reserved3;	//0xCCA2073C
	UINT32                                                    reserved4;	//0xCCA20740
	UINT32                                                    reserved5;	//0xCCA20744
	PE_O24_VSD_OBC_HEAD_DISPLAY_DEBUG_MAP_T                  display_debug_map;	//0xCCA20748
	PE_O24_VSD_OBC_HEAD_PSP_FORCE_VALUE_T                      psp_force_value;	//0xCCA2074C
	UINT32                                                    reserved6;	//0xCCA20750
	UINT32                                                    reserved7;	//0xCCA20754
	UINT32                                                    reserved8;	//0xCCA20758
	UINT32                                                    reserved9;	//0xCCA2075C
	UINT32                                                   reserved10;	//0xCCA20760
	UINT32                                                   reserved11;	//0xCCA20764
	UINT32                                                   reserved12;	//0xCCA20768
	UINT32                                                   reserved13;	//0xCCA2076C
	PE_O24_VSD_OBC_HEAD_REFINE_CTRL0_T                            refine_ctrl0;	//0xCCA20770
	PE_O24_VSD_OBC_HEAD_REFINE_CTRL1_T                            refine_ctrl1;	//0xCCA20774
	PE_O24_VSD_OBC_HEAD_REFINE_CTRL2_T                            refine_ctrl2;	//0xCCA20778
	PE_O24_VSD_OBC_HEAD_REFINE_CTRL3_T                            refine_ctrl3;	//0xCCA2077C
	PE_O24_VSD_OBC_HEAD_REFINE_CTRL4_T                            refine_ctrl4;	//0xCCA20780
}PE_VSD_OBC_HEAD_REG_O24_T;



typedef union {
	UINT32 udata32;
	struct {						//0xCCA20200 RW 0x8310_0000
	UINT32 resvd0                           :16;
	UINT32 reg_debug_mode                   :4;	//(19:16,NA,0x0) //0: normal	1: RCE_P ( R,G,B )	2: RCE_L ( R,G,B )	3: head_gain (W = R&G&B )	4: body_gain (W = R&G&B ) 	5: txtr_bain (W = R&G&B ) 	6: FACE+BODY (R = head_gain , G = body gain, B = 0)	7: FACE+BODY+TXTR (R = head_gain , G = body gain, B = txtr_gain)	8:face_body_blend (W = R&G&B )	9:final_blend(W = R&G&B )
	UINT32 reg_out_winmode_dly_sel          :2;	//(21:20,NA,0x1) //0: 43T (DTM 23T)	1: 21T (DTM 1T)	2: 22T (DTM 2T)
	UINT32 resvd1                           :2;
	UINT32 reg_ocsc_en                      :1;	//(24,NA,0x1) //
	UINT32 reg_icsc_en                      :1;	//(25,NA,0x1) //
	UINT32 resvd2                           :5;
	UINT32 reg_obe_en                       :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_000_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20204 RW 0x1E00_10E0
	UINT32 reg_heigt                        :16;	//(15:0,NA,0x10E0) //4320
	UINT32 reg_width                        :16;	//(31:16,NA,0x1E00) //7680
	};
}PE_O24_VSD_OBE_CTRL_001_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20208 RW 0x0000_0000
	UINT32 reg_bg_body_hist_th              :8;	//(7:0,NA,0x00) //
	UINT32 reg_bg_head_hist_th              :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_hist_th                 :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_hist_th                 :8;	//(31:24,NA,0x00) //
	};
}PE_O24_VSD_OBE_CTRL_002_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2020C RW 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 reg_bg_txtr_hist_th              :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_hist_th                 :8;	//(31:24,NA,0x00) //
	};
}PE_O24_VSD_OBE_CTRL_003_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20210 RW 0x0000_0000
	UINT32 reg_sat_prsv_ratio               :8;	//(7:0,NA,0x00) //
	UINT32 reg_hue_prsv_ratio               :8;	//(15:8,NA,0x00) //
	UINT32 reg_sat_prsv_en                  :1;	//(16,NA,0x0) //
	UINT32 reg_hue_prsv_en                  :1;	//(17,NA,0x0) //
	UINT32 resvd                            :13;
	UINT32 reg_hsp_en                       :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_004_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20214 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,NA,0x0000_0000) //
	};
}PE_O24_VSD_OBE_CTRL_005_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20218 RW 0x0000_0000
	UINT32 reg_ind_addr_ai                  :9;	//(8:0,NA,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_ind_ai                       :1;	//(12,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ind_load                     :1;	//(15,NA,0x0) //not use
	UINT32 resvd2                           :16;
	};
}PE_O24_VSD_OBE_IND_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2021C RW 0x0000_0000
	UINT32 reg_ind_data_wr                  :32;	//(31:0,NA,0x0000_0000) //not use
	};
}PE_O24_VSD_OBE_IND_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20220 RW 0x0000_0000
	UINT32 reg_ind_data_rd                  :32;	//(31:0,NA,0x0000_0000) //
	};
}PE_O24_VSD_OBE_IND_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20224 RW 0x1000_7D12
	UINT32 reg_icsc_coef1                   :15;	//(14:0,NA,0x7D12) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef0                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_009_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20228 RW 0x78A8_1000
	UINT32 reg_icsc_coef3                   :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef2                   :15;	//(30:16,NA,0x78A8) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_010_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2022C RW 0x1D0E_0000
	UINT32 reg_icsc_coef5                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef4                   :15;	//(30:16,NA,0x1D0E) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_011_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20230 RW 0x1000_0000
	UINT32 reg_icsc_coef7                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef6                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_012_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20234 RW 0x18A4_0000
	UINT32 resvd0                           :16;
	UINT32 reg_icsc_coef8                   :15;	//(30:16,NA,0x18A4) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_013_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20238 RW 0x0000_7E00
	UINT32 reg_icsc_ofst1                   :11;	//(10:0,NA,0x7E00) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_OBE_CTRL_014_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2023C RW 0x7E00_0000
	UINT32 reg_icsc_ofst3                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst2                   :11;	//(26:16,NA,0x7E00) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_OBE_CTRL_015_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20240 RW 0x0000_0000
	UINT32 reg_icsc_ofst5                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst4                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_OBE_CTRL_016_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20244 RW 0x09D3_00FE
	UINT32 reg_ocsc_coef1                   :15;	//(14:0,NA,0x00FE) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef0                   :15;	//(30:16,NA,0x09D3) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_017_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20248 RW 0x02EE_7A98
	UINT32 reg_ocsc_coef3                   :15;	//(14:0,NA,0x7A98) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef2                   :15;	//(30:16,NA,0x02EE) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_018_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2024C RW 0x0706_7E62
	UINT32 reg_ocsc_coef5                   :15;	//(14:0,NA,0x7E62) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef4                   :15;	//(30:16,NA,0x0706) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_019_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20250 RW 0x799E_7F5C
	UINT32 reg_ocsc_coef7                   :15;	//(14:0,NA,0x7F5C) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef6                   :15;	//(30:16,NA,0x799E) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_020_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20254 RW 0x0706_0000
	UINT32 resvd0                           :16;
	UINT32 reg_ocsc_coef8                   :15;	//(30:16,NA,0x0706) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_OBE_CTRL_021_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20258 RW 0x0000_0000
	UINT32 reg_ocsc_ofst1                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_OBE_CTRL_022_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2025C RW 0x0000_0040
	UINT32 reg_ocsc_ofst3                   :11;	//(10:0,NA,0x0040) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst2                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_OBE_CTRL_023_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20260 RW 0x0200_0200
	UINT32 reg_ocsc_ofst5                   :11;	//(10:0,NA,0x0200) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst4                   :11;	//(26:16,NA,0x0200) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_OBE_CTRL_024_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20264 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_txtr_master_gain             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x00) //
	};
}PE_O24_VSD_OBE_CTRL_025_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20268 RW 0x0080_0080
	UINT32 reg_final_blend_lut_y2           :8;	//(7:0,NA,0x80) //
	UINT32 reg_final_blend_lut_x2           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y3           :8;	//(23:16,NA,0x80) //
	UINT32 reg_final_blend_lut_x3           :8;	//(31:24,NA,0x00) //for RCE_P, RCE_L blending
	};
}PE_O24_VSD_OBE_CTRL_026_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2026C RW 0x0080_0080
	UINT32 reg_final_blend_lut_y0           :8;	//(7:0,NA,0x80) //
	UINT32 reg_final_blend_lut_x0           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y1           :8;	//(23:16,NA,0x80) //
	UINT32 reg_final_blend_lut_x1           :8;	//(31:24,NA,0x00) //for RCE_P, RCE_L blending
	};
}PE_O24_VSD_OBE_CTRL_027_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20270 RW 0x0000_0000
	UINT32 reg_head_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_028_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20274 RW 0x0000_0000
	UINT32 reg_head_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_029_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20278 RW 0x0000_0000
	UINT32 reg_head_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_030_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2027C RW 0x0000_0000
	UINT32 reg_head_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_031_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20280 RW 0x0000_0000
	UINT32 reg_head_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_032_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20284 RW 0x0000_0000
	UINT32 reg_head_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_033_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20288 RW 0x0000_0000
	UINT32 reg_head_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_034_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2028C RW 0x0000_0000
	UINT32 reg_head_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_035_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20290 RW 0x0000_0000
	UINT32 reg_head_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_036_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20294 RW 0x0000_0000
	UINT32 reg_head_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_037_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20298 RW 0x0000_0000
	UINT32 reg_head_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_038_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2029C RW 0x0000_0000
	UINT32 reg_head_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_039_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202A0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_040_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202A4 RW 0x0000_0000
	UINT32 reg_head_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_041_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202A8 RW 0x0000_0000
	UINT32 reg_head_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_042_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202AC RW 0x0000_0000
	UINT32 reg_head_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_043_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202B0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_044_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202B4 RW 0x0000_0000
	UINT32 reg_head_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_045_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202B8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_046_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202BC RW 0x0000_0000
	UINT32 reg_body_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_047_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202C0 RW 0x0000_0000
	UINT32 reg_body_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_048_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202C4 RW 0x0000_0000
	UINT32 reg_body_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_049_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202C8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_050_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202CC RW 0x0000_0000
	UINT32 reg_body_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_051_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202D0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_052_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202D4 RW 0x0000_0000
	UINT32 reg_body_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_053_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202D8 RW 0x0000_0000
	UINT32 reg_body_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_054_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202DC RW 0x0000_0000
	UINT32 reg_body_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_055_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202E0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_056_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202E4 RW 0x0000_0000
	UINT32 reg_body_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_057_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202E8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_058_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202EC RW 0x0000_0000
	UINT32 reg_body_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_059_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202F0 RW 0x0000_0000
	UINT32 reg_body_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_060_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202F4 RW 0x0000_0000
	UINT32 reg_body_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_061_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202F8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_062_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA202FC RW 0x0000_0000
	UINT32 reg_body_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_063_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20300 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_064_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20304 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_065_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20308 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_066_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2030C RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_067_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20310 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_068_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20314 RW 0x0000_0000
	UINT32 reg_potr_bg_r_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_r_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_069_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20318 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_070_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2031C RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_071_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20320 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_072_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20324 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_073_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20328 RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_074_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2032C RW 0x0000_0000
	UINT32 reg_potr_bg_g_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_g_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_075_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20330 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_076_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20334 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_077_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20338 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_078_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2033C RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_079_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20340 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_080_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20344 RW 0x0000_0000
	UINT32 reg_potr_bg_b_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_potr_bg_b_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_081_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20348 RW 0x0000_0000
	UINT32 reg_head_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_gain_lut_x3             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O24_VSD_OBE_CTRL_082_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2034C RW 0x0000_0000
	UINT32 reg_head_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_gain_lut_x1             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O24_VSD_OBE_CTRL_083_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20350 RW 0x0000_0000
	UINT32 reg_body_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_gain_lut_x3             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O24_VSD_OBE_CTRL_084_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20354 RW 0x0000_0000
	UINT32 reg_body_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_gain_lut_x1             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O24_VSD_OBE_CTRL_085_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20358 RW 0x0000_0000
	UINT32 reg_body_head_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x3             :8;	//(31:24,NA,0x00) //body-head
	};
}PE_O24_VSD_OBE_CTRL_086_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2035C RW 0x0000_0000
	UINT32 reg_body_head_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x1             :8;	//(31:24,NA,0x00) //
	};
}PE_O24_VSD_OBE_CTRL_087_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20360 RW 0x0000_0000
	UINT32 reg_head_body_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x3             :8;	//(31:24,NA,0x00) //head-body
	};
}PE_O24_VSD_OBE_CTRL_088_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20364 RW 0x0000_0000
	UINT32 reg_head_body_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x1             :8;	//(31:24,NA,0x00) //
	};
}PE_O24_VSD_OBE_CTRL_089_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20368 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_090_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2036C RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_091_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20370 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_092_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20374 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_093_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20378 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_094_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2037C RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_095_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20380 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_096_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20384 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_097_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20388 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_098_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2038C RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_099_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20390 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20394 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20398 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2039C RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203A0 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203A4 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203A8 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203AC RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203B0 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203B4 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203B8 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_110_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203BC RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_111_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203C0 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_112_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203C4 RW 0x0000_0000
	UINT32 reg_lnds_bg_r_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_r_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_113_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203C8 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_114_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203CC RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_115_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203D0 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_116_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203D4 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_117_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203D8 RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_118_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203DC RW 0x0000_0000
	UINT32 reg_lnds_bg_g_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_g_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_119_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203E0 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y0             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x0             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_120_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203E4 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y1             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x1             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_121_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203E8 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y2             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x2             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_122_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203EC RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y3             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x3             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_123_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203F0 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y4             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x4             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_124_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203F4 RW 0x0000_0000
	UINT32 reg_lnds_bg_b_lut_y5             :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_lnds_bg_b_lut_x5             :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_OBE_CTRL_125_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203F8 RW 0x0000_0000
	UINT32 reg_txtr_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x3             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O24_VSD_OBE_CTRL_126_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA203FC RW 0x0000_0000
	UINT32 reg_txtr_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x1             :8;	//(31:24,NA,0x00) //o22/f22 4pt
	};
}PE_O24_VSD_OBE_CTRL_127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20400 RW 0x0000_0000
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x000) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_128_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20404 RW 0x0780_0438
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_129_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20408 RW 0x0780_0438
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_130_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2040C RW 0x0F00_0870
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x870) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0xF00) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_131_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20410 RW 0x0000_0000
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x000) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_132_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20414 RW 0x0780_0438
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_133_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20418 RW 0x0780_0438
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x438) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x780) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_134_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2041C RW 0x0F00_0870
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x870) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0xF00) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_O24_VSD_OBE_CTRL_135_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20420 RW 0x0000_0000
	UINT32 reg_hist_body_gain_lut_y2        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x2        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y3        :8;	//(23:16,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x3        :8;	//(31:24,NA,0x00) //o22/f22 4pt for hist
	};
}PE_O24_VSD_OBE_CTRL_136_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20424 RW 0x0000_0000
	UINT32 reg_hist_body_gain_lut_y0        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x0        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y1        :8;	//(23:16,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x1        :8;	//(31:24,NA,0x00) //o22/f22 4pt for hist
	};
}PE_O24_VSD_OBE_CTRL_137_T;

typedef struct {
	PE_O24_VSD_OBE_CTRL_000_T                         reg_obe_ctrl_000;	//0xCCA20200
	PE_O24_VSD_OBE_CTRL_001_T                         reg_obe_ctrl_001;	//0xCCA20204
	PE_O24_VSD_OBE_CTRL_002_T                         reg_obe_ctrl_002;	//0xCCA20208
	PE_O24_VSD_OBE_CTRL_003_T                         reg_obe_ctrl_003;	//0xCCA2020C
	PE_O24_VSD_OBE_CTRL_004_T                         reg_obe_ctrl_004;	//0xCCA20210
	PE_O24_VSD_OBE_CTRL_005_T                         reg_obe_ctrl_005;	//0xCCA20214
	PE_O24_VSD_OBE_IND_CTRL_0_T                     reg_obe_ind_ctrl_0;	//0xCCA20218
	PE_O24_VSD_OBE_IND_CTRL_1_T                     reg_obe_ind_ctrl_1;	//0xCCA2021C
	PE_O24_VSD_OBE_IND_CTRL_2_T                     reg_obe_ind_ctrl_2;	//0xCCA20220
	PE_O24_VSD_OBE_CTRL_009_T                         reg_obe_ctrl_009;	//0xCCA20224
	PE_O24_VSD_OBE_CTRL_010_T                         reg_obe_ctrl_010;	//0xCCA20228
	PE_O24_VSD_OBE_CTRL_011_T                         reg_obe_ctrl_011;	//0xCCA2022C
	PE_O24_VSD_OBE_CTRL_012_T                         reg_obe_ctrl_012;	//0xCCA20230
	PE_O24_VSD_OBE_CTRL_013_T                         reg_obe_ctrl_013;	//0xCCA20234
	PE_O24_VSD_OBE_CTRL_014_T                         reg_obe_ctrl_014;	//0xCCA20238
	PE_O24_VSD_OBE_CTRL_015_T                         reg_obe_ctrl_015;	//0xCCA2023C
	PE_O24_VSD_OBE_CTRL_016_T                         reg_obe_ctrl_016;	//0xCCA20240
	PE_O24_VSD_OBE_CTRL_017_T                         reg_obe_ctrl_017;	//0xCCA20244
	PE_O24_VSD_OBE_CTRL_018_T                         reg_obe_ctrl_018;	//0xCCA20248
	PE_O24_VSD_OBE_CTRL_019_T                         reg_obe_ctrl_019;	//0xCCA2024C
	PE_O24_VSD_OBE_CTRL_020_T                         reg_obe_ctrl_020;	//0xCCA20250
	PE_O24_VSD_OBE_CTRL_021_T                         reg_obe_ctrl_021;	//0xCCA20254
	PE_O24_VSD_OBE_CTRL_022_T                         reg_obe_ctrl_022;	//0xCCA20258
	PE_O24_VSD_OBE_CTRL_023_T                         reg_obe_ctrl_023;	//0xCCA2025C
	PE_O24_VSD_OBE_CTRL_024_T                         reg_obe_ctrl_024;	//0xCCA20260
	PE_O24_VSD_OBE_CTRL_025_T                         reg_obe_ctrl_025;	//0xCCA20264
	PE_O24_VSD_OBE_CTRL_026_T                         reg_obe_ctrl_026;	//0xCCA20268
	PE_O24_VSD_OBE_CTRL_027_T                         reg_obe_ctrl_027;	//0xCCA2026C
	PE_O24_VSD_OBE_CTRL_028_T                         reg_obe_ctrl_028;	//0xCCA20270
	PE_O24_VSD_OBE_CTRL_029_T                         reg_obe_ctrl_029;	//0xCCA20274
	PE_O24_VSD_OBE_CTRL_030_T                         reg_obe_ctrl_030;	//0xCCA20278
	PE_O24_VSD_OBE_CTRL_031_T                         reg_obe_ctrl_031;	//0xCCA2027C
	PE_O24_VSD_OBE_CTRL_032_T                         reg_obe_ctrl_032;	//0xCCA20280
	PE_O24_VSD_OBE_CTRL_033_T                         reg_obe_ctrl_033;	//0xCCA20284
	PE_O24_VSD_OBE_CTRL_034_T                         reg_obe_ctrl_034;	//0xCCA20288
	PE_O24_VSD_OBE_CTRL_035_T                         reg_obe_ctrl_035;	//0xCCA2028C
	PE_O24_VSD_OBE_CTRL_036_T                         reg_obe_ctrl_036;	//0xCCA20290
	PE_O24_VSD_OBE_CTRL_037_T                         reg_obe_ctrl_037;	//0xCCA20294
	PE_O24_VSD_OBE_CTRL_038_T                         reg_obe_ctrl_038;	//0xCCA20298
	PE_O24_VSD_OBE_CTRL_039_T                         reg_obe_ctrl_039;	//0xCCA2029C
	PE_O24_VSD_OBE_CTRL_040_T                         reg_obe_ctrl_040;	//0xCCA202A0
	PE_O24_VSD_OBE_CTRL_041_T                         reg_obe_ctrl_041;	//0xCCA202A4
	PE_O24_VSD_OBE_CTRL_042_T                         reg_obe_ctrl_042;	//0xCCA202A8
	PE_O24_VSD_OBE_CTRL_043_T                         reg_obe_ctrl_043;	//0xCCA202AC
	PE_O24_VSD_OBE_CTRL_044_T                         reg_obe_ctrl_044;	//0xCCA202B0
	PE_O24_VSD_OBE_CTRL_045_T                         reg_obe_ctrl_045;	//0xCCA202B4
	PE_O24_VSD_OBE_CTRL_046_T                         reg_obe_ctrl_046;	//0xCCA202B8
	PE_O24_VSD_OBE_CTRL_047_T                         reg_obe_ctrl_047;	//0xCCA202BC
	PE_O24_VSD_OBE_CTRL_048_T                         reg_obe_ctrl_048;	//0xCCA202C0
	PE_O24_VSD_OBE_CTRL_049_T                         reg_obe_ctrl_049;	//0xCCA202C4
	PE_O24_VSD_OBE_CTRL_050_T                         reg_obe_ctrl_050;	//0xCCA202C8
	PE_O24_VSD_OBE_CTRL_051_T                         reg_obe_ctrl_051;	//0xCCA202CC
	PE_O24_VSD_OBE_CTRL_052_T                         reg_obe_ctrl_052;	//0xCCA202D0
	PE_O24_VSD_OBE_CTRL_053_T                         reg_obe_ctrl_053;	//0xCCA202D4
	PE_O24_VSD_OBE_CTRL_054_T                         reg_obe_ctrl_054;	//0xCCA202D8
	PE_O24_VSD_OBE_CTRL_055_T                         reg_obe_ctrl_055;	//0xCCA202DC
	PE_O24_VSD_OBE_CTRL_056_T                         reg_obe_ctrl_056;	//0xCCA202E0
	PE_O24_VSD_OBE_CTRL_057_T                         reg_obe_ctrl_057;	//0xCCA202E4
	PE_O24_VSD_OBE_CTRL_058_T                         reg_obe_ctrl_058;	//0xCCA202E8
	PE_O24_VSD_OBE_CTRL_059_T                         reg_obe_ctrl_059;	//0xCCA202EC
	PE_O24_VSD_OBE_CTRL_060_T                         reg_obe_ctrl_060;	//0xCCA202F0
	PE_O24_VSD_OBE_CTRL_061_T                         reg_obe_ctrl_061;	//0xCCA202F4
	PE_O24_VSD_OBE_CTRL_062_T                         reg_obe_ctrl_062;	//0xCCA202F8
	PE_O24_VSD_OBE_CTRL_063_T                         reg_obe_ctrl_063;	//0xCCA202FC
	PE_O24_VSD_OBE_CTRL_064_T                         reg_obe_ctrl_064;	//0xCCA20300
	PE_O24_VSD_OBE_CTRL_065_T                         reg_obe_ctrl_065;	//0xCCA20304
	PE_O24_VSD_OBE_CTRL_066_T                         reg_obe_ctrl_066;	//0xCCA20308
	PE_O24_VSD_OBE_CTRL_067_T                         reg_obe_ctrl_067;	//0xCCA2030C
	PE_O24_VSD_OBE_CTRL_068_T                         reg_obe_ctrl_068;	//0xCCA20310
	PE_O24_VSD_OBE_CTRL_069_T                         reg_obe_ctrl_069;	//0xCCA20314
	PE_O24_VSD_OBE_CTRL_070_T                         reg_obe_ctrl_070;	//0xCCA20318
	PE_O24_VSD_OBE_CTRL_071_T                         reg_obe_ctrl_071;	//0xCCA2031C
	PE_O24_VSD_OBE_CTRL_072_T                         reg_obe_ctrl_072;	//0xCCA20320
	PE_O24_VSD_OBE_CTRL_073_T                         reg_obe_ctrl_073;	//0xCCA20324
	PE_O24_VSD_OBE_CTRL_074_T                         reg_obe_ctrl_074;	//0xCCA20328
	PE_O24_VSD_OBE_CTRL_075_T                         reg_obe_ctrl_075;	//0xCCA2032C
	PE_O24_VSD_OBE_CTRL_076_T                         reg_obe_ctrl_076;	//0xCCA20330
	PE_O24_VSD_OBE_CTRL_077_T                         reg_obe_ctrl_077;	//0xCCA20334
	PE_O24_VSD_OBE_CTRL_078_T                         reg_obe_ctrl_078;	//0xCCA20338
	PE_O24_VSD_OBE_CTRL_079_T                         reg_obe_ctrl_079;	//0xCCA2033C
	PE_O24_VSD_OBE_CTRL_080_T                         reg_obe_ctrl_080;	//0xCCA20340
	PE_O24_VSD_OBE_CTRL_081_T                         reg_obe_ctrl_081;	//0xCCA20344
	PE_O24_VSD_OBE_CTRL_082_T                         reg_obe_ctrl_082;	//0xCCA20348
	PE_O24_VSD_OBE_CTRL_083_T                         reg_obe_ctrl_083;	//0xCCA2034C
	PE_O24_VSD_OBE_CTRL_084_T                         reg_obe_ctrl_084;	//0xCCA20350
	PE_O24_VSD_OBE_CTRL_085_T                         reg_obe_ctrl_085;	//0xCCA20354
	PE_O24_VSD_OBE_CTRL_086_T                         reg_obe_ctrl_086;	//0xCCA20358
	PE_O24_VSD_OBE_CTRL_087_T                         reg_obe_ctrl_087;	//0xCCA2035C
	PE_O24_VSD_OBE_CTRL_088_T                         reg_obe_ctrl_088;	//0xCCA20360
	PE_O24_VSD_OBE_CTRL_089_T                         reg_obe_ctrl_089;	//0xCCA20364
	PE_O24_VSD_OBE_CTRL_090_T                         reg_obe_ctrl_090;	//0xCCA20368
	PE_O24_VSD_OBE_CTRL_091_T                         reg_obe_ctrl_091;	//0xCCA2036C
	PE_O24_VSD_OBE_CTRL_092_T                         reg_obe_ctrl_092;	//0xCCA20370
	PE_O24_VSD_OBE_CTRL_093_T                         reg_obe_ctrl_093;	//0xCCA20374
	PE_O24_VSD_OBE_CTRL_094_T                         reg_obe_ctrl_094;	//0xCCA20378
	PE_O24_VSD_OBE_CTRL_095_T                         reg_obe_ctrl_095;	//0xCCA2037C
	PE_O24_VSD_OBE_CTRL_096_T                         reg_obe_ctrl_096;	//0xCCA20380
	PE_O24_VSD_OBE_CTRL_097_T                         reg_obe_ctrl_097;	//0xCCA20384
	PE_O24_VSD_OBE_CTRL_098_T                         reg_obe_ctrl_098;	//0xCCA20388
	PE_O24_VSD_OBE_CTRL_099_T                         reg_obe_ctrl_099;	//0xCCA2038C
	PE_O24_VSD_OBE_CTRL_100_T                         reg_obe_ctrl_100;	//0xCCA20390
	PE_O24_VSD_OBE_CTRL_101_T                         reg_obe_ctrl_101;	//0xCCA20394
	PE_O24_VSD_OBE_CTRL_102_T                         reg_obe_ctrl_102;	//0xCCA20398
	PE_O24_VSD_OBE_CTRL_103_T                         reg_obe_ctrl_103;	//0xCCA2039C
	PE_O24_VSD_OBE_CTRL_104_T                         reg_obe_ctrl_104;	//0xCCA203A0
	PE_O24_VSD_OBE_CTRL_105_T                         reg_obe_ctrl_105;	//0xCCA203A4
	PE_O24_VSD_OBE_CTRL_106_T                         reg_obe_ctrl_106;	//0xCCA203A8
	PE_O24_VSD_OBE_CTRL_107_T                         reg_obe_ctrl_107;	//0xCCA203AC
	PE_O24_VSD_OBE_CTRL_108_T                         reg_obe_ctrl_108;	//0xCCA203B0
	PE_O24_VSD_OBE_CTRL_109_T                         reg_obe_ctrl_109;	//0xCCA203B4
	PE_O24_VSD_OBE_CTRL_110_T                         reg_obe_ctrl_110;	//0xCCA203B8
	PE_O24_VSD_OBE_CTRL_111_T                         reg_obe_ctrl_111;	//0xCCA203BC
	PE_O24_VSD_OBE_CTRL_112_T                         reg_obe_ctrl_112;	//0xCCA203C0
	PE_O24_VSD_OBE_CTRL_113_T                         reg_obe_ctrl_113;	//0xCCA203C4
	PE_O24_VSD_OBE_CTRL_114_T                         reg_obe_ctrl_114;	//0xCCA203C8
	PE_O24_VSD_OBE_CTRL_115_T                         reg_obe_ctrl_115;	//0xCCA203CC
	PE_O24_VSD_OBE_CTRL_116_T                         reg_obe_ctrl_116;	//0xCCA203D0
	PE_O24_VSD_OBE_CTRL_117_T                         reg_obe_ctrl_117;	//0xCCA203D4
	PE_O24_VSD_OBE_CTRL_118_T                         reg_obe_ctrl_118;	//0xCCA203D8
	PE_O24_VSD_OBE_CTRL_119_T                         reg_obe_ctrl_119;	//0xCCA203DC
	PE_O24_VSD_OBE_CTRL_120_T                         reg_obe_ctrl_120;	//0xCCA203E0
	PE_O24_VSD_OBE_CTRL_121_T                         reg_obe_ctrl_121;	//0xCCA203E4
	PE_O24_VSD_OBE_CTRL_122_T                         reg_obe_ctrl_122;	//0xCCA203E8
	PE_O24_VSD_OBE_CTRL_123_T                         reg_obe_ctrl_123;	//0xCCA203EC
	PE_O24_VSD_OBE_CTRL_124_T                         reg_obe_ctrl_124;	//0xCCA203F0
	PE_O24_VSD_OBE_CTRL_125_T                         reg_obe_ctrl_125;	//0xCCA203F4
	PE_O24_VSD_OBE_CTRL_126_T                         reg_obe_ctrl_126;	//0xCCA203F8
	PE_O24_VSD_OBE_CTRL_127_T                         reg_obe_ctrl_127;	//0xCCA203FC
	PE_O24_VSD_OBE_CTRL_128_T                         reg_obe_ctrl_128;	//0xCCA20400
	PE_O24_VSD_OBE_CTRL_129_T                         reg_obe_ctrl_129;	//0xCCA20404
	PE_O24_VSD_OBE_CTRL_130_T                         reg_obe_ctrl_130;	//0xCCA20408
	PE_O24_VSD_OBE_CTRL_131_T                         reg_obe_ctrl_131;	//0xCCA2040C
	PE_O24_VSD_OBE_CTRL_132_T                         reg_obe_ctrl_132;	//0xCCA20410
	PE_O24_VSD_OBE_CTRL_133_T                         reg_obe_ctrl_133;	//0xCCA20414
	PE_O24_VSD_OBE_CTRL_134_T                         reg_obe_ctrl_134;	//0xCCA20418
	PE_O24_VSD_OBE_CTRL_135_T                         reg_obe_ctrl_135;	//0xCCA2041C
	PE_O24_VSD_OBE_CTRL_136_T                         reg_obe_ctrl_136;	//0xCCA20420
	PE_O24_VSD_OBE_CTRL_137_T                         reg_obe_ctrl_137;	//0xCCA20424
}PE_VSD_OBE_REG_O24_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C00 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O24_VSD_DTM_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C04 RW 0x0438_0780
	UINT32 width                            :12;	//(11:0,NA,0x780) //width
	UINT32 resvd0                           :4;
	UINT32 height                           :12;	//(27:16,NA,0x438) //height
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C08 RW 0x0100_0000
	UINT32 resvd0                           :1;
	UINT32 reg_va_cnt_en                    :1;	//(1,NA,0x0) //1: va count enable for DTM_TOP_CTRL_03
	UINT32 dtm_disp_detour                  :1;	//(2,NA,0x0) //1: display tone mapping detour
	UINT32 resvd1                           :1;
	UINT32 reg_use_own_lut_en               :1;	//(4,NA,0x0) //0:use luminanace LUT channel G hif	1:use own LUT hif(B/R)(WR only)
	UINT32 resvd2                           :19;
	UINT32 reg_master_en                    :1;	//(24,NA,0x1) //LUT master enable
	UINT32 resvd3                           :7;
	};
}PE_O24_VSD_DTM_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C0C RO 0x0000_0000
	UINT32 vcnt                             :12;	//(11:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(12,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(13,NA,0x0) //Vertical Active at PE1 output
	UINT32 resvd0                           :2;
	UINT32 vcnt2                            :12;	//(27:16,NA,0x0) //vertical line number
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C10 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_O24_VSD_DTM_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C14 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,NA,0x14) //vdpulse position for register loading
	};
}PE_O24_VSD_DTM_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C20 RW 0x0000_0000
	UINT32 dummy_00                         :32;	//(31:0,NA,0x0) //
	};
}PE_O24_VSD_DTM_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C24 RW 0x0000_0000
	UINT32 dummy_01                         :32;	//(31:0,NA,0x0) //
	};
}PE_O24_VSD_DTM_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C28 RW 0x0000_0000
	UINT32 dummy_02                         :32;	//(31:0,NA,0x0) //
	};
}PE_O24_VSD_DTM_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C2C RW 0x0000_0000
	UINT32 dummy_03                         :32;	//(31:0,NA,0x0) //
	};
}PE_O24_VSD_DTM_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C40 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0,NA,0x1) //
	UINT32 resvd                            :31;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C44 RW 0x12A0_7C98
	UINT32 r_csc1st_coef1                   :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C48 RW 0x7775_12A0
	UINT32 r_csc1st_coef3                   :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C4C RW 0x21D7_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C50 RW 0x12A0_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C54 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C58 RW 0x07C0_0600
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C5C RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C60 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_VSD_DTM_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C70 RW 0x0000_0000
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
}PE_O24_VSD_DTM_LLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C74 RW 0x0000_0000
	UINT32 win_w0_x0                        :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0                        :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C78 RW 0x0437_077F
	UINT32 win_w0_x1                        :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1                        :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C7C RW 0x0000_0000
	UINT32 win_w1_x0                        :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0                        :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C80 RW 0x0437_077F
	UINT32 win_w1_x1                        :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1                        :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_LLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C84 RW 0x03FF_03FF
	UINT32 hif_llut_wdata_y_33rd            :10;	//(9:0,NA,0x3FF) //Y coordinate of 33rd control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut_wdata_x_33rd            :10;	//(25:16,NA,0x3FF) //X coordinate of 33rd control point
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_DTM_LLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C88 RW 0x0000_8000
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
}PE_O24_VSD_DTM_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C8C RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut0_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_DTM_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C90 RW 0x0000_8000
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
}PE_O24_VSD_DTM_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C94 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut1_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_DTM_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C98 RW 0x0000_8000
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
}PE_O24_VSD_DTM_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20C9C RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut2_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD_DTM_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CA0 RW 0x0000_0000
	UINT32 reg_lut_lum_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_lum_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_lum_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CA4 RW 0x0000_0000
	UINT32 reg_lut_lum_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_lum_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_lum_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CA8 RW 0x0000_0000
	UINT32 reg_lut_sat_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_sat_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_sat_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CAC RW 0x0000_0000
	UINT32 reg_lut_sat_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_sat_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_sat_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CE0 RW 0xFF00_0000
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
}PE_O24_VSD_DTM_HUE_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CE4 RW 0x00000000
	UINT32 reg_lum_lut_input_sel            :1;	//(0,NA,0x0) //0:Y 1:max_rgb
	UINT32 resvd0                           :3;
	UINT32 reg_hue_lut_gain_sel             :1;	//(4,NA,0x0) //0:luma 1:saturation
	UINT32 resvd1                           :3;
	UINT32 reg_sat_lut_gain_sel             :1;	//(8,NA,0x0) //0:luma 1:saturation
	UINT32 resvd2                           :23;
	};
}PE_O24_VSD_DTM_HUE_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CE8 RW 0xFF00_0000
	UINT32 smooth_gain                      :8;	//(7:0,NA,0xFF) //smooth gain
	UINT32 smooth_dbg                       :1;	//(8,NA,0x0) //debug blur image
	UINT32 resvd                            :23;
	};
}PE_O24_VSD_DTM_SMT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CF0 RW 0x0000_0000
	UINT32 odd_win_w0_x0                    :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y0                    :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_ODD_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CF4 RW 0x0437_077F
	UINT32 odd_win_w0_x1                    :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y1                    :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_ODD_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CF8 RW 0x0000_0000
	UINT32 odd_win_w1_x0                    :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y0                    :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_ODD_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20CFC RW 0x0437_077F
	UINT32 odd_win_w1_x1                    :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y1                    :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_VSD_DTM_ODD_LLUT_CTRL_04_T;

typedef struct {
	PE_O24_VSD_DTM_TOP_CTRL_00_T                           dtm_top_ctrl_00;	//0xCCA20C00
	PE_O24_VSD_DTM_TOP_CTRL_01_T                           dtm_top_ctrl_01;	//0xCCA20C04
	PE_O24_VSD_DTM_TOP_CTRL_02_T                           dtm_top_ctrl_02;	//0xCCA20C08
	PE_O24_VSD_DTM_TOP_CTRL_03_T                           dtm_top_ctrl_03;	//0xCCA20C0C
	PE_O24_VSD_DTM_TOP_CTRL_04_T                           dtm_top_ctrl_04;	//0xCCA20C10
	PE_O24_VSD_DTM_TOP_CTRL_05_T                           dtm_top_ctrl_05;	//0xCCA20C14
	UINT32                                                    reserved0;	//0xCCA20C18
	UINT32                                                    reserved1;	//0xCCA20C1C
	PE_O24_VSD_DTM_FSW_CTRL_00_T                           dtm_fsw_ctrl_00;	//0xCCA20C20
	PE_O24_VSD_DTM_FSW_CTRL_01_T                           dtm_fsw_ctrl_01;	//0xCCA20C24
	PE_O24_VSD_DTM_FSW_CTRL_02_T                           dtm_fsw_ctrl_02;	//0xCCA20C28
	PE_O24_VSD_DTM_FSW_CTRL_03_T                           dtm_fsw_ctrl_03;	//0xCCA20C2C
	UINT32                                                    reserved2;	//0xCCA20C30
	UINT32                                                    reserved3;	//0xCCA20C34
	UINT32                                                    reserved4;	//0xCCA20C38
	UINT32                                                    reserved5;	//0xCCA20C3C
	PE_O24_VSD_DTM_CSC1_CTRL_00_T                         dtm_csc1_ctrl_00;	//0xCCA20C40
	PE_O24_VSD_DTM_CSC1_CTRL_01_T                         dtm_csc1_ctrl_01;	//0xCCA20C44
	PE_O24_VSD_DTM_CSC1_CTRL_02_T                         dtm_csc1_ctrl_02;	//0xCCA20C48
	PE_O24_VSD_DTM_CSC1_CTRL_03_T                         dtm_csc1_ctrl_03;	//0xCCA20C4C
	PE_O24_VSD_DTM_CSC1_CTRL_04_T                         dtm_csc1_ctrl_04;	//0xCCA20C50
	PE_O24_VSD_DTM_CSC1_CTRL_05_T                         dtm_csc1_ctrl_05;	//0xCCA20C54
	PE_O24_VSD_DTM_CSC1_CTRL_06_T                         dtm_csc1_ctrl_06;	//0xCCA20C58
	PE_O24_VSD_DTM_CSC1_CTRL_07_T                         dtm_csc1_ctrl_07;	//0xCCA20C5C
	PE_O24_VSD_DTM_CSC1_CTRL_08_T                         dtm_csc1_ctrl_08;	//0xCCA20C60
	UINT32                                                    reserved6;	//0xCCA20C64
	UINT32                                                    reserved7;	//0xCCA20C68
	UINT32                                                    reserved8;	//0xCCA20C6C
	PE_O24_VSD_DTM_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0xCCA20C70
	PE_O24_VSD_DTM_LLUT_CTRL_01_T                         dtm_llut_ctrl_01;	//0xCCA20C74
	PE_O24_VSD_DTM_LLUT_CTRL_02_T                         dtm_llut_ctrl_02;	//0xCCA20C78
	PE_O24_VSD_DTM_LLUT_CTRL_03_T                         dtm_llut_ctrl_03;	//0xCCA20C7C
	PE_O24_VSD_DTM_LLUT_CTRL_04_T                         dtm_llut_ctrl_04;	//0xCCA20C80
	PE_O24_VSD_DTM_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0xCCA20C84
	PE_O24_VSD_DTM_LLUT0_IA_CTRL_T                       dtm_llut0_ia_ctrl;	//0xCCA20C88
	PE_O24_VSD_DTM_LLUT0_IA_DATA_T                       dtm_llut0_ia_data;	//0xCCA20C8C
	PE_O24_VSD_DTM_LLUT1_IA_CTRL_T                       dtm_llut1_ia_ctrl;	//0xCCA20C90
	PE_O24_VSD_DTM_LLUT1_IA_DATA_T                       dtm_llut1_ia_data;	//0xCCA20C94
	PE_O24_VSD_DTM_LLUT2_IA_CTRL_T                       dtm_llut2_ia_ctrl;	//0xCCA20C98
	PE_O24_VSD_DTM_LLUT2_IA_DATA_T                       dtm_llut2_ia_data;	//0xCCA20C9C
	PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_00_T           dtm_lut_lum_sat_ctrl_00;	//0xCCA20CA0
	PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_01_T           dtm_lut_lum_sat_ctrl_01;	//0xCCA20CA4
	PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_02_T           dtm_lut_lum_sat_ctrl_02;	//0xCCA20CA8
	PE_O24_VSD_DTM_LUT_LUM_SAT_CTRL_03_T           dtm_lut_lum_sat_ctrl_03;	//0xCCA20CAC
	UINT32                                                    reserved9;	//0xCCA20CB0
	UINT32                                                   reserved10;	//0xCCA20CB4
	UINT32                                                   reserved11;	//0xCCA20CB8
	UINT32                                                   reserved12;	//0xCCA20CBC
	UINT32                                                   reserved13;	//0xCCA20CC0
	UINT32                                                   reserved14;	//0xCCA20CC4
	UINT32                                                   reserved15;	//0xCCA20CC8
	UINT32                                                   reserved16;	//0xCCA20CCC
	UINT32                                                   reserved17;	//0xCCA20CD0
	UINT32                                                   reserved18;	//0xCCA20CD4
	UINT32                                                   reserved19;	//0xCCA20CD8
	UINT32                                                   reserved20;	//0xCCA20CDC
	PE_O24_VSD_DTM_HUE_SAT_CTRL_00_T                   dtm_hue_sat_ctrl_00;	//0xCCA20CE0
	PE_O24_VSD_DTM_HUE_SAT_CTRL_01_T                   dtm_hue_sat_ctrl_01;	//0xCCA20CE4
	PE_O24_VSD_DTM_SMT_CTRL_00_T                           dtm_smt_ctrl_00;	//0xCCA20CE8
	UINT32                                                   reserved21;	//0xCCA20CEC
	PE_O24_VSD_DTM_ODD_LLUT_CTRL_01_T                 dtm_odd_llut_ctrl_01;	//0xCCA20CF0
	PE_O24_VSD_DTM_ODD_LLUT_CTRL_02_T                 dtm_odd_llut_ctrl_02;	//0xCCA20CF4
	PE_O24_VSD_DTM_ODD_LLUT_CTRL_03_T                 dtm_odd_llut_ctrl_03;	//0xCCA20CF8
	PE_O24_VSD_DTM_ODD_LLUT_CTRL_04_T                 dtm_odd_llut_ctrl_04;	//0xCCA20CFC
}PE_VSD_DTM_REG_O24_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC824900 RW 0x0001_5101
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
	UINT32 resvd1                           :3;
	UINT32 reg_mvf_vfast                    :1;	//(20:20,NA,0) //MV V-fast mode (0: off, 1: on)
	UINT32 resvd2                           :11;
	};
}PE_O24_AMG0_HEAD_AMG_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824904 RW 0x0087_00F0
	UINT32 reg_wid                          :8;	//(7:0,NA,240) //processing width (default: 240)
	UINT32 resvd0                           :8;
	UINT32 reg_hei                          :8;	//(23:16,NA,135) //processing height (default: 135)
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_AMG_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824908 RW 0x0118_0001
	UINT32 reg_use_extern_valid             :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_use_blank_period_cnt         :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_AMG0_HEAD_AMG_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82490C RW 0x3210_0064
	UINT32 reg_pic_delay_d2i                :16;	//(15:0,NA,100) //Delay of done to next init
	UINT32 reg_pic_delay_i2s                :8;	//(23:16,NA,16) //Delay of init to start
	UINT32 reg_flush_cnt                    :8;	//(31:24,NA,50) //Flush counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824910 RW 0x0001_0000
	UINT32 reg_mif_urgency                  :1;	//(0:0,NA,0) //Urgency = mif_bundle[59]
	UINT32 resvd0                           :7;
	UINT32 reg_mif_prefetch_line            :8;	//(15:8,NA,0) //MV pre-fetch line count
	UINT32 reg_mvf_prec                     :1;	//(16:16,NA,1) //MV precision (0: L0, 1: L1)
	UINT32 resvd1                           :15;
	};
}PE_O24_AMG0_HEAD_AMG_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824914 RW 0x0000_0000
	UINT32 reg_force_mvf_mv_x               :8;	//(7:0,NA,0) //Force MVF MVX
	UINT32 reg_force_mvf_mv_y               :8;	//(15:8,NA,0) //Force MVF MVY
	UINT32 reg_force_mvf_mv_mode            :2;	//(17:16,NA,0) //Force MVF MV mode
	UINT32 resvd                            :13;
	UINT32 reg_force_mvf_enable             :1;	//(31:31,NA,0) //Force MVF enable
	};
}PE_O24_AMG0_HEAD_AMG_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824918 RW 0x0000_0000
	UINT32 reg_pat_iir1_en                  :1;	//(0:0,NA,0) //Input IIR (run1,seg) pattern enable
	UINT32 reg_pat_iir2_en                  :1;	//(1:1,NA,0) //Input IIR (run2,head) pattern enable
	UINT32 reg_pat_iir3_en                  :1;	//(2:2,NA,0) //Input IIR (run3,seg) pattern enable
	UINT32 reg_pat_iir4_en                  :1;	//(3:3,NA,0) //Input IIR (run4,body) pattern enable
	UINT32 resvd0                           :12;
	UINT32 reg_pat_out1_en                  :1;	//(16:16,NA,0) //Output (run1,mc) pattern enable
	UINT32 reg_pat_out2_en                  :1;	//(17:17,NA,0) //Output (run2,head) pattern enable
	UINT32 reg_pat_out3_en                  :1;	//(18:18,NA,0) //Output (run3,basic) pattern enable
	UINT32 reg_pat_out4_en                  :1;	//(19:19,NA,0) //Output (run4,body) pattern enable
	UINT32 resvd1                           :12;
	};
}PE_O24_AMG0_HEAD_PAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824920 RW 0x0242_0242
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
}PE_O24_AMG0_HEAD_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824924 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0: Y	1: Cb	2: Cr	3: Depth
	UINT32 resvd                            :30;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824928 RO 0x0000_0000
	UINT32 reg_read_hist_00_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 0)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_00_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 0)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82492C RO 0x0000_0000
	UINT32 reg_read_hist_01_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 1)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_01_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 1)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824930 RO 0x0000_0000
	UINT32 reg_read_hist_02_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 2)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_02_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 2)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824934 RO 0x0000_0000
	UINT32 reg_read_hist_03_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 3)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_03_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 3)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824938 RO 0x0000_0000
	UINT32 reg_read_hist_04_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 4)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_04_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 4)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82493C RO 0x0000_0000
	UINT32 reg_read_hist_05_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 5)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_05_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 5)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824940 RO 0x0000_0000
	UINT32 reg_read_hist_06_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 6)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_06_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 6)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824944 RO 0x0000_0000
	UINT32 reg_read_hist_07_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 7)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_07_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 7)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824948 RO 0x0000_0000
	UINT32 reg_read_hist_08_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 8)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_08_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 8)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82494C RO 0x0000_0000
	UINT32 reg_read_hist_09_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 9)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_09_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 9)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824950 RO 0x0000_0000
	UINT32 reg_read_hist_10_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 10)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_10_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 10)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824954 RO 0x0000_0000
	UINT32 reg_read_hist_11_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 11)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_11_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 11)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824958 RO 0x0000_0000
	UINT32 reg_read_hist_12_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 12)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_12_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 12)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82495C RO 0x0000_0000
	UINT32 reg_read_hist_13_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 13)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_13_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 13)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824960 RO 0x0000_0000
	UINT32 reg_read_hist_14_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 14)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_14_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 14)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824964 RO 0x0000_0000
	UINT32 reg_read_hist_15_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 15)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_15_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 15)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824968 RO 0x0000_0000
	UINT32 reg_read_hist_16_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 16)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_16_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 16)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82496C RO 0x0000_0000
	UINT32 reg_read_hist_17_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 17)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_17_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 17)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824970 RO 0x0000_0000
	UINT32 reg_read_hist_18_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 18)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_18_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 18)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824974 RO 0x0000_0000
	UINT32 reg_read_hist_19_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 19)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_19_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 19)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824978 RO 0x0000_0000
	UINT32 reg_read_hist_20_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 20)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_20_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 20)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82497C RO 0x0000_0000
	UINT32 reg_read_hist_21_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 21)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_21_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 21)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824980 RO 0x0000_0000
	UINT32 reg_read_hist_22_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 22)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_22_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 22)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824984 RO 0x0000_0000
	UINT32 reg_read_hist_23_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 23)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_23_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 23)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824988 RO 0x0000_0000
	UINT32 reg_read_hist_24_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 24)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_24_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 24)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82498C RO 0x0000_0000
	UINT32 reg_read_hist_25_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 25)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_25_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 25)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824990 RO 0x0000_0000
	UINT32 reg_read_hist_26_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 26)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_26_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 26)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824994 RO 0x0000_0000
	UINT32 reg_read_hist_27_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 27)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_27_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 27)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824998 RO 0x0000_0000
	UINT32 reg_read_hist_28_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 28)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_28_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 28)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82499C RO 0x0000_0000
	UINT32 reg_read_hist_29_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 29)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_29_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 29)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249A0 RO 0x0000_0000
	UINT32 reg_read_hist_30_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 30)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_30_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 30)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249A4 RO 0x0000_0000
	UINT32 reg_read_hist_31_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 31)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_31_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 31)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG0_HEAD_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249B0 RW 0x0000_0101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0: Probability map	1: Ellipse gain map	2: Probability map (FG)	3: Probability map (BG)	4: Probability map (diff)	5: Box map	6: Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,0) //Object map output mux selection	0: HEAD/BODY	1: Blending	2: Depth only	3: Adding
	UINT32 resvd3                           :18;
	};
}PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249B4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
}PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249B8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249BC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249C0 RW 0x0000_0000
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
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249C4 RW 0x0000_0000
	UINT32 reg_box_fg_cand_w1               :8;	//(7:0,NA,0) //Box (FG candidate) position, w, start
	UINT32 reg_box_fg_cand_w2               :8;	//(15:8,NA,0) //Box (FG candidate) position, w, end
	UINT32 reg_box_fg_cand_h1               :8;	//(23:16,NA,0) //Box (FG candidate) position, h, start
	UINT32 reg_box_fg_cand_h2               :8;	//(31:24,NA,0) //Box (FG candidate) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249C8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249CC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249D0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249D4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249D8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249DC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249E0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249E4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249E8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249EC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249F0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8249F4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
}PE_O24_AMG0_HEAD_BOX_SET_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A00 RW 0x0000_0000
	UINT32 reg_fg_cand_e_mul_a              :9;	//(8:0,NA,0) //Ellipse (FG candidate) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_fg_cand_e_mul_b              :9;	//(24:16,NA,0) //Ellipse (FG candidate) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_fg_cand_ellipse_en           :1;	//(31:31,NA,0) //Ellipse (FG candidate) gain gen enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A04 RW 0x0000_0000
	UINT32 reg_fg_cand_ellipse_master       :8;	//(7:0,NA,0) //Ellipse (FG candidate) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_fg_cand_ellipse_offset       :8;	//(23:16,NA,0) //Ellipse (FG candidate) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 0) ellipse to rect disable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 1) ellipse to rect disable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 2) ellipse to rect disable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 3) ellipse to rect disable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
}PE_O24_AMG0_HEAD_ELLIPSE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
}PE_O24_AMG0_HEAD_LUT_PROB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
}PE_O24_AMG0_HEAD_LUT_PROB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824A80 RW 0x0000_00CC
	UINT32 reg_blur_vcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
}PE_O24_AMG0_HEAD_BLUR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824B20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0: use manual value	1: use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0: use IIR result	1: use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
}PE_O24_AMG0_HEAD_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824B24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
}PE_O24_AMG0_HEAD_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824B30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
}PE_O24_AMG0_HEAD_LUT_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824B34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
}PE_O24_AMG0_HEAD_LUT_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824B38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
}PE_O24_AMG0_HEAD_LUT_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BB0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :8;	//(7:0,NA,0) //Top input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :8;	//(15:8,NA,0) //Top input (pel, Y) previous frame vertical counter
	UINT32 reg_mon_in_pel_y_vert_cnt        :8;	//(23:16,NA,0) //Top input (pel, Y) vertical counter
	UINT32 reg_mon_in_pel_y_hori_cnt        :8;	//(31:24,NA,0) //Top input (pel, Y) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BB4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :8;	//(7:0,NA,0) //Top input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :8;	//(15:8,NA,0) //Top input (pel, C) previous frame vertical counter
	UINT32 reg_mon_in_pel_c_vert_cnt        :8;	//(23:16,NA,0) //Top input (pel, C) vertical counter
	UINT32 reg_mon_in_pel_c_hori_cnt        :8;	//(31:24,NA,0) //Top input (pel, C) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BB8 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :8;	//(7:0,NA,0) //Top input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :8;	//(15:8,NA,0) //Top input (depth map) previous frame vertical counter
	UINT32 reg_mon_in_depth_vert_cnt        :8;	//(23:16,NA,0) //Top input (depth map) vertical counter
	UINT32 reg_mon_in_depth_hori_cnt        :8;	//(31:24,NA,0) //Top input (depth map) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BBC RO 0x0000_0000
	UINT32 reg_mon_in_mc_sucfail            :8;	//(7:0,NA,0) //Top input (MC map) success/fail monitoring register
	UINT32 reg_mon_in_mc_fin_vert           :8;	//(15:8,NA,0) //Top input (MC map) previous frame vertical counter
	UINT32 reg_mon_in_mc_vert_cnt           :8;	//(23:16,NA,0) //Top input (MC map) vertical counter
	UINT32 reg_mon_in_mc_hori_cnt           :8;	//(31:24,NA,0) //Top input (MC map) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BC0 RO 0x0000_0000
	UINT32 reg_mon_in_basic_sucfail         :8;	//(7:0,NA,0) //Top input (Basic map) success/fail monitoring register
	UINT32 reg_mon_in_basic_fin_vert        :8;	//(15:8,NA,0) //Top input (Basic map) previous frame vertical counter
	UINT32 reg_mon_in_basic_vert_cnt        :8;	//(23:16,NA,0) //Top input (Basic map) vertical counter
	UINT32 reg_mon_in_basic_hori_cnt        :8;	//(31:24,NA,0) //Top input (Basic map) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BC4 RO 0x0000_0000
	UINT32 reg_mon_in_iir_sucfail           :8;	//(7:0,NA,0) //Top input (IIR feedback) success/fail monitoring register
	UINT32 reg_mon_in_iir_fin_vert          :8;	//(15:8,NA,0) //Top input (IIR feedback) previous frame vertical counter
	UINT32 reg_mon_in_iir_vert_cnt          :8;	//(23:16,NA,0) //Top input (IIR feedback) vertical counter
	UINT32 reg_mon_in_iir_hori_cnt          :8;	//(31:24,NA,0) //Top input (IIR feedback) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BC8 RO 0x0000_0000
	UINT32 reg_mon_out_iir_sucfail          :8;	//(7:0,NA,0) //Top output (IIR out) success/fail monitoring register
	UINT32 reg_mon_out_iir_fin_vert         :8;	//(15:8,NA,0) //Top output (IIR out) previous frame vertical counter
	UINT32 reg_mon_out_iir_vert_cnt         :8;	//(23:16,NA,0) //Top output (IIR out) vertical counter
	UINT32 reg_mon_out_iir_hori_cnt         :8;	//(31:24,NA,0) //Top output (IIR out) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BCC RO 0x0000_0000
	UINT32 reg_run_1st_flag                 :1;	//(0:0,NA,0) //Top 1st-run done pulse
	UINT32 reg_run_2nd_flag                 :1;	//(1:1,NA,0) //Top 2nd-run done pulse (core 2nd-run and mifw done)
	UINT32 reg_run_3rd_flag                 :1;	//(2:2,NA,0) //Top 3rd-run done pulse
	UINT32 reg_run_4th_flag                 :1;	//(3:3,NA,0) //Top 4th-run done pulse (core 4rd-run and mifw done)
	UINT32 reg_done_intr_1st                :1;	//(4:4,NA,0) //Top 1st-run done flag
	UINT32 reg_done_intr_2nd                :1;	//(5:5,NA,0) //Top 2nd-run done flag
	UINT32 reg_done_intr_3rd                :1;	//(6:6,NA,0) //Top 3rd-run done flag
	UINT32 reg_done_intr_4th                :1;	//(7:7,NA,0) //Top 4th-run done flag
	UINT32 reg_amg_done_flag                :1;	//(8:8,NA,0) //AMG core done flag
	UINT32 reg_grm_done_flag                :1;	//(9:9,NA,0) //GRM core done flag
	UINT32 reg_mtb_done_flag                :1;	//(10:10,NA,0) //MTB core done flag
	UINT32 reg_mif_done_flag                :1;	//(11:11,NA,0) //MIF write done flag
	UINT32 reg_abnomral_init_oc             :1;	//(12:12,NA,0) //Abnormal init occurred
	UINT32 resvd                            :19;
	};
}PE_O24_AMG0_HEAD_AMG_TOP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BD0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_sucfail           :8;	//(7:0,NA,0) //Core input (pel) success/fail monitoring register
	UINT32 reg_mon_in_pel_fin_vert          :8;	//(15:8,NA,0) //Core input (pel) previous frame vertical counter
	UINT32 reg_mon_in_pel_vert_cnt          :8;	//(23:16,NA,0) //Core input (pel) vertical counter
	UINT32 reg_mon_in_pel_hori_cnt          :8;	//(31:24,NA,0) //Core input (pel) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BD4 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :8;	//(7:0,NA,0) //Core input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :8;	//(15:8,NA,0) //Core input (depth map) previous frame vertical counter
	UINT32 reg_mon_in_depth_vert_cnt        :8;	//(23:16,NA,0) //Core input (depth map) vertical counter
	UINT32 reg_mon_in_depth_hori_cnt        :8;	//(31:24,NA,0) //Core input (depth map) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BD8 RO 0x0000_0000
	UINT32 reg_mon_in_grm_sucfail           :8;	//(7:0,NA,0) //Core input (GRM) success/fail monitoring register
	UINT32 reg_mon_in_grm_fin_vert          :8;	//(15:8,NA,0) //Core input (GRM) previous frame vertical counter
	UINT32 reg_mon_in_grm_vert_cnt          :8;	//(23:16,NA,0) //Core input (GRM) vertical counter
	UINT32 reg_mon_in_grm_hori_cnt          :8;	//(31:24,NA,0) //Core input (GRM) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BDC RO 0x0000_0000
	UINT32 reg_mon_in_mtb_sucfail           :8;	//(7:0,NA,0) //Core input (MTB) success/fail monitoring register
	UINT32 reg_mon_in_mtb_fin_vert          :8;	//(15:8,NA,0) //Core input (MTB) previous frame vertical counter
	UINT32 reg_mon_in_mtb_vert_cnt          :8;	//(23:16,NA,0) //Core input (MTB) vertical counter
	UINT32 reg_mon_in_mtb_hori_cnt          :8;	//(31:24,NA,0) //Core input (MTB) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BE0 RO 0x0000_0000
	UINT32 reg_mon_in_iir_sucfail           :8;	//(7:0,NA,0) //Core input (IIR feedback) success/fail monitoring register
	UINT32 reg_mon_in_iir_fin_vert          :8;	//(15:8,NA,0) //Core input (IIR feedback) previous frame vertical counter
	UINT32 reg_mon_in_iir_vert_cnt          :8;	//(23:16,NA,0) //Core input (IIR feedback) vertical counter
	UINT32 reg_mon_in_iir_hori_cnt          :8;	//(31:24,NA,0) //Core input (IIR feedback) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BE4 RO 0x0000_0000
	UINT32 reg_mon_out_iir_sucfail          :8;	//(7:0,NA,0) //Core output (IIR out) success/fail monitoring register
	UINT32 reg_mon_out_iir_fin_vert         :8;	//(15:8,NA,0) //Core output (IIR out) previous frame vertical counter
	UINT32 reg_mon_out_iir_vert_cnt         :8;	//(23:16,NA,0) //Core output (IIR out) vertical counter
	UINT32 reg_mon_out_iir_hori_cnt         :8;	//(31:24,NA,0) //Core output (IIR out) horizontal counter
	};
}PE_O24_AMG0_HEAD_AMG_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_AMG0_HEAD_AMG_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_AMG0_HEAD_AMG_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_AMG0_HEAD_AMG_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824BFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_AMG0_HEAD_AMG_FSW_CTRL_03_T;

typedef struct {
	PE_O24_AMG0_HEAD_AMG_TOP_CTRL_00_T                     amg_top_ctrl_00;	//0xCC824900
	PE_O24_AMG0_HEAD_AMG_TOP_CTRL_01_T                     amg_top_ctrl_01;	//0xCC824904
	PE_O24_AMG0_HEAD_AMG_TOP_CTRL_02_T                     amg_top_ctrl_02;	//0xCC824908
	PE_O24_AMG0_HEAD_AMG_TOP_CTRL_03_T                     amg_top_ctrl_03;	//0xCC82490C
	PE_O24_AMG0_HEAD_AMG_TOP_CTRL_04_T                     amg_top_ctrl_04;	//0xCC824910
	PE_O24_AMG0_HEAD_AMG_TOP_CTRL_05_T                     amg_top_ctrl_05;	//0xCC824914
	PE_O24_AMG0_HEAD_PAT_CTRL_00_T                             pat_ctrl_00;	//0xCC824918
	UINT32                                                    reserved0;	//0xCC82491C
	PE_O24_AMG0_HEAD_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xCC824920
	PE_O24_AMG0_HEAD_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xCC824924
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_00_T                 histogram_stat_00;	//0xCC824928
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_01_T                 histogram_stat_01;	//0xCC82492C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_02_T                 histogram_stat_02;	//0xCC824930
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_03_T                 histogram_stat_03;	//0xCC824934
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_04_T                 histogram_stat_04;	//0xCC824938
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_05_T                 histogram_stat_05;	//0xCC82493C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_06_T                 histogram_stat_06;	//0xCC824940
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_07_T                 histogram_stat_07;	//0xCC824944
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_08_T                 histogram_stat_08;	//0xCC824948
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_09_T                 histogram_stat_09;	//0xCC82494C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_10_T                 histogram_stat_10;	//0xCC824950
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_11_T                 histogram_stat_11;	//0xCC824954
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_12_T                 histogram_stat_12;	//0xCC824958
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_13_T                 histogram_stat_13;	//0xCC82495C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_14_T                 histogram_stat_14;	//0xCC824960
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_15_T                 histogram_stat_15;	//0xCC824964
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_16_T                 histogram_stat_16;	//0xCC824968
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_17_T                 histogram_stat_17;	//0xCC82496C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_18_T                 histogram_stat_18;	//0xCC824970
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_19_T                 histogram_stat_19;	//0xCC824974
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_20_T                 histogram_stat_20;	//0xCC824978
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_21_T                 histogram_stat_21;	//0xCC82497C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_22_T                 histogram_stat_22;	//0xCC824980
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_23_T                 histogram_stat_23;	//0xCC824984
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_24_T                 histogram_stat_24;	//0xCC824988
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_25_T                 histogram_stat_25;	//0xCC82498C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_26_T                 histogram_stat_26;	//0xCC824990
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_27_T                 histogram_stat_27;	//0xCC824994
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_28_T                 histogram_stat_28;	//0xCC824998
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_29_T                 histogram_stat_29;	//0xCC82499C
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_30_T                 histogram_stat_30;	//0xCC8249A0
	PE_O24_AMG0_HEAD_HISTOGRAM_STAT_31_T                 histogram_stat_31;	//0xCC8249A4
	UINT32                                                    reserved1;	//0xCC8249A8
	UINT32                                                    reserved2;	//0xCC8249AC
	PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xCC8249B0
	PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xCC8249B4
	PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xCC8249B8
	PE_O24_AMG0_HEAD_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xCC8249BC
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_00_T                     box_set_ctrl_00;	//0xCC8249C0
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_01_T                     box_set_ctrl_01;	//0xCC8249C4
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_02_T                     box_set_ctrl_02;	//0xCC8249C8
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_03_T                     box_set_ctrl_03;	//0xCC8249CC
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_04_T                     box_set_ctrl_04;	//0xCC8249D0
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_05_T                     box_set_ctrl_05;	//0xCC8249D4
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_06_T                     box_set_ctrl_06;	//0xCC8249D8
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_07_T                     box_set_ctrl_07;	//0xCC8249DC
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_08_T                     box_set_ctrl_08;	//0xCC8249E0
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_09_T                     box_set_ctrl_09;	//0xCC8249E4
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_10_T                     box_set_ctrl_10;	//0xCC8249E8
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_11_T                     box_set_ctrl_11;	//0xCC8249EC
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_12_T                     box_set_ctrl_12;	//0xCC8249F0
	PE_O24_AMG0_HEAD_BOX_SET_CTRL_13_T                     box_set_ctrl_13;	//0xCC8249F4
	UINT32                                                    reserved3;	//0xCC8249F8
	UINT32                                                    reserved4;	//0xCC8249FC
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xCC824A00
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xCC824A04
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xCC824A08
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xCC824A0C
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xCC824A10
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xCC824A14
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xCC824A18
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xCC824A1C
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xCC824A20
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xCC824A24
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xCC824A28
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xCC824A2C
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xCC824A30
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xCC824A34
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xCC824A38
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xCC824A3C
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xCC824A40
	PE_O24_AMG0_HEAD_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xCC824A44
	UINT32                                                    reserved5;	//0xCC824A48
	UINT32                                                    reserved6;	//0xCC824A4C
	PE_O24_AMG0_HEAD_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xCC824A50
	PE_O24_AMG0_HEAD_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xCC824A54
	UINT32                                                    reserved7;	//0xCC824A58
	UINT32                                                    reserved8;	//0xCC824A5C
	PE_O24_AMG0_HEAD_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xCC824A60
	PE_O24_AMG0_HEAD_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xCC824A64
	PE_O24_AMG0_HEAD_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xCC824A68
	PE_O24_AMG0_HEAD_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xCC824A6C
	PE_O24_AMG0_HEAD_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xCC824A70
	PE_O24_AMG0_HEAD_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xCC824A74
	PE_O24_AMG0_HEAD_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xCC824A78
	PE_O24_AMG0_HEAD_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xCC824A7C
	PE_O24_AMG0_HEAD_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xCC824A80
	UINT32                                                    reserved9;	//0xCC824A84
	UINT32                                                   reserved10;	//0xCC824A88
	UINT32                                                   reserved11;	//0xCC824A8C
	UINT32                                                   reserved12;	//0xCC824A90
	UINT32                                                   reserved13;	//0xCC824A94
	UINT32                                                   reserved14;	//0xCC824A98
	UINT32                                                   reserved15;	//0xCC824A9C
	UINT32                                                   reserved16;	//0xCC824AA0
	UINT32                                                   reserved17;	//0xCC824AA4
	UINT32                                                   reserved18;	//0xCC824AA8
	UINT32                                                   reserved19;	//0xCC824AAC
	UINT32                                                   reserved20;	//0xCC824AB0
	UINT32                                                   reserved21;	//0xCC824AB4
	UINT32                                                   reserved22;	//0xCC824AB8
	UINT32                                                   reserved23;	//0xCC824ABC
	UINT32                                                   reserved24;	//0xCC824AC0
	UINT32                                                   reserved25;	//0xCC824AC4
	UINT32                                                   reserved26;	//0xCC824AC8
	UINT32                                                   reserved27;	//0xCC824ACC
	UINT32                                                   reserved28;	//0xCC824AD0
	UINT32                                                   reserved29;	//0xCC824AD4
	UINT32                                                   reserved30;	//0xCC824AD8
	UINT32                                                   reserved31;	//0xCC824ADC
	UINT32                                                   reserved32;	//0xCC824AE0
	UINT32                                                   reserved33;	//0xCC824AE4
	UINT32                                                   reserved34;	//0xCC824AE8
	UINT32                                                   reserved35;	//0xCC824AEC
	UINT32                                                   reserved36;	//0xCC824AF0
	UINT32                                                   reserved37;	//0xCC824AF4
	UINT32                                                   reserved38;	//0xCC824AF8
	UINT32                                                   reserved39;	//0xCC824AFC
	UINT32                                                   reserved40;	//0xCC824B00
	UINT32                                                   reserved41;	//0xCC824B04
	UINT32                                                   reserved42;	//0xCC824B08
	UINT32                                                   reserved43;	//0xCC824B0C
	UINT32                                                   reserved44;	//0xCC824B10
	UINT32                                                   reserved45;	//0xCC824B14
	UINT32                                                   reserved46;	//0xCC824B18
	UINT32                                                   reserved47;	//0xCC824B1C
	PE_O24_AMG0_HEAD_IIR_CTRL_00_T                             iir_ctrl_00;	//0xCC824B20
	PE_O24_AMG0_HEAD_IIR_CTRL_01_T                             iir_ctrl_01;	//0xCC824B24
	UINT32                                                   reserved48;	//0xCC824B28
	UINT32                                                   reserved49;	//0xCC824B2C
	PE_O24_AMG0_HEAD_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xCC824B30
	PE_O24_AMG0_HEAD_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xCC824B34
	PE_O24_AMG0_HEAD_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xCC824B38
	UINT32                                                   reserved50;	//0xCC824B3C
	UINT32                                                   reserved51;	//0xCC824B40
	UINT32                                                   reserved52;	//0xCC824B44
	UINT32                                                   reserved53;	//0xCC824B48
	UINT32                                                   reserved54;	//0xCC824B4C
	UINT32                                                   reserved55;	//0xCC824B50
	UINT32                                                   reserved56;	//0xCC824B54
	UINT32                                                   reserved57;	//0xCC824B58
	UINT32                                                   reserved58;	//0xCC824B5C
	UINT32                                                   reserved59;	//0xCC824B60
	UINT32                                                   reserved60;	//0xCC824B64
	UINT32                                                   reserved61;	//0xCC824B68
	UINT32                                                   reserved62;	//0xCC824B6C
	UINT32                                                   reserved63;	//0xCC824B70
	UINT32                                                   reserved64;	//0xCC824B74
	UINT32                                                   reserved65;	//0xCC824B78
	UINT32                                                   reserved66;	//0xCC824B7C
	UINT32                                                   reserved67;	//0xCC824B80
	UINT32                                                   reserved68;	//0xCC824B84
	UINT32                                                   reserved69;	//0xCC824B88
	UINT32                                                   reserved70;	//0xCC824B8C
	UINT32                                                   reserved71;	//0xCC824B90
	UINT32                                                   reserved72;	//0xCC824B94
	UINT32                                                   reserved73;	//0xCC824B98
	UINT32                                                   reserved74;	//0xCC824B9C
	UINT32                                                   reserved75;	//0xCC824BA0
	UINT32                                                   reserved76;	//0xCC824BA4
	UINT32                                                   reserved77;	//0xCC824BA8
	UINT32                                                   reserved78;	//0xCC824BAC
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_00_T                     amg_top_stat_00;	//0xCC824BB0
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_01_T                     amg_top_stat_01;	//0xCC824BB4
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_02_T                     amg_top_stat_02;	//0xCC824BB8
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_03_T                     amg_top_stat_03;	//0xCC824BBC
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_04_T                     amg_top_stat_04;	//0xCC824BC0
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_05_T                     amg_top_stat_05;	//0xCC824BC4
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_06_T                     amg_top_stat_06;	//0xCC824BC8
	PE_O24_AMG0_HEAD_AMG_TOP_STAT_07_T                     amg_top_stat_07;	//0xCC824BCC
	PE_O24_AMG0_HEAD_AMG_CORE_STAT_00_T                   amg_core_stat_00;	//0xCC824BD0
	PE_O24_AMG0_HEAD_AMG_CORE_STAT_01_T                   amg_core_stat_01;	//0xCC824BD4
	PE_O24_AMG0_HEAD_AMG_CORE_STAT_02_T                   amg_core_stat_02;	//0xCC824BD8
	PE_O24_AMG0_HEAD_AMG_CORE_STAT_03_T                   amg_core_stat_03;	//0xCC824BDC
	PE_O24_AMG0_HEAD_AMG_CORE_STAT_04_T                   amg_core_stat_04;	//0xCC824BE0
	PE_O24_AMG0_HEAD_AMG_CORE_STAT_05_T                   amg_core_stat_05;	//0xCC824BE4
	UINT32                                                   reserved79;	//0xCC824BE8
	UINT32                                                   reserved80;	//0xCC824BEC
	PE_O24_AMG0_HEAD_AMG_FSW_CTRL_00_T                     amg_fsw_ctrl_00;	//0xCC824BF0
	PE_O24_AMG0_HEAD_AMG_FSW_CTRL_01_T                     amg_fsw_ctrl_01;	//0xCC824BF4
	PE_O24_AMG0_HEAD_AMG_FSW_CTRL_02_T                     amg_fsw_ctrl_02;	//0xCC824BF8
	PE_O24_AMG0_HEAD_AMG_FSW_CTRL_03_T                     amg_fsw_ctrl_03;	//0xCC824BFC
}PE_AMG_HEAD_REG_O24_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC824C20 RW 0x0242_0242
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
}PE_O24_AMG1_BODY_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C24 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0: Y	1: Cb	2: Cr	3: Depth
	UINT32 resvd                            :30;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C28 RO 0x0000_0000
	UINT32 reg_read_hist_00_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 0)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_00_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 0)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C2C RO 0x0000_0000
	UINT32 reg_read_hist_01_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 1)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_01_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 1)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C30 RO 0x0000_0000
	UINT32 reg_read_hist_02_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 2)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_02_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 2)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C34 RO 0x0000_0000
	UINT32 reg_read_hist_03_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 3)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_03_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 3)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C38 RO 0x0000_0000
	UINT32 reg_read_hist_04_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 4)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_04_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 4)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C3C RO 0x0000_0000
	UINT32 reg_read_hist_05_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 5)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_05_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 5)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C40 RO 0x0000_0000
	UINT32 reg_read_hist_06_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 6)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_06_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 6)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C44 RO 0x0000_0000
	UINT32 reg_read_hist_07_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 7)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_07_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 7)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C48 RO 0x0000_0000
	UINT32 reg_read_hist_08_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 8)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_08_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 8)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C4C RO 0x0000_0000
	UINT32 reg_read_hist_09_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 9)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_09_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 9)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C50 RO 0x0000_0000
	UINT32 reg_read_hist_10_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 10)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_10_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 10)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C54 RO 0x0000_0000
	UINT32 reg_read_hist_11_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 11)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_11_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 11)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C58 RO 0x0000_0000
	UINT32 reg_read_hist_12_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 12)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_12_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 12)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C5C RO 0x0000_0000
	UINT32 reg_read_hist_13_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 13)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_13_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 13)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C60 RO 0x0000_0000
	UINT32 reg_read_hist_14_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 14)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_14_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 14)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C64 RO 0x0000_0000
	UINT32 reg_read_hist_15_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 15)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_15_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 15)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C68 RO 0x0000_0000
	UINT32 reg_read_hist_16_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 16)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_16_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 16)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C6C RO 0x0000_0000
	UINT32 reg_read_hist_17_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 17)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_17_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 17)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C70 RO 0x0000_0000
	UINT32 reg_read_hist_18_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 18)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_18_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 18)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C74 RO 0x0000_0000
	UINT32 reg_read_hist_19_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 19)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_19_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 19)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C78 RO 0x0000_0000
	UINT32 reg_read_hist_20_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 20)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_20_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 20)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C7C RO 0x0000_0000
	UINT32 reg_read_hist_21_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 21)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_21_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 21)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C80 RO 0x0000_0000
	UINT32 reg_read_hist_22_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 22)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_22_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 22)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C84 RO 0x0000_0000
	UINT32 reg_read_hist_23_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 23)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_23_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 23)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C88 RO 0x0000_0000
	UINT32 reg_read_hist_24_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 24)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_24_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 24)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C8C RO 0x0000_0000
	UINT32 reg_read_hist_25_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 25)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_25_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 25)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C90 RO 0x0000_0000
	UINT32 reg_read_hist_26_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 26)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_26_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 26)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C94 RO 0x0000_0000
	UINT32 reg_read_hist_27_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 27)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_27_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 27)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C98 RO 0x0000_0000
	UINT32 reg_read_hist_28_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 28)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_28_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 28)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824C9C RO 0x0000_0000
	UINT32 reg_read_hist_29_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 29)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_29_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 29)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CA0 RO 0x0000_0000
	UINT32 reg_read_hist_30_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 30)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_30_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 30)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CA4 RO 0x0000_0000
	UINT32 reg_read_hist_31_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 31)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_31_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 31)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG1_BODY_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CB0 RW 0x0000_1101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0: Probability map	1: Ellipse gain map	2: Probability map (FG)	3: Probability map (BG)	4: Probability map (diff)	5: Box map	6: Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,1) //Object map output mux selection	0: HEAD/BODY	1: Blending	2: Depth only	3: Adding
	UINT32 resvd3                           :18;
	};
}PE_O24_AMG1_BODY_OBJT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CB4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
}PE_O24_AMG1_BODY_OBJT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CB8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_OBJT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CBC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG1_BODY_OBJT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CC0 RW 0x0000_0000
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
}PE_O24_AMG1_BODY_BOX_SET_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CC4 RW 0x0000_0000
	UINT32 reg_box_fg_cand_w1               :8;	//(7:0,NA,0) //Box (FG candidate) position, w, start
	UINT32 reg_box_fg_cand_w2               :8;	//(15:8,NA,0) //Box (FG candidate) position, w, end
	UINT32 reg_box_fg_cand_h1               :8;	//(23:16,NA,0) //Box (FG candidate) position, h, start
	UINT32 reg_box_fg_cand_h2               :8;	//(31:24,NA,0) //Box (FG candidate) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CC8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CCC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CD0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CD4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CD8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CDC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CE0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CE4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CE8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CEC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CF0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824CF4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
}PE_O24_AMG1_BODY_BOX_SET_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D00 RW 0x0000_0000
	UINT32 reg_fg_cand_e_mul_a              :9;	//(8:0,NA,0) //Ellipse (FG candidate) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_fg_cand_e_mul_b              :9;	//(24:16,NA,0) //Ellipse (FG candidate) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_fg_cand_ellipse_en           :1;	//(31:31,NA,0) //Ellipse (FG candidate) gain gen enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D04 RW 0x0000_0000
	UINT32 reg_fg_cand_ellipse_master       :8;	//(7:0,NA,0) //Ellipse (FG candidate) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_fg_cand_ellipse_offset       :8;	//(23:16,NA,0) //Ellipse (FG candidate) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 0) ellipse to rect disable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 1) ellipse to rect disable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 2) ellipse to rect disable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 3) ellipse to rect disable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
}PE_O24_AMG1_BODY_ELLIPSE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
}PE_O24_AMG1_BODY_LUT_PROB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
}PE_O24_AMG1_BODY_LUT_PROB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D80 RW 0x0000_00CC
	UINT32 reg_blur_vcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
}PE_O24_AMG1_BODY_BLUR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D90 RW 0x5014_0000
	UINT32 reg_lut_depth_map_y0             :8;	//(7:0,NA,0) //LUT (depth map) control point, y0
	UINT32 reg_lut_depth_map_x0             :8;	//(15:8,NA,0) //LUT (depth map) control point, x0
	UINT32 reg_lut_depth_map_y1             :8;	//(23:16,NA,20) //LUT (depth map) control point, y1
	UINT32 reg_lut_depth_map_x1             :8;	//(31:24,NA,80) //LUT (depth map) control point, x1
	};
}PE_O24_AMG1_BODY_LUT_DEPTH_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824D94 RW 0xFFFF_6E6E
	UINT32 reg_lut_depth_map_y2             :8;	//(7:0,NA,110) //LUT (depth map) control point, y2
	UINT32 reg_lut_depth_map_x2             :8;	//(15:8,NA,110) //LUT (depth map) control point, x2
	UINT32 reg_lut_depth_map_y3             :8;	//(23:16,NA,255) //LUT (depth map) control point, y3
	UINT32 reg_lut_depth_map_x3             :8;	//(31:24,NA,255) //LUT (depth map) control point, x3
	};
}PE_O24_AMG1_BODY_LUT_DEPTH_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DA0 RW 0xC090_6030
	UINT32 reg_region_position_x1           :8;	//(7:0,NA,48) //Region gain position, x1
	UINT32 reg_region_position_x2           :8;	//(15:8,NA,96) //Region gain position, x2
	UINT32 reg_region_position_x3           :8;	//(23:16,NA,144) //Region gain position, x3
	UINT32 reg_region_position_x4           :8;	//(31:24,NA,192) //Region gain position, x4
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DA4 RW 0xEFEF_EFEF
	UINT32 reg_region_position_x5           :8;	//(7:0,NA,239) //Region gain position, x5
	UINT32 reg_region_position_x6           :8;	//(15:8,NA,239) //Region gain position, x6
	UINT32 reg_region_position_x7           :8;	//(23:16,NA,239) //Region gain position, x7
	UINT32 reg_region_position_x8           :8;	//(31:24,NA,239) //Region gain position, x8
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DA8 RW 0x7D73_5A28
	UINT32 reg_region_position_y1           :8;	//(7:0,NA,40) //Region gain position, y1
	UINT32 reg_region_position_y2           :8;	//(15:8,NA,90) //Region gain position, y2
	UINT32 reg_region_position_y3           :8;	//(23:16,NA,115) //Region gain position, y3
	UINT32 reg_region_position_y4           :8;	//(31:24,NA,125) //Region gain position, y4
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DAC RW 0x0000_8686
	UINT32 reg_region_position_y5           :8;	//(7:0,NA,134) //Region gain position, y5
	UINT32 reg_region_position_y6           :8;	//(15:8,NA,134) //Region gain position, y6
	UINT32 resvd                            :16;
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DB0 RW 0x0000_0000
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
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DB4 RW 0x0000_0000
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
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DB8 RW 0x0000_0000
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
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DBC RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,128) //Region gain, 11
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,128) //Region gain, 21
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,128) //Region gain, 31
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,128) //Region gain, 41
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DC0 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,128) //Region gain, 51
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,128) //Region gain, 61
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,128) //Region gain, 71
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,128) //Region gain, 81
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DC4 RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,128) //Region gain, 12
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,128) //Region gain, 22
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,128) //Region gain, 32
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,128) //Region gain, 42
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DC8 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,128) //Region gain, 52
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,128) //Region gain, 62
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,128) //Region gain, 72
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,128) //Region gain, 82
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DCC RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,128) //Region gain, 13
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,128) //Region gain, 23
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,128) //Region gain, 33
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,128) //Region gain, 43
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DD0 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,128) //Region gain, 53
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,128) //Region gain, 63
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,128) //Region gain, 73
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,128) //Region gain, 83
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DD4 RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,128) //Region gain, 14
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,128) //Region gain, 24
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,128) //Region gain, 34
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,128) //Region gain, 44
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DD8 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,128) //Region gain, 54
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,128) //Region gain, 64
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,128) //Region gain, 74
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,128) //Region gain, 84
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DDC RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,128) //Region gain, 15
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,128) //Region gain, 25
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,128) //Region gain, 35
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,128) //Region gain, 45
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DE0 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,128) //Region gain, 55
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,128) //Region gain, 65
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,128) //Region gain, 75
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,128) //Region gain, 85
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DE4 RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,128) //Region gain, 16
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,128) //Region gain, 26
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,128) //Region gain, 36
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,128) //Region gain, 46
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DE8 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,128) //Region gain, 56
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,128) //Region gain, 66
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,128) //Region gain, 76
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,128) //Region gain, 86
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DEC RW 0x8600_EF00
	UINT32 reg_region_bnd_x0                :8;	//(7:0,NA,0) //Region bound, x0
	UINT32 reg_region_bnd_x1                :8;	//(15:8,NA,239) //Region bound, x1
	UINT32 reg_region_bnd_y0                :8;	//(23:16,NA,0) //Region bound, y0
	UINT32 reg_region_bnd_y1                :8;	//(31:24,NA,134) //Region bound, y1
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DF0 RW 0x0000_0080
	UINT32 reg_region_bnd_gain              :8;	//(7:0,NA,128) //Region bound gain
	UINT32 resvd                            :24;
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824DF4 RW 0x0000_0110
	UINT32 reg_region_gain_offset0          :8;	//(7:0,NA,16) //Region gain offset0
	UINT32 reg_region_gain_offset1          :8;	//(15:8,NA,1) //Region gain offset1
	UINT32 resvd                            :16;
	};
}PE_O24_AMG1_BODY_REGION_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E00 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_u_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y0
	UINT32 reg_lut_depth_iir_u_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, up) control point, x0
	UINT32 reg_lut_depth_iir_u_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y1
	UINT32 reg_lut_depth_iir_u_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, up) control point, x1
	};
}PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E04 RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_u_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y2
	UINT32 reg_lut_depth_iir_u_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, up) control point, x2
	UINT32 reg_lut_depth_iir_u_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y3
	UINT32 reg_lut_depth_iir_u_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, up) control point, x3
	};
}PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E08 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_d_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y0
	UINT32 reg_lut_depth_iir_d_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, down) control point, x0
	UINT32 reg_lut_depth_iir_d_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y1
	UINT32 reg_lut_depth_iir_d_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, down) control point, x1
	};
}PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E0C RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_d_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y2
	UINT32 reg_lut_depth_iir_d_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, down) control point, x2
	UINT32 reg_lut_depth_iir_d_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y3
	UINT32 reg_lut_depth_iir_d_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, down) control point, x3
	};
}PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E10 RW 0x3FFF_00FF
	UINT32 reg_lut_depth_body_y0            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y0
	UINT32 reg_lut_depth_body_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth>body), x0
	UINT32 reg_lut_depth_body_y1            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y1
	UINT32 reg_lut_depth_body_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth>body), x1
	};
}PE_O24_AMG1_BODY_LUT_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E14 RW 0xFFFF_7EFF
	UINT32 reg_lut_depth_body_y2            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y2
	UINT32 reg_lut_depth_body_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth>body), x2
	UINT32 reg_lut_depth_body_y3            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y3
	UINT32 reg_lut_depth_body_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth>body), x3
	};
}PE_O24_AMG1_BODY_LUT_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E18 RW 0x3F20_0000
	UINT32 reg_lut_body_depth_y0            :8;	//(7:0,NA,0) //LUT (depth body blend) control point (for depth<=body), y0
	UINT32 reg_lut_body_depth_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth<=body), x0
	UINT32 reg_lut_body_depth_y1            :8;	//(23:16,NA,32) //LUT (depth body blend) control point (for depth<=body), y1
	UINT32 reg_lut_body_depth_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth<=body), x1
	};
}PE_O24_AMG1_BODY_LUT_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E1C RW 0xFF58_7E58
	UINT32 reg_lut_body_depth_y2            :8;	//(7:0,NA,88) //LUT (depth body blend) control point (for depth<=body), y2
	UINT32 reg_lut_body_depth_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth<=body), x2
	UINT32 reg_lut_body_depth_y3            :8;	//(23:16,NA,88) //LUT (depth body blend) control point (for depth<=body), y3
	UINT32 reg_lut_body_depth_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth<=body), x3
	};
}PE_O24_AMG1_BODY_LUT_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0: use manual value	1: use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0: use IIR result	1: use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
}PE_O24_AMG1_BODY_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
}PE_O24_AMG1_BODY_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
}PE_O24_AMG1_BODY_LUT_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
}PE_O24_AMG1_BODY_LUT_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC824E38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
}PE_O24_AMG1_BODY_LUT_IIR_CTRL_02_T;

typedef struct {
	PE_O24_AMG1_BODY_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xCC824C20
	PE_O24_AMG1_BODY_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xCC824C24
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_00_T                 histogram_stat_00;	//0xCC824C28
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_01_T                 histogram_stat_01;	//0xCC824C2C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_02_T                 histogram_stat_02;	//0xCC824C30
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_03_T                 histogram_stat_03;	//0xCC824C34
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_04_T                 histogram_stat_04;	//0xCC824C38
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_05_T                 histogram_stat_05;	//0xCC824C3C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_06_T                 histogram_stat_06;	//0xCC824C40
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_07_T                 histogram_stat_07;	//0xCC824C44
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_08_T                 histogram_stat_08;	//0xCC824C48
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_09_T                 histogram_stat_09;	//0xCC824C4C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_10_T                 histogram_stat_10;	//0xCC824C50
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_11_T                 histogram_stat_11;	//0xCC824C54
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_12_T                 histogram_stat_12;	//0xCC824C58
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_13_T                 histogram_stat_13;	//0xCC824C5C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_14_T                 histogram_stat_14;	//0xCC824C60
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_15_T                 histogram_stat_15;	//0xCC824C64
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_16_T                 histogram_stat_16;	//0xCC824C68
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_17_T                 histogram_stat_17;	//0xCC824C6C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_18_T                 histogram_stat_18;	//0xCC824C70
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_19_T                 histogram_stat_19;	//0xCC824C74
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_20_T                 histogram_stat_20;	//0xCC824C78
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_21_T                 histogram_stat_21;	//0xCC824C7C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_22_T                 histogram_stat_22;	//0xCC824C80
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_23_T                 histogram_stat_23;	//0xCC824C84
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_24_T                 histogram_stat_24;	//0xCC824C88
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_25_T                 histogram_stat_25;	//0xCC824C8C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_26_T                 histogram_stat_26;	//0xCC824C90
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_27_T                 histogram_stat_27;	//0xCC824C94
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_28_T                 histogram_stat_28;	//0xCC824C98
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_29_T                 histogram_stat_29;	//0xCC824C9C
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_30_T                 histogram_stat_30;	//0xCC824CA0
	PE_O24_AMG1_BODY_HISTOGRAM_STAT_31_T                 histogram_stat_31;	//0xCC824CA4
	UINT32                                                    reserved0;	//0xCC824CA8
	UINT32                                                    reserved1;	//0xCC824CAC
	PE_O24_AMG1_BODY_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xCC824CB0
	PE_O24_AMG1_BODY_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xCC824CB4
	PE_O24_AMG1_BODY_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xCC824CB8
	PE_O24_AMG1_BODY_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xCC824CBC
	PE_O24_AMG1_BODY_BOX_SET_CTRL_00_T                     box_set_ctrl_00;	//0xCC824CC0
	PE_O24_AMG1_BODY_BOX_SET_CTRL_01_T                     box_set_ctrl_01;	//0xCC824CC4
	PE_O24_AMG1_BODY_BOX_SET_CTRL_02_T                     box_set_ctrl_02;	//0xCC824CC8
	PE_O24_AMG1_BODY_BOX_SET_CTRL_03_T                     box_set_ctrl_03;	//0xCC824CCC
	PE_O24_AMG1_BODY_BOX_SET_CTRL_04_T                     box_set_ctrl_04;	//0xCC824CD0
	PE_O24_AMG1_BODY_BOX_SET_CTRL_05_T                     box_set_ctrl_05;	//0xCC824CD4
	PE_O24_AMG1_BODY_BOX_SET_CTRL_06_T                     box_set_ctrl_06;	//0xCC824CD8
	PE_O24_AMG1_BODY_BOX_SET_CTRL_07_T                     box_set_ctrl_07;	//0xCC824CDC
	PE_O24_AMG1_BODY_BOX_SET_CTRL_08_T                     box_set_ctrl_08;	//0xCC824CE0
	PE_O24_AMG1_BODY_BOX_SET_CTRL_09_T                     box_set_ctrl_09;	//0xCC824CE4
	PE_O24_AMG1_BODY_BOX_SET_CTRL_10_T                     box_set_ctrl_10;	//0xCC824CE8
	PE_O24_AMG1_BODY_BOX_SET_CTRL_11_T                     box_set_ctrl_11;	//0xCC824CEC
	PE_O24_AMG1_BODY_BOX_SET_CTRL_12_T                     box_set_ctrl_12;	//0xCC824CF0
	PE_O24_AMG1_BODY_BOX_SET_CTRL_13_T                     box_set_ctrl_13;	//0xCC824CF4
	UINT32                                                    reserved2;	//0xCC824CF8
	UINT32                                                    reserved3;	//0xCC824CFC
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xCC824D00
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xCC824D04
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xCC824D08
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xCC824D0C
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xCC824D10
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xCC824D14
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xCC824D18
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xCC824D1C
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xCC824D20
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xCC824D24
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xCC824D28
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xCC824D2C
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xCC824D30
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xCC824D34
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xCC824D38
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xCC824D3C
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xCC824D40
	PE_O24_AMG1_BODY_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xCC824D44
	UINT32                                                    reserved4;	//0xCC824D48
	UINT32                                                    reserved5;	//0xCC824D4C
	PE_O24_AMG1_BODY_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xCC824D50
	PE_O24_AMG1_BODY_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xCC824D54
	UINT32                                                    reserved6;	//0xCC824D58
	UINT32                                                    reserved7;	//0xCC824D5C
	PE_O24_AMG1_BODY_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xCC824D60
	PE_O24_AMG1_BODY_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xCC824D64
	PE_O24_AMG1_BODY_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xCC824D68
	PE_O24_AMG1_BODY_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xCC824D6C
	PE_O24_AMG1_BODY_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xCC824D70
	PE_O24_AMG1_BODY_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xCC824D74
	PE_O24_AMG1_BODY_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xCC824D78
	PE_O24_AMG1_BODY_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xCC824D7C
	PE_O24_AMG1_BODY_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xCC824D80
	UINT32                                                    reserved8;	//0xCC824D84
	UINT32                                                    reserved9;	//0xCC824D88
	UINT32                                                   reserved10;	//0xCC824D8C
	PE_O24_AMG1_BODY_LUT_DEPTH_CTRL_00_T                 lut_depth_ctrl_00;	//0xCC824D90
	PE_O24_AMG1_BODY_LUT_DEPTH_CTRL_01_T                 lut_depth_ctrl_01;	//0xCC824D94
	UINT32                                                   reserved11;	//0xCC824D98
	UINT32                                                   reserved12;	//0xCC824D9C
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_00_T             region_gain_ctrl_00;	//0xCC824DA0
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_01_T             region_gain_ctrl_01;	//0xCC824DA4
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_02_T             region_gain_ctrl_02;	//0xCC824DA8
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_03_T             region_gain_ctrl_03;	//0xCC824DAC
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_04_T             region_gain_ctrl_04;	//0xCC824DB0
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_05_T             region_gain_ctrl_05;	//0xCC824DB4
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_06_T             region_gain_ctrl_06;	//0xCC824DB8
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_07_T             region_gain_ctrl_07;	//0xCC824DBC
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_08_T             region_gain_ctrl_08;	//0xCC824DC0
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_09_T             region_gain_ctrl_09;	//0xCC824DC4
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_10_T             region_gain_ctrl_10;	//0xCC824DC8
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_11_T             region_gain_ctrl_11;	//0xCC824DCC
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_12_T             region_gain_ctrl_12;	//0xCC824DD0
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_13_T             region_gain_ctrl_13;	//0xCC824DD4
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_14_T             region_gain_ctrl_14;	//0xCC824DD8
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_15_T             region_gain_ctrl_15;	//0xCC824DDC
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_16_T             region_gain_ctrl_16;	//0xCC824DE0
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_17_T             region_gain_ctrl_17;	//0xCC824DE4
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_18_T             region_gain_ctrl_18;	//0xCC824DE8
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_19_T             region_gain_ctrl_19;	//0xCC824DEC
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_20_T             region_gain_ctrl_20;	//0xCC824DF0
	PE_O24_AMG1_BODY_REGION_GAIN_CTRL_21_T             region_gain_ctrl_21;	//0xCC824DF4
	UINT32                                                   reserved13;	//0xCC824DF8
	UINT32                                                   reserved14;	//0xCC824DFC
	PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T         lut_depth_iir_ctrl_00;	//0xCC824E00
	PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T         lut_depth_iir_ctrl_01;	//0xCC824E04
	PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T         lut_depth_iir_ctrl_02;	//0xCC824E08
	PE_O24_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T         lut_depth_iir_ctrl_03;	//0xCC824E0C
	PE_O24_AMG1_BODY_LUT_BLD_CTRL_00_T                     lut_bld_ctrl_00;	//0xCC824E10
	PE_O24_AMG1_BODY_LUT_BLD_CTRL_01_T                     lut_bld_ctrl_01;	//0xCC824E14
	PE_O24_AMG1_BODY_LUT_BLD_CTRL_02_T                     lut_bld_ctrl_02;	//0xCC824E18
	PE_O24_AMG1_BODY_LUT_BLD_CTRL_03_T                     lut_bld_ctrl_03;	//0xCC824E1C
	PE_O24_AMG1_BODY_IIR_CTRL_00_T                             iir_ctrl_00;	//0xCC824E20
	PE_O24_AMG1_BODY_IIR_CTRL_01_T                             iir_ctrl_01;	//0xCC824E24
	UINT32                                                   reserved15;	//0xCC824E28
	UINT32                                                   reserved16;	//0xCC824E2C
	PE_O24_AMG1_BODY_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xCC824E30
	PE_O24_AMG1_BODY_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xCC824E34
	PE_O24_AMG1_BODY_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xCC824E38
}PE_AMG_BODY_REG_O24_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC825800 RW 0xFFFF_C5BF
	UINT32 reg_ca_mc_prv_lut_y4             :8;	//(7:0,NA,191) //Contrast adjust LUT points (MC: PRV), y4
	UINT32 reg_ca_mc_prv_lut_x4             :8;	//(15:8,NA,197) //Contrast adjust LUT points (MC: PRV), x4
	UINT32 reg_ca_mc_prv_lut_y5             :8;	//(23:16,NA,255) //Contrast adjust LUT points (MC: PRV), y5
	UINT32 reg_ca_mc_prv_lut_x5             :8;	//(31:24,NA,255) //Contrast adjust LUT points (MC: PRV), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825804 RW 0x8B7F_503F
	UINT32 reg_ca_mc_prv_lut_y2             :8;	//(7:0,NA,63) //Contrast adjust LUT points (MC: PRV), y2
	UINT32 reg_ca_mc_prv_lut_x2             :8;	//(15:8,NA,80) //Contrast adjust LUT points (MC: PRV), x2
	UINT32 reg_ca_mc_prv_lut_y3             :8;	//(23:16,NA,127) //Contrast adjust LUT points (MC: PRV), y3
	UINT32 reg_ca_mc_prv_lut_x3             :8;	//(31:24,NA,139) //Contrast adjust LUT points (MC: PRV), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825808 RW 0x1900_0000
	UINT32 reg_ca_mc_prv_lut_y0             :8;	//(7:0,NA,0) //Contrast adjust LUT points (MC: PRV), y0
	UINT32 reg_ca_mc_prv_lut_x0             :8;	//(15:8,NA,0) //Contrast adjust LUT points (MC: PRV), x0
	UINT32 reg_ca_mc_prv_lut_y1             :8;	//(23:16,NA,0) //Contrast adjust LUT points (MC: PRV), y1
	UINT32 reg_ca_mc_prv_lut_x1             :8;	//(31:24,NA,25) //Contrast adjust LUT points (MC: PRV), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82580C RW 0xFFFF_F7FF
	UINT32 reg_ca_mc_cur_lut_y4             :8;	//(7:0,NA,255) //Contrast adjust LUT points (MC: CUR), y4
	UINT32 reg_ca_mc_cur_lut_x4             :8;	//(15:8,NA,247) //Contrast adjust LUT points (MC: CUR), x4
	UINT32 reg_ca_mc_cur_lut_y5             :8;	//(23:16,NA,255) //Contrast adjust LUT points (MC: CUR), y5
	UINT32 reg_ca_mc_cur_lut_x5             :8;	//(31:24,NA,255) //Contrast adjust LUT points (MC: CUR), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825810 RW 0xA9AA_5B55
	UINT32 reg_ca_mc_cur_lut_y2             :8;	//(7:0,NA,85) //Contrast adjust LUT points (MC: CUR), y2
	UINT32 reg_ca_mc_cur_lut_x2             :8;	//(15:8,NA,91) //Contrast adjust LUT points (MC: CUR), x2
	UINT32 reg_ca_mc_cur_lut_y3             :8;	//(23:16,NA,170) //Contrast adjust LUT points (MC: CUR), y3
	UINT32 reg_ca_mc_cur_lut_x3             :8;	//(31:24,NA,169) //Contrast adjust LUT points (MC: CUR), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825814 RW 0x0E00_0000
	UINT32 reg_ca_mc_cur_lut_y0             :8;	//(7:0,NA,0) //Contrast adjust LUT points (MC: CUR), y0
	UINT32 reg_ca_mc_cur_lut_x0             :8;	//(15:8,NA,0) //Contrast adjust LUT points (MC: CUR), x0
	UINT32 reg_ca_mc_cur_lut_y1             :8;	//(23:16,NA,0) //Contrast adjust LUT points (MC: CUR), y1
	UINT32 reg_ca_mc_cur_lut_x1             :8;	//(31:24,NA,14) //Contrast adjust LUT points (MC: CUR), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825818 RW 0xFFFF_F7FF
	UINT32 reg_ca_mc_res_lut_y4             :8;	//(7:0,NA,255) //Contrast adjust LUT points (MC: RES), y4
	UINT32 reg_ca_mc_res_lut_x4             :8;	//(15:8,NA,247) //Contrast adjust LUT points (MC: RES), x4
	UINT32 reg_ca_mc_res_lut_y5             :8;	//(23:16,NA,255) //Contrast adjust LUT points (MC: RES), y5
	UINT32 reg_ca_mc_res_lut_x5             :8;	//(31:24,NA,255) //Contrast adjust LUT points (MC: RES), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82581C RW 0xA9AA_5B55
	UINT32 reg_ca_mc_res_lut_y2             :8;	//(7:0,NA,85) //Contrast adjust LUT points (MC: RES), y2
	UINT32 reg_ca_mc_res_lut_x2             :8;	//(15:8,NA,91) //Contrast adjust LUT points (MC: RES), x2
	UINT32 reg_ca_mc_res_lut_y3             :8;	//(23:16,NA,170) //Contrast adjust LUT points (MC: RES), y3
	UINT32 reg_ca_mc_res_lut_x3             :8;	//(31:24,NA,169) //Contrast adjust LUT points (MC: RES), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825820 RW 0x0E00_0000
	UINT32 reg_ca_mc_res_lut_y0             :8;	//(7:0,NA,0) //Contrast adjust LUT points (MC: RES), y0
	UINT32 reg_ca_mc_res_lut_x0             :8;	//(15:8,NA,0) //Contrast adjust LUT points (MC: RES), x0
	UINT32 reg_ca_mc_res_lut_y1             :8;	//(23:16,NA,0) //Contrast adjust LUT points (MC: RES), y1
	UINT32 reg_ca_mc_res_lut_x1             :8;	//(31:24,NA,14) //Contrast adjust LUT points (MC: RES), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825824 RW 0xFFFF_C5BF
	UINT32 reg_ca_basic_prv_lut_y4          :8;	//(7:0,NA,191) //Contrast adjust LUT points (Basic: PRV), y4
	UINT32 reg_ca_basic_prv_lut_x4          :8;	//(15:8,NA,197) //Contrast adjust LUT points (Basic: PRV), x4
	UINT32 reg_ca_basic_prv_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Basic: PRV), y5
	UINT32 reg_ca_basic_prv_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Basic: PRV), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825828 RW 0x8B7F_503F
	UINT32 reg_ca_basic_prv_lut_y2          :8;	//(7:0,NA,63) //Contrast adjust LUT points (Basic: PRV), y2
	UINT32 reg_ca_basic_prv_lut_x2          :8;	//(15:8,NA,80) //Contrast adjust LUT points (Basic: PRV), x2
	UINT32 reg_ca_basic_prv_lut_y3          :8;	//(23:16,NA,127) //Contrast adjust LUT points (Basic: PRV), y3
	UINT32 reg_ca_basic_prv_lut_x3          :8;	//(31:24,NA,139) //Contrast adjust LUT points (Basic: PRV), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82582C RW 0x1900_0000
	UINT32 reg_ca_basic_prv_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Basic: PRV), y0
	UINT32 reg_ca_basic_prv_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Basic: PRV), x0
	UINT32 reg_ca_basic_prv_lut_y1          :8;	//(23:16,NA,0) //Contrast adjust LUT points (Basic: PRV), y1
	UINT32 reg_ca_basic_prv_lut_x1          :8;	//(31:24,NA,25) //Contrast adjust LUT points (Basic: PRV), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825830 RW 0xFFFF_F7FF
	UINT32 reg_ca_basic_cur_lut_y4          :8;	//(7:0,NA,255) //Contrast adjust LUT points (Basic: CUR), y4
	UINT32 reg_ca_basic_cur_lut_x4          :8;	//(15:8,NA,247) //Contrast adjust LUT points (Basic: CUR), x4
	UINT32 reg_ca_basic_cur_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Basic: CUR), y5
	UINT32 reg_ca_basic_cur_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Basic: CUR), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825834 RW 0xA9AA_5B55
	UINT32 reg_ca_basic_cur_lut_y2          :8;	//(7:0,NA,85) //Contrast adjust LUT points (Basic: CUR), y2
	UINT32 reg_ca_basic_cur_lut_x2          :8;	//(15:8,NA,91) //Contrast adjust LUT points (Basic: CUR), x2
	UINT32 reg_ca_basic_cur_lut_y3          :8;	//(23:16,NA,170) //Contrast adjust LUT points (Basic: CUR), y3
	UINT32 reg_ca_basic_cur_lut_x3          :8;	//(31:24,NA,169) //Contrast adjust LUT points (Basic: CUR), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825838 RW 0x0E00_0000
	UINT32 reg_ca_basic_cur_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Basic: CUR), y0
	UINT32 reg_ca_basic_cur_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Basic: CUR), x0
	UINT32 reg_ca_basic_cur_lut_y1          :8;	//(23:16,NA,0) //Contrast adjust LUT points (Basic: CUR), y1
	UINT32 reg_ca_basic_cur_lut_x1          :8;	//(31:24,NA,14) //Contrast adjust LUT points (Basic: CUR), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82583C RW 0xFFFF_F7FF
	UINT32 reg_ca_basic_res_lut_y4          :8;	//(7:0,NA,255) //Contrast adjust LUT points (Basic: RES), y4
	UINT32 reg_ca_basic_res_lut_x4          :8;	//(15:8,NA,247) //Contrast adjust LUT points (Basic: RES), x4
	UINT32 reg_ca_basic_res_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Basic: RES), y5
	UINT32 reg_ca_basic_res_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Basic: RES), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825840 RW 0xA9AA_5B55
	UINT32 reg_ca_basic_res_lut_y2          :8;	//(7:0,NA,85) //Contrast adjust LUT points (Basic: RES), y2
	UINT32 reg_ca_basic_res_lut_x2          :8;	//(15:8,NA,91) //Contrast adjust LUT points (Basic: RES), x2
	UINT32 reg_ca_basic_res_lut_y3          :8;	//(23:16,NA,170) //Contrast adjust LUT points (Basic: RES), y3
	UINT32 reg_ca_basic_res_lut_x3          :8;	//(31:24,NA,169) //Contrast adjust LUT points (Basic: RES), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825844 RW 0x0E00_0000
	UINT32 reg_ca_basic_res_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Basic: RES), y0
	UINT32 reg_ca_basic_res_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Basic: RES), x0
	UINT32 reg_ca_basic_res_lut_y1          :8;	//(23:16,NA,0) //Contrast adjust LUT points (Basic: RES), y1
	UINT32 reg_ca_basic_res_lut_x1          :8;	//(31:24,NA,14) //Contrast adjust LUT points (Basic: RES), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825848 RW 0xFFFF_C0C0
	UINT32 reg_ca_final_res_lut_y4          :8;	//(7:0,NA,192) //Contrast adjust LUT points (Final: RES), y4
	UINT32 reg_ca_final_res_lut_x4          :8;	//(15:8,NA,192) //Contrast adjust LUT points (Final: RES), x4
	UINT32 reg_ca_final_res_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Final: RES), y5
	UINT32 reg_ca_final_res_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Final: RES), x5
	};
}PE_O24_AMG2_MTB_CA_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82584C RW 0xA0A0_8080
	UINT32 reg_ca_final_res_lut_y2          :8;	//(7:0,NA,128) //Contrast adjust LUT points (Final: RES), y2
	UINT32 reg_ca_final_res_lut_x2          :8;	//(15:8,NA,128) //Contrast adjust LUT points (Final: RES), x2
	UINT32 reg_ca_final_res_lut_y3          :8;	//(23:16,NA,160) //Contrast adjust LUT points (Final: RES), y3
	UINT32 reg_ca_final_res_lut_x3          :8;	//(31:24,NA,160) //Contrast adjust LUT points (Final: RES), x3
	};
}PE_O24_AMG2_MTB_CA_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825850 RW 0x4040_0000
	UINT32 reg_ca_final_res_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Final: RES), y0
	UINT32 reg_ca_final_res_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Final: RES), x0
	UINT32 reg_ca_final_res_lut_y1          :8;	//(23:16,NA,64) //Contrast adjust LUT points (Final: RES), y1
	UINT32 reg_ca_final_res_lut_x1          :8;	//(31:24,NA,64) //Contrast adjust LUT points (Final: RES), x1
	};
}PE_O24_AMG2_MTB_CA_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825860 RW 0x0000_0000
	UINT32 reg_blend_inp_type_mc            :1;	//(0:0,NA,0) //Blending input type (MC , 0: ABS diff, 1: offset diff)
	UINT32 resvd0                           :3;
	UINT32 reg_blend_inp_type_basic         :1;	//(4:4,NA,0) //Blending input type (Basic, 0: ABS diff, 1: offset diff)
	UINT32 resvd1                           :3;
	UINT32 reg_blend_inp_type_final         :1;	//(8:8,NA,0) //Blending input type (Final, 0: ABS diff, 1: offset diff)
	UINT32 resvd2                           :23;
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825864 RW 0xFF80_46B0
	UINT32 reg_blend_mc_lut_wei4            :8;	//(7:0,NA,176) //Blending LUT points (MC), y4
	UINT32 reg_blend_mc_lut_dif4            :8;	//(15:8,NA,70) //Blending LUT points (MC), x4
	UINT32 reg_blend_mc_lut_wei5            :8;	//(23:16,NA,128) //Blending LUT points (MC), y5
	UINT32 reg_blend_mc_lut_dif5            :8;	//(31:24,NA,255) //Blending LUT points (MC), x5
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825868 RW 0x32C0_1EE0
	UINT32 reg_blend_mc_lut_wei2            :8;	//(7:0,NA,224) //Blending LUT points (MC), y2
	UINT32 reg_blend_mc_lut_dif2            :8;	//(15:8,NA,30) //Blending LUT points (MC), x2
	UINT32 reg_blend_mc_lut_wei3            :8;	//(23:16,NA,192) //Blending LUT points (MC), y3
	UINT32 reg_blend_mc_lut_dif3            :8;	//(31:24,NA,50) //Blending LUT points (MC), x3
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82586C RW 0x05F0_00F0
	UINT32 reg_blend_mc_lut_wei0            :8;	//(7:0,NA,240) //Blending LUT points (MC), y0
	UINT32 reg_blend_mc_lut_dif0            :8;	//(15:8,NA,0) //Blending LUT points (MC), x0
	UINT32 reg_blend_mc_lut_wei1            :8;	//(23:16,NA,240) //Blending LUT points (MC), y1
	UINT32 reg_blend_mc_lut_dif1            :8;	//(31:24,NA,5) //Blending LUT points (MC), x1
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825870 RW 0xFF00_4600
	UINT32 reg_blend_basic_lut_wei4         :8;	//(7:0,NA,0) //Blending LUT points (Basic), y4
	UINT32 reg_blend_basic_lut_dif4         :8;	//(15:8,NA,70) //Blending LUT points (Basic), x4
	UINT32 reg_blend_basic_lut_wei5         :8;	//(23:16,NA,0) //Blending LUT points (Basic), y5
	UINT32 reg_blend_basic_lut_dif5         :8;	//(31:24,NA,255) //Blending LUT points (Basic), x5
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825874 RW 0x32C0_1EE0
	UINT32 reg_blend_basic_lut_wei2         :8;	//(7:0,NA,224) //Blending LUT points (Basic), y2
	UINT32 reg_blend_basic_lut_dif2         :8;	//(15:8,NA,30) //Blending LUT points (Basic), x2
	UINT32 reg_blend_basic_lut_wei3         :8;	//(23:16,NA,192) //Blending LUT points (Basic), y3
	UINT32 reg_blend_basic_lut_dif3         :8;	//(31:24,NA,50) //Blending LUT points (Basic), x3
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825878 RW 0x05F0_00F0
	UINT32 reg_blend_basic_lut_wei0         :8;	//(7:0,NA,240) //Blending LUT points (Basic), y0
	UINT32 reg_blend_basic_lut_dif0         :8;	//(15:8,NA,0) //Blending LUT points (Basic), x0
	UINT32 reg_blend_basic_lut_wei1         :8;	//(23:16,NA,240) //Blending LUT points (Basic), y1
	UINT32 reg_blend_basic_lut_dif1         :8;	//(31:24,NA,5) //Blending LUT points (Basic), x1
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82587C RW 0xFFFF_46FF
	UINT32 reg_blend_final_lut_wei4         :8;	//(7:0,NA,255) //Blending LUT points (final), y4
	UINT32 reg_blend_final_lut_dif4         :8;	//(15:8,NA,70) //Blending LUT points (final), x4
	UINT32 reg_blend_final_lut_wei5         :8;	//(23:16,NA,255) //Blending LUT points (final), y5
	UINT32 reg_blend_final_lut_dif5         :8;	//(31:24,NA,255) //Blending LUT points (final), x5
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825880 RW 0x32F0_1EE0
	UINT32 reg_blend_final_lut_wei2         :8;	//(7:0,NA,224) //Blending LUT points (final), y2
	UINT32 reg_blend_final_lut_dif2         :8;	//(15:8,NA,30) //Blending LUT points (final), x2
	UINT32 reg_blend_final_lut_wei3         :8;	//(23:16,NA,240) //Blending LUT points (final), y3
	UINT32 reg_blend_final_lut_dif3         :8;	//(31:24,NA,50) //Blending LUT points (final), x3
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825884 RW 0x05C0_0080
	UINT32 reg_blend_final_lut_wei0         :8;	//(7:0,NA,128) //Blending LUT points (final), y0
	UINT32 reg_blend_final_lut_dif0         :8;	//(15:8,NA,0) //Blending LUT points (final), x0
	UINT32 reg_blend_final_lut_wei1         :8;	//(23:16,NA,192) //Blending LUT points (final), y1
	UINT32 reg_blend_final_lut_dif1         :8;	//(31:24,NA,5) //Blending LUT points (final), x1
	};
}PE_O24_AMG2_MTB_BLEND_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825888 RW 0x0000_0001
	UINT32 reg_warper_en                    :1;	//(0:0,NA,1) //Warper enable
	UINT32 resvd                            :31;
	};
}PE_O24_AMG2_MTB_WARP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825890 RW 0x0000_1111
	UINT32 reg_blf_en                       :1;	//(0:0,NA,1) //BLF enable
	UINT32 resvd0                           :3;
	UINT32 reg_blf_abs_diff_shift_yy        :2;	//(5:4,NA,1) //BLF pel weight LUT input control (ABS diff shift, 0~3 bits), Y
	UINT32 resvd1                           :2;
	UINT32 reg_blf_abs_diff_shift_cb        :2;	//(9:8,NA,1) //BLF pel weight LUT input control (ABS diff shift, 0~3 bits), CB
	UINT32 resvd2                           :2;
	UINT32 reg_blf_abs_diff_shift_cr        :2;	//(13:12,NA,1) //BLF pel weight LUT input control (ABS diff shift, 0~3 bits), CR
	UINT32 resvd3                           :18;
	};
}PE_O24_AMG2_MTB_BLF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825894 RW 0x3B3E_3F3F
	UINT32 reg_blf_lut_val_yy_00            :8;	//(7:0,NA,63) //BLF pel weight LUT value, (00), Y
	UINT32 reg_blf_lut_val_yy_01            :8;	//(15:8,NA,63) //BLF pel weight LUT value, (01), Y
	UINT32 reg_blf_lut_val_yy_02            :8;	//(23:16,NA,62) //BLF pel weight LUT value, (02), Y
	UINT32 reg_blf_lut_val_yy_03            :8;	//(31:24,NA,59) //BLF pel weight LUT value, (03), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825898 RW 0x2B30_3438
	UINT32 reg_blf_lut_val_yy_04            :8;	//(7:0,NA,56) //BLF pel weight LUT value, (04), Y
	UINT32 reg_blf_lut_val_yy_05            :8;	//(15:8,NA,52) //BLF pel weight LUT value, (05), Y
	UINT32 reg_blf_lut_val_yy_06            :8;	//(23:16,NA,48) //BLF pel weight LUT value, (06), Y
	UINT32 reg_blf_lut_val_yy_07            :8;	//(31:24,NA,43) //BLF pel weight LUT value, (07), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82589C RW 0x181D_2126
	UINT32 reg_blf_lut_val_yy_08            :8;	//(7:0,NA,38) //BLF pel weight LUT value, (08), Y
	UINT32 reg_blf_lut_val_yy_09            :8;	//(15:8,NA,33) //BLF pel weight LUT value, (09), Y
	UINT32 reg_blf_lut_val_yy_10            :8;	//(23:16,NA,29) //BLF pel weight LUT value, (10), Y
	UINT32 reg_blf_lut_val_yy_11            :8;	//(31:24,NA,24) //BLF pel weight LUT value, (11), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258A0 RW 0x0B0D_1114
	UINT32 reg_blf_lut_val_yy_12            :8;	//(7:0,NA,20) //BLF pel weight LUT value, (12), Y
	UINT32 reg_blf_lut_val_yy_13            :8;	//(15:8,NA,17) //BLF pel weight LUT value, (13), Y
	UINT32 reg_blf_lut_val_yy_14            :8;	//(23:16,NA,13) //BLF pel weight LUT value, (14), Y
	UINT32 reg_blf_lut_val_yy_15            :8;	//(31:24,NA,11) //BLF pel weight LUT value, (15), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258A4 RW 0x0305_0608
	UINT32 reg_blf_lut_val_yy_16            :8;	//(7:0,NA,8) //BLF pel weight LUT value, (16), Y
	UINT32 reg_blf_lut_val_yy_17            :8;	//(15:8,NA,6) //BLF pel weight LUT value, (17), Y
	UINT32 reg_blf_lut_val_yy_18            :8;	//(23:16,NA,5) //BLF pel weight LUT value, (18), Y
	UINT32 reg_blf_lut_val_yy_19            :8;	//(31:24,NA,3) //BLF pel weight LUT value, (19), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258A8 RW 0x0101_0202
	UINT32 reg_blf_lut_val_yy_20            :8;	//(7:0,NA,2) //BLF pel weight LUT value, (20), Y
	UINT32 reg_blf_lut_val_yy_21            :8;	//(15:8,NA,2) //BLF pel weight LUT value, (21), Y
	UINT32 reg_blf_lut_val_yy_22            :8;	//(23:16,NA,1) //BLF pel weight LUT value, (22), Y
	UINT32 reg_blf_lut_val_yy_23            :8;	//(31:24,NA,1) //BLF pel weight LUT value, (23), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258AC RW 0x0000_0000
	UINT32 reg_blf_lut_val_yy_24            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (24), Y
	UINT32 reg_blf_lut_val_yy_25            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (25), Y
	UINT32 reg_blf_lut_val_yy_26            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (26), Y
	UINT32 reg_blf_lut_val_yy_27            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (27), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258B0 RW 0x0000_0000
	UINT32 reg_blf_lut_val_yy_28            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (28), Y
	UINT32 reg_blf_lut_val_yy_29            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (29), Y
	UINT32 reg_blf_lut_val_yy_30            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (30), Y
	UINT32 reg_blf_lut_val_yy_31            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (31), Y
	};
}PE_O24_AMG2_MTB_BLF_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258B4 RW 0x3B3E_3F3F
	UINT32 reg_blf_lut_val_cb_00            :8;	//(7:0,NA,63) //BLF pel weight LUT value, (00), CB
	UINT32 reg_blf_lut_val_cb_01            :8;	//(15:8,NA,63) //BLF pel weight LUT value, (01), CB
	UINT32 reg_blf_lut_val_cb_02            :8;	//(23:16,NA,62) //BLF pel weight LUT value, (02), CB
	UINT32 reg_blf_lut_val_cb_03            :8;	//(31:24,NA,59) //BLF pel weight LUT value, (03), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258B8 RW 0x2B30_3438
	UINT32 reg_blf_lut_val_cb_04            :8;	//(7:0,NA,56) //BLF pel weight LUT value, (04), CB
	UINT32 reg_blf_lut_val_cb_05            :8;	//(15:8,NA,52) //BLF pel weight LUT value, (05), CB
	UINT32 reg_blf_lut_val_cb_06            :8;	//(23:16,NA,48) //BLF pel weight LUT value, (06), CB
	UINT32 reg_blf_lut_val_cb_07            :8;	//(31:24,NA,43) //BLF pel weight LUT value, (07), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258BC RW 0x181D_2126
	UINT32 reg_blf_lut_val_cb_08            :8;	//(7:0,NA,38) //BLF pel weight LUT value, (08), CB
	UINT32 reg_blf_lut_val_cb_09            :8;	//(15:8,NA,33) //BLF pel weight LUT value, (09), CB
	UINT32 reg_blf_lut_val_cb_10            :8;	//(23:16,NA,29) //BLF pel weight LUT value, (10), CB
	UINT32 reg_blf_lut_val_cb_11            :8;	//(31:24,NA,24) //BLF pel weight LUT value, (11), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258C0 RW 0x0B0D_1114
	UINT32 reg_blf_lut_val_cb_12            :8;	//(7:0,NA,20) //BLF pel weight LUT value, (12), CB
	UINT32 reg_blf_lut_val_cb_13            :8;	//(15:8,NA,17) //BLF pel weight LUT value, (13), CB
	UINT32 reg_blf_lut_val_cb_14            :8;	//(23:16,NA,13) //BLF pel weight LUT value, (14), CB
	UINT32 reg_blf_lut_val_cb_15            :8;	//(31:24,NA,11) //BLF pel weight LUT value, (15), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258C4 RW 0x0305_0608
	UINT32 reg_blf_lut_val_cb_16            :8;	//(7:0,NA,8) //BLF pel weight LUT value, (16), CB
	UINT32 reg_blf_lut_val_cb_17            :8;	//(15:8,NA,6) //BLF pel weight LUT value, (17), CB
	UINT32 reg_blf_lut_val_cb_18            :8;	//(23:16,NA,5) //BLF pel weight LUT value, (18), CB
	UINT32 reg_blf_lut_val_cb_19            :8;	//(31:24,NA,3) //BLF pel weight LUT value, (19), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258C8 RW 0x0101_0202
	UINT32 reg_blf_lut_val_cb_20            :8;	//(7:0,NA,2) //BLF pel weight LUT value, (20), CB
	UINT32 reg_blf_lut_val_cb_21            :8;	//(15:8,NA,2) //BLF pel weight LUT value, (21), CB
	UINT32 reg_blf_lut_val_cb_22            :8;	//(23:16,NA,1) //BLF pel weight LUT value, (22), CB
	UINT32 reg_blf_lut_val_cb_23            :8;	//(31:24,NA,1) //BLF pel weight LUT value, (23), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258CC RW 0x0000_0000
	UINT32 reg_blf_lut_val_cb_24            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (24), CB
	UINT32 reg_blf_lut_val_cb_25            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (25), CB
	UINT32 reg_blf_lut_val_cb_26            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (26), CB
	UINT32 reg_blf_lut_val_cb_27            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (27), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258D0 RW 0x0000_0000
	UINT32 reg_blf_lut_val_cb_28            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (28), CB
	UINT32 reg_blf_lut_val_cb_29            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (29), CB
	UINT32 reg_blf_lut_val_cb_30            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (30), CB
	UINT32 reg_blf_lut_val_cb_31            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (31), CB
	};
}PE_O24_AMG2_MTB_BLF_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258D4 RW 0x3B3E_3F3F
	UINT32 reg_blf_lut_val_cr_00            :8;	//(7:0,NA,63) //BLF pel weight LUT value, (00), CR
	UINT32 reg_blf_lut_val_cr_01            :8;	//(15:8,NA,63) //BLF pel weight LUT value, (01), CR
	UINT32 reg_blf_lut_val_cr_02            :8;	//(23:16,NA,62) //BLF pel weight LUT value, (02), CR
	UINT32 reg_blf_lut_val_cr_03            :8;	//(31:24,NA,59) //BLF pel weight LUT value, (03), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258D8 RW 0x2B30_3438
	UINT32 reg_blf_lut_val_cr_04            :8;	//(7:0,NA,56) //BLF pel weight LUT value, (04), CR
	UINT32 reg_blf_lut_val_cr_05            :8;	//(15:8,NA,52) //BLF pel weight LUT value, (05), CR
	UINT32 reg_blf_lut_val_cr_06            :8;	//(23:16,NA,48) //BLF pel weight LUT value, (06), CR
	UINT32 reg_blf_lut_val_cr_07            :8;	//(31:24,NA,43) //BLF pel weight LUT value, (07), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258DC RW 0x181D_2126
	UINT32 reg_blf_lut_val_cr_08            :8;	//(7:0,NA,38) //BLF pel weight LUT value, (08), CR
	UINT32 reg_blf_lut_val_cr_09            :8;	//(15:8,NA,33) //BLF pel weight LUT value, (09), CR
	UINT32 reg_blf_lut_val_cr_10            :8;	//(23:16,NA,29) //BLF pel weight LUT value, (10), CR
	UINT32 reg_blf_lut_val_cr_11            :8;	//(31:24,NA,24) //BLF pel weight LUT value, (11), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258E0 RW 0x0B0D_1114
	UINT32 reg_blf_lut_val_cr_12            :8;	//(7:0,NA,20) //BLF pel weight LUT value, (12), CR
	UINT32 reg_blf_lut_val_cr_13            :8;	//(15:8,NA,17) //BLF pel weight LUT value, (13), CR
	UINT32 reg_blf_lut_val_cr_14            :8;	//(23:16,NA,13) //BLF pel weight LUT value, (14), CR
	UINT32 reg_blf_lut_val_cr_15            :8;	//(31:24,NA,11) //BLF pel weight LUT value, (15), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258E4 RW 0x0305_0608
	UINT32 reg_blf_lut_val_cr_16            :8;	//(7:0,NA,8) //BLF pel weight LUT value, (16), CR
	UINT32 reg_blf_lut_val_cr_17            :8;	//(15:8,NA,6) //BLF pel weight LUT value, (17), CR
	UINT32 reg_blf_lut_val_cr_18            :8;	//(23:16,NA,5) //BLF pel weight LUT value, (18), CR
	UINT32 reg_blf_lut_val_cr_19            :8;	//(31:24,NA,3) //BLF pel weight LUT value, (19), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258E8 RW 0x0101_0202
	UINT32 reg_blf_lut_val_cr_20            :8;	//(7:0,NA,2) //BLF pel weight LUT value, (20), CR
	UINT32 reg_blf_lut_val_cr_21            :8;	//(15:8,NA,2) //BLF pel weight LUT value, (21), CR
	UINT32 reg_blf_lut_val_cr_22            :8;	//(23:16,NA,1) //BLF pel weight LUT value, (22), CR
	UINT32 reg_blf_lut_val_cr_23            :8;	//(31:24,NA,1) //BLF pel weight LUT value, (23), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258EC RW 0x0000_0000
	UINT32 reg_blf_lut_val_cr_24            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (24), CR
	UINT32 reg_blf_lut_val_cr_25            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (25), CR
	UINT32 reg_blf_lut_val_cr_26            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (26), CR
	UINT32 reg_blf_lut_val_cr_27            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (27), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258F0 RW 0x0000_0000
	UINT32 reg_blf_lut_val_cr_28            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (28), CR
	UINT32 reg_blf_lut_val_cr_29            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (29), CR
	UINT32 reg_blf_lut_val_cr_30            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (30), CR
	UINT32 reg_blf_lut_val_cr_31            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (31), CR
	};
}PE_O24_AMG2_MTB_BLF_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258F4 RW 0x353B_3E3F
	UINT32 reg_blf_lut_val_spa_00           :8;	//(7:0,NA,63) //BLF spatial weight LUT value, [y0][x0]
	UINT32 reg_blf_lut_val_spa_01           :8;	//(15:8,NA,62) //BLF spatial weight LUT value, [y0][x1]
	UINT32 reg_blf_lut_val_spa_02           :8;	//(23:16,NA,59) //BLF spatial weight LUT value, [y0][x2]
	UINT32 reg_blf_lut_val_spa_03           :8;	//(31:24,NA,53) //BLF spatial weight LUT value, [y0][x3]
	};
}PE_O24_AMG2_MTB_BLF_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258F8 RW 0x393D_3E2E
	UINT32 reg_blf_lut_val_spa_04           :8;	//(7:0,NA,46) //BLF spatial weight LUT value, [y0][x4]
	UINT32 reg_blf_lut_val_spa_05           :8;	//(15:8,NA,62) //BLF spatial weight LUT value, [y1][x0]
	UINT32 reg_blf_lut_val_spa_06           :8;	//(23:16,NA,61) //BLF spatial weight LUT value, [y1][x1]
	UINT32 reg_blf_lut_val_spa_07           :8;	//(31:24,NA,57) //BLF spatial weight LUT value, [y1][x2] (cen)
	};
}PE_O24_AMG2_MTB_BLF_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8258FC RW 0x393B_2D34
	UINT32 reg_blf_lut_val_spa_08           :8;	//(7:0,NA,52) //BLF spatial weight LUT value, [y1][x3]
	UINT32 reg_blf_lut_val_spa_09           :8;	//(15:8,NA,45) //BLF spatial weight LUT value, [y1][x4]
	UINT32 reg_blf_lut_val_spa_10           :8;	//(23:16,NA,59) //BLF spatial weight LUT value, [y2][x0]
	UINT32 reg_blf_lut_val_spa_11           :8;	//(31:24,NA,57) //BLF spatial weight LUT value, [y2][x1]
	};
}PE_O24_AMG2_MTB_BLF_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825900 RW 0x002A_3136
	UINT32 reg_blf_lut_val_spa_12           :8;	//(7:0,NA,54) //BLF spatial weight LUT value, [y2][x2]
	UINT32 reg_blf_lut_val_spa_13           :8;	//(15:8,NA,49) //BLF spatial weight LUT value, [y2][x3]
	UINT32 reg_blf_lut_val_spa_14           :8;	//(23:16,NA,42) //BLF spatial weight LUT value, [y2][x4]
	UINT32 resvd                            :8;
	};
}PE_O24_AMG2_MTB_BLF_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825910 RW 0x0000_0001
	UINT32 reg_median_filt_en               :1;	//(0:0,NA,1) //Median filter enable
	UINT32 resvd                            :31;
	};
}PE_O24_AMG2_MTB_MEDIAN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC825920 RW 0x0000_0000
	UINT32 reg_dbg_mtb_mode                 :2;	//(1:0,NA,0) //Debug mode	0: Normal AMG output	1: Debug MC	2: Debug Basic	3: Debug Final
	UINT32 resvd0                           :2;
	UINT32 reg_dbg_mtb_map                  :5;	//(8:4,NA,0) //Debug mode map selection	00: Normal MTB output	01: CUR map	02: CUR map (CA)	03: PRV map	04: PRV map (CA)	05: MV, x	06: MV, y	07: Warp map	08: Warp mode	09: BLF map	10: BLF mode	11: Blend map	12: Blend alpha	13: Median map
	UINT32 resvd1                           :3;
	UINT32 reg_dbg_mv_shift                 :2;	//(13:12,NA,0) //Debug mode MV shift	0: MV shift 1 (<<1)	1: MV shift 2 (<<2)	2: MV shift 3 (<<3)	3: MV shift 4 (<<4)
	UINT32 resvd2                           :18;
	};
}PE_O24_AMG2_MTB_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259D0 RO 0x0000_0000
	UINT32 reg_mon_in_mv_sucfail            :8;	//(7:0,NA,0) //Core input (MV) success/fail monitoring register
	UINT32 reg_mon_in_mv_fin_vert           :8;	//(15:8,NA,0) //Core input (MV) previous frame vertical counter
	UINT32 reg_mon_in_mv_vert_cnt           :8;	//(23:16,NA,0) //Core input (MV) vertical counter
	UINT32 reg_mon_in_mv_hori_cnt           :8;	//(31:24,NA,0) //Core input (MV) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259D4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :8;	//(7:0,NA,0) //Core input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :8;	//(15:8,NA,0) //Core input (pel, Y) previous frame vertical counter
	UINT32 reg_mon_in_pel_y_vert_cnt        :8;	//(23:16,NA,0) //Core input (pel, Y) vertical counter
	UINT32 reg_mon_in_pel_y_hori_cnt        :8;	//(31:24,NA,0) //Core input (pel, Y) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259D8 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :8;	//(7:0,NA,0) //Core input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :8;	//(15:8,NA,0) //Core input (pel, C) previous frame vertical counter
	UINT32 reg_mon_in_pel_c_vert_cnt        :8;	//(23:16,NA,0) //Core input (pel, C) vertical counter
	UINT32 reg_mon_in_pel_c_hori_cnt        :8;	//(31:24,NA,0) //Core input (pel, C) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259DC RO 0x0000_0000
	UINT32 reg_mon_in_mc_prv_sucfail        :8;	//(7:0,NA,0) //Core input (MC, PRV) success/fail monitoring register
	UINT32 reg_mon_in_mc_prv_fin_vert       :8;	//(15:8,NA,0) //Core input (MC, PRV) previous frame vertical counter
	UINT32 reg_mon_in_mc_prv_vert_cnt       :8;	//(23:16,NA,0) //Core input (MC, PRV) vertical counter
	UINT32 reg_mon_in_mc_prv_hori_cnt       :8;	//(31:24,NA,0) //Core input (MC, PRV) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259E0 RO 0x0000_0000
	UINT32 reg_mon_in_mc_cur_sucfail        :8;	//(7:0,NA,0) //Core input (MC, CUR) success/fail monitoring register
	UINT32 reg_mon_in_mc_cur_fin_vert       :8;	//(15:8,NA,0) //Core input (MC, CUR) previous frame vertical counter
	UINT32 reg_mon_in_mc_cur_vert_cnt       :8;	//(23:16,NA,0) //Core input (MC, CUR) vertical counter
	UINT32 reg_mon_in_mc_cur_hori_cnt       :8;	//(31:24,NA,0) //Core input (MC, CUR) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259E4 RO 0x0000_0000
	UINT32 reg_mon_in_basic_prv_sucfail     :8;	//(7:0,NA,0) //Core input (Basic, PRV) success/fail monitoring register
	UINT32 reg_mon_in_basic_prv_fin_vert    :8;	//(15:8,NA,0) //Core input (Basic, PRV) previous frame vertical counter
	UINT32 reg_mon_in_basic_prv_vert_cnt    :8;	//(23:16,NA,0) //Core input (Basic, PRV) vertical counter
	UINT32 reg_mon_in_basic_prv_hori_cnt    :8;	//(31:24,NA,0) //Core input (Basic, PRV) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259E8 RO 0x0000_0000
	UINT32 reg_mon_in_basic_cur_sucfail     :8;	//(7:0,NA,0) //Core input (Basic, CUR) success/fail monitoring register
	UINT32 reg_mon_in_basic_cur_fin_vert    :8;	//(15:8,NA,0) //Core input (Basic, CUR) previous frame vertical counter
	UINT32 reg_mon_in_basic_cur_vert_cnt    :8;	//(23:16,NA,0) //Core input (Basic, CUR) vertical counter
	UINT32 reg_mon_in_basic_cur_hori_cnt    :8;	//(31:24,NA,0) //Core input (Basic, CUR) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259EC RO 0x0000_0000
	UINT32 reg_mon_in_final_mres_sucfail    :8;	//(7:0,NA,0) //Core input (Final, MC result) success/fail monitoring register
	UINT32 reg_mon_in_final_mres_fin_vert   :8;	//(15:8,NA,0) //Core input (Final, MC result) previous frame vertical counter
	UINT32 reg_mon_in_final_mres_vert_cnt   :8;	//(23:16,NA,0) //Core input (Final, MC result) vertical counter
	UINT32 reg_mon_in_final_mres_hori_cnt   :8;	//(31:24,NA,0) //Core input (Final, MC result) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259F0 RO 0x0000_0000
	UINT32 reg_mon_in_final_bres_sucfail    :8;	//(7:0,NA,0) //Core input (Final, Basic result) success/fail monitoring register
	UINT32 reg_mon_in_final_bres_fin_vert   :8;	//(15:8,NA,0) //Core input (Final, Basic result) previous frame vertical counter
	UINT32 reg_mon_in_final_bres_vert_cnt   :8;	//(23:16,NA,0) //Core input (Final, Basic result) vertical counter
	UINT32 reg_mon_in_final_bres_hori_cnt   :8;	//(31:24,NA,0) //Core input (Final, Basic result) horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8259F4 RO 0x0000_0000
	UINT32 reg_mon_out_sucfail              :8;	//(7:0,NA,0) //Core output success/fail monitoring register
	UINT32 reg_mon_out_fin_vert             :8;	//(15:8,NA,0) //Core output previous frame vertical counter
	UINT32 reg_mon_out_vert_cnt             :8;	//(23:16,NA,0) //Core output vertical counter
	UINT32 reg_mon_out_hori_cnt             :8;	//(31:24,NA,0) //Core output horizontal counter
	};
}PE_O24_AMG2_MTB_MTB_CORE_STAT_09_T;

typedef struct {
	PE_O24_AMG2_MTB_CA_CTRL_00_T                                ca_ctrl_00;	//0xCC825800
	PE_O24_AMG2_MTB_CA_CTRL_01_T                                ca_ctrl_01;	//0xCC825804
	PE_O24_AMG2_MTB_CA_CTRL_02_T                                ca_ctrl_02;	//0xCC825808
	PE_O24_AMG2_MTB_CA_CTRL_03_T                                ca_ctrl_03;	//0xCC82580C
	PE_O24_AMG2_MTB_CA_CTRL_04_T                                ca_ctrl_04;	//0xCC825810
	PE_O24_AMG2_MTB_CA_CTRL_05_T                                ca_ctrl_05;	//0xCC825814
	PE_O24_AMG2_MTB_CA_CTRL_06_T                                ca_ctrl_06;	//0xCC825818
	PE_O24_AMG2_MTB_CA_CTRL_07_T                                ca_ctrl_07;	//0xCC82581C
	PE_O24_AMG2_MTB_CA_CTRL_08_T                                ca_ctrl_08;	//0xCC825820
	PE_O24_AMG2_MTB_CA_CTRL_09_T                                ca_ctrl_09;	//0xCC825824
	PE_O24_AMG2_MTB_CA_CTRL_10_T                                ca_ctrl_10;	//0xCC825828
	PE_O24_AMG2_MTB_CA_CTRL_11_T                                ca_ctrl_11;	//0xCC82582C
	PE_O24_AMG2_MTB_CA_CTRL_12_T                                ca_ctrl_12;	//0xCC825830
	PE_O24_AMG2_MTB_CA_CTRL_13_T                                ca_ctrl_13;	//0xCC825834
	PE_O24_AMG2_MTB_CA_CTRL_14_T                                ca_ctrl_14;	//0xCC825838
	PE_O24_AMG2_MTB_CA_CTRL_15_T                                ca_ctrl_15;	//0xCC82583C
	PE_O24_AMG2_MTB_CA_CTRL_16_T                                ca_ctrl_16;	//0xCC825840
	PE_O24_AMG2_MTB_CA_CTRL_17_T                                ca_ctrl_17;	//0xCC825844
	PE_O24_AMG2_MTB_CA_CTRL_18_T                                ca_ctrl_18;	//0xCC825848
	PE_O24_AMG2_MTB_CA_CTRL_19_T                                ca_ctrl_19;	//0xCC82584C
	PE_O24_AMG2_MTB_CA_CTRL_20_T                                ca_ctrl_20;	//0xCC825850
	UINT32                                                    reserved0;	//0xCC825854
	UINT32                                                    reserved1;	//0xCC825858
	UINT32                                                    reserved2;	//0xCC82585C
	PE_O24_AMG2_MTB_BLEND_CTRL_00_T                          blend_ctrl_00;	//0xCC825860
	PE_O24_AMG2_MTB_BLEND_CTRL_01_T                          blend_ctrl_01;	//0xCC825864
	PE_O24_AMG2_MTB_BLEND_CTRL_02_T                          blend_ctrl_02;	//0xCC825868
	PE_O24_AMG2_MTB_BLEND_CTRL_03_T                          blend_ctrl_03;	//0xCC82586C
	PE_O24_AMG2_MTB_BLEND_CTRL_04_T                          blend_ctrl_04;	//0xCC825870
	PE_O24_AMG2_MTB_BLEND_CTRL_05_T                          blend_ctrl_05;	//0xCC825874
	PE_O24_AMG2_MTB_BLEND_CTRL_06_T                          blend_ctrl_06;	//0xCC825878
	PE_O24_AMG2_MTB_BLEND_CTRL_07_T                          blend_ctrl_07;	//0xCC82587C
	PE_O24_AMG2_MTB_BLEND_CTRL_08_T                          blend_ctrl_08;	//0xCC825880
	PE_O24_AMG2_MTB_BLEND_CTRL_09_T                          blend_ctrl_09;	//0xCC825884
	PE_O24_AMG2_MTB_WARP_CTRL_00_T                            warp_ctrl_00;	//0xCC825888
	UINT32                                                    reserved3;	//0xCC82588C
	PE_O24_AMG2_MTB_BLF_CTRL_00_T                              blf_ctrl_00;	//0xCC825890
	PE_O24_AMG2_MTB_BLF_CTRL_01_T                              blf_ctrl_01;	//0xCC825894
	PE_O24_AMG2_MTB_BLF_CTRL_02_T                              blf_ctrl_02;	//0xCC825898
	PE_O24_AMG2_MTB_BLF_CTRL_03_T                              blf_ctrl_03;	//0xCC82589C
	PE_O24_AMG2_MTB_BLF_CTRL_04_T                              blf_ctrl_04;	//0xCC8258A0
	PE_O24_AMG2_MTB_BLF_CTRL_05_T                              blf_ctrl_05;	//0xCC8258A4
	PE_O24_AMG2_MTB_BLF_CTRL_06_T                              blf_ctrl_06;	//0xCC8258A8
	PE_O24_AMG2_MTB_BLF_CTRL_07_T                              blf_ctrl_07;	//0xCC8258AC
	PE_O24_AMG2_MTB_BLF_CTRL_08_T                              blf_ctrl_08;	//0xCC8258B0
	PE_O24_AMG2_MTB_BLF_CTRL_09_T                              blf_ctrl_09;	//0xCC8258B4
	PE_O24_AMG2_MTB_BLF_CTRL_10_T                              blf_ctrl_10;	//0xCC8258B8
	PE_O24_AMG2_MTB_BLF_CTRL_11_T                              blf_ctrl_11;	//0xCC8258BC
	PE_O24_AMG2_MTB_BLF_CTRL_12_T                              blf_ctrl_12;	//0xCC8258C0
	PE_O24_AMG2_MTB_BLF_CTRL_13_T                              blf_ctrl_13;	//0xCC8258C4
	PE_O24_AMG2_MTB_BLF_CTRL_14_T                              blf_ctrl_14;	//0xCC8258C8
	PE_O24_AMG2_MTB_BLF_CTRL_15_T                              blf_ctrl_15;	//0xCC8258CC
	PE_O24_AMG2_MTB_BLF_CTRL_16_T                              blf_ctrl_16;	//0xCC8258D0
	PE_O24_AMG2_MTB_BLF_CTRL_17_T                              blf_ctrl_17;	//0xCC8258D4
	PE_O24_AMG2_MTB_BLF_CTRL_18_T                              blf_ctrl_18;	//0xCC8258D8
	PE_O24_AMG2_MTB_BLF_CTRL_19_T                              blf_ctrl_19;	//0xCC8258DC
	PE_O24_AMG2_MTB_BLF_CTRL_20_T                              blf_ctrl_20;	//0xCC8258E0
	PE_O24_AMG2_MTB_BLF_CTRL_21_T                              blf_ctrl_21;	//0xCC8258E4
	PE_O24_AMG2_MTB_BLF_CTRL_22_T                              blf_ctrl_22;	//0xCC8258E8
	PE_O24_AMG2_MTB_BLF_CTRL_23_T                              blf_ctrl_23;	//0xCC8258EC
	PE_O24_AMG2_MTB_BLF_CTRL_24_T                              blf_ctrl_24;	//0xCC8258F0
	PE_O24_AMG2_MTB_BLF_CTRL_25_T                              blf_ctrl_25;	//0xCC8258F4
	PE_O24_AMG2_MTB_BLF_CTRL_26_T                              blf_ctrl_26;	//0xCC8258F8
	PE_O24_AMG2_MTB_BLF_CTRL_27_T                              blf_ctrl_27;	//0xCC8258FC
	PE_O24_AMG2_MTB_BLF_CTRL_28_T                              blf_ctrl_28;	//0xCC825900
	UINT32                                                    reserved4;	//0xCC825904
	UINT32                                                    reserved5;	//0xCC825908
	UINT32                                                    reserved6;	//0xCC82590C
	PE_O24_AMG2_MTB_MEDIAN_CTRL_00_T                        median_ctrl_00;	//0xCC825910
	UINT32                                                    reserved7;	//0xCC825914
	UINT32                                                    reserved8;	//0xCC825918
	UINT32                                                    reserved9;	//0xCC82591C
	PE_O24_AMG2_MTB_DEBUG_CTRL_00_T                          debug_ctrl_00;	//0xCC825920
	UINT32                                                   reserved10;	//0xCC825924
	UINT32                                                   reserved11;	//0xCC825928
	UINT32                                                   reserved12;	//0xCC82592C
	UINT32                                                   reserved13;	//0xCC825930
	UINT32                                                   reserved14;	//0xCC825934
	UINT32                                                   reserved15;	//0xCC825938
	UINT32                                                   reserved16;	//0xCC82593C
	UINT32                                                   reserved17;	//0xCC825940
	UINT32                                                   reserved18;	//0xCC825944
	UINT32                                                   reserved19;	//0xCC825948
	UINT32                                                   reserved20;	//0xCC82594C
	UINT32                                                   reserved21;	//0xCC825950
	UINT32                                                   reserved22;	//0xCC825954
	UINT32                                                   reserved23;	//0xCC825958
	UINT32                                                   reserved24;	//0xCC82595C
	UINT32                                                   reserved25;	//0xCC825960
	UINT32                                                   reserved26;	//0xCC825964
	UINT32                                                   reserved27;	//0xCC825968
	UINT32                                                   reserved28;	//0xCC82596C
	UINT32                                                   reserved29;	//0xCC825970
	UINT32                                                   reserved30;	//0xCC825974
	UINT32                                                   reserved31;	//0xCC825978
	UINT32                                                   reserved32;	//0xCC82597C
	UINT32                                                   reserved33;	//0xCC825980
	UINT32                                                   reserved34;	//0xCC825984
	UINT32                                                   reserved35;	//0xCC825988
	UINT32                                                   reserved36;	//0xCC82598C
	UINT32                                                   reserved37;	//0xCC825990
	UINT32                                                   reserved38;	//0xCC825994
	UINT32                                                   reserved39;	//0xCC825998
	UINT32                                                   reserved40;	//0xCC82599C
	UINT32                                                   reserved41;	//0xCC8259A0
	UINT32                                                   reserved42;	//0xCC8259A4
	UINT32                                                   reserved43;	//0xCC8259A8
	UINT32                                                   reserved44;	//0xCC8259AC
	UINT32                                                   reserved45;	//0xCC8259B0
	UINT32                                                   reserved46;	//0xCC8259B4
	UINT32                                                   reserved47;	//0xCC8259B8
	UINT32                                                   reserved48;	//0xCC8259BC
	UINT32                                                   reserved49;	//0xCC8259C0
	UINT32                                                   reserved50;	//0xCC8259C4
	UINT32                                                   reserved51;	//0xCC8259C8
	UINT32                                                   reserved52;	//0xCC8259CC
	PE_O24_AMG2_MTB_MTB_CORE_STAT_00_T                    mtb_core_stat_00;	//0xCC8259D0
	PE_O24_AMG2_MTB_MTB_CORE_STAT_01_T                    mtb_core_stat_01;	//0xCC8259D4
	PE_O24_AMG2_MTB_MTB_CORE_STAT_02_T                    mtb_core_stat_02;	//0xCC8259D8
	PE_O24_AMG2_MTB_MTB_CORE_STAT_03_T                    mtb_core_stat_03;	//0xCC8259DC
	PE_O24_AMG2_MTB_MTB_CORE_STAT_04_T                    mtb_core_stat_04;	//0xCC8259E0
	PE_O24_AMG2_MTB_MTB_CORE_STAT_05_T                    mtb_core_stat_05;	//0xCC8259E4
	PE_O24_AMG2_MTB_MTB_CORE_STAT_06_T                    mtb_core_stat_06;	//0xCC8259E8
	PE_O24_AMG2_MTB_MTB_CORE_STAT_07_T                    mtb_core_stat_07;	//0xCC8259EC
	PE_O24_AMG2_MTB_MTB_CORE_STAT_08_T                    mtb_core_stat_08;	//0xCC8259F0
	PE_O24_AMG2_MTB_MTB_CORE_STAT_09_T                    mtb_core_stat_09;	//0xCC8259F4
}PE_AMG_MTB_REG_O24_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC826000 RW 0x0000_0001
	UINT32 reg_blur_filt_en                 :1;	//(0:0,NA,1) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O24_AMG3_GRM_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826004 RW 0x0007_0708
	UINT32 reg_blur_y_coef_0                :7;	//(6:0,NA,8) //Blur filter (Y) coefficient, [1][1] (center)
	UINT32 resvd0                           :1;
	UINT32 reg_blur_y_coef_1                :7;	//(14:8,NA,7) //Blur filter (Y) coefficient, [0][1],[1][0],[1][2],[2][1]
	UINT32 resvd1                           :1;
	UINT32 reg_blur_y_coef_2                :7;	//(22:16,NA,7) //Blur filter (Y) coefficient, [0][0],[0][2],[2][0],[2][2]
	UINT32 resvd2                           :9;
	};
}PE_O24_AMG3_GRM_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826008 RW 0x0007_0708
	UINT32 reg_blur_c_coef_0                :7;	//(6:0,NA,8) //Blur filter (C) coefficient, [1][1] (center)
	UINT32 resvd0                           :1;
	UINT32 reg_blur_c_coef_1                :7;	//(14:8,NA,7) //Blur filter (C) coefficient, [0][1],[1][0],[1][2],[2][1]
	UINT32 resvd1                           :1;
	UINT32 reg_blur_c_coef_2                :7;	//(22:16,NA,7) //Blur filter (C) coefficient, [0][0],[0][2],[2][0],[2][2]
	UINT32 resvd2                           :9;
	};
}PE_O24_AMG3_GRM_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826010 RW 0x7C98_12A0
	UINT32 reg_yc2rgb_coef0                 :15;	//(14:0,NA,4768) //YC2RGB coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef1                 :15;	//(30:16,NA,-872) //YC2RGB coefficient 1
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826014 RW 0x12A0_7775
	UINT32 reg_yc2rgb_coef2                 :15;	//(14:0,NA,-2187) //YC2RGB coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef3                 :15;	//(30:16,NA,4768) //YC2RGB coefficient 3
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826018 RW 0x0000_21D7
	UINT32 reg_yc2rgb_coef4                 :15;	//(14:0,NA,8663) //YC2RGB coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef5                 :15;	//(30:16,NA,0) //YC2RGB coefficient 5
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82601C RW 0x0000_12A0
	UINT32 reg_yc2rgb_coef6                 :15;	//(14:0,NA,4768) //YC2RGB coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef7                 :15;	//(30:16,NA,0) //YC2RGB coefficient 7
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826020 RW 0x0000_1CB0
	UINT32 reg_yc2rgb_coef8                 :15;	//(14:0,NA,7344) //YC2RGB coefficient 8
	UINT32 resvd                            :17;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826024 RW 0x0780_07F0
	UINT32 reg_yc2rgb_ofst0                 :11;	//(10:0,NA,-16) //YC2RGB offset 0
	UINT32 resvd0                           :5;
	UINT32 reg_yc2rgb_ofst1                 :11;	//(26:16,NA,-128) //YC2RGB offset 1
	UINT32 resvd1                           :5;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826028 RW 0x0000_0780
	UINT32 reg_yc2rgb_ofst2                 :11;	//(10:0,NA,-128) //YC2RGB offset 2
	UINT32 resvd0                           :5;
	UINT32 reg_yc2rgb_ofst3                 :11;	//(26:16,NA,0) //YC2RGB offset 3
	UINT32 resvd1                           :5;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82602C RW 0x0000_0000
	UINT32 reg_yc2rgb_ofst4                 :15;	//(14:0,NA,0) //YC2RGB offset 4
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_ofst5                 :15;	//(30:16,NA,0) //YC2RGB offset 5
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826030 RW 0x0080_8001
	UINT32 reg_rgb2hsv_sat_sel              :1;	//(0:0,NA,1) //RGB2HSV saturation selection (0: div_mode, 1: simple_mode)
	UINT32 resvd0                           :7;
	UINT32 reg_rgb2hsv_sgain                :8;	//(15:8,NA,128) //RGB2HSV saturation gain
	UINT32 reg_rgb2hsv_vgain                :8;	//(23:16,NA,128) //RGB2HSV value gain
	UINT32 resvd1                           :8;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826034 RW 0x0080_8080
	UINT32 reg_rgb2hsv_hoffset              :8;	//(7:0,NA,128) //RGB2HSV hue offset
	UINT32 reg_rgb2hsv_soffset              :8;	//(15:8,NA,128) //RGB2HSV saturation offset
	UINT32 reg_rgb2hsv_voffset              :8;	//(23:16,NA,128) //RGB2HSV value offset
	UINT32 resvd                            :8;
	};
}PE_O24_AMG3_GRM_YC2HSV_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826038 RW 0x5014_0000
	UINT32 reg_lut_depth_map_y0             :8;	//(7:0,NA,0) //LUT (depth map) control point, y0
	UINT32 reg_lut_depth_map_x0             :8;	//(15:8,NA,0) //LUT (depth map) control point, x0
	UINT32 reg_lut_depth_map_y1             :8;	//(23:16,NA,20) //LUT (depth map) control point, y1
	UINT32 reg_lut_depth_map_x1             :8;	//(31:24,NA,80) //LUT (depth map) control point, x1
	};
}PE_O24_AMG3_GRM_DEPTH_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82603C RW 0xFFFF_6E6E
	UINT32 reg_lut_depth_map_y2             :8;	//(7:0,NA,110) //LUT (depth map) control point, y2
	UINT32 reg_lut_depth_map_x2             :8;	//(15:8,NA,110) //LUT (depth map) control point, x2
	UINT32 reg_lut_depth_map_y3             :8;	//(23:16,NA,255) //LUT (depth map) control point, y3
	UINT32 reg_lut_depth_map_x3             :8;	//(31:24,NA,255) //LUT (depth map) control point, x3
	};
}PE_O24_AMG3_GRM_DEPTH_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826040 RW 0x64B4_0000
	UINT32 reg_rgn_LU_x_stt                 :8;	//(7:0,NA,0) //Region position (LU), x stt
	UINT32 reg_rgn_LU_y_stt                 :8;	//(15:8,NA,0) //Region position (LU), x end
	UINT32 reg_rgn_LU_x_end                 :8;	//(23:16,NA,180) //Region position (LU), y stt
	UINT32 reg_rgn_LU_y_end                 :8;	//(31:24,NA,100) //Region position (LU), y end
	};
}PE_O24_AMG3_GRM_REGION_POS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826044 RW 0x64F0_003C
	UINT32 reg_rgn_RU_x_stt                 :8;	//(7:0,NA,60) //Region position (RU), x stt
	UINT32 reg_rgn_RU_y_stt                 :8;	//(15:8,NA,0) //Region position (RU), x end
	UINT32 reg_rgn_RU_x_end                 :8;	//(23:16,NA,240) //Region position (RU), y stt
	UINT32 reg_rgn_RU_y_end                 :8;	//(31:24,NA,100) //Region position (RU), y end
	};
}PE_O24_AMG3_GRM_REGION_POS_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826048 RW 0x87B4_2200
	UINT32 reg_rgn_LD_x_stt                 :8;	//(7:0,NA,0) //Region position (LD), x stt
	UINT32 reg_rgn_LD_y_stt                 :8;	//(15:8,NA,34) //Region position (LD), x end
	UINT32 reg_rgn_LD_x_end                 :8;	//(23:16,NA,180) //Region position (LD), y stt
	UINT32 reg_rgn_LD_y_end                 :8;	//(31:24,NA,135) //Region position (LD), y end
	};
}PE_O24_AMG3_GRM_REGION_POS_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82604C RW 0x87F0_223C
	UINT32 reg_rgn_RD_x_stt                 :8;	//(7:0,NA,60) //Region position (RD), x stt
	UINT32 reg_rgn_RD_y_stt                 :8;	//(15:8,NA,34) //Region position (RD), x end
	UINT32 reg_rgn_RD_x_end                 :8;	//(23:16,NA,240) //Region position (RD), y stt
	UINT32 reg_rgn_RD_y_end                 :8;	//(31:24,NA,135) //Region position (RD), y end
	};
}PE_O24_AMG3_GRM_REGION_POS_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826050 RW 0x0000_3200
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection (0: LU, 1: RU, 2: LD, 3: RD)
	UINT32 resvd0                           :6;
	UINT32 reg_depth_hist_th                :8;	//(15:8,NA,50) //Depth map threshold for histogram
	UINT32 resvd1                           :16;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826054 RW 0xFFFF_281E
	UINT32 reg_sat_h_hist_th                :8;	//(7:0,NA,30) //Saturation threshold for HUE histogram
	UINT32 reg_val_h_hist_th                :8;	//(15:8,NA,40) //Value threshold for HUE histogram
	UINT32 reg_sat_v_hist_th                :8;	//(23:16,NA,255) //Saturation threshold for VAL histogram
	UINT32 reg_val_v_hist_th                :8;	//(31:24,NA,255) //Value threshold for VAL histogram
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826058 RW 0x0300_0301
	UINT32 reg_hist_frame_step              :8;	//(7:0,NA,1) //Histogram IIR frame step
	UINT32 reg_hist_step_size               :8;	//(15:8,NA,3) //Histogram IIR step size
	UINT32 reg_hist_fw_ctrl_en              :1;	//(16:16,NA,0) //Histogram IIR FW cotrol enable
	UINT32 resvd                            :7;
	UINT32 reg_hist_fw_step_size            :8;	//(31:24,NA,3) //Histogram IIR FW step size
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82605C RW 0x0033_0033
	UINT32 reg_hue_coef_0                   :9;	//(8:0,NA,51) //Histogram filter (HUE) coefficient, [ 6] (center)
	UINT32 resvd0                           :7;
	UINT32 reg_hue_coef_1                   :9;	//(24:16,NA,51) //Histogram filter (HUE) coefficient, [ 5][ 7]
	UINT32 resvd1                           :7;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826060 RW 0x0000_0033
	UINT32 reg_hue_coef_2                   :9;	//(8:0,NA,51) //Histogram filter (HUE) coefficient, [ 4][ 8]
	UINT32 resvd0                           :7;
	UINT32 reg_hue_coef_3                   :9;	//(24:16,NA,0) //Histogram filter (HUE) coefficient, [ 3][ 9]
	UINT32 resvd1                           :7;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826064 RW 0x0000_0000
	UINT32 reg_hue_coef_4                   :9;	//(8:0,NA,0) //Histogram filter (HUE) coefficient, [ 2][10]
	UINT32 resvd0                           :7;
	UINT32 reg_hue_coef_5                   :9;	//(24:16,NA,0) //Histogram filter (HUE) coefficient, [ 1][11]
	UINT32 resvd1                           :7;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826068 RW 0x0000_0000
	UINT32 reg_hue_coef_6                   :9;	//(8:0,NA,0) //Histogram filter (HUE) coefficient, [ 0][12]
	UINT32 resvd                            :23;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82606C RW 0x0033_0033
	UINT32 reg_val_coef_0                   :9;	//(8:0,NA,51) //Histogram filter (VAL) coefficient, [ 6] (center)
	UINT32 resvd0                           :7;
	UINT32 reg_val_coef_1                   :9;	//(24:16,NA,51) //Histogram filter (VAL) coefficient, [ 5][ 7]
	UINT32 resvd1                           :7;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826070 RW 0x0000_0033
	UINT32 reg_val_coef_2                   :9;	//(8:0,NA,51) //Histogram filter (VAL) coefficient, [ 4][ 8]
	UINT32 resvd0                           :7;
	UINT32 reg_val_coef_3                   :9;	//(24:16,NA,0) //Histogram filter (VAL) coefficient, [ 3][ 9]
	UINT32 resvd1                           :7;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826074 RW 0x0000_0000
	UINT32 reg_val_coef_4                   :9;	//(8:0,NA,0) //Histogram filter (VAL) coefficient, [ 2][10]
	UINT32 resvd0                           :7;
	UINT32 reg_val_coef_5                   :9;	//(24:16,NA,0) //Histogram filter (VAL) coefficient, [ 1][11]
	UINT32 resvd1                           :7;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826078 RW 0x0000_0000
	UINT32 reg_val_coef_6                   :9;	//(8:0,NA,0) //Histogram filter (VAL) coefficient, [ 0][12]
	UINT32 resvd                            :23;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82607C RO 0x0000_0000
	UINT32 reg_hist_bg_hue_00               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 0)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_00               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 0)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826080 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_01               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 1)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_01               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 1)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826084 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_02               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 2)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_02               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 2)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826088 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_03               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 3)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_03               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 3)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82608C RO 0x0000_0000
	UINT32 reg_hist_bg_hue_04               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 4)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_04               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 4)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826090 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_05               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 5)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_05               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 5)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826094 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_06               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 6)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_06               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 6)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826098 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_07               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 7)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_07               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 7)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82609C RO 0x0000_0000
	UINT32 reg_hist_bg_hue_08               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 8)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_08               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 8)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260A0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_09               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 9)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_09               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 9)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260A4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_10               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 10)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_10               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 10)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260A8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_11               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 11)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_11               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 11)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260AC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_12               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 12)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_12               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 12)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260B0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_13               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 13)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_13               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 13)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260B4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_14               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 14)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_14               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 14)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260B8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_15               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 15)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_15               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 15)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260BC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_16               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 16)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_16               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 16)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260C0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_17               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 17)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_17               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 17)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260C4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_18               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 18)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_18               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 18)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260C8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_19               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 19)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_19               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 19)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260CC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_20               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 20)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_20               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 20)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260D0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_21               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 21)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_21               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 21)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260D4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_22               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 22)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_22               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 22)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260D8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_23               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 23)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_23               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 23)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260DC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_24               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 24)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_24               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 24)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260E0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_25               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 25)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_25               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 25)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260E4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_26               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 26)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_26               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 26)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260E8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_27               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 27)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_27               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 27)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260EC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_28               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 28)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_28               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 28)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260F0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_29               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 29)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_29               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 29)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260F4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_30               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 30)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_30               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 30)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260F8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_31               :15;	//(14:0,NA,0) //Histogram read data (BG, HUE, bin 31)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_hue_31               :15;	//(30:16,NA,0) //Histogram read data (FG, HUE, bin 31)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8260FC RO 0x0000_0000
	UINT32 reg_hist_bg_val_00               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 0)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_00               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 0)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826100 RO 0x0000_0000
	UINT32 reg_hist_bg_val_01               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 1)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_01               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 1)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826104 RO 0x0000_0000
	UINT32 reg_hist_bg_val_02               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 2)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_02               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 2)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826108 RO 0x0000_0000
	UINT32 reg_hist_bg_val_03               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 3)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_03               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 3)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82610C RO 0x0000_0000
	UINT32 reg_hist_bg_val_04               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 4)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_04               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 4)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826110 RO 0x0000_0000
	UINT32 reg_hist_bg_val_05               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 5)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_05               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 5)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826114 RO 0x0000_0000
	UINT32 reg_hist_bg_val_06               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 6)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_06               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 6)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826118 RO 0x0000_0000
	UINT32 reg_hist_bg_val_07               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 7)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_07               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 7)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82611C RO 0x0000_0000
	UINT32 reg_hist_bg_val_08               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 8)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_08               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 8)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826120 RO 0x0000_0000
	UINT32 reg_hist_bg_val_09               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 9)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_09               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 9)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826124 RO 0x0000_0000
	UINT32 reg_hist_bg_val_10               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 10)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_10               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 10)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826128 RO 0x0000_0000
	UINT32 reg_hist_bg_val_11               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 11)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_11               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 11)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82612C RO 0x0000_0000
	UINT32 reg_hist_bg_val_12               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 12)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_12               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 12)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826130 RO 0x0000_0000
	UINT32 reg_hist_bg_val_13               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 13)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_13               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 13)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826134 RO 0x0000_0000
	UINT32 reg_hist_bg_val_14               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 14)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_14               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 14)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826138 RO 0x0000_0000
	UINT32 reg_hist_bg_val_15               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 15)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_15               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 15)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82613C RO 0x0000_0000
	UINT32 reg_hist_bg_val_16               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 16)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_16               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 16)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826140 RO 0x0000_0000
	UINT32 reg_hist_bg_val_17               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 17)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_17               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 17)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826144 RO 0x0000_0000
	UINT32 reg_hist_bg_val_18               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 18)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_18               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 18)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826148 RO 0x0000_0000
	UINT32 reg_hist_bg_val_19               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 19)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_19               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 19)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82614C RO 0x0000_0000
	UINT32 reg_hist_bg_val_20               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 20)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_20               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 20)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826150 RO 0x0000_0000
	UINT32 reg_hist_bg_val_21               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 21)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_21               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 21)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826154 RO 0x0000_0000
	UINT32 reg_hist_bg_val_22               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 22)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_22               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 22)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826158 RO 0x0000_0000
	UINT32 reg_hist_bg_val_23               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 23)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_23               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 23)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82615C RO 0x0000_0000
	UINT32 reg_hist_bg_val_24               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 24)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_24               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 24)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826160 RO 0x0000_0000
	UINT32 reg_hist_bg_val_25               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 25)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_25               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 25)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826164 RO 0x0000_0000
	UINT32 reg_hist_bg_val_26               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 26)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_26               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 26)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826168 RO 0x0000_0000
	UINT32 reg_hist_bg_val_27               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 27)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_27               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 27)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82616C RO 0x0000_0000
	UINT32 reg_hist_bg_val_28               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 28)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_28               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 28)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826170 RO 0x0000_0000
	UINT32 reg_hist_bg_val_29               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 29)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_29               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 29)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826174 RO 0x0000_0000
	UINT32 reg_hist_bg_val_30               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 30)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_30               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 30)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826178 RO 0x0000_0000
	UINT32 reg_hist_bg_val_31               :15;	//(14:0,NA,0) //Histogram read data (BG, VAL, bin 31)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_fg_val_31               :15;	//(30:16,NA,0) //Histogram read data (FG, VAL, bin 31)
	UINT32 resvd1                           :1;
	};
}PE_O24_AMG3_GRM_HISTOGRAM_STAT_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826180 RW 0x0000_0110
	UINT32 reg_sv_map_mode                  :1;	//(0:0,NA,0) //SV map mode
	UINT32 resvd0                           :3;
	UINT32 reg_sv_map_shift                 :2;	//(5:4,NA,1) //SV map shift (0: shift6, 1: shift7, 2: shift8, 3: shift9)
	UINT32 resvd1                           :2;
	UINT32 reg_sv_post_shift                :2;	//(9:8,NA,1) //SV post map shift (0: shift6, 1: shift7, 2: shift8, 3: shift9)
	UINT32 resvd2                           :22;
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826184 RW 0x64AD_1400
	UINT32 reg_sat_lut_y0                   :8;	//(7:0,NA,0) //SAT LUT points, y0
	UINT32 reg_sat_lut_x0                   :8;	//(15:8,NA,20) //SAT LUT points, x0
	UINT32 reg_sat_lut_y1                   :8;	//(23:16,NA,173) //SAT LUT points, y1
	UINT32 reg_sat_lut_x1                   :8;	//(31:24,NA,100) //SAT LUT points, x1
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826188 RW 0xFFFF_C7FF
	UINT32 reg_sat_lut_y2                   :8;	//(7:0,NA,255) //SAT LUT points, y2
	UINT32 reg_sat_lut_x2                   :8;	//(15:8,NA,199) //SAT LUT points, x2
	UINT32 reg_sat_lut_y3                   :8;	//(23:16,NA,255) //SAT LUT points, y3
	UINT32 reg_sat_lut_x3                   :8;	//(31:24,NA,255) //SAT LUT points, x3
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC82618C RW 0x1E00_0000
	UINT32 reg_val_lut_y0                   :8;	//(7:0,NA,0) //VAL LUT points, y0
	UINT32 reg_val_lut_x0                   :8;	//(15:8,NA,0) //VAL LUT points, x0
	UINT32 reg_val_lut_y1                   :8;	//(23:16,NA,0) //VAL LUT points, y1
	UINT32 reg_val_lut_x1                   :8;	//(31:24,NA,30) //VAL LUT points, x1
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826190 RW 0xFFFF_8080
	UINT32 reg_val_lut_y2                   :8;	//(7:0,NA,128) //VAL LUT points, y2
	UINT32 reg_val_lut_x2                   :8;	//(15:8,NA,128) //VAL LUT points, x2
	UINT32 reg_val_lut_y3                   :8;	//(23:16,NA,255) //VAL LUT points, y3
	UINT32 reg_val_lut_x3                   :8;	//(31:24,NA,255) //VAL LUT points, x3
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826194 RW 0x3CFF_00C8
	UINT32 reg_sv_map_lut_y0                :8;	//(7:0,NA,200) //SV map LUT points, y0
	UINT32 reg_sv_map_lut_x0                :8;	//(15:8,NA,0) //SV map LUT points, x0
	UINT32 reg_sv_map_lut_y1                :8;	//(23:16,NA,255) //SV map LUT points, y1
	UINT32 reg_sv_map_lut_x1                :8;	//(31:24,NA,60) //SV map LUT points, x1
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC826198 RW 0xFFFF_80A0
	UINT32 reg_sv_map_lut_y2                :8;	//(7:0,NA,160) //SV map LUT points, y2
	UINT32 reg_sv_map_lut_x2                :8;	//(15:8,NA,128) //SV map LUT points, x2
	UINT32 reg_sv_map_lut_y3                :8;	//(23:16,NA,255) //SV map LUT points, y3
	UINT32 reg_sv_map_lut_x3                :8;	//(31:24,NA,255) //SV map LUT points, x3
	};
}PE_O24_AMG3_GRM_SV_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261A0 RW 0x0000_12C1
	UINT32 reg_max_hue_clip                 :1;	//(0:0,NA,1) //Manual max clip enable, HUE
	UINT32 resvd0                           :3;
	UINT32 reg_max_hue                      :15;	//(18:4,NA,300) //Manual max clip value, HUE
	UINT32 resvd1                           :13;
	};
}PE_O24_AMG3_GRM_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261A4 RW 0x0000_2BC1
	UINT32 reg_max_val_clip                 :1;	//(0:0,NA,1) //Manual max clip enable, VAL
	UINT32 resvd0                           :3;
	UINT32 reg_max_val                      :15;	//(18:4,NA,700) //Manual max clip value, VAL
	UINT32 resvd1                           :13;
	};
}PE_O24_AMG3_GRM_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261A8 RW 0x0000_0100
	UINT32 reg_norm_hue_factor              :9;	//(8:0,NA,256) //Normalization factor, HUE
	UINT32 resvd0                           :3;
	UINT32 reg_norm_hue_offset              :10;	//(21:12,NA,0) //Normalization offset, HUE
	UINT32 resvd1                           :10;
	};
}PE_O24_AMG3_GRM_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261AC RW 0x0000_1080
	UINT32 reg_norm_val_factor              :9;	//(8:0,NA,128) //Normalization factor, VAL
	UINT32 resvd0                           :3;
	UINT32 reg_norm_val_offset              :10;	//(21:12,NA,1) //Normalization offset, VAL
	UINT32 resvd1                           :10;
	};
}PE_O24_AMG3_GRM_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261B0 RW 0x0800_1001
	UINT32 reg_ratio_hue_fg_offset          :10;	//(9:0,NA,1) //Gain ratio offset, FG, HUE
	UINT32 resvd0                           :2;
	UINT32 reg_ratio_hue_bg_offset          :10;	//(21:12,NA,1) //Gain ratio offset, BG, HUE
	UINT32 resvd1                           :2;
	UINT32 reg_ratio_hue_shift              :4;	//(27:24,NA,8) //Gain ratio shift, HUE
	UINT32 resvd2                           :4;
	};
}PE_O24_AMG3_GRM_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261B4 RW 0x0706_4001
	UINT32 reg_ratio_val_fg_offset          :10;	//(9:0,NA,1) //Gain ratio offset, FG, VAL
	UINT32 resvd0                           :2;
	UINT32 reg_ratio_val_bg_offset          :10;	//(21:12,NA,100) //Gain ratio offset, BG, VAL
	UINT32 resvd1                           :2;
	UINT32 reg_ratio_val_shift              :4;	//(27:24,NA,7) //Gain ratio shift, VAL
	UINT32 resvd2                           :4;
	};
}PE_O24_AMG3_GRM_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261C0 RW 0x4060_0028
	UINT32 reg_grm_lut_y0                   :8;	//(7:0,NA,40) //Final GRM LUT points, y0
	UINT32 reg_grm_lut_x0                   :8;	//(15:8,NA,0) //Final GRM LUT points, x0
	UINT32 reg_grm_lut_y1                   :8;	//(23:16,NA,96) //Final GRM LUT points, y1
	UINT32 reg_grm_lut_x1                   :8;	//(31:24,NA,64) //Final GRM LUT points, x1
	};
}PE_O24_AMG3_GRM_GRM_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261C4 RW 0xFFFF_80A0
	UINT32 reg_grm_lut_y2                   :8;	//(7:0,NA,160) //Final GRM LUT points, y2
	UINT32 reg_grm_lut_x2                   :8;	//(15:8,NA,128) //Final GRM LUT points, x2
	UINT32 reg_grm_lut_y3                   :8;	//(23:16,NA,255) //Final GRM LUT points, y3
	UINT32 reg_grm_lut_x3                   :8;	//(31:24,NA,255) //Final GRM LUT points, x3
	};
}PE_O24_AMG3_GRM_GRM_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261D0 RW 0x2800_0000
	UINT32 reg_lut_db_grm_y0                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y0
	UINT32 reg_lut_db_grm_x0                :8;	//(15:8,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), x0
	UINT32 reg_lut_db_grm_y1                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y1
	UINT32 reg_lut_db_grm_x1                :8;	//(31:24,NA,40) //LUT (DB GRM blend) control point (for DepthBody>GRM), x1
	};
}PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261D4 RW 0xFF00_5000
	UINT32 reg_lut_db_grm_y2                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y2
	UINT32 reg_lut_db_grm_x2                :8;	//(15:8,NA,80) //LUT (DB GRM blend) control point (for DepthBody>GRM), x2
	UINT32 reg_lut_db_grm_y3                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y3
	UINT32 reg_lut_db_grm_x3                :8;	//(31:24,NA,255) //LUT (DB GRM blend) control point (for DepthBody>GRM), x3
	};
}PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261D8 RW 0x2800_0000
	UINT32 reg_lut_grm_db_y0                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y0
	UINT32 reg_lut_grm_db_x0                :8;	//(15:8,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x0
	UINT32 reg_lut_grm_db_y1                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y1
	UINT32 reg_lut_grm_db_x1                :8;	//(31:24,NA,40) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x1
	};
}PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261DC RW 0xFF00_5000
	UINT32 reg_lut_grm_db_y2                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y2
	UINT32 reg_lut_grm_db_x2                :8;	//(15:8,NA,80) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x2
	UINT32 reg_lut_grm_db_y3                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y3
	UINT32 reg_lut_grm_db_x3                :8;	//(31:24,NA,255) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x3
	};
}PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261E0 RW 0x2800_0000
	UINT32 reg_lut_dbg_mtb_y0               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y0
	UINT32 reg_lut_dbg_mtb_x0               :8;	//(15:8,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x0
	UINT32 reg_lut_dbg_mtb_y1               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y1
	UINT32 reg_lut_dbg_mtb_x1               :8;	//(31:24,NA,40) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x1
	};
}PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261E4 RW 0xFF00_5000
	UINT32 reg_lut_dbg_mtb_y2               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y2
	UINT32 reg_lut_dbg_mtb_x2               :8;	//(15:8,NA,80) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x2
	UINT32 reg_lut_dbg_mtb_y3               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y3
	UINT32 reg_lut_dbg_mtb_x3               :8;	//(31:24,NA,255) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x3
	};
}PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261E8 RW 0x2800_0000
	UINT32 reg_lut_mtb_dbg_y0               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y0
	UINT32 reg_lut_mtb_dbg_x0               :8;	//(15:8,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x0
	UINT32 reg_lut_mtb_dbg_y1               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y1
	UINT32 reg_lut_mtb_dbg_x1               :8;	//(31:24,NA,40) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x1
	};
}PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261EC RW 0xFF00_5000
	UINT32 reg_lut_mtb_dbg_y2               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y2
	UINT32 reg_lut_mtb_dbg_x2               :8;	//(15:8,NA,80) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x2
	UINT32 reg_lut_mtb_dbg_y3               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y3
	UINT32 reg_lut_mtb_dbg_x3               :8;	//(31:24,NA,255) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x3
	};
}PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8261F0 RW 0x0000_0000
	UINT32 reg_dbg_grm_mode                 :4;	//(3:0,NA,0) //Debug mode	0: Normal AMG output	1: HUE	2: SAT	3: VAL	4: SV blend map (pre)	5: SV blend map (post)	6: Final gain, HUE	7: Final gain, VAL	8: GRM result	9: GRM blend map
	UINT32 resvd0                           :4;
	UINT32 reg_dbg_grm_rgn                  :2;	//(9:8,NA,0) //Debug mode region selction (for debug mode 6~8)	0: LU	1: RU	2: LD	3: RD
	UINT32 resvd1                           :22;
	};
}PE_O24_AMG3_GRM_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8262F0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :8;	//(7:0,NA,0) //Core input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :8;	//(15:8,NA,0) //Core input (pel, Y) previous frame vertical counter
	UINT32 reg_mon_in_pel_y_vert_cnt        :8;	//(23:16,NA,0) //Core input (pel, Y) vertical counter
	UINT32 reg_mon_in_pel_y_hori_cnt        :8;	//(31:24,NA,0) //Core input (pel, Y) horizontal counter
	};
}PE_O24_AMG3_GRM_GRM_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8262F4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :8;	//(7:0,NA,0) //Core input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :8;	//(15:8,NA,0) //Core input (pel, C) previous frame vertical counter
	UINT32 reg_mon_in_pel_c_vert_cnt        :8;	//(23:16,NA,0) //Core input (pel, C) vertical counter
	UINT32 reg_mon_in_pel_c_hori_cnt        :8;	//(31:24,NA,0) //Core input (pel, C) horizontal counter
	};
}PE_O24_AMG3_GRM_GRM_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8262F8 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :8;	//(7:0,NA,0) //Core input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :8;	//(15:8,NA,0) //Core input (depth map) previous frame vertical counter
	UINT32 reg_mon_in_depth_vert_cnt        :8;	//(23:16,NA,0) //Core input (depth map) vertical counter
	UINT32 reg_mon_in_depth_hori_cnt        :8;	//(31:24,NA,0) //Core input (depth map) horizontal counter
	};
}PE_O24_AMG3_GRM_GRM_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8262FC RO 0x0000_0000
	UINT32 reg_mon_out_sucfail              :8;	//(7:0,NA,0) //Core output success/fail monitoring register
	UINT32 reg_mon_out_fin_vert             :8;	//(15:8,NA,0) //Core output previous frame vertical counter
	UINT32 reg_mon_out_vert_cnt             :8;	//(23:16,NA,0) //Core output vertical counter
	UINT32 reg_mon_out_hori_cnt             :8;	//(31:24,NA,0) //Core output horizontal counter
	};
}PE_O24_AMG3_GRM_GRM_CORE_STAT_03_T;

typedef struct {
	PE_O24_AMG3_GRM_BLUR_CTRL_00_T                            blur_ctrl_00;	//0xCC826000
	PE_O24_AMG3_GRM_BLUR_CTRL_01_T                            blur_ctrl_01;	//0xCC826004
	PE_O24_AMG3_GRM_BLUR_CTRL_02_T                            blur_ctrl_02;	//0xCC826008
	UINT32                                                    reserved0;	//0xCC82600C
	PE_O24_AMG3_GRM_YC2HSV_CTRL_00_T                        yc2hsv_ctrl_00;	//0xCC826010
	PE_O24_AMG3_GRM_YC2HSV_CTRL_01_T                        yc2hsv_ctrl_01;	//0xCC826014
	PE_O24_AMG3_GRM_YC2HSV_CTRL_02_T                        yc2hsv_ctrl_02;	//0xCC826018
	PE_O24_AMG3_GRM_YC2HSV_CTRL_03_T                        yc2hsv_ctrl_03;	//0xCC82601C
	PE_O24_AMG3_GRM_YC2HSV_CTRL_04_T                        yc2hsv_ctrl_04;	//0xCC826020
	PE_O24_AMG3_GRM_YC2HSV_CTRL_05_T                        yc2hsv_ctrl_05;	//0xCC826024
	PE_O24_AMG3_GRM_YC2HSV_CTRL_06_T                        yc2hsv_ctrl_06;	//0xCC826028
	PE_O24_AMG3_GRM_YC2HSV_CTRL_07_T                        yc2hsv_ctrl_07;	//0xCC82602C
	PE_O24_AMG3_GRM_YC2HSV_CTRL_08_T                        yc2hsv_ctrl_08;	//0xCC826030
	PE_O24_AMG3_GRM_YC2HSV_CTRL_09_T                        yc2hsv_ctrl_09;	//0xCC826034
	PE_O24_AMG3_GRM_DEPTH_CTRL_00_T                          depth_ctrl_00;	//0xCC826038
	PE_O24_AMG3_GRM_DEPTH_CTRL_01_T                          depth_ctrl_01;	//0xCC82603C
	PE_O24_AMG3_GRM_REGION_POS_CTRL_00_T                region_pos_ctrl_00;	//0xCC826040
	PE_O24_AMG3_GRM_REGION_POS_CTRL_01_T                region_pos_ctrl_01;	//0xCC826044
	PE_O24_AMG3_GRM_REGION_POS_CTRL_02_T                region_pos_ctrl_02;	//0xCC826048
	PE_O24_AMG3_GRM_REGION_POS_CTRL_03_T                region_pos_ctrl_03;	//0xCC82604C
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_00_T                  histogram_ctrl_00;	//0xCC826050
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_01_T                  histogram_ctrl_01;	//0xCC826054
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_02_T                  histogram_ctrl_02;	//0xCC826058
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_03_T                  histogram_ctrl_03;	//0xCC82605C
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_04_T                  histogram_ctrl_04;	//0xCC826060
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_05_T                  histogram_ctrl_05;	//0xCC826064
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_06_T                  histogram_ctrl_06;	//0xCC826068
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_07_T                  histogram_ctrl_07;	//0xCC82606C
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_08_T                  histogram_ctrl_08;	//0xCC826070
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_09_T                  histogram_ctrl_09;	//0xCC826074
	PE_O24_AMG3_GRM_HISTOGRAM_CTRL_10_T                  histogram_ctrl_10;	//0xCC826078
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_00_T                  histogram_stat_00;	//0xCC82607C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_01_T                  histogram_stat_01;	//0xCC826080
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_02_T                  histogram_stat_02;	//0xCC826084
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_03_T                  histogram_stat_03;	//0xCC826088
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_04_T                  histogram_stat_04;	//0xCC82608C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_05_T                  histogram_stat_05;	//0xCC826090
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_06_T                  histogram_stat_06;	//0xCC826094
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_07_T                  histogram_stat_07;	//0xCC826098
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_08_T                  histogram_stat_08;	//0xCC82609C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_09_T                  histogram_stat_09;	//0xCC8260A0
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_10_T                  histogram_stat_10;	//0xCC8260A4
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_11_T                  histogram_stat_11;	//0xCC8260A8
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_12_T                  histogram_stat_12;	//0xCC8260AC
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_13_T                  histogram_stat_13;	//0xCC8260B0
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_14_T                  histogram_stat_14;	//0xCC8260B4
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_15_T                  histogram_stat_15;	//0xCC8260B8
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_16_T                  histogram_stat_16;	//0xCC8260BC
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_17_T                  histogram_stat_17;	//0xCC8260C0
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_18_T                  histogram_stat_18;	//0xCC8260C4
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_19_T                  histogram_stat_19;	//0xCC8260C8
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_20_T                  histogram_stat_20;	//0xCC8260CC
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_21_T                  histogram_stat_21;	//0xCC8260D0
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_22_T                  histogram_stat_22;	//0xCC8260D4
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_23_T                  histogram_stat_23;	//0xCC8260D8
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_24_T                  histogram_stat_24;	//0xCC8260DC
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_25_T                  histogram_stat_25;	//0xCC8260E0
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_26_T                  histogram_stat_26;	//0xCC8260E4
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_27_T                  histogram_stat_27;	//0xCC8260E8
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_28_T                  histogram_stat_28;	//0xCC8260EC
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_29_T                  histogram_stat_29;	//0xCC8260F0
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_30_T                  histogram_stat_30;	//0xCC8260F4
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_31_T                  histogram_stat_31;	//0xCC8260F8
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_32_T                  histogram_stat_32;	//0xCC8260FC
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_33_T                  histogram_stat_33;	//0xCC826100
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_34_T                  histogram_stat_34;	//0xCC826104
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_35_T                  histogram_stat_35;	//0xCC826108
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_36_T                  histogram_stat_36;	//0xCC82610C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_37_T                  histogram_stat_37;	//0xCC826110
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_38_T                  histogram_stat_38;	//0xCC826114
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_39_T                  histogram_stat_39;	//0xCC826118
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_40_T                  histogram_stat_40;	//0xCC82611C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_41_T                  histogram_stat_41;	//0xCC826120
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_42_T                  histogram_stat_42;	//0xCC826124
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_43_T                  histogram_stat_43;	//0xCC826128
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_44_T                  histogram_stat_44;	//0xCC82612C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_45_T                  histogram_stat_45;	//0xCC826130
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_46_T                  histogram_stat_46;	//0xCC826134
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_47_T                  histogram_stat_47;	//0xCC826138
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_48_T                  histogram_stat_48;	//0xCC82613C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_49_T                  histogram_stat_49;	//0xCC826140
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_50_T                  histogram_stat_50;	//0xCC826144
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_51_T                  histogram_stat_51;	//0xCC826148
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_52_T                  histogram_stat_52;	//0xCC82614C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_53_T                  histogram_stat_53;	//0xCC826150
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_54_T                  histogram_stat_54;	//0xCC826154
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_55_T                  histogram_stat_55;	//0xCC826158
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_56_T                  histogram_stat_56;	//0xCC82615C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_57_T                  histogram_stat_57;	//0xCC826160
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_58_T                  histogram_stat_58;	//0xCC826164
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_59_T                  histogram_stat_59;	//0xCC826168
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_60_T                  histogram_stat_60;	//0xCC82616C
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_61_T                  histogram_stat_61;	//0xCC826170
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_62_T                  histogram_stat_62;	//0xCC826174
	PE_O24_AMG3_GRM_HISTOGRAM_STAT_63_T                  histogram_stat_63;	//0xCC826178
	UINT32                                                    reserved1;	//0xCC82617C
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_00_T                    sv_blend_ctrl_00;	//0xCC826180
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_01_T                    sv_blend_ctrl_01;	//0xCC826184
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_02_T                    sv_blend_ctrl_02;	//0xCC826188
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_03_T                    sv_blend_ctrl_03;	//0xCC82618C
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_04_T                    sv_blend_ctrl_04;	//0xCC826190
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_05_T                    sv_blend_ctrl_05;	//0xCC826194
	PE_O24_AMG3_GRM_SV_BLEND_CTRL_06_T                    sv_blend_ctrl_06;	//0xCC826198
	UINT32                                                    reserved2;	//0xCC82619C
	PE_O24_AMG3_GRM_GAIN_CTRL_00_T                            gain_ctrl_00;	//0xCC8261A0
	PE_O24_AMG3_GRM_GAIN_CTRL_01_T                            gain_ctrl_01;	//0xCC8261A4
	PE_O24_AMG3_GRM_GAIN_CTRL_02_T                            gain_ctrl_02;	//0xCC8261A8
	PE_O24_AMG3_GRM_GAIN_CTRL_03_T                            gain_ctrl_03;	//0xCC8261AC
	PE_O24_AMG3_GRM_GAIN_CTRL_04_T                            gain_ctrl_04;	//0xCC8261B0
	PE_O24_AMG3_GRM_GAIN_CTRL_05_T                            gain_ctrl_05;	//0xCC8261B4
	UINT32                                                    reserved3;	//0xCC8261B8
	UINT32                                                    reserved4;	//0xCC8261BC
	PE_O24_AMG3_GRM_GRM_BLEND_CTRL_00_T                  grm_blend_ctrl_00;	//0xCC8261C0
	PE_O24_AMG3_GRM_GRM_BLEND_CTRL_01_T                  grm_blend_ctrl_01;	//0xCC8261C4
	UINT32                                                    reserved5;	//0xCC8261C8
	UINT32                                                    reserved6;	//0xCC8261CC
	PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_00_T                lut_dg_bld_ctrl_00;	//0xCC8261D0
	PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_01_T                lut_dg_bld_ctrl_01;	//0xCC8261D4
	PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_02_T                lut_dg_bld_ctrl_02;	//0xCC8261D8
	PE_O24_AMG3_GRM_LUT_DG_BLD_CTRL_03_T                lut_dg_bld_ctrl_03;	//0xCC8261DC
	PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_00_T                lut_gm_bld_ctrl_00;	//0xCC8261E0
	PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_01_T                lut_gm_bld_ctrl_01;	//0xCC8261E4
	PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_02_T                lut_gm_bld_ctrl_02;	//0xCC8261E8
	PE_O24_AMG3_GRM_LUT_GM_BLD_CTRL_03_T                lut_gm_bld_ctrl_03;	//0xCC8261EC
	PE_O24_AMG3_GRM_DEBUG_CTRL_00_T                          debug_ctrl_00;	//0xCC8261F0
	UINT32                                                    reserved7;	//0xCC8261F4
	UINT32                                                    reserved8;	//0xCC8261F8
	UINT32                                                    reserved9;	//0xCC8261FC
	UINT32                                                   reserved10;	//0xCC826200
	UINT32                                                   reserved11;	//0xCC826204
	UINT32                                                   reserved12;	//0xCC826208
	UINT32                                                   reserved13;	//0xCC82620C
	UINT32                                                   reserved14;	//0xCC826210
	UINT32                                                   reserved15;	//0xCC826214
	UINT32                                                   reserved16;	//0xCC826218
	UINT32                                                   reserved17;	//0xCC82621C
	UINT32                                                   reserved18;	//0xCC826220
	UINT32                                                   reserved19;	//0xCC826224
	UINT32                                                   reserved20;	//0xCC826228
	UINT32                                                   reserved21;	//0xCC82622C
	UINT32                                                   reserved22;	//0xCC826230
	UINT32                                                   reserved23;	//0xCC826234
	UINT32                                                   reserved24;	//0xCC826238
	UINT32                                                   reserved25;	//0xCC82623C
	UINT32                                                   reserved26;	//0xCC826240
	UINT32                                                   reserved27;	//0xCC826244
	UINT32                                                   reserved28;	//0xCC826248
	UINT32                                                   reserved29;	//0xCC82624C
	UINT32                                                   reserved30;	//0xCC826250
	UINT32                                                   reserved31;	//0xCC826254
	UINT32                                                   reserved32;	//0xCC826258
	UINT32                                                   reserved33;	//0xCC82625C
	UINT32                                                   reserved34;	//0xCC826260
	UINT32                                                   reserved35;	//0xCC826264
	UINT32                                                   reserved36;	//0xCC826268
	UINT32                                                   reserved37;	//0xCC82626C
	UINT32                                                   reserved38;	//0xCC826270
	UINT32                                                   reserved39;	//0xCC826274
	UINT32                                                   reserved40;	//0xCC826278
	UINT32                                                   reserved41;	//0xCC82627C
	UINT32                                                   reserved42;	//0xCC826280
	UINT32                                                   reserved43;	//0xCC826284
	UINT32                                                   reserved44;	//0xCC826288
	UINT32                                                   reserved45;	//0xCC82628C
	UINT32                                                   reserved46;	//0xCC826290
	UINT32                                                   reserved47;	//0xCC826294
	UINT32                                                   reserved48;	//0xCC826298
	UINT32                                                   reserved49;	//0xCC82629C
	UINT32                                                   reserved50;	//0xCC8262A0
	UINT32                                                   reserved51;	//0xCC8262A4
	UINT32                                                   reserved52;	//0xCC8262A8
	UINT32                                                   reserved53;	//0xCC8262AC
	UINT32                                                   reserved54;	//0xCC8262B0
	UINT32                                                   reserved55;	//0xCC8262B4
	UINT32                                                   reserved56;	//0xCC8262B8
	UINT32                                                   reserved57;	//0xCC8262BC
	UINT32                                                   reserved58;	//0xCC8262C0
	UINT32                                                   reserved59;	//0xCC8262C4
	UINT32                                                   reserved60;	//0xCC8262C8
	UINT32                                                   reserved61;	//0xCC8262CC
	UINT32                                                   reserved62;	//0xCC8262D0
	UINT32                                                   reserved63;	//0xCC8262D4
	UINT32                                                   reserved64;	//0xCC8262D8
	UINT32                                                   reserved65;	//0xCC8262DC
	UINT32                                                   reserved66;	//0xCC8262E0
	UINT32                                                   reserved67;	//0xCC8262E4
	UINT32                                                   reserved68;	//0xCC8262E8
	UINT32                                                   reserved69;	//0xCC8262EC
	PE_O24_AMG3_GRM_GRM_CORE_STAT_00_T                    grm_core_stat_00;	//0xCC8262F0
	PE_O24_AMG3_GRM_GRM_CORE_STAT_01_T                    grm_core_stat_01;	//0xCC8262F4
	PE_O24_AMG3_GRM_GRM_CORE_STAT_02_T                    grm_core_stat_02;	//0xCC8262F8
	PE_O24_AMG3_GRM_GRM_CORE_STAT_03_T                    grm_core_stat_03;	//0xCC8262FC
}PE_AMG_GRM_REG_O24_T;

#endif

